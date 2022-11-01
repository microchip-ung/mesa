// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_luton26_cil.h"
#include "vtss_ts_api.h"

#if defined(VTSS_ARCH_LUTON26)

/* - CIL functions ------------------------------------------------- */

/* ================================================================= *
 * NPI
 * ================================================================= */

static vtss_rc l26_npi_mask_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t *conf = &vtss_state->packet.rx_conf;

    if (vtss_state->packet.npi_conf.enable) {
        u32 val, qmask, i;
        for (qmask = i = 0; i < vtss_state->packet.rx_queue_count; i++) {
            if (conf->queue[i].npi.enable) {
                qmask |= VTSS_BIT(i); /* NPI redirect */
            }
        }
        val = VTSS_F_SYS_SYSTEM_EXT_CPU_CFG_EXT_CPU_PORT(VTSS_CHIP_PORT(vtss_state->packet.npi_conf.port_no)) | VTSS_F_SYS_SYSTEM_EXT_CPU_CFG_EXT_CPUQ_MSK(qmask);
        L26_WR(VTSS_SYS_SYSTEM_EXT_CPU_CFG, val);
    } else {
        L26_WR(VTSS_SYS_SYSTEM_EXT_CPU_CFG, 0); /* No redirect by default */
    }

    return VTSS_RC_OK;
}

static vtss_rc l26_npi_update(vtss_state_t *vtss_state)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;
    
    VTSS_RC(l26_npi_mask_set(vtss_state));

    if (conf->port_no != VTSS_PORT_NO_NONE) {
        u32 port = VTSS_CHIP_PORT(conf->port_no);

        /* Control IFH insertion */
        L26_WRM_CTL(VTSS_REW_PORT_PORT_CFG(port), conf->enable, VTSS_F_REW_PORT_PORT_CFG_IFH_INSERT_ENA);

        /* Control IFH parsing  */
        L26_WRM_CTL(VTSS_SYS_SYSTEM_PORT_MODE(port), conf->enable, VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR);
    }

    return VTSS_RC_OK;
}

static vtss_rc l26_npi_conf_set(vtss_state_t *vtss_state, const vtss_npi_conf_t *const new)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;

    /* Disable current NPI port */
    conf->enable = FALSE;
    VTSS_RC(l26_npi_update(vtss_state));

    /* Set new NPI port */
    *conf = *new;
    if (!conf->enable) {
        conf->port_no = VTSS_PORT_NO_NONE;
    }
    VTSS_RC(l26_npi_update(vtss_state));

    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc l26_packet_phy_cnt_to_ts_cnt(vtss_state_t *vtss_state, u32 phy_cnt, u64 *ts_cnt)
{
    VTSS_I("Not supported in this architecture");
    *ts_cnt = 0;

    return VTSS_RC_OK;
}

static vtss_rc l26_packet_ns_to_ts_cnt(vtss_state_t  *vtss_state,
                                       u32           ns,
                                       u64           *ts_cnt)
{
    vtss_timestamp_t ts;
    u32              tc;
    u64              tc_64;

    if (ns >= VTSS_ONE_MIA) {
       VTSS_I("Invalid ns value (%d)", ns);
    }
    _vtss_ts_domain_timeofday_get(NULL, 0, &ts, &tc_64);
    tc = tc_64 >> 16;       /* The tc_64 returned by _vtss_ts_domain_timeofday_get() is in 16 bit fractions of nanoseconds */
    if (ts.nanoseconds < ns) { // ns has wrapped
        ts.nanoseconds += VTSS_ONE_MIA;
    }
    tc = tc - ((ts.nanoseconds - ns) / VTSS_HW_TIME_NSEC_PR_CNT);
    *ts_cnt = (u64)tc << 16;  /* Must return in 16 bit fractions of nanoseconds */

    return VTSS_RC_OK;
}

static void l26_packet_ts_cnt_sub(u32 *r, u32 x, u32 y)
{
    *r = x-y;
    if (x < y) {*r += VTSS_HW_TIME_WRAP_LIMIT;} /* time counter has wrapped */
}

