// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// Avoid "options.h not used in module vtss_l3.c"
/*lint --e{766} */
#include <vtss/api/options.h>
#if defined(VTSS_FEATURE_LAYER3)

#include <sys/time.h>
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_os.h"

// Allow to do bulk opertations for ~20ms
#define BULK_TIME_MAX 20

#define E(...) VTSS_EG(VTSS_TRACE_GROUP_L3, ##__VA_ARGS__)
#define I(...) VTSS_IG(VTSS_TRACE_GROUP_L3, ##__VA_ARGS__)
#define D(...) VTSS_DG(VTSS_TRACE_GROUP_L3, ##__VA_ARGS__)
#define N(...) VTSS_NG(VTSS_TRACE_GROUP_L3, ##__VA_ARGS__)

#define MAC_FORMAT "%02x-%02x-%02x-%02x-%02x-%02x"
#define MAC_ARGS(X) \
    X.addr[0], X.addr[1], X.addr[2], X.addr[3], X.addr[4], X.addr[5]

#define IPV4_FORMAT "%u.%u.%u.%u"
#define IPV4_ARGS(X) \
    (((X) >> 24) & 0xff), (((X) >> 16) & 0xff), \
    (((X) >> 8) & 0xff), ((X) & 0xff)

#define IPV6_FORMAT "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x"
#define IPV6_ARGS(X) \
    ((((u32)((X).addr[ 0])) << 8) | ((u32)(X).addr[ 1])), \
    ((((u32)((X).addr[ 2])) << 8) | ((u32)(X).addr[ 3])), \
    ((((u32)((X).addr[ 4])) << 8) | ((u32)(X).addr[ 5])), \
    ((((u32)((X).addr[ 6])) << 8) | ((u32)(X).addr[ 7])), \
    ((((u32)((X).addr[ 8])) << 8) | ((u32)(X).addr[ 9])), \
    ((((u32)((X).addr[10])) << 8) | ((u32)(X).addr[11])), \
    ((((u32)((X).addr[12])) << 8) | ((u32)(X).addr[13])), \
    ((((u32)((X).addr[14])) << 8) | ((u32)(X).addr[15]))

#define IPV6N_FORMAT IPV6_FORMAT "/%hhu"
#define IPV6N_ARG(X) IPV6_ARGS((X).address), (X).prefix_size

#define IPV6_UC_FORMAT \
    "net: "IPV6N_FORMAT", next-hop: "IPV6_FORMAT
#define IPV6_UC_ARGS(X) IPV6N_ARG((X).network), IPV6_ARGS((X).destination)

#define IPV4N_FORMAT IPV4_FORMAT "/%hhu"
#define IPV4N_ARG(X) IPV4_ARGS((X).address), (X).prefix_size

#define IPV4_UC_FORMAT \
    "net: "IPV4N_FORMAT", next-hop: "IPV4_FORMAT
#define IPV4_UC_ARGS(X) IPV4N_ARG((X).network), IPV4_ARGS((X).destination)

#define IPV4_MC_FORMAT \
    "group: "IPV4_FORMAT", sip: "IPV4_FORMAT
#define IPV4_MC_ARGS(X) IPV4_ARGS((X).group), IPV4_ARGS((X).source)

#define IPV6_MC_FORMAT \
    "group: "IPV6_FORMAT", sip: "IPV6_FORMAT
#define IPV6_MC_ARGS(X) IPV6_ARGS((X).group), IPV6_ARGS((X).source)


void vtss_l3_integrity_check(const vtss_state_t *vs, const char *file,
                             unsigned line)
{
    u32 i, sum = 0;
    const u32 *data = (const u32 *)(&vs->l3);
    for (i = 0; i < sizeof(vtss_l3_state_t)/4; ++i, ++data) {
        sum ^= *data;
    }

    if (sum != 0) {
        if (file) {
            E("%s:%u CHECKSUM ERROR %x != %x", file, line, sum,
              vs->l3.checksum);
        } else {
            E("CHECKSUM ERROR %x != %x", sum, vs->l3.checksum);
        }
    }
}

void vtss_l3_integrity_update(vtss_state_t *vs)
{
    u32 i, sum = 0;

    vs->l3.checksum = 0;
    const u32 *data = (const u32 *)(&vs->l3);
    for (i = 0; i < sizeof(vtss_l3_state_t)/4; ++i, ++data) {
        sum ^= *data;
    }

    vs->l3.checksum = sum;
}

void vtss_api_l3_integrity_check(const char *file, unsigned line)
{
    vtss_state_t *vs;
    if (vtss_inst_check(0, &vs) == VTSS_RC_OK) {
        vtss_l3_integrity_check(vs, file, line);
    } else {
        E("INSTANCE ERROR");
    }
}

static void integrity_check(const vtss_inst_t inst)
{
    vtss_state_t *vs;
    if (vtss_inst_check(inst, &vs) == VTSS_RC_OK) {
        vtss_l3_integrity_check(vs, 0, 0);
    } else {
        E("INSTANCE ERROR");
    }
}

static void integrity_update(vtss_inst_t inst)
{
    vtss_state_t *vs;
    if (vtss_inst_check(inst, &vs) == VTSS_RC_OK) {
        vtss_l3_integrity_update(vs);
    } else {
        E("INSTANCE ERROR");
    }
}

#define VTSS_L3_ENTER() VTSS_ENTER(); integrity_check(inst);
#define VTSS_L3_EXIT()  integrity_update(inst); VTSS_EXIT();

/* finds and returns an unused rleg id for the provided vlan. Will fail if the
 * given vlan is allready configured, or if no more rlegs are aviable. */
static inline
vtss_rc rleg_id_get_new(vtss_l3_rleg_conf_t       *rleg_conf,
                        const vtss_l3_rleg_conf_t *const new_rleg,
                        vtss_l3_rleg_id_t         *rleg_id)
{
    u32 i;
    u32 free_id = 0xffffffff; // just to make lint happy
    BOOL found_free = FALSE;

    for (i = 0; i < VTSS_RLEG_CNT; ++i) {
        if (rleg_conf[i].vlan == new_rleg->vlan) {
            E("rleg_id_get_new failed, as vlan %d is allready used by rleg %d",
              rleg_conf[i].vlan, i);

            return VTSS_RC_ERROR;
        }

        if (rleg_conf[i].vlan == 0 && found_free == FALSE && (new_rleg->rleg_enable == 0 || new_rleg->rleg_id == i)) {
            found_free = TRUE;
            free_id = i;
        }
    }

    if (found_free) {
        D("%s:%d vlan: %u, rleg_id: %u",
          __FUNCTION__, __LINE__, new_rleg->vlan, free_id);
        rleg_conf[free_id] = *new_rleg;
        if (rleg_id) {
            *rleg_id = free_id;
        }
        return VTSS_RC_OK;
    }

    I("New rleg requested, but we are out of resources");
    return VTSS_RC_ERROR;
}

/* finds and returns an existing rleg id for the provided vlan. Will fail if the
 * given vlan does not allready exitst. */
static inline
vtss_rc rleg_id_get(vtss_l3_rleg_conf_t *rleg_conf,
                    const vtss_vid_t     vlan,
                    vtss_l3_rleg_id_t   *rleg_id,
                    vtss_l3_rleg_conf_t *rleg)
{
    u32 i;

    if (vlan == 0)
        return VTSS_RC_ERROR;

    for (i = 0; i < VTSS_RLEG_CNT; ++i) {
        if (rleg_conf[i].vlan == vlan) {
            if (rleg_id)
                *rleg_id = i;

            if (rleg)
                *rleg = rleg_conf[i];

            return VTSS_RC_OK;
        }
    }

    return VTSS_RC_ERROR;
}

/* finds delete and returns an existing rleg id for the provided vlan. Will fail
 * if the given vlan does not allready exitst. */
static inline
vtss_rc rleg_id_del(vtss_l3_rleg_conf_t *rleg_conf,
                    const vtss_vid_t     vlan,
                    vtss_l3_rleg_id_t   *rleg_id)
{
    vtss_l3_rleg_id_t id;
    VTSS_RC(rleg_id_get(rleg_conf, vlan, &id, 0));

    *rleg_id = id;
    rleg_conf[id].ipv4_unicast_enable = FALSE;
    rleg_conf[id].ipv6_unicast_enable = FALSE;
    rleg_conf[id].ipv4_multicast_enable = FALSE;
    rleg_conf[id].ipv6_multicast_enable = FALSE;
    rleg_conf[id].ipv4_icmp_redirect_enable = FALSE;
    rleg_conf[id].ipv6_icmp_redirect_enable = FALSE;
    rleg_conf[id].vlan = 0;

    I("rleg_id = %d, vlan = %d", id, vlan);

    return VTSS_RC_OK;
}

static vtss_rc rleg_del(vtss_state_t *vtss_state,
                        vtss_l3_rleg_conf_t *rleg_conf,
                        const vtss_vid_t     vlan)
{
    vtss_rc rc;
    vtss_l3_rleg_id_t rleg_id = 0xffffffff; // Just to make lint happy
    vtss_l3_rleg_conf_t conf = {
        .ipv4_unicast_enable = FALSE,
        .ipv6_unicast_enable = FALSE,
        .ipv4_multicast_enable = FALSE,
        .ipv6_multicast_enable = FALSE,
        .ipv4_icmp_redirect_enable = FALSE,
        .ipv6_icmp_redirect_enable = FALSE,
        .vlan = vlan
    };

#define DO(X)                                          \
    if (rc == VTSS_RC_OK) {                            \
        rc = (X);                                      \
        if (rc != VTSS_RC_OK) {                        \
            E("Failed: " #X "rleg_id = %d, vlan = %d", \
              rleg_id, vlan);                          \
        }                                              \
    }
    rc = rleg_id_del(rleg_conf, vlan, &rleg_id);
    I("Deleting rleg_id = %d, vlan = %d", rleg_id, vlan);
    DO(VTSS_FUNC(l3.vlan_set, rleg_id, vlan, FALSE));
    DO(VTSS_FUNC(l3.rleg_set, rleg_id, &conf));
#undef DO

    return rc;
}

static vtss_rc rleg_add(vtss_state_t *vtss_state,
                        vtss_l3_rleg_conf_t       *rleg_conf,
                        const vtss_l3_rleg_conf_t *const conf)
{
    vtss_rc rc;
    vtss_l3_rleg_id_t rleg_id = 0xffffffff; // Just to make lint happy

#define DO(X)                                                             \
    if (rc == VTSS_RC_OK) {                                               \
        rc = (X);                                                         \
        if (rc != VTSS_RC_OK) {                                           \
            E("Failed: " #X "rleg_id = %d, vlan = %d",                    \
              rleg_id, conf->vlan);                                       \
        }                                                                 \
    } else {                                                              \
        I("Skipping: " #X "rleg_id = %d, vlan = %d due to earlier error", \
          rleg_id, conf->vlan);                                           \
    }
    rc = rleg_id_get_new(vtss_state->l3.rleg_conf, conf, &rleg_id);
    D("Adding rleg: rleg_id = %d, vlan = %d", rleg_id, conf->vlan);
    DO(VTSS_FUNC(l3.rleg_set, rleg_id, conf));
    DO(VTSS_FUNC(l3.vlan_set, rleg_id, conf->vlan, TRUE));
#undef DO

    return rc;
}

