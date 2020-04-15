/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef _MSCC_ETHERNET_SWITCH_API_TYPES_
#define _MSCC_ETHERNET_SWITCH_API_TYPES_

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/****************************************************************************
 * Basic types (used in includes)
 ****************************************************************************/

typedef uint8_t mesa_bool_t;

/****************************************************************************
 * Included types
 ****************************************************************************/

#include <mscc/ethernet/switch/api/capability.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/****************************************************************************
 * Common types
 ****************************************************************************/

// Chip number used for targets with multiple chips
typedef uint32_t mesa_chip_no_t;

// Error code type
typedef int mesa_rc;

// Error codes
enum
{
    MESA_RC_OK                                  =  0,  // Success
    MESA_RC_ERROR                               = -1,  // Unspecified error
    MESA_RC_INV_STATE                           = -2,  // Invalid state for operation
    MESA_RC_INCOMPLETE                          = -3,  // Incomplete result
    MESA_RC_NOT_IMPLEMENTED                     = -4,  // Not implemented
    MESA_RC_ERR_PARM                            = -5,  // Invalid parameter
    MESA_RC_ERR_NO_RES                          = -6,  // Out of resources

    MESA_RC_ERR_KR_CONF_NOT_SUPPORTED           = -7,  // The PHY doesn't support 10GBASE_KR equalization
    MESA_RC_ERR_KR_CONF_INVALID_PARAMETER       = -8,  // One of the parameters are out of range

    // 1G ERRORS ****/
    MESA_RC_ERR_PHY_BASE_NO_NOT_FOUND           = -50,  // Port base number (first port within a chip) is not found
    MESA_RC_ERR_PHY_6G_MACRO_SETUP              = -51,  // Setup of 6G macro failed
    MESA_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED      = -52,  // PHY does not support the selected media mode
    MESA_RC_ERR_PHY_CLK_CONF_NOT_SUPPORTED      = -53,  // The PHY doesn't support clock configuration (for SynceE)
    MESA_RC_ERR_PHY_GPIO_ALT_MODE_NOT_SUPPORTED = -54,  // The PHY doesn't support the alternative mode for the selected GPIO pin
    MESA_RC_ERR_PHY_GPIO_PIN_NOT_SUPPORTED      = -55,  // The PHY doesn't support the selected GPIO pin
    MESA_RC_ERR_PHY_PORT_OUT_RANGE              = -56,  // PHY API called with port number larger than MESA_PORTS
    MESA_RC_ERR_PHY_PATCH_SETTING_NOT_SUPPORTED = -57,  // PHY API micro patch setting not supported for the port in question
    MESA_RC_ERR_PHY_LCPLL_NOT_SUPPORTED         = -58,  // PHY API LC-PLL status not supported for the port
    MESA_RC_ERR_PHY_RCPLL_NOT_SUPPORTED         = -59,  // PHY API RC-PLL status not supported for the port

