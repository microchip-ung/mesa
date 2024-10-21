// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_fa_cil.h"
#if defined(VTSS_ARCH_FA) && defined(VTSS_FEATURE_QOS_TAS_LIST_LINKED)
#include "vtss_fa_lan969x_tas.h"

static u32 tas_op_type_calc(vtss_qos_tas_gco_t  gate_operation)
{
    switch (gate_operation) {
    case VTSS_QOS_TAS_GCO_SET_GATE_STATES: return 0;
    case VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC: return 2;
    case VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC: return 3;
    }

    VTSS_E("Unknown register QSYS:TAS_GCL_CFG:TAS_GCL_CTRL_CFG.OP_TYPE value");
    return VTSS_QOS_TAS_GCO_SET_GATE_STATES;
}

static vtss_qos_tas_gco_t tas_gate_operation_calc(u32 value)
{
    switch (value) {
    case 0: return VTSS_QOS_TAS_GCO_SET_GATE_STATES;
    case 2: return VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC;
    case 3: return VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC;
    }

    VTSS_E("Unknown register QSYS:TAS_GCL_CFG:TAS_GCL_CTRL_CFG.OP_TYPE value");
    return VTSS_QOS_TAS_GCO_SET_GATE_STATES;
}

static void tas_next_unused_entry_get(vtss_state_t *vtss_state,  u32 *entry_idx)
{
    u32                  i;
    vtss_tas_list_entry  *entries = vtss_state->qos.tas.tas_entries;

    for (i = *entry_idx + 1; i < RT_TAS_NUMBER_OF_ENTRIES; ++i) {
        if (!entries[i].in_use) {
            *entry_idx = i;
            entries[i].in_use = TRUE;
            return;
        }
    }
}

u32 lan969x_tas_list_allocate(vtss_state_t *vtss_state,  u32 length)
{
    u32                     i, list_idx, found, first_entry = 0;
    BOOL                    first;
    vtss_tas_list_t         *tas_lists = vtss_state->qos.tas.tas_lists;
    vtss_tas_list_entry     *entries = vtss_state->qos.tas.tas_entries;

    VTSS_D("Enter length %u", length);

    /* Find a unused list */
    for (list_idx = 0; list_idx < VTSS_TAS_NUMBER_OF_LISTS; ++list_idx) {
        if (!tas_lists[list_idx].in_use) { /* Find a unused list */
            break;
        }
    }
    if (list_idx == VTSS_TAS_NUMBER_OF_LISTS) {
        VTSS_D("No free TAS list was found");
        return TAS_LIST_IDX_NONE;
    }

    /* Check that there are unused list entries for the complete list */
    for (i = 0, found = 0, first = TRUE; ((found < length) && (i < RT_TAS_NUMBER_OF_ENTRIES)); ++i) {
        if (!entries[i].in_use) {
            if (first) {
                first = FALSE;
                first_entry = i;
            }
            found += 1;
        }
    }

    if (found == length) {
        tas_lists[list_idx].in_use = TRUE; /* The found list is now in use */
        tas_lists[list_idx].entry_idx = first_entry;
        entries[first_entry].in_use = TRUE; /* Only the first element is actually reserved, but we know that there are unused entries for the complete list */
        /* Select the list entry and make it point to it self to make the list empty */
        REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(first_entry), VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM);
        REG_WR(VTSS_HSCH_TAS_GCL_CTRL_CFG2, first_entry);
    } else {
        VTSS_D("No free entry slot was found in any row");
        return TAS_LIST_IDX_NONE;
    }

    VTSS_D("Exit list_idx %u", list_idx);

    return list_idx;
}