static vtss_rc rleg_update(vtss_state_t              *vtss_state,
                           vtss_l3_rleg_conf_t       *rleg_conf,
                           const vtss_l3_rleg_conf_t *const conf)
{
    u32 i;
    vtss_rc rc = VTSS_RC_ERROR;

    for (i = 0; i < VTSS_RLEG_CNT; ++i) {
        if (rleg_conf[i].vlan == conf->vlan) {
            rleg_conf[i] = *conf;
            D("Updating rleg: rleg_id = %d, vlan = %d", i, conf->vlan);
            rc = VTSS_FUNC(l3.rleg_set, i, conf);
            break;
        }
    }

    return rc;
}

#if VTSS_OPT_TRACE
static
char * vtss_routing_entry_to_string(const vtss_routing_entry_t *const entry,
                                    char * buf,
                                    unsigned size)
{
    switch( entry->type ) {
    case VTSS_ROUTING_ENTRY_TYPE_INVALID:
        VTSS_SNPRINTF(buf, size, "INVALID");
        break;

    case VTSS_ROUTING_ENTRY_TYPE_IPV6_UC:
        VTSS_SNPRINTF(buf, size, IPV6_UC_FORMAT,
                 IPV6_UC_ARGS(entry->route.ipv6_uc));
        break;

    case VTSS_ROUTING_ENTRY_TYPE_IPV4_UC:
        VTSS_SNPRINTF(buf, size, IPV4_UC_FORMAT,
                 IPV4_UC_ARGS(entry->route.ipv4_uc));
        break;
    default:
        VTSS_SNPRINTF(buf, size, "UNKNOWN");
        break;
    }

    return buf;
}

static
char * vtss_routing_mc_entry_to_string(const vtss_routing_mc_entry_t *const entry,
                                       char * buf,
                                       unsigned size)
{
    if ( entry->type == VTSS_RT_TYPE_IPV4_MC) {
        VTSS_SNPRINTF(buf, size, IPV4_MC_FORMAT,
                 IPV4_MC_ARGS(entry->route.ipv4_mc));
    } else {
        VTSS_SNPRINTF(buf, size, IPV6_MC_FORMAT,
                 IPV6_MC_ARGS(entry->route.ipv6_mc));
    }

    return buf;
}

static
char * vtss_neighbour_to_string(const vtss_l3_neighbour_t* const entry,
                                char * buf,
                                unsigned size)
{
    unsigned c;

    c = VTSS_SNPRINTF(buf, size, "dmac: " MAC_FORMAT ", vid: %u, ip: ",
                 MAC_ARGS(entry->dmac), entry->vlan);

    if (c + 1 >= size)
        goto END;
    else
        size -= c;

    switch (entry->dip.type) {
    case VTSS_IP_TYPE_NONE:
        VTSS_SNPRINTF(buf + c, size, "INVALID");
        break;

    case VTSS_IP_TYPE_IPV4:
        VTSS_SNPRINTF(buf + c, size, IPV4_FORMAT, IPV4_ARGS(entry->dip.addr.ipv4));
        break;

    case VTSS_IP_TYPE_IPV6:
        VTSS_SNPRINTF(buf + c, size, IPV6_FORMAT, IPV6_ARGS(entry->dip.addr.ipv6));
        break;

    default:
        VTSS_SNPRINTF(buf + c, size, "UNKNOWN");
        break;
    }

END:
    return buf;
}
#endif

static inline int ipv4_cmp(const vtss_ipv4_t a, const vtss_ipv4_t b)
{
    return (a > b ? 1 : (a < b ? -1 : 0));
}

static inline int ipv6_cmp(const vtss_ipv6_t *a, const vtss_ipv6_t *b)
{
    u8 i, a_addr, b_addr;

    for (i = 0; i < 16; i++) {
        a_addr = a->addr[i];
        b_addr = b->addr[i];
        if (a_addr != b_addr) {
            return (a_addr > b_addr ? 1 : -1);
        }
    }
    return 0;
}

static inline int ip_addr_cmp(const vtss_ip_addr_t *a, const vtss_ip_addr_t *b)
{
    BOOL ipv4 = (a->type == VTSS_IP_TYPE_IPV4);

    /* IPv4 considered greater than IPv6 */
    if (a->type != b->type) {
        return (ipv4 ? 1 : -1);
    }

    if (ipv4) {
        return ipv4_cmp(a->addr.ipv4, b->addr.ipv4);
    } else {
        return ipv6_cmp(&a->addr.ipv6, &b->addr.ipv6);
    }
}

/* - ARP ----------------------------------------------------------- */

static inline vtss_rc rt_grp_move(vtss_state_t *vtss_state, u16 idx_old, u16 idx_new);

static inline vtss_rc arp_alloc(vtss_state_t *vtss_state, u8 cnt, u16 *idx)
{
    vtss_l3_arp_info_t *arp = &vtss_state->l3.arp;
    vtss_l3_arp_row_t  *row, *row_free;
    u8                 size, done;
    u16                i, j, k, i_free = VTSS_L3_ARP_ROW_CNT, j_free = 0, old, new;
    struct {
        u16 free_cnt; /* Number of free entries */
        u16 row_idx;  /* Index of row with smallest number of used entries */
        u16 col_idx;  /* Index of column of next used entry */
        u16 row_cnt;  /* Smallest number of used entries */
    } info[VTSS_L3_ARP_COL_CNT + 1], *pi; /* Info per size (2/3/4/6/12) */

    if (cnt < 2 || cnt > VTSS_L3_ARP_COL_CNT) {
        E("illegal size: %u", cnt);
        return VTSS_RC_ERROR;
    } else if (cnt > (VTSS_L3_ARP_COL_CNT / 2)) {
        cnt = VTSS_L3_ARP_COL_CNT;
    } else if (cnt == 5) {
        cnt = (VTSS_L3_ARP_COL_CNT / 2);
    }

    VTSS_MEMSET(info, 0, sizeof(info));
    done = 0;
    for (i = 0; i < VTSS_L3_ARP_ROW_CNT && !done; i++) {
        row = &arp->row[i];
        if ((size = row->size) != 0) {
            pi = &info[size];
            if (pi->row_cnt == 0 || row->cnt < pi->row_cnt) {
                /* Row with fewer used entries found */
                pi->row_cnt = row->cnt;
                pi->row_idx = i;
            }
            for (j = 0; j < VTSS_L3_ARP_COL_CNT; j += size) {
                if (row->used[j]) {
                    /* Skip used column */
                } else if (size == cnt) {
                    /* Free entry with correct size found */
                    i_free = i;
                    j_free = j;
                    done = 1;
                    break;
                } else {
                    pi->free_cnt += size;
                }
            }
        } else if (i_free == VTSS_L3_ARP_ROW_CNT) {
            /* First free row found */
            i_free = i;
        }
    }

    pi = NULL;
    if (i_free == VTSS_L3_ARP_ROW_CNT) {
        /* No free row or column found, check if we can free a new row */
        for (size = (VTSS_L3_ARP_COL_CNT / 2); size > 1; size--) {
            if (info[size].free_cnt >= VTSS_L3_ARP_COL_CNT) {
                pi = &info[size];
                break;
            }
        }

        if (pi == NULL) {
            I("no free ARP entries");
            return VTSS_RC_ERROR;
        }
    }

    if (pi != NULL) {
        /* Free row to make room for new entry */
        I("freeing row %u, size: %u", pi->row_idx, size);
        row_free = &arp->row[pi->row_idx];
        pi->col_idx = VTSS_L3_ARP_COL_CNT;
        for (j = 0; j < VTSS_L3_ARP_COL_CNT; j += size) {
            if (row_free->used[j]) {
                /* Found first used column to be moved */
                I("free first col: %u", j);
                pi->col_idx = j;
                break;
            }
        }
        done = 0;
        for (i = 0; i < VTSS_L3_ARP_ROW_CNT && !done; i++) {
            row = &arp->row[i];
            if (row->size != size || row == row_free) {
                continue;
            }
            for (j = 0; j < VTSS_L3_ARP_COL_CNT && !done; j += size) {
                if (row->used[j]) {
                    continue;
                }
                old = (pi->row_idx * VTSS_L3_ARP_COL_CNT + pi->col_idx);
                new = (i * VTSS_L3_ARP_COL_CNT + j);
                VTSS_RC(rt_grp_move(vtss_state, old, new));
                for (k = 0; k < size; k++) {
                    row->used[j + k] = 1;
                    row_free->used[pi->col_idx + k] = 0;
                }
                row->cnt += size;
                done = 1;
                for (k = (pi->col_idx + size); k < VTSS_L3_ARP_COL_CNT; k += size) {
                    if (row_free->used[k]) {
                        I("free next col: %u", k);
                        pi->col_idx = k;
                        done = 0;
                        break;
                    }
                }
            }
        }

        row_free->cnt = 0;
        i_free = pi->row_idx;
        j_free = 0;
    }

    /* Allocate block */
    row = &arp->row[i_free];
    row->size = cnt;
    row->cnt += cnt;
    for (j = 0; j < cnt; j++) {
        row->used[j + j_free] = 1;
    }
    *idx = (i_free * VTSS_L3_ARP_COL_CNT + j_free);
    I("allocate %u", *idx);

    return VTSS_RC_OK;
}

static inline vtss_rc arp_free(vtss_state_t *vtss_state, u16 idx)
{
    vtss_l3_arp_row_t *row;
    u8                size;
    u16               i = (idx / VTSS_L3_ARP_COL_CNT);
    u16               j = (idx % VTSS_L3_ARP_COL_CNT);

    if (i >= VTSS_L3_ARP_ROW_CNT) {
        E("illegal idx: %u", idx);
        return VTSS_RC_ERROR;
    }

    row = &vtss_state->l3.arp.row[i];
    if ((size = row->size) == 0 || row->used[j] == 0) {
        E("already free idx: %u", idx);
        return VTSS_RC_ERROR;
    }

    I("free idx: %u", idx);
    for (i = 0; i < size; i++) {
        row->used[j + i] = 0;
    }
    row->cnt -= size;
    if (row->cnt == 0) {
        row->size = 0;
    }
    return VTSS_RC_OK;
}

/* - Next-hops ----------------------------------------------------- */

/* Compare next-hop keys and return (a > b ? 1 : (a < b ? -1) : 0) */
static inline int nh_cmp(const vtss_l3_nh_key_t *a, const vtss_l3_nh_key_t *b)
{
    int cmp;

    if ((cmp = ip_addr_cmp(&a->dip, &b->dip)) != 0) {
        return cmp;
    }
    if (a->dip.type == VTSS_IP_TYPE_IPV6 && a->vid != b->vid) {
        return (a->vid > b->vid ? 1 : -1);
    }
    return 0;
}

