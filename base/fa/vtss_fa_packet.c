// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)
#include "vtss_ts_api.h"

/* - CIL functions ------------------------------------------------- */

#define FA_IFH_WORDS (VTSS_FA_RX_IFH_SIZE / 4)    /* 9 32-bit words in an IFH */
#define FA_IFH_BYTES (VTSS_FA_RX_IFH_SIZE)        /* 36 bytes words in an IFH */

/* ================================================================= *
 *  NPI
 * ================================================================= */

static vtss_rc fa_npi_redirect_qu_to_port(vtss_state_t *vtss_state, vtss_packet_rx_queue_t qu, vtss_phys_port_no_t chip_port)
{
    REG_WRM(VTSS_QFWD_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_CPU_QU(qu)),
            VTSS_F_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL(chip_port),
            VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL);

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_FDMA) && VTSS_OPT_FDMA
static vtss_rc fa_fdma_qu_redirect_set(vtss_state_t *vtss_state, vtss_packet_rx_queue_t qu, vtss_phys_port_no_t chip_port)
{
    // If the NPI port has taken over the queue, simply cache the FDMA's wanted setting.
    BOOL npi_redirect = vtss_state->packet.npi_conf.port_no != VTSS_PORT_NO_NONE && vtss_state->packet.rx_conf.queue[qu].npi.enable;

    if (!npi_redirect) {
        // Not taken over by NPI. Do redirect to port specified by FDMA.
        VTSS_RC(fa_npi_redirect_qu_to_port(vtss_state, qu, chip_port));
    }

    // Remember the setting wanted by the FDMA.
    vtss_state->packet.default_qu_redirect[qu] = chip_port;

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_FDMA && VTSS_OPT_FDMA */

static vtss_rc fa_npi_mask_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t  *rx_conf  = &vtss_state->packet.rx_conf;
    vtss_npi_conf_t        *npi_conf = &vtss_state->packet.npi_conf;
    vtss_packet_rx_queue_t qu;

    for (qu = 0; qu < vtss_state->packet.rx_queue_count; qu++) {
        BOOL npi_redirect = npi_conf->port_no != VTSS_PORT_NO_NONE && rx_conf->queue[qu].npi.enable;

        VTSS_RC(fa_npi_redirect_qu_to_port(vtss_state, qu, npi_redirect ? VTSS_CHIP_PORT(npi_conf->port_no) : vtss_state->packet.default_qu_redirect[qu]));
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_npi_update(vtss_state_t *vtss_state)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;

    VTSS_RC(fa_npi_mask_set(vtss_state));

    if (conf->port_no != VTSS_PORT_NO_NONE) {
        u32 port = VTSS_CHIP_PORT(conf->port_no);

        // Control IFH insertion and parsing, use short prefix if enabled.
        REG_WRM(VTSS_REW_IFH_CTRL(port), VTSS_F_REW_IFH_CTRL_KEEP_IFH_SEL(conf->enable ? 2 : 0), VTSS_M_REW_IFH_CTRL_KEEP_IFH_SEL);
        REG_WRM(VTSS_ASM_PORT_CFG(port), VTSS_F_ASM_PORT_CFG_INJ_FORMAT_CFG(conf->enable ? 2 : 0), VTSS_M_ASM_PORT_CFG_INJ_FORMAT_CFG);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_npi_conf_set(vtss_state_t *vtss_state, const vtss_npi_conf_t *const new)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;

    // Disable current NPI port
    conf->enable = FALSE;
    VTSS_RC(fa_npi_update(vtss_state));

    // Set new NPI port
    *conf = *new;
    VTSS_RC(fa_npi_update(vtss_state));

    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc fa_packet_phy_cnt_to_ts_cnt(vtss_state_t  *vtss_state,
                                           u32           frame_cnt,
                                           u64           *ts_cnt)
{
    vtss_timestamp_t ts;
    u64              tc;
    u32              tod_cnt, diff;

    /* The frame_cnt parameter is a 32 bit wrapping nano second counter, extracted from the received packet (inserted by the PHY) */

    /* The time of day is sampled 2 or more times pr sec, assumed frame stamping belong to domain 0 */
    _vtss_ts_domain_timeofday_get(NULL, 0, &ts, &tc);
    tod_cnt = ts.nanoseconds + (VTSS_ONE_MIA * ts.seconds); /* tod_cnt is now a TOD 32 bit wrapping nano second counter */

    diff = tod_cnt - frame_cnt;             /* Calculate the difference between FRAME and TOD 32 bit wrapping nano second counter */
    *ts_cnt = tc - (u64)((u64)diff << 16);  /* Difference in 16 bit nano second fragments */
    VTSS_I("frame_cnt %u  tod_cnt %u  ts_cnt %" PRIu64 "  diff %u  ts.sec %u  ts.ns %u  tc %" PRIu64 "", frame_cnt, tod_cnt, *ts_cnt, diff, ts.seconds, ts.nanoseconds, tc);

    return VTSS_RC_OK;
}

static vtss_rc fa_packet_ns_to_ts_cnt(vtss_state_t  *vtss_state,
                                      u32           frame_ns,
                                      u64           *ts_cnt)
{
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
    } else {
        tod_ns = ts.nanoseconds;
    }

    diff = tod_ns - frame_ns;               /* Calculate the difference between FRAME and TOD 30 bit wrapping nano second counter */
    *ts_cnt = tc - (u64)((u64)diff << 16);  /* Difference in 16 bit nano second fragments */
    VTSS_I("frame_ns %u  tod_ns %u  ts_cnt %" PRIu64 "  diff %u  ts.sec %u  ts.ns %u  tc %" PRIu64 "", frame_ns, tod_ns, *ts_cnt, diff, ts.seconds, ts.nanoseconds, tc);

    return VTSS_RC_OK;
}

static u32 fa_packet_unpack32(const u8 *buf)
{
    return (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + buf[3];
}

static vtss_rc fa_ptp_get_timestamp(vtss_state_t                    *vtss_state,
                                    const u8                        *const frm,
                                    const vtss_packet_rx_info_t     *const rx_info,
                                    vtss_packet_ptp_message_type_t  message_type,
                                    vtss_packet_timestamp_props_t   ts_props,
                                    u64                             *ts_cnt,
                                    BOOL                            *timestamp_ok)
{
    if (ts_props.ts_feature_is_PTS) {
        u32 packet_ns = fa_packet_unpack32(frm);
        if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_30BIT) {
            /* convert to jaguar 32 bit NSF */
            VTSS_D("ts_cnt before %u", packet_ns);
            (void)fa_packet_ns_to_ts_cnt(vtss_state, packet_ns, ts_cnt);
            VTSS_D("ts_cnt after %" PRIu64, *ts_cnt);
            *timestamp_ok = rx_info->hw_tstamp_decoded;
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_32BIT) {
            /* convert to jaguar 32 bit NSF */
            VTSS_D("ts_cnt before %u", packet_ns);
            (void)fa_packet_phy_cnt_to_ts_cnt(vtss_state, packet_ns, ts_cnt);
            VTSS_D("ts_cnt after %" PRIu64, *ts_cnt);
            *timestamp_ok = rx_info->hw_tstamp_decoded;
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_44BIT) {
            VTSS_I("ts_cnt can not be retrieved from the packet supress warning for mode %d ", ts_props.phy_ts_mode);
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_48BIT) {
            VTSS_I("ts_cnt can not be retrieved from the packet supress warning for mode %d ", ts_props.phy_ts_mode);
        } else {
            VTSS_I("PHY timestamp mode %d not supported", ts_props.phy_ts_mode);
        }
    } else {
        /* The hw_tstamp is a tc in 16 bit nano second fragments (46 (30 bits nsec + 16 bits sub nsec) wrapping) */
        *ts_cnt = rx_info->hw_tstamp;
        *timestamp_ok = rx_info->hw_tstamp_decoded;
        /* if Sync message then subtract the p2p delay from rx time  */
        if (message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC) {
            *ts_cnt = *ts_cnt - ts_props.delay_comp.delay_cnt;
        }
        /* link asymmetry compensation for Sync and PdelayResp events are not done in Jaguar2 on packets forwarded to the CPU */
        if ((message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC || message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_P_DELAY_RESP) && ts_props.delay_comp.asymmetry_cnt != 0) {
            *ts_cnt = *ts_cnt - ts_props.delay_comp.asymmetry_cnt;
        }
    }
    return VTSS_RC_OK;
}

/* Setup L2CP Profile */
vtss_rc vtss_fa_l2cp_conf_set(vtss_state_t *vtss_state, u32 profile, u32 l2cp, vtss_fa_l2cp_conf_t *conf)
{
    u32 reg;

    switch (conf->reg) {
    case VTSS_PACKET_REG_DISCARD:
        reg = 3;
        break;
    case VTSS_PACKET_REG_CPU_COPY:
        reg = 2;
        break;
    case VTSS_PACKET_REG_CPU_ONLY:
        reg = 1;
        break;
    case VTSS_PACKET_REG_FORWARD:
    default:
        reg = 0;
        break;
    }
    REG_WR(VTSS_ANA_CL_L2CP_ENTRY_CFG(profile * 32 + l2cp),
           VTSS_F_ANA_CL_L2CP_ENTRY_CFG_COSID_VAL(conf->cosid) |
           VTSS_F_ANA_CL_L2CP_ENTRY_CFG_COSID_ENA(conf->cosid_enable ? 1 : 0) |
           VTSS_F_ANA_CL_L2CP_ENTRY_CFG_CPU_FWD_CFG(reg) |
           VTSS_F_ANA_CL_L2CP_ENTRY_CFG_CPU_L2CP_QU(conf->queue));
    return VTSS_RC_OK;
}

static vtss_rc fa_rx_conf_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t      *conf = &vtss_state->packet.rx_conf;
    vtss_packet_rx_reg_t       *reg = &conf->reg;
    vtss_packet_rx_queue_map_t *map = &conf->map;
    vtss_packet_rx_port_conf_t *port_conf;
    vtss_port_no_t             port_no;
    u32                        port, i, j, cap_cfg, queue;
    BOOL                       cpu_only;
    vtss_fa_l2cp_conf_t        l2cp_conf;

    // Each CPU queue gets reserved extraction buffer space. No sharing at port or buffer level
    for (queue = 0; queue < vtss_state->packet.rx_queue_count; queue++) {
        REG_WR(VTSS_QRES_RES_CFG(2048 /* egress */ + VTSS_CHIP_PORT_CPU * VTSS_PRIOS + queue), conf->queue[queue].size / FA_BUFFER_CELL_SZ);
    }
    REG_WR(VTSS_QRES_RES_CFG(2048 /* egress */ + 560 /* per-port reservation */ + VTSS_CHIP_PORT_CPU), 0); // No extra shared space at port level

    // Setup Rx registrations that we only have per-switch API support for (not per-port)
    cap_cfg = VTSS_F_ANA_CL_CAPTURE_CFG_CPU_MLD_REDIR_ENA  (reg->mld_cpu_only)       |
              VTSS_F_ANA_CL_CAPTURE_CFG_CPU_IP4_MC_COPY_ENA(reg->ipmc_ctrl_cpu_copy) |
              VTSS_F_ANA_CL_CAPTURE_CFG_CPU_IGMP_REDIR_ENA (reg->igmp_cpu_only);

    // Setup Rx registrations that we have per-port
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        port_conf = &vtss_state->packet.rx_port_conf[port_no];

        for (i = 0; i < 32; i++) {
            if (i < 16) {
                // BPDU
                j = i;
                l2cp_conf.reg = port_conf->bpdu_reg[j];
                cpu_only = reg->bpdu_cpu_only;
                l2cp_conf.queue = map->bpdu_queue;
                l2cp_conf.cosid_enable = port_conf->bpdu[j].cosid_enable;
                l2cp_conf.cosid = port_conf->bpdu[j].cosid;
            } else {
                // GARP
                j = (i - 16);
                l2cp_conf.reg = port_conf->garp_reg[j];
                cpu_only = reg->garp_cpu_only[j];
                l2cp_conf.queue = map->garp_queue;
                l2cp_conf.cosid_enable = port_conf->garp[j].cosid_enable;
                l2cp_conf.cosid = port_conf->garp[j].cosid;
            }
            if (l2cp_conf.reg == VTSS_PACKET_REG_NORMAL) {
                // Use global registration
                l2cp_conf.reg = (cpu_only ? VTSS_PACKET_REG_CPU_ONLY : VTSS_PACKET_REG_FORWARD);
            }
            /* Use L2CP profile 64-128 for ports */
            VTSS_RC(vtss_fa_l2cp_conf_set(vtss_state, port + 64, i, &l2cp_conf));
        }
        REG_WR(VTSS_ANA_CL_CAPTURE_CFG(port), cap_cfg);
    }

    // IGMP and IPMC queues:
    REG_WR(VTSS_ANA_CL_CPU_PROTO_QU_CFG,
           VTSS_F_ANA_CL_CPU_PROTO_QU_CFG_CPU_IP6_MC_CTRL_QU(map->ipmc_ctrl_queue) |
           VTSS_F_ANA_CL_CPU_PROTO_QU_CFG_CPU_MLD_QU        (map->igmp_queue) |
           VTSS_F_ANA_CL_CPU_PROTO_QU_CFG_CPU_IP4_MC_CTRL_QU(map->ipmc_ctrl_queue) |
           VTSS_F_ANA_CL_CPU_PROTO_QU_CFG_CPU_IGMP_QU       (map->igmp_queue));

    // Learn queue:
    REG_WRM(VTSS_ANA_L2_LRN_CFG,
            VTSS_F_ANA_L2_LRN_CFG_CPU_LRN_QU(map->learn_queue),
            VTSS_M_ANA_L2_LRN_CFG_CPU_LRN_QU);

    // Enable forwarding to CPU of MAC-table SMAC hits, where the MAC-table entry has the CPU_COPY flag set.
    REG_WRM(VTSS_ANA_L2_LRN_CFG,
            VTSS_F_ANA_L2_LRN_CFG_CPU_SMAC_COPY_ENA(1),
            VTSS_M_ANA_L2_LRN_CFG_CPU_SMAC_COPY_ENA);

    // sFlow queue:
    if (map->sflow_queue != VTSS_PACKET_RX_QUEUE_NONE) {
        REG_WRM(VTSS_ANA_AC_PS_COMMON_SFLOW_CFG,
                VTSS_F_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU(map->sflow_queue),
                VTSS_M_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU);
    }

    // Configure L3 routing CPU queues
    REG_WR(VTSS_ANA_L3_CPU_QU_CFG,
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_QU            (map->l3_uc_queue)    |
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_OPT_QU     (map->l3_other_queue) |
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_HDR_FAIL_QU(map->l3_other_queue) |
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_SIP_RPF_QU         (map->l3_other_queue) |
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_IP_LEN_QU          (map->l3_other_queue) |
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_MC_FAIL_QU         (map->l3_other_queue) |
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_UC_FAIL_QU         (map->l3_uc_queue)    |
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_IP_TTL_FAIL_QU     (map->l3_other_queue));

    // Configure Rx Queue #i to map to an Rx group.
    for (i = 0; i < vtss_state->packet.rx_queue_count; i++) {
        if (conf->grp_map[i]) {
            VTSS_E("Attempt to redirect queue %d - use vtss_dma_conf_set() instead", i);
        }
    }

    VTSS_RC(fa_npi_mask_set(vtss_state));

    return VTSS_RC_OK;
}

