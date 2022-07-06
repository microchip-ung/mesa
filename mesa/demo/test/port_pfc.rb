#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_2x")

check_capabilities do
    c = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(c != chip_family_to_id("MESA_CHIP_FAMILY_CARACAL"), "L26 not supported")
end

#---------- Description -------------------------------------------------------
# Purpose:
# Verify that vtss_port_conf_t::flow_control::pfc (802.1Qbb PFC) is working as expected.
#
# Test procedure:
# 1. VLAN prio is enabled in the DUT
# 2. PFC prios in DUT port 1 is enabled/disabled
# 3. Data frames are sent on host port 1 with a matching priority.
# 4. Host port 2 transmits PFC frames to DUT port 2 which inhibits the port to schedule frames for some priority.
# 5. DUT port 1 sends  PFC frames back to host port 1 to make it stop transmitting (see note).
# 6. The result is verified by reading counters from the DUT.
# 7. This is repeated for each of the entry in the test_list below.
#
# Note:
# The NIC does not support 802.1Qbb PFC, i.e. it will not stop transmitting when it receives such frames (from the DUT)
# Correct DUT behaviour can still be validated by checking its counters.

#---------- Test parameters ----------------------------------------------------
$port_tx1      = 0
$port_tx2      = 1
$frame_smac    = "00:00:00:00:00:01"
$frame_dmac    = "00:00:00:00:00:02"
$pause_dmac    = "01:80:C2:00:00:01"
$pause_etype   = 0x8808
$frame_size    = 1518
$num_of_frames = 20000
$num_of_pause  = 10000
$test_list     = [
                  { port_conf_pfc:[1,0,0,0,0,0,0,0], data_frame_pcp: 0, pause_frame_pfc:[1,0,0,0,0,0,0,0]}, # PFC 0 active
                  { port_conf_pfc:[1,1,0,0,0,0,0,0], data_frame_pcp: 1, pause_frame_pfc:[1,1,0,0,0,0,0,0]}, # PFC 0 active
                  { port_conf_pfc:[1,1,1,0,0,0,0,0], data_frame_pcp: 2, pause_frame_pfc:[1,1,1,0,0,0,0,0]}, # PFC 2 active
                  { port_conf_pfc:[1,1,1,1,0,0,0,0], data_frame_pcp: 3, pause_frame_pfc:[1,1,1,1,0,0,0,0]}, # PFC 3 active
                  { port_conf_pfc:[1,1,1,1,1,0,0,0], data_frame_pcp: 4, pause_frame_pfc:[1,1,1,1,1,0,0,0]}, # PFC 4 active
                  { port_conf_pfc:[1,1,1,1,1,1,0,0], data_frame_pcp: 5, pause_frame_pfc:[1,1,1,1,1,1,0,0]}, # PFC 5 active
                  { port_conf_pfc:[1,1,1,1,1,1,1,0], data_frame_pcp: 6, pause_frame_pfc:[1,1,1,1,1,1,1,0]}, # PFC 6 active
                  { port_conf_pfc:[1,1,1,1,1,1,1,1], data_frame_pcp: 7, pause_frame_pfc:[1,1,1,1,1,1,1,1]}, # PFC 7 active
                  { port_conf_pfc:[0,1,0,0,0,0,0,0], data_frame_pcp: 0, pause_frame_pfc:[1,0,0,0,0,0,0,0]}, # PFC not active -> Port not enabled
                 ]

#---------- Configuration -----------------------------------------------------
$ts.dut.run "mesa-cmd deb port polling disable"
test("Setup learning, vlan and PCP classification") do
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

    # Enable PCP classification
    [$port_tx1, $port_tx2].each do |port|
        conf = $ts.dut.call "mesa_qos_port_conf_get", $ts.dut.p[port]
        conf["tag"]["class_enable"] = true
        for pcp in 0..7
            conf["tag"]["pcp_dei_map"][pcp][0]["prio"] = pcp
        end
        $ts.dut.call "mesa_qos_port_conf_set", $ts.dut.p[port], conf
    end
end

