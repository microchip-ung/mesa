// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_OAM
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X) && defined(VTSS_FEATURE_VOP)

static vtss_rc lan966x_vop_conf_set(vtss_state_t          *vtss_state,
                                    const vtss_vop_conf_t *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_event_active_get(vtss_state_t   *vtss_state,
                                            const u32      active_size,
                                            u32            *const active)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_event_mask_set(vtss_state_t          *vtss_state,
                                          const vtss_voe_idx_t  voe_idx,
                                          const u32             mask,
                                          const BOOL            enable)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_event_get(vtss_state_t          *vtss_state,
                                     const vtss_voe_idx_t  voe_idx,
                                     u32                   *const mask)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_alloc(vtss_state_t                *vtss_state,
                                 const vtss_voe_type_t       type,
                                 const vtss_port_no_t        port,
                                 const vtss_oam_direction_t  direction,
                                 vtss_voe_idx_t              *const voe_idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_free(vtss_state_t          *vtss_state,
                                const vtss_voe_idx_t  voe_idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_conf_set(vtss_state_t           *vtss_state,
                                    const vtss_voe_idx_t   voe_idx,
                                    const vtss_voe_conf_t  *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_conf_set(vtss_state_t              *vtss_state,
                                       const vtss_voe_idx_t      voe_idx,
                                       const vtss_voe_cc_conf_t  *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_rdi_set(vtss_state_t          *vtss_state,
                                      const vtss_voe_idx_t  voe_idx,
                                      const BOOL            rdi)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_cpu_copy_next_set(vtss_state_t          *vtss_state,
                                                const vtss_voe_idx_t  voe_idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_lt_conf_set(vtss_state_t               *vtss_state,
                                       const vtss_voe_idx_t       voe_idx,
                                       const vtss_voe_lt_conf_t   *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_lb_conf_set(vtss_state_t               *vtss_state,
                                       const vtss_voe_idx_t       voe_idx,
                                       const vtss_voe_lb_conf_t   *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_laps_conf_set(vtss_state_t                 *vtss_state,
                                         const vtss_voe_idx_t         voe_idx,
                                         const vtss_voe_laps_conf_t   *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_status_get(vtss_state_t          *vtss_state,
                                      const vtss_voe_idx_t  voe_idx,
                                      vtss_voe_status_t     *const status)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_status_get(vtss_state_t          *vtss_state,
                                         const vtss_voe_idx_t  voe_idx,
                                         vtss_voe_cc_status_t  *status)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_lt_status_get(vtss_state_t           *vtss_state,
                                         const vtss_voe_idx_t   voe_idx,
                                         vtss_voe_lt_status_t   *status)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_lb_status_get(vtss_state_t         *vtss_state,
                                         const vtss_voe_idx_t voe_idx,
                                         vtss_voe_lb_status_t *status)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_laps_status_get(vtss_state_t             *vtss_state,
                                           const vtss_voe_idx_t     voe_idx,
                                           vtss_voe_laps_status_t   *status)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_counters_get(vtss_state_t         *vtss_state,
                                        const vtss_voe_idx_t voe_idx,
                                        vtss_voe_counters_t  *const counters)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_counters_get(vtss_state_t           *vtss_state,
                                           const vtss_voe_idx_t   voe_idx,
                                           vtss_voe_cc_counters_t *counters)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_lb_counters_get(vtss_state_t           *vtss_state,
                                           const vtss_voe_idx_t   voe_idx,
                                           vtss_voe_lb_counters_t *counters)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_counters_clear(vtss_state_t          *vtss_state,
                                          const vtss_voe_idx_t  voe_idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_counters_clear(vtss_state_t          *vtss_state,
                                             const vtss_voe_idx_t  voe_idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_lb_counters_clear(vtss_state_t          *vtss_state,
                                             const vtss_voe_idx_t  voe_idx)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_oam_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_oam_voe_poll_1sec(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_init(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_oam_state_t *state = &vtss_state->oam;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->vop_conf_set = lan966x_vop_conf_set;
        state->voe_event_active_get = lan966x_voe_event_active_get;
        state->voe_event_mask_set = lan966x_voe_event_mask_set;
        state->voe_event_get = lan966x_voe_event_get;
        state->voe_alloc = lan966x_voe_alloc;
        state->voe_free = lan966x_voe_free;
        state->voe_conf_set = lan966x_voe_conf_set;
        state->voe_cc_conf_set = lan966x_voe_cc_conf_set;
        state->voe_cc_rdi_set = lan966x_voe_cc_rdi_set;
        state->voe_cc_cpu_copy_next_set = lan966x_voe_cc_cpu_copy_next_set;
        state->voe_lt_conf_set = lan966x_voe_lt_conf_set;
        state->voe_lb_conf_set = lan966x_voe_lb_conf_set;
        state->voe_laps_conf_set = lan966x_voe_laps_conf_set;
        state->voe_status_get = lan966x_voe_status_get;
        state->voe_cc_status_get = lan966x_voe_cc_status_get;
        state->voe_lt_status_get = lan966x_voe_lt_status_get;
        state->voe_lb_status_get = lan966x_voe_lb_status_get;
        state->voe_laps_status_get = lan966x_voe_laps_status_get;
        state->voe_counters_get = lan966x_voe_counters_get;
        state->voe_cc_counters_get = lan966x_voe_cc_counters_get;
        state->voe_lb_counters_get = lan966x_voe_lb_counters_get;
        state->voe_counters_clear = lan966x_voe_counters_clear;
        state->voe_cc_counters_clear = lan966x_voe_cc_counters_clear;
        state->voe_lb_counters_clear = lan966x_voe_lb_counters_clear;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan966x_init(vtss_state));
        break;

    case VTSS_INIT_CMD_POLL:
        VTSS_RC(lan966x_oam_voe_poll_1sec(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
