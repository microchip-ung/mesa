// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_L2_STATE_H_
#define _VTSS_L2_STATE_H_

#if defined(VTSS_FEATURE_LAYER2)

/* Port forwarding state */
#define VTSS_PORT_RX_FORWARDING(fwd_state) (fwd_state == VTSS_PORT_FORWARD_ENABLED || fwd_state == VTSS_PORT_FORWARD_INGRESS ? 1 : 0)
#define VTSS_PORT_TX_FORWARDING(fwd_state) (fwd_state == VTSS_PORT_FORWARD_ENABLED || fwd_state == VTSS_PORT_FORWARD_EGRESS ? 1 : 0)

/* PVLAN entry */
typedef struct {
    BOOL member[VTSS_PORT_ARRAY_SIZE]; /* Member ports */
} vtss_pvlan_entry_t;

/* PGID entry */
typedef struct {
    BOOL member[VTSS_PORT_ARRAY_SIZE]; /* Egress ports */
    BOOL resv;                         /* Fixed reservation */
    u32  references;                   /* Number references to entry */
    BOOL cpu_copy;                     /* CPU copy */
    vtss_packet_rx_queue_t cpu_queue;  /* CPU queue */
} vtss_pgid_entry_t;

/* Number of destination masks */

#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
#define VTSS_PGID_LUTON26 64
#undef VTSS_PGIDS
#define VTSS_PGIDS        VTSS_PGID_LUTON26
#endif

#if defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_PGID_JAGUAR_2 1077
#undef VTSS_PGIDS
#define VTSS_PGIDS VTSS_PGID_JAGUAR_2
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_ARCH_SPARX5)
#define VTSS_PGID_FA (2048 + 65)
#undef VTSS_PGIDS
#define VTSS_PGIDS VTSS_PGID_FA
#endif /* VTSS_ARCH_SPARX5 */

/* Pseudo PGID for IPv4/IPv6 MC */
#define VTSS_PGID_NONE VTSS_PGIDS

#define VTSS_GLAG_NO_NONE 0xffffffff

/* Size of lookup page and pointer array */
#define VTSS_MAC_PAGE_SIZE 128
#define VTSS_MAC_PTR_SIZE  (VTSS_MAC_ADDRS/VTSS_MAC_PAGE_SIZE)

/* MAC address table users */
#define VTSS_MAC_USER_NONE 0 /* Normal entries added by the application */
#define VTSS_MAC_USER_SSM  1 /* Internal entries added for SSM purposes */
#define VTSS_MAC_USER_ASM  2 /* Internal entries added for ASM purposes */
typedef u8 vtss_mac_user_t;

/* MAC address entry flags */
#define VTSS_MAC_FLAG_ADDED 0x01 /* Entry added flag used for warm start synchronization */

/* MAC address table for get next operations */
typedef struct vtss_mac_entry_t {
    struct vtss_mac_entry_t *next;  /* Next in list */
    u32                     mach;  /* VID and 16 MSB of MAC */
    u32                     macl;  /* 32 LSB of MAC */
    u8                      member[VTSS_PORT_BF_SIZE];
    BOOL                    cpu_copy;
    BOOL                    cpu_copy_smac;
    u8                      flags;
    vtss_packet_rx_queue_t  cpu_queue;
    vtss_mac_user_t         user;
} vtss_mac_entry_t;

/* IPv4 and IPv6 multicast address */
#define VTSS_MAC_IPV4_MC(mac) (mac[0] == 0x01 && mac[1] == 0x00 && mac[2] == 0x5e && (mac[3] & 0x80) == 0x00)
#define VTSS_MAC_IPV6_MC(mac) (mac[0] == 0x33 && mac[1] == 0x33)
#define VTSS_MAC_BC(mac)      (mac[0] == 0xff && mac[1] == 0xff && mac[2] == 0xff && mac[3] == 0xff && mac[4] == 0xff && mac[5] == 0xff)

void vtss_mach_macl_get(const vtss_vid_mac_t *vid_mac, u32 *mach, u32 *macl);
void vtss_mach_macl_set(vtss_vid_mac_t *vid_mac, u32 mach, u32 macl);

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
#define VTSS_MAC_INDEX_VID_CNT 4
#if defined(VTSS_ARCH_LAN966X_FPGA)
#define VTSS_MAC_INDEX_CNT     512
#else
#define VTSS_MAC_INDEX_CNT     2048
#endif

/* MAC addresses for a VLAN in the index table */
typedef struct {
    vtss_vid_t vid;
    u16        cnt;
    u8         valid[VTSS_BF_SIZE(VTSS_MAC_INDEX_CNT)];
} vtss_mac_vlan_entry_t;

typedef struct {
    u32                   idx_add; // Index for add operation
    u32                   idx_get; // Index for get operation
    u32                   oui;
    u8                    cnt; // Number of VID indices in list
    u8                    vidx[VTSS_MAC_INDEX_VID_CNT];
    vtss_mac_vlan_entry_t e[VTSS_MAC_INDEX_VID_CNT];
} vtss_mac_index_table_t;
#endif

/* Counter for number of enabled rings with port in discarding state */
#if (VTSS_ERPIS > 255)
typedef u16 vtss_erps_counter_t;
#else
typedef u8 vtss_erps_counter_t;
#endif

/* For IPMC SSM, VLAN ID may be allocated for IPv4/IPv6 FID */
#define IPMC_USED_NONE 0x00
#define IPMC_USED_IPV4 0x01
#define IPMC_USED_IPV6 0x02

#if defined(VTSS_ARCH_SERVAL_T)
#define VSI_USED_FOR_OAM 127    /* This VSI is reserved for OAM in order to fix problem with Port domain OAM replies that are not forwarded to port unless member of VLAN */
#define VTSS_VSI_CNT 126        /* This is the number of VSI that can be allocated (1-VTSS_VSI_CNT) */
#else
#define VSI_USED_FOR_OAM 1023   /* This VSI is reserved for OAM in order to fix problem with Port domain OAM replies that are not forwarded to port unless member of VLAN */
#define VTSS_VSI_CNT 1022        /* This is the number of VSI that can be allocated (1-VTSS_VSI_CNT) */
#endif

/* VSI entry */
typedef struct vtss_vsi_entry_t {
    struct vtss_vsi_entry_t *next;   /* next in list */
    u16                     vsi;     /* VSI value */
} vtss_vsi_entry_t;

