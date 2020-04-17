#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$conf_table = [ "BOTH", "BOTH", "EGRESS", "NONE" ]

test "conf" do
    t_i("Set port forwarding state")
    $ts.dut.port_list.each_with_index do |port, idx|
        state = ("MESA_AUTH_STATE_" + $conf_table[idx])
        $ts.dut.call("mesa_auth_port_state_set", port, state)
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    $ts.dut.p.each_index do |idx_tx|
        # Determine forwarding per ingress port
        conf = $conf_table[idx_tx]
        fwd = (conf[0] == "B")

        # Determine forwarding per egress port
        idx_list = []
        $ts.dut.p.each_index do |idx_rx|
            conf = $conf_table[idx_rx]
            if (fwd and idx_rx != idx_tx and conf[0] != "N")
                idx_list << idx_rx
            end
        end
        run_ef_tx_rx_cmd($ts, idx_tx, idx_list, "eth")
    end
end
