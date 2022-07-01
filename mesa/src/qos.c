// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_api.h>
#include <mesa.h>

#if defined(VTSS_FEATURE_QOS)
static void mesa_conv_storm_policer_vtss_to_mesa(vtss_packet_rate_t rate,
                 mesa_bool_t frame_rate,
                 const vtss_storm_policer_mode_t *mode,
                 mesa_qos_storm_policer_conf_t *out)
{
    out->rate = rate;
    out->frame_rate = frame_rate;

    mesa_conv_vtss_storm_policer_mode_t_to_mesa_storm_policer_mode_t(mode, &out->mode);
}

static void mesa_conv_storm_policer_mesa_to_vtss(const mesa_qos_storm_policer_conf_t *in,
                 vtss_packet_rate_t *rate,
                 mesa_bool_t *frame_rate,
                 vtss_storm_policer_mode_t *mode)
{
    *rate = in->rate;
    *frame_rate = in->frame_rate;
    mesa_conv_mesa_storm_policer_mode_t_to_vtss_storm_policer_mode_t(&in->mode, mode);
}

// TODO, should this be a conv or a conv2
mesa_rc mesa_conv_vtss_qos_conf_t_to_mesa_qos_conf_t(const vtss_qos_conf_t *in, mesa_qos_conf_t *out)
{
    vtss_dscp_t dscp;

    for (dscp = 0; dscp < 64; dscp++) {
        out->dscp[dscp].trust = in->dscp_trust[dscp];
        out->dscp[dscp].prio = in->dscp_qos_class_map[dscp];
        out->dscp[dscp].dpl = in->dscp_dp_level_map[dscp];
        out->dscp[dscp].remark = in->dscp_remark[dscp];
        out->dscp[dscp].dscp = in->dscp_translate_map[dscp];
    }
    mesa_conv_storm_policer_vtss_to_mesa(in->policer_uc, in->policer_uc_frame_rate, &in->policer_uc_mode, &out->policer_uc);
    mesa_conv_storm_policer_vtss_to_mesa(in->policer_mc, in->policer_mc_frame_rate, &in->policer_mc_mode, &out->policer_mc);
    mesa_conv_storm_policer_vtss_to_mesa(in->policer_bc, in->policer_bc_frame_rate, &in->policer_bc_mode, &out->policer_bc);
    return VTSS_RC_OK;
}

