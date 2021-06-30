#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

dut_cap_check_exit("rte")

#---------- Configuration -----------------------------------------------------

test "conf" do
    # Initialize QSPI
    qspi_init

    # Clear IO memory
    io_fpga_rw("fill 0x0100 0x100 0")

    # Write data
    vcore_rw(0x40000100, 0x12345678)

    # Check IO-FPGA data (swapped)
    str = "78563412"
    res = io_str_rd(0x100, str)
    t_i("Exp  : #{str}")
    act = "0x100: #{res}"
    if (res == str)
        t_i(act)
    else
        t_e(act)
    end

    # Read IO memory
    io_fpga_rw("dump 0x0100 16")
end