#if defined(VTSS_ARCH_JAGUAR_2)
typedef struct {
    u32               max_count;           /* Maximum number of VSI */
    u32               count;               /* Actual number of allocated VSI */
    vtss_vsi_entry_t  *free;               /* List of free entries */
    vtss_vsi_entry_t  table[VTSS_VSI_CNT]; /* Table of physical VSI entries */
} vtss_vsi_info_t;
#endif /* VTSS_ARCH_JAGUAR_2 */

#define VLAN_FLAGS_ENABLED  0x01
#define VLAN_FLAGS_UPDATE   0x02
#define VLAN_FLAGS_ISOLATED 0x04
#define VLAN_FLAGS_LEARN    0x08
#define VLAN_FLAGS_FLOOD    0x10
#define VLAN_FLAGS_MIRROR   0x20
#define VLAN_FLAGS_FILTER   0x40

/* VLAN entry */
typedef struct {
    u8          flags;
    u8          member[VTSS_PORT_BF_SIZE]; /* Port members */
#if defined(VTSS_FEATURE_HW_PROT)
    u8          hw_prot_disable[VTSS_PORT_BF_SIZE]; /* Inactive HW protection ports */
#endif /* VTSS_FEATURE_HW_PROT */
#if defined(VTSS_FEATURE_VCAP)
    u8          tx_tag[VTSS_PORT_ARRAY_SIZE]; /* Tx tagging */
#endif
#if defined(VTSS_FEATURE_L2_ERPS)
    vtss_erps_counter_t erps_discard_cnt[VTSS_PORT_ARRAY_SIZE]; /* ERPS discard counter */
#endif
#if defined(VTSS_FEATURE_L2_MSTP)
    vtss_msti_t msti;                      /* MSTP instance */
#endif
#if defined(VTSS_ARCH_LUTON26)
    BOOL        ipmc_used;                 /* In use for SSM */
#endif
#if defined(VTSS_ARCH_JAGUAR_2)
    BOOL        vsi_enable;                /* VSI enable */
    BOOL        vsi_vlan_forward_disable;  /* If VSI is enabled this decides if VLAN forwarding is disabled */
    vtss_vsi_entry_t  *vsi;                /* VSI entry */
    BOOL        mgmt;                      /* VLAN management flag */
#endif
#if defined(VTSS_FEATURE_LAYER3)
    BOOL        rl_enable;                 /* RL enable */
    u16         rl_id;                     /* RL ID */
#endif
#if defined(VTSS_FEATURE_VLAN_SVL)
    vtss_vid_t  fid;
#endif
} vtss_vlan_entry_t;

/* MSTP entry */
typedef struct {
    vtss_stp_state_t state[VTSS_PORT_ARRAY_SIZE]; /* MSTP state */
} vtss_mstp_entry_t;

/* ERPS entry */
typedef struct {
    u8   vlan_member[VTSS_BF_SIZE(VTSS_VIDS)]; /* VLAN members */
    u8   port_member[VTSS_PORT_BF_SIZE];       /* Forwarding port members */
} vtss_erps_entry_t;

/* Port protection */
typedef struct {
    vtss_eps_port_conf_t conf;     /* Configuration */
    vtss_eps_selector_t  selector; /* Selector */
} vtss_port_eps_t;

#if defined(VTSS_FEATURE_VCAP)
/* VLAN Translation Group entry (Group to VLAN Translation mappings) */
typedef struct vtss_vlan_trans_grp2vlan_entry_t {
    struct vtss_vlan_trans_grp2vlan_entry_t     *next;                             /* Next in list                      */
    vtss_vlan_trans_grp2vlan_conf_t             conf;                              /* Group to VLAN configuration       */
} vtss_vlan_trans_grp2vlan_entry_t;

/* VLAN Translation Group lists - used and free */
typedef struct {
    vtss_vlan_trans_grp2vlan_entry_t  *used;                                       /* used list                         */
    vtss_vlan_trans_grp2vlan_entry_t  *free;                                       /* free list                         */
    vtss_vlan_trans_grp2vlan_entry_t  trans_list[VTSS_VLAN_TRANS_MAX_CNT];         /* Actual storage for list members   */
} vtss_vlan_trans_grp2vlan_t;

/* VLAN Translation Port entry (Ports to Group mappings) */
typedef struct vtss_vlan_trans_port2grp_entry_t {
    struct vtss_vlan_trans_port2grp_entry_t     *next;                             /* Next in list                      */
    vtss_vlan_trans_port2grp_conf_t             conf;                              /* Port to Group configuration       */
} vtss_vlan_trans_port2grp_entry_t;

/* VLAN Translation Port lists - used and free */
typedef struct {
    vtss_vlan_trans_port2grp_entry_t   *used;                                      /* used list                         */
    vtss_vlan_trans_port2grp_entry_t   *free;                                      /* free list                         */
    vtss_vlan_trans_port2grp_entry_t   port_list[VTSS_VLAN_TRANS_GROUP_MAX_CNT];   /* Actual storage for list members   */
} vtss_vlan_trans_port2grp_t;
#endif

typedef struct {
    vtss_chip_counter_t frames;                         /**< Frame counters */
    vtss_chip_counter_t bytes;                          /**< Byte counters */
} vtss_chip_counter_pair_t;

typedef struct {
    vtss_chip_counter_pair_t rx_green;   /**< Rx green frames/bytes */
    vtss_chip_counter_pair_t rx_yellow;  /**< Rx yellow frames/bytes */
    vtss_chip_counter_pair_t rx_red;     /**< Rx red frames/bytes */
    vtss_chip_counter_pair_t rx_discard; /**< Rx discarded frames/bytes */
    vtss_chip_counter_pair_t tx_discard; /**< Tx discarded frames/bytes */
    vtss_chip_counter_pair_t tx_green;   /**< Tx green frames/bytes */
    vtss_chip_counter_pair_t tx_yellow;  /**< Tx yellow frames/bytes */
#if defined(VTSS_ARCH_LAN966X)
    // PSFP counters
    vtss_chip_counter_t      rx_match;
    vtss_chip_counter_t      rx_gate_discard;
    vtss_chip_counter_t      rx_sdu_discard;
#endif
} vtss_sdx_counters_t;

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
typedef struct {
    vtss_chip_counter_pair_t rx_unicast;   /**< Unicast packets and bytes counted on this VLAN */
    vtss_chip_counter_pair_t rx_multicast; /**< Multicast packets and bytes counted on this VLAN */
    vtss_chip_counter_pair_t rx_broadcast; /**< Broadcast packets and bytes counted on this VLAN */
} vtss_vlan_chip_counters_t;

