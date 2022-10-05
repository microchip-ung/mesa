// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// #include <cyg/infra/diag.h>
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_jaguar2_cil.h"
#if defined(VTSS_ARCH_JAGUAR_2)

#if defined(VTSS_ARCH_SERVAL_T)
#include "../omega/vtss_omega_clock_cil.h"
#endif //defined(VTSS_ARCH_SERVAL_T)

static vtss_rc jr2_port_counters_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no);

static vtss_rc jr2_port_clause_37_control_get(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no,
                                               vtss_port_clause_37_control_t *const control)
{
    u32 value, port = VTSS_CHIP_PORT(port_no);
    u32 tgt = VTSS_TO_DEV1G(port);

    JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt), &value);
    control->enable = VTSS_BOOL(VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA(value));
    value = VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(control->enable ? value : 0);
    VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &control->advertisement));

    return VTSS_RC_OK;
}

static vtss_rc jr2_port_clause_37_control_set(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no)
{
    vtss_port_clause_37_control_t *control = &vtss_state->port.clause_37[port_no];
    u32 value;
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 tgt = VTSS_TO_DEV1G(port);

    /* Aneg capabilities for this port */
    VTSS_RC(vtss_cmn_port_clause_37_adv_set(&value, &control->advertisement, control->enable));

    /* Set aneg capabilities, enable neg and restart */
    JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
           VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(value) |
           VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA(1) |
           VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1));

    if (!control->enable) {
        /* Disable Aneg */
        JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(0) |
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA(0) |
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1));
    }

    return VTSS_RC_OK;
}


static vtss_rc jr2_port_clause_37_status_get(vtss_state_t *vtss_state,
                                              const vtss_port_no_t         port_no,
                                              vtss_port_clause_37_status_t *const status)

{
    u32                    value;
    vtss_port_sgmii_aneg_t *sgmii_adv = &status->autoneg.partner.sgmii;
    u32                    port = VTSS_CHIP_PORT(port_no);
    u32                    tgt = VTSS_TO_DEV1G(port);

    if (vtss_state->port.conf[port_no].power_down) {
        status->link = 0;
        return VTSS_RC_OK;
    }

    /* Get the link state 'down' sticky bit  */
    JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);
    status->link = (JR2_BF(DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY, value) ? 0 : 1);
    if (status->link == 0) {
        /* The link has been down. Clear the sticky bit and return the 'down' value  */
        JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt),
                VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY);
    } else {
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(tgt), &value);
        status->link = JR2_BF(DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS, value) &&
                       JR2_BF(DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS, value);
    }

    /* Get PCS ANEG status register */
    JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS(tgt), &value);

    /* Get 'Aneg complete'   */
    status->autoneg.complete = JR2_BF(DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);

   /* Workaround for a Serdes issue, when aneg completes with FDX capability=0 */
    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SERDES) {
        if (status->autoneg.complete) {
            if (((value >> 21) & 0x1) == 0) {
                JR2_WRM_CLR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
                JR2_WRM_SET(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
                (void)jr2_port_clause_37_control_set(vtss_state, port_no); /* Restart Aneg */
                VTSS_MSLEEP(50);
                JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS(tgt), &value);
                status->autoneg.complete = JR2_BF(DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);
            }
        }
    }

    /* Return partner advertisement ability */
    value = VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_LP_ADV_ABILITY(value);

    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
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
    } else {
        VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &status->autoneg.partner.cl37));
    }

    return VTSS_RC_OK;
}

#define JR2_SERDES_TYPE_1G  1
#define JR2_SERDES_TYPE_6G  6
#define JR2_SERDES_TYPE_10G 10

static vtss_rc jr2_port_inst_get(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *tgt, u32 *serdes_inst, u32 *serdes_type)
{
    u32 t=0, t0=0, t1=0, si=0, st=0, port = VTSS_CHIP_PORT(port_no);

    if ((serdes_inst == NULL) && (serdes_type == NULL) && (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_NO_CONNECTION)) {
        *tgt = VTSS_TO_DEV(port);
        return VTSS_RC_OK;
    }

#if defined(VTSS_ARCH_SERVAL_T)
    if (VTSS_PORT_IS_10G(port)) {
        if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SFI) {
            // Dev10G_0-1 connected to SD10G 2-3
            st = JR2_SERDES_TYPE_10G;
            si = (port == 9) ? 2 : 3;
            t  = (port - VTSS_PORT_10G_START);
            t0 = VTSS_TO_DEV10G_0;
            t1 = VTSS_TO_DEV10G_1;
        } else {
            // Dev2G5_9-10 (also) connected to SD10G 2-3
            st = JR2_SERDES_TYPE_10G;
            si = (port == 9) ? 2 : 3;
            t = port;
            t0 = VTSS_TO_DEV2G5_0;
            t1 = VTSS_TO_DEV2G5_1;
        }
    } else {
        if (port < 5) {
            st = JR2_SERDES_TYPE_1G;
            si = port; // 1G Serdes 0-4
            t0 = VTSS_TO_DEV2G5_0;
            t1 = VTSS_TO_DEV2G5_1;
        } else if (port < 7) {
            st = JR2_SERDES_TYPE_6G;
            si = (port - 5); // 6G serdes <--> 2G5dev 5-6
            t0 = VTSS_TO_DEV2G5_0;
            t1 = VTSS_TO_DEV2G5_1;
        } else {
            st = JR2_SERDES_TYPE_10G;
            si = (port - 7); // 10G serdes 0,1 <--> 2G5dev 7,8
            t0 = VTSS_TO_DEV2G5_0;
            t1 = VTSS_TO_DEV2G5_1;
        }
        t  = port;
    }
#else

    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_QSGMII || (port >= 32 && port < 48)) {
        st = JR2_SERDES_TYPE_6G;
        if (port < 8) {
            // DEV1G, QSGMII on hw pin S13-S14. 6G macro 4-5
            si = ((port >> 2) + 4);
            t0 = VTSS_TO_DEV1G_0;
            t1 = VTSS_TO_DEV1G_1;
            t  = port;
        } else if (port >= 8 && port < 32) {
            // DEV2G5, QSGMII on hw pin S15-S20. 6G macro 6-11
            si = ((port >> 2) + 4);
            t0 = VTSS_TO_DEV2G5_0;
            t1 = VTSS_TO_DEV2G5_1;
            t  = (port - 8);
        } else if (port >= 32 && port < 48) {
            // DEV1G on QSGMII only, hw pin S21-S24. 6G macro 12-15
            si = ((port >> 2) + 4);
            t0 = VTSS_TO_DEV1G_0;
            t1 = VTSS_TO_DEV1G_1;
            t  = (port - 24);
        } else {
            VTSS_E("Illegal port: %u", port);
            return VTSS_RC_ERROR;
        }
    } else {
        if (port < 8) {
            // DEV1G
            st = JR2_SERDES_TYPE_1G;
            si = (port + 1);
            t0 = VTSS_TO_DEV1G_0;
            t1 = VTSS_TO_DEV1G_1;
            t  = port;
        } else if (port >= 8 && port < 32) {
            // DEV2G5
            st = JR2_SERDES_TYPE_6G;
            si = (port - 8);
            t0 = VTSS_TO_DEV2G5_0;
            t1 = VTSS_TO_DEV2G5_1;
            t  = (port - 8);
        } else if (port == VTSS_CHIP_PORT_NPI) {
            // NPI
            st = JR2_SERDES_TYPE_1G;
            si = 0;
            t0 = VTSS_TO_DEV2G5_0;
            t1 = VTSS_TO_DEV2G5_1;
            t  = 24;
        } else if (port >= VTSS_PORT_10G_START && port < VTSS_CHIP_PORTS) {
            if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SFI) {
                // SFP+
                st = JR2_SERDES_TYPE_10G;
                si = (port - VTSS_PORT_10G_START);
                t0 = VTSS_TO_DEV10G_0;
                t1 = VTSS_TO_DEV10G_1;
                t  = (port - VTSS_PORT_10G_START);
            } else if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_XAUI ||
                       vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_RXAUI) {
                // XAUI/RXAUI
                st = JR2_SERDES_TYPE_6G;
                si = (port == 49) ? 0xF0000 : (port == 50) ? 0xF00000 : (port == 51) ? 0xF00 : 0xF000;
                t0 = VTSS_TO_DEV10G_0;
                t1 = VTSS_TO_DEV10G_1;
                t  = (port - VTSS_PORT_10G_START);
            } else {
                // Dev2G5_25-28 connected to SD10G
                st = JR2_SERDES_TYPE_10G;
                si = (port - VTSS_PORT_10G_START);
                t0 = VTSS_TO_DEV2G5_0;
                t1 = VTSS_TO_DEV2G5_1;
                t = 25 + (port - VTSS_PORT_10G_START);
            }
        } else {
            VTSS_E("Illegal port: %u", port);
            return VTSS_RC_ERROR;
        }
    }
#endif /* VTSS_ARCH_SERVAL_T */

    *tgt = (t*(t1 - t0) + t0);
    if (serdes_inst != NULL) {
        *serdes_inst = si;
    }
    if (serdes_type != NULL) {
        *serdes_type = st;
    }

    return VTSS_RC_OK;
}

/* - CIL functions ------------------------------------------------- */

#if defined(VTSS_FEATURE_SYNCE)
#define RCVRD_CLK_GPIO_NO 33      // on servalt the 4 recovered clock outputs are GPIO 33-36
static vtss_rc jr2_synce_clock_out_set(vtss_state_t *vtss_state, const vtss_synce_clk_port_t clk_port_par)
{
    u32 div_mask = 0;
    vtss_synce_clk_port_t clk_port = clk_port_par;
#if defined(VTSS_ARCH_SERVAL_T)
    u32 rcvrd_clk_src_idx;
#endif
    if (clk_port > 3) {
        VTSS_E("Invalid clock port no: %d\n", clk_port);
        return VTSS_RC_ERROR;
    }
    VTSS_D("clk_port %X  enable %u\n", clk_port, vtss_state->synce.out_conf[clk_port].enable);

#if defined(VTSS_ARCH_SERVAL_T)
    switch (vtss_state->synce.out_conf[clk_port].divider) {
        case VTSS_SYNCE_DIVIDER_1: div_mask = 6; break;
        case VTSS_SYNCE_DIVIDER_4: div_mask = 1; break;
        case VTSS_SYNCE_DIVIDER_5: div_mask = 4; break;
        case VTSS_SYNCE_DIVIDER_2: div_mask = 0; break;
        case VTSS_SYNCE_DIVIDER_8: div_mask = 2; break;
        case VTSS_SYNCE_DIVIDER_16: div_mask = 3; break;
        case VTSS_SYNCE_DIVIDER_25: div_mask = 5; break;
    }

#if defined(VTSS_FEATURE_CLOCK)
    rcvrd_clk_src_idx = clk_port + 4;  // In serval T with internal DPLL, recovered clock 4-7 are used as clock inputs to the internal EEC Controller(s)
#else
    rcvrd_clk_src_idx = clk_port + 1;  // In serval T with external DPLL, recovered clock 1-3 are used as clock inputs to the external DPLL
#endif
    VTSS_D("divider %d, div_mask %d, rcvrd_clk_src_idx %d\n", vtss_state->synce.out_conf[clk_port].divider, div_mask, rcvrd_clk_src_idx);
    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(rcvrd_clk_src_idx),
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_DIV(div_mask) |
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA(vtss_state->synce.out_conf[clk_port].enable),
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_DIV |
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA);
#if !defined(VTSS_FEATURE_CLOCK)
    if (VTSS_RC_OK != vtss_jr2_gpio_mode(vtss_state, 0, RCVRD_CLK_GPIO_NO + rcvrd_clk_src_idx, VTSS_GPIO_ALT_0)) {
        VTSS_E("Failed to set GPIO mode for recovered clock[%d]\n", rcvrd_clk_src_idx);
        return VTSS_RC_ERROR;
    }
#endif
#else
    switch (vtss_state->synce.out_conf[clk_port].divider) {
        case VTSS_SYNCE_DIVIDER_1: div_mask = 0; break;
        case VTSS_SYNCE_DIVIDER_4: div_mask = 2; break;
        case VTSS_SYNCE_DIVIDER_5: div_mask = 1; break;
    }
    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(div_mask) |
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA(vtss_state->synce.out_conf[clk_port].enable),
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_DIV |
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA);
#endif /* VTSS_ARCH_SERVAL_T */

    return VTSS_RC_OK;
}

static vtss_rc jr2_synce_clock_in_set(vtss_state_t *vtss_state, const vtss_synce_clk_port_t clk_port_par)
{
    vtss_synce_clk_port_t clk_port = clk_port_par;
    vtss_synce_clock_in_t *conf = &vtss_state->synce.in_conf[clk_port];
    u32         serdes_type;
    u32         tgt, serdes_instance, mask;
    i32         new_chip_port = vtss_state->port.map[conf->port_no].chip_port;
    i32         clk_src;
    BOOL        ena = conf->enable;
#if defined(VTSS_ARCH_SERVAL_T)
    vtss_synce_clock_in_type_t port_type = conf->clk_in;
    u32 rcvrd_clk_src_idx;
#endif
    if (clk_port > 3) {
        VTSS_E("Invalid clock port no: %d\n", clk_port);
        return VTSS_RC_ERROR;
    }
#if defined(VTSS_ARCH_SERVAL_T)
#if defined(VTSS_FEATURE_CLOCK)
    rcvrd_clk_src_idx = clk_port + 4;  // In serval T with internal DPLL, recovered clock 4-7 are used as clock inputs to the internal EEC Controller(s)
#else
    rcvrd_clk_src_idx = clk_port + 1;  // In serval T with external DPLL, recovered clock 1-3 are used as clock inputs to the external DPLL
#endif
    VTSS_D("rcvrd_clk_src_idx %d\n", rcvrd_clk_src_idx);
    if (port_type == VTSS_SYNCE_CLOCK_INTERFACE) {
        if (new_chip_port <= 1) {
            clk_src = new_chip_port + 2;
        } else if (new_chip_port >= 2 && new_chip_port <= 6) {
            clk_src = new_chip_port + 4;
        } else if (new_chip_port >= 9 && new_chip_port <= 10) {
            clk_src = new_chip_port + 6;
        } else {
            VTSS_E("SyncE not supported for port_no %u, chip port %u", conf->port_no, new_chip_port);
            return VTSS_RC_ERROR;
        }
    } else if (port_type == VTSS_SYNCE_CLOCK_STATION_CLK) {
        clk_src = 22+conf->port_no;
    } else {
        // External differential clock used, i.e. this input selector is bypassed
        clk_src = 22; // not used
        ena = FALSE;
    }
    if (!ena) {
        // This is a work around because in ServalT the SYNC_ETH_CFG_RCVRD_CLK_ENA bit does not work,
        // i.e  it is not possible to tristate the recovered clock output.
        clk_src = 23; //port is currently not used, use this to force signal fail, if no source is enabled.
    }
#else
    if (new_chip_port <= 23) {
        clk_src = new_chip_port + 1;
    } else if (new_chip_port >= 24 && new_chip_port <= 31) {
        clk_src = new_chip_port + 5;
    } else if (new_chip_port >= 49 && new_chip_port <= 52) {
        clk_src = new_chip_port - 24;
    } else {
        VTSS_E("SyncE not supported for port_no %u, chip port %u", conf->port_no, new_chip_port);
        return VTSS_RC_ERROR;
    }
#endif //VTSS_ARCH_SERVAL_T
    VTSS_D("clk_port %X, port_no %u, chip port %u enable %u, squelsh %u, clk_src %d\n", clk_port, conf->port_no, new_chip_port, ena, conf->squelsh, clk_src);
#if defined(VTSS_ARCH_SERVAL_T)
    /* In Serval-T recovered clock 4-7 are used as clock inputs to the internal EEC Controller(s) */
    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(rcvrd_clk_src_idx),
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_SRC(clk_src) |
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA(ena),
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_SRC |
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA);
#else
    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(clk_src) |
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA(ena),
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_SRC |
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA);
#endif /* VTSS_ARCH_SERVAL_T */

    if (ena) {
        /* Enable input clock configuration - now configuring the new (or maybe the same) input port */
        if (VTSS_RC_OK == jr2_port_inst_get(vtss_state, conf->port_no, &tgt, &serdes_instance, &serdes_type)) {
            VTSS_D("port_no %u, tgt 0x%x, serdes_instance %u serdes_type %u\n", conf->port_no, tgt, serdes_instance, serdes_type);
            mask = (1<<serdes_instance);
            if (serdes_type == JR2_SERDES_TYPE_1G) {
                VTSS_RC(jr2_sd1g_read(vtss_state, mask)); /* Readback the 1G common config register */
                JR2_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
                        VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_ENA(conf->squelsh),
                        VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_ENA);
                VTSS_RC(jr2_sd1g_write(vtss_state, mask)); /* transfer 1G common config register */
            }
            if (serdes_type == JR2_SERDES_TYPE_6G) {
                VTSS_RC(jr2_sd6g_read(vtss_state, mask));                /* Readback the 1G common config register */
                JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                        VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_ENA(conf->squelsh),
                        VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_ENA);
                VTSS_RC(jr2_sd6g_write(vtss_state, mask));     /* transfer 6G common config register */
            }
            if (serdes_type == JR2_SERDES_TYPE_10G) {
#if defined(VTSS_ARCH_SERVAL_T)
                if (vtss_state->port.conf[conf->port_no].speed == VTSS_SPEED_1G) {
                    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG(serdes_instance),
                            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RCVRD_CLK_DIV(0) |
                            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA(conf->squelsh),
                            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RCVRD_CLK_DIV |
                            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA);
                } else {
                    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG(serdes_instance),
                            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RCVRD_CLK_DIV(1) |
                            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA(conf->squelsh),
                            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RCVRD_CLK_DIV |
                            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA);
                }
#else
                if (vtss_state->port.conf[conf->port_no].speed == VTSS_SPEED_1G) {
                    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG(serdes_instance),
                            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RECO_CLK_DIV(0) |
                            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA(conf->squelsh),
                            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RECO_CLK_DIV |
                            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA);
                } else {
                    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG(serdes_instance),
                            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RECO_CLK_DIV(1) |
                            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA(conf->squelsh),
                            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RECO_CLK_DIV |
                            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA);
                }
#endif /* VTSS_ARCH_SERVAL_T */
            }
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_synce_station_clk_out_set(vtss_state_t *vtss_state, const vtss_synce_clk_port_t clk_port_par)
{
    u32 div_mask = 0;
    vtss_synce_clk_port_t clk_port = clk_port_par;
    VTSS_D("clk_port %X  enable %u\n", clk_port, vtss_state->synce.out_conf[clk_port].enable);

    switch (vtss_state->synce.station_clk_out_conf[clk_port].divider) {
        case VTSS_SYNCE_DIVIDER_1:  div_mask = 6; break;
        case VTSS_SYNCE_DIVIDER_4:  div_mask = 1; break;
        case VTSS_SYNCE_DIVIDER_5:  div_mask = 4; break;
#if defined(VTSS_ARCH_SERVAL_T)
        case VTSS_SYNCE_DIVIDER_2:  div_mask = 0; break;
        case VTSS_SYNCE_DIVIDER_8:  div_mask = 2; break;
        case VTSS_SYNCE_DIVIDER_16: div_mask = 3; break;
        case VTSS_SYNCE_DIVIDER_25: div_mask = 5; break;
#endif
    }
    VTSS_D("divider %d, div_mask %d\n", vtss_state->synce.station_clk_out_conf[clk_port].divider, div_mask);
    // the station clock output is connected to output no 0 from the OMEGA HW.
#if defined(VTSS_ARCH_SERVAL_T)
    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_SRC(17 + vtss_state->synce.station_clk_out_conf[clk_port].dpll_out_no) | // Select SD10G[dpll_out_no] TX clock
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_DIV(div_mask) |
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA(vtss_state->synce.station_clk_out_conf[clk_port].enable),
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_SRC |
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_DIV |
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA);
#else
    JR2_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(17 + vtss_state->synce.station_clk_out_conf[clk_port].dpll_out_no) |
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(div_mask) |
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA(vtss_state->synce.station_clk_out_conf[clk_port].enable),
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_SRC |
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_DIV |
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA);
#endif

    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_SYNCE */

/* ================================================================= *
 *  Port control
 * ================================================================= */

static vtss_rc vtss_jr2_vaui_lane_alignement(vtss_state_t *vtss_state, u32 p, BOOL ena) {
    // VTSS_TO_VAUI0, Instance 0 maps to Serdes6G 16-19
    // VTSS_TO_VAUI0, Instance 1 maps to Serdes6G 20-23
    // VTSS_TO_VAUI1, Instance 0 maps to Serdes6G 8-11
    // VTSS_TO_VAUI2, Instance 1 maps to Serdes6G 12-15
#if !defined(VTSS_ARCH_SERVAL_T)
    if (VTSS_PORT_IS_10G(p)) {
        /* Disable/enable LANE alignment */
        JR2_WRM(VTSS_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG(p >= 51 ? VTSS_TO_VAUI0 : VTSS_TO_VAUI1, !(p % 2)),
                VTSS_F_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_LANE_SYNC_ENA(ena ? 0xf : 0),
                VTSS_M_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_LANE_SYNC_ENA);
    }
#endif /* VTSS_ARCH_SERVAL_T */
    return VTSS_RC_OK;
}

static BOOL port_is_in_10g_mode(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SFI ||
        vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_XAUI ||
        vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_RXAUI) {
        return 1;
    } else {
        return 0;
    }
}

vtss_rc vtss_jr2_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_max_tags_t  max_tags = vtss_state->port.conf[port_no].max_tags;
    vtss_vlan_port_type_t vlan_type = vtss_state->l2.vlan_port_conf[port_no].port_type;
    u32                   etype, port = VTSS_CHIP_PORT(port_no);

    /* S-ports and VLAN unaware ports both support 0x88a8 (in addition to 0x8100) */
    etype = (vlan_type == VTSS_VLAN_PORT_TYPE_S_CUSTOM ? vtss_state->l2.vlan_conf.s_etype :
             vlan_type == VTSS_VLAN_PORT_TYPE_C ? VTSS_ETYPE_TAG_C : VTSS_ETYPE_TAG_S);

    if (VTSS_PORT_IS_10G(port)) {
        /* As 10G and 1G devices come in pairs, we must update both devices with max tags */
        /* Currently only supporting one user defined TAG (besides 0x8100 and 0x88A8) */
        JR2_WRM(VTSS_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG(VTSS_TO_DEV(port), 0),
                VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(etype) |
                VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ENA(max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1),
                VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID |
                VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ENA);

        JR2_WRM(VTSS_DEV10G_MAC_CFG_STATUS_MAC_NUM_TAGS_CFG(VTSS_TO_DEV(port)), // Triple tags not currently supported
                VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_NUM_TAGS_CFG_NUM_TAGS(max_tags == VTSS_PORT_MAX_TAGS_ONE?1 : max_tags == VTSS_PORT_MAX_TAGS_TWO?2 : 0),
                VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_NUM_TAGS_CFG_NUM_TAGS);

        JR2_WRM(VTSS_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG(VTSS_TO_DEV(port)),
                VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1),
                VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK);
    }
    JR2_WR(VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG(VTSS_TO_DEV1G(port)),
           VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(etype) |
           VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_PB_ENA(max_tags == VTSS_PORT_MAX_TAGS_TWO ? 1 : 0) | // Triple tags not currently supported
           VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_AWR_ENA(max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1) |
           VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA(max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1));

    return VTSS_RC_OK;
}


/* static vtss_rc jr2_miim_read_write(vtss_state_t *vtss_state, */
/*                                     BOOL read,  */
/*                                     u32 miim_controller,  */
/*                                     u8 miim_addr,  */
/*                                     u8 addr,  */
/*                                     u16 *value,  */
/*                                     BOOL report_errors) */
/* { */
/*     // JR2-TBD: Stub */
/*     return VTSS_RC_ERROR; */
/* } */

/* PHY commands */
#define PHY_CMD_ADDRESS  0 /* 10G: Address */
#define PHY_CMD_WRITE    1 /* 1G/10G: Write */
#define PHY_CMD_READ_INC 2 /* 1G: Read, 10G: Read and increment */
#define PHY_CMD_READ     3 /* 10G: Read */

