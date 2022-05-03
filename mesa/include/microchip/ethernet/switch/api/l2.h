// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_L2_
#define _MICROCHIP_ETHERNET_SWITCH_API_L2_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/switch/api/qos.h>
#include <microchip/ethernet/switch/api/tsn.h>
#include <microchip/ethernet/switch/api/vop.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/* - MAC address table --------------------------------------------- */

// MAC address entry
typedef struct
{
    mesa_vid_mac_t   vid_mac;          // VLAN ID and MAC addr
    mesa_port_list_t destination;      // Destination ports
    mesa_bool_t      copy_to_cpu;      // CPU copy flag for DMAC lookup
    mesa_bool_t      copy_to_cpu_smac; // CPU copy flag for SMAC lookup
    mesa_bool_t      locked;           // Locked/static flag
    mesa_bool_t      index_table;      // Index table used
    mesa_bool_t      aged;             // Age flag
    mesa_packet_rx_queue_t cpu_queue;  // CPU queue
} mesa_mac_table_entry_t;

// Add MAC address entry.
// entry [IN]  MAC address entry structure.
mesa_rc mesa_mac_table_add(const mesa_inst_t             inst,
                           const mesa_mac_table_entry_t  *const entry);

// Delete MAC address entry.
// vid_mac [IN]  VLAN ID and MAC address structure.
mesa_rc mesa_mac_table_del(const mesa_inst_t     inst,
                           const mesa_vid_mac_t  *const vid_mac);

// Get MAC address entry.
// vid_mac [IN]  VLAN ID and MAC address.
// entry [OUT]   MAC address entry.
mesa_rc mesa_mac_table_get(const mesa_inst_t       inst,
                           const mesa_vid_mac_t    *const vid_mac,
                           mesa_mac_table_entry_t  *const entry);

// Lookup next MAC address entry.
// vid_mac [IN]  VLAN ID and MAC address.
// entry [OUT]   MAC address entry.
mesa_rc mesa_mac_table_get_next(const mesa_inst_t       inst,
                                const mesa_vid_mac_t    *const vid_mac,
                                mesa_mac_table_entry_t  *const entry);


// MAC address table age time
typedef uint32_t mesa_mac_table_age_time_t;

// Get MAC address table age time.
// age_time [OUT]  MAC age time in seconds. Value zero disables aging.
//                 The default is 300 seconds.
mesa_rc mesa_mac_table_age_time_get(const mesa_inst_t          inst,
                                    mesa_mac_table_age_time_t  *const age_time);

// Set MAC address table age time.
// age_time [IN]  MAC age time in seconds. Value zero disables aging.
mesa_rc mesa_mac_table_age_time_set(const mesa_inst_t                inst,
                                    const mesa_mac_table_age_time_t  age_time);

// Do age scan of the MAC address table.
// This should be done periodically with interval T/2, where T is the age timer.
mesa_rc mesa_mac_table_age(const mesa_inst_t  inst);

// Do VLAN specific age scan of the MAC address table.
// vid [IN]  VLAN ID.
mesa_rc mesa_mac_table_vlan_age(const mesa_inst_t  inst,
                                const mesa_vid_t   vid);

// Flush MAC address table, i.e. remove all unlocked entries.
mesa_rc mesa_mac_table_flush(const mesa_inst_t inst);

// Delete MAC address entries learned on port.
// port_no [IN]  Port number.
mesa_rc mesa_mac_table_port_flush(const mesa_inst_t     inst,
                                  const mesa_port_no_t  port_no);

// Delete MAC address entries learned on VLAN ID.
// vid [IN]  VLAN ID.
mesa_rc mesa_mac_table_vlan_flush(const mesa_inst_t  inst,
                                  const mesa_vid_t   vid);

// Delete MAC address entries learned on port and VLAN ID.
// port_no [IN]  Port number.
// vid [IN]      VLAN ID.
mesa_rc mesa_mac_table_vlan_port_flush(const mesa_inst_t     inst,
                                       const mesa_port_no_t  port_no,
                                       const mesa_vid_t      vid);

// MAC address table status
typedef struct
{
    mesa_event_t learned;  // One or more entries were learned
    mesa_event_t replaced; // One or more entries were replaced
    mesa_event_t moved;    // One or more entries moved to another port
    mesa_event_t aged;     // One or more entries were aged
} mesa_mac_table_status_t;

// Get MAC address table status.
// status [OUT]  MAC address table status.
mesa_rc mesa_mac_table_status_get(const mesa_inst_t        inst,
                                  mesa_mac_table_status_t  *const status);

// Learning mode
typedef struct
{
    mesa_bool_t automatic;  // Automatic learning done by switch chip (default enabled)
    mesa_bool_t cpu;        // Learn frames copied to CPU (default disabled)
    mesa_bool_t discard;    // Learn frames discarded (default disabled)
} mesa_learn_mode_t;

// Get the learn mode for a port.
// port_no [IN]  Port number.
// mode [OUT]    Learn mode.
mesa_rc mesa_learn_port_mode_get(const mesa_inst_t     inst,
                                 const mesa_port_no_t  port_no,
                                 mesa_learn_mode_t     *const mode);
// Set the learn mode for a port.
// port_no [IN]  Port number.
// mode [IN]     Learn mode.
mesa_rc mesa_learn_port_mode_set(const mesa_inst_t        inst,
                                 const mesa_port_no_t     port_no,
                                 const mesa_learn_mode_t  *const mode);

/* - Operational state --------------------------------------------- */

// Get port operational state.
// port_no [IN]  Port number.
// state [OUT]   Port state, TRUE if link is up.
mesa_rc mesa_port_state_get(const mesa_inst_t     inst,
                            const mesa_port_no_t  port_no,
                            mesa_bool_t           *const state);


// Set port operational state.
// port_no [IN]  Port number.
// state [IN]    Port state, TRUE if link is up.
//               By default, all ports are down.
mesa_rc mesa_port_state_set(const mesa_inst_t     inst,
                            const mesa_port_no_t  port_no,
                            mesa_bool_t           state);

/* - Spanning Tree ------------------------------------------------- */

// Spanning Tree state
typedef enum
{
    MESA_STP_STATE_DISCARDING,  // STP state discarding (admin/operational down)
    MESA_STP_STATE_LEARNING,    // STP state learning
    MESA_STP_STATE_FORWARDING   // STP state forwarding
} mesa_stp_state_t;

// Get Spanning Tree state for a port.
// port_no [IN]  Port number.
// state [OUT]   STP state.
mesa_rc mesa_stp_port_state_get(const mesa_inst_t     inst,
                                const mesa_port_no_t  port_no,
                                mesa_stp_state_t      *const state);

// Set Spanning Tree state for a port.
// port_no [IN]  Port number.
// state [IN]    STP state. By default, all ports are forwarding.
mesa_rc mesa_stp_port_state_set(const mesa_inst_t       inst,
                                const mesa_port_no_t    port_no,
                                const mesa_stp_state_t  state);

// MSTP instance number
typedef uint32_t mesa_msti_t;

#define MESA_MSTIS           (65)                         // Number of MSTP instances
#define MESA_MSTI_START      (0)                          // MSTI start number
#define MESA_MSTI_END        (MESA_MSTI_START+MESA_MSTIS) // MSTI end number
#define MESA_MSTI_ARRAY_SIZE MESA_MSTI_END                // MSTI array size

// Get MSTP instance mapping for a VLAN.
// vid [IN]    VLAN ID.
// msti [OUT]  MSTP instance.
mesa_rc mesa_mstp_vlan_msti_get(const mesa_inst_t  inst,
                                const mesa_vid_t   vid,
                                mesa_msti_t        *const msti);

// Set MSTP instance mapping for a VLAN.
// vid [IN]   VLAN ID.
// msti [IN]  MSTP instance.
//            By default, all VLANs map to the first MSTP instance.
mesa_rc mesa_mstp_vlan_msti_set(const mesa_inst_t  inst,
                                const mesa_vid_t   vid,
                                const mesa_msti_t  msti);

// Get MSTP state for a port and MSTP instance.
// port_no [IN]  Port number.
// msti [IN]     MSTP instance.
// state [OUT]   MSTP state.
mesa_rc mesa_mstp_port_msti_state_get(const mesa_inst_t     inst,
                                      const mesa_port_no_t  port_no,
                                      const mesa_msti_t     msti,
                                      mesa_stp_state_t      *const state);

