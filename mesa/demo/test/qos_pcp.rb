#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

test "conf" do
    t_i("Set VLAN port configuration")
    $ts.dut.port_list.each do |port|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["untagged_vid"] = 0
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end

    t_i("Map PCP 0-7 to class 7-0")
    $ts.dut.port_list.each do |port|
        conf = $ts.dut.call("mesa_qos_port_conf_get", port)
        conf["tag"]["class_enable"] = true
        for pcp in 0..7
            for dei in 0..1
                conf["tag"]["pcp_dei_map"][pcp][dei]["prio"] = (7 - pcp)
            end
        end
        $ts.dut.call("mesa_qos_port_conf_set", port, conf)
    end
end

#---------- Frame testing -----------------------------------------------------

# Send frame on one port and check switch counters on another port
def frame_test_counters(frame, idx_tx, idx_rx, cnt_tx, cnt_rx, prio)
    port_rx = $ts.dut.port_list[idx_tx]  # Switch Rx
    port_tx = $ts.dut.port_list[idx_rx]  # Switch Tx
    $ts.dut.call("mesa_port_counters_clear", port_rx)
    $ts.dut.call("mesa_port_counters_clear", port_tx)

    # Send frames
    if_tx = "#{$ts.pc.p[idx_tx]}"
    if_rx = "#{$ts.pc.p[idx_rx]}"
    t_i("Sending #{cnt_tx} frames on #{if_tx} to #{if_rx}")
    for i in 1..cnt_tx do
        $ts.pc.run("sudo ef tx #{if_tx} #{frame}")
    end
    sleep(1)

    # Check counters
    t_i("Checking counters")
    rx_cnt = $ts.dut.call("mesa_port_counters_get", port_rx)["prio"][prio]["rx"]
    tx_cnt = $ts.dut.call("mesa_port_counters_get", port_tx)["prio"][prio]["tx"]
    msg = "Rx expected #{cnt_tx} frames, got #{rx_cnt} frames on port #{port_rx}, priority #{prio}"
    if (rx_cnt == cnt_tx)
        t_i(msg)
    else
        t_e(msg)
    end
    msg = "Tx expected #{cnt_rx} frames, got #{tx_cnt} frames on port #{port_tx}, priority #{prio}"
    if (tx_cnt == cnt_rx)
        t_i(msg)
    else
        t_e(msg)
    end
end

test "frame-io" do
    for pcp in 0..7
        frame = "eth"
        frame += cmd_tag_push({tpid: 0x8100, vid: 1, pcp: pcp})
        count = (pcp + 1)
        frame_test_counters(frame, 0, 1, count, count, 7 - pcp)
    end
end
