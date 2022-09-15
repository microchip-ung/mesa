// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X) && defined(VTSS_FEATURE_PACKET)

/* ================================================================= *
 *  NPI
 * ================================================================= */

// IFH is 28 bytes (7 words)
#define LAN966X_IFH_SIZE  IFH_LEN
#define LAN966X_IFH_WORDS (LAN966X_IFH_SIZE / 4)

static vtss_rc lan966x_npi_mask_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t *conf = &vtss_state->packet.rx_conf;
    vtss_port_no_t        port_no = vtss_state->packet.npi_conf.port_no;
    u32                   val = 0, qmask, i;

    val = QSYS_EXT_CPU_CFG_EXT_CPU_KILL_ENA(1) |
          QSYS_EXT_CPU_CFG_INT_CPU_KILL_ENA(1);
    if (port_no < vtss_state->port_count) {
        for (qmask = i = 0; i < vtss_state->packet.rx_queue_count; i++) {
            if (conf->queue[i].npi.enable) {
                qmask |= VTSS_BIT(i); /* NPI redirect */
            }
        }
        val |= (QSYS_EXT_CPU_CFG_EXT_CPU_PORT(VTSS_CHIP_PORT(port_no)) |
               QSYS_EXT_CPU_CFG_EXT_CPUQ_MSK(qmask));
    }
    REG_WR(QSYS_EXT_CPU_CFG, val);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_npi_conf_set(vtss_state_t *vtss_state, const vtss_npi_conf_t *const new)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;
    u32             val = (SYS_PORT_MODE_INCL_INJ_HDR(3) | SYS_PORT_MODE_INCL_XTR_HDR(3));
    u32             msk = (SYS_PORT_MODE_INCL_INJ_HDR_M | SYS_PORT_MODE_INCL_XTR_HDR_M);

    // Disable current NPI port
    if (conf->enable) {
        REG_WRM(SYS_PORT_MODE(VTSS_CHIP_PORT(conf->port_no)), 0, msk);
    }

    // Set new NPI port
    *conf = *new;
    if (conf->enable) {
        REG_WRM(SYS_PORT_MODE(VTSS_CHIP_PORT(conf->port_no)), val, msk);
    }
    VTSS_RC(lan966x_npi_mask_set(vtss_state));
    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc lan966x_packet_phy_cnt_to_ts_cnt(vtss_state_t *vtss_state, u32 phy_cnt, u64 *ts_cnt)
{
    VTSS_I("Not supported in this architecture");
    *ts_cnt = 0;

    return VTSS_RC_OK;
}

static vtss_rc lan966x_packet_ns_to_ts_cnt(vtss_state_t  *vtss_state,
                                           u32            frame_ns,
                                           u64            *ts_cnt)
{
#if defined(VTSS_FEATURE_TIMESTAMP)
    vtss_timestamp_t ts;
    u64              tc;
    u32              tod_ns, diff;

    /* The frame_ns parameter is a one mia (one second) wrapping nano second counter, extracted from the received packet (inserted by the PHY) */

    while (frame_ns >= VTSS_ONE_MIA) {
        /* skip sec part */
        frame_ns -= VTSS_ONE_MIA;
        VTSS_I("decrement frame_ns value (%d)", frame_ns);
    }

    /* The time of day is sampled 2 or more times pr sec, assumed frame stamping belong to domain 0 */
    _vtss_ts_domain_timeofday_get(NULL, 0, &ts, &tc);
    if (ts.nanoseconds < frame_ns) {
        tod_ns = ts.nanoseconds + VTSS_ONE_MIA; /* TOD nanoseconds is smaller than the frame_ns from the frame. TOD nanoseconds has wrapped */
        tc += ((u64)VTSS_ONE_MIA) << 16;
    } else {
        tod_ns = ts.nanoseconds;
    }

    diff = tod_ns - frame_ns;               /* Calculate the difference between FRAME and TOD 30 bit wrapping nano second counter */
    *ts_cnt = tc - (u64)((u64)diff << 16);  /* Difference in 16 bit nano second fragments */
    VTSS_I("frame_ns %u  tod_ns %u  ts_cnt %" PRIu64 "  diff %u  ts.sec %u  ts.ns %u  tc %" PRIu64 "", frame_ns, tod_ns, *ts_cnt, diff, ts.seconds, ts.nanoseconds, tc);
#endif
    return VTSS_RC_OK;
}

