// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_SECURITY_
#define _MICROCHIP_ETHERNET_SWITCH_API_SECURITY_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/* - Port Based Network Access Control, 802.1X --------------------- */

// Authentication state
typedef enum
{
    MESA_AUTH_STATE_NONE,   // Not authenticated
    MESA_AUTH_STATE_EGRESS, // Authenticated in egress direction
    MESA_AUTH_STATE_BOTH    // Authenticated in both directions
} mesa_auth_state_t;

// Get 802.1X Authentication state for a port.
// port_no [IN]  Port number.
// state [OUT]   Authentication state.
mesa_rc mesa_auth_port_state_get(const mesa_inst_t    inst,
                                 const mesa_port_no_t port_no,
                                 mesa_auth_state_t    *const state);

// Set 802.1X Authentication state for a port.
// port_no [IN]  Port number.
// state [IN]    Authentication state.
//               By default, all ports are authenticated.
mesa_rc mesa_auth_port_state_set(const mesa_inst_t       inst,
                                 const mesa_port_no_t    port_no,
                                 const mesa_auth_state_t state);

/* - Access Control Lists ------------------------------------------ */

// ACL policer configuration
typedef struct {
    mesa_bool_t        bit_rate_enable; // Use bit rate policing instead of packet rate
    mesa_bitrate_t     bit_rate;        // Bit rate
    mesa_packet_rate_t rate;            // Packet rate
} mesa_acl_policer_conf_t;

// Get ACL policer configuration.
// policer_no [IN]  ACL policer number.
// conf [OUT]       ACL policer configuration.
mesa_rc mesa_acl_policer_conf_get(const mesa_inst_t           inst,
                                  const mesa_acl_policer_no_t policer_no,
                                  mesa_acl_policer_conf_t     *const conf);

// Set ACL policer configuration.
// policer_no [IN]  ACL policer number.
// conf [IN]        ACL policer configuration.
mesa_rc mesa_acl_policer_conf_set(const mesa_inst_t             inst,
                                  const mesa_acl_policer_no_t   policer_no,
                                  const mesa_acl_policer_conf_t *const conf);

// ACL port action
typedef enum
{
    MESA_ACL_PORT_ACTION_NONE,   // No action from port list
    MESA_ACL_PORT_ACTION_FILTER, // Port list filter is used
    MESA_ACL_PORT_ACTION_REDIR   // Port list redirect is used
} mesa_acl_port_action_t;

// ACL PTP action
typedef enum
{
    MESA_ACL_PTP_ACTION_NONE,     // No PTP action
    MESA_ACL_PTP_ACTION_ONE_STEP, // PTP one-step time-stamping
    MESA_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY   CAP(ACL_PTP_DELAY), // PTP one-step time-stamping, Serval: add delay, Jr2: Add EDLY
    MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1 CAP(ACL_PTP_DELAY), // PTP one-step time-stamping, Serval: subtract delay 1, Jr2: Add IDLY1
    MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2 CAP(ACL_PTP_DELAY), // PTP one-step time-stamping, Serval: subtract delay 2, Jr2: Add IDLY2
    MESA_ACL_PTP_ACTION_ONE_AND_TWO_STEP     CAP(ACL_PTP_ONE_AND_TWO_STEP), // PTP one-step and two-step time-stamping
    MESA_ACL_PTP_ACTION_TWO_STEP // PTP two-step time-stamping
} mesa_acl_ptp_action_t;

// ACL Source IP index. For IPv6 entries, it must be divisible by 4 and consumes 4 rules
typedef uint8_t mesa_acl_sip_idx_t CAP(ACL_SIP_CNT);

// ACL Source IP configuration
typedef struct {
    mesa_ip_addr_t sip; // Source IP address
} mesa_acl_sip_conf_t;

// Set ACL Source IP configuration for index.
// idx  [IN]  Entry index.
// conf [IN]  Source IP configuration.
mesa_rc mesa_acl_sip_conf_set(const mesa_inst_t          inst,
                              const mesa_acl_sip_idx_t   idx,
                              const mesa_acl_sip_conf_t  *const conf)
    CAP(ACL_SIP_CNT);

// ACL PTP response action
typedef enum
{
    MESA_ACL_PTP_RSP_NONE,               // No response action
    MESA_ACL_PTP_RSP_DLY_REQ_RSP_TS_UPD, // Auto response to Delay_Req, includes receiveTimestamp update
    MESA_ACL_PTP_RSP_DLY_REQ_RSP_NO_TS   // Auto response to Delay_Req, exludes receiveTimestamp update
} mesa_acl_ptp_rsp_t CAP(ACL_SIP_CNT);