static u32 l26_packet_unpack32(const u8 *buf)
{
    return (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + buf[3];
}

static void l26_packet_pack32(u32 v, u8 *buf)
{
    buf[0] = (v>>24) & 0xff;
    buf[1] = (v>>16) & 0xff;
    buf[2] = (v>>8) & 0xff;
    buf[3] = v & 0xff;
}

static vtss_rc l26_ptp_get_timestamp(vtss_state_t                    *vtss_state,
                                     const u8                        *const frm,
                                     const vtss_packet_rx_info_t     *const rx_info,
                                     vtss_packet_ptp_message_type_t  message_type,
                                     vtss_packet_timestamp_props_t   ts_props,
                                     u64                             *rxTime,
                                     BOOL                            *timestamp_ok)
{
    vtss_ts_id_t ts_id;
    vtss_ts_timestamp_t ts;
    u32                 ns_32;
    ts_id.ts_id = rx_info->tstamp_id;
    *timestamp_ok = rx_info->tstamp_id_decoded;
    VTSS_I("Timestamp_id %d, Timestamp_decoded %d", ts_id.ts_id, *timestamp_ok);
    if (VTSS_RC_OK == _vtss_rx_timestamp_get(0, &ts_id, &ts) && ts.ts_valid) {
        ns_32 = ts.ts;
    } else {
        VTSS_I("No valid timestamp detected for id: %d", ts_id.ts_id);
        ns_32 = 0;
        *timestamp_ok = FALSE;
    }
#ifdef PTP_LOG_TRANSPARENT_ONESTEP_FORWARDING
    VTSS_I("Forwarded message type %d, ts.id %lu, source: %s, dest %s", message_type, ts_id.ts_id,
                                                                       (etype == ip_ether_type) ? misc_ipv4_txt(sender.ip,str1) : misc_mac_txt(sender.mac, str1),
                                                                       (etype == ip_ether_type) ? misc_ipv4_txt(dest_ip,str2) : misc_mac_txt(sender.mac, str2));
    uint tx_port_no;
    port_iter_t pit;
    port_iter_init_local(&pit);
    while (port_iter_getnext(&pit)) {
        tx_port_no = pit.iport;
        if (VTSS_RC_OK == _vtss_tx_timestamp_get(0, tx_port_no, &ts_id,&ts) && ts.ts_valid) {
            VTSS_I("Forwarded message, ts.id %u, to port %u", ts_id.ts_id, ptp_l2port_to_api(tx_port_no));
        }
    }
#endif
    if (ts_props.ts_feature_is_PTS) {
        ns_32 = l26_packet_unpack32(frm);
        (void)l26_packet_ns_to_ts_cnt(vtss_state, ns_32, rxTime);
        *timestamp_ok = TRUE;
        l26_packet_pack32(0, (u8 *)frm);   /* clear reserved field */
        VTSS_I("msgtype %d, rxtime %" PRIu64 "", message_type, *rxTime);
    } else {
        if (message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC) {
            /* if Sync message then subtract the p2p delay from rx time  */
            l26_packet_ts_cnt_sub(&ns_32, ns_32, (u32)(ts_props.delay_comp.delay_cnt >> 16));
        }
        /* link asymmetry compensation for Sync and PdelayResp events */
        if ((message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC || message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_P_DELAY_RESP) && ts_props.delay_comp.asymmetry_cnt != 0) {
            l26_packet_ts_cnt_sub(&ns_32, ns_32, (u32)(ts_props.delay_comp.asymmetry_cnt >> 16));
        }
        *rxTime = (u64)ns_32 << 16;  /* Must return in 16 bit fractions of nanoseconds */
    }
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Packet control
 * ================================================================= */

static vtss_rc l26_packet_mode_update(vtss_state_t *vtss_state)
{
    if (!vtss_state->packet.manual_mode) {
        /* Change mode to manual extraction and injection */
        vtss_state->packet.manual_mode = 1;
        /* Status word before last data */
        L26_WR(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(0), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP);
    }
    return VTSS_RC_OK;
}

#define XTR_EOF_0     0x80000000U
#define XTR_EOF_1     0x80000001U
#define XTR_EOF_2     0x80000002U
#define XTR_EOF_3     0x80000003U
#define XTR_PRUNED    0x80000004U
#define XTR_ABORT     0x80000005U
#define XTR_ESCAPE    0x80000006U
#define XTR_NOT_READY 0x80000007U

static vtss_rc l26_rx_frame_discard(vtss_state_t *vtss_state,
                                    const vtss_packet_rx_queue_t queue_no)
{
    BOOL done = FALSE;
    vtss_packet_rx_grp_t xtr_grp;

    if (vtss_state->init_conf.packet_init_disable) {
        VTSS_I("Packet interface not supported");
        return VTSS_RC_OK;
    }

    xtr_grp = vtss_state->packet.rx_conf.grp_map[queue_no];

    while(!done) {
        u32 val;
        L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val);
        switch(val) {
        case XTR_ABORT:
        case XTR_PRUNED:
        case XTR_EOF_3:
        case XTR_EOF_2:
        case XTR_EOF_1:
        case XTR_EOF_0:
            L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val); /* Last data */
            done = TRUE;        /* Last 1-4 bytes */
            break;
        case XTR_ESCAPE:
            L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val); /* Escaped data */
            break;
        case XTR_NOT_READY:
        default:
            ;
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_rx_frame_rd(vtss_state_t *vtss_state,
                               const vtss_packet_rx_queue_t queue_no,
                               u8 *frame,
                               int buflen,
                               u32 *bytes_read)
{
    u32 read = 0;
    u8 *buf = frame;
    BOOL done = FALSE;
    vtss_rc rc = VTSS_RC_OK;
    vtss_packet_rx_grp_t xtr_grp = vtss_state->packet.rx_conf.grp_map[queue_no];

    if (vtss_state->init_conf.packet_init_disable) {
        VTSS_I("Packet interface not supported");
        return VTSS_RC_OK;
    }

    while(!done && buflen > 3) {
        u32 val;

        L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val);

        switch(val) {
        case XTR_NOT_READY:
            break;              /* Try again... */
        case XTR_ABORT:
            L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val); /* Unused */
            rc = VTSS_RC_ERROR;
            done = TRUE;
            break;
        case XTR_EOF_3:
            L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val);
            *buf++ = (u8)(val >> 0);
            read += 1;
            done = TRUE;
            break;
        case XTR_EOF_2:
            L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val);
            *buf++ = (u8)(val >> 0);
            *buf++ = (u8)(val >> 8);
            read += 2;
            done = TRUE;
            break;
        case XTR_EOF_1:
            L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val);
            *buf++ = (u8)(val >>  0);
            *buf++ = (u8)(val >>  8);
            *buf++ = (u8)(val >> 16);
            read += 3;
            done = TRUE;
            break;
        case XTR_PRUNED:
            rc = VTSS_RC_INCOMPLETE; /* But get the last 4 bytes as well */
            /* FALLTHROUGH */
        case XTR_EOF_0:
            done = TRUE;
            /* FALLTHROUGH */
        case XTR_ESCAPE:
            L26_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val);
            /* FALLTHROUGH */
        default:
            *buf++ = (u8)(val >>  0);
            *buf++ = (u8)(val >>  8);
            *buf++ = (u8)(val >> 16);
            *buf++ = (u8)(val >> 24);
            buflen -= 4, read += 4;
        }
    }

    if (bytes_read != NULL) {
        if(!done) {                 /* Buffer overrun */
            (void) l26_rx_frame_discard(vtss_state, queue_no);
            rc = VTSS_RC_INCOMPLETE; /* ??? */
        }

        if (rc != VTSS_RC_ERROR)
            *bytes_read = read;
    }
    return rc;
}

