// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"
#if defined(VTSS_FEATURE_PORT_CONTROL)

/* - Port mapping -------------------------------------------------- */

/* Get port map */
vtss_rc vtss_port_map_get(const vtss_inst_t  inst,
                          vtss_port_map_t    port_map[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_port_no_t port_no;
    vtss_rc        rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)
            port_map[port_no] = vtss_state->port.map[port_no];
    }
    VTSS_EXIT();
    VTSS_D("exit");

    return rc;
}

/* Set port map */
vtss_rc vtss_port_map_set(const vtss_inst_t      inst,
                          const vtss_port_map_t  port_map[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t    *vtss_state;
    vtss_port_no_t  port_no;
    vtss_rc         rc;
    vtss_port_map_t *pmap;

    VTSS_D("enter");
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
            pmap = &vtss_state->port.map[port_no];
            *pmap = port_map[port_no];

            /* For single chip targets, the chip_no is set to zero */
            if (vtss_state->chip_count < 2) {
                pmap->chip_no = 0;
                pmap->miim_chip_no = 0;
            }

            /* Port numbers greater than or equal to the first unmapped port are ignored */
            if (port_map[port_no].chip_port < 0 && port_no < vtss_state->port_count)
                vtss_state->port_count = port_no;
        }

#if defined(VTSS_FEATURE_LAYER2)
        /* Initialize PGID table */
        {
            u32               pgid;
            vtss_pgid_entry_t *pgid_entry;

            /* The first entries are reserved for forwarding to single port (unicast) */
            for (pgid = 0; pgid < vtss_state->port_count; pgid++) {
                pgid_entry = &vtss_state->l2.pgid_table[pgid];
                pgid_entry->member[pgid] = 1;
                pgid_entry->references = 1;
            }

            /* Next entry is reserved for dropping */
            vtss_state->l2.pgid_drop = pgid;
            vtss_state->l2.pgid_table[pgid].references = 1;

            /* Next entry is reserved for flooding */
            pgid++;
            vtss_state->l2.pgid_flood = pgid;
            pgid_entry = &vtss_state->l2.pgid_table[pgid];
            pgid_entry->references = 1;
            for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
                pgid_entry->member[port_no] = 1;
        }
#endif /* VTSS_FEATURE_LAYER2 */
        rc = VTSS_FUNC_0(port.map_set);
#if defined(VTSS_FEATURE_LAYER2)
        if (rc == VTSS_RC_OK) /* Update destination masks */
            rc = vtss_update_masks(vtss_state, 0, 1, 0);
#endif /* VTSS_FEATURE_LAYER2 */
    }
    VTSS_D("exit");

    return rc;
}

/* - Port configuration -------------------------------------------- */

vtss_rc vtss_port_clause_37_control_set(const vtss_inst_t                    inst,
                                        const vtss_port_no_t                 port_no,
                                        const vtss_port_clause_37_control_t  *const control)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->port.clause_37[port_no] = *control;
        rc = VTSS_FUNC_COLD(port.clause_37_control_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_clause_37_control_get(const vtss_inst_t              inst,
                                        const vtss_port_no_t           port_no,
                                        vtss_port_clause_37_control_t  *const control)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *control = vtss_state->port.clause_37[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_conf_get(const vtss_inst_t     inst,
                           const vtss_port_no_t  port_no,
                           vtss_port_conf_t      *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *conf = vtss_state->port.conf[port_no];
    VTSS_EXIT();
    return rc;
}

// Internal port configuration set function
vtss_rc vtss_port_conf_set_private(vtss_state_t           *vtss_state,
                                   const vtss_port_no_t   port_no,
                                   const vtss_port_conf_t *const conf)
{
    vtss_rc          rc;
#if defined(VTSS_FEATURE_AFI_SWC)
    BOOL             afi_link;
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

    vtss_state->port.conf[port_no] = *conf;

    if (!vtss_state->port.conf_set_called[port_no]) {
        // Initially, the port's state is down in S/W, but not in H/W. The very
        // first time vtss_port_conf_set() is called, we must also set the port
        // state down in H/W or we might get flush errors if conf->power_down
        // is false and a lot of traffic wants to go out on the port we are
        // currently powering up.
        (void)vtss_update_masks(vtss_state, 1, 0, 1);
    }

#if defined(VTSS_FEATURE_AFI_SWC)
    // Pause all AFI-generated frames ingressing and egressing this port.
    // This must be done prior to actually reconfiguring the port, so that it
    // can be flushed if necessary.
    afi_link   = FALSE;
    VTSS_I("Stopping AFI on port_no %u", port_no);
    (void)VTSS_FUNC(afi.link_state_change, port_no, &afi_link);
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

    if ((rc = VTSS_FUNC_COLD(port.conf_set, port_no)) == VTSS_RC_OK) {
        vtss_state->port.conf_set_called[port_no] = TRUE;
    }

#if defined(VTSS_FEATURE_AFI_SWC)
    // Resume AFI-generated frames on this port if it had link prior to calling
    // this function. Link change is only controlled by vtss_port_state_set().
    if (afi_link) {
        VTSS_I("Resuming AFI on port_no %u", port_no);
        (void)VTSS_FUNC(afi.link_state_change, port_no, &afi_link);
    }
#endif /* defined(VTSS_FEATURE_AFI_SWC) */
    return rc;
}

vtss_rc vtss_port_conf_set(const vtss_inst_t       inst,
                           const vtss_port_no_t    port_no,
                           const vtss_port_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_I("port_no: %u, power-down = %u", port_no, conf->power_down);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_state->port.conf_set_called[port_no] &&
            VTSS_MEMCMP(&vtss_state->port.conf[port_no], conf, sizeof(*conf)) == 0) {
            // Not first time and conf hasn't changed. Nothing to do.
            VTSS_I("port_no: %u - conf unchanged, skipping set", port_no);
        } else {
            rc = vtss_port_conf_set_private(vtss_state, port_no, conf);
        }
    }
    VTSS_EXIT();
    VTSS_I("Exit(port_no = %u, rc = %d)", port_no, rc);
    return rc;
}

#if defined(VTSS_FEATURE_PORT_IFH)
vtss_rc vtss_port_ifh_conf_set(const vtss_inst_t       inst,
                               const vtss_port_no_t    port_no,
                               const vtss_port_ifh_t  *const conf)
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t npi_port = VTSS_PORT_NO_NONE;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_PACKET)
        if (vtss_state->packet.npi_conf.enable) {
            npi_port = vtss_state->packet.npi_conf.port_no;
        }
#endif
        if (port_no == npi_port) {
            rc = VTSS_RC_ERROR;
        } else {
            vtss_state->port.ifh_conf[port_no] = *conf;
            rc = VTSS_FUNC_COLD(port.ifh_set, port_no);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_ifh_conf_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_port_ifh_t      *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->port.ifh_conf[port_no];
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_PORT_IFH */

/* - Port status --------------------------------------------------- */
static vtss_rc vtss_port_usxgmii_status_get(vtss_state_t         *vtss_state,
                                            const vtss_port_no_t port_no,
                                            vtss_port_status_t   *const status)
{
    vtss_rc                       rc;
    vtss_port_clause_37_status_t  clause_37_status;

    VTSS_N("port_no: %u", port_no);
    VTSS_MEMSET(&clause_37_status, 0, sizeof(clause_37_status));
    if ((rc = VTSS_FUNC(port.clause_37_status_get, port_no, &clause_37_status)) != VTSS_RC_OK) {
        return rc;
    }
    status->link_down = (clause_37_status.link ? 0 : 1);
    status->aneg_complete = clause_37_status.autoneg.complete;
    status->link = clause_37_status.autoneg.partner.usxgmii.link;
    status->fdx = clause_37_status.autoneg.partner.usxgmii.fdx;
    status->speed = clause_37_status.autoneg.partner.usxgmii.speed;

    return rc;
}

static vtss_rc vtss_port_clause_37_status_get(vtss_state_t         *vtss_state,
                                              const vtss_port_no_t port_no,
                                              vtss_port_status_t   *const status)
{
    vtss_rc                       rc;
    vtss_port_clause_37_status_t  clause_37_status;
    vtss_port_clause_37_control_t *control;
    vtss_port_clause_37_adv_t     *adv, *lp;
    VTSS_N("port_no: %u", port_no);
    VTSS_MEMSET(&clause_37_status, 0, sizeof(clause_37_status)); /* Please Lint */
    if ((rc = VTSS_FUNC(port.clause_37_status_get, port_no, &clause_37_status)) != VTSS_RC_OK)
        return rc;
    status->link_down = (clause_37_status.link ? 0 : 1);
    status->aneg_complete = clause_37_status.autoneg.complete;

    if (status->link_down) {
        /* Link has been down, so get the current status */
        if ((rc = VTSS_FUNC(port.clause_37_status_get, port_no,
                            &clause_37_status)) != VTSS_RC_OK)
            return rc;
        status->link = clause_37_status.link;
    } else {
        /* Link is still up */
        status->link = 1;
    }
    /* Link is down */
    if (status->link == 0)
        return VTSS_RC_OK;

    /* Link is up */
    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
        /* The SGMII aneg status is a status from SFP-Phy on the copper side */
        if (clause_37_status.autoneg.complete) {
            if (clause_37_status.autoneg.partner.sgmii.speed_1G) {
                status->speed = VTSS_SPEED_1G;
            } else if (clause_37_status.autoneg.partner.sgmii.speed_100M) {
                status->speed = VTSS_SPEED_100M;
            } else {
                status->speed = VTSS_SPEED_10M;
            }
            status->fdx = clause_37_status.autoneg.partner.sgmii.fdx;
            /* Flow control is not supported by SGMII aneg. */
            status->aneg.obey_pause = 0;
            status->aneg.generate_pause = 0;
        } else {
            status->link = 0;
        }
    } else {
        control = &vtss_state->port.clause_37[port_no];
        if (control->enable) {
            /* Auto-negotiation enabled */
            adv = &control->advertisement;
            lp = &clause_37_status.autoneg.partner.cl37;
            if (clause_37_status.autoneg.complete) {
                /* Speed and duplex mode auto negotiation result */
                if (adv->fdx && lp->fdx) {
                    status->fdx = 1;
                } else if (adv->hdx && lp->hdx) {
                    status->fdx = 0;
                } else
                    status->link = 0;

                /* Flow control auto negotiation result */
                status->aneg.obey_pause =
                    (adv->symmetric_pause &&
                     (lp->symmetric_pause ||
                      (adv->asymmetric_pause && lp->asymmetric_pause)) ? 1 : 0);
                status->aneg.generate_pause =
                    (lp->symmetric_pause &&
                     (adv->symmetric_pause ||
                      (adv->asymmetric_pause && lp->asymmetric_pause)) ? 1 : 0);

                /* Remote fault */
                if (lp->remote_fault != VTSS_PORT_CLAUSE_37_RF_LINK_OK)
                    status->remote_fault = 1;

                /* The speed is fixed */
                status->speed = vtss_state->port.conf[port_no].speed;
            } else {
                /* Autoneg says that the link partner is not OK */
                status->link = 0;
            }
        } else {
            /* Forced speed */
            status->speed = vtss_state->port.conf[port_no].speed;
            status->fdx = 1;
        }
    }

    return VTSS_RC_OK;

}

