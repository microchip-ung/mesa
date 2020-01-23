// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

vtss_rc vtss_lan966x_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_max_tags_t  max_tags = vtss_state->port.conf[port_no].max_tags;
    vtss_vlan_port_type_t vlan_type = vtss_state->l2.vlan_port_conf[port_no].port_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    u32                   etype, aware;

    /* S-ports and VLAN unaware ports both suport 0x88a8 (in addition to 0x8100) */
    etype = (vlan_type == VTSS_VLAN_PORT_TYPE_S_CUSTOM ? vtss_state->l2.vlan_conf.s_etype :
             vlan_type == VTSS_VLAN_PORT_TYPE_C ? VTSS_ETYPE_TAG_C : VTSS_ETYPE_TAG_S);
    aware = (max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1);
    REG_WR(DEV_MAC_TAGS_CFG(port),
           DEV_MAC_TAGS_CFG_TAG_ID(etype) |
           (aware? DEV_MAC_TAGS_CFG_VLAN_AWR_ENA_M : 0) |
           DEV_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA_M);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_clause_37_control_get(vtss_state_t *vtss_state,
                                                  const vtss_port_no_t port_no,
                                                  vtss_port_clause_37_control_t *const control)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_clause_37_control_set(vtss_state_t *vtss_state,
                                                  const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_clause_37_status_get(vtss_state_t *vtss_state,
                                                 const vtss_port_no_t         port_no,
                                                 vtss_port_clause_37_status_t *const status)
{
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SYNCE)
static vtss_rc lan966x_synce_clock_out_set(vtss_state_t *vtss_state, const u32 clk_port)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_synce_clock_in_set(vtss_state_t *vtss_state, const u32 clk_port)
{
    return VTSS_RC_OK;
}
#endif

static vtss_rc lan966x_miim_read_write(vtss_state_t *vtss_state,
                                       BOOL read,
                                       u32 miim_controller,
                                       u8 miim_addr,
                                       u8 addr,
                                       u16 *value,
                                       BOOL report_errors)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_miim_read(vtss_state_t *vtss_state,
                                 vtss_miim_controller_t miim_controller,
                                 u8 miim_addr,
                                 u8 addr,
                                 u16 *value,
                                 BOOL report_errors)
{
    return lan966x_miim_read_write(vtss_state, TRUE, miim_controller, miim_addr, addr, value, report_errors);
}

static vtss_rc lan966x_miim_write(vtss_state_t *vtss_state,
                                  vtss_miim_controller_t miim_controller,
                                  u8 miim_addr,
                                  u8 addr,
                                  u16 value,
                                  BOOL report_errors)
{
    return lan966x_miim_read_write(vtss_state, FALSE, miim_controller, miim_addr, addr, &value, report_errors);
}

static vtss_rc lan966x_mmd_read(vtss_state_t *vtss_state,
                                vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                u16 addr, u16 *value, BOOL report_errors)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mmd_write(vtss_state_t *vtss_state,
                                 vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                 u16 addr, u16 value, BOOL report_errors)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mmd_read_inc(vtss_state_t *vtss_state,
                                    vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                    u16 addr, u16 *buf, u8 count, BOOL report_errors)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_conf_get(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no, vtss_port_conf_t *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}


static vtss_rc lan966x_port_ifh_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_status_get(vtss_state_t *vtss_state,
                                       const vtss_port_no_t  port_no,
                                       vtss_port_status_t    *const status)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_basic_counters_get(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no,
                                               vtss_basic_counters_t *const counters)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_counters_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_counters_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_counters_get(vtss_state_t *vtss_state,
                                         const vtss_port_no_t port_no,
                                         vtss_port_counters_t *const counters)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_forward_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_test_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_buf_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

vtss_rc vtss_lan966x_port_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

vtss_rc vtss_lan966x_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_port_state_t *state = &vtss_state->port;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->miim_read = lan966x_miim_read;
        state->miim_write = lan966x_miim_write;
        state->mmd_read = lan966x_mmd_read;
        state->mmd_read_inc = lan966x_mmd_read_inc;
        state->mmd_write = lan966x_mmd_write;
        state->conf_get = lan966x_port_conf_get;
        state->conf_set = lan966x_port_conf_set;
        state->clause_37_status_get = lan966x_port_clause_37_status_get;
        state->clause_37_control_get = lan966x_port_clause_37_control_get;
        state->clause_37_control_set = lan966x_port_clause_37_control_set;
        state->status_get = lan966x_port_status_get;
        state->counters_update = lan966x_port_counters_update;
        state->counters_clear = lan966x_port_counters_clear;
        state->counters_get = lan966x_port_counters_get;
        state->basic_counters_get = lan966x_port_basic_counters_get;
        state->ifh_set = lan966x_port_ifh_set;
        state->forward_set = lan966x_port_forward_set;
        state->test_conf_set = lan966x_port_test_conf_set;
#if defined(VTSS_FEATURE_SYNCE)
        vtss_state->synce.clock_out_set = lan966x_synce_clock_out_set;
        vtss_state->synce.clock_in_set = lan966x_synce_clock_in_set;
#endif
        break;

    case VTSS_INIT_CMD_INIT:
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(lan966x_port_buf_conf_set(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