// Set MSTP state for a port and MSTP instance.
// port_no [IN]  Port number.
// msti [IN]     MSTP instance.
// state [IN]    MSTP state.
//               By default, all ports are forwarding for the first MSTP instance.
mesa_rc mesa_mstp_port_msti_state_set(const mesa_inst_t       inst,
                                      const mesa_port_no_t    port_no,
                                      const mesa_msti_t       msti,
                                      const mesa_stp_state_t  state);

/* - VLAN ---------------------------------------------------------- */

// VLAN configuration
typedef struct {
    mesa_etype_t s_etype; // Alternative S-tag Ethernet Type (default 0x88a8)
} mesa_vlan_conf_t;

// Get VLAN configuration.
// conf [OUT]  VLAN configuration structure.
mesa_rc mesa_vlan_conf_get(const mesa_inst_t inst,
                           mesa_vlan_conf_t  *const conf);

// Set VLAN configuration.
// conf [IN]  VLAN configuration structure.
mesa_rc mesa_vlan_conf_set(const mesa_inst_t      inst,
                           const mesa_vlan_conf_t *const conf);

// VLAN port type configuration
typedef enum
{
    MESA_VLAN_PORT_TYPE_UNAWARE, // VLAN unaware port
    MESA_VLAN_PORT_TYPE_C,       // C-port
    MESA_VLAN_PORT_TYPE_S,       // S-port
    MESA_VLAN_PORT_TYPE_S_CUSTOM // S-port using alternative Ethernet Type
} mesa_vlan_port_type_t;

// VLAN port configuration
typedef struct
{
    mesa_vlan_port_type_t port_type;      // Port type (ingress and egress)
    mesa_vid_t            pvid;           // Port VLAN ID (PVID, ingress)
    mesa_vid_t            untagged_vid;   // Port untagged VLAN ID (UVID, egress)
    mesa_vlan_frame_t     frame_type;     // Acceptable frame type (ingress)
    mesa_bool_t           ingress_filter; // Ingress filtering
} mesa_vlan_port_conf_t;

// Get VLAN mode for port.
// port_no [IN]  Port number.
// conf [OUT]    VLAN port configuration structure.
mesa_rc mesa_vlan_port_conf_get(const mesa_inst_t      inst,
                                const mesa_port_no_t   port_no,
                                mesa_vlan_port_conf_t  *const conf);

// Set VLAN mode for port.
// port_no [IN]  Port number.
// conf [IN]     VLAN port configuration structure.
//               By default, all ports are VLAN unaware with PVID equal to 1.
mesa_rc mesa_vlan_port_conf_set(const mesa_inst_t            inst,
                                const mesa_port_no_t         port_no,
                                const mesa_vlan_port_conf_t  *const conf);

// Get VLAN membership.
// vid [IN]      VLAN ID.
// member [OUT]  VLAN port member list.
mesa_rc mesa_vlan_port_members_get(const mesa_inst_t inst,
                                   const mesa_vid_t  vid,
                                   mesa_port_list_t  *port_list);

// Set VLAN membership.
// vid [IN]     VLAN ID.
// member [IN]  VLAN port member list.
//              By default, all ports are members of VLAN 1.
mesa_rc mesa_vlan_port_members_set(const mesa_inst_t      inst,
                                   const mesa_vid_t       vid,
                                   const mesa_port_list_t *port_list);

// VLAN ID configuration
typedef struct
{
    mesa_bool_t learning;        // Enable/disable learning
    mesa_bool_t flooding;        // Enable/disable flooding
    mesa_bool_t mirror;          // Enable/disable mirroring
    mesa_bool_t ingress_filter;  // Ingress filtering
    mesa_vid_t  fid CAP(L2_SVL); // Forwarding ID for SVL/IVL control
} mesa_vlan_vid_conf_t;

// Get VLAN ID configuration
// vid [IN]    VLAN ID.
// conf [OUT]  VLAN configuration.
mesa_rc mesa_vlan_vid_conf_get(const mesa_inst_t    inst,
                               const mesa_vid_t     vid,
                               mesa_vlan_vid_conf_t *const conf);

// Set VLAN ID configuration
// vid [IN]   VLAN ID.
// conf [IN]  VLAN configuration.
// By default, all VLANs have learning enabled and the FID is equal to the VID.
mesa_rc mesa_vlan_vid_conf_set(const mesa_inst_t          inst,
                               const mesa_vid_t           vid,
                               const mesa_vlan_vid_conf_t *const conf);

// VLAN Tx tag control
typedef enum
{
    MESA_VLAN_TX_TAG_PORT,    // Egress tagging determined by VLAN port configuration
    MESA_VLAN_TX_TAG_DISABLE, // Egress tagging disabled
    MESA_VLAN_TX_TAG_ENABLE,  // Egress tagging enabled
} mesa_vlan_tx_tag_t;

// Get VLAN Tx tagging configuration.
// vid [IN]      VLAN ID.
// cnt [IN]      Number of ports.
// tx_tag [OUT]  Egress port tagging list.
mesa_rc mesa_vlan_tx_tag_get(const mesa_inst_t  inst,
                             const mesa_vid_t   vid,
                             const uint32_t     cnt,
                             mesa_vlan_tx_tag_t *const tx_tag);

// Set VLAN Tx tagging configuration.
// vid [IN]     VLAN ID.
// cnt [IN]     Number of ports.
// tx_tag [IN]  Egress port tagging list.
//              By default, the VLAN port configuration is used for all ports in all VLANs.
mesa_rc mesa_vlan_tx_tag_set(const mesa_inst_t        inst,
                             const mesa_vid_t         vid,
                             const uint32_t           cnt,
                             const mesa_vlan_tx_tag_t *const tx_tag);

// Container for VLAN counters
typedef struct {
    uint64_t frames; // Number of frames
    uint64_t bytes;  // Number of bytes
} mesa_vlan_counter_types_t CAP(L2_VLAN_COUNTERS);

// VLAN counters
typedef struct {
    mesa_vlan_counter_types_t rx_vlan_unicast;   // Number of received unicast frames or bytes
    mesa_vlan_counter_types_t rx_vlan_multicast; // Number of received multicast frames or bytes
    mesa_vlan_counter_types_t rx_vlan_broadcast; // Number of received broadcast frames or bytes
} mesa_vlan_counters_t CAP(L2_VLAN_COUNTERS);

// Get VLAN Counters.
// vid [IN]       VLAN ID.
// counters [OUT] VLAN counters.
mesa_rc mesa_vlan_counters_get(const mesa_inst_t    inst,
                               const mesa_vid_t     vid,
                               mesa_vlan_counters_t *const counters)
    CAP(L2_VLAN_COUNTERS);

// Clear VLAN Counters.
// vid [IN]  VLAN ID.
mesa_rc mesa_vlan_counters_clear(const mesa_inst_t inst,
                                 const mesa_vid_t  vid)
    CAP(L2_VLAN_COUNTERS);

/* - VCL ----------------------------------------------------------- */

// VCL port configuration
typedef struct {
    mesa_bool_t          dmac_dip; // Enable DMAC/DIP matching (default SMAC/SIP)
    mesa_vcap_key_type_t key_type; // Key type for VCL lookup
} mesa_vcl_port_conf_t;

// Get VCL port configuration.
// port_no [IN]  Port number.
// conf [OUT]    VCL port configuration structure.
mesa_rc mesa_vcl_port_conf_get(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               mesa_vcl_port_conf_t *const conf);
// Get VCL port configuration.
// port_no [IN]  Port number.
// conf [IN]     VCL port configuration structure.
//               By default, NORMAL key type and SMAC/SIP lookup is used.
mesa_rc mesa_vcl_port_conf_set(const mesa_inst_t          inst,
                               const mesa_port_no_t       port_no,
                               const mesa_vcl_port_conf_t *const conf);

// VCE frame type
typedef enum
{
    MESA_VCE_TYPE_ANY,     // Any frame type
    MESA_VCE_TYPE_ETYPE,   // Ethernet Type
    MESA_VCE_TYPE_LLC,     // LLC
    MESA_VCE_TYPE_SNAP,    // SNAP
    MESA_VCE_TYPE_IPV4,    // IPv4
    MESA_VCE_TYPE_IPV6     // IPv6
} mesa_vce_type_t;

// VCE ID type
typedef uint32_t mesa_vce_id_t;

#define MESA_VCL_IDS        256                              // Number of VCLs
#define MESA_VCL_ID_START   0                                // VCL ID start number
#define MESA_VCL_ID_END     (MESA_VCL_ID_START+MESA_VCL_IDS) // VCL ID end number
#define MESA_VCL_ARRAY_SIZE MESA_VCL_ID_END                  // VCL ID array size