vtss_rc vtss_port_status_get(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             vtss_port_status_t    *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("port_no: %u", port_no);

    /* Initialize status */
    VTSS_MEMSET(status, 0, sizeof(*status));
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        switch (vtss_state->port.conf[port_no].if_type) {
            case VTSS_PORT_INTERFACE_RGMII:
            case VTSS_PORT_INTERFACE_RGMII_ID:
            case VTSS_PORT_INTERFACE_RGMII_RXID:
            case VTSS_PORT_INTERFACE_RGMII_TXID:
            case VTSS_PORT_INTERFACE_SGMII:
            case VTSS_PORT_INTERFACE_SGMII_2G5:
            case VTSS_PORT_INTERFACE_QSGMII:
                // PHY status
                break;
            case VTSS_PORT_INTERFACE_SERDES:
            case VTSS_PORT_INTERFACE_SGMII_CISCO:
                rc = vtss_port_clause_37_status_get(vtss_state, port_no, status);
                break;
            case VTSS_PORT_INTERFACE_SXGMII:
            case VTSS_PORT_INTERFACE_DXGMII_5G:
            case VTSS_PORT_INTERFACE_DXGMII_10G:
            case VTSS_PORT_INTERFACE_QXGMII:
            case VTSS_PORT_INTERFACE_USGMII:
                rc = vtss_port_usxgmii_status_get(vtss_state, port_no, status);
                break;
            default:
                rc = VTSS_FUNC(port.status_get, port_no, status);
                break;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_port_counters_update(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        rc = VTSS_FUNC(port.counters_update, port_no);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_counters_clear(const vtss_inst_t    inst,
                                 const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        rc = VTSS_FUNC(port.counters_clear, port_no);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_counters_get(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               vtss_port_counters_t *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        rc = VTSS_FUNC(port.counters_get, port_no, counters);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_basic_counters_get(const vtss_inst_t     inst,
                                     const vtss_port_no_t  port_no,
                                     vtss_basic_counters_t *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        rc = VTSS_FUNC(port.basic_counters_get, port_no, counters);
    VTSS_EXIT();
    return rc;
}

// Gets the forwarding configuration for a port( via the forward pointer )
vtss_rc vtss_port_forward_state_get(const vtss_inst_t     inst,
                                    const vtss_port_no_t  port_no,
                                    vtss_port_forward_t   *const forward)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *forward = vtss_state->port.forward[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_forward_state_set(const vtss_inst_t          inst,
                                    const vtss_port_no_t       port_no,
                                    const vtss_port_forward_t  forward)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u, forward: %s",
           port_no,
           forward == VTSS_PORT_FORWARD_ENABLED ? "enabled" :
           forward == VTSS_PORT_FORWARD_DISABLED ? "disabled" :
           forward == VTSS_PORT_FORWARD_INGRESS ? "ingress" : "egress");
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->port.forward[port_no] = forward;
        rc = VTSS_FUNC_COLD(port.forward_set, port_no);
#if defined(VTSS_FEATURE_LAYER2)
        if (rc == VTSS_RC_OK)
            rc = vtss_update_masks(vtss_state, 1, 0, 1);
#endif /* VTSS_FEATURE_LAYER2 */

    }
    VTSS_EXIT();
    return rc;
}

/* - MII and MMD management ---------------------------------------- */

static vtss_rc vtss_miim_check(vtss_state_t           *vtss_state,
                               vtss_port_no_t         port_no,
                               u8                     addr,
                               vtss_miim_controller_t *miim_controller,
                               u8                     *miim_addr)
{
    vtss_port_map_t *port_map;

    VTSS_RC(vtss_port_no_check(vtss_state, port_no));
    if (addr > 31) {
        VTSS_E("illegal addr: %u on port_no: %u", addr, port_no);
        return VTSS_RC_ERROR;
    }
    port_map = &vtss_state->port.map[port_no];
    *miim_controller = port_map->miim_controller;
    *miim_addr = port_map->miim_addr;
    if (*miim_controller < 0 || *miim_controller >= VTSS_MIIM_CONTROLLERS) {
        VTSS_E("illegal miim_controller:%d on port_no:%u, addr:0x%X, miim_addr:0x%X", *miim_controller, port_no, addr, *miim_addr);
        return VTSS_RC_ERROR;
    }
    if (*miim_addr > 31) {
        VTSS_E("illegal miim_addr:%u on port_no:%u, controller:%d, addr:0x%X", *miim_addr, port_no, *miim_controller, addr);
        return VTSS_RC_ERROR;
    }
    VTSS_SELECT_CHIP(port_map->miim_chip_no);
    return VTSS_RC_OK;
}


/* MII management read function (IEEE 802.3 clause 22) */
static vtss_rc vtss_miim_reg_read(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  const u8             addr,
                                  u16                  *const value)
{
    vtss_state_t           *vtss_state;
    vtss_rc                rc;
    vtss_miim_controller_t miim_controller;
    u8                     miim_addr;

    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_RC(vtss_miim_check(vtss_state, port_no, addr, &miim_controller, &miim_addr));
    if ((rc = VTSS_FUNC(port.miim_read, miim_controller, miim_addr, addr, value, TRUE)) == VTSS_RC_OK) {
        VTSS_N("port_no: %u, addr: 0x%02x, value: 0x%04x", port_no, addr, *value);
    }

    return rc;
}

/* MII management write function (IEEE 802.3 clause 22) */
static vtss_rc vtss_miim_reg_write(const vtss_inst_t    inst,
                                   const vtss_port_no_t port_no,
                                   const u8             addr,
                                   const u16            value)
{
    vtss_state_t           *vtss_state;
    vtss_rc                rc;
    vtss_miim_controller_t miim_controller;
    u8                     miim_addr;

    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_RC(vtss_miim_check(vtss_state, port_no, addr, &miim_controller, &miim_addr));
    if ((rc = VTSS_FUNC(port.miim_write, miim_controller, miim_addr, addr, value, TRUE)) == VTSS_RC_OK) {
        VTSS_N("port_no: %u, addr: 0x%02x, value: 0x%04x", port_no, addr, value);
    }
    return rc;
}

vtss_rc vtss_port_miim_read(const vtss_inst_t    inst,
                            const vtss_port_no_t port_no,
                            const u8             addr,
                            u16                  *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_miim_reg_read(vtss_state, port_no, addr, value);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_miim_write(const vtss_inst_t    inst,
                             const vtss_port_no_t port_no,
                             const u8             addr,
                             const u16            value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_miim_reg_write(vtss_state, port_no, addr, value);
    }
    VTSS_EXIT();
    return rc;
}

/* Internal feature: Access MII directly without lock */
#define VTSS_MIIM_ADDR_MASK 0x7f

/* MII management read function (direct - not via port map) */
vtss_rc vtss_miim_read(const vtss_inst_t            inst,
                       const vtss_chip_no_t         chip_no,
                       const vtss_miim_controller_t miim_controller,
                       const u8                     miim_addr,
                       const u8                     addr,
                       u16                          *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    u8           new_addr = (miim_addr & VTSS_MIIM_ADDR_MASK);

    VTSS_RC(vtss_inst_chip_no_check(inst, &vtss_state, chip_no));

    /* Direct access */
    if (new_addr != miim_addr)
        return VTSS_FUNC(port.miim_read, miim_controller, new_addr, addr, value, FALSE);

    VTSS_ENTER();
    rc = VTSS_FUNC(port.miim_read, miim_controller, miim_addr, addr, value, FALSE);
    VTSS_EXIT();
    return rc;
}

/* MII management write function - (direct - not via port map) */
vtss_rc vtss_miim_write(const vtss_inst_t            inst,
                        const vtss_chip_no_t         chip_no,
                        const vtss_miim_controller_t miim_controller,
                        const u8                     miim_addr,
                        const u8                     addr,
                        const u16                    value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    u8           new_addr = (miim_addr & VTSS_MIIM_ADDR_MASK);

    VTSS_RC(vtss_inst_chip_no_check(inst, &vtss_state, chip_no));

    /* Direct access */
    if (new_addr != miim_addr)
        return VTSS_FUNC(port.miim_write, miim_controller, new_addr, addr, value, FALSE);

    VTSS_ENTER();
    rc = VTSS_FUNC(port.miim_write, miim_controller, miim_addr, addr, value, FALSE);
    VTSS_EXIT();
    return rc;
}

static vtss_rc vtss_mmd_check(vtss_state_t           *vtss_state,
                              vtss_port_no_t         port_no,
                              u8                     addr,
                              vtss_miim_controller_t *miim_controller,
                              u8                     *miim_addr)
{
    vtss_port_map_t *port_map;

    VTSS_RC(vtss_port_no_check(vtss_state, port_no));
    if (addr > 31) {
        VTSS_E("illegal addr: %u on port_no: %u", addr, port_no);
        return VTSS_RC_ERROR;
    }
    port_map = &vtss_state->port.map[port_no];
    *miim_controller = port_map->miim_controller;
    *miim_addr = port_map->miim_addr;
    if (*miim_controller < 0 || *miim_controller >= VTSS_MIIM_CONTROLLERS) {
        VTSS_E("illegal miim_controller: %d on port_no: %u", *miim_controller, port_no);
        return VTSS_RC_ERROR;
    }
    if (*miim_addr > 31) {
        VTSS_E("illegal miim_addr: %u on port_no: %u", *miim_addr, port_no);
        return VTSS_RC_ERROR;
    }
    VTSS_SELECT_CHIP(port_map->miim_chip_no);
    return VTSS_RC_OK;
}

static vtss_rc vtss_mmd_reg_read(const vtss_inst_t    inst,
                                 const vtss_port_no_t port_no,
                                 const u8             mmd,
                                 const u16            addr,
                                 u16                  *const value)
{
    vtss_state_t           *vtss_state;
    vtss_rc                rc;
    vtss_miim_controller_t mdio_controller;
    u8                     mdio_addr;

    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_RC(vtss_mmd_check(vtss_state, port_no, 0, &mdio_controller, &mdio_addr));
    rc = VTSS_FUNC(port.mmd_read, mdio_controller, mdio_addr, mmd, addr, value, TRUE);
    if (rc == VTSS_RC_OK) {
        VTSS_N("port_no: %u, mmd: %u, addr: 0x%04x, value: 0x%04x",
               port_no, mmd, addr, *value);
    }
    return rc;
}

static vtss_rc vtss_mmd_reg_read_inc(const vtss_inst_t    inst,
                                     const vtss_port_no_t port_no,
                                     const u8             mmd,
                                     const u16            addr,
                                     u16                  *buf,
                                     u8                   count)
{
    vtss_state_t           *vtss_state;
    vtss_rc                rc;
    vtss_miim_controller_t mdio_controller;
    u8                     mdio_addr;
    u8                     buf_count = count;

    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_RC(vtss_mmd_check(vtss_state, port_no, 0, &mdio_controller, &mdio_addr));
    rc = VTSS_FUNC(port.mmd_read_inc, mdio_controller, mdio_addr, mmd, addr, buf, count, TRUE);
    if (rc == VTSS_RC_OK) {
        VTSS_N("port_no: %u, mmd: %u, addr: 0x%04x", port_no, mmd, addr);
        while (buf_count) {
            VTSS_N(" value[%d]: 0x%04x",count,*buf);
            buf++;
            buf_count--;
        }
    }
    return rc;
}

static vtss_rc vtss_mmd_reg_write(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  const u8             mmd,
                                  const u16            addr,
                                  const u16            value)
{
    vtss_state_t           *vtss_state;
    vtss_rc                rc;
    vtss_miim_controller_t mdio_controller;
    u8                     mdio_addr;

    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_RC(vtss_mmd_check(vtss_state, port_no, 0, &mdio_controller, &mdio_addr));
    rc = VTSS_FUNC(port.mmd_write, mdio_controller, mdio_addr, mmd, addr, value, TRUE);
    if (rc == VTSS_RC_OK) {
        VTSS_N("port_no: %u, mmd: %u, addr: 0x%04x, value: 0x%04x", port_no, mmd, addr, value);
    }
    return rc;
}

vtss_rc vtss_port_mmd_read(const vtss_inst_t    inst,
                           const vtss_port_no_t port_no,
                           const u8             mmd,
                           const u16            addr,
                           u16                  *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_mmd_reg_read(vtss_state, port_no, mmd, addr, value);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_mmd_read_inc(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               const u8             mmd,
                               const u16            addr,
                               u16                  *const buf,
                               u8                   count)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_mmd_reg_read_inc(vtss_state, port_no, mmd, addr, buf, count);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_port_mmd_write(const vtss_inst_t    inst,
                            const vtss_port_no_t port_no,
                            const u8             mmd,
                            const u16            addr,
                            const u16            value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_mmd_reg_write(vtss_state, port_no, mmd, addr, value);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_mmd_masked_write(const vtss_inst_t     inst,
                                   const vtss_port_no_t  port_no,
                                   const u8              mmd,
                                   const u16             addr,
                                   const u16             value,
                                   const u16             mask)
{
    vtss_state_t           *vtss_state;
    vtss_rc                rc;
    vtss_miim_controller_t miim_controller;
    u8                     miim_addr;
    u16                    val = 0; /* Please Lint */

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_miim_check(vtss_state, port_no, 0, &miim_controller, &miim_addr)) == VTSS_RC_OK &&
        (rc = VTSS_FUNC(port.mmd_read, miim_controller, miim_addr, mmd, addr, &val, TRUE)) == VTSS_RC_OK) {
        val = ((val & ~mask) | (value & mask));
        rc = VTSS_FUNC(port.mmd_write, miim_controller, miim_addr, mmd, addr, val, TRUE);
        if (rc == VTSS_RC_OK) {
            VTSS_N("port_no: %u, mmd: %u, addr: 0x%04x, val: 0x%04x", port_no, mmd, addr, val);
        }
    }
    VTSS_EXIT();
    return rc;
}

/* MMD management write function (direct - not via port map) */
vtss_rc vtss_mmd_write(const vtss_inst_t            inst,
                       const vtss_chip_no_t         chip_no,
                       const vtss_miim_controller_t miim_controller,
                       const u8                     miim_addr,
                       const u8                     mmd,
                       const u16                    addr,
                       const u16                    value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_chip_no_check(inst, &vtss_state, chip_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(port.mmd_write, miim_controller, miim_addr, mmd, addr, value, FALSE);
    }

    if (rc == VTSS_RC_OK) {
        VTSS_N("miim_addr: %u, mmd: %u, addr: 0x%04x, value: 0x%04x", miim_addr, mmd, addr, value);
    }
    VTSS_EXIT();
    return rc;
}

/* MMD management read function (direct - not via port map) */
vtss_rc vtss_mmd_read(const vtss_inst_t            inst,
                      const vtss_chip_no_t         chip_no,
                      const vtss_miim_controller_t miim_controller,
                      const u8                     miim_addr,
                      const u8                     mmd,
                      const u16                    addr,
                      u16                          *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_chip_no_check(inst, &vtss_state, chip_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(port.mmd_read, miim_controller, miim_addr, mmd, addr, value, FALSE);
    }

    if (rc == VTSS_RC_OK) {
        VTSS_N("miim_addr: %u, mmd: %u, addr: 0x%04x, value: 0x%04x",
               miim_addr, mmd, addr, *value);
    }
    VTSS_EXIT();
    return rc;
}

/* - Warm start synchronization ------------------------------------ */

#if defined(VTSS_FEATURE_WARM_START)
static BOOL vtss_bool_changed(BOOL old, BOOL new)
{
    return ((old == new) || (old && new) ? 0 : 1);
}

/* Synchronize port configuration */
static vtss_rc vtss_port_conf_sync(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_rc          rc;
    vtss_port_conf_t old, *new = &vtss_state->port.conf[port_no];

    VTSS_MEMSET(&old, 0, sizeof(old)); /* Please Lint */
    if ((rc = VTSS_FUNC(port.conf_get, port_no, &old)) == VTSS_RC_OK &&
        new->speed != VTSS_SPEED_UNDEFINED &&
        (vtss_bool_changed(old.power_down, new->power_down) ||
         old.speed != new->speed ||
         vtss_bool_changed(old.fdx, new->fdx) ||
         vtss_bool_changed(old.flow_control.obey, new->flow_control.obey) ||
         vtss_bool_changed(old.flow_control.generate, new->flow_control.generate))) {
        /* Apply changed configuration */
        VTSS_I("port_no %u changed, apply port conf", port_no);
        VTSS_I("old conf, power_down: %u, speed: %u, fdx: %u, obey: %u, gen: %u",
               old.power_down, old.speed, old.fdx,
               old.flow_control.obey, old.flow_control.generate);
        VTSS_I("new conf, power_down: %u, speed: %u, fdx: %u, obey: %u, gen: %u",
               new->power_down, new->speed, new->fdx,
               new->flow_control.obey, new->flow_control.generate);
        rc = VTSS_FUNC(port.conf_set, port_no);
    }

    return rc;
}

/* Synchronize port clause 37 control */
static vtss_rc vtss_port_clause_37_sync(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_rc                       rc = VTSS_RC_OK;
    vtss_port_clause_37_control_t old_ctrl, *new_ctrl = &vtss_state->port.clause_37[port_no];
    vtss_port_clause_37_adv_t     *old, *new;

    old = &old_ctrl.advertisement;
    new = &new_ctrl->advertisement;

    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SERDES &&
        (rc = VTSS_FUNC(port.clause_37_control_get, port_no, &old_ctrl)) == VTSS_RC_OK &&
        (vtss_bool_changed(old_ctrl.enable, new_ctrl->enable) ||
         (new_ctrl->enable &&
          (vtss_bool_changed(old->next_page, new->next_page) ||
           vtss_bool_changed(old->acknowledge, new->acknowledge) ||
           old->remote_fault != new->remote_fault ||
           vtss_bool_changed(old->asymmetric_pause, new->asymmetric_pause) ||
           vtss_bool_changed(old->symmetric_pause, new->symmetric_pause) ||
           vtss_bool_changed(old->hdx, new->hdx) ||
           vtss_bool_changed(old->fdx, new->fdx))))) {
        VTSS_I("port_no %u changed, apply clause 37 conf", port_no);
        VTSS_I("old conf, ena: %u, next: %u, ack: %u, rem: %u, assym: %u, sym: %u. hdx: %u, fdx: %u",
               old_ctrl.enable, old->next_page, old->acknowledge, old->remote_fault, old->asymmetric_pause, old->symmetric_pause, old->hdx, old->fdx);
        VTSS_I("new conf, ena: %u, next: %u, ack: %u, rem: %u, assym: %u, sym: %u. hdx: %u, fdx: %u",
               new_ctrl->enable, new->next_page, new->acknowledge, new->remote_fault, new->asymmetric_pause, new->symmetric_pause, new->hdx, new->fdx);
        rc = VTSS_FUNC(port.clause_37_control_set, port_no);
    }
    return rc;
}

vtss_rc vtss_port_restart_sync(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(vtss_port_conf_sync(vtss_state, port_no));
        VTSS_RC(vtss_port_clause_37_sync(vtss_state, port_no));
#if defined(VTSS_ARCH_OCELOT)
        VTSS_FUNC_RC(port.ifh_set, port_no);
#endif /* VTSS_ARCH_OCELOT */

    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_WARM_START */

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_port_inst_create(vtss_state_t *vtss_state)
{
    vtss_port_no_t   port_no;
    vtss_init_conf_t *init_conf = &vtss_state->init_conf;

    init_conf->miim_read = vtss_miim_reg_read;
    init_conf->miim_write = vtss_miim_reg_write;
    init_conf->mmd_read = vtss_mmd_reg_read;
    init_conf->mmd_read_inc = vtss_mmd_reg_read_inc;
    init_conf->mmd_write = vtss_mmd_reg_write;

#if defined(VTSS_FEATURE_PORT_MUX)
    switch (vtss_state->create.target) {
#if defined(VTSS_ARCH_LUTON26)
    case VTSS_TARGET_SPARX_III_10:
    case VTSS_TARGET_SPARX_III_10_01:
        init_conf->mux_mode = VTSS_PORT_MUX_MODE_2;
        break;
    case VTSS_TARGET_CARACAL_LITE:
    case VTSS_TARGET_CARACAL_1:
    case VTSS_TARGET_SPARX_III_10_UM:
        init_conf->mux_mode = VTSS_PORT_MUX_MODE_1;
        break;
#endif /* VTSS_ARCH_LUTON26 */
#if defined(VTSS_ARCH_OCELOT)
    case VTSS_TARGET_7511:
    case VTSS_TARGET_7513:
        init_conf->mux_mode = VTSS_PORT_MUX_MODE_0;
        break;
    case VTSS_TARGET_7512:
    case VTSS_TARGET_7514:
        init_conf->mux_mode = VTSS_PORT_MUX_MODE_4;
        break;
#endif /* VTSS_ARCH_OCELOT */
    default:
        init_conf->mux_mode = VTSS_PORT_MUX_MODE_0;
        break;
    }
#endif /* VTSS_FEATURE_PORT_MUX */


    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        vtss_state->port.forward[port_no] = VTSS_PORT_FORWARD_ENABLED;
        // Initialize all ports in the table as unused.
        // vtss_port_map_set will be called later on
        // and set 'cnt' number of ports in this port
        // table, where 'cnt' <= VTSS_PORT_NO_END.
        vtss_state->port.map[port_no].chip_port = -1;
    }

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    init_conf->serdes.serdes1g_vdd = VTSS_VDD_1V0; /* Based on Ref board design */
    init_conf->serdes.serdes6g_vdd = VTSS_VDD_1V0; /* Based on Ref board design */
    init_conf->serdes.ib_cterm_ena = 1;            /* Based on Ref board design */
    init_conf->serdes.qsgmii.ob_post0 = 2;         /* Based on Ref board design */
    init_conf->serdes.qsgmii.ob_sr = 0;            /* Based on Ref board design */
#endif /* VTSS_FEATURE_SERDES_MACRO_SETTINGS */

    return VTSS_RC_OK;
}

/* - Port utilities ------------------------------------------------ */
/* Decode advertisement word */
vtss_rc vtss_cmn_port_clause_37_adv_get(u32 value, vtss_port_clause_37_adv_t *adv)
{
    adv->fdx = VTSS_BOOL(value & (1<<5));
    adv->hdx = VTSS_BOOL(value & (1<<6));
    adv->symmetric_pause = VTSS_BOOL(value & (1<<7));
    adv->asymmetric_pause = VTSS_BOOL(value & (1<<8));
    switch ((value>>12) & 3) {
    case 0:
        adv->remote_fault = VTSS_PORT_CLAUSE_37_RF_LINK_OK;
        break;
    case 1:
        adv->remote_fault = VTSS_PORT_CLAUSE_37_RF_LINK_FAILURE;
        break;
    case 2:
        adv->remote_fault = VTSS_PORT_CLAUSE_37_RF_OFFLINE;
        break;
    default:
        adv->remote_fault = VTSS_PORT_CLAUSE_37_RF_AUTONEG_ERROR;
        break;
    }
    adv->acknowledge = VTSS_BOOL(value & (1<<14));
    adv->next_page = VTSS_BOOL(value & (1<<15));

    return VTSS_RC_OK;
}

vtss_rc vtss_cmn_port_sgmii_cisco_aneg_get(u32 value, vtss_port_sgmii_aneg_t *sgmii_adv)
{
    sgmii_adv->link = ((value >> 15) == 1) ? 1 : 0;
    sgmii_adv->fdx = (((value >> 12) & 0x1) == 1) ? 1 : 0;
    sgmii_adv->hdx = !sgmii_adv->fdx;
    value = ((value >> 10) & 3);
    sgmii_adv->speed_10M = (value == 0 ? 1 : 0);
    sgmii_adv->speed_100M = (value == 1 ? 1 : 0);
    sgmii_adv->speed_1G = (value == 2 ? 1 : 0);
    return VTSS_RC_OK;
}

vtss_rc vtss_cmn_port_usxgmii_aneg_get(u32 lp_adv, vtss_port_usxgmii_aneg_t *usxgmii)
{
    usxgmii->link = ((lp_adv >> 15) == 1) ? 1 : 0;
    usxgmii->fdx = (((lp_adv >> 12) & 0x1) == 1) ? 1 : 0;
    switch ((lp_adv >> 9) & 7) {
    case 0:
        usxgmii->speed = VTSS_SPEED_10M;
        break;
    case 1:
        usxgmii->speed = VTSS_SPEED_100M;
        break;
    case 2:
        usxgmii->speed = VTSS_SPEED_1G;
        break;
    case 3:
        usxgmii->speed = VTSS_SPEED_10G;
        break;
    case 4:
        usxgmii->speed = VTSS_SPEED_2500M;
        break;
    case 5:
        usxgmii->speed = VTSS_SPEED_5G;
        break;
    default:
        VTSS_E("Unknown speed '%d' after usxgmii aneg", ((lp_adv >> 9) & 7));
        break;
    }
    return VTSS_RC_OK;
}
/* Encode advertisement word */
vtss_rc vtss_cmn_port_clause_37_adv_set(u32 *value, vtss_port_clause_37_adv_t *adv, BOOL aneg_enable)
{
    u32 rf;

    if (!aneg_enable) {
        *value = 0;
        return VTSS_RC_OK;
    }
    switch (adv->remote_fault) {
    case VTSS_PORT_CLAUSE_37_RF_LINK_OK:
        rf = 0;
        break;
    case VTSS_PORT_CLAUSE_37_RF_LINK_FAILURE:
        rf = 1;
        break;
    case VTSS_PORT_CLAUSE_37_RF_OFFLINE:
        rf = 2;
        break;
    default:
        rf = 3;
        break;
    }

    *value = (((adv->next_page ? 1 : 0)<<15) |
              ((adv->acknowledge ? 1 : 0)<<14) |
              (rf<<12) |
              ((adv->asymmetric_pause ? 1 : 0)<<8) |
              ((adv->symmetric_pause ? 1 : 0)<<7) |
              ((adv->hdx ? 1 : 0)<<6) |
              ((adv->fdx ? 1 : 0)<<5));
    return VTSS_RC_OK;
}

/* Get first port_no in port_list or CPU port */
vtss_port_no_t vtss_cmn_first_port_no_get(vtss_state_t *vtss_state,
                                          const BOOL port_list[VTSS_PORT_ARRAY_SIZE])
{
    vtss_port_no_t port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (port_list[port_no])
            return port_no;
    }
    return VTSS_PORT_NO_NONE;
}

#if VTSS_OPT_DEBUG_PRINT
vtss_port_no_t vtss_cmn_port2port_no(vtss_state_t *vtss_state,
                                     const vtss_debug_info_t *const info, u32 chip_port)
{
    vtss_port_no_t port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if ((u32)VTSS_CHIP_PORT(port_no) == chip_port && VTSS_PORT_CHIP_SELECTED(port_no)) {
            if (info->port_list[port_no])
                return port_no;
            break;
        }
    }
    return VTSS_PORT_NO_NONE;
}
#endif

