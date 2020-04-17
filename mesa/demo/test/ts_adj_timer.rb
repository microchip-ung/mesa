#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$npi_port = 3
$port0 = 0
$cpu_queue = 7

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5).")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    $cap_core_clock = $ts.dut.call("mesa_capability", "MESA_CAP_INIT_CORE_CLOCK")
end

def tod_adj_timer_test(domain)
    test "tod_adj_timer_test  domain = #{domain}" do

    if ($cap_core_clock != 0)
        # Get the core clock and set the maximum frequency adjustment
        misc = $ts.dut.call("mesa_misc_get")
        if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_625MHZ")
            adj_max = 11874999
            nano_diff = 10000000
        end
        if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_500MHZ")
            adj_max = 9499999
            nano_diff = 10000000
        end
        if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_250MHZ")
            adj_max = 4749999
            nano_diff = 6000000
        end
    else
        adj_max = 11874999
        nano_diff = 10000000
    end

    measures = 3

    #domain == 3 indicates use of default domain API
    domain_def = (domain == 3) ? true : false
    if (domain_def)
        domain = 0    # The default domain is 0
    end

    # Set TOD to zero
    tod_ts  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    tod_ts[0]["seconds"] = 0
    tod_ts[0]["nanoseconds"] = 0
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", tod_ts[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod_ts[0])

    test "Measure 20 seconds without adjustment" do
    $sum_nano0 = 0
    (1..measures).each do |i|
        tod = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        tod1 = tod[0]
        sleep(20)
        tod = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        tod2 = tod[0]

        if (tod2["nanoseconds"] < tod1["nanoseconds"])
            console("Wrap detected")
            tod2["seconds"] -= 1    
            tod2["nanoseconds"] += 1000000000
        end
        $nano0 = ((tod2["seconds"] - tod1["seconds"]) * 1000000000) + (tod2["nanoseconds"] - tod1["nanoseconds"])
        console("nano = #{$nano0}  tod1[seconds] = #{tod1["seconds"]}  tod1[nanoseconds] = #{tod1["nanoseconds"]}  tod2[seconds] = #{tod2["seconds"]}  tod2[nanoseconds] = #{tod2["nanoseconds"]}")
        $sum_nano0 += $nano0
    end
    $nano0 = $sum_nano0/measures
    console("$nano0 = #{$nano0}")
    end

    # Set frequency adjustment to maximum positive
    domain_def ? $ts.dut.call("mesa_ts_adjtimer_set", adj_max) : $ts.dut.call("mesa_ts_domain_adjtimer_set", domain, adj_max)

    test "Measure 20 seconds with positive adjustment" do
    $sum_nano1 = 0
    (1..measures).each do |i|
        tod = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        tod1 = tod[0]
        sleep(20)
        tod = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        tod2 = tod[0]

        if (tod2["nanoseconds"] < tod1["nanoseconds"])
            console("Wrap detected")
            tod2["seconds"] -= 1    
            tod2["nanoseconds"] += 1000000000
        end
        $nano1 = ((tod2["seconds"] - tod1["seconds"]) * 1000000000) + (tod2["nanoseconds"] - tod1["nanoseconds"])
        console("diff = #{$nano1-$nano0}  nano = #{$nano1}  tod1[seconds] = #{tod1["seconds"]}  tod1[nanoseconds] = #{tod1["nanoseconds"]}  tod2[seconds] = #{tod2["seconds"]}  tod2[nanoseconds] = #{tod2["nanoseconds"]}")
        $sum_nano1 += $nano1
    end
    $nano1= $sum_nano1/measures
    console("$nano1 = #{$nano1}  diff = #{$nano1-$nano0}")
    if ($nano1 < ($nano0 + nano_diff))    # expect at least 10 ms longer
        t_e("Measured 20 seconds not as expected.  nano0 = #{$nano0}  nano1 = #{$nano1}")
    end
    end

    # Set frequency adjustment to maximum negative
    domain_def ? $ts.dut.call("mesa_ts_adjtimer_set", -adj_max) : $ts.dut.call("mesa_ts_domain_adjtimer_set", domain, -adj_max)

    test "Measure 20 seconds negative adjustment" do
    $sum_nano2 = 0
    (1..measures).each do |i|
        tod = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        tod1 = tod[0]
        sleep(20)
        tod = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
        tod2 = tod[0]

        if (tod2["nanoseconds"] < tod1["nanoseconds"])
            console("Wrap detected")
            tod2["seconds"] -= 1    
            tod2["nanoseconds"] += 1000000000
        end
        $nano2 = ((tod2["seconds"] - tod1["seconds"]) * 1000000000) + (tod2["nanoseconds"] - tod1["nanoseconds"])
        console("diff = #{$nano0-$nano2}  nano = #{$nano2}  tod1[seconds] = #{tod1["seconds"]}  tod1[nanoseconds] = #{tod1["nanoseconds"]}  tod2[seconds] = #{tod2["seconds"]}  tod2[nanoseconds] = #{tod2["nanoseconds"]}")
        $sum_nano2 += $nano2
    end
    $nano2= $sum_nano2/measures
    console("$nano2 = #{$nano2}  diff = #{$nano0-$nano2}")
    if ($nano2 > ($nano0 - nano_diff))    # expect at least 10 ms shorter
        t_e("Measured 20 seconds not as expected.  nano0 = #{$nano0}  nano2 = #{$nano2}")
    end
    end

    end
end

test "test_config" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # Frequency adjustment save
    $frequence_adjustment_restore0 = $ts.dut.call("mesa_ts_domain_adjtimer_get", 0)
    $frequence_adjustment_restore1 = $ts.dut.call("mesa_ts_domain_adjtimer_get", 1)
    $frequence_adjustment_restore2 = $ts.dut.call("mesa_ts_domain_adjtimer_get", 2)
end

test "test_run" do
    # Test frequency adjustment using domain specific API
    tod_adj_timer_test(0)
    tod_adj_timer_test(1)
    tod_adj_timer_test(2)

    # Test frequency adjustment using default domain (0) API. Domain value 3 is a illegal domain indicating default
    $ts.dut.call("mesa_ts_domain_adjtimer_set", 0, $frequence_adjustment_restore0)
    tod_adj_timer_test(3)
end

test "test_clean_up" do
    # Frequency adjustment restore
    $ts.dut.call("mesa_ts_domain_adjtimer_set", 0, $frequence_adjustment_restore0)
    $ts.dut.call("mesa_ts_domain_adjtimer_set", 1, $frequence_adjustment_restore1)
    $ts.dut.call("mesa_ts_domain_adjtimer_set", 2, $frequence_adjustment_restore2)
end