    // MACSEC ERRORS
    MESA_RC_ERR_MACSEC_INVALID_SCI_MACADDR      = -60,  // From IEEE 802.1AE-2006, section 9.9 - The 64-bit value FF-FF-FF-FF-FF-FF is never used as an SCI and is reserved for use by implementations to indicate the absence of an SC or an SCI in contexts where an SC can be present
    MESA_RC_ERR_MACSEC_NOT_ENABLED              = -61,  // Trying to access port where MACSEC is not enabled
    MESA_RC_ERR_MACSEC_SECY_ALREADY_IN_USE      = -63,  // Trying to use a secy which is already in use
    MESA_RC_ERR_MACSEC_NO_SECY_FOUND            = -64,  // No SecY found for the specific port
    MESA_RC_ERR_MACSEC_NO_SECY_VACANCY          = -65,  // No secy vacancy
    MESA_RC_ERR_MACSEC_INVALID_VALIDATE_FRM     = -66,  // Validate_frames value invalid
    MESA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH   = -67,  // Could not program the SA match
    MESA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW    = -68,  // Could not program the SA flow
    MESA_RC_ERR_MACSEC_COULD_NOT_ENA_SA         = -69,  // Could not enable the SA
    MESA_RC_ERR_MACSEC_COULD_NOT_SET_SA         = -70,  // Could not set SA to in use
    MESA_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN   = -71,  // Invalid header bypass length
    MESA_RC_ERR_MACSEC_SC_NOT_FOUND             = -72,  // Could not find SC (from sci)
    MESA_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH        = -73,  // No control frame match
    MESA_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN    = -74,  // Could no set bypass pattern for CP rule
    MESA_RC_ERR_MACSEC_TIMEOUT_ISSUE            = -75,  // Internal timeout issue, bailing out
    MESA_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS   = -76,  // Could not empty the egress pipeline
    MESA_RC_ERR_MACSEC_AN_NOT_CREATED           = -77,  // AN not created.
    MESA_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS  = -78,  // Could not empty the ingress pipeline
    MESA_RC_ERR_MACSEC_TX_SC_NOT_EXIST          = -80,  // No tx SC found
    MESA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA     = -81,  // Could not disable sa
    MESA_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA      = -82,  // Could not delete rx sa
    MESA_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA      = -83,  // Could not delete tx sa
    MESA_RC_ERR_MACSEC_PATTERN_NOT_SET          = -84,  // Pattern not set
    MESA_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED     = -85,  // HW resources exhausted
    MESA_RC_ERR_MACSEC_SCI_ALREADY_EXISTS       = -86,  // SCI already exists
    MESA_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND    = -87,  // Could not find SC resources
    MESA_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE     = -88,  // Rx AN is in use
    MESA_RC_ERR_MACSEC_EMPTY_RECORD             = -89,  // Could not get an empty record
    MESA_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM      = -90,  // Could not program the xform record
    MESA_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA      = -91,  // Could not toggle SA
    MESA_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE     = -92,  // Tx AN is in use
    MESA_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE  = -93,  // All available SA's are in use
    MESA_RC_ERR_MACSEC_MATCH_DISABLE            = -94,  // MACSEC match disabled
    MESA_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE      = -95,  // All CP rules of the specific type are in use
    MESA_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID   = -96,  // The pattern priority is not valid
    MESA_RC_ERR_MACSEC_BUFFER_TOO_SMALL         = -97,  // Buffer to small, must be greater than MESA_MACSEC_FRAME_CAPTURE_SIZE_MAX
    MESA_RC_ERR_MACSEC_FRAME_TOO_LONG           = -98,  // Frame length is supposed to be less than the amount of data in the fifo
    MESA_RC_ERR_MACSEC_FRAME_TRUNCATED          = -99,  // Frame is Truncated
    MESA_RC_ERR_MACSEC_PHY_POWERED_DOWN         = -100, // Phy is powered down, i.e. the MacSec block is not accessible
    MESA_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE   = -101, // Port/Phy is not MacSec capable
    MESA_RC_ERR_MACSEC_AN_NOT_EXIST             = -102, // AN does not exist
    MESA_RC_ERR_MACSEC_NO_PATTERN_CFG           = -103, // No pattern is configured
    MESA_RC_ERR_MACSEC_MAX_MTU                  = -105, // Maximum MTU allowed is 32761 (+ 4 bytes for VLAN)
    MESA_RC_ERR_MACSEC_UNEXPECT_CP_MODE         = -106, // Unexpected CP mode
    MESA_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN     = -107, // Could not disable AN
    MESA_RC_ERR_MACSEC_RULE_OUT_OF_RANGE        = -108, // Rule id is out of range. Must not be larger than MESA_MACSEC_CP_RULES
    MESA_RC_ERR_MACSEC_RULE_NOT_EXIST           = -109, // Rule does not exist
    MESA_RC_ERR_MACSEC_CSR_READ                 = -110, // Could not do CSR read
    MESA_RC_ERR_MACSEC_CSR_WRITE                = -111, // Could not do CSR write
    MESA_RC_ERR_PHY_6G_RCPLL_ON_BASE_PORT_ONLY  = -112, // PHY API 6G RC-PLL status support only on Base port

    // MISC ERRORS
    MESA_RC_ERR_INVALID_NULL_PTR                = -200, // A pointer was unexpected NULL

    // Clause 37 ERRORS
    MESA_RC_ERR_PCS_BLOCK_NOT_SUPPORTED         = -300, // Invalid access to PCS block

    // PoE ERRORS
    MESA_RC_ERR_POE_FIRMWARE_VER_NOT_NEW        = -400 // The version of loaded firmware is identical to new

}; // Leave it anonymous.

// Event type.
// When a variable of this type is used as an input parameter, the API will set the variable if the event has occured.
// The API will never clear the variable. If is up to the application to clear the variable, when the event has been handled.
typedef uint8_t mesa_event_t;

// Policer packet rate in PPS
typedef uint32_t mesa_packet_rate_t;

#define MESA_PACKET_RATE_DISABLED 0xffffffff // Special value for disabling packet policer

#define MESA_PORT_NO_NONE    (0xffffffff) // Port number none
#define MESA_PORT_NO_CPU     (0xfffffffe) // Port number for CPU for special purposes
// Port Number
typedef uint32_t mesa_port_no_t;