static vtss_rc jr2_miim_cmd(vtss_state_t *vtss_state,
                            u32 cmd, u32 sof, vtss_miim_controller_t miim_controller,
                            u8 miim_addr, u8 addr, u16 *data, BOOL report_errors)
{
    u32 i, n;
    u32 value;

    switch (miim_controller) {
    case VTSS_MIIM_CONTROLLER_0:
        i = 0;
        break;
    case VTSS_MIIM_CONTROLLER_1:
        i = 1;
        break;
    case VTSS_MIIM_CONTROLLER_2:
        i = 2;
        break;
    default:
        VTSS_E("illegal miim_controller: %d", miim_controller);
        return VTSS_RC_ERROR;
    }

    /* Set Start of frame field */
    JR2_WR(VTSS_DEVCPU_GCB_MIIM_MII_CFG(i),
           VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_CFG_PRESCALE(0x32) |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(sof));

    /* Read command is different for Clause 22 */
    if (sof == 1 && cmd == PHY_CMD_READ) {
        cmd = PHY_CMD_READ_INC;
    }

    /* Start command */
    JR2_WR(VTSS_DEVCPU_GCB_MIIM_MII_CMD(i),
           VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(miim_addr) |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(addr) |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(*data) |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(cmd));

    /* Wait for access to complete */
    for (n = 0; ; n++) {
        JR2_RD(VTSS_DEVCPU_GCB_MIIM_MII_STATUS(i), &value);
        if ((value & (VTSS_M_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_PENDING_RD |
                      VTSS_M_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_PENDING_WR)) == 0) {
            break;
        }
        if (n == 1000) {
            goto mmd_error;
        }
    }

    /* Read data */
    if (cmd == PHY_CMD_READ || cmd == PHY_CMD_READ_INC) {
        JR2_RD(VTSS_DEVCPU_GCB_MIIM_MII_DATA(i), &value);
        if (value & VTSS_M_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS) {
            goto mmd_error;
        }
        *data = VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(value);
    }
    return VTSS_RC_OK;

mmd_error:
    if(report_errors) {
        VTSS_E("miim failed, cmd: %s, miim_addr: %u, addr: %u, miim_controller:%u, sof:%u",
               cmd == PHY_CMD_READ ? "PHY_CMD_READ" :
               cmd == PHY_CMD_WRITE ? "PHY_CMD_WRITE" :
               cmd == PHY_CMD_ADDRESS ? "PHY_CMD_ADDRESS" : "PHY_CMD_READ_INC",
               miim_addr, addr, miim_controller, sof);
    }

    return VTSS_RC_ERROR;
}

static vtss_rc jr2_miim_read(vtss_state_t *vtss_state,
                              vtss_miim_controller_t miim_controller,
                              u8 miim_addr,
                              u8 addr,
                              u16 *value,
                              BOOL report_errors)
{
    return jr2_miim_cmd(vtss_state, PHY_CMD_READ, 1, miim_controller, miim_addr, addr, value, report_errors);
//    return jr2_miim_read_write(vtss_state, TRUE, miim_controller, miim_addr, addr, value, report_errors);
}

static vtss_rc jr2_miim_write(vtss_state_t *vtss_state,
                               vtss_miim_controller_t miim_controller,
                               u8 miim_addr,
                               u8 addr,
                               u16 value,
                               BOOL report_errors)
{
    return jr2_miim_cmd(vtss_state, PHY_CMD_WRITE, 1, miim_controller, miim_addr, addr, &value, report_errors);
//    return jr2_miim_read_write(vtss_state, FALSE, miim_controller, miim_addr, addr, &value, report_errors);
}

static vtss_rc jr2_mmd_read(vtss_state_t *vtss_state,
                            vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                            u16 addr, u16 *value, BOOL report_errors)
{

    VTSS_RC(jr2_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd,
                         &addr, report_errors));
    if (jr2_miim_cmd(vtss_state, PHY_CMD_READ, 0, miim_controller, miim_addr, mmd,
                     value, 0) != VTSS_RC_OK) {
        if (report_errors) {
            VTSS_E("jr2_mmd_read failed, miim_controller:%d miim_addr:%x, mmd:%x, addr:%x",miim_controller, miim_addr, mmd, addr);
        }
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

/* MMD (MDIO Management Devices (10G)) read-inc */
static vtss_rc jr2_mmd_read_inc(vtss_state_t *vtss_state,
                                vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                u16 addr, u16 *buf, u8 count, BOOL report_errors)
{

    VTSS_RC(jr2_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd,
                         &addr, report_errors));
    while (count > 1) {
        VTSS_RC(jr2_miim_cmd(vtss_state, PHY_CMD_READ_INC, 0, miim_controller, miim_addr, mmd,
                             buf, report_errors));
        buf++;
        count--;
    }
    VTSS_RC(jr2_miim_cmd(vtss_state, PHY_CMD_READ, 0, miim_controller, miim_addr, mmd,
                         buf, report_errors));
    return VTSS_RC_OK;
}


/* MMD (MDIO Management Devices (10G)) write */
static vtss_rc jr2_mmd_write(vtss_state_t *vtss_state,
                             vtss_miim_controller_t miim_controller,
                             u8 miim_addr, u8 mmd, u16 addr, u16 data,  BOOL report_errors)
{
    VTSS_RC(jr2_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd,
                         &addr, report_errors));
    return jr2_miim_cmd(vtss_state, PHY_CMD_WRITE, 0, miim_controller, miim_addr, mmd,
                        &data, report_errors);
}

static BOOL vrfy_spd_iface(vtss_port_no_t port_no, vtss_port_interface_t if_type, vtss_port_speed_t speed, BOOL *port_10g)
{
    *port_10g = 0;
    switch (if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        return TRUE;

    case VTSS_PORT_INTERFACE_SERDES:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_2500M) {
            VTSS_E("Serdes port interface only supports 1000M speed (port:%u speed:%d)",port_no, speed);
            return 0;
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_QSGMII:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M) {
            VTSS_E("SGMII/QSGMII port interface only supports 10/100/1000M speeds (port:%u)",port_no);
            return 0;
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M && speed != VTSS_SPEED_2500M) {
            VTSS_E("SGMII/QSGMII port interface only supports 10/100/1000M/2.5G speeds (port:%u)",port_no);
            return 0;
        }
        break;
    case VTSS_PORT_INTERFACE_100FX:
        if (speed != VTSS_SPEED_100M) {
            VTSS_E("100FX port interface only supports 100M speed (port:%u)",port_no);
            return 0;
        }
        break;
    case VTSS_PORT_INTERFACE_SFI:
    case VTSS_PORT_INTERFACE_RXAUI:
    case VTSS_PORT_INTERFACE_XAUI:
        if (speed != VTSS_SPEED_10G) {
            VTSS_E("SFI/XAUI/RXAUI port interface only supports 10G speeds (port:%u)",port_no);
            return 0;
        }
        *port_10g = 1;
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        if (speed != VTSS_SPEED_2500M) {
            VTSS_E("VAUI port interface only supports 2.5G speed (port:%u)",port_no);
            return 0;
        }
        break;
    default:
        VTSS_E("Illegal interface type (%d)",if_type);
        return 0;
    }
    return 1;
}

static vtss_rc jr2_port_conf_get(vtss_state_t *vtss_state,
                                  const vtss_port_no_t port_no, vtss_port_conf_t *const conf)
{
    // JR2-TBD: Stub
    return VTSS_RC_ERROR;
}

/* Serdes1G: Read/write data */

/*
 * Watermark encode/decode for QSYS:RES_CTRL:RES_CFG.WM_HIGH
 * Bit x:  Unit; 0:1, 1:16
 * Bit(x-1)-0: Value to be multiplied with unit
 */
#if defined(VTSS_ARCH_SERVAL_T)
#define MULTIPLIER_BIT 512
#else
#define MULTIPLIER_BIT 2048
#endif


static u16 wm_enc(u16 value)
{
    if (value > JR2_BUFFER_REFERENCE) {
        return VTSS_M_QRES_RES_CTRL_RES_CFG_WM_HIGH; /* Encode as all ones in relevant bit width */
    }
    if (value >= MULTIPLIER_BIT) {
        return MULTIPLIER_BIT + value / 16;
    }
    return value;
}

static u32 wm_dec(u32 value)
{
    if (value >= MULTIPLIER_BIT) {
        return (value - MULTIPLIER_BIT) * 16;
    }
    return value;
}

u32 vtss_jr2_wm_high_get(vtss_state_t *vtss_state, u32 queue)
{
    u32 wm_high;
    JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((queue + 496 + 2048)), &wm_high); /* Shared egress high watermark for queue - common for all dpls */
    return wm_dec(wm_high) * JR2_BUFFER_CELL_SZ; /* Convert from 176 byte chunks to bytes */
}

static vtss_rc jr2_port_pfc(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u32 q, pfc_mask = 0;
    u32 spd = (conf->speed == VTSS_SPEED_10G) ? 1 :
              (conf->speed == VTSS_SPEED_2500M) ? 2 :
              (conf->speed == VTSS_SPEED_1G) ? 3 :
              (conf->speed == VTSS_SPEED_100M) ? 4 : 5;

    /*  ASM / Rx enable */
    for (q = 0; q < VTSS_PRIOS; q++) {
        pfc_mask |= conf->flow_control.pfc[q] ? (1 << q) : 0;
    }
    JR2_WRM(VTSS_ASM_PFC_PFC_CFG(port),
            VTSS_F_ASM_PFC_PFC_CFG_RX_PFC_ENA(pfc_mask) |
            VTSS_F_ASM_PFC_PFC_CFG_FC_LINK_SPEED(spd),
            VTSS_M_ASM_PFC_PFC_CFG_RX_PFC_ENA |
            VTSS_M_ASM_PFC_PFC_CFG_FC_LINK_SPEED);

    /*  HQOS Scheduling must be in 'normal' mode otherwise PFC will not work */
    /*  Use pfc status for the port on layer 1 */
    JR2_WRM(VTSS_HSCH_HSCH_MISC_PFC_CFG(port),
            VTSS_F_HSCH_HSCH_MISC_PFC_CFG_PFC_LAYER(VTSS_BOOL(pfc_mask)),
            VTSS_M_HSCH_HSCH_MISC_PFC_CFG_PFC_LAYER);

    /*  Scheduler element = port in normal mode */
    JR2_WRM(VTSS_HSCH_HSCH_MISC_PFC_CFG(port),
            VTSS_F_HSCH_HSCH_MISC_PFC_CFG_PFC_SE(port),
            VTSS_M_HSCH_HSCH_MISC_PFC_CFG_PFC_SE);

    /*  ASM must not drop PFC frames as the PFC detection is done on the cellbus interface */
    JR2_WRM(VTSS_ASM_CFG_PAUSE_CFG(port),
            VTSS_F_ASM_CFG_PAUSE_CFG_ABORT_CTRL_ENA(!VTSS_BOOL(pfc_mask)),
            VTSS_M_ASM_CFG_PAUSE_CFG_ABORT_CTRL_ENA);

    /*  DSM / Tx enable */
    JR2_WRM(VTSS_QRES_RES_QOS_ADV_PFC_CFG(port),
            VTSS_F_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA(pfc_mask),
            VTSS_M_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA);
    JR2_WRM(VTSS_DSM_CFG_ETH_PFC_CFG(port),
            VTSS_F_DSM_CFG_ETH_PFC_CFG_PFC_ENA(VTSS_BOOL(pfc_mask)),
            VTSS_M_DSM_CFG_ETH_PFC_CFG_PFC_ENA);

    /* When enabled let the queue system generate Pause frames to avoid HOL */
    JR2_WRM(VTSS_DSM_CFG_RX_PAUSE_CFG(port),
            VTSS_F_DSM_CFG_RX_PAUSE_CFG_FC_OBEY_LOCAL(VTSS_BOOL(pfc_mask)),
            VTSS_M_DSM_CFG_RX_PAUSE_CFG_FC_OBEY_LOCAL);

    /* // Disable Port memory */
    JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((4096 + port + 512)), 0);

    /* // Disable Shared Prio memory */
    for (q = 0; q < VTSS_PRIOS; q++) {
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((4096 + q + 496)), 0);
    }

    /* // Disable Shared DP memory */
    for (q = 0; q < 4; q++) {
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((4096 + q + 508)), 0);
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_port_fc_setup(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u8                *smac = &conf->flow_control.smac.addr[0];
    u32               q, pause_start = 0x77F00, pause_stop = 0x77F00, rsrv_raw = 0x77F00, atop_tot = 0x77F00, sum_port, sum_cpu, val;
    BOOL              pfc = 0, fc_gen = conf->flow_control.generate, fc_obey = conf->flow_control.obey;
    vtss_port_no_t    port_no;

    for (q = 0; q < VTSS_PRIOS; q++) {
        if (conf->flow_control.pfc[q]) {
            pfc = 1;
            if (fc_gen || fc_obey) {
                VTSS_E("802.3X FC and 802.1Qbb PFC cannot both be enabled, chip port %u",port);
                return VTSS_RC_ERROR;
            }
        }
    }

    /* Configure 802.1Qbb PFC */
    VTSS_RC(jr2_port_pfc(vtss_state, port, conf));

    /* Configure Standard 802.3X FC */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (vtss_state->port.conf[port_no].flow_control.generate || pfc) {
            atop_tot = 0; //  Generate FC early if any port is in FC mode
        }
    }

    if (pfc || fc_gen || fc_obey) {
        // pause_start must be greater than reserved memory for
        //    IGR_WM(PORT) + IGR_WM(PORT, PRIO)
        // and
        //    EGR_WM(CPUPORT_0) + EGR_WM(CPUPORT_0, PRIO)
        // The latter is required in order not to transmit pause frames when the
        // CPU is congested.

        // Per port:
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG(   0 /* ingress */ + 512 /* per port */ + port),                 &sum_port);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG(2048 /* egress  */ + 512 /* per port */ + VTSS_CHIP_PORT_CPU_0), &sum_cpu);

        // Per prio:
        for (q = 0; q < VTSS_PRIOS; q++) {
            JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG(   0 /* ingress */ + port *                 VTSS_PRIOS /* per prio */ + q), &val);
            sum_port += val;

            JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG(2048 /* egress  */ + VTSS_CHIP_PORT_CPU_0 * VTSS_PRIOS /* per prio */+ q), &val);
            sum_cpu += val;
        }

        pause_start = MAX(sum_port, sum_cpu);

        // Allow for a standard frame.
        pause_start += VTSS_MAX_FRAME_LENGTH_STANDARD / JR2_BUFFER_CELL_SZ;

        pause_stop = 4 * (VTSS_MAX_FRAME_LENGTH_STANDARD / JR2_BUFFER_CELL_SZ);
        if (conf->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
            rsrv_raw = pause_start + (3 * VTSS_MAX_FRAME_LENGTH_STANDARD) / JR2_BUFFER_CELL_SZ;
        } else {
            rsrv_raw = pause_start + 20000 / JR2_BUFFER_CELL_SZ;
        }
    }

    /* Set Pause WM hysteresis*/
    JR2_WR(VTSS_QSYS_PAUSE_CFG_PAUSE_CFG(port),
           VTSS_F_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(wm_enc(pause_start)) |
           VTSS_F_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(wm_enc(pause_stop)) |
           VTSS_F_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA(0)); // enabled after reset

    /* Set SMAC of Pause frame */
    JR2_WR(VTSS_DSM_CFG_MAC_ADDR_BASE_HIGH_CFG(port), (smac[0]<<16) | (smac[1]<<8) | smac[2]);
    JR2_WR(VTSS_DSM_CFG_MAC_ADDR_BASE_LOW_CFG(port),  (smac[3]<<16) | (smac[4]<<8) | smac[5]);

    /* Set HDX flowcontrol */
    JR2_WRM(VTSS_DSM_CFG_MAC_CFG(port),
            VTSS_F_DSM_CFG_MAC_CFG_HDX_BACKPRESSURE(!conf->fdx),
            VTSS_M_DSM_CFG_MAC_CFG_HDX_BACKPRESSURE);

    /* Obey flowcontrol  */
    JR2_WRM(VTSS_DSM_CFG_RX_PAUSE_CFG(port),
            VTSS_F_DSM_CFG_RX_PAUSE_CFG_RX_PAUSE_EN(fc_obey),
            VTSS_M_DSM_CFG_RX_PAUSE_CFG_RX_PAUSE_EN);

    /* No ingress dropping in flowontrol  */
    JR2_WRM(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(port),
           VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE(!fc_gen),
           VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE);

    JR2_WR(VTSS_QSYS_PAUSE_CFG_ATOP(port),
           VTSS_F_QSYS_PAUSE_CFG_ATOP_ATOP(wm_enc(rsrv_raw)));

    /*  When 'port ATOP' and 'common ATOP_TOT' are exceeded, tail dropping is activated on port */
    JR2_WR(VTSS_QSYS_PAUSE_CFG_ATOP_TOT_CFG,
           VTSS_F_QSYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(wm_enc(atop_tot)));

    return VTSS_RC_OK;
}


static vtss_rc jr2_sd10g_xfi_mode(vtss_state_t *vtss_state, vtss_serdes_mode_t mode, vtss_port_no_t port_no)
{
    u32 tgt = VTSS_TO_10G_XFI_TGT(VTSS_CHIP_PORT(port_no));
    vtss_port_conf_t *conf  = &vtss_state->port.conf[port_no];

    // Set XFI to default
    JR2_WR(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt), 0x5);

    if (mode == VTSS_SERDES_MODE_100FX ||
        mode == VTSS_SERDES_MODE_SGMII ||
        mode == VTSS_SERDES_MODE_1000BaseX ||
        mode == VTSS_SERDES_MODE_2G5) {
        JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt),
                VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_PORT_SEL(1),
                VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_PORT_SEL);
    } else {
        JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt),
                VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_PORT_SEL(0),
                VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_PORT_SEL);
    }

    JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt),
            VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_RST(0),
            VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_RST);

    JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt),
            VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_INVERT(conf->serdes.tx_invert),
            VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_INVERT);

    JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt),
            VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_RX_INVERT(conf->serdes.rx_invert),
            VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_RX_INVERT);

    JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt),
            VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_ENA(1),
            VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_ENA);

    JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt),
            VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_ENDIAN(1),
            VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_ENDIAN);

    JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(tgt),
            VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_RESYNC_SHOT(1),
            VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_RESYNC_SHOT);

    return VTSS_RC_OK;
}

static vtss_rc jr2_serdes_cfg(vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_serdes_mode_t mode)
{
    u32  serdes_inst, serdes_type, tgt, addr, port = VTSS_CHIP_PORT(port_no);
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];

    if (mode == vtss_state->port.serdes_mode[port_no]) {
        return VTSS_RC_OK; // No change of Serdes
    }

    VTSS_RC(jr2_port_inst_get(vtss_state, port_no, &tgt, &serdes_inst, &serdes_type));

    VTSS_D("Configure Serdes chip port %u, serdes mode:%d serdes inst:%d, serdes type:%d)", port, mode, serdes_inst, serdes_type);

    if (!VTSS_PORT_IS_10G(port) || mode == VTSS_SERDES_MODE_1000BaseX) {
        addr = (1 << serdes_inst);
    } else {
        addr = serdes_inst;
    }

    if (mode == VTSS_SERDES_MODE_XAUI || mode == VTSS_SERDES_MODE_RXAUI) {
        /* Enable Lane alignment */
        VTSS_RC(vtss_jr2_vaui_lane_alignement(vtss_state, port, 1));
    }

    switch (serdes_type) {
    case JR2_SERDES_TYPE_1G:
        VTSS_RC(jr2_sd1g_cfg(vtss_state, port_no, mode, addr));
        break;

    case JR2_SERDES_TYPE_6G:
        if ((mode != VTSS_SERDES_MODE_QSGMII) || (mode == VTSS_SERDES_MODE_QSGMII && ((port % 4) == 0))) {
            VTSS_RC(jr2_sd6g_cfg(vtss_state, port_no, mode, addr));
        }
        break;

    case JR2_SERDES_TYPE_10G:
        VTSS_RC(jr2_sd10g_xfi_mode(vtss_state, mode, port_no));
        VTSS_RC(jr2_sd10g_cfg(vtss_state, mode, conf->serdes.media_type, port));
        /* Change to 100FX after Serdes config */
        if (mode == VTSS_SERDES_MODE_100FX) {
            JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(VTSS_TO_10G_XFI_TGT(port)),
                    VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_ENA(1),
                    VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_ENA);

            JR2_WRM(VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(VTSS_TO_10G_XFI_TGT(port)),
                    VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_RESYNC_SHOT(1),
                    VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_RESYNC_SHOT);
        }
#if defined(VTSS_FEATURE_CLOCK)
        // whenever the serdes setup is changed, the tx clock synchronizationmust be refreshed
        VTSS_RC(vtss_omega_clock_output_filter_bw_refresh(vtss_state, serdes_inst));
#endif /* VTSS_FEATURE_CLOCK */

        VTSS_D("Done");
        break;
    }

    vtss_state->port.serdes_mode[port_no] = mode;
    return VTSS_RC_OK;
}

/* Poll port until all memory is freed */
static vtss_rc jr2_port_flush_poll(vtss_state_t *vtss_state, vtss_phys_port_no_t port)
{
    u32  value, resource, prio, delay_cnt = 0;
#if VTSS_OPT_TRACE
    char *failing_mem = "";
#endif
    BOOL poll_src;

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_FEATURE_AFI_SWC)
    // Only do DST-MEM resource.
    // The reason not to do SRC-MEM poll is that if the AFI is having at least
    // one up-flow (with CL_DP == 0) on the port we are trying to flush, SRC-MEM
    // will never go to zero even though the flow has actually been stopped
    // (which it is by now).
    poll_src = FALSE;
#else
    // Do both DST-MEM and SRC-MEM poll.
    poll_src = TRUE;
#endif

    // Resource == 0: Memory tracked per source (SRC-MEM)
    // Resource == 1: Frame references tracked per source (SRC-REF)
    // Resource == 2: Memory tracked per destination (DST-MEM)
    // Resource == 3: Frame references tracked per destination. (DST-REF)

    while (1) {
        BOOL empty = TRUE;

        for (resource = 0; resource < (poll_src ? 2 : 1); resource++) {
            // Start with DST-MEM (base == 2048) and if enabled, also check
            // SRC-MEM (base == 0).
            u32 base = (resource == 0 ? 2048 : 0) + VTSS_PRIOS * port;

            for (prio = 0; prio < VTSS_PRIOS; prio++) {
                JR2_RD(VTSS_QRES_RES_CTRL_RES_STAT(base + prio), &value);
                if (value) {
#if VTSS_OPT_TRACE
                    failing_mem = resource == 0 ? "DST-MEM" : "SRC-MEM";
#endif
                    empty = FALSE;

                    // Here, it could be tempting to exit the loop, but because
                    // the registers are clear-on-read, we gotta continue, or it
                    // will take at least 8 or 16 VTSS_MSLEEP() calls to get out
                    // of this.
                }
            }
        }

        if (empty) {
            break;
        }

        if (delay_cnt++ == 2000) {
            u32  base, idx, cnt;
            char buf[300];
            buf[sizeof(buf) - 1] = '\0';

            cnt = VTSS_SNPRINTF(buf, sizeof(buf) - 1, "QRES:RES_CTRL[chip-port = %u]:RES_STAT\n", port);

            for (resource = 0; resource < 4; resource++) {
                base = resource * 1024 + port * VTSS_PRIOS;
                for (prio = 0; prio < VTSS_PRIOS; prio++) {
                    idx = base + prio;
                    JR2_RD(VTSS_QRES_RES_CTRL_RES_STAT(idx), &value);
                    if (value) {
                        cnt += VTSS_SNPRINTF(buf + cnt, sizeof(buf) - 1 - cnt,  "res = %u, prio = %u => idx = %u val = %u\n", resource, prio, idx, value);
                    }
                }
            }

            VTSS_E("Flush timeout chip port %u. %s queue not empty\n%s", port, failing_mem, buf);
            break;
        }

        VTSS_MSLEEP(1);
    }

    return VTSS_RC_OK;
}

