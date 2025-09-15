// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)
#include "vtss_ts_api.h"

#if defined(VTSS_ARCH_LAIKA)
#include "vtss_lk_packet.h"
#endif

/* - CIL functions ------------------------------------------------- */

#define FA_IFH_WORDS (VTSS_FA_RX_IFH_SIZE / 4U) /* 9 32-bit words in an IFH */
#define FA_IFH_BYTES (VTSS_FA_RX_IFH_SIZE)      /* 36 bytes words in an IFH */

/* ================================================================= *
 *  NPI
 * ================================================================= */

static vtss_rc fa_npi_redirect_qu_to_port(vtss_state_t          *vtss_state,
                                          vtss_packet_rx_queue_t qu,
                                          vtss_phys_port_no_t    chip_port)
{
    REG_WRM(VTSS_QFWD_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_CPU_QU(qu)),
            VTSS_F_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL(chip_port),
            VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL);

    return VTSS_RC_OK;
}

static vtss_rc fa_npi_mask_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t *rx_conf = &vtss_state->packet.rx_conf;
    vtss_npi_conf_t       *npi_conf = &vtss_state->packet.npi_conf;
    vtss_packet_rx_queue_t qu;

    for (qu = 0U; qu < vtss_state->packet.rx_queue_count; qu++) {
        BOOL npi_redirect = npi_conf->port_no != VTSS_PORT_NO_NONE && rx_conf->queue[qu].npi.enable;

        VTSS_RC(fa_npi_redirect_qu_to_port(vtss_state, qu,
                                           npi_redirect
                                               ? VTSS_CHIP_PORT(npi_conf->port_no)
                                               : vtss_state->packet.default_qu_redirect[qu]));
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
        REG_WRM(VTSS_REW_IFH_CTRL(port), VTSS_F_REW_IFH_CTRL_KEEP_IFH_SEL(conf->enable ? 2 : 0),
                VTSS_M_REW_IFH_CTRL_KEEP_IFH_SEL);
        REG_WRM(VTSS_ASM_PORT_CFG(port), VTSS_F_ASM_PORT_CFG_INJ_FORMAT_CFG(conf->enable ? 2 : 0),
                VTSS_M_ASM_PORT_CFG_INJ_FORMAT_CFG);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_packet_npi_conf_set(struct vtss_state_s         *vtss_state,
                                     const vtss_npi_conf_t *const conf)
{
    vtss_npi_conf_t *old = &vtss_state->packet.npi_conf;

    // Disable current NPI port
    old->enable = FALSE;
    VTSS_RC(fa_npi_update(vtss_state));

    // Set new NPI port
    *old = *conf;
    VTSS_RC(fa_npi_update(vtss_state));

    return vtss_cmn_vlan_update_all(vtss_state);
}

vtss_rc vtss_cil_packet_phy_cnt_to_ts_cnt(struct vtss_state_s *vtss_state, u32 phy_cnt, u64 *ts_cnt)
{
    vtss_timestamp_t ts;
    u64              tc;
    u32              tod_cnt, diff;
    u32              frame_cnt = phy_cnt;

    /* The frame_cnt parameter is a 32 bit wrapping nano second counter,
     * extracted from the received packet (inserted by the PHY) */

    /* The time of day is sampled 2 or more times pr sec, assumed frame stamping
     * belong to domain 0 */
    (void)vtss_ts_domain_timeofday_get_private(NULL, 0U, &ts, &tc);
    tod_cnt = ts.nanoseconds + (VTSS_ONE_MIA * ts.seconds); /* tod_cnt is now a TOD 32 bit
                                                               wrapping nano second counter */

    diff = tod_cnt - frame_cnt;             /* Calculate the difference between FRAME and
                                               TOD 32 bit wrapping nano second counter */
    *ts_cnt = tc - (u64)((u64)diff << 16U); /* Difference in 16 bit nano second fragments */
    VTSS_I("frame_cnt %u  tod_cnt %u  ts_cnt %" PRIu64 "  diff %u  ts.sec %u  ts.ns %u  tc %" PRIu64
           "",
           frame_cnt, tod_cnt, *ts_cnt, diff, ts.seconds, ts.nanoseconds, tc);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_packet_ns_to_ts_cnt(struct vtss_state_s *vtss_state, u32 ns, u64 *ts_cnt)
{
    vtss_timestamp_t ts;
    u64              tc;
    u32              tod_ns, diff;
    u32              frame_ns = ns;

    /* The frame_ns parameter is a one mia (one second) wrapping nano second
     * counter, extracted from the received packet (inserted by the PHY) */

    while (frame_ns >= VTSS_ONE_MIA) {
        /* skip sec part */
        frame_ns -= VTSS_ONE_MIA;
        VTSS_I("decrement frame_ns value (%d)", frame_ns);
    }

    /* The time of day is sampled 2 or more times pr sec, assumed frame stamping
     * belong to domain 0 */
    (void)vtss_ts_domain_timeofday_get_private(NULL, 0U, &ts, &tc);
    if (ts.nanoseconds < frame_ns) {
        tod_ns = ts.nanoseconds + VTSS_ONE_MIA; /* TOD nanoseconds is smaller than the frame_ns
                                                   from the frame. TOD nanoseconds has wrapped */
        tc += ((u64)VTSS_ONE_MIA) << 16U;
    } else {
        tod_ns = ts.nanoseconds;
    }

    diff = tod_ns - frame_ns;               /* Calculate the difference between FRAME and TOD
                                               30 bit wrapping nano second counter */
    *ts_cnt = tc - (u64)((u64)diff << 16U); /* Difference in 16 bit nano second fragments */
    VTSS_I("frame_ns %u  tod_ns %u  ts_cnt %" PRIu64 "  diff %u  ts.sec %u  ts.ns %u  tc %" PRIu64
           "",
           frame_ns, tod_ns, *ts_cnt, diff, ts.seconds, ts.nanoseconds, tc);

    return VTSS_RC_OK;
}

static u32 fa_packet_unpack32(const u8 *buf)
{
    return ((u32)buf[0] << 24U) + ((u32)buf[1] << 16U) + ((u32)buf[2] << 8U) + (u32)buf[3];
}

vtss_rc vtss_cil_packet_ptp_get_timestamp(struct vtss_state_s               *vtss_state,
                                          const u8 *const                    frm,
                                          const vtss_packet_rx_info_t *const rx_info,
                                          vtss_packet_ptp_message_type_t     message_type,
                                          vtss_packet_timestamp_props_t      ts_props,
                                          u64                               *rxTime,
                                          BOOL                              *timestamp_ok)
{
    u64 *ts_cnt = rxTime;
    if (ts_props.ts_feature_is_PTS) {
        u32 packet_ns = fa_packet_unpack32(frm);
        if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_30BIT) {
            //'ts_cnt' should be similar 'tc' returned from
            // fa_ts_io_pin_timeofday_get. packet contains only nano seconds
            // part in reserved field. Hence, only nano seconds are returned.
            *ts_cnt = (u64)packet_ns << 16U;
            *timestamp_ok = rx_info->hw_tstamp_decoded;
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_32BIT) {
            /* convert to jaguar 32 bit NSF */
            VTSS_D("ts_cnt before %u", packet_ns);
            (void)vtss_cil_packet_phy_cnt_to_ts_cnt(vtss_state, packet_ns, ts_cnt);
            VTSS_D("ts_cnt after %" PRIu64, *ts_cnt);
            *timestamp_ok = rx_info->hw_tstamp_decoded;
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_44BIT) {
            VTSS_I("ts_cnt can not be retrieved from the packet supress warning for mode %d ",
                   ts_props.phy_ts_mode);
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_48BIT) {
            // 'ts_cnt' should be similar 'tc' returned from
            // fa_ts_io_pin_timeofday_get.
            // PHY passes ingress timestamp in reserved field.
            *ts_cnt = (u64)packet_ns << 16U;
            *timestamp_ok = TRUE;
        } else {
            VTSS_I("PHY timestamp mode %d not supported", ts_props.phy_ts_mode);
        }
    } else {
        /* The hw_tstamp is a tc in 16 bit nano second fragments (46 (30 bits
         * nsec + 16 bits sub nsec) wrapping) */
        *ts_cnt = rx_info->hw_tstamp;
        *timestamp_ok = rx_info->hw_tstamp_decoded;
        /* if Sync message then subtract the p2p delay from rx time  */
        if (message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC) {
            *ts_cnt = *ts_cnt - ts_props.delay_comp.delay_cnt;
        }
        /* link asymmetry compensation for Sync and PdelayResp events are not
         * done in Jaguar2 on packets forwarded to the CPU */
        if ((message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC ||
             message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_P_DELAY_RESP) &&
            ts_props.delay_comp.asymmetry_cnt != 0U) {
            *ts_cnt = *ts_cnt - ts_props.delay_comp.asymmetry_cnt;
        }
    }
    return VTSS_RC_OK;
}

/* Setup L2CP Profile */
static vtss_rc fa_l2cp_conf_set(vtss_state_t        *vtss_state,
                                u32                  profile,
                                u32                  l2cp,
                                vtss_fa_l2cp_conf_t *conf)
{
    u32 reg;

    switch (conf->reg) {
    case VTSS_PACKET_REG_DISCARD:  reg = 3U; break;
    case VTSS_PACKET_REG_CPU_COPY: reg = 2U; break;
    case VTSS_PACKET_REG_CPU_ONLY: reg = 1U; break;
    case VTSS_PACKET_REG_FORWARD:
    default:                       reg = 0U; break;
    }
    REG_WR(VTSS_ANA_CL_L2CP_ENTRY_CFG(profile * 32U + l2cp),
           VTSS_F_ANA_CL_L2CP_ENTRY_CFG_COSID_VAL(conf->cosid) |
               VTSS_F_ANA_CL_L2CP_ENTRY_CFG_COSID_ENA(conf->cosid_enable ? 1 : 0) |
               VTSS_F_ANA_CL_L2CP_ENTRY_CFG_CPU_FWD_CFG(reg) |
               VTSS_F_ANA_CL_L2CP_ENTRY_CFG_CPU_L2CP_QU(conf->queue));
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_packet_rx_conf_set(struct vtss_state_s *vtss_state)
{
    vtss_packet_rx_conf_t      *conf = &vtss_state->packet.rx_conf;
    vtss_packet_rx_reg_t       *reg = &conf->reg;
    vtss_packet_rx_queue_map_t *map = &conf->map;
    vtss_packet_rx_port_conf_t *port_conf;
    vtss_port_no_t              port_no;
    u32                         port, i, j, cap_cfg, queue, offs;
    BOOL                        cpu_only;
    vtss_fa_l2cp_conf_t         l2cp_conf;

    // Each CPU queue gets reserved extraction buffer space. No sharing at port
    // or buffer level
    offs = 2048U; // Egress/destination memory
#if defined(VTSS_ARCH_LAIKA)
    port = RT_CHIP_PORT_CPU_0;
#else
    port = RT_CHIP_PORT_CPU_1;
#endif
    for (queue = 0U; queue < vtss_state->packet.rx_queue_count; queue++) {
        i = conf->queue[queue].size / FA_BUFFER_CELL_SZ;
        REG_WR(VTSS_QRES_RES_CFG(offs + port * VTSS_PRIOS + queue), i);
    }
    // Per-port reservation, no extra shared space
    REG_WR(VTSS_QRES_RES_CFG(offs + RT_RES_CFG_MAX_PORT_IDX + port), 0);

    // Setup Rx registrations that we only have per-switch API support for (not
    // per-port)
    cap_cfg = VTSS_F_ANA_CL_CAPTURE_CFG_CPU_MLD_REDIR_ENA(reg->mld_cpu_only) |
              VTSS_F_ANA_CL_CAPTURE_CFG_CPU_IP4_MC_COPY_ENA(reg->ipmc_ctrl_cpu_copy) |
              VTSS_F_ANA_CL_CAPTURE_CFG_CPU_IGMP_REDIR_ENA(reg->igmp_cpu_only);

    // Calculate offset for port L2CP profiles. LK_TGT and LA_TGT is 16, FA_TGT is 64.
#if defined(VTSS_ARCH_SPARX5)
    offs = 64U;
#else
    offs = 16U;
#endif

    // Setup Rx registrations that we have per-port
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        port_conf = &vtss_state->packet.rx_port_conf[port_no];

        for (i = 0U; i < 32U; i++) {
            l2cp_conf.cosid_enable = FALSE;
            l2cp_conf.cosid = 0;
            if (i < 16U) {
                // BPDU
                j = i;
                l2cp_conf.reg = port_conf->bpdu_reg[j];
                cpu_only = reg->bpdu_cpu_only;
                l2cp_conf.queue = map->bpdu_queue;
#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
                l2cp_conf.cosid_enable = port_conf->bpdu[j].cosid_enable;
                l2cp_conf.cosid = port_conf->bpdu[j].cosid;
#endif
            } else {
                // GARP
                j = (i - 16U);
                l2cp_conf.reg = port_conf->garp_reg[j];
                cpu_only = reg->garp_cpu_only[j];
                l2cp_conf.queue = map->garp_queue;
#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
                l2cp_conf.cosid_enable = port_conf->garp[j].cosid_enable;
                l2cp_conf.cosid = port_conf->garp[j].cosid;
#endif
            }
            if (l2cp_conf.reg == VTSS_PACKET_REG_NORMAL) {
                // Use global registration
                l2cp_conf.reg = (cpu_only ? VTSS_PACKET_REG_CPU_ONLY : VTSS_PACKET_REG_FORWARD);
            }
            /* Use L2CP profile at offset for ports */
            VTSS_RC(fa_l2cp_conf_set(vtss_state, port + offs, i, &l2cp_conf));
        }
        REG_WR(VTSS_ANA_CL_CAPTURE_CFG(port), cap_cfg);
    }

    // IGMP and IPMC queues:
    REG_WR(VTSS_ANA_CL_CPU_PROTO_QU_CFG,
           VTSS_F_ANA_CL_CPU_PROTO_QU_CFG_CPU_IP6_MC_CTRL_QU(map->ipmc_ctrl_queue) |
               VTSS_F_ANA_CL_CPU_PROTO_QU_CFG_CPU_MLD_QU(map->igmp_queue) |
               VTSS_F_ANA_CL_CPU_PROTO_QU_CFG_CPU_IP4_MC_CTRL_QU(map->ipmc_ctrl_queue) |
               VTSS_F_ANA_CL_CPU_PROTO_QU_CFG_CPU_IGMP_QU(map->igmp_queue));

    // Learn queue:
    REG_WRM(VTSS_ANA_L2_LRN_CFG, VTSS_F_ANA_L2_LRN_CFG_CPU_LRN_QU(map->learn_queue),
            VTSS_M_ANA_L2_LRN_CFG_CPU_LRN_QU);

    // Enable forwarding to CPU of MAC-table SMAC hits, where the MAC-table
    // entry has the CPU_COPY flag set.
    REG_WRM(VTSS_ANA_L2_LRN_CFG, VTSS_F_ANA_L2_LRN_CFG_CPU_SMAC_COPY_ENA(1),
            VTSS_M_ANA_L2_LRN_CFG_CPU_SMAC_COPY_ENA);

    // sFlow queue:
    if (map->sflow_queue != VTSS_PACKET_RX_QUEUE_NONE) {
        REG_WRM(VTSS_ANA_AC_PS_COMMON_SFLOW_CFG,
                VTSS_F_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU(map->sflow_queue),
                VTSS_M_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU);
    }
#if defined(VTSS_FEATURE_LAYER3)
    // Configure L3 routing CPU queues
    REG_WR(VTSS_ANA_L3_CPU_QU_CFG,
           VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_QU(map->l3_uc_queue) |
               VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_OPT_QU(map->l3_other_queue) |
               VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_HDR_FAIL_QU(map->l3_other_queue) |
               VTSS_F_ANA_L3_CPU_QU_CFG_CPU_SIP_RPF_QU(map->l3_other_queue) |
               VTSS_F_ANA_L3_CPU_QU_CFG_CPU_IP_LEN_QU(map->l3_other_queue) |
               VTSS_F_ANA_L3_CPU_QU_CFG_CPU_MC_FAIL_QU(map->l3_other_queue) |
               VTSS_F_ANA_L3_CPU_QU_CFG_CPU_UC_FAIL_QU(map->l3_uc_queue) |
               VTSS_F_ANA_L3_CPU_QU_CFG_CPU_IP_TTL_FAIL_QU(map->l3_other_queue));
#endif
#if defined(VTSS_FEATURE_REDBOX)
    if (vtss_state->vtss_features[FEATURE_REDBOX]) {
        // RedBox CPU queues
        for (i = 0U; i < VTSS_REDBOX_CNT; i++) {
            j = RB_TGT(i);
            REG_WR(VTSS_RB_CPU_CFG(j), VTSS_F_RB_CPU_CFG_SPV_CPUQ(map->sv_queue) |
                                           VTSS_F_RB_CPU_CFG_BPDU_CPUQ(map->bpdu_queue));
        }
    }
#endif
    // Configure Rx Queue #i to map to an Rx group.
    for (i = 0U; i < vtss_state->packet.rx_queue_count; i++) {
        if (conf->grp_map[i] != 0U) {
            VTSS_E("Attempt to redirect queue %d - use vtss_dma_conf_set() instead", i);
        }
    }

    VTSS_RC(fa_npi_mask_set(vtss_state));

    return VTSS_RC_OK;
}

static vtss_rc fa_packet_mode_update(vtss_state_t *vtss_state)
{
    u32 queue, byte_swap, port, grp = 1U;
#ifdef VTSS_OS_BIG_ENDIAN
    byte_swap = 0;
#else
    byte_swap = 1U;
#endif
#if defined(VTSS_ARCH_LAIKA)
    port = RT_CHIP_PORT_CPU_0;
#else
    port = RT_CHIP_PORT_CPU_1;
#endif

    (void)byte_swap;
    (void)grp;

    if (!vtss_state->packet.manual_mode) {
        /* Change mode to manual extraction and injection */
        vtss_state->packet.manual_mode = TRUE;
#if !defined(VTSS_ARCH_LAIKA)
        REG_WR(VTSS_DEVCPU_QS_XTR_GRP_CFG(grp),
               VTSS_F_DEVCPU_QS_XTR_GRP_CFG_MODE(1) |
                   VTSS_F_DEVCPU_QS_XTR_GRP_CFG_STATUS_WORD_POS(0) |
                   VTSS_F_DEVCPU_QS_XTR_GRP_CFG_BYTE_SWAP(byte_swap));
        REG_WR(VTSS_DEVCPU_QS_INJ_GRP_CFG(grp),
               VTSS_F_DEVCPU_QS_INJ_GRP_CFG_MODE(1) |
                   VTSS_F_DEVCPU_QS_INJ_GRP_CFG_BYTE_SWAP(byte_swap));
#endif
        REG_WRM(VTSS_ASM_PORT_CFG(port),
                VTSS_F_ASM_PORT_CFG_NO_PREAMBLE_ENA(1) | VTSS_F_ASM_PORT_CFG_INJ_FORMAT_CFG(1),
                VTSS_M_ASM_PORT_CFG_NO_PREAMBLE_ENA | VTSS_M_ASM_PORT_CFG_INJ_FORMAT_CFG);
        // Kernel driver changes this for FDMA, so change it back
        REG_WRM(VTSS_DSM_DEV_TX_STOP_WM_CFG(port), VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM(0),
                VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM);

        for (queue = 0U; queue < vtss_state->packet.rx_queue_count; queue++) {
            REG_WRM(VTSS_QFWD_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_CPU_QU(queue)),
                    VTSS_F_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL(port),
                    VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL);
            vtss_state->packet.default_qu_redirect[queue] = port;
        }
    }
    return VTSS_RC_OK;
}