// Physical port number
typedef uint32_t mesa_phys_port_no_t;

// The different interfaces for connecting MAC and PHY
typedef enum
{
    MESA_PORT_INTERFACE_NO_CONNECTION, // No connection
    MESA_PORT_INTERFACE_LOOPBACK,      // Internal loopback in MAC
    MESA_PORT_INTERFACE_INTERNAL,      // Internal interface
    MESA_PORT_INTERFACE_MII,           // MII (RMII does not exist)
    MESA_PORT_INTERFACE_GMII,          // GMII
    MESA_PORT_INTERFACE_RGMII,         // RGMII
    MESA_PORT_INTERFACE_TBI,           // TBI
    MESA_PORT_INTERFACE_RTBI,          // RTBI
    MESA_PORT_INTERFACE_SGMII,         // SGMII
    MESA_PORT_INTERFACE_SGMII_2G5,     // SGMII 2G5
    MESA_PORT_INTERFACE_SGMII_CISCO,   // SGMII using Cisco aneg
    MESA_PORT_INTERFACE_SERDES,        // SERDES
    MESA_PORT_INTERFACE_VAUI,          // VAUI
    MESA_PORT_INTERFACE_100FX,         // 100FX
    MESA_PORT_INTERFACE_XAUI,          // XAUI
    MESA_PORT_INTERFACE_RXAUI,         // RXAUI
    MESA_PORT_INTERFACE_XGMII,         // XGMII
    MESA_PORT_INTERFACE_SPI4,          // SPI4
    MESA_PORT_INTERFACE_QSGMII,        // QSGMII
    MESA_PORT_INTERFACE_SFI,           // SFI/LAN
} mesa_port_interface_t;

// Auto negotiation struct
typedef struct
{
    mesa_bool_t obey_pause;      // This port should obey PAUSE frames
    mesa_bool_t generate_pause;  // Link partner obeys PAUSE frames
} mesa_aneg_t;                   // Auto negotiation result

// Serdes macro mode
typedef enum
{
    MESA_SERDES_MODE_DISABLE,   // Disable serdes
    MESA_SERDES_MODE_XAUI_12G,  // XAUI 12G mode
    MESA_SERDES_MODE_XAUI,      // XAUI 10G mode
    MESA_SERDES_MODE_RXAUI,     // RXAUI 10G mode
    MESA_SERDES_MODE_RXAUI_12G, // RXAUI 12G mode
    MESA_SERDES_MODE_2G5,       // 2.5G mode
    MESA_SERDES_MODE_QSGMII,    // QSGMII mode
    MESA_SERDES_MODE_SGMII,     // SGMII mode
    MESA_SERDES_MODE_100FX,     // 100FX mode
    MESA_SERDES_MODE_1000BaseX, // 1000BaseX mode
    MESA_SERDES_MODE_SFI,       // LAN/10G mode
    MESA_SERDES_MODE_SFI_DAC,   // LAN/10G DAC(CU)
    MESA_SERDES_MODE_SFI_SR,    // Short Range
    MESA_SERDES_MODE_SFI_ZR,    // ZR with APC hardware algorithm
    MESA_SERDES_MODE_SFI_BP,    // Backplane
    MESA_SERDES_MODE_SFI_B2B,   // Bord to Board
    MESA_SERDES_MODE_SFI_PR_NONE, // No preset
    MESA_SERDES_MODE_IDLE,      // Send idles (port appears as down for LP)
    MESA_SERDES_MODE_TEST_MODE  // Send fixed test pattern (port appears as up for LP, but no frame rx/tx)
} mesa_serdes_mode_t;

// VOE index
typedef uint32_t mesa_voe_idx_t;

#define MESA_VOE_IDX_NONE 0xFFFFFFFF // Special value meaning no VOE

// VOI (MIP) index
typedef uint32_t mesa_voi_idx_t;

#define MESA_VOI_IDX_NONE 0xFFFFFFFF // Special value meaning no VOI (MIP)

/****************************************************************************
 * QoS types
 ****************************************************************************/

// Priority number
typedef uint32_t mesa_prio_t;
#define MESA_PRIO_CNT        8
#define MESA_PRIO_ARRAY_SIZE MESA_PRIO_CNT

// Queue number
typedef uint32_t mesa_queue_t;
#define MESA_QUEUE_CNT        8
#define MESA_QUEUE_ARRAY_SIZE MESA_QUEUE_CNT

// Tag Priority or Priority Code Point (PCP)
typedef uint32_t mesa_tagprio_t;

