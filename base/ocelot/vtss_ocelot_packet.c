// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_ocelot_cil.h"

// Avoid Lint Warning 572: Excessive shift value (precision 1 shifted right by 2), which occurs
// in this file because (t) - VTSS_IO_ORIGIN1_OFFSET == 0 for t = VTSS_TO_CFG (i.e. ICPU_CFG), and 0 >> 2 gives a lint warning.
/*lint --e{572} */
#if defined(VTSS_ARCH_OCELOT)

/* - CIL functions ------------------------------------------------- */

#if defined(VTSS_FEATURE_AFI_SWC)
/* ================================================================= *
 *  AFI - Automatic Frame Injector
 * ================================================================= */

#define VTSS_QSYS_TIMER_UNIT_PS 198400LLU        /* Timer base period in picoseconds */
#define VTSS_PS_PER_SEC         1000000000000LLU /* Picoseconds per second */
#define VTSS_AFI_SLOT_DIVIDER   16               /* Where to place the slot divider (TIMED_ENTRY_FAST_CNT) */
#define VTSS_AFI_SLOTS_PER_CC   8                /* Number of slots visited in one clock cycle */

// Unfortunately, the AFI timers aren't defined as a replication (due to distinct defaults),
// so we have to define our own address.
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG(x) VTSS_IOREG(VTSS_TO_QSYS, 0x44c6 + (x))

/**
 * srvl_afi_chip_port_to_str()
 */
static char *srvl_afi_chip_port_to_str(vtss_state_t *vtss_state, vtss_phys_port_no_t chip_port, char *buf)
{
    vtss_port_no_t port_no;

    switch (chip_port) {
    case (vtss_phys_port_no_t)-1:
       // Special case just to get the print function print something special
       VTSS_STRCPY(buf, "SHARED");
       break;

    case VTSS_CHIP_PORT_CPU:
       VTSS_STRCPY(buf, "CPU");
       break;

    default:
        port_no = vtss_cmn_chip_to_logical_port(vtss_state, vtss_state->chip_no, chip_port);
        if (port_no != VTSS_PORT_NO_NONE) {
            VTSS_SPRINTF(buf, "%u", port_no);
        } else {
            // Port is not in port map. Odd.
            VTSS_E("chip_port = %u not in port map", chip_port);
            VTSS_STRCPY(buf, "N/A");
        }

        break;
    }

    return buf;
}

/**
 * srvl_afi_qsys_resource_to_str()
 */
static const char *srvl_afi_qsys_resource_to_str(u32 resource)
{
    switch (resource) {
    case 0:
        return "SRC-MEM";

    case 1:
        return "SRC-REF";

    case 2:
        return "DST-MEM";

    case 3:
        return "DST-REF";

    default:
        VTSS_E("Invalid resource (%u)", resource);
        break;
    }

    return "INVALID";
}

/**
 * srvl_afi_debug_qres_print()
 */
static void srvl_afi_debug_qres_print(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 idx, vtss_phys_port_no_t chip_port, u32 resource, u32 prio, u32 inuse, u32 maxuse)
{
    char buf[20];

    pr("%4u %-8s %7s %9d %4u %5u %6u\n", idx, srvl_afi_qsys_resource_to_str(resource), srvl_afi_chip_port_to_str(vtss_state, chip_port, buf), chip_port, prio, inuse, maxuse);
}

/**
 * srvl_afi_debug_qres()
 */
static vtss_rc srvl_afi_debug_qres(vtss_state_t *vtss_state, const vtss_debug_printf_t pr)
{
    vtss_phys_port_no_t chip_port;
    u32                 resource, resource_base, port_base, idx, prio, val, inuse, addr;

    pr("\nQSYS Resource table (QSYS:RES_CTRL[idx]:RES_STAT)\n");
    pr("Idx  Resource Port No Chip Port Prio INUSE MAXUSE\n");
    pr("---- -------- ------- --------- ---- ----- ------\n");

    addr = VTSS_QSYS_RES_CTRL_RES_STAT(255);
    SRVL_RD(addr, &val);
    srvl_afi_debug_qres_print(vtss_state, pr, 255, (vtss_phys_port_no_t)-1, 0, 7, VTSS_X_QSYS_RES_CTRL_RES_STAT_INUSE(val), VTSS_X_QSYS_RES_CTRL_RES_STAT_MAXUSE(val));

    for (resource = 0; resource < 4; resource++) {
        resource_base = resource * 256;
        for (chip_port = 0; chip_port <= VTSS_CHIP_PORT_CPU; chip_port++) {
            port_base = resource_base + chip_port * VTSS_PRIOS;
            for (prio = 0; prio < VTSS_PRIOS; prio++) {
                idx = port_base + prio;
                addr = VTSS_QSYS_RES_CTRL_RES_STAT(idx);
                SRVL_RD(addr, &val);
                inuse  = VTSS_X_QSYS_RES_CTRL_RES_STAT_INUSE(val);
                if (inuse) {
                    // Only print non-zero values or we will be flooded.
                    srvl_afi_debug_qres_print(vtss_state, pr, idx, chip_port, resource, prio, inuse, VTSS_X_QSYS_RES_CTRL_RES_STAT_MAXUSE(val)
);
                }
            }
        }
    }

    pr("\n");

    return VTSS_RC_OK;
}

/*
 * srvl_afi_cancel()
 * Cancels a frame by writing to the AFI.
 */
static vtss_rc srvl_afi_cancel(vtss_state_t *vtss_state, vtss_afi_id_t afi_id)
{
    u32           val, cnt = 0;
    vtss_mtimer_t timer;
    vtss_rc       rc = VTSS_RC_OK;

    // Before cancelling this frame, make sure it indeed is known by the AFI H/W
    SRVL_RD(VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY(afi_id), &val);
    if ((val & VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_VLD) == 0) {
        VTSS_IG(VTSS_TRACE_GROUP_AFI, "Cancelling a frame (ID = %u) that is not in H/W", afi_id);
        return VTSS_RC_OK;
    }

    // Do cancel frame
    SRVL_WRM(VTSS_QSYS_TIMED_FRAME_CFG_TFRM_MISC,
             VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_SLOT(afi_id) | VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_1SHOT,
             VTSS_M_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_SLOT         | VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_1SHOT);

    VTSS_MTIMER_START(&timer, 2000);

    // Wait for the one-shot bit to clear.
    while (1) {
        cnt++;
        SRVL_RD(VTSS_QSYS_TIMED_FRAME_CFG_TFRM_MISC, &val);
        if ((val & VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_1SHOT) == 0) {
            goto do_exit;
        }

        if (VTSS_MTIMER_TIMEOUT(&timer)) {
            VTSS_EG(VTSS_TRACE_GROUP_AFI, "Timeout waiting for cancelling of frame (afi_id = %u)", afi_id);
            rc = VTSS_RC_ERROR;
            goto do_exit;
        }
    }

do_exit:
    VTSS_MTIMER_CANCEL(&timer);
    VTSS_IG(VTSS_TRACE_GROUP_AFI, "Reads = %u", cnt);

    return rc;
}

/*
 * srvl_afi_link_state_change()
 * Called internally on link-up/down events to resume/pause AFI frames.
 */
static vtss_rc srvl_afi_link_state_change(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL *link_up)
{
    vtss_afi_id_t afi_id;
    BOOL          resume = *link_up;

    VTSS_IG(VTSS_TRACE_GROUP_AFI, "Link %s event on iport %u", *link_up ? "up" : "down", port_no);

    // Gotta return the current link state in #link_up, which is an INOUT.
    if (port_no < VTSS_PORTS) {
        *link_up = vtss_state->afi.link[port_no];
        vtss_state->afi.link[port_no] = resume;
    } else {
        *link_up = FALSE;
    }

    if (resume) {
        // Resuming of paused AFI flows requires intervention by the
        // application, which will have to re-inject the frame using the AFI ID
        // originally obtained with a call to vtss_afi_alloc().
        // So here, we just return VTSS_RC_OK to keep the caller happy.
        return VTSS_RC_OK;
    }

    // Search through all AFI slots to see if we send frames to #port_no
    // through this slot.
    for (afi_id = 0; afi_id < VTSS_ARRSZ(vtss_state->afi.slots); afi_id++) {
        vtss_afi_slot_conf_t *slot_conf = &vtss_state->afi.slots[afi_id];

        if (!resume && slot_conf->state == VTSS_AFI_SLOT_STATE_ENABLED && slot_conf->port_no == port_no) {
            // Pausing an enabled frame. This will remove the frame from the switch core, but keep the software state.
            slot_conf->state = VTSS_AFI_SLOT_STATE_PAUSED;

            VTSS_IG(VTSS_TRACE_GROUP_AFI, "iport = %u: Cancelling (pausing) afi_id = %u", port_no, afi_id);
            VTSS_RC(srvl_afi_cancel(vtss_state, afi_id));
        }
    }

    return VTSS_RC_OK;
}

/*
 * srvl_afi_alloc()
 * Attempts to find a suitable AFI timer and AFI slot for a given frame to be
 * periodically injected.
 */