static inline vtss_l3_nh_t *nh_alloc(vtss_state_t *vtss_state,
                                     vtss_l3_nh_t **list,
                                     vtss_l3_nh_t *prev,
                                     vtss_l3_nh_t *new)
{
    vtss_l3_nh_info_t *info = &vtss_state->l3.nh;
    vtss_l3_nh_t      *nh;

    if ((nh = info->free) == NULL) {
        /* We should run out of ARP entries before next-hop entries */
        E("no more next-hop entries");
    } else {
        info->free = nh->next;
        info->free_cnt--;
        *nh = *new;
        if (prev == NULL) {
            nh->next = *list;
            *list = nh;
        } else {
            nh->next = prev->next;
            prev->next = nh;
        }
    }
    return nh;
}

static inline void nh_free(vtss_state_t *vtss_state,
                           vtss_l3_nh_t *list)
{
    vtss_l3_nh_info_t *info = &vtss_state->l3.nh;
    vtss_l3_nh_t      *nh, *next;

    for (nh = list; nh != NULL; ) {
        next = nh->next;
        nh->next = info->free;
        info->free = nh;
        info->free_cnt++;
        nh = next;
    }
}

static inline vtss_rc nh_update(vtss_state_t *vtss_state,
                                u32          idx,
                                vtss_l3_nb_t *nb)
{
    BOOL enable = vtss_state->l3.common.routing_enable;

    I("idx: %u, dmac: " MAC_FORMAT ", vid: %u", idx, MAC_ARGS(nb->dmac), nb->nh.vid);
    return (enable ? VTSS_FUNC(l3.arp_set, idx, nb) : VTSS_RC_OK);
}

/* Look for a next-hop in a list */
static inline vtss_l3_nh_t *nh_lookup(vtss_state_t *vtss_state,
                                      vtss_l3_nh_t *list,
                                      vtss_l3_nh_t *nh)
{
    vtss_l3_nh_t *cur;

    for (cur = list; cur != NULL; cur = cur->next) {
        if (nh_cmp(&cur->nh, &nh->nh) == 0) {
            break;
        }
    }
    return cur;
}

/* - Next-hop groups ----------------------------------------------- */

static inline vtss_l3_nh_grp_t *nh_grp_alloc(vtss_state_t *vtss_state, u8 cnt)
{
    vtss_l3_nh_grp_info_t *info = &vtss_state->l3.nh_grp;
    vtss_l3_nh_grp_t      *grp = NULL;
    u16                   idx;

    if (cnt > VTSS_L3_NH_MAX) {
        E("maximum %u next-hops are supported", VTSS_L3_NH_MAX);
    } else if (arp_alloc(vtss_state, cnt, &idx) != VTSS_RC_OK) {
        /* We should run out of ARP entries before next-hop groups */
    } else if (vtss_state->l3.nh.free_cnt < cnt) {
        E("no more next-hop entries");
    } else if ((grp = info->free) == NULL) {
        E("no more next-hop groups");
    } else {
        info->free = grp->next;
        info->free_cnt--;
        grp->next = info->list;
        info->list = grp;
        grp->idx = idx;
    }
    return grp;
}

static inline void nh_grp_free(vtss_state_t *vtss_state, vtss_l3_nh_grp_t *grp)
{
    vtss_l3_nh_grp_info_t *info = &vtss_state->l3.nh_grp;
    vtss_l3_nh_grp_t      *cur, *prev = NULL;

    if (grp->count == 0) {
        E("group already free");
    } else {
        grp->count--;
        if (grp->count == 0) {
            /* Free next-hop list and move group to free list */
            nh_free(vtss_state, grp->list);
            (void)arp_free(vtss_state, grp->idx);
            for (cur = info->list; cur != NULL; prev = cur, cur = cur->next) {
                if (cur == grp) {
                    break;
                }
            }
            if (cur == NULL) {
                E("group not found");
            } else {
                if (prev == NULL) {
                    info->list = cur->next;
                } else {
                    prev->next = cur->next;
                }
                cur->next = info->free;
                info->free = grp;
                info->free_cnt++;
            }
        }
    }
}

static inline vtss_rc nh_grp_update(vtss_state_t     *vtss_state,
                                    vtss_l3_nh_grp_t *grp)
{
    vtss_l3_nh_t *nh;
    vtss_l3_nb_t *nb, nb_zero, *nb_up;
    u32          idx = grp->idx;
    int          cmp;

    VTSS_MEMSET(&nb_zero, 0, sizeof(nb_zero));
    for (nh = grp->list, nb = vtss_state->l3.nb.list; nh != NULL; ) {
        cmp = (nb == NULL ? -1 : nh_cmp(&nh->nh, &nb->nh));
        if (cmp > 0) {
            /* Next-hop is bigger, take next neighbour */
            nb = nb->next;
        } else {
            if (cmp == 0) {
                /* Next-hop is equal, update and take next neighbour*/
                nb_up = nb;
                nb = nb->next;
            } else {
                /* Next-hop is smaller, update with zero DMAC */
                nb_up = &nb_zero;
            }
            VTSS_RC(nh_update(vtss_state, idx, nb_up));
            idx++;
            nh = nh->next;
        }
    }
    return VTSS_RC_OK;
}

/* Look for a next-hop group matching a list */
static inline vtss_l3_nh_grp_t *nh_grp_lookup(vtss_state_t *vtss_state,
                                              vtss_l3_nh_t *list)
{
    vtss_l3_nh_grp_t *grp;
    vtss_l3_nh_t     *a, *b;
    int              cmp;

    for (grp = vtss_state->l3.nh_grp.list; grp != NULL; grp = grp->next) {
        if (grp->list == list) {
            continue;
        }
        cmp = 1;
        for (a = grp->list, b = list; a != NULL && b != NULL; a = a->next, b = b->next) {
            if ((cmp = nh_cmp(&a->nh, &b->nh)) != 0) {
                break;
            }
        }
        if (cmp == 0 && a == NULL && b == NULL) {
            break;
        }
    }
    return grp;
}

/* - Networks/routes ----------------------------------------------- */

/* Compare network and return (a > b ? 1 : (a < b ? -1) : 0) */
static inline int net_cmp(const vtss_l3_net_t *a, const vtss_l3_net_t *b)
{
    /* IPv4 considered greater than IPv6 */
    if (a->network.type != b->network.type) {
        return (a->network.type == VTSS_IP_TYPE_IPV4 ? 1 : -1);
    }

    if (a->prefix_size != b->prefix_size) {
        return (a->prefix_size > b->prefix_size ? 1 : -1);
    }

    return ip_addr_cmp(&a->network, &b->network);
}

/* Compare network and return (a > b ? 1 : (a < b ? -1) : 0) */
static inline int mc_rt_cmp(const vtss_l3_mc_rt_t *a, const vtss_l3_mc_rt_t *b)
{
    int cmp1, cmp2;
    /* IPv4 considered greater than IPv6 */
    if (a->network.type != b->network.type) {
        return (a->network.type == VTSS_IP_TYPE_IPV4 ? 1 : -1);
    }

    if ((cmp1 = ip_addr_cmp(&a->sip, &b->sip)) == 0) {
        return ip_addr_cmp(&a->network, &b->network);
    }

    if ((cmp2 = ip_addr_cmp(&a->network, &b->network)) == 0) {
        return cmp1;
    }
    return cmp2;
}

static inline int mc_mask_cmp(const u32 *a, const u32 *b)
{
    for (u16 i = 0; i < 4; i++) {
        if (a[i] != b[i]) {
            return 1;
        }
    }
    return 0;
}

static inline vtss_rc rt_update(vtss_state_t  *vtss_state,
                                vtss_l3_net_t *net,
                                vtss_l3_nb_t  *nb,
                                u32 cnt)
{
    BOOL         enable = vtss_state->l3.common.routing_enable;
    BOOL         discard = 1;
    int          i;
    vtss_l3_nb_t nb_zero = {0};

    if (net->network.type == VTSS_IP_TYPE_IPV4) {
        I("net: " IPV4N_FORMAT,
          IPV4_ARGS(net->network.addr.ipv4), net->prefix_size);
    } else {
        I("net: " IPV6N_FORMAT,
          IPV6_ARGS(net->network.addr.ipv6), net->prefix_size);
    }
    if (cnt > VTSS_L3_NH_MAX) {
        I("delete net");
        return (enable ? VTSS_FUNC(l3.rt_del, net) : VTSS_RC_OK);
    }
    if (net->grp == NULL) {
        /* Single next-hop */
        if (nb == NULL) {
            nb = &nb_zero;
            if (net->network.type == VTSS_IP_TYPE_IPV4) {
                discard = (net->nh.dip.addr.ipv4 == 0xffffffff);
            } else {
                for (i = 0; i < 16; i++) {
                    if (net->nh.dip.addr.ipv6.addr[i] != 0xff) {
                        discard = 0;
                    }
                }
            }
            if (discard) {
                // Discard route, ensure non-zero DMAC and use reserved router leg
                nb->dmac.addr[5] = 0xff;
                nb->rleg = VTSS_RLEG_DISCARD;
            }
        }
        I("dmac: " MAC_FORMAT ", vid: %u", MAC_ARGS(nb->dmac), nb->nh.vid);
    } else {
        I("cnt: %u, idx: %u", cnt, net->grp->idx);
    }
    return (enable ? VTSS_FUNC(l3.rt_add, net, nb, cnt) : VTSS_RC_OK);
}

static inline vtss_rc mc_rt_update(vtss_state_t  *vtss_state,
                                   vtss_l3_mc_rt_t *net, BOOL add)
{
    BOOL         enable = vtss_state->l3.common.mc_routing_enable;

    if (net->network.type == VTSS_IP_TYPE_IPV4) {
        I("group: " IPV4N_FORMAT, IPV4_ARGS(net->network.addr.ipv4), 32);
    } else {
        I("group: " IPV6N_FORMAT, IPV6_ARGS(net->network.addr.ipv6), 128);
    }
    if (add) {
        return (enable ? VTSS_FUNC(l3.mc_rt_add, net) : VTSS_RC_OK);
    } else {
        return (enable ? VTSS_FUNC(l3.mc_rt_del, net) : VTSS_RC_OK);
    }
}


static inline vtss_rc rt_grp_move(vtss_state_t *vtss_state, u16 idx_old, u16 idx_new)
{
    vtss_l3_nh_grp_t *grp;
    vtss_l3_net_t    *net;
    vtss_l3_nh_t     *nh;
    u32              cnt = 0;

    I("old: %u, new: %u", idx_old, idx_new);
    for (grp = vtss_state->l3.nh_grp.list; grp != NULL; grp = grp->next) {
        if (grp->idx == idx_old) {
            grp->idx = idx_new;
            VTSS_RC(nh_grp_update(vtss_state, grp));
            for (nh = grp->list; nh != NULL; nh = nh->next) {
                cnt++;
            }
            break;
        }
    }

    for (net = vtss_state->l3.net.list; net != NULL; net = net->next) {
        if (net->grp == grp) {
            VTSS_RC(rt_update(vtss_state, net, NULL, cnt));
        }
    }

    return VTSS_RC_OK;
}

