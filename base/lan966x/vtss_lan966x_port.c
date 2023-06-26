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

#if VTSS_OPT_DEBUG_PRINT
static u32 wm_dec_frames(u32 value)
{
    return wm_dec(value, 0);
}
#endif

u32 vtss_lan966x_wm_high_get(vtss_state_t *vtss_state, u32 queue)
{
    u32 wm_high;
    REG_RD(QSYS_RES_CFG((queue + 216)), &wm_high); /* Shared ingress high watermark for queue - common for all dpls */
    return wm_dec_bytes(wm_high);
}

#if defined(VTSS_FEATURE_QOS)
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
#endif

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
    value = DEV_PCS1G_ANEG_CFG_ADV_ABILITY_X(control->enable ? value : 0);
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
    vtss_port_sgmii_aneg_t        *sgmii_adv = &status->autoneg.partner.sgmii;
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
        sgmii_adv->hdx = (status->autoneg.partner.cl37.fdx ? 0 : 1);
        if (status->link) {
            /* If the SFP module does not have a link then the port does not have link */
            status->link = sgmii_adv->link;
        }
        VTSS_N("port:%d, value:0x%X, sgmii_adv->link:%d, status->link:%d", port_no, value, sgmii_adv->link, status->link);
    } else {
        VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &status->autoneg.partner.cl37));
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SYNCE)
#define RCVRD_CLK_GPIO_NO 30      // on Maserati the 2 recovered clock outputs are GPIO 30-31
static vtss_rc lan966x_synce_clock_out_set(vtss_state_t *vtss_state, const u32 clk_port)
{
    u32                     div_mask;
    vtss_synce_clock_out_t  *conf;

    if (clk_port > 1) {
        VTSS_E("Invalid clock port no: %d\n", clk_port);
        return VTSS_RC_ERROR;
    }

    conf = &vtss_state->synce.out_conf[clk_port];

    VTSS_D("clk_port %X  enable %u\n", clk_port, conf->enable);

    switch (conf->divider) {
        case VTSS_SYNCE_DIVIDER_1:  div_mask = 6; break;
        case VTSS_SYNCE_DIVIDER_2:  div_mask = 0; break;
        case VTSS_SYNCE_DIVIDER_4:  div_mask = 1; break;
        case VTSS_SYNCE_DIVIDER_5:  div_mask = 4; break;
        case VTSS_SYNCE_DIVIDER_8:  div_mask = 2; break;
        case VTSS_SYNCE_DIVIDER_16: div_mask = 3; break;
        case VTSS_SYNCE_DIVIDER_25: div_mask = 5; break;
        default:                    div_mask = 0; break;
    }
    REG_WRM(HSIO_SYNC_ETH_CFG(clk_port),
            HSIO_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(div_mask) |
            HSIO_SYNC_ETH_CFG_RECO_CLK_ENA(conf->enable),
            HSIO_SYNC_ETH_CFG_SEL_RECO_CLK_DIV_M |
            HSIO_SYNC_ETH_CFG_RECO_CLK_ENA_M);

    /* To get the best quality of the recovered clocks it is recommended to change the drive strength to 3 */
    REG_WRM(CHIP_TOP_GPIO_CFG(RCVRD_CLK_GPIO_NO + clk_port),
            CHIP_TOP_GPIO_CFG_DS(conf->enable ? 3 : 1),  /* 1 is default */
            CHIP_TOP_GPIO_CFG_DS_M);

    if (VTSS_RC_OK != vtss_lan966x_gpio_mode(vtss_state, 0, RCVRD_CLK_GPIO_NO + clk_port, conf->enable ? VTSS_GPIO_ALT_4 : VTSS_GPIO_IN)) {
        VTSS_E("Failed to set GPIO mode for recovered clock[%d]\n", clk_port);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}
#endif

#if !defined(VTSS_OPT_FPGA)
typedef enum {
    PORT_TYPE_NONE,
    PORT_TYPE_CUPHY,
    PORT_TYPE_SD,
    PORT_TYPE_RGMII
} port_type_t;

static vtss_rc lan966x_port_type_calc(vtss_state_t *vtss_state,
                                      vtss_port_no_t port_no, port_type_t *port_type, u32 *idx, vtss_serdes_mode_t *mode_req)
{
    u32   port = VTSS_CHIP_PORT(port_no);
    BOOL  lan9668 = (vtss_state->create.target == VTSS_TARGET_LAN9668);

    *port_type = PORT_TYPE_NONE;
    *idx = VTSS_SD6G_40_CNT;
    *mode_req = VTSS_SERDES_MODE_DISABLE;

    VTSS_I("port %u mux_mode %u", port, vtss_state->init_conf.mux_mode);

    switch (vtss_state->init_conf.mux_mode) {
    case VTSS_PORT_MUX_MODE_0:
        // 2xQSGMII
        *port_type = PORT_TYPE_SD;
        if (port < 4) {
            *mode_req = VTSS_SERDES_MODE_QSGMII;
            *idx = 1;
        } else if (lan9668) {
            *mode_req = VTSS_SERDES_MODE_QSGMII;
            *idx = 2;
        }
        break;
    case VTSS_PORT_MUX_MODE_1:
        // 2xCu + 2x2,5G + 1xQSGMII
        *port_type = PORT_TYPE_SD;
        if (port < 2) {
            // Port 0/1: Cu
            *port_type = PORT_TYPE_CUPHY;
            *idx = port;
        } else if (port < 4) {
            // Port 2/3: 2.5G
            *idx = (port - 2);
        } else if (lan9668) {
            // Port 4-7: QSGMII
            *mode_req = VTSS_SERDES_MODE_QSGMII;
            *idx = 2;
        }
        break;

    case VTSS_PORT_MUX_MODE_2:
        // 2xCu + 1x2,5G + 2xRGMII
        *port_type = PORT_TYPE_SD;
        *idx = 2;
        if (port < 2) {
            // Port 0/1: Cu
            *port_type = PORT_TYPE_CUPHY;
            *idx = port;
        } else if (port < 4) {
            // Port 2/3: RGMII
            *port_type = PORT_TYPE_RGMII;
            *idx = (port == 2) ? 0 : 1;
        }
        break;

    case VTSS_PORT_MUX_MODE_5:
        // 2xCu + 3x1G
        *port_type = PORT_TYPE_SD;
        if (port < 2) {
            // Port 0/1: Cu
            *port_type = PORT_TYPE_CUPHY;
            *idx = port;
        } else if (port < 5) {
            // Port 2-4: 2.5G
            *idx = (port - 2);
        }
        break;
    default:
        VTSS_E("unknown mux mode");
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_SYNCE)
static vtss_rc lan966x_synce_clock_in_set(vtss_state_t *vtss_state, const u32 clk_port)
{
#if !defined(VTSS_OPT_FPGA)
    vtss_synce_clock_in_t    *conf;
    u32                      idx = VTSS_SD6G_40_CNT;
    vtss_serdes_mode_t       mode_req = VTSS_SERDES_MODE_DISABLE;
    port_type_t              port_type;
    u32                      clk_src = 0;
    BOOL                     ena;
    u32                      link_stat, clk_div, sd_ena;

    VTSS_D("Enter");

    if (clk_port > 1) {
        VTSS_E("Invalid clock port no: %d\n", clk_port);
        return VTSS_RC_ERROR;
    }
    conf = &vtss_state->synce.in_conf[clk_port];
    if (conf->port_no >= VTSS_PORT_ARRAY_SIZE) {
        VTSS_E("Invalid port no: %d\n", conf->port_no);
        return VTSS_RC_ERROR;
    }
    ena = conf->enable;

    if (lan966x_port_type_calc(vtss_state, conf->port_no, &port_type, &idx, &mode_req) != VTSS_RC_OK) {
        return VTSS_RC_ERROR;
    }

    switch (port_type) {
    case PORT_TYPE_NONE:
        VTSS_E("unknown port type");
        return VTSS_RC_ERROR;
    case PORT_TYPE_SD:
        clk_src = idx;
        break;
    case PORT_TYPE_RGMII:
        clk_src = 3 + idx;
        break;
    case PORT_TYPE_CUPHY:
        clk_src = 5 + idx;
        break;
    }

    VTSS_D("clk_port %X, port_no %u, enable %u, squelch %u, clk_src %u\n", clk_port, conf->port_no, ena, conf->squelsh, clk_src);

    /* Configure the SerDes to select for recovered clock */
    REG_WRM(HSIO_SYNC_ETH_CFG(clk_port),
            HSIO_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(clk_src) |
            HSIO_SYNC_ETH_CFG_RECO_CLK_ENA(ena),
            HSIO_SYNC_ETH_CFG_SEL_RECO_CLK_SRC_M |
            HSIO_SYNC_ETH_CFG_RECO_CLK_ENA_M);

    if (ena && (port_type == PORT_TYPE_SD)) {  /* Enable Port type SERDES */
        /* Enable input clock configuration - now configuring the new (or maybe the same) input port */
        /* In the following the SERDES recovered clock divider is calculated. */
        /* Values are chosen that gives frequency closest to 100 MHz or the frequency closest to a whole number - less decimals */
        clk_div = 0; /* Divide by 1 is default */
        link_stat = 1;
        sd_ena = 1;

        REG_WRM(HSIO_SYNC_ETH_SD_CFG(idx),
                HSIO_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(clk_div) |
                HSIO_SYNC_ETH_SD_CFG_SD_LINK_STAT_ENA(link_stat) |
                HSIO_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(conf->squelsh),
                HSIO_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV_M |
                HSIO_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA_M |
                HSIO_SYNC_ETH_SD_CFG_SD_LINK_STAT_ENA_M);

        REG_WR(HSIO_SIGDET_CFG(idx),
               HSIO_SIGDET_CFG_SD_SEL(1) |
               HSIO_SIGDET_CFG_SD_POL(0) |
               HSIO_SIGDET_CFG_SD_ENA(sd_ena));
    }

    if (ena && (port_type == PORT_TYPE_CUPHY)) {  /* Enable Port type Internal PHY */
        REG_WRM(CHIP_TOP_CUPHY_PORT_CFG(idx),
                CHIP_TOP_CUPHY_PORT_CFG_AUTO_SQUELCH_ENA(conf->squelsh),
                CHIP_TOP_CUPHY_PORT_CFG_AUTO_SQUELCH_ENA_M);
    }
#endif

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

vtss_rc lan966x_rgmii_setup(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_port_interface_t mode, int speed)
{
#if !defined(VTSS_OPT_FPGA)
    bool tx_delay = FALSE;
    bool rx_delay = FALSE;
    int inst;
    u32 port = VTSS_CHIP_PORT(port_no);

    if (port == 2 || port == 5) {
        inst = 0;
    } else if (port == 3 || port == 6) {
        inst = 1;
    } else {
        VTSS_E("illegal rgmii port %d", port);
        return VTSS_RC_ERROR;
    }

    REG_WRM(HSIO_RGMII_CFG(inst),
            HSIO_RGMII_CFG_RGMII_RX_RST(0) |
            HSIO_RGMII_CFG_RGMII_TX_RST(0) |
            HSIO_RGMII_CFG_TX_CLK_CFG(speed),
            HSIO_RGMII_CFG_RGMII_RX_RST_M |
            HSIO_RGMII_CFG_RGMII_TX_RST_M |
            HSIO_RGMII_CFG_TX_CLK_CFG_M);

    if (vtss_state->port.current_if_type[port_no] == mode) {
        return VTSS_RC_OK; // Delay already set
    }

    if (mode == VTSS_PORT_INTERFACE_RGMII_ID ||
        mode == VTSS_PORT_INTERFACE_RGMII_TXID) {
        tx_delay = TRUE;
    }

    if (mode == VTSS_PORT_INTERFACE_RGMII_ID ||
        mode == VTSS_PORT_INTERFACE_RGMII_RXID) {
        rx_delay = TRUE;
    }

    // Setup DLL configuration
    // HSIO_DLL_CFG 0: RGMII0_RXC (RX clock)
    // HSIO_DLL_CFG 1: RGMII0_TXC (TX clock)
    // HSIO_DLL_CFG 2: RGMII1_RXC (RX clock)
    // HSIO_DLL_CFG 3: RGMII1_TXC (TX clock)

    REG_WRM(HSIO_DLL_CFG(inst == 0 ? 0x0 : 0x2),
            HSIO_DLL_CFG_DLL_RST(!rx_delay) |
            HSIO_DLL_CFG_DLL_ENA(rx_delay),
            HSIO_DLL_CFG_DLL_RST_M |
            HSIO_DLL_CFG_DLL_ENA_M);

    REG_WRM(HSIO_DLL_CFG(inst == 0 ? 0x0 : 0x2),
            HSIO_DLL_CFG_DELAY_ENA(rx_delay),
            HSIO_DLL_CFG_DELAY_ENA_M);

    REG_WRM(HSIO_DLL_CFG(inst == 0 ? 0x1 : 0x3),
            HSIO_DLL_CFG_DLL_RST(!tx_delay) |
            HSIO_DLL_CFG_DLL_ENA(tx_delay),
            HSIO_DLL_CFG_DLL_RST_M |
            HSIO_DLL_CFG_DLL_ENA_M);

    REG_WRM(HSIO_DLL_CFG(inst == 0 ? 0x1 : 0x3),
            HSIO_DLL_CFG_DELAY_ENA(tx_delay),
            HSIO_DLL_CFG_DELAY_ENA_M);

#endif // !defined(VTSS_OPT_FPGA)
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
            QSYS_SW_PORT_MODE_INGRESS_DROP_MODE(fc_gen ? 0 : 1),
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

#if !defined(VTSS_OPT_FPGA)
static vtss_rc lan966x_serdes_conf_set(vtss_state_t *vtss_state,
                                       u32 idx, vtss_serdes_mode_t mode)
{
    u32  val, lane_sel, rate, mpll_multi;
    BOOL ref125M;

    // PLL determines whether 125MHz or 25MHz is used
    REG_RD(GCB_HW_STAT, &val);
    val = GCB_HW_STAT_PLL_CONF_X(val);
    ref125M = (val == 1 || val == 2);

    if (mode == VTSS_SERDES_MODE_QSGMII) {
        lane_sel = 0;
        mpll_multi = (ref125M ? 40 : 100);
        rate = 0;
    } else if (mode == VTSS_SERDES_MODE_2G5) {
        lane_sel = 1;
        mpll_multi = (ref125M ? 50 : 125);
        rate = 1;
    } else {
        lane_sel = 1;
        mpll_multi = (ref125M ? 40 : 100);
        rate = 2;
    }

    REG_WR(HSIO_SD_CFG(idx),
           HSIO_SD_CFG_PHY_RESET(1) |
           HSIO_SD_CFG_LANE_10BIT_SEL(lane_sel) |
           HSIO_SD_CFG_RX_RATE(rate) |
           HSIO_SD_CFG_TX_RATE(rate));

    REG_WR(HSIO_MPLL_CFG(idx),
           HSIO_MPLL_CFG_REF_SSP_EN(1) |
           HSIO_MPLL_CFG_MPLL_MULTIPLIER(mpll_multi) |
           HSIO_MPLL_CFG_REF_CLKDIV2(ref125M ? 1 : 0));
    VTSS_MSLEEP(1);

    if (mode == VTSS_SERDES_MODE_DISABLE) {
        // Leave SerDes disabled
        return VTSS_RC_OK;
    }

    REG_WRM(HSIO_SD_CFG(idx),
            HSIO_SD_CFG_PHY_RESET(0),
            HSIO_SD_CFG_PHY_RESET_M);
    VTSS_MSLEEP(1);

    // Enable PLL
    REG_WRM(HSIO_MPLL_CFG(idx),
            HSIO_MPLL_CFG_MPLL_EN(1),
            HSIO_MPLL_CFG_MPLL_EN_M);
    VTSS_MSLEEP(1);

    // Wait for PLL to lock
    REG_RD(HSIO_SD_STAT(idx), &val);
    val = HSIO_SD_STAT_MPLL_STATE_X(val);
    if (val != 1) {
        VTSS_E("sd_stat[%u].mpll_state is %u, expected 1", idx, val);
        return VTSS_RC_ERROR;
    }
    VTSS_D("sd_stat[%u].mpll_state is %u", idx, val);

    // Enable Tx common mode
    REG_WRM(HSIO_SD_CFG(idx),
            HSIO_SD_CFG_TX_CM_EN(1),
            HSIO_SD_CFG_TX_CM_EN_M);
    VTSS_MSLEEP(1);

    // Wait for Tx common state
    REG_RD(HSIO_SD_STAT(idx), &val);
    val = HSIO_SD_STAT_TX_CM_STATE_X(val);
    if (val != 1) {
        VTSS_E("sd_stat[%u].tx_cm_state is %u, expected 1", idx, val);
        return VTSS_RC_ERROR;
    }
    VTSS_D("sd_stat[%u].tx_cm_state is %u", idx, val);

    // Enable Rx PLL
    REG_WRM(HSIO_SD_CFG(idx),
            HSIO_SD_CFG_RX_PLL_EN(1) |
            HSIO_SD_CFG_TX_EN(1),
            HSIO_SD_CFG_RX_PLL_EN_M |
            HSIO_SD_CFG_TX_EN_M);
    VTSS_MSLEEP(1);

    // Wait for Rx DPLL to lock
    REG_RD(HSIO_SD_STAT(idx), &val);
    val = HSIO_SD_STAT_RX_PLL_STATE_X(val);
    if (val != 1) {
        VTSS_E("sd_stat[%u].rx_pll_state is %u, expected 1", idx, val);
        return VTSS_RC_ERROR;
    }
    VTSS_D("sd_stat[%u].rx_pll_state is %u", idx, val);

    // Wait for Tx operational
    REG_RD(HSIO_SD_STAT(idx), &val);
    val = HSIO_SD_STAT_TX_STATE_X(val);
    if (val != 1) {
        VTSS_E("sd_stat[%u].tx_state is %u, expected 1", idx, val);
        return VTSS_RC_ERROR;
    }
    VTSS_D("sd_stat[%u].tx_state is %u", idx, val);

    // Enable Rx/Tx
    REG_WRM(HSIO_SD_CFG(idx),
            HSIO_SD_CFG_TX_DATA_EN(1) |
            HSIO_SD_CFG_RX_DATA_EN(1),
            HSIO_SD_CFG_TX_DATA_EN_M |
            HSIO_SD_CFG_RX_DATA_EN_M);
    return VTSS_RC_OK;
}
#endif
static vtss_rc lan966x_serdes_cfg(vtss_state_t *vtss_state,
                                  vtss_port_no_t port_no, vtss_serdes_mode_t mode)
{
    vtss_rc                  rc = VTSS_RC_OK;
#if !defined(VTSS_OPT_FPGA)
#if VTSS_OPT_TRACE
    u32                      port = VTSS_CHIP_PORT(port_no);
#endif
    u32                      idx = VTSS_SD6G_40_CNT;
    vtss_serdes_mode_t       mode_req = VTSS_SERDES_MODE_DISABLE;
    port_type_t              port_type = PORT_TYPE_NONE;

    if ((rc = lan966x_port_type_calc(vtss_state, port_no, &port_type, &idx, &mode_req)) != VTSS_RC_OK) {
        return rc;
    }

    if (port_type != PORT_TYPE_SD) {
        VTSS_I("port %u port_type %u is not a SERDES port", port, port_type);
        vtss_state->port.serdes_mode[port_no] = VTSS_SERDES_MODE_NONE;
        return VTSS_RC_OK;
    }

    if (mode_req != VTSS_SERDES_MODE_DISABLE && mode != mode_req) {
        VTSS_E("port %u must be %s", port, vtss_serdes_if_txt(mode_req));
        return VTSS_RC_ERROR;
    }
    if (idx < VTSS_SD6G_40_CNT && vtss_state->port.sd6g40_mode[idx] != mode) {
        vtss_state->port.sd6g40_mode[idx] = mode;
        rc = lan966x_serdes_conf_set(vtss_state, idx, mode);
    }
    vtss_state->port.serdes_mode[port_no] = mode;
#endif
    return rc;
}

static vtss_rc fa_port_flush(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32      port = VTSS_CHIP_PORT(port_no);
    u32      delay = 0, value;
    vtss_rc  rc = VTSS_RC_OK;

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

    return rc;

    /* The port is disabled and flushed, now set up the port in the new operating mode */
}

static vtss_rc lan966x_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_rc                rc = VTSS_RC_OK;
    vtss_port_conf_t       *conf = &vtss_state->port.conf[port_no];
    u32                    port = VTSS_CHIP_PORT(port_no), i, p;
    u32                    value, link_speed = 1, pfc_mask;
    BOOL                   disable = conf->power_down, disable_serdes = 0, giga = 1, rgmii = 0;
    BOOL                   loop = (conf->loop == VTSS_PORT_LOOP_PCS_HOST), skip_port_flush = 0;
    vtss_port_speed_t      speed = conf->speed, sgmii = 0;
    vtss_port_frame_gaps_t gaps;
    vtss_serdes_mode_t     mode = VTSS_SERDES_MODE_SGMII;
#if !defined(VTSS_OPT_FPGA)
    u32                    idx = VTSS_SD6G_40_CNT;
    vtss_serdes_mode_t     mode_req = VTSS_SERDES_MODE_DISABLE;
    port_type_t            port_type = PORT_TYPE_NONE;
#endif

    /* Verify speed and interface type */
    switch (speed) {
    case VTSS_SPEED_10M:
        link_speed = 3;
        break;
    case VTSS_SPEED_100M:
        link_speed = 2;
        break;
    case VTSS_SPEED_1G:
        break;
    case VTSS_SPEED_2500M:
        if (conf->if_type == VTSS_PORT_INTERFACE_SERDES ||
            conf->if_type == VTSS_PORT_INTERFACE_VAUI   ||
            conf->if_type == VTSS_PORT_INTERFACE_SGMII_2G5) {
            break;
        }
        // Fall through
    default:
        VTSS_E("illegal speed: %u, port %u", speed, port);
        return VTSS_RC_ERROR;
    }

    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        disable = 1;
        break;
#if defined(VTSS_OPT_FPGA)
    case VTSS_PORT_INTERFACE_GMII:
#endif
    case VTSS_PORT_INTERFACE_SGMII:
        sgmii = 1;
        break;
    case VTSS_PORT_INTERFACE_RGMII:
    case VTSS_PORT_INTERFACE_RGMII_RXID:
    case VTSS_PORT_INTERFACE_RGMII_TXID:
    case VTSS_PORT_INTERFACE_RGMII_ID:
        if (port != 2 && port != 3 && port != 5 && port != 6) {
            VTSS_E("Port %u does not support RGMII", port);
            return VTSS_RC_ERROR;
        }
        rgmii = 1;
        break;
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        disable_serdes = 1;
        sgmii = 1;
        break;
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        if (speed == VTSS_SPEED_2500M) {
            mode = VTSS_SERDES_MODE_2G5;
        } else {
            sgmii = 1;
        }
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        mode = VTSS_SERDES_MODE_QSGMII;
        break;
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
        disable_serdes = 1;
        if (speed == VTSS_SPEED_2500M) {
            mode = VTSS_SERDES_MODE_2G5;
        } else if (speed != VTSS_SPEED_1G) {
            VTSS_E("illegal speed 10/100, port %u", port);
            return VTSS_RC_ERROR;
        }
        break;
    default:
        VTSS_E("illegal interface, port %u", port);
        return VTSS_RC_ERROR;
    }

    if (sgmii && disable && !disable_serdes) {
        // power-down a port connected to a phy. Port flush/disable not needed.
        skip_port_flush = 1;
    }

    if (disable && disable_serdes) {
        // Disable SerDes to cause link down at the other end
        mode = VTSS_SERDES_MODE_DISABLE;
    }
    if (!skip_port_flush) {
        // Flush and disable the port
        VTSS_RC(fa_port_flush(vtss_state, port_no));
    }
    // Setup SerDes
    VTSS_RC(lan966x_serdes_cfg(vtss_state, port_no, mode));

    /* Configure framelength check (from ethertype / length field) */
    REG_WRM_CTL(DEV_MAC_ADV_CHK_CFG(port), conf->frame_length_chk, DEV_MAC_ADV_CHK_CFG_LEN_DROP_ENA_M);

    /* GIG/FDX mode */
    if (conf->fdx) {
        value = DEV_MAC_MODE_CFG_FDX_ENA_M;
    } else {
        REG_WRM_SET(SYS_FRONT_PORT_MODE(port), SYS_FRONT_PORT_MODE_HDX_MODE_M);
        value = (conf->flow_control.obey ? DEV_MAC_MODE_CFG_FC_WORD_SYNC_ENA_M : 0);
    }

#if !defined(VTSS_OPT_FPGA)
    VTSS_RC(lan966x_port_type_calc(vtss_state, port_no, &port_type, &idx, &mode_req));
    if (port_type != PORT_TYPE_SD && link_speed != 1) {
        /* RGMII or Internal phy in 10/100 mode = GIG mode disabled */
        giga = 0;
    }
#endif
#if defined(VTSS_OPT_FPGA)
        giga = link_speed == 1 ? 1 : 0;
#endif
    if (giga) {
        value |= DEV_MAC_MODE_CFG_GIGA_MODE_ENA_M;
    }
    REG_WR(DEV_MAC_MODE_CFG(port), value);
#if !defined(VTSS_OPT_FPGA)
    // Internal PHYs
    if (port < 2) {
        REG_WRM_CTL(CHIP_TOP_CUPHY_PORT_CFG(port),
                    giga, CHIP_TOP_CUPHY_PORT_CFG_GTX_CLK_ENA_M);
    }
#endif

    /* Default gaps */
    gaps.fdx_gap = (conf->fdx ? 6 : 5);
    gaps.hdx_gap_1 = (speed == VTSS_SPEED_10M ? 2 : 1);
    gaps.hdx_gap_2 = 2;

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

    // Choose SGMII or SerDes PCS mode
    REG_WR(DEV_PCS1G_MODE_CFG(port), DEV_PCS1G_MODE_CFG_SGMII_MODE_ENA(sgmii));

    // PCS setup
    if (sgmii) {
        // Set whole register
        REG_WR(DEV_PCS1G_ANEG_CFG(port), DEV_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(1));
    } else {
        // Clear specific bit only
        REG_WRM_CLR(DEV_PCS1G_ANEG_CFG(port), DEV_PCS1G_ANEG_CFG_SW_RESOLVE_ENA_M);
    }

    REG_WR(DEV_PCS1G_SD_CFG(port),
           DEV_PCS1G_SD_CFG_SD_SEL(conf->sd_internal ? 0 : 1) |
           DEV_PCS1G_SD_CFG_SD_POL(conf->sd_active_high) |
           DEV_PCS1G_SD_CFG_SD_ENA(conf->sd_enable));

    // Enable/disable PCS
    REG_WR(DEV_PCS1G_CFG(port), DEV_PCS1G_CFG_PCS_ENA(disable ? 0 : 1));

    if (conf->if_type == VTSS_PORT_INTERFACE_SGMII ||
        conf->if_type == VTSS_PORT_INTERFACE_SGMII_2G5) {
        REG_WR(DEV_PCS1G_ANEG_CFG(port), 0);
    } else if (conf->if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
        // Complete SGMII aneg
        REG_WR(DEV_PCS1G_ANEG_CFG(port),
               DEV_PCS1G_ANEG_CFG_ADV_ABILITY(0x0001) |
               DEV_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(1) |
               DEV_PCS1G_ANEG_CFG_RESTART_ONE_SHOT(1) |
               DEV_PCS1G_ANEG_CFG_ENA(1));
        REG_WR(DEV_PCS1G_STICKY(port), 0xffffffff);
    }

    // Update vtss_state database accordingly
    lan966x_port_clause_37_control_get(vtss_state, port_no, &vtss_state->port.clause_37[port_no]);

    // Loopback mode
#if defined(VTSS_OPT_FPGA)
    REG_WRM(DEV_PORT_MISC(port),
            DEV_PORT_MISC_DEV_LOOP_ENA(loop ? 2 : 0),
            DEV_PORT_MISC_DEV_LOOP_ENA_M);
    REG_WRM(SYS_FRONT_PORT_MODE(port),
            SYS_FRONT_PORT_MODE_DONT_WAIT_FOR_TS(loop ? 1 : 0),
            SYS_FRONT_PORT_MODE_DONT_WAIT_FOR_TS_M);
#else
    REG_WR(DEV_PCS1G_LB_CFG(port), DEV_PCS1G_LB_CFG_TBI_HOST_LB_ENA(loop));
#endif

    /* Set Max Length and maximum tags allowed */
    REG_WR(DEV_MAC_MAXLEN_CFG(port), conf->max_frame_length);
    VTSS_RC(vtss_lan966x_port_max_tags_set(vtss_state, port_no));

#if defined(VTSS_FEATURE_QOS)
    // Setup QoS - in reset
    VTSS_RC(vtss_lan966x_qos_port_change(vtss_state, port_no, TRUE));
#endif

    if (conf->if_type == VTSS_PORT_INTERFACE_NO_CONNECTION) {
        /* Core: Enable port for frame transfer */
        REG_WRM_SET(QSYS_SW_PORT_MODE(port), QSYS_SW_PORT_MODE_PORT_ENA_M);
    } else if (!disable) {
        /* Enable MAC module */
        REG_WR(DEV_MAC_ENA_CFG(port),
               DEV_MAC_ENA_CFG_RX_ENA_M |
               DEV_MAC_ENA_CFG_TX_ENA_M);

        if (rgmii) {
            VTSS_RC(lan966x_rgmii_setup(vtss_state, port_no, conf->if_type, link_speed));

            REG_WRM(DEV_CLOCK_CFG(port),
                    DEV_CLOCK_CFG_LINK_SPEED(link_speed) |
                    DEV_CLOCK_CFG_PORT_RST(0) |
                    DEV_CLOCK_CFG_MAC_RX_RST(0) |
                    DEV_CLOCK_CFG_MAC_TX_RST(0),
                    DEV_CLOCK_CFG_LINK_SPEED_M |
                    DEV_CLOCK_CFG_PORT_RST_M |
                    DEV_CLOCK_CFG_MAC_RX_RST_M |
                    DEV_CLOCK_CFG_MAC_TX_RST_M);
        } else {
            /* Take MAC, Port, Phy (intern) and PCS (SGMII/Serdes) clock out of reset */
            REG_WR(DEV_CLOCK_CFG(port), DEV_CLOCK_CFG_LINK_SPEED(link_speed));
        }

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

    // For QSGMII, make sure PCS Tx is out of reset with valid speed for all 4 ports
    if (mode == VTSS_SERDES_MODE_QSGMII) {
        for (i = 0; i < 4; i++) {
            p = ((port & 4) + i);
            REG_RD(DEV_CLOCK_CFG(p), &value);
            if (DEV_CLOCK_CFG_PCS_TX_RST_X(value)) {
                value &= ~DEV_CLOCK_CFG_PCS_TX_RST_M;
                if (DEV_CLOCK_CFG_LINK_SPEED_X(value) == 0) {
                    value |= DEV_CLOCK_CFG_LINK_SPEED(1);
                }
                REG_WR(DEV_CLOCK_CFG(p), value);
            }
        }
    }

    vtss_state->port.current_speed[port_no] = vtss_state->port.conf[port_no].speed;
    vtss_state->port.current_if_type[port_no] = vtss_state->port.conf[port_no].if_type;
    vtss_state->port.current_mt[port_no] = vtss_state->port.conf[port_no].serdes.media_type;

#if defined(VTSS_FEATURE_QOS)
    // Setup QoS - out of reset
    VTSS_RC(vtss_lan966x_qos_port_change(vtss_state, port_no, FALSE));
#endif
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
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    u32              val, port = VTSS_CHIP_PORT(port_no);

    if (conf->if_type == VTSS_PORT_INTERFACE_VAUI) {
        REG_RD(DEV_PCS1G_LINK_STATUS(port), &val);
        status->link = DEV_PCS1G_LINK_STATUS_LINK_STATUS_X(val);
        REG_RD(DEV_PCS1G_STICKY(port), &val);
        status->link_down = DEV_PCS1G_STICKY_LINK_DOWN_STICKY_X(val);
        if (status->link_down) {
            REG_WR(DEV_PCS1G_STICKY(port), DEV_PCS1G_STICKY_LINK_DOWN_STICKY_M);
        }
        status->speed = VTSS_SPEED_2500M;
        status->fdx = 1;
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
static vtss_rc vtss_lan966x_dual_cnt_update(vtss_state_t *vtss_state,
                                            u32 *addr, vtss_dual_counter_t *counter, BOOL clear)
{
    u32 base = *addr;

    // E-MAC counters
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, addr, &counter->emac, clear));
    // P-MAC counters, offset depends on Rx/Tx
    *addr = (base + (base < 0x80 ? 0x30 : base < 0x84 ? 0x23 : 0x21));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, addr, &counter->pmac, clear));
    *addr = (base + 1); // Next E-MAC counter address
    return VTSS_RC_OK;
}
#define CNT_SUM(cnt) (cnt.emac.value + cnt.pmac.value)
#else
static vtss_rc vtss_lan966x_dual_cnt_update(vtss_state_t *vtss_state,
                                            u32 *addr, vtss_chip_counter_t *counter, BOOL clear)
{
    // E-MAC counters
    return vtss_lan966x_counter_update(vtss_state, addr, counter, clear);
}
#define CNT_SUM(cnt) (cnt.value)
#endif

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
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_port_dot3br_counters_t        *dot3br;
#endif

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
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_mm_assembly_errors, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_mm_smd_errors, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_mm_assembly_ok, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->rx_mm_fragments, clear));
#endif

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
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_llct, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_ct, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_mm_hold, clear));
    VTSS_RC(vtss_lan966x_counter_update(vtss_state, p, &c->tx_mm_fragments, clear));
