// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief QoS API
 * \details This header file describes Quality of Service functions
 */

#ifndef _VTSS_QOS_API_H_
#define _VTSS_QOS_API_H_

#include <vtss/api/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(VTSS_FEATURE_QOS)

/** \page qos Quality of Service (QoS)

    The Quality of Service (QoS) functions are used to control the various QoS features in the switch.
*/

#if defined(VTSS_FEATURE_QOS_WRED_V2) || defined(VTSS_FEATURE_QOS_WRED_V3)
/**
 * \brief Random Early Detection version 2. Select if max means max drop probability or max fill level
 **/
typedef enum {
    VTSS_WRED_MAX_DP, /**< Unit for max is drop probability */
    VTSS_WRED_MAX_FL  /**< Unit for max is fill level */
} vtss_wred_max_t;

#define VTSS_WRED_V2_MAX_DP VTSS_WRED_MAX_DP /**< Backward compatibility */
#define VTSS_WRED_V2_MAX_FL VTSS_WRED_MAX_FL /**< Backward compatibility */

/** \brief Backward compatibility */
typedef vtss_wred_max_t vtss_wred_v2_max_t;

/**
 * \brief Random Early Detection configuration struct version 2 (per queue, per dpl - switch global)
 **/
typedef struct {
    BOOL               enable;   /**< Enable/disable RED */
    vtss_pct_t         min_fl;   /**< Minimum fill level */
    vtss_pct_t         max;      /**< Maximum drop probability or fill level - selected by max_unit */
    vtss_wred_v2_max_t max_unit; /**< Selects the unit for max */
} vtss_wred_conf_t;

/** \brief Backward compatibility */
typedef vtss_wred_conf_t vtss_red_v2_t;

#endif /* defined(VTSS_FEATURE_QOS_WRED_V2) || defined(VTSS_FEATURE_QOS_WRED_V3) */

#if defined(VTSS_FEATURE_QOS_WRED_V3)
#define VTSS_WRED_DPL_CNT    3           /**< Number of dpl's. There are no profile for dpl 0, only for dpl 1 to 3 */
#define VTSS_WRED_GROUP_CNT  3           /**< Number of groups */
typedef vtss_wred_conf_t vtss_red_v3_t; /**< Version 3 uses the v2 struct (per queue, per dpl, per group - switch global */
#endif /* defined(VTSS_FEATURE_QOS_WRED_V3) */

/** \page qos

    \section global_conf Global Configuration

    The global configuration functions are used to control the global switch parameters.\n
    The following functions are available:
    - vtss_qos_conf_get() is used to get global configuration.
    - vtss_qos_conf_set() is used to set global configuration.
*/

/**
 * \brief All parameters below are defined per chip
 **/
typedef struct {
    vtss_prio_t          prios;                                   /**< Number of priorities (1/2/4/8) */

    BOOL                 dscp_trust[64];                          /**< Ingress: Only trusted DSCP values are used for QOS class and DP level classification  */
    vtss_prio_t          dscp_qos_class_map[64];                  /**< Ingress: Mapping from DSCP value to QOS class  */
    vtss_dp_level_t      dscp_dp_level_map[64];                   /**< Ingress: Mapping from DSCP value to DP level */

    vtss_dscp_t          dscp_qos_map[VTSS_PRIO_ARRAY_SIZE];      /**< Ingress: Mapping from QoS class to DSCP (DP unaware or DP level = 0) */
    vtss_dscp_t          dscp_qos_map_dp1[VTSS_PRIO_ARRAY_SIZE];  /**< Ingress: Mapping from QoS class to DSCP (DP aware and DP level = 1) */
#if VTSS_DPLS == 4
    vtss_dscp_t          dscp_qos_map_dp2[VTSS_PRIO_ARRAY_SIZE];  /**< Ingress: Mapping from QoS class to DSCP (DP aware and DP level = 2) */
    vtss_dscp_t          dscp_qos_map_dp3[VTSS_PRIO_ARRAY_SIZE];  /**< Ingress: Mapping from QoS class to DSCP (DP aware and DP level = 3) */
#endif /* VTSS_DPLS == 4 */

    BOOL                 dscp_remark[64];                         /**< Ingress: DSCP remarking enable. Used when port.dscp_mode = VTSS_DSCP_MODE_SEL */
    vtss_dscp_t          dscp_translate_map[64];                  /**< Ingress: Translated DSCP value. Used when port.dscp_translate = TRUE) */
    vtss_dscp_t          dscp_remap[64];                          /**< Egress: Remap one DSCP to another (DP unaware or DP level = 0) */
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
    vtss_dscp_t          dscp_remap_dp1[64];                      /**< Egress: Remap one DSCP to another (DP aware and DP level = 1) */
#endif /* defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE) */

    vtss_packet_rate_t        policer_uc;                         /**< Unicast packet storm policer */
    BOOL                      policer_uc_frame_rate;              /**< FALSE: Unit is kbps. TRUE: Unit is fps */
    vtss_storm_policer_mode_t policer_uc_mode;                    /**< Unicast packet storm policer mode */
    vtss_packet_rate_t        policer_mc;                         /**< Multicast packet storm policer */
    BOOL                      policer_mc_frame_rate;              /**< FALSE: Unit is kbps. TRUE: Unit is fps */
    vtss_storm_policer_mode_t policer_mc_mode;                    /**< Multicast packet storm policer mode */
    vtss_packet_rate_t        policer_bc;                         /**< Broadcast packet storm policer */
    BOOL                      policer_bc_frame_rate;              /**< FALSE: Unit is kbps. TRUE: Unit is fps */
    vtss_storm_policer_mode_t policer_bc_mode;                    /**< Broadcast packet storm policer mode */

#if defined(VTSS_FEATURE_QOS_WRED_V2)
    vtss_wred_conf_t          red_v2[VTSS_QUEUE_ARRAY_SIZE][2];        /**< Random Early Detection - per queue (0..7), per dpl (0..1) */
#endif /* defined(VTSS_FEATURE_QOS_WRED_V2) */

#if defined(VTSS_FEATURE_QOS_WRED_V3)
    vtss_wred_conf_t          red_v3[VTSS_QUEUE_ARRAY_SIZE]            /**< Random Early Detection - per queue (0..7), per dpl (1..3), per group (0..2) */
    [VTSS_WRED_DPL_CNT]
    [VTSS_WRED_GROUP_CNT];
#endif /* defined(VTSS_FEATURE_QOS_WRED_V3) */
} vtss_qos_conf_t;