/* Port disable and flush procedure */
static vtss_rc jr2_port_flush(vtss_state_t *vtss_state, const vtss_port_no_t port_no, BOOL is_10g)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 tgt = is_10g ? VTSS_TO_DEV(port) : VTSS_TO_DEV1G(port);

    VTSS_I("Flush chip port: %u (10g:%d)", port, is_10g);

    if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_QSGMII) {
        VTSS_RC(jr2_port_inst_get(vtss_state, port_no, &tgt, NULL, NULL));
    }

    if (is_10g) {
        /* 1: Reset the PCS Rx clock domain  */
        JR2_WRM_SET(VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt),
                    VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST);

        /* 2: Disable MAC frame reception */
        JR2_WRM_CLR(VTSS_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG(tgt),
                    VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA);
    } else {
        /* 1: Reset the PCS Rx clock domain  */
        JR2_WRM_SET(VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt),
                    VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST);

        /* 2: Disable MAC frame reception */
        JR2_WRM_CLR(VTSS_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG(tgt),
                    VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA);
    }

    /* 3: Disable traffic being sent to or from switch port */
    JR2_WRM_CLR(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(port),
                 VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);

    /* 4: Disable dequeuing from the egress queues  */
    JR2_WRM_SET(VTSS_HSCH_HSCH_MISC_PORT_MODE(port),
                VTSS_M_HSCH_HSCH_MISC_PORT_MODE_DEQUEUE_DIS);

    /* 5: Disable Flowcontrol */
    JR2_WRM_CLR(VTSS_QSYS_PAUSE_CFG_PAUSE_CFG(port), VTSS_M_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA);

    /* 5.1: Disable PFC */
    JR2_WRM(VTSS_QRES_RES_QOS_ADV_PFC_CFG(port),
            VTSS_F_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA(0),
            VTSS_M_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA);

    /* 6: Wait a worst case time 8ms (jumbo/10Mbit) *\/ */
    VTSS_MSLEEP(8);

    /* 7: Flush the queues accociated with the port */
#if defined(VTSS_ARCH_JAGUAR_2_B)
    JR2_WRM_SET(VTSS_HSCH_HSCH_MISC_PORT_MODE(port),
                 VTSS_M_HSCH_HSCH_MISC_PORT_MODE_FLUSH_ENA);
#else // VTSS_ARCH_JAGUAR_2_C
    JR2_WRM(VTSS_HSCH_HSCH_MISC_FLUSH_CTRL,
            VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_PORT(port) |
            VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_DST(1) |
            VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_SRC(1) |
            VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_ENA(1),
            VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_PORT |
            VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_SRC |
            VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_DST |
            VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_ENA);
#endif

    /* 8: Enable dequeuing from the egress queues */
    JR2_WRM_CLR(VTSS_HSCH_HSCH_MISC_PORT_MODE(port),
                VTSS_M_HSCH_HSCH_MISC_PORT_MODE_DEQUEUE_DIS);

    /* 9: Wait until flushing is complete */
    VTSS_RC(jr2_port_flush_poll(vtss_state, port));

   /* 10: Reset the  MAC clock domain */
    if (is_10g) {
        JR2_WRM(VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt),
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST(1) |
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST(1) |
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST(1) |
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL(6),
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST |
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST |
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST |
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL);
    } else {
        JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt),
               VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST(0)|
               VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST(0)|
               VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST(1)|
               VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST(1)|
               VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL(3));
    }
    /* 11: Clear flushing */
#if defined(VTSS_ARCH_JAGUAR_2_B)
    JR2_WRM_CLR(VTSS_HSCH_HSCH_MISC_PORT_MODE(port),
                 VTSS_M_HSCH_HSCH_MISC_PORT_MODE_FLUSH_ENA);
#else
    JR2_WRM(VTSS_HSCH_HSCH_MISC_FLUSH_CTRL,
            VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_PORT(port) |
            VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_ENA(0),
            VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_PORT |
            VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_ENA);
#endif

#if !defined(VTSS_ARCH_SERVAL_T)
    if (is_10g) {
        /* Disable XAUI PCS */
        JR2_WRM_CLR(VTSS_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG(tgt),
                    VTSS_M_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG_PCS_ENA);

        /* Disable RXAUI PCS */
        JR2_WRM_CLR(VTSS_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG(tgt),
                    VTSS_M_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_PCS_ENA);

        /* Disable SFI PCS */
        JR2_WRM_CLR(VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG(VTSS_TO_10G_PCS_TGT(port)),
                    VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_PCS_ENA);
    }
#endif /* VTSS_ARCH_SERVAL_T */
    /* The port is disabled and flushed */

    return VTSS_RC_OK;
}

#if defined(VTSS_ARCH_SERVAL_T)
// Configure the internal PHY
static vtss_rc srvlt_phy_config(vtss_state_t *vtss_state, u32 port, BOOL enable)
{
    u32 intr;

    if (port > 1) {
        return VTSS_RC_OK; // Not internal Phy
    }
    // Field: VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_ENA
    JR2_WRM(VTSS_DEVCPU_GCB_PHY_PHY_CFG, enable ? VTSS_BIT(port) : 0, VTSS_BIT(port));

    // Change serdes to phy interrupt or vice versa in the ICPU DEV interrupt vector
    JR2_RD(VTSS_ICPU_CFG_INTR_DEV_INTR_ENA, &intr);
    if (enable) {    // Serdes to phy interrupt
        if (intr & VTSS_BIT(port)) {
            JR2_WRM(VTSS_ICPU_CFG_INTR_DEV_INTR_ENA, VTSS_BIT(port+11), VTSS_BIT(port) | VTSS_BIT(port+11));
        }
    } else { // Phy to phy interrupt
        if (intr & VTSS_BIT(port+11)) {
            JR2_WRM(VTSS_ICPU_CFG_INTR_DEV_INTR_ENA, VTSS_BIT(port), VTSS_BIT(port) | VTSS_BIT(port+11));
        }
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_SERVAL_T */

#if defined(VTSS_FEATURE_PORT_KR)

// Defines for the current an state in KR_DEV7_AN_SM
#define AN_ENABLE 0
#define AN_XMT_DISABLE 1
#define AN_ABIL_DET 2
#define AN_ACK_DET 3
#define AN_CMPL_ACK 4
#define AN_TRAIN 5
#define AN_GOOD_CHK 6
#define AN_GOOD 7
#define AN_RATE_DET 8
#define AN_WAIT_RATE_DONE 13

static vtss_rc jr2_port_kr_fec_set(vtss_state_t *vtss_state,
                                       const vtss_port_no_t port_no)
{
    BOOL fec = vtss_state->port.kr_fec[port_no].r_fec;
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 br   = VTSS_TO_10G_PCS10G_BR(port);
    u32 xfi  = VTSS_TO_10G_XFI_TGT(port);      // KR-Control/Stickies
    u32 val;

    // Enable/disable FEC

    VTSS_I("Port:%d KR FEC %s",port_no, fec ? "Enabled" : "Disabled");

    JR2_WRM(VTSS_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG(br),
           VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_FEC_ENA(fec) |
           VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_TX_DATA_FLIP(fec) |
           VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_RX_DATA_FLIP(fec),
           VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_FEC_ENA |
           VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_TX_DATA_FLIP |
           VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_RX_DATA_FLIP);

    // Clear the stickies
    JR2_RD(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi), &val);
    JR2_WR(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi), val);

    return VTSS_RC_OK;
}


static vtss_rc jr2_port_kr_status(vtss_state_t *vtss_state,
                                      const vtss_port_no_t port_no,
                                      vtss_port_kr_status_t *const status)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 dev7 = VTSS_TO_10G_KR_DEV7_TGT(port);  // ANEG
    u32 dev1 = VTSS_TO_10G_KR_DEV1_TGT(port);  // Training
    u32 xfi  = VTSS_TO_10G_XFI_TGT(port);      // KR-Control/Stickies
    u32 br   = VTSS_TO_10G_PCS10G_BR(port);
    u32 val, an_sm, aneg, pcs, fec, hist, sticky = 0;
    BOOL aneg_is_restarted = 0;

    if (vtss_state->port.conf[port_no].power_down) {
        status->aneg.complete = 0;
        status->train.complete = 0;
        return VTSS_RC_OK;
    }

    JR2_RD(VTSS_KR_DEV7_AN_SM_AN_SM(dev7), &an_sm);
    an_sm = VTSS_X_KR_DEV7_AN_SM_AN_SM_AN_SM(an_sm);
    JR2_RD(VTSS_KR_DEV7_KR_7X0001_KR_7X0001(dev7), &aneg);
    JR2_RD(VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS(VTSS_TO_10G_PCS_TGT(port)), &pcs);
    JR2_RD(VTSS_XFI_SHELL_XFI_CONTROL_XFI_STATUS(xfi), &val);

    if (an_sm == AN_GOOD ||  // State: AN_GOOD
        an_sm == AN_XMT_DISABLE ||  // State: Transmit Disable
        an_sm == AN_WAIT_RATE_DONE) { // State: Wait Rom
        // Aneg state machine is waiting, store and clear the speed requests to let aneg finish
        JR2_RD(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi), &sticky);
        JR2_WR(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi),
               VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_10G_STICKY(1) |
               VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX10G_STICKY(1) |
               VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX10G_STICKY(1) |
               VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_1G_STICKY(1) |
               VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX1G_STICKY(1) |
               VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX1G_STICKY(1));
    }

    // Aneg status
    status->aneg.complete = (an_sm == AN_GOOD) &&
        VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_AN_COMPLETE(aneg) &&
        VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_BLOCK_LOCK(pcs);
    status->aneg.block_lock = VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_BLOCK_LOCK(pcs);
    status->aneg.sm = an_sm;
    status->aneg.lp_aneg_able = VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_AN_LP_ABLE(aneg);
    status->aneg.active = VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_STATUS_ANEG_ACTIVE_STATUS(val);

    // Training status
    JR2_RD(VTSS_KR_DEV1_KR_1X0097_KR_1X0097(dev1), &val);
    status->train.complete = VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_RCVR_RDY(val) &&
                               !VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_TR_FAIL(val) &&
                               VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_AN_LP_ABLE(aneg);
    u32 tr_fail = VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_TR_FAIL(val) &&
        VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_AN_LP_ABLE(aneg);

    if (an_sm == AN_ACK_DET && tr_fail && !status->aneg.active) {
        VTSS_I("Port:%d. Stuck in AN_ACK_DET.  Restart Aneg",port_no);
        JR2_WRM(VTSS_KR_DEV7_KR_7X0000_KR_7X0000(dev7),
                VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART(1),
                VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART);
        return VTSS_RC_OK;
    } else if (an_sm == AN_ACK_DET && tr_fail && status->aneg.active) {
        VTSS_I("Port:%d. Stuck in AN_ACK_DET.  Restart Training",port_no);
        JR2_WRM(VTSS_KR_DEV1_KR_1X0096_KR_1X0096(dev1),
                VTSS_F_KR_DEV1_KR_1X0096_KR_1X0096_TR_RESTART(1),
                VTSS_M_KR_DEV1_KR_1X0096_KR_1X0096_TR_RESTART);
        return VTSS_RC_OK;
    } else if (an_sm == AN_ACK_DET && !tr_fail && (sticky == 0)) {
        VTSS_I("Port:%d. Stuck in AN_ACK_DET.  Restart KR block",port_no);
        vtss_state->port.kr_conf_set(vtss_state, port_no);
        return VTSS_RC_OK;
    }

    // FEC status
    status->fec.r_fec_enable = vtss_state->port.kr_fec[port_no].r_fec;

    // Verify that the aneg state machine is not stuck
    if (an_sm == AN_ABIL_DET || (an_sm == AN_GOOD && !status->aneg.complete)) {
        JR2_RD(VTSS_KR_DEV7_AN_HIST_AN_HIST(dev7), &hist);
        if ((hist & 0xFF7B) == 0) { // mask out parallel detect and ability check
            // Restart aneg
            VTSS_I("Port:%d. Stuck in %s.  Restart Aneg",port_no, an_sm == AN_ABIL_DET ? "ABIL_DET" : "AN_GOOD");
            JR2_WRM(VTSS_KR_DEV7_KR_7X0000_KR_7X0000(dev7),
                    VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART(1),
                    VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART);
            // Clear stickys
            JR2_WR(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi), 0x3FF);
            return VTSS_RC_OK;
        } else {
            // Clear aneg history
            JR2_WRM(VTSS_KR_DEV7_AN_CFG0_AN_CFG0(dev7),
                    VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR(1),
                    VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR);
            JR2_WRM(VTSS_KR_DEV7_AN_CFG0_AN_CFG0(dev7),
                    VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR(0),
                    VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR);
        }
    }


    if (status->aneg.active) {
        // Aneg is still running, return now.
        status->aneg.speed_req = VTSS_SPEED_UNDEFINED;
        status->aneg.request_fec_change = FALSE;
        status->aneg.r_fec_enable = FALSE;
        return VTSS_RC_OK;
    }

    if (status->fec.r_fec_enable) {
        JR2_RD(VTSS_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_CORRECTED(br), &fec);
        status->fec.corrected_block_cnt = fec;
        JR2_RD(VTSS_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_UNCORRECTED(br), &fec);
        status->fec.uncorrected_block_cnt = fec;
    }

    // Speed request
    JR2_RD(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi), &val);
    val = sticky | val;

    if (VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_RATE(val) == 0 &&
        (VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_10G_STICKY(val) ||
         VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX10G_STICKY(val) ||
         VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX10G_STICKY(val))) {
        status->aneg.speed_req = VTSS_SPEED_10G;
    }

    // FEC request
    status->aneg.request_fec_change = VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_FEC_STICKY(val);
    status->aneg.r_fec_enable = VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_FEC_ENABLE(val);

    if (status->aneg.speed_req == VTSS_SPEED_UNDEFINED ||
        status->aneg.speed_req == VTSS_SPEED_10G) {
        // Workaround for 1G TX/RX sticky request
        if (VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX1G_STICKY(val) ||
            VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX1G_STICKY(val)) {
            JR2_WR(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi),
                   VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX1G_STICKY(1) |
                   VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX1G_STICKY(1));
        }
    }

    if (status->train.complete || (an_sm == AN_TRAIN)) {
        // ob tap values
        JR2_RD(VTSS_KR_DEV1_TR_TAPVAL_TR_C0VAL(dev1), &val);
        status->train.c0_ob_tap_result = (u8)val;
        JR2_RD(VTSS_KR_DEV1_TR_TAPVAL_TR_CMVAL(dev1), &val);
        status->train.cm_ob_tap_result = (u8)val;
        JR2_RD(VTSS_KR_DEV1_TR_TAPVAL_TR_CPVAL(dev1), &val);
        status->train.cp_ob_tap_result = (u8)val;

        if (an_sm == AN_TRAIN) {
            VTSS_I("Port:%d. Stuck in training  Restart Aneg. AN sm:%d",port_no,an_sm);
            if (vtss_state->port.kr_conf[port_no].aneg.enable) {
                JR2_WRM(VTSS_KR_DEV7_KR_7X0000_KR_7X0000(dev7),
                        VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE(1) |
                        VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART(1),
                        VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE |
                        VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART);
                aneg_is_restarted = TRUE;
            }
        }
    }
    if (!aneg_is_restarted &&
        vtss_state->port.kr_fec[port_no].r_fec &&
        vtss_state->port.kr_conf[port_no].aneg.enable &&
        !VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_BLOCK_LOCK(pcs) &&
        status->aneg.lp_aneg_able) {
        // Workaround for FEC enable request
        VTSS_I("Port:%d. Lost block lock. Restart Aneg. AN sm:%d",port_no,an_sm);
        JR2_WRM(VTSS_KR_DEV7_KR_7X0000_KR_7X0000(dev7),
                VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART(1),
                VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART);
    }

    if (status->aneg.request_fec_change) {
        vtss_state->port.kr_fec[port_no].r_fec = status->aneg.r_fec_enable;
        (void)jr2_port_kr_fec_set(vtss_state, port_no);
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_port_kr_conf_set(vtss_state_t *vtss_state,
                                        const vtss_port_no_t port_no)
{
    vtss_port_kr_conf_t *aneg = &vtss_state->port.kr_conf[port_no];
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 dev7 = VTSS_TO_10G_KR_DEV7_TGT(port);  // ANEG
    u32 dev1 = VTSS_TO_10G_KR_DEV1_TGT(port);  // Training
    u32 xfi  = VTSS_TO_10G_XFI_TGT(port);      // KR-Control/Stickies
    u32 abil = 0;
    // Re-configure the serdes
    VTSS_RC(jr2_sd10g_cfg(vtss_state, vtss_state->port.serdes_mode[port_no],
                          vtss_state->port.current_mt[port_no], port));
    // Adjust the timers for JR2 core clock (frequency of 250Mhz)
    JR2_WR(VTSS_KR_DEV7_LFLONG_TMR_LFLONG_MSW(dev7), 322);
    JR2_WR(VTSS_KR_DEV7_TR_TMR_TR_MSW(dev7), 322);
    JR2_WRM(VTSS_KR_DEV1_TR_CFG0_TR_CFG0(dev1),
            VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_TMR_DVDR(6),
            VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_TMR_DVDR);
    JR2_WR(VTSS_KR_DEV1_WT_TMR_WT_TMR(dev1), 1712);
    JR2_WR(VTSS_KR_DEV1_MW_TMR_MW_TMR_LSW(dev1), 58521);
    JR2_WR(VTSS_KR_DEV1_MW_TMR_MW_TMR_MSW(dev1), 204);

    // Clear the KR_CONTROL stickies
    JR2_WR(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi), 0x7ff);

    if (aneg->aneg.enable) {
        /* AN Selector */
        JR2_WR(VTSS_KR_DEV7_LD_ADV_KR_7X0010(dev7),
               VTSS_F_KR_DEV7_LD_ADV_KR_7X0010_ADV0(0x0001));

        /* AN Technology aneg field bit 5=1000Base-KX,
           6=10GBase-KX4,
           7=10GBase-KR (no supported) */

        abil = (0  ? VTSS_BIT(5) : 0) |  /* 1G adv not supported */
               (aneg->aneg.adv_10g ? VTSS_BIT(7) : 0);

        JR2_WRM(VTSS_KR_DEV7_LD_ADV_KR_7X0011(dev7),
                VTSS_F_KR_DEV7_LD_ADV_KR_7X0011_ADV1(abil),
                VTSS_BIT(5) | VTSS_BIT(7));

        /* AN FEC aneg field bit 14 = fec aneg,
           15 = fec requested */
        abil = VTSS_BIT(14) | (aneg->aneg.r_fec_req  ? VTSS_BIT(15) : 0);
        JR2_WRM(VTSS_KR_DEV7_LD_ADV_KR_7X0012(dev7),
                VTSS_F_KR_DEV7_LD_ADV_KR_7X0012_ADV2(abil),
                VTSS_BIT(14) | VTSS_BIT(15));

        // Freeze break link timer
        JR2_WRM(VTSS_KR_DEV1_TR_CFG1_TR_CFG1(dev1),
                VTSS_BIT(10),
                VTSS_BIT(10));

        // Freeze page detect timer (disable parallel detect)
        JR2_WRM(VTSS_KR_DEV1_TR_CFG1_TR_CFG1(dev1),
                aneg->aneg.no_pd ? VTSS_BIT(6) : 0,
                VTSS_BIT(6));
    }

    // Disable Training if requested
    JR2_WRM(VTSS_KR_DEV7_AN_CFG0_AN_CFG0(dev7),
            VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_TR_DISABLE(!aneg->train.enable),
            VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_TR_DISABLE);

    if (aneg->train.enable) {
        // Clear training history
        JR2_WRM(VTSS_KR_DEV1_TR_CFG0_TR_CFG0(dev1),
                VTSS_BIT(5),  // SM_HIST_CLR
                VTSS_BIT(5)); // SM_HIST_CLR
        JR2_WRM(VTSS_KR_DEV1_TR_CFG0_TR_CFG0(dev1),
                0,            // SM_HIST_CLR
                VTSS_BIT(5)); // SM_HIST_CLR

        // KR Training config according to UG1061 chapter 3.1
        JR2_WRM(VTSS_KR_DEV1_TR_MTHD_TR_MTHD(dev1),
                VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CP(0) |
                VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_C0(0) |
                VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CM(0),
                VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CP |
                VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_C0 |
                VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CM);

        JR2_WRM(VTSS_KR_DEV1_TR_CFG0_TR_CFG0(dev1),
                VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_LD_PRE_INIT(1) |
                VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_LP_PRE_INIT(1),
                VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_LD_PRE_INIT |
                VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_LP_PRE_INIT);

        JR2_WRM(VTSS_KR_DEV1_TR_CFG2_TR_CFG2(dev1),
                VTSS_F_KR_DEV1_TR_CFG2_TR_CFG2_VP_MAX(0x1F) |
                VTSS_F_KR_DEV1_TR_CFG2_TR_CFG2_V2_MIN(1),
                VTSS_M_KR_DEV1_TR_CFG2_TR_CFG2_VP_MAX |
                VTSS_M_KR_DEV1_TR_CFG2_TR_CFG2_V2_MIN);

        JR2_WRM(VTSS_KR_DEV1_TR_CFG3_TR_CFG3(dev1),
                VTSS_F_KR_DEV1_TR_CFG3_TR_CFG3_CP_MAX(0x3f) |
                VTSS_F_KR_DEV1_TR_CFG3_TR_CFG3_CP_MIN(0x35),
                VTSS_M_KR_DEV1_TR_CFG3_TR_CFG3_CP_MAX |
                VTSS_M_KR_DEV1_TR_CFG3_TR_CFG3_CP_MIN);

        JR2_WRM(VTSS_KR_DEV1_TR_CFG4_TR_CFG4(dev1),
                VTSS_F_KR_DEV1_TR_CFG4_TR_CFG4_C0_MAX(0x1f) |
                VTSS_F_KR_DEV1_TR_CFG4_TR_CFG4_C0_MIN(0xc),
                VTSS_M_KR_DEV1_TR_CFG4_TR_CFG4_C0_MAX |
                VTSS_M_KR_DEV1_TR_CFG4_TR_CFG4_C0_MIN);

        JR2_WRM(VTSS_KR_DEV1_TR_CFG5_TR_CFG5(dev1),
                VTSS_F_KR_DEV1_TR_CFG5_TR_CFG5_CM_MAX(0) |
                VTSS_F_KR_DEV1_TR_CFG5_TR_CFG5_CM_MIN(0x3a),
                VTSS_M_KR_DEV1_TR_CFG5_TR_CFG5_CM_MAX |
                VTSS_M_KR_DEV1_TR_CFG5_TR_CFG5_CM_MIN);

        JR2_WRM(VTSS_KR_DEV1_TR_CFG6_TR_CFG6(dev1),
                VTSS_F_KR_DEV1_TR_CFG6_TR_CFG6_CP_INIT(0x38) |
                VTSS_F_KR_DEV1_TR_CFG6_TR_CFG6_C0_INIT(0x14),
                VTSS_M_KR_DEV1_TR_CFG6_TR_CFG6_CP_INIT |
                VTSS_M_KR_DEV1_TR_CFG6_TR_CFG6_C0_INIT);

        JR2_WRM(VTSS_KR_DEV1_TR_CFG7_TR_CFG7(dev1),
                VTSS_F_KR_DEV1_TR_CFG7_TR_CFG7_CM_INIT(0x3e),
                VTSS_M_KR_DEV1_TR_CFG7_TR_CFG7_CM_INIT);

        JR2_WRM(VTSS_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR(dev1),
                VTSS_F_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR_OBCFG_ADDR(0x12),
                VTSS_M_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR_OBCFG_ADDR);

        // Training should only be enabled if Aneg is disabled.
        // Aneg enables training automatically
        if (!aneg->aneg.enable) {
            JR2_WRM(VTSS_KR_DEV1_KR_1X0096_KR_1X0096(dev1),
                    VTSS_F_KR_DEV1_KR_1X0096_KR_1X0096_TR_ENABLE(1),
                    VTSS_M_KR_DEV1_KR_1X0096_KR_1X0096_TR_ENABLE);
        }

    }

    // KR Autoneg

    // Disable clock gating
    JR2_WRM(VTSS_KR_DEV7_AN_CFG0_AN_CFG0(dev7),
            VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_CLKG_DISABLE(aneg->aneg.enable),
            VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_CLKG_DISABLE);

    // Clear aneg history
    JR2_WRM(VTSS_KR_DEV7_AN_CFG0_AN_CFG0(dev7),
            VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR(1),
            VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR);
    JR2_WRM(VTSS_KR_DEV7_AN_CFG0_AN_CFG0(dev7),
            VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR(0),
            VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR);

    // Disable / Enable Auto-neg
    JR2_WRM(VTSS_KR_DEV7_KR_7X0000_KR_7X0000(dev7),
            VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE(0),
            VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE);

    if (aneg->aneg.enable) {
        JR2_WRM(VTSS_KR_DEV7_KR_7X0000_KR_7X0000(dev7),
                VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE(1) |
                VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART(1),
                VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE |
                VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART);
    }

    // Release the break link timer
    JR2_WRM(VTSS_KR_DEV1_TR_CFG1_TR_CFG1(dev1),
            0,
            VTSS_BIT(10));

    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_PORT_KR */

static vtss_rc jr2_port_conf_1g_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t       *conf  = &vtss_state->port.conf[port_no];
    u32                    port   = VTSS_CHIP_PORT(port_no);
    u32                    tgt, tx_gap, hdx_gap_1 = 0, hdx_gap_2 = 0;
    vtss_port_speed_t      speed = conf->speed;
    u32                    value;
    BOOL                   fdx = conf->fdx, disable = conf->power_down;
    BOOL                   sgmii = 0, if_100fx = 0;
    vtss_serdes_mode_t     serdes_mode = VTSS_SERDES_MODE_SGMII;
#if defined(VTSS_ARCH_SERVAL_T)
    u32                    bt_fld = (port == 9) ? 0 : 2;
#else                      // Offset of Dev10G_MODE
    u32                    bt_fld = (port == 49) ? 12 : (port == 50) ? 14 : (port == 51) ? 16 : 18;
#endif


    // Find device target and serdes macro for this chip port
    VTSS_RC(jr2_port_inst_get(vtss_state, port_no, &tgt, NULL, NULL));

    VTSS_D("chip port: %u interface:%s", port, vtss_port_if_txt(conf->if_type));

    // Find serdes mode
    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        disable = 1;
        break;
    case VTSS_PORT_INTERFACE_INTERNAL:
    case VTSS_PORT_INTERFACE_SGMII:
        serdes_mode = VTSS_SERDES_MODE_SGMII;
        sgmii = 1;
        break;
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        serdes_mode = (speed == VTSS_SPEED_2500M ? VTSS_SERDES_MODE_2G5 : VTSS_SERDES_MODE_SGMII);
        sgmii = (serdes_mode == VTSS_SERDES_MODE_SGMII ? 1: 0);
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        serdes_mode = VTSS_SERDES_MODE_QSGMII;
        sgmii = 1;
        JR2_WRM(VTSS_HSIO_HW_CFGSTAT_HW_CFG, VTSS_BIT(port/4), VTSS_BIT(port/4));
        if ((port % 4) == 0) {
            // BZ23738
            for (u32 p = port + 1; p <= port + 3; ++p)
                JR2_WRM_CLR(VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL(VTSS_TO_DEV(p)), VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST);
        }
        break;
    case VTSS_PORT_INTERFACE_100FX:
        serdes_mode = VTSS_SERDES_MODE_100FX;
        if_100fx = 1;
        break;
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_QSGMII) {
            serdes_mode = VTSS_SERDES_MODE_QSGMII; // Do not change the Serdes mode
        } else {
            serdes_mode = VTSS_SERDES_MODE_1000BaseX;
        }
        sgmii = 1;
        break;
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
        serdes_mode = (speed == VTSS_SPEED_2500M ? VTSS_SERDES_MODE_2G5 : VTSS_SERDES_MODE_1000BaseX);
        break;
    default:
        VTSS_E("illegal interface, port %u", port_no);
        return VTSS_RC_ERROR;
    }
    // ports 32-48 can only be connected to QSGMII Serdes
    if (port >= 32 && port < 48) {
        serdes_mode = VTSS_SERDES_MODE_QSGMII;
    }

    if (conf->loop == VTSS_PORT_LOOP_PCS_HOST) {
        serdes_mode = VTSS_SERDES_MODE_TEST_MODE;
    }

