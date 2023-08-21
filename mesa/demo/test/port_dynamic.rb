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
# Test procedure:
# Use debug commands (#deb port dynamic.. ) to change port mode and to inspect the changes
# 1. Change a QSGMII port to 5G or 10G
# 2. Verify that the core BW for that port is 10G and none for other ports
# 3. Verify that the phys are deleted
# 4. Verify that the interface type is as expeted
# 5. Change the port back to QSGMII
# 6. Verify that the core BW for all ports is 1G
# 7. Verify that the phys are back
# 8. Verify that the interface type is as expeted
# 9. Verify normal traffic forwarding

#---------- Capabilities -----------------------------------------------------
cap_check_exit("PORT_DYNAMIC")

#---------- Configuration and Test -----------------------------------------------------

# Always take the first 4 ports
$p1 = 1
$p2 = 2
$p3 = 3
$p4 = 4
$is_fpga = 0

$test_with_traffic = false

check_capabilities do
    [$p1-1, $p2-1, $p3-1, $p4-1].each do |port_tx|
        conf = $ts.dut.call "mesa_port_conf_get", port_tx
    $ts.dut.run "mesa-cmd deb api port #{$p2} full"

        if conf["if_type"].include? "QSGMII"
        else
            assert(0==1, "all 4 interfaces must be QSGMII")
        end
    end
    $is_fpga = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_FPGA")
end



# PCB-135 Test config:
# p1 = 16
# p2 = 15
# p3 = 14
# p4 = 13

#---------- Frame testing -----------------------------------------------------
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

def bulk_frame_fwd_bg()
    #---------- Test parameters ----------------------------------------------------
    $port_tx1      = 0
    $port_tx2      = 1
    $port_tx3      = 2
    $port_tx4      = 3
    $frame_smac    = "00:00:00:00:00:01"
    $frame_dmac    = "00:00:00:00:00:02"
    $frame_smac2   = "00:00:00:00:00:03"
    $frame_dmac2   = "00:00:00:00:00:04"
    $frame_size    = 1000
    $bulk_frames = 2000000

    #---------- Frame testing -----------------------------------------------------
    sz = $frame_size - 14 - 4
    cmd =  "sudo ef name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} data pattern cnt #{sz} "
    cmd += "name f#{$port_tx2} eth dmac #{$frame_smac} smac #{$frame_dmac} data pattern cnt #{sz} "
    cmd += "name f#{$port_tx3} eth dmac #{$frame_dmac2} smac #{$frame_smac2} data pattern cnt #{sz} "
    cmd += "name f#{$port_tx4} eth dmac #{$frame_smac2} smac #{$frame_dmac2} data pattern cnt #{sz} "

    cmd1 = cmd + "tx #{$ts.pc.p[$port_tx1]} name f#{$port_tx1} "
    cmd1 += "tx #{$ts.pc.p[$port_tx2]} name f#{$port_tx2} "
    cmd1 += "tx #{$ts.pc.p[$port_tx3]} name f#{$port_tx3} "
    cmd1 += "tx #{$ts.pc.p[$port_tx4]} name f#{$port_tx4} "
    $ts.pc.try cmd1

    $ts.dut.run "mesa-cmd port statis clear"
    cmd2 = cmd + "tx #{$ts.pc.p[$port_tx1]} rep #{$bulk_frames} name f#{$port_tx1} "
    cmd2 += "tx #{$ts.pc.p[$port_tx2]} rep #{$bulk_frames} name f#{$port_tx2} "
    cmd2 += "tx #{$ts.pc.p[$port_tx3]} rep #{$bulk_frames} name f#{$port_tx3} "
    cmd2 += "tx #{$ts.pc.p[$port_tx4]} rep #{$bulk_frames} name f#{$port_tx4} "

    pid_ef = []
    pid_ef << $ts.pc.bg("ef tx", "#{cmd2}")
end