// Priority Code Point (PCP)
typedef uint8_t mesa_pcp_t;
#define MESA_PCP_CNT        8
#define MESA_PCP_ARRAY_SIZE MESA_PCP_CNT

// Drop Eligible Indicator (DEI)
typedef mesa_bool_t mesa_dei_t;
#define MESA_DEI_CNT        2
#define MESA_DEI_ARRAY_SIZE MESA_DEI_CNT

#define MESA_DSCP_CNT       64

// Drop Precedence Level (DPL)
typedef uint8_t mesa_dp_level_t;

// Drop Precedence Level (DPL)
typedef mesa_dp_level_t mesa_dpl_t;

// Class of Service. Same as QoS class
typedef uint8_t mesa_cos_t;

// Percentage, 0-100
typedef uint8_t mesa_pct_t;

// Policer/Shaper bit rate in kbps (1000 bits per second).
// The rate will be rounded to the nearest value supported by the chip
typedef uint32_t mesa_bitrate_t;
#define MESA_BITRATE_DISABLED 0xffffffff // Bitrate disabled

// Policer/shaper burst level in bytes.
// The level will be rounded to the nearest value supported by the chip
typedef uint32_t mesa_burst_level_t;

// Storm policer mode configuration
typedef enum
{
    MESA_STORM_POLICER_MODE_PORTS_AND_CPU, // Police both CPU and front port destinations
    MESA_STORM_POLICER_MODE_PORTS_ONLY,    // Police front port destinations only
    MESA_STORM_POLICER_MODE_CPU_ONLY       // Police CPU destination only
} mesa_storm_policer_mode_t;

// DSCP value (0-63)
typedef uint8_t mesa_dscp_t;

// QoS Control Entry ID
typedef uint32_t mesa_qce_id_t;

// Dual leaky buckets policer configuration
typedef enum
{
    MESA_POLICER_TYPE_MEF,    // MEF bandwidth profile
    MESA_POLICER_TYPE_SINGLE  // Single bucket policer (CIR/CBS)
} mesa_policer_type_t;

// EVC policer index
typedef uint16_t mesa_evc_policer_id_t;

// WRED group number
typedef uint32_t mesa_wred_group_t;

#define MESA_QOS_MAP_ID_NONE  0xfff // ID for unallocated/unused ingress or egress map

// Ingress map ID
typedef uint16_t mesa_qos_ingress_map_id_t;

// Egress map ID
typedef uint16_t mesa_qos_egress_map_id_t;

// Enable and boolean value
typedef struct {
    mesa_bool_t enable; // Enable/disable value
    mesa_bool_t value;  // Value
} mesa_opt_bool_t;

// Enable and priority value
typedef struct {
    mesa_bool_t enable; // Enable/disable value
    mesa_prio_t value;  // Value
} mesa_opt_prio_t;

/****************************************************************************
 * VLAN types
 ****************************************************************************/

// VLAN Identifier
typedef uint16_t mesa_vid_t; // 0-4095

#define MESA_VID_NULL     ((const mesa_vid_t)0)     // NULL VLAN ID
#define MESA_VID_DEFAULT  ((const mesa_vid_t)1)     // Default VLAN ID
#define MESA_VID_RESERVED ((const mesa_vid_t)0xFFF) // Reserved VLAN ID
#define MESA_VIDS         ((const mesa_vid_t)4096)  // Number of VLAN IDs
#define MESA_VID_ALL      ((const mesa_vid_t)0x1000)// Untagged VID: All VLAN IDs

// VLAN acceptable frame type
typedef enum
{
    MESA_VLAN_FRAME_ALL,      // Accept all frames
    MESA_VLAN_FRAME_TAGGED,   // Accept tagged frames only
    MESA_VLAN_FRAME_UNTAGGED  // Accept untagged frames only
} mesa_vlan_frame_t;

// Ethernet Type
typedef uint16_t mesa_etype_t;

// VLAN tag with "arbitrary" TPID.
typedef struct {
    mesa_etype_t   tpid; // Tag Protocol Identifier
    mesa_tagprio_t pcp;  // Priority Code Point
    mesa_bool_t    dei;  // Drop Eligible Indicator
    mesa_vid_t     vid;  // VLAN Identifier
} mesa_vlan_tag_t;

#define MESA_ETYPE_VTSS 0x8880 // Vitesse Ethernet Type

// MAC Address
typedef struct
{
    uint8_t addr[6];   // Network byte order
} mesa_mac_t;

// Number of bytes for representing MAC address (SMAC/DMAC) type
#define MESA_MAC_ADDR_SZ_BYTES 6

// MAC address (SMAC/DMAC)
typedef uint8_t mesa_mac_addr_t[MESA_MAC_ADDR_SZ_BYTES];

