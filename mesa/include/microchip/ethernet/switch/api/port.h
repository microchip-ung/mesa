// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_PORT_
#define _MICROCHIP_ETHERNET_SWITCH_API_PORT_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/switch/api/misc.h> // For mesa_sgpio_group_t
#include <microchip/ethernet/hdr_start.h>       // ALL INCLUDE ABOVE THIS LINE

// The internal bandwidth allocated for the port
typedef enum
{
    MESA_BW_DEFAULT,     // Default to max port speed
    MESA_BW_1G,          // Max 1G
    MESA_BW_2G5,         // Max 2.5G
    MESA_BW_5G,          // Max 5G
    MESA_BW_10G,         // Max 10G
    MESA_BW_25G,         // Max 25G
    MESA_BW_UNDEFINED,   // Undefined
} mesa_internal_bw_t;

// Enable/disable SD-to-SGPIO mapping
typedef enum
{
    MESA_SD_SGPIO_MAP_IGNORE,   /**< No mapping as default */
    MESA_SD_SGPIO_MAP_ENABLE,   /**< Enable and use mapping  */
    MESA_SD_SGPIO_MAP_DISABLE,  /**< Disable mapping globally */
} mesa_sd_sgpio_action_t;

// Signal detect mapping to SGPIO group/port/bit
typedef struct
{
    mesa_sd_sgpio_action_t action; // Enable mapping
    mesa_sgpio_group_t     group;  // SGPIO group (0-2)
    uint32_t               port;   // SGPIO port (0-31)
    uint32_t               bit;    // SGPIO bit (0-3)
} mesa_port_sgpio_map_t;

// Signifies an unused chip port
#define CHIP_PORT_UNUSED -1

// Port map structure
typedef struct
{
    int32_t                chip_port;             // Set to -1 if not used
    mesa_chip_no_t         chip_no;               // Chip number, multi-chip targets
    mesa_internal_bw_t     max_bw CAP(PORT_BW);   // Max internal bandwidth reserved for the port
    mesa_miim_controller_t miim_controller;       // MII management controller
    uint8_t                miim_addr;             // PHY address, ignored for MESA_MIIM_CONTROLLER_NONE
    mesa_chip_no_t         miim_chip_no;          // MII management chip number, multi-chip targets
    mesa_port_sgpio_map_t  sd_map CAP(SGPIO_MAP); // PCS signal detect to SGPIO bit map
} mesa_port_map_t;

// Set port map.
// cnt [IN]       Number of entries in port_map. Must be equal to the configured port count.
// port_map [IN]  Port map array.
mesa_rc mesa_port_map_set(const mesa_inst_t     inst,
                          uint32_t              cnt,
                          const mesa_port_map_t *port_map);

// Get port map.
// cnt [IN]        Number of entries in port_map. Must be equal to the configured port count.
// port_map [OUT]  Port map.
mesa_rc mesa_port_map_get(const mesa_inst_t  inst,
                          uint32_t           cnt,
                          mesa_port_map_t    *port_map);

/**
 * Advertisement Word (Refer to IEEE 802.3 Clause 37):
 *  MSB                                                                         LSB
 *  D15  D14  D13  D12  D11  D10   D9   D8   D7   D6   D5   D4   D3   D2   D1   D0
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 * | NP | Ack| RF2| RF1|rsvd|rsvd|rsvd| PS2| PS1| HD | FD |rsvd|rsvd|rsvd|rsvd|rsvd|
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 **/

// Auto-negotiation remote fault type
typedef enum                              // RF2      RF1
{
    MESA_PORT_CLAUSE_37_RF_LINK_OK       = ((0<<1) | (0<<0)), // Link OK
    MESA_PORT_CLAUSE_37_RF_OFFLINE       = ((1<<1) | (0<<0)), // Off line
    MESA_PORT_CLAUSE_37_RF_LINK_FAILURE  = ((0<<1) | (1<<0)), // Link failure
    MESA_PORT_CLAUSE_37_RF_AUTONEG_ERROR = ((1<<1) | (1<<0))  // Autoneg error
} mesa_port_clause_37_remote_fault_t;

// Advertisement control data for Clause 37 aneg
typedef struct
{
    mesa_bool_t                        fdx;              // (FD)
    mesa_bool_t                        hdx;              // (HD)
    mesa_bool_t                        symmetric_pause;  // (PS1)
    mesa_bool_t                        asymmetric_pause; // (PS2)
    mesa_port_clause_37_remote_fault_t remote_fault;     // (RF1) + (RF2)
    mesa_bool_t                        acknowledge;      // (Ack)
    mesa_bool_t                        next_page;        // (NP)
} mesa_port_clause_37_adv_t;

// Advertisement control data for SGMII aneg
typedef struct
{
    mesa_bool_t link;          // LP link status
    mesa_bool_t fdx;           // FD
    mesa_bool_t hdx;           // HD
    mesa_bool_t speed_10M;     // speed 10 advertised
    mesa_bool_t speed_100M;    // speed 100 advertised
    mesa_bool_t speed_1G;      // speed 1G advertised
    mesa_bool_t aneg_complete; // Aneg process completed
} mesa_port_sgmii_aneg_t;

// Auto-negotiation control parameter struct
typedef struct
{
    mesa_bool_t               enable;        // Enable of Autoneg
    mesa_port_clause_37_adv_t advertisement; // Clause 37 Advertisement control data
} mesa_port_clause_37_control_t;

// Get clause 37 auto-negotiation Control word.
// port_no [IN]   Port number.
// control [OUT]  Control structure.
mesa_rc mesa_port_clause_37_control_get(const mesa_inst_t              inst,
                                        const mesa_port_no_t           port_no,
                                        mesa_port_clause_37_control_t  *const control);

