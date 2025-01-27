#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

test "forward" do
    idx_list = []
    $ts.dut.p.each_index do |idx|
        idx_list.push(idx)
    end
    idx_list.each do |idx|
        port = $ts.dut.p[idx]
        t_i("Tx idx: #{idx}, #{$ts.pc.p[idx]} -> port #{port}")
        run_ef_tx_rx_cmd($ts, idx, idx_list - [idx], "eth smac #{port + 1}")
    end
    #$ts.dut.run("mesa-cmd port stati pa")
end
