// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_VCAP_STATE_H_
#define _VTSS_VCAP_STATE_H_


#if defined(VTSS_FEATURE_VCAP)

#if defined(VTSS_ARCH_LUTON26)
#define VTSS_FEATURE_IS1  /* VCAP IS1 */
#define VTSS_FEATURE_IS2  /* VCAP IS2 */
#define VTSS_FEATURE_ES0  /* VCAP ES0 */
#endif /* VTSS_ARCH_LUTON26 */

#if defined(VTSS_ARCH_OCELOT)
#define VTSS_OPT_WARM_START
#define VTSS_FEATURE_IS1  /* VCAP IS1 */
#define VTSS_FEATURE_IS2  /* VCAP IS2 */
#define VTSS_FEATURE_ES0  /* VCAP ES0 */
#endif /* VTSS_ARCH_OCELOT */

#if defined(VTSS_ARCH_LAN966X)
#define VTSS_FEATURE_IS1  /* VCAP IS1 */
#define VTSS_FEATURE_IS2  /* VCAP IS2 */
#define VTSS_FEATURE_ES0  /* VCAP ES0 */
#endif /* VTSS_ARCH_LAN966X */

#if defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_FEATURE_IS2            /* VCAP IS2 */
#define VTSS_FEATURE_ES0            /* VCAP ES0 */
#define VTSS_FEATURE_CLM            /* VCAP CLM */
#define VTSS_FEATURE_LPM            /* VCAP LPM */
#define VTSS_FEATURE_VCAP_SUPER     /* VCAP_SUPER pool */
#if defined(VTSS_ARCH_SERVAL_T)
#define VTSS_VCAP_SUPER_BLK_CNT  6   /* Number of VCAP_SUPER blocks */
#define VTSS_VCAP_SUPER_ROW_CNT  64  /* Number of rows in one VCAP super block (full rules) */
#else
#if defined(VTSS_CHIP_SPARX_IV_52)
#define VTSS_VCAP_SUPER_BLK_CNT  4   /* Number of VCAP_SUPER blocks */
#elif defined(VTSS_CHIP_SERVAL_2)
#define VTSS_VCAP_SUPER_BLK_CNT  5   /* Number of VCAP_SUPER blocks */
#elif defined(VTSS_CHIP_SPARX_IV_44)
#define VTSS_VCAP_SUPER_BLK_CNT  6   /* Number of VCAP_SUPER blocks */
#else
#define VTSS_VCAP_SUPER_BLK_CNT  8   /* Number of VCAP_SUPER blocks */
#endif
#define VTSS_VCAP_SUPER_ROW_CNT  256 /* Number of rows in one VCAP super block (full rules) */
#endif /* VTSS_ARCH_SERVAL_T */
#define VTSS_VCAP_SUPER_RULE_CNT (VTSS_VCAP_SUPER_BLK_CNT * VTSS_VCAP_SUPER_ROW_CNT * 8) /* Eight rules per row */
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_ARCH_SPARX5)
#define VTSS_FEATURE_IS2             /* VCAP IS2 */
#define VTSS_FEATURE_IS2_B           /* VCAP IS2_B */
#define VTSS_FEATURE_ES0             /* VCAP ES0 */
#define VTSS_FEATURE_ES2             /* VCAP ES2 */
#define VTSS_FEATURE_CLM             /* VCAP CLM */
#define VTSS_FEATURE_LPM             /* VCAP LPM */
#define VTSS_FEATURE_VCAP_SUPER      /* VCAP_SUPER pool */
#define VTSS_VCAP_SUPER_BLK_CNT  10  /* Number of VCAP_SUPER blocks */
#define VTSS_VCAP_SUPER_ROW_CNT  256 /* Number of rows in one VCAP super block (full rules) */
#define VTSS_VCAP_SUPER_RULE_CNT (VTSS_VCAP_SUPER_BLK_CNT * VTSS_VCAP_SUPER_ROW_CNT * 6) /* Six rules per row */
#endif

/** \brief VCAP key size */
typedef enum
{
    VTSS_VCAP_KEY_SIZE_FULL,     /**< Full (1/1) key */
    VTSS_VCAP_KEY_SIZE_HALF,     /**< Half (1/2) key */
    VTSS_VCAP_KEY_SIZE_QUARTER,  /**< Quarter (1/4) key */
    VTSS_VCAP_KEY_SIZE_SIXTH,    /**< Sixth (1/6) key */
    VTSS_VCAP_KEY_SIZE_EIGHTH,   /**< Eighth (1/8) key */
    VTSS_VCAP_KEY_SIZE_TWELFTH,  /**< Twelfth (1/12) key */
    VTSS_VCAP_KEY_SIZE_SIXTEENTH /**< Sixteeth (1/16) key */
} vtss_vcap_key_size_t;

#define VTSS_VCAP_KEY_SIZE_LAST VTSS_VCAP_KEY_SIZE_SIXTEENTH
#define VTSS_VCAP_KEY_SIZE_MAX  (VTSS_VCAP_KEY_SIZE_LAST + 1)

/* Resource change data */
typedef struct {
    u32 add;                             /* Number of added items */
    u32 del;                             /* Number of deleted items */
    u32 add_key[VTSS_VCAP_KEY_SIZE_MAX]; /* Added rules for each key size */
    u32 del_key[VTSS_VCAP_KEY_SIZE_MAX]; /* Deleted rules for each key size */
} vtss_res_chg_t;

/* Policer/statistics change data */
typedef struct {
    u32 add;         /* Number of added items */
    u32 del;         /* Number of deleted items */
    u32 add_size[9]; /* Added items for each size (0-8) */
    u32 del_size[9]; /* Deleted items for each size (0-8) */
} vtss_ps_chg_t;

/* Resource change information */
typedef struct {
    vtss_res_chg_t  is0;
    vtss_res_chg_t  is1;
    vtss_res_chg_t  clm_a;
    vtss_res_chg_t  clm_b;
    vtss_res_chg_t  clm_c;
    vtss_res_chg_t  lpm;
    vtss_res_chg_t  is2;
    vtss_res_chg_t  is2_b;
    vtss_res_chg_t  es0;
    vtss_res_chg_t  es2;
    vtss_res_chg_t  isdx;
    vtss_res_chg_t  esdx;
    vtss_res_chg_t  vsi;
    vtss_ps_chg_t   pol;
    vtss_ps_chg_t   istat;
    vtss_ps_chg_t   estat;
    u32             clm;
} vtss_res_t;

typedef enum {
    VTSS_VCAP_TYPE_NONE,
    VTSS_VCAP_TYPE_IS0,
    VTSS_VCAP_TYPE_IS1,
    VTSS_VCAP_TYPE_IS2,
    VTSS_VCAP_TYPE_IS2_B,
    VTSS_VCAP_TYPE_ES0,
    VTSS_VCAP_TYPE_ES2,
    VTSS_VCAP_TYPE_CLM_A,
    VTSS_VCAP_TYPE_CLM_B,
    VTSS_VCAP_TYPE_CLM_C,
    VTSS_VCAP_TYPE_LPM
} vtss_vcap_type_t;

/* VCAP ID */
typedef u64 vtss_vcap_id_t;

/* VCAP users in prioritized order */
typedef enum {
    /* IS0 users */
    VTSS_IS0_USER_EVC,           /* EVC (JR1) */
#if defined(VTSS_ARCH_OCELOT)
    VTSS_IS0_USER_MPLS_LL,       /* MPLS link layer */
    VTSS_IS0_USER_MPLS_MLBS_3,   /* MPLS label stack depth 3 */
    VTSS_IS0_USER_MPLS_MLBS_2,   /* MPLS label stack depth 2 */
    VTSS_IS0_USER_MPLS_MLBS_1,   /* MPLS label stack depth 1 */
#endif

    /* IS1 users */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    VTSS_IS1_USER_MPLS_LL,       /* MPLS link layer */
    VTSS_IS1_USER_MPLS_MLBS,     /* MPLS label stack, single label */
    VTSS_IS1_USER_MCE_0,         /* MCE_0 (First MCE user) */
#else
    VTSS_IS1_USER_TT_LOOP_0,     /* TT_LOOP before MEP (first lookup) */
#endif
    VTSS_IS1_USER_VCL,           /* VCL (first lookup) */
    VTSS_IS1_USER_VLAN,          /* VLAN translation (first lookup) */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    VTSS_IS1_USER_MCE_1,         /* MCE_1 (Second MCE user) */
    VTSS_IS1_USER_MCE_2,         /* MCE_2 (Third MCE user) */
    VTSS_IS1_USER_MCE_3,         /* MCE_3 (Fourth MCE user) */
    VTSS_IS1_USER_MCE_4,         /* MCE_4 (Fifth MCE user) */
#else
    VTSS_IS1_USER_MEP,           /* MEP (first lookup, L26/SRVL) */
    VTSS_IS1_USER_TT_LOOP_1,     /* TT_LOOP after MEP */
#endif
    VTSS_IS1_USER_ECE,           /* ECE (JR2) */
    VTSS_IS1_USER_EVC,           /* EVC (first lookup, L26/SRVL) */
    VTSS_IS1_USER_EVC_CPU,       /* EVC CPU port (JR2) */
    VTSS_IS1_USER_QOS,           /* QoS QCL (second lookup for L26/JR1, third lookup for SRVL) */
    VTSS_IS1_USER_ACL,           /* ACL SIP/SMAC (third lookup, L26) */
    VTSS_IS1_USER_SSM,           /* SSM (first lookup, L26) */
    VTSS_IS1_USER_RCL,           /* RCL */

    /* IS2 users */
    VTSS_IS2_USER_IGMP,          /* IGMP rules (first lookup, JR1) */
    VTSS_IS2_USER_SSM,           /* SSM rules */
    VTSS_IS2_USER_ASM,           /* ASM rules */
    VTSS_IS2_USER_IGMP_ANY,      /* IGMP any rules (first lookup, JR1) */
    VTSS_IS2_USER_EEE,           /* EEE loopback port rules (second lookup, JR1) */
    VTSS_IS2_USER_ACL_PTP,       /* ACL PTP rules (second lookup, L26) */
    VTSS_IS2_USER_ACL_SIP,       /* ACL SIP/SMAC rules (Serval) */
    VTSS_IS2_USER_ACL,           /* ACL rules (first lookup for L26, second lookup for JR1) */
    VTSS_IS2_USER_IPACL,         /* I-PACL */
    VTSS_IS2_USER_IVACL,         /* I-VACL */
    VTSS_IS2_USER_IRACL,         /* I-RACL */
    VTSS_IS2_USER_ERACL,         /* E-RACL */

    /* ES0 users */
    VTSS_ES0_USER_TCL,      /* Tag Control List */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    VTSS_ES0_USER_MCE_0,    /* MCE_0 (First MCE user) */
#else
    VTSS_ES0_USER_TT_LOOP,  /* TT_LOOP (first lookup) */
#endif
    VTSS_ES0_USER_VLAN,     /* VLAN translation */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    VTSS_ES0_USER_MCE_1,    /* MCE_1 (Second MCE user) */
    VTSS_ES0_USER_MCE_2,    /* MCE_2 (Third MCE user) */
    VTSS_ES0_USER_MCE_3,    /* MCE_3 (Fourth MCE user) */
#else
    VTSS_ES0_USER_MEP,      /* MEP (first lookup, L26/SRVL) */
#endif
    VTSS_ES0_USER_EVC,      /* EVC rules */
    VTSS_ES0_USER_EFE,      /* EFE rules */
    VTSS_ES0_USER_TX_TAG,   /* VLAN Tx tagging */
    VTSS_ES0_USER_MPLS,     /* MPLS */

    /* LPM users */
    VTSS_LPM_USER_ACL,      /* ACL SIP/SMAC */
    VTSS_LPM_USER_L3,       /* L3 Unicast */
    VTSS_LPM_USER_L3_MC,    /* L3 Mulitcast */

    /* ES2 users */
    VTSS_ES2_USER_EVACL,    /* E-VACL */
    VTSS_ES2_USER_EPACL,    /* E-PACL */
} vtss_vcap_user_t;