vtss_rc lan969x_tas_list_free(vtss_state_t *vtss_state,  u32 list_idx)
{
    u32                     entry_idx, value;
    vtss_tas_list_t         *tas_lists = vtss_state->qos.tas.tas_lists;
    vtss_tas_list_entry     *entries = vtss_state->qos.tas.tas_entries;

    VTSS_D("Enter");

    if (list_idx >= VTSS_TAS_NUMBER_OF_LISTS) {
        return VTSS_RC_ERROR;
    }

    VTSS_D("list_idx %u  entry_idx %u", list_idx, tas_lists[list_idx].entry_idx);

    if (tas_lists[list_idx].entry_idx < RT_TAS_NUMBER_OF_ENTRIES) { /* Check if the list has entries */
        /* Mark all entries as unused */
        entry_idx = tas_lists[list_idx].entry_idx;
        /* Select the list */
        REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM);
        do {
            /* Select the list entry */
            REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(entry_idx), VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM);

            entries[entry_idx].in_use = FALSE;  /* Mark as unused */

            /* Read the next GCL entry index */
            REG_RD(VTSS_HSCH_TAS_GCL_CTRL_CFG2, &value);
            entry_idx = VTSS_X_HSCH_TAS_GCL_CTRL_CFG2_NEXT_GCL(value);
        } while(entry_idx != tas_lists[list_idx].entry_idx);
    }

    tas_lists[list_idx].in_use = FALSE; /* Free the list */
    tas_lists[list_idx].inherit_profile = FALSE;
    tas_lists[list_idx].profile_idx = TAS_PROFILE_IDX_NONE;
    tas_lists[list_idx].entry_idx = TAS_ENTRY_IDX_NONE;

    return VTSS_RC_OK;
}

vtss_rc lan969x_tas_current_port_conf_calc(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_qos_tas_port_conf_t *current_port_conf)
{
    u32                   msb, store, value, entry_idx, entry_first, gcl_idx, gate_state;
    vtss_tas_gcl_state_t  *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];

    VTSS_MEMSET(current_port_conf, 0, sizeof(*current_port_conf));
    if (gcl_state->curr_list_idx == TAS_LIST_IDX_NONE) {
        return VTSS_RC_OK;
    }

    /* Store the currently selected list */
    REG_RD(VTSS_HSCH_TAS_CFG_CTRL, &store);

    /* Select the list */
    REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(gcl_state->curr_list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM);;

    /* Read the based address of the first entry in the list */
    REG_RD(VTSS_HSCH_TAS_LIST_CFG, &value);
    entry_idx = entry_first = VTSS_X_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR(value);
#if defined(VTSS_FEATURE_QOS_OT)
    if (vtss_state->vtss_features[FEATURE_QOS_OT]) {
        u32 se = VTSS_X_HSCH_TAS_LIST_CFG_LIST_HSCH_POS(value);
        current_port_conf->ot = ((se >= FA_HSCH_L0_OT_SE(0)) && (se < RT_HSCH_L0_SES)) ? TRUE : FALSE;
    }
#endif
    /* Read the list elements */
    gcl_idx = 0;
    do {
        /* Select the list entry */
        REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(entry_idx), VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM);

        /* Read the gate state */
        REG_RD(VTSS_HSCH_TAS_GCL_CTRL_CFG, &value);
        gate_state = VTSS_X_HSCH_TAS_GCL_CTRL_CFG_GATE_STATE(value);
        vtss_u8_to_bool8(gate_state, current_port_conf->gcl[gcl_idx].gate_open);

        /* Read time interval */
        REG_RD(VTSS_HSCH_TAS_GCL_TIME_CFG, &current_port_conf->gcl[gcl_idx].time_interval);

        /* Read the operational type */
        current_port_conf->gcl[gcl_idx].gate_operation = tas_gate_operation_calc(VTSS_X_HSCH_TAS_GCL_CTRL_CFG_OP_TYPE(value));

        /* Read the next GCL entry index */
        REG_RD(VTSS_HSCH_TAS_GCL_CTRL_CFG2, &value);
        entry_idx = VTSS_X_HSCH_TAS_GCL_CTRL_CFG2_NEXT_GCL(value);

        gcl_idx += 1;
    } while(entry_idx != entry_first);

    /* Save list length */
    current_port_conf->gcl_length = gcl_idx;

    REG_RD(VTSS_HSCH_TAS_BASE_TIME_NSEC, &current_port_conf->base_time.nanoseconds);
    REG_RD(VTSS_HSCH_TAS_BASE_TIME_SEC_LSB, &current_port_conf->base_time.seconds);
    REG_RD(VTSS_HSCH_TAS_BASE_TIME_SEC_MSB, &msb);
    current_port_conf->base_time.sec_msb = (u16)msb;
    REG_RD(VTSS_HSCH_TAS_CYCLE_TIME_CFG, &current_port_conf->cycle_time);

    /* Re-store the currently selected list */
    REG_WR(VTSS_HSCH_TAS_CFG_CTRL, store);

    return VTSS_RC_OK;
}