static u32 lan966x_packet_unpack32(const u8 *buf)
{
    return (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + buf[3];
}

static vtss_rc lan966x_ptp_get_timestamp(vtss_state_t                    *vtss_state,
                                         const u8                        *const frm,
                                         const vtss_packet_rx_info_t     *const rx_info,
                                         vtss_packet_ptp_message_type_t  message_type,
                                         vtss_packet_timestamp_props_t   ts_props,
                                         u64                             *rxTime,
                                         BOOL                            *timestamp_ok)
{
    if (ts_props.ts_feature_is_PTS) {
        if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_30BIT) {
            // rxTime is similar to tc returned from lan966x_ts_io_pin_timeofday_get
            *rxTime = ((u64)lan966x_packet_unpack32(frm)) << 16;
            *timestamp_ok = rx_info->hw_tstamp_decoded;
        } else {
            VTSS_I("PHY timestamp mode %d not supported", ts_props.phy_ts_mode);
        }
    } else {
        /* The hw_tstamp is a tc in 16 bit nano second fragments (46 (30 bits nsec + 16 bits sub nsec) wrapping) */
        *rxTime = rx_info->hw_tstamp;
        *timestamp_ok = rx_info->hw_tstamp_decoded;
        /* if Sync message then subtract the p2p delay from rx time  */
        if (message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC) {
            *rxTime = *rxTime - ts_props.delay_comp.delay_cnt;
        }
        /* link asymmetry compensation for Sync and PdelayResp events are not done in Jaguar2 on packets forwarded to the CPU */
        if ((message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC || message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_P_DELAY_RESP) && ts_props.delay_comp.asymmetry_cnt != 0) {
            *rxTime = *rxTime - ts_props.delay_comp.asymmetry_cnt;
        }
    }
    return VTSS_RC_OK;
}

static u32 lan966x_cpu_fwd_mask_get(vtss_packet_reg_type_t type, BOOL redir, u32 i)
{
    u32 mask;

    /* Map NORMAL to CPU_ONLY/FORWARD */
    if (type == VTSS_PACKET_REG_NORMAL) {
        type = (redir ? VTSS_PACKET_REG_CPU_ONLY : VTSS_PACKET_REG_FORWARD);
    }

    if (type == VTSS_PACKET_REG_CPU_ONLY) {
         /* Set REDIR bit */
        mask = VTSS_BIT(i);
    } else if (type == VTSS_PACKET_REG_DISCARD) {
        /* Set DROP bit */
        mask = VTSS_BIT(i + 16);
    } else if (type == VTSS_PACKET_REG_CPU_COPY) {
        /* Set REDIR and DROP bits */
        mask = (VTSS_BIT(i) | VTSS_BIT(i + 16));
    } else {
        /* No bits set for VTSS_PACKET_REG_FORWARD */
        mask = 0;
    }
    return mask;
}

static u32 lan966x_ifh_get(const u8 *ifh, u32 pos, u32 len)
{
    u32 i, j, k, v = 0, val = 0;

    for (i = 0; i < len; i++) {
        j = (pos + i);
        k = (j % 8);
        if (i == 0 || k == 0) {
            // Read IFH byte
            v = ifh[LAN966X_IFH_SIZE - (j / 8) - 1];
        }
        if (v & (1 << k)) {
            val |= (1 << i);
        }
    }
    return val;
}

static void lan966x_ifh_set(u8 *ifh, u32 pos, u32 len, u32 val)
{
    u32 i, j, k, v = 0;

    for (i = 0; i < len; i++) {
        j = (pos + i);
        k = (j % 8);
        if (i == 0 || k == 0) {
            // Read IFH byte
            v = ifh[LAN966X_IFH_SIZE - (j / 8) - 1];
        }
        if (val & (1 << i)) {
            v |= (1 << k);
        }
        if (i == (len - 1) || k == 7) {
            // Write IFH byte
            ifh[LAN966X_IFH_SIZE - (j / 8) - 1] = v;
        }
    }
}

#define IFH_GET(ifh, fld)      lan966x_ifh_get(ifh, IFH_POS_##fld, IFH_WID_##fld)
#define IFH_SET(iff, fld, val) lan966x_ifh_set(ifh, IFH_POS_##fld, IFH_WID_##fld, val)

static vtss_rc lan966x_rx_hdr_decode(const vtss_state_t          *const state,
                                     const vtss_packet_rx_meta_t *const meta,
                                     const u8                           ifh[VTSS_PACKET_HDR_SIZE_BYTES],
                                     vtss_packet_rx_info_t *const info)
{
    u32 port, tci;

    VTSS_MEMSET(info, 0, sizeof(*info));
    info->length = meta->length;

    // Ingress port
    port = IFH_GET(ifh, SRCPORT);
    info->port_no = vtss_cmn_chip_to_logical_port(state, 0, port);
    if (info->port_no == VTSS_PORT_NO_NONE) {
        VTSS_EG(VTSS_TRACE_GROUP_PACKET, "Unknown port: %u", port);
        return VTSS_RC_ERROR;
    }

    // Tag information
    tci = IFH_GET(ifh, TCI);
    info->tag.pcp = VTSS_EXTRACT_BITFIELD(tci, 13, 3);
    info->tag.dei = VTSS_EXTRACT_BITFIELD(tci, 12, 1);
    info->tag.vid = VTSS_EXTRACT_BITFIELD(tci, 0, 12);
    VTSS_RC(vtss_cmn_packet_hints_update(state, VTSS_TRACE_GROUP_PACKET, meta->etype, info));

    // CPU queue, priority, ACL hit
    info->xtr_qu_mask = IFH_GET(ifh, CPUQ);
    info->cos = IFH_GET(ifh, QOS_CLASS);
    info->acl_hit = IFH_GET(ifh, ACL_HIT);

    // Timestamp
    // hw_tstamp 48bits NS + 16 Sub-NS.    TIMESTAMP: 30bits NS + 2 Sub-NS
    info->hw_tstamp = (u64)(IFH_GET(ifh, TIMESTAMP)) << 14;
    info->hw_tstamp_decoded = TRUE;

    // sFlow ID
    port = IFH_GET(ifh, SFLOW_ID);
    if (port == (VTSS_CHIP_PORTS + 1)) {
        info->sflow_type    = VTSS_SFLOW_TYPE_RX;
        info->sflow_port_no = info->port_no;
    } else if (port < VTSS_CHIP_PORTS) {
        info->sflow_type    = VTSS_SFLOW_TYPE_TX;
        info->sflow_port_no = vtss_cmn_chip_to_logical_port(state, 0, port);
    }

    // Ingress flow
    info->iflow_id = IFH_GET(ifh, ISDX);

    return VTSS_RC_OK;
}

