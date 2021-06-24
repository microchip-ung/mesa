#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

def qspi_dump
    qspi_rw("mr.")
    qspi_rw("cr.")
    qspi_rw("ricr.")
    qspi_rw("wicr.")
    qspi_rw("ifr.")
    qspi_rw("sr.")
end

def qspi_overlay
    ol = "/sys/kernel/config/device-tree/overlays/tsys01"
    $ts.dut.run("mount -t configfs none /sys/kernel/config")
    $ts.dut.run("mkdir -p #{ol}")
    $ts.dut.run("cat /overlays/qspi_overlay.dtbo > #{ol}/dtbo")
end

def rmw(reg, msk)
    val = $ts.dut.run("symreg -r #{reg}")[:out][2..11].to_i(16)
    $ts.dut.run("symreg -r #{reg} #{val | msk}")
    $ts.dut.run("symreg -r #{reg}")
end

def qspi_setup
    $ts.dut.run("symreg -r gck[1] 0x3b0001")
    #rmw("gcb_gpio_alt1[0]", 0xf8000000)
    #rmw("gcb_gpio_alt2[0]", 0x00000001)
    qspi_rw("cr", "dllon", 1)
    qspi_rw("mr", "smm", 1)
    qspi_rw("cr", "updcfg", 1)
    qspi_rw("cr", "qspien", 1)
    qspi_rw("ricr", "rdinst", 0xeb)
    qspi_rw("wicr", "wrinst", 0x38)
    #qspi_rw("ifr", "apbtfrtyp", 1)
    #qspi_rw("ifr", "tfrtyp", 1)
    #qspi_rw("ifr", "nbdum", 6)
    #qspi_rw("ifr", "addrl", 2)
    #qspi_rw("ifr", "dataen", 1)
    #qspi_rw("ifr", "addren", 1)
    #qspi_rw("ifr", "insten", 1)
    #qspi_rw("ifr", "width", 4)
    qspi_rw("ifr", 0x010618b4)
    qspi_rw("cr", "lastxfer", 1)
    qspi_rw("cr", "updcfg", 1)
end

test "conf" do
    # Initialize QSPI
    #qspi_init

    # Clear IO memory
    #io_fpga_rw("fill 0x0100 0x100 0")

    qspi_overlay
    #qspi_setup

    qspi_rw("sr.")
    $ts.dut.run("symreg gck[1].")

    #vcore_rw(0x40000100, 0x12345678)
    #io_fpga_rw("dump 0x0100 16")
end
