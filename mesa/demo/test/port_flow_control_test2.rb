#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Description -------------------------------------------------------
# Purpose:
# Verify that vtss_port_conf_t::flow_control is working as expected.
# Use different port speeds to create congestion in the DUT with the expected frameloss / no frameloss .
#
# Test procedure:
# Host port 1 and 3 (DUT ingress) transmits unicast frames to host port 2 (through the DUT)
# Host port 2 (DUT egress) changes to different speeds which leads to different congestion in the DUT.
# Frameloss / no frameloss is verified.
#
# Note: Host ports must run @ 1G to react upon flowcontrol frames (for some unknown reason).

#---------- Test parameters ----------------------------------------------------
$port_tx1      = 0
$port_rx1      = 1
$port_tx2      = 2
$frame_smac    = "00:00:00:00:00:01"
$frame_dmac    = "00:00:00:00:00:02"
$frame_size    = 512
$num_of_frames = 10000
$test_list     = [{ speed_in:"1000fdx", speed_out:"100fdx",  flowcontrol:true },
                  { speed_in:"1000fdx", speed_out:"10fdx",   flowcontrol:true },
                  { speed_in:"1000fdx", speed_out:"10fdx",   flowcontrol:false},
                  { speed_in:"1000fdx", speed_out:"1000fdx", flowcontrol:true },
                  { speed_in:"auto",    speed_out:"auto",    flowcontrol:false},
                 ]

#---------- Configuration -----------------------------------------------------

console("Adding static entry on the last port, i.e. no need for frame learning")
entry = {
  vid_mac: { vid: 1, mac: { addr: [0,0,0,0,0,2] } },
  destination: "#{$ts.dut.p[$port_rx1]}",
  copy_to_cpu: false,
  copy_to_cpu_smac: false,
  locked: true,
  aged: false,
  cpu_queue: 0,
}
$ts.dut.call "mesa_mac_table_add", entry

#---------- Frame testing -----------------------------------------------------
sz = $frame_size - 14 - 4

$test_list.each do |entry|
    test ("Speed in:'#{entry[:speed_in]}' Speed out:'#{entry[:speed_out]}' Flowcontrol:'#{entry[:flowcontrol]}'}'") do
        speed_in = entry[:speed_in]
        speed_out = entry[:speed_out]
        if (speed_in == "auto") && (speed_out == "auto")
            $num_of_frames = $num_of_frames * 10
        end
        if (speed_in == "1000fdx") && (speed_out == "1000fdx")
            $num_of_frames = $num_of_frames * 10
        end
        cmd =  "sudo ef name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} "
        cmd += "et 0x0800 data pattern cnt #{sz} "
        cmd += "tx #{$ts.pc.p[$port_tx1]} rep #{$num_of_frames} name f#{$port_tx1} "
        cmd += "tx #{$ts.pc.p[$port_tx2]} rep #{$num_of_frames} name f#{$port_tx1} "

        cli_port_tx1 = $ts.dut.p[$port_tx1] + 1
        cli_port_rx = $ts.dut.p[$port_rx1] + 1
        cli_port_tx2 = $ts.dut.p[$port_tx2] + 1        
        cli_ports = cli_port_tx1.to_s + ',' + cli_port_tx2.to_s
        $ts.dut.run "mesa-cmd port mode #{cli_ports} #{speed_in}"
        ena = "disable"
        if entry[:flowcontrol]
            ena = "enable"
        end
        $ts.dut.run "mesa-cmd port flow control #{cli_ports} #{ena}"

        # Using shaper to create a congestion
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$port_rx1])
        conf["shaper"]["level"] = 1
        if speed_out == "1000fdx" || speed_out == "auto"
            conf["shaper"]["rate"] = 0xFFFFFFFF
        elsif speed_out == "100fdx"
            conf["shaper"]["rate"] = 100*1000
        else
            conf["shaper"]["rate"] = 10*1000
        end
        conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
#        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$port_rx1], conf)


        # $ts.dut.run "mesa-cmd port mode #{cli_port_rx} #{speed_out}"

        $ts.dut.run "mesa-cmd port statis clear"

        t_i "Wait until DUT ports are operational"
        if !dut_port_state_up($ts.dut.port_list)
            t_e "Port state is not up"
        end
        sleep 10
        $ts.pc.try cmd

        cnt_tx1 = $ts.dut.call "mesa_port_counters_get", $ts.dut.p[$port_tx1]
        cnt_tx2 = $ts.dut.call "mesa_port_counters_get", $ts.dut.p[$port_tx2]
        cnt_rx = $ts.dut.call "mesa_port_counters_get", $ts.dut.p[$port_rx1]
        rx_frames = cnt_tx1['if_group']['ifInUcastPkts'] + cnt_tx2['if_group']['ifInUcastPkts']
        tx_frames = cnt_rx['if_group']['ifOutUcastPkts']
        tx_pause  = cnt_tx1['ethernet_like']['dot3OutPauseFrames']
        rx_pause  = cnt_tx1['ethernet_like']['dot3InPauseFrames']

        t_i "DUT rx:#{rx_frames} tx:#{tx_frames} tx_pause:#{tx_pause} rx_pause:#{rx_pause}"

        if (entry[:flowcontrol] && (tx_pause == 0))
            t_e("No Pause frames sent!")
        end
        if (entry[:flowcontrol] && (tx_frames != rx_frames))
            t_e("Unexpected frameloss!")
        end
        if (!entry[:flowcontrol])
            if ((tx_frames == 0) || (tx_frames >= rx_frames))
                t_e("Expected to see frameloss!")
            end
        end
    end
end