static u8 tas_preemptable_calc(vtss_qos_tas_gce_t *gcl, u32 gcl_length)
{
    u32 i;
    u8  vector = 0;

    for (i = 0; i < gcl_length; ++i) {
        if (gcl[i].gate_operation == VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC) { /* The MAC release interval priorities are pre-empt able */
            vector |= vtss_bool8_to_u8(gcl[i].gate_open);
        }
    }
    return vector;
}

vtss_rc lan969x_tas_list_start(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                               u32 list_idx, u32 obsolete_list_idx,
                               vtss_qos_tas_port_conf_t *port_conf, u32 startup_time)
{
    u32                 gcl_idx, value, time_interval_sum = 0;
    u32                 maxsdu, i, hold_advance;
    u32                 profile_idx = vtss_state->qos.tas.tas_lists[list_idx].profile_idx;
    u32                 entry_idx = vtss_state->qos.tas.tas_lists[list_idx].entry_idx;
    vtss_port_no_t      chip_port = VTSS_CHIP_PORT(port_no);

    vtss_timestamp_t    *base_time = &port_conf->base_time;
    u32                 cycle_time = port_conf->cycle_time;
    u32                 gcl_length = port_conf->gcl_length;
    vtss_qos_tas_gce_t  *gcl = port_conf->gcl;;
    u16                 *max_sdu  = port_conf->max_sdu;
    u8                  preemptable = 0;
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    u32  fp_enable_tx = (vtss_state->qos.fp.port_conf[port_no].enable_tx ? 1 : 0);
#else
    u32  fp_enable_tx = FALSE;
#endif

    VTSS_D("Enter list_idx %u  obsolete_list_idx %u  entry_idx %u  profile_idx %u  chip_port %u  gcl_length %u  gate_open[0] %X",
           list_idx, obsolete_list_idx, entry_idx, profile_idx, chip_port, gcl_length, vtss_bool8_to_u8(gcl[0].gate_open));
#if defined(VTSS_FEATURE_QOS_OT)
    if (vtss_state->vtss_features[FEATURE_QOS_OT]) {
        VTSS_D("se %u  ot %u", FA_HSCH_TAS_SE(chip_port, port_conf->ot), port_conf->ot);
    } else {
        VTSS_D("se %u", FA_HSCH_TAS_SE(chip_port, FALSE));
    }
#else
    VTSS_D("se %u", FA_HSCH_TAS_SE(chip_port, FALSE));
#endif

    /* Select the list */
    REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM);

    /* List must be in ADMIN state */
    REG_RD(VTSS_HSCH_TAS_LIST_STATE, &value);
    if (VTSS_X_HSCH_TAS_LIST_STATE_LIST_STATE(value) != TAS_LIST_STATE_ADMIN) {
        VTSS_D("The TAS list is not in admin state  index %u", list_idx);
        return VTSS_RC_ERROR;
    }

    /* Configure the list */
    REG_WR(VTSS_HSCH_TAS_BASE_TIME_NSEC, base_time->nanoseconds);
    REG_WR(VTSS_HSCH_TAS_BASE_TIME_SEC_LSB, base_time->seconds);
    REG_WR(VTSS_HSCH_TAS_BASE_TIME_SEC_MSB, base_time->sec_msb);
    REG_WR(VTSS_HSCH_TAS_CYCLE_TIME_CFG, cycle_time);
    REG_WR(VTSS_HSCH_TAS_STARTUP_CFG, VTSS_F_HSCH_TAS_STARTUP_CFG_OBSOLETE_IDX((obsolete_list_idx != TAS_LIST_IDX_NONE) ? obsolete_list_idx : list_idx) |
                                      VTSS_F_HSCH_TAS_STARTUP_CFG_STARTUP_TIME(startup_time/256));
