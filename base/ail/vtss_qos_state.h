// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_QOS_STATE_H_
#define _VTSS_QOS_STATE_H_

#if defined(VTSS_FEATURE_QOS)

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)

#define VTSS_QOS_DWRR_COST_BIT_WIDTH 5

#endif /* defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) */

#if defined(VTSS_ARCH_LUTON26)
#define VTSS_L26_POLICER_CNT 256

/** \brief Shared policer users */
typedef enum {
    VTSS_POLICER_USER_NONE,    /**< Policer is free */
    VTSS_POLICER_USER_DISCARD, /**< Discard Policer */
    VTSS_POLICER_USER_PORT,    /**< Port Policer */
    VTSS_POLICER_USER_QUEUE,   /**< Queue Policer */
    VTSS_POLICER_USER_ACL,     /**< ACL Policer */
    VTSS_POLICER_USER_EVC,     /**< EVC Policer */
    VTSS_POLICER_USER_MEP,     /**< Up-MEP Policer */

    /* Number of users, must be last field */
    VTSS_POLICER_USER_CNT
} vtss_policer_user_t;

/* Policer allocation */
typedef struct {
    u16 count;   /* Reference count */
    u16 policer; /* Policer index */
} vtss_policer_alloc_t;

/* Policer types used for IS2 entries */
#define VTSS_L26_POLICER_NONE 0
#define VTSS_L26_POLICER_ACL  1
#define VTSS_L26_POLICER_EVC  2

#endif /* VTSS_ARCH_LUTON26 */

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
typedef struct {
    BOOL disable;    /* Disable policer */
    BOOL frame_rate; /* Enable frame rate policing (always single bucket) */
    BOOL dual;       /* Enable dual leaky bucket mode */
    BOOL data_rate;  /* Enable data rate policing */
    u32  cir;        /* CIR in kbps/fps (ignored in single bucket mode) */
    u32  cbs;        /* CBS in bytes/frames (ignored in single bucket mode) */
    u32  eir;        /* EIR (PIR) in kbps/fps */
    u32  ebs;        /* EBS (PBS) in bytes/frames */
    BOOL cf;         /* Coupling flag (ignored in single bucket mode) */
    BOOL drop_yellow;
    vtss_opt_bool_t mark_all_red;
} vtss_policer_conf_t;

typedef struct {
    u32 rate_pwm;       /**< Target relative rate of CIR PWM Serval fix. Unit: kbps. Valid values are 0, 100, 200, and 300. Use 0 to disable the CIR PWM Serval fix */
    u32 rate_pwm_high;  /**< High rate of CIR PWM Serval fix.            Unit: 100 kbps */
    i32 rate_pwm_error; /**< Current rate error of CIR PWM Serval fix. */
    u32 level_pwm;      /**< CBS used by CIR PWM Serval fix.             Unit: 4096 bytes */
    u32 eir_pwm;        /**< Target relative rate of EIR PWM Serval fix. Unit: kbps. Valid values are 0, 100, 200, and 300. Use 0 to disable the EIR PWM Serval fix */
    u32 eir_pwm_high;   /**< High rate of EIR PWM Serval fix.            Unit: 100 kbps */
    i32 eir_pwm_error;  /**< Current rate error of EIR PWM Serval fix. */
    u32 ebs_pwm;        /**< EBS used by EIR PWM Serval fix.             Unit: 4096 bytes */
} vtss_shaper_calibrate_t;
#endif /* defined(VTSS_ARCH_OCELOT) */

/* SDX zero is reserved for non-service forwarding */
#if defined(VTSS_ARCH_OCELOT)
#define VTSS_SRVL_SDX_CNT 1022 /* SDX 1023 is reserved for CPU Tx operations */
#define VTSS_SDX_CNT VTSS_SRVL_SDX_CNT
#endif /* VTSS_ARCH_OCELOT */

#if defined(VTSS_ARCH_LAN966X) && !VTSS_OPT_LIGHT
#define VTSS_SDX_CNT      255
#define VTSS_EVC_POL_CNT  240 /* DLB policers (port/queue/ACL policers reserved) */
#define VTSS_EVC_STAT_CNT 256 /* ISDX/ESDX statistics */
#endif