static u32 pdu_type_calc(const vtss_packet_tx_info_t *const info)
{
    switch (info->oam_type) {
    case VTSS_PACKET_OAM_TYPE_NONE:       break;  // Do nothing
    case VTSS_PACKET_OAM_TYPE_CCM:        return 1;
    case VTSS_PACKET_OAM_TYPE_MRP_TST:    return 2;
    case VTSS_PACKET_OAM_TYPE_MRP_ITST:   return 3;
    case VTSS_PACKET_OAM_TYPE_DLR_BCN:    return 4;
    case VTSS_PACKET_OAM_TYPE_DLR_ADV:    return 5;
    case VTSS_PACKET_OAM_TYPE_MPLS_TP_1:  return 0;  // Not supported
    case VTSS_PACKET_OAM_TYPE_MPLS_TP_2:  return 0;  // Not supported
    default:                              return 9;  // Y1731_NON_CCM
    }

    if (info->ptp_action != VTSS_PACKET_PTP_ACTION_NONE) {
        if (info->inj_encap.type == VTSS_PACKET_ENCAP_TYPE_IP4) {
            return 7;
        }
        if (info->inj_encap.type == VTSS_PACKET_ENCAP_TYPE_IP6) {
            return 8;
        }
    }

    return 0;
}

#if defined(VTSS_FEATURE_VOP)
static u32 seq_num_oam_calc(vtss_packet_oam_type_t oam_type, u32 chip_port)
{
    switch (oam_type) {
    case VTSS_PACKET_OAM_TYPE_CCM:      return chip_port;   /* VOP sequence numbers */
    case VTSS_PACKET_OAM_TYPE_DLR_BCN:
    case VTSS_PACKET_OAM_TYPE_DLR_ADV:  return VTSS_VOE_CNT + chip_port;   /* DLR sequence numbers */
    case VTSS_PACKET_OAM_TYPE_MRP_TST:
    case VTSS_PACKET_OAM_TYPE_MRP_ITST: return (VTSS_VOE_CNT*2) + (VTSS_VOE_CNT*2) + chip_port;   /* MRP sequence numbers */
    default:
        VTSS_E("Invalid oam_type (%u)", oam_type);
    }
    return 0;
}
#endif

