#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'
require 'time'

$ts = get_test_setup("mesa_pc_b2b_2x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5) or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")} (Lan966x) or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")} (Lan969x)")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
end

def tod_external_clock_frequence_test
    test "tod_external_clock_frequence_test" do

    # External clock mode configuration
    conf = $ts.dut.call("mesa_ts_external_clock_mode_get")
    conf["one_pps_mode"] = "MESA_TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE"
    conf["enable"] = true
    conf["freq"] = 24000000
    $ts.dut.call("mesa_ts_external_clock_mode_set", conf)

    for domain in 0..2
        # Set TOD
        tod = $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        tod_ts = tod[0]
        tod_ts["seconds"] = 10
        tod_ts["nanoseconds"] = 0
        $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod_ts)
        a = Time.now()

        # Get TOD after to check configuration
        tod = $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        tod_ts = tod[0]
        if (tod_ts["seconds"] != 10)
            t_e("TOD in domain #{domain} was not configured as expected.  tod_ts[seconds] = #{tod_ts["seconds"]}  expected_seconds = 10")
        end

        sleep(1)

        # Get TOD to check TOD incremented
        tod = $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        b = Time.now()
        execution = b-a

        tod_f = tod[0]["seconds"].to_f + (tod[0]["nanoseconds"].to_f / 1000000000.0)
        diff_f = tod_f - 10.0 - execution
        t_i "tod_f #{tod_f}  diff_f #{diff_f}  diff_f.to_i #{diff_f.to_i}  execution #{execution}"

        if (diff_f.to_i != 0)
            t_e("TOD in domain #{domain} was not configured as expected.")
        end
    end

    # Check if TOD set is ongoing
    ongoinig = $ts.dut.call("mesa_ts_ongoing_adjustment")

    if (ongoinig)
        t_e("TOD set ongoing must not be true")
    end

    end
end

test "test_conf" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # External clock mode save
    $external_clock_mode_restore = $ts.dut.call("mesa_ts_external_clock_mode_get")
end

test "test_run" do
    # Test TOD with external clock frequence generator
    tod_external_clock_frequence_test
end

test "test_clean_up" do
    # External clock mode restore
    $ts.dut.call("mesa_ts_external_clock_mode_set", $external_clock_mode_restore)
end