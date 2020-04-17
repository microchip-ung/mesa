// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "mscc/ethernet/switch/api.h"

static struct {
    mesa_port_no_t        iport;
    mesa_port_no_t        eport;
    mesa_vid_t            vid_a;
    mesa_vid_t            vid_b;
    mesa_vlan_port_conf_t vlan_conf;
    mesa_l3_common_conf_t l3_conf;
    int                   rt_cnt;
    mesa_routing_entry_t  route[10];
    int                   nbr_cnt;
    mesa_l3_neighbour_t   nbr[10];
} state;

static int ipv4_uc_init(int argc, const char *argv[])
{
    mesa_port_no_t        iport = ARGV_INT("iport", "Ingress port, VID 10");
    mesa_port_no_t        eport = ARGV_INT("eport", "Egress port, VID 20");
    mesa_vlan_port_conf_t vlan_conf;
    mesa_port_list_t      port_list;
    mesa_l3_common_conf_t l3_conf;
    mesa_l3_rleg_conf_t   rl_conf;
    mesa_routing_entry_t  route;
    mesa_l3_neighbour_t   nbr;
    int                   i;
    
    EXAMPLE_BARRIER(argc);

    if (mesa_capability(NULL, MESA_CAP_L3) == 0) {
        cli_printf("L3 not supported\n");
        return -1;
    }

    // Store state
    memset(&state, 0, sizeof(state));
    state.iport = iport;
    state.eport = eport;
    RC(mesa_vlan_port_conf_get(NULL, 0, &state.vlan_conf));

    // Ingress port, VID_A = 10
    state.vid_a = 10;
    RC(mesa_vlan_port_conf_get(NULL, iport, &vlan_conf));
    vlan_conf.pvid = state.vid_a;
    vlan_conf.untagged_vid = state.vid_a;
    RC(mesa_vlan_port_conf_set(NULL, iport, &vlan_conf));

    // Egress port, VID_B = 20
    state.vid_b = 20;
    RC(mesa_vlan_port_conf_get(NULL, eport, &vlan_conf));
    vlan_conf.pvid = state.vid_b;
    vlan_conf.untagged_vid = state.vid_b;
    RC(mesa_vlan_port_conf_set(NULL, eport, &vlan_conf));

    // Add ports to VID_A
    RC(mesa_vlan_port_members_get(NULL, state.vid_a, &port_list));
    mesa_port_list_set(&port_list, iport, 1);
    RC(mesa_vlan_port_members_set(NULL, state.vid_a, &port_list));

    // Add ports to VID_B
    RC(mesa_vlan_port_members_get(NULL, state.vid_b, &port_list));
    mesa_port_list_set(&port_list, eport, 1);
    RC(mesa_vlan_port_members_set(NULL, state.vid_b, &port_list));

    // Enable unicast routing and set base MAC address
    RC(mesa_l3_common_get(NULL, &l3_conf));
    state.l3_conf = l3_conf;
    l3_conf.rleg_mode = MESA_ROUTING_RLEG_MAC_MODE_SINGLE;
    for (i = 0; i < 6; i++) {
        l3_conf.base_address.addr[i] = (i == 5 ? 1 : 0);
    }
    l3_conf.routing_enable = 1;
    RC(mesa_l3_common_set(NULL, &l3_conf));

    // Enable IPv4 unicast routing on VID_A
    memset(&rl_conf, 0, sizeof(rl_conf));
    rl_conf.ipv4_unicast_enable = 1;
    rl_conf.vlan = state.vid_a;
    RC(mesa_l3_rleg_add(NULL, &rl_conf));

    // Enable IPv4 unicast routing on VID_B
    rl_conf.vlan = state.vid_b;
    RC(mesa_l3_rleg_add(NULL, &rl_conf));

    // Add direct route to network 1.1.1.0/24 via VID_A
    route.type = MESA_ROUTING_ENTRY_TYPE_IPV4_UC;
    route.route.ipv4_uc.network.address = 0x01010100;
    route.route.ipv4_uc.network.prefix_size = 24;
    route.route.ipv4_uc.destination = 0;
    route.vlan = state.vid_a;
    RC(mesa_l3_route_add(NULL, &route));
    state.route[state.rt_cnt++] = route;
    
    // Add direct route to network 2.2.2.0/24 via VID_B
    route.type = MESA_ROUTING_ENTRY_TYPE_IPV4_UC;
    route.route.ipv4_uc.network.address = 0x02020200;
    route.route.ipv4_uc.network.prefix_size = 24;
    route.route.ipv4_uc.destination = 0;
    route.vlan = state.vid_b;
    RC(mesa_l3_route_add(NULL, &route));
    state.route[state.rt_cnt++] = route;

    // Add direct route to host 1.1.1.1 via VID_A
    route.type = MESA_ROUTING_ENTRY_TYPE_IPV4_UC;
    route.route.ipv4_uc.network.address = 0x01010101;
    route.route.ipv4_uc.network.prefix_size = 32;
    route.route.ipv4_uc.destination = 0x01010101;
    route.vlan = state.vid_a;
    RC(mesa_l3_route_add(NULL, &route));
    state.route[state.rt_cnt++] = route;

    // Add direct route to host 2.2.2.2 via VID_B
    route.type = MESA_ROUTING_ENTRY_TYPE_IPV4_UC;
    route.route.ipv4_uc.network.address = 0x02020202;
    route.route.ipv4_uc.network.prefix_size = 32;
    route.route.ipv4_uc.destination = 0x02020202;
    route.vlan = state.vid_b;
    RC(mesa_l3_route_add(NULL, &route));
    state.route[state.rt_cnt++] = route;

    // Add indirect route to network 3.3.0.0/16 via nexthop 2.2.2.1 on VID_B
    route.type = MESA_ROUTING_ENTRY_TYPE_IPV4_UC;
    route.route.ipv4_uc.network.address = 0x03030000;
    route.route.ipv4_uc.network.prefix_size = 16;
    route.route.ipv4_uc.destination = 0x02020201;
    route.vlan = state.vid_b;
    RC(mesa_l3_route_add(NULL, &route));
    state.route[state.rt_cnt++] = route;

    // Add neighbour entry for host 1.1.1.1
    nbr.dip.type = MESA_IP_TYPE_IPV4;
    nbr.dip.addr.ipv4 = 0x01010101;
    nbr.vlan = state.vid_a;
    for (i = 0; i < 6; i++) {
        nbr.dmac.addr[i] = (i > 1 ? 1 : 0);
    }
    RC(mesa_l3_neighbour_add(NULL, &nbr));
    state.nbr[state.nbr_cnt++] = nbr;
    
    // Add neighbour entry for host 2.2.2.2
    nbr.dip.type = MESA_IP_TYPE_IPV4;
    nbr.dip.addr.ipv4 = 0x02020202;
    nbr.vlan = state.vid_b;
    for (i = 0; i < 6; i++) {
        nbr.dmac.addr[i] = (i > 1 ? 2 : 0);
    }
    RC(mesa_l3_neighbour_add(NULL, &nbr));
    state.nbr[state.nbr_cnt++] = nbr;
    
    // Add neighbour entry for nexthop router 2.2.2.1
    nbr.dip.type = MESA_IP_TYPE_IPV4;
    nbr.dip.addr.ipv4 = 0x02020201;
    nbr.vlan = state.vid_b;
    for (i = 0; i < 6; i++) {
        nbr.dmac.addr[i] = (i == 5 ? 1 : i > 1 ? 2 : 0);
    }
    RC(mesa_l3_neighbour_add(NULL, &nbr));
    state.nbr[state.nbr_cnt++] = nbr;
    
    return 0;
}

