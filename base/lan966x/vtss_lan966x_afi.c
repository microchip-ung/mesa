// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

static vtss_rc lan966x_afi_alloc(vtss_state_t *vtss_state, vtss_afi_frm_dscr_t *const dscr, vtss_afi_id_t *const afi_id)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_afi_free(vtss_state_t *vtss_state, vtss_afi_id_t afi_id)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_afi_hijack(vtss_state_t *vtss_state, vtss_afi_id_t afi_id)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_afi_link_state_change(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL *link_up)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_afi_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_init(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_afi_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_afi_state_t *state = &vtss_state->afi;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->alloc = lan966x_afi_alloc;
        state->free = lan966x_afi_free;
        state->hijack = lan966x_afi_hijack;
        state->link_state_change = lan966x_afi_link_state_change;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan966x_init(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
