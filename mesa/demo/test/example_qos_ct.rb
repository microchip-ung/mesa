#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check that cut-through is supported
cap_check_exit("QOS_EGRESS_QUEUE_CUT_THROUGH")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0
$idx_ct = 1
$idx_sf = 2

test "init" do
    $ts.dut.run("mesa-cmd example init ct iport #{$ts.dut.p[$idx_tx]} eport #{$ts.dut.p[$idx_ct]}")
end

def frame_test(idx_tx, idx_list, pcp)
    cmd = "sudo ef name f1 eth"
    cmd += cmd_tag_push({tpid: 0x8100, vid: 1, pcp: pcp})
    cmd += " data pattern cnt 1496 tx #{$ts.pc.p[idx_tx]} name f1 "
    idx_list.each do |idx|
        cmd += "-c #{$ts.pc.p[idx]},1,adapter_unsynced,,1 "
        cmd += "rx #{$ts.pc.p[idx]} name f1 "
    end
    $ts.pc.run(cmd)

    t = []
    idx_list.each do |idx|
        pkts = $ts.pc.get_pcap("#{$ts.pc.p[idx]}.pcap")
        t[idx] = pkts[0][:us]
    end
    t
end

def check_diff(delta, min, max)
    txt = "diff: #{delta} usec, min: #{min}, max: #{max}"
    if (delta >= min and delta <= max)
        t_i(txt)
    else
        t_e(txt)
    end
end

test "ct" do
    idx_list = [$idx_ct, $idx_sf]
    t1 = frame_test($idx_tx, idx_list, 0) # Store-and-forward
    t2 = frame_test($idx_tx, idx_list, 7) # Cut-through
    t3 = frame_test($idx_tx, idx_list, 0) # Store-and-forward

    # In cut-through, only the first cell is stored (about 200 bytes) 
    # Latency difference between cut-through and store-and-forward
    # at 1Gbps is approximately (1500 - 200)*8 nsec = 10 usec
    check_diff(t2[$idx_sf] + t1[$idx_ct] - t1[$idx_sf] - t2[$idx_ct], 9, 11)

    # In store-and-forward, the latency difference should be small
    check_diff(t3[$idx_sf] + t1[$idx_ct] - t1[$idx_sf] - t3[$idx_ct], -1, 1)
end


test "uninit" do
    idx_list = [$idx_ct, $idx_sf]
    $ts.dut.run("mesa-cmd example uninit")
    t1 = frame_test($idx_tx, idx_list, 0) # Store-and-forward
    t2 = frame_test($idx_tx, idx_list, 7) # Store-and-forward
    check_diff(t2[$idx_sf] + t1[$idx_ct] - t1[$idx_sf] - t2[$idx_ct], -1, 1)
end