/**
 * \brief Get QoS setup for switch.
 *
 * \param inst [IN]   Target instance reference.
 * \param conf [OUT]  QoS setup structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_conf_get(const vtss_inst_t  inst,
                          vtss_qos_conf_t    *const conf);

/**
 * \brief Set QoS setup for switch.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  QoS setup structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_conf_set(const vtss_inst_t      inst,
                          const vtss_qos_conf_t  *const conf);

/* Number of Port policers (per port) available in HW */
#if defined(VTSS_ARCH_SERVAL_T)
#define VTSS_PORT_POLICERS 2 /**< Number of Port policers (per port) available in HW */
#elif defined(VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5)
#define VTSS_PORT_POLICERS 4 /**< Number of Port policers (per port) available in HW */
#else
#define VTSS_PORT_POLICERS 1 /**< Number of Port policers (per port) available in HW */
#endif

/**
 * \brief Policer
 **/
typedef struct {
    vtss_burst_level_t level;       /**< Burst level */
    vtss_bitrate_t     rate;        /**< Maximum rate */
} vtss_policer_t;

#define VTSS_PORT_POLICER_CPU_QUEUES 8 /**< Number of cpu queues pr port policer */

/**
 * \brief Policer Extensions
 **/
typedef struct {
    BOOL               frame_rate;           /**< Measure rates in frames per seconds instead of bits per second */
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL)
    vtss_dp_level_t    dp_bypass_level;      /**< Drop Predence bypass level */
#endif /* VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL */
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2)
    BOOL               known_unicast;        /**< Known unicast frames are policed */
    BOOL               known_multicast;      /**< Known multicast frames are policed */
    BOOL               known_broadcast;      /**< Known broadcast frames are policed */
    BOOL               unknown_unicast;      /**< Unknown unicast frames are policed */
    BOOL               unknown_multicast;    /**< Unknown multicast frames are policed */
    BOOL               unknown_broadcast;    /**< Unknown broadcast frames are policed */
    BOOL               learning;             /**< Learning frames are policed */
    BOOL               to_cpu;               /**< Frames to the CPU are policed */
    BOOL               cpu_queue[VTSS_PORT_POLICER_CPU_QUEUES]; /**< Enable each individual CPU queue (if to_cpu is set) */
    BOOL               limit_noncpu_traffic; /**< Remove the front ports from the destination set for a policed frame */
    BOOL               limit_cpu_traffic;    /**< Remove the CPU ports from the destination set for a policed frame */
#endif /* VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2 */
    BOOL               flow_control;         /**< Flow control is enabled */
} vtss_policer_ext_t;

#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
/** \brief Dual leaky buckets policer configuration */
typedef struct {
    vtss_policer_type_t type;      /**< Policer type */
    BOOL                enable;    /**< Enable/disable policer */
#if defined(VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5)
    BOOL                cm;        /**< Colour Mode (TRUE means colour aware) */
#endif /* VTSS_ARCH_JAGUAR_2 */
    BOOL                cf;        /**< Coupling Flag */
    BOOL                line_rate; /**< Line rate policing (default is data rate policing) */
    vtss_bitrate_t      cir;       /**< Committed Information Rate */
    vtss_burst_level_t  cbs;       /**< Committed Burst Size */
    vtss_bitrate_t      eir;       /**< Excess Information Rate */
    vtss_burst_level_t  ebs;       /**< Excess Burst Size */
#if defined(VTSS_FEATURE_PSFP)
    BOOL                drop_yellow;  // DropOnYellow: Discard yellow frames
    vtss_opt_bool_t     mark_all_red; // MarkAllFramesRedEnable/MarkAllFramesRed: Discard all frames if red frame seen
#endif
} vtss_dlb_policer_conf_t;
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */

#if defined(VTSS_ARCH_CARACAL)
/** \page qos

    \section mep_conf MEP Policer Configuration

    The MEP policer configuration functions are used to control the MEP policers.\n
    The following functions are available:
    - vtss_mep_policer_conf_get() is used to get MEP policer configuration for a specific port and priority.
    - vtss_mep_policer_conf_set() is used to set MEP policer configuration for a specific port and priority.
*/

