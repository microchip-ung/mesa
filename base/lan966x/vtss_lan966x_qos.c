// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X) && defined(VTSS_FEATURE_QOS)

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

vtss_rc vtss_lan966x_qos_policer_conf_set(vtss_state_t *vtss_state, u32 policer, vtss_policer_conf_t *conf)
{
    u32  cir = 0, cbs = 0, pir, pbs, mode;
    u32  cf = 0, pbs_max, cbs_max = 0;
    BOOL pir_discard = 0;
    u32  cir_ena = 0;
    BOOL cir_discard = 0;
    BOOL drop_yellow = 0;
    BOOL mark_all_red = 0;

    pir = conf->eir;
    pbs = conf->ebs;
    if (conf->frame_rate) {
        /* Frame rate policing (single leaky bucket) */

        /* There are two frame rate "modes" that has 33 1/3 frame or 1/3 frame resolution. Use 1/3 frame resolution if possible. The pir configuration bit field is 15 bit wide */
        if (pir >= (0x7FFF / 3)) {  /* PIR rate requires the 33 1/3 frame resolution */
            mode = POL_MODE_FRMRATE_33_1_3_FPS;
            pir = VTSS_DIV_ROUND_UP(pir*3, 100); /* Resolution is in steps of 33 1/3 fps. 33 1/3 => 100/3 */
            pbs = (pbs * 10 / 328);              /* Burst unit is 32.8 frames */
            pbs_max = VTSS_BITMASK(6);           /* Limit burst to the maximum value */
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
            drop_yellow = conf->drop_yellow;
            mark_all_red = conf->mark_all_red.enable;
            if (mark_all_red && conf->mark_all_red.value) {
                pir = 0;
                pbs = 0;
            } else {
                cir = conf->cir;
                cbs = conf->cbs;
            }
            if (cir == 0 && cbs == 0) {
                /* Discard CIR frames */
                cir_discard = 1;
            }
            cir = VTSS_DIV_ROUND_UP(cir*3, 100);/* Rate unit is 33 1/3 kbps, round up */
            cbs = (cbs ? cbs : 1);              /* BZ 9813: Avoid using zero burst size */
            cbs = VTSS_DIV_ROUND_UP(cbs, 4096); /* Burst unit is 4kB, round up */
            cbs_max = 61;                       /* See Bugzilla#4944, comment#2  */
            cir_ena = 1;
            cf = conf->cf;
            if (cf) {
                pir += conf->cir;
                pbs += conf->ebs;
            }
        }
        if (pir == 0 && pbs == 0) {
            /* Discard PIR frames */
            pir_discard = 1;
        }
        pir = VTSS_DIV_ROUND_UP(pir*3, 100); /* Rate unit is 33 1/3 kbps, round up */
        pbs = (pbs ? pbs : 1);               /* BZ 9813: Avoid using zero burst size */
        pbs = VTSS_DIV_ROUND_UP(pbs, 4096);  /* Burst unit is 4kB, round up */
        pbs_max = 61;                        /* See Bugzilla#4944, comment#2  */
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

    // Setup with RED_ENA = 0 and LVL = 0 to be able to clear POL_STATE
    mode = (ANA_POL_MODE_DROP_ON_YELLOW_ENA(drop_yellow) |
            ANA_POL_MODE_MARK_ALL_FRMS_RED_ENA(0) |
            ANA_POL_MODE_IPG_SIZE(20)             |
            ANA_POL_MODE_DLB_COUPLED(cf ? 1 : 0)  |
            ANA_POL_MODE_CIR_ENA(cir_ena ? 1 : 0) |
            ANA_POL_MODE_FRM_MODE(mode)           |
            ANA_POL_MODE_OVERSHOOT_ENA(1));
    REG_WR(ANA_POL_MODE(policer), mode);
    REG_WR(ANA_POL_PIR_STATE(policer), ANA_POL_PIR_STATE_PIR_LVL(0));
    REG_WR(ANA_POL_CIR_STATE(policer), ANA_POL_CIR_STATE_CIR_LVL(0));
    REG_WR(ANA_POL_STATE(policer), ANA_POL_STATE_MARK_ALL_FRMS_RED_SET(0));

    // Setup with new RED_ENA mode
    REG_WR(ANA_POL_PIR_CFG(policer), ANA_POL_PIR_CFG_PIR_RATE(pir) | ANA_POL_PIR_CFG_PIR_BURST(pbs));
    REG_WR(ANA_POL_PIR_STATE(policer), ANA_POL_PIR_STATE_PIR_LVL(pir_discard ? ANA_POL_PIR_STATE_PIR_LVL_M : 0));
    REG_WR(ANA_POL_CIR_CFG(policer), ANA_POL_CIR_CFG_CIR_RATE(cir) | ANA_POL_CIR_CFG_CIR_BURST(cbs));
    REG_WR(ANA_POL_CIR_STATE(policer), ANA_POL_CIR_STATE_CIR_LVL(cir_discard ? ANA_POL_CIR_STATE_CIR_LVL_M : 0));
    REG_WR(ANA_POL_MODE(policer), mode | ANA_POL_MODE_MARK_ALL_FRMS_RED_ENA(mark_all_red));

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
                wm_red_low  = MIN(wm_red_low / 1024, VTSS_BITMASK(8));                 /* Convert from bytes to 960 byte chunks and prevent overflow */
                wm_red_high = MIN(wm_red_high / 1024, VTSS_BITMASK(8));                /* Convert from bytes to 960 byte chunks and prevent overflow */
            } else {
                wm_red_low = wm_red_high = VTSS_BITMASK(8);                            /* Disable red by setting both fields to max */
            }

            REG_WR(QSYS_RED_PROFILE((queue + (8 * dpl))), /* Red profile for queue, dpl */
                   QSYS_RED_PROFILE_WM_RED_LOW(wm_red_low) |
                   QSYS_RED_PROFILE_WM_RED_HIGH(wm_red_high));
        }
    }

    VTSS_RC(vtss_lan966x_wm_update(vtss_state)); /* Update watermarks */

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_queue_cut_through_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_fp_port_conf_t *conf = &vtss_state->qos.fp.port_conf[port_no];
    u32                     i, ct_ena = 0, port = VTSS_CHIP_PORT(port_no);

    for (i = 0; i < 8; i++) {
        // If frame preemption is enabled, cut-through is disabled
        if ((conf->enable_tx == 0 || conf->admin_status[i] == 0) &&
            vtss_state->qos.port_conf[port_no].cut_through_enable[i]) {
            ct_ena |= VTSS_BIT(i);
        }
    }
    REG_WR(ANA_CUT_THRU_CFG(port), ANA_CUT_THRU_CFG_CUT_THRU_ENA(ct_ena));
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

    /* Cut-through configuration */
    VTSS_RC(lan966x_qos_queue_cut_through_set(vtss_state, port_no));

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
    VTSS_MEMSET(&pol_cfg, 0, sizeof(pol_cfg));
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
        VTSS_MEMSET(&pol_cfg, 0, sizeof(pol_cfg));
        if (conf->policer_queue[queue].rate != VTSS_BITRATE_DISABLED) {
            pol_cfg.eir = conf->policer_queue[queue].rate;
            pol_cfg.ebs = conf->policer_queue[queue].level;
        } else {
            pol_cfg.disable = TRUE;
        }
        VTSS_RC(lan966x_queue_policer_set(vtss_state, port, queue, conf->policer_queue[queue].rate != VTSS_BITRATE_DISABLED, &pol_cfg));
    }

#if defined(VTSS_FEATURE_VCAP)
    /* Update QCL port configuration */
    VTSS_RC(vtss_lan966x_vcap_port_key_addr_set(vtss_state,
                                                port_no,
                                                2, /* Third IS1 lookup */
                                                vtss_state->qos.port_conf[port_no].key_type,
                                                vtss_state->qos.port_conf_old.key_type,
                                                vtss_state->qos.port_conf[port_no].dmac_dip));
#endif
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
        VTSS_MEMSET(&shaper, 0, sizeof(shaper));
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
    VTSS_MEMSET(status, 0, sizeof(*status));

#if defined(VTSS_FEATURE_STORM_POLICER_DROP_COUNTER)
    status->storm = vtss_state->qos.storm;
    vtss_state->qos.storm = FALSE;
#endif
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_QOS_TAS)
#define TAS_LIST_STATE_ADMIN       0
#define TAS_LIST_STATE_ADVANCING   1
#define TAS_LIST_STATE_PENDING     2
#define TAS_LIST_STATE_OPERATING   3
#define TAS_LIST_STATE_TERMINATING 4

#define TAS_LIST_IDX_NONE    0xFFFFFFFF
#define TAS_PROFILE_IDX_NONE 0xFFFFFFFF
#define TAS_ENTRY_IDX_NONE   0xFFFFFFFF

#define TAS_LIST_STATE_ADMIN       0
#define TAS_LIST_STATE_ADVANCING   1
#define TAS_LIST_STATE_PENDING     2
#define TAS_LIST_STATE_OPERATING   3
#define TAS_LIST_STATE_TERMINATING 4

#define TAS_LIST_IDX_NONE    0xFFFFFFFF
#define TAS_PROFILE_IDX_NONE 0xFFFFFFFF
#define TAS_ENTRY_IDX_NONE   0xFFFFFFFF

static u32 tas_profile_allocate(vtss_state_t *vtss_state,  const vtss_port_no_t port_no)
{
    u32                 profile_idx;
    vtss_tas_profile_t  *tas_profiles = vtss_state->qos.tas.tas_profiles;

    for (profile_idx = 0; profile_idx < VTSS_TAS_NUMBER_OF_PROFILES; ++profile_idx) {
        if (!tas_profiles[profile_idx].in_use) { /* Find a unused profile */
            break;
        }
    }
    if (profile_idx == VTSS_TAS_NUMBER_OF_PROFILES) {
        VTSS_D("No free TAS profile was found");
        return TAS_PROFILE_IDX_NONE;
    }

    tas_profiles[profile_idx].in_use = TRUE;
    tas_profiles[profile_idx].port_no = port_no;

    return profile_idx;
}

static vtss_rc tas_profile_free(vtss_state_t *vtss_state,  u32 profile_idx)
{
    vtss_tas_profile_t  *tas_profiles = vtss_state->qos.tas.tas_profiles;

    if (profile_idx >= VTSS_TAS_NUMBER_OF_PROFILES) {
        return VTSS_RC_ERROR;
    }

    tas_profiles[profile_idx].in_use = FALSE;

    return VTSS_RC_OK;
}