// Set clause 37 auto-negotiation Control word.
// port_no [IN]  Port number.
// control [IN]  Control structure.
mesa_rc mesa_port_clause_37_control_set(const mesa_inst_t                    inst,
                                        const mesa_port_no_t                 port_no,
                                        const mesa_port_clause_37_control_t  *const control);

// Flow control setup
typedef struct
{
    mesa_bool_t obey;     // TRUE if 802.3x PAUSE frames should be obeyed
    mesa_bool_t generate; // TRUE if 802.3x PAUSE frames should generated
    mesa_mac_t  smac;     // Port MAC address used as SMAC in PAUSE frames

    // TRUE if 802.1Qbb Priority Flow Control should be generated and obeyed.
    // Cannot be enabled together with 802.3x Flowcontrol
    mesa_bool_t pfc[MESA_PRIO_ARRAY_SIZE];
} mesa_port_flow_control_conf_t;

// Inter frame gap structure
typedef struct
{
    uint32_t hdx_gap_1; // Half duplex: First part of Rx to Tx gap
    uint32_t hdx_gap_2; // Half duplex: Second part of Rx to Tx gap
    uint32_t fdx_gap;   // Full duplex: Tx to Tx gap
} mesa_port_frame_gaps_t;

#define MESA_MAX_FRAME_LENGTH_STANDARD 1518  // IEEE 802.3 standard

// VLAN awareness for frame length check
typedef enum
{
    MESA_PORT_MAX_TAGS_NONE, // No extra tags allowed
    MESA_PORT_MAX_TAGS_ONE,  // Single tag allowed
    MESA_PORT_MAX_TAGS_TWO   // Single and double tag allowed
} mesa_port_max_tags_t;

// Port loop back configuration
typedef enum
{
    MESA_PORT_LOOP_DISABLE,  // No port loop
    MESA_PORT_LOOP_PCS_HOST, // PCS host port loop
} mesa_port_loop_t;

// SFI Serdes configuration
typedef struct
{
    mesa_bool_t             sfp_dac;    // obsolete (use media_10g)
    mesa_sd10g_media_type_t media_type; // The 10G Serdes media/cable type
    mesa_bool_t             rx_invert;  // Invert the RX Serdes signal (1)
    mesa_bool_t             tx_invert;  // Invert the TX Serdes signal (1)
} mesa_port_serdes_conf_t;

// 1G PCS specific configuration
typedef enum
{
    MESA_PORT_PCS_NORMAL,  // Normal 1G PCS configuration
    MESA_PORT_PCS_ENABLE,  // Only Enable 1G PCS and return
    MESA_PORT_PCS_DISABLE, // Only Disable 1G PCS and return
    MESA_PORT_PCS_IGNORE   // Skip any PCS settings
} mesa_port_pcs_conf_t CAP(PORT_PCS_CONF);

// Port configuration structure
typedef struct
{
    // Note: If if_type field is set to MESA_PORT_INTERFACE_QSGMII, the ports are mapped together in groups of four.
    // If one of the four ports is used, all four ports in the group must always be configured,
    // but the four ports doesn't need to configured with the same configuration.
    // This is needed in order to achieve correct comma alignment at the QSGMII interface.
    // Which ports that are mapped together can be found in the chip data-sheet.
    mesa_port_interface_t   if_type;           // Interface type

    mesa_bool_t             sd_enable;         // Signal detect enable
    mesa_bool_t             sd_active_high;    // External signal detect polarity
    mesa_bool_t             sd_internal;       // Internal signal detect selection
    mesa_port_frame_gaps_t  frame_gaps;        // Inter frame gaps
    mesa_bool_t             power_down;        // Disable and power down the port
    mesa_port_speed_t       speed;             // Port speed
    mesa_bool_t             fdx;               // Full duplex mode
    mesa_port_flow_control_conf_t flow_control; // Flow control setup
    uint32_t                max_frame_length;  // Maximum frame length
    mesa_bool_t             frame_length_chk;  // Enforce 802.3 frame length check (from ethertype field)
    mesa_port_max_tags_t    max_tags;          // VLAN awareness for length check
    mesa_bool_t             exc_col_cont;      // Excessive collision continuation
    mesa_bool_t             xaui_rx_lane_flip; // Xaui Rx lane flip
    mesa_bool_t             xaui_tx_lane_flip; // Xaui Tx lane flip
    mesa_port_loop_t        loop;              // Enable/disable of port loop back
    mesa_port_serdes_conf_t serdes;            // Serdes settings (for SFI interface)
    mesa_port_pcs_conf_t    pcs CAP(PORT_PCS_CONF); // Special 1G PCS settings, only supported for L26
} mesa_port_conf_t;

// Set port configuration.
// port_no [IN]  Port number.
// conf [IN]     Port setup structure.
mesa_rc mesa_port_conf_set(const mesa_inst_t       inst,
                           const mesa_port_no_t    port_no,
                           const mesa_port_conf_t  *const conf);

// Get port configuration.
// port_no [IN]  Port number.
// conf [OUT]    Port configuration.
mesa_rc mesa_port_conf_get(const mesa_inst_t     inst,
                           const mesa_port_no_t  port_no,
                           mesa_port_conf_t      *const conf);

// Get port status.
// port_no [IN]  Port number.
// status [OUT]  Status structure.
mesa_rc mesa_port_status_get(const mesa_inst_t     inst,
                             const mesa_port_no_t  port_no,
                             mesa_port_status_t    *const status);

/******************************************************************************/
/* Port Counters                                                              */
/******************************************************************************/

// Counter type
typedef uint64_t mesa_port_counter_t;

