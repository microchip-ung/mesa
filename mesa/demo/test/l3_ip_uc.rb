#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

# Check if L3 supported
cap_check_exit("L3")

$router_mac = [0,1,2,3,4,5]
$vrid = 100

# Routing configuration table
$conf_table =
        [
     {
         vid: 2,
         network: 0x02020200,
         prefix: 24,
         discard_network: 0x04040400,
         discard_prefix: 24,
         router: 0x02020201,
         host: 0x02020202,
         dmac: [2,2,2,2,2,2]
     },
     {
         vid: 3,
         network: 0x03030300,
         prefix: 24,
         discard_network: 0x05050505,
         discard_prefix: 32,
         router: 0x03030301,
         host: 0x03030303,
         dmac: [3,3,3,3,3,3]
     }
    ]

test "conf" do
    t_i("Set VLAN port configuration")
    $ts.dut.port_list.each_with_index do |port, idx|
        pvid = (idx < 2 ? $conf_table[idx][:vid] : 1)
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["pvid"] = pvid
        conf["untagged_vid"] = pvid
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end

    t_i("Set VLAN memberships")
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")
    $conf_table.each_with_index do |e, idx|
        $ts.dut.call("mesa_vlan_port_members_set", e[:vid], "#{$ts.dut.port_list[idx]}")
    end

    t_i("Enable routing and setup router MAC address")
    conf = $ts.dut.call("mesa_l3_common_get")
    conf["rleg_mode"] = "MESA_ROUTING_RLEG_MAC_MODE_SINGLE"
    conf["base_address"] = {addr: $router_mac}
    conf["routing_enable"] = true
    $ts.dut.call("mesa_l3_common_set", conf)

    t_i("Add router legs")
    $conf_table.each do |e|
        conf = {}
        conf[:rleg_enable] = false
        conf[:rleg_id] = 0
        conf[:ipv4_unicast_enable] = true
        conf[:ipv6_unicast_enable] = false
        conf[:ipv4_multicast_enable] = false
        conf[:ipv6_multicast_enable] = false
        conf[:ipv4_icmp_redirect_enable] = false
        conf[:ipv6_icmp_redirect_enable] = false
        conf[:vlan] = e[:vid]
        conf[:vrid0_enable] = false
        conf[:vrid0] = 0
        conf[:vrid1_enable] = true
        conf[:vrid1] = $vrid
        conf[:mc_ttl_limit_enable] = false
        conf[:mc_ttl_limit] = 0
        $ts.dut.call("mesa_l3_rleg_add", conf)
    end

    t_i("Add direct routes, host routes and discard routes")
    $conf_table.each do |e|
        ipv4_uc = {
            network: {
                address: e[:network],
                prefix_size: e[:prefix]
            },
            destination: 0
        }
        conf = {
            type: "MESA_ROUTING_ENTRY_TYPE_IPV4_UC",
            route: {
                ipv4_uc: ipv4_uc
            },
            vlan: e[:vid]
        }
        $ts.dut.call("mesa_l3_route_add", conf)

        ipv4_uc[:network][:address] = e[:host]
        ipv4_uc[:network][:prefix_size] = 32
        ipv4_uc[:destination] = e[:host]
        $ts.dut.call("mesa_l3_route_add", conf)

        ipv4_uc[:network][:address] = e[:discard_network]
        ipv4_uc[:network][:prefix_size] = e[:discard_prefix]
        ipv4_uc[:destination] = 0xffffffff
        $ts.dut.call("mesa_l3_route_add", conf)
    end

    t_i("Add neighbours")
    $conf_table.each do |e|
        conf = {
            dmac: {
                addr: e[:dmac]
            },
            vlan: e[:vid],
            dip: {
                type: "MESA_IP_TYPE_IPV4",
                addr: {
                    ipv4: e[:host]
                }
            }
        }
        $ts.dut.call("mesa_l3_neighbour_add", conf)
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    # Tx frames for for each host port
    $conf_table.each_with_index do |entry, idx|
        # Test both router MAC address and VRRP MAC address
        [$router_mac, [0,0,0x5e,0,1,$vrid]].each do |mac|
            # Tx frame f1, Rx frame f2
            dmac = mac_to_txt(mac)
            f1 = "eth dmac #{dmac}"
            dmac = mac_to_txt(entry[:dmac])
            smac = mac_to_txt($router_mac)
            f2 = "eth dmac #{dmac} smac #{smac}"
            sip = ipv4_to_txt($conf_table[idx == 0 ? 1 : 0][:host])
            dip = ipv4_to_txt(entry[:host])
            f = " ipv4 sip #{sip} dip #{dip} ttl "
            ttl = 64
            f1 += f + "#{ttl}"
            f2 += f + "#{ttl - 1}"

            $ts.dut.p.each_index do |idx_tx|
                cmd = "sudo ef name f1 #{f1} name f2 #{f2}"
                cmd += " tx #{$ts.pc.p[idx_tx]} name f1"
                $ts.dut.p.each_index do |idx_rx|
                    cmd += " rx #{$ts.pc.p[idx_rx]}"
                    if (idx_tx < 2 and idx_rx == idx)
                        # If sent to a port with routing, forward to host port
                        cmd += " name f2"
                    end
                end
                $ts.pc.run(cmd)
            end
        end
    end
end

test "discard-route" do
    # Tx frames for for each host port
    $conf_table.each_with_index do |entry, idx|
        # Tx frame f1, expect discard
        dmac = mac_to_txt($router_mac)
        sip = ipv4_to_txt($conf_table[idx == 0 ? 1 : 0][:host])
        dip = ipv4_to_txt(entry[:discard_network])
        f1 = "eth dmac #{dmac} ipv4 sip #{sip} dip #{dip}"
        $ts.dut.p.each_index do |idx_tx|
            cmd = "sudo ef name f1 #{f1} "
            $ts.dut.p.each_index do |idx_rx|
                dir = "rx"
                f = nil
                if (idx_rx == idx_tx)
                    dir = "tx"
                    f = "f1"
                end
                cmd += " #{dir} #{$ts.pc.p[idx_rx]}"
                unless (f.nil?)
                    cmd += " name #{f}"
                end
            end
            $ts.pc.run(cmd)
        end
    end
end

test "dump" do
    break
    $ts.dut.run("mesa-cmd debug api vlan")
    $ts.dut.run("mesa-cmd debug api l3")
end
