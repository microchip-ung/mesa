// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_L3_STATE_H_
#define _VTSS_L3_STATE_H_

#if defined(VTSS_FEATURE_LAYER3)

// One router leg is reserved for discarding
#define VTSS_RLEG_DISCARD  VTSS_RLEG_CNT
#define VTSS_RLEG_STAT_CNT (VTSS_RLEG_CNT + 1)

/* ARP table is divided into rows with 12 columns each */
#define VTSS_L3_ARP_COL_CNT 12
#define VTSS_L3_ARP_ROW_CNT (VTSS_ARP_CNT / VTSS_L3_ARP_COL_CNT)

typedef struct {
    u8 size;
    u8 cnt;
    u8 used[VTSS_L3_ARP_COL_CNT];
} vtss_l3_arp_row_t;

typedef struct {
    vtss_l3_arp_row_t row[VTSS_L3_ARP_ROW_CNT];
} vtss_l3_arp_info_t;

typedef struct {
    vtss_ip_addr_t dip; /* Next-hop IP address */
    vtss_vid_t     vid; /* VID for IPv6 link-local address */
} vtss_l3_nh_key_t;

/* Next-hop entry */
typedef struct vtss_l3_nh_t {
    struct vtss_l3_nh_t *next; /* Next entry */
    vtss_l3_nh_key_t    nh;    /* Next-hop */
} vtss_l3_nh_t;

/* Next-hop group entry */
typedef struct vtss_l3_nh_grp_t {
    struct vtss_l3_nh_grp_t *next; /* Next entry */
    vtss_l3_nh_t            *list; /* Next-hop list */
    u32                     count; /* Reference count */
    u16                     idx;   /* ARP base index */
} vtss_l3_nh_grp_t;

/* UC Network entry */
typedef struct vtss_l3_net_t {
    struct vtss_l3_net_t *next;       /* Next entry */
    vtss_l3_nh_grp_t     *grp;        /* Next-hop group */
    vtss_ip_addr_t       network;     /* Network address */
    vtss_prefix_size_t   prefix_size; /* Prefix size */
    vtss_l3_nh_key_t     nh;          /* Next-hop, if single */
    u64                  id;          /* VCAP ID */
} vtss_l3_net_t;


/* MC route entry */
typedef struct vtss_l3_mc_rt_t {
    struct vtss_l3_mc_rt_t *next;     /* Next entry */
    vtss_ip_addr_t         network;   /* Group address */
    vtss_ip_addr_t         sip;       /* Src IP */
    u64                    id;        /* VCAP ID */
    u16                    tbl;       /* L3MC table ID */
    vtss_vid_t             src_rleg;  /* Source RLEG/VLAN */
} vtss_l3_mc_rt_t;

/* Table sizes */
#define VTSS_L3_NH_MAX     8                        /* Maximum number of next-hops per group */
#define VTSS_L3_NH_CNT     (VTSS_ARP_CNT + VTSS_L3_NH_MAX)
#define VTSS_L3_NH_GRP_CNT ((VTSS_ARP_CNT / 2) + 1) /* Each group has at least two next-hops */
#define VTSS_L3_NET_CNT    VTSS_LPM_CNT
#define VTSS_L3_NB_CNT     VTSS_LPM_CNT             /* Neighbours may be encoded directly in LPM table */
#define VTSS_L3_MC_RT_CNT  VTSS_LPM_MC_CNT

#define VTSS_L3_MC_RPF_DIS 0xFF   /* ID for disabled RPF  */

typedef struct vtss_l3_nb_t {
    struct vtss_l3_nb_t *next; /* Next entry */
    vtss_l3_nh_key_t    nh;    /* Next-hop */
    vtss_mac_t          dmac;
    vtss_l3_rleg_id_t   rleg;
} vtss_l3_nb_t;

/* Next-hop information */
typedef struct {
    vtss_l3_nh_t *free;                 /* Free list */
    u32          free_cnt;              /* Free count */
    vtss_l3_nh_t table[VTSS_L3_NH_CNT]; /* Table */
} vtss_l3_nh_info_t;

/* Next-hop group information */
typedef struct {
    vtss_l3_nh_grp_t *list;                     /* Actual list */
    vtss_l3_nh_grp_t *free;                     /* Free list */
    u32              free_cnt;                  /* Free count */
    vtss_l3_nh_grp_t table[VTSS_L3_NH_GRP_CNT]; /* Table */
} vtss_l3_nh_grp_info_t;