#define VTSS_POL_STAT_NONE 0  /* The NO Policer/SDX statistics value */

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL_T)
#define VTSS_JR_SDX_CNT  511
#define VTSS_EVC_POL_CNT  512  /* EVC policers */
#define VTSS_EVC_STAT_CNT 1024 /* EVC statistics */
#else /* End VTSS_ARCH_SERVAL_T */
#define VTSS_JR_SDX_CNT  4095
#define VTSS_EVC_POL_CNT  4096 /* EVC policers */
#define VTSS_EVC_STAT_CNT 8192 /* EVC statistics */
#endif /* End VTSS_ARCH_JAGUAR_2 */
#if defined(VTSS_FEATURE_VOP)
#define VTSS_SDX_CNT VTSS_JR_SDX_CNT
#endif
#define VTSS_QUEUE_POL_IDX(port, queue) (VTSS_EVC_POL_CNT + (port * 8) + queue)
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5)
#define VTSS_QOS_INGRESS_MAP_ROWS 512                                     /**< Number of rows in hardware */
#else
#define VTSS_QOS_INGRESS_MAP_ROWS 256                                     /**< Number of rows in hardware */
#endif /* defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5) */

#define VTSS_QOS_INGRESS_MAP_IX_RESERVED (VTSS_QOS_INGRESS_MAP_ROWS - 10) /**< Start of area reserved at the end. Used in move operations */
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5)
#define VTSS_QOS_EGRESS_MAP_ROWS  512                                     /**< Number of rows in hardware */
#else
#define VTSS_QOS_EGRESS_MAP_ROWS  256                                     /**< Number of rows in hardware */
#endif /* defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5) */

#define VTSS_QOS_EGRESS_MAP_IX_RESERVED (VTSS_QOS_EGRESS_MAP_ROWS - 32)   /**< Start of area reserved at the end. Used in move operations */

/* Egress map action flags */
#define VTSS_QOS_EGRESS_MAP_ACTION_PCP     0x01
#define VTSS_QOS_EGRESS_MAP_ACTION_DEI     0x02
#define VTSS_QOS_EGRESS_MAP_ACTION_DSCP    0x04
#define VTSS_QOS_EGRESS_MAP_ACTION_PATH    0x08
#define VTSS_QOS_EGRESS_MAP_ACTION_MPLS_TC 0x10

#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP) || defined(VTSS_FEATURE_QOS_EGRESS_MAP)
/*********************************************************************************************************************************

Ingress and egress mapping uses two kind of tables for the administration of id's and indexes in hardware.

The id table (indexed by id) contains the mapping from id to [ix, res].
CLM has only one res(ource) whereas ES0 has two: Resource A and B.
ix is both the index in the ix table and the index bit 11:3 in CLM and ES0 actions.
See section 2.14.3 and 2.28.6 regarding mapping tables in the VSC7468 datasheet.
An unused id is indicated by setting ix to 0xfff (not shown in the figure below).

The ix table (indexed by ix) contains the mapping from ix to id, key to use for the mapping and eight bit flags.
The bit flags are currently only used in egress mapping in order to store the enabled actions.

The length of each entry in both the ix table and the hardware table can be derived from the key.
An unused ix is indicated by setting the id to 0xfff (not shown in the figure below).
The actual mapping configuration is only stored in the hardware table.

In the figure below, mappings have been added and deleted in the following sequence:
 Add id 3, key 1
 Add id 9, key 1
 Add id 6, key 2
 Del id 9

                Id table                          Ix table (res = 0)
                (index is id)                    (index is ix)
                 +----+-----+                     +----+-----+-------+
                 | ix | res |                     | id | key | flags |
                 +----+-----+                     +------------------+
              0  |    |     |                  0  |    |     |       |
              1  |    |     |                  1  |  3 |   1 |       | key2len(1) = 2 for ingress mapping
              2  |    |     |                  2  |    |     |       |
              3  |  1 |   0 |    (was id 9)+-> 3  |    |   1 |       | key2len(1) = 2 for ingress mapping
              4  |    |     |                  4  |    |     |       |
              5  |    |     |                  5  |  6 |   2 |       | key2len(2) = 8 for ingress mapping
              6  |  5 |   0 |                  6  |    |     |       |
              7  |    |     |                  7  |    |     |       |
              8  |    |     |                  8  |    |     |       |
(was ix 3)+-> 9  |    |     |                  9  |    |     |       |
             10  |    |     |                 10  |    |     |       |
             11  |    |     |                 11  |    |     |       |
                 |    |     |                 12  |    |     |       |
                 |    |     |        free +-> 13  |    |     |       |
                 |    |     |                 14  |    |     |       |
                 |    |     |                 15  |    |     |       |
                 |    |     |                     |    |     |       |
                 |    |     |                     |    |     |       |
                 |    |     |                     |    |     |       |
            ...  |    |     |                     |    |     |       |
            255  |    |     |                     |    |     |       |
                 +----+-----+                     |    |     |       |
                                                  |    |     |       |
                                                  |    |     |       |
                                                  |    |     |       |
                                             ...  |    |     |       |
                                reserved +-> 502  |    |     |       |
                                                  |    |     |       |
                                             ...  |    |     |       |
                                             511  |    |     |       |
                                                  +----+-----+-------+

The ix table is associated with a 'free' index, which always point to the next free index.

Delete:
 If an entry is deleted, the ix in the id table and the id in the ix table are set to 0xffff.
 If the entry was the last one, the 'free' index is decremented correspondingly.
 If not, the entry is now considered to be unused. The key is left unchanged in order to
 be able to traverse the list of entries. The index of the next entry is found as index of
 current entry + key2len(length).

Add:
 A new entry is added in the ix table in the following way:
 1) Use first unused entry with correct length, located before the 'free' index, or
 2) Use free space starting from the 'free' index and up to the reserved area, or
 3) Compact list (see below) and use free space as indicated by the 'free' index, or
 4) Return error: No more room for mapping!

Update:
 If the key does not change then the entries in both tables are reused.
 Otherwise an update is handled as an add followed by a delete.

Compact:
 When we try to add an entry and the ix table is full, the ix table is compacted.
 The unused entries are eliminated by traversing the table and if an unused entry
 is found, then the next used entry is copied to the unused entry's position.
 In this way, all used entries ripples towards a lower index.
 If an entry will have overlapping regions (the entry is moved less than its length),
 then the entry is first moved to a reserved area and then back to the original destination.
 This will prevent any disturbances in the traffic due to incomplete/partial table updates..
 In the example above, a compact operation will move id 6 in the ix table two times:
 First copy 8 entries from ix 5 to the reserved ares (ix 502), notify all users of id 6 that
 the index in hardware has changed to 502. Then copy the 8 entries from ix 502 to ix 3 and
 notify all users again.

The administration data structure contains function pointers that are installed at initialization time.
These functions handle the differences between ingress and egress.

*********************************************************************************************************************************/

