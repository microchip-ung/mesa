#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

# Check if internal CPU
cap_check_exit("MISC_CPU_TYPE")

test "link-down" do
    $ts.pc.p.each do |eth|
        $ts.pc.run("ip link set #{eth} down")
    end
    $ts.dut.p.each do |port|
        conf = $ts.dut.call("mesa_port_conf_get", port)
        type = conf["if_type"]
        name = "los"
        if (type == "MESA_PORT_INTERFACE_SGMII" or
            type == "MESA_PORT_INTERFACE_QSGMII")
            name = "flnk"
        end
        cnt = $ts.dut.call("mesa_event_get", name, port)
        check_counter("#{name}[#{port}]", cnt, 1)
    end
end

test "dump" do
    str = ""
    $ts.dut.p.each do |port|
        if (str != "")
            str += ","
        end
        str += "#{port + 1}"
    end
    $ts.dut.run("mesa-cmd port mode #{str}")
    $ts.dut.run("mesa-cmd deb api ai port #{str}")
    $ts.dut.run("mesa-cmd deb api ai phy #{str}")
    $ts.dut.run("mesa-cmd intr")
end
