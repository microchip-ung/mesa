// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_QOS_
#define _MICROCHIP_ETHERNET_SWITCH_API_QOS_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// QoS configuration per (DSCP, DPL)
typedef struct {
    mesa_dscp_t dscp; // Egress map from DSCP,DPL to DSCP value
} mesa_qos_dscp_dpl_conf_t;

// Set global QoS egress configuration per (DSCP, DPL).
// On egress the classified DSCP,DPL is mapped to DSCP if egress port mesa_qos_port_dscp_conf_t.emode == (MESA_DSCP_EMODE_REMAP || MESA_DSCP_EMODE_REMAP_DPA)
// dpl_cnt [IN]  Number of DPLs supported.
// conf [IN]     Configuration. Array[64][dpl_cnt].
mesa_rc mesa_qos_dscp_dpl_conf_set(const mesa_inst_t              inst,
                                   const uint32_t                 dpl_cnt,
                                   const mesa_qos_dscp_dpl_conf_t *const conf);

// Get global QoS egress configuration per (DSCP, DPL)
// dpl_cnt [IN]  Number of DPLs supported.
// conf [OUT]    Configuration. Array[64][dpl_cnt].
mesa_rc mesa_qos_dscp_dpl_conf_get(const mesa_inst_t        inst,
                                   const uint32_t           dpl_cnt,
                                   mesa_qos_dscp_dpl_conf_t *const conf);

// QoS ingress configuration per DPL
typedef struct {
    mesa_dscp_t dscp[MESA_PRIO_ARRAY_SIZE]; // Ingress map from priority (QoS class) to DSCP
} mesa_qos_dpl_conf_t;

// Set global QoS ingress configuration per DPL
// On ingress the classified priority,DPL is mapped to DSCP depending on ingress port mesa_qos_port_dscp_conf_t.mode and DSCP mesa_qos_dscp_conf_t.remark
// dpl_cnt [IN]  Number of DPLs supported.
// conf [IN]     Configuration. Array[dpl_cnt].
mesa_rc mesa_qos_dpl_conf_set(const mesa_inst_t         inst,
                              const uint32_t            dpl_cnt,
                              const mesa_qos_dpl_conf_t *const conf);

// Get clobal QoS ingress configuration per DPL
// dpl_cnt [IN]  Number of DPLs supported.
// conf [OUT]    Configuration. Array[dpl_cnt].
mesa_rc mesa_qos_dpl_conf_get(const mesa_inst_t   inst,
                              const uint32_t      dpl_cnt,
                              mesa_qos_dpl_conf_t *const conf);

// Select if max means max drop probability or max fill level
typedef enum {
    MESA_WRED_MAX_DP, // Unit for max is drop probability
    MESA_WRED_MAX_FL  // Unit for max is fill level
} mesa_wred_max_t CAP(QOS_WRED);

// Weighted Random Early Detection configuration
typedef struct {
    mesa_bool_t     enable;   // Enable/disable RED
    mesa_pct_t      min_fl;   // Minimum fill level
    mesa_pct_t      max;      // Maximum drop probability or fill level - selected by max_unit
    mesa_wred_max_t max_unit; // Selects the unit for max
} mesa_wred_conf_t CAP(QOS_WRED);

// QoS configuration per (DPL, GROUP)
typedef struct {
    mesa_wred_conf_t wred[MESA_QUEUE_ARRAY_SIZE] CAP(QOS_WRED); // WRED configuration per priority
} mesa_qos_dpl_group_conf_t;

// Get QoS configuration per (DPL, GROUP)
// dpl_cnt [IN]    Number of DPLs supported.
// group_cnt [IN]  Number of groups supported.
// conf [OUT]      Configuration. Array[dpl_cnt][group_cnt]
mesa_rc mesa_qos_dpl_group_conf_get(const mesa_inst_t         inst,
                                    const uint32_t            dpl_cnt,
                                    const uint32_t            group_cnt,
                                    mesa_qos_dpl_group_conf_t *const conf);

// Set QoS configuration per (DPL, GROUP)
// dpl_cnt [IN]    Number of DPLs supported.
// group_cnt [IN]  Number of groups supported.
// conf [IN]       Configuration. Array[dpl_cnt][group_cnt]
mesa_rc mesa_qos_dpl_group_conf_set(const mesa_inst_t               inst,
                                    const uint32_t                  dpl_cnt,
                                    const uint32_t                  group_cnt,
                                    const mesa_qos_dpl_group_conf_t *const conf);

// QoS configuration per DSCP value on ingress
typedef struct {
    mesa_bool_t     trust;  // Enable mapping of DSCP value to classified priority (QOS class) and DP level ('prio' and 'pdl')
    mesa_prio_t     prio;   // Map DSCP value to this classified priority (QOS class)
    mesa_dp_level_t dpl;    // Map DSCP value to this classified DP level
    mesa_bool_t     remark; // Map classified priority,DPL through global table (mesa_qos_dpl_conf_t)
                            // if ingress port is configured mesa_qos_port_dscp_conf_t.mode == MESA_DSCP_MODE_SEL
    mesa_dscp_t     dscp;   // translate DSCP value to this value if ingress port is configured mesa_qos_port_dscp_conf_t.translate == TRUE
} mesa_qos_dscp_conf_t;

