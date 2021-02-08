// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/switch/api/l3.h>

mscc_rc l3_check_capabilities(const mesa_inst_t inst) {
    // snippet_begin caps
    if (mesa_capability(inst, MESA_CAP_L3) != 1) {
        return MESA_RC_ERROR;
    }
    // snippet_end

    return MESA_RC_OK;
}

mscc_rc l3_vlan_config(const mesa_inst_t inst) {
    // TODO
}

mscc_rc l3_basic_config(const mesa_inst_t inst) {
    // snippet_begin l3_global
    // Enable routing and use the 00:00:00:10:00:00 mac-address on all router
    // legs.
    mesa_l3_common_conf_t cconf = {
        .routing_enable = 1,
        .rleg_mode      = MESA_ROUTING_RLEG_MAC_MODE_SINGLE,
        .base_address   = {0x0, 0x0, 0x0, 0x10, 0x0, 0x0},
    };
    RC(mesa_l3_common_set(inst, &cconf));

    // snippet_endbegin add_rleg
    // Add 2 router legs on VLAN 10 and 20, enable IPv4 routing but no IPv6.
    mesa_l3_rleg_conf_t rleg = {
        .ipv4_unicast_enable = 1,
        .ipv4_icmp_redirect_enable = 1,
        .vlan = 10,
    };
    RC(mesa_l3_rleg_add(inst, &rleg));
    rleg.vlan = 20;
    RC(mesa_l3_rleg_add(inst, &rleg));


    // snippet_endbegin if_route
    // Add the two interface routes (destination is zero, meaning copy to
    // CPU).
    mesa_routing_entry_t rt = {
        .type = MESA_ROUTING_ENTRY_TYPE_IPV4_UC,
    };

    rt.route.ipv4_uc.network = to_network("10.0.0.1/24");
    rt.route.ipv4_uc.destination = 0;
    rt.vlan = 10;
    RC(mesa_l3_route_add(inst, &rt));

    rt.route.ipv4_uc.network = to_network("20.0.0.1/24");
    rt.route.ipv4_uc.destination = 0;
    rt.vlan = 20;
    RC(mesa_l3_route_add(inst, &rt));

    // snippet_endbegin host_rt1
    // Add a host route and ARP entry for 10.0.0.5
    mesa_l3_neighbour_t ne = {};
    rt.route.ipv4_uc.network = to_network4("10.0.0.5/32");
    rt.route.ipv4_uc.destination = to_ip4("10.0.0.5");
    rt.vlan = 10;
    RC(mesa_l3_route_add(inst, &rt));

    ne.dmac = {0x0, 0x0, 0x0, 0x10, 0x10, 0x05};
    ne.vlan = 10;
    ne.dip  = to_ip("10.0.0.5");
    RC(mesa_l3_neighbour_add(inst, &ne));

    // snippet_endbegin host_rt2
    // Add a host route and ARP entry for 20.0.0.5
    mesa_l3_neighbour_t ne = {};
    rt.route.ipv4_uc.network = to_network4("20.0.0.5/32");
    rt.route.ipv4_uc.destination = to_ip4("20.0.0.5");
    rt.vlan = 20;
    RC(mesa_l3_route_add(inst, &rt));

    ne.dmac = {0x0, 0x0, 0x0, 0x10, 0x20, 0x05};
    ne.vlan = 20;
    ne.dip  = to_ip("20.0.0.5");
    RC(mesa_l3_neighbour_add(inst, &ne));

    // snippet_endbegin next_hop_rt
    // Add next-hop route (and ARP entry) for the 100.0.0.0/16 network via
    // 20.0.0.5
    mesa_l3_neighbour_t ne = {};
    rt.route.ipv4_uc.network = to_network4("100.0.0.0/16");
    rt.route.ipv4_uc.destination = to_ip4("20.0.0.5");
    rt.vlan = 20;
    RC(mesa_l3_route_add(inst, &rt));

    // snippet_endbegin def_gw
    // Add default gateway via 10.0.0.10
    mesa_l3_neighbour_t ne = {};
    rt.route.ipv4_uc.network = to_network4("0.0.0.0/0");
    rt.route.ipv4_uc.destination = to_ip4("10.0.0.10");
    rt.vlan = 10;
    RC(mesa_l3_route_add(inst, &rt));

    ne.dmac = {0x0, 0x0, 0x0, 0x10, 0x10, 0x10};
    ne.vlan = 10;
    ne.dip  = to_ip("10.0.0.10");
    RC(mesa_l3_neighbour_add(inst, &ne));
    // snippet_end
}

mscc_rc l3_clean_up(const mesa_inst_t inst) {
    mesa_l3_flush(inst);
}

static seq[] = {
    STEP(l3_check_capabilities),
    STEP(l3_vlan_config),
    STEP(l3_basic_config),
    STEP(l3_clean_up),
};

REGISTER_EXAMPLE("L3-simple-example", seq);