static vtss_rc fa_packet_mode_update(vtss_state_t *vtss_state)
{
    u32 queue, byte_swap, port = VTSS_CHIP_PORT_CPU_1, grp = 1;
#ifdef VTSS_OS_BIG_ENDIAN
    byte_swap = 0;
#else
    byte_swap = 1;
#endif

    if (!vtss_state->packet.manual_mode) {
        /* Change mode to manual extraction and injection */
        vtss_state->packet.manual_mode = 1;
        REG_WR(VTSS_DEVCPU_QS_XTR_GRP_CFG(grp),
               VTSS_F_DEVCPU_QS_XTR_GRP_CFG_MODE(1) |
               VTSS_F_DEVCPU_QS_XTR_GRP_CFG_STATUS_WORD_POS(0) |
               VTSS_F_DEVCPU_QS_XTR_GRP_CFG_BYTE_SWAP(byte_swap));
        REG_WR(VTSS_DEVCPU_QS_INJ_GRP_CFG(grp),
               VTSS_F_DEVCPU_QS_INJ_GRP_CFG_MODE(1) |
               VTSS_F_DEVCPU_QS_INJ_GRP_CFG_BYTE_SWAP(byte_swap));
        REG_WR(VTSS_ASM_PORT_CFG(port),
               VTSS_F_ASM_PORT_CFG_NO_PREAMBLE_ENA(1) |
               VTSS_F_ASM_PORT_CFG_INJ_FORMAT_CFG(1));
        for (queue = 0; queue < vtss_state->packet.rx_queue_count; queue++) {
            REG_WRM(VTSS_QFWD_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_CPU_QU(queue)),
                    VTSS_F_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL(port),
                    VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL);
            vtss_state->packet.default_qu_redirect[queue] = port;
        }
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

static vtss_rc fa_rx_frame_discard_grp(vtss_state_t *vtss_state, const vtss_packet_rx_grp_t xtr_grp)
{
    BOOL done = FALSE;
    u32  val;

    while (!done) {
        REG_RD(VTSS_DEVCPU_QS_XTR_RD(xtr_grp), &val);
        switch (val) {
        case XTR_ABORT:
        case XTR_PRUNED:
        case XTR_EOF_3:
        case XTR_EOF_2:
        case XTR_EOF_1:
        case XTR_EOF_0:
            REG_RD(VTSS_DEVCPU_QS_XTR_RD(xtr_grp), &val); /* Last data */
            done = TRUE;        /* Last 1-4 bytes */
            break;
        case XTR_ESCAPE:
            REG_RD(VTSS_DEVCPU_QS_XTR_RD(xtr_grp), &val); /* Escaped data */
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
static int fa_rx_frame_word(vtss_state_t *vtss_state, vtss_packet_rx_grp_t grp, BOOL first_word, u32 *rval, u32 *bytes_valid)
{
    u32 val;

    REG_RD(VTSS_DEVCPU_QS_XTR_RD(grp), &val);

    if (val == XTR_NOT_READY) {
        /** XTR_NOT_READY means two different things depending on whether this is the first
         * word read of a frame or after at least one word has been read.
         * When the first word, the group is empty, and we return an error.
         * Otherwise we have to wait for the FIFO to have received some more data. */
        if (first_word) {
            return 2; /* Error */
        }
        do {
            REG_RD(VTSS_DEVCPU_QS_XTR_RD(grp), &val);
        } while (val == XTR_NOT_READY);
    }

    switch (val) {
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
        REG_RD(VTSS_DEVCPU_QS_XTR_RD(grp), &val);
        if (val == XTR_ESCAPE) {
            REG_RD(VTSS_DEVCPU_QS_XTR_RD(grp), rval);
        } else {
            *rval = val;
        }
        return 1; /* EOF */
    case XTR_ESCAPE:
        REG_RD(VTSS_DEVCPU_QS_XTR_RD(grp), rval);
        *bytes_valid = 4;
        return 0;
    default:
        *rval = val;
        *bytes_valid = 4;
        return 0;
    }
}

static vtss_rc fa_rx_frame_get_internal(vtss_state_t           *vtss_state,
                                        vtss_packet_rx_grp_t   grp,
                                        u32                    *const ifh,
                                        u8                     *const frame,
                                        const u32              buf_length,
                                        u32                    *frm_length) /* Including FCS */
{
    u32     i, val, bytes_got, bytes_valid, buf_len = buf_length;
    BOOL    done = 0;
    u8      *buf;
    int     result;

    *frm_length = bytes_got = 0;

    /* Read IFH words */
    for (i = 0; i < FA_IFH_WORDS; i++) {
        if (fa_rx_frame_word(vtss_state, grp, TRUE, &val, &bytes_valid) != 0) {
            /* We accept neither EOF nor ERROR when reading the IFH */
            return VTSS_RC_ERROR;
        }
        ifh[i] = val;
    }

    buf = frame;

    /* Read the rest of the frame */
    while (!done && buf_len >= 4) {
        result = fa_rx_frame_word(vtss_state, grp, FALSE, &val, &bytes_valid);
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
        (void)fa_rx_frame_discard_grp(vtss_state, grp);
        return VTSS_RC_ERROR;
    }

    if (bytes_got < 60) {
        VTSS_E("short frame, %u bytes read", bytes_got);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

#define VSTAX 73 /* The IFH bit position of the first VSTAX bit. This is because the VSTAX bit positions in Data sheet is starting from zero. */

static vtss_rc fa_rx_hdr_decode(const vtss_state_t          *const state,
                                const vtss_packet_rx_meta_t *const meta,
                                const u8                           xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                vtss_packet_rx_info_t       *const info)
{
    u16                 vstax_hi, vstax_one;
    u32                 fwd, misc, sflow_id;
    u64                 tstamp, dst, vstax_lo;
    u8                  xtr_hdr_2;
    vtss_phys_port_no_t chip_port;
    vtss_trace_group_t  trc_grp = VTSS_TRACE_GROUP_PACKET;

    VTSS_DG(trc_grp, "IFH (36 bytes) + bit of packet:");
    VTSS_DG_HEX(trc_grp, &xtr_hdr[0], 96);
    // Bit 287-272 (16 bits) are unused

    // TS is bit 232-271
    xtr_hdr_2 = xtr_hdr[ 2] & 0x3F;  /* For some reason bit6-7 is occasionally unexpectedly set. Must be cleared */
    tstamp    = ((u64)xtr_hdr_2 << 32);
    tstamp   |= ((u64)xtr_hdr[ 3] << 24) | ((u64)xtr_hdr[ 4] << 16) | ((u64)xtr_hdr[ 5] <<  8) | ((u64)xtr_hdr[ 6] <<  0);

    // DST is bit 153-231 (79 bits), but we only read the 63 LSB for now
    dst       = ((u64)xtr_hdr[ 9] << 56) | ((u64)xtr_hdr[10] << 48) | ((u64)xtr_hdr[11] << 40) | ((u64)xtr_hdr[12] << 32);
    dst      |= ((u64)xtr_hdr[13] << 24) | ((u64)xtr_hdr[14] << 16) | ((u64)xtr_hdr[15] <<  8) | ((u64)xtr_hdr[16] <<  0);
    vstax_one = (dst & 1); // Bit 152 is the MSB of VSTAX, which must be 1
    dst       = (dst >> 1);

    // VSTAX is bit 73-152 (80 bits), but we skip bit 63 for now (bit 79 is read above)
    vstax_hi  =                                                       ((u16)xtr_hdr[17] <<  8) | ((u16)xtr_hdr[18] <<  0);
    vstax_hi  = (vstax_hi >> 1);
    vstax_lo  = ((u64)xtr_hdr[19] << 56) | ((u64)xtr_hdr[20] << 48) | ((u64)xtr_hdr[21] << 40) | ((u64)xtr_hdr[22] << 32);
    vstax_lo |= ((u64)xtr_hdr[23] << 24) | ((u64)xtr_hdr[24] << 16) | ((u64)xtr_hdr[25] <<  8) | ((u64)xtr_hdr[26] <<  0);
    vstax_lo  = (vstax_lo >> 1);

    // FWD is bit 45-72 (28 bits), but we only read the 27 LSB for now
    fwd       = ((u32)xtr_hdr[27] << 24) | ((u32)xtr_hdr[28] << 16) | ((u32)xtr_hdr[29] <<  8) | ((u32)xtr_hdr[30] <<  0);
    fwd       = (fwd >> 5);

    // MISC is bit 29-44 (16 bits)
    misc      =                            ((u32)xtr_hdr[30] << 16) | ((u32)xtr_hdr[31] <<  8) | ((u32)xtr_hdr[32] <<  0);
    misc      = (misc >> 5);

    // The VStaX header's MSbit must be 1.
    if (vstax_one != 1) {
        VTSS_EG(trc_grp, "Invalid Rx header signature");
        return VTSS_RC_ERROR;
    }

    VTSS_MEMSET(info, 0, sizeof(*info));

    info->hw_tstamp         = tstamp<<8;
    info->length            = meta->length;
    info->hw_tstamp_decoded = TRUE;

    chip_port = VTSS_EXTRACT_BITFIELD(fwd, 1, 7); // FWD:SRC_PORT
    info->port_no = vtss_cmn_chip_to_logical_port(state, 0, chip_port);
    if (chip_port == VTSS_CHIP_PORT_CPU_0 || chip_port == VTSS_CHIP_PORT_CPU_1) {
        VTSS_IG(trc_grp, "This frame is transmitted by the CPU itself and should be discarded.");
    }

//     VTSS_IG(trc_grp, "Received on xtr_qu = %u, chip_no = %d, chip_port = %u, port_no = %u", meta->xtr_qu, meta->chip_no, chip_port, info->port_no);

    // TBD_PACKET: Check if bugzilla#17780 is valid for this architecture
    sflow_id = VTSS_EXTRACT_BITFIELD(fwd, 12, 7); // FWD:SFLOW_ID
    if (sflow_id < VTSS_CHIP_PORTS) {
        info->sflow_type = VTSS_SFLOW_TYPE_TX;
        info->sflow_port_no = vtss_cmn_chip_to_logical_port(state, 0, sflow_id);
    } else if (sflow_id == 125 || sflow_id == 126) {
        info->sflow_type = VTSS_SFLOW_TYPE_RX;
        info->sflow_port_no = info->port_no;
    }

    info->xtr_qu_mask = VTSS_EXTRACT_BITFIELD(misc, 0, 8); // MISC:CPU_MASK

    if (VTSS_EXTRACT_BITFIELD64(dst, 22, 16) & FA_IFH_CL_RSLT_ACL_HIT) {
        // ACL hit signalled in DST:MATCH_ID_GRP_IDX
        info->acl_hit = 1;
    }

    info->cosid    = VTSS_EXTRACT_BITFIELD(  vstax_hi, 12,  3);
    info->iflow_id = VTSS_EXTRACT_BITFIELD(  vstax_hi,  0, 12);
    info->dp       = VTSS_EXTRACT_BITFIELD64(vstax_lo, 60,  2);
    info->cos      = VTSS_EXTRACT_BITFIELD64(vstax_lo, 56,  3);
    info->tag.pcp  = VTSS_EXTRACT_BITFIELD64(vstax_lo, 29,  3);
    info->tag.dei  = VTSS_EXTRACT_BITFIELD64(vstax_lo, 28,  1);
    info->tag.vid  = VTSS_EXTRACT_BITFIELD64(vstax_lo, 16, 12);

    VTSS_RC(vtss_cmn_packet_hints_update(state, trc_grp, meta->etype, info));

    return VTSS_RC_OK;
}

static vtss_rc fa_rx_frame(vtss_state_t          *vtss_state,
                           u8                    *const data,
                           const u32             buflen,
                           vtss_packet_rx_info_t *const rx_info)
{
    vtss_rc rc = VTSS_RC_INCOMPLETE;
    u32     val;

    VTSS_RC(fa_packet_mode_update(vtss_state));

    /* Check if data is ready for grp */
    REG_RD(VTSS_DEVCPU_QS_XTR_DATA_PRESENT, &val);
    if (val) {
        u32 ifh[FA_IFH_WORDS];
        u32 length;
        vtss_packet_rx_grp_t grp = VTSS_OS_CTZ(val);
        u8 xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES];
        vtss_packet_rx_meta_t meta;

        /* Get frame, separate IFH and frame data */
        VTSS_RC(fa_rx_frame_get_internal(vtss_state, grp, ifh, data, buflen, &length));

        /* IFH is done separately because of alignment needs */
        VTSS_MEMCPY(xtr_hdr, ifh, sizeof(ifh));
        VTSS_MEMSET(&meta, 0, sizeof(meta));
        meta.length = (length - 4);
        meta.etype = (data[12] << 8) | data[13];
        rc = fa_rx_hdr_decode(vtss_state, &meta, xtr_hdr, rx_info);
    }
    return rc;
}

/*****************************************************************************/
// fa_ptp_action_to_ifh()
/*****************************************************************************/
static vtss_rc fa_ptp_action_to_ifh(vtss_packet_ptp_action_t ptp_action, u8 ptp_domain, BOOL afi, u32 *result)  /* TBD_henrikb */
{
    vtss_rc rc = VTSS_RC_OK;

    switch (ptp_action) {
    case VTSS_PACKET_PTP_ACTION_ONE_STEP:
        *result = 1;
        break;

    case VTSS_PACKET_PTP_ACTION_TWO_STEP:
        *result = 4;
        break;

    case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP:
        *result = 3;
        break;

    case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ:
        *result = 7;
        break;

    case VTSS_PACKET_PTP_ACTION_AFI_NONE:
        *result = 12;
        break;

    default:
        VTSS_E("Invalid PTP action (%d)", ptp_action);
        *result = 0;
        rc = VTSS_RC_ERROR;
        break;
    }

    *result = *result | (ptp_domain << 6);

    return rc;
}

static void IFH_ENCODE_BITFIELD(u8 *const bin_hdr, u64 value, u32 pos, u32 width)
{
    if (width > 40) return; /* Max width is 5 bytes - 40 bits. In worst case this will spread over 6 bytes - 48 bits*/

    u32 byte = (35 - (pos / 8));  /* Calculate the Start IFH byte position of this IFH bit position */
    u32 bit  = (pos % 8);         /* Calculate the Start bit position in the Start IFH byte */
    u64 encode = VTSS_ENCODE_BITFIELD64(value, bit, width);   /* Encode the bit field into a 32 bit variable. */

    if (encode & 0xFF)           bin_hdr[byte]   |= (u8)((encode & 0xFF));                 /* The b0-b7 goes into the start IFH byte */
    if (encode & 0xFF00)         bin_hdr[byte-1] |= (u8)((encode & 0xFF00) >> 8);          /* The b8-b15 goes into the next IFH byte */
    if (encode & 0xFF0000)       bin_hdr[byte-2] |= (u8)((encode & 0xFF0000) >> 16);       /* The b16-b23 goes into the next IFH byte */
    if (encode & 0xFF000000)     bin_hdr[byte-3] |= (u8)((encode & 0xFF000000) >> 24);     /* The b24-b31 goes into the next IFH byte */
    if (encode & 0xFF00000000)   bin_hdr[byte-4] |= (u8)((encode & 0xFF00000000) >> 32);   /* The b32-b39 goes into the next IFH byte */
    if (encode & 0xFF0000000000) bin_hdr[byte-5] |= (u8)((encode & 0xFF0000000000) >> 40); /* The b40-b47 goes into the next IFH byte */
}

/*****************************************************************************/
// fa_tx_hdr_encode()
/*****************************************************************************/
static vtss_rc fa_tx_hdr_encode(vtss_state_t                *const state,
                                const vtss_packet_tx_info_t *const info,
                                u8                          *const bin_hdr,
                                u32                         *const bin_hdr_len)
{
    vtss_prio_t         cos;
    vtss_phys_port_no_t chip_port;
    BOOL                rewrite = TRUE, setup_cl = FALSE;
    u32                 pl_pt = 0, pl_act = 0, vid, pdu_type = 0, isdx = info->iflow_id;

    if (bin_hdr == NULL) {
        // Caller wants us to return the number of bytes required to fill
        // in #bin_hdr. We need FA_IFH_BYTES (36) bytes for the IFH.
        *bin_hdr_len = FA_IFH_BYTES;
        return VTSS_RC_OK;
    } else if (*bin_hdr_len < FA_IFH_BYTES) {
        VTSS_E("Invalid IFH length: %u  min: %u", *bin_hdr_len, FA_IFH_BYTES);
        return VTSS_RC_ERROR;
    }

    *bin_hdr_len = FA_IFH_BYTES;
    VTSS_MEMSET(bin_hdr, 0, FA_IFH_BYTES); /* IFH is all zero. From now on bits can be set by OR. No bit clear should be required */

    IFH_ENCODE_BITFIELD(bin_hdr, 1, VSTAX+79, 1); // VSTAX.RSV = 1. MSBit must be 1
    IFH_ENCODE_BITFIELD(bin_hdr, 1, VSTAX+55, 1); // VSTAX.INGR_DROP_MODE = Enable. Don't make head-of-line blocking
    IFH_ENCODE_BITFIELD(bin_hdr, 1, 67,       1); // FWD.UPDATE_FCS = Enable. Enforce update of FCS.

#if defined(VTSS_FEATURE_AFI_SWC)
    if (info->afi_id != VTSS_AFI_ID_NONE) {
        // The CPU wants this frame to go into the AFI packet memory for repetitive injection.
        IFH_ENCODE_BITFIELD(bin_hdr, 1, 72, 1); // FWD.AFI_INJ = Enable
    }
#endif

    // FIXME: Super-priority injection
    cos = (info->cos >= 8 ? 7 : info->cos);

    if (info->switch_frm) {
        // This is a switched frame - the frame is injected into the switch */
        pl_act = 2; // MISC.PIPELINE_ACT = INJ_MASQ
        if (info->masquerade_port != VTSS_PORT_NO_NONE) {
            // OAM Injection in an Up-MEP/MIP - The following will be according to TN1258 (EVC Baseline)
            VTSS_DG(VTSS_TRACE_GROUP_PACKET, "Masqueraded OAM/Y1564 Injecting");

            chip_port = VTSS_CHIP_PORT_FROM_STATE(state, info->masquerade_port);
            IFH_ENCODE_BITFIELD(bin_hdr, chip_port % 32,    VSTAX+0,  5); // VSTAX.SRC.SRC_UPSPN = masquerade chip port
            IFH_ENCODE_BITFIELD(bin_hdr, chip_port / 32,    VSTAX+5,  5); // VSTAX.SRC.SRC_UPSID = masquerade chip port
            IFH_ENCODE_BITFIELD(bin_hdr, chip_port,         46,       7); // FWD.SRC_PORT = masquerade port
            setup_cl = TRUE; // Setup classified fields later
            pl_pt = info->pipeline_pt;
            if (info->oam_type != VTSS_PACKET_OAM_TYPE_NONE && pl_pt != VTSS_PACKET_PIPELINE_PT_NONE && pl_pt != VTSS_PACKET_PIPELINE_PT_ANA_CLM) {
                pdu_type = 1; // DST.PDU_TYPE = OAM_Y1731
            }
        } else {
            IFH_ENCODE_BITFIELD(bin_hdr, VTSS_CHIP_PORT_CPU_0, 46, 7); // FWD.SRC_PORT = CPU
        }
    } else {
        // Not a switched frame.
        IFH_ENCODE_BITFIELD(bin_hdr, VTSS_CHIP_PORT_CPU_0, 46, 7); // FWD.SRC_PORT = CPU

        // Add mirror port if enabled.
        if (state->l2.mirror_conf.port_no != VTSS_PORT_NO_NONE && state->l2.mirror_cpu_ingress) {
            IFH_ENCODE_BITFIELD(bin_hdr, FA_MIRROR_PROBE_RX + 1, 53, 2);  /* FWD.MIRROR_PROBE = Ingress mirror probe. 1-based in this field */
        }

        if (info->ptp_action != VTSS_PACKET_PTP_ACTION_NONE) {
            // PTP injection
            u32 rew_cmd;

            rewrite = TRUE;
            VTSS_DG(VTSS_TRACE_GROUP_PACKET, "Injecting with PTP action: %d, pdu_offset %u", info->ptp_action, info->pdu_offset);
            VTSS_RC(fa_ptp_action_to_ifh(info->ptp_action, info->ptp_domain, info->afi_id != VTSS_AFI_ID_NONE, &rew_cmd));
            VTSS_DG(VTSS_TRACE_GROUP_PACKET, "Injecting rew_cmd: 0x%x, ptp_timestamp %" PRIu64 "", rew_cmd, info->ptp_timestamp);
            IFH_ENCODE_BITFIELD(bin_hdr, rew_cmd, VSTAX+32, 10); // VSTAX.REW_CMD = PTP rewrite command. (when FWD_MODE == FWD_LLOOKUP).
            pdu_type = 5; // DST.PDU_TYPE = PTP
            pl_pt = VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE;
        } else if (info->oam_type != VTSS_PACKET_OAM_TYPE_NONE) {
            // OAM injection
            VTSS_DG(VTSS_TRACE_GROUP_PACKET, "OAM Injecting");
            IFH_ENCODE_BITFIELD(bin_hdr, 1, VSTAX+59, 1); // VSTAX.SP = 1. Super Priority
            pdu_type = 1; // DST.PDU_TYPE = OAM_Y1731
            pl_pt = info->pipeline_pt;

            if (info->pipeline_pt != VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE || info->oam_type == VTSS_PACKET_OAM_TYPE_LCK) {
                /* Injecting LCK is done in the client flow. This must hit the ES0 */
                rewrite = TRUE;
            } else {
                rewrite = FALSE;
            }
        } else {
            // Normal port injection without rewriting, unless asked to rewrite.
            rewrite = (info->tag.tpid == 0 && info->tag.vid != VTSS_VID_NULL);
            pl_pt = (info->pipeline_pt == VTSS_PACKET_PIPELINE_PT_NONE ? VTSS_PACKET_PIPELINE_PT_ANA_DONE : info->pipeline_pt);
        }

        chip_port = VTSS_CHIP_PORT_FROM_STATE(state, info->dst_port);
        if (info->afi_id == VTSS_AFI_ID_NONE) {
            // Must be 0 for AFI-injected frames, or the REW will see this as a
            // CPU queue mask and not work as expected. The destination port is
            // chosen during mesa_afi_slow_inj_alloc()/mesa_afi_fast_inj_alloc()
            IFH_ENCODE_BITFIELD(bin_hdr, chip_port, 29, 8);   // MISC.CPU_MASK = Destination port. For injected frames this field is Destination port.
        }

        pl_act = 1; // MISC.PIPELINE_ACT = INJ
        IFH_ENCODE_BITFIELD(bin_hdr, !rewrite,  45, 1);   // FWD.DO_NOT_REW = 0 => do rewrite, 1 => do not rewrite
        IFH_ENCODE_BITFIELD(bin_hdr, cos, VSTAX+56, 3);  // VSTAX.CL_COS = cos. qos_class/iprio (internal priority)

        if (rewrite) {
            setup_cl = TRUE; // Setup classified fields later
            IFH_ENCODE_BITFIELD(bin_hdr, info->dp, VSTAX+60,  2); // VSTAX.CL_DP = dp.
            if (info->tag.tpid != 0 && info->tag.tpid != 0x8100) {
                IFH_ENCODE_BITFIELD(bin_hdr, 1, VSTAX+14, 1);  // VSTAX.TAG.TAG_TYPE = 1. S-TAG
            }
        } else if (info->pipeline_pt == VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE &&
                   info->oam_type != VTSS_PACKET_OAM_TYPE_NONE &&
                   isdx == VTSS_ISDX_NONE) {
            // ESO_ISDX_KEY_ENA is configured to the opposite of the requested. Try not to hit ES0 when no rewriting is calculated
            IFH_ENCODE_BITFIELD(bin_hdr, 1, 70, 1); // FWD.ESO_ISDX_KEY_ENA = 1
            IFH_ENCODE_BITFIELD(bin_hdr, info->cosid, VSTAX+76, 3); // VSTAX.COSID = cosid.
        }
    } /* switched frame */

    IFH_ENCODE_BITFIELD(bin_hdr, 124,    57, 7); // FWD.SFLOW_ID (disable SFlow sampling)
    IFH_ENCODE_BITFIELD(bin_hdr, pl_pt,  37, 5); // MISC.PIPELINE_PT
    IFH_ENCODE_BITFIELD(bin_hdr, pl_act, 42, 3); // MISC.PIPELINE_ACT

    if (pdu_type) {
        if (info->pdu_offset == 0 || (info->pdu_offset % 2) != 0) {
            VTSS_E("Invalid pdu_offset %u. It must be an even number greater than 0", info->pdu_offset);
            return VTSS_RC_ERROR;
        }
        IFH_ENCODE_BITFIELD(bin_hdr, info->pdu_offset / 2, 195, 6); // DST.PDU_W16_OFFSET
        IFH_ENCODE_BITFIELD(bin_hdr, pdu_type,             191, 4); // DST.PDU_TYPE
    }

    if (setup_cl) {
        IFH_ENCODE_BITFIELD(bin_hdr, info->cosid,   VSTAX+76, 3);  // VSTAX.COSID = cosid.
        IFH_ENCODE_BITFIELD(bin_hdr, cos,           VSTAX+56, 3);  // VSTAX.CL_COS = cos. qos_class/iprio (internal priority)
        IFH_ENCODE_BITFIELD(bin_hdr, info->tag.pcp, VSTAX+29,  3); // VSTAX.TAG.CL_PCP = pcp.
        IFH_ENCODE_BITFIELD(bin_hdr, info->tag.dei, VSTAX+28,  1); // VSTAX.TAG.CL_DEI = dei.
        vid = info->tag.vid;
        if (vid >= VTSS_VIDS) {
            // Extended VID
            IFH_ENCODE_BITFIELD(bin_hdr, 1, 202, 1); // DST.XVID_EXT = Enable.
            vid = (VTSS_VIDS - vid);
        }
        IFH_ENCODE_BITFIELD(bin_hdr, vid, VSTAX+16, 12); // VSTAX.TAG.CL_VID = vid.
        if (isdx != VTSS_ISDX_NONE) {
            IFH_ENCODE_BITFIELD(bin_hdr, 1,          70,        1); // FWD.ESO_ISDX_KEY_ENA = 1
            IFH_ENCODE_BITFIELD(bin_hdr, isdx, VSTAX+64, 12); // VSTAX.MISH.ISDX = isdx
        }
    }
    IFH_ENCODE_BITFIELD(bin_hdr, ((info->ptp_timestamp>>8) & 0xFFFFFFFFFF), 232, 40); // TS = 40 bits PTP time stamp

    VTSS_IG(VTSS_TRACE_GROUP_PACKET, "IFH:");
    VTSS_IG_HEX(VTSS_TRACE_GROUP_PACKET, &bin_hdr[0], *bin_hdr_len);

    return VTSS_RC_OK;
}

static vtss_rc fa_tx_frame_ifh_vid(vtss_state_t *vtss_state,
                                   const vtss_packet_tx_ifh_t *const ifh,
                                   const u8 *const frame,
                                   const u32 length,
                                   const vtss_vid_t vid)
{
    u32 val, w, count, last;
    const u8 *buf = frame;
    vtss_packet_tx_grp_t grp = 1;

    VTSS_N("length: %u, vid: %u, ifhlen: %d", length, vid, ifh->length);

    VTSS_RC(fa_packet_mode_update(vtss_state));

    if (ifh->length != FA_IFH_BYTES) {
        return VTSS_RC_ERROR;
    }

    REG_RD(VTSS_DEVCPU_QS_INJ_STATUS, &val);
    if (!(VTSS_X_DEVCPU_QS_INJ_STATUS_FIFO_RDY(val) & VTSS_BIT(grp))) {
        VTSS_E("Not ready");
        return VTSS_RC_ERROR;
    }

    if (VTSS_X_DEVCPU_QS_INJ_STATUS_WMARK_REACHED(val) & VTSS_BIT(grp)) {
        VTSS_E("Watermark reached");
        return VTSS_RC_ERROR;
    }

    /* Indicate SOF */
    REG_WR(VTSS_DEVCPU_QS_INJ_CTRL(grp), VTSS_F_DEVCPU_QS_INJ_CTRL_GAP_SIZE(1) | VTSS_M_DEVCPU_QS_INJ_CTRL_SOF);

    // Write the IFH to the chip.
    for (w = 0; w < FA_IFH_WORDS; w++) {
        REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), ifh->ifh[w]);
    }

    /* Write words, round up */
    count = ((length + 3) / 4);
    last = length % 4;
    for (w = 0; w < count; w++, buf += 4) {
        if (w == 3 && vid != VTSS_VID_NULL) {
            /* Insert C-tag */
            REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), VTSS_OS_NTOHL((0x8100U << 16) | vid));
            w++;
        }
#ifdef VTSS_OS_BIG_ENDIAN
        REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
#else
        REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
#endif
    }

    /* Add padding */
    while (w < (60 / 4)) {
        REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), 0);
        w++;
    }

    /* Indicate EOF and valid bytes in last word */
    REG_WR(VTSS_DEVCPU_QS_INJ_CTRL(grp),
           VTSS_F_DEVCPU_QS_INJ_CTRL_GAP_SIZE(1) |
           VTSS_F_DEVCPU_QS_INJ_CTRL_VLD_BYTES(length < 60 ? 0 : last) |
           VTSS_M_DEVCPU_QS_INJ_CTRL_EOF);

    /* Add dummy CRC */
    REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), 0);
    w++;

    VTSS_N("wrote %u words, last: %u", w, last);

    return VTSS_RC_OK;
}