$ts.dut.run "mesa-cmd deb port poll dis"
test "Test with traffic" do
    if ($test_with_traffic)
        bulk_frame_fwd_bg()
        $ts.dut.run "mesa-cmd deb api port #{$p2} full"
        sleep (5)
        res4 = $ts.dut.run "mesa-cmd deb port dynamic 5 1000fdx force"
        sleep (15)
        $ts.dut.run "mesa-cmd port statis pac"
        $ts.dut.run "mesa-cmd deb api port #{$p2} full"
        exit
    end
end

test "Change-To-1x10G" do
    $ts.dut.run "mesa-cmd deb api port #{$p2} full"
    cmd_res = $ts.dut.run "mesa-cmd deb port dynamic #{$p1} 10g force"
    if (cmd_res[:out].include?("Error"))
        t_e "Could not perfom command in API"
    end
    res1 = $ts.dut.run "mesa-cmd deb port dynamic #{$p1} force"
    res2 = $ts.dut.run "mesa-cmd deb port dynamic #{$p2} force"
    res3 = $ts.dut.run "mesa-cmd deb port dynamic #{$p3} force"
    res4 = $ts.dut.run "mesa-cmd deb port dynamic #{$p4} force"
    if !res1[:out].include?("BW-10") || !res2[:out].include?("BW-None") || !res3[:out].include?("BW-None") || !res4[:out].include?("BW-None")
        t_e("Error in SW-core BW")
    end
    if !res1[:out].include?("No-Phy") || !res2[:out].include?("No-Phy") || !res3[:out].include?("No-Phy") || !res4[:out].include?("No-Phy")
        t_e("Error in phy status")
    end
    if !res1[:out].include?("SFI") || !res2[:out].include?("N/C") || !res3[:out].include?("N/C") || !res4[:out].include?("N/C")
        t_e("Error in interface mode")
    end
    $ts.dut.run "mesa-cmd deb port dynamic force"
    $ts.dut.run "mesa-cmd deb api port #{$p2} full"
end

test "Change-To-4xQSGMII" do
    cmd_res = $ts.dut.run "mesa-cmd deb port dynamic #{$p1} 1000fdx force"
    if (cmd_res[:out].include?("Error"))
        t_e "Could not perfom command in API"
    end
    res1 = $ts.dut.run "mesa-cmd deb port dynamic #{$p1} force"
    res2 = $ts.dut.run "mesa-cmd deb port dynamic #{$p2} force"
    res3 = $ts.dut.run "mesa-cmd deb port dynamic #{$p3} force"
    res4 = $ts.dut.run "mesa-cmd deb port dynamic #{$p4} force"
    if !res1[:out].include?("BW-1G") || !res2[:out].include?("BW-1G") || !res3[:out].include?("BW-1G") || !res4[:out].include?("BW-1G")
        t_e("Error in SW-core BW")
    end
    if res1[:out].include?("No-Phy") || !res2[:out].include?("No-Phy") || !res3[:out].include?("No-Phy") || !res4[:out].include?("No-Phy")
        t_e("Error in phy status")
    end
    if !res1[:out].include?("QSGMII") || !res2[:out].include?("N/C") || !res3[:out].include?("N/C") || !res4[:out].include?("N/C")
        t_e("Error in interface mode")
    end
    $ts.dut.run "mesa-cmd deb port dynamic #{$p2},#{$p3},#{$p4} 1000fdx force"
    res2 = $ts.dut.run "mesa-cmd deb port dynamic #{$p2} force"
    res3 = $ts.dut.run "mesa-cmd deb port dynamic #{$p3} force"
    res4 = $ts.dut.run "mesa-cmd deb port dynamic #{$p4} force"

    if !res2[:out].include?("QSGMII") || !res3[:out].include?("QSGMII") || !res4[:out].include?("QSGMII")
        t_e("Error in interface mode")
    end
    $ts.dut.run "mesa-cmd deb api port #{$p2} full"
    $ts.dut.run "mesa-cmd deb port dynamic force"
end
if $is_fpga == 0
    test "Verify frame forwarding" do
        sleep (5)
        test_frame_fwd()
    end
end
