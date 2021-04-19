#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

test "conf" do
    id = $ts.dut.call("mesa_chip_id_get")
    part_no = id["part_number"]
    rev = id["revision"]
    msg = "part_no: 0x#{part_no.to_s(16)}, revision: #{rev}"
    if ((part_no >> 12) == 7)
        t_i(msg)
    else
        t_e(msg)
    end
end