/**
 * \brief Get MEP policer configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param port_no [IN]     Ingress port number.
 * \param prio [IN]        Selected priority (QoS class).
 * \param conf [OUT]       Policer configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_mep_policer_conf_get(const vtss_inst_t       inst,
                                  const vtss_port_no_t    port_no,
                                  const vtss_prio_t       prio,
                                  vtss_dlb_policer_conf_t *const conf);

/**
 * \brief Set MEP policer configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param port_no [IN]     Ingress port number.
 * \param prio [IN]        Selected priority (QoS class).
 * \param conf [IN]        Policer configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_mep_policer_conf_set(const vtss_inst_t             inst,
                                  const vtss_port_no_t          port_no,
                                  const vtss_prio_t             prio,
                                  const vtss_dlb_policer_conf_t *const conf);
#endif /* defined(VTSS_ARCH_CARACAL) */

#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT)
/**
 * \brief Shaper Accounting Mode
 **/
typedef enum {
    VTSS_SHAPER_MODE_LINE, /**< Use line-rate for the shaper */
    VTSS_SHAPER_MODE_DATA, /**< Use data-rate for the shaper */
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPER_FRAME)
    VTSS_SHAPER_MODE_FRAME  /**< Use frame-rate for the shaper */
#endif
} vtss_shaper_mode_t;
#endif

/**
 * \brief Shaper
 **/
typedef struct {
    vtss_burst_level_t level;          /**< CBS (Committed Burst Size).       Unit: bytes. frames if frame-rate */
    vtss_bitrate_t     rate;           /**< CIR (Committed Information Rate). Unit: kbps. frame/s if frame-rate. Use VTSS_BITRATE_DISABLED to disable shaper */
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
    vtss_burst_level_t ebs;            /**< EBS (Excess Burst Size).          Unit: bytes */
    vtss_bitrate_t     eir;            /**< EIR (Excess Information Rate).    Unit: kbps. Use VTSS_BITRATE_DISABLED to disable DLB */
#endif /* VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB */
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT)
    vtss_shaper_mode_t mode;           /**< RT (Rate type). Shaper rate type configuration: 0 = Line-rate, 1 = Data-rate */
#endif
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB)
    BOOL               credit_enable;  /**< Queue shaper only: Credit-based shaping */
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB */

} vtss_shaper_t;

/** \brief Tag Remark Mode */
typedef enum {
    VTSS_TAG_REMARK_MODE_CLASSIFIED = 0, /**< Use classified PCP/DEI values */
    VTSS_TAG_REMARK_MODE_DEFAULT    = 2, /**< Use default (configured) PCP/DEI values */
    VTSS_TAG_REMARK_MODE_MAPPED     = 3  /**< Use mapped versions of classified QOS class and DP level */
} vtss_tag_remark_mode_t;

/**
 * \brief DSCP mode for ingress port
 **/
typedef enum {
    VTSS_DSCP_MODE_NONE,   /**< DSCP not remarked */
    VTSS_DSCP_MODE_ZERO,   /**< DSCP value zero remarked */
    VTSS_DSCP_MODE_SEL,    /**< DSCP values selected above (dscp_remark) are remarked */
    VTSS_DSCP_MODE_ALL     /**< DSCP remarked for all values */
} vtss_dscp_mode_t;

/**
 * \brief DSCP mode for egress port
 **/
typedef enum {
    VTSS_DSCP_EMODE_DISABLE,   /**< DSCP not remarked */
    VTSS_DSCP_EMODE_REMARK,    /**< DSCP remarked with DSCP value from analyzer */
    VTSS_DSCP_EMODE_REMAP,     /**< DSCP remarked with DSCP value from analyzer remapped through global remap table  */
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
    VTSS_DSCP_EMODE_REMAP_DPA  /**< DSCP remarked with DSCP value from analyzer remapped through global remap dp aware tables */
#endif /* VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE */
} vtss_dscp_emode_t;

/** \page qos

    \section port_conf Port Configuration

    The port configuration functions are used to control the per port parameters.\n
    The following functions are available:
    - vtss_qos_port_conf_get() is used to get port configuration for a specific port.
    - vtss_qos_port_conf_set() is used to set port configuration for a specific port.
*/

/** \brief QoS setup per port **/
typedef struct {
    vtss_policer_t policer_port[VTSS_PORT_POLICERS];             /**< Ingress port policers */

    vtss_policer_ext_t policer_ext_port[VTSS_PORT_POLICERS];     /**< Ingress port policers extensions */

    vtss_policer_t     policer_queue[VTSS_QUEUE_ARRAY_SIZE];     /**< Ingress queue policers */

    vtss_shaper_t  shaper_port;                                  /**< Egress port shaper */

    vtss_shaper_t shaper_queue[VTSS_QUEUE_ARRAY_SIZE];           /**< Egress queue shapers */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB)
    BOOL          excess_enable[VTSS_QUEUE_ARRAY_SIZE];          /**< Allow this queue to use excess bandwidth */
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB */

#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
    BOOL          cut_through_enable[VTSS_QUEUE_ARRAY_SIZE];     /**< Allow this queue to use cut through feature */
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH */

    vtss_prio_t    default_prio;                                 /**< Default port priority (QoS class) */
    vtss_tagprio_t usr_prio;                                     /**< Default Ingress VLAN tag priority (PCP) */

    vtss_dp_level_t   default_dpl;                                             /**< Default Ingress Drop Precedence level */
    vtss_dei_t        default_dei;                                             /**< Default Ingress DEI value  */
    BOOL              tag_class_enable;                                        /**< Ingress classification of QoS class and DP level based PCP and DEI */
    vtss_prio_t       qos_class_map[VTSS_PCP_ARRAY_SIZE][VTSS_DEI_ARRAY_SIZE]; /**< Ingress mapping for tagged frames from PCP and DEI to QOS class  */
    vtss_dp_level_t   dp_level_map[VTSS_PCP_ARRAY_SIZE][VTSS_DEI_ARRAY_SIZE];  /**< Ingress mapping for tagged frames from PCP and DEI to DP level */
    BOOL              dscp_class_enable;                                       /**< Ingress classification of QoS class and DP level based on DSCP */

    vtss_dscp_mode_t  dscp_mode;                      /**< Ingress DSCP mode */
    vtss_dscp_emode_t dscp_emode;                     /**< Egress DSCP mode */
    BOOL              dscp_translate;                 /**< Ingress: Translate DSCP value via dscp_translate_map[DSCP] before use */

    vtss_tag_remark_mode_t tag_remark_mode;                      /**< Egress tag remark mode */
    vtss_tagprio_t         tag_default_pcp;                      /**< Default PCP value for Egress port */
    vtss_dei_t             tag_default_dei;                      /**< Default DEI value for Egress port */
    vtss_tagprio_t         tag_pcp_map[VTSS_PRIO_ARRAY_SIZE][2]; /**< Egress mapping from QOS class and (1 bit) DP level to PCP */
    vtss_dei_t             tag_dei_map[VTSS_PRIO_ARRAY_SIZE][2]; /**< Egress mapping from QOS class and (1 bit) DP level to DEI */

    BOOL       dwrr_enable;                                      /**< Enable Weighted fairness queueing */
#if defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
    u8         dwrr_cnt;                                         /**< Number of queues, starting from queue 0, running in DWRR mode */
#endif /* VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT */
    vtss_pct_t queue_pct[VTSS_QUEUE_ARRAY_SIZE];                 /**< Queue percentages */

#if defined(VTSS_FEATURE_QCL_DMAC_DIP)
    BOOL       dmac_dip;                                         /**< Enable DMAC/DIP matching in QCLs (default SMAC/SIP) */
#endif /* VTSS_FEATURE_QCL_DMAC_DIP */

#if defined(VTSS_FEATURE_QCL_KEY_TYPE)
    vtss_vcap_key_type_t key_type;                               /**< Key type for received frames */
#endif /* defined(VTSS_FEATURE_QCL_KEY_TYPE) */

#if defined(VTSS_FEATURE_QOS_WRED_V3)
    vtss_wred_group_t wred_group;                                /**< WRED group number - zero based */
#endif /* defined(VTSS_FEATURE_QOS_WRED_V3) */

#if (defined VTSS_FEATURE_QOS_COSID_CLASSIFICATION)
    vtss_cosid_t cosid;                                          /**< Default COSID */
#endif /* VTSS_FEATURE_QOS_COSID_CLASSIFICATION */

#if (defined VTSS_FEATURE_QOS_INGRESS_MAP)
    vtss_qos_ingress_map_id_t ingress_map;                       /**< Ingress map to use for classification. Default is none. */
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if (defined VTSS_FEATURE_QOS_EGRESS_MAP)
    vtss_qos_egress_map_id_t egress_map;                         /**< Egress map to use for remarking. Default is none. */
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */
} vtss_qos_port_conf_t;

/**
 * \brief Get QoS setup for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    QoS setup structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_port_conf_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_qos_port_conf_t  *const conf);

/**
 * \brief Set QoS setup for port.
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number.
 * \param conf [IN]    QoS setup structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_port_conf_set(const vtss_inst_t           inst,
                               const vtss_port_no_t        port_no,
                               const vtss_qos_port_conf_t  *const conf);

/** \brief QoS status  **/
typedef struct {
    vtss_event_t        storm;                  /**< Storm policing active since last call. */
} vtss_qos_status_t;

/**
* \brief Get QoS status for port.
*
* \param inst [IN]     Target instance reference.
* \param status [OUT]  QoS status structure.
*
* \return Return code.
**/
vtss_rc vtss_qos_status_get(const vtss_inst_t inst,
                            vtss_qos_status_t *const status);

#if defined(VTSS_FEATURE_QCL)
/** \page qos

    \section qcl_conf QoS Control List Configuration

    Advanced QoS classification rules can be done using the QoS Control List (QCL).
    Each QoS Control Entry (QCE) is identified by a QCE ID (::vtss_qce_id_t).\n
    The following functions are available:
    - vtss_qce_init() is used to initialize a QCE (::vtss_qce_t) to default values.
    - vtss_qce_add() is used to add or modify a QCE.
    - vtss_qce_del() is used to delete a QCE.

    The QCEs are ordered in a list of rules based on the QCE IDs. When adding a rule,
    the QCE ID of the rule and the QCE ID of the next rule in the list must be specified.
    A special value #VTSS_QCE_ID_LAST is used to specify that the rule must be added at the
    end of the list.\n
    Each QCE includes a key structure (::vtss_qce_key_t) with fields used for matching
    received frames and an action structure (::vtss_qce_action_t) with the classification parameters.\n
    By default, no QCE rules are setup.

*/

/**
 * \brief QCL ID type
 **/
typedef u32 vtss_qcl_id_t;

#define VTSS_QCL_IDS        1                                  /**< Number of QCLs */
#define VTSS_QCL_ID_START   0                                  /**< QCL ID start number */
#define VTSS_QCL_ID_END     (VTSS_QCL_ID_START + VTSS_QCL_IDS) /**< QCL ID end number */
#define VTSS_QCL_ARRAY_SIZE VTSS_QCL_ID_END                    /**< QCL ID array size */