/* VLAN Counter information */
typedef struct {
    u32                         poll_idx;               /* Counter polling index */
    vtss_vlan_chip_counters_t   counters[VTSS_VIDS];    /* Counters for all the VLANs */
} vtss_vlan_counter_info_t;
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

#if defined(VTSS_FEATURE_FRER)
typedef struct {
    vtss_chip_counter_t out_of_order_packets;
    vtss_chip_counter_t rogue_packets;
    vtss_chip_counter_t passed_packets;
    vtss_chip_counter_t discarded_packets;
    vtss_chip_counter_t lost_packets;
    vtss_chip_counter_t tagless_packets;
    vtss_chip_counter_t resets;
} vtss_frer_chip_counters_t;
#endif

#if defined(VTSS_FEATURE_PSFP)

// PSFP Gate Control List maximum length
#define VTSS_PSFP_GCL_CNT 4

typedef struct {
    u32             gcl_length;
    vtss_psfp_gce_t gce[VTSS_PSFP_GCL_CNT];
} vtss_psfp_gcl_t;

typedef struct {
    vtss_psfp_gate_conf_t   gate[VTSS_PSFP_GATE_CNT];
    vtss_psfp_gcl_t         admin_gcl[VTSS_PSFP_GATE_CNT];
    vtss_psfp_gcl_t         oper_gcl[VTSS_PSFP_GATE_CNT];
    vtss_psfp_gcl_conf_t    oper_conf[VTSS_PSFP_GATE_CNT];
    vtss_psfp_filter_conf_t filter[VTSS_PSFP_FILTER_CNT];
} vtss_psfp_state_t;
#endif

#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
/* Number of sources and destinations */
#if defined(VTSS_ARCH_LUTON26)
#define VTSS_IPMC_SRC_MAX 256
#define VTSS_IPMC_DST_MAX 2048
#else
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
#define VTSS_IPMC_DST_MAX (2*64)  /* Half IS2 rules */
#elif defined(VTSS_ARCH_SERVAL_T)
#define VTSS_IPMC_DST_MAX (4*6*64) /* Quarter IS2 rules in VCAP_SUPER */
#elif defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_IPMC_DST_MAX (4*4*256) /* JR2: Quarter IS2 rules in VCAP_SUPER */
#else
#define VTSS_IPMC_DST_MAX (4*5*256) /* FA: Quarter IS2 rules in VCAP_SUPER */
#endif
#define VTSS_IPMC_SRC_MAX VTSS_IPMC_DST_MAX
#endif

typedef union {
    vtss_ipv4_t ipv4; /* IPv4 address */
    vtss_ipv6_t ipv6; /* IPv6 address */
} vtss_ip_addr_internal_t;

/* IPMC source data */
typedef struct {
    vtss_ip_addr_internal_t sip; /* Source IP address */
    vtss_vid_t              vid; /* VLAN ID */
    vtss_vid_t              fid; /* FID allocated for this source (if SIP non-zero) */
    BOOL                    ssm; /* SSM indication (zero SIP) */
} vtss_ipmc_src_data_t;

/* IPMC destination data */
typedef struct {
    vtss_ip_addr_internal_t dip;                       /* Destination IP address */
    u8                      member[VTSS_PORT_BF_SIZE]; /* Port members */
    u64                     id;                        /* VCAP ID */
} vtss_ipmc_dst_data_t;

/* IPMC source and destination data */
typedef struct {
    BOOL                 ipv6;    /* IPv4/IPv6 indication */
    BOOL                 src_add; /* Source add flag */
    BOOL                 src_del; /* Source delete flag */
    BOOL                 dst_add; /* destination add flag */
    BOOL                 dst_del; /* destionation delete flag */
    vtss_ipmc_src_data_t src;
    vtss_ipmc_dst_data_t dst;
    u64                  id_next; /* Next VCAP ID for add operation */
} vtss_ipmc_data_t;

/* IPMC destination entry */
typedef struct vtss_ipmc_dst_t {
    struct vtss_ipmc_dst_t *next; /* Next destination entry */
    vtss_ipmc_dst_data_t   data;  /* Entry data */
    BOOL                   add;   /* Internal add flag */
} vtss_ipmc_dst_t;

/* IPMC source entry */
typedef struct vtss_ipmc_src_t {
    struct vtss_ipmc_src_t *next;  /* Next source entry */
    vtss_ipmc_dst_t        *dest;  /* Destination list */
    vtss_ipmc_src_data_t   data;   /* Entry data */
} vtss_ipmc_src_t;

/* IPMC object */
typedef struct {
    u32             src_count;    /* Actual number of sources */
    u32             src_max;      /* Maximum number of sources */
    u32             dst_count;    /* Actual number of destinations */
    u32             dst_max;      /* Maximum number of destinations */
    vtss_ipmc_src_t *src_used[2]; /* Used IPv4(0)/IPv6(1) source entries */
    vtss_ipmc_src_t *src_free;    /* Free source entries */
    vtss_ipmc_dst_t *dst_free;    /* Free destination entries */
    const char      *name;        /* IPMC name for debugging */
    u64             id;           /* Next free VCAP ID */
} vtss_ipmc_obj_t;

typedef struct {
    vtss_ipmc_obj_t obj;                          /* Object */
    vtss_ipmc_src_t src_table[VTSS_IPMC_SRC_MAX]; /* Source table */
    vtss_ipmc_dst_t dst_table[VTSS_IPMC_DST_MAX]; /* Destination table */
} vtss_ipmc_info_t;

typedef enum {
    VTSS_IPMC_CMD_CHECK, /* Check resources */
    VTSS_IPMC_CMD_ADD,   /* Add resources */
    VTSS_IPMC_CMD_DEL,   /* Delete resources */
} vtss_ipmc_cmd_t;
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */

#if defined(VTSS_SDX_CNT)
/* SDX entry */
typedef struct vtss_sdx_entry_t {
    struct vtss_sdx_entry_t *next;    /* next in list */
    vtss_port_no_t          port_no;  /* UNI/NNI port number */
    u16                     id;       /* ID number, used for E-tree leaf/root indication */
    u16                     sdx;      /* SDX value */
    u16                     pol_idx;  /* Policer index */
    u16                     stat_idx; /* Statistics index */
    u8                      pol_cnt;  /* Policer count */
    u8                      stat_cnt; /* Statistics count */
    u16                     ms_idx;   /* Member stream index */
    vtss_iflow_conf_t       conf;     /* Ingress flow configuration */
} vtss_sdx_entry_t;

