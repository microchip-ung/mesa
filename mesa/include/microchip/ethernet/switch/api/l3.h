// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef MICROCHIP_ETHERNET_SWITCH_API_L3
#define MICROCHIP_ETHERNET_SWITCH_API_L3

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h> // ALL INCLUDE ABOVE THIS LINE

// Virtual router identifier
typedef uint8_t mesa_l3_vrid_t;

// MAC addressing mode for routing legs
typedef enum {
    // The addressing mode has still not been configured
    MESA_ROUTING_RLEG_MAC_MODE_INVALID = 0,

    // One common MAC address is used for all legs
    MESA_ROUTING_RLEG_MAC_MODE_SINGLE = 1,
} mesa_l3_rleg_common_mode_t CAP(L3);

// Common configurations for all routing legs
typedef struct {
    // Common rleg-mode for all routing legs.
    mesa_l3_rleg_common_mode_t rleg_mode;

    // Base mac address used to derive addresses for all routing legs.
    mesa_mac_t base_address;

    // Globally enable/disable unicast routing.
    mesa_bool_t routing_enable;

    // Globally enable/disable multicast routing.
    mesa_bool_t mc_routing_enable;
} mesa_l3_common_conf_t CAP(L3);

// Router leg control structure
typedef struct {
    // Enable router leg ID
    mesa_bool_t rleg_enable;

    // Router leg ID
    mesa_l3_rleg_id_t rleg_id;

    // Enable IPv4 unicast routing
    mesa_bool_t ipv4_unicast_enable;

    // Enable IPv6 unicast routing
    mesa_bool_t ipv6_unicast_enable;

    // Enable IPv4 multicast routing
    mesa_bool_t ipv4_multicast_enable;

    // Enable IPv6 multicast routing
    mesa_bool_t ipv6_multicast_enable;

    // Enable IPv4 icmp redirect
    mesa_bool_t ipv4_icmp_redirect_enable;

    // Enable IPv6 icmp redirect
    mesa_bool_t ipv6_icmp_redirect_enable;

    // Vlan for which the router leg is instantiated
    mesa_vid_t vlan;

    // Enable/disable VRRP for a given router leg.
    //
    // The hardware has support for enabling 0-2 VRID's for a given router leg.
    // This is activated by configured vrid0_enable and vrid1_enable. The actual
    // VRID the route is assigned to is configured in vrid0/vrid1.
    mesa_bool_t vrid0_enable;

    // The VRID value assigned to this router leg.
    mesa_l3_vrid_t vrid0;

    // Enable/disable vrid1 for this router leg.
    mesa_bool_t vrid1_enable;

    // The VRID value assigned to this router leg.
    mesa_l3_vrid_t vrid1;

    // Enable/disable non-default multicast TTL limit for this router leg.
    mesa_bool_t mc_ttl_limit_enable;

    // The TTL in the frame must be equal or higher than this value (must be >=
    // 2).
    uint32_t mc_ttl_limit;

} mesa_l3_rleg_conf_t CAP(L3);

// Neighbour type
typedef enum {
    // Invalid entry.
    MESA_L3_NEIGHBOUR_TYPE_INVALID = 0,

    // IPv4 Neighbour entry (ARP).
    MESA_L3_NEIGHBOUR_TYPE_ARP = 1,

    // IPv6 Neighbour entry (NDP).
    MESA_L3_NEIGHBOUR_TYPE_NDP = 2,
} mesa_l3_neighbour_type_t CAP(L3);

// Neighbour entry
typedef struct {
    // MAC address of destination
    mesa_mac_t dmac;

    // VLAN of destination
    mesa_vid_t vlan;

    // IP address of destination
    mesa_ip_addr_t dip;
} mesa_l3_neighbour_t CAP(L3);

// Flush all L3 configurations
mesa_rc mesa_l3_flush(const mesa_inst_t inst) CAP(L3);

// Get common router configuration.
// conf [OUT]    Common routing configurations.
mesa_rc mesa_l3_common_get(const mesa_inst_t inst, mesa_l3_common_conf_t *const conf) CAP(L3);

// Set common router configuration.
// conf [OUT]    Common routing configurations.
mesa_rc mesa_l3_common_set(const mesa_inst_t inst, const mesa_l3_common_conf_t *const conf) CAP(L3);

// Get a specific configured router leg
// vid  [IN]     VLAN ID of the router leg to get
// conf [OUT]    Output buffer where the configuration is written
mesa_rc mesa_l3_rleg_get_specific(const mesa_inst_t inst, mesa_vid_t vid, mesa_l3_rleg_conf_t *conf)
    CAP(L3);