// ACL PTP RedBox forwarding
typedef struct {
    mesa_bool_t enable; // Enable processing
    mesa_bool_t srcid;  // SourcePortIdentity forwarding
    mesa_bool_t reqid;  // RequestingPortIdentity forwarding
} mesa_acl_ptp_rb_fwd_t;

// ACL PTP action configuration
typedef struct {
    mesa_acl_ptp_rsp_t    response;             // PTP Delay_Req/Response action
    int8_t                log_message_interval; // PTP logMessageInterval [-8,7] returned in the Delay_Resp message
    mesa_bool_t           copy_smac_to_dmac;    // PTP DMAC operation
    mesa_bool_t           set_smac_to_port_mac; // PTP SMAC operation
    uint8_t               dom_sel;              // PTP domain selector. PTP_DOM_SEL indexes the PTP configuration
    mesa_udp_tcp_t        sport;                // UDP source port
    mesa_udp_tcp_t        dport;                // UDP destination port
    mesa_acl_ptp_rb_fwd_t rb_fwd;               // RedBox forwarding
} mesa_acl_ptp_action_conf_t CAP(ACL_SIP_CNT);

// ACL address update
typedef enum {
    MESA_ACL_ADDR_UPDATE_NONE,             // No SMAC/DMAC change
    MESA_ACL_ADDR_UPDATE_MAC_SWAP,         // Swap SMAC and DMAC
    MESA_ACL_ADDR_UPDATE_DMAC_REPLACE,     // Replace DMAC
    MESA_ACL_ADDR_UPDATE_DMAC_REPLACE_MSB, // Replace 40 MSB of DMAC
    MESA_ACL_ADDR_UPDATE_MAC_IP_SWAP_UC,   // Swap MAC addresses if DMAC is unicast. Replace SMAC if DMAC is multicast. Same for SIP/DIP
    MESA_ACL_ADDR_UPDATE_IGR_MAC_SWAP,              // Ingress: Swap SMAC and DMAC
    MESA_ACL_ADDR_UPDATE_IGR_DMAC_SMAC_INCR,        // Ingress: Increment DMAC and SMAC
    MESA_ACL_ADDR_UPDATE_IGR_DMAC_INCR_SMAC_REPLACE // Ingress: Increment DMAC, replace SMAC
} mesa_acl_addr_update_t CAP(ACL_SIP_CNT);

// ACL address action configuration
typedef struct {
    mesa_acl_addr_update_t update;  // Address update
    mesa_mac_t             mac;     // MAC address used for replace operations
    mesa_acl_sip_idx_t     sip_idx; // Source IP index
} mesa_acl_addr_action_t CAP(ACL_SIP_CNT);

// ACL Action
typedef struct
{
    mesa_bool_t                cpu;            // Forward to CPU
    mesa_bool_t                cpu_once;       // Only first frame forwarded to CPU
    mesa_bool_t                cpu_disable;    // Disable CPU copy from previous forwarding decisions
    mesa_packet_rx_queue_t     cpu_queue;      // CPU queue
    mesa_bool_t                police;         // Enable policer
    mesa_acl_policer_no_t      policer_no;     // Policer number
    mesa_bool_t                evc_police     CAP(ACL_EVC_POLICER); // Enable EVC policer
    mesa_evc_policer_id_t      evc_policer_id CAP(ACL_EVC_POLICER); // EVC policer ID
    mesa_bool_t                learn;          // Allow learning
    mesa_acl_port_action_t     port_action;    // Port action
    mesa_port_list_t           port_list;      // Egress port list
    mesa_bool_t                mirror;         // Enable mirroring
    mesa_acl_ptp_action_t      ptp_action;     // PTP action
    mesa_acl_ptp_action_conf_t ptp  CAP(ACL_SIP_CNT); // PTP configuration
    mesa_acl_addr_action_t     addr CAP(ACL_SIP_CNT); // Address update configuration
    mesa_bool_t                lm_cnt_disable CAP(ACL_LM_CNT_CTRL); // Disable OAM LM Tx counting
    mesa_bool_t                mac_swap CAP(ACL_MAC_SWAP); // Swap SMAC and DMAC
    mesa_bool_t                ifh_flag CAP(ACL_IFH_FLAG); // Control one target specific bit in IFH
} mesa_acl_action_t;