#if defined(VTSS_FEATURE_MPLS) && defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#define VTSS_MPLS_IN_ENCAP_LABEL_CNT    3       /* Number of HW labels supported at ingress */
#define VTSS_MPLS_OUT_ENCAP_LABEL_CNT   3       /* Number of HW labels supported at egress */
#endif

#if defined(VTSS_FEATURE_IS0)
#if defined(VTSS_ARCH_OCELOT)

// In- and Out-segment encapsulation counts

#define VTSS_MPLS_IN_ENCAP_CNT          128     /* Number of HW entries */
#define VTSS_MPLS_IN_ENCAP_LABEL_CNT    3       /* Number of HW labels supported at ingress */
#define VTSS_MPLS_OUT_ENCAP_LABEL_CNT   3       /* Number of HW labels supported at egress */

typedef enum {
    VTSS_MLL_ETHERTYPE_DOWNSTREAM_ASSIGNED = 1,
    VTSS_MLL_ETHERTYPE_UPSTREAM_ASSIGNED   = 2
} vtss_mll_ethertype_t;

typedef enum {
    VTSS_IS0_MLBS_OAM_NONE    = 0,
    VTSS_IS0_MLBS_OAM_VCCV1   = 1,
    VTSS_IS0_MLBS_OAM_VCCV2   = 2,
    VTSS_IS0_MLBS_OAM_VCCV3   = 3,
    VTSS_IS0_MLBS_OAM_GAL_MEP = 4,
    VTSS_IS0_MLBS_OAM_GAL_MIP = 5
} vtss_is0_mlbs_oam_t;

typedef enum {
    VTSS_IS0_MLBS_POPCOUNT_0  = 1,
    VTSS_IS0_MLBS_POPCOUNT_14 = 2,
    VTSS_IS0_MLBS_POPCOUNT_18 = 3,
    VTSS_IS0_MLBS_POPCOUNT_22 = 4,
    VTSS_IS0_MLBS_POPCOUNT_26 = 5,
    VTSS_IS0_MLBS_POPCOUNT_30 = 6,
    VTSS_IS0_MLBS_POPCOUNT_34 = 7
} vtss_is0_mlbs_popcount_t;

typedef enum {
    VTSS_IS0_TYPE_MLL,
    VTSS_IS0_TYPE_MLBS
} vtss_is0_type_t;

typedef struct {
    BOOL                     physical[VTSS_PORT_ARRAY_SIZE]; /**< Physical port list */
    BOOL                     cpu;
} vtss_is0_b_portlist_t;

typedef enum {
    VTSS_IS0_TAGTYPE_UNTAGGED = 0,     /**< Frame is untagged */
    VTSS_IS0_TAGTYPE_CTAGGED  = 1,     /**< Frame is C-tagged */
    VTSS_IS0_TAGTYPE_STAGGED  = 2      /**< Frame is S-tagged */
} vtss_is0_tagtype_t;

typedef struct {
    vtss_port_no_t           ingress_port;
    vtss_is0_tagtype_t       tag_type;
    vtss_vid_t               b_vid;
    vtss_mac_t               dmac;
    vtss_mac_t               smac;
    vtss_mll_ethertype_t     ether_type;
    BOOL                     ingress_port_dontcare;     // TRUE = don't match field
    BOOL                     tag_type_dontcare;
    BOOL                     b_vid_dontcare;
    BOOL                     dmac_dontcare;
    BOOL                     smac_dontcare;
    BOOL                     ether_type_dontcare;
} vtss_is0_mll_key_t;

typedef struct {
    u8                       linklayer_index;
    BOOL                     mpls_forwarding;
    vtss_is0_b_portlist_t    b_portlist;
    u8                       cpu_queue;

    u16                      oam_isdx;
    BOOL                     oam_isdx_add_replace;

    // Below: Only used when mpls_forwarding == FALSE
    u16                      isdx;
    u8                       vprofile_index;
    vtss_vid_t               classified_vid;
    BOOL                     use_service_config;

    // Below: Only used when mpls_forwarding == FALSE && use_service_config == TRUE
    vtss_prio_t              qos;
    vtss_dp_level_t          dp;
} vtss_is0_mll_action_t;

typedef struct {
    u32                         linklayer_index;
    struct {
        u32                     value;                          /* Label value (20 bits) */
        u32                     value_mask;                     /* Label bits to match */
        u8                      tc;                             /* TC value (0-7) */
        u8                      tc_mask;                        /* TC bits to match */
    } label_stack[VTSS_MPLS_IN_ENCAP_LABEL_CNT];   // 0 is top-of-stack
} vtss_is0_mlbs_key_t;

typedef struct {
    u16                      isdx;
    u8                       cpu_queue;
    vtss_is0_b_portlist_t    b_portlist;
    vtss_is0_mlbs_oam_t      oam;
    BOOL                     oam_buried_mip;
    u8                       oam_reserved_label_value;
    BOOL                     oam_reserved_label_bottom_of_stack;
    u16                      oam_isdx;
    BOOL                     oam_isdx_add_replace;   /**< TRUE = replace; FALSE = add */

    BOOL                     cw_enable;
    BOOL                     terminate_pw;

    u8                       tc_label_index;
    u8                       ttl_label_index;
    u8                       swap_label_index;
    vtss_is0_mlbs_popcount_t pop_count; /**< 0, 14, 18, 22, 26, 30, 34 */

    BOOL                     e_lsp;
    u8                       tc_maptable_index;
    u8                       l_lsp_qos_class;
    BOOL                     add_tc_to_isdx;

    BOOL                     swap_is_bottom_of_stack;

    u8                       vprofile_index;
    vtss_vid_t               classified_vid;
    BOOL                     use_service_config;

    // Below: Only used when use_service_config == TRUE
    BOOL                     s_tag;          /**< FALSE = C-tag */
    vtss_tagprio_t           pcp;            /**< PCP value */
    vtss_dei_t               dei;            /**< DEI value */
} vtss_is0_mlbs_action_t;

typedef union {
    vtss_is0_mll_key_t       mll;
    vtss_is0_mlbs_key_t      mlbs;
} vtss_is0_key_t;

typedef union {
    vtss_is0_mll_action_t    mll;
    vtss_is0_mlbs_action_t   mlbs;
} vtss_is0_action_t;

/* IS0 entry */
typedef struct {
    vtss_is0_type_t          type;
    vtss_is0_key_t           key;
    vtss_is0_action_t        action;
} vtss_is0_entry_t;

/* IS0 data */
typedef struct {
    vtss_is0_entry_t *entry;
} vtss_is0_data_t;

#endif
#endif /* VTSS_FEATURE_IS0 */

typedef enum {
    VTSS_FID_SEL_DEFAULT = 0,   /* Disabled: FID = classified VID. */
    VTSS_FID_SEL_SMAC,          /* Use FID_VAL for SMAC lookup in MAC table. */
    VTSS_FID_SEL_DMAC,          /* Use FID_VAL for DMAC lookup in MAC table. */
    VTSS_FID_SEL_BOTHMAC        /* Use FID_VAL for DMAC and SMAC lookup in MAC */
} vtss_fid_sel_t;