// QoS storm policer configuration
typedef struct {
    mesa_packet_rate_t        rate;       // Policer rate
    mesa_bool_t               frame_rate; // FALSE: Unit is kbps. TRUE: Unit is fps
    mesa_storm_policer_mode_t mode;       // Unicast packet storm policer mode
} mesa_qos_storm_policer_conf_t;

// All parameters below are defined per chip
typedef struct {
    mesa_prio_t                   prios;      // Number of priorities (1/2/4/8) ---- Only for Luton28 - should return error on other platforms
    mesa_qos_dscp_conf_t          dscp[64];   // DSCP configuration
    mesa_qos_storm_policer_conf_t policer_uc; // Unicast storm policer
    mesa_qos_storm_policer_conf_t policer_mc; // Multicast storm policer
    mesa_qos_storm_policer_conf_t policer_bc; // Broadcast storm policer
} mesa_qos_conf_t;

// Set global QoS configuration for switch.
// conf [IN]  QoS configuration structure.
mesa_rc mesa_qos_conf_set(const mesa_inst_t     inst,
                          const mesa_qos_conf_t *const conf);

// Get global QoS configuration for switch.
// conf [OUT]  QoS configuration structure.
mesa_rc mesa_qos_conf_get(const mesa_inst_t inst,
                          mesa_qos_conf_t   *const conf);

// QoS status
typedef struct {
    mesa_event_t storm; // Storm policing active since last call.
} mesa_qos_status_t;

// Get QoS status for switch.
// status [OUT]  QoS status structure.
mesa_rc mesa_qos_status_get(const mesa_inst_t inst,
                            mesa_qos_status_t *const status);

// Policer
typedef struct {
    mesa_burst_level_t level;       // Burst level
    mesa_bitrate_t     rate;        // Maximum rate
} mesa_policer_t;

// QoS configuration per (port, policer)
typedef struct {
    mesa_policer_t  policer;     // Basic policer config
    mesa_bool_t     frame_rate;  // Measure rates in frames per seconds instead of bits per second
    mesa_dp_level_t dp_bypass_level CAP(QOS_PORT_POLICER_EXT_DPBL); // Drop Predence bypass level

    mesa_bool_t known_unicast         CAP(QOS_PORT_POLICER_EXT_TTM); // Known unicast frames are policed
    mesa_bool_t known_multicast       CAP(QOS_PORT_POLICER_EXT_TTM); // Known multicast frames are policed
    mesa_bool_t known_broadcast       CAP(QOS_PORT_POLICER_EXT_TTM); // Known broadcast frames are policed
    mesa_bool_t unknown_unicast       CAP(QOS_PORT_POLICER_EXT_TTM); // Unknown unicast frames are policed
    mesa_bool_t unknown_multicast     CAP(QOS_PORT_POLICER_EXT_TTM); // Unknown multicast frames are policed
    mesa_bool_t unknown_broadcast     CAP(QOS_PORT_POLICER_EXT_TTM); // Unknown broadcast frames are policed
    mesa_bool_t learning              CAP(QOS_PORT_POLICER_EXT_TTM); // Learning frames are policed
    mesa_bool_t limit_noncpu_traffic  CAP(QOS_PORT_POLICER_EXT_TTM); // Remove the front ports from the destination set for a policed frame
    mesa_bool_t limit_cpu_traffic     CAP(QOS_PORT_POLICER_EXT_TTM); // Remove the CPU ports from the destination set for a policed frame

    mesa_bool_t flow_control;         // Flow control is enabled
} mesa_qos_port_policer_conf_t;

// Get port policer configuration
// port_no [IN]  Port number.
// cnt [IN]      Number of policers supported.
// conf [OUT]    Configuration.
mesa_rc mesa_qos_port_policer_conf_get(const mesa_inst_t            inst,
                                       const mesa_port_no_t         port_no,
                                       const uint32_t               cnt,
                                       mesa_qos_port_policer_conf_t *const conf);

// Set port policer configuration
// port_no [IN]  Port number.
// cnt [IN]      Number of policers supported.
// conf [IN]     Configuration.
mesa_rc mesa_qos_port_policer_conf_set(const mesa_inst_t                  inst,
                                       const mesa_port_no_t               port_no,
                                       const uint32_t                     cnt,
                                       const mesa_qos_port_policer_conf_t *const conf);

// QoS egress configuration per (PORT, DPL)
typedef struct {
    mesa_tagprio_t pcp[MESA_PRIO_ARRAY_SIZE]; // Mapping from priority (QOS class) to tag PCP
    mesa_dei_t     dei[MESA_PRIO_ARRAY_SIZE]; // Mapping from priority (QOS class) to tag DEI
} mesa_qos_port_dpl_conf_t;

