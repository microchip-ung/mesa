#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$ts = get_test_setup("mesa_pc_b2b_2x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5). or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")} (Lan966x).")
    assert(($ts.ts_external_clock_looped == true),
           "External clock must be looped")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
end

$pcb = $ts.dut.pcb

$external_io_in = 2
if ($pcb == "6813-Adaro")
    $external_io_in = 0
end
if ($pcb == "8291-EndNode")
    $external_io_in = 4
end
if ($pcb == "8290")
    $external_io_in = 0
end
t_i "external_io_in #{$external_io_in}"

def tod_external_clock_1pps_test
    test "tod_external_clock_1pps_test" do

    # Init Set TOD
    tod = $ts.dut.call("mesa_ts_domain_timeofday_get", 0)
    $tod_ts1 = tod[0]

    # Init Configure TOD input pin
    pin_conf = $ts.dut.call("mesa_ts_external_io_mode_get", $external_io_in)
    pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_SAVE"
    pin_conf["freq"] = 0

    # Init Configure external 1PPS output to NONE
    ext_conf = $ts.dut.call("mesa_ts_external_clock_mode_get")
    ext_conf["one_pps_mode"] = "MESA_TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE"
    ext_conf["enable"] = false
    ext_conf["freq"] = 0
    $ts.dut.call("mesa_ts_external_clock_mode_set", ext_conf)

    for domain in 0..2
        test "domain = #{domain}" do

        # Set TOD 
        $tod_ts1["seconds"] = 0
        $tod_ts1["nanoseconds"] = 0
        $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts1)

        # Configure 1PPS input pin to this domain
        pin_conf["domain"] = domain
        $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_in, pin_conf)

        # Get TOD on 1PPS input pin
        pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
        pin_ts1 = pin[0]

        sleep(1.6)

        # Get TOD on 1PPS input pin again to check not incremented
        pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
        pin_ts2 = pin[0]
        if (pin_ts1["seconds"] != pin_ts2["seconds"])
            t_e("Case 1PPS is not enabled. TOD in domain #{domain} was not as expected.  pin_ts1[seconds] = #{pin_ts1["seconds"]}  pin_ts2[seconds] = #{pin_ts2["seconds"]}")
        end

        t_i "Configure external 1PPS output that is looped back to 1PPS input pin"
        ext_conf["one_pps_mode"] = "MESA_TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT"
        $ts.dut.call("mesa_ts_external_clock_mode_set", ext_conf)
        sleep(0.9)

        t_i "Get TOD on 1PPS input pin"
        5.times {
            pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
            if (pin[0]["seconds"] > pin_ts1["seconds"])
                break
            end
            sleep(0.8)
        }
        pin_ts1 = pin[0]

        sleep(1.6)

        # Get TOD on 1PPS input pin to check incremented
        pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
        pin_ts2 = pin[0]
        if ((pin_ts2["seconds"] > (pin_ts1["seconds"] + 2 + 1)) || (pin_ts2["seconds"] <= pin_ts1["seconds"]))
            t_e("Case 1PPS is enabled. TOD in domain #{domain} was not as expected.  pin_ts1[seconds] = #{pin_ts1["seconds"]}  pin_ts2[seconds] = #{pin_ts2["seconds"]}")
        end

        t_i "Configure external to no 1PPS output"
        ext_conf["one_pps_mode"] = "MESA_TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE"
        $ts.dut.call("mesa_ts_external_clock_mode_set", ext_conf)
        end
    end
    end
end

test "test_conf" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # External clock mode save
    $external_clock_mode_restore = $ts.dut.call("mesa_ts_external_clock_mode_get")

    # External io mode save
    $extern_io_mode_restore_in = $ts.dut.call("mesa_ts_external_io_mode_get", $external_io_in)

    $ts.dut.run "mesa-cmd Debug Port Polling disable"
end

test "test_run" do
    # Test external clock 1PPS
    tod_external_clock_1pps_test
end

test "test_clean_up" do
    # External clock mode restore
    $ts.dut.call("mesa_ts_external_clock_mode_set", $external_clock_mode_restore)

    # External io mode restore
    $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_in, $extern_io_mode_restore_in)

    $ts.dut.run "mesa-cmd Debug Port Polling enable"
end