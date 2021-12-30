#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5) or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")} (Lan966x) or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")} (Lan969x)")
    assert(($ts.ts_external_clock_looped == true),
           "External clock must be looped")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
end

$mstoen_gpio = 55
$slvoen_gpio = 54
$rs422_out_pin = 3
$rs422_in_pin = 2

def tod_external_io_rs422_1pps_test
    test "tod_external_io_rs422_1pps_test" do

    # Init Set TOD
    tod = $ts.dut.call("mesa_ts_domain_timeofday_get", 0)
    tod_ts = tod[0]

    # Configure 1PPS output pin to no 1PPS output
    pin_conf = $ts.dut.call("mesa_ts_external_io_mode_get", $rs422_out_pin)
    pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_DISABLE"
    pin_conf["freq"] = 0
    $ts.dut.call("mesa_ts_external_io_mode_set", $rs422_out_pin, pin_conf)

    for domain in 0..2
        test "domain = #{domain}" do
        # Set TOD 
        tod_ts["seconds"] = 0
        tod_ts["nanoseconds"] = 0
        $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod_ts)

        # Configure RS422 1PPS input pin to this domain
        pin_conf["domain"] = domain
        pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_SAVE"
        $ts.dut.call("mesa_ts_external_io_mode_set", $rs422_in_pin, pin_conf)

        # Configure RS422 1PPS output pin to this domain
        pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_OUTPUT"
        $ts.dut.call("mesa_ts_external_io_mode_set", $rs422_out_pin, pin_conf)

        sleep(1)

        # Get TOD on 1PPS input pin
        in_pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $rs422_in_pin)
        in_pin_tod1 = in_pin[0]

        # Get saved TOD nanoseconds
        saved_nano1 = $ts.dut.call("mesa_ts_alt_clock_saved_get")
        saved_nano1 >>= 16

        sleep(1)

        # Get TOD on 1PPS input pin
        in_pin = $ts.dut.call("mesa_ts_saved_timeofday_get", $rs422_in_pin)
        in_pin_tod2 = in_pin[0]

        # Get saved TOD nanoseconds
        saved_nano2 = $ts.dut.call("mesa_ts_alt_clock_saved_get")
        saved_nano2 >>= 16

        if (in_pin_tod2["seconds"] != (in_pin_tod1["seconds"] + 1))
            t_e("TOD is not incremented as expected.  in_pin_tod1[seconds] = #{in_pin_tod1["seconds"]}  in_pin_tod2[seconds] = #{in_pin_tod2["seconds"]}")
        end

        if ((saved_nano2 != saved_nano1) || (saved_nano2 > 50))   # The max of 50 nano is experimental
            t_e("Saved nanoseconds is not as expected.  saved_nano1 = #{saved_nano1}  saved_nano2 = #{saved_nano2}")
        end

        # Configure RS422 1PPS output pin to DISABLE
        pin_conf["pin"] = "MESA_TS_EXT_IO_MODE_ONE_PPS_DISABLE"
        $ts.dut.call("mesa_ts_external_io_mode_set", $rs422_out_pin, pin_conf)
        end
    end
    end
end

test "test_conf" do
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        t_i("Test not implemented yet")
        exit 0
    end

    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # Assert buffer output enable
    $ts.dut.call("mesa_gpio_mode_set", 0, $mstoen_gpio, "MESA_GPIO_OUT")
    $ts.dut.call("mesa_gpio_mode_set", 0, $slvoen_gpio, "MESA_GPIO_OUT")
    $ts.dut.call("mesa_gpio_write", 0, $mstoen_gpio, true)
    $ts.dut.call("mesa_gpio_write", 0, $slvoen_gpio, false)

    # External io mode save
    $extern_io_mode_restore0 = $ts.dut.call("mesa_ts_external_io_mode_get", $rs422_in_pin)
    $extern_io_mode_restore1 = $ts.dut.call("mesa_ts_external_io_mode_get", $rs422_out_pin)
end

test"test_run" do
    # Test io clock on the RS422 interface
    tod_external_io_rs422_1pps_test
end

test "test_clean_up" do
    # External io mode restore
    $ts.dut.call("mesa_ts_external_io_mode_set", $rs422_in_pin, $extern_io_mode_restore0)
    $ts.dut.call("mesa_ts_external_io_mode_set", $rs422_out_pin, $extern_io_mode_restore1)

    # GPIO mode restore. Input is deafult
    $ts.dut.call("mesa_gpio_mode_set", 0, $mstoen_gpio, "MESA_GPIO_IN")
    $ts.dut.call("mesa_gpio_mode_set", 0, $slvoen_gpio, "MESA_GPIO_IN")
end