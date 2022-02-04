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
# A port-pair configuration is created and multicast routing eanbled between them
# The following is performed for each config:
# 1) A vlan is created with the local port as member.
# 2) A router leg is created for the given vlan
# 3) IP MC Routing is enabled
# 4) A MC group route is created
# 5) A MC router leg is added to this route with the other pairs rleg as member
# 6) Frame is insterted on the local port and validated on the other.

$router_mac = "00:01:02:03:04:05"
$conf_table =
  [
  [
    {    
      test: "Source specific multicast routing",
      rt_ttl_limit_ena: false,
      rt_ttl_limit: 0,
      rt_rpf: false,
      frm_dmac: "01:00:5e:01:01:01",
      frm_vid: 2,
      frm_sip: "10.1.1.2",
      frm_mcast: "230.1.1.1",
      frm_ttl: 64,
      expect_rx: true
    },
    {
      test: "Source specific multicast routing",
      rt_ttl_limit_ena: false,
      rt_ttl_limit: 0,
      rt_rpf: true,
      frm_dmac: "01:00:5e:01:01:02",
      frm_vid: 3,
      frm_sip: "20.1.1.1",
      frm_mcast: "230.1.1.2",
      frm_ttl: 64,
      expect_rx: true
    }
  ],
  [
      {
      test: "Multicast ttl test",
      rt_ttl_limit_ena: false,
      rt_ttl_limit: 0,
      rt_rpf: true,
      frm_dmac: "01:00:5e:01:01:01",
      frm_vid: 2,
      frm_sip: "10.1.1.2",
      frm_mcast: "230.1.1.3",
      frm_ttl: 1,
      expect_rx: false
    },
      {
      test: "Multicast ttl test",
      rt_ttl_limit_ena: false,
      rt_ttl_limit: 0,
      rt_rpf: true,
      frm_dmac: "01:00:5e:01:01:02",
      frm_vid: 3,
      frm_sip: "20.1.1.2",
      frm_mcast: "230.1.1.4",
      frm_ttl: 2,
      expect_rx: true
    }
  ],
  [
    {
      test: "Multicast router ttl-limit enabled",
      rt_ttl_limit_ena: true,
      rt_ttl_limit: 10,
      rt_rpf: true,
      frm_dmac: "01:00:5e:01:01:01",
      frm_vid: 2,
      frm_sip: "10.1.1.2",
      frm_mcast: "230.1.1.3",
      frm_ttl: 10,
      expect_rx: false
    },
    {
      test: "Multicast router ttl-limit enabled",
      rt_ttl_limit_ena: true,
      rt_ttl_limit: 11,
      rt_rpf: true,
      frm_dmac: "01:00:5e:01:01:02",
      frm_vid: 3,
      frm_sip: "20.1.1.2",
      frm_mcast: "230.1.1.4",
      frm_ttl: 10,
      expect_rx: true
    }
  ],
  [
    {
      test: "Source independent routing [*,G]",
      rt_sip: "0.0.0.0",
      rt_mcast: "230.1.1.1",
      rt_ttl_limit_ena: false,
      rt_ttl_limit: 0,
      rt_rpf: false,
      frm_dmac: "01:00:5e:01:01:01",
      frm_vid: 2,
      frm_sip: "1.1.1.1",
      frm_mcast: "230.1.1.1",
      frm_ttl: 64,
      expect_rx: true
    },
    {
      test: "Source specific routing [S,G]",
      rt_sip: "20.1.1.1",
      rt_mcast: "230.1.1.2",
      rt_ttl_limit_ena: false,
      rt_ttl_limit: 0,
      rt_rpf: true,
      frm_dmac: "01:00:5e:01:01:02",
      frm_vid: 3,
      frm_sip: "20.1.1.2",
      frm_mcast: "230.1.1.2",
      frm_ttl: 64,
      expect_rx: false
    }
  ]
  ]


