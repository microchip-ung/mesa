#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check that FRER is supported
cap_check_exit("L2_FRER")

#---------- Configuration -----------------------------------------------------

$idx_up    = 0
$idx_rp    = 1
$idx_cp    = 2
$idx_other = 3

test "init" do
  cmd = "mesa-cmd example init frer"
  cmd += " uport #{$ts.dut.p[$idx_up]}"
  cmd += " rport #{$ts.dut.p[$idx_rp]}"
  cmd += " cport #{$ts.dut.p[$idx_cp]}"
  $ts.dut.run(cmd)
end

def frer_frame(t, idx)
    cmd = ""
    if (t.key?:discard)
        # Tx discard
    else
        cmd = " name f#{t[:idx]} eth"
        if (idx == $idx_up)
            cmd += " dmac ::2 smac ::1"
        else
            cmd += " dmac ::1 smac ::2"
        end
        if (t.key?:tag)
            cmd += cmd_tag_push(t[:tag])
        end
        if (t.key?:seq)
            cmd += " rtag seqn #{t[:seq]}"
        end
        cmd += " data pattern cnt 128"
    end
    cmd
end

$test_table =
    [
        {
            txt: "Tx U-port, generation, seq = 0",
            tx: {idx: $idx_up},
            rx: [{idx: $idx_rp, seq: 0},
                 {idx: $idx_cp, tag: {tpid: 0x8100, vid: 10}, seq: 0}]
        },
        {
            txt: "Tx U-port, generation, seq = 1",
            tx: {idx: $idx_up},
            rx: [{idx: $idx_rp, seq: 1},
                 {idx: $idx_cp, tag: {tpid: 0x8100, vid: 10}, seq: 1}]
        },
        {
            txt: "Tx R-port, recovery pass, seq = 100",
            tx: {idx: $idx_rp, seq: 100},
            rx: [{idx: $idx_up},
                 {idx: $idx_cp, tag: {tpid: 0x8100, vid: 10}, seq: 100}]
        },
        {
            txt: "Tx R-port, recovery discard, seq = 100",
            tx: {idx: $idx_rp, seq: 100},
            rx: [{idx: $idx_up, discard: 1},
                 {idx: $idx_cp, tag: {tpid: 0x8100, vid: 10}, seq: 100}]
        },
        {
            txt: "Tx C-port, recovery pass, seq = 101",
            tx: {idx: $idx_cp, tag: {tpid: 0x8100, vid: 10}, seq: 101},
            rx: [{idx: $idx_up},
                 {idx: $idx_rp, seq: 101}]
        },
        {
            txt: "Tx C-port, recovery discard, seq = 101",
            tx: {idx: $idx_cp, tag: {tpid: 0x8100, vid: 10}, seq: 101},
            rx: [{idx: $idx_up, discard: 1},
                 {idx: $idx_rp, seq: 101}]
        }
    ]

$test_table.each do |t|
    test t[:txt] do
        cmd = "sudo ef"
        tx = t[:tx]
        idx = tx[:idx]
        cmd += frer_frame(tx, idx)
        t[:rx].each do |rx|
            cmd += frer_frame(rx, idx)
        end
        cmd += " tx #{$ts.pc.p[idx]} name f#{idx}"
        t[:rx].each do |rx|
            idx = rx[:idx]
            cmd += " rx #{$ts.pc.p[idx]}"
            if (rx.key?:discard)
            else
                cmd += " name f#{idx}"
            end
        end
        $ts.pc.run(cmd)
    end
end

test "stats" do
    $ts.dut.run("mesa-cmd example run frer")
end

test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
    run_ef_tx_rx_cmd($ts, $idx_up, [$idx_rp, $idx_cp, $idx_other], "eth")
end
