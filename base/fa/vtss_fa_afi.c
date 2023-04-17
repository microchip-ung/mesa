// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_AFI
#include "vtss_fa_cil.h"
#include <stdint.h>

#if defined(VTSS_ARCH_FA) && defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_AFI_V2)

#define FA_AFI_CHIP_PORT(port_no) ((port_no) == VTSS_PORT_NO_NONE ? VTSS_CHIP_PORT_VD1 : VTSS_CHIP_PORT(port_no))

/******************************************************************************/
//
// Internal CIL: Misc. functions
//
/******************************************************************************/

static void fa_afi_debug_frame_hdr(const vtss_debug_printf_t pr, const char *hdr, const char *hdr1)
{
    pr(hdr);
    pr("FrmPtr NxtPtr Type  Delay [ns] Cnt Dst Pri Sht FP\n");
    pr(hdr1);
    pr("------ ------ ----- ---------- --- --- --- --- -----\n");
}

static vtss_rc fa_afi_debug_frame_entry(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 *frm_ptr)
{
    u32 val, type, next, part0, part1, delay_cc;
    u64 delay_ns;

    REG_RD(VTSS_AFI_FRM_NEXT_AND_TYPE(*frm_ptr), &val);
    type = VTSS_X_AFI_FRM_NEXT_AND_TYPE_ENTRY_TYPE(val);
    next = VTSS_X_AFI_FRM_NEXT_AND_TYPE_NEXT_PTR(val);
    pr("0x%04x 0x%04x ", *frm_ptr, next);
    REG_RD(VTSS_AFI_FRM_ENTRY_PART0(*frm_ptr), &part0);
    REG_RD(VTSS_AFI_FRM_ENTRY_PART1(*frm_ptr), &part1);
    if (type == 0) {
        // Frame
        pr("Frame %-10s %3u %3u %3u %3u %u",
           "",
           VTSS_EXTRACT_BITFIELD(part0, VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS, VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID),
           VTSS_EXTRACT_BITFIELD(part0, VTSS_AFI_FRM_TBL_PART0_DSTP_POS, VTSS_AFI_FRM_TBL_PART0_DSTP_WID),
           VTSS_EXTRACT_BITFIELD(part1, VTSS_AFI_FRM_TBL_PART1_EPRIO_POS, VTSS_AFI_FRM_TBL_PART1_EPRIO_WID),
           VTSS_EXTRACT_BITFIELD(part1, VTSS_AFI_FRM_TBL_PART1_SHORT_POS, VTSS_AFI_FRM_TBL_PART1_SHORT_WID),
           VTSS_EXTRACT_BITFIELD(part0, VTSS_AFI_FRM_TBL_PART0_FP_POS, VTSS_AFI_FRM_TBL_PART0_FP_WID));
    } else {
        // Delay
        delay_cc = VTSS_EXTRACT_BITFIELD(part0, VTSS_AFI_FRM_TBL_PART0_DELAY_POS, VTSS_AFI_FRM_TBL_PART0_DELAY_WID);
        delay_ns = VTSS_DIV64(((u64)delay_cc * vtss_state->afi.clk_period_ps), 1000LLU);
        pr("Delay %10" PRIu64, delay_ns); // Delay in nanoseconds
    }
    pr("\n");
    *frm_ptr = next;
    return VTSS_RC_OK;
}

static vtss_rc fa_afi_debug(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    u64 t_us[8], base_us;
    u32 val, val0, val1, t[8], idx, frm_ptr;

    // Timer Tick Table
    pr("Timer Tick Table\n");
    pr("Clock period: %" PRIu64 " ps\n", vtss_state->afi.clk_period_ps);
    pr("Idx  Value Length [us]\n");
    pr("---- ----- -----------\n");

    REG_RD(VTSS_AFI_TTI_TICK_LEN_0_3, &val0);
    REG_RD(VTSS_AFI_TTI_TICK_LEN_4_7, &val1);
    t[0] = VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN0(val0);
    t[1] = VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN1(val0);
    t[2] = VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN2(val0);
    t[3] = VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN3(val0);
    t[4] = VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN4(val1);
    t[5] = VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN5(val1);
    t[6] = VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN6(val1);
    t[7] = VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN7(val1);

    REG_RD(VTSS_AFI_TTI_TICK_BASE, &val);
    val0 = VTSS_X_AFI_TTI_TICK_BASE_BASE_LEN(val);
    base_us = VTSS_DIV64(val0 * vtss_state->afi.clk_period_ps, 1000000LLU);
    pr("Base %5u %11" PRIu64 "\n", val0, base_us);

    for (idx = 0; idx < VTSS_ARRSZ(t); idx++) {
        t_us[idx] = (idx == 0 ? base_us : t_us[idx - 1]) * t[idx];
        pr("%4u %5u %11" PRIu64 "\n", idx, t[idx], t_us[idx]);
    }

    // TTI Table
    pr("\nTTI Table\n");
    fa_afi_debug_frame_hdr(pr, "Idx  TickIdx TmrLen Period [us] Jit ", "---- ------- ------ ----------- --- ");
    for (idx = 0; idx < VTSS_ARRSZ(vtss_state->afi.tti_tbl); idx++) {
        u32  tick_idx, tmr_len;

        REG_RD(VTSS_AFI_TTI_TIMER(idx), &val);
        tick_idx = VTSS_X_AFI_TTI_TIMER_TICK_IDX(val);
        tmr_len  = VTSS_X_AFI_TTI_TIMER_TIMER_LEN(val);
        if (VTSS_X_AFI_TTI_TIMER_TIMER_ENA(val) == 0 || tmr_len == 0) {
            continue;
        }

        pr("%4u %7u %6u %11" PRIu64 " %3u ",
           idx,
           tick_idx,
           tmr_len,
           t_us[tick_idx] * tmr_len,
           VTSS_X_AFI_TTI_TIMER_JITTER(val));

        // Get pointer to first frame table entry
        REG_RD(VTSS_AFI_TTI_FRM(idx), &val);
        frm_ptr = VTSS_X_AFI_TTI_FRM_FRM_PTR(val);
        if (fa_afi_debug_frame_entry(vtss_state, pr, &frm_ptr) != VTSS_RC_OK) {
            break;
        }
    }

    // DTI Table
    pr("\nDTI table\n");
    fa_afi_debug_frame_hdr(pr, "Idx ", "--- ");
    for (idx = 0; idx < VTSS_ARRSZ(vtss_state->afi.dti_tbl); idx++) {
        BOOL first = 1;

        REG_RD(VTSS_AFI_DTI_CTRL(idx), &val);
        if (!VTSS_X_AFI_DTI_CTRL_ENA(val)) {
            // DTI index not in use
            continue;
        }

        // Get pointer to first frame table entry
        REG_RD(VTSS_AFI_DTI_FRM(idx), &val);
        frm_ptr = VTSS_X_AFI_DTI_FRM_FIRST_FRM_PTR(val);
        while (1) {
            if (first) {
                first = 0;
                pr("%3u ", idx);
            } else {
                pr("%-4s", "");
            }
            if (fa_afi_debug_frame_entry(vtss_state, pr, &frm_ptr) != VTSS_RC_OK || frm_ptr == 0) {
                break;
            }
        }
    }

    VTSS_RC(vtss_fa_port_debug_qres(vtss_state, pr, FALSE));
    VTSS_RC(vtss_fa_port_debug_qres(vtss_state, pr, TRUE));

    return VTSS_RC_OK;
}