typedef int     (*vtss_qos_map_key2len_t)(int key);
typedef vtss_rc (*vtss_qos_map_vcap_update_t)(struct vtss_state_s *vtss_state, const u16 id);
typedef vtss_rc (*vtss_qos_map_hw_update_t)(struct vtss_state_s *vtss_state, const u16 res, const u16 ix, const int len, const void *const map);
typedef vtss_rc (*vtss_qos_map_hw_copy_t)(struct vtss_state_s *vtss_state, const u16 res, const u16 src, const u16 dst, const int len);

#define VTSS_QOS_MAP_KEY_NONE      0xf  /**< Value to use for no key */
#define VTSS_QOS_MAP_RESOURCES       2  /**< Maximum number of resources supported */

typedef enum {
    VTSS_QOS_MAP_KIND_INGRESS,          /**< This is an ingress map */
    VTSS_QOS_MAP_KIND_EGRESS,           /**< This is an egress map */
} vtss_qos_map_kind_t;

typedef struct {
    u16 ix  : 12;                       /**< The associated map index in the hw tables. VTSS_QOS_MAP_ID_NONE if not in use */
    u16 res :  4;                       /**< The associated resource id. Resource A = 0, resource B = 1 */
} vtss_qos_map_id_entry_t;

typedef struct {
    vtss_qos_map_id_entry_t *entry;     /**< Array of entries, indexed by map id */
    u16                      entry_len; /**< Indicated the number of allocated entries above */
} vtss_qos_map_id_adm_t;

typedef struct {
    u16 id  : 12;                       /**< Id for this entry. Use VTSS_QOS_MAP_ID_NONE if not in use */
    u16 key :  4;                       /**< Key for this entry. Use VTSS_QOS_MAP_KEY_NONE if not in use */
    u8  flags;                          /**< Bit flags. Currently only used for storing of enabled actions in egress mapping */
} vtss_qos_map_ix_entry_t;

typedef struct {
    vtss_qos_map_ix_entry_t *entry;     /**< Array of entries, indexed by hw index */
    u16                      entry_len; /**< Indicated the number of allocated entries above */
    u16                      free;      /**< Start of free area */
    u16                      reserved;  /**< Start of reserved area (never changes after initialization) */
} vtss_qos_map_ix_adm_t;

