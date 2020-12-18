#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check DLB policers supported
cap_check_exit("L2_XDLB")

#---------- Configuration -----------------------------------------------------

$idx_ap1 = 0
$idx_ap2 = 1
$idx_tp1 = 2
$idx_tp2 = 3

test_table =
    [
     {
         txt: "access/untag -> trunk/tag",
         cfg: {tvid: 100, tpcp: 4, rate: 1000},
         tx: {idx: $idx_ap1, tag: {}},
         rx: {idx: $idx_tp1, tag: {tpid: 0x8100, vid: 100, pcp: 4}}
     },
     {
         txt: "trunk/tag -> access/untag",
         tx: {idx: $idx_tp1, tag: {tpid: 0x8100, vid: 100}},
         rx: {idx: $idx_ap1, tag: {}}
     },
     {
         txt: "access/prio-tag -> trunk/tag",
         cfg: {avid: 0, apcp: 6, tvid: 98, tpcp: 5, rate: 2000},
         tx: {idx: $idx_ap2, tag: {tpid: 0x8100, pcp: 6}},
         rx: {idx: $idx_tp2, tag: {tpid: 0x8100, vid: 98, pcp: 5}}
     },
     {
         txt: "trunk/tag -> access/prio-tag",
         tx: {idx: $idx_tp2, tag: {tpid: 0x8100, vid: 98}},
         rx: {idx: $idx_ap2, tag: {tpid: 0x8100, pcp: 6}}
     },
     {
         txt: "access/prio-tag -> discard",
         tx: {idx: $idx_ap2, tag: {tpid: 0x8100, pcp: 5}},
         rx: {idx: $idx_tp2}
     },
]

test "init" do
    $ts.dut.run("mesa-cmd example init eflow")
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        # Configuration
        rx = t[:rx]
        tx = t[:tx]
        if (t.key?:cfg)
            cfg = t[:cfg]
            cmd = "mesa-cmd example run eflow aport #{$ts.dut.p[tx[:idx]]} "
            if (cfg.key?:avid)
                cmd += "avid #{cfg[:avid]} "
            end
            if (cfg.key?:apcp)
                cmd += "apcp #{cfg[:apcp]} "
            end
            cmd += "tport #{$ts.dut.p[rx[:idx]]} tvid #{cfg[:tvid]} tpcp #{cfg[:tpcp]} "
            if (cfg.key?:rate)
                cmd += "rate #{cfg[:rate]} "
            end
            $ts.dut.run(cmd)
        end

        # Frame test
        cmd = "sudo ef"
        cmd += " name f1 eth"
        cmd += cmd_tag_push(tx[:tag])
        cmd += " data pattern cnt 64"
        str = ""
        if (rx.key?:tag)
            cmd += " name f2 eth"
            cmd += cmd_tag_push(rx[:tag])
            cmd += " data pattern cnt 64"
            str = "name f2"
        end
        cmd += " tx #{$ts.pc.p[tx[:idx]]} name f1"
        cmd += " rx #{$ts.pc.p[rx[:idx]]} #{str}"
        $ts.pc.run(cmd)
    end
end

test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
    run_ef_tx_rx_cmd($ts, $idx_ap1, [$idx_ap2, $idx_tp1, $idx_tp2], "eth")
end