// RMON counter structure (RFC 2819)
typedef struct {
    mesa_port_counter_t rx_etherStatsDropEvents;           // Rx drop events
    mesa_port_counter_t rx_etherStatsOctets;               // Rx octets
    mesa_port_counter_t rx_etherStatsPkts;                 // Rx packets
    mesa_port_counter_t rx_etherStatsBroadcastPkts;        // Rx broadcasts
    mesa_port_counter_t rx_etherStatsMulticastPkts;        // Rx multicasts
    mesa_port_counter_t rx_etherStatsCRCAlignErrors;       // Rx CRC/alignment errors
    mesa_port_counter_t rx_etherStatsUndersizePkts;        // Rx undersize packets
    mesa_port_counter_t rx_etherStatsOversizePkts;         // Rx oversize packets
    mesa_port_counter_t rx_etherStatsFragments;            // Rx fragments
    mesa_port_counter_t rx_etherStatsJabbers;              // Rx jabbers
    mesa_port_counter_t rx_etherStatsPkts64Octets;         // Rx 64 byte packets
    mesa_port_counter_t rx_etherStatsPkts65to127Octets;    // Rx 65-127 byte packets
    mesa_port_counter_t rx_etherStatsPkts128to255Octets;   // Rx 128-255 byte packets
    mesa_port_counter_t rx_etherStatsPkts256to511Octets;   // Rx 256-511 byte packets
    mesa_port_counter_t rx_etherStatsPkts512to1023Octets;  // Rx 512-1023 byte packet
    mesa_port_counter_t rx_etherStatsPkts1024to1518Octets; // Rx 1024-1518 byte packets
    mesa_port_counter_t rx_etherStatsPkts1519toMaxOctets;  // Rx 1519- byte packets

    mesa_port_counter_t tx_etherStatsDropEvents;           // Tx drop events
    mesa_port_counter_t tx_etherStatsOctets;               // Tx octets
    mesa_port_counter_t tx_etherStatsPkts;                 // Tx packets
    mesa_port_counter_t tx_etherStatsBroadcastPkts;        // Tx broadcasts
    mesa_port_counter_t tx_etherStatsMulticastPkts;        // Tx multicasts
    mesa_port_counter_t tx_etherStatsCollisions;           // Tx collisions
    mesa_port_counter_t tx_etherStatsPkts64Octets;         // Tx 64 byte packets
    mesa_port_counter_t tx_etherStatsPkts65to127Octets;    // Tx 65-127 byte packets
    mesa_port_counter_t tx_etherStatsPkts128to255Octets;   // Tx 128-255 byte packets
    mesa_port_counter_t tx_etherStatsPkts256to511Octets;   // Tx 256-511 byte packets
    mesa_port_counter_t tx_etherStatsPkts512to1023Octets;  // Tx 512-1023 byte packet
    mesa_port_counter_t tx_etherStatsPkts1024to1518Octets; // Tx 1024-1518 byte packets
    mesa_port_counter_t tx_etherStatsPkts1519toMaxOctets;  // Tx 1519- byte packets
} mesa_port_rmon_counters_t;

// Interfaces Group counter structure (RFC 2863)
typedef struct {
    mesa_port_counter_t ifInOctets;          // Rx octets
    mesa_port_counter_t ifInUcastPkts;       // Rx unicasts
    mesa_port_counter_t ifInMulticastPkts;   // Rx multicasts
    mesa_port_counter_t ifInBroadcastPkts;   // Rx broadcasts
    mesa_port_counter_t ifInNUcastPkts;      // Rx non-unicasts
    mesa_port_counter_t ifInDiscards;        // Rx discards
    mesa_port_counter_t ifInErrors;          // Rx errors

    mesa_port_counter_t ifOutOctets;         // Tx octets
    mesa_port_counter_t ifOutUcastPkts;      // Tx unicasts
    mesa_port_counter_t ifOutMulticastPkts;  // Tx multicasts
    mesa_port_counter_t ifOutBroadcastPkts;  // Tx broadcasts
    mesa_port_counter_t ifOutNUcastPkts;     // Tx non-unicasts
    mesa_port_counter_t ifOutDiscards;       // Tx discards
    mesa_port_counter_t ifOutErrors;         // Tx errors
} mesa_port_if_group_counters_t;

// Ethernet-like Interface counter structure (RFC 3635)
typedef struct {
    mesa_port_counter_t dot3StatsAlignmentErrors          CAP(PORT_CNT_ETHER_LIKE); // Rx alignment errors
    mesa_port_counter_t dot3StatsFCSErrors                CAP(PORT_CNT_ETHER_LIKE); // Rx FCS errors
    mesa_port_counter_t dot3StatsFrameTooLongs            CAP(PORT_CNT_ETHER_LIKE); // Rx too long
    mesa_port_counter_t dot3StatsSymbolErrors             CAP(PORT_CNT_ETHER_LIKE); // Rx symbol errors
    mesa_port_counter_t dot3ControlInUnknownOpcodes       CAP(PORT_CNT_ETHER_LIKE); // Rx unknown opcodes
    mesa_port_counter_t dot3InPauseFrames;                 // Rx pause

    mesa_port_counter_t dot3StatsSingleCollisionFrames    CAP(PORT_CNT_ETHER_LIKE); // Tx single collisions
    mesa_port_counter_t dot3StatsMultipleCollisionFrames  CAP(PORT_CNT_ETHER_LIKE); // Tx multiple collisions
    mesa_port_counter_t dot3StatsDeferredTransmissions    CAP(PORT_CNT_ETHER_LIKE); // Tx deferred
    mesa_port_counter_t dot3StatsLateCollisions           CAP(PORT_CNT_ETHER_LIKE); // Tx late collisions
    mesa_port_counter_t dot3StatsExcessiveCollisions      CAP(PORT_CNT_ETHER_LIKE); // Tx excessive collisions
    mesa_port_counter_t dot3StatsCarrierSenseErrors       CAP(PORT_CNT_ETHER_LIKE); // Tx carrier sense errors
    mesa_port_counter_t dot3OutPauseFrames;                // Tx pause
} mesa_port_ethernet_like_counters_t;

