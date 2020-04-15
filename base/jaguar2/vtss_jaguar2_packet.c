/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_jaguar2_cil.h"
#include "vtss_ts_api.h"

// Avoid Lint Warning 572: Excessive shift value (precision 1 shifted right by 2), which occurs
// in this file because (t) - VTSS_IO_ORIGIN1_OFFSET == 0 for t = VTSS_TO_CFG (i.e. ICPU_CFG), and 0 >> 2 gives a lint warning.
/*lint --e{572} */
#if defined(VTSS_ARCH_JAGUAR_2)

// Manual injection mode uses FDMA Channel 9 (Port 54 Injection Direction, CPU group 1)
#define VTSS_FDMA_CH_INJ_MANUAL_MODE 9

/* - CIL functions ------------------------------------------------- */

#define JR2_IFH_WORDS (VTSS_JR2_RX_IFH_SIZE / 4)    /* 7 32-bit words in an IFH */
#define JR2_IFH_BYTES (VTSS_JR2_RX_IFH_SIZE)        /* 28 bytes words in an IFH */

/* ================================================================= *
 *  NPI
 * ================================================================= */

static vtss_rc jr2_npi_redirect_qu_to_port(vtss_state_t *vtss_state, vtss_packet_rx_queue_t qu, vtss_phys_port_no_t chip_port)
{
    JR2_WRM(VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_CPU_QU(qu)), VTSS_F_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL(chip_port), VTSS_M_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL);

    return VTSS_RC_OK;
}

static vtss_rc jr2_npi_mask_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t  *rx_conf  = &vtss_state->packet.rx_conf;
    vtss_npi_conf_t        *npi_conf = &vtss_state->packet.npi_conf;
    vtss_packet_rx_queue_t qu;

    for (qu = 0; qu < vtss_state->packet.rx_queue_count; qu++) {
        BOOL npi_redirect = npi_conf->port_no != VTSS_PORT_NO_NONE && rx_conf->queue[qu].npi.enable;

        VTSS_RC(jr2_npi_redirect_qu_to_port(vtss_state, qu, npi_redirect ? VTSS_CHIP_PORT(npi_conf->port_no) : vtss_state->packet.default_qu_redirect[qu]));
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_npi_update(vtss_state_t *vtss_state)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;

    VTSS_RC(jr2_npi_mask_set(vtss_state));

    if (conf->port_no != VTSS_PORT_NO_NONE) {
        u32 port = VTSS_CHIP_PORT(conf->port_no);

        // Control IFH insertion and parsing.
        // If npi_conf.enable == TRUE:
        //   When egressing the NPI port, use short prefix
        //   When ingressing the NPI port, use short prefix.
        // else
        //   Use no encapsulation.
        //
        //  Definition of prefix formats:
        //    No prefix      (0): Frame
        //    IFH w/o prefix (1): IFH, Frame
        //    Short prefix   (2): any DMAC, any SMAC, EtherType=0x8880, payload=0x0007, IFH, Frame
        //    Long prefix    (3): any DMAC, any SMAC, VLAN Tag, EtherType=0x8880, payload=0x0007, IFH, Frame
        JR2_WRM(VTSS_REW_COMMON_PORT_CTRL(port), VTSS_F_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL(conf->enable ? 2 : 0), VTSS_M_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL);
        JR2_WRM(VTSS_ASM_CFG_PORT_CFG    (port), VTSS_F_ASM_CFG_PORT_CFG_INJ_FORMAT_CFG  (conf->enable ? 2 : 0), VTSS_M_ASM_CFG_PORT_CFG_INJ_FORMAT_CFG);
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_npi_conf_set(vtss_state_t *vtss_state, const vtss_npi_conf_t *const new)
{
    vtss_npi_conf_t *conf = &vtss_state->packet.npi_conf;

    // Disable current NPI port
    conf->enable = FALSE;
    VTSS_RC(jr2_npi_update(vtss_state));

    // Set new NPI port
    *conf = *new;
    VTSS_RC(jr2_npi_update(vtss_state));

    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc jr2_packet_phy_cnt_to_ts_cnt(vtss_state_t  *vtss_state,
                                            u32           phy_cnt,
                                            u64           *ts_cnt)
{
    vtss_timestamp_t ts;
    u32       tc;
    u32       phy_tc;
    u64       tc_64;

    /* in Jaguar 2 the timeofday is sampled 2 or more times pr sec, phy's are assumed to belong to domain 0 */
    _vtss_ts_domain_timeofday_get(NULL, 0, &ts, &tc_64);
    phy_tc = ts.nanoseconds + VTSS_ONE_MIA * ts.seconds;

    tc = tc_64 >> 16;       /* The tc_64 returned by _vtss_ts_domain_timeofday_get() is in 16 bit fractions of nanoseconds */
    tc += (phy_cnt - phy_tc);
    tc_64 = (u64)tc << 16;  /* Must return in 16 bit fractions of nanoseconds */

    VTSS_I("phy_cnt. %u, ts.sec %u, ts.ns %u, tc %" PRIu64 "", phy_cnt, ts.seconds, ts.nanoseconds, tc_64);
    *ts_cnt = tc_64;

    return VTSS_RC_OK;
}

static vtss_rc jr2_packet_ns_to_ts_cnt(vtss_state_t  *vtss_state,
                                       u32           ns,
                                       u64           *ts_cnt)
{
    vtss_timestamp_t ts;
    u32       tc;
    u64       tc_64;

    while (ns >= VTSS_ONE_MIA) {
        /* skip sec part */
        ns -= VTSS_ONE_MIA;
        VTSS_I("decrement ns value (%d)", ns);
    }
    /* in Jaguar 2 the timeofday is sampled 2 times pr sec */
    _vtss_ts_domain_timeofday_get(NULL, 0, &ts, &tc_64);
    tc = tc_64 >> 16;       /* The tc_64 returned by _vtss_ts_domain_timeofday_get() is in 16 bit fractions of nanoseconds */
    if (ts.nanoseconds < ns) { // ns has not wrapped
        if ((ts.nanoseconds <= VTSS_ONE_MIA/2 && ns <= (VTSS_ONE_MIA/4)*3) || (ts.nanoseconds > VTSS_ONE_MIA/2)) {
            tc += (ns - ts.nanoseconds) / VTSS_HW_TIME_NSEC_PR_CNT;
        } else {
            tc -= (VTSS_ONE_MIA + ts.nanoseconds - ns) / VTSS_HW_TIME_NSEC_PR_CNT;
        }
    } else {
        if (ts.nanoseconds > VTSS_ONE_MIA/2 && ns <= VTSS_ONE_MIA/4) {
            tc += (VTSS_ONE_MIA + ns - ts.nanoseconds) / VTSS_HW_TIME_NSEC_PR_CNT;
        } else {
            tc -= (ts.nanoseconds - ns) / VTSS_HW_TIME_NSEC_PR_CNT;
        }
    }
    tc_64 = (u64)tc << 16;  /* Must return in 16 bit fractions of nanoseconds */

    VTSS_I("ns. %u, ts.sec %u, ts.ns %u, tc %" PRIu64 "", ns, ts.seconds, ts.nanoseconds, tc_64);
    *ts_cnt = tc_64;

    return VTSS_RC_OK;
}

static void jr2_packet_ts_cnt_sub(u32 *r, u32 x, u32 y)
{
    *r = x-y;
    if (x < y) {*r += VTSS_HW_TIME_WRAP_LIMIT;} /* time counter has wrapped */
}

#if defined(VTSS_OPT_PHY_TIMESTAMP)
static u32 jr2_packet_unpack32(const u8 *buf)
{
    return (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + buf[3];
}
#endif

static vtss_rc jr2_ptp_get_timestamp(vtss_state_t                    *vtss_state,
                                     const u8                        *const frm,
                                     const vtss_packet_rx_info_t     *const rx_info,
                                     vtss_packet_ptp_message_type_t  message_type,
                                     vtss_packet_timestamp_props_t   ts_props,
                                     u64                             *rxTime,
                                     BOOL                            *timestamp_ok)
{
    if (ts_props.ts_feature_is_PTS) {
#if defined(VTSS_OPT_PHY_TIMESTAMP)
        u32 packet_ns = jr2_packet_unpack32(frm);
        if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_30BIT) {
            /* convert to jaguar 32 bit NSF */
            VTSS_D("rxTime before %u", packet_ns);
            (void)jr2_packet_ns_to_ts_cnt(vtss_state, packet_ns, rxTime);
            VTSS_D("rxTime after %" PRIu64 "", *rxTime);
            *timestamp_ok = rx_info->hw_tstamp_decoded;
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_32BIT) {
            /* convert to jaguar 32 bit NSF */
            VTSS_D("rxTime before %u", packet_ns);
            (void)jr2_packet_phy_cnt_to_ts_cnt(vtss_state, packet_ns, rxTime);
            VTSS_D("rxTime after %" PRIu64 "", *rxTime);
            *timestamp_ok = rx_info->hw_tstamp_decoded;
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_44BIT) {
            VTSS_I("rxtime can not be retrieved from the packet supress warning for mode %d ", ts_props.phy_ts_mode);
        } else if (ts_props.phy_ts_mode == VTSS_PACKET_INTERNAL_TC_MODE_48BIT) {
            VTSS_I("rxtime can not be retrieved from the packet supress warning for mode %d ", ts_props.phy_ts_mode);
        } else {
            VTSS_I("PHY timestamp mode %d not supported", ts_props.phy_ts_mode);
        }
#else
        VTSS_I("PHY timestamp feature not supported");
#endif
    } else {
        u32 ns_32 = rx_info->hw_tstamp >> 16;   /* The HW time stamp is in 16 bit fractions of nanoseconds */
        *timestamp_ok = rx_info->hw_tstamp_decoded;
        /* if Sync message then subtract the p2p delay from rx time  */
        if (message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC) {
            jr2_packet_ts_cnt_sub(&ns_32, ns_32, (u32)(ts_props.delay_comp.delay_cnt >> 16));
        }
        /* link asymmetry compensation for Sync and PdelayResp events are not done in Jaguar2 on packets forwarded to the CPU */
        if ((message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC || message_type == VTSS_PACKET_PTP_MESSAGE_TYPE_P_DELAY_RESP) && ts_props.delay_comp.asymmetry_cnt != 0) {
            jr2_packet_ts_cnt_sub(&ns_32, ns_32, (u32)(ts_props.delay_comp.asymmetry_cnt >> 16));
        }
        *rxTime = (u64)ns_32 << 16;  /* Must return in 16 bit fractions of nanoseconds */
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_dma_conf_set(vtss_state_t *vtss_state, const vtss_packet_dma_conf_t *const new)
{
    u32                    qmask;
    int                    i, mode;
    vtss_packet_rx_queue_t qu;

    for (qmask = 0, i = 0; i < VTSS_QUEUE_END; i++) {
        if (new->dma_enable[i]) {
            qmask |= VTSS_BIT(i);
        }
    }

    VTSS_I("%sabling DMA, mask %08x", qmask ? "En" : "Dis", qmask);

    if (qmask == 0) {
        JR2_WRM_CLR(VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG,
                    VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_INJ_ENA(0) | VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_ENA(0));
        JR2_WRM(VTSS_ICPU_CFG_FDMA_FDMA_CH_CFG(VTSS_FDMA_CH_INJ_MANUAL_MODE), VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_INJ_GRP(0), VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_INJ_GRP);
        for (qu = 0; qu < vtss_state->packet.rx_queue_count; qu++) {
            JR2_WRM(VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_CPU_QU(qu)), VTSS_F_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL(VTSS_CHIP_PORT_CPU_0), VTSS_M_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL);
            vtss_state->packet.default_qu_redirect[qu] = VTSS_CHIP_PORT_CPU_0;
        }
    }

    mode = (qmask ? 2 : 1);       /* DMA / Register */
    i = VTSS_PACKET_TX_GRP_CNT - 1; /* Only setup higest group */
    JR2_WRM(VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(i), VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE(mode), VTSS_M_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE);
    i = VTSS_PACKET_RX_GRP_CNT - 1; /* Only setup higest group */
    JR2_WRM(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE(mode), VTSS_M_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE);

    if (qmask) {
        JR2_WRM_SET(VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG,
                    VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_INJ_ENA(1) | VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_ENA(1));
        JR2_WRM(VTSS_ICPU_CFG_FDMA_FDMA_CH_CFG(VTSS_FDMA_CH_INJ_MANUAL_MODE), VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_INJ_GRP(1), VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_INJ_GRP);
        for (qu = 0; qu < vtss_state->packet.rx_queue_count; qu++) {
            JR2_WRM(VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_CPU_QU(qu)), VTSS_F_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL(VTSS_CHIP_PORT_CPU_1), VTSS_M_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL);
            vtss_state->packet.default_qu_redirect[qu] = VTSS_CHIP_PORT_CPU_1;
        }
    }

    /* Update config */
    vtss_state->packet.dma_conf = *new;

    return VTSS_RC_OK;
}

static vtss_rc jr2_dma_offset(vtss_state_t *vtss_state, BOOL extract, u32 *const offset)
{
    if (extract) {
        *offset = VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_XTR(4096 - 1); /* Last word is status/control */
    } else {
        *offset = VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INJ(0);      /* First word is status/control */
    }
    return VTSS_RC_OK;
}

/* Setup L2CP Profile */
vtss_rc vtss_jr2_l2cp_conf_set(vtss_state_t *vtss_state, u32 profile, u32 l2cp, vtss_jr2_l2cp_conf_t *conf)
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
    JR2_WR(VTSS_ANA_CL_L2CP_TBL_L2CP_ENTRY_CFG(profile * 32 + l2cp),
           VTSS_F_ANA_CL_L2CP_TBL_L2CP_ENTRY_CFG_COSID_VAL(conf->cosid) |
           VTSS_F_ANA_CL_L2CP_TBL_L2CP_ENTRY_CFG_COSID_ENA(conf->cosid_enable ? 1 : 0) |
           VTSS_F_ANA_CL_L2CP_TBL_L2CP_ENTRY_CFG_CPU_FWD_CFG(reg) |
           VTSS_F_ANA_CL_L2CP_TBL_L2CP_ENTRY_CFG_CPU_L2CP_QU(conf->queue));
    return VTSS_RC_OK;
}

static vtss_rc jr2_rx_conf_set(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t      *conf = &vtss_state->packet.rx_conf;
    vtss_packet_rx_reg_t       *reg = &conf->reg;
    vtss_packet_rx_queue_map_t *map = &conf->map;
    vtss_packet_rx_port_conf_t *port_conf;
    vtss_port_no_t             port_no;
    u32                        port, i, j, cap_cfg, queue;
    BOOL                       cpu_only;
    vtss_jr2_l2cp_conf_t       l2cp_conf;

    // Each CPU queue gets reserved extraction buffer space. No sharing at port or buffer level
    for (queue = 0; queue < vtss_state->packet.rx_queue_count; queue++) {
        JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(2048 /* egress */ + VTSS_CHIP_PORT_CPU * VTSS_PRIOS + queue), conf->queue[queue].size / JR2_BUFFER_CELL_SZ);
    }

    JR2_WR(VTSS_QRES_RES_CTRL_RES_CFG(2048 /* egress */ + 512 /* per-port reservation */ + VTSS_CHIP_PORT_CPU), 0); // No extra shared space at port level

    // Setup Rx registrations that we only have per-switch API support for (not per-port)
    cap_cfg = VTSS_F_ANA_CL_PORT_CAPTURE_CFG_CPU_MLD_REDIR_ENA  (reg->mld_cpu_only)       |
              VTSS_F_ANA_CL_PORT_CAPTURE_CFG_CPU_IP4_MC_COPY_ENA(reg->ipmc_ctrl_cpu_copy) |
              VTSS_F_ANA_CL_PORT_CAPTURE_CFG_CPU_IGMP_REDIR_ENA (reg->igmp_cpu_only);

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
            /* Use L2CP profile 64-116 for ports */
            VTSS_RC(vtss_jr2_l2cp_conf_set(vtss_state, port + 64, i, &l2cp_conf));
        }
        JR2_WR(VTSS_ANA_CL_PORT_CAPTURE_CFG(port), cap_cfg);
    }

    // Setup queue mappings

    // IGMP and IPMC queues:
    JR2_WR(VTSS_ANA_CL_COMMON_CPU_PROTO_QU_CFG,
           VTSS_F_ANA_CL_COMMON_CPU_PROTO_QU_CFG_CPU_IP6_MC_CTRL_QU(map->ipmc_ctrl_queue) |
           VTSS_F_ANA_CL_COMMON_CPU_PROTO_QU_CFG_CPU_MLD_QU        (map->igmp_queue) |
           VTSS_F_ANA_CL_COMMON_CPU_PROTO_QU_CFG_CPU_IP4_MC_CTRL_QU(map->ipmc_ctrl_queue) |
           VTSS_F_ANA_CL_COMMON_CPU_PROTO_QU_CFG_CPU_IGMP_QU       (map->igmp_queue));

    // Learn queue:
    JR2_WRM(VTSS_ANA_L2_COMMON_LRN_CFG,
            VTSS_F_ANA_L2_COMMON_LRN_CFG_CPU_LRN_QU(map->learn_queue),
            VTSS_M_ANA_L2_COMMON_LRN_CFG_CPU_LRN_QU);

    // Enable forwarding to CPU of MAC-table SMAC hits, where the MAC-table entry has the CPU_COPY flag set.
    JR2_WRM(VTSS_ANA_L2_COMMON_LRN_CFG,
            VTSS_F_ANA_L2_COMMON_LRN_CFG_CPU_SMAC_COPY_ENA(1),
            VTSS_M_ANA_L2_COMMON_LRN_CFG_CPU_SMAC_COPY_ENA);

    // sFlow queue:
    if (map->sflow_queue != VTSS_PACKET_RX_QUEUE_NONE) {
        JR2_WRM(VTSS_ANA_AC_PS_COMMON_SFLOW_CFG,
                VTSS_F_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU(map->sflow_queue),
                VTSS_M_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU);
    }