#if !defined(VTSS_ARCH_LAIKA)

#ifdef VTSS_OS_BIG_ENDIAN
#define XTR_EOF_0          0x80000000U
#define XTR_EOF_1          0x80000001U
#define XTR_EOF_2          0x80000002U
#define XTR_EOF_3          0x80000003U
#define XTR_PRUNED         0x80000004U
#define XTR_ABORT          0x80000005U
#define XTR_ESCAPE         0x80000006U
#define XTR_NOT_READY      0x80000007U
#define XTR_VALID_BYTES(x) (4U - ((x) & 3U))
#else
#define XTR_EOF_0          0x00000080U
#define XTR_EOF_1          0x01000080U
#define XTR_EOF_2          0x02000080U
#define XTR_EOF_3          0x03000080U
#define XTR_PRUNED         0x04000080U
#define XTR_ABORT          0x05000080U
#define XTR_ESCAPE         0x06000080U
#define XTR_NOT_READY      0x07000080U
#define XTR_VALID_BYTES(x) (4U - (((x) >> 24U) & 3U))
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
            done = TRUE;                                  /* Last 1-4 bytes */
            break;
        case XTR_ESCAPE:
            REG_RD(VTSS_DEVCPU_QS_XTR_RD(xtr_grp), &val); /* Escaped data */
            break;
        case XTR_NOT_READY:
        default:            VTSS_D("MISRA Non empty default"); break;
        }
    }
    return VTSS_RC_OK;
}