// Port bridge counter structure (RFC 4188)
typedef struct
{
    mesa_port_counter_t dot1dTpPortInDiscards; // Rx bridge discards
} mesa_port_bridge_counters_t;

// Port counters per (PORT, PRIO)
typedef struct {
    mesa_port_counter_t rx; // Rx frames
    mesa_port_counter_t tx; // Tx frames
    mesa_port_counter_t rx_green          CAP(PORT_CNT_EVC); // Rx green frames
    mesa_port_counter_t rx_yellow         CAP(PORT_CNT_EVC); // Rx yellow frames
    mesa_port_counter_t rx_red            CAP(PORT_CNT_EVC); // Rx red frames
    mesa_port_counter_t rx_green_discard  CAP(PORT_CNT_EVC); // Rx green discarded frames
    mesa_port_counter_t rx_yellow_discard CAP(PORT_CNT_EVC); // Rx yellow discarded frames
    mesa_port_counter_t tx_green          CAP(PORT_CNT_EVC); // Tx green frames
    mesa_port_counter_t tx_yellow         CAP(PORT_CNT_EVC); // Tx yellow frames
} mesa_port_prio_counters_t;

// Port 802.3br counter structure
typedef struct
{
    mesa_port_counter_t aMACMergeFrameAssErrorCount; // Rx counter
    mesa_port_counter_t aMACMergeFrameSmdErrorCount; // Rx counter
    mesa_port_counter_t aMACMergeFrameAssOkCount;    // Rx counter
    mesa_port_counter_t aMACMergeFragCountRx;        // Rx counter
    mesa_port_counter_t aMACMergeFragCountTx;        // Tx counter
    mesa_port_counter_t aMACMergeHoldCount;          // Tx counter
} mesa_port_dot3br_counters_t;

// Port counter structure
typedef struct
{
    mesa_port_rmon_counters_t          rmon;                             // RMON counters
    mesa_port_if_group_counters_t      if_group;                         // Interfaces Group counters
    mesa_port_ethernet_like_counters_t ethernet_like;                    // Ethernet-like Interface counters
    mesa_port_bridge_counters_t        bridge;                           // Bridge counters
    mesa_port_prio_counters_t          prio[MESA_PRIO_ARRAY_SIZE];       // Priority counters
    mesa_port_dot3br_counters_t        dot3br CAP(QOS_FRAME_PREEMPTION); // 802.3br counters
} mesa_port_counters_t;

// Update counters for port.
// port_no [IN]  Port number.
mesa_rc mesa_port_counters_update(const mesa_inst_t     inst,
                                  const mesa_port_no_t  port_no);

// Clear counters for port.
// port_no [IN]  Port/aggregation number.
mesa_rc mesa_port_counters_clear(const mesa_inst_t     inst,
                                 const mesa_port_no_t  port_no);

// Get counters for port.
// port_no [IN]    Port/aggregation number.
// counters [OUT]  Counter structure.
mesa_rc mesa_port_counters_get(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               mesa_port_counters_t  *const counters);

// Basic counters structure
typedef struct
{
    uint32_t rx_frames; // Rx frames
    uint32_t tx_frames; // Tx frames
} mesa_basic_counters_t;

// Get basic counters for port.
// port_no [IN]    Port/aggregation number.
// counters [OUT]  Counter structure.
mesa_rc mesa_port_basic_counters_get(const mesa_inst_t     inst,
                                     const mesa_port_no_t  port_no,
                                     mesa_basic_counters_t *const counters);

// Port forwarding state
typedef enum
{
    MESA_PORT_FORWARD_ENABLED,   // Forward in both directions
    MESA_PORT_FORWARD_DISABLED,  // Forwarding and learning disabled
    MESA_PORT_FORWARD_INGRESS,   // Forward frames from port only
    MESA_PORT_FORWARD_EGRESS     // Forward frames to port only (learning disabled)
} mesa_port_forward_t;

// Get port forwarding state.
// port_no [IN]   Port number.
// forward [OUT]  Forwarding state.
mesa_rc mesa_port_forward_state_get(const mesa_inst_t     inst,
                                    const mesa_port_no_t  port_no,
                                    mesa_port_forward_t   *const forward);

// Set port forwarding state.
// port_no [IN]  Port number.
// forward [IN]  Forwarding state.
//               By default, forwarding is enabled in both directions.
mesa_rc mesa_port_forward_state_set(const mesa_inst_t          inst,
                                    const mesa_port_no_t       port_no,
                                    const mesa_port_forward_t  forward);

// Port Internal Frame Header structure
typedef struct
{
    mesa_bool_t ena_inj_header CAP(PORT_INJ_HDR); // Enable injection header
    mesa_bool_t ena_xtr_header CAP(PORT_XTR_HDR); // Enable extraction header
    mesa_bool_t ena_ifh_header CAP(PORT_XTR_HDR); // Same as ena_xtr_header (JR1 compatibility)
} mesa_port_ifh_t CAP(PORT_IFH);

// Set port Internal Frame Header settings.
// port_no [IN]  Port number.
// conf [IN]     Port IFH structure.
mesa_rc mesa_port_ifh_conf_set(const mesa_inst_t       inst,
                               const mesa_port_no_t    port_no,
                               const mesa_port_ifh_t  *const conf)
    CAP(PORT_IFH);

