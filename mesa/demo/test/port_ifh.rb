#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

$idx_normal = 0
$idx_inj = 1
$idx_xtr = 2

test "ifh-conf" do
    [$idx_inj, $idx_xtr].each do |idx|
        port = $ts.dut.p[idx]
        conf = $ts.dut.call("mesa_port_ifh_conf_get", port)
        fld = (idx == $idx_inj ? "ena_inj_header" : "ena_xtr_header")
        conf[fld] = true
        $ts.dut.call("mesa_port_ifh_conf_set", port, conf)
    end
end

test "inj-to-normal" do
    f = "eth data pattern cnt 46"
    cmd = "ef name f_inj "
    cmd += cmd_tx_ifh_push({"dst_port": $ts.dut.p[$idx_normal]})
    cmd += "#{f} name f_normal #{f} "
    cmd += "tx #{$ts.pc.p[$idx_inj]} name f_inj "
    cmd += "rx #{$ts.pc.p[$idx_normal]} name f_normal "
    cmd += "rx #{$ts.pc.p[$idx_xtr]}"
    $ts.pc.run(cmd)
end

test "normal-to-xtr" do
    f = "eth data pattern cnt 46"
    cmd = "ef name f_normal #{f} name f_xtr "
    cmd += cmd_rx_ifh_push({port_idx: $idx_normal})
    cmd += "#{f} "
    cmd += "tx #{$ts.pc.p[$idx_normal]} name f_normal "
    cmd += "rx #{$ts.pc.p[$idx_xtr]} name f_xtr "
    cmd += "rx #{$ts.pc.p[$idx_inj]} name f_normal"
    $ts.pc.run(cmd)
end

test "xtr-match_id" do
    if (cap_get("PACKET_RX_MATCH_ID") == 0)
        break
    end

    # Set match ID bit 0-7 using VCL
    port = $ts.dut.port_list[$idx_normal]
    vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
    vce["id"] = 1
    vce["key"]["port_list"] = "#{port}"
    action = vce["action"]
    action["match_id"] = 0x34
    action["match_mask"] = 0xff
    $ts.dut.call("mesa_vce_add", 0, vce)

    # Set match ID bit 8-15 using ACL
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ANY")
    ace["id"] = 1
    ace["port_list"] = "#{port}"
    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
    action["port_list"] = "#{$ts.dut.port_list[$idx_xtr]}"
    action["match_id"] = 0x1200
    action["match_mask"] = 0xff00
    $ts.dut.call("mesa_ace_add", 0, ace)

    f = "eth data pattern cnt 46"
    cmd = "ef name f_normal #{f} name f_xtr "
    cmd += cmd_rx_ifh_push({match_id: 0x1234})
    cmd += "#{f} "
    cmd += "tx #{$ts.pc.p[$idx_normal]} name f_normal "
    cmd += "rx #{$ts.pc.p[$idx_xtr]} name f_xtr "
    $ts.pc.run(cmd)
end

test_summary

test "dump" do
    #$ts.dut.run("mesa-cmd deb api ci vx action 3")
    #$ts.dut.run("mesa-cmd deb api ci acl action 3")
end