typedef struct {
    BOOL              used; /* Used indication */
    vtss_eflow_conf_t conf; /* Egress flow configuration */
} vtss_eflow_entry_t;

/* Table and free list for ISDX/ESDX */
typedef struct {
    u32              count;               /* Actual number of rules */
    vtss_sdx_entry_t *free;               /* List of free entries */
    vtss_sdx_entry_t table[VTSS_SDX_CNT]; /* Table of entries */
} vtss_sdx_list_t;

#if defined(VTSS_EVC_STAT_CNT)
typedef struct {
    u16 idx; /* Ingress index */
    u16 edx; /* Egress index */
} vtss_stat_idx_t;

/* Number of policer/SDX rows, each with 8 values */
#define VTSS_EVC_POL_ROW_CNT  (VTSS_EVC_POL_CNT / 8)
#define VTSS_EVC_STAT_ROW_CNT (VTSS_EVC_STAT_CNT / 8)

typedef struct {
    BOOL used; /* Used/free indication */
    u16  *ref; /* Reference to allocated value */
} vtss_xcol_entry_t;

typedef struct {
    u8                size;   /* Entry size, 1/2/4/8 or 0 (free) */
    u8                count;  /* Number of used columns */
    vtss_xcol_entry_t col[8]; /* Columns */
} vtss_xrow_entry_t;

typedef struct {
    u32               max_count;         /* Maximum number of entries */
    u32               count;             /* Actual number of allocated entries */
    u32               count_size[8 + 1]; /* Actual number per size (0-8) */
    const             char *name;        /* Name for debugging */
    vtss_rc (* move)(struct vtss_state_s *vtss_state, u16 idx_old, u16 idx_new, u16 count);
    vtss_rc (* clear)(struct vtss_state_s *vtss_state, u16 idx);
    vtss_xrow_entry_t *row;              /* Pointer to first row */
} vtss_xrow_header_t;

typedef struct {
    vtss_xrow_header_t hdr;
    vtss_xrow_entry_t  row[VTSS_EVC_POL_ROW_CNT];
} vtss_evc_pol_table_t;

typedef struct {
    vtss_xrow_header_t hdr;
    vtss_xrow_entry_t  row[VTSS_EVC_STAT_ROW_CNT];
} vtss_evc_stat_table_t;

typedef struct {
    u16 idx; /* Allocated idx */
    u8  cnt; /* Number of classes, zero means unused */
    u16 sdx; /* Associated ISDX (LAN966X) */
} vtss_xstat_entry_t;

typedef struct {
    vtss_xstat_entry_t table[VTSS_EVC_STAT_CNT];
} vtss_xstat_table_t;

typedef struct {
    u16 idx; /* Allocated idx */
    u8  cnt; /* Number of classes, zero means unused */
} vtss_xpol_entry_t;

typedef struct {
    vtss_xpol_entry_t table[VTSS_EVC_POL_CNT];
} vtss_xpol_table_t;
#endif

#if defined(VTSS_FEATURE_FRER)
typedef struct {
    vtss_xrow_header_t hdr;
    vtss_xrow_entry_t  row[VTSS_MSTREAM_CNT/8];
} vtss_ms_table_t;

typedef struct {
    u16 idx; /* Allocated idx */
    u8  cnt; /* Number of classes, zero means unused */
    u8  port_list[VTSS_PORT_BF_SIZE];
} vtss_xms_entry_t;

typedef struct {
    vtss_xms_entry_t table[VTSS_MSTREAM_CNT];
} vtss_xms_table_t;
#endif

#define VTSS_EVC_VOE_IDX_NONE 0xFFFF
#define VTSS_EVC_MIP_IDX_NONE 0xFFFF

/* SDX information */
typedef struct {
    u32                 max_count; /* Maximum number of rules */
    u32                 poll_idx;  /* Counter polling index */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    vtss_sdx_counters_t sdx_table[VTSS_EVC_STAT_CNT];
#else
    vtss_sdx_counters_t sdx_table[VTSS_SDX_CNT + 1]; /* Allow 1-based indexing (index zero is unused) */
#endif
    vtss_sdx_list_t     isdx;      /* ISDX list */
    vtss_sdx_list_t     esdx;      /* ESDX list */
    vtss_sdx_entry_t    *iflow;    /* List of allocated ingress flow entries */
} vtss_sdx_info_t;
#endif /* VTSS_SDX_CNT */

#if defined(VTSS_FEATURE_RCL)
#define VTSS_RCL_VID_CNT 8

typedef struct {
    BOOL                enable;
    vtss_vid_t          vid;
    vtss_rcl_vid_conf_t conf;
} vtss_rcl_vid_entry_t;
#endif