static void ipv4_uc_stat(const char *name, uint64_t cnt)
{
    char buf[80];
    
    sprintf(buf, "%s:", name);
    cli_printf("%-19s%19llu\n", buf, cnt);
}

static int ipv4_uc_run(int argc, const char *argv[])
{
    mesa_l3_counters_t c;
    mesa_vid_t         vid;
    int                i;
    
    EXAMPLE_BARRIER(argc);
    
    for (i = 0; i < 2; i++) {
        vid = (i ? state.vid_b : state.vid_a);
        RC(mesa_l3_counters_rleg_get(NULL, vid, &c));
        cli_printf("VLAN %u counters:\n", vid);
        ipv4_uc_stat("Rx IPv4 Frames", c.ipv4uc_received_frames);
        ipv4_uc_stat("Rx IPv4 Bytes", c.ipv4uc_received_octets);
        ipv4_uc_stat("Tx IPv4 Frames", c.ipv4uc_transmitted_frames);
        ipv4_uc_stat("Tx IPv4 Bytes", c.ipv4uc_transmitted_octets);
        cli_printf("\n");
    }

    return 0;
}

static int ipv4_uc_uninit(void)
{
    mesa_port_list_t port_list;
    int              i;
    
    // Restore VLAN configuration
    RC(mesa_vlan_port_conf_set(NULL, state.iport, &state.vlan_conf));
    RC(mesa_vlan_port_conf_set(NULL, state.eport, &state.vlan_conf));
    mesa_port_list_clear(&port_list);
    RC(mesa_vlan_port_members_set(NULL, state.vid_a, &port_list));
    RC(mesa_vlan_port_members_set(NULL, state.vid_b, &port_list));

    // Disable routing
    RC(mesa_l3_common_set(NULL, &state.l3_conf));

    // Delete Router Legs
    RC(mesa_l3_rleg_del(NULL, state.vid_a));
    RC(mesa_l3_rleg_del(NULL, state.vid_b));

    // Delete routes
    for (i = 0; i < state.rt_cnt; i++) {
        RC(mesa_l3_route_del(NULL, &state.route[i]));
    }
    
    // Delete neighbours
    for (i = 0; i < state.nbr_cnt; i++) {
        RC(mesa_l3_neighbour_del(NULL, &state.nbr[i]));
    }
    
    return 0;
}

static const char *ipv4_uc_help(void)
{
    return "IPv4 unicast routing example";
}

EXAMPLE(ipv4_uc, ipv4_uc_init, ipv4_uc_run, ipv4_uc_uninit, ipv4_uc_help);