/**
 * Return values:
 *  0 = Data OK.
 *  1 = EOF reached. Data OK. bytes_valid indicates the number of valid bytes in
 * last word ([1; 4]). 2 = Error. No data from queue system.
 */
static u32 fa_rx_frame_word(vtss_state_t        *vtss_state,
                            vtss_packet_rx_grp_t grp,
                            BOOL                 first_word,
                            u32                 *rval,
                            u32                 *bytes_valid)
{
    u32 val, retval;

    REG_RD(VTSS_DEVCPU_QS_XTR_RD(grp), &val);

    if (val == XTR_NOT_READY) {
        /** XTR_NOT_READY means two different things depending on whether this
         * is the first word read of a frame or after at least one word has been
         * read. When the first word, the group is empty, and we return an
         * error. Otherwise we have to wait for the FIFO to have received some
         * more data. */
        if (first_word) {
            return 2U; /* Error */
        }
        do {
            REG_RD(VTSS_DEVCPU_QS_XTR_RD(grp), &val);
        } while (val == XTR_NOT_READY);
    }

    switch (val) {
    case XTR_ABORT:
        /* No accompanying data. */
        VTSS_E("Aborted frame");
        retval = 2U; /* Error */
        break;
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
        retval = 1U; /* EOF */
        break;
    case XTR_ESCAPE:
        REG_RD(VTSS_DEVCPU_QS_XTR_RD(grp), rval);
        *bytes_valid = 4U;
        retval = 0U;
        break;
    default:
        *rval = val;
        *bytes_valid = 4U;
        retval = 0U;
        break;
    }
    return retval;
}