#if defined(VTSS_FEATURE_IS1) || defined(VTSS_FEATURE_CLM)
typedef enum {
    VTSS_MPLS_OAM_DETECT_NONE        = 0,   /**< No OAM detection */

    // PW termination:
    VTSS_MPLS_OAM_DETECT_VCCV1       = 1,   /**< VCCV1 detection */
    VTSS_MPLS_OAM_DETECT_VCCV2       = 2,   /**< VCCV2 detection */
    VTSS_MPLS_OAM_DETECT_VCCV3       = 3,   /**< VCCV3 detection */
    VTSS_MPLS_OAM_DETECT_VCCV4       = 4,   /**< VCCV4 detection */

    // LSP:
    VTSS_MPLS_OAM_DETECT_GAL         = 5,   /**< GAL detection */

    // Section:
    VTSS_MPLS_OAM_DETECT_SECTION     = 6,   /**< Section OAM (GAL on top of stack) */

    // Control PDU:
    VTSS_MPLS_OAM_DETECT_G8113_1     = 1,   /**< G.8113.1/Y.1731 detection */
    VTSS_MPLS_OAM_DETECT_G8113_2     = 2,   /**< G.8113.2 detection */
    VTSS_MPLS_OAM_DETECT_PTP         = 3,   /**< PTP detection */
    VTSS_MPLS_OAM_DETECT_IP4_UDP_PTP = 4,   /**< PTP over IPv4 UDP detection */
    VTSS_MPLS_OAM_DETECT_IP6_UDP_PTP = 5,   /**< PTP over IPv6 UDP detection */
    VTSS_MPLS_OAM_DETECT_SAM_SEQ     = 7,   /**< SAM detection */
} vtss_mpls_oam_detect_t;

typedef enum {
    VTSS_MPLS_FWD_TYPE_NONE         = 0,    /**< No forwarding */
    VTSS_MPLS_FWD_TYPE_TERMINATE_PW = 1,    /**< Terminate Pseudo Wire */
    VTSS_MPLS_FWD_TYPE_LABEL_SWAP   = 2,    /**< Label swap */
    VTSS_MPLS_FWD_TYPE_LABEL_POP    = 3,    /**< Label pop */
    VTSS_MPLS_FWD_TYPE_CTRL_PDU     = 4     /**< Control PDU */
} vtss_mpls_fwd_type_t;

#define VTSS_IS1_NXT_IDX_EVC_MASK   0x1FF   /* This is masking the bits used for EVC id encoding in the 'nxt_idx' action */
#define VTSS_IS1_NXT_IDX_LEAF_MASK  0x200   /* This is masking the bits used for EVC Leaf encoding in the 'nxt_idx' action */
#define VTSS_VID_SECOND   ((const vtss_vid_t)0x2000)/**< Classified VID from second tag */
#define VTSS_VID_THIRD    ((const vtss_vid_t)0x3000)/**< Classified VID from third tag */

typedef struct {
    BOOL            dscp_enable;    /**< Enable DSCP classification */
    vtss_dscp_t     dscp;           /**< DSCP value */
    BOOL            dp_enable;      /**< Enable DP classification */
    vtss_dp_level_t dp;             /**< DP value */
    BOOL            prio_enable;    /**< Enable priority classification */
    vtss_prio_t     prio;           /**< Priority (QOS) value */
    BOOL            cosid_enable;   /**< Enable COSID classification */
    vtss_prio_t     cosid;          /**< COSID value */
    BOOL            vid_enable;     /**< VLAN ID enable */
    vtss_vid_t      vid;            /**< VLAN ID or VTSS_VID_NULL */
    vtss_fid_sel_t  fid_sel;        /**< FID Select */
    vtss_vid_t      fid_val;        /**< FID value */
    BOOL            pcp_dei_enable; /**< Enable PCP and DEI classification (only for Luton26/Serval) */
    BOOL            pcp_enable;     /**< Enable PCP classification (not supported for Luton26/Serval) */
    BOOL            dei_enable;     /**< Enable DEI classification (not supported for Luton26/Serval) */
    vtss_tagprio_t  pcp;            /**< PCP value */
    vtss_dei_t      dei;            /**< DEI value */
    BOOL            host_match;     /**< Host match */
    BOOL            isdx_enable;    /**< ISDX enable */
    u16             isdx;           /**< ISDX value */
    BOOL            pag_enable;     /**< PAG enable */
    u8              pag;            /**< PAG value */
    BOOL            pop_enable;     /**< VLAN POP enable */
    u8              pop;            /**< VLAN POP count */
#if defined(VTSS_ARCH_OCELOT)
    BOOL            oam_enable;     /**< OAM detection enable */
#endif /* VTSS_ARCH_OCELOT */
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
    vtss_oam_detect_t oam_detect;   /**< OAM detection */
#endif /* VTSS_ARCH_OCELOT || VTSS_ARCH_JAGUAR_2 */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    vtss_vid_t      gvid;           /**< Classified GVID */
    BOOL            mip_enable;     /**< OAM hitting MIP enable */
    u8              pipe_enable;    /**< Pipeline_force_enable */
    u8              pipe_pt;        /**< Pipeline_pt */
    u8              pipe_sel;       /**< Pipeline_act_sel */
    u8              nxt_key_type;   /**< Next key type */
    u16             match_id;       /**< The generated match id to follow the frame to CPU. The 'MATCH_ID_MASK' is set to 0x0FFF */
    BOOL            nxt_idx_enable; /**< The nxt_idx replace action is enabled */
    u16             nxt_idx;        /**< The index that can be used as next lookup key. See VTSS_IS1_NXT_IDX_EVC_MASK */
    BOOL            fwd_disable;    /**< Forwarding is disabled */
    u8              rt_sel;         /**< Routing selection */
    BOOL            cpu;            /**< Redirect to CPU if TRUE */
    u8              cpu_queue;      /**< CPU queue used for redirect to CPU */

    u8                     mpls_rsvd_lbl;       /**< MPLS Reserved Label Value, usually GAL == 13 */
    vtss_mpls_fwd_type_t   mpls_fwd_type;       /**< MPLS forwarding type */
    BOOL                   mpls_oam_flavor_1;   /**< TRUE = G.8113.1 (Y.1731); FALSE = G.8113.2 */
    vtss_mpls_oam_detect_t mpls_oam_detect;     /**< MPLS OAM detection type */
    BOOL                   mpls_mep_enable;     /**< OAM hitting MPLS MEP enable */
    BOOL                   mpls_mip_enable;     /**< OAM hitting MPLS MIP enable */
    BOOL                   mpls_tc_enable;      /**< Use label's TC as classified value */
    BOOL                   mpls_ttl_enable;     /**< Use label's TTL as classified value */
    BOOL                   mpls_ip_enable;      /**< Enable MPLS profiles for MPLS encap'd IP frames */
    BOOL                   mpls_cw_enable;      /**< Process PW Control Word */
#endif /* VTSS_ARCH_JAGUAR_2 */
#if defined(VTSS_ARCH_LAN966X)
    BOOL                   dlb_enable;
    u16                    dlb;
    BOOL                   sfid_enable;
    u16                    sfid;
    BOOL                   sgid_enable;
    u16                    sgid;
    vtss_rce_action_t      rce_action;
#endif
} vtss_is1_action_t;

typedef enum
{
    VTSS_IS1_TYPE_ANY,      /**< Any frame type */
    VTSS_IS1_TYPE_ETYPE,    /**< Ethernet Type */
    VTSS_IS1_TYPE_LLC,      /**< LLC */
    VTSS_IS1_TYPE_SNAP,     /**< SNAP */
    VTSS_IS1_TYPE_IPV4,     /**< IPv4 */
    VTSS_IS1_TYPE_IPV6,     /**< IPv6 */
    VTSS_IS1_TYPE_SMAC_SIP, /**< SMAC/SIP */
    VTSS_IS1_TYPE_RCE,      /**< RCE */
    VTSS_IS1_TYPE_MPLS_MLL, /**< MPLS Link Layer */
    VTSS_IS1_TYPE_MPLS_MLBS /**< MPLS LaBel Stack */
} vtss_is1_type_t;

typedef struct
{
    vtss_vcap_bit_t dmac_mc; /**< Multicast DMAC */
    vtss_vcap_bit_t dmac_bc; /**< Broadcast DMAC */
    vtss_vcap_u48_t smac;    /**< SMAC */
#if !defined(VTSS_ARCH_LUTON26)
    vtss_vcap_u48_t dmac;    /**< DMAC */
#endif
} vtss_is1_mac_t; /**< MAC header */

typedef struct
{
    vtss_vcap_vr_t  vid;        /**< VLAN ID (12 bit) */
    vtss_vcap_u8_t  pcp;        /**< PCP (3 bit) */
    vtss_vcap_bit_t dei;        /**< DEI */
    vtss_vcap_bit_t tagged;     /**< Tagged frame */
    vtss_vcap_bit_t s_tag;      /**< S-tag type */
} vtss_is1_tag_t; /**< VLAN Tag */

typedef struct {
    vtss_vcap_u16_t etype; /**< Ethernet Type value */
    vtss_vcap_u32_t data;  /**< MAC data */
    vtss_vcap_u8_t  mel;   /**< OAM MEL */
} vtss_is1_frame_etype_t;

typedef struct {
    vtss_vcap_u48_t data; /**< Data */
} vtss_is1_frame_llc_t;

typedef struct {
    vtss_vcap_u48_t data; /**< Data */
} vtss_is1_frame_snap_t;

typedef struct {
    vtss_vcap_bit_t ip_mc;    /**< IP_MC field */
    vtss_vcap_bit_t fragment; /**< Fragment */
    vtss_vcap_bit_t options;  /**< Header options */
    vtss_vcap_vr_t  dscp;     /**< DSCP field (6 bit) */
    vtss_vcap_u8_t  proto;    /**< Protocol */
    vtss_vcap_ip_t  sip;      /**< Source IP address */
#if !defined(VTSS_ARCH_LUTON26)
    vtss_vcap_ip_t  dip;      /**< Destination IP address */
#endif
    vtss_vcap_vr_t  sport;    /**< UDP/TCP: Source port */
    vtss_vcap_vr_t  dport;    /**< UDP/TCP: Destination port */
} vtss_is1_frame_ipv4_t;

