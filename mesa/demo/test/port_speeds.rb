#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Capabilities -----------------------------------------------------
hdx_support = true
check_capabilities do
    conf = $ts.dut.call "mesa_port_conf_get", $ts.dut.p[0]
    assert(!(conf["if_type"] != "MESA_PORT_INTERFACE_SGMII" &&
             conf["if_type"] != "MESA_PORT_INTERFACE_QSGMII"),
           "SGMII support is required")

    c = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    if (c == chip_family_to_id("MESA_CHIP_FAMILY_SERVALT"))
        hdx_support = false
    end
end

#---------- Description -------------------------------------------------------
# Purpose:
# Verify that the speed and duplex settings can be changed to all legal values.
# Change the speed and duplex of an port and verify normal switch functionality with
# frame transmission/reception on host ports.
# Note that forcing the switch port speed will cause the host port to go to
# half duplex mode. Address learning is performed by adding static mac-addresses.
#
# Test procedure:
# 1) Host port 'a' transmits unicast frames to host port 'b' and vice versa (through the DUT)
# 2) Verify no frameloss
# 3) This is repeated for each entry in speed_list below

#---------- Test parameters ----------------------------------------------------
$port_tx1   = 0
$port_tx2   = 1
$frame_smac = "00:00:00:00:00:01"
$frame_dmac = "00:00:00:00:00:02"
$frame_size = 64
$num_of_frames = 1
$speed_list = [{ speed: 100,    dpx: "fdx"},
               { speed: 100,    dpx: "hdx"},
               { speed: 10,     dpx: "fdx"},
               { speed: 10,     dpx: "hdx"},
               { speed: "auto", dpx: ""}]
 
#---------- Configuration and Frame testing -----------------------------------------------------
sz = $frame_size - 14 - 4
cmd =  "sudo ef "
cmd += "name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} et 0x0800 data pattern cnt #{sz} "
cmd += "name f#{$port_tx2} eth dmac #{$frame_smac} smac #{$frame_dmac} et 0x0800 data pattern cnt #{sz} "
cmd += "tx #{$ts.pc.p[$port_tx1]} name f#{$port_tx1} "
cmd += "tx #{$ts.pc.p[$port_tx2]} name f#{$port_tx2} "
cmd += "rx #{$ts.pc.p[$port_tx2]} name f#{$port_tx1} "
cmd += "rx #{$ts.pc.p[$port_tx1]} name f#{$port_tx2} "

$speed_list.each do |spd_entry|
    test "Mode:'#{spd_entry[:speed]}#{spd_entry[:dpx]} Sending #{$num_of_frames} #{$frame_size} byte frames between ports #{$port_tx1} and #{$port_tx2}" do
        if spd_entry[:dpx] == "hdx" && !hdx_support
            next
        end
        speed = spd_entry[:speed]
        duplex = spd_entry[:dpx]
        cli_port1 = $ts.dut.p[$port_tx1] + 1
        cli_ports = cli_port1.to_s
        $ts.dut.run "mesa-cmd port mode #{cli_ports} #{speed}#{duplex}"
        t_i "Wait until DUT ports are operational"
        sleep 5
        for i in 1..10 do
            if !dut_port_state_up($ts.dut.port_list)
                sleep 2
            else
                break;
            end
        end
        # Get port statis in case of failures
        $ts.dut.run("mesa-cmd port statis clear")
        $ts.pc.run cmd
        $ts.dut.run("mesa-cmd port statis pac")
    end
end
