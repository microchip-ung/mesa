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
    u32 value, port = VTSS_CHIP_PORT(port_no);

    REG_RD(DEV_PCS1G_ANEG_CFG(port), &value);
    control->enable = VTSS_BOOL(value & DEV_PCS1G_ANEG_CFG_ENA_M);
    value = DEV_PCS1G_ANEG_CFG_ADV_ABILITY(control->enable ? value : 0);
    VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &control->advertisement));
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_clause_37_control_set(vtss_state_t *vtss_state,
                                                  const vtss_port_no_t port_no)
{
    vtss_port_clause_37_control_t *control = &vtss_state->port.clause_37[port_no];
    u32                           value, port = VTSS_CHIP_PORT(port_no);

    /* Aneg capabilities for this port */
    VTSS_RC(vtss_cmn_port_clause_37_adv_set(&value, &control->advertisement, control->enable));

    /* Set aneg capabilities */
    REG_WR(DEV_PCS1G_ANEG_CFG(port),
           DEV_PCS1G_ANEG_CFG_ADV_ABILITY(value) |
           DEV_PCS1G_ANEG_CFG_RESTART_ONE_SHOT_M |
           (control->enable ? DEV_PCS1G_ANEG_CFG_ENA_M : 0));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_clause_37_status_get(vtss_state_t *vtss_state,
                                                 const vtss_port_no_t         port_no,
                                                 vtss_port_clause_37_status_t *const status)
{
    u32                           value, port = VTSS_CHIP_PORT(port_no);
    vtss_port_sgmii_aneg_t        *sgmii_adv = &status->autoneg.partner_adv_sgmii;
    BOOL                          synced_status;
    vtss_port_clause_37_control_t *aneg = &vtss_state->port.clause_37[port_no];
    vtss_port_interface_t         if_type = vtss_state->port.conf[port_no].if_type;

    if (vtss_state->port.conf[port_no].power_down) {
        status->link = 0;
        return VTSS_RC_OK;
    }

    /* Get the link state 'down' sticky bit  */
    REG_RD(DEV_PCS1G_STICKY(port), &value);
    status->link = (value & DEV_PCS1G_STICKY_LINK_DOWN_STICKY_M ? 0 : 1);
    REG_RD(DEV_PCS1G_LINK_STATUS(port), &value);
    synced_status = (value & DEV_PCS1G_LINK_STATUS_SYNC_STATUS_M);
    if (status->link == 0) {
        /* The link has been down. Clear the sticky bit and return the 'down' value  */
        REG_WR(DEV_PCS1G_STICKY(port), DEV_PCS1G_STICKY_LINK_DOWN_STICKY_M);
    } else {
        status->link = ((value & DEV_PCS1G_LINK_STATUS_LINK_STATUS_M) && synced_status);
    }

    /* Get PCS ANEG status register */
    REG_RD(DEV_PCS1G_ANEG_STATUS(port), &value);
    status->autoneg.complete = (value & DEV_PCS1G_ANEG_STATUS_ANEG_COMPLETE_M ? 1 : 0);

    /* Workaround for a Serdes issue, when aneg completes with FDX capability=0 */
    /* There is another situation which needs to restart aneg: aneg un-complete but the synced status is up, added by SGZ */
    if (aneg->enable && if_type == VTSS_PORT_INTERFACE_SERDES) {
        if ((status->autoneg.complete && ((value >> 21) & 0x1) == 0) ||
            (synced_status && !status->autoneg.complete)) {
            REG_WRM_CLR(DEV_PCS1G_CFG(port), DEV_PCS1G_CFG_PCS_ENA_M);
            REG_WRM_SET(DEV_PCS1G_CFG(port), DEV_PCS1G_CFG_PCS_ENA_M);
            (void)lan966x_port_clause_37_control_set(vtss_state, port_no); /* Restart Aneg */
            VTSS_MSLEEP(50);
            REG_RD(DEV_PCS1G_ANEG_STATUS(port), &value);
            status->autoneg.complete = (value & DEV_PCS1G_ANEG_STATUS_ANEG_COMPLETE_M ? 1 : 0);
        }
    }

    /* Return partner advertisement ability */
    value = DEV_PCS1G_ANEG_STATUS_LP_ADV_X(value);
    VTSS_N("port:%d, if_type:0x%X", port_no, if_type);
    if (if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
        sgmii_adv->link = ((value >> 15) == 1) ? 1 : 0;
        sgmii_adv->fdx = (((value >> 12) & 0x1) == 1) ? 1 : 0;
        value = ((value >> 10) & 3);
        sgmii_adv->speed_10M = (value == 0 ? 1 : 0);
        sgmii_adv->speed_100M = (value == 1 ? 1 : 0);
        sgmii_adv->speed_1G = (value == 2 ? 1 : 0);
        sgmii_adv->hdx = (status->autoneg.partner_advertisement.fdx ? 0 : 1);
        if (status->link) {
            /* If the SFP module does not have a link then the port does not have link */
            status->link = sgmii_adv->link;
        }
        VTSS_N("port:%d, value:0x%X, sgmii_adv->link:%d, status->link:%d", port_no, value, sgmii_adv->link, status->link);
    } else {
        VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &status->autoneg.partner_advertisement));
    }
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
    u32 data;

    /* Enqueue MIIM operation to be executed */
    REG_WR(GCB_MII_CMD(miim_controller),
           GCB_MII_CMD_CMD_VLD_M |
           GCB_MII_CMD_CMD_PHYAD(miim_addr) |
           GCB_MII_CMD_CMD_REGAD(addr) |
           GCB_MII_CMD_CMD_WRDATA(*value) |
           GCB_MII_CMD_CMD_OPR_FIELD(read ? 2 : 1));

    /* Wait for MIIM operation to finish */
    do {
        REG_RD(GCB_MII_STATUS(miim_controller), &data);
    } while (data & GCB_MII_STATUS_STAT_BUSY_M);

    if (read) {
        REG_RD(GCB_MII_DATA(miim_controller), &data);
        if (data & GCB_MII_DATA_DATA_SUCCESS(3))
            return VTSS_RC_ERROR;
        *value = GCB_MII_DATA_DATA_RDDATA_X(data);
    }
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
