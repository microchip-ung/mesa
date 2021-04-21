#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

$idx_iport = 0
$idx_eport = 1
$idx_list = []
$ts.dut.p.each_index do |idx|
    $idx_list << idx
end

test "init" do
    $ts.dut.run("mesa-cmd example init packet iport #{$ts.dut.p[$idx_iport]} eport #{$ts.dut.p[$idx_eport]}")
end

def packet_test(idx_tx, idx_list)
    cmd = "sudo ef -t 2000 name f1 "
    cmd += "eth dmac 01:00:5e:05:06:07 smac 00:00:00:00:00:0a "
    cmd += "ipv4 proto 2 dip 225.5.6.7 data pattern cnt 32 "
    cmd += "tx #{$ts.pc.p[idx_tx]} name f1 "
    $idx_list.each do |idx|
        cmd += "rx #{$ts.pc.p[idx]} #{idx_list.include?(idx) ? "name f1 " : ""}"
    end
    $ts.pc.run(cmd)
end

test "port-forward" do
    packet_test($idx_iport, [$idx_eport])
end

test "vlan-forward" do
    packet_test($idx_eport, $idx_list)
end

test "uninit" do
    $ts.dut.run("mesa-cmd example run");
    $ts.dut.run("mesa-cmd example uninit")
    packet_test($idx_iport, $idx_list - [$idx_iport])
end