static u32 tas_list_allocate(vtss_state_t *vtss_state,  u32 length)
{
    u32                     i, list_idx, found, first_entry = 0;
    BOOL                    first;
    vtss_tas_list_t         *tas_lists = vtss_state->qos.tas.tas_lists;
    vtss_tas_list_entry     *entries = vtss_state->qos.tas.tas_entries;

    VTSS_D("Enter length %u", length);

    /* Find a unused list */
    for (list_idx = 0; list_idx < VTSS_TAS_NUMBER_OF_LISTS; ++list_idx) {
        if (!tas_lists[list_idx].in_use) { /* Find a unused list */
            break;
        }
    }
    if (list_idx == VTSS_TAS_NUMBER_OF_LISTS) {
        VTSS_D("No free TAS list was found");
        return TAS_LIST_IDX_NONE;
    }

    /* Check that there are unused list entries for the complete list */
    for (i = 0, found = 0, first = TRUE; ((found < length) && (i < VTSS_TAS_NUMBER_OF_ENTRIES)); ++i) {
        if (!entries[i].in_use) {
            if (first) {
                first = FALSE;
                first_entry = i;
            }
            found += 1;
        }
    }

    if (found == length) {
        tas_lists[list_idx].in_use = TRUE; /* The found list is now in use */
        tas_lists[list_idx].entry_idx = first_entry;
        entries[first_entry].in_use = TRUE; /* Only the first element is actually reserved, but we know that there are unused entries for the complete list */
    } else {
        VTSS_D("No free entry slot was found in any row");
        return TAS_LIST_IDX_NONE;
    }

    VTSS_D("Exit list_idx %u", list_idx);

    return list_idx;
}

static vtss_rc tas_list_free(vtss_state_t *vtss_state,  u32 list_idx)
{
    u32                     entry_idx, value;
    vtss_tas_list_t         *tas_lists = vtss_state->qos.tas.tas_lists;
    vtss_tas_list_entry     *entries = vtss_state->qos.tas.tas_entries;

    if (list_idx >= VTSS_TAS_NUMBER_OF_LISTS) {
        return VTSS_RC_ERROR;
    }

    VTSS_D("Enter list_idx %u  entry_idx %u", list_idx, tas_lists[list_idx].entry_idx);

    if (tas_lists[list_idx].entry_idx < VTSS_TAS_NUMBER_OF_ENTRIES) { /* Check if the list has entries */
        /* Mark all entries as unused */
        entry_idx = tas_lists[list_idx].entry_idx;
        do {
            /* Select the list entry */
            REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_GCL_ENTRY_NUM(entry_idx), QSYS_TAS_CFG_CTRL_GCL_ENTRY_NUM_M);

            entries[entry_idx].in_use = FALSE;  /* Mark as unused */

            /* Read the next GCL entry index */
            REG_RD(QSYS_TAS_GCL_CT_CFG2, &value);
            entry_idx = QSYS_TAS_GCL_CT_CFG2_NEXT_GCL_X(value);
        } while(entry_idx != tas_lists[list_idx].entry_idx);
    }

    if (!tas_lists[list_idx].inherit_profile) {   /* Inherit profiles are not freed */
        (void)tas_profile_free(vtss_state, tas_lists[list_idx].profile_idx); /* Free any possible profile */
    }

    tas_lists[list_idx].in_use = FALSE; /* Free the list */
    tas_lists[list_idx].inherit_profile = FALSE;
    tas_lists[list_idx].profile_idx = TAS_PROFILE_IDX_NONE;
    tas_lists[list_idx].entry_idx = TAS_ENTRY_IDX_NONE;

    return VTSS_RC_OK;
}

static void tas_next_unused_entry_get(vtss_state_t *vtss_state,  u32 *entry_idx)
{
    u32                  i;
    vtss_tas_list_entry  *entries = vtss_state->qos.tas.tas_entries;

    for (i = *entry_idx + 1; i < VTSS_TAS_NUMBER_OF_ENTRIES; ++i) {
        if (!entries[i].in_use) {
            *entry_idx = i;
            entries[i].in_use = TRUE;
            return;
        }
    }
}

static u8 tas_link_speed_calc(vtss_port_speed_t speed)
{
    switch (speed) {
        case VTSS_SPEED_UNDEFINED: return 0;
        case VTSS_SPEED_AUTO:      return 0;
        case VTSS_SPEED_10M:       return 1;
        case VTSS_SPEED_100M:      return 2;
        case VTSS_SPEED_1G:        return 3;
        case VTSS_SPEED_2500M:     return 4;
        case VTSS_SPEED_5G:        return 5;
        case VTSS_SPEED_10G:       return 6;
        case VTSS_SPEED_12G:       return 0;
        case VTSS_SPEED_25G:       return 7;
    }
    return 0;
}

static vtss_qos_tas_gco_t tas_gate_operation_calc(u32 value)
{
    switch (value) {
    case 0: return VTSS_QOS_TAS_GCO_SET_GATE_STATES;
    case 2: return VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC;
    case 3: return VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC;
    }

    VTSS_E("Unknown register QSYS:TAS_GCL_CFG:TAS_GCL_CTRL_CFG.OP_TYPE value");
    return VTSS_QOS_TAS_GCO_SET_GATE_STATES;
}

static u32 tas_op_type_calc(vtss_qos_tas_gco_t  gate_operation)
{
    switch (gate_operation) {
    case VTSS_QOS_TAS_GCO_SET_GATE_STATES: return 0;
    case VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC: return 2;
    case VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC: return 3;
    }

    VTSS_E("Unknown register QSYS:TAS_GCL_CFG:TAS_GCL_CTRL_CFG.OP_TYPE value");
    return VTSS_QOS_TAS_GCO_SET_GATE_STATES;
}

static BOOL tas_time_stamp_diff(vtss_timestamp_t *ts, vtss_timestamp_t *ts_sub, u32 *diff)
{
    vtss_timestamp_t  diff_time;

    diff_time = *ts;
    if (vtss_timestampSub(&diff_time, ts_sub) != VTSS_RC_OK) {
        return FALSE;
    }

    /* Convert diff_time to u32 */
    *diff = diff_time.nanoseconds + diff_time.seconds * 1000000000; /* Without including 'sec_msb' the difference can be up to 136 years - must be enough */

    return TRUE;
}

static BOOL tas_trunk_port_conf_calc(vtss_qos_tas_port_conf_t  *current_port_conf,
                                     vtss_timestamp_t          *current_end_time,
                                     vtss_timestamp_t          *new_start_time,
                                     vtss_qos_tas_port_conf_t  *trunk_port_conf)
{
    /* Trunk list is calculated to start at the end of current list and to end cycle at new list start time */
    u32 trunk_duration, interval_sum = 0, i = 0;
    vtss_timestamp_t  trunk_duration_time;

    VTSS_MEMSET(trunk_port_conf, 0, sizeof(*trunk_port_conf));

    /* Calculate max duration of trunk list */
    trunk_duration_time = *new_start_time;
    if (vtss_timestampSub(&trunk_duration_time, current_end_time) != VTSS_RC_OK) {
        return FALSE;
    }

    /* Convert duration time to u32 */
    trunk_duration = trunk_duration_time.nanoseconds + trunk_duration_time.seconds * 1000000000; /* Without including 'sec_msb' the gap can be up to 136 years - must be enough */

    /* Copy the full current port configuration toe trunk */
    VTSS_MEMCPY(trunk_port_conf, current_port_conf, sizeof(*trunk_port_conf));

    /* Calculate the required number of GCL list entries in the trunk list */
    for (i = 0; i < current_port_conf->gcl_length; ++i) {
        if (trunk_duration >= (interval_sum + current_port_conf->gcl[i].time_interval)) {    /* Stop if the trunk list is getting longer than the required trunk duration */
            interval_sum += current_port_conf->gcl[i].time_interval;
        } else {
            break;
        }
    }

    /* Check if any entries got into the trunk list */
    if (i == 0) {
        return FALSE;
    }

    /* Set the length of the trunk list */
    trunk_port_conf->gcl_length = i;

    /* Set the base time of the trunk list to end of current list */
    trunk_port_conf->base_time = *current_end_time;

    /* Set the cycle time of the trunk list to the trunk duration. This might be longer than the trunk interval sum but then then last gate sate will be extended */
    trunk_port_conf->cycle_time = trunk_duration;

    return TRUE;
}

static void tas_stop_port_conf_calc(vtss_timestamp_t *current_end_time, BOOL *gate_open, vtss_qos_tas_port_conf_t *stop_port_conf)
{
    VTSS_MEMSET(stop_port_conf, 0, sizeof(*stop_port_conf));

    stop_port_conf->base_time = *current_end_time;
    stop_port_conf->cycle_time = 1000;
    stop_port_conf->gcl_length = 1;
    stop_port_conf->gcl[0].gate_operation = VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC;
    VTSS_MEMCPY(stop_port_conf->gcl[0].gate_open, gate_open, sizeof(stop_port_conf->gcl[0].gate_open));
    stop_port_conf->gcl[0].time_interval = 1000;
}

static vtss_rc tas_current_port_conf_calc(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_qos_tas_port_conf_t *current_port_conf)
{
    u32                   msb, store, value, entry_idx, entry_first, gcl_idx, gate_state;
    vtss_tas_gcl_state_t  *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];

    VTSS_MEMSET(current_port_conf, 0, sizeof(*current_port_conf));
    if (gcl_state->curr_list_idx == TAS_LIST_IDX_NONE) {
        return VTSS_RC_OK;
    }

    /* Store the currently selected list */
    REG_RD(QSYS_TAS_CFG_CTRL, &store);

    /* Select the list */
    REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_LIST_NUM(gcl_state->curr_list_idx), QSYS_TAS_CFG_CTRL_LIST_NUM_M);;

    /* Read the based address of the first entry in the list */
    REG_RD(QSYS_TAS_LIST_CFG, &value);
    entry_idx = entry_first = QSYS_TAS_LIST_CFG_LIST_BASE_ADDR_X(value);

    /* Read the list elements */
    gcl_idx = 0;
    do {
        /* Select the list entry */
        REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_GCL_ENTRY_NUM(entry_idx), QSYS_TAS_CFG_CTRL_GCL_ENTRY_NUM_M);

        /* Read the gate state */
        REG_RD(QSYS_TAS_GCL_CT_CFG, &value);
        gate_state = QSYS_TAS_GCL_CT_CFG_GATE_STATE_X(value);
        vtss_u8_to_bool8(gate_state, current_port_conf->gcl[gcl_idx].gate_open);

        /* Read time interval */
        REG_RD(QSYS_TAS_GCL_TM_CFG, &current_port_conf->gcl[gcl_idx].time_interval);

        /* Read the operational type */
        current_port_conf->gcl[gcl_idx].gate_operation = tas_gate_operation_calc(QSYS_TAS_GCL_CT_CFG_OP_TYPE_X(value));

        /* Read the next GCL entry index */
        REG_RD(QSYS_TAS_GCL_CT_CFG2, &value);
        entry_idx = QSYS_TAS_GCL_CT_CFG2_NEXT_GCL_X(value);

        gcl_idx += 1;
    } while(entry_idx != entry_first);

    /* Save list length */
    current_port_conf->gcl_length = gcl_idx;

    REG_RD(QSYS_TAS_BT_NSEC, &current_port_conf->base_time.nanoseconds);
    REG_RD(QSYS_TAS_BT_SEC_LSB, &current_port_conf->base_time.seconds);
    REG_RD(QSYS_TAS_BT_SEC_MSB, &msb);
    current_port_conf->base_time.sec_msb = (u16)msb;
    REG_RD(QSYS_TAS_CT_CFG, &current_port_conf->cycle_time);

    /* Re-store the currently selected list */
    REG_WR(QSYS_TAS_CFG_CTRL, store);

    return VTSS_RC_OK;
}