static inline vtss_l3_nb_t *nb_lookup(vtss_state_t     *vtss_state,
                                      vtss_l3_nh_key_t *nh)
{
    vtss_l3_nb_t *cur;

    for (cur = vtss_state->l3.nb.list; cur != NULL; cur = cur->next) {
        if (nh_cmp(&cur->nh, nh) == 0) {
            break;
        }
    }
    return cur;
}

static inline void route2net(const vtss_routing_entry_t *route,
                             vtss_l3_net_t *net)
{
    VTSS_MEMSET(net, 0, sizeof(*net));
    if (route->type == VTSS_ROUTING_ENTRY_TYPE_IPV4_UC) {
        const vtss_ipv4_uc_t *ipv4 = &route->route.ipv4_uc;

        net->network.type = VTSS_IP_TYPE_IPV4;
        net->network.addr.ipv4 = ipv4->network.address;
        net->prefix_size = ipv4->network.prefix_size;
        net->nh.dip.addr.ipv4 = ipv4->destination;
    } else {
        const vtss_ipv6_uc_t *ipv6 = &route->route.ipv6_uc;

        net->network.type = VTSS_IP_TYPE_IPV6;
        net->network.addr.ipv6 = ipv6->network.address;
        net->prefix_size = ipv6->network.prefix_size;
        net->nh.dip.addr.ipv6 = ipv6->destination;
    }
    net->nh.dip.type = net->network.type;
    net->nh.vid = route->vlan;
}

static inline void route2mc_rt(const vtss_routing_mc_entry_t *route,
                                vtss_l3_mc_rt_t *net)
{
    VTSS_MEMSET(net, 0, sizeof(*net));
    if (route->type == VTSS_RT_TYPE_IPV4_MC) {
        const vtss_ipv4_mc_t *ipv4 = &route->route.ipv4_mc;
        net->network.type = VTSS_IP_TYPE_IPV4;
        net->network.addr.ipv4 = ipv4->group;
        net->sip.type = VTSS_IP_TYPE_IPV4;
        net->sip.addr.ipv4 = ipv4->source;
    } else {
        const vtss_ipv6_mc_t *ipv6 = &route->route.ipv6_mc;
        net->network.type = VTSS_IP_TYPE_IPV6;
        net->network.addr.ipv6 = ipv6->group;
        net->sip.type = VTSS_IP_TYPE_IPV6;
        net->sip.addr.ipv6 = ipv6->source;
    }
    net->src_rleg = route->source_rleg;
}

static vtss_rc rt_res_check(vtss_state_t *vtss_state, u32 ipv4_cnt, u32 ipv6_cnt)
{
    vtss_res_chg_t res;

    VTSS_MEMSET(&res, 0, sizeof(res));
    res.add_key[VTSS_VCAP_KEY_SIZE_SIXTEENTH] = ipv4_cnt;
    res.add_key[VTSS_VCAP_KEY_SIZE_QUARTER] = ipv6_cnt;
    return vtss_cmn_vcap_res_check(&vtss_state->vcap.lpm.obj, &res);
}

static vtss_rc mc_rt_res_check(vtss_state_t *vtss_state, u32 ipv4_cnt, u32 ipv6_cnt)
{
    vtss_res_chg_t res;

    VTSS_MEMSET(&res, 0, sizeof(res));
    res.add_key[VTSS_VCAP_KEY_SIZE_EIGHTH] = ipv4_cnt;
    res.add_key[VTSS_VCAP_KEY_SIZE_HALF] = ipv6_cnt;
    return vtss_cmn_vcap_res_check(&vtss_state->vcap.lpm.obj, &res);
}

static BOOL mc_tbl_find(vtss_l3_mc_tbl_t *tbl, u32 *rlegs, u8 rpf, u16 *id)
{
    u32 i, a;

    if (rlegs == NULL) {
        // Find an empty table entry
        for (i = 0; i < VTSS_MC_TBL_CNT; ++i) {
            if (tbl[i].cnt == 0) {
                for (a = 0; a < 4; a++) {
                    tbl[i].rlegs[a] = 0;
                }
                tbl[i].rpf = VTSS_L3_MC_RPF_DIS;
                *id = i;
                return TRUE;
            }
        }
        // No empty table entries left
        return FALSE;
    } else {
        // Find an specific table entry
        for (i = 0; i < VTSS_MC_TBL_CNT; ++i) {
            if (tbl[i].cnt == 0) {
                continue;
            }
            if ((VTSS_MEMCMP(rlegs, tbl[i].rlegs, sizeof(tbl[i].rlegs)) == 0) && (tbl[i].rpf == rpf)) {
                // found a match
                *id = i;
                return TRUE;
            }
        }
    }
    // Entry not found
    return FALSE;
}

static vtss_rc mc_update_rleg_tbl(vtss_state_t           *vtss_state,
                                  vtss_l3_mc_rt_t        *cur,
                                  u32                    *new_rlegs,
                                  BOOL                   *rt_update)
{
    u16                   new_tbl_id, i;
    vtss_l3_rleg_id_t     rpf = VTSS_L3_MC_RPF_DIS;
    vtss_l3_mc_tbl_t      *tbl_ptr = vtss_state->l3.mc_tbl;

    // For RPF
    if (cur->src_rleg != VTSS_VID_NULL) {
        if (rleg_id_get(vtss_state->l3.rleg_conf, cur->src_rleg, &rpf, NULL) != VTSS_RC_OK) {
            E("Router leg not found");
            return VTSS_RC_ERROR;
        }
    }
    // Does the new rleg entry exist?
    if (mc_tbl_find(tbl_ptr, new_rlegs, rpf, &new_tbl_id)) {
        // Yes it does, use it
        tbl_ptr[cur->tbl].cnt--;
        cur->tbl = new_tbl_id;
        tbl_ptr[new_tbl_id].cnt++;
        *rt_update = TRUE;
    } else if (tbl_ptr[cur->tbl].cnt == 1) {
        // Update the existing one
        if (tbl_ptr[cur->tbl].rpf != rpf) {
            tbl_ptr[cur->tbl].rpf = rpf;
            *rt_update = TRUE;
        } else {
            *rt_update = FALSE;
        }
    } else {
        // Entry does not exist create a new one
        if (!mc_tbl_find(tbl_ptr, NULL, 0, &new_tbl_id)) {
            I("MC L3 Table is full");
            return VTSS_RC_ERROR;
        }
        tbl_ptr[cur->tbl].cnt--;
        cur->tbl = new_tbl_id;
        tbl_ptr[new_tbl_id].cnt++;
        tbl_ptr[cur->tbl].rpf = rpf;
        *rt_update = TRUE;
    }
    for (i = 0; i < 4; ++i) {
        tbl_ptr[cur->tbl].rlegs[i] = new_rlegs[i];
    }
    return VTSS_RC_OK;
}

static inline vtss_rc mc_rt_rleg_modify(vtss_state_t                  *vtss_state,
                                        const vtss_routing_mc_entry_t *const route,
                                        const vtss_vid_t               dest_rleg,
                                        BOOL add)
{
    vtss_l3_mc_rt_info_t *info = &vtss_state->l3.mc_rt;
    vtss_l3_mc_rt_t      *cur, net_old;
    vtss_l3_mc_tbl_t      *tbl_ptr = vtss_state->l3.mc_tbl;
    int                   cmp = 1;
    u32                   new_rlegs[4] = {0};
    u16                   i;
    vtss_l3_rleg_id_t     rleg_id = 0;
    BOOL                  rt_update;

    /* Search for an existing network */
    route2mc_rt(route, &net_old);
    for (cur = info->list; cur != NULL; cur = cur->next) {
        if ((cmp = mc_rt_cmp(&net_old, cur)) >= 0) {
            break;
        }
    }
    if (cmp != 0) {
        I("MC Route not found");
        return VTSS_RC_ERROR;
    }
    if (rleg_id_get(vtss_state->l3.rleg_conf, dest_rleg, &rleg_id, NULL) != VTSS_RC_OK) {
        E("Router leg not found");
        return VTSS_RC_ERROR;
    }

    if (rleg_id >= 128) {
        E("Router leg id above 128 not supported");
        return VTSS_RC_ERROR;
    }

    for (i = 0; i < 4; i++) {
        new_rlegs[i] = tbl_ptr[cur->tbl].rlegs[i];
    }
    /* rleg id to mc mask */
    if (add) {
        new_rlegs[rleg_id / 32] |= 1 << (rleg_id % 32); // add the rleg bit
    } else {
        new_rlegs[rleg_id / 32] &= ~(1 << (rleg_id % 32)); // clear the rleg bit
    }
    VTSS_RC(mc_update_rleg_tbl(vtss_state, cur, new_rlegs, &rt_update));

    return rt_update ? mc_rt_update(vtss_state, cur, TRUE) : VTSS_FUNC(l3.mc_rt_rleg_add, cur);
}

/* Get/clear LPM counter */
vtss_rc vtss_lpm_mc_entry_get(vtss_state_t *vtss_state,  const u64 id, u32 *const counter, BOOL clear)
{
    vtss_vcap_idx_t idx;
    vtss_vcap_obj_t *obj = &vtss_state->vcap.lpm.obj;

    if (vtss_vcap_lookup(vtss_state, obj, VTSS_LPM_USER_L3_MC, id, NULL, &idx) != VTSS_RC_OK) {
        VTSS_E("id not found");
        return VTSS_RC_ERROR;
    }
    return(obj->entry_get(vtss_state, &idx, counter, clear));
}

static inline vtss_rc mc_rt_get_active(vtss_state_t                  *vtss_state,
                                       const vtss_routing_mc_entry_t *const route,
                                       BOOL *active)
{
    vtss_l3_mc_rt_info_t *info = &vtss_state->l3.mc_rt;
    vtss_l3_mc_rt_t   *cur, net_old;
    u32 cnt;

    route2mc_rt(route, &net_old);
    for (cur = info->list; cur != NULL; cur = cur->next) {
        if (mc_rt_cmp(&net_old, cur) == 0) {
            break;
        }
    }

    if (cur == NULL) {
        I("MC route not found");
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_lpm_mc_entry_get(vtss_state, cur->id, &cnt, TRUE));
    *active = (cnt > 0) ? TRUE : FALSE;
    return VTSS_RC_OK;
}