vtss_port_no_t vtss_api_port(vtss_state_t *vtss_state, u32 chip_port)
{
    vtss_port_no_t port_no;

    /* Map from chip port to API port */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if ((u32)VTSS_CHIP_PORT(port_no) == chip_port) {
            if (VTSS_PORT_CHIP_SELECTED(port_no)) {
                return port_no;
            }
            VTSS_D("Chip Port %u API Port %u not selected for this chip", chip_port, port_no);
            break;
        }
    }
    VTSS_D("unknown chip port: %u", chip_port);
    return VTSS_PORT_NO_NONE;
}

#if defined(VTSS_FEATURE_PORT_KR) || defined(VTSS_FEATURE_PORT_KR_IRQ)

vtss_rc vtss_port_kr_status_get(vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_port_kr_status_t *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_MEMSET(status, 0, sizeof(*status));
        rc = VTSS_FUNC_COLD(port.kr_status, port_no, status);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_port_kr_conf_set(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  const vtss_port_kr_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->port.kr_conf[port_no] = *conf;
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
        VTSS_MEMSET(&vtss_state->port.train_state[port_no], 0, sizeof(vtss_port_kr_state_t));
#endif
        rc = VTSS_FUNC_COLD(port.kr_conf_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_kr_conf_get(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  vtss_port_kr_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->port.kr_conf[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_kr_fec_get(const vtss_inst_t inst,
                             const vtss_port_no_t port_no,
                             vtss_port_kr_fec_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->port.kr_fec[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_kr_fec_set(const vtss_inst_t inst,
                             const vtss_port_no_t port_no,
                             const vtss_port_kr_fec_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_state->port.conf[port_no].if_type != VTSS_PORT_INTERFACE_SFI &&
           (conf->r_fec || conf->rs_fec)) {
            // If enabling R-FEC and/or RS-FEC and the MAC I/F is not SFI, it's
            // an error. If disabling both R-FEC and RS-FEC, the MAC I/F can be
            // anything.
            rc = VTSS_RC_ERROR;
        } else {
            vtss_state->port.kr_fec[port_no] = *conf;
            rc = VTSS_FUNC_COLD(port.kr_fec_set, port_no);
        }
    }
    VTSS_EXIT();
    return rc;
}

#endif /* defined(VTSS_FEATURE_PORT_KR) || defined(VTSS_FEATURE_PORT_KR_IRQ) */

#if defined(VTSS_FEATURE_PORT_KR_IRQ)

vtss_rc vtss_port_kr_irq_get(vtss_inst_t inst,
                             const vtss_port_no_t port_no,
                             u32 *const vector)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(port.kr_irq_get, port_no, vector);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_kr_irq_activity(vtss_inst_t inst,
                                  u32 *const mask)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, 0)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(port.kr_irq_activity, mask);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_kr_event_enable(const vtss_inst_t     inst,
                                  const vtss_port_no_t port_no,
                                  BOOL enable)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(port.kr_event_enable, port_no, enable);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_port_kr_eye_get(vtss_inst_t inst,
                             const vtss_port_no_t port_no,
                             vtss_port_kr_eye_dim_t *const eye)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(port.kr_eye_dim, port_no, eye);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_kr_ctle_adjust(vtss_inst_t inst,
                                 const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(port.kr_ctle_adjust, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_kr_ctle_get(vtss_inst_t inst,
                              const vtss_port_no_t port_no, vtss_port_ctle_t *const ctle)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(port.kr_ctle_get, port_no, ctle);
    }
    VTSS_EXIT();
    return rc;
}


#endif /* VTSS_FEATURE_PORT_KR_IRQ */

vtss_rc vtss_port_test_conf_get(const vtss_inst_t      inst,
                                const vtss_port_no_t   port_no,
                                vtss_port_test_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->port.test_conf[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_test_conf_set(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_port_test_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->port.test_conf[port_no] = *conf;
        rc = VTSS_FUNC_COLD(port.test_conf_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_PORT_KR_IRQ)

// For debugging
# if 0
static char *fa_kr_aneg_rate(u32 reg)
{
    switch (reg) {
    case 0:  return "No Change";
    case 7:  return "25G-KR";
    case 8:  return "25G-KR-S";
    case 9:  return "10G-KR";
    case 10: return "10G-KX4";
    case 11: return "5G-KR";
    case 12: return "2.5G-KX";
    case 13: return "1G-KX";
    default: return "other";
    }
    return "other";
}


static char *irq2txt(u32 irq)
{
    switch (irq) {
    case KR_ACTV:       return  "KR_ACTV";
    case KR_LPSVALID:   return  "KR_LPS";
    case KR_LPCVALID:   return  "KR_LPC";
    case KR_WT_DONE:    return  "WT_DONE";
    case KR_MW_DONE:    return  "MW_DONE";
    case KR_BER_BUSY_0: return  "BER_BUSY0";
    case KR_BER_BUSY_1: return  "BER_BUSY1";
    case KR_REM_RDY_0:  return  "REM_RDY0";
    case KR_REM_RDY_1:  return  "REM_RDY1";
    case KR_FRLOCK_0:   return  "FRLOCK0";
    case KR_FRLOCK_1:   return  "FRLOCK1";
    case KR_DME_VIOL_0: return  "DME_VIOL0";
    case KR_DME_VIOL_1: return  "DME_VIOL1";
    case KR_AN_XMIT_DISABLE: return  "AN_XM_DIS";
    case KR_TRAIN:      return  "TRAIN";
    case KR_RATE_DET:   return  "RATE_DET";
    case KR_CMPL_ACK:   return  "CMPL_ACK";
    case KR_AN_GOOD:    return  "AN_GOOD";
    case KR_LINK_FAIL:  return  "LINK_FAIL";
    case KR_ABD_FAIL:   return  "ABD_FAIL";
    case KR_ACK_FAIL:   return  "ACK_FAIL";
    case KR_NP_FAIL:    return  "NP_FAIL";
    case KR_NP_RX:      return  "NP_RX";
    case KR_INCP_LINK:  return  "INCP_LINK";
    case KR_GEN0_DONE:  return  "GEN0_DONE";
    case KR_GEN1_DONE:  return  "GEN1_DONE";
    case 0:  return "";
    default:  return "ILLEGAL";
    }
}

static void dump_irq(u32 p, u32 irq)
{
    char buf[200] = {0}, *b=&buf[0];

    b += VTSS_SPRINTF(b, "p:%d ",p);
    for (u32 i = 4; i < 31; i++) {
        if (((1 << i) & irq) > 0) {
            b += VTSS_SPRINTF(b, "%s ",irq2txt((1 << i)));
        }
    }
    if ((irq & 0xf) > 0) {
        b += VTSS_SPRINTF(b, "%s ",fa_kr_aneg_rate(irq & 0xf));
    }

    printf("%s \n",buf);
}


static vtss_port_speed_t kr_irq2spd(u32 irq)
{
    switch (irq) {
    case KR_ANEG_RATE_25G: return VTSS_SPEED_25G;
    case KR_ANEG_RATE_10G: return VTSS_SPEED_10G;
    case KR_ANEG_RATE_5G:  return VTSS_SPEED_5G;
    case KR_ANEG_RATE_2G5: return VTSS_SPEED_2500M;
    case KR_ANEG_RATE_1G:  return VTSS_SPEED_1G;
    default:
        printf("KR speed not supported\n");
    }
    return VTSS_SPEED_10G;
}
#endif

static vtss_rc kr_fw_req(vtss_state_t *vtss_state,
                         const vtss_port_no_t port_no,
                         vtss_port_kr_fw_req_t *const fw_req)
{
    return vtss_state->port.kr_fw_req(vtss_state, port_no, fw_req);
}

static vtss_rc kr_train_frm_get(vtss_state_t *vtss_state,
                                const vtss_port_no_t port_no,
                                vtss_port_kr_frame_t *const frm)
{
    return vtss_state->port.kr_frame_get(vtss_state, port_no, frm);
}

static vtss_rc kr_train_frm_set(vtss_state_t *vtss_state,
                                const vtss_port_no_t port_no,
                                const vtss_port_kr_frame_t *const frm)
{
    return vtss_state->port.kr_frame_set(vtss_state, port_no, frm);
}

static vtss_rc kr_coef_set(vtss_state_t *vtss_state,
                           const vtss_port_no_t port_no,
                           const u16 coef,
                           vtss_kr_status_results_t *const sts)
{
    return vtss_state->port.kr_coef_set(vtss_state, port_no, coef, sts);
}

static vtss_rc kr_eye_dim_get(vtss_state_t *vtss_state,
                                 const vtss_port_no_t port_no,
                                 vtss_port_kr_eye_dim_t *const eye)
{
    return vtss_state->port.kr_eye_dim(vtss_state, port_no, eye);
}

static u16 kr_analyze_ber(vtss_port_kr_state_t *krs, vtss_kr_tap_t tap)
{
    u32 zero_cnt = 0, low_mark = 0, high_mark = 0, low_best = 0, high_best = 0;
    for (u32 i = 0; i < krs->lp_tap_max_cnt[tap]; i++) {
        if (krs->ber_cnt[tap][i] == 0 ) {
            if (zero_cnt == 0) {
                low_mark = i;
            }
            zero_cnt++;
            if (i == krs->lp_tap_max_cnt[tap] - 1) {
                high_mark = i;
                if ((high_mark - low_mark) >= (high_best - low_best)) {
                    high_best = high_mark;
                    low_best = low_mark;
                }
            }
        } else {
            if (zero_cnt == 0) {
                continue;
            }
            high_mark = i - 1;
            if ((high_mark - low_mark) >= (high_best - low_best)) {
                high_best = high_mark;
                low_best = low_mark;
            }
            zero_cnt = 0;
        }
    }
    return (high_best - (high_best-low_best)/2);
}

static u32 kr_get_best_eye(vtss_port_kr_state_t *krs, vtss_kr_tap_t tap)
{
    u32 max_height = 0;
    u32 indx = 0, repl=0, max_repl=0;

    for (u32 i = 0; i < krs->lp_tap_max_cnt[tap]; i++) {
        if (krs->eye_height[tap][i] > max_height ) {
            max_height = krs->eye_height[tap][i];
        }
    }
    // Find the midfield of the identcial max height posistions (if more than one)
    for (u32 i = 0; i < krs->lp_tap_max_cnt[tap]; i++) {
        if (krs->eye_height[tap][i] == max_height ) {
            for (u32 a = i; a <= krs->lp_tap_max_cnt[tap]; a++) {
                if (krs->eye_height[tap][a] == max_height && (a < krs->lp_tap_max_cnt[tap])) {
                    repl++;
                } else {
                    if (repl > max_repl) {
                        max_repl = repl;
                        indx = i;
                        i = a;
                        repl = 0;
                        break;
                    }
                }
            }
        }
    }

    return indx + (max_repl / 2);
}

static u16 kr_eye_height_get(vtss_state_t *state, vtss_port_no_t p)
{
    vtss_port_kr_eye_dim_t eye;

    if (kr_eye_dim_get(state, p, &eye) == VTSS_RC_OK) {
        return (u16)eye.height;
    } else {
        VTSS_E("Eye scan fails to complete\n");
    }
    return 0;
}

static u16 fa_port_kr_ber_cnt(vtss_state_t *vtss_state, vtss_port_no_t p)
{
    u16 ber;
    if (vtss_state->port.kr_ber_cnt(vtss_state, p, &ber) == VTSS_RC_OK) {
        return ber;
    } else {
        VTSS_E("Could not read BER");
    }
    return 0;
}
static u16 kr_coef2frm(kr_coefficient_update_t ld, vtss_kr_tap_t tap)
{
    u16 offset;

    if (tap == VTSS_TAP_CP1) {
        offset = 4;
    } else if (tap == VTSS_TAP_C0) {
        offset = 2;
    } else {
        offset = 0;
    }

    switch (ld) {
    case COEF_PRESET: return (1 << 13);
    case COEF_INIT:   return (1 << 12);
    case COEF_DECR:   return (1 << (1 + offset));
    case COEF_INCR:   return (1 << (0 + offset));
    case COEF_HOLD:   return 0;
    default:
        VTSS_E("Illegal prm\n");
        break;
    }
    return 0;
}

static kr_status_report_t kr_frm2status(u16 data, vtss_kr_tap_t tap)
{
    u16 sts = 0;

    if (tap == VTSS_TAP_CP1) {
        sts = (data >> 4) & 0x3;
    } else if (tap == VTSS_TAP_C0) {
        sts = (data >> 2) & 0x3;
    } else {
        sts = data & 0x3;
    }

    switch (sts) {
    case 0:  return STATUS_NOT_UPDATED;
    case 1:  return STATUS_UPDATED;
    case 2:  return STATUS_MINIMUM;
    default: return STATUS_MAXIMUM;
    }
}

static vtss_kr_tap_t kr_ber_next_tap(vtss_kr_tap_t tap, BOOL first)
{
    if (first) {
        return VTSS_TAP_CM1;
    }
    switch (tap) {
    case VTSS_TAP_CM1: return VTSS_TAP_CP1;
    case VTSS_TAP_CP1: return VTSS_TAP_C0;
    case VTSS_TAP_C0:  return VTSS_TAP_C0;
    }
    return 0;
}

static void kr_send_coef_update(vtss_state_t *state, vtss_port_kr_state_t *krs, vtss_port_no_t p, kr_coefficient_update_t coef)
{
    vtss_port_kr_frame_t frm;
    frm.data = kr_coef2frm(coef, krs->current_tap);
    frm.type = VTSS_COEFFICIENT_UPDATE_FRM;
    (void)kr_train_frm_set(state, p, &frm);
    krs->ber_coef_frm = frm.data;
}

static void kr_send_sts_report(vtss_state_t *state, vtss_port_no_t p, u32 data)
{
    vtss_port_kr_frame_t frm;
    frm.data = data;
    frm.type = VTSS_STATUS_REPORT_FRM;
    (void)kr_train_frm_set(state, p, &frm);
}

static void kr_ber_training(vtss_state_t *vtss_state,
                            vtss_port_no_t p, u32 irq)
{

    vtss_port_kr_frame_t frm;
    vtss_port_kr_state_t *krs = &vtss_state->port.train_state[p];
    kr_status_report_t lp_status = 0;
    vtss_port_kr_fw_req_t req_msg = {0};
    u32 mid_mark;

    if (irq == KR_TRAIN) {
        kr_send_coef_update(vtss_state, krs, p, COEF_INIT);
        krs->ber_training_stage = VTSS_BER_GO_TO_MIN;
        krs->current_tap = kr_ber_next_tap(0, 1); // Give us the first tap
        // Sometimes the signal is unstable right after TRAIN start
        // Disable fail checking and enable after first step in VTSS_BER_GO_TO_MIN
        krs->ignore_fail = TRUE;
        return;
    }

    if (irq == KR_LPSVALID) {
       frm.type = VTSS_STATUS_REPORT_FRM;
       (void)kr_train_frm_get(vtss_state, p, &frm);
       krs->ber_status_frm = frm.data;
       lp_status = kr_frm2status(frm.data, krs->current_tap);
    }

    switch (krs->ber_training_stage) {
    case VTSS_BER_GO_TO_MIN:
        if (irq == KR_LPSVALID) {
            if (lp_status == STATUS_UPDATED || lp_status == STATUS_MAXIMUM) {
                kr_send_coef_update(vtss_state, krs, p, COEF_HOLD);
                if (krs->dme_viol_handled) {
                    krs->ber_training_stage = VTSS_BER_CALCULATE_BER;
                    krs->tap_idx = 0;
                    krs->dme_viol = 0;
                    krs->dme_viol_handled = FALSE;
                    krs->tap_max_reached = FALSE;
                }
            } else if (lp_status == STATUS_NOT_UPDATED) {
                if (krs->dme_viol) {
                    kr_send_coef_update(vtss_state, krs, p, COEF_INCR);
                    krs->dme_viol_handled = TRUE;
                } else {
                    kr_send_coef_update(vtss_state, krs, p, COEF_DECR);
                }
            } else if (lp_status == STATUS_MINIMUM) {
                kr_send_coef_update(vtss_state, krs, p, COEF_HOLD);
                krs->ber_training_stage = VTSS_BER_CALCULATE_BER;
                krs->tap_idx = 0;
                krs->tap_max_reached = FALSE;
            } else {
                VTSS_E("IRQ:0x%x, State:VTSS_BER_GO_TO_MIN, LP Status:%d\n",irq, lp_status);
            }
        } else if (irq == KR_DME_VIOL_1) {
            krs->dme_viol = TRUE;
        }
        krs->ignore_fail = FALSE;
        return;
    case VTSS_BER_CALCULATE_BER:
        krs->ignore_fail = TRUE; // Basically its to late to deal with errors in the CALC_BER stage
        if (irq == KR_BER_BUSY_1) {
            krs->ber_busy = TRUE;
        } else if ((irq == KR_BER_BUSY_0) && (krs->ber_busy)) {
            krs->ber_busy = FALSE;
            krs->ber_cnt[krs->current_tap][krs->tap_idx - 1] = fa_port_kr_ber_cnt(vtss_state, p);
            krs->eye_height[krs->current_tap][krs->tap_idx - 1] = kr_eye_height_get(vtss_state, p);
            if (krs->tap_max_reached) {
                krs->lp_tap_max_cnt[krs->current_tap] = krs->tap_idx;
                if (vtss_state->port.kr_conf[p].train.use_ber_cnt) {
                    mid_mark = kr_analyze_ber(krs, krs->current_tap);
                } else {
                    mid_mark = kr_get_best_eye(krs, krs->current_tap);
                }
                krs->lp_tap_end_cnt[krs->current_tap] = mid_mark;
                krs->decr_cnt = krs->tap_idx - mid_mark - 1;
                kr_send_coef_update(vtss_state, krs, p, COEF_DECR);
                krs->ber_training_stage = VTSS_BER_MOVE_TO_MID_MARK;
            } else {
                kr_send_coef_update(vtss_state, krs, p, COEF_INCR);
            }
        } else if (irq == KR_LPSVALID) {
            if (lp_status == STATUS_NOT_UPDATED) {
                req_msg.ber_enable = TRUE;
                (void)kr_fw_req(vtss_state, p, &req_msg);
                krs->tap_idx++;
            } else if (lp_status == STATUS_UPDATED || (lp_status == STATUS_MAXIMUM)) {
                kr_send_coef_update(vtss_state, krs, p, COEF_HOLD);
                if(lp_status == STATUS_MAXIMUM) {
                    krs->tap_max_reached = TRUE;
                }
            } else {
                VTSS_E("IRQ:0x%x, State:VTSS_BER_CALCULATE_BER, LP Status:%d\n",irq, lp_status);
            }
        } else if (irq == KR_DME_VIOL_1) {
            // Ignore DME_VIOL in this state
        } else {
            VTSS_E("IRQ:0x%x, State:VTSS_BER_CALCULATE_BER, Status:%d, Last COEF send:%d\n",irq,lp_status,krs->ber_coef_frm);
        }
        break;

    case VTSS_BER_MOVE_TO_MID_MARK:
        if (irq == KR_LPSVALID) {
            krs->ignore_fail = TRUE;
            if (lp_status == STATUS_UPDATED || lp_status == STATUS_MINIMUM || lp_status == STATUS_MAXIMUM) {
                // Note: STATUS_MAXIMUM should not occur but we must support it
                kr_send_coef_update(vtss_state, krs, p, COEF_HOLD);
                if (krs->decr_cnt > 0) {
                    krs->decr_cnt--;
                }
                if (krs->decr_cnt == 0 || lp_status == STATUS_MINIMUM || lp_status == STATUS_MAXIMUM) {
                    if (krs->current_tap == kr_ber_next_tap(krs->current_tap, 0)) {
                        krs->ber_training_stage = VTSS_BER_LOCAL_RX_TRAINED;
                    } else {
                        krs->current_tap = kr_ber_next_tap(krs->current_tap, 0);
                        krs->ber_training_stage = VTSS_BER_GO_TO_MIN;
                        krs->ignore_fail = FALSE;
                    }
                }
            } else if (lp_status == STATUS_NOT_UPDATED) {
                kr_send_coef_update(vtss_state, krs, p, COEF_DECR);
            } else {
                VTSS_E("IRQ:0x%x, State:MOVE_TO_MID_MARK(1), Status:%d, Last COEF send:%d\n",irq,lp_status,krs->ber_coef_frm);
            }
        } else {
            VTSS_E("IRQ:0x%x, State:MOVE_TO_MID_MARK(2), Status:%d, Last COEF send:%d\n",irq,lp_status,krs->ber_coef_frm);
        }
        break;

    default:
        VTSS_E("IRQ:0x%x, State:DEFAILT, Status:%d, Last COEF send:%d\n",irq,lp_status,krs->ber_coef_frm);
        break;
    }
}


static void kr_reset_state(vtss_port_kr_state_t *krs) {
    VTSS_MEMSET(krs, 0, sizeof(vtss_port_kr_state_t));
}
#define BT(x) (1 << (x))
// Handle the incoming KR IRQs
static vtss_rc kr_irq_apply(vtss_state_t *vtss_state,
                            const vtss_port_no_t port_no,
                            const u32 irq_vec)
{
    vtss_port_kr_state_t *krs = &vtss_state->port.train_state[port_no];
    vtss_port_kr_frame_t frm;
    vtss_port_kr_conf_t *kr = &vtss_state->port.kr_conf[port_no];
    u32 irq = irq_vec;

     // To ignore IRQ failures
    if (krs->ignore_fail) {
        irq &= ~KR_DME_VIOL_0;
        irq &= ~KR_DME_VIOL_1;
        irq &= ~KR_REM_RDY_0;
        irq &= ~KR_FRLOCK_0;
    }
    // Ignore FRLOCK in sets (Frame lock off/on)
    if ((irq & KR_FRLOCK_0) && (irq & KR_FRLOCK_1)) {
        irq &= ~KR_FRLOCK_1;
        irq &= ~KR_FRLOCK_0;
    }

    // KR_AN_XMIT_DISABLE. Aneg is restarted.
    if (irq & KR_AN_XMIT_DISABLE) {
        vtss_port_kr_fw_req_t req_msg = {0};
        req_msg.transmit_disable = TRUE;
        if (krs->training_started) {
            krs->training_started = FALSE;
            req_msg.stop_training = TRUE;
        }
        (void)kr_fw_req(vtss_state, port_no, &req_msg);
        kr_reset_state(krs);
    }

    // KR_TRAIN. Start Training
    if (irq & KR_TRAIN) {
        if (kr->train.enable) {
            krs->test_mode = kr->train.test_mode;
            krs->test_repeat = kr->train.test_repeat;
            krs->current_state = VTSS_TR_SEND_TRAINING;
            krs->training_started = TRUE;
            krs->remote_rx_ready = FALSE;
            krs->ignore_fail = FALSE;
            vtss_port_kr_fw_req_t req_msg = {0};
            req_msg.start_training = TRUE;
            req_msg.mw_start = TRUE;
            (void)kr_fw_req(vtss_state, port_no, &req_msg);
            if (kr->train.no_remote) {
                // Do not train remote LP
                krs->ber_training_stage = VTSS_BER_LOCAL_RX_TRAINED;
                krs->current_state = VTSS_TR_TRAIN_REMOTE;
                // 'Receiver Ready' sent 3 times to LP as according to standard
                krs->tr_res.status |= BT(15);
                kr_send_sts_report(vtss_state, port_no, krs->tr_res.status);
                krs->ignore_fail = TRUE;
            } else {
                (void)kr_ber_training(vtss_state, port_no, KR_TRAIN);
            }
        } else {
            krs->current_state = VTSS_TR_SEND_DATA;
            krs->training_started = FALSE;
            vtss_port_kr_fw_req_t req_msg = {0};
            req_msg.stop_training = TRUE;
            req_msg.tr_done = TRUE;
            (void)kr_fw_req(vtss_state, port_no, &req_msg);
            krs->signal_detect = TRUE;
        }
    }

    // KR_FRLOCK_1. (Training frame lock attained)
    if ((irq & KR_FRLOCK_1) && krs->training_started) {
        if (krs->current_state == VTSS_TR_SEND_TRAINING) {
            krs->current_state = VTSS_TR_TRAIN_LOCAL;
        }
    }

    // KR_REM_RDY_1. Remote is ready
    if (irq & KR_REM_RDY_1) {
        // Ignore failures after remote is ready
        irq &= ~KR_DME_VIOL_0;
        irq &= ~KR_DME_VIOL_1;
        irq &= ~KR_REM_RDY_0;
        irq &= ~KR_FRLOCK_0;
    }

    // KR_FRLOCK_0. (Training frame lock is lost during training)
    if ((irq & KR_FRLOCK_0) && krs->training_started && (krs->current_state != VTSS_TR_LINK_READY)) {
        if ((krs->current_state == VTSS_TR_TRAIN_LOCAL) || (krs->current_state == VTSS_TR_TRAIN_REMOTE)) {
            krs->current_state = VTSS_TR_SEND_TRAINING;
            krs->remote_rx_ready = FALSE;
        }
    }

    // KR_LPCVALID (Received Coefficent update)
    if ((irq & KR_LPCVALID) && krs->training_started) {
        // Get coef request
        frm.type = VTSS_COEFFICIENT_UPDATE_FRM;
        (void)kr_train_frm_get(vtss_state, port_no, &frm);

        // Apply it and return the results
        kr_coef_set(vtss_state, port_no, frm.data, &krs->tr_res);
        krs->tr_res.coef = frm.data;
        if (krs->ber_training_stage == VTSS_BER_LOCAL_RX_TRAINED) {
            krs->tr_res.status |= BT(15); // Receiver Ready bit
        }

        // Send Status report
        kr_send_sts_report(vtss_state, port_no, krs->tr_res.status);
    }

    // KR_BER_BUSY_1 (LD is doing BER check on receiving train frames)
    if (irq & KR_BER_BUSY_1) {
        kr_ber_training(vtss_state, port_no, KR_BER_BUSY_1);
    }

    // KR_BER_BUSY_0 (BER check is done)
    if (irq & KR_BER_BUSY_0) {
        kr_ber_training(vtss_state, port_no, KR_BER_BUSY_0);
    }

    // KR_LPSVALID (Received Status report)
    if ((irq & KR_LPSVALID) && krs->training_started) {
        if (krs->test_mode) {
            if (krs->test_repeat > 0) {
                krs->current_tap = VTSS_TAP_CM1;
                kr_send_coef_update(vtss_state, krs, port_no, (krs->test_repeat % 2 == 0) ? COEF_HOLD : COEF_DECR);
                krs->test_repeat--;
            } else {
                krs->current_state = VTSS_TR_TRAIN_REMOTE;
                krs->ber_training_stage = VTSS_BER_LOCAL_RX_TRAINED;
                krs->tr_res.status |= BT(15);
                kr_send_sts_report(vtss_state, port_no, krs->tr_res.status);
            }
        } else {
            if (krs->ber_training_stage != VTSS_BER_LOCAL_RX_TRAINED) {
                kr_ber_training(vtss_state, port_no, KR_LPSVALID);
            } else {
                krs->current_state = VTSS_TR_TRAIN_REMOTE;
            }
        }
    }

    // KR_WT_DONE (wait time expired, training is completed)
    if (irq & KR_WT_DONE) {
        if (krs->current_state ==  VTSS_TR_LINK_READY) {
            krs->current_state = VTSS_TR_SEND_DATA;
            krs->training_started = FALSE;
            vtss_port_kr_fw_req_t req_msg = {0};
            req_msg.stop_training = TRUE;
            req_msg.tr_done = TRUE;
            (void)kr_fw_req(vtss_state, port_no, &req_msg);
            krs->signal_detect = TRUE;
        }
    }

    // KR_DME_VIOL_1 (Failure during frame transmission)
    if (irq & KR_DME_VIOL_1 && krs->training_started && (krs->current_state != VTSS_TR_LINK_READY)) {
        kr_ber_training(vtss_state, port_no, KR_DME_VIOL_1);
    }

    // KR_DME_VIOL_0
    // Do nothing

    // KR_REM_RDY_1 (LP is ready)
    if (irq & KR_REM_RDY_1) {
        krs->remote_rx_ready = TRUE;
    }

    // KR_REM_RDY_0 (LP is not happy)
    if (irq & KR_REM_RDY_0 && krs->training_started && (krs->current_state != VTSS_TR_LINK_READY)) {
        krs->remote_rx_ready = FALSE;
    }

    // KR_MW_DONE (Max wait timer expired (72.6.10.3.2))
    if (irq & KR_MW_DONE) {
        kr_send_sts_report(vtss_state, port_no, 0); // Workaround to avoid IRQ failures
        if (krs->training_started) {
            vtss_port_kr_fw_req_t req_msg = {0};
            req_msg.training_failure = TRUE;
            (void)kr_fw_req(vtss_state, port_no, &req_msg);
        }
    }

    // WT_START (Start wait timer to ensure that the LP detects our state (72.6.10.3.2))
    if (krs->current_state == VTSS_TR_TRAIN_REMOTE && krs->remote_rx_ready) {
        // Set the 'Receiver Ready' bit
        krs->tr_res.status |= BT(15);
        kr_send_sts_report(vtss_state, port_no, krs->tr_res.status);
        vtss_port_kr_fw_req_t req_msg = {0};
        req_msg.wt_start = TRUE;
        (void)kr_fw_req(vtss_state, port_no, &req_msg);
        krs->current_state = VTSS_TR_LINK_READY;
    }

    // KR_RATE_DET (parallel detect)
    if (irq & KR_RATE_DET) {
        vtss_port_kr_fw_req_t req_msg = {0};
        req_msg.gen0_tmr_start = TRUE;
        req_msg.rate_done = TRUE;
        (void)kr_fw_req(vtss_state, port_no, &req_msg);
    }

    // KR_AN_RATE (autoneg rate)
    if ((irq & KR_AN_RATE) > 0) {
        vtss_port_kr_fw_req_t req_msg = {0};
        req_msg.rate_done = TRUE;
        (void)kr_fw_req(vtss_state, port_no, &req_msg);
    }

    // KR_NP_RX (next page request)
    if ((irq & KR_NP_RX) > 0) {
        vtss_port_kr_fw_req_t req_msg = {0};
        req_msg.next_page = TRUE;
        (void)kr_fw_req(vtss_state, port_no, &req_msg);
    }

    // Make sure that port.status_get also sees link
    if ((irq & KR_MW_DONE) && krs->training_started && krs->signal_detect) {
        vtss_port_status_t ps;
        VTSS_FUNC(port.status_get, port_no, &ps);
        if (!ps.link) {
            VTSS_E("p:%d No port.status link after MW_DONE - Restart training\n",port_no);
            VTSS_FUNC_COLD(port.kr_conf_set, port_no);
        }
    }


    return VTSS_RC_OK;
}

vtss_rc vtss_port_kr_irq_apply(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               const u32 *const irq_vec)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_D("port_no: %u", port_no);
        rc = kr_irq_apply(vtss_state, port_no, *irq_vec);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_kr_state_get(vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_port_kr_state_t *const state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *state = vtss_state->port.train_state[port_no];
    }
    VTSS_EXIT();
    return rc;
}

#endif //defined(VTSS_FEATURE_PORT_KR_IRQ)
vtss_rc vtss_port_serdes_debug_set(const vtss_inst_t               inst,
                                   const vtss_port_no_t            port_no,
                                   const vtss_port_serdes_debug_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_D("port_no: %u", port_no);
        rc = VTSS_FUNC_COLD(port.serdes_debug_set, port_no, conf);
    }
    VTSS_EXIT();
    return rc;
}

#if VTSS_OPT_DEBUG_PRINT

/* - Debug print --------------------------------------------------- */

static void vtss_port_debug_print_conf(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       const vtss_debug_info_t   *const info)
{
    vtss_port_no_t   port_no;
    vtss_port_map_t  *map;
    vtss_port_conf_t *conf;
    const char       *mode;
    const char       *aneg;
    BOOL             header = 1;
    char             buf[32];

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_PORT))
        return;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no])
            continue;
        if (header) {
            header = 0;
            VTSS_SPRINTF(buf, "Mapping (VTSS_PORTS = %u)", VTSS_PORTS);
            vtss_debug_print_header(pr, buf);
            pr("Port  Chip Port  Chip  ");
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
            pr("Max BW  ");
#endif
            pr("MIIM Bus  MIIM Addr  MIIM Chip\n");
        }
        map = &vtss_state->port.map[port_no];
        pr("%-6u%-11d%-6u", port_no, map->chip_port, map->chip_no);
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        pr("%-8s", map->max_bw == VTSS_BW_1G ? "1G" :
           map->max_bw == VTSS_BW_2G5 ? "2G5" :
           map->max_bw == VTSS_BW_5G  ? "5G" :
           map->max_bw == VTSS_BW_10G ? "10G" :
           map->max_bw == VTSS_BW_25G ? "25G" : "N/A");
#endif
        pr("%-10d%-11u%u\n", map->miim_controller, map->miim_addr, map->miim_chip_no);
    }
    if (!header)
        pr("\n");
    header = 1;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no])
            continue;
        if (header) {
            header = 0;
            vtss_debug_print_header(pr, "Configuration");
            pr("Port  Interface    Serdes     Speed     Aneg  Obey      Generate  ");
#if defined(VTSS_FEATURE_PFC)
            pr("PFC[0-7]  ");
#endif
            pr("Max Length\n");
        }
        conf = &vtss_state->port.conf[port_no];
        switch (conf->speed) {
        case VTSS_SPEED_10M:
            mode = (conf->fdx ? "10fdx" : "10hdx");
            break;
        case VTSS_SPEED_100M:
            mode = (conf->fdx ? "100fdx" : "100hdx");
            break;
        case VTSS_SPEED_1G:
            mode = (conf->fdx ? "1Gfdx" : "1Ghdx");
            break;
        case VTSS_SPEED_2500M:
            mode = (conf->fdx ? "2.5Gfdx" : "2.5Ghdx");
            break;
        case VTSS_SPEED_5G:
            mode = (conf->fdx ? "5Gfdx" : "5Ghdx");
            break;
        case VTSS_SPEED_10G:
            mode = (conf->fdx ? "10Gfdx" : "10Ghdx");
            break;
        case VTSS_SPEED_25G:
            mode = (conf->fdx ? "25Gfdx" : "25Ghdx");
            break;
        default:
            mode = "?";
            break;
        }
        aneg = conf->if_type == VTSS_PORT_INTERFACE_QXGMII ||
               conf->if_type == VTSS_PORT_INTERFACE_SGMII_CISCO ||
               vtss_state->port.clause_37[port_no].enable ? "Yes" : "No";
        VTSS_SPRINTF(buf, "%s", vtss_serdes_if_txt(vtss_state->port.serdes_mode[port_no]));
        if (conf->if_type == VTSS_PORT_INTERFACE_SFI) {
            VTSS_SPRINTF(buf + VTSS_STRLEN(buf), "(%s)",vtss_media_type_if_txt(conf->serdes.media_type));
        }
        pr("%-6u%-13s%-11s%-10s%-6s%-10s%-10s",
           port_no,
           vtss_port_if_txt(conf->if_type),
           buf,
           mode,
           aneg,
           vtss_bool_txt(conf->flow_control.obey),
           vtss_bool_txt(conf->flow_control.generate));
