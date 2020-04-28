#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5).")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
end

def tod_domain_offset_test(domain, seconds)
    test "tod_domain_offset_test  doamin = #{domain}  seconds = #{seconds}" do

    #domain == 3 indicates use of default domain API
    domain_def = (domain == 3) ? true : false
    if (domain_def)
        domain = 0    # The default domain is 0
    end

    console("Test delta TOD in seconds")

    # Set TOD to 'second'
    tod  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    tod[0]["seconds"] = seconds
    tod[0]["nanoseconds"] = 0
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", tod[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod[0])

    console("Set TOD delta 10 seconds - positive")
    tod[0]["seconds"] = 10
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set_delta", tod[0], false) : $ts.dut.call("mesa_ts_domain_timeofday_set_delta", domain, tod[0], false)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)

    if (tod_new[0]["seconds"] != seconds + 10)
        t_e("TOD in domain #{domain} was not read as expected.  expected seconds = #{seconds+10}  tod_new[seconds] = #{tod_new[0]["seconds"]}")
    end

    console("Set TOD delta 10 seconds - negative")
    tod[0]["seconds"] = 10
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set_delta", tod[0], true) : $ts.dut.call("mesa_ts_domain_timeofday_set_delta", domain, tod[0], true)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)

    if ((tod_new[0]["seconds"] < seconds) || (tod_new[0]["seconds"] > seconds+1))   #Accepting one second in execution time
        t_e("TOD in domain #{domain} was not read as expected.  expected seconds = #{seconds+1}  tod_new[seconds] = #{tod_new[0]["seconds"]}")
    end

    console("Test delta TOD in nanoseconds")

    # Clear TOD seconds and nanoseconds
    tod[0]["seconds"] = 0
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", tod[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod[0])

    console ("Set TOD delta 0.5 seconds - positive")
    tod[0]["nanoseconds"] = 500000000
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set_delta", tod[0], false) : $ts.dut.call("mesa_ts_domain_timeofday_set_delta", domain, tod[0], false)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)

    if ((tod_new[0]["seconds"] > 1) ||
        ((tod_new[0]["seconds"] == 1) && (tod_new[0]["nanoseconds"] > 200000000)) ||
        ((tod_new[0]["seconds"] == 0) && (tod_new[0]["nanoseconds"] < 700000000)))  #Accepting approx 700 ms in execution time
        t_e("TOD in domain #{domain} was not read as expected.  tod_new[seconds] = #{tod_new[0]["seconds"]}  tod_new[nanoseconds] = #{tod_new[0]["nanoseconds"]}")
    end

    console("Set TOD delta 0.5 seconds - negative")
    tod[0]["nanoseconds"] = 500000000
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set_delta", tod[0], true) : $ts.dut.call("mesa_ts_domain_timeofday_set_delta", domain, tod[0], true)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)

    if ((tod_new[0]["seconds"] > 1) ||
        ((tod_new[0]["seconds"] == 1) && (tod_new[0]["nanoseconds"] > 400000000)) ||
        ((tod_new[0]["seconds"] == 0) && (tod_new[0]["nanoseconds"] < 300000000)))  #Accepting approx 2*700 ms in execution time
        t_e("TOD in domain #{domain} was not read as expected.  tod_new[seconds] = #{tod_new[0]["seconds"]}  tod_new[nanoseconds] = #{tod_new[0]["nanoseconds"]}")
    end

    console("Test TOD offset in nanoseconds")

    # Clear TOD seconds and nanoseconds
    tod[0]["seconds"] = 0
    tod[0]["nanoseconds"] = 0
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", tod[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod[0])

    console("Set TOD offset 0.5 seconds - positive. Its weired - offset parameter is signed but always subtracted in the API, so in order to add an offset it has to be negative :-)")
    domain_def ? $ts.dut.call("mesa_ts_timeofday_offset_set", -500000000) : $ts.dut.call("mesa_ts_domain_timeofday_offset_set", domain, -500000000)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)

    if ((tod_new[0]["seconds"] > 1) || ((tod_new[0]["seconds"] == 1) && (tod_new[0]["nanoseconds"] > 200000000)))  #Accepting approx 700 ms in execution time
        t_e("TOD in domain #{domain} was not read as expected.  tod_new[seconds] = #{tod_new[0]["seconds"]}  tod_new[nanoseconds] = #{tod_new[0]["nanoseconds"]}")
    end

    console("Set TOD offset 0.5 seconds - negative. Its weired - offset parameter is signed but always subtracted in the API, so in order to subtract an offset it has to be positive :-)")
    domain_def ? $ts.dut.call("mesa_ts_timeofday_offset_set", 500000000) : $ts.dut.call("mesa_ts_domain_timeofday_offset_set", domain, 500000000)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)

    if ((tod_new[0]["seconds"] > 1) || ((tod_new[0]["seconds"] == 1) && (tod_new[0]["nanoseconds"] > 400000000)))  #Accepting approx 2*700 ms in execution time
        t_e("TOD in domain #{domain} was not read as expected.  tod_new[seconds] = #{tod_new[0]["seconds"]}  tod_new[nanoseconds] = #{tod_new[0]["nanoseconds"]}")
    end

    end
end

test "test_conf" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    $ts.dut.run "mesa-cmd Debug Port Polling disable"
end

test "test_run" do
    # Test TOD domains delta using domain specific API
    tod_domain_offset_test(0, 10)
    tod_domain_offset_test(1, 100)
    tod_domain_offset_test(2, 1000)

    # Test TOD domain delta using default domain (0) API. Domain value 3 is a illegal domain indicating default
    tod_domain_offset_test(3, 0)
end

test "test_clean_up" do
    $ts.dut.run "mesa-cmd Debug Port Polling enable"
end