#define VTSS_QCE_ID_LAST 0 /**< Special value used to add last in list */

/** \brief QoS Control Entry type */
typedef enum {
    VTSS_QCE_TYPE_ANY,     /**< Any frame type */
    VTSS_QCE_TYPE_ETYPE,   /**< Ethernet Type */
    VTSS_QCE_TYPE_LLC,     /**< LLC */
    VTSS_QCE_TYPE_SNAP,    /**< SNAP */
    VTSS_QCE_TYPE_IPV4,    /**< IPv4 */
    VTSS_QCE_TYPE_IPV6     /**< IPv6 */
} vtss_qce_type_t;

/** \brief QCE MAC information */
typedef struct {
    vtss_vcap_bit_t dmac_mc; /**< Multicast DMAC */
    vtss_vcap_bit_t dmac_bc; /**< Broadcast DMAC */
#if defined(VTSS_FEATURE_QCL_KEY_DMAC)
    vtss_vcap_u48_t dmac;    /**< DMAC - Serval: key_type = mac_ip_addr */
#endif /* defined(VTSS_FEATURE_QCL_KEY_DMAC) */
    vtss_vcap_u48_t smac;    /**< SMAC - Only the 24 most significant bits (OUI) are supported on Jaguar1, rest are wildcards */
} vtss_qce_mac_t;

/** \brief QCE tag information */
typedef struct {
    vtss_vcap_vr_t  vid;    /**< VLAN ID (12 bit) */
    vtss_vcap_u8_t  pcp;    /**< PCP (3 bit) */
    vtss_vcap_bit_t dei;    /**< DEI */
    vtss_vcap_bit_t tagged; /**< Tagged/untagged frame */
    vtss_vcap_bit_t s_tag;  /**< S-tagged/C-tagged frame */
} vtss_qce_tag_t;

/** \brief Frame data for VTSS_QCE_TYPE_ETYPE */
typedef struct {
    vtss_vcap_u16_t etype; /**< Ethernet Type value */
    vtss_vcap_u32_t data;  /**< MAC data */
} vtss_qce_frame_etype_t;

/** \brief Frame data for VTSS_QCE_TYPE_LLC */
typedef struct {
    vtss_vcap_u48_t data; /**< Data */
} vtss_qce_frame_llc_t;

/** \brief Frame data for VTSS_QCE_TYPE_SNAP */
typedef struct {
    vtss_vcap_u48_t data; /**< Data */
} vtss_qce_frame_snap_t;

/** \brief Frame data for VTSS_QCE_TYPE_IPV4 */
typedef struct {
    vtss_vcap_bit_t fragment; /**< Fragment */
    vtss_vcap_vr_t  dscp;     /**< DSCP field (6 bit) */
    vtss_vcap_u8_t  proto;    /**< Protocol */
    vtss_vcap_ip_t  sip;      /**< Source IP address - Serval: key_type = normal, ip_addr and mac_ip_addr */
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
    vtss_vcap_ip_t  dip;      /**< Destination IP address - Serval: key_type = ip_addr and mac_ip_addr */
#endif /* defined(VTSS_FEATURE_QCL_KEY_DIP) */
    vtss_vcap_vr_t  sport;    /**< UDP/TCP: Source port - Serval: key_type = normal, ip_addr and mac_ip_addr */
    vtss_vcap_vr_t  dport;    /**< UDP/TCP: Destination port - Serval: key_type = double_tag, ip_addr and mac_ip_addr */
} vtss_qce_frame_ipv4_t;

/** \brief Frame data for VTSS_QCE_TYPE_IPV6 */
typedef struct {
    vtss_vcap_vr_t   dscp;    /**< DSCP field (6 bit) */
    vtss_vcap_u8_t   proto;   /**< Protocol */
    vtss_vcap_u128_t sip;     /**< Source IP address (32 LSB on L26 and J1, 64 LSB on Serval when key_type = mac_ip_addr) */
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
    vtss_vcap_u128_t dip;     /**< Destination IP address - 64 LSB on Serval when key_type = mac_ip_addr */
#endif /* defined(VTSS_FEATURE_QCL_KEY_DIP) */
    vtss_vcap_vr_t   sport;   /**< UDP/TCP: Source port - Serval: key_type = normal, ip_addr and mac_ip_addr */
    vtss_vcap_vr_t   dport;   /**< UDP/TCP: Destination port - Serval: key_type = double_tag, ip_addr and mac_ip_addr */
} vtss_qce_frame_ipv6_t;

/**
 * \brief QCE key
 **/
typedef struct {
    BOOL            port_list[VTSS_PORT_ARRAY_SIZE]; /**< Port list */
    vtss_qce_mac_t  mac;                             /**< MAC */
    vtss_qce_tag_t  tag;                             /**< Tag */
#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    vtss_qce_tag_t  inner_tag;                       /**< Inner tag */
#endif /* defined(VTSS_FEATURE_QCL_KEY_INNER_TAG) */
    vtss_qce_type_t type;                            /**< Frame type */

    union {
        /* VTSS_QCE_TYPE_ANY: No specific fields */
        vtss_qce_frame_etype_t etype; /**< VTSS_QCE_TYPE_ETYPE */
        vtss_qce_frame_llc_t   llc;   /**< VTSS_QCE_TYPE_LLC */
        vtss_qce_frame_snap_t  snap;  /**< VTSS_QCE_TYPE_SNAP */
        vtss_qce_frame_ipv4_t  ipv4;  /**< VTSS_QCE_TYPE_IPV4 */
        vtss_qce_frame_ipv6_t  ipv6;  /**< VTSS_QCE_TYPE_IPV6 */
    } frame; /**< Frame type specific data */
} vtss_qce_key_t;