static vtss_rc srvl_afi_alloc(vtss_state_t *vtss_state, vtss_afi_frm_dscr_t *const dscr, vtss_afi_id_t *const afi_id)
{
    u32                   timer, slot, min_slot, max_slot, val;
    vtss_afi_timer_conf_t *timer_conf;
    vtss_afi_slot_conf_t  *slot_conf;

#if VTSS_OPT_AFI_OPTIMIZE_FOR_TIMERS
    u32                   sub_slot, attempt, attempt_min;
    BOOL                  found = FALSE;

    // When optimizing for timers, all timer values are preconfigured,
    // and we will probably need to be invoked more times than if
    // we optimized for AFI slots.

    // The pre-configured timers are configured in descending FPS-order.
    // Find the lowest numbered timer whose fps is at or below the requested fps.
    for (timer = 0; timer < VTSS_ARRSZ(vtss_state->afi.timers); timer++) {
        u32 timer_fps = vtss_state->afi.timers[timer].fps;
        if (timer_fps <= dscr->fps) {
            dscr->actual_fps = timer_fps;
            break;
        }
    }

    if (timer == VTSS_ARRSZ(vtss_state->afi.timers)) {
        // The smallest possible rate was not small enough
        // for the request.
        VTSS_EG(VTSS_TRACE_GROUP_AFI, "Requested %u fps, but couldn't go slower than %u fps", dscr->fps, vtss_state->afi.timers[VTSS_ARRSZ(vtss_state->afi.timers) - 1].fps);
        return VTSS_RC_ERROR;
    }

    // Find a free slot. In H/W, the AFI loads 8 (VTSS_AFI_SLOTS_PER_CC) slots
    // per clock cycle and looks to see - in these 8 slots - if a frame is ready
    // to be transmitted again. If so, it checks to see if the destination port
    // is ready to accept frames, and if so, it transmits the frame. If not, the
    // AFI continues with the next 8 slots - with the wringle that in even clock
    // cycles, it checks for "fast frames" and in odd clock cycles, it checks
    // for "slow frames". The delimiter between fast and slow frames is
    // controlled through a debug field called
    // QSYS:TIMED_FRAME_CFG:TFRM_MISC.TIMED_ENTRY_FAST_CNT. This register has
    // granularity of VTSS_AFI_SLOTS_PER_CC slots and is by default 2, which
    // means that the first 16 slots are fully checked for new frames every four
    // clock cycles (it takes two iterations and it's only in even clock cycles
    // the fast slots are checked).
    // To make a long story short, since the H/W checks 8 consecutive slots per
    // clock cycle, it's better to space all frames by 8 slots and since every
    // other clock cycle is spent in each section delimited by the above-
    // mentioned field, we must place the delimiter such that there is room for
    // the fastest flows (those pointed to by timers[0]) - preferably spaced
    // 8 slots. timers[0] is able to provide roughly 240000 fps, and to fill a
    // 2.5Gbps port (worst case 64 byte frames), we need
    //   2.5E9 bps / (64 bytes + 20 IFG) / 8 bits/byte / 240000 fps = 15.5
    // fast slots. To get them out on the same port, they must be spaced 8 slots
    // apart, so we need to place the divider at slot 15 * 8. For simplicity, we
    // set it at 16 * 8 (so that the value to write into TIMED_ENTRY_FAST_CNT is
    // 16, which is what VTSS_AFI_SLOT_DIVIDER is set to.

    // We allocate the fast section for timer 0 and 1. If we can't find an
    // available slot there, use the slow section. In principle, we should have
    // had the port number to judge where to place the flow.
    attempt_min = timer < 2 ? 0 : 1;
    for (attempt = attempt_min; attempt < 2; attempt++) {
        if (attempt == 0) {
            // Use fast section
            min_slot = 0;
            max_slot = VTSS_AFI_SLOT_DIVIDER * VTSS_AFI_SLOTS_PER_CC - 1;
        } else {
            // Use slow section
            min_slot = VTSS_AFI_SLOT_DIVIDER * VTSS_AFI_SLOTS_PER_CC;
            max_slot = VTSS_ARRSZ(vtss_state->afi.slots) - 1;
        }

        // Now make two loops where the inner increments 8 slots
        // per time and the outer runs from 0 to 8, so that we
        // only use two or more slots within the same 8-slot department
        // when absolutely necessary.
        for (sub_slot = 0; sub_slot < 8; sub_slot++) {
            for (slot = min_slot + sub_slot; slot <= max_slot; slot += 8) {
                if (vtss_state->afi.slots[slot].state == VTSS_AFI_SLOT_STATE_FREE) {
                    // Also check that H/W doesn't have a frame now that it isn't
                    // supposed to have (can happen if the egress port is
                    // oversubscribed and the user hasn't called the hijack
                    // function).
                    SRVL_RD(VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY(slot), &val);
                    if ((val & VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_VLD) != 0) {
                        VTSS_IG(VTSS_TRACE_GROUP_AFI, "Cancelling an unknown frame in slot %u", slot);
                        VTSS_RC(srvl_afi_cancel(vtss_state, slot));
                    }

                    found = TRUE;
                    break;
                }
            }

            if (found) {
                break;
            }
        }

        if (found) {
            break;
        }

        if (!found && attempt == 1) {
            // Out of slots.
            VTSS_EG(VTSS_TRACE_GROUP_AFI, "Unable to find a usable AFI slot (fps = %u)", dscr->actual_fps);
            return VTSS_RC_ERROR;
        }
    }

    timer_conf = &vtss_state->afi.timers[timer];
    slot_conf  = &vtss_state->afi.slots[slot];

    // Update the S/W state
    timer_conf->ref_cnt++;
    slot_conf->timer_idx = timer;
    slot_conf->state     = VTSS_AFI_SLOT_STATE_RESERVED; // Only reserved. We don't know the destination port yet.
    vtss_state->afi.fps_per_section[min_slot == 0 ? 0 : 1] += dscr->actual_fps;

    *afi_id = slot;
    return VTSS_RC_OK;
#else
    u64 ticks;

    // Figure out the closest, smaller fps that we can obtain with the AFI at hand.
    ticks = VTSS_DIV64(VTSS_PS_PER_SEC, ((u64)dscr->fps * VTSS_QSYS_TIMER_UNIT_PS));
    if (ticks == 0) {
        VTSS_EG(VTSS_TRACE_GROUP_AFI, "Got ticks == 0 with fps == %u", dscr->fps);
        return VTSS_RC_ERROR;
    }

    dscr->actual_fps = VTSS_DIV64(VTSS_PS_PER_SEC, (ticks * VTSS_QSYS_TIMER_UNIT_PS));

    // Since we are truncating in the ticks computation, ticks will always be <= than had
    // we used floating point. This means that dscr->actual_fps will always be >= dscr->fps.
    if (dscr->actual_fps < dscr->fps) {
        VTSS_EG(VTSS_TRACE_GROUP_AFI, "Error: Assumption didn't hold %u/%u\n", dscr->actual_fps, dscr->fps);
        return VTSS_RC_ERROR;
    }

    if (dscr->actual_fps > dscr->fps) {
        // Try with a higher tick count, which will give a lower rate.
        // We have promised (see public signature for dscr) that the actual
        // fps will be less than or equal to the desired fps.
        ticks++;
        dscr->actual_fps = VTSS_DIV64(VTSS_PS_PER_SEC, (ticks * VTSS_QSYS_TIMER_UNIT_PS));
    }

    if (ticks <= 0 || ticks > 0xFFFFFFFFULL) {
        VTSS_EG(VTSS_TRACE_GROUP_AFI, "Unable to fulfil user request for fps = %u", dscr->fps);
        return VTSS_RC_ERROR;
    }

    // If we get here, the user wants to add a new flow. Find a suitable timer.
    for (timer = 0; timer < VTSS_ARRSZ(vtss_state->afi.timers); timer++) {
        // First see if we can reuse one that is already in use.
        timer_conf = &vtss_state->afi.timers[timer];

        if (timer_conf->ref_cnt > 0 && timer_conf->fps == dscr->actual_fps)  {
            // Found a suitable timer.
            break;
        }
    }

    if (timer == VTSS_ARRSZ(vtss_state->afi.timers)) {
        // Didn't find a suitable already-configured timer. See if there are any free timers.
        for (timer = 0; timer < VTSS_ARRSZ(vtss_state->afi.timers); timer++) {

            if (vtss_state->afi.timers[timer].ref_cnt == 0)  {
                // Found a suitable timer
                break;
            }
        }
    }

    if (timer == VTSS_ARRSZ(vtss_state->afi.timers)) {
        // No free timers.
        VTSS_EG(VTSS_TRACE_GROUP_AFI, "Unable to find a usable AFI timer (fps = %u)", dscr->actual_fps);
        return VTSS_RC_ERROR;
    }

    // Find a free slot. The first 16 slots are reserved for frames faster than 60 us.
    if (dscr->actual_fps > 16666) {
        min_slot = 0;
        max_slot = 15;
    } else {
        min_slot = 16;
        max_slot = VTSS_ARRSZ(vtss_state->afi.slots) - 1;
    }

    for (slot = min_slot; slot <= max_slot; slot++) {
        if (vtss_state->afi.slots[slot].state == VTSS_AFI_SLOT_STATE_FREE) {
            // Also check that H/W doesn't have a frame now that it isn't
            // supposed to have (can happen if the egress port is oversubscribed
            // and the user hasn't called the hijack function).
            SRVL_RD(VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY(slot), &val);
            if ((val & VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_VLD) != 0) {
                VTSS_IG(VTSS_TRACE_GROUP_AFI, "Cancelling an unknown frame in slot %u", slot);
                VTSS_RC(srvl_afi_cancel(vtss_state, slot));
            }

            break;
        }
    }

    if (slot == max_slot + 1) {
        // Out of slots.
        VTSS_EG(VTSS_TRACE_GROUP_AFI, "Unable to find a usable AFI slot (fps = %u)", dscr->actual_fps);
        return VTSS_RC_ERROR;
    }

    timer_conf = &vtss_state->afi.timers[timer];
    slot_conf  = &vtss_state->afi.slots[slot];

    // If we get here, we both have a valid timer and a valid slot.
    if (timer_conf->ref_cnt == 0) {
        SRVL_WR(VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG(timer), ticks);
    }

    // Update the S/W state
    timer_conf->ref_cnt++;
    timer_conf->fps      = dscr->actual_fps;
    slot_conf->timer_idx = timer;
    slot_conf->state     = VTSS_AFI_SLOT_STATE_RESERVED; // Only reserved. We don't know the destination port yet.

    *afi_id = slot;
    return VTSS_RC_OK;
#endif
}

