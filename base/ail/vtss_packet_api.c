/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"
#include "vtss_util.h"

#if defined(VTSS_FEATURE_PACKET)

/* - Configuration ------------------------------------------------- */

vtss_rc vtss_packet_rx_conf_get(const vtss_inst_t      inst,
                                vtss_packet_rx_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        *conf = vtss_state->packet.rx_conf;
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_rx_conf_set(const vtss_inst_t            inst,
                                const vtss_packet_rx_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->packet.rx_conf = *conf;
        rc = VTSS_FUNC_0(packet.rx_conf_set);
#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
        if (rc == VTSS_RC_OK) {
            rc = VTSS_FUNC(qos.cpu_port_shaper_set, conf->shaper_rate);
        }
#endif /* defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER) */
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_rx_port_conf_get(const vtss_inst_t          inst,
                                     const vtss_port_no_t       port_no,
                                     vtss_packet_rx_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *conf = vtss_state->packet.rx_port_conf[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_rx_port_conf_set(const vtss_inst_t                inst,
                                     const vtss_port_no_t             port_no,
                                     const vtss_packet_rx_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->packet.rx_port_conf[port_no] = *conf;
        rc = VTSS_FUNC_0(packet.rx_conf_set);
    }
    VTSS_EXIT();
    return rc;
}

/* - Rx frame ------------------------------------------------------ */

static vtss_rc vtss_packet_queue_check(vtss_state_t *vtss_state,
                                       const vtss_packet_rx_queue_t queue_no)
{
    if (queue_no >= vtss_state->packet.rx_queue_count) {
        VTSS_E("illegal queue_no: %u", queue_no);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_packet_rx_frame_get(const vtss_inst_t             inst,
                                 const vtss_packet_rx_queue_t  queue_no,
                                 vtss_packet_rx_header_t       *const header,
                                 u8                            *const frame,
                                 const u32                     length)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("queue_no: %u", queue_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_packet_queue_check(vtss_state, queue_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(packet.rx_frame_get, queue_no, header, frame, length);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_rx_frame_get_raw(const vtss_inst_t inst,
                                     u8                *const data,
                                     const u32         buflen,
                                     u32               *const ifhlen,
                                     u32               *const frmlen)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(packet.rx_frame_get_raw, data, buflen, ifhlen, frmlen);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_rx_frame_discard(const vtss_inst_t             inst,
                                     const vtss_packet_rx_queue_t  queue_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("queue_no: %u", queue_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_packet_queue_check(vtss_state, queue_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(packet.rx_frame_discard, queue_no);
    }
    VTSS_EXIT();
    return rc;
}

/* - Tx frame ------------------------------------------------------ */

static vtss_rc vtss_packet_tx_port(vtss_state_t         *vtss_state,
                                   const vtss_port_no_t port_no,
                                   const u8             *const frame,
                                   const u32            length)
{
    vtss_rc                rc;
    vtss_port_no_t         mirror_port = vtss_state->l2.mirror_conf.port_no;
#if defined(VTSS_FEATURE_VSTAX)
    vtss_vstax_tx_header_t vstax;

    vstax.fwd_mode = VTSS_VSTAX_FWD_MODE_CPU_ALL;
    vstax.ttl = 1;
    vstax.prio = VTSS_PRIO_SUPER;
    vstax.tci.vid = VTSS_VID_NULL;
    vstax.tci.cfi = 0;
    vstax.tci.tagprio = 0;
    vstax.port_no = VTSS_PORT_NO_NONE;
    vstax.queue_no = VTSS_PACKET_RX_QUEUE_START;

    vtss_state->l2.vstax_tx_header = &vstax;
#endif /* VTSS_FEATURE_VSTAX */

    VTSS_N("port_no: %u, length: %u", port_no, length);

    /* If egress mirroring is enabled, send on mirror port */
    if (vtss_state->l2.mirror_egress[port_no] &&
        mirror_port != VTSS_PORT_NO_NONE && port_no != mirror_port &&
        vtss_state->l2.port_state[mirror_port]) {
        if ((rc = VTSS_FUNC(packet.tx_frame_port, mirror_port,
                            frame, length, VTSS_VID_NULL)) != VTSS_RC_OK)
            return rc;
    }
    return VTSS_FUNC(packet.tx_frame_port, port_no, frame, length, VTSS_VID_NULL);
}

vtss_rc vtss_packet_tx_frame(const vtss_inst_t           inst,
                             const vtss_packet_tx_ifh_t *const ifh,
                             const u8                   *const frame,
                             const u32                   length)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    if (ifh != NULL && frame != NULL && length > 0 && ifh->length <= VTSS_PACKET_TX_IFH_MAX) {
        if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
            VTSS_N("ifh: %u, length: %u", ifh->length, length);
            VTSS_ENTER();
            rc = VTSS_FUNC(packet.tx_frame_ifh, ifh, frame, length);
            VTSS_EXIT();
        }
    }
    return rc;
}

vtss_rc vtss_packet_tx_frame_port(const vtss_inst_t     inst,
                                  const vtss_port_no_t  port_no,
                                  const u8              *const frame,
                                  const u32             length)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        rc = vtss_packet_tx_port(vtss_state, port_no, frame, length);
    VTSS_EXIT();
    return rc;
}

/* - Frame filter -------------------------------------------------- */

static vtss_rc vtss_packet_port_filter(vtss_state_t                  *state,
                                       const vtss_packet_port_info_t *const info,
                                       vtss_packet_port_filter_t     filter[VTSS_PORT_ARRAY_SIZE],
                                       BOOL tx_filter)
{
    vtss_port_no_t            port_rx, port_tx;
    vtss_vid_t                vid, uvid;
    vtss_aggr_no_t            aggr_no;

    vtss_packet_port_filter_t *port_filter;
    BOOL                      vlan_filter = 0, vlan_member[VTSS_PORT_ARRAY_SIZE];
    vtss_vlan_port_conf_t     *vlan_port_conf;

    port_rx = info->port_no;
    vid = info->vid;
    memset(vlan_member, 0, VTSS_PORT_ARRAY_SIZE); /* Please Lint */
    if (vid != VTSS_VID_NULL) {
        vlan_filter = 1;
        VTSS_RC(vtss_cmn_vlan_members_get(state, vid, vlan_member));
    }

    for (port_tx = VTSS_PORT_NO_START; port_tx < state->port_count; port_tx++) {
        /* Discard by default */
        port_filter = &filter[port_tx];
        port_filter->filter = VTSS_PACKET_FILTER_DISCARD;

        /* Ingress port filtering */
        if (port_rx != VTSS_PORT_NO_NONE) {
            if (!state->l2.rx_forward[port_rx]) {
                /* Rx forward filtering */
                VTSS_N("port_rx %u not ingress forwarding", port_rx);
                continue;
            }

            if (vlan_filter && vlan_member[port_rx] == 0 &&
                state->l2.vlan_port_conf[port_rx].ingress_filter) {
                /* VLAN/MSTP/ERPS/.. ingress filtering */
                VTSS_N("port_rx %u not member of VLAN %u", port_rx, vid);
                continue;
            }

            /* If Tx filtering is not required, return result for the first port only */
            if (!tx_filter) {
                port_filter->filter = VTSS_PACKET_FILTER_UNTAGGED;
                return VTSS_RC_OK;
            }

            /* Ingress and egress port filtering (forwarding) */
            if (port_rx == port_tx) {
                /* Source port filtering */
                VTSS_N("port_rx %u and port_tx %u are identical", port_rx, port_tx);
                continue;
            }

            aggr_no = state->l2.port_aggr_no[port_rx];
            if (info->aggr_rx_disable == 0 &&
                aggr_no != VTSS_AGGR_NO_NONE &&
                state->l2.port_aggr_no[port_tx] == aggr_no) {
                /* Ingress LLAG filter */
                VTSS_N("port_rx %u and port_tx %u are members of same LLAG %u",
                       port_rx, port_tx, aggr_no);
                continue;
            }
        }

        /* Egress port filtering */
        if (vlan_filter && vlan_member[port_tx] == 0) {
            /* VLAN/MSTP/ERPS/.. egress filtering */
            VTSS_N("port_tx %u not member of VLAN %u", port_tx, vid);
            continue;
        }

        if (info->aggr_tx_disable) {
            if (!state->l2.tx_forward[port_tx]) {
                /* Egress Forward mode check */
                VTSS_N("port_tx: %u not forwarding", port_tx);
                continue;
            }
        } else if (!state->l2.tx_forward_aggr[port_tx]) {
            /* Egress LAG/STP check */
            VTSS_N("port_tx: %u not LAG/STP forwarding", port_tx);
            continue;
        }

        /* Determine whether to send tagged or untagged */
        vlan_port_conf = &state->l2.vlan_port_conf[port_tx];
        uvid = vlan_port_conf->untagged_vid;
        port_filter->filter = (uvid != VTSS_VID_ALL && uvid != vid ?
                               VTSS_PACKET_FILTER_TAGGED : VTSS_PACKET_FILTER_UNTAGGED);

        /* Determine tag type */
        port_filter->tpid = VTSS_ETYPE_TAG_C;
        switch (vlan_port_conf->port_type) {
        case VTSS_VLAN_PORT_TYPE_S:
            port_filter->tpid = VTSS_ETYPE_TAG_S;
            break;
        case VTSS_VLAN_PORT_TYPE_S_CUSTOM:
            port_filter->tpid = state->l2.vlan_conf.s_etype;
            break;
        default:
            break;
        }
    } /* Port loop */
    return VTSS_RC_OK;
}

static vtss_rc vtss_packet_filter(vtss_state_t                    *state,
                                  const vtss_packet_frame_info_t  *const info,
                                  vtss_packet_filter_t            *const filter)
{
    vtss_packet_port_info_t   port_info;
    vtss_packet_port_filter_t port_filter[VTSS_PORT_ARRAY_SIZE];
    BOOL                      tx_filter = (info->port_tx == VTSS_PORT_NO_NONE ? 0 : 1);

    /* Copy fields to port filter */
    port_info.port_no = info->port_no;
    port_info.vid = info->vid;
    port_info.aggr_rx_disable = info->aggr_rx_disable;
    port_info.aggr_tx_disable = info->aggr_tx_disable;

    /* Use port filter function */
    VTSS_RC(vtss_packet_port_filter(state, &port_info, port_filter, tx_filter));
    *filter = port_filter[tx_filter ? info->port_tx : 0].filter;
    return VTSS_RC_OK;
}

static vtss_rc vtss_packet_tx_port_vlan(vtss_state_t          *vtss_state,
                                        const vtss_port_no_t  port_no,
                                        const vtss_vid_t      vid,
                                        const u8              *const frame,
                                        const u32             length)
{
    vtss_rc                  rc;
    vtss_port_no_t           port;
    vtss_mac_table_entry_t   mac_entry;
    u32                      i;
    BOOL                     mac_found = 0, mirror = 0, mirror_done = 0;
    vtss_packet_frame_info_t info;
    vtss_packet_filter_t     filter;
    vtss_vid_t               uvid, tx_vid;
#if defined(VTSS_FEATURE_VSTAX)
    vtss_vstax_tx_header_t   vstax;

    vstax.fwd_mode = VTSS_VSTAX_FWD_MODE_LOOKUP;
    vstax.ttl = VTSS_VSTAX_TTL_PORT;
    vstax.prio = VTSS_PRIO_START;
    vstax.tci.vid = vid;
    vstax.tci.cfi = 0;
    vstax.tci.tagprio = 0;
    vtss_state->l2.vstax_tx_header = &vstax;
#endif /* VTSS_FEATURE_VSTAX */

    VTSS_N("port_no: %u, vid: %u, length: %u", port_no, vid, length);

    VTSS_RC(vtss_vid_check(vid));

    memset(&mac_entry, 0, sizeof(mac_entry)); /* Please Lint */
    if (port_no == VTSS_PORT_NO_NONE) {
        /* Lookup (VID, DMAC) */
        mac_entry.vid_mac.vid = vid;
        for (i = 0; i < 6; i++)
            mac_entry.vid_mac.mac.addr[i] = frame[i];
        mac_found = (vtss_mac_get(vtss_state, &mac_entry.vid_mac, &mac_entry) == VTSS_RC_OK);
    }

    /* Filter on VLAN, no ingress filtering */
    vtss_packet_frame_info_init(&info);
    info.vid = vid;

    /* Transmit on ports */
    for (port = VTSS_PORT_NO_START; port < vtss_state->port_count; port++) {

        /* Port check */
        if (port_no != VTSS_PORT_NO_NONE && port != port_no) {
            VTSS_N("skip port: %u", port);
            continue;
        }

        /* Destination port check */
        if (mac_found && mac_entry.destination[port] == 0) {
            VTSS_N("port: %u not a destination member", port);
            continue;
        }

        /* Egress filtering */
        info.port_tx = port;
        if (vtss_packet_filter(vtss_state, &info, &filter) != VTSS_RC_OK ||
            filter == VTSS_PACKET_FILTER_DISCARD) {
            VTSS_N("port: %u filtered", port);
            continue;
        }

        /* All checks successful, transmit on port */
        VTSS_N("tx on port: %u", port);
        tx_vid = (filter == VTSS_PACKET_FILTER_TAGGED ? vid : VTSS_VID_NULL);
        if ((rc = VTSS_FUNC(packet.tx_frame_port, port, frame, length, tx_vid)) != VTSS_RC_OK)
            return rc;

        /* Check if egress mirroring must be done */
        if (vtss_state->l2.mirror_egress[port])
            mirror = 1;

        /* Check if egress mirroring has been done */
        if (port == vtss_state->l2.mirror_conf.port_no)
            mirror_done = 1;
    }

    port = vtss_state->l2.mirror_conf.port_no;
    if (port_no != VTSS_PORT_NO_NONE &&
        mirror && !mirror_done && port != VTSS_PORT_NO_NONE &&
        vtss_state->l2.stp_state[port] == VTSS_STP_STATE_FORWARDING) {
        uvid = vtss_state->l2.vlan_port_conf[port_no].untagged_vid;
        tx_vid = (uvid != VTSS_VID_ALL && uvid != vid ? vid : VTSS_VID_NULL);
        if ((rc = VTSS_FUNC(packet.tx_frame_port, port, frame, length, tx_vid)) != VTSS_RC_OK)
            return rc;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_packet_tx_frame_port_vlan(const vtss_inst_t     inst,
                                       const vtss_port_no_t  port_no,
                                       const vtss_vid_t      vid,
                                       const u8              *const frame,
                                       const u32             length)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        rc = vtss_packet_tx_port_vlan(vtss_state, port_no, vid, frame, length);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_tx_frame_vlan(const vtss_inst_t  inst,
                                  const vtss_vid_t   vid,
                                  const u8           *const frame,
                                  const u32          length)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_packet_tx_port_vlan(vtss_state, VTSS_PORT_NO_NONE, vid, frame, length);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_frame_filter(const vtss_inst_t               inst,
                                 const vtss_packet_frame_info_t  *const info,
                                 vtss_packet_filter_t            *const filter)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if ((rc = vtss_inst_check_get(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_packet_filter(vtss_state, info, filter);
    return rc;
}

void vtss_packet_frame_info_init(vtss_packet_frame_info_t *const info)
{
    memset(info, 0, sizeof(*info));
    info->port_no = VTSS_PORT_NO_NONE;
    info->port_tx = VTSS_PORT_NO_NONE;
}

vtss_rc vtss_packet_port_info_init(vtss_packet_port_info_t *const info)
{
    memset(info, 0, sizeof(*info));
    info->port_no = VTSS_PORT_NO_NONE;
    return VTSS_RC_OK;
}

vtss_rc vtss_packet_port_filter_get(const vtss_inst_t             inst,
                                    const vtss_packet_port_info_t *const info,
                                    vtss_packet_port_filter_t     filter[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if ((rc = vtss_inst_check_get(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_packet_port_filter(vtss_state, info, filter, 1);
    return rc;
}

vtss_rc vtss_packet_vlan_filter_get(const vtss_inst_t         inst,
                                    vtss_packet_vlan_filter_t filter[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_vid_t     vid;
    vtss_port_no_t port_no;
    BOOL           member[VTSS_PORT_ARRAY_SIZE];

    if ((rc = vtss_inst_check_get(inst, &vtss_state)) == VTSS_RC_OK) {
        memset(filter, 0, VTSS_PORT_ARRAY_SIZE * sizeof(vtss_packet_vlan_filter_t));
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            /* Rx and Tx forwarding */
            filter[port_no].rx_forward = vtss_state->l2.rx_forward[port_no];
            filter[port_no].tx_forward = vtss_state->l2.tx_forward[port_no];
        }
        for (vid = VTSS_VID_DEFAULT; vid < VTSS_VIDS; vid++) {
            if (vtss_cmn_vlan_members_get(vtss_state, vid, member) == VTSS_RC_OK) {
                for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                    /* VLAN/MSTP/ERPS/.. filtering */
                    if (!member[port_no]) {
                        filter[port_no].vlan_discard[vid/8] |= (1 << (vid % 8));
                    }
                }
            }
        }
    }
    return rc;
}

vtss_rc vtss_packet_vlan_status_get(const vtss_inst_t         inst,
                                    vtss_packet_vlan_status_t *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if ((rc = vtss_inst_check_get(inst, &vtss_state)) == VTSS_RC_OK) {
        status->changed = vtss_state->l2.vlan_filter_changed;
        vtss_state->l2.vlan_filter_changed = FALSE;
    }
    return rc;
}

vtss_rc vtss_packet_vlan_vsi_map_get(const vtss_inst_t          inst,
                                     vtss_packet_vlan_vsi_map_t *const map)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if ((rc = vtss_inst_check_get(inst, &vtss_state)) == VTSS_RC_OK) {
        *map = vtss_state->packet.vid2vsi;
    }
    return rc;
}

#if defined(VTSS_FEATURE_VSTAX)
vtss_rc vtss_packet_tx_frame_vstax(const vtss_inst_t             inst,
                                   const vtss_port_no_t          port_no,
                                   const vtss_vstax_tx_header_t  *const header,
                                   const u8                      *const frame,
                                   const u32                     length)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("port_no: %u, length: %u", port_no, length);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.vstax_tx_header = header;
        rc = VTSS_FUNC(packet.tx_frame_port, port_no, frame, length, VTSS_VID_NULL);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_vstax_header2frame(const vtss_inst_t             inst,
                                       const vtss_port_no_t          port_no,
                                       const vtss_vstax_tx_header_t  *const header,
                                       u8                            *const frame)
{
    // This function doesn't require vtss_state be set up correctly,
    // and if running stackable and doing a lengthy API function
    // (e.g. a debug print function), the stack will fall apart unless
    // this function executes without waiting for the API semaphore.
    vtss_state_t *vtss_state = vtss_inst_check_no_persist(inst);

    return VTSS_FUNC_FROM_STATE(vtss_state, packet.vstax_header2frame, port_no, header, frame);
}

vtss_rc vtss_packet_vstax_frame2header(const vtss_inst_t       inst,
                                       const u8                *const frame,
                                       vtss_vstax_rx_header_t  *const header)
{
    // This function doesn't require vtss_state be set up correctly,
    // and if running stackable and doing a lengthy API function
    // (e.g. a debug print function), the stack will fall apart unless
    // this function executes without waiting for the API semaphore.
    vtss_state_t *vtss_state = vtss_inst_check_no_persist(inst);

    return VTSS_FUNC_FROM_STATE(vtss_state, packet.vstax_frame2header, frame, header);
}
#endif /* VTSS_FEATURE_VSTAX */

/*
 * Decode an extraction header.
 */
vtss_rc vtss_packet_rx_hdr_decode(const vtss_inst_t                  inst,
                                  const vtss_packet_rx_meta_t *const meta,
                                  const u8                           hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                        vtss_packet_rx_info_t *const info)
{
    vtss_state_t *vtss_state = vtss_inst_check_no_persist(inst);

    if (meta == NULL || info == NULL) {
        return VTSS_RC_ERROR;
    }

    // This function executes without locking the API semaphore.
    return VTSS_FUNC_FROM_STATE(vtss_state, packet.rx_hdr_decode, meta, hdr, info);
}

/*
 * Encode an injection header.
 */
vtss_rc vtss_packet_tx_hdr_encode(const vtss_inst_t                  inst,
                                  const vtss_packet_tx_info_t *const info,
                                        u8                    *const bin_hdr,
                                        u32                   *const bin_hdr_len)
{
    vtss_state_t *vtss_state = vtss_inst_check_no_persist(inst);

    if (info == NULL || bin_hdr_len == NULL) {
        return VTSS_RC_ERROR;
    }

    // This function executes without locking the API semaphore.
    // The only parameter it uses from the state variable (#inst) is
    // the port map, which is assumed to be constant once booted.
    return VTSS_FUNC_FROM_STATE(vtss_state, packet.tx_hdr_encode, info, bin_hdr, bin_hdr_len);
}

vtss_rc vtss_packet_tx_hdr_compile(const vtss_inst_t                  inst,
                                   const vtss_packet_tx_info_t *const info,
                                          vtss_packet_tx_ifh_t *const ifh)
{
    if (ifh != NULL) {
        ifh->length = sizeof(ifh->ifh);
        return vtss_packet_tx_hdr_encode(inst, info, (u8*) ifh->ifh, &ifh->length);
    }
    return VTSS_RC_ERROR;
}

/*
 * Initialize a packet_tx_info_t structure.
 */
vtss_rc vtss_packet_tx_info_init(const vtss_inst_t                  inst,
                                       vtss_packet_tx_info_t *const info)
{
    if (info == NULL) {
        return VTSS_RC_ERROR;
    }

    memset(info, 0, sizeof(*info));
    info->masquerade_port = VTSS_PORT_NO_NONE; // Default to not masquerading.
#if VTSS_ISDX_NONE != 0
    info->isdx            = VTSS_ISDX_NONE;    // Default to not injecting on an ISDX.
#endif
#if VTSS_VSI_NONE != 0
    info->vsi             = VTSS_VSI_NONE;     // Default to not injecting on a VSI.
#endif
#if defined(VTSS_FEATURE_AFI_SWC) && VTSS_AFI_ID_NONE != 0
    info->afi_id          = VTSS_AFI_ID_NONE;  // Default to not repeating the frame.
#endif
    return VTSS_RC_OK;
}

/* - NPI port ------------------------------------------------------ */

vtss_rc vtss_npi_conf_get(const vtss_inst_t inst, vtss_npi_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->packet.npi_conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_npi_conf_set(const vtss_inst_t inst, const vtss_npi_conf_t *const conf)
{
    vtss_state_t    *vtss_state;
    vtss_rc         rc;
    vtss_npi_conf_t conf_old;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, conf->enable ? conf->port_no : VTSS_PORT_NO_START)) == VTSS_RC_OK) {
        conf_old = vtss_state->packet.npi_conf;
        if ((rc = VTSS_FUNC_COLD(packet.npi_conf_set, conf)) == VTSS_RC_OK) {
            rc = vtss_update_masks(vtss_state, 1, 0, 0);    // Update src masks
            /* Update VLAN configuration for old and new NPI port */
            if (rc == VTSS_RC_OK && conf_old.enable) {
                rc = VTSS_FUNC_COLD(l2.vlan_port_conf_set, conf_old.port_no);
            }
            if (rc == VTSS_RC_OK && conf->enable) {
                rc = VTSS_FUNC_COLD(l2.vlan_port_conf_set, conf->port_no);
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

/* - TOD ns to ts count -------------------------------------------- */

vtss_rc vtss_packet_phy_cnt_to_ts_cnt(const vtss_inst_t  inst,
                                      const u32          phy_cnt,
                                      u64                *ts_cnt)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (rc == VTSS_RC_OK) {
            rc = VTSS_FUNC(packet.packet_phy_cnt_to_ts_cnt, phy_cnt, ts_cnt);
        }
    }
    VTSS_EXIT();
    return rc;
}

/* - TOD ns to ts count -------------------------------------------- */

vtss_rc vtss_packet_ns_to_ts_cnt(const vtss_inst_t  inst,
                                 const u32          ns,
                                 u64                *ts_cnt)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (rc == VTSS_RC_OK) {
            rc = VTSS_FUNC(packet.packet_ns_to_ts_cnt, ns, ts_cnt);
        }
    }
    VTSS_EXIT();
    return rc;
}

/* - PTP get timestamp --------------------------------------------- */

vtss_rc vtss_ptp_get_timestamp(const vtss_inst_t                   inst,
                               const u8 *const                     frm,
                               const vtss_packet_rx_info_t *const  rx_info,
                               vtss_packet_ptp_message_type_t      message_type,
                               vtss_packet_timestamp_props_t       ts_props,
                               u64                                 *rxTime,
                               BOOL                                *timestamp_ok)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (rc == VTSS_RC_OK) {
            rc = VTSS_FUNC(packet.ptp_get_timestamp, frm, rx_info, message_type, ts_props, rxTime, timestamp_ok);
        }
    }
    VTSS_EXIT();
    return rc;
}

/* - Packet mode --------------------------------------------------- */

vtss_rc vtss_packet_dma_conf_get(const vtss_inst_t             inst,
                                 vtss_packet_dma_conf_t        *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->packet.dma_conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_dma_conf_set(const vtss_inst_t             inst,
                                 const vtss_packet_dma_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(packet.dma_conf_set, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_packet_dma_offset(const vtss_inst_t             inst,
                               BOOL extraction,
                               u32 *offset)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(packet.dma_offset, extraction, offset);
    }
    VTSS_EXIT();
    return rc;
}

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_packet_inst_create(vtss_state_t *vtss_state)
{
    vtss_packet_rx_conf_t *rx_conf = &vtss_state->packet.rx_conf;

    rx_conf->reg.bpdu_cpu_only = 1;
    /* Enabling SFlow queue has side-effects on some platforms (JR-48), so by default we don't. */
    rx_conf->map.sflow_queue = VTSS_PACKET_RX_QUEUE_NONE;
    /* Learn-all frames should only be enabled on JR-stacking and JR-48 platforms. */
    rx_conf->map.lrn_all_queue = VTSS_PACKET_RX_QUEUE_NONE;
    /* Stack-queue frames should only be enabled on JR-stacking platforms. */
    rx_conf->map.stack_queue    = VTSS_PACKET_RX_QUEUE_NONE;
#if defined(VTSS_FEATURE_LAYER3)
    rx_conf->map.l3_uc_queue    = VTSS_PACKET_RX_QUEUE_NONE;
    rx_conf->map.l3_other_queue = VTSS_PACKET_RX_QUEUE_NONE;
#endif /* VTSS_FEATURE_LAYER3 */
    /* Enabling Queue 0 at default */
    rx_conf->queue[0].size =  8 * 1024;

    vtss_state->packet.npi_conf.port_no = VTSS_PORT_NO_NONE;

#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
    rx_conf->shaper_rate = VTSS_BITRATE_DISABLED;
#endif /* defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER) */

    return VTSS_RC_OK;
}

/* - Packet utilities ---------------------------------------------- */

/*
 * Convert a 64-bit mask consisting of logical port numbers to another 64-bit
 * mask consisting of physical port numbers.
 * The function fails if no bits are set, if a port is not in the port map,
 * if two ports are located on two different physical chips, or if more than
 * bit is set and a stack port is among them.
 *
 * On successful exit:
 *   #chip_port_mask is set to the physical port mask corresponding to the logical port mask we were called with.
 *   #chip_no        is set to the chip number for which #chip_port_mask applies.
 *   #stack_port_no  is set to the logical stack port number if #logical_port_mask points out a stack port, VTSS_PORT_NO_NONE if not.
 *   #port_cnt       is set to the number of bits set in #logical_port_mask.
 *   #port_no        is set to the last logical port number investigated in #logical_port_mask. Usually only useful when #port_cnt is exactly 1.
 */
vtss_rc vtss_cmn_logical_to_chip_port_mask(const vtss_state_t *const state,
                                                 u64                 logical_port_mask,
                                                 u64                 *chip_port_mask,
                                                 vtss_chip_no_t      *chip_no,
                                                 vtss_port_no_t      *stack_port_no,
                                                 u32                 *port_cnt,
                                                 vtss_port_no_t      *port_no)
{
    u32 i, w, p;

    /* Lint cannot see that state->port_count < VTSS_PORT_ARRAY_SIZE, so it thinks
     * that port_map[p] can happen to exceed the array size.
     */
    /*lint --e{506, 550, 661, 662} */

    if (!logical_port_mask) {
       VTSS_E("Empty port mask");
       return VTSS_RC_ERROR;
    }

    *chip_port_mask = 0;
    *chip_no        = 0xFFFFFFFFUL;
    *stack_port_no  = VTSS_PORT_NO_NONE;
    *port_cnt       = 0;

    for (i = 0; i < 64; i += 32) {
        w = (u32)(logical_port_mask >> i);

        while ((p = VTSS_OS_CTZ(w)) < 32) {
            w &= ~VTSS_BIT(p);
            p += i;

            if (p >= state->port_count) {
                VTSS_E("port = %u out of range (mask = 0x%" PRIx64 ")", p, logical_port_mask);
                return VTSS_RC_ERROR;
            }

            if (*chip_no == 0xFFFFFFFFUL) {
                *chip_no = state->port.map[p].chip_no;
            } else if (*chip_no != state->port.map[p].chip_no) {
                VTSS_E("Maps to two different devices (mask = 0x%" PRIx64 ")", logical_port_mask);
                return VTSS_RC_ERROR;
            }

            *chip_port_mask |= (1ULL << state->port.map[p].chip_port);
            *port_no = p;
            (*port_cnt)++;
        }
    }

    return VTSS_RC_OK;
}

/*
 * Get logical port number from chip number and physical port number.
 * If <chip_no, chip_port> is not in the port map, the function
 * returns VTSS_PORT_NO_NONE.
 */
vtss_port_no_t vtss_cmn_chip_to_logical_port(const vtss_state_t       *const state,
                                             const vtss_chip_no_t            chip_no,
                                             const vtss_phys_port_no_t       chip_port)
{
    vtss_port_no_t port_no;
    for (port_no = VTSS_PORT_NO_START; port_no < state->port_count; port_no++) {
        if (VTSS_CHIP_PORT_FROM_STATE(state, port_no) == chip_port && VTSS_CHIP_NO_FROM_STATE(state, port_no) == chip_no) {
            return port_no;
        }
    }
    return VTSS_PORT_NO_NONE;
}

/*
 * Update Packet Rx hints and tag_type.
 * The classified VID (info->tag.vid) must be set prior to
 * calling this function.
 * On exit, info->tag.tpid is updated and info->tag_type and info->hints may
 * be updated.
 * This function doesn't support stack ports or internal ports, because
 * it's the original ingress port's properties that are required to be
 * able to set hints correctly.
 */
vtss_rc vtss_cmn_packet_hints_update(const vtss_state_t          *const state,
                                     const vtss_trace_group_t           trc_grp,
                                     const vtss_etype_t                 etype,
                                           vtss_packet_rx_info_t *const info)
{
    const vtss_vlan_port_conf_t *vlan_port_conf = &state->l2.vlan_port_conf[info->port_no];

    if (info->port_no == VTSS_PORT_NO_NONE) {
        VTSS_EG(trc_grp, "Internal error");
        return VTSS_RC_ERROR;
    }

    info->tag.tpid = etype;

    switch (vlan_port_conf->port_type) {
    case VTSS_VLAN_PORT_TYPE_C:
        if (etype == VTSS_ETYPE_TAG_C) {
            info->tag_type = VTSS_TAG_TYPE_C_TAGGED;
        } else if (etype == VTSS_ETYPE_TAG_S || etype == state->l2.vlan_conf.s_etype) {
            info->hints |= VTSS_PACKET_RX_HINTS_VLAN_TAG_MISMATCH;
        }
        break;

    case VTSS_VLAN_PORT_TYPE_S:
        if (etype == VTSS_ETYPE_TAG_S) {
            info->tag_type = VTSS_TAG_TYPE_S_TAGGED;
        } else if (etype == VTSS_ETYPE_TAG_C || etype == state->l2.vlan_conf.s_etype) {
            info->hints |= VTSS_PACKET_RX_HINTS_VLAN_TAG_MISMATCH;
        }
        break;

    case VTSS_VLAN_PORT_TYPE_S_CUSTOM:
        if (etype == state->l2.vlan_conf.s_etype) {
            info->tag_type = VTSS_TAG_TYPE_S_CUSTOM_TAGGED;
        } else if (etype == VTSS_ETYPE_TAG_C || etype == VTSS_ETYPE_TAG_S) {
            info->hints |= VTSS_PACKET_RX_HINTS_VLAN_TAG_MISMATCH;
        }
        break;

    default:
        break;
    }

    if ((info->tag_type == VTSS_TAG_TYPE_UNTAGGED && vlan_port_conf->frame_type == VTSS_VLAN_FRAME_TAGGED) ||
        (info->tag_type != VTSS_TAG_TYPE_UNTAGGED && vlan_port_conf->frame_type == VTSS_VLAN_FRAME_UNTAGGED)) {
        info->hints |= VTSS_PACKET_RX_HINTS_VLAN_FRAME_MISMATCH;
    }

    if (!VTSS_PORT_BF_GET(state->l2.vlan_table[info->tag.vid].member, info->port_no)) {
        info->hints |= VTSS_PACKET_RX_HINTS_VID_MISMATCH;
    }

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static const char *vtss_packet_reg_txt(vtss_packet_reg_type_t type)
{
    return (type == VTSS_PACKET_REG_NORMAL ? "N" :
            type == VTSS_PACKET_REG_FORWARD ? "F" :
#if defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
            type == VTSS_PACKET_REG_DISCARD ? "D" :
            type == VTSS_PACKET_REG_CPU_COPY ? "C" :
#endif /* VTSS_FEATURE_PACKET_PORT_REG_DISCARD */
            type == VTSS_PACKET_REG_CPU_ONLY ? "R" : "?");
}

void vtss_packet_debug_print(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    u32                   i;
    char                  buf[16];
    vtss_packet_rx_conf_t *conf = &vtss_state->packet.rx_conf;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_PACKET))
        return;

    vtss_debug_print_header(pr, "Registrations");
    {
        vtss_port_no_t             port_no;
        vtss_packet_rx_port_conf_t *port_conf;
        BOOL                       header = 1;

        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (!info->port_list[port_no])
                continue;
            if (header) {
                header = 0;
                pr("Port  BPDU              GARP              ");
#if defined(VTSS_ARCH_SERVAL)
                pr("IPMC  IGMP  MLD");
#endif /* VTSS_ARCH_SERVAL */
                pr("\n");
            }
            pr("%-6u", port_no);
            port_conf = &vtss_state->packet.rx_port_conf[port_no];
            for (i = 0; i < 32; i++) {
                pr("%s%s",
                   vtss_packet_reg_txt(i < 16 ? port_conf->bpdu_reg[i] : port_conf->garp_reg[i - 16]),
                   i % 16 == 15 ? "  " : "");
            }
#if defined(VTSS_ARCH_SERVAL)
            pr("%-6s%-6s%s",
               vtss_packet_reg_txt(port_conf->ipmc_ctrl_reg),
               vtss_packet_reg_txt(port_conf->igmp_reg),
               vtss_packet_reg_txt(port_conf->mld_reg));
#endif /* VTSS_ARCH_SERVAL */
            pr("\n");
        }
        if (!header)
            pr("\n");
    }

    vtss_debug_print_value(pr, "BPDU", conf->reg.bpdu_cpu_only);
    for (i = 0; i < 16; i++) {
        sprintf(buf, "GARP_%u", i);
        vtss_debug_print_value(pr, buf, conf->reg.garp_cpu_only[i]);
    }
    vtss_debug_print_value(pr, "IPMC", conf->reg.ipmc_ctrl_cpu_copy);
    vtss_debug_print_value(pr, "IGMP", conf->reg.igmp_cpu_only);
    vtss_debug_print_value(pr, "MLD",  conf->reg.mld_cpu_only);
    pr("\n");

    vtss_debug_print_header(pr, "Queue Mappings");
    vtss_debug_print_value(pr, "BPDU",     conf->map.bpdu_queue);
    vtss_debug_print_value(pr, "GARP",     conf->map.garp_queue);
    vtss_debug_print_value(pr, "LEARN",    conf->map.learn_queue);
    vtss_debug_print_value(pr, "IGMP",     conf->map.igmp_queue);
    vtss_debug_print_value(pr, "IPMC",     conf->map.ipmc_ctrl_queue);
    vtss_debug_print_value(pr, "MAC_VID",  conf->map.mac_vid_queue);
    vtss_debug_print_value(pr, "STACK",    conf->map.stack_queue);
    vtss_debug_print_value(pr, "SFLOW",    conf->map.sflow_queue);
    vtss_debug_print_value(pr, "LRN_ALL",  conf->map.lrn_all_queue);
#if defined(VTSS_FEATURE_LAYER3)
    vtss_debug_print_value(pr, "L3_UC",    conf->map.l3_uc_queue);
    vtss_debug_print_value(pr, "L3_OTHER", conf->map.l3_other_queue);
#endif /* VTSS_FEATURE_LAYER3 */

    pr("\n");

    vtss_debug_print_header(pr, "NPI");
    vtss_debug_print_value(pr, "Enabled", vtss_state->packet.npi_conf.enable);
    if (vtss_state->packet.npi_conf.port_no != VTSS_PORT_NO_NONE) {
        vtss_packet_rx_conf_t *rx_conf = &vtss_state->packet.rx_conf;

        vtss_debug_print_value(pr, "NPI_PORT", vtss_state->packet.npi_conf.port_no);
        for (i = 0; i < vtss_state->packet.rx_queue_count; i++) {
            sprintf(buf, "REDIR:CPUQ_%u", i);
            vtss_debug_print_value(pr, buf, rx_conf->queue[i].npi.enable);
        }
    }
    pr("\n");

#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
    vtss_debug_print_header(pr, "CPU Shaper");
    vtss_debug_print_value(pr, "Enabled", !(conf->shaper_rate == VTSS_BITRATE_DISABLED));
    if (conf->shaper_rate != VTSS_BITRATE_DISABLED) {
        vtss_debug_print_value(pr, "Rate", conf->shaper_rate);
    }
    pr("\n");
#endif /* defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER) */
}

#endif /* VTSS_FEATURE_PACKET */