#if defined(VTSS_FEATURE_PFC)
        {
            u8 i;

            for (i = 0; i < VTSS_PRIOS; i++) {
                pr("%u", conf->flow_control.pfc[i] ? 1 : 0);
            }
            pr("  ");
        }
#endif
        pr("%u+%s\n",
           conf->max_frame_length,
           conf->max_tags == VTSS_PORT_MAX_TAGS_NONE ? "0" :
           conf->max_tags == VTSS_PORT_MAX_TAGS_ONE ? "4" :
           conf->max_tags == VTSS_PORT_MAX_TAGS_TWO ? "8" : "?");
    }
    if (!header)
        pr("\n");

#if defined(VTSS_FEATURE_LAYER2)
    header = 1;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_stp_state_t    stp = vtss_state->l2.stp_state[port_no];
        vtss_auth_state_t   auth = vtss_state->l2.auth_state[port_no];
        vtss_port_forward_t fwd = vtss_state->port.forward[port_no];
        if (!info->port_list[port_no])
            continue;
        if (header) {
            header = 0;
            vtss_debug_print_header(pr, "Forwarding");
            pr("Port  State  Forwarding  STP State   Auth State  Rx Fwd    Tx Fwd    Aggr Fwd\n");
        }
        pr("%-6u%-7s%-12s%-12s%-12s%-10s%-10s%s\n",
           port_no,
           vtss_state->l2.port_state[port_no] ? "Up" : "Down",
           fwd == VTSS_PORT_FORWARD_ENABLED ? "Enabled" :
           fwd == VTSS_PORT_FORWARD_DISABLED ? "Disabled" :
           fwd == VTSS_PORT_FORWARD_INGRESS ? "Ingress" :
           fwd == VTSS_PORT_FORWARD_EGRESS ? "Egress" : "?",
           stp == VTSS_STP_STATE_DISCARDING ? "Discarding" :
           stp == VTSS_STP_STATE_LEARNING ? "Learning" :
           stp == VTSS_STP_STATE_FORWARDING  ? "Forwarding" : "?",
           auth == VTSS_AUTH_STATE_NONE ? "None" :
           auth == VTSS_AUTH_STATE_EGRESS ? "Egress" :
           auth == VTSS_AUTH_STATE_BOTH ? "Both" : "?",
           vtss_bool_txt(vtss_state->l2.rx_forward[port_no]),
           vtss_bool_txt(vtss_state->l2.tx_forward[port_no]),
           vtss_bool_txt(vtss_state->l2.tx_forward_aggr[port_no]));
    }
    if (!header)
        pr("\n");
