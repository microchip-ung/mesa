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
    vtss_vcap_obj_t             *obj = &vtss_state->vcap.is2.obj;
    vtss_vcap_user_t            user = VTSS_IS2_USER_ACL;
    vtss_vcap_data_t            data;
    vtss_is2_data_t             *is2 = &data.u.is2;
    vtss_is2_entry_t            entry;
    vtss_res_chg_t              chg;
    const vtss_ace_udp_tcp_t    *sport = NULL, *dport = NULL;
    vtss_vcap_range_chk_table_t range_new = vtss_state->vcap.range;
    BOOL                        sip_smac_new = 0, sip_smac_old = 0;
    vtss_port_no_t              port_no;
    vtss_vcap_key_size_t        key_size = VTSS_VCAP_KEY_SIZE_HALF;

    // Check the simple things
    VTSS_RC(vtss_cmn_ace_add(vtss_state, ace_id, ace));

    if (ace->type == VTSS_ACE_TYPE_IPV6 && ace->type_ext) {
        // Encode as IPv6 is full rule
        key_size = VTSS_VCAP_KEY_SIZE_FULL;
    }

    // Check that half entry can be added
    memset(&chg, 0, sizeof(chg));
    chg.add_key[key_size] = 1;
    if (vtss_vcap_lookup(vtss_state, obj, user, ace->id, &data, NULL) == VTSS_RC_OK) {
        chg.del_key[data.key_size] = 1;

        // Free any old range checkers
        VTSS_RC(vtss_vcap_range_free(&range_new, is2->srange));
        VTSS_RC(vtss_vcap_range_free(&range_new, is2->drange));

        // Lookup SIP/SMAC rule
        if (vtss_vcap_lookup(vtss_state, obj, VTSS_IS2_USER_ACL_SIP, ace->id,
                             NULL, NULL) == VTSS_RC_OK) {
            sip_smac_old = 1;
            chg.del_key[VTSS_VCAP_KEY_SIZE_QUARTER] = 1;
        }
    }

    if (ace->type == VTSS_ACE_TYPE_IPV4) {
        if (ace->frame.ipv4.sip_smac.enable) {
            // SMAC_SIP4 rule needed
            sip_smac_new = 1;
            chg.add_key[VTSS_VCAP_KEY_SIZE_QUARTER] = 1;
        }
        if (vtss_vcap_udp_tcp_rule(&ace->frame.ipv4.proto)) {
            sport = &ace->frame.ipv4.sport;
            dport = &ace->frame.ipv4.dport;
        }
    }
    if (ace->type == VTSS_ACE_TYPE_IPV6 && vtss_vcap_udp_tcp_rule(&ace->frame.ipv6.proto)) {
        sport = &ace->frame.ipv6.sport;
        dport = &ace->frame.ipv6.dport;
    }
    VTSS_RC(vtss_cmn_vcap_res_check(obj, &chg));

    vtss_vcap_is2_init(&data, &entry);
    if (sport && dport) {
        // Allocate new range checkers
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->srange, sport, 1));
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->drange, dport, 0));
    }

    // Commit range checkers
    VTSS_RC(vtss_vcap_range_commit(vtss_state, &range_new));

    // Add main entry
    entry.first = 1;
    entry.ace = *ace;
    if (sip_smac_new) {
        entry.host_match = 1;
        entry.ace.frame.ipv4.sip.value = ace->frame.ipv4.sip_smac.sip;
        entry.ace.frame.ipv4.sip.mask = 0xffffffff;
    }
    data.key_size = key_size;
    if (ace->action.port_action == VTSS_ACL_PORT_ACTION_REDIR) {
        is2->action.redir = 1;
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (ace->action.port_list[port_no]) {
                VTSS_PORT_BF_SET(is2->action.member, port_no, 1);
            }
        }
    }
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, ace->id, ace_id, &data, 0));
    is2->action.redir = 0;

    // Add/delete SIP/SMAC entry
    user = VTSS_IS2_USER_ACL_SIP;
    if (sip_smac_new) {
        data.key_size = VTSS_VCAP_KEY_SIZE_QUARTER;
        VTSS_RC(vtss_vcap_add(vtss_state, obj, user, ace->id, VTSS_VCAP_ID_LAST, &data, 0));
    } else if (sip_smac_old) {
        VTSS_RC(vtss_vcap_del(vtss_state, obj, user, ace->id));
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ace_del(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    // Delete main entry
    VTSS_RC(vtss_cmn_ace_del(vtss_state, ace_id));

    // Delete SIP/SMAC entry
    VTSS_RC(vtss_vcap_del(vtss_state, &vtss_state->vcap.is2.obj, VTSS_IS2_USER_ACL_SIP, ace_id));
    return VTSS_RC_OK;
}

static vtss_rc lan966x_vcap_range_commit(vtss_state_t *vtss_state)
{
    u32                   i, type;
    vtss_vcap_range_chk_t *entry;

    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        entry = &vtss_state->vcap.range.entry[i];
        switch (entry->type) {
        case VTSS_VCAP_RANGE_TYPE_SPORT:
            type = 2;
            break;
        case VTSS_VCAP_RANGE_TYPE_DPORT:
            type = 1;
            break;
        case VTSS_VCAP_RANGE_TYPE_SDPORT:
            type = 3;
            break;
        case VTSS_VCAP_RANGE_TYPE_VID:
            type = 4;
            break;
        case VTSS_VCAP_RANGE_TYPE_DSCP:
            type = 5;
            break;
        default:
            if (entry->count == 0) {
                type = 0;
                break;
            } else {
                VTSS_E("illegal type: %d", entry->type);
                return VTSS_RC_ERROR;
            }
        }
        REG_WR(ANA_VCAP_RNG_CFG(i), ANA_VCAP_RNG_CFG_CFG(type));
        REG_WR(ANA_VCAP_RNG_VAL_CFG(i),
               ANA_VCAP_RNG_VAL_CFG_MIN_VAL(entry->min) |
               ANA_VCAP_RNG_VAL_CFG_MAX_VAL(entry->max));
    }
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