#if defined(VTSS_FEATURE_LAYER3)
    // Configure L3 routing CPU queues
    JR2_WR(VTSS_ANA_L3_COMMON_CPU_QU_CFG,
           VTSS_F_ANA_L3_COMMON_CPU_QU_CFG_CPU_RLEG_QU            (map->l3_uc_queue)    |
           VTSS_F_ANA_L3_COMMON_CPU_QU_CFG_CPU_RLEG_IP_OPT_QU     (map->l3_other_queue) |
           VTSS_F_ANA_L3_COMMON_CPU_QU_CFG_CPU_RLEG_IP_HDR_FAIL_QU(map->l3_other_queue) |
           VTSS_F_ANA_L3_COMMON_CPU_QU_CFG_CPU_SIP_RPF_QU         (map->l3_other_queue) |
           VTSS_F_ANA_L3_COMMON_CPU_QU_CFG_CPU_IP_LEN_QU          (map->l3_other_queue) |
           VTSS_F_ANA_L3_COMMON_CPU_QU_CFG_CPU_MC_FAIL_QU         (map->l3_other_queue) |
           VTSS_F_ANA_L3_COMMON_CPU_QU_CFG_CPU_UC_FAIL_QU         (map->l3_uc_queue)    |
           VTSS_F_ANA_L3_COMMON_CPU_QU_CFG_CPU_IP_TTL_FAIL_QU     (map->l3_other_queue));
#endif /* VTSS_FEATURE_LAYER3 */

    // Configure Rx Queue #i to map to an Rx group.
    for (i = 0; i < vtss_state->packet.rx_queue_count; i++) {
        if (conf->grp_map[i]) {
            VTSS_E("Attempt to redirect queue %d - use vtss_dma_conf_set() instead", i);
        }
    }

    VTSS_RC(jr2_npi_mask_set(vtss_state));

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

