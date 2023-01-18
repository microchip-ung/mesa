// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief L3 routing API
 * \details This header file describes L3 IPv4/IPv6 hardware assisted routing
 * functions.
 */

#ifndef _VTSS_L3_API_H_
#define _VTSS_L3_API_H_

#include <vtss/api/types.h>

#if defined(VTSS_FEATURE_LAYER3)

/** \page layer3 Layer 3
 *
 * The Layer 3 functionality is build around some global configuration and three
 * tables:
 *
 * IP unicast: router-legs (RLEG), longest-prefix-match (LPM) and
 * neighbour-table (IP UC ARP).
 *
 * IP multicast: router-legs (RLEG), longest-prefix-match (LPM) and
 * Router Leg bitmask table.
 *
 * Following is the purpose of these configurations entities.
 *
 *
 * Configuration entities
 * ----------------------
 *
 * Global configuration: Required to enable routing and to configure the MAC
 * addressing schema to use for the router legs.
 *
 * Router legs: The purpose of L3 routing is to forward IP frames from one L3
 * interface to another. The router legs represents these L3 interfaces. A
 * router leg is associated to a L2 VLAN, it has a MAC-address and a set of
 * other attributes to enable/disable IPv4/IPv6 routing and VRRP settings. If a
 * IP frame is received on a VLAN which has an associated router leg, and the
 * destination MAC of the frame matches the MAC address of the router leg, then
 * the frame is candidate for being routed.
 *
 * NOTE: The router leg table should be synchronized with the interface table in
 * the operating systems IP stack. When a L3 interface is added in the operating
 * system, a corresponding router leg should be created. When an IP address is
 * assigned to a given L3 interface in the IP stack, then the corresponding
 * interface route should be installed in the LPM table.
 *
 * Longest prefix match: This is where the actual routing takes place, if a IP
 * frame qualifies for routing then the destination IP address is matched
 * against the LPM table. The best match (the longest prefix match) in the LPM
 * table is used to route the frame. If no match is found in the LPM table, then
 * the frame is forwarded to the CPU. The LPM table should include network
 * routes, host routes and interface routes. An interface route is a route
 * representing the configured IP range of the interface, and with the
 * destination configured to zero.
 *
 * NOTE: An IP UC LPM entry can only be routed in HW if the destination of the route
 * is installed in the neighbour table. If this is not the case the frame will
 * be forwarded to the CPU, which should perform the ARP/NDP resolution route
 * the packet in SW and install the neighbour in HW for future use.
 *
 * IP UC Neighbour table: This table is used to map IP address to (MAC addresses,
 * VLAN). When a packet is being routed in the LPM table, the output is a
 * "next-hop" IP address, this "next-hop" IP address must be translated to a
 * MAC-address and a VLAN before it can be L2 forwarded. If a LPM entry does not
 * have a corresponding neighbour entry, then the packet will be forwarded to
 * the CPU.
 * The neighbour table should be synchronized with the ARP/NDP table of the
 * operating systems IP stack.
 *
 * IP MC Rleg bitmask table: This table consists of destination router legs entries
 * for a given MC group in the LPM table, i.e. each group can have a unique number of
 * destination rlegs.  If 2 (or more) groups have identical destinations they will share
 * the same rleg bitmask table entry.
 *
 * Mode of operation
 * -----------------
 * IP Unicast:
 *
 * When a frame is being routed and the best match in the LPM table is a
 * interface route, then the packet will be forwarded to the CPU. The CPU should
 * now start the ARP/NDP protocols in order to figure out what the MAC address
 * is of the destination host. The address resolution has completed the frame
 * can be routed. In order to enable hardware routing for directly connected
 * routes, the derived destination host must be installed as a host route in the
 * LPM table, and an associated neighbour entry should be installed.
 *
 * When a new network route is installed, the MAC address of the next hop route
 * may not be known in advance. If this is the case the first hit on that route
 * will also cause the frame to be forwarded to the CPU, and the CPU may
 * complete the neighbour discovery and install a neighbour entry. After the
 * neighbour entry has been installed the routing will be performed in HW.
 *
 * IP Multicast:
 *
 * To enable MC routing a MC group must be installed into the LPM table without
 * a rleg destination, i.e. initially frames to this group will get dropped.
 * The SIP can be either specific address or any.
 * Hereafter the receivers will join this group and enable forwarding to their RLEG/VLAN and
 * when the receiver leaves the group then the rleg is removed. The receiver can enforce
 * only to listen to a group from specific source.  The sender activity status can be
 * monitored by the router application and the group removed in case of an idle sender
 *
 */