// Add a router leg on the given VLAN
// conf [IN] Routing leg configuration.
mesa_rc mesa_l3_rleg_add(const mesa_inst_t inst, const mesa_l3_rleg_conf_t *const conf) CAP(L3);

// Update an existing router leg.
// Will fail if an existing router leg with the same VLAN does not exists.
// conf [IN] Routing leg configuration.
mesa_rc mesa_l3_rleg_update(const mesa_inst_t inst, const mesa_l3_rleg_conf_t *const conf) CAP(L3);

// Delete a router leg associated with VLAN
// vlan [IN]     VLAN to delete router leg from
mesa_rc mesa_l3_rleg_del(const mesa_inst_t inst, const mesa_vid_t vlan) CAP(L3);

// Add an entry to the routing table
// entry [IN]    Route to add
mesa_rc mesa_l3_route_add(const mesa_inst_t inst, const mesa_routing_entry_t *const entry) CAP(L3);

// Add a list of routes
// cnt  [IN]      Length of 'entry'
// entry [IN]     List of routes to add
// rt_added [OUT] Number of routes added
mesa_rc mesa_l3_route_bulk_add(const mesa_inst_t           inst,
                               const uint32_t              cnt,
                               const mesa_routing_entry_t *entry,
                               uint32_t *const             rt_added) CAP(L3);

// Delete an entry from the routing table
// entry [IN]    Entry to delete.
mesa_rc mesa_l3_route_del(const mesa_inst_t inst, const mesa_routing_entry_t *const entry) CAP(L3);

// Delete a list of routes
// cnt  [IN]        Length of 'entry'
// entry [IN]       List of routes to add
// rt_deleted [OUT] Number of routes deleted
mesa_rc mesa_l3_route_bulk_del(const mesa_inst_t           inst,
                               const uint32_t              cnt,
                               const mesa_routing_entry_t *entry,
                               uint32_t *const             rt_deleted) CAP(L3);

// Add a new entry to the neighbour cache.
// entry [IN]    Entry to add.
mesa_rc mesa_l3_neighbour_add(const mesa_inst_t inst, const mesa_l3_neighbour_t *const entry)
    CAP(L3);

// Delete an entry from the neighbour  cache.
// entry [IN]    Entry to delete.
mesa_rc mesa_l3_neighbour_del(const mesa_inst_t inst, const mesa_l3_neighbour_t *const entry)
    CAP(L3);

// Add an multicast entry to the routing table
// entry [IN]    MC entry to add
mesa_rc mesa_l3_mc_route_add(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry)
    CAP(L3);

// Delete an entry from the multicast routing table
// entry [IN]    MC entry to delete.
mesa_rc mesa_l3_mc_route_del(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry)
    CAP(L3);

// Add an router leg to an existing routing entry
// entry [IN]       MC route entry
// dest_rleg [IN]   Destination router leg to add to route
mesa_rc mesa_l3_mc_route_rleg_add(const mesa_inst_t                    inst,
                                  const mesa_routing_mc_entry_t *const entry,
                                  const mesa_vid_t                     dest_rleg) CAP(L3);

// Remove an router leg from an routing entry
// entry [IN]      MC route entry
// dest_rleg [IN]  Destination router leg to remove from route
mesa_rc mesa_l3_mc_route_rleg_del(const mesa_inst_t                    inst,
                                  const mesa_routing_mc_entry_t *const entry,
                                  const mesa_vid_t                     dest_rleg) CAP(L3);

// Get activity status on a mc route, i.e. if it has been used by mc transmitter.
// Clear on read.
// entry [IN]     MC entry to check for activity
// active [OUT]   True (active) / False (not active) since last read.
mesa_rc mesa_l3_mc_route_active_get(const mesa_inst_t                    inst,
                                    const mesa_routing_mc_entry_t *const entry,
                                    mesa_bool_t *const                   active) CAP(L3);

// Reset all router leg statistics counters
mesa_rc mesa_l3_counters_reset(const mesa_inst_t inst) CAP(L3);

// Get routing system counters
// counters [OUT] Counters
mesa_rc mesa_l3_counters_system_get(const mesa_inst_t inst, mesa_l3_counters_t *const counters)
    CAP(L3);

// Get routing legs counters
// vlan [IN]      Routing leg
// counters [OUT] Counters
mesa_rc mesa_l3_counters_rleg_get(const mesa_inst_t         inst,
                                  const mesa_vid_t          vlan,
                                  mesa_l3_counters_t *const counters) CAP(L3);

// Clear routing legs counters
// vlan [IN]      Routing leg
mesa_rc mesa_l3_counters_rleg_clear(const mesa_inst_t inst, const mesa_vid_t vlan) CAP(L3);

#include <microchip/ethernet/hdr_end.h>
#endif // MICROCHIP_ETHERNET_SWITCH_API_L3