// Reference to queue into which frame shall be injected.
typedef struct {
    vtss_phys_port_no_t chip_port;
    u32 qu_num;
} fa_afi_qu_ref_t;

/*
Frames to internal dst ports:
  QNUM=(C_INT_BASE_SE+(dst-C_INT_FIRST_DST)) *8+ prio

Frames to frontports:
 QNUM=dst*512+prio*64+src, for src<64
 QNUM=dst*64+prio*8+(src-64)+C_QNUM_HIGH, for src>=64

Frames transmitted with super priority:
  QNUM=C_SP0_BASE_Q+dst

Frames transmitted with super priority after port shaper
  QNUM=C_SP1_BASE_Q+dst

C_INT_BASE_SE is 5031
C_INT_FIRST_DST is 65
C_QNUM_HIGH is 35840
C_SP0_BASE_Q is 40320
C_SP1_BASE_Q is 40390
*/
static vtss_rc fa_afi_port_prio_2_qu_ref(vtss_state_t *vtss_state, vtss_port_no_t port_no,
                                         vtss_prio_t prio, fa_afi_qu_ref_t *qu_ref)
{
    qu_ref->chip_port = FA_AFI_CHIP_PORT(port_no); // Destination port

    if (prio == VTSS_PRIO_SUPER) {
        // Super priority
        qu_ref->qu_num = (40320 + qu_ref->chip_port);
    } else if (prio > VTSS_PRIO_SUPER) {
        // Super priority after shaper
        qu_ref->qu_num = (40390 + qu_ref->chip_port);
    } else if (qu_ref->chip_port == VTSS_CHIP_PORT_VD1) {
        // Internal VD0 port
        qu_ref->qu_num = ((5031 + VTSS_CHIP_PORT_VD0 - VTSS_CHIP_PORTS) * 8 + prio);
    } else {
        // Front port, CPU_0 is used as source
        qu_ref->qu_num = (qu_ref->chip_port * 64 + prio * 8 + VTSS_CHIP_PORT_CPU_0 - 64 + 35840);
    }

    VTSS_I("port_no = %d, prio = %u => qu_num = %u", port_no, prio, qu_ref->qu_num);

    return VTSS_RC_OK;
}

static vtss_afi_port_t *fa_afi_port_tbl_entry(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return &vtss_state->afi.port_tbl[port_no == VTSS_PORT_NO_NONE ? VTSS_ARRSZ(vtss_state->afi.port_tbl) - 1 : port_no];
}

static vtss_rc fa_afi_chip_port_flush(vtss_state_t *vtss_state, u32 port)
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
        REG_RD(VTSS_AFI_PORT_FRM_OUT(port), &afi_val);

        if ((afi_val = VTSS_X_AFI_PORT_FRM_OUT_FRM_OUT_CNT(afi_val)) == 0) {
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
            VTSS_E("AFI's FRM_OUT_CNT is non-zero (%u) on chip port %u even after %u msecs of trying", afi_val, port, timeout);
            rc = VTSS_RC_ERROR;
            break;
        }
    }

    VTSS_I("Flush: Polled FRM_OUT_CNT %u times for chip port %u", cnt, port);
    return rc;
}