// MAC Address in specific VLAN
typedef struct
{
    mesa_vid_t vid; // VLAN ID
    mesa_mac_t mac; // MAC address
} mesa_vid_mac_t;

// Broadcast address used for addr in the mesa_mac_t struct
#define MAC_ADDR_BROADCAST {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}

typedef uint32_t mesa_isdx_t; // Ingress Service Index type
#define MESA_ISDX_NONE (0)    // Ingress Service Index number none
#define MESA_VSI_NONE  (0)    // Virtual Switching Instance number none

// Ingress flow ID
typedef uint16_t mesa_iflow_id_t;

#define MESA_IFLOW_ID_NONE 0 // No flow ID allocated

// Aggregation Number.
typedef uint32_t mesa_aggr_no_t;

// GLAG number
typedef uint32_t mesa_glag_no_t;

/****************************************************************************
 * CPU queue types
 ****************************************************************************/
// CPU Rx queue number
typedef uint32_t mesa_packet_rx_queue_t;

// CPU Rx group number
// This is a value in range [0; MESA_PACKET_RX_GRP_CNT[.
typedef uint32_t mesa_packet_rx_grp_t;

// CPU Tx group number
// This is a value in range [0; MESA_PACKET_TX_GRP_CNT[.
typedef uint32_t mesa_packet_tx_grp_t;

// COSID number
typedef uint8_t mesa_cosid_t;
#define MESA_COSID_CNT 8 // Number of COSIDs

// Packet registration type
typedef enum {
    MESA_PACKET_REG_NORMAL,   // Global registration configuration is used
    MESA_PACKET_REG_FORWARD,  // Forward normally
    MESA_PACKET_REG_DISCARD,  // Discard
    MESA_PACKET_REG_CPU_COPY, // Copy to CPU
    MESA_PACKET_REG_CPU_ONLY  // Redirect to CPU
} mesa_packet_reg_type_t;

// Registration per port and L2CP
typedef struct {
    mesa_bool_t  cosid_enable; // Enable COSID
    mesa_cosid_t cosid;        // COSID
} mesa_packet_rx_port_l2cp_conf_t CAP(PACKET_PORT_L2CP_REG);

// Packet registration per port
typedef struct {
    // IP MC Control, NORMAL/FORWARD/CPU_COPY supported
    mesa_packet_reg_type_t          ipmc_ctrl_reg CAP(PACKET_PORT_IPMC);

    // IGMP, NORMAL/FORWARD/CPU_ONLY supported
    mesa_packet_reg_type_t          igmp_reg CAP(PACKET_PORT_IPMC);

    // MLD, NORMAL/FORWARD/CPU_ONLY supported
    mesa_packet_reg_type_t          mld_reg CAP(PACKET_PORT_IPMC);

    // BPDU range: 01-80-C2-00-00-0X
    mesa_packet_reg_type_t          bpdu_reg[16];

    // GARP range: 01-80-C2-00-00-2X
    mesa_packet_reg_type_t          garp_reg[16];

    // BPDU range: 01-80-C2-00-00-0X
    mesa_packet_rx_port_l2cp_conf_t bpdu[16] CAP(PACKET_PORT_L2CP_REG);

    // GARP range: 01-80-C2-00-00-2X
    mesa_packet_rx_port_l2cp_conf_t garp[16] CAP(PACKET_PORT_L2CP_REG);
} mesa_packet_rx_port_conf_t;

// VDD power supply
typedef enum {
    MESA_VDD_1V0, // 1.0V (default)
    MESA_VDD_1V2, // 1.2V
} mesa_vdd_t;

/****************************************************************************
 * L3 types
 ****************************************************************************/
// UDP/TCP port number
typedef uint16_t mesa_udp_tcp_t;

// IPv4 address/mask
typedef uint32_t mesa_ip_t;

// IPv4 address/mask
typedef mesa_ip_t mesa_ipv4_t;

// Prefix size
typedef uint32_t mesa_prefix_size_t;

// IPv6 address/mask
typedef struct
{
    uint8_t addr[16]; // Address
} mesa_ipv6_t;

// Router leg ID
typedef uint32_t mesa_l3_rleg_id_t;

// IP address type
// This type may be used directly in SNMP InetAddressType types.
typedef enum {
    MESA_IP_TYPE_NONE = 0, // Matches "InetAddressType_unknown"
    MESA_IP_TYPE_IPV4 = 1, // Matches "InetAddressType_ipv4"
    MESA_IP_TYPE_IPV6 = 2, // Matches "InetAddressType_ipv6"
} mesa_ip_type_t;