#if defined(VTSS_FEATURE_QOS_OT)
    if (vtss_state->vtss_features[FEATURE_QOS_OT]) {
        REG_WR(VTSS_HSCH_TAS_LIST_CFG, VTSS_F_HSCH_TAS_LIST_CFG_LIST_PORT_NUM(chip_port) |
                                    VTSS_F_HSCH_TAS_LIST_CFG_LIST_HSCH_POS(FA_HSCH_TAS_SE(chip_port, port_conf->ot)) |
                                    VTSS_F_HSCH_TAS_LIST_CFG_LIST_TOD_DOM(vtss_state->ts.conf.tsn_domain) |
                                    VTSS_F_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR(entry_idx));
    } else {
        REG_WR(VTSS_HSCH_TAS_LIST_CFG, VTSS_F_HSCH_TAS_LIST_CFG_LIST_PORT_NUM(chip_port) |
                                    VTSS_F_HSCH_TAS_LIST_CFG_LIST_HSCH_POS(FA_HSCH_TAS_SE(chip_port, FALSE)) |
                                    VTSS_F_HSCH_TAS_LIST_CFG_LIST_TOD_DOM(vtss_state->ts.conf.tsn_domain) |
                                    VTSS_F_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR(entry_idx));
    }
#else
    REG_WR(VTSS_HSCH_TAS_LIST_CFG, VTSS_F_HSCH_TAS_LIST_CFG_LIST_PORT_NUM(chip_port) |
                                   VTSS_F_HSCH_TAS_LIST_CFG_LIST_HSCH_POS(FA_HSCH_TAS_SE(chip_port, FALSE)) |
                                   VTSS_F_HSCH_TAS_LIST_CFG_LIST_TOD_DOM(vtss_state->ts.conf.tsn_domain) |
                                   VTSS_F_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR(entry_idx));
#endif

    /* Configure the profile */
    for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        maxsdu = (max_sdu[i] / 64);
        REG_WR(VTSS_HSCH_TAS_QMAXSDU_CFG(profile_idx, i), VTSS_F_HSCH_TAS_QMAXSDU_CFG_QMAXSDU_VAL(maxsdu));
        REG_WR(VTSS_HSCH_QMAXSDU_DISC_CFG(profile_idx, i), VTSS_F_HSCH_QMAXSDU_DISC_CFG_QMAXSDU_DISC_ENA((maxsdu != 0) ? 1 : 0) |
                                                           VTSS_F_HSCH_QMAXSDU_DISC_CFG_QMAXSDU_LSB(max_sdu[i] % 64));
    }

    REG_RD(VTSS_DSM_PREEMPT_CFG(chip_port), &value);
    hold_advance = (fp_enable_tx != 0) ? (VTSS_X_DSM_PREEMPT_CFG_P_MIN_SIZE(value) + 1) : 0;
    /* FP pre-emptable frames must not be guard banded as this is controlled by the MAC HOLD command */
    preemptable = tas_preemptable_calc(gcl, gcl_length);
    /* Note that queues marked with '1' in SCH_TRAFFIC_QUEUES has guard banding disabled */
    REG_WRM(VTSS_HSCH_TAS_PROFILE_CONFIG(profile_idx), VTSS_F_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES(preemptable) |
                                         VTSS_F_HSCH_TAS_PROFILE_CONFIG_HOLDADVANCE(hold_advance) |
                                         VTSS_F_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED(tas_link_speed_calc(vtss_state->port.conf[port_no].speed)),
                                         VTSS_M_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES |
                                         VTSS_M_HSCH_TAS_PROFILE_CONFIG_HOLDADVANCE |
                                         VTSS_M_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED);

    /* Configure the list elements */
    for (gcl_idx = 0; gcl_idx < gcl_length; ++gcl_idx) {
        /* Select the list entry */
        REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(entry_idx), VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM);

        if (gcl_idx < (gcl_length - 1)) { /* If not the last entry get the next entry index */
            tas_next_unused_entry_get(vtss_state, &entry_idx);
        } else {    /* Last entry */
            entry_idx = vtss_state->qos.tas.tas_lists[list_idx].entry_idx; /* End of list - point to start of list */
        }

        /* Configure the list entry */
        REG_WR(VTSS_HSCH_TAS_GCL_CTRL_CFG, VTSS_F_HSCH_TAS_GCL_CTRL_CFG_GATE_STATE(vtss_bool8_to_u8(gcl[gcl_idx].gate_open)) |
                                           VTSS_F_HSCH_TAS_GCL_CTRL_CFG_OP_TYPE(tas_op_type_calc(gcl[gcl_idx].gate_operation)));
        REG_WR(VTSS_HSCH_TAS_GCL_CTRL_CFG2, VTSS_F_HSCH_TAS_GCL_CTRL_CFG2_NEXT_GCL(entry_idx));
        REG_WR(VTSS_HSCH_TAS_GCL_TIME_CFG, gcl[gcl_idx].time_interval);

        /* Calculate the sum of time intervals */
        time_interval_sum += gcl[gcl_idx].time_interval;
    }

    /* Check if the sum of intervals are larger that the requeste cycle time */
    if ((time_interval_sum > cycle_time) || (cycle_time > VTSS_QOS_TAS_CT_MAX) || (cycle_time == 0)) {
        VTSS_D("The TAS list cycle time is invalid. time_interval_sum %u  cycle_time %u", time_interval_sum, cycle_time);
        return VTSS_RC_ERROR;
    }
    if (time_interval_sum != cycle_time) {
        VTSS_D("The TAS list cycle time is larger than list time interval sum. time_interval_sum %u  cycle_time %u", time_interval_sum, cycle_time);
    }

    /* Start the list */
    tas_list_state_write(vtss_state, list_idx, TAS_LIST_STATE_ADVANCING);

    return VTSS_RC_OK;
}