static vtss_rc tas_list_state_write(vtss_state_t *vtss_state, u32 list_idx, u32 state)
{
    u32  i = 0, value, store;

    /* Store the currently selected list */
    REG_RD(QSYS_TAS_CFG_CTRL, &store);

    /* Select the list */
    REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_LIST_NUM(list_idx), QSYS_TAS_CFG_CTRL_LIST_NUM_M);

    /* Write the TAS list state. Note that the written state must be read back with same value in oeder to assure correct write */
    do {
        REG_WRM(QSYS_TAS_LST, QSYS_TAS_LST_LIST_STATE(state), QSYS_TAS_LST_LIST_STATE_M);
        REG_RD(QSYS_TAS_LST, &value);
        i++;
    } while((i < 10) && (QSYS_TAS_LST_LIST_STATE_X(value) != state));

    /* Re-store the currently selected list */
    REG_WR(QSYS_TAS_CFG_CTRL, store);

    return VTSS_RC_OK;
}

static vtss_rc tas_list_state_read(vtss_state_t *vtss_state, u32 list_idx, u32 *state)
{
    u32  store, value;

    /* Store the currently selected list */
    REG_RD(QSYS_TAS_CFG_CTRL, &store);

    /* Select the list */
    REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_LIST_NUM(list_idx), QSYS_TAS_CFG_CTRL_LIST_NUM_M);

    /* Read the list state */
    REG_RD(QSYS_TAS_LST, &value);
    *state = QSYS_TAS_LST_LIST_STATE_X(value);

    /* Re-store the currently selected list */
    REG_WR(QSYS_TAS_CFG_CTRL, store);

    return VTSS_RC_OK;
}

static vtss_rc tas_list_base_time_read(vtss_state_t *vtss_state, u32 list_idx, vtss_timestamp_t *base_time)
{
    u32  store, msb;

    /* Store the currently selected list */
    REG_RD(QSYS_TAS_CFG_CTRL, &store);

    /* Select the list */
    REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_LIST_NUM(list_idx), QSYS_TAS_CFG_CTRL_LIST_NUM_M);

    /* Read the base time */
    REG_RD(QSYS_TAS_BT_NSEC, &base_time->nanoseconds);
    REG_RD(QSYS_TAS_BT_SEC_LSB, &base_time->seconds);
    REG_RD(QSYS_TAS_BT_SEC_MSB, &msb);
    base_time->sec_msb = (u16)msb;

    /* Re-store the currently selected list */
    REG_WR(QSYS_TAS_CFG_CTRL, store);

    return VTSS_RC_OK;
}

static vtss_rc tas_list_cycle_time_read(vtss_state_t *vtss_state, u32 list_idx, u32 *cycle_time)
{
    u32  store;

    /* Store the currently selected list */
    REG_RD(QSYS_TAS_CFG_CTRL, &store);

    /* Select the list */
    REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_LIST_NUM(list_idx), QSYS_TAS_CFG_CTRL_LIST_NUM_M);

    /* Read the cycle time */
    REG_RD(QSYS_TAS_CT_CFG, cycle_time);

    /* Re-store the currently selected list */
    REG_WR(QSYS_TAS_CFG_CTRL, store);

    return VTSS_RC_OK;
}

static vtss_rc tas_gate_state_write(vtss_state_t *vtss_state,  vtss_port_no_t port_no,  BOOL *gate_open)
{
    vtss_port_no_t  chip_port = VTSS_CHIP_PORT(port_no);

    REG_WR(QSYS_TAS_GS_CTRL, QSYS_TAS_GS_CTRL_HSCH_POS(chip_port));
    REG_WR(QSYS_TAS_GATE_STATE, QSYS_TAS_GATE_STATE_TAS_GATE_STATE(vtss_bool8_to_u8(gate_open)));

    return VTSS_RC_OK;
}

static vtss_rc tas_gate_state_read(vtss_state_t *vtss_state,  vtss_port_no_t port_no,  BOOL *gate_open)
{
    u32  value;
    vtss_port_no_t  chip_port = VTSS_CHIP_PORT(port_no);

    REG_WR(QSYS_TAS_GS_CTRL, 5040 + 64 + chip_port);
    REG_RD(QSYS_TAS_GATE_STATE, &value);

    vtss_u8_to_bool8(QSYS_TAS_GATE_STATE_TAS_GATE_STATE_X(value), gate_open);

    return VTSS_RC_OK;
}

static BOOL tas_current_end_time_calc(vtss_state_t *vtss_state,  u32 current_list_idx,  vtss_timestamp_t *new_base_time,  vtss_timestamp_t *current_end_time)
{
    vtss_timestamp_t  current_base_time = {}, diff_base_time = {};
    u32               current_cycle_time = 0;
    u64               diff_base_time_u64, current_elapse_time;

    VTSS_MEMSET(current_end_time, 0, sizeof(*current_end_time));

    if (current_list_idx != TAS_LIST_IDX_NONE) {
        /* Get the base time of current list */
        tas_list_base_time_read(vtss_state, current_list_idx, &current_base_time);

        /* Get the cycle time of current list */
        if (VTSS_RC_OK != tas_list_cycle_time_read(vtss_state, current_list_idx, &current_cycle_time)) {
            VTSS_D("tas_list_cycle_time_read() failed");
        }

        /* Calculate the end time of current list as this: */
        /* current_end_time = current_base_time + ((new_base_time - current_base_time) / current_cycle_time) * current_cycle_time */

        /* Calculate base time difference (new_base_time - current_base_time) */
        diff_base_time = *new_base_time;
        if (vtss_timestampSub(&diff_base_time, &current_base_time) != VTSS_RC_OK) {
            return FALSE;
        }

        /* Convert base time difference to u64 */
        diff_base_time_u64 = (u64)diff_base_time.nanoseconds + (u64)((u64)diff_base_time.seconds * (u64)1000000000); /* Without including 'sec_msb' the difference can be up to 136 years - must be enough */

        /* Calculate current elapse time (((new_base_time - current_base_time) / current_cycle_time) * current_cycle_time) */
        current_elapse_time = (diff_base_time_u64 / (u64)current_cycle_time) * (u64)current_cycle_time;

        /* Calculate the current_end_time = current_base_time + current_elapse_time */
        *current_end_time = current_base_time;
        if (vtss_timestampAddNano(current_end_time, current_elapse_time) != VTSS_RC_OK) {
            return FALSE;
        }
    }

    return TRUE;
}

static void tas_gcl_state_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32                   next_state = TAS_LIST_STATE_OPERATING;
    vtss_tas_gcl_state_t  *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];

    if (gcl_state->next_list_idx != TAS_LIST_IDX_NONE) {    /* Start next list is ongoing. Check if done */
        if (VTSS_RC_OK != tas_list_state_read(vtss_state, gcl_state->next_list_idx, &next_state)) {
            VTSS_D("tas_list_state_read() failed");
        }
        if ((next_state == TAS_LIST_STATE_OPERATING) ||
            (next_state == TAS_LIST_STATE_ADMIN)) {   /* Start next list is done or terminated */
            (void)tas_list_free(vtss_state, gcl_state->curr_list_idx);    /* Free any possible valid lists */
            (void)tas_list_free(vtss_state, gcl_state->trunk_list_idx);
            if (gcl_state->stop_ongoing) {  /* The next list is a stop list */
                (void)tas_list_free(vtss_state, gcl_state->next_list_idx);
                tas_list_state_write(vtss_state, gcl_state->next_list_idx, TAS_LIST_STATE_ADMIN);
                gcl_state->curr_list_idx = TAS_LIST_IDX_NONE;
            } else {
                gcl_state->curr_list_idx = gcl_state->next_list_idx;    /* Configure the possible new current list */
            }

            gcl_state->trunk_list_idx = TAS_LIST_IDX_NONE;
            gcl_state->next_list_idx = TAS_LIST_IDX_NONE;

            gcl_state->stop_ongoing = FALSE;        /* Stop of list is NOT ongoing */
            gcl_state->new_list_scheduled = FALSE;  /* Start of new list is NOT ongoing */
        }
    }
}

static vtss_rc tas_list_cancel(vtss_state_t *vtss_state, u32 list_index)
{
    tas_list_state_write(vtss_state, list_index, TAS_LIST_STATE_ADMIN);
    tas_list_free(vtss_state, list_index);

    return VTSS_RC_OK;
}

