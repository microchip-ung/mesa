#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Description -------------------------------------------------------
# Purpose:
# Measure and log the DUT frame buffer capacity.
#
# Test procedure:
# Host port 1 (1G) bursts a number of 1518 bytes frames to host port 2 (through the DUT).
# DUT port 2 is changed to 10M FDX.  This creates congestion and frames are stored.
# The frameburst is incremented/decremented until the buffer capacity is reached
# and the result is logged.  Very low buffer capacity will produce an error.

#---------- Test parameters ----------------------------------------------------
$port_tx1      = 0
$port_rx1      = 1
$frame_smac    = "00:00:00:00:00:01"
$frame_dmac    = "00:00:00:00:00:02"
$frame_size    = 1518
$num_of_frames = 2000  # Start burst size
$min_buf_cap   = 20000 # Error if the buffer capacity in bytes is below this number

if $ts.dut.call("mesa_capability", "MESA_CAP_MISC_FPGA") == 1
    $min_buf_cap = 8000 # Less frame buffer in FPGA
end

#---------- Configuration -----------------------------------------------------
console("Adding static entry on the last port, i.e. no need for frame learning")
entry = {
  vid_mac: { vid: 1, mac: { addr: [0,0,0,0,0,2] } },
  destination: "#{$ts.dut.p[$port_rx1]}",
  copy_to_cpu: false,
  copy_to_cpu_smac: false,
  locked: true,
  index_table: false,
  aged: false,
  cpu_queue: 0,
}
test "config" do
    $ts.dut.call "mesa_mac_table_add", entry

    # Using shaper to create a congestion
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$port_rx1])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 10000
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$port_rx1], conf)

    $ts.dut.run("mesa-cmd port flow control disable")
    t_i "Wait until DUT ports are operational"
    if !dut_port_state_up($ts.dut.port_list)
        t_e "Port state is not up"
    end
end

#---------- Frame testing -----------------------------------------------------
sz = $frame_size - 14 - 4
passed_frames = 0
failed_frames = $num_of_frames
next_frames = 0
while(true) do
    test "Try #{$num_of_frames} frames" do
        $ts.dut.run "mesa-cmd port statis clear"

        cmd =  "sudo ef name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} "
        cmd += "et 0x0800 data pattern cnt #{sz} "
        cmd += "tx #{$ts.pc.p[$port_tx1]} rep #{$num_of_frames} name f#{$port_tx1} "

        $ts.pc.try cmd
        sleep 2
        cnt = $ts.dut.call "mesa_port_counters_get", $ts.dut.p[$port_rx1]
        tx_frames = cnt['if_group']['ifOutUcastPkts']
        t_i("Sent frames:#{$num_of_frames}. Received frames:#{tx_frames}")
        if (tx_frames == $num_of_frames)
            passed_frames = $num_of_frames
            next_frames = passed_frames + (failed_frames - passed_frames - 1) / 2
        else
            failed_frames = $num_of_frames
            next_frames = failed_frames - (failed_frames - passed_frames) / 2
        end
    end
    if next_frames == $num_of_frames
        break;
    end
    $num_of_frames = next_frames;
end
buffer_cap = $num_of_frames * 1518

test "results" do
    t_i("-----------------------------------------------------------------")
    t_i("The buffer capacity is approx #{buffer_cap} bytes (#{$num_of_frames} x #{$frame_size} byte frames)")
    t_i("-----------------------------------------------------------------")
    if buffer_cap < $min_buf_cap || buffer_cap > 10000000
        t_e "The buffer capacity is failing"
    end
end