/*
 * srvl_afi_free()
 * Cancels a periodically injected frame and frees up the
 * resources allocated for it.
 */
static vtss_rc srvl_afi_free(vtss_state_t *vtss_state, vtss_afi_id_t afi_id)
{
    vtss_afi_slot_conf_t *slot_conf;

    if (afi_id >= VTSS_ARRSZ(vtss_state->afi.slots)) {
        VTSS_EG(VTSS_TRACE_GROUP_AFI, "Invalid AFI ID (%u)", afi_id);
        return VTSS_RC_ERROR;
    }

    slot_conf = &vtss_state->afi.slots[afi_id];

    if (slot_conf->state != VTSS_AFI_SLOT_STATE_FREE) {

        // Ask the switch core to stop it. It doesn't harm to stop
        // a slot that is just reserved and not active.
        VTSS_IG(VTSS_TRACE_GROUP_AFI, "Freeing afi_id = %u on port_no = %u", afi_id, slot_conf->port_no);
        VTSS_RC(srvl_afi_cancel(vtss_state, afi_id));

        slot_conf->state = VTSS_AFI_SLOT_STATE_FREE;

        // One less frame referencing this timer.
        vtss_state->afi.timers[slot_conf->timer_idx].ref_cnt--;

#if VTSS_OPT_AFI_OPTIMIZE_FOR_TIMERS
        {
            u32 timer_fps = vtss_state->afi.timers[slot_conf->timer_idx].fps;
            u32 section = afi_id >= VTSS_AFI_SLOT_DIVIDER * VTSS_AFI_SLOTS_PER_CC ? 1 : 0;
            if (vtss_state->afi.fps_per_section[section] < timer_fps) {
                VTSS_EG(VTSS_TRACE_GROUP_AFI, "AFI ID = %u: Error updating section info. afi.fps_per_section[0, 1] = %u, %u. Timer = %u. FPS = %u", afi_id, vtss_state->afi.fps_per_section[0], vtss_state->afi.fps_per_section[1], slot_conf->timer_idx, timer_fps);
                return VTSS_RC_ERROR;
            }

            vtss_state->afi.fps_per_section[section] -= timer_fps;
        }
#endif
    }

    return VTSS_RC_OK;
}

/*
 * srvl_afi_hijack()
 */
static vtss_rc srvl_afi_hijack(vtss_state_t *vtss_state, vtss_afi_id_t afi_id)
{
    vtss_afi_slot_conf_t *slot_conf;
    vtss_mtimer_t        timer;
    int                  t;
    u32                  timer_val[4] = {0}, cnt = 0, val;
    vtss_rc              rc = VTSS_RC_OK;

    if (afi_id >= VTSS_ARRSZ(vtss_state->afi.slots)) {
        VTSS_EG(VTSS_TRACE_GROUP_AFI, "Invalid AFI ID (%u)", afi_id);
        return VTSS_RC_ERROR;
    }

    slot_conf = &vtss_state->afi.slots[afi_id];

    if (slot_conf->state != VTSS_AFI_SLOT_STATE_ENABLED) {
        // This may happen due to a race condition, where the frame gets
        // cancelled, e.g. by a link-down, before this function is invoked, so
        // not a real error, hence the use of VTSS_IG() rather than VTSS_EG()
        // and return of VTSS_RC_OK rather than VTSS_RC_ERROR.
        VTSS_IG(VTSS_TRACE_GROUP_AFI, "Frame with AFI ID %u has not been sent towards the AFI", afi_id);
        return VTSS_RC_OK;
    }

    // Wait for the frame to hit this slot in H/W.
    // While we do this, we make the fastest timers very slow in order to allow
    // the frame to get out of the QSYS and into the AFI H/W.

    // Make the fastest timers very slow
    for (t = 0; t < VTSS_ARRSZ(timer_val); t++) {
        SRVL_RD(VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG(t), &timer_val[t]);
        SRVL_WR(VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG(t), 0xFFFFFFFF);
    }

    VTSS_MTIMER_START(&timer, 2000);

    while (1) {
        cnt++;
        SRVL_RD(VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY(afi_id), &val);
        if ((val & VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_VLD) != 0) {
            // Hijacked.
            goto do_exit;
        }

        if (VTSS_MTIMER_TIMEOUT(&timer)) {
            VTSS_EG(VTSS_TRACE_GROUP_AFI, "Timeout waiting for frame to hit the AFI (afi_id = %u). Reads so far = %u", afi_id, cnt);
            rc = VTSS_RC_ERROR;
            goto do_exit;
        }
    }

do_exit:
    // Set the timers back to what they were.
    for (t = 0; t < VTSS_ARRSZ(timer_val); t++) {
        SRVL_WR(VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG(t), timer_val[t]);
    }

    VTSS_MTIMER_CANCEL(&timer);
    VTSS_IG(VTSS_TRACE_GROUP_AFI, "Reads = %u", cnt);

    return rc;
}

/*
 * srvl_afi_init()
 */
static vtss_rc srvl_afi_init(vtss_state_t *vtss_state)
{
#if VTSS_OPT_AFI_OPTIMIZE_FOR_TIMERS
    u64 ticks;
    u32 timer;

    // Some of the timer settings are found empirically.
    vtss_state->afi.timers[0].fps = 250000;
    vtss_state->afi.timers[1].fps = 100000;
    vtss_state->afi.timers[2].fps =  30000;
    vtss_state->afi.timers[3].fps =   3000;
    vtss_state->afi.timers[4].fps =    300; // Want to support 3.33 ms CCM with a single frame flow to space frames evenly
    vtss_state->afi.timers[5].fps =    100; // Ditto with 10 ms CCM
    vtss_state->afi.timers[6].fps =     10; // Ditto with 100 ms CCM
    vtss_state->afi.timers[7].fps =      1; // If writing anything but 1 here, 1 FPS would not be achievable...

    // Configure the timers.
    for (timer = 0; timer < VTSS_ARRSZ(vtss_state->afi.timers); timer++) {
        ticks = VTSS_DIV64(VTSS_PS_PER_SEC, ((u64)vtss_state->afi.timers[timer].fps * VTSS_QSYS_TIMER_UNIT_PS)) + 1;
        SRVL_WR(VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG(timer), ticks);

        // Update our state with the actually achieved rate
        vtss_state->afi.timers[timer].fps = VTSS_DIV_ROUND_UP(VTSS_PS_PER_SEC, ticks * VTSS_QSYS_TIMER_UNIT_PS);
    }

    // In srvl_afi_alloc(), there's a long story that tells how the slots are
    // used, and why the following register needs to be set to
    // VTSS_AFI_SLOT_DIVIDER.
    // Unfortunately, it's a debug register, so we publish it here.
#define  VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_ENTRY_FAST_CNT(x) VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_ENTRY_FAST_CNT    VTSS_ENCODE_BITMASK(0,7)
    SRVL_WRM(VTSS_QSYS_TIMED_FRAME_CFG_TFRM_MISC,
             VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_ENTRY_FAST_CNT(VTSS_AFI_SLOT_DIVIDER),
             VTSS_M_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_ENTRY_FAST_CNT);
#endif /* VTSS_OPT_AFI_OPTIMIZE_FOR_TIMERS */

    return VTSS_RC_OK;
}

#undef VTSS_QSYS_TIMER_UNIT_PS
#undef VTSS_PS_PER_SEC
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

/* ================================================================= *
 *  NPI
 * ================================================================= */

static vtss_rc srvl_npi_mask_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t *conf = &vtss_state->packet.rx_conf;
    vtss_port_no_t        port_no = vtss_state->packet.npi_conf.port_no;
    u32                   val = 0, qmask, i;

    if (port_no != VTSS_PORT_NO_NONE) {
        for (qmask = i = 0; i < vtss_state->packet.rx_queue_count; i++) {
            if (conf->queue[i].npi.enable) {
                qmask |= VTSS_BIT(i); /* NPI redirect */
            }
        }
        val = VTSS_F_QSYS_SYSTEM_EXT_CPU_CFG_EXT_CPU_PORT(VTSS_CHIP_PORT(port_no)) |
            VTSS_F_QSYS_SYSTEM_EXT_CPU_CFG_EXT_CPUQ_MSK(qmask);
    }
    SRVL_WR(VTSS_QSYS_SYSTEM_EXT_CPU_CFG, val);

    return VTSS_RC_OK;
}