#endif /* VTSS_FEATURE_LAYER2 */
}

/* Print counters in two columns */
static void vtss_debug_port_cnt(const vtss_debug_printf_t pr,
                                const char *col1, const char *col2,
                                vtss_port_counter_t c1, vtss_port_counter_t c2)
{
    char buf[200];

    VTSS_SPRINTF(buf, "Rx %s:", col1);
    pr("%-19s%19" PRIu64 "   ", buf, c1);
    if (col2 != NULL) {
        VTSS_SPRINTF(buf, "Tx %s:", VTSS_STRLEN(col2) ? col2 : col1);
        pr("%-19s%19" PRIu64, buf, c2);
    }
    pr("\n");
}

static void vtss_port_debug_print_counters(vtss_state_t *vtss_state,
                                           const vtss_debug_printf_t pr,
                                           const vtss_debug_info_t   *const info)
{
    vtss_port_no_t                     port_no;
    vtss_port_counters_t               counters;
    vtss_port_rmon_counters_t          *rmon = &counters.rmon;
    vtss_port_if_group_counters_t      *ifg = &counters.if_group;
    vtss_port_ethernet_like_counters_t *eth = &counters.ethernet_like;
    char                               buf[80];

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_PORT_CNT))
        return;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_SELECT_CHIP_PORT_NO(port_no);
        if (!info->port_list[port_no] ||
            VTSS_FUNC(port.counters_get, port_no, &counters) != VTSS_RC_OK)
            continue;
        if (info->clear && VTSS_FUNC(port.counters_clear, port_no) != VTSS_RC_OK)
            continue;
        VTSS_SPRINTF(buf, "Port %u Counters", port_no);
        vtss_debug_print_header(pr, buf);

        /* Basic counters */
        vtss_debug_port_cnt(pr, "Packets", "", rmon->rx_etherStatsPkts,
                            rmon->tx_etherStatsPkts);
        vtss_debug_port_cnt(pr, "Octets", "", rmon->rx_etherStatsOctets,
                            rmon->tx_etherStatsOctets);
        vtss_debug_port_cnt(pr, "Unicast", "", ifg->ifInUcastPkts, ifg->ifOutUcastPkts);
        vtss_debug_port_cnt(pr, "Multicast", "", rmon->rx_etherStatsMulticastPkts,
                            rmon->tx_etherStatsMulticastPkts);
        vtss_debug_port_cnt(pr, "Broadcast", "", rmon->rx_etherStatsBroadcastPkts,
                            rmon->tx_etherStatsBroadcastPkts);
        vtss_debug_port_cnt(pr, "Pause", "", eth->dot3InPauseFrames, eth->dot3OutPauseFrames);
        pr("\n");
        if (!info->full)
            continue;

        /* RMON counters */
        vtss_debug_port_cnt(pr, "64", "", rmon->rx_etherStatsPkts64Octets,
                            rmon->tx_etherStatsPkts64Octets);
        vtss_debug_port_cnt(pr, "65-127", "", rmon->rx_etherStatsPkts65to127Octets,
                            rmon->tx_etherStatsPkts65to127Octets);
        vtss_debug_port_cnt(pr, "128-255", "", rmon->rx_etherStatsPkts128to255Octets,
                            rmon->tx_etherStatsPkts128to255Octets);
        vtss_debug_port_cnt(pr, "256-511", "", rmon->rx_etherStatsPkts256to511Octets,
                            rmon->tx_etherStatsPkts256to511Octets);
        vtss_debug_port_cnt(pr, "512-1023", "", rmon->rx_etherStatsPkts512to1023Octets,
                            rmon->tx_etherStatsPkts512to1023Octets);
        vtss_debug_port_cnt(pr, "1024-1526", "", rmon->rx_etherStatsPkts1024to1518Octets,
                            rmon->tx_etherStatsPkts1024to1518Octets);
        vtss_debug_port_cnt(pr, "1527-    ", "", rmon->rx_etherStatsPkts1519toMaxOctets,
                            rmon->tx_etherStatsPkts1519toMaxOctets);
        pr("\n");