#if defined(VTSS_ARCH_SERVAL_T)
    if (port < 2 && !fdx) {
        // BZ20496: half-duplex not supported
        VTSS_E("Half-duplex not supported on internal ports (port %u)", port_no);
        return VTSS_RC_ERROR;
    }
    // Enable/disable the internal Phy of ServalT
    VTSS_RC(srvlt_phy_config(vtss_state, port, (conf->if_type == VTSS_PORT_INTERFACE_SGMII) ? TRUE : FALSE));
#endif

    if (VTSS_PORT_IS_10G(port)) {
        /* Configure the 10G Mux mode to DEV2G5 */
        JR2_WRM(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                VTSS_ENCODE_BITFIELD(3, bt_fld, 2),
                VTSS_ENCODE_BITMASK(bt_fld, 2));

        /* Must be 1 when the 10G port is attached to DEV2G5*/
        JR2_WRM(VTSS_DSM_CFG_DEV_TX_STOP_WM_CFG(port),
                VTSS_F_DSM_CFG_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA(1),
                VTSS_M_DSM_CFG_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA);

    }

    /* Enable the Serdes if disabled */
    if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_DISABLE) {
        VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, serdes_mode));
    }

    if (disable) {
#if defined(VTSS_ARCH_SERVAL_T)
        // In order to keep the Tx clock running, so that frames don't buffer up on a disabled port,
        // make sure to move the mux to pointing to Serdes (which always has the Tx clock enabled) rather
        // than the internal PHY (which will get its Tx clock disabled during administrative shutdown).
        // Having the queue system operable during shutdown will allow for Up-MEP counting and for
        // allowing the AFI to remove frames from a port that already has reached its AFI::FRM_OUT_MAX.
        VTSS_RC(srvlt_phy_config(vtss_state, port, FALSE));
#endif
        if (conf->if_type == VTSS_PORT_INTERFACE_QSGMII) {
            return VTSS_RC_OK; // Do nothing for multi port modes
        }
        /* The port is not powered down in CE builds, as frames still needs to be forwarded to an up-mep */
        /* Instead the PCS is disabled, which forces link down and discards frame forwarding */
        JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA(1) |
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1));
        // Update vtss_state database accordingly
        jr2_port_clause_37_control_get(vtss_state,port_no, &(vtss_state->port.clause_37[port_no]));

        // Disable 100fx and 1000BaseX PCS
        JR2_WRM(VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt),
                VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST(1),
                VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST);

        JR2_WRM(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG(tgt),
                VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA(0),
                VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);

        JR2_WRM(VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA(0),
                VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA);

        return VTSS_RC_OK;
    }

    /* Port disable and flush procedure: */
    VTSS_RC(jr2_port_flush(vtss_state, port_no, FALSE));

    /* Configure the Serdes Macro to 'serdes_mode' */
    if (serdes_mode != vtss_state->port.serdes_mode[port_no]) {
        VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, serdes_mode));
    }

    /* Bugzilla 4388: disabling frame aging when in HDX */
    JR2_WRM_CTL(VTSS_HSCH_HSCH_MISC_PORT_MODE(port), !fdx, VTSS_M_HSCH_HSCH_MISC_PORT_MODE_AGE_DIS);

    /* GIG/FDX mode */
    if (fdx) {
        value = VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA;
        if (speed == VTSS_SPEED_1G || speed == VTSS_SPEED_2500M) {
            value |= VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_GIGA_MODE_ENA;
        }
    } else {
        value = 0;
    }
    JR2_WR(VTSS_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG(tgt), value);

    /* Default gaps */
    tx_gap = (speed == VTSS_SPEED_1G) ? 4 : fdx ? 6 : 5;
    if (speed == VTSS_SPEED_100M) {
        hdx_gap_1 = 1;
        hdx_gap_2 = 4;
    } else if (speed == VTSS_SPEED_10M) {
        hdx_gap_1 = 2;
        hdx_gap_2 = 1;
    }

    /* Non default gaps */
    if (conf->frame_gaps.hdx_gap_1 != VTSS_FRAME_GAP_DEFAULT) {
        hdx_gap_1 = conf->frame_gaps.hdx_gap_1;
    }
    if (conf->frame_gaps.hdx_gap_2 != VTSS_FRAME_GAP_DEFAULT) {
        hdx_gap_2 = conf->frame_gaps.hdx_gap_2;
    }
    if (conf->frame_gaps.fdx_gap != VTSS_FRAME_GAP_DEFAULT) {
        tx_gap = conf->frame_gaps.fdx_gap;
    }

    /* Set MAC IFG Gaps */
    JR2_WR(VTSS_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG(tgt),
            VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG(tx_gap) |
            VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1(hdx_gap_1) |
            VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2(hdx_gap_2));

    /* Set MAC HDX late collision */
    JR2_WRM(VTSS_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG(tgt),
            VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS(67) |
            VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA(conf->exc_col_cont),
            VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS |
            VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA);

    /* PCS settings for 100fx/SGMII/SERDES */
    if (if_100fx) {

        /* 100FX PCS */
        JR2_WRM(VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA(!disable) |
                VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL(!conf->sd_internal) |
                VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_POL(conf->sd_active_high) |
                VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA(conf->sd_enable),
                VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA |
                VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL |
                VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_POL |
                VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA);
    } else {
        /* Disable 100FX */
        JR2_WRM_CLR(VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                     VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA);

        /* Choose SGMII or Serdes PCS mode */
        JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_SGMII_MODE_ENA(sgmii));

        if (sgmii) {
            /* Set whole register */
            JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                   VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(1));
        } else {
            /* Clear specific bit only */
            JR2_WRM_CLR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                         VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA);
        }

        JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_POL(conf->sd_active_high) |
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA(conf->sd_enable) |
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_SEL(!conf->sd_internal));

        /* Enable/disable PCS */
        JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA(!disable));

        if (conf->if_type == VTSS_PORT_INTERFACE_SGMII || conf->if_type == VTSS_PORT_INTERFACE_SGMII_2G5) {
            JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt), 0);
        } else if (conf->if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
            /* Complete SGMII aneg */
            JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                   VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(0x0001) |
                   VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(1) |
                   VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA(1) |
                   VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1));

            /* Clear the sticky bits */
            JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);
            JR2_WR(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), value);
        }
    }
    //Update vtss_state database accordingly
    jr2_port_clause_37_control_get(vtss_state,port_no,&(vtss_state->port.clause_37[port_no]));

    JR2_WRM_CTL(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG(tgt),
                 conf->loop == VTSS_PORT_LOOP_PCS_HOST,
                VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA(1));

    /* Set Max Length */
    JR2_WRM(VTSS_DEV1G_MAC_CFG_STATUS_MAC_MAXLEN_CFG(tgt),
            VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN(conf->max_frame_length),
            VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN);

    /* Configure frame length check (from ethertype / length field) */
    JR2_WRM(VTSS_DEV1G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(tgt),
            VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA(conf->frame_length_chk),
            VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA);

    /* Configure MAC vlan awareness */
    VTSS_RC(vtss_jr2_port_max_tags_set(vtss_state, port_no));

    /* Must be 1 for 10/100 */
    JR2_WRM(VTSS_DSM_CFG_DEV_TX_STOP_WM_CFG(port),
            VTSS_F_DSM_CFG_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM((speed == VTSS_SPEED_10M || speed == VTSS_SPEED_100M) ? 1 : 0),
            VTSS_M_DSM_CFG_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM);

    if (!disable) {
        /* Configure flow control */
        if (jr2_port_fc_setup(vtss_state, port, conf) != VTSS_RC_OK) {
            VTSS_E("Could not configure FC port: %u", port);
        }
        /* Update policer flow control configuration */
        VTSS_RC(vtss_jr2_port_policer_fc_set(vtss_state, port_no, port));

        /* Enable MAC module */
        JR2_WR(VTSS_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG(tgt),
               VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA |
               VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA);

        /* Take MAC, Port, Phy (intern) and PCS (SGMII/Serdes) clock out of reset */
        JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt),
               VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL(speed == VTSS_SPEED_10M ? 0 : speed == VTSS_SPEED_100M ? 1 : 2));

        /* Core: This is a 1G/2G5 port (fwd_speed) and enable port for frame transfer */
#if defined(VTSS_ARCH_JAGUAR_2_B)
        /* The arbiter must know the port speed */
        JR2_WRM(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(port),
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(1) |
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_SPEED(speed == VTSS_SPEED_2500M ? 1 : 0),
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA |
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_SPEED);
#else
        JR2_WRM(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(port),
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(1) |
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_URGENCY(speed == VTSS_SPEED_2500M ? 41 : 104), //( 270000/6400 - 1) : (672000/6400 - 1)
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA |
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_URGENCY);
#endif

        /* Enable flowcontrol - must be done after the port is enabled */
        if (conf->flow_control.generate) {
            JR2_WRM_SET(VTSS_QSYS_PAUSE_CFG_PAUSE_CFG(port), VTSS_M_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA);
        }
    }

    VTSS_D("chip port: %u (1G),is configured", port);
    return VTSS_RC_OK;
}

static vtss_serdes_mode_t map_media_to_serdes(vtss_sd10g_media_type_t media)
{
    switch (media) {
    case VTSS_SD10G_MEDIA_SR: return VTSS_SERDES_MODE_SFI_SR;
    case VTSS_SD10G_MEDIA_ZR: return VTSS_SERDES_MODE_SFI_ZR;
    case VTSS_SD10G_MEDIA_DAC: return VTSS_SERDES_MODE_SFI_DAC;
    case VTSS_SD10G_MEDIA_BP: return VTSS_SERDES_MODE_SFI_BP;
    case VTSS_SD10G_MEDIA_B2B: return VTSS_SERDES_MODE_SFI_B2B;
    case VTSS_SD10G_MEDIA_10G_KR: return VTSS_SERDES_MODE_SFI_KR;
    case VTSS_SD10G_MEDIA_PR_NONE: return VTSS_SERDES_MODE_SFI_PR_NONE;
    default:
        return VTSS_SERDES_MODE_SFI_PR_NONE;
    }
}

static vtss_rc jr2_port_conf_10g_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t   *conf = &vtss_state->port.conf[port_no];
    u32                port = VTSS_CHIP_PORT(port_no);
    u32                tgt;
    vtss_port_speed_t  speed = conf->speed;
#if !defined(VTSS_ARCH_SERVAL_T)
    BOOL               rx_flip = conf->xaui_rx_lane_flip;
    BOOL               tx_flip = conf->xaui_tx_lane_flip;
    u32                bt_fld = (port == 49) ? 12 : (port == 50) ? 14 : (port == 51) ? 16 : 18;
#else                  // Offset of Dev10G_MODE
    u32                bt_fld = (port == 9) ? 0 : 2;
#endif /* VTSS_ARCH_SERVAL_T */
    u32                mode_10g = 0;
    u32                link_speed = 4;
    vtss_serdes_mode_t serdes_mode;

    // Find device target and serdes macro for this chip port
    VTSS_RC(jr2_port_inst_get(vtss_state, port_no, &tgt, NULL, NULL));

    /* Verify speed */
    switch (speed) {
    case VTSS_SPEED_10G:
        break;
    default:
        VTSS_E("Illegal speed: %d", speed);
        return VTSS_RC_ERROR;
    }

    VTSS_D("chip port: %u interface:%s", port, vtss_port_if_txt(conf->if_type));
    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_XAUI:
        serdes_mode = VTSS_SERDES_MODE_XAUI;
        mode_10g = 1;
        break;
    case VTSS_PORT_INTERFACE_RXAUI:
        serdes_mode = VTSS_SERDES_MODE_RXAUI;
        mode_10g = 2;
        break;
    case VTSS_PORT_INTERFACE_SFI:
        serdes_mode = map_media_to_serdes(conf->serdes.media_type);
        mode_10g = 0;
        link_speed = 7;
        break;
    case VTSS_PORT_INTERFACE_LOOPBACK:
        serdes_mode = VTSS_SERDES_MODE_1000BaseX;
        mode_10g = 3;
        break;
    default:
        VTSS_E("Illegal interface type");
        return VTSS_RC_ERROR;
    }

    /* Configure the 10G Mux mode  */
    JR2_WRM(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
            VTSS_ENCODE_BITFIELD(mode_10g, bt_fld,2),
            VTSS_ENCODE_BITMASK(bt_fld,2));

   /* This is a 10G port only */
    JR2_WRM(VTSS_DSM_CFG_DEV_TX_STOP_WM_CFG(port),
            VTSS_F_DSM_CFG_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM(0) |
            VTSS_F_DSM_CFG_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA(0),
            VTSS_M_DSM_CFG_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM |
            VTSS_M_DSM_CFG_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA);

    if (conf->power_down) {
        /* The port is not powered down in CE builds, as frames still needs to be forwarded to an up-mep */
        /* Instead the Serdes is configured to send out idles which simulates port down state */
        VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, VTSS_SERDES_MODE_IDLE));
        return VTSS_RC_OK;
    }

    /* Enable the Serdes if disabled */
    if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_DISABLE) {
        VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, serdes_mode));
    }

    /* Port disable and flush procedure: */
    VTSS_RC(jr2_port_flush(vtss_state, port_no, TRUE));

   /* Re-configure Serdes if needed */
    if (serdes_mode != vtss_state->port.serdes_mode[port_no] ||
        vtss_state->port.current_mt[port_no] != conf->serdes.media_type) {
        VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, serdes_mode));
    }

    if (conf->if_type == VTSS_PORT_INTERFACE_XAUI) {
#if !defined(VTSS_ARCH_SERVAL_T)
        /* XAUI: Handle Signal Detect */
        JR2_WR(VTSS_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG(tgt),
               VTSS_F_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG_SD_POL(conf->sd_active_high) |
               VTSS_F_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG_SD_SEL(!conf->sd_internal) |
               VTSS_F_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG_SD_ENA(conf->sd_enable));

        /* Enable XAUI PCS */
        JR2_WRM_SET(VTSS_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG(tgt),
                    VTSS_M_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG_PCS_ENA);

        /* XAUI Lane flipping  */
        JR2_WRM(VTSS_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_EXT_CFG(tgt),
                VTSS_F_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_EXT_CFG_RX_FLIP_HMBUS(rx_flip) |
                VTSS_F_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_EXT_CFG_TX_FLIP_HMBUS(tx_flip),
                VTSS_M_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_EXT_CFG_RX_FLIP_HMBUS |
                VTSS_M_DEV10G_PCS_XAUI_CONFIGURATION_PCS_XAUI_EXT_CFG_TX_FLIP_HMBUS);
    } else if (conf->if_type == VTSS_PORT_INTERFACE_RXAUI) {
        /*  RXAUI: Enable RXAUI PCS and Handle Signal Detect */
        JR2_WRM(VTSS_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG(tgt),
                VTSS_F_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_PCS_ENA(1) |
                VTSS_F_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_SD_POL(conf->sd_active_high) |
                VTSS_F_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_SD_SEL(!conf->sd_internal) |
                VTSS_F_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_SD_ENA(conf->sd_enable),
                VTSS_M_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_PCS_ENA |
                VTSS_M_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_SD_POL |
                VTSS_M_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_SD_SEL |
                VTSS_M_DEV10G_PCS2X6G_CONFIGURATION_PCS2X6G_CFG_SD_ENA);
#endif /* VTSS_ARCH_SERVAL_T */
    } else if (conf->if_type == VTSS_PORT_INTERFACE_SFI) {
        /* SFI: Handle Signal Detect */
        JR2_WR(VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG(VTSS_TO_10G_PCS_TGT(port)),
               VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_POL(conf->sd_active_high) |
               VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_SEL(!conf->sd_internal) |
               VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_ENA(conf->sd_enable));

        /* Enable SFI PCS */
        JR2_WRM_SET(VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG(VTSS_TO_10G_PCS_TGT(port)),
                    VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_PCS_ENA);

    } else {
        VTSS_E("Interface config not done yet");
        return VTSS_RC_ERROR;
    }

    /* MAC Host loopback */
    JR2_WRM(VTSS_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG(tgt),
            VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG_XGMII_HOST_LB_ENA(conf->loop == VTSS_PORT_LOOP_PCS_HOST),
            VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG_XGMII_HOST_LB_ENA);


    /* Set Max Length and maximum tags allowed */
    JR2_WRM(VTSS_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG(tgt),
            VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN(conf->max_frame_length),
            VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN);

    /* Configure framelength check (from ethertype / length field) */
    JR2_WRM(VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(tgt),
            VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_INR_ERR_ENA(conf->frame_length_chk),
            VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_INR_ERR_ENA);

    /* Configure MAC vlan awareness */
    VTSS_RC(vtss_jr2_port_max_tags_set(vtss_state, port_no));

    if (!conf->power_down) {
        /* Configure flow control */
        if (jr2_port_fc_setup(vtss_state, port, conf) != VTSS_RC_OK) {
            VTSS_E("Could not configure FC port: %u", port);
        }
        /* Enable MAC module */
        JR2_WR(VTSS_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG(tgt),
               VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA |
               VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA);

        JR2_WRM(VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt),
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST(0) |
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST(0) |
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST(0) |
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST(0) |
                VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL(link_speed),
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST |
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST |
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST |
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST |
                VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL);

        /* Core: This is a 10G port (fwd_speed) and enable port for frame transfer */
#if defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_WRM(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(port),
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_SPEED(2),
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_SPEED);
#endif /* VTSS_ARCH_JAGUAR_2_B */

#if defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_WRM(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(port),
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(1),
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);
#else /* VTSS_ARCH_JAGUAR_2_C */
        JR2_WRM(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(port),
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(1) |
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_URGENCY(9),
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA |
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_URGENCY);
#endif /* VTSS_ARCH_JAGUAR_2_B */

        /* Enable flowcontrol - must be done after the port is enabled */
        if (conf->flow_control.generate) {
            JR2_WRM_SET(VTSS_QSYS_PAUSE_CFG_PAUSE_CFG(port), VTSS_M_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA);
        }

        /* Restart KR-Aneg after port is enabled */
        if (vtss_state->port.kr_conf[port_no].aneg.enable) {
            jr2_port_kr_conf_set(vtss_state, port_no);
        }
    } else {
        /* Disable the power hungry serdes */
        VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, VTSS_SERDES_MODE_DISABLE));
    }
    vtss_state->port.current_mt[port_no] = vtss_state->port.conf[port_no].serdes.media_type;
    VTSS_D("chip port: %u (10G),is configured", port);

    return VTSS_RC_OK;
}


static vtss_rc jr2_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    BOOL             port_10g;
    u32              port = VTSS_CHIP_PORT(port_no), value, mode;
#if defined(VTSS_ARCH_SERVAL_T)
    u32              bt_fld = (port == 9) ? 0 : 2;
#else                // Offset of Dev10G_MODE
    u32              bt_fld = (port == 49) ? 12 : (port == 50) ? 14 : (port == 51) ? 16 : 18;
