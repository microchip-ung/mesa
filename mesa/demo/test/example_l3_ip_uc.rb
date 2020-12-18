#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if L3 supported
cap_check_exit("L3")

#---------- Configuration -----------------------------------------------------

$idx_ip = 0
$idx_ep = 1
$rmac = "00:00:00:00:00:01"

test "init" do
    $ts.dut.run("mesa-cmd example init ipv4_uc iport #{$ts.dut.p[$idx_ip]} eport #{$ts.dut.p[$idx_ep]}")
end

test_table =
    [
     {
         txt: "forward 1.1.1.1 -> 2.2.2.2",
         tx: {idx: $idx_ip, dmac: $rmac, smac: "00:00:01:01:01:01", ttl: 64, sip: "1.1.1.1", dip: "2.2.2.2"},
         rx: {idx: $idx_ep, dmac: "00:00:02:02:02:02", smac: $rmac, ttl: 63, sip: "1.1.1.1", dip: "2.2.2.2"}
     },
     {
         txt: "forward 2.2.2.2 -> 1.1.1.1",
         tx: {idx: $idx_ep, dmac: $rmac, smac: "00:00:02:02:02:02", ttl: 64, sip: "2.2.2.2", dip: "1.1.1.1"},
         rx: {idx: $idx_ip, dmac: "00:00:01:01:01:01", smac: $rmac, ttl: 63, sip: "2.2.2.2", dip: "1.1.1.1"}
     },
     {
         txt: "forward 1.1.1.1 -> 3.3.3.3 via 2.2.2.1",
         tx: {idx: $idx_ip, dmac: $rmac, smac: "00:00:01:01:01:01", ttl: 64, sip: "1.1.1.1", dip: "3.3.3.3"},
         rx: {idx: $idx_ep, dmac: "00:00:02:02:02:01", smac: $rmac, ttl: 63, sip: "1.1.1.1", dip: "3.3.3.3"}
     },
    ]

def ip_frame(f)
    cmd = " eth"
    if (f.key?:dmac)
        cmd += " dmac #{f[:dmac]}"
    end
    if (f.key?:smac)
        cmd += " smac #{f[:smac]}"
    end
    cmd += " ipv4"
    if (f.key?:sip)
        cmd += " sip #{f[:sip]}"
    end
    if (f.key?:dip)
        cmd += " dip #{f[:dip]}"
    end
    if (f.key?:ttl)
        cmd += " ttl #{f[:ttl]}"
    end
    cmd
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        cmd = "sudo ef"
        tx = t[:tx]
        cmd += (" name f1" + ip_frame(tx))
        rx = t[:rx]
        cmd += (" name f2" + ip_frame(rx))
        cmd += " tx #{$ts.pc.p[tx[:idx]]} name f1"
        cmd += " rx #{$ts.pc.p[rx[:idx]]} name f2"        
        $ts.pc.run(cmd)
    end
end

test "counters" do
    $ts.dut.run("mesa-cmd example run ipv4_uc")
end

test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
    run_ef_tx_rx_cmd($ts, $idx_ip, [$idx_ep, 2, 3], "eth")
end