static inline vtss_rc mc_rt_add(vtss_state_t                  *vtss_state,
                                const vtss_routing_mc_entry_t *const route)
{
    vtss_l3_mc_rt_info_t *info = &vtss_state->l3.mc_rt;
    vtss_l3_mc_tbl_t      *tbl_ptr = vtss_state->l3.mc_tbl;
    vtss_vcap_obj_t    *obj = &vtss_state->vcap.lpm.obj;
    vtss_l3_mc_rt_t   *cur, *prev = NULL, net_new;
    int                cmp = 1;
    u8                 cnt;
    u16                new_tbl_id;

    /* Search for an existing network or a place to insert new network */
    route2mc_rt(route, &net_new);
    for (cur = info->list; cur != NULL; prev = cur, cur = cur->next) {
        if ((cmp = mc_rt_cmp(&net_new, cur)) >= 0) {
            break;
        }
    }

    if (cmp != 0) {
        /* Add new network */
        if (vtss_state->l3.common.mc_routing_enable &&
            (obj->count == obj->max_count)) {
            /* Routing is enabled and current LPM block is full, check resources */
            cnt = (net_new.network.type == VTSS_IP_TYPE_IPV4 ? 1 : 0);
            VTSS_RC(mc_rt_res_check(vtss_state, cnt, 1 - cnt));
        }
        if ((cur = info->free) == NULL || info->free_cnt == 0) {
            /* Allocation failed */
            E("no free mc entries");
            return VTSS_RC_ERROR;
        }
        if (net_new.network.type == VTSS_IP_TYPE_IPV4) {
            info->free_cnt--;
        } else {
            info->free_cnt = info->free_cnt < 4 ? 0 : info->free_cnt - 4;
        }

        info->free = cur->next;
        *cur = net_new;
        cur->id = info->id++;
        if (prev == NULL) {
            /* Insert first */
            cur->next = info->list;
            info->list = cur;
        } else {
            /* Insert after previous entry */
            cur->next = prev->next;
            prev->next = cur;
        }

        // Find an empty L3 MC entry
        if (!mc_tbl_find(tbl_ptr, NULL, 0, &new_tbl_id)) {
            E("MC L3 Table is full");
            return VTSS_RC_ERROR;
        }
        cur->tbl = new_tbl_id;
        tbl_ptr[new_tbl_id].cnt++;
        return mc_rt_update(vtss_state, cur, TRUE);
    }
    return VTSS_RC_OK;
}

static inline vtss_rc mc_rt_del(vtss_state_t                  *vtss_state,
                                const vtss_routing_mc_entry_t *const route)
{
    vtss_l3_mc_rt_info_t *info = &vtss_state->l3.mc_rt;
    vtss_l3_mc_tbl_t     *tbl_ptr = vtss_state->l3.mc_tbl;
    vtss_l3_mc_rt_t      *cur, *prev = NULL, net_old;
    /* Search for route */
    route2mc_rt(route, &net_old);
    for (cur = info->list; cur != NULL; prev = cur, cur = cur->next) {
        if (mc_rt_cmp(&net_old, cur) == 0) {
            break;
        }
    }
    if (cur == NULL) {
        I("MC route not found");
        return VTSS_RC_ERROR;
    }

    tbl_ptr[cur->tbl].cnt--;

    if (prev == NULL) {
        info->list = cur->next;
    } else {
        prev->next = cur->next;
    }
    cur->next = info->free;
    info->free = cur;
    if (net_old.network.type == VTSS_IP_TYPE_IPV4) {
        info->free_cnt++;
    } else {
        info->free_cnt += 4;
    }
    return mc_rt_update(vtss_state, cur, FALSE);
}

static inline vtss_rc rt_add(vtss_state_t               *vtss_state,
                             const vtss_routing_entry_t *const route)
{
    vtss_l3_net_info_t *info = &vtss_state->l3.net;
    vtss_vcap_obj_t    *obj = &vtss_state->vcap.lpm.obj;
    vtss_l3_net_t      *cur, *prev = NULL, net_new;
    vtss_l3_nh_grp_t   *grp;
    vtss_l3_nh_t       nh_new, nh_old, *list, *nh, *prev_nh = NULL;
    int                cmp = 1;
    u8                 cnt;

    /* Search for an existing network or a place to insert new network */
    route2net(route, &net_new);
    for (cur = info->list; cur != NULL; prev = cur, cur = cur->next) {
        if ((cmp = net_cmp(&net_new, cur)) >= 0) {
            break;
        }
    }

    if (cmp != 0) {
        /* Add new network */
        if (vtss_state->l3.common.routing_enable &&
            obj->count == obj->max_count) {
            /* Routing is enabled and current LPM block is full, check resources */
            cnt = (net_new.network.type == VTSS_IP_TYPE_IPV4 ? 1 : 0);
            VTSS_RC(rt_res_check(vtss_state, cnt, 1 - cnt));
        }
        if ((cur = info->free) == NULL) {
            /* Allocation failed */
            I("no free net entries");
            return VTSS_RC_ERROR;
        }
        info->free_cnt--;
        info->free = cur->next;
        *cur = net_new;
        cur->id = info->id++;
        if (prev == NULL) {
            /* Insert first */
            cur->next = info->list;
            info->list = cur;
        } else {
            /* Insert after previous entry */
            cur->next = prev->next;
            prev->next = cur;
        }
        return rt_update(vtss_state, cur, nb_lookup(vtss_state, &cur->nh), 0);
    }

    /* Existing route was found */
    nh_new.nh = net_new.nh;
    if (cur->grp == NULL) {
        /* Network has a single next-hop */
        nh_old.nh = cur->nh;
        if ((cmp = nh_cmp(&nh_new.nh, &nh_old.nh)) == 0) {
            /* Single unchanged next-hop */
            return VTSS_RC_OK;
        } else if (cmp < 0) {
            /* New next-hop is first */
            list = &nh_new;
            nh_new.next = &nh_old;
            nh_old.next = NULL;
        } else {
            /* Old next-hop is first */
            list = &nh_old;
            nh_old.next = &nh_new;
            nh_new.next = NULL;
        }
        /* Variable 'list' now has two entries allocated on stack */
        cnt = 2;
        if ((grp = nh_grp_lookup(vtss_state, list)) == NULL) {
            if ((grp = nh_grp_alloc(vtss_state, cnt)) == NULL) {
                return VTSS_RC_ERROR;
            }

            /* Insert next-hop entries in list */
            for (nh = list, list = NULL; nh != NULL; nh = nh->next) {
                prev_nh = nh_alloc(vtss_state, &list, prev_nh, nh);
            }
            grp->list = list;
            VTSS_RC(nh_grp_update(vtss_state, grp));
        }
        grp->count++;
        cur->grp = grp;
        return rt_update(vtss_state, cur, NULL, cnt);
    }

    /* Network with multiple next-hops */
    list = cur->grp->list;
    cnt = 1;
    for (nh = list; nh != NULL; nh = nh->next) {
        cnt++;
    }
    for (nh = list; nh != NULL; prev_nh = nh, nh = nh->next) {
        if ((cmp = nh_cmp(&nh->nh, &nh_new.nh)) >= 0) {
            break;
        }
    }
    if (cmp == 0) {
        /* Next-hop already found in list */
        return VTSS_RC_OK;
    }

    /* Temporarily insert nh_new in list to check if it is a new list */
    nh = &nh_new;
    if (prev_nh == NULL) {
        nh->next = list;
        list = nh;
    } else {
        nh->next = prev_nh->next;
        prev_nh->next = nh;
    }
    grp = nh_grp_lookup(vtss_state, list);
    if (prev_nh != NULL) {
        /* Take nh_new out of list again */
        prev_nh->next = nh->next;
    }

    if (grp == NULL) {
        /* New or changed group */
        if ((grp = nh_grp_alloc(vtss_state, cnt)) == NULL) {
            /* Allocation of new group failed */
            return VTSS_RC_ERROR;
        }
        prev_nh = NULL;
        for (nh = cur->grp->list, list = NULL; nh != NULL; nh = nh->next) {
            prev_nh = nh_alloc(vtss_state, &list, prev_nh, nh);
        }
        prev_nh = NULL;
        for (nh = list; nh != NULL; prev_nh = nh, nh = nh->next) {
            if (nh_cmp(&nh->nh, &nh_new.nh) > 0) {
                break;
            }
        }
        (void) nh_alloc(vtss_state, &list, prev_nh, &nh_new);
        grp->list = list;
        VTSS_RC(nh_grp_update(vtss_state, grp));
    }

    /* Free old list and use new/matching list */
    nh_grp_free(vtss_state, cur->grp);
    cur->grp = grp;
    grp->count++;
    return rt_update(vtss_state, cur, NULL, cnt);
}

static inline vtss_rc rt_del(vtss_state_t               *vtss_state,
                             const vtss_routing_entry_t *const route)
{
    vtss_l3_net_info_t *info = &vtss_state->l3.net;
    vtss_l3_net_t      *cur, *prev = NULL, net_old;
    vtss_l3_nh_grp_t   *grp;
    vtss_l3_nh_t       *nh, *prev_nh = NULL, *list;
    u8                 cnt;

    /* Search for network */
    route2net(route, &net_old);
    for (cur = info->list; cur != NULL; prev = cur, cur = cur->next) {
        if (net_cmp(&net_old, cur) == 0) {
            break;
        }
    }

    if (cur == NULL) {
        I("network not found");
        return VTSS_RC_ERROR;
    }

    if (cur->grp == NULL) {
        /* Network with single next-hop, free it */
        if (prev == NULL) {
            info->list = cur->next;
        } else {
            prev->next = cur->next;
        }
        cur->next = info->free;
        info->free = cur;
        info->free_cnt++;
        return rt_update(vtss_state, cur, NULL, VTSS_L3_NH_MAX + 1);
    }

    /* Network with multiple next-hops */
    list = cur->grp->list;
    for (cnt = 0, nh = list; nh != NULL; nh = nh->next) {
        cnt++;
    }
    for (nh = list; nh != NULL; prev_nh = nh, nh = nh->next) {
        if (nh_cmp(&nh->nh, &net_old.nh) == 0) {
            break;
        }
    }

    if (nh == NULL) {
        I("next-hop not found");
        return VTSS_RC_ERROR;
    }

    if (cnt < 3) {
        /* Route has two next-hops and returns to single next-hop */
        cur->nh = (nh->next == NULL ? list->nh : nh->next->nh);
        I("single next-hop, free idx: %u", cur->grp->idx);
        nh_grp_free(vtss_state, cur->grp);
        cur->grp = NULL;
        return rt_update(vtss_state, cur, nb_lookup(vtss_state, &cur->nh), 0);
    }

    /* Temporarily take out next-hop from list to look for an existing list */
    cnt--;
    if (prev_nh == NULL) {
        list = nh->next;
    } else {
        prev_nh->next = nh->next;
    }
    grp = nh_grp_lookup(vtss_state, list);
    if (prev_nh != NULL) {
        /* Put back next-hop again */
        prev_nh->next = nh;
    }

    if (grp == NULL) {
        /* New or changed group */
        if ((grp = nh_grp_alloc(vtss_state, cnt)) == NULL) {
            /* Allocation of new group failed */
            return VTSS_RC_ERROR;
        }
        prev_nh = NULL;
        for (nh = cur->grp->list, list = NULL; nh != NULL; nh = nh->next) {
            if (nh_cmp(&nh->nh, &net_old.nh)) {
                prev_nh = nh_alloc(vtss_state, &list, prev_nh, nh);
            }
        }
        grp->list = list;
        VTSS_RC(nh_grp_update(vtss_state, grp));
    }

    /* Free old list and use new/matching list */
    nh_grp_free(vtss_state, cur->grp);
    cur->grp = grp;
    grp->count++;
    return rt_update(vtss_state, cur, NULL, cnt);
}


/* - Neighbours ---------------------------------------------------- */

