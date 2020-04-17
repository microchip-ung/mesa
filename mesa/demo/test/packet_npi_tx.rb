#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_npi   = 0
$idx_rx    = 1
$idx_other = 2

test "conf" do
    t_i("NPI port")
    conf = $ts.dut.call("mesa_npi_conf_get")
    conf["enable"] = true
    conf["port_no"] = $ts.dut.p[$idx_npi]
    $ts.dut.call("mesa_npi_conf_set", conf)
end

#---------- Frame testing -----------------------------------------------------

test "tx-port" do
    f2 = "eth data pattern cnt 46"
    f1 = (cmd_tx_ifh_push({"dst_port": $ts.dut.p[$idx_rx]}) + f2)
    cmd = "sudo ef name f1 #{f1} name f2 #{f2} "
    cmd += "tx #{$ts.pc.p[$idx_npi]} name f1 "
    cmd += "rx #{$ts.pc.p[$idx_rx]} name f2 "
    cmd += "rx #{$ts.pc.p[$idx_other]}"
    $ts.pc.run(cmd)
end

test "tx-vlan" do
    f_end = " data pattern cnt 46"
    f2 = ("eth" + f_end)
    f1 = (cmd_tx_ifh_push({"switch_frm": true}) + "eth" + cmd_tag_push({tpid: 0x8100, vid: 1}) + f_end)
    cmd = "sudo ef name f1 #{f1} name f2 #{f2} "
    cmd += "tx #{$ts.pc.p[$idx_npi]} name f1 "
    cmd += "rx #{$ts.pc.p[$idx_rx]} name f2 "
    cmd += "rx #{$ts.pc.p[$idx_other]} name f2"
    $ts.pc.run(cmd)
end