#if defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_SERVAL_T)

// Serval-T has 6 super VCAP blocks, each with 64 rows of 16 entries. This means
// that a single block will give us 64*16 entries - which is the minimum
// meaningful amount. 6*1024 is max.
#define VTSS_RLEG_CNT    31   /**< Length of RLEG table */
#define VTSS_LPM_CNT     1024 /**< Length of LPM table */
#define VTSS_ARP_CNT     256  /**< Length of ARP table */
#define VTSS_LPM_MC_CNT  512  /**< Length of LPM table for multicast entries */
#define VTSS_MC_TBL_CNT  256  /**< Length of MC RLEG bit-mask table */
#else
// Jaguar-2 has 8 super VCAP blocks, each with 256 rows of 16 entries. This means
// that a single block will give us 256*16 = 4096 entries.
#define VTSS_RLEG_CNT    127  /**< Length of RLEG table */
#define VTSS_LPM_CNT     4096 /**< Length of LPM table for unicast entries */
#define VTSS_ARP_CNT     2048 /**< Length of ARP table */
#define VTSS_LPM_MC_CNT  2048 /**< Length of LPM table for multicast entries */
#define VTSS_MC_TBL_CNT  1024 /**< Length of MC RLEG mask table */

// A IPv4 unicast address occupies 1 entry in the LPM VCAP while
// IPv6 unicast address occupies 4 entries.
// I.e. the max number of IP UC entries:
// IPv4 UC = VTSS_LPM_CNT
// IPv6 UC = VTSS_LPM_CNT/4

// A IPv4 multicast address occupies 2 entries in the LPM VCAP while
// IPv6 multicast address occupies 8 entries.
// I.e. the max number of IP MC entries:
// IPv4 MC = VTSS_LPM_MC_CNT
// IPv6 MC = VTSS_LPM_MC_CNT/4

#endif /* VTSS_ARCH_SERVAL_T */
#endif /* VTSS_ARCH_JAGUAR_2 */


#if defined(VTSS_ARCH_SPARX5)

// SparX-5 has 10 super VCAP blocks, each with 256 rows of 12 entries (52 bits each).
// This means that a single block will give us 256*12 = 3072 entries.
#define VTSS_RLEG_CNT    127  /**< Length of RLEG table */
#define VTSS_LPM_CNT     3072 /**< Length of LPM table */
#define VTSS_ARP_CNT     2048 /**< Length of ARP table */
#define VTSS_LPM_MC_CNT  1536 /**< Length of LPM table for multicast entries */
#define VTSS_MC_TBL_CNT  2048 /**< Length of MC RLEG bit-mask table */

// A IPv4 unicast address occupies 1 entry in the LPM VCAP while
// IPv6 unicast address occupies 2 entries.
// I.e. the max number of IP UC entries:
// IPv4 UC = VTSS_LPM_CNT
// IPv6 UC = VTSS_LPM_CNT/4

// A IPv4 multicast address occupies 2 entries in the LPM VCAP while
// IPv6 multicast address occupies 5 entries. As each row consists of 12 entries
// there is only room for 2 IPv6 MC addresses (10) per row.
// I.e. the max number of IP MC entries:
// IPv4 MC = VTSS_LPM_MC_CNT
// IPv6 MC = VTSS_LPM_MC_CNT/3
//
// Currently the IP MC supports up to 128 egress router legs.

#endif /* VTSS_ARCH_SPARX5 */