#if defined(VTSS_FEATURE_QOS)
        {
            vtss_port_proprietary_counters_t *prop = &counters.prop;
            vtss_prio_t                      prio;

            /* Priority counters */
            for (prio = VTSS_PRIO_START; prio < VTSS_PRIO_END; prio++) {
                VTSS_SPRINTF(buf, "Class %u", prio);
                vtss_debug_port_cnt(pr, buf, "", prop->rx_prio[prio - VTSS_PRIO_START], prop->tx_prio[prio - VTSS_PRIO_START]);
            }
            pr("\n");
        }
#endif

        /* Drop and error counters */
        vtss_debug_port_cnt(pr, "Drops", "", rmon->rx_etherStatsDropEvents,
                            rmon->tx_etherStatsDropEvents);
        vtss_debug_port_cnt(pr, "CRC/Alignment", "Late/Exc. Coll.",
                            rmon->rx_etherStatsCRCAlignErrors, ifg->ifOutErrors);
        vtss_debug_port_cnt(pr, "Undersize", NULL, rmon->rx_etherStatsUndersizePkts, 0);
        vtss_debug_port_cnt(pr, "Oversize", NULL, rmon->rx_etherStatsOversizePkts, 0);
        vtss_debug_port_cnt(pr, "Fragments", NULL, rmon->rx_etherStatsFragments, 0);
        vtss_debug_port_cnt(pr, "Jabbers", NULL, rmon->rx_etherStatsJabbers, 0);
