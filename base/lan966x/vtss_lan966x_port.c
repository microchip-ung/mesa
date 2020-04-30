// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

#if defined(VTSS_ARCH_LAN966X_FPGA)
#define MULTIPLIER_BIT VTSS_BIT(5)
#else
#define MULTIPLIER_BIT VTSS_BIT(8)
#endif

static u32 wm_enc(u32 value, BOOL bytes)
{
    if (bytes) {
        value /= LAN966X_BUFFER_CELL_SZ;
    }
    if (value >= MULTIPLIER_BIT) {
        value /= 16;
        if (value >= MULTIPLIER_BIT) {
            value = (MULTIPLIER_BIT - 1);
        }
        value |= MULTIPLIER_BIT;
    }
    return value;
}

static u32 wm_enc_bytes(u32 value)
{
    return wm_enc(value, 1);
}

#if 0
static u32 wm_enc_frames(u32 value)
{
    return wm_enc(value, 0);
}
#endif

static u32 wm_dec(u32 value, BOOL bytes)
{
    if (value & MULTIPLIER_BIT) {
        value = ((value & (MULTIPLIER_BIT - 1)) * 16);
    }
    if (bytes) {
        value *= LAN966X_BUFFER_CELL_SZ;
    }
    return value;
}

static u32 wm_dec_bytes(u32 value)
{
    return wm_dec(value, 1);
}


static u32 wm_dec_frames(u32 value)
{
    return wm_dec(value, 0);
}

u32 vtss_lan966x_wm_high_get(vtss_state_t *vtss_state, u32 queue)
{
    u32 wm_high;
    REG_RD(QSYS_RES_CFG((queue + 216)), &wm_high); /* Shared ingress high watermark for queue - common for all dpls */
    return wm_dec_bytes(wm_high);
}