#define MESA_VCE_ID_LAST 0 // Special value used to add last in list

// VCE MAC header information
typedef struct
{
    mesa_vcap_bit_t dmac_mc; // Multicast DMAC
    mesa_vcap_bit_t dmac_bc; // Broadcast DMAC
    mesa_vcap_u48_t dmac;    // DMAC
    mesa_vcap_u48_t smac;    // SMAC
} mesa_vce_mac_t;

// VCE tag information
typedef struct
{
    mesa_vcap_vid_t vid;    // VLAN ID (12 bit)
    mesa_vcap_u8_t  pcp;    // PCP (3 bit)
    mesa_vcap_bit_t dei;    // DEI
    mesa_vcap_bit_t tagged; // Tagged/untagged frame
    mesa_vcap_bit_t s_tag;  // S-tag type
} mesa_vce_tag_t;

// Frame data for MESA_VCE_TYPE_ETYPE
typedef struct
{
    mesa_vcap_u16_t etype; // Ethernet Type value
    mesa_vcap_u32_t data;  // MAC data
    mesa_vcap_u8_t  mel;   // MEG level (7 bit)
} mesa_vce_frame_etype_t;

// Frame data for MESA_VCE_TYPE_LLC
typedef struct
{
    mesa_vcap_u48_t data; // Data
} mesa_vce_frame_llc_t;

// Frame data for MESA_VCE_TYPE_SNAP
typedef struct
{
    mesa_vcap_u48_t data; // Data
} mesa_vce_frame_snap_t;

// Frame data for MESA_VCE_TYPE_IPV4
typedef struct
{
    mesa_vcap_bit_t fragment; // Fragment
    mesa_vcap_bit_t options;  // Header options
    mesa_vcap_vr_t  dscp;     // DSCP field (6 bit)
    mesa_vcap_u8_t  proto;    // Protocol
    mesa_vcap_ip_t  sip;      // Source IP address
    mesa_vcap_ip_t  dip;      // Destination IP address
    mesa_vcap_vr_t  sport;    // UDP/TCP: Source port
    mesa_vcap_vr_t  dport;    // UDP/TCP: Destination port
} mesa_vce_frame_ipv4_t;

// Frame data for MESA_VCE_TYPE_IPV6
typedef struct
{
    mesa_vcap_vr_t   dscp;  // DSCP field (6 bit)
    mesa_vcap_u8_t   proto; // Protocol
    mesa_vcap_u128_t sip;   // Source IP address
    mesa_vcap_u128_t dip;   // Destination IP address
    mesa_vcap_vr_t   sport; // UDP/TCP: Source port
    mesa_vcap_vr_t   dport; // UDP/TCP: Destination port
} mesa_vce_frame_ipv6_t;

// VCE Key
typedef struct
{
    mesa_port_list_t port_list; // Port list
    mesa_vce_mac_t   mac;       // MAC header
    mesa_vce_tag_t   tag;       // Outer tag
    mesa_vce_tag_t   inner_tag; // Inner tag
    mesa_vce_type_t  type;      // VCE frame type

    union
    {
        // MESA_VCE_TYPE_ANY: No specific fields
        mesa_vce_frame_etype_t etype; // MESA_VCE_TYPE_ETYPE
        mesa_vce_frame_llc_t   llc;   // MESA_VCE_TYPE_LLC
        mesa_vce_frame_snap_t  snap;  // MESA_VCE_TYPE_SNAP
        mesa_vce_frame_ipv4_t  ipv4;  // MESA_VCE_TYPE_IPV4
        mesa_vce_frame_ipv6_t  ipv6;  // MESA_VCE_TYPE_IPV6
    } frame;  // Frame type specific data
} mesa_vce_key_t;

// Ingress map selection
typedef enum {
    MESA_IMAP_SEL_DISABLE, // Ingress map not used
    MESA_IMAP_SEL_OUTER,   // Ingress map used for outer tag
    MESA_IMAP_SEL_INNER,   // Ingress map used for inner tag
} mesa_imap_sel_t;

// OAM detection signalled to VOE
typedef enum {
    MESA_OAM_DETECT_NONE,                     // No OAM detection
    MESA_OAM_DETECT_UNTAGGED,                 // Untagged OAM detection
    MESA_OAM_DETECT_SINGLE_TAGGED,            // Single tagged OAM detection
    MESA_OAM_DETECT_DOUBLE_TAGGED,            // Double tagged OAM detection
    MESA_OAM_DETECT_TRIPLE_TAGGED CAP(VOP_V2) // Triple tagged OAM detection
} mesa_oam_detect_t CAP(VOP);

// VCE Action
typedef struct
{
    mesa_vid_t                vid;         // Classified VLAN ID
    mesa_acl_policy_no_t      policy_no;   // ACL policy number
    mesa_bool_t               pop_enable;  // Tag pop enable
    uint8_t                   pop_cnt;     // Tag pop count
    mesa_imap_sel_t           map_sel;     // Ingress map selection
    mesa_qos_ingress_map_id_t map_id;      // Ingress map to use for classification
    mesa_iflow_id_t           flow_id;     // Ingress flow ID.
                                           // (VOP_V2) If MESA_IFLOW_ID_NONE OAM will be handled by the possibly enabled port-VOE.
    mesa_oam_detect_t         oam_detect;  // OAM detection
    mesa_bool_t               prio_enable; // Enable priority classification
    mesa_prio_t               prio;        // Priority value
    mesa_bool_t               dp_enable;   // Enable DP classification
    mesa_dp_level_t           dp;          // DP value
    mesa_bool_t               dscp_enable; // Enable DSCP classification
    mesa_dscp_t               dscp;        // DSCP value
    mesa_bool_t               pcp_enable;  // Enable PCP classification
    mesa_pcp_t                pcp;         // PCP value
    mesa_bool_t               dei_enable;  // Enable DEI classification
    mesa_dei_t                dei;         // DEI value
} mesa_vce_action_t;

// VLAN Control Entry
typedef struct
{
    mesa_vce_id_t     id;     // VCE ID
    mesa_vce_key_t    key;    // VCE Key
    mesa_vce_action_t action; // VCE Action
} mesa_vce_t;

// Initialize VCE to default values.
// type [IN]  VCE type.
// vce [OUT]  VCE structure.
mesa_rc mesa_vce_init(const mesa_inst_t      inst,
                      const mesa_vce_type_t  type,
                      mesa_vce_t             *const vce);

// Add/modify VCE.
// vce_id [IN]  VCE ID. The VCE will be added before the entry with this ID.
//                      MESA_VCE_ID_LAST is reserved for inserting last.
// vce [IN]     VCE structure.
mesa_rc mesa_vce_add(const mesa_inst_t    inst,
                     const mesa_vce_id_t  vce_id,
                     const mesa_vce_t     *const vce);

// Delete VCE.
// vce_id [IN]  VCE ID.
mesa_rc mesa_vce_del(const mesa_inst_t    inst,
                     const mesa_vce_id_t  vce_id);

/* - Ingress counters ---------------------------------------------- */

// Class/COSID count
typedef uint8_t mesa_class_cnt_t;

// Ingress counter ID
typedef uint16_t mesa_ingress_cnt_id_t;

// Allocate ingress counters.
// cnt [IN]   Number of classes/COSIDs
// id [OUT]   Ingress counter ID.
mesa_rc mesa_ingress_cnt_alloc(const mesa_inst_t      inst,
                               const mesa_class_cnt_t cnt,
                               mesa_ingress_cnt_id_t  *const id);

// Free ingress counters.
// id [IN]    Ingress counter ID.
mesa_rc mesa_ingress_cnt_free(const mesa_inst_t           inst,
                              const mesa_ingress_cnt_id_t id);

// Ingress counters
typedef struct {
    // For the following counter pairs, only the frame counters are valid in PSFP mode
    mesa_counter_pair_t rx_green;        // Rx green frames/bytes
    mesa_counter_pair_t rx_yellow;       // Rx yellow frames/bytes
    mesa_counter_pair_t rx_red;          // Rx red frames/bytes

    // The following counters are only valid in PSFP mode
    mesa_counter_t      rx_match;        // MatchingFramesCount: Rx matching frames
    mesa_counter_t      rx_gate_pass;    // PassingFramesCount: Rx passed gate
    mesa_counter_t      rx_gate_discard; // NotPassingFramesCount: Rx discarded by gate
    mesa_counter_t      rx_sdu_pass;     // PassingSDUCount: Rx passed maximum SDU size filter
    mesa_counter_t      rx_sdu_discard;  // NotPassingSDUCount: Rx discarded by maximum SDU size filter

    // The following counters are valid in any mode
    mesa_counter_pair_t rx_discard;      // Rx discarded frames/bytes
    mesa_counter_pair_t tx_discard;      // Tx discarded frames/bytes
} mesa_ingress_counters_t;

