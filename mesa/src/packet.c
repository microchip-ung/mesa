// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_api.h>
#include <mesa.h>

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_conv2_vtss_packet_rx_queue_conf_t_to_mesa_packet_rx_queue_conf_t(const vtss_packet_rx_queue_conf_t *in, mesa_packet_rx_queue_conf_t *out)
{
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_packet_rx_queue_conf_t_to_vtss_packet_rx_queue_conf_t(const mesa_packet_rx_queue_conf_t *in, vtss_packet_rx_queue_conf_t *out)
{
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_vtss_packet_rx_conf_t_to_mesa_packet_rx_conf_t(const vtss_packet_rx_conf_t *in, mesa_packet_rx_conf_t *out)
{
    vtss_packet_rx_queue_t queue;

    for (queue = 0; queue < VTSS_PACKET_RX_QUEUE_CNT; queue++) {
        out->queue[queue].grp_map = in->grp_map[queue];
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_packet_rx_conf_t_to_vtss_packet_rx_conf_t(const mesa_packet_rx_conf_t *in, vtss_packet_rx_conf_t *out)
{
    vtss_packet_rx_queue_t queue;

    for (queue = 0; queue < VTSS_PACKET_RX_QUEUE_CNT; queue++) {
        out->grp_map[queue] = in->queue[queue].grp_map;
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_vtss_packet_tx_info_t_to_mesa_packet_tx_info_t(const vtss_packet_tx_info_t *in, mesa_packet_tx_info_t *out)
{
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_packet_tx_info_t_to_vtss_packet_tx_info_t(const mesa_packet_tx_info_t *in, vtss_packet_tx_info_t *out)
{
    return VTSS_RC_OK;
}
#else
void mesa_packet_frame_info_init(mesa_packet_frame_info_t *const info)
{
}
#endif

mesa_rc mesa_packet_port_filter_get(const mesa_inst_t             inst,
                                    const mesa_packet_port_info_t *const info,
                                    const uint32_t                cnt,
                                    mesa_packet_port_filter_t     *const filter)
{
#if defined(VTSS_FEATURE_PACKET)
    mesa_rc                   rc;
    vtss_port_no_t            port_no;
    vtss_packet_port_info_t   vtss_info;
    vtss_packet_port_filter_t vtss_filter[VTSS_PORT_ARRAY_SIZE];

    if (cnt > VTSS_PORTS) {
        return VTSS_RC_ERROR;
    }
    mesa_conv_mesa_packet_port_info_t_to_vtss_packet_port_info_t(info, &vtss_info);
    if ((rc = vtss_packet_port_filter_get((const vtss_inst_t)inst, &vtss_info, vtss_filter)) == VTSS_RC_OK) {
        for (port_no = 0; port_no < cnt; port_no++) {
            mesa_conv_vtss_packet_port_filter_t_to_mesa_packet_port_filter_t(&vtss_filter[port_no], &filter[port_no]);
        }
    }
    return rc;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_packet_vlan_filter_get(const mesa_inst_t         inst,
                                    const uint32_t            cnt,
                                    mesa_packet_vlan_filter_t *const filter)
{
#if defined(VTSS_FEATURE_PACKET)
    mesa_rc                   rc;
    vtss_port_no_t            port_no;
    vtss_packet_vlan_filter_t vtss_filter[VTSS_PORTS];

    if (cnt > VTSS_PORTS) {
        return VTSS_RC_ERROR;
    }
    if ((rc = vtss_packet_vlan_filter_get((const vtss_inst_t)inst, vtss_filter)) == VTSS_RC_OK) {
        for (port_no = 0; port_no < cnt; port_no++) {
            mesa_conv_vtss_packet_vlan_filter_t_to_mesa_packet_vlan_filter_t(&vtss_filter[port_no], &filter[port_no]);
        }
    }
    return rc;
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_packet_tx_hdr_encode(const mesa_inst_t           inst,
                                  const mesa_packet_tx_info_t *const info,
                                  const uint32_t              bin_hdr_max_len,
                                  uint8_t                     *const bin_hdr,
                                  uint32_t                    *const bin_hdr_len)
{
#if defined(VTSS_FEATURE_PACKET)
    vtss_packet_tx_info_t vtss_info;

    mesa_conv_mesa_packet_tx_info_t_to_vtss_packet_tx_info_t(info, &vtss_info);
    *bin_hdr_len = bin_hdr_max_len; // INOUT in VTSS API
    return vtss_packet_tx_hdr_encode((const vtss_inst_t)inst, &vtss_info, bin_hdr, bin_hdr_len);
#else
    return VTSS_RC_ERROR;
#endif
}

mesa_rc mesa_afi_alloc(const mesa_inst_t          inst,
                       const mesa_afi_frm_dscr_t  *const dscr,
                       mesa_afi_frm_dscr_actual_t *const actual,
                       mesa_afi_id_t              *const id)
{
#if defined(VTSS_AFI_V1)
    mesa_rc             rc;
    vtss_afi_frm_dscr_t vtss_dscr;

    mesa_conv_mesa_afi_frm_dscr_t_to_vtss_afi_frm_dscr_t(dscr, &vtss_dscr);
    if ((rc = vtss_afi_alloc((const vtss_inst_t)inst, &vtss_dscr, id)) == VTSS_RC_OK) {
        actual->fps = vtss_dscr.actual_fps; // INOUT in VTSS API
    }
    return rc;
#else
    return VTSS_RC_OK;
#endif
}

mesa_rc mesa_afi_fast_inj_start(const mesa_inst_t                   inst,
                                const mesa_afi_fastid_t             fastid,
                                const mesa_afi_fast_inj_start_cfg_t *const cfg,
                                mesa_afi_fast_inj_start_actual_t    *const actual)
{
#if defined(VTSS_AFI_V2)
    mesa_rc                       rc;
    vtss_afi_fast_inj_start_cfg_t vtss_cfg;

    mesa_conv_mesa_afi_fast_inj_start_cfg_t_to_vtss_afi_fast_inj_start_cfg_t(cfg, &vtss_cfg);
    if ((rc = vtss_afi_fast_inj_start((const vtss_inst_t)inst, fastid, &vtss_cfg)) == VTSS_RC_OK) {
        actual->bps = vtss_cfg.bps_actual; // INOUT in VTSS API
    }
    return rc;
#else
    return VTSS_RC_OK;
#endif
}
