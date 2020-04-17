#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

vid_x = 100
vid_y = 200
vid_z = 300

$vid_table = [ { vid: vid_x, tag: "PORT" },
               { vid: vid_y, tag: "DISABLE" },
               { vid: vid_z, tag: "ENABLE" } ]
$uvid_table = [ 0, vid_x, vid_y, 4096 ]

test "conf" do
    t_i("Set VLAN port configuration")
    $ts.dut.port_list.each_with_index do |port, idx|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["untagged_vid"] = $uvid_table[idx]
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end
    
    t_i("Set VLAN memberships and Tx tagging")
    port_cnt = cap_get("PORT_CNT")
    $vid_table.each do |entry|
        vid = entry[:vid]
        $ts.dut.call("mesa_vlan_port_members_set", vid, $ts.dut.p.join(","))

        tx_tag = $ts.dut.call("mesa_vlan_tx_tag_get", vid, port_cnt)
        $ts.dut.port_list.each do |port|
            tx_tag[port] = ("MESA_VLAN_TX_TAG_" + entry[:tag])
        end
        $ts.dut.call("mesa_vlan_tx_tag_set", vid, port_cnt, tx_tag)
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    $vid_table.each do |entry|
        vid = entry[:vid]
        tx_cfg = entry[:tag][0]
        $ts.dut.p.each_index do |idx_tx|
            cmd = "sudo ef"
            cmd_end = ""
            $ts.dut.p.each_index do |idx_rx|
                tag = { tpid: 0x8100, vid: vid }
                dir = "tx"
                if (idx_rx != idx_tx)
                    dir = "rx"
                    uvid = $uvid_table[idx_rx]
                    if (tx_cfg == "D" or (tx_cfg == "P" and (uvid == 4096 or uvid == vid)))
                        # Tx untagged
                        tag[:tpid] = 0
                    end
                end
                cmd_name = " name f#{idx_rx}"
                cmd += cmd_name
                cmd += " eth"
                cmd += cmd_tag_push(tag)
                cmd += " data pattern cnt 64"
                cmd_end += " #{dir} #{$ts.pc.p[idx_rx]}"
                cmd_end += cmd_name
            end
            $ts.pc.run(cmd + cmd_end)
        end
    end
end
