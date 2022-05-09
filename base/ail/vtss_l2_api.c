// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L2
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"

#if defined(VTSS_FEATURE_LAYER2)

void vtss_port_mask_clear(vtss_port_mask_t *pmask)
{
    VTSS_MEMSET(pmask, 0, sizeof(*pmask));
}

void vtss_port_mask_get(vtss_state_t *vtss_state,
                        const BOOL member[],
                        vtss_port_mask_t *pmask)
{
    vtss_port_no_t port_no;
    u32            port;

    vtss_port_mask_clear(pmask);
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (member[port_no]) {
            port = VTSS_CHIP_PORT(port_no);
            pmask->m[port / 32] |= (1 << (port % 32));
        }
    }
}

void vtss_port_mask_port(vtss_state_t *vtss_state,
                         vtss_port_no_t port_no,
                         vtss_port_mask_t *pmask)
{
    u32 port = VTSS_CHIP_PORT(port_no);

    vtss_port_mask_clear(pmask);
    pmask->m[port / 32] |= (1 << (port % 32));
}

/* Determine port membership considering aggregations etc. */
static void vtss_pgid_members_get(vtss_state_t *vtss_state,
                                  u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_pgid_entry_t *pgid_entry;
    vtss_port_eps_t   *protect;
    vtss_port_no_t    port_no, port;
    vtss_aggr_no_t    aggr_no;
    vtss_dgroup_no_t  dgroup_no;

    /* Store raw port members */
    pgid_entry = &vtss_state->l2.pgid_table[pgid];
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)
        member[port_no] = (port_no < vtss_state->port_count ? pgid_entry->member[port_no] : 0);

    /* Reserved entries are used direcly (e.g. GLAG masks) */
    if (pgid_entry->resv)
        return;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        /* Check if 1+1 protected port is member */
        protect = &vtss_state->l2.port_protect[port_no];
        if ((port = protect->conf.port_no) != VTSS_PORT_NO_NONE &&
            protect->conf.type == VTSS_EPS_PORT_1_PLUS_1) {
            if (member[port])    /* Include working port if protection port is member */
                member[port_no] = 1;
            if (member[port_no]) /* Include protection port if working port is member */
                member[port] = 1;
        }

        /* Check if aggregated ports or destination group members are port members */
        aggr_no = vtss_state->l2.port_aggr_no[port_no];
        dgroup_no = vtss_state->l2.dgroup_port_conf[port_no].dgroup_no;
        for (port = VTSS_PORT_NO_START; port < vtss_state->port_count; port++) {
            if (member[port] &&
                ((aggr_no != VTSS_AGGR_NO_NONE && vtss_state->l2.port_aggr_no[port] == aggr_no) ||
                 vtss_state->l2.dgroup_port_conf[port].dgroup_no == dgroup_no)) {
                member[port_no] = 1;
            }
        }
    }
}

/* - MAC address table --------------------------------------------- */

void vtss_mach_macl_get(const vtss_vid_mac_t *vid_mac, u32 *mach, u32 *macl)
{
    *mach = ((vid_mac->vid<<16) | (vid_mac->mac.addr[0]<<8) | vid_mac->mac.addr[1]);
    *macl = ((vid_mac->mac.addr[2]<<24) | (vid_mac->mac.addr[3]<<16) |
             (vid_mac->mac.addr[4]<<8) | vid_mac->mac.addr[5]);
}

void vtss_mach_macl_set(vtss_vid_mac_t *vid_mac, u32 mach, u32 macl)
{
    vid_mac->vid = ((mach >> 16) & 0xfff);
    vid_mac->mac.addr[0] = ((mach >> 8) & 0xff);
    vid_mac->mac.addr[1] = ((mach >> 0) & 0xff);
    vid_mac->mac.addr[2] = ((macl >> 24) & 0xff);
    vid_mac->mac.addr[3] = ((macl >> 16) & 0xff);
    vid_mac->mac.addr[4] = ((macl >> 8) & 0xff);
    vid_mac->mac.addr[5] = ((macl >> 0) & 0xff);
}

static vtss_mac_entry_t *vtss_mac_entry_get(vtss_state_t *vtss_state,
                                            u32 mach, u32 macl, BOOL next)
{
    u32              first,last,mid;
    vtss_mac_entry_t *cur,*old;

    /* Check if table is empty */
    if (vtss_state->l2.mac_ptr_count == 0)
        return NULL;

    /* Locate page using binary search */
    for (first = 0, last = vtss_state->l2.mac_ptr_count-1; first != last; ) {
        mid = (first + last)/2;
        cur = vtss_state->l2.mac_list_ptr[mid];
        if (cur->mach > mach || (cur->mach == mach && cur->macl >= macl)) {
            /* Entry greater or equal, search lower half */
            last = mid;
        } else {
            /* Entry is smaller, search upper half */
            first = mid + 1;
        }
    }

    cur = vtss_state->l2.mac_list_ptr[first];
    /* Go back one page if entry greater */
    if (first != 0 && (cur->mach > mach || (cur->mach == mach && cur->macl > macl)))
        cur = vtss_state->l2.mac_list_ptr[first-1];

    /* Look for greater entry using linear search */
    for (old = NULL; cur != NULL; old = cur, cur = cur->next)
        if (cur->mach > mach || (cur->mach == mach && cur->macl > macl))
            break;

    return (next ? cur : old);
}

/* Update MAC table page pointers */
static void vtss_mac_pages_update(vtss_state_t *vtss_state)
{
    u32              i,count;
    vtss_mac_entry_t *cur;

    for (i = 0, cur = vtss_state->l2.mac_list_used; i < VTSS_MAC_PTR_SIZE && cur!=NULL ; i++) {
        vtss_state->l2.mac_list_ptr[i] = cur;

        /* Move one page forward */
        for (count = 0; count != VTSS_MAC_PAGE_SIZE && cur != NULL ; cur = cur->next, count++)
            ;
    }
    vtss_state->l2.mac_ptr_count = i;
}

/* Add MAC table entry */
static vtss_mac_entry_t *vtss_mac_entry_add(vtss_state_t *vtss_state,
                                            const vtss_mac_user_t user,
                                            const vtss_vid_mac_t *vid_mac)
{
    u32              mach, macl;
    vtss_mac_entry_t *cur, *tmp;

    /* Calculate MACH and MACL */
    vtss_mach_macl_get(vid_mac, &mach, &macl);

    /* Look for previous or existing entry in used list */
    if ((tmp = vtss_mac_entry_get(vtss_state, mach, macl, 0)) != NULL &&
        tmp->mach == mach && tmp->macl == macl)
        return (tmp->user == user ? tmp : NULL);

    /* Allocate entry from free list */
    if ((cur = vtss_state->l2.mac_list_free) == NULL) {
        VTSS_E("no free MAC entries");
        return NULL;
    }
    vtss_state->l2.mac_list_free = cur->next;
    cur->mach = mach;
    cur->macl = macl;
    cur->user = user;

    if (tmp == NULL) {
        /* Insert first */
        cur->next = vtss_state->l2.mac_list_used;
        vtss_state->l2.mac_list_used = cur;
    } else {
        /* Insert after previous entry */
        cur->next = tmp->next;
        tmp->next = cur;
    }
    vtss_state->l2.mac_table_count++;

    /* Update page pointers */
    vtss_mac_pages_update(vtss_state);

    return cur;
}