static vtss_rc srvl_npi_update(vtss_state_t *vtss_state)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;

    VTSS_RC(srvl_npi_mask_set(vtss_state));

    if (conf->port_no != VTSS_PORT_NO_NONE) {
        u32 value, port = VTSS_CHIP_PORT(conf->port_no);

        /* Control IFH insertion and  parsing */
        value = (conf->enable ?
                 VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR(3) | VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR(3) : 0);
        SRVL_WRM(VTSS_SYS_SYSTEM_PORT_MODE(port), value,
                 VTSS_M_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR | VTSS_M_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR);
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_npi_conf_set(vtss_state_t *vtss_state, const vtss_npi_conf_t *const new)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;

    /* Disable current NPI port */
    conf->enable = FALSE;
    VTSS_RC(srvl_npi_update(vtss_state));

    /* Set new NPI port */
    *conf = *new;
    VTSS_RC(srvl_npi_update(vtss_state));

    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc srvl_packet_phy_cnt_to_ts_cnt(vtss_state_t *vtss_state, u32 phy_cnt, u64 *ts_cnt)
{
    VTSS_I("Not supported in this architecture");
    *ts_cnt = 0;

    return VTSS_RC_OK;
}

static vtss_rc srvl_packet_ns_to_ts_cnt(vtss_state_t  *vtss_state,
                                        u32            ns,
                                        u64            *ts_cnt)
{
    vtss_timestamp_t ts;
    u32              tc;
    u64              tc_64;

    if (ns >= VTSS_ONE_MIA) {
       VTSS_I("Invalid ns value (%d)", ns);
    }
    _vtss_ts_domain_timeofday_get(NULL, 0, &ts, &tc_64);
    tc = tc_64 >> 16;       /* The tc_64 returned by _vtss_ts_domain_timeofday_get() is in 16 bit fractions of nanoseconds */
    if (ts.nanoseconds < ns) { // ns has wrapped
        ts.nanoseconds += VTSS_ONE_MIA;
    }
    tc = tc - ((ts.nanoseconds - ns) / VTSS_HW_TIME_NSEC_PR_CNT);
    *ts_cnt = (u64)tc << 16;  /* Must return in 16 bit fractions of nanoseconds */

    return VTSS_RC_OK;
}

static u32 srvl_packet_unpack32(const u8 *buf)
{
    return (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + buf[3];
}

static vtss_rc srvl_ptp_get_timestamp(vtss_state_t                    *vtss_state,
                                      const u8                        *const frm,
                                      const vtss_packet_rx_info_t     *const rx_info,
                                      vtss_packet_ptp_message_type_t  message_type,
                                      vtss_packet_timestamp_props_t   ts_props,
                                      u64                             *rxTime,
                                      BOOL                            *timestamp_ok)
{
    vtss_ts_id_t ts_id;
    *rxTime = rx_info->hw_tstamp;
    *timestamp_ok = rx_info->hw_tstamp_decoded;
    if (ts_props.ts_feature_is_PTS || ts_props.backplane_port) {
        u32 packet_ns;
        packet_ns = srvl_packet_unpack32(frm);
        if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_30BIT) {
            /* convert to 32 bit timestamp */
            VTSS_D("rxTime before %u", packet_ns);
            (void)srvl_packet_ns_to_ts_cnt(vtss_state, packet_ns, rxTime);
            VTSS_D("rxTime after %" PRIu64 "", *rxTime);
        } else if (ts_props.phy_ts_mode != VTSS_PACKET_INTERNAL_TC_MODE_32BIT) {
            VTSS_I("PHY timestamp mode %d not supported", ts_props.phy_ts_mode);
        }
    }
    VTSS_D("Raw timestamp %" PRIu64 ", hw_tstamp_decoded %u", *rxTime, *timestamp_ok);
    ts_id.ts_id = rx_info->tstamp_id;
    if (rx_info->tstamp_id_decoded) {
        (void)_vtss_rx_timestamp_id_release(0,&ts_id);
        VTSS_D("Timestamp %" PRIu64 ", ts decoded %d, Ts id %d", *rxTime, rx_info->tstamp_id_decoded, ts_id.ts_id);
    }
    return VTSS_RC_OK;
}

static u32 srvl_cpu_fwd_mask_get(vtss_packet_reg_type_t type, BOOL redir, u32 i)
{
    u32 mask;

    /* Map NORMAL to CPU_ONLY/FORWARD */
    if (type == VTSS_PACKET_REG_NORMAL) {
        type = (redir ? VTSS_PACKET_REG_CPU_ONLY : VTSS_PACKET_REG_FORWARD);
    }

    if (type == VTSS_PACKET_REG_CPU_ONLY) {
         /* Set REDIR bit */
        mask = VTSS_BIT(i);
    } else if (type == VTSS_PACKET_REG_DISCARD) {
        /* Set DROP bit */
        mask = VTSS_BIT(i + 16);
    } else if (type == VTSS_PACKET_REG_CPU_COPY) {
        /* Set REDIR and DROP bits */
        mask = (VTSS_BIT(i) | VTSS_BIT(i + 16));
    } else {
        /* No bits set for VTSS_PACKET_REG_FORWARD */
        mask = 0;
    }
    return mask;
}

static vtss_rc srvl_rx_conf_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t      *conf = &vtss_state->packet.rx_conf;
    vtss_packet_rx_reg_t       *reg = &conf->reg;
    vtss_packet_rx_queue_map_t *map = &conf->map;
    u32                        queue, i, value, port, bpdu, garp;
    vtss_port_no_t             port_no;
    vtss_packet_rx_port_conf_t *port_conf;

    /* Each CPU queue gets reserved extraction buffer space. No sharing at port or buffer level */
    for (queue = 0; queue < vtss_state->packet.rx_queue_count; queue++) {
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(512 /* egress */ + VTSS_CHIP_PORT_CPU * VTSS_PRIOS + queue), conf->queue[queue].size / SRVL_BUFFER_CELL_SZ);
    }
    SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(512 /* egress */ + 224 /* per-port reservation */ + VTSS_CHIP_PORT_CPU), 0); /* No extra shared space at port level */

    /* Rx IPMC, BPDU and GARP registrations */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        port_conf = &vtss_state->packet.rx_port_conf[port_no];
        SRVL_WRM(VTSS_ANA_PORT_CPU_FWD_CFG(port),
                 ((port_conf->ipmc_ctrl_reg == VTSS_PACKET_REG_NORMAL && reg->ipmc_ctrl_cpu_copy) ||
                  port_conf->ipmc_ctrl_reg == VTSS_PACKET_REG_CPU_COPY ?
                  VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_IPMC_CTRL_COPY_ENA : 0) |
                 ((port_conf->igmp_reg == VTSS_PACKET_REG_NORMAL && reg->igmp_cpu_only) ||
                  port_conf->igmp_reg == VTSS_PACKET_REG_CPU_ONLY ?
                  VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_IGMP_REDIR_ENA : 0) |
                 ((port_conf->mld_reg == VTSS_PACKET_REG_NORMAL && reg->mld_cpu_only) ||
                  port_conf->mld_reg == VTSS_PACKET_REG_CPU_ONLY ?
                  VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_MLD_REDIR_ENA : 0),
                 VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_IPMC_CTRL_COPY_ENA |
                 VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_IGMP_REDIR_ENA |
                 VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_MLD_REDIR_ENA);
        for (i = 0, bpdu = 0, garp = 0; i < 16; i++) {
            bpdu |= srvl_cpu_fwd_mask_get(port_conf->bpdu_reg[i], reg->bpdu_cpu_only, i);
            garp |= srvl_cpu_fwd_mask_get(port_conf->garp_reg[i], reg->garp_cpu_only[i], i);
        }
        SRVL_WR(VTSS_ANA_PORT_CPU_FWD_BPDU_CFG(port), bpdu);
        SRVL_WR(VTSS_ANA_PORT_CPU_FWD_GARP_CFG(port), garp);
    }

    /* Fixme - chipset has more queues of classification the API expose */
    value =
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_SFLOW(map->sflow_queue != VTSS_PACKET_RX_QUEUE_NONE ? map->sflow_queue - VTSS_PACKET_RX_QUEUE_START : VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MIRROR(map->mac_vid_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_LRN(map->learn_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MAC_COPY(map->mac_vid_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_SRC_COPY(map->mac_vid_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE(map->mac_vid_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_ALLBRIDGE(map->bpdu_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_IPMC_CTRL(map->ipmc_ctrl_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_IGMP(map->igmp_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MLD(map->igmp_queue-VTSS_PACKET_RX_QUEUE_START);
    SRVL_WR(VTSS_ANA_COMMON_CPUQ_CFG, value);

    /* Setup each of the BPDU, GARP and CCM 'address' extraction queues */
    for (i = 0; i < 16; i++) {
        value =
            VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_BPDU_VAL(map->bpdu_queue-VTSS_PACKET_RX_QUEUE_START) |
            VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_GARP_VAL(map->garp_queue-VTSS_PACKET_RX_QUEUE_START) |
            VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_CCM_VAL(VTSS_PACKET_RX_QUEUE_START); /* Fixme */
        SRVL_WR(VTSS_ANA_COMMON_CPUQ_8021_CFG(i), value);
    }

    /* Configure Rx Queue #i to map to an Rx group. */
    for (i = 0; i < vtss_state->packet.rx_queue_count; i++) {
        if (conf->grp_map[i]) {
            VTSS_E("Attempt to redirect queue %d - use vtss_dma_conf_set instead()", i);
        }
    }

    VTSS_RC(srvl_npi_mask_set(vtss_state));

    return VTSS_RC_OK;
}

static vtss_rc srvl_packet_mode_update(vtss_state_t *vtss_state)
{
    u32 byte_swap;
#ifdef VTSS_OS_BIG_ENDIAN
    byte_swap = 0;
#else
    byte_swap = 1;
#endif

    if (!vtss_state->packet.manual_mode) {
        /* Change mode to manual extraction and injection */
        vtss_state->packet.manual_mode = 1;
        SRVL_WR(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(0),
                VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE(1) |
                (byte_swap ? VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP : 0));
        SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(0),
                VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE(1) |
                (byte_swap ? VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_BYTE_SWAP : 0));
        SRVL_WR(VTSS_SYS_SYSTEM_PORT_MODE(VTSS_CHIP_PORT_CPU_0),
                VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR(1) |
                VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR(1));

    }
    return VTSS_RC_OK;
}

#ifdef VTSS_OS_BIG_ENDIAN
#define XTR_EOF_0          0x80000000U
#define XTR_EOF_1          0x80000001U
#define XTR_EOF_2          0x80000002U
#define XTR_EOF_3          0x80000003U
#define XTR_PRUNED         0x80000004U
#define XTR_ABORT          0x80000005U
#define XTR_ESCAPE         0x80000006U
#define XTR_NOT_READY      0x80000007U
#define XTR_VALID_BYTES(x) (4 - ((x) & 3))
#else
#define XTR_EOF_0          0x00000080U
#define XTR_EOF_1          0x01000080U
#define XTR_EOF_2          0x02000080U
#define XTR_EOF_3          0x03000080U
#define XTR_PRUNED         0x04000080U
#define XTR_ABORT          0x05000080U
#define XTR_ESCAPE         0x06000080U
#define XTR_NOT_READY      0x07000080U
#define XTR_VALID_BYTES(x) (4 - (((x) >> 24) & 3))
#endif

static vtss_rc srvl_rx_frame_discard_grp(vtss_state_t *vtss_state, const vtss_packet_rx_grp_t xtr_grp)
{
    BOOL done = FALSE;

    while (!done) {
        u32 val;
        SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val);
        switch(val) {
        case XTR_ABORT:
        case XTR_PRUNED:
        case XTR_EOF_3:
        case XTR_EOF_2:
        case XTR_EOF_1:
        case XTR_EOF_0:
            SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val); /* Last data */
            done = TRUE;        /* Last 1-4 bytes */
            break;
        case XTR_ESCAPE:
            SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val); /* Escaped data */
            break;
        case XTR_NOT_READY:
        default:
          break;
        }
    }
    return VTSS_RC_OK;
}

/**
 * Return values:
 *  0 = Data OK.
 *  1 = EOF reached. Data OK. bytes_valid indicates the number of valid bytes in last word ([1; 4]).
 *  2 = Error. No data from queue system.
 */
static int srvl_rx_frame_word(vtss_state_t *vtss_state, vtss_packet_rx_grp_t grp, BOOL first_word, u32 *rval, u32 *bytes_valid)
{
    u32 val;

    SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), &val);

    if (val == XTR_NOT_READY) {
        /** XTR_NOT_READY means two different things depending on whether this is the first
         * word read of a frame or after at least one word has been read.
         * When the first word, the group is empty, and we return an error.
         * Otherwise we have to wait for the FIFO to have received some more data. */
        if (first_word) {
            return 2; /* Error */
        }
        do {
            SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), &val);
        } while (val == XTR_NOT_READY);
    }

    switch(val) {
    case XTR_ABORT:
        /* No accompanying data. */
        VTSS_E("Aborted frame");
        return 2; /* Error */
    case XTR_EOF_0:
    case XTR_EOF_1:
    case XTR_EOF_2:
    case XTR_EOF_3:
    case XTR_PRUNED:
        *bytes_valid = XTR_VALID_BYTES(val);
        SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), &val);
        if (val == XTR_ESCAPE) {
            SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), rval);
        } else {
            *rval = val;
        }
        return 1; /* EOF */
    case XTR_ESCAPE:
        SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), rval);
        *bytes_valid = 4;
        return 0;
    default:
        *rval = val;
        *bytes_valid = 4;
        return 0;
    }
}