static vtss_rc tas_list_start(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                              u32 list_idx, u32 obsolete_list_idx,
                              vtss_qos_tas_port_conf_t *port_conf, u32 startup_time)
{
    u32                 maxsdu, i, gcl_idx, hold_advance, value, time_interval_sum = 0;
    u32                 profile_idx = vtss_state->qos.tas.tas_lists[list_idx].profile_idx;
    u32                 entry_idx = vtss_state->qos.tas.tas_lists[list_idx].entry_idx;
    vtss_port_no_t      chip_port = VTSS_CHIP_PORT(port_no);

    vtss_timestamp_t    *base_time = &port_conf->base_time;
    u32                 cycle_time = port_conf->cycle_time;
    u32                 gcl_length = port_conf->gcl_length;
    vtss_qos_tas_gce_t  *gcl = port_conf->gcl;;
    u16                 *max_sdu  = port_conf->max_sdu;
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    u32  fp_enable_tx = (vtss_state->qos.fp.port_conf[port_no].enable_tx ? 1 : 0);
#else
    u32  fp_enable_tx = FALSE;
#endif

    VTSS_D("Enter list_idx %u  obsolete_list_idx %u  entry_idx %u  profile_idx %u  chip_port %u", list_idx, obsolete_list_idx, entry_idx, profile_idx, chip_port);
    VTSS_D("startup_time %u", startup_time);

    /* Select the list */
    REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_LIST_NUM(list_idx), QSYS_TAS_CFG_CTRL_LIST_NUM_M);

    /* List must be in ADMIN state */
    REG_RD(QSYS_TAS_LST, &value);
    if (QSYS_TAS_LST_LIST_STATE_X(value) != TAS_LIST_STATE_ADMIN) {
        VTSS_D("The TAS list is not in admin state");
        return VTSS_RC_ERROR;
    }

    /* Configure the list */
    REG_WR(QSYS_TAS_BT_NSEC, base_time->nanoseconds);
    REG_WR(QSYS_TAS_BT_SEC_LSB, base_time->seconds);
    REG_WR(QSYS_TAS_BT_SEC_MSB, base_time->sec_msb);
    REG_WR(QSYS_TAS_CT_CFG, cycle_time);
    REG_WR(QSYS_TAS_STARTUP_CFG, QSYS_TAS_STARTUP_CFG_OBSOLETE_IDX((obsolete_list_idx != TAS_LIST_IDX_NONE) ? obsolete_list_idx : list_idx) |
                                 QSYS_TAS_STARTUP_CFG_STARTUP_TIME(startup_time/256));
    REG_WR(QSYS_TAS_LIST_CFG, QSYS_TAS_LIST_CFG_LIST_BASE_ADDR(entry_idx));

    /* Configure the profile */
    for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        maxsdu = (fp_enable_tx != 0) ? 1 : (max_sdu[i] / 64) + ( max_sdu[i] ? 1 : 0);  /* In case of FP aktive the MAXSDU must be as small as possible */
        REG_WR(QSYS_TAS_QMAXSDU_CFG(profile_idx, i), QSYS_TAS_QMAXSDU_CFG_QMAXSDU_VAL(maxsdu));
    }
    /* Configure the queue max sdu */
    for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        value = QSYS_QMAXSDU_CFG_0_QMAXSDU_0(max_sdu[i]);
        switch (i) {
        case 0: REG_WR(QSYS_QMAXSDU_CFG_0(chip_port), value); break;
        case 1: REG_WR(QSYS_QMAXSDU_CFG_1(chip_port), value); break;
        case 2: REG_WR(QSYS_QMAXSDU_CFG_2(chip_port), value); break;
        case 3: REG_WR(QSYS_QMAXSDU_CFG_3(chip_port), value); break;
        case 4: REG_WR(QSYS_QMAXSDU_CFG_4(chip_port), value); break;
        case 5: REG_WR(QSYS_QMAXSDU_CFG_5(chip_port), value); break;
        case 6: REG_WR(QSYS_QMAXSDU_CFG_6(chip_port), value); break;
        case 7: REG_WR(QSYS_QMAXSDU_CFG_7(chip_port), value); break;
        }
    }

    REG_RD(SYS_FRONT_PORT_MODE(chip_port), &value);
    hold_advance = SYS_FRONT_PORT_MODE_ADD_FRAG_SIZE_X(value) + 1;
    REG_WR(QSYS_TAS_PROFILE_CFG(profile_idx), QSYS_TAS_PROFILE_CFG_PORT_NUM(chip_port) |
                                              QSYS_TAS_PROFILE_CFG_SCH_QUEUES(0) |
                                              QSYS_TAS_PROFILE_CFG_HOLDADVANCE(hold_advance) |
                                              QSYS_TAS_PROFILE_CFG_LINK_SPEED(tas_link_speed_calc(vtss_state->port.conf[port_no].speed)));

    /* Configure the list elements */
    for (gcl_idx = 0; gcl_idx < gcl_length; ++gcl_idx) {
        /* Select the list entry */
        REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_GCL_ENTRY_NUM(entry_idx), QSYS_TAS_CFG_CTRL_GCL_ENTRY_NUM_M);

        if (gcl_idx < (gcl_length - 1)) { /* If not the last entry get the next entry index */
            tas_next_unused_entry_get(vtss_state, &entry_idx);
        } else {    /* Last entry */
            entry_idx = vtss_state->qos.tas.tas_lists[list_idx].entry_idx; /* End of list - point to start of list */
        }

        /* Configure the list entry */
        REG_WR(QSYS_TAS_GCL_CT_CFG, QSYS_TAS_GCL_CT_CFG_GATE_STATE(vtss_bool8_to_u8(gcl[gcl_idx].gate_open)) |
                                    QSYS_TAS_GCL_CT_CFG_OP_TYPE(tas_op_type_calc(gcl[gcl_idx].gate_operation)) |
                                    QSYS_TAS_GCL_CT_CFG_HSCH_POS(chip_port));
        REG_WR(QSYS_TAS_GCL_CT_CFG2, QSYS_TAS_GCL_CT_CFG2_PORT_PROFILE(profile_idx) |
                                     QSYS_TAS_GCL_CT_CFG2_NEXT_GCL(entry_idx));
        REG_WR(QSYS_TAS_GCL_TM_CFG, gcl[gcl_idx].time_interval);

        /* Calculate the sum of time intervals */
        time_interval_sum += gcl[gcl_idx].time_interval;
    }

    /* Check if the sum of intervals are larger that the requeste cycle time */
    if ((time_interval_sum > cycle_time) || (cycle_time > VTSS_QOS_TAS_CT_MAX) || (cycle_time == 0)) {
        VTSS_D("The TAS list cycle time is invalid. time_interval_sum %u  cycle_time %u", time_interval_sum, cycle_time);
        return VTSS_RC_ERROR;
    }
    if (time_interval_sum != cycle_time) {
        VTSS_D("The TAS list cycle time is larger than list time interval sum. time_interval_sum %u  cycle_time %u", time_interval_sum, cycle_time);
    }

    /* Start the list */
    tas_list_state_write(vtss_state, list_idx, TAS_LIST_STATE_ADVANCING);

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_qos_tas_port_conf_update(struct vtss_state_s   *vtss_state,
                                              const vtss_port_no_t  port_no)
{
    u32                 i;
    vtss_tas_profile_t  *tas_profiles = vtss_state->qos.tas.tas_profiles;

    /* This must be done when the link comes up and link speed has been negotiated. The profile used on this port must be configured to actual speed */
    for (i = 0; i < VTSS_TAS_NUMBER_OF_PROFILES; ++i) {
        if (tas_profiles[i].in_use && tas_profiles[i].port_no == port_no) {
            REG_WRM(QSYS_TAS_PROFILE_CFG(i), QSYS_TAS_PROFILE_CFG_LINK_SPEED(tas_link_speed_calc(vtss_state->port.conf[port_no].speed)),
                                             QSYS_TAS_PROFILE_CFG_LINK_SPEED_M);
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_tas_frag_size_update(struct vtss_state_s   *vtss_state,
                                                const vtss_port_no_t  port_no)
{
    vtss_port_no_t           chip_port = VTSS_CHIP_PORT(port_no);
    vtss_qos_tas_port_conf_t *port_conf = &vtss_state->qos.tas.port_conf[port_no];
    vtss_tas_gcl_state_t     *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];
    u32                      i, maxsdu, hold_advance, profile_idx, value;
    u16                      *max_sdu  = port_conf->max_sdu;
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    u32  fp_enable_tx = (vtss_state->qos.fp.port_conf[port_no].enable_tx ? 1 : 0);
#else
    u32  fp_enable_tx = FALSE;
#endif

    if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {    /* Check if there is a current list active */
        profile_idx = vtss_state->qos.tas.tas_lists[gcl_state->curr_list_idx].profile_idx;  /* Get the profile index for the currently active list */

        /* This must be done depending on FP enabled or disabled */
        for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
            maxsdu = (fp_enable_tx != 0) ? 1 : (max_sdu[i] / 64) + ( max_sdu[i] ? 1 : 0);  /* In case of FP active the MAXSDU must be as small as possible */
            REG_WR(QSYS_TAS_QMAXSDU_CFG(profile_idx, i), QSYS_TAS_QMAXSDU_CFG_QMAXSDU_VAL(maxsdu));
        }

        /* This must be done when the frame preemption RemAddFragSize is changing */
        REG_RD(SYS_FRONT_PORT_MODE(chip_port), &value);
        hold_advance = (fp_enable_tx != 0) ? (SYS_FRONT_PORT_MODE_ADD_FRAG_SIZE_X(value) + 1) : 0;
        REG_WRM(QSYS_TAS_PROFILE_CFG(profile_idx), QSYS_TAS_PROFILE_CFG_HOLDADVANCE(hold_advance), QSYS_TAS_PROFILE_CFG_HOLDADVANCE_M); /* Update the hold_advance configuration */
    }

    return VTSS_RC_OK;
}

static int tas_base_time_in_future(vtss_state_t *vtss_state,  vtss_timestamp_t  *base_time,  u32 min_distance_time)
{
    u64               tc;
    vtss_timestamp_t  tod_time, distance_time;

    /* Get current time */
    _vtss_ts_domain_timeofday_get(vtss_state, 0, &tod_time, &tc);

    /* Check if base time is in the past */
    if (vtss_timestampLarger(&tod_time, base_time)) {
        VTSS_D("base time is in the past");
        return -1;
    }

    /* Check if base time is in the future. Check if it is too close  */
    distance_time = *base_time;
    if (vtss_timestampSub(&distance_time, &tod_time) != VTSS_RC_OK) {
        VTSS_D("Base time subtraction failed");
        return 0;
    }
    /* Must be more that min_distance_time in the future */
    if ((distance_time.sec_msb == 0) && (distance_time.seconds == 0) && (distance_time.nanoseconds < min_distance_time)) {
        VTSS_D("Scheduled list start is too close");
        return 0;
    }

    return 1;   /* Correctly in the future */
}

static BOOL tas_scheduled_cancel_ok(vtss_state_t *vtss_state,  vtss_tas_gcl_state_t  *gcl_state)
{
    u32               scheduled_list_idx;
    vtss_timestamp_t  scheduled_base_time;

    /* Check if a list is already scheduled to start */
    if (gcl_state->new_list_scheduled) {
        /* Read the base time of the scheduled list start */
        scheduled_list_idx = (gcl_state->trunk_list_idx != TAS_LIST_IDX_NONE) ? gcl_state->trunk_list_idx : gcl_state->next_list_idx;
        tas_list_base_time_read(vtss_state, scheduled_list_idx, &scheduled_base_time);

        return (tas_base_time_in_future(vtss_state, &scheduled_base_time, 500000000) == 1) ? TRUE : FALSE; /* Check if scheduled base time is ok. It must be in the future and not too close (500 ms) */
    }
    return TRUE;
}

static BOOL tas_cycle_time_ok(vtss_qos_tas_port_conf_t *new_port_conf)
{
    u32                 i, time_interval_sum = 0;

    if ((new_port_conf->cycle_time < VTSS_QOS_TAS_CT_MIN) || (new_port_conf->cycle_time > VTSS_QOS_TAS_CT_MAX)) {
        return FALSE;
    }

    for (i = 0; i < new_port_conf->gcl_length; ++i) {
        time_interval_sum += new_port_conf->gcl[i].time_interval;
    }

    if (new_port_conf->cycle_time < time_interval_sum) {
        return FALSE;
    }

    return TRUE;
}

static vtss_rc lan966x_qos_tas_conf_set(vtss_state_t *vtss_state)
{
    vtss_qos_tas_conf_t *conf = &vtss_state->qos.tas.global_conf;

    /* Configure all ways guard band */
    REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_ALWAYS_GB_SCH_Q(conf->always_guard_band ? 1 : 0), QSYS_TAS_CFG_CTRL_ALWAYS_GB_SCH_Q_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_tas_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32                      i, profile_idx, trunk_profile_idx, trunk_startup_time, stop_startup_time, time_gap,
                             new_startup_time = 2000;  /* two nanoseconds */
    u32                      list_idx, trunk_list_idx, obsolete_list_idx, stop_list_idx;
    vtss_qos_tas_port_conf_t *new_port_conf = &vtss_state->qos.tas.port_conf[port_no];
    vtss_qos_tas_port_conf_t trunk_port_conf, stop_port_conf, current_port_conf;
    vtss_tas_gcl_state_t     *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];
    vtss_tas_list_t          *tas_lists = vtss_state->qos.tas.tas_lists;
    vtss_timestamp_t         current_end_time, old_cycle_start_time, stop_base_time;
    u64                      tc;
    int                      rc;

    list_idx = trunk_list_idx = obsolete_list_idx = stop_list_idx = TAS_LIST_IDX_NONE;
    profile_idx = trunk_profile_idx = TAS_PROFILE_IDX_NONE;
    trunk_startup_time = stop_startup_time = time_gap = 0;
    VTSS_MEMSET(&current_end_time, 0, sizeof(current_end_time));

    /* Update the GCL state */
    tas_gcl_state_update(vtss_state, port_no);

    /* Calculate the current GCL */
    if (tas_current_port_conf_calc(vtss_state, port_no, &current_port_conf) == VTSS_RC_ERROR) {
        VTSS_D("Calculate the current GCL failed");
        return VTSS_RC_ERROR;
    }

    if (new_port_conf->gate_enabled) {
        /* Running list on port is enabled */
        if (new_port_conf->config_change) {
            /* Start new list */

            /* Check for correct max SDU size */
            for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
                if ((new_port_conf->max_sdu[i] < 64) || (new_port_conf->max_sdu[i] > (255 * 64))) {   /* The the max register value is 255. Resolution is 64 bytes */
                    VTSS_D("Check of MAX SDU size failed");
                    return VTSS_RC_ERROR;
                }
            }

            /* Check for correct cycle time */
            if (!tas_cycle_time_ok(new_port_conf)) {
                VTSS_D("Check of cycle time failed");
                return VTSS_RC_ERROR;
            }

            /* Calculate the end time of possible current list cycle */
            if (!tas_current_end_time_calc(vtss_state, gcl_state->curr_list_idx, &new_port_conf->base_time, &current_end_time)) {
                VTSS_D("Calculate the end time of current list cycle failed");
                return VTSS_RC_ERROR;
            }

            /* Check if requested base time is ok - in the future and not too close (two cycle times) */
            if ((rc = tas_base_time_in_future(vtss_state, &new_port_conf->base_time, (2 * new_port_conf->cycle_time))) != 1) {
                VTSS_D("The requested GCL base time is not OK");
                if ((rc == -1) && (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE)) {    /* Base time in the future and current list active */
                    gcl_state->config_change_error++;
                }
                return VTSS_RC_ERROR;
            }

            /* Check if a stop of list is on going - must finish */
            if (gcl_state->stop_ongoing) {
                VTSS_D("The TAS list stop is ongoing");
                return VTSS_RC_OK;
            }

            /* Check if a list is already scheduled to start */
            if (gcl_state->new_list_scheduled) {
                /* Check if it is ok to cancel scheduled list.  */
                if (!tas_scheduled_cancel_ok(vtss_state, gcl_state)) {
                    VTSS_D("A scheduled list start is on going");
                    return VTSS_RC_ERROR;
                }
                /* Cancel the scheduled list start */
                tas_list_cancel(vtss_state, gcl_state->trunk_list_idx);
                tas_list_cancel(vtss_state, gcl_state->next_list_idx);
            }

            /* Check if a list is currently running. Possible trunk list required */
            if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {
                /* Calculate the time gap between current list cycle and beginning of new list */
                if (!tas_time_stamp_diff(&new_port_conf->base_time, &current_end_time, &time_gap)) {
                    VTSS_D("Calculate the time gap between current list cycle and beginning of new list failed");
                    return VTSS_RC_ERROR;
                }
                if (time_gap > new_port_conf->cycle_time_ext) { /* Check if gap is larger that the accepted extension time. Truncation of current list */
                    VTSS_D("GCL truncation");
                    if ((trunk_list_idx = tas_list_allocate(vtss_state, new_port_conf->gcl_length)) == TAS_LIST_IDX_NONE) {   /* Allocate trunk list */
                        VTSS_I("Allocate trunk list failed");
                        return VTSS_RC_ERROR;
                    }
                    tas_lists[trunk_list_idx].profile_idx = tas_lists[gcl_state->curr_list_idx].profile_idx;  /* The trunk list inherit profile from current list */;
                    tas_lists[trunk_list_idx].inherit_profile = TRUE;
                } else {
                    VTSS_D("GCL extension");
                }
            }

            /* Allocate resources for new list */
            if ((list_idx = tas_list_allocate(vtss_state, new_port_conf->gcl_length)) == TAS_LIST_IDX_NONE) {   /* Allocate new list */
                tas_list_free(vtss_state, trunk_list_idx);
                VTSS_I("No TAS list was allocated");
                return VTSS_RC_ERROR;
            }
            if ((profile_idx = tas_profile_allocate(vtss_state, port_no)) == TAS_PROFILE_IDX_NONE) {    /* Allocate new profile */
                tas_list_free(vtss_state, list_idx);
                tas_list_free(vtss_state, trunk_list_idx);
                VTSS_I("No TAS profiles was allocated");
                return VTSS_RC_ERROR;
            }
            tas_lists[list_idx].profile_idx = profile_idx;
            tas_lists[list_idx].inherit_profile = FALSE;
            obsolete_list_idx = gcl_state->curr_list_idx;

            /* Resources are now allocated - start the lists */

            /* Check if trunk list must be started */
            if (trunk_list_idx != TAS_LIST_IDX_NONE) {
                /* Calculate the truncated GCL and startup time*/
                tas_trunk_port_conf_calc(&current_port_conf, &current_end_time, &new_port_conf->base_time, &trunk_port_conf);
                trunk_startup_time = current_port_conf.cycle_time;   /* STARTUP_TIME := first_cycle_start(B) - last_cycle_start(A). In this case this is equel to cycle time as there will be no gap between current list cycle end and trunk list cycle start */
                /* Start the trunk list */
                if (tas_list_start(vtss_state, port_no, trunk_list_idx, obsolete_list_idx, &trunk_port_conf, trunk_startup_time) != VTSS_RC_OK) {
                    /* Start failed */
                    tas_list_free(vtss_state, trunk_list_idx);
                    tas_list_free(vtss_state, list_idx);
                    VTSS_I("The trunk TAS list could not start");
                    return VTSS_RC_ERROR;
                }
                obsolete_list_idx = trunk_list_idx;
            }

            /* Start the new list */
            if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {
                /* Calculate the 'old' last cycle start time */
                if (trunk_list_idx != TAS_LIST_IDX_NONE) {
                    old_cycle_start_time = trunk_port_conf.base_time;   /* Trunk list has only one cycle so the base time is the start of the last cycle */
                } else {
                    old_cycle_start_time = current_end_time;            /* Start of current last cycle is the end time of last cycle minus the cycle time */
                    if (vtss_timestampSubNano(&old_cycle_start_time, current_port_conf.cycle_time) != VTSS_RC_OK) {
                        VTSS_D("Calculate the 'old' last cycle start time failed");
                        return VTSS_RC_ERROR;
                    }
                }
                /* Calculate the new startup time */
                if (!tas_time_stamp_diff(&new_port_conf->base_time, &old_cycle_start_time, &new_startup_time)) { /* STARTUP_TIME := first_cycle_start(B) - last_cycle_start(A). */
                    VTSS_D("Calculate the new startup time failed");
                    return VTSS_RC_ERROR;
                }
            }
            if (tas_list_start(vtss_state, port_no, list_idx, obsolete_list_idx, new_port_conf, new_startup_time) != VTSS_RC_OK) {
                /* Start failed */
                tas_list_free(vtss_state, list_idx);

                /* Cancel the trunk list */
                tas_list_cancel(vtss_state, trunk_list_idx);

                VTSS_I("The new TAS list could not start");
                return VTSS_RC_ERROR;
            }

            gcl_state->next_list_idx = list_idx;
            gcl_state->trunk_list_idx = trunk_list_idx;
            gcl_state->new_list_scheduled = TRUE;  /* Start of new list is ongoing */

        } else {
            /* Check if a list is currently running */
            if (gcl_state->curr_list_idx == TAS_LIST_IDX_NONE) {
                tas_gate_state_write(vtss_state, port_no, new_port_conf->gate_open);   /* Set the gate state of the port to 'gate_open[]' */
            }
        }
    } else {
        /* Running list on port is disabled */

        /* Check if a stop of list is on going - must finish */
        if (gcl_state->stop_ongoing) {
            VTSS_D("The TAS list stop is ongoing");
            return VTSS_RC_OK;
        }

        /* Check if a list is scheduled to start */
        if (gcl_state->new_list_scheduled) {
            /* Check if it is ok to cancel scheduled list */
            if (!tas_scheduled_cancel_ok(vtss_state, gcl_state)) {    /* A scheduled list start is on going - must finish */
                VTSS_D("A scheduled list start is on going");
                return VTSS_RC_ERROR;
            }
            /* Cancel the scheduled list start */
            tas_list_cancel(vtss_state, gcl_state->trunk_list_idx);
            tas_list_cancel(vtss_state, gcl_state->next_list_idx);
        }

        /* Check if a list is currently running - must be stopped by a stop list */
        if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {
            /* Calculate first possible base time of stop list. This is TOD plus two times the current cycle time */
            _vtss_ts_domain_timeofday_get(vtss_state, 0, &stop_base_time, &tc);
             VTSS_D("stop base_time seconds %u  nanoseconds %u  sec_msb %u", stop_base_time.seconds, stop_base_time.nanoseconds, stop_base_time.sec_msb);
             VTSS_D("current base_time seconds %u  nanoseconds %u  sec_msb %u", current_port_conf.base_time.seconds, current_port_conf.base_time.nanoseconds, current_port_conf.base_time.sec_msb);

            /* Check if current base time is in the future. This should not happen as gcl_state say that list is started */
            if (vtss_timestampLarger(&current_port_conf.base_time, &stop_base_time)) {
                VTSS_D("current list base time is in the future");
                stop_base_time = current_port_conf.base_time;
            }

            if (vtss_timestampAddNano(&stop_base_time, 2 * current_port_conf.cycle_time) != VTSS_RC_OK) {
                VTSS_D("Calculate first possible base time of stop list failed.  cycle_time %u", current_port_conf.cycle_time);
                return VTSS_RC_ERROR;
            }
            /* Calculate the end time of current list cycle */
            if (!tas_current_end_time_calc(vtss_state, gcl_state->curr_list_idx, &stop_base_time, &current_end_time)) {
                VTSS_D("Calculate the end time of current list cycle failed");
                return VTSS_RC_ERROR;
            }

            /* Calculate the stop GCL and stop startup time */
            tas_stop_port_conf_calc(&current_end_time, new_port_conf->gate_open, &stop_port_conf);
            stop_startup_time = current_port_conf.cycle_time;   /* STARTUP_TIME := first_cycle_start(B) - last_cycle_start(A). In this case this is equal to cycle time as there will be no gap between current list cycle end and stop list cycle start */

            /* Allocate stop list */
            if ((stop_list_idx = tas_list_allocate(vtss_state, stop_port_conf.gcl_length)) == TAS_LIST_IDX_NONE) {
                VTSS_I("No TAS list was allocated");
                return VTSS_RC_ERROR;
            }
            tas_lists[stop_list_idx].profile_idx = tas_lists[gcl_state->curr_list_idx].profile_idx;  /* The stop list use same profile as current list */
            tas_lists[stop_list_idx].inherit_profile = TRUE;
            obsolete_list_idx = gcl_state->curr_list_idx;

            /* Start the stop list */
            if (tas_list_start(vtss_state, port_no, stop_list_idx, obsolete_list_idx, &stop_port_conf, stop_startup_time) != VTSS_RC_OK) {
                /* Start failed */
                tas_list_free(vtss_state, stop_list_idx);
                VTSS_I("The stop TAS list could not start");
                return VTSS_RC_ERROR;
            }
            gcl_state->trunk_list_idx = TAS_LIST_IDX_NONE;
            gcl_state->next_list_idx = stop_list_idx;
            gcl_state->stop_ongoing = TRUE;  /* Stop of new list is ongoing */
            gcl_state->config_change_error = 0;
        }

        return VTSS_RC_OK;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_tas_port_status_get(vtss_state_t              *vtss_state,
                                               const vtss_port_no_t       port_no,
                                               vtss_qos_tas_port_status_t *const status)
{
    u32                   list_idx = TAS_LIST_IDX_NONE;
    vtss_tas_gcl_state_t  *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];

    VTSS_MEMSET(status, 0, sizeof(*status));

    /* Update the GCL state */
    tas_gcl_state_update(vtss_state, port_no);

    /* Configuration is pending if next list is active. This is true if new start list is pending or stop list is pending */
    status->config_pending = (gcl_state->next_list_idx != TAS_LIST_IDX_NONE) ? TRUE : FALSE;

    status->config_change_error = gcl_state->config_change_error;

    /* Read the base time that a pending configuration is going to be changed or the current configuration has been changed */
    if (gcl_state->next_list_idx != TAS_LIST_IDX_NONE) {
        list_idx = gcl_state->next_list_idx;    /* New list is pending */
    } else if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {    /* New list is not pending*/
        list_idx = gcl_state->curr_list_idx;    /* Current list is active */
    }
    if (list_idx != TAS_LIST_IDX_NONE) {
        tas_list_base_time_read(vtss_state, list_idx, &status->config_change_time);
    }

    /* Read the current gate state on the port */
    tas_gate_state_read(vtss_state, port_no, status->gate_open);

    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_QOS_TAS

static vtss_rc lan966x_qos_fp_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_fp_port_conf_t *conf = &vtss_state->qos.fp.port_conf[port_no];
    BOOL                    enable_tx = (conf->enable_tx ? 1 : 0);
    u32                     i, mask = 0, port = VTSS_CHIP_PORT(port_no);
    BOOL                    verify_dis = !(!conf->verify_disable_tx && conf->enable_tx);

    if (enable_tx) {
        for (i = 0; i < 8; i++) {
            if (vtss_state->qos.port_conf[port_no].cut_through_enable[i]) {
                VTSS_E("frame preemption and cut through cannot both be enabled");
                return VTSS_RC_ERROR;
            }
        }
    }

    REG_WRM(DEV_VERIF_CONFIG(port),
            DEV_VERIF_CONFIG_PRM_VERIFY_DIS(1),
            DEV_VERIF_CONFIG_PRM_VERIFY_DIS_M);

    // Setup preemption
    REG_WR(DEV_VERIF_CONFIG(port),
           DEV_VERIF_CONFIG_PRM_VERIFY_DIS(verify_dis) |
           DEV_VERIF_CONFIG_PRM_VERIFY_TIME(conf->verify_time) |
           DEV_VERIF_CONFIG_VERIF_TIMER_UNITS(vtss_state->port.conf[port_no].speed == VTSS_SPEED_2500M ? 2 : 0));
    REG_WRM(SYS_FRONT_PORT_MODE(port),
            SYS_FRONT_PORT_MODE_ADD_FRAG_SIZE(conf->add_frag_size),
            SYS_FRONT_PORT_MODE_ADD_FRAG_SIZE_M);

    // Enable/disable preemptable queues
    for (i = 0; i < 8; i++) {
        mask |= (enable_tx && conf->admin_status[i] ? VTSS_BIT(i) : 0);
    }
    REG_WR(QSYS_PREEMPT_CFG(port),
           QSYS_PREEMPT_CFG_P_QUEUES(mask) |
           QSYS_PREEMPT_CFG_STRICT_IPG(mask ? 0 : 2));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_qos_fp_port_status_get(vtss_state_t              *vtss_state,
                                              const vtss_port_no_t      port_no,
                                              vtss_qos_fp_port_status_t *const status)
{
    u32 value, v, port = VTSS_CHIP_PORT(port_no);
    vtss_qos_fp_port_conf_t *conf = &vtss_state->qos.fp.port_conf[port_no];

    REG_RD(DEV_MM_STATUS(port), &value);
    status->preemption_active = DEV_MM_STATUS_PRMPT_ACTIVE_STATUS_X(value);
    if (vtss_state->qos.fp.port_conf[port_no].verify_disable_tx) {
        v = VTSS_MM_STATUS_VERIFY_DISABLED;
    } else {
        v = (DEV_MM_STATUS_PRMPT_VERIFY_STATE_X(value));
        if (v == 3 && conf->enable_tx) {
            /* Verification failed, restart it */
            REG_WRM(DEV_VERIF_CONFIG(port),
                    DEV_VERIF_CONFIG_PRM_VERIFY_DIS(1),
                    DEV_VERIF_CONFIG_PRM_VERIFY_DIS_M);

            REG_WRM(DEV_VERIF_CONFIG(port),
                    DEV_VERIF_CONFIG_PRM_VERIFY_DIS(0),
                    DEV_VERIF_CONFIG_PRM_VERIFY_DIS_M);
        }
        v += 2;
    }
    status->status_verify = v;
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_qos_port_change(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL in_reset)
{
    /* Setup depending on port speed */
    VTSS_RC(lan966x_qos_queue_cut_through_set(vtss_state, port_no));
#if defined(VTSS_FEATURE_QOS_TAS)
    VTSS_RC(lan966x_qos_tas_frag_size_update(vtss_state, port_no));
#endif
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

#if VTSS_OPT_DEBUG_PRINT
#if defined(VTSS_FEATURE_QOS_TAS)
static char *debug_tas_state_string(u32 value)
{
    switch (value) {
        case 0:    return("ADMIN");
        case 1:    return("ADVANCING");
        case 2:    return("PENDING");
        case 3:    return("OPERATING");
        case 4:    return("TERMINATING");
        default:   return("UNKNOWN");
    }
    return("INVALID");
}

static vtss_rc debug_tas_conf_print(vtss_state_t *vtss_state,  const vtss_debug_printf_t pr,  u32 list_idx,  BOOL any_state)
{
    u32   j, value, value1, entry_first, state, entry_idx, profile_idx;

    /* Select the list */
    REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_LIST_NUM(list_idx), QSYS_TAS_CFG_CTRL_LIST_NUM_M);
    REG_RD(QSYS_TAS_LST, &state);

    if ((QSYS_TAS_LST_LIST_STATE_X(state) != 0) || any_state) {    /* Print list not in ADMIN state */
        pr("GCL Index: %u\n", list_idx);
        pr("----------------\n");
        REG_RD(QSYS_TAS_BT_NSEC, &value);
        pr("    %s: %u\n", "BASE_TIME_NSEC", value);
        REG_RD(QSYS_TAS_BT_SEC_LSB, &value);
        pr("    %s: %u\n", "BASE_TIME_SEC_LSB", value);
        REG_RD(QSYS_TAS_BT_SEC_MSB, &value);
        pr("    %s: %u\n", "BASE_TIME_SEC_MSB", value);
        REG_RD(QSYS_TAS_CT_CFG, &value);
        pr("    %s: %u\n", "CYCLE_TIME_CFG", value);
        REG_RD(QSYS_TAS_STARTUP_CFG, &value);
        pr("    %s: %u\n", "OBSOLETE_IDX", QSYS_TAS_STARTUP_CFG_OBSOLETE_IDX_X(value));
        pr("    %s: %u\n", "STARTUP_TIME", QSYS_TAS_STARTUP_CFG_STARTUP_TIME_X(value));
        REG_RD(QSYS_TAS_LIST_CFG, &value);
        entry_idx = QSYS_TAS_LIST_CFG_LIST_BASE_ADDR_X(value);
        pr("    %s: %u\n", "LIST_BASE_ADDR", entry_idx);
        pr("    %s: %s\n", "LIST_STATE", debug_tas_state_string(QSYS_TAS_LST_LIST_STATE_X(state)));
        pr("\n");

        /* Read the list elements */
        entry_first = entry_idx;

        /* Read the list elements */
        do {
            pr("    Enty Index: %u\n", entry_idx);
            pr("    ----------------\n");

            /* Select the list entry */
            REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_GCL_ENTRY_NUM(entry_idx), QSYS_TAS_CFG_CTRL_GCL_ENTRY_NUM_M);

            /* Read the gate state */
            REG_RD(QSYS_TAS_GCL_CT_CFG, &value);
            REG_RD(QSYS_TAS_GCL_CT_CFG2, &value1);
            profile_idx = QSYS_TAS_GCL_CT_CFG2_PORT_PROFILE_X(value1);
            pr("        %s: 0x%X\n", "GATE_STATE", QSYS_TAS_GCL_CT_CFG_GATE_STATE_X(value));
            pr("        %s: %u\n", "PORT_PROFILE", profile_idx);
            pr("        %s: %u\n", "HSCH_POS", QSYS_TAS_GCL_CT_CFG_HSCH_POS_X(value));
            pr("        %s: %u\n", "OP_TYPE", QSYS_TAS_GCL_CT_CFG_OP_TYPE_X(value));

            /* Read time interval */
            REG_RD(QSYS_TAS_GCL_TM_CFG, &value);
            pr("        %s: %u\n", "TIME_INTERVAL", value);

            /* Read max SDU configuration in the profile */
            pr("        %s: ", "QMAXSDU_VAL");
            for (j = 0; j < VTSS_QUEUE_ARRAY_SIZE; ++j) {
                REG_RD(QSYS_TAS_QMAXSDU_CFG(profile_idx, j), &value);
                pr("%u-", value);
            }
            pr("\n");

            /* Read scheduled configuration in the profile */
            REG_RD(QSYS_TAS_PROFILE_CFG(profile_idx), &value);
            pr("        %s: %u\n", "PORT_NUM", QSYS_TAS_PROFILE_CFG_PORT_NUM_X(value));
            pr("        %s: %u\n", "LINK_SPEED", QSYS_TAS_PROFILE_CFG_LINK_SPEED_X(value));
            pr("        %s: 0x%X\n", "SCH_TRAFFIC_QUEUES", QSYS_TAS_PROFILE_CFG_SCH_QUEUES_X(value));
            pr("        %s: 0x%X\n", "HOLDADVANCE", QSYS_TAS_PROFILE_CFG_HOLDADVANCE_X(value));

            /* Read the next GCL entry index */
            entry_idx = QSYS_TAS_GCL_CT_CFG2_NEXT_GCL_X(value1);
        } while(entry_idx != entry_first);

        pr("\n");
    }

    return VTSS_RC_OK;
}
#endif

static vtss_rc lan966x_qos_debug(vtss_state_t               *vtss_state,
                                 const vtss_debug_printf_t  pr,
                                 const vtss_debug_info_t    *const info)
{
    u32            i, port, pir, value, mode, terminal_se, dwrr_se;
    u32            cir, qmap, policer;
    int            queue;
    BOOL           header = 1;
    vtss_port_no_t port_no;
#if defined(VTSS_FEATURE_QOS_TAS)
    u32            j, tas_list_idx = 0, div = 0;
    vtss_port_no_t tas_port = 0;
#endif
    char           buf[16];
    BOOL           show_act, basics_act, port_pol_act,
                   storm_pol_act, schedul_act, policer_act, shape_act, tas_act, tas_state_act, tas_count_act;

    show_act = basics_act = port_pol_act = policer_act =
    storm_pol_act = schedul_act = tas_act = shape_act = tas_state_act = tas_count_act = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show_act =             (info->action == 0)  ? TRUE : FALSE;
        basics_act =           (info->action == 1)  ? TRUE : FALSE;
        port_pol_act =         (info->action == 2)  ? TRUE : FALSE;
        storm_pol_act =        (info->action == 3)  ? TRUE : FALSE;
        policer_act =          (info->action == 4)  ? TRUE : FALSE;
        schedul_act =          (info->action == 5)  ? TRUE : FALSE;
        shape_act =            (info->action == 6) ? TRUE : FALSE;
        tas_act =              (info->action == 7)  ? TRUE : FALSE;
        tas_state_act =        (info->action == 8)  ? TRUE : FALSE;
        tas_count_act =        (info->action == 9)  ? TRUE : FALSE;
    }

#if defined(VTSS_FEATURE_QOS_TAS)
    if (info->action > 9) { /* This potentially a TAS configuration or analyze action */
        for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
            tas_act = ((info->action / div) == 7) ? TRUE : FALSE;
            tas_state_act = ((info->action / div) == 8) ? TRUE : FALSE;
            tas_count_act = ((info->action / div) == 9) ? TRUE : FALSE;

            if (tas_act || tas_state_act || tas_count_act) {
                break;
            }
        }
        if (tas_act) {
            tas_list_idx = info->action % div;
        }
        if (tas_state_act || tas_count_act) {
            tas_port = info->action % div;
        }
        VTSS_D("tas_act %u  tas_state_act %u  tas_count_act %u  tas_list_idx %u  tas_port %u  div %u",
                tas_act, tas_state_act, tas_count_act, tas_list_idx, tas_port, div);
    }