static vtss_rc jr2_rx_frame_discard_grp(vtss_state_t *vtss_state, const vtss_packet_rx_grp_t xtr_grp)
{

    BOOL done = FALSE;

    while (!done) {
        u32 val;
        JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val);
        switch (val) {
        case XTR_ABORT:
        case XTR_PRUNED:
        case XTR_EOF_3:
        case XTR_EOF_2:
        case XTR_EOF_1:
        case XTR_EOF_0:
            JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val); /* Last data */
            done = TRUE;        /* Last 1-4 bytes */
            break;
        case XTR_ESCAPE:
            JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(xtr_grp), &val); /* Escaped data */
            break;
        case XTR_NOT_READY:
        default:
            break;
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_rx_frame_discard(vtss_state_t *vtss_state, const vtss_packet_rx_queue_t queue_no)
{
    vtss_packet_rx_grp_t xtr_grp = vtss_state->packet.rx_conf.grp_map[queue_no];
    return jr2_rx_frame_discard_grp(vtss_state, xtr_grp);
}

/**
 * Return values:
 *  0 = Data OK.
 *  1 = EOF reached. Data OK. bytes_valid indicates the number of valid bytes in last word ([1; 4]).
 *  2 = Error. No data from queue system.
 */
static int jr2_rx_frame_word(vtss_state_t *vtss_state, vtss_packet_rx_grp_t grp, BOOL first_word, u32 *rval, u32 *bytes_valid)
{
    u32 val;

    JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), &val);

    if (val == XTR_NOT_READY) {
        /** XTR_NOT_READY means two different things depending on whether this is the first
         * word read of a frame or after at least one word has been read.
         * When the first word, the group is empty, and we return an error.
         * Otherwise we have to wait for the FIFO to have received some more data. */
        if (first_word) {
            return 2; /* Error */
        }
        do {
            JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), &val);
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
        JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), &val);
        if (val == XTR_ESCAPE) {
            JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), rval);
        } else {
            *rval = val;
        }
        return 1; /* EOF */
    case XTR_ESCAPE:
        JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_RD(grp), rval);
        *bytes_valid = 4;
        return 0;
    default:
        *rval = val;
        *bytes_valid = 4;
        return 0;
    }
}

static vtss_rc jr2_rx_frame_get_internal(vtss_state_t           *vtss_state,
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

    /* Read IFH. It consists of 7 words */
    for (i = 0; i < JR2_IFH_WORDS; i++) {
        if (jr2_rx_frame_word(vtss_state, grp, TRUE, &val, &bytes_valid) != 0) {
            /* We accept neither EOF nor ERROR when reading the IFH */
            return VTSS_RC_ERROR;
        }
        ifh[i] = val;
    }

    buf = frame;

    /* Read the rest of the frame */
    while (!done && buf_len >= 4) {
        result = jr2_rx_frame_word(vtss_state, grp, FALSE, &val, &bytes_valid);
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
        (void)jr2_rx_frame_discard_grp(vtss_state, grp);
        return VTSS_RC_ERROR;
    }

    if (bytes_got < 60) {
        VTSS_E("short frame, %u bytes read", bytes_got);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}


static vtss_rc jr2_rx_frame_get(vtss_state_t                 *vtss_state,
                                const vtss_packet_rx_queue_t queue_no,
                                vtss_packet_rx_header_t      *const header,
                                u8                           *const frame,
                                const u32                    length)
{
    vtss_rc              rc;
    vtss_packet_rx_grp_t grp = vtss_state->packet.rx_conf.grp_map[queue_no];
    u32                  val, port, port_1, port_2;
    u32                  ifh[JR2_IFH_WORDS]; /* The internal frame header of Jaguar2 is 28 bytes long. */
    vtss_port_no_t       port_no;
    BOOL                 found = FALSE;
    u16                  ethtype;
    int                  i;

    /* Check if data is ready for grp */
    JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT, &val);
    if (!(val & VTSS_F_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT(VTSS_BIT(grp)))) {
        return VTSS_RC_INCOMPLETE;
    }

    if ((rc = jr2_rx_frame_get_internal(vtss_state, grp, ifh, frame, length, &header->length)) != VTSS_RC_OK) {
        return rc;
    }
    header->length -= 4; // According to specification, vtss_packet_rx_header_t::length excludes the FCS, but jr2_rx_frame_get_internal() includes it.

    /* Decoding assumes host order IFH */
    for (i = 0; i < JR2_IFH_WORDS; i++) {
        ifh[i] = VTSS_OS_NTOHL(ifh[i]);
    }

    /* Note: there is no length reported in the IFH in Jaguar2 */

    /* Note - VLAN tags are *not* stripped on ingress */
    /* Internal Frame Header field (0~223) bits which includes VStaX header field */

    /* VStaX header field (48~127) bits -> (0~79) relatively */
    /* --> TAG field (79~60) -> (31~12) relatively */
    header->tag.vid     = VTSS_EXTRACT_BITFIELD(ifh[4], (16 + 48 - 64), 12);
    header->tag.cfi     = VTSS_EXTRACT_BITFIELD(ifh[4], (28 + 48 - 64),  1);
    header->tag.tagprio = VTSS_EXTRACT_BITFIELD(ifh[4], (29 + 48 - 64),  3);
    /* --> General field (101~92) -> (53~44) relatively */
    header->learn      = (VTSS_EXTRACT_BITFIELD(ifh[4], (47 + 48 - 64),  1) ? 1 : 0);

    /* MISC field (25~10) */
    /* queue_mask (17~10) */
    header->queue_mask  = VTSS_EXTRACT_BITFIELD(ifh[6], 10,  8);

    /* Map from chip port to API port */
    /* Physical source port number (SRC_PORT) 32~27, 6 bits in FWD field in Jaguar2 */
    port_1 = VTSS_EXTRACT_BITFIELD(ifh[5], 32 - 32, 1);
    port_2 = VTSS_EXTRACT_BITFIELD(ifh[6], 27, 5);

    port = (port_1 << 5) | port_2;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (VTSS_CHIP_PORT(port_no) == port) {
            header->port_no = port_no;
            found = TRUE;
            break;
        }
    }
    if (!found) {
        VTSS_E("Unknown chip port: %u", port);
        return VTSS_RC_ERROR;
    } else {
        VTSS_D("chip port: %u", port);
    }

    ethtype = (frame[12] << 8) + frame[13];
    header->arrived_tagged = (ethtype == VTSS_ETYPE_TAG_C || ethtype == VTSS_ETYPE_TAG_S); /* Emulated */

    return VTSS_RC_OK;
}

static vtss_rc jr2_rx_frame_get_raw(vtss_state_t         *vtss_state,
                                    u8                  *const data,
                                    const u32           buflen,
                                    u32                 *const ifhlen,
                                    u32                 *const frmlen)
{
    vtss_rc rc = VTSS_RC_INCOMPLETE;
    u32     val;

    /* Check if data is ready for grp */
    JR2_RD(VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT, &val);
    if (val) {
        u32 ifh[JR2_IFH_WORDS];
        u32 length;
        vtss_packet_rx_grp_t grp = VTSS_OS_CTZ(val);

        /* Get frame, separate IFH and frame data */
        if ((rc = jr2_rx_frame_get_internal(vtss_state, grp, ifh, data + sizeof(ifh), buflen - sizeof(ifh), &length)) != VTSS_RC_OK) {
            return rc;
        }

        /* IFH is done separately because of alignment needs */
        memcpy(data, ifh, sizeof(ifh));
        *ifhlen = sizeof(ifh);
        *frmlen = length;
        rc = VTSS_RC_OK;
    }
    return rc;
}


static vtss_rc jr2_vstax_header2frame(const vtss_state_t            *const state,
                                      const vtss_port_no_t          port_no,
                                      const vtss_vstax_tx_header_t  *const vstax,
                                      u8                            *const frame)
{
    u32 chip_port = (vstax->port_no == VTSS_PORT_NO_NONE ? vstax->chip_port : VTSS_CHIP_PORT_FROM_STATE(state, vstax->port_no));
    u32 val;
    u32 vstax_hi = 0;
    u64 vstax_lo = 0;

    /* EtherType */
    vstax_hi |= VTSS_ENCODE_BITFIELD(VTSS_ETYPE_VTSS, 16, 16);

    /* Valid */
    vstax_hi |= VTSS_ENCODE_BITFIELD(1,               15,  1);

    /* Ingress Drop Mode == 1 => No head-of-line blocking. Not used on super-prio injection */
    vstax_lo |= VTSS_ENCODE_BITFIELD64(1, 55, 1);

    /* DP */
    if (vstax->dp) {
        vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->dp, 60, 2);
    }

    /* QoS */
    if (vstax->prio == VTSS_PRIO_SUPER) {
        vstax_lo |= VTSS_ENCODE_BITFIELD64(TRUE, 59, 1);
    } else {
        vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->prio, 56, 3);
    }

    /* TTL */
    if (vstax->ttl == VTSS_VSTAX_TTL_PORT) {
        /* TBD_STACK */
        val = 0;
    } else {
        val = vstax->ttl;
    }
    vstax_lo |= VTSS_ENCODE_BITFIELD64(val, 48, 5);

    /* LRN skip */
    vstax_lo |= VTSS_ENCODE_BITFIELD64(TRUE, 47, 1);

    /* Fwd mode and associated fields*/
    vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->fwd_mode, 44, 3);
    switch (vstax->fwd_mode) {
    case VTSS_VSTAX_FWD_MODE_LOOKUP:
        break;
    case VTSS_VSTAX_FWD_MODE_UPSID_PORT:
        /* dst_port_type=0 */
        vstax_lo |= VTSS_ENCODE_BITFIELD64((u32)vstax->upsid - VTSS_VSTAX_UPSID_START, 37, 5);
        vstax_lo |= VTSS_ENCODE_BITFIELD64(chip_port, 32, 5);
        break;
    case VTSS_VSTAX_FWD_MODE_CPU_UPSID:
        vstax_lo |= VTSS_ENCODE_BITFIELD64((u32)vstax->upsid - VTSS_VSTAX_UPSID_START, 37, 5);
        vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->queue_no - VTSS_PACKET_RX_QUEUE_START, 32, 4);
        break;
    case VTSS_VSTAX_FWD_MODE_CPU_ALL:
        vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->keep_ttl, 41, 1);
        vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->queue_no - VTSS_PACKET_RX_QUEUE_START, 32, 4);
        break;
    default:
        VTSS_E("Illegal fwd mode: %d", vstax->fwd_mode);
    }

    /* uprio */
    vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->tci.tagprio, 29, 3);

    /* cfi */
    vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->tci.cfi, 28, 1);

    /* VID */
    vstax_lo |= VTSS_ENCODE_BITFIELD64(vstax->tci.vid, 16, 12);

    /* Source */
    {
        /* src_addr_mode (bit #10) == 0, a.k.a. src_ind_port */
        /* Pick the src_port_type (bit #11) == 1, a.k.a. port_type_intpn. */
        vstax_lo |= VTSS_ENCODE_BITFIELD64(TRUE, 11, 1);
        vstax_lo |= VTSS_ENCODE_BITFIELD64(0, 5, 5); /* Source chip_no == 0, i.e. ourselves. */
        vstax_lo |= VTSS_ENCODE_BITFIELD64(0xf, 0, 5); /* intpn_dlookup */
    }

    frame[ 0] = vstax_hi >> 24;
    frame[ 1] = vstax_hi >> 16;
    frame[ 2] = vstax_hi >>  8;
    frame[ 3] = vstax_hi >>  0;
    frame[ 4] = vstax_lo >> 56;
    frame[ 5] = vstax_lo >> 48;
    frame[ 6] = vstax_lo >> 40;
    frame[ 7] = vstax_lo >> 32;
    frame[ 8] = vstax_lo >> 24;
    frame[ 9] = vstax_lo >> 16;
    frame[10] = vstax_lo >>  8;
    frame[11] = vstax_lo >>  0;

    return VTSS_RC_OK;
}

