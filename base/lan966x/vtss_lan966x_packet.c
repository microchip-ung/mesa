// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

/* ================================================================= *
 *  NPI
 * ================================================================= */

static vtss_rc lan966x_npi_conf_set(vtss_state_t *vtss_state, const vtss_npi_conf_t *const new)
{
    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc lan966x_packet_phy_cnt_to_ts_cnt(vtss_state_t *vtss_state, u32 phy_cnt, u64 *ts_cnt)
{
    VTSS_I("Not supported in this architecture");
    *ts_cnt = 0;

    return VTSS_RC_OK;
}

static vtss_rc lan966x_packet_ns_to_ts_cnt(vtss_state_t  *vtss_state,
                                           u32            ns,
                                           u64            *ts_cnt)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ptp_get_timestamp(vtss_state_t                    *vtss_state,
                                         const u8                        *const frm,
                                         const vtss_packet_rx_info_t     *const rx_info,
                                         vtss_packet_ptp_message_type_t  message_type,
                                         vtss_packet_timestamp_props_t   ts_props,
                                         u64                             *rxTime,
                                         BOOL                            *timestamp_ok)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_rx_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_tx_frame_ifh(vtss_state_t *vtss_state,
                                    const vtss_packet_tx_ifh_t *const ifh,
                                    const u8 *const frame,
                                    const u32 length)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_rx_hdr_decode(const vtss_state_t          *const state,
                                     const vtss_packet_rx_meta_t *const meta,
                                     const u8                           xtr_hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                     vtss_packet_rx_info_t *const info)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_rx_frame(struct vtss_state_s  *vtss_state,
                                u8                   *const data,
                                const u32             buflen,
                                vtss_packet_rx_info_t *rx_info)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_tx_hdr_encode(vtss_state_t          *const state,
                                     const vtss_packet_tx_info_t *const info,
                                     u8                    *const bin_hdr,
                                     u32                   *const bin_hdr_len)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

vtss_rc vtss_lan966x_packet_debug_print(vtss_state_t *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_packet_init(vtss_state_t *vtss_state)
{
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
        state->rx_ifh_size = VTSS_SVL_RX_IFH_SIZE;
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