// ACL key generation for ARP/IPv4/IPv6 frames
typedef enum {
    MESA_ACL_KEY_DEFAULT, // Match MESA_ACE_TYPE_ARP/IPV4/IPV6 (default)
    MESA_ACL_KEY_ETYPE,   // Match MESA_ACE_TYPE_ETYPE
    MESA_ACL_KEY_EXT      // Match MESA_ACE_TYPE_IPV4/IPV6 extended rule
} mesa_acl_key_t;

// ACL key generation for ARP/IPv4/IPv6 frames
typedef struct {
    mesa_acl_key_t etype; // ETYPE/LLC/SNAP frame key
    mesa_acl_key_t arp;   // ARP frame key
    mesa_acl_key_t ipv4;  // IPv4 frame key
    mesa_acl_key_t ipv6;  // IPv6 frame key
} mesa_acl_frame_key_t;

// ACL port configuration
typedef struct
{
    mesa_acl_policy_no_t policy_no; // Policy number
    mesa_acl_action_t    action;    // Action
    mesa_acl_frame_key_t key;       // ACL key generation
} mesa_acl_port_conf_t;

// Get ACL configuration for port.
// port_no [IN]  Port number.
// conf [OUT]    Port configuration.
mesa_rc mesa_acl_port_conf_get(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               mesa_acl_port_conf_t  *const conf);

// Set ACL configuration for port.
// port_no [IN]  Port number.
// conf [IN]     Port configuration.
mesa_rc mesa_acl_port_conf_set(const mesa_inst_t           inst,
                               const mesa_port_no_t        port_no,
                               const mesa_acl_port_conf_t  *const conf);

// ACL port counter
typedef uint32_t mesa_acl_port_counter_t;

// Get default action counter for port.
// port_no [IN]   Port number.
// counter [OUT]  Default action counter for port.
mesa_rc mesa_acl_port_counter_get(const mesa_inst_t        inst,
                                  const mesa_port_no_t     port_no,
                                  mesa_acl_port_counter_t  *const counter);

// Clear default action counter for port.
// port_no [IN]  Port number.
mesa_rc mesa_acl_port_counter_clear(const mesa_inst_t     inst,
                                    const mesa_port_no_t  port_no);

// ACE frame type
typedef enum
{
    MESA_ACE_TYPE_ANY,     // Any frame type
    MESA_ACE_TYPE_ETYPE,   // Ethernet Type
    MESA_ACE_TYPE_LLC,     // LLC
    MESA_ACE_TYPE_SNAP,    // SNAP
    MESA_ACE_TYPE_ARP,     // ARP/RARP
    MESA_ACE_TYPE_IPV4,    // IPv4
    MESA_ACE_TYPE_IPV6     // IPv6
} mesa_ace_type_t;

// ACE ID type
typedef uint32_t mesa_ace_id_t;

#define MESA_ACE_ID_LAST 0 // Special value used to add last in list

// ACE 1 bit
typedef enum
{
    MESA_ACE_BIT_ANY, // Value 0 or 1
    MESA_ACE_BIT_0,   // Value 0
    MESA_ACE_BIT_1    // Value 1
} mesa_ace_bit_t;

// ACE 8 bit value and mask
typedef mesa_vcap_u8_t mesa_ace_u8_t;

// ACE 16 bit value and mask
typedef mesa_vcap_u16_t mesa_ace_u16_t;

// ACE 32 bit value and mask
typedef mesa_vcap_u32_t mesa_ace_u32_t;

// ACE 40 bit value and mask
typedef mesa_vcap_u40_t mesa_ace_u40_t;

// ACE 48 bit value and mask
typedef mesa_vcap_u48_t mesa_ace_u48_t;

// ACE 128 bit value and mask
typedef mesa_vcap_u128_t mesa_ace_u128_t;

// ACE VLAN ID value and mask
typedef mesa_vcap_vid_t mesa_ace_vid_t;

// ACE IP address value and mask
typedef mesa_vcap_ip_t mesa_ace_ip_t;

// ACE UDP/TCP port range
typedef mesa_vcap_udp_tcp_t mesa_ace_udp_tcp_t;

// PTP header filtering
typedef struct
{
    mesa_bool_t    enable; // Enable PTP header filtering
    mesa_ace_u32_t header; // PTP header byte 0, 1, 4 and 6
} mesa_ace_ptp_t;

