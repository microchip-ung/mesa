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
$external_io_out = 1
$diff_high = 2
$diff_low = 2

if ($pcb == "6849-Sunrise")
    $diff_high = 8
    $diff_low = 5
end
if ($pcb == "8291-EndNode")
    $external_io_in = 4
    $diff_high = 2
    $diff_low = 3
end
if ($pcb == 134)
    $diff_low = 3
end
if ($pcb == "8290")
    $external_io_in = 0
    $external_io_out = 3
    $diff_high = 2
    $diff_low = 3
end
if ($pcb == 111)
    $external_io_out = 0
    $diff_high = 16
    $diff_low = 25
end
if ($pcb == "6813-Adaro")
    $external_io_in = 0
    $diff_high = 10
    $diff_low = 10
end
t_i "$external_io_out #{$external_io_out} $external_io_in #{$external_io_in}"

def tod_external_io_1pps_test
    test "tod_external_io_1pps_test" do

    # Init Set TOD
    tod = $ts.dut.call("mesa_ts_domain_timeofday_get", 0)
    tod_ts1 = tod[0]

    t_i("Configure 1PPS output pin to no 1PPS output")
    pin_conf = $ts.dut.call("mesa_ts_external_io_mode_get", $external_io_out)
    pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_DISABLE"
    pin_conf["freq"] = 0
    $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_out, pin_conf)

    for domain in 0..2
        test "domain = #{domain}" do
        t_i("Set TOD to zero")
        tod_ts1["seconds"] = 0
        tod_ts1["nanoseconds"] = 0
        $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod_ts1)

        t_i("Configure 1PPS input pin to this domain")
        pin_conf["domain"] = domain
        pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_SAVE"
        $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_in, pin_conf)

        t_i("Get TOD on 1PPS input pin")
        pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
        pin_ts1 = pin[0]

        sleep(1.6)

        t_i("Get TOD on 1PPS input pin again to check not incremented")
        pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
        pin_ts2 = pin[0]
        if (pin_ts1["seconds"] != pin_ts2["seconds"])
            t_e("Case 1PPS is not enabled. TOD in domain #{domain} was not as expected.  pin_ts1[seconds] = #{pin_ts1["seconds"]}  pin_ts2[seconds] = #{pin_ts2["seconds"]}")
        end

        t_i("Configure 1PPS output pin to this domain")
        pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_OUTPUT"
        $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_out, pin_conf)

        t_i("Get TOD on 1PPS input pin")
        5.times {
            pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
            if (pin[0]["seconds"] > pin_ts1["seconds"])
                break
            end
            sleep(0.8)
        }
        pin_ts1 = pin[0]

        sleep(0.8)

        t_i("Get TOD on 1PPS input pin to check incremented")
        pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
        if (pin[0]["seconds"] == pin_ts1["seconds"])
            sleep(0.2)
            pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
        end

        pin_ts2 = pin[0]
        if ((pin_ts2["seconds"] > (pin_ts1["seconds"] + 2)) || (pin_ts2["seconds"] <= pin_ts1["seconds"]))
            t_e("Case 1PPS is enabled. TOD in domain #{domain} was not as expected.  pin_ts1[seconds] = #{pin_ts1["seconds"]}  pin_ts2[seconds] = #{pin_ts2["seconds"]}")
        end

        t_i("Configure 1PPS output pin to no 1PPS output")
        pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_DISABLE"
        $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_out, pin_conf)
        end
    end
    end
end

def tod_external_io_1pps_tod_offset_test
    test "tod_external_io_1pps_tod_offset_test" do

    domain_out = 0
    domain_in = 1
    offset = 10000000

    t_i("Init Set TOD")
    tod = $ts.dut.call("mesa_ts_domain_timeofday_get", domain_out)
    ts = tod[0]

    t_i("Configure 1PPS input pin")
    pin_conf = $ts.dut.call("mesa_ts_external_io_mode_get", $external_io_in)
    pin_conf["domain"] = domain_in
    pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_SAVE"
    $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_in, pin_conf)

    t_i("Set TOD to zero for both domains")
    ts["seconds"] = 1
    ts["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_domain_timeofday_set", domain_in, ts)
    $ts.dut.call("mesa_ts_domain_timeofday_set", domain_out, ts)

    t_i("Configure 1PPS output pin")
    pin_conf = $ts.dut.call("mesa_ts_external_io_mode_get", $external_io_out)
    pin_conf["domain"] = domain_out
    pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_OUTPUT"
    pin_conf["freq"] = 0
    $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_out, pin_conf)

    sleep(0.5)
    tod = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)

    sleep(0.7)

    # Get base line TOD on 1PPS input pin
    tod = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
    ts1 = tod[0]

    t_i("Set TOD offset 0.1 seconds - positive. Its weird - offset parameter is signed but always subtracted in the API, so in order to add an offset it has to be negative")
    $ts.dut.call("mesa_ts_domain_timeofday_offset_set", domain_out, -offset)

    sleep(0.5)

    tod = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
    sleep(0.7)

    # Get TOD on 1PPS input pin
    tod = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
    ts2 = tod[0]

    diff = ts1["nanoseconds"] - ts2["nanoseconds"]
    t_i("Difference #{diff} in TOD nanoseconds must be approx #{offset}")
    if (diff > (offset+$diff_high)) || (diff < (offset-$diff_low))
        t_e("Difference is not as expected")
    end

    t_i("Set TOD offset 0.1 seconds - negative. Its weird - offset parameter is signed but always subtracted in the API, so in order to subtract an offset it has to be positive")
    $ts.dut.call("mesa_ts_domain_timeofday_offset_set", domain_out, offset)

    sleep(0.5)

    tod = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
    sleep(0.7)

    # Get TOD on 1PPS input pin
    tod = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
    ts2 = tod[0]

    diff = ts2["nanoseconds"] - ts1["nanoseconds"]
    t_i("Difference #{diff} in TOD nanoseconds must be approx 0")
    if ((diff > $diff_high) || (diff < -$diff_low))
        t_e("Difference is not as expected")
    end
    end
end

test "test_conf" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # External io mode save
    $extern_io_mode_restore_in = $ts.dut.call("mesa_ts_external_io_mode_get", $external_io_in)

    $ts.dut.run "mesa-cmd Debug Port Polling disable"
end

test "test_run" do
    # Test io clock 1PPS
    tod_external_io_1pps_test
    tod_external_io_1pps_tod_offset_test
end

test "test_clean_up" do
    # External io mode restore
    $ts.dut.call("mesa_ts_external_io_mode_set", $external_io_in, $extern_io_mode_restore_in)

    $ts.dut.run "mesa-cmd Debug Port Polling enable"
end