// TODO, should this be a conv or a conv2
mesa_rc mesa_conv_mesa_qos_conf_t_to_vtss_qos_conf_t(const mesa_qos_conf_t *in, vtss_qos_conf_t *out)
{
    vtss_dscp_t dscp;

    for (dscp = 0; dscp < 64; dscp++) {
        out->dscp_trust[dscp] = in->dscp[dscp].trust;
        out->dscp_qos_class_map[dscp] = in->dscp[dscp].prio;
        out->dscp_dp_level_map[dscp] = in->dscp[dscp].dpl;
        out->dscp_remark[dscp] = in->dscp[dscp].remark;
        out->dscp_translate_map[dscp] = in->dscp[dscp].dscp;
    }
    mesa_conv_storm_policer_mesa_to_vtss(&in->policer_uc, &out->policer_uc, &out->policer_uc_frame_rate, &out->policer_uc_mode);
    mesa_conv_storm_policer_mesa_to_vtss(&in->policer_mc, &out->policer_mc, &out->policer_mc_frame_rate, &out->policer_mc_mode);
    mesa_conv_storm_policer_mesa_to_vtss(&in->policer_bc, &out->policer_bc, &out->policer_bc_frame_rate, &out->policer_bc_mode);
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_vtss_qos_port_conf_t_to_mesa_qos_port_conf_t(const vtss_qos_port_conf_t *in, mesa_qos_port_conf_t *out)
{
    vtss_pcp_t   pcp;
    vtss_dei_t   dei;
    vtss_queue_t queue;

    // Shaper
    mesa_conv_vtss_shaper_t_to_mesa_shaper_t(&in->shaper_port, &out->shaper);

    // Tag
    out->tag.pcp = in->usr_prio;
    out->tag.dei = in->default_dei;
    out->tag.class_enable = in->tag_class_enable;
    for (pcp = 0; pcp < VTSS_PCPS; pcp++) {
        for (dei = 0; dei < VTSS_DEIS; dei++) {
            out->tag.pcp_dei_map[pcp][dei].prio = in->qos_class_map[pcp][dei];
            out->tag.pcp_dei_map[pcp][dei].dpl = in->dp_level_map[pcp][dei];
        }
    }
    mesa_conv_vtss_tag_remark_mode_t_to_mesa_tag_remark_mode_t(&in->tag_remark_mode, &out->tag.remark_mode);
    out->tag.egress_pcp = in->tag_default_pcp;
    out->tag.egress_dei = in->tag_default_dei;

    // DSCP
    out->dscp.class_enable = in->dscp_class_enable;
    mesa_conv_vtss_dscp_mode_t_to_mesa_dscp_mode_t(&in->dscp_mode, &out->dscp.mode);
    mesa_conv_vtss_dscp_emode_t_to_mesa_dscp_emode_t(&in->dscp_emode, &out->dscp.emode);
    out->dscp.translate = in->dscp_translate;

    // Queue
    for (queue = 0; queue < VTSS_QUEUES; queue++) {
        mesa_conv_vtss_policer_t_to_mesa_policer_t(&in->policer_queue[queue], &out->queue[queue].policer);
        mesa_conv_vtss_shaper_t_to_mesa_shaper_t(&in->shaper_queue[queue], &out->queue[queue].shaper);
        out->queue[queue].pct = in->queue_pct[queue];
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB)
        out->queue[queue].excess_enable = in->excess_enable[queue];
#endif
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
        out->queue[queue].cut_through_enable = in->cut_through_enable[queue];
#endif
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_qos_port_conf_t_to_vtss_qos_port_conf_t(const mesa_qos_port_conf_t *in, vtss_qos_port_conf_t *out)
{
    vtss_pcp_t   pcp;
    vtss_dei_t   dei;
    vtss_queue_t queue;

    // Shaper
    mesa_conv_mesa_shaper_t_to_vtss_shaper_t(&in->shaper, &out->shaper_port);

    // Tag
    out->usr_prio = in->tag.pcp;
    out->default_dei = in->tag.dei;
    out->tag_class_enable = in->tag.class_enable;
    for (pcp = 0; pcp < VTSS_PCPS; pcp++) {
        for (dei = 0; dei < VTSS_DEIS; dei++) {
            out->qos_class_map[pcp][dei] = in->tag.pcp_dei_map[pcp][dei].prio;
            out->dp_level_map[pcp][dei] = in->tag.pcp_dei_map[pcp][dei].dpl;
        }
    }
    mesa_conv_mesa_tag_remark_mode_t_to_vtss_tag_remark_mode_t(&in->tag.remark_mode, &out->tag_remark_mode);
    out->tag_default_pcp = in->tag.egress_pcp;
    out->tag_default_dei = in->tag.egress_dei;

    // DSCP
    out->dscp_class_enable = in->dscp.class_enable;
    mesa_conv_mesa_dscp_mode_t_to_vtss_dscp_mode_t(&in->dscp.mode, &out->dscp_mode);
    mesa_conv_mesa_dscp_emode_t_to_vtss_dscp_emode_t(&in->dscp.emode, &out->dscp_emode);
    out->dscp_translate = in->dscp.translate;

    // Queue
    for (queue = 0; queue < VTSS_QUEUES; queue++) {
        mesa_conv_mesa_policer_t_to_vtss_policer_t(&in->queue[queue].policer, &out->policer_queue[queue]);
        mesa_conv_mesa_shaper_t_to_vtss_shaper_t(&in->queue[queue].shaper, &out->shaper_queue[queue]);
        out->queue_pct[queue] = in->queue[queue].pct;
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB)
        out->excess_enable[queue] = in->queue[queue].excess_enable;
#endif
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
        out->cut_through_enable[queue] = in->queue[queue].cut_through_enable;
#endif
    }

    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_QOS

#if defined(VTSS_FEATURE_QCL)
mesa_rc mesa_conv2_vtss_qce_key_t_to_mesa_qce_key_t(const vtss_qce_key_t *in, mesa_qce_key_t *out)
{
    switch (in->type) {
    case VTSS_QCE_TYPE_ANY:
        break;
    case VTSS_QCE_TYPE_ETYPE:
        mesa_conv_vtss_qce_frame_etype_t_to_mesa_qce_frame_etype_t(&in->frame.etype, &out->frame.etype);
        break;
    case VTSS_QCE_TYPE_LLC:
        mesa_conv_vtss_qce_frame_llc_t_to_mesa_qce_frame_llc_t(&in->frame.llc, &out->frame.llc);
        break;
    case VTSS_QCE_TYPE_SNAP:
        mesa_conv_vtss_qce_frame_snap_t_to_mesa_qce_frame_snap_t(&in->frame.snap, &out->frame.snap);
        break;
    case VTSS_QCE_TYPE_IPV4:
        mesa_conv_vtss_qce_frame_ipv4_t_to_mesa_qce_frame_ipv4_t(&in->frame.ipv4, &out->frame.ipv4);
        break;
    case VTSS_QCE_TYPE_IPV6:
        mesa_conv_vtss_qce_frame_ipv6_t_to_mesa_qce_frame_ipv6_t(&in->frame.ipv6, &out->frame.ipv6);
        break;
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_qce_key_t_to_vtss_qce_key_t(const mesa_qce_key_t *in, vtss_qce_key_t *out)
{
    switch (in->type) {
    case MESA_QCE_TYPE_ANY:
        break;
    case MESA_QCE_TYPE_ETYPE:
        mesa_conv_mesa_qce_frame_etype_t_to_vtss_qce_frame_etype_t(&in->frame.etype, &out->frame.etype);
        break;
    case MESA_QCE_TYPE_LLC:
        mesa_conv_mesa_qce_frame_llc_t_to_vtss_qce_frame_llc_t(&in->frame.llc, &out->frame.llc);
        break;
    case MESA_QCE_TYPE_SNAP:
        mesa_conv_mesa_qce_frame_snap_t_to_vtss_qce_frame_snap_t(&in->frame.snap, &out->frame.snap);
        break;
    case MESA_QCE_TYPE_IPV4:
        mesa_conv_mesa_qce_frame_ipv4_t_to_vtss_qce_frame_ipv4_t(&in->frame.ipv4, &out->frame.ipv4);
        break;
    case MESA_QCE_TYPE_IPV6:
        mesa_conv_mesa_qce_frame_ipv6_t_to_vtss_qce_frame_ipv6_t(&in->frame.ipv6, &out->frame.ipv6);
        break;
    }
    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_QCL

#define VTSS_RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }

// Array with index [x,y]
#define MESA_IDX_2_BASE(x, y_cnt)           (x * y_cnt)
#define MESA_IDX_2(x, y, y_cnt)             (MESA_IDX_2_BASE(x, y_cnt) + y)

// Array with index [x,y,z]
#define MESA_IDX_3_BASE(x, y, y_cnt, z_cnt) (MESA_IDX_2(x, y, y_cnt) * z_cnt)
#define MESA_IDX_3(x, y, z, y_cnt, z_cnt)   (MESA_IDX_3_BASE(x, y, y_cnt, z_cnt) + z)

mesa_rc mesa_qos_dscp_dpl_conf_get(const mesa_inst_t        inst,
                                   const uint32_t           dpl_cnt,
                                   mesa_qos_dscp_dpl_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS)
    vtss_qos_conf_t vtss_conf;
    vtss_dscp_t     dscp;
    u32             idx;

    if (dpl_cnt != VTSS_DPLS) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_conf_get((const vtss_inst_t)inst, &vtss_conf));
    for (dscp = 0; dscp < 64; dscp++) {
        idx = MESA_IDX_2_BASE(dscp, VTSS_DPLS);
        conf[idx].dscp = vtss_conf.dscp_remap[dscp];
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
        conf[idx + 1].dscp = vtss_conf.dscp_remap_dp1[dscp];
#endif
    }
    return VTSS_RC_OK;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qos_dscp_dpl_conf_set(const mesa_inst_t              inst,
                                   const uint32_t                 dpl_cnt,
                                   const mesa_qos_dscp_dpl_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS)
    vtss_qos_conf_t vtss_conf;
    vtss_dscp_t     dscp;
    u32             idx;

    if (dpl_cnt != VTSS_DPLS) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_conf_get((const vtss_inst_t)inst, &vtss_conf));
    for (dscp = 0; dscp < 64; dscp++) {
        idx = MESA_IDX_2_BASE(dscp, VTSS_DPLS);
        vtss_conf.dscp_remap[dscp] = conf[idx].dscp;
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
        vtss_conf.dscp_remap_dp1[dscp] = conf[idx + 1].dscp;
#endif
    }
    return vtss_qos_conf_set((const vtss_inst_t)inst, &vtss_conf);
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qos_dpl_conf_get(const mesa_inst_t   inst,
                              const uint32_t      dpl_cnt,
                              mesa_qos_dpl_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS)
    vtss_qos_conf_t vtss_conf;
    vtss_prio_t     prio;

    if (dpl_cnt != VTSS_DPLS) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_conf_get((const vtss_inst_t)inst, &vtss_conf));
    for (prio = 0; prio < VTSS_PRIOS; prio++) {
        conf[0].dscp[prio] = vtss_conf.dscp_qos_map[prio];
        conf[1].dscp[prio] = vtss_conf.dscp_qos_map_dp1[prio];
#if (VTSS_DPLS == 4)
        conf[2].dscp[prio] = vtss_conf.dscp_qos_map_dp2[prio];
        conf[3].dscp[prio] = vtss_conf.dscp_qos_map_dp3[prio];
#endif
    }
    return VTSS_RC_OK;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qos_dpl_conf_set(const mesa_inst_t         inst,
                              const uint32_t            dpl_cnt,
                              const mesa_qos_dpl_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS)
    vtss_qos_conf_t vtss_conf;
    vtss_prio_t     prio;

    if (dpl_cnt != VTSS_DPLS) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_conf_get((const vtss_inst_t)inst, &vtss_conf));
    for (prio = 0; prio < VTSS_PRIOS; prio++) {
        vtss_conf.dscp_qos_map[prio] = conf[0].dscp[prio];
        vtss_conf.dscp_qos_map_dp1[prio] = conf[1].dscp[prio];
#if (VTSS_DPLS == 4)
        vtss_conf.dscp_qos_map_dp2[prio] = conf[2].dscp[prio];
        vtss_conf.dscp_qos_map_dp3[prio] = conf[3].dscp[prio];
#endif
    }
    return vtss_qos_conf_set((const vtss_inst_t)inst, &vtss_conf);
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qos_dpl_group_conf_get(const mesa_inst_t         inst,
                                    const uint32_t            dpl_cnt,
                                    const uint32_t            group_cnt,
                                    mesa_qos_dpl_group_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS_WRED_V2) || defined(VTSS_FEATURE_QOS_WRED_V3)
    vtss_qos_conf_t  vtss_conf;
    vtss_queue_t     queue;
    vtss_dpl_t       dpl;
    u32              idx, grp;
    vtss_red_v2_t    *vtss_wred;
    mesa_wred_conf_t *wred;

    if (dpl_cnt != VTSS_DPLS || group_cnt != mesa_capability(inst, MESA_CAP_QOS_WRED_GROUP_CNT)) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_conf_get((const vtss_inst_t)inst, &vtss_conf));
    for (queue = 0; queue < VTSS_QUEUES; queue++) {
        for (dpl = 1; dpl < VTSS_DPLS; dpl++) {
            // DPL zero is not used
            for (grp = 0; grp < group_cnt; grp++) {
#if defined(VTSS_FEATURE_QOS_WRED_V2)
                vtss_wred = &vtss_conf.red_v2[queue][dpl]; // dpl 0 (green frames) is not used
#else
                vtss_wred = &vtss_conf.red_v3[queue][dpl - 1][grp];
#endif
                idx = MESA_IDX_2(dpl, grp, group_cnt);
                wred = &conf[idx].wred[queue];
                wred->enable = vtss_wred->enable;
                wred->min_fl = vtss_wred->min_fl;
                wred->max = vtss_wred->max;
                wred->max_unit = (mesa_wred_max_t)vtss_wred->max_unit;
            }
        }
    }