// SIP/SMAC filtering
typedef struct
{
    mesa_bool_t enable; // Enable SIP/SMAC filtering
    mesa_ip_t   sip;    // SIP
    mesa_mac_t  smac;   // SMAC
} mesa_ace_sip_smac_t;

// ACE VLAN information
typedef struct
{
    mesa_ace_vid_t   vid;      // VLAN ID (12 bit)
    mesa_ace_u8_t    usr_prio; // User priority/PCP (3 bit)
    mesa_ace_bit_t   cfi;      // CFI/DEI
    mesa_ace_bit_t   tagged;   // Tagged/untagged frame
} mesa_ace_vlan_t;

// Frame data for MESA_ACE_TYPE_ANY
typedef struct
{
    mesa_ace_u48_t dmac; // DMAC
    mesa_ace_u48_t smac; // SMAC
} mesa_ace_frame_any_t;

// Frame data for MESA_ACE_TYPE_ETYPE
typedef struct
{
    mesa_ace_u48_t dmac;  // DMAC
    mesa_ace_u48_t smac;  // SMAC
    mesa_ace_u16_t etype; // Ethernet Type value
    mesa_ace_u16_t data;  // MAC data
    mesa_ace_ptp_t ptp;   // PTP header filtering (overrides smac byte 2,4 and data fields)
} mesa_ace_frame_etype_t;

// Frame data for MESA_ACE_TYPE_LLC
typedef struct
{
    mesa_ace_u48_t dmac; // DMAC
    mesa_ace_u48_t smac; // SMAC
    mesa_ace_u32_t llc;  // LLC header: DSAP at byte 0, SSAP at byte 1, Control at byte 2
} mesa_ace_frame_llc_t;

// Frame data for MESA_ACE_TYPE_SNAP
typedef struct
{
    mesa_ace_u48_t dmac; // DMAC
    mesa_ace_u48_t smac; // SMAC
    mesa_ace_u40_t snap; // SNAP header: Organization Code at byte 0, Type at byte 3
} mesa_ace_frame_snap_t;

// Frame data for MESA_ACE_TYPE_ARP
typedef struct
{
    mesa_ace_u48_t dmac;       // DMAC, MESA_ACL_KEY_EXT
    mesa_ace_u48_t smac;       // SMAC
    mesa_ace_bit_t arp;        // Opcode ARP/RARP
    mesa_ace_bit_t req;        // Opcode request/reply
    mesa_ace_bit_t unknown;    // Opcode unknown
    mesa_ace_bit_t smac_match; // Sender MAC matches SMAC
    mesa_ace_bit_t dmac_match; // Target MAC matches DMAC
    mesa_ace_bit_t length;     // Protocol addr. length 4, hardware length 6
    mesa_ace_bit_t ip;         // Protocol address type IP
    mesa_ace_bit_t ethernet;   // Hardware address type Ethernet
    mesa_ace_ip_t  sip;        // Sender IP address
    mesa_ace_ip_t  dip;        // Target IP address
} mesa_ace_frame_arp_t;

// Frame data for MESA_ACE_TYPE_IPV4
typedef struct
{
    mesa_ace_u48_t      dmac CAP(ACL_EXT_MAC); // DMAC, MESA_ACL_KEY_EXT
    mesa_ace_u48_t      smac CAP(ACL_EXT_MAC); // SMAC, MESA_ACL_KEY_EXT
    mesa_ace_bit_t      ttl;                   // TTL zero
    mesa_ace_bit_t      fragment;              // Fragment
    mesa_ace_bit_t      options;               // Header options
    mesa_ace_u8_t       ds;                    // DS field
    mesa_ace_u8_t       proto;                 // Protocol
    mesa_ace_ip_t       sip;                   // Source IP address
    mesa_ace_ip_t       dip;                   // Destination IP address
    mesa_ace_u48_t      data;                  // Not UDP/TCP: IP data
    mesa_ace_udp_tcp_t  sport;                 // UDP/TCP: Source port
    mesa_ace_udp_tcp_t  dport;                 // UDP/TCP: Destination port
    mesa_ace_bit_t      tcp_fin;               // TCP FIN
    mesa_ace_bit_t      tcp_syn;               // TCP SYN
    mesa_ace_bit_t      tcp_rst;               // TCP RST
    mesa_ace_bit_t      tcp_psh;               // TCP PSH
    mesa_ace_bit_t      tcp_ack;               // TCP ACK
    mesa_ace_bit_t      tcp_urg;               // TCP URG
    mesa_ace_bit_t      sip_eq_dip;            // SIP equals DIP
    mesa_ace_bit_t      sport_eq_dport;        // SPORT equals DPORT
    mesa_ace_bit_t      seq_zero;              // TCP sequence number is zero
    mesa_ace_ptp_t      ptp;                   // PTP filtering (overrides sip field)
    mesa_ace_sip_smac_t sip_smac;              // SIP/SMAC matching (overrides sip field)
} mesa_ace_frame_ipv4_t;