// Either an IPv4 or IPv6 address
typedef struct {
    mesa_ip_type_t  type; // Union type
    union {
        mesa_ipv4_t ipv4; // IPv4 address
        mesa_ipv6_t ipv6; // IPv6 address
    } addr;               // IP address
} mesa_ip_addr_t;

// IPv4 network
typedef struct
{
    mesa_ipv4_t        address;     // Network address
    mesa_prefix_size_t prefix_size; // Prefix size
} mesa_ipv4_network_t;

// IPv6 network
typedef struct
{
    mesa_ipv6_t        address;     // Network address
    mesa_prefix_size_t prefix_size; // Prefix size
} mesa_ipv6_network_t;

// IPv6 network
typedef struct
{
    mesa_ip_addr_t     address;     // Network address
    mesa_prefix_size_t prefix_size; // Prefix size
} mesa_ip_network_t;

// Routing entry type
typedef enum
{
    MESA_ROUTING_ENTRY_TYPE_INVALID = 0,
    MESA_ROUTING_ENTRY_TYPE_IPV6_UC = 1,
    MESA_ROUTING_ENTRY_TYPE_IPV4_MC = 2, // obsolete
    MESA_ROUTING_ENTRY_TYPE_IPV4_UC = 3,
} mesa_routing_entry_type_t;

// IPv4 unicast routing entry
typedef struct
{
    // Network to route
    mesa_ipv4_network_t network;

    // IP address of next-hop router (zero if local route)
    mesa_ipv4_t         destination;
} mesa_ipv4_uc_t;

// IPv6 routing entry
typedef struct
{
    // Network to route
    mesa_ipv6_network_t network;

    // IP address of next-hop router (zero if local route)
    mesa_ipv6_t         destination;
} mesa_ipv6_uc_t;

// IPv4 multicast routing entry
typedef struct
{
    // Multicast Group address
    mesa_ipv4_t group;

    // SIP address. All zero address enables source independent MC groups [*.G]
    mesa_ipv4_t source;
} mesa_ipv4_mc_t;

// IPv6 multicast routing entry
typedef struct
{
    // Multicast Group address
    mesa_ipv6_t group;

    // SIP address. All zero address enables source independent MC groups [*.G]
    mesa_ipv6_t source;
} mesa_ipv6_mc_t;

// Unicast Routing entry
typedef struct
{
   // Type of unicast route
   mesa_routing_entry_type_t type;

   union {
       // IPv4 unicast route
       mesa_ipv4_uc_t ipv4_uc;

       // IPv6 unicast route
       mesa_ipv6_uc_t ipv6_uc;
   } route; // Route

   // Link-local addresses needs to specify a egress vlan.
   mesa_vid_t vlan;

} mesa_routing_entry_t;

#define MESA_RT_TYPE_IPV4_MC 0
#define MESA_RT_TYPE_IPV6_MC 1

// Multicast Routing entry
typedef struct
{
    // Type of multicast route: MESA_RT_TYPE_IPV4_MC or MESA_RT_TYPE_IPV6_MC
    mesa_bool_t type;

    union {
        // IPv4 multicast route
        mesa_ipv4_mc_t ipv4_mc;

        // IPv6 multicast route
        mesa_ipv6_mc_t ipv6_mc;
    } route; // MC Route

    // Optional: Multicast Reverse Path Forwarding, use MESA_VID_NULL to ignore
    mesa_vid_t source_rleg;
} mesa_routing_mc_entry_t;


// Routing interface statics counter
typedef struct {
    uint64_t ipv4uc_received_octets;    // IPv4UC octets received and hardware forwarded
    uint64_t ipv4uc_received_frames;    // IPv4UC frames received and hardware forwarded
    uint64_t ipv6uc_received_octets;    // IPv6UC octets received and hardware forwarded
    uint64_t ipv6uc_received_frames;    // IPv6UC frames received and hardware forwarded

    uint64_t ipv4uc_transmitted_octets; // IPv4UC octets transmitted
    uint64_t ipv4uc_transmitted_frames; // IPv4UC frames transmitted
    uint64_t ipv6uc_transmitted_octets; // IPv6UC octets transmitted
    uint64_t ipv6uc_transmitted_frames; // IPv6UC frames transmitted

    uint64_t ipv4mc_received_octets;    // IPv4MC octets received and hardware forwarded
    uint64_t ipv4mc_received_frames;    // IPv4MC frames received and hardware forwarded
    uint64_t ipv6mc_received_octets;    // IPv6MC octets received and hardware forwarded
    uint64_t ipv6mc_received_frames;    // IPv6MC frames received and hardware forwarded

    uint64_t ipv4mc_transmitted_octets; // IPv4MC octets transmitted
    uint64_t ipv4mc_transmitted_frames; // IPv4MC frames transmitted
    uint64_t ipv6mc_transmitted_octets; // IPv6MC octets transmitted
    uint64_t ipv6mc_transmitted_frames; // IPv6MC frames transmitted
} mesa_l3_counters_t;

