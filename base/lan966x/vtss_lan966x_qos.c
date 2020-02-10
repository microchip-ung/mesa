// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

#define TERMINAL_SE_INDEX_OFFSET 80
#define TERMINAL_SE_INDEX_LIMIT  255

#define HSCH_L2_SE(port, queue) (8 * (port) + queue)

#define POL_MODE_LINERATE            0
#define POL_MODE_DATARATE            1
#define POL_MODE_FRMRATE_33_1_3_FPS  2
#define POL_MODE_FRMRATE_1_3_FPS     3

#define DEFAULT_POL_ORDER 0x1d3 /* Serval policer order: Serial (QoS -> Port -> VCAP) */

#define CPU_PORT_0_SE_INDEX 88
#define CPU_PORT_1_SE_INDEX 89

static u32 divide_by_33_1_3(u32 x)
{
    u32 ret_val, rest;

    ret_val = (x / 100) * 3;
    rest = (x % 100) * 3;
    ret_val += VTSS_DIV_ROUND_UP(rest*1000, 33333);
    return ret_val;
}

vtss_rc vtss_lan966x_qos_policer_conf_set(vtss_state_t *vtss_state, u32 policer, vtss_policer_conf_t *conf)
{
    u32  cir = 0, cbs = 0, pir, pbs, mode;
    u32  cf = 0, pbs_max, cbs_max = 0;
    BOOL pir_discard = 0;
    u32  cir_ena = 0;
    BOOL cir_discard = 0;

    pir = conf->eir;
    pbs = conf->ebs;
    if (conf->frame_rate) {
        /* Frame rate policing (single leaky bucket) */

        /* There are two frame rate "modes" that has 33 1/3 frame or 1/3 frame resolution. Use 1/3 frame resolution if possible. The pir configuration bit field is 15 bit wide */
        if (pir >= (0x7FFF / 3)) {  /* PIR rate requires the 33 1/3 frame resolution */
            mode = POL_MODE_FRMRATE_33_1_3_FPS;
            pir = divide_by_33_1_3(pir);    /* Resolution is in steps of 33 1/3 fps */
            pbs = (pbs * 10 / 328);         /* Burst unit is 32.8 frames */
            pbs_max = VTSS_BITMASK(6);      /* Limit burst to the maximum value */
        } else {                    /* PIR rate can be configured using the 1/3 frame resolution */
            mode = POL_MODE_FRMRATE_1_3_FPS;
            pir = pir*3;          /* Resolution is in steps of 1/3 fps */
            pbs = (pbs * 10 / 3); /* Burst unit is 0.3 frames */
            pbs_max = 60;         /* See Bugzilla#4944, comment#2 */
            if (pir == 0 && pbs == 0) {
                /* Discard all frames */
                pir_discard = 1;
                cir_discard = 1;
            }
        }
        pbs++; /* Round up burst size */
    } else {
        /* Bit rate policing */
        mode = (conf->data_rate ? POL_MODE_DATARATE : POL_MODE_LINERATE);
        if (conf->dual) {
            /* Dual leaky bucket mode */
            cir = conf->cir;
            cbs = conf->cbs;
            if (cir == 0 && cbs == 0) {
                /* Discard CIR frames */
                cir_discard = 1;
            }
            cir = divide_by_33_1_3(cir);        /* Rate unit is 33 1/3 kbps, round up */
            cbs = (cbs ? cbs : 1);              /* BZ 9813: Avoid using zero burst size */
            cbs = VTSS_DIV_ROUND_UP(cbs, 4096); /* Burst unit is 4kB, round up */
            cbs_max = 61;                       /* See Bugzilla#4944, comment#2  */
            cir_ena = 1;
            cf = conf->cf;
            if (cf)
                pir += conf->cir;
        }
        if (pir == 0 && pbs == 0) {
            /* Discard PIR frames */
            pir_discard = 1;
        }
        pir = divide_by_33_1_3(pir);        /* Rate unit is 33 1/3 kbps, round up */
        pbs = (pbs ? pbs : 1);              /* BZ 9813: Avoid using zero burst size */
        pbs = VTSS_DIV_ROUND_UP(pbs, 4096); /* Burst unit is 4kB, round up */
        pbs_max = 61;                       /* See Bugzilla#4944, comment#2  */
    }

    /* Limit to maximum values */
    pir = MIN(VTSS_BITMASK(15), pir);
    cir = MIN(VTSS_BITMASK(15), cir);
    pbs = MIN(pbs_max, pbs);
    cbs = MIN(cbs_max, cbs);

    if (conf->disable) {
        /* Disable policer using zero burst and maximum rate */
        pbs = 0;
        pir = VTSS_BITMASK(15);
    }

    REG_WR(ANA_POL_MODE(policer), ANA_POL_MODE_IPG_SIZE(20)             |
                                  ANA_POL_MODE_DLB_COUPLED(cf ? 1 : 0)  |
                                  ANA_POL_MODE_CIR_ENA(cir_ena ? 1 : 0) |
                                  ANA_POL_MODE_FRM_MODE(mode)           |
                                  ANA_POL_MODE_OVERSHOOT_ENA(1));
    REG_WR(ANA_POL_PIR_CFG(policer), ANA_POL_PIR_CFG_PIR_RATE(pir) | ANA_POL_PIR_CFG_PIR_BURST(pbs));
    REG_WR(ANA_POL_PIR_STATE(policer), ANA_POL_PIR_STATE_PIR_LVL(pir_discard ? 1 : 0));
    REG_WR(ANA_POL_CIR_CFG(policer), ANA_POL_CIR_CFG_CIR_RATE(cir) | ANA_POL_CIR_CFG_CIR_BURST(cbs));
    REG_WR(ANA_POL_CIR_STATE(policer), ANA_POL_CIR_STATE_CIR_LVL(cir_discard ? 1 : 0));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_shaper_conf_set(vtss_state_t *vtss_state, vtss_shaper_t *shaper, u32 se, BOOL dlb_ena, u32 dlb_sense_port, u32 dlb_sense_qos, vtss_shaper_calibrate_t *calibrate)
{
    VTSS_D("Enter  se %u  rate %u  level %u  mode %u", se, shaper->rate, shaper->level, shaper->mode);
/* Egress port/queue shaper rate configuration
     * The value (in kbps) is rounded up to the next possible value:
     *        0 -> 0 (Open until burst capacity is used, then closed)
     *   1..100 -> 1 (100 kbps)
     * 101..200 -> 2 (200 kbps)
     * 201..300 -> 3 (300 kbps)
     */

    /* Egress port/queue shaper burst level configuration
     * The value is rounded up to the next possible value:
     *           0 -> 0 (Shaper disabled)
     *    1.. 4096 -> 1 ( 4 KB)
     * 4097.. 8192 -> 2 ( 8 KB)
     * 8193..12288 -> 3 (12 KB)
     */

    /* Egress port shaper configuration */

    /* First set the shaper mode, i.e. line-rate or data-rate */
    /* Shaper mode is not configurable for queue shapers of elements 0 - 217 (i.e. SE 256 - 691),
       meaning no queue-shaping inside a service. Serval 1 limitation */
    REG_WRM(QSYS_SE_CFG(se),
            QSYS_SE_CFG_SE_FRM_MODE(shaper->mode),
            QSYS_SE_CFG_SE_FRM_MODE_M);

    if (shaper->rate != VTSS_BITRATE_DISABLED) {
        u32 cir = MIN(VTSS_BITMASK(15), VTSS_DIV_ROUND_UP(shaper->rate,   100));
        u32 cbs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP(shaper->level, 4096));
        cir = (cir ? cir : 1);               /* Avoid using zero rate */
        cbs = (cbs ? cbs : 1);               /* Avoid using zero burst size */

        REG_WR(QSYS_CIR_CFG(se),
               QSYS_CIR_CFG_CIR_RATE(cir) |
               QSYS_CIR_CFG_CIR_BURST(cbs));

        /* DLB configuration */
        if (dlb_ena) {
            if (shaper->eir != VTSS_BITRATE_DISABLED) {
                u32 eir = MIN(VTSS_BITMASK(15), VTSS_DIV_ROUND_UP(shaper->eir,  100));
                u32 ebs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP(shaper->ebs, 4096));
                eir = (eir ? eir : 1);               /* Avoid using zero rate */
                ebs = (ebs ? ebs : 1);               /* Avoid using zero burst size */

                REG_WR(QSYS_EIR_CFG(se),
                       QSYS_EIR_CFG_EIR_RATE(eir) |
                       QSYS_EIR_CFG_EIR_BURST(ebs));

                REG_WR(QSYS_SE_DLB_SENSE(se),
                       QSYS_SE_DLB_SENSE_SE_DLB_PRIO(dlb_sense_qos)   |
                       QSYS_SE_DLB_SENSE_SE_DLB_SPORT(dlb_sense_port) |
                       QSYS_SE_DLB_SENSE_SE_DLB_PRIO_ENA(1)           |
                       QSYS_SE_DLB_SENSE_SE_DLB_DPORT_ENA(1));
            } else {
                REG_WR(QSYS_EIR_CFG(se), 0);      /* Disable EIR */
                REG_WR(QSYS_SE_DLB_SENSE(se), 0); /* Disable DLB */
            }
        }
    } else {    /* Disable shaper */
        REG_WR(QSYS_CIR_CFG(se), 0); /* Disable shaper */
        if (dlb_ena) {
            REG_WR(QSYS_EIR_CFG(se), 0);      /* Disable EIR */
            REG_WR(QSYS_SE_DLB_SENSE(se), 0); /* Disable DLB */
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_port_policer_fc_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no, u32 port)
{
    vtss_port_conf_t     *port_conf = &vtss_state->port.conf[port_no];
    vtss_qos_port_conf_t *qos_conf = &vtss_state->qos.port_conf[port_no];

    REG_WR(ANA_POL_FLOWC(port),
           ANA_POL_FLOWC_POL_FLOWC((port_conf->flow_control.generate &&
                                    (qos_conf->policer_port[0].rate != VTSS_BITRATE_DISABLED) &&
                                    qos_conf->policer_ext_port[0].flow_control) ? 1 : 0));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_policer_set(vtss_state_t *vtss_state, u32 port, BOOL enable, vtss_policer_conf_t *conf)
{
    u32  order = DEFAULT_POL_ORDER;

    VTSS_RC(vtss_lan966x_qos_policer_conf_set(vtss_state, LAN966X_POLICER_PORT + port, conf));

    REG_WRM(ANA_POL_CFG(port),
            ANA_POL_CFG_PORT_POL_ENA(enable ? 1 : 0) | ANA_POL_CFG_POL_ORDER(order),
            ANA_POL_CFG_PORT_POL_ENA_M | ANA_POL_CFG_POL_ORDER_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_queue_policer_set(vtss_state_t *vtss_state, u32 port, u32 queue, BOOL enable, vtss_policer_conf_t *conf)
{
    VTSS_RC(vtss_lan966x_qos_policer_conf_set(vtss_state, LAN966X_POLICER_QUEUE + (port * 8) + queue, conf));

    REG_WRM(ANA_POL_CFG(port),
            ANA_POL_CFG_QUEUE_POL_ENA(enable ? VTSS_BIT(queue): 0),
            ANA_POL_CFG_QUEUE_POL_ENA(VTSS_BIT(queue)));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_wred_conf_set(vtss_state_t *vtss_state)
{
    vtss_qos_conf_t *conf = &vtss_state->qos.conf;
    int              queue, dpl;

    for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
        u32 wm_high = vtss_lan966x_wm_high_get(vtss_state, queue);
        for (dpl = 0; dpl < 2; dpl++) {
            vtss_red_v2_t *red = &conf->red_v2[queue][dpl];
            vtss_pct_t     max_dp = 100;
            vtss_pct_t     max_fl = 100;
            u32            wm_red_low, wm_red_high;

            /* Sanity check */
            if (red->min_fl > 100) {
                VTSS_E("illegal min_fl (%u) on queue %d, dpl %d", red->min_fl, queue, dpl);
                return VTSS_RC_ERROR;
            }
            if ((red->max < 1) || (red->max > 100)) {
                VTSS_E("illegal max (%u) on queue %d, dpl %d", red->max, queue, dpl);
                return VTSS_RC_ERROR;
            }
            if ((red->max_unit != VTSS_WRED_V2_MAX_DP) && (red->max_unit != VTSS_WRED_V2_MAX_FL)) {
                VTSS_E("illegal max_unit (%u) on queue %d, dpl %d", red->max_unit, queue, dpl);
                return VTSS_RC_ERROR;
            }
            if (red->max_unit == VTSS_WRED_V2_MAX_DP) {
                max_dp = red->max; /* Unit is drop probability - save specified value */
            } else {
                if (red->min_fl >= red->max) {
                    VTSS_E("min_fl (%u) >= max fl (%u) on queue %d, dpl %d", red->min_fl, red->max, queue, dpl);
                    return VTSS_RC_ERROR;
                } else {
                    max_fl = red->max; /* Unit is fill level - save specified value */
                }
            }

            if (red->enable) {
                wm_red_low  = wm_high * red->min_fl / 100;                              /* Convert from % to actual value in bytes */
                wm_red_high = wm_high * max_fl / 100;                                   /* Convert from % to actual value in bytes */
                wm_red_high = ((wm_red_high - wm_red_low) * 100 / max_dp) + wm_red_low; /* Adjust wm_red_high to represent 100% drop probability */
                wm_red_low  = MIN(wm_red_low / 1024, VTSS_BITMASK(5));                 /* Convert from bytes to 960 byte chunks and prevent overflow */
                wm_red_high = MIN(wm_red_high / 1024, VTSS_BITMASK(5));                /* Convert from bytes to 960 byte chunks and prevent overflow */
            } else {
                wm_red_low = wm_red_high = VTSS_BITMASK(5);                            /* Disable red by setting both fields to max */
            }

            REG_WR(QSYS_RED_PROFILE((queue + (8 * dpl))), /* Red profile for queue, dpl */
                   QSYS_RED_PROFILE_WM_RED_LOW(wm_red_low) |
                   QSYS_RED_PROFILE_WM_RED_HIGH(wm_red_high));
        }
    }

    VTSS_RC(vtss_lan966x_wm_update(vtss_state)); /* Update watermarks */

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t  *conf = &vtss_state->qos.port_conf[port_no];
    int                   pcp, dei, queue, class, dpl;
    vtss_policer_conf_t   pol_cfg;
    u32                   tag_remark_mode, value, terminal_se, dwrr_cnt, port = VTSS_CHIP_PORT(port_no);
    BOOL                  tag_default_dei, sch_valid, precise_rate = FALSE;
    u8                    dwrr_cost[8] = {0};

    /* Port default PCP and DEI configuration */
    REG_WRM(ANA_VLAN_CFG(port),
            ANA_VLAN_CFG_VLAN_DEI(conf->default_dei ? 1 : 0) | ANA_VLAN_CFG_VLAN_PCP(conf->usr_prio),
            ANA_VLAN_CFG_VLAN_DEI_M | ANA_VLAN_CFG_VLAN_PCP_M);

    /* Port default QoS class, DP level, tagged frames mode, DSCP mode and DSCP remarking configuration */
    REG_WR(ANA_QOS_CFG(port),
           ANA_QOS_CFG_DP_DEFAULT_VAL(conf->default_dpl ? 1 : 0)                               |
           ANA_QOS_CFG_QOS_DEFAULT_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->default_prio)) |
           ANA_QOS_CFG_QOS_PCP_ENA(conf->tag_class_enable ? 1 : 0)                             |
           ANA_QOS_CFG_QOS_DSCP_ENA(conf->dscp_class_enable ? 1 : 0)                           |
           ANA_QOS_CFG_DSCP_TRANSLATE_ENA(conf->dscp_translate ? 1 : 0)                        |
           ANA_QOS_CFG_DSCP_REWR_CFG(conf->dscp_mode));

    /* Egress DSCP remarking configuration */
    REG_WR(REW_DSCP_CFG(port), REW_DSCP_CFG_DSCP_REWR_CFG(conf->dscp_emode));

    /* Map for (PCP and DEI) to (QoS class and DP level */
    for (pcp = VTSS_PCP_START; pcp < VTSS_PCP_END; pcp++) {
        for (dei = VTSS_DEI_START; dei < VTSS_DEI_END; dei++) {
            REG_WR(ANA_PCP_DEI_CFG(port, (8*dei + pcp)),
                   ANA_PCP_DEI_CFG_DP_PCP_DEI_VAL(conf->dp_level_map[pcp][dei] ? 1 : 0) |
                   ANA_PCP_DEI_CFG_QOS_PCP_DEI_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->qos_class_map[pcp][dei])));
        }
    }

    /* Verify that the default scheduler configuration is used. */
    REG_RD(QSYS_QMAP(port), &value);
    sch_valid = (value ? FALSE : TRUE);

    if (!sch_valid) {
        VTSS_E("Invalid scheduler configuration for port %u", port);
    } else {
        precise_rate = TRUE;
        terminal_se = TERMINAL_SE_INDEX_OFFSET + port;

        /* DWRR configuration */
        if (conf->dwrr_enable) {
#if defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
            dwrr_cnt = conf->dwrr_cnt;
            /* Number of allowed queues in DWRR mode is 1..8 */
            if (dwrr_cnt < 1) {
                dwrr_cnt = 1;
            } else if (dwrr_cnt > 8) {
                dwrr_cnt = 8;
            }
#else
            dwrr_cnt = 6;
#endif /* VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT */
        } else {
            dwrr_cnt = 0; /* All queues are running in strict mode */
        }

        REG_WRM(QSYS_SE_CFG(terminal_se),
                QSYS_SE_CFG_SE_DWRR_CNT(dwrr_cnt),
                QSYS_SE_CFG_SE_DWRR_CNT_M | QSYS_SE_CFG_SE_RR_ENA_M);

        VTSS_RC(vtss_cmn_qos_weight2cost(conf->queue_pct, dwrr_cost, dwrr_cnt, VTSS_QOS_DWRR_COST_BIT_WIDTH));
        for (queue = 0; queue < 8; queue++) {
            REG_WR(QSYS_SE_DWRR_CFG(terminal_se, queue), dwrr_cost[queue]);
        }

        /* Port shaper configuration */
        VTSS_RC(lan966x_qos_shaper_conf_set(vtss_state, &conf->shaper_port, terminal_se, TRUE, port, 0, precise_rate ? &vtss_state->qos.port_shaper[port_no] : NULL));

        /* Egress queue shaper configuration */
        for (queue = 0; queue < 8; queue++) {
            u32  queue_shaper_se;
            BOOL dlb_ena = TRUE;

            queue_shaper_se = HSCH_L2_SE(port, queue);

            VTSS_RC(lan966x_qos_shaper_conf_set(vtss_state, &conf->shaper_queue[queue], queue_shaper_se, dlb_ena, port, queue, NULL));

            if (dlb_ena) {
                /* Excess configuration */
                REG_WRM(QSYS_SE_CFG(queue_shaper_se),
                        QSYS_SE_CFG_SE_EXC_ENA(conf->excess_enable[queue] ? 1 : 0),
                        QSYS_SE_CFG_SE_EXC_ENA_M);
                /* Credit configuration */
                REG_WRM(QSYS_SE_CFG(queue_shaper_se),
                        QSYS_SE_CFG_SE_AVB_ENA(conf->shaper_queue[queue].credit_enable ? 1 : 0),
                        QSYS_SE_CFG_SE_AVB_ENA_M);
            }
        }
    }

    tag_remark_mode = conf->tag_remark_mode;
    tag_default_dei = (tag_remark_mode == VTSS_TAG_REMARK_MODE_DEFAULT ? conf->tag_default_dei : 0);

    /* Tag remarking configuration */
    REG_WRM(REW_PORT_VLAN_CFG(port),
            REW_PORT_VLAN_CFG_PORT_DEI(tag_default_dei ? 1 : 0) | REW_PORT_VLAN_CFG_PORT_PCP(conf->tag_default_pcp),
            REW_PORT_VLAN_CFG_PORT_DEI_M | REW_PORT_VLAN_CFG_PORT_PCP_M);

    /* Map remark mode */
    switch (tag_remark_mode) {
    case VTSS_TAG_REMARK_MODE_DEFAULT:
        tag_remark_mode = 1; /* PORT_PCP/PORT_DEI */
        break;
    case VTSS_TAG_REMARK_MODE_MAPPED:
        tag_remark_mode = 2; /* MAPPED */
        break;
    default:
        tag_remark_mode = 0; /* Classified PCP/DEI */
        break;
    }

    REG_WRM(REW_TAG_CFG(port),
            REW_TAG_CFG_TAG_PCP_CFG(tag_remark_mode) | REW_TAG_CFG_TAG_DEI_CFG(tag_remark_mode),
            REW_TAG_CFG_TAG_PCP_CFG_M | REW_TAG_CFG_TAG_DEI_CFG_M);

    /* Map for (QoS class and DP level) to (PCP and DEI) */
    for (class = VTSS_QUEUE_START; class < VTSS_QUEUE_END; class++) {
        for (dpl = 0; dpl < 2; dpl++) {
            REG_WRM(REW_PCP_DEI_CFG(port, (8 * dpl + class)),
                    REW_PCP_DEI_CFG_DEI_QOS_VAL(conf->tag_dei_map[class][dpl] ? 1 : 0) | REW_PCP_DEI_CFG_PCP_QOS_VAL(conf->tag_pcp_map[class][dpl]),
                    REW_PCP_DEI_CFG_DEI_QOS_VAL_M | REW_PCP_DEI_CFG_PCP_QOS_VAL_M);
        }
    }

    /* Update port policer flow control configuration */
    /* This must be done before the port policer configuration */
    VTSS_RC(lan966x_qos_port_policer_fc_set(vtss_state, port_no, port));

    /* Port policer configuration */
    memset(&pol_cfg, 0, sizeof(pol_cfg));
    if (conf->policer_port[0].rate != VTSS_BITRATE_DISABLED) {
        pol_cfg.frame_rate = conf->policer_ext_port[0].frame_rate;
        pol_cfg.eir = conf->policer_port[0].rate;
        pol_cfg.ebs = pol_cfg.frame_rate ? 64 : conf->policer_port[0].level; /* If frame_rate we always use 64 frames as burst value */
    } else {
        pol_cfg.disable = TRUE;
    }
    VTSS_RC(lan966x_port_policer_set(vtss_state, port, conf->policer_port[0].rate != VTSS_BITRATE_DISABLED, &pol_cfg));

    /* Queue policer configuration */
    for (queue = 0; queue < 8; queue++) {
        memset(&pol_cfg, 0, sizeof(pol_cfg));
        if (conf->policer_queue[queue].rate != VTSS_BITRATE_DISABLED) {
            pol_cfg.eir = conf->policer_queue[queue].rate;
            pol_cfg.ebs = conf->policer_queue[queue].level;
        } else {
            pol_cfg.disable = TRUE;
        }
        VTSS_RC(lan966x_queue_policer_set(vtss_state, port, queue, conf->policer_queue[queue].rate != VTSS_BITRATE_DISABLED, &pol_cfg));
    }

    /* Update QCL port configuration - TBD_HENRIKB */
//    VTSS_RC(vtss_lan966x_vcap_port_key_addr_set(vtss_state,
//                                                port_no,
//                                                2, /* Third IS1 lookup */
//                                                vtss_state->qos.port_conf[port_no].key_type,
//                                                vtss_state->qos.port_conf_old.key_type,
//                                                vtss_state->qos.port_conf[port_no].dmac_dip));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_conf_set(vtss_state_t *vtss_state, BOOL changed)
{
    vtss_qos_conf_t *conf = &vtss_state->qos.conf;
    vtss_port_no_t   port_no;
    u32              i, unit;

    if (changed) {
        /* Number of priorities changed, update QoS setup for all ports */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            VTSS_RC(lan966x_qos_port_conf_set(vtss_state, port_no));
        }
    }
    /* Storm control */
    REG_WR(QSYS_STORMLIM_BURST, QSYS_STORMLIM_BURST_STORM_BURST(6)); /* Burst of 64 frames allowed */
    /* UC storm policer */
    if (conf->policer_uc_frame_rate == FALSE) {
        VTSS_E("bit rate not supported on unicast storm policer");
        return VTSS_RC_ERROR;
    }
    REG_WR(QSYS_STORMLIM_CFG(0),
           QSYS_STORMLIM_CFG_STORM_RATE(vtss_cmn_qos_packet_rate(conf->policer_uc, &unit)) |
           QSYS_STORMLIM_CFG_STORM_UNIT(unit ? 1 : 0)                              |
           QSYS_STORMLIM_CFG_STORM_MODE(vtss_cmn_qos_storm_mode(conf->policer_uc, conf->policer_uc_mode)));
    /* BC storm policer */
    if (conf->policer_bc_frame_rate == FALSE) {
        VTSS_E("bit rate not supported on broadcast storm policer");
        return VTSS_RC_ERROR;
    }
    REG_WR(QSYS_STORMLIM_CFG(1),
           QSYS_STORMLIM_CFG_STORM_RATE(vtss_cmn_qos_packet_rate(conf->policer_bc, &unit)) |
           QSYS_STORMLIM_CFG_STORM_UNIT(unit ? 1 : 0)                              |
           QSYS_STORMLIM_CFG_STORM_MODE(vtss_cmn_qos_storm_mode(conf->policer_bc, conf->policer_bc_mode)));
    /* MC storm policer */
    if (conf->policer_mc_frame_rate == FALSE) {
        VTSS_E("bit rate not supported on multicast storm policer");
        return VTSS_RC_ERROR;
    }
    REG_WR(QSYS_STORMLIM_CFG(2),
           QSYS_STORMLIM_CFG_STORM_RATE(vtss_cmn_qos_packet_rate(conf->policer_mc, &unit)) |
           QSYS_STORMLIM_CFG_STORM_UNIT(unit ? 1 : 0)                              |
           QSYS_STORMLIM_CFG_STORM_MODE(vtss_cmn_qos_storm_mode(conf->policer_mc, conf->policer_mc_mode)));

    /* DSCP classification and remarking configuration
     */
    for (i = 0; i < 64; i++) {
        REG_WR(ANA_DSCP_CFG(i),
               ANA_DSCP_CFG_DP_DSCP_VAL(conf->dscp_dp_level_map[i] ? 1 : 0)                               |
               ANA_DSCP_CFG_QOS_DSCP_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->dscp_qos_class_map[i])) |
               ANA_DSCP_CFG_DSCP_TRANSLATE_VAL(conf->dscp_translate_map[i])                               |
               ANA_DSCP_CFG_DSCP_TRUST_ENA(conf->dscp_trust[i] ? 1 : 0)                                   |
               ANA_DSCP_CFG_DSCP_REWR_ENA(conf->dscp_remark[i] ? 1 : 0));

        REG_WR(REW_DSCP_RM_CFG(i),
               REW_DSCP_RM_CFG_VAL(conf->dscp_remap[i]));

        REG_WR(REW_DSCP_RM_DP1_CFG(i),
               REW_DSCP_RM_DP1_CFG_DP1_VAL(conf->dscp_remap_dp1[i]));
    }

    /* DSCP classification from QoS configuration
     */
    for (i = 0; i < 8; i++) {
        REG_WR(ANA_DSCP_REWR_CFG(i),
               ANA_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL(conf->dscp_qos_map[i]));

        REG_WR(ANA_DSCP_REWR_CFG(i + 8),
               ANA_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL(conf->dscp_qos_map_dp1[i]));
    }

    /* WRED configuration
     */
    VTSS_RC(lan966x_qos_wred_conf_set(vtss_state));

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
static vtss_rc lan966x_evc_policer_conf_set(vtss_state_t *vtss_state,  const vtss_evc_policer_id_t policer_id)
{
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
static vtss_rc lan966x_qos_cpu_port_shaper_set(vtss_state_t *vtss_state,  const vtss_bitrate_t rate)
{
    u32           i, se, queue, packet_rate;
    vtss_shaper_t shaper;

    for (i = 0; i < 2; i++) {
        /* CPU port shaper at level 1 (kbps) */
        se = (CPU_PORT_0_SE_INDEX + i);
        memset(&shaper, 0, sizeof(shaper));
        shaper.rate  = rate;       // kbps
        shaper.level = (4096 * 4); // 16 kbytes burst size
        VTSS_RC(lan966x_qos_shaper_conf_set(vtss_state, &shaper, se, FALSE, 0, 0, NULL));

        for (queue = 0; queue < 8; queue++) {
            /* CPU queue shapers at level 2, 1 FPS corresponds to 100 kbps */
            se = HSCH_L2_SE(VTSS_CHIP_PORT_CPU_0 + i, queue);
            packet_rate = vtss_state->packet.rx_conf.queue[queue].rate;
            shaper.rate  = (packet_rate == VTSS_PACKET_RATE_DISABLED ? VTSS_BITRATE_DISABLED : packet_rate * 100);
            shaper.level = 4096;
            shaper.mode = 3;
            VTSS_RC(lan966x_qos_shaper_conf_set(vtss_state, &shaper, se, FALSE, 0, 0, NULL));
        }
    }
    return VTSS_RC_OK;
}
#endif

static vtss_rc lan966x_qos_status_get(vtss_state_t *vtss_state, vtss_qos_status_t *status)
{
    memset(status, 0, sizeof(*status));

#if defined(VTSS_FEATURE_STORM_POLICER_DROP_COUNTER)
    status->storm = vtss_state->qos.storm;
    vtss_state->qos.storm = FALSE;
#endif
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc lan966x_qos_debug(vtss_state_t               *vtss_state,
                                 const vtss_debug_printf_t  pr,
                                 const vtss_debug_info_t    *const info)
{
    u32            i, port, pir, value, mode, terminal_se, dwrr_se;
    u32            cir, qmap;
    int            queue;
    BOOL           header = 1;
    vtss_port_no_t port_no;
    char           buf[16];

    /* Global configuration starts here */

    pr("QoS WRED Config has been moved to 'debug api cil wm'\n\n");

    vtss_debug_print_header(pr, "QoS Storm Control");

    REG_RD(QSYS_STORMLIM_BURST, &value);
    pr("Burst: %u\n", QSYS_STORMLIM_BURST_STORM_BURST_X(value));
    for (i = 0; i < 3; i++) {
        const char *name = (i == 0 ? "UC" : i == 1 ? "BC" : "MC");
        REG_RD(QSYS_STORMLIM_CFG(i), &value);
        pr("%s   : Rate %2u, Unit %u, Mode %u\n", name,
           QSYS_STORMLIM_CFG_STORM_RATE_X(value),
           QSYS_STORMLIM_CFG_STORM_UNIT_X(value),
           QSYS_STORMLIM_CFG_STORM_MODE_X(value));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS DSCP Config");

    pr("DSCP Trans CLS DPL Rewr Trust Remap_DP0 Remap_DP1\n");
    for (i = 0; i < 64; i++) {
        u32 dscp_cfg, dscp_remap, dscp_remap_dp1;
        REG_RD(ANA_DSCP_CFG(i), &dscp_cfg);
        REG_RD(REW_DSCP_RM_CFG(i), &dscp_remap);
        REG_RD(REW_DSCP_RM_DP1_CFG(i), &dscp_remap_dp1);

        pr("%4u %5u %3u %3u %4u %5u %5u     %5u\n",
           i,
           ANA_DSCP_CFG_DSCP_TRANSLATE_VAL_X(dscp_cfg),
           ANA_DSCP_CFG_QOS_DSCP_VAL_X(dscp_cfg),
           ANA_DSCP_CFG_DP_DSCP_VAL_X(dscp_cfg),
           ANA_DSCP_CFG_DSCP_REWR_ENA_X(dscp_cfg),
           ANA_DSCP_CFG_DSCP_TRUST_ENA_X(dscp_cfg),
           REW_DSCP_RM_CFG_VAL_X(dscp_remap),
           REW_DSCP_RM_DP1_CFG_DP1_VAL_X(dscp_remap_dp1));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS DSCP Classification from QoS Config");

    pr("QoS DSCP_DP0 DSCP_DP1\n");
    for (i = 0; i < 8; i++) {
        u32 qos_dp0, qos_dp1;
        REG_RD(ANA_DSCP_REWR_CFG(i), &qos_dp0);
        REG_RD(ANA_DSCP_REWR_CFG(i + 8), &qos_dp1);
        pr("%3u %4u     %4u\n",
           i,
           ANA_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL_X(qos_dp0),
           ANA_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL_X(qos_dp1));
    }
    pr("\n");

    /* Per port configuration starts here */

    vtss_debug_print_header(pr, "QoS Port Classification Config");

    pr("LP CP PCP CLS DEI DPL TC_EN DC_EN\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 vlan, qos;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        REG_RD(ANA_VLAN_CFG(port), &vlan);
        REG_RD(ANA_QOS_CFG(port), &qos);
        pr("%2u %2u %3u %3u %3u %3u %5u %5u\n",
           port_no, // Logical port
           port,    // Chip port
           ANA_VLAN_CFG_VLAN_PCP_X(vlan),
           ANA_QOS_CFG_QOS_DEFAULT_VAL_X(qos),
           ANA_VLAN_CFG_VLAN_DEI_X(vlan),
           ANA_QOS_CFG_DP_DEFAULT_VAL_X(qos),
           ANA_QOS_CFG_QOS_PCP_ENA_X(qos),
           ANA_QOS_CFG_QOS_DSCP_ENA_X(qos));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Classification PCP, DEI to QoS class, DP level Mapping");

    pr("LP CP QoS class (8*DEI+PCP)           DP level (8*DEI+PCP)\n");
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
                REG_RD(ANA_PCP_DEI_CFG(port, (8*dei + pcp)), &value);
                class_ct += snprintf(class_buf + class_ct, sizeof(class_buf) - class_ct, "%s%u", delim,
                                     ANA_PCP_DEI_CFG_QOS_PCP_DEI_VAL_X(value));
                dpl_ct   += snprintf(dpl_buf   + dpl_ct,   sizeof(dpl_buf)   - dpl_ct,   "%s%u",  delim,
                                     ANA_PCP_DEI_CFG_DP_PCP_DEI_VAL_X(value));
            }
        }
        pr("%2u %2u %s %s\n", port_no, port, class_buf, dpl_buf);
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Scheduler Config");

    pr("LP CP   SE Base IdxSel InpSel RR_ENA DWRR C0 C1 C2 C3 C4 C5 C6 C7\n");
    for (port_no = VTSS_PORT_NO_START; port_no < (vtss_state->port_count + 2); port_no++) {
        if (port_no < vtss_state->port_count) {
            if (!info->port_list[port_no]) {
                continue;
            }
            port = VTSS_CHIP_PORT(port_no);
            sprintf(buf, "%2u", port_no);
        } else {
            i = (port_no - vtss_state->port_count);
            port = (VTSS_CHIP_PORT_CPU_0 + i);
            sprintf(buf, "C%u", i);
        }
        dwrr_se = TERMINAL_SE_INDEX_OFFSET + port;
        REG_RD(QSYS_QMAP(port), &qmap);
        REG_RD(QSYS_SE_CFG(dwrr_se), &value);
        pr("%s %2u %4u %4u %6u %6u %6u %4u",
           buf,     // Logical port
           port,    // Chip port
           dwrr_se,
           QSYS_QMAP_SE_BASE_X(qmap),
           QSYS_QMAP_SE_IDX_SEL_X(qmap),
           QSYS_QMAP_SE_INP_SEL_X(qmap),
           QSYS_SE_CFG_SE_RR_ENA_X(value),
           QSYS_SE_CFG_SE_DWRR_CNT_X(value));
        for (queue = 0; queue < 8; queue++) {
            REG_RD(QSYS_SE_DWRR_CFG(dwrr_se, queue), &value);
            pr(" %2u", QSYS_SE_DWRR_CFG_DWRR_COST_X(value));
        }
        pr("\n");
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port and Queue Shaper Config");

    pr("LP CP Queue SE  CBS  CIR    EBS  EIR    SE_PRIO SE_SPORT SE_DPORT Excess Credit SE_FRM_MODE\n");
    for (port_no = VTSS_PORT_NO_START; port_no < (vtss_state->port_count + 2); port_no++) {
        u32 eir, sense, excess;
        if (port_no < vtss_state->port_count) {
            if (!info->port_list[port_no]) {
                continue;
            }
            port = VTSS_CHIP_PORT(port_no);
            sprintf(buf, "%2u", port_no);
        } else {
            i = (port_no - vtss_state->port_count);
            port = (VTSS_CHIP_PORT_CPU_0 + i);
            sprintf(buf, "C%u", i);
        }
        terminal_se = TERMINAL_SE_INDEX_OFFSET + port;

        REG_RD(QSYS_CIR_CFG(terminal_se), &value);
        REG_RD(QSYS_EIR_CFG(terminal_se), &eir);
        REG_RD(QSYS_SE_DLB_SENSE(terminal_se), &sense);
        pr("%s %2u     - %3u 0x%02x 0x%04x 0x%02x 0x%04x ",
           buf,
           port,
           terminal_se,
           QSYS_CIR_CFG_CIR_BURST_X(value),
           QSYS_CIR_CFG_CIR_RATE_X(value),
           QSYS_EIR_CFG_EIR_BURST_X(eir),
           QSYS_EIR_CFG_EIR_RATE_X(eir));
        if (QSYS_SE_DLB_SENSE_SE_DLB_PRIO_ENA_X(sense)) {
            pr("%7u ", QSYS_SE_DLB_SENSE_SE_DLB_PRIO_ENA_X(sense));
        } else {
            pr("      - ");
        }
        if (QSYS_SE_DLB_SENSE_SE_DLB_SPORT_ENA_X(sense)) {
            pr("%8u ", QSYS_SE_DLB_SENSE_SE_DLB_SPORT_ENA_X(sense));
        } else {
            pr("       - ");
        }
        if (QSYS_SE_DLB_SENSE_SE_DLB_DPORT_ENA_X(sense)) {
            pr("%8u ", QSYS_SE_DLB_SENSE_SE_DLB_DPORT_ENA_X(sense));
        } else {
            pr("       - ");
        }
        pr("     - ");
        pr("     - ");
        REG_RD(QSYS_SE_CFG(terminal_se), &value);
        pr("%11u\n", QSYS_SE_CFG_SE_FRM_MODE_X(value));
        for (queue = 0; queue < 8; queue++) {
            BOOL cir_only = FALSE;
            u32  queue_shaper_se;

            queue_shaper_se = HSCH_L2_SE(port, queue);

            REG_RD(QSYS_CIR_CFG(queue_shaper_se), &value);
            if (cir_only) {
                excess = 0;
                eir = 0;
                sense = 0;
            } else {
                REG_RD(QSYS_SE_CFG(queue_shaper_se), &excess);
                REG_RD(QSYS_EIR_CFG(queue_shaper_se), &eir);
                REG_RD(QSYS_SE_DLB_SENSE(queue_shaper_se), &sense);
            }
            pr("      %5d %3u 0x%02x 0x%04x 0x%02x 0x%04x ",
               queue,
               queue_shaper_se,
               QSYS_CIR_CFG_CIR_BURST_X(value),
               QSYS_CIR_CFG_CIR_RATE_X(value),
               QSYS_EIR_CFG_EIR_BURST_X(eir),
               QSYS_EIR_CFG_EIR_RATE_X(eir)
                );
            if (QSYS_SE_DLB_SENSE_SE_DLB_PRIO_ENA_X(sense)) {
                pr("%7u ", QSYS_SE_DLB_SENSE_SE_DLB_PRIO_ENA_X(sense));
            } else {
                pr("      - ");
            }
            if (QSYS_SE_DLB_SENSE_SE_DLB_SPORT_ENA_X(sense)) {
                pr("%8u ", QSYS_SE_DLB_SENSE_SE_DLB_SPORT_ENA_X(sense));
            } else {
                pr("       - ");
            }
            if (QSYS_SE_DLB_SENSE_SE_DLB_DPORT_ENA_X(sense)) {
                pr("%8u ", QSYS_SE_DLB_SENSE_SE_DLB_DPORT_ENA_X(sense));
            } else {
                pr("       - ");
            }
            pr("%6d ", QSYS_SE_CFG_SE_EXC_ENA_X(excess));
            pr("%6d ", QSYS_SE_CFG_SE_AVB_ENA_X(excess));
            REG_RD(QSYS_SE_CFG(queue_shaper_se), &value);
            pr("%11u\n", QSYS_SE_CFG_SE_FRM_MODE_X(value));
        }
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS CPU Port Shaper Config");
    pr("CPU CP SE  CBS  CIR\n");
    REG_RD(QSYS_CIR_CFG(CPU_PORT_0_SE_INDEX), &value);
    pr("%3u %2u %3u 0x%02x 0x%04x\n",
       0,
       VTSS_CHIP_PORT_CPU_0,
       CPU_PORT_0_SE_INDEX,
       QSYS_CIR_CFG_CIR_BURST_X(value),
       QSYS_CIR_CFG_CIR_RATE_X(value));
    REG_RD(QSYS_CIR_CFG(CPU_PORT_1_SE_INDEX), &value);
    pr("%3u %2u %3u 0x%02x 0x%04x\n",
       1,
       VTSS_CHIP_PORT_CPU_1,
       CPU_PORT_1_SE_INDEX,
       QSYS_CIR_CFG_CIR_BURST_X(value),
       QSYS_CIR_CFG_CIR_RATE_X(value));
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Tag Remarking Config");

    pr("LP CP MPCP MDEI PCP DEI\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 tag_default, tag_ctrl;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        REG_RD(REW_PORT_VLAN_CFG(port), &tag_default);
        REG_RD(REW_TAG_CFG(port), &tag_ctrl);
        pr("%2u %2u %4x %4x %3d %3d\n",
           port_no,
           port,
           REW_TAG_CFG_TAG_PCP_CFG_X(tag_ctrl),
           REW_TAG_CFG_TAG_DEI_CFG_X(tag_ctrl),
           REW_PORT_VLAN_CFG_PORT_PCP_X(tag_default),
           REW_PORT_VLAN_CFG_PORT_DEI_X(tag_default));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Tag Remarking Map");

    pr("LP CP PCP (2*QoS class+DPL)           DEI (2*QoS class+DPL)\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        int class, dpl, pcp_ct = 0, dei_ct = 0;
        char pcp_buf[40], dei_buf[40];
        if (info->port_list[port_no] == 0)
            continue;
        port = VTSS_CHIP_PORT(port_no);
        for (class = VTSS_QUEUE_START; class < VTSS_QUEUE_END; class++) {
            for (dpl = 0; dpl < 2; dpl++) {
                const char *delim = ((class == VTSS_QUEUE_START) && (dpl == 0)) ? "" : ",";
                REG_RD(REW_PCP_DEI_CFG(port, (8*dpl + class)), &value);
                pcp_ct += snprintf(pcp_buf + pcp_ct, sizeof(pcp_buf) - pcp_ct, "%s%u", delim,
                                   REW_PCP_DEI_CFG_PCP_QOS_VAL_X(value));
                dei_ct += snprintf(dei_buf + dei_ct, sizeof(dei_buf) - dei_ct, "%s%u",  delim,
                                   REW_PCP_DEI_CFG_DEI_QOS_VAL_X(value));
            }
        }
        pr("%2u %2u %s %s\n", port_no, port, pcp_buf, dei_buf);
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port DSCP Remarking Config");

    pr("LP CP I_Mode Trans E_Mode\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 qos_cfg, dscp_cfg;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        REG_RD(ANA_QOS_CFG(port), &qos_cfg);
        REG_RD(REW_DSCP_CFG(port), &dscp_cfg);
        pr("%2u %2u %6u %5u %6u\n",
           port_no,
           port,
           ANA_QOS_CFG_DSCP_REWR_CFG_X(qos_cfg),
           ANA_QOS_CFG_DSCP_TRANSLATE_ENA_X(qos_cfg),
           REW_DSCP_CFG_DSCP_REWR_CFG_X(dscp_cfg));
    }
    pr("\n");

    VTSS_RC(vtss_lan966x_debug_range_checkers(vtss_state, pr, info));
    VTSS_RC(vtss_lan966x_debug_is1_all(vtss_state, pr, info));

    vtss_debug_print_header(pr, "QoS Port and Queue Policer");

    vtss_lan966x_debug_reg_header(pr, "Policer Config (chip ports)");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_CFG(port)), port, "POL_CFG");
        vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_FLOWC(port)), port, "POL_FLOWC");
    }
    pr("\n");

    vtss_debug_print_header(pr, "Policers");

    header = 1;
    for (i = 0; i < LAN966X_POLICER_CNT; i++) {
        REG_RD(ANA_POL_PIR_CFG(i), &pir);
        if (pir == 0) {
            continue;
        }

        if (header) {
            pr("Index  Mode  Dual  IFG  CF  OS  PIR    PBS  CIR    CBS\n");
            header = 0;
        }

#if defined(LAN966X_POLICER_EVC)
        if (!info->full && i >= LAN966X_POLICER_EVC) {
            pr("Use 'full' to see all of the %d policers!", LAN966X_POLICER_CNT);
            break;
        }
#endif /* LAN966X_POLICER_EVC */

        REG_RD(ANA_POL_MODE(i), &value);
        REG_RD(ANA_POL_CIR_CFG(i), &cir);
        mode = ANA_POL_MODE_FRM_MODE_X(value);
        pr("%-7u%-6s%-6u%-5u%-4u%-4u%-7u%-5u%-7u%-5u\n",
           i,
           mode == POL_MODE_LINERATE ? "Line" : mode == POL_MODE_DATARATE ? "Data" :
           mode == POL_MODE_FRMRATE_33_1_3_FPS ? "F33_1_3" : "F1_3",
           ANA_POL_MODE_CIR_ENA_X(value),
           ANA_POL_MODE_IPG_SIZE_X(value),
           ANA_POL_MODE_DLB_COUPLED_X(value),
           ANA_POL_MODE_OVERSHOOT_ENA_X(value),
           ANA_POL_PIR_CFG_PIR_RATE_X(pir),
           ANA_POL_PIR_CFG_PIR_BURST_X(pir),
           ANA_POL_CIR_CFG_CIR_RATE_X(cir),
           ANA_POL_CIR_CFG_CIR_BURST_X(cir)
            );
    }
    if (!header) {
        pr("\n");
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_qos_debug_print(vtss_state_t               *vtss_state,
                                     const vtss_debug_printf_t  pr,
                                     const vtss_debug_info_t    *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_QOS, lan966x_qos_debug, vtss_state, pr, info);
}


/* - Initialization ------------------------------------------------ */

vtss_rc vtss_lan966x_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_qos_state_t *state = &vtss_state->qos;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->conf_set = lan966x_qos_conf_set;
        state->port_conf_set = vtss_cmn_qos_port_conf_set;
        state->port_conf_update = lan966x_qos_port_conf_set;
        state->status_get = lan966x_qos_status_get;
        state->qce_add = vtss_cmn_qce_add;
        state->qce_del = vtss_cmn_qce_del;
#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
        state->cpu_port_shaper_set = lan966x_qos_cpu_port_shaper_set;
#endif
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
        state->evc_policer_conf_set = lan966x_evc_policer_conf_set;
#endif
#if defined(VTSS_FEATURE_EVC_POLICERS)
        state->evc_policer_max = 1022;
#endif
        state->prio_count = LAN966X_PRIOS;
        break;

    case VTSS_INIT_CMD_INIT:
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        break;

    case VTSS_INIT_CMD_POLL:
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