#endif

    VTSS_D("show %u  basic %u  port_pol %u  storm_pol %u  policer %u  schedul %u  shape %u",
           show_act, basics_act, port_pol_act, storm_pol_act, policer_act, schedul_act, shape_act);

    if (info->action == 10) {
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            REG_RD(DEV_MM_STATUS(VTSS_CHIP_PORT(port_no)), &value);
            pr("p:%d MM_STATUS:0x%x\n",port_no, value);
            REG_RD(DEV_VERIF_CONFIG(VTSS_CHIP_PORT(port_no)), &value);
            pr("p:%d DEV_VERIF_CONFIG:0x%x\n",port_no, value);
        }
#endif
    }

    if (show_act) {
        pr("QOS Debug Group action:\n");
        pr("    0:      Show possible actions\n");
        pr("    1:      Print Basic configuration\n");
        pr("    2:      Print Port policing configurations\n");
        pr("    3:      Print Storm Policing configurations\n");
        pr("    4:      Print Policers configurations\n");
        pr("    5:      Print Scheduling hierarchy configurations\n");
        pr("    6:      Print Shapers configurations\n");
        pr("    7XXXX   Print Time Aware Scheduling configurations. All active liats or the XXXX specified\n");
        pr("    8XXXX   Print Time Aware Scheduling gate state analyze. Port is the XXXX specified\n");
        pr("    9XXXX   Print Time Aware Scheduling counter analyze. Port is the XXXX specified\n");
        pr("    10      Print frame preemtion details\n");
        pr("\n");
    }

    /* Global configuration starts here */

    pr("QoS WRED Config has been moved to 'debug api cil wm'\n\n");

    if (!info->has_action || basics_act) { /* Basic configuration must be printed */
        vtss_debug_print_header(pr, "QoS basic classification (ingress) configuration");

        pr("Port configuration:\n");
        pr("-------------------\n");

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
                    pcp_ct += VTSS_SNPRINTF(pcp_buf + pcp_ct, sizeof(pcp_buf) - pcp_ct, "%s%u", delim,
                                    REW_PCP_DEI_CFG_PCP_QOS_VAL_X(value));
                    dei_ct += VTSS_SNPRINTF(dei_buf + dei_ct, sizeof(dei_buf) - dei_ct, "%s%u",  delim,
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
                    class_ct += VTSS_SNPRINTF(class_buf + class_ct, sizeof(class_buf) - class_ct, "%s%u", delim,
                                        ANA_PCP_DEI_CFG_QOS_PCP_DEI_VAL_X(value));
                    dpl_ct   += VTSS_SNPRINTF(dpl_buf   + dpl_ct,   sizeof(dpl_buf)   - dpl_ct,   "%s%u",  delim,
                                        ANA_PCP_DEI_CFG_DP_PCP_DEI_VAL_X(value));
                }
            }
            pr("%2u %2u %s %s\n", port_no, port, class_buf, dpl_buf);
        }
        pr("\n");

        pr("Global configuration:\n");
        pr("---------------------\n");

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
    }

    if (!info->has_action || storm_pol_act) { /* Storm Policing configuration must be printed */
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
    }

    if (!info->has_action || schedul_act) {
        vtss_debug_print_header(pr, "QoS Scheduler Config");

        pr("LP CP   SE Base IdxSel InpSel RR_ENA DWRR C0 C1 C2 C3 C4 C5 C6 C7\n");
        for (port_no = VTSS_PORT_NO_START; port_no < (vtss_state->port_count + 2); port_no++) {
            if (port_no < vtss_state->port_count) {
                if (!info->port_list[port_no]) {
                    continue;
                }
                port = VTSS_CHIP_PORT(port_no);
                VTSS_SPRINTF(buf, "%2u", port_no);
            } else {
                i = (port_no - vtss_state->port_count);
                port = (VTSS_CHIP_PORT_CPU_0 + i);
                VTSS_SPRINTF(buf, "C%u", i);
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
    }

    if (!info->has_action || shape_act) { /* Shapers configuration must be printed */
        vtss_debug_print_header(pr, "QoS Port and Queue Shaper Config");

        pr("LP CP Queue SE  CBS  CIR    EBS  EIR    SE_PRIO SE_SPORT SE_DPORT Excess Credit SE_FRM_MODE\n");
        for (port_no = VTSS_PORT_NO_START; port_no < (vtss_state->port_count + 2); port_no++) {
            u32 eir, sense, excess;
            if (port_no < vtss_state->port_count) {
                if (!info->port_list[port_no]) {
                    continue;
                }
                port = VTSS_CHIP_PORT(port_no);
                VTSS_SPRINTF(buf, "%2u", port_no);
            } else {
                i = (port_no - vtss_state->port_count);
                port = (VTSS_CHIP_PORT_CPU_0 + i);
                VTSS_SPRINTF(buf, "C%u", i);
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
    }

    if (!info->has_action || port_pol_act) { /* Port policing configuration must be printed */
        vtss_debug_print_header(pr, "QoS Port and Queue Policer");

        vtss_lan966x_debug_reg_header(pr, "Policer Config (chip ports)");
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (!info->port_list[port_no]) {
                continue;
            }
            port = VTSS_CHIP_PORT(port_no);
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_CFG(port)), port, "POL_CFG");
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_FLOWC(port)), port, "POL_FLOWC");

            policer = LAN966X_POLICER_PORT + port_no;
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_STATE(policer)), port, "POL_STATE");
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_PIR_CFG(policer)), port, "POL_PIR_CFG");
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_PIR_STATE(policer)), port, "POL_PIR_STATE");
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_CIR_CFG(policer)), port, "POL_CIR_CFG");
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_CIR_STATE(policer)), port, "POL_CIR_STATE");
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_POL_MODE(policer)), port, "POL_MODE");
        }
        pr("\n");
    }

    if (!info->has_action || policer_act) {
        vtss_debug_print_header(pr, "Policers");

        header = 1;
        for (i = 0; i < LAN966X_POLICER_CNT; i++) {
            REG_RD(ANA_POL_PIR_CFG(i), &pir);
            if (pir == 0) {
                continue;
            }

            if (header) {
                pr("Index  Mode  Dual  IFG  CF  OS  DOY  MAR  PIR    PBS  CIR    CBS\n");
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
            pr("%-7u%-6s%-6u%-5u%-4u%-4u%-5u%-5u%-7u%-5u%-7u%-5u\n",
            i,
            mode == POL_MODE_LINERATE ? "Line" : mode == POL_MODE_DATARATE ? "Data" :
            mode == POL_MODE_FRMRATE_33_1_3_FPS ? "F33_1_3" : "F1_3",
            ANA_POL_MODE_CIR_ENA_X(value),
            ANA_POL_MODE_IPG_SIZE_X(value),
            ANA_POL_MODE_DLB_COUPLED_X(value),
            ANA_POL_MODE_OVERSHOOT_ENA_X(value),
            ANA_POL_MODE_DROP_ON_YELLOW_ENA_X(value),
            ANA_POL_MODE_MARK_ALL_FRMS_RED_ENA_X(value),
            ANA_POL_PIR_CFG_PIR_RATE_X(pir),
            ANA_POL_PIR_CFG_PIR_BURST_X(pir),
            ANA_POL_CIR_CFG_CIR_RATE_X(cir),
            ANA_POL_CIR_CFG_CIR_BURST_X(cir)
                );
        }
    }

#if defined(VTSS_FEATURE_QOS_TAS)
    if (!info->has_action || tas_act) { /* SAT configuration must be printed */
        vtss_tas_gcl_state_t *gcl;
        vtss_tas_list_t *lists = vtss_state->qos.tas.tas_lists;

        vtss_debug_print_header(pr, "QoS Time Aware Scheduler");
        if (div == 0) {
            pr("GCLs allocated:\n");
            pr("port   stop  scheduled  list        list_in_use  list_entry_idx  list_profile_idx\n");
            pr("---------------------------------------------------------------------------------\n");

            for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                /* Update the GCL state */
                tas_gcl_state_update(vtss_state, port_no);

                gcl = &vtss_state->qos.tas.tas_gcl_state[port_no];

                if (gcl->stop_ongoing || gcl->new_list_scheduled || (gcl->curr_list_idx != TAS_LIST_IDX_NONE) || (gcl->trunk_list_idx != TAS_LIST_IDX_NONE) || (gcl->next_list_idx != TAS_LIST_IDX_NONE)) {
                    pr("%-7u%-6u%-11u", port_no, gcl->stop_ongoing, gcl->new_list_scheduled);
                    if (gcl->curr_list_idx != TAS_LIST_IDX_NONE) {
                        pr("%-12u%-13u%-16u%-16u\n", gcl->curr_list_idx, lists[gcl->curr_list_idx].in_use, lists[gcl->curr_list_idx].entry_idx, lists[gcl->curr_list_idx].profile_idx);
                    } else {
                        pr("%-12s%-13s%-16s%-16s\n", "-", "-", "-", "-");
                    }
                    if (gcl->trunk_list_idx != TAS_LIST_IDX_NONE) {
                        pr("%24s%-12u%-13u%-16u%-16u\n", "trunk   ", gcl->trunk_list_idx, lists[gcl->trunk_list_idx].in_use, lists[gcl->trunk_list_idx].entry_idx, lists[gcl->trunk_list_idx].profile_idx);
                    }
                    if (gcl->next_list_idx != TAS_LIST_IDX_NONE) {
                        pr("%24s%-12u%-13u%-16u%-16u\n", "next   ", gcl->next_list_idx, lists[gcl->next_list_idx].in_use, lists[gcl->next_list_idx].entry_idx, lists[gcl->next_list_idx].profile_idx);
                    }
                }
            }
            pr("\n");

            pr("GCL Entries allocated:\n");
            pr("in_use\n");
            pr("-------------------\n");
            for (i = 0, j = 0; i < VTSS_TAS_NUMBER_OF_ENTRIES; i++) {
                if (vtss_state->qos.tas.tas_entries[i].in_use) {
                    pr("%u, ", i);
                    j += 1;
                    if (j == 20) {
                        pr("\n");
                        j = 0;
                    }
                }
            }
            pr("\n");
        }
        pr("\n");

        pr("GCL register configuration:\n");
        for (i = 0; i < VTSS_TAS_NUMBER_OF_LISTS; i++) {
            if ((div > 1) && (tas_list_idx != i)) {   /* A specific TAS list must be printed - this is not the one */
                continue;
            }
            (void)debug_tas_conf_print(vtss_state, pr, i, (div > 1));
        }
    }

    if (tas_state_act && (div > 1)) { /* SAT state analyze must be printed */
#define PRIO_MASK 0x01
#define CYCLE_TIME 12480000
        vtss_port_no_t   chip_port = VTSS_CHIP_PORT(tas_port-1);
        u32              gate_state, index = 0;
        i32              off;
        u64              tc;
        vtss_timestamp_t ts0, ts1, distance;
        struct {
            u8               gate_state;
            vtss_timestamp_t ts;
        } buffer[1000];

        _vtss_ts_domain_timeofday_get(NULL, 0, &ts0, &tc);
        REG_WR(QSYS_TAS_GS_CTRL, (5040 + 64 + chip_port));
        while (1) {
            _vtss_ts_domain_timeofday_get(NULL, 0, &ts1, &tc);
            REG_RD(QSYS_TAS_GATE_STATE, &gate_state);
            gate_state &= PRIO_MASK;
            if ((index == 0) || (gate_state != buffer[index-1].gate_state)) {
                buffer[index].gate_state = (u8)(gate_state);
                buffer[index].ts = ts1;
                index++;
            }
            if (((ts1.seconds - ts0.seconds) > 2) || (index >= 1000)) break;
        }

        for (i=0; i<index; ++i) {
            if ((i > 1) && (buffer[i].gate_state != 0)) {
                distance = buffer[i].ts;
                (void)vtss_timestampSub(&distance, &buffer[i-2].ts);
                off = distance.nanoseconds - CYCLE_TIME;
                pr("state %X  sec %u  nsec %u  distance %u  off %i\n", buffer[i].gate_state, buffer[i].ts.seconds, buffer[i].ts.nanoseconds, distance.nanoseconds, off);
            }
        }
        pr("index %u  ts1.seconds %u  ts0.seconds %u\n", index, ts1.seconds, ts0.seconds);
    }