// Get port Internal Frame Header settings.
// port_no [IN]  Port number.
// conf [OUT]    Port IFH configuration.
mesa_rc mesa_port_ifh_conf_get(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               mesa_port_ifh_t      *const conf)
    CAP(PORT_IFH);

// Read value from MIIM register.
// port_no [IN]  Port number.
// addr    [IN]  PHY register address.
// value   [OUT] PHY register value.
mesa_rc mesa_port_miim_read(const mesa_inst_t    inst,
                            const mesa_port_no_t port_no,
                            const uint8_t        addr,
                            uint16_t             *const value);

// Write value to MIIM register.
// port_no [IN]  Port number.
// addr    [IN]  PHY register address.
// value   [IN]  PHY register value.
mesa_rc mesa_port_miim_write(const mesa_inst_t    inst,
                             const mesa_port_no_t port_no,
                             const uint8_t        addr,
                             const uint16_t       value);

// Direct MIIM read (bypassing port map)
// chip_no         [IN]  Chip number (if multi-chip instance).
// miim_controller [IN]  MIIM Controller Instance
// miim_addr       [IN]  MIIM Device Address
// addr            [IN]  MIIM Register Address
// value           [OUT] Register value read
mesa_rc mesa_miim_read(const mesa_inst_t            inst,
                       const mesa_chip_no_t         chip_no,
                       const mesa_miim_controller_t miim_controller,
                       const uint8_t                miim_addr,
                       const uint8_t                addr,
                       uint16_t                     *const value);

// Direct MIIM write (bypassing port map)
// chip_no         [IN]  Chip number (if multi-chip instance).
// miim_controller [IN]  MIIM Controller Instance
// miim_addr       [IN]  MIIM Device Address
// addr            [IN]  MIIM Register Address
// value           [IN]  Register value to write
mesa_rc mesa_miim_write(const mesa_inst_t            inst,
                        const mesa_chip_no_t         chip_no,
                        const mesa_miim_controller_t miim_controller,
                        const uint8_t                miim_addr,
                        const uint8_t                addr,
                        const uint16_t               value);

// Read value from MMD register.
// port_no [IN]  Port number connected to MMD.
// mmd     [IN]  MMD number.
// addr    [IN]  PHY register address.
// value   [OUT] PHY register value.
mesa_rc mesa_port_mmd_read(const mesa_inst_t     inst,
                           const mesa_port_no_t  port_no,
                           const uint8_t         mmd,
                           const uint16_t        addr,
                           uint16_t              *const value)
    CAP(PORT_10G);

// Read values (a number of 16 bit values) from MMD register.
// port_no [IN]  Port number connected to MMD.
// mmd     [IN]  MMD number.
// addr    [IN]  PHY register address.
// buf     [OUT] PHY register values.
// count   [IN]  number of values to read.
mesa_rc mesa_port_mmd_read_inc(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               const uint8_t         mmd,
                               const uint16_t        addr,
                               uint16_t              *const buf,
                               uint8_t               count)
    CAP(PORT_10G);

// Write value to MMD register.
// port_no [IN]  Port number connected to MMD.
// mmd     [IN]  MMD number.
// addr    [IN]  PHY register address.
// value   [IN]  PHY register value.
mesa_rc mesa_port_mmd_write(const mesa_inst_t     inst,
                            const mesa_port_no_t  port_no,
                            const uint8_t         mmd,
                            const uint16_t        addr,
                            const uint16_t        value)
    CAP(PORT_10G);

// Read, modify and write value to MMD register.
// port_no  [IN]  Port number connected to MMD.
// mmd      [IN]  MMD number.
// addr     [IN]  PHY register address.
// value    [IN]  PHY register value.
// mask     [IN]  PHY register mask, only enabled bits are changed.
mesa_rc mesa_port_mmd_masked_write(const mesa_inst_t     inst,
                                   const mesa_port_no_t  port_no,
                                   const uint8_t         mmd,
                                   const uint16_t        addr,
                                   const uint16_t        value,
                                   const uint16_t        mask)
    CAP(PORT_10G);

// Direct MMD read (Clause 45, bypassing port map)
// chip_no         [IN]  Chip number (if multi-chip instance).
// miim_controller [IN]  MIIM Controller Instance
// miim_addr       [IN]  MIIM Device Address
// mmd             [IN]  MMD number.
// addr            [IN]  MIIM Register Address
// value           [OUT] Register value read
mesa_rc mesa_mmd_read(const mesa_inst_t            inst,
                      const mesa_chip_no_t         chip_no,
                      const mesa_miim_controller_t miim_controller,
                      const uint8_t                miim_addr,
                      const uint8_t                mmd,
                      const uint16_t               addr,
                      uint16_t                     *const value)
    CAP(PORT_10G);

// Direct MMD write (Clause 45, bypassing port map)
// chip_no         [IN]  Chip number (if multi-chip instance).
// miim_controller [IN]  MIIM Controller Instance
// miim_addr       [IN]  MIIM Device Address
// mmd             [IN]  MMD number.
// addr            [IN]  MIIM Register Address
// value           [IN]  Register value to write
mesa_rc mesa_mmd_write(const mesa_inst_t            inst,
                       const mesa_chip_no_t         chip_no,
                       const mesa_miim_controller_t miim_controller,
                       const uint8_t                miim_addr,
                       const uint8_t                mmd,
                       const uint16_t               addr,
                       const uint16_t               value)
    CAP(PORT_10G);

/******************************************************************************/
/* 10G/25G KR Backplane Ethernet                                              */
/******************************************************************************/

