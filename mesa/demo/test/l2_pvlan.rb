#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

test "conf" do
    t_i("Setup PVLANs")
    $ts.dut.call("mesa_pvlan_port_members_set", 0, "")
    $ts.dut.call("mesa_pvlan_port_members_set", 1, port_idx_list_str([0, 2]))
    $ts.dut.call("mesa_pvlan_port_members_set", 2, port_idx_list_str([1, 2, 3]))

    t_i("Setup APVLAN, allowing port 3 to forward to port 1 only")
    $ts.dut.call("mesa_apvlan_port_members_set", $ts.dut.port_list[3], port_idx_list_str([1]))
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    $ts.dut.p.each_index do |idx_tx|
        idx_list = (idx_tx == 0 ? [2] :
                    idx_tx == 1 ? [2, 3] :
                    idx_tx == 2 ? [0, 1, 3] : [1])
        t_i("Port index: #{idx_tx}")
        run_ef_tx_rx_cmd($ts, idx_tx, idx_list, "eth")
    end
end

