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

test_summary