typedef struct {
    /* CIL function pointers */
    vtss_rc (* mac_table_add)(struct vtss_state_s *vtss_state,
                              const vtss_mac_table_entry_t *const entry, u32 pgid);
    vtss_rc (* mac_table_del)(struct vtss_state_s *vtss_state,
                              const vtss_vid_mac_t *const vid_mac);
    vtss_rc (* mac_table_get)(struct vtss_state_s *vtss_state,
                              vtss_mac_table_entry_t *const entry, u32 *pgid);
    vtss_rc (* mac_table_get_next)(struct vtss_state_s *vtss_state,
                                   vtss_mac_table_entry_t *const entry, u32 *pgid);
    vtss_rc (* mac_table_age_time_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* mac_table_age)(struct vtss_state_s *vtss_state,
                              BOOL             pgid_age,
                              u32              pgid,
                              BOOL             vid_age,
                              const vtss_vid_t vid);
    vtss_rc (* mac_table_status_get)(struct vtss_state_s *vtss_state,
                                     vtss_mac_table_status_t *const status);
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    vtss_rc (* mac_index_update)(struct vtss_state_s *vtss_state);
#endif
    vtss_rc (* learn_port_mode_set)(struct vtss_state_s *vtss_state,
                                    const vtss_port_no_t port_no);
    vtss_rc (* learn_state_set)(struct vtss_state_s *vtss_state,
                                const BOOL member[VTSS_PORT_ARRAY_SIZE]);
#if defined(VTSS_FEATURE_L2_MSTP)
    vtss_rc (* mstp_vlan_msti_set)(struct vtss_state_s *vtss_state,
                                   const vtss_vid_t vid);
    vtss_rc (* mstp_state_set)(struct vtss_state_s *vtss_state,
                               const vtss_port_no_t port_no,
                               const vtss_msti_t    msti);
#endif
#if defined(VTSS_FEATURE_L2_ERPS)
    vtss_rc (* erps_vlan_member_set)(struct vtss_state_s *vtss_state,
                                     const vtss_erpi_t erpi,
                                     const vtss_vid_t  vid);
    vtss_rc (* erps_port_state_set)(struct vtss_state_s *vtss_state,
                                    const vtss_erpi_t    erpi,
                                    const vtss_port_no_t port_no);
#endif
    vtss_rc (* vlan_conf_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* vlan_port_conf_set)(struct vtss_state_s *vtss_state,
                                   const vtss_port_no_t port_no);
    vtss_rc (* vlan_port_conf_update)(struct vtss_state_s *vtss_state,
                                      vtss_port_no_t port_no, vtss_vlan_port_conf_t *conf);
    vtss_rc (* vlan_port_members_set)(struct vtss_state_s *vtss_state,
                                      const vtss_vid_t vid);
    vtss_rc (* vlan_tx_tag_set)(struct vtss_state_s *vtss_state,
                                const vtss_vid_t vid,
                                const vtss_vlan_tx_tag_t tx_tag[VTSS_PORT_ARRAY_SIZE]);
    vtss_rc (* vlan_mask_update)(struct vtss_state_s *vtss_state,
                                 vtss_vid_t vid, BOOL member[VTSS_PORT_ARRAY_SIZE]);
    vtss_rc (* isolated_vlan_set)(struct vtss_state_s *vtss_state,
                                  const vtss_vid_t vid);
    vtss_rc (* isolated_port_members_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* aggr_mode_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* mirror_port_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* mirror_ingress_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* mirror_egress_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* mirror_cpu_ingress_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* mirror_cpu_egress_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* eps_port_set)(struct vtss_state_s *vtss_state,
                             const vtss_port_no_t port_no);
    vtss_rc (* flood_conf_set)(struct vtss_state_s *vtss_state);
#if defined(VTSS_FEATURE_IPV4_MC_SIP)
    vtss_rc (* ipv4_mc_add)(struct vtss_state_s *vtss_state,
                            vtss_vid_t vid, vtss_ip_t sip, vtss_ip_t dip,
                            const BOOL member[VTSS_PORT_ARRAY_SIZE]);
    vtss_rc (* ipv4_mc_del)(struct vtss_state_s *vtss_state,
                            vtss_vid_t vid, vtss_ip_t sip, vtss_ip_t dip);
#endif /* VTSS_FEATURE_IPV4_MC_SIP */
#if defined(VTSS_FEATURE_IPV6_MC_SIP)
    vtss_rc (* ipv6_mc_add)(struct vtss_state_s *vtss_state,
                            vtss_vid_t vid, vtss_ipv6_t sip, vtss_ipv6_t dip,
                            const BOOL member[VTSS_PORT_ARRAY_SIZE]);
    vtss_rc (* ipv6_mc_del)(struct vtss_state_s *vtss_state,
                            vtss_vid_t vid, vtss_ipv6_t sip, vtss_ipv6_t dip);
#endif /* VTSS_FEATURE_IPV6_MC_SIP */
#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
    vtss_rc (* ip_mc_update)(struct vtss_state_s *vtss_state,
                             vtss_ipmc_data_t *ipmc, vtss_ipmc_cmd_t cmd);
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */
    vtss_rc (* src_table_write)(struct vtss_state_s *vtss_state,
                                vtss_port_no_t port_no, BOOL member[VTSS_PORT_ARRAY_SIZE]);
    vtss_rc (* pgid_table_write)(struct vtss_state_s *vtss_state,
                                 u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE]);
    vtss_rc (* aggr_table_write)(struct vtss_state_s *vtss_state,
                                 u32 ac, BOOL member[VTSS_PORT_ARRAY_SIZE]);
    vtss_rc (* pmap_table_write)(struct vtss_state_s *vtss_state,
                                 vtss_port_no_t port_no, vtss_port_no_t l_port_no);
    vtss_rc (*sflow_port_conf_set)(struct vtss_state_s *vtss_state,
                                   vtss_port_no_t port_no, const vtss_sflow_port_conf_t *const conf);
    vtss_rc (*sflow_sampling_rate_convert)(struct vtss_state_s *const state, const BOOL power2, const u32 rate_in, u32 *const rate_out);

#if defined(VTSS_FEATURE_VCAP)
    vtss_rc (* vcl_port_conf_set)(struct vtss_state_s *vtss_state,
                                  const vtss_port_no_t port_no);
    vtss_rc (* vce_add)(struct vtss_state_s *vtss_state,
                        const vtss_vce_id_t  vce_id,
                        const vtss_vce_t     *const vce);
    vtss_rc (* vce_del)(struct vtss_state_s *vtss_state,
                        const vtss_vce_id_t  vce_id);
    vtss_rc (* vlan_trans_group_add) (struct vtss_state_s *vtss_state,
                                      const vtss_vlan_trans_grp2vlan_conf_t *conf);
    vtss_rc (* vlan_trans_group_del) (struct vtss_state_s *vtss_state,
                                      const vtss_vlan_trans_grp2vlan_conf_t *conf);
    vtss_rc (* vlan_trans_group_get) (struct vtss_state_s *vtss_state,
                                      vtss_vlan_trans_grp2vlan_conf_t *conf, BOOL next);
    vtss_rc (* vlan_trans_port_conf_set) (struct vtss_state_s *vtss_state,
                                          const vtss_vlan_trans_port2grp_conf_t *conf);
    vtss_rc (* vlan_trans_port_conf_get) (struct vtss_state_s *vtss_state,
                                          vtss_vlan_trans_port2grp_conf_t *conf, BOOL next);
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    vtss_rc (* vcap_port_conf_set)(struct vtss_state_s *vtss_state,
                                   const vtss_port_no_t port_no);
#endif
#endif // VTSS_FEATURE_VCAP
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    vtss_rc (* vlan_counters_get)(struct vtss_state_s *vtss_state,
                                  const vtss_vid_t          vid,
                                  vtss_vlan_counters_t      *const counters);
    vtss_rc (* vlan_counters_clear)(struct vtss_state_s *vtss_state,
                                    const vtss_vid_t        vid);