#endif

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
    for (i = 0; i < VTSS_PRIOS; i++) {
        rmon->tx_etherStatsDropEvents += (c->dr_yellow_class[i].value + c->dr_green_class[i].value);
    }

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
    if_group->ifOutDiscards = rmon->tx_etherStatsDropEvents;
    if_group->ifOutErrors = (c->tx_drops.value + c->tx_aging.value);

    /* Ethernet-like counters */
    elike->dot3InPauseFrames = CNT_SUM(c->rx_pause) + CNT_SUM(c->rx_control);
    elike->dot3OutPauseFrames = CNT_SUM(c->tx_pause);

    /* Bridge counters */
    counters->bridge.dot1dTpPortInDiscards = (c->rx_classified_drops.value + c->dr_local.value);
    for (i = 0; i < VTSS_PRIOS; i++) {
        counters->bridge.dot1dTpPortInDiscards += c->rx_red_class[i].value;
    }

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    /* 802.3br counters */
    dot3br = &counters->dot3br;
    dot3br->aMACMergeFrameAssErrorCount = c->rx_mm_assembly_errors.value;
    dot3br->aMACMergeFrameSmdErrorCount = c->rx_mm_smd_errors.value;
    dot3br->aMACMergeFrameAssOkCount = c->rx_mm_assembly_ok.value;
    dot3br->aMACMergeFragCountRx = c->rx_mm_fragments.value;
    dot3br->aMACMergeFragCountTx = c->tx_mm_fragments.value;
    dot3br->aMACMergeHoldCount = c->tx_mm_hold.value;