static vtss_rc fa_rx_frame_get_internal(vtss_state_t        *vtss_state,
                                        vtss_packet_rx_grp_t grp,
                                        u32 *const           ifh,
                                        u8 *const            frame,
                                        const u32            buf_length,
                                        u32                 *frm_length) /* Including FCS */
{
    u32  i, val, bytes_got, bytes_valid, buf_len = buf_length;
    BOOL done = FALSE;
    u8  *buf;
    u32  result;

    *frm_length = bytes_got = 0U;

    /* Read IFH words */
    for (i = 0U; i < FA_IFH_WORDS; i++) {
        if (fa_rx_frame_word(vtss_state, grp, TRUE, &val, &bytes_valid) != 0U) {
            /* We accept neither EOF nor ERROR when reading the IFH */
            return VTSS_RC_ERROR;
        }
        ifh[i] = val;
    }

    buf = frame;

    /* Read the rest of the frame */
    while (!done && buf_len >= 4U) {
        result = fa_rx_frame_word(vtss_state, grp, FALSE, &val, &bytes_valid);
        if (result == 2U) {
            // Error.
            return VTSS_RC_ERROR;
        }
        // Store the data.
        bytes_got += bytes_valid;
#ifdef VTSS_OS_BIG_ENDIAN
        *buf++ = (u8)(val >> 24);
        *buf++ = (u8)(val >> 16);
        *buf++ = (u8)(val >> 8);
        *buf++ = (u8)(val >> 0);
#else
        *buf++ = (u8)(val >> 0U);
        *buf++ = (u8)(val >> 8U);
        *buf++ = (u8)(val >> 16U);
        *buf++ = (u8)(val >> 24U);
#endif
        buf_len -= bytes_valid;
        done = result == 1U;
    }

    /* Updated received byte count */
    *frm_length = bytes_got;

    if (!done) {
        /* Buffer overrun. Skip remainder of frame */
        (void)fa_rx_frame_discard_grp(vtss_state, grp);
        return VTSS_RC_ERROR;
    }

    if (bytes_got < 60U) {
        VTSS_E("short frame, %u bytes read", bytes_got);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_LAIKA */

#define VSTAX                                                                                      \
    73U /* The IFH bit position of the first VSTAX bit. This is because the                        \
           VSTAX bit positions in Data sheet is starting from zero. */

// The overall IFH layout for FireAnt and Laguna is the same, for example DST
// starts at offset 153. But within blocks, some Laguna fields are smaller, so
// fields may be shifted:
// - FWD: SRC_PORT is 6/7 bits, causing upper fields to be shifted.
// - DST: COPY_CNT is 8/9 bits, causing upper fields to be shifted.

// These overall offsets are used by the encode() function:
#if defined(VTSS_ARCH_SPARX5)
#define FWD_UPDATE_FCS       67U
#define FWD_AFI_INJ          72U
#define FWD_MIRROR_PROBE     53U
#define FWD_ESO_ISDX_KEY_ENA 70U
#define FWD_SFLOW_ID         57U
#define DST_PDU_W16_OFFSET   195U
#define DST_PDU_TYPE         191U
#define DST_XVID_EXT         202U
#else
#define FWD_UPDATE_FCS       66U
#define FWD_AFI_INJ          71U
#define FWD_MIRROR_PROBE     52U
#define FWD_ESO_ISDX_KEY_ENA 69U
#define FWD_SFLOW_ID         56U
#define DST_PDU_W16_OFFSET   194U
#define DST_PDU_TYPE         190U
#define DST_XVID_EXT         201U
#endif

// These block offsets are used by the decode() function:
#if defined(VTSS_ARCH_SPARX5)
#define SRC_PORT_WID     7U
#define FWD_SFLOW_ID_POS 12U
#define DST_CL_RSLT_POS  22U
#else
#define SRC_PORT_WID     6U
#define FWD_SFLOW_ID_POS 11U
#define DST_CL_RSLT_POS  21U
#endif

vtss_rc vtss_cil_packet_rx_hdr_decode(const struct vtss_state_s *const   vtss_state,
                                      const vtss_packet_rx_meta_t *const meta,
                                      const u8                     hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                      vtss_packet_rx_info_t *const info)
{
    u16                 vstax_hi, vstax_one, rb = 0;
    u32                 fwd, misc, tagging, sflow_id;
    u64                 tstamp, dst, vstax_lo;
    u8                  xtr_hdr_2;
    vtss_phys_port_no_t chip_port;
    vtss_trace_group_t  trc_grp = VTSS_TRACE_GROUP_PACKET;
    VTSS_DG(trc_grp, "IFH (36 bytes) + bit of packet:");
    VTSS_DG_HEX(trc_grp, &hdr[0], 96);
    // (Fireant) Bit 272-287 (16 bits) are unused
    // (Laguna) Bit 279-287 (9 bits) are unused

#if defined(VTSS_FEATURE_REDBOX)
    if (vtss_state->vtss_features[FEATURE_REDBOX]) {
        // RedBox is bit 270-278 (9 bits)
        rb = (((u16)hdr[1] & 0x7fU) << 2U) | (((u16)hdr[2] & 0xc0U) >> 6U);
    }
#endif

    // TS is bit 232-269 (38 bits)
    xtr_hdr_2 = hdr[2] & 0x3FU; /* For some reason bit6-7 is occasionally
                                      unexpectedly set. Must be cleared */
    tstamp = ((u64)xtr_hdr_2 << 32U);
    tstamp |=
        ((u64)hdr[3] << 24U) | ((u64)hdr[4] << 16U) | ((u64)hdr[5] << 8U) | ((u64)hdr[6] << 0U);

    // DST is bit 153-231 (79 bits), but we only read the 63 LSB for now
    dst = ((u64)hdr[9] << 56U) | ((u64)hdr[10] << 48U) | ((u64)hdr[11] << 40U) |
          ((u64)hdr[12] << 32U);
    dst |=
        ((u64)hdr[13] << 24U) | ((u64)hdr[14] << 16U) | ((u64)hdr[15] << 8U) | ((u64)hdr[16] << 0U);
    vstax_one = (u16)(dst & 1UL); // Bit 152 is the MSB of VSTAX, which must be 1
    dst = (dst >> 1UL);

    // VSTAX is bit 73-152 (80 bits), but we skip bit 63 for now (bit 79 is read
    // above)
    vstax_hi = ((u16)hdr[17] << 8U) | ((u16)hdr[18] << 0U);
    vstax_hi = (vstax_hi >> 1U);
    vstax_lo = ((u64)hdr[19] << 56U) | ((u64)hdr[20] << 48U) | ((u64)hdr[21] << 40U) |
               ((u64)hdr[22] << 32U);
    vstax_lo |=
        ((u64)hdr[23] << 24U) | ((u64)hdr[24] << 16U) | ((u64)hdr[25] << 8U) | ((u64)hdr[26] << 0U);
    vstax_lo = (vstax_lo >> 1U);

    // FWD is bit 45-72 (28 bits), but we only read the 27 LSB for now
    fwd =
        ((u32)hdr[27] << 24U) | ((u32)hdr[28] << 16U) | ((u32)hdr[29] << 8U) | ((u32)hdr[30] << 0U);
    fwd = (fwd >> 5U);

    // MISC is bit 29-44 (16 bits)
    misc = ((u32)hdr[30] << 16U) | ((u32)hdr[31] << 8U) | ((u32)hdr[32] << 0U);
    misc = (misc >> 5U);

    // TAGGING is bit 8-28 (21 bits)
    tagging = ((u32)hdr[32] << 16U) | ((u32)hdr[33] << 8U) | ((u32)hdr[34] << 0U);

    // The VStaX header's MSbit must be 1.
    if (vstax_one != 1U) {
        VTSS_EG(trc_grp, "Invalid Rx header signature");
        return VTSS_RC_ERROR;
    }

    VTSS_MEMSET(info, 0, sizeof(*info));

    info->hw_tstamp = tstamp << 8U;
    info->length = meta->length;
    info->hw_tstamp_decoded = TRUE;

    chip_port = VTSS_EXTRACT_BITFIELD(fwd, 1, SRC_PORT_WID); // FWD:SRC_PORT
    info->port_no = vtss_cmn_chip_to_logical_port(vtss_state, 0U, chip_port);
    if (info->port_no == VTSS_PORT_NO_NONE) {
        VTSS_EG(trc_grp, "Invalid port number");
        return VTSS_RC_ERROR;
    }
    if (chip_port == RT_CHIP_PORT_CPU_0 || chip_port == RT_CHIP_PORT_CPU_1) {
        VTSS_IG(trc_grp, "This frame is transmitted by the CPU itself and should be discarded.");
    }

    //     VTSS_IG(trc_grp, "Received on xtr_qu = %u, chip_no = %d, chip_port =
    //     %u, port_no = %u", meta->xtr_qu, meta->chip_no, chip_port,
    //     info->port_no);

    // TBD_PACKET: Check if bugzilla#17780 is valid for this architecture
    sflow_id = VTSS_EXTRACT_BITFIELD(fwd, FWD_SFLOW_ID_POS, 7); // FWD:SFLOW_ID
    if (sflow_id < RT_CHIP_PORTS) {
        info->sflow_type = VTSS_SFLOW_TYPE_TX;
        info->sflow_port_no = vtss_cmn_chip_to_logical_port(vtss_state, 0U, sflow_id);
    } else if (sflow_id == 125U || sflow_id == 126U) {
        info->sflow_type = VTSS_SFLOW_TYPE_RX;
        info->sflow_port_no = info->port_no;
    } else {
        VTSS_D("MISRA Non empty else");
    }

    info->xtr_qu_mask = VTSS_EXTRACT_BITFIELD(misc, 0U, 8U); // MISC:CPU_MASK

    info->match_id = (u16)VTSS_EXTRACT_BITFIELD64(dst, DST_CL_RSLT_POS, 16U);
    if ((info->match_id & FA_IFH_CL_RSLT_ACL_HIT) != 0U) {
        // ACL hit signalled in DST:CL_RSLT
        info->acl_hit = TRUE;
    }

    info->cosid = (u8)VTSS_EXTRACT_BITFIELD(vstax_hi, 12, 3);
    info->iflow_id = VTSS_EXTRACT_BITFIELD(vstax_hi, 0, 12);
    info->dp = (u8)VTSS_EXTRACT_BITFIELD64(vstax_lo, 60, 2);
    info->cos = (u32)VTSS_EXTRACT_BITFIELD64(vstax_lo, 56, 3);
    info->tag.pcp = (u32)VTSS_EXTRACT_BITFIELD64(vstax_lo, 29, 3);
    info->tag.dei = (VTSS_EXTRACT_BITFIELD64(vstax_lo, 28, 1) != 0U);
    info->tag.vid = (u16)VTSS_EXTRACT_BITFIELD64(vstax_lo, 16, 12);
    info->rb_port_a = (VTSS_EXTRACT_BITFIELD(rb, 7, 1) == 0U);
    info->rb_tagged = (VTSS_EXTRACT_BITFIELD(rb, 8, 1) != 0U);
    info->rb_path_id = (u8)VTSS_EXTRACT_BITFIELD64(dst, 9, 4);    // DST:MPLS
    info->rb_seq_no = (u16)VTSS_EXTRACT_BITFIELD(tagging, 0, 16); // TAGGING:SEQ_NO

    VTSS_RC(vtss_cmn_packet_hints_update(vtss_state, trc_grp, meta->etype, info));
    return VTSS_RC_OK;
}

#if defined(VTSS_ARCH_LAIKA)

vtss_rc vtss_cil_packet_rx_frame(struct vtss_state_s         *vtss_state,
                                 u8 *const                    data,
                                 const u32                    buflen,
                                 vtss_packet_rx_info_t *const rx_info)
{
    u8                    ifh[VTSS_PACKET_HDR_SIZE_BYTES];
    vtss_packet_rx_meta_t meta = {};
    u32                   length;
    vtss_rc               rc = VTSS_RC_INCOMPLETE;
    VTSS_RC(fa_packet_mode_update(vtss_state));
    VTSS_RC(lk_pie_chnl_rx(vtss_state, data, buflen, ifh, &length));
    meta.length = length;
    meta.etype = (data[12] << 8) | data[13];
    rc = vtss_cil_packet_rx_hdr_decode(vtss_state, &meta, ifh, rx_info);
    return rc;
}

#else

vtss_rc vtss_cil_packet_rx_frame(struct vtss_state_s         *vtss_state,
                                 u8 *const                    data,
                                 const u32                    buflen,
                                 vtss_packet_rx_info_t *const rx_info)
{
    vtss_rc rc = VTSS_RC_INCOMPLETE;
    u32     val;
    VTSS_RC(fa_packet_mode_update(vtss_state));

    /* Check if data is ready for grp */
    REG_RD(VTSS_DEVCPU_QS_XTR_DATA_PRESENT, &val);
    if (val != 0U) {
        u32                   ifh[FA_IFH_WORDS];
        u32                   length;
        vtss_packet_rx_grp_t  grp = VTSS_OS_CTZ(val);
        u8                    xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES];
        vtss_packet_rx_meta_t meta;

        /* Get frame, separate IFH and frame data */
        VTSS_RC(fa_rx_frame_get_internal(vtss_state, grp, ifh, data, buflen, &length));

        /* IFH is done separately because of alignment needs */
        VTSS_MEMCPY(xtr_hdr, (u8 *)ifh, sizeof(ifh));
        VTSS_MEMSET(&meta, 0, sizeof(meta));
        meta.length = (length - 4U);
        meta.etype = ((u16)data[12] << 8U) | (u16)data[13];
        rc = vtss_cil_packet_rx_hdr_decode(vtss_state, &meta, xtr_hdr, rx_info);
    }
    return rc;
}

#endif /* VTSS_ARCH_LAIKA */

static u32 fa_plpt_to_ifh(vtss_state_t *vtss_state, vtss_packet_pipeline_pt_t plpt)
{
    u32 retval;
#if defined(VTSS_ARCH_SPARX5)
    switch (plpt) {
    case VTSS_PACKET_PIPELINE_PT_NONE:         retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_RB:       retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_VRAP:     retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_PORT_VOE: retval = 2U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_CL:       retval = 3U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_CLM:      retval = 4U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IPT_PROT: retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_OU_VOI:   retval = 6U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_OU_SW:    retval = 7U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_OU_PROT:  retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_OU_VOE:   retval = 9U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_MID_PROT: retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IN_VOE:   retval = 11U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IN_PROT:  retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IN_SW:    retval = 13U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IN_VOI:   retval = 14U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_VLAN:     retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_DONE:     retval = 16U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_IN_VOI:   retval = 17U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_IN_SW:    retval = 18U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_IN_VOE:   retval = 19U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_OU_VOE:   retval = 20U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_OU_SW:    retval = 21U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_OU_VOI:   retval = 22U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_OU_SAT:   retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE: retval = 24U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_VCAP:     retval = 0U; break;
    default:                                   retval = 0U; break;
    }
#else
    switch (plpt) {
    case VTSS_PACKET_PIPELINE_PT_NONE:         retval = 0U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_RB:       retval = 1U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_VRAP:     retval = 2U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_PORT_VOE: retval = 3U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_CL:       retval = 4U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_CLM:      retval = 5U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IPT_PROT: retval = 6U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_OU_VOI:   retval = 7U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_OU_SW:    retval = 8U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_OU_PROT:  retval = 9U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_OU_VOE:   retval = 10U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_MID_PROT: retval = 11U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IN_VOE:   retval = 12U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IN_PROT:  retval = 13U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IN_SW:    retval = 14U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_IN_VOI:   retval = 15U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_VLAN:     retval = 16U; break;
    case VTSS_PACKET_PIPELINE_PT_ANA_DONE:     retval = 17U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_IN_VOI:   retval = 18U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_IN_SW:    retval = 19U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_IN_VOE:   retval = 20U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_OU_VOE:   retval = 21U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_OU_SW:    retval = 22U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_OU_VOI:   retval = 23U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_OU_SAT:   retval = 24U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE: retval = 25U; break;
    case VTSS_PACKET_PIPELINE_PT_REW_VCAP:     retval = 26U; break;
    default:                                   retval = 0U; break;
    }
#endif
    return retval;
}

static vtss_rc fa_ptp_action_to_ifh(vtss_packet_ptp_action_t ptp_action,
                                    u8                       ptp_domain,
                                    BOOL                     afi,
                                    u32                     *result) /* TBD_henrikb */
{
    vtss_rc rc = VTSS_RC_OK;

    switch (ptp_action) {
    case VTSS_PACKET_PTP_ACTION_ONE_STEP: *result = 1U; break;

    case VTSS_PACKET_PTP_ACTION_TWO_STEP: *result = 4U; break;

    case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP: *result = 3U; break;

    case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ: *result = 7U; break;

    case VTSS_PACKET_PTP_ACTION_AFI_NONE: *result = 12U; break;

    default:
        VTSS_E("Invalid PTP action (%d)", ptp_action);
        *result = 0U;
        rc = VTSS_RC_ERROR;
        break;
    }

    *result = *result | ((u32)ptp_domain << 6U);

    return rc;
}

static void IFH_ENCODE_BITFIELD(u8 *const bin_hdr, u64 value, u32 pos, u32 width)
{
    if (width > 40U) {
        /* Max width is 5 bytes - 40 bits.
           In worst case this will spread over 6 bytes - 48 bits*/
        return;
    }

    u32 byte = (35U - (pos / 8U)); /* Calculate the Start IFH byte position of
                                    this IFH bit position */
    u32 bit = (pos % 8U);          /* Calculate the Start bit position in the Start IFH byte */
    u64 encode = VTSS_ENCODE_BITFIELD64(value, bit, width); /* Encode the bit field into
                                                               a 32 bit variable. */

    if ((encode & 0xFFUL) != 0U) {
        bin_hdr[byte] |= (u8)((encode & 0xFFU)); /* The b0-b7 goes into the start IFH byte */
    }
    if ((encode & 0xFF00UL) != 0U) {
        bin_hdr[byte - 1U] |=
            (u8)((encode & 0xFF00UL) >> 8U); /* The b8-b15 goes into the next IFH byte */
    }
    if ((encode & 0xFF0000UL) != 0U) {
        bin_hdr[byte - 2U] |=
            (u8)((encode & 0xFF0000U) >> 16U); /* The b16-b23 goes into the next IFH byte */
    }
    if ((encode & 0xFF000000UL) != 0U) {
        bin_hdr[byte - 3U] |=
            (u8)((encode & 0xFF000000UL) >> 24U); /* The b24-b31 goes into the next IFH byte */
    }
    if ((encode & 0xFF00000000UL) != 0U) {
        bin_hdr[byte - 4U] |=
            (u8)((encode & 0xFF00000000UL) >> 32U); /* The b32-b39 goes into the next IFH byte */
    }
    if ((encode & 0xFF0000000000UL) != 0U) {
        bin_hdr[byte - 5U] |=
            (u8)((encode & 0xFF0000000000UL) >> 40U); /* The b40-b47 goes into the next IFH byte */
    }
}

/*****************************************************************************/
// fa_tx_hdr_encode()
/*****************************************************************************/
static u32 pdu_type_calc(const vtss_packet_tx_info_t *const info)
{
    u32 retval = 0U;
    switch (info->oam_type) {
    case VTSS_PACKET_OAM_TYPE_NONE:      break; // Do nothing
    case VTSS_PACKET_OAM_TYPE_MRP_TST:   retval = 10U; break;
    case VTSS_PACKET_OAM_TYPE_MRP_ITST:  retval = 10U; break;
    case VTSS_PACKET_OAM_TYPE_DLR_BCN:   retval = 11U; break;
    case VTSS_PACKET_OAM_TYPE_DLR_ADV:   retval = 11U; break;
    case VTSS_PACKET_OAM_TYPE_MPLS_TP_1: retval = 2U; break;
    case VTSS_PACKET_OAM_TYPE_MPLS_TP_2: retval = 2U; break;
    default:                             retval = 1U; break; // Y1731 OAM
    }
    if (retval != 0U) {
        return retval;
    }

    if (info->ptp_action != VTSS_PACKET_PTP_ACTION_NONE) {
        if (info->inj_encap.type == VTSS_PACKET_ENCAP_TYPE_IP4) {
            return 6U;
        }
        if (info->inj_encap.type == VTSS_PACKET_ENCAP_TYPE_IP6) {
            return 7U;
        }
        return 5U;
    }

    return 0U;
}

vtss_rc vtss_cil_packet_tx_hdr_encode(struct vtss_state_s *const         vtss_state,
                                      const vtss_packet_tx_info_t *const info,
                                      u8 *const                          bin_hdr,
                                      u32 *const                         bin_hdr_len)
{
    vtss_prio_t               icos;
    vtss_phys_port_no_t       chip_port, src_port = RT_CHIP_PORT_CPU_0;
    BOOL                      rewrite = TRUE, setup_cl = FALSE, afi = FALSE;
    u32                       mi_port, pl_act = 0U, vid, pdu_type = 0U, isdx = info->iflow_id;
    vtss_packet_pipeline_pt_t pl_pt = VTSS_PACKET_PIPELINE_PT_NONE;

    if (bin_hdr == NULL) {
        // Caller wants us to return the number of bytes required to fill
        // in #bin_hdr. We need FA_IFH_BYTES (36) bytes for the IFH.
        *bin_hdr_len = FA_IFH_BYTES;
        return VTSS_RC_OK;
    } else if (*bin_hdr_len < FA_IFH_BYTES) {
        VTSS_E("Invalid IFH length: %u  min: %u", *bin_hdr_len, FA_IFH_BYTES);
        return VTSS_RC_ERROR;
    } else {
        VTSS_D("MISRA Non empty else");
    }

    *bin_hdr_len = FA_IFH_BYTES;
    VTSS_MEMSET(bin_hdr, 0, FA_IFH_BYTES); /* IFH is all zero. From now on bits can be set
                                              by OR. No bit clear should be required */

    IFH_ENCODE_BITFIELD(bin_hdr, 1U, VSTAX + 79U,
                        1U); // VSTAX.RSV = 1. MSBit must be 1
    IFH_ENCODE_BITFIELD(bin_hdr, 1U, VSTAX + 55U,
                        1U); // VSTAX.INGR_DROP_MODE = Enable. Don't make
                             // head-of-line blocking
    IFH_ENCODE_BITFIELD(bin_hdr, 1U, FWD_UPDATE_FCS,
                        1U); // FWD.UPDATE_FCS = Enable. Enforce update of FCS.

#if defined(VTSS_FEATURE_AFI_SWC)
    if (info->afi_id != VTSS_AFI_ID_NONE) {
        afi = TRUE;
        // The CPU wants this frame to go into the AFI packet memory for
        // repetitive injection.
        IFH_ENCODE_BITFIELD(bin_hdr, 1U, FWD_AFI_INJ, 1U); // FWD.AFI_INJ = Enable
    }
#endif

    // FIXME: Super-priority injection
    icos = (info->cos >= 8U ? 7U : info->cos);

    if (info->switch_frm) {
        // This is a switched frame - the frame is injected into the switch */
        pl_act = 2U; // MISC.PIPELINE_ACT = INJ_MASQ
        if (info->masquerade_port != VTSS_PORT_NO_NONE) {
            // OAM Injection in an Up-MEP/MIP - The following will be according
            // to TN1258 (EVC Baseline)
            VTSS_DG(VTSS_TRACE_GROUP_PACKET, "Masqueraded OAM/Y1564 Injecting");

            chip_port = VTSS_CHIP_PORT_FROM_STATE(vtss_state, info->masquerade_port);
            IFH_ENCODE_BITFIELD(bin_hdr, ((u64)chip_port % 32U), VSTAX + 0U,
                                5U); // VSTAX.SRC.SRC_UPSPN = masquerade chip port
            IFH_ENCODE_BITFIELD(bin_hdr, ((u64)chip_port / 32U), VSTAX + 5U,
                                5U); // VSTAX.SRC.SRC_UPSID = masquerade chip port
            src_port = chip_port;    // FWD.SRC_PORT = masquerade port
            setup_cl = TRUE;         // Setup classified fields later
            pl_pt = info->pipeline_pt;
            if (info->oam_type != VTSS_PACKET_OAM_TYPE_NONE &&
                pl_pt != VTSS_PACKET_PIPELINE_PT_NONE && pl_pt != VTSS_PACKET_PIPELINE_PT_ANA_CLM) {
                pdu_type = 1U; // DST.PDU_TYPE = OAM_Y1731
            }
        }
    } else {
        // Not a switched frame.
        // Add mirror port if CPU ingress mirroring or egress mirroring on
        // dst_port is enabled.
        mi_port = vtss_state->l2.mirror_conf.port_no;
#if defined(VTSS_FEATURE_AFI_SWC)
        if (!afi)
#endif
        {
            if (mi_port < vtss_state->port_count &&
                (vtss_state->l2.mirror_cpu_ingress ||
                 vtss_state->l2.mirror_egress[info->dst_port]) &&
                vtss_state->l2.port_state[mi_port]) {
                IFH_ENCODE_BITFIELD(bin_hdr, FA_MIRROR_PROBE_RX + 1U, FWD_MIRROR_PROBE,
                                    2U); /* FWD.MIRROR_PROBE = Ingress mirror probe.
                                           1-based in this field */
            }
        }

        pdu_type = pdu_type_calc(info);

        if (info->ptp_action != VTSS_PACKET_PTP_ACTION_NONE) {
            // PTP injection
            u32 rew_cmd;

            rewrite = TRUE;
            VTSS_DG(VTSS_TRACE_GROUP_PACKET, "Injecting with PTP action: %d, pdu_offset %u",
                    info->ptp_action, info->pdu_offset);
            VTSS_RC(fa_ptp_action_to_ifh(info->ptp_action, info->ptp_domain, afi, &rew_cmd));
            VTSS_DG(VTSS_TRACE_GROUP_PACKET, "Injecting rew_cmd: 0x%x, ptp_timestamp %" PRIu64 "",
                    rew_cmd, info->ptp_timestamp);
            IFH_ENCODE_BITFIELD(bin_hdr, (u64)rew_cmd, VSTAX + 32U,
                                10U); // VSTAX.REW_CMD = PTP rewrite command.
                                      // (when FWD_MODE == FWD_LLOOKUP).
            pl_pt = VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE;
        } else if (info->oam_type != VTSS_PACKET_OAM_TYPE_NONE) {
            // OAM injection
            VTSS_DG(VTSS_TRACE_GROUP_PACKET, "OAM Injecting");
            IFH_ENCODE_BITFIELD(bin_hdr, 1U, VSTAX + 59U,
                                1U); // VSTAX.SP = 1. Super Priority
            pl_pt = info->pipeline_pt;

            if (info->pipeline_pt != VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE ||
                info->oam_type == VTSS_PACKET_OAM_TYPE_LCK) {
                /* Injecting LCK is done in the client flow. This must hit the
                 * ES0 */
                rewrite = TRUE;
            } else {
                rewrite = FALSE;
            }
        } else {
            // Normal port injection without rewriting, unless asked to rewrite.
            rewrite = (info->tag.tpid == 0U && info->tag.vid != VTSS_VID_NULL);
            pl_pt = (info->pipeline_pt == VTSS_PACKET_PIPELINE_PT_NONE
                         ? VTSS_PACKET_PIPELINE_PT_ANA_DONE
                         : info->pipeline_pt);
        }

        chip_port = VTSS_CHIP_PORT_FROM_STATE(vtss_state, info->dst_port);
#if defined(VTSS_FEATURE_AFI_SWC)
        if (!afi)
#endif
        {
            // Must be 0 for AFI-injected frames, or the REW will see this as a
            // CPU queue mask and not work as expected. The destination port is
            // chosen during mesa_afi_slow_inj_alloc()/mesa_afi_fast_inj_alloc()
            IFH_ENCODE_BITFIELD(bin_hdr, (u64)chip_port, 29U,
                                8U); // MISC.CPU_MASK = Destination port. For
                                     // injected frames this field is Destination
                                     // port.
        }

        pl_act = 1U; // MISC.PIPELINE_ACT = INJ
        IFH_ENCODE_BITFIELD(bin_hdr, (rewrite ? 0U : 1U), 45U,
                            1U); // FWD.DO_NOT_REW = 0 => do rewrite, 1 => do not
                                 // rewrite
        IFH_ENCODE_BITFIELD(bin_hdr, (u64)icos, VSTAX + 56U,
                            3U); // VSTAX.CL_COS = cos. qos_class/iprio (internal
                                 // priority)

        if (rewrite) {
            setup_cl = TRUE; // Setup classified fields later
            IFH_ENCODE_BITFIELD(bin_hdr, info->dp, VSTAX + 60U,
                                2U); // VSTAX.CL_DP = dp.
            if (info->tag.tpid != 0U && info->tag.tpid != 0x8100U) {
                IFH_ENCODE_BITFIELD(bin_hdr, 1U, VSTAX + 14U,
                                    1U); // VSTAX.TAG.TAG_TYPE = 1. S-TAG
            }
        } else if (info->pipeline_pt == VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE &&
                   info->oam_type != VTSS_PACKET_OAM_TYPE_NONE && isdx == VTSS_ISDX_NONE) {
            // ESO_ISDX_KEY_ENA is configured to the opposite of the requested.
            // Try not to hit ES0 when no rewriting is calculated
            IFH_ENCODE_BITFIELD(bin_hdr, 1U, FWD_ESO_ISDX_KEY_ENA,
                                1U); // FWD.ESO_ISDX_KEY_ENA = 1
            IFH_ENCODE_BITFIELD(bin_hdr, (u64)info->cosid, VSTAX + 76U,
                                3U); // VSTAX.COSID = cosid.
        } else {
            VTSS_D("MISRA Non empty else");
        }
    } /* switched frame */

    IFH_ENCODE_BITFIELD(bin_hdr, 124, FWD_SFLOW_ID,
                        7U); // FWD.SFLOW_ID (disable SFlow sampling)
    IFH_ENCODE_BITFIELD(bin_hdr, (u64)fa_plpt_to_ifh(vtss_state, pl_pt), 37U,
                        5U);                            // MISC.PIPELINE_PT
    IFH_ENCODE_BITFIELD(bin_hdr, (u64)pl_act, 42U, 3U); // MISC.PIPELINE_ACT

    if (pdu_type != 0U) {
        if (info->pdu_offset == 0U || (info->pdu_offset % 2U) != 0U) {
            VTSS_E("Invalid pdu_offset %u. It must be an even number greater than 0",
                   info->pdu_offset);
            return VTSS_RC_ERROR;
        }
        IFH_ENCODE_BITFIELD(bin_hdr, ((u64)info->pdu_offset / 2U), DST_PDU_W16_OFFSET,
                            6U);                                       // DST.PDU_W16_OFFSET
        IFH_ENCODE_BITFIELD(bin_hdr, (u64)pdu_type, DST_PDU_TYPE, 4U); // DST.PDU_TYPE
    }

    if (setup_cl) {
        IFH_ENCODE_BITFIELD(bin_hdr, (u64)info->cosid, VSTAX + 76U,
                            3U); // VSTAX.COSID = cosid.
        IFH_ENCODE_BITFIELD(bin_hdr, (u64)icos, VSTAX + 56U,
                            3U); // VSTAX.CL_COS = cos. qos_class/iprio (internal
                                 // priority)
        IFH_ENCODE_BITFIELD(bin_hdr, (u64)info->tag.pcp, VSTAX + 29U,
                            3U); // VSTAX.TAG.CL_PCP = pcp.
        IFH_ENCODE_BITFIELD(bin_hdr, (info->tag.dei ? 1U : 0U), VSTAX + 28U,
                            1U); // VSTAX.TAG.CL_DEI = dei.
        vid = info->tag.vid;
        if (vid >= VTSS_VIDS) {
            // Extended VID
            IFH_ENCODE_BITFIELD(bin_hdr, 1U, DST_XVID_EXT,
                                1U); // DST.XVID_EXT = Enable.
            vid = (VTSS_VIDS - vid);
        }
        IFH_ENCODE_BITFIELD(bin_hdr, (u64)vid, VSTAX + 16U,
                            12U); // VSTAX.TAG.CL_VID = vid.
        if (isdx != VTSS_ISDX_NONE) {
            IFH_ENCODE_BITFIELD(bin_hdr, 1U, FWD_ESO_ISDX_KEY_ENA,
                                1U); // FWD.ESO_ISDX_KEY_ENA = 1
            IFH_ENCODE_BITFIELD(bin_hdr, (u64)isdx, VSTAX + 64U,
                                12U); // VSTAX.MISH.ISDX = isdx
        }
    }
    IFH_ENCODE_BITFIELD(bin_hdr, (((u64)info->ptp_timestamp >> 8U) & 0xFFFFFFFFFFU), 232U,
                        40U); // TS = 40 bits PTP time stamp

#if defined(VTSS_FEATURE_REDBOX)
    if (vtss_state->vtss_features[FEATURE_REDBOX]) {
        if (info->rb_tag_disable) {
            // RB.RB_TAG: Disable RedBox tagging
            IFH_ENCODE_BITFIELD(bin_hdr, 1U, 272U, 1U);
        }

        // RB.RB_CMD.FWD_SEL: RedBox forwarding
        IFH_ENCODE_BITFIELD(bin_hdr, (u64)info->rb_fwd, 273U, 2U);

        if (info->rb_dd_disable) {
            // RB.RB_CMD.DD_DISABLE
            IFH_ENCODE_BITFIELD(bin_hdr, 1U, 275U, 1U); // Disable RedBox Duplicate
                                                        // Discard processing
        }

        if (info->rb_ring_netid_enable) {
            // RB.RB_CMD.NETID_ENA: Use ring_netid instead of netid in HSR tag
            IFH_ENCODE_BITFIELD(bin_hdr, 1U, 276U, 1U);
        }

        if (info->rb_tag_ptp) {
            u8 path_id = info->rb_path_id;

            // RB.RB_TC0
            IFH_ENCODE_BITFIELD(bin_hdr, 1U, 271U, 1U);

            if ((path_id & 1U) > 0U) {
                // DST.MPLS_SBIT: LAN_B flag
                IFH_ENCODE_BITFIELD(bin_hdr, 1U, 165U, 1U);
            }

            // DST.MPLS_TC: Net ID
            path_id >>= 1U;
            IFH_ENCODE_BITFIELD(bin_hdr, (u64)path_id, 162U, 3U);

            // TAGGING.SEQ_NO: Sequence number
            IFH_ENCODE_BITFIELD(bin_hdr, (u64)info->rb_seq_no, 8U, 16U);
            src_port = VTSS_CHIP_PORT_FROM_STATE(vtss_state, info->dst_port);
        }
    }
#endif
    // FWD.SRC_PORT: Source port
    IFH_ENCODE_BITFIELD(bin_hdr, (u64)src_port, 46U, SRC_PORT_WID);

    VTSS_IG(VTSS_TRACE_GROUP_PACKET, "IFH:");
    VTSS_IG_HEX(VTSS_TRACE_GROUP_PACKET, &bin_hdr[0], *bin_hdr_len);
    return VTSS_RC_OK;
}

#if defined(VTSS_ARCH_LAIKA)

vtss_rc vtss_cil_packet_tx_frame_ifh(struct vtss_state_s              *vtss_state,
                                     const vtss_packet_tx_ifh_t *const ifh,
                                     const u8 *const                   frame,
                                     const u32                         length)
{
    VTSS_RC(fa_packet_mode_update(vtss_state));
    return lk_pie_chnl_tx(vtss_state, frame, length, ifh);
}

#else
static vtss_rc fa_tx_frame_ifh_vid(struct vtss_state_s              *vtss_state,
                                   const vtss_packet_tx_ifh_t *const ifh,
                                   const u8 *const                   frame,
                                   const u32                         length)
{
    u32                  val, w, count, last;
    const u8            *buf = frame;
    vtss_packet_tx_grp_t grp = 1U;

    VTSS_N("length: %u, ifhlen: %d", length, ifh->length);

    VTSS_RC(fa_packet_mode_update(vtss_state));

    if (ifh->length != FA_IFH_BYTES) {
        return VTSS_RC_ERROR;
    }

    REG_RD(VTSS_DEVCPU_QS_INJ_STATUS, &val);
    if ((VTSS_X_DEVCPU_QS_INJ_STATUS_FIFO_RDY(val) & VTSS_BIT(grp)) == 0U) {
        VTSS_E("Not ready");
        return VTSS_RC_ERROR;
    }

    if ((VTSS_X_DEVCPU_QS_INJ_STATUS_WMARK_REACHED(val) & VTSS_BIT(grp)) != 0U) {
        VTSS_E("Watermark reached");
        return VTSS_RC_ERROR;
    }

    /* Indicate SOF */
    REG_WR(VTSS_DEVCPU_QS_INJ_CTRL(grp),
           VTSS_F_DEVCPU_QS_INJ_CTRL_GAP_SIZE(1) | VTSS_M_DEVCPU_QS_INJ_CTRL_SOF);

    // Write the IFH to the chip.
    for (w = 0U; w < FA_IFH_WORDS; w++) {
        REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), ifh->ifh[w]);
    }

    /* Write words, round up */
    count = ((length + 3U) / 4U);
    last = length % 4U;
    for (w = 0U; w < count; w++) {
#ifdef VTSS_OS_BIG_ENDIAN
        REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp),
               ((u32)buf[0] << 24) | ((u32)buf[1] << 16) | ((u32)buf[2] << 8) | (u32)buf[3]);
