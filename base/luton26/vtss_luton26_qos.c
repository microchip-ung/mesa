// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_luton26_cil.h"

#if defined(VTSS_ARCH_LUTON26)

/* - CIL functions ------------------------------------------------- */

#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
static vtss_rc l26_evc_policer_move(vtss_state_t *vtss_state, u32 policer)
{
    vtss_policer_alloc_t *pol_alloc;
    u32                  policer_id;

    VTSS_I("policer: %u", policer);

    /* Look for the ACL policer mapping to this Luton26 policer */
    for (policer_id = 0; policer_id < VTSS_EVC_POLICERS; policer_id++) {
        pol_alloc = &vtss_state->qos.evc_policer_alloc[policer_id];
        if (pol_alloc->count && pol_alloc->policer == policer) {
            VTSS_I("EVC policer: %u", policer_id);

            /* Find new free policer */
            VTSS_RC(vtss_l26_policer_free_get(vtss_state, &pol_alloc->policer));

            /* Update new EVC policer */
            VTSS_RC(vtss_l26_evc_policer_conf_set(vtss_state, policer_id));

            /* Update rules to point to new policer */
            VTSS_RC(vtss_l26_acl_evc_policer_move(vtss_state, VTSS_POLICER_USER_EVC, policer_id, 
                                                  policer, pol_alloc->policer));
            break;
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_l26_evc_policer_conf_set(vtss_state_t *vtss_state,
                                      const vtss_evc_policer_id_t policer_id)
{
    vtss_evc_policer_conf_t *conf = &vtss_state->qos.evc_policer_conf[policer_id];
    vtss_policer_alloc_t    *pol_alloc = &vtss_state->qos.evc_policer_alloc[policer_id];
    vtss_l26_policer_conf_t cfg;

    /* Only setup policer if allocated */
    if (pol_alloc->count == 0)
        return VTSS_RC_OK;

    /* Convert to Luton26 policer configuration */
    VTSS_MEMSET(&cfg, 0, sizeof(cfg));
    cfg.dual = 1;
    cfg.data_rate = (conf->line_rate ? 0 : 1);
    if (conf->enable) {
        /* Use configured values if policer enabled */
        switch (conf->type) {
        case VTSS_POLICER_TYPE_MEF:
            cfg.cir = conf->cir;
            cfg.cbs = conf->cbs;
            cfg.eir = conf->eir;
            cfg.ebs = conf->ebs;
            cfg.cf = conf->cf;
            break;
        case VTSS_POLICER_TYPE_SINGLE:
        default:
            cfg.dual = 0;
            cfg.eir = conf->cir;
            cfg.ebs = conf->cbs;
            break;
        }
    } else {
        /* Use maximum rates if policer disabled */
        cfg.cir = 100000000; /* 100 Gbps, will be rounded down */
        cfg.eir = 100000000; /* 100 Gbps, will be rounded down */
        cfg.cbs = 4*1024; /* 4 kB burst size */
        cfg.ebs = 4*1024; /* 4 kB burst size */
    }
    return vtss_l26_policer_conf_set(vtss_state, VTSS_POLICER_USER_EVC, pol_alloc->policer, 1, &cfg);
}
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */

/* 
   Configure one of the shared 256 policers.
   A policer can be configured if it is free or owned by the same user.
   A special case is when the policer is owned by ACL or EVC and another user wants to allocate it.
   In this case the ACL or the EVE subsystem is asked to use another policer.
   If this operation succeeds, the policer is free and can be allocated as normal.

   This function is reentrant and can be used directly inside the ACL/EVC move function
   in order to deallocate the policer.
*/
vtss_rc vtss_l26_policer_conf_set(vtss_state_t *vtss_state,
                                  vtss_policer_user_t user, u32 policer, BOOL enable, vtss_l26_policer_conf_t *conf)
{
    vtss_policer_user_t owner;
    u32 cir = 0;
    u32 cbs = 0;
    u32 pir = 0;
    u32 pbs = 0;
    u32 mode = POL_MODE_LINERATE;
    u32 cir_ena = 0;
    u32 cf = 0;
    u32 value;
    
    if ((user == VTSS_POLICER_USER_NONE) || (user >= VTSS_POLICER_USER_CNT)) {
        VTSS_E("illegal user: %d", user);
        return VTSS_RC_ERROR;
    }

    if (policer >= VTSS_L26_POLICER_CNT) {
        VTSS_E("illegal policer: %u", policer);
        return VTSS_RC_ERROR;
    }

    owner = vtss_state->qos.policer_user[policer];

    if (enable) {
        if (conf == NULL) {
            VTSS_E("conf == NULL");
            return VTSS_RC_ERROR;
        }

        /* Verify user versus owner */
        if (owner != user) {
            /* Policer is occupied by someone else */
            switch (owner) {
            case VTSS_POLICER_USER_NONE:
                /* Free entry, no problem */
                break;
            case VTSS_POLICER_USER_ACL:
                if (vtss_l26_acl_policer_move(vtss_state, policer) != VTSS_RC_OK) {
                    VTSS_I("unable to move ACL policer %u", policer);
                    return VTSS_RC_ERROR;
                }
                break;
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
            case VTSS_POLICER_USER_EVC:
                if (l26_evc_policer_move(vtss_state, policer) != VTSS_RC_OK) {
                    VTSS_I("unable to move EVC policer %u", policer);
                    return VTSS_RC_ERROR;
                } 
                break;
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
            default:
                VTSS_I("Unmovable policer %u occupied by user %d", policer, owner);
                return VTSS_RC_ERROR;
            }
        }

        /* Calculate register fields */
        pir = conf->eir;
        pbs = conf->ebs;
        if (conf->frame_rate) {
            /* Frame rate policing (single leaky bucket) */
            if (pir >= 100) {
                mode = POL_MODE_FRMRATE_100FPS;
                pir  = (pir + 99) / 100; /* Resolution is in steps of 100 fps */
                pbs  = (pbs * 10 / 328); /* Burst unit is 32.8 frames */
                pbs++; /* Round up burst size */
                pbs  = MIN(VTSS_BITMASK(6),  pbs); /* Limit burst to the maximum value */
            } else {
                mode = POL_MODE_FRMRATE_1FPS;
                pbs  = (pbs * 10 / 3); /* Burst unit is 0.3 frames */
                pbs++; /* Round up burst size */
                pbs  = MIN(60, pbs); /* See Bugzilla#4944, comment#2 */
            }
        } else {
            /* Bit rate policing */
            if (conf->data_rate)
                mode = POL_MODE_DATARATE;
            if (conf->dual) {
                /* Dual leaky bucket mode */
                cir = (conf->cir + 99) / 100;  /* Rate unit is 100 kbps. Round up to next possible value */
                cbs = (conf->cbs ? conf->cbs : 1); /* BZ 9813: Avoid using zero burst size */
                cbs = (cbs + 4095) / 4096; /* Burst unit is 4kB. Round up to next possible value */
                cbs  = MIN(61, cbs); /* See Bugzilla#4944, comment#2  */
                cir_ena = 1;
                cf = conf->cf;
                if (cf)
                    pir += conf->cir;
            }
            pir  = (pir + 99) / 100;  /* Rate unit is 100 kbps. Round up to next possible value */
            pbs = (pbs ? pbs : 1);    /* BZ 9813: Avoid using zero burst size */
            pbs  = (pbs + 4095) / 4096; /* Burst unit is 4kB. Round up to next possible value */
            pbs  = MIN(61, pbs); /* See Bugzilla#4944, comment#2  */
        }
    
        /* Limit rate to the maximum value */
        pir  = MIN(VTSS_BITMASK(15), pir);
        cir  = MIN(VTSS_BITMASK(15), cir);

        /* Set current user */
        vtss_state->qos.policer_user[policer] = user;
    } else { /* Disable policer */
        /* Verify user versus owner */
        if (owner != user) {
            /* Silently ignore if a user (e.g. QoS) disables a policer it has not allocated */
            return VTSS_RC_OK;
        }
        /* Clear current user */
        vtss_state->qos.policer_user[policer] = VTSS_POLICER_USER_NONE;
    }
    
    /* Begin of work around part 1 for Bugzilla#3253 Comment#2:
     * ==================================================================
     * FYI;
     * It was not possible to make an ECO directly accessing the bit, so:
     * To set overshoot_ena, set cir_ena=0, dlb_coupled=1
     * To clr overshoot_ena, set cir_ena=0, dlb_coupled=0
     * To keep overshoot_ena, set cir_ena=1, dlb_coupled=X
     *
     * To get overshoot_ena, read the field as for any other field.
     * ==================================================================
     *
     * The following code enables OVERSHOOT_ENA
     */
    value = (VTSS_F_SYS_POL_POL_MODE_CFG_IPG_SIZE(20) |
             VTSS_F_SYS_POL_POL_MODE_CFG_FRM_MODE(mode) |
             VTSS_F_SYS_POL_POL_MODE_CFG_DLB_COUPLED |
             VTSS_F_SYS_POL_POL_MODE_CFG_OVERSHOOT_ENA);
    L26_WR(VTSS_SYS_POL_POL_MODE_CFG(policer), value);
    /* End of work around part 1 for Bugzilla#3253 Comment#2 */

    /* Setup policer registers */
    value = (VTSS_F_SYS_POL_POL_MODE_CFG_IPG_SIZE(20) |
             VTSS_F_SYS_POL_POL_MODE_CFG_FRM_MODE(mode) |
             VTSS_F_SYS_POL_POL_MODE_CFG_OVERSHOOT_ENA);
    if (cir_ena) {
        value |= VTSS_F_SYS_POL_POL_MODE_CFG_CIR_ENA;
        if (cf) {
            value |= VTSS_F_SYS_POL_POL_MODE_CFG_DLB_COUPLED;
        }
    } else {
        /* Begin of work around part 2 for Bugzilla#3253 Comment#2: */
        value |= VTSS_F_SYS_POL_POL_MODE_CFG_DLB_COUPLED; /* DBL_COUPLED controls OVERSHOOT_ENA when CIR_ENA is 0. */
        /* End of work around part 2 for Bugzilla#3253 Comment#2: */
    }
    L26_WR(VTSS_SYS_POL_POL_MODE_CFG(policer), value);
    L26_WR(VTSS_SYS_POL_POL_PIR_CFG(policer), 
           VTSS_F_SYS_POL_POL_PIR_CFG_PIR_RATE(pir) |
           VTSS_F_SYS_POL_POL_PIR_CFG_PIR_BURST(pbs));
    L26_WR(VTSS_SYS_POL_POL_CIR_CFG(policer), 
           VTSS_F_SYS_POL_POL_CIR_CFG_CIR_RATE(cir) |
           VTSS_F_SYS_POL_POL_CIR_CFG_CIR_BURST(cbs));
    L26_WR(VTSS_SYS_POL_POL_PIR_STATE(policer), 0); /* Reset current fill level */
    L26_WR(VTSS_SYS_POL_POL_CIR_STATE(policer), 0); /* Reset current fill level */

    return VTSS_RC_OK;
}

/* Get first free policer */
vtss_rc vtss_l26_policer_free_get(vtss_state_t *vtss_state, u16 *new)
{
    u16 policer;

    /* Look for free policer starting from above */
    for (policer = 0; policer < VTSS_L26_POLICER_CNT; policer++) {
        if (vtss_state->qos.policer_user[policer] == VTSS_POLICER_USER_NONE) {
            *new = policer;
            return VTSS_RC_OK;
        }
    }
    return VTSS_RC_ERROR;
}

#define L26_DEFAULT_POL_ORDER 0x1d3 /* Luton 26 policer order: Serial (QoS -> Port -> ACL) */

vtss_rc vtss_l26_port_policer_fc_set(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no, u32 chipport)
{
    vtss_port_conf_t *port_conf = &vtss_state->port.conf[port_no];
    vtss_qos_port_conf_t *qos_conf = &vtss_state->qos.port_conf[port_no];
    u32 fc_new = (port_conf->flow_control.generate &&
                  (qos_conf->policer_port[0].rate != VTSS_BITRATE_DISABLED) &&
                  qos_conf->policer_ext_port[0].flow_control) ? 1 : 0;
    u32 fc_old;

    L26_RD(VTSS_SYS_POL_MISC_POL_FLOWC(chipport), &fc_old);

    VTSS_I("port_no: %u, port: %u, fc_old: %u, fc_new: %u", port_no, chipport, fc_old, fc_new);

    if (fc_old != fc_new) {
        if (fc_new) { /* Disabled -> Enabled */
            L26_WR(VTSS_SYS_POL_MISC_POL_FLOWC(chipport), 1);
        } else { /* Enabled -> Disabled - Bug#12745: Do the following steps: */
            u32 port_cfg, pir_cfg, cir_cfg;

            /* 1: Save registers that will be modified */
            L26_RD(VTSS_SYS_POL_POL_PIR_CFG(chipport), &pir_cfg);
            L26_RD(VTSS_SYS_POL_POL_CIR_CFG(chipport), &cir_cfg);
            L26_RD(VTSS_ANA_PORT_PORT_CFG(chipport),   &port_cfg);

            /* 2: Stop the ingress traffic */
            L26_WRM_CLR(VTSS_ANA_PORT_PORT_CFG(chipport), VTSS_F_ANA_PORT_PORT_CFG_RECV_ENA);

            /* 3: Set burst size to max in order to empty the policer */
            L26_WRM_SET(VTSS_SYS_POL_POL_PIR_CFG(chipport), VTSS_F_SYS_POL_POL_PIR_CFG_PIR_BURST(0x3f));
            L26_WRM_SET(VTSS_SYS_POL_POL_CIR_CFG(chipport), VTSS_F_SYS_POL_POL_CIR_CFG_CIR_BURST(0x3f));

            /* 4: Wait 100uS */
            VTSS_NSLEEP(100000);

            /* 5: Disable flow control */
            L26_WR(VTSS_SYS_POL_MISC_POL_FLOWC(chipport), 0);

            /* 6: Restore saved registers */
            L26_WR(VTSS_SYS_POL_POL_PIR_CFG(chipport), pir_cfg);
            L26_WR(VTSS_SYS_POL_POL_CIR_CFG(chipport), cir_cfg);
            L26_WR(VTSS_ANA_PORT_PORT_CFG(chipport),   port_cfg);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_port_policer_set(vtss_state_t *vtss_state, vtss_port_no_t port_no, 
                                    u32 port, BOOL enable, vtss_l26_policer_conf_t *conf)
{
    BOOL redir_8021 = FALSE;
    BOOL redir_ip   = FALSE;
    u32  order      = L26_DEFAULT_POL_ORDER;

    VTSS_RC(vtss_l26_port_policer_fc_set(vtss_state, port_no, port));

    VTSS_RC(vtss_l26_policer_conf_set(vtss_state, VTSS_POLICER_USER_PORT, port, enable, conf));

    L26_WRM(VTSS_ANA_PORT_POL_CFG(port), 
            (redir_8021   ? VTSS_F_ANA_PORT_POL_CFG_POL_CPU_REDIR_8021 : 0) |
            (redir_ip     ? VTSS_F_ANA_PORT_POL_CFG_POL_CPU_REDIR_IP   : 0) |
            (enable       ? VTSS_F_ANA_PORT_POL_CFG_PORT_POL_ENA       : 0) |
            VTSS_F_ANA_PORT_POL_CFG_POL_ORDER(order),
            VTSS_F_ANA_PORT_POL_CFG_POL_CPU_REDIR_8021 |
            VTSS_F_ANA_PORT_POL_CFG_POL_CPU_REDIR_IP   |
            VTSS_F_ANA_PORT_POL_CFG_PORT_POL_ENA       |
            VTSS_M_ANA_PORT_POL_CFG_POL_ORDER);

    return VTSS_RC_OK;
}

static vtss_rc l26_queue_policer_set(vtss_state_t *vtss_state,
                                     u32 port, u32 queue, BOOL enable, vtss_l26_policer_conf_t *conf)
{
    VTSS_RC(vtss_l26_policer_conf_set(vtss_state, VTSS_POLICER_USER_QUEUE, 32 + port * 8 + queue, enable, conf));

    L26_WRM(VTSS_ANA_PORT_POL_CFG(port), 
            (enable       ? VTSS_F_ANA_PORT_POL_CFG_QUEUE_POL_ENA(VTSS_BIT(queue)): 0),
            VTSS_F_ANA_PORT_POL_CFG_QUEUE_POL_ENA(VTSS_BIT(queue)));

    return VTSS_RC_OK;
}

static u32 l26_packet_rate(vtss_packet_rate_t rate, u32 *unit)
{
    int i;
    u32 new_rate;

    if (rate > 512) {
        /* Supported rate = 1k, 2k, 4k, 8k, 16k, 32k, 64k, 128k, 256k, 512k and 1024k frames per second*/
        new_rate = (rate + 999) / 1000; /* Round up */
        *unit = 0; /* Base unit is 1 kiloframes per second */
    } else {
        /* Supported rate = 1, 2, 4, 8, 16, 32, 64, 128, 256 and 512 frames per second */
        new_rate = rate;
        *unit = 1; /* Base unit is 1 frame per second */
    }

    for (i = 0; i < 10; i++) {
        if ((u32)(1 << i) >= new_rate) { /* 2^i is equal to or higher than new_rate */
            break;
        }
    }

    /*
     * Note that we return 10 if there is no match in the for loop above.
     * This is the maximum allowed rate of 2^10 = 1024 kiloframes per second
     */
    return i;
}

static u32 l26_storm_mode(vtss_packet_rate_t rate, vtss_storm_policer_mode_t mode)
{
    if (rate == VTSS_PACKET_RATE_DISABLED) {
        return 0; /* Disabled */
    }

    switch (mode) {
    case VTSS_STORM_POLICER_MODE_PORTS_AND_CPU:
        return 3; /* Police both CPU and front port destinations */
    case VTSS_STORM_POLICER_MODE_PORTS_ONLY:
        return 2; /* Police front port destinations only */
    case VTSS_STORM_POLICER_MODE_CPU_ONLY:
        return 1; /* Police CPU destination only */
    default:
        return 0; /* Disabled */
    }
}

static vtss_rc l26_qcl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    BOOL dmac_dip = vtss_state->qos.port_conf[port_no].dmac_dip;
    u32  mask = VTSS_F_ANA_PORT_VCAP_CFG_S1_DMAC_DIP_ENA(2);
    u32  port = VTSS_CHIP_PORT(port_no);

    /* Enable/disable DMAC/DIP match in second IS1 lookup */
    L26_WRM(VTSS_ANA_PORT_VCAP_CFG(port), dmac_dip ? mask : 0, mask);

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_qos_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t *conf = &vtss_state->qos.port_conf[port_no];
    u32 port = VTSS_CHIP_PORT(port_no);
    int pcp, dei, queue, class, dpl;
    u8 cost[6];
    vtss_l26_policer_conf_t pol_cfg;
    u32  tag_remark_mode, shaping_ena = 0, exs_ena = 0, avb_ena = 0, m;
    BOOL tag_default_dei;

    /* Port default PCP and DEI configuration */
    L26_WRM(VTSS_ANA_PORT_VLAN_CFG(port),
            (conf->default_dei ? VTSS_F_ANA_PORT_VLAN_CFG_VLAN_DEI : 0) |
            VTSS_F_ANA_PORT_VLAN_CFG_VLAN_PCP(conf->usr_prio),
            VTSS_F_ANA_PORT_VLAN_CFG_VLAN_DEI                           |
            VTSS_M_ANA_PORT_VLAN_CFG_VLAN_PCP);
    
    /* Port default QoS class, DP level, tagged frames mode, DSCP mode and DSCP remarking configuration */
    L26_WR(VTSS_ANA_PORT_QOS_CFG(port),
           (conf->default_dpl ? VTSS_F_ANA_PORT_QOS_CFG_DP_DEFAULT_VAL : 0)           |
           VTSS_F_ANA_PORT_QOS_CFG_QOS_DEFAULT_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->default_prio)) |
           (conf->tag_class_enable ? VTSS_F_ANA_PORT_QOS_CFG_QOS_PCP_ENA : 0)         |
           (conf->dscp_class_enable ? VTSS_F_ANA_PORT_QOS_CFG_QOS_DSCP_ENA : 0)       |
           (conf->dscp_translate ? VTSS_F_ANA_PORT_QOS_CFG_DSCP_TRANSLATE_ENA : 0)    |
           VTSS_F_ANA_PORT_QOS_CFG_DSCP_REWR_CFG(conf->dscp_mode));

    /* Egress DSCP remarking configuration */
    L26_WR(VTSS_REW_PORT_DSCP_CFG(port), VTSS_F_REW_PORT_DSCP_CFG_DSCP_REWR_CFG(conf->dscp_emode));

    /* Map for (PCP and DEI) to (QoS class and DP level */
    for (pcp = VTSS_PCP_START; pcp < VTSS_PCP_END; pcp++) {
        for (dei = VTSS_DEI_START; dei < VTSS_DEI_END; dei++) {
            L26_WR(VTSS_ANA_PORT_QOS_PCP_DEI_MAP_CFG(port, (8*dei + pcp)),
                   (conf->dp_level_map[pcp][dei] ? VTSS_F_ANA_PORT_QOS_PCP_DEI_MAP_CFG_DP_PCP_DEI_VAL : 0) |
                   VTSS_F_ANA_PORT_QOS_PCP_DEI_MAP_CFG_QOS_PCP_DEI_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->qos_class_map[pcp][dei])));
        }
    }

    /* Enable gap value adjustment */
    L26_WR(VTSS_SYS_SCH_LB_DWRR_CFG(port), VTSS_F_SYS_SCH_LB_DWRR_CFG_FRM_ADJ_ENA);

    /* DWRR configuration */
    VTSS_RC(vtss_cmn_qos_weight2cost(conf->queue_pct, cost, 6, 5));
    L26_WR(VTSS_SYS_SCH_SCH_DWRR_CFG(port),
           (conf->dwrr_enable ? VTSS_F_SYS_SCH_SCH_DWRR_CFG_DWRR_MODE : 0) |
           VTSS_X_SYS_SCH_SCH_DWRR_CFG_COST_CFG(
               VTSS_ENCODE_BITFIELD(cost[0],  0, 5) |
               VTSS_ENCODE_BITFIELD(cost[1],  5, 5) |
               VTSS_ENCODE_BITFIELD(cost[2], 10, 5) |
               VTSS_ENCODE_BITFIELD(cost[3], 15, 5) |
               VTSS_ENCODE_BITFIELD(cost[4], 20, 5) |
               VTSS_ENCODE_BITFIELD(cost[5], 25, 5)));

    /* Egress port shaper burst level configuration
     * The value is rounded up to the next possible value:
     *           0 -> 0 (Always closed)
     *    1.. 4096 -> 1 ( 4 KB)
     * 4097.. 8192 -> 2 ( 8 KB)
     * 8193..12288 -> 3 (12 KB)
     */
    L26_WR(VTSS_SYS_SCH_LB_LB_THRES(((9 * port) + 8)),
           VTSS_F_SYS_SCH_LB_LB_THRES_LB_THRES(MIN(0x3f, ((conf->shaper_port.level + 4095) / 4096))));

    /* Egress port shaper rate configuration
     * The value (in kbps) is rounded up to the next possible value:
     *        0 -> 0 (Open until burst capacity is used, then closed)
     *   1..100 -> 1 (100160 bps)
     * 101..200 -> 2 (200320 bps)
     * 201..300 -> 3 (300480 bps)
     */
    L26_WR(VTSS_SYS_SCH_LB_LB_RATE(((9 * port) + 8)),
           VTSS_F_SYS_SCH_LB_LB_RATE_LB_RATE(MIN(0x7fff, VTSS_DIV64(((u64)conf->shaper_port.rate * 1000) + 100159, 100160))));

    /* Egress queue shaper rate and burst level configuration. See documentation above */
    for (queue = 0; queue < 8; queue++) {
        L26_WR(VTSS_SYS_SCH_LB_LB_THRES(((9 * port) + queue)),
               VTSS_F_SYS_SCH_LB_LB_THRES_LB_THRES(MIN(0x3f, ((conf->shaper_queue[queue].level + 4095) / 4096))));

        L26_WR(VTSS_SYS_SCH_LB_LB_RATE(((9 * port) + queue)),
               VTSS_F_SYS_SCH_LB_LB_RATE_LB_RATE(MIN(0x7fff, VTSS_DIV64(((u64)conf->shaper_queue[queue].rate * 1000) + 100159, 100160))));
        m = VTSS_BIT(queue);
        shaping_ena |= (conf->shaper_queue[queue].rate == VTSS_BITRATE_DISABLED ? 0 : m);
        exs_ena |= (conf->excess_enable[queue] ? m : 0);
        avb_ena |= (conf->shaper_queue[queue].credit_enable ? m : 0);
    }

    /* Egress port and queue shaper enable/disable configuration */
    L26_WR(VTSS_SYS_SCH_SCH_SHAPING_CTRL(port),
           VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PRIO_SHAPING_ENA(shaping_ena) |
           (conf->shaper_port.rate != VTSS_BITRATE_DISABLED ? VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PORT_SHAPING_ENA : 0) |
           VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_EXS_ENA(exs_ena) |
           VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_AVB_ENA(avb_ena));

    tag_remark_mode = conf->tag_remark_mode;
    tag_default_dei = (tag_remark_mode == VTSS_TAG_REMARK_MODE_DEFAULT ? 
                       conf->tag_default_dei : 0);

    /* Tag remarking configuration */
    L26_WRM(VTSS_REW_PORT_PORT_VLAN_CFG(port),
            (tag_default_dei ? VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_DEI : 0) |
            VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_PCP(conf->tag_default_pcp),
            VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_DEI                               |
            VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_PCP);
    
    L26_WRM(VTSS_REW_PORT_TAG_CFG(port),
            VTSS_F_REW_PORT_TAG_CFG_TAG_QOS_CFG(tag_remark_mode),
            VTSS_M_REW_PORT_TAG_CFG_TAG_QOS_CFG);

    /* Map for (QoS class and DP level) to (PCP and DEI) */
    for (class = VTSS_QUEUE_START; class < VTSS_QUEUE_END; class++) {
        for (dpl = 0; dpl < 2; dpl++) {
            L26_WRM(VTSS_REW_PORT_PCP_DEI_QOS_MAP_CFG(port, (8*dpl + class)),
                    (conf->tag_dei_map[class][dpl] ? VTSS_F_REW_PORT_PCP_DEI_QOS_MAP_CFG_DEI_QOS_VAL : 0) |
                    VTSS_F_REW_PORT_PCP_DEI_QOS_MAP_CFG_PCP_QOS_VAL(conf->tag_pcp_map[class][dpl]),
                    VTSS_F_REW_PORT_PCP_DEI_QOS_MAP_CFG_DEI_QOS_VAL                                       |
                    VTSS_M_REW_PORT_PCP_DEI_QOS_MAP_CFG_PCP_QOS_VAL);
        }
    }

    /* Port policer configuration */
    VTSS_MEMSET(&pol_cfg, 0, sizeof(pol_cfg));
    if (conf->policer_port[0].rate != VTSS_BITRATE_DISABLED) {
        pol_cfg.frame_rate = conf->policer_ext_port[0].frame_rate;
        pol_cfg.eir = conf->policer_port[0].rate;
        pol_cfg.ebs = pol_cfg.frame_rate ? 64 : conf->policer_port[0].level; /* If frame_rate we always use 64 frames as burst value */
    }
    VTSS_RC(l26_port_policer_set(vtss_state, port_no, port, conf->policer_port[0].rate != VTSS_BITRATE_DISABLED, &pol_cfg));

    /* Queue policer configuration */
    for (queue = 0; queue < 8; queue++) {
        VTSS_MEMSET(&pol_cfg, 0, sizeof(pol_cfg));
        if (conf->policer_queue[queue].rate != VTSS_BITRATE_DISABLED) {
            pol_cfg.eir = conf->policer_queue[queue].rate;
            pol_cfg.ebs = conf->policer_queue[queue].level;
        }
        VTSS_RC(l26_queue_policer_set(vtss_state, port, queue, conf->policer_queue[queue].rate != VTSS_BITRATE_DISABLED, &pol_cfg));
    }

    /* Select between SMAC/SIP or DMAC/DIP in IS1 lookup */
    VTSS_RC(l26_qcl_port_conf_set(vtss_state, port_no));

    return VTSS_RC_OK;
}

static vtss_rc l26_qos_conf_set(vtss_state_t *vtss_state, BOOL changed)
{
    vtss_qos_conf_t *conf = &vtss_state->qos.conf;
    vtss_port_no_t   port_no;
    u32              i, unit;
        
    if (changed) {
        /* Number of priorities changed, update QoS setup for all ports */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            VTSS_RC(vtss_l26_qos_port_conf_set(vtss_state, port_no));   
        }
    }
    /* Storm control */
    L26_WR(VTSS_ANA_ANA_STORMLIMIT_BURST, VTSS_F_ANA_ANA_STORMLIMIT_BURST_STORM_BURST(6)); /* Burst of 64 frames allowed */
    /* UC storm policer */
    if (conf->policer_uc_frame_rate == FALSE) {
        VTSS_E("bit rate not supported on unicast storm policer");
        return VTSS_RC_ERROR;
    }
    L26_WR(VTSS_ANA_ANA_STORMLIMIT_CFG(0),
           VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_RATE(l26_packet_rate(conf->policer_uc, &unit)) |
           (unit ? VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_UNIT : 0) |
           VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_MODE(l26_storm_mode(conf->policer_uc, conf->policer_uc_mode)));
    /* BC storm policer */
    if (conf->policer_bc_frame_rate == FALSE) {
        VTSS_E("bit rate not supported on broadcast storm policer");
        return VTSS_RC_ERROR;
    }
    L26_WR(VTSS_ANA_ANA_STORMLIMIT_CFG(1),
           VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_RATE(l26_packet_rate(conf->policer_bc, &unit)) |
           (unit ? VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_UNIT : 0) |
           VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_MODE(l26_storm_mode(conf->policer_bc, conf->policer_bc_mode)));
    /* MC storm policer */
    if (conf->policer_mc_frame_rate == FALSE) {
        VTSS_E("bit rate not supported on multicast storm policer");
        return VTSS_RC_ERROR;
    }
    L26_WR(VTSS_ANA_ANA_STORMLIMIT_CFG(2),
           VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_RATE(l26_packet_rate(conf->policer_mc, &unit)) |
           (unit ? VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_UNIT : 0) |
           VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_MODE(l26_storm_mode(conf->policer_mc, conf->policer_mc_mode)));

    /* Frame adjustment (gap value - number of bytes added in leaky buckets and DWRR calculations) */
    L26_WR(VTSS_SYS_SCH_LB_DWRR_FRM_ADJ, VTSS_F_SYS_SCH_LB_DWRR_FRM_ADJ_FRM_ADJ(20)); /* 20 bytes added */

    /* DSCP classification and remarking configuration
     */
    for (i = 0; i < 64; i++) {
        L26_WR(VTSS_ANA_COMMON_DSCP_CFG(i),
               (conf->dscp_dp_level_map[i] ? VTSS_F_ANA_COMMON_DSCP_CFG_DP_DSCP_VAL : 0)           |
               VTSS_F_ANA_COMMON_DSCP_CFG_QOS_DSCP_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->dscp_qos_class_map[i])) |
               VTSS_F_ANA_COMMON_DSCP_CFG_DSCP_TRANSLATE_VAL(conf->dscp_translate_map[i])          |
               (conf->dscp_trust[i] ? VTSS_F_ANA_COMMON_DSCP_CFG_DSCP_TRUST_ENA : 0)               |
               (conf->dscp_remark[i] ? VTSS_F_ANA_COMMON_DSCP_CFG_DSCP_REWR_ENA : 0));

        L26_WR(VTSS_REW_COMMON_DSCP_REMAP_CFG(i),
               VTSS_F_REW_COMMON_DSCP_REMAP_CFG_DSCP_REMAP_VAL(conf->dscp_remap[i]));

        L26_WR(VTSS_REW_COMMON_DSCP_REMAP_DP1_CFG(i),
               VTSS_F_REW_COMMON_DSCP_REMAP_DP1_CFG_DSCP_REMAP_DP1_VAL(conf->dscp_remap_dp1[i]));
    }

    /* DSCP classification from QoS configuration
     */
    for (i = 0; i < 8; i++) {
        L26_WR(VTSS_ANA_COMMON_DSCP_REWR_CFG(i),
               VTSS_F_ANA_COMMON_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL(conf->dscp_qos_map[i]));

        L26_WR(VTSS_ANA_COMMON_DSCP_REWR_CFG(i + 8),
               VTSS_F_ANA_COMMON_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL(conf->dscp_qos_map_dp1[i]));
    }

    return VTSS_RC_OK;
}