vtss_rc vtss_lan966x_wm_update(vtss_state_t *vtss_state)
{
    u32 q;

    /* Update BUF_PRIO_SHR_E sharing watermarks according to AN1121 Section 7 WRED Operation */
    for (q = 0; q < VTSS_PRIOS; q++) {
        if (vtss_state->qos.conf.red_v2[q][0].enable || vtss_state->qos.conf.red_v2[q][1].enable) {
            REG_WR(QSYS_RES_CFG((q + 216 + 512)), 0); /* WRED is enabled for DP0 or DP1 - set watermark to zero */
        } else {
            REG_WR(QSYS_RES_CFG((q + 216 + 512)), vtss_state->port.buf_prio_shr[q]); /* Restore initial value */
        }
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_max_tags_t  max_tags = vtss_state->port.conf[port_no].max_tags;
    vtss_vlan_port_type_t vlan_type = vtss_state->l2.vlan_port_conf[port_no].port_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    u32                   etype, double_ena, single_ena;

    /* S-ports and VLAN unaware ports both suport 0x88a8 (in addition to 0x8100) */
    etype = (vlan_type == VTSS_VLAN_PORT_TYPE_S_CUSTOM ? vtss_state->l2.vlan_conf.s_etype :
             vlan_type == VTSS_VLAN_PORT_TYPE_C ? VTSS_ETYPE_TAG_C : VTSS_ETYPE_TAG_S);
    single_ena = (max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1);
    double_ena = (max_tags == VTSS_PORT_MAX_TAGS_TWO ? 1 : 0);
    REG_WR(DEV_MAC_TAGS_CFG(port),
           DEV_MAC_TAGS_CFG_TAG_ID(etype) |
           DEV_MAC_TAGS_CFG_PB_ENA(double_ena) |
           DEV_MAC_TAGS_CFG_VLAN_AWR_ENA(single_ena) |
           DEV_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA(1));
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

/* Clause 45 operations */
#define PHY_CMD_WRITE    1 /* Write */
#define PHY_CMD_READ_INC 2 /* Read and increment */
#define PHY_CMD_READ     3 /* 10G: Read */

static vtss_rc lan966x_mmd_cmd(vtss_state_t *vtss_state,
                               u32 cmd,
                               u32 miim_controller,
                               u8 miim_addr,
                               u8 mmd,
                               u16 addr,
                               u16 *value,
                               BOOL report_errors)
{
    vtss_rc rc = VTSS_RC_OK;
    u32     data;

    /* Switch to clause 45 */
    REG_WRM(GCB_MII_CFG(miim_controller),
            GCB_MII_CFG_ST_CFG_FIELD(0),
            GCB_MII_CFG_ST_CFG_FIELD_M);

    /* Enqueue address set operation */
    REG_WR(GCB_MII_CMD(miim_controller),
           GCB_MII_CMD_CMD_VLD_M |
           GCB_MII_CMD_CMD_PHYAD(miim_addr) |
           GCB_MII_CMD_CMD_REGAD(mmd) |
           GCB_MII_CMD_CMD_WRDATA(addr) |
           GCB_MII_CMD_CMD_OPR_FIELD(0));

    /* Wait for MIIM operation to finish */
    do {
        REG_RD(GCB_MII_STATUS(miim_controller), &data);
    } while (data & GCB_MII_STATUS_STAT_BUSY_M);

    /* Enqueue read or write operation */
    REG_WR(GCB_MII_CMD(miim_controller),
           GCB_MII_CMD_CMD_VLD_M |
           GCB_MII_CMD_CMD_PHYAD(miim_addr) |
           GCB_MII_CMD_CMD_REGAD(mmd) |
           GCB_MII_CMD_CMD_WRDATA(*value) |
           GCB_MII_CMD_CMD_OPR_FIELD(cmd));

    /* Wait for MIIM operation to finish */
    do {
        REG_RD(GCB_MII_STATUS(miim_controller), &data);
    } while (data & GCB_MII_STATUS_STAT_BUSY_M);

    if (cmd == PHY_CMD_READ || cmd == PHY_CMD_READ_INC) {
        REG_RD(GCB_MII_DATA(miim_controller), &data);
        if (data & GCB_MII_DATA_DATA_SUCCESS(3)) {
            rc = VTSS_RC_ERROR;
        } else {
            *value = GCB_MII_DATA_DATA_RDDATA_X(data);
        }
    }

    /* Switch back to clause 22 */
    REG_WRM(GCB_MII_CFG(miim_controller),
            GCB_MII_CFG_ST_CFG_FIELD(1),
            GCB_MII_CFG_ST_CFG_FIELD_M);

    return rc;
}

static vtss_rc lan966x_mmd_read(vtss_state_t *vtss_state,
                                vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                u16 addr, u16 *value, BOOL report_errors)
{
    return lan966x_mmd_cmd(vtss_state, PHY_CMD_READ, miim_controller, miim_addr, mmd, addr, value, report_errors);
}

static vtss_rc lan966x_mmd_write(vtss_state_t *vtss_state,
                                 vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                 u16 addr, u16 value, BOOL report_errors)
{
    return lan966x_mmd_cmd(vtss_state, PHY_CMD_WRITE, miim_controller, miim_addr, mmd, addr, &value, report_errors);
}

static vtss_rc lan966x_mmd_read_inc(vtss_state_t *vtss_state,
                                    vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                    u16 addr, u16 *buf, u8 count, BOOL report_errors)
{
    while (count > 1) {
        VTSS_RC(lan966x_mmd_cmd(vtss_state, PHY_CMD_READ_INC, miim_controller, miim_addr, mmd, addr, buf, report_errors));
        buf++;
        count--;
    }
    return VTSS_RC_OK;
}

static u32 lan966x_pfc_mask(vtss_port_conf_t *conf)
{
    u32 q, mask = 0;

    for (q = 0; q < VTSS_PRIOS; q++) {
        mask |= (conf->flow_control.pfc[q] ? VTSS_BIT(q) : 0);
    }
    return mask;
}

static vtss_rc lan966x_port_pfc(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u32 pfc_mask = lan966x_pfc_mask(conf);
    u32 spd = (conf->speed == VTSS_SPEED_10M ? 3 :
               conf->speed == VTSS_SPEED_100M ? 2 :
               conf->speed == VTSS_SPEED_1G ? 1 : 0);

    /* Rx enable/disable */
    REG_WR(ANA_PFC_CFG(port),
           ANA_PFC_CFG_RX_PFC_ENA(pfc_mask) |
           ANA_PFC_CFG_FC_LINK_SPEED(spd));

    /* Forward 802.1Qbb pause frames to analyzer */
    REG_WRM(DEV_PORT_MISC(port),
            DEV_PORT_MISC_FWD_CTRL_ENA(pfc_mask ? 1 : 0),
            DEV_PORT_MISC_FWD_CTRL_ENA_M);

    /* PFC Tx enable is done after the core is enabled */

    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_fc_setup(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u8                *mac;
    u32               pfc_mask = lan966x_pfc_mask(conf);
    BOOL              fc_gen = conf->flow_control.generate, fc_obey = conf->flow_control.obey;
    vtss_port_speed_t speed = conf->speed;
    vtss_port_no_t    port_no;
    u32               rsrv_raw, rsrv_total = 0, atop_wm;
    u32               pause_stop  = 1;
    u32               rsrv_raw_fc_jumbo = 40000;
    u32               rsrv_raw_no_fc_jumbo = 12000;
    u32               rsrv_raw_fc_no_jumbo = (9 * 1518);
    u32               link_speed = (speed == VTSS_SPEED_10M ? 3 :
                                    speed == VTSS_SPEED_100M ? 2 :
                                    speed == VTSS_SPEED_1G ? 1 : 0);

    if (pfc_mask && (fc_gen || fc_obey)) {
        VTSS_E("802.3X FC and 802.1Qbb PFC cannot both be enabled, chip port %u", port);
        return VTSS_RC_ERROR;
    }

    /* Configure 802.1Qbb PFC */
    VTSS_RC(lan966x_port_pfc(vtss_state, port, conf));

    if (pfc_mask) {
        // Each port can use this as max before tail dropping starts
        rsrv_raw = rsrv_raw_fc_no_jumbo;
    } else {
        /* Standard Flowcontrol */
        if (conf->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
            if (fc_gen) { /* FC and jumbo enabled*/
                pause_stop = 7;
                rsrv_raw = rsrv_raw_fc_jumbo;
            } else {      /* FC disabled, jumbo enabled */
                rsrv_raw = rsrv_raw_no_fc_jumbo;
            }
        } else {
            if (fc_gen) { /* FC enabled, jumbo disabled */
                pause_stop = 4;
                rsrv_raw = rsrv_raw_fc_no_jumbo;
            } else {
                rsrv_raw = 0;
            }
        }
    }

    /* Set Pause WM hysteresis, start/stop are in 1518 byte units */
    REG_WR(SYS_PAUSE_CFG(port),
           SYS_PAUSE_CFG_PAUSE_START(wm_enc_bytes((pause_stop + 2) * 1518)) |
           SYS_PAUSE_CFG_PAUSE_STOP(wm_enc_bytes(pause_stop * 1518)) |
           SYS_PAUSE_CFG_PAUSE_ENA(fc_gen ? 1 : 0));

    /* Set SMAC of Pause frame */
    mac = &conf->flow_control.smac.addr[0];
    REG_WR(DEV_FC_MAC_HIGH_CFG(port), (mac[0]<<16) | (mac[1]<<8) | mac[2]);
    REG_WR(DEV_FC_MAC_LOW_CFG(port), (mac[3]<<16) | (mac[4]<<8) | mac[5]);

    /* Enable/disable FC incl. pause value and zero pause */
    REG_WR(SYS_MAC_FC_CFG(port),
           SYS_MAC_FC_CFG_FC_LINK_SPEED(link_speed) |
           SYS_MAC_FC_CFG_FC_LATENCY_CFG(7) |
           SYS_MAC_FC_CFG_ZERO_PAUSE_ENA(1) |
           SYS_MAC_FC_CFG_RX_FC_ENA(fc_obey ? 1 : 0) |
           SYS_MAC_FC_CFG_PAUSE_VAL_CFG(pfc_mask ? 0xff : 0xffff));
    REG_WRM(QSYS_SW_PORT_MODE(port),
            QSYS_SW_PORT_MODE_INGRESS_DROP_MODE(fc_gen ? 1 : 0),
            QSYS_SW_PORT_MODE_INGRESS_DROP_MODE_M);

    /* Calculate the total reserved space for all ports */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        conf = &vtss_state->port.conf[port_no];
        fc_gen = conf->flow_control.generate;
        if (lan966x_pfc_mask(conf)) {
            rsrv_total += rsrv_raw_no_fc_jumbo;
        } else if (conf->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
            if (fc_gen) {
                rsrv_total += rsrv_raw_fc_jumbo;
            } else {
                rsrv_total += rsrv_raw_no_fc_jumbo;
            }
        } else if (fc_gen) {
            rsrv_total += rsrv_raw_fc_no_jumbo;
        }
    }
    atop_wm = (LAN966X_BUFFER_MEMORY - rsrv_total);

    /* When 'port ATOP' and 'common ATOP_TOT' are exceeded, tail dropping is activated on port */
    REG_WR(SYS_ATOP_TOT_CFG, wm_enc_bytes(atop_wm));
    REG_WR(SYS_ATOP(port), wm_enc_bytes(rsrv_raw));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_conf_get(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no, vtss_port_conf_t *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_rc                rc = VTSS_RC_OK;
    vtss_port_conf_t       *conf = &vtss_state->port.conf[port_no];
    u32                    port = VTSS_CHIP_PORT(port_no);
    u32                    value, link_speed, delay = 0, pfc_mask;
    BOOL                   disable = conf->power_down;
    vtss_port_speed_t      speed = conf->speed;
    vtss_port_frame_gaps_t gaps;

    /* Verify speed and interface type */
    switch (speed) {
    case VTSS_SPEED_10M:
        link_speed = 3;
        break;
    case VTSS_SPEED_100M:
        link_speed = 2;
        break;
    case VTSS_SPEED_1G:
    case VTSS_SPEED_2500M:
        link_speed = 1;
        break;
    default:
        VTSS_E("illegal speed:%d, port %u", speed, port);
        return VTSS_RC_ERROR;
    }

    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        disable = 1;
        break;
    case VTSS_PORT_INTERFACE_GMII:
        break;
    default:
        VTSS_E("illegal interface, port %u", port);
        return VTSS_RC_ERROR;
    }

    /* 1: Reset the PCS Rx clock domain  */
    REG_WRM_SET(DEV_CLOCK_CFG(port), DEV_CLOCK_CFG_PCS_RX_RST_M);

    /* 2: Disable MAC frame reception */
    REG_WRM_CLR(DEV_MAC_ENA_CFG(port), DEV_MAC_ENA_CFG_RX_ENA_M);

    /* 3: Disable traffic being sent to or from switch port */
    REG_WRM_CLR(QSYS_SW_PORT_MODE(port), QSYS_SW_PORT_MODE_PORT_ENA_M);

    /* 4: Disable dequeuing from the egress queues  */
    REG_WRM_SET(QSYS_PORT_MODE(port), QSYS_PORT_MODE_DEQUEUE_DIS_M);

    /* 5: Disable Flowcontrol */
    REG_WRM_CLR(SYS_PAUSE_CFG(port), SYS_PAUSE_CFG_PAUSE_ENA_M);

    /* 5.1: Disable PFC */
    REG_WRM(QSYS_SW_PORT_MODE(port),
            QSYS_SW_PORT_MODE_TX_PFC_ENA(0),
            QSYS_SW_PORT_MODE_TX_PFC_ENA_M);

    /* 6: Wait a worst case time 8ms (jumbo/10Mbit) */
    VTSS_MSLEEP(8);

    /* 7: Disable HDX backpressure (Bugzilla 3203) */
    REG_WRM_CLR(SYS_FRONT_PORT_MODE(port), SYS_FRONT_PORT_MODE_HDX_MODE_M);

    /* 8: Flush the queues accociated with the port */
    REG_WRM(QSYS_SW_PORT_MODE(port),
            QSYS_SW_PORT_MODE_AGING_MODE(3),
            QSYS_SW_PORT_MODE_AGING_MODE_M);

    /* 9: Enable dequeuing from the egress queues */
    REG_WRM_CLR(QSYS_PORT_MODE(port), QSYS_PORT_MODE_DEQUEUE_DIS_M);

    /* 10: Wait until flushing is complete */
    do {
        REG_RD(QSYS_SW_STATUS(port), &value);
        VTSS_MSLEEP(1);
        delay++;
        if (delay == 2000) {
            VTSS_E("Flush timeout chip port %u", port);
            rc = VTSS_RC_ERROR;
            break;
        }
    } while (value & QSYS_SW_STATUS_EQ_AVAIL_M);

    /* 11: Reset the Port and MAC clock domains */
    REG_WRM_CLR(DEV_MAC_ENA_CFG(port), DEV_MAC_ENA_CFG_TX_ENA_M); /* Bugzilla#19076 */
    REG_WRM_SET(DEV_CLOCK_CFG(port), DEV_CLOCK_CFG_PORT_RST_M);
    VTSS_MSLEEP(1);
    REG_WRM_SET(DEV_CLOCK_CFG(port),
                DEV_CLOCK_CFG_MAC_TX_RST_M |
                DEV_CLOCK_CFG_MAC_RX_RST_M |
                DEV_CLOCK_CFG_PORT_RST_M);

    /* 12: Clear flushing */
    REG_WRM(QSYS_SW_PORT_MODE(port),
            QSYS_SW_PORT_MODE_AGING_MODE(0),
            QSYS_SW_PORT_MODE_AGING_MODE_M);

    /* The port is disabled and flushed, now set up the port in the new operating mode */

    /* Configure framelength check (from ethertype / length field) */
    REG_WRM_CTL(DEV_MAC_ADV_CHK_CFG(port), conf->frame_length_chk, DEV_MAC_ADV_CHK_CFG_LEN_DROP_ENA_M);

    /* GIG/FDX mode */
    if (conf->fdx) {
        value = DEV_MAC_MODE_CFG_FDX_ENA_M;
        if (speed == VTSS_SPEED_1G || speed == VTSS_SPEED_2500M) {
            value |= DEV_MAC_MODE_CFG_GIGA_MODE_ENA_M;
        }
    } else {
        REG_WRM_SET(SYS_FRONT_PORT_MODE(port), SYS_FRONT_PORT_MODE_HDX_MODE_M);
        value = (conf->flow_control.obey ? DEV_MAC_MODE_CFG_FC_WORD_SYNC_ENA_M : 0);
    }
    REG_WR(DEV_MAC_MODE_CFG(port), value);

    /* Default gaps */
    gaps.fdx_gap = 15;
    if (speed == VTSS_SPEED_1G || speed == VTSS_SPEED_2500M) {
        gaps.fdx_gap = 5;
    }
    if (conf->fdx) {
        gaps.hdx_gap_1 = 0;
        gaps.hdx_gap_2 = 0;
    } else {
        gaps.hdx_gap_1 = 5;
        gaps.hdx_gap_2 = 5;
    }

    /* Non default gaps */
    if (conf->frame_gaps.fdx_gap != VTSS_FRAME_GAP_DEFAULT)
        gaps.fdx_gap = conf->frame_gaps.fdx_gap;
    if (conf->frame_gaps.hdx_gap_1 != VTSS_FRAME_GAP_DEFAULT)
        gaps.hdx_gap_1 = conf->frame_gaps.hdx_gap_1;
    if (conf->frame_gaps.hdx_gap_2 != VTSS_FRAME_GAP_DEFAULT)
        gaps.hdx_gap_2 = conf->frame_gaps.hdx_gap_2;

    /* Set MAC IFG Gaps */
    REG_WR(DEV_MAC_IFG_CFG(port),
           DEV_MAC_IFG_CFG_TX_IFG(gaps.fdx_gap) |
           DEV_MAC_IFG_CFG_RX_IFG1(gaps.hdx_gap_1) |
           DEV_MAC_IFG_CFG_RX_IFG2(gaps.hdx_gap_2));

    /* Load seed and set MAC HDX late collision */
    value = (DEV_MAC_HDX_CFG_RETRY_EXC_COL_ENA(conf->exc_col_cont ? 1 : 0) |
             DEV_MAC_HDX_CFG_LATE_COL_POS(67));
    REG_WR(DEV_MAC_HDX_CFG(port), DEV_MAC_HDX_CFG_SEED_LOAD_M | value);
    VTSS_NSLEEP(1000);
    REG_WR(DEV_MAC_HDX_CFG(port), value);

    // TBD: PCS setup

    /* Set Max Length and maximum tags allowed */
    REG_WR(DEV_MAC_MAXLEN_CFG(port), conf->max_frame_length);
    VTSS_RC(vtss_lan966x_port_max_tags_set(vtss_state, port_no));

    // Setup QoS - in reset
    VTSS_RC(vtss_lan966x_qos_port_change(vtss_state, port_no, TRUE));

    if (!disable) {
        /* Enable MAC module */
        REG_WR(DEV_MAC_ENA_CFG(port),
               DEV_MAC_ENA_CFG_RX_ENA_M |
               DEV_MAC_ENA_CFG_TX_ENA_M);

        /* Take MAC, Port, Phy (intern) and PCS (SGMII/Serdes) clock out of reset */
        REG_WR(DEV_CLOCK_CFG(port), DEV_CLOCK_CFG_LINK_SPEED(link_speed));

        /* Configure flow control */
        VTSS_RC(lan966x_port_fc_setup(vtss_state, port, conf));

        /* Core: Enable port for frame transfer */
        REG_WRM_SET(QSYS_SW_PORT_MODE(port), QSYS_SW_PORT_MODE_PORT_ENA_M);

        /* Enable flowcontrol - must be done after flushing */
        if (conf->flow_control.generate) {
            REG_WRM_SET(SYS_MAC_FC_CFG(port), SYS_MAC_FC_CFG_TX_FC_ENA_M);
        }

        if ((pfc_mask = lan966x_pfc_mask(conf)) != 0) {
            /*  Enable PFC Tx enable */
            REG_WRM(QSYS_SW_PORT_MODE(port),
                    QSYS_SW_PORT_MODE_TX_PFC_ENA(pfc_mask),
                    QSYS_SW_PORT_MODE_TX_PFC_ENA_M);
        }
    }

    vtss_state->port.current_speed[port_no] = vtss_state->port.conf[port_no].speed;
    vtss_state->port.current_if_type[port_no] = vtss_state->port.conf[port_no].if_type;
    vtss_state->port.current_mt[port_no] = vtss_state->port.conf[port_no].serdes.media_type;

    // Setup QoS - out of reset
    VTSS_RC(vtss_lan966x_qos_port_change(vtss_state, port_no, FALSE));

#if defined(VTSS_FEATURE_QOS_TAS)
    /* Time Aware Scheduling setup depends on link speed */
    VTSS_RC(vtss_lan966x_qos_tas_port_conf_update(vtss_state, port_no));
#endif

    return rc;
}


static vtss_rc lan966x_port_ifh_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_ifh_t *ifh = &vtss_state->port.ifh_conf[port_no];
    u32             port = VTSS_CHIP_PORT(port_no);

    REG_WRM(SYS_PORT_MODE(port),
            SYS_PORT_MODE_INCL_INJ_HDR(ifh->ena_inj_header ? 1 : 0) |
            SYS_PORT_MODE_INCL_XTR_HDR(ifh->ena_xtr_header ? 3 : 0),
            SYS_PORT_MODE_INCL_INJ_HDR_M |
            SYS_PORT_MODE_INCL_XTR_HDR_M);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_status_get(vtss_state_t *vtss_state,
                                       const vtss_port_no_t  port_no,
                                       vtss_port_status_t    *const status)
{
    return VTSS_RC_OK;
}

static vtss_rc vtss_lan966x_dual_cnt_update(vtss_state_t *vtss_state,
                                            u32 *addr, vtss_dual_counter_t *counter, BOOL clear)
{
    u32 base = *addr;

    // E-MAC counters
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, addr, &counter->c[0], clear));
    // P-MAC counters, offset depends on Rx/Tx
    *addr = (base + (base < 0x80 ? 0x30 : base < 0x84 ? 0x21 : 0x1f));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, addr, &counter->c[1], clear));
    *addr = (base + 1); // Next E-MAC counter address
    return VTSS_RC_OK;
}