#endif /* VTSS_FEATURE_VLAN_COUNTERS */
#if defined(VTSS_FEATURE_XFLOW)
    vtss_rc (* iflow_conf_set)(struct vtss_state_s *vtss_state,
                               const vtss_iflow_id_t   id);
#endif
#if defined(VTSS_FEATURE_XSTAT)
    vtss_rc (* icnt_get)(struct vtss_state_s *vtss_state,
                         u16 idx, vtss_ingress_counters_t *counters);
    vtss_rc (* ecnt_get)(struct vtss_state_s *vtss_state,
                         u16 idx, vtss_egress_counters_t *counters);
#endif
#if defined(VTSS_EVC_STAT_CNT)
    /* Functions needed for alloc/free of policers/statistics */
    vtss_rc (* policer_update)(struct vtss_state_s *vtss_state,
                               const u16 idx);
    vtss_rc (* counters_update)(struct vtss_state_s *vtss_state,
                                vtss_stat_idx_t *sidx,
                                BOOL clear);
    vtss_rc (* isdx_update)(struct vtss_state_s *vtss_state,
                            vtss_sdx_entry_t *sdx);
#if defined(VTSS_FEATURE_PSFP)
    vtss_rc (* policer_status_get)(struct vtss_state_s *vtss_state,
                                   const u16 idx,
                                   vtss_dlb_policer_status_t *const status);
#endif /* VTSS_FEATURE_PSFP */
#endif
#if defined(VTSS_FEATURE_FRER)
    vtss_rc (* cstream_conf_set)(struct vtss_state_s *vtss_state,
                                 const vtss_frer_cstream_id_t id);
    vtss_rc (* mstream_conf_set)(struct vtss_state_s *vtss_state,
                                 const u16 idx);
    vtss_rc (* cstream_cnt_get)(struct vtss_state_s *vtss_state,
                                const vtss_frer_cstream_id_t id,
                                vtss_frer_counters_t *counters);
    vtss_rc (* mstream_cnt_get)(struct vtss_state_s *vtss_state,
                                const u16 idx,
                                vtss_frer_counters_t *counters);
#endif
#if defined(VTSS_FEATURE_PSFP)
    vtss_rc (* psfp_gate_conf_set)(struct vtss_state_s *vtss_state,
                                   const vtss_psfp_gate_id_t id);
    vtss_rc (* psfp_gate_status_get)(struct vtss_state_s *vtss_state,
                                     const vtss_psfp_gate_id_t id,
                                     vtss_psfp_gate_status_t *const status);
    vtss_rc (* psfp_filter_conf_set)(struct vtss_state_s *vtss_state,
                                     const vtss_psfp_filter_id_t id);
    vtss_rc (* psfp_filter_status_get)(struct vtss_state_s *vtss_state,
                                       const vtss_psfp_filter_id_t id,
                                       vtss_psfp_filter_status_t *const status);
#endif
#if defined(VTSS_FEATURE_RCL)
    vtss_rc (* rcl_vid_conf_set)(struct vtss_state_s *vtss_state, const u8 idx);
#endif

    /* Configuration/state */
    /* Aggregated forwarding information */
    BOOL                          learn[VTSS_PORT_ARRAY_SIZE];
    BOOL                          rx_forward[VTSS_PORT_ARRAY_SIZE];
    BOOL                          tx_forward[VTSS_PORT_ARRAY_SIZE];
    BOOL                          tx_forward_aggr[VTSS_PORT_ARRAY_SIZE];
    BOOL                          port_all[VTSS_PORTS];  /* For convenience, includes all ports */
    BOOL                          port_none[VTSS_PORTS]; /* For convenience, excludes all ports */

    BOOL                          port_state[VTSS_PORT_ARRAY_SIZE];
    vtss_aggr_no_t                port_aggr_no[VTSS_PORT_ARRAY_SIZE];
    vtss_auth_state_t             auth_state[VTSS_PORT_ARRAY_SIZE];
    vtss_stp_state_t              stp_state[VTSS_PORT_ARRAY_SIZE];
    vtss_pvlan_entry_t            pvlan_table[VTSS_PVLAN_ARRAY_SIZE];
    BOOL                          apvlan_table[VTSS_PORT_ARRAY_SIZE][VTSS_PORT_ARRAY_SIZE];
    vtss_dgroup_port_conf_t       dgroup_port_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_mirror_conf_t            mirror_conf;

    BOOL                          mirror_ingress[VTSS_PORT_ARRAY_SIZE];
    BOOL                          mirror_egress[VTSS_PORT_ARRAY_SIZE];
    BOOL                          mirror_cpu_ingress;
    BOOL                          mirror_cpu_egress;
    vtss_vlan_conf_t              vlan_conf;
    vtss_vlan_port_type_t         vlan_port_type[VTSS_PORT_ARRAY_SIZE];
    vtss_vid_t                    vlan_port_uvid[VTSS_PORT_ARRAY_SIZE];
    vtss_vlan_port_conf_t         vlan_port_conf[VTSS_PORT_ARRAY_SIZE];
#if defined(VTSS_FEATURE_VCAP)
    vtss_vcl_port_conf_t          vcl_port_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_vcl_port_conf_t          vcl_port_conf_old;
#endif
    BOOL                          l3_dt[VTSS_PORT_ARRAY_SIZE];
    vtss_port_eps_t               port_protect[VTSS_PORT_ARRAY_SIZE];
    BOOL                          vlan_filter_changed;
    vtss_vlan_entry_t             vlan_table[VTSS_VIDS];
#if defined(VTSS_FEATURE_L2_MSTP)
    vtss_mstp_entry_t             mstp_table[VTSS_MSTI_ARRAY_SIZE];
#endif
#if defined(VTSS_FEATURE_L2_ERPS)
    vtss_erps_entry_t             erps_table[VTSS_ERPI_ARRAY_SIZE];