typedef struct {
    char                       name[8];                    /**< "Ingress" or "Egress" */
    vtss_qos_map_kind_t        kind;                       /**< Kind of map */
    vtss_qos_map_id_adm_t      id;                         /**< Administration of map id table */
    vtss_qos_map_ix_adm_t      ix[VTSS_QOS_MAP_RESOURCES]; /**< Administration of map ix table(s) */
    vtss_qos_map_key2len_t     key2len;                    /**< Function for key to length conversion */
    vtss_qos_map_vcap_update_t vcap_update;                /**< Function for updating of vcap */
    vtss_qos_map_hw_update_t   hw_update;                  /**< Function for updating of map registers */
    vtss_qos_map_hw_copy_t     hw_copy;                    /**< Function for copying of map registers */
} vtss_qos_map_adm_t;

vtss_rc vtss_cmn_qos_map_add(struct vtss_state_s *vtss_state, vtss_qos_map_adm_t *adm, const u16 id, const int key, const u8 flags, const void *const map);
vtss_rc vtss_cmn_qos_map_del(struct vtss_state_s *vtss_state, vtss_qos_map_adm_t *adm, const u16 id);

#endif /* defined(VTSS_FEATURE_QOS_INGRESS_MAP) || defined(VTSS_FEATURE_QOS_EGRESS_MAP) */

#if defined(VTSS_FEATURE_QOS_HSCH_LEAK_LISTS)

#if defined(VTSS_ARCH_SERVAL_T)
#define VTSS_HSCH_LAYERS                        4 /**< Number of layers (L0, L1, L2 and QSCH) */
#define VTSS_HSCH_L0_SES                      416 /**< Number of scheduler elements in layer 0 */
#define VTSS_HSCH_L1_SES                       64 /**< Number of scheduler elements in layer 1 */
#define VTSS_HSCH_L2_SES                       15 /**< Number of scheduler elements in layer 2 */
#define VTSS_HSCH_L3_QSHPS (VTSS_HSCH_L0_SES * 2) /**< Number of queue shapers in layer 3 */
#elif defined(VTSS_ARCH_JAGUAR_2_B)
#define VTSS_HSCH_LAYERS                        3 /**< Number of layers (L0, L1 and L2) */
#define VTSS_HSCH_L0_SES                     4096 /**< Number of scheduler elements in layer 0 */
#define VTSS_HSCH_L1_SES                       64 /**< Number of scheduler elements in layer 1 */
#define VTSS_HSCH_L2_SES                       57 /**< Number of scheduler elements in layer 2 */
#elif defined(VTSS_ARCH_JAGUAR_2_C)
#define VTSS_HSCH_LAYERS                        4 /**< Number of layers (L0, L1, L2 and QSCH) */
#define VTSS_HSCH_L0_SES                     3400 /**< Number of scheduler elements in layer 0 */
#define VTSS_HSCH_L1_SES                       64 /**< Number of scheduler elements in layer 1 */
#define VTSS_HSCH_L2_SES                       57 /**< Number of scheduler elements in layer 2 */
#define VTSS_HSCH_L3_QSHPS (VTSS_HSCH_L0_SES * 2) /**< Number of queue shapers in layer 3 */
#elif defined(VTSS_ARCH_SPARX5)
// TBD_VK: Check the numbers below when the datasheet is ready.
#define VTSS_HSCH_LAYERS                        4 /**< Number of layers (L0, L1, L2 and QSCH) */
#define VTSS_HSCH_L0_SES                     5040 /**< Number of scheduler elements in layer 0 */
#define VTSS_HSCH_L1_SES                       64 /**< Number of scheduler elements in layer 1 */
#define VTSS_HSCH_L2_SES                       70 /**< Number of scheduler elements in layer 2 */
#define VTSS_HSCH_L3_QSHPS (VTSS_HSCH_L0_SES * 2) /**< Number of queue shapers in layer 3 */
#endif /* defined(VTSS_ARCH_SERVAL_T) */

#define VTSS_HSCH_LEAK_LISTS                    4 /**< Number of leak list groups per layer */

