#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Description -------------------------------------------------------
# Purpose:
# Verify that a dynamic port change (within a serdes) is working as expected.
# This means that ports within a serdes can go from 4->1 and 1->4 without disturbing traffic on other ports.
# A complete SQA test would require boards supporting hot-plugging out/in different cards.
# We don't have such a setup, so we only test that we can perform the change with CLI commands and inspcet that the API looks correct.
# Also verify traffic after the change.
#
# Note this test is identical to the port_dynamic.rb test - but is using an example code instead of the demo-cli.
#
# Test procedure:
# Use example code in port_dynamic to change port mode and to inspect the changes
# 1. Change a QSGMII port to 5G or 10G
# 2. Verify that the core BW for that port is 5G/10G and none for other ports
# 3. Verify that the phys are deleted
# 4. Verify that the interface type is as expeted
# 5. Change the port back to QSGMII
# 6. Verify that the core BW for all ports is 1G
# 7. Verify that the phys are back
# 8. Verify that the interface type is as expeted
# 9. Verify normal traffic forwarding

#---------- Capabilities -----------------------------------------------------
cap_check_exit("PORT_DYNAMIC")


check_capabilities do
    [$ts.dut.p[0], $ts.dut.p[1], $ts.dut.p[2], $ts.dut.p[3]].each do |port_tx|
        conf = $ts.dut.call "mesa_port_conf_get", port_tx
        if conf["if_type"].include? "QSGMII"
        else
            assert(0==1, "all 4 interfaces must be QSGMII")
        end
    end
end

def test_frame_fwd()
    test "Frame-Forwarding" do
        $port_tx1      = 0
        $port_tx2      = 1
        $port_tx3      = 2
        $port_tx4      = 3
        $frame_smac    = "00:00:00:00:00:01"
        $frame_dmac    = "00:00:00:00:00:02"
        $frame_smac2   = "00:00:00:00:00:03"
        $frame_dmac2   = "00:00:00:00:00:04"
        $frame_size    = 64

        sz = $frame_size - 14 - 4
        cmd =  "sudo ef name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} data pattern cnt #{sz} "
        cmd += "name f#{$port_tx2} eth dmac #{$frame_smac} smac #{$frame_dmac} data pattern cnt #{sz} "
        cmd += "name f#{$port_tx3} eth dmac #{$frame_dmac2} smac #{$frame_smac2} data pattern cnt #{sz} "
        cmd += "name f#{$port_tx4} eth dmac #{$frame_smac2} smac #{$frame_dmac2} data pattern cnt #{sz} "

        cmd1 = cmd + "tx #{$ts.pc.p[$port_tx1]} name f#{$port_tx1} "
        cmd1 += "tx #{$ts.pc.p[$port_tx2]} name f#{$port_tx2} "
        cmd1 += "tx #{$ts.pc.p[$port_tx3]} name f#{$port_tx3} "
        cmd1 += "tx #{$ts.pc.p[$port_tx4]} name f#{$port_tx4} "

        test "Address learning" do
            $ts.pc.try cmd1
            sleep (2)
        end
        $ts.dut.run "mesa-cmd port statis clear"
        cmd1 += "rx #{$ts.pc.p[$port_tx1]} name f#{$port_tx2} "
        cmd1 += "rx #{$ts.pc.p[$port_tx2]} name f#{$port_tx1} "
        cmd1 += "rx #{$ts.pc.p[$port_tx3]} name f#{$port_tx4} "
        cmd1 += "rx #{$ts.pc.p[$port_tx4]} name f#{$port_tx3} "

        test "Frame forwarding and receiving" do
            $ts.pc.try cmd1
            $ts.dut.run "mesa-cmd port statis pac"
        end
    end
end

$ts.dut.run("mesa-cmd deb port poll disable")
port_to_change = $ts.dut.p[0]

test "1 port per Serdes in SFI mode" do
    t_i("Configure the test by calling the example code command with interface SFI/5G")
    $ts.dut.run("mesa-cmd example init port_dynamic port_to_change #{port_to_change} interface 0")
    $ts.dut.run("mesa-cmd example uninit")
    $ts.dut.run("mesa-cmd deb api ail port")
end

test "4 ports per Serdes in QSGMII mode" do
    t_i("Configure the test by calling the example code command with interface QSGMII")
    $ts.dut.run("mesa-cmd example init port_dynamic port_to_change #{port_to_change} interface 1")
    $ts.dut.run("mesa-cmd example uninit")
    $ts.dut.run("mesa-cmd deb api ail port")
end

# Skipping for now as the xilinx FPGA serdes needs a reset before forwarding is possible
# test "test_run" do
#     sleep 5
#     t_i("Verify with frame forwarding")
#     test_frame_fwd()
# end