static vtss_rc l26_qos_status_get(vtss_state_t *vtss_state, vtss_qos_status_t *status)
{
    u32 value;

    /* Read and clear sticky register */
    L26_RD(VTSS_ANA_ANA_ANEVENTS, &value);
    L26_WR(VTSS_ANA_ANA_ANEVENTS, value & VTSS_F_ANA_ANA_ANEVENTS_STORM_DROP);

    /* Detect storm events */
    status->storm = VTSS_BOOL(value & VTSS_F_ANA_ANA_ANEVENTS_STORM_DROP);

    return VTSS_RC_OK;
}


/* - Debug print --------------------------------------------------- */

static vtss_rc l26_debug_qos(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    u32            i, value, port;
    vtss_port_no_t port_no;

    vtss_debug_print_header(pr, "QoS Storm Control");

    L26_RD(VTSS_ANA_ANA_STORMLIMIT_BURST, &value);
    pr("Burst: %u\n", VTSS_X_ANA_ANA_STORMLIMIT_BURST_STORM_BURST(value));
    for (i = 0; i < 3; i++) {
        const char *name = (i == 0 ? "UC" : i == 1 ? "BC" : "MC");
        L26_RD(VTSS_ANA_ANA_STORMLIMIT_CFG(i), &value);
        pr("%s   : Rate %2u, Unit %u, Mode %u\n", name,
           VTSS_X_ANA_ANA_STORMLIMIT_CFG_STORM_RATE(value),
           VTSS_BOOL(value & VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_UNIT),
           VTSS_X_ANA_ANA_STORMLIMIT_CFG_STORM_MODE(value));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Classification Config");

    pr("Port PCP CLS DEI DPL TC_EN DC_EN\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 vlan, qos;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        L26_RD(VTSS_ANA_PORT_VLAN_CFG(port), &vlan);
        L26_RD(VTSS_ANA_PORT_QOS_CFG(port), &qos);
        pr("%4u %3u %3u %3u %3u %5u %5u\n",
           port_no,
           VTSS_X_ANA_PORT_VLAN_CFG_VLAN_PCP(vlan),
           VTSS_X_ANA_PORT_QOS_CFG_QOS_DEFAULT_VAL(qos),
           VTSS_BOOL(vlan & VTSS_F_ANA_PORT_VLAN_CFG_VLAN_DEI),
           VTSS_BOOL(qos & VTSS_F_ANA_PORT_QOS_CFG_DP_DEFAULT_VAL),
           VTSS_BOOL(qos & VTSS_F_ANA_PORT_QOS_CFG_QOS_PCP_ENA),
           VTSS_BOOL(qos & VTSS_F_ANA_PORT_QOS_CFG_QOS_DSCP_ENA));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Classification PCP, DEI to QoS class, DP level Mapping");

    pr("Port QoS class (8*DEI+PCP)           DP level (8*DEI+PCP)\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        int pcp, dei, class_ct = 0, dpl_ct = 0;
        char class_buf[40], dpl_buf[40];
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        for (dei = VTSS_DEI_START; dei < VTSS_DEI_END; dei++) {
            for (pcp = VTSS_PCP_START; pcp < VTSS_PCP_END; pcp++) {
                const char *delim = ((pcp == VTSS_PCP_START) && (dei == VTSS_DEI_START)) ? "" : ",";
                L26_RD(VTSS_ANA_PORT_QOS_PCP_DEI_MAP_CFG(port, (8*dei + pcp)), &value);
                class_ct += VTSS_SNPRINTF(class_buf + class_ct, sizeof(class_buf) - class_ct, "%s%u", delim,
                                     VTSS_X_ANA_PORT_QOS_PCP_DEI_MAP_CFG_QOS_PCP_DEI_VAL(value));
                dpl_ct   += VTSS_SNPRINTF(dpl_buf   + dpl_ct,   sizeof(dpl_buf)   - dpl_ct,   "%s%u",  delim,
                                     VTSS_BOOL(value & VTSS_F_ANA_PORT_QOS_PCP_DEI_MAP_CFG_DP_PCP_DEI_VAL));
            }
        }
        pr("%4u %s %s\n", port_no, class_buf, dpl_buf);
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Leaky Bucket and Scheduler Config");

    L26_RD(VTSS_SYS_SCH_LB_DWRR_FRM_ADJ, &value);
    pr("Frame Adjustment (gap value): %u bytes\n", VTSS_X_SYS_SCH_LB_DWRR_FRM_ADJ_FRM_ADJ(value));
    pr("Port F_EN Mode C0 C1 C2 C3 C4 C5\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 frm_adj_ena, dwrr_cfg, cost;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        L26_RD(VTSS_SYS_SCH_LB_DWRR_CFG(port), &frm_adj_ena);
        L26_RD(VTSS_SYS_SCH_SCH_DWRR_CFG(port), &dwrr_cfg);
        cost = VTSS_X_SYS_SCH_SCH_DWRR_CFG_COST_CFG(dwrr_cfg);
        pr("%4u %4u %4u %2u %2u %2u %2u %2u %2u\n",
           port_no,
           VTSS_BOOL(frm_adj_ena & VTSS_F_SYS_SCH_LB_DWRR_CFG_FRM_ADJ_ENA),
           VTSS_BOOL(dwrr_cfg & VTSS_F_SYS_SCH_SCH_DWRR_CFG_DWRR_MODE),
           VTSS_EXTRACT_BITFIELD(cost,  0, 5),
           VTSS_EXTRACT_BITFIELD(cost,  5, 5),
           VTSS_EXTRACT_BITFIELD(cost, 10, 5),
           VTSS_EXTRACT_BITFIELD(cost, 15, 5),
           VTSS_EXTRACT_BITFIELD(cost, 20, 5),
           VTSS_EXTRACT_BITFIELD(cost, 25, 5));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port and Queue Shaper enable/disable Config");

    pr("Port P Q0-Q7    Ex Q0-Q7\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 queue_shaper, queue_excess;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        L26_RD(VTSS_SYS_SCH_SCH_SHAPING_CTRL(port), &value);
        queue_shaper = VTSS_X_SYS_SCH_SCH_SHAPING_CTRL_PRIO_SHAPING_ENA(value);
        queue_excess = VTSS_X_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_EXS_ENA(value);
        pr("%4u %u %u%u%u%u%u%u%u%u %u%u%u%u%u%u%u%u\n",
           port_no,
           VTSS_BOOL(value & VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PORT_SHAPING_ENA),
           VTSS_BOOL(queue_shaper & VTSS_BIT(0)),
           VTSS_BOOL(queue_shaper & VTSS_BIT(1)),
           VTSS_BOOL(queue_shaper & VTSS_BIT(2)),
           VTSS_BOOL(queue_shaper & VTSS_BIT(3)),
           VTSS_BOOL(queue_shaper & VTSS_BIT(4)),
           VTSS_BOOL(queue_shaper & VTSS_BIT(5)),
           VTSS_BOOL(queue_shaper & VTSS_BIT(6)),
           VTSS_BOOL(queue_shaper & VTSS_BIT(7)),
           VTSS_BOOL(queue_excess & VTSS_BIT(0)),
           VTSS_BOOL(queue_excess & VTSS_BIT(1)),
           VTSS_BOOL(queue_excess & VTSS_BIT(2)),
           VTSS_BOOL(queue_excess & VTSS_BIT(3)),
           VTSS_BOOL(queue_excess & VTSS_BIT(4)),
           VTSS_BOOL(queue_excess & VTSS_BIT(5)),
           VTSS_BOOL(queue_excess & VTSS_BIT(6)),
           VTSS_BOOL(queue_excess & VTSS_BIT(7)));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port and Queue Shaper Burst and Rate Config");

    pr("Port Queue Burst Rate\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        int queue;
        u32 burst, rate;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        L26_RD(VTSS_SYS_SCH_LB_LB_THRES(((9 * port) + 8)), &burst);
        L26_RD(VTSS_SYS_SCH_LB_LB_RATE(((9 * port) + 8)), &rate);
        pr("%4u     - 0x%02x  0x%04x\n     ",
           port_no,
           VTSS_X_SYS_SCH_LB_LB_THRES_LB_THRES(burst),
           VTSS_X_SYS_SCH_LB_LB_RATE_LB_RATE(rate));
        for (queue = 0; queue < 8; queue++) {
            L26_RD(VTSS_SYS_SCH_LB_LB_THRES(((9 * port) + queue)), &burst);
            L26_RD(VTSS_SYS_SCH_LB_LB_RATE(((9 * port) + queue)), &rate);
            pr("%5d 0x%02x  0x%04x\n     ",
               queue,
               VTSS_X_SYS_SCH_LB_LB_THRES_LB_THRES(burst),
               VTSS_X_SYS_SCH_LB_LB_RATE_LB_RATE(rate));
        }
        pr("\r");
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Tag Remarking Config");

    pr("Port Mode PCP DEI\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 tag_default, tag_ctrl;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        L26_RD(VTSS_REW_PORT_PORT_VLAN_CFG(port), &tag_default);
        L26_RD(VTSS_REW_PORT_TAG_CFG(port), &tag_ctrl);
        pr("%4u %4x %3d %3d\n",
           port_no,
           VTSS_X_REW_PORT_TAG_CFG_TAG_QOS_CFG(tag_ctrl),
           VTSS_X_REW_PORT_PORT_VLAN_CFG_PORT_PCP(tag_default),
           VTSS_BOOL(tag_default & VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_DEI));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Tag Remarking Map");

    pr("Port PCP (2*QoS class+DPL)           DEI (2*QoS class+DPL)\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        int class, dpl, pcp_ct = 0, dei_ct = 0;
        char pcp_buf[40], dei_buf[40];
        if (info->port_list[port_no] == 0)
            continue;
        port = VTSS_CHIP_PORT(port_no);
        for (class = VTSS_QUEUE_START; class < VTSS_QUEUE_END; class++) {
            for (dpl = 0; dpl < 2; dpl++) {
                const char *delim = ((class == VTSS_QUEUE_START) && (dpl == 0)) ? "" : ",";
                L26_RD(VTSS_REW_PORT_PCP_DEI_QOS_MAP_CFG(port, (8*dpl + class)), &value);
                pcp_ct += VTSS_SNPRINTF(pcp_buf + pcp_ct, sizeof(pcp_buf) - pcp_ct, "%s%u", delim,
                                   VTSS_X_REW_PORT_PCP_DEI_QOS_MAP_CFG_PCP_QOS_VAL(value));
                dei_ct += VTSS_SNPRINTF(dei_buf + dei_ct, sizeof(dei_buf) - dei_ct, "%s%u",  delim,
                                   VTSS_BOOL(value & VTSS_F_REW_PORT_PCP_DEI_QOS_MAP_CFG_DEI_QOS_VAL));
            }
        }
        pr("%4u %s %s\n", port_no, pcp_buf, dei_buf);
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port DSCP Remarking Config");

    pr("Port I_Mode Trans E_Mode\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 qos_cfg, dscp_cfg;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        L26_RD(VTSS_ANA_PORT_QOS_CFG(port), &qos_cfg);
        L26_RD(VTSS_REW_PORT_DSCP_CFG(port), &dscp_cfg);
        pr("%4u %6u %5u %6u\n",
           port_no,
           VTSS_X_ANA_PORT_QOS_CFG_DSCP_REWR_CFG(qos_cfg),
           VTSS_BOOL(qos_cfg & VTSS_F_ANA_PORT_QOS_CFG_DSCP_TRANSLATE_ENA),
           VTSS_X_REW_PORT_DSCP_CFG_DSCP_REWR_CFG(dscp_cfg));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS DSCP Config");

    pr("DSCP Trans CLS DPL Rewr Trust Remap_DP0 Remap_DP1\n");
    for (i = 0; i < 64; i++) {
        u32 dscp_cfg, dscp_remap, dscp_remap_dp1;
        L26_RD(VTSS_ANA_COMMON_DSCP_CFG(i), &dscp_cfg);
        L26_RD(VTSS_REW_COMMON_DSCP_REMAP_CFG(i), &dscp_remap);
        L26_RD(VTSS_REW_COMMON_DSCP_REMAP_DP1_CFG(i), &dscp_remap_dp1);

        pr("%4u %5u %3u %3u %4u %5u %5u     %5u\n",
           i,
           VTSS_X_ANA_COMMON_DSCP_CFG_DSCP_TRANSLATE_VAL(dscp_cfg),
           VTSS_X_ANA_COMMON_DSCP_CFG_QOS_DSCP_VAL(dscp_cfg),
           VTSS_BOOL(dscp_cfg & VTSS_F_ANA_COMMON_DSCP_CFG_DP_DSCP_VAL),
           VTSS_BOOL(dscp_cfg & VTSS_F_ANA_COMMON_DSCP_CFG_DSCP_REWR_ENA),
           VTSS_BOOL(dscp_cfg & VTSS_F_ANA_COMMON_DSCP_CFG_DSCP_TRUST_ENA),
           VTSS_X_REW_COMMON_DSCP_REMAP_CFG_DSCP_REMAP_VAL(dscp_remap),
           VTSS_X_REW_COMMON_DSCP_REMAP_DP1_CFG_DSCP_REMAP_DP1_VAL(dscp_remap_dp1));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS DSCP Classification from QoS Config");

    pr("QoS DSCP_DP0 DSCP_DP1\n");
    for (i = 0; i < 8; i++) {
        u32 qos_dp0, qos_dp1;
        L26_RD(VTSS_ANA_COMMON_DSCP_REWR_CFG(i), &qos_dp0);
        L26_RD(VTSS_ANA_COMMON_DSCP_REWR_CFG(i + 8), &qos_dp1);
        pr("%3u %4u     %4u\n",
           i,
           VTSS_X_ANA_COMMON_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL(qos_dp0),
           VTSS_X_ANA_COMMON_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL(qos_dp1));
    }
    pr("\n");

    VTSS_RC(vtss_l26_debug_range_checkers(vtss_state, pr, info));
    VTSS_RC(vtss_l26_debug_vcap_port(vtss_state, pr, info));
    VTSS_RC(vtss_l26_debug_vcap_is1(vtss_state, pr, info));

    vtss_debug_print_header(pr, "QoS Port and Queue Policer");

    vtss_l26_debug_reg_header(pr, "Policer Config");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_POL_CFG(port), port, "POL_CFG");
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_SYS_POL_MISC_POL_FLOWC(port), port, "POL_FLOWC");
    }
    pr("\n");

    pr("Policers:\n");
    for (i = 0; i < VTSS_L26_POLICER_CNT; i++) {
        u32                 mode;
        vtss_policer_user_t user;

        if (!info->full && i == vtss_state->port_count) {
            pr("Use 'full' to see all of the %d policers!", VTSS_L26_POLICER_CNT);
            break;
        }

        if ((i % 32) == 0) {
            pr("\nIndex  User   Mode  Dual  IFG  CF  OS  PIR    PBS  CIR    CBS\n");
        }

        L26_RD(VTSS_SYS_POL_POL_MODE_CFG(i), &value);
        mode = VTSS_X_SYS_POL_POL_MODE_CFG_FRM_MODE(value);
        user = vtss_state->qos.policer_user[i];
        pr("%-5u  %-5s  %-4s  %-4u  %-3u  %-2u  %-2u  ",
           i,
           user == VTSS_POLICER_USER_NONE ? "None" :
           user == VTSS_POLICER_USER_DISCARD ? "Disc" :
           user == VTSS_POLICER_USER_PORT ? "Port" :
           user == VTSS_POLICER_USER_QUEUE ? "Queue" :
           user == VTSS_POLICER_USER_ACL ? "ACL" :
           user == VTSS_POLICER_USER_EVC ? "EVC" :
           user == VTSS_POLICER_USER_MEP ? "MEP" : "?",
           mode == POL_MODE_LINERATE ? "Line" : mode == POL_MODE_DATARATE ? "Data" :
           mode == POL_MODE_FRMRATE_100FPS ? "F100" : "F1",
           L26_BF(SYS_POL_POL_MODE_CFG_CIR_ENA, value),
           VTSS_X_SYS_POL_POL_MODE_CFG_IPG_SIZE(value),
           L26_BF(SYS_POL_POL_MODE_CFG_DLB_COUPLED, value),
           L26_BF(SYS_POL_POL_MODE_CFG_OVERSHOOT_ENA, value));

        L26_RD(VTSS_SYS_POL_POL_PIR_CFG(i), &value);
        pr("%-5u  %-3u  ",
           VTSS_X_SYS_POL_POL_PIR_CFG_PIR_RATE(value),
           VTSS_X_SYS_POL_POL_PIR_CFG_PIR_BURST(value));

        L26_RD(VTSS_SYS_POL_POL_CIR_CFG(i), &value);
        pr("%-5u  %-3u\n",
           VTSS_X_SYS_POL_POL_CIR_CFG_CIR_RATE(value),
           VTSS_X_SYS_POL_POL_CIR_CFG_CIR_BURST(value));
    }
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_qos_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_QOS, l26_debug_qos, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

vtss_rc vtss_l26_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_qos_state_t *state = &vtss_state->qos;
    u32              value;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        /* QoS */
        state->conf_set = l26_qos_conf_set;
        state->port_conf_set = vtss_cmn_qos_port_conf_set;
        state->port_conf_update = vtss_l26_qos_port_conf_set;
        state->qce_add = vtss_cmn_qce_add;
        state->qce_del = vtss_cmn_qce_del;
        state->status_get = l26_qos_status_get;
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
        state->evc_policer_conf_set = vtss_l26_evc_policer_conf_set;
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
        state->prio_count = L26_PRIOS;
        /* Reserve policer for ACL discarding) */
        state->policer_user[L26_ACL_POLICER_DISC] = VTSS_POLICER_USER_DISCARD;
        break;
    case VTSS_INIT_CMD_INIT:
        /* Initialize leaky buckets */
        L26_WR(VTSS_SYS_SCH_SCH_LB_CTRL, VTSS_F_SYS_SCH_SCH_LB_CTRL_LB_INIT);

        do { /* Wait until leaky buckets initialization is completed  */
            L26_RD(VTSS_SYS_SCH_SCH_LB_CTRL, &value);                       
        } while(value & VTSS_F_SYS_SCH_SCH_LB_CTRL_LB_INIT);
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LUTON26 */
