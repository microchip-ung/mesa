#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require "pp"
require "json"
require_relative 'libeasy/et'

meta = {
    "owner" => "anielsen",
    "desc"  => "Reboot, load new SW, and start mesa-demo",
}

$ts = get_test_setup("mesa_pc_b2b_2x")

$ts.dut.run("mesa-cmd deb sym read DEVCPU_PTP:PTP_TOD_DOMAINS[0-2]:CLK_PER_CFG")