#endif

    VTSS_I("port_no:%d (port:%d), shutdown:%d", port_no, port, conf->power_down);

    if (!vrfy_spd_iface(port_no, conf->if_type, conf->speed, &port_10g)) {
        return VTSS_RC_ERROR;
    }
    /* The 10G ports can be either DEV10G or DEV2G5 */
    /* Only one of them can be active and attached to the switch core at a time. */
    /* A shut down must be performed on the DEV that is not active: */
    if (VTSS_PORT_IS_10G(port) && !conf->power_down) {
        JR2_RD(VTSS_HSIO_HW_CFGSTAT_HW_CFG, &value);
        mode = VTSS_EXTRACT_BITFIELD(value, bt_fld, 2);
        VTSS_D("port_10g = %d, Mode = %u", port_10g, mode);
        if ((mode == 3) && port_10g) {
            VTSS_RC(jr2_port_flush(vtss_state, port_no, FALSE)); // Shutdown the 2G5 device
            (void)jr2_port_counters_clear(vtss_state, port_no);  // Clear counters before DEV change
        } else if ((mode != 3) && !port_10g) {
            VTSS_RC(jr2_port_flush(vtss_state, port_no, TRUE));  // Shutdown the 10G device
            (void)jr2_port_counters_clear(vtss_state, port_no);  // Clear counters before DEV change
        }
    }

    VTSS_D("port_no:%d (port:%d, dev%s) if:%s, spd:%s/%s, shutdown:%d",
           port_no, port, VTSS_PORT_IS_10G(port) ? "10G":"1G", vtss_port_if_txt(conf->if_type),
           vtss_port_spd_txt(conf->speed), conf->fdx ? "FDX" : "HDX", conf->power_down);

    if (port_10g) {
        return jr2_port_conf_10g_set(vtss_state, port_no);
    } else {
        return jr2_port_conf_1g_set(vtss_state, port_no);
    }
}

//----------------------------------------------------------------------------------------------------



/* Get status of the XAUI, VAUI or 100FX ports. */
/* Status for SERDES and SGMII ports is handled elsewhere (through autonegotiation) */
static vtss_rc jr2_port_status_get(vtss_state_t *vtss_state,
                                  const vtss_port_no_t  port_no,
                                  vtss_port_status_t    *const status)
{
    u32              value, sd;
    u32              tgt;
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];

    VTSS_RC(jr2_port_inst_get(vtss_state, port_no, &tgt, NULL, NULL));

    if (conf->power_down) {
        /* Disabled port is considered down */
        return VTSS_RC_OK;
    }

    switch (vtss_state->port.conf[port_no].if_type) {
    case VTSS_PORT_INTERFACE_100FX:
        /* Get the PCS status  */
        JR2_RD(VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), &value);

        /* Link has been down if the are any error stickies */
        status->link_down = VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY(value) ||
                            VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY(value) ||
                            VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY(value) ||
                            VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_STATUS(value);

        /* BZ#22236 - One of 10G port link with 100FX SFP goes down in J2-24 and J2-48 after traffic is started
         * When polling for link status several
         * sticky bits are checked.  If they are set then the link is considered down and
         * the port is removed from the forwarding mask. The SSD_ERROR_STICKY (Stream
         * Start Delimiter Error from FX100-PCS) was getting asserted on a 100FX/10G port,
         * but no frames are lost.
         * The logic owner (Alexander Kock) have looked at this but cannot explain this,
         * the frames should be dropped if the sticky is asserted.  As a workaround we
         * decided to remove this bit from the checking.
         * changeset: 23d0a0aefa70bf5a99f2cc071d6a6a25efb1bb85
         *
         * And then we found the workaround bring the new issue.
         * BZ#23095: Ports are blinking continuously when SFPs are inserted, without any cable connected
         * Therefore, update the workaround on 10G port only.
         */
        if (!VTSS_PORT_IS_10G(VTSS_CHIP_PORT(port_no))) {
            status->link_down |= VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY(value) ? 1 : 0;
        }

        if (status->link_down) {
            /* Clear the stickies and re-read */
            JR2_WR(VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), value);
            VTSS_MSLEEP(1);
            JR2_RD(VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), &value);
        }
        /* Link=1 if sync status=1 and no error stickies after a clear */
        status->link = VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_STATUS(value) &&
                     (!VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY(value) &&
                      !VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY(value) &&
                      !VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY(value) &&
                      !VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_STATUS(value));

        //BZ#23095
        if (!VTSS_PORT_IS_10G(VTSS_CHIP_PORT(port_no))) {
            status->link &= (VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_STATUS(value) &&
                            !VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY(value)) ? 1 : 0;
        }

        status->speed = VTSS_SPEED_100M;
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        /* Get the PCS status */
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(tgt), &value);
        status->link = JR2_BF(DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS, value) &&
                       JR2_BF(DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS, value);
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);
        status->link_down = JR2_BF(DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY, value);
        if (status->link_down) {
            /* The link has been down. Clear the sticky bit */
            JR2_WRM_SET(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt),
                        VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY);
        }
        status->speed = VTSS_SPEED_2500M;
        break;
    case VTSS_PORT_INTERFACE_XAUI:
    case VTSS_PORT_INTERFACE_RXAUI:
    case VTSS_PORT_INTERFACE_SFI:
        /* MAC10G Tx Monitor Sticky bit Register */
        JR2_RD(VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY(tgt), &value);
        /* Signal detect from the 10G Macro */
        JR2_RD(VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10(VTSS_TO_10G_SRD_TGT(VTSS_CHIP_PORT(port_no))), &sd);
        if (value != 2) {
            /* The link is or has been down. Clear the sticky bit */
            status->link_down = 1;
            JR2_WR(VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY(tgt), 0xFFFFFFFF);
            JR2_RD(VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY(tgt), &value);
        }
        if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SFI) {
            /* IDLE_STATE_STICKY = 1 and no others stickys --> link on */
            status->link = (value == 2 ? 1 : 0) && VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_SDET(sd);
        } else {
            status->link = (value == 2 ? 1 : 0);
        }
        status->speed = conf->speed;
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        status->link = 0;
        status->link_down = 0;
        break;
    default:
        VTSS_E("Status not supported for port: %u", port_no);
        return VTSS_RC_ERROR;
    }
    status->fdx = conf->fdx;
    return VTSS_RC_OK;
}

#define JR2_CNT_1G(name, i, cnt, clr)                         \
{                                                            \
    u32 value;                                               \
    JR2_RD(VTSS_ASM_DEV_STATISTICS_##name##_CNT(i), &value); \
    vtss_cmn_counter_32_update(value, cnt, clr);             \
}

#define JR2_CNT_10G(name, i, cnt, clr)                           \
{                                                               \
    u32 value;                                                  \
    JR2_RD(VTSS_DEV10G_DEV_STATISTICS_##name##_CNT(i), &value); \
    vtss_cmn_counter_32_update(value, cnt, clr);                \
}

#define JR2_CNT_ANA_AC(name, cnt, clr)               \
{                                                    \
    u32 value;                                       \
    JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_##name, &value); \
    vtss_cmn_counter_32_update(value, cnt, clr);     \
}

static vtss_rc vtss_jr2_qsys_counter_update(vtss_state_t *vtss_state,
                                            u32 *addr, vtss_chip_counter_t *counter, BOOL clear)
{
    u32 value;

#if defined(VTSS_ARCH_JAGUAR_2_C)
    JR2_RD(VTSS_XQS_STAT_CNT(*addr), &value);
#else
    JR2_RD(VTSS_QSYS_STAT_CNT(*addr), &value);
#endif /* VTSS_ARCH_JAGUAR_2_C */

    *addr = (*addr + 1); /* Next counter address */
    vtss_cmn_counter_32_update(value, counter, clear);

    return VTSS_RC_OK;
}

/* Index of ANA_AC port counters */
#define JR2_CNT_ANA_AC_PORT_FILTER        0
#define JR2_CNT_ANA_AC_PORT_POLICER_DROPS 1

/* Index of ANA_AC queue counters */
#define JR2_CNT_ANA_AC_QUEUE_PRIO 0

static vtss_rc jr2_port_counters_chip(vtss_state_t                 *vtss_state,
                                      vtss_port_no_t               port_no,
                                      vtss_port_jr2_counters_t     *c,
                                      vtss_port_counters_t *const  counters,
                                      BOOL                         clr)
{
    u32                                i, addr, port;
    vtss_port_counter_t                rx_errors;
    vtss_port_rmon_counters_t          *rmon;
    vtss_port_if_group_counters_t      *if_group;
    vtss_port_ethernet_like_counters_t *elike;
    vtss_port_proprietary_counters_t   *prop;

    if (port_no >= vtss_state->port_count) {
        /* CPU/virtual port */
        port = (VTSS_CHIP_PORT_CPU + port_no - vtss_state->port_count);
    } else if (!port_is_in_10g_mode(vtss_state, port_no)) {
        /* ASM counters */
        port = VTSS_CHIP_PORT(port_no);
        i = port;
        JR2_CNT_1G(RX_IN_BYTES, i, &c->rx_in_bytes, clr);
        JR2_CNT_1G(RX_SYMBOL_ERR, i, &c->rx_symbol_err, clr);
        JR2_CNT_1G(RX_PAUSE, i, &c->rx_pause, clr);
        JR2_CNT_1G(RX_UNSUP_OPCODE, i, &c->rx_unsup_opcode, clr);
        JR2_CNT_1G(RX_OK_BYTES, i, &c->rx_ok_bytes, clr);
        JR2_CNT_1G(RX_BAD_BYTES, i, &c->rx_bad_bytes, clr);
        JR2_CNT_1G(RX_UC, i, &c->rx_unicast, clr);
        JR2_CNT_1G(RX_MC, i, &c->rx_multicast, clr);
        JR2_CNT_1G(RX_BC, i, &c->rx_broadcast, clr);
        JR2_CNT_1G(RX_CRC_ERR, i, &c->rx_crc_err, clr);
        JR2_CNT_1G(RX_UNDERSIZE, i, &c->rx_undersize, clr);
        JR2_CNT_1G(RX_FRAGMENTS, i, &c->rx_fragments, clr);
        JR2_CNT_1G(RX_IN_RANGE_LEN_ERR, i, &c->rx_in_range_len_err, clr);
        JR2_CNT_1G(RX_OUT_OF_RANGE_LEN_ERR, i, &c->rx_out_of_range_len_err, clr);
        JR2_CNT_1G(RX_OVERSIZE, i, &c->rx_oversize, clr);
        JR2_CNT_1G(RX_JABBERS, i, &c->rx_jabbers, clr);
        JR2_CNT_1G(RX_SIZE64, i, &c->rx_size64, clr);
        JR2_CNT_1G(RX_SIZE65TO127, i, &c->rx_size65_127, clr);
        JR2_CNT_1G(RX_SIZE128TO255, i, &c->rx_size128_255, clr);
        JR2_CNT_1G(RX_SIZE256TO511, i, &c->rx_size256_511, clr);
        JR2_CNT_1G(RX_SIZE512TO1023, i, &c->rx_size512_1023, clr);
        JR2_CNT_1G(RX_SIZE1024TO1518, i, &c->rx_size1024_1518, clr);
        JR2_CNT_1G(RX_SIZE1519TOMAX, i, &c->rx_size1519_max, clr);

        JR2_CNT_1G(TX_OUT_BYTES, i, &c->tx_out_bytes, clr);
        JR2_CNT_1G(TX_PAUSE, i, &c->tx_pause, clr);
        JR2_CNT_1G(TX_OK_BYTES, i, &c->tx_ok_bytes, clr);
        JR2_CNT_1G(TX_UC, i, &c->tx_unicast, clr);
        JR2_CNT_1G(TX_MC, i, &c->tx_multicast, clr);
        JR2_CNT_1G(TX_BC, i, &c->tx_broadcast, clr);
        JR2_CNT_1G(TX_SIZE64, i, &c->tx_size64, clr);
        JR2_CNT_1G(TX_SIZE65TO127, i, &c->tx_size65_127, clr);
        JR2_CNT_1G(TX_SIZE128TO255, i, &c->tx_size128_255, clr);
        JR2_CNT_1G(TX_SIZE256TO511, i, &c->tx_size256_511, clr);
        JR2_CNT_1G(TX_SIZE512TO1023, i, &c->tx_size512_1023, clr);
        JR2_CNT_1G(TX_SIZE1024TO1518, i, &c->tx_size1024_1518, clr);
        JR2_CNT_1G(TX_SIZE1519TOMAX, i, &c->tx_size1519_max, clr);
        JR2_CNT_1G(TX_MULTI_COLL, i, &c->tx_multi_coll, clr);
        JR2_CNT_1G(TX_LATE_COLL, i, &c->tx_late_coll, clr);
        JR2_CNT_1G(TX_XCOLL, i, &c->tx_xcoll, clr);
        JR2_CNT_1G(TX_DEFER, i, &c->tx_defer, clr);
        JR2_CNT_1G(TX_XDEFER, i, &c->tx_xdefer, clr);
        JR2_CNT_1G(TX_BACKOFF1, i, &c->tx_backoff1, clr);
    } else {
        /* DEV10G counters */
        port = VTSS_CHIP_PORT(port_no);
        VTSS_RC(jr2_port_inst_get(vtss_state, port_no, &i, NULL, NULL));
        JR2_CNT_10G(40BIT_RX_IN_BYTES, i, &c->rx_in_bytes, clr);
        JR2_CNT_10G(32BIT_RX_SYMBOL_ERR, i, &c->rx_symbol_err, clr);
        JR2_CNT_10G(32BIT_RX_PAUSE, i, &c->rx_pause, clr);
        JR2_CNT_10G(32BIT_RX_UNSUP_OPCODE, i, &c->rx_unsup_opcode, clr);
        JR2_CNT_10G(40BIT_RX_OK_BYTES, i, &c->rx_ok_bytes, clr);
        JR2_CNT_10G(40BIT_RX_BAD_BYTES, i, &c->rx_bad_bytes, clr);
        JR2_CNT_10G(32BIT_RX_UC, i, &c->rx_unicast, clr);
        JR2_CNT_10G(32BIT_RX_MC, i, &c->rx_multicast, clr);
        JR2_CNT_10G(32BIT_RX_BC, i, &c->rx_broadcast, clr);
        JR2_CNT_10G(32BIT_RX_CRC_ERR, i, &c->rx_crc_err, clr);
        JR2_CNT_10G(32BIT_RX_UNDERSIZE, i, &c->rx_undersize, clr);
        JR2_CNT_10G(32BIT_RX_FRAGMENTS, i, &c->rx_fragments, clr);
        JR2_CNT_10G(32BIT_RX_IN_RANGE_LEN_ERR, i, &c->rx_in_range_len_err, clr);
        JR2_CNT_10G(32BIT_RX_OUT_OF_RANGE_LEN_ERR, i, &c->rx_out_of_range_len_err, clr);
        JR2_CNT_10G(32BIT_RX_OVERSIZE, i, &c->rx_oversize, clr);
        JR2_CNT_10G(32BIT_RX_JABBERS, i, &c->rx_jabbers, clr);
        JR2_CNT_10G(32BIT_RX_SIZE64, i, &c->rx_size64, clr);
        JR2_CNT_10G(32BIT_RX_SIZE65TO127, i, &c->rx_size65_127, clr);
        JR2_CNT_10G(32BIT_RX_SIZE128TO255, i, &c->rx_size128_255, clr);
        JR2_CNT_10G(32BIT_RX_SIZE256TO511, i, &c->rx_size256_511, clr);
        JR2_CNT_10G(32BIT_RX_SIZE512TO1023, i, &c->rx_size512_1023, clr);
        JR2_CNT_10G(32BIT_RX_SIZE1024TO1518, i, &c->rx_size1024_1518, clr);
        JR2_CNT_10G(32BIT_RX_SIZE1519TOMAX, i, &c->rx_size1519_max, clr);

        JR2_CNT_10G(40BIT_TX_OUT_BYTES, i, &c->tx_out_bytes, clr);
        JR2_CNT_10G(32BIT_TX_PAUSE, i, &c->tx_pause, clr);
        JR2_CNT_10G(40BIT_TX_OK_BYTES, i, &c->tx_ok_bytes, clr);
        JR2_CNT_10G(32BIT_TX_UC, i, &c->tx_unicast, clr);
        JR2_CNT_10G(32BIT_TX_MC, i, &c->tx_multicast, clr);
        JR2_CNT_10G(32BIT_TX_BC, i, &c->tx_broadcast, clr);
        JR2_CNT_10G(32BIT_TX_SIZE64, i, &c->tx_size64, clr);
        JR2_CNT_10G(32BIT_TX_SIZE65TO127, i, &c->tx_size65_127, clr);
        JR2_CNT_10G(32BIT_TX_SIZE128TO255, i, &c->tx_size128_255, clr);
        JR2_CNT_10G(32BIT_TX_SIZE256TO511, i, &c->tx_size256_511, clr);
        JR2_CNT_10G(32BIT_TX_SIZE512TO1023, i, &c->tx_size512_1023, clr);
        JR2_CNT_10G(32BIT_TX_SIZE1024TO1518, i, &c->tx_size1024_1518, clr);
        JR2_CNT_10G(32BIT_TX_SIZE1519TOMAX, i, &c->tx_size1519_max, clr);
    }

    /* QSYS counters */
#if defined(VTSS_ARCH_JAGUAR_2_C)
    JR2_WR(VTSS_XQS_SYSTEM_STAT_CFG, VTSS_F_XQS_SYSTEM_STAT_CFG_STAT_VIEW(port));
#else
    JR2_WR(VTSS_QSYS_SYSTEM_STAT_CFG, VTSS_F_QSYS_SYSTEM_STAT_CFG_STAT_VIEW(port));
#endif /* VTSS_ARCH_JAGUAR_2_C */
#if defined(VTSS_ARCH_JAGUAR_2_B)
    addr = 0;
#else
    addr = 16;
#endif /* VTSS_ARCH_JAGUAR_2_B */
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_jr2_qsys_counter_update(vtss_state, &addr, &c->tx_green_drops[i], clr));
    }
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_jr2_qsys_counter_update(vtss_state, &addr, &c->tx_yellow_drops[i], clr));
    }
    addr = 256;
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_jr2_qsys_counter_update(vtss_state, &addr, &c->tx_green_class[i], clr));
    }
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_jr2_qsys_counter_update(vtss_state, &addr, &c->tx_yellow_class[i], clr));
    }
    VTSS_RC(vtss_jr2_qsys_counter_update(vtss_state, &addr, &c->tx_queue_drops, clr));

    /* ANA_AC counters */
    JR2_CNT_ANA_AC(PORT_STAT_LSB_CNT(port, JR2_CNT_ANA_AC_PORT_FILTER), &c->rx_local_drops, clr);
    JR2_CNT_ANA_AC(PORT_STAT_LSB_CNT(port, JR2_CNT_ANA_AC_PORT_POLICER_DROPS), &c->rx_policer_drops, clr);
    for (i = 0; i < VTSS_PRIOS; i++) {
        JR2_CNT_ANA_AC(QUEUE_STAT_LSB_CNT(port*8 + i, JR2_CNT_ANA_AC_QUEUE_PRIO), &c->rx_class[i], clr);
    }

    if (counters == NULL) {
        return VTSS_RC_OK;
    }

    /* Proprietary counters */
    prop = &counters->prop;
    for (i = 0; i < VTSS_PRIOS; i++) {
        prop->rx_prio[i] = c->rx_class[i].value;
        prop->tx_prio[i] = (c->tx_yellow_class[i].value + c->tx_green_class[i].value);
    }

    /* RMON Rx counters */
    rmon = &counters->rmon;
    rmon->rx_etherStatsDropEvents = c->rx_policer_drops.value;
    rmon->rx_etherStatsOctets = (c->rx_ok_bytes.value + c->rx_bad_bytes.value);
    rx_errors = (c->rx_crc_err.value +  c->rx_undersize.value + c->rx_oversize.value +
                 c->rx_symbol_err.value + c->rx_jabbers.value + c->rx_fragments.value);
    if (vtss_state->port.conf[port_no].frame_length_chk) {
        rx_errors += (c->rx_in_range_len_err.value + c->rx_out_of_range_len_err.value);
    }
    rmon->rx_etherStatsPkts = (c->rx_unicast.value + c->rx_multicast.value +
                               c->rx_broadcast.value + rx_errors);
    rmon->rx_etherStatsBroadcastPkts = c->rx_broadcast.value;
    rmon->rx_etherStatsMulticastPkts = c->rx_multicast.value;
    rmon->rx_etherStatsCRCAlignErrors = c->rx_crc_err.value;
    rmon->rx_etherStatsUndersizePkts = c->rx_undersize.value;
    rmon->rx_etherStatsOversizePkts = c->rx_oversize.value;
    rmon->rx_etherStatsFragments = c->rx_fragments.value;
    rmon->rx_etherStatsJabbers = c->rx_jabbers.value;
    rmon->rx_etherStatsPkts64Octets = c->rx_size64.value;
    rmon->rx_etherStatsPkts65to127Octets = c->rx_size65_127.value;
    rmon->rx_etherStatsPkts128to255Octets = c->rx_size128_255.value;
    rmon->rx_etherStatsPkts256to511Octets = c->rx_size256_511.value;
    rmon->rx_etherStatsPkts512to1023Octets = c->rx_size512_1023.value;
    rmon->rx_etherStatsPkts1024to1518Octets = c->rx_size1024_1518.value;
    rmon->rx_etherStatsPkts1519toMaxOctets = c->rx_size1519_max.value;

    /* RMON Tx counters */
    rmon->tx_etherStatsDropEvents = c->tx_queue_drops.value;
    for (i = 0; i < VTSS_PRIOS; i++) {
        rmon->tx_etherStatsDropEvents += (c->tx_green_drops[i].value + c->tx_yellow_drops[i].value);
    }
    rmon->tx_etherStatsPkts = (c->tx_unicast.value + c->tx_multicast.value +
                               c->tx_broadcast.value + c->tx_late_coll.value);
    rmon->tx_etherStatsOctets = c->tx_ok_bytes.value;
    rmon->tx_etherStatsBroadcastPkts = c->tx_broadcast.value;
    rmon->tx_etherStatsMulticastPkts = c->tx_multicast.value;
    rmon->tx_etherStatsCollisions = (c->tx_multi_coll.value + c->tx_backoff1.value +
                                     c->tx_late_coll.value + c->tx_xcoll.value);
    rmon->tx_etherStatsPkts64Octets = c->tx_size64.value;
    rmon->tx_etherStatsPkts65to127Octets = c->tx_size65_127.value;
    rmon->tx_etherStatsPkts128to255Octets = c->tx_size128_255.value;
    rmon->tx_etherStatsPkts256to511Octets = c->tx_size256_511.value;
    rmon->tx_etherStatsPkts512to1023Octets = c->tx_size512_1023.value;
    rmon->tx_etherStatsPkts1024to1518Octets = c->tx_size1024_1518.value;
    rmon->tx_etherStatsPkts1519toMaxOctets = c->tx_size1519_max.value;

    /* Interfaces Group Rx counters */
    if_group = &counters->if_group;
    if_group->ifInOctets = rmon->rx_etherStatsOctets;
    if_group->ifInUcastPkts = c->rx_unicast.value;
    if_group->ifInMulticastPkts = c->rx_multicast.value;
    if_group->ifInBroadcastPkts = c->rx_broadcast.value;
    if_group->ifInNUcastPkts = (c->rx_multicast.value + c->rx_broadcast.value);
    if_group->ifInDiscards = rmon->rx_etherStatsDropEvents;
    if_group->ifInErrors = rx_errors;

    /* Interfaces Group Tx counters */
    if_group->ifOutOctets = rmon->tx_etherStatsOctets;
    if_group->ifOutUcastPkts = c->tx_unicast.value;
    if_group->ifOutMulticastPkts = c->tx_multicast.value;
    if_group->ifOutBroadcastPkts = c->tx_broadcast.value;
    if_group->ifOutNUcastPkts = (c->tx_multicast.value + c->tx_broadcast.value);
    if_group->ifOutDiscards = rmon->tx_etherStatsDropEvents;
    if_group->ifOutErrors = (c->tx_late_coll.value + c->tx_csense.value + c->tx_xcoll.value);

    /* Ethernet-like Rx counters */
    elike = &counters->ethernet_like;
    elike->dot3StatsAlignmentErrors = 0; /* Not supported */
    elike->dot3StatsFCSErrors = c->rx_crc_err.value;
    elike->dot3StatsFrameTooLongs = c->rx_oversize.value;
    elike->dot3StatsSymbolErrors = c->rx_symbol_err.value;
    elike->dot3ControlInUnknownOpcodes = c->rx_unsup_opcode.value;
    elike->dot3InPauseFrames = c->rx_pause.value + c->rx_unsup_opcode.value;

    /* Ethernet-like Tx counters */
    elike->dot3StatsSingleCollisionFrames = c->tx_backoff1.value;
    elike->dot3StatsMultipleCollisionFrames = c->tx_multi_coll.value;
    elike->dot3StatsDeferredTransmissions = c->tx_defer.value;
    elike->dot3StatsLateCollisions = c->tx_late_coll.value;
    elike->dot3StatsExcessiveCollisions = c->tx_xcoll.value;
    elike->dot3StatsCarrierSenseErrors = c->tx_csense.value;
    elike->dot3OutPauseFrames = c->tx_pause.value;

    /* Bridge counters, including filtered frames with and without CRC error */
    counters->bridge.dot1dTpPortInDiscards = c->rx_local_drops.value;

    return VTSS_RC_OK;
}

