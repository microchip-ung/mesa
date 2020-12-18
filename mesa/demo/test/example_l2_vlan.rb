#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_up = 0
$idx_ap = 1
$idx_tp = 2
$idx_hp = 3

test "init" do
  cmd = "mesa-cmd example init vlan"
  cmd += " uport #{$ts.dut.p[$idx_up]}"
  cmd += " aport #{$ts.dut.p[$idx_ap]}"
  cmd += " tport #{$ts.dut.p[$idx_tp]}"
  cmd += " hport #{$ts.dut.p[$idx_hp]}"
  $ts.dut.run(cmd)
end

test_table =
    [
     {
         txt: "unaware untag -> trunk tag, hybrid untag",
         tx: {idx: $idx_up, tag: {}},
         rx: [{idx: $idx_ap},
              {idx: $idx_tp, tag: {tpid: 0x8100, vid: 10}},
              {idx: $idx_hp, tag: {}}]
     },
     {
         txt: "access untag -> trunk tag, hybrid tag",
         tx: {idx: $idx_ap, tag: {}},
         rx: [{idx: $idx_up},
              {idx: $idx_tp, tag: {tpid: 0x8100, vid: 20}},
              {idx: $idx_hp, tag: {tpid: 0x8100, vid: 20}}]
     },
     {
         txt: "trunk tag(10) -> unaware untag, hybrid untag",
         tx: {idx: $idx_tp, tag: {tpid: 0x8100, vid: 10}},
         rx: [{idx: $idx_up, tag: {}},
              {idx: $idx_ap},
              {idx: $idx_hp, tag: {}}]
     },
     {
         txt: "trunk tag(20) -> access untag, hybrid tag",
         tx: {idx: $idx_tp, tag: {tpid: 0x8100, vid: 20}},
         rx: [{idx: $idx_up},
              {idx: $idx_ap, tag: {}},
              {idx: $idx_hp, tag: {tpid: 0x8100, vid: 20}}]
     },
     {
         txt: "hybrid untag -> unaware untag, trunk tag",
         tx: {idx: $idx_hp, tag: {}},
         rx: [{idx: $idx_up, tag: {}},
              {idx: $idx_ap},
              {idx: $idx_tp, tag: {tpid: 0x8100, vid: 10}}]
     },
     {
         txt: "hybrid tag(20) -> access untag, trunk tag",
         tx: {idx: $idx_tp, tag: {tpid: 0x8100, vid: 20}},
         rx: [{idx: $idx_up},
              {idx: $idx_ap, tag: {}},
              {idx: $idx_hp, tag: {tpid: 0x8100, vid: 20}}]
     },
]

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        cmd = "sudo ef"
        tx = t[:tx]
        cmd += " name f#{tx[:idx]} eth"
        cmd += cmd_tag_push(tx[:tag])
        cmd += " data pattern cnt 64"
        t[:rx].each do |rx|
            idx = rx[:idx]
            if (rx.key?:tag)
                cmd += " name f#{idx} eth"
                cmd += cmd_tag_push(rx[:tag])
                cmd += " data pattern cnt 64"
            end
        end
        idx = tx[:idx]
        cmd += " tx #{$ts.pc.p[idx]} name f#{idx}"
        t[:rx].each do |rx|
            idx = rx[:idx]
            cmd += " rx #{$ts.pc.p[idx]}"            
            if (rx.key?:tag)
                cmd += " name f#{idx}"
            end
        end
        $ts.pc.run(cmd)
    end
end

test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
    run_ef_tx_rx_cmd($ts, $idx_up, [$idx_ap, $idx_tp, $idx_hp], "eth")
end