#---------- Configuration -----------------------------------------------------
$rleg_vid = []
$mc_conf = {}
$conf_table.each do |pair|
    test "l3-mc-conf" do
        # Set VLAN port configuration
        test "Set VLAN port configuration" do
            pair.each_with_index do |entry, idx|
                port = $ts.dut.p[idx]
                pvid = pair[idx][:frm_vid]
                conf = $ts.dut.call "mesa_vlan_port_conf_get", port
                conf["pvid"] = pvid
                conf["untagged_vid"] = pvid
                conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
                $ts.dut.call "mesa_vlan_port_conf_set", port, conf
            end
        end

        # Set VLAN memberships
        test "Set VLAN memberships" do
            $ts.dut.call "mesa_vlan_port_members_set", 1, ""
            pair.each_with_index do |e, idx|
                $ts.dut.call "mesa_vlan_port_members_set", e[:frm_vid], "#{$ts.dut.port_list[idx]}"
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
            pair.each do |e|
                conf = {
                  rleg_enable: false,
                  rleg_id: 0,
                  ipv4_unicast_enable: true,
                  ipv6_unicast_enable: false,
                  ipv4_multicast_enable: true,
                  ipv6_multicast_enable: false,
                  ipv4_icmp_redirect_enable: false,
                  ipv6_icmp_redirect_enable: false,
                  vlan: e[:frm_vid],
                  vrid0_enable: false,
                  vrid0: 0,
                  vrid1_enable: false,
                  vrid1: 0,
                  mc_ttl_limit_enable: e[:rt_ttl_limit_ena],
                  mc_ttl_limit: e[:rt_ttl_limit]
                }
                if $rleg_vid.include?e[:frm_vid]
                    $ts.dut.call "mesa_l3_rleg_update", conf
                else
                    $ts.dut.call "mesa_l3_rleg_add", conf
                    $rleg_vid << e[:frm_vid]
                end
            end
        end
        
        test "Add multicast routes" do
            pair.each_with_index do |e, idx|
                if e.key?(:rt_sip)
                    ip_src = IPAddr.new(e[:rt_sip]).to_i
                    ip_mcast = IPAddr.new(e[:rt_mcast]).to_i
                else
                    ip_src = IPAddr.new(e[:frm_sip]).to_i
                    ip_mcast = IPAddr.new(e[:frm_mcast]).to_i
                end
                ipv4_mc = {
                  source: ip_src,
                  group: ip_mcast
                }
                if e[:rt_rpf]
                    src_rleg = e[:frm_vid]
                else
                    src_rleg = 0
                end
                conf = {
                  type: false,
                  route: {
                    ipv4_mc: ipv4_mc,
                  },
                  source_rleg: src_rleg
                }
                $ts.dut.call "mesa_l3_mc_route_add", conf
                $ts.dut.call "mesa_l3_mc_route_rleg_add", conf, (pair[idx == 0 ? 1 : 0][:frm_vid])
                $mc_conf.merge!(conf => (pair[idx == 0 ? 1 : 0][:frm_vid]))
            end
        end
    end # test mc_conf

    #---------- Frame testing -----------------------------------------------------
    test "mc-frame-routing-io" do
        # Tx frames for for each host port and expect to rx the routed frame
        pair.each_with_index do |entry, idx_tx|
            tx_dmac = entry[:frm_dmac]
            tx_smac = idx_tx + 1
            tx_ip_src = entry[:frm_sip]
            tx_ip_dst = entry[:frm_mcast]
            vid = entry[:frm_vid]
            ttl = entry[:frm_ttl]            
            console entry[:test]
            cmd =  "sudo ef name f#{idx_tx} eth dmac #{tx_dmac} smac #{tx_smac} ctag vid #{vid} "
            cmd += "et 0x0800 ipv4 sip #{tx_ip_src} dip #{tx_ip_dst} ttl #{ttl} data pattern zero 30 "
            cmd += "tx #{$ts.pc.p[idx_tx]} name f#{idx_tx} "

            pair.each_with_index do |rxentry, idx_rx|
                if (idx_tx == idx_rx)
                    next
                end
                if ttl > 0
                    ttl -= 1
                end
                cmd += "name f#{idx_rx} eth dmac #{tx_dmac} smac #{$router_mac} et 0x0800 "
                cmd += "ipv4 sip #{tx_ip_src} dip #{tx_ip_dst} ttl #{ttl} data pattern zero 30 "
                if entry[:expect_rx]
                    cmd += "rx #{$ts.pc.p[idx_rx]} name f#{idx_rx}"
                else
                    cmd += "rx #{$ts.pc.p[idx_rx]}"
                end                
            end
            $ts.pc.try cmd
        end

        # Verify counters
        rleg1 = $ts.dut.call "mesa_l3_counters_rleg_get", pair[0][:frm_vid]
        rleg2 = $ts.dut.call "mesa_l3_counters_rleg_get", pair[1][:frm_vid]
        if (rleg1[:ipv4mc_transmitted_frames] != rleg2[:ipv4mc_received_frames]) &&
            (rleg2[:ipv4mc_transmitted_frames] != rleg1[:ipv4mc_received_frames])
            t_e("MC counters does not match");
        end
    end
end

#---------- Cleanup -----------------------------------------------------
$mc_conf.each do |rt, vid|
    $ts.dut.call "mesa_l3_mc_route_rleg_del", rt, vid
end

$mc_conf.each do |rt, vid|
    $ts.dut.call "mesa_l3_mc_route_del", rt
end

$rleg_vid.each do |vid|
    $ts.dut.call "mesa_l3_rleg_del", vid
end