static vtss_rc jr2_port_basic_counters_get(vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no,
                                            vtss_basic_counters_t *const counters)
{
    // JR2-TBD: Stub
    return VTSS_RC_ERROR;
}

static vtss_rc jr2_port_counters(vtss_state_t                *vtss_state,
                                 const vtss_port_no_t        port_no,
                                 vtss_port_counters_t *const counters,
                                 BOOL                        clear)
{
    return jr2_port_counters_chip(vtss_state,
                                  port_no,
                                  &vtss_state->port.counters[port_no].counter.jr2,
                                  counters,
                                  clear);
}

static vtss_rc jr2_port_counters_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return jr2_port_counters(vtss_state, port_no, NULL, 0);
}

static vtss_rc jr2_port_counters_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return jr2_port_counters(vtss_state, port_no, NULL, 1);
}

static vtss_rc jr2_port_counters_get(vtss_state_t *vtss_state,
                                      const vtss_port_no_t port_no,
                                      vtss_port_counters_t *const counters)
{
    VTSS_MEMSET(counters, 0, sizeof(*counters));
    return jr2_port_counters(vtss_state, port_no, counters, 0);
}

static vtss_rc jr2_port_forward_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc jr2_port_test_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32                tgt, serdes_inst, serdes_type, port = VTSS_CHIP_PORT(port_no);
    vtss_serdes_mode_t mode = vtss_state->port.serdes_mode[port_no];
    vtss_port_lb_t lb = vtss_state->port.test_conf[port_no].loopback;
    vtss_port_conf_t   *conf = &vtss_state->port.conf[port_no];
    u32 tgt_ana = VTSS_TO_10G_SRD_TGT(port);

    VTSS_RC(jr2_port_inst_get(vtss_state, port_no, &tgt, &serdes_inst, &serdes_type));

    switch (serdes_type) {
    case JR2_SERDES_TYPE_1G:
        VTSS_RC(jr2_sd1g_cfg(vtss_state, port_no, mode, 1 << serdes_inst));
        break;

    case JR2_SERDES_TYPE_6G:
        if (mode != VTSS_SERDES_MODE_QSGMII || (port % 4) == 0) {
            VTSS_RC(jr2_sd6g_cfg(vtss_state, port_no, mode, 1 << serdes_inst));
        }
        break;

    case JR2_SERDES_TYPE_10G:
        if (lb == VTSS_PORT_LB_EQUIPMENT || lb == VTSS_PORT_LB_DISABLED) {
            JR2_WRM(VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0(tgt_ana),
                    VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_PAD_LOOP(lb != VTSS_PORT_LB_DISABLED),
                    VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_PAD_LOOP);

            JR2_WRM(VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0(tgt_ana),
                    VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SIG_SEL(lb == VTSS_PORT_LB_DISABLED ? 0 : 2),
                    VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SIG_SEL);

            JR2_WRM(VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3(tgt_ana),
                    VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SET_SDET(lb != VTSS_PORT_LB_DISABLED),
                    VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SET_SDET);

            JR2_WRM(VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10(tgt_ana),
                    VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_REC(lb != VTSS_PORT_LB_DISABLED),
                    VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_REC);
        } else {
            VTSS_E("Loopback not supported for port: %u", port_no);
            return VTSS_RC_ERROR;
        }
        return VTSS_RC_OK;
    default:
        break;
    }

    // Disable signal detect during loopback
    if (lb == VTSS_PORT_LB_DISABLED) {
        JR2_WRM(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
                VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA(conf->sd_enable),
                VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA);
        JR2_WRM(VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA(conf->sd_enable),
                VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA);
    } else {
        JR2_WRM(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
                VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA(0),
                VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA);
        JR2_WRM(VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA(0),
                VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA);
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_port_ifh_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    vtss_port_ifh_t *ifh = &vtss_state->port.ifh_conf[port_no];
    BOOL extr =  ifh->ena_xtr_header || ifh->ena_ifh_header;

     /* Enable/Disable IFH parsing at ingress DMAC:SMAC:0x8880:0x0007:IFH:Frame */
    JR2_WRM(VTSS_ASM_CFG_PORT_CFG(port),
            VTSS_F_ASM_CFG_PORT_CFG_INJ_FORMAT_CFG(ifh->ena_inj_header ? 2 : 0) |
            VTSS_F_ASM_CFG_PORT_CFG_SKIP_PREAMBLE_ENA(ifh->ena_inj_header),
            VTSS_M_ASM_CFG_PORT_CFG_SKIP_PREAMBLE_ENA |
            VTSS_M_ASM_CFG_PORT_CFG_INJ_FORMAT_CFG);

     /* Enable/Disable IFH prepend at egress DMAC:SMAC:0x8880:0x0007:IFH:Frame */
    JR2_WRM(VTSS_REW_COMMON_PORT_CTRL(port),
             VTSS_F_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL(extr ? 2 : 0),
             VTSS_M_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL);

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_wm_update(vtss_state_t *vtss_state)
{
    int  group, queue, dpl;
    BOOL enabled[VTSS_PRIOS] = {0};

    for (group = 0; group < VTSS_WRED_GROUP_CNT; group++) {
        for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
            for (dpl = 0; dpl < VTSS_WRED_DPL_CNT; dpl++) {
                if (vtss_state->qos.conf.red_v3[queue][dpl][group].enable) {
                    enabled[queue] = TRUE;
                }
            }
        }
    }

    /* Update BUF_PRIO_SHR_I sharing watermarks, to disallow ingress side in determining sharing state. WRED operates on egress calculations only */
    for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
        if (enabled[queue]) {
            JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((queue + 496 + 0)), 0); /* WRED is enabled somewhere for this QoS class - set watermark to zero */
        } else {
            JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((queue + 496 + 0)), vtss_state->port.buf_prio_shr[queue]); /* Restore initial value */
        }
    }
    return VTSS_RC_OK;
}

#define BUF_OVERSUBSRIPTION_FACTOR 200 // (factor 100 = no oversubsription)
static vtss_rc jr2_port_buf_conf_set(vtss_state_t *vtss_state)
{
    int q;
    u32 port_no, port, dp;
    u32 buf_q_rsrv_i, buf_q_rsrv_e, ref_q_rsrv_i, ref_q_rsrv_e, buf_prio_shr_i[8], buf_prio_shr_e[8];
    u32 buf_p_rsrv_i, buf_p_rsrv_e, ref_p_rsrv_i, ref_p_rsrv_e, buf_col_shr_i, buf_col_shr_e, ref_col_shr_i, ref_col_shr_e;
    u32 buf_prio_rsrv, guaranteed, q_rsrv_mask, prio_mem;

    /* Mode: Strict priority sharing. Higher priorities have right to use all shared before lower */

    /* Reserved space. Buffer values are in BYTES */
    buf_q_rsrv_i  = 4000;                 /* Ingress Queue reserved space (all prios) */
    buf_p_rsrv_i  = 15000;                /* Ingress Port reserved space */
    buf_q_rsrv_e  = 4000;                 /* Egress Queue reserved space (all prios)  */
    buf_p_rsrv_e  = 15000;                /* Egress Port reserved space  */
    buf_col_shr_i = JR2_BUFFER_MEMORY;    /* Coloring - disabled for now */
    buf_col_shr_e = JR2_BUFFER_MEMORY;    /* Coloring - disabled for now */
    buf_prio_rsrv = 6000;                 /* Distance between priority stops in the shared memory */

    /* Reserved frame reference. Values are NUMBER of FRAMES */
    ref_q_rsrv_e  = 4;                    /* Number of frames that can be pending at each egress queue   */
    ref_q_rsrv_i  = 4;                    /* Number of frames that can be pending at each ingress queue  */
    ref_p_rsrv_e  = 10;                   /* Number of frames that can be pending shared between the QoS classes at egress */
    ref_p_rsrv_i  = 10;                   /* Number of frames that can be pending shared between the QoS classes at ingress */
    ref_col_shr_i = JR2_BUFFER_REFERENCE; /* Coloring - disabled for now */
    ref_col_shr_e = JR2_BUFFER_REFERENCE; /* Coloring - disabled for now */


    /* The number of supported queues is given through the state structure                           */
    q_rsrv_mask = 0xff >> (8 - vtss_state->qos.conf.prios);

    /* The memory is oversubsrcribed by BUF_OVERSUBSRIPTION_FACTOR (factor 100 = no oversubsription) */

    /* **************************************************  */
    /* BELOW, everything is calculated based on the above. */
    /* **************************************************  */

    /* Find the amount of guaranteeed space per port */
    guaranteed = buf_p_rsrv_i+buf_p_rsrv_e;
    for (q = 0; q < VTSS_PRIOS; q++) {
        if (q_rsrv_mask & (1 << q))
            guaranteed += (buf_q_rsrv_i+buf_q_rsrv_e);
    }

    if (((vtss_state->port_count + 1) * guaranteed * 100 / BUF_OVERSUBSRIPTION_FACTOR) > JR2_BUFFER_MEMORY) {
        VTSS_E("Memory is oversubscribed");
    }
    /* Find the total amount of shared memory incl. oversubscription */
    prio_mem = JR2_BUFFER_MEMORY - (vtss_state->port_count + 1) * guaranteed * 100 / BUF_OVERSUBSRIPTION_FACTOR;

    /* Find the prio watermarks */
    for (q = vtss_state->qos.conf.prios - 1; q >= 0; q--) {
        buf_prio_shr_i[q] = prio_mem;
        buf_prio_shr_e[q] = prio_mem;
        prio_mem -= buf_prio_rsrv;
    }
    buf_col_shr_i=buf_col_shr_e=prio_mem;

    for (port_no = 0; port_no <= vtss_state->port_count; port_no++) {
        if (port_no == vtss_state->port_count) {
            port = VTSS_CHIP_PORT_CPU_0;
        } else {
            port = VTSS_CHIP_PORT(port_no);
        }
        /* Reserved amount for (PORT,PRIO) at index 8 * PORT + PRIO */
        for (q = 0; q < VTSS_PRIOS; q++) {
            if (q_rsrv_mask&(1 << q)) {
                JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q +    0), wm_enc(buf_q_rsrv_i / JR2_BUFFER_CELL_SZ));
                JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 1024), wm_enc(ref_q_rsrv_i));
                JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 2048), wm_enc(buf_q_rsrv_e / JR2_BUFFER_CELL_SZ));
                JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 3072), wm_enc(ref_q_rsrv_e));
            }
        }
        /* Reserved amount for PORT at index PORT + 512 */
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 +    0), wm_enc(buf_p_rsrv_i / JR2_BUFFER_CELL_SZ));
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 + 1024), wm_enc(ref_p_rsrv_i));
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 + 2048), wm_enc(buf_p_rsrv_e / JR2_BUFFER_CELL_SZ));
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 + 3072), wm_enc(ref_p_rsrv_e));
    }

    /* Maximum allowed use of the shared buffer for PRIO at index PRIO + 496 */
    for (q = 0; q < VTSS_PRIOS; q++) {
        /* Save initial encoded value of shared area for later use by WRED */
        vtss_state->port.buf_prio_shr[q] = wm_enc(buf_prio_shr_i[q] / JR2_BUFFER_CELL_SZ);

        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 +    0)), wm_enc(buf_prio_shr_i[q] / JR2_BUFFER_CELL_SZ));
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 + 2048)), wm_enc(buf_prio_shr_e[q] / JR2_BUFFER_CELL_SZ));
        /* Todo bug#20488:
           JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 + 1024)), wm_enc(ref_prio_shr_i[q]);
           JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 + 3072)), wm_enc(ref_prio_shr_e[q]);
        */
    }

    /* Index 508: Maximum allowed use of the shared buffer for frames with DP=1 (yellow). */
    /* Index 509: Maximum allowed use of the shared buffer for frames with DP=2 (yellow). */
    /* Index 510: Maximum allowed use of the shared buffer for frames with DP=3 (yellow). */
    /* Index 511: Maximum allowed use of the shared buffer for frames with DP=0 (green). */
    for (dp = 0; dp < 4; dp++) {
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(dp + 508 +    0), wm_enc(buf_col_shr_i / JR2_BUFFER_CELL_SZ));
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(dp + 508 + 1024), wm_enc(ref_col_shr_i));
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(dp + 508 + 2048), wm_enc(buf_col_shr_e / JR2_BUFFER_CELL_SZ));
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(dp + 508 + 3072), wm_enc(ref_col_shr_e));
        if (dp==2) {
            // Green watermark should match the highest priority watermark. Otherwise the will be no
            // strict shared space per qos level
            buf_col_shr_i=buf_col_shr_e=buf_prio_shr_i[7];
        }
    }

    /* We do not use VTSS_CHIP_PORT_CPU_1 - set all watermarks to zero. */
    port = VTSS_CHIP_PORT_CPU_1;
    for (q = 0; q < VTSS_PRIOS; q++) {
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q +    0), 0);
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 1024), 0);
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 2048), 0);
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 3072), 0);
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 4096), 0);
    }
    JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 +    0), 0);
    JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 + 1024), 0);
    JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 + 2048), 0);
    JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 + 3072), 0);
    JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(port + 512 + 4096), 0);

    /* On both CPU ports: Enable EGRESS_DROP_MODE and do not use shared memory. */
    for (port = VTSS_CHIP_PORT_CPU_0; port <= VTSS_CHIP_PORT_CPU_1; port++) {
        JR2_WRM(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(port),
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_EGR_NO_SHARING(1) |
                VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_DROP_MODE(1),
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_EGR_NO_SHARING |
                VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_DROP_MODE);
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_ARCH_JAGUAR_2_CE) && !defined(VTSS_ARCH_SERVAL_T)

// Translate a relative filling to an absolute cell count
#define QLIM_WM(total, fraction) \
        (total*fraction/100/JR2_BUFFER_CELL_SZ)

static vtss_rc jr2_port_buf_qlim_set(vtss_state_t *vtss_state)
{
    vtss_qs_conf_t *qs = &vtss_state->init_conf.qs_conf;
    u32 res, dp, prio, port, col, avail;

    // Access to wm parameters through qs->wm1 and qs->wm2);


    // Set legacy share levels to max for src_mem and src_ref
    for (res=0; res<2; res++) {
        for (dp=0; dp<4; dp++) {
            JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(dp + 508 +res*1024), VTSS_M_QRES_RES_CTRL_RES_CFG_WM_HIGH);
        }

        for (prio=0; prio<8; prio++) {
            JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(prio + 496 +res*1024), VTSS_M_QRES_RES_CTRL_RES_CFG_WM_HIGH);
        }
    }

    // Set max mode for all ports
    for (port=0; port<VTSS_CHIP_PORTS; port++) {
        JR2_WR(VTSS_XQS_QLIMIT_PORT_QLIMIT_PORT_CFG(port), VTSS_M_XQS_QLIMIT_PORT_QLIMIT_PORT_CFG_QLIMIT_MAX_MODE_ENA);
    }

    // Disable queuelim for VD1 only
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        JR2_WR(VTSS_XQS_QLIMIT_PORT_QLIMIT_DIS_CFG(port),
               VTSS_F_XQS_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_IGR_DIS(0) |
               VTSS_F_XQS_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_EGR_DIS(port==VTSS_CHIP_PORT_VD1));
    }

    // Set 5,70,90,95,100 % of memory size (or wm1) for qlim,qdiv,ctop,atop,top watermarks
    // Set same for yellow, but take half the memory size (or wm2) as base
    for (col=0; col<2; col++) {
        avail = (col?qs->wm2:qs->wm1);
        if (avail==0) {
            avail = JR2_BUFFER_MEMORY/(col?2:1);
        }

        JR2_WR(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_QLIM_CFG(0,col), QLIM_WM(avail,  5));
        JR2_WR(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_QDIV_CFG(0,col), QLIM_WM(avail, 70));
        JR2_WR(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_CTOP_CFG(0,col), QLIM_WM(avail, 90));
        JR2_WR(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_ATOP_CFG(0,col), QLIM_WM(avail, 95));
        JR2_WR(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_TOP_CFG(0,col),  QLIM_WM(avail,100));
    }

    return VTSS_RC_OK;
}


static vtss_rc jr2_debug_wm_qlim(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t  *const info)
{
    const u32 GAZ_CORE_QUEUE_CNT    = 27328;
    u32 value, q, shr_id, col, aq_cells, cc_cells, sc_cells, qinf;

    pr ("\nQueuelimitation check/status\n");
    pr ("----------------------------\n");

    for (shr_id=0; shr_id<1; shr_id++) {
        pr ("Consumption monitoring for share: %u\n", shr_id);

        JR2_RD(VTSS_XQS_QLIMIT_SHR_QLIMIT_QUE_ACT_CFG(shr_id),  &aq_cells);
        JR2_RD(VTSS_XQS_QLIMIT_SHR_QLIMIT_QUE_CONG_CFG(shr_id), &cc_cells);
        JR2_RD(VTSS_XQS_QLIMIT_SHR_QLIMIT_SE_CONG_CFG(shr_id),  &sc_cells);

        for (col=0; col<2; col++) {
            pr ("%s Watermarks (Act:%2u, Cong:%2u, SE-Cong:%2u)\n", col?"Yellow":"Green", aq_cells, cc_cells, sc_cells);
            JR2_RD(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_TOP_CFG(shr_id, col), &value);
            pr ("Stop for all(*1)...............: %5u\n", value);
            JR2_RD(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_ATOP_CFG(shr_id, col), &value);
            pr ("Stop for active schedulers(*2).: %5u\n", value);
            JR2_RD(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_CTOP_CFG(shr_id, col), &value);
            pr ("Stop for active consumers(*3)..: %5u\n", value);
            JR2_RD(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_QLIM_CFG(shr_id, col), &value);
            pr ("Stop for growing consumers(*4).: %5u\n", value);
            JR2_RD(VTSS_XQS_QLIMIT_SHR_QLIMIT_SHR_QDIV_CFG(shr_id, col), &value);
            pr ("Amount to divide...............: %5u\n", value);
        }

        pr ("\nMaximum consumption tracked:\n");
        JR2_RD(VTSS_XQS_QLIMIT_MON_QLIMIT_SHR_FILL_MAX_STAT(shr_id), &value);
        pr ("Highest fill level...................: %5u\n", value);
        JR2_RD(VTSS_XQS_QLIMIT_MON_QLIMIT_CONG_CNT_MAX_STAT(shr_id), &value);
        pr ("Highest congested SE count...........: %5u\n\n", value);
    }

    pr ("*1: Share filled to this level: drop all incoming\n");
    pr ("*2: Share filled to this level: drop if SE_CONG\n");
    pr ("*3: Share filled to this level: drop if SE_CONG and QUE_CONG\n");
    pr ("*4: Share filled to this level: drop if SE_LARGE and QUE_LARGE\n");
    pr ("QUE_ACT    = QueSize>QLIMIT_QUEUE_ACT\n");
    pr ("QUE_CONG   = QueSize>QLIMIT_QUEUE_CONG\n");
    pr ("QUE_LARGE  = QueSize>QUE_DYN_WM\n");
    pr ("SE_CONG    = SeSize >QLIMIT_SE_CONG\n");
    pr ("SE_LARGE   = SeSize >SE_DYN_WM\n");
    pr ("\n");
    pr ("SE_DYN_WM  = QLIMIT_SHR_CTOP / (Number of ses using more that QLIMIT_QUEUE_CONG)\n");
    pr ("QUE_DYN_WM = SE_DYN_WM / (Number of queues on se using more QLIMIT_QUEUE_CONG)\n");

    pr ("\nQueues hit by queue limitation:\n");
    for (q=0; q<GAZ_CORE_QUEUE_CNT; q++) {
        JR2_WR (VTSS_XQS_SYSTEM_MAP_CFG_CFG, q);
        JR2_RD(VTSS_XQS_QLIMIT_QUEUE_QUEUE_SIZE(0), &qinf);
        u32 killed = VTSS_X_XQS_QLIMIT_QUEUE_QUEUE_SIZE_QUEUE_KILLED(qinf);
        u32 qsz    = VTSS_X_XQS_QLIMIT_QUEUE_QUEUE_SIZE_QUEUE_SIZE(qinf);

        if (killed || qsz) {
            pr ("%5u --> %2u, Prio %1u. Killed:%1u CurSize:%u\n", q, q/64/8, q%8, killed, qsz);
        }
    }

    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_JAGUAR_2_CE && !defined(VTSS_ARCH_SERVAL_T) */

/* - Debug print --------------------------------------------------- */

#define JR_DEBUG_MAC(pr, addr, i, name) vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_MAC_CFG_STATUS_MAC_##addr, i, "MAC_"name)
#define JR_DEBUG_PCS(pr, addr, i, name) vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_##addr, i, "PCS_"name)
#define JR_DEBUG_PCS_XAUI(pr, addr, i, name) vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_DEV10G_PCS_XAUI_##addr, i, "PCS_"name)
#define JR_DEBUG_10G_MAC(pr, addr, i, name) vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_DEV10G_MAC_CFG_STATUS_MAC_##addr, i, "MAC_"name)
#define JR_DEBUG_FX100(pr, addr, i, name) vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_PCS_FX100_##addr, i, name)
#define JR_DEBUG_HSIO(pr, addr, name) JR2_DEBUG_REG_NAME(pr, HSIO, addr, name)

static vtss_rc jr2_debug_chip_port(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info,
                                   vtss_port_no_t port_no)
{
    u32  tgt, i, inst, type, port = VTSS_CHIP_PORT(port_no);
    char buf[32];

    VTSS_RC(jr2_port_inst_get(vtss_state, port_no, &tgt, &inst, &type));
    if (VTSS_PORT_IS_1G(port)) {
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt), port, "DEV_RST_CTRL");
        JR_DEBUG_MAC(pr, ENA_CFG(tgt), port, "ENA_CFG");
        JR_DEBUG_MAC(pr, MODE_CFG(tgt), port, "MODE_CFG");
        JR_DEBUG_MAC(pr, MAXLEN_CFG(tgt), port, "MAXLEN_CFG");
        JR_DEBUG_MAC(pr, TAGS_CFG(tgt), port, "TAGS_CFG");
        JR_DEBUG_PCS(pr, CFG(tgt), port, "CFG");
        JR_DEBUG_PCS(pr, MODE_CFG(tgt), port, "MODE_CFG");
        JR_DEBUG_PCS(pr, SD_CFG(tgt), port, "SD_CFG");
        JR_DEBUG_PCS(pr, ANEG_CFG(tgt), port, "ANEG_CFG");
        JR_DEBUG_PCS(pr, ANEG_STATUS(tgt), port, "ANEG_STATUS");
        JR_DEBUG_PCS(pr, LINK_STATUS(tgt), port, "LINK_STATUS");
        JR_DEBUG_FX100(pr, CONFIGURATION_PCS_FX100_CFG(tgt), port, "PCS_FX100_CFG");
        JR_DEBUG_FX100(pr, STATUS_PCS_FX100_STATUS(tgt), port, "FX100_STATUS");
    } else {
        if (port_is_in_10g_mode(vtss_state, port_no)) {
#if !defined(VTSS_ARCH_SERVAL_T)
            JR_DEBUG_PCS_XAUI(pr, CONFIGURATION_PCS_XAUI_EXT_CFG(tgt), port, "EXT_CFG");
            JR_DEBUG_PCS_XAUI(pr, CONFIGURATION_PCS_XAUI_CFG(tgt), port, "CFG");
            JR_DEBUG_PCS_XAUI(pr, CONFIGURATION_PCS_XAUI_SD_CFG(tgt), port, "SD_CFG");
            JR_DEBUG_PCS_XAUI(pr, STATUS_PCS_XAUI_RX_STATUS(tgt), port,  "XAUI_RX_STATUS");
            JR_DEBUG_PCS_XAUI(pr, STATUS_PCS_XAUI_RX_ERROR_STATUS(tgt), port, "XAUI_RX_ERROR_STATUS");
#endif /* VTSS_ARCH_SERVAL_T */
            JR_DEBUG_10G_MAC(pr, TX_MONITOR_STICKY(tgt), port, "TX_MONITOR_STICKY");
            JR_DEBUG_10G_MAC(pr, ENA_CFG(tgt), port, "ENA_CFG");
            JR_DEBUG_10G_MAC(pr, MODE_CFG(tgt), port, "MODE_CFG");
        } else {
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL(tgt), port, "DEV_RST_CTRL");
            JR_DEBUG_MAC(pr, ENA_CFG(tgt), port, "ENA_CFG");
            JR_DEBUG_MAC(pr, MODE_CFG(tgt), port, "MODE_CFG");
            JR_DEBUG_MAC(pr, MAXLEN_CFG(tgt), port, "MAXLEN_CFG");
            JR_DEBUG_MAC(pr, TAGS_CFG(tgt), port, "TAGS_CFG");
            JR_DEBUG_PCS(pr, CFG(tgt), port, "CFG");
            JR_DEBUG_PCS(pr, MODE_CFG(tgt), port, "MODE_CFG");
            JR_DEBUG_PCS(pr, SD_CFG(tgt), port, "SD_CFG");
            JR_DEBUG_PCS(pr, ANEG_CFG(tgt), port, "ANEG_CFG");
            JR_DEBUG_PCS(pr, ANEG_STATUS(tgt), port, "ANEG_STATUS");
            JR_DEBUG_PCS(pr, LINK_STATUS(tgt), port, "LINK_STATUS");
            JR_DEBUG_FX100(pr, CONFIGURATION_PCS_FX100_CFG(tgt), port, "PCS_FX100_CFG");
            JR_DEBUG_FX100(pr, STATUS_PCS_FX100_STATUS(tgt), port, "FX100_STATUS");
        }
    }
    JR2_DEBUG_REGX_NAME(pr, DSM, CFG_RX_PAUSE_CFG, port, "RX_PAUSE_CFG");
    JR2_DEBUG_REGX_NAME(pr, DSM, CFG_ETH_FC_CFG, port, "ETH_FC_CFG");
    pr("\n");

    if (VTSS_PORT_IS_10G(port)) {
        // APC status readouts:
        u32 value, p, sd, pcs;
        pr("APC status:\n");
        pr("port    gain    g.adj   ldlev   offs    agc     c       l       dfe1    dfe2    dfe3    dfe4\n");
        for (p = VTSS_PORT_10G_START; p < VTSS_CHIP_PORTS; p++) {
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 eqz_gain = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ACTVAL(value);
            u32 eqz_gain_adj = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ADJ_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 ld_lev = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_LD_LEV_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 eqz_offs = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 eqz_agc = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 eqz_c = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 eqz_l = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 dfe1 = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 dfe2 = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 dfe3 = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_ACTVAL(value);
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL(VTSS_TO_10G_APC_TGT(p)), &value);
            u32 dfe4 = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_ACTVAL(value);
            pr("%-7d %-7d %-7d %-7d %-7d %-7d %-7d %-7d %-7d %-7d %-7d %-7d\n",
               p, eqz_gain, eqz_gain_adj, ld_lev, eqz_offs, eqz_agc, eqz_c, eqz_l, dfe1, dfe2, dfe3, dfe4);
        }

        pr("\nLink status (MAC/SD/PCS):\n");
        pr("port          local_fault   remote_fault  idle_state    SD            rx_blk_lock   rx_hi_ber\n");
        for (p = VTSS_PORT_10G_START; p < VTSS_CHIP_PORTS; p++) {
            JR2_RD(VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY(VTSS_TO_DEV(p)), &value);
            JR2_RD(VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10(VTSS_TO_10G_SRD_TGT(p)), &sd);
            JR2_RD(VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS(VTSS_TO_10G_PCS_TGT(p)), &pcs);
            pr("%-13d %-13d %-13d %-13d %-13d %-13d %-13d\n",
               p,
               VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(value),
               VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(value),
               VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(value),
               VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_SDET(sd),
               VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_BLOCK_LOCK(pcs),
               VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_HI_BER(pcs));
            // Clear the stickies
            JR2_WR(VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS(VTSS_TO_10G_PCS_TGT(p)), 0xFFFFFFFF);
        }
    }

    /* Show SerDes setup if full configuration requested */
    if (!info->full) {
        return VTSS_RC_OK;
    }

    for (i = inst; i < (inst + (type == JR2_SERDES_TYPE_10G ? 4 : 1)); i++) {
        if (type == JR2_SERDES_TYPE_1G) {
            VTSS_SPRINTF(buf, "SerDes1G_%u", i);
            vtss_jr2_debug_reg_header(pr, buf);
            VTSS_RC(jr2_sd1g_read(vtss_state, 1 << i));
            JR_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_DES_CFG, "DES_CFG");
            JR_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_IB_CFG, "IB_CFG");
            JR_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_OB_CFG, "OB_CFG");
            JR_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_SER_CFG, "SER_CFG");
            JR_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, "COMMON_CFG");
            JR_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_PLL_CFG, "PLL_CFG");
            JR_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_MISC_CFG, "100FX_MISC");
            JR_DEBUG_HSIO(pr, SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS, "PLL_STATUS");
            JR_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0, "DFT_CFG0");
            JR_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1, "DFT_CFG1");
            JR_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2, "DFT_CFG2");
            JR_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_TP_CFG, "TP_CFG");
            JR_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_MISC_CFG, "MISC_CFG");
            JR_DEBUG_HSIO(pr, SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS, "DFT_STATUS");
        } else if (type == JR2_SERDES_TYPE_6G) {
            VTSS_SPRINTF(buf, "SerDes6G_%u", i);
            vtss_jr2_debug_reg_header(pr, buf);
            VTSS_RC(jr2_sd6g_read(vtss_state, 1 << i));
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_IB_CFG, "IB_CFG");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_IB_CFG1, "IB_CFG1");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, "OB_CFG");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG1, "OB_CFG1");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_SER_CFG, "SER_CFG");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, "COMMON_CFG");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, "PLL_CFG");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0, "IB_STATUS0");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1, "IB_STATUS1");
            JR_DEBUG_HSIO(pr, SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, "PLL_STATUS");
        } else {
        }
        pr("\n");
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_port(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)

