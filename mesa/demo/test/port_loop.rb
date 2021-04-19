#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Capabilities -----------------------------------------------------
check_capabilities do
    c1 = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    c2 = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    assert(((c1 == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2") && c2 < 30) || (c1 == chip_family_to_id("MESA_CHIP_FAMILY_SERVALT"))),
           "loop support")
end

#---------- Description -------------------------------------------------------
# Purpose:
# Verify that vtss_port_conf_t::loop is working as expected. This enum can be 'VTSS_PORT_LOOP_DISABLE' and 'VTSS_PORT_LOOP_PCS_HOST'.
# 'VTSS_PORT_LOOP_PCS_HOST' means that egress frames are (also) loopbacked to ingress, i.e. both ingress and egress counters increment.
#
# Test procedure:
# Send frames to DUT port 'a' to be flooded to DUT port 'b'.
# Verify that the frames are counted as ingress and egress frames at DUT port 'b'.


#---------- Test parameters ----------------------------------------------------
$port_tx1      = 0
$port_tx2      = 1
$frame_smac    = "00:00:00:00:00:01"
$frame_dmac    = "00:00:00:00:00:02"
$frame_size    = 64
$num_of_frames = 10

#---------- Configuration -----------------------------------------------------
$ts.dut.run "mesa-cmd deb port polling disable"
conf = {}
test "conf" do
    conf = $ts.dut.call "mesa_port_conf_get", $ts.dut.p[$port_tx1]
    conf["loop"] = "MESA_PORT_LOOP_PCS_HOST"
    $ts.dut.call "mesa_port_conf_set", $ts.dut.p[$port_tx1], conf
end

#---------- Frame testing -----------------------------------------------------
test "frame-io" do
    sz = $frame_size - 14 - 4
    cmd =  "sudo ef name f#{$port_tx2} eth dmac #{$frame_dmac} smac #{$frame_smac} "
    cmd += "et 0x0800 data pattern cnt #{sz} "
    cmd += "tx #{$ts.pc.p[$port_tx2]} rep #{$num_of_frames} name f#{$port_tx2} "

    $ts.dut.call "mesa_port_counters_clear", $ts.dut.p[$port_tx1]
    $ts.pc.try cmd
    cnt = $ts.dut.call "mesa_port_counters_get", $ts.dut.p[$port_tx1]

    tx_frame_cnt = cnt['if_group']['ifOutUcastPkts']
    rx_frame_cnt = cnt['if_group']['ifInUcastPkts']
    if (($num_of_frames != tx_frame_cnt) || ($num_of_frames != rx_frame_cnt))
        t_e "Loopback frames missing"
    end
end

#---------- Clean up -----------------------------------------------------------
conf["loop"] = "MESA_PORT_LOOP_DISABLE"
$ts.dut.call "mesa_port_conf_set", $ts.dut.p[$port_tx1], conf
