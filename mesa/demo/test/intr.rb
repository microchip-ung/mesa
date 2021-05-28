#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'oam_lib'

$ts = get_test_setup("mesa_pc_b2b_2x")

# Check if internal CPU
cap_check_exit("MISC_CPU_TYPE")

def check_event_counter(name, port = 0, value = -1)
    cnt = $ts.dut.call("mesa_event_get", name, port)
    if (value < 0)
        # Default: Check that counter is non-zero
        value = (cnt == 0 ? 1 : cnt)
    end
    check_counter("#{name}[#{port}]", cnt, value)
end

test "oam" do
    # Check that OAM is supported
    if (cap_get("VOP") == 0)
        break
    end

    # Setup VOP
    vop_config(0)

    # Allocate port VOE
    voe_idx = voe_alloc("MESA_VOE_TYPE_PORT", $ts.dut.p[0]);

    # Setup VOE
    voe_config(voe_idx, 0, 0)

    # Enable/disable CCM to start/stop LOC events
    [true, false].each do |enable|
        voe_cc_config(voe_idx, enable, 0, [], 0, "MESA_VOE_CCM_PERIOD_10_MS")
    end

    # Check VOE event
    check_event_counter("voe", 0)
end

test "ptp-rdy" do
    # Not supported for Caracal
    if (cap_get("MISC_CHIP_FAMILY") == chip_family_to_id("MESA_CHIP_FAMILY_CARACAL"))
        break
    end

    # Add ACE matching all frames with two step action
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ANY")
    ace["id"] = 1
    ace["port_list"] = "#{$ts.dut.p[0]}"
    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
    action["port_list"] = "#{$ts.dut.p[1]}"
    action["ptp_action"] = "MESA_ACL_PTP_ACTION_TWO_STEP"
    $ts.dut.call("mesa_ace_add", 0, ace)

    # Send frame
    run_ef_tx_rx_cmd($ts, 0, [1], "eth")

    # Update from timestamp FIFO to stop events
    $ts.dut.call("mesa_tx_timestamp_update")

    # Check timestamp event
    check_event_counter("clk_ts", 0)
end

test "link-down" do
    # Take links down
    $ts.pc.p.each do |eth|
        $ts.pc.run("ip link set #{eth} down")
    end

    # Check for LOS/FLNK event
    $ts.dut.p.each do |port|
        conf = $ts.dut.call("mesa_port_conf_get", port)
        type = conf["if_type"]
        name = "los"
        if (type == "MESA_PORT_INTERFACE_SGMII" or
            type == "MESA_PORT_INTERFACE_QSGMII")
            name = "flnk"
        end
        check_event_counter(name, port, 1)
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