{
    vtss_port_no_t port_no;
    u32            port;
    char           buf[32];

#if defined(VTSS_CALENDAR_CALC)
    vtss_calendar_t *cal = &vtss_state->port.calendar;

    // Print calendar
    if (cal->manual) {
        u32 i, port_bw[255], p_idle = 0;
        VTSS_MEMSET(port_bw, 0, sizeof(port_bw));

        pr("Manual, %s calculated, calendar of %u bytes\n", cal->dynamic ? "dynamically" : "statically", cal->len);

        for (i = 0; i < cal->len; i++) {
            u8 p = cal->cbc[i];

            if (p > p_idle) {
                p_idle = p;
            }

            pr("%2d%s", p, (i + 1) % 16 ? " " : "\n");
            port_bw[p]++;
        }

        pr("\nVD0: %u Mbps, VD1: %u Mbps, CPU0: %u Mbps, CPU1: %u Mbps, IDLE = %u Mbps\n\n",
           250 * port_bw[VTSS_CHIP_PORT_VD0],
           250 * port_bw[VTSS_CHIP_PORT_VD1],
           250 * port_bw[VTSS_CHIP_PORT_CPU_0],
           250 * port_bw[VTSS_CHIP_PORT_CPU_1],
           250 * port_bw[p_idle]);
    } else {
        pr("Auto calendar\n\n");
    }
#endif /* defined(VTSS_CALENDAR_CALC) */

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0)
            continue;
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_jr2_debug_reg_header(pr, buf);
        VTSS_RC(jr2_debug_chip_port(vtss_state, pr, info, port_no));
    } /* Port loop */
    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_port_counters(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       const vtss_debug_info_t   *const info, vtss_port_no_t port_no)
{
    u32                      i;
    char                     rx_buf[32], tx_buf[32];
    vtss_port_jr2_counters_t cnt;

    VTSS_MEMSET(&cnt, 0, sizeof(vtss_port_jr2_counters_t));
    VTSS_RC(jr2_port_counters_chip(vtss_state, port_no, &cnt, NULL, 0));

    if (port_no < vtss_state->port_count && (info->full || info->action != 3)) {
        vtss_jr2_debug_cnt(pr, "ok_bytes", "out_bytes", &cnt.rx_ok_bytes, &cnt.tx_out_bytes);
        vtss_jr2_debug_cnt(pr, "uc", "", &cnt.rx_unicast, &cnt.tx_unicast);
        vtss_jr2_debug_cnt(pr, "mc", "", &cnt.rx_multicast, &cnt.tx_multicast);
        vtss_jr2_debug_cnt(pr, "bc", "", &cnt.rx_broadcast, &cnt.tx_broadcast);
    }

    if (port_no < vtss_state->port_count && (info->full || info->action == 2)) {
        vtss_jr2_debug_cnt(pr, "pause", "", &cnt.rx_pause, &cnt.tx_pause);
        vtss_jr2_debug_cnt(pr, "64", "", &cnt.rx_size64, &cnt.tx_size64);
        vtss_jr2_debug_cnt(pr, "65_127", "", &cnt.rx_size65_127, &cnt.tx_size65_127);
        vtss_jr2_debug_cnt(pr, "128_255", "", &cnt.rx_size128_255, &cnt.tx_size128_255);
        vtss_jr2_debug_cnt(pr, "256_511", "", &cnt.rx_size256_511, &cnt.tx_size256_511);
        vtss_jr2_debug_cnt(pr, "512_1023", "", &cnt.rx_size512_1023, &cnt.tx_size512_1023);
        vtss_jr2_debug_cnt(pr, "1024_1526", "", &cnt.rx_size1024_1518, &cnt.tx_size1024_1518);
        vtss_jr2_debug_cnt(pr, "jumbo", "", &cnt.rx_size1519_max, &cnt.tx_size1519_max);
        vtss_jr2_debug_cnt(pr, "crc", NULL, &cnt.rx_crc_err, NULL);
        vtss_jr2_debug_cnt(pr, "undersize", "multi_coll", &cnt.rx_undersize, &cnt.tx_multi_coll);
        vtss_jr2_debug_cnt(pr, "fragments", "late_coll", &cnt.rx_fragments, &cnt.tx_late_coll);
        vtss_jr2_debug_cnt(pr, "inr_len_err", "xcoll", &cnt.rx_in_range_len_err, &cnt.tx_xcoll);
        vtss_jr2_debug_cnt(pr, "oor_len_err", "defer", &cnt.rx_out_of_range_len_err, &cnt.tx_defer);
        vtss_jr2_debug_cnt(pr, "oversize", "xdefer", &cnt.rx_oversize, &cnt.tx_xdefer);
        vtss_jr2_debug_cnt(pr, "jabbers", "backoff1", &cnt.rx_jabbers, &cnt.tx_backoff1);
    }

    if (info->full || info->action == 1 || info->action == 3) {
        vtss_jr2_debug_cnt(pr, "local_drops", NULL, &cnt.rx_local_drops, NULL);
        vtss_jr2_debug_cnt(pr, "policer_drops", "queue_drops", &cnt.rx_policer_drops, &cnt.tx_queue_drops);

        for (i = 0; i < VTSS_PRIOS; i++) {
            VTSS_SPRINTF(rx_buf, "class_%u", i);
            VTSS_SPRINTF(tx_buf, "green_%u", i);
            vtss_jr2_debug_cnt(pr, rx_buf, tx_buf, &cnt.rx_class[i], &cnt.tx_green_class[i]);
        }
        for (i = 0; i < VTSS_PRIOS; i++) {
            VTSS_SPRINTF(tx_buf, "yellow_%u", i);
            vtss_jr2_debug_cnt(pr, NULL, tx_buf, NULL, &cnt.tx_yellow_class[i]);
        }
        for (i = 0; i < VTSS_PRIOS; i++) {
            VTSS_SPRINTF(tx_buf, "green_drops_%u", i);
            vtss_jr2_debug_cnt(pr, NULL, tx_buf, NULL, &cnt.tx_green_drops[i]);
        }
        for (i = 0; i < VTSS_PRIOS; i++) {
            VTSS_SPRINTF(tx_buf, "yellow_drops_%u", i);
            vtss_jr2_debug_cnt(pr, NULL, tx_buf, NULL, &cnt.tx_yellow_drops[i]);
        }
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_port_cnt(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455} */ // Due to VTSS_EXIT_ENTER
    vtss_port_no_t port_no;
    BOOL           cpu_port = (info->action == 1);

    if (info->has_action && info->action == 0) {
        pr("Port counter actions:\n");
        pr("0: Show actions\n");
        pr("1: Show CPU and VD counters\n");
        pr("2: Show MAC counters only\n");
        pr("3: Show QS counters only\n");
        return VTSS_RC_OK;
    }

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count + 4; port_no++) {
        if (port_no < vtss_state->port_count) {
            if (info->port_list[port_no] == 0 || cpu_port)
                continue;
            pr("Counters for port: %u (chip_port: %u):\n\n", port_no, VTSS_CHIP_PORT(port_no));
        } else {
            if (!cpu_port)
                continue;
            pr("Counters for chip_port: %u:\n\n", VTSS_CHIP_PORT_CPU + port_no - vtss_state->port_count);
        }
        VTSS_EXIT_ENTER();
        (void)jr2_debug_port_counters(vtss_state, pr, info, port_no);
    }
    return VTSS_RC_OK;
}

static char *jr2_chip_port_to_str(vtss_state_t *vtss_state, vtss_phys_port_no_t chip_port, char *buf)
{
    vtss_port_no_t port_no;

    switch (chip_port) {
    case -1:
       // Special case just to get the print function print something special
       VTSS_STRCPY(buf, "SHARED");
       break;

    case VTSS_CHIP_PORT_CPU_0:
       VTSS_STRCPY(buf, "CPU0");
       break;

    case VTSS_CHIP_PORT_CPU_1:
       VTSS_STRCPY(buf, "CPU1");
       break;

    case VTSS_CHIP_PORT_VD0:
       VTSS_STRCPY(buf, "VD0");
       break;

    case VTSS_CHIP_PORT_VD1:
        VTSS_STRCPY(buf, "VD1");
        break;

    default:
        port_no = vtss_cmn_chip_to_logical_port(vtss_state, vtss_state->chip_no, chip_port);
        if (port_no != VTSS_PORT_NO_NONE) {
            VTSS_SPRINTF(buf, "%u", port_no);
        } else {
            // Port is not in port map. Odd.
            VTSS_E("chip_port = %u not in port map", chip_port);
            VTSS_STRCPY(buf, "N/A");
        }

        break;
    }

    return buf;
}

static const char *jr2_qsys_resource_to_str(u32 resource)
{
    switch (resource) {
    case 0:
        return "SRC-MEM";

    case 1:
        return "SRC-REF";

    case 2:
        return "DST-MEM";

    case 3:
        return "DST-REF";

    default:
        VTSS_E("Invalid resource (%u)", resource);
        break;
    }

    return "INVALID";
}

static void jr2_debug_qres_print(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 idx, vtss_phys_port_no_t chip_port, u32 resource, u32 prio, u32 val)
{
    char buf[20];

    pr("%4u %-8s %7s %9d %4u %10u\n", idx, jr2_qsys_resource_to_str(resource), jr2_chip_port_to_str(vtss_state, chip_port, buf), chip_port, prio, val);
}

vtss_rc vtss_jr2_port_debug_qres(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, BOOL res_stat_cur)
{
    vtss_phys_port_no_t chip_port;
    u32                 resource, resource_base, port_base, idx, prio, val, addr;

    pr("\nQSYS Resource table (QRES:RES_CTRL[idx]:RES_STAT%s)\n", res_stat_cur ? "_CUR" : "");
    pr("Idx  Resource Port No Chip Port Prio Value\n");
    pr("---- -------- ------- --------- ---- ----------\n");

    // Print shared SRC-MEM, because up-flows with CL_DP == 1 are counted here
    // and not in the masquerade port counters.
    addr = res_stat_cur ? VTSS_QRES_RES_CTRL_RES_STAT_CUR(511) : VTSS_QRES_RES_CTRL_RES_STAT(511);
    JR2_RD(addr, &val);
    jr2_debug_qres_print(vtss_state, pr, 511, -1, 0, 7, val);

    for (resource = 0; resource < 4; resource++) {
        resource_base = resource * 1024;
        for (chip_port = 0; chip_port < VTSS_CHIP_PORTS_ALL; chip_port++) {
            port_base = resource_base + chip_port * VTSS_PRIOS;
            for (prio = 0; prio < VTSS_PRIOS; prio++) {
                idx = port_base + prio;
                addr = res_stat_cur ? VTSS_QRES_RES_CTRL_RES_STAT_CUR(idx) : VTSS_QRES_RES_CTRL_RES_STAT(idx);
                JR2_RD(addr, &val);
                if (val) {
                    // Only print non-zero values or we will be flooded.
                    jr2_debug_qres_print(vtss_state, pr, idx, chip_port, resource, prio, val);
                }
            }
        }
    }

    pr("\n");

    return VTSS_RC_OK;
}

static char *fa_kr_aneg_sm(u32 reg)
{
    switch (reg) {
    case 0:  return "AN_ENABLE(0)";
    case 1:  return "XMI_DISABLE(1)";
    case 2:  return "ABILITY_DET(2)";
    case 3:  return "ACK_DET(3)";
    case 4:  return "COMPLETE_ACK(4)";
    case 5:  return "TRAIN(5)";
    case 6:  return "AN_GOOD_CHK(6)";
    case 7:  return "AN_GOOD(7)";
    case 8:  return "RATE_DET(8)";
    case 11: return "LINK_STAT_CHK(11)";
    case 12: return "PARLL_DET_FAULT(12)";
    case 13: return "WAIT_RATE_DONE(13)";
    case 14: return "NXTPG_WAIT(14)";
    default: return "?";
    }
}

static void print_reg_bit(const vtss_debug_printf_t pr, BOOL bt, char *name)
{
    if (bt) {
        pr("%s ",name);
    }
}

static vtss_rc jr2_debug_chip_kr(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info,
                                 vtss_port_no_t port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 dev7 = VTSS_TO_10G_KR_DEV7_TGT(port);  // ANEG
    u32 dev1 = VTSS_TO_10G_KR_DEV1_TGT(port);  // Training
    u32 xfi  = VTSS_TO_10G_XFI_TGT(port);      // KR-Control/Stickies
    u32 an_sm, aneg, pcs, tr, xfis, hist, krc, value, sd;

    if (info->has_action && info->action == 2) {
        // Restart aneg
        JR2_WRM(VTSS_KR_DEV7_KR_7X0000_KR_7X0000(dev7),
                VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART(1),
                VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART);
        pr("Aneg restarted\n");
        return VTSS_RC_OK;
    }

    if (info->has_action && info->action == 3) {
        // Restart serdes
        VTSS_RC(jr2_sd10g_cfg(vtss_state, vtss_state->port.serdes_mode[port_no],
                              vtss_state->port.current_mt[port_no], port));
        pr("Serdes reconfigured\n");
        return VTSS_RC_OK;
    }

    if (info->has_action && info->action == 4) {
        // Restart serdes
        VTSS_RC(jr2_sd10g_cfg(vtss_state, VTSS_SERDES_MODE_SGMII,
                              vtss_state->port.current_mt[port_no], port));

        VTSS_RC(jr2_sd10g_cfg(vtss_state, vtss_state->port.serdes_mode[port_no],
                              vtss_state->port.current_mt[port_no], port));
        pr("Serdes reconfigured 1G->10G\n");
        return VTSS_RC_OK;
    }
    if (info->has_action && info->action == 5) {
        JR2_WRM(VTSS_KR_DEV1_TR_CFG1_TR_CFG1(dev1),
                VTSS_BIT(6),
                VTSS_BIT(6));
        pr("Parallel detect disabled\n");
    }

    JR2_RD(VTSS_KR_DEV7_AN_SM_AN_SM(dev7), &an_sm);
    JR2_RD(VTSS_KR_DEV7_AN_HIST_AN_HIST(dev7), &hist);
    JR2_RD(VTSS_KR_DEV7_KR_7X0001_KR_7X0001(dev7), &aneg);
    JR2_RD(VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS(VTSS_TO_10G_PCS_TGT(port)), &pcs);
    JR2_RD(VTSS_XFI_SHELL_XFI_CONTROL_XFI_STATUS(xfi), &xfis);
    JR2_RD(VTSS_KR_DEV1_KR_1X0097_KR_1X0097(dev1), &tr);
    JR2_RD(VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(xfi), &krc);

    pr("an_sm              :%s\n", fa_kr_aneg_sm(VTSS_X_KR_DEV7_AN_SM_AN_SM_AN_SM(an_sm)));
    pr("an_complete        :%d\n", VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_AN_COMPLETE(aneg));
    pr("aneg_active:       :%d\n", VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_STATUS_ANEG_ACTIVE_STATUS(xfis));
    pr("an_hist            :0x%x  ", VTSS_X_KR_DEV7_AN_HIST_AN_HIST_AN_SM_HIST(hist));
    if (hist > 0) {
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,0,1), "AN_ENA(0)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,1,1), "XMI_DIS(1)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,2,1), "ABI_DET(2)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,3,1), "ACK_DET(3)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,4,1), "LNK_CHK(4)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,5,1), "COMPL_ACK(5)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,6,1), "AN_GOOD_CHK(6)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,7,1), "PRL_DET_FAUL(7)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,8,1), "AN_GOOD(8)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,9,1), "NXT_PG_WAIT(9)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,10,1),"RATE_DET(10)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,11,1),"TRAIN(11)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,12,1),"RSRV(12)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,13,1),"RSRV(13)");
        print_reg_bit(pr, VTSS_EXTRACT_BITFIELD(hist,14,1),"NPRX(14)");
    }
    pr("\n");
    pr("tr_rcvr_rdy:       :%d\n", VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_RCVR_RDY(tr));
    pr("tr_fail:           :%d\n", VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_TR_FAIL(tr));
    pr("kr_control:        :0x%x\n", krc);

    JR2_WRM(VTSS_KR_DEV7_AN_CFG0_AN_CFG0(dev7),
            VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR(1),
            VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR);
    JR2_WRM(VTSS_KR_DEV7_AN_CFG0_AN_CFG0(dev7),
            VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR(0),
            VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR);

    JR2_RD(VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY(VTSS_TO_DEV(port)), &value);
    pr("\nLink status: %d:\n", (value == 2));
    pr("port          local_fault   remote_fault  idle_state    SD            rx_blk_lock   rx_hi_ber\n");
    JR2_RD(VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10(VTSS_TO_10G_SRD_TGT(port)), &sd);
    JR2_RD(VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS(VTSS_TO_10G_PCS_TGT(port)), &pcs);
    pr("%-13d %-13d %-13d %-13d %-13d %-13d %-13d\n",
       port,
       VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(value),
       VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(value),
       VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(value),
       VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_SDET(sd),
       VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_BLOCK_LOCK(pcs),
       VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_HI_BER(pcs));
    // Clear the stickies
    JR2_WR(VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS(VTSS_TO_10G_PCS_TGT(port)), 0xFFFFFFFF);

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_kr(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info)

{
    vtss_port_no_t port_no;

    if (info->has_action && info->action == 0) {
        pr("Serdes actions:\n");
        pr("0: Show actions\n");
        pr("1: Dump kr\n");
        pr("2: Restart aneg\n");
        pr("3: Reconfigure serdes\n");
        pr("4: Reconfigure serdes to 1G then to 10G\n");
        pr("5: Disable parallel detect\n");
        return VTSS_RC_OK;
    }
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0)
            continue;
        if (!vtss_state->port.kr_conf[port_no].aneg.enable)
            continue;

        VTSS_RC(jr2_debug_chip_kr(vtss_state, pr, info, port_no));
    } /* Port loop */


    return VTSS_RC_OK;
}