// Get ingress counters.
// id [IN]         Ingress counter ID.
// cosid [IN]      COSID.
// counters [OUT]  Counters.
mesa_rc mesa_ingress_cnt_get(const mesa_inst_t           inst,
                             const mesa_ingress_cnt_id_t id,
                             const mesa_cosid_t          cosid,
                             mesa_ingress_counters_t     *counters);

// Clear ingress counters.
// id [IN]     Ingress counter ID.
// cosid [IN]  COSID.
mesa_rc mesa_ingress_cnt_clear(const mesa_inst_t           inst,
                               const mesa_ingress_cnt_id_t id,
                               const mesa_cosid_t          cosid);

/* - Dual Leaky Bucket policers ------------------------------------ */

// DLB policer ID
typedef uint16_t mesa_dlb_policer_id_t;

// Allocate DLB policers.
// cnt [IN]   Number of classes/COSIDs
// id [OUT]   DLB policer ID.
mesa_rc mesa_dlb_policer_alloc(const mesa_inst_t      inst,
                               const mesa_class_cnt_t cnt,
                               mesa_dlb_policer_id_t  *const id);

// Free DLB policers.
// id [IN]    DLB policer ID.
mesa_rc mesa_dlb_policer_free(const mesa_inst_t           inst,
                              const mesa_dlb_policer_id_t id);

// Get DLB policer configuration.
// id [IN]     DLB policer ID.
// cosid [IN]  COSID.
// conf [OUT]  Policer configuration.
mesa_rc mesa_dlb_policer_conf_get(const mesa_inst_t           inst,
                                  const mesa_dlb_policer_id_t id,
                                  const mesa_cosid_t          cosid,
                                  mesa_dlb_policer_conf_t     *const conf);

// Set DLB policer configuration.
// id [IN]     DLB policer ID.
// cosid [IN]  COSID.
// conf [IN]   Policer configuration.
//             By default, all DLB policers are disabled.
// On Sparx-5 architecture this function has the following behavior:
// Policers are in HW divided into groups with these attributes:
//      minimum burst size
//      maximum burst size
//      minimum information rate
//      maximum information rate that is based on actual burst size. Higher burst size give higher max rate.
// A policer must fit into a group. Unsupported combinations of burst size and information rate exists.
// When requested burst size and information rate is not supported, the parameters are changed for best fit.
// Requested information rate too low is changed to the all group lowest minimum
// Requested information rate too high is changed to the all group highest maximum
// Requested burst size too low is changed to the group minimum for the selected rate
// Requested burst size too high is changed to the group maximum for the selected rate
mesa_rc mesa_dlb_policer_conf_set(const mesa_inst_t             inst,
                                  const mesa_dlb_policer_id_t   id,
                                  const mesa_cosid_t            cosid,
                                  const mesa_dlb_policer_conf_t *const conf);

// DLB policer status
typedef struct {
    mesa_bool_t mark_all_red; // MarkAllFramesRed: Discard all frames if red frame seen
} mesa_dlb_policer_status_t;

// Get DLB policer status.
// id [IN]       DLB policer ID.
// cosid [IN]    COSID.
// status [OUT]  DLB policer status.
mesa_rc mesa_dlb_policer_status_get(const mesa_inst_t           inst,
                                    const mesa_dlb_policer_id_t id,
                                    const mesa_cosid_t          cosid,
                                    mesa_dlb_policer_status_t   *const status);

/* - Ingress flow -------------------------------------------------- */

// Allocate ingress flow.
// id [OUT]   Ingress flow ID.
mesa_rc mesa_iflow_alloc(const mesa_inst_t inst,
                         mesa_iflow_id_t   *const id);

// Free ingress flow.
// id [IN]    Ingress flow ID.
mesa_rc mesa_iflow_free(const mesa_inst_t     inst,
                        const mesa_iflow_id_t id);

// Ingress flow configuration
typedef struct
{
    mesa_bool_t            cnt_enable;          // Enable ingress counter mapping
    mesa_ingress_cnt_id_t  cnt_id;              // Ingress counter ID
    mesa_bool_t            dlb_enable;          // Enable DLB policer
    mesa_dlb_policer_id_t  dlb_id;              // DLB policer ID
    mesa_voe_idx_t         voe_idx CAP(VOP);    // VOE index or MESA_VOE_IDX_NONE.
                                                // (VOP_V2) If MESA_VOE_IDX_NONE possibly enabled port-VOE will see OAM as data - else OAM will be handled by the VOE.
    mesa_voi_idx_t         voi_idx CAP(VOP_V2); // VOI index or MESA_VOI_IDX_NONE
    mesa_frer_iflow_conf_t frer CAP(L2_FRER);   // FRER ingress flow configuration
    mesa_psfp_iflow_conf_t psfp CAP(L2_PSFP);   // PSFP ingress flow configuration
    mesa_bool_t            cut_through_disable CAP(QOS_EGRESS_QUEUE_CUT_THROUGH); // Force store-and-forward
} mesa_iflow_conf_t;

// Get ingress flow configuration.
// id [IN]     Ingress flow ID.
// conf [OUT]  Ingress flow configuration.
mesa_rc mesa_iflow_conf_get(const mesa_inst_t     inst,
                            const mesa_iflow_id_t id,
                            mesa_iflow_conf_t     *const conf);

// Set ingress flow configuration.
// id [IN]    Ingress flow ID.
// conf [IN]  Ingress flow configuration.
mesa_rc mesa_iflow_conf_set(const mesa_inst_t      inst,
                            const mesa_iflow_id_t   id,
                            const mesa_iflow_conf_t *const conf);

/* - Tag Control List ---------------------------------------------- */

// TCE ID type
typedef uint32_t mesa_tce_id_t;

#define MESA_TCE_ID_LAST 0 // Special value used to add last in list

// Egress flow ID
typedef uint16_t mesa_eflow_id_t;

#define MESA_EFLOW_ID_NONE 0 // No flow ID allocated

// TCE Key
typedef struct
{
    mesa_port_list_t port_list;   // Port list
    mesa_vid_t       vid;         // Classified VLAN ID (zero means any VID)
    mesa_bool_t      flow_enable; // Enable ingress flow ID instead of VLAN ID
    mesa_iflow_id_t  flow_id;     // Ingress flow ID
} mesa_tce_key_t;

// TCE TPID selection
typedef enum {
    MESA_TPID_SEL_PORT,    // Tag pushed according to port VLAN configuration
    MESA_TPID_SEL_NONE,    // No tag pushed
    MESA_TPID_SEL_C,       // C-tag pushed
    MESA_TPID_SEL_S,       // S-tag pushed
    MESA_TPID_SEL_S_CUSTOM // S-custom tag pushed
} mesa_tpid_sel_t;

// TCE PCP selection
typedef enum {
    MESA_PCP_SEL_PORT,       // PCP selected according to port QoS configuration
    MESA_PCP_SEL_FIXED,      // Fixed PCP value
    MESA_PCP_SEL_CLASSIFIED, // Classified PCP value
    MESA_PCP_SEL_MAPPED      // Mapped PCP value
} mesa_pcp_sel_t;

// TCE DEI selection
typedef enum {
    MESA_DEI_SEL_PORT,       // DEI selected according to port QoS configuration
    MESA_DEI_SEL_FIXED,      // Fixed DEI value
    MESA_DEI_SEL_CLASSIFIED, // Classified DEI value
    MESA_DEI_SEL_MAPPED      // Mapped DEI value
} mesa_dei_sel_t;

#define MESA_TCE_VID_CLASSIFIED 0    // Use classified VID
#define MESA_TCE_VID_PRIORITY   4096 // Use priority-tag (VID zero)

// TCE tag information
typedef struct
{
    mesa_tpid_sel_t          tpid;    // TPID selection
    mesa_vid_t               vid;     // VLAN ID or special values MESA_TCE_VID_* above
    mesa_pcp_sel_t           pcp_sel; // PCP selection
    mesa_pcp_t               pcp;     // PCP value
    mesa_dei_sel_t           dei_sel; // DEI selection
    mesa_dei_t               dei;     // DEI value
    mesa_qos_egress_map_id_t map_id;  // Egress QoS map
} mesa_tce_tag_t;