static vtss_rc srvl_rx_frame_get_internal(vtss_state_t           *vtss_state,
                                          vtss_packet_rx_grp_t   grp,
                                          u32                    *const ifh,
                                          u8                     *const frame,
                                          const u32              buf_length,
                                          u32                    *frm_length) /* Including FCS */
{
    u32     i, val, bytes_got, bytes_valid, buf_len = buf_length;
    BOOL    done = 0;
    u8      *buf;
    int     result;

    *frm_length = bytes_got = 0;

    /* Read IFH. It consists of 4 words */
    for (i = 0; i < 4; i++) {
        if (srvl_rx_frame_word(vtss_state, grp, TRUE, &val, &bytes_valid) != 0) {
            /* We accept neither EOF nor ERROR when reading the IFH */
            return VTSS_RC_ERROR;
        }
        ifh[i] = val;
    }

    buf = frame;

    /* Read the rest of the frame */
    while (!done && buf_len >= 4) {
        result = srvl_rx_frame_word(vtss_state, grp, FALSE, &val, &bytes_valid);
        if (result == 2) {
            // Error.
            return VTSS_RC_ERROR;
        }
        // Store the data.
        bytes_got += bytes_valid;
#ifdef VTSS_OS_BIG_ENDIAN
        *buf++ = (u8)(val >> 24);
        *buf++ = (u8)(val >> 16);
        *buf++ = (u8)(val >>  8);
        *buf++ = (u8)(val >>  0);
#else
        *buf++ = (u8)(val >>  0);
        *buf++ = (u8)(val >>  8);
        *buf++ = (u8)(val >> 16);
        *buf++ = (u8)(val >> 24);
#endif
        buf_len -= bytes_valid;
        done = result == 1;
    }

    /* Updated received byte count */
    *frm_length = bytes_got;

    if (!done) {
        /* Buffer overrun. Skip remainder of frame */
        (void)srvl_rx_frame_discard_grp(vtss_state, grp);
        return VTSS_RC_ERROR;
    }

    if (bytes_got < 60) {
        VTSS_E("short frame, %u bytes read", bytes_got);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_tx_frame_ifh_vid(vtss_state_t *vtss_state,
                                     const vtss_packet_tx_ifh_t *const ifh,
                                     const u8 *const frame,
                                     const u32 length,
                                     const vtss_vid_t vid)
{
    u32 val, w, count, last;
    const u8 *buf = frame;
    vtss_packet_tx_grp_t grp = 0;

    VTSS_N("ifh: %u, length: %u", ifh->length, length);

    VTSS_RC(srvl_packet_mode_update(vtss_state));

    if (ifh->length != 16) {
        return VTSS_RC_ERROR;
    }

    SRVL_RD(VTSS_DEVCPU_QS_INJ_INJ_STATUS, &val);
    if (!(VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_FIFO_RDY(val) & VTSS_BIT(grp))) {
        VTSS_E("Not ready");
        return VTSS_RC_ERROR;
    }

    if (VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED(val) & VTSS_BIT(grp)) {
        VTSS_E("Watermark reached");
        return VTSS_RC_ERROR;
    }

    /* Indicate SOF */
    SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_CTRL(grp), VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(1) | VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_SOF);

    // Write the IFH to the chip.
    for (w = 0; w < 4; w++) {
        SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), ifh->ifh[w]);
    }

    /* Write words, round up */
    count = ((length+3) / 4);
    last = length % 4;
    for (w = 0; w < count; w++, buf += 4) {
        if (w == 3 && vid != VTSS_VID_NULL) {
            /* Insert C-tag */
            SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), VTSS_OS_NTOHL((0x8100U << 16) | vid));
            w++;
        }
#ifdef VTSS_OS_BIG_ENDIAN
        SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
#else
        SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
#endif
    }

    /* Add padding */
    while (w < (60 / 4)) {
        SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), 0);
        w++;
    }

    /* Indicate EOF and valid bytes in last word */
    SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_CTRL(grp),
            VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(1) |
            VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES(length < 60 ? 0 : last) |
            VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_EOF);

    /* Add dummy CRC */
    SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), 0);
    w++;

    VTSS_N("wrote %u words, last: %u", w, last);

    return VTSS_RC_OK;
}

static vtss_rc srvl_tx_frame_ifh(vtss_state_t *vtss_state,
                                 const vtss_packet_tx_ifh_t *const ifh,
                                 const u8 *const frame,
                                 const u32 length)
{
    return srvl_tx_frame_ifh_vid(vtss_state, ifh, frame, length, VTSS_VID_NULL);
}

#define IFH_OFF_REW_OP  117
#define IFH_LEN_REW_OP  9
#define IFH_OFF_REW_VAL 85