// KR Aneg status
typedef struct {
    mesa_bool_t       complete;                       // Aneg completed successfully
    mesa_bool_t       active;                         // Aneg is running
    mesa_port_speed_t speed_req;                      // Speed negotiated (needs to be configured)
    mesa_bool_t       request_fec_change;             // FEC state change is negotiated (needs to be configured)
    mesa_bool_t       r_fec_enable;                   // Base-R-FEC (Clause 74) is negotiated
    mesa_bool_t       rs_fec_enable CAP(PORT_KR_IRQ); // Base-RS-FEC (Clause 108) is negotiated
    uint32_t          sm;                             // (debug) Aneg state machine
    uint32_t          hist          CAP(PORT_KR_IRQ); // (debug) Aneg history
    mesa_bool_t       lp_aneg_able;                   // (debug) LP aneg ability
    mesa_bool_t       block_lock;                     // (debug) PCS block lock
    uint16_t          lp_bp0        CAP(PORT_KR_IRQ); // (debug) LP Base page 0-15
    uint16_t          lp_bp1        CAP(PORT_KR_IRQ); // (debug) LP Base page 16-31
    uint16_t          lp_bp2        CAP(PORT_KR_IRQ); // (debug) LP Base page 32-47
    uint16_t          lp_np0        CAP(PORT_KR_IRQ); // (debug) LP Next page 0-15
    uint16_t          lp_np1        CAP(PORT_KR_IRQ); // (debug) LP Next page 16-31
    uint16_t          lp_np2        CAP(PORT_KR_IRQ); // (debug) LP Next page 32-47
} mesa_port_kr_status_aneg_t        CAP(PORT_KR);

// KR Training status
typedef struct {
    mesa_bool_t complete;         // Training completed successfully, tap settings applied.
    uint8_t     cm_ob_tap_result; // The minus 1 coefficient c(-1). 7-bit signed, range: -32..31
    uint8_t     cp_ob_tap_result; // The 0 coefficient c(0).        7-bit signed, range: -32..31
    uint8_t     c0_ob_tap_result; // The plus 1 coefficient c(1).   7-bit signed, range: -32..31
    uint32_t    frame_sent       CAP(PORT_KR_IRQ); // Training frames sent
    uint16_t    frame_errors     CAP(PORT_KR_IRQ); // Training frames errors
} mesa_port_kr_status_train_t    CAP(PORT_KR);

// KR FEC status
typedef struct {
    mesa_bool_t  r_fec_enable;                   // FEC enabled (Clause 74)
    mesa_bool_t  rs_fec_enable CAP(PORT_KR_IRQ); // RS-FEC Enabled (Clause 108 / 25G)  */
    uint32_t     corrected_block_cnt;            // Corrected block count
    uint32_t     uncorrected_block_cnt;          // Un-corrected block count
} mesa_port_kr_status_fec_t CAP(PORT_KR);

// KR Aneg and Training structures
typedef struct {
    mesa_port_kr_status_aneg_t  aneg;  // Aneg structure
    mesa_port_kr_status_train_t train; // Training structure
    mesa_port_kr_status_fec_t   fec;   // FEC structure
} mesa_port_kr_status_t CAP(PORT_KR);


// KR Link Advertisement capability config
typedef struct {
    mesa_bool_t enable;                       // Autoneg enable
    mesa_bool_t adv_25g     CAP(PORT_KR_IRQ); // Advertise 25G
    mesa_bool_t adv_10g;                      // Advertise 10G
    mesa_bool_t adv_5g      CAP(PORT_KR_IRQ); // Advertise 5G
    mesa_bool_t adv_2g5     CAP(PORT_KR_IRQ); // Advertise 2G5
    mesa_bool_t adv_1g      CAP(PORT_KR_IRQ); // Advertise 1G
    mesa_bool_t r_fec_req;                    // Request R-FEC
    mesa_bool_t rs_fec_req  CAP(PORT_KR_IRQ); // Request RS-FEC (25G)
    mesa_bool_t next_page   CAP(PORT_KR_IRQ); // Use next page when advertise
    mesa_bool_t no_pd;                        // Do not enable parallel detect
} mesa_port_kr_aneg_t       CAP(PORT_KR);

// KR Training config
typedef struct {
    mesa_bool_t enable;                        // Enable KR training, BER method used
    mesa_bool_t no_remote   CAP(PORT_KR_IRQ);  // Do not train remote, only local
    mesa_bool_t no_eq_apply CAP(PORT_KR_IRQ);  // Do not apply EQ settings to HW (debug only)
    mesa_bool_t use_ber_cnt CAP(PORT_KR_IRQ);  // Use BER count instead of eye height
    mesa_bool_t test_mode   CAP(PORT_KR_IRQ);  // Debug only
    uint32_t test_repeat    CAP(PORT_KR_IRQ);  // Debug only
} mesa_port_kr_train_t      CAP(PORT_KR);

// KR configuration structures
typedef struct {
    mesa_port_kr_aneg_t  aneg;  // 10G-KR Aneg capability, 802.3ap Clause 73
    mesa_port_kr_train_t train; // 10G-KR Training parameters, 802.3ap Clause 72
} mesa_port_kr_conf_t CAP(PORT_KR);

// Set KR configuration incl. aneg and training.
// Aneg is started which starts the training process.
// The results can be read through mesa_port_kr_status_get().
// port_no [IN]  Port number.
// conf [IN]  Configuration structure.
mesa_rc mesa_port_kr_conf_set(const mesa_inst_t inst,
                                  const mesa_port_no_t port_no,
                                  const mesa_port_kr_conf_t *const conf)
    CAP(PORT_KR);

// Get KR configuration
// port_no [IN]   Port number.
// conf [OUT]  Configuration structure.
mesa_rc mesa_port_kr_conf_get(const mesa_inst_t inst,
                                  const mesa_port_no_t port_no,
                                  mesa_port_kr_conf_t *const conf)
    CAP(PORT_KR);