vtss_rc lan966x_tas_frag_size_update(struct vtss_state_s   *vtss_state,
                                     const vtss_port_no_t  port_no)
{
    vtss_port_no_t           chip_port = VTSS_CHIP_PORT(port_no);
    vtss_qos_tas_port_conf_t *port_conf = &vtss_state->qos.tas.port_conf[port_no];
    vtss_tas_gcl_state_t     *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];
    u32                      gcl_length = port_conf->gcl_length;
    vtss_qos_tas_gce_t       *gcl = port_conf->gcl;;
    u32                      hold_advance, profile_idx, value;
    u8                       preemptable = 0;
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    u32  fp_enable_tx = (vtss_state->qos.fp.port_conf[port_no].enable_tx ? 1 : 0);
#else
    u32  fp_enable_tx = FALSE;
#endif

    if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {    /* Check if there is a current list active */
        profile_idx = vtss_state->qos.tas.tas_lists[gcl_state->curr_list_idx].profile_idx;  /* Get the profile index for the currently active list */

        /* This must be done when the frame preemption RemAddFragSize is changing */
        REG_RD(VTSS_DSM_PREEMPT_CFG(chip_port), &value);
        hold_advance = (fp_enable_tx != 0) ? (VTSS_X_HSCH_TAS_PROFILE_CONFIG_HOLDADVANCE(value) + 1) : 0;
        /* FP pre-emptable frames must not be guard banded as this is controlled by the MAC HOLD command */
        preemptable = tas_preemptable_calc(gcl, gcl_length);
        /* Note that queues marked with '1' in SCH_TRAFFIC_QUEUES has guard banding disabled */
        REG_WRM(VTSS_HSCH_TAS_PROFILE_CONFIG(profile_idx), VTSS_F_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES(preemptable) |
                                             VTSS_F_HSCH_TAS_PROFILE_CONFIG_HOLDADVANCE(hold_advance),
                                             VTSS_M_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES |
                                             VTSS_M_HSCH_TAS_PROFILE_CONFIG_HOLDADVANCE);
    }

    return VTSS_RC_OK;
}

#endif
