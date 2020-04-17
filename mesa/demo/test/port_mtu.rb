#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Description -------------------------------------------------------
# Purpose:
# MTU testing.
# Test the 'mesa_port_conf_t::max_frame_length' and 'mesa_port_conf_t::max_tags' struct members,
# by setting the 'max_frame_length' (mtu) and 'max_tags' to different values and verify with frame transmission.
#
# Test procedure:
# Host port 'a' transmits unicast frames to host port 'b' (through the DUT) with different frame sizes
# and different port settings as described in the test_table below.
#
#
#---------- Test parameters ----------------------------------------------------
$port_tx1      = 0
$port_rx       = 1
$frame_smac    = "00:00:00:00:00:01"
$frame_dmac    = "00:00:00:00:00:02"
$test_table    =
    [
    { frmsize: 64,   mtu: 64,   max_tags: "MESA_PORT_MAX_TAGS_NONE", fwd: true  },
    { frmsize: 65,   mtu: 64,   max_tags: "MESA_PORT_MAX_TAGS_NONE", fwd: false },
    { frmsize: 1518, mtu: 1518, max_tags: "MESA_PORT_MAX_TAGS_NONE", fwd: true  },
    { frmsize: 1522, mtu: 1518, max_tags: "MESA_PORT_MAX_TAGS_ONE",  fwd: true  },
    { frmsize: 1523, mtu: 1518, max_tags: "MESA_PORT_MAX_TAGS_ONE",  fwd: false },
    { frmsize: 1526, mtu: 1518, max_tags: "MESA_PORT_MAX_TAGS_TWO",  fwd: true  },
    { frmsize: 1527, mtu: 1518, max_tags: "MESA_PORT_MAX_TAGS_TWO",  fwd: false },
    { frmsize: 9000, mtu: 9000, max_tags: "MESA_PORT_MAX_TAGS_NONE", fwd: true  },
    { frmsize: 9001, mtu: 9000, max_tags: "MESA_PORT_MAX_TAGS_NONE", fwd: false } ]

#---------- Frame testing -----------------------------------------------------
$ts.dut.run "mesa-cmd deb port polling disable"
$test_table.each do |entry|
    console("Framesize:#{entry[:frmsize]}, MTU:#{entry[:mtu]}  Max-tags:#{entry[:max_tags]} Frame fwd:#{entry[:fwd]}")
    tag = 0
    tag_txt = ""
    if entry[:max_tags].eql? "MESA_PORT_MAX_TAGS_ONE"
        tag = 4
        tag_txt = "ctag vid 1"
    elsif entry[:max_tags].eql? "MESA_PORT_MAX_TAGS_TWO"
        tag_txt = "ctag vid 1 ctag vid 2"
        tag = 8
    end
    # Adjust data length for length MAC header, tag and FCS
    sz = entry[:frmsize] - 14 - 4 - tag

    test "conf" do
        conf = $ts.dut.call "mesa_port_conf_get", $ts.dut.p[$port_tx1]
        conf["max_frame_length"] = entry[:mtu]
        conf["max_tags"] = entry[:max_tags]
        $ts.dut.call "mesa_port_conf_set", $ts.dut.p[$port_tx1], conf
    end

    test "frame-io" do
        cmd =  "sudo ef name f#{$port_tx1} eth dmac #{$frame_dmac} smac #{$frame_smac} "
        cmd += "#{tag_txt} data pattern cnt #{sz} "
        cmd += "tx #{$ts.pc.p[$port_tx1]} name f#{$port_tx1} "
        if (entry[:fwd])
            cmd += "rx #{$ts.pc.p[$port_rx]} name f#{$port_tx1} "
        else
            cmd += "rx #{$ts.pc.p[$port_rx]} "
        end
        $ts.pc.try cmd
    end
end