#endif
    return VTSS_RC_OK;
}

mesa_rc mesa_qos_dpl_group_conf_set(const mesa_inst_t               inst,
                                    const uint32_t                  dpl_cnt,
                                    const uint32_t                  group_cnt,
                                    const mesa_qos_dpl_group_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS_WRED_V2) || defined(VTSS_FEATURE_QOS_WRED_V3)
    vtss_qos_conf_t        vtss_conf;
    vtss_queue_t           queue;
    vtss_dpl_t             dpl;
    u32                    idx, grp;
    vtss_red_v2_t          *vtss_wred;
    const mesa_wred_conf_t *wred;

    if (dpl_cnt != VTSS_DPLS || group_cnt != mesa_capability(inst, MESA_CAP_QOS_WRED_GROUP_CNT)) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_conf_get((const vtss_inst_t)inst, &vtss_conf));
    for (queue = 0; queue < VTSS_QUEUES; queue++) {
        for (dpl = 1; dpl < VTSS_DPLS; dpl++) {
            // DPL zero is not used
            for (grp = 0; grp < group_cnt; grp++) {
#if defined(VTSS_FEATURE_QOS_WRED_V2)
                vtss_wred = &vtss_conf.red_v2[queue][dpl]; // dpl 0 (green frames) is not used
#else
                vtss_wred = &vtss_conf.red_v3[queue][dpl - 1][grp];
#endif
                idx = MESA_IDX_2(dpl, grp, group_cnt);
                wred = &conf[idx].wred[queue];
                vtss_wred->enable = wred->enable;
                vtss_wred->min_fl = wred->min_fl;
                vtss_wred->max = wred->max;
                vtss_wred->max_unit = (vtss_wred_v2_max_t)wred->max_unit;
            }
        }
    }
    return vtss_qos_conf_set((const vtss_inst_t)inst, &vtss_conf);
