#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check that cut-through is supported
cap_check_exit("QOS_EGRESS_QUEUE_CUT_THROUGH")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0
$idx_rx = 1

test "init" do
    $ts.dut.run("mesa-cmd example init ct iport #{$ts.dut.p[$idx_tx]} eport #{$ts.dut.p[$idx_rx]}")
end

def frame_test(idx_tx, idx_rx, min, max)
    # Send learn frame to ensure forwarding to a single port
    mac = 10
    $ts.pc.run("sudo ef tx #{$ts.pc.p[idx_rx]} eth smac #{mac}")

    # Send f1 (PCP = 7) and F2 (PCP = 0) and capture Rx/Tx timestamps
    idx_list = [idx_tx, idx_rx]
    cmd = "sudo ef "
    for i in 1..2 do
        pcp = (i == 1 ? 7 : 0)
        cmd += ("name f#{i} eth dmac #{mac}" + cmd_tag_push({tpid: 0x8100, pcp: pcp}) + " data pattern cnt 1496 ")
        cmd += "tx #{$ts.pc.p[idx_tx]} name f#{i} "
    end
    idx_list.each do |idx|
        cmd += "-c #{$ts.pc.p[idx]},2,adapter_unsynced,,2 "
    end
    $ts.pc.run(cmd)

    t = []
    idx_list.each do |idx|
        p = $ts.pc.get_pcap("#{$ts.pc.p[idx]}.pcap")
        t[idx] = (p[1][:us] - p[0][:us])
    end
    t_i("t: #{t}")

    delta = (t[idx_rx] - t[idx_tx])
    txt = "diff: #{delta} usec, min: #{min}, max: #{max}"
    if (delta >= min and delta <= max)
        t_i(txt)
    else
        t_e(txt)
    end
end

test "ct" do
    # Cut-through, approximately 10 usec latency difference expected
    frame_test($idx_tx, $idx_rx, 6, 14)
end


test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
    # Store-and-forward, same latency expected
    frame_test($idx_tx, $idx_rx, -5, 5)
end
