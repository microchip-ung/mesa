#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Description -------------------------------------------------------
# Purpose:
# Verify that normal frame forwarding is working with bulk of frames
# Use all ports, port to port forwarding.
#
# Test procedure:
# Send one frame on each to ensure address learning.
# Send another frame and verify correct forwarding.
# Send bulk of frames and verify forwarding by reading the counters

#---------- Test parameters ----------------------------------------------------
$port_tx1      = 0
$port_tx2      = 1
$port_tx3      = 2
$port_tx4      = 3
$frame_smac    = "00:00:00:00:00:01"
$frame_dmac    = "00:00:00:00:00:02"
$frame_smac2   = "00:00:00:00:00:03"
$frame_dmac2   = "00:00:00:00:00:04"
$frame_size    = 64
$bulk_frames = 1000000

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

test "Address learning" do
    $ts.pc.try cmd1
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

$ts.dut.run "mesa-cmd port statis clear"
cmd2 = cmd + "tx #{$ts.pc.p[$port_tx1]} rep #{$bulk_frames} name f#{$port_tx1} "
cmd2 += "tx #{$ts.pc.p[$port_tx2]} rep #{$bulk_frames} name f#{$port_tx2} "
cmd2 += "tx #{$ts.pc.p[$port_tx3]} rep #{$bulk_frames} name f#{$port_tx3} "
cmd2 += "tx #{$ts.pc.p[$port_tx4]} rep #{$bulk_frames} name f#{$port_tx4} "

test "Bulk forwarding" do
    $ts.pc.try cmd2
    $ts.dut.run "mesa-cmd port statis pac"
    $ts.dut.p.each do |port|
        cnt = $ts.dut.call "mesa_port_counters_get", port
        tx_frames = cnt['if_group']['ifOutUcastPkts']
        #symbol_err = cnt['ethernet_like']['dot3StatsSymbolErrors']
        if (tx_frames != $bulk_frames) 
            t_e("Unexpected framloss port #{port} Tx:#{$bulk_frames} Rx:#{tx_frames}")
        else
            t_i("Port #{port} Tx:#{$bulk_frames} Rx:#{tx_frames} - OK")
        end
        #if (symbol_err > 0)
        #    t_e("Unexpected symbol errors (#{symbol_err}) port #{port}")
        #end
    end    
end