#else
    return VTSS_RC_OK;
#endif
}

mesa_rc mesa_qos_port_policer_conf_get(const mesa_inst_t            inst,
                                       const mesa_port_no_t         port_no,
                                       const uint32_t               cnt,
                                       mesa_qos_port_policer_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS)
    vtss_qos_port_conf_t         vtss_conf;
    mesa_qos_port_policer_conf_t *pol;
    vtss_policer_ext_t           *pol_ext;
    u32                          idx;

    if (cnt != VTSS_PORT_POLICERS) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_port_conf_get((const vtss_inst_t)inst, port_no, &vtss_conf));
    for (idx = 0; idx < VTSS_PORT_POLICERS; idx++) {
        pol = &conf[idx];
        mesa_conv_vtss_policer_t_to_mesa_policer_t(&vtss_conf.policer_port[idx], &pol->policer);
        pol_ext = &vtss_conf.policer_ext_port[idx];
        pol->frame_rate = pol_ext->frame_rate;
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL)
        pol->dp_bypass_level = pol_ext->dp_bypass_level;
#endif
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2)
        pol->known_unicast = pol_ext->known_unicast;
        pol->known_multicast = pol_ext->known_multicast;
        pol->known_broadcast = pol_ext->known_broadcast;
        pol->unknown_unicast = pol_ext->unknown_unicast;
        pol->unknown_multicast = pol_ext->unknown_multicast;
        pol->unknown_broadcast = pol_ext->unknown_broadcast;
        pol->learning = pol_ext->learning;
        pol->limit_noncpu_traffic = pol_ext->limit_noncpu_traffic;
        pol->limit_cpu_traffic = pol_ext->limit_cpu_traffic;
