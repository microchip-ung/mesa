#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

# Check if L3 supported
cap_check_exit("L3")

$router_mac = [0,1,2,3,4,5]

$if_table = 
    [
     { port: 0, vid: 2},
     { port: 1, vid: 3}
    ]

$route_table =
    [
     { net: 0x04040100, prefix: 24, nexthop: 0x03030303, cnt: 1 },
     { net: 0x04040200, prefix: 24, nexthop: 0x03030303, cnt: 2 },
     { net: 0x04040300, prefix: 24, nexthop: 0x03030303, cnt: 3 },
     { net: 0x04040400, prefix: 24, nexthop: 0x03030303, cnt: 4 },
     { net: 0x04040500, prefix: 24, nexthop: 0x03030303, cnt: 5 },
     { net: 0x04040600, prefix: 24, nexthop: 0x03030303, cnt: 6 },
     { net: 0x04040700, prefix: 24, nexthop: 0x03030303, cnt: 7 },
     { net: 0x04040800, prefix: 24, nexthop: 0x03030303, cnt: 8 },
     { net: [2,0,0,0,0,0,0,0,0,0,0,0,5,10,0,0], prefix: 112, nexthop: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 1 },
     { net: [2,0,0,0,0,0,0,0,0,0,0,0,5,11,0,0], prefix: 112, nexthop: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 2 },
     { net: [2,0,0,0,0,0,0,0,0,0,0,0,5,12,0,0], prefix: 112, nexthop: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 3 },
     { net: [2,0,0,0,0,0,0,0,0,0,0,0,5,13,0,0], prefix: 112, nexthop: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 4 },
     { net: [2,0,0,0,0,0,0,0,0,0,0,0,5,14,0,0], prefix: 112, nexthop: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 5 },
     { net: [2,0,0,0,0,0,0,0,0,0,0,0,5,15,0,0], prefix: 112, nexthop: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 6 },
     { net: [2,0,0,0,0,0,0,0,0,0,0,0,5,16,0,0], prefix: 112, nexthop: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 7 },
     { net: [2,0,0,0,0,0,0,0,0,0,0,0,5,17,0,0], prefix: 112, nexthop: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 8 },
    ]

$nb_table =
    [
     { vid: 3, dip: 0x03030303, cnt: 8 },
     { vid: 3, dip: [2,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3], cnt: 8 }
    ]

def ip2mac(nh)
    mac = [0,0,0,0,0,0]
    for i in 2..5
        if (nh.kind_of?(Array))
            mac[i] = nh[i + 10]
        else
            mac[i] = ((nh >> ((5 - i) * 8)) & 0xff)
        end
    end
    mac
end
     
def route_conf(add)
    $route_table.each do |e|
        net = {}
        ip = { network: net }
        conf = {}
        net[:prefix_size] = e[:prefix]
        for i in 0..(e[:cnt] - 1)
            if (e[:net].kind_of?(Array))
                # IPv6
                conf[:type] = "MESA_ROUTING_ENTRY_TYPE_IPV6_UC"
                conf[:route] = { ipv6_uc: ip }
                net[:address] = { addr: e[:net] }
                nh = e[:nexthop].dup
                nh[15] += i
                ip[:destination] = { addr: nh }
                conf[:vlan] = 3
            else
                # IPv4
                conf[:type] = "MESA_ROUTING_ENTRY_TYPE_IPV4_UC"
                conf[:route] = { ipv4_uc: ip}
                net[:address] = e[:net]
                ip[:destination] = (e[:nexthop] + i)
                conf[:vlan] = 0
            end
            if (add)
                $ts.dut.call("mesa_l3_route_add", conf)
            elsif (i != 0)
                $ts.dut.call("mesa_l3_route_del", conf)
            end
        end
    end
end

