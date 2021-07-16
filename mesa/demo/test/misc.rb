#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

test "chip_id" do
    break
    t_i("Read chip ID")
    id = $ts.dut.call("mesa_chip_id_get")
    part_no = id["part_number"]
    rev = id["revision"]
    t_i("part_no: 0x#{part_no.to_s(16)}, revision: #{rev}")
end

test "forward" do
    break
    t_i("Forward one frame from each port to all other ports")
    idx_list = []
    $ts.dut.p.each_index do |idx|
        idx_list << idx
    end
    $ts.dut.p.each_index do |idx|
        port = $ts.dut.p[idx]
        t_i("Tx idx: #{idx}, #{$ts.pc.p[idx]} -> port #{port}")
        run_ef_tx_rx_cmd($ts, idx, idx_list - [idx], "eth smac #{port + 1}")
    end
    $ts.dut.run("mesa-cmd mac dump")
    $ts.dut.run("mesa-cmd port stati pa")
end

test "forward-length" do
    break
    t_i("Forward frames of different sizes from port index 1 to 0")
    [64, 128, 256].each do |len|
        t_i("Tx #{len} bytes, port #{$ts.dut.p[1]} -> #{$ts.dut.p[0]}")
        $ts.pc.run("sudo ef name f1 eth et 0xaaaa data pattern cnt #{len - 18} tx #{$ts.pc.p[1]} name f1 rx #{$ts.pc.p[0]} name f1")
    end
    $ts.dut.run("mesa-cmd port stati pa")
end

test "forward-loop-2.5G" do
    break
    loop_pair_check
    idx_tx = 0
    idx_rx = 1
    p0 = $ts.dut.p[idx_tx]
    p1 = $ts.dut.p[idx_rx]
    lp0 = $ts.dut.looped_port_list[0]
    lp1 = $ts.dut.looped_port_list[1]

    # Loop ports are 2.5G
    [lp0, lp1].each do |port|
        $ts.dut.run("mesa-cmd port mode #{port + 1} 2500")
    end

    # Port-to-port forwarding via loop ports
    $ts.dut.call("mesa_vlan_port_members_set", 1, "#{p1},#{lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 0, "#{p0},#{lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 1, "#{p1},#{lp1}")

    # Forwarding via loop ports
    cmd = "sudo ef name f1 eth "
    cmd += "tx #{$ts.pc.p[idx_tx]} name f1 "
    cmd += "rx #{$ts.pc.p[idx_rx]} name f1 "
    $ts.pc.run(cmd)
    $ts.dut.run("mesa-cmd port mode")
    $ts.dut.run("mesa-cmd port stati pa")
end

test "led-control" do
    break
    $ts.dut.p.each_with_index do |port, i|
        mode = (i == 0 ? "100fdx" : i == 1 ? "100hdx" : i == 2 ? "10fdx" : "10hdx")
        $ts.dut.run("mesa-cmd port mode #{port + 1} #{mode}")
    end
    sleep(5)
    $ts.dut.run("mesa-cmd debug phy cls read 1,8 5 0")
    $ts.dut.run("mesa-cmd debug phy cls read 1,8 5 1")
    $ts.dut.run("mesa-cmd debug phy cls read 1,8 4 32")
    $ts.dut.run("mesa-cmd debug phy cls read 1,8 4 33")
    $ts.dut.run("mesa-cmd port mode")
end