//    if (tas_count_act && (div > 1)) { /* SAT counter analyze must be printed */
//        vtss_port_no_t  chip_port = VTSS_CHIP_PORT(tas_port-1);
//        u32 count, old_count, equal_count, index = 0;
//        BOOL interval_start;
//        i32 off;
//        vtss_timestamp_t ts0, ts1, distance;
//        u64              tc;
//        struct {
//            u8               count;
//            vtss_timestamp_t ts;
//        } buffer[1000];
//
//        _vtss_ts_domain_timeofday_get(NULL, 0, &ts0, &tc);
//        REG_RD(VTSS_ASM_RX_UC_CNT(chip_port), &old_count);
//        interval_start = FALSE;
//        equal_count = 0;
//        index = 0;
//        while (1) {
//            _vtss_ts_domain_timeofday_get(NULL, 0, &ts1, &tc);
//            REG_RD(VTSS_ASM_TX_UC_CNT(chip_port), &count);
//            equal_count = (count == old_count) ? (equal_count + 1) : 0;
//            if ((equal_count == 0) && (interval_start == TRUE)) {    // Start of interval
//                interval_start = FALSE;
//                buffer[index].count = count;
//                buffer[index].ts = ts1;
//                index++;
//            } else if (equal_count == 50) {    // No frame transmitted in approx 193 us (Frame size 500). Next transmission is start of interval
//                interval_start = TRUE;
//            }
//            old_count = count;
//            if (((ts1.seconds - ts0.seconds) > 2) || (index >= 1000)) break;
//        }
//
//        for (i=0; i<index; ++i) {
//            if (i > 0) {
//                distance = buffer[i].ts;
//                (void)vtss_timestampSub(&distance, &buffer[i-1].ts);
//                off = distance.nanoseconds - CYCLE_TIME;
//                pr("count %u  sec %u  nsec %u  distance %u  off %i\n", buffer[i].count, buffer[i].ts.seconds, buffer[i].ts.nanoseconds, distance.nanoseconds, off);
//            }
//        }
//        pr("index %u  chip_port %u  ts1.seconds %u  ts0.seconds %u\n", index, chip_port, ts1.seconds, ts0.seconds);
//    }
#endif // VTSS_FEATURE_QOS_TAS

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
#endif // VTSS_OPT_DEBUG_PRINT

