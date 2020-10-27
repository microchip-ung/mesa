#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

test "conf" do
    # Initialize QSPI
    qspi_init

    # Clear IO memory
    io_fpga_rw("fill 0x0100 0x100 0")
    io_sram_rw("fill 0x0200 0x100 0")
end

def rte_ob_test
    wal_id = 1

    # Write data to SRAM
    rd_addr = 0x200
    str = "98765432"
    io_str_wr(rd_addr, str, "SRAM")
    wr_addr = 0x100

    # Add WA
    conf = $ts.dut.call("mera_ob_wa_init")
    conf["internal"] = true
    addr = conf["rd_addr"]
    addr["intf"] = "MERA_IO_INTF_SRAM"
    addr["addr"] = rd_addr
    conf["length"] = 4
    addr = conf["wr_addr"]
    addr["intf"] = "MERA_IO_INTF_QSPI"
    addr["addr"] = wr_addr
    $ts.dut.call("mera_ob_wa_add", wal_id, conf)

    # Setup WAL entry
    conf = $ts.dut.call("mera_ob_wal_conf_get", wal_id)
    conf["time"]["interval"] = 1000000000 # One second
    $ts.dut.call("mera_ob_wal_conf_set", wal_id, conf)

    # Check data
    sleep(2)
    res = io_str_rd(wr_addr, str, "QSPI")
    t_i("Exp (QSPI): #{str}")
    act = ("0x%08x: #{res}" % wr_addr)
    if (res == str)
        t_i(act)
    else
        t_e(act)
    end
end

test "sram_to_qspi" do
    rte_ob_test
end

test "dump" do
    #break
    $ts.dut.run("mera-cmd debug api ob")
    io_fpga_rw("dump 0x0100 16")
    io_sram_rw("dump 0x0200 16")
end
