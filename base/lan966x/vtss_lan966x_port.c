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

static vtss_rc lan966x_port_conf_get(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no, vtss_port_conf_t *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t       *conf = &vtss_state->port.conf[port_no];
    u32                    port = VTSS_CHIP_PORT(port_no);
    u32                    value, link_speed, delay = 0;
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
            VTSS_E("Flush timeout chip port %u",port);
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

    if (!disable) {
        /* Enable MAC module */
        REG_WR(DEV_MAC_ENA_CFG(port),
               DEV_MAC_ENA_CFG_RX_ENA_M |
               DEV_MAC_ENA_CFG_TX_ENA_M);

        /* Take MAC, Port, Phy (intern) and PCS (SGMII/Serdes) clock out of reset */
        REG_WR(DEV_CLOCK_CFG(port), DEV_CLOCK_CFG_LINK_SPEED(link_speed));

        /* Configure flow control */
        // TBD: VTSS_RC(srvl_port_fc_setup(vtss_state, port, conf));

        /* Core: Enable port for frame transfer */
        REG_WRM_SET(QSYS_SW_PORT_MODE(port), QSYS_SW_PORT_MODE_PORT_ENA_M);

        /* Notify QoS module about port configuration change */
        //TBD: VTSS_RC(vtss_srvl_qos_port_conf_change(vtss_state, port_no, port, link_speed));
    }
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

    /* Setup counter view */
    REG_WR(SYS_STAT_CFG, SYS_STAT_CFG_STAT_VIEW(port));

    base = 0x00;
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_octets, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_unicast, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_multicast, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_broadcast, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_shorts, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_fragments, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_jabbers, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_crc_align_errors, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_symbol_errors, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_64, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_65_127, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_128_255, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_256_511, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_512_1023, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_1024_1526, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_1527_max, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_pause, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_control, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_longs, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_classified_drops, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_red_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_green_class[i], clear));

    base = 0x80;
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_octets, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_unicast, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_multicast, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_broadcast, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_collision, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_drops, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_pause, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_64, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_65_127, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_128_255, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_256_511, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_512_1023, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_1024_1526, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_1527_max, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_green_class[i], clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_aging, clear));

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

    rmon->rx_etherStatsOctets = c->rx_octets.value;
    rmon->rx_etherStatsPkts =
        (c->rx_shorts.value + c->rx_fragments.value + c->rx_jabbers.value + c->rx_longs.value +
         c->rx_64.value + c->rx_65_127.value + c->rx_128_255.value + c->rx_256_511.value +
         c->rx_512_1023.value + c->rx_1024_1526.value + c->rx_1527_max.value);
    rmon->rx_etherStatsBroadcastPkts = c->rx_broadcast.value;
    rmon->rx_etherStatsMulticastPkts = c->rx_multicast.value;
    rmon->rx_etherStatsCRCAlignErrors = c->rx_crc_align_errors.value;
    rmon->rx_etherStatsUndersizePkts = c->rx_shorts.value;
    rmon->rx_etherStatsOversizePkts = c->rx_longs.value;
    rmon->rx_etherStatsFragments = c->rx_fragments.value;
    rmon->rx_etherStatsJabbers = c->rx_jabbers.value;
    rmon->rx_etherStatsPkts64Octets = c->rx_64.value;
    rmon->rx_etherStatsPkts65to127Octets = c->rx_65_127.value;
    rmon->rx_etherStatsPkts128to255Octets = c->rx_128_255.value;
    rmon->rx_etherStatsPkts256to511Octets = c->rx_256_511.value;
    rmon->rx_etherStatsPkts512to1023Octets = c->rx_512_1023.value;
    rmon->rx_etherStatsPkts1024to1518Octets = c->rx_1024_1526.value;
    rmon->rx_etherStatsPkts1519toMaxOctets = c->rx_1527_max.value;

    /* RMON Tx counters */
    rmon->tx_etherStatsDropEvents = (c->tx_drops.value + c->tx_aging.value);
    rmon->tx_etherStatsOctets = c->tx_octets.value;
    rmon->tx_etherStatsPkts =
        (c->tx_64.value + c->tx_65_127.value + c->tx_128_255.value + c->tx_256_511.value +
         c->tx_512_1023.value + c->tx_1024_1526.value + c->tx_1527_max.value);
    rmon->tx_etherStatsBroadcastPkts = c->tx_broadcast.value;
    rmon->tx_etherStatsMulticastPkts = c->tx_multicast.value;
    rmon->tx_etherStatsCollisions = c->tx_collision.value;
    rmon->tx_etherStatsPkts64Octets = c->tx_64.value;
    rmon->tx_etherStatsPkts65to127Octets = c->tx_65_127.value;
    rmon->tx_etherStatsPkts128to255Octets = c->tx_128_255.value;
    rmon->tx_etherStatsPkts256to511Octets = c->tx_256_511.value;
    rmon->tx_etherStatsPkts512to1023Octets = c->tx_512_1023.value;
    rmon->tx_etherStatsPkts1024to1518Octets = c->tx_1024_1526.value;
    rmon->tx_etherStatsPkts1519toMaxOctets = c->tx_1527_max.value;

    /* Interfaces Group Rx counters */
    if_group->ifInOctets = c->rx_octets.value;
    if_group->ifInUcastPkts = c->rx_unicast.value;
    if_group->ifInMulticastPkts = c->rx_multicast.value;
    if_group->ifInBroadcastPkts = c->rx_broadcast.value;
    if_group->ifInNUcastPkts = c->rx_multicast.value + c->rx_broadcast.value;
    if_group->ifInDiscards = rmon->rx_etherStatsDropEvents;
    if_group->ifInErrors =
        (c->rx_crc_align_errors.value + c->rx_shorts.value + c->rx_fragments.value +
         c->rx_jabbers.value + c->rx_longs.value);

    /* Interfaces Group Tx counters */
    if_group->ifOutOctets = c->tx_octets.value;
    if_group->ifOutUcastPkts = c->tx_unicast.value;
    if_group->ifOutMulticastPkts = c->tx_multicast.value;
    if_group->ifOutBroadcastPkts = c->tx_broadcast.value;
    if_group->ifOutNUcastPkts = (c->tx_multicast.value + c->tx_broadcast.value);
    if_group->ifOutErrors = (c->tx_drops.value + c->tx_aging.value);

    /* Ethernet-like counters */
    elike->dot3InPauseFrames = c->rx_pause.value;
    elike->dot3OutPauseFrames = c->tx_pause.value;

    /* Bridge counters */
    counters->bridge.dot1dTpPortInDiscards = (c->rx_classified_drops.value + c->dr_local.value);
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
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_64, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_65_127, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_128_255, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_256_511, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_512_1023, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_1024_1526, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_1527_max, 0));

    /* Tx Counters */
    base = 0x87; /* tx_64 */
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_64, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_65_127, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_128_255, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_256_511, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_512_1023, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_1024_1526, 0));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_1527_max, 0));

    /* Rx frames */
    counters->rx_frames =
        (c->rx_64.value + c->rx_65_127.value + c->rx_128_255.value + c->rx_256_511.value +
         c->rx_512_1023.value + c->rx_1024_1526.value + c->rx_1527_max.value);

    /* Tx frames */
    counters->tx_frames =
        (c->tx_64.value + c->tx_65_127.value + c->tx_128_255.value + c->tx_256_511.value +
         c->tx_512_1023.value + c->tx_1024_1526.value + c->tx_1527_max.value);

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