#endif

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
    VTSS_MEMSET(counters, 0, sizeof(*counters));
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
    int q, i;
    u32 port, value;

    // Default watermarks are used
    for (q = 0; q < VTSS_PRIOS; q++) {
        /* Save initial encoded value of shared area for later use by WRED */
        REG_RD(QSYS_RES_CFG((q + 216 + 512)), &vtss_state->port.buf_prio_shr[q]);
    }
    // Set source buffer size for each priority and each port to 1500 bytes */
    for (i = 0; i <= 95; i++) {
        REG_WR(QSYS_RES_CFG((i)), 1700/64);
        REG_WR(QSYS_RES_CFG((512 + i)), 1700/64);
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

#if VTSS_OPT_DEBUG_PRINT

/* - Debug print --------------------------------------------------- */

static vtss_rc lan966x_debug_port(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    vtss_port_no_t port_no;
    u32            port;
    char           buf[32];
#if !defined(VTSS_OPT_FPGA)
    u32            i;

    VTSS_SPRINTF(buf, "Mux Mode %u", vtss_state->init_conf.mux_mode);
    vtss_lan966x_debug_reg_header(pr, buf);
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(HSIO_HW_CFG), "HW_CFG");
    pr("\n");

    for (i = 0; i < VTSS_SD6G_40_CNT; i++) {
        VTSS_SPRINTF(buf, "SD6G[%u]: %s", i, vtss_serdes_if_txt(vtss_state->port.sd6g40_mode[i]));
        vtss_lan966x_debug_reg_header(pr, buf);
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(HSIO_SD_CFG(i)), "SD_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(HSIO_SD_CFG2(i)), "SD_CFG2");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(HSIO_MPLL_CFG(i)), "MPLL_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(HSIO_SD_STAT(i)), "SD_STAT");
        pr("\n");
    }
