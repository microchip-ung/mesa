#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

test "conf" do
    $ts.dut.run("mesa-cmd vlan del 1")
end

[64, 128, 256, 512, 1024, 1518].each do |len|
    test "frame-tx-#{len}" do
        $ts.dut.bg("packet_tx", "echo start;sleep 1;mesa-cmd packet tx #{len}")
        cmd = "sudo ef -t 3000"
        $ts.pc.p.each_index do |idx|
            cmd += " rx #{$ts.pc.p[idx]} eth smac #{$ts.dut.p[idx] + 1} et 0xaaaa data repeat #{len - 18} 0xaa"
        end
        $ts.pc.run(cmd)
    end
end

test "dump" do
    $ts.dut.run("mesa-cmd port stati pac")
end
