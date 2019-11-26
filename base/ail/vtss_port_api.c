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
    vtss_port_conf_t old_conf;
#if defined(VTSS_FEATURE_AFI_SWC)
    BOOL             afi_link;
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

    old_conf = vtss_state->port.conf[port_no];
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

    if ((rc = VTSS_FUNC_COLD(port.conf_set, port_no)) != VTSS_RC_OK) {
        // Operation failed. Restore old configuration.
        vtss_state->port.conf[port_no] = old_conf;
        (void)VTSS_FUNC_COLD(port.conf_set, port_no);
    } else {
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
            memcmp(&vtss_state->port.conf[port_no], conf, sizeof(*conf)) == 0) {
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
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (port_no == vtss_state->packet.npi_conf.port_no) {
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

static vtss_rc vtss_port_clause_37_status_get(vtss_state_t         *vtss_state,
                                              const vtss_port_no_t port_no,
                                              vtss_port_status_t   *const status)
{
    vtss_rc                       rc;
    vtss_port_clause_37_status_t  clause_37_status;
    vtss_port_clause_37_control_t *control;
    vtss_port_clause_37_adv_t     *adv, *lp;
    VTSS_N("port_no: %u", port_no);
    memset(&clause_37_status, 0, sizeof(clause_37_status)); /* Please Lint */
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
            if (clause_37_status.autoneg.partner_adv_sgmii.speed_1G) {
                status->speed = VTSS_SPEED_1G;
            } else if (clause_37_status.autoneg.partner_adv_sgmii.speed_100M) {
                status->speed = VTSS_SPEED_100M;
            } else {
                status->speed = VTSS_SPEED_10M;
            }
            status->fdx = clause_37_status.autoneg.partner_adv_sgmii.fdx;
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
            lp = &clause_37_status.autoneg.partner_advertisement;
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

#if defined(VTSS_CHIP_10G_PHY)
static vtss_rc vtss_cmn_clause_37_status_get(const vtss_inst_t  inst,
                                                  const vtss_port_no_t port_no,
                                                  vtss_port_status_t   *const status)
{
    vtss_state_t *vtss_state;
    vtss_phy_10g_clause_37_cmn_status_t clause_37_status;
    vtss_phy_10g_clause_37_control_t *control;
    vtss_phy_10g_clause_37_adv_t     *adv, *lp;

    memset(status, 0, sizeof(*status));
    VTSS_RC(vtss_inst_port_no_check(inst, &vtss_state, port_no));
    VTSS_RC(vtss_phy_10g_clause_37_status_get(inst, port_no, &clause_37_status));
    status->link_down = (clause_37_status.host.link & clause_37_status.line.link) ? 0 : 1;
    status->aneg_complete = clause_37_status.host.autoneg.complete & clause_37_status.line.autoneg.complete;

    if (status->link_down) {
        /* Link has been down, so get the current status */
        VTSS_RC(vtss_phy_10g_clause_37_status_get(inst, port_no, &clause_37_status));
        status->link = clause_37_status.host.link & clause_37_status.line.link;
    } else {
        status->link = 1;  /* Link is still up */
    }

    if (status->link == 0) {
        return VTSS_RC_OK;    /* Link is still down */
    }

    control = &vtss_state->phy_10g_state[port_no].clause_37;

    if (control->enable) {
        /* Auto-negotiation enabled */
        adv = &control->advertisement;
        lp = &clause_37_status.line.autoneg.partner_advertisement;
        if (status->aneg_complete) {
            /* Speed and duplex mode auto negotiation result */
            if (adv->fdx && lp->fdx) {
                status->speed = VTSS_SPEED_1G;
                status->fdx = 1;
            } else if (adv->hdx && lp->hdx) {
                status->speed = VTSS_SPEED_1G;
                status->fdx = 0;
            } else {
                status->link = 0;
            }

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
            if (lp->remote_fault != VTSS_PHY_10G_CLAUSE_37_RF_LINK_OK)
                status->remote_fault = 1;
        } else {
            /* Autoneg says that the link partner is not OK */
            status->link = 0;
        }
    } else {
        /* Forced speed */
        status->speed = VTSS_SPEED_1G;
        status->fdx = 1;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_CHIP_10G_PHY */

vtss_rc vtss_port_status_get(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             vtss_port_status_t    *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("port_no: %u", port_no);

    /* Initialize status */
    memset(status, 0, sizeof(*status));
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        switch (vtss_state->port.conf[port_no].if_type) {
            case VTSS_PORT_INTERFACE_RGMII:
            case VTSS_PORT_INTERFACE_SGMII:
            case VTSS_PORT_INTERFACE_SGMII_2G5:
            case VTSS_PORT_INTERFACE_QSGMII:
            case VTSS_PORT_INTERFACE_SXGMII:
            case VTSS_PORT_INTERFACE_USGMII:
            case VTSS_PORT_INTERFACE_QXGMII:
            case VTSS_PORT_INTERFACE_DXGMII_5G:
            case VTSS_PORT_INTERFACE_DXGMII_10G:
#if defined(VTSS_CHIP_CU_PHY)
                rc = vtss_phy_status_get_private(vtss_state, port_no, status);
#endif /* VTSS_CHIP_CU_PHY */
                break;
            case VTSS_PORT_INTERFACE_SERDES:
            case VTSS_PORT_INTERFACE_SGMII_CISCO:
                rc = vtss_port_clause_37_status_get(vtss_state, port_no, status);
                break;
            default:
                rc = VTSS_FUNC(port.status_get, port_no, status);
                break;
        }
    }
    VTSS_EXIT();

#if defined(VTSS_CHIP_10G_PHY)
    /* If a 10G PHY (Venice) is connected to the switch-port and is in 1G serdes mode, */
    /* we need to get the combined status of the switch port and 10G phy. */
    vtss_phy_10g_id_t phy_id;
    vtss_port_status_t status_10g;
    if ((rc == VTSS_RC_OK) && (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SERDES || vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SFI)) {
        if ((vtss_phy_10g_id_get(inst, port_no, &phy_id) == VTSS_RC_OK) && (phy_id.family == VTSS_PHY_FAMILY_VENICE || phy_id.family == VTSS_PHY_FAMILY_MALIBU)) {
            if (vtss_state->phy_10g_state[port_no].mode.oper_mode == VTSS_PHY_1G_MODE) {
                VTSS_RC(vtss_cmn_clause_37_status_get(inst, port_no, &status_10g));
                status->link_down = status->link_down | status_10g.link_down; /* Link status from switch port and Phy */
                status->link = status->link & status_10g.link;
                status->remote_fault = status->remote_fault | status_10g.remote_fault;
                status->aneg =  status_10g.aneg;
            }
        }
    }
#if defined(VTSS_FEATURE_MACSEC)
    if ((rc == VTSS_RC_OK) && (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_XAUI || vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SFI || vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SERDES)) {
        /* If the Host MAC in the Phy is enabled then the Switch will always see link. In this case we need to add a Phy link check. */
        if ((vtss_phy_10g_id_get(inst, port_no, &phy_id) == VTSS_RC_OK) && (phy_id.family == VTSS_PHY_FAMILY_VENICE || phy_id.family == VTSS_PHY_FAMILY_MALIBU)) {
            vtss_phy_10g_status_t status_phy;
            VTSS_RC(vtss_phy_10g_status_get(inst, port_no, &status_phy));
            //status->link = status_phy.pma.rx_link && status_phy.pcs.rx_link && status_phy.xs.rx_link && status->link;
            VTSS_I("port %u Host link %s  PHY link %s \n",port_no,status->link ? "UP" : "DOWN",status_phy.status ? "UP" : "DOWN");
            status->link = status->link && status_phy.status ;
        }
    }
#endif /* VTSS_FEATURE_MACSEC */
#endif /* VTSS_CHIP_10G_PHY   */
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
static vtss_rc vtss_port_miim_read(const vtss_inst_t    inst,
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
static vtss_rc vtss_port_miim_write(const vtss_inst_t    inst,
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

    memset(&old, 0, sizeof(old)); /* Please Lint */
    if ((rc = VTSS_FUNC(port.conf_get, port_no, &old)) == VTSS_RC_OK &&
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
#if defined(VTSS_ARCH_SERVAL)
        VTSS_FUNC_RC(port.ifh_set, port_no);
#endif /* VTSS_ARCH_SERVAL */

    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_WARM_START */

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_port_inst_create(vtss_state_t *vtss_state)
{
    vtss_port_no_t   port_no;
    vtss_init_conf_t *init_conf = &vtss_state->init_conf;

    init_conf->miim_read = vtss_port_miim_read;
    init_conf->miim_write = vtss_port_miim_write;
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

vtss_port_no_t vtss_cmn_port2port_no(vtss_state_t *vtss_state,
                                     const vtss_debug_info_t *const info, u32 chip_port)
{
    vtss_port_no_t port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (VTSS_CHIP_PORT(port_no) == chip_port && VTSS_PORT_CHIP_SELECTED(port_no)) {
            if (info->port_list[port_no])
                return port_no;
            break;
        }
    }
    return VTSS_PORT_NO_NONE;
}

vtss_port_no_t vtss_api_port(vtss_state_t *vtss_state, u32 chip_port)
{
    vtss_port_no_t port_no;

    /* Map from chip port to API port */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (VTSS_CHIP_PORT(port_no) == chip_port) {
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

#if defined(VTSS_FEATURE_10GBASE_KR_V2)
/* - 10GBase KR --------------------------------------------------- */
vtss_rc vtss_port_10g_kr_fw_req(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_port_10g_kr_fw_req_t *const fw_req)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(port.kr_fw_req, port_no, fw_req);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_10g_kr_status_get(const vtss_inst_t inst,
                                    const vtss_port_no_t port_no,
                                    vtss_port_10g_kr_status_t *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(port.kr_status, port_no, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_10g_kr_conf_set(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  const vtss_port_10g_kr_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->port.kr_conf[port_no] = *conf;
        rc = VTSS_FUNC_COLD(port.kr_conf_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_10g_kr_conf_get(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  vtss_port_10g_kr_conf_t *const conf)
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

#endif /* VTSS_FEATURE_10GBASE_KR_V2 */

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
        switch (vtss_state->port.conf[port_no].if_type) {
        case VTSS_PORT_INTERFACE_RGMII:
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_SGMII_2G5:
        case VTSS_PORT_INTERFACE_QSGMII:
        {
#if defined(VTSS_CHIP_CU_PHY)
            /* PHY loopback is used */
            vtss_phy_loopback_t loopback;

            memset(&loopback, 0, sizeof(loopback));
            switch (conf->loopback) {
            case VTSS_PORT_LB_NEAR_END:
                loopback.near_end_enable = TRUE;
                break;
            case VTSS_PORT_LB_FAR_END:
                loopback.far_end_enable = TRUE;
                break;
            case VTSS_PORT_LB_FACILITY:
                loopback.mac_serdes_facility_enable = TRUE;
                break;
            case VTSS_PORT_LB_EQUIPMENT:
                loopback.mac_serdes_equipment_enable = TRUE;
                break;
            default:
                break;
            }
            VTSS_EXIT();
            rc = vtss_phy_loopback_set(inst, port_no, loopback);
            VTSS_ENTER();
#endif /* VTSS_CHIP_CU_PHY */
            break;
        }
        default:
            rc = VTSS_RC_OK;
            break;
        }
    }
    if (rc == VTSS_RC_OK) {
        vtss_state->port.test_conf[port_no] = *conf;
        rc = VTSS_FUNC_COLD(port.test_conf_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}


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
            sprintf(buf, "Mapping (VTSS_PORTS = %u)", VTSS_PORTS);
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
            pr("Port  Interface    Serdes     Speed     Aneg  Obey      Generate  Max Length\n");
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
        aneg = vtss_state->port.clause_37[port_no].enable ? "Yes" : "No";
        sprintf(buf, "%s", vtss_serdes_if_txt(vtss_state->port.serdes_mode[port_no]));
        if (conf->if_type == VTSS_PORT_INTERFACE_SFI) {
            sprintf(buf + strlen(buf), "(%s)",vtss_media_type_if_txt(conf->serdes.media_type));
        }
        pr("%-6u%-13s%-11s%-10s%-6s%-10s%-10s%u+%s\n",
           port_no,
           vtss_port_if_txt(conf->if_type),
           buf,
           mode,
           aneg,
           vtss_bool_txt(conf->flow_control.obey),
           vtss_bool_txt(conf->flow_control.generate),
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

    sprintf(buf, "Rx %s:", col1);
    pr("%-19s%19" PRIu64 "   ", buf, c1);
    if (col2 != NULL) {
        sprintf(buf, "Tx %s:", strlen(col2) ? col2 : col1);
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
        sprintf(buf, "Port %u Counters", port_no);
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
                sprintf(buf, "Class %u", prio);
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

#endif /* VTSS_FEATURE_PORT_CONTROL */
