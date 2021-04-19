#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Description -------------------------------------------------------
# Purpose:
# Verify that vtss_port_conf_t::flow_control is working as expected.
# vtss_port_conf_t:flow_control:obey     : Obey flow control frames and pause frame transmission
# vtss_port_conf_t:flow_control:generate : Generate flow control frames when the buffer is above some limit
# Change the parameters and verify that the effect is as expected (frameloss / no loss / FC obey / FC gen).
# Also verify flow control counters.
#
# Test procedure:
# Host port 1 transmits unicast frames to host port 2 (through the DUT)
# Host port 2 transmits flowcontrol frames which inhibits the DUT port to forward the frames (when enabled)


#---------- Test parameters ----------------------------------------------------
$port_tx1      = 0
$port_tx2      = 1
$frame_smac    = "00:00:00:00:00:01"
$frame_dmac    = "00:00:00:00:00:02"
$pause_dmac    = "01:80:C2:00:00:01"
$pause_etype   = 0x8808
$frame_size    = 1518
$num_of_frames = 10000
$test_list     = [
  { obey:false, generate:false, rx_pause_cnt:true,  tx_pause_cnt:false, frameloss:false },
  { obey:false, generate:true,  rx_pause_cnt:true,  tx_pause_cnt:false, frameloss:false },
  { obey:true,  generate:true,  rx_pause_cnt:true,  tx_pause_cnt:true,  frameloss:false },
]

#---------- Configuration -----------------------------------------------------
console "Adding static entry on the last port, i.e. no need for frame learning"
entry = {
  vid_mac: { vid: 1, mac: { addr: [0,0,0,0,0,2] } },
  destination: "#{$ts.dut.p[$port_tx2]}",
  copy_to_cpu: false,
  copy_to_cpu_smac: false,
  locked: true,
  index_table: false,
  aged: false,
  cpu_queue: 0,
}
$ts.dut.call "mesa_mac_table_add", entry


#---------- Frame testing -----------------------------------------------------
sz = $frame_size - 14 - 4
cmd =  "sudo ef name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} "
cmd += "et 0x0800 data pattern cnt #{sz} "

cmd +=  "name f#{$port_tx2} eth dmac #{$pause_dmac} smac #{$frame_dmac} "
cmd += "et #{$pause_etype} data hex 00:01:ff:ff "
cmd += "tx #{$ts.pc.p[$port_tx1]} rep #{$num_of_frames} name f#{$port_tx1} "
cmd += "tx #{$ts.pc.p[$port_tx2]} rep #{$num_of_frames} name f#{$port_tx2} "


$test_list.each do |entry|
    test "Obey:'#{entry[:obey]}' Generate:'#{entry[:generate]}' rx_pause_cnt:'#{entry[:rx_pause_cnt]}'\
         tx_pause_cnt:'#{entry[:tx_pause_cnt]}' frameloss:'#{entry[:frameloss]}'" do

      [$ts.dut.p[$port_tx1], $ts.dut.p[$port_tx2]].each do |port_tx|
          conf = $ts.dut.call "mesa_port_conf_get", port_tx
          conf["flow_control"] = {obey:entry[:obey],
                                  generate:entry[:generate],
                                  smac:{addr:[0,1,2,3,4,5]},
                                  pfc:[false,false,false,false,false,false,false,false]}
          $ts.dut.call "mesa_port_conf_set", port_tx, conf
          $ts.dut.call "mesa_port_counters_clear", port_tx

      end

      $ts.pc.try cmd
      [$ts.dut.p[$port_tx1], $ts.dut.p[$port_tx2]].each do |port|
          cnt = $ts.dut.call "mesa_port_counters_get", port
          rx_pause = cnt['ethernet_like']['dot3InPauseFrames']
          tx_pause = cnt['ethernet_like']['dot3OutPauseFrames']
          tx_frames = cnt['if_group']['ifOutUcastPkts']

          if port == $ts.dut.p[$port_tx1]
              t_i("#{$port_tx1} RX pause #{rx_pause}")
              if (entry[:tx_pause_cnt] && (tx_pause == 0))
                  t_e("No tx pause frames")
              end
              if (!entry[:tx_pause_cnt] && (tx_pause > 0))
                  t_e("Unexpected pause frames")
              end
          end
          if port == $ts.dut.p[$port_tx2]
              t_i("#{$port_tx2} RX pause #{rx_pause}")
              if (entry[:rx_pause_cnt] && (rx_pause != $num_of_frames))
                  t_e("No rx pause frames seen: #{entry[:rx_pause_cnt]} port #{$port_tx2} #{rx_pause}")
              end
              if (!entry[:rx_pause_cnt] && (rx_pause > 0))
                  t_e("Unexpected pause frames seen")
              end
              if (entry[:frameloss] && (tx_frames == $num_of_frames))
                  t_e("Expected to see frameloss!")
              end
              if (!entry[:frameloss] && (tx_frames != $num_of_frames))
                  t_e("Unexpected frameloss tx:#{tx_frames} rx:#{$num_of_frames} ")
              end
          end
      end
  end
end
