#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'libeasy/utils'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Capabilities -----------------------------------------------------
cap_check_exit("L3")

#---------- Test parameters ----------------------------------------------------
# Test: Multiple  MC-routes.
# 1) Add 2 VLANs and Rlegs for 2 ports
# 2) Add 'no_of_mcasts' MC-groups and a rleg to the second port
# 3) Send frame with the MC-group address from the first port and verify that it gets routed to the second port.
# 4) Repeat for each mcast address

$router_mac = "00:01:02:03:04:05"
$conf_table =
  [
  {
    tx_port: 0,
    vid: 2,
    dmac: "33:33:01:02:03:01",
    sip: "01::1:1",
    mcast: "ff00::0102:0001",
    no_of_mcasts: 50
  },
  {
    vid: 100,
  },
  ]

lpm_cnt = cap_get("L3_LPM_CNT")
if (lpm_cnt < 100)
    $conf_table[0][:no_of_mcasts] = (lpm_cnt / 8)
end

#---------- Configuration -----------------------------------------------------
$rleg_vid = []
$mc_conf = []
#$ts.dut.run "mesa-cmd deb trace api_ail l3 info"
test "l3-mc-conf" do
    $conf_table.each_with_index do |e, idx|
        test "Set VLAN port configuration" do
            port = $ts.dut.p[idx]
            pvid = e[:vid]
            conf = $ts.dut.call "mesa_vlan_port_conf_get", port
            conf["pvid"] = pvid
            conf["untagged_vid"] = 0x1000
            conf["port_type"] = "MESA_VLAN_PORT_TYPE_UNAWARE"
            $ts.dut.call "mesa_vlan_port_conf_set", port, conf
        end
        test "Set VLAN memberships" do
            $ts.dut.call "mesa_vlan_port_members_set", e[:vid], "#{$ts.dut.port_list[idx]}"
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
        $conf_table.each_with_index do |e, idx|
            conf = {
              rleg_enable: false,
              rleg_id: 0,
              ipv4_unicast_enable: false,
              ipv6_unicast_enable: false,
              ipv4_multicast_enable: false,
              ipv6_multicast_enable: true,
              ipv4_icmp_redirect_enable: false,
              ipv6_icmp_redirect_enable: false,
              vlan: e[:vid],
              vrid0_enable: false,
              vrid0: 0,
              vrid1_enable: false,
              vrid1: 0,
              mc_ttl_limit_enable: false,
              mc_ttl_limit: 0
            }
            $ts.dut.call "mesa_l3_rleg_add", conf
            $rleg_vid << e[:vid]
        end
    end

    test "Add multicast routes" do
        $conf_table.each_with_index do |e, idx|
            if !e.key?(:mcast)
                next
            end
            sip = ipv6_str2arr(e[:sip])
            dip = ipv6_str2arr(e[:mcast])
            for addr in 1..e[:no_of_mcasts]
                ipv6_mc = {
                  source: ip_src   = { addr: sip },
                  group:  ip_mcast = { addr: dip }
                }
                src_rleg = e[:vid]
                conf = {
                  type: true,
                  route: {
                    ipv6_mc: ipv6_mc,
                  },
                  source_rleg: src_rleg
                }
                $ts.dut.call "mesa_l3_mc_route_add", conf
                vlan = $conf_table[1][:vid]
                $ts.dut.call "mesa_l3_mc_route_rleg_add", conf, vlan
                tmp = Marshal.load(Marshal.dump(conf)) # need a real copy
                $mc_conf << [tmp, vlan]
                if dip[15] == 255
                    dip[14] += 1
                    dip[15] = 0
                else
                    dip[15] += 1
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
        ip = "ipv6"
        et = "0x86dd"
        ttl = "hlim"
        idx_tx = 0
        idx_rx = 1
        tx_dmac = e[:dmac]
        tx_smac = idx_tx + 1
        tx_ip_src = e[:sip]
        tx_ip_dst = e[:mcast]
        vid = e[:vid]
        ttl_tx = 64
        ttl_rx = ttl_tx - 1
        ip_mcast = IPAddr.new(e[:mcast]).to_i
        for addr in 1..e[:no_of_mcasts]
            tx_ip_dst = IPAddr.new(ip_mcast, Socket::AF_INET6).to_s
            cmd =  "sudo ef name f#{idx_tx} eth dmac #{tx_dmac} smac #{tx_smac} "
            cmd += "et #{et} #{ip} sip #{tx_ip_src} dip #{tx_ip_dst} #{ttl} #{ttl_tx} "
            cmd += "tx #{$ts.pc.p[idx_tx]} name f#{idx_tx} "

            cmd += "name f-rx eth dmac #{tx_dmac} smac #{$router_mac} et #{et} "
            cmd += "#{ip} sip #{tx_ip_src} dip #{tx_ip_dst} #{ttl} #{ttl_rx} "

            cmd += "rx #{$ts.pc.p[idx_rx]} name f-rx "
            $ts.pc.try cmd
            ip_mcast += 1
        end
    end
end

#---------- Cleanup -----------------------------------------------------
pp $mc_conf
$mc_conf.each do |rt, vid|
    $ts.dut.call "mesa_l3_mc_route_rleg_del", rt, vid
end

$mc_conf.each do |rt, vid|
    $ts.dut.call "mesa_l3_mc_route_del", rt
end

$rleg_vid.each do |vid|
    $ts.dut.call "mesa_l3_rleg_del", vid
end
