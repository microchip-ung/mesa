// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_MRP
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"

#if defined(VTSS_FEATURE_MRP)

vtss_rc vtss_mrp_add(const vtss_inst_t      inst,
                     const vtss_mrp_idx_t   mrp_idx,
                     const vtss_mrp_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    if (conf == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();

    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, conf->p_port)) != VTSS_RC_OK) {
        VTSS_E("Invalid p_port %u", conf->p_port);
        goto do_exit;
    }

    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, conf->s_port)) != VTSS_RC_OK) {
        VTSS_E("Invalid s_port %u", conf->s_port);
        goto do_exit;
    }

    rc = VTSS_FUNC(mrp.mrp_add, mrp_idx, conf);

do_exit:
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_get(const vtss_inst_t      inst,
                     const vtss_mrp_idx_t   mrp_idx,
                     vtss_mrp_conf_t        *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        // This may be called without the instance being active to get defaults.
        // defaults.
        *conf = vtss_state->mrp.data[mrp_idx].conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_del(const vtss_inst_t      inst,
                     const vtss_mrp_idx_t   mrp_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_del, mrp_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_ring_role_set(const vtss_inst_t           inst,
                               const vtss_mrp_idx_t        mrp_idx,
                               const vtss_mrp_ring_role_t  role)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_ring_role_set, mrp_idx, role);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_ring_role_get(const vtss_inst_t    inst,
                               const vtss_mrp_idx_t mrp_idx,
                               vtss_mrp_ring_role_t *const role)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || role == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->mrp.data[mrp_idx].active) {
            *role = vtss_state->mrp.data[mrp_idx].conf.ring_role;
        } else {
            VTSS_E("Instance %u is not active", mrp_idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_primary_port_set(const vtss_inst_t    inst,
                                  const vtss_mrp_idx_t mrp_idx,
                                  const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_primary_port_set, mrp_idx, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_primary_port_get(const vtss_inst_t    inst,
                                  const vtss_mrp_idx_t mrp_idx,
                                  vtss_port_no_t       *const port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || port_no == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->mrp.data[mrp_idx].active) {
            *port_no = vtss_state->mrp.data[mrp_idx].conf.p_port;
        } else {
            VTSS_E("Instance %u is not active", mrp_idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_ring_state_set(const vtss_inst_t           inst,
                                const vtss_mrp_idx_t        mrp_idx,
                                const vtss_mrp_ring_state_t state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_ring_state_set, mrp_idx, state);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_ring_state_get(const vtss_inst_t     inst,
                                const vtss_mrp_idx_t  mrp_idx,
                                vtss_mrp_ring_state_t *const state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || state == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->mrp.data[mrp_idx].active) {
            *state = vtss_state->mrp.data[mrp_idx].ring_state;
        } else {
            VTSS_E("Instance %u is not active", mrp_idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_in_ring_state_set(const vtss_inst_t           inst,
                                   const vtss_mrp_idx_t        mrp_idx,
                                   const vtss_mrp_ring_state_t state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_in_ring_state_set, mrp_idx, state);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_in_ring_state_get(const vtss_inst_t     inst,
                                   const vtss_mrp_idx_t  mrp_idx,
                                   vtss_mrp_ring_state_t *const state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || state == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->mrp.data[mrp_idx].active) {
            *state = vtss_state->mrp.data[mrp_idx].in_ring_state;
        } else {
            VTSS_E("Instance %u is not active", mrp_idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_port_state_set(const vtss_inst_t           inst,
                                const vtss_mrp_idx_t        mrp_idx,
                                const vtss_port_no_t        port,
                                const vtss_mrp_port_state_t state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_port_state_set, mrp_idx, port, state);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_port_state_get(const vtss_inst_t     inst,
                                const vtss_mrp_idx_t  mrp_idx,
                                const vtss_port_no_t  port_no,
                                vtss_mrp_port_state_t *const state)
{
    vtss_state_t    *vtss_state;
    vtss_mrp_data_t *mrp_data;
    vtss_rc         rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || state == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        mrp_data = &vtss_state->mrp.data[mrp_idx];
        if (mrp_data->active) {
            if (mrp_data->conf.p_port == port_no) {
                *state = mrp_data->p_port_state;
            }
            if (mrp_data->conf.s_port == port_no) {
                *state = mrp_data->s_port_state;
            }
            if (mrp_data->conf.i_port == port_no) {
                *state = mrp_data->i_port_state;
            }
        } else {
            VTSS_E("Instance %u is not active", mrp_idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_best_mrm_set(const vtss_inst_t         inst,
                              const vtss_mrp_idx_t      mrp_idx,
                              const vtss_mrp_best_mrm_t *const best)
{
    vtss_state_t    *vtss_state;
    vtss_rc         rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || best == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((rc = VTSS_FUNC(mrp.mrp_best_mrm_set, mrp_idx, best)) == VTSS_RC_OK) {
            vtss_state->mrp.data[mrp_idx].best_mrm = *best;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_best_mrm_get(const vtss_inst_t    inst,
                              const vtss_mrp_idx_t mrp_idx,
                              vtss_mrp_best_mrm_t  *const best)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || best == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->mrp.data->active) {
            *best = vtss_state->mrp.data[mrp_idx].best_mrm;
        } else {
            VTSS_E("Instance %u is not active", mrp_idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_tst_loc_conf_set(const vtss_inst_t             inst,
                                  const vtss_mrp_idx_t          mrp_idx,
                                  const vtss_mrp_tst_loc_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || conf == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_tst_loc_conf_set, mrp_idx, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_tst_loc_conf_get(const vtss_inst_t        inst,
                                  const vtss_mrp_idx_t     mrp_idx,
                                  vtss_mrp_tst_loc_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || conf == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        // This may be called without the instance being active to get defaults.
        *conf = vtss_state->mrp.data[mrp_idx].tst_loc_conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_tst_hitme_once(const vtss_inst_t    inst,
                                const vtss_mrp_idx_t mrp_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_tst_hitme_once, mrp_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_itst_hitme_once(const vtss_inst_t    inst,
                                 const vtss_mrp_idx_t mrp_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_itst_hitme_once, mrp_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_tst_copy_conf_set(const vtss_inst_t              inst,
                                   const vtss_mrp_idx_t           mrp_idx,
                                   const vtss_mrp_tst_copy_conf_t *const copy)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || copy == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_tst_copy_conf_set, mrp_idx, copy);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_tst_copy_conf_get(const vtss_inst_t        inst,
                                   const vtss_mrp_idx_t      mrp_idx,
                                   vtss_mrp_tst_copy_conf_t *const copy)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || copy == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->mrp.data->active) {
            *copy = vtss_state->mrp.data[mrp_idx].tst_copy_conf;
        } else {
            VTSS_E("Instance %u is not active", mrp_idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_status_get(const vtss_inst_t    inst,
                            const vtss_mrp_idx_t mrp_idx,
                            vtss_mrp_status_t    *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || status == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_status_get, mrp_idx, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_counters_get(const vtss_inst_t    inst,
                              const vtss_mrp_idx_t mrp_idx,
                              vtss_mrp_counters_t  *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT || counters == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_counters_get, mrp_idx, counters);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_counters_clear(const vtss_inst_t    inst,
                                const vtss_mrp_idx_t mrp_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_counters_clear, mrp_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_event_mask_set(const vtss_inst_t    inst,
                                const vtss_mrp_idx_t mrp_idx,
                                const u32            mask,
                                const BOOL           enable)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  mrp_idx %u  mask %u  enable %u", mrp_idx, mask, enable);

    if (mrp_idx >= VTSS_MRP_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((rc = VTSS_FUNC(mrp.mrp_event_mask_set, mrp_idx, mask, enable)) == VTSS_RC_OK) {
            if (enable) {
                vtss_state->mrp.data[mrp_idx].event_mask |= mask;
            } else {
                vtss_state->mrp.data[mrp_idx].event_mask &= ~mask;
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_event_mask_get(const vtss_inst_t    inst,
                                const vtss_mrp_idx_t mrp_idx,
                                u32                  *const mask)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if (mrp_idx >= VTSS_MRP_CNT || mask == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->mrp.data->active) {
            *mask = vtss_state->mrp.data[mrp_idx].event_mask;
        } else {
            VTSS_E("Instance %u is not active", mrp_idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mrp_event_get(const vtss_inst_t    inst,
                           const vtss_mrp_idx_t mrp_idx,
                           vtss_mrp_event_t     *const events)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if (mrp_idx >= VTSS_MRP_CNT || events == NULL) {
        return VTSS_RC_ERROR;
    }

    VTSS_D("Enter  mrp_idx %u  p_mask %u  s_mask %u", mrp_idx, events->p_mask, events->s_mask);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(mrp.mrp_event_get, mrp_idx, events);
    }
    VTSS_EXIT();
    return rc;
}

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_mrp_inst_create(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

#define YN(x) ((x) ? "Yes" : "No ")

static char *debug_mac_string(const vtss_mac_t *m)
{
    static char buf[20];

    VTSS_SPRINTF(buf, "%02X-%02X-%02X-%02X-%02X-%02X", m->addr[0], m->addr[1], m->addr[2], m->addr[3], m->addr[4], m->addr[5]);

    return buf;
}

static char *debug_ring_role_string(const vtss_mrp_ring_role_t role, BOOL in)
{
    switch (role) {
    case VTSS_MRP_RING_ROLE_DISABLED:
        return "DIS";
    case VTSS_MRP_RING_ROLE_CLIENT:
        return in ? "MIC" : "MRC";
    case VTSS_MRP_RING_ROLE_MANAGER:
        return in ? "MIM" : "MRM";
    }
    return "INVALID";
}

static char *debug_ring_state_string(const vtss_mrp_ring_state_t  state)
{
    switch (state) {
    case VTSS_MRP_RING_STATE_CLOSED:
        return "CLOSED";
    case VTSS_MRP_RING_STATE_OPEN:
        return "OPEN";
    }
    return "INVALID";
}

void vtss_mrp_debug_print(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info)
{
    u32                     i, div, mrp_idx;
    BOOL                    show, mrp, status;
    vtss_mrp_data_t         *mrp_data;
    vtss_mrp_tst_loc_conf_t *mrp_tst_loc_conf;
    u32                     mrp_event_mask;
    vtss_mrp_status_t       mrp_status;
    vtss_mrp_counters_t     mrp_counters;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_MRP)) {
        return;
    }

    div = 0;
    mrp_idx = 0;
    show = mrp = status = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show = (info->action == 0) ? TRUE : FALSE;

        if (info->action > 0) { /* This potentially is a MRP status action */
            for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
                mrp = (info->action / div == 1) ? TRUE : FALSE;
                status = (info->action / div == 2) ? TRUE : FALSE;
                if (mrp || status) {
                    break;
                }
            }
            if (mrp || status) {    /* Calculate the possible MRP/VOI index */
                mrp_idx = info->action % div;
            }
        }
    }

    if (show) {
        pr("MRP Debug Group action:\n");
        pr("    0: Show possible actions\n");
        pr("    1XXXX: Print MRP XXXX instance configurations. Without XXXX all MRPs are printed\n");
        pr("    2XXXX: Print MRP XXXX instance status. Without XXXX all MRPs are printed\n");
        pr("\n");
    }

    if (!info->has_action || mrp) { /* MRP configuration must be printed */
        pr("MRP instance Config:\n\n");

        for (i = 0; i < VTSS_MRP_CNT; ++i) {
            if (mrp && (div > 1) && (mrp_idx != i)) {   /* A specific MRP instance must be printed - this is not the one */
                continue;
            }
            if (info->full || vtss_state->mrp.data[i].active) {
                mrp_data = &vtss_state->mrp.data[i];
                mrp_tst_loc_conf = &vtss_state->mrp.data[i].tst_loc_conf;
                mrp_event_mask = vtss_state->mrp.data[i].event_mask;

                pr("MRP:%4u  active:%s  tst_loc_idx: %u  itst_loc_idx: %u  ring_role:%s  in_ring_role:%s%s  p_port:%u  s_port:%u  i_port:%d\n",
                   i,
                   YN(mrp_data->active),
                   mrp_data->tst_loc_idx,
                   mrp_data->itst_loc_idx,
                   debug_ring_role_string(mrp_data->conf.ring_role, FALSE),
                   debug_ring_role_string(mrp_data->conf.in_ring_role, TRUE),
                   mrp_data->conf.in_ring_role != VTSS_MRP_RING_ROLE_DISABLED ? mrp_data->conf.in_rc_mode ? "-RC" : "-LC" : "",
                   mrp_data->conf.p_port,
                   mrp_data->conf.s_port,
                   mrp_data->conf.i_port);
                pr("------------------------------------------------------------------\n");

                if (info->full || mrp_data->active) {
                    pr("ring_state:%s  in_ring_state:%s  mac:%s\n",
                       debug_ring_state_string(mrp_data->ring_state),
                       debug_ring_state_string(mrp_data->in_ring_state),
                       debug_mac_string(&mrp_data->conf.mac));
                    pr("-----\n");
                }

                if (info->full || mrp_data->active) {
                    pr("tst_interval:%u  tst_mon_count:%u  itst_interval:%u  itst_mon_count:%u\n",
                       mrp_tst_loc_conf->tst_interval,
                       mrp_tst_loc_conf->tst_mon_count,
                       mrp_tst_loc_conf->itst_interval,
                       mrp_tst_loc_conf->itst_mon_count);
                    pr("-----\n");
                }

                if (info->full || mrp_data->active) {
                    pr("EVENT enable:%4s  tst_loc:%s  itst_loc:%s\n",
                       YN(mrp_event_mask != VTSS_MRP_EVENT_MASK_NONE),
                       YN(mrp_event_mask &  VTSS_MRP_EVENT_MASK_TST_LOC),
                       YN(mrp_event_mask &  VTSS_MRP_EVENT_MASK_ITST_LOC));
                    pr("-----\n");
                }
                pr("\n");
            } /* full or allocated */
        } /* for to */
        pr("\n");
    } /* Print MRP configurations */

    if (!info->has_action || status) { /* MRP status must be printed */
        pr("MRP Status:\n\n");

        for (i = 0; i < VTSS_MRP_CNT; ++i) {
            if (status && (div > 1) && (mrp_idx != i)) {   /* A specific MRP must be printed - this is not the one */
                continue;
            }
            if (info->full || vtss_state->mrp.data[i].active) {
                mrp_data = &vtss_state->mrp.data[i];

                pr("MRP:%4u  active:%s  ring_role:%s  in_ring_role:%s%s  p_port:%u  s_port:%u  i_port:%d\n",
                   i,
                   YN(mrp_data->active),
                   debug_ring_role_string(mrp_data->conf.ring_role, FALSE),
                   debug_ring_role_string(mrp_data->conf.in_ring_role, TRUE),
                   mrp_data->conf.in_ring_role != VTSS_MRP_RING_ROLE_DISABLED ? mrp_data->conf.in_rc_mode ? "-RC" : "-LC" : "",
                   mrp_data->conf.p_port,
                   mrp_data->conf.s_port,
                   mrp_data->conf.i_port);
                pr("------------------------------------------------------------------\n");

                // Cannot get inactive status & counters without a trace error
                if (!vtss_state->mrp.data[i].active) {
                    continue;
                }

                if (VTSS_FUNC(mrp.mrp_status_get, i, &mrp_status) == VTSS_RC_OK) {
                    pr("MRP status:\n");
                    pr("p-port: tst_loc %s  itst_loc %s  mrp_seen %s  mrp_proc_seen %s  dmac_err_seen %s  vers_err_seen %s\n",
                       YN(mrp_status.p_status.tst_loc),
                       YN(mrp_status.p_status.itst_loc),
                       YN(mrp_status.p_status.mrp_seen),
                       YN(mrp_status.p_status.mrp_proc_seen),
                       YN(mrp_status.p_status.dmac_err_seen),
                       YN(mrp_status.p_status.vers_err_seen));
                    pr("s-port: tst_loc %s  itst_loc %s  mrp_seen %s  mrp_proc_seen %s  dmac_err_seen %s  vers_err_seen %s\n",
                       YN(mrp_status.s_status.tst_loc),
                       YN(mrp_status.s_status.itst_loc),
                       YN(mrp_status.s_status.mrp_seen),
                       YN(mrp_status.s_status.mrp_proc_seen),
                       YN(mrp_status.s_status.dmac_err_seen),
                       YN(mrp_status.s_status.vers_err_seen));
                    pr("i-port: tst_loc %s  itst_loc %s  mrp_seen %s  mrp_proc_seen %s  dmac_err_seen %s  vers_err_seen %s\n",
                       YN(mrp_status.i_status.tst_loc),
                       YN(mrp_status.i_status.itst_loc),
                       YN(mrp_status.i_status.mrp_seen),
                       YN(mrp_status.i_status.mrp_proc_seen),
                       YN(mrp_status.i_status.dmac_err_seen),
                       YN(mrp_status.i_status.vers_err_seen));
                    pr("-----\n");
                }

                if (VTSS_FUNC(mrp.mrp_counters_get, i, &mrp_counters) == VTSS_RC_OK) {
                    pr("MRP counters:\n");
                    pr("p-port: tst_rx_count %" PRIu64 "  itst_rx_count %" PRIu64 "\n",
                       mrp_counters.p_counters.tst_rx_count,
                       mrp_counters.p_counters.itst_rx_count);
                    pr("s-port: tst_rx_count %" PRIu64 "  itst_rx_count %" PRIu64 "\n",
                       mrp_counters.s_counters.tst_rx_count,
                       mrp_counters.s_counters.itst_rx_count);
                    pr("i-port: tst_rx_count %" PRIu64 "  itst_rx_count %" PRIu64 "\n",
                       mrp_counters.i_counters.tst_rx_count,
                       mrp_counters.i_counters.itst_rx_count);
                    pr("-----\n");
                }
                pr("\n");
            }
        }
    }
}

#undef YN

#endif  /* VTSS_FEATURE_MRP */
