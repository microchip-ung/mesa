#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if PSFP supported
cap_check_exit("L2_PSFP")

#---------- Configuration -----------------------------------------------------

test "conf" do
    $ts.dut.run("mesa-cmd test 9")
end

$idx_tx = 0
$idx_rx = 1

test "frame-preemption" do
    cmd = "sudo ef "
    cmd += "name f1 eth et 0x8100 ctag vid 10 data pattern cnt 1496 "
    cmd += "name f2 eth et 0xaaaa data pattern cnt 46 "
    cmd += "tx #{$ts.pc.p[$idx_tx]} name f1 "
    cmd += "tx #{$ts.pc.p[$idx_tx]} name f2 "
    # Frame f1 is sent through PMAC, so it gets a special preamble and is not seen by the PC
    cmd += "rx #{$ts.pc.p[$idx_rx]} name f2 "
    $ts.pc.run(cmd)
end

test "frame-psfp" do
    port_rx = $ts.dut.p[$idx_tx]
    port_tx = $ts.dut.p[$idx_rx]
    $ts.dut.call("mesa_port_counters_clear", port_rx)
    $ts.dut.call("mesa_port_counters_clear", port_tx)
    cmd = "sudo ef "
    cmd += "name f1 eth et 0x8100 ctag vid 20 data pattern cnt 1496 "
    cmd += "tx #{$ts.pc.p[$idx_tx]} rep 1000 name f1 "
    $ts.pc.run(cmd)
    cnt_rx = $ts.dut.call("mesa_port_counters_get", port_rx)["rmon"]["rx_etherStatsPkts"]
    cnt_tx = $ts.dut.call("mesa_port_counters_get", port_tx)["rmon"]["tx_etherStatsPkts"]
    t_i("Rx port #{port_rx}: #{cnt_rx}")
    t_i("Tx port #{port_tx}: #{cnt_tx}")
end

test "frame-frer" do
    if_tx = $ts.pc.p[$idx_tx]
    if_rx1 = $ts.pc.p[$idx_rx]
    if_rx2 = $ts.pc.p[$idx_rx + 1]
    for i in 0..1 do
        cmd = "sudo ef "
        cmd += "name f1 eth et 0x8100 ctag vid 30 data pattern cnt 128 "
        cmd += "name f2 eth et 0x8100 ctag vid 30 rtag seqn #{i} data pattern cnt 128 "
        # Generation
        cmd += "tx #{if_tx} name f1 " 
        cmd += "rx #{if_rx1} name f2 "
        cmd += "rx #{if_rx2} name f2 "
        # Recovery
        cmd += "tx #{if_rx1} name f2 "
        cmd += "tx #{if_rx2} name f2 "
        cmd += "rx #{if_tx} name f1 " 
        $ts.pc.run(cmd)
    end
end

test "frame-tas" do
    len = (10000/8 - 20 - 14 - 4 - 4) # 10000 bits per frame
    tx_cnt = 110
    cmd = "sudo ef -c #{$ts.pc.p[$idx_rx]},1,adapter_unsynced,,#{tx_cnt} "
    cmd += "name f1 eth et 0x8100 ctag vid 40 data pattern cnt #{len} "
    cmd += "tx #{$ts.pc.p[$idx_tx]} rep #{tx_cnt} name f1 "
    $ts.pc.run(cmd)
    pkts = $ts.pc.get_pcap("#{$ts.links[1][:pc]}.pcap")
    if (pkts.size == 0)
        t_e("No packets logged");
    else
        t_i("Logged #{pkts.size} packets")
        pkts.each do |p|
            t = p[:us_rel]
            t_i("t: #{t}")
        end
    end
end