#endif
        pol->flow_control = pol_ext->flow_control;
    }
    return VTSS_RC_OK;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qos_port_policer_conf_set(const mesa_inst_t                  inst,
                                       const mesa_port_no_t               port_no,
                                       const uint32_t                     cnt,
                                       const mesa_qos_port_policer_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS)
    vtss_qos_port_conf_t               vtss_conf;
    const mesa_qos_port_policer_conf_t *pol;
    vtss_policer_ext_t                 *pol_ext;
    u32                                idx;

    if (cnt != VTSS_PORT_POLICERS) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_port_conf_get((const vtss_inst_t)inst, port_no, &vtss_conf));
    for (idx = 0; idx < VTSS_PORT_POLICERS; idx++) {
        pol = &conf[idx];
        mesa_conv_mesa_policer_t_to_vtss_policer_t(&pol->policer, &vtss_conf.policer_port[idx]);
        pol_ext = &vtss_conf.policer_ext_port[idx];
        pol_ext->frame_rate = pol->frame_rate;
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL)
        pol_ext->dp_bypass_level = pol->dp_bypass_level;
#endif
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2)
        pol_ext->known_unicast = pol->known_unicast;
        pol_ext->known_multicast = pol->known_multicast;
        pol_ext->known_broadcast = pol->known_broadcast;
        pol_ext->unknown_unicast = pol->unknown_unicast;
        pol_ext->unknown_multicast = pol->unknown_multicast;
        pol_ext->unknown_broadcast = pol->unknown_broadcast;
        pol_ext->learning = pol->learning;
        pol_ext->limit_noncpu_traffic = pol->limit_noncpu_traffic;
        pol_ext->limit_cpu_traffic = pol->limit_cpu_traffic;