static vtss_rc srvl_rx_hdr_decode(const vtss_state_t          *const state,
                                  const vtss_packet_rx_meta_t *const meta,
                                  const u8                           xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                        vtss_packet_rx_info_t *const info)
{
    u64                 ifh[2];
    u32                 sflow_id;
    vtss_phys_port_no_t chip_port;
    u32                 rew_op, rew_op_lsb, rew_val;
    int                 i;

    VTSS_DG(VTSS_TRACE_GROUP_PACKET, "IFH:");
    VTSS_DG_HEX(VTSS_TRACE_GROUP_PACKET, xtr_hdr, 8);

    for (i = 0; i < 2; i++) {
        int offset = 8 * i;
        ifh[i] = ((u64)xtr_hdr[offset + 0] << 56) | ((u64)xtr_hdr[offset + 1] << 48) | ((u64)xtr_hdr[offset + 2] << 40) | ((u64)xtr_hdr[offset + 3] << 32) |
                 ((u64)xtr_hdr[offset + 4] << 24) | ((u64)xtr_hdr[offset + 5] << 16) | ((u64)xtr_hdr[offset + 6] <<  8) | ((u64)xtr_hdr[offset + 7] <<  0);
    }

    VTSS_MEMSET(info, 0, sizeof(*info));

    info->length    = meta->length;

    // Map from chip port to API port
    chip_port = VTSS_EXTRACT_BITFIELD64(ifh[1], 43, 4);
    info->port_no = vtss_cmn_chip_to_logical_port(state, 0, chip_port);
    if (info->port_no == VTSS_PORT_NO_NONE) {
        VTSS_EG(VTSS_TRACE_GROUP_PACKET, "Unknown chip port: %u", chip_port);
        return VTSS_RC_ERROR;
    }

    info->tag.pcp     = VTSS_EXTRACT_BITFIELD64(ifh[1], 13,  3);
    info->tag.dei     = VTSS_EXTRACT_BITFIELD64(ifh[1], 12,  1);
    info->tag.vid     = VTSS_EXTRACT_BITFIELD64(ifh[1],  0, 12);
    info->xtr_qu_mask = VTSS_EXTRACT_BITFIELD64(ifh[1], 20,  8);
    info->cos         = VTSS_EXTRACT_BITFIELD64(ifh[1], 17,  3);

    VTSS_RC(vtss_cmn_packet_hints_update(state, VTSS_TRACE_GROUP_PACKET, meta->etype, info));

    info->acl_hit = VTSS_EXTRACT_BITFIELD64(ifh[1], 31, 1);

    rew_op  = VTSS_EXTRACT_BITFIELD64(ifh[0], IFH_OFF_REW_OP - 64,  IFH_LEN_REW_OP);
    rew_val = VTSS_EXTRACT_BITFIELD64(ifh[0], IFH_OFF_REW_VAL - 64, 32);
    rew_op_lsb = rew_op & 0x7;

    if (rew_op_lsb == 3) {
        // Two-step PTP Tx timestamp in MSbits of the rew_op field
        info->tstamp_id         = rew_op >> 3;
        info->tstamp_id_decoded = TRUE;
    }

    if (rew_op_lsb != 4) {
        // Rx timestamp in rew_val except when REW_OP[2:0] == 4
        info->hw_tstamp         = (u64)rew_val<<16;
        info->hw_tstamp_decoded = TRUE;
    }

    // sflow_id:
    // 0-11 : Frame has been sFlow sampled by a Tx sampler on port given by @sflow_id.
    // 12   : Frame has been sFlow sampled by an Rx sampler on port given by @src_port.
    // 13-14: Reserved.
    // 15   : Frame has not been sFlow sampled.
    sflow_id = VTSS_EXTRACT_BITFIELD64(ifh[1], 32, 4);
    if (sflow_id == 12) {
        info->sflow_type    = VTSS_SFLOW_TYPE_RX;
        info->sflow_port_no = info->port_no;
    } else if (sflow_id < 12) {
        info->sflow_type    = VTSS_SFLOW_TYPE_TX;
        info->sflow_port_no = vtss_cmn_chip_to_logical_port(state, 0, sflow_id);
    }

    info->iflow_id = VTSS_EXTRACT_BITFIELD64(ifh[1], 47, 10);

    return VTSS_RC_OK;
}

static vtss_rc srvl_rx_frame(struct vtss_state_s  *vtss_state,
                             u8                   *const data,
                             const u32             buflen,
                             vtss_packet_rx_info_t *rx_info)
{
    vtss_rc rc = VTSS_RC_INCOMPLETE;
    u32     val;

    VTSS_RC(srvl_packet_mode_update(vtss_state));

    /* Check if data is ready for grp */
    SRVL_RD(VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT, &val);
    if (val) {
        u32 ifh[4];
        u32 length;
        vtss_packet_rx_grp_t grp = VTSS_OS_CTZ(val);
        u8 xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES];
        vtss_packet_rx_meta_t meta;

        /* Get frame, separate IFH and frame data */
        VTSS_RC(srvl_rx_frame_get_internal(vtss_state, grp, ifh, data, buflen, &length));

        /* IFH is done separately because of alignment needs */
        VTSS_MEMCPY(xtr_hdr, ifh, sizeof(ifh));
        VTSS_MEMSET(&meta, 0, sizeof(meta));
        meta.length = (length - 4);
        meta.etype = (data[12] << 8) | data[13];
        rc = srvl_rx_hdr_decode(vtss_state, &meta, xtr_hdr, rx_info);
    }
    return rc;
}

/*****************************************************************************/
// srvl_oam_type_to_ifh()
/*****************************************************************************/
static vtss_rc srvl_oam_type_to_ifh(vtss_packet_oam_type_t oam_type, u32 *result)
{
    vtss_rc rc = VTSS_RC_OK;

    switch (oam_type) {
    case VTSS_PACKET_OAM_TYPE_NONE:
        *result = 0;
        break;
    case VTSS_PACKET_OAM_TYPE_CCM:
        *result = 2;
        break;
    case VTSS_PACKET_OAM_TYPE_CCM_LM:
        *result = 3;
        break;
    case VTSS_PACKET_OAM_TYPE_LBM:
        *result = 4;
        break;
    case VTSS_PACKET_OAM_TYPE_LBR:
        *result = 5;
        break;
    case VTSS_PACKET_OAM_TYPE_LMM:
        *result = 6;
        break;
    case VTSS_PACKET_OAM_TYPE_LMR:
        *result = 7;
        break;
    case VTSS_PACKET_OAM_TYPE_DMM:
        *result = 8;
        break;
    case VTSS_PACKET_OAM_TYPE_DMR:
        *result = 9;
        break;
    case VTSS_PACKET_OAM_TYPE_1DM:
        *result = 10;
        break;
    case VTSS_PACKET_OAM_TYPE_LTM:
        *result = 11;
        break;
    case VTSS_PACKET_OAM_TYPE_LTR:
        *result = 12;
        break;
    case VTSS_PACKET_OAM_TYPE_GENERIC:
        *result = 13;
        break;
    default:
        VTSS_E("Invalid OAM type (%d)", oam_type);
        rc = VTSS_RC_ERROR;
        break;
    }
    *result = (*result << 3) | 4;
    return rc;
}

/*****************************************************************************/
// srvl_ptp_action_to_ifh()
/*****************************************************************************/
static vtss_rc srvl_ptp_action_to_ifh(vtss_packet_ptp_action_t ptp_action, u8 ptp_id, u32 *result)
{
    vtss_rc rc = VTSS_RC_OK;

    switch (ptp_action) {
    case VTSS_PACKET_PTP_ACTION_NONE:
        *result = 0;
        break;
    case VTSS_PACKET_PTP_ACTION_ONE_STEP:
        *result = 2; // Residence compensation must be done in S/W, so bit 5 is not set.
        break;
    case VTSS_PACKET_PTP_ACTION_TWO_STEP:
        *result = (3 | (ptp_id << 3)); // Select a PTP timestamp identifier for two-step PTP.
        break;
    case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP:
        *result = 5;
        break;
    default:
        VTSS_E("Invalid PTP action (%d)", ptp_action);
        rc = VTSS_RC_ERROR;
        break;
    }
    return rc;
}