#ifdef __cplusplus
extern "C" {
#endif

/** \brief Virtual router identifier */
typedef u8  vtss_l3_vrid_t;

/** \brief MAC addressing mode for routing legs */
typedef enum
{
    /** The addressing mode has still not been configured */
    VTSS_ROUTING_RLEG_MAC_MODE_INVALID = 0,

    /** One common MAC address is used for all legs */
    VTSS_ROUTING_RLEG_MAC_MODE_SINGLE = 1,
} vtss_l3_rleg_common_mode_t;

/** \brief Common configurations for all routing legs */
typedef struct
{
    /** Common rleg-mode for all routing legs. */
    vtss_l3_rleg_common_mode_t rleg_mode;

    /** Base mac address used to derive addresses for all routing legs. */
    vtss_mac_t                 base_address;

    /** Globally enable/disable unicast routing. */
    BOOL                       routing_enable;

    /** Globally enable/disable multicast routing. */
    BOOL                       mc_routing_enable;
} vtss_l3_common_conf_t;

/** \brief Router leg control structure */
typedef struct
{
    /** Enable router leg ID */
    BOOL rleg_enable;

    /** Router leg ID */
    vtss_l3_rleg_id_t rleg_id;

    /** Enable IPv4 unicast routing */
    BOOL ipv4_unicast_enable;

    /** Enable IPv6 unicast routing */
    BOOL ipv6_unicast_enable;

    /** Enable IPv4 multicast routing */
    BOOL ipv4_multicast_enable;

    /** Enable IPv6 multicast routing */
    BOOL ipv6_multicast_enable;

    /** Enable IPv4 icmp redirect */
    BOOL ipv4_icmp_redirect_enable;

    /** Enable IPv6 icmp redirect */
    BOOL ipv6_icmp_redirect_enable;

    /** Vlan for which the router leg is instantiated */
    vtss_vid_t          vlan;

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
    BOOL                vrid0_enable;

    /** The VRID value assigned to this router leg. */
    vtss_l3_vrid_t      vrid0;

    /** Enable/disable vrid1 for this router leg. */
    BOOL                vrid1_enable;

    /** The VRID value assigned to this router leg. */
    vtss_l3_vrid_t      vrid1;

    /** Enable/disable non-default multicast TTL limit for this router leg.
     *  Default: Frames with TTL >= 2 are routet. */
    BOOL                mc_ttl_limit_enable;

    /** The TTL in the frame must be equal or higher than this value (must be >= 2). */
    u32                 mc_ttl_limit;

} vtss_l3_rleg_conf_t;

/** \brief Neighbour type */
typedef enum
{
    /** Invalid entry. */
    VTSS_L3_NEIGHBOUR_TYPE_INVALID = 0,

    /** IPv4 Neighbour entry (ARP). */
    VTSS_L3_NEIGHBOUR_TYPE_ARP = 1,

    /** IPv6 Neighbour entry (NDP). */
    VTSS_L3_NEIGHBOUR_TYPE_NDP = 2,
} vtss_l3_neighbour_type_t;

/** \brief Neighbour entry */
typedef struct
{
    /** MAC address of destination */
    vtss_mac_t         dmac;

    /** VLAN of destination */
    vtss_vid_t         vlan;

    /** IP address of destination */
    vtss_ip_addr_t     dip;
} vtss_l3_neighbour_t;

/**
 * \brief Flush all L3 configurations
 *
 * \param inst [IN]     Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_flush(const vtss_inst_t inst);

/**
 * \brief Get common router configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param conf [OUT]    Common routing configurations.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_common_get(const vtss_inst_t      inst,
                           vtss_l3_common_conf_t *const conf);

/**
 * \brief Set common router configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param conf [OUT]    Common routing configurations.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_common_set(const vtss_inst_t            inst,
                           const vtss_l3_common_conf_t *const conf);

/**
 * \brief Get a specific configured router leg
 *
 * \param inst [IN]     Target instance reference.
 * \param vid  [IN]     VLAN ID of the router leg to get
 * \param conf [OUT]    Output buffer where the configuration is written
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_rleg_get_specific(const vtss_inst_t     inst,
                                  vtss_vid_t            vid,
                                  vtss_l3_rleg_conf_t  *conf);

/**
 * \brief Add a router leg on the given VLAN
 *
 * \param inst [IN] Target instance reference.
 * \param conf [IN] Routing leg configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_rleg_add(const vtss_inst_t          inst,
                         const vtss_l3_rleg_conf_t *const conf);

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
vtss_rc vtss_l3_rleg_update(const vtss_inst_t          inst,
                            const vtss_l3_rleg_conf_t *const conf);

/**
 * \brief Delete a router leg associated with VLAN
 *
 * \param inst [IN]     Target instance reference.
 * \param vlan [IN]     VLAN to delete router leg from
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_rleg_del(const vtss_inst_t         inst,
                         const vtss_vid_t          vlan);

/**
 * \brief Add an entry to the routing table
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    Route to add
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_route_add(const vtss_inst_t             inst,
                          const vtss_routing_entry_t    * const entry);

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
vtss_rc vtss_l3_route_bulk_add(const vtss_inst_t             inst,
                               const u32                     cnt,
                               const vtss_routing_entry_t    *entry,
                               u32                           *const rt_added);

/**
 * \brief Delete an entry from the routing table
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    Entry to delete.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_route_del(const vtss_inst_t             inst,
                          const vtss_routing_entry_t    *const entry);

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
vtss_rc vtss_l3_route_bulk_del(const vtss_inst_t             inst,
                               const u32                     cnt,
                               const vtss_routing_entry_t    *entry,
                               u32                           *const rt_deleted);

/**
 * \brief Add a new entry to the neighbour cache.
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    Entry to add.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_neighbour_add(const vtss_inst_t         inst,
                              const vtss_l3_neighbour_t * const entry);

/**
 * \brief Delete an entry from the neighbour  cache.
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    Entry to delete.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_neighbour_del(const vtss_inst_t         inst,
                              const vtss_l3_neighbour_t * const entry);

/**
 * \brief Add an multicast entry to the routing table
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    MC entry to add
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_mc_route_add(const vtss_inst_t              inst,
                             const vtss_routing_mc_entry_t  *const entry);

/**
 * \brief Delete an entry from the multicast routing table
 *
 * \param inst [IN]     Target instance reference.
 * \param entry [IN]    MC entry to delete.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_mc_route_del(const vtss_inst_t              inst,
                             const vtss_routing_mc_entry_t  *const entry);

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
vtss_rc vtss_l3_mc_route_active_get(const vtss_inst_t              inst,
                                    const vtss_routing_mc_entry_t  *const entry,
                                    BOOL *const active);

/**
 * \brief Add an router leg to an existing routing entry
 *
 * \param inst [IN]        Target instance reference.
 * \param entry [IN]       MC route entry
 * \param dest_rleg [IN]   Destination router leg to add to route
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_mc_route_rleg_add(const vtss_inst_t              inst,
                                  const vtss_routing_mc_entry_t  *const entry,
                                  const vtss_vid_t               dest_rleg);

/**
 * \brief Remove an router leg from an routing entry
 *
 * \param inst [IN]       Target instance reference.
 * \param entry [IN]      MC route entry
 * \param dest_rleg [IN]  Destination router leg to remove from route
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_mc_route_rleg_del(const vtss_inst_t              inst,
                                  const vtss_routing_mc_entry_t  *const entry,
                                  const vtss_vid_t               dest_rleg);

/**
 * \brief Reset all routing leg statistics counters
 *
 * \param inst [IN]     Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_counters_reset(const vtss_inst_t inst);

/**
 * \brief Get routing system counters
 *
 * \param inst [IN]      Target instance reference.
 * \param counters [OUT] Counters
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_counters_system_get(const vtss_inst_t  inst,
                                    vtss_l3_counters_t * const counters);

/**
 * \brief Get routing legs counters
 *
 * \param inst [IN]      Target instance reference.
 * \param vlan [IN]      Routing leg
 * \param counters [OUT] Counters
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_counters_rleg_get(const vtss_inst_t       inst,
                                  const vtss_vid_t        vlan,
                                  vtss_l3_counters_t      * const counters);

/**
 * \brief Clear routing legs counters
 *
 * \param inst [IN]      Target instance reference.
 * \param vlan [IN]      Routing leg
 *
 * \return Return code.
 **/
vtss_rc vtss_l3_counters_rleg_clear(const vtss_inst_t       inst,
                                    const vtss_vid_t        vlan);


#ifdef __cplusplus
}
#endif
#endif /* VTSS_FEATURE_LAYER3 */
#endif /* _VTSS_L3_API_H_ */