// Set QoS egress configuration per (PORT, DPL)
// On egress the classified priority,DPL is mapped to tag PCP,DEI if egress port mesa_qos_port_tag_conf_t.remark_mode == MESA_TAG_REMARK_MODE_MAPPED
// port_no [IN]  Port number.
// dpl_cnt [IN]  Number of DPLs supported.
// conf [IN]     Configuration. Array[dpl_cnt].
mesa_rc mesa_qos_port_dpl_conf_set(const mesa_inst_t              inst,
                                   const mesa_port_no_t           port_no,
                                   const uint32_t                 dpl_cnt,
                                   const mesa_qos_port_dpl_conf_t *const conf);

// Get QoS egress configuration per (PORT, DPL)
// port_no [IN]  Port number.
// dpl_cnt [IN]  Number of DPLs supported.
// conf [OUT]    Configuration. Array[dpl_cnt].
mesa_rc mesa_qos_port_dpl_conf_get(const mesa_inst_t        inst,
                                   const mesa_port_no_t     port_no,
                                   const uint32_t           dpl_cnt,
                                   mesa_qos_port_dpl_conf_t *const conf);

// DSCP mode for ingress port controlling which DSCP values are mapped through global table (mesa_qos_dpl_conf_t)
typedef enum {
    MESA_DSCP_MODE_NONE,   // DSCP not mapped
    MESA_DSCP_MODE_ZERO,   // DSCP value zero mapped
    MESA_DSCP_MODE_SEL,    // DSCP values with mesa_qos_dscp_conf_t.remark == TRUE are mapped
    MESA_DSCP_MODE_ALL     // All DSCP values are mapped.
} mesa_dscp_mode_t;

// DSCP mode for egress port controlling the DSCP value update on egress
typedef enum {
    MESA_DSCP_EMODE_DISABLE,   // DSCP not remarked
    MESA_DSCP_EMODE_REMARK,    // DSCP remarked with classified DSCP
    MESA_DSCP_EMODE_REMAP,     // DSCP remarked with classified DSCP value mapped through global table (see mesa_qos_dscp_dpl_conf_t)
    MESA_DSCP_EMODE_REMAP_DPA CAP(QOS_DSCP_REMARK_DP_AWARE) // DSCP remarked with classified DSCP value mapped through global DPL aware table (see mesa_qos_dscp_dpl_conf_t)
} mesa_dscp_emode_t;

// QoS DSCP configuration per PORT
typedef struct {
    mesa_bool_t       class_enable; // Enable ingress mapping of DSCP to classified priority (QoS class) and DP level through global table ('mesa_qos_dscp_conf_t')
    mesa_dscp_mode_t  mode;         // Ingress DSCP mode controlling which DSCP values are mapped through global table (mesa_qos_dpl_conf_t).
    mesa_dscp_emode_t emode;        // Egress port DSCP mode
    mesa_bool_t       translate;    // Enable Ingress translate of IP frame DSCP value to classified DSCP through global table ('mesa_qos_dscp_conf_t')
} mesa_qos_port_dscp_conf_t;

// QoS configuration per (PORT, PCP, DEI)
typedef struct {
    mesa_prio_t     prio; // Ingress mapping for tagged frames from PCP and DEI to priority (QOS class)
    mesa_dp_level_t dpl;  // Ingress mapping for tagged frames from PCP and DEI to DP level
} mesa_qos_port_pcp_dei_conf_t;

// Egress Tag Remark Mode
typedef enum {
    MESA_TAG_REMARK_MODE_CLASSIFIED = 0, // Use classified PCP/DEI values as tag PCP/DEI
    MESA_TAG_REMARK_MODE_DEFAULT    = 2, // Use configured default egress PCP/DEI values as tag PCP/DEI
    MESA_TAG_REMARK_MODE_MAPPED     = 3  // Use mapped versions of classified QOS class and DP level (see mesa_qos_port_dpl_conf_t) as tag PCP/DEI
} mesa_tag_remark_mode_t;

// QoS VLAN tag configuration per PORT
typedef struct {
    mesa_tagprio_t         pcp;          // Default ingress PCP
    mesa_dei_t             dei;          // Default ingress DEI
    mesa_bool_t            class_enable; // Ingress classification of priority (QoS class) and DP level, based on PCP and DEI through lookup in 'pcp_dei_map' table
    mesa_qos_port_pcp_dei_conf_t pcp_dei_map[MESA_PCP_ARRAY_SIZE][MESA_DEI_ARRAY_SIZE]; // Ingress mapping for tagged frames from PCP and DEI to priority and DPL
    mesa_tag_remark_mode_t remark_mode;  // Egress tag remark mode
    mesa_tagprio_t         egress_pcp;   // Default egress PCP
    mesa_dei_t             egress_dei;   // Default egress DEI
} mesa_qos_port_tag_conf_t;