// R-tag selection
typedef enum {
    MESA_RTAG_SEL_NONE,  // No R-tag pushed
    MESA_RTAG_SEL_OUTER, // Outer R-tag pushed
    MESA_RTAG_SEL_INNER, // Inner R-tag pushed
} mesa_rtag_sel_t;

// TCE R-tag information
typedef struct {
    mesa_rtag_sel_t sel; // R-tag push selection
    mesa_bool_t     pop; // R-tag popping
} mesa_tce_rtag_t;

// TCE Action
typedef struct
{
    mesa_tce_tag_t  tag;       // Outer tag
    mesa_tce_tag_t  inner_tag; // Inner tag
    uint8_t         pop_cnt;   // Tag pop count
    mesa_eflow_id_t flow_id;   // Egress flow ID.
                               // (VOP_V2) If MESA_EFLOW_ID_NONE possibly enabled port-VOE will see OAM as data.
    mesa_tce_rtag_t rtag;      // R-tag control, if capability MESA_CAP_L2_FRER is non-zero and MESA_CAP_L2_FRER_IFLOW_POP is zero.
} mesa_tce_action_t;

// Tag Control Entry
typedef struct
{
    mesa_tce_id_t     id;     // TCE ID
    mesa_tce_key_t    key;    // TCE Key
    mesa_tce_action_t action; // TCE Action
} mesa_tce_t;

// Initialize TCE to default values.
// tce [OUT]  TCE structure.
mesa_rc mesa_tce_init(const mesa_inst_t inst,
                      mesa_tce_t        *const tce);

// Add/modify TCE.
// tce_id [IN]  TCE ID. The TCE will be added before the entry with this ID.
//                      MESA_TCE_ID_LAST is reserved for inserting last.
// tce [IN]     TCE structure.
mesa_rc mesa_tce_add(const mesa_inst_t   inst,
                     const mesa_tce_id_t tce_id,
                     const mesa_tce_t    *const tce);

// Delete TCE.
// tce_id [IN]  TCE ID.
mesa_rc mesa_tce_del(const mesa_inst_t   inst,
                     const mesa_tce_id_t tce_id);

/* - Egress counters ----------------------------------------------- */

// Egress counter ID
typedef uint16_t mesa_egress_cnt_id_t;

// Allocate egress counters.
// cnt [IN]   Number of classes/COSIDs
// id [OUT]   Egress counter ID.
mesa_rc mesa_egress_cnt_alloc(const mesa_inst_t      inst,
                              const mesa_class_cnt_t cnt,
                              mesa_egress_cnt_id_t   *const id);

// Free egress counters.
// id [IN]    Egress counter ID.
mesa_rc mesa_egress_cnt_free(const mesa_inst_t          inst,
                             const mesa_egress_cnt_id_t id);

// Egress counters
typedef struct {
    mesa_counter_pair_t tx_green;   // Tx green frames/bytes
    mesa_counter_pair_t tx_yellow;  // Tx yellow frames/bytes
} mesa_egress_counters_t;

// Get egress counters.
// id [IN]         Egress counter ID.
// cosid [IN]      COSID.
// counters [OUT]  Counters.
mesa_rc mesa_egress_cnt_get(const mesa_inst_t          inst,
                            const mesa_egress_cnt_id_t id,
                            const mesa_cosid_t         cosid,
                            mesa_egress_counters_t     *counters);

// Clear egress counters.
// id [IN]     Egress counter ID.
// cosid [IN]  COSID.
mesa_rc mesa_egress_cnt_clear(const mesa_inst_t          inst,
                              const mesa_egress_cnt_id_t id,
                              const mesa_cosid_t         cosid);

/* - Egress flow --------------------------------------------------- */

// Allocate egress flow.
// id [OUT]   Egress flow ID.
mesa_rc mesa_eflow_alloc(const mesa_inst_t inst,
                         mesa_eflow_id_t   *const id);

// Free egress flow.
// id [IN]    Egress flow ID.
mesa_rc mesa_eflow_free(const mesa_inst_t     inst,
                        const mesa_eflow_id_t id);

// Egress flow configuration
typedef struct
{
    mesa_bool_t          cnt_enable;          // Enable ingress counter mapping
    mesa_egress_cnt_id_t cnt_id;              // Ingress counter ID
    mesa_voe_idx_t       voe_idx CAP(VOP);    // VOE index or MESA_VOE_IDX_NONE. 
                                              // (VOP_V2) If MESA_VOE_IDX_NONE possibly enabled port-VOE will see OAM as data - else OAM will be handled by the VOE.
    mesa_voi_idx_t       voi_idx CAP(VOP_V2); // VOI index or MESA_VOI_IDX_NONE
} mesa_eflow_conf_t;

// Get egress flow configuration.
// id [IN]     Egress flow ID.
// conf [OUT]  Egress flow configuration.
mesa_rc mesa_eflow_conf_get(const mesa_inst_t     inst,
                            const mesa_eflow_id_t id,
                            mesa_eflow_conf_t     *const conf);

// Set egress flow configuration.
// id [IN]    Egress flow ID.
// conf [IN]  Egress flow configuration.
mesa_rc mesa_eflow_conf_set(const mesa_inst_t       inst,
                            const mesa_eflow_id_t   id,
                            const mesa_eflow_conf_t *const conf);

/* - VLAN translation ---------------------------------------------- */

// VLAN translation port-to-group configuration
typedef struct {
    uint16_t         group_id;  // Group ID
    mesa_port_list_t port_list; // Port list
} mesa_vlan_trans_port2grp_conf_t;

// VLAN translation direction
typedef enum {
    MESA_VLAN_TRANS_DIR_BOTH,     // Bidirectional translation
    MESA_VLAN_TRANS_DIR_INGRESS,  // Ingress translation
    MESA_VLAN_TRANS_DIR_EGRESS    // Egress translation
} mesa_vlan_trans_dir_t;

// VLAN translation group-to-VLAN configuration
typedef struct {
    uint16_t              group_id;  // Group ID
    mesa_vid_t            vid;       // External VLAN ID (ingress key, egress data)
    mesa_vid_t            trans_vid; // Internal VLAN ID (egress key, ingress data)
    mesa_vlan_trans_dir_t dir;       // Direction
} mesa_vlan_trans_grp2vlan_conf_t;

// Add VLAN Translation Group entry.
// conf      [IN]  Translation configuration.
mesa_rc mesa_vlan_trans_group_add(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const conf);

// Delete VLAN Translation Group entry.
// conf [IN] Translation configuration.
mesa_rc mesa_vlan_trans_group_del(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const conf);

// Get VLAN Translation Group entry.
// in   [IN]  Translation configuration.
// conf [OUT] Translation configuration.
mesa_rc mesa_vlan_trans_group_get(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const in,
                                  mesa_vlan_trans_grp2vlan_conf_t       *const conf);

// Get next VLAN Translation Group entry.
// in   [IN]  Translation configuration.
// conf [OUT] Translation configuration.
mesa_rc mesa_vlan_trans_group_get_next(const mesa_inst_t                     inst,
                                       const mesa_vlan_trans_grp2vlan_conf_t *const in,
                                       mesa_vlan_trans_grp2vlan_conf_t       *conf);

// Associate VLAN Translation Group entries to a port_list.
// Each port can only be member of one group.
// conf [IN]  Translation group.
mesa_rc mesa_vlan_trans_group_to_port_set(const mesa_inst_t                     inst,
                                          const mesa_vlan_trans_port2grp_conf_t *const conf);

// VLAN Translation function to fetch all ports for a group.
// group_id [IN]  Group ID.
// conf     [OUT] Translation group.
mesa_rc mesa_vlan_trans_group_to_port_get(const mesa_inst_t               inst,
                                          const uint16_t                  group_id,
                                          mesa_vlan_trans_port2grp_conf_t *conf);

// VLAN Translation function to fetch all ports for next group.
// group_id [IN]  Group ID.
// conf     [OUT] Translation group.
mesa_rc mesa_vlan_trans_group_to_port_get_next(const mesa_inst_t               inst,
                                               const uint16_t                  group_id,
                                               mesa_vlan_trans_port2grp_conf_t *conf);