#---------- Frame testing -----------------------------------------------------
$test_list.each do |entry|
    test("PFC port conf:'#{entry[:port_conf_pfc]}' Data frame PCP:'#{entry[:data_frame_pcp]}' Pause frame PFC:'#{entry[:data_frame_pcp]}'") do
        # DUT port PFC configuration
        conf_pfc = entry[:port_conf_pfc]
        [$port_tx1, $port_tx2].each do |port_tx|
            conf = $ts.dut.call "mesa_port_conf_get", $ts.dut.p[port_tx]
            fc = {obey:false,
                  generate:false,
                  smac:{addr:[0,1,2,3,4,5]},
                  pfc:[]}
            for i in 0..7
                fc[:pfc][i] = (conf_pfc[i] == 0 ? false : true);
            end
            conf["flow_control"] = fc
            #conf["max_frame_length"] = conf["max_frame_length"] + 1
            $ts.dut.call "mesa_port_conf_set", $ts.dut.p[port_tx], conf
        end

        # Frame config
        tag = "ctag vid 1 pcp #{entry[:data_frame_pcp]} "
        pause_frame_pfc = entry[:pause_frame_pfc]
        pause_str = "010100ff"
        (0..7).each do |prio|
            pause_str += "00"
            pause_str += ((pause_frame_pfc[prio] == 1) ? "ff" : "00")
        end

        $ts.dut.run "mesa-cmd port statis clear"

        sz = $frame_size - 14 - 4 - 4
        cmd =  "sudo ef -c #{$ts.pc.p[$port_tx1]},20,adapter_unsynced,,1000 "
        cmd += "name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} #{tag} data pattern cnt #{sz} "
        cmd += "tx #{$ts.pc.p[$port_tx1]} rep #{$num_of_frames} name f#{$port_tx1} "
        $ts.pc.try cmd

        test ("Check that no Pause frame is received") do
        pkts = $ts.pc.get_pcap "#{$ts.pc.p[$port_tx1]}.pcap"
        for inx in 0..999
            data = pkts[inx][:data].each_byte.map{|c| c.to_i}
            if (data[12] == 0x88)
                t_e "Unexpected Pause frame received   inx #{inx} data #{data}"
                break
            end
        end
        end

        $ts.dut.run "mesa-cmd port statis clear"

        sz = $frame_size - 14 - 4 - 4
        cmd =  "sudo ef -c #{$ts.pc.p[$port_tx1]},20,adapter_unsynced,,50 "
        cmd += "name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} #{tag} data pattern cnt #{sz} "
        cmd += "name f#{$port_tx2} eth dmac #{$pause_dmac} smac #{$frame_dmac} et #{$pause_etype} data hex #{pause_str} "
        cmd += "tx #{$ts.pc.p[$port_tx1]} rep #{$num_of_frames} name f#{$port_tx1} "
        cmd += "tx #{$ts.pc.p[$port_tx2]} rep #{$num_of_pause} name f#{$port_tx2} "
        $ts.pc.try cmd

        if ((conf_pfc[entry[:data_frame_pcp]] == 1) && (pause_frame_pfc[entry[:data_frame_pcp]] == 1))
            # Pause frames are transmitted
            test ("Check the Pause frame source MAC") do
            pkts = $ts.pc.get_pcap "#{$ts.pc.p[$port_tx1]}.pcap"
            for inx in 0..49
                data = pkts[inx][:data].each_byte.map{|c| c.to_i}
                if (data[12] == 0x88)
                    t_i "inx #{inx} data #{data}"
                    break
                end
            end
            if (inx == 49)
                t_e "No Pause frame received"
            else
                if (data[6] != 0) || (data[7] != 1) || (data[8] != 2) ||
                (data[9] != 3) || (data[10] != 4) || (data[11] != 5)
                    t_e "Pause frame received with unexpected source MAC"
                end
            end
            end # end test
        end

        $ts.dut.run "mesa-cmd port statis pac"

        # Test verification
        [$ts.dut.p[$port_tx1], $ts.dut.p[$port_tx2]].each do |port|
            cnt = $ts.dut.call "mesa_port_counters_get", port
            tx_pause_cnt = cnt['ethernet_like']['dot3OutPauseFrames']
            rx_pause_cnt = cnt['ethernet_like']['dot3InPauseFrames']
            tx_frame_cnt = cnt["if_group"]["ifOutUcastPkts"]
            rx_frame_cnt = cnt["if_group"]["ifInUcastPkts"]
            rx_mc_cnt = cnt["if_group"]["ifInMulticastPkts"]

            console " Port:#{port} (Prio:#{entry[:data_frame_pcp]}) Tx-UC:#{tx_frame_cnt}  Tx-Pause:#{tx_pause_cnt} Rx-UC:#{rx_frame_cnt} Rx-MC:#{rx_mc_cnt}"

            if ((conf_pfc[entry[:data_frame_pcp]] == 1) && (pause_frame_pfc[entry[:data_frame_pcp]] == 1))
                tx_pause = true
                frameloss = true
            else
                tx_pause = false
                frameloss = false
            end
            
            if port == $ts.dut.p[$port_tx1]
                if (tx_pause)
                    if (tx_pause_cnt == 0) 
                        t_e("No tx pause frames")
                    end
                else
                    if (tx_pause_cnt > 0) 
                        t_e("Unexpected pause frames")
                    end
                end
            end
            if port == $ts.dut.p[$port_tx2]
                if (tx_pause)
                    if (rx_pause_cnt == 0)
                        t_e("No rx pause frames")
                    end
                end
                if (frameloss)
                    if (tx_frame_cnt == $num_of_frames)
                        t_e("Failure: Expected too see frameloss")
                    end
                else
                    if (tx_frame_cnt != $num_of_frames)
                        t_e("Failure: Unexpected frameloss")
                    end
                end
            end
        end
        $ts.dut.run "mesa-cmd port statis clear"
        cmd =  "sudo ef "
        cmd += "name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} "
        cmd += "name f#{$port_tx2} eth dmac #{$frame_smac} smac #{$frame_dmac} "
        cmd += "tx #{$ts.pc.p[$port_tx1]} rep 1000 name f#{$port_tx1} "
        cmd += "tx #{$ts.pc.p[$port_tx2]} rep 1000 name f#{$port_tx2} "
        $ts.pc.try cmd
        $ts.dut.run "mesa-cmd port statis pac"
        $ts.dut.run "mesa-cmd port statis 1"
        $ts.dut.run "mesa-cmd port statis 2"

    end # test
end # test_list
