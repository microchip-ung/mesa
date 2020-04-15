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

#ifndef _MSCC_ETHERNET_SWITCH_API_L3_
#define _MSCC_ETHERNET_SWITCH_API_L3_

#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/** \brief Virtual router identifier */
typedef uint8_t  mesa_l3_vrid_t;

/** \brief MAC addressing mode for routing legs */
typedef enum
{
    /** The addressing mode has still not been configured */
    MESA_ROUTING_RLEG_MAC_MODE_INVALID = 0,

    /** One common MAC address is used for all legs */
    MESA_ROUTING_RLEG_MAC_MODE_SINGLE = 1,
} mesa_l3_rleg_common_mode_t CAP(L3);

/** \brief Common configurations for all routing legs */
typedef struct
{
    /** Common rleg-mode for all routing legs. */
    mesa_l3_rleg_common_mode_t rleg_mode;

    /** Base mac address used to derive addresses for all routing legs. */
    mesa_mac_t                 base_address;

    /** Globally enable/disable unicast routing. */
    mesa_bool_t                routing_enable;

    /** Globally enable/disable multicast routing. */
    mesa_bool_t                mc_routing_enable;
} mesa_l3_common_conf_t CAP(L3);

/** \brief Router leg control structure */
typedef struct
{
    /** Enable IPv4 unicast routing */
    mesa_bool_t ipv4_unicast_enable;

    /** Enable IPv6 unicast routing */
    mesa_bool_t ipv6_unicast_enable;

    /** Enable IPv4 multicast routing */
    mesa_bool_t ipv4_multicast_enable;

    /** Enable IPv6 multicast routing */
    mesa_bool_t ipv6_multicast_enable;

    /** Enable IPv4 icmp redirect */
    mesa_bool_t ipv4_icmp_redirect_enable;

    /** Enable IPv6 icmp redirect */
    mesa_bool_t ipv6_icmp_redirect_enable;

    /** Vlan for which the router leg is instantiated */
    mesa_vid_t          vlan;

    /** Enable/disable VRRP for a given router leg.
     *
     * The hardware has support for enabling 0-2 VRID's for a given router leg.
     * This is activated by configured vrid0_enable and vrid1_enable. The actual
     * VRID the route is assigned to is configured in vrid0/vrid1.
     *
     * JR1-NOTE: When enabling vrrp for JR1-revb, the hardware will consider all
     * destination mac addresses matching 00-00-5E-00-XX-{VRID} as VRRP address.
     * For versions earlier than rev-B VRRP is only supported for IPv4
     * (00-00-5E-00-01-{VRID}).
     */
    mesa_bool_t         vrid0_enable;

    /** The VRID value assigned to this router leg. */
    mesa_l3_vrid_t      vrid0;

    /** Enable/disable vrid1 for this router leg. */
    mesa_bool_t         vrid1_enable;

    /** The VRID value assigned to this router leg. */
    mesa_l3_vrid_t      vrid1;

    /** Enable/disable non-default multicast TTL limit for this router leg. */
    mesa_bool_t         mc_ttl_limit_enable;

    /** The TTL in the frame must be equal or higher than this value (must be >= 2). */
    uint32_t            mc_ttl_limit;

} mesa_l3_rleg_conf_t CAP(L3);

/** \brief Neighbour type */
typedef enum
{
    /** Invalid entry. */
    MESA_L3_NEIGHBOUR_TYPE_INVALID = 0,

    /** IPv4 Neighbour entry (ARP). */
    MESA_L3_NEIGHBOUR_TYPE_ARP = 1,

    /** IPv6 Neighbour entry (NDP). */
    MESA_L3_NEIGHBOUR_TYPE_NDP = 2,
} mesa_l3_neighbour_type_t CAP(L3);

/** \brief Neighbour entry */
typedef struct
{
    /** MAC address of destination */
    mesa_mac_t         dmac;

    /** VLAN of destination */
    mesa_vid_t         vlan;

    /** IP address of destination */
    mesa_ip_addr_t     dip;
} mesa_l3_neighbour_t CAP(L3);