static vtss_rc fa_afi_chip_port_start(vtss_state_t *vtss_state, u32 port, vtss_afi_port_t *afi_port)
{
    // Set FRM_OUT_MAX back to normal
    REG_WRM(VTSS_AFI_PORT_CFG(port),
            VTSS_F_AFI_PORT_CFG_FRM_OUT_MAX(afi_port->frm_out_max),
            VTSS_M_AFI_PORT_CFG_FRM_OUT_MAX);

    // Set FC_SKIP_TTI_INJ=0
    REG_WRM(VTSS_AFI_PORT_CFG(port),
            VTSS_F_AFI_PORT_CFG_FC_SKIP_TTI_INJ(0),
            VTSS_M_AFI_PORT_CFG_FC_SKIP_TTI_INJ);

    VTSS_I("Reallowed injection to chip-port %u, and set frame out max back to %u", port, afi_port->frm_out_max);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_chip_port_stop(vtss_state_t *vtss_state, u32 port)
{
    // Set FC_SKIP_TTI_INJ = 1
    // Stop the port by setting FRM_OUT_MAX to 0.
    REG_WRM(VTSS_AFI_PORT_CFG(port),
            VTSS_F_AFI_PORT_CFG_FC_SKIP_TTI_INJ(1) |
            VTSS_F_AFI_PORT_CFG_FRM_OUT_MAX(0),
            VTSS_M_AFI_PORT_CFG_FC_SKIP_TTI_INJ |
            VTSS_M_AFI_PORT_CFG_FRM_OUT_MAX);

    VTSS_I("Stopped injection to chip-port %u by setting FRM_OUT_MAX to 0", port);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_port_start(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return fa_afi_chip_port_start(vtss_state, FA_AFI_CHIP_PORT(port_no), fa_afi_port_tbl_entry(vtss_state, port_no));
}

static vtss_rc fa_afi_port_stop(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 port = FA_AFI_CHIP_PORT(port_no);

    VTSS_I("port_no = %d, chip_port = %u", port_no, port);

    VTSS_RC(fa_afi_chip_port_stop( vtss_state, port));

    return fa_afi_chip_port_flush(vtss_state, port);
}

static vtss_rc fa_afi_port_link_up(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_afi_port_t *port = fa_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. port = %u, link = %d, started = %d", port_no, port->link, port->started);

    if (port->started) {
        VTSS_RC(fa_afi_port_start(vtss_state, port_no));
    }

    port->link = 1;
    VTSS_I("Exit.  port = %u, link = %d, started = %d", port_no, port->link, port->started);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_port_link_down(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_afi_port_t *port = fa_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. port = %u, link = %d, started = %d", port_no, port->link, port->started);

    VTSS_RC(fa_afi_port_stop(vtss_state, port_no));
    port->link = 0;

    VTSS_I("Exit.  port = %u, link = %d, started = %d", port_no, port->link, port->started);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_hijack_error_print(vtss_state_t *vtss_state)
{
    u32  cnt, val, idx;
    char buf1[300], buf2[300];

    cnt = VTSS_SNPRINTF(buf1, sizeof(buf1), "QRES:RES_CTRL[VD1 = %u]:RES_STAT\n", VTSS_CHIP_PORT_VD1);
    for (idx = 0; idx < 8; idx++) {
        REG_RD(VTSS_QRES_RES_STAT(3 * 1024 + VTSS_CHIP_PORT_VD1 * 8 + idx), &val);
        cnt += VTSS_SNPRINTF(buf1 + cnt, sizeof(buf1) - cnt,  "Qu = %u: Cnt = %u\n", idx, val);
    }

    cnt = VTSS_SNPRINTF(buf2, sizeof(buf2), "QRES:RES_CTRL[VD1 = %u]:RES_STAT_CUR\n", VTSS_CHIP_PORT_VD1);
    for (idx = 0; idx < 8; idx++) {
        REG_RD(VTSS_QRES_RES_STAT_CUR(3 * 1024 + VTSS_CHIP_PORT_VD1 * 8 + idx), &val);
        cnt += VTSS_SNPRINTF(buf2 + cnt, sizeof(buf2) - cnt,  "Qu = %u: Cnt = %u\n", idx, val);
    }

    VTSS_E("CIL: Timeout waiting for NEW_FRM_CTRL.VLD\n%s\n%s", buf1, buf2);
    return VTSS_RC_OK;
}

static vtss_rc fa_afi_frm_hijack(vtss_state_t *vtss_state, i32 frm_idx, vtss_prio_t prio)
{
    frm_info_t     *fi = &vtss_state->afi.frm_tbl[frm_idx].frm_delay.frm.frm_info;
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
        REG_RD(VTSS_AFI_NEW_FRM_CTRL, &new_frm_vld);
        if (VTSS_X_AFI_NEW_FRM_CTRL_VLD(new_frm_vld)) {
            break;
        }

        if (VTSS_MTIMER_TIMEOUT(&timer)) {
            (void)fa_afi_hijack_error_print(vtss_state);
            return VTSS_RC_ERROR;
        }
    }

    VTSS_I("Reads = %u", cnt);

    // Get frm_info for hijacked frame
    REG_RD(VTSS_AFI_NEW_FRM_INFO, &frm_info);
    frm_info = VTSS_X_AFI_NEW_FRM_INFO_FRM_INFO(frm_info);
    fi->fp = VTSS_EXTRACT_BITFIELD(frm_info, VTSS_AFI_FRM_INFO_FP_POS, VTSS_AFI_FRM_INFO_FP_WID);
    fi->dstp = VTSS_EXTRACT_BITFIELD(frm_info, VTSS_AFI_FRM_INFO_DSTP_POS, VTSS_AFI_FRM_INFO_DSTP_WID);
    fi->fshort = VTSS_EXTRACT_BITFIELD(frm_info, VTSS_AFI_FRM_INFO_SHORT_POS, VTSS_AFI_FRM_INFO_SHORT_WID);
    fi->eprio = VTSS_EXTRACT_BITFIELD(frm_info, VTSS_AFI_FRM_INFO_EPRIO_POS, VTSS_AFI_FRM_INFO_EPRIO_WID);
    VTSS_I("idx: %u, info: 0x%08x, fp/dstp/eprio/short: %u/%u/%u/%u", frm_idx, frm_info, fi->fp, fi->dstp, fi->eprio, fi->fshort);
    fi->eprio = prio; // Extracted eprio is always zero, so we use the priority of the AFI instance

    // Setup FRM_TBL entry
    REG_WRM(VTSS_AFI_FRM_NEXT_AND_TYPE(frm_idx),
            VTSS_F_AFI_FRM_NEXT_AND_TYPE_ENTRY_TYPE(0),
            VTSS_M_AFI_FRM_NEXT_AND_TYPE_ENTRY_TYPE);
    REG_WR(VTSS_AFI_FRM_ENTRY_PART0(frm_idx),
           VTSS_ENCODE_BITFIELD(fi->fp, VTSS_AFI_FRM_TBL_PART0_FP_POS, VTSS_AFI_FRM_TBL_PART0_FP_WID) |
           VTSS_ENCODE_BITFIELD(fi->dstp, VTSS_AFI_FRM_TBL_PART0_DSTP_POS, VTSS_AFI_FRM_TBL_PART0_DSTP_WID));
    REG_WR(VTSS_AFI_FRM_ENTRY_PART1(frm_idx),
           VTSS_ENCODE_BITFIELD(fi->fshort, VTSS_AFI_FRM_TBL_PART1_SHORT_POS, VTSS_AFI_FRM_TBL_PART1_SHORT_WID) |
           VTSS_ENCODE_BITFIELD(fi->eprio, VTSS_AFI_FRM_TBL_PART1_EPRIO_POS, VTSS_AFI_FRM_TBL_PART1_EPRIO_WID));

    REG_WR(VTSS_AFI_NEW_FRM_CTRL, VTSS_F_AFI_NEW_FRM_CTRL_VLD(0));

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_frm_setup(vtss_state_t *vtss_state, i32 frm_idx)
{
    vtss_afi_frm_t *frm = &vtss_state->afi.frm_tbl[frm_idx];
    u32            inj_cnt = frm->frm_delay.frm.inj_cnt;

    REG_WRM(VTSS_AFI_FRM_ENTRY_PART0(frm_idx),
            VTSS_ENCODE_BITFIELD(inj_cnt, VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS, VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID),
            VTSS_ENCODE_BITMASK(VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS, VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID));
    REG_WR(VTSS_AFI_FRM_NEXT_AND_TYPE(frm_idx),
           VTSS_F_AFI_FRM_NEXT_AND_TYPE_NEXT_PTR(frm->next_ptr) |
           VTSS_F_AFI_FRM_NEXT_AND_TYPE_ENTRY_TYPE(0));

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_delay_setup(vtss_state_t *vtss_state, i32 frm_idx)
{
    vtss_afi_frm_t *frm = &vtss_state->afi.frm_tbl[frm_idx];
    u32            delay = frm->frm_delay.delay.delay;

    REG_WR(VTSS_AFI_FRM_ENTRY_PART0(frm_idx),
           VTSS_ENCODE_BITFIELD(delay, VTSS_AFI_FRM_TBL_PART0_DELAY_POS, VTSS_AFI_FRM_TBL_PART0_DELAY_WID));

    REG_WR(VTSS_AFI_FRM_NEXT_AND_TYPE(frm_idx),
           VTSS_F_AFI_FRM_NEXT_AND_TYPE_NEXT_PTR(frm->next_ptr) |
           VTSS_F_AFI_FRM_NEXT_AND_TYPE_ENTRY_TYPE(1));

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_set_frm_rm(vtss_state_t *vtss_state, i32 frm_idx)
{
    u32 part1;

    VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));

    REG_RD(VTSS_AFI_FRM_ENTRY_PART1(frm_idx), &part1);
    if (VTSS_EXTRACT_BITFIELD(part1, VTSS_AFI_FRM_TBL_PART1_RM_POS, 1)) {
        VTSS_E("frm_rm already set");
        return VTSS_RC_ERROR;
    }
    if (VTSS_EXTRACT_BITFIELD(part1, VTSS_AFI_FRM_TBL_PART1_GONE_POS, 1)) {
        VTSS_E("frm_gone already set");
        return VTSS_RC_ERROR;
    }
    part1 |= (1 << VTSS_AFI_FRM_TBL_PART1_RM_POS);
    REG_WR(VTSS_AFI_FRM_ENTRY_PART1(frm_idx), part1);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_frm_gone_get(vtss_state_t *vtss_state, u8 *const frm_gone, i32 frm_idx)
{
    u32 part1;

    REG_RD(VTSS_AFI_FRM_ENTRY_PART1(frm_idx), &part1);
    *frm_gone = VTSS_EXTRACT_BITFIELD(part1, VTSS_AFI_FRM_TBL_PART1_GONE_POS, 1);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_dti_pause_resume(vtss_state_t *vtss_state, u32 dti_idx, BOOL pause)
{
    vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];

    VTSS_I("Enter. %sing dti_idx = %u", pause ? "Paus" : "Resum", dti_idx);

    // Start/Stop
    REG_WRM(VTSS_AFI_DTI_CTRL(dti_idx),
            VTSS_F_AFI_DTI_CTRL_ENA(pause ? 0 : 1),
            VTSS_M_AFI_DTI_CTRL_ENA);
    dti->paused = pause;

    VTSS_I("Exit (%u)", dti_idx);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_tti_pause_resume(vtss_state_t *vtss_state, u32 tti_idx, BOOL pause)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

    VTSS_I("Enter. %sing tti_idx = %u", pause ? "Paus" : "Resum", tti_idx);

    // Start and stop timer using timer_ena
    REG_WRM(VTSS_AFI_TTI_TIMER(tti_idx),
            VTSS_F_AFI_TTI_TIMER_TIMER_ENA(pause ? 0 : 1),
            VTSS_M_AFI_TTI_TIMER_TIMER_ENA);
    tti->paused = pause;

    VTSS_I("Exit (%u)", tti_idx);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_up_flows_pause_resume(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL pause)
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
            VTSS_RC(fa_afi_dti_pause_resume(vtss_state, dti_idx, pause));
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
            VTSS_RC(fa_afi_tti_pause_resume(vtss_state, tti_idx, pause));
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
        u32 frm_out_max = fa_afi_port_tbl_entry(vtss_state, VTSS_PORT_NO_NONE)->frm_out_max;
        u32 sleep_ms = (8 * frm_out_max) / 1000;

        // Sleep at least one millisecond
        sleep_ms = sleep_ms ? sleep_ms : 1;

        VTSS_I("Sleeping %u ms", sleep_ms);
        VTSS_MSLEEP(sleep_ms);
    }

    VTSS_I("Exit (%sing up-flows on port_no = %u)", pause ? "paus" : "resum", port_no);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_port_fwd_set(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL new_fwd, BOOL *old_fwd)
{
    u32 val, port = FA_AFI_CHIP_PORT(port_no);

    REG_RD(VTSS_QFWD_SWITCH_PORT_MODE(port), &val);

    VTSS_I("Enter(port_no = %d => chip_port = %u, new_fwd = %d, val before = 0x%08x", port_no, port, new_fwd, val);

    if (old_fwd) {
        *old_fwd = VTSS_X_QFWD_SWITCH_PORT_MODE_PORT_ENA(val);
    }

    if (new_fwd) {
        val |= VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA;
    } else {
        val &= ~VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA;
    }

    REG_WR(VTSS_QFWD_SWITCH_PORT_MODE(port), val);
    VTSS_I("Exit(port_no = %d => chip_port = %u, new_fwd = %d, val after = 0x%08x", port_no, port, new_fwd, val);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_frm_gone_wait(vtss_state_t *vtss_state, u32 idx, vtss_port_no_t port_no, i32 frm_idx, BOOL is_dti)
{
    u32             poll_cnt, poll_cnt_max, method;
    BOOL            frm_gone = FALSE, old_fwd = TRUE;
    vtss_afi_port_t *port = fa_afi_port_tbl_entry(vtss_state, port_no);

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
            VTSS_RC(fa_afi_port_fwd_set(vtss_state, port_no, 0, &old_fwd));
            break;

        case 3:
            // Stop and flush other AFI flows on this port before polling again.
            VTSS_RC(fa_afi_port_stop(vtss_state, port_no));
            break;
        }

        // Poll for FRM_GONE == 1 for last frame
        poll_cnt = 0;
        while (!frm_gone && poll_cnt++ < poll_cnt_max) {
            VTSS_RC(fa_afi_frm_gone_get(vtss_state, &frm_gone, frm_idx));
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
            VTSS_RC(fa_afi_port_start(vtss_state, port_no));
        }

        // Fallthrough

    case 2:
        // Set port forwarding back to what is was
        VTSS_RC(fa_afi_port_fwd_set(vtss_state, port_no, old_fwd, NULL));

        // Fallthrough

    case 1:
        // Nothing more to do
        break;
    }

    if (frm_gone) {
        VTSS_I("%s_idx = %u on port %d: Polled %u times out of %u using method %u. FRM_GONE = %d", is_dti ? "dti" : "tti", idx, port_no, poll_cnt, poll_cnt_max, method, frm_gone);
        return VTSS_RC_OK;
    } else {
        VTSS_E("%s_idx = %u on port %d: Polled %u times out of %u using method %u. FRM_GONE = %d", is_dti ? "dti" : "tti", idx, port_no, poll_cnt, poll_cnt_max, method, frm_gone);
        return VTSS_RC_ERROR;

    }
}

/******************************************************************************/
//
// Internal CIL: DTI functions
//
/******************************************************************************/

static vtss_rc fa_afi_dti_qu_ref_update(vtss_state_t *vtss_state, u32 dti_idx)
{
    vtss_afi_dti_t   *dti = &vtss_state->afi.dti_tbl[dti_idx];
    fa_afi_qu_ref_t qu_ref;

    VTSS_RC(fa_afi_port_prio_2_qu_ref(vtss_state, dti->port_no, dti->prio, &qu_ref));
    REG_WR(VTSS_AFI_DTI_PORT_QU(dti_idx),
           VTSS_F_AFI_DTI_PORT_QU_QU_NUM(qu_ref.qu_num) |
           VTSS_F_AFI_DTI_PORT_QU_PORT_NUM(qu_ref.chip_port));

    return VTSS_RC_OK;
}

/******************************************************************************/
//
// Internal CIL: TTI functions
//
/******************************************************************************/

static vtss_rc fa_afi_tti_cal_init(vtss_state_t *vtss_state)
{
    u32  max_poll_cnt = 5;
    u32  val;
    BOOL tti_init = 1 /* picky compiler */;

    REG_WRM(VTSS_AFI_TTI_CTRL,
            VTSS_F_AFI_TTI_CTRL_TTI_INIT(1),
            VTSS_M_AFI_TTI_CTRL_TTI_INIT);

    // Wait for device to clear TTI_INIT
    while (max_poll_cnt-- > 0) {
        REG_RD(VTSS_AFI_TTI_CTRL, &val);
        if ((tti_init = VTSS_X_AFI_TTI_CTRL_TTI_INIT(val)) == 0) {
            break;
        }
    }

    if (tti_init == 1) {
        VTSS_E("Timeout waiting for TTI_CTRL.TTI_INIT == 0");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_tti_qu_ref_update(vtss_state_t *vtss_state, u32 tti_idx)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];
    fa_afi_qu_ref_t qu_ref;

    VTSS_RC(fa_afi_port_prio_2_qu_ref(vtss_state, tti->port_no, tti->prio, &qu_ref));
    REG_WR(VTSS_AFI_TTI_PORT_QU(tti_idx),
           VTSS_F_AFI_TTI_PORT_QU_QU_NUM(qu_ref.qu_num) |
           VTSS_F_AFI_TTI_PORT_QU_PORT_NUM(qu_ref.chip_port));

    return VTSS_RC_OK;
}

/******************************************************************************/
//
// External CIL: DTI functions
//
/******************************************************************************/

static vtss_rc fa_afi_dti_start(vtss_state_t *vtss_state,
                                u32 dti_idx, BOOL do_frm_delay_config, BOOL do_dti_config, BOOL start_flow)
{
    vtss_afi_dti_t *dti     = &vtss_state->afi.dti_tbl[dti_idx];
    vtss_afi_frm_t *frm_tbl = vtss_state->afi.frm_tbl;
    u32            frm_idx;
    BOOL           link;
    vtss_port_no_t port_no;

    VTSS_I("Enter: Starting dti_idx = %u (do_config = %d)", dti_idx, do_dti_config);

    if (dti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        VTSS_E("DTI already started");
        return VTSS_RC_ERROR;
    }

    if (do_frm_delay_config) {
        // (Re)write FRM_TBL configuration for DTI
        frm_idx = dti->first_frm_idx;
        while (frm_idx > 0) {
            if (frm_tbl[frm_idx].entry_type) {
                VTSS_RC(fa_afi_delay_setup(vtss_state, frm_idx));
            } else {
                VTSS_RC(fa_afi_frm_setup(vtss_state, frm_idx));
            }
            frm_idx = frm_tbl[frm_idx].next_ptr;
        }
    }

    if (do_dti_config) {
        // (Re)write DTI configuration
        REG_WRM(VTSS_AFI_DTI_MODE(dti_idx),
                VTSS_F_AFI_DTI_MODE_MODE(dti->mode) |
                VTSS_F_AFI_DTI_MODE_TRAILING_DELAY_SEQ_CNT(dti->trailing_delay_seq_cnt) |
                VTSS_F_AFI_DTI_MODE_FRM_INJ_CNT(0) |
                VTSS_F_AFI_DTI_MODE_DTI_NEXT(dti->dti_next),
                VTSS_M_AFI_DTI_MODE_MODE |
                VTSS_M_AFI_DTI_MODE_TRAILING_DELAY_SEQ_CNT |
                VTSS_M_AFI_DTI_MODE_FRM_INJ_CNT |
                VTSS_M_AFI_DTI_MODE_DTI_NEXT);
        VTSS_RC(fa_afi_dti_qu_ref_update(vtss_state, dti_idx));
    }

    // Configuration settings performed regardless of do_dti_config
    REG_WRM(VTSS_AFI_DTI_FRM(dti_idx),
            VTSS_F_AFI_DTI_FRM_NEXT_FRM_PTR(dti->first_frm_idx),
            VTSS_M_AFI_DTI_FRM_NEXT_FRM_PTR);
    REG_WRM(VTSS_AFI_DTI_CNT(dti_idx),
            VTSS_F_AFI_DTI_CNT_CNT(dti->mode == 1 ? 0 : dti->frm_inj_cnt),
            VTSS_M_AFI_DTI_CNT_CNT);
    REG_WR(VTSS_AFI_DTI_CNT_DOWN(dti_idx), 0);

    // This must be enabled for JR2C and later.
    REG_WR(VTSS_AFI_DTI_DURATION(dti_idx), 0);

    REG_WR(VTSS_AFI_DTI_CTRL(dti_idx), VTSS_F_AFI_DTI_CTRL_BW(dti->bw));

    if (!start_flow) {
        VTSS_I("Exit without starting flow. dti_idx = %u", dti_idx);
        return VTSS_RC_OK;
    }

    // Always start down-flows, because a per-port AFI mechanism ensures that
    // flows are not really started until the port gets link.
    // Only start up-flows if there's link on the port. Calls to
    // jr2_afi_link_state_change() ensure that these up-flows are started and
    // stopped by link state changes.
    port_no = (dti->port_no != VTSS_PORT_NO_NONE ? dti->port_no : dti->masquerade_port_no);
    link    = (dti->port_no != VTSS_PORT_NO_NONE ? TRUE         : fa_afi_port_tbl_entry(vtss_state, port_no)->link);

    VTSS_I("port_no = %d: link = %d", port_no, link);
    VTSS_RC(fa_afi_dti_pause_resume(vtss_state, dti_idx, !link));

    // User has started this flow now, even though it may not be started in
    // reality.
    dti->state = VTSS_AFI_ENTRY_STATE_STARTED;

    VTSS_I("Exit. dti_idx = %u, paused = %d", dti_idx, dti->paused);
    return VTSS_RC_OK;
}

static vtss_rc fa_afi_dti_stop(vtss_state_t *vtss_state, u32 dti_idx)
{
    vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];

    VTSS_I("Enter. Stopping dti_idx = %u", dti_idx);

    if (dti->state != VTSS_AFI_ENTRY_STATE_STARTED) {
        VTSS_E("DTI not started");
        return VTSS_RC_ERROR;
    }
    VTSS_RC(fa_afi_dti_pause_resume(vtss_state, dti_idx, 1));
    dti->state = VTSS_AFI_ENTRY_STATE_STOPPED;

    VTSS_I("Exit (%u)", dti_idx);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_dti_frm_hijack(vtss_state_t *vtss_state, u32 dti_idx, u32 frm_size)
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
        VTSS_E("Frame idx for dti->first_frm_idx = %u is 0, when iterating %u times", dti->first_frm_idx, dti->frm_cnt);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));

    frm = &vtss_state->afi.frm_tbl[frm_idx];

    VTSS_RC(fa_afi_frm_hijack(vtss_state, frm_idx, dti->prio));
    frm->frm_delay.frm.frm_size = frm_size;

    if (dti->frm_cnt++ == 0) {
        // Setup FIRST_FRM_PTR
        REG_WRM(VTSS_AFI_DTI_FRM(dti_idx),
                VTSS_F_AFI_DTI_FRM_FIRST_FRM_PTR(frm_idx),
                VTSS_M_AFI_DTI_FRM_FIRST_FRM_PTR);
    }

    VTSS_I("Exit(%u)", dti_idx);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_dti_frm_rm_inj(vtss_state_t *vtss_state, u32 dti_idx)
{
    vtss_afi_dti_t  *dti = &vtss_state->afi.dti_tbl[dti_idx];
    vtss_afi_frm_t  *frm_tbl = vtss_state->afi.frm_tbl;
    i32             frm_idx, last_frm_idx = 0;

    VTSS_I("Removing dti_idx = %u", dti_idx);

    if (dti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        VTSS_E("ID = %u: Injection must be stopped before rm injection", dti_idx);
        return VTSS_RC_ERROR;
    }

    // Set the FRM_RM bit for each frame to be removed in the Frame Table.
    for (frm_idx = dti->first_frm_idx; frm_idx > 0; frm_idx = frm_tbl[frm_idx].next_ptr) {
        if (frm_tbl[frm_idx].entry_type != 0) {
            // Not a frame entry
            continue;
        }

        // This is a frame. Remove it.
        VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));
        VTSS_RC(fa_afi_set_frm_rm(vtss_state, frm_idx));
        last_frm_idx = frm_idx;
    }

    // Set DTI_FRM.NEXT_FRM_PTR to DTI_FRM.FIRST_FRM_PTR
    REG_WRM(VTSS_AFI_DTI_FRM(dti_idx),
            VTSS_F_AFI_DTI_FRM_NEXT_FRM_PTR(dti->first_frm_idx),
            VTSS_M_AFI_DTI_FRM_NEXT_FRM_PTR);

    // Set DTI_MODE.MODE=0
    // Set DTI_MODE.FRM_INJ_CNT to 0.
    if (dti->mode != 0) {
        REG_WRM(VTSS_AFI_DTI_MODE(dti_idx),
                VTSS_F_AFI_DTI_MODE_MODE(0) |
                VTSS_F_AFI_DTI_MODE_FRM_INJ_CNT(0),
                VTSS_M_AFI_DTI_MODE_MODE |
                VTSS_M_AFI_DTI_MODE_FRM_INJ_CNT);
    }

    // Set DTI_CNT.CNT=1
    REG_WRM(VTSS_AFI_DTI_CNT(dti_idx),
            VTSS_F_AFI_DTI_CNT_CNT(1),
            VTSS_M_AFI_DTI_CNT_CNT);

    // Set all delays in sequence to 0 to speed up the removal procedure
    for (frm_idx = dti->first_frm_idx; frm_idx > 0; frm_idx = frm_tbl[frm_idx].next_ptr) {
        if (frm_tbl[frm_idx].entry_type != 1) {
            // Not a delay entry
            continue;
        }

        // This is a delay. Clear it.
        VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));
        REG_WR(VTSS_AFI_FRM_ENTRY_PART0(frm_idx), 0);
    }

    REG_WR(VTSS_AFI_DTI_CNT_DOWN(dti_idx), 0);

    // Start removal injection!
    REG_WR(VTSS_AFI_DTI_CTRL(dti_idx),
           VTSS_F_AFI_DTI_CTRL_ENA(1) |
           VTSS_F_AFI_DTI_CTRL_BW(0));

    // Wait until the frame is gone.
    VTSS_RC(fa_afi_frm_gone_wait(vtss_state, dti_idx, dti->port_no, last_frm_idx, TRUE));

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_dti_cnt_get(vtss_state_t *vtss_state, u32 dti_idx, u32 *const cnt)
{
    VTSS_I("Enter(%u)", dti_idx);
    REG_RD(VTSS_AFI_DTI_CNT(dti_idx), cnt);
    VTSS_I("Exit(%u = %u)", dti_idx, *cnt);
    return VTSS_RC_OK;
}

