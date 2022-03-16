// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_jaguar2_cil.h"

#if defined(VTSS_ARCH_JAGUAR_2)

/* Calculate Layer 0 Scheduler Element when using default hierarchy */
#if defined(VTSS_ARCH_SERVAL_T)
#define JR2_HSCH_L0_SE(port, queue) ((16 * port) + (2 * queue))
#define JR2_L0_SE_CPU_0 412
#elif defined(VTSS_ARCH_JAGUAR_2_C)
#define JR2_HSCH_L0_SE(port, queue) ((64 * port) + (8 * queue))
#define JR2_L0_SE_CPU_0 3396
#else
#error "Unsupported architecture."
#endif

/* - CIL functions ------------------------------------------------- */

/* Calculate 19 bit policer rate

   If input rate is kbps (frame_rate = FALSE) then output rate is calculated like this:
   output rate = ((input rate * 1000) + 25039) / 25040
   This will round up the rate to the nearest possible value:
     0      -> 0 (Open until burst capacity is used, then closed)
     1..25  -> 1 ( 25040 bps)
    26..50  -> 2 ( 50080 bps)
    51..75  -> 3 ( 75120 bps)
    76..100 -> 4 (100160 bps)
   ...

   If input rate is frames per second (frame_rate = TRUE) then output rate is calculated like this:
   output rate = ((input rate) + 9) / 10
   This will round up the rate to the nearest possible value:
     0     -> 0 (Open until burst capacity is used, then closed)
     1..10 -> 1 (10 fps)
    11..20 -> 2 (20 fps)
    21..30 -> 3 (30 fps)
    31..40 -> 4 (40 fps)
   ...

   In both cases the maximum rate returned is limited to 0x7FFFF (13.128.146.480 bps or 5.242.870 fps).
*/
static u32 jr2_calc_policer_rate(u32 rate, BOOL frame_rate)
{
    if (!frame_rate) { /* input rate is measured in kbps */
        rate = VTSS_DIV64(((u64)rate * 1000) + 25039, 25040);
    } else { /* input rate is measured in fps */
        rate = VTSS_DIV64(((u64)rate) + 9, 10);
    }
    return MIN(0x7ffff, rate);
}

/* Calculate 6 bit policer burst level

   If input rate is kbps (frame_rate = FALSE) then output burst level is calculated like this:
   output burst level = (input burst level + 8191) / 8192
   This will round up the burst level to the nearest possible value:
       0        -> 0 (Always closed)
       1.. 8192 -> 1 ( 8.192 bytes)
    8193..16384 -> 2 (16.384 bytes)
   16385..24576 -> 3 (24.576 bytes)
   ...

   If input rate is frames per second (frame_rate = TRUE) then output burst level is set to max.

   In both cases the maximum level returned is limited to 0x3F (516.096 bytes or 206 frames).
*/
static u32 jr2_calc_policer_level(u32 level, u32 rate, BOOL frame_rate)
{
    if (rate == 0) {
        return 0;                                /* Always closed */
    } else if ((rate == VTSS_BITRATE_DISABLED) || frame_rate) {
        return 0x3f;                             /* Maximum burst level */
    } else {
        return MIN(0x3f, (level + 8191) / 8192); /* Calculated value 0..0x3f ~ 0..516.096 bytes in steps of 8.192 bytes */
    }
}

vtss_rc vtss_jr2_port_policer_fc_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no, u32 chipport)
{
    u32 i, fc_ena = 0;
    vtss_port_conf_t *port_conf = &vtss_state->port.conf[port_no];
    vtss_qos_port_conf_t *qos_conf = &vtss_state->qos.port_conf[port_no];

    if (port_conf->flow_control.generate) {
        for (i = 0; i < VTSS_PORT_POLICERS; i++) {
            if ((qos_conf->policer_port[i].rate != VTSS_BITRATE_DISABLED) && qos_conf->policer_ext_port[i].flow_control) {
                fc_ena |= 1 << i;
            }
        }
    }
    JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG(chipport), fc_ena);
    JR2_WRM(VTSS_DSM_CFG_ETH_FC_CFG(chipport),
            VTSS_F_DSM_CFG_ETH_FC_CFG_FC_ANA_ENA(!!fc_ena),
            VTSS_M_DSM_CFG_ETH_FC_CFG_FC_ANA_ENA);

    return VTSS_RC_OK;
}

