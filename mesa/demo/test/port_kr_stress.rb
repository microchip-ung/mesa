#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Description -------------------------------------------------------
# Purpose:
# Stress test KR
#
# Test procedure:
# 1. Create 2 VLANs with p1 + loop port 1 in VLAN-2 and p2 and loop port 2 in VLAN-3,
#    to allow frame forwarding from port 1 --> loop --> port 2
# 2. Aneg and train at 10G/25g
# 3. Run line rate traffic for a few seconds over the link
# 4. Verify no framesloss
# 5. Do shut/no shutdown on KR link - link should re-train
# 6. Repeat steps 3-5 10 times

#---------- Configuration -----------------------------------------------------

check_capabilities do
    cap_kr = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_KR_IRQ")
    assert(cap_kr != 0, "KR IRQ must be supported")
end

repeat_test = 10
plist = []
if $ts.dut.looped_port_list != nil && $ts.dut.looped_port_list_10g != nil
    plist = $ts.dut.looped_port_list + $ts.dut.looped_port_list_10g
elsif $ts.dut.looped_port_list != nil
    plist = $ts.dut.looped_port_list
    $ts.dut.looped_port_list_10g = []
elsif $ts.dut.looped_port_list_10g != nil
    plist = $ts.dut.looped_port_list_10g
    $ts.dut.looped_port_list = []
end

kr_ports = []
test "Config" do
    plist.each do |idx|
        conf = $ts.dut.call "mesa_port_conf_get", idx
        if conf["serdes"]["media_type"].include? "DAC"
            kr_ports << idx
        end
    end
end

cap25 = ""
speed = []
speed_cap = []
$cli_port = ""
check_capabilities do
    assert((kr_ports.count > 0), "DAC based loop ports must be supported (#{kr_ports.count})")

    conf = $ts.dut.call("mesa_port_conf_get", kr_ports[0])
    if (conf["speed"] == "MESA_SPEED_25G")
        cap25 = "adv-25g"
        speed = ['25g', '10g', '5g', '2500', '1000fdx', '25g']
        speed_cap = ['adv-1g', 'adv-2g5', 'adv-5g', 'adv-10g', 'adv-25g']
    elsif (conf["speed"] == "MESA_SPEED_10G")
        speed = ['10g', '5g', '2500', '1000fdx', '10g']
        speed_cap = ['adv-1g', 'adv-2g5', 'adv-5g', 'adv-10g']
    end
    assert((speed_cap.count > 0), "Loop ports must be 10G or 25G")
end

###### Frame transmit profile ########
$port_tx1      = 0
$port_tx2      = 1
$frame_smac    = "00:00:00:00:00:01"
$frame_dmac    = "00:00:00:00:00:02"
$frame_size    = 64
$bulk_frames = 2000000
sz = $frame_size - 14 - 4
cmd =  "sudo ef name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} data pattern cnt #{sz} "
cmd += "name f#{$port_tx2} eth dmac #{$frame_smac} smac #{$frame_dmac} data pattern cnt #{sz} "
cmd += "tx #{$ts.pc.p[$port_tx1]} rep #{$bulk_frames} name f#{$port_tx1} "
cmd += "tx #{$ts.pc.p[$port_tx2]} rep #{$bulk_frames} name f#{$port_tx2} "

###### Create 2 VLANs for frame forwarding  ########
# PC-p1 --> DUT-p1 --VLAN2--> cable-loop --> --VLAN3--> DUT-p2 -> PC-p2
p1 = $ts.dut.p[0] + 1
p2 = kr_ports[0] + 1
vlan2p = p1.to_s + ',' + p2.to_s
p1 = $ts.dut.p[1] + 1
p2 = kr_ports[1] + 1
vlan3p = p1.to_s + ',' + p2.to_s
$ts.dut.run "mesa-cmd vlan add 2 #{vlan2p}"
$ts.dut.run "mesa-cmd vlan add 3 #{vlan3p}"
$ts.dut.run "mesa-cmd vlan pvid #{vlan2p} 2"
$ts.dut.run "mesa-cmd vlan pvid #{vlan3p} 3"
$ts.dut.run "mesa-cmd vlan uvid #{vlan2p} pvid"
$ts.dut.run "mesa-cmd vlan uvid #{vlan3p} pvid"

############ TRAINING ################
spds = []
spds << "adv-10g"
if cap25 != ""
    spds << "adv-25g"
end
cnt = 0
test "Training" do
    spds.each do |spd|
        kr_ports.each do |idx|
            $cli_port = idx+1
            $ts.dut.run "mesa-cmd port kr aneg #{$cli_port} #{spd} rfec rsfec train"
            t_i("==============================================");
        end
        for i in 1..repeat_test do
            kr_ports.each do |idx|
                cnt = 0
                while cnt < 5
                    conf = $ts.dut.call "mesa_port_kr_status_get", idx
                    if conf["train"]["complete"] == true
                        break
                    end
                    sleep 2
                    cnt += 1
                end
                if conf["train"]["complete"] != true
                    t_e("Could not complete training for #{spd}");
                    exit
                else
                    eye = $ts.dut.call "mesa_port_kr_eye_get", idx
                    t_i("Training port #{idx} (#{spd}) completed with eye height:#{eye["height"]}");
                end

            end
            test "Frame forwarding " do
                sleep 2
                $ts.dut.run "mesa-cmd port statis clear"
                $ts.pc.try cmd

                for p in 0..1 do
                    cnt = $ts.dut.call "mesa_port_counters_get", $ts.dut.port_list[p]
                    tx_frames = cnt['if_group']['ifOutUcastPkts']
                    if (tx_frames != $bulk_frames)
                        t_e("Unexpected framloss port #{$ts.dut.port_list[p]} Tx:#{$bulk_frames} Rx:#{tx_frames}")
                    else
                        t_i("Port #{$ts.dut.port_list[p]} at speed '#{spd}' Tx:#{$bulk_frames} Rx:#{tx_frames} - OK (round #{i})")
                        t_i("============================================");
                    end
                end
            end
            $ts.dut.run "mesa-cmd port state #{$cli_port} dis"
            $ts.dut.run "mesa-cmd port state #{$cli_port} ena"
            sleep 3
        end
    end
end