/******************************************************************************/
//
// External CIL: TTI functions
//
/******************************************************************************/

static vtss_rc fa_afi_ttis_enable(vtss_state_t *vtss_state)
{
    VTSS_I("Enter");
    REG_WRM(VTSS_AFI_TTI_CTRL,
            VTSS_F_AFI_TTI_CTRL_TTI_ENA(1),
            VTSS_M_AFI_TTI_CTRL_TTI_ENA);
    VTSS_I("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_afi_tti_start(vtss_state_t *vtss_state,  u32 tti_idx, BOOL do_config)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];
    u32            rand_tick_cnt;
    BOOL           link;
    vtss_port_no_t port_no;

    VTSS_I("Enter. Starting tti_idx = %u (do_config = %d)", tti_idx, do_config);

    if (tti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        VTSS_E("TTI already started");
        return VTSS_RC_ERROR;
    }

    if (do_config) {
        VTSS_RC(fa_afi_tti_qu_ref_update(vtss_state, tti_idx));

        REG_WRM(VTSS_AFI_TTI_TIMER(tti_idx),
                VTSS_F_AFI_TTI_TIMER_TICK_IDX(tti->tick_idx) |
                VTSS_F_AFI_TTI_TIMER_JITTER(tti->jitter) |
                VTSS_F_AFI_TTI_TIMER_TIMER_LEN(tti->timer_len),
                VTSS_M_AFI_TTI_TIMER_TICK_IDX |
                VTSS_M_AFI_TTI_TIMER_JITTER |
                VTSS_M_AFI_TTI_TIMER_TIMER_LEN);
        REG_WR(VTSS_AFI_TTI_FRM(tti_idx),
               VTSS_F_AFI_TTI_FRM_FRM_PTR(tti->frm_idx));
    }

    // Set TICK_CNT to a random value in range [1-TIMER_LEN]
    rand_tick_cnt = tti->start_cfg.first_frame_urgent ? 1 : 1 + (rand() % tti->timer_len);

    REG_WRM(VTSS_AFI_TTI_TICKS(tti_idx),
            VTSS_F_AFI_TTI_TICKS_TICK_CNT(rand_tick_cnt),
            VTSS_M_AFI_TTI_TICKS_TICK_CNT);

    // Always start down-flows, because a per-port AFI mechanism ensures that
    // flows are not really started until the port gets link.
    // Only start up-flows if there's link on the port. Calls to
    // jr2_afi_link_state_change() ensure that these up-flows are started and
    // stopped by link state changes.
    port_no = tti->port_no != VTSS_PORT_NO_NONE ? tti->port_no : tti->masquerade_port_no;
    link    = tti->port_no != VTSS_PORT_NO_NONE ? TRUE         : fa_afi_port_tbl_entry(vtss_state, port_no)->link;

    VTSS_I("port_no = %d: link = %d", port_no, link);
    VTSS_RC(fa_afi_tti_pause_resume(vtss_state, tti_idx, !link));

    // User has started this flow now, even though it may not be started in
    // reality.
    tti->state = VTSS_AFI_ENTRY_STATE_STARTED;

    VTSS_I("Exit. tti_idx = %u, paused = %d", tti_idx, tti->paused);
    return VTSS_RC_OK;
}

static vtss_rc fa_afi_tti_stop(vtss_state_t *vtss_state, u32 tti_idx)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

    VTSS_I("Enter. Stopping tti_idx = %u", tti_idx);

    if (tti->state != VTSS_AFI_ENTRY_STATE_STARTED) {
        VTSS_E("DTI not started");
        return VTSS_RC_ERROR;
    }
    VTSS_RC(fa_afi_tti_pause_resume(vtss_state, tti_idx, 1));
    tti->state = VTSS_AFI_ENTRY_STATE_STOPPED;

    VTSS_I("Exit(%u)", tti_idx);
    return VTSS_RC_OK;
}

