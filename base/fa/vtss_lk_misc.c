// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_LAIKA)

/* - CIL functions ------------------------------------------------- */

#if defined(VTSS_FEATURE_EEE)
/* =================================================================
 *  EEE - Energy Efficient Ethernet
 * =================================================================*/
static vtss_rc fa_eee_port_conf_set(vtss_state_t                     *vtss_state,
                                    const vtss_port_no_t              port_no,
                                    const vtss_eee_port_conf_t *const conf)
{
    u32            closest_match_index, closest_match, i, requested_time;
    u32            eee_cfg_reg = 0x0; // SYS::EEE_CFG register value.
    vtss_port_no_t chip_port = VTSS_CHIP_PORT(port_no);
    u16            eee_timer_age;
    u32            dev_tgt = vtss_fa_dev_tgt(vtss_state, port_no);

    // The formula for the actual wake-up time given a
    // register value is non-linear (though periodic with
    // increasing base values).
    // The easiest way to find the closest match to a user-specified
    // value is to create a static lookup table that will have to be
    // traversed everytime.
    if (!vtss_state->eee.timer_table_initialized) {
        vtss_state->eee.timer_table_initialized = TRUE;
        for (i = 0; i < VTSS_EEE_TIMER_TABLE_CNT; i++) {
            vtss_state->eee.timer_table[i] = (1 << (2 * (i / 16UL))) * (i % 16UL);
        }
    }

    // EEE enable
    if (conf->eee_ena) {
        // LPI is really an old error code redefined to tell the link partner to
        // go to
        //  lower power or when removed to wakeup.
        //  Some devices are seeing the error code and assuming there is a
        //  problem causing the link to go down. A work around is to only enable
        //  EEE in the MAC (No LPI signal to the PHY) when the PHY has auto
        //  negotiated and have found that the link partner supports EEE.
        if (conf->lp_advertisement == 0) {
            VTSS_D("Link partner doesn't support EEE - Keeping EEE disabled. Port:%u", chip_port);
        } else if (!(vtss_state->port.conf[port_no].fdx)) {
            // EEE and Half duplex are not supposed to work together, so we
            // disables EEE in the case where the port is in HDX mode.
            VTSS_D("EEE disabled due to that port is in HDX mode, port:%u", chip_port);
        } else {
            eee_cfg_reg |= VTSS_M_DEV1G_EEE_CFG_EEE_ENA;
        }
    }

    // EEE wakeup timer (See datasheet for understanding calculation)
    closest_match_index = 0;
    closest_match = 0xFFFFFFFFUL;
    requested_time = conf->tx_tw;
    for (i = 0; i < VTSS_EEE_TIMER_TABLE_CNT; i++) {
        u32 table_val = vtss_state->eee.timer_table[i];
        if (table_val >= requested_time) {
            u32 diff = table_val - requested_time;
            if (diff < closest_match) {
                closest_match = diff;
                closest_match_index = i;
                if (closest_match == 0) {
                    break;
                }
            }
        }
    }

    if (closest_match == 0xFFFFFFFFUL) {
        closest_match_index = 127;
    }

    eee_cfg_reg |= VTSS_F_DEV1G_EEE_CFG_EEE_TIMER_WAKEUP(closest_match_index);

    // Set the latency depending upon what the user prefer (power saving vs. low
    // traffic latency)
    if (conf->optimized_for_power) {
        eee_timer_age = 82; // Set timer age to 263 mSec.
    } else {
        eee_timer_age = 0x23; // Set timer age to 48 uSec.
    }

    // EEE holdoff timer
    eee_cfg_reg |= VTSS_F_DEV1G_EEE_CFG_EEE_TIMER_HOLDOFF(0x5) |
                   VTSS_F_DEV1G_EEE_CFG_EEE_TIMER_AGE(eee_timer_age);

    // EEE fast queues
    VTSS_N("eee_fast_queues:0x%X, to-dev:%d, chip_port:%d", conf->eee_fast_queues, dev_tgt,
           chip_port);
    REG_WRM(VTSS_QSYS_EEE_CFG(chip_port),
            VTSS_F_QSYS_EEE_CFG_EEE_FAST_QUEUES(conf->eee_fast_queues),
            VTSS_M_QSYS_EEE_CFG_EEE_FAST_QUEUES);

    // Registers write
    VTSS_D("chip_port:%d, eee_cfg_reg:0x%X", chip_port, eee_cfg_reg);
    REG_WR(VTSS_DEV1G_EEE_CFG(dev_tgt), eee_cfg_reg);
    VTSS_D("chip_port:%u, eee_cfg_reg = 0x%X, conf->tx_tw = %d, eee_timer_age:%d", chip_port,
           eee_cfg_reg, conf->tx_tw, eee_timer_age);

    // Setting Buffer size to 12.2 Kbyte & 255 frames.
    REG_WR(VTSS_QSYS_EEE_THRES, 0xFFFF);

    // Work-around of Bugzilla#18901
    u32 dummy_reg, prio;
    for (prio = 0; prio < 8; prio++) {
        REG_RD(VTSS_QRES_RES_STAT(2048 + 8 * port_no + prio), &dummy_reg);
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_EEE */

/* ================================================================= *
 *  Miscellaneous
 * ================================================================= */

static vtss_rc fa_reg_read(vtss_state_t        *vtss_state,
                           const vtss_chip_no_t chip_no,
                           const u32            addr,
                           u32 *const           value)
{
    return vtss_fa_rd(vtss_state, addr, value);
}

static vtss_rc fa_reg_write(vtss_state_t        *vtss_state,
                            const vtss_chip_no_t chip_no,
                            const u32            addr,
                            const u32            value)
{
    return vtss_fa_wr(vtss_state, addr, value);
}

vtss_rc vtss_fa_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id)
{
    chip_id->part_number = 0x6500;
    chip_id->revision = 1;
    return VTSS_RC_OK;
}

static vtss_rc fa_ptp_event_poll(vtss_state_t *vtss_state, vtss_ptp_event_type_t *ev_mask)
{
    u32 sticky, mask;

    /* PTP events */
    *ev_mask = 0;
    REG_RD(VTSS_DEVCPU_PTP_PTP_PIN_INTR, &sticky);
    REG_WR(VTSS_DEVCPU_PTP_PTP_PIN_INTR, sticky);
    REG_RD(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA, &mask);
    sticky &= mask; /* Only handle enabled sources */

    *ev_mask |=
        (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1 << 0)) ? VTSS_PTP_PIN_0_SYNC_EV : 0;
    *ev_mask |=
        (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1 << 1)) ? VTSS_PTP_PIN_1_SYNC_EV : 0;
    *ev_mask |=
        (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1 << 2)) ? VTSS_PTP_PIN_2_SYNC_EV : 0;
    *ev_mask |=
        (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1 << 3)) ? VTSS_PTP_PIN_3_SYNC_EV : 0;
    *ev_mask |=
        (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1 << 4)) ? VTSS_PTP_PIN_4_SYNC_EV : 0;
    *ev_mask |=
        (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1 << 5)) ? VTSS_PTP_PIN_5_SYNC_EV : 0;
    VTSS_D("sticky: 0x%x, ev_mask 0x%x", sticky, *ev_mask);

    return VTSS_RC_OK;
}

