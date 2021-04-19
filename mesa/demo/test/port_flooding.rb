#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Frame testing -----------------------------------------------------
test "frame-io" do
    $ts.pc.p.each do |idx_tx|
        cmd =  "sudo ef name f-#{idx_tx} eth dmac ff:ff:ff:ff:ff:ff smac ::1 "
        cmd += "tx #{idx_tx} name f-#{idx_tx} "
        $ts.pc.p.each do |idx_rx|
            if (idx_rx != idx_tx)
                cmd += "rx #{idx_rx} name f-#{idx_tx} "
            else
                cmd += "rx #{idx_rx} "
            end
        end
        $ts.pc.try cmd
    end
end