#else
        REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp),
               ((u32)buf[3] << 24) | ((u32)buf[2] << 16) | ((u32)buf[1] << 8) | (u32)buf[0]);
#endif
        buf += 4;
    }

    /* Add padding */
    while (w < (60U / 4U)) {
        REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), 0);
        w++;
    }

    /* Indicate EOF and valid bytes in last word */
    REG_WR(VTSS_DEVCPU_QS_INJ_CTRL(grp),
           VTSS_F_DEVCPU_QS_INJ_CTRL_GAP_SIZE(1) |
               VTSS_F_DEVCPU_QS_INJ_CTRL_VLD_BYTES(length < 60U ? 0U : last) |
               VTSS_M_DEVCPU_QS_INJ_CTRL_EOF);

    /* Add dummy CRC */
    REG_WR(VTSS_DEVCPU_QS_INJ_WR(grp), 0);

    VTSS_N("wrote %u words, last: %u", (w + 1), last);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_packet_tx_frame_ifh(struct vtss_state_s              *vtss_state,
                                     const vtss_packet_tx_ifh_t *const ifh,
                                     const u8 *const                   frame,
                                     const u32                         length)
{
    return fa_tx_frame_ifh_vid(vtss_state, ifh, frame, length);
}

#endif /* VTSS_ARCH_LAIKA */