// Frame data for MESA_ACE_TYPE_IPV6
typedef struct
{
    mesa_ace_u48_t     dmac CAP(ACL_EXT_MAC); // DMAC, MESA_ACL_KEY_EXT
    mesa_ace_u48_t     smac CAP(ACL_EXT_MAC); // SMAC, MESA_ACL_KEY_EXT
    mesa_ace_u8_t      proto;                 // IPv6 protocol
    mesa_ace_u128_t    sip;                   // IPv6 source address (byte 0-7 only used for MESA_ACL_KEY_EXT)
    mesa_ace_u128_t    dip CAP(ACL_EXT_DIP);  // IPv6 destination address, MESA_ACL_KEY_EXT
    mesa_ace_bit_t     ttl;                   // TTL zero
    mesa_ace_u8_t      ds;                    // DS field
    mesa_ace_u48_t     data;                  // Not UDP/TCP: IP data
    mesa_ace_udp_tcp_t sport;                 // UDP/TCP: Source port
    mesa_ace_udp_tcp_t dport;                 // UDP/TCP: Destination port
    mesa_ace_bit_t     tcp_fin;               // TCP FIN
    mesa_ace_bit_t     tcp_syn;               // TCP SYN
    mesa_ace_bit_t     tcp_rst;               // TCP RST
    mesa_ace_bit_t     tcp_psh;               // TCP PSH
    mesa_ace_bit_t     tcp_ack;               // TCP ACK
    mesa_ace_bit_t     tcp_urg;               // TCP URG
    mesa_ace_bit_t     sip_eq_dip;            // SIP equals DIP
    mesa_ace_bit_t     sport_eq_dport;        // SPORT equals DPORT
    mesa_ace_bit_t     seq_zero;              // TCP sequence number is zero
    mesa_ace_ptp_t     ptp;                   // PTP filtering (overrides sip byte 0-3)
} mesa_ace_frame_ipv6_t;

// Access Control Entry
typedef struct
{
    mesa_ace_id_t        id;           // ACE ID, must be different from MESA_ACE_ID_LAST
    uint8_t              lookup       CAP(ACL_KEY_LOOKUP); // Lookup, any non-zero value means second lookup
    mesa_bool_t          isdx_enable  CAP(ACL_KEY_ISDX);   // Use VID value for ISDX value
    mesa_bool_t          isdx_disable CAP(ACL_KEY_ISDX);   // Match only frames with ISDX zero
    mesa_port_list_t     port_list;    // Port list
    mesa_ace_u8_t        policy;       // Policy number
    mesa_ace_type_t      type;         // ACE frame type
    mesa_bool_t          type_ext;     // Use extended type for IPv4/IPv6
    mesa_acl_action_t    action;       // ACE action

    mesa_ace_bit_t       dmac_mc;      // Multicast DMAC
    mesa_ace_bit_t       dmac_bc;      // Broadcast DMAC

    mesa_ace_vlan_t      vlan;         // VLAN Tag

    union
    {
        mesa_ace_frame_any_t   any;    // MESA_ACE_TYPE_ANY
        mesa_ace_frame_etype_t etype;  // MESA_ACE_TYPE_ETYPE
        mesa_ace_frame_llc_t   llc;    // MESA_ACE_TYPE_LLC
        mesa_ace_frame_snap_t  snap;   // MESA_ACE_TYPE_SNAP
        mesa_ace_frame_arp_t   arp;    // MESA_ACE_TYPE_ARP
        mesa_ace_frame_ipv4_t  ipv4;   // MESA_ACE_TYPE_IPV4
        mesa_ace_frame_ipv6_t  ipv6;   // MESA_ACE_TYPE_IPV6
    } frame; // Frame type specific data
} mesa_ace_t;

