// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)
static vtss_rc lan966x_qos_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_conf_set(vtss_state_t *vtss_state, BOOL changed)
{
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
static vtss_rc lan966x_evc_policer_conf_set(vtss_state_t *vtss_state,
                                            const vtss_evc_policer_id_t policer_id)
{
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
static vtss_rc lan966x_qos_cpu_port_shaper_set(vtss_state_t *vtss_state, const vtss_bitrate_t rate)
{
    return VTSS_RC_OK;
}
#endif

static vtss_rc lan966x_qos_status_get(vtss_state_t *vtss_state, vtss_qos_status_t *status)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

vtss_rc vtss_lan966x_qos_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

vtss_rc vtss_lan966x_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_qos_state_t *state = &vtss_state->qos;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->conf_set = lan966x_qos_conf_set;
        state->port_conf_set = vtss_cmn_qos_port_conf_set;
        state->port_conf_update = lan966x_qos_port_conf_set;
        state->status_get = lan966x_qos_status_get;
        state->qce_add = vtss_cmn_qce_add;
        state->qce_del = vtss_cmn_qce_del;
#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
        state->cpu_port_shaper_set = lan966x_qos_cpu_port_shaper_set;
#endif
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
        state->evc_policer_conf_set = lan966x_evc_policer_conf_set;
#endif
        //TBD: state->evc_policer_max = 1022;
        //TBD: state->prio_count = LAN966X_PRIOS;
        break;

    case VTSS_INIT_CMD_INIT:
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        break;

    case VTSS_INIT_CMD_POLL:
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
