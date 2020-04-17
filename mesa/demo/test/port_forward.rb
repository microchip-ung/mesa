#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$conf_table = [ "ENABLED", "DISABLED", "INGRESS" , "EGRESS" ]

test "conf" do
    t_i("Set port forwarding state")
    $ts.dut.port_list.each_with_index do |port, idx|
        $ts.dut.call("mesa_port_forward_state_set", port, "MESA_PORT_FORWARD_" + $conf_table[idx])
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do

    $ts.dut.p.each_index do |idx_tx|
        # Determine forwarding per ingress port
        conf = $conf_table[idx_tx]
        fwd = (conf[2] == "A" or conf[0] == "I")
        cmd =  "sudo ef name f#{idx_tx} eth dmac ::1 smac ::2 "
        cmd += "tx #{$ts.pc.p[idx_tx]} name f#{idx_tx} "
        # Determine forwarding per egress port
        idx_list = []
        $ts.dut.p.each_index do |idx_rx|
            conf = $conf_table[idx_rx]
            if (fwd and idx_rx != idx_tx and conf[0] == "E")
                if (fwd and idx_rx != idx_tx and conf[0] == "E")
                    cmd += "rx #{$ts.pc.p[idx_rx]} name f#{idx_tx} "
                else
                    cmd += "rx #{$ts.pc.p[idx_rx]} "
                end
            else
                cmd += "rx #{$ts.pc.p[idx_rx]} "
            end
        end
        $ts.pc.try cmd
    end
end

#---------- Clean-up -----------------------------------------------------
$ts.dut.port_list.each_with_index do |port, idx|
    $ts.dut.call("mesa_port_forward_state_set", port, "MESA_PORT_FORWARD_ENABLED")
end