typedef struct {
    vtss_vcap_bit_t  ip_mc; /**< IP_MC field */
    vtss_vcap_vr_t   dscp;  /**< DSCP field (6 bit) */
    vtss_vcap_u8_t   proto; /**< Protocol */
    vtss_vcap_u128_t sip;   /**< Source IP address */
#if !defined(VTSS_ARCH_LUTON26)
    vtss_vcap_u128_t dip;   /**< Destination IP adddress */
#endif
    vtss_vcap_vr_t   sport; /**< UDP/TCP: Source port */
    vtss_vcap_vr_t   dport; /**< UDP/TCP: Destination port */
} vtss_is1_frame_ipv6_t;

typedef struct {
    vtss_port_no_t port_no; /**< Ingress port or VTSS_PORT_NO_NONE */
    vtss_mac_t     smac;    /**< SMAC */
    vtss_ip_t      sip;     /**< Source IP address */
} vtss_is1_frame_smac_sip_t;

typedef struct {
    BOOL           upstream; /**< TRUE == upstream-assigned label Ethertype; FALSE == downstream-assigned. */
} vtss_is1_frame_mpls_mll_t;

typedef struct {
    u32             label;      /**< MPLS label (20-bit). 0 == wildcard */
    vtss_vcap_bit_t s_bit;      /**< MPLS bottom-of-Stack bit */
    vtss_vcap_bit_t ttl_expiry; /**< Set if TTL <= 1 */
} vtss_is1_frame_mpls_mlbs_t;

typedef struct {
    vtss_is1_type_t      type;      /**< Frame type */

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
    vtss_vcap_key_type_t key_type;  /**< Key type */
#endif /* VTSS_ARCH_OCELOT/JAGUAR_2/VTSS_ARCH_SPARX5/VTSS_ARCH_LAN966X */
#if defined(VTSS_ARCH_OCELOT)
    vtss_vcap_u16_t      isdx;      /**< ISDX */
#endif /* VTSS_ARCH_OCELOT */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    vtss_vcap_vid_t      g_idx;        /**< The 'nxt_idx' generated by previous IS1 action can match against this key */
    BOOL                 cpu_port;     /**< Match CPU port */
    BOOL                 looped;       /**< Only Frames looped can hit */
    BOOL                 port_hit;     /**< Only Frames from port can hit */
    BOOL                 masqueraded;  /**< Only Frames masqueraded on port_list can hit */
    BOOL                 dmac_dip;     /**< DMAC/DIP selection instead of SMAC/SIP for NORMAL rules */
#endif /* JAGUAR_2 */

    BOOL                 port_list[VTSS_PORT_ARRAY_SIZE]; /**< Port list */
    vtss_is1_mac_t       mac;          /**< MAC header */
    vtss_is1_tag_t       tag;          /**< VLAN Tag */
    vtss_is1_tag_t       inner_tag;    /**< Inner Tag, only 'tagged' field valid for L26/JR1 */

    union
    {
        /* VTSS_IS1_TYPE_ANY: No specific fields */
        vtss_is1_frame_etype_t     etype;    /**< VTSS_IS1_TYPE_ETYPE */
        vtss_is1_frame_llc_t       llc;      /**< VTSS_IS1_TYPE_LLC */
        vtss_is1_frame_snap_t      snap;     /**< VTSS_IS1_TYPE_SNAP */
        vtss_is1_frame_ipv4_t      ipv4;     /**< VTSS_IS1_TYPE_IPV4 */
        vtss_is1_frame_ipv6_t      ipv6;     /**< VTSS_IS1_TYPE_IPV6 */
        vtss_is1_frame_smac_sip_t  smac_sip; /**< VTSS_IS1_TYPE_SMAC_SIP */
        vtss_is1_frame_mpls_mll_t  mll;      /**< VTSS_IS1_TYPE_MPLS_MLL */
        vtss_is1_frame_mpls_mlbs_t mlbs;     /**< VTSS_IS1_TYPE_MPLS_MLBS */
#if defined(VTSS_FEATURE_RCL)
        vtss_rce_key_t             rce_key;
#endif
    } frame; /**< Frame type specific data */
} vtss_is1_key_t;

typedef struct {
    vtss_is1_action_t action;
    vtss_is1_key_t    key;
} vtss_is1_entry_t;

#define VTSS_IS1_FLAG_MAP_ID    0x01 /* Ingress map ID valid */
#define VTSS_IS1_FLAG_MAP_INNER 0x02 /* Ingress map ID used for inner tag */
#define VTSS_IS1_FLAG_TRI_VID   0x04 /* Use TRI_VID (JR2) */

typedef struct {
    u8               lookup;      /* Lookup (Serval) or first flag (L26/JR) */
    u8               flags;       /* Flags, see above */
    u16              map_id;      /* Ingress QoS map ID */
    u16              isdx;
    u32              vid_range;   /* VID range */
    u32              dscp_range;  /* DSCP range */
    u32              sport_range; /* Source port range */
    u32              dport_range; /* Destination port range */
    vtss_port_no_t   port_no;     /* First ingress port number */
    vtss_is1_entry_t *entry;      /* IS1 entry */
} vtss_is1_data_t;
#endif /* VTSS_FEATURE_IS1/CLM */

#if defined(VTSS_FEATURE_LPM)
typedef enum {
    VTSS_LPM_KEY_SGL_IP4,
    VTSS_LPM_KEY_DBL_IP4,
    VTSS_LPM_KEY_SGL_IP6,
    VTSS_LPM_KEY_DBL_IP6,
} vtss_lpm_key_type_t;

typedef struct {
    BOOL           dst_ena;
    vtss_vcap_ip_t xip;
} vtss_lpm_sgl_ip4_t;

typedef struct {
    vtss_vcap_ip_t dip;
    vtss_vcap_ip_t sip;
} vtss_lpm_dbl_ip4_t;

typedef struct {
    BOOL             dst_ena;
    vtss_vcap_u128_t xip;
} vtss_lpm_sgl_ip6_t;

typedef struct {
    vtss_vcap_u128_t dip;
    vtss_vcap_u128_t sip;
} vtss_lpm_dbl_ip6_t;

typedef struct {
    vtss_lpm_key_type_t type;
    union {
        vtss_lpm_sgl_ip4_t sgl_ip4;
        vtss_lpm_sgl_ip6_t sgl_ip6;
        vtss_lpm_dbl_ip4_t dbl_ip4;
        vtss_lpm_dbl_ip6_t dbl_ip6;
    } data;
} vtss_lpm_key_t;

typedef struct {
    vtss_mac_t             mac;
    u16                    vmid;
    vtss_packet_rx_queue_t cpu_queue;
    BOOL                   secur_match_mac_ena;
    BOOL                   arp_ena;
} vtss_lpm_arp_entry_t;

typedef struct {
    u32 arp_ptr;
    u8  ecmp_cnt;
    u8  rgid;
} vtss_lpm_arp_ptr_t;

typedef struct {
    u8 type;
    union {
        vtss_lpm_arp_entry_t arp_entry;
        vtss_lpm_arp_ptr_t   arp_ptr;
        u32                  l3mc_idx;
    } data;
} vtss_lpm_action_t;

typedef struct {
    vtss_lpm_key_t    key;
    vtss_lpm_action_t action;
} vtss_lpm_entry_t;

typedef struct {
    vtss_lpm_entry_t *entry;
} vtss_lpm_data_t;
#endif /* VTSS_FEATURE_LPM */

#if defined(VTSS_FEATURE_IS2)
typedef struct {
    BOOL       first;        /* First or second lookup */
    BOOL       host_match;   /* Host match from IS1 */
    BOOL       udp_tcp_any;  /* Match UDP/TCP frames */
    BOOL       smac_sip6;    /* SMAC/SIPv6 */
#if defined(VTSS_FEATURE_HACL)
    vtss_hacl_type_t type;
    vtss_hace_t      ace;
    u8               rng;     /* Range index */
    u32              mask[3]; /* Port or router leg mask */
#else
    vtss_ace_t ace;          /* ACE structure */
#endif
    BOOL       ipmc;         /* IPMC flag */
} vtss_is2_entry_t;

// Internal port action used for SSM
#define VTSS_ACL_PORT_ACTION_PGID 100

typedef struct {
    BOOL redir;                     /* Port redirect flag */
    BOOL member[VTSS_PORT_BF_SIZE]; /* Port redirect list */
} vtss_is2_action_t;

typedef struct {
    u32              srange;       /* Source port range */
    u32              drange;       /* Destination port range */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    u16              cnt_id;       /* Counter ID */
#endif
#if defined(VTSS_ARCH_LUTON26)
    u8               policer_type; /* Policer type */
    u8               policer;      /* Allocated policer index */
#endif /* VTSS_ARCH_LUTON26 */
    vtss_is2_action_t action; /* ACE action */
    vtss_is2_entry_t *entry; /* ACE data */
} vtss_is2_data_t;
#endif /* VTSS_FEATURE_IS2 */

#if defined(VTSS_FEATURE_ES0)
/* ES0 tag */
typedef enum {
    VTSS_ES0_TAG_NONE, /* No ES0 tag */
    VTSS_ES0_TAG_ES0,  /* ES0 tag only */
    VTSS_ES0_TAG_PORT, /* ES0 tag and port tag, if enabled (not valid for Serval inner_tag) */
    VTSS_ES0_TAG_BOTH  /* ES0 and port tag (not valid for Serval) */
} vtss_es0_tag_t;