static vtss_rc fa_ptp_event_enable(vtss_state_t         *vtss_state,
                                   vtss_ptp_event_type_t ev_mask,
                                   BOOL                  enable)
{
    /* PTP masks */
    VTSS_D("ev_mask 0x%x, enable: %d", ev_mask, enable);

    if (ev_mask & VTSS_PTP_PIN_0_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1 << 0 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1 << 0));
    }
    if (ev_mask & VTSS_PTP_PIN_1_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1 << 1 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1 << 1));
    }
    if (ev_mask & VTSS_PTP_PIN_2_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1 << 2 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1 << 2));
    }
    if (ev_mask & VTSS_PTP_PIN_3_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1 << 3 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1 << 3));
    }
    if (ev_mask & VTSS_PTP_PIN_4_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1 << 4 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1 << 4));
    }
    if (ev_mask & VTSS_PTP_PIN_5_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1 << 5 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1 << 5));
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_poll_1sec(vtss_state_t *vtss_state)
{
    return vtss_fa_init_groups(vtss_state, VTSS_INIT_CMD_POLL);
}

vtss_rc vtss_fa_gpio_mode(vtss_state_t          *vtss_state,
                          const vtss_chip_no_t   chip_no,
                          const vtss_gpio_no_t   gpio_no,
                          const vtss_gpio_mode_t mode)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_misc_debug_print(vtss_state_t                  *vtss_state,
                                 lmu_ss_t                      *ss,
                                 const vtss_debug_info_t *const info)
{
    return VTSS_RC_OK;
}
#endif

/* - Initialization ------------------------------------------------ */
vtss_rc vtss_fa_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_misc_state_t *state = &vtss_state->misc;

    if (cmd == VTSS_INIT_CMD_CREATE) {
        state->reg_read = fa_reg_read;
        state->reg_write = fa_reg_write;
        state->chip_id_get = vtss_fa_chip_id_get;
        state->poll_1sec = fa_poll_1sec;
        state->ptp_event_poll = fa_ptp_event_poll;
        state->ptp_event_enable = fa_ptp_event_enable;
#if defined(VTSS_FEATURE_EEE)
        vtss_state->eee.port_conf_set = fa_eee_port_conf_set;
#endif /* VTSS_FEATURE_EEE */
    } else if (cmd == VTSS_INIT_CMD_INIT) {
    } else if (cmd == VTSS_INIT_CMD_PORT_MAP) {
    }

    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_LAIKA */