// Shaper Accounting Mode
typedef enum {
    MESA_SHAPER_MODE_LINE, // Use line-rate for the shaper
    MESA_SHAPER_MODE_DATA, // Use data-rate for the shaper
    MESA_SHAPER_MODE_FRAME CAP(QOS_EGRESS_SHAPER_FRAME) // Use frame-rate for the shaper
} mesa_shaper_mode_t CAP(QOS_EGRESS_SHAPERS_RT);

// Shaper
typedef struct {
    // CBS (Committed Burst Size).
    // Unit: bytes
    //
    // If mode is set to MESA_SHAPER_MODE_FRAME, then unit is number-of-frames
    mesa_burst_level_t level;

    // CIR (Committed Information Rate).
    // Unit: kbps. Use MESA_BITRATE_DISABLED to disable shaper
    //
    // If mode is set to MESA_SHAPER_MODE_FRAME, then unit is frames/s
    mesa_bitrate_t     rate;

    mesa_burst_level_t ebs CAP(QOS_EGRESS_SHAPERS_DLB); // EBS (Excess Burst Size).  Unit: bytes
    mesa_bitrate_t     eir CAP(QOS_EGRESS_SHAPERS_DLB); // EIR (Excess Information Rate). Unit: kbps. Use MESA_BITRATE_DISABLED to disable DLB
    mesa_shaper_mode_t mode CAP(QOS_EGRESS_SHAPERS_RT); // RT (Rate type)
    mesa_bool_t        credit_enable CAP(QOS_EGRESS_QUEUE_SHAPERS_CRB); // Queue shaper only: Credit-based shaping
} mesa_shaper_t;

// QoS configuration per (port, queue)
typedef struct {
    mesa_policer_t policer; // Ingress queue policer
    mesa_shaper_t  shaper;  // Egress queue shapers
    mesa_pct_t     pct;     // The DWRR Queue percentage if DWRR is enabled ('dwrr_enable')
    mesa_bool_t    excess_enable       CAP(QOS_EGRESS_QUEUE_SHAPERS_EB);  // Allow this queue to use excess bandwidth
    mesa_bool_t    cut_through_enable  CAP(QOS_EGRESS_QUEUE_CUT_THROUGH); // Allow this queue to use cut through feature
} mesa_qos_port_queue_conf_t;

// QoS configuration per PORT
typedef struct {
    mesa_shaper_t              shaper;       // Egress port shaper
    mesa_prio_t                default_prio; // Default ingress priority (QoS class)
    mesa_dp_level_t            default_dpl;  // Default ingress drop precedence level
    mesa_qos_port_tag_conf_t   tag;          // VLAN tag configuration
    mesa_qos_port_dscp_conf_t  dscp;         // DSCP configuration
    mesa_bool_t                dwrr_enable;                          // Enable Deficit Weighted Round Robin (DWRR) fairness scheduling.
    uint8_t                    dwrr_cnt CAP(QOS_SCHEDULER_CNT_DWRR); // Number of queues running in DWRR mode starting from queue 0.
                                                                     // Value 3 means that queue 0 to 2 is running DWRR scheduling.
    mesa_bool_t                dmac_dip CAP(QOS_QCL_DMAC_DIP);       // QCL lookup matching on DMAC/DIP (default is SMAC/SIP)
    mesa_vcap_key_type_t       key_type CAP(QOS_QCL_KEY_TYPE);       // QCL lookup key type for received frames
    mesa_wred_group_t          wred_group CAP(QOS_WRED_GROUP_CNT);   // WRED group number of this port - zero based
    mesa_cosid_t               cosid CAP(QOS_COSID_CLASSIFICATION);  // Default COSID
    mesa_qos_ingress_map_id_t  ingress_map CAP(QOS_INGRESS_MAP_CNT); // Ingress map that all frames hit on ingress (see mesa_qos_ingress_map_t). Default is none.
    mesa_qos_egress_map_id_t   egress_map CAP(QOS_EGRESS_MAP_CNT);   // Egress map that all frames hit on egress (see mesa_qos_egress_map_t). Default is none.
    mesa_qos_port_queue_conf_t queue[MESA_QUEUE_ARRAY_SIZE];         // Per priority (QOS class/Queue) configuration
} mesa_qos_port_conf_t;

// Get QoS configuration for port.
// port_no [IN]  Port number.
// conf [OUT]    QoS configuration structure.
mesa_rc mesa_qos_port_conf_get(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               mesa_qos_port_conf_t *const conf);

// Set QoS configuration for port.
// port_no [IN] Port number.
// conf [IN]    QoS configuration structure.
mesa_rc mesa_qos_port_conf_set(const mesa_inst_t          inst,
                               const mesa_port_no_t       port_no,
                               const mesa_qos_port_conf_t *const conf);

#define MESA_QCE_ID_LAST 0 // Special value used to add last in list