// Get KR Aneg and training status
// port_no [IN]  Port number.
// status [OUT]  KR Aneg and Training status
mesa_rc mesa_port_kr_status_get(const mesa_inst_t inst,
                                    const mesa_port_no_t port_no,
                                    mesa_port_kr_status_t *const status)
    CAP(PORT_KR);

#define MESA_KR_AN_RATE         (0xF)
#define MESA_KR_ACTV            (1 << 29)
#define MESA_KR_LPSVALID        (1 << 28)
#define MESA_KR_LPCVALID        (1 << 27)
#define MESA_KR_WT_DONE         (1 << 26)
#define MESA_KR_MW_DONE         (1 << 25)
#define MESA_KR_BER_BUSY_0      (1 << 24)
#define MESA_KR_BER_BUSY_1      (1 << 23)
#define MESA_KR_REM_RDY_0       (1 << 22)
#define MESA_KR_REM_RDY_1       (1 << 21)
#define MESA_KR_FRLOCK_0        (1 << 20)
#define MESA_KR_FRLOCK_1        (1 << 19)
#define MESA_KR_DME_VIOL_0      (1 << 18)
#define MESA_KR_DME_VIOL_1      (1 << 17)
#define MESA_KR_AN_XMIT_DISABLE (1 << 16)
#define MESA_KR_TRAIN           (1 << 15)
#define MESA_KR_RATE_DET        (1 << 14)
#define MESA_KR_CMPL_ACK        (1 << 13)
#define MESA_KR_AN_GOOD         (1 << 12)
#define MESA_KR_LINK_FAIL       (1 << 11)
#define MESA_KR_ABD_FAIL        (1 << 10)
#define MESA_KR_ACK_FAIL        (1 << 9)
#define MESA_KR_NP_FAIL         (1 << 8)
#define MESA_KR_NP_RX           (1 << 7)
#define MESA_KR_INCP_LINK       (1 << 6)
#define MESA_KR_GEN0_DONE       (1 << 5)
#define MESA_KR_GEN1_DONE       (1 << 4)
#define MESA_KR_ANEG_RATE_25G    7
#define MESA_KR_ANEG_RATE_25G_S  8
#define MESA_KR_ANEG_RATE_10G    9
#define MESA_KR_ANEG_RATE_5G     11
#define MESA_KR_ANEG_RATE_2G5    12
#define MESA_KR_ANEG_RATE_1G     13

typedef enum {
    MESA_TR_INITILIZE,
    MESA_TR_SEND_TRAINING,
    MESA_TR_TRAIN_LOCAL,
    MESA_TR_TRAIN_REMOTE,
    MESA_TR_SEND_DATA,
    MESA_TR_TRAINING_FAILURE,
    MESA_TR_LINK_READY
} mesa_train_state_t CAP(PORT_KR_IRQ);

typedef enum {
    MESA_BER_GO_TO_MIN,
    MESA_BER_CALCULATE_BER,
    MESA_BER_MOVE_TO_MID_MARK,
    MESA_BER_LOCAL_RX_TRAINED
} mesa_ber_stage_t CAP(PORT_KR_IRQ);

typedef enum {
    MESA_TAP_CM1,
    MESA_TAP_C0,
    MESA_TAP_CP1,
} mesa_kr_tap_t CAP(PORT_KR_IRQ);

typedef struct {
    uint16_t cm1;
    uint16_t c0;
    uint16_t cp1;
    uint16_t coef;
    uint16_t status;
} mesa_kr_status_results_t CAP(PORT_KR_IRQ);

typedef struct {
    uint32_t vga;
    uint32_t edc;
    uint32_t eqr;
} mesa_port_ctle_t;

/** \brief KR state machine structures */
typedef struct {
    mesa_train_state_t       current_state;
    mesa_ber_stage_t         ber_training_stage;
    mesa_kr_tap_t            current_tap;
    mesa_bool_t              signal_detect;
    mesa_bool_t              training_started;
    mesa_bool_t              remote_rx_ready;
    mesa_bool_t              local_rx_ready;
    mesa_bool_t              dme_viol_handled;
    mesa_bool_t              dme_viol;
    mesa_bool_t              ber_busy;
    mesa_bool_t              tap_max_reached;
    mesa_bool_t              receiver_ready_sent;
    mesa_bool_t              kr_mw_done;
    mesa_bool_t              ignore_fail;
    mesa_port_speed_t        next_parallel_spd;
    uint16_t                 lp_tap_max_cnt[3];
    uint16_t                 lp_tap_end_cnt[3];
    uint32_t                 tap_idx;
    uint16_t                 ber_cnt[3][64];
    uint16_t                 eye_height[3][64];
    uint16_t                 decr_cnt;
    uint16_t                 ber_coef_frm;
    uint16_t                 ber_status_frm;
    mesa_bool_t              test_mode;
    mesa_bool_t              test_repeat;
    mesa_kr_status_results_t tr_res;
} mesa_port_kr_state_t CAP(PORT_KR_IRQ);

mesa_rc mesa_port_kr_state_get(const mesa_inst_t inst,
                               const mesa_port_no_t port_no,
                               mesa_port_kr_state_t *const state)
    CAP(PORT_KR_IRQ);


// KR FEC structure */
typedef struct {
    mesa_bool_t r_fec;                   /**< Enable/Disable Clause 74 R-FEC              */
    mesa_bool_t rs_fec CAP(PORT_KR_IRQ); /**< Enable/Disable Clause 108 RS-FEC (25G only) */
} mesa_port_kr_fec_t CAP(PORT_KR);

// KR eye info
typedef struct {
    uint32_t height;
} mesa_port_kr_eye_dim_t CAP(PORT_KR_IRQ);