static vtss_rc jr2_vstax_frame2header(const vtss_state_t      *const state,
                                      const u8                *const frame,
                                      vtss_vstax_rx_header_t  *const vstax)
{
    u32 vstax_hi = 0;
    const u8 *ifh = frame;

    /* 4 bytes to vstax_hi */
    vstax_hi <<= 8, vstax_hi += *ifh++;
    vstax_hi <<= 8, vstax_hi += *ifh++;
    vstax_hi <<= 8, vstax_hi += *ifh++;
    vstax_hi <<= 8, vstax_hi += *ifh++;

    memset(vstax, 0, sizeof(*vstax));

    /* Valid IFH */
    vstax->valid =
        (VTSS_EXTRACT_BITFIELD(vstax_hi, 16, 16) == VTSS_ETYPE_VTSS) &&
        VTSS_EXTRACT_BITFIELD(vstax_hi, 15, 1);

    /* Decode rest if OK */
    if (vstax->valid) {
        u64 vstax_lo = 0;

        vstax->isdx = VTSS_EXTRACT_BITFIELD(vstax_hi, 0, 12);

        /* 8 bytes to vstax_lo */
        vstax_lo <<= 8, vstax_lo += *ifh++;
        vstax_lo <<= 8, vstax_lo += *ifh++;
        vstax_lo <<= 8, vstax_lo += *ifh++;
        vstax_lo <<= 8, vstax_lo += *ifh++;
        vstax_lo <<= 8, vstax_lo += *ifh++;
        vstax_lo <<= 8, vstax_lo += *ifh++;
        vstax_lo <<= 8, vstax_lo += *ifh++;
        vstax_lo <<= 8, vstax_lo += *ifh++;

        vstax->sp = VTSS_EXTRACT_BITFIELD64(vstax_lo, 59, 1);

        if (VTSS_EXTRACT_BITFIELD64(vstax_lo, 10, 1)) {
            /* GLAG */
            vstax->port_no = VTSS_PORT_NO_NONE;
            vstax->glag_no = VTSS_EXTRACT_BITFIELD64(vstax_lo, 0, 5);
        } else {
            /* Port */
            vstax->port_no = vtss_jr2_vtss_pgid(state, VTSS_EXTRACT_BITFIELD64(vstax_lo, 0,  5));
            vstax->upsid   = VTSS_EXTRACT_BITFIELD64(vstax_lo, 5,  5);
            vstax->glag_no = VTSS_GLAG_NO_NONE;
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_rx_hdr_decode(const vtss_state_t          *const state,
                                 const vtss_packet_rx_meta_t *const meta,
                                 const u8                           xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                 vtss_packet_rx_info_t       *const info)
{
    u16                 vstax_hi;
    u32                 tstamp;
    u64                 dst, vstax_lo, fwd;
    BOOL                sflow_marked;
    vtss_vid_t          vid;
    vtss_phys_port_no_t chip_port;

    VTSS_DG(VTSS_TRACE_GROUP_PACKET, "IFH (28 bytes) + bit of packet:");
    VTSS_DG_HEX(VTSS_TRACE_GROUP_PACKET, &xtr_hdr[0], 96);
    tstamp    = ((u32)xtr_hdr[ 0] << 24) | ((u32)xtr_hdr[ 1] << 16) | ((u32)xtr_hdr[ 2] <<  8) | ((u32)xtr_hdr[ 3] <<  0);
    dst       = ((u64)xtr_hdr[ 4] << 56) | ((u64)xtr_hdr[ 5] << 48) | ((u64)xtr_hdr[ 6] << 40) | ((u64)xtr_hdr[ 7] << 32);
    dst      |= ((u64)xtr_hdr[ 8] << 24) | ((u64)xtr_hdr[ 9] << 16) | ((u64)xtr_hdr[10] <<  8) | ((u64)xtr_hdr[11] <<  0);
    vstax_hi  =                                                       ((u16)xtr_hdr[12] <<  8) | ((u16)xtr_hdr[13] <<  0);
    vstax_lo  = ((u64)xtr_hdr[14] << 56) | ((u64)xtr_hdr[15] << 48) | ((u64)xtr_hdr[16] << 40) | ((u64)xtr_hdr[17] << 32);
    vstax_lo |= ((u64)xtr_hdr[18] << 24) | ((u64)xtr_hdr[19] << 16) | ((u64)xtr_hdr[20] <<  8) | ((u64)xtr_hdr[21] <<  0);
    fwd       =                                                       ((u64)xtr_hdr[22] << 40) | ((u64)xtr_hdr[23] << 32);
    fwd      |= ((u64)xtr_hdr[24] << 24) | ((u64)xtr_hdr[25] << 16) | ((u64)xtr_hdr[26] <<  8) | ((u64)xtr_hdr[27] <<  0);

    // The VStaX header's MSbit must be 1.
    if (VTSS_EXTRACT_BITFIELD(vstax_hi, 15, 1) != 1) {
        VTSS_EG(VTSS_TRACE_GROUP_PACKET, "Invalid Rx header signature");
        return VTSS_RC_ERROR;
    }

    memset(info, 0, sizeof(*info));

    info->sw_tstamp         = meta->sw_tstamp;
    info->hw_tstamp         = (u64)tstamp<<16;
    info->length            = meta->length;
    info->hw_tstamp_decoded = TRUE;

    chip_port = VTSS_EXTRACT_BITFIELD64(fwd, 27, 6);
    info->port_no = vtss_cmn_chip_to_logical_port(state, meta->chip_no, chip_port);

    if (chip_port == VTSS_CHIP_PORT_CPU_0 || chip_port == VTSS_CHIP_PORT_CPU_1) {
        VTSS_IG(VTSS_TRACE_GROUP_PACKET, "This frame is transmitted by the CPU itself and should be discarded.");
    }

//     VTSS_IG(VTSS_TRACE_GROUP_PACKET, "Received on xtr_qu = %u, chip_no = %d, chip_port = %u, port_no = %u", meta->xtr_qu, meta->chip_no, chip_port, info->port_no);

    info->glag_no = VTSS_GLAG_NO_NONE;

    if (VTSS_EXTRACT_BITFIELD64(fwd, 43, 1)) {
        // Received with VStaX header. Decode it.
        u8 vstax_hdr_bin[VTSS_VSTAX_HDR_SIZE];

        vstax_hdr_bin[0] = (VTSS_ETYPE_VTSS >> 8) & 0xFF;
        vstax_hdr_bin[1] = (VTSS_ETYPE_VTSS >> 0) & 0xFF;
        memcpy(&vstax_hdr_bin[2], &xtr_hdr[8], VTSS_VSTAX_HDR_SIZE - 2);
        (void)jr2_vstax_frame2header(state, vstax_hdr_bin, &info->vstax);
        info->glag_no = info->vstax.glag_no;
    }

    sflow_marked = VTSS_EXTRACT_BITFIELD64(fwd, 37, 1);
    info->xtr_qu_mask = VTSS_EXTRACT_BITFIELD64(fwd, 10, 8);

    // Bugzilla#17780. Due to a chip-bug, sFlow frames will not give rise to any bits set in
    // the CPU extraction mask, so let's do it for it.
    if (info->xtr_qu_mask == 0 && sflow_marked && state->packet.rx_conf.map.sflow_queue != VTSS_PACKET_RX_QUEUE_NONE) {
        info->xtr_qu_mask = VTSS_BIT(state->packet.rx_conf.map.sflow_queue);
    }

    if (sflow_marked) {
        // This is only reliable if ANA_AC:PS_COMMON:PS_COMMON_CFG.SFLOW_SMPL_ID_IN_STAMP_ENA is set to 1.
        u32 sflow_id        = (meta->fcs >> 26) & 0x3F; // Indicates physical port number.
        info->sflow_type    = chip_port == sflow_id ? VTSS_SFLOW_TYPE_RX : VTSS_SFLOW_TYPE_TX;
        info->sflow_port_no = vtss_cmn_chip_to_logical_port(state, meta->chip_no, sflow_id);
    }

    // FIXME: Super-prio

    if (VTSS_EXTRACT_BITFIELD64(dst, 19, 16) & JR2_IFH_CL_RSLT_ACL_HIT) {
        // ACL hit signalled in CL_RSLT
        info->acl_hit = 1;
    }

    info->cosid      = VTSS_EXTRACT_BITFIELD(  vstax_hi, 12,  3);
    info->vstax.isdx = VTSS_EXTRACT_BITFIELD(  vstax_hi,  0, 12);
    info->dp         = VTSS_EXTRACT_BITFIELD64(vstax_lo, 60,  2);
    info->cos        = VTSS_EXTRACT_BITFIELD64(vstax_lo, 56,  3);
    info->tag.pcp    = VTSS_EXTRACT_BITFIELD64(vstax_lo, 29,  3);
    info->tag.dei    = VTSS_EXTRACT_BITFIELD64(vstax_lo, 28,  1);
    info->tag.vid    = VTSS_EXTRACT_BITFIELD64(vstax_lo, 16, 12);

    if (VTSS_EXTRACT_BITFIELD64(dst, 45, 1)) {
        info->vsi = VTSS_EXTRACT_BITFIELD64(dst, 46, 12);
        if ((vid = state->packet.vsi2vid[info->vsi]) != VTSS_VID_NULL) {
            // Map VSI to classified VID
            info->tag.vid = vid;
        }
    } else {
        info->vsi = VTSS_VSI_NONE;
    }

    VTSS_RC(vtss_cmn_packet_hints_update(state, VTSS_TRACE_GROUP_PACKET, meta->etype, info));

    return VTSS_RC_OK;
}

/*****************************************************************************/
// jr2_ptp_action_to_ifh()
/*****************************************************************************/
static vtss_rc jr2_ptp_action_to_ifh(vtss_packet_ptp_action_t ptp_action, BOOL afi, u32 *result)
{
    vtss_rc rc = VTSS_RC_OK;

    switch (ptp_action) {
    case VTSS_PACKET_PTP_ACTION_ONE_STEP:
        *result = 1;
        break;

    case VTSS_PACKET_PTP_ACTION_AFI_NONE:
        if (afi) {
            *result = 0x018;  // AFI does not work unless REW_CMD[3..0] != 0, so when we want to run AFI but no PTP action, we set bit 3 (add ingress delay) which makes no harm as we don't configure any ingress delay on the CPU port
        } else {
            *result = 0;
        }
        break;

    case VTSS_PACKET_PTP_ACTION_TWO_STEP:
        *result = 2;
        break;

    case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP:
    case VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ:
        *result = 3;
        if (afi || (ptp_action == VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ)) {
            *result |= 0x10;    /* Bit 4 is enable of sequence number increment in rewriter */
        }
        break;

    default:
        VTSS_E("Invalid PTP action (%d)", ptp_action);
        rc = VTSS_RC_ERROR;
        break;
    }

    return rc;
}

/*****************************************************************************/
// jr2_tx_hdr_encode()
/*****************************************************************************/
static vtss_rc jr2_tx_hdr_encode(vtss_state_t                *const state,
                                 const vtss_packet_tx_info_t *const info,
                                 u8                          *const bin_hdr,
                                 u32                         *const bin_hdr_len)
{
    u64                 dst, vstax_lo, fwd, ts;
    u16                 vstax_hi;
    BOOL                contains_stack_hdr;
    vtss_prio_t         cos;
    vtss_phys_port_no_t chip_port;
    vtss_vlan_entry_t   *vlan = NULL;

    if (bin_hdr == NULL) {
        // Caller wants us to return the number of bytes required to fill
        // in #bin_hdr. We need 28 bytes for the IFH.
        *bin_hdr_len = JR2_IFH_BYTES;
        return VTSS_RC_OK;
    } else if (*bin_hdr_len < JR2_IFH_BYTES) {
        return VTSS_RC_ERROR;
    }

    *bin_hdr_len = JR2_IFH_BYTES;

#if defined(VTSS_FEATURE_VSTAX)
    contains_stack_hdr = info->tx_vstax_hdr != VTSS_PACKET_TX_VSTAX_NONE;
#else
    contains_stack_hdr = FALSE;
#endif

    dst      = 0;
    vstax_hi = VTSS_ENCODE_BITFIELD  (1,                     15, 1); // MSBit must be 1
    vstax_lo = VTSS_ENCODE_BITFIELD64(1,                     55, 1); // ingr_drop_mode = 1 => don't make head-of-line blocking
    fwd      = VTSS_ENCODE_BITFIELD64(1,                     42, 1); // Enforce update of FCS.
    fwd     |= VTSS_ENCODE_BITFIELD64(VTSS_CHIP_PORT_CPU_0,  27, 6); // SRC_PORT = CPU

#if defined(VTSS_FEATURE_AFI_SWC)
    if (info->afi_id != VTSS_AFI_ID_NONE) {
        // The CPU wants this frame to go into the AFI packet memory for repetitive injection.
        fwd |= VTSS_ENCODE_BITFIELD64(1, 47, 1); // AFI_INJ = 1
    }
#endif

    // FIXME: Super-priority injection
    cos = info->cos >= 8 ? 7 : info->cos;

    if (!info->switch_frm) {
        // Most of the stuff that needs to be filled in is when we're not switching the frame.
        // First figure out which ports the caller wants to inject to.
        u64            chip_port_mask;
        vtss_chip_no_t chip_no;
        vtss_port_no_t stack_port_no;
        u32            port_cnt;
        vtss_port_no_t port_no; /* Only valid if port_cnt == 1 */
        BOOL           rewrite;

        VTSS_RC(vtss_cmn_logical_to_chip_port_mask(state, info->dst_port_mask, &chip_port_mask, &chip_no, &stack_port_no, &port_cnt, &port_no));

        // Get the frame classified to info->tag.vid and rewritten accordingly if requested to.
        rewrite = info->tag.tpid == 0 && info->tag.vid != VTSS_VID_NULL;

#ifdef VTSS_FEATURE_MIRROR_CPU
        // Add mirror port if enabled.
        if (state->l2.mirror_conf.port_no != VTSS_PORT_NO_NONE && state->l2.mirror_cpu_ingress) {
            fwd |= VTSS_ENCODE_BITFIELD64(JR2_MIRROR_PROBE_RX + 1 /* 1-based in this field */, 33, 2);
        }
#endif

        if (info->ptp_action == VTSS_PACKET_PTP_ACTION_NONE &&
            info->oam_type   == VTSS_PACKET_OAM_TYPE_NONE   &&
            info->vsi        == VTSS_VSI_NONE) {
            // Normal multi-port-injection without rewriting, unless asked to rewrite.

            dst |= VTSS_ENCODE_BITFIELD64(chip_port_mask,  0, 53); // Dst ports when DST_MODE == INJECT
            fwd |= VTSS_ENCODE_BITFIELD64(16,             18,  5); // Bypass analyzer (inject into ANA_DONE pipeline point)
            fwd |= VTSS_ENCODE_BITFIELD64(1,              23,  3); // MISC.PIPELINE_ACT = INJ
            fwd |= VTSS_ENCODE_BITFIELD64(3,              38,  3); // DST_MODE = INJECT
        } else {
            // Either injecting with a PTP action, OAM, or to a VSI (Virtual Switching Instance).
            // This means that we can't inject with a user-specified stack header and only
            // on one port at a time.
            if (contains_stack_hdr) {
                VTSS_E("Cannot inject with a stack header when DST_MODE == ENCAP");
                return VTSS_RC_ERROR;
            }

            if (port_cnt != 1) {
                VTSS_E("Can only inject to a single port when DST_MODE == ENCAP");
                return VTSS_RC_ERROR;
            }

            chip_port = VTSS_CHIP_PORT_FROM_STATE(state, port_no);

            fwd      |= VTSS_ENCODE_BITFIELD64(0,         38, 3); // DST_MODE = ENCAP (with only one port).
            fwd      |= VTSS_ENCODE_BITFIELD64(chip_port, 10, 8); // MISC.INJECT_PORT when DST_MODE == ENCAP
            fwd      |= VTSS_ENCODE_BITFIELD64(1,         23, 3); // MISC.PIPELINE_ACT = INJ

            rewrite = TRUE;

            if (info->ptp_action != VTSS_PACKET_PTP_ACTION_NONE) {
                u32 rew_cmd;

                if (info->pdu_offset == 0 || (info->pdu_offset % 2) != 0) {
                    VTSS_E("Invalid pdu_offset %u. It must be an even number greater than 0", info->pdu_offset);
                    return VTSS_RC_ERROR;
                }

                VTSS_DG(VTSS_TRACE_GROUP_PACKET, "Injecting with PTP action: %d, pdu_offset %u", info->ptp_action, info->pdu_offset);
                VTSS_RC(jr2_ptp_action_to_ifh(info->ptp_action, info->afi_id != VTSS_AFI_ID_NONE, &rew_cmd));
                VTSS_DG(VTSS_TRACE_GROUP_PACKET, "Injecting rew_cmd: 0x%x, ptp_timestamp %" PRIu64 "", rew_cmd, info->ptp_timestamp);

                vstax_lo |= VTSS_ENCODE_BITFIELD64(rew_cmd,              32, 8); // REW_CMD (when FWD_MODE == FWD_LLOOKUP, which is what this is).
                dst      |= VTSS_ENCODE_BITFIELD64(info->pdu_offset / 2, 38, 6); // PDU_W16_OFFSET = 7 when DST_MODE == ENCAP
                dst      |= VTSS_ENCODE_BITFIELD64(3,                    35, 3); // PDU_TYPE = PTP when DST_MODE == ENCAP
                fwd      |= VTSS_ENCODE_BITFIELD64(24,                   18, 5); // MISC.PIPELINE_PT = REW_PORT_VOE
            } else if (info->oam_type != VTSS_PACKET_OAM_TYPE_NONE) {
                // OAM injection
                VTSS_DG(VTSS_TRACE_GROUP_PACKET, "OAM Injecting");
                vstax_lo |= VTSS_ENCODE_BITFIELD64(1, 59, 1);                    // Super Priority
                dst      |= VTSS_ENCODE_BITFIELD64(info->pdu_offset / 2, 38, 6); // PDU_W16_OFFSET = 7 when DST_MODE == ENCAP
                if (info->oam_type == VTSS_PACKET_OAM_TYPE_MPLS_TP_1) {
                    VTSS_DG(VTSS_TRACE_GROUP_PACKET, "OAM Injecting MPLS1: TC,S,TTL %u,%u,%u", cos, info->oam_mpls_sbit, info->oam_mpls_ttl);
                    dst  |= VTSS_ENCODE_BITFIELD64(1,                    35, 3); // PDU_TYPE = OAM_Y1731
                    dst  |= VTSS_ENCODE_BITFIELD64(info->oam_mpls_ttl,   11, 8); // MPLS_TTL
                    dst  |= VTSS_ENCODE_BITFIELD64(info->oam_mpls_sbit,  10, 1); // MPLS_SBIT
                    dst  |= VTSS_ENCODE_BITFIELD64(cos,                   7, 3); // MPLS_TC
                    dst  |= VTSS_ENCODE_BITFIELD64(1,                     5, 2); // TYPE_AFTER_POP=CW
                } else if (info->oam_type == VTSS_PACKET_OAM_TYPE_MPLS_TP_2) {
                    VTSS_DG(VTSS_TRACE_GROUP_PACKET, "OAM Injecting MPLS2: TC,S,TTL %u,%u,%u", cos, info->oam_mpls_sbit, info->oam_mpls_ttl);
                    dst  |= VTSS_ENCODE_BITFIELD64(2,                    35, 3); // PDU_TYPE = OAM_MPLS_TP
                    dst  |= VTSS_ENCODE_BITFIELD64(info->oam_mpls_ttl,   11, 8); // MPLS_TTL
                    dst  |= VTSS_ENCODE_BITFIELD64(info->oam_mpls_sbit,  10, 1); // MPLS_SBIT
                    dst  |= VTSS_ENCODE_BITFIELD64(cos,                   7, 3); // MPLS_TC
                    dst  |= VTSS_ENCODE_BITFIELD64(1,                     5, 2); // TYPE_AFTER_POP=CW
                } else {
                    dst  |= VTSS_ENCODE_BITFIELD64(1,                    35, 3); // PDU_TYPE = OAM_Y1731
                    if (info->tag.vid < VTSS_VIDS) {
                        vlan = &state->l2.vlan_table[info->tag.vid];
                        if (vlan->vsi_enable) { /* VSI is enabled for this VLAN */
                            dst |= VTSS_ENCODE_BITFIELD64(1,         45,  1);              // GEN_IDX_MODE = 1
                            dst |= VTSS_ENCODE_BITFIELD64(vlan->vsi->vsi, 46, 12);         // GEN_IDX = VSI
                        }
                    }
                }
                fwd      |= VTSS_ENCODE_BITFIELD64(info->pipeline_pt,    18, 5); // MISC.PIPELINE_PT = pipeline_pt_val
                if (((info->pipeline_pt == VTSS_PACKET_PIPELINE_PT_REW_IN_VOE) || (info->pipeline_pt == VTSS_PACKET_PIPELINE_PT_REW_OU_VOE)) &&
                    ((info->oam_type == VTSS_PACKET_OAM_TYPE_DMM) || (info->oam_type == VTSS_PACKET_OAM_TYPE_1DM))) {    // DM injection into a service has an added dummy tag that must be popped
                    fwd  |= VTSS_ENCODE_BITFIELD64(1, 8, 2);                        // POP one tag
                }

                if ((info->pipeline_pt != VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE) || (info->oam_type == VTSS_PACKET_OAM_TYPE_LCK)) {  /* Injecting LCK is done in the client flow. This must hit the ES0 */
                    rewrite = TRUE;
                } else {
                    rewrite = FALSE;
                }
            } else {
                // VSI injection.
                dst |= VTSS_ENCODE_BITFIELD64(1,         45,  1); // GEN_IDX_MODE = 1
                dst |= VTSS_ENCODE_BITFIELD64(info->vsi, 46, 12); // GEN_IDX = VSI
                if (!info->isdx_dont_use) {
                    fwd |= VTSS_ENCODE_BITFIELD64(1,         45,  1); // ESO_ISDX_KEY_ENA = 1
                }
                fwd |= VTSS_ENCODE_BITFIELD64(17,        18,  5); // MISC.PIPELINE_PT = REW_IN_MIP
            }
        }

        fwd |= VTSS_ENCODE_BITFIELD64(!rewrite, 26, 1); // FWD.DO_NOT_REW = 0 => do rewrite, 1 => do not rewrite

        if (contains_stack_hdr) {
#if defined(VTSS_FEATURE_VSTAX)
            // Stack header is already filled in by the user. Make sure the selected port is a stack port.
            if (stack_port_no == VTSS_PORT_NO_NONE) {
                VTSS_E("Injecting with stack header to non-stack port");
                return VTSS_RC_ERROR;
            }

            if (info->tx_vstax_hdr == VTSS_PACKET_TX_VSTAX_SYM) {
                // The following function also inserts the EtherType, hence the "-2" from the correct VStaX header position within the IFH.
                VTSS_RC(jr2_vstax_header2frame(state, stack_port_no, &info->vstax.sym, &bin_hdr[12 - 2]));
            } else {
                // Copy the user-defined stack header to the binary header. Skip EtherType.
                memcpy(bin_hdr + 12, info->vstax.bin + 2, VTSS_VSTAX_HDR_SIZE - 2);
            }
#endif
        } else {
            // A stack header is not already prefilled by the user, so we compose one
            // in order to control egress queue (CoS) and in order to convey tag info
            // and other info to the rewriter (if the frame needs rewriting).
            if (stack_port_no != VTSS_PORT_NO_NONE) {
                // When injecting to a stack port, the user must already have filled in the VStaX header.
                VTSS_E("Injecting without a stack header to a stack port");
                return VTSS_RC_ERROR;
            }

            vstax_lo |= VTSS_ENCODE_BITFIELD64(cos, 56, 3); // qos_class/iprio (internal priority)

            if (rewrite) {
                vstax_lo |= VTSS_ENCODE_BITFIELD64(info->dp,      60,  2);
                vstax_lo |= VTSS_ENCODE_BITFIELD64(info->tag.pcp, 29,  3);
                vstax_lo |= VTSS_ENCODE_BITFIELD64(info->tag.dei, 28,  1);
                vstax_lo |= VTSS_ENCODE_BITFIELD64(info->tag.vid, 16, 12);
                vstax_hi |= VTSS_ENCODE_BITFIELD64(info->cosid,   12,  3);
                if (info->isdx != VTSS_ISDX_NONE) {
                    if (!info->isdx_dont_use) {
                        fwd |= VTSS_ENCODE_BITFIELD64(1, 45, 1); // ESO_ISDX_KEY_ENA = 1
                    }
                    vstax_hi |= VTSS_ENCODE_BITFIELD64(info->isdx, 0, 12);
                }
                if (info->tag.tpid != 0 && info->tag.tpid != 0x8100) {
                    // S-tagged
                    vstax_lo |= VTSS_ENCODE_BITFIELD64(1, 14, 1);
                }
            } else if ((info->pipeline_pt == VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE) &&
                       (info->oam_type != VTSS_PACKET_OAM_TYPE_NONE)) {
                /*
                 * A Port MEP needs the COS-ID in the IFH for the sake of SLM-type OAM
                 */
                vstax_hi |= VTSS_ENCODE_BITFIELD64(info->cosid,   12,  3);

                if (info->isdx == VTSS_ISDX_NONE) {  // ESO_ISDX_KEY_ENA is configured to the opposite of the requested. Try not to hit ES0 when no rewriting is calculated
                    fwd |= VTSS_ENCODE_BITFIELD64(1, 45, 1);    // ESO_ISDX_KEY_ENA = 1
                }
            }
        }
    } else {    /* This is a switched frame - the frame is injected into the switch */
        if (info->masquerade_port == VTSS_PORT_NO_NONE) {
            // Normal switched frame.
            fwd |= VTSS_ENCODE_BITFIELD64(2, 23, 3); // MISC.PIPELINE_ACT = INJ_MASQ
        } else {
            /* This is OAM or Y1564 injection */
            vtss_packet_pipeline_pt_t pipeline_pt = info->pipeline_pt;

            // OAM Injection in an Up-MEP/MIP - The following will be according to TN1258 (EVC Baseline)
            chip_port = VTSS_CHIP_PORT_FROM_STATE(state, info->masquerade_port);

#if defined(VTSS_FEATURE_AFI_SWC)
            if (info->afi_id != VTSS_AFI_ID_NONE && pipeline_pt < VTSS_PACKET_PIPELINE_PT_ANA_CLM) {
                // Due to a chip error, one cannot inject in a pipeline point
                // that comes before CLM when masquerading and sending the frame
                // to the AFI. The reason is that the chip's analyzer will
                // overwrite the IFH's source port with the CPU's source port.
                // The IFH's source port is importantwhen up-injecting.
                // Being unable to inject before ANA_CLM may mean that S/W will
                // have to perform basic classification on the frame
                VTSS_E("Cannot inject into a pipeline point (%u) before ANA_CLM while masquerading and sending frame to AFI. "
                       "This may mean that S/W will have to perform basic classification on behalf of the chip and fill it into the IFH before injecting", pipeline_pt);
                pipeline_pt = VTSS_PACKET_PIPELINE_PT_ANA_CLM;
            }
#endif

            VTSS_IG(VTSS_TRACE_GROUP_PACKET, "Masqueraded OAM/Y.1564 Injection. Masq port = %u => chip port = %u. Pipeline PT = %d", info->masquerade_port, chip_port, pipeline_pt);

            if (info->isdx != VTSS_ISDX_NONE) {
                fwd      |= VTSS_ENCODE_BITFIELD64(1, 45, 1);                  // ESO_ISDX_KEY_ENA = 1
                vstax_hi |= VTSS_ENCODE_BITFIELD64(info->isdx, 0, 12);         // Isdx
            }

            if (info->tag.vid < VTSS_VIDS) {
                vlan = &state->l2.vlan_table[info->tag.vid];
                if ((pipeline_pt != VTSS_PACKET_PIPELINE_PT_ANA_CLM) && vlan->vsi_enable) { /* Not injection into CLM and VSI is enabled */
                    VTSS_DG(VTSS_TRACE_GROUP_PACKET, "VSI = %u", vlan->vsi->vsi);
                    dst |= VTSS_ENCODE_BITFIELD64(1,         45,  1);              // GEN_IDX_MODE = 1
                    dst |= VTSS_ENCODE_BITFIELD64(vlan->vsi->vsi, 46, 12);         // GEN_IDX = VSI
                }
            }

            vstax_hi |= VTSS_ENCODE_BITFIELD(info->cosid, 12, 3);              // COS id
            vstax_lo |= VTSS_ENCODE_BITFIELD64(info->dp,      60,  2);
            vstax_lo |= VTSS_ENCODE_BITFIELD64(info->tag.pcp, 29,  3);
            vstax_lo |= VTSS_ENCODE_BITFIELD64(info->tag.dei, 28,  1);
            vstax_lo |= VTSS_ENCODE_BITFIELD64(info->tag.vid, 16, 12);         // Classified VID
            vstax_lo |= VTSS_ENCODE_BITFIELD64(0, 10, 1);                      // Up injection according to Bugzilla#19337
            vstax_lo |= VTSS_ENCODE_BITFIELD64(0, 11, 1);                      // -"-
            vstax_lo |= VTSS_ENCODE_BITFIELD64(chip_port % 32, 0, 5);          // -"-
            vstax_lo |= VTSS_ENCODE_BITFIELD64(chip_port / 32, 5, 5);          // -"-
            vstax_lo |= VTSS_ENCODE_BITFIELD64(cos, 56, 3);                    // qos_class/iprio (internal priority)
            vstax_lo |= VTSS_ENCODE_BITFIELD64(0, 59, 1);                      // NO Super Priority
            vstax_lo |= VTSS_ENCODE_BITFIELD64(0, 60, 2);                      // Drop Precedence 0
            fwd      |= VTSS_ENCODE_BITFIELD64(0, 10, 8);                      // CPU_MASK = NO dport for switched frames
            fwd      |= VTSS_ENCODE_BITFIELD64(2, 23, 3);                      // MISC.PIPELINE_ACT = INJ_MASQ
            fwd      |= VTSS_ENCODE_BITFIELD64(pipeline_pt, 18, 5);            // MISC.PIPELINE_PT = pipeline_pt_val
            fwd      |= VTSS_ENCODE_BITFIELD64(0, 38,  3);                     // DST_MODE = ENCAP
            fwd      &= ~VTSS_ENCODE_BITFIELD64(0x3F, 27, 6);                  // SRC_PORT = 0
            fwd      |= VTSS_ENCODE_BITFIELD64(chip_port, 27, 6);              // SRC_PORT = masquerade port
            fwd      |= VTSS_ENCODE_BITFIELD64(info->dscp, 0, 6);              // DSCP

            if ((info->oam_type != VTSS_PACKET_OAM_TYPE_NONE) && (pipeline_pt != VTSS_PACKET_PIPELINE_PT_NONE) && (pipeline_pt != VTSS_PACKET_PIPELINE_PT_ANA_CLM)) {
                dst      |= VTSS_ENCODE_BITFIELD64(1, 35, 3);                      // PDU_TYPE = OAM_Y1731
                dst      |= VTSS_ENCODE_BITFIELD64(info->pdu_offset / 2, 38, 6);   // PDU_W16_OFFSET = pdu_offset (value 14 (DMAC+SMAC+ETYPE) is for untagged frame)
            }

            fwd      |= VTSS_ENCODE_BITFIELD64(0, 26, 1);                      // DO_NOT_REW = do rewrite
        }
    }

    ts = info->ptp_timestamp>>16;
    bin_hdr[ 0] = ts >>  24;
    bin_hdr[ 1] = ts >>  16;
    bin_hdr[ 2] = ts >>   8;
    bin_hdr[ 3] = ts >>   0;
    bin_hdr[ 4] = dst >> 56;
    bin_hdr[ 5] = dst >> 48;
    bin_hdr[ 6] = dst >> 40;
    bin_hdr[ 7] = dst >> 32;
    bin_hdr[ 8] = dst >> 24;
    bin_hdr[ 9] = dst >> 16;
    bin_hdr[10] = dst >>  8;
    bin_hdr[11] = dst >>  0;
    if (!contains_stack_hdr) {
        bin_hdr[12] = vstax_hi >>  8;
        bin_hdr[13] = vstax_hi >>  0;
        bin_hdr[14] = vstax_lo >> 56;
        bin_hdr[15] = vstax_lo >> 48;
        bin_hdr[16] = vstax_lo >> 40;
        bin_hdr[17] = vstax_lo >> 32;
        bin_hdr[18] = vstax_lo >> 24;
        bin_hdr[19] = vstax_lo >> 16;
        bin_hdr[20] = vstax_lo >>  8;
        bin_hdr[21] = vstax_lo >>  0;
    }

    bin_hdr[22] = fwd >> 40;
    bin_hdr[23] = fwd >> 32;
    bin_hdr[24] = fwd >> 24;
    bin_hdr[25] = fwd >> 16;
    bin_hdr[26] = fwd >>  8;
    bin_hdr[27] = fwd >>  0;

    VTSS_IG(VTSS_TRACE_GROUP_PACKET, "IFH:");
    VTSS_IG_HEX(VTSS_TRACE_GROUP_PACKET, &bin_hdr[0], *bin_hdr_len);

    return VTSS_RC_OK;
}

static vtss_rc jr2_tx_frame_ifh_vid(vtss_state_t *vtss_state,
                                    const vtss_packet_tx_ifh_t *const ifh,
                                    const u8 *const frame,
                                    const u32 length,
                                    const vtss_vid_t vid)
{
    u32 val, w, count, last;
    const u8 *buf = frame;
    vtss_packet_tx_grp_t grp = 0;

    VTSS_N("length: %u, vid: %u, ifhlen: %d", length, vid, ifh->length);

    if (ifh->length != JR2_IFH_BYTES) {
        return VTSS_RC_ERROR;
    }

    JR2_RD(VTSS_DEVCPU_QS_INJ_INJ_STATUS, &val);
    if (!(VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_FIFO_RDY(val) & VTSS_BIT(grp))) {
        VTSS_E("Not ready");
        return VTSS_RC_ERROR;
    }

    if (VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED(val) & VTSS_BIT(grp)) {
        VTSS_E("Watermark reached");
        return VTSS_RC_ERROR;
    }

    /* Indicate SOF */
    JR2_WR(VTSS_DEVCPU_QS_INJ_INJ_CTRL(grp), VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(1) | VTSS_M_DEVCPU_QS_INJ_INJ_CTRL_SOF);

    // Write the IFH to the chip.
    for (w = 0; w < JR2_IFH_WORDS; w++) {
        JR2_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), ifh->ifh[w]);
    }

    /* Write words, round up */
    count = ((length + 3) / 4);
    last = length % 4;
    for (w = 0; w < count; w++, buf += 4) {
        if (w == 3 && vid != VTSS_VID_NULL) {
            /* Insert C-tag */
            JR2_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), VTSS_OS_NTOHL((0x8100U << 16) | vid));
            w++;
        }
#ifdef VTSS_OS_BIG_ENDIAN
        JR2_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
#else
        JR2_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
#endif
    }

    /* Add padding */
    while (w < (60 / 4)) {
        JR2_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), 0);
        w++;
    }

    /* Indicate EOF and valid bytes in last word */
    JR2_WR(VTSS_DEVCPU_QS_INJ_INJ_CTRL(grp),
           VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(1) |
           VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES(length < 60 ? 0 : last) |
           VTSS_M_DEVCPU_QS_INJ_INJ_CTRL_EOF);

    /* Add dummy CRC */
    JR2_WR(VTSS_DEVCPU_QS_INJ_INJ_WR(grp), 0);
    w++;

    VTSS_N("wrote %u words, last: %u", w, last);

    return VTSS_RC_OK;
}