static inline u32 BYTE_SWAP(u32 v)
{
    register u32 v1 = v;
    v1 = ((v1 >> 24) & 0x000000FF) | ((v1 >> 8) & 0x0000FF00) | ((v1 << 8) & 0x00FF0000) | ((v1 << 24) & 0xFF000000);
    return v1;
}

static vtss_rc l26_tx_frame_ifh_vid(vtss_state_t *vtss_state,
                                   const vtss_packet_tx_ifh_t *const ifh,
                                   const u8 *const frame,
                                   const u32 length,
                                   const vtss_vid_t vid)
{
    u32 status, w, count, last;
    const u8 *buf = frame;

    if (vtss_state->init_conf.packet_init_disable) {
        VTSS_I("Packet interface not supported");
        return VTSS_RC_OK;
    }

    VTSS_N("length: %u, vid: %u, ifhlen: %d", length, vid, ifh->length);

    VTSS_RC(l26_packet_mode_update(vtss_state));

    L26_RD(VTSS_DEVCPU_QS_INJ_INJ_STATUS, &status);
    if (!(VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_FIFO_RDY(status) & VTSS_BIT(CPU_INJ_REG))) {
        VTSS_E("not ready");
        return VTSS_RC_ERROR;
    }

    if (VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED(status) & VTSS_BIT(CPU_INJ_REG)) {
        VTSS_E("wm reached");
        return VTSS_RC_ERROR;
    }

    /* Indicate SOF */
    L26_WR(VTSS_DEVCPU_QS_INJ_INJ_CTRL(CPU_INJ_REG), VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_SOF);

    /* Write IFH - variable length */
    for (w = 0, count = (ifh->length/4); w < count; w++) {
        L26_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(CPU_INJ_REG), ifh->ifh[w]);
    }

    /* Write words, round up */
    count = ((length+3) / 4);
    last = (length % 4);
    for (w = 0; w < count; w++, buf += 4) {
        if (w == 3 && vid != VTSS_VID_NULL) {
            /* Insert C-tag */
            L26_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(CPU_INJ_REG), VTSS_OS_NTOHL((0x8100U << 16) | vid));
            w++;
        }
#ifdef VTSS_OS_BIG_ENDIAN
        L26_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(CPU_INJ_REG), (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
#else
        L26_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(CPU_INJ_REG), (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
#endif
    }

    /* Add padding */
    while (w < (60 / 4)) {
        L26_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(CPU_INJ_REG), 0);
        w++;
    }
    
    /* Indicate EOF and valid bytes in last word */
    L26_WR(VTSS_DEVCPU_QS_INJ_INJ_CTRL(CPU_INJ_REG), 
           VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES(length < 60 ? 0 : last) |
           VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_EOF);

    /* Add dummy CRC */
    L26_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(CPU_INJ_REG), 0);
    w++;

    VTSS_N("wrote %u words, last: %u", w, last);

    return VTSS_RC_OK;
}