#endif
        pol_ext->flow_control = pol->flow_control;
    }
    return vtss_qos_port_conf_set((const vtss_inst_t)inst, port_no, &vtss_conf);
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qos_port_dpl_conf_get(const mesa_inst_t        inst,
                                   const mesa_port_no_t     port_no,
                                   const uint32_t           dpl_cnt,
                                   mesa_qos_port_dpl_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS)
    vtss_qos_port_conf_t vtss_conf;
    vtss_prio_t          prio;
    vtss_dpl_t           dpl;

    if (dpl_cnt != VTSS_DPLS) {
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_qos_port_conf_get((const vtss_inst_t)inst, port_no, &vtss_conf));
    for (prio = 0; prio < VTSS_PRIOS; prio++) {
        for (dpl = 0; dpl < 2; dpl++) {
            conf[dpl].pcp[prio] = vtss_conf.tag_pcp_map[prio][dpl];
            conf[dpl].dei[prio] = vtss_conf.tag_dei_map[prio][dpl];
        }
    }
    return VTSS_RC_OK;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qos_port_dpl_conf_set(const mesa_inst_t              inst,
                                   const mesa_port_no_t           port_no,
                                   const uint32_t                 dpl_cnt,
                                   const mesa_qos_port_dpl_conf_t *const conf)
{
#if defined(VTSS_FEATURE_QOS)
    vtss_qos_port_conf_t vtss_conf;
    vtss_prio_t          prio;
    vtss_dpl_t           dpl;

    if (dpl_cnt != VTSS_DPLS) {
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_qos_port_conf_get((const vtss_inst_t)inst, port_no, &vtss_conf));
    for (prio = 0; prio < VTSS_PRIOS; prio++) {
        for (dpl = 0; dpl < 2; dpl++) {
            vtss_conf.tag_pcp_map[prio][dpl] = conf[dpl].pcp[prio];
            vtss_conf.tag_dei_map[prio][dpl] = conf[dpl].dei[prio];
        }
    }
    return vtss_qos_port_conf_set((const vtss_inst_t)inst, port_no, &vtss_conf);
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qos_tas_port_gcl_conf_get(const mesa_inst_t     inst,
                                       const mesa_port_no_t  port_no,
                                       const uint32_t        cnt,
                                       mesa_qos_tas_gce_t    *const gcl,
                                       uint32_t              *const gce_cnt)
{
#if defined(VTSS_FEATURE_QOS_TAS)
    vtss_qos_tas_port_conf_t vtss_conf;
    u32                      idx;

    if ((gce_cnt == NULL) || (gcl == NULL)) {
        return VTSS_RC_ERROR;
    }
    if (cnt != VTSS_QOS_TAS_GCL_LEN_MAX) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_tas_port_conf_get((const vtss_inst_t)inst, port_no, &vtss_conf));
    for (idx = 0; (idx < VTSS_QOS_TAS_GCL_LEN_MAX) && (idx < vtss_conf.gcl_length); idx++) {
        mesa_conv_vtss_qos_tas_gce_t_to_mesa_qos_tas_gce_t(&vtss_conf.gcl[idx], &gcl[idx]);
    }
    *gce_cnt = vtss_conf.gcl_length;
    return VTSS_RC_OK;
#else
    return VTSS_RC_ERROR;
#endif /* defined(VTSS_FEATURE_QOS_TAS) */
}