/* ES0 TPI */
typedef enum {
    VTSS_ES0_TPID_C,   /* C-tag */
    VTSS_ES0_TPID_S,   /* S-tag */
    VTSS_ES0_TPID_PORT /* Port tag type */
} vtss_es0_tpid_t;

/* ES0 QOS */
typedef enum {
    VTSS_ES0_QOS_CLASS,
    VTSS_ES0_QOS_ES0,
    VTSS_ES0_QOS_PORT,
    VTSS_ES0_QOS_MAPPED
} vtss_es0_qos_t;

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)

#if defined(VTSS_FEATURE_MPLS)
#if defined(VTSS_CHIP_LYNX_2) || defined(VTSS_CHIP_JAGUAR_2) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
#define VTSS_MPLS_OUT_ENCAP_CNT         1023    /* Number of HW entries */
#elif defined(VTSS_CHIP_SERVAL_2)
#define VTSS_MPLS_OUT_ENCAP_CNT         511     /* Number of HW entries */
#elif defined(VTSS_ARCH_SERVAL_T)
#define VTSS_MPLS_OUT_ENCAP_CNT         127     /* Number of HW entries */
#else
#define VTSS_MPLS_OUT_ENCAP_CNT         0       /* Number of HW entries */
#endif
#endif /* VTSS_FEATURE_MPLS */

/* ES0 VID information */
typedef struct {
    BOOL       sel; /* Enable to select value (default classified) */
    vtss_vid_t val; /* VLAN ID value */
} vtss_es0_vid_t;

/* ES0 PCP selection */
typedef enum {
    VTSS_ES0_PCP_CLASS,  /* Classified PCP */
    VTSS_ES0_PCP_ES0,    /* PCP_VAL in ES0 */
    VTSS_ES0_PCP_MAPPED, /* Mapped PCP */
    VTSS_ES0_PCP_QOS     /* QoS class */
} vtss_es0_pcp_sel_t;

/* ES0 PCP information */
typedef struct {
    vtss_es0_pcp_sel_t sel; /* PCP selection */
    vtss_tagprio_t     val; /* PCP value */
} vtss_es0_pcp_t;

/* ES0 DEI selection */
typedef enum {
    VTSS_ES0_DEI_CLASS,  /* Classified DEI */
    VTSS_ES0_DEI_ES0,    /* DEI_VAL in ES0 */
    VTSS_ES0_DEI_MAPPED, /* Mapped DEI */
    VTSS_ES0_DEI_DP      /* DP value */
} vtss_es0_dei_sel_t;

/* ES0 DEI information */
typedef struct {
    vtss_es0_dei_sel_t sel; /* DEI selection */
    vtss_dei_t         val; /* DEI value */
} vtss_es0_dei_t;

/* ES0 PCP/DEI selection information */
typedef struct {
    vtss_es0_pcp_sel_t pcp;
    vtss_es0_dei_sel_t dei;
} vtss_es0_sel_t;

/* ES0 tag information */
typedef struct {
    vtss_es0_tag_t  tag;  /* Tag selection */
    vtss_es0_tpid_t tpid; /* TPID selection */
    vtss_es0_vid_t  vid;  /* VLAN ID selection and value */
    vtss_es0_pcp_t  pcp;  /* PCP selection and value */
    vtss_es0_dei_t  dei;  /* DEI selection and value */
} vtss_es0_tag_conf_t;

typedef enum {
    VTSS_ES0_MPLS_ENCAP_LEN_NONE = 0,
    VTSS_ES0_MPLS_ENCAP_LEN_14   = 2,
    VTSS_ES0_MPLS_ENCAP_LEN_18   = 3,
    VTSS_ES0_MPLS_ENCAP_LEN_22   = 4,
    VTSS_ES0_MPLS_ENCAP_LEN_26   = 5,
    VTSS_ES0_MPLS_ENCAP_LEN_30   = 6,
    VTSS_ES0_MPLS_ENCAP_LEN_34   = 7
} vtss_es0_mpls_encap_len_t;
#endif /* VTSS_ARCH_OCELOT/JAGUAR_2/VTSS_ARCH_SPARX5 */

/* ES0 action */
typedef struct {
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
    /* For Serval, the following two fields replace the tag related fields below */
    vtss_es0_tag_conf_t       outer_tag;
    vtss_es0_tag_conf_t       inner_tag;
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    BOOL                      mep_idx_enable;
    u16                       mep_idx;
    u32                       mpls_encap_idx;
    vtss_es0_mpls_encap_len_t mpls_encap_len;
    vtss_es0_mpls_encap_len_t mpls_pop_len;
#endif
#endif /* VTSS_ARCH_OCELOT/JAGUAR_2 */

    vtss_es0_tag_t  tag;
    vtss_es0_tpid_t tpid;
    vtss_es0_qos_t  qos;
    vtss_vid_t      vid_a; /* Outer/port tag */
    vtss_vid_t      vid_b; /* Inner/ES0 tag */
    u8              pcp;
    BOOL            dei;

    u16             esdx;  /* Jaguar/Serval only */
    u32             esdx_cosid_offset; /* Jaguar-2 only */
    u8              pop_cnt;         /* Egress pop count */

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    vtss_voi_idx_t  voi_idx;         /* VOI index */
    u8              forward_sel;     /* FWD_SEL action */
    u8              pipe_pt;         /* PIPELINE_PT action */
    u8              pipe_act;        /* PIPELINE_ACT action */
    u8              cpu_queue;       /* CPU queue used for redirect to CPU */
    BOOL            mac_swap_enable; /* Enable MAC swapping */
    BOOL            independent_mel; /* INDEPENDENT_MEL_ENA action */

    u8              mpls_label_sel;  /* MPLS label value mapping selector */
    u8              mpls_tc_sel;     /* MPLS label TC mapping selector */
    u8              mpls_sbit_sel;   /* MPLS label S-bit selector */
    u8              mpls_ttl_sel;    /* MPLS label TTL selector */
    u32             mpls_label_val;  /* MPLS label value, 0..2^20-1 */
    u8              mpls_tc_val;     /* MPLS label TC value, 0-7 */
    u8              mpls_sbit_val;   /* MPLS label S-bit value, 0-1 */
    u8              mpls_ttl_val;    /* MPLS label TTL value, 1-255 */
    BOOL            mpls_cw_disable; /* TRUE: Don't include MPLS CW, even if cfg'd in encap */
#endif /* VTSS_ARCH_JAGUAR_2 */
#if defined(VTSS_FEATURE_FRER)
    vtss_tce_rtag_t rtag;
#endif
} vtss_es0_action_t;

typedef enum
{
    VTSS_ES0_TYPE_VID,
    VTSS_ES0_TYPE_ISDX /* Jaguar/Serval only */
} vtss_es0_type_t;

/* ES0 key */
typedef struct {
    vtss_port_no_t  port_no;    /* Egress port number or VTSS_PORT_NO_NONE */
    vtss_es0_type_t type;       /* Jaguar/Serval only */
    vtss_vcap_bit_t isdx_neq0;  /* Jaguar/Serval only */
    vtss_port_no_t  rx_port_no; /* Ingress port number or VTSS_PORT_NO_NONE */
    BOOL            vid_any;    /* Match any vid */
    BOOL            vsi_enable; /* Jaguar-2: VSI enable */
    u16             vsi;        /* Jaguar-2: VSI */

    union {
        struct {
            vtss_vid_t     vid;
            vtss_vcap_u8_t pcp;
        } vid;

        struct {
            BOOL           isdx_enable; /* Jaguar-2 */
            u16            isdx;
            vtss_vcap_u8_t pcp;
        } isdx;
    } data;
} vtss_es0_key_t;

/* ES0 entry */
typedef struct {
    vtss_es0_action_t action;
    vtss_es0_key_t    key;
} vtss_es0_entry_t;

#define VTSS_ES0_FLAG_MASK_PORT  0x000000ff /* Flags related to ES0 egress port */
#define VTSS_ES0_FLAG_MASK_NNI   0x0000ff00 /* Flags related to ES0 NNI port */

#define VTSS_ES0_FLAG_OT_UVID    0x00000001 /* Use port UVID for outer tag */
#define VTSS_ES0_FLAG_OT_TPID    0x00000002 /* Use port TPID for outer tag */
#define VTSS_ES0_FLAG_OT_PCP     0x00000004 /* Use port PCP for outer tag */
#define VTSS_ES0_FLAG_OT_DEI     0x00000008 /* Use port DEI for outer tag */
#define VTSS_ES0_FLAG_IT_UVID    0x00000010 /* Use port UVID for inner tag */
#define VTSS_ES0_FLAG_IT_TPID    0x00000020 /* Use port TPID for inner tag */
#define VTSS_ES0_FLAG_IT_PCP     0x00000040 /* Use port PCP for inner tag */
#define VTSS_ES0_FLAG_IT_DEI     0x00000080 /* Use port DEI for inner tag */
#define VTSS_ES0_FLAG_PCP_MAP    0x00000100 /* Use mapped PCP for ECE */
#define VTSS_ES0_FLAG_MAP_OT_PCP 0x00010000 /* Map outer tag PCP */
#define VTSS_ES0_FLAG_MAP_OT_DEI 0x00020000 /* Map outer tag DEI */
#define VTSS_ES0_FLAG_MAP_IT_PCP 0x00040000 /* Map inner tag PCP */
#define VTSS_ES0_FLAG_MAP_IT_DEI 0x00080000 /* Map inner tag DEI */
#define VTSS_ES0_FLAG_MAP_ID_TC  0x00100000 /* MPLS TC egress map ID valid */