static vtss_rc jr2_port_policer_set(vtss_state_t *vtss_state,
                                    u32 port, u32 idx, vtss_policer_t *conf, vtss_policer_ext_t *conf_ext)
{
    u32 pol_idx = ((VTSS_PORT_POLICERS * port) + idx);
    u32 cpu_qu_mask = 0, q, traffic_type_mask = 0;

    /* Burst size and rate */
    JR2_WR(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0(pol_idx), jr2_calc_policer_level(conf->level, conf->rate, conf_ext->frame_rate));
    JR2_WR(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1(pol_idx), conf_ext->flow_control ? 1 : 0); /* 8196 bytes flow control deassert threshold */
    JR2_WR(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG(pol_idx), jr2_calc_policer_rate(conf->rate, conf_ext->frame_rate));

    /* GAP */
    JR2_WR(VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP(port), 20); /* GAP_VALUE = 20 : Use line-rate measurement */

    /* CPU queue mask */
    for (q = 0; q < 8; q++) {
        if (conf_ext->cpu_queue[q]) {
            cpu_qu_mask |= VTSS_BIT(q);
        }
    }

    /* Traffic type mask */
    if (conf->rate != VTSS_BITRATE_DISABLED) {  /* traffic_type_mask == 0 (init value) means policer is disabled */
        if (conf_ext->known_multicast) {
            traffic_type_mask |= VTSS_BIT(0);
        }
        if (conf_ext->known_broadcast) {
            traffic_type_mask |= VTSS_BIT(1);
        }
        if (conf_ext->known_unicast) {
            traffic_type_mask |= VTSS_BIT(2);
        }
        if (conf_ext->unknown_multicast) {
            traffic_type_mask |= VTSS_BIT(3);
        }
        if (conf_ext->unknown_broadcast) {
            traffic_type_mask |= VTSS_BIT(4);
        }
        if (conf_ext->unknown_unicast) {
            traffic_type_mask |= VTSS_BIT(5);
        }
        if (conf_ext->to_cpu) {
            traffic_type_mask |= VTSS_BIT(6);
        }
        if (conf_ext->learning) {
            traffic_type_mask |= VTSS_BIT(7);
        }
    }

    JR2_WR(VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG(port, idx),
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_CPU_QU_MASK(cpu_qu_mask)                                 |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_DP_BYPASS_LVL(conf_ext->dp_bypass_level)                 |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_FRAME_RATE_ENA(conf_ext->frame_rate)                     |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_NONCPU_TRAFFIC_ENA(conf_ext->limit_noncpu_traffic) |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_CPU_TRAFFIC_ENA(conf_ext->limit_cpu_traffic)       |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_TRAFFIC_TYPE_MASK(traffic_type_mask));

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_policer_conf_set(vtss_state_t *vtss_state, u32 idx, vtss_dlb_policer_conf_t *dlb_conf)
{
    vtss_dlb_policer_conf_t conf = *dlb_conf;
    u64                     rate, interval;
    u32                     scale, cf, i, level;

    switch (conf.type) {
    case VTSS_POLICER_TYPE_MEF:
        break;
    case VTSS_POLICER_TYPE_SINGLE:
    default:
        /* Single bucket, disable EIR */
        conf.eir = 0;
        conf.ebs = 0;
        conf.cm = 0;
        conf.cf = 0;
        break;
    }

    /* Calculate scale based on maximum rate */
    if ((cf = (conf.cm && conf.cf ? 1 : 0)) != 0) {
        /* Coupling mode, PIR = EIR + CIR */
        conf.eir += conf.cir;
    }
    rate = MAX(conf.cir, conf.eir);
    if (rate > 2000000) {
        /* More than 2 Gbps */
        scale = 0;
        interval = 8192524;
    } else if (rate > 260000) {
        /* More than 260 Mbps */
        scale = 1;
        interval = 1024066;
    } else if (rate > 32000) {
        /* More than 32 Mbps */
        scale = 2;
        interval = 128008;
    } else {
        /* Less than 32 Mbps */
        scale = 3;
        interval = 16001;
    }

    JR2_WR(VTSS_ANA_AC_POL_SDLB_DLB_CFG(idx),
           VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_COUPLING_MODE(cf) |
           VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_COLOR_AWARE_LVL(conf.cm ? 0 : 3) |
           VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_CIR_INC_DP_VAL(1) |
           VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK(3) |
           VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_GAP_VAL(conf.line_rate ? 20 : 0) |
           VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_TIMESCALE_VAL(scale));

    for (i = 0; i < 2; i++) {
        if (i == 0) {
            rate = conf.cir;
            level = conf.cbs;
        } else {
            rate = conf.eir;
            level = conf.ebs;
        }
        rate = VTSS_DIV_ROUND_UP((rate * 1000), interval);
        if (rate > 0x7ff || conf.enable == 0) {
            rate = 0x7ff;
        }
        level = VTSS_DIV_ROUND_UP(level, 2048);
        if (level > 0x7f) {
            level = 0x7f;
        } else if (level == 0) {
            level = 1;
        }
        if (rate == 0) {
            /* No burst allowed if rate is zero */
            level = 0;
        }
        JR2_WR(VTSS_ANA_AC_POL_SDLB_LB_CFG(idx, i),
               VTSS_F_ANA_AC_POL_SDLB_LB_CFG_THRES_VAL(level) |
               VTSS_F_ANA_AC_POL_SDLB_LB_CFG_RATE_VAL(rate));
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_queue_policer_set(vtss_state_t *vtss_state,
                                     u32 port, u32 queue, vtss_policer_t *conf)
{
    if (port < VTSS_CHIP_PORTS) {
        u32                     pol_idx = VTSS_QUEUE_POL_IDX(port, queue);
        vtss_dlb_policer_conf_t dlb_conf;

        VTSS_MEMSET(&dlb_conf, 0, sizeof(dlb_conf));
        dlb_conf.type = VTSS_POLICER_TYPE_SINGLE;
        dlb_conf.enable = 1;
        dlb_conf.line_rate = 1;
        dlb_conf.cir = conf->rate;
        dlb_conf.cbs = conf->level;
        return vtss_jr2_policer_conf_set(vtss_state, pol_idx, &dlb_conf);
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_dwrr_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t *conf        = &vtss_state->qos.port_conf[port_no];
    u32                  chip_port    = VTSS_CHIP_PORT(port_no);
    u32                  layer        = 1;         /* Default layer for JAGUAR_2_C or SERVAL_T when HQoS is not present */
    u32                  se           = chip_port; /* Default se for JAGUAR_2_C or SERVAL_T when HQoS is not present */
    u8                   dwrr_cost[8] = {0};
    u32                  dwrr_cnt, dwrr_num;
    int                  queue;

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
    dwrr_num = dwrr_cnt;

    if (dwrr_cnt) {
        dwrr_cnt--; /* Value is offset by one. dwrr_cnt == 2 means that the 3 lowest inputs uses DWRR */
    }

    /* Select layer and scheduler element */
    JR2_WRM(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(layer) |
            VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX(se),
            VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER |
            VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX);

    JR2_WRM(VTSS_HSCH_HSCH_CFG_SE_CFG(se),
            VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT(dwrr_cnt),
            VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT);

    VTSS_RC(vtss_cmn_qos_weight2cost(conf->queue_pct, dwrr_cost, dwrr_num, VTSS_QOS_DWRR_COST_BIT_WIDTH));
    for (queue = 0; queue < 8; queue++) {
        JR2_WRM(VTSS_HSCH_HSCH_DWRR_DWRR_ENTRY(queue),
                VTSS_F_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_COST(dwrr_cost[queue]),
                VTSS_M_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_COST);
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_leak_list_init(vtss_state_t *vtss_state)
{
    vtss_qos_leak_layer_t *ll;
    vtss_qos_leak_group_t *lg;
    u32 layer, group, leak_interval;
    u32 sys_clk_per_100ps = 40; /* Unit is 100 pS. Default for Jaguar2 rev. B */

    /* Init allocation data for layer 0 */
    ll = &vtss_state->qos.leak_conf.layer[0];
    ll->entry = vtss_state->qos.leak_conf.l0_alloc;
    ll->entries = VTSS_HSCH_L0_SES;

    /* Leak lists are currently not used in layer 1 */

    /* Init allocation data for layer 2 */
    ll = &vtss_state->qos.leak_conf.layer[2];
    ll->entry = vtss_state->qos.leak_conf.l2_alloc;
    ll->entries = VTSS_HSCH_L2_SES;

    /* Init allocation data for layer 3 */
    ll = &vtss_state->qos.leak_conf.layer[3];
    ll->entry = vtss_state->qos.leak_conf.l3_alloc;
    ll->entries = VTSS_HSCH_L3_QSHPS;

    JR2_RD(VTSS_HSCH_HSCH_MISC_SYS_CLK_PER, &sys_clk_per_100ps);

    /* We use the same leak chain setup for all layers. Setup layer 0 and then final copy to other layers */
    ll = &vtss_state->qos.leak_conf.layer[0];
    ll->group[0].max_rate = VTSS_HSCH_MAX_RATE_GROUP_0;
    ll->group[1].max_rate = VTSS_HSCH_MAX_RATE_GROUP_1;
    ll->group[2].max_rate = VTSS_HSCH_MAX_RATE_GROUP_2;
    ll->group[3].max_rate = VTSS_HSCH_MAX_RATE_GROUP_3;

    for (group = 0; group < VTSS_HSCH_LEAK_LISTS; group++) {
        lg = &ll->group[group];
        leak_interval  = (128000 * 1000) / lg->max_rate; /* Calculate leak_interval in uS (max_rate is kbps) */
        lg->resolution = 1000 / leak_interval; /* Calculate resolution in kbps (leak_interval is in uS) */
        lg->leak_time  = 1000 * leak_interval; /* Calculate leak_time in 1nS units (leak_interval is in uS) */
        lg->max_ses    = (1000 * leak_interval) / sys_clk_per_100ps; /* We can service one SE in ~10 cycles.
                                                                        Calculate the maximum number of SEs
                                                                        we can service in each leak_interval */
    }
    /* Copy all groups from layer 0 to all other layers */
    for (layer = 1; layer < VTSS_HSCH_LAYERS; layer++) {
        for (group = 0; group < VTSS_HSCH_LEAK_LISTS; group++) {
            vtss_state->qos.leak_conf.layer[layer].group[group] = ll->group[group];
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_leak_first(vtss_state_t *vtss_state,
                                  const u32    layer,
                                  const u32    group,
                                  const u32    se)
{
    JR2_WRM(VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG(layer, group),
            VTSS_F_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_FIRST(se),
            VTSS_M_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_FIRST);
    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_leak_link(vtss_state_t *vtss_state,
                                 const u32    layer,
                                 const u32    group,
                                 const u32    se,
                                 const u32    se_next)
{
    if (layer == 3) { /* Queue shapers */
        JR2_WR(VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_CONNECT(se), se_next);
    } else {
        /* Select layer */
        JR2_WRM(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
                VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(layer),
                VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER);

        JR2_WR(VTSS_HSCH_HSCH_CFG_SE_CONNECT(se), se_next);
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_leak_time(vtss_state_t *vtss_state,
                                 const u32    layer,
                                 const u32    group,
                                 const u32    leak_time)
{
#if defined(VTSS_ARCH_JAGUAR_2_C)
    JR2_WR(VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_TIMER_CFG(layer, group), leak_time);
#else
    JR2_WRM(VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG(layer, group),
            VTSS_F_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_TIME(leak_time),
            VTSS_M_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_TIME);
#endif /* VTSS_ARCH_JAGUAR_2_C */
    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_leak_list_unlink(vtss_state_t *vtss_state,
                                        const u32    layer,
                                        const u32    se)
{
    vtss_qos_leak_layer_t *ll = &vtss_state->qos.leak_conf.layer[layer];
    vtss_qos_leak_entry_t *le = &ll->entry[se];

    if (layer >= VTSS_HSCH_LAYERS) {
        VTSS_E("Invalid layer %u!", layer);
        return VTSS_RC_ERROR;
    }

    if (se >= vtss_state->qos.leak_conf.layer[layer].entries) {
        VTSS_E("se %u >= %u in layer %u!", se, vtss_state->qos.leak_conf.layer[layer].entries, layer);
        return VTSS_RC_ERROR;
    }

    if (le->enabled) {
        vtss_qos_leak_group_t *lg   = &ll->group[le->group];
        BOOL                  first = (se == le->prev);
        BOOL                  last  = (se == le->next);

        /*
         * Shaper(s) MUST be disabled before calling this function!
         * The leak algorithm needs to run at least once in order to stop the shaper.
         * If the shaper is active (is shaping) and the leaking is disabled before the
         * leak algorithm has been run, all traffic is blocked by the shaper.
         */

        VTSS_NSLEEP(lg->leak_time);     /* Sleep one leak period */

        if (first) {
            if (last) {
                /* This is the one and only entry in the list. Disable leaking by setting leak_time to zero */
                lg->head.prev    = 0;
                lg->head.next    = 0;
                lg->head.group   = 0;
                lg->head.enabled = FALSE;
                VTSS_RC(jr2_qos_leak_time(vtss_state, layer, le->group, 0));
                if (lg->cur_ses != 1) {
                    VTSS_E("Layer %u, group %u. Unlink first&last SE but lg->cur_ses == %u!", layer, le->group, lg->cur_ses);
                    return VTSS_RC_ERROR;
                }
            } else { /* not last */
                lg->head.next = le->next;
                ll->entry[le->next].prev = le->next;
                VTSS_RC(jr2_qos_leak_first(vtss_state, layer, le->group, le->next));
                if (lg->cur_ses < 2) {
                    VTSS_E("Layer %u, group %u. Unlink first SE but lg->cur_ses == %u!", layer, le->group, lg->cur_ses);
                    return VTSS_RC_ERROR;
                }
            }
        } else { /* not first */
            if (last) {
                lg->head.prev = le->prev;
                ll->entry[le->prev].next = le->prev;
                VTSS_RC(jr2_qos_leak_link(vtss_state, layer, le->group, le->prev, le->prev));
                if (lg->cur_ses < 2) {
                    VTSS_E("Layer %u, group %u. Unlink last SE but lg->cur_ses == %u!", layer, le->group, lg->cur_ses);
                    return VTSS_RC_ERROR;
                }
            } else { /* not last */
                ll->entry[le->prev].next = le->next;
                ll->entry[le->next].prev = le->prev;
                VTSS_RC(jr2_qos_leak_link(vtss_state, layer, le->group, le->prev, le->next));
                if (lg->cur_ses < 3) {
                    VTSS_E("Layer %u, group %u. Unlink middle SE but lg->cur_ses == %u!", layer, le->group, lg->cur_ses);
                    return VTSS_RC_ERROR;
                }
            }
        }
        le->enabled = FALSE;
        lg->cur_ses--;
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_leak_list_link(vtss_state_t         *vtss_state,
                                      const u32            layer,
                                      const u32            se,
                                      const vtss_bitrate_t rate,
                                      vtss_bitrate_t       *resolution)
{
    vtss_qos_leak_layer_t *ll = &vtss_state->qos.leak_conf.layer[layer];
    vtss_qos_leak_entry_t *le = &ll->entry[se];
    vtss_qos_leak_group_t *lg = &ll->group[le->group];
    vtss_bitrate_t        current_max_rate = ll->group[le->group].max_rate;
    int                   group;
    BOOL                  change_group = FALSE;

    if (layer >= VTSS_HSCH_LAYERS) {
        VTSS_E("Invalid layer %u!", layer);
        return VTSS_RC_ERROR;
    }

    if (se >= vtss_state->qos.leak_conf.layer[layer].entries) {
        VTSS_E("se %u >= %u in layer %u!", se, vtss_state->qos.leak_conf.layer[layer].entries, layer);
        return VTSS_RC_ERROR;
    }

    if (le->enabled) {
        if (rate > current_max_rate) {
            change_group = TRUE;
        } else {
            /* Check if we can find a better group. We expect the groups to be ordered by rate with lowest rate at group[0] */
            for (group = le->group - 1; group >= 0; group--) {
                lg = &ll->group[group];
                if ((rate <= lg->max_rate) && (lg->max_rate < current_max_rate) && (lg->cur_ses < lg->max_ses)) {
                    change_group = TRUE;
                    break;
                }
            }
        }
        if (change_group) {
            VTSS_RC(jr2_qos_leak_list_unlink(vtss_state, layer, se));
        } else {
            *resolution = ll->group[le->group].resolution;
            return VTSS_RC_OK;
        }
    }
    /* Find best possible new group */
    for (group = 0; group < VTSS_HSCH_LEAK_LISTS; group++) {
        lg = &ll->group[group];
        if ((lg->cur_ses < lg->max_ses) && /* There must be free sessions left */
            ((rate <= lg->max_rate) ||     /* Rate must not exceed max_rate unless it is the last group */
             (group == (VTSS_HSCH_LEAK_LISTS - 1)))) {
            *resolution = lg->resolution;
            break;
        }
    }
    if (group == VTSS_HSCH_LEAK_LISTS) {
        *resolution = 0;
        VTSS_E("No free entries in leak lists!");
        return VTSS_RC_ERROR;
    }
    le->enabled = TRUE;
    le->group   = group;
    le->prev    = se; /* Always insert at head of chain */
    if (lg->head.enabled) { /* This is NOT the first entry in group */
        ll->entry[lg->head.next].prev = se;
        le->next = lg->head.next;
    } else { /* This is the first entry in group */
        le->next         = se;
        lg->head.prev    = se;
        lg->head.enabled = TRUE;
    }
    lg->head.next = se;
    lg->cur_ses++;
    VTSS_RC(jr2_qos_leak_time(vtss_state, layer, group, 0)); /* stop leaking */
    VTSS_RC(jr2_qos_leak_link(vtss_state, layer, group, se, le->next));
    VTSS_RC(jr2_qos_leak_first(vtss_state, layer, group, se));
    VTSS_RC(jr2_qos_leak_time(vtss_state, layer, group, lg->leak_time)); /* start leaking */

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_qos_shaper_conf_set(vtss_state_t *vtss_state, vtss_shaper_t *shaper, u32 layer, u32 se, u32 dlb_sense_port, u32 dlb_sense_qos)
{
    u32            cir, cbs, eir, ebs;
    vtss_bitrate_t resolution;

    VTSS_D("layer %u, se %u, dlb_sense_port %u, dlb_sense_qos %u!", layer, se, dlb_sense_port, dlb_sense_qos);

    /* Shaper rate configuration.
     * Resolution is determined by the actual leak list. Example if resolution is 100 kbps:
     * The value (in kbps) is rounded up to the next possible value:
     *        0 -> 0 (Open until burst capacity is used, then closed)
     *   1..100 -> 1 (100 kbps)
     * 101..200 -> 2 (200 kbps)
     * 201..300 -> 3 (300 kbps)
     */

    /* Shaper burst level configuration
     * The value is rounded up to the next possible value:
     *           0 -> 0 (Shaper disabled)
     *    1.. 4096 -> 1 ( 4 KB)
     * 4097.. 8192 -> 2 ( 8 KB)
     * 8193..12288 -> 3 (12 KB)
     */

    /* Select layer */
    JR2_WRM(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(layer),
            VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER);

    if (shaper->rate != VTSS_BITRATE_DISABLED) {
        VTSS_RC(jr2_qos_leak_list_link(vtss_state, layer, se, shaper->rate, &resolution));

        cir = MIN(VTSS_BITMASK(17), VTSS_DIV_ROUND_UP(shaper->rate,  resolution));
        cbs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP(shaper->level, 4096));

        JR2_WR(VTSS_HSCH_HSCH_CFG_CIR_CFG(se),
               VTSS_F_HSCH_HSCH_CFG_CIR_CFG_CIR_RATE(cir) |
               VTSS_F_HSCH_HSCH_CFG_CIR_CFG_CIR_BURST(cbs));

        if (shaper->eir != VTSS_BITRATE_DISABLED) {
            eir = MIN(VTSS_BITMASK(17), VTSS_DIV_ROUND_UP(shaper->eir, resolution));
            ebs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP(shaper->ebs, 4096));

            JR2_WR(VTSS_HSCH_HSCH_CFG_EIR_CFG(se),
                   VTSS_F_HSCH_HSCH_CFG_EIR_CFG_EIR_RATE(eir) |
                   VTSS_F_HSCH_HSCH_CFG_EIR_CFG_EIR_BURST(ebs));

            JR2_WR(VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE(se),
                   VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO(dlb_sense_qos)   |
                   VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT(dlb_sense_port) |
                   VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO_ENA(1)           |
                   VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT_ENA(1));
        } else {
            JR2_WR(VTSS_HSCH_HSCH_CFG_EIR_CFG(se),      0); /* Disable EIR */
            JR2_WR(VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE(se), 0); /* Disable DLB */
        }
        JR2_WRM(VTSS_HSCH_HSCH_CFG_SE_CFG(se),
                VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE(shaper->mode),
                VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE);
    } else {
        JR2_WR(VTSS_HSCH_HSCH_CFG_CIR_CFG(se),      0); /* Disable CIR */
        JR2_WR(VTSS_HSCH_HSCH_CFG_EIR_CFG(se),      0); /* Disable EIR */
        JR2_WR(VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE(se), 0); /* Disable DLB */
        JR2_WRM(VTSS_HSCH_HSCH_CFG_SE_CFG(se),
                VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE(0), /* Set to default */
                VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE);

        VTSS_RC(jr2_qos_leak_list_unlink(vtss_state, layer, se));
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_queue_shaper_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t *conf = &vtss_state->qos.port_conf[port_no];
    u32                  chip_port = VTSS_CHIP_PORT(port_no);
    u32                  layer = 0; /* Default layer on all variants */
    int                  queue;

    for (queue = 0; queue < 8; queue++) {
        u32 se = JR2_HSCH_L0_SE(chip_port, queue);
        VTSS_RC(vtss_jr2_qos_shaper_conf_set(vtss_state, &conf->shaper_queue[queue], layer, se, chip_port, queue));
        JR2_WRM(VTSS_HSCH_HSCH_CFG_SE_CFG(se),
                VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_AVB_ENA(conf->shaper_queue[queue].credit_enable),
                VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_AVB_ENA);
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t *conf = &vtss_state->qos.port_conf[port_no];
    u32                  chip_port = VTSS_CHIP_PORT(port_no);
    int                  pcp, dei, class, queue, policer;
    BOOL                 tag_default_dei;
    u32                  tag_pcp_cfg, tag_dei_cfg;

    /* Port default PCP and DEI configuration */
    JR2_WRM(VTSS_ANA_CL_PORT_VLAN_CTRL(chip_port),
            VTSS_F_ANA_CL_PORT_VLAN_CTRL_PORT_PCP(conf->usr_prio)     |
            VTSS_F_ANA_CL_PORT_VLAN_CTRL_PORT_DEI(conf->default_dei),
            VTSS_M_ANA_CL_PORT_VLAN_CTRL_PORT_PCP                     |
            VTSS_M_ANA_CL_PORT_VLAN_CTRL_PORT_DEI);

    /* Port default QoS class, DP level, tagged frames mode, DSCP mode and DSCP remarking configuration */
    JR2_WRM(VTSS_ANA_CL_PORT_QOS_CFG(chip_port),
            VTSS_F_ANA_CL_PORT_QOS_CFG_DSCP_REWR_MODE_SEL(conf->dscp_mode)                                      |
            VTSS_F_ANA_CL_PORT_QOS_CFG_DSCP_TRANSLATE_ENA(conf->dscp_translate)                                 |
            VTSS_F_ANA_CL_PORT_QOS_CFG_PCP_DEI_DP_ENA(conf->tag_class_enable)                                   |
            VTSS_F_ANA_CL_PORT_QOS_CFG_PCP_DEI_QOS_ENA(conf->tag_class_enable)                                  |
            VTSS_F_ANA_CL_PORT_QOS_CFG_DSCP_DP_ENA(conf->dscp_class_enable)                                     |
            VTSS_F_ANA_CL_PORT_QOS_CFG_DSCP_QOS_ENA(conf->dscp_class_enable)                                    |
            VTSS_F_ANA_CL_PORT_QOS_CFG_DEFAULT_DP_VAL(conf->default_dpl)                                        |
            VTSS_F_ANA_CL_PORT_QOS_CFG_DEFAULT_QOS_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->default_prio)),
            VTSS_M_ANA_CL_PORT_QOS_CFG_DSCP_REWR_MODE_SEL                                                       |
            VTSS_M_ANA_CL_PORT_QOS_CFG_DSCP_TRANSLATE_ENA                                                       |
            VTSS_M_ANA_CL_PORT_QOS_CFG_PCP_DEI_DP_ENA                                                           |
            VTSS_M_ANA_CL_PORT_QOS_CFG_PCP_DEI_QOS_ENA                                                          |
            VTSS_M_ANA_CL_PORT_QOS_CFG_DSCP_DP_ENA                                                              |
            VTSS_M_ANA_CL_PORT_QOS_CFG_DSCP_QOS_ENA                                                             |
            VTSS_M_ANA_CL_PORT_QOS_CFG_DEFAULT_DP_VAL                                                           |
            VTSS_M_ANA_CL_PORT_QOS_CFG_DEFAULT_QOS_VAL);

    /* Egress DSCP remarking configuration */
    JR2_WR(VTSS_REW_PORT_DSCP_MAP(chip_port),
           VTSS_F_REW_PORT_DSCP_MAP_DSCP_UPDATE_ENA((conf->dscp_emode > VTSS_DSCP_EMODE_DISABLE)) |
           VTSS_F_REW_PORT_DSCP_MAP_DSCP_REMAP_ENA((conf->dscp_emode > VTSS_DSCP_EMODE_REMARK)));

    /* Map for (PCP and DEI) to (QoS class and DP level */
    for (pcp = VTSS_PCP_START; pcp < VTSS_PCP_END; pcp++) {
        for (dei = VTSS_DEI_START; dei < VTSS_DEI_END; dei++) {
            JR2_WR(VTSS_ANA_CL_PORT_PCP_DEI_MAP_CFG(chip_port, (8 * dei + pcp)),
                   VTSS_F_ANA_CL_PORT_PCP_DEI_MAP_CFG_PCP_DEI_DP_VAL(conf->dp_level_map[pcp][dei]) |
                   VTSS_F_ANA_CL_PORT_PCP_DEI_MAP_CFG_PCP_DEI_QOS_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->qos_class_map[pcp][dei])));
        }
    }

    /* Port scheduler configuration. */
    VTSS_RC(jr2_qos_dwrr_conf_set(vtss_state, port_no));

    /* Port shaper configuration. Use scheduler element in layer 2 indexed by chip_port. */
    VTSS_RC(vtss_jr2_qos_shaper_conf_set(vtss_state, &conf->shaper_port, 2, chip_port, chip_port, 0));

    /* Queue shaper configuration. */
    VTSS_RC(jr2_qos_queue_shaper_conf_set(vtss_state, port_no));

    /* Tag remarking configuration */
    tag_default_dei = (conf->tag_remark_mode == VTSS_TAG_REMARK_MODE_DEFAULT ? conf->tag_default_dei : 0); // JR2-TBD: Is this necessary on JR2?

    JR2_WRM(VTSS_REW_PORT_PORT_VLAN_CFG(chip_port),
            VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_PCP(conf->tag_default_pcp) |
            VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_DEI(tag_default_dei),                                       // Is this necessary on JR2?
            VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_PCP                        |
            VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_DEI);

    switch (conf->tag_remark_mode) {
    case VTSS_TAG_REMARK_MODE_DEFAULT:
        tag_pcp_cfg = 1; /* PORT_PCP */
        tag_dei_cfg = 1; /* PORT_DEI */
        break;
    case VTSS_TAG_REMARK_MODE_MAPPED:
        tag_pcp_cfg = 2; /* DE and QoS mapped to PCP (PCP_MAP_DEx */
        tag_dei_cfg = 2; /* DE and QoS mapped to DEI (DEI_MAP_DEx */
        break;
    default:
        tag_pcp_cfg = 0; /* Classified PCP */
        tag_dei_cfg = 0; /* Classified PCP/DEI */
        break;
    }

    JR2_WRM(VTSS_REW_PORT_TAG_CTRL(chip_port),
            VTSS_F_REW_PORT_TAG_CTRL_TAG_PCP_CFG(tag_pcp_cfg) |
            VTSS_F_REW_PORT_TAG_CTRL_TAG_DEI_CFG(tag_dei_cfg),
            VTSS_M_REW_PORT_TAG_CTRL_TAG_PCP_CFG              |
            VTSS_M_REW_PORT_TAG_CTRL_TAG_DEI_CFG);

    /* Map for (QoS class and DP level) to (PCP and DEI) */
    for (class = VTSS_QUEUE_START; class < VTSS_QUEUE_END; class++) {
        JR2_WR(VTSS_REW_PORT_PCP_MAP_DE0(chip_port, class),
               VTSS_F_REW_PORT_PCP_MAP_DE0_PCP_DE0(conf->tag_pcp_map[class][0]));
        JR2_WR(VTSS_REW_PORT_PCP_MAP_DE1(chip_port, class),
               VTSS_F_REW_PORT_PCP_MAP_DE1_PCP_DE1(conf->tag_pcp_map[class][1]));
        JR2_WR(VTSS_REW_PORT_DEI_MAP_DE0(chip_port, class),
               VTSS_F_REW_PORT_DEI_MAP_DE0_DEI_DE0(conf->tag_dei_map[class][0]));
        JR2_WR(VTSS_REW_PORT_DEI_MAP_DE1(chip_port, class),
               VTSS_F_REW_PORT_DEI_MAP_DE1_DEI_DE1(conf->tag_dei_map[class][1]));
    }

    /* Port policer configuration */
    for (policer = 0; policer < VTSS_PORT_POLICERS; policer++) {
        VTSS_RC(jr2_port_policer_set(vtss_state, chip_port, policer, &conf->policer_port[policer], &conf->policer_ext_port[policer]));
    }

    /* Queue policer configuration */
    for (queue = 0; queue < 8; queue++) {
        VTSS_RC(jr2_queue_policer_set(vtss_state, chip_port, queue, &conf->policer_queue[queue]));
    }

    /* Update policer flow control configuration */
    VTSS_RC(vtss_jr2_port_policer_fc_set(vtss_state, port_no, chip_port));

    /* Update WRED group configuration */
    if (conf->wred_group > 2) {
        VTSS_E("Invalid WRED group: %u!", conf->wred_group);
        return VTSS_RC_ERROR;
    }
    JR2_WR(VTSS_QRES_RES_QOS_ADV_WRED_GROUP(chip_port), conf->wred_group);

    /* Update VCAP port QoS configuration */
    VTSS_RC(vtss_jr2_vcap_port_qos_update(vtss_state, port_no));

    return VTSS_RC_OK;
}

static vtss_rc jr2_storm_policer_set(vtss_state_t             *vtss_state,
                                     u32                       idx,
                                     vtss_packet_rate_t        rate,
                                     BOOL                      frame_rate,
                                     vtss_storm_policer_mode_t mode)
{
    BOOL noncpu_traffic, cpu_traffic;
    u32  traffic_type_mask;

    if (idx > 2) {
        VTSS_E("Invalid storm policer index: %u!", idx);
        return VTSS_RC_ERROR;
    }

    if (rate == VTSS_PACKET_RATE_DISABLED) {
        /* Apply default values */
        JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG(idx), 0);
        JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG(idx), 0);
        JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL(idx),
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_NONCPU_TRAFFIC_ENA(1));
    } else {
        if (mode == VTSS_STORM_POLICER_MODE_PORTS_ONLY) {
            noncpu_traffic = TRUE;
            cpu_traffic    = FALSE;
        } else if (mode == VTSS_STORM_POLICER_MODE_CPU_ONLY) {
            noncpu_traffic = FALSE;
            cpu_traffic    = TRUE;
        } else {
            noncpu_traffic = TRUE;
            cpu_traffic    = TRUE;
        }

        if (idx == 0) {
            traffic_type_mask = 0x20; /* Unknown unicast:   0b0010.0000 */
        } else if (idx == 1) {
            traffic_type_mask = 0x08; /* Unknown multicast: 0b0000.1000 */
        } else {
            traffic_type_mask = 0x10; /* Unknown broadcast: 0b0001.0000 */
        }

        JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG(idx),
               jr2_calc_policer_rate(rate, frame_rate));
        JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG(idx),
               jr2_calc_policer_level(8192 * 2, rate, frame_rate));
        JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL(idx),
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_FRAME_RATE_ENA(frame_rate)               |
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_CPU_QU_MASK(0)                           |
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_NONCPU_TRAFFIC_ENA(noncpu_traffic) |
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_CPU_TRAFFIC_ENA(cpu_traffic)       |
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_TRAFFIC_TYPE_MASK(traffic_type_mask));
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_ARCH_SERVAL_T)
#define WRED_BITMASK VTSS_BITMASK(9)
#else
#define WRED_BITMASK VTSS_BITMASK(11)
#endif

static vtss_rc jr2_qos_wred_conf_set(vtss_state_t *vtss_state)
{
    vtss_qos_conf_t *conf = &vtss_state->qos.conf;
    int              group, queue, dpl;

    for (group = 0; group < VTSS_WRED_GROUP_CNT; group++) {
        for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
            u32 wm_high = vtss_jr2_wm_high_get(vtss_state, queue);

            for (dpl = 0; dpl < VTSS_WRED_DPL_CNT; dpl++) {
                vtss_red_v3_t *red = &conf->red_v3[queue][dpl][group];
                vtss_pct_t     max_dp = 100;
                vtss_pct_t     max_fl = 100;
                u32            wm_red_low, wm_red_high;

                /* Sanity check */
                if (red->min_fl > 100) {
                    VTSS_E("illegal min_fl (%u) on group %d, queue %d, dpl %d", red->min_fl, group, queue, dpl);
                    return VTSS_RC_ERROR;
                }
                if ((red->max < 1) || (red->max > 100)) {
                    VTSS_E("illegal max (%u) on group %d, queue %d, dpl %d", red->max, group, queue, dpl);
                    return VTSS_RC_ERROR;
                }
                if ((red->max_unit != VTSS_WRED_V2_MAX_DP) && (red->max_unit != VTSS_WRED_V2_MAX_FL)) {
                    VTSS_E("illegal max_unit (%u) on group %d, queue %d, dpl %d", red->max_unit, group, queue, dpl);
                    return VTSS_RC_ERROR;
                }
                if (red->max_unit == VTSS_WRED_V2_MAX_DP) {
                    max_dp = red->max; /* Unit is drop probability - save specified value */
                } else {
                    if (red->min_fl >= red->max) {
                        VTSS_E("min_fl (%u) >= max fl (%u) on group %d, queue %d, dpl %d", red->min_fl, red->max, group, queue, dpl);
                        return VTSS_RC_ERROR;
                    } else {
                        max_fl = red->max; /* Unit is fill level - save specified value */
                    }
                }
                if (red->enable) {
                    wm_red_low  = wm_high * red->min_fl / 100;                              /* Convert from % to actual value in bytes */
                    wm_red_high = wm_high * max_fl / 100;                                   /* Convert from % to actual value in bytes */
                    wm_red_high = ((wm_red_high - wm_red_low) * 100 / max_dp) + wm_red_low; /* Adjust wm_red_high to represent 100% drop probability */
                    wm_red_low  = MIN(wm_red_low / 2816, WRED_BITMASK);                     /* Convert from bytes to 2816 byte chunks and prevent overflow */
                    wm_red_high = MIN(wm_red_high / 2816, WRED_BITMASK);                    /* Convert from bytes to 2816 byte chunks and prevent overflow */
                } else {
                    wm_red_low = wm_red_high = WRED_BITMASK;                                /* Disable red by setting both fields to max */
                }

                JR2_WR(VTSS_QRES_RES_WRED_WRED_PROFILE((24 * group) + (8 * dpl) + queue),   /* Red profile for qroup, queue, dpl */
                       VTSS_F_QRES_RES_WRED_WRED_PROFILE_WM_RED_LOW(wm_red_low) |
                       VTSS_F_QRES_RES_WRED_WRED_PROFILE_WM_RED_HIGH(wm_red_high));
            }
        }
    }

    VTSS_RC(vtss_jr2_wm_update(vtss_state)); /* Update watermarks */

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_conf_set(vtss_state_t *vtss_state, BOOL changed)
{
    vtss_qos_conf_t    *conf = &vtss_state->qos.conf;
    vtss_port_no_t     port_no;
    u32                i;

    if (changed) {
        /* Number of priorities changed, update QoS setup for all ports */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            VTSS_RC(jr2_qos_port_conf_set(vtss_state, port_no));
        }
    }

    /* Storm control:
     *
     * Jaguar 2 has eight identical configurable storm policers.
     *
     * Allocation:
     *  Policer 0:   Unicast (unknown unicast frames).
     *  Policer 1:   Multicast (unknown multicast frames).
     *  Policer 2:   Broadcast (known and unknown broadcast frames).
     *  Policer 3-7: Not used.
     */
    VTSS_RC(jr2_storm_policer_set(vtss_state, 0, conf->policer_uc, conf->policer_uc_frame_rate, conf->policer_uc_mode));
    VTSS_RC(jr2_storm_policer_set(vtss_state, 1, conf->policer_mc, conf->policer_mc_frame_rate, conf->policer_mc_mode));
    VTSS_RC(jr2_storm_policer_set(vtss_state, 2, conf->policer_bc, conf->policer_bc_frame_rate, conf->policer_bc_mode));

    /* DSCP classification and remarking configuration: */
    for (i = 0; i < 64; i++) {
        JR2_WR(VTSS_ANA_CL_COMMON_DSCP_CFG(i),
               VTSS_F_ANA_CL_COMMON_DSCP_CFG_DSCP_TRANSLATE_VAL(conf->dscp_translate_map[i])                               |
               VTSS_F_ANA_CL_COMMON_DSCP_CFG_DSCP_QOS_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->dscp_qos_class_map[i])) |
               VTSS_F_ANA_CL_COMMON_DSCP_CFG_DSCP_DP_VAL(conf->dscp_dp_level_map[i])                                       |
               VTSS_F_ANA_CL_COMMON_DSCP_CFG_DSCP_REWR_ENA(conf->dscp_remark[i])                                           |
               VTSS_F_ANA_CL_COMMON_DSCP_CFG_DSCP_TRUST_ENA(conf->dscp_trust[i]));
        JR2_WR(VTSS_REW_COMMON_DSCP_REMAP(i),
               VTSS_F_REW_COMMON_DSCP_REMAP_DSCP_REMAP(conf->dscp_remap[i]));
    }

    /* DSCP classification from QoS configuration: */
    for (i = 0; i < 8; i++) {
        JR2_WR(VTSS_ANA_CL_COMMON_QOS_MAP_CFG(i),
               VTSS_F_ANA_CL_COMMON_QOS_MAP_CFG_DSCP_REWR_VAL(conf->dscp_qos_map[i]));
        JR2_WR(VTSS_ANA_CL_COMMON_QOS_MAP_CFG(i +  8),
               VTSS_F_ANA_CL_COMMON_QOS_MAP_CFG_DSCP_REWR_VAL(conf->dscp_qos_map_dp1[i]));
        JR2_WR(VTSS_ANA_CL_COMMON_QOS_MAP_CFG(i + 16),
               VTSS_F_ANA_CL_COMMON_QOS_MAP_CFG_DSCP_REWR_VAL(conf->dscp_qos_map_dp2[i]));
        JR2_WR(VTSS_ANA_CL_COMMON_QOS_MAP_CFG(i + 24),
               VTSS_F_ANA_CL_COMMON_QOS_MAP_CFG_DSCP_REWR_VAL(conf->dscp_qos_map_dp3[i]));

    }

    /* WRED configuration: */
    VTSS_RC(jr2_qos_wred_conf_set(vtss_state));

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_ingress_map_vcap_update(vtss_state_t *vtss_state,
                                               const u16    id)
{
    vtss_port_no_t port_no;

    VTSS_D("id %u", id);

    /* Update CLM for all ports that references this ID */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (id == vtss_state->qos.port_conf[port_no].ingress_map) {
            /* Update VCAP port QoS configuration */
            VTSS_RC(vtss_jr2_vcap_port_qos_update(vtss_state, port_no));
        }
    }

    /* Update CLM on ID/key changes */
    return vtss_vcap_clm_update(vtss_state, id);
}

static vtss_rc jr2_qos_ingress_map_hw_entry_update(vtss_state_t                        *vtss_state,
                                                   const u32                           row,
                                                   const u32                           col,
                                                   const vtss_qos_ingress_map_values_t *const val)
{
    JR2_WR(VTSS_ANA_CL_MAP_TBL_MAP_ENTRY(row, col),
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_PATH_COLOR_VAL(!!val->dpl)      |
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_PATH_COSID_VAL(val->path_cosid) |
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_DP_VAL(val->dpl)                |
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_COSID_VAL(val->cosid)           |
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_QOS_VAL(val->cos)               |
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_DEI_VAL(val->dei)               |
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_PCP_VAL(val->pcp)               |
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_DSCP_VAL(val->dscp)             |
           VTSS_F_ANA_CL_MAP_TBL_MAP_ENTRY_TC_VAL(val->mpls_tc));

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_ingress_map_hw_update(vtss_state_t *vtss_state,
                                             const u16    res,
                                             const u16    ix,
                                             const int    len,
                                             const void   *const map)
{
    u32 col, row;
    const vtss_qos_ingress_map_t *const m = map;

    VTSS_D("res %u, ix %u, len %u", res, ix, len);

    if (m) {
        u32 action =
            VTSS_F_ANA_CL_MAP_TBL_SET_CTRL_PATH_ENA(m->action.path)   |
            VTSS_F_ANA_CL_MAP_TBL_SET_CTRL_DP_ENA(m->action.dpl)      |
            VTSS_F_ANA_CL_MAP_TBL_SET_CTRL_COSID_ENA(m->action.cosid) |
            VTSS_F_ANA_CL_MAP_TBL_SET_CTRL_QOS_ENA(m->action.cos)     |
            VTSS_F_ANA_CL_MAP_TBL_SET_CTRL_DEI_ENA(m->action.dei)     |
            VTSS_F_ANA_CL_MAP_TBL_SET_CTRL_PCP_ENA(m->action.pcp)     |
            VTSS_F_ANA_CL_MAP_TBL_SET_CTRL_DSCP_ENA(m->action.dscp)   |
            VTSS_F_ANA_CL_MAP_TBL_SET_CTRL_TC_ENA(m->action.mpls_tc);

        switch (m->key) {
        case VTSS_QOS_INGRESS_MAP_KEY_PCP:
            /* Add 1 row with PCP values */
            JR2_WR(VTSS_ANA_CL_MAP_TBL_SET_CTRL(ix), action);
            for (col = 0; col < 8; col++) {
                VTSS_RC(jr2_qos_ingress_map_hw_entry_update(vtss_state, ix, col, &m->maps.pcp[col]));
            }
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI:
            /* Add 2 row with PCP/DEI values */
            for (row = 0; row < 2; row++) {
                JR2_WR(VTSS_ANA_CL_MAP_TBL_SET_CTRL(ix + row), action);
                for (col = 0; col < 8; col++) {
                    VTSS_RC(jr2_qos_ingress_map_hw_entry_update(vtss_state, ix + row, col, &m->maps.pcp_dei[col][row]));
                }
            }
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_DSCP:
            /* Add 8 rows with DSCP values */
            for (row = 0; row < 8; row++) {
                JR2_WR(VTSS_ANA_CL_MAP_TBL_SET_CTRL(ix + row), action);
                for (col = 0; col < 8; col++) {
                    VTSS_RC(jr2_qos_ingress_map_hw_entry_update(vtss_state, ix + row, col, &m->maps.dscp[(row * 8) + col]));
                }
            }
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI:
            /* Add 8 rows with DSCP values */
            for (row = 0; row < 8; row++) {
                JR2_WR(VTSS_ANA_CL_MAP_TBL_SET_CTRL(ix + row), action);
                for (col = 0; col < 8; col++) {
                    VTSS_RC(jr2_qos_ingress_map_hw_entry_update(vtss_state, ix + row, col, &m->maps.dpd.dscp[(row * 8) + col]));
                }
            }
            /* Add 2 rows with PCP/DEI values after the 8 DSCP rows */
            for (row = 0; row < 2; row++) {
                JR2_WR(VTSS_ANA_CL_MAP_TBL_SET_CTRL(8 + ix + row), action);
                for (col = 0; col < 8; col++) {
                    VTSS_RC(jr2_qos_ingress_map_hw_entry_update(vtss_state, 8 + ix + row, col, &m->maps.dpd.pcp_dei[col][row]));
                }
            }
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC:
            /* Add 1 row with MPLS TC values */
            JR2_WR(VTSS_ANA_CL_MAP_TBL_SET_CTRL(ix), action);
            for (col = 0; col < 8; col++) {
                VTSS_RC(jr2_qos_ingress_map_hw_entry_update(vtss_state, ix, col, &m->maps.mpls_tc[col]));
            }
            break;
        default:
            VTSS_E("Invalid ingress map key: %u!", m->key);
            return VTSS_RC_ERROR;
        }
    } else {
        /* Set rows to zero */
        for (row = 0; row < len; row++) {
            JR2_WR(VTSS_ANA_CL_MAP_TBL_SET_CTRL(ix + row), 0);
            for (col = 0; col < 8; col++) {
                JR2_WR(VTSS_ANA_CL_MAP_TBL_MAP_ENTRY(ix + row, col), 0);
            }
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_ingress_map_hw_copy(vtss_state_t *vtss_state,
                                           const u16    res,
                                           const u16    src,
                                           const u16    dst,
                                           const int    len)
{
    u32 col, row, val;

    VTSS_D("res %u, src %u, dst %u, len %d", res, src, dst, len);

    for (row = 0; row < len; row++) {
        JR2_RD(VTSS_ANA_CL_MAP_TBL_SET_CTRL(src + row), &val);
        JR2_WR(VTSS_ANA_CL_MAP_TBL_SET_CTRL(dst + row), val);
        for (col = 0; col < 8; col++) {
            JR2_RD(VTSS_ANA_CL_MAP_TBL_MAP_ENTRY(src + row, col), &val);
            JR2_WR(VTSS_ANA_CL_MAP_TBL_MAP_ENTRY(dst + row, col), val);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_ingress_map_add(vtss_state_t *vtss_state, const vtss_qos_ingress_map_t *const map)
{
    VTSS_D("id %u, key %u", map->id, map->key);
    return vtss_cmn_qos_map_add(vtss_state, &vtss_state->qos.imap, map->id, map->key, 0, map);
}

static vtss_rc jr2_qos_ingress_map_del(vtss_state_t *vtss_state, const vtss_qos_ingress_map_id_t id)
{
    VTSS_D("id %u", id);
    return vtss_cmn_qos_map_del(vtss_state, &vtss_state->qos.imap, id);
}

static vtss_rc jr2_qos_egress_map_vcap_update(vtss_state_t *vtss_state,
                                              const u16    id)
{
    vtss_port_no_t port_no;

    VTSS_D("id %u", id);

    /* Update ES0 for all ports that references this ID */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (id == vtss_state->qos.port_conf[port_no].egress_map) {
            /* Update VCAP port QoS configuration */
            VTSS_RC(vtss_jr2_vcap_port_qos_update(vtss_state, port_no));
        }
    }

    /* Update ES0 on ID/key changes */
    return vtss_vcap_es0_emap_update(vtss_state, id);
}

static vtss_rc jr2_qos_egress_map_hw_entry_update(vtss_state_t                       *vtss_state,
                                                  const u32                          res,
                                                  const u32                          row,
                                                  const u32                          col,
                                                  const vtss_qos_egress_map_values_t *const val)
{
    if (res == 0) { // Resource A
        JR2_WR(VTSS_REW_MAP_RES_A_MAP_VAL_A((row * 8) + col),
               VTSS_F_REW_MAP_RES_A_MAP_VAL_A_OAM_COLOR(val->dei)        |
               VTSS_F_REW_MAP_RES_A_MAP_VAL_A_OAM_COSID(val->path_cosid) |
               VTSS_F_REW_MAP_RES_A_MAP_VAL_A_DSCP_VAL(val->dscp)        |
               VTSS_F_REW_MAP_RES_A_MAP_VAL_A_DEI_VAL(val->dei)          |
               VTSS_F_REW_MAP_RES_A_MAP_VAL_A_PCP_VAL(val->pcp)          |
               VTSS_F_REW_MAP_RES_A_MAP_VAL_A_TC_VAL(val->mpls_tc));
    } else { // Resource B
        JR2_WR(VTSS_REW_MAP_RES_B_MAP_VAL_B((row * 8) + col),
               VTSS_F_REW_MAP_RES_B_MAP_VAL_B_OAM_COLOR(val->dei)        |
               VTSS_F_REW_MAP_RES_B_MAP_VAL_B_OAM_COSID(val->path_cosid) |
               VTSS_F_REW_MAP_RES_B_MAP_VAL_B_DSCP_VAL(val->dscp)        |
               VTSS_F_REW_MAP_RES_B_MAP_VAL_B_DEI_VAL(val->dei)          |
               VTSS_F_REW_MAP_RES_B_MAP_VAL_B_PCP_VAL(val->pcp)          |
               VTSS_F_REW_MAP_RES_B_MAP_VAL_B_TC_VAL(val->mpls_tc));
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_egress_map_hw_update(vtss_state_t *vtss_state,
                                            const u16     res,
                                            const u16     ix,
                                            const int     len,
                                            const void   *const map)
{
    u32 col, row, dpl;
    const vtss_qos_egress_map_t *const m = map;

    VTSS_D("res %u, ix %u, len %u", res, ix, len);

    if (m) {
        switch (m->key) {
        case VTSS_QOS_EGRESS_MAP_KEY_COSID:
            /* Add 1 row with COSID values */
            for (col = 0; col < 8; col++) {
                VTSS_RC(jr2_qos_egress_map_hw_entry_update(vtss_state, res, ix, col, &m->maps.cosid[col]));
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_COSID_DPL:
            /* Add 4 rows with COSID/DPL values */
            for (row = 0; row < 4; row++) {
                for (col = 0; col < 8; col++) {
                    VTSS_RC(jr2_qos_egress_map_hw_entry_update(vtss_state, res, ix + row, col, &m->maps.cosid_dpl[col][row]));
                }
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_DSCP:
            /* Add 8 rows with DSCP values */
            for (row = 0; row < 8; row++) {
                for (col = 0; col < 8; col++) {
                    VTSS_RC(jr2_qos_egress_map_hw_entry_update(vtss_state, res, ix + row, col, &m->maps.dscp[(row * 8) + col]));
                }
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_DSCP_DPL:
            /* Add 32 rows with DSCP/DPL values */
            for (dpl = 0; dpl < 4; dpl++) {
                for (row = 0; row < 8; row++) {
                    for (col = 0; col < 8; col++) {
                        VTSS_RC(jr2_qos_egress_map_hw_entry_update(vtss_state, res, ix + row + (dpl * 8), col, &m->maps.dscp_dpl[(row * 8) + col][dpl]));
                    }
                }
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC:
            /* Add 1 row with TC values */
            for (col = 0; col < 8; col++) {
                VTSS_RC(jr2_qos_egress_map_hw_entry_update(vtss_state, res, ix, col, &m->maps.mpls_tc[col]));
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL:
            /* Add 4 rows with MPLS TC/DPL values */
            for (row = 0; row < 4; row++) {
                for (col = 0; col < 8; col++) {
                    VTSS_RC(jr2_qos_egress_map_hw_entry_update(vtss_state, res, ix + row, col, &m->maps.mpls_tc_dpl[col][row]));
                }
            }
            break;
        default:
            VTSS_E("Invalid ingress map key: %u!", m->key);
            return VTSS_RC_ERROR;
        }
    } else {
        /* Set rows to zero */
        for (row = 0; row < len; row++) {
            for (col = 0; col < 8; col++) {
                if (res == 0) { // Resource A
                    JR2_WR(VTSS_REW_MAP_RES_A_MAP_VAL_A(((ix + row) * 8) + col), 0);
                } else { // Resource B
                    JR2_WR(VTSS_REW_MAP_RES_B_MAP_VAL_B(((ix + row) * 8) + col), 0);
                }
            }
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_egress_map_hw_copy(vtss_state_t *vtss_state,
                                          const u16    res,
                                          const u16    src,
                                          const u16    dst,
                                          const int    len)
{
    u32 col, row, val;

    VTSS_D("res %u, src %u, dst %u, len %d", res, src, dst, len);

    for (row = 0; row < len; row++) {
        for (col = 0; col < 8; col++) {
            if (res == 0) { // Resource A
                JR2_RD(VTSS_REW_MAP_RES_A_MAP_VAL_A(((src + row) * 8) + col), &val);
                JR2_WR(VTSS_REW_MAP_RES_A_MAP_VAL_A(((dst + row) * 8) + col), val);
            } else { // Resource B
                JR2_RD(VTSS_REW_MAP_RES_B_MAP_VAL_B(((src + row) * 8) + col), &val);
                JR2_WR(VTSS_REW_MAP_RES_B_MAP_VAL_B(((dst + row) * 8) + col), val);
            }
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_egress_map_add(vtss_state_t *vtss_state, const vtss_qos_egress_map_t *const map)
{
    u8 flags = 0;

    VTSS_D("id %u, key %u", map->id, map->key);

    if (map->action.pcp) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_PCP;
    }
    if (map->action.dei) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_DEI;
    }
    if (map->action.dscp) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_DSCP;
    }
    if (map->action.path) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_PATH;
    }
    if (map->action.mpls_tc) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_MPLS_TC;
    }

    return vtss_cmn_qos_map_add(vtss_state, &vtss_state->qos.emap, map->id, map->key, flags, map);
}

static vtss_rc jr2_qos_egress_map_del(vtss_state_t *vtss_state, const vtss_qos_egress_map_id_t id)
{
    VTSS_D("id %u", id);
    return vtss_cmn_qos_map_del(vtss_state, &vtss_state->qos.emap, id);
}

static vtss_rc jr2_qos_cpu_port_shaper_set(vtss_state_t *vtss_state, const vtss_bitrate_t rate)
{
    vtss_shaper_t shaper;
    u32           se, i;

    for (i = 0; i < 2; i++) {
#if defined(VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER)
        u32            queue, packet_rate, cir;
        vtss_bitrate_t res;

        /* Allocate queue shapers for CPU port layer 0 element */
        se = (JR2_L0_SE_CPU_0 + i);
        JR2_WR(VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG(se),
               VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_MIN(0) |
               VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_MAX(7)|
               VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_BASE(i * 8));

        /* Link to first group in layer 3 leak list */
        VTSS_RC(jr2_qos_leak_list_link(vtss_state, 3, se, VTSS_HSCH_MAX_RATE_GROUP_0, &res));
        JR2_WR(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
               VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX(se));
        for (queue = 0; queue < 8; queue++) {
            /* Resolution is in 1 kbps units, and 1 FPS corresponds to 100 kbps */
            packet_rate = vtss_state->packet.rx_conf.queue[queue].rate;
            cir = MIN(VTSS_BITMASK(17), VTSS_DIV_ROUND_UP(packet_rate * 100,  res));
            JR2_WR(VTSS_HSCH_QSHP_CFG_QSHP_CIR_CFG(queue),
                   VTSS_F_HSCH_QSHP_CFG_QSHP_CIR_CFG_CIR_RATE(cir) |
                   VTSS_F_HSCH_QSHP_CFG_QSHP_CIR_CFG_CIR_BURST(packet_rate == VTSS_PACKET_RATE_DISABLED ? 0 : 1));
            JR2_WR(VTSS_HSCH_QSHP_CFG_QSHP_CFG(queue),
                   VTSS_F_HSCH_QSHP_CFG_QSHP_CFG_SE_FRM_MODE(3));
        }
#endif
        /* CPU port shaper (kbps) */
        VTSS_MEMSET(&shaper, 0, sizeof(shaper));
        shaper.rate  = rate;       // kbps
        shaper.level = (4096 * 4); // 16 kbytes burst size
        shaper.eir   = VTSS_BITRATE_DISABLED;
        se = (VTSS_CHIP_PORT_CPU_0 + i);
        VTSS_RC(vtss_jr2_qos_shaper_conf_set(vtss_state, &shaper, 2, se, 0, 0));
    }
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */
static vtss_rc jr2_debug_qos_scheduler_element(vtss_state_t              *vtss_state,
                                               const vtss_debug_printf_t pr,
                                               const char                *header,
                                               const u32                 layer,
                                               const u32                 se)
{
    JR2_WRM(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(layer) |
            VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX(se),
            VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER |
            VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX);

    vtss_jr2_debug_reg_header(pr, header);
    vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_CFG_CIR_CFG(se),      se, "HSCH_CFG_CIR_CFG");
    vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_CFG_EIR_CFG(se),      se, "HSCH_CFG_EIR_CFG");
    vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_CFG_SE_CFG(se),       se, "HSCH_CFG_SE_CFG");
    vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_CFG_SE_CONNECT(se),   se, "HSCH_CFG_SE_CONNECT");
    vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE(se), se, "HSCH_CFG_SE_DLB_SENSE");

    return VTSS_RC_OK;
}

static void jr2_debug_qos_ingress_mapping(vtss_state_t              *vtss_state,
                                          const vtss_debug_printf_t pr,
                                          const u32                 ix_start,
                                          const int                 length)
{
    u32  ix, col;
    int  len;
    char buf[64];

    for (len = 0; len < length; len++) {
        ix = ix_start + len;
        VTSS_SPRINTF(buf, "Index %u, (%u of %u)", ix, len + 1, length);
        vtss_jr2_debug_reg_header(pr, buf);
        VTSS_SPRINTF(buf, " MAP_TBL[%u]:SET_CTRL", ix);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_CL_MAP_TBL_SET_CTRL(ix), buf);
        for (col = 0; col < 8; col++) {
            VTSS_SPRINTF(buf, " MAP_TBL[%u]:MAP_ENTRY[%u]", ix, col);
            vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_CL_MAP_TBL_MAP_ENTRY(ix, col), buf);
        }
    }
}

static void jr2_debug_qos_egress_mapping(vtss_state_t              *vtss_state,
                                         const vtss_debug_printf_t pr,
                                         const u32                 res,
                                         const u32                 ix_start,
                                         const int                 length)
{
    u32  ix, col, addr;
    int  len;
    char buf[64];

    for (len = 0; len < length; len++) {
        ix = ix_start + len;
        VTSS_SPRINTF(buf, "Index %u, (%u of %u)", ix, len + 1, length);
        vtss_jr2_debug_reg_header(pr, buf);
        for (col = 0; col < 8; col++) {
            addr = (ix * 8) + col;
            if (res == 0) { // Resource A
                VTSS_SPRINTF(buf, " MAP_RES_A[%u]:MAP_VAL_A", addr);
                vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_MAP_RES_A_MAP_VAL_A(addr), buf);
            } else { // Resource B
                VTSS_SPRINTF(buf, " MAP_RES_B[%u]:MAP_VAL_B", addr);
                vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_MAP_RES_B_MAP_VAL_B(addr), buf);
            }
        }
    }
}

static void jr2_debug_qos_mapping(vtss_state_t              *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info,
                                  const vtss_qos_map_adm_t  *const m)
{
    u32 i, res;

    for (res = 0; res < VTSS_QOS_MAP_RESOURCES; res++) {
        char buf[64];
        if (m->ix[res].entry == NULL) {
            continue; /* Resource not present */
        }
        VTSS_SPRINTF(buf, "QoS %s Mapping Tables Res %u", m->name, res);
        vtss_debug_print_header(pr, buf);
        if (info->full) {
            if (m->kind == VTSS_QOS_MAP_KIND_INGRESS) {
                for (i = 0; i < VTSS_QOS_INGRESS_MAP_ROWS; i++) {
                    jr2_debug_qos_ingress_mapping(vtss_state, pr, i, 1);
                }
            } else {
                for (i = 0; i < VTSS_QOS_EGRESS_MAP_ROWS; i++) {
                    jr2_debug_qos_egress_mapping(vtss_state, pr, res, i, 1);
                }
            }
        } else {
            int  len;
            BOOL empty = TRUE;

            i = 0;
            while (i < m->ix[res].free) {
                len = m->key2len(m->ix[res].entry[i].key);
                if (m->ix[res].entry[i].id != VTSS_QOS_MAP_ID_NONE) {
                    if (m->kind == VTSS_QOS_MAP_KIND_INGRESS) {
                        jr2_debug_qos_ingress_mapping(vtss_state, pr, i, len);
                    } else {
                        jr2_debug_qos_egress_mapping(vtss_state, pr, res, i, len);
                    }
                    empty = FALSE;
                }
                if (len) {
                    i += len;
                } else {
                    pr("Error: ix[%u].entry[%u].key %d gives zero length!\n", res, i, m->ix[res].entry[i].key);
                    break;
                }
            }
            if (empty) {
                pr("No entries allocated!\n");
            }
            pr("Use 'full' to see all entries!\n");
        }
        pr("\n");
    }
}

static vtss_rc jr2_debug_qos_leak_chain(vtss_state_t              *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const vtss_debug_info_t   *const info)
{
    u32                   layer, group, se, cnt, leak_cfg;
    u32                   sys_clk_per_100ps;
    vtss_qos_leak_layer_t *ll;
    vtss_qos_leak_group_t *lg;

    vtss_debug_print_header(pr, "QoS Leak List Config");

    JR2_RD(VTSS_HSCH_HSCH_MISC_SYS_CLK_PER, &sys_clk_per_100ps);
    pr("HSCH:HSCH_MISC:SYS_CLK_PER.SYS_CLK_PER_100PS: %u\n\n", sys_clk_per_100ps);

    pr("Layer Group Err MaxRate Res LeakTime MaxSes CurSes Frst Last Ses...\n");
    for (layer = 0; layer < VTSS_HSCH_LAYERS; layer++) {
        /* Select layer */
        JR2_WRM(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
                VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(layer),
                VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER);

        ll = &vtss_state->qos.leak_conf.layer[layer];
        if (ll->entry == NULL) {
            continue; // Skip unused layer
        }
        for (group = 0; group < VTSS_HSCH_LEAK_LISTS; group++) {
            JR2_RD(VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG(layer, group), &leak_cfg);
            lg = &ll->group[group];
            se = lg->head.next;
            pr("%5u %5u %2u %8u %3u %8u %6u %6u %4u %4u ",
               layer, group, VTSS_X_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_ERR(leak_cfg),
               lg->max_rate, lg->resolution, lg->leak_time, lg->max_ses, lg->cur_ses, lg->head.next, lg->head.prev);

            if (lg->head.enabled) {
                u32 val, hw_next;
                /* Check for consistency with leak first in hw */
                JR2_RD(VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG(layer, group), &val);
                hw_next = VTSS_X_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_FIRST(val);
                if (se != hw_next) {
                    pr("Error: se %u != first hw_next %u!\n", se, hw_next);
                }
                cnt = 0;
                while (1) {
                    cnt++;
                    if (se >= ll->entries) {
                        pr("Error: Se %u >= %u!\n", se, ll->entries);
                        break;
                    }
                    if (cnt > lg->max_ses) {
                        pr("Error: cnt %u > %u!\n", cnt, lg->max_ses);
                        break;
                    }
                    pr("%u<%u>%u ", ll->entry[se].prev, se, ll->entry[se].next);
                    /* Check for consistency with leak chain in hw */
                    if (layer == 3) { /* Queue shapers */
                        JR2_RD(VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_CONNECT(se), &val);
                        hw_next = VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_CONNECT_SE_LEAK_LINK(val);
                    } else {
                        JR2_RD(VTSS_HSCH_HSCH_CFG_SE_CONNECT(se), &val);
                        hw_next = VTSS_X_HSCH_HSCH_CFG_SE_CONNECT_SE_LEAK_LINK(val);
                    }
                    if (ll->entry[se].next != hw_next) {
                        pr("Error: ll->entry[se].next %u != hw_next %u!\n", se, hw_next);
                    }

                    if (se == ll->entry[se].next) { /* End of list? */
                        if (cnt != lg->cur_ses) {
                            pr("Error: cnt %u != cur_ses %u!\n", cnt, lg->cur_ses);
                        }
                        break;
                    } else {
                        se = ll->entry[se].next;
                    }
                }
            }
            pr("\n");
        }
        pr("\n");
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_qos_status_get(vtss_state_t *vtss_state, vtss_qos_status_t *status)
{
    u32 value;

    /* Read and clear sticky register */
    JR2_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY, &value);
    JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY, value &
           VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY);

    /* Detect storm events */
    status->storm = VTSS_BOOL(value & VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY);

    return VTSS_RC_OK;
}


static vtss_rc jr2_debug_qos(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    u32            i, port, value, pol_idx, se, layer;
    int            queue;
    vtss_port_no_t port_no;
    char           buf[64];
    BOOL           clm, show;

    clm = show = FALSE;

    /* Global configuration starts here */

    if (info->has_action) { /* Action parameter is present */
        show = (info->action == 0) ? TRUE : FALSE;
        clm = (info->action == 1) ? TRUE : FALSE;
    }

    VTSS_D("has_action %u  show %u  clm %u", info->has_action, show, clm);

    if (show) {
        pr("OAM Debug Group action:\n");
        pr("    0: Show possible actions\n");
        pr("    1: Print CLM configurations\n");
        pr("\n");
    }

    if (!info->has_action) {
    pr("QoS WRED Config has been moved to 'debug api cil wm'\n\n");

    jr2_debug_qos_leak_chain(vtss_state, pr, info);

    jr2_debug_qos_mapping(vtss_state, pr, info, &vtss_state->qos.imap);
    jr2_debug_qos_mapping(vtss_state, pr, info, &vtss_state->qos.emap);

    vtss_debug_print_header(pr, "QoS DSCP Config");

    pr("DSCP Trans CLS DPL Rewr Trust Remap\n");
    for (i = 0; i < 64; i++) {
        u32 dscp_cfg, dscp_remap;
        JR2_RD(VTSS_ANA_CL_COMMON_DSCP_CFG(i), &dscp_cfg);
        JR2_RD(VTSS_REW_COMMON_DSCP_REMAP(i), &dscp_remap);
        pr("%4u %5u %3u %3u %4u %5u %5u\n",
           i,
           VTSS_X_ANA_CL_COMMON_DSCP_CFG_DSCP_TRANSLATE_VAL(dscp_cfg),
           VTSS_X_ANA_CL_COMMON_DSCP_CFG_DSCP_QOS_VAL(dscp_cfg),
           VTSS_X_ANA_CL_COMMON_DSCP_CFG_DSCP_DP_VAL(dscp_cfg),
           VTSS_X_ANA_CL_COMMON_DSCP_CFG_DSCP_REWR_ENA(dscp_cfg),
           VTSS_X_ANA_CL_COMMON_DSCP_CFG_DSCP_TRUST_ENA(dscp_cfg),
           VTSS_X_REW_COMMON_DSCP_REMAP_DSCP_REMAP(dscp_remap));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS DSCP Classification from QoS Config");

    pr("QoS DSCP_DP0 DSCP_DP1 DSCP_DP2 DSCP_DP3\n");
    for (i = 0; i < 8; i++) {
        u32 qos_dp0, qos_dp1, qos_dp2, qos_dp3;
        JR2_RD(VTSS_ANA_CL_COMMON_QOS_MAP_CFG(i),      &qos_dp0);
        JR2_RD(VTSS_ANA_CL_COMMON_QOS_MAP_CFG(i +  8), &qos_dp1);
        JR2_RD(VTSS_ANA_CL_COMMON_QOS_MAP_CFG(i + 16), &qos_dp2);
        JR2_RD(VTSS_ANA_CL_COMMON_QOS_MAP_CFG(i + 24), &qos_dp3);
        pr("%3u %4u     %4u     %4u     %4u\n",
           i,
           VTSS_X_ANA_CL_COMMON_QOS_MAP_CFG_DSCP_REWR_VAL(qos_dp0),
           VTSS_X_ANA_CL_COMMON_QOS_MAP_CFG_DSCP_REWR_VAL(qos_dp1),
           VTSS_X_ANA_CL_COMMON_QOS_MAP_CFG_DSCP_REWR_VAL(qos_dp2),
           VTSS_X_ANA_CL_COMMON_QOS_MAP_CFG_DSCP_REWR_VAL(qos_dp3));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Storm Policers");
    vtss_jr2_debug_reg_header(pr, "Storm Policers");
    for (i = 0; i < 8; i++) {
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG(i) ,  i, "POL_STORM_RATE_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG(i) , i, "POL_STORM_THRES_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL(i) ,      i, "POL_STORM_CTRL");
    }
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG, "POL_ALL_CFG");
    pr("\n");

    /* Per port configuration starts here */

    vtss_debug_print_header(pr, "QoS Port Classification Config");

    pr("LP CP PCP CLS DEI DPL TC_CLS TC_DPL DC_CLS DC_DPL W_GRP\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 vlan, qos, wred_group;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        JR2_RD(VTSS_ANA_CL_PORT_VLAN_CTRL(port), &vlan);
        JR2_RD(VTSS_ANA_CL_PORT_QOS_CFG(port), &qos);
        JR2_RD(VTSS_QRES_RES_QOS_ADV_WRED_GROUP(port), &wred_group);
        pr("%2u %2u %3u %3u %3u %3u %6u %6u %6u %6u %5u\n",
           port_no, // Logical port
           port,    // Chip port
           VTSS_X_ANA_CL_PORT_VLAN_CTRL_PORT_PCP(vlan),
           VTSS_X_ANA_CL_PORT_QOS_CFG_DEFAULT_QOS_VAL(qos),
           VTSS_X_ANA_CL_PORT_VLAN_CTRL_PORT_DEI(vlan),
           VTSS_X_ANA_CL_PORT_QOS_CFG_DEFAULT_DP_VAL(qos),
           VTSS_X_ANA_CL_PORT_QOS_CFG_PCP_DEI_QOS_ENA(qos),
           VTSS_X_ANA_CL_PORT_QOS_CFG_PCP_DEI_DP_ENA(qos),
           VTSS_X_ANA_CL_PORT_QOS_CFG_DSCP_QOS_ENA(qos),
           VTSS_X_ANA_CL_PORT_QOS_CFG_DSCP_DP_ENA(qos),
           wred_group);
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
                JR2_RD(VTSS_ANA_CL_PORT_PCP_DEI_MAP_CFG(port, (8 * dei + pcp)), &value);
                class_ct += VTSS_SNPRINTF(class_buf + class_ct, sizeof(class_buf) - class_ct, "%s%u", delim,
                                     VTSS_X_ANA_CL_PORT_PCP_DEI_MAP_CFG_PCP_DEI_QOS_VAL(value));
                dpl_ct   += VTSS_SNPRINTF(dpl_buf   + dpl_ct,   sizeof(dpl_buf)   - dpl_ct,   "%s%u",  delim,
                                     VTSS_X_ANA_CL_PORT_PCP_DEI_MAP_CFG_PCP_DEI_DP_VAL(value));
            }
        }
        pr("%2u %2u %s %s\n", port_no, port, class_buf, dpl_buf);
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Tag Remarking Config");

    pr("LP CP MPCP MDEI PCP DEI\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 tag_ctrl, tag_default;
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        JR2_RD(VTSS_REW_PORT_TAG_CTRL(port), &tag_ctrl);
        JR2_RD(VTSS_REW_PORT_PORT_VLAN_CFG(port), &tag_default);
        pr("%2u %2u %4x %4x %3d %3d\n",
           port_no,
           port,
           VTSS_X_REW_PORT_TAG_CTRL_TAG_PCP_CFG(tag_ctrl),
           VTSS_X_REW_PORT_TAG_CTRL_TAG_DEI_CFG(tag_ctrl),
           VTSS_X_REW_PORT_PORT_VLAN_CFG_PORT_PCP(tag_default),
           VTSS_X_REW_PORT_PORT_VLAN_CFG_PORT_DEI(tag_default));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Tag Remarking Map");

    pr("LP CP PCP (2*QoS class+DPL)           DEI (2*QoS class+DPL)\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        int class, pcp_ct = 0, dei_ct = 0;
        u32 pcp_dp0, pcp_dp1, dei_dp0, dei_dp1;
        char pcp_buf[40], dei_buf[40];
        if (info->port_list[port_no] == 0) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        for (class = VTSS_QUEUE_START; class < VTSS_QUEUE_END; class++) {
            const char *delim = (class == VTSS_QUEUE_START) ? "" : ",";
            JR2_RD(VTSS_REW_PORT_PCP_MAP_DE0(port, class), &pcp_dp0);
            JR2_RD(VTSS_REW_PORT_PCP_MAP_DE1(port, class), &pcp_dp1);
            JR2_RD(VTSS_REW_PORT_DEI_MAP_DE0(port, class), &dei_dp0);
            JR2_RD(VTSS_REW_PORT_DEI_MAP_DE1(port, class), &dei_dp1);
            pcp_ct += VTSS_SNPRINTF(pcp_buf + pcp_ct, sizeof(pcp_buf) - pcp_ct, "%s%u,%u",
                               delim,
                               VTSS_X_REW_PORT_PCP_MAP_DE0_PCP_DE0(pcp_dp0),
                               VTSS_X_REW_PORT_PCP_MAP_DE1_PCP_DE1(pcp_dp1));
            dei_ct += VTSS_SNPRINTF(dei_buf + dei_ct, sizeof(dei_buf) - dei_ct, "%s%u,%u",
                               delim,
                               VTSS_X_REW_PORT_DEI_MAP_DE0_DEI_DE0(dei_dp0),
                               VTSS_X_REW_PORT_DEI_MAP_DE1_DEI_DE1(dei_dp1));
        }
        pr("%2u %2u %s %s\n", port_no, port, pcp_buf, dei_buf);
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port DSCP Remarking Config");

    pr("LP CP I_Mode Keep Trans Update Remap\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        u32 qos_cfg, dscp_map;
        if (info->port_list[port_no] == 0) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        JR2_RD(VTSS_ANA_CL_PORT_QOS_CFG(port), &qos_cfg);
        JR2_RD(VTSS_REW_PORT_DSCP_MAP(port), &dscp_map);
        pr("%2u %2u %6u %4u %5u %6u %5u\n",
           port_no,
           port,
           VTSS_X_ANA_CL_PORT_QOS_CFG_DSCP_REWR_MODE_SEL(qos_cfg),
           VTSS_X_ANA_CL_PORT_QOS_CFG_DSCP_KEEP_ENA(qos_cfg),
           VTSS_X_ANA_CL_PORT_QOS_CFG_DSCP_TRANSLATE_ENA(qos_cfg),
           VTSS_X_REW_PORT_DSCP_MAP_DSCP_UPDATE_ENA(dscp_map),
           VTSS_X_REW_PORT_DSCP_MAP_DSCP_REMAP_ENA(dscp_map));
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Policers");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        int policer;
        if (info->port_list[port_no] == 0) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_jr2_debug_reg_header(pr, buf);
        for (policer = 0; policer < VTSS_PORT_POLICERS; policer++) {
            pol_idx = ((VTSS_PORT_POLICERS * port) + policer);
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0(pol_idx) , pol_idx, "THRES_CFG_0");
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1(pol_idx) , pol_idx, "THRES_CFG_1");
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG(pol_idx) , pol_idx, "RATE_CFG");
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG(port, policer) , pol_idx, "POL_PORT_CFG");
        }
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP(port) , port, "GAP");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG(port) , port, "POL_PORT_FC_CFG");
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Queue Policers");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_jr2_debug_reg_header(pr, buf);
        for (queue = 0; queue < 8; queue++) {
            pol_idx = VTSS_QUEUE_POL_IDX(port, queue);
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_SDLB_MISC_CFG(pol_idx), pol_idx, "MISC_CFG");
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_SDLB_DLB_CFG(pol_idx), pol_idx, "DLB_CFG");
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_SDLB_LB_CFG(pol_idx, 0), pol_idx, "LB_CFG_0");
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_SDLB_LB_CFG(pol_idx, 1), pol_idx, "LB_CFG_1");
        }
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Hsch leak lists");
    vtss_jr2_debug_reg_header(pr, "Hsch leak lists");
#if defined(VTSS_ARCH_JAGUAR_2_C)
    for (i = 0; i <= 3; i++) {
        u32 leak_group;
        for (leak_group = 0; leak_group <= 3; leak_group++) {
            VTSS_SPRINTF(buf, "HSCH_TIMER_CFG_%u", i);
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_TIMER_CFG(i, leak_group), leak_group, buf);
            VTSS_SPRINTF(buf, "HSCH_LEAK_CFG_%u", i);
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG(i, leak_group), leak_group, buf);
        }
    }
#elif defined(VTSS_ARCH_SERVAL_T)
    for (i = 0; i <= 3; i++) {
        u32 leak_group;
        for (leak_group = 0; leak_group <= 3; leak_group++) {
            VTSS_SPRINTF(buf, "HSCH_LEAK_CFG_%u", i);
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG(i, leak_group), leak_group, buf);
        }
    }
#else
#error "Update this piece of code."
#endif
    pr("\n");

    vtss_debug_print_header(pr, "QoS Scheduler Config");

    pr("LP CP LA   SE WRR FRM_MODE C0 C1 C2 C3 C4 C5 C6 C7\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        layer = 1;

        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        se   = port;

        JR2_WRM(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
                VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(layer) |
                VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX(se),
                VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER |
                VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX);

        JR2_RD(VTSS_HSCH_HSCH_CFG_SE_CFG(se), &value);
        pr("%2u %2u %2u %4u %3u %8u",
           port_no, // Logical port
           port,    // Chip port
           layer,   // Layer
           se,      // Scheduler element
           VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT(value),
           VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_FRM_MODE(value));
        for (queue = 0; queue < 8; queue++) {
            JR2_RD(VTSS_HSCH_HSCH_DWRR_DWRR_ENTRY(queue), &value);
            pr(" %2u", VTSS_X_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_COST(value));
        }
        pr("\n");
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Port Shapers (Uses elements from layer 2 indexed by chip port)");
    /* Select layer 2 */
    layer = 2;
    JR2_WRM(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(layer),
            VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER);

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        jr2_debug_qos_scheduler_element(vtss_state, pr, buf, layer, port);
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS Queue Shapers (Uses elements from layer 0)");
    /* Select layer 0 */
    layer = 0;
    JR2_WRM(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(layer),
            VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER);

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);

        for (queue = 0; queue < 8; queue++) {
            se = JR2_HSCH_L0_SE(port, queue);
            VTSS_SPRINTF(buf, "Port %u (%u), queue %u", port, port_no, queue);
            jr2_debug_qos_scheduler_element(vtss_state, pr, buf, layer, se);
        }
    }
    pr("\n");

    vtss_debug_print_header(pr, "QoS CPU Shapers (Uses elements from layer 2 indexed by chip port)");
    for (i = 0; i < 2; i++) {
        port = (VTSS_CHIP_PORT_CPU_0 + i);
        VTSS_SPRINTF(buf, "CPU %u, CP %u", i, port);
        jr2_debug_qos_scheduler_element(vtss_state, pr, buf, 2, port);
        se = (JR2_L0_SE_CPU_0 + i);
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG(se), se, "HSCH_QSHP_ALLOC_CFG");
        JR2_WR(VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG,
               VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX(se));
        for (queue = 0; queue < 8; queue++) {
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_QSHP_CFG_QSHP_CIR_CFG(queue), queue, "HSCH_QSHP_CIR_CFG");
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_QSHP_CFG_QSHP_CFG(queue), queue, "HSCH_QSHP_CFG");
        }
        pr("\n");
    }

    /* Only show the hierarchy if HQoS is not present, otherwise use the HQoS debug cmd */
    vtss_debug_print_header(pr, "QoS Layer 0 + Layer 1 SEs");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0) {
            continue;
        }
        u32 l0_se, l1_se;
        port = VTSS_CHIP_PORT(port_no);
        for (queue = 0; queue < 8; queue++) {
            l0_se = JR2_HSCH_L0_SE(port, queue);
            VTSS_SPRINTF(buf, "Port %u (%u), queue %u", port, port_no, queue);
            vtss_jr2_debug_reg_header(pr, buf);
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_L0_CFG_HSCH_L0_CFG(l0_se), l0_se, "HSCH_L0_CFG_HSCH_L0_CFG");
        }
        l1_se = port;
        VTSS_SPRINTF(buf, "L1 Scheduling element %u", l1_se);
        vtss_jr2_debug_reg_header(pr, buf);
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_L1_CFG_HSCH_L1_CFG(l1_se), l1_se, "HSCH_L1_CFG_HSCH_L1_CFG");
    }
    pr("\n");
    }

    if (!info->has_action || clm) {
        vtss_debug_print_header(pr, "CLM_B Info:");
        VTSS_RC(vtss_jr2_debug_clm_b(vtss_state, pr, info));
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_qos_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_QOS, jr2_debug_qos, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */
static vtss_rc jr2_qos_init(vtss_state_t *vtss_state)
{
    vtss_policer_t     pol_conf;
    vtss_policer_ext_t pol_ext_conf;
    u32                port, i;

    /* Setup queue policer indexes */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        JR2_WRM(VTSS_ANA_L2_COMMON_PORT_DLB_CFG(port),
                VTSS_F_ANA_L2_COMMON_PORT_DLB_CFG_QUEUE_DLB_IDX(VTSS_QUEUE_POL_IDX(port, 0)),
                VTSS_M_ANA_L2_COMMON_PORT_DLB_CFG_QUEUE_DLB_IDX);
    }

    VTSS_MEMSET(&pol_conf, 0, sizeof(pol_conf));
    VTSS_MEMSET(&pol_ext_conf, 0, sizeof(pol_ext_conf));
    pol_conf.rate = VTSS_BITRATE_DISABLED;
    /* Disable port and queue policers */
    for (port = 0; port <= VTSS_CHIP_PORT_CPU_1; port++) {
        for (i = 0; i < 8; i++) {
            if (i < VTSS_PORT_POLICERS) {
                VTSS_RC(jr2_port_policer_set(vtss_state, port, i, &pol_conf, &pol_ext_conf));
            }
            VTSS_RC(jr2_queue_policer_set(vtss_state, port, i, &pol_conf));
        }
    }

    /* Queue mapping: We use the defaults for QFWD:QMAP */

    VTSS_RC(jr2_qos_leak_list_init(vtss_state));

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_qos_state_t   *state = &vtss_state->qos;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->conf_set = jr2_qos_conf_set;

        state->port_conf_set = vtss_cmn_qos_port_conf_set;
        state->port_conf_update = jr2_qos_port_conf_set;

        state->qce_add = vtss_cmn_qce_add;
        state->qce_del = vtss_cmn_qce_del;

        state->ingress_map_add         = jr2_qos_ingress_map_add;
        state->ingress_map_del         = jr2_qos_ingress_map_del;
        state->ingress_map_vcap_update = jr2_qos_ingress_map_vcap_update;
        state->ingress_map_hw_update   = jr2_qos_ingress_map_hw_update;
        state->ingress_map_hw_copy     = jr2_qos_ingress_map_hw_copy;

        state->egress_map_add          = jr2_qos_egress_map_add;
        state->egress_map_del          = jr2_qos_egress_map_del;
        state->egress_map_vcap_update  = jr2_qos_egress_map_vcap_update;
        state->egress_map_hw_update    = jr2_qos_egress_map_hw_update;
        state->egress_map_hw_copy      = jr2_qos_egress_map_hw_copy;

        state->cpu_port_shaper_set = jr2_qos_cpu_port_shaper_set;

        state->prio_count = JR2_PRIOS;

        state->status_get = jr2_qos_status_get;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(jr2_qos_init(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_JAGUAR_2 */
