#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

port_list = []

test "phy-port-list" do
    $ts.dut.port_list.each do |port|
        s = $ts.dut.try_ignore("meba_phy_status_poll", port)
        if (s != nil)
            port_list << port
        end
    end
end

test "phy-status" do
    port_list.each do |port|
        s = $ts.dut.call("meba_phy_status_poll", port)
        t_i("port #{port}, link: #{s["link"]}, speed: #{s["speed"]}")
    end
end

test "phy-power" do
    port_list.each do |port|
        $ts.dut.call("meba_phy_power_set", port, "MESA_PHY_POWER_ENABLED")
    end
end

test "dump" do
    str = ""
    pre = ""
    port_list.each do |port|
        str += "#{pre}#{port + 1}"
        pre = ","
    end
    $ts.dut.run("mesa-cmd port mode #{str}")
    $ts.dut.run("mesa-cmd debug api ai phy #{str}")
    $ts.dut.run("mesa-cmd debug api ai port #{str}")
end