/* Combined VLAN/QoS flags */
#define VTSS_ES0_FLAG_OT_VLAN    (VTSS_ES0_FLAG_OT_UVID | VTSS_ES0_FLAG_OT_TPID)
#define VTSS_ES0_FLAG_OT_QOS     (VTSS_ES0_FLAG_OT_PCP | VTSS_ES0_FLAG_OT_DEI)
#define VTSS_ES0_FLAG_IT_VLAN    (VTSS_ES0_FLAG_IT_UVID | VTSS_ES0_FLAG_IT_TPID)
#define VTSS_ES0_FLAG_IT_QOS     (VTSS_ES0_FLAG_IT_PCP | VTSS_ES0_FLAG_IT_DEI)

/* Combined flags for using egress mappings on inner/outer tag PCP/DEI */
#define VTSS_ES0_FLAG_MAP_ID_OT  (VTSS_ES0_FLAG_MAP_OT_PCP | VTSS_ES0_FLAG_MAP_OT_DEI)
#define VTSS_ES0_FLAG_MAP_ID_IT  (VTSS_ES0_FLAG_MAP_IT_PCP | VTSS_ES0_FLAG_MAP_IT_DEI)

/* ES0 data */
typedef struct {
    vtss_es0_entry_t *entry;
    u32              flags;
    u8               prio;      /* ECE priority */
    vtss_port_no_t   port_no;   /* Egress port number */
    vtss_vid_t       vid;       /* Classified VID */
    vtss_port_no_t   nni;       /* NNI port affecting ES0 entry for UNI port */
    u16              map_id_ot; /* Outer tag egress QoS map ID */
    u16              map_id_it; /* Inner tag egress QoS map ID */
#if defined(VTSS_FEATURE_MPLS) && defined(VTSS_ARCH_JAGUAR_2)
    u16              mpls_encap_idx; /* MPLS encapsulation index. 0 if unused */
#endif /* VTSS_FEATURE_MPLS */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
    u16              esdx;      /* Egress statistics */
#endif
#if defined(VTSS_FEATURE_XFLOW)
    vtss_eflow_id_t  flow_id;
#endif
#if !defined(VTSS_ARCH_LUTON26)
    vtss_es0_sel_t   ot;
    vtss_es0_sel_t   it;
#endif
} vtss_es0_data_t;
#endif /* VTSS_FEATURE_ES0 */

/* VCAP data */
typedef struct {
    vtss_vcap_key_size_t key_size;   /* Key size */
    union {
#if defined(VTSS_FEATURE_IS0)
        vtss_is0_data_t is0;
#endif /* VTSS_FEATURE_IS0 */
#if defined(VTSS_FEATURE_IS1) || defined(VTSS_FEATURE_CLM)
        vtss_is1_data_t is1;
#endif /* VTSS_FEATURE_IS1/CLM */
#if defined(VTSS_FEATURE_LPM)
        vtss_lpm_data_t lpm;
#endif /* VTSS_FEATURE_LPM */
#if defined(VTSS_FEATURE_IS2)
        vtss_is2_data_t is2;
#endif /* VTSS_FEATURE_IS2 */
#if defined(VTSS_FEATURE_ES0)
        vtss_es0_data_t es0;
#endif /* VTSS_FEATURE_ES0 */
    } u;
#if defined(VTSS_ARCH_JAGUAR_2)
    BOOL port_hit, looped, masqueraded; /* Copy of IS1 key values to be used for clm_update_masq_hit_ena */
#endif /* VTSS_ARCH_JAGUAR_2 */
} vtss_vcap_data_t;

/* VCAP entry */
typedef struct vtss_vcap_entry_t {
    struct vtss_vcap_entry_t *next; /* Next in list */
    vtss_vcap_user_t         user;  /* User */
    vtss_vcap_id_t           id;    /* Entry ID */
    vtss_vcap_data_t         data;  /* Entry data */
    void                     *copy; /* Entry copy. Points to a copy of entry key/action (or NULL if not needed). */
} vtss_vcap_entry_t;

/* VCAP rule index */
typedef struct {
    u32                  row;      /* TCAM row */
    u32                  col;      /* TCAM column */
    vtss_vcap_key_size_t key_size; /* Rule key size */
} vtss_vcap_idx_t;

typedef struct {
    u32 count;     /* Actual number */
    u32 max_count; /* Maximum number */
} vtss_vcap_count_t;

#if defined(VTSS_FEATURE_VCAP_SUPER)
/* VCAP super object */
typedef struct {
    vtss_vcap_type_t  block_type[VTSS_VCAP_SUPER_BLK_CNT];
    vtss_rc           (* block_map)(struct vtss_state_s *vtss_state, u32 block, vtss_vcap_type_t type);
    vtss_rc           (* block_move)(struct vtss_state_s *vtss_state, u32 block, BOOL up);
    u32               row_count; /* Number of rows in one block */
    vtss_vcap_count_t block;
    u32               max_rule_count; /* Maximum number of rules */
    u32               rule_count;     /* Actual number of rules */
    vtss_vcap_entry_t table[VTSS_VCAP_SUPER_RULE_CNT]; /* Table */
    vtss_vcap_entry_t *free;          /* Free entries */
} vtss_vcap_super_obj_t;
#endif /* VTSS_FEATURE_VCAP_SUPER */

/* VCAP object */
typedef struct {
    /* VCAP data */
    u32               max_count;      /* Maximum number of rows */
    u32               count;          /* Actual number of rows */
    u32               max_rule_count; /* Maximum number of rules */
    u32               rule_count;     /* Actual number of rules */
    u32               key_count[VTSS_VCAP_KEY_SIZE_MAX]; /* Actual number of rule per key */
    vtss_vcap_entry_t *used;          /* Used entries */
    vtss_vcap_entry_t *free;          /* Free entries */
    const char        *name;          /* VCAP name for debugging */
    vtss_vcap_type_t  type;           /* VCAP type */

    /* VCAP methods */
    vtss_rc (* entry_get)(struct vtss_state_s *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear);
    vtss_rc (* entry_add)(struct vtss_state_s *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *data, u32 counter);
    vtss_rc (* entry_del)(struct vtss_state_s *vtss_state, vtss_vcap_idx_t *idx);
    vtss_rc (* entry_move)(struct vtss_state_s *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up);

#if defined(VTSS_FEATURE_VCAP_SUPER)
    vtss_vcap_super_obj_t *vcap_super;
#endif /* VTSS_FEATURE_VCAP_SUPER */
} vtss_vcap_obj_t;

/* Special VCAP ID used to add last in list */
#define VTSS_VCAP_ID_LAST 0

/* Special VCAP ID used to add before entry with greater ID */
#define VTSS_VCAP_ID_GT   0xffffffffffffffff

/* VCAP ranges */
#define VTSS_VCAP_RANGE_CHK_CNT 8
#define VTSS_VCAP_RANGE_CHK_NONE 0xffffffff

/* VCAP range checker type */
typedef enum {
    VTSS_VCAP_RANGE_TYPE_IDLE,   /* Unused */
    VTSS_VCAP_RANGE_TYPE_SPORT,  /* UDP/TCP source port */
    VTSS_VCAP_RANGE_TYPE_DPORT,  /* UDP/TCP destination port */
    VTSS_VCAP_RANGE_TYPE_SDPORT, /* UDP/TCP source/destination port */
    VTSS_VCAP_RANGE_TYPE_VID,    /* VLAN ID */
    VTSS_VCAP_RANGE_TYPE_DSCP    /* DSCP */
} vtss_vcap_range_chk_type_t;

/* VCAP range checker entry */
typedef struct {
    vtss_vcap_range_chk_type_t type;  /* Range type */
    u32                        count; /* Reference count */
    u32                        min;   /* Lower value of range */
    u32                        max;   /* Upper value of range */
} vtss_vcap_range_chk_t;

/* VCAP range checker table */
typedef struct {
    vtss_vcap_range_chk_t entry[VTSS_VCAP_RANGE_CHK_CNT];
} vtss_vcap_range_chk_table_t;

#if defined(VTSS_FEATURE_IS0)
/* Number of IS0 rules */
#define VTSS_SRVL_IS0_CNT 768  /* Half entries */
#define VTSS_IS0_CNT      VTSS_SRVL_IS0_CNT

/* IS0 information */
typedef struct {
    vtss_vcap_obj_t   obj;                 /* Object */
    vtss_vcap_entry_t table[VTSS_IS0_CNT]; /* Table */
#if defined(VTSS_OPT_WARM_START)
    vtss_is0_entry_t  copy[VTSS_IS0_CNT];  /* Copy of entries */
#endif /* VTSS_OPT_WARM_START */
} vtss_is0_info_t;
#endif /* VTSS_FEATURE_IS0 */

#if defined(VTSS_FEATURE_IS1)
/* Number of IS1 rules */
#define VTSS_L26_IS1_CNT  256
#define VTSS_SRVL_IS1_CNT 256  /* Quarter entries */

#if defined(VTSS_ARCH_OCELOT)
#define VTSS_IS1_CNT      VTSS_SRVL_IS1_CNT
#elif defined(VTSS_ARCH_LAN966X)
#if defined(VTSS_ARCH_LAN966X_FPGA)
#define VTSS_LAN966X_IS1_CNT (16 * 4)
#else
#define VTSS_LAN966X_IS1_CNT (192 * 4)
#endif
#define VTSS_IS1_CNT VTSS_LAN966X_IS1_CNT
#else
#define VTSS_IS1_CNT      VTSS_L26_IS1_CNT
#endif

/* IS1 information */
typedef struct {
    vtss_vcap_obj_t   obj;                 /* Object */
    vtss_vcap_entry_t table[VTSS_IS1_CNT]; /* Table */
#if defined(VTSS_OPT_WARM_START) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    vtss_is1_entry_t  copy[VTSS_IS1_CNT];  /* Copy of entries */
#endif /* VTSS_OPT_WARM_START */
} vtss_is1_info_t;
#endif /* VTSS_FEATURE_IS1 */