/* The bit rates below must be defined in increasing order */
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C)
#define VTSS_HSCH_MAX_RATE_GROUP_0        1024000 /**< Maximum bit rate for group 0 in kbps ( 1.024 Gbps) */
#define VTSS_HSCH_MAX_RATE_GROUP_1        1024000 /**< Maximum bit rate for group 1 in kbps ( 1.024 Gbps) */
#define VTSS_HSCH_MAX_RATE_GROUP_2        2560000 /**< Maximum bit rate for group 2 in kbps ( 2.56  Gbps) */
#define VTSS_HSCH_MAX_RATE_GROUP_3       12800000 /**< Maximum bit rate for group 3 in kbps (12.8   Gbps) */
#elif defined(VTSS_ARCH_SPARX5_CE)
// TBD_VK: Verify the target names and rate values for CE SKUs.
#   if defined(VTSS_CHIP_7538)
#   define VTSS_HSCH_MAX_RATE_GROUP_0      655355 /**< Maximum bit rate for group 0 in kbps ( 0.655 Gbps) */
#   define VTSS_HSCH_MAX_RATE_GROUP_1     1048568 /**< Maximum bit rate for group 1 in kbps ( 1.049 Gbps) */
#   define VTSS_HSCH_MAX_RATE_GROUP_2     6553550 /**< Maximum bit rate for group 2 in kbps ( 6.554 Gbps) */
#   define VTSS_HSCH_MAX_RATE_GROUP_3    10485680 /**< Maximum bit rate for group 3 in kbps (10.486 Gbps) */
#   else
#   define VTSS_HSCH_MAX_RATE_GROUP_0      655355 /**< Maximum bit rate for group 0 in kbps ( 0.655 Gbps) */
#   define VTSS_HSCH_MAX_RATE_GROUP_1     1048568 /**< Maximum bit rate for group 1 in kbps ( 1.049 Gbps) */
#   define VTSS_HSCH_MAX_RATE_GROUP_2     6553550 /**< Maximum bit rate for group 2 in kbps ( 6.554 Gbps) */
#   define VTSS_HSCH_MAX_RATE_GROUP_3    26214200 /**< Maximum bit rate for group 3 in kbps (26.214 Gbps) */
#   endif /* defined(VTSS_CHIP_7538) */
#elif defined(VTSS_ARCH_SPARX5)
#define VTSS_HSCH_MAX_RATE_GROUP_0        1048568 /**< Maximum bit rate for group 0 in kbps ( 1.049 Gbps) */
#define VTSS_HSCH_MAX_RATE_GROUP_1        2621420 /**< Maximum bit rate for group 1 in kbps ( 2.621 Gbps) */
#define VTSS_HSCH_MAX_RATE_GROUP_2       10485680 /**< Maximum bit rate for group 2 in kbps (10.486 Gbps) */
#define VTSS_HSCH_MAX_RATE_GROUP_3       26214200 /**< Maximum bit rate for group 3 in kbps (26.214 Gbps) */
#endif /* defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) */

/** \brief Leak Chain entry */
typedef struct {
    u32 prev    : 14; /**< Index of previous element in chain. A value equal to this element no. indicates this element is the head of chain */
    u32 next    : 14; /**< Index of next element in chain. A value equal to this element no. indicates this element is the end of the chain */
    u32 group   :  2; /**< Leak group that the element belongs to */
    u32 enabled :  1; /**< TRUE if entry is enabled */
    u32 unused  :  1; /**< Currently unused */
} vtss_qos_leak_entry_t;

/** \brief Leak Group */
typedef struct {
    vtss_bitrate_t        max_rate;   /**< The maximum supported bitrate in kbps for this leak group. Write at init, then read-only */
    vtss_bitrate_t        resolution; /**< Resolution for this leak group in kbps. Write at init, then read-only */
    u32                   leak_time;  /**< The value written to the LEAK_TIME register when leak group is in use. Write at init, then read-only */
    u16                   max_ses;    /**< Maximum allowed number of scheduler elements in leak list */
    u16                   cur_ses;    /**< Current number of scheduler elements in leak list */
    vtss_qos_leak_entry_t head;       /**< Index of first and last scheduler element in leak group list */
} vtss_qos_leak_group_t;

/** \brief Leak Layer */
typedef struct {
    vtss_qos_leak_group_t group[VTSS_HSCH_LEAK_LISTS]; /**< Per group data */
    vtss_qos_leak_entry_t *entry;                      /**< Pointer to allocation for this layer */
    u16                   entries;                     /**< Number of entries in this layer */
} vtss_qos_leak_layer_t;

/** \brief Leak Config */
typedef struct {
    vtss_qos_leak_layer_t layer[VTSS_HSCH_LAYERS];      /**< Per layer data */
    vtss_qos_leak_entry_t l0_alloc[VTSS_HSCH_L0_SES];   /**< Allocation of layer 0 entries. Only accessed through layer[0].entry above */
//  vtss_qos_leak_entry_t l1_alloc[VTSS_HSCH_L1_SES];   /**< Allocation of layer 1 entries. Currently not used */
    vtss_qos_leak_entry_t l2_alloc[VTSS_HSCH_L2_SES];   /**< Allocation of layer 2 entries. Only accessed through layer[2].entry above */
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5)
    vtss_qos_leak_entry_t l3_alloc[VTSS_HSCH_L3_QSHPS]; /**< Allocation of layer 3 (queue shaper) entries. Only accessed through layer[3].entry above */