static vtss_rc lan966x_qos_port_map_set(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    u32            port;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        // Always enable port frame preemption
        // The queue config controls if FP is active or not
        REG_WR(DEV_ENABLE_CONFIG(port),
               DEV_ENABLE_CONFIG_MM_RX_ENA(1) |
               DEV_ENABLE_CONFIG_MM_TX_ENA(1) |
               DEV_ENABLE_CONFIG_KEEP_S_AFTER_D(0));

        vtss_state->qos.fp.port_conf[port_no].verify_disable_tx = TRUE;
    }
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */
vtss_rc vtss_lan966x_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_qos_state_t    *state = &vtss_state->qos;
    vtss_policer_conf_t pol_conf;
#if defined(VTSS_FEATURE_QOS_TAS)
    u32                 i, clk_period;
#endif

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->conf_set = lan966x_qos_conf_set;
        state->port_conf_set = vtss_cmn_qos_port_conf_set;
        state->port_conf_update = lan966x_qos_port_conf_set;
        state->status_get = lan966x_qos_status_get;
#if defined(VTSS_FEATURE_QCL)
        state->qce_add = vtss_cmn_qce_add;
        state->qce_del = vtss_cmn_qce_del;
#endif
#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
        state->cpu_port_shaper_set = lan966x_qos_cpu_port_shaper_set;
