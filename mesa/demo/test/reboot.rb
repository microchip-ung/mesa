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

$ts = get_test_setup("mesa_pc_b2b_2x", {}, "-t api_cil:vcap:debug")