/****************************************************************************
 * VCAP types
 ****************************************************************************/
// VCAP 1 bit
typedef enum
{
    MESA_VCAP_BIT_ANY, // Value 0 or 1
    MESA_VCAP_BIT_0,   // Value 0
    MESA_VCAP_BIT_1    // Value 1
} mesa_vcap_bit_t;

// VCAP 8 bit value and mask
typedef struct
{
    uint8_t value;   // Value
    uint8_t mask;    // Mask, cleared bits are wildcards
} mesa_vcap_u8_t;

// VCAP 16 bit value and mask
typedef struct
{
    uint8_t value[2];   // Value
    uint8_t mask[2];    // Mask, cleared bits are wildcards
} mesa_vcap_u16_t;

// VCAP 24 bit value and mask
typedef struct
{
    uint8_t value[3];   // Value
    uint8_t mask[3];    // Mask, cleared bits are wildcards
} mesa_vcap_u24_t;

// VCAP 32 bit value and mask
typedef struct
{
    uint8_t value[4];   // Value
    uint8_t mask[4];    // Mask, cleared bits are wildcards
} mesa_vcap_u32_t;

// VCAP 40 bit value and mask
typedef struct
{
    uint8_t value[5];   // Value
    uint8_t mask[5];    // Mask, cleared bits are wildcards
} mesa_vcap_u40_t;

// VCAP 48 bit value and mask
typedef struct
{
    uint8_t value[6];   // Value
    uint8_t mask[6];    // Mask, cleared bits are wildcards
} mesa_vcap_u48_t;

// VCAP 128 bit value and mask
typedef struct
{
    uint8_t value[16];   // Value
    uint8_t mask[16];    // Mask, cleared bits are wildcards
} mesa_vcap_u128_t;

// VCAP VLAN ID value and mask
typedef struct
{
    uint16_t value;   // Value
    uint16_t mask;    // Mask, cleared bits are wildcards
} mesa_vcap_vid_t;

// VCAP IPv4 address value and mask
typedef struct
{
    mesa_ip_t value;   // Value
    mesa_ip_t mask;    // Mask, cleared bits are wildcards
} mesa_vcap_ip_t;

// VCAP UDP/TCP port range
typedef struct
{
    mesa_bool_t    in_range;   // Port in range match
    mesa_udp_tcp_t low;        // Port low value
    mesa_udp_tcp_t high;       // Port high value
} mesa_vcap_udp_tcp_t;

// Value/Range type
typedef enum
{
    MESA_VCAP_VR_TYPE_VALUE_MASK,      // Used as value/mask
    MESA_VCAP_VR_TYPE_RANGE_INCLUSIVE, // Used as inclusive range: low <= range <= high
    MESA_VCAP_VR_TYPE_RANGE_EXCLUSIVE  // Used as exclusive range: range < low or range > high
} mesa_vcap_vr_type_t;

// VCAP universal value or range type
typedef uint16_t mesa_vcap_vr_value_t;

// VCAP value/mask
typedef struct
{
    mesa_vcap_vr_value_t value; // Value
    mesa_vcap_vr_value_t mask;  // Mask, cleared bits are wildcards
} mesa_vcap_vr_v_t;

// VCAP range
typedef struct
{
    mesa_vcap_vr_value_t low;  // Low value
    mesa_vcap_vr_value_t high; // High value
} mesa_vcap_vr_r_t;

// VCAP universal value or range
typedef struct
{
    mesa_vcap_vr_type_t type; // Type
    union
    {
        mesa_vcap_vr_v_t v; // type == MESA_VCAP_VR_TYPE_VALUE_MASK
        mesa_vcap_vr_r_t r; // type == MESA_VCAP_VR_TYPE_RANGE_XXXXXX
    } vr; // Value or range
} mesa_vcap_vr_t;

// VCAP key type
typedef enum {
    MESA_VCAP_KEY_TYPE_NORMAL,     // Half key, SIP only
    MESA_VCAP_KEY_TYPE_DOUBLE_TAG, // Quarter key, two tags
    MESA_VCAP_KEY_TYPE_IP_ADDR,    // Half key, SIP and DIP
    MESA_VCAP_KEY_TYPE_MAC_IP_ADDR // Full key, MAC and IP addresses
} mesa_vcap_key_type_t;