/**
 * \brief QCE action
 **/
typedef struct {
    BOOL                      prio_enable;      /**< Enable priority classification */
    vtss_prio_t               prio;             /**< Priority value */
    BOOL                      dp_enable;        /**< Enable DP classification */
    vtss_dp_level_t           dp;               /**< DP value */
    BOOL                      dscp_enable;      /**< Enable DSCP classification */
    vtss_dscp_t               dscp;             /**< DSCP value */
    BOOL                      pcp_dei_enable;   /**< Enable PCP and DEI classification */
    vtss_tagprio_t            pcp;              /**< PCP value */
    vtss_dei_t                dei;              /**< DEI value */
    BOOL                      policy_no_enable; /**< Enable ACL policy classification */
    vtss_acl_policy_no_t      policy_no;        /**< ACL policy number */
#if (defined VTSS_FEATURE_QCL_MAP_ACTION)
    BOOL                      map_id_enable;    /**< Enable classification via ingress map */
    vtss_qos_ingress_map_id_t map_id;           /**< Ingress map to use for classification */
#endif /* VTSS_FEATURE_QCL_MAP_ACTION */
} vtss_qce_action_t;

/**
 * \brief QoS Control Entry
 **/
typedef struct {
    vtss_qce_id_t     id;         /**< Entry ID */
    vtss_qce_key_t    key;        /**< QCE key */
    vtss_qce_action_t action;     /**< QCE action */
} vtss_qce_t;

/**
 * \brief Initialize QCE to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param type [IN]  QCE type.
 * \param qce [OUT]  QCE structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qce_init(const vtss_inst_t      inst,
                      const vtss_qce_type_t  type,
                      vtss_qce_t             *const qce);

/**
 * \brief Add QCE to QCL.
 *
 * \param inst [IN]    Target instance reference.
 * \param qcl_id [IN]  QCL ID.
 * \param qce_id [IN]  QCE ID. The QCE will be added before the entry with this ID.
 *                     VTSS_QCE_ID_LAST is reserved for inserting last.
 * \param qce [IN]     QCE structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qce_add(const vtss_inst_t    inst,
                     const vtss_qcl_id_t  qcl_id,
                     const vtss_qce_id_t  qce_id,
                     const vtss_qce_t     *const qce);

/**
 * \brief Delete QCE from QCL.
 *
 * \param inst [IN]    Target instance reference.
 * \param qcl_id [IN]  QCL ID.
 * \param qce_id [IN]  QCE ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_qce_del(const vtss_inst_t    inst,
                     const vtss_qcl_id_t  qcl_id,
                     const vtss_qce_id_t  qce_id);
#endif // VTSS_FEATURE_QCL

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP) || defined(VTSS_FEATURE_QOS_EGRESS_MAP)
/** \brief Key that determines what to match */
typedef enum {
    VTSS_QOS_INGRESS_MAP_KEY_PCP,                   /**< Use PCP for tagged frames and none for the rest */
    VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI,               /**< Use PCP/DEI for tagged frames and none for the rest */
    VTSS_QOS_INGRESS_MAP_KEY_DSCP,                  /**< Use DSCP as key for IP frames and none for the rest */
    VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI,          /**< Use DSCP as key for IP frames, PCP/DEI for tagged frames and none for the rest */
    VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC                /**< Use MPLS TC as key for MPLS frames and none for the rest */
} vtss_qos_ingress_map_key_t;

/** \brief Actions that can be applied to classified values if the entry is matched */
typedef struct {
    BOOL cos;                                       /**< If TRUE, then replace the classified COS */
    BOOL dpl;                                       /**< If TRUE, then replace the classified DPL */
    BOOL pcp;                                       /**< If TRUE, then replace the classified PCP */
    BOOL dei;                                       /**< If TRUE, then replace the classified DEI */
    BOOL dscp;                                      /**< If TRUE, then replace the classified DSCP */
    BOOL cosid;                                     /**< If TRUE, then replace the classified COS ID */
    BOOL path;                                      /**< If TRUE, then replace the classified path COS ID */
    BOOL mpls_tc;                                   /**< If TRUE, then replace the classified MPLS TC */
} vtss_qos_ingress_map_action_t;

/** \brief Mapped values that can be applied to classified values if the entry is matched */
typedef struct {
    vtss_cos_t     cos;                             /**< The classified COS is set to cos if action.cos is TRUE */
    vtss_dpl_t     dpl;                             /**< The classified DPL is set to dpl if action.dpl is TRUE */
    vtss_pcp_t     pcp;                             /**< The classified PCP is set to pcp if action.pcp is TRUE */
    vtss_dei_t     dei;                             /**< The classified DEI is set to dei if action.dei is TRUE */
    vtss_dscp_t    dscp;                            /**< The classified DSCP is set to dscp if action.dscp is TRUE */
    vtss_cosid_t   cosid;                           /**< The classified COS ID is set to cosid if action.cosid is TRUE */
    vtss_cosid_t   path_cosid;                      /**< Path COS ID value used by OAM MEP if action.path is TRUE */
    vtss_mpls_tc_t mpls_tc;                         /**< The classified TC is set to mpls_tc if action.mpls_tc is TRUE */
} vtss_qos_ingress_map_values_t;