// QoS Control Entry type
typedef enum {
    MESA_QCE_TYPE_ANY,     // Any frame type
    MESA_QCE_TYPE_ETYPE,   // Ethernet Type
    MESA_QCE_TYPE_LLC,     // LLC
    MESA_QCE_TYPE_SNAP,    // SNAP
    MESA_QCE_TYPE_IPV4,    // IPv4
    MESA_QCE_TYPE_IPV6     // IPv6
} mesa_qce_type_t;

// QCE MAC information
typedef struct {
    mesa_vcap_bit_t dmac_mc; // Multicast DMAC
    mesa_vcap_bit_t dmac_bc; // Broadcast DMAC
    mesa_vcap_u48_t dmac CAP(QOS_QCL_KEY_DMAC); // DMAC - Serval: key_type = mac_ip_addr
    mesa_vcap_u48_t smac;    // SMAC - Only the 24 most significant bits (OUI) are supported on Jaguar1, rest are wildcards
} mesa_qce_mac_t;

// QCE tag information
typedef struct {
    mesa_vcap_vr_t  vid;    // VLAN ID (12 bit)
    mesa_vcap_u8_t  pcp;    // PCP (3 bit)
    mesa_vcap_bit_t dei;    // DEI
    mesa_vcap_bit_t tagged; // Tagged/untagged frame
    mesa_vcap_bit_t s_tag;  // S-tagged/C-tagged frame
} mesa_qce_tag_t;

// Frame data for MESA_QCE_TYPE_ETYPE
typedef struct {
    mesa_vcap_u16_t etype; // Ethernet Type value
    mesa_vcap_u32_t data;  // MAC data
} mesa_qce_frame_etype_t;

// Frame data for MESA_QCE_TYPE_LLC
typedef struct {
    mesa_vcap_u48_t data; // Data
} mesa_qce_frame_llc_t;

// Frame data for MESA_QCE_TYPE_SNAP
typedef struct {
    mesa_vcap_u48_t data; // Data
} mesa_qce_frame_snap_t;

// Frame data for MESA_QCE_TYPE_IPV4
typedef struct {
    mesa_vcap_bit_t fragment; // Fragment
    mesa_vcap_vr_t  dscp;     // DSCP field (6 bit)
    mesa_vcap_u8_t  proto;    // Protocol
    mesa_vcap_ip_t  sip;      // Source IP address - Serval: key_type = normal, ip_addr and mac_ip_addr
    mesa_vcap_ip_t  dip CAP(QOS_QCL_KEY_DIP); // Destination IP address - Serval: key_type = ip_addr and mac_ip_addr
    mesa_vcap_vr_t  sport;    // UDP/TCP: Source port - Serval: key_type = normal, ip_addr and mac_ip_addr
    mesa_vcap_vr_t  dport;    // UDP/TCP: Destination port - Serval: key_type = double_tag, ip_addr and mac_ip_addr
} mesa_qce_frame_ipv4_t;

// Frame data for MESA_QCE_TYPE_IPV6
typedef struct {
    mesa_vcap_vr_t   dscp;    // DSCP field (6 bit)
    mesa_vcap_u8_t   proto;   // Protocol
    mesa_vcap_u128_t sip;     // Source IP address (32 LSB on L26 and J1, 64 LSB on Serval when key_type = mac_ip_addr)
    mesa_vcap_u128_t dip CAP(QOS_QCL_KEY_DIP); // Destination IP address - 64 LSB on Serval when key_type = mac_ip_addr
    mesa_vcap_vr_t   sport;   // UDP/TCP: Source port - Serval: key_type = normal, ip_addr and mac_ip_addr
    mesa_vcap_vr_t   dport;   // UDP/TCP: Destination port - Serval: key_type = double_tag, ip_addr and mac_ip_addr
} mesa_qce_frame_ipv6_t;

// QCE key
typedef struct {
    mesa_port_list_t port_list;                       // Port list
    mesa_qce_mac_t   mac;                             // MAC
    mesa_qce_tag_t   tag;                             // Tag
    mesa_qce_tag_t   inner_tag CAP(QOS_QCL_KEY_INNER_TAG); // Inner tag
    mesa_qce_type_t  type;                            // Frame type

    union {
        // MESA_QCE_TYPE_ANY: No specific fields
        mesa_qce_frame_etype_t etype; // MESA_QCE_TYPE_ETYPE
        mesa_qce_frame_llc_t   llc;   // MESA_QCE_TYPE_LLC
        mesa_qce_frame_snap_t  snap;  // MESA_QCE_TYPE_SNAP
        mesa_qce_frame_ipv4_t  ipv4;  // MESA_QCE_TYPE_IPV4
        mesa_qce_frame_ipv6_t  ipv6;  // MESA_QCE_TYPE_IPV6
    } frame; // Frame type specific data
} mesa_qce_key_t;