static inline void nb2nh(const vtss_l3_neighbour_t *nb,
                         vtss_l3_nh_key_t *nh)
{
    nh->dip = nb->dip;
    nh->vid = nb->vlan;
}

static inline vtss_rc nb_update(vtss_state_t *vtss_state,
                                vtss_l3_nb_t *nb)
{
    vtss_l3_state_t  *l3 = &vtss_state->l3;
    vtss_l3_net_t    *net;
    vtss_l3_nh_grp_t *grp;
    vtss_l3_nh_t     *nh;
    vtss_rc          rc;
    u32              idx;

    /* Search for single next-hop addresses to update */
    for (net = l3->net.list; net != NULL; net = net->next) {
        if (net->grp == NULL &&
            nh_cmp(&net->nh, &nb->nh) == 0 &&
            (rc = rt_update(vtss_state, net, nb, 0)) != VTSS_RC_OK) {
            return rc;
        }
    }

    /* Look for group next-hop entries to update */
    for (grp = l3->nh_grp.list; grp != NULL; grp = grp->next) {
        for (nh = grp->list, idx = grp->idx; nh != NULL; nh = nh->next, idx++) {
            if (nh_cmp(&nh->nh, &nb->nh) == 0 &&
                (rc = nh_update(vtss_state, idx, nb)) != VTSS_RC_OK) {
                return VTSS_RC_OK;
            }
        }
    }
    return VTSS_RC_OK;
}

static inline vtss_rc nb_add(vtss_state_t              *vtss_state,
                             const vtss_l3_neighbour_t *const nb)
{
    vtss_l3_nb_info_t *info = &vtss_state->l3.nb;
    vtss_l3_nb_t      *cur, *prev = NULL;
    vtss_l3_rleg_id_t rleg = 0;
    vtss_l3_nh_key_t  nh;
    int               cmp = 1;

    VTSS_RC(rleg_id_get(vtss_state->l3.rleg_conf, nb->vlan, &rleg, NULL));

    /* Search for an existing entry or a place to insert new entry */
    nb2nh(nb, &nh);
    for (cur = info->list; cur != NULL; prev = cur, cur = cur->next) {
        if ((cmp = nh_cmp(&cur->nh, &nh)) >= 0) {
            break;
        }
    }

    if (cmp != 0) {
        /* Add new entry */
        if ((cur = info->free) == NULL) {
            /* Allocation failed */
            I("no free neighbour entries");
            return VTSS_RC_ERROR;
        } else {
            info->free_cnt--;
            info->free = cur->next;
            if (prev == NULL) {
                /* Insert first */
                cur->next = info->list;
                info->list = cur;
            } else {
                /* Insert after previous entry */
                cur->next = prev->next;
                prev->next = cur;
            }
        }
    }

    /* Save entry and update hardware */
    cur->nh = nh;
    cur->dmac = nb->dmac;
    cur->rleg = rleg;
    return nb_update(vtss_state, cur);
}

static inline vtss_rc nb_del(vtss_state_t              *vtss_state,
                             const vtss_l3_neighbour_t *const nb)
{
    vtss_l3_nb_info_t *info = &vtss_state->l3.nb;
    vtss_l3_nb_t      *cur, *prev = NULL;
    vtss_l3_nh_key_t  nh;

    /* Search for entry */
    nb2nh(nb, &nh);
    for (cur = info->list; cur != NULL; prev = cur, cur = cur->next) {
        if (nh_cmp(&cur->nh, &nh) == 0) {
            break;
        }
    }

    if (cur == NULL) {
        I("neighbour not found");
        return VTSS_RC_ERROR;
    }

    if (prev == NULL) {
        info->list = cur->next;
    } else {
        prev->next = cur->next;
    }
    cur->next = info->free;
    info->free = cur;
    info->free_cnt++;

    /* Clear DMAC and update hardware */
    VTSS_MEMSET(&cur->dmac, 0, sizeof(cur->dmac));
    return nb_update(vtss_state, cur);
}

/* Implementing the public API */
vtss_rc vtss_l3_flush(const vtss_inst_t inst)
{
    /* Obsolete API function */
    return VTSS_RC_OK;
}

vtss_rc vtss_l3_common_get(const vtss_inst_t      inst,
                           vtss_l3_common_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->l3.common;
        rc = VTSS_RC_OK;
    }
    VTSS_L3_EXIT();

    return rc;
}

static vtss_rc rt_setup(vtss_state_t *vtss_state, BOOL enable)
{
    vtss_l3_state_t *l3 = &vtss_state->l3;
    vtss_l3_net_t   *net, *next;
    vtss_l3_nh_t    *nh;
    vtss_l3_nb_t    *nb = NULL;
    u32             cnt = (VTSS_L3_NH_MAX + 1), ipv4_cnt = 0, ipv6_cnt = 0;
    vtss_rc         rc = VTSS_RC_OK;

    if (enable) {
        /* Check resources */
        for (net = vtss_state->l3.net.list; net != NULL; net = net->next) {
            if (net->network.type == VTSS_IP_TYPE_IPV4) {
                ipv4_cnt++;
            } else {
                ipv6_cnt++;
            }
        }
        VTSS_RC(rt_res_check(vtss_state, ipv4_cnt, ipv6_cnt));
    }

    /* Enable routing temporarily to allow CIL calls */
    l3->common.routing_enable = TRUE;
    l3->common.mc_routing_enable = TRUE;
    for (net = vtss_state->l3.net.list; net != NULL; net = net->next) {
        if (enable) {
            /* Add routes */
            cnt = 0;
            if (net->grp != NULL) {
                nb = NULL;
                VTSS_RC(nh_grp_update(vtss_state, net->grp));
                for (nh = net->grp->list; nh != NULL; nh = nh->next) {
                    cnt++;
                }
            } else {
                nb = nb_lookup(vtss_state, &net->nh);
            }
        }
        /* Insert last by clearing 'next' pointer temporarily */
        next = net->next;
        net->next = NULL;
        rc = rt_update(vtss_state, net, nb, cnt);
        net->next = next;
        if (rc != VTSS_RC_OK) {
            break;
        }
    }
    l3->common.routing_enable = (enable ? 0 : 1);

    return rc;
}

