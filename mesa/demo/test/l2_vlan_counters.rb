#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

# Check if VLAN counters supported
cap_check_exit("L2_VLAN_COUNTERS")

# Base VID
$vid = 10

test "conf" do
    t_i "VLAN port configuration"
    $ts.dut.port_list.each_with_index do |port, idx|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["pvid"] = ($vid + idx)
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    cast_list = ["unicast", "multicast", "broadcast"]
    tx_cnt = [{},{}]

    cnt = 1
    for i in 0..1 do
        [0, 1].each do |idx|
            # Counter per VLAN and cast
            vid = ($vid + idx)
            if (i == 0) 
                # First round, send frames
                cast_list.each_with_index do |cast, j|
                    t_i("Sending #{cnt} #{cast} frames on idx #{idx}")
                    dmac = "f#{j == 0 ? "0" : j == 1 ? "1" : "f"}:ff:ff:ff:ff:ff"
                    $ts.pc.run("sudo ef tx #{$ts.pc.p[idx]} rep #{cnt} eth dmac #{dmac}")
                    tx_cnt[idx][cast] = cnt
                    cnt = (cnt + 1)
                end
            else
                # Second round, clear counters
                $ts.dut.call("mesa_vlan_counters_clear", vid)
            end

            # Check counters
            rx_cnt = $ts.dut.call("mesa_vlan_counters_get", vid)
            cast_list.each do |cast|
                ["frames", "bytes"].each do |type|
                    exp = (i == 0 ? tx_cnt[idx][cast] : 0)
                    if (type[0] == "b")
                        exp = (exp * 64)
                    end
                    val = rx_cnt["rx_vlan_#{cast}"][type]
                    msg = "VID #{vid}, #{cast} #{type}, expected: #{exp}, value: #{val}"
                    if (val == exp)
                        t_i(msg)
                    else
                        t_e(msg)
                    end
                end
            end
        end
    end
end