// QCE action
typedef struct {
    mesa_bool_t               prio_enable;      // Enable priority classification
    mesa_prio_t               prio;             // Priority value
    mesa_bool_t               dp_enable;        // Enable DP classification
    mesa_dp_level_t           dp;               // DP value
    mesa_bool_t               dscp_enable;      // Enable DSCP classification
    mesa_dscp_t               dscp;             // DSCP value
    mesa_bool_t               pcp_dei_enable;   // Enable PCP and DEI classification
    mesa_tagprio_t            pcp;              // PCP value
    mesa_dei_t                dei;              // DEI value
    mesa_bool_t               policy_no_enable; // Enable ACL policy classification
    mesa_acl_policy_no_t      policy_no;        // ACL policy number
    mesa_bool_t               map_id_enable CAP(QOS_INGRESS_MAP_CNT); // Enable classification via ingress map
    mesa_qos_ingress_map_id_t map_id        CAP(QOS_INGRESS_MAP_CNT); // Ingress map to use for classification
} mesa_qce_action_t;

// QoS Control Entry
typedef struct {
    mesa_qce_id_t     id;         // Entry ID
    mesa_qce_key_t    key;        // QCE key
    mesa_qce_action_t action;     // QCE action
} mesa_qce_t;

// Initialize QCE to default values.
// type [IN]  QCE type.
// qce [OUT]  QCE structure.
mesa_rc mesa_qce_init(const mesa_inst_t     inst,
                      const mesa_qce_type_t type,
                      mesa_qce_t            *const qce);

// Add QCE to QCL.
// qcl_id [IN]  QCL ID.
// qce_id [IN]  QCE ID. The QCE will be added before the entry with this ID.
//              MESA_QCE_ID_LAST is reserved for inserting last.
// qce [IN]     QCE structure.
mesa_rc mesa_qce_add(const mesa_inst_t   inst,
                     const mesa_qce_id_t qce_id,
                     const mesa_qce_t    *const qce);

// Delete QCE from QCL.
// qcl_id [IN]  QCL ID.
// qce_id [IN]  QCE ID.
mesa_rc mesa_qce_del(const mesa_inst_t   inst,
                     const mesa_qce_id_t qce_id);

// Key that determines what to match
typedef enum {
    MESA_QOS_INGRESS_MAP_KEY_PCP,                   // Use PCP for tagged frames and none for the rest
    MESA_QOS_INGRESS_MAP_KEY_PCP_DEI,               // Use PCP/DEI for tagged frames and none for the rest
    MESA_QOS_INGRESS_MAP_KEY_DSCP,                  // Use DSCP as key for IP frames and none for the rest
    MESA_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI,          // Use DSCP as key for IP frames, PCP/DEI for tagged frames and none for the rest
    MESA_QOS_INGRESS_MAP_KEY_MPLS_TC                // Use MPLS TC as key for MPLS frames and none for the rest
} mesa_qos_ingress_map_key_t CAP(QOS_INGRESS_MAP_CNT);

// Actions that can be applied to classified values if the entry is matched
typedef struct {
    mesa_bool_t cos;                                // If TRUE, then replace the classified COS
    mesa_bool_t dpl;                                // If TRUE, then replace the classified DPL
    mesa_bool_t pcp;                                // If TRUE, then replace the classified PCP
    mesa_bool_t dei;                                // If TRUE, then replace the classified DEI
    mesa_bool_t dscp;                               // If TRUE, then replace the classified DSCP
    mesa_bool_t cosid;                              // If TRUE, then replace the classified COS ID
    mesa_bool_t path;                               // If TRUE, then replace the classified path COS ID
    mesa_bool_t mpls_tc;                            // If TRUE, then replace the classified MPLS TC
} mesa_qos_ingress_map_action_t CAP(QOS_INGRESS_MAP_CNT);

// Mapped values that can be applied to classified values if the entry is matched
typedef struct {
    mesa_cos_t     cos;                             // The classified COS is set to cos if action.cos is TRUE
    mesa_dpl_t     dpl;                             // The classified DPL is set to dpl if action.dpl is TRUE
    mesa_pcp_t     pcp;                             // The classified PCP is set to pcp if action.pcp is TRUE
    mesa_dei_t     dei;                             // The classified DEI is set to dei if action.dei is TRUE
    mesa_dscp_t    dscp;                            // The classified DSCP is set to dscp if action.dscp is TRUE
    mesa_cosid_t   cosid;                           // The classified COS ID is set to cosid if action.cosid is TRUE
    mesa_cosid_t   path_cosid;                      // Path COS ID value used by OAM MEP if action.path is TRUE
    mesa_mpls_tc_t mpls_tc;                         // The classified TC is set to mpls_tc if action.mpls_tc is TRUE
} mesa_qos_ingress_map_values_t CAP(QOS_INGRESS_MAP_CNT);

// Values for a combination of DSCP, PCP and DEI
typedef struct {
    mesa_qos_ingress_map_values_t dscp[64];         // Mapped values for each DSCP value
    mesa_qos_ingress_map_values_t pcp_dei[8][2];    // Mapped values for each PCP/DEI value
} mesa_qos_ingress_map_dpd_t CAP(QOS_INGRESS_MAP_CNT);

