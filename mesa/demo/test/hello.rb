#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

test "FrameCapture" do
    cap = $ts.links.collect{|x| "-c #{x[:pc]},20,adapter_unsynced"}.join(" ")
    #cap = $ts.links.collect{|x| "-c #{x[:pc]}"}.join(" ")
    $ts.pc.run "ef #{cap} tx #{$ts.links[0][:pc]} rep 10 eth data pattern cnt 1212"

    $ts.links.each do |link|
        pkts = $ts.pc.get_pcap "#{link[:pc]}.pcap"
        t_i "Got #{pkts.size} packets"

        pkts.each do |p|
            t_i "TS: %4d, len: %4d #{hexstr(p[:data])}" % [p[:us_rel], p[:len_on_wire]]
        end
    end
end


#---------- Configuration -----------------------------------------------------

test "conf" do
    break # Skip for now
    # Problem with array of array
    conf = $ts.dut.call("mesa_qos_dscp_dpl_conf_get", 4)

    # Problem with large JSON messages
    map = $ts.dut.call("mesa_qos_ingress_map_init", "MESA_QOS_INGRESS_MAP_KEY_DSCP")
    map["id"] = 1
    $ts.dut.call("mesa_qos_ingress_map_add", map)

    # Method does not exist
    $ts.dut.call_err("mesa_dummy_test")

    # Illegal port number
    $ts.dut.call_err("mesa_vlan_port_conf_get", 1000)

    # Struct fields missing
    $ts.dut.call_err("mesa_vlan_port_conf_set", 1, { pvid:43 })

    # Illegal enumeration value
    conf = $ts.dut.call("mesa_vlan_port_conf_get", 1)
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_DUMMY"
    $ts.dut.call_err("mesa_vlan_port_conf_set", 1, conf)

    # Legal call, port counters
    cnt = $ts.dut.call("mesa_port_counters_get", 0)
    rmon = cnt["rmon"]
    puts("RxPackets: #{rmon["rx_etherStatsPkts"]}")
    puts("TxPackets: #{rmon["tx_etherStatsPkts"]}")
end