mesa_rc mesa_qos_tas_port_gcl_conf_set(const mesa_inst_t          inst,
                                       const mesa_port_no_t       port_no,
                                       const uint32_t             gce_cnt,
                                       const mesa_qos_tas_gce_t   *const gcl)
{
#if defined(VTSS_FEATURE_QOS_TAS)
    vtss_qos_tas_port_conf_t vtss_conf;
    u32                      idx;

    if (gcl == NULL) {
        return VTSS_RC_ERROR;
    }
    if (gce_cnt > VTSS_QOS_TAS_GCL_LEN_MAX) {
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_qos_tas_port_conf_get((const vtss_inst_t)inst, port_no, &vtss_conf));
    for (idx = 0; idx < gce_cnt; idx++) {
        mesa_conv_mesa_qos_tas_gce_t_to_vtss_qos_tas_gce_t(&gcl[idx], &vtss_conf.gcl[idx]);
    }
    vtss_conf.gcl_length = gce_cnt;
    vtss_conf.config_change = FALSE;
    return vtss_qos_tas_port_conf_set((const vtss_inst_t)inst, port_no, &vtss_conf);
#else
    return VTSS_RC_ERROR;
#endif /* defined(VTSS_FEATURE_QOS_TAS) */
}

mesa_rc mesa_qce_add(const mesa_inst_t   inst,
                     const mesa_qce_id_t qce_id,
                     const mesa_qce_t    *const qce)
{
#if defined(VTSS_FEATURE_QCL)
    vtss_qce_t vtss_qce;

    mesa_conv_mesa_qce_t_to_vtss_qce_t(qce, &vtss_qce);
    return vtss_qce_add((vtss_inst_t)inst, VTSS_QCL_ID_START, qce_id, &vtss_qce);
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_qce_del(const mesa_inst_t   inst,
                     const mesa_qce_id_t qce_id)
{
#if defined(VTSS_FEATURE_QCL)
    return vtss_qce_del((vtss_inst_t)inst, VTSS_QCL_ID_START, qce_id);
#else
    return VTSS_RC_ERROR;
#endif
}

