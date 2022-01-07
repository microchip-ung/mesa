#!/usr/bin/env ruby

# Copyright (c) 2004-2021 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_2x", {}, "", "loop")

#---------- Description -------------------------------------------------------
# Purpose:
# Verify normal frame forwarding is working over looped SFP ports.
# This test requires looped port setup.
#
# Test procedure:
# 1. Use 2 front ports and 2 looped ports in 2 VLANs. The looped SFP ports connects the 2 VLANs.
# 2. Set front port 1 and loop port 1 in VLAN 2.
# 3. Set front port 2 and loop port 2 in VLAN 3.
# 4. Choose speed for DAC based loop ports. Optical ports only supports the default speed.
# 5. Send frames over the loop ports and verify no frameloss.
# 6. Repeat for each supported speed.
# 7. Repeat for each looped port pair in the setup.
#--------------------------------------------------------------------------------

check_capabilities do
    assert(($ts.dut.looped_port_list != nil) && ($ts.dut.looped_port_list.length > 1),
           "Two front ports must be looped")
end

$cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")

def send_and_verify(tx, rx)
    cmd =  "sudo ef name f-#{tx} eth dmac ff:ff:ff:ff:ff:ff smac ::1 "
    cmd += "tx #{$ts.pc.p[tx]} name f-#{tx} "
    cmd += "rx #{$ts.pc.p[rx]} name f-#{tx} "
    $ts.pc.try cmd
end

def vlan_add(vlan, port)
    $ts.dut.run "mesa-cmd vlan add #{vlan} #{port}"
    $ts.dut.run "mesa-cmd vlan pvid #{port} #{vlan}"
    $ts.dut.run "mesa-cmd vlan uvid #{port} pvid"
end

def send_bulk(port_tx1, port_tx2, frames)
    frame_smac    = "00:00:00:00:00:01"
    frame_dmac    = "00:00:00:00:00:02"
    frame_size    = 64
    sz = frame_size - 14 - 4
    cmd =  "sudo ef name f#{port_tx1} eth dmac #{frame_dmac} smac #{frame_smac} data pattern cnt #{sz} "
    cmd += "name f#{port_tx2} eth dmac #{frame_smac} smac #{frame_dmac} data pattern cnt #{sz} "
    cmd += "tx #{$ts.pc.p[port_tx1]} rep #{frames} name f#{port_tx1} "
    cmd += "tx #{$ts.pc.p[port_tx2]} rep #{frames} name f#{port_tx2} "
    $ts.pc.try cmd
end

#---------- Test parameters -------------------------------------------------------
# Merge looped_port_list and looped_port_list_10g
if $ts.dut.looped_port_list_10g
    $ts.dut.looped_port_list_10g.each do |idx|
        $ts.dut.looped_port_list << idx
    end
end

$p0 =  $ts.dut.p[0] + 1
$p1 =  $ts.dut.p[1] + 1
$tx_port = [0, 1]
$vlan2ports = $p0.to_s
$vlan3ports = $p1.to_s
$bulk_frames = 1000000

#---------- Now the test--------------------------------------------------------------
i = 0
dac = 0
test "Test SFP loop" do
    loop do
        conf = $ts.dut.call "mesa_port_conf_get", $ts.dut.looped_port_list[i]
        type = conf["if_type"]
        if (type == "MESA_PORT_INTERFACE_SGMII" or type == "MESA_PORT_INTERFACE_QSGMII")
            continue; # SFP test only
        end
        if conf["serdes"]["media_type"].include? "DAC"
            dac = 1
            if conf["speed"].include? "25G" then spds = ["25g","10g","5g","2500","1000fdx","100fdx"] end
            if conf["speed"].include? "10G" then spds = ["10g","5g","2500","1000fdx","100fdx"] end
            if conf["speed"].include? "2500" then spds = ["2500","1000fdx","100fdx"] end
            if conf["speed"].include? "1G" then spds = ["1000fdx","100fdx"] end

            if (($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5") && $ts.dut.looped_port_list[i] > 11) ||
                ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")))
                spds.pop # Remove 100fdx
            end
        else
            dac = 0
            if conf["speed"].include? "25G" then spds = ["25g"] end
            if conf["speed"].include? "10G" then spds = ["10g"] end
            if conf["speed"].include? "1G" then spds = ["1000fdx"] end
            if conf["speed"].include? "100M" then spds = ["100fdx"] end
        end

        if (spds == nil)
            t_i "*******No valid speeds found**********"
            return
        end

        $loop0 = $ts.dut.looped_port_list[i] + 1
        $loop1 = $ts.dut.looped_port_list[i+1] + 1
        cli_ports = $loop0.to_s + ',' + $loop1.to_s
        $vlan2ports += ',' + $loop0.to_s
        $vlan3ports += ',' + $loop1.to_s
        vlan_add(2, $vlan2ports)
        vlan_add(3, $vlan3ports)

        spds.each {|spd|
            $ts.dut.run "mesa-cmd port mode #{cli_ports} #{spd}"
            t_i("==========================================================");
            t_i("======== DAC ports:#{cli_ports} speed:#{spd} =============")
            sleep 5
            test "Frame forwarding with broadcast frames" do
                if spd == "100fdx"
                    send_and_verify($tx_port[0], $tx_port[1])
                    send_and_verify($tx_port[1], $tx_port[0])
                else
                    send_bulk(0, 1, 10)
                    $ts.dut.run "mesa-cmd port statis clear"
                    # Send frames from PC
                    send_bulk(0, 1, $bulk_frames)
                    # Verify by reading DUT counters
                    for p in 0..1 do
                        cnt = $ts.dut.call "mesa_port_counters_get", $ts.dut.port_list[p]
                        tx_frames = cnt['if_group']['ifOutUcastPkts']
                        if (tx_frames != $bulk_frames)
                            t_e("Unexpected framloss port #{$ts.dut.port_list[p]} speed:#{spd} Tx:#{$bulk_frames} Rx:#{tx_frames}")
                            exit
                        else
                            t_i("Port #{$ts.dut.port_list[p]} at speed '#{spd}' Tx:#{$bulk_frames} Rx:#{tx_frames} - OK (loop #{i/2+1})")
                            t_i("==============================================================================");
                        end
                    end
                end
            end
        }

        if $ts.dut.looped_port_list[i+2] == nil
            break;
        end

        $ts.dut.run "mesa-cmd port state #{$loop0} dis"
        $ts.dut.run "mesa-cmd port state #{$loop1} dis"
        sleep 3
        i += 2
    end
end