#endif /* defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5) */
} vtss_qos_leak_conf_t;

#endif /* defined(VTSS_FEATURE_QOS_HSCH_LEAK_LISTS) */

#if defined(VTSS_FEATURE_QOS_TAS)
#if defined(VTSS_ARCH_SPARX5)
#define VTSS_TAS_NUMBER_OF_LISTS              (0x7F+1)
#define VTSS_TAS_NUMBER_OF_PROFILES           100
#define VTSS_TAS_NUMBER_OF_ENTRIES            (0x3FFF+1)
#define VTSS_TAS_NUMBER_OF_ENTRIES_PER_BLOCK  32    /* Number of entries per block. This is the minimum allocated number of entries for a list */
#define VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW     (VTSS_QOS_TAS_GCL_LEN_MAX / VTSS_TAS_NUMBER_OF_ENTRIES_PER_BLOCK)    /* Number of blocks per row. A list must be able to fit into one row. So a row must have blocks to contain the maximum GCL */
#define VTSS_TAS_NUMBER_OF_ENTRIES_PER_ROW    VTSS_QOS_TAS_GCL_LEN_MAX    /* Number of entries per row. This is also the maximum lengt of a list as a list mist be in one row */
#define VTSS_TAS_NUMBER_OF_ROWS               (VTSS_TAS_NUMBER_OF_ENTRIES/VTSS_TAS_NUMBER_OF_ENTRIES_PER_ROW)   /* Number of rows */
#endif

#if defined(VTSS_ARCH_LAN966X)
#define VTSS_TAS_NUMBER_OF_LISTS              (0x1F+1)
#define VTSS_TAS_NUMBER_OF_PROFILES           16
#define VTSS_TAS_NUMBER_OF_ENTRIES            (0xFFF+1)
#endif

typedef struct {
    BOOL in_use;
    BOOL inherit_profile;
    u32  entry_idx;         /* Point to the first list entry */
    u32  profile_idx;
    u32  hold_profile_idx;  /* Profile for FP hold MAC guard band */
} vtss_tas_list_t;

typedef struct {
    BOOL in_use;
} vtss_tas_list_entry;

typedef struct {
    BOOL            in_use;
    vtss_port_no_t  port_no;
} vtss_tas_profile_t;

typedef struct {
    BOOL in_use;
} vtss_tas_entry_block_t;

typedef struct {
    u16  in_use;
    u16  slot_size;
} vtss_tas_entry_row_t;

typedef struct {
    BOOL stop_ongoing;
    BOOL new_list_scheduled;
    u32 curr_list_idx;
    u32 trunk_list_idx;
    u32 next_list_idx;
    u64 config_change_error;
} vtss_tas_gcl_state_t;

typedef struct {
    vtss_tas_list_t          tas_lists[VTSS_TAS_NUMBER_OF_LISTS];
    vtss_tas_profile_t       tas_profiles[VTSS_TAS_NUMBER_OF_PROFILES];
#if defined(VTSS_FEATURE_QOS_TAS_LIST_LINKED)
    vtss_tas_list_entry      tas_entries[VTSS_TAS_NUMBER_OF_ENTRIES];
#else
    vtss_tas_entry_block_t   tas_entry_blocks[VTSS_TAS_NUMBER_OF_ROWS][VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW];
    vtss_tas_entry_row_t     tas_entry_rows[VTSS_TAS_NUMBER_OF_ROWS];
#endif
    vtss_tas_gcl_state_t     tas_gcl_state[VTSS_PORT_ARRAY_SIZE];

    vtss_qos_tas_conf_t      global_conf;
    vtss_qos_tas_port_conf_t port_conf[VTSS_PORT_ARRAY_SIZE];
} vtss_qos_tas_state_t;
#endif /* defined(VTSS_FEATURE_QOS_TAS) */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
typedef struct {
    vtss_qos_fp_port_conf_t port_conf[VTSS_PORT_ARRAY_SIZE];
} vtss_qos_fp_state_t;
#endif /* defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) */