#define CNT_SUM(cnt) (cnt.c[0].value + cnt.c[1].value)

static vtss_rc lan966x_port_counters_read(vtss_state_t                 *vtss_state,
                                          vtss_port_no_t               port_no,
                                          u32                          port,
                                          vtss_port_luton26_counters_t *c,
                                          vtss_port_counters_t *const  counters,
                                          BOOL                         clear)
{
    u32                                i, base, *p = &base;
    vtss_port_rmon_counters_t          *rmon;
    vtss_port_if_group_counters_t      *if_group;
    vtss_port_ethernet_like_counters_t *elike;
    vtss_port_proprietary_counters_t   *prop;
    vtss_port_dot3br_counters_t        *dot3br;

    /* Setup counter view */
    REG_WR(SYS_STAT_CFG, SYS_STAT_CFG_STAT_VIEW(port));

    base = 0x00;
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_octets, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_unicast, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_multicast, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_broadcast, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_shorts, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_fragments, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_jabbers, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_crc_align_errors, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_symbol_errors, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_64, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_65_127, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_128_255, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_256_511, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_512_1023, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_1024_1526, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_1527_max, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_pause, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_control, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_longs, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_classified_drops, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_red_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_green_class[i], clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_mm_assembly_errors, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_mm_smd_errors, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_mm_assembly_ok, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_mm_fragments, clear));

    base = 0x80;
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_octets, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_unicast, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_multicast, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_broadcast, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_collision, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_drops, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_pause, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_64, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_65_127, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_128_255, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_256_511, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_512_1023, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_1024_1526, clear));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_1527_max, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_green_class[i], clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_aging, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_mm_hold, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_mm_fragments, clear));

    /* 32-bit Drop chip counters */
    base = 0x100;
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->dr_local, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->dr_tail, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->dr_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->dr_green_class[i], clear));

    if (counters == NULL) {
        return VTSS_RC_OK;
    }

    /* Calculate API counters based on chip counters */
    rmon = &counters->rmon;
    if_group = &counters->if_group;
    elike = &counters->ethernet_like;
    prop = &counters->prop;
    dot3br = &counters->dot3br;

    /* Proprietary counters */
    for (i = 0; i < VTSS_PRIOS; i++) {
        prop->rx_prio[i] = (c->rx_red_class[i].value + c->rx_yellow_class[i].value + c->rx_green_class[i].value);
        prop->tx_prio[i] = (c->tx_yellow_class[i].value + c->tx_green_class[i].value);
    }

    /* RMON Rx counters */
    rmon->rx_etherStatsDropEvents = c->dr_tail.value;
    for (i = 0; i < VTSS_PRIOS; i++) {
        rmon->rx_etherStatsDropEvents += (c->dr_yellow_class[i].value + c->dr_green_class[i].value);
    }

    rmon->rx_etherStatsOctets = CNT_SUM(c->rx_octets);
    rmon->rx_etherStatsPkts =
        (CNT_SUM(c->rx_shorts) + CNT_SUM(c->rx_fragments) + CNT_SUM(c->rx_jabbers) + CNT_SUM(c->rx_longs) +
         CNT_SUM(c->rx_64) + CNT_SUM(c->rx_65_127) + CNT_SUM(c->rx_128_255) + CNT_SUM(c->rx_256_511) +
         CNT_SUM(c->rx_512_1023) + CNT_SUM(c->rx_1024_1526) + CNT_SUM(c->rx_1527_max));
    rmon->rx_etherStatsBroadcastPkts = CNT_SUM(c->rx_broadcast);
    rmon->rx_etherStatsMulticastPkts = CNT_SUM(c->rx_multicast);
    rmon->rx_etherStatsCRCAlignErrors = CNT_SUM(c->rx_crc_align_errors);
    rmon->rx_etherStatsUndersizePkts = CNT_SUM(c->rx_shorts);
    rmon->rx_etherStatsOversizePkts = CNT_SUM(c->rx_longs);
    rmon->rx_etherStatsFragments = CNT_SUM(c->rx_fragments);
    rmon->rx_etherStatsJabbers = CNT_SUM(c->rx_jabbers);
    rmon->rx_etherStatsPkts64Octets = CNT_SUM(c->rx_64);
    rmon->rx_etherStatsPkts65to127Octets = CNT_SUM(c->rx_65_127);
    rmon->rx_etherStatsPkts128to255Octets = CNT_SUM(c->rx_128_255);
    rmon->rx_etherStatsPkts256to511Octets = CNT_SUM(c->rx_256_511);
    rmon->rx_etherStatsPkts512to1023Octets = CNT_SUM(c->rx_512_1023);
    rmon->rx_etherStatsPkts1024to1518Octets = CNT_SUM(c->rx_1024_1526);
    rmon->rx_etherStatsPkts1519toMaxOctets = CNT_SUM(c->rx_1527_max);

    /* RMON Tx counters */
    rmon->tx_etherStatsDropEvents = (c->tx_drops.value + c->tx_aging.value);
    rmon->tx_etherStatsOctets = CNT_SUM(c->tx_octets);
    rmon->tx_etherStatsPkts =
        (CNT_SUM(c->tx_64) + CNT_SUM(c->tx_65_127) + CNT_SUM(c->tx_128_255) + CNT_SUM(c->tx_256_511) +
         CNT_SUM(c->tx_512_1023) + CNT_SUM(c->tx_1024_1526) + CNT_SUM(c->tx_1527_max));
    rmon->tx_etherStatsBroadcastPkts = CNT_SUM(c->tx_broadcast);
    rmon->tx_etherStatsMulticastPkts = CNT_SUM(c->tx_multicast);
    rmon->tx_etherStatsCollisions = c->tx_collision.value;
    rmon->tx_etherStatsPkts64Octets = CNT_SUM(c->tx_64);
    rmon->tx_etherStatsPkts65to127Octets = CNT_SUM(c->tx_65_127);
    rmon->tx_etherStatsPkts128to255Octets = CNT_SUM(c->tx_128_255);
    rmon->tx_etherStatsPkts256to511Octets = CNT_SUM(c->tx_256_511);
    rmon->tx_etherStatsPkts512to1023Octets = CNT_SUM(c->tx_512_1023);
    rmon->tx_etherStatsPkts1024to1518Octets = CNT_SUM(c->tx_1024_1526);
    rmon->tx_etherStatsPkts1519toMaxOctets = CNT_SUM(c->tx_1527_max);

    /* Interfaces Group Rx counters */
    if_group->ifInOctets = CNT_SUM(c->rx_octets);
    if_group->ifInUcastPkts = CNT_SUM(c->rx_unicast);
    if_group->ifInMulticastPkts = CNT_SUM(c->rx_multicast);
    if_group->ifInBroadcastPkts = CNT_SUM(c->rx_broadcast);
    if_group->ifInNUcastPkts = CNT_SUM(c->rx_multicast) + CNT_SUM(c->rx_broadcast);
    if_group->ifInDiscards = rmon->rx_etherStatsDropEvents;
    if_group->ifInErrors =
        (CNT_SUM(c->rx_crc_align_errors) + CNT_SUM(c->rx_shorts) + CNT_SUM(c->rx_fragments) +
         CNT_SUM(c->rx_jabbers) + CNT_SUM(c->rx_longs));

    /* Interfaces Group Tx counters */
    if_group->ifOutOctets = CNT_SUM(c->tx_octets);
    if_group->ifOutUcastPkts = CNT_SUM(c->tx_unicast);
    if_group->ifOutMulticastPkts = CNT_SUM(c->tx_multicast);
    if_group->ifOutBroadcastPkts = CNT_SUM(c->tx_broadcast);
    if_group->ifOutNUcastPkts = (CNT_SUM(c->tx_multicast) + CNT_SUM(c->tx_broadcast));
    if_group->ifOutErrors = (c->tx_drops.value + c->tx_aging.value);

    /* Ethernet-like counters */
    elike->dot3InPauseFrames = CNT_SUM(c->rx_pause);
    elike->dot3OutPauseFrames = CNT_SUM(c->tx_pause);

    /* Bridge counters */
    counters->bridge.dot1dTpPortInDiscards = (c->rx_classified_drops.value + c->dr_local.value);

    /* 802.3br counters */
    dot3br->aMACMergeFrameAssErrorCount = c->rx_mm_assembly_errors.value;
    dot3br->aMACMergeFrameSmdErrorCount = c->rx_mm_smd_errors.value;
    dot3br->aMACMergeFrameAssOkCount = c->rx_mm_assembly_ok.value;
    dot3br->aMACMergeFragCountRx = c->rx_mm_fragments.value;
    dot3br->aMACMergeFragCountTx = c->tx_mm_fragments.value;
    dot3br->aMACMergeHoldCount = c->tx_mm_hold.value;

    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_basic_counters_get(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no,
                                               vtss_basic_counters_t *const counters)
{
    u32                          base, *p = &base, port = VTSS_CHIP_PORT(port_no);
    vtss_port_luton26_counters_t *c = &vtss_state->port.counters[port_no].counter.luton26;

    /* Setup counter view */
    REG_WR(SYS_STAT_CFG, SYS_STAT_CFG_STAT_VIEW(port));

    /* Rx Counters */
    base = 0x09; /* rx_64 */
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_64, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_65_127, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_128_255, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_256_511, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_512_1023, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_1024_1526, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->rx_1527_max, 0));

    /* Tx Counters */
    base = 0x87; /* tx_64 */
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_64, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_65_127, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_128_255, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_256_511, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_512_1023, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_1024_1526, 0));
    VTSS_RC(vtss_lan966x_dual_cnt_update(vtss_state, p, &c->tx_1527_max, 0));

    /* Rx frames */
    counters->rx_frames =
        (CNT_SUM(c->rx_64) + CNT_SUM(c->rx_65_127) + CNT_SUM(c->rx_128_255) + CNT_SUM(c->rx_256_511) +
         CNT_SUM(c->rx_512_1023) + CNT_SUM(c->rx_1024_1526) + CNT_SUM(c->rx_1527_max));

    /* Tx frames */
    counters->tx_frames =
        (CNT_SUM(c->tx_64) + CNT_SUM(c->tx_65_127) + CNT_SUM(c->tx_128_255) + CNT_SUM(c->tx_256_511) +
         CNT_SUM(c->tx_512_1023) + CNT_SUM(c->tx_1024_1526) + CNT_SUM(c->tx_1527_max));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_counters_cmd(vtss_state_t                *vtss_state,
                                      const vtss_port_no_t        port_no,
                                      vtss_port_counters_t *const counters,
                                      BOOL                        clear)
{
    return lan966x_port_counters_read(vtss_state,
                                      port_no,
                                      VTSS_CHIP_PORT(port_no),
                                      &vtss_state->port.counters[port_no].counter.luton26,
                                      counters,
                                      clear);
}