// Union of mapped values for different keys
typedef union {
    mesa_qos_ingress_map_values_t pcp[8];           // MESA_QOS_INGRESS_MAP_KEY_PCP
    mesa_qos_ingress_map_values_t pcp_dei[8][2];    // MESA_QOS_INGRESS_MAP_KEY_PCP_DEI
    mesa_qos_ingress_map_values_t dscp[64];         // MESA_QOS_INGRESS_MAP_KEY_DSCP
    mesa_qos_ingress_map_dpd_t    dpd;              // MESA_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI
    mesa_qos_ingress_map_values_t mpls_tc[8];       // MESA_QOS_INGRESS_MAP_KEY_MPLS_TC
} mesa_qos_ingress_map_maps_t CAP(QOS_INGRESS_MAP_CNT);

// The complete map. There is one of these per map id
typedef struct {
    mesa_qos_ingress_map_id_t     id;               // ID for this entry
    mesa_qos_ingress_map_key_t    key;              // Lookup key
    mesa_qos_ingress_map_action_t action;           // Action enable/disable
    mesa_qos_ingress_map_maps_t   maps;             // Maps for specific key
} mesa_qos_ingress_map_t CAP(QOS_INGRESS_MAP_CNT);

// Initialize an ingress map to default values.
// key  [IN]  Initialize to this key.
// map [OUT]  Ingress map structure.
mesa_rc mesa_qos_ingress_map_init(const mesa_inst_t                inst,
                                  const mesa_qos_ingress_map_key_t key,
                                  mesa_qos_ingress_map_t           *const map)
    CAP(QOS_INGRESS_MAP_CNT);

// Add/update an ingress map.
// map  [IN] Ingress map structure.
mesa_rc mesa_qos_ingress_map_add(const mesa_inst_t            inst,
                                 const mesa_qos_ingress_map_t *const map)
    CAP(QOS_INGRESS_MAP_CNT);

// Delete an ingress map.
// id   [IN]  Map ID.
mesa_rc mesa_qos_ingress_map_del(const mesa_inst_t               inst,
                                 const mesa_qos_ingress_map_id_t id)
    CAP(QOS_INGRESS_MAP_CNT);

// Delete all ingress maps.
mesa_rc mesa_qos_ingress_map_del_all(const mesa_inst_t inst)
    CAP(QOS_INGRESS_MAP_CNT);

// Key that determines what to match
typedef enum {
    MESA_QOS_EGRESS_MAP_KEY_COSID,                   // Use classified COS ID
    MESA_QOS_EGRESS_MAP_KEY_COSID_DPL,               // Use classified COS ID and DPL
    MESA_QOS_EGRESS_MAP_KEY_DSCP,                    // Use classified DSCP
    MESA_QOS_EGRESS_MAP_KEY_DSCP_DPL,                // Use classified DSCP and DPL
    MESA_QOS_EGRESS_MAP_KEY_MPLS_TC,                 // Use classified TC
    MESA_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL              // Use classified TC and DPL
} mesa_qos_egress_map_key_t CAP(QOS_EGRESS_MAP_CNT);

// Actions that can be applied to the frame if the entry is matched
typedef struct {
    mesa_bool_t pcp;                                 // If TRUE, then replace PCP in frame
    mesa_bool_t dei;                                 // If TRUE, then replace DEI in frame
    mesa_bool_t dscp;                                // If TRUE, then replace DSCP in frame
    mesa_bool_t path;                                // If TRUE, then replace path COS ID in frame
    mesa_bool_t mpls_tc;                             // If TRUE, then replace MPLS TC in frame
} mesa_qos_egress_map_action_t CAP(QOS_EGRESS_MAP_CNT);

// Mapped values that can be applied to classified values if the entry is matched
typedef struct {
    mesa_pcp_t     pcp;                              // The classified PCP is set to pcp if action.pcp is TRUE
    mesa_dei_t     dei;                              // The classified DEI is set to dei if action.dei is TRUE
    mesa_dscp_t    dscp;                             // The classified DSCP is set to dscp if action.dscp is TRUE
    mesa_cosid_t   path_cosid;                       // Path COS ID value used by OAM MEP if action.path is TRUE
    mesa_mpls_tc_t mpls_tc;                          // The classified TC is set to mpls_tc if action.mpls_tc is TRUE
} mesa_qos_egress_map_values_t CAP(QOS_EGRESS_MAP_CNT);