static vtss_rc jr2_tx_frame_ifh(vtss_state_t *vtss_state,
                                const vtss_packet_tx_ifh_t *const ifh,
                                const u8 *const frame,
                                const u32 length)
{
    return jr2_tx_frame_ifh_vid(vtss_state, ifh, frame, length, VTSS_VID_NULL);
}

static vtss_rc jr2_tx_frame_port(vtss_state_t *vtss_state,
                                 const vtss_port_no_t  port_no,
                                 const u8              *const frame,
                                 const u32             length,
                                 const vtss_vid_t      vid)
{
    vtss_packet_tx_ifh_t ifh;
    vtss_packet_tx_info_t tx_info;
    vtss_rc rc;

    (void) vtss_packet_tx_info_init(vtss_state, &tx_info);
    tx_info.dst_port_mask = VTSS_BIT64(port_no);

    ifh.length = sizeof(ifh.ifh);
    if ((rc = jr2_tx_hdr_encode(vtss_state, &tx_info, (u8 *) ifh.ifh, &ifh.length) != VTSS_RC_OK)) {
        return rc;
    }
    return jr2_tx_frame_ifh_vid(vtss_state, &ifh, frame, length, vid);
}

/* - Debug print --------------------------------------------------- */

static vtss_rc jr2_debug_pkt(vtss_state_t              *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_MANUAL, XTRINJ_MANUAL_CFG, "XTRINJ_MANUAL_CFG");
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_packet_debug_print(vtss_state_t              *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_PACKET, jr2_debug_pkt, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */
static vtss_rc jr2_packet_init(vtss_state_t *vtss_state)
{
    vtss_packet_rx_queue_t qu;
    u32                    val;
    u32                    i;
    int                    pcp, dei;

    // The extraction queues can be redirected to any port.
    // This is used to redirect selected queues to an NPI port, but also the uFDMA
    // may use this feature to redirect to a dummy port when throttling.
    // The NPI settings take precedence over the uFDMA, but we need to keep track of
    // what the uFDMA wants to set it to in case the application enables and disables NPI redirection.
    for (qu = 0; qu < vtss_state->packet.rx_queue_count; qu++) {
        JR2_RD(VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_CPU_QU(qu)), &val);
        vtss_state->packet.default_qu_redirect[qu] = VTSS_X_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL(val);
    }

    // Set-up default packet Rx endianness, position of status word, and who will be extracting.
    for (i = 0; i < VTSS_PACKET_RX_GRP_CNT; i++) {
#ifdef VTSS_OS_BIG_ENDIAN
        // Big-endian
        JR2_WRM_CLR(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_M_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP);
#else
        // Little-endian
        JR2_WRM_SET(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_M_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP);
#endif

        if (!vtss_state->sys_config.using_vrap) {
            if (!vtss_state->init_conf.using_ufdma || i != 0) {
                // Only write instance 0 of this register if not using the uFDMA, which may be loaded before
                // the switch application, because it may be part of a Linux kernel.
                // If not using VRAP, default to do register-based extraction.
                // The uFDMA driver may change this field to "2" later.
                JR2_WRM(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE(1), VTSS_M_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE);
            }
        }

        // Status word (only used when manually extracting) must come just before last data
        JR2_WRM_CLR(VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(i), VTSS_M_DEVCPU_QS_XTR_XTR_GRP_CFG_STATUS_WORD_POS);
    }

    // Set-up default packet Tx endianness and who will be injecting.
    for (i = 0; i < VTSS_PACKET_TX_GRP_CNT; i++) {
#ifdef VTSS_OS_BIG_ENDIAN
        // Big-endian
        JR2_WRM_CLR(VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(i), VTSS_M_DEVCPU_QS_INJ_INJ_GRP_CFG_BYTE_SWAP);
#else
        // Little-endian
        JR2_WRM_SET(VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(i), VTSS_M_DEVCPU_QS_INJ_INJ_GRP_CFG_BYTE_SWAP);
#endif

        if (!vtss_state->init_conf.using_ufdma || i != 0) {
            // According to the datasheet, we must insert a small delay after every end-of-frame when injecting to QS.
            JR2_WRM(VTSS_DEVCPU_QS_INJ_INJ_CTRL(i), VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(0), VTSS_M_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE);
        }

        if (!vtss_state->sys_config.using_vrap) {
            // If not using VRAP, default to do register-based injection. The uFDMA driver may change this field to "2" later.
            if (!vtss_state->init_conf.using_ufdma || i != 0) {
                // Only write instance 0 of this register if not using the uFDMA, which may be loaded before
                // the switch application, because it may be part of a Linux kernel.
                JR2_WRM(VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(i), VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE(1), VTSS_M_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE);
            }
        }
    }

    // Setup CPU port 0 and 1. Only do this if not using VRAP
    for (i = VTSS_CHIP_PORT_CPU_0; i <= VTSS_CHIP_PORT_CPU_1 && !vtss_state->sys_config.using_vrap; i++) {
        // This register is not replicated for CPU ports on JR2, but it will be
        // on future chips, which is why it's just commented out here. If commmented in,
        // the actual registers that are written is REW:COMMON:TPID_CFG[0-1],
        // where the first replication will be overwritten later by the
        // application.
        // Enable IFH insertion upon extraction
        // JR2_WRM(VTSS_REW_COMMON_PORT_CTRL(i), VTSS_F_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL(1), VTSS_M_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL);

        // Enable IFH parsing upon injection (no prefix)
        JR2_WRM(VTSS_ASM_CFG_PORT_CFG(i), VTSS_F_ASM_CFG_PORT_CFG_INJ_FORMAT_CFG(1), VTSS_M_ASM_CFG_PORT_CFG_INJ_FORMAT_CFG);

        // We don't have a preamble when injecting into the CPU ports (when not using VRAP).
        JR2_WRM(VTSS_ASM_CFG_PORT_CFG(i), VTSS_F_ASM_CFG_PORT_CFG_NO_PREAMBLE_ENA(1), VTSS_M_ASM_CFG_PORT_CFG_NO_PREAMBLE_ENA);

        // Prevent chip from moving a possible VStaX header from the frame payload into the IFH (we have already composed
        // the IFH with a proper VStaX header).
        JR2_WRM(VTSS_ASM_CFG_PORT_CFG(i), VTSS_F_ASM_CFG_PORT_CFG_VSTAX2_AWR_ENA(0), VTSS_M_ASM_CFG_PORT_CFG_VSTAX2_AWR_ENA);

        // Strict priority when reading the two CPU ports is default.
    }

    // Setup CPU port 0 and 1 to allow for classification of transmission of
    // switched frames into a user-module-specifiable QoS class.
    // For the two CPU ports, we set a one-to-one mapping between a VLAN tag's
    // PCP and a QoS class. When transmitting switched frames, the PCP value
    // of the VLAN tag (which is always inserted to get it switched on a given
    // VID), then controls the priority.
    // Enable looking into PCP and DEI bits
    JR2_WRM(VTSS_ANA_CL_PORT_QOS_CFG(VTSS_CHIP_PORT_CPU),
            VTSS_F_ANA_CL_PORT_QOS_CFG_PCP_DEI_DP_ENA(1) | VTSS_F_ANA_CL_PORT_QOS_CFG_PCP_DEI_QOS_ENA(1),
            VTSS_M_ANA_CL_PORT_QOS_CFG_PCP_DEI_DP_ENA    | VTSS_M_ANA_CL_PORT_QOS_CFG_PCP_DEI_QOS_ENA);

    // Set-up the one-to-one PCP->QoS mapping
    for (pcp = 0; pcp < VTSS_PCP_END - VTSS_PCP_START; pcp++) {
        for (dei = 0; dei < VTSS_DEI_END - VTSS_DEI_START; dei++) {
            JR2_WR(VTSS_ANA_CL_PORT_PCP_DEI_MAP_CFG(VTSS_CHIP_PORT_CPU, (8 * dei + pcp)),
                   VTSS_F_ANA_CL_PORT_PCP_DEI_MAP_CFG_PCP_DEI_QOS_VAL(pcp));
        }
    }

    for (i = VTSS_CHIP_PORT_CPU_0; i <= VTSS_CHIP_PORT_CPU_1; i++) {
        // Disable aging of Rx CPU queues to allow the frames to stay there longer than
        // on normal front ports.
        JR2_WRM(VTSS_HSCH_HSCH_MISC_PORT_MODE(i), VTSS_F_HSCH_HSCH_MISC_PORT_MODE_AGE_DIS(1), VTSS_M_HSCH_HSCH_MISC_PORT_MODE_AGE_DIS);
        JR2_WRM(VTSS_DSM_CFG_BUF_CFG(i),          VTSS_F_DSM_CFG_BUF_CFG_AGING_ENA(0),        VTSS_M_DSM_CFG_BUF_CFG_AGING_ENA);

        // Enable stacking on CPU ports for VLAN classification purposes
        JR2_WRM(VTSS_ANA_CL_PORT_STACKING_CTRL(i),
                VTSS_F_ANA_CL_PORT_STACKING_CTRL_STACKING_AWARE_ENA(1),
                VTSS_M_ANA_CL_PORT_STACKING_CTRL_STACKING_AWARE_ENA);
        JR2_WRM(VTSS_ANA_CL_PORT_STACKING_CTRL(i),
                VTSS_F_ANA_CL_PORT_STACKING_CTRL_STACKING_HEADER_DISCARD_ENA(0),
                VTSS_M_ANA_CL_PORT_STACKING_CTRL_STACKING_HEADER_DISCARD_ENA);

        // Set CPU ports to be VLAN aware, since frames that we send switched
        // must contain a VLAN tag for correct classification. One could use
        // the frame's VStaX header, but that won't work for stacking solutions.
        // We also set it to pop one tag.
        JR2_WRM(VTSS_ANA_CL_PORT_VLAN_CTRL(i),
                VTSS_F_ANA_CL_PORT_VLAN_CTRL_PORT_VID      (0) |
                VTSS_F_ANA_CL_PORT_VLAN_CTRL_VLAN_AWARE_ENA(1) |
                VTSS_F_ANA_CL_PORT_VLAN_CTRL_VLAN_POP_CNT  (1),
                VTSS_M_ANA_CL_PORT_VLAN_CTRL_PORT_VID          |
                VTSS_M_ANA_CL_PORT_VLAN_CTRL_VLAN_AWARE_ENA    |
                VTSS_M_ANA_CL_PORT_VLAN_CTRL_VLAN_POP_CNT);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_packet_state_t *state = &vtss_state->packet;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->rx_conf_set              = jr2_rx_conf_set;
        state->rx_frame_get             = jr2_rx_frame_get;
        state->rx_frame_get_raw         = jr2_rx_frame_get_raw;
        state->rx_frame_discard         = jr2_rx_frame_discard;
        state->tx_frame_port            = jr2_tx_frame_port;
        state->tx_frame_ifh             = jr2_tx_frame_ifh;
        state->rx_hdr_decode            = jr2_rx_hdr_decode;
        state->rx_ifh_size              = VTSS_JR2_RX_IFH_SIZE;
        state->tx_hdr_encode            = jr2_tx_hdr_encode;
        state->vstax_header2frame       = jr2_vstax_header2frame;
        state->vstax_frame2header       = jr2_vstax_frame2header;
        state->npi_conf_set             = jr2_npi_conf_set;
        state->packet_phy_cnt_to_ts_cnt = jr2_packet_phy_cnt_to_ts_cnt;
        state->packet_ns_to_ts_cnt      = jr2_packet_ns_to_ts_cnt;
        state->ptp_get_timestamp        = jr2_ptp_get_timestamp;
        state->dma_conf_set             = jr2_dma_conf_set;
        state->dma_offset               = jr2_dma_offset;
        state->rx_queue_count           = VTSS_PACKET_RX_QUEUE_CNT;

        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(jr2_packet_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        if (!vtss_state->warm_start_cur) {
            VTSS_RC(jr2_rx_conf_set(vtss_state));
        }
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_JAGUAR_2 */