// Initialize ACE to default values.
// type [IN]  ACE type.
// ace [OUT]  ACE structure.
mesa_rc mesa_ace_init(const mesa_inst_t      inst,
                      const mesa_ace_type_t  type,
                      mesa_ace_t             *const ace);

// Add/modify ACE.
// ace_id_next [IN]  ACE ID of next entry.
//                   The ACE will be added before the entry with this ID.
//                   MESA_ACE_ID_LAST is reserved for inserting last.
// ace [IN]          ACE structure.
mesa_rc mesa_ace_add(const mesa_inst_t    inst,
                     const mesa_ace_id_t  ace_id_next,
                     const mesa_ace_t     *const ace);

// Delete ACE.
// ace_id [IN]  ACE ID.
mesa_rc mesa_ace_del(const mesa_inst_t    inst,
                     const mesa_ace_id_t  ace_id);

// ACE hit counter
typedef uint32_t mesa_ace_counter_t;

// Get ACE counter.
// ace_id [IN]    ACE ID.
// counter [OUT]  ACE counter.
mesa_rc mesa_ace_counter_get(const mesa_inst_t    inst,
                             const mesa_ace_id_t  ace_id,
                             mesa_ace_counter_t   *const counter);

// Clear ACE counter.
// ace_id [IN]  ACE ID.
mesa_rc mesa_ace_counter_clear(const mesa_inst_t    inst,
                               const mesa_ace_id_t  ace_id);

#define MESA_ACE_IDX_NONE 0xffff // ACE index not valid

// ACE status
typedef struct {
    uint16_t idx[2]; // ACE hardware index table
} mesa_ace_status_t CAP(ACL_ACE_STATUS);

// Get ACE status.
// ace_id [IN]   ACE ID.
// status [OUT]  ACE status.
mesa_rc mesa_ace_status_get(const mesa_inst_t    inst,
                            const mesa_ace_id_t  ace_id,
                            mesa_ace_status_t    *const status)
    CAP(ACL_ACE_STATUS);

// Hierarchical ACL type
typedef enum {
    MESA_HACL_TYPE_IPACL,   // Ingress port ACL (I-PACL)
    MESA_HACL_TYPE_IVACL,   // Ingress VLAN ACL (I-VACL)
    MESA_HACL_TYPE_IRACL,   // Ingress router ACL (I-RACL)
    MESA_HACL_TYPE_ERACL,   // Egress router ACL (E-RACL)
    MESA_HACL_TYPE_EVACL,   // Egress VLAN ACL (E-VACL)
    MESA_HACL_TYPE_EPACL,   // Egress port ACL (E-PACL)
} mesa_hacl_type_t CAP(ACL_HACL);

#define MESA_RLEG_LIST_ARRAY_SIZE 64 // Router leg list

// Router leg list
typedef struct {
    uint8_t _private[MESA_RLEG_LIST_ARRAY_SIZE]; // Router leg list, access using utilities below
} mesa_rleg_list_t;

// Set router leg in router leg list.
// l     [IN]  Router leg list.
// rleg  [IN]  Router leg ID.
// val   [IN]  Value.
void mesa_rleg_list_set(mesa_rleg_list_t *l, mesa_l3_rleg_id_t rleg, mesa_bool_t val);

// Get router leg value from router leg list.
// l     [IN]  Router leg list.
// rleg  [IN]  Router leg ID.
mesa_bool_t mesa_rleg_list_get(const mesa_rleg_list_t *l, mesa_l3_rleg_id_t rleg);

// Frame data for MESA_ACE_TYPE_ETYPE
typedef struct {
    mesa_ace_u16_t etype; // Ethernet Type value
    mesa_ace_u16_t data;  // MAC data
} mesa_hace_frame_etype_t CAP(ACL_HACL);

// Frame data for MESA_ACE_TYPE_LLC
typedef struct {
    mesa_ace_u32_t llc;  // LLC header: DSAP at byte 0, SSAP at byte 1, Control at byte 2
} mesa_hace_frame_llc_t CAP(ACL_HACL);

// Frame data for MESA_ACE_TYPE_SNAP
typedef struct {
    mesa_ace_u40_t snap; // SNAP header: Organization Code at byte 0, Type at byte 3
} mesa_hace_frame_snap_t CAP(ACL_HACL);

