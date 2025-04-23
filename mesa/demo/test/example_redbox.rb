#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if RedBox supported
cap_check_exit("L2_REDBOX_CNT")

#---------- Configuration -----------------------------------------------------

$idx_a = 0
$idx_b = 1
$idx_c = 2

test "init" do
    port_a = $ts.dut.p[$idx_a]
    port_b = $ts.dut.p[$idx_b]
    $ts.dut.run("mesa-cmd example init redbox port_a #{port_a} port_b #{port_b}")
end

test "run" do
    [$idx_a, $idx_b, $idx_c].each do |idx|
        smac = (idx == $idx_a ? "a" : idx == $idx_b ? "b" : "c")
        cmd = "ef name f1 eth smac :#{smac} "
        if (idx != $idx_c)
            cmd += "htag pathid 0 size 52 seqn 0 "
        end
        cmd += "tx #{$ts.pc.p[idx]} name f1"
        $ts.pc.run(cmd)
    end
    $ts.dut.run("mesa-cmd example run redbox")
end

test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
end
