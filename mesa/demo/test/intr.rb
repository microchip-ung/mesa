#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

# Check if internal CPU
cap_check_exit("MISC_CPU_TYPE")

test "los" do
    # Find SFP port
    sfp = nil
    $ts.dut.p.each do |port|
        conf = $ts.dut.call("mesa_port_conf_get", port)
        if (conf["if_type"] == "MESA_PORT_INTERFACE_SGMII_CISCO")
            sfp = port
            break
        end
    end
    port = sfp
    if (port == nil)
        t_i("no SFP ports found")
        break
    end

    $ts.dut.run("mesa-cmd port state #{port + 1} dis")
    sleep(1)
    cnt = $ts.dut.call("mesa_event_get", "los", port)
    check_counter("los[#{port}]", cnt, 1)
end

test "dump" do
    $ts.dut.run("mesa-cmd intr")
end