#endif
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        port_no = vtss_cmn_port2port_no(vtss_state, info, port);
        if (port_no == VTSS_PORT_NO_NONE) {
            continue;
        }
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_lan966x_debug_reg_header(pr, buf);
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_CLOCK_CFG(port)), "CLOCK_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_MAC_ENA_CFG(port)), "MAC_ENA_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_MAC_MODE_CFG(port)), "MAC_MODE_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_MAC_ADV_CHK_CFG(port)), "MAC_ADV_CHK_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_MAC_IFG_CFG(port)), "MAC_IFG_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_MAC_HDX_CFG(port)), "MAC_HDX_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_MAC_MAXLEN_CFG(port)), "MAC_MAXLEN_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(QSYS_SW_PORT_MODE(port)), "SW_PORT_MODE");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(QSYS_PORT_MODE(port)), "PORT_MODE");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_FRONT_PORT_MODE(port)), "SW_PORT_MODE");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_PAUSE_CFG(port)), "SYS_PAUSE_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(ANA_PFC_CFG(port)), "ANA_PFC_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PORT_MISC(port)), "PORT_MISC");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PCS1G_CFG(port)), "PCS1G_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PCS1G_SD_CFG(port)), "PCS1G_SD_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PCS1G_ANEG_CFG(port)), "PCS1G_ANEG_CFG");
        pr("\n");
    }
    return VTSS_RC_OK;
}