static vtss_rc lan966x_port_counters_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return lan966x_port_counters_cmd(vtss_state, port_no, NULL, 0);
}

static vtss_rc lan966x_port_counters_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return lan966x_port_counters_cmd(vtss_state, port_no, NULL, 1);
}

static vtss_rc lan966x_port_counters_get(vtss_state_t *vtss_state,
                                         const vtss_port_no_t port_no,
                                         vtss_port_counters_t *const counters)
{
    memset(counters, 0, sizeof(*counters));
    return lan966x_port_counters_cmd(vtss_state, port_no, counters, 0);
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
    int q;
    u32 port, value;

    // Default watermarks are used
    for (q = 0; q < VTSS_PRIOS; q++) {
        /* Save initial encoded value of shared area for later use by WRED */
        REG_RD(QSYS_RES_CFG((q + 216 + 512)), &vtss_state->port.buf_prio_shr[q]);
    }

    // The CPU will only use its reserved buffer in the shared queue system and
    // none of the shared buffer space, therefore we disable resource sharing in
    // egress direction. We must not disable resource sharing in the ingress
    // direction, because some traffic test scenarios require loads of buffer
    // memory for frames initiated by the CPU.
    port = VTSS_CHIP_PORT_CPU;

    // Egress
    REG_RD(QSYS_EGR_NO_SHARING, &value);
    value = QSYS_EGR_NO_SHARING_EGR_NO_SHARING_X(value);
    value |= VTSS_BIT(port);
    REG_WRM(QSYS_EGR_NO_SHARING,
            QSYS_EGR_NO_SHARING_EGR_NO_SHARING(value),
            QSYS_EGR_NO_SHARING_EGR_NO_SHARING_M);

    // The CPU should also discard frames forwarded to it if it has run
    // out of the reserved buffer space. Otherwise they will be held back
    // in the ingress queues with potential head-of-line blocking effects.
    REG_RD(QSYS_EGR_DROP_MODE, &value);
    value = QSYS_EGR_DROP_MODE_EGRESS_DROP_MODE_X(value);
    value |= VTSS_BIT(port);
    REG_WRM(QSYS_EGR_DROP_MODE,
            QSYS_EGR_DROP_MODE_EGRESS_DROP_MODE(value),
            QSYS_EGR_DROP_MODE_EGRESS_DROP_MODE_M);

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static void lan966x_debug_cnt_inst(const vtss_debug_printf_t pr, u32 i,
                                   const char *col1, const char *col2,
                                   vtss_chip_counter_t *c1, vtss_chip_counter_t *c2)
{
    char buf[80];

    sprintf(buf, "%s_%u", col1, i);
    vtss_lan966x_debug_cnt(pr, buf, col2, c1, c2);
}

static void lan966x_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                              vtss_dual_counter_t *c1, vtss_dual_counter_t *c2)
{
    u32  i;
    char buf1[32], buf2[32];
    const char *name;

    for (i = 0; i < 2; i++) {
        name = (i ? "pmac" : "emac");
        sprintf(buf1, "%s_%s", name, col1);
        if (col2 == NULL) {
            vtss_lan966x_debug_cnt(pr, buf1, NULL, &c1->c[i], NULL);
        } else {
            if (strlen(col2) != 0) {
                sprintf(buf2, "%s_%s", name, col2);
            } else {
                strcpy(buf2, "");
            }
            vtss_lan966x_debug_cnt(pr, buf1, buf2, &c1->c[i], &c2->c[i]);
        }
    }
}