static void jr2_debug_wm_dump(const vtss_debug_printf_t pr, const char *reg_name, u32 *value, u32 i, u32 multiplier)
{
    u32 q;
    pr("%-25s", reg_name);
    for (q = 0; q < i; q++) {
        pr("%10u ", wm_dec(value[q]) * multiplier);
    }
    pr("\n");
}




static vtss_rc jr2_debug_wm(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t  *const info)

{
    u32 port_no, value, q, dp, port = 0;
    u32 q_id[8];
    u32 dp_id[8];
    u32 p_val1 = 0, p_val2 = 0, p_val3 = 0, p_val4 = 0, p_val5 = 0;
    u32 q_val1[8], q_val2[8], q_val3[8], q_val4[8], q_val5[8];
    u32 c_val1[8], c_val2[8], c_val3[8], c_val4[8], c_val5[8];
    u32 dp_val1[4], dp_val2[4], dp_val3[4], dp_val4[4], dp_val5[4];
    int group, queue, dpl;


#if defined(VTSS_ARCH_JAGUAR_2_CE) && !defined(VTSS_ARCH_SERVAL_T)
    // Show the qlimitation status instead if in use.
    if (vtss_state->init_conf.qs_conf.mode != VTSS_QS_MODE_DEFAULT) {
        return jr2_debug_wm_qlim(vtss_state, pr, info);
    }
#endif /* VTSS_ARCH_JAGUAR_2_CE && !defined(VTSS_ARCH_SERVAL_T) */

    for (q = 0; q < VTSS_PRIOS; q++) {
        q_id[q] = q;
        q_val1[q] = q_val2[q] = q_val3[q] = q_val4[q] = q_val5[q] = 0;
        c_val1[q] = c_val2[q] = c_val3[q] = c_val4[q] = c_val5[q] = 0;
    }

    for (dp = 0; dp < 4; dp++) {
        if (dp < 3) {
            dp_id[dp] = dp + 1;
        } else {
            dp_id[dp] = 0;
        }
        dp_val1[dp] = dp_val2[dp] = dp_val3[dp] = dp_val4[dp] = dp_val5[dp] = 0;
    }

    pr("General info:\n");
    pr("-------------\n");
    pr("Total Buffer           : %d bytes\n",JR2_BUFFER_MEMORY);
    pr("Total Frame References : %d\n",JR2_BUFFER_REFERENCE);
    pr("Cell size              : %d bytes\n",JR2_BUFFER_CELL_SZ);
    pr("Oversubsription factor : %d\n",BUF_OVERSUBSRIPTION_FACTOR/100);
    pr("Num of ports configured: %d (including 2 CPU ports)\n",vtss_state->port_count + 2);
    JR2_RD(VTSS_QSYS_PAUSE_CFG_PAUSE_TOT_CFG, &value);
    pr("FC Pause TOT_START     : %d bytes\n", wm_dec(VTSS_X_QSYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(value)) * JR2_BUFFER_CELL_SZ);
    pr("FC Pause TOT_STOP      : %d bytes\n", wm_dec(VTSS_X_QSYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(value)) * JR2_BUFFER_CELL_SZ);
    JR2_RD(VTSS_QSYS_PAUSE_CFG_ATOP_TOT_CFG, &value);
    pr("FC ATOP_TOT            : %d bytes\n", wm_dec(VTSS_X_QSYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(value)) * JR2_BUFFER_CELL_SZ);
    pr("\n");

    for (port_no = VTSS_PORT_NO_START; port_no < (vtss_state->port_count + 2); port_no++) {
        if (port_no >= vtss_state->port_count) { /* This is a CPU port */
            /* CPU port */
            if (!info->full)
                continue;
            if (port_no == vtss_state->port_count) {
                port = VTSS_CHIP_PORT_CPU_0;
                pr("CPU port 0 (chip port %u):\n",port);
            } else {
                port = VTSS_CHIP_PORT_CPU_1;
                pr("CPU port 1 (chip port %u):\n",port);
            }
        } else {
            if (!info->port_list[port_no]) {
                continue;
            }
            port = VTSS_CHIP_PORT(port_no);
            pr("API port %u (chip port %u):\n", port_no, port);
        }
        pr("==========================\n\n");
        pr("Flow Control:\n");
        pr("------------\n");
        JR2_RD(VTSS_DSM_CFG_ETH_PFC_CFG(port), &value);
        pr("PFC ena             : %d\n", VTSS_X_DSM_CFG_ETH_PFC_CFG_PFC_ENA(value));
        JR2_RD(VTSS_DSM_CFG_RX_PAUSE_CFG(port), &value);
        pr("FC Rx ena (standard): %d\n", (VTSS_X_DSM_CFG_RX_PAUSE_CFG_RX_PAUSE_EN(value)));
        JR2_RD(VTSS_QSYS_PAUSE_CFG_PAUSE_CFG(port), &value);
        pr("FC Tx ena (standard): %d\n", VTSS_X_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA(value));
        pr("FC Start    (Bytes) : %d\n", wm_dec(VTSS_X_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(value)) * JR2_BUFFER_CELL_SZ);
        pr("FC Stop     (Bytes) : %d\n", wm_dec(VTSS_X_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(value)) * JR2_BUFFER_CELL_SZ);
        JR2_RD(VTSS_QSYS_PAUSE_CFG_ATOP(port), &value);
        pr("FC Atop     (Bytes) : %d\n", wm_dec(VTSS_X_QSYS_PAUSE_CFG_ATOP_ATOP(value)) * JR2_BUFFER_CELL_SZ);
        pr("\n");

        /* Reserved amount for (PORT,PRIO) at index 8 * PORT + PRIO */
        for (q = 0; q < VTSS_PRIOS; q++) {
            JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q +    0)), &q_val1[q]);
            JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 1024)), &q_val2[q]);
            JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 2048)), &q_val3[q]);
            JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 3072)), &q_val4[q]);
            JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 4096)), &q_val5[q]);
        }

        jr2_debug_wm_dump(pr, "Queue level:", q_id, 8, 1);
        pr("-----------\n");
        jr2_debug_wm_dump(pr, "Qu Ingr Buf Rsrv (Bytes) :", q_val1, 8, JR2_BUFFER_CELL_SZ);
        jr2_debug_wm_dump(pr, "Qu Ingr Ref Rsrv (Frames):", q_val2, 8, 1);
        jr2_debug_wm_dump(pr, "Qu Egr Buf Rsrv  (Bytes) :", q_val3, 8, JR2_BUFFER_CELL_SZ);
        jr2_debug_wm_dump(pr, "Qu Egr Ref Rsrv  (Frames):", q_val4, 8, 1);
        jr2_debug_wm_dump(pr, "Qu Ingr PFC      (Bytes) :", q_val5, 8, JR2_BUFFER_CELL_SZ);
        pr("\n");

        /* Reserved amount for PORT at index PORT + 512 */
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port + 512 +    0)), &p_val1);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port + 512 + 1024)), &p_val2);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port + 512 + 2048)), &p_val3);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port + 512 + 3072)), &p_val4);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((port + 512 + 4096)), &p_val5);
        pr("Port level:\n");
        pr("-----------\n");
        pr("Port Ingress Buf Rsrv       (Bytes) : %u\n", wm_dec(p_val1) * JR2_BUFFER_CELL_SZ);
        pr("Port Ingress Ref Rsrv       (Frames): %u\n", wm_dec(p_val2));
        pr("Port Egress  Buf Rsrv       (Bytes) : %u\n", wm_dec(p_val3) * JR2_BUFFER_CELL_SZ);
        pr("Port Egress  Ref Rsrv       (Frames): %u\n", wm_dec(p_val4));
        pr("Port Ingress Buf Rsrv - PFC (Bytes) : %u\n", wm_dec(p_val5) * JR2_BUFFER_CELL_SZ);
        pr("\n");
    }

    pr("Shared space:\n");
    pr("=============\n\n");
    /* Maximum allowed use of the shared buffer for PRIO at index PRIO + 496 */
    for (q = 0; q < VTSS_PRIOS; q++) {
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 +    0)), &c_val1[q]);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 + 1024)), &c_val2[q]);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 + 2048)), &c_val3[q]);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 + 3072)), &c_val4[q]);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((q + 496 + 4096)), &c_val5[q]);
    }
    jr2_debug_wm_dump(pr, "QoS level:", q_id, 8, 1);
    pr("-----------\n");
    jr2_debug_wm_dump(pr, "QoS Ingr Buf       (Bytes) :", c_val1, 8, JR2_BUFFER_CELL_SZ);
    jr2_debug_wm_dump(pr, "QoS Ingr Ref       (Frames):", c_val2, 8, 1);
    jr2_debug_wm_dump(pr, "QoS Egr Buf        (Bytes) :", c_val3, 8, JR2_BUFFER_CELL_SZ);
    jr2_debug_wm_dump(pr, "QoS Egr Ref        (Frames):", c_val4, 8, 1);
    jr2_debug_wm_dump(pr, "QoS Ingr Buf - PFC (Bytes) :", c_val5, 8, JR2_BUFFER_CELL_SZ);
    pr("\n");

    /* Configure shared space for all DP levels (green:3 yellow:0-2) */
    /* Index 508: Maximum allowed use of the shared buffer for frames with DP=1 (yellow). */
    /* Index 509: Maximum allowed use of the shared buffer for frames with DP=2 (yellow). */
    /* Index 510: Maximum allowed use of the shared buffer for frames with DP=3 (yellow). */
    /* Index 511: Maximum allowed use of the shared buffer for frames with DP=0 (green). */
    for (dp = 0; dp < 4; dp++) {
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((dp + 508 +    0)), &dp_val1[dp]);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((dp + 508 + 1024)), &dp_val2[dp]);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((dp + 508 + 2048)), &dp_val3[dp]);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((dp + 508 + 3072)), &dp_val4[dp]);
        JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((dp + 508 + 4096)), &dp_val5[dp]);
    }
    jr2_debug_wm_dump(pr, "DP level:", dp_id, 4, 1);
    pr("-----------\n");
    jr2_debug_wm_dump(pr, "DP Ingr Buf        (Bytes) :", dp_val1, 4, JR2_BUFFER_CELL_SZ);
    jr2_debug_wm_dump(pr, "DP Ingr Ref        (Frames):", dp_val2, 4, 1);
    jr2_debug_wm_dump(pr, "DP Egr Buf         (Bytes) :", dp_val3, 4, JR2_BUFFER_CELL_SZ);
    jr2_debug_wm_dump(pr, "DP Egr Ref         (Frames):", dp_val4, 4, 1);
    jr2_debug_wm_dump(pr, "DP Ingr Buf - PFC  (Bytes) :", dp_val5, 4, JR2_BUFFER_CELL_SZ);
    pr("\n");

    if (info->full) {
        pr("WRED config:\n");
        pr("-----------\n");
        pr("Group Queue Dpl WM_HIGH  bytes RED_LOW  bytes RED_HIGH bytes\n");
//      xxxxx xxxxx xxx 0xxxxx xxxxxxx 0xxxxx xxxxxxx 0xxxxx xxxxxxx
        for (group = 0; group < VTSS_WRED_GROUP_CNT; group++) {
            for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
                u32 wm_high;
                JR2_RD(VTSS_QRES_RES_CTRL_RES_CFG((queue + 496 + 2048)), &wm_high); /* Shared egress high watermark for queue - common for all dpls */
                for (dpl = 0; dpl < VTSS_WRED_DPL_CNT; dpl++) {
                    JR2_RD(VTSS_QRES_RES_WRED_WRED_PROFILE((24 * group) + (8 * dpl) + queue), &value);
                    u32 wm_red_low  = VTSS_X_QRES_RES_WRED_WRED_PROFILE_WM_RED_LOW(value);
                    u32 wm_red_high = VTSS_X_QRES_RES_WRED_WRED_PROFILE_WM_RED_HIGH(value);
                    pr("%5d %5d %3d 0x%04x %7u 0x%04x %7u 0x%04x %7u\n",
                       group,
                       queue,
                       dpl + 1,
                       wm_high,
                       wm_dec(wm_high) * JR2_BUFFER_CELL_SZ, /* Convert from 176 byte chunks to bytes */
                       wm_red_low,
                       wm_red_low * 2816,                    /* Convert from 2816 byte chunks to bytes */
                       wm_red_high,
                       wm_red_high * 2816);                  /* Convert from 2816 byte chunks to bytes */
                }
            }
        }
    }
    pr("\n");

    pr("Burst capacity expected for one port (prio 7): %d bytes\n",
       wm_dec(c_val1[7]) * JR2_BUFFER_CELL_SZ  + wm_dec(p_val1) * JR2_BUFFER_CELL_SZ +
       wm_dec(p_val3) * JR2_BUFFER_CELL_SZ);

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
#if defined(VTSS_ARCH_JAGUAR_2_C)
        JR2_RD(VTSS_XQS_SYSTEM_FWD_DROP_EVENTS(port), &value);
#else
        JR2_RD(VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS(port), &value);
#endif /* VTSS_ARCH_JAGUAR_2_C */
        if (value == 0) {
            continue;
        }
        pr("Port %u (%d) have dropped frame(s)\n", port_no, port);
#if defined(VTSS_ARCH_JAGUAR_2_C)
        JR2_WR(VTSS_XQS_SYSTEM_FWD_DROP_EVENTS(port), 0xFFFFFFFF); // Clear stickies
#else
        JR2_WR(VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS(port), 0xFFFFFFFF); // Clear stickies
#endif /* VTSS_ARCH_JAGUAR_2_C */
    }

    VTSS_RC(vtss_jr2_port_debug_qres(vtss_state, pr, FALSE));
    VTSS_RC(vtss_jr2_port_debug_qres(vtss_state, pr, TRUE));

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_port_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT, jr2_debug_port, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT_CNT, jr2_debug_port_cnt, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_WM, jr2_debug_wm, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_KR, jr2_debug_kr, vtss_state, pr, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc jr2_init_ana(vtss_state_t *vtss_state)
{
    u32 port, i, j, value;
    BOOL vlan_counters = FALSE;

    /* Initialize policers */
    JR2_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG,
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_GAP_VALUE(20)  | /* GAP_VALUE = 20 : Use line-rate measurement */
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP(0xe) | /* Non-zero DPL means yellow statistics */
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT(1)  |
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT(1)   |
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT(1)    |
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT(1),
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_GAP_VALUE      |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP      |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT     |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT      |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT       |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT);

    /* Setup ANA_AC to count local drops and policer drops per port */
    JR2_WR(VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK(0),
           VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_ZERO_DST_STICKY_MASK);
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK(JR2_CNT_ANA_AC_PORT_FILTER),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(1<<0));
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK(JR2_CNT_ANA_AC_PORT_POLICER_DROPS),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(0x730)); /* count policer drops*/
    for (port = 0; port < VTSS_CHIP_PORTS_ALL; port++) {
        JR2_WR(VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG(port, JR2_CNT_ANA_AC_PORT_FILTER),
               VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_PRIO_MASK(0xff) |
               VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_FRM_TYPE(1));
        JR2_WR(VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG(port, JR2_CNT_ANA_AC_PORT_POLICER_DROPS),
               VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_PRIO_MASK(0xff) |
               VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_FRM_TYPE(1));
    }

    /* Enable overall signaling of flow control from the port policers to DSM */
    JR2_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG,
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA(1),
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA);

    /* Setup ANA_AC to count non-FCS errors per queue */
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG(JR2_CNT_ANA_AC_QUEUE_PRIO),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(0));

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    if (!vtss_state->init_conf.vlan_counters_disable) {
        vlan_counters = TRUE;
    }
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

    if (vlan_counters) {
        /* Enable VLAN counters */
        JR2_WRM_SET(VTSS_ANA_AC_PS_COMMON_MISC_CTRL, VTSS_M_ANA_AC_PS_COMMON_MISC_CTRL_USE_VID_AS_ISDX_ENA);
    }

    /* Setup ANA_AC SDX/VLAN statistics:
       - Counters (0,1,2) are byte counters (40-bit)
       - Counters (3,4,5) are frame counters (32-bit) */
    for (i = 0; i < 6; i++) {
        j = (i % 3);
        if (vlan_counters) {
            // 0/3: UC, 1/4: MC, 2/5: BC
            j = (j == 0 ? 3 : j == 1 ? 4 : 6);
        } else {
            // 0/3: Green, 1/4: Yellow, 2/5: Red
        }
        value = (1 << j);
        JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG(i),
               VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(i < 3 ? 1 : 0));
        JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK(i),
               VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(value));
    }

    /* Now, wait until initilization is complete */

    /* Await policer init */
#if defined(VTSS_ARCH_SERVAL_T)
    JR2_POLL_MASK(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG,
                  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT |
//                   VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT | // Not currently working - BJO
                   VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT  |
                   VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT);
#else

    JR2_POLL_MASK(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG,
                  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT |
#if defined(VTSS_ARCH_JAGUAR_2_B)
                   VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT |
#endif
                   VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT  |
                   VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT);
#endif // VTSS_ARCH_SERVAL_T

    return VTSS_RC_OK;
}

static vtss_rc jr2_port_init(vtss_state_t *vtss_state)
{
    u32 port;

    VTSS_RC(jr2_init_ana(vtss_state));

    /* Disable LANE alignment per default  */
    for (port = VTSS_PORT_10G_START; port < VTSS_CHIP_PORTS; port++) {
        VTSS_RC(vtss_jr2_vaui_lane_alignement(vtss_state, port, 0));
    }

#if defined(VTSS_ARCH_SERVAL_T)
    JR2_WR(VTSS_DEVCPU_GCB_PHY_PHY_CFG, 0);

    JR2_WRM(VTSS_DEVCPU_GCB_PHY_PHY_CFG,
            VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_RESET(3) |
            VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_ENA(3) |
            VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_COMMON_RESET(1),
            VTSS_M_DEVCPU_GCB_PHY_PHY_CFG_PHY_RESET |
            VTSS_M_DEVCPU_GCB_PHY_PHY_CFG_PHY_ENA |
            VTSS_M_DEVCPU_GCB_PHY_PHY_CFG_PHY_COMMON_RESET);

    // Bug in ServalT Rev. A chip. Sometime PLL is not running with correct speed. That can be detected is reading of supervisor takes less than 100ms.
    if (vtss_state->misc.chip_id.revision == 0) {
        u32 val, msec=0;
        while(1) {
            JR2_RD(VTSS_DEVCPU_GCB_PHY_PHY_STAT, &val);
            VTSS_MSLEEP(1);

            if (VTSS_X_DEVCPU_GCB_PHY_PHY_STAT_SUPERVISOR_COMPLETE(val) || (msec > 200)) {
                if (msec < 100) {
                    VTSS_E("---------------------> PHYs NOT working, please power cycle the board (Waited %d ms for Phy supervisor) <--------------------------\n",msec);
                }
                break;
            }
            msec++;
        }
    }
#endif /* VTSS_ARCH_SERVAL_T */

    /* Disable all Serdes instances (to save power) */
    for (port = VTSS_PORT_10G_START; port < VTSS_CHIP_PORTS; port++) {
//        VTSS_RC(jr2_sd10g_cfg(vtss_state, VTSS_SERDES_MODE_DISABLE, port));
    }
#if defined(VTSS_ARCH_SERVAL_T)
    VTSS_RC(jr2_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_DISABLE, 0x3));  // 2 * 6G - From DS1185-Serval-T_port_conf.xlsx
    VTSS_RC(jr2_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_DISABLE, 0x1F)); // 5 * 1G - From DS1185-Serval-T_port_conf.xlsx
#else
    VTSS_RC(jr2_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_DISABLE, 0xFFFFFF));
    VTSS_RC(jr2_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_DISABLE, 0xFF));
#endif

    // Gotta disable ingress and egress queue limitation, because directed
    // frames transmitted from the CPU could cause the feature to wrongly
    // think the queue has reached its limit after a link down-up.
#if defined(VTSS_ARCH_JAGUAR_2_B)
#elif defined(VTSS_ARCH_SERVAL_T)
     for (port = 0; port < VTSS_CHIP_PORTS_ALL; port++) {
        JR2_WRM_SET(VTSS_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG(port),
                    VTSS_M_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_IGR_DIS |
                    VTSS_M_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_EGR_DIS);
    }
#else
     for (port = 0; port < VTSS_CHIP_PORTS_ALL; port++) {
        JR2_WRM_SET(VTSS_XQS_QLIMIT_PORT_QLIMIT_DIS_CFG(port),
                    VTSS_M_XQS_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_IGR_DIS |
                    VTSS_M_XQS_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_EGR_DIS);
    }
#endif /* various archs */

    // Count QS drops at egress port
#if defined(VTSS_ARCH_SERVAL_T)
    JR2_WR(VTSS_QFWD_SYSTEM_STAT_CNT_CFG, VTSS_F_QFWD_SYSTEM_STAT_CNT_CFG_DROP_COUNT_EGRESS(1));
#else
    JR2_WR(VTSS_XQS_SYSTEM_STAT_CNT_CFG, VTSS_F_XQS_SYSTEM_STAT_CNT_CFG_DROP_COUNT_EGRESS(1));
#endif

    // Make sure the ports are not VStaX aware, because that will cause the
    // switch to move a possible VStaX header from the frame into the IFH.
    // This is not NPI-port compatible.
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        JR2_WRM(VTSS_ASM_CFG_PORT_CFG(port),
                VTSS_F_ASM_CFG_PORT_CFG_VSTAX2_AWR_ENA(0),
                VTSS_M_ASM_CFG_PORT_CFG_VSTAX2_AWR_ENA);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_port_state_t *state = &vtss_state->port;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->miim_read = jr2_miim_read;
        state->miim_write = jr2_miim_write;
        state->mmd_read = jr2_mmd_read;
        state->mmd_read_inc = jr2_mmd_read_inc;
        state->mmd_write = jr2_mmd_write;
        state->conf_get = jr2_port_conf_get;
        state->conf_set = jr2_port_conf_set;
        state->clause_37_status_get = jr2_port_clause_37_status_get;
        state->clause_37_control_get = jr2_port_clause_37_control_get;
        state->clause_37_control_set = jr2_port_clause_37_control_set;
#if defined( VTSS_FEATURE_PORT_KR)
        state->kr_conf_set = jr2_port_kr_conf_set;
        state->kr_status = jr2_port_kr_status;
        state->kr_fec_set = jr2_port_kr_fec_set;
#endif /*  VTSS_FEATURE_PORT_KR */
        state->status_get = jr2_port_status_get;
        state->counters_update = jr2_port_counters_update;
        state->counters_clear = jr2_port_counters_clear;
        state->counters_get = jr2_port_counters_get;
        state->basic_counters_get = jr2_port_basic_counters_get;
        state->ifh_set = jr2_port_ifh_set;
        state->forward_set = jr2_port_forward_set;
        state->test_conf_set = jr2_port_test_conf_set;

        /* SYNCE features */
#if defined(VTSS_FEATURE_SYNCE)
        vtss_state->synce.clock_out_set = jr2_synce_clock_out_set;
        vtss_state->synce.clock_in_set = jr2_synce_clock_in_set;
        vtss_state->synce.station_clk_out_set = jr2_synce_station_clk_out_set;
#endif /* VTSS_FEATURE_SYNCE */
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(jr2_port_init(vtss_state));
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        if (!vtss_state->warm_start_cur) {
#if defined(VTSS_ARCH_JAGUAR_2_CE) && !defined(VTSS_ARCH_SERVAL_T)
            if (vtss_state->init_conf.qs_conf.mode == VTSS_QS_MODE_DEFAULT) {
                VTSS_RC(jr2_port_buf_conf_set(vtss_state));
            } else {
                VTSS_RC(jr2_port_buf_qlim_set(vtss_state));
            }
#else
            VTSS_RC(jr2_port_buf_conf_set(vtss_state));
#endif /* VTSS_ARCH_JAGUAR_2_CE && !defined(VTSS_ARCH_SERVAL_T) */
        }

        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_JAGUAR_2 */