#if defined(VTSS_FEATURE_CLM)
/* CLM information */
typedef struct {
    vtss_vcap_obj_t obj; /* Object */
} vtss_clm_info_t;
#endif /* VTSS_FEATURE_CLM */

#if defined(VTSS_FEATURE_LPM)
/* LPM information */
typedef struct {
    vtss_vcap_obj_t obj; /* Object */
} vtss_lpm_info_t;
#endif /* VTSS_FEATURE_LPM */

#if defined(VTSS_FEATURE_IS2)
/* Number of IS2 rules */
#define VTSS_L26_IS2_CNT  256
#define VTSS_SRVL_IS2_CNT 256  /* Quarter entries */
#define VTSS_JR1_IS2_CNT  512
#define VTSS_MAS_IS2_CNT  32

#if defined(VTSS_ARCH_OCELOT)
#define VTSS_IS2_CNT      VTSS_SRVL_IS2_CNT
#elif defined(VTSS_ARCH_LUTON26)
#define VTSS_IS2_CNT      VTSS_L26_IS2_CNT
#elif defined(VTSS_ARCH_LAN966X)
#if defined(VTSS_ARCH_LAN966X_FPGA)
#define VTSS_LAN966X_IS2_CNT (16 * 4)
#else
#define VTSS_LAN966X_IS2_CNT (64 * 4)
#endif
#define VTSS_IS2_CNT      VTSS_LAN966X_IS2_CNT
#elif defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_IS2_CNT      0 /* VCAP_SUPER is used */
#define VTSS_ACL_CNT_SIZE 4096
#elif defined(VTSS_ARCH_SPARX5)
#define VTSS_IS2_CNT      0 /* VCAP_SUPER is used */
#define VTSS_ACL_CNT_SIZE 4096 /* IS2_A/IS2_B */
#define VTSS_ES2_CNT_SIZE 2048 /* ES2 */
#endif /* VTSS_ARCH_OCELOT */

/* IS2 information */
typedef struct {
    vtss_vcap_obj_t   obj;                 /* Object */
    vtss_vcap_entry_t table[VTSS_IS2_CNT]; /* Table */
#if defined(VTSS_OPT_WARM_START)
    vtss_is2_entry_t  copy[VTSS_IS2_CNT];  /* Copy of entries */
#endif /* VTSS_OPT_WARM_START */
} vtss_is2_info_t;
#endif /* VTSS_FEATURE_IS2 */

#if defined(VTSS_FEATURE_ES0)
#define VTSS_L26_ES0_CNT  256

#define VTSS_SRVL_ES0_CNT 256

#if defined(VTSS_ARCH_SERVAL_T)
#define VTSS_JR2_ES0_CNT  512
#else
#define VTSS_JR2_ES0_CNT  4096
#endif /* VTSS_ARCH_SERVAL_T */

#if defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_ES0_CNT VTSS_JR2_ES0_CNT
#elif defined(VTSS_ARCH_OCELOT)
#define VTSS_ES0_CNT VTSS_SRVL_ES0_CNT
#elif defined(VTSS_ARCH_LAN966X)
#if defined(VTSS_ARCH_LAN966X_FPGA)
#define VTSS_LAN966X_ES0_CNT 16
#else
#define VTSS_LAN966X_ES0_CNT 256
#endif
#define VTSS_ES0_CNT VTSS_LAN966X_ES0_CNT
#elif defined(VTSS_ARCH_SPARX5)
#define VTSS_FA_ES0_CNT 4096
#define VTSS_ES0_CNT    VTSS_FA_ES0_CNT
#else
#define VTSS_ES0_CNT VTSS_L26_ES0_CNT
#endif

/* ES0 information */
typedef struct {
    vtss_vcap_obj_t   obj;                 /* Object */
    vtss_vcap_entry_t table[VTSS_ES0_CNT]; /* Table */
#if defined(VTSS_OPT_WARM_START)
    vtss_es0_entry_t  copy[VTSS_ES0_CNT];  /* Copy of entries */
#endif /* VTSS_OPT_WARM_START */
} vtss_es0_info_t;
#endif /* VTSS_FEATURE_ES0 */

#if defined(VTSS_FEATURE_ES2)
#define VTSS_FA_ES2_CNT 2048 /* 1024 rows allowing 2048 half rules */
#define VTSS_ES2_CNT    VTSS_FA_ES2_CNT

/* ES2 information */
typedef struct {
    vtss_vcap_obj_t   obj;                 /* Object */
    vtss_vcap_entry_t table[VTSS_ES2_CNT]; /* Table */
#if defined(VTSS_OPT_WARM_START)
    vtss_es0_entry_t  copy[VTSS_ES2_CNT];  /* Copy of entries */
#endif /* VTSS_OPT_WARM_START */
} vtss_es2_info_t;
#endif /* VTSS_FEATURE_ES2 */

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
typedef struct {
    BOOL dmac_dip[3]; /* Aggregated dmac_dip flag - one per IS1 lookup */
} vtss_dmac_dip_conf_t;
#endif /* VTSS_ARCH_OCELOT */

typedef struct {
    /* CIL function pointers */
    vtss_rc (* range_commit)(struct vtss_state_s *vtss_state);
#if defined(VTSS_FEATURE_CLM)
    vtss_rc (* clm_entry_update)(struct vtss_state_s *vtss_state,
                                 vtss_vcap_type_t type, vtss_vcap_idx_t *idx, vtss_is1_data_t *is1);
    vtss_rc (* clm_entry_update_masq_hit_ena)(struct vtss_state_s *vtss_state,
                                             vtss_vcap_type_t type, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, BOOL enable);
#endif /* VTSS_FEATURE_CLM */
#if defined(VTSS_FEATURE_IS1)
    vtss_rc (* is1_entry_update)(struct vtss_state_s *vtss_state,
                                 vtss_vcap_idx_t *idx, vtss_is1_action_t *act);
#endif
#if defined(VTSS_FEATURE_IS2)
    vtss_rc (* is2_entry_update)(struct vtss_state_s *vtss_state,
                                 vtss_vcap_idx_t *idx, vtss_is2_data_t *is2);
#endif
#if defined(VTSS_FEATURE_ES0)
    vtss_rc (* es0_entry_update)(struct vtss_state_s *vtss_state,
                                 vtss_vcap_idx_t *idx, vtss_es0_data_t *es0);
    vtss_rc (* es0_esdx_update)(struct vtss_state_s *vtss_state,
                                const u16 idx_old,
                                const u16 idx_new);
#if defined(VTSS_FEATURE_XFLOW)
    vtss_rc (* es0_eflow_update)(struct vtss_state_s *vtss_state,
                                 const vtss_eflow_id_t flow_id);
#endif
#endif /* VTSS_FEATURE_ES0 */
    vtss_rc (* acl_policer_set)(struct vtss_state_s *vtss_state,
                                const vtss_acl_policer_no_t policer_no);
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    vtss_rc (* acl_sip_set)(struct vtss_state_s *vtss_state,
                            const vtss_acl_sip_idx_t idx);
#endif
    vtss_rc (* acl_port_set)(struct vtss_state_s *vtss_state,
                             const vtss_port_no_t port_no);
    vtss_rc (* acl_port_counter_get)(struct vtss_state_s *vtss_state,
                                     const vtss_port_no_t     port_no,
                                     vtss_acl_port_counter_t  *const counter);
    vtss_rc (* acl_port_counter_clear)(struct vtss_state_s *vtss_state,
                                       const vtss_port_no_t     port_no);
    vtss_rc (* acl_ace_add)(struct vtss_state_s *vtss_state,
                            const vtss_ace_id_t  ace_id,
                            const vtss_ace_t     *const ace);
    vtss_rc (* acl_ace_del)(struct vtss_state_s *vtss_state,
                            const vtss_ace_id_t  ace_id);
    vtss_rc (* acl_ace_counter_get)(struct vtss_state_s *vtss_state,
                                    const vtss_ace_id_t  ace_id,
                                    vtss_ace_counter_t   *const counter);
    vtss_rc (* acl_ace_counter_clear)(struct vtss_state_s *vtss_state,
                                      const vtss_ace_id_t  ace_id);
#if defined(VTSS_ARCH_LUTON26)
    vtss_rc (* acl_ace_status_get)(struct vtss_state_s *vtss_state,
                                   const vtss_ace_id_t ace_id,
                                   vtss_ace_status_t   *const status);
#endif /* VTSS_ARCH_LUTON26 */
#if defined(VTSS_FEATURE_HACL)
    vtss_rc (* hace_add)(struct vtss_state_s *vtss_state,
                         const vtss_hacl_type_t type,
                         const vtss_ace_id_t ace_id_next,
                         const vtss_hace_t *const hace);
    vtss_rc (* hace_del)(struct vtss_state_s *vtss_state,
                         const vtss_hacl_type_t type,
                         const vtss_ace_id_t ace_id);
    vtss_rc (* hace_counter_get)(struct vtss_state_s *vtss_state,
                                 const vtss_hacl_type_t type,
                                 const vtss_ace_id_t ace_id,
                                 vtss_ace_counter_t *const counter);
    vtss_rc (* hace_counter_clear)(struct vtss_state_s *vtss_state,
                                   const vtss_hacl_type_t type,
                                   const vtss_ace_id_t ace_id);
#endif /* VTSS_FEATURE_HACL */

    /* Configuration/state */
    vtss_vcap_range_chk_table_t   range;
    u32                           counter[2]; /* Multi-chip support */
#if defined(VTSS_FEATURE_VCAP_SUPER)
    vtss_vcap_super_obj_t         vcap_super;
#endif /* VTSS_FEATURE_VCAP_SUPER */
#if defined(VTSS_FEATURE_IS0)
    vtss_is0_info_t               is0;
#endif /* VTSS_FEATURE_IS0 */
#if defined(VTSS_FEATURE_IS1)
    vtss_is1_info_t               is1;
#endif /* VTSS_FEATURE_IS1 */
#if defined(VTSS_FEATURE_IS2)
    vtss_is2_info_t               is2;
#endif /* VTSS_FEATURE_IS2 */
#if defined(VTSS_FEATURE_IS2_B)
    vtss_is2_info_t               is2_b;
#endif /* VTSS_FEATURE_IS2_B */
#if defined(VTSS_FEATURE_ES0)
    vtss_es0_info_t               es0;
#endif /* VTSS_FEATURE_ES0 */
#if defined(VTSS_FEATURE_ES2)
    vtss_es2_info_t               es2;
#endif /* VTSS_FEATURE_ES2 */
#if defined(VTSS_FEATURE_CLM)
    vtss_clm_info_t               clm_a;
    vtss_clm_info_t               clm_b;
    vtss_clm_info_t               clm_c;
#endif /* VTSS_FEATURE_CLM */
#if defined(VTSS_FEATURE_LPM)
    vtss_clm_info_t               lpm;
#endif /* VTSS_FEATURE_LPM */
    vtss_vcap_user_t              acl_user;
    vtss_acl_policer_conf_t       acl_policer_conf[VTSS_ACL_POLICERS];
#if defined(VTSS_ARCH_LUTON26)
    vtss_policer_alloc_t          acl_policer_alloc[VTSS_ACL_POLICERS];
#endif /* VTSS_ARCH_LUTON26 */
    vtss_acl_port_conf_t          acl_old_port_conf;
    vtss_acl_port_conf_t          acl_port_conf[VTSS_PORT_ARRAY_SIZE];
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    vtss_vcap_port_conf_t         port_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_vcap_port_conf_t         port_conf_old;
    vtss_dmac_dip_conf_t          dmac_dip_conf[VTSS_PORT_ARRAY_SIZE];/* Aggregated dmac_dip flag - per port per IS1 lookup */
#endif
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    vtss_acl_sip_conf_t           acl_sip_table[VTSS_ACL_SIP_CNT];
    u8 acl_cnt_alloc[VTSS_BF_SIZE(VTSS_ACL_CNT_SIZE)];
#endif
#if defined(VTSS_ARCH_SPARX5)
    vtss_vcap_range_chk_table_t   is2_range;
    vtss_vcap_range_chk_table_t   es2_range;
    u8 is2b_cnt_alloc[VTSS_BF_SIZE(VTSS_ACL_CNT_SIZE)];
    u8 es2_cnt_alloc[VTSS_BF_SIZE(VTSS_ES2_CNT_SIZE)];
#endif
} vtss_vcap_state_t;