// Frame data for MESA_ACE_TYPE_ARP
typedef struct {
    mesa_ace_bit_t arp;        // Opcode ARP/RARP
    mesa_ace_bit_t req;        // Opcode request/reply
    mesa_ace_bit_t unknown;    // Opcode unknown
    mesa_ace_bit_t smac_match; // Sender MAC matches SMAC
    mesa_ace_bit_t dmac_match; // Target MAC matches DMAC
    mesa_ace_bit_t length;     // Protocol addr. length 4, hardware length 6
    mesa_ace_bit_t ip;         // Protocol address type IP
    mesa_ace_bit_t ethernet;   // Hardware address type Ethernet
    mesa_ace_ip_t  sip;        // Sender IP address
    mesa_ace_ip_t  dip;        // Target IP address
} mesa_hace_frame_arp_t CAP(ACL_HACL);

// Frame data for MESA_ACE_TYPE_IPV4
typedef struct
{
    mesa_ace_bit_t      ttl;      // TTL zero
    mesa_ace_bit_t      fragment; // Fragment
    mesa_ace_bit_t      options;  // Header options
    mesa_ace_u8_t       ds;       // DS field
    mesa_ace_u8_t       proto;    // Protocol
    mesa_ace_ip_t       sip;      // Source IP address
    mesa_ace_ip_t       dip;      // Destination IP address
    mesa_ace_u48_t      data;     // Not UDP/TCP: IP data
    mesa_ace_udp_tcp_t  sport;    // UDP/TCP: Source port
    mesa_ace_udp_tcp_t  dport;    // UDP/TCP: Destination port
    mesa_ace_bit_t      tcp_fin;  // TCP FIN
    mesa_ace_bit_t      tcp_syn;  // TCP SYN
    mesa_ace_bit_t      tcp_rst;  // TCP RST
    mesa_ace_bit_t      tcp_psh;  // TCP PSH
    mesa_ace_bit_t      tcp_ack;  // TCP ACK
    mesa_ace_bit_t      tcp_urg;  // TCP URG
    mesa_ace_sip_smac_t sip_smac; // SIP/SMAC matching (overrides sip field)
} mesa_hace_frame_ipv4_t CAP(ACL_HACL);

// Frame data for MESA_ACE_TYPE_IPV6
typedef struct
{
    mesa_ace_bit_t     ttl;     // TTL zero
    mesa_ace_u8_t      ds;      // DS field
    mesa_ace_u8_t      proto;   // IPv6 protocol
    mesa_ace_u128_t    sip;     // IPv6 source address
    mesa_ace_u128_t    dip;     // IPv6 destination address
    mesa_ace_u48_t     data;    // Not UDP/TCP: IP data
    mesa_ace_udp_tcp_t sport;   // UDP/TCP: Source port
    mesa_ace_udp_tcp_t dport;   // UDP/TCP: Destination port
    mesa_ace_bit_t     tcp_fin; // TCP FIN
    mesa_ace_bit_t     tcp_syn; // TCP SYN
    mesa_ace_bit_t     tcp_rst; // TCP RST
    mesa_ace_bit_t     tcp_psh; // TCP PSH
    mesa_ace_bit_t     tcp_ack; // TCP ACK
    mesa_ace_bit_t     tcp_urg; // TCP URG
} mesa_hace_frame_ipv6_t CAP(ACL_HACL);

// Hierarchical ACL key
typedef struct {
    mesa_port_list_t        port_list; // Ingress/egress port list (unused for RACLs)
    mesa_rleg_list_t        rleg_list; // Ingress/egress router leg list (RACLs only)
    mesa_ace_u8_t           policy;    // Policy number
    mesa_ace_type_t         type;      // ACE frame type
    mesa_bool_t             type_ext;  // Use extended type for IPv4/IPv6 (I-PACL)
    mesa_ace_vlan_t         vlan;      // Classified VLAN tag values (unused for RACLs)
    mesa_ace_ptp_t          ptp;       // PTP header filtering for EType/IPv4/IPv6 (unused for RACLs)
    mesa_ace_bit_t          dmac_mc;   // Multicast DMAC (unused for RACLs)
    mesa_ace_bit_t          dmac_bc;   // Broadcast DMAC (unused for RACLs)
    mesa_ace_u48_t          dmac;      // DMAC (unused for RACLs)
    mesa_ace_u48_t          smac;      // SMAC (unused for RACLs)
    mesa_hace_frame_etype_t etype;     // MESA_ACE_TYPE_ETYPE (unused for RACLs)
    mesa_hace_frame_llc_t   llc;       // MESA_ACE_TYPE_LLC (unused for RACLs)
    mesa_hace_frame_snap_t  snap;      // MESA_ACE_TYPE_SNAP (unused for RACLs)
    mesa_hace_frame_arp_t   arp;       // MESA_ACE_TYPE_ARP (unused for VACLS/RACLs)
    mesa_hace_frame_ipv4_t  ipv4;      // MESA_ACE_TYPE_IPV4 (unused for VACLs)
    mesa_hace_frame_ipv6_t  ipv6;      // MESA_ACE_TYPE_IPV6 (unused for VACLs)
} mesa_hace_key_t CAP(ACL_HACL);

