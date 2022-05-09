// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_api.h>
#include <mesa.h>

mesa_rc mesa_conv_uint8_t_to_mesa_port_list_t(const mesa_bool_t in[VTSS_PORT_ARRAY_SIZE], mesa_port_list_t *out)
{
    vtss_port_no_t port_no;

    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        mesa_port_list_set(out, port_no, in[port_no]);
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_port_list_t_to_uint8_t(const mesa_port_list_t *in, mesa_bool_t out[VTSS_PORT_ARRAY_SIZE])
{
    vtss_port_no_t port_no;

    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        out[port_no] = mesa_port_list_get(in, port_no);
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_VCAP)
#define VTSS_BF_GET(a, n)    ((a[(n)/8] & (1<<((n)%8))) ? 1 : 0)
#define VTSS_BF_SET(a, n, v) do { if (v) { a[(n)/8] |= (1U<<((n)%8)); } else { a[(n)/8] &= ~(1U<<((n)%8)); }} while (0)

mesa_rc mesa_conv2_vtss_vlan_trans_port2grp_conf_t_to_mesa_vlan_trans_port2grp_conf_t(const vtss_vlan_trans_port2grp_conf_t *in, mesa_vlan_trans_port2grp_conf_t *out)
{
    vtss_port_no_t port_no;
    mesa_bool_t    member[VTSS_PORT_ARRAY_SIZE];

    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        member[port_no] = VTSS_BF_GET(in->ports, port_no);
    }

    return mesa_conv_uint8_t_to_mesa_port_list_t(member, &out->port_list);
}

mesa_rc mesa_conv2_mesa_vlan_trans_port2grp_conf_t_to_vtss_vlan_trans_port2grp_conf_t(const mesa_vlan_trans_port2grp_conf_t *in, vtss_vlan_trans_port2grp_conf_t *out)
{
    mesa_rc        rc;
    vtss_port_no_t port_no;
    mesa_bool_t    member[VTSS_PORT_ARRAY_SIZE];

    if ((rc = mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, member)) == VTSS_RC_OK) {
        for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
            VTSS_BF_SET(out->ports, port_no, member[port_no]);
        }
    }
    return rc;
}