#endif
    vtss_learn_mode_t             learn_mode[VTSS_PORT_ARRAY_SIZE];
    BOOL                          isolated_port[VTSS_PORT_ARRAY_SIZE];
    BOOL                          uc_flood[VTSS_PORT_ARRAY_SIZE];
    BOOL                          mc_flood[VTSS_PORT_ARRAY_SIZE];
    BOOL                          ipv4_mc_flood[VTSS_PORT_ARRAY_SIZE];
    BOOL                          ipv6_mc_flood[VTSS_PORT_ARRAY_SIZE];
    BOOL                          ipv6_mc_scope;
    vtss_mac_table_age_time_t     mac_age_time;
    vtss_mac_table_status_t       mac_status;
    u32                           mac_index_next;  /* Index for MAC table get next */
    u32                           mac_table_max;   /* Maximum number of entries in mac_table */
    u32                           mac_table_count; /* Actual number of entries in mac_table */
    vtss_mac_entry_t              *mac_list_used;  /* Sorted list of entries */
    vtss_mac_entry_t              *mac_list_free;  /* Free list */
    vtss_mac_entry_t              mac_table[VTSS_MAC_ADDRS]; /* Sorted MAC address table */
    u32                           mac_ptr_count;   /* Number of valid pointers */
    vtss_mac_entry_t              *mac_list_ptr[VTSS_MAC_PTR_SIZE]; /* Pointer array */
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    vtss_mac_index_table_t        mac_index_table;
#endif
    u32                           ac_count;
    vtss_aggr_mode_t              aggr_mode;
    u32                           aggr_chip_port_next[2];
    u32                           pgid_count;
    u32                           pgid_drop;
    u32                           pgid_flood;
    u32                           pgid_glag_dest;
    u32                           pgid_glag_src;
    u32                           pgid_glag_aggr_a;
    u32                           pgid_glag_aggr_b;
    vtss_pgid_entry_t             pgid_table[VTSS_PGIDS+1];

    vtss_sflow_port_conf_t        sflow_conf[VTSS_PORT_ARRAY_SIZE];
    u32                           sflow_max_power_of_two;
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    u32                           sflow_ena_cnt; /* Count - the number of ports on which sFlow is enabled */
#endif

#if defined(VTSS_FEATURE_VCAP)
    vtss_vlan_trans_grp2vlan_t    vt_trans_conf;
    vtss_vlan_trans_port2grp_t    vt_port_conf;
#endif
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    vtss_vlan_counter_info_t      vlan_counters_info;
#endif /* VTSS_FEATURE_VLAN_COUNTERS */
#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
    vtss_ipmc_info_t              ipmc;
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */
#if defined(VTSS_ARCH_JAGUAR_2)
    vtss_vsi_info_t      vsi_info;
#endif /* VTSS_ARCH_JAGUAR_2 */
#if defined(VTSS_EVC_STAT_CNT)
    vtss_evc_pol_table_t  pol_table;
    vtss_evc_stat_table_t istat_table;
    vtss_evc_stat_table_t estat_table;
    vtss_xstat_table_t    istat;
    vtss_xstat_table_t    estat;
    vtss_xpol_table_t     pol;
#endif
#if defined(VTSS_SDX_CNT)
    vtss_sdx_info_t      sdx_info;
    vtss_eflow_entry_t   eflow[VTSS_SDX_CNT];
#endif /* VTSS_SDX_CNT */
#if defined(VTSS_EVC_POL_CNT)
    vtss_dlb_policer_conf_t pol_conf[VTSS_EVC_POL_CNT]; /* Policer configuration */
#if defined(VTSS_FEATURE_PSFP)
    vtss_dlb_policer_status_t pol_status[VTSS_EVC_POL_CNT];
#endif
#endif
#if defined(VTSS_FEATURE_FRER)
    vtss_ms_table_t           ms_table;
    vtss_xms_table_t          ms;
    vtss_frer_stream_conf_t   mstream_conf[VTSS_MSTREAM_CNT];
    vtss_frer_stream_conf_t   cstream_conf[VTSS_CSTREAM_CNT];
    vtss_frer_chip_counters_t ms_counters[VTSS_MSTREAM_CNT];
    vtss_frer_chip_counters_t cs_counters[VTSS_CSTREAM_CNT];
    u32                       poll_idx; /* Counter polling index */
#endif
#if defined(VTSS_FEATURE_PSFP)
    vtss_psfp_state_t psfp;
#endif
#if defined(VTSS_FEATURE_RCL)
    vtss_rcl_vid_entry_t rcl_vid[VTSS_RCL_VID_CNT];
#endif
} vtss_l2_state_t;

#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
BOOL l26_ssm_validate_fid(u16 *fid, BOOL fid_only);
vtss_rc l26_ssm_conflict_adjustment(vtss_ipmc_src_t *ssm);
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */

vtss_rc vtss_l2_inst_create(struct vtss_state_s *vtss_state);
vtss_rc vtss_l2_restart_sync(struct vtss_state_s *vtss_state);

vtss_rc vtss_vid_check(const vtss_vid_t vid);
vtss_rc vtss_mac_add(struct vtss_state_s *vtss_state,
                     vtss_mac_user_t user, const vtss_mac_table_entry_t *const entry);
vtss_rc vtss_mac_del(struct vtss_state_s *vtss_state,
                     vtss_mac_user_t user, const vtss_vid_mac_t *const vid_mac);
vtss_rc vtss_mac_get(struct vtss_state_s *vtss_state,
                     vtss_mac_table_entry_t *const entry, u32 *pgid);
vtss_rc vtss_update_masks(struct vtss_state_s *vtss_state,
                          BOOL src_update, BOOL dest_update, BOOL aggr_update);
vtss_rc vtss_cmn_vlan_members_get(struct vtss_state_s *state,
                                  const vtss_vid_t vid,
                                  BOOL member[VTSS_PORT_ARRAY_SIZE]);
vtss_rc vtss_cmn_vlan_members_set(struct vtss_state_s *vtss_state, const vtss_vid_t vid);
vtss_rc vtss_cmn_vlan_port_conf_set(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);

vtss_rc vtss_cmn_vlan_tx_tag_set(struct vtss_state_s *vtss_state,
                                 const vtss_vid_t         vid,
                                 const vtss_vlan_tx_tag_t tx_tag[VTSS_PORT_ARRAY_SIZE]);
vtss_rc vtss_cmn_vlan_update_all(struct vtss_state_s *vtss_state);
#if defined(VTSS_FEATURE_L2_MSTP)
vtss_rc vtss_cmn_mstp_state_set(struct vtss_state_s *vtss_state,
                                const vtss_port_no_t   port_no,
                                const vtss_msti_t      msti);
#endif
#if defined(VTSS_FEATURE_L2_ERPS)
vtss_rc vtss_cmn_erps_vlan_member_set(struct vtss_state_s *vtss_state,
                                      const vtss_erpi_t erpi,
                                      const vtss_vid_t  vid);
vtss_rc vtss_cmn_erps_port_state_set(struct vtss_state_s *vtss_state,
                                     const vtss_erpi_t    erpi,
                                     const vtss_port_no_t port_no);