/** \brief Values for a combination of DSCP, PCP and DEI */
typedef struct {
    vtss_qos_ingress_map_values_t dscp[64];         /**< Mapped values for each DSCP value */
    vtss_qos_ingress_map_values_t pcp_dei[8][2];    /**< Mapped values for each PCP/DEI value */
} vtss_qos_ingress_map_dpd_t;

/** \brief Union of mapped values for different keys */
typedef union {
    vtss_qos_ingress_map_values_t pcp[8];           /**< VTSS_QOS_INGRESS_MAP_KEY_PCP */
    vtss_qos_ingress_map_values_t pcp_dei[8][2];    /**< VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI */
    vtss_qos_ingress_map_values_t dscp[64];         /**< VTSS_QOS_INGRESS_MAP_KEY_DSCP */
    vtss_qos_ingress_map_dpd_t    dpd;              /**< VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI */
    vtss_qos_ingress_map_values_t mpls_tc[8];       /**< VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC */
} vtss_qos_ingress_map_maps_t;

/** \brief The complete map. There is one of these per map id */
typedef struct {
    vtss_qos_ingress_map_id_t     id;               /**< ID for this entry */
    vtss_qos_ingress_map_key_t    key;              /**< Lookup key */
    vtss_qos_ingress_map_action_t action;           /**< Action enable/disable */
    vtss_qos_ingress_map_maps_t   maps;             /**< Maps for specific key */
} vtss_qos_ingress_map_t;

/** \brief Key that determines what to match */
typedef enum {
    VTSS_QOS_EGRESS_MAP_KEY_COSID,                  /**< Use classified COS ID */
    VTSS_QOS_EGRESS_MAP_KEY_COSID_DPL,              /**< Use classified COS ID and DPL */
    VTSS_QOS_EGRESS_MAP_KEY_DSCP,                   /**< Use classified DSCP  */
    VTSS_QOS_EGRESS_MAP_KEY_DSCP_DPL,               /**< Use classified DSCP and DPL */
    VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC,                /**< Use classified TC */
    VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL             /**< Use classified TC and DPL */
} vtss_qos_egress_map_key_t;

/** \brief Actions that can be applied to the frame if the entry is matched */
typedef struct {
    BOOL pcp;                                       /**< If TRUE, then replace PCP in frame */
    BOOL dei;                                       /**< If TRUE, then replace DEI in frame */
    BOOL dscp;                                      /**< If TRUE, then replace DSCP in frame */
    BOOL path;                                      /**< If TRUE, then replace path COS ID in frame */
    BOOL mpls_tc;                                   /**< If TRUE, then replace MPLS TC in frame */
} vtss_qos_egress_map_action_t;

/** \brief Mapped values that can be applied to classified values if the entry is matched */
typedef struct {
    vtss_pcp_t     pcp;                             /**< The classified PCP is set to pcp if action.pcp is TRUE */
    vtss_dei_t     dei;                             /**< The classified DEI is set to dei if action.dei is TRUE */
    vtss_dscp_t    dscp;                            /**< The classified DSCP is set to dscp if action.dscp is TRUE */
    vtss_cosid_t   path_cosid;                      /**< Path COS ID value used by OAM MEP if action.path is TRUE */
    vtss_mpls_tc_t mpls_tc;                         /**< The classified TC is set to mpls_tc if action.mpls_tc is TRUE */
} vtss_qos_egress_map_values_t;

/** \brief Union of mapped values for different keys */
typedef union {
    vtss_qos_egress_map_values_t cosid[8];          /**< VTSS_QOS_EGRESS_MAP_KEY_COSID */
    vtss_qos_egress_map_values_t cosid_dpl[8][4];   /**< VTSS_QOS_EGRESS_MAP_KEY_COSID_DPL */
    vtss_qos_egress_map_values_t dscp[64];          /**< VTSS_QOS_EGRESS_MAP_KEY_DSCP */
    vtss_qos_egress_map_values_t dscp_dpl[64][4];   /**< VTSS_QOS_EGRESS_MAP_KEY_DSCP_DPL */
    vtss_qos_egress_map_values_t mpls_tc[8];        /**< VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC */
    vtss_qos_egress_map_values_t mpls_tc_dpl[8][4]; /**< VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL */
} vtss_qos_egress_map_maps_t;

/** \brief The complete map. There is one of these per map id */
typedef struct {
    vtss_qos_egress_map_id_t     id;                /**< ID for this entry */
    vtss_qos_egress_map_key_t    key;               /**< Lookup key */
    vtss_qos_egress_map_action_t action;            /**< Action enable/disable */
    vtss_qos_egress_map_maps_t   maps;              /**< Maps for specific key */
} vtss_qos_egress_map_t;
#endif /* defined(VTSS_FEATURE_QOS_INGRESS_MAP) || defined(VTSS_FEATURE_QOS_EGRESS_MAP) */

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
/** \page qos

    \section ingress_map Ingress Map

    Global ingress mapping can be done using the ingress map functionality.
    Each ingress map is identified by an ingress map id (::vtss_qos_ingress_map_id_t).\n
    The following functions are available:
    - vtss_qos_ingress_map_init() is used to initialize an ingress map (::vtss_qos_ingress_map_t) to default values.
    - vtss_qos_ingress_map_add() is used to add or modify an ingress map.
    - vtss_qos_ingress_map_del() is used to delete an ingress map.
    - vtss_qos_ingress_map_del_all() is used to delete all ingress maps.

    By default, no ingress maps are setup.
*/