// VCAP port configuration
typedef struct {
    mesa_vcap_key_type_t key_type_is1_1; // Key type for second IS1 lookup
    mesa_bool_t          dmac_dip_1;     // Enable DMAC/DIP matching in second lookup (default SMAC/SIP)
} mesa_vcap_port_conf_t CAP(L2_VCAP_PORT_CONF);

// Get VCAP port configuration.
// port_no [IN]  Port number.
// conf [OUT]    VCAP port configuration structure.
mesa_rc mesa_vcap_port_conf_get(const mesa_inst_t     inst,
                                const mesa_port_no_t  port_no,
                                mesa_vcap_port_conf_t *const conf)
    CAP(L2_VCAP_PORT_CONF);

// Set VCAP port configuration.
// port_no [IN]  Port number.
// conf [IN]     VCAP port configuration structure.
mesa_rc mesa_vcap_port_conf_set(const mesa_inst_t           inst,
                                const mesa_port_no_t        port_no,
                                const mesa_vcap_port_conf_t *const conf)
    CAP(L2_VCAP_PORT_CONF);

/* - Port Isolation------------------------------------------------- */

// Get enable/disable port isolation for VLAN.
// vid [IN]        VLAN ID.
// isolated [OUT]  VLAN isolation enable/disable option.
mesa_rc mesa_isolated_vlan_get(const mesa_inst_t  inst,
                               const mesa_vid_t   vid,
                               mesa_bool_t        *const isolated);


// Set enable/disable port isolation for VLAN.
// vid [IN]       VLAN ID.
// isolated [IN]  VLAN isolation enable/disable option.
//                By default, port isolation is disabled for all VLANs.
mesa_rc mesa_isolated_vlan_set(const mesa_inst_t  inst,
                               const mesa_vid_t   vid,
                               const mesa_bool_t  isolated);

// Get the isolated port member set.
// member [OUT]  Isolated port member list.
mesa_rc mesa_isolated_port_members_get(const mesa_inst_t inst,
                                       mesa_port_list_t  *port_list);

// Set the isolated port member set.
// member [IN]  Isolated port member list.
//              By default, no ports are isolated.
mesa_rc mesa_isolated_port_members_set(const mesa_inst_t      inst,
                                       const mesa_port_list_t *port_list);

/* - Private VLAN (PVLAN) ------------------------------------------ */

// Private VLAN Number
typedef uint32_t mesa_pvlan_no_t;

// Get Private VLAN membership.
// pvlan_no [IN]  Private VLAN group number.
// member [OUT]   Private VLAN port member list.
mesa_rc mesa_pvlan_port_members_get(const mesa_inst_t     inst,
                                    const mesa_pvlan_no_t pvlan_no,
                                    mesa_port_list_t      *port_list);

// Set Private VLAN membership.
// pvlan_no [IN]  Private VLAN group number.
// member [IN]    Private VLAN port member list.
//                By default, all ports are member of PVLAN 0.
mesa_rc mesa_pvlan_port_members_set(const mesa_inst_t      inst,
                                    const mesa_pvlan_no_t  pvlan_no,
                                    const mesa_port_list_t *port_list);

// Get Asymmetric Private VLAN membership.
// port_no [IN]  Ingress port.
// member [OUT]  Asymmetric Private VLAN port member list.
mesa_rc mesa_apvlan_port_members_get(const mesa_inst_t    inst,
                                     const mesa_port_no_t port_no,
                                     mesa_port_list_t     *port_list);

// Set Asymmetric Private VLAN membership.
// port_no [IN]  Ingress port.
// member [IN]   Asymmetric Private VLAN port member list.
//               By default, all ports are allowed to forward to all other ports.
mesa_rc mesa_apvlan_port_members_set(const mesa_inst_t      inst,
                                     const mesa_port_no_t   port_no,
                                     const mesa_port_list_t *port_list);


// Destination port group number
typedef mesa_port_no_t mesa_dgroup_no_t;

// Destination group port configuration
typedef struct {
    mesa_dgroup_no_t dgroup_no; // Destination port group
} mesa_dgroup_port_conf_t;

// Get Destination Group configuration for port.
// port_no [IN]  Port number.
// conf [OUT]    Destination group port configuration.
mesa_rc mesa_dgroup_port_conf_get(const mesa_inst_t       inst,
                                  const mesa_port_no_t    port_no,
                                  mesa_dgroup_port_conf_t *const conf);

// Set Destination Group configuration for port.
// port_no [IN]  Port number.
// conf [IN]     Destination group port configuration.
//               By default, the destination group for each port is equal to the port number.
mesa_rc mesa_dgroup_port_conf_set(const mesa_inst_t             inst,
                                  const mesa_port_no_t          port_no,
                                  const mesa_dgroup_port_conf_t *const conf);

/* - SFLOW --------------------------------------------------------- */

// sFlow configuration structure.
// Not all sampling rates are supported.
// Since the sFlow standard mandates that returned sample rates are
// actual sample rates and not desired sample rates, it is recommended
// to call mesa_sflow_sampling_rate_convert() to obtain the actual
// sample rate given a desired sample rate.
// mesa_sflow_port_conf_set() will auto-convert the requested sample rate
// to an actual sample rate, which will be returned in subsequent calls
// to mesa_sflow_port_conf_get().

// sFlow ingress and/or egress sampling is supported.
typedef enum {
    MESA_SFLOW_TYPE_NONE = 0, // Sampler is not enabled on the port.
    MESA_SFLOW_TYPE_RX,       // Sampler is enabled for ingress on the port.
    MESA_SFLOW_TYPE_TX,       // Sampler is enabled for egress on the port.
    MESA_SFLOW_TYPE_ALL       // Sampler is enabled for both ingress and egress on the port.
} mesa_sflow_type_t;

typedef struct {
    mesa_sflow_type_t type;          // Sample direction. Also used to turn off sampling.
    uint32_t          sampling_rate; // A value of N means: sample on average 1 out of N frames. 0 disables sampling.
} mesa_sflow_port_conf_t;

// Get port sFlow configuration.
// port_no [IN]  Port number (a.k.a. data source).
// conf    [OUT] sFlow sampler configuration.
mesa_rc mesa_sflow_port_conf_get(const mesa_inst_t            inst,
                                 const mesa_port_no_t         port_no,
                                       mesa_sflow_port_conf_t *const conf);

// Set port sFlow configuration.
// port_no [IN] Port number (a.k.a. data source).
// conf    [IN] sFlow sampler configuration.
mesa_rc mesa_sflow_port_conf_set(const mesa_inst_t            inst,
                                 const mesa_port_no_t         port_no,
                                 const mesa_sflow_port_conf_t *const conf);

// Convert desired sample rate to supported sample rate
//
// Since it may not be possible to realize all desired sample rates
// in H/W, this function can be used to query for an actual
// sample rate given a desired sample rate.
//
// If the sFlow application code wishes to support more than one
// sampler instance per port, it will have to use only powers of
// two for the sampling rate. To obtain powers of two sampling
// rates, given an arbitrary input sampling rate, set power2 to TRUE,
// otherwise set it to FALSE.
//
// power2   [IN]  Only return sampling rates in powers of two.
// rate_in  [IN]  Desired sample rate
// rate_out [OUT] Realizable sample rate
mesa_rc mesa_sflow_sampling_rate_convert(const mesa_inst_t inst,
                                         const mesa_bool_t power2,
                                         const uint32_t    rate_in,
                                               uint32_t    *const rate_out);

/* - Aggregation --------------------------------------------------- */

// Get aggregation port members.
// aggr_no [IN]  Aggregation number.
// member [OUT]  Aggregation port member list.
mesa_rc mesa_aggr_port_members_get(const mesa_inst_t    inst,
                                   const mesa_aggr_no_t aggr_no,
                                   mesa_port_list_t     *port_list);

// Set aggregation port members.
// aggr_no [IN]  Aggregation number.
// member [IN]   Aggregation port member list.
//               By default, no ports are aggregated.
mesa_rc mesa_aggr_port_members_set(const mesa_inst_t      inst,
                                   const mesa_aggr_no_t   aggr_no,
                                   const mesa_port_list_t *port_list);

// Aggregation traffic distribution mode
typedef struct
{
    mesa_bool_t smac_enable;        // Source MAC address
    mesa_bool_t dmac_enable;        // Destination MAC address
    mesa_bool_t sip_dip_enable;     // Source and destination IP address
    mesa_bool_t sport_dport_enable; // Source and destination UDP/TCP port
} mesa_aggr_mode_t;

