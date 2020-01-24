// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

/* ================================================================= *
 *  Register access
 * ================================================================= */
void vtss_lan966x_reg_error(const char *file, int line) {
    printf("\n\nFATAL ERROR at %s:%d> Index exceed replication!\n\n", file, line);
    vtss_callout_trace_printf(VTSS_TRACE_LAYER, VTSS_TRACE_GROUP_DEFAULT,
                              VTSS_TRACE_LEVEL_ERROR, file, line, file,
                              "Index exceed replication!");
}

/* Read target register using current CPU interface */
static inline vtss_rc lan966x_rd_direct(vtss_state_t *vtss_state, u32 reg, u32 *value)
{
    return vtss_state->init_conf.reg_read(0, reg, value);
}

/* Write target register using current CPU interface */
static inline vtss_rc lan966x_wr_direct(vtss_state_t *vtss_state, u32 reg, u32 value)
{
    return vtss_state->init_conf.reg_write(0, reg, value);
}

vtss_rc (*vtss_lan966x_wr)(vtss_state_t *vtss_state, u32 addr, u32 value) = lan966x_wr_direct;
vtss_rc (*vtss_lan966x_rd)(vtss_state_t *vtss_state, u32 addr, u32 *value) = lan966x_rd_direct;

/* Read-modify-write target register using current CPU interface */
vtss_rc vtss_lan966x_wrm(vtss_state_t *vtss_state, u32 reg, u32 value, u32 mask)
{
    vtss_rc rc;
    u32     val;

    if ((rc = vtss_lan966x_rd(vtss_state, reg, &val)) == VTSS_RC_OK) {
        val = ((val & ~mask) | (value & mask));
        rc = vtss_lan966x_wr(vtss_state, reg, val);
    }
    return rc;
}

/* ================================================================= *
 *  Utility functions
 * ================================================================= */
u32 vtss_lan966x_port_mask(vtss_state_t *vtss_state, const BOOL member[])
{
    vtss_port_no_t port_no;
    u32            port, mask = 0;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (member[port_no]) {
            port = VTSS_CHIP_PORT(port_no);
            mask |= VTSS_BIT(port);
        }
    }
    return mask;
}

/* ================================================================= *
 *  Debug print utility functions
 * ================================================================= */

void vtss_lan966x_debug_print_port_header(vtss_state_t *vtss_state,
                                          const vtss_debug_printf_t pr, const char *txt)
{
    vtss_debug_print_port_header(vtss_state, pr, txt, VTSS_CHIP_PORTS + 1, 1);
}

void vtss_lan966x_debug_print_mask(const vtss_debug_printf_t pr, u32 mask)
{
    u32 port;

    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        pr("%s%s", port == 0 || (port & 7) ? "" : ".", ((1<<port) & mask) ? "1" : "0");
    }
    pr("  0x%08x\n", mask);
}

void vtss_lan966x_debug_reg_header(const vtss_debug_printf_t pr, const char *name)
{
    char buf[64];

    sprintf(buf, "%-32s  Addr   ", name);
    vtss_debug_print_reg_header(pr, buf);
}

void vtss_lan966x_debug_reg(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr, u32 addr, const char *name)
{
    u32 value;
    char buf[200];

    if (vtss_lan966x_rd(vtss_state, addr, &value) == VTSS_RC_OK) {
        sprintf(buf, "%-32s  0x%08x", name, addr);
        vtss_debug_print_reg(pr, buf, value);
    }
}

void vtss_lan966x_debug_reg_inst(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name)
{
    char buf[64];

    sprintf(buf, "%s_%u", name, i);
    vtss_lan966x_debug_reg(vtss_state, pr, addr, buf);
}

/* ================================================================= *
 *  Debug print
 * ================================================================= */
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

#if defined(VTSS_FEATURE_TIMESTAMP)
    /* Initialize TS */
    VTSS_RC(vtss_lan966x_ts_init(vtss_state, cmd));
#endif

#if defined(VTSS_FEATURE_VOP)
/* Initialize OAM */
    VTSS_RC(vtss_lan966x_oam_init(vtss_state, cmd));
#endif

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
    u32 val;

    REG_RD(GCB_BUILDID, &val);
    if (val != LAN966x_BUILD_ID) {
        VTSS_E("Unexpected build id. Got: %08x Expected %08x", val, LAN966x_BUILD_ID);
        return VTSS_RC_ERROR;
    }

    VTSS_FUNC_RC(misc.chip_id_get, &vtss_state->misc.chip_id);

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