/**
 * \brief Initialize an ingress map to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param key  [IN]  Initialize to this key.
 * \param map [OUT]  Ingress map structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_ingress_map_init(const vtss_inst_t                inst,
                                  const vtss_qos_ingress_map_key_t key,
                                  vtss_qos_ingress_map_t           *const map);

/**
 * \brief Add/update an ingress map.
 *
 * \param inst [IN] Target instance reference.
 * \param map  [IN] Ingress map structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_ingress_map_add(const vtss_inst_t            inst,
                                 const vtss_qos_ingress_map_t *const map);

/**
 * \brief Delete an ingress map.
 *
 * \param inst [IN]  Target instance reference.
 * \param id   [IN]  Map ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_ingress_map_del(const vtss_inst_t               inst,
                                 const vtss_qos_ingress_map_id_t id);
/**
 * \brief Delete all ingress maps.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_ingress_map_del_all(const vtss_inst_t inst);
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
/** \page qos

    \section egress_map Egress Map

    Global egress mapping can be done using the egress map functionality.
    Each egress map is identified by an egress map id (::vtss_qos_egress_map_id_t).\n
    The following functions are available:
    - vtss_qos_egress_map_init() is used to initialize an egress map (::vtss_qos_egress_map_t) to default values.
    - vtss_qos_egress_map_add() is used to add or modify an egress map.
    - vtss_qos_egress_map_del() is used to delete an egress map.
    - vtss_qos_egress_map_del_all() is used to delete all egress maps.

    By default, no egress maps are setup.
*/

/**
 * \brief Initialize an egress map to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param key  [IN]  Initialize to this key.
 * \param map [OUT]  Egress map structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_egress_map_init(const vtss_inst_t               inst,
                                 const vtss_qos_egress_map_key_t key,
                                 vtss_qos_egress_map_t           *const map);

/**
 * \brief Add/update an egress map.
 *
 * \param inst [IN] Target instance reference.
 * \param map  [IN] Egress map structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_egress_map_add(const vtss_inst_t           inst,
                                const vtss_qos_egress_map_t *const map);

/**
 * \brief Delete an egress map.
 *
 * \param inst [IN]  Target instance reference.
 * \param id   [IN]  Map ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_egress_map_del(const vtss_inst_t              inst,
                                const vtss_qos_egress_map_id_t id);
/**
 * \brief Delete all egress maps.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_egress_map_del_all(const vtss_inst_t inst);
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */

#if defined(VTSS_ARCH_OCELOT)
/**
 * \brief Calibrate egress shaper rates.
 *
 * This function calibrates the egress port and queue shapers on VTSS_ARCH_OCELOT.
 *
 * Calling this function periodically will enhance the accuracy of the egress
 * port and queue shapers.
 *
 * Recommended rate is between 1 to 50 times per second.
 *
 * \param inst [IN] Target instance reference.
 *
 * \return VTSS_RC_INCOMPLETE if calibration is still needed, VTSS_RC_OK if not
 * needed anymore, VTSS_RC_ERROR in case of an error.
 * NOTICE: Everytime a shaper is changed, this function must be invoked again.
 **/
vtss_rc vtss_qos_shaper_calibrate(const vtss_inst_t inst);
#endif /* defined(VTSS_ARCH_OCELOT) */

#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
/** \brief EVC policer configuration */
typedef vtss_dlb_policer_conf_t vtss_evc_policer_conf_t;
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */

#if defined(VTSS_FEATURE_EVC_POLICERS)

#if defined(VTSS_CHIP_SERVAL)
#define VTSS_EVC_POLICERS           1022 /**< Maximum number of EVC policers */
#elif defined(VTSS_ARCH_LUTON26) || defined(VTSS_CHIP_SERVAL_LITE)
#define VTSS_EVC_POLICERS           256  /**< Maximum number of EVC policers */
#elif defined(VTSS_ARCH_OCELOT)
#define VTSS_EVC_POLICERS           64   /**< Maximum number of EVC policers */
#endif

#if defined(VTSS_ARCH_OCELOT)
#define VTSS_EVC_POLICER_ID_DISCARD 4094 /**< EVC/ECE: Policer discards all frames */
#define VTSS_EVC_POLICER_ID_NONE    4095 /**< EVC/ECE: Policer forwards all frames */
#define VTSS_EVC_POLICER_ID_EVC     4096 /**< ECE only: Use EVC policer */
#endif /* VTSS_ARCH_OCELOT */

/**
 * \brief Get EVC policer configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param policer_id [IN]  Policer ID.
 * \param conf [OUT]       Policer configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_evc_policer_conf_get(const vtss_inst_t           inst,
                                  const vtss_evc_policer_id_t policer_id,
                                  vtss_evc_policer_conf_t     *const conf);

/**
 * \brief Set EVC policer configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param policer_id [IN]  Policer ID.
 * \param conf [IN]        Policer configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_evc_policer_conf_set(const vtss_inst_t             inst,
                                  const vtss_evc_policer_id_t   policer_id,
                                  const vtss_evc_policer_conf_t *const conf);
#endif /* VTSS_FEATURE_EVC_POLICERS */

#endif /* VTSS_FEATURE_QOS */

#ifdef __cplusplus
}
#endif
#endif /* _VTSS_QOS_API_H_ */