// Get aggregation traffic distribution mode.
// mode [OUT]  Distribution mode structure.
mesa_rc mesa_aggr_mode_get(const mesa_inst_t  inst,
                           mesa_aggr_mode_t   *const mode);


// Set aggregation traffic distribution mode.
// mode [IN]  Distribution mode structure.
//            By default, SMAC is enabled.
mesa_rc mesa_aggr_mode_set(const mesa_inst_t       inst,
                           const mesa_aggr_mode_t  *const mode);

/* - Mirroring ----------------------------------------------------- */

// Mirror port configuration
typedef enum
{
    MESA_MIRROR_TAG_NONE,    // No mirror tag is added
    MESA_MIRROR_TAG_C,       // C-tag is added
    MESA_MIRROR_TAG_S,       // S-tag is added
    MESA_MIRROR_TAG_S_CUSTOM // Custom S-tag is added
} mesa_mirror_tag_t CAP(L2_MIRROR_TAG);

// Mirror configuration
typedef struct
{
    mesa_port_no_t    port_no;                // Mirror port or MESA_PORT_NO_NONE
    mesa_bool_t       fwd_enable;             // Enable normal traffic forwarding to mirror port
    mesa_mirror_tag_t tag CAP(L2_MIRROR_TAG); // Mirror tag type
    mesa_vid_t        vid CAP(L2_MIRROR_TAG); // Mirror tag VID
    mesa_tagprio_t    pcp CAP(L2_MIRROR_TAG); // Mirror tag PCP
    mesa_dei_t        dei CAP(L2_MIRROR_TAG); // Mirror tag DEI
} mesa_mirror_conf_t;

// Get the mirror configuration.
// conf [OUT]  Mirror configuration.
mesa_rc mesa_mirror_conf_get(const mesa_inst_t  inst,
                             mesa_mirror_conf_t *const conf);

// Set the mirror configuration.
// conf [IN]  Mirror configuration.
//            By default, mirroring is disabled.
mesa_rc mesa_mirror_conf_set(const mesa_inst_t        inst,
                             const mesa_mirror_conf_t *const conf);

// Get the mirror monitor port.
// port_no [OUT]  Port number.
mesa_rc mesa_mirror_monitor_port_get(const mesa_inst_t  inst,
                                     mesa_port_no_t     *const port_no);

// Set the mirror monitor port.
// port_no [IN]  Port number or MESA_PORT_NO_NONE.
mesa_rc mesa_mirror_monitor_port_set(const mesa_inst_t     inst,
                                     const mesa_port_no_t  port_no);

// Get the mirror ingress ports list.
// member [OUT]  Port member list.
mesa_rc mesa_mirror_ingress_ports_get(const mesa_inst_t inst,
                                      mesa_port_list_t  *port_list);

// Set the mirror ingress port list.
// member [IN]  Port member list.
mesa_rc mesa_mirror_ingress_ports_set(const mesa_inst_t      inst,
                                      const mesa_port_list_t *port_list);

// Get the mirror egress port list.
// member [OUT]  Port member list.
mesa_rc mesa_mirror_egress_ports_get(const mesa_inst_t inst,
                                     mesa_port_list_t  *port_list);

// Set the mirror egress port list.
// member [IN]  Port member list.
mesa_rc mesa_mirror_egress_ports_set(const mesa_inst_t      inst,
                                     const mesa_port_list_t *port_list);

// Get the mirror CPU ingress.
// member [OUT]  CPU  member
mesa_rc mesa_mirror_cpu_ingress_get(const mesa_inst_t  inst,
                                    mesa_bool_t        *member);

// Set CPU ingress mirroring (frames from the CPU)
// member [IN]  CPU member.
mesa_rc mesa_mirror_cpu_ingress_set(const mesa_inst_t  inst,
                                    const mesa_bool_t  member);

// Get the mirror CPU egress
// member [OUT]  CPU member.
mesa_rc mesa_mirror_cpu_egress_get(const mesa_inst_t  inst,
                                   mesa_bool_t        *member);

// Set the mirror CPU egress (frames to the CPU)
// member [IN]  CPU member.
mesa_rc mesa_mirror_cpu_egress_set(const mesa_inst_t  inst,
                                   const mesa_bool_t  member);

/* - Flooding control ---------------------------------------------- */

// Get unicast flood members.
// member [OUT]  Port member list.
mesa_rc mesa_uc_flood_members_get(const mesa_inst_t inst,
                                  mesa_port_list_t  *port_list);

// Set unicast flood members.
// member [IN]  Port member list.
//              By default, all ports are members.
mesa_rc mesa_uc_flood_members_set(const mesa_inst_t      inst,
                                  const mesa_port_list_t *port_list);

// Get multicast flood members.
// member [OUT]  Port member list.
mesa_rc mesa_mc_flood_members_get(const mesa_inst_t inst,
                                  mesa_port_list_t  *port_list);

// Set multicast flood members.
// This member set is used when flooding multicast frames, which are not IPv4/IPv6 data frames.
// member [IN]  Port member list.
//              By default, all ports are members.
mesa_rc mesa_mc_flood_members_set(const mesa_inst_t      inst,
                                  const mesa_port_list_t *port_list);

/* - IPv4 multicast ------------------------------------------ */

// Get IPv4 multicast flood members.
// member [OUT]  Port member list.
mesa_rc mesa_ipv4_mc_flood_members_get(const mesa_inst_t inst,
                                       mesa_port_list_t  *port_list);

// Set IPv4 multicast flood members.
// This member set is used when flooding IPv4 multicast data frames, meaning
// DIP in range 224.0.1.0 to 239.255.255.255.
// member [IN]  Port member list.
//              Ports connected to IPv4 multicast routers should be enabled.
//              By default, all ports are members.
mesa_rc mesa_ipv4_mc_flood_members_set(const mesa_inst_t      inst,
                                       const mesa_port_list_t *port_list);

// Add IPv4 multicast entry.
// vid [IN]     VLAN ID.
// sip [IN]     Source IP address (zero means any source).
// dip [IN]     Destination IP address.
// member [IN]  Port member list.
mesa_rc mesa_ipv4_mc_add(const mesa_inst_t      inst,
                         const mesa_vid_t       vid,
                         const mesa_ip_t        sip,
                         const mesa_ip_t        dip,
                         const mesa_port_list_t *port_list)
    CAP(L2_IPV4_MC_SIP);

// Delete IPv4 multicast entry.
// vid [IN]     VLAN ID.
// sip [IN]     Source IP address.
// dip [IN]     Destination IP address.
mesa_rc mesa_ipv4_mc_del(const mesa_inst_t inst,
                         const mesa_vid_t  vid,
                         const mesa_ip_t   sip,
                         const mesa_ip_t   dip)
    CAP(L2_IPV4_MC_SIP);

/* - IPv6 multicast ------------------------------------------- */

// Get IPv6 multicast flood members.
// member [OUT]  Port member list.
mesa_rc mesa_ipv6_mc_flood_members_get(const mesa_inst_t inst,
                                       mesa_port_list_t  *port_list);

// Set IPv6 multicast flood members.
// This member set is used when flooding IPv6 multicast data frames, meaning
// DIP in range FF00::/8 (optionally except Link-Local addresses, see below).
// member [IN]  Port member list.
//              Ports connected to IPv6 multicast routers should be enabled.
//              By default, all ports are members.
mesa_rc mesa_ipv6_mc_flood_members_set(const mesa_inst_t      inst,
                                       const mesa_port_list_t *port_list);

// Get IPv6 multicast control flooding mode.
// scope [OUT]  IPv6 multicast control flood.
mesa_rc mesa_ipv6_mc_ctrl_flood_get(const mesa_inst_t  inst,
                                    mesa_bool_t        *const scope);

// Set IPv6 multicast control flooding mode.
// This controls whether unknown Link-Local scope IPv6 multicasts (FF02::/16) are flooded
// using the multicast port list or the IPv6 multicast port list.
// scope [IN]  IPv6 multicast control flood.
//             0: Flood to multicast port members.
//             1: Flood to IPv6 multicast flood members.
mesa_rc mesa_ipv6_mc_ctrl_flood_set(const mesa_inst_t  inst,
                                    const mesa_bool_t  scope);

// Add IPv6 multicast entry.
// vid [IN]     VLAN ID.
// sip [IN]     Source IP address (zero means any source).
// dip [IN]     Destination IP address.
// member [IN]  Port member list.
mesa_rc mesa_ipv6_mc_add(const mesa_inst_t      inst,
                         const mesa_vid_t       vid,
                         const mesa_ipv6_t      sip,
                         const mesa_ipv6_t      dip,
                         const mesa_port_list_t *port_list)
    CAP(L2_IPV6_MC_SIP);

