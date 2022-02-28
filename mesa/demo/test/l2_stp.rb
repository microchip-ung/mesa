#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$stp_state_table = [ "DISCARDING", "LEARNING", "FORWARDING" , "FORWARDING" ]
$vid_table = [ { vid: 100, msti: 0, state: "FORWARDING" },
               { vid: 200, msti: 1, state: "DISCARDING" },
               { vid: 300, msti: 2, state: "LEARNING" },
               { vid: 400, msti: 3, state: "FORWARDING" } ]

# Port index 2 has special MSTP states
$mstp_port_idx = 2

test "conf" do
    t_i("Set STP ports state")
    $ts.dut.port_list.each_with_index do |port, idx|
        $ts.dut.call("mesa_stp_port_state_set", port, "MESA_STP_STATE_" + $stp_state_table[idx])
    end

    # Caracal/Serval need VLAN ingress filtering for MSTP
    ingress_filter = (cap_get("L2_TPID_AWARE") == 0)

    t_i("Set VLAN port configuration")
    $ts.dut.port_list.each do |port|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["untagged_vid"] = 0
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end
    
    t_i("Set VLAN memberships and MSTP mappings")
    $vid_table.each do |e|
        vid = e[:vid]
        $ts.dut.call("mesa_vlan_port_members_set", vid, $ts.dut.p.join(","))
        conf = $ts.dut.call("mesa_vlan_vid_conf_get", vid)
        conf["ingress_filter"] = ingress_filter
        $ts.dut.call("mesa_vlan_vid_conf_set", vid, conf);
        $ts.dut.call("mesa_mstp_vlan_msti_set", vid, e[:msti])
        $ts.dut.port_list.each_with_index do |port, idx|
            state = (idx == $mstp_port_idx ? e[:state] : "FORWARDING")
            $ts.dut.call("mesa_mstp_port_msti_state_set", port, e[:msti], "MESA_STP_STATE_" + state)
        end
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    $vid_table.each do |e|
        cmd = "eth"
        cmd += cmd_tag_push({tpid: 0x8100, vid: e[:vid]})
        cmd += " data pattern cnt 64"
        $ts.dut.p.each_index do |idx_tx|
            # Determine STP/MSTP forwarding per ingress port
            fwd = ($stp_state_table[idx_tx][0] == "F" and
                   (idx_tx != $mstp_port_idx or e[:state][0] == "F"))
            
            # Determine STP/MSTP forwarding per egress port
            idx_list = []
            $ts.dut.p.each_index do |idx_rx|
                if (idx_rx != idx_tx and fwd and
                    $stp_state_table[idx_rx][0] == "F" and
                    (idx_rx != $mstp_port_idx or e[:state][0] == "F"))
                    idx_list << idx_rx
                end
            end
            run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
        end
    end
end

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api stp")
    $ts.dut.run("mesa-cmd deb api vlan")
end