/* - Debug print --------------------------------------------------- */

static vtss_rc fa_debug_pkt(vtss_state_t                  *vtss_state,
                            lmu_ss_t                      *ss,
                            const vtss_debug_info_t *const info)
{
    u32 qu, i, j, cfg, cur, max;

    vtss_fa_debug_reg_header(ss, "FRAME_COPY_CFG");
    for (qu = 0U; qu < 12U; qu++) {
        if (qu < 8U) {
            vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_QFWD_FRAME_COPY_CFG(qu)), qu,
                                   "CFG_CPU_QU");
        } else if (qu == 8U) {
            vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_QFWD_FRAME_COPY_CFG(qu)), qu,
                                   "CFG_LRN_ALL");
        } else {
            vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_QFWD_FRAME_COPY_CFG(qu)), qu,
                                   "CFG_MIRROR_PROBE");
        }
    }
    pr("\n");

    vtss_fa_debug_reg_header(ss, "IFH_CTRL");
    for (qu = 0U; qu < 4U; qu++) {
        u32 port = VTSS_CHIP_PORT(qu);

        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_REW_IFH_CTRL(port)), port,
                               "KEEP_IFH_SEL");
    }
    pr("\n");

    vtss_fa_debug_reg_header(ss, "PORT_CFG");
    for (qu = 0U; qu < 4U; qu++) {
        u32 port = VTSS_CHIP_PORT(qu);
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_ASM_PORT_CFG(port)), port, "PORT_CFG");
    }
    pr("\n");

    vtss_fa_debug_reg_header(ss, "PORT_STATUS");
    for (qu = 0U; qu < 4U; qu++) {
        u32 port = VTSS_CHIP_PORT(qu);
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_ASM_PORT_STICKY(port)), port,
                               "PORT_STATUS");
        REG_WR(VTSS_ASM_PORT_STICKY(port), 0xFFFFFFFFU);
    }
    pr("\n");

