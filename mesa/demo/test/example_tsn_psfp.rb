#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

# Enable PSFP counters using "-vp" option
$ts = get_test_setup("mesa_pc_b2b_2x", {}, "-vp")

# Check that PSFP is supported
cap_check_exit("L2_PSFP")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0
$idx_rx = 1

test "init" do
  $ts.dut.run("mesa-cmd example init psfp iport #{$ts.dut.p[$idx_tx]}")
end

def filter_test(fwd, len)
    idx_list = []
    $ts.dut.p.each_index do |idx|
        if (fwd and idx != $idx_tx)
            idx_list << idx
        end
    end
    run_ef_tx_rx_cmd($ts, $idx_tx, idx_list, "eth data pattern cnt #{len - 18}")
end

test "filter.max_sdu" do
    filter_test(false, 1400)
end

test "gate" do
    # The following tests should work at 1G and 10G speeds:
    # - 100 usec gate intervals are used.
    # - Frame size of 10000 bits per frame.
    # - 1G: 10 frames per 100 usec.
    # - 10G: 100 frames per 100 usec.
    time_interval = 100000 # 100 usec
    len = ((10000/8) - 20)
    tx_cnt = 1000
    cmd = "sudo ef -c #{$ts.pc.p[$idx_rx]},1,adapter_unsynced,,#{tx_cnt} "
    cmd += "name f1 eth data pattern cnt #{len - 18} tx #{$ts.pc.p[$idx_tx]} rep #{tx_cnt} name f1"
    $ts.pc.run(cmd)
    pkts = $ts.pc.get_pcap "#{$ts.links[1][:pc]}.pcap"
    if (pkts.size == 0)
        t_e("No packets logged");
    else
        t_i("Logged #{pkts.size} packets")
        t_int = (time_interval / 1000) # Microseconds
        t0 = 0
        t0_valid = false
        margin = 20
        pkts.each do |p|
            t = p[:us_rel]
            diff = (t - t0)
            txt = "(t: #{t}, t0: #{t0}, diff: #{diff})"
            if (diff < 0)
                t_e("Prev interval #{txt}")
            elsif (diff < (t_int + margin))
                t_i("Same interval #{txt}")
            elsif (!t0_valid or (diff > (2*t_int - margin) and diff < (2*t_int + margin)))
                t_i("Next interval #{txt}")
                t0 = t
                t0_valid = true
            else
                t_e("Closed interval #{txt}")
            end
        end
    end
end

test "stats" do
    $ts.dut.run("mesa-cmd example run psfp")
end

test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
    filter_test(true, 1400)
end