#if defined(VTSS_ARCH_SPARX5)
typedef struct {
    u32 min_burst;          /* Minimum burst size and granularity in bytes */
    u32 pup_interval;       /* Configures ANA_AC_SDLB:LBGRP_TBL[0-9]:PUP_INTERVAL.PUP_INTERVAL */
    u32 frame_size;         /* Configures ANA_AC_SDLB:LBGRP_TBL[0-9]:FRM_RATE_TOKENS.FRM_RATE_TOKENS */
    u32 lb_set_count;       /* Number of LB set added to the group */
} vtss_qos_lb_group_t;
#define LB_GROUP_CNT   10   /* The number of LB groups */
#define LB_SET_CNT   4615   /* The number of LB sets */
#endif

typedef struct {
    /* CIL function pointers */
    vtss_rc (* conf_set)(struct vtss_state_s *vtss_state, BOOL changed);
    vtss_rc (* port_conf_set)(struct vtss_state_s *vtss_state,
                              const vtss_port_no_t port_no);
    vtss_rc (* port_conf_update)(struct vtss_state_s *vtss_state,
                                 const vtss_port_no_t port_no);
    vtss_rc (* status_get)(struct vtss_state_s *vtss_state,
                           vtss_qos_status_t *const status);

#if defined(VTSS_FEATURE_QCL)
    vtss_rc (* qce_add)(struct vtss_state_s *vtss_state,
                        const vtss_qcl_id_t  qcl_id,
                        const vtss_qce_id_t  qce_id,
                        const vtss_qce_t     *const qce);
    vtss_rc (* qce_del)(struct vtss_state_s *vtss_state,
                        const vtss_qcl_id_t  qcl_id,
                        const vtss_qce_id_t  qce_id);
#endif /* VTSS_FEATURE_QCL */
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
    vtss_rc (* evc_policer_conf_set)(struct vtss_state_s *vtss_state,
                                     const vtss_evc_policer_id_t policer_id);
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
#if defined(VTSS_ARCH_OCELOT)
    vtss_rc (* shaper_calibrate)(struct vtss_state_s *vtss_state);
#endif /* defined(VTSS_ARCH_OCELOT) */

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    vtss_rc (* ingress_map_add)(struct vtss_state_s *vtss_state,
                                const vtss_qos_ingress_map_t *const map);
    vtss_rc (* ingress_map_del)(struct vtss_state_s *vtss_state,
                                const vtss_qos_ingress_map_id_t id);
    vtss_qos_map_vcap_update_t ingress_map_vcap_update;
    vtss_qos_map_hw_update_t   ingress_map_hw_update;
    vtss_qos_map_hw_copy_t     ingress_map_hw_copy;
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    vtss_rc (* egress_map_add)(struct vtss_state_s *vtss_state,
                               const vtss_qos_egress_map_t *const map);
    vtss_rc (* egress_map_del)(struct vtss_state_s *vtss_state,
                               const vtss_qos_egress_map_id_t id);
    vtss_qos_map_vcap_update_t egress_map_vcap_update;
    vtss_qos_map_hw_update_t   egress_map_hw_update;
    vtss_qos_map_hw_copy_t     egress_map_hw_copy;
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
    vtss_rc (* cpu_port_shaper_set)(struct vtss_state_s *vtss_state, const vtss_bitrate_t rate);
#endif /* defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER) */

#if defined(VTSS_FEATURE_QOS_TAS)
    vtss_rc (* tas_conf_set)(struct vtss_state_s  *vtss_state);
    vtss_rc (* tas_port_conf_set)(struct vtss_state_s  *vtss_state,
                                  const vtss_port_no_t port_no);
    vtss_rc (* tas_port_status_get)(struct vtss_state_s        *vtss_state,
                                    const vtss_port_no_t       port_no,
                                    vtss_qos_tas_port_status_t *const status);
#endif /* defined(VTSS_FEATURE_QOS_QBV) */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_rc (* fp_port_status_get)(struct vtss_state_s       *vtss_state,
                                   const vtss_port_no_t      port_no,
                                   vtss_qos_fp_port_status_t *const status);

    vtss_rc (* fp_port_conf_set)(struct vtss_state_s *vtss_state,
                                 const vtss_port_no_t port_no);
#endif /* defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) */

    /* Configuration/state */
    BOOL                    wfq;
    vtss_prio_t             prio_count; /* Maximum number of supported priorities. Must be a power of two. Read-only! */
    vtss_qos_conf_t         conf;
    vtss_qos_port_conf_t    port_conf_old;
    vtss_qos_port_conf_t    port_conf[VTSS_PORT_ARRAY_SIZE];
#if defined(VTSS_ARCH_LUTON26)
    vtss_policer_user_t     policer_user[VTSS_L26_POLICER_CNT];
#endif /* VTSS_ARCH_LUTON26 */