/*****************************************************************************/
// srvl_tx_hdr_encode()
/*****************************************************************************/
static vtss_rc srvl_tx_hdr_encode(      vtss_state_t          *const state,
                                  const vtss_packet_tx_info_t *const info,
                                        u8                    *const bin_hdr,
                                        u32                   *const bin_hdr_len)
{
    u64 inj_hdr[2];
    u32 isdx = info->iflow_id;

    if (bin_hdr == NULL) {
        // Caller wants us to return the number of bytes required to fill
        // in #bin_hdr. We need 16 bytes for the IFH.
        *bin_hdr_len = 16;
        return VTSS_RC_OK;
    } else if (*bin_hdr_len < 16) {
        return VTSS_RC_ERROR;
    }

    *bin_hdr_len = 16;

    inj_hdr[0] = VTSS_ENCODE_BITFIELD64(!info->switch_frm, 127 - 64, 1); // BYPASS
    inj_hdr[1] = 0;

    if (info->switch_frm) {
        if (info->masquerade_port != VTSS_PORT_NO_NONE) {
            u32 chip_port;
            if (info->masquerade_port >= state->port_count) {
                VTSS_E("Invalid masquerade port (%u)", info->masquerade_port);
                return VTSS_RC_ERROR;
            }

            chip_port = VTSS_CHIP_PORT_FROM_STATE(state, info->masquerade_port);
            inj_hdr[0] |= VTSS_ENCODE_BITFIELD64(1,         126 - 64, 1); // Enable masquerading.
            inj_hdr[0] |= VTSS_ENCODE_BITFIELD64(chip_port, 122 - 64, 4); // Masquerade port.
        }

        if (info->tag.tpid) {
            inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(1, 28 - 0, 2); // POP_CNT = 1, i.e. pop one tag, expected inserted by application.
        }
    } else {
        u32            port_cnt, rew_op = 0, rew_val = 0, pop_cnt = 3 /* Disable rewriter */;
        u64            chip_port_mask;
        vtss_chip_no_t chip_no;
        vtss_port_no_t stack_port_no, port_no;

        VTSS_RC(vtss_cmn_logical_to_chip_port_mask(state, info->dst_port_mask, &chip_port_mask, &chip_no, &stack_port_no, &port_cnt, &port_no));

#ifdef VTSS_FEATURE_MIRROR_CPU
        // Add mirror port if enabled. Mirroring of directed frames must occur through the port mask.
        if (state->l2.mirror_conf.port_no != VTSS_PORT_NO_NONE && state->l2.mirror_cpu_ingress) {
            chip_port_mask |= VTSS_BIT64(VTSS_CHIP_PORT_FROM_STATE(state, state->l2.mirror_conf.port_no));
        }
#endif

        if (info->ptp_action != VTSS_PACKET_PTP_ACTION_NONE) {
            VTSS_RC(srvl_ptp_action_to_ifh(info->ptp_action, info->ptp_id, &rew_op));
            rew_val = info->ptp_timestamp>>16;
            pop_cnt = 0; // Don't disable rewriter.
        } else if (info->oam_type != VTSS_PACKET_OAM_TYPE_NONE) {
            VTSS_RC(srvl_oam_type_to_ifh(info->oam_type, &rew_op));
            pop_cnt = 0; // Don't disable rewriter.
        } else if (info->tag.tpid == 0 && info->tag.vid != VTSS_VID_NULL) {
            // Get the frame classified to info->tag.vid, and rewritten accordingly.
            pop_cnt = 0;
        }

#if defined(VTSS_FEATURE_AFI_SWC)
        if (info->ptp_action == VTSS_PACKET_PTP_ACTION_NONE && info->afi_id != VTSS_AFI_ID_NONE) {
            vtss_afi_slot_conf_t *slot_conf = &state->afi.slots[info->afi_id];
            vtss_inst_t          inst = state; // For VTSS_ENTER() and VTSS_EXIT()

            // The rew_val is re-used for AFI, so we can't periodically transmit a frame
            // if ptp_action != VTSS_PACKET_PTP_ACTION_NONE
            if (port_cnt != 1) {
                VTSS_E("When using AFI, exactly one port must be specified (dst_port_mask = 0x%" PRIu64 ").", info->dst_port_mask);
                return VTSS_RC_ERROR;
            }

            if (info->afi_id >= VTSS_ARRSZ(state->afi.slots)) {
                VTSS_E("Invalid AFI ID (%u)", info->afi_id);
                return VTSS_RC_ERROR;
            }

            VTSS_ENTER();
            if (slot_conf->state != VTSS_AFI_SLOT_STATE_RESERVED) {
                VTSS_EXIT();
                VTSS_E("AFI ID (%u) not allocated", info->afi_id);
                return VTSS_RC_ERROR;
            }

            slot_conf->state   = VTSS_AFI_SLOT_STATE_ENABLED;
            slot_conf->port_no = port_no;
            VTSS_EXIT();

            // Install the frame using super-prio, or we could end up in a
            // situation where the frame never arrives at the QSYS.
            inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(1, 41, 1);

            rew_val = info->afi_id;
            inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(slot_conf->timer_idx + 1, 37 -  0,  4);
        }
#endif

        inj_hdr[0] |= VTSS_ENCODE_BITFIELD64(rew_op,  IFH_OFF_REW_OP - 64, IFH_LEN_REW_OP); // REW_OP
        inj_hdr[0] |= VTSS_ENCODE_BITFIELD64(rew_val, IFH_OFF_REW_VAL- 64, 32); // REW_VAL
        inj_hdr[0] |= VTSS_ENCODE_BITFIELD64(chip_port_mask >> 8, 64 - 64,  3); // Don't send to the CPU port (hence length == 3 and not 4)
        inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(chip_port_mask,      56 -  0,  8);
        if (isdx != VTSS_ISDX_NONE) {
            inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(isdx,      47 -  0, 9); // ISDX
        }
        if (isdx != VTSS_ISDX_NONE) {
            inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(1,           32 -  0,  1); // Use ISDX for ES0 lookups
        }

        if (info->cos >= 8) {
            // Inject super priority by setting ACL_HIT (IFH[31]) to 0 (done by VTSS_MEMSET() above) and ACL_ID[4] (IFH[41]) to 1
            inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(1, 41, 1); // acl_id[4].
        }

        inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(info->dp,                                                30 -  0,  1); // Drop Precedence
        inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(pop_cnt,                                                 28 -  0,  2); // POP_CNT
        inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(info->cos >= 8 ? 7 : info->cos,                          17 -  0,  3); // QOS Class
        inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(info->tag.tpid == 0 || info->tag.tpid == 0x8100 ? 0 : 1, 16 -  0,  1); // TAG_TYPE
        inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(info->tag.pcp,                                           13 -  0,  3); // PCP
        inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(info->tag.dei,                                           12 -  0,  1); // DEI
        inj_hdr[1] |= VTSS_ENCODE_BITFIELD64(info->tag.vid,                                            0 -  0, 16); // VID
    }

    // Time to store it in DDR SDRAM.
    bin_hdr[ 0] = inj_hdr[0] >> 56;
    bin_hdr[ 1] = inj_hdr[0] >> 48;
    bin_hdr[ 2] = inj_hdr[0] >> 40;
    bin_hdr[ 3] = inj_hdr[0] >> 32;
    bin_hdr[ 4] = inj_hdr[0] >> 24;
    bin_hdr[ 5] = inj_hdr[0] >> 16;
    bin_hdr[ 6] = inj_hdr[0] >>  8;
    bin_hdr[ 7] = inj_hdr[0] >>  0;
    bin_hdr[ 8] = inj_hdr[1] >> 56;
    bin_hdr[ 9] = inj_hdr[1] >> 48;
    bin_hdr[10] = inj_hdr[1] >> 40;
    bin_hdr[11] = inj_hdr[1] >> 32;
    bin_hdr[12] = inj_hdr[1] >> 24;
    bin_hdr[13] = inj_hdr[1] >> 16;
    bin_hdr[14] = inj_hdr[1] >>  8;
    bin_hdr[15] = inj_hdr[1] >>  0;

    VTSS_I("IFH:");
    VTSS_I_HEX(&bin_hdr[0], *bin_hdr_len);

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

#define SRVL_DEBUG_CPU_FWD(pr, addr, i, name) vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_CPU_FWD_##addr, i, "FWD_"name)
#define SRVL_DEBUG_XTR(pr, addr, name) vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_QS_XTR_XTR_##addr, "XTR_"name)
#define SRVL_DEBUG_XTR_INST(pr, addr, i, name) vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_DEVCPU_QS_XTR_XTR_##addr, i, "XTR_"name)
#define SRVL_DEBUG_INJ(pr, addr, name) vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_QS_INJ_INJ_##addr, "INJ_"name)
#define SRVL_DEBUG_INJ_INST(pr, addr, i, name) vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_DEVCPU_QS_INJ_INJ_##addr, i, "INJ_"name)

static vtss_rc srvl_debug_pkt(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32  i, port;
    char buf[32];

    /* Analyzer CPU forwarding registers */
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "Port %u", port);
        vtss_srvl_debug_reg_header(pr, buf);
        SRVL_DEBUG_CPU_FWD(pr, CFG(port), port, "CFG");
        SRVL_DEBUG_CPU_FWD(pr, BPDU_CFG(port), port, "BPDU_CFG");
        SRVL_DEBUG_CPU_FWD(pr, GARP_CFG(port), port, "GARP_CFG");
        SRVL_DEBUG_CPU_FWD(pr, CCM_CFG(port), port, "CCM_CFG");
        pr("\n");
    }

    /* Analyzer CPU queue mappings */
    vtss_srvl_debug_reg_header(pr, "CPU Queues");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_COMMON_CPUQ_CFG, "CPUQ_CFG");
    for (i = 0; i < 16; i++)
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_COMMON_CPUQ_8021_CFG(i), i, "CPUQ_8021_CFG");
    pr("\n");

    /* Packet extraction registers */
    vtss_srvl_debug_reg_header(pr, "Extraction");
    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++)
        SRVL_DEBUG_XTR_INST(pr, FRM_PRUNING(i), i, "FRM_PRUNING");
    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++)
        SRVL_DEBUG_XTR_INST(pr, GRP_CFG(i), i, "GRP_CFG");
#if defined(VTSS_DEVCPU_QS_XTR_XTR_CFG)
    SRVL_DEBUG_XTR(pr, CFG, "CFG");
#endif
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_QSYS_SYSTEM_CPU_GROUP_MAP, "CPU_GROUP_MAP");
    SRVL_DEBUG_XTR(pr, DATA_PRESENT, "DATA_PRESENT");
    pr("\n");

    /* Packet injection registers */
    vtss_srvl_debug_reg_header(pr, "Injection");
    for (i = 0; i < VTSS_PACKET_TX_GRP_CNT; i++)
        SRVL_DEBUG_INJ_INST(pr, GRP_CFG(i), i, "GRP_CFG");
    for (i = 0; i < VTSS_PACKET_TX_GRP_CNT; i++)
        SRVL_DEBUG_INJ_INST(pr, CTRL(i), i, "CTRL");
    for (i = 0; i < VTSS_PACKET_TX_GRP_CNT; i++)
        SRVL_DEBUG_INJ_INST(pr, ERR(i), i, "ERR");
    SRVL_DEBUG_INJ(pr, STATUS, "STATUS");
    pr("\n");

    vtss_srvl_debug_reg_header(pr, "DMA xtr/inj");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG, "XTRINJ_MANUAL_CFG");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA, "XTRINJ_MANUAL_INTR_ENA");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR, "XTRINJ_MANUAL_INTR");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_FDMA_FDMA_EVT_ERR, "FDMA_EVT_ERR");
    vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_SYS_SYSTEM_PORT_MODE(VTSS_CHIP_PORT_CPU_0), VTSS_CHIP_PORT_CPU_0, "SYSTEM_PORT_MODE");
    vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_SYS_SYSTEM_PORT_MODE(VTSS_CHIP_PORT_CPU_1), VTSS_CHIP_PORT_CPU_1, "SYSTEM_PORT_MODE");
    pr("\n");

    if (vtss_state->packet.npi_conf.enable) {
        vtss_srvl_debug_reg_header(pr, "NPI");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_QSYS_SYSTEM_EXT_CPU_CFG, "EXT_CPU_CFG");
        port = VTSS_CHIP_PORT(vtss_state->packet.npi_conf.port_no);
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_SYS_SYSTEM_PORT_MODE(port), port, "SYSTEM_PORT_MODE");
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_packet_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_PACKET, srvl_debug_pkt, vtss_state, pr, info);
}

