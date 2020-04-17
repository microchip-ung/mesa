#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

# One protection group with "1:1" and one with "1+1"
$group_table = [ {idx_list: [0, 1], type: "FOR"},
                 {idx_list: [2, 3], type: "PLUS"} ]
test "conf" do
    $group_table.each do |g|
        idx_list = g[:idx_list]
        port = $ts.dut.port_list[idx_list[0]]
        conf = $ts.dut.call "mesa_eps_port_conf_get", port
        conf["type"] = "MESA_EPS_PORT_1_#{g[:type]}_1"
        conf["port_no"] = $ts.dut.port_list[idx_list[1]]
        $ts.dut.call "mesa_eps_port_conf_set", port, conf
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    # Test each selector state
    [0, 1].each do |idx|
        sel = ("MESA_EPS_SELECTOR_" + (idx == 0 ? "WORKING" : "PROTECTION"))
        g_for = nil
        g_plus = nil
        $group_table.each do |g|
            $ts.dut.call "mesa_eps_port_selector_set", $ts.dut.port_list[g[:idx_list][0]], sel
            if (g[:type][0] == "F")
                g_for = g
            else
                g_plus = g
            end
        end
        $ts.dut.p.each_index do |idx_tx|
            if (g_for[:idx_list].include? idx_tx)
                # Switch Rx on 1:1 group
                idx_list = g_plus[:idx_list]
            elsif (idx_tx == g_plus[:idx_list][idx])
                # Switch Rx on 1+1 working port
                idx_list = [g_for[:idx_list][idx]]
            else
                # Switch Rx on 1+1 protection port
                idx_list = []
            end
            run_ef_tx_rx_cmd($ts, idx_tx, idx_list, "eth")
        end
    end
end