static vtss_rc lan966x_debug_port_cnt(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    vtss_port_no_t               port_no = 0;
    u32                          i, port;
    vtss_port_luton26_counters_t *cnt;
    BOOL                         cpu_port = (info->action == 1);

    if (info->has_action && info->action == 0) {
        pr("Port counter actions:\n");
        pr("0: Show actions\n");
        pr("1: Show CPU counters only\n");
        pr("2: Show MAC counters only\n");
        pr("3: Show QS counters only\n");
        return VTSS_RC_OK;
    }

    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        if (info->clear) {
            REG_WR(SYS_STAT_CFG, SYS_STAT_CFG_STAT_CLEAR_SHOT(0x7) | SYS_STAT_CFG_STAT_VIEW(port));
        }
        if (port < VTSS_CHIP_PORTS) {
            // Normal port
            if ((port_no = vtss_cmn_port2port_no(vtss_state, info, port)) == VTSS_PORT_NO_NONE || cpu_port)
                continue;
            cnt = &vtss_state->port.counters[port_no].counter.luton26;
            pr("Counters for chip port: %u (port_no %u):\n\n", port, port_no);
        } else {
            // CPU port
            if (!cpu_port)
                continue;
            cnt = &vtss_state->port.cpu_counters.counter.luton26;
            port_no = VTSS_PORT_NO_NONE;
            pr("Counters CPU port: %u\n\n", port);
        }
        VTSS_RC(lan966x_port_counters_read(vtss_state, port_no, port, cnt, NULL, 0));
        VTSS_EXIT_ENTER();

        // Basic MAC counters
        if (port < VTSS_CHIP_PORTS && (info->full || info->action != 3)) {
            lan966x_debug_cnt(pr, "oct", "", &cnt->rx_octets, &cnt->tx_octets);
            lan966x_debug_cnt(pr, "uc", "", &cnt->rx_unicast, &cnt->tx_unicast);
            lan966x_debug_cnt(pr, "mc", "", &cnt->rx_multicast, &cnt->tx_multicast);
            lan966x_debug_cnt(pr, "bc", "", &cnt->rx_broadcast, &cnt->tx_broadcast);
        }

        // Detailed MAC counters
        if (port < VTSS_CHIP_PORTS && (info->full || info->action == 2)) {
            lan966x_debug_cnt(pr, "pause", "", &cnt->rx_pause, &cnt->tx_pause);
            lan966x_debug_cnt(pr, "64", "", &cnt->rx_64, &cnt->tx_64);
            lan966x_debug_cnt(pr, "65_127", "", &cnt->rx_65_127, &cnt->tx_65_127);
            lan966x_debug_cnt(pr, "128_255", "", &cnt->rx_128_255, &cnt->tx_128_255);
            lan966x_debug_cnt(pr, "256_511", "", &cnt->rx_256_511, &cnt->tx_256_511);
            lan966x_debug_cnt(pr, "512_1023", "", &cnt->rx_512_1023, &cnt->tx_512_1023);
            lan966x_debug_cnt(pr, "1024_1526", "", &cnt->rx_1024_1526, &cnt->tx_1024_1526);
            lan966x_debug_cnt(pr, "jumbo", "", &cnt->rx_1527_max, &cnt->tx_1527_max);
            lan966x_debug_cnt(pr, "crc", NULL, &cnt->rx_crc_align_errors, NULL);
            lan966x_debug_cnt(pr, "symbol", NULL, &cnt->rx_symbol_errors, NULL);
            lan966x_debug_cnt(pr, "short", NULL, &cnt->rx_shorts, NULL);
            lan966x_debug_cnt(pr, "long", NULL, &cnt->rx_longs, NULL);
            lan966x_debug_cnt(pr, "frag", NULL, &cnt->rx_fragments, NULL);
            lan966x_debug_cnt(pr, "jabber", NULL, &cnt->rx_jabbers, NULL);
            lan966x_debug_cnt(pr, "control", NULL, &cnt->rx_control, NULL);
            vtss_lan966x_debug_cnt(pr, "mm_ass_err", NULL, &cnt->rx_mm_assembly_errors, NULL);
            vtss_lan966x_debug_cnt(pr, "mm_smd_err", NULL, &cnt->rx_mm_smd_errors, NULL);
            vtss_lan966x_debug_cnt(pr, "mm_ass_ok",  "mm_hold", &cnt->rx_mm_assembly_ok, &cnt->tx_mm_hold);
            vtss_lan966x_debug_cnt(pr, "mm_frag", "", &cnt->rx_mm_fragments, &cnt->tx_mm_fragments);
        }

        // QS counters
        if (info->full || cpu_port || info->action == 3) {
            vtss_lan966x_debug_cnt(pr, "cat_drop", cpu_port ? NULL : "drops",
                                   &cnt->rx_classified_drops, &cnt->tx_drops);
            vtss_lan966x_debug_cnt(pr, "dr_local", cpu_port ? NULL : "aged",
                                   &cnt->dr_local, &cnt->tx_aging);
            vtss_lan966x_debug_cnt(pr, "dr_tail", NULL, &cnt->dr_tail, NULL);
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, "green", "",
                                       &cnt->rx_green_class[i], &cnt->tx_green_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, "yellow", "",
                                       &cnt->rx_yellow_class[i], &cnt->tx_yellow_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, "red", NULL, &cnt->rx_red_class[i], NULL);
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, "dr_green", NULL, &cnt->dr_green_class[i], NULL);
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, "dr_yellow", NULL, &cnt->dr_yellow_class[i], NULL);
        }
        pr("\n");
    }
    return VTSS_RC_OK;
}