vtss_rc vtss_l3_common_set(const vtss_inst_t            inst,
                           const vtss_l3_common_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    BOOL         enable;

    I("%s %d " MAC_FORMAT, __FUNCTION__, conf->rleg_mode,
      MAC_ARGS(conf->base_address));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = VTSS_FUNC(l3.common_set, conf)) == VTSS_RC_OK) {
        enable = (conf->routing_enable ? 1 : 0);
        if (enable != (vtss_state->l3.common.routing_enable ? 1 : 0)) {
            I("routing is %sabled at runtime", enable ? "en" : "dis");
            rc = rt_setup(vtss_state, enable);
        }
        if (rc == VTSS_RC_OK) {
            vtss_state->l3.common = *conf;
        }
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_rleg_add(const vtss_inst_t          inst,
                         const vtss_l3_rleg_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    I("%s vlan:%u %s %s %s %s %s %s %d %d",
      __FUNCTION__,
      conf->vlan,
      (conf->ipv4_unicast_enable ? "ipv4_uc" : "no-ipv4_uc"),
      (conf->ipv6_unicast_enable ? "ipv6_uc" : "no-ipv6_uc"),
      (conf->ipv4_multicast_enable ? "ipv4_mc" : "no-ipv4_mc"),
      (conf->ipv6_multicast_enable ? "ipv6_mc" : "no-ipv6_mc"),
      (conf->ipv4_icmp_redirect_enable ? "ipv4_icmp_redirect" : "no-ipv4_icmp_redirect"),
      (conf->ipv6_icmp_redirect_enable ? "ipv6_icmp_redirect" : "no-ipv6_icmp_redirect"),
      (conf->vrid0_enable ? (int)conf->vrid0 : -1),
      (conf->vrid1_enable ? (int)conf->vrid1 : -1)
    );

    if (conf->vlan == VTSS_VID_NULL || conf->vlan > VTSS_VID_RESERVED) {
        E("%u is not a valid vlan id", conf->vlan);
        return VTSS_RC_ERROR;
    }

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = rleg_add(vtss_state, vtss_state->l3.rleg_conf, conf);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_rleg_update(const vtss_inst_t          inst,
                            const vtss_l3_rleg_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    I("%s vlan:%u %s %s %s %s %s %s %d %d",
      __FUNCTION__,
      conf->vlan,
      (conf->ipv4_unicast_enable ? "ipv4_uc" : "no-ipv4_uc"),
      (conf->ipv6_unicast_enable ? "ipv6_uc" : "no-ipv6_uc"),
      (conf->ipv4_multicast_enable ? "ipv4_mc" : "no-ipv4_mc"),
      (conf->ipv6_multicast_enable ? "ipv6_mc" : "no-ipv6_mc"),
      (conf->ipv4_icmp_redirect_enable ? "ipv4_redir" : "no-ipv4_redir"),
      (conf->ipv6_icmp_redirect_enable ? "ipv6_redir" : "no-ipv6_redir"),
      (conf->vrid0_enable ? (int)conf->vrid0 : -1),
      (conf->vrid1_enable ? (int)conf->vrid1 : -1)
    );

    if (conf->vlan == VTSS_VID_NULL || conf->vlan > VTSS_VID_RESERVED) {
        E("%u is not a valid vlan id", conf->vlan);
        return VTSS_RC_ERROR;
    }

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = rleg_update(vtss_state, vtss_state->l3.rleg_conf, conf);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_rleg_get_specific(const vtss_inst_t     inst,
                                  vtss_vid_t            vid,
                                  vtss_l3_rleg_conf_t  *conf) {
    vtss_state_t *vtss_state;
    vtss_rc rc;

    if (vid == VTSS_VID_NULL || vid > VTSS_VID_RESERVED) {
        E("%u is not a valid vlan id", vid);
        return VTSS_RC_ERROR;
    }

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = rleg_id_get(vtss_state->l3.rleg_conf, vid, NULL, conf);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_rleg_del(const vtss_inst_t inst,
                         const vtss_vid_t  vlan)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    I("%s vlan:%u", __FUNCTION__, vlan);

    if (vlan == VTSS_VID_NULL || vlan > VTSS_VID_RESERVED) {
        E("%u is not a valid vlan id", vlan);
        return VTSS_RC_ERROR;
    }

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = rleg_del(vtss_state, vtss_state->l3.rleg_conf, vlan);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_counters_reset(const vtss_inst_t inst)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    I("l3_counters_reset");

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(l3.rleg_counters_reset);
        VTSS_MEMSET(&(vtss_state->l3.statistics), 0, sizeof(vtss_l3_statistics_t));
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_counters_system_get(const vtss_inst_t  inst,
                                    vtss_l3_counters_t *const counters)
{
    vtss_state_t       *vtss_state;
    vtss_rc            rc;
    u32                i;
    vtss_l3_counters_t *cnt;

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        VTSS_MEMSET(counters, 0, sizeof(*counters));
        for (i = 0; i < VTSS_RLEG_CNT; i++) {
            if (vtss_state->l3.rleg_conf[i].vlan != 0 &&
                VTSS_FUNC(l3.rleg_counters_get, i) == VTSS_RC_OK) {
                /* Summarize router leg counters */
                cnt = &vtss_state->l3.statistics.interface_counter[i];
                counters->ipv4uc_received_octets += cnt->ipv4uc_received_octets;
                counters->ipv4uc_received_frames += cnt->ipv4uc_received_frames;
                counters->ipv6uc_received_octets += cnt->ipv6uc_received_octets;
                counters->ipv6uc_received_frames += cnt->ipv6uc_received_frames;
                counters->ipv4mc_received_octets += cnt->ipv4mc_received_octets;
                counters->ipv4mc_received_frames += cnt->ipv4mc_received_frames;
                counters->ipv6mc_received_octets += cnt->ipv6mc_received_octets;
                counters->ipv6mc_received_frames += cnt->ipv6mc_received_frames;
                counters->ipv4uc_transmitted_octets += cnt->ipv4uc_transmitted_octets;
                counters->ipv4uc_transmitted_frames += cnt->ipv4uc_transmitted_frames;
                counters->ipv6uc_transmitted_octets += cnt->ipv6uc_transmitted_octets;
                counters->ipv6uc_transmitted_frames += cnt->ipv6uc_transmitted_frames;
                counters->ipv4mc_transmitted_octets += cnt->ipv4mc_transmitted_octets;
                counters->ipv4mc_transmitted_frames += cnt->ipv4mc_transmitted_frames;
                counters->ipv6mc_transmitted_octets += cnt->ipv6mc_transmitted_octets;
                counters->ipv6mc_transmitted_frames += cnt->ipv6mc_transmitted_frames;
            }
        }
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_counters_rleg_get(const vtss_inst_t   inst,
                                  const vtss_vid_t    vlan,
                                  vtss_l3_counters_t *const counters)
{
#define DO(X)                                          \
    if (rc == VTSS_RC_OK) {                            \
        rc = (X);                                      \
        if (rc != VTSS_RC_OK) {                        \
            E("Failed: " #X "rleg_id = %d, vlan = %d", \
              rleg, vlan);                             \
        }                                              \
    }

    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_OK;
    vtss_l3_rleg_id_t rleg = 0;
    D("%s vlan:%u", __FUNCTION__, vlan);

    if (vlan == VTSS_VID_NULL || vlan > VTSS_VID_RESERVED) {
        E("%u is not a valid vlan id", vlan);
        return VTSS_RC_ERROR;
    }

    VTSS_L3_ENTER();
    DO(vtss_inst_check(inst, &vtss_state));
    DO(rleg_id_get(vtss_state->l3.rleg_conf, vlan, &rleg, 0));
    if (rc == VTSS_RC_OK &&
        VTSS_FUNC(l3.rleg_counters_get, rleg) == VTSS_RC_OK) {
        *counters = vtss_state->l3.statistics.interface_counter[rleg];
    }
    VTSS_L3_EXIT();

#undef DO
    return rc;
}

vtss_rc vtss_l3_counters_rleg_clear(const vtss_inst_t   inst,
                                    const vtss_vid_t    vlan)
{
#define DO(X)                                          \
    if (rc == VTSS_RC_OK) {                            \
        rc = (X);                                      \
        if (rc != VTSS_RC_OK) {                        \
            E("Failed: " #X "rleg_id = %d, vlan = %d", \
              rleg, vlan);                             \
        }                                              \
    }

    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_OK;
    vtss_l3_rleg_id_t rleg = 0;
    D("%s vlan:%u", __FUNCTION__, vlan);

    if (vlan == VTSS_VID_NULL || vlan > VTSS_VID_RESERVED) {
        E("%u is not a valid vlan id", vlan);
        return VTSS_RC_ERROR;
    }

    VTSS_L3_ENTER();
    DO(vtss_inst_check(inst, &vtss_state));
    DO(rleg_id_get(vtss_state->l3.rleg_conf, vlan, &rleg, 0));
    if (rc == VTSS_RC_OK) {
        (void) VTSS_MEMSET(&(vtss_state->l3.statistics.interface_counter[rleg]), 0,
                      sizeof(vtss_l3_counters_t));
    }
    VTSS_L3_EXIT();

#undef DO
    return rc;
}

vtss_rc vtss_l3_route_add(const vtss_inst_t          inst,
                          const vtss_routing_entry_t *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("%s", vtss_routing_entry_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = rt_add(vtss_state, entry);
    }
    VTSS_L3_EXIT();

    return rc;
}

static vtss_rc RT_bulk_add_del(const vtss_inst_t             inst,
                               const u32                     cnt,
                               BOOL                          del,
                               const vtss_routing_entry_t    *entry,
                               u32                           *const cnt_out)
{
    vtss_rc rc;
    vtss_mtimer_t start_time;
    u32 done_ = 0, i = 0;
    vtss_state_t *vtss_state;

    VTSS_L3_ENTER();
    VTSS_MTIMER_START(&start_time, BULK_TIME_MAX);
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (i = 0; i < cnt; ++i, ++entry) {
            if (del) {
                // Ignore return value when doing bulk delete operations.
                // Resource is not expected to be an issue here.
                (void)rt_del(vtss_state, entry);
            } else {
                rc = rt_add(vtss_state, entry);
            }

            if (rc != VTSS_RC_OK) {
                break;
            }

            done_++;
            if (VTSS_MTIMER_TIMEOUT(&start_time)) {
                break;
            }
        }
    }
    VTSS_L3_EXIT();

    *cnt_out = done_;

    // Success if one or more routes was added correctly
    if (done_ > 0) {
        return VTSS_RC_OK;
    }

    return rc;
}

vtss_rc vtss_l3_route_bulk_add(const vtss_inst_t             inst,
                               const u32                     cnt,
                               const vtss_routing_entry_t    *entry,
                               u32                           *const rt_added)
{
    return RT_bulk_add_del(inst, cnt, FALSE, entry, rt_added);
}

vtss_rc vtss_l3_route_del(const vtss_inst_t          inst,
                          const vtss_routing_entry_t *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("%s", vtss_routing_entry_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = rt_del(vtss_state, entry);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_route_bulk_del(const vtss_inst_t             inst,
                               const u32                     cnt,
                               const vtss_routing_entry_t    *entry,
                               u32                           *const rt_deleted)
{
    return RT_bulk_add_del(inst, cnt, TRUE, entry, rt_deleted);
}

vtss_rc vtss_l3_neighbour_add(const vtss_inst_t         inst,
                              const vtss_l3_neighbour_t *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("%s", vtss_neighbour_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = nb_add(vtss_state, entry);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_neighbour_del(const vtss_inst_t         inst,
                              const vtss_l3_neighbour_t *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("%s", vtss_neighbour_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = nb_del(vtss_state, entry);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_mc_route_add(const vtss_inst_t              inst,
                             const vtss_routing_mc_entry_t  *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("%s", vtss_routing_mc_entry_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = mc_rt_add(vtss_state, entry);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_mc_route_active_get(const vtss_inst_t              inst,
                                    const vtss_routing_mc_entry_t  *const entry,
                                    BOOL *const active)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("%s", vtss_routing_mc_entry_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = mc_rt_get_active(vtss_state, entry, active);
    }
    VTSS_L3_EXIT();

    return rc;
}


vtss_rc vtss_l3_mc_route_del(const vtss_inst_t              inst,
                             const vtss_routing_mc_entry_t  *const entry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("%s", vtss_routing_mc_entry_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = mc_rt_del(vtss_state, entry);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_mc_route_rleg_add(const vtss_inst_t              inst,
                                  const vtss_routing_mc_entry_t  *const entry,
                                  const vtss_vid_t               dest_rleg)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("Add rleg:%d for group %s", dest_rleg,
      vtss_routing_mc_entry_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = mc_rt_rleg_modify(vtss_state, entry, dest_rleg, TRUE);
    }
    VTSS_L3_EXIT();

    return rc;
}

vtss_rc vtss_l3_mc_route_rleg_del(const vtss_inst_t              inst,
                                  const vtss_routing_mc_entry_t  *const entry,
                                  const vtss_vid_t               dest_rleg)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
#if VTSS_OPT_TRACE
    char         buf[128];
#endif

    I("Del rleg:%d for %s", dest_rleg,
      vtss_routing_mc_entry_to_string(entry, buf, sizeof(buf)));

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = mc_rt_rleg_modify(vtss_state, entry, dest_rleg, FALSE);
    }
    VTSS_L3_EXIT();

    return rc;
}


#ifdef __cplusplus
extern "C" vtss_rc vtss_l3_debug_sticky_clear(const vtss_inst_t inst);
#else
vtss_rc vtss_l3_debug_sticky_clear(const vtss_inst_t inst);
#endif
vtss_rc vtss_l3_debug_sticky_clear(const vtss_inst_t inst)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    I("sticky_clear");

    VTSS_L3_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        rc = VTSS_FUNC(l3.debug_sticky_clear);
    }
    VTSS_L3_EXIT();

    return rc;
}

void vtss_debug_print_l3(vtss_state_t *vtss_state,
                         const vtss_debug_printf_t pr,
                         const vtss_debug_info_t *const info)
{
    u32                        i, j, cnt = 0, counter;
    vtss_l3_rleg_common_mode_t m;
    vtss_l3_state_t            *l3 = &vtss_state->l3;
    vtss_l3_net_t              *net;
    vtss_l3_mc_rt_t           *mc_net;
    char                       buf[128];
    vtss_ip_type_t             type = VTSS_IP_TYPE_NONE;
    vtss_l3_nh_grp_t           *grp;
    vtss_l3_nh_t               *nh;
    vtss_l3_nb_t               *nb;
    vtss_l3_arp_row_t          *row;
    BOOL                       empty;

    vtss_l3_integrity_check(vtss_state, 0, 0);

    pr("Common:\n");
    pr("=======\n");
    pr("Routing enable: %s\n", l3->common.routing_enable ? "TRUE" : "FALSE");
    m = l3->common.rleg_mode;
    pr("Rleg_mode:      %s (%u)\n",
       m == VTSS_ROUTING_RLEG_MAC_MODE_INVALID ? "INVALID" :
       m == VTSS_ROUTING_RLEG_MAC_MODE_SINGLE ? "SINGLE" : "UNKNOWN",
       m);
    pr("Base address:   " MAC_FORMAT "\n\n", MAC_ARGS(l3->common.base_address));

    pr("Router Legs:\n");
    pr("============\n");
    pr("ID   RLEG IPv4UC IPv6UC IPv4MC IPv6MC IPv4ICMP IPv6ICMP vlan vrid0 vrid1 mc_limit ttl_limit\n");
    pr("---- ---- ------ ------ ------ ------ -------- -------- ---- ----- ----- -------- ---------\n");
    for (i = 0; i < VTSS_RLEG_CNT; i++) {
        const vtss_l3_rleg_conf_t *r = &l3->rleg_conf[i];

        if ( (!r->ipv4_unicast_enable) &&
             (!r->ipv6_unicast_enable) &&
             (!r->ipv4_multicast_enable) &&
             (!r->ipv6_multicast_enable) &&
             (!r->ipv4_icmp_redirect_enable) &&
             (!r->ipv6_icmp_redirect_enable) )
            continue;

        pr("%-5u%-5s%-7s%-7s%-7s%-7s%-9s%-9s%-5u",
           i,
           r->rleg_enable ? "ENA" : "DIS",
           r->ipv4_unicast_enable ? "ENA" : "DIS",
           r->ipv6_unicast_enable ? "ENA" : "DIS",
           r->ipv4_multicast_enable ? "ENA" : "DIS",
           r->ipv6_multicast_enable ? "ENA" : "DIS",
           r->ipv4_icmp_redirect_enable ? "ENA" : "DIS",
           r->ipv6_icmp_redirect_enable ? "ENA" : "DIS",
           r->vlan);
        if (r->vrid0_enable) {
            pr("%-6u", r->vrid0);
        } else {
            pr("DIS   ");
        }
        if (r->vrid1_enable) {
            pr("%-6u", r->vrid1);
        } else {
            pr("DIS   ");
        }
        pr("%-9s",r->mc_ttl_limit_enable ? "ENA" : "DIS");
        pr("%-9d",r->mc_ttl_limit);
        pr("\n");
    }
    pr("\n");

    pr("Networks:\n");
    pr("=========\n");
    pr("Free count: %u\n", l3->net.free_cnt);
    for (net = l3->net.list; net != NULL; net = net->next) {
        if (net->network.type != type) {
            type = net->network.type;
            pr("\n");
            if (type == VTSS_IP_TYPE_IPV4) {
                pr("%-20s", "Network");
            } else {
                pr("%-45s", "Network");
            }
            pr("NextHop\n");
        }
        if (type == VTSS_IP_TYPE_IPV4) {
            VTSS_SPRINTF(buf, IPV4N_FORMAT, IPV4_ARGS(net->network.addr.ipv4), net->prefix_size);
            pr("%-20s", buf);
            if (net->grp == NULL) {
                pr(IPV4_FORMAT "\n", IPV4_ARGS(net->nh.dip.addr.ipv4));
            } else {
                for (nh = net->grp->list; nh != NULL; nh = nh->next) {
                    if (nh != net->grp->list) {
                        pr("%-20s", "");
                    }
                    pr(IPV4_FORMAT "\n", IPV4_ARGS(nh->nh.dip.addr.ipv4));
                }
            }
        } else {
            VTSS_SPRINTF(buf, IPV6N_FORMAT, IPV6_ARGS(net->network.addr.ipv6), net->prefix_size);
            pr("%-45s", buf);
            if (net->grp == NULL) {
                pr(IPV6_FORMAT "-%u\n", IPV6_ARGS(net->nh.dip.addr.ipv6), net->nh.vid);
            } else {
                for (nh = net->grp->list; nh != NULL; nh = nh->next) {
                    if (nh != net->grp->list) {
                        pr("%-45s", "");
                    }
                    pr(IPV6_FORMAT "-%u\n", IPV6_ARGS(nh->nh.dip.addr.ipv6), nh->nh.vid);
                }
            }
        }
    }
    pr("\n");

    pr("NextHops:\n");
    pr("=========\n");
    pr("Free groups : %u\n", l3->nh_grp.free_cnt);
    pr("Free entries: %u\n", l3->nh.free_cnt);
    for (grp = l3->nh_grp.list, i = 0; grp != NULL; grp = grp->next, i++) {
        if (i == 0) {
            pr("\n");
            pr("Index  Count  ARP   NextHop\n");
        }
        pr("%-7u%-7u%-6u", i, grp->count, grp->idx);
        for (nh = grp->list; nh != NULL; nh = nh->next) {
            if (nh != grp->list) {
                pr("%-20s", "");
            }
            if (nh->nh.dip.type == VTSS_IP_TYPE_IPV4) {
                pr(IPV4_FORMAT "\n", IPV4_ARGS(nh->nh.dip.addr.ipv4));
            } else {
                pr(IPV6_FORMAT "/%u\n", IPV6_ARGS(nh->nh.dip.addr.ipv6), nh->nh.vid);
            }
        }
    }
    pr("\n");

    pr("Neighbours:\n");
    pr("===========\n");
    pr("Free entries: %u\n", l3->nb.free_cnt);
    type = VTSS_IP_TYPE_NONE;
    for (nb = l3->nb.list; nb != NULL; nb = nb->next) {
        if (nb->nh.dip.type != type) {
            type = nb->nh.dip.type;
            pr("\n");
            if (type == VTSS_IP_TYPE_IPV4) {
                pr("%-17sDMAC", "DIP");
            } else {
                pr("%-41s%-19sVID", "DIP", "DMAC");
            }
            pr("\n");
        }
        if (type == VTSS_IP_TYPE_IPV4) {
            VTSS_SPRINTF(buf, IPV4_FORMAT, IPV4_ARGS(nb->nh.dip.addr.ipv4));
            pr("%-17s" MAC_FORMAT "\n", buf, MAC_ARGS(nb->dmac));
        } else {
            pr(IPV6_FORMAT "  " MAC_FORMAT "  %u\n",
               IPV6_ARGS(nb->nh.dip.addr.ipv6), MAC_ARGS(nb->dmac), nb->nh.vid);
        }
    }
    pr("\n");

    pr("ARP Table:\n");
    pr("==========\n");
    pr("Rows    : %u\n", VTSS_L3_ARP_ROW_CNT);
    pr("Columns : %u\n", VTSS_L3_ARP_COL_CNT);
    pr("Total   : %u\n\n", VTSS_L3_ARP_ROW_CNT * VTSS_L3_ARP_COL_CNT);
    for (i = 0; i < VTSS_L3_ARP_ROW_CNT; i++) {
        row = &l3->arp.row[i];
        if (row->size == 0) {
            continue;
        }
        if (cnt == 0) {
            pr("Index  Size  Count  Used\n");
        }
        cnt += row->cnt;
        pr("%-7u%-6u%-7u", i * VTSS_L3_ARP_COL_CNT, row->size, row->cnt);
        for (j = 0; j < VTSS_L3_ARP_COL_CNT; j++) {
            pr(row->used[j] ? "X" : "0");
        }
        pr("\n");
    }
    if (cnt) {
        pr("\nUsed : %u\n\n", cnt);
    }

    pr("Multicast Groups:\n");
    pr("================\n");
    pr("Free count: %u\n", l3->mc_rt.free_cnt);
    pr("Group                 SIP                   MC-TBL    Src vlan  Hit\n");
    pr("------                ------                ------    --------  ---\n");
    for (mc_net = l3->mc_rt.list, cnt = 0; mc_net != NULL; mc_net = mc_net->next, cnt++) {
        if (vtss_lpm_mc_entry_get(vtss_state, mc_net->id, &counter, TRUE) != VTSS_RC_OK) {
            pr("Could not get entry\n");
        }
        if (mc_net->network.type == VTSS_IP_TYPE_IPV4) {
            VTSS_SPRINTF(buf, IPV4N_FORMAT, IPV4_ARGS(mc_net->network.addr.ipv4), 32);
            pr("%-20s  ", buf);
            if (mc_net->sip.addr.ipv4 > 0) {
                VTSS_SPRINTF(buf, IPV4N_FORMAT, IPV4_ARGS(mc_net->sip.addr.ipv4), 32);
            } else {
                VTSS_SPRINTF(buf, "don't care");
            }
        } else {
            VTSS_SPRINTF(buf, IPV6N_FORMAT, IPV6_ARGS(mc_net->network.addr.ipv6), 128);
            pr("%-45s\n", buf);
            for (j = 0, i = 0; i < 16; i++) {
                j += mc_net->sip.addr.ipv6.addr[i];
            }
            if (j > 0) {
                VTSS_SPRINTF(buf, IPV6N_FORMAT, IPV6_ARGS(mc_net->sip.addr.ipv6), 32);
            } else {
                VTSS_SPRINTF(buf, "don't care");
            }
        }
        pr("%-20s  ", buf);
        pr("%-10d", mc_net->tbl);
        mc_net->src_rleg == VTSS_VID_NULL ? pr("%-10s", "Disabled") : pr("%-10d", mc_net->tbl);
        pr("%-20d\n", counter);
    }
    pr("%d entries found\n\n", cnt);
    pr("MC-TBL:\n");
    pr("============\n");
    pr("ID   Count  RPF-VMID  Rlegs IDs\n");
    pr("---- ------ --------  --------\n");
    for (i = 0; i < VTSS_MC_TBL_CNT; i++) {
        vtss_l3_mc_tbl_t *t = &vtss_state->l3.mc_tbl[i];
        if (t->cnt == 0) {
            continue;
        }
        pr("%-5u%-7d", i, t->cnt);
        t->rpf == VTSS_L3_MC_RPF_DIS ? pr("%-10s","Disabled") : pr("%-10d",t->rpf);
        empty = 1;
        for (j = 0; j < 4; j++) {
            for (cnt = 0; cnt < 32; cnt++) {
                if ((t->rlegs[j] >> cnt) & 1) {
                    pr("%d " ,cnt + (j * 32));
                    empty = 0;
                }
            }
        }
        if (empty) {
            pr("Empty");
        }
        pr("\n");
    }
    pr("\n");

}

vtss_rc vtss_l3_inst_create(vtss_state_t *vtss_state)
{
    vtss_l3_state_t  *l3 = &vtss_state->l3;
    int              i;
    vtss_l3_nh_t     *nh;
    vtss_l3_nh_grp_t *grp;
    vtss_l3_net_t    *net;
    vtss_l3_nb_t     *nb;
    vtss_l3_mc_rt_t *mc_net;

    /* Fill up free lists */
    for (i = 0; i < VTSS_L3_NH_CNT; i++) {
        nh = &l3->nh.table[i];
        nh->next = l3->nh.free;
        l3->nh.free = nh;
        l3->nh.free_cnt++;
    }
    for (i = 0; i < VTSS_L3_NH_GRP_CNT; i++) {
        grp = &l3->nh_grp.table[i];
        grp->next = l3->nh_grp.free;
        l3->nh_grp.free = grp;
        l3->nh_grp.free_cnt++;
    }
    for (i = 0; i < VTSS_L3_NET_CNT; i++) {
        net = &l3->net.table[i];
        net->next = l3->net.free;
        l3->net.free = net;
        l3->net.free_cnt++;
    }
    for (i = 0; i < VTSS_L3_NB_CNT; i++) {
        nb = &l3->nb.table[i];
        nb->next = l3->nb.free;
        l3->nb.free = nb;
        l3->nb.free_cnt++;
    }
    for (i = 0; i < VTSS_L3_MC_RT_CNT; i++) {
        mc_net = &l3->mc_rt.table[i];
        mc_net->next = l3->mc_rt.free;
        l3->mc_rt.free = mc_net;
        l3->mc_rt.free_cnt++;
    }
    l3->net.id = 1;
    l3->mc_rt.id = 1;

    vtss_l3_integrity_update(vtss_state);
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_LAYER3 */