mesa_rc mesa_conv2_vtss_vce_key_t_to_mesa_vce_key_t(const vtss_vce_key_t *in, mesa_vce_key_t *out)
{
    switch (in->type) {
    case VTSS_VCE_TYPE_ANY:
        break;
    case VTSS_VCE_TYPE_ETYPE:
        mesa_conv_vtss_vce_frame_etype_t_to_mesa_vce_frame_etype_t(&in->frame.etype, &out->frame.etype);
        break;
    case VTSS_VCE_TYPE_LLC:
        mesa_conv_vtss_vce_frame_llc_t_to_mesa_vce_frame_llc_t(&in->frame.llc, &out->frame.llc);
        break;
    case VTSS_VCE_TYPE_SNAP:
        mesa_conv_vtss_vce_frame_snap_t_to_mesa_vce_frame_snap_t(&in->frame.snap, &out->frame.snap);
        break;
    case VTSS_VCE_TYPE_IPV4:
        mesa_conv_vtss_vce_frame_ipv4_t_to_mesa_vce_frame_ipv4_t(&in->frame.ipv4, &out->frame.ipv4);
        break;
    case VTSS_VCE_TYPE_IPV6:
        mesa_conv_vtss_vce_frame_ipv6_t_to_mesa_vce_frame_ipv6_t(&in->frame.ipv6, &out->frame.ipv6);
        break;
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_vce_key_t_to_vtss_vce_key_t(const mesa_vce_key_t *in, vtss_vce_key_t *out)
{
    switch (in->type) {
    case MESA_VCE_TYPE_ANY:
        break;
    case MESA_VCE_TYPE_ETYPE:
        mesa_conv_mesa_vce_frame_etype_t_to_vtss_vce_frame_etype_t(&in->frame.etype, &out->frame.etype);
        break;
    case MESA_VCE_TYPE_LLC:
        mesa_conv_mesa_vce_frame_llc_t_to_vtss_vce_frame_llc_t(&in->frame.llc, &out->frame.llc);
        break;
    case MESA_VCE_TYPE_SNAP:
        mesa_conv_mesa_vce_frame_snap_t_to_vtss_vce_frame_snap_t(&in->frame.snap, &out->frame.snap);
        break;
    case MESA_VCE_TYPE_IPV4:
        mesa_conv_mesa_vce_frame_ipv4_t_to_vtss_vce_frame_ipv4_t(&in->frame.ipv4, &out->frame.ipv4);
        break;
    case MESA_VCE_TYPE_IPV6:
        mesa_conv_mesa_vce_frame_ipv6_t_to_vtss_vce_frame_ipv6_t(&in->frame.ipv6, &out->frame.ipv6);
        break;
    }
    return VTSS_RC_OK;
}
#endif

mesa_rc mesa_vlan_tx_tag_get(const mesa_inst_t  inst,
                             const mesa_vid_t   vid,
                             const uint32_t     cnt,
                             mesa_vlan_tx_tag_t *const tx_tag)
{
#if defined(VTSS_FEATURE_VCAP)
    mesa_rc            rc;
    vtss_port_no_t     port_no;
    vtss_vlan_tx_tag_t tag[VTSS_PORT_ARRAY_SIZE];

    if (cnt > VTSS_PORTS) {
        return VTSS_RC_ERROR;
    }
    if ((rc = vtss_vlan_tx_tag_get((const vtss_inst_t)inst, vid, tag)) == VTSS_RC_OK) {
        for (port_no = 0; port_no < cnt; port_no++) {
            mesa_conv_vtss_vlan_tx_tag_t_to_mesa_vlan_tx_tag_t(&tag[port_no], &tx_tag[port_no]);
        }
    }
    return rc;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_vlan_tx_tag_set(const mesa_inst_t        inst,
                             const mesa_vid_t         vid,
                             const uint32_t           cnt,
                             const mesa_vlan_tx_tag_t *const tx_tag)
{
#if defined(VTSS_FEATURE_VCAP)
    vtss_port_no_t     port_no;
    vtss_vlan_tx_tag_t tag[VTSS_PORT_ARRAY_SIZE];

    if (cnt > VTSS_PORTS) {
        return VTSS_RC_ERROR;
    }
    for (port_no = 0; port_no < cnt; port_no++) {
        mesa_conv_mesa_vlan_tx_tag_t_to_vtss_vlan_tx_tag_t(&tx_tag[port_no], &tag[port_no]);
    }
    return vtss_vlan_tx_tag_set((const vtss_inst_t)inst, vid, tag);
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_vlan_trans_group_add(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const conf)
{
#if defined(VTSS_FEATURE_VCAP)
    vtss_vlan_trans_grp2vlan_conf_t vtss_conf;

    mesa_conv_mesa_vlan_trans_grp2vlan_conf_t_to_vtss_vlan_trans_grp2vlan_conf_t(conf, &vtss_conf);
    return vtss_vlan_trans_group_conf_add((const vtss_inst_t)inst, &vtss_conf);
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_vlan_trans_group_del(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const conf)
{
#if defined(VTSS_FEATURE_VCAP)
    vtss_vlan_trans_grp2vlan_conf_t vtss_conf;

    mesa_conv_mesa_vlan_trans_grp2vlan_conf_t_to_vtss_vlan_trans_grp2vlan_conf_t(conf, &vtss_conf);
    return vtss_vlan_trans_group_conf_del((const vtss_inst_t)inst, &vtss_conf);
#else
    return VTSS_RC_ERROR;
#endif
}

static mesa_rc mesa_vtr_grp_get(const mesa_inst_t                     inst,
                                const mesa_vlan_trans_grp2vlan_conf_t *const in,
                                mesa_vlan_trans_grp2vlan_conf_t       *conf,
                                BOOL next)
{
#if defined(VTSS_FEATURE_VCAP)
    mesa_rc                         rc;
    vtss_vlan_trans_grp2vlan_conf_t vtss_conf;

    mesa_conv_mesa_vlan_trans_grp2vlan_conf_t_to_vtss_vlan_trans_grp2vlan_conf_t(in, &vtss_conf);
    if ((rc = vtss_vlan_trans_group_get((const vtss_inst_t)inst, &vtss_conf, next)) == VTSS_RC_OK) {
        mesa_conv_vtss_vlan_trans_grp2vlan_conf_t_to_mesa_vlan_trans_grp2vlan_conf_t(&vtss_conf, conf);
    }
    return rc;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_vlan_trans_group_get(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const in,
                                  mesa_vlan_trans_grp2vlan_conf_t       *const conf)
{
    return mesa_vtr_grp_get(inst, in, conf, FALSE);
}

mesa_rc mesa_vlan_trans_group_get_next(const mesa_inst_t                     inst,
                                       const mesa_vlan_trans_grp2vlan_conf_t *const in,
                                       mesa_vlan_trans_grp2vlan_conf_t       *const conf)
{
    return mesa_vtr_grp_get(inst, in, conf, TRUE);
}

static mesa_rc mesa_vtr_grp_to_port_get(const mesa_inst_t               inst,
                                        const uint16_t                  group_id,
                                        mesa_vlan_trans_port2grp_conf_t *conf,
                                        BOOL                            next)
{
#if defined(VTSS_FEATURE_VCAP)
    mesa_rc                         rc;
    vtss_vlan_trans_port2grp_conf_t vtss_conf;

    vtss_conf.group_id = group_id;
    if ((rc = vtss_vlan_trans_group_to_port_get((const vtss_inst_t)inst, &vtss_conf, next)) == VTSS_RC_OK) {
        mesa_conv_vtss_vlan_trans_port2grp_conf_t_to_mesa_vlan_trans_port2grp_conf_t(&vtss_conf, conf);
    }
    return rc;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_vlan_trans_group_to_port_get(const mesa_inst_t               inst,
                                          const uint16_t                  group_id,
                                          mesa_vlan_trans_port2grp_conf_t *conf)
{
    return mesa_vtr_grp_to_port_get(inst, group_id, conf, FALSE);
}

mesa_rc mesa_vlan_trans_group_to_port_get_next(const mesa_inst_t               inst,
                                               const uint16_t                  group_id,
                                               mesa_vlan_trans_port2grp_conf_t *conf)
{
    return mesa_vtr_grp_to_port_get(inst, group_id, conf, TRUE);
}

mesa_rc mesa_vlan_trans_group_to_port_set(const mesa_inst_t inst, const mesa_vlan_trans_port2grp_conf_t *const conf)
{
#if defined(VTSS_FEATURE_VCAP)
    vtss_vlan_trans_port2grp_conf_t vtss_conf;

    mesa_conv_mesa_vlan_trans_port2grp_conf_t_to_vtss_vlan_trans_port2grp_conf_t(conf, &vtss_conf);
    return vtss_vlan_trans_group_to_port_set((const vtss_inst_t)inst, &vtss_conf);
#else
    return VTSS_RC_ERROR;
#endif
}