#endif
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
        state->evc_policer_conf_set = lan966x_evc_policer_conf_set;
#endif
#if defined(VTSS_FEATURE_QOS_TAS)
        state->tas_conf_set        = lan966x_qos_tas_conf_set;
        state->tas_port_conf_set   = lan966x_qos_tas_port_conf_set;
        state->tas_port_status_get = lan966x_qos_tas_port_status_get;
#endif
        state->fp_port_status_get = lan966x_qos_fp_port_status_get;
        state->fp_port_conf_set = lan966x_qos_fp_port_conf_set;
#if defined(VTSS_FEATURE_EVC_POLICERS)
        state->evc_policer_max = 1022;
#endif
        state->prio_count = LAN966X_PRIOS;
        break;

    case VTSS_INIT_CMD_INIT:
#if defined(VTSS_FEATURE_QOS_TAS)
        // Initialize the TAS max number of GCL
        REG_WRM(QSYS_TAS_CFG_CTRL, QSYS_TAS_CFG_CTRL_LIST_NUM_MAX(VTSS_TAS_NUMBER_OF_LISTS-1), QSYS_TAS_CFG_CTRL_LIST_NUM_MAX_M);

        for (u32 port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            vtss_state->qos.tas.tas_gcl_state[port_no].stop_ongoing = FALSE;
            vtss_state->qos.tas.tas_gcl_state[port_no].new_list_scheduled = FALSE;
            vtss_state->qos.tas.tas_gcl_state[port_no].config_change_error = 0;
            vtss_state->qos.tas.tas_gcl_state[port_no].curr_list_idx = TAS_LIST_IDX_NONE;
            vtss_state->qos.tas.tas_gcl_state[port_no].trunk_list_idx = TAS_LIST_IDX_NONE;
            vtss_state->qos.tas.tas_gcl_state[port_no].next_list_idx = TAS_LIST_IDX_NONE;
            for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
                vtss_state->qos.tas.port_conf[port_no].max_sdu[i] = 24 * 64;   /* Default register value is 24. Resolution is 64 bytes */
            }
        }
        VTSS_MEMSET(&vtss_state->qos.tas.tas_lists, 0, sizeof(vtss_state->qos.tas.tas_lists));
        VTSS_MEMSET(&vtss_state->qos.tas.tas_profiles, 0, sizeof(vtss_state->qos.tas.tas_profiles));
        VTSS_MEMSET(&vtss_state->qos.tas.tas_entries, 0, sizeof(vtss_state->qos.tas.tas_entries));

        clk_period = vtss_lan966x_clk_period_ps(vtss_state);
        REG_WRM(QSYS_TAS_STM_CFG,
                QSYS_TAS_STM_CFG_REVISIT_DLY((256 * 1000) / clk_period),
                QSYS_TAS_STM_CFG_REVISIT_DLY_M);
#endif

        /* Setup discard policer */
        VTSS_MEMSET(&pol_conf, 0, sizeof(pol_conf));
        pol_conf.frame_rate = 1;
        VTSS_RC(vtss_lan966x_qos_policer_conf_set(vtss_state, LAN966X_POLICER_DISC, &pol_conf));
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(lan966x_qos_port_map_set(vtss_state));
        break;

    case VTSS_INIT_CMD_POLL:
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