static vtss_rc lan966x_debug_port_cnt(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    vtss_port_no_t               port_no = 0;
    u32                          i, port;
    vtss_port_luton26_counters_t *cnt;
    BOOL                         cpu_port;

    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        cpu_port = (port == VTSS_CHIP_PORT_CPU);

        if (info->clear) {
            REG_WR(SYS_STAT_CFG, SYS_STAT_CFG_STAT_CLEAR_SHOT(0x7) | SYS_STAT_CFG_STAT_VIEW(port));
        }

        if (cpu_port) {
            /* CPU port */
            if (!info->full)
                continue;
            cnt = &vtss_state->port.cpu_counters.counter.luton26;
            port_no = VTSS_PORT_NO_NONE;
        } else {
            /* Normal port */
            if ((port_no = vtss_cmn_port2port_no(vtss_state, info, port)) == VTSS_PORT_NO_NONE)
                continue;
            cnt = &vtss_state->port.counters[port_no].counter.luton26;
        }
        VTSS_RC(lan966x_port_counters_read(vtss_state, port_no, port, cnt, NULL, 0));
        VTSS_EXIT_ENTER();

        /* Basic counters */
        if (cpu_port) {
            pr("Counters CPU port: %u\n\n", port);
        } else {
            pr("Counters for phys. port: %u (iport %u):\n\n", port, port_no);
            vtss_lan966x_debug_cnt(pr, "oct", "", &cnt->rx_octets, &cnt->tx_octets);
            vtss_lan966x_debug_cnt(pr, "uc", "", &cnt->rx_unicast, &cnt->tx_unicast);
            vtss_lan966x_debug_cnt(pr, "mc", "", &cnt->rx_multicast, &cnt->tx_multicast);
            vtss_lan966x_debug_cnt(pr, "bc", "", &cnt->rx_broadcast, &cnt->tx_broadcast);
        }

        /* Detailed counters */
        if (info->full) {
            if (!cpu_port) {
                vtss_lan966x_debug_cnt(pr, "pause", "", &cnt->rx_pause, &cnt->tx_pause);
                vtss_lan966x_debug_cnt(pr, "64", "", &cnt->rx_64, &cnt->tx_64);
                vtss_lan966x_debug_cnt(pr, "65_127", "", &cnt->rx_65_127, &cnt->tx_65_127);
                vtss_lan966x_debug_cnt(pr, "128_255", "", &cnt->rx_128_255, &cnt->tx_128_255);
                vtss_lan966x_debug_cnt(pr, "256_511", "", &cnt->rx_256_511, &cnt->tx_256_511);
                vtss_lan966x_debug_cnt(pr, "512_1023", "", &cnt->rx_512_1023, &cnt->tx_512_1023);
                vtss_lan966x_debug_cnt(pr, "1024_1526", "", &cnt->rx_1024_1526, &cnt->tx_1024_1526);
                vtss_lan966x_debug_cnt(pr, "jumbo", "", &cnt->rx_1527_max, &cnt->tx_1527_max);
            }
            vtss_lan966x_debug_cnt(pr, "cat_drop", cpu_port ? NULL : "drops",
                                   &cnt->rx_classified_drops, &cnt->tx_drops);
            vtss_lan966x_debug_cnt(pr, "dr_local", cpu_port ? NULL : "aged",
                                   &cnt->dr_local, &cnt->tx_aging);
            vtss_lan966x_debug_cnt(pr, "dr_tail", NULL, &cnt->dr_tail, NULL);
            if (!cpu_port) {
                vtss_lan966x_debug_cnt(pr, "crc", NULL, &cnt->rx_crc_align_errors, NULL);
                vtss_lan966x_debug_cnt(pr, "symbol", NULL, &cnt->rx_symbol_errors, NULL);
                vtss_lan966x_debug_cnt(pr, "short", NULL, &cnt->rx_shorts, NULL);
                vtss_lan966x_debug_cnt(pr, "long", NULL, &cnt->rx_longs, NULL);
                vtss_lan966x_debug_cnt(pr, "frag", NULL, &cnt->rx_fragments, NULL);
                vtss_lan966x_debug_cnt(pr, "jabber", NULL, &cnt->rx_jabbers, NULL);
                vtss_lan966x_debug_cnt(pr, "control", NULL, &cnt->rx_control, NULL);
            }
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

vtss_rc vtss_lan966x_port_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT_CNT, lan966x_debug_port_cnt, vtss_state, pr, info));
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