static void lan966x_debug_cnt_inst(const vtss_debug_printf_t pr, u32 i,
                                   const char *col1, const char *col2,
                                   vtss_chip_counter_t *c1, vtss_chip_counter_t *c2)
{
    char buf1[80], buf2[80];

    VTSS_SPRINTF(buf1, "%s_%u", col1 && VTSS_STRLEN(col1) ? col1 : col2, i);
    VTSS_SPRINTF(buf2, "%s_%u", col2 && VTSS_STRLEN(col2) ? col2 : col1, i);
    vtss_lan966x_debug_cnt(pr, col1 ? buf1 : col1, col2 ? buf2 : col2, c1, c2);
}

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
static void lan966x_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                              vtss_dual_counter_t *c1, vtss_dual_counter_t *c2)
{
    u32  i;
    char buf1[32], buf2[32];
    const char *name;
    vtss_chip_counter_t *c;

    for (i = 0; i < 2; i++) {
        if (i) {
            name = "pmac";
            c = &c1->pmac;
        } else {
            name = "emac";
            c = &c1->emac;
        }
        VTSS_SPRINTF(buf1, "%s_%s", name, col1);
        if (col2 == NULL) {
            vtss_lan966x_debug_cnt(pr, buf1, NULL, c, NULL);
        } else {
            if (VTSS_STRLEN(col2) != 0) {
                VTSS_SPRINTF(buf2, "%s_%s", name, col2);
            } else {
                VTSS_STRCPY(buf2, "");
            }
            vtss_lan966x_debug_cnt(pr, buf1, buf2, c, i ? &c2->pmac : &c2->emac);
        }
    }
}
#else
static void lan966x_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                              vtss_chip_counter_t *c1, vtss_chip_counter_t *c2)
{
    vtss_lan966x_debug_cnt(pr, col1, col2, c1, c2);
}
#endif

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
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
            vtss_lan966x_debug_cnt(pr, "mm_ass_err", NULL, &cnt->rx_mm_assembly_errors, NULL);
            vtss_lan966x_debug_cnt(pr, "mm_smd_err", NULL, &cnt->rx_mm_smd_errors, NULL);
            vtss_lan966x_debug_cnt(pr, "mm_ass_ok",  "mm_hold", &cnt->rx_mm_assembly_ok, &cnt->tx_mm_hold);
            vtss_lan966x_debug_cnt(pr, "mm_frag", "", &cnt->rx_mm_fragments, &cnt->tx_mm_fragments);