/* Delete MAC table entry */
static vtss_rc vtss_mac_entry_del(vtss_state_t *vtss_state,
                                  const vtss_mac_user_t user, const vtss_vid_mac_t *vid_mac)
{
    u32              mach, macl;
    vtss_mac_entry_t *cur, *old;

    /* Calculate MACH and MACL */
    vtss_mach_macl_get(vid_mac, &mach, &macl);

    /* Look for entry */
    for (old = NULL, cur = vtss_state->l2.mac_list_used; cur != NULL; old = cur, cur = cur->next) {
        if (cur->mach == mach && cur->macl == macl) {
            if (cur->user != user) {
                /* Deleting entries added by other users is not allowed */
                return VTSS_RC_ERROR;
            }

            /* Remove from used list */
            if (old == NULL)
                vtss_state->l2.mac_list_used = cur->next;
            else
                old->next = cur->next;

            /* Insert in free list */
            cur->next = vtss_state->l2.mac_list_free;
            vtss_state->l2.mac_list_free = cur;
            vtss_state->l2.mac_table_count--;

            /* Update page pointers */
            vtss_mac_pages_update(vtss_state);
            break;
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_mac_entry_update(vtss_state_t *vtss_state, vtss_mac_entry_t *cur, u32 pgid)
{
    vtss_mac_table_entry_t entry;

    VTSS_MEMSET(&entry, 0, sizeof(entry));
    vtss_mach_macl_set(&entry.vid_mac, cur->mach, cur->macl);
    entry.locked = 1;
    entry.aged = 0;
    entry.copy_to_cpu = cur->cpu_copy;
    entry.copy_to_cpu_smac = cur->cpu_copy_smac;
    return VTSS_FUNC(l2.mac_table_add, &entry, pgid);
}

static BOOL vtss_ipmc_mac(vtss_state_t *vtss_state, const vtss_vid_mac_t *vid_mac)
{
    /* The JR2 architecture treats IPMC entries like other entries */
    return (vtss_state->arch == VTSS_ARCH_JR2 || vtss_state->arch == VTSS_ARCH_ANT ? 0 :
            (VTSS_MAC_IPV4_MC(vid_mac->mac.addr) || VTSS_MAC_IPV6_MC(vid_mac->mac.addr)));
}

/* Update IPv4 and IPv6 multicast entries on aggregation changes */
static vtss_rc vtss_mac_table_update(vtss_state_t *vtss_state)
{
    u32               pgid = VTSS_PGID_NONE;
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[pgid];
    vtss_mac_entry_t  *cur;
    vtss_port_no_t    port_no;
    vtss_vid_mac_t    vid_mac;

    for (cur = vtss_state->l2.mac_list_used; cur != NULL; cur = cur->next) {
        vtss_mach_macl_set(&vid_mac, cur->mach, cur->macl);
        if (!vtss_ipmc_mac(vtss_state, &vid_mac))
            continue;
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            pgid_entry->member[port_no] = VTSS_PORT_BF_GET(cur->member, port_no);
        vtss_pgid_members_get(vtss_state, pgid, pgid_entry->member);
        (void)vtss_mac_entry_update(vtss_state, cur, pgid);
    }

    return VTSS_RC_OK;
}

/* Write PGID member to chip */
static vtss_rc vtss_pgid_table_write(vtss_state_t *vtss_state, u32 pgid)
{
    BOOL member[VTSS_PORT_ARRAY_SIZE];

    VTSS_N("pgid: %u", pgid);

    /* Ignore unused entries */
    if (vtss_state->l2.pgid_table[pgid].references == 0)
        return VTSS_RC_OK;

    /* Get port members */
    vtss_pgid_members_get(vtss_state, pgid, member);

    /* Update PGID table */
    return VTSS_FUNC(l2.pgid_table_write, pgid, member);
}

/* Allocate PGID */
static vtss_rc vtss_pgid_alloc(vtss_state_t *vtss_state,
                               u32 *new, const BOOL member[VTSS_PORT_ARRAY_SIZE],
                               BOOL cpu_copy, vtss_packet_rx_queue_t cpu_queue, BOOL do_alloc)
{
    u32               pgid, pgid_free = *new;
    BOOL              pgid_found = 0;
    vtss_pgid_entry_t *pgid_entry;
    vtss_port_no_t    port_no;

    VTSS_D("enter");

    /* Search for matching or unused entry in PGID table */
    for (pgid = 0; pgid < vtss_state->l2.pgid_count; pgid++)  {
        pgid_entry = &vtss_state->l2.pgid_table[pgid];
        if (pgid_entry->resv) /* Skip reserved entries */
            continue;

        if (pgid_entry->references == 0) {
            /* Check if the first unused entry is found or the pgid can be reused */
            if (pgid_free == VTSS_PGID_NONE || pgid == *new) {
                pgid_found = 1;
                pgid_free = pgid;
            }
        } else {
            /* Check if an existing entry matches */
            for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
                if (member[port_no] != pgid_entry->member[port_no])
                    break;
            if (port_no == vtss_state->port_count &&
                pgid_entry->cpu_copy == cpu_copy && pgid_entry->cpu_queue == cpu_queue) {
                VTSS_D("reusing pgid: %u", pgid);
                if (do_alloc) {
                    *new = pgid;
                    pgid_entry->references++;
                }
                return VTSS_RC_OK;
            }
        }
    }

    /* No pgid found */
    if (pgid_found == 0) {
        VTSS_E("no more pgids");
        return VTSS_RC_ERROR;
    }

    VTSS_D("using pgid: %u", pgid_free);
    if (!do_alloc) {
        return VTSS_RC_OK;
    }
    *new = pgid_free;
    pgid_entry = &vtss_state->l2.pgid_table[pgid_free];
    pgid_entry->references = 1;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
        pgid_entry->member[port_no] = member[port_no];
    pgid_entry->cpu_copy = cpu_copy;
    pgid_entry->cpu_queue = cpu_queue;
    return vtss_pgid_table_write(vtss_state, pgid_free);
}

/* Free PGID */
static vtss_rc vtss_pgid_free(vtss_state_t *vtss_state, u32 pgid)
{
    vtss_pgid_entry_t *pgid_entry;

    VTSS_D("pgid: %u", pgid);

    /* Ignore IPv4/IPv6 MC free */
    if (pgid == VTSS_PGID_NONE)
        return VTSS_RC_OK;

    if (pgid > vtss_state->l2.pgid_count) {
        VTSS_E("illegal pgid: %u", pgid);
        return VTSS_RC_ERROR;
    }

    /* Do not free reserved PGIDs */
    pgid_entry = &vtss_state->l2.pgid_table[pgid];
    if (pgid_entry->resv)
        return VTSS_RC_OK;

    /* Check if pgid already free */
    if (pgid_entry->references == 0) {
        VTSS_E("pgid: %u already free", pgid);
        return VTSS_RC_ERROR;
    }

    pgid_entry->references--;
    return VTSS_RC_OK;
}

/* Determine logical port */
static vtss_port_no_t vtss_aggr_port(vtss_state_t *vtss_state, vtss_port_no_t port)
{
    vtss_port_no_t port_no;
    vtss_aggr_no_t aggr_no;
    vtss_port_no_t lport_no = port; /* Use port itself by default */

    if ((aggr_no = vtss_state->l2.port_aggr_no[port]) != VTSS_AGGR_NO_NONE) {
        /* Aggregated, use first operational port in aggregation */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            if (vtss_state->l2.port_state[port_no] &&
                vtss_state->l2.port_aggr_no[port_no] == aggr_no) {
                lport_no = port_no;
                break;
            }
    }
    return lport_no;
}

/* Update source, destination and aggregation masks */
vtss_rc vtss_update_masks(vtss_state_t *vtss_state,
                          BOOL src_update, BOOL dest_update, BOOL aggr_update)
{
    vtss_rc             rc;
    vtss_port_no_t      i_port, e_port, port_p;
    vtss_aggr_no_t      aggr_no;
    BOOL                member[VTSS_PORT_ARRAY_SIZE], learn[VTSS_PORT_ARRAY_SIZE], chg, *fwd;
    BOOL                rx_forward[VTSS_PORT_ARRAY_SIZE], tx_forward[VTSS_PORT_ARRAY_SIZE];
    u32                 pgid;
    u32                 port_count = vtss_state->port_count;
    u32                 ac, aggr_count[VTSS_PORT_ARRAY_SIZE];
    u32                 aggr_index[VTSS_PORT_ARRAY_SIZE], n;
    vtss_port_eps_t     *protect;
    vtss_chip_no_t      chip_no = vtss_state->chip_no;
    vtss_port_no_t      npi_port = VTSS_PORT_NO_NONE;

    VTSS_N("enter");

    if (vtss_state->warm_start_cur) {
        VTSS_D("warm start, returning");
        return VTSS_RC_OK;
    }
    VTSS_MEMSET(rx_forward, 0, sizeof(rx_forward));
    VTSS_MEMSET(tx_forward, 0, sizeof(tx_forward));

    /* Determine learning, Rx and Tx forwarding state per port */
    for (i_port = VTSS_PORT_NO_START; i_port < port_count; i_port++) {
        protect = &vtss_state->l2.port_protect[i_port];

        /* Learning */
        learn[i_port] = (vtss_state->l2.port_state[i_port] &&
                         vtss_state->l2.stp_state[i_port] != VTSS_STP_STATE_DISCARDING &&
                         VTSS_PORT_RX_FORWARDING(vtss_state->port.forward[i_port]) &&
                         vtss_state->l2.auth_state[i_port] == VTSS_AUTH_STATE_BOTH &&
                         (protect->conf.port_no == VTSS_PORT_NO_NONE ||
                          protect->conf.type == VTSS_EPS_PORT_1_FOR_1 ||
                          protect->selector == VTSS_EPS_SELECTOR_WORKING));

        /* Rx forwarding */
        rx_forward[i_port] = (learn[i_port] &&
                              vtss_state->l2.stp_state[i_port] == VTSS_STP_STATE_FORWARDING);

        /* Tx forwarding */
        tx_forward[i_port] = (vtss_state->l2.port_state[i_port] &&
                              vtss_state->l2.stp_state[i_port] == VTSS_STP_STATE_FORWARDING &&
                              VTSS_PORT_TX_FORWARDING(vtss_state->port.forward[i_port]) &&
                              vtss_state->l2.auth_state[i_port] != VTSS_AUTH_STATE_NONE);

        /* Store Tx forward information */
        if (vtss_state->l2.tx_forward[i_port] != tx_forward[i_port]) {
            vtss_state->l2.tx_forward[i_port] = tx_forward[i_port];
            vtss_state->l2.vlan_filter_changed = TRUE;
        }
    }

    /* Determine state for protection ports */
    for (i_port = VTSS_PORT_NO_START; i_port < port_count; i_port++) {
        protect = &vtss_state->l2.port_protect[i_port];
        port_p = protect->conf.port_no;

        /* If 1+1 working port is active, discard on Rx */
        if (port_p != VTSS_PORT_NO_NONE &&
            protect->conf.type == VTSS_EPS_PORT_1_PLUS_1 &&
            protect->selector == VTSS_EPS_SELECTOR_WORKING) {
            learn[port_p] = 0;
            rx_forward[port_p] = 0;
        }
    }

    /* Update learn mask */
    if (src_update && (rc = VTSS_FUNC(l2.learn_state_set, learn)) != VTSS_RC_OK)
        return rc;

#if defined(VTSS_FEATURE_PACKET)
    if (vtss_state->packet.npi_conf.enable) {
        npi_port = vtss_state->packet.npi_conf.port_no;
    }
#endif

    /* Update source masks */
    for (i_port = VTSS_PORT_NO_START; src_update && i_port < port_count; i_port++) {
        /* Exclude all ports by default */
        VTSS_MEMSET(member, 0, sizeof(member));

        /* Store Rx forward information */
        if (vtss_state->l2.rx_forward[i_port] != rx_forward[i_port]) {
            vtss_state->l2.rx_forward[i_port] = rx_forward[i_port];
            vtss_state->l2.vlan_filter_changed = TRUE;
        }
        vtss_state->l2.learn[i_port] = learn[i_port];

        /* Special case - NPI port */
        if (i_port == npi_port) {
            // Allow all forwarding ports but myself
            VTSS_MEMCPY(member, tx_forward, sizeof(member));
            member[i_port] = FALSE;
        } else if (rx_forward[i_port]) {
            /* Check if ingress forwarding is allowed */
            vtss_pvlan_no_t     pvlan_no;

            /* Include members of the same PVLAN */
            for (pvlan_no = VTSS_PVLAN_NO_START; pvlan_no < VTSS_PVLAN_NO_END; pvlan_no++) {
                if (vtss_state->l2.pvlan_table[pvlan_no].member[i_port] == 0)
                    continue;
                /* The ingress port is a member of this PVLAN */
                for (e_port = VTSS_PORT_NO_START; e_port < port_count; e_port++)
                    if (vtss_state->l2.pvlan_table[pvlan_no].member[e_port])
                        member[e_port] = 1; /* Egress port also member */
            }

            /* Exclude protection port if it exists */
            if ((port_p = vtss_state->l2.port_protect[i_port].conf.port_no) != VTSS_PORT_NO_NONE)
                member[port_p] = 0;

            member[i_port] = 0;
            aggr_no = vtss_state->l2.port_aggr_no[i_port];
            for (e_port = VTSS_PORT_NO_START; e_port < port_count; e_port++) {
                /* Exclude members of the same aggregation */
                if (aggr_no != VTSS_AGGR_NO_NONE &&
                    vtss_state->l2.port_aggr_no[e_port] == aggr_no)
                    member[e_port] = 0;

                /* Exclude working port if it exists */
                if (vtss_state->l2.port_protect[e_port].conf.port_no == i_port)
                    member[e_port] = 0;
                VTSS_N("i_port: %u %sforwarding to e_port %u",
                       i_port, member[e_port] ? "" : "NOT ", e_port);

                /* Exclude ports, which are not egress forwarding */
                if (!VTSS_PORT_TX_FORWARDING(vtss_state->port.forward[e_port]))
                    member[e_port] = 0;

                /* Exclude ports not allowed by assymmetric PVLANs */
                if (!vtss_state->l2.apvlan_table[i_port][e_port])
                    member[e_port] = 0;
            }
        }
        if ((rc = VTSS_FUNC(l2.src_table_write, i_port, member)) != VTSS_RC_OK)
            return rc;
    } /* src_update */

    /* Update PGID table (destination masks) */
    if (dest_update) {
        for (pgid = 0; pgid < vtss_state->l2.pgid_count; pgid++) {
            VTSS_RC(vtss_pgid_table_write(vtss_state, pgid));
        }
        /* Update destination masks encoded in MAC address table */
        VTSS_RC(vtss_mac_table_update(vtss_state));
    } /* dest_update */

    /* Update aggregation masks */
    if (aggr_update) {

        /* Count number of operational ports and index of each port */
        for (i_port = VTSS_PORT_NO_START; i_port < port_count; i_port++) {
            aggr_count[i_port] = 0;
            aggr_index[i_port] = 0;

            /* If port is not forwarding, continue */
            if (!tx_forward[i_port])
                continue;

            aggr_no = vtss_state->l2.port_aggr_no[i_port];
            VTSS_D("port_no: %u, aggr_no: %u is forwarding", i_port, aggr_no);

            if (aggr_no == VTSS_AGGR_NO_NONE) {
                /* Not aggregated */
                aggr_count[i_port]++;
                continue;
            }
            for (e_port = VTSS_PORT_NO_START; e_port < port_count; e_port++) {
                if (tx_forward[e_port] && vtss_state->l2.port_aggr_no[e_port] == aggr_no) {
                    /* Port is forwarding and member of the same aggregation */
                    aggr_count[i_port]++;
                    if (e_port < i_port && i_port < VTSS_PORT_ARRAY_SIZE)
                        aggr_index[i_port]++;
                }
            }
        }

        for (ac = 0; ac < vtss_state->l2.ac_count; ac++) {
            /* Include one forwarding port from each aggregation */
            chg = 0;
            for (i_port = VTSS_PORT_NO_START; i_port < port_count; i_port++) {
                n = (aggr_index[i_port] + ac);
                member[i_port] = (aggr_count[i_port] != 0 && (n % aggr_count[i_port]) == 0);

                if (ac == 0) {
                    /* Store Tx forward information for the first aggregation code */
                    fwd = &vtss_state->l2.tx_forward_aggr[i_port];
                    if (*fwd != member[i_port]) {
                        *fwd = member[i_port];
                        chg = 1;
                    }
                }
            }
            /* Write to aggregation table */
            if ((rc = VTSS_FUNC(l2.aggr_table_write, ac, member)) != VTSS_RC_OK)
                return rc;

            /* Update IS2 if first aggregation mask changed */
            if (chg) {
#if defined(VTSS_FEATURE_VCAP)
                VTSS_RC(vtss_vcap_is2_update(vtss_state));
#endif
            }
        }

        /* Update port map table on aggregation changes */
        for (i_port = VTSS_PORT_NO_START; i_port < port_count; i_port++) {
            if ((rc = VTSS_FUNC(l2.pmap_table_write, i_port, vtss_aggr_port(vtss_state, i_port))) != VTSS_RC_OK)
                return rc;
        }
    } /* aggr_update */

    /* Restore chip number in case we were called from a port specific function,
       which had selected the chip number based on the port map. */
    VTSS_SELECT_CHIP(chip_no);

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
typedef struct {
    u32 oui;
    u32 idx;
} vtss_oui_idx_t;

static void vtss_mac_oui_idx_get(const vtss_mac_t *mac, vtss_oui_idx_t *oi)
{
    u32 i;

    VTSS_MEMSET(oi, 0, sizeof(*oi));
    for (i = 0; i < 3; i++) {
        oi->oui = ((oi->oui << 8) + mac->addr[i]);
        oi->idx = ((oi->idx << 8) + mac->addr[i + 3]);
    }
}

static vtss_rc vtss_mac_index_get(vtss_state_t *vtss_state,
                                  vtss_mac_table_entry_t *entry, u32 *pgid, BOOL next)
{
    vtss_mac_index_table_t *t = &vtss_state->l2.mac_index_table;
    vtss_vid_mac_t         *vid_mac = &entry->vid_mac;
    vtss_mac_vlan_entry_t  *e;
    vtss_oui_idx_t         oi;
    u32                    i, j, k, m, n;

    vtss_mac_oui_idx_get(&vid_mac->mac, &oi);
    if (next) {
        // Get next entry
        for (i = 0; i < t->cnt; i++) {
            j = t->vidx[i];
            e = &t->e[j];
            if (e->vid < vid_mac->vid) {
                // Smaller VID, no match
                continue;
            } else if (e->vid > vid_mac->vid) {
                // Greater VID, search for smallest address
                k = 0;
            } else if (t->oui < oi.oui) {
                // Same VID, smaller OUI, no match
                continue;
            } else if (t->oui > oi.oui) {
                // Same VID, greater OUI, search for smallest address
                k = 0;
            } else {
                // Same VID and OUI, search for next address
                k = (oi.idx + 1);
            }

            // Find next byte, then bit indicating a valid address
            n = (k % 8);
            m = (1 << n);
            while (k < VTSS_MAC_INDEX_CNT) {
                if (m && e->valid[k / 8] < m) {
                    // Next byte
                    k += (8 - n);
                    n = 0;
                    m = 1;
                } else if (VTSS_BF_GET(e->valid, k)) {
                    vid_mac->vid = e->vid;
                    for (i = 0; i < 3; i++) {
                        n = (16 - i * 8);
                        vid_mac->mac.addr[i] = ((t->oui >> n) & 0xff);
                        vid_mac->mac.addr[i + 3] = ((k >> n) & 0xff);
                    }
                    t->idx_get = (j * VTSS_MAC_INDEX_VID_CNT + k);
                    entry->index_table = 1;
                    return VTSS_FUNC(l2.mac_table_get, entry, pgid);
                } else {
                    // Next bit
                    m = 0;
                    k++;
                }
            }
        }
    } else if (oi.oui == t->oui && oi.idx < VTSS_MAC_INDEX_CNT) {
        // Get specific entry
        for (i = 0; i < t->cnt; i++) {
            j = t->vidx[i];
            e = &t->e[j];
            if (e->vid == vid_mac->vid) {
                if (VTSS_BF_GET(e->valid, oi.idx)) {
                    t->idx_get = (j * VTSS_MAC_INDEX_VID_CNT + oi.idx);
                    entry->index_table = 1;
                    return VTSS_FUNC(l2.mac_table_get, entry, pgid);
                }
            }
        }
    }
    return VTSS_RC_ERROR;
}

static vtss_rc vtss_mac_index_update(vtss_state_t *vtss_state)
{
    vtss_mac_index_table_t *t = &vtss_state->l2.mac_index_table;
    u8                     i, j, idx = 0;
    vtss_vid_t             vid, vid_min = 0, vid_max;

    // Build sorted list of VIDs for get-next
    for (i = 0; i < VTSS_MAC_INDEX_VID_CNT; i++) {
        vid_max = VTSS_VIDS;
        for (j = 0; j < VTSS_MAC_INDEX_VID_CNT; j++) {
            vid = t->e[j].vid;
            if (vid > vid_min && vid < vid_max) {
                idx = j;
                vid_max = vid;
            }
        }
        if (vid_max == VTSS_VIDS) {
            break;
        }
        vid_min = vid_max;
        t->vidx[i] = idx;
    }
    t->cnt = i;
    return VTSS_FUNC_0(l2.mac_index_update);
}

static vtss_rc vtss_mac_index_add(vtss_state_t *vtss_state,
                                  const vtss_mac_table_entry_t *const entry)
{
    vtss_mac_index_table_t *t = &vtss_state->l2.mac_index_table;
    vtss_mac_vlan_entry_t  *e;
    vtss_vid_t             vid = entry->vid_mac.vid;
    vtss_oui_idx_t         oi;
    u8                     i, i_free = VTSS_MAC_INDEX_VID_CNT;

    if (vid == 0) {
        VTSS_E("vid must be non-zero");
        return VTSS_RC_ERROR;
    }
    vtss_mac_oui_idx_get(&entry->vid_mac.mac, &oi);
    if (t->cnt && oi.oui != t->oui) {
        VTSS_E("new OUI 0x%06x does not match old OUI 0x%06x", oi.oui, t->oui);
        return VTSS_RC_ERROR;
    }
    if (oi.idx >= VTSS_MAC_INDEX_CNT) {
        VTSS_E("MAC/idx 0x%06x/%u exceeds block size %u", oi.idx, oi.idx, VTSS_MAC_INDEX_CNT);
        return VTSS_RC_ERROR;
    }

    // Look for existing or free entry
    for (i = 0; i < VTSS_MAC_INDEX_VID_CNT; i++) {
        e = &t->e[i];
        if (e->vid == vid) {
            break;
        }
        if (e->vid == 0 && i_free == VTSS_MAC_INDEX_VID_CNT) {
            i_free = i;
        }
    }
    if (i == VTSS_MAC_INDEX_VID_CNT) {
        // VID not found
        i = i_free;
        if (i == VTSS_MAC_INDEX_VID_CNT) {
            VTSS_E("no more VLANs available");
            return VTSS_RC_ERROR;
        }
        t->oui = oi.oui;
        t->e[i].vid = vid;
        VTSS_RC(vtss_mac_index_update(vtss_state));
    }
    e = &t->e[i];
    if (VTSS_BF_GET(e->valid, oi.idx) == 0) {
        e->cnt++;
        VTSS_BF_SET(e->valid, oi.idx, 1);
    }
    t->idx_add = (i * VTSS_MAC_INDEX_VID_CNT + oi.idx); // Index to be added
    return VTSS_RC_OK;
}

static vtss_rc vtss_mac_index_del(vtss_state_t *vtss_state,
                                  const vtss_vid_mac_t *const vid_mac)
{
    vtss_mac_index_table_t *t = &vtss_state->l2.mac_index_table;
    vtss_mac_vlan_entry_t  *e;
    vtss_oui_idx_t         oi;
    u8                     i;

    vtss_mac_oui_idx_get(&vid_mac->mac, &oi);
    for (i = 0; i < VTSS_MAC_INDEX_VID_CNT; i++) {
        e = &t->e[i];
        if (e->vid == vid_mac->vid && VTSS_BF_GET(e->valid, oi.idx)) {
            e->cnt--;
            VTSS_BF_SET(e->valid, oi.idx, 0);
            if (e->cnt == 0) {
                // Free VID entry
                e->vid = 0;
                return vtss_mac_index_update(vtss_state);
            }
        }
    }
    return VTSS_RC_OK;
}
#endif

vtss_rc vtss_mac_add(vtss_state_t *vtss_state,
                     vtss_mac_user_t user, const vtss_mac_table_entry_t *const entry)
{
    u32                    pgid, pgid_old, port_count = vtss_state->port_count;
    vtss_mac_table_entry_t old_entry = {0};
    vtss_mac_entry_t       *mac_entry;
    vtss_port_no_t         port_no;
    BOOL                   ipmc = 0, *member;
    vtss_vid_mac_t         vid_mac;
    BOOL                   cpu_copy = 0;
    vtss_packet_rx_queue_t cpu_queue = 0;

    vid_mac = entry->vid_mac;
    VTSS_D("vid: %d, mac: %02x-%02x-%02x-%02x-%02x-%02x",
           vid_mac.vid,
           vid_mac.mac.addr[0], vid_mac.mac.addr[1], vid_mac.mac.addr[2],
           vid_mac.mac.addr[3], vid_mac.mac.addr[4], vid_mac.mac.addr[5]);

    if (!entry->locked) {
        VTSS_E("entry must be locked");
        return VTSS_RC_ERROR;
    }

    if (entry->copy_to_cpu) {
        cpu_copy = 1;
        cpu_queue = entry->cpu_queue;
    } else {
        /* Only entries without CPU copy can be encoded as IPMC entries */
        ipmc = vtss_ipmc_mac(vtss_state, &vid_mac);
    }

    // Fill out member list for IPMC (pseudo PGID)
    pgid = VTSS_PGID_NONE;
    member = vtss_state->l2.pgid_table[pgid].member;
    for (port_no = VTSS_PORT_NO_START; port_no < port_count; port_no++) {
        member[port_no] = VTSS_BOOL(entry->destination[port_no]);
    }

    // Check if a PGID can be allocated
    pgid_old = VTSS_PGID_NONE;
    if (!ipmc) {
        old_entry.vid_mac = vid_mac;
        if (vtss_mac_get(vtss_state, &old_entry, &pgid_old) == VTSS_RC_OK && old_entry.locked) {
            // Locked entry, PGID may be freed later
        } else {
            pgid_old = VTSS_PGID_NONE;
        }
        if (pgid_old == VTSS_PGID_NONE || vtss_state->l2.pgid_table[pgid_old].references > 1) {
            // New PGID allocation is needed
            VTSS_RC(vtss_pgid_alloc(vtss_state, &pgid, member, cpu_copy, cpu_queue, 0));
        }
    }

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    if (entry->index_table) {
        VTSS_RC(vtss_mac_index_add(vtss_state, entry));
    } else
#endif
    {
        /* Add all locked entries to state block */
        if ((mac_entry = vtss_mac_entry_add(vtss_state, user, &entry->vid_mac)) == NULL) {
            return VTSS_RC_ERROR;
        }
        for (port_no = VTSS_PORT_NO_START; port_no < port_count; port_no++)
            VTSS_PORT_BF_SET(mac_entry->member, port_no, entry->destination[port_no]);
        mac_entry->cpu_copy = cpu_copy;
        mac_entry->cpu_copy_smac = entry->copy_to_cpu_smac;
        mac_entry->cpu_queue = cpu_queue;
    }

    /* No further processing in warm start mode */
    if (vtss_state->warm_start_cur)
        return VTSS_RC_OK;

    if (ipmc) {
        /* IPv4/IPv6 multicast address, use pseudo PGID */
        vtss_pgid_members_get(vtss_state, pgid, member);
    } else {
        /* Free old PGID if the address exists */
        if (pgid_old != VTSS_PGID_NONE) {
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
            if (old_entry.index_table != VTSS_BOOL(entry->index_table)) {
                // Delete old locked entry if it is in the other table
                VTSS_RC(vtss_mac_del(vtss_state, user, &vid_mac));
                pgid_old = VTSS_PGID_NONE;
            }
#endif
            VTSS_RC(vtss_pgid_free(vtss_state, pgid_old));
        }

        /* Allocate new PGID */
        VTSS_RC(vtss_pgid_alloc(vtss_state, &pgid, member, cpu_copy, cpu_queue, 1));
    }

    vtss_state->l2.mac_status.learned = 1;

    return VTSS_FUNC(l2.mac_table_add, entry, pgid);
}

vtss_rc vtss_mac_table_add(const vtss_inst_t             inst,
                           const vtss_mac_table_entry_t  *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("vid: %d, mac: %02x-%02x-%02x-%02x-%02x-%02x, copy_to_cpu: %u locked: %u",
           entry->vid_mac.vid,
           entry->vid_mac.mac.addr[0], entry->vid_mac.mac.addr[1], entry->vid_mac.mac.addr[2],
           entry->vid_mac.mac.addr[3], entry->vid_mac.mac.addr[4], entry->vid_mac.mac.addr[5],
           entry->copy_to_cpu,
           entry->locked);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_add(vtss_state, VTSS_MAC_USER_NONE, entry);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_del(vtss_state_t *vtss_state,
                     vtss_mac_user_t user, const vtss_vid_mac_t *const vid_mac)
{
    vtss_rc                rc;
    vtss_mac_table_entry_t entry;
    u32                    pgid = 0; /* Please Lint */

    VTSS_D("vid: %d, mac: %02x-%02x-%02x-%02x-%02x-%02x",
           vid_mac->vid,
           vid_mac->mac.addr[0], vid_mac->mac.addr[1], vid_mac->mac.addr[2],
           vid_mac->mac.addr[3], vid_mac->mac.addr[4], vid_mac->mac.addr[5]);

    /* Delete entry from state block */
    VTSS_RC(vtss_mac_entry_del(vtss_state, user, vid_mac));

    /* No further processing in warm start mode */
    if (vtss_state->warm_start_cur)
        return VTSS_RC_OK;

    /* Free PGID and delete if the entry exists */
    entry.vid_mac = *vid_mac;
    if ((rc = vtss_mac_get(vtss_state, &entry, &pgid)) == VTSS_RC_OK) {
        if (entry.locked)
            VTSS_RC(vtss_pgid_free(vtss_state, pgid));
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
        if (entry.index_table) {
            VTSS_RC(vtss_mac_index_del(vtss_state, vid_mac));
        }
#endif
        vtss_state->l2.mac_status.aged = 1;
        rc = VTSS_FUNC(l2.mac_table_del, vid_mac);
    }
    return rc;
}

vtss_rc vtss_mac_table_del(const vtss_inst_t     inst,
                           const vtss_vid_mac_t  *const vid_mac)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_del(vtss_state, VTSS_MAC_USER_NONE, vid_mac);
    VTSS_EXIT();
    return rc;
}

static void vtss_mac_pgid_get(vtss_state_t *vtss_state,
                              vtss_mac_table_entry_t *const entry, u32 pgid)
{
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[pgid];

    vtss_pgid_members_get(vtss_state, pgid, entry->destination);

    /* The CPU copy flag may be set in the MAC address table or PGID table */
    if (pgid_entry->cpu_copy) {
        entry->copy_to_cpu = 1;
        entry->cpu_queue = pgid_entry->cpu_queue;
    }
}

vtss_rc vtss_mac_get(vtss_state_t *vtss_state,
                     vtss_mac_table_entry_t *const entry, u32 *pgid)
{
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    // Lookup in index table first
    if (vtss_mac_index_get(vtss_state, entry, pgid, 0) == VTSS_RC_OK) {
        return VTSS_RC_OK;
    }
    entry->index_table = 0;
    vtss_state->l2.mac_index_table.idx_get = 0xffffffff;
#endif
    // Lookup in normal table
    return VTSS_FUNC(l2.mac_table_get, entry, pgid);
}


vtss_rc vtss_mac_table_get(const vtss_inst_t       inst,
                           const vtss_vid_mac_t    *const vid_mac,
                           vtss_mac_table_entry_t  *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    u32          pgid = 0; /* Please Lint */

    VTSS_D("vid: %d, mac: %02x-%02x-%02x-%02x-%02x-%02x",
           vid_mac->vid,
           vid_mac->mac.addr[0], vid_mac->mac.addr[1], vid_mac->mac.addr[2],
           vid_mac->mac.addr[3], vid_mac->mac.addr[4], vid_mac->mac.addr[5]);

    VTSS_ENTER();
    entry->vid_mac = *vid_mac;
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_mac_get(vtss_state, entry, &pgid)) == VTSS_RC_OK) {
        vtss_mac_pgid_get(vtss_state, entry, pgid);
    }
    VTSS_EXIT();
    return rc;
}

static vtss_rc vtss_mac_get_next(vtss_state_t *vtss_state,
                                 const vtss_vid_mac_t   *const vid_mac,
                                 vtss_mac_table_entry_t *const entry)
{
    vtss_rc                rc = VTSS_RC_ERROR;
    u32                    pgid = 0; /* Please Lint */
    vtss_mac_table_entry_t mac_entry;
    u32                    mach, macl;
    vtss_mac_entry_t       *cur, *cmp;
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    vtss_mac_entry_t       mac_idx;
#endif

    VTSS_D("vid: %d, mac: %02x-%02x-%02x-%02x-%02x-%02x",
           vid_mac->vid,
           vid_mac->mac.addr[0], vid_mac->mac.addr[1], vid_mac->mac.addr[2],
           vid_mac->mac.addr[3], vid_mac->mac.addr[4], vid_mac->mac.addr[5]);

    // Look for static entry
    vtss_mach_macl_get(vid_mac, &mach, &macl);
    for (cur = vtss_mac_entry_get(vtss_state, mach, macl, 1); cur != NULL; cur = cur->next) {
        if (cur->user != VTSS_MAC_USER_NONE) {
            continue;
        }

        /* Lookup in chip */
        vtss_mach_macl_set(&entry->vid_mac, cur->mach, cur->macl);
        if ((rc = vtss_mac_get(vtss_state, entry, &pgid)) == VTSS_RC_OK) {
            vtss_mac_pgid_get(vtss_state, entry, pgid);
            VTSS_D("found sw entry 0x%08x%08x", cur->mach, cur->macl);
            break;
        }
    }

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    // Look for entry in index table
    mac_entry.vid_mac = *vid_mac;
    if (vtss_mac_index_get(vtss_state, &mac_entry, &pgid, 1) == VTSS_RC_OK) {
        vtss_mach_macl_get(&mac_entry.vid_mac, &mach, &macl);
        if (cur == NULL || (mach < cur->mach || (mach == cur->mach && macl < cur->macl))) {
            // Index entry is smaller than static entry
            vtss_mac_pgid_get(vtss_state, &mac_entry, pgid);
            mac_idx.mach = mach;
            mac_idx.macl = macl;
            cur = &mac_idx;
            *entry = mac_entry;
            rc = VTSS_RC_OK;
        }
    }
#endif

    mac_entry.vid_mac = *vid_mac;
    while (VTSS_FUNC(l2.mac_table_get_next, &mac_entry, &pgid) == VTSS_RC_OK) {
        vtss_mac_pgid_get(vtss_state, &mac_entry, pgid);
        vtss_mach_macl_get(&mac_entry.vid_mac, &mach, &macl);
        VTSS_D("found chip entry 0x%08x%08x", mach, macl);

        if ((cmp = vtss_mac_entry_get(vtss_state, mach, macl, 0)) != NULL &&
            cmp->mach == mach && cmp->macl == macl && cmp->user != VTSS_MAC_USER_NONE) {
            continue;
        }

        if (cur == NULL || (mach < cur->mach || (mach == cur->mach && macl < cur->macl))) {
            // Chip entry is smaller than static/index entry
            *entry = mac_entry;
        }

        rc = VTSS_RC_OK;
        break;
    }

    return rc;
}


vtss_rc vtss_mac_table_get_next(const vtss_inst_t       inst,
                                const vtss_vid_mac_t    *const vid_mac,
                                vtss_mac_table_entry_t  *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_get_next(vtss_state, vid_mac, entry);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_table_age_time_get(const vtss_inst_t          inst,
                                    vtss_mac_table_age_time_t  *const age_time)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        *age_time = vtss_state->l2.mac_age_time;
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_table_age_time_set(const vtss_inst_t                inst,
                                    const vtss_mac_table_age_time_t  age_time)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("age_time: %u", age_time);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.mac_age_time = age_time;
        rc = VTSS_FUNC_0(l2.mac_table_age_time_set);
    }
    VTSS_EXIT();
    return rc;
}

static vtss_rc vtss_mac_age(vtss_state_t     *vtss_state,
                            BOOL             pgid_age,
                            u32              pgid,
                            BOOL             vid_age,
                            const vtss_vid_t vid,
                            u32              count)
{
    vtss_rc        rc;
    u32            i;
    vtss_port_no_t port_no = VTSS_PORT_NO_NONE;

    VTSS_D("enter, pgid_age: %u, pgid: %u, vid_age: %u, vid: %u, count: %u", pgid_age, pgid, vid_age, vid, count);

    if (pgid_age && pgid < vtss_state->port_count)
        port_no = vtss_aggr_port(vtss_state, pgid);

    for (i = 0; i < count; i++) {
        if ((rc = VTSS_FUNC_COLD(l2.mac_table_age, pgid_age, pgid, vid_age, vid)) != VTSS_RC_OK)
            return rc;

        /* Age logical port */
        if (port_no != VTSS_PORT_NO_NONE &&
            (rc = VTSS_FUNC_COLD(l2.mac_table_age, pgid_age, port_no, vid_age, vid)) != VTSS_RC_OK)
            return rc;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_mac_table_age(const vtss_inst_t  inst)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_age(vtss_state, 0, 0, 0, 0, 1);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_table_vlan_age(const vtss_inst_t  inst,
                                const vtss_vid_t   vid)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("vid: %u", vid);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_age(vtss_state, 0, 0, 1, vid, 1);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_table_flush(const vtss_inst_t inst)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_age(vtss_state, 0, 0, 0, 0, 2);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_table_port_flush(const vtss_inst_t     inst,
                                  const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_age(vtss_state, 1, port_no, 0, 0, 2);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_table_vlan_flush(const vtss_inst_t  inst,
                                  const vtss_vid_t   vid)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("vid: %u", vid);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_age(vtss_state, 0, 0, 1, vid, 2);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_table_vlan_port_flush(const vtss_inst_t     inst,
                                       const vtss_port_no_t  port_no,
                                       const vtss_vid_t      vid)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u, vid: %u", port_no, vid);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_mac_age(vtss_state, 1, port_no, 1, vid, 2);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vid_check(const vtss_vid_t vid)
{
    if (vid == VTSS_VID_NULL || vid >= VTSS_VIDS) {
        VTSS_E("illegal vid: %u", vid);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_mac_table_status_get(const vtss_inst_t        inst,
                                  vtss_mac_table_status_t  *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = VTSS_FUNC(l2.mac_table_status_get, status)) == VTSS_RC_OK) {
        /* Read and clear events */
        if (vtss_state->l2.mac_status.learned)
            status->learned = 1;
        if (vtss_state->l2.mac_status.aged)
            status->aged = 1;
        VTSS_MEMSET(&vtss_state->l2.mac_status, 0, sizeof(*status));
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_learn_port_mode_get(const vtss_inst_t     inst,
                                 const vtss_port_no_t  port_no,
                                 vtss_learn_mode_t     *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *mode = vtss_state->l2.learn_mode[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_learn_port_mode_set(const vtss_inst_t        inst,
                                 const vtss_port_no_t     port_no,
                                 const vtss_learn_mode_t  *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u, auto: %u, cpu: %u, discard: %u",
           port_no, mode->automatic, mode->cpu, mode->discard);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->l2.learn_mode[port_no] = *mode;
        rc = VTSS_FUNC_COLD(l2.learn_port_mode_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

/* - Operational state --------------------------------------------- */

vtss_rc vtss_port_state_get(const vtss_inst_t     inst,
                            const vtss_port_no_t  port_no,
                            BOOL                  *const state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *state = vtss_state->l2.port_state[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_port_state_set(const vtss_inst_t     inst,
                            const vtss_port_no_t  port_no,
                            BOOL                  state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_I("port_no: %u, state: %s", port_no, state ? "up" : "down");
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_AFI_SWC)
        if (!state) {
            BOOL afi_link = FALSE;

            // Pause all AFI-generated frames to this port.
            // This must be done prior to actually taking the port down.
            VTSS_I("Pausing AFI on port_no %u", port_no);
            (void)VTSS_FUNC(afi.link_state_change, port_no, &afi_link);
        }
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

#if defined(VTSS_FEATURE_TIMESTAMP)
        if (!vtss_state->l2.port_state[port_no] && state) {
            (void)VTSS_FUNC(ts.link_up, port_no);
        }
#endif

        vtss_state->l2.port_state[port_no] = state;
        rc = vtss_update_masks(vtss_state, 1, 0, 1);

#if defined(VTSS_FEATURE_AFI_SWC)
        if (rc == VTSS_RC_OK && state) {
            BOOL afi_link = TRUE;

            // Resume all AFI-generated frames to this port.
            // This must be done after bringing the port up
            VTSS_I("Resuming AFI on iport %u", port_no);
            (void)VTSS_FUNC(afi.link_state_change, port_no, &afi_link);
        }
#endif /* defined(VTSS_FEATURE_AFI_SWC) */
    }
    VTSS_EXIT();
    return rc;
}

/* - Spanning Tree ------------------------------------------------- */

vtss_rc vtss_stp_port_state_get(const vtss_inst_t     inst,
                                const vtss_port_no_t  port_no,
                                vtss_stp_state_t      *const state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *state = vtss_state->l2.stp_state[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_stp_port_state_set(const vtss_inst_t       inst,
                                const vtss_port_no_t    port_no,
                                const vtss_stp_state_t  state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_I("port_no: %u, state: %s",
           port_no,
           state == VTSS_STP_STATE_DISCARDING ? "discard" :
           state == VTSS_STP_STATE_LEARNING ? "learn" : "forward");
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->l2.stp_state[port_no] = state;
        rc = vtss_update_masks(vtss_state, 1, 0, 1);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_L2_MSTP)
vtss_rc vtss_mstp_vlan_msti_get(const vtss_inst_t  inst,
                                const vtss_vid_t   vid,
                                vtss_msti_t        *const msti)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        *msti = vtss_state->l2.vlan_table[vid].msti;
    VTSS_EXIT();
    return rc;
}

static vtss_rc vtss_msti_check(const vtss_msti_t msti)
{
    if (msti >= VTSS_MSTI_END) {
        VTSS_E("illegal msti: %u", msti);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_mstp_vlan_msti_set(const vtss_inst_t  inst,
                                const vtss_vid_t   vid,
                                const vtss_msti_t  msti)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("vid: %u, msti: %u", vid, msti);

    VTSS_RC(vtss_vid_check(vid));
    VTSS_RC(vtss_msti_check(msti));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.vlan_table[vid].msti = msti;
        rc = VTSS_FUNC_COLD(l2.mstp_vlan_msti_set, vid);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mstp_port_msti_state_get(const vtss_inst_t     inst,
                                      const vtss_port_no_t  port_no,
                                      const vtss_msti_t     msti,
                                      vtss_stp_state_t      *const state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_msti_check(msti));
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *state = vtss_state->l2.mstp_table[msti].state[port_no - VTSS_PORT_NO_START];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mstp_port_msti_state_set(const vtss_inst_t       inst,
                                      const vtss_port_no_t    port_no,
                                      const vtss_msti_t       msti,
                                      const vtss_stp_state_t  state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("port_no: %u, msti: %u, state: %s",
           port_no, msti,
           state == VTSS_STP_STATE_DISCARDING ? "discard" :
           state == VTSS_STP_STATE_LEARNING ? "learn" : "forward");

    VTSS_RC(vtss_msti_check(msti));
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->l2.mstp_table[msti].state[port_no - VTSS_PORT_NO_START] = state;
        rc = VTSS_FUNC_COLD(l2.mstp_state_set, port_no, msti);
    }
    VTSS_EXIT();
    return rc;
}
#endif // VTSS_FEATURE_L2_MSTP

#if defined(VTSS_FEATURE_L2_ERPS)
static vtss_rc vtss_erpi_check(const vtss_erpi_t erpi)
{
    if (erpi >= VTSS_ERPI_END) {
        VTSS_E("illegal erpi: %u", erpi);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_erps_vlan_member_get(const vtss_inst_t inst,
                                  const vtss_erpi_t erpi,
                                  const vtss_vid_t  vid,
                                  BOOL              *const member)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_erpi_check(erpi));
    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        *member = VTSS_BF_GET(vtss_state->l2.erps_table[erpi].vlan_member, vid);
    VTSS_EXIT();
    return rc;
}

/* Update ERPS discard state for VLAN */
static void vtss_erps_vlan_update(vtss_state_t *vtss_state,
                                  vtss_erpi_t erpi, vtss_vid_t vid, BOOL member)
{
    vtss_port_no_t    port_no;
    vtss_vlan_entry_t *vlan_entry;
    vtss_erps_entry_t *erps_entry = &vtss_state->l2.erps_table[erpi];

    if (VTSS_BF_GET(erps_entry->vlan_member, vid) != member) {
        VTSS_BF_SET(erps_entry->vlan_member, vid, member);

        /* Update ERPI discard state for VLAN */
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (!VTSS_PORT_BF_GET(erps_entry->port_member, port_no)) {
                /* Update number of rings with port in discarding state */
                if (member)
                    vlan_entry->erps_discard_cnt[port_no]++;
                else
                    vlan_entry->erps_discard_cnt[port_no]--;
            }
        }
    }
}

vtss_rc vtss_erps_vlan_member_set(const vtss_inst_t inst,
                                  const vtss_erpi_t erpi,
                                  const vtss_vid_t  vid,
                                  const BOOL        member)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("erpi: %u, vid: %u, member: %u", erpi, vid, member);

    VTSS_RC(vtss_erpi_check(erpi));
    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_erps_vlan_update(vtss_state, erpi, vid, VTSS_BOOL(member));
        rc = VTSS_FUNC_COLD(l2.erps_vlan_member_set, erpi, vid);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_erps_port_state_get(const vtss_inst_t    inst,
                                 const vtss_erpi_t    erpi,
                                 const vtss_port_no_t port_no,
                                 vtss_erps_state_t    *const state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_erpi_check(erpi));
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *state = (VTSS_PORT_BF_GET(vtss_state->l2.erps_table[erpi].port_member, port_no) ?
                  VTSS_ERPS_STATE_FORWARDING : VTSS_ERPS_STATE_DISCARDING);
    VTSS_EXIT();
    return rc;
}

/* Update ERPS discard state for port */
static BOOL vtss_erps_port_update(vtss_state_t *vtss_state,
                                  vtss_erpi_t erpi, vtss_port_no_t port_no, BOOL forward)
{
    vtss_vid_t          vid;
    vtss_vlan_entry_t   *vlan_entry;
    vtss_erps_entry_t   *erps_entry = &vtss_state->l2.erps_table[erpi];
    vtss_erps_counter_t count;

    /* Check if forwarding state has changed */
    if (forward == VTSS_PORT_BF_GET(erps_entry->port_member, port_no))
        return 0;
    VTSS_PORT_BF_SET(erps_entry->port_member, port_no, forward);

    /* Update ERPI discard state for port in VLANs enabled for the ring */
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        if (VTSS_BF_GET(erps_entry->vlan_member, vid)) {
            vlan_entry = &vtss_state->l2.vlan_table[vid];
            count = vlan_entry->erps_discard_cnt[port_no];
            if (forward) {
                /* Change to forwarding state */
                count--;
                if (count == 0)
                    vlan_entry->flags |= VLAN_FLAGS_UPDATE;
            } else {
                /* Change to discarding state */
                count++;
                if (count == 1)
                    vlan_entry->flags |= VLAN_FLAGS_UPDATE;
            }
            vlan_entry->erps_discard_cnt[port_no] = count;
        }
    }

    return 1;
}

vtss_rc vtss_erps_port_state_set(const vtss_inst_t       inst,
                                 const vtss_erpi_t       erpi,
                                 const vtss_port_no_t    port_no,
                                 const vtss_erps_state_t state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    BOOL         forward = VTSS_BOOL(state == VTSS_ERPS_STATE_FORWARDING);

    VTSS_N("erpi: %u, port_no: %u, state: %s",
           erpi, port_no, forward ? "forward" : "discard");

    VTSS_RC(vtss_erpi_check(erpi));
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_erps_port_update(vtss_state, erpi, port_no, forward))
            rc = VTSS_FUNC_COLD(l2.erps_port_state_set, erpi, port_no);
    }
    VTSS_EXIT();
    return rc;
}
#endif // VTSS_FEATURE_L2_ERPS

/* - VLAN ---------------------------------------------------------- */

vtss_rc vtss_vlan_conf_get(const vtss_inst_t inst,
                           vtss_vlan_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->l2.vlan_conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_conf_set(const vtss_inst_t      inst,
                           const vtss_vlan_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.vlan_conf = *conf;
        rc = VTSS_FUNC_COLD_0(l2.vlan_conf_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_port_conf_get(const vtss_inst_t      inst,
                                const vtss_port_no_t   port_no,
                                vtss_vlan_port_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_N("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *conf = vtss_state->l2.vlan_port_conf[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_port_conf_set(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_vlan_port_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->l2.vlan_port_conf[port_no] = *conf;
        rc = VTSS_FUNC_COLD(l2.vlan_port_conf_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_port_members_get(const vtss_inst_t  inst,
                                   const vtss_vid_t   vid,
                                   BOOL               member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = VTSS_PORT_BF_GET(vtss_state->l2.vlan_table[vid].member, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_port_members_set(const vtss_inst_t  inst,
                                   const vtss_vid_t   vid,
                                   const BOOL         member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t      *vtss_state;
    vtss_rc           rc;
    vtss_port_no_t    port_no;
    vtss_vlan_entry_t *vlan_entry;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        vlan_entry->flags &= ~VLAN_FLAGS_ENABLED;
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            VTSS_PORT_BF_SET(vlan_entry->member, port_no, member[port_no]);
            if (member[port_no])
                vlan_entry->flags |= VLAN_FLAGS_ENABLED;
        }
        rc = VTSS_FUNC_COLD(l2.vlan_port_members_set, vid);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_vid_conf_get(const vtss_inst_t    inst,
                               const vtss_vid_t     vid,
                               vtss_vlan_vid_conf_t *const conf)
{
    vtss_state_t      *vtss_state;
    vtss_rc           rc;
    vtss_vlan_entry_t *e;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        e = &vtss_state->l2.vlan_table[vid];
        conf->learning = (e->flags & VLAN_FLAGS_LEARN ? 1 : 0);
        conf->flooding = (e->flags & VLAN_FLAGS_FLOOD ? 1 : 0);
        conf->mirror = (e->flags & VLAN_FLAGS_MIRROR ? 1 : 0);
        conf->ingress_filter = (e->flags & VLAN_FLAGS_FILTER ? 1 : 0);
#if defined(VTSS_FEATURE_VLAN_SVL)
        conf->fid = e->fid;
#endif /* VTSS_FEATURE_VLAN_SVL */
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_vid_conf_set(const vtss_inst_t          inst,
                               const vtss_vid_t           vid,
                               const vtss_vlan_vid_conf_t *const conf)
{
    vtss_state_t      *vtss_state;
    vtss_rc           rc;
    vtss_vlan_entry_t *e;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        e = &vtss_state->l2.vlan_table[vid];
        if (conf->learning) {
            e->flags |= VLAN_FLAGS_LEARN;
        } else {
            e->flags &= ~VLAN_FLAGS_LEARN;
        }
        if (conf->flooding) {
            e->flags |= VLAN_FLAGS_FLOOD;
        } else {
            e->flags &= ~VLAN_FLAGS_FLOOD;
        }
        if (conf->mirror) {
            e->flags |= VLAN_FLAGS_MIRROR;
        } else {
            e->flags &= ~VLAN_FLAGS_MIRROR;
        }
        if (conf->ingress_filter) {
            e->flags |= VLAN_FLAGS_FILTER;
        } else {
            e->flags &= ~VLAN_FLAGS_FILTER;
        }
#if defined(VTSS_FEATURE_VLAN_SVL)
        e->fid = conf->fid;
#endif /* VTSS_FEATURE_VLAN_SVL */
        rc = vtss_cmn_vlan_members_set(vtss_state, vid);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_VCAP)
vtss_rc vtss_vlan_tx_tag_get(const vtss_inst_t  inst,
                             const vtss_vid_t   vid,
                             vtss_vlan_tx_tag_t tx_tag[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("vid: %u", vid);
    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            tx_tag[port_no] = vtss_state->l2.vlan_table[vid].tx_tag[port_no];
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_tx_tag_set(const vtss_inst_t        inst,
                             const vtss_vid_t         vid,
                             const vtss_vlan_tx_tag_t tx_tag[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("vid: %u", vid);
    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(l2.vlan_tx_tag_set, vid, tx_tag);
    }
    VTSS_EXIT();
    return rc;
}
#endif // VTSS_FEATURE_VCAP

/* - Port Isolation------------------------------------------------- */

vtss_rc vtss_isolated_vlan_get(const vtss_inst_t  inst,
                               const vtss_vid_t   vid,
                               BOOL               *const isolated)
{
    vtss_state_t      *vtss_state;
    vtss_rc           rc;
    vtss_vlan_entry_t *e;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        e = &vtss_state->l2.vlan_table[vid];
        *isolated = (e->flags & VLAN_FLAGS_ISOLATED ? 1 : 0);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_isolated_vlan_set(const vtss_inst_t  inst,
                               const vtss_vid_t   vid,
                               const BOOL         isolated)
{
    vtss_state_t      *vtss_state;
    vtss_rc           rc;
    vtss_vlan_entry_t *e;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        e = &vtss_state->l2.vlan_table[vid];
        if (isolated) {
            e->flags |= VLAN_FLAGS_ISOLATED;
        } else {
            e->flags &= ~VLAN_FLAGS_ISOLATED;
        }
        rc = VTSS_FUNC_COLD(l2.isolated_vlan_set, vid);
    }
    VTSS_EXIT();
    return rc;

}

vtss_rc vtss_isolated_port_members_get(const vtss_inst_t  inst,
                                       BOOL               member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = vtss_state->l2.isolated_port[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_isolated_port_members_set(const vtss_inst_t  inst,
                                       const BOOL         member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            vtss_state->l2.isolated_port[port_no] = member[port_no];
        rc = VTSS_FUNC_COLD_0(l2.isolated_port_members_set);
    }
    VTSS_EXIT();
    return rc;
}

 /* - Private VLAN (PVLAN) ------------------------------------------ */

static vtss_rc vtss_pvlan_no_check(const vtss_pvlan_no_t pvlan_no)
{
    if (pvlan_no >= VTSS_PVLAN_NO_END) {
        VTSS_E("illegal pvlan_no: %u", pvlan_no);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_pvlan_port_members_get(const vtss_inst_t      inst,
                                    const vtss_pvlan_no_t  pvlan_no,
                                    BOOL                   member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t       *vtss_state;
    vtss_rc            rc;
    vtss_port_no_t     port_no;
    vtss_pvlan_entry_t *pvlan_entry;

    VTSS_RC(vtss_pvlan_no_check(pvlan_no));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        pvlan_entry = &vtss_state->l2.pvlan_table[pvlan_no];
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = pvlan_entry->member[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_pvlan_port_members_set(const vtss_inst_t      inst,
                                    const vtss_pvlan_no_t  pvlan_no,
                                    const BOOL             member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t       *vtss_state;
    vtss_rc            rc;
    vtss_port_no_t     port_no;
    vtss_pvlan_entry_t *pvlan_entry;

    VTSS_RC(vtss_pvlan_no_check(pvlan_no));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        pvlan_entry = &vtss_state->l2.pvlan_table[pvlan_no];
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            pvlan_entry->member[port_no] = member[port_no];
        rc = vtss_update_masks(vtss_state, 1, 0, 0);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_apvlan_port_members_get(const vtss_inst_t    inst,
                                     const vtss_port_no_t port_no,
                                     BOOL                 member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t e_port;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        for (e_port = VTSS_PORT_NO_START; e_port < vtss_state->port_count; e_port++) {
            member[e_port] = vtss_state->l2.apvlan_table[port_no][e_port];
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_apvlan_port_members_set(const vtss_inst_t    inst,
                                     const vtss_port_no_t port_no,
                                     const BOOL           member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t e_port;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        for (e_port = VTSS_PORT_NO_START; e_port < vtss_state->port_count; e_port++) {
            vtss_state->l2.apvlan_table[port_no][e_port] = member[e_port];
        }
        rc = vtss_update_masks(vtss_state, 1, 0, 0);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_dgroup_port_conf_get(const vtss_inst_t       inst,
                                  const vtss_port_no_t    port_no,
                                  vtss_dgroup_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *conf = vtss_state->l2.dgroup_port_conf[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_dgroup_port_conf_set(const vtss_inst_t             inst,
                                  const vtss_port_no_t          port_no,
                                  const vtss_dgroup_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK &&
        (rc = vtss_port_no_check(vtss_state, conf->dgroup_no)) == VTSS_RC_OK) {
        vtss_state->l2.dgroup_port_conf[port_no] = *conf;
        rc = vtss_update_masks(vtss_state, 0, 1, 0);
    }
    VTSS_EXIT();
    return rc;
}

/* - Aggregation --------------------------------------------------- */

static vtss_rc vtss_aggr_no_check(vtss_state_t *vtss_state, const vtss_aggr_no_t aggr_no)
{
    if (aggr_no >= (vtss_state->port_count/2)) {
        VTSS_E("illegal aggr_no: %u", aggr_no);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_aggr_port_members_get(const vtss_inst_t     inst,
                                   const vtss_aggr_no_t  aggr_no,
                                   BOOL                  member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;
    vtss_glag_no_t glag_no;

    VTSS_D("aggr_no: %u", aggr_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_aggr_no_check(vtss_state, aggr_no)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            glag_no = vtss_state->l2.port_aggr_no[port_no];
            member[port_no] = VTSS_BOOL(glag_no == aggr_no);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_aggr_port_members_set(const vtss_inst_t     inst,
                                   const vtss_aggr_no_t  aggr_no,
                                   const BOOL            member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("aggr_no: %u", aggr_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_aggr_no_check(vtss_state, aggr_no)) == VTSS_RC_OK) {
        {
            for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                if (member[port_no])
                    vtss_state->l2.port_aggr_no[port_no] = aggr_no;
                else if (vtss_state->l2.port_aggr_no[port_no] == aggr_no)
                    vtss_state->l2.port_aggr_no[port_no] = VTSS_AGGR_NO_NONE;
            }
            rc = vtss_update_masks(vtss_state, 1, 1, 1);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_aggr_mode_get(const vtss_inst_t  inst,
                           vtss_aggr_mode_t   *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        *mode = vtss_state->l2.aggr_mode;
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_aggr_mode_set(const vtss_inst_t       inst,
                           const vtss_aggr_mode_t  *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.aggr_mode = *mode;
        rc = VTSS_FUNC_0(l2.aggr_mode_set);
    }
    VTSS_EXIT();
    return rc;
}

/* - Mirroring ----------------------------------------------------- */

vtss_rc vtss_mirror_conf_get(const vtss_inst_t  inst,
                             vtss_mirror_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->l2.mirror_conf;
    }

    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_mirror_conf_set(const vtss_inst_t        inst,
                             const vtss_mirror_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_port_no_none_check(vtss_state, conf->port_no)) == VTSS_RC_OK) {
        vtss_state->l2.mirror_conf = *conf;
        rc = VTSS_FUNC_COLD_0(l2.mirror_port_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_monitor_port_get(const vtss_inst_t  inst,
                                     vtss_port_no_t     *const port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *port_no = vtss_state->l2.mirror_conf.port_no;
    }

    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_monitor_port_set(const vtss_inst_t     inst,
                                     const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_port_no_none_check(vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->l2.mirror_conf.port_no = port_no;
        rc = VTSS_FUNC_COLD_0(l2.mirror_port_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_ingress_ports_get(const vtss_inst_t  inst,
                                      BOOL               member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = vtss_state->l2.mirror_ingress[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_ingress_ports_set(const vtss_inst_t  inst,
                                      const BOOL         member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            vtss_state->l2.mirror_ingress[port_no] = VTSS_BOOL(member[port_no]);
        rc = VTSS_FUNC_COLD_0(l2.mirror_ingress_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_egress_ports_get(const vtss_inst_t  inst,
                                     BOOL               member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = vtss_state->l2.mirror_egress[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_egress_ports_set(const vtss_inst_t  inst,
                                     const BOOL         member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            vtss_state->l2.mirror_egress[port_no] = VTSS_BOOL(member[port_no]);
        rc = VTSS_FUNC_COLD_0(l2.mirror_egress_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_cpu_egress_get(const vtss_inst_t  inst,
                                   BOOL               *member)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *member = vtss_state->l2.mirror_cpu_egress;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_cpu_egress_set(const vtss_inst_t  inst,
                                   const BOOL         member)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.mirror_cpu_egress = VTSS_BOOL(member);
        rc = VTSS_FUNC_COLD_0(l2.mirror_cpu_egress_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_cpu_ingress_get(const vtss_inst_t  inst,
                                    BOOL               *member)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *member = vtss_state->l2.mirror_cpu_ingress;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mirror_cpu_ingress_set(const vtss_inst_t  inst,
                                    const BOOL         member)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.mirror_cpu_ingress = VTSS_BOOL(member);
        rc = VTSS_FUNC_COLD_0(l2.mirror_cpu_ingress_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_eps_port_conf_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_eps_port_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *conf = vtss_state->l2.port_protect[port_no].conf;
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_eps_port_conf_set(const vtss_inst_t           inst,
                               const vtss_port_no_t        port_no,
                               const vtss_eps_port_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u, type: %u, conf.port_no: %u", port_no, conf->type, conf->port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->l2.port_protect[port_no].conf = *conf;
        rc = vtss_update_masks(vtss_state, 1, 1, 1);
        if (rc == VTSS_RC_OK)
            rc = VTSS_FUNC_COLD(l2.eps_port_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_eps_port_selector_get(const vtss_inst_t    inst,
                                   const vtss_port_no_t port_no,
                                   vtss_eps_selector_t  *const selector)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *selector = vtss_state->l2.port_protect[port_no].selector;
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_eps_port_selector_set(const vtss_inst_t          inst,
                                   const vtss_port_no_t       port_no,
                                   const vtss_eps_selector_t  selector)
{
    vtss_state_t         *vtss_state;
    vtss_rc              rc;
    vtss_eps_port_conf_t *conf;

    VTSS_D("port_no: %u selector: %u", port_no, selector);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->l2.port_protect[port_no].selector = selector;
        rc = vtss_update_masks(vtss_state, 1, 0, 1);
        if (rc == VTSS_RC_OK)
            rc = VTSS_FUNC_COLD(l2.eps_port_set, port_no);
        conf = &vtss_state->l2.port_protect[port_no].conf;
        if (rc == VTSS_RC_OK && conf->type == VTSS_EPS_PORT_1_FOR_1) {
            /* Flush port for 1:1 protection */
            if (selector == VTSS_EPS_SELECTOR_PROTECTION) {
                /* Flush working port */
                rc = vtss_mac_age(vtss_state, 1, port_no, 0, 0, 2);
            } else if (conf->port_no != VTSS_PORT_NO_NONE) {
                /* Flush protecting port */
                rc = vtss_mac_age(vtss_state, 1, conf->port_no, 0, 0, 2);
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

/* - Flooding control ---------------------------------------------- */
vtss_rc vtss_uc_flood_members_get(const vtss_inst_t  inst,
                                  BOOL               member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = vtss_state->l2.uc_flood[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_uc_flood_members_set(const vtss_inst_t  inst,
                                  const BOOL         member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            vtss_state->l2.uc_flood[port_no] = member[port_no];
        rc = VTSS_FUNC_COLD_0(l2.flood_conf_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mc_flood_members_get(const vtss_inst_t  inst,
                                  BOOL               member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = vtss_state->l2.mc_flood[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mc_flood_members_set(const vtss_inst_t  inst,
                                  const BOOL         member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            vtss_state->l2.mc_flood[port_no] = member[port_no];
        rc = VTSS_FUNC_COLD_0(l2.flood_conf_set);
    }
    VTSS_EXIT();
    return rc;
}

/* - IGMP ---------------------------------------------------- */

vtss_rc vtss_ipv4_mc_flood_members_get(const vtss_inst_t  inst,
                                       BOOL               member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = vtss_state->l2.ipv4_mc_flood[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ipv4_mc_flood_members_set(const vtss_inst_t  inst,
                                       const BOOL         member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            vtss_state->l2.ipv4_mc_flood[port_no] = VTSS_BOOL(member[port_no]);
        rc = VTSS_FUNC_COLD_0(l2.flood_conf_set);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_IPV4_MC_SIP)
vtss_rc vtss_ipv4_mc_add(const vtss_inst_t inst,
                         const vtss_vid_t  vid,
                         const vtss_ip_t   sip,
                         const vtss_ip_t   dip,
                         const BOOL        member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(l2.ipv4_mc_add, vid, sip, dip, member);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ipv4_mc_del(const vtss_inst_t inst,
                         const vtss_vid_t  vid,
                         const vtss_ip_t   sip,
                         const vtss_ip_t   dip)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(l2.ipv4_mc_del, vid, sip, dip);
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_IPV4_MC_SIP */

/* - MLD  ----------------------------------------------------- */

#if defined(VTSS_FEATURE_IPV6_MC_SIP)
vtss_rc vtss_ipv6_mc_add(const vtss_inst_t inst,
                         const vtss_vid_t  vid,
                         const vtss_ipv6_t sip,
                         const vtss_ipv6_t dip,
                         const BOOL        member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(l2.ipv6_mc_add, vid, sip, dip, member);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ipv6_mc_del(const vtss_inst_t inst,
                         const vtss_vid_t  vid,
                         const vtss_ipv6_t sip,
                         const vtss_ipv6_t dip)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(l2.ipv6_mc_del, vid, sip, dip);
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_IPV6_MC_SIP */

vtss_rc vtss_ipv6_mc_flood_members_get(const vtss_inst_t  inst,
                                       BOOL               member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            member[port_no] = vtss_state->l2.ipv6_mc_flood[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ipv6_mc_flood_members_set(const vtss_inst_t  inst,
                                       const BOOL         member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_state_t   *vtss_state;
    vtss_rc        rc;
    vtss_port_no_t port_no;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            vtss_state->l2.ipv6_mc_flood[port_no] = VTSS_BOOL(member[port_no]);
        rc = VTSS_FUNC_COLD_0(l2.flood_conf_set);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ipv6_mc_ctrl_flood_get(const vtss_inst_t  inst,
                                    BOOL               *const scope)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        *scope = vtss_state->l2.ipv6_mc_scope;
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ipv6_mc_ctrl_flood_set(const vtss_inst_t  inst,
                                    const BOOL         scope)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("scope: %u", scope);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.ipv6_mc_scope = VTSS_BOOL(scope);
        rc = VTSS_FUNC_COLD_0(l2.flood_conf_set);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_VCAP)
vtss_rc vtss_vcl_port_conf_get(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               vtss_vcl_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *conf = vtss_state->l2.vcl_port_conf[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vcl_port_conf_set(const vtss_inst_t          inst,
                               const vtss_port_no_t       port_no,
                               const vtss_vcl_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_vcl_port_conf_t *vcl_port_conf = &vtss_state->l2.vcl_port_conf[port_no];

        vtss_state->l2.vcl_port_conf_old = *vcl_port_conf;
        *vcl_port_conf = *conf;
        rc = VTSS_FUNC_COLD(l2.vcl_port_conf_set, port_no);
        if (rc != VTSS_RC_OK) {
            /* Restore configuration if operation failed */
            *vcl_port_conf = vtss_state->l2.vcl_port_conf_old;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vce_init(const vtss_inst_t inst,
                      const vtss_vce_type_t  type,
                      vtss_vce_t *const vce)
{
    vtss_vce_key_t *key = &vce->key;

    VTSS_D("type: %d", type);
    VTSS_MEMSET(vce, 0, sizeof(*vce));
    key->type = type;
    key->mac.dmac_mc = VTSS_VCAP_BIT_ANY;
    key->mac.dmac_bc = VTSS_VCAP_BIT_ANY;
    key->tag.dei = VTSS_VCAP_BIT_ANY;
    key->tag.tagged = VTSS_VCAP_BIT_ANY;
    key->tag.s_tag = VTSS_VCAP_BIT_ANY;

    switch (type) {
    case VTSS_VCE_TYPE_ANY:
    case VTSS_VCE_TYPE_ETYPE:
    case VTSS_VCE_TYPE_LLC:
    case VTSS_VCE_TYPE_SNAP:
    case VTSS_VCE_TYPE_IPV6:
        break;
    case VTSS_VCE_TYPE_IPV4:
        key->frame.ipv4.fragment = VTSS_VCAP_BIT_ANY;
        key->frame.ipv4.options = VTSS_VCAP_BIT_ANY;
        break;
    default:
        VTSS_E("unknown type: %d", type);
        return VTSS_RC_ERROR;
    }

    vce->action.policy_no = VTSS_ACL_POLICY_NO_NONE;
    return VTSS_RC_OK;
}

vtss_rc vtss_vce_add(const vtss_inst_t    inst,
                     const vtss_vce_id_t  vce_id,
                     const vtss_vce_t     *const vce)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("vce_id: %u before %u %s",
            vce->id, vce_id, vce_id == VTSS_VCE_ID_LAST ? "(last)" : "");

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(l2.vce_add, vce_id, vce);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vce_del(const vtss_inst_t    inst,
                     const vtss_vce_id_t  vce_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("vce_id: %u", vce_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(l2.vce_del, vce_id);
    VTSS_EXIT();
    return rc;
}
#endif // VTSS_FEATURE_VCAP

#if defined(VTSS_FEATURE_PSFP)
static vtss_rc vtss_psfp_gate_id_check(const vtss_psfp_gate_id_t id)
{
    if (id < VTSS_PSFP_GATE_CNT) {
        return VTSS_RC_OK;
    }
    VTSS_E("illegal gate id: %u", id);
    return VTSS_RC_ERROR;
}

vtss_rc vtss_psfp_gcl_conf_get(const vtss_inst_t         inst,
                               const vtss_psfp_gate_id_t id,
                               const u32                 max_cnt,
                               vtss_psfp_gce_t           *const gcl,
                               u32                       *const gce_cnt)
{
    vtss_state_t    *vtss_state;
    vtss_rc         rc;
    vtss_psfp_gcl_t *admin_gcl;
    u32             i;

    VTSS_RC(vtss_psfp_gate_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        admin_gcl = &vtss_state->l2.psfp.admin_gcl[id];
        for (i = 0; i < max_cnt && i < VTSS_PSFP_GCL_CNT; i++) {
            gcl[i] = admin_gcl->gce[i];
        }
        *gce_cnt = admin_gcl->gcl_length;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_psfp_gcl_conf_set(const vtss_inst_t         inst,
                               const vtss_psfp_gate_id_t id,
                               const u32                 gce_cnt,
                               const vtss_psfp_gce_t     *const gcl)
{
    vtss_state_t    *vtss_state;
    vtss_rc         rc;
    vtss_psfp_gcl_t *admin_gcl;
    u32             i;

    VTSS_RC(vtss_psfp_gate_id_check(id));
    if (gce_cnt > VTSS_PSFP_GCL_CNT) {
        VTSS_E("illegal gcl_length: %u, maximum: %u", gce_cnt, VTSS_PSFP_GCL_CNT);
        return VTSS_RC_ERROR;
    }
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        admin_gcl = &vtss_state->l2.psfp.admin_gcl[id];
        for (i = 0; i < gce_cnt; i++) {
            admin_gcl->gce[i] = gcl[i];
        }
        admin_gcl->gcl_length = gce_cnt;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_psfp_gate_conf_get(const vtss_inst_t         inst,
                                const vtss_psfp_gate_id_t id,
                                vtss_psfp_gate_conf_t     *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_psfp_gate_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->l2.psfp.gate[id];
    }
    VTSS_EXIT();
    return rc;
}

static vtss_rc vtss_gate_status_get(vtss_state_t *vtss_state,
                                    const vtss_psfp_gate_id_t id,
                                    vtss_psfp_gate_status_t   *const status)
{
    vtss_rc               rc;
    vtss_psfp_state_t     *psfp = &vtss_state->l2.psfp;
    vtss_psfp_gate_conf_t *conf = &psfp->gate[id];

    if ((rc = VTSS_FUNC(l2.psfp_gate_status_get, id, status)) == VTSS_RC_OK &&
        conf->config_change && !status->config_pending) {
        /* Current GCL has been activated, store it as operational GCL */
        psfp->oper_gcl[id] = psfp->admin_gcl[id];
        psfp->oper_conf[id] = conf->config;
    }
    return rc;
}

vtss_rc vtss_psfp_gate_conf_set(const vtss_inst_t           inst,
                                const vtss_psfp_gate_id_t   id,
                                const vtss_psfp_gate_conf_t *const conf)
{
    vtss_rc                 rc;
    vtss_state_t            *vtss_state;
    vtss_psfp_gate_status_t status;

    VTSS_RC(vtss_psfp_gate_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_gate_status_get(vtss_state, id, &status)) == VTSS_RC_OK) {
        vtss_state->l2.psfp.gate[id] = *conf;
        rc = VTSS_FUNC(l2.psfp_gate_conf_set, id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_psfp_gate_status_get(const vtss_inst_t         inst,
                                  const vtss_psfp_gate_id_t id,
                                  vtss_psfp_gate_status_t   *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_psfp_gate_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = vtss_gate_status_get(vtss_state, id, status);
    }
    VTSS_EXIT();
    return rc;
}

static vtss_rc vtss_psfp_filter_id_check(const vtss_psfp_filter_id_t id)
{
    if (id < VTSS_PSFP_FILTER_CNT) {
        return VTSS_RC_OK;
    }
    VTSS_E("illegal filter id: %u", id);
    return VTSS_RC_ERROR;
}

vtss_rc vtss_psfp_filter_conf_get(const vtss_inst_t           inst,
                                  const vtss_psfp_filter_id_t id,
                                  vtss_psfp_filter_conf_t     *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_psfp_filter_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->l2.psfp.filter[id];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_psfp_filter_conf_set(const vtss_inst_t             inst,
                                  const vtss_psfp_filter_id_t   id,
                                  const vtss_psfp_filter_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_psfp_filter_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.psfp.filter[id] = *conf;
        rc = VTSS_FUNC(l2.psfp_filter_conf_set, id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_psfp_filter_status_get(const vtss_inst_t           inst,
                                    const vtss_psfp_filter_id_t id,
                                    vtss_psfp_filter_status_t   *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_psfp_filter_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(l2.psfp_filter_status_get, id, status);
    }
    VTSS_EXIT();
    return rc;
}
#endif

#if defined(VTSS_EVC_STAT_CNT)
static void vtss_cmn_cnt_copy(vtss_chip_counter_pair_t *old, vtss_chip_counter_pair_t *new)
{
    new->frames.value = old->frames.value;
    new->bytes.value = old->bytes.value;
}

static vtss_rc vtss_cmn_pol_move(vtss_state_t *vtss_state, u16 idx_old, u16 idx_new, u16 count)
{
    vtss_sdx_info_t  *sdx_info = &vtss_state->l2.sdx_info;
    vtss_sdx_entry_t *sdx;
    u16              i, *idx;

    VTSS_I("move idx_old: %u to idx_new: %u", idx_old, idx_new);

    /* Move policers */
    for (i = 0; i < count; i++) {
        vtss_state->l2.pol_conf[idx_new + i] = vtss_state->l2.pol_conf[idx_old + i];
        VTSS_FUNC_RC(l2.policer_update, idx_new + i);
    }

    /* Update ISDX entries referring to the old index */
    for (i = 0; i < sdx_info->max_count; i++) {
        sdx = &sdx_info->isdx.table[i];
        idx = &sdx->pol_idx;
        if (sdx->port_no != VTSS_PORT_NO_NONE && *idx == idx_old) {
            *idx = idx_new;
            VTSS_FUNC_RC(l2.isdx_update, sdx);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_cmn_pol_clear(vtss_state_t *vtss_state, u16 idx)
{
    vtss_dlb_policer_conf_t *conf;

    /* Clear and update policer configuration */
    conf = &vtss_state->l2.pol_conf[idx];
    VTSS_MEMSET(conf, 0, sizeof(*conf));
    return VTSS_FUNC(l2.policer_update, idx);
}

static vtss_rc vtss_cmn_istat_move(vtss_state_t *vtss_state, u16 idx_old, u16 idx_new, u16 count)
{
    vtss_sdx_info_t  *sdx_info = &vtss_state->l2.sdx_info;
    vtss_sdx_entry_t *sdx;
    vtss_stat_idx_t  stat_idx;
    u16              i, *idx;

    VTSS_I("move idx_old: %u to idx_new: %u", idx_old, idx_new);

    /* Move statistics */
    for (i = 0; i < count; i++) {
        vtss_sdx_counters_t *c_old = &sdx_info->sdx_table[idx_old + i];
        vtss_sdx_counters_t *c_new = &sdx_info->sdx_table[idx_new + i];

        /* Read old and new counters, then copy counters */
        stat_idx.idx = (idx_old + i);
        stat_idx.edx = 0;
        VTSS_FUNC_RC(l2.counters_update, &stat_idx, FALSE);
        stat_idx.idx = (idx_new + i);
        stat_idx.edx = 0;
        VTSS_FUNC_RC(l2.counters_update, &stat_idx, FALSE);
        vtss_cmn_cnt_copy(&c_old->rx_green, &c_new->rx_green);
        vtss_cmn_cnt_copy(&c_old->rx_yellow, &c_new->rx_yellow);
        vtss_cmn_cnt_copy(&c_old->rx_red, &c_new->rx_red);
        vtss_cmn_cnt_copy(&c_old->rx_discard, &c_new->rx_discard);
        vtss_cmn_cnt_copy(&c_old->tx_discard, &c_new->tx_discard);
    }

    /* Update ISDX entries referring to the old index */
    for (i = 0; i < sdx_info->max_count; i++) {
        sdx = &sdx_info->isdx.table[i];
        idx = &sdx->stat_idx;
        if (sdx->port_no != VTSS_PORT_NO_NONE && *idx == idx_old) {
            *idx = idx_new;
            VTSS_FUNC_RC(l2.isdx_update, sdx);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_cmn_istat_clear(vtss_state_t *vtss_state, u16 idx)
{
    vtss_stat_idx_t stat_idx;

    /* Clear SDX counters */
    stat_idx.idx = idx;
    stat_idx.edx = 0;
    return VTSS_FUNC(l2.counters_update, &stat_idx, TRUE);
}

static vtss_rc vtss_cmn_estat_move(vtss_state_t *vtss_state, u16 idx_old, u16 idx_new, u16 count)
{
    vtss_sdx_info_t *sdx_info = &vtss_state->l2.sdx_info;
    vtss_stat_idx_t stat_idx;
    u16             i;

    VTSS_I("move idx_old: %u to idx_new: %u", idx_old, idx_new);

    /* Move statistics */
    for (i = 0; i < count; i++) {
        vtss_sdx_counters_t *c_old = &sdx_info->sdx_table[idx_old + i];
        vtss_sdx_counters_t *c_new = &sdx_info->sdx_table[idx_new + i];

        /* Read old and new counters, then copy counters */
        stat_idx.idx = 0;
        stat_idx.edx = (idx_old + i);
        VTSS_FUNC_RC(l2.counters_update, &stat_idx, FALSE);
        stat_idx.idx = 0;
        stat_idx.edx = (idx_new + i);
        VTSS_FUNC_RC(l2.counters_update, &stat_idx, FALSE);
        vtss_cmn_cnt_copy(&c_old->tx_green, &c_new->tx_green);
        vtss_cmn_cnt_copy(&c_old->tx_yellow, &c_new->tx_yellow);
    }
    return VTSS_FUNC(vcap.es0_esdx_update, idx_old, idx_new);
}

static vtss_rc vtss_cmn_estat_clear(vtss_state_t *vtss_state, u16 idx)
{
    vtss_stat_idx_t stat_idx;

    /* Clear SDX counters */
    stat_idx.idx = 0;
    stat_idx.edx = idx;
    return VTSS_FUNC(l2.counters_update, &stat_idx, TRUE);
}

static vtss_rc vtss_xrow_free(vtss_state_t *vtss_state, vtss_xrow_header_t *hdr, u16 *idx)
{
    vtss_xrow_entry_t  *row;
    vtss_xcol_entry_t  *col;
    u16                row_idx, col_idx;
    u8                 size;

    if (*idx == VTSS_POL_STAT_NONE) {
        /* Silently ignore if already free */
        return VTSS_RC_OK;
    }

    if (*idx >= hdr->max_count) {
        VTSS_E("%s, illegal idx: %u, max_count: %u", hdr->name, *idx, hdr->max_count);
        return VTSS_RC_ERROR;
    }

    row_idx = (*idx / 8);
    row = (hdr->row + row_idx);
    size = row->size;
    if (size == 0) {
        VTSS_E("%s, unused row, idx: %u, row_idx: %u", hdr->name, *idx, row_idx);
        return VTSS_RC_ERROR;
    }

    col_idx = (*idx % 8);
    col = &row->col[col_idx];
    if (!col->used) {
        VTSS_E("%s, already free, idx: %u, row_idx: %u, col_idx: %u", hdr->name, *idx, row_idx, col_idx);
        return VTSS_RC_ERROR;
    }

    col->used = FALSE;
    hdr->count -= size;
    hdr->count_size[size] -= size;
    row->count -= size;
    if (row->count == 0) {
        row->size = 0;
    }
    VTSS_I("%s, free idx: %u, row_idx: %u, col_idx: %u", hdr->name, *idx, row_idx, col_idx);
    *idx = VTSS_POL_STAT_NONE;

    return VTSS_RC_OK;
}

static vtss_rc vtss_xrow_alloc(vtss_state_t *vtss_state, vtss_xrow_header_t *hdr, u8 count, u16 *idx)
{
#if VTSS_OPT_TRACE
    const              char *txt;
#endif
    vtss_xrow_entry_t  *row, *row_free;
    vtss_xcol_entry_t  *col;
    u16                row_idx, row_max = (hdr->max_count / 8), row_new = row_max;
    u16                col_idx, idx_new, idx_old, i;
    u8                 size;
    BOOL               clear = TRUE;
    char               *p1, *p2;
    struct {
        u16 free_count; /* Number of free entries */
        u16 row_idx;    /* Index of row with smallest number of used entries */
        u16 col_idx;    /* Index of column of next used entry */
        u16 row_count;  /* Smallest number of used entries */
    } info[8 + 1], *pi; /* Info per size (1/2/4/8), allow 1-based indexing */

    VTSS_MEMSET(info, 0, sizeof(info));

    if (count == 0) {
        /* Silently ignore if no allocation required */
        *idx = VTSS_POL_STAT_NONE;
        return VTSS_RC_OK;
    }

    if (*idx != VTSS_POL_STAT_NONE) {
        /* Try to reallocate index */
        if (*idx < hdr->max_count) {
            row_idx = (*idx / 8);
            col_idx = (*idx % 8);
            row = (hdr->row + row_idx);
            if (row->size == count && row->col[col_idx].used) {
                /* Reuse row and column */
                hdr->count -= count;
                hdr->count_size[count] -= count;
                row->count -= count;
#if VTSS_OPT_TRACE
                txt = "reallocate";
#endif
                clear = FALSE;
                goto alloc_ok;
            }
        }

        /* Free entry */
        VTSS_RC(vtss_xrow_free(vtss_state, hdr, idx));
    }

    /* Reuse row or find free row or free columns */
    for (row_idx = 0; row_idx < row_max; row_idx++) {
        row = (hdr->row + row_idx);
        if ((size = row->size) != 0) {
            pi = &info[size];
            if (pi->row_count == 0 || row->count < pi->row_count) {
                /* Row with fewer used entries found */
                pi->row_count = row->count;
                pi->row_idx = row_idx;
            }
            for (col_idx = 0; col_idx < 8; col_idx += size) {
                if (row->col[col_idx].used) {
                    /* Skip used column */
                } else if (size == count) {
#if VTSS_OPT_TRACE
                    txt = "new column";
#endif
                            goto alloc_ok;
                } else {
                    pi->free_count += size;
                }
            }
        } else if (row_new == row_max) {
            /* First free row found */
            row_new = row_idx;
        }
    }

    /* Allocate new row and column */
    if (row_new < row_max) {
        row_idx = row_new;
        col_idx = 0;
#if VTSS_OPT_TRACE
        txt = "new row";
#endif
        goto alloc_ok;
    }

    /* Last resort, check if allocations can be moved to free up a row */
    for (size = 4; size > 0; size--) {
        pi = &info[size];
        if (pi->free_count > 7) {
            break;
        }
    }
    if (size > 0 && pi->row_idx != 0) {
        VTSS_I("%s, freeing row_idx: %u, size: %u", hdr->name, pi->row_idx, size);
        row_free = (hdr->row + pi->row_idx);
        pi->col_idx = 8;
        for (col_idx = 0; col_idx < 8; col_idx += size) {
            if (row_free->col[col_idx].used) {
                /* Found first used column to be moved */
                VTSS_I("freeing col: %u", col_idx);
                pi->col_idx = col_idx;
                break;
            }
        }
        for (row_idx = 0; row_idx < row_max && pi->col_idx < 8; row_idx++) {
            row = (hdr->row + row_idx);
            if (row->size != size || row_idx == pi->row_idx) {
                continue;
            }
            for (col_idx = 0; col_idx < 8 && pi->col_idx < 8; col_idx += size) {
                col = &row->col[col_idx];
                if (col->used) {
                    continue;
                }
                VTSS_I("%s, move row/col: %u/%u to row/col: %u/%u", hdr->name, pi->row_idx, pi->col_idx, row_idx, col_idx);
                idx_old = (pi->row_idx * 8 + pi->col_idx);
                idx_new = (row_idx * 8 + col_idx);
                VTSS_RC(hdr->move(vtss_state, idx_old, idx_new, size));
                *col = row_free->col[pi->col_idx];
                if (col->ref != NULL) {
                    *(col->ref) = idx_new;
                }
                row->count += size;
                for (pi->col_idx++; pi->col_idx < 8; pi->col_idx++) {
                    if (row_free->col[col_idx].used) {
                        break;
                    }
                }
            }
        }
#if VTSS_OPT_TRACE
        txt = "freed row";
#endif
        row_free->count = 0;
        row_idx = pi->row_idx;
        col_idx = 0;
        goto alloc_ok;
    }

    VTSS_E("%s, no free idx", hdr->name);
    return VTSS_RC_ERROR;

alloc_ok:
    hdr->count += count;
    hdr->count_size[count] += count;
    row = (hdr->row + row_idx);
    row->size = count;
    row->count += count;
    col = &row->col[col_idx];
    col->used = TRUE;
    p1 = (char *)idx;
    p2 = (char *)vtss_state;
    col->ref = (p1 > p2 && p1 < (p2 + sizeof(*vtss_state)) ? idx : NULL);
    *idx = (row_idx * 8 + col_idx);
    VTSS_I("%s, %s, row: %u, col: %u, idx: %u, count: %u", hdr->name, txt, row_idx, col_idx, *idx, count);
    for (i = 0; clear && i < count; i++) {
        if (hdr->clear) {
            VTSS_RC(hdr->clear(vtss_state, *idx + i));
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cmn_policer_alloc(vtss_state_t *vtss_state, u8 count, u16 *idx)
{
    return vtss_xrow_alloc(vtss_state, &vtss_state->l2.pol_table.hdr, count, idx);
}

vtss_rc vtss_cmn_policer_free(vtss_state_t *vtss_state, u16 *idx)
{
    return vtss_xrow_free(vtss_state, &vtss_state->l2.pol_table.hdr, idx);
}

vtss_rc vtss_cmn_istat_alloc(vtss_state_t *vtss_state, u8 count, u16 *idx)
{
    return vtss_xrow_alloc(vtss_state, &vtss_state->l2.istat_table.hdr, count, idx);
}

vtss_rc vtss_cmn_istat_free(vtss_state_t *vtss_state, u16 *idx)
{
    return vtss_xrow_free(vtss_state, &vtss_state->l2.istat_table.hdr, idx);
}

vtss_rc vtss_cmn_estat_alloc(vtss_state_t *vtss_state, u8 count, u16 *idx)
{
    return vtss_xrow_alloc(vtss_state, &vtss_state->l2.estat_table.hdr, count, idx);
}

vtss_rc vtss_cmn_estat_free(vtss_state_t *vtss_state, u16 *idx)
{
    return vtss_xrow_free(vtss_state, &vtss_state->l2.estat_table.hdr, idx);
}

#if defined(VTSS_FEATURE_FRER)
static vtss_rc vtss_mstream_move(vtss_state_t *vtss_state, u16 idx_old, u16 idx_new, u16 count)
{
    vtss_sdx_info_t  *sdx_info = &vtss_state->l2.sdx_info;
    vtss_sdx_entry_t *sdx;
    u16              i, *idx;

    VTSS_I("move idx_old: %u to idx_new: %u", idx_old, idx_new);

    /* Move streams */
    for (i = 0; i < count; i++) {
        vtss_state->l2.mstream_conf[idx_new + i] = vtss_state->l2.mstream_conf[idx_old + i];
        VTSS_FUNC_RC(l2.mstream_conf_set, idx_new + i);
    }

    /* Update ISDX entries referring to the old index */
    for (i = 0; i < sdx_info->max_count; i++) {
        sdx = &sdx_info->isdx.table[i];
        idx = &sdx->ms_idx;
        if (sdx->port_no != VTSS_PORT_NO_NONE && *idx == idx_old) {
            *idx = idx_new;
            VTSS_FUNC_RC(l2.isdx_update, sdx);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_mstream_clear(vtss_state_t *vtss_state, u16 idx)
{
    vtss_frer_stream_conf_t *conf;

    /* Clear and update stream */
    conf = &vtss_state->l2.mstream_conf[idx];
    VTSS_MEMSET(conf, 0, sizeof(*conf));
    return VTSS_FUNC(l2.mstream_conf_set, idx);
}
#endif

static vtss_rc vtss_l2_pol_stat_create(vtss_state_t *vtss_state)
{
    vtss_l2_state_t    *state = &vtss_state->l2;
    vtss_xrow_header_t *hdr;
    u16                dummy, cnt;

#if defined(VTSS_ARCH_LAN966X)
    cnt = 0;
#else
    /* Dummy blocks of 8 instances are reserved for normal/default traffic */
    cnt = 8;
#endif

    hdr = &state->pol_table.hdr;
    hdr->name = "policer";
    hdr->max_count = VTSS_EVC_POL_CNT;
    hdr->row = state->pol_table.row;
    dummy = VTSS_POL_STAT_NONE;
    VTSS_RC(vtss_xrow_alloc(vtss_state, hdr, cnt, &dummy));
    hdr->move = vtss_cmn_pol_move;
    hdr->clear = vtss_cmn_pol_clear;

    hdr = &state->istat_table.hdr;
    hdr->name = "istat";
    hdr->max_count = VTSS_EVC_STAT_CNT;
    hdr->row = state->istat_table.row;
    dummy = VTSS_POL_STAT_NONE;
    VTSS_RC(vtss_xrow_alloc(vtss_state, hdr, cnt, &dummy));
    hdr->move = vtss_cmn_istat_move;
    hdr->clear = vtss_cmn_istat_clear;

#if defined(VTSS_ARCH_LAN966X)
    cnt = 1;
#endif
    hdr = &state->estat_table.hdr;
    hdr->name = "estat";
    hdr->max_count = VTSS_EVC_STAT_CNT;
    hdr->row = state->estat_table.row;
    dummy = VTSS_POL_STAT_NONE;
    VTSS_RC(vtss_xrow_alloc(vtss_state, hdr, cnt, &dummy));
    hdr->move = vtss_cmn_estat_move;
    hdr->clear = vtss_cmn_estat_clear;

#if defined(VTSS_FEATURE_FRER)
    cnt = 8;
    hdr = &state->ms_table.hdr;
    hdr->name = "mstream";
    hdr->max_count = VTSS_MSTREAM_CNT;
    hdr->row = state->ms_table.row;
    dummy = VTSS_POL_STAT_NONE;
    VTSS_RC(vtss_xrow_alloc(vtss_state, hdr, cnt, &dummy));
    hdr->move = vtss_mstream_move;
    hdr->clear = vtss_mstream_clear;
#endif
    return VTSS_RC_OK;
}
#endif /* VTSS_EVC_STAT_CNT */

#if defined(VTSS_FEATURE_XSTAT)

/* - Ingress counters ---------------------------------------------- */

static vtss_rc vtss_class_cnt_get(const vtss_class_cnt_t class_cnt, u8 *cnt)
{
#if defined(VTSS_ARCH_LAN966X)
    // Only one class supported
    if (class_cnt != 1) {
        VTSS_E("illegal class count: %u", class_cnt);
        return VTSS_RC_ERROR;
    }
    *cnt = class_cnt;
#else
    if (class_cnt == 0 || class_cnt > 8) {
        VTSS_E("illegal class count: %u", class_cnt);
        return VTSS_RC_ERROR;
    } else if (class_cnt < 3) {
        /* 1 or 2 classes */
        *cnt = class_cnt;
    } else if (class_cnt < 5) {
        /* 3/4 classes */
        *cnt = 4;
    } else {
        /* 8 classes */
        *cnt = 8;
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_ingress_cnt_alloc(const vtss_inst_t      inst,
                               const vtss_class_cnt_t class_cnt,
                               vtss_ingress_cnt_id_t  *const id)
{
    vtss_state_t       *vtss_state;
    vtss_xstat_entry_t *stat;
    vtss_rc            rc;
    u8                 cnt;
    u16                i;

    VTSS_RC(vtss_class_cnt_get(class_cnt, &cnt));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_RC_ERROR;
        for (i = 0; i < VTSS_EVC_STAT_CNT; i++) {
            stat = &vtss_state->l2.istat.table[i];
            if (stat->cnt == 0) {
                if ((rc = vtss_cmn_istat_alloc(vtss_state, cnt, &stat->idx)) == VTSS_RC_OK) {
                    stat->cnt = cnt;
                    *id = i;
                }
                break;
            }
        }
        if (rc == VTSS_RC_ERROR) {
            VTSS_I("no free ingress counters found");
        }
    }
    VTSS_EXIT();
    return rc;
}

static vtss_xstat_entry_t *vtss_istat_lookup(vtss_state_t *vtss_state,
                                             const vtss_ingress_cnt_id_t id,
                                             BOOL error)
{
    vtss_xstat_entry_t *stat;

    if (id >= VTSS_EVC_STAT_CNT) {
        VTSS_E("illegal id: %u", id);
        return NULL;
    }
    stat = &vtss_state->l2.istat.table[id];
    if (stat->cnt == 0) {
        if (error) {
            VTSS_E("free id: %u", id);
        }
        return NULL;
    }
    return stat;
}

vtss_rc vtss_ingress_cnt_free(const vtss_inst_t           inst,
                              const vtss_ingress_cnt_id_t id)
{
    vtss_state_t       *vtss_state;
    vtss_xstat_entry_t *stat;
    vtss_rc            rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((stat = vtss_istat_lookup(vtss_state, id, 1)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            rc = vtss_cmn_istat_free(vtss_state, &stat->idx);
            stat->cnt = 0;
            stat->sdx = 0;
        }
    }
    VTSS_EXIT();
    return rc;
}

static u16 vtss_icnt_idx(vtss_xstat_entry_t *stat, vtss_cosid_t cosid)
{
#if defined(VTSS_ARCH_LAN966X)
    return stat->sdx;
#else
    return (stat->idx + cosid);
#endif
}

vtss_rc vtss_ingress_cnt_get(const vtss_inst_t           inst,
                             const vtss_ingress_cnt_id_t id,
                             const vtss_cosid_t          cosid,
                             vtss_ingress_counters_t     *counters)
{
    vtss_state_t       *vtss_state;
    vtss_xstat_entry_t *stat;
    vtss_rc            rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((stat = vtss_istat_lookup(vtss_state, id, 1)) != NULL && cosid < stat->cnt) {
            rc = VTSS_FUNC(l2.icnt_get, vtss_icnt_idx(stat, cosid), counters);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ingress_cnt_clear(const vtss_inst_t           inst,
                               const vtss_ingress_cnt_id_t id,
                               const vtss_cosid_t          cosid)
{
    vtss_state_t       *vtss_state;
    vtss_xstat_entry_t *stat;
    vtss_rc            rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((stat = vtss_istat_lookup(vtss_state, id, 1)) != NULL && cosid < stat->cnt) {
            rc = VTSS_FUNC(l2.icnt_get, vtss_icnt_idx(stat, cosid), NULL);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_XSTAT */

#if defined(VTSS_FEATURE_XDLB)

/* - Dual Leaky Bucket policers ------------------------------------ */

vtss_rc vtss_dlb_policer_alloc(const vtss_inst_t      inst,
                               const vtss_class_cnt_t class_cnt,
                               vtss_dlb_policer_id_t  *const id)
{
    vtss_state_t      *vtss_state;
    vtss_xpol_entry_t *pol;
    vtss_rc           rc;
    u8                cnt;
    u16               i;

    VTSS_RC(vtss_class_cnt_get(class_cnt, &cnt));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_RC_ERROR;
        for (i = 0; i < VTSS_EVC_POL_CNT; i++) {
            pol = &vtss_state->l2.pol.table[i];
            if (pol->cnt == 0) {
                if ((rc = vtss_cmn_policer_alloc(vtss_state, cnt, &pol->idx)) == VTSS_RC_OK) {
                    pol->cnt = cnt;
                    *id = i;
                }
                break;
            }
        }
        if (rc == VTSS_RC_ERROR) {
            VTSS_I("no free policers found");
        }
    }
    VTSS_EXIT();
    return rc;
}

static vtss_xpol_entry_t *vtss_pol_lookup(vtss_state_t *vtss_state,
                                          const vtss_dlb_policer_id_t id)
{
    vtss_xpol_entry_t *pol;

    if (id >= VTSS_EVC_POL_CNT) {
        VTSS_E("illegal id: %u", id);
        return NULL;
    }
    pol = &vtss_state->l2.pol.table[id];
    if (pol->cnt == 0) {
        VTSS_E("free id: %u", id);
        return NULL;
    }
    return pol;
}

vtss_rc vtss_dlb_policer_free(const vtss_inst_t           inst,
                              const vtss_dlb_policer_id_t id)
{
    vtss_state_t      *vtss_state;
    vtss_xpol_entry_t *pol;
    vtss_rc           rc;
    vtss_dlb_policer_conf_t  *conf;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((pol = vtss_pol_lookup(vtss_state, id)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            /* Disable policers in CIL */
            for(u32 i = 0; i < pol->cnt; ++i) {
                conf = &vtss_state->l2.pol_conf[pol->idx + i];
                if (conf->enable == TRUE) {
                    conf->enable = FALSE;
                    vtss_state->l2.pol_conf[pol->idx + i] = *conf;
                    rc = VTSS_FUNC(l2.policer_update, pol->idx + i);
                }
            }
            rc = vtss_cmn_policer_free(vtss_state, &pol->idx);
            pol->cnt = 0;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_dlb_policer_conf_get(const vtss_inst_t           inst,
                                  const vtss_dlb_policer_id_t id,
                                  const vtss_cosid_t          cosid,
                                  vtss_dlb_policer_conf_t     *const conf)
{
    vtss_state_t      *vtss_state;
    vtss_xpol_entry_t *pol;
    vtss_rc           rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((pol = vtss_pol_lookup(vtss_state, id)) != NULL && cosid < pol->cnt) {
            *conf = vtss_state->l2.pol_conf[pol->idx + cosid];
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_dlb_policer_conf_set(const vtss_inst_t             inst,
                                  const vtss_dlb_policer_id_t   id,
                                  const vtss_cosid_t            cosid,
                                  const vtss_dlb_policer_conf_t *const conf)
{
    vtss_state_t      *vtss_state;
    vtss_xpol_entry_t *pol;
    vtss_rc           rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((pol = vtss_pol_lookup(vtss_state, id)) != NULL && cosid < pol->cnt) {
            vtss_state->l2.pol_conf[pol->idx + cosid] = *conf;
            rc = VTSS_FUNC(l2.policer_update, pol->idx + cosid);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_PSFP)
vtss_rc vtss_dlb_policer_status_get(const vtss_inst_t           inst,
                                    const vtss_dlb_policer_id_t id,
                                    const vtss_cosid_t          cosid,
                                    vtss_dlb_policer_status_t   *const status)
{
    vtss_state_t      *vtss_state;
    vtss_xpol_entry_t *pol;
    vtss_rc           rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((pol = vtss_pol_lookup(vtss_state, id)) != NULL && cosid < pol->cnt) {
            rc = VTSS_FUNC(l2.policer_status_get, pol->idx + cosid, status);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_PSFP */

#endif /* VTSS_FEATURE_XDLB */

#if defined(VTSS_FEATURE_FRER)
static vtss_rc vtss_frer_cstream_id_check(const vtss_frer_cstream_id_t id)
{
    if (id < VTSS_CSTREAM_CNT) {
        return VTSS_RC_OK;
    }
    VTSS_E("illegal cstream id: %u", id);
    return VTSS_RC_ERROR;
}

vtss_rc vtss_frer_cstream_conf_get(const vtss_inst_t            inst,
                                   const vtss_frer_cstream_id_t id,
                                   vtss_frer_stream_conf_t      *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_frer_cstream_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->l2.cstream_conf[id];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_frer_cstream_conf_set(const vtss_inst_t             inst,
                                   const vtss_frer_cstream_id_t  id,
                                   const vtss_frer_stream_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_frer_cstream_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->l2.cstream_conf[id] = *conf;
        rc = VTSS_FUNC(l2.cstream_conf_set, id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_frer_cstream_cnt_get(const vtss_inst_t            inst,
                                  const vtss_frer_cstream_id_t id,
                                  vtss_frer_counters_t         *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_frer_cstream_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(l2.cstream_cnt_get, id, counters);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_frer_cstream_cnt_clear(const vtss_inst_t            inst,
                                    const vtss_frer_cstream_id_t id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_frer_cstream_id_check(id));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(l2.cstream_cnt_get, id, NULL);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_ARCH_LAN966X)
#define VTSS_FRER_EGR_PORT_CNT 4
#else
#define VTSS_FRER_EGR_PORT_CNT 8
#endif

vtss_rc vtss_frer_mstream_alloc(const vtss_inst_t      inst,
                                const BOOL             port_list[VTSS_PORTS],
                                vtss_frer_mstream_id_t *const id)
{
    vtss_state_t     *vtss_state;
    vtss_xms_entry_t *ms;
    vtss_rc          rc;
    vtss_port_no_t   port_no;
    u8               cnt = 0;
    u16              i;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_RC_ERROR;
        for (i = 0; i < VTSS_MSTREAM_CNT; i++) {
            ms = &vtss_state->l2.ms.table[i];
            if (ms->cnt == 0) {
                VTSS_PORT_BF_CLR(ms->port_list);
                for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                    if (port_list[port_no]) {
                        VTSS_PORT_BF_SET(ms->port_list, port_no, 1);
                        cnt++;
                    }
                }
                if (cnt == 0 || cnt > VTSS_FRER_EGR_PORT_CNT) {
                    VTSS_E("illegal port count: %u", cnt)
                } else if ((rc = vtss_xrow_alloc(vtss_state, &vtss_state->l2.ms_table.hdr, cnt, &ms->idx)) == VTSS_RC_OK) {
                    ms->cnt = cnt;
                    *id = i;
                }
                break;
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

static vtss_xms_entry_t *vtss_ms_lookup(vtss_state_t *vtss_state,
                                        const vtss_frer_mstream_id_t id)
{
    vtss_xms_entry_t *ms;

    if (id >= VTSS_MSTREAM_CNT) {
        VTSS_E("illegal id: %u", id);
        return NULL;
    }
    ms = &vtss_state->l2.ms.table[id];
    if (ms->cnt == 0) {
        VTSS_E("free id: %u", id);
        return NULL;
    }
    return ms;
}

static u16 vtss_ms_idx_lookup(vtss_state_t *vtss_state,
                              const vtss_frer_mstream_id_t id,
                              const vtss_port_no_t port_no)
{
    vtss_xms_entry_t *ms = vtss_ms_lookup(vtss_state, id);
    vtss_port_no_t   port;
    u16              idx = 0;

    if (ms != NULL) {
        if (VTSS_PORT_BF_GET(ms->port_list, port_no) == 0) {
            VTSS_E("id: %u, port_no: %u not enabled", id, port_no);
        } else {
            idx = ms->idx;
            for (port = 0; port < port_no; port++) {
                if (VTSS_PORT_BF_GET(ms->port_list, port)) {
                    idx++;
                }
            }
        }
    }
    return idx;
}

vtss_rc vtss_frer_mstream_free(const vtss_inst_t            inst,
                               const vtss_frer_mstream_id_t id)
{
    vtss_state_t     *vtss_state;
    vtss_xms_entry_t *ms;
    vtss_rc          rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((ms = vtss_ms_lookup(vtss_state, id)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            rc = vtss_xrow_free(vtss_state, &vtss_state->l2.ms_table.hdr, &ms->idx);
            ms->cnt = 0;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_frer_mstream_conf_get(const vtss_inst_t            inst,
                                   const vtss_frer_mstream_id_t id,
                                   const vtss_port_no_t         port_no,
                                   vtss_frer_stream_conf_t      *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    u16          idx;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if ((idx = vtss_ms_idx_lookup(vtss_state, id, port_no)) == 0) {
            rc = VTSS_RC_ERROR;
        } else {
            *conf = vtss_state->l2.mstream_conf[idx];
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_frer_mstream_conf_set(const vtss_inst_t             inst,
                                   const vtss_frer_mstream_id_t  id,
                                   const vtss_port_no_t          port_no,
                                   const vtss_frer_stream_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    u16          idx;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if ((idx = vtss_ms_idx_lookup(vtss_state, id, port_no)) == 0) {
            rc = VTSS_RC_ERROR;
        } else {
            vtss_state->l2.mstream_conf[idx] = *conf;
            rc = VTSS_FUNC(l2.mstream_conf_set, idx);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_frer_mstream_cnt_get(const vtss_inst_t            inst,
                                  const vtss_frer_mstream_id_t id,
                                  const vtss_port_no_t         port_no,
                                  vtss_frer_counters_t         *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    u16          idx;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if ((idx = vtss_ms_idx_lookup(vtss_state, id, port_no)) == 0) {
            rc = VTSS_RC_ERROR;
        } else {
            rc = VTSS_FUNC(l2.mstream_cnt_get, idx, counters);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_frer_mstream_cnt_clear(const vtss_inst_t            inst,
                                    const vtss_frer_mstream_id_t id,
                                    const vtss_port_no_t         port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    u16          idx;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if ((idx = vtss_ms_idx_lookup(vtss_state, id, port_no)) == 0) {
            rc = VTSS_RC_ERROR;
        } else {
            rc = VTSS_FUNC(l2.mstream_cnt_get, idx, NULL);
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_FRER */

#if defined(VTSS_FEATURE_XFLOW)

/* - Ingress flow -------------------------------------------------- */

vtss_rc vtss_iflow_alloc(const vtss_inst_t inst,
                         vtss_iflow_id_t   *const id)
{
    vtss_state_t      *vtss_state;
    vtss_rc           rc;
    vtss_sdx_entry_t  *sdx, **list, *cur, *prev = NULL;
    vtss_iflow_conf_t *conf;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((sdx = vtss_cmn_sdx_alloc(vtss_state, 0, 0, TRUE)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            /* Insert allocated entry in sorted list */
            list = &vtss_state->l2.sdx_info.iflow;
            for (cur = *list; cur != NULL; prev = cur, cur = cur->next) {
                if (cur->sdx > sdx->sdx) {
                    break;
                }
            }
            if (prev == NULL) {
                sdx->next = *list;
                *list = sdx;
            } else {
                sdx->next = prev->next;
                prev->next = sdx;
            }
            conf = &sdx->conf;
            VTSS_MEMSET(conf, 0, sizeof(*conf));
#if defined(VTSS_FEATURE_VOP)
            conf->voe_idx = VTSS_VOE_IDX_NONE;
#endif
#if defined(VTSS_FEATURE_VOP_V2)
            conf->voi_idx = VTSS_VOI_IDX_NONE;
#endif
            *id = sdx->sdx;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_iflow_free(const vtss_inst_t     inst,
                        const vtss_iflow_id_t id)
{
    vtss_state_t     *vtss_state;
    vtss_rc          rc;
    vtss_sdx_entry_t **list, *cur, *prev = NULL;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_RC_ERROR;
        list = &vtss_state->l2.sdx_info.iflow;
        for (cur = *list; cur != NULL; prev = cur, cur = cur->next) {
            if (cur->sdx == id) {
                if (prev == NULL) {
                    *list = cur->next;
                } else {
                    prev->next = cur->next;
                }
#if defined(VTSS_ARCH_LAN966X)
                if (cur->conf.cnt_enable) {
                    vtss_xstat_entry_t *stat = vtss_istat_lookup(vtss_state, cur->conf.cnt_id, 0);

                    if (stat != NULL) {
                        // Remove reference from ingress counters to flow
                        stat->sdx = 0;
                    }
                }
#endif
                vtss_cmn_sdx_free(vtss_state, cur, TRUE);
                rc = VTSS_RC_OK;
                break;
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_sdx_entry_t *vtss_iflow_lookup(vtss_state_t *vtss_state, vtss_iflow_id_t id)
{
    vtss_sdx_entry_t *cur;

    for (cur = vtss_state->l2.sdx_info.iflow; cur != NULL; cur = cur->next) {
        if (cur->sdx == id) {
            break;
        }
    }
    return cur;
}

vtss_rc vtss_iflow_conf_get(const vtss_inst_t     inst,
                            const vtss_iflow_id_t id,
                            vtss_iflow_conf_t     *const conf)
{
    vtss_state_t     *vtss_state;
    vtss_rc          rc;
    vtss_sdx_entry_t *sdx;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((sdx = vtss_iflow_lookup(vtss_state, id)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            *conf = sdx->conf;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_iflow_conf_set(const vtss_inst_t       inst,
                            const vtss_iflow_id_t   id,
                            const vtss_iflow_conf_t *const conf)
{
    vtss_state_t     *vtss_state;
    vtss_rc          rc;
    vtss_sdx_entry_t *sdx;
    u16              stat_idx = 0, pol_idx = 0, ms_idx = 0;
    u8               stat_cnt = 0, pol_cnt = 0, clear = 0;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((sdx = vtss_iflow_lookup(vtss_state, id)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
#if defined(VTSS_FEATURE_XDLB)
            if (conf->dlb_enable) {
                vtss_xpol_entry_t *pol = vtss_pol_lookup(vtss_state, conf->dlb_id);

                if (pol == NULL) {
                    rc = VTSS_RC_ERROR;
                } else {
                    pol_idx = pol->idx;
                    pol_cnt = pol->cnt;
                }
            }
#endif
#if defined(VTSS_FEATURE_FRER)
            if (conf->frer.mstream_enable) {
                vtss_xms_entry_t *ms = vtss_ms_lookup(vtss_state, conf->frer.mstream_id);

                if (ms == NULL) {
                    rc = VTSS_RC_ERROR;
                } else {
                    ms_idx = ms->idx;
                }
            }
#endif
#if defined(VTSS_FEATURE_XSTAT)
            if (conf->cnt_enable && rc == VTSS_RC_OK) {
                vtss_xstat_entry_t *stat = vtss_istat_lookup(vtss_state, conf->cnt_id, 1);

                if (stat == NULL) {
                    rc = VTSS_RC_ERROR;
                } else {
                    stat_idx = stat->idx;
                    stat_cnt = stat->cnt;
#if defined(VTSS_ARCH_LAN966X)
                    // Ingress counters can only be mapped to one flow
                    if (stat->sdx == 0) {
                        clear = 1;
                        stat->sdx = sdx->sdx;
                    } else if (stat->sdx != sdx->sdx) {
                        VTSS_E("cnt_id %u already mapped to iflow %u", conf->cnt_id, sdx->sdx);
                        rc = VTSS_RC_ERROR;
                    }
#endif
                }
            }
#endif
            if (rc == VTSS_RC_OK) {
                sdx->conf = *conf;
                sdx->stat_idx = stat_idx;
                sdx->stat_cnt = stat_cnt;
                sdx->pol_idx = pol_idx;
                sdx->pol_cnt = pol_cnt;
                sdx->ms_idx = ms_idx;
                rc = VTSS_FUNC(l2.iflow_conf_set, id);
                if (rc == VTSS_RC_OK && clear) {
#if defined(VTSS_FEATURE_XSTAT)
                    rc = vtss_cmn_istat_clear(vtss_state, sdx->sdx);
#endif
                }
            }
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_XFLOW */

#if defined(VTSS_FEATURE_VCAP)

/* - Tag Control List ---------------------------------------------- */

vtss_rc vtss_tce_init(const vtss_inst_t inst,
                      vtss_tce_t        *const tce)
{
    VTSS_MEMSET(tce, 0, sizeof(*tce));
    tce->action.inner_tag.tpid = VTSS_TPID_SEL_NONE;
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    tce->action.tag.map_id = VTSS_QOS_EGRESS_MAP_ID_NONE;
    tce->action.inner_tag.map_id = VTSS_QOS_EGRESS_MAP_ID_NONE;
#endif
    return VTSS_RC_OK;
}

/* Convert (TCE ID, port_no) to VCAP ID */
static vtss_vcap_id_t vtss_tce2id(vtss_tce_id_t tce_id, vtss_port_no_t port_no)
{
    vtss_vcap_id_t id = port_no;

    return ((id << 32) + tce_id);
}

/* Convert VCAP ID to (TCE ID, port_no) */
static void vtss_id2tce(vtss_vcap_id_t id, vtss_tce_id_t *tce_id, vtss_port_no_t *port_no)
{
    *tce_id = id;
    *port_no = (id >> 32);
}

static void vtss_tce2tag(const vtss_tce_tag_t *tce, vtss_es0_data_t *es0, BOOL outer)
{
    vtss_es0_action_t *action = &es0->entry->action;

    action->tag = (tce->tpid == VTSS_TPID_SEL_NONE ? VTSS_ES0_TAG_NONE : VTSS_ES0_TAG_ES0);
    action->tpid = (tce->tpid == VTSS_TPID_SEL_C ? VTSS_ES0_TPID_C :
                    tce->tpid == VTSS_TPID_SEL_S_CUSTOM ? VTSS_ES0_TPID_PORT : VTSS_ES0_TPID_S);

    if (tce->tpid == VTSS_TPID_SEL_PORT) {
        es0->flags |= (outer ? VTSS_ES0_FLAG_OT_VLAN : VTSS_ES0_FLAG_IT_VLAN);
    }
    if (tce->pcp_sel == VTSS_PCP_SEL_PORT) {
        es0->flags |= (outer ? VTSS_ES0_FLAG_OT_PCP : VTSS_ES0_FLAG_IT_PCP);
    }
    if (tce->dei_sel == VTSS_DEI_SEL_PORT) {
        es0->flags |= (outer ? VTSS_ES0_FLAG_OT_DEI : VTSS_ES0_FLAG_IT_DEI);
    }
#if defined(VTSS_ARCH_LUTON26)
    action->vid_b = tce->vid;
    action->qos = (tce->pcp_sel == VTSS_PCP_SEL_FIXED ? VTSS_ES0_QOS_ES0 :
                   tce->pcp_sel == VTSS_PCP_SEL_CLASSIFIED ? VTSS_ES0_QOS_CLASS : VTSS_ES0_QOS_MAPPED);
    action->pcp = tce->pcp;
    action->dei = tce->dei;
#else
    {
        vtss_es0_tag_conf_t *tag = (outer ? &action->outer_tag : &action->inner_tag);
        vtss_es0_sel_t      *sel = (outer ? &es0->ot : &es0->it);

        tag->tag = action->tag;
        tag->tpid = action->tpid;
        tag->vid.sel = (tce->vid ? TRUE : FALSE);
        tag->vid.val = tce->vid;
        sel->pcp = (tce->pcp_sel == VTSS_PCP_SEL_MAPPED ? VTSS_ES0_PCP_MAPPED :
                    tce->pcp_sel == VTSS_PCP_SEL_CLASSIFIED ? VTSS_ES0_PCP_CLASS : VTSS_ES0_PCP_ES0);
        tag->pcp.sel = sel->pcp;
        tag->pcp.val = tce->pcp;
        sel->dei = (tce->dei_sel == VTSS_DEI_SEL_MAPPED ? VTSS_ES0_DEI_MAPPED :
                    tce->dei_sel == VTSS_DEI_SEL_CLASSIFIED ? VTSS_ES0_DEI_CLASS : VTSS_ES0_DEI_ES0);
        tag->dei.sel = sel->dei;
        tag->dei.val = tce->dei;
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
        if (tce->map_id < VTSS_QOS_EGRESS_MAP_IDS) {
            if (outer) {
                es0->map_id_ot = tce->map_id;
                if (sel->pcp == VTSS_ES0_PCP_MAPPED) {
                    es0->flags |= VTSS_ES0_FLAG_MAP_OT_PCP;
                }
                if (sel->dei == VTSS_ES0_DEI_MAPPED) {
                    es0->flags |= VTSS_ES0_FLAG_MAP_OT_DEI;
                }
            } else {
                es0->map_id_it = tce->map_id;
                if (sel->pcp == VTSS_ES0_PCP_MAPPED) {
                    es0->flags |= VTSS_ES0_FLAG_MAP_IT_PCP;
                }
                if (sel->dei == VTSS_ES0_DEI_MAPPED) {
                    es0->flags |= VTSS_ES0_FLAG_MAP_IT_DEI;
                }
            }
        }
#endif
    }
#endif
}

static vtss_rc vtss_cmn_tce_add(vtss_state_t *vtss_state,
                                const vtss_tce_id_t tce_id,
                                const vtss_tce_t    *const tce)
{
    vtss_vcap_obj_t    *obj = &vtss_state->vcap.es0.obj;
    vtss_vcap_user_t   user = VTSS_ES0_USER_TCL;
    vtss_res_t         res;
    vtss_vcap_data_t   data;
    vtss_es0_entry_t   entry;
    vtss_es0_data_t    *es0 = &data.u.es0;
    vtss_vcap_entry_t  *cur;
    vtss_tce_id_t      cur_id;
    vtss_vcap_id_t     id, id_next = VTSS_VCAP_ID_LAST;
    vtss_port_no_t     port_no;
    BOOL               port_del[VTSS_PORTS];
#if defined(VTSS_FEATURE_XSTAT)
    vtss_xstat_entry_t *stat = NULL;
#endif
#if defined(VTSS_FEATURE_XFLOW)
    vtss_eflow_entry_t *eflow = NULL;

    VTSS_D("Enter");

    /* Check if egress flow ID is valid */
    if (tce->action.flow_id != VTSS_EFLOW_ID_NONE &&
        (eflow = vtss_eflow_lookup(vtss_state, tce->action.flow_id)) == NULL) {
        return VTSS_RC_ERROR;
    }
#endif

#if defined(VTSS_FEATURE_XSTAT)
    /* Check if egress counter ID is valid */
    if (eflow != NULL && eflow->conf.cnt_enable &&
        (stat = vtss_estat_lookup(vtss_state, eflow->conf.cnt_id)) == NULL) {
        return VTSS_RC_ERROR;
    }
#endif

    /* Check if ID is valid */
    if (tce->id == VTSS_VCAP_ID_LAST) {
        VTSS_E("tce id %u not allowed", tce->id);
        return VTSS_RC_ERROR;
    }

    /* Check resource consumption */
    vtss_cmn_res_init(&res);
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port_del[port_no] = 0;
        if (tce->key.port_list[port_no]) {
            res.es0.add++;
        }
    }
    for (cur = obj->used; cur != NULL; cur = cur->next) {
        if (cur->user == user) {
            vtss_id2tce(cur->id, &cur_id, &port_no);
            if (cur_id == tce->id) {
                res.es0.del++;
                if (!tce->key.port_list[port_no]) {
                    port_del[port_no] = 1;
                }
            }
            if (cur_id == tce_id && id_next == VTSS_VCAP_ID_LAST) {
                /* Found next ID */
                id_next = cur->id;
            }
        }
    }
    VTSS_RC(vtss_cmn_res_check(vtss_state, &res));

    /* Check if next ID is valid */
    if (tce_id != VTSS_TCE_ID_LAST && id_next == VTSS_VCAP_ID_LAST) {
        VTSS_E("tce_id %u not found", tce_id);
        return VTSS_RC_ERROR;
    }

    /* Delete resources */
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        if (port_del[port_no]) {
            id = vtss_tce2id(tce->id, port_no);
            VTSS_RC(vtss_vcap_del(vtss_state, obj, user, id));
        }
    }

    /* Add/update resources */
    vtss_vcap_es0_init(&data, &entry);
    if (tce->key.vid == VTSS_VID_NULL) {
        entry.key.vid_any = TRUE;
    } else {
        entry.key.data.vid.vid = tce->key.vid;
        es0->vid = tce->key.vid;
    }
#if defined(VTSS_FEATURE_XFLOW)
    if (tce->key.flow_enable) {
        entry.key.type = VTSS_ES0_TYPE_ISDX;
        entry.key.data.isdx.isdx_enable = 1;
        entry.key.data.isdx.isdx = tce->key.flow_id;
    }
    es0->flow_id = tce->action.flow_id;
    if (eflow != NULL) {
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        if (eflow->conf.voe_idx < VTSS_PORT_VOE_BASE_IDX) {      /* Do not point to a Port VOE */
            entry.action.mep_idx_enable = 1;
            entry.action.mep_idx = eflow->conf.voe_idx;
        }
#endif
#if defined(VTSS_FEATURE_VOP_V2)
        if (eflow->conf.voi_idx != VTSS_VOI_IDX_NONE) {
            entry.action.voi_idx = eflow->conf.voi_idx;
        }
#endif
    }
#if defined(VTSS_FEATURE_VOP_V2)
    entry.action.independent_mel = (eflow == NULL) || (eflow->conf.voe_idx == VTSS_VOE_IDX_NONE) ? TRUE : FALSE;
#endif
#if defined(VTSS_FEATURE_XSTAT)
    if (stat != NULL) {
        u32 cosid;

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
        es0->esdx = stat->idx;
#endif
        for (cosid = 0; cosid < 8; cosid++) {
            entry.action.esdx_cosid_offset |= ((cosid < stat->cnt ? cosid : (u32)(stat->cnt - 1)) << (cosid * 3));
        }
    }
#endif
#endif
    vtss_tce2tag(&tce->action.tag, es0, TRUE);
#if !defined(VTSS_ARCH_LUTON26)
    vtss_tce2tag(&tce->action.inner_tag, es0, FALSE);
#endif
    entry.action.pop_cnt = tce->action.pop_cnt;
#if defined(VTSS_FEATURE_FRER)
    entry.action.rtag = tce->action.rtag;
    if (entry.action.rtag.sel != VTSS_RTAG_SEL_NONE) {
        /* Always pop R-tag when pushing R-tag */
        entry.action.rtag.pop = TRUE;
    }
#endif
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        if (tce->key.port_list[port_no]) {
            entry.key.port_no = port_no;
            es0->port_no = port_no;
            id = vtss_tce2id(tce->id, port_no);
            VTSS_RC(vtss_vcap_add(vtss_state, obj, user, id, id_next, &data, 0));
            id_next = id;
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_cmn_tce_del(vtss_state_t *vtss_state,
                                const vtss_tce_id_t tce_id)
{
    vtss_vcap_obj_t   *obj = &vtss_state->vcap.es0.obj;
    vtss_vcap_user_t  user = VTSS_ES0_USER_TCL;
    vtss_vcap_entry_t *cur;
    vtss_tce_id_t     cur_id;
    vtss_vcap_id_t    id;
    vtss_port_no_t    port_no;
    BOOL              port_del[VTSS_PORTS];

    /* Look for TCEs and note the port numbers */
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port_del[port_no] = 0;
    }
    for (cur = obj->used; cur != NULL; cur = cur->next) {
        if (cur->user == user) {
            vtss_id2tce(cur->id, &cur_id, &port_no);
            if (cur_id == tce_id) {
                port_del[port_no] = 1;
            }
        }
    }
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        if (port_del[port_no]) {
            id = vtss_tce2id(tce_id, port_no);
            VTSS_RC(vtss_vcap_del(vtss_state, obj, user, id));
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_tce_add(const vtss_inst_t   inst,
                     const vtss_tce_id_t tce_id,
                     const vtss_tce_t    *const tce)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter");

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = vtss_cmn_tce_add(vtss_state, tce_id, tce);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_tce_del(const vtss_inst_t   inst,
                     const vtss_tce_id_t tce_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = vtss_cmn_tce_del(vtss_state, tce_id);
    }
    VTSS_EXIT();
    return rc;
}
#endif // VTSS_FEATURE_VCAP

#if defined(VTSS_FEATURE_XSTAT)

/* - Egress counters ----------------------------------------------- */

vtss_rc vtss_egress_cnt_alloc(const vtss_inst_t      inst,
                              const vtss_class_cnt_t class_cnt,
                              vtss_egress_cnt_id_t   *const id)
{
    vtss_state_t       *vtss_state;
    vtss_xstat_entry_t *stat;
    vtss_rc            rc;
    u8                 cnt;
    u16                i;

    VTSS_RC(vtss_class_cnt_get(class_cnt, &cnt));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_RC_ERROR;
        for (i = 0; i < VTSS_EVC_STAT_CNT; i++) {
            stat = &vtss_state->l2.estat.table[i];
            if (stat->cnt == 0) {
                if ((rc = vtss_cmn_estat_alloc(vtss_state, cnt, &stat->idx)) == VTSS_RC_OK) {
                    stat->cnt = cnt;
                    *id = i;
                }
                break;
            }
        }
        if (rc == VTSS_RC_ERROR) {
            VTSS_I("no free ingress counters found");
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_xstat_entry_t *vtss_estat_lookup(vtss_state_t *vtss_state, const vtss_egress_cnt_id_t id)
{
    vtss_xstat_entry_t *stat;

    if (id >= VTSS_EVC_STAT_CNT) {
        VTSS_E("illegal id: %u", id);
        return NULL;
    }
    stat = &vtss_state->l2.estat.table[id];
    if (stat->cnt == 0) {
        VTSS_E("free id: %u", id);
        return NULL;
    }
    return stat;
}

vtss_rc vtss_egress_cnt_free(const vtss_inst_t          inst,
                             const vtss_egress_cnt_id_t id)
{
    vtss_state_t       *vtss_state;
    vtss_xstat_entry_t *stat;
    vtss_rc            rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((stat = vtss_estat_lookup(vtss_state, id)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            rc = vtss_cmn_estat_free(vtss_state, &stat->idx);
            stat->cnt = 0;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_egress_cnt_get(const vtss_inst_t          inst,
                            const vtss_egress_cnt_id_t id,
                            const vtss_cosid_t         cosid,
                            vtss_egress_counters_t     *counters)
{
    vtss_state_t       *vtss_state;
    vtss_xstat_entry_t *stat;
    vtss_rc            rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((stat = vtss_estat_lookup(vtss_state, id)) != NULL && cosid < stat->cnt) {
            rc = VTSS_FUNC(l2.ecnt_get, stat->idx + cosid, counters);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_egress_cnt_clear(const vtss_inst_t          inst,
                              const vtss_egress_cnt_id_t id,
                              const vtss_cosid_t         cosid)
{
    vtss_state_t       *vtss_state;
    vtss_xstat_entry_t *stat;
    vtss_rc            rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((stat = vtss_estat_lookup(vtss_state, id)) != NULL && cosid < stat->cnt) {
            rc = VTSS_FUNC(l2.ecnt_get, stat->idx + cosid, NULL);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_XSTAT */

#if defined(VTSS_FEATURE_XFLOW)

/* - Egress flow --------------------------------------------------- */

vtss_eflow_entry_t *vtss_eflow_lookup(vtss_state_t *vtss_state, vtss_eflow_id_t id)
{
    vtss_eflow_entry_t *eflow;

    if (id >= VTSS_SDX_CNT || id == VTSS_EFLOW_ID_NONE) {
        VTSS_E("illegal id: %u", id);
        return NULL;
    }
    eflow = &vtss_state->l2.eflow[id - 1];
    if (eflow->used == 0) {
        VTSS_E("free id: %u", id);
        return NULL;
    }
    return eflow;
}

vtss_rc vtss_eflow_alloc(const vtss_inst_t inst,
                         vtss_eflow_id_t   *const id)
{
    vtss_state_t       *vtss_state;
    vtss_rc            rc;
    vtss_eflow_entry_t *eflow;
    vtss_eflow_conf_t  *conf;
    u16                i;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_RC_ERROR;
        for (i = 0; i < VTSS_SDX_CNT; i++) {
            eflow = &vtss_state->l2.eflow[i];
            if (!eflow->used) {
                eflow->used = 1;
                conf = &eflow->conf;
                VTSS_MEMSET(conf, 0, sizeof(*conf));
#if defined(VTSS_FEATURE_VOP)
                conf->voe_idx = VTSS_VOE_IDX_NONE;
#endif
#if defined(VTSS_FEATURE_VOP_V2)
                conf->voi_idx = VTSS_VOI_IDX_NONE;
#endif
                *id = (i + 1);
                rc = VTSS_RC_OK;
                break;
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_eflow_free(const vtss_inst_t     inst,
                        const vtss_eflow_id_t id)
{
    vtss_state_t       *vtss_state;
    vtss_rc            rc;
    vtss_eflow_entry_t *eflow;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((eflow = vtss_eflow_lookup(vtss_state, id)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            eflow->used = 0;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_eflow_conf_get(const vtss_inst_t     inst,
                            const vtss_eflow_id_t id,
                            vtss_eflow_conf_t     *const conf)
{
    vtss_state_t       *vtss_state;
    vtss_rc            rc;
    vtss_eflow_entry_t *eflow;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((eflow = vtss_eflow_lookup(vtss_state, id)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            *conf = eflow->conf;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_eflow_conf_set(const vtss_inst_t       inst,
                            const vtss_eflow_id_t   id,
                            const vtss_eflow_conf_t *const conf)
{
    vtss_state_t       *vtss_state;
    vtss_rc            rc;
    vtss_eflow_entry_t *eflow;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((eflow = vtss_eflow_lookup(vtss_state, id)) == NULL) {
            rc = VTSS_RC_ERROR;
        } else {
            eflow->conf = *conf;
            rc = VTSS_FUNC(vcap.es0_eflow_update, id);
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_XFLOW */

#if defined(VTSS_FEATURE_VCAP)

/* - VLAN translation ---------------------------------------------- */

static const char *vtss_vlan_trans_dir_txt(const vtss_vlan_trans_dir_t dir)
{
    return (dir == VTSS_VLAN_TRANS_DIR_BOTH ? "Both" :
            dir == VTSS_VLAN_TRANS_DIR_INGRESS ? "Ingress" :
            dir == VTSS_VLAN_TRANS_DIR_EGRESS ? "Egress" : "?");
}

vtss_rc vtss_vlan_trans_group_conf_add(const vtss_inst_t                     inst,
                                       const vtss_vlan_trans_grp2vlan_conf_t *conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("group_id: %u, vid: %u, trans_vid: %u, dir: %s",
           conf->group_id, conf->vid, conf->trans_vid, vtss_vlan_trans_dir_txt(conf->dir));

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(l2.vlan_trans_group_add, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_trans_group_conf_del(const vtss_inst_t                     inst,
                                       const vtss_vlan_trans_grp2vlan_conf_t *conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("group_id: %u, vid: %u, trans_vid: %u, dir: %s",
           conf->group_id, conf->vid, conf->trans_vid, vtss_vlan_trans_dir_txt(conf->dir));

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(l2.vlan_trans_group_del, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_trans_group_add(const vtss_inst_t      inst,
                                  const u16              group_id,
                                  const vtss_vid_t       vid,
                                  const vtss_vid_t       trans_vid)
{
    vtss_vlan_trans_grp2vlan_conf_t conf;

    conf.group_id = group_id;
    conf.vid = vid;
    conf.trans_vid = trans_vid;
    conf.dir = VTSS_VLAN_TRANS_DIR_BOTH;
    return vtss_vlan_trans_group_conf_add(inst, &conf);
}

vtss_rc vtss_vlan_trans_group_del(const vtss_inst_t      inst,
                                  const u16              group_id,
                                  const vtss_vid_t       vid)
{
    vtss_vlan_trans_grp2vlan_conf_t conf;

    conf.group_id = group_id;
    conf.vid = vid;
    conf.trans_vid = 0;
    conf.dir = VTSS_VLAN_TRANS_DIR_BOTH;
    return vtss_vlan_trans_group_conf_del(inst, &conf);
}

vtss_rc vtss_vlan_trans_group_get(const vtss_inst_t                inst,
                                  vtss_vlan_trans_grp2vlan_conf_t  *conf,
                                  BOOL                             next)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("group_id: %u", conf->group_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(l2.vlan_trans_group_get, conf, next);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_trans_group_to_port_set(const vtss_inst_t                     inst,
                                          const vtss_vlan_trans_port2grp_conf_t *conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("group_id: %u", conf->group_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(l2.vlan_trans_port_conf_set, conf);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_trans_group_to_port_get(const vtss_inst_t                inst,
                                          vtss_vlan_trans_port2grp_conf_t  *conf,
                                          BOOL                             next)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("group_id: %u", conf->group_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(l2.vlan_trans_port_conf_get, conf, next);
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
vtss_rc vtss_vcap_port_conf_get(const vtss_inst_t     inst,
                                const vtss_port_no_t  port_no,
                                vtss_vcap_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *conf = vtss_state->vcap.port_conf[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vcap_port_conf_set(const vtss_inst_t           inst,
                                const vtss_port_no_t        port_no,
                                const vtss_vcap_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_vcap_port_conf_t *port_conf = &vtss_state->vcap.port_conf[port_no];

        vtss_state->vcap.port_conf_old = *port_conf;
        *port_conf = *conf;
        rc = VTSS_FUNC_COLD(l2.vcap_port_conf_set, port_no);
        if (rc != VTSS_RC_OK) {
            /* Restore configuration if operation failed */
            *port_conf = vtss_state->vcap.port_conf_old;
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif
#endif // VTSS_FEATURE_VCAP

/* VLAN counters */
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
vtss_rc vtss_vlan_counters_get(const vtss_inst_t    inst,
                               const vtss_vid_t     vid,
                               vtss_vlan_counters_t *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(l2.vlan_counters_get, vid, counters);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_vlan_counters_clear(const vtss_inst_t  inst,
                                 const vtss_vid_t   vid)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_RC(vtss_vid_check(vid));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(l2.vlan_counters_clear, vid);
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

/* - Port Based Network Access Control, 802.1X --------------------- */

vtss_rc vtss_auth_port_state_get(const vtss_inst_t     inst,
                                 const vtss_port_no_t  port_no,
                                 vtss_auth_state_t     *const state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *state = vtss_state->l2.auth_state[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_auth_port_state_set(const vtss_inst_t        inst,
                                 const vtss_port_no_t     port_no,
                                 const vtss_auth_state_t  state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->l2.auth_state[port_no] = state;
        rc = vtss_update_masks(vtss_state, 1, 0, 1);
    }
    VTSS_EXIT();
    return rc;
}

/* - SFLOW --------------------------------------------------------- */

vtss_rc vtss_sflow_port_conf_get(const vtss_inst_t      inst,
                                 const u32              port_no,
                                 vtss_sflow_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->l2.sflow_conf[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_sflow_port_conf_set(const vtss_inst_t            inst,
                                 const vtss_port_no_t         port_no,
                                 const vtss_sflow_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(l2.sflow_port_conf_set, port_no, conf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_sflow_sampling_rate_convert(const vtss_inst_t  inst,
                                         const BOOL         power2,
                                         const u32          rate_in,
                                               u32          *const rate_out)
{
    // Don't take API lock and don't change vtss_state, since this is
    // a non-state-dependant function.
    vtss_state_t *vtss_state = vtss_inst_check_no_persist(inst);

    return VTSS_FUNC_FROM_STATE(vtss_state, l2.sflow_sampling_rate_convert, power2, rate_in, rate_out);
}

/* - Warm start synchronization ------------------------------------ */

#if defined(VTSS_FEATURE_WARM_START)
static void vtss_mac_entry_add_sync(vtss_state_t *vtss_state,
                                    vtss_mac_entry_t *cur, u32 pgid, BOOL new)
{
    vtss_rc        rc;
    BOOL           *member;
    vtss_vid_mac_t vid_mac;
    vtss_port_no_t port_no;

    /* Skip if already added */
    if (cur->flags & VTSS_MAC_FLAG_ADDED)
        return;

    /* Add entry */
    cur->flags |= VTSS_MAC_FLAG_ADDED;
    member = vtss_state->l2.pgid_table[VTSS_PGID_NONE].member;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
        member[port_no] = VTSS_PORT_BF_GET(cur->member, port_no);
    vtss_mach_macl_set(&vid_mac, cur->mach, cur->macl);
    if (vtss_ipmc_mac(vtss_state, &vid_mac)) {
        rc = VTSS_RC_OK;
        pgid = VTSS_PGID_NONE;
        vtss_pgid_members_get(vtss_state, pgid, member);
    } else {
        rc = vtss_pgid_alloc(vtss_state, &pgid, member, cur->cpu_copy, cur->cpu_queue, 1);
    }
    if (rc == VTSS_RC_OK) {
        VTSS_I("adding %s: %08x-%08x, pgid: %u",
               new ? "new" : "old" , cur->mach, cur->macl, pgid);
        (void)vtss_mac_entry_update(vtss_state, cur, pgid);
    }
}

/* Synchronize static entries in the MAC address table */
static vtss_rc vtss_mac_table_sync(vtss_state_t *vtss_state)
{
    vtss_mac_table_entry_t mac_entry;
    u32                    mach, macl, pgid = 0; /* Please Lint */
    vtss_mac_entry_t       *cur = vtss_state->l2.mac_list_used;
    BOOL                   found, next = 1;

    /* Step 1:
       Delete static hardware entries not present in the API table.
       Reuse PGIDs for entries present in the API table */
    VTSS_MEMSET(&mac_entry, 0, sizeof(mac_entry));
    while (1) {
        if (next) {
            /* Get next static HW entry */
            found = 0;
            while (VTSS_FUNC(l2.mac_table_get_next, &mac_entry, &pgid) == VTSS_RC_OK) {
                if (mac_entry.locked) {
                    found = 1;
                    break;
                }
            }
            if (!found)
                break;
        }

        vtss_mach_macl_get(&mac_entry.vid_mac, &mach, &macl);
        next = 1;
        if (cur == NULL || cur->mach > mach || (cur->mach == mach && cur->macl > macl)) {
            /* SW entry non-existing or bigger, delete HW entry */
            VTSS_I("deleting %08x-%08x", mach, macl);
            (void) VTSS_FUNC(l2.mac_table_del, &mac_entry.vid_mac);
        } else {
            if (cur->mach == mach && cur->macl == macl) {
                /* SW entry matches, update HW entry reusing PGID */
                vtss_mac_entry_add_sync(vtss_state, cur, pgid, 0);
            } else {
                /* SW entry smaller, do not get next HW entry */
                next = 0;
            }
            cur = cur->next;
        }
    }

    /* Step 2: Add new entries */
    for (cur = vtss_state->l2.mac_list_used; cur != NULL; cur = cur->next) {
        vtss_mac_entry_add_sync(vtss_state, cur, VTSS_PGID_NONE, 1); /* Do not reuse PGID */
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_l2_restart_sync(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    vtss_vid_t     vid;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_FUNC_RC(l2.learn_port_mode_set, port_no);
        VTSS_FUNC_RC(l2.vlan_port_conf_set, port_no);
#if defined(VTSS_FEATURE_VCAP)
#if defined(VTSS_ARCH_OCELOT)
        vtss_state->vcap.port_conf_old = vtss_state->vcap.port_conf[port_no];
        VTSS_FUNC_RC(l2.vcap_port_conf_set, port_no);
#endif /* VTSS_ARCH_OCELOT */
        vtss_state->l2.vcl_port_conf_old = vtss_state->l2.vcl_port_conf[port_no];
        VTSS_FUNC_RC(l2.vcl_port_conf_set, port_no);
#endif // VTSS_FEATURE_VCAP
    }

    VTSS_FUNC_RC_0(l2.isolated_port_members_set);
    VTSS_FUNC_RC_0(l2.mirror_port_set);
    VTSS_FUNC_RC_0(l2.mirror_ingress_set);
    VTSS_FUNC_RC_0(l2.mirror_egress_set);
    VTSS_FUNC_RC_0(l2.mirror_cpu_egress_set);
    VTSS_FUNC_RC_0(l2.mirror_cpu_ingress_set);
    VTSS_FUNC_RC_0(l2.flood_conf_set);
    VTSS_RC(vtss_mac_table_sync(vtss_state));
    VTSS_RC(vtss_update_masks(vtss_state, 1, 1, 1));
    for (vid = 0; vid < VTSS_VIDS; vid++) {
        VTSS_FUNC_RC(l2.vlan_port_members_set, vid);
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_WARM_START */

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_l2_inst_create(vtss_state_t *vtss_state)
{
    vtss_port_no_t        port_no;
    vtss_vlan_port_conf_t *vlan;
    vtss_vid_t            vid;
    vtss_vlan_entry_t     *vlan_entry;
    u32                   i;

    vtss_state->l2.vlan_conf.s_etype = VTSS_ETYPE_TAG_S; /* Default S-tag Ethernet type */

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        vlan = &vtss_state->l2.vlan_port_conf[port_no];
        vlan->pvid = VTSS_VID_DEFAULT;
        vlan->untagged_vid = VTSS_VID_DEFAULT;
        vtss_state->l2.learn_mode[port_no].automatic = 1;
        vtss_state->l2.stp_state[port_no] = VTSS_STP_STATE_FORWARDING;
        vtss_state->l2.port_aggr_no[port_no] = VTSS_AGGR_NO_NONE;
        vtss_state->l2.auth_state[port_no] = VTSS_AUTH_STATE_BOTH;
        vtss_state->l2.pvlan_table[VTSS_PVLAN_NO_DEFAULT].member[port_no] = 1;
        {
            vtss_port_no_t e_port;

            for (e_port = VTSS_PORT_NO_START; e_port < VTSS_PORT_NO_END; e_port++) {
                vtss_state->l2.apvlan_table[port_no][e_port] = 1;
            }
        }
        vtss_state->l2.dgroup_port_conf[port_no].dgroup_no = port_no;
        vtss_state->l2.uc_flood[port_no] = 1;
        vtss_state->l2.mc_flood[port_no] = 1;
        vtss_state->l2.ipv4_mc_flood[port_no] = 1;
        vtss_state->l2.ipv6_mc_flood[port_no] = 1;
        vtss_state->l2.port_all[port_no] = 1;
        vtss_state->l2.port_protect[port_no].conf.port_no = VTSS_PORT_NO_NONE;
        vtss_state->l2.port_protect[port_no].selector = VTSS_EPS_SELECTOR_WORKING;
    }

    /* Initialize VLAN table */
    for (vid = 0; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
#if defined(VTSS_FEATURE_L2_MSTP)
        vlan_entry->msti = VTSS_MSTI_START;
#endif
        if (vid != VTSS_VID_NULL) {
            vlan_entry->flags = (VLAN_FLAGS_LEARN | VLAN_FLAGS_FLOOD);
        }
#if defined(VTSS_FEATURE_VLAN_SVL)
        vlan_entry->fid = vid;
#endif /* VTSS_FEATURE_VLAN_SVL */
        if (vid != VTSS_VID_DEFAULT)
            continue;
        vlan_entry->flags |= VLAN_FLAGS_ENABLED;
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)
            VTSS_PORT_BF_SET(vlan_entry->member, port_no, 1);
    }

#if defined(VTSS_FEATURE_L2_MSTP)
    {
    /* All ports are forwarding in first MSTP instance */
        vtss_mstp_entry_t  *mstp_entry;

        mstp_entry = &vtss_state->l2.mstp_table[VTSS_MSTI_START];
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)
            mstp_entry->state[port_no] = VTSS_STP_STATE_FORWARDING;
    }
#endif

    vtss_state->l2.aggr_mode.smac_enable = 1;

    vtss_state->l2.mirror_conf.port_no = VTSS_PORT_NO_NONE;

    /* Initialize MAC address table */
    vtss_state->l2.mac_table_max = VTSS_MAC_ADDRS;
    for (i = 0; i < VTSS_MAC_ADDRS; i++) {
        /* Insert first in free list */
        vtss_state->l2.mac_table[i].next = vtss_state->l2.mac_list_free;
        vtss_state->l2.mac_list_free = &vtss_state->l2.mac_table[i];
    }
    vtss_state->l2.mac_age_time = 300;

#if defined(VTSS_FEATURE_VCAP)
    {
        vtss_vlan_trans_grp2vlan_entry_t *grp_entry;
        vtss_vlan_trans_grp2vlan_t       *grp_conf;
        vtss_vlan_trans_port2grp_entry_t *port_entry;
        vtss_vlan_trans_port2grp_t       *port_conf;

        /* Initialize VLAN Translation Group free/used lists */
        grp_conf = &vtss_state->l2.vt_trans_conf;
        grp_conf->used = NULL;
        for (i = VTSS_VLAN_TRANS_FIRST_GROUP_ID; i <= VTSS_VLAN_TRANS_MAX_CNT; i++) {
            grp_entry = &grp_conf->trans_list[i - VTSS_VLAN_TRANS_FIRST_GROUP_ID];
            /* Insert in free list */
            grp_entry->next = grp_conf->free;
            grp_conf->free = grp_entry;
        }
        /* Initialize VLAN Translation Port free/used lists */
        port_conf = &vtss_state->l2.vt_port_conf;
        port_conf->used = NULL;
        for (i = VTSS_VLAN_TRANS_FIRST_GROUP_ID; i <= VTSS_VLAN_TRANS_GROUP_MAX_CNT; i++) {
            port_entry = &port_conf->port_list[i - VTSS_VLAN_TRANS_FIRST_GROUP_ID];
            /* Insert in free list */
            port_entry->next = port_conf->free;
            port_conf->free = port_entry;
        }
    }
#endif // VTSS_FEATURE_VCAP
#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
    {
        vtss_ipmc_info_t *ipmc = &vtss_state->l2.ipmc;
        vtss_ipmc_src_t  *src;
        vtss_ipmc_dst_t  *dst;

        ipmc->obj.src_max = VTSS_IPMC_SRC_MAX;
        ipmc->obj.dst_max = VTSS_IPMC_DST_MAX;

        /* Add IPMC entries to free list */
        ipmc->obj.name = "IPMC";
        for (i = 0; i < VTSS_IPMC_SRC_MAX; i++) {
            src = &ipmc->src_table[i];
            src->next = ipmc->obj.src_free;
            ipmc->obj.src_free = src;
        }
        for (i = 0; i < VTSS_IPMC_DST_MAX; i++) {
            dst = &ipmc->dst_table[i];
            dst->next = ipmc->obj.dst_free;
            ipmc->obj.dst_free = dst;
        }
    }
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */

#if defined(VTSS_ARCH_JAGUAR_2)
    {
        vtss_vsi_info_t   *vsi_info = &vtss_state->l2.vsi_info;
        vtss_vsi_entry_t  *vsi;

        /* Add VSIs to free list */
        for (i = 0; i < vsi_info->max_count; i++) {
            vsi = &vsi_info->table[i];
            vsi->next = vsi_info->free;
            vsi->vsi = (vsi_info->max_count - i);
            vsi_info->free = vsi;
        }
    }
#endif

#if defined(VTSS_SDX_CNT)
    {
        vtss_sdx_info_t  *sdx_info = &vtss_state->l2.sdx_info;
        vtss_sdx_list_t  *isdx_list = &sdx_info->isdx;
        vtss_sdx_list_t  *esdx_list = &sdx_info->esdx;
        vtss_sdx_entry_t *sdx;

        /* Add SDX entries to free lists */
        for (i = 0; i < sdx_info->max_count; i++) {
            /* ISDX */
            sdx = &isdx_list->table[i];
            sdx->port_no = VTSS_PORT_NO_NONE;
            sdx->sdx = (sdx_info->max_count - i);
            sdx->next = isdx_list->free;
            isdx_list->free = sdx;
            
            /* ESDX */
            sdx = &esdx_list->table[i];
            sdx->port_no = VTSS_PORT_NO_NONE;
            sdx->sdx = (sdx_info->max_count - i);
            sdx->next = esdx_list->free;
            esdx_list->free = sdx;
        }
    }
#endif
#if defined(VTSS_EVC_STAT_CNT)
    VTSS_RC(vtss_l2_pol_stat_create(vtss_state));
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cmn_vlan_members_get(vtss_state_t *state,
                                  const vtss_vid_t vid,
                                  BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_port_no_t    port_no, port_p, mirror_port;
    vtss_vlan_entry_t *vlan_entry = &state->l2.vlan_table[vid];
#if defined(VTSS_FEATURE_L2_MSTP)
    vtss_mstp_entry_t *mstp_entry = &state->l2.mstp_table[vlan_entry->msti];
#endif
    vtss_port_eps_t   *protect;
    vtss_port_no_t    npi_port = VTSS_PORT_NO_NONE;

    VTSS_N("update %d", vid);

    /* Mirror port and forwarding mode */
    mirror_port = (state->l2.mirror_conf.fwd_enable ? VTSS_PORT_NO_NONE : state->l2.mirror_conf.port_no);

#if defined(VTSS_FEATURE_PACKET)
    if (state->packet.npi_conf.enable) {
        npi_port = state->packet.npi_conf.port_no;
    }
#endif

    /* Determine VLAN port members */
    for (port_no = VTSS_PORT_NO_START; port_no < state->port_count; port_no++) {
        member[port_no] = (
            /* Include VLAN member port */
            VTSS_PORT_BF_GET(vlan_entry->member, port_no) &&
            /* Exclude MSTP/ERPS discarding port */
#if defined(VTSS_FEATURE_L2_MSTP)
            mstp_entry->state[port_no] == VTSS_STP_STATE_FORWARDING &&
#endif
#if defined(VTSS_FEATURE_L2_ERPS)
            vlan_entry->erps_discard_cnt[port_no] == 0 &&
#endif
            port_no != mirror_port);
        /* Exclude NPI port */
        if (port_no == npi_port) {
            member[port_no] = 0;
        }
    }

    /* Consider protections */
    for (port_no = VTSS_PORT_NO_START; port_no < state->port_count; port_no++) {
#if defined(VTSS_FEATURE_HW_PROT)
        /* Remove inactive HW protection ports (both the active and inactive port are set in member[]
         * when we get here) */
        member[port_no] = member[port_no] && !VTSS_PORT_BF_GET(vlan_entry->hw_prot_disable, port_no);
#endif /* VTSS_FEATURE_HW_PROT */

        protect = &state->l2.port_protect[port_no];
        if ((port_p = protect->conf.port_no) == VTSS_PORT_NO_NONE)
            continue;

        if (protect->conf.type == VTSS_EPS_PORT_1_PLUS_1) {
            /* Port is 1+1 protected, include both ports if one of them is VLAN member */
            if (member[port_no])
                member[port_p] = 1;
            if (member[port_p])
                member[port_no] = 1;
        } else if (member[port_no]) {
            /* Port is 1:1 protected and VLAN member */
            if (protect->selector == VTSS_EPS_SELECTOR_WORKING) {
                /* Working port selected, protection port is not VLAN member */
                member[port_p] = 0;
            } else {
                /* Protection port selected, working port is not VLAN member */
                member[port_p] = 1;
                member[port_no] = 0;
            }
        }
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cmn_vlan_members_set(vtss_state_t *vtss_state, const vtss_vid_t vid)
{
    BOOL member[VTSS_PORT_ARRAY_SIZE];

    VTSS_N("update %d", vid);

    if (vtss_state->l2.vlan_mask_update == NULL)
        return VTSS_RC_ERROR;

    VTSS_RC(vtss_cmn_vlan_members_get(vtss_state, vid, member));
    vtss_state->l2.vlan_filter_changed = TRUE;

    return vtss_state->l2.vlan_mask_update(vtss_state, vid, member);
}

vtss_rc vtss_cmn_vlan_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_rc               rc;
    vtss_vlan_port_conf_t conf;
#if defined(VTSS_FEATURE_PACKET)
    vtss_npi_conf_t       *npi_conf;
#endif
#if defined(VTSS_FEATURE_ES0)
    u16                   flags = 0;
#endif

    if (vtss_state->l2.vlan_port_conf_update == NULL)
        return VTSS_RC_ERROR;

    conf = vtss_state->l2.vlan_port_conf[port_no];

#if defined(VTSS_FEATURE_PACKET)
    npi_conf = &vtss_state->packet.npi_conf;
    if (npi_conf->enable && npi_conf->port_no == port_no) {
        /* Setup NPI port as C-aware */
        conf.port_type = VTSS_VLAN_PORT_TYPE_C;

        // Since the NPI port is taken out of all VLANs, it must have ingress
        // filtering disabled (unless the external CPU injects masqueraded with
        // CPU as source port).
        conf.ingress_filter = FALSE;
    }
#endif

    rc = vtss_state->l2.vlan_port_conf_update(vtss_state, port_no, &conf);

#if defined(VTSS_FEATURE_ES0)
    if (vtss_state->l2.vlan_port_uvid[port_no] != conf.untagged_vid) {
        /* VLAN untagged VID changed, update ES0 rules */
        vtss_state->l2.vlan_port_uvid[port_no]= conf.untagged_vid;
        flags |= (VTSS_ES0_FLAG_OT_UVID | VTSS_ES0_FLAG_IT_UVID);
    }
    if (vtss_state->l2.vlan_port_type[port_no] != conf.port_type) {
        /* VLAN port type changed, update ES0 rules */
        vtss_state->l2.vlan_port_type[port_no]= conf.port_type;
        flags |= (VTSS_ES0_FLAG_OT_TPID | VTSS_ES0_FLAG_IT_TPID);
    }
    if (flags) {
        VTSS_RC(vtss_vcap_es0_update(vtss_state, port_no, flags));
    }
#endif /* VTSS_FEATURE_ES0 */

    return rc;
}

#if defined(VTSS_FEATURE_ES0)
static void vtss_cmn_es0_data_set(vtss_state_t *vtss_state,
                                  vtss_port_no_t port_no, vtss_vid_t vid, vtss_vid_t new_vid,
                                  BOOL tag_enable,
                                  vtss_vcap_data_t *data, vtss_es0_entry_t *entry)
{
    vtss_es0_data_t   *es0 = &data->u.es0;
    vtss_es0_key_t    *key = &entry->key;
    vtss_es0_action_t *action = &entry->action;

    /* Use (VID, port) as key */
    vtss_vcap_es0_init(data, entry);
    key->port_no = port_no;
    key->type = VTSS_ES0_TYPE_VID;
    key->data.vid.vid = vid;

    if (tag_enable) {
        /* Enable tagging */
        action->tag = VTSS_ES0_TAG_ES0;
        es0->flags = (VTSS_ES0_FLAG_OT_TPID | VTSS_ES0_FLAG_OT_QOS); /* Use port TPID and QoS */
        es0->port_no = port_no;
        action->vid_b = new_vid;

#if !defined(VTSS_ARCH_LUTON26)
        action->outer_tag.tag = VTSS_ES0_TAG_ES0;
        action->outer_tag.vid.sel = 1;
        action->outer_tag.vid.val = new_vid;
#endif
    } else {
        action->tag = VTSS_ES0_TAG_NONE;
        action->tpid = VTSS_ES0_TPID_S; /* Needed to overrule port configuration */
    }
}

static vtss_vcap_id_t vtss_tx_tag_vcap_id(vtss_vid_t vid, vtss_port_no_t port_no)
{
    vtss_vcap_id_t id = vid;

    return ((id << 32) + port_no);
}

vtss_rc vtss_cmn_vlan_tx_tag_set(vtss_state_t *vtss_state,
                                 const vtss_vid_t         vid,
                                 const vtss_vlan_tx_tag_t tx_tag[VTSS_PORT_ARRAY_SIZE])
{
    vtss_res_t        res;
    vtss_port_no_t    port_no, i;
    vtss_vlan_entry_t *vlan_entry = &vtss_state->l2.vlan_table[vid];
    vtss_vcap_obj_t   *obj = &vtss_state->vcap.es0.obj;
    vtss_vcap_id_t    id, id_next;
    vtss_vid_t        vid_next;
    vtss_vcap_data_t  data;
    vtss_es0_entry_t  entry;
    BOOL              tag_enable;

    /* Check resource consumption */
    vtss_cmn_res_init(&res);
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (vlan_entry->tx_tag[port_no] == VTSS_VLAN_TX_TAG_PORT) {
            if (tx_tag[port_no] != VTSS_VLAN_TX_TAG_PORT) {
                /* Add new ES0 rule for port */
                res.es0.add++;
            }
        } else if (tx_tag[port_no] == VTSS_VLAN_TX_TAG_PORT) {
            /* Delete old ES0 rule for port */
            res.es0.del++;
        }
    }
    VTSS_RC(vtss_cmn_res_check(vtss_state, &res));

    /* Delete resources */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (vlan_entry->tx_tag[port_no] != VTSS_VLAN_TX_TAG_PORT &&
            tx_tag[port_no] == VTSS_VLAN_TX_TAG_PORT) {
            id = vtss_tx_tag_vcap_id(vid, port_no);
            VTSS_RC(vtss_vcap_del(vtss_state, obj, VTSS_ES0_USER_TX_TAG, id));
        }
        vlan_entry->tx_tag[port_no] = tx_tag[port_no];
    }

    /* Find next ID */
    id_next = VTSS_VCAP_ID_LAST;
    for (vid_next = (vid + 1); vid_next < VTSS_VIDS; vid_next++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid_next];
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (vlan_entry->tx_tag[port_no] != VTSS_VLAN_TX_TAG_PORT) {
                id_next = vtss_tx_tag_vcap_id(vid_next, port_no);
                vid_next = VTSS_VIDS;
                break;
            }
        }
    }

    /* Add/update resources */
    for (i = vtss_state->port_count; i != 0; i--) {
        port_no = (i - 1);
        switch (tx_tag[port_no]) {
        case VTSS_VLAN_TX_TAG_ENABLE:
            tag_enable = 1;
            break;
        case VTSS_VLAN_TX_TAG_DISABLE:
            tag_enable = 0;
            break;
        default:
            continue;
        }
        vtss_cmn_es0_data_set(vtss_state, port_no, vid, vid, tag_enable, &data, &entry);
        id = vtss_tx_tag_vcap_id(vid, port_no);
        VTSS_RC(vtss_vcap_add(vtss_state, obj, VTSS_ES0_USER_TX_TAG, id, id_next, &data, 0));
        id_next = id;
    }
    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_ES0

static BOOL vtss_cmn_vlan_enabled(vtss_vlan_entry_t *vlan_entry)
{
    return (vlan_entry->flags & VLAN_FLAGS_ENABLED ? 1 : 0);
}

/* Update all VLANs */
vtss_rc vtss_cmn_vlan_update_all(vtss_state_t *vtss_state)
{
    vtss_vid_t vid;

    for (vid = VTSS_VID_DEFAULT; vid < VTSS_VIDS; vid++)
        VTSS_RC(vtss_cmn_vlan_members_set(vtss_state, vid));
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_L2_MSTP)
vtss_rc vtss_cmn_mstp_state_set(vtss_state_t *vtss_state,
                                const vtss_port_no_t   port_no,
                                const vtss_msti_t      msti)
{
    vtss_vid_t        vid;
    vtss_vlan_entry_t *vlan_entry;

    /* Update all VLANs mapping to MSTI */
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if (vtss_cmn_vlan_enabled(vlan_entry) && vlan_entry->msti == msti)
            VTSS_RC(vtss_cmn_vlan_members_set(vtss_state, vid));
    }

    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_L2_ERPS)
vtss_rc vtss_cmn_erps_vlan_member_set(vtss_state_t *vtss_state,
                                      const vtss_erpi_t erpi,
                                      const vtss_vid_t  vid)
{
    return vtss_cmn_vlan_members_set(vtss_state, vid);
}

vtss_rc vtss_cmn_erps_port_state_set(vtss_state_t *vtss_state,
                                     const vtss_erpi_t    erpi,
                                     const vtss_port_no_t port_no)
{
    vtss_vid_t        vid;
    vtss_vlan_entry_t *vlan_entry;

    /* Update all VLANs changed by ERPS */
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if (vlan_entry->flags & VLAN_FLAGS_UPDATE) {
            vlan_entry->flags &= ~VLAN_FLAGS_UPDATE;
            if (vtss_cmn_vlan_enabled(vlan_entry))
                VTSS_RC(vtss_cmn_vlan_members_set(vtss_state, vid));
        }
    }
    return VTSS_RC_OK;

}
#endif // VTSS_FEATURE_L2_ERPS

vtss_rc vtss_cmn_eps_port_set(vtss_state_t *vtss_state,
                              const vtss_port_no_t port_w)
{
    vtss_vid_t vid;

    /* Update all VLANs */
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        if (vtss_cmn_vlan_enabled(&vtss_state->l2.vlan_table[vid]))
            VTSS_RC(vtss_cmn_vlan_members_set(vtss_state, vid));
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_HW_PROT)
vtss_rc vtss_cmn_hw_prot_port_disable_set(struct vtss_state_s *vtss_state,
                                          const vtss_vid_t    vid,
                                          const BOOL          member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_vlan_entry_t *vlan_entry = &vtss_state->l2.vlan_table[vid];
    vtss_port_no_t    port_no;

    if (vid != VTSS_VID_NULL) {

        if (!member) {
            VTSS_PORT_BF_CLR(vlan_entry->hw_prot_disable);
        } else {
            for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                VTSS_PORT_BF_SET(vlan_entry->hw_prot_disable, port_no, member[port_no]);
            }
        }
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_HW_PROT */

#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
u32 vtss_cmn_ip2u32(vtss_ip_addr_internal_t *ip, BOOL ipv6)
{
    u32 addr = 0, i;

    if (ipv6) {
        for (i = 12; i < 16; i++) {
            addr += (ip->ipv6.addr[i] << ((15 - i)*8));
        }
    } else {
        addr = ip->ipv4;
    }
    return addr;
}

/* IPMC source key is (SIP, SSM, VID) */
static u64 vtss_cmn_ip_mc_src_key(vtss_ipmc_src_data_t *src, BOOL ipv6)
{
    u64 key = vtss_cmn_ip2u32(&src->sip, ipv6);

    key = (key << 32);
    if (src->ssm)
        key += (1<<12);
    key += src->vid;
    return key;
}

/* IPMC destination key is (DIP32/DIP23, DIP) */
static u64 vtss_cmn_ip_mc_dst_key(vtss_ipmc_dst_data_t *dst, BOOL ipv6)
{
    u32 dip = vtss_cmn_ip2u32(&dst->dip, ipv6);
    u64 key = (ipv6 ? dip : (dip &  0x007fffff));

    key = (key << 32);
    key += dip;
    return key;
}

static vtss_rc vtss_cmn_ip_mc_add(vtss_state_t *vtss_state, vtss_ipmc_data_t *ipmc)
{
    vtss_ipmc_obj_t *obj = &vtss_state->l2.ipmc.obj;
    vtss_ipmc_src_t *src, *src_prev = NULL, **src_list;
    vtss_ipmc_dst_t *dst = NULL, *dst_prev = NULL;
    vtss_vid_t      fid;
    u64             sip, ipmc_sip = vtss_cmn_ip_mc_src_key(&ipmc->src, ipmc->ipv6);
    u32             dip, ipmc_dip = vtss_cmn_ip_mc_dst_key(&ipmc->dst, ipmc->ipv6);

    /* Search for source entry or the place to insert the new entry */
    src_list = &obj->src_used[ipmc->ipv6];
    for (src = *src_list; src != NULL; src_prev = src, src = src->next) {
        sip = vtss_cmn_ip_mc_src_key(&src->data, ipmc->ipv6);
        if (sip > ipmc_sip) {
            /* Found bigger entry */
            src = NULL;
            break;
        } else if (sip == ipmc_sip) {
            /* Found matching key, save allocated FID */
            ipmc->src.fid = src->data.fid;
            if (!ipmc->ipv6 ||
                VTSS_MEMCMP(&src->data.sip.ipv6, &ipmc->src.sip.ipv6, sizeof(vtss_ipv6_t)) == 0) {
                /* Found identical entry */
                break;
            }
        }
    }

    if (src == NULL) {
        /* Check if source entry can be allocated */
        if (obj->src_free == NULL) {
            VTSS_I("no more source entries");
            return VTSS_RC_ERROR;
        }
        ipmc->src_add = 1;
    } else {
        /* Source found, search for destination entry or the place to insert the new entry */
        for (dst = src->dest; dst != NULL; dst_prev = dst, dst = dst->next) {
            dip = vtss_cmn_ip_mc_dst_key(&dst->data, ipmc->ipv6);
            if (dip > ipmc_dip) {
                /* Found bigger entry */
                dst = NULL;
                break;
            }

            if (dip == ipmc_dip &&
                (!ipmc->ipv6 ||
                 VTSS_MEMCMP(&dst->data.dip.ipv6, &ipmc->dst.dip.ipv6, sizeof(vtss_ipv6_t)) == 0)) {
                /* Found identical entry */
                VTSS_MEMCPY(dst->data.member, ipmc->dst.member, VTSS_PORT_BF_SIZE);
                ipmc->dst.id = dst->data.id;
                break;
            }
        }
    }

    if (dst == NULL) {
        /* Check if destination entry can be allocated */
        if (obj->dst_free == NULL) {
            VTSS_I("no more destination entries");
            return VTSS_RC_ERROR;
        }
        ipmc->dst_add = 1;
    }

    /* Check that resources can be added in device */
    fid = ipmc->src.fid;
    VTSS_FUNC_RC(l2.ip_mc_update, ipmc, VTSS_IPMC_CMD_CHECK);

    /* Now allocate resources */
    if (src == NULL) {
        /* Allocate new source entry */
        src = obj->src_free;
        obj->src_free = src->next;
        obj->src_count++;
        if (src_prev == NULL) {
            /* Insert first in list */
            src->next = *src_list;
            *src_list = src;
        } else {
            /* Insert after previous entry */
            src->next = src_prev->next;
            src_prev->next = src;
        }
        src->data = ipmc->src;
        src->dest = NULL;
    }

    if (dst == NULL) {
        /* Allocate new destination entry */
        dst = obj->dst_free;
        obj->dst_free = dst->next;
        obj->dst_count++;
        if (dst_prev == NULL) {
            /* Insert first in list */
            dst->next = src->dest;
            src->dest = dst;
        } else {
            /* Insert after previous entry */
            dst->next = dst_prev->next;
            dst_prev->next = dst;
        }
        obj->id++;
        ipmc->dst.id = obj->id;
        dst->data = ipmc->dst;
    }
    ipmc->id_next = (dst->next != NULL ? dst->next->data.id :
                     src->next != NULL && src->next->data.ssm == src->data.ssm ? src->next->dest->data.id : VTSS_VCAP_ID_LAST);

    /* Add ressources in device */
    ipmc->src.fid = fid;
    VTSS_FUNC_RC(l2.ip_mc_update, ipmc, VTSS_IPMC_CMD_ADD);

    return VTSS_RC_OK;
}

static vtss_rc vtss_cmn_ip_mc_del(vtss_state_t *vtss_state, vtss_ipmc_data_t *ipmc)
{
    vtss_ipmc_obj_t *obj = &vtss_state->l2.ipmc.obj;
    vtss_ipmc_src_t *src, *src_prev = NULL, **src_list;
    vtss_ipmc_dst_t *dst = NULL, *dst_prev = NULL;

    /* Search for source entry */
    src_list = &obj->src_used[ipmc->ipv6];
    for (src = *src_list; src != NULL; src_prev = src, src = src->next) {
        if (src->data.vid == ipmc->src.vid &&
            ((!ipmc->ipv6 && ipmc->src.sip.ipv4 == src->data.sip.ipv4) ||
             (ipmc->ipv6 &&
              VTSS_MEMCMP(&src->data.sip.ipv6, &ipmc->src.sip.ipv6, sizeof(vtss_ipv6_t)) == 0))) {
            ipmc->src.fid = src->data.fid;
            /* Found entry */
            break;
        }
    }

    if (src == NULL) {
        VTSS_E("IPv%u SIP 0x%08x not found",
               ipmc->ipv6 ? 6 : 4, vtss_cmn_ip2u32(&ipmc->src.sip, ipmc->ipv6));
        return VTSS_RC_ERROR;
    }

    /* Search for destination entry */
    for (dst = src->dest; dst != NULL; dst_prev = dst, dst = dst->next) {
        if ((!ipmc->ipv6 && dst->data.dip.ipv4 == ipmc->dst.dip.ipv4) ||
            (ipmc->ipv6 &&
             VTSS_MEMCMP(&dst->data.dip.ipv6, &ipmc->dst.dip.ipv6, sizeof(vtss_ipv6_t)) == 0)) {
            /* Found entry */
            ipmc->dst.id = dst->data.id;
            break;
        }
    }


    if (dst == NULL) {
        VTSS_E("IPv%u DIP 0x%08x not found",
               ipmc->ipv6 ? 6 : 4, vtss_cmn_ip2u32(&ipmc->dst.dip, ipmc->ipv6));
        return VTSS_RC_ERROR;
    }

    /* Move destination entry to free list */
    if (dst_prev == NULL)
        src->dest = dst->next;
    else
        dst_prev->next = dst->next;
    dst->next = obj->dst_free;
    obj->dst_free = dst;
    obj->dst_count--;

    /* Free source, if it was the last destination */
    if (src->dest == NULL) {
        if (src_prev == NULL)
            *src_list = src->next;
        else
            src_prev->next = src->next;
        src->next = obj->src_free;
        obj->src_free = src;
        obj->src_count--;
        ipmc->src_del = 1;
    }
    ipmc->dst_del = 1;

    /* Delete resources */
    VTSS_FUNC_RC(l2.ip_mc_update, ipmc, VTSS_IPMC_CMD_DEL);

    return VTSS_RC_OK;
}

static void vtss_cmn_ipv4_mc_data_init(vtss_ipmc_data_t *ipmc,
                                       const vtss_vid_t vid,
                                       const vtss_ip_t  sip,
                                       const vtss_ip_t  dip)
{
    VTSS_MEMSET(ipmc, 0, sizeof(*ipmc));
    ipmc->src.vid = vid;
    ipmc->src.sip.ipv4 = sip;
    ipmc->dst.dip.ipv4 = dip;
    if (sip == 0) {
        /* Zero SIP indicates ASM */
        ipmc->src.fid = vid;
    } else {
        ipmc->src.ssm = 1;
    }
}

vtss_rc vtss_cmn_ipv4_mc_add(vtss_state_t     *vtss_state,
                             const vtss_vid_t vid,
                             const vtss_ip_t  sip,
                             const vtss_ip_t  dip,
                             const BOOL       member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_ipmc_data_t ipmc;
    vtss_port_no_t   port_no;

    vtss_cmn_ipv4_mc_data_init(&ipmc, vid, sip, dip);
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_PORT_BF_SET(ipmc.dst.member, port_no, member[port_no]);
    }
    return vtss_cmn_ip_mc_add(vtss_state, &ipmc);
}

vtss_rc vtss_cmn_ipv4_mc_del(vtss_state_t     *vtss_state,
                             const vtss_vid_t vid,
                             const vtss_ip_t  sip,
                             const vtss_ip_t  dip)
{
    vtss_ipmc_data_t ipmc;

    vtss_cmn_ipv4_mc_data_init(&ipmc, vid, sip, dip);
    return vtss_cmn_ip_mc_del(vtss_state, &ipmc);
}

static void vtss_cmn_ipv6_mc_data_init(vtss_ipmc_data_t  *ipmc,
                                       const vtss_vid_t  vid,
                                       const vtss_ipv6_t sip,
                                       const vtss_ipv6_t dip)
{
    vtss_ipv6_t sipv6;

    VTSS_MEMSET(ipmc, 0, sizeof(*ipmc));
    ipmc->ipv6 = 1;
    ipmc->src.vid = vid;
    ipmc->src.sip.ipv6 = sip;
    ipmc->dst.dip.ipv6 = dip;
    VTSS_MEMSET(&sipv6, 0, sizeof(sipv6));
    if (VTSS_MEMCMP(&sip, &sipv6, sizeof(sipv6)) == 0) {
        /* Zero SIP indicates ASM */
        ipmc->src.fid = vid;
    } else {
        ipmc->src.ssm = 1;
    }
}

vtss_rc vtss_cmn_ipv6_mc_add(vtss_state_t      *vtss_state,
                             const vtss_vid_t  vid,
                             const vtss_ipv6_t sip,
                             const vtss_ipv6_t dip,
                             const BOOL        member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_ipmc_data_t ipmc;
    vtss_port_no_t   port_no;

    vtss_cmn_ipv6_mc_data_init(&ipmc, vid, sip, dip);
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_PORT_BF_SET(ipmc.dst.member, port_no, member[port_no]);
    }
    return vtss_cmn_ip_mc_add(vtss_state, &ipmc);
}

vtss_rc vtss_cmn_ipv6_mc_del(vtss_state_t      *vtss_state,
                             const vtss_vid_t  vid,
                             const vtss_ipv6_t sip,
                             const vtss_ipv6_t dip)
{
    vtss_ipmc_data_t ipmc;

    vtss_cmn_ipv6_mc_data_init(&ipmc, vid, sip, dip);
    return vtss_cmn_ip_mc_del(vtss_state, &ipmc);
}
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */

#if defined(VTSS_FEATURE_VCAP)
#if defined(VTSS_ARCH_OCELOT)
vtss_vcap_key_type_t vtss_vcl_key_type_get(vtss_vcap_key_type_t key_type_a, vtss_vcap_key_type_t key_type_b)
{
    /* For Serval-1, EVC and VCL port configuration must be aggregated to determine the first IS1 lookup key.
       By default, both key types are NORMAL. */
    return (key_type_a == VTSS_VCAP_KEY_TYPE_NORMAL ? key_type_b : key_type_a);
}
#endif

#if !defined(VTSS_ARCH_LUTON26)
static void vtss_cmn_key_type_get(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 lookup,
                                  vtss_is1_key_t *key, vtss_vcap_key_size_t *key_size)
{
    vtss_vcl_port_conf_t *conf;

    key->key_type = VTSS_VCAP_KEY_TYPE_NORMAL;
    if (port_no < vtss_state->port_count) {
        /* The first port in the list determines the key type */
        conf = &vtss_state->l2.vcl_port_conf[port_no];
        key->key_type = conf->key_type;
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
        if (lookup == 1) {
            key->key_type = vtss_state->vcap.port_conf[port_no].key_type_is1_1;
        }
#else
        key->dmac_dip = conf->dmac_dip;
#endif
    }
    *key_size = vtss_vcap_key_type2size(key->key_type);
}
#endif /* VTSS_ARCH_LUTON26 */

vtss_rc vtss_cmn_vcl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_vcap_obj_t   *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_entry_t *cur;

    if (vtss_state->l2.vcl_port_conf[port_no].key_type != vtss_state->l2.vcl_port_conf_old.key_type) {
        /* Key type changed, check if port used in VCL/VLAN translation rules */
        for (cur = obj->used; cur != NULL; cur = cur->next) {
            if (cur->data.u.is1.port_no == port_no) {
                VTSS_I("port_no: %u is used in VCAP rules, key type can not be changed", port_no);
                return VTSS_RC_ERROR;
            }
        }
    }
    return VTSS_RC_OK;
}

static void vtss_vce2is1_tag(const vtss_vce_tag_t *vce, vtss_is1_tag_t *tag)
{
    tag->vid.type = VTSS_VCAP_VR_TYPE_VALUE_MASK;
    tag->vid.vr.v.value = vce->vid.value;
    tag->vid.vr.v.mask = vce->vid.mask;
    tag->pcp = vce->pcp;
    tag->dei = vce->dei;
    tag->tagged = vce->tagged;
    tag->s_tag = vce->s_tag;
}

/* Add VCE */
vtss_rc vtss_cmn_vce_add(vtss_state_t *vtss_state, const vtss_vce_id_t vce_id, const vtss_vce_t *const vce)
{
    vtss_vcap_obj_t             *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_user_t            user = VTSS_IS1_USER_VCL;
    vtss_vcap_data_t            data;
    vtss_is1_data_t             *is1 = &data.u.is1;
    vtss_is1_entry_t            entry;
    vtss_is1_action_t           *action = &entry.action;
    vtss_is1_key_t              *key = &entry.key;
    vtss_res_chg_t              res_chg;
    vtss_vcap_range_chk_table_t range_new = vtss_state->vcap.range; /* Make a temporary working copy of the range table */
#if defined(VTSS_FEATURE_VOP_V2)
    vtss_sdx_entry_t            *sdx;
#endif

    /* Check VCE ID */
    if (vce->id == VTSS_VCE_ID_LAST || vce->id == vce_id) {
        VTSS_E("illegal vce id: %u", vce->id);
        return VTSS_RC_ERROR;
    }

    /* Check if main entry exists */
    VTSS_MEMSET(&res_chg, 0, sizeof(res_chg));
    if (vtss_vcap_lookup(vtss_state, obj, user, vce->id, &data, NULL) == VTSS_RC_OK) {
        /* Free any old range checkers */
        VTSS_RC(vtss_vcap_range_free(&range_new, is1->vid_range));
        VTSS_RC(vtss_vcap_range_free(&range_new, is1->dscp_range));
        VTSS_RC(vtss_vcap_range_free(&range_new, is1->sport_range));
        VTSS_RC(vtss_vcap_range_free(&range_new, is1->dport_range));
        res_chg.del_key[data.key_size] = 1;
    }

    /* Initialize entry data */
    vtss_vcap_is1_init(&data, &entry);
    data.key_size = VTSS_VCAP_KEY_SIZE_FULL;
    is1->port_no = vtss_cmn_first_port_no_get(vtss_state, vce->key.port_list);
    is1->flags = VTSS_IS1_FLAG_TRI_VID;

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    vtss_cmn_key_type_get(vtss_state, is1->port_no, is1->lookup, key, &data.key_size);
#endif
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    if (vtss_state->arch == VTSS_ARCH_JR2 || vtss_state->arch == VTSS_ARCH_ANT) {
        vtss_cmn_key_type_get(vtss_state, is1->port_no, is1->lookup, key, &data.key_size);
    }
#endif

    /* Check that the entry can be added */
    res_chg.add_key[data.key_size] = 1;
    VTSS_RC(vtss_cmn_vcap_res_check(obj, &res_chg));

    /* Copy action data */
    action->vid = vce->action.vid;
    if (vce->action.policy_no != VTSS_ACL_POLICY_NO_NONE) {
        action->pag_enable = TRUE;
        action->pag = vce->action.policy_no;
    }
    action->pop_enable = vce->action.pop_enable;
    action->pop = vce->action.pop_cnt;
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    if (vce->action.map_sel != VTSS_IMAP_SEL_DISABLE) {
        is1->map_id = vce->action.map_id;
        is1->flags |= VTSS_IS1_FLAG_MAP_ID;
        if (vce->action.map_sel == VTSS_IMAP_SEL_INNER) {
            is1->flags |= VTSS_IS1_FLAG_MAP_INNER;
        }
    }
#endif
#if defined(VTSS_FEATURE_XFLOW)
    if (vce->action.flow_id != VTSS_IFLOW_ID_NONE) {
        action->isdx_enable = TRUE;
        action->isdx = vce->action.flow_id;
        is1->isdx = action->isdx;
#if defined(VTSS_FEATURE_VOP_V2)
        if ((sdx = vtss_iflow_lookup(vtss_state, vce->action.flow_id)) != NULL) {
            if (sdx->conf.voi_idx != VTSS_VOI_IDX_NONE) {
                action->mip_enable = TRUE;  /* If a flow_id pointed to by VCE action is pointing to a MIP resource then the VCAP action must enable MIP */
            }
        } else {
            VTSS_D("Could not lookup action.flow_id: %d", vce->action.flow_id);
        }
#endif
    }
#if defined(VTSS_FEATURE_VOP)
    action->oam_detect = vce->action.oam_detect;
#endif
#if defined(VTSS_ARCH_OCELOT)
    action->oam_enable = (vce->action.oam_detect != VTSS_OAM_DETECT_NONE) ? 1 : 0;
#endif
#endif
    action->prio_enable    = vce->action.prio_enable;
    action->prio           = vce->action.prio;
    action->dp_enable      = vce->action.dp_enable;
    action->dp             = vce->action.dp;
    action->dscp_enable    = vce->action.dscp_enable;
    action->dscp           = vce->action.dscp;
    action->pcp_dei_enable = (vce->action.pcp_enable || vce->action.dei_enable);
    action->pcp_enable     = vce->action.pcp_enable;
    action->dei_enable     = vce->action.dei_enable;
    action->pcp            = vce->action.pcp;
    action->dei            = vce->action.dei;

    /* Copy key data */
    VTSS_MEMCPY(key->port_list, vce->key.port_list, sizeof(key->port_list));

    key->mac.dmac_mc = vce->key.mac.dmac_mc;
    key->mac.dmac_bc = vce->key.mac.dmac_bc;
    key->mac.smac = vce->key.mac.smac;
#if defined(VTSS_FEATURE_VCL_KEY_DMAC)
    key->mac.dmac = vce->key.mac.dmac;
#endif

    vtss_vce2is1_tag(&vce->key.tag, &key->tag);
#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    vtss_vce2is1_tag(&vce->key.inner_tag, &key->inner_tag);
#endif

    switch (vce->key.type) {
    case VTSS_VCE_TYPE_ANY:
        key->type = VTSS_IS1_TYPE_ANY;
        break;
    case VTSS_VCE_TYPE_ETYPE:
        key->type              = VTSS_IS1_TYPE_ETYPE;
        key->frame.etype.etype = vce->key.frame.etype.etype;
        key->frame.etype.data  = vce->key.frame.etype.data;
        key->frame.etype.mel   = vce->key.frame.etype.mel;
        break;
    case VTSS_VCE_TYPE_LLC:
        key->type           = VTSS_IS1_TYPE_LLC;
        key->frame.llc.data = vce->key.frame.llc.data;
        break;
    case VTSS_VCE_TYPE_SNAP:
        key->type            = VTSS_IS1_TYPE_SNAP;
        key->frame.snap.data = vce->key.frame.snap.data;
        break;
    case VTSS_VCE_TYPE_IPV4:
        key->type                = VTSS_IS1_TYPE_IPV4;
        key->frame.ipv4.fragment = vce->key.frame.ipv4.fragment;
        key->frame.ipv4.options  = vce->key.frame.ipv4.options;
        key->frame.ipv4.dscp     = vce->key.frame.ipv4.dscp;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->dscp_range, VTSS_VCAP_RANGE_TYPE_DSCP, &key->frame.ipv4.dscp));
        key->frame.ipv4.proto    = vce->key.frame.ipv4.proto;
        key->frame.ipv4.sip      = vce->key.frame.ipv4.sip;
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
        key->frame.ipv4.dip      = vce->key.frame.ipv4.dip;
#endif
        key->frame.ipv4.sport    = vce->key.frame.ipv4.sport;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->sport_range, VTSS_VCAP_RANGE_TYPE_SPORT, &key->frame.ipv4.sport));
        key->frame.ipv4.dport    = vce->key.frame.ipv4.dport;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->dport_range, VTSS_VCAP_RANGE_TYPE_DPORT, &key->frame.ipv4.dport));
        break;
    case VTSS_VCE_TYPE_IPV6:
        key->type                = VTSS_IS1_TYPE_IPV6;
        key->frame.ipv6.dscp     = vce->key.frame.ipv6.dscp;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->dscp_range, VTSS_VCAP_RANGE_TYPE_DSCP, &key->frame.ipv6.dscp));
        key->frame.ipv6.proto    = vce->key.frame.ipv6.proto;
        key->frame.ipv6.sip      = vce->key.frame.ipv6.sip;
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
        key->frame.ipv6.dip      = vce->key.frame.ipv6.dip;
#endif
        key->frame.ipv6.sport    = vce->key.frame.ipv6.sport;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->sport_range, VTSS_VCAP_RANGE_TYPE_SPORT, &key->frame.ipv6.sport));
        key->frame.ipv6.dport    = vce->key.frame.ipv6.dport;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->dport_range, VTSS_VCAP_RANGE_TYPE_DPORT, &key->frame.ipv6.dport));
        break;
    default:
        VTSS_E("illegal type: %d", vce->key.type);
        return VTSS_RC_ERROR;
    }

    /* Commit range checkers */
    VTSS_RC(vtss_vcap_range_commit(vtss_state, &range_new));

    /* Add main entry */
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, vce->id, vce_id, &data, 0));
    return VTSS_RC_OK;
}

/* Delete VCE */
vtss_rc vtss_cmn_vce_del(vtss_state_t *vtss_state, const vtss_vce_id_t vce_id)
{
    vtss_vcap_obj_t  *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_user_t user = VTSS_IS1_USER_VCL;
    vtss_vcap_data_t data;
    vtss_is1_data_t  *is1 = &data.u.is1;

    if (vtss_vcap_lookup(vtss_state, obj, user, vce_id, &data, NULL) != VTSS_RC_OK) {
        /* This is possible as add may fail in some situations due to hardware limitation */
        VTSS_D("vce_id: %u not found", vce_id);
        return VTSS_RC_OK;
    }

    /* Delete range checkers and main entry */
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->vid_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->dscp_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->sport_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->dport_range));
    VTSS_RC(vtss_vcap_del(vtss_state, obj, user, vce_id));

    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_VCAP

#if VTSS_OPT_DEBUG_PRINT
#if defined(VTSS_FEATURE_XFLOW)
static void vtss_debug_print_w6(const vtss_debug_printf_t pr, BOOL enable, u32 val)
{
    if (enable) {
        pr("%-6u", val);
    } else {
        pr("%-6s", "-");
    }
}

static void vtss_debug_print_iflow(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    vtss_sdx_entry_t  *sdx;
    vtss_iflow_conf_t *conf;
    BOOL              first = TRUE;

    for (sdx = vtss_state->l2.sdx_info.iflow; sdx != NULL; sdx = sdx->next) {
        if (first) {
            first = FALSE;
            pr("Ingress Flows:\n\n");
            pr("ISDX  ");
#if defined(VTSS_FEATURE_XSTAT)
            pr("STAT  ");
#endif
#if defined(VTSS_FEATURE_XDLB)
            pr("DLB   ");
#endif
#if defined(VTSS_FEATURE_VOP)
            pr("VOE   ");
#endif
#if defined(VTSS_FEATURE_VOP_V2)
            pr("MIP   ");
#endif
#if defined(VTSS_FEATURE_FRER)
            pr("MSID  Generate  ");
#endif
#if defined(VTSS_FEATURE_FRER_IFLOW_POP)
            pr("Pop       ");
#endif
#if defined(VTSS_FEATURE_PSFP)
            pr("Filter  ");
#endif
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
            pr("CT_DIS");
#endif
            pr("\n");
        }
        conf = &sdx->conf;
        vtss_debug_print_w6(pr, TRUE, sdx->sdx);
#if defined(VTSS_FEATURE_XSTAT)
        vtss_debug_print_w6(pr, conf->cnt_enable, conf->cnt_id);
#endif
#if defined(VTSS_FEATURE_XDLB)
        vtss_debug_print_w6(pr, conf->dlb_enable, conf->dlb_id);
#endif
#if defined(VTSS_FEATURE_VOP)
        vtss_debug_print_w6(pr, conf->voe_idx != VTSS_VOE_IDX_NONE, conf->voe_idx);
#endif
#if defined(VTSS_FEATURE_VOP_V2)
        vtss_debug_print_w6(pr, conf->voi_idx != VTSS_VOI_IDX_NONE, conf->voi_idx);
#endif
#if defined(VTSS_FEATURE_FRER)
        vtss_debug_print_w6(pr, conf->frer.mstream_enable, conf->frer.mstream_id);
        pr("%-10s", vtss_bool_txt(conf->frer.generation));
#endif
#if defined(VTSS_FEATURE_FRER_IFLOW_POP)
        pr("%-10s", vtss_bool_txt(conf->frer.pop));
#endif
#if defined(VTSS_FEATURE_PSFP)
        vtss_debug_print_w6(pr, conf->psfp.filter_enable, conf->psfp.filter_id);
#endif
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
        pr("  %u", conf->cut_through_disable);
#endif
        pr("\n");
    }
    if (!first) {
        pr("\n");
    }
}

static void vtss_debug_print_eflow(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    vtss_eflow_entry_t *eflow;
    vtss_eflow_conf_t  *conf;
    u32                i;
    BOOL               first = TRUE;

    for (i = 0; i < VTSS_SDX_CNT; i++) {
        eflow = &vtss_state->l2.eflow[i];
        if (!eflow->used) {
            continue;
        }
        if (first) {
            first = FALSE;
            pr("Egress Flows:\n\n");
            pr("ESDX  ");
#if defined(VTSS_FEATURE_XSTAT)
            pr("STAT  ");
#endif
            pr("VOE   ");
#if defined(VTSS_ARCH_JAGUAR_2)
            pr("MIP   ");
#endif
            pr("\n");
        }
        conf = &eflow->conf;
        vtss_debug_print_w6(pr, TRUE, i + 1);
#if defined(VTSS_FEATURE_XSTAT)
        vtss_debug_print_w6(pr, conf->cnt_enable, conf->cnt_id);
#endif
#if defined(VTSS_FEATURE_VOP)
        vtss_debug_print_w6(pr, conf->voe_idx != VTSS_VOE_IDX_NONE, conf->voe_idx);
#endif
#if defined(VTSS_FEATURE_VOP_V2)
        vtss_debug_print_w6(pr, conf->voi_idx != VTSS_VOI_IDX_NONE, conf->voi_idx);
#endif
        pr("\n");
    }
    if (!first) {
        pr("\n");
    }
}
#endif

#if defined(VTSS_FEATURE_XSTAT)
static void vtss_debug_print_xrow(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info,
                                  vtss_xrow_header_t *hdr)
{
    vtss_xrow_entry_t  *row;
    u16                row_idx, col_idx, size, count;
    BOOL               header = TRUE;

    vtss_debug_print_header(pr, hdr->name);
    pr("max_count : %u\n", hdr->max_count);
    pr("count     : %u\n", hdr->count);
    for (size = 0; size < 9; size++) {
        if ((count = hdr->count_size[size]) != 0) {
            pr("count[%u]  : %u\n", size, count);
        }
    }
    pr("\n");

    for (row_idx = 0; row_idx < (hdr->max_count / 8); row_idx++) {
        row = (hdr->row + row_idx);
        if (row->size == 0) {
            continue;
        }
        if (header) {
            header = FALSE;
            pr("Index  Size  Count  01234567\n");
        }
        pr("%-7u%-6u%-7u", row_idx * 8, row->size, row->count);
        for (col_idx = 0; col_idx < 8; col_idx++) {
            pr(col_idx % row->size ? "-" : row->col[col_idx].used ? "X" : "0");
        }
        pr("\n");
    }
    if (!header)
        pr("\n");
}



static void vtss_debug_print_istat(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    vtss_xstat_entry_t      *stat;
    vtss_ingress_counters_t cnt;
    vtss_counter_t          c[3];
    u16                     i, j;
    char                    buf[80];
    BOOL                    first = TRUE;

    vtss_debug_print_xrow(vtss_state, pr, info, &vtss_state->l2.istat_table.hdr);
    for (i = 0; i < VTSS_EVC_STAT_CNT; i++) {
        stat = &vtss_state->l2.istat.table[i];
        if (stat->cnt == 0) {
            continue;
        }
        if (first) {
            first = FALSE;
            pr("Ingress Counters:\n\n");
            pr("ID    SDX   IDX   CNT  COSID  Green/Yellow/Red Frames  ");
            VTSS_STRCPY(buf, "Green/Yellow/Red Bytes");
#if defined(VTSS_FEATURE_PSFP)
            if (vtss_state->init_conf.psfp_counters_enable) {
                VTSS_STRCPY(buf, "Match/GateDiscard/SduDiscard");
            }
#endif
            pr("%s\n", buf);
        }
        for (j = 0; j < stat->cnt; j++) {
            if (j == 0) {
                pr("%-6u%-6u%-6u%-5u", i, stat->sdx, stat->idx, stat->cnt);
            } else {
                pr("%-23s", "");
            }
            pr("%-7u", j);
            if (VTSS_FUNC(l2.icnt_get, vtss_icnt_idx(stat, j), &cnt) == VTSS_RC_OK) {
                VTSS_SPRINTF(buf, "%"PRIu64"/%"PRIu64"/%"PRIu64,
                        cnt.rx_green.frames, cnt.rx_yellow.frames, cnt.rx_red.frames);
                pr("%-25s", buf);
                c[0] = cnt.rx_green.bytes;
                c[1] = cnt.rx_yellow.bytes;
                c[2] = cnt.rx_red.bytes;
#if defined(VTSS_FEATURE_PSFP)
                if (vtss_state->init_conf.psfp_counters_enable) {
                    c[0] = cnt.rx_match;
                    c[1] = cnt.rx_gate_discard;
                    c[2] = cnt.rx_sdu_discard;
                }
#endif
                pr("%"PRIu64"/%"PRIu64"/%"PRIu64, c[0], c[1], c[2]);
            }
            pr("\n");
        }
    }
    if (!first) {
        pr("\n");
    }
}

static void vtss_debug_print_estat(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    vtss_xstat_entry_t     *stat;
    vtss_egress_counters_t cnt;
    u16                    i, j;
    BOOL                   first = TRUE;
    char                   buf[80];
    
    vtss_debug_print_xrow(vtss_state, pr, info, &vtss_state->l2.estat_table.hdr);
    for (i = 0; i < VTSS_EVC_STAT_CNT; i++) {
        stat = &vtss_state->l2.estat.table[i];
        if (stat->cnt == 0) {
            continue;
        }
        if (first) {
            first = FALSE;
            pr("Egress Counters:\n\n");
            pr("ID    IDX   CNT  COSID  Green/Yellow Frames  Green/Yellow Bytes\n");
        }
        for (j = 0; j < stat->cnt; j++) {
            if (j == 0) {
                pr("%-6u%-6u%-5u", i, stat->idx, stat->cnt);
            } else {
                pr("%-17s", "");
            }
            pr("%-7u", j);
            if (VTSS_FUNC(l2.ecnt_get, stat->idx + j, &cnt) == VTSS_RC_OK) {
                VTSS_SPRINTF(buf, "%"PRIu64"/%"PRIu64, cnt.tx_green.frames, cnt.tx_yellow.frames);
                pr("%-21s", buf);
                pr("%"PRIu64"/%"PRIu64, cnt.tx_green.bytes, cnt.tx_yellow.bytes);
            }
            pr("\n");
        }
    }
    if (!first) {
        pr("\n");
    }
}
#endif

#if defined(VTSS_FEATURE_PSFP)
static char *vtss_opt_bool_str(vtss_opt_bool_t *b, char *buf)
{
    if (b->enable) {
        VTSS_SPRINTF(buf, "%u", b->value ? 1 : 0);
    } else {
        VTSS_SPRINTF(buf, "%s", "-");
    }
    return buf;
}
#endif

#if defined(VTSS_FEATURE_XDLB)
static void vtss_debug_print_dlb(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    vtss_xpol_entry_t       *pol;
    vtss_dlb_policer_conf_t *conf;
    u16                     i, j;
    BOOL                    first = TRUE, cm = 1;

    vtss_debug_print_xrow(vtss_state, pr, info, &vtss_state->l2.pol_table.hdr);
    for (i = 0; i < VTSS_EVC_POL_CNT; i++) {
        pol = &vtss_state->l2.pol.table[i];
        if (pol->cnt == 0) {
            continue;
        }
        if (first) {
            first = FALSE;
            pr("DLB Policers:\n\n");
            pr("ID    IDX   CNT  COSID  Ena  Type    CM  CF  Rate  CIR         CBS         EIR         EBS");
#if defined(VTSS_FEATURE_PSFP)
            pr("         MarkRed  DropYellow");
#endif
            pr("\n");
        }
        for (j = 0; j < pol->cnt; j++) {
            if (j == 0) {
                pr("%-6u%-6u%-5u", i, pol->idx, pol->cnt);
            } else {
                pr("%-17s", "");
            }
            conf = &vtss_state->l2.pol_conf[pol->idx + j];
#if defined(VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5)
            cm = conf->cm;
#endif
            pr("%-7u%-5u%-8s%-4u%-4u%-6s%-12u%-12u%-12u%-12u",
               j,
               conf->enable,
               conf->type == VTSS_POLICER_TYPE_MEF ? "MEF" :
               conf->type == VTSS_POLICER_TYPE_SINGLE ? "SINGLE" : "?",
               cm, conf->cf, conf->line_rate ? "Line" : "Data", conf->cir, conf->cbs, conf->eir, conf->ebs);
#if defined(VTSS_FEATURE_PSFP)
            {
                vtss_dlb_policer_status_t status;
                char                      buf[16];
                pr("%s/%-7u%u",
                   vtss_opt_bool_str(&conf->mark_all_red, buf),
                   VTSS_FUNC(l2.policer_status_get, pol->idx + j, &status) == VTSS_RC_OK ? status.mark_all_red : 0,
                   conf->drop_yellow);
            }
#endif
            pr("\n");
        }
    }
    if (!first) {
        pr("\n");
    }
}
#endif

#if defined(VTSS_FEATURE_FRER)
static void vtss_debug_print_stream(const vtss_debug_printf_t pr, vtss_frer_stream_conf_t *conf, BOOL mstream)
{
    pr("%-5u%-5s%-6u%-6u",
       conf->recovery,
       conf->alg == VTSS_FRER_RECOVERY_ALG_VECTOR ? "Vcr" : "Mch",
       conf->hlen,
       conf->reset_time);
    if (mstream) {
        pr("%-6u", conf->cstream_id);
    }
    pr("\n");
}

static void vtss_debug_frer_cnt(const vtss_debug_printf_t pr, const char *name, vtss_counter_t cnt)
{
    char buf[80];

    VTSS_SPRINTF(buf, "%s:", name);
    pr("%-19s%19" PRIu64 "   \n", buf, cnt);
}

static void vtss_debug_print_frer_cnt(const vtss_debug_printf_t pr, vtss_frer_counters_t *c)
{
    vtss_debug_frer_cnt(pr, "OutOfOrder", c->out_of_order_packets);
    vtss_debug_frer_cnt(pr, "Rogue", c->rogue_packets);
    vtss_debug_frer_cnt(pr, "Passed", c->passed_packets);
    vtss_debug_frer_cnt(pr, "Discarded", c->discarded_packets);
    vtss_debug_frer_cnt(pr, "Lost", c->lost_packets);
    vtss_debug_frer_cnt(pr, "TagLess", c->tagless_packets);
    vtss_debug_frer_cnt(pr, "Resets", c->resets);
    pr("\n");
}

static void vtss_debug_print_frer(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    vtss_xms_entry_t        *ms;
    vtss_frer_stream_conf_t *conf;
    vtss_frer_counters_t    c;
    vtss_port_no_t          port_no;
    u16                     i, j, idx;
    BOOL                    first;

    vtss_debug_print_xrow(vtss_state, pr, info, &vtss_state->l2.ms_table.hdr);
    for (i = 0; i < 2; i++) {
        first = TRUE;
        for (j = 0; j < VTSS_MSTREAM_CNT; j++) {
            ms = &vtss_state->l2.ms.table[j];
            if (ms->cnt == 0) {
                continue;
            }
            idx = ms->idx;
            for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                if (VTSS_PORT_BF_GET(ms->port_list, port_no)) {
                    if (i == 0) {
                        /* Configuration */
                        if (first) {
                            first = FALSE;
                            pr("Member Streams:\n\n");
                            pr("MSID  Port  IDX   Rec  Alg  Hlen  Rst   CSID\n");
                        }
                        pr("%-6u%-6u%-6u", j, port_no, idx);
                        vtss_debug_print_stream(pr, &vtss_state->l2.mstream_conf[idx], TRUE);
                    } else if (VTSS_FUNC(l2.mstream_cnt_get, idx, &c) == VTSS_RC_OK &&
                               (info->clear == 0 || VTSS_FUNC(l2.mstream_cnt_get, idx, NULL) == VTSS_RC_OK)) {
                        /* Counters */
                        pr("Counters for MSID %u, port %u, IDX %u\n", j, port_no, idx);
                        vtss_debug_print_frer_cnt(pr, &c);
                    }
                    idx++;
                }
            }
        }
        if (!first) {
            first = TRUE;
            pr("\n");
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < VTSS_CSTREAM_CNT; j++) {
            conf = &vtss_state->l2.cstream_conf[j];
            if (conf->recovery == 0) {
                continue;
            }
            if (i == 0) {
                /* Configuration */
                if (first) {
                    first = FALSE;
                    pr("Compound Streams:\n\n");
                    pr("CSID  Rec  Alg  Hlen  Rst\n");
                }
                pr("%-6u", j);
                vtss_debug_print_stream(pr, conf, FALSE);
            } else if (VTSS_FUNC(l2.cstream_cnt_get, j, &c) == VTSS_RC_OK &&
                       (info->clear == 0 || VTSS_FUNC(l2.cstream_cnt_get, j, NULL) == VTSS_RC_OK)) {
                /* Counters */
                pr("Counters for CSID %u\n", j);
                vtss_debug_print_frer_cnt(pr, &c);
            }
        }
        if (!first) {
            first = TRUE;
            pr("\n");
        }
    }
}
#endif

#if defined(VTSS_FEATURE_PSFP)
static char *vtss_opt_prio_str(vtss_opt_prio_t *p, char *buf)
{
    if (p->enable) {
        VTSS_SPRINTF(buf, "%u", p->value);
    } else {
        VTSS_SPRINTF(buf, "%s", "-");
    }
    return buf;
}

static char *vtss_ts_str(vtss_timestamp_t *ts, char *buf, int max)
{
#if defined(VTSS_OPSYS_LINUX)
    time_t time = ts->seconds;
    struct tm timeinfo;
    struct tm *t = localtime_r(&time, &timeinfo);
    strftime(buf, max, "%Y-%m-%d %H:%M:%S", t);
#else
    VTSS_MEMSET(buf, 0, max);
#endif
    VTSS_SPRINTF((buf + VTSS_STRLEN(buf)), ".%09u (%u-%u)", ts->nanoseconds, ts->seconds, ts->nanoseconds);

    return buf;
}

static void vtss_debug_print_gcl(const vtss_debug_printf_t pr, vtss_psfp_gcl_conf_t *conf, vtss_psfp_gcl_t *gcl)
{
    u16  i;
    char buf[64];

    pr("BaseTime : %s\n", vtss_ts_str(&conf->base_time, buf, sizeof(buf)));
    pr("CycleTime: %u-%u\n", conf->cycle_time, conf->cycle_time_ext);
    for (i = 0; i < gcl->gcl_length; i++) {
        vtss_psfp_gce_t *gce = &gcl->gce[i];
        if (i == 0) {
            pr("\nIndex  Open  Priority  TimeInt     OctetMax\n");
        }
        pr("%-7u%-6u%-10s%-12u%u\n",
           i,
           gce->gate_open ? 1 : 0,
           vtss_opt_prio_str(&gce->prio, buf),
           gce->time_interval,
           gce->octet_max);
    }
}

static void vtss_debug_print_psfp(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    u16  i;
    BOOL first = TRUE;
    char buf[64];
    vtss_psfp_state_t *psfp = &vtss_state->l2.psfp;

    for (i = 0; i < VTSS_PSFP_FILTER_CNT; i++) {
        vtss_psfp_filter_conf_t   *conf = &psfp->filter[i];
        vtss_psfp_filter_status_t status;
        if (info->full || conf->gate_enable || conf->max_sdu || conf->block_oversize.enable) {
            if (first) {
                first = FALSE;
                pr("PSFP Filters:\n\n");
                pr("ID    Gate  MaxSDU  BlockOversize\n");
            }
            pr("%-6u", i);
            vtss_debug_print_w6(pr, conf->gate_enable, conf->gate_id);
            pr("%-8u%s/%u\n", conf->max_sdu, vtss_opt_bool_str(&conf->block_oversize, buf),
               VTSS_FUNC(l2.psfp_filter_status_get, i, &status) == VTSS_RC_OK ? status.block_oversize : 0);
        }
    }
    if (!first) {
        first = TRUE;
        pr("\n");
    }

    for (i = 0; i < VTSS_PSFP_GATE_CNT; i++) {
        vtss_psfp_gate_conf_t   *conf = &psfp->gate[i];
        vtss_psfp_gate_status_t status;
        if (info->full || conf->enable) {
            if (first) {
                first = FALSE;
                pr("PSFP Gates:\n\n");
            }
            pr("Gate ID  : %u\n", i);
            pr("Enabled  : %u\n", conf->enable ? 1 : 0);
            pr("Open     : %u\n", conf->gate_open ? 1 : 0);
            pr("Priority : %s\n", vtss_opt_prio_str(&conf->prio, buf));
            pr("InvRx    : %s\n", vtss_opt_bool_str(&conf->close_invalid_rx, buf));
            pr("OctExc   : %s\n", vtss_opt_bool_str(&conf->close_octets_exceeded, buf));
            pr("Change   : %u\n", conf->config_change ? 1 : 0);
            vtss_debug_print_gcl(pr, &conf->config, &psfp->admin_gcl[i]);
            pr("\n");
            if (vtss_gate_status_get(vtss_state, i, &status) == VTSS_RC_OK) {
                pr("Status\n");
                pr("Open     : %u\n", status.gate_open ? 1 : 0);
                pr("Priority : %s\n", vtss_opt_prio_str(&status.prio, buf));
                pr("ChgTime  : %s\n", vtss_ts_str(&status.config_change_time, buf, sizeof(buf)));
                pr("CurTime  : %s\n", vtss_ts_str(&status.current_time, buf, sizeof(buf)));
                pr("Pending  : %u\n", status.config_pending ? 1 : 0);
                pr("InvRx    : %u\n", status.close_invalid_rx);
                pr("OctExc   : %u\n", status.close_octets_exceeded);
                vtss_debug_print_gcl(pr, &psfp->oper_conf[i], &psfp->oper_gcl[i]);
                pr("\n");
            }
        }
    }
}
#endif

#if defined(VTSS_FEATURE_RCL)
static void vtss_debug_print_rcl(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    vtss_rcl_vid_entry_t *entry;
    u8                   i, j;
    BOOL                 first = TRUE;

    for (i = 0; i < VTSS_RCL_VID_CNT; i++) {
        entry = &vtss_state->l2.rcl_vid[i];
        if (entry->enable) {
            if (first) {
                first = FALSE;
                pr("RCL VID  Entries:\n\n");
                pr("IDX  VID   PCP[0-7]\n");
            }
            pr("%-5u%-6u", i, entry->vid);
            for (j = 0; j < VTSS_PCPS; j++) {
                pr("%u", entry->conf.pcp[j] ? 1 : 0);
            }
            pr("\n");
        }
    }
}
#endif

#if defined(VTSS_FEATURE_VCAP)
static void vtss_debug_print_vcl(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    vtss_port_no_t       port_no;
    vtss_vcl_port_conf_t *conf;
    BOOL                 first = TRUE;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no]) {
            continue;
        }
        if (first) {
            first = FALSE;
            pr("VCL Port Configuration:\n\n");
            pr("Port  Key Type      DMAC/DIP\n");
        }
        conf = &vtss_state->l2.vcl_port_conf[port_no];
        pr("%-6u%-14s%s\n",
           port_no, vtss_vcap_key_type2txt(conf->key_type), vtss_bool_txt(conf->dmac_dip));
    }
    if (!first) {
        pr("\n");
    }
}

static void vtss_debug_print_vlan_trans(vtss_state_t *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const vtss_debug_info_t   *const info)
{
    vtss_vlan_trans_grp2vlan_conf_t conf;
    vtss_vlan_trans_port2grp_conf_t port_conf;
    BOOL                            next = FALSE;

    pr("VLAN Translation Group Table\n");
    pr("----------------------------\n");
    VTSS_MEMSET(&conf, 0, sizeof(vtss_vlan_trans_grp2vlan_conf_t));
    while ((vtss_cmn_vlan_trans_group_get(vtss_state, &conf, next)) == VTSS_RC_OK) {
        if (!next) {
            pr("GroupID  VID   Trans_VID  Direction\n");
            pr("-------  ---   ---------  ---------\n");
            next = TRUE;
        }
        pr("%-9u%-6u%-11u%s\n", conf.group_id, conf.vid, conf.trans_vid, vtss_vlan_trans_dir_txt(conf.dir));
    }
    pr("\nVLAN Translation Port Table\n");
    pr("---------------------------\n");
    next = FALSE;
    //vtss_cmn_vlan_trans_port_conf_get(vtss_vlan_trans_port2grp_conf_t *conf, BOOL next);
    VTSS_MEMSET(&port_conf, 0, sizeof(vtss_vlan_trans_port2grp_conf_t));
    while ((vtss_cmn_vlan_trans_port_conf_get(vtss_state, &port_conf, next)) == VTSS_RC_OK) {
        if (!next) {
            pr("GroupID  Ports\n");
            pr("-------  -----\n");
            next = TRUE;
        }
        pr("%-7u  ", port_conf.group_id);
        vtss_debug_print_ports(vtss_state, pr, port_conf.ports, 1);
    }

    pr("\n");
#if defined(VTSS_FEATURE_IS1) || defined(VTSS_FEATURE_CLM)
    vtss_vcap_debug_print_is1(vtss_state, pr, info);
#endif /* VTSS_FEATURE_IS1/CLM */
    vtss_vcap_debug_print_es0(vtss_state, pr, info);
    vtss_debug_print_vcl(vtss_state, pr, info);
#if defined(VTSS_FEATURE_XFLOW)
    vtss_debug_print_iflow(vtss_state, pr, info);
#endif
#if defined(VTSS_FEATURE_XSTAT)
    vtss_debug_print_istat(vtss_state, pr, info);
#endif
#if defined(VTSS_FEATURE_XDLB)
    vtss_debug_print_dlb(vtss_state, pr, info);
#endif
#if defined(VTSS_FEATURE_XFLOW)
    vtss_debug_print_eflow(vtss_state, pr, info);
#endif
#if defined(VTSS_FEATURE_XSTAT)
    vtss_debug_print_estat(vtss_state, pr, info);
#endif
#if defined(VTSS_FEATURE_FRER)
    vtss_debug_print_frer(vtss_state, pr, info);
#endif
#if defined(VTSS_FEATURE_PSFP)
    vtss_debug_print_psfp(vtss_state, pr, info);
#endif
#if defined(VTSS_FEATURE_RCL)
    vtss_debug_print_rcl(vtss_state, pr, info);
#endif
}
#endif // VTSS_FEATURE_VCAP
#endif // VTSS_OPT_DEBUG_PRINT

#if defined(VTSS_FEATURE_VCAP)
/* VTE(VLAN Translation Entry) ID */
static vtss_vcap_id_t vtss_vt_is1_vte_id_get(const vtss_vlan_trans_grp2vlan_conf_t *conf)
{
    return ((conf->group_id << 12) + conf->vid);
}

/* Add IS1 TCAM entry for the VLAN Translation */
static vtss_rc vtss_vt_is1_entry_add(vtss_state_t *vtss_state,
                                     const vtss_vlan_trans_grp2vlan_conf_t *conf,
                                     const u8 *ports)
{
    vtss_vcap_obj_t             *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_user_t            user = VTSS_IS1_USER_VLAN;
    vtss_vcap_data_t            data;
    vtss_is1_data_t             *is1 = &data.u.is1;
    vtss_is1_entry_t            entry;
    vtss_is1_action_t           *action = &entry.action;
    vtss_is1_key_t              *key = &entry.key;
    vtss_vcap_key_size_t        key_size = VTSS_VCAP_KEY_SIZE_FULL;
    u32                         i;
    vtss_vcap_id_t              vte_id = vtss_vt_is1_vte_id_get(conf);

    VTSS_D("vtss_vt_is1_entry_add - vte_id: 0x%" PRIx64 ", vid: %u, trans_vid: %u", vte_id, conf->vid, conf->trans_vid);
    /* Initialize entry data */
    vtss_vcap_is1_init(&data, &entry);

    /* First Lookup */
    is1->lookup = 0;

    /* Copy port list */
    for (i = 0; i < VTSS_PORT_ARRAY_SIZE; i++) {
        key->port_list[i] = (ports[i/8] & (1 << (i % 8)) ? TRUE : FALSE);
    }
    is1->port_no = vtss_cmn_first_port_no_get(vtss_state, key->port_list);

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    is1->lookup = 1; /* Second lookup */
    vtss_cmn_key_type_get(vtss_state, is1->port_no, is1->lookup, key, &key_size);
#endif /* VTSS_ARCH_OCELOT */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    if (vtss_state->arch == VTSS_ARCH_JR2 || vtss_state->arch == VTSS_ARCH_ANT) {
        vtss_cmn_key_type_get(vtss_state, is1->port_no, is1->lookup, key, &key_size);
    }
#endif
    data.key_size = key_size;

    /* Copy action data */
    action->vid = conf->trans_vid;

    /* VID is of type value/mask */
    key->tag.vid.type = VTSS_VCAP_VR_TYPE_VALUE_MASK;
    key->tag.vid.vr.v.value = conf->vid;
    key->tag.vid.vr.v.mask = 0xFFFF;
    /* Allow only for tagged frames */
    key->tag.tagged = VTSS_VCAP_BIT_1;
    key->type = VTSS_IS1_TYPE_ANY;

    /* Add main entry */
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, vte_id, VTSS_VCAP_ID_GT, &data, 0));
    return VTSS_RC_OK;
}
/* Delete IS1 TCAM entry for the VLAN Translation */
static vtss_rc vtss_vt_is1_entry_del(vtss_state_t *vtss_state,
                                     vtss_vlan_trans_grp2vlan_conf_t *conf)
{
    vtss_vcap_obj_t  *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_user_t user = VTSS_IS1_USER_VLAN;
    vtss_vcap_data_t data;
    vtss_is1_data_t  *is1 = &data.u.is1;
    vtss_vcap_id_t   vte_id = vtss_vt_is1_vte_id_get(conf);

    if (vtss_vcap_lookup(vtss_state, obj, user, vte_id, &data, NULL) != VTSS_RC_OK) {
        VTSS_E("vte_id: %" PRIu64 " not found", vte_id);
        return VTSS_RC_ERROR;
    }
    /* Delete range checkers and main entry */
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->vid_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->dscp_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->sport_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->dport_range));
    VTSS_RC(vtss_vcap_del(vtss_state, obj, user, vte_id));
    return VTSS_RC_OK;
}

/* ES0 index derived from VID (11:0 bits) and Port number (64:12 bits) */
static vtss_vcap_id_t vtss_vt_es0_vte_id_get(const vtss_vlan_trans_grp2vlan_conf_t *conf, const vtss_port_no_t port_no)
{
    vtss_vcap_id_t id = port_no;

    return ((id << 12) + conf->trans_vid);
}

/* VLAN Translation function to add entry to ES0 */
static vtss_rc vtss_vt_es0_entry_add(vtss_state_t *vtss_state,
                                     const vtss_vlan_trans_grp2vlan_conf_t *conf,
                                     const vtss_port_no_t port_no)
{
    vtss_vcap_data_t data;
    vtss_es0_entry_t entry;
    vtss_vcap_id_t   id;

    id = vtss_vt_es0_vte_id_get(conf, port_no);
    vtss_cmn_es0_data_set(vtss_state, port_no, conf->trans_vid, conf->vid, 1, &data, &entry);

    return vtss_vcap_add(vtss_state, &vtss_state->vcap.es0.obj, VTSS_ES0_USER_VLAN, id, VTSS_VCAP_ID_GT, &data, 0);
}

/* VLAN Translation function to delete entry to ES0 */
static vtss_rc vtss_vt_es0_entry_del(vtss_state_t *vtss_state,
                                     vtss_vlan_trans_grp2vlan_conf_t *conf,
                                     const vtss_port_no_t port_no)
{
    vtss_vcap_id_t id;

    id = vtss_vt_es0_vte_id_get(conf, port_no);
    return vtss_vcap_del(vtss_state, &vtss_state->vcap.es0.obj, VTSS_ES0_USER_VLAN, id);
}

/* Helper function to calculate number of set bits in a byte */
static u8 bitcount(u8 n)
{
    u8 cnt = 0;
    while (n)
    {
        n &= (n-1);
        cnt++;
    }
    return cnt;
}

static BOOL vtss_vlan_trans_group_match(const vtss_vlan_trans_grp2vlan_conf_t *a,
                                        const vtss_vlan_trans_grp2vlan_conf_t *b)
{
    // Check if ingress/egress key matches
    return (a->group_id == b->group_id &&
            ((a->dir != VTSS_VLAN_TRANS_DIR_EGRESS && b->dir != VTSS_VLAN_TRANS_DIR_EGRESS && a->vid == b->vid) ||
             (a->dir != VTSS_VLAN_TRANS_DIR_INGRESS && b->dir != VTSS_VLAN_TRANS_DIR_INGRESS && a->trans_vid == b->trans_vid)));
}

/* Add entry to the VLAN Translation group list */
static vtss_rc vtss_vlan_trans_group_list_add(vtss_state_t *vtss_state,
                                              const vtss_vlan_trans_grp2vlan_conf_t *conf)
{
    vtss_vlan_trans_grp2vlan_t       *list = &vtss_state->l2.vt_trans_conf;
    vtss_vlan_trans_grp2vlan_entry_t *tmp, *prev, *new = NULL;

    /* Insert the new node into the used list */
    for (tmp = list->used, prev = NULL; tmp != NULL; tmp = tmp->next) {
        /* Check to see if the translation is already configured for this group */
        if (vtss_vlan_trans_group_match(&tmp->conf, conf)) {
            // Ingress/egress match found
            if (new != NULL) {
                VTSS_I("translation conflict");
                return VTSS_RC_ERROR;
            }
            new = tmp;
        }

        // We are only looking for matches in the same group
        if (conf->group_id < tmp->conf.group_id) {
            break;
        }

        // List is sorted based on (group_id, vid, trans_vid)
        if (conf->group_id > tmp->conf.group_id || conf->vid > tmp->conf.vid ||
            (conf->vid == tmp->conf.vid && conf->trans_vid > tmp->conf.trans_vid)) {
            prev = tmp;
        }
    }

    if (new == NULL) {
        // Take entry from free list for new translation
        if ((new = list->free) == NULL) {  /* No free entry exists */
            return VTSS_RC_ERROR;
        }
        list->free = new->next;

        // Insert entry in used list
        if (prev == NULL) {
            new->next = list->used;
            list->used = new;
        } else {
            new->next = prev->next;
            prev->next = new;
        }
    }

    /* Copy the configuration */
    new->conf = *conf;
    return VTSS_RC_OK;
}

/* Delete entry to the VLAN Translation group list */
static vtss_rc vtss_vlan_trans_group_list_del(vtss_state_t *vtss_state,
                                              vtss_vlan_trans_grp2vlan_conf_t *conf)
{
    vtss_vlan_trans_grp2vlan_t       *list = &vtss_state->l2.vt_trans_conf;
    vtss_vlan_trans_grp2vlan_entry_t *tmp, *prev;

    /* Search used list to find matching entry */
    for (tmp = list->used, prev = NULL; tmp != NULL; prev = tmp, tmp = tmp->next) {
        if (conf->group_id == tmp->conf.group_id && conf->dir == tmp->conf.dir &&
            conf->vid == tmp->conf.vid && conf->trans_vid == tmp->conf.trans_vid) {
            /* Remove from the used list */
            if (prev == NULL) {
                list->used = tmp->next;
            } else {
                prev->next = tmp->next;
            }

            /* Add to the free list */
            tmp->next = list->free;
            list->free = tmp;
            return VTSS_RC_OK;
        }
    }
    return VTSS_RC_ERROR;
}

static vtss_rc vtss_vlan_trans_group_list_get(vtss_state_t *vtss_state,
                                              vtss_vlan_trans_grp2vlan_conf_t *conf)
{
    vtss_vlan_trans_grp2vlan_t       *list = &vtss_state->l2.vt_trans_conf;
    vtss_vlan_trans_grp2vlan_entry_t *tmp;

    /* Search used list to find out matching entry */
    for (tmp = list->used; tmp != NULL; tmp = tmp->next) {
        if (vtss_vlan_trans_group_match(&tmp->conf, conf)) {
            // Ingress/egress match found
            *conf = tmp->conf;
            return VTSS_RC_OK;
        }
    }
    return VTSS_RC_ERROR;
}

/* VLAN Translation function to add IS1 and ES0 entries for a group */
static void vtss_vlan_trans_group_hw_entries_add(vtss_state_t *vtss_state,
                                                 const u16 group_id, u8 *ports)
{
    vtss_vlan_trans_grp2vlan_t       *list = &vtss_state->l2.vt_trans_conf;
    vtss_vlan_trans_grp2vlan_entry_t *tmp;
    vtss_port_no_t                   port_no;
    vtss_vlan_trans_grp2vlan_conf_t  *conf;

    /* Search used list to find out matching entry */
    for (tmp = list->used; tmp != NULL; tmp = tmp->next) {
        conf = &tmp->conf;
        if (group_id != conf->group_id) {
            continue;
        }

        // Add ingress rule
        if (conf->dir != VTSS_VLAN_TRANS_DIR_EGRESS && vtss_vt_is1_entry_add(vtss_state, conf, ports) != VTSS_RC_OK) {
            VTSS_D("vtss_vlan_trans_group_hw_entries_add: IS1 entry add failed");
        }

        // Add egress rules
        if (conf->dir != VTSS_VLAN_TRANS_DIR_INGRESS) {
            for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                if (VTSS_PORT_BF_GET(ports, port_no) &&
                    vtss_vt_es0_entry_add(vtss_state, conf, port_no) != VTSS_RC_OK) {
                    VTSS_D("vtss_vlan_trans_group_hw_entries_add: ES0 entry add failed");
                }
            }
        }
    }
}

/* VLAN Translation function to delete IS1 and ES0 entries for a group */
static void vtss_vlan_trans_group_hw_entries_del(vtss_state_t *vtss_state,
                                                 const u16 group_id, u8 *ports)
{
    vtss_vlan_trans_grp2vlan_t       *list = &vtss_state->l2.vt_trans_conf;
    vtss_vlan_trans_grp2vlan_entry_t *tmp;
    vtss_port_no_t                   port_no;
    vtss_vlan_trans_grp2vlan_conf_t  *conf;

    /* Search used list to find out matching entry */
    for (tmp = list->used; tmp != NULL; tmp = tmp->next) {
        conf = &tmp->conf;
        if (group_id != conf->group_id) {
            continue;
        }

        // Delete ingress rule
        if (conf->dir != VTSS_VLAN_TRANS_DIR_EGRESS && vtss_vt_is1_entry_del(vtss_state, conf) != VTSS_RC_OK) {
            VTSS_D("vtss_vlan_trans_group_hw_entries_del: IS1 entry delete failed");
        }

        // Delete egress rules
        if (conf->dir != VTSS_VLAN_TRANS_DIR_INGRESS) {
            for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                if (VTSS_PORT_BF_GET(ports, port_no) &&
                    vtss_vt_es0_entry_del(vtss_state, conf, port_no) != VTSS_RC_OK) {
                    VTSS_D("vtss_vlan_trans_group_hw_entries_del: ES0 entry delete failed");
                }
            }
        }
    }
}

/* VLAN Translation helper function to update all the IS1 and ES0 entries based on port list */
static vtss_rc vtss_vlan_trans_group_port_list_update(vtss_state_t *vtss_state,
                                                      const u16 group_id, const u8 *ports,
                                                      const u8 *new_ports, const BOOL update)
{
    vtss_vlan_trans_grp2vlan_t       *list = &vtss_state->l2.vt_trans_conf;
    vtss_vlan_trans_grp2vlan_entry_t *tmp;
    vtss_port_no_t                   port_no;
    BOOL                             ingress, egress;
    vtss_vlan_trans_grp2vlan_conf_t  *conf;

    /* Search used list to find out matching entry */
    for (tmp = list->used; tmp != NULL; tmp = tmp->next) {
        conf = &tmp->conf;
        if (group_id != conf->group_id) {
            continue;
        }

        ingress = (conf->dir == VTSS_VLAN_TRANS_DIR_EGRESS ? FALSE : TRUE);
        egress = (conf->dir == VTSS_VLAN_TRANS_DIR_INGRESS ? FALSE : TRUE);
        if (update == TRUE) {
            // Delete ingress rule
            if (ingress && vtss_vt_is1_entry_del(vtss_state, conf) != VTSS_RC_OK) {
                VTSS_D("vtss_vlan_trans_group_port_list_update: IS1 entry delete failed");
            } /* if ((vtss_vt_is1_entry_del( */

            // Delete egress rules
            if (egress) {
                for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                    if (VTSS_PORT_BF_GET(ports, port_no) &&
                        vtss_vt_es0_entry_del(vtss_state, conf, port_no) != VTSS_RC_OK) {
                        VTSS_D("vtss_vlan_trans_group_port_list_update: ES0 entry delete failed");
                    }
                }
            }
        }

        // Add ingress rule
        if (ingress && vtss_vt_is1_entry_add(vtss_state, conf, new_ports) != VTSS_RC_OK) {
            VTSS_D("vtss_vlan_trans_group_port_list_update: IS1 entry addition failed");
        }

        // Add egress rules
        if (egress) {
            for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                if (VTSS_PORT_BF_GET(new_ports, port_no) &&
                    vtss_vt_es0_entry_add(vtss_state, conf, port_no) != VTSS_RC_OK) {
                    VTSS_D("vtss_vlan_trans_group_port_list_update: ES0 entry addition failed");
                }
            }
        }
    }
    return VTSS_RC_OK;
}

/* VLAN Translation function to fetch port_list for this group */
static vtss_rc vtss_vlan_trans_port_list_get(vtss_state_t *vtss_state,
                                             const u16 group_id, u8 *ports)
{
    vtss_vlan_trans_port2grp_t       *list = &vtss_state->l2.vt_port_conf;
    vtss_vlan_trans_port2grp_entry_t *tmp;

    VTSS_MEMSET(ports, 0, VTSS_VLAN_TRANS_PORT_BF_SIZE);
    for (tmp = list->used; tmp != NULL; tmp = tmp->next) {
        if (tmp->conf.group_id == group_id) {
            VTSS_MEMCPY(ports, tmp->conf.ports, VTSS_VLAN_TRANS_PORT_BF_SIZE);
            return VTSS_RC_OK;
        }
    }
    return VTSS_RC_ERROR;
}

static void vtss_vlan_trans_group_trans_cnt(vtss_state_t *vtss_state,
                                            const u16 group_id, u32 *in_cnt, u32 *eg_cnt)
{
    vtss_vlan_trans_grp2vlan_t       *list = &vtss_state->l2.vt_trans_conf;
    vtss_vlan_trans_grp2vlan_entry_t *tmp;
    u32                              rx_cnt = 0, tx_cnt = 0;

    /* Search used list to find out matching entry */
    for (tmp = list->used; tmp != NULL; tmp = tmp->next) {
        if (group_id == tmp->conf.group_id) {
            if (tmp->conf.dir != VTSS_VLAN_TRANS_DIR_EGRESS) {
                rx_cnt++;
            }
            if (tmp->conf.dir != VTSS_VLAN_TRANS_DIR_INGRESS) {
                tx_cnt++;
            }
        }
    }
    *in_cnt = rx_cnt;
    *eg_cnt = tx_cnt;
}

static vtss_rc vtss_vlan_trans_res_check(vtss_state_t *vtss_state,
                                         const u16 group_id, const u8 *ports)
{
    vtss_vlan_trans_port2grp_t       *port_list = &vtss_state->l2.vt_port_conf;
    vtss_vlan_trans_port2grp_entry_t *tmp;
    vtss_vlan_trans_port2grp_conf_t  conf;
    BOOL                             del_entry, grp_found = FALSE;
    u32                              i, k, port_cnt, in_cnt, eg_cnt;
    u32                              orig_port_cnt = 0;
    u32                              is1_add = 0, is1_del = 0, es0_add = 0, es0_del = 0;
    vtss_res_t                       res;

    for (tmp = port_list->used; tmp != NULL; tmp = tmp->next) {
        conf = tmp->conf; // Copy configuration
        if (group_id != conf.group_id) {
            port_cnt = 0;
            del_entry = TRUE;
            for (i = 0; i < VTSS_PORT_BF_SIZE; i++) {
                for (k = 0; k < 8; k++) {
                    if (ports[i] & conf.ports[i] & (1 << k)) {
                        port_cnt++;
                    }
                }
                /* Remove the ports and check if more ports are left */
                conf.ports[i] &= ~(ports[i]);
                if (conf.ports[i]) {
                    del_entry = FALSE;
                }
            }
            if (port_cnt != 0) {
                /* Get number of VLAN Translations defined for this group */
                vtss_vlan_trans_group_trans_cnt(vtss_state, conf.group_id, &in_cnt, &eg_cnt);
                if (del_entry && in_cnt) {
                    is1_del++;
                }
                es0_del += (port_cnt * eg_cnt);
            }
        } else {
            grp_found = TRUE;
            orig_port_cnt = 0;
            port_cnt = 0;
            for (i = 0; i < VTSS_PORT_BF_SIZE; i++) {
                orig_port_cnt += bitcount(conf.ports[i]);
                conf.ports[i] |= ports[i];
                port_cnt += bitcount(conf.ports[i]);
            }
            /* Get number of VLAN Translations defined for this group */
            vtss_vlan_trans_group_trans_cnt(vtss_state, group_id, &in_cnt, &eg_cnt);
            VTSS_D("in_cnt = %u, eg_cnt = %u, port_cnt = %u, orig_port_cnt = %u", in_cnt, eg_cnt, port_cnt, orig_port_cnt);
            /* IS1 entry will only get updated */
            es0_add += (eg_cnt * (port_cnt - orig_port_cnt));
        }
    }

    if (grp_found == FALSE) {
        port_cnt = 0;
        for (i = 0; i < VTSS_PORT_BF_SIZE; i++) {
            port_cnt += bitcount(ports[i]);
        }
        /* Get number of VLAN Translations defined for this group */
        vtss_vlan_trans_group_trans_cnt(vtss_state, group_id, &in_cnt, &eg_cnt);
        is1_add += in_cnt;
        VTSS_D("in_cnt = %u, eg_cnt = %u, port_cnt = %u", in_cnt, eg_cnt, port_cnt);
        es0_add += eg_cnt * port_cnt;
    }
    VTSS_D("is1_add = %u, is1_del = %u, es0_add = %u, es0_del = %u", is1_add, is1_del, es0_add, es0_del);

    /* Resource check based on add/delete count */
    vtss_cmn_res_init(&res);
    if (vtss_state->arch == VTSS_ARCH_JR2) {
        res.clm_b.add = is1_add;
        res.clm_b.del = is1_del;
    } else {
        res.is1.add = is1_add;
        res.is1.del = is1_del;
    }
    res.es0.add = es0_add;
    res.es0.del = es0_del;
    return vtss_cmn_res_check(vtss_state, &res);
}

/* VLAN Translation function to update all the port to group mappings and delete if none
   of the ports exist for a group */
static vtss_rc vtss_vlan_trans_port_list_del(vtss_state_t *vtss_state, const u8 *ports)
{
    vtss_vlan_trans_port2grp_t       *list = &vtss_state->l2.vt_port_conf;
    vtss_vlan_trans_port2grp_entry_t *tmp, *prev;
    vtss_vlan_trans_port2grp_conf_t  conf;
    BOOL                             modified_entry, del_entry;
    u32                              i;

    /* Delete all the port to group mappings corresponding to the ports list */
    for (tmp = list->used, prev = NULL; tmp != NULL;) {
        modified_entry = FALSE;
        conf = tmp->conf; // Copy configuration
        for (i = 0; i < VTSS_PORT_BF_SIZE; i++) {
            if (ports[i] & conf.ports[i]) {
                modified_entry = TRUE;
                /* Remove the ports */
                tmp->conf.ports[i] &= ~(ports[i]);
            }
        }
        /* As a result of port deletes, if an entry exists with no ports, delete the entry */
        if (modified_entry == TRUE) {
            vtss_vlan_trans_group_hw_entries_del(vtss_state, conf.group_id, conf.ports);
            del_entry = TRUE;
            for (i = 0; i < VTSS_PORT_BF_SIZE; i++) {
                if (tmp->conf.ports[i]) {
                    del_entry = FALSE;
                }
            }
            if (del_entry) { /* None of the ports is valid, so delete the entry */
                if (prev == NULL) { /* Delete the first node */
                    /* Remove from the used list */
                    list->used = tmp->next;
                } else {
                    /* Remove from the used list */
                    prev->next = tmp->next;
                }
                /* Add to the free list */
                tmp->next = list->free;
                list->free = tmp;
                /* Update tmp to continue the loop */
                if (prev == NULL) { /* This is the first node in used list */
                    tmp = list->used;
                    continue;
                } else {
                    tmp = prev;
                } /* if (prev == NULL) */
            } else { /* If some ports are valid, we need to add the IS1 and ES0 entries */
                vtss_vlan_trans_group_hw_entries_add(vtss_state, conf.group_id, tmp->conf.ports);
            }
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return VTSS_RC_OK;
}

/* VLAN Translation function to add VLAN Translation entry into a group */
vtss_rc vtss_cmn_vlan_trans_group_add(vtss_state_t *vtss_state,
                                      const vtss_vlan_trans_grp2vlan_conf_t *const conf_add)
{
    u8                              ports[VTSS_VLAN_TRANS_PORT_BF_SIZE], port_cnt = 0;
    vtss_port_no_t                  port_no;
    BOOL                            ports_exist = TRUE;
    u32                             i;
    vtss_res_t                      res;
    vtss_res_chg_t                  *chg;
    vtss_vlan_trans_grp2vlan_conf_t conf;

    VTSS_MEMSET(ports, 0, VTSS_VLAN_TRANS_PORT_BF_SIZE);
    /* Fetch port_list for this group */
    if ((vtss_vlan_trans_port_list_get(vtss_state, conf_add->group_id, ports)) != VTSS_RC_OK) {
        ports_exist = FALSE;
        VTSS_D("No Port mapping for this group");
    }

    // Calculate and check ressources
    vtss_cmn_res_init(&res);
    chg = (vtss_state->arch == VTSS_ARCH_JR2 ? &res.clm_c : &res.is1);
    if (ports_exist == TRUE) {
        for (i = 0; i < VTSS_VLAN_TRANS_PORT_BF_SIZE; i++) {
            port_cnt += bitcount(ports[i]);
        }
        VTSS_I("VLAN Translation: Port Count = %u", port_cnt);

        /* We need one IS1 entry and port_cnt number of ES0 VLAN Translations. Check for VCAP resources */
        conf = *conf_add;
        if (vtss_vlan_trans_group_list_get(vtss_state, &conf) == VTSS_RC_OK) {
            if (conf.dir != VTSS_VLAN_TRANS_DIR_EGRESS) {
                // Ingress rule must be deleted
                chg->del = 1;
            }
            if (conf.dir != VTSS_VLAN_TRANS_DIR_INGRESS) {
                // Egress rules must be deleted
                res.es0.del = port_cnt;
            }
        }
        if (conf_add->dir != VTSS_VLAN_TRANS_DIR_EGRESS) {
            // Ingress rule must be added/updated
            chg->add = 1;
        }
        if (conf_add->dir != VTSS_VLAN_TRANS_DIR_INGRESS) {
            // Egress rules must be added/updated
            res.es0.add = port_cnt;
        }
        VTSS_RC(vtss_cmn_res_check(vtss_state, &res));
    }

    /* Add to the state list */
    VTSS_RC(vtss_vlan_trans_group_list_add(vtss_state, conf_add));

    if (ports_exist == TRUE) {
        if (chg->del) {
            // Delete ingress rule
            if ((vtss_vt_is1_entry_del(vtss_state, &conf)) != VTSS_RC_OK) {
                return VTSS_RC_ERROR;
            }
        }
        if (chg->add) {
            // Add/update ingress rule
            if ((vtss_vt_is1_entry_add(vtss_state, conf_add, ports)) != VTSS_RC_OK) {
                return VTSS_RC_ERROR;
            }
        }

        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (VTSS_PORT_BF_GET(ports, port_no)) {
                if (res.es0.del) {
                    // Delete egress rule
                    VTSS_RC(vtss_vt_es0_entry_del(vtss_state, &conf, port_no));
                }
                if (res.es0.add) {
                    // Add/update egress rule
                    VTSS_RC(vtss_vt_es0_entry_add(vtss_state, conf_add, port_no));
                }
            }
        }
    }
    return VTSS_RC_OK;
}

/* VLAN Translation function to delete a VLAN Translation entry from a group */
vtss_rc vtss_cmn_vlan_trans_group_del(vtss_state_t *vtss_state,
                                      const vtss_vlan_trans_grp2vlan_conf_t *conf_del)
{
    u8                              ports[VTSS_VLAN_TRANS_PORT_BF_SIZE];
    vtss_port_no_t                  port_no;
    vtss_vlan_trans_grp2vlan_conf_t conf;
    BOOL                            ports_exist = TRUE;

    VTSS_MEMSET(ports, 0, VTSS_VLAN_TRANS_PORT_BF_SIZE);
    /* Fetch port_list for this group */
    if ((vtss_vlan_trans_port_list_get(vtss_state, conf_del->group_id, ports)) != VTSS_RC_OK) {
        ports_exist = FALSE;
        VTSS_D("No Port mapping for this group");
    }

    // Lookup translation
    conf = *conf_del;
    VTSS_RC(vtss_vlan_trans_group_list_get(vtss_state, &conf));

    if (ports_exist == TRUE) {
        // Delete ingress rule
        if (conf.dir != VTSS_VLAN_TRANS_DIR_EGRESS) {
            VTSS_RC(vtss_vt_is1_entry_del(vtss_state, &conf));
        }

        // Delete egress rules
        if (conf.dir != VTSS_VLAN_TRANS_DIR_INGRESS) {
            for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                if (VTSS_PORT_BF_GET(ports, port_no)) {
                    VTSS_RC(vtss_vt_es0_entry_del(vtss_state, &conf, port_no));
                }
            }
        }
    }

    /* Delete from the state list */
    return vtss_vlan_trans_group_list_del(vtss_state, &conf);
}

/* VLAN Translation function to fetch a VLAN Translation entry for a group; next parameter is only valid
   if both the group_id and vid are valid */
vtss_rc vtss_cmn_vlan_trans_group_get(vtss_state_t *vtss_state,
                                      vtss_vlan_trans_grp2vlan_conf_t *conf, BOOL next)
{
    vtss_vlan_trans_grp2vlan_t       *list = &vtss_state->l2.vt_trans_conf;;
    vtss_vlan_trans_grp2vlan_entry_t *tmp;
    BOOL                             next_entry = FALSE;

    if (conf == NULL) {
        VTSS_E("VLAN Translation: NULL pointer");
        return VTSS_RC_ERROR;
    }

    if (list->used == NULL) {
        VTSS_D("Group list is empty");
        return VTSS_RC_ERROR;
    }

    /* If group_id is 0, return first entry */
    if (conf->group_id == VTSS_VLAN_TRANS_NULL_GROUP_ID) {
        *conf = list->used->conf;
        return VTSS_RC_OK;
    }

    for (tmp = list->used; tmp != NULL; tmp = tmp->next) {
        if (next_entry) {
            *conf = tmp->conf;
            return VTSS_RC_OK;
        }
        if (conf->group_id == tmp->conf.group_id &&
            (conf->vid == 0 || vtss_vlan_trans_group_match(&tmp->conf, conf))) {
            if (!next || conf->vid == 0) {
                /* Return first entry if vid is 0 or return matching entry */
                *conf = tmp->conf;
                return VTSS_RC_OK;
            }
            next_entry = TRUE;
        }
    }
    return VTSS_RC_ERROR;
}

/* VLAN Translation function to associate ports to a group. Only one port can be part
   of one group not multiple groups */
vtss_rc vtss_cmn_vlan_trans_port_conf_set(vtss_state_t *vtss_state,
                                          const vtss_vlan_trans_port2grp_conf_t *conf)
{
    vtss_vlan_trans_port2grp_t       *list = &vtss_state->l2.vt_port_conf;
    vtss_vlan_trans_port2grp_entry_t *tmp, *prev, *new = NULL;
    vtss_vlan_trans_port2grp_conf_t  old_conf;
    u32                              i;

    if ((vtss_vlan_trans_res_check(vtss_state, conf->group_id, conf->ports)) != VTSS_RC_OK) {
        VTSS_D("VLAN Translation: Not enough resources to add the entry");
        return VTSS_RC_ERROR;
    }
    if ((vtss_vlan_trans_port_list_del(vtss_state, conf->ports)) != VTSS_RC_OK) {
        VTSS_D("VLAN Translation: vtss_vlan_trans_port_list_del failed");
    }

    /* Insert the new node into the used list */
    for (tmp = list->used, prev = NULL; tmp != NULL; prev = tmp, tmp = tmp->next) {
        if (conf->group_id == tmp->conf.group_id) {
            old_conf = tmp->conf; // Copy configuration
            for (i = 0; i < VTSS_PORT_BF_SIZE; i++) {
                tmp->conf.ports[i] |= conf->ports[i];
            }
            new = tmp;
            if (vtss_vlan_trans_group_port_list_update(vtss_state, conf->group_id, old_conf.ports,
                                                       tmp->conf.ports, TRUE) != VTSS_RC_OK)
            {
                VTSS_D("VLAN Translation: vtss_vlan_trans_group_port_list_update failed");
            }
            break;
        }
        /* List needs to be sorted based on group_id */
        if (conf->group_id < tmp->conf.group_id) {
            break;
        }
    }
    if (new == NULL) {
        /* Get free node from free list */
        if ((new = list->free) == NULL) {  /* No free entry exists */
            return VTSS_RC_ERROR;
        }
        list->free = new->next;

        /* Copy the configuration */
        new->conf = *conf;

        // Insert entry in used list
        if (prev == NULL) {
            new->next = list->used;
            list->used = new;
        } else {
            new->next = prev->next;
            prev->next = new;
        }

        VTSS_MEMSET(&old_conf, 0, sizeof(old_conf));
        if (vtss_vlan_trans_group_port_list_update(vtss_state, conf->group_id, old_conf.ports,
                                                   conf->ports, FALSE) != VTSS_RC_OK)
        {
            VTSS_D("VLAN Translation: vtss_vlan_trans_group_port_list_update failed");
        }
    }
    return VTSS_RC_OK;
}

/* VLAN Translation function to fetch all ports for a group */
vtss_rc vtss_cmn_vlan_trans_port_conf_get(vtss_state_t *vtss_state,
                                          vtss_vlan_trans_port2grp_conf_t *conf, BOOL next)
{
    vtss_vlan_trans_port2grp_t       *list = &vtss_state->l2.vt_port_conf;
    vtss_vlan_trans_port2grp_entry_t *tmp;
    BOOL                             next_entry = FALSE;

    if (conf == NULL) {
        VTSS_E("VLAN Translation: NULL pointer");
        return VTSS_RC_ERROR;
    }

    if (list->used == NULL) {
        VTSS_D("Port list is empty");
        return VTSS_RC_ERROR;
    }

    /* If group_id is 0, return first entry */
    if (conf->group_id == VTSS_VLAN_TRANS_NULL_GROUP_ID) {
        *conf = list->used->conf;
        return VTSS_RC_OK;
    }

    for (tmp = list->used; tmp != NULL; tmp = tmp->next) {
        if (next_entry == TRUE) {
            *conf = tmp->conf;
            return VTSS_RC_OK;
        }

        if (conf->group_id == tmp->conf.group_id) {
            if (next == FALSE) {
                *conf = tmp->conf;
                return VTSS_RC_OK;
            }
            next_entry = TRUE;
        }
    }
    return VTSS_RC_ERROR;
}
#endif // VTSS_FEATURE_VCAP

/* - SDX, counters, policers --------------------------------------- */
#if defined(VTSS_SDX_CNT)

vtss_sdx_entry_t *vtss_cmn_sdx_alloc(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 id, BOOL isdx)
{
    vtss_sdx_entry_t *sdx;
    vtss_sdx_list_t  *list = (isdx ? &vtss_state->l2.sdx_info.isdx : &vtss_state->l2.sdx_info.esdx);

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    if (!vtss_state->init_conf.vlan_counters_disable) {
        VTSS_I("SDX allocation not possible, VLAN counters are used");
        return NULL;
    }
#endif

    if ((sdx = list->free) == NULL) {
        VTSS_I("%sSDX alloc failed, port_no: %u", isdx ? "I" : "E", port_no);
        return NULL;
    }

    /* Take out of free list */
    list->free = sdx->next;
    list->count++;
    sdx->port_no = port_no;
    sdx->id = id;
    sdx->next = NULL;

    return sdx;
}

void vtss_cmn_sdx_free(vtss_state_t *vtss_state, vtss_sdx_entry_t *sdx, BOOL isdx)
{
    vtss_sdx_list_t *list = (isdx ? &vtss_state->l2.sdx_info.isdx : &vtss_state->l2.sdx_info.esdx);

    sdx->port_no = VTSS_PORT_NO_NONE;
    sdx->id = 0;
    sdx->pol_idx = 0;
    sdx->pol_cnt = 0;
    sdx->stat_idx = 0;
    sdx->stat_cnt = 0;
    sdx->next = list->free;
    list->free = sdx;
    list->count--;
}

#endif /* VTSS_SDX_CNT */

#if defined(VTSS_FEATURE_RCL)
vtss_rc vtss_rcl_vid_lookup(vtss_state_t *vtss_state, vtss_vid_t vid, u8 *idx, BOOL lookup_free)
{
    u8                   i, j = VTSS_RCL_VID_CNT;
    vtss_rcl_vid_entry_t *entry;

    for (i = 0; i < VTSS_RCL_VID_CNT; i++) {
        entry = &vtss_state->l2.rcl_vid[i];
        if (entry->enable) {
            if (entry->vid == vid) {
                // Existing entry found
                j = i;
                break;
            }
        } else if (lookup_free && i < j) {
            j = i;
        }
    }
    if (j < VTSS_RCL_VID_CNT) {
        *idx = j;
        return VTSS_RC_OK;
    }
    return VTSS_RC_ERROR;
}

vtss_rc vtss_rcl_vid_add(const vtss_inst_t         inst,
                         const vtss_vid_t          vid,
                         const vtss_rcl_vid_conf_t *const conf)
{
    vtss_state_t         *vtss_state;
    vtss_rc              rc;
    u8                   idx;
    vtss_rcl_vid_entry_t *entry;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((rc = vtss_rcl_vid_lookup(vtss_state, vid, &idx, TRUE)) == VTSS_RC_OK) {
            entry = &vtss_state->l2.rcl_vid[idx];
            entry->enable = TRUE;
            entry->vid = vid;
            entry->conf = *conf;
            rc = VTSS_FUNC(l2.rcl_vid_conf_set, idx);
        } else {
            VTSS_I("RCL VID table full");
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_rcl_vid_del(const vtss_inst_t inst,
                         const vtss_vid_t  vid)
{
    vtss_state_t         *vtss_state;
    vtss_rc              rc;
    u8                   idx;
    vtss_rcl_vid_entry_t *entry;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if ((rc = vtss_rcl_vid_lookup(vtss_state, vid, &idx, FALSE)) == VTSS_RC_OK) {
            entry = &vtss_state->l2.rcl_vid[idx];
            VTSS_MEMSET(entry, 0, sizeof(*entry));
            rc = VTSS_FUNC(l2.rcl_vid_conf_set, idx);
        } else {
            VTSS_E("VID %u not found", vid);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_rce_init(const vtss_inst_t inst,
                      vtss_rce_t        *const rce)
{
    VTSS_MEMSET(rce, 0, sizeof(*rce));
    return VTSS_RC_OK;
}

static vtss_rc vtss_cmn_rce_add(vtss_state_t *vtss_state,
                                const vtss_rce_id_t rce_id,
                                const vtss_rce_t    *const rce)
{
    vtss_vcap_obj_t             *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_user_t            user = VTSS_IS1_USER_RCL;
    vtss_vcap_data_t            data;
    vtss_is1_entry_t            entry;
    vtss_is1_action_t           *action = &entry.action;
    vtss_is1_key_t              *key = &entry.key;
    vtss_res_chg_t              res;

    // Check RCE ID
    if (rce->id == VTSS_RCE_ID_LAST || rce->id == rce_id) {
        VTSS_E("illegal rce id: %u", rce->id);
        return VTSS_RC_ERROR;
    }

    // Check that entry can be added
    VTSS_MEMSET(&res, 0, sizeof(res));
    if (vtss_vcap_lookup(vtss_state, obj, user, rce->id, &data, NULL) == VTSS_RC_OK) {
        res.del_key[data.key_size] = 1;
    }
    vtss_vcap_is1_init(&data, &entry);
    data.key_size = VTSS_VCAP_KEY_SIZE_QUARTER;
    res.add_key[data.key_size] = 1;
    VTSS_RC(vtss_cmn_vcap_res_check(obj, &res));

    // Add entry
    key->key_type = VTSS_VCAP_KEY_TYPE_DOUBLE_TAG;
    key->type = VTSS_IS1_TYPE_RCE;
    key->frame.rce_key = rce->key;
    action->rce_action = rce->action;
    return vtss_vcap_add(vtss_state, obj, user, rce->id, rce_id, &data, 0);
}

vtss_rc vtss_rce_add(const vtss_inst_t   inst,
                     const vtss_rce_id_t rce_id,
                     const vtss_rce_t    *const rce)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = vtss_cmn_rce_add(vtss_state, rce_id, rce);
    }
    VTSS_EXIT();
    return rc;
}

static vtss_rc vtss_cmn_rce_del(vtss_state_t *vtss_state,
                                const vtss_rce_id_t rce_id)
{
    vtss_vcap_obj_t  *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_user_t user = VTSS_IS1_USER_RCL;
    vtss_vcap_data_t data;

    if (vtss_vcap_lookup(vtss_state, obj, user, rce_id, &data, NULL) != VTSS_RC_OK) {
        VTSS_E("rce_id: %u not found", rce_id);
        return VTSS_RC_ERROR;
    }
    return vtss_vcap_del(vtss_state, obj, user, rce_id);
}

vtss_rc vtss_rce_del(const vtss_inst_t   inst,
                     const vtss_rce_id_t rce_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = vtss_cmn_rce_del(vtss_state, rce_id);
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_RCL */

#if VTSS_OPT_DEBUG_PRINT

/* - Debug print --------------------------------------------------- */

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
/* Print counters in two columns */
static void vtss_debug_vlan_cnt(const vtss_debug_printf_t pr,
                                const char *name,
                                vtss_vlan_counter_types_t *cnt)
{
    char buf[80];

    VTSS_SPRINTF(buf, "%s Packets:", name);
    pr("%-19s%19" PRIu64 "   ", buf, cnt->frames);
    VTSS_SPRINTF(buf, "%s Octets:", name);
    pr("%-19s%19" PRIu64, buf, cnt->bytes);
    pr("\n");
}
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

static void vtss_debug_print_vlan(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455} */  // Due to the VTSS_EXIT_ENTER
    vtss_vid_t            vid;
    vtss_vlan_entry_t     *entry;
    BOOL                  header = 1;
    vtss_port_no_t        port_no;
    vtss_vlan_port_conf_t *conf;
#if defined(VTSS_FEATURE_L2_ERPS)
    u8                    erps_discard[VTSS_PORT_BF_SIZE];
#endif
    u32                   msti = 0;
    BOOL                  mgmt = 0;

    pr("S-tag Etype: 0x%04x\n\n", vtss_state->l2.vlan_conf.s_etype);

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no])
            continue;
        if (header) {
            header = 0;
            pr("Port  Type  ");
#if defined(VTSS_ARCH_OCELOT)
            pr("EType   ");
#endif /* VTSS_ARCH_OCELOT */
            pr("PVID  UVID  Frame  Filter\n");
        }
        conf = &vtss_state->l2.vlan_port_conf[port_no];
        pr("%-4u  %-4s  ",
           port_no,
           conf->port_type == VTSS_VLAN_PORT_TYPE_UNAWARE ? "U" :
           conf->port_type == VTSS_VLAN_PORT_TYPE_C ? "C" :
           conf->port_type == VTSS_VLAN_PORT_TYPE_S ? "S" :
           conf->port_type == VTSS_VLAN_PORT_TYPE_S_CUSTOM ? "S_CU" : "?");
#if defined(VTSS_ARCH_OCELOT)
        pr("0x%04x  ", conf->s_etype);
#endif /* VTSS_ARCH_OCELOT */
        pr("%-4u  %-4u  %-5s  %u\n",
           conf->pvid, conf->untagged_vid,
           conf->frame_type == VTSS_VLAN_FRAME_ALL ? "all" :
           conf->frame_type == VTSS_VLAN_FRAME_TAGGED ? "tag" : "untag",
           conf->ingress_filter);
    }
    if (!header)
        pr("\n");
    header = 1;

    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        entry = &vtss_state->l2.vlan_table[vid];
        if (!(entry->flags & VLAN_FLAGS_ENABLED) && !info->full)
            continue;
        if (header) {
            pr("VID   ");
#if defined(VTSS_FEATURE_VLAN_SVL)
            pr("FID   ");
#endif /* VTSS_FEATURE_VLAN_SVL */
            vtss_debug_print_port_header(vtss_state, pr, "VSI   Mgmt  MSTI  Lrn  Fld  Mir  Flt  Iso  ", 0, 1);
            header = 0;
        }
        pr("%-6u", vid);
#if defined(VTSS_FEATURE_VLAN_SVL)
        pr("%-6u", entry->fid);
#endif /* VTSS_FEATURE_VLAN_SVL */
#if defined(VTSS_ARCH_JAGUAR_2)
        mgmt = entry->mgmt;
        if ((entry->vsi_enable) && (entry->vsi != NULL)) {
            pr("%-6u", entry->vsi->vsi);
        } else
#endif
        {
            pr("%-6s", "-");
        }
#if defined(VTSS_FEATURE_L2_MSTP)
        msti = entry->msti;
#endif
        pr("%-6u%-6u%-5u%-5u%-5u%-5u%-5u",
           mgmt,
           msti,
           entry->flags & VLAN_FLAGS_LEARN ? 1 : 0,
           entry->flags & VLAN_FLAGS_FLOOD ? 1 : 0,
           entry->flags & VLAN_FLAGS_MIRROR ? 1 : 0,
           entry->flags & VLAN_FLAGS_FILTER ? 1 : 0,
           entry->flags & VLAN_FLAGS_ISOLATED ? 1 : 0);
        vtss_debug_print_ports(vtss_state, pr, entry->member, 0);
        pr(" <- VLAN Members\n");
#if defined(VTSS_FEATURE_L2_ERPS)
        pr("%-49s", "");
#if defined(VTSS_FEATURE_VLAN_SVL)
        pr("%-6s", "");
#endif /* VTSS_FEATURE_VLAN_SVL */
        VTSS_PORT_BF_CLR(erps_discard);
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            VTSS_PORT_BF_SET(erps_discard,
                             port_no,
                             entry->erps_discard_cnt[port_no] ? 1 : 0);
        }
        vtss_debug_print_ports(vtss_state, pr, erps_discard, 0);
        pr(" <- ERPS Discard\n");
#endif // VTSS_FEATURE_L2_ERPS

        /* Leave critical region briefly */
        VTSS_EXIT_ENTER();
    }
    if (!header)
        pr("\n");
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vtss_vlan_counters_t counters;

        entry = &vtss_state->l2.vlan_table[vid];
        if ((!(entry->flags & VLAN_FLAGS_ENABLED) && !info->full) || VTSS_FUNC(l2.vlan_counters_get, vid, &counters) != VTSS_RC_OK)
            continue;
        pr("VLAN ID %u Counters:\n\n", vid);
        vtss_debug_vlan_cnt(pr, "Unicast", &counters.rx_vlan_unicast);
        vtss_debug_vlan_cnt(pr, "Multicast", &counters.rx_vlan_multicast);
        vtss_debug_vlan_cnt(pr, "Broadcast", &counters.rx_vlan_broadcast);
        pr("\n");
    }
#endif /* VTSS_FEATURE_VLAN_COUNTERS */
}

static void vtss_debug_print_pvlan(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    BOOL            header = 1;
    vtss_port_no_t  port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no])
            continue;
        if (header) {
            header = 0;
            pr("Port  Isolation\n");
        }
        pr("%-6u%s\n", port_no, vtss_bool_txt(vtss_state->l2.isolated_port[port_no]));
    }
    if (!header)
        pr("\n");

    vtss_debug_print_port_header(vtss_state, pr, "PVLAN  ", 0, 1);
    {
        vtss_pvlan_no_t pvlan_no;

        for (pvlan_no = VTSS_PVLAN_NO_START; pvlan_no < VTSS_PVLAN_NO_END; pvlan_no++) {
            pr("%-7u", pvlan_no);
            vtss_debug_print_port_members(vtss_state, pr, vtss_state->l2.pvlan_table[pvlan_no].member, 1);
        }
    }
    pr("\n");

    header = 1;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no])
            continue;
        if (header) {
            header = 0;
            vtss_debug_print_port_header(vtss_state, pr, "APVLAN  ", 0, 1);
        }
        pr("%-6u  ", port_no);
        vtss_debug_print_port_members(vtss_state, pr, vtss_state->l2.apvlan_table[port_no], 1);
    }
    if (!header)
        pr("\n");
}

void vtss_debug_print_mac_entry(const vtss_debug_printf_t pr,
                                const char *name,
                                BOOL *header,
                                vtss_mac_table_entry_t *entry,
                                u32 pgid)
{
    u8 *p = &entry->vid_mac.mac.addr[0];

    if (*header) {
        *header = 0;
        vtss_debug_print_header(pr, name);
        pr("VID   MAC                PGID  CPU  Que  Locked  Age");
        pr("\n");
    }
    pr("%-4u  %02x-%02x-%02x-%02x-%02x-%02x  %-4u  %u/%u  %-3u  %-6u  %d\n",
       entry->vid_mac.vid, p[0], p[1], p[2], p[3], p[4], p[5],
       pgid, entry->copy_to_cpu, entry->copy_to_cpu_smac, entry->cpu_queue, entry->locked, entry->aged);
}

static void vtss_debug_print_mac_table(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455} */  // Due to the VTSS_EXIT_ENTER
    vtss_mac_entry_t       *entry;
    vtss_vid_mac_t         vid_mac;
    vtss_mac_table_entry_t mac_entry;
    u8                     *p = &vid_mac.mac.addr[0];
    BOOL                   header = 1;
    u32                    pgid;

    vtss_debug_print_value(pr, "Age time", vtss_state->l2.mac_age_time);
    vtss_debug_print_value(pr, "MAC table size", sizeof(vtss_mac_entry_t)*VTSS_MAC_ADDRS);
    vtss_debug_print_value(pr, "MAC table maximum", vtss_state->l2.mac_table_max);
    vtss_debug_print_value(pr, "MAC table count", vtss_state->l2.mac_table_count);
    pr("\n");

    vtss_debug_print_port_header(vtss_state, pr, "Flood Members  ", 0, 1);
    pr("Unicast        ");
    vtss_debug_print_port_members(vtss_state, pr, vtss_state->l2.uc_flood, 1);
    pr("Multicast      ");
    vtss_debug_print_port_members(vtss_state, pr, vtss_state->l2.mc_flood, 1);
    pr("IPv4 MC        ");
    vtss_debug_print_port_members(vtss_state, pr, vtss_state->l2.ipv4_mc_flood, 1);
    pr("IPv6 MC        ");
    vtss_debug_print_port_members(vtss_state, pr, vtss_state->l2.ipv6_mc_flood, 1);
    pr("\n");

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    {
        vtss_mac_index_table_t *t = &vtss_state->l2.mac_index_table;
        vtss_mac_vlan_entry_t  *e;
        u32                    i;

        pr("Index OUI   : 0x%06x\n", t->oui);
        pr("VID idx list: %s", t->cnt ? "" : "-");
        for (i = 0; i < t->cnt; i++) {
            pr("%s%u", i == 0 ? "" : "-", t->vidx[i]);
        }
        pr("\n\nIDX  VID   CNT\n");
        for (i = 0; i < VTSS_MAC_INDEX_VID_CNT; i++) {
            e = &t->e[i];
            pr("%-5u%-6u%u\n", i, e->vid, e->cnt);
        }
        pr("\n");

        VTSS_MEMSET(&mac_entry, 0, sizeof(mac_entry));
        while (vtss_mac_index_get(vtss_state, &mac_entry, &pgid, 1) == VTSS_RC_OK) {
            vtss_mac_pgid_get(vtss_state, &mac_entry, pgid);
            vtss_debug_print_mac_entry(pr, "Index Entries", &header, &mac_entry, pgid);
            VTSS_EXIT_ENTER();
        }
        if (!header) {
            header = 1;
            pr("\n");
        }
    }
#endif

    /* MAC address table in state */
    for (entry = vtss_state->l2.mac_list_used; entry != NULL; entry = entry->next) {
        if (header) {
            vtss_debug_print_header(pr, "API Entries");
            vtss_debug_print_port_header(vtss_state, pr, "User  VID   MAC                CPU  ", 0, 1);
            header = 0;
        }
        vtss_mach_macl_set(&vid_mac, entry->mach, entry->macl);
        pr("%-6s%-6u%02x-%02x-%02x-%02x-%02x-%02x  %u/%-3u",
           entry->user == VTSS_MAC_USER_NONE ? "None" :
           entry->user == VTSS_MAC_USER_SSM ? "SSM" :
           entry->user == VTSS_MAC_USER_ASM ? "ASM" : "?",
           vid_mac.vid, p[0], p[1], p[2], p[3], p[4], p[5], entry->cpu_copy, entry->cpu_copy_smac);
        vtss_debug_print_ports(vtss_state, pr, entry->member, 1);
        VTSS_EXIT_ENTER();
    }
    if (!header)
        pr("\n");

    /* MAC address table in chip */
    header = 1;
    VTSS_MEMSET(&mac_entry, 0, sizeof(mac_entry));
    while (vtss_state->l2.mac_table_get_next != NULL &&
           vtss_state->l2.mac_table_get_next(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK) {
        vtss_mac_pgid_get(vtss_state, &mac_entry, pgid);
        vtss_debug_print_mac_entry(pr, "Chip Entries", &header, &mac_entry, pgid);
        VTSS_EXIT_ENTER();
    }
    if (!header)
        pr("\n");
}

static void vtss_debug_print_aggr(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    vtss_port_no_t    port_no;
    u8                member[VTSS_PORT_BF_SIZE];
    vtss_aggr_mode_t  *mode;
    vtss_pgid_entry_t *pgid_entry;
    u32               pgid;
    BOOL              empty;
    vtss_aggr_no_t    aggr_no;

    VTSS_PORT_BF_CLR(member);
    vtss_debug_print_port_header(vtss_state, pr, "LLAG  ", 0, 1);
    for (aggr_no = VTSS_AGGR_NO_START; aggr_no < VTSS_AGGR_NO_END; aggr_no++) {
        pr("%-4u  ", aggr_no);
        VTSS_PORT_BF_CLR(member);
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            VTSS_PORT_BF_SET(member, port_no, vtss_state->l2.port_aggr_no[port_no] == aggr_no);
        vtss_debug_print_ports(vtss_state, pr, member, 1);
    }
    pr("\n");

    vtss_debug_print_header(pr, "Mode");
    mode = &vtss_state->l2.aggr_mode;
    vtss_debug_print_value(pr, "SMAC", mode->smac_enable);
    vtss_debug_print_value(pr, "DMAC", mode->dmac_enable);
    vtss_debug_print_value(pr, "SIP/DIP", mode->sip_dip_enable);
    vtss_debug_print_value(pr, "SPORT/DPORT", mode->sport_dport_enable);
    pr("\n");

    vtss_debug_print_port_header(vtss_state, pr, "PGID  Count  Resv  CPU  Queue  ", 0, 1);
    for (pgid = 0; pgid < vtss_state->l2.pgid_count; pgid++) {
        pgid_entry = &vtss_state->l2.pgid_table[pgid];
        empty = pgid_entry->cpu_copy ? 0 : 1;
        for (port_no = VTSS_PORT_NO_START; empty && port_no < vtss_state->port_count; port_no++) {
            if (pgid_entry->member[port_no]) {
                empty = 0;
            }
        }
        if ((pgid_entry->references == 0 && !info->full) || (pgid > 50 && empty && !info->full)) {
            continue;
        }
        pr("%-4u  %-5u  %-4u  %-3u  %-5u  ", pgid, pgid_entry->references, pgid_entry->resv, pgid_entry->cpu_copy, pgid_entry->cpu_queue);

        vtss_debug_print_port_members(vtss_state, pr, pgid_entry->member, 1);
    }
    pr("\n");
    vtss_debug_print_value(pr, "PGID count", vtss_state->l2.pgid_count);
    vtss_debug_print_value(pr, "PGID drop", vtss_state->l2.pgid_drop);
    vtss_debug_print_value(pr, "PGID flood", vtss_state->l2.pgid_flood);
    pr("\n");

    pr("Port  Destination Group\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        pr("%-6u%u\n", port_no, vtss_state->l2.dgroup_port_conf[port_no].dgroup_no);
    }
    pr("\n");
}

static void vtss_debug_print_stp_state(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr, vtss_stp_state_t *state)
{
    vtss_port_no_t   port_no;
    vtss_stp_state_t s;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        s = state[port_no];
        pr("%s%s",
           port_no == 0 || (port_no & 7) ? "" : ".",
           s == VTSS_STP_STATE_FORWARDING ? "F" : s == VTSS_STP_STATE_LEARNING ? "L" : "D");
    }
    pr("\n");

}

static void vtss_debug_print_stp(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    vtss_debug_print_port_header(vtss_state, pr, "STP   ", 0, 1);
    pr("      ");
    vtss_debug_print_stp_state(vtss_state, pr, vtss_state->l2.stp_state);
    pr("\n");

#if defined(VTSS_FEATURE_L2_MSTP)
    {
        vtss_msti_t msti;

        vtss_debug_print_port_header(vtss_state, pr, "MSTI  ", 0, 1);
        for (msti = VTSS_MSTI_START; msti < VTSS_MSTI_END; msti++) {
            pr("%-4u  ", msti);
            vtss_debug_print_stp_state(vtss_state, pr, vtss_state->l2.mstp_table[msti].state);
        }
        pr("\n");
    }
#endif
}

static void vtss_debug_print_port_none(const vtss_debug_printf_t pr,
                                       const char *name,
                                       vtss_port_no_t port_no)
{
    pr("%s: ", name);
    if (port_no == VTSS_PORT_NO_NONE)
        pr("None");
    else
        pr("%u", port_no);
    pr("\n");
}

static void vtss_debug_print_mirror(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    vtss_mirror_conf_t *conf = &vtss_state->l2.mirror_conf;

    vtss_debug_print_port_header(vtss_state, pr, "         ", 0, 0);
    pr(" CPU\n");

    pr("Ingress: ");
    vtss_debug_print_port_members(vtss_state, pr, vtss_state->l2.mirror_ingress, 0);
    pr(" %u\n", vtss_state->l2.mirror_cpu_ingress);

    pr("Egress : ");
    vtss_debug_print_port_members(vtss_state, pr, vtss_state->l2.mirror_egress, 0);
    pr(" %u\n\n", vtss_state->l2.mirror_cpu_egress);

    vtss_debug_print_port_none(pr, "Mirror Port      ", conf->port_no);
    pr("Mirror Forwarding: %s\n", vtss_bool_txt(conf->fwd_enable));
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    pr("Mirror Tag       : %s\n",
       conf->tag == VTSS_MIRROR_TAG_NONE ? "None" :
       conf->tag == VTSS_MIRROR_TAG_C ? "C-Tag" :
       conf->tag == VTSS_MIRROR_TAG_S ? "S-Tag" :
       conf->tag == VTSS_MIRROR_TAG_S_CUSTOM ? "S-Custom-Tag" : "?");
    pr("Mirror VID       : %u\n", conf->vid);
    pr("Mirror PCP       : %u\n", conf->pcp);
    pr("Mirror DEI       : %u\n", conf->dei);
#endif
    pr("\n");
}

#if defined(VTSS_FEATURE_L2_ERPS)
static void vtss_debug_print_erps(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    vtss_erpi_t       erpi;
    vtss_erps_entry_t *entry;
    int               i;
    vtss_vid_t        vid;

    vtss_debug_print_port_header(vtss_state, pr, "ERPI  ", 0, 0);
    pr("  VLANs\n");
    for (erpi = VTSS_ERPI_START; erpi < VTSS_ERPI_END; erpi++) {
        entry = &vtss_state->l2.erps_table[erpi];
        pr("%-4u  ", erpi);
        vtss_debug_print_ports(vtss_state, pr, entry->port_member, 0);
        pr("  ");
        for (vid = VTSS_VID_NULL, i = 0; vid < VTSS_VIDS; vid++) {
            if (VTSS_BF_GET(entry->vlan_member, vid)) {
                pr("%s%u", i ? "," : "", vid);
                i++;
            }
        }
        pr("%s\n", i ? "" : "-");
    }
    pr("\n");
}
#endif // VTSS_FEATURE_L2_ERPS

static void vtss_debug_print_eps(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    vtss_port_no_t  port_no;
    vtss_port_eps_t *eps;
    char            buf[16];
    BOOL            header = 1;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no])
            continue;
        if (header) {
            header = 0;
            pr("Port  Protection  Type  Selector\n");
        }
        eps = &vtss_state->l2.port_protect[port_no];
        if (eps->conf.port_no == VTSS_PORT_NO_NONE)
            VTSS_STRCPY(buf, "None");
        else
            VTSS_SPRINTF(buf, "%-4u", eps->conf.port_no);
        pr("%-4u  %-10s  %-4s  %s\n",
           port_no, buf, eps->conf.type == VTSS_EPS_PORT_1_PLUS_1 ? "1+1" : "1:1",
           eps->selector == VTSS_EPS_SELECTOR_WORKING ? "Working" : "Protection");
    }
    if (!header)
        pr("\n");
}

#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
static void vtss_debug_print_ipv6_addr(const vtss_debug_printf_t pr, vtss_ipv6_t *ipv6)
{
    int i;

    for (i = 0; i < 16; i++) {
        pr("%02x%s", ipv6->addr[i], (i & 1) && i != 15 ? ":" : "");
    }
}

static void vtss_debug_print_ipmc(vtss_state_t              *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    vtss_ipmc_info_t *ipmc = &vtss_state->l2.ipmc;
    vtss_ipmc_src_t  *src;
    vtss_ipmc_dst_t  *dst;
    char             buf[80];
    u32              ipv6, src_free_count = 0, dst_free_count = 0;
    BOOL             header;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_IPMC))
        return;

    for (src = ipmc->obj.src_free; src != NULL; src = src->next) {
        src_free_count++;
    }
    for (dst = ipmc->obj.dst_free; dst != NULL; dst = dst->next) {
        dst_free_count++;
    }

    vtss_debug_print_value(pr, "State size", sizeof(*ipmc));
    vtss_debug_print_value(pr, "Source count", ipmc->obj.src_count);
    vtss_debug_print_value(pr, "Source free", src_free_count);
    vtss_debug_print_value(pr, "Source maximum", ipmc->obj.src_max);
    vtss_debug_print_value(pr, "Destination count", ipmc->obj.dst_count);
    vtss_debug_print_value(pr, "Destination free", dst_free_count);
    vtss_debug_print_value(pr, "Destination maximum", ipmc->obj.dst_max);
    pr("\n");

    /* SIP Table */
    for (ipv6 = 0; ipv6 < 2; ipv6++) {
        VTSS_SPRINTF(buf, ipv6 ? "  %-40s" : "  %-11s", "DIP");
        for (src = ipmc->obj.src_used[ipv6]; src != NULL; src = src->next) {
            pr("%-6s%-6s%-6s%s\n", "Type", "VID", "FID", "SIP");
            pr("%-6s%-6u%-6u", src->data.ssm ? "SSM" : "ASM", src->data.vid, src->data.fid);
            if (ipv6)
                vtss_debug_print_ipv6_addr(pr, &src->data.sip.ipv6);
            else
                pr("0x%08x", src->data.sip.ipv4);
            pr("\n\n");
            header = 1;
            for (dst = src->dest; dst != NULL; dst = dst->next) {
                if (header) {
                    vtss_debug_print_port_header(vtss_state, pr, buf, 0, 1);
                    header = 0;
                }
                pr("  ");
                if (ipv6)
                    vtss_debug_print_ipv6_addr(pr, &dst->data.dip.ipv6);
                else
                    pr("0x%08x", dst->data.dip.ipv4);
                pr(" ");
                vtss_debug_print_ports(vtss_state, pr, dst->data.member, 1);
            }
            pr("\n");
        }
    }

#if defined(VTSS_FEATURE_IS1)
    if (vtss_state->arch == VTSS_ARCH_L26) {
        vtss_vcap_debug_print_is1(vtss_state, pr, info);
    }
#endif /* VTSS_FEATURE_IS1 */

#if defined(VTSS_FEATURE_IS2)
    if (vtss_state->arch == VTSS_ARCH_JR1) {
        vtss_vcap_debug_print_is2(vtss_state, pr, info);
    }
#endif /* VTSS_FEATURE_IS2 */

    vtss_debug_print_mac_table(vtss_state, pr, info);
}
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */

void vtss_l2_debug_print(vtss_state_t *vtss_state,
                         const vtss_debug_printf_t pr,
                         const vtss_debug_info_t   *const info)
{
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_VLAN))
        vtss_debug_print_vlan(vtss_state, pr, info);
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_PVLAN))
        vtss_debug_print_pvlan(vtss_state, pr, info);
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_MAC_TABLE))
        vtss_debug_print_mac_table(vtss_state, pr, info);
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_AGGR))
        vtss_debug_print_aggr(vtss_state, pr, info);
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_STP))
        vtss_debug_print_stp(vtss_state, pr, info);
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_MIRROR))
        vtss_debug_print_mirror(vtss_state, pr, info);
#if defined(VTSS_FEATURE_L2_ERPS)
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_ERPS))
        vtss_debug_print_erps(vtss_state, pr, info);
#endif
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_EPS))
        vtss_debug_print_eps(vtss_state, pr, info);
#if defined(VTSS_FEATURE_VCAP)
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_VXLAT))
        vtss_debug_print_vlan_trans(vtss_state, pr, info);
#endif
#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
    vtss_debug_print_ipmc(vtss_state, pr, info);
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */
}
#endif // VTSS_OPT_DEBUG_PRINT

#endif /* VTSS_FEATURE_LAYER2 */