static vtss_rc lan966x_tx_hdr_encode(vtss_state_t          *const state,
                                     const vtss_packet_tx_info_t *const info,
                                     u8                    *const ifh,
                                     u32                   *const ifh_len)
{
    vtss_port_no_t port_no;
    u32            port, dst_mask, mask = 0, pop_cnt = 0, rew_cmd = 0, tci, cos, etype_ofs;
#if defined(VTSS_FEATURE_VOP)
    u32            seq_num_chip_port = 0;
#endif
        const vtss_vlan_tag_t *tag = &info->tag;

    if (ifh == NULL) {
        *ifh_len = LAN966X_IFH_SIZE;
        return VTSS_RC_OK;
    } else if (*ifh_len < LAN966X_IFH_SIZE) {
        return VTSS_RC_ERROR;
    }

    if ((info->oam_type != VTSS_PACKET_OAM_TYPE_NONE) && (info->ptp_action != VTSS_PACKET_PTP_ACTION_NONE)) {
        VTSS_E("Invalid PDU type indication oam_type %u  ptp_action %u", info->oam_type, info->ptp_action);
        return VTSS_RC_ERROR;
    }

    *ifh_len = LAN966X_IFH_SIZE;
    VTSS_MEMSET(ifh, 0, LAN966X_IFH_SIZE);

    if (info->switch_frm) {
        port_no = info->masquerade_port;
        if (port_no != VTSS_PORT_NO_NONE) {
            if (port_no <= state->port_count) {
                port = VTSS_CHIP_PORT_FROM_STATE(state, port_no);
                IFH_SET(ifh, MASQ, 1);
                IFH_SET(ifh, MASQ_PORT, port);
            } else {
                VTSS_E("Invalid masquerade port (%u)", port_no);
                return VTSS_RC_ERROR;
            }
        }
        if (tag->tpid) {
            // Pop one tag, expected inserted by application
            pop_cnt = 1;
        }
    } else {
        IFH_SET(ifh, BYPASS, 1);

        // Destination port mask, including CPU mirroring
        dst_mask = info->dst_port_mask;
        port_no = state->l2.mirror_conf.port_no;
        if (port_no < state->port_count && state->l2.mirror_cpu_ingress) {
            dst_mask |= VTSS_BIT(port_no);
        }
        for (port_no = 0; port_no < state->port_count; port_no++) {
            if (dst_mask & (1 << port_no)) {
#if defined(VTSS_FEATURE_VOP)
                seq_num_chip_port = VTSS_CHIP_PORT_FROM_STATE(state, port_no);
#endif
                mask |= VTSS_BIT(VTSS_CHIP_PORT_FROM_STATE(state, port_no));
            }
        }
        IFH_SET(ifh, DSTS, mask);

        // PTP rewrite operations
        switch (info->ptp_action) {
        case VTSS_PACKET_PTP_ACTION_ONE_STEP:
            rew_cmd = 1;
            break;
        case VTSS_PACKET_PTP_ACTION_TWO_STEP:
            rew_cmd = 4;
            break;
        case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP:
            rew_cmd = 3;
            break;
        case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ:
            rew_cmd = 7;
            break;
        case VTSS_PACKET_PTP_ACTION_AFI_NONE:
            rew_cmd = 12;
            break;
        default:
            if (tag->tpid != 0 || tag->vid == VTSS_VID_NULL) {
                // Disable rewriter
                pop_cnt = 3;
            }
            break;
        }
        if (rew_cmd) {
            IFH_SET(ifh, REW_CMD, (info->ptp_domain << 6) | rew_cmd);
        }

        IFH_SET(ifh, PDU_TYPE, pdu_type_calc(info));

        etype_ofs = 0;
        if (info->inj_encap.type == VTSS_PACKET_ENCAP_TYPE_NONE) {
            if (info->pdu_offset > 14) {
                etype_ofs = (info->pdu_offset - 14) / 4;
            }
        } else {
            etype_ofs = MIN(3, info->inj_encap.tag_count);
        }
        IFH_SET(ifh, ETYPE_OFS, etype_ofs);

#if defined(VTSS_FEATURE_VOP)
        if (info->oam_type != VTSS_PACKET_OAM_TYPE_NONE) {
            IFH_SET(ifh, REW_OAM, 1);
            IFH_SET(ifh, SEQ_NUM, seq_num_oam_calc(info->oam_type, seq_num_chip_port)); /* Point to the sequence number update configuration */

            if (info->oam_type == VTSS_PACKET_OAM_TYPE_CCM     ||
                info->oam_type == VTSS_PACKET_OAM_TYPE_MRP_TST ||
                info->oam_type == VTSS_PACKET_OAM_TYPE_MRP_ITST) {
                // Don't set "do not rewrite", because then some fields of the
                // MRP_[In]Test PDUs won't get updated in that case.
                pop_cnt = 0;
            }
        } else {
            if ((info->ptp_action == VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ) ||
                (info->ptp_action == VTSS_PACKET_PTP_ACTION_AFI_NONE)) {
                /* The VOP and DLR requires a 32 bit counter. MRP and PT requires 16 bit sequence number */
                /* The PTP sequence numbers are last after VOP, DLR and MRP */
                /* In case of PTP frame the SEQ_NUM field is indexing every 16 bit field in the PTP_SEQ_NO configuration - see VML */
                IFH_SET(ifh, SEQ_NUM, ((VTSS_VOE_CNT*2) + (VTSS_VOE_CNT*2) + VTSS_VOE_CNT) + info->sequence_idx);
            }
        }
#endif

#if defined(VTSS_AFI_V2)
        // AFI
        if (info->afi_id != VTSS_AFI_ID_NONE) {
            IFH_SET(ifh, AFI, 1);
        }
#endif

        // DP and priority
        IFH_SET(ifh, DP, info->dp);
        cos = (info->cos >= 8 ? 7 : info->cos);
        IFH_SET(ifh, QOS_CLASS, cos);
        IFH_SET(ifh, IPV, cos);

        // TCI
        tci = (tag->tpid == 0 || tag->tpid == 0x8100 ? 0 : 1); // Tag type
        tci = ((tci << 16) | (tag->pcp << 13) | (tag->dei << 12) | tag->vid);
        IFH_SET(ifh, TCI, tci);
    }
    IFH_SET(ifh, TIMESTAMP, ((info->ptp_timestamp>>14) & 0xFFFFFFFFFF)); // TS = 32 bits PTP time stamp. Two bits sub nano

    IFH_SET(ifh, POP_CNT, pop_cnt);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_packet_mode_update(vtss_state_t *vtss_state)
{
    u32 byte_swap;
#ifdef VTSS_OS_BIG_ENDIAN
    byte_swap = 0;
#else
    byte_swap = 1;
#endif

    if (!vtss_state->packet.manual_mode) {
        /* Change mode to manual extraction and injection */
        vtss_state->packet.manual_mode = 1;
        REG_WR(QS_XTR_GRP_CFG(0),
               QS_XTR_GRP_CFG_MODE(1) |
               QS_XTR_GRP_CFG_BYTE_SWAP(byte_swap));
        REG_WR(QS_INJ_GRP_CFG(0),
               QS_INJ_GRP_CFG_MODE(1) |
               QS_INJ_GRP_CFG_BYTE_SWAP(byte_swap));
        REG_WR(SYS_PORT_MODE(VTSS_CHIP_PORT_CPU_0),
               SYS_PORT_MODE_INCL_XTR_HDR(1) |
               SYS_PORT_MODE_INCL_INJ_HDR(1));
    }
    return VTSS_RC_OK;
}

#ifdef VTSS_OS_BIG_ENDIAN
#define XTR_EOF_0          0x80000000U
#define XTR_EOF_1          0x80000001U
#define XTR_EOF_2          0x80000002U
#define XTR_EOF_3          0x80000003U
#define XTR_PRUNED         0x80000004U
#define XTR_ABORT          0x80000005U
#define XTR_ESCAPE         0x80000006U
#define XTR_NOT_READY      0x80000007U
#define XTR_VALID_BYTES(x) (4 - ((x) & 3))
#else
#define XTR_EOF_0          0x00000080U
#define XTR_EOF_1          0x01000080U
#define XTR_EOF_2          0x02000080U
#define XTR_EOF_3          0x03000080U
#define XTR_PRUNED         0x04000080U
#define XTR_ABORT          0x05000080U
#define XTR_ESCAPE         0x06000080U
#define XTR_NOT_READY      0x07000080U
#define XTR_VALID_BYTES(x) (4 - (((x) >> 24) & 3))
#endif

static vtss_rc lan966x_rx_frame_discard_grp(vtss_state_t *vtss_state, const vtss_packet_rx_grp_t xtr_grp)
{
    BOOL done = FALSE;

    while (!done) {
        u32 val;
        REG_RD(QS_XTR_RD(xtr_grp), &val);
        switch(val) {
        case XTR_ABORT:
        case XTR_PRUNED:
        case XTR_EOF_3:
        case XTR_EOF_2:
        case XTR_EOF_1:
        case XTR_EOF_0:
            REG_RD(QS_XTR_RD(xtr_grp), &val); /* Last data */
            done = TRUE;        /* Last 1-4 bytes */
            break;
        case XTR_ESCAPE:
            REG_RD(QS_XTR_RD(xtr_grp), &val); /* Escaped data */
            break;
        case XTR_NOT_READY:
        default:
          break;
        }
    }
    return VTSS_RC_OK;
}

/**
 * Return values:
 *  0 = Data OK.
 *  1 = EOF reached. Data OK. bytes_valid indicates the number of valid bytes in last word ([1; 4]).
 *  2 = Error. No data from queue system.
 */
static int lan966x_rx_frame_word(vtss_state_t *vtss_state,
                                 vtss_packet_rx_grp_t grp, BOOL first_word, u32 *rval, u32 *bytes_valid)
{
    u32 val;

    REG_RD(QS_XTR_RD(grp), &val);
    if (val == XTR_NOT_READY) {
        /** XTR_NOT_READY means two different things depending on whether this is the first
         * word read of a frame or after at least one word has been read.
         * When the first word, the group is empty, and we return an error.
         * Otherwise we have to wait for the FIFO to have received some more data. */
        if (first_word) {
            return 2; /* Error */
        }
        do {
            REG_RD(QS_XTR_RD(grp), &val);
        } while (val == XTR_NOT_READY);
    }

    switch(val) {
    case XTR_ABORT:
        /* No accompanying data. */
        VTSS_E("Aborted frame");
        return 2; /* Error */
    case XTR_EOF_0:
    case XTR_EOF_1:
    case XTR_EOF_2:
    case XTR_EOF_3:
    case XTR_PRUNED:
        *bytes_valid = XTR_VALID_BYTES(val);
        REG_RD(QS_XTR_RD(grp), &val);
        if (val == XTR_ESCAPE) {
            REG_RD(QS_XTR_RD(grp), rval);
        } else {
            *rval = val;
        }
        return 1; /* EOF */
    case XTR_ESCAPE:
        REG_RD(QS_XTR_RD(grp), rval);
        *bytes_valid = 4;
        return 0;
    default:
        *rval = val;
        *bytes_valid = 4;
        return 0;
    }
}

static vtss_rc lan966x_rx_frame_get_internal(vtss_state_t           *vtss_state,
                                             vtss_packet_rx_grp_t   grp,
                                             u32                    *const ifh,
                                             u8                     *const frame,
                                             const u32              buf_length,
                                             u32                    *frm_length) /* Including FCS */
{
    u32  i, val, bytes_got, bytes_valid, buf_len = buf_length;
    BOOL done = 0;
    u8   *buf;
    int  result;

    *frm_length = bytes_got = 0;

    /* Read IFH */
    for (i = 0; i < LAN966X_IFH_WORDS; i++) {
        if (lan966x_rx_frame_word(vtss_state, grp, TRUE, &val, &bytes_valid) != 0) {
            /* We accept neither EOF nor ERROR when reading the IFH */
            return VTSS_RC_ERROR;
        }
        ifh[i] = val;
    }

    buf = frame;

    /* Read the rest of the frame */
    while (!done && buf_len >= 4) {
        result = lan966x_rx_frame_word(vtss_state, grp, FALSE, &val, &bytes_valid);
        if (result == 2) {
            // Error.
            return VTSS_RC_ERROR;
        }
        // Store the data.
        bytes_got += bytes_valid;
#ifdef VTSS_OS_BIG_ENDIAN
        *buf++ = (u8)(val >> 24);
        *buf++ = (u8)(val >> 16);
        *buf++ = (u8)(val >>  8);
        *buf++ = (u8)(val >>  0);
#else
        *buf++ = (u8)(val >>  0);
        *buf++ = (u8)(val >>  8);
        *buf++ = (u8)(val >> 16);
        *buf++ = (u8)(val >> 24);
#endif
        buf_len -= bytes_valid;
        done = result == 1;
    }

    /* Updated received byte count */
    *frm_length = bytes_got;

    if (!done) {
        /* Buffer overrun. Skip remainder of frame */
        (void)lan966x_rx_frame_discard_grp(vtss_state, grp);
        return VTSS_RC_ERROR;
    }

    if (bytes_got < 60) {
        VTSS_E("short frame, %u bytes read", bytes_got);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_rx_frame(struct vtss_state_s  *vtss_state,
                                u8                   *const data,
                                const u32             buflen,
                                vtss_packet_rx_info_t *rx_info)
{
    vtss_rc rc = VTSS_RC_INCOMPLETE;
    u32     val;

    VTSS_RC(lan966x_packet_mode_update(vtss_state));

    /* Check if data is ready for grp */
    REG_RD(QS_XTR_DATA_PRESENT, &val);
    if (val) {
        u32 ifh[LAN966X_IFH_WORDS];
        u32 length;
        vtss_packet_rx_grp_t grp = VTSS_OS_CTZ(val);
        u8 xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES];
        vtss_packet_rx_meta_t meta;

        /* Get frame, separate IFH and frame data */
        VTSS_RC(lan966x_rx_frame_get_internal(vtss_state, grp, ifh, data, buflen, &length));

        /* IFH is done separately because of alignment needs */
        VTSS_MEMCPY(xtr_hdr, ifh, sizeof(ifh));
        VTSS_MEMSET(&meta, 0, sizeof(meta));
        meta.length = (length - 4);
        rc = lan966x_rx_hdr_decode(vtss_state, &meta, xtr_hdr, rx_info);
    }
    return rc;
}

static vtss_rc lan966x_inj_wr(vtss_state_t *vtss_state, u32 data)
{
    u32 cnt = 0, val;

    do {
        REG_RD(QS_INJ_STATUS, &val);
        cnt++;
        if (cnt == 10) {
            VTSS_E("FIFO not ready");
            return VTSS_RC_OK;
        }
    } while ((QS_INJ_STATUS_FIFO_RDY_X(val) & 0x1) == 0);
    REG_WR(QS_INJ_WR(0), data);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_tx_frame_ifh(vtss_state_t *vtss_state,
                                    const vtss_packet_tx_ifh_t *const ifh,
                                    const u8 *const frame,
                                    const u32 length)
{
    u32 val, w, count, last;
    const u8 *buf = frame;
    vtss_packet_tx_grp_t grp = 0;

    VTSS_RC(lan966x_packet_mode_update(vtss_state));

    if (ifh->length != LAN966X_IFH_SIZE) {
        return VTSS_RC_ERROR;
    }

    REG_RD(QS_INJ_STATUS, &val);
    if (!(QS_INJ_STATUS_FIFO_RDY_X(val) & VTSS_BIT(grp))) {
        VTSS_E("Not ready");
        return VTSS_RC_ERROR;
    }

    if (QS_INJ_STATUS_WMARK_REACHED_X(val) & VTSS_BIT(grp)) {
        VTSS_E("Watermark reached");
        return VTSS_RC_ERROR;
    }

    /* Indicate SOF */
    REG_WR(QS_INJ_CTRL(grp), QS_INJ_CTRL_GAP_SIZE(1) | QS_INJ_CTRL_SOF_M);

    // Write the IFH to the chip.
    for (w = 0; w < LAN966X_IFH_WORDS; w++) {
        VTSS_RC(lan966x_inj_wr(vtss_state, ifh->ifh[w]));
    }

    /* Write words, round up */
    count = ((length+3) / 4);
    last = length % 4;
    for (w = 0; w < count; w++, buf += 4) {
#ifdef VTSS_OS_BIG_ENDIAN
        val = ((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
#else
        val = ((buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
#endif
        VTSS_RC(lan966x_inj_wr(vtss_state, val));
    }

    /* Add padding */
    while (w < (60 / 4)) {
        VTSS_RC(lan966x_inj_wr(vtss_state, 0));
        w++;
    }

    /* Indicate EOF and valid bytes in last word */
    REG_WR(QS_INJ_CTRL(grp),
           QS_INJ_CTRL_GAP_SIZE(1) |
           QS_INJ_CTRL_VLD_BYTES(length < 60 ? 0 : last) |
           QS_INJ_CTRL_EOF_M);

    /* Add dummy CRC */
    VTSS_RC(lan966x_inj_wr(vtss_state, 0));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_rx_conf_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t      *conf = &vtss_state->packet.rx_conf;
    vtss_packet_rx_reg_t       *reg = &conf->reg;
    vtss_packet_rx_queue_map_t *map = &conf->map;
    u32                        queue, i, port, bpdu, garp, wm;
    vtss_port_no_t             port_no;
    vtss_packet_rx_port_conf_t *pc;

    // Each CPU queue gets reserved extraction buffer space. No sharing at port or buffer level
    for (queue = 0; queue < vtss_state->packet.rx_queue_count; queue++) {
        // Ressource 2 (memory per destination) starts at index 512
        i = (512 + VTSS_CHIP_PORT_CPU * VTSS_PRIOS + queue);
        wm = (conf->queue[queue].size / LAN966X_BUFFER_CELL_SZ);
        // Limit to maximum value with unit 1
        wm = MIN(wm, QSYS_RES_CFG_WM_HIGH_M / 2);
        REG_WR(QSYS_RES_CFG(i), wm);
    }
    // Nothing reserved at port level
    REG_WR(QSYS_RES_CFG(512 + 224  + VTSS_CHIP_PORT_CPU), 0);

    // Rx IPMC, BPDU and GARP registrations
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        pc = &vtss_state->packet.rx_port_conf[port_no];
        REG_WR(ANA_CPU_FWD_CFG(port),
               ((pc->ipmc_ctrl_reg == VTSS_PACKET_REG_NORMAL && reg->ipmc_ctrl_cpu_copy) ||
                pc->ipmc_ctrl_reg == VTSS_PACKET_REG_CPU_COPY ? ANA_CPU_FWD_CFG_IPMC_CTRL_COPY_ENA_M : 0) |
               ((pc->igmp_reg == VTSS_PACKET_REG_NORMAL && reg->igmp_cpu_only) ||
                pc->igmp_reg == VTSS_PACKET_REG_CPU_ONLY ? ANA_CPU_FWD_CFG_IGMP_REDIR_ENA_M : 0) |
               ((pc->mld_reg == VTSS_PACKET_REG_NORMAL && reg->mld_cpu_only) ||
                pc->mld_reg == VTSS_PACKET_REG_CPU_ONLY ? ANA_CPU_FWD_CFG_MLD_REDIR_ENA_M : 0));
        for (i = 0, bpdu = 0, garp = 0; i < 16; i++) {
            // Always discard Pause frames 01:80:C2:00:00:01
            bpdu |= lan966x_cpu_fwd_mask_get(i == 1 ? VTSS_PACKET_REG_DISCARD : pc->bpdu_reg[i], reg->bpdu_cpu_only, i);
            garp |= lan966x_cpu_fwd_mask_get(pc->garp_reg[i], reg->garp_cpu_only[i], i);
        }
        REG_WR(ANA_CPU_FWD_BPDU_CFG(port), bpdu);
        REG_WR(ANA_CPU_FWD_GARP_CFG(port), garp);
    }

    // CPU queues
    REG_WR(ANA_CPUQ_CFG,
           ANA_CPUQ_CFG_CPUQ_SFLOW(map->sflow_queue == VTSS_PACKET_RX_QUEUE_NONE ? 0 : map->sflow_queue) |
           ANA_CPUQ_CFG_CPUQ_MIRROR(map->mac_vid_queue) |
           ANA_CPUQ_CFG_CPUQ_LRN(map->learn_queue) |
           ANA_CPUQ_CFG_CPUQ_MAC_COPY(map->mac_vid_queue) |
           ANA_CPUQ_CFG_CPUQ_SRC_COPY(map->mac_vid_queue) |
           ANA_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE(map->mac_vid_queue) |
           ANA_CPUQ_CFG_CPUQ_ALLBRIDGE(map->bpdu_queue) |
           ANA_CPUQ_CFG_CPUQ_IPMC_CTRL(map->ipmc_ctrl_queue) |
           ANA_CPUQ_CFG_CPUQ_IGMP(map->igmp_queue) |
           ANA_CPUQ_CFG_CPUQ_MLD(map->igmp_queue));
    for (i = 0; i < 16; i++) {
        REG_WR(ANA_CPUQ_8021_CFG(i),
               ANA_CPUQ_8021_CFG_CPUQ_BPDU_VAL(map->bpdu_queue) |
               ANA_CPUQ_8021_CFG_CPUQ_GARP_VAL(map->garp_queue));
    }

    // NPI
    return lan966x_npi_mask_set(vtss_state);
}

#if VTSS_OPT_DEBUG_PRINT

/* - Debug print --------------------------------------------------- */

static vtss_rc lan966x_debug_pkt(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    u32  port, i;
    char buf[32];

    // Analyzer CPU forwarding registers
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "Port %u", port);
        vtss_lan966x_debug_reg_header(pr, buf);
        vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_CPU_FWD_CFG(port)), port, "FWD_CFG");
        vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_CPU_FWD_BPDU_CFG(port)), port, "BPDU_CFG");
        vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_CPU_FWD_GARP_CFG(port)), port, "GARP_CFG");
        pr("\n");
    }

    // Analyzer CPU queue mappings
    vtss_lan966x_debug_reg_header(pr, "CPU Queues");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(ANA_CPUQ_CFG), "CPUQ_CFG");
    for (i = 0; i < 16; i++) {
        vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_CPUQ_8021_CFG(i)), i, "CPUQ_8021_CFG");
    }
    pr("\n");

    // NPI port
    if (vtss_state->packet.npi_conf.enable) {
        vtss_lan966x_debug_reg_header(pr, "NPI");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(QSYS_EXT_CPU_CFG), "QSYS:EXT_CPU_CFG");
        port = VTSS_CHIP_PORT(vtss_state->packet.npi_conf.port_no);
        vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(SYS_PORT_MODE(port)), port, "SYS:PORT_MODE");
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_packet_debug_print(vtss_state_t *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_PACKET, lan966x_debug_pkt, vtss_state, pr, info);
}
#endif // VTSS_OPT_DEBUG_PRINT

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_packet_init(vtss_state_t *vtss_state)
{
    u32 pcp, dei, port = VTSS_CHIP_PORT_CPU;

    // Setup the CPU port as VLAN aware to support switching frames based on tags
    REG_WR(ANA_VLAN_CFG(port),
           ANA_VLAN_CFG_VLAN_AWARE_ENA_M  |
           ANA_VLAN_CFG_VLAN_POP_CNT(1) |
           ANA_VLAN_CFG_VLAN_VID(1));

    REG_WR(REW_PORT_CFG(port), REW_PORT_CFG_NO_REWRITE(1));

    // Disable learning (only RECV_ENA must be set)
    REG_WR(ANA_PORT_CFG(port), ANA_PORT_CFG_RECV_ENA_M);

    // Enable CPU port and disable againg
    REG_WRM(QSYS_SW_PORT_MODE(port),
            QSYS_SW_PORT_MODE_PORT_ENA_M | QSYS_SW_PORT_MODE_AGING_MODE(0),
            QSYS_SW_PORT_MODE_PORT_ENA_M | QSYS_SW_PORT_MODE_AGING_MODE_M);

    // Enable PCP classification for CPU port
    REG_WR(ANA_QOS_CFG(port), ANA_QOS_CFG_QOS_PCP_ENA_M);

    lan966x_packet_mode_update(vtss_state);

    // Set-up the one-to-one mapping between PCP and QoS class
    for (pcp = 0; pcp < 8; pcp++) {
        for (dei = 0; dei < 2; dei++) {
            REG_WR(ANA_PCP_DEI_CFG(port, (8 * dei + pcp)), ANA_PCP_DEI_CFG_QOS_PCP_DEI_VAL(pcp));
        }
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_packet_state_t *state = &vtss_state->packet;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->rx_conf_set = lan966x_rx_conf_set;
        state->rx_frame = lan966x_rx_frame;
        state->tx_frame_ifh = lan966x_tx_frame_ifh;
        state->rx_hdr_decode = lan966x_rx_hdr_decode;
        state->rx_ifh_size = LAN966X_IFH_SIZE;
        state->tx_hdr_encode = lan966x_tx_hdr_encode;
        state->npi_conf_set = lan966x_npi_conf_set;
        state->packet_phy_cnt_to_ts_cnt = lan966x_packet_phy_cnt_to_ts_cnt;
        state->packet_ns_to_ts_cnt = lan966x_packet_ns_to_ts_cnt;
        state->ptp_get_timestamp = lan966x_ptp_get_timestamp;
        state->rx_queue_count = VTSS_PACKET_RX_QUEUE_CNT;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan966x_packet_init(vtss_state));
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(lan966x_rx_conf_set(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
