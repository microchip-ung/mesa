#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_ace   = 0
$idx_port  = 1
$idx_redir = 2

test "conf" do
    t_i("ACE redirect")
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ANY")
    ace["id"] = 1
    ace["port_list"] = "#{$ts.dut.port_list[$idx_ace]}"
    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_REDIR"
    action["port_list"] = "#{$ts.dut.port_list[$idx_redir]}"
    $ts.dut.call("mesa_ace_add", 0, ace)

    t_i("Port default redirect")
    port = $ts.dut.port_list[$idx_port]
    conf = $ts.dut.call("mesa_acl_port_conf_get", port)
    action = conf["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_REDIR"
    action["port_list"] = "#{$ts.dut.port_list[$idx_redir]}"
    $ts.dut.call("mesa_acl_port_conf_set", port, conf)
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    port = $ts.dut.port_list[$idx_redir]
    for i in 0..2
        if (i == 1)
            state = "MESA_STP_STATE_DISCARDING"
            idx_rx = []
        else
            state = "MESA_STP_STATE_FORWARDING"
            idx_rx = [$idx_redir]
        end
        $ts.dut.call("mesa_stp_port_state_set", port, state)
        for j in 0..1
            idx_tx = (j == 0 ? $idx_ace : $idx_port)
            run_ef_tx_rx_cmd($ts, idx_tx, idx_rx, "eth")
        end
    end
end
