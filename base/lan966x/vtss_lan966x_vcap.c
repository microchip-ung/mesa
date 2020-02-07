// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_VCAP
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

/* ================================================================= *
 *  IS1
 * ================================================================= */

static vtss_rc lan966x_is1_entry_get(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is1_entry_add(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is1_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is1_entry_move(vtss_state_t *vtss_state,
                                      vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is1_entry_update(vtss_state_t *vtss_state,
                                        vtss_vcap_idx_t *idx, vtss_is1_action_t *act)
{
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  IS2
 * ================================================================= */

static vtss_rc lan966x_is2_entry_get(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is2_entry_add(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is2_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is2_entry_move(vtss_state_t *vtss_state,
                                      vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is2_entry_update(vtss_state_t *vtss_state,
                                        vtss_vcap_idx_t *idx, vtss_is2_data_t *is2)
{
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  ES0
 * ================================================================= */

static vtss_rc lan966x_es0_entry_get(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_entry_add(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_entry_move(vtss_state_t *vtss_state,
                                      vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_entry_update(vtss_state_t *vtss_state,
                                        vtss_vcap_idx_t *idx, vtss_es0_data_t *es0)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_eflow_update(vtss_state_t *vtss_state, const vtss_eflow_id_t flow_id)
{
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  ACL
 * ================================================================= */

static vtss_rc lan966x_acl_policer_set(vtss_state_t *vtss_state,
                                       const vtss_acl_policer_no_t policer_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_acl_port_conf_set(vtss_state_t *vtss_state,
                                         const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_acl_port_counter_get(vtss_state_t *vtss_state,
                                            const vtss_port_no_t    port_no,
                                            vtss_acl_port_counter_t *const counter)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_acl_port_counter_clear(vtss_state_t *vtss_state,
                                              const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ace_add(vtss_state_t *vtss_state,
                               const vtss_ace_id_t ace_id, const vtss_ace_t *const ace)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ace_del(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_vcap_range_commit(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_vcap_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_vcap_init(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_vcap_state_t *state = &vtss_state->vcap;
    vtss_vcap_obj_t   *is1 = &state->is1.obj;
    vtss_vcap_obj_t   *is2 = &state->is2.obj;
    vtss_vcap_obj_t   *es0 = &state->es0.obj;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        // IS1
        is1->max_count = (VTSS_LAN966X_IS1_CNT / 4);
        is1->max_rule_count = VTSS_LAN966X_IS1_CNT;
        is1->entry_get = lan966x_is1_entry_get;
        is1->entry_add = lan966x_is1_entry_add;
        is1->entry_del = lan966x_is1_entry_del;
        is1->entry_move = lan966x_is1_entry_move;
        state->is1_entry_update = lan966x_is1_entry_update;

        // IS2
        is2->max_count = (VTSS_LAN966X_IS2_CNT / 4);
        is2->max_rule_count = VTSS_LAN966X_IS2_CNT;
        is2->entry_get = lan966x_is2_entry_get;
        is2->entry_add = lan966x_is2_entry_add;
        is2->entry_del = lan966x_is2_entry_del;
        is2->entry_move = lan966x_is2_entry_move;
        state->is2_entry_update = lan966x_is2_entry_update;

        // ES0
        es0->max_count = VTSS_LAN966X_ES0_CNT;
        es0->max_rule_count = VTSS_LAN966X_ES0_CNT;
        es0->entry_get = lan966x_es0_entry_get;
        es0->entry_add = lan966x_es0_entry_add;
        es0->entry_del = lan966x_es0_entry_del;
        es0->entry_move = lan966x_es0_entry_move;
        state->es0_entry_update = lan966x_es0_entry_update;
        state->es0_eflow_update = lan966x_es0_eflow_update;

        // ACL
        state->acl_policer_set = lan966x_acl_policer_set;
        state->acl_port_set = lan966x_acl_port_conf_set;
        state->acl_port_counter_get = lan966x_acl_port_counter_get;
        state->acl_port_counter_clear = lan966x_acl_port_counter_clear;
        state->acl_ace_add = lan966x_ace_add;
        state->acl_ace_del = lan966x_ace_del;
        state->acl_ace_counter_get = vtss_cmn_ace_counter_get;
        state->acl_ace_counter_clear = vtss_cmn_ace_counter_clear;
        state->range_commit = lan966x_vcap_range_commit;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan966x_vcap_init(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