/****************************************************************************
 * ACL types
 ****************************************************************************/
// ACL policer number
typedef uint32_t mesa_acl_policer_no_t;

#define MESA_ACL_POLICY_NO_NONE  0xffffffff // ACLs disabled on port

// ACL policy number
typedef uint32_t mesa_acl_policy_no_t;

// Counter
typedef uint64_t mesa_counter_t;

// Counter pair
typedef struct {
    mesa_counter_t frames; // Number of frames
    mesa_counter_t bytes;  // Number of bytes
} mesa_counter_pair_t;

// EVC/ECE counters
typedef struct {
    mesa_counter_pair_t rx_green;   // Rx green frames/bytes
    mesa_counter_pair_t rx_yellow;  // Rx yellow frames/bytes
    mesa_counter_pair_t rx_red;     // Rx red frames/bytes
    mesa_counter_pair_t rx_discard; // Rx discarded frames/bytes
    mesa_counter_pair_t tx_discard; // Tx discarded frames/bytes
    mesa_counter_pair_t tx_green;   // Tx green frames/bytes
    mesa_counter_pair_t tx_yellow;  // Tx yellow frames/bytes
} mesa_evc_counters_t;

// MPLS TC bits
typedef uint8_t mesa_mpls_tc_t;

/****************************************************************************
 * 1588 types
 ****************************************************************************/

// Clock adjustment rate in parts per billion (ppb) * 1<<16.
// Range is +-2**47 ppb
// For example, 8.25 ppb is expressed as 0x0000.0000.0008.4000
typedef int64_t mesa_clk_adj_rate_t;

// Time interval in ns * 1<<16
// range +-2**47 ns = 140737 sec = 39 hours
// For example, 2.5 ns is expressed as 0x0000.0000.0002.8000
typedef int64_t mesa_timeinterval_t;

#define MESA_ONE_MIA 1000000000 // One billion
#define MESA_ONE_MILL   1000000 // One million
#define MESA_MAX_TIMEINTERVAL 0x7fffffffffffffffLL // Maximum time interval

#define MESA_INTERVAL_SEC(t) ((int32_t)MESA_DIV64((t)>>16, MESA_ONE_MIA)) // One Second time interval
#define MESA_INTERVAL_MS(t)  ((int32_t)MESA_DIV64((t)>>16, MESA_ONE_MILL)) // One millisecond time interval
#define MESA_INTERVAL_US(t)  ((int32_t)MESA_DIV64((t)>>16, 1000)) // One microsecond time interval
#define MESA_INTERVAL_NS(t)  ((int32_t)MESA_MOD64((t)>>16, MESA_ONE_MIA)) // This returns the ns part of the interval, not the total number of ns
#define MESA_INTERVAL_PS(t)  (((((int32_t)(t & 0xffff))*1000)+0x8000)/0x10000) // This returns the ps part of the interval, not the total number of ps
#define MESA_SEC_NS_INTERVAL(s,n) (((mesa_timeinterval_t)(n)+(mesa_timeinterval_t)(s)*MESA_ONE_MIA)<<16)  // TBD

// Time stamp in seconds and nanoseconds
typedef struct {
    uint16_t sec_msb;         // Seconds msb
    uint32_t seconds;         // Seconds
    uint32_t nanoseconds;     // nanoseconds
    uint16_t nanosecondsfrac; // 16 bit fraction of nano seconds
} mesa_timestamp_t;

// Scaled nanosec as defined in 802.1AS clause 6.3.3.1:
// The ScaledNs type represents signed values of time and time interval in units of 2**-16 ns.
typedef struct {
    int32_t  scaled_ns_high; // Seconds
    uint64_t scaled_ns_low;  // nanoseconds
} mesa_scaled_ns_t;

// Unsigned Scaled nanosec as defined in 802.1AS clause 6.3.3.2:
// The UScaledNs type represents unsigned values of time and time interval in units of 2**-16 ns.
typedef struct {
    uint32_t uscaled_ns_high; // Seconds
    uint64_t uscaled_ns_low;  // nanoseconds
} mesa_uscaled_ns_t;

#define MESA_CLOCK_IDENTITY_LENGTH 8 // Length of unique PTP identifier

// PTP clock unique identifier
typedef uint8_t mesa_clock_identity[MESA_CLOCK_IDENTITY_LENGTH];

#include <mscc/ethernet/switch/api/hdr_end.h>

#include <mscc/ethernet/switch/api/port_list.h>

#endif // _MSCC_ETHERNET_SWITCH_API_TYPES_