// Get KR FEC
// inst    [IN]  Target instance reference.
// port_no [IN]  Port number.
// conf    [IN]  Configuration structure.
mesa_rc mesa_port_kr_fec_get(const mesa_inst_t inst,
                             const mesa_port_no_t port_no,
                             mesa_port_kr_fec_t *const conf)
    CAP(PORT_KR);

// Set KR FEC
// inst    [IN]  Target instance reference.
// port_no [IN]  Port number.
// conf    [IN]  Configuration structure.
mesa_rc mesa_port_kr_fec_set(const mesa_inst_t inst,
                             const mesa_port_no_t port_no,
                             const mesa_port_kr_fec_t *const conf)
    CAP(PORT_KR);

// Apply KR interrupts
// port_no [IN]  Port number.
// irq    [IN]  interrupt id.
mesa_rc mesa_port_kr_irq_apply(const mesa_inst_t inst,
                               const mesa_port_no_t port_no,
                               const uint32_t *const irq_vec)
    CAP(PORT_KR_IRQ);

// Get and clear KR interrupts
// port_no [IN]  Port number.
// irq    [IN]  interrupt id.
mesa_rc mesa_port_kr_irq_get(const mesa_inst_t inst,
                             const mesa_port_no_t port_no,
                             uint32_t *const irq_vec)
    CAP(PORT_KR_IRQ);

/**
 * \brief Enable / Disable KR IRQs
 *
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param enable  [OUT] enable/disable
 *
 * \return Return code.
 **/
mesa_rc mesa_port_kr_event_enable(const mesa_inst_t inst,
                                  const mesa_port_no_t port_no,
                                  mesa_bool_t enable)
    CAP(PORT_KR_IRQ);

// Get current KR interrupt status across all ports
// mask    [OUT]  A mask with one bit for each port.

mesa_rc mesa_port_kr_irq_activity(mesa_inst_t inst,
                                  uint32_t *const mask)
    CAP(PORT_KR_IRQ);

/**
 * \brief Get and clear KR interrupts
 *
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param eye     [OUT] The height of the eye.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_kr_eye_get(mesa_inst_t inst,
                             const mesa_port_no_t port_no,
                             mesa_port_kr_eye_dim_t *const eye)
    CAP(PORT_KR_IRQ);

/**
 * \brief Start CTLE adjustment
 *
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_kr_ctle_adjust(mesa_inst_t inst,
                                 const mesa_port_no_t port_no)
    CAP(PORT_KR_IRQ);

/**
 * \brief Get CTLE config
 *
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param ctle    [OUT] CTLE values.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_kr_ctle_get(mesa_inst_t inst,
                              const mesa_port_no_t port_no, mesa_port_ctle_t *const ctle)
    CAP(PORT_KR_IRQ);



/******************************************************************************/
/* 10G/25G KR Backplane Ethernet - End                                        */
/******************************************************************************/

// Port loopback
typedef enum
{
    MESA_PORT_LB_DISABLED, // Loopback disabled
    MESA_PORT_LB_NEAR_END, // Near-end loopback
    MESA_PORT_LB_FAR_END,  // Far-end loopback
    MESA_PORT_LB_FACILITY, // Facility loopback
    MESA_PORT_LB_EQUIPMENT // Equipment loopback
} mesa_port_lb_t;

// Port test configuration structure
typedef struct
{
    mesa_port_lb_t loopback; // Loopback type
} mesa_port_test_conf_t;

// Get port test configuration.
// port_no [IN]  Port number.
// conf [OUT]    Port test configuration.
mesa_rc mesa_port_test_conf_get(const mesa_inst_t      inst,
                                const mesa_port_no_t   port_no,
                                mesa_port_test_conf_t  *const conf);

// Set port test configuration.
// port_no [IN]  Port number.
// conf [IN]     Port test configuration.
mesa_rc mesa_port_test_conf_set(const mesa_inst_t            inst,
                                const mesa_port_no_t         port_no,
                                const mesa_port_test_conf_t  *const conf);

// Serdes Tx Equalizer taps
typedef enum
{
    MESA_SERDES_PRE_CURSOR,
    MESA_SERDES_MAIN_CURSOR,
    MESA_SERDES_POST_CURSOR,
} mesa_port_serdes_tap_enum_t;

//  Function pointer for API callout.
//  This function will typically be implemented in MEBA were the board specifics are known.
//  The purpose is to get the tap value for a specific port/speed/tap.
//  port_no [IN]    Port number.
//  speed   [IN]    Port speed.
//  tap     [IN]    Pre/main/post tap.
//  value   [OUT]   The register value to be written.
typedef mesa_rc (*mesa_port_serdes_tap_get_t)(const mesa_inst_t                 inst,
                                              const mesa_port_no_t              port_no,
                                              const mesa_port_speed_t           speed,
                                              const mesa_port_serdes_tap_enum_t tap,
                                              uint32_t                          *const value);

/** \brief Serdes debug parameters */
typedef enum
{
    MESA_SERDES_DFE_PRM,  /**< DFE prms. in this order : h1,h2,h3,h4,h5,dlev */
    MESA_SERDES_CTLE_PRM, /**< CTLE prms. in this order: r,c,vga */
    MESA_SERDES_TXEQ_PRM, /**< TxEQ prms. in this order: tap_dly, tap_adv, amplitude */
} mesa_serdes_debug_type_t;

/** \brief Serdes debug configuration structure */
typedef struct
{
    mesa_serdes_debug_type_t debug_type;
    uint32_t                 serdes_prm[10]; /**< Depends on debug_type */
} mesa_port_serdes_debug_t;

/**
 * \brief Used for Serdes debugging.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Serdes test configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_serdes_debug_set(const mesa_inst_t              inst,
                                   const mesa_port_no_t           port_no,
                                   const mesa_port_serdes_debug_t *const conf);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_PORT_
