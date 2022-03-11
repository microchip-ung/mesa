#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Description -------------------------------------------------------
# Purpose:
# Verify that a por bulk change is working as expected.
# This means that a number of ports can be changed without applying to HW.
# When the change is complete, the whole configuration is applied, which means that
# some time consuming functions (especially the Serdeses) can be done in parallel, speeding the config up.
# Verify frame forwarding after the change.
#
#---------- Capabilities -----------------------------------------------------
cap_check_exit("PORT_CONF_BULK")

MESA_VID_NULL = 0

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

test "test_conf" do
    t_i("Configure the test by calling the example code command")
    port_from = $ts.dut.p[0] > $ts.dut.p[3] ? $ts.dut.p[3] : $ts.dut.p[0]
    port_to   = $ts.dut.p[0] > $ts.dut.p[3] ? $ts.dut.p[0] : $ts.dut.p[3]
    $ts.dut.run("mesa-cmd example init port_conf_bulk port1 #{port_from} port2 #{port_to}")
end

test "test_run" do
    t_i("Verify with frame forwarding")
    test_frame_fwd()
end

test "test_clean_up" do
    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")

end