#if defined(VTSS_ARCH_LAIKA)
    lk_debug_pkt(vtss_state, ss, info);
#else
    vtss_fa_debug_reg_header(ss, "DEVCPU_QS");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_QS_XTR_CFG), "XTR_CFG");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_QS_VTSS_DBG), "INJ_FRM_CNT");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_QS_XTR_DATA_PRESENT),
                      "XTR_DATA_PRESENT");
    for (i = 0U; i < 2U; i++) {
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_QS_XTR_GRP_CFG(i)), i,
                               "XTR_GRP_CFG");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_QS_INJ_GRP_CFG(i)), i,
                               "INJ_GRP_CFG");
    }
    pr("\n");
#endif

    vtss_fa_debug_reg_header(ss, "QFWD");
    for (i = RT_CHIP_PORT_CPU_0; i <= RT_CHIP_PORT_CPU_1; i++) {
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_QFWD_SWITCH_PORT_MODE(i)), i,
                               "PORT_MODE");
    }
    pr("\n");

    pr("IDX   Port/Queue    CFG   CUR   MAX\n");
    for (i = RT_CHIP_PORT_CPU_0; i <= RT_CHIP_PORT_CPU_1; i++) {
        for (qu = 0U; qu < VTSS_PRIOS; qu++) {
            j = (2048U + i * VTSS_PRIOS + qu);
            REG_RD(VTSS_QRES_RES_CFG(j), &cfg);
            REG_RD(VTSS_QRES_RES_STAT_CUR(j), &cur);
            REG_RD(VTSS_QRES_RES_STAT(j), &max);
            pr("%-6u%u (CPU_%u_%u)  %-6u%-6u%-6u\n", j, i, i - RT_CHIP_PORT_CPU, qu, cfg, cur, max);
        }
    }
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_packet_debug_print(vtss_state_t                  *vtss_state,
                                   lmu_ss_t                      *ss,
                                   const vtss_debug_info_t *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_PACKET, fa_debug_pkt, vtss_state, ss, info);
}