static vtss_rc l26_tx_frame_ifh(vtss_state_t *vtss_state,
                                const vtss_packet_tx_ifh_t *const ifh,
                                const u8 *const frame,
                                const u32 length)
{
    return l26_tx_frame_ifh_vid(vtss_state, ifh, frame, length, VTSS_VID_NULL);
}

static vtss_rc l26_rx_hdr_decode(const vtss_state_t          *const state,
                                 const vtss_packet_rx_meta_t *const meta,
                                 const u8                           xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                       vtss_packet_rx_info_t *const info)
{
    u64                 ifh;
    u32                 sflow_id;
    u8                  signature;
    vtss_phys_port_no_t chip_port;

    VTSS_DG(VTSS_TRACE_GROUP_PACKET, "IFH:");
    VTSS_DG_HEX(VTSS_TRACE_GROUP_PACKET, &xtr_hdr[0], 8);

    ifh = ((u64)xtr_hdr[0] << 56) | ((u64)xtr_hdr[1] << 48) | ((u64)xtr_hdr[2] << 40) | ((u64)xtr_hdr[3] << 32) |
          ((u64)xtr_hdr[4] << 24) | ((u64)xtr_hdr[5] << 16) | ((u64)xtr_hdr[6] <<  8) | ((u64)xtr_hdr[7] <<  0);

    // Signature must be 0xFF, otherwise it's not a valid extraction header.
    signature = VTSS_EXTRACT_BITFIELD64(ifh, 56, 8);
    if (signature != 0xFF) {
        VTSS_EG(VTSS_TRACE_GROUP_PACKET, "Invalid Rx header signature. Expected 0xFF got 0x%02x", signature);
        return VTSS_RC_ERROR;
    }

    VTSS_MEMSET(info, 0, sizeof(*info));

    info->length    = meta->length;

    // Map from chip port to API port
    chip_port = VTSS_EXTRACT_BITFIELD64(ifh, 51, 5);
    info->port_no = vtss_cmn_chip_to_logical_port(state, 0, chip_port);
    if (info->port_no == VTSS_PORT_NO_NONE) {
        VTSS_EG(VTSS_TRACE_GROUP_PACKET, "Unknown chip port: %u", chip_port);
        return VTSS_RC_ERROR;
    }

    info->tag.pcp     = VTSS_EXTRACT_BITFIELD64(ifh, 13,  3);
    info->tag.dei     = VTSS_EXTRACT_BITFIELD64(ifh, 12,  1);
    info->tag.vid     = VTSS_EXTRACT_BITFIELD64(ifh,  0, 12);
    info->xtr_qu_mask = VTSS_EXTRACT_BITFIELD64(ifh, 20,  8);
    info->cos         = VTSS_EXTRACT_BITFIELD64(ifh, 17,  3);

    VTSS_RC(vtss_cmn_packet_hints_update(state, VTSS_TRACE_GROUP_PACKET, meta->etype, info));

    info->acl_hit = VTSS_EXTRACT_BITFIELD64(ifh, 31, 1);
    if (info->acl_hit) {
        // An additional check for PTP frame would have been better,
        // since tstamp_id_decoded = TRUE gets set for any frame that
        // comes to the CPU due to an IS2 rule.
        info->tstamp_id = VTSS_EXTRACT_BITFIELD64(ifh, 45, 6);
        info->tstamp_id_decoded = TRUE;
    }

    // sflow_id:
    // 0-26 : Frame has been SFlow sampled by a Tx sampler on port given by #sflow_id.
    // 27   : Frame has been SFlow sampled by an Rx sampler on port given by #port_no.
    // 28-30: Reserved.
    // 31   : Frame has not been SFlow sampled.
    sflow_id = VTSS_EXTRACT_BITFIELD64(ifh, 32, 5);
    if (sflow_id == 27) {
        info->sflow_type = VTSS_SFLOW_TYPE_RX;
        info->sflow_port_no = info->port_no;
    } else if (sflow_id < 27) {
        info->sflow_type = VTSS_SFLOW_TYPE_TX;
        info->sflow_port_no = vtss_cmn_chip_to_logical_port(state, 0, sflow_id);
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_rx_frame(struct vtss_state_s   *vtss_state,
                            u8                    *const data,
                            const u32             buflen,
                            vtss_packet_rx_info_t *const rx_info)
{
    vtss_rc               rc = VTSS_RC_INCOMPLETE;
    u32                   val, len;
    vtss_packet_rx_meta_t meta;
    u8                    ifh[VTSS_L26_RX_IFH_SIZE];

    if (vtss_state->init_conf.packet_init_disable) {
        VTSS_I("Packet interface not supported");
        return VTSS_RC_OK;
    }

    VTSS_RC(l26_packet_mode_update(vtss_state));

    /* Check if data is ready for grp */
    L26_RD(VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT, &val);
    if (val) {
        VTSS_RC(l26_rx_frame_rd(vtss_state, 0, ifh, VTSS_L26_RX_IFH_SIZE, NULL));
        VTSS_RC(l26_rx_frame_rd(vtss_state, 0, data, buflen, &len));
        VTSS_MEMSET(&meta, 0, sizeof(meta));
        meta.length = (len - 4);
        meta.etype = (data[12] << 8) | data[13];
        rc = l26_rx_hdr_decode(vtss_state, &meta, ifh, rx_info);
    }
    return rc;
}

/*****************************************************************************/
// l26_ptp_action_to_ifh()
/*****************************************************************************/
static vtss_rc l26_ptp_action_to_ifh(vtss_packet_ptp_action_t ptp_action, u32 *result)
{
    vtss_rc rc = VTSS_RC_OK;

    switch (ptp_action) {
    case VTSS_PACKET_PTP_ACTION_NONE:
        *result = 0;
        break;
    case VTSS_PACKET_PTP_ACTION_ONE_STEP:
        *result = 1;
        break;
    case VTSS_PACKET_PTP_ACTION_TWO_STEP:
        *result = 2;
        break;
    case VTSS_PACKET_PTP_ACTION_ONE_AND_TWO_STEP:
        *result = 3;
        break;
    default:
        VTSS_EG(VTSS_TRACE_GROUP_PACKET, "Invalid PTP action (%d)", ptp_action);
        rc = VTSS_RC_ERROR;
        break;
    }
    return rc;
}

static vtss_rc l26_tx_hdr_encode(      vtss_state_t          *const state,
                                 const vtss_packet_tx_info_t *const info,
                                       u8                    *const bin_hdr,
                                       u32                   *const bin_hdr_len)
{
    u64 inj_hdr, ts;
    u32 required_ifh_size = info->ptp_action == 0 ? 8 : 8 + 4;

    if (bin_hdr == NULL) {
        // Caller wants us to return the number of bytes required to fill
        // in #bin_hdr. We need 8 or 12 bytes for the IFH depending on
        // whether we need to timestamp the frame.
        *bin_hdr_len = required_ifh_size;
        return VTSS_RC_OK;
    } else if (*bin_hdr_len < required_ifh_size) {
        return VTSS_RC_ERROR;
    }

    *bin_hdr_len = required_ifh_size;

    inj_hdr  = VTSS_ENCODE_BITFIELD64(!info->switch_frm,               63,  1); // BYPASS
    inj_hdr |= VTSS_ENCODE_BITFIELD64( info->cos >= 8 ? 7 : info->cos, 17,  3); // QoS Class.

    if (info->switch_frm) {
        if (info->tag.tpid != 0) {
            // If sending the frame switched, the caller should have inserted a VLAN tag in the packet
            // to get it classified to a particular VID. This is flagged to this function through
            // the tag.tpid member, which is non-zero if a tag is added. When a tag is added,
            // the frame still contains the tag at egress, so we have to remove it by setting POP_CNT to 1.
            inj_hdr |= VTSS_ENCODE_BITFIELD64(0x1, 28, 2);
        }
    } else {
        u64            chip_port_mask;
        vtss_chip_no_t chip_no;
        vtss_port_no_t stack_port_no, port_no;
        u32            port_cnt, ptp_action, pop_cnt = 3 /* Disable rewriter */;

        VTSS_RC(vtss_cmn_logical_to_chip_port_mask(state, info->dst_port_mask, &chip_port_mask, &chip_no, &stack_port_no, &port_cnt, &port_no));

        if (info->tag.tpid == 0 && info->tag.vid != VTSS_VID_NULL) {
            // Get the frame classified to info->tag.vid, and rewritten accordingly.
            pop_cnt = 0;
        }

#ifdef VTSS_FEATURE_MIRROR_CPU
        // Add mirror port if enabled. Mirroring of directed frames must occur through the port mask.
        if (state->l2.mirror_conf.port_no != VTSS_PORT_NO_NONE && state->l2.mirror_cpu_ingress) {
            chip_port_mask |= VTSS_BIT64(VTSS_CHIP_PORT_FROM_STATE(state, state->l2.mirror_conf.port_no));
        }
#endif

        // Destination port set.
        inj_hdr |= VTSS_ENCODE_BITFIELD64(chip_port_mask, 32, 26); // Ignore the CPU port

        // Inject frame as is, i.e. disable rewriter.
        inj_hdr |= VTSS_ENCODE_BITFIELD64(pop_cnt, 28, 2); // POP_CNT

        VTSS_RC(l26_ptp_action_to_ifh(info->ptp_action, &ptp_action));
        inj_hdr |= VTSS_ENCODE_BITFIELD64(ptp_action,   61, 2); // PTP_ACTION
        inj_hdr |= VTSS_ENCODE_BITFIELD64(info->ptp_id, 59, 2); // PTP_ID
    }

    // Time to store it as binary.
    bin_hdr[0] = inj_hdr >> 56;
    bin_hdr[1] = inj_hdr >> 48;
    bin_hdr[2] = inj_hdr >> 40;
    bin_hdr[3] = inj_hdr >> 32;
    bin_hdr[4] = inj_hdr >> 24;
    bin_hdr[5] = inj_hdr >> 16;
    bin_hdr[6] = inj_hdr >>  8;
    bin_hdr[7] = inj_hdr >>  0;

    // Lu26 has variable-length IFH. If PTP_ACTION != VTSS_PACKET_PTP_ACTION_NONE, a 32-bit timestamp
    // is inserted in between the normal injection header and the first
    // byte of the DMAC.
    if (info->ptp_action != VTSS_PACKET_PTP_ACTION_NONE) {
        // Store the timestamp.
        ts = info->ptp_timestamp>>16;
        bin_hdr[8 + 0] = ts >> 24;
        bin_hdr[8 + 1] = ts >> 16;
        bin_hdr[8 + 2] = ts >>  8;
        bin_hdr[8 + 3] = ts >>  0;
    }

    VTSS_IG(VTSS_TRACE_GROUP_PACKET, "IFH:");
    VTSS_IG_HEX(VTSS_TRACE_GROUP_PACKET, &bin_hdr[0], *bin_hdr_len);

    return VTSS_RC_OK;
}

static vtss_rc l26_rx_conf_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t      *conf = &vtss_state->packet.rx_conf;
    vtss_packet_rx_reg_t       *reg = &conf->reg;
    vtss_packet_rx_queue_map_t *map = &conf->map;
    u32                        queue, i, value, port, bpdu, garp;
    vtss_port_no_t             port_no;
    vtss_packet_rx_port_conf_t *port_conf;
    vtss_packet_reg_type_t     type;
    
    if (vtss_state->init_conf.packet_init_disable) {
        VTSS_I("Packet interface not supported");
        return VTSS_RC_OK;
    }

    /* Each CPU queue get resverved extraction buffer space. No sharing at port or buffer level */
    for (queue = 0; queue < vtss_state->packet.rx_queue_count; queue++) {
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(VTSS_CHIP_PORT_CPU * VTSS_PRIOS + queue + 512), conf->queue[queue].size/L26_BUFFER_CELL_SZ);
    }
    L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(VTSS_CHIP_PORT_CPU + 224 + 512), 0); /* No extra shared space at port level */
    
    /* Rx IPMC registration */
    value = 
        (reg->ipmc_ctrl_cpu_copy ? VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_IPMC_CTRL_COPY_ENA  : 0) |
        (reg->igmp_cpu_only      ? VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_IGMP_REDIR_ENA      : 0) |
        (reg->mld_cpu_only       ? VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_MLD_REDIR_ENA       : 0);
    for (port = 0; port < VTSS_CHIP_PORTS; port++) 
        L26_WR(VTSS_ANA_PORT_CPU_FWD_CFG(port), value);

    /* Rx BPDU and GARP registrations */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!VTSS_PORT_CHIP_SELECTED(port_no))
            continue;
        port = VTSS_CHIP_PORT(port_no);
        port_conf = &vtss_state->packet.rx_port_conf[port_no];
        for (i = 0, bpdu = 0, garp = 0; i < 16; i++) {
            type = port_conf->bpdu_reg[i];
            if ((type == VTSS_PACKET_REG_NORMAL && reg->bpdu_cpu_only) ||
                type == VTSS_PACKET_REG_CPU_ONLY)
                bpdu |= VTSS_BIT(i);
            type = port_conf->garp_reg[i];
            if ((type == VTSS_PACKET_REG_NORMAL && reg->garp_cpu_only[i]) ||
                type == VTSS_PACKET_REG_CPU_ONLY)
                garp |= VTSS_BIT(i);
        }
        L26_WR(VTSS_ANA_PORT_CPU_FWD_BPDU_CFG(port), bpdu);
        L26_WR(VTSS_ANA_PORT_CPU_FWD_GARP_CFG(port), garp);
    }

    /* Fixme - chipset has more queues than the classification the API expose */
    value = 
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_SFLOW(map->sflow_queue != VTSS_PACKET_RX_QUEUE_NONE ? map->sflow_queue - VTSS_PACKET_RX_QUEUE_START : VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MIRROR(map->mac_vid_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_LRN(map->learn_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MAC_COPY(map->mac_vid_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_SRC_COPY(map->mac_vid_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE(map->mac_vid_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_ALLBRIDGE(map->bpdu_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_IPMC_CTRL(map->ipmc_ctrl_queue-VTSS_PACKET_RX_QUEUE_START) |
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_IGMP(map->igmp_queue-VTSS_PACKET_RX_QUEUE_START) | 
        VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MLD(map->igmp_queue-VTSS_PACKET_RX_QUEUE_START);
    L26_WR(VTSS_ANA_COMMON_CPUQ_CFG, value);

    /* Setup each of the BPDU, GARP and CCM 'address' extraction queues */
    for (i = 0; i < 16; i++) {
        value = 
            VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_BPDU_VAL(map->bpdu_queue-VTSS_PACKET_RX_QUEUE_START) | 
            VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_GARP_VAL(map->garp_queue-VTSS_PACKET_RX_QUEUE_START) |
            VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_CCM_VAL(VTSS_PACKET_RX_QUEUE_START); /* Fixme */
        L26_WR(VTSS_ANA_COMMON_CPUQ_8021_CFG(i), value);
    }

    /* Configure Rx Queue #i to map to an Rx group. */
    for (value = i = 0; i < vtss_state->packet.rx_queue_count; i++) {
        if(conf->grp_map[i]) {
            value |= VTSS_BIT(i);
        }
    }
    L26_WRM(VTSS_SYS_SCH_SCH_CPU, VTSS_F_SYS_SCH_SCH_CPU_SCH_CPU_MAP(value), VTSS_M_SYS_SCH_SCH_CPU_SCH_CPU_MAP);

    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++) {
        /* One-to-one mapping from CPU Queue number to Extraction Group number. Enable both. */
        /* Note: On Luton26, CPU Queue is not to be confused with CPU Extraction Queue. */
        L26_WR(VTSS_DEVCPU_QS_XTR_XTR_MAP(i), (i * VTSS_F_DEVCPU_QS_XTR_XTR_MAP_GRP) | VTSS_F_DEVCPU_QS_XTR_XTR_MAP_MAP_ENA);
    }

    VTSS_RC(l26_npi_mask_set(vtss_state));

    /* Setup CPU port 0 and 1 */
    for (i = VTSS_CHIP_PORT_CPU_0; i <= VTSS_CHIP_PORT_CPU_1; i++) {
        /* Enable IFH insertion */
        L26_WRM_SET(VTSS_REW_PORT_PORT_CFG(i), VTSS_F_REW_PORT_PORT_CFG_IFH_INSERT_ENA);

        /* Enable IFH parsing on CPU port 0 and 1 */
        L26_WRM_SET(VTSS_SYS_SYSTEM_PORT_MODE(i), VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR);
    }

    /* Enable CPU port */
    L26_WRM_SET(VTSS_SYS_SYSTEM_SWITCH_PORT_MODE(VTSS_CHIP_PORT_CPU), 
                VTSS_F_SYS_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);
    
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

#define L26_DEBUG_CPU_FWD(pr, addr, i, name) vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_CPU_FWD_##addr, i, "FWD_"name)
#define L26_DEBUG_XTR(pr, addr, name) vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_QS_XTR_XTR_##addr, "XTR_"name)
#define L26_DEBUG_XTR_INST(pr, addr, i, name) vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_DEVCPU_QS_XTR_XTR_##addr, i, "XTR_"name)
#define L26_DEBUG_INJ(pr, addr, name) vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_QS_INJ_INJ_##addr, "INJ_"name)
#define L26_DEBUG_INJ_INST(pr, addr, i, name) vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_DEVCPU_QS_INJ_INJ_##addr, i, "INJ_"name)

static vtss_rc l26_debug_pkt(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    u32  i, port;
    char buf[32];

    if (vtss_state->init_conf.packet_init_disable) {
        VTSS_I("Packet interface not supported");
        return VTSS_RC_OK;
    }

    /* Analyzer CPU forwarding registers */
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "Port %u", port);
        vtss_l26_debug_reg_header(pr, buf);
        L26_DEBUG_CPU_FWD(pr, CFG(port), port, "CFG");
        L26_DEBUG_CPU_FWD(pr, BPDU_CFG(port), port, "BPDU_CFG");
        L26_DEBUG_CPU_FWD(pr, GARP_CFG(port), port, "GARP_CFG");
        L26_DEBUG_CPU_FWD(pr, CCM_CFG(port), port, "CCM_CFG");
        pr("\n");
    }
    
    /* Analyzer CPU queue mappings */
    vtss_l26_debug_reg_header(pr, "CPU Queues");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_ANA_COMMON_CPUQ_CFG, "CPUQ_CFG");
    for (i = 0; i < 16; i++)
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_COMMON_CPUQ_8021_CFG(i), i, "CPUQ_8021_CFG");
    pr("\n");

    /* Packet extraction registers */
    vtss_l26_debug_reg_header(pr, "Extraction");
    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++)
        L26_DEBUG_XTR_INST(pr, FRM_PRUNING(i), i, "FRM_PRUNING");
    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++)
        L26_DEBUG_XTR_INST(pr, GRP_CFG(i), i, "GRP_CFG");
    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++)
        L26_DEBUG_XTR_INST(pr, MAP(i), i, "MAP");
    L26_DEBUG_XTR(pr, DATA_PRESENT, "DATA_PRESENT");
    L26_DEBUG_XTR(pr, QU_DBG, "QU_DBG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_SYS_SCH_SCH_CPU, "SCH_CPU");
    pr("\n");
    
    /* Packet injection registers */
    vtss_l26_debug_reg_header(pr, "Injection");
    for (i = 0; i < VTSS_PACKET_TX_GRP_CNT; i++)
        L26_DEBUG_INJ_INST(pr, GRP_CFG(i), i, "GRP_CFG");
    for (i = 0; i < VTSS_PACKET_TX_GRP_CNT; i++)
        L26_DEBUG_INJ_INST(pr, CTRL(i), i, "CTRL");
    for (i = 0; i < VTSS_PACKET_TX_GRP_CNT; i++)
        L26_DEBUG_INJ_INST(pr, ERR(i), i, "ERR");
    L26_DEBUG_INJ(pr, STATUS, "STATUS");
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_packet_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PACKET, l26_debug_pkt, vtss_state, pr, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc l26_packet_init(vtss_state_t *vtss_state)
{
    u32 i, pcp, dei;

    /* Setup the CPU port as VLAN aware to support switching frames based on tags */
    L26_WR(VTSS_ANA_PORT_VLAN_CFG(VTSS_CHIP_PORT_CPU), 
           VTSS_F_ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA  |
           VTSS_F_ANA_PORT_VLAN_CFG_VLAN_POP_CNT(1) |
           VTSS_F_ANA_PORT_VLAN_CFG_VLAN_VID(1));
    
    /* Disable learning (only RECV_ENA must be set) */
    L26_WR(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT_CPU), VTSS_F_ANA_PORT_PORT_CFG_RECV_ENA);

    /* Set-up default packet Rx endianness and position of status word. */
    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++) {
        // Do not configure any byte-swapping if using the uFDMA on its particular Rx group.
        if (!vtss_state->init_conf.using_ufdma || i != 0) {
            /* Little-endian and status word before last data */
            L26_WR(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP);
        }
    }

    /* Setup CPU port 0 and 1 to allow for classification of transmission of
     * switched frames into a user-module-specifiable QoS class.
     * For the two CPU ports, we set a one-to-one mapping between a VLAN tag's
     * PCP and a QoS class. When transmitting switched frames, the PCP value
     * of the VLAN tag (which is always inserted to get it switched on a given
     * VID), then controls the priority. */
    /* Enable looking into PCP bits */
    L26_WR(VTSS_ANA_PORT_QOS_CFG(VTSS_CHIP_PORT_CPU), VTSS_F_ANA_PORT_QOS_CFG_QOS_PCP_ENA);

    /* Disable aging of Rx CPU queues to allow the frames to stay there longer than
     * on normal front ports. */
    L26_WRM_SET(VTSS_REW_PORT_PORT_CFG(VTSS_CHIP_PORT_CPU), VTSS_F_REW_PORT_PORT_CFG_AGE_DIS);

    /* Disallow the CPU Rx queues to use shared memory. */
    L26_WRM_SET(VTSS_SYS_SYSTEM_EGR_NO_SHARING, VTSS_BIT(VTSS_CHIP_PORT_CPU));

    /* Don't make head-of-line-blocking of frames going to the CPU, as this may
     * cause pause-frames to be sent out on flow-control-enabled front ports. */
    L26_WRM_SET(VTSS_SYS_PAUSE_CFG_EGR_DROP_FORCE, VTSS_BIT(VTSS_CHIP_PORT_CPU));

    /* Set-up the one-to-one mapping */
    for (pcp = 0; pcp < VTSS_PCP_END - VTSS_PCP_START; pcp++) {
        for (dei = 0; dei < VTSS_DEI_END - VTSS_DEI_START; dei++) {
            L26_WR(VTSS_ANA_PORT_QOS_PCP_DEI_MAP_CFG(VTSS_CHIP_PORT_CPU, (8 * dei + pcp)), VTSS_F_ANA_PORT_QOS_PCP_DEI_MAP_CFG_QOS_PCP_DEI_VAL(pcp));
        }
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_packet_state_t *state = &vtss_state->packet;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->rx_conf_set              = l26_rx_conf_set;
        state->rx_frame                 = l26_rx_frame;
        state->tx_frame_ifh             = l26_tx_frame_ifh;
        state->rx_hdr_decode            = l26_rx_hdr_decode;
        state->rx_ifh_size              = VTSS_L26_RX_IFH_SIZE;
        state->tx_hdr_encode            = l26_tx_hdr_encode;
        state->npi_conf_set             = l26_npi_conf_set;
        state->packet_phy_cnt_to_ts_cnt = l26_packet_phy_cnt_to_ts_cnt;
        state->packet_ns_to_ts_cnt      = l26_packet_ns_to_ts_cnt;
        state->ptp_get_timestamp        = l26_ptp_get_timestamp;
        state->rx_queue_count           = VTSS_PACKET_RX_QUEUE_CNT;
        break;
    case VTSS_INIT_CMD_INIT:
        if (!vtss_state->init_conf.packet_init_disable) {
            VTSS_RC(l26_packet_init(vtss_state));
        }
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        if (!vtss_state->warm_start_cur) {
            VTSS_RC(l26_rx_conf_set(vtss_state)); 
        }
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LUTON26 */