vtss_rc vtss_vcap_inst_create(struct vtss_state_s *vtss_state);
vtss_rc vtss_vcap_restart_sync(struct vtss_state_s *vtss_state);

void vtss_cmn_res_init(vtss_res_t *res);
vtss_rc vtss_cmn_vcap_res_check(vtss_vcap_obj_t *obj, vtss_res_chg_t *chg);
vtss_rc vtss_cmn_res_check(struct vtss_state_s *vtss_state, vtss_res_t *res);

BOOL vtss_vcap_udp_tcp_rule(const vtss_vcap_u8_t *proto);
vtss_rc vtss_vcap_range_alloc(vtss_vcap_range_chk_table_t *range_chk_table,
                              u32 *range,
                              vtss_vcap_range_chk_type_t type,
                              u32 min,
                              u32 max);
vtss_rc vtss_vcap_range_free(vtss_vcap_range_chk_table_t *range_chk_table,
                             u32 range);
vtss_rc vtss_vcap_udp_tcp_range_alloc(vtss_vcap_range_chk_table_t *range_chk_table,
                                      u32 *range,
                                      const vtss_vcap_udp_tcp_t *port,
                                      BOOL sport);
BOOL vtss_vcap_vr_rng2vm(vtss_vcap_vr_t *vr);
vtss_rc vtss_vcap_vr_alloc(vtss_vcap_range_chk_table_t *range_chk_table,
                           u32 *range,
                           vtss_vcap_range_chk_type_t type,
                           vtss_vcap_vr_t *vr);
vtss_rc vtss_vcap_range_commit(struct vtss_state_s *vtss_state, vtss_vcap_range_chk_table_t *range_new);
u32 vtss_vcap_key_rule_count(vtss_vcap_key_size_t key_size);
char *vtss_vcap_id_txt(struct vtss_state_s *vtss_state, vtss_vcap_id_t id);
vtss_rc vtss_vcap_lookup(struct vtss_state_s *vtss_state,
                         vtss_vcap_obj_t *obj, int user, vtss_vcap_id_t id,
                         vtss_vcap_data_t *data, vtss_vcap_idx_t *idx);
u32 vtss_vcap_count_get(vtss_vcap_obj_t *obj, int user);
vtss_rc vtss_vcap_del(struct vtss_state_s *vtss_state, vtss_vcap_obj_t *obj, int user, vtss_vcap_id_t id);
vtss_rc vtss_vcap_add(struct vtss_state_s *vtss_state, vtss_vcap_obj_t *obj, int user, vtss_vcap_id_t id,
                      vtss_vcap_id_t ins_id, vtss_vcap_data_t *data, BOOL dont_add);
vtss_rc vtss_vcap_get_next_id(vtss_vcap_obj_t *obj, int user1, int user2,
                              vtss_vcap_id_t id, vtss_vcap_id_t *ins_id);
#if defined(VTSS_FEATURE_VCAP_SUPER)
const char *vtss_vcap_type_txt(vtss_vcap_type_t type);
#endif /* VTSS_FEATURE_VCAP_SUPER */
#if defined(VTSS_FEATURE_IS0)
void vtss_vcap_is0_init(vtss_vcap_data_t *data, vtss_is0_entry_t *entry);
void vtss_vcap_debug_print_is0(struct vtss_state_s *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_IS0 */
#if defined(VTSS_FEATURE_IS1) || defined(VTSS_FEATURE_CLM)
vtss_vcap_obj_t *vtss_vcap_is1_obj_get(struct vtss_state_s *vtss_state);
void vtss_vcap_is1_init(vtss_vcap_data_t *data, vtss_is1_entry_t *entry);
void vtss_vcap_debug_print_is1(struct vtss_state_s *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info);
vtss_rc vtss_vcap_is1_update(struct vtss_state_s *vtss_state, vtss_is1_action_t *act);
#endif /* VTSS_FEATURE_IS1/CLM */
#if defined(VTSS_FEATURE_CLM)
void vtss_vcap_debug_print_clm_a(struct vtss_state_s *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
void vtss_vcap_debug_print_clm_b(struct vtss_state_s *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
void vtss_vcap_debug_print_clm_c(struct vtss_state_s *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
vtss_rc vtss_vcap_clm_update(struct vtss_state_s *vtss_state, const vtss_qos_egress_map_id_t id);
vtss_rc vtss_vcap_clm_update_masq_hit_ena(struct vtss_state_s *vtss_state,
                                          vtss_vcap_obj_t *obj, int user, vtss_vcap_id_t id, BOOL enable);
#endif /* VTSS_FEATURE_CLM */
#if defined(VTSS_FEATURE_IS2)
void vtss_vcap_is2_init(vtss_vcap_data_t *data, vtss_is2_entry_t *entry);
vtss_rc vtss_vcap_is2_update(struct vtss_state_s *vtss_state);
void vtss_vcap_debug_print_is2(struct vtss_state_s *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_IS2 */
#if defined(VTSS_FEATURE_ES0)
void vtss_vcap_es0_init(vtss_vcap_data_t *data, vtss_es0_entry_t *entry);
void vtss_cmn_es0_action_get(struct vtss_state_s *vtss_state, vtss_es0_data_t *es0);
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
vtss_rc vtss_vcap_es0_emap_update(struct vtss_state_s *vtss_state, vtss_qos_egress_map_id_t map_id);
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */
vtss_rc vtss_vcap_es0_update(struct vtss_state_s *vtss_state,
                             const vtss_port_no_t port_no, u16 flags);
void vtss_vcap_debug_print_es0(struct vtss_state_s *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_ES0 */
const char *vtss_vcap_key_size2txt(vtss_vcap_key_size_t key_size);
const char *vtss_vcap_key_type2txt(vtss_vcap_key_type_t key_type);
vtss_vcap_key_size_t vtss_vcap_key_type2size(vtss_vcap_key_type_t key_type);
void vtss_vcap_debug_print_range_checkers(struct vtss_state_s *vtss_state,
                                          const vtss_debug_printf_t pr,
                                          const vtss_debug_info_t   *const info);

vtss_rc vtss_cmn_ace_add(struct vtss_state_s *vtss_state,
                         const vtss_ace_id_t ace_id, const vtss_ace_t *const ace);
vtss_rc vtss_cmn_ace_del(struct vtss_state_s *vtss_state, const vtss_ace_id_t ace_id);
vtss_rc vtss_cmn_ace_counter_get(struct vtss_state_s *vtss_state,
                                 const vtss_ace_id_t ace_id, vtss_ace_counter_t *const counter);
vtss_rc vtss_cmn_ace_counter_clear(struct vtss_state_s *vtss_state, const vtss_ace_id_t ace_id);
char *vtss_acl_policy_no_txt(vtss_acl_policy_no_t policy_no, char *buf);
void vtss_vcap_debug_print_acl(struct vtss_state_s *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info);

#endif /* VTSS_FEATURE_VCAP */

#endif /* _VTSS_VCAP_STATE_H_ */