#if defined(VTSS_FEATURE_PORT_CNT_BRIDGE)
        vtss_debug_port_cnt(pr, "Filtered", NULL, counters.bridge.dot1dTpPortInDiscards, 0);
#endif /* VTSS_FEATURE_PORT_CNT_BRIDGE */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        {
            vtss_port_dot3br_counters_t *dot3br = &counters.dot3br;

            pr("\n");
            vtss_debug_port_cnt(pr, "AssError", NULL, dot3br->aMACMergeFrameAssErrorCount, 0);
            vtss_debug_port_cnt(pr, "SmdError", NULL, dot3br->aMACMergeFrameSmdErrorCount, 0);
            vtss_debug_port_cnt(pr, "AssOk", "HoldCount", dot3br->aMACMergeFrameAssOkCount, dot3br->aMACMergeHoldCount);
            vtss_debug_port_cnt(pr, "FragCount", "", dot3br->aMACMergeFragCountRx, dot3br->aMACMergeFragCountTx);
        }
#endif

#if defined(VTSS_ARCH_CARACAL)
        {
            /* EVC */
            vtss_port_evc_counters_t *evc = &counters.evc;
            vtss_prio_t              prio;

            for (prio = VTSS_PRIO_START; prio < VTSS_PRIO_END; prio++) {
                pr("\nClass %u:\n", prio);
                vtss_debug_port_cnt(pr, "Green", "", evc->rx_green[prio - VTSS_PRIO_START],
                                    evc->tx_green[prio - VTSS_PRIO_START]);
                vtss_debug_port_cnt(pr, "Yellow", "", evc->rx_yellow[prio - VTSS_PRIO_START],
                                    evc->tx_yellow[prio - VTSS_PRIO_START]);
                vtss_debug_port_cnt(pr, "Red", NULL, evc->rx_red[prio - VTSS_PRIO_START], 0);
                vtss_debug_port_cnt(pr, "Green Drops", NULL,
                                    evc->rx_green_discard[prio - VTSS_PRIO_START], 0);
                vtss_debug_port_cnt(pr, "Yellow Drops", NULL,
                                    evc->rx_yellow_discard[prio - VTSS_PRIO_START], 0);
            }
        }
#endif /* VTSS_ARCH_CARACAL */
        pr("\n");
    }
}

void vtss_port_debug_print(vtss_state_t *vtss_state,
                           const vtss_debug_printf_t pr,
                           const vtss_debug_info_t   *const info)
{
    vtss_port_debug_print_conf(vtss_state, pr, info);
    vtss_port_debug_print_counters(vtss_state, pr, info);
}
#endif // VTSS_OPT_DEBUG_PRINT

#endif /* VTSS_FEATURE_PORT_CONTROL */