#if defined(VTSS_FEATURE_EVC_POLICERS)
    u32                     evc_policer_max;
    vtss_evc_policer_conf_t evc_policer_conf[VTSS_EVC_POLICERS];
#if defined(VTSS_ARCH_LUTON26)
    vtss_policer_alloc_t    evc_policer_alloc[VTSS_EVC_POLICERS];
#endif /* VTSS_ARCH_LUTON26 */
#endif /* VTSS_FEATURE_EVC_POLICERS */

#if defined(VTSS_ARCH_SPARX5)
    vtss_qos_lb_group_t lb_groups[LB_GROUP_CNT];
    u16                 lb_set_grp_idx[LB_SET_CNT];     /* The LB group index for this LB set */
#endif

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    vtss_shaper_calibrate_t port_shaper[VTSS_PORT_ARRAY_SIZE];
    vtss_shaper_calibrate_t queue_shaper[VTSS_PORT_ARRAY_SIZE][VTSS_QUEUE_ARRAY_SIZE];
#endif /* defined(VTSS_ARCH_OCELOT) */

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    vtss_qos_map_id_entry_t imap_id[VTSS_QOS_INGRESS_MAP_IDS];    /* Allocation of id table. Only accessed through imap below */
    vtss_qos_map_ix_entry_t imap_ix[VTSS_QOS_INGRESS_MAP_ROWS];   /* Allocation of ix table. Only accessed through imap below */
    vtss_qos_map_adm_t      imap;                                 /* Generic table administration */
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    vtss_qos_map_id_entry_t emap_id[VTSS_QOS_EGRESS_MAP_IDS];     /* Allocation of id table. Only accessed through emap below */
    vtss_qos_map_ix_entry_t emap_ix_a[VTSS_QOS_EGRESS_MAP_ROWS];  /* Allocation of ix table resource A. Only accessed through emap below */
    vtss_qos_map_ix_entry_t emap_ix_b[VTSS_QOS_EGRESS_MAP_ROWS];  /* Allocation of ix table resource B. Only accessed through emap below */
    vtss_qos_map_adm_t      emap;                                 /* Generic table administration */
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_HSCH_LEAK_LISTS)
    vtss_qos_leak_conf_t    leak_conf;
#endif /* defined(VTSS_FEATURE_QOS_HSCH_LEAK_LISTS) */

#if defined(VTSS_FEATURE_QOS_TAS)
    vtss_qos_tas_state_t tas;
#endif /* defined(VTSS_FEATURE_QOS_TAS) */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_qos_fp_state_t fp;
#endif /* defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) */
#if defined(VTSS_FEATURE_STORM_POLICER_DROP_COUNTER)
    u32   storm_policer_drop_counter[3];
    BOOL  storm;
#endif
} vtss_qos_state_t;

vtss_rc vtss_qos_inst_create(struct vtss_state_s *vtss_state);
vtss_rc vtss_qos_restart_sync(struct vtss_state_s *vtss_state);

u32 vtss_cmn_qos_chip_prio(struct vtss_state_s *vtss_state, const vtss_prio_t prio);
u32 vtss_cmn_qos_packet_rate(vtss_packet_rate_t rate, u32 *unit);
u32 vtss_cmn_qos_storm_mode(vtss_packet_rate_t rate, vtss_storm_policer_mode_t mode);
vtss_rc vtss_cmn_qos_port_conf_set(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_cmn_qos_weight2cost(const vtss_pct_t *weight, u8 *cost, u32 num, u8 bit_width);
#if defined(VTSS_FEATURE_QCL)
vtss_rc vtss_cmn_qce_add(struct vtss_state_s *vtss_state,
                         const vtss_qcl_id_t qcl_id, const vtss_qce_id_t qce_id, const vtss_qce_t *const qce);
vtss_rc vtss_cmn_qce_del(struct vtss_state_s *vtss_state,
                         const vtss_qcl_id_t qcl_id, const vtss_qce_id_t qce_id);
#endif
#if defined(VTSS_FEATURE_EVC_POLICERS)
vtss_rc vtss_evc_policer_id_check(struct vtss_state_s *vtss_state,
                                  const vtss_evc_policer_id_t policer_id, BOOL resv);
void vtss_qos_debug_print_dlb(struct vtss_state_s *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_EVC_POLICERS */
#if VTSS_OPT_DEBUG_PRINT
void vtss_qos_debug_print(struct vtss_state_s *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info);
#endif
#endif /* VTSS_FEATURE_QOS */

#endif /* _VTSS_QOS_STATE_H_ */
