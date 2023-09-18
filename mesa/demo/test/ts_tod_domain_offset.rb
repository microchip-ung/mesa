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

def tod_domain_offset_test(domain, seconds)
    test "tod_domain_offset_test  doamin = #{domain}  seconds = #{seconds}" do

    #domain == 3 indicates use of default domain API
    domain_def = (domain == 3) ? true : false
    if (domain_def)
        domain = 0    # The default domain is 0
    end

    t_i("Test delta TOD in seconds")

    # Set TOD to 'second'
    tod  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    tod[0]["seconds"] = seconds
    tod[0]["nanoseconds"] = 0
    tod[0]["nanosecondsfrac"] = 0
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", tod[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod[0])
    a = Time.now()

    t_i("Set TOD delta 10 seconds - positive")
    tod[0]["seconds"] = 10
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set_delta", tod[0], false) : $ts.dut.call("mesa_ts_domain_timeofday_set_delta", domain, tod[0], false)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    b = Time.now()
    execution = b-a

    new_f = tod_new[0]["seconds"].to_f + (tod_new[0]["nanoseconds"].to_f / 1000000000.0)
    diff_f = new_f - seconds.to_f - execution

    t_i("diff_f = #{diff_f}  seconds.to_f = #{seconds.to_f}  new_f = #{new_f}  execution = #{execution}")
    if ((diff_f < 9.7) ||  (diff_f > 10.3))
        t_e("TOD in domain #{domain} was not read as expected.")
    end

    tod[0]["seconds"] = seconds
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", tod[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod[0])
    a = Time.now()

    t_i("Set TOD delta 10 seconds - negative")
    tod[0]["seconds"] = 10
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set_delta", tod[0], true) : $ts.dut.call("mesa_ts_domain_timeofday_set_delta", domain, tod[0], true)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    b = Time.now()
    execution = b-a

    new_f = tod_new[0]["seconds"].to_f + (tod_new[0]["nanoseconds"].to_f / 1000000000.0)
    diff_f = new_f - seconds.to_f - execution

    t_i("diff_f = #{diff_f}  seconds.to_f = #{seconds.to_f}  new_f = #{new_f}  execution = #{execution}")
    if ((diff_f < -10.2) ||  (diff_f > -9.8))
        t_e("TOD in domain #{domain} was not read as expected.")
    end

    t_i("Test delta TOD in nanoseconds")

    tod_get  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    a = Time.now()

    t_i ("Set TOD delta 0.5 seconds - positive")
    tod[0]["seconds"] = 0
    tod[0]["nanoseconds"] = 500000000
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set_delta", tod[0], false) : $ts.dut.call("mesa_ts_domain_timeofday_set_delta", domain, tod[0], false)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    b = Time.now()
    execution = b-a

    new_f = tod_new[0]["seconds"].to_f + (tod_new[0]["nanoseconds"].to_f / 1000000000.0)
    get_f = tod_get[0]["seconds"].to_f + (tod_get[0]["nanoseconds"].to_f / 1000000000.0)
    diff_f = new_f - get_f - execution
    t_i("diff_f = #{diff_f}  get_f = #{get_f}  new_f = #{new_f}  execution = #{execution}")
    if ((diff_f > 0.6) || (diff_f < 0.39))
        t_e("TOD in domain #{domain} was not read as expected")
    end

    tod_get  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    a = Time.now()

    t_i("Set TOD delta 0.5 seconds - negative")
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set_delta", tod[0], true) : $ts.dut.call("mesa_ts_domain_timeofday_set_delta", domain, tod[0], true)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    b = Time.now()
    execution = b-a

    new_f = tod_new[0]["seconds"].to_f + (tod_new[0]["nanoseconds"].to_f / 1000000000.0)
    get_f = tod_get[0]["seconds"].to_f + (tod_get[0]["nanoseconds"].to_f / 1000000000.0)
    diff_f = new_f - get_f - execution
    t_i("diff_f = #{diff_f}  get_f = #{get_f}  new_f = #{new_f}  execution = #{execution}")
    if ((diff_f > -0.4) || (diff_f < -0.6))
        t_e("TOD in domain #{domain} was not read as expected")
    end

    t_i("Test TOD offset in nanoseconds")

    t_i("Set TOD offset 0.5 seconds - positive. Its weired - offset parameter is signed but always subtracted in the API, so in order to add an offset it has to be negative :-)")
    tod_get  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    a = Time.now()
    domain_def ? $ts.dut.call("mesa_ts_timeofday_offset_set", -500000000) : $ts.dut.call("mesa_ts_domain_timeofday_offset_set", domain, -500000000)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    b = Time.now()
    execution = b-a

    new_f = tod_new[0]["seconds"].to_f + (tod_new[0]["nanoseconds"].to_f / 1000000000.0)
    get_f = tod_get[0]["seconds"].to_f + (tod_get[0]["nanoseconds"].to_f / 1000000000.0)
    diff_f = new_f - get_f - execution
    t_i("diff_f = #{diff_f}  get_f = #{get_f}  new_f = #{new_f}  execution = #{execution}")
    if ((diff_f > 0.6) || (diff_f < 0.4))
        t_e("TOD in domain #{domain} was not read as expected")
    end

    t_i("Set TOD offset 0.5 seconds - negative. Its weired - offset parameter is signed but always subtracted in the API, so in order to subtract an offset it has to be positive :-)")
    tod_get  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    a = Time.now()
    domain_def ? $ts.dut.call("mesa_ts_timeofday_offset_set", 500000000) : $ts.dut.call("mesa_ts_domain_timeofday_offset_set", domain, 500000000)

    # Check new TOD
    tod_new  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    b = Time.now()
    execution = b-a

    new_f = tod_new[0]["seconds"].to_f + (tod_new[0]["nanoseconds"].to_f / 1000000000.0)
    get_f = tod_get[0]["seconds"].to_f + (tod_get[0]["nanoseconds"].to_f / 1000000000.0)
    diff_f = new_f - get_f - execution
    t_i("diff_f = #{diff_f}  get_f = #{get_f}  new_f = #{new_f}  execution = #{execution}")
    if ((diff_f > -0.4) || (diff_f < -0.6))
        t_e("TOD in domain #{domain} was not read as expected")
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
    tod_domain_offset_test(3, 20)
end

test "test_clean_up" do
    $ts.dut.run "mesa-cmd Debug Port Polling enable"
end