/* Network information */
typedef struct {
    vtss_l3_net_t *list;                  /* Actual list */
    vtss_l3_net_t *free;                  /* Free list */
    u32           free_cnt;               /* Free count */
    vtss_l3_net_t table[VTSS_L3_NET_CNT]; /* Table */
    u64           id;                     /* Next free VCAP ID */
} vtss_l3_net_info_t;

/* Neighbour information */
typedef struct {
    vtss_l3_nb_t *list;                 /* Actual list */
    vtss_l3_nb_t *free;                 /* Free list */
    u32          free_cnt;              /* Free count */
    vtss_l3_nb_t table[VTSS_L3_NB_CNT]; /* Table */
} vtss_l3_nb_info_t;

/* MC information */
typedef struct {
    vtss_l3_mc_rt_t *list;                   /* Actual list */
    vtss_l3_mc_rt_t *free;                   /* Free list */
    u32             free_cnt;                /* Free count */
    vtss_l3_mc_rt_t table[VTSS_L3_MC_RT_CNT];  /* L3 MC Table */
    u64             id;                      /* Next free VCAP ID */
} vtss_l3_mc_rt_info_t;

/* L3MC Table */
typedef struct {
    u32             rlegs[4]; /* Router leg bit mask */
    u16             cnt;      /* Reference count */
    u8              rpf;      /* RPF ingress rt-leg  */
} vtss_l3_mc_tbl_t;

typedef struct {
    vtss_l3_counters_t interface_shadow_counter[VTSS_RLEG_STAT_CNT];
    vtss_l3_counters_t interface_counter[VTSS_RLEG_STAT_CNT];
    u32                rleg; /* Next router leg to poll */
} vtss_l3_statistics_t;

typedef struct {
    /* CIL function pointers */
    vtss_rc (* rleg_counters_get)(struct vtss_state_s *vtss_state,
                                  const vtss_l3_rleg_id_t);
    vtss_rc (* rleg_counters_reset)(struct vtss_state_s *vtss_state);
    vtss_rc (* common_set)(struct vtss_state_s *vtss_state,
                              const vtss_l3_common_conf_t * const);
    vtss_rc (* rleg_set)(struct vtss_state_s *vtss_state,
                            const vtss_l3_rleg_id_t, const vtss_l3_rleg_conf_t * const);
    vtss_rc (* vlan_set)(struct vtss_state_s *vtss_state,
                         const vtss_l3_rleg_id_t, const vtss_vid_t, const BOOL);
    vtss_rc (* rt_add)(struct vtss_state_s *vtss_state,
                       vtss_l3_net_t *net, vtss_l3_nb_t *nb, u32 cnt);
    vtss_rc (* rt_del)(struct vtss_state_s *vtss_state,
                       vtss_l3_net_t *net);
    vtss_rc (* mc_rt_add)(struct vtss_state_s *vtss_state,
                          vtss_l3_mc_rt_t *net);
    vtss_rc (* mc_rt_del)(struct vtss_state_s *vtss_state,
                          vtss_l3_mc_rt_t *net);
    vtss_rc (* mc_rt_rleg_add)(struct vtss_state_s *vtss_state, vtss_l3_mc_rt_t *net);
    vtss_rc (* mc_rt_rleg_del)(struct vtss_state_s *vtss_state, vtss_l3_mc_rt_t *net);
    vtss_rc (* arp_set)(struct vtss_state_s *vtss_state,
                        u32 idx, vtss_l3_nb_t *nb);
    vtss_rc (* debug_sticky_clear)(struct vtss_state_s *vtss_state);

    /* Configuration/state */
    u32                        checksum;
    vtss_l3_common_conf_t      common;
    vtss_l3_rleg_conf_t        rleg_conf[VTSS_RLEG_CNT];
    vtss_l3_statistics_t       statistics;
    vtss_l3_nh_info_t          nh;
    vtss_l3_nh_grp_info_t      nh_grp;
    vtss_l3_net_info_t         net;
    vtss_l3_nb_info_t          nb;
    vtss_l3_arp_info_t         arp;
    vtss_l3_mc_rt_info_t       mc_rt;
    vtss_l3_mc_tbl_t           mc_tbl[VTSS_MC_TBL_CNT];
} vtss_l3_state_t;

vtss_rc vtss_l3_inst_create(struct vtss_state_s *vtss_state);
void vtss_l3_integrity_update(struct vtss_state_s *vtss_state);
void vtss_l3_integrity_check(const struct vtss_state_s *vtss_state, const char *file, unsigned line);
void vtss_debug_print_l3(struct vtss_state_s *vtss_state,
                         const vtss_debug_printf_t pr,
                         const vtss_debug_info_t   *const info);

#endif /* VTSS_FEATURE_LAYER3 */

#endif /* _VTSS_L3_STATE_H_ */
