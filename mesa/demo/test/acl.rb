#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

test "conf" do
    conf_table =
        [
         {
             # ACE 1: From port 0, forward SIP 1.1.1.1 only to port 2 and 3
             id: 1,
             port: [0],
             sip: 0x01010101,
             sip_mask: 0xffffffff,
             action: "MESA_ACL_PORT_ACTION_FILTER",
             port_list: [1, 2]
         },
         {
             # ACE 2: From port 0, redirect SIP 1.1.1.x back to port 0
             id: 2,
             port: [0],
             sip: 0x01010100,
             sip_mask: 0xffffff00,
             action: "MESA_ACL_PORT_ACTION_REDIR",
             port_list: [0]
         },
         {
             # ACE 3: From port 1, forward SIP 1.1.1.1 only to port 0
             id: 3,
             port: [1],
             sip: 0x01010101,
             sip_mask: 0xffffffff,
             action: "MESA_ACL_PORT_ACTION_FILTER",
             port_list: [0]
         }
        ]

    conf_table.each do |conf|
        ace = $ts.dut.call "mesa_ace_init", "MESA_ACE_TYPE_IPV4"
        ace["id"] = conf[:id]
        action = ace["action"]
        action["port_action"] = conf[:action]
        action["port_list"] = port_idx_list_str(conf[:port_list])
        ace["port_list"] = port_idx_list_str(conf[:port])
        sip = ace["frame"]["ipv4"]["sip"]
        sip["value"] = conf[:sip]
        sip["mask"] = conf[:sip_mask]
        $ts.dut.call "mesa_ace_add", 0, ace
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    # Tx frames for for each host port
    ["1.1.1.1", "1.1.1.2"].each do |sip|
        $ts.dut.p.each_index do |idx_tx|
            idx_list = []
            $ts.dut.p.each_index do |idx_rx|
                # Forward to all other ports by default
                fwd = (idx_rx != idx_tx)
                if (sip == "1.1.1.1")
                    if (idx_tx == 0 and idx_rx == 3)
                        # ACE 1 match, do not forward to port 3
                        fwd = false
                    end
                    if (idx_tx == 1)
                        # ACE 3 match, forward only to port 0
                        fwd = (idx_rx == 0)
                    end
                else
                    if (idx_tx == 0)
                        # ACE 2 match, redirect back to port 0
                        fwd = (idx_rx == 0)
                    end
                end
                if (fwd)
                    idx_list << idx_rx
                end
            end
            cmd = "eth ipv4 sip #{sip}"
            run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
        end
    end
end