#endif
vtss_rc vtss_cmn_eps_port_set(struct vtss_state_s *vtss_state, const vtss_port_no_t port_w);
#if defined(VTSS_FEATURE_HW_PROT)
vtss_rc vtss_cmn_hw_prot_port_disable_set(struct vtss_state_s *vtss_state,
                                          const vtss_vid_t    vid,
                                          const BOOL          member[VTSS_PORT_ARRAY_SIZE]);
#endif /* VTSS_FEATURE_HW_PROT */
#if VTSS_OPT_DEBUG_PRINT
void vtss_debug_print_mac_entry(const vtss_debug_printf_t pr,
                                const char *name,
                                BOOL *header,
                                vtss_mac_table_entry_t *entry,
                                u32 pgid);
#endif
#if defined(VTSS_FEATURE_IPV4_MC_SIP) || defined(VTSS_FEATURE_IPV6_MC_SIP)
u32 vtss_cmn_ip2u32(vtss_ip_addr_internal_t *ip, BOOL ipv6);
vtss_rc vtss_cmn_ipv4_mc_add(struct vtss_state_s     *vtss_state,
                             const vtss_vid_t vid,
                             const vtss_ip_t  sip,
                             const vtss_ip_t  dip,
                             const BOOL       member[VTSS_PORT_ARRAY_SIZE]);
vtss_rc vtss_cmn_ipv4_mc_del(struct vtss_state_s     *vtss_state,
                             const vtss_vid_t vid,
                             const vtss_ip_t  sip,
                             const vtss_ip_t  dip);
vtss_rc vtss_cmn_ipv6_mc_add(struct vtss_state_s      *vtss_state,
                             const vtss_vid_t  vid,
                             const vtss_ipv6_t sip,
                             const vtss_ipv6_t dip,
                             const BOOL        member[VTSS_PORT_ARRAY_SIZE]);
vtss_rc vtss_cmn_ipv6_mc_del(struct vtss_state_s      *vtss_state,
                             const vtss_vid_t  vid,
                             const vtss_ipv6_t sip,
                             const vtss_ipv6_t dip);
#endif /* VTSS_FEATURE_IPV4_MC_SIP || VTSS_FEATURE_IPV6_MC_SIP */

#if defined(VTSS_FEATURE_VCAP)
#if defined(VTSS_ARCH_OCELOT)
vtss_vcap_key_type_t vtss_vcl_key_type_get(vtss_vcap_key_type_t key_type_a, vtss_vcap_key_type_t key_type_b);
#endif
vtss_rc vtss_cmn_vcl_port_conf_set(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_cmn_vce_add(struct vtss_state_s *vtss_state,
                         const vtss_vce_id_t vce_id, const vtss_vce_t *const vce);
vtss_rc vtss_cmn_vce_del(struct vtss_state_s *vtss_state, const vtss_vce_id_t vce_id);
vtss_rc vtss_cmn_vlan_trans_group_add(struct vtss_state_s *vtss_state,
                                      const vtss_vlan_trans_grp2vlan_conf_t *conf);
vtss_rc vtss_cmn_vlan_trans_group_del(struct vtss_state_s *vtss_state,
                                      const vtss_vlan_trans_grp2vlan_conf_t *conf);
vtss_rc vtss_cmn_vlan_trans_group_get(struct vtss_state_s *vtss_state,
                                      vtss_vlan_trans_grp2vlan_conf_t *conf, BOOL next);
vtss_rc vtss_cmn_vlan_trans_port_conf_set(struct vtss_state_s *vtss_state,
                                          const vtss_vlan_trans_port2grp_conf_t *conf);
vtss_rc vtss_cmn_vlan_trans_port_conf_get(struct vtss_state_s *vtss_state,
                                          vtss_vlan_trans_port2grp_conf_t *conf, BOOL next);
vtss_rc vtss_rcl_vid_lookup(struct vtss_state_s *vtss_state, vtss_vid_t vid, u8 *idx, BOOL lookup_free);
#endif // VTSS_FEATURE_VCAP

/* Generic port mask */
typedef struct {
    u32 m[3];
} vtss_port_mask_t;

void vtss_port_mask_clear(vtss_port_mask_t *pmask);
void vtss_port_mask_get(struct vtss_state_s *vtss_state,
                        const BOOL member[],
                        vtss_port_mask_t *pmask);
void vtss_port_mask_port(struct vtss_state_s *vtss_state,
                         vtss_port_no_t port_no,
                         vtss_port_mask_t *pmask);

#if defined(VTSS_SDX_CNT)
vtss_sdx_entry_t *vtss_cmn_sdx_alloc(struct vtss_state_s *vtss_state, vtss_port_no_t port_no, u16 id, BOOL isdx);
void vtss_cmn_sdx_free(struct vtss_state_s *vtss_state, vtss_sdx_entry_t *sdx, BOOL isdx);
vtss_rc vtss_cmn_policer_alloc(struct vtss_state_s *vtss_state, u8 count, u16 *idx);
vtss_rc vtss_cmn_policer_free(struct vtss_state_s *vtss_state, u16 *idx);
vtss_rc vtss_cmn_istat_alloc(struct vtss_state_s *vtss_state, u8 count, u16 *idx);
vtss_rc vtss_cmn_istat_free(struct vtss_state_s *vtss_state, u16 *idx);
vtss_rc vtss_cmn_estat_alloc(struct vtss_state_s *vtss_state, u8 count, u16 *idx);
vtss_rc vtss_cmn_estat_free(struct vtss_state_s *vtss_state, u16 *idx);
vtss_sdx_entry_t *vtss_iflow_lookup(struct vtss_state_s *vtss_state, vtss_iflow_id_t id);
vtss_eflow_entry_t *vtss_eflow_lookup(struct vtss_state_s *vtss_state, vtss_eflow_id_t id);
#endif
#if defined(VTSS_FEATURE_XSTAT)
vtss_xstat_entry_t *vtss_estat_lookup(struct vtss_state_s *vtss_state, const vtss_egress_cnt_id_t id);
#endif

#if VTSS_OPT_DEBUG_PRINT
void vtss_l2_debug_print(struct vtss_state_s *vtss_state,
                         const vtss_debug_printf_t pr,
                         const vtss_debug_info_t   *const info);
#endif
#endif /* VTSS_FEATURE_LAYER2 */

#endif /* _VTSS_L2_STATE_H_ */
