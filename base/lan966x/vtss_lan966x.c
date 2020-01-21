// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

static vtss_rc lan966x_debug_info_print(vtss_state_t *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    /* Initialize ports */
    VTSS_RC(vtss_lan966x_port_init(vtss_state, cmd));

    /* Initialize miscellaneous */
    VTSS_RC(vtss_lan966x_misc_init(vtss_state, cmd));

    /* Initialize packet and AFI */
    VTSS_RC(vtss_lan966x_packet_init(vtss_state, cmd));
    VTSS_RC(vtss_lan966x_afi_init(vtss_state, cmd));

    /* Initialize L2 */
    VTSS_RC(vtss_lan966x_l2_init(vtss_state, cmd));

    /* Initialize VCAP */
    VTSS_RC(vtss_lan966x_vcap_init(vtss_state, cmd));

    /* Initialize QoS */
    VTSS_RC(vtss_lan966x_qos_init(vtss_state, cmd));

    /* Initialize TS */
    VTSS_RC(vtss_lan966x_ts_init(vtss_state, cmd));

    /* Initialize OAM */
    VTSS_RC(vtss_lan966x_oam_init(vtss_state, cmd));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_map_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_restart_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_init_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_register_access_mode_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_inst_create(vtss_state_t *vtss_state)
{
    /* Initialization */
    vtss_state->cil.init_conf_set = lan966x_init_conf_set;
    vtss_state->cil.register_access_mode_set = lan966x_register_access_mode_set;
    vtss_state->cil.restart_conf_set = lan966x_restart_conf_set;
    vtss_state->cil.debug_info_print = lan966x_debug_info_print;
    vtss_state->port.map_set = lan966x_port_map_set;

    /* Create function groups */
    return vtss_lan966x_init_groups(vtss_state, VTSS_INIT_CMD_CREATE);
}
#endif /* VTSS_ARCH_LAN966X */