// Hierarchical ACL action
typedef struct {
    mesa_acl_port_action_t     port_action; // Port action
    mesa_port_list_t           port_list;   // Egress port list (I-PACL/I-VACL only)
    mesa_bool_t                cpu;         // Forward to CPU (I-PACL/I-VACL only)
    mesa_bool_t                cpu_once;    // Only first frame forwarded to CPU (I-PACL/I-VACL only)
    mesa_bool_t                cpu_disable; // Disable CPU copy from previous forwarding decisions (I-PACL/I-VACL only)
    mesa_packet_rx_queue_t     cpu_queue;   // CPU queue (I-PACL/I-VACL only)
    mesa_bool_t                police;      // Enable policer (I-PACL/I-VACL only)
    mesa_acl_policer_no_t      policer_no;  // Policer number (I-PACL/I-VACL only)
    mesa_bool_t                mirror;      // Enable mirroring (I-PACL/I-VACL only)
    mesa_acl_ptp_action_t      ptp_action;  // PTP action (I-PACL/I-VACL only)
    mesa_acl_ptp_action_conf_t ptp;         // PTP configuration (I-PACL/I-VACL only)
    mesa_acl_addr_action_t     addr;        // Address update configuration (I-PACL/I-VACL only)
    mesa_bool_t                ifh_flag;    // Control one target specific bit in IFH (I-PACL/I-VACL only)
} mesa_hacl_action_t CAP(ACL_HACL);

// Hierarchical ACL Entry
typedef struct {
    mesa_ace_id_t      id;     // Entry ID
    mesa_hace_key_t    key;    // ACE key
    mesa_hacl_action_t action; // ACE action
} mesa_hace_t CAP(ACL_HACL);

// Initialize Hierarchical ACE to default values.
// type [IN]   ACE type.
// hace [OUT]  ACE structure.
mesa_rc mesa_hace_init(const mesa_inst_t     inst,
                       const mesa_ace_type_t type,
                       mesa_hace_t           *const hace)
    CAP(ACL_HACL);

// Add/modify Hierarchical ACE.
// type [IN]         Hierarcical ACL type.
// ace_id_next [IN]  ACE ID of next entry.
//                   The ACE will be added before the entry with this ID.
//                   MESA_ACE_ID_LAST is reserved for inserting last.
// hace [IN]         ACE structure.
mesa_rc mesa_hace_add(const mesa_inst_t      inst,
                      const mesa_hacl_type_t type,
                      const mesa_ace_id_t    ace_id_next,
                      const mesa_hace_t      *const hace)
    CAP(ACL_HACL);

// Delete Hierarchical ACE.
// type [IN]    Hierarcical ACL type.
// ace_id [IN]  ACE ID.
mesa_rc mesa_hace_del(const mesa_inst_t      inst,
                      const mesa_hacl_type_t type,
                      const mesa_ace_id_t    ace_id)
    CAP(ACL_HACL);

// Get Hierarchical ACE counter.
// type [IN]      Hierarcical ACL type.
// ace_id [IN]    ACE ID.
// counter [OUT]  ACE counter.
mesa_rc mesa_hace_counter_get(const mesa_inst_t      inst,
                              const mesa_hacl_type_t type,
                              const mesa_ace_id_t    ace_id,
                              mesa_ace_counter_t     *const counter)
    CAP(ACL_HACL);

// Clear Hierarchical ACE counter.
// type [IN]    Hierarcical ACL type.
// ace_id [IN]  ACE ID.
mesa_rc mesa_hace_counter_clear(const mesa_inst_t      inst,
                                const mesa_hacl_type_t type,
                                const mesa_ace_id_t    ace_id)
    CAP(ACL_HACL);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_SECURITY_