#endif
        }

        // QS counters
        if (info->full || cpu_port || info->action == 3) {
            vtss_lan966x_debug_cnt(pr, "cat_drop", cpu_port ? NULL : "drops",
                                   &cnt->rx_classified_drops, &cnt->tx_drops);
            vtss_lan966x_debug_cnt(pr, "dr_local", cpu_port ? NULL : "aged",
                                   &cnt->dr_local, &cnt->tx_aging);
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
            vtss_lan966x_debug_cnt(pr, "dr_tail", cpu_port ? NULL : "ct",
                                   &cnt->dr_tail, &cnt->tx_ct);
            if (!cpu_port) {
                vtss_lan966x_debug_cnt(pr, NULL, "llct", NULL, &cnt->tx_llct);
            }
#else
            vtss_lan966x_debug_cnt(pr, "dr_tail", NULL, &cnt->dr_tail, NULL);
#endif
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, "green", "",
                                       &cnt->rx_green_class[i], &cnt->tx_green_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, "yellow", "",
                                       &cnt->rx_yellow_class[i], &cnt->tx_yellow_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, "red", "dr_green", &cnt->rx_red_class[i], &cnt->dr_green_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                lan966x_debug_cnt_inst(pr, i, NULL, "dr_yellow", NULL, &cnt->dr_yellow_class[i]);
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
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT, lan966x_debug_port, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT_CNT, lan966x_debug_port_cnt, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_WM, lan966x_debug_wm, vtss_state, pr, info));
    return VTSS_RC_OK;
}
#endif // VTSS_OPT_DEBUG_PRINT

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

        // Count QS drops at egress port
        REG_WRM_SET(QSYS_STAT_CFG, QSYS_STAT_CFG_DROP_COUNT_EGRESS(1));
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
