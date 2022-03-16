// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_OAM
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"

#if defined(VTSS_FEATURE_VOP)

vtss_rc vtss_vop_conf_set(const vtss_inst_t       inst,
                          const vtss_vop_conf_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->oam.vop_conf = *conf;
        rc = VTSS_FUNC(oam.vop_conf_set, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vop_conf_get(const vtss_inst_t   inst,
                          vtss_vop_conf_t     *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  conf %p", conf);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        *conf = vtss_state->oam.vop_conf;
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_alloc(const vtss_inst_t            inst,
                       const vtss_voe_allocation_t  *const param,
                       vtss_voe_idx_t               *const voe_idx)
{
    vtss_state_t *vtss_state;
    vtss_oam_direction_t direction = VTSS_OAM_DIRECTION_DOWN;
    vtss_voe_type_t type = VTSS_VOE_TYPE_PORT;
    vtss_rc      rc;

    vtss_state = (inst == NULL ? vtss_default_inst : inst);     /* This is required as VTSS_CHIP_PORT is using vtss_state */
    if (VTSS_CHIP_PORT(param->port) >= VTSS_PORT_VOE_CNT) {
        VTSS_E("Invalid port %u", param->port);
        return VTSS_RC_ERROR;
    }

#if !defined(VTSS_ARCH_LAN966X)
    VTSS_D("Enter  type %d  port %u  direction %u  voe_idx %p", param->type, param->port, param->direction, voe_idx);

    if ((param->type != VTSS_VOE_TYPE_SERVICE) && (param->type != VTSS_VOE_TYPE_PORT)) {
        VTSS_E("Invalid type %u", param->type);
        return VTSS_RC_ERROR;
    }
    if ((param->direction != VTSS_OAM_DIRECTION_DOWN) && (param->direction != VTSS_OAM_DIRECTION_UP)) {
        VTSS_E("Invalid direction %u", param->direction);
        return VTSS_RC_ERROR;
    }
    direction = param->direction;
    type = param->type;
#else
    VTSS_D("Enter  port %u  voe_idx %p", param->port, voe_idx);
#endif

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_alloc, type, param->port, direction, voe_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_free(const vtss_inst_t     inst,
                      const vtss_voe_idx_t  voe_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d", voe_idx);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_free, voe_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_conf_set(const vtss_inst_t      inst,
                          const vtss_voe_idx_t   voe_idx,
                          const vtss_voe_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->oam.voe_conf[voe_idx] = *conf;
        rc = VTSS_FUNC(oam.voe_conf_set, voe_idx, conf);
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_voe_conf_get(const vtss_inst_t      inst,
                          const vtss_voe_idx_t   voe_idx,
                          vtss_voe_conf_t        *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->oam.voe_conf[voe_idx];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_cc_conf_set(const vtss_inst_t         inst,
                             const vtss_voe_idx_t      voe_idx,
                             const vtss_voe_cc_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->oam.voe_cc_conf[voe_idx] = *conf;
        rc = VTSS_FUNC(oam.voe_cc_conf_set, voe_idx, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_cc_conf_get(const vtss_inst_t      inst,
                             const vtss_voe_idx_t   voe_idx,
                             vtss_voe_cc_conf_t     *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->oam.voe_cc_conf[voe_idx];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_cc_rdi_set(const vtss_inst_t     inst,
                            const vtss_voe_idx_t  voe_idx,
                            const BOOL            rdi)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  rdi %u", voe_idx, rdi);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->oam.voe_rdi_conf[voe_idx] = rdi;
        rc = VTSS_FUNC(oam.voe_cc_rdi_set, voe_idx, rdi);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_cc_rdi_get(const vtss_inst_t     inst,
                            const vtss_voe_idx_t  voe_idx,
                            BOOL                  *rdi)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  rdi %p", voe_idx, rdi);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *rdi = vtss_state->oam.voe_rdi_conf[voe_idx];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_cc_cpu_copy_next_set(const vtss_inst_t     inst,
                                      const vtss_voe_idx_t  voe_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d", voe_idx);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_cc_cpu_copy_next_set, voe_idx);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_VOP_CFM)
vtss_rc vtss_voe_lt_conf_set(const vtss_inst_t          inst,
                             const vtss_voe_idx_t       voe_idx,
                             const vtss_voe_lt_conf_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->oam.voe_lt_conf[voe_idx] = *conf;
        rc = VTSS_FUNC(oam.voe_lt_conf_set, voe_idx, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_lt_conf_get(const vtss_inst_t      inst,
                             const vtss_voe_idx_t   voe_idx,
                             vtss_voe_lt_conf_t     *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->oam.voe_lt_conf[voe_idx];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_lb_conf_set(const vtss_inst_t          inst,
                             const vtss_voe_idx_t       voe_idx,
                             const vtss_voe_lb_conf_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->oam.voe_lb_conf[voe_idx] = *conf;
        rc = VTSS_FUNC(oam.voe_lb_conf_set, voe_idx, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_lb_conf_get(const vtss_inst_t      inst,
                             const vtss_voe_idx_t   voe_idx,
                             vtss_voe_lb_conf_t     *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->oam.voe_lb_conf[voe_idx];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_laps_conf_set(const vtss_inst_t            inst,
                               const vtss_voe_idx_t         voe_idx,
                               const vtss_voe_laps_conf_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->oam.voe_laps_conf[voe_idx] = *conf;
        rc = VTSS_FUNC(oam.voe_laps_conf_set, voe_idx, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_laps_conf_get(const vtss_inst_t      inst,
                               const vtss_voe_idx_t   voe_idx,
                               vtss_voe_laps_conf_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  conf %p", voe_idx, conf);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->oam.voe_laps_conf[voe_idx];
    }
    VTSS_EXIT();
    return rc;
}
#endif

vtss_rc vtss_voe_status_get(const vtss_inst_t     inst,
                            const vtss_voe_idx_t  voe_idx,
                            vtss_voe_status_t     *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  status %p", voe_idx, status);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_status_get, voe_idx, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_counters_get(const vtss_inst_t    inst,
                              const vtss_voe_idx_t voe_idx,
                              vtss_voe_counters_t  *counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  counters %p", voe_idx, counters);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_counters_get, voe_idx, counters);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_counters_clear(const vtss_inst_t     inst,
                               const vtss_voe_idx_t  voe_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d", voe_idx);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_counters_clear, voe_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_cc_status_get(const vtss_inst_t     inst,
                               const vtss_voe_idx_t  voe_idx,
                               vtss_voe_cc_status_t  *status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  status %p", voe_idx, status);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_cc_status_get, voe_idx, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_cc_counters_get(const vtss_inst_t     inst,
                                const vtss_voe_idx_t   voe_idx,
                                vtss_voe_cc_counters_t *counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  counters %p", voe_idx, counters);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_cc_counters_get, voe_idx, counters);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_cc_counters_clear(const vtss_inst_t     inst,
                                  const vtss_voe_idx_t  voe_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d", voe_idx);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_cc_counters_clear, voe_idx);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_VOP_CFM)
vtss_rc vtss_voe_lt_status_get(const vtss_inst_t     inst,
                               const vtss_voe_idx_t  voe_idx,
                               vtss_voe_lt_status_t  *status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  status %p", voe_idx, status);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_lt_status_get, voe_idx, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_lb_status_get(const vtss_inst_t     inst,
                               const vtss_voe_idx_t  voe_idx,
                               vtss_voe_lb_status_t  *status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  status %p", voe_idx, status);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_lb_status_get, voe_idx, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_lb_counters_get(const vtss_inst_t     inst,
                                const vtss_voe_idx_t   voe_idx,
                                vtss_voe_lb_counters_t *counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d  counters %p", voe_idx, counters);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_lb_counters_get, voe_idx, counters);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_lb_counters_clear(const vtss_inst_t     inst,
                                   const vtss_voe_idx_t  voe_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %d", voe_idx);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_lb_counters_clear, voe_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_laps_status_get(const vtss_inst_t       inst,
                                 const vtss_voe_idx_t    voe_idx,
                                 vtss_voe_laps_status_t  *status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter voe_idx %d  status %p", voe_idx, status);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_laps_status_get, voe_idx, status);
    }
    VTSS_EXIT();
    return rc;
}
#endif

vtss_rc vtss_voe_event_active_get(const vtss_inst_t   inst,
                                  const u32           active_size,
                                  u32                 *const active)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  active_size %u  active %p", active_size, active);

    if (active_size != VTSS_EVENT_MASK_ARRAY_SIZE) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_event_active_get, active_size, active);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_event_mask_set(const vtss_inst_t     inst,
                                const vtss_voe_idx_t  voe_idx,
                                const u32             mask,
                                const BOOL            enable)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %u  mask %u  enable %u", voe_idx, mask, enable);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (enable) {
            vtss_state->oam.voe_event_mask[voe_idx] |= mask;
        } else {
            vtss_state->oam.voe_event_mask[voe_idx] &= ~mask;
        }
        rc = VTSS_FUNC(oam.voe_event_mask_set, voe_idx, mask, enable);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_event_mask_get(const vtss_inst_t     inst,
                                const vtss_voe_idx_t  voe_idx,
                                u32                   *const mask)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %u  mask %p", voe_idx, mask);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *mask = vtss_state->oam.voe_event_mask[voe_idx];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voe_event_get(const vtss_inst_t     inst,
                           const vtss_voe_idx_t  voe_idx,
                           u32                   *const mask)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voe_idx %u  mask %p", voe_idx, mask);

    if (voe_idx >= VTSS_VOE_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voe_event_get, voe_idx, mask);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_VOP_V2)
vtss_rc vtss_voi_alloc(const vtss_inst_t            inst,
                       const vtss_voi_allocation_t  *const param,
                       vtss_voi_idx_t               *voi_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  direction %u  voi_idx %p", param->direction, voi_idx);

    if ((param->direction != VTSS_OAM_DIRECTION_DOWN) && (param->direction != VTSS_OAM_DIRECTION_UP)) {
        VTSS_E("Invalid direction %u", param->direction);
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voi_alloc, param->port, param->direction, voi_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voi_free(const vtss_inst_t       inst,
                      const vtss_voi_idx_t    voi_idx)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voi_idx %u", voi_idx);

    if (voi_idx >= VTSS_VOI_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(oam.voi_free, voi_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voi_conf_set(const vtss_inst_t       inst,
                          const vtss_voi_idx_t    voi_idx,
                          const vtss_voi_conf_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voi_idx %u  conf %p", voi_idx, conf);

    if (voi_idx >= VTSS_VOI_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->oam.voi_conf[voi_idx] = *conf;
        rc = VTSS_FUNC(oam.voi_conf_set, voi_idx, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_voi_conf_get(const vtss_inst_t      inst,
                          const vtss_voi_idx_t   voi_idx,
                          vtss_voi_conf_t        *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter  voi_idx %u  conf %p", voi_idx, conf);

    if (voi_idx >= VTSS_VOI_CNT) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->oam.voi_conf[voi_idx];
    }
    VTSS_EXIT();
    return rc;
}
#endif



/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_oam_inst_create(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

/* Compile time print of OAM ail data base size */
/*
char (*__kaboom)[((sizeof( vtss_voe_conf_t ) + sizeof( vtss_voe_cc_conf_t ) +
                   sizeof( vtss_voe_lt_conf_t ) + sizeof( vtss_voe_lb_conf_t ) +
                   sizeof( vtss_voe_laps_conf_t ) + sizeof( u32 )) * VTSS_VOE_CNT) +
                 (sizeof( vtss_voi_conf_t ) * VTSS_VOI_CNT) +
                 sizeof(vtss_vop_conf_t)];
void kaboom_print( void )
{
    printf( "%d", __kaboom );
}
*/

#define YN(x) ((x) ? "Yes" : "No ")

static char *debug_mac_string(const vtss_mac_t *m)
{
    static char buf[20];

    VTSS_SPRINTF(buf, "%02X-%02X-%02X-%02X-%02X-%02X", m->addr[0], m->addr[1], m->addr[2], m->addr[3], m->addr[4], m->addr[5]);

    return buf;
}

static char *debug_dmac_check_string(const vtss_voe_dmac_check_t  dmac_check)
{
    switch (dmac_check) {
        case VTSS_VOE_DMAC_CHECK_UNICAST:     return("UNICAST");
        case VTSS_VOE_DMAC_CHECK_MULTICAST:   return("MULTICAST");
        case VTSS_VOE_DMAC_CHECK_BOTH:        return("BOTH");
        case VTSS_VOE_DMAC_CHECK_NONE:        return("NONE");
    }
    return("INVALID");
}

static char *debug_cpu_copy_string(const vtss_oam_cpu_copy_t  cpu_copy)
{
    switch (cpu_copy) {
#if defined(VTSS_FEATURE_VOP_V2)
        case VTSS_OAM_CPU_COPY_AUTO:   return("AUTO");
#endif
        case VTSS_OAM_CPU_COPY_ALL:    return("ALL");
        case VTSS_OAM_CPU_COPY_NONE:   return("NONE");
    }
    return("INVALID");
}

#if defined(VTSS_FEATURE_VOP_V2)
static char *debug_raps_handling_string(const vtss_oam_raps_handling_t  raps_handling)
{
    switch (raps_handling) {
        case VTSS_OAM_RAPS_HANDLING_COPY_CPU:   return("COPY");
        case VTSS_OAM_RAPS_HANDLING_REDIR_CPU:  return("REDIR");
        case VTSS_OAM_RAPS_HANDLING_DISCARD:    return("DISCARD");
        case VTSS_OAM_RAPS_HANDLING_NONE:       return("NONE");
    }
    return("INVALID");
}
#endif

static char *debug_period_string(const vtss_voe_ccm_period_t  period)
{
    switch (period) {
        case VTSS_VOE_CCM_PERIOD_3_3_MS:   return("3.3MS");
        case VTSS_VOE_CCM_PERIOD_10_MS:    return("10MS");
        case VTSS_VOE_CCM_PERIOD_100_MS:   return("100MS");
        case VTSS_VOE_CCM_PERIOD_1_SEC:    return("1S");
#if defined(VTSS_FEATURE_VOP_V2)
        case VTSS_VOE_CCM_PERIOD_10_SEC:   return("10S");
#endif
    }
    return("INVALID");
}

static char *to_string(u8 *megid, u32 length)
{
    static char buf_ret[100];

    if (length > sizeof(buf_ret)) {
        length = sizeof(buf_ret);
    }

    VTSS_SNPRINTF(buf_ret, length, "%s", megid);

    return(buf_ret);
}

static char *debug_megid_string(u8  *megid)
{
    static char buf_ret[220];   /* Have to make this buffer extra long as the compiler generates warning when doing VTSS_SNPRINTF() if the composed string is longer than the buffer size !!! */
    u32 domain_length, name_length, name_off;

    if (megid[0] == 01) {   /* Maintenance name not present. */
        VTSS_SNPRINTF(buf_ret, sizeof(buf_ret), "%02u-%02u-%02u-%s", megid[0], megid[1], megid[2], &megid[3]);
    } else {   /* Maintenance name present.*/
        domain_length = megid[1];
        name_length = megid[3 + domain_length];
        name_off = 2 + domain_length;
        VTSS_SNPRINTF(buf_ret, sizeof(buf_ret), "%02u-%02u-%s-%02u-%02u-%s", megid[0], megid[1], to_string(&megid[2], domain_length),
                                                                        megid[name_off], megid[name_off+1], to_string(&megid[name_off+2], name_length));
    }
    return(buf_ret);
}

void vtss_oam_debug_print(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info)
{
    u32                     i, div, vo_idx;
    BOOL                    show, vop, voe, status, voi;
    vtss_vop_conf_t         *vop_conf = &vtss_state->oam.vop_conf;
    vtss_voe_alloc_t        *voe_alloc;
    vtss_voe_conf_t         *voe_conf;
    vtss_voe_cc_conf_t      *voe_cc_conf;
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_voe_lt_conf_t      *voe_lt_conf;
    vtss_voe_lb_conf_t      *voe_lb_conf;
    vtss_voe_laps_conf_t    *voe_laps_conf;
#endif
    u32                     voe_event_mask;
    vtss_voe_status_t       voe_status;
    vtss_voe_cc_status_t    cc_status;
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_voe_lt_status_t    lt_status;
    vtss_voe_lb_status_t    lb_status;
    vtss_voe_laps_status_t  laps_status;
#endif
    vtss_voe_counters_t     voe_counters;
    vtss_voe_cc_counters_t  cc_counters;
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_voe_lb_counters_t  lb_counters;
#endif
#if defined(VTSS_FEATURE_VOP_V2)
    vtss_voi_alloc_t        *voi_alloc;
    vtss_voi_conf_t         *voi_conf;
#endif

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_OAM))
        return;

    div = 0;
    vo_idx = 0;
    show = vop = voe = status = voi = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show = (info->action == 0) ? TRUE : FALSE;
        vop = (info->action == 1) ? TRUE : FALSE;

        if (info->action > 0) { /* This potentially is a VOE status action */
            for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
                voe = (info->action / div == 4) ? TRUE : FALSE;
                status = (info->action / div == 5) ? TRUE : FALSE;
                voi = (info->action / div == 10) ? TRUE : FALSE;
                if (voe || status || voi) {
                    break;
                }
            }
            if (voe || status || voi) {    /* Calculate the possible VOE/VOI index */
                vo_idx = info->action % div;
            }
        }
    }

    if (show) {
        pr("OAM Debug Group action:\n");
        pr("    0: Show possible actions\n");
        pr("    1: Print VOP configurations\n");
        pr("    4XXXX: Print VOE XXXX configurations. Without XXXX all VOEs are printed\n");
        pr("    5XXXX: Print VOE XXXX status. Without XXXX all VOEs are printed\n");
#if defined(VTSS_FEATURE_VOP_V2)
        pr("    10XXXX: Print VOI XXXX configurations. Without XXXX all VOIs are printed\n");
#endif
        pr("\n");
    }

    if (!info->has_action || vop) { /* VOP configuration must be printed */
        pr("VOP Config:\n\n");
    
        pr("Multicast MAC: %s\n", debug_mac_string(&vop_conf->multicast_dmac));

#if defined(VTSS_FEATURE_VOP_V2)
        pr("Auto copy: Period[0]:%u us Period[1]:%u us\n", vop_conf->auto_copy_period[0], vop_conf->auto_copy_period[1]);
        pr("Auto_Cp_CCM:     Period[%u]\n", vop_conf->auto_copy_ccm_valid & 1);
        pr("Auto_Cp_CCM_TLV: Period[%u]\n", vop_conf->auto_copy_ccm_tlv & 1);
        pr("Auto_Cp_CCM_err: Period[%u]\n", vop_conf->auto_copy_ccm_err & 1);
        pr("Auto_Cp_LBR:     Period[%u]\n", vop_conf->auto_copy_lbr & 1);
#endif

        pr("PDU extract:\n");
        pr("VOE CCM    RX queue %u\n", vop_conf->voe_queue_ccm);
#if !defined(VTSS_ARCH_LAN966X)
        pr("VOE LT     RX queue %u\n", vop_conf->voe_queue_lt);
        pr("VOE LBM    RX queue %u\n", vop_conf->voe_queue_lbm);
        pr("VOE LBR    RX queue %u\n", vop_conf->voe_queue_lbr);
        pr("VOE APS    RX queue %u\n", vop_conf->voe_queue_aps);
#endif
        pr("VOE ERROR  RX queue %u\n", vop_conf->voe_queue_err);
#if defined(VTSS_FEATURE_VOP_V2)
        pr("VOI        RX queue %u\n", vop_conf->voi_queue);
#endif
        pr("\n");
    } /* Print VOP configurations */

    if (!info->has_action || voe) { /* VOE configuration must be printed */
        pr("VOE Config:\n\n");
    
        for (i=0; i<VTSS_VOE_CNT; ++i) {
            if (voe && (div > 1) && (vo_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }
            if (info->full  ||  vtss_state->oam.voe_alloc_data[i].allocated) {
                voe_alloc = &vtss_state->oam.voe_alloc_data[i];
                voe_conf = &vtss_state->oam.voe_conf[i];
                voe_cc_conf = &vtss_state->oam.voe_cc_conf[i];
#if defined(VTSS_FEATURE_VOP_CFM)
                voe_lt_conf = &vtss_state->oam.voe_lt_conf[i];
                voe_lb_conf = &vtss_state->oam.voe_lb_conf[i];
                voe_laps_conf = &vtss_state->oam.voe_laps_conf[i];
#endif
                voe_event_mask = vtss_state->oam.voe_event_mask[i];

                pr("VOE:%4u  allocated:%s  type:%s  port:%u  direction:%s\n",
                   i,
                   YN(voe_alloc->allocated),
                   ((voe_alloc->type == VTSS_VOE_TYPE_SERVICE) ? "Service" : "Port"),
                   voe_alloc->port,
                   ((voe_alloc->direction == VTSS_OAM_DIRECTION_DOWN) ? "Down" : "Up"));
                pr("------------------------------------------------------------------\n");

                if (info->full  ||  voe_conf->enable) {
#if defined(VTSS_FEATURE_VOP_V2)
                    pr("enable:%4s  unicast_mac:%s  meg_level:%u  dmac_check_type:%s  loop_iflow_id: %u  block_mel_high:%s\n",
                       YN(voe_conf->enable),
                       debug_mac_string(&voe_conf->unicast_mac),
                       voe_conf->meg_level,
                       debug_dmac_check_string(voe_conf->dmac_check_type),
                       voe_conf->loop_iflow_id,
                       YN(voe_conf->block_mel_high));
#else
#if !defined(VTSS_ARCH_LAN966X)
                       pr("enable:%4s  unicast_mac:%s  meg_level:%u  dmac_check_type:%s  loop_iflow_id: %u\n",
                       YN(voe_conf->enable),
                       debug_mac_string(&voe_conf->unicast_mac),
                       voe_conf->meg_level,
                       debug_dmac_check_string(voe_conf->dmac_check_type),
                       voe_conf->loop_iflow_id);
#else
                       pr("enable:%4s  unicast_mac:%s  meg_level:%u  dmac_check_type:%s\n",
                       YN(voe_conf->enable),
                       debug_mac_string(&voe_conf->unicast_mac),
                       voe_conf->meg_level,
                       debug_dmac_check_string(voe_conf->dmac_check_type));
#endif
#endif
                    pr("-----\n");
                }

                if (info->full  ||  voe_cc_conf->enable) {
#if !defined(VTSS_ARCH_LAN966X)
                    pr("CC enable:%4s  cpu_copy:%s  seq_no_update:%s  count_as_selected:%s  period %s  prio:%u  peer_mepid %u  rdi_set %u\n",
                       YN(voe_cc_conf->enable),
                       debug_cpu_copy_string(voe_cc_conf->cpu_copy),
                       YN(voe_cc_conf->seq_no_update),
                       YN(voe_cc_conf->count_as_selected),
                       debug_period_string(voe_cc_conf->expected_period),
                       voe_cc_conf->expected_priority,
                       voe_cc_conf->expected_peer_mepid,
                       vtss_state->oam.voe_rdi_conf[i]);
#else
                    pr("CC enable:%4s  cpu_copy:%s  seq_no_update:%s  period %s  prio:%u  peer_mepid %u  rdi_set %u\n",
                       YN(voe_cc_conf->enable),
                       debug_cpu_copy_string(voe_cc_conf->cpu_copy),
                       YN(voe_cc_conf->seq_no_update),
                       debug_period_string(voe_cc_conf->expected_period),
                       voe_cc_conf->expected_priority,
                       voe_cc_conf->expected_peer_mepid,
                       vtss_state->oam.voe_rdi_conf[i]);
#endif
                    pr("          %4s  megid:%s\n", " ", debug_megid_string(voe_cc_conf->expected_megid));
                    pr("-----\n");
                }

#if defined(VTSS_FEATURE_VOP_CFM)
                if (info->full  ||  voe_lt_conf->enable) {
                    pr("LT enable:%4s  ltm_cpu_copy:%s  ltr_cpu_copy:%s  count_as_selected:%s\n",
                       YN(voe_lt_conf->enable),
                       YN(voe_lt_conf->ltm_cpu_copy),
                       YN(voe_lt_conf->ltr_cpu_copy),
                       YN(voe_lt_conf->count_as_selected));
                    pr("-----\n");
                }

                if (info->full  ||  voe_lb_conf->enable) {
                    pr("LB enable:%4s  lbm_cpu_copy:%s  lbr_cpu_copy:%s  trans_id_update %s  trans_id %u  count_as_selected:%s\n",
                       YN(voe_lb_conf->enable),
                       YN(voe_lb_conf->lbm_cpu_copy),
                       YN(voe_lb_conf->lbr_cpu_copy),
                       YN(voe_lb_conf->lbr_cpu_copy),
                       voe_lb_conf->trans_id,
                       YN(voe_lb_conf->count_as_selected));
                    pr("-----\n");
                }

                if (info->full  ||  voe_laps_conf->enable) {
                    pr("LAPS enable:%4s  cpu_copy:%s  count_as_selected:%s\n",
                       YN(voe_laps_conf->enable),
                       YN(voe_laps_conf->cpu_copy),
                       YN(voe_laps_conf->count_as_selected));
                    pr("-----\n");
                }
#endif
                if (info->full  ||  voe_conf->enable) {
#if defined(VTSS_FEATURE_VOP_V2)
                    pr("EVENT enable:%4s  scr_port:%s  tlv_port:%s  tlv_if:%s  period:%s  zero_period:%s  priority:%s  loc:%s  mep_id:%s  meg_id:%s  level:%s  rdi:%s\n",
                    YN(voe_event_mask != VTSS_VOE_EVENT_MASK_NONE),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_SRC_PORT_MOVE),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_TLV_PORT_STATUS),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_TLV_IF_STATUS),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_PERIOD),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_PRIORITY),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_LOC),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_MEP_ID),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_MEG_ID),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_MEG_LEVEL),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_RX_RDI));
#else
                    pr("EVENT enable:%4s  period:%s  zero_period:%s  priority:%s  loc:%s  mep_id:%s  meg_id:%s  level:%s  rdi:%s\n",
                    YN(voe_event_mask != VTSS_VOE_EVENT_MASK_NONE),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_PERIOD),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_PRIORITY),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_LOC),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_MEP_ID),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_MEG_ID),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_MEG_LEVEL),
                    YN(voe_event_mask &  VTSS_VOE_EVENT_MASK_CCM_RX_RDI));
#endif
                    pr("-----\n");
                }
                pr("\n");
            } /* full or allocated */
        } /* for to */
        pr("\n");
    } /* Print VOE configurations */

    if (!info->has_action || status) { /* VOE status must be printed */
        pr("VOE Status:\n\n");
    
        for (i=0; i<VTSS_VOE_CNT; ++i) {
            if (status && (div > 1) && (vo_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }
            if (info->full  ||  vtss_state->oam.voe_alloc_data[i].allocated) {
                voe_alloc = &vtss_state->oam.voe_alloc_data[i];
                voe_conf = &vtss_state->oam.voe_conf[i];

                pr("VOE:%4u  allocated:%s  type:%s  port:%u  direction:%s\n",
                   i,
                   YN(voe_alloc->allocated),
                   ((voe_alloc->type == VTSS_VOE_TYPE_SERVICE) ? "Service" : "Port"),
                   voe_alloc->port,
                   ((voe_alloc->direction == VTSS_OAM_DIRECTION_DOWN) ? "Down" : "Up"));
                pr("------------------------------------------------------------------\n");

                if (VTSS_FUNC(oam.voe_status_get, i, &voe_status) == VTSS_RC_OK &&
                    VTSS_FUNC(oam.voe_counters_get, i, &voe_counters) == VTSS_RC_OK) {
                    pr("VOE status:\n");
#if defined(VTSS_FEATURE_VOP_V2)
                    pr("opcode_unexp_seen %s  dmac_unexp_seen %s  tx_level_low_seen %s  version_unexp_seen %s  rx_level_low_seen %s  rx_level_high_seen %s\n",
                       YN(voe_status.opcode_unexp_seen),
                       YN(voe_status.dmac_unexp_seen),
                       YN(voe_status.tx_level_low_seen),
                       YN(voe_status.version_unexp_seen),
                       YN(voe_status.rx_level_low_seen),
                       YN(voe_status.rx_level_high_seen));
#else
                    pr("opcode_unexp_seen %s  dmac_unexp_seen %s\n",
                       YN(voe_status.opcode_unexp_seen),
                       YN(voe_status.dmac_unexp_seen));
#endif

#if defined(VTSS_FEATURE_VOP_V2)
                    pr("rx_counter %" PRIu64 "  tx_counter %" PRIu64 "  rx_selected_counter %" PRIu64 "  tx_selected_counter %" PRIu64 "  rx_discard_counter %" PRIu64 "  tx_discard_counter %" PRIu64 "\n",
                       voe_counters.rx_counter,
                       voe_counters.tx_counter,
                       voe_counters.rx_selected_counter,
                       voe_counters.tx_selected_counter,
                       voe_counters.rx_discard_counter,
                       voe_counters.tx_discard_counter);
#else
#if defined(VTSS_FEATURE_VOP_CFM)
                    pr("rx_counter %" PRIu64 "  tx_counter %" PRIu64 "\n",
                       voe_counters.rx_counter,
                       voe_counters.tx_counter);
#else
                    pr("rx_counter %" PRIu64 "\n",
                       voe_counters.rx_counter);
#endif
#endif
                    pr("-----\n");
                }

                if (VTSS_FUNC(oam.voe_cc_status_get, i, &cc_status) == VTSS_RC_OK &&
                    VTSS_FUNC(oam.voe_cc_counters_get, i, &cc_counters) == VTSS_RC_OK) {
                    pr("CC status:\n");
#if defined(VTSS_FEATURE_VOP_V2)
                    pr("zero_period %s  rdi %s  loc %s  period_unexp %s  priority_unexp %s  mep_id_unexp %s  meg_id_unexp %s  mel_unexp %s\n",
                       YN(cc_status.zero_period),
                       YN(cc_status.rdi),
                       YN(cc_status.loc),
                       YN(cc_status.period_unexp),
                       YN(cc_status.priority_unexp),
                       YN(cc_status.mep_id_unexp),
                       YN(cc_status.meg_id_unexp),
                       YN(cc_status.mel_unexp));
#else
                    pr("zero_period %s  rdi %s  loc %s  period_unexp %s  priority_unexp %s  mep_id_unexp %s  meg_id_unexp %s\n",
                       YN(cc_status.zero_period),
                       YN(cc_status.rdi),
                       YN(cc_status.loc),
                       YN(cc_status.period_unexp),
                       YN(cc_status.priority_unexp),
                       YN(cc_status.mep_id_unexp),
                       YN(cc_status.meg_id_unexp));
#endif
#if defined(VTSS_FEATURE_VOP_V2)
                    pr("seen %s  tlv_seen %s  seq_unexp_seen %s\n",
                       YN(cc_status.seen),
                       YN(cc_status.tlv_seen),
                       YN(cc_status.seq_unexp_seen));
#else
                    pr("seen %s\n",
                       YN(cc_status.seen));
#endif
#if defined(VTSS_FEATURE_VOP_V2)
                    pr("rx_port %u  port_status_tlv %u  if_status_tlv %u\n",
                       cc_status.rx_port,
                       cc_status.port_status_tlv,
                       cc_status.if_status_tlv);
#endif
                    pr("rx_valid_counter %" PRIu64 "  rx_invalid_counter %" PRIu64 "  rx_oo_counter %" PRIu64 "  tx_counter %" PRIu64 "\n",
                       cc_counters.rx_valid_counter,
                       cc_counters.rx_invalid_counter,
                       cc_counters.rx_oo_counter,
                       cc_counters.tx_counter);
                    pr("-----\n");
                }

#if defined(VTSS_FEATURE_VOP_CFM)
                if (VTSS_FUNC(oam.voe_lt_status_get, i, &lt_status) == VTSS_RC_OK) {
                    pr("LT status:\n");
                    pr("ltm_seen %s  ltr_seen %s\n",
                       YN(lt_status.ltm_seen),
                       YN(lt_status.ltr_seen));
                    pr("-----\n");
                }

                if (VTSS_FUNC(oam.voe_lb_status_get, i, &lb_status) == VTSS_RC_OK &&
                    VTSS_FUNC(oam.voe_lb_counters_get, i, &lb_counters) == VTSS_RC_OK) {
                    pr("LB status:\n");
#if defined(VTSS_FEATURE_VOP_V2)
                    pr("lbm_seen %s  lbr_seen %s  trans_unexp_seen %s\n",
                       YN(lb_status.lbm_seen),
                       YN(lb_status.lbr_seen),
                       YN(lb_status.trans_unexp_seen));
#else
                    pr("lbm_seen %s  lbr_seen %s\n",
                       YN(lb_status.lbm_seen),
                       YN(lb_status.lbr_seen));
#endif
                    pr("tx_trans_id %u  rx_trans_id %u\n",
                       lb_status.tx_trans_id,
                       lb_status.rx_trans_id);

#if defined(VTSS_FEATURE_VOP_V2)
                    pr("rx_lbr_counter %" PRIu64 "  tx_lbm_counter %" PRIu64 "  rx_lbr_oo_counter %" PRIu64 "  rx_lbr_crc_counter %" PRIu64 "  tx_lbr_counter %" PRIu64 "\n",
                       lb_counters.rx_lbr_counter,
                       lb_counters.tx_lbm_counter,
                       lb_counters.rx_lbr_oo_counter,
                       lb_counters.rx_lbr_crc_counter,
                       lb_counters.tx_lbr_counter);
#else
                    pr("rx_lbr_counter %" PRIu64 "  tx_lbm_counter %" PRIu64 "  rx_lbr_oo_counter %" PRIu64 "\n",
                       lb_counters.rx_lbr_counter,
                       lb_counters.tx_lbm_counter,
                       lb_counters.rx_lbr_oo_counter);
#endif
                    pr("-----\n");
                }

                if (VTSS_FUNC(oam.voe_laps_status_get, i, &laps_status) == VTSS_RC_OK) {
                    pr("LAPS status:\n");
                    pr("seen %s\n",
                       YN(laps_status.seen));
                    pr("-----\n");
                }
#endif
                pr("\n");
            }
        }
    }

#if defined(VTSS_FEATURE_VOP_V2)
    if (!info->has_action || voi) { /* VOI configuration must be printed */
        pr("VOI Config:\n\n");
    
        for (i=0; i<VTSS_VOI_CNT; ++i) {
            if (voi && (div > 1) && (vo_idx != i)) {   /* A specific VOI must be printed - this is not the one */
                continue;
            }
            if (info->full  ||  vtss_state->oam.voi_alloc_data[i].allocated) {
                voi_alloc = &vtss_state->oam.voi_alloc_data[i];
                voi_conf = &vtss_state->oam.voi_conf[i];

                pr("VOI:%4u  allocated:%s  port:%u  direction:%s\n",
                   i,
                   YN(voi_alloc->allocated),
                   voi_alloc->port,
                   ((voi_alloc->direction == VTSS_OAM_DIRECTION_DOWN) ? "Down" : "Up"));
                pr("------------------------------------------------------------------\n");

                if (info->full  ||  voi_conf->enable) {
                    pr("enable:%4s  unicast_mac:%s  meg_level:%u  lbm_cpu_redir: %s  ltm_cpu_redir: %s  raps_handle: %s\n",
                       YN(voi_conf->enable),
                       debug_mac_string(&voi_conf->unicast_mac),
                       voi_conf->meg_level,
                       YN(voi_conf->lbm_cpu_redir),
                       YN(voi_conf->ltm_cpu_redir),
                       debug_raps_handling_string(voi_conf->raps_handling));
                    pr("-----\n");
                }
                pr("\n");

            }
        }
    }
#endif
}

#undef YN

#endif  /* VTSS_FEATURE_VOP */
