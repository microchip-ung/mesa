#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'libeasy/utils'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Capabilities -----------------------------------------------------
cap_check_exit("L3")

#---------- Test parameters ----------------------------------------------------
# Test: One MC-route with many MC-rlegs.
# 1) Add a number of VLANs and add IP-rleg to each of them
# 2) Add a MC-group and a MC-rleg to each of the configured IP-rlegs.
# 3) Send frame with the MC-group address and verify that it gets forwarded to all IP rlegs (VLANs).

$router_mac = "00:01:02:03:04:05"
$conf_table =
  [
  {
    tx_port: 0,
    rx_port: [1,2,3],
    vid: 2,
    vid_end: 2,
    dmac: "01:00:5e:01:01:01",
    sip: "10.1.1.1",
    mcast: "230.1.1.1",
  },
  {
    vid: 100,
    vid_end: 102
  },
  {
    vid: 200,
    vid_end: 203
  },
  {
    vid: 300,
    vid_end: 304
  },
  ]

#---------- Configuration -----------------------------------------------------
$rleg_vid = []
$mc_conf = []
#$ts.dut.run "mesa-cmd deb trace api_ail l3 info"
test "l3-mc-conf" do
    vid_cnt = 0
    $conf_table.each_with_index do |e, idx|
        test "Set VLAN port configuration" do
            port = $ts.dut.p[idx]
            pvid = e[:vid]
            conf = $ts.dut.call "mesa_vlan_port_conf_get", port
            conf["pvid"] = pvid
            conf["untagged_vid"] = 0x1000
            conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
            $ts.dut.call "mesa_vlan_port_conf_set", port, conf
        end
        test "Set VLAN memberships" do
            for vlan in e[:vid]..e[:vid_end]
                $ts.dut.call "mesa_vlan_port_members_set", vlan, "#{$ts.dut.port_list[idx]}"
                vid_cnt = (vid_cnt + 1)
            end
        end
    end

    # Enable routing and setup router MAC address
    rt_mac = $router_mac.split(":")
    rt_mac.each_with_index{|val, index | rt_mac[index] = val.to_i}
    conf = {
      rleg_mode: "MESA_ROUTING_RLEG_MAC_MODE_SINGLE",
      base_address: {addr: rt_mac},
      routing_enable: false,
      mc_routing_enable: true
    }
    $ts.dut.call "mesa_l3_common_set", conf

    test "Add router legs" do
        rl_incr = cap_get("L3_RLEG_CNT") / vid_cnt
        rl_id = 0
        $conf_table.each_with_index do |e, idx|
            for vlan in e[:vid]..e[:vid_end]
                conf = {
                  rleg_enable: true,
                  rleg_id: rl_id,
                  ipv4_unicast_enable: true,
                  ipv6_unicast_enable: false,
                  ipv4_multicast_enable: true,
                  ipv6_multicast_enable: false,
                  ipv4_icmp_redirect_enable: false,
                  ipv6_icmp_redirect_enable: false,
                  vlan: vlan,
                  vrid0_enable: false,
                  vrid0: 0,
                  vrid1_enable: false,
                  vrid1: 0,
                  mc_ttl_limit_enable: false,
                  mc_ttl_limit: 0
                }            
                $ts.dut.call "mesa_l3_rleg_add", conf
                $rleg_vid << vlan
                rl_id = (rl_id + rl_incr)
            end
        end
    end

    test "Add multicast routes" do
        $conf_table.each_with_index do |e, idx|
            if !e.key?(:mcast)
                next
            end
            ip_src = IPAddr.new(e[:sip]).to_i
            ip_mcast = IPAddr.new(e[:mcast]).to_i    
            ipv4_mc = {
              source: ip_src,
              group: ip_mcast
            }
            src_rleg = e[:vid]

            conf = {
              type: false,
              route: {
                ipv4_mc: ipv4_mc,
              },
              source_rleg: src_rleg
            }
            $ts.dut.call "mesa_l3_mc_route_add", conf
            e[:rx_port].each do |idx_rx|
                vid = $conf_table[idx_rx][:vid]
                vid_end = $conf_table[idx_rx][:vid_end]
                for vlan in vid..vid_end
                    $ts.dut.call "mesa_l3_mc_route_rleg_add", conf, vlan
                    $mc_conf << [conf, vlan]
                end
            end
        end
    end # test mc_conf
end

#---------- Frame testing -----------------------------------------------------
test "mc-frame-routing-io" do
    # Tx frames from port 1 and 2 and expect only to receive from 1 (on port 0)
    $conf_table.each_with_index do |e, idx_tx|
        if !e.key?(:mcast)
            next
        end
        idx_tx = e[:tx_port]
        tx_dmac = e[:dmac]
        tx_smac = idx_tx + 1
        tx_ip_src = e[:sip]
        tx_ip_dst = e[:mcast]
        vid = e[:vid]
        ttl = 64
        ttl_rx = ttl - 1
        cmd =  "sudo ef name f#{idx_tx} eth dmac #{tx_dmac} smac #{tx_smac} ctag vid #{vid} "
        cmd += "et 0x0800 ipv4 sip #{tx_ip_src} dip #{tx_ip_dst} ttl #{ttl} data pattern zero 30 "
        cmd += "tx #{$ts.pc.p[idx_tx]} name f#{idx_tx} "
        
        cmd += "name f-rx eth dmac #{tx_dmac} smac #{$router_mac} et 0x0800 "
        cmd += "ipv4 sip #{tx_ip_src} dip #{tx_ip_dst} ttl #{ttl_rx} data pattern zero 30 "
        e[:rx_port].each do |idx_rx|
            vid = $conf_table[idx_rx][:vid]
            vid_end = $conf_table[idx_rx][:vid_end]
            for vlan in vid..vid_end
                cmd += "rx #{$ts.pc.p[idx_rx]} name f-rx "
            end
        end
        $ts.pc.try cmd
    end
end

#---------- Cleanup -----------------------------------------------------
$mc_conf.each do |rt, vid|
    $ts.dut.call "mesa_l3_mc_route_rleg_del", rt, vid
end

$mc_conf.each do |rt, vid|
    $ts.dut.call "mesa_l3_mc_route_del", rt
    break
end

$rleg_vid.each do |vid|
    $ts.dut.call "mesa_l3_rleg_del", vid
end