/* - Initialization ------------------------------------------------ */
static vtss_rc fa_packet_init(vtss_state_t *vtss_state)
{
    vtss_packet_rx_queue_t qu;
    u32                    val;
    u32                    i, port;
    u32                    pcp, dei;
    vtss_rc                rc = VTSS_RC_OK;

#if defined(VTSS_ARCH_LAIKA)
    rc = lk_init(vtss_state);
#endif
    // The extraction queues can be redirected to any port.
    // This is used to redirect selected queues to an NPI port, but also the
    // FDMA (if included) may use this feature to redirect to a dummy port when
    // throttling. The NPI settings take precedence over the FDMA, but we need
    // to keep track of what the FDMA wants to set it to in case the application
    // enables and disables NPI redirection.
    for (qu = 0U; qu < vtss_state->packet.rx_queue_count; qu++) {
        i = QFWD_FRAME_COPY_CFG_CPU_QU(qu);
        REG_RD(VTSS_QFWD_FRAME_COPY_CFG(i), &val);
        vtss_state->packet.default_qu_redirect[qu] = VTSS_X_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL(val);
        REG_WRM(VTSS_QFWD_FRAME_COPY_CFG(i),
                VTSS_F_QFWD_FRAME_COPY_CFG_FRMC_QOS_VAL(qu) |
                    VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_QOS_ENA,
                VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_QOS_VAL | VTSS_M_QFWD_FRAME_COPY_CFG_FRMC_QOS_ENA);
    }

    // Setup CPU port 0 and 1 to allow for classification of transmission of
    // switched frames into a user-module-specifiable QoS class.
    // For the two CPU ports, we set a one-to-one mapping between a VLAN tag's
    // PCP and a QoS class. When transmitting switched frames, the PCP value
    // of the VLAN tag (which is always inserted to get it switched on a given
    // VID), then controls the priority.
    // Enable looking into PCP and DEI bits
    REG_WRM(VTSS_ANA_CL_QOS_CFG(RT_CHIP_PORT_CPU),
            VTSS_F_ANA_CL_QOS_CFG_PCP_DEI_DP_ENA(1) | VTSS_F_ANA_CL_QOS_CFG_PCP_DEI_QOS_ENA(1),
            VTSS_M_ANA_CL_QOS_CFG_PCP_DEI_DP_ENA | VTSS_M_ANA_CL_QOS_CFG_PCP_DEI_QOS_ENA);

    // Set-up the one-to-one PCP->QoS mapping
    for (pcp = 0U; pcp < VTSS_PCP_END - VTSS_PCP_START; pcp++) {
        for (dei = 0U; dei < VTSS_DEI_END - VTSS_DEI_START; dei++) {
            REG_WR(VTSS_ANA_CL_PCP_DEI_MAP_CFG(RT_CHIP_PORT_CPU, (8U * dei + pcp)),
                   VTSS_F_ANA_CL_PCP_DEI_MAP_CFG_PCP_DEI_QOS_VAL(pcp));
        }
    }

    for (i = RT_CHIP_PORT_CPU_0; i <= RT_CHIP_PORT_CPU_1; i++) {
        // Disable aging of Rx CPU queues to allow the frames to stay there
        // longer than on normal front ports.
        REG_WRM(VTSS_HSCH_PORT_MODE(i), VTSS_F_HSCH_PORT_MODE_AGE_DIS(1),
                VTSS_M_HSCH_PORT_MODE_AGE_DIS);
        REG_WRM(VTSS_DSM_BUF_CFG(i), VTSS_F_DSM_BUF_CFG_AGING_ENA(0), VTSS_M_DSM_BUF_CFG_AGING_ENA);
        REG_WRM(VTSS_ASM_PORT_CFG(i), VTSS_F_ASM_PORT_CFG_FRM_AGING_DIS(1),
                VTSS_M_ASM_PORT_CFG_FRM_AGING_DIS);

        // Enable stacking on CPU ports for VLAN classification purposes
        REG_WRM(VTSS_ANA_CL_STACKING_CTRL(i), VTSS_F_ANA_CL_STACKING_CTRL_STACKING_AWARE_ENA(1),
                VTSS_M_ANA_CL_STACKING_CTRL_STACKING_AWARE_ENA);
        REG_WRM(VTSS_ANA_CL_STACKING_CTRL(i),
                VTSS_F_ANA_CL_STACKING_CTRL_STACKING_HEADER_DISCARD_ENA(0),
                VTSS_M_ANA_CL_STACKING_CTRL_STACKING_HEADER_DISCARD_ENA);

        // Set CPU ports to be VLAN aware, since frames that we send switched
        // must contain a VLAN tag for correct classification. One could use
        // the frame's VStaX header, but that won't work for stacking solutions.
        // We also set it to pop one tag.
        REG_WRM(VTSS_ANA_CL_VLAN_CTRL(i),
                VTSS_F_ANA_CL_VLAN_CTRL_PORT_VID(0) | VTSS_F_ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA(1) |
                    VTSS_F_ANA_CL_VLAN_CTRL_VLAN_POP_CNT(1),
                VTSS_M_ANA_CL_VLAN_CTRL_PORT_VID | VTSS_M_ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA |
                    VTSS_M_ANA_CL_VLAN_CTRL_VLAN_POP_CNT);

        // Disable IGMP redirect for CPU ports
        REG_WR(VTSS_ANA_CL_CAPTURE_CFG(i), 0);
    }

    // Make sure the ports are not VStaX aware, because that will cause the
    // switch to move a possible VStaX header from the frame into the IFH.
    // This is not NPI-port compatible.
    for (port = 0U; port < RT_CHIP_PORTS; port++) {
        REG_WRM(VTSS_ASM_PORT_CFG(port), VTSS_F_ASM_PORT_CFG_VSTAX2_AWR_ENA(0),
                VTSS_M_ASM_PORT_CFG_VSTAX2_AWR_ENA);
    }

    return rc;
}

vtss_rc vtss_fa_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_packet_state_t *state = &vtss_state->packet;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->rx_ifh_size = VTSS_FA_RX_IFH_SIZE;
        state->rx_queue_count = VTSS_PACKET_RX_QUEUE_CNT;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_INIT, 30);
        VTSS_RC(fa_packet_init(vtss_state));
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_INIT, 30);
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_PMAP, 30);
        if (!vtss_state->warm_start_cur) {
            VTSS_RC(vtss_cil_packet_rx_conf_set(vtss_state));
        }
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_PMAP, 30);
        break;
    default: VTSS_D("MISRA Non empty default"); break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_FA */