static vtss_rc fa_afi_tti_frm_hijack(vtss_state_t *vtss_state, u32 tti_idx)
{
    vtss_rc        rc;
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

    VTSS_I("Enter(%u)", tti_idx);
    rc = fa_afi_frm_hijack(vtss_state, tti->frm_idx, tti->prio);
    VTSS_I("Exit(%u)", tti_idx);
    return rc;
}

static vtss_rc fa_afi_tti_frm_rm_inj(vtss_state_t *vtss_state, u32 tti_idx)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

    VTSS_I("Enter(%u)", tti_idx);

    if (tti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        VTSS_E("ID = %u: Injection must be stopped before rm injection", tti_idx);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(fa_afi_set_frm_rm(vtss_state, tti->frm_idx));

    // Start removal injection!
    // Set TIMER_LEN to max value (=> inject ASAP)
    REG_WRM(VTSS_AFI_TTI_TIMER(tti_idx),
            VTSS_F_AFI_TTI_TIMER_TIMER_LEN((1 << VTSS_AFI_TTI_TBL_TIMER_LEN_WID) - 1),
            VTSS_M_AFI_TTI_TIMER_TIMER_LEN);

    // Make sure timer is started
    REG_WRM(VTSS_AFI_TTI_TIMER(tti_idx),
            VTSS_F_AFI_TTI_TIMER_TIMER_ENA(1),
            VTSS_M_AFI_TTI_TIMER_TIMER_ENA);

    // Wait until the frame is gone.
    VTSS_RC(fa_afi_frm_gone_wait(vtss_state, tti_idx, tti->port_no, tti->frm_idx, FALSE));

    VTSS_I("Exit(%u)", tti_idx);
    return VTSS_RC_OK;
}