static void lan966x_debug_wm_dump(const vtss_debug_printf_t pr,
                                  const char *reg_name, u32 *value, u32 i, BOOL bytes)
{
    u32 q;
    pr("%-26s", reg_name);
    for (q = 0; q < i; q++) {
        pr("%6u ", wm_dec(value[q], bytes));
    }
    pr("\n");
}

static vtss_rc lan966x_debug_wm(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)

{
    u32 port_no, value, q, dp, cpu_port, port;
    u32 id[8] = {0}, val1[8] = {0}, val2[8] = {0}, val3[8] = {0}, val4[8] = {0}, val5[8] = {0};
    const char *txt;

    pr("Global configuration:\n");
    pr("---------------------\n");
    pr("Total buffer memory     : %d bytes\n", LAN966X_BUFFER_MEMORY);
    pr("Total frame references  : %d frames\n", LAN966X_BUFFER_REFERENCE);
    pr("\n");
    REG_RD(SYS_PAUSE_TOT_CFG, &value);
    pr("FC Pause TOT_START WM   : %d bytes\n", wm_dec_bytes(SYS_PAUSE_TOT_CFG_PAUSE_TOT_START_X(value)));
    pr("FC Pause TOT_STOP WM    : %d bytes\n", wm_dec_bytes(SYS_PAUSE_TOT_CFG_PAUSE_TOT_STOP_X(value)));
    REG_RD(SYS_ATOP_TOT_CFG, &value);
    pr("FC TailDrop ATOP_TOT WM : %d bytes\n", wm_dec_bytes(SYS_ATOP_TOT_CFG_ATOP_TOT_X(value)));
    pr("\n");

    for (port_no = VTSS_PORT_NO_START; port_no <= vtss_state->port_count; port_no++) {
        cpu_port = (port_no == vtss_state->port_count);
        if (cpu_port) {
            /* CPU port */
            if (!info->full) {
                continue;
            }
            port = VTSS_CHIP_PORT_CPU;
            pr("CPU Port : %u\n", port);
            pr("-------------\n");
        } else {
            if (!info->port_list[port_no]) {
                continue;
            }
            port = VTSS_CHIP_PORT(port_no);
            pr("Port : %u (%u)\n", port, port_no);
            pr("---------\n");
        }
        if (!cpu_port) {
            REG_RD(SYS_MAC_FC_CFG(port), &value);
            pr("FC Pause Tx ena     : %d\n", SYS_MAC_FC_CFG_TX_FC_ENA_X(value));
            pr("FC Pause Rx ena     : %d\n", SYS_MAC_FC_CFG_RX_FC_ENA_X(value));
            pr("FC Pause Time Value : 0x%x\n", SYS_MAC_FC_CFG_PAUSE_VAL_CFG_X(value));
            pr("FC Zero pause       : %d\n", SYS_MAC_FC_CFG_ZERO_PAUSE_ENA_X(value));
            REG_RD(SYS_PAUSE_CFG(port), &value);
            pr("FC Pause Ena        : %d\n", SYS_PAUSE_CFG_PAUSE_ENA_X(value));
            pr("FC Pause Start WM   : %d bytes\n", wm_dec_bytes(SYS_PAUSE_CFG_PAUSE_START_X(value)));
            pr("FC Pause Stop WM    : %d bytes\n", wm_dec_bytes(SYS_PAUSE_CFG_PAUSE_STOP_X(value)));
            REG_RD(ANA_PFC_CFG(port), &value);
            value = ANA_PFC_CFG_RX_PFC_ENA_X(value);
            pr("PFC Enable [0-7]    : ");
            for (q = 0; q < VTSS_PRIOS; q++) {
                pr("%u", value & VTSS_BIT(q) ? 1 : 0);
            }
            pr("\n\n");
        }

        REG_RD(SYS_ATOP(port), &value);
        pr("FC TailDrop ATOP WM : %d bytes\n", wm_dec_bytes(SYS_ATOP_ATOP_X(value)));
        REG_RD(QSYS_SW_PORT_MODE(port), &value);
        pr("Ingress Drop Mode   : %d\n", QSYS_SW_PORT_MODE_INGRESS_DROP_MODE_X(value));
        REG_RD(QSYS_EGR_DROP_MODE, &value);
        pr("Egress Drop Mode    : %d\n", QSYS_EGR_DROP_MODE_EGRESS_DROP_MODE_X(value) & VTSS_BIT(port) ? 1 : 0);
        REG_RD(QSYS_IGR_NO_SHARING, &value);
        pr("Ingress No Sharing  : %d\n", QSYS_IGR_NO_SHARING_IGR_NO_SHARING_X(value) & VTSS_BIT(port) ? 1 : 0);
        REG_RD(QSYS_EGR_NO_SHARING, &value);
        pr("Egress No Sharing   : %d\n", QSYS_EGR_NO_SHARING_EGR_NO_SHARING_X(value) & VTSS_BIT(port) ? 1 : 0);
        REG_RD(QSYS_PORT_MODE(port), &value);
        pr("Dequeuing disabled  : %d\n", QSYS_PORT_MODE_DEQUEUE_DIS_X(value));
        pr("\n");

        for (q = 0; q < VTSS_PRIOS; q++) {
            id[q] = q;
            REG_RD(QSYS_RES_CFG(port * VTSS_PRIOS + q + 0),   &val1[q]);
            REG_RD(QSYS_RES_CFG(port * VTSS_PRIOS + q + 256), &val2[q]);
            REG_RD(QSYS_RES_CFG(port * VTSS_PRIOS + q + 512), &val3[q]);
            REG_RD(QSYS_RES_CFG(port * VTSS_PRIOS + q + 768), &val4[q]);
        }
        lan966x_debug_wm_dump(pr, "Queue level rsrv WMs:", id, 8, FALSE);
        lan966x_debug_wm_dump(pr, "Qu Ingr Buf Rsrv (Bytes) :", val1, 8, TRUE);
        lan966x_debug_wm_dump(pr, "Qu Ingr Ref Rsrv (Frames):", val2, 8, FALSE);
        lan966x_debug_wm_dump(pr, "Qu Egr Buf Rsrv  (Bytes) :", val3, 8, TRUE);
        lan966x_debug_wm_dump(pr, "Qu Egr Ref Rsrv  (Frames):", val4, 8, FALSE);
        pr("\n");

        /* Configure reserved space for port */
        REG_RD(QSYS_RES_CFG(port + 224 +   0), &val1[0]);
        REG_RD(QSYS_RES_CFG(port + 224 + 256), &val2[0]);
        REG_RD(QSYS_RES_CFG(port + 224 + 512), &val3[0]);
        REG_RD(QSYS_RES_CFG(port + 224 + 768), &val4[0]);
        pr("Port level rsrv WMs:\n");
        pr("Port Ingress Buf Rsrv: %u Bytes\n",  wm_dec_bytes(val1[0]));
        pr("Port Ingress Ref Rsrv: %u Frames\n", wm_dec_frames(val2[0]));
        pr("Port Egress  Buf Rsrv: %u Bytes\n",  wm_dec_bytes(val3[0]));
        pr("Port Egress  Ref Rsrv: %u Frames\n", wm_dec_frames(val4[0]));
        pr("\n");
    }

    pr("Shared :\n");
    pr("--------\n");
    /* Shared space for all QoS classes */
    REG_RD(QSYS_RES_QOS_MODE, &value);
    value = QSYS_RES_QOS_MODE_RES_QOS_RSRVD_X(value);
    for (q = 0; q < VTSS_PRIOS; q++) {
        REG_RD(QSYS_RES_CFG(q + 216 + 0),   &val1[q]);
        REG_RD(QSYS_RES_CFG(q + 216 + 256), &val2[q]);
        REG_RD(QSYS_RES_CFG(q + 216 + 512), &val3[q]);
        REG_RD(QSYS_RES_CFG(q + 216 + 768), &val4[q]);
        val5[q] = (value & VTSS_BIT(q) ? 1 : 0);
    }
    lan966x_debug_wm_dump(pr, "QoS level:", id, 8, FALSE);
    lan966x_debug_wm_dump(pr, "QoS Ingr Buf (Bytes) :", val1, 8, TRUE);
    lan966x_debug_wm_dump(pr, "QoS Ingr Ref (Frames):", val2, 8, FALSE);
    lan966x_debug_wm_dump(pr, "QoS Egr Buf  (Bytes) :", val3, 8, TRUE);
    lan966x_debug_wm_dump(pr, "QoS Egr Ref  (Frames):", val4, 8, FALSE);
    lan966x_debug_wm_dump(pr, "QoS Reservation Mode :", val5, 8, FALSE);
    pr("\n");

    pr("Color level:\n");
    /* Configure shared space for both DP levels         */
    /* In this context dp:0 is yellow and dp:1 is green */
    for (dp = 0; dp < 2; dp++) {
        REG_RD(QSYS_RES_CFG(dp + 254 +   0), &val1[0]);
        REG_RD(QSYS_RES_CFG(dp + 254 + 256), &val2[0]);
        REG_RD(QSYS_RES_CFG(dp + 254 + 512), &val3[0]);
        REG_RD(QSYS_RES_CFG(dp + 254 + 768), &val4[0]);
        txt = (dp ? "Green " : "Yellow");
        pr("Port DP:%s Ingress Buf : %u Bytes\n", txt, wm_dec_bytes(val1[0]));
        pr("Port DP:%s Ingress Ref : %u Frames\n",txt, wm_dec_frames(val2[0]));
        pr("Port DP:%s Egress  Buf : %u Bytes\n", txt, wm_dec_bytes(val3[0]));
        pr("Port DP:%s Egress  Ref : %u Frames\n",txt, wm_dec_frames(val4[0]));
    }
    pr("\n");

    pr("WRED config:\n");
    pr("Queue Dpl WM_HIGH  bytes RED_LOW  bytes RED_HIGH  bytes\n");
    //  xxxxx xxx 0xxxxx xxxxxxx 0xxxxx xxxxxxx 0xxxxx  xxxxxxx
    for (q = VTSS_QUEUE_START; q < VTSS_QUEUE_END; q++) {
        u32 wm_high, red_profile, wm_red_low, wm_red_high;
        REG_RD(QSYS_RES_CFG(q + 216), &wm_high); /* Shared ingress high watermark for queue */
        for (dp = 0; dp < 2; dp++) {
            REG_RD(QSYS_RED_PROFILE(q + (8 * dp)), &red_profile); /* Red profile for queue, dpl */
            wm_red_low  = QSYS_RED_PROFILE_WM_RED_LOW_X(red_profile);
            wm_red_high = QSYS_RED_PROFILE_WM_RED_HIGH_X(red_profile);
            pr("%5u %3u  0x%04x %6u  0x%04x %6u   0x%04x %6u\n",
               q,
               dp,
               wm_high,
               wm_dec_bytes(wm_high),
               wm_red_low,
               wm_red_low * 1024,
               wm_red_high,
               wm_red_high * 1024);
        }
    }
    pr("\n");

    for (port_no = VTSS_PORT_NO_START; port_no <= vtss_state->port_count; port_no++) {
        for (q = 0; q < VTSS_PRIOS; q++) {
            port = (port_no == vtss_state->port_count) ? VTSS_CHIP_PORT_CPU : VTSS_CHIP_PORT(port_no);
            REG_RD(QSYS_RES_STAT(port * VTSS_PRIOS + q + 0), &value);
            if (value > 0) {
                pr("API port %u (%u), ingress qu %u: Inuse:%u bytes, Maxuse:%u bytes\n",
                   port_no, port, q,
                   wm_dec_bytes(QSYS_RES_STAT_INUSE_X(value)),
                   wm_dec_bytes(QSYS_RES_STAT_MAXUSE_X(value)));
            }
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_port_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT_CNT, lan966x_debug_port_cnt, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_WM, lan966x_debug_wm, vtss_state, pr, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

vtss_rc vtss_lan966x_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_port_state_t *state = &vtss_state->port;
    u32               port;

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
        /* Clear port counters */
        for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
            REG_WR(SYS_STAT_CFG,
                   SYS_STAT_CFG_STAT_CLEAR_SHOT(0x7) |
                   SYS_STAT_CFG_STAT_VIEW(port));
        }
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