test "conf" do
    t_i("Enable routing and setup router MAC address")
    conf = $ts.dut.call("mesa_l3_common_get")
    conf["rleg_mode"] = "MESA_ROUTING_RLEG_MAC_MODE_SINGLE"
    conf["base_address"] = {addr: $router_mac}
    conf["routing_enable"] = true
    $ts.dut.call("mesa_l3_common_set", conf)

    t_i("Set VLAN and Router Leg configuration")
    $if_table.each do |e|
        port = $ts.dut.port_list[e[:port]]
        vid = e[:vid]
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["pvid"] = vid
        conf["untagged_vid"] = vid
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
        
        $ts.dut.call("mesa_vlan_port_members_set", vid, "#{port}")

        conf = {}
        conf[:rleg_enable] = false
        conf[:rleg_id] = 0
        conf[:ipv4_unicast_enable] = true
        conf[:ipv6_unicast_enable] = true
        conf[:ipv4_multicast_enable] = false
        conf[:ipv6_multicast_enable] = false
        conf[:ipv4_icmp_redirect_enable] = false
        conf[:ipv6_icmp_redirect_enable] = false
        conf[:vlan] = vid
        conf[:vrid0_enable] = false
        conf[:vrid0] = 0
        conf[:vrid1_enable] = false
        conf[:vrid1] = 0
        conf[:mc_ttl_limit_enable] = false
        conf[:mc_ttl_limit] = 0
        $ts.dut.call("mesa_l3_rleg_add", conf)
    end

    t_i("Add neighbours")
    $nb_table.each do |e|
        addr = {}
        dip = { addr: addr }
        dmac = {}
        conf = {}
        conf[:dip] = dip
        conf[:dmac] = dmac
        conf[:vlan] = e[:vid]
        for i in 0..(e[:cnt] - 1)
            nh = 0
            if (e[:dip].kind_of?(Array))
                # IPv6
                dip[:type] = "MESA_IP_TYPE_IPV6"
                nh = e[:dip].dup
                nh[15] += i
                addr[:ipv6] = { addr: nh }
            else
                #IPv4
                dip[:type] = "MESA_IP_TYPE_IPV4"
                nh = (e[:dip] + i)
                addr[:ipv4] = nh
            end
            dmac[:addr] = ip2mac(nh)
            $ts.dut.call("mesa_l3_neighbour_add", conf)
        end
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    idx_tx = $if_table[0][:port]
    idx_rx = $if_table[1][:port]
    
    # Reduce table for platforms with few ARP entries
    arp_cnt = (cap_get("L3_ARP_CNT") / 2)
    cnt = 0
    $route_table.each do |rt|
        new_cnt = (cnt + rt[:cnt])
        if ((new_cnt + 8) > arp_cnt)
            rt[:cnt] = 0
        else
            cnt = new_cnt
        end
    end

    # Test once with multiple nexthops, then with single nexthop
    [true, false].each do |add|
        route_conf(add)
        $route_table.each do |rt|
            if (rt[:cnt] == 0)
                break
            end
            for i in 0..7
                # Incrementing SIP, calculate nexthop (4-bit XOR of SIP)
                xor = 0
                if (rt[:net].kind_of?(Array))
                    # IPv6
                    sip = [2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2 + i]
                    for j in 0..15
                        xor ^= sip[j]
                    end
                    xor = ((xor ^= (xor >> 4)) & 0xf)
                    nh = rt[:nexthop].dup
                    if (add)
                        nh[15] += (xor % rt[:cnt])
                    end
                    nh_txt = ipv6_to_txt(nh)
                    sip = ipv6_to_txt(sip)
                    dip = ipv6_to_txt(rt[:net])
                    f = " ipv6 next 1 sip #{sip} dip #{dip} hlim "
                else
                    sip = (0x02020202 + i)
                    for j in 0..7
                        xor ^= (sip >> (j * 4))
                    end
                    xor &= 0xf
                    nh = rt[:nexthop]
                    if (add)
                        nh += (xor % rt[:cnt])
                    end
                    nh_txt = ipv4_to_txt(nh)
                    sip = ipv4_to_txt(sip)
                    dip = ipv4_to_txt(rt[:net])
                    f = " ipv4 proto 1 sip #{sip} dip #{dip} ttl "
                end
                
                txt = (add ? "multi" : "single")
                t_i("#{txt}, sip: #{sip}, dip: #{dip}, nh: #{nh_txt}")

                # Tx frame f1, Rx frame f2
                rmac = mac_to_txt($router_mac)
                f1 = " eth dmac #{rmac}"
                dmac = mac_to_txt(ip2mac(nh))
                f2 = " eth dmac #{dmac} smac #{rmac}"
                ttl = 64
                f1 += f + "#{ttl}"
                f2 += f + "#{ttl - 1}"

                cmd = "sudo ef name f1 #{f1} name f2 #{f2} "
                cmd += "tx #{$ts.pc.p[idx_tx]} name f1 rx #{$ts.pc.p[idx_rx]} name f2"
                $ts.pc.run(cmd)
            end
        end
    end
end