/******************************************************************************/
//
// External CIL: Other functions
//
/******************************************************************************/

static vtss_rc fa_afi_link_state_change(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL *link_up)
{
    vtss_afi_port_t *port = fa_afi_port_tbl_entry(vtss_state, port_no);
    BOOL return_val = port->link;

    VTSS_I("Enter. port_no = %d, current link = %d, new link = %d", port_no, return_val, *link_up);

    if (*link_up) {
        // Re-allow frame injection to this port
        VTSS_RC(fa_afi_port_link_up(vtss_state, port_no));

        // Start all VD1 flows that utilize this port ingress-wise
        VTSS_RC(fa_afi_up_flows_pause_resume(vtss_state, port_no, FALSE));
    } else if (port->link) {
        // Stop all VD1 flows that utilize this port ingress-wise
        VTSS_RC(fa_afi_up_flows_pause_resume(vtss_state, port_no, TRUE));

        // Disable frame injection to this port.
        VTSS_RC(fa_afi_port_link_down(vtss_state, port_no));
    }

    *link_up = return_val;

    VTSS_I("Exit(port_no = %u)", port_no);
    return VTSS_RC_OK;
}

static vtss_rc fa_afi_qu_ref_update(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 dti_idx, tti_idx;

    // Injection must already have been stopped on #port_no.

    // Update the queue number for all DTIs egressing #port_no (down-flows)
    for (dti_idx = 0; dti_idx < VTSS_ARRSZ(vtss_state->afi.dti_tbl); dti_idx++) {
        vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];

        if (dti->state != VTSS_AFI_ENTRY_STATE_FREE && dti->port_no == port_no) {
            VTSS_RC(fa_afi_dti_qu_ref_update(vtss_state, dti_idx));
        }
    }

    // Update the queue number for all TTIs egressing #port_no (down-flows)
    for (tti_idx = 0; tti_idx < VTSS_ARRSZ(vtss_state->afi.tti_tbl); tti_idx++) {
        vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

        if (tti->state != VTSS_AFI_ENTRY_STATE_FREE && tti->port_no == port_no) {
            VTSS_RC(fa_afi_tti_qu_ref_update(vtss_state, tti_idx));
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_enable(vtss_state_t *vtss_state)
{
    VTSS_I("Enter");

    // Enable AFI first (power saving feature added on ServalT)
    REG_WRM(VTSS_AFI_MISC_CTRL,
            VTSS_F_AFI_MISC_CTRL_AFI_ENA(1),
            VTSS_M_AFI_MISC_CTRL_AFI_ENA);
    VTSS_RC(fa_afi_tti_cal_init(vtss_state));

    VTSS_I("Exit");

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_port_admin_start(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_afi_port_t *port = fa_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. port = %d, link = %d, started = %d", port_no, port->link, port->started);

    if (port->started) {
        VTSS_E("Port %u already started", port_no);
        return VTSS_RC_ERROR;
    }

    if (port->link) {
        VTSS_RC(fa_afi_port_start(vtss_state, port_no));
    }

    port->started = 1;

    VTSS_I("Exit. port = %d, link = %d, started = %d", port_no, port->link, port->started);

    return VTSS_RC_OK;
}

static vtss_rc fa_afi_port_admin_stop(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_afi_port_t *port = fa_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. port = %d, link = %d, started = %d", port_no, port->link, port->started);

    if (!port->started) {
        VTSS_E("Port %u not started", port_no);
        return VTSS_RC_ERROR;
    }

    // Stop all VD1 flows that utilize this port ingress-wise
    VTSS_RC(fa_afi_up_flows_pause_resume(vtss_state, port_no, TRUE));

    // Disable frame injection to this port.
    VTSS_RC(fa_afi_port_stop(vtss_state, port_no));
    port->started = 0;

    VTSS_I("Exit. port = %d, link = %d, started = %d", port_no, port->link, port->started);

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_afi_debug_print(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_AFI, fa_afi_debug, vtss_state, pr, info);
}

static vtss_rc fa_afi_init(vtss_state_t *vtss_state)
{
    u32 tick_base_len, val0, val1, idx, port;
    u64 t_ps[8], tick_base_ps;

    vtss_state->afi.clk_period_ps = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);

    // Find a suitable base tick, given that we want the first tick length to be VTSS_AFI_TTI_TICK_LEN0_US
    tick_base_len = VTSS_DIV64(VTSS_AFI_TTI_TICK_LEN0_US * 1000000LLU, vtss_state->afi.clk_period_ps);
    if (tick_base_len == 0 || tick_base_len > VTSS_M_AFI_TTI_TICK_BASE_BASE_LEN) {
        VTSS_E("Unable to find a suitable tick base given the first tick index request (%u us)", VTSS_AFI_TTI_TICK_LEN0_US);
        return VTSS_RC_ERROR;
    }

    REG_WRM(VTSS_AFI_TTI_TICK_BASE,
            VTSS_F_AFI_TTI_TICK_BASE_BASE_LEN(tick_base_len),
            VTSS_M_AFI_TTI_TICK_BASE_BASE_LEN);

    // Get true tick base without rounding errors.
    tick_base_ps = tick_base_len * vtss_state->afi.clk_period_ps;

    // Configure tick lengths (rounding is done when using these constants)
    val0 = (VTSS_F_AFI_TTI_TICK_LEN_0_3_LEN0(VTSS_DIV64(VTSS_AFI_TTI_TICK_LEN0_US * 1000000LLU, tick_base_ps)) |
            VTSS_F_AFI_TTI_TICK_LEN_0_3_LEN1(VTSS_AFI_TTI_TICK_LEN1_US / VTSS_AFI_TTI_TICK_LEN0_US) |
            VTSS_F_AFI_TTI_TICK_LEN_0_3_LEN2(VTSS_AFI_TTI_TICK_LEN2_US / VTSS_AFI_TTI_TICK_LEN1_US) |
            VTSS_F_AFI_TTI_TICK_LEN_0_3_LEN3(VTSS_AFI_TTI_TICK_LEN3_US / VTSS_AFI_TTI_TICK_LEN2_US));
    REG_WR(VTSS_AFI_TTI_TICK_LEN_0_3, val0);
    val1 = (VTSS_F_AFI_TTI_TICK_LEN_4_7_LEN4(VTSS_AFI_TTI_TICK_LEN4_US / VTSS_AFI_TTI_TICK_LEN3_US) |
            VTSS_F_AFI_TTI_TICK_LEN_4_7_LEN5(VTSS_AFI_TTI_TICK_LEN5_US / VTSS_AFI_TTI_TICK_LEN4_US) |
            VTSS_F_AFI_TTI_TICK_LEN_4_7_LEN6(VTSS_AFI_TTI_TICK_LEN6_US / VTSS_AFI_TTI_TICK_LEN5_US) |
            VTSS_F_AFI_TTI_TICK_LEN_4_7_LEN7(VTSS_AFI_TTI_TICK_LEN7_US / VTSS_AFI_TTI_TICK_LEN6_US));
    REG_WR(VTSS_AFI_TTI_TICK_LEN_4_7, val1);

    // In order to not accummulate rounding errors, first compute the
    // tick lengths in ps and then found them to microseconds.
    t_ps[0] = VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN0(val0) * tick_base_ps;
    t_ps[1] = VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN1(val0) * t_ps[0];
    t_ps[2] = VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN2(val0) * t_ps[1];
    t_ps[3] = VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN3(val0) * t_ps[2];
    t_ps[4] = VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN4(val1) * t_ps[3];
    t_ps[5] = VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN5(val1) * t_ps[4];
    t_ps[6] = VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN6(val1) * t_ps[5];
    t_ps[7] = VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN7(val1) * t_ps[6];

    for (idx = 0; idx < VTSS_ARRSZ(vtss_state->afi.tick_len_us); idx++) {
        vtss_state->afi.tick_len_us[idx] = VTSS_DIV64(t_ps[idx], 1000000LLU);
    }

    // On JR2C and later, a new bit, TIMER_ENA, was introduced with
    // a default value of 1 to be backward compatible. This has
    // the unfortunate side-effect that the very first frame of
    // a flow *may* come as the flow is started and the next frame
    // some random time after, so that the two frames aren't spaced
    // with the required amount of time.
    // To make sure that this very first frame isn't transmitted
    // by accident, we therefore disable all TTI timers during boot.
    for (idx = 0; idx < VTSS_ARRSZ(vtss_state->afi.tti_tbl); idx++) {
        REG_WRM(VTSS_AFI_TTI_TIMER(idx), VTSS_F_AFI_TTI_TIMER_TIMER_ENA(0), VTSS_M_AFI_TTI_TIMER_TIMER_ENA);
    }

    // Stop injection on all ports, corresponding to link == 0.
    // Will be started upon link up.
    for (port = 0; port < VTSS_CHIP_PORTS_ALL; port++) {
        VTSS_RC(fa_afi_chip_port_stop(vtss_state, port));
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_afi_init(vtss_state_t *vtss_state, const vtss_init_cmd_t cmd)
{
    vtss_afi_state_t *state = &vtss_state->afi;
    vtss_port_no_t   port_no;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        // Assign CIL function pointers
        state->afi_enable        = fa_afi_enable;
        state->ttis_enable       = fa_afi_ttis_enable;

        state->tti_start         = fa_afi_tti_start;
        state->tti_stop          = fa_afi_tti_stop;
        state->tti_frm_hijack    = fa_afi_tti_frm_hijack;
        state->tti_frm_rm_inj    = fa_afi_tti_frm_rm_inj;

        state->dti_start         = fa_afi_dti_start;
        state->dti_stop          = fa_afi_dti_stop;
        state->dti_frm_hijack    = fa_afi_dti_frm_hijack;
        state->dti_frm_rm_inj    = fa_afi_dti_frm_rm_inj;
        state->dti_cnt_get       = fa_afi_dti_cnt_get;

        state->port_admin_start  = fa_afi_port_admin_start;
        state->port_admin_stop   = fa_afi_port_admin_stop;
        state->link_state_change = fa_afi_link_state_change;
        state->qu_ref_update     = fa_afi_qu_ref_update;

        // Initialize ports to started = 1. This corresponds to
        // calling fa_afi_port_admin_start() during boot.
        for (port_no = 0; port_no < VTSS_ARRSZ(vtss_state->afi.port_tbl); port_no++) {
            vtss_state->afi.port_tbl[port_no].started = 1;
        }
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(fa_afi_init(vtss_state));
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        // Now that the port map is set, we can use "port_no".
        // VD1 always has "link up". It is indexed with port_no == VTSS_PORT_NO_NONE
        VTSS_RC(fa_afi_port_link_up(vtss_state, VTSS_PORT_NO_NONE));
        break;

    case VTSS_INIT_CMD_POLL:
        break;

    default:
        break;
    }

    return VTSS_RC_OK;
}

#endif /* defined(VTSS_AFI_V2) && defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_ARCH_FA) */