#if defined(VTSS_FEATURE_AFI_SWC)
static vtss_rc srvl_debug_afi(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32 timer, slot, cnt = 0;

    /* AFI Timers */
    vtss_srvl_debug_reg_header(pr, "Timers");
    for (timer = 0; timer < VTSS_ARRSZ(vtss_state->afi.timers); timer++) {
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG(timer), timer, "CFG");
    }

    pr("\nTimer fps\n");
    pr("----- ------\n");
    for (timer = 0; timer < VTSS_ARRSZ(vtss_state->afi.timers); timer++) {
        pr("%5u %6u\n", timer, vtss_state->afi.timers[timer].fps);
    }

    /* Used slots */
    pr("\nH/W status (only slots in use are shown):\n");
    pr("Slot FrmPtr Port Timer Toggle\n");
    pr("---- ------ ---- ----- ------\n");
    for (slot = 0; slot < VTSS_ARRSZ(vtss_state->afi.slots); slot++) {
        u32 val;

        SRVL_RD(VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY(slot), &val);
        if ((val & VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_VLD) == 0) {
            continue;
        }

        timer = VTSS_X_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_TM_SEL(val);
        cnt++;
        pr("%4u 0x%04x %4u %5u %6u\n",
           slot,
           VTSS_X_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_FP(val),
           VTSS_X_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_PORTNO(val),
           timer == 0 ? 7 : timer - 1 /* H/W uses one-based counters (SIC!), S/W uses zero-based */,
           (val & VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_TM_T) != 0);
    }

    if (cnt == 0) {
        pr("<None>");
    }

    pr("\n\n");

    for (cnt = 0; cnt < VTSS_ARRSZ(vtss_state->afi.fps_per_section); cnt++) {
        pr("Accumulated FPS for section %u = %u\n", cnt, vtss_state->afi.fps_per_section[cnt]);
    }

    VTSS_RC(srvl_afi_debug_qres(vtss_state, pr));

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_afi_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_AFI, srvl_debug_afi, vtss_state, pr, info);
}
#endif /* VTSS_FEATURE_AFI_SWC */

/* - Initialization ------------------------------------------------ */

static vtss_rc srvl_packet_init(vtss_state_t *vtss_state)
{
    u32 i, pcp, dei;

    /* Setup the CPU port as VLAN aware to support switching frames based on tags */
    SRVL_WR(VTSS_ANA_PORT_VLAN_CFG(VTSS_CHIP_PORT_CPU),
            VTSS_F_ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA  |
            VTSS_F_ANA_PORT_VLAN_CFG_VLAN_POP_CNT(1) |
            VTSS_F_ANA_PORT_VLAN_CFG_VLAN_VID(1));

    /* Disable learning (only RECV_ENA must be set) */
    SRVL_WR(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT_CPU), VTSS_F_ANA_PORT_PORT_CFG_RECV_ENA);

    /* Set-up default packet Rx endianness, position of status word, and who will be extracting. */
    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++) {
        /* status word before last data */
        SRVL_WRM_CLR(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_STATUS_WORD_POS);
#ifdef VTSS_OS_BIG_ENDIAN
        /* Big-endian */
        SRVL_WRM_CLR(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP);
#else
        /* Little-endian */
        SRVL_WRM_SET(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP);
#endif

        if (!vtss_state->sys_config.using_vrap) {
            /* If not using VRAP, default to do register-based extraction. The uFDMA driver may change this field to "2" later. */
            if (!vtss_state->init_conf.using_ufdma || i != 0) {
                // Only write instance 0 of this register if not using the uFDMA, which may be loaded before
                // the switch application, because it may be part of a Linux kernel.
                SRVL_WRM(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE(1), VTSS_M_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE);
            }
        }

        /* Status word (only used when manually extracting) must come just before last data */
        SRVL_WRM_CLR(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_STATUS_WORD_POS);
    }

    /* Set-up default packet Tx endianness and who will be injecting. */
    for (i = 0; i < VTSS_PACKET_TX_GRP_CNT; i++) {
#ifdef VTSS_OS_BIG_ENDIAN
        /* Big-endian */
        SRVL_WRM_CLR(VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(i), VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_BYTE_SWAP);
#else
        /* Little-endian */
        SRVL_WRM_SET(VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(i), VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_BYTE_SWAP);
#endif
        /* According to datasheet, we must insert a small delay after every end-of-frame when injecting to qs. */
        SRVL_WR(VTSS_DEVCPU_QS_INJ_INJ_CTRL(i), VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(1));

        if (!vtss_state->sys_config.using_vrap) {
            /* If not using VRAP, default to do register-based injection. The uFDMA driver may change this field to "2" later. */
            if (!vtss_state->init_conf.using_ufdma || i != 0) {
                // Only write instance 0 of this register if not using the uFDMA, which may be loaded before
                // the switch application, because it may be part of a Linux kernel.
                SRVL_WRM(VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(i), VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE(1), VTSS_M_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE);
            }
        }
    }

    /* Setup CPU port 0 and 1. Only do this if not using VRAP */
    for (i = VTSS_CHIP_PORT_CPU_0; i <= VTSS_CHIP_PORT_CPU_1 && !vtss_state->sys_config.using_vrap; i++) {
        /* Enable IFH insertion upon extraction */
        SRVL_WRM_SET(VTSS_SYS_SYSTEM_PORT_MODE(i), VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR(1));

        /* Enable IFH parsing upon injection */
        SRVL_WRM_SET(VTSS_SYS_SYSTEM_PORT_MODE(i), VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR(1));
    }

    /* Enable CPU port */
    SRVL_WRM_SET(VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE(VTSS_CHIP_PORT_CPU), VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);

    /* Setup CPU port 0 and 1 to allow for classification of transmission of
     * switched frames into a user-module-specifiable QoS class.
     * For the two CPU ports, we set a one-to-one mapping between a VLAN tag's
     * PCP and a QoS class. When transmitting switched frames, the PCP value
     * of the VLAN tag (which is always inserted to get it switched on a given
     * VID), then controls the priority. */
    /* Enable looking into PCP bits */
    SRVL_WR(VTSS_ANA_PORT_QOS_CFG(VTSS_CHIP_PORT_CPU), VTSS_F_ANA_PORT_QOS_CFG_QOS_PCP_ENA);

    /* Disable aging of Rx CPU queues to allow the frames to stay there longer than
     * on normal front ports. */
    SRVL_WRM_SET(VTSS_REW_PORT_PORT_CFG(VTSS_CHIP_PORT_CPU_0), VTSS_F_REW_PORT_PORT_CFG_AGE_DIS);
    SRVL_WRM_SET(VTSS_REW_PORT_PORT_CFG(VTSS_CHIP_PORT_CPU_1), VTSS_F_REW_PORT_PORT_CFG_AGE_DIS);

    /* Set-up the one-to-one mapping */
    for (pcp = 0; pcp < VTSS_PCP_END - VTSS_PCP_START; pcp++) {
        for (dei = 0; dei < VTSS_DEI_END - VTSS_DEI_START; dei++) {
            SRVL_WR(VTSS_ANA_PORT_QOS_PCP_DEI_MAP_CFG(VTSS_CHIP_PORT_CPU, (8 * dei + pcp)),
                    VTSS_F_ANA_PORT_QOS_PCP_DEI_MAP_CFG_QOS_PCP_DEI_VAL(pcp));
        }
    }

#if defined(VTSS_FEATURE_AFI_SWC)
    // Cancel any possible ongoing AFI frames from previous session.
    for (i = 0; i < VTSS_AFI_SLOT_CNT; i++) {
        (void)srvl_afi_cancel(vtss_state, i);
    }

    VTSS_RC(srvl_afi_init(vtss_state));
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_packet_state_t *state = &vtss_state->packet;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->rx_conf_set                = srvl_rx_conf_set;
        state->rx_frame                   = srvl_rx_frame;
        state->tx_frame_ifh               = srvl_tx_frame_ifh;
        state->rx_hdr_decode              = srvl_rx_hdr_decode;
        state->rx_ifh_size                = VTSS_SVL_RX_IFH_SIZE;
        state->tx_hdr_encode              = srvl_tx_hdr_encode;
        state->npi_conf_set               = srvl_npi_conf_set;
        state->packet_phy_cnt_to_ts_cnt   = srvl_packet_phy_cnt_to_ts_cnt;
        state->packet_ns_to_ts_cnt        = srvl_packet_ns_to_ts_cnt;
        state->ptp_get_timestamp          = srvl_ptp_get_timestamp;
        state->rx_queue_count             = VTSS_PACKET_RX_QUEUE_CNT;
#if defined(VTSS_FEATURE_AFI_SWC)
        vtss_state->afi.alloc             = srvl_afi_alloc;
        vtss_state->afi.free              = srvl_afi_free;
        vtss_state->afi.hijack            = srvl_afi_hijack;
        vtss_state->afi.link_state_change = srvl_afi_link_state_change;
#endif /* VTSS_FEATURE_AFI_SWC */
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(srvl_packet_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(srvl_rx_conf_set(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_OCELOT */