static vtss_rc fa_tx_frame_ifh(vtss_state_t *vtss_state,
                               const vtss_packet_tx_ifh_t *const ifh,
                               const u8 *const frame,
                               const u32 length)
{
    return fa_tx_frame_ifh_vid(vtss_state, ifh, frame, length, VTSS_VID_NULL);
}

/* - Debug print --------------------------------------------------- */

static vtss_rc fa_debug_pkt(vtss_state_t              *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_packet_debug_print(vtss_state_t              *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_PACKET, fa_debug_pkt, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */
static vtss_rc fa_packet_init(vtss_state_t *vtss_state)
{
    vtss_packet_rx_queue_t qu;
    u32                    val;
    u32                    i, port;
    int                    pcp, dei;

    // The extraction queues can be redirected to any port.
    // This is used to redirect selected queues to an NPI port, but also the FDMA (if included)
    // may use this feature to redirect to a dummy port when throttling.
    // The NPI settings take precedence over the FDMA, but we need to keep track of
    // what the FDMA wants to set it to in case the application enables and disables NPI redirection.
    for (qu = 0; qu < vtss_state->packet.rx_queue_count; qu++) {
        i = QFWD_FRAME_COPY_CFG_CPU_QU(qu);
        REG_RD(VTSS_QFWD_FRAME_COPY_CFG(i), &val);
        vtss_state->packet.default_qu_redirect[qu] = VTSS_X_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL(val);
        REG_WRM(VTSS_QFWD_FRAME_COPY_CFG(i),
                VTSS_F_QFWD_FRAME_COPY_CFG_FRMC_QOS_VAL(qu) |
                VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_QOS_ENA,
                VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_QOS_VAL |
                VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_QOS_ENA);
    }

    // Setup CPU port 0 and 1 to allow for classification of transmission of
    // switched frames into a user-module-specifiable QoS class.
    // For the two CPU ports, we set a one-to-one mapping between a VLAN tag's
    // PCP and a QoS class. When transmitting switched frames, the PCP value
    // of the VLAN tag (which is always inserted to get it switched on a given
    // VID), then controls the priority.
    // Enable looking into PCP and DEI bits
    REG_WRM(VTSS_ANA_CL_QOS_CFG(VTSS_CHIP_PORT_CPU),
            VTSS_F_ANA_CL_QOS_CFG_PCP_DEI_DP_ENA(1) | VTSS_F_ANA_CL_QOS_CFG_PCP_DEI_QOS_ENA(1),
            VTSS_M_ANA_CL_QOS_CFG_PCP_DEI_DP_ENA    | VTSS_M_ANA_CL_QOS_CFG_PCP_DEI_QOS_ENA);

    // Set-up the one-to-one PCP->QoS mapping
    for (pcp = 0; pcp < VTSS_PCP_END - VTSS_PCP_START; pcp++) {
        for (dei = 0; dei < VTSS_DEI_END - VTSS_DEI_START; dei++) {
            REG_WR(VTSS_ANA_CL_PCP_DEI_MAP_CFG(VTSS_CHIP_PORT_CPU, (8 * dei + pcp)),
                   VTSS_F_ANA_CL_PCP_DEI_MAP_CFG_PCP_DEI_QOS_VAL(pcp));
        }
    }

    for (i = VTSS_CHIP_PORT_CPU_0; i <= VTSS_CHIP_PORT_CPU_1; i++) {
        // Disable aging of Rx CPU queues to allow the frames to stay there longer than
        // on normal front ports.
        REG_WRM(VTSS_HSCH_PORT_MODE(i), VTSS_F_HSCH_PORT_MODE_AGE_DIS(1), VTSS_M_HSCH_PORT_MODE_AGE_DIS);
        REG_WRM(VTSS_DSM_BUF_CFG(i), VTSS_F_DSM_BUF_CFG_AGING_ENA(0), VTSS_M_DSM_BUF_CFG_AGING_ENA);
        REG_WRM(VTSS_ASM_PORT_CFG(i), VTSS_F_ASM_PORT_CFG_FRM_AGING_DIS(1), VTSS_M_ASM_PORT_CFG_FRM_AGING_DIS);

        // Enable stacking on CPU ports for VLAN classification purposes
        REG_WRM(VTSS_ANA_CL_STACKING_CTRL(i),
                VTSS_F_ANA_CL_STACKING_CTRL_STACKING_AWARE_ENA(1),
                VTSS_M_ANA_CL_STACKING_CTRL_STACKING_AWARE_ENA);
        REG_WRM(VTSS_ANA_CL_STACKING_CTRL(i),
                VTSS_F_ANA_CL_STACKING_CTRL_STACKING_HEADER_DISCARD_ENA(0),
                VTSS_M_ANA_CL_STACKING_CTRL_STACKING_HEADER_DISCARD_ENA);

        // Set CPU ports to be VLAN aware, since frames that we send switched
        // must contain a VLAN tag for correct classification. One could use
        // the frame's VStaX header, but that won't work for stacking solutions.
        // We also set it to pop one tag.
        REG_WRM(VTSS_ANA_CL_VLAN_CTRL(i),
                VTSS_F_ANA_CL_VLAN_CTRL_PORT_VID      (0) |
                VTSS_F_ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA(1) |
                VTSS_F_ANA_CL_VLAN_CTRL_VLAN_POP_CNT  (1),
                VTSS_M_ANA_CL_VLAN_CTRL_PORT_VID          |
                VTSS_M_ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA    |
                VTSS_M_ANA_CL_VLAN_CTRL_VLAN_POP_CNT);

        // Disable IGMP redirect for CPU ports
        REG_WR(VTSS_ANA_CL_CAPTURE_CFG(i), 0);
    }

    // Make sure the ports are not VStaX aware, because that will cause the
    // switch to move a possible VStaX header from the frame into the IFH.
    // This is not NPI-port compatible.
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        REG_WRM(VTSS_ASM_PORT_CFG(port),
                VTSS_F_ASM_PORT_CFG_VSTAX2_AWR_ENA(0),
                VTSS_M_ASM_PORT_CFG_VSTAX2_AWR_ENA);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_packet_state_t *state = &vtss_state->packet;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->rx_conf_set              = fa_rx_conf_set;
        state->rx_frame                 = fa_rx_frame;
        state->tx_frame_ifh             = fa_tx_frame_ifh;
        state->rx_hdr_decode            = fa_rx_hdr_decode;
        state->rx_ifh_size              = VTSS_FA_RX_IFH_SIZE;
        state->tx_hdr_encode            = fa_tx_hdr_encode;
        state->npi_conf_set             = fa_npi_conf_set;
        state->packet_phy_cnt_to_ts_cnt = fa_packet_phy_cnt_to_ts_cnt;
        state->packet_ns_to_ts_cnt      = fa_packet_ns_to_ts_cnt;
        state->ptp_get_timestamp        = fa_ptp_get_timestamp;
        state->rx_queue_count           = VTSS_PACKET_RX_QUEUE_CNT;

#if defined(VTSS_FEATURE_FDMA) && VTSS_OPT_FDMA
        state->fdma_qu_redirect_set = fa_fdma_qu_redirect_set;
        fa_fdma_func_init(vtss_state);
#endif /* VTSS_FEATURE_FDMA && VTSS_OPT_FDMA */
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(fa_packet_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        if (!vtss_state->warm_start_cur) {
            VTSS_RC(fa_rx_conf_set(vtss_state));
        }
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_FA */
