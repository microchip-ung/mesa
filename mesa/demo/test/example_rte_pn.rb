#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0 # PC Tx port
$idx_rx = 1 # PC Rx port

test "conf" do
    # Initialize QSPI
    qspi_init

    # Clear IO memory
    io_fpga_rw("fill 0x0100 0x100 0")

    # Write data to QSPI
    io_str_wr(0x110, "0504030201", "QSPI")

    # Find chip Tx port
    port_cnt = cap_get("PORT_CNT")
    map = $ts.dut.call("mesa_port_map_get", port_cnt)
    eport = map[$ts.dut.p[$idx_rx]]["chip_port"]

    # Initialize MESA/MERA examples
    $ts.dut.run("mesa-cmd example init pn iport #{$ts.dut.p[$idx_tx]}")
    $ts.dut.run("mera-cmd example init pn eport #{eport}")
end

test "frame-io" do
    # Frame f1 is sent to RTE-OB with incrementing data pattern
    len = 46
    f1 = "eth dmac 2 smac 1 et 0x8892 data hex 8000"
    f1 += " data pattern cnt #{len - 8}"
    cc = "ccc0"
    ds = "35"
    ts = "00"
    f1 += " data hex #{cc}#{ds}#{ts}"

    # Frame f2 is sent by RTE-IB every second with data "0504030201" at frame offset 2
    f2 = "eth dmac 1 smac 2 et 0x8892 data hex 8000 data hex "
    for i in 0..(len - 7) do
        d = (i < 5 ? (5 - i) : 0)
        f2 += ("%02x" % d)
    end
    f2 += " ctag pcp ign dei ign vid ign" # Ignore CC using C-tag

    cmd = "sudo ef -t 900 name f1 #{f1} name f2 #{f2}"
    cmd += " tx #{$ts.pc.p[$idx_tx]} name f1"
    [0, 1, 2, 3].each do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == $idx_rx)
            cmd += " name f2"
        end
    end
    $ts.pc.run(cmd)

    # Check data pattern read from frame offset 2.
    addr = 0x100
    str = "0001020304"
    intf = "QSPI"
    res = io_str_rd(addr, str, intf)
    t_i("Exp (#{intf}): #{str}")
    act = ("0x%08x: #{res}" % addr)
    if (res == str)
        t_i(act)
    else
        t_e(act)
    end
end

test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
    $ts.dut.run("mera-cmd example uninit")
end

test "dump" do
    break
    $ts.dut.run("mera-cmd debug api ob")
    io_fpga_rw("dump 0x0100 64")
end