/**
 * \brief Flush all L3 configurations
 *
 * \param inst [IN]     Target instance reference.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_flush(const mesa_inst_t inst)
    CAP(L3);

/**
 * \brief Get common router configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param conf [OUT]    Common routing configurations.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_common_get(const mesa_inst_t     inst,
                           mesa_l3_common_conf_t *const conf)
    CAP(L3);

/**
 * \brief Set common router configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param conf [OUT]    Common routing configurations.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_common_set(const mesa_inst_t           inst,
                           const mesa_l3_common_conf_t *const conf)
    CAP(L3);

/**
 * \brief Get a specific configured router leg
 *
 * \param inst [IN]     Target instance reference.
 * \param vid  [IN]     VLAN ID of the router leg to get
 * \param conf [OUT]    Output buffer where the configuration is written
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_rleg_get_specific(const mesa_inst_t   inst,
                                  mesa_vid_t          vid,
                                  mesa_l3_rleg_conf_t *conf)
    CAP(L3);

/**
 * \brief Add a router leg on the given VLAN
 *
 * \param inst [IN] Target instance reference.
 * \param conf [IN] Routing leg configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_rleg_add(const mesa_inst_t          inst,
                         const mesa_l3_rleg_conf_t *const conf)
    CAP(L3);

/**
 * \brief Update an existing router leg.
 *
 * Will fail if an existing router leg with the same VLAN does not exists.
 *
 * \param inst [IN] Target instance reference.
 * \param conf [IN] Routing leg configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_rleg_update(const mesa_inst_t         inst,
                            const mesa_l3_rleg_conf_t *const conf)
    CAP(L3);

/**
 * \brief Delete a router leg associated with VLAN
 *
 * \param inst [IN]     Target instance reference.
 * \param vlan [IN]     VLAN to delete router leg from
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_rleg_del(const mesa_inst_t inst,
                         const mesa_vid_t  vlan)
    CAP(L3);

/**
 * \brief Add an entry to the routing table
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    Route to add
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_route_add(const mesa_inst_t          inst,
                          const mesa_routing_entry_t *const entry)
    CAP(L3);

/**
 * \brief Add a list of routes
 *
 * \param inst [IN]      Target instance reference.
 * \param cnt  [IN]      Length of 'entry'
 * \param entry [IN]     List of routes to add
 * \param rt_added [OUT] Number of routes added
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_route_bulk_add(const mesa_inst_t             inst,
                               const uint32_t                cnt,
                               const mesa_routing_entry_t    *entry,
                               uint32_t                      *const rt_added)
    CAP(L3);

/**
 * \brief Delete an entry from the routing table
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    Entry to delete.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_route_del(const mesa_inst_t          inst,
                          const mesa_routing_entry_t *const entry)
    CAP(L3);

/**
 * \brief Deletes a list of routes
 *
 * \param inst [IN]        Target instance reference.
 * \param cnt  [IN]        Length of 'entry'
 * \param entry [IN]       List of routes to add
 * \param rt_deleted [OUT] Number of routes deleted
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_route_bulk_del(const mesa_inst_t             inst,
                               const uint32_t                cnt,
                               const mesa_routing_entry_t    *entry,
                               uint32_t                      *const rt_deleted)
    CAP(L3);

/**
 * \brief Add a new entry to the neighbour cache.
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    Entry to add.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_neighbour_add(const mesa_inst_t         inst,
                              const mesa_l3_neighbour_t *const entry)
    CAP(L3);

/**
 * \brief Delete an entry from the neighbour  cache.
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    Entry to delete.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_neighbour_del(const mesa_inst_t         inst,
                              const mesa_l3_neighbour_t *const entry)
    CAP(L3);

/**
 * \brief Add an multicast entry to the routing table
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    MC entry to add
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_mc_route_add(const mesa_inst_t              inst,
                             const mesa_routing_mc_entry_t  *const entry)
    CAP(L3);

/**
 * \brief Delete an entry from the multicast routing table
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    MC entry to delete.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_mc_route_del(const mesa_inst_t              inst,
                             const mesa_routing_mc_entry_t  *const entry)
     CAP(L3);

/**
 * \brief Add an router leg to an existing routing entry
 *
 * \param inst [IN]        Target instance reference.
 * \param entry [IN]       MC route entry
 * \param dest_rleg [IN]   Destination router leg to add to route
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_mc_route_rleg_add(const mesa_inst_t              inst,
                                  const mesa_routing_mc_entry_t  *const entry,
                                  const mesa_vid_t               dest_rleg)
    CAP(L3);

/**
 * \brief Remove an router leg from an routing entry
 *
 * \param inst [IN]       Target instance reference.
 * \param entry [IN]      MC route entry
 * \param dest_rleg [IN]  Destination router leg to remove from route
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_mc_route_rleg_del(const mesa_inst_t              inst,
                                  const mesa_routing_mc_entry_t  *const entry,
                                  const mesa_vid_t               dest_rleg)
    CAP(L3);

/**
 * \brief Get activity status on a mc route, i.e. if it has been used by mc transmitter.
 *  Clear on read.
 *
 * \param inst [IN]      Target instance reference.
 * \param entry [IN]     MC entry to check for activity
 * \param active [OUT]   True (active) / False (not active) since last read.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_mc_route_active_get(const mesa_inst_t              inst,
                                    const mesa_routing_mc_entry_t  *const entry,
                                    mesa_bool_t *const active)
    CAP(L3);

/**
 * \brief Reset all routing leg statistics counters
 *
 * \param inst [IN]     Target instance reference.
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_counters_reset(const mesa_inst_t inst)
    CAP(L3);

/**
 * \brief Get routing system counters
 *
 * \param inst [IN]      Target instance reference.
 * \param counters [OUT] Counters
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_counters_system_get(const mesa_inst_t  inst,
                                    mesa_l3_counters_t *const counters)
    CAP(L3);

/**
 * \brief Get routing legs counters
 *
 * \param inst [IN]      Target instance reference.
 * \param vlan [IN]      Routing leg
 * \param counters [OUT] Counters
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_counters_rleg_get(const mesa_inst_t  inst,
                                  const mesa_vid_t   vlan,
                                  mesa_l3_counters_t *const counters)
    CAP(L3);

/**
 * \brief Clear routing legs counters
 *
 * \param inst [IN]      Target instance reference.
 * \param vlan [IN]      Routing leg
 *
 * \return Return code.
 **/
mesa_rc mesa_l3_counters_rleg_clear(const mesa_inst_t inst,
                                    const mesa_vid_t  vlan)
    CAP(L3);

#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_L3_
