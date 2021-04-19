#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

$idx_iport = 0
$idx_eport = 1

test "init" do
    $ts.dut.run("mesa-cmd example init evlan iport #{$ts.dut.p[$idx_iport]} eport #{$ts.dut.p[$idx_eport]}")
end

test "frame-io" do
    # Frame test
    cmd = "sudo ef"
    cmd += " name f1 eth"
    cmd += cmd_tag_push({tpid: 0x8100, vid: 10})
    cmd += " data pattern cnt 64"
    cmd += " name f2 eth"
    cmd += cmd_tag_push({tpid: 0x88a8, vid: 20})
    cmd += " data pattern cnt 64"
    cmd += " tx #{$ts.pc.p[$idx_iport]} name f1"
    cmd += " rx #{$ts.pc.p[$idx_eport]} name f2"
    $ts.pc.run(cmd)
    $ts.dut.run("mesa-cmd example run evlan")
end

test "uninit" do
    idx_list = []
    $ts.dut.p.each_index do |idx|
        if (idx != $idx_iport)
            idx_list << idx
        end
    end
    $ts.dut.run("mesa-cmd example uninit")
    run_ef_tx_rx_cmd($ts, $idx_iport, idx_list, "eth" + cmd_tag_push({tpid: 0x8100, vid: 10}) + " data pattern cnt 46")
end
