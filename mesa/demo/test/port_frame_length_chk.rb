#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Description -------------------------------------------------------
# Purpose:
# Verify the Ethernet Type/Length field is working as expected.
# a) If Type/length field (byte 12-13) is <= than 1500 then the field is a 'Length' field.
# b) If Type/length field (byte 12-13) is  > than 1500 then the field is a 'Type' field.
# mesa_port_conf_t::frame_length_chk enforces frame drop in the case of a) if length field
# does not match with actual frame-data len.
#
# Test procedure:
# Enable/disable 'mesa_port_conf_t::frame_length_chk' struct member and verify the effect
# by setting the length and framesize to different values as described by the test_table below.
#
#---------- Test parameters ----------------------------------------------------
$port_1      = 0
$port_2      = 1
$tx_smac    = "00:00:00:00:00:01"
$tx_dmac    = "00:00:00:00:00:02"
$num_of_frames = 1
$test_table    =
    [
        { frmsize: 1518, len_field: 1500, frame_length_chk: true,  fwd: true  },
        { frmsize: 1517, len_field: 1500, frame_length_chk: true,  fwd: false },
        { frmsize: 1519, len_field: 1500, frame_length_chk: true,  fwd: false },
        { frmsize: 64,   len_field: 46,   frame_length_chk: true,  fwd: true  },
        { frmsize: 64,   len_field: 47,   frame_length_chk: true,  fwd: false },
        { frmsize: 64,   len_field: 47,   frame_length_chk: false, fwd: true  },
    ]

#---------- Configuration and Frame testing -----------------------------------------------------
$ts.dut.run "mesa-cmd deb port polling disable"
test "frame_func" do
    $test_table.each do |entry|
        test "Configuration" do
            conf = $ts.dut.call "mesa_port_conf_get", $ts.dut.p[$port_1]
            conf["frame_length_chk"] = entry[:frame_length_chk]
            $ts.dut.call "mesa_port_conf_set", $ts.dut.p[$port_1], conf
        end

        test "Framesize:#{entry[:frmsize]}, Frame fwd:#{entry[:len_field]}, Frame fwd:#{entry[:fwd]}" do
            sz = entry[:frmsize] - 14 - 4
            cmd =  "sudo ef name f#{$port_1} eth dmac #{$tx_dmac} smac #{$tx_smac} "
            cmd += "et #{entry[:len_field]} data pattern cnt #{sz} "
            cmd += "tx #{$ts.pc.p[$port_1]} name f#{$port_1} "
            p1 = $ts.dut.p[$port_1]
            p2 = $ts.dut.p[$port_2]
            $ts.dut.call("mesa_port_counters_clear", p1)
            $ts.dut.call("mesa_port_counters_clear", p2)
            $ts.pc.try cmd
            cnt = $ts.dut.call("mesa_port_counters_get", p2)
            if entry[:fwd]
                if cnt['rmon']['tx_etherStatsPkts'] != 1
                    t_e "unexpected frameloss"
                end
            else
                if cnt['rmon']['tx_etherStatsPkts'] != 0
                    t_e "unexpected framefwd"
                end
            end
            # For Jaguar-2/FireAnt, ifInErrors counts
            cnt = $ts.dut.call("mesa_port_counters_get", p1)
            t_i("ifInErrors: #{cnt['if_group']['ifInErrors']}")
        end
    end
end