// Union of mapped values for different keys
typedef union {
    mesa_qos_egress_map_values_t cosid[8];           // MESA_QOS_EGRESS_MAP_KEY_COSID
    mesa_qos_egress_map_values_t cosid_dpl[8][4];    // MESA_QOS_EGRESS_MAP_KEY_COSID_DPL
    mesa_qos_egress_map_values_t dscp[64];           // MESA_QOS_EGRESS_MAP_KEY_DSCP
    mesa_qos_egress_map_values_t dscp_dpl[64][4];    // MESA_QOS_EGRESS_MAP_KEY_DSCP_DPL
    mesa_qos_egress_map_values_t mpls_tc[8];         // MESA_QOS_EGRESS_MAP_KEY_MPLS_TC
    mesa_qos_egress_map_values_t mpls_tc_dpl[8][4];  // MESA_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL
} mesa_qos_egress_map_maps_t CAP(QOS_EGRESS_MAP_CNT);

// The complete map. There is one of these per map id
typedef struct {
    mesa_qos_egress_map_id_t     id;                 // ID for this entry
    mesa_qos_egress_map_key_t    key;                // Lookup key
    mesa_qos_egress_map_action_t action;             // Action enable/disable
    mesa_qos_egress_map_maps_t   maps;               // Maps for specific key
} mesa_qos_egress_map_t CAP(QOS_EGRESS_MAP_CNT);

// Initialize an egress map to default values.
// key  [IN]  Initialize to this key.
// map [OUT]  Egress map structure.
mesa_rc mesa_qos_egress_map_init(const mesa_inst_t               inst,
                                 const mesa_qos_egress_map_key_t key,
                                 mesa_qos_egress_map_t           *const map)
    CAP(QOS_EGRESS_MAP_CNT);

// Add/update an egress map.
// map  [IN] Egress map structure.
mesa_rc mesa_qos_egress_map_add(const mesa_inst_t           inst,
                                const mesa_qos_egress_map_t *const map)
    CAP(QOS_EGRESS_MAP_CNT);

// Delete an egress map.
// id   [IN]  Map ID.
mesa_rc mesa_qos_egress_map_del(const mesa_inst_t              inst,
                                const mesa_qos_egress_map_id_t id)
    CAP(QOS_EGRESS_MAP_CNT);

// Delete all egress maps.
mesa_rc mesa_qos_egress_map_del_all(const mesa_inst_t inst)
    CAP(QOS_EGRESS_MAP_CNT);

// Calibrate egress shaper rates.
//
// This function calibrates the egress port and queue shapers on MESA_ARCH_SERVAL.
// Calling this function periodically will enhance the accuracy of the egress
// port and queue shapers.
// Recommended rate is between 1 to 50 times per second.
//
// Returns MESA_RC_INCOMPLETE if calibration is still needed, MESA_RC_OK if not
// needed anymore, MESA_RC_ERROR in case of an error.
// NOTICE: Everytime a shaper is changed, this function must be invoked again.
mesa_rc mesa_qos_shaper_calibrate(const mesa_inst_t inst)
    CAP(QOS_SHAPER_CALIBRATE);

// Dual leaky buckets policer configuration
typedef struct {
    mesa_policer_type_t type;         // Policer type
    mesa_bool_t         enable;       // Enable/disable policer
    mesa_bool_t         cm CAP(QOS_DLB_CM); // Colour Mode (TRUE means colour aware)
    mesa_bool_t         cf;           // Coupling Flag
    mesa_bool_t         line_rate;    // Line rate policing (default is data rate policing)
    mesa_bitrate_t      cir;          // Committed Information Rate
    mesa_burst_level_t  cbs;          // Committed Burst Size
    mesa_bitrate_t      eir;          // Excess Information Rate
    mesa_burst_level_t  ebs;          // Excess Burst Size
    mesa_bool_t         drop_yellow;  // DropOnYellow: Discard yellow frames
    mesa_opt_bool_t     mark_all_red; // MarkAllFramesRedEnable/MarkAllFramesRed: Discard all frames if red frame seen
} mesa_dlb_policer_conf_t;

// EVC policer configuration
typedef mesa_dlb_policer_conf_t mesa_evc_policer_conf_t;

#define MESA_EVC_POLICER_ID_DISCARD 4094 // EVC/ECE: Policer discards all frames
#define MESA_EVC_POLICER_ID_NONE    4095 // EVC/ECE: Policer forwards all frames
#define MESA_EVC_POLICER_ID_EVC     4096 // ECE only: Use EVC policer

// Get EVC policer configuration.
// policer_id [IN]  Policer ID.
// conf [OUT]       Policer configuration.
mesa_rc mesa_evc_policer_conf_get(const mesa_inst_t           inst,
                                  const mesa_evc_policer_id_t policer_id,
                                  mesa_evc_policer_conf_t     *const conf)
    CAP(EVC_POLICER_CNT);

// Set EVC policer configuration.
// policer_id [IN]  Policer ID.
// conf [IN]        Policer configuration.
mesa_rc mesa_evc_policer_conf_set(const mesa_inst_t             inst,
                                  const mesa_evc_policer_id_t   policer_id,
                                  const mesa_evc_policer_conf_t *const conf)
    CAP(EVC_POLICER_CNT);


#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_QOS_
