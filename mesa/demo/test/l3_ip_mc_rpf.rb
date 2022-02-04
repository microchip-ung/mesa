#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'libeasy/utils'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Capabilities -----------------------------------------------------
cap_check_exit("L3")
check_capabilities do
    $cap_fpga = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_FPGA")
    assert(($cap_fpga == 0), "Feature not supported on FPGA")
end

#---------- Test parameters ----------------------------------------------------
$router_mac = "00:01:02:03:04:05"
$conf_table =
  [
    {
      vid: 2,
      sip: "10.1.1.1",
      mcast: "230.1.1.1",
      ipv6_sip: "01::1:1",
      ipv6_mcast: "ff00::0102:0304",
      rt_rpf: false,
    },
    {
      vid: 3,
      sip: "20.1.1.1",
      mcast: "230.1.1.2",
      ipv6_sip: "02::2:2",
      ipv6_mcast: "ff00::0102:0305",
      rt_rpf: true,
    },
    {
      vid: 4,
    },
  ]

$frame_table =
  [
  {
    tx_port: 1,
    dmac: "33:33:01:02:03:01",
    vid: 3,
    sip: "01::1:1",
    mcast: "ff00::0102:0304",
    expect_rx: true
  },
  {
    tx_port: 1,
    dmac: "33:33:01:02:03:01",
    vid: 3,
    sip: "02::2:2",
    mcast: "ff00::0102:0305",
    expect_rx: true
  },
  {
    tx_port: 2,
    dmac: "33:33:01:02:03:01",
    vid: 4,
    sip: "01::1:1",
    mcast: "ff00::0102:0304",
    expect_rx: true
  },
  {
    tx_port: 2,
    dmac: "33:33:01:02:03:01",
    vid: 4,
    sip: "02::2:2",
    mcast: "ff00::0102:0305",
    expect_rx: false # false due to RFP is enabled
  },
  {
    tx_port: 1,
    dmac: "01:00:5e:01:01:01",
    vid: 3,
    sip: "10.1.1.1",
    mcast: "230.1.1.1",
    expect_rx: true
  },
  {
    tx_port: 1,
    dmac: "01:00:5e:01:01:01",
    vid: 3,
    sip: "20.1.1.1",
    mcast: "230.1.1.2",
    expect_rx: true
  },
  {
    tx_port: 2,
    dmac: "01:00:5e:01:01:01",
    vid: 4,
    sip: "10.1.1.1",
    mcast: "230.1.1.1",
    expect_rx: true
  },
  {
    tx_port: 2,
    dmac: "01:00:5e:01:01:01",
    vid: 4,
    sip: "20.1.1.1",
    mcast: "230.1.1.2",
    expect_rx: false # false due to RFP is enabled
  },
  ]

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
            conf["untagged_vid"] = pvid
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
              ipv4_multicast_enable: true,
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
        ["v4", "v6"].each {|ver|
            $conf_table.each_with_index do |e, idx|
                if !e.key?(:sip)
                    next
                end
                if ver == "v6" && !e.key?(:ipv6_sip)
                    next
                end
                if ver == "v4"
                    ip_src = IPAddr.new(e[:sip]).to_i
                    ip_mcast = IPAddr.new(e[:mcast]).to_i
                    ipv4_mc = {
                      source: ip_src,
                      group: ip_mcast
                    }
                else
                    sip = ipv6_str2arr(e[:ipv6_sip])
                    dip = ipv6_str2arr(e[:ipv6_mcast])
                    ipv6_mc = {
                      source: ip_src   = { addr: sip },
                      group:  ip_mcast = { addr: dip }
                    }
                end

                if e[:rt_rpf]
                    src_rleg = e[:vid]
                else
                    src_rleg = 0
                end
                conf = {}
                if ver == "v4"
                    conf = {
                      type: false,
                      route: {
                        ipv4_mc: ipv4_mc,
                      },
                      source_rleg: src_rleg
                    }
                else
                    conf = {
                    type: true,
                      route: {
                      ipv6_mc: ipv6_mc,
                    },
                      source_rleg: src_rleg
                    }
                end
                $ts.dut.call "mesa_l3_mc_route_add", conf
                $ts.dut.call "mesa_l3_mc_route_rleg_add", conf, $conf_table[0][:vid]
                if !$mc_conf.include? conf
                    $mc_conf << conf
                end
            end
        }
    end # test mc_conf
end

#---------- Frame testing -----------------------------------------------------
test "mc-frame-routing-io" do
    # Tx frames from port 1 and 2 and expect only to receive from 1 (on port 0)
    $frame_table.each_with_index do |e, idx_tx|
        ip = "ipv4"
        et = "0x0800"
        ttl = "ttl"
        if e[:dmac].include? "33:33"
            ip = "ipv6"
            et = "0x86dd"
            ttl = "hlim"
        end
        idx_tx = e[:tx_port]
        tx_dmac = e[:dmac]
        tx_smac = idx_tx + 1
        tx_ip_src = e[:sip]
        tx_ip_dst = e[:mcast]
        vid = e[:vid]
        ttl_tx = 64
        ttl_rx = ttl_tx - 1
        cmd =  "sudo ef name f#{idx_tx} eth dmac #{tx_dmac} smac #{tx_smac} "
        cmd += "et #{et} #{ip} sip #{tx_ip_src} dip #{tx_ip_dst} #{ttl} #{ttl_tx} "
        cmd += "tx #{$ts.pc.p[idx_tx]} name f#{idx_tx} "
        idx_rx = 0
        cmd += "name f#{idx_rx} eth dmac #{tx_dmac} smac #{$router_mac} et #{et} "
        cmd += "#{ip} sip #{tx_ip_src} dip #{tx_ip_dst} #{ttl} #{ttl_rx} "
        if e[:expect_rx]
            cmd += "rx #{$ts.pc.p[idx_rx]} name f#{idx_rx}"
        else
            cmd += "rx #{$ts.pc.p[idx_rx]}"
        end
        $ts.pc.try cmd
    end
end

$mc_conf.each do |rt, vid|
    active = $ts.dut.call "mesa_l3_mc_route_active_get", rt
    if !active
        t_e "Route was not hit??"
    end
    active = $ts.dut.call "mesa_l3_mc_route_active_get", rt
    if active
        t_e "Route hit should be cleared hit??"
    end
end

#---------- Cleanup -----------------------------------------------------
$mc_conf.each do |rt, vid|
    $ts.dut.call "mesa_l3_mc_route_del", rt
end
$rleg_vid.each do |vid|
    $ts.dut.call "mesa_l3_rleg_del", vid
end