// Delete IPv6 multicast entry.
// vid [IN]  VLAN ID.
// sip [IN]  Source IP address.
// dip [IN]  Destination IP address.
mesa_rc mesa_ipv6_mc_del(const mesa_inst_t inst,
                         const mesa_vid_t  vid,
                         const mesa_ipv6_t sip,
                         const mesa_ipv6_t dip)
    CAP(L2_IPV6_MC_SIP);


/* - Ethernet Protection Switching ---------------------------------- */

// Port protection type
typedef enum
{
    MESA_EPS_PORT_1_PLUS_1, // 1+1 protection
    MESA_EPS_PORT_1_FOR_1   // 1:1 protection
} mesa_eps_port_type_t;

// Port protection configuration
typedef struct
{
    mesa_eps_port_type_t type;    // Protection type
    mesa_port_no_t       port_no; // Protection port or MESA_PORT_NO_NONE
} mesa_eps_port_conf_t;

// Get EPS port configuration.
// port_no [IN]  Working port.
// conf [OUT]    Protection configuration.
mesa_rc mesa_eps_port_conf_get(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               mesa_eps_port_conf_t  *const conf);

// Set EPS port configuration.
// port_no [IN]  Working port.
// conf [IN]     Protection configuration.
//               By default, all ports are unprotected.
mesa_rc mesa_eps_port_conf_set(const mesa_inst_t           inst,
                               const mesa_port_no_t        port_no,
                               const mesa_eps_port_conf_t  *const conf);


// EPS selector
typedef enum
{
    MESA_EPS_SELECTOR_WORKING,    // Select working port
    MESA_EPS_SELECTOR_PROTECTION  // Select protection port
} mesa_eps_selector_t;

// Get EPS port selector.
// port_no [IN]    Working port.
// selector [OUT]  Selector.
mesa_rc mesa_eps_port_selector_get(const mesa_inst_t     inst,
                                   const mesa_port_no_t  port_no,
                                   mesa_eps_selector_t   *const selector);

// Set EPS port selector.
// port_no [IN]   Working port.
// selector [IN]  Selector.
mesa_rc mesa_eps_port_selector_set(const mesa_inst_t          inst,
                                   const mesa_port_no_t       port_no,
                                   const mesa_eps_selector_t  selector);

/* - Ethernet Ring Protection Swiching ----------------------------- */

// ERPS instance number
typedef uint32_t mesa_erpi_t;

#define MESA_ERPIS           (64)                         // Number of ERPS instances
#define MESA_ERPI_START      (0)                          // ERPI start number
#define MESA_ERPI_END        (MESA_ERPI_START+MESA_ERPIS) // ERPI end number
#define MESA_ERPI_ARRAY_SIZE MESA_ERPI_END                // ERPI array size

// Get ERPS member state for a VLAN.
// erpi [IN]     ERPS instance.
// vid [IN]      VLAN ID.
// member [OUT]  Membership.
mesa_rc mesa_erps_vlan_member_get(const mesa_inst_t inst,
                                  const mesa_erpi_t erpi,
                                  const mesa_vid_t  vid,
                                  mesa_bool_t       *const member);

// Set ERPS member state for a VLAN.
// erpi [IN]    ERPS instance.
// vid [IN]     VLAN ID.
// member [IN]  Membership, TRUE if VLAN is included in ERPS instance.
//              By default, no VLANs map to a ring instance.
mesa_rc mesa_erps_vlan_member_set(const mesa_inst_t inst,
                                  const mesa_erpi_t erpi,
                                  const mesa_vid_t  vid,
                                  const mesa_bool_t member);

// ERPS state
typedef enum {
    MESA_ERPS_STATE_FORWARDING, // Forwarding
    MESA_ERPS_STATE_DISCARDING, // Discarding
} mesa_erps_state_t;

// Get ERPS state for ERPS instance and port.
// erpi [IN]     ERPS instance.
// port_no [IN]  Port number.
// state [OUT]   ERPS state.
mesa_rc mesa_erps_port_state_get(const mesa_inst_t    inst,
                                 const mesa_erpi_t    erpi,
                                 const mesa_port_no_t port_no,
                                 mesa_erps_state_t    *const state);

// Set ERPS state for ERPS instance and port.
// port_no [IN]  Port number.
// erpi [IN]     ERPS instance.
// state [IN]    ERPS state.
mesa_rc mesa_erps_port_state_set(const mesa_inst_t       inst,
                                 const mesa_erpi_t       erpi,
                                 const mesa_port_no_t    port_no,
                                 const mesa_erps_state_t state);

/* - Real-time Control List ---------------------------------------- */

// RCL VID configuration
typedef struct {
    mesa_bool_t pcp[MESA_PCP_CNT]; // PCP values
} mesa_rcl_vid_conf_t;

// Add/enable RCL VID classification.
// vid  [IN]  VLAN ID in outer tag or zero for untagged/priority-tagged frames
// conf [IN]  VLAN configuration structure.
mesa_rc mesa_rcl_vid_add(const mesa_inst_t         inst,
                         const mesa_vid_t          vid,
                         const mesa_rcl_vid_conf_t *const conf);

// Delete/disable RCL VID classification.
// vid  [IN]  VLAN ID in outer tag or zero for untagged/priority-tagged frames
mesa_rc mesa_rcl_vid_del(const mesa_inst_t inst,
                         const mesa_vid_t  vid);

// RCL Ethernet Type
typedef enum {
    MESA_RCL_ETYPE_ANY,      // Any Ethernet Type
    MESA_RCL_ETYPE_PROFINET, // Ethernet Type 0x8892
    MESA_RCL_ETYPE_OPC_UA,   // Ethernet Type 0xB62C
} mesa_rcl_etype_t;

// RCE key
typedef struct
{
    mesa_port_no_t   port_no;         // Ingress port
    mesa_vid_t       vid;             // VID or zero for untagged/priority-tagged
    mesa_vcap_bit_t  tagged;          // Outer tag
    mesa_bool_t      smac;            // SMAC/DMAC lookup selection
    mesa_vcap_u48_t  mac;             // SMAC/DMAC value
    mesa_rcl_etype_t etype;           // Ethernet type
    mesa_vcap_u16_t  frame_id;        // Profinet: FrameId
    mesa_vcap_u16_t  publisher_id;    // OPC-UA: PublisherId
    mesa_vcap_u16_t  writer_group_id; // OPC-UA: WriterGroupId
} mesa_rce_key_t;

// RCE action
typedef struct
{
    uint16_t         rtp_id;       // RTP identifier
    mesa_bool_t      rtp_sub_id;   // RTP sub-identifier
    mesa_bool_t      rtp_inbound;  // RTP inbound processing
    mesa_bool_t      port_enable;  // Enable port forwarding to egress port list
    mesa_port_list_t port_list;    // Egress port list (e.g. RTE port)
    mesa_bool_t      llct_enable;  // Enable Low-Latency Cut-Through
    mesa_port_no_t   llct_port_no; // LLCT egress port
} mesa_rce_action_t;

// RCE ID
typedef uint32_t mesa_rce_id_t;

#define MESA_RCE_ID_LAST 0 // Special value used to add last in list

// Real-time Control Entry
typedef struct
{
    mesa_rce_id_t     id;     // RCE ID
    mesa_rce_key_t    key;    // RCE Key
    mesa_rce_action_t action; // RCE Action
} mesa_rce_t;

// Initialize RCE to default values.
mesa_rc mesa_rce_init(const mesa_inst_t inst,
                      mesa_rce_t        *const rce);

// Add/modify RCE.
// rce_id [IN]  RCE ID. The RCE will be added before the entry with this ID.
//              MESA_RCE_ID_LAST is reserved for inserting last.
// rce [IN]     RCE structure.
mesa_rc mesa_rce_add(const mesa_inst_t   inst,
                     const mesa_rce_id_t rce_id,
                     const mesa_rce_t    *const rce);

// Delete RCE.
// rce_id [IN]  RCE ID.
mesa_rc mesa_rce_del(const mesa_inst_t   inst,
                     const mesa_rce_id_t rce_id);

// Legacy stacking types ------------------------------------------------------

// VStaX Unit Port Set ID (UPSID; 0-31).
typedef int mesa_vstax_upsid_t;

// Unit Port Set Port Number
typedef uint32_t mesa_vstax_upspn_t;

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_L2_
