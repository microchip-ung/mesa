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
    $cap_core_clock = $ts.dut.call("mesa_capability", "MESA_CAP_INIT_CORE_CLOCK")
end

MESA_VID_NULL = 0

ig = rand(3)    # Get a random ingress port between 0 and 3
begin   # Get a random egress port between 0 and 3 different from egress port
    eg = rand(3)
end while eg == ig

t_i("---------eg: #{eg}  ig: #{ig}---------")

$port0 = ig
$port1 = eg
$port2 = 2
$npi_port = 3
$pcb = $ts.dut.pcb


test "test_conf" do
    t_i("Configure the test by calling the example code command. No asymmetry delay")
    $ts.dut.run("mesa-cmd example init transparent_clock ing-port #{$ts.dut.p[ig]+1} eg-port #{$ts.dut.p[eg]+1} delay_mode 0")
end

test "test_run" do
    t_i("Time Stamp transparent clock test")

    t_i("Measure the lowest correction value")
    lowest_corr_none = nano_corr_lowest_measure

    if ($cap_core_clock != 0)
        misc = $ts.dut.call("mesa_misc_get")
        exp_corr = (misc["core_clock_freq"] == "MESA_CORE_CLOCK_250MHZ") ? 2 : 1
    else
        exp_corr = ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) ? 2 : 1
    end
    if ($pcb == 135)    #Test on Copper PHY
        if ((lowest_corr_none > 2380) || (lowest_corr_none < 1805))
            t_e("Unexpected correction field including egress delay. lowest_corr_none = #{lowest_corr_none}")
        end
    else
        if ((lowest_corr_none < 0) || ((lowest_corr_none / 1000) != exp_corr))
            t_e("Unexpected correction field including egress delay. lowest_corr_none = #{lowest_corr_none}")
        end
    end

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        diff_max = 520
    else
        diff_max = 100
    end
    if ($pcb == 135)    #Test on Copper PHY
        diff_max = 500
    end

    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")

    t_i("Configure the test by calling the example code command. Add asymmetry delay")
    asymmetry = lowest_corr_none-100
    $ts.dut.run("mesa-cmd example init transparent_clock ing-port #{$ts.dut.p[ig]+1} eg-port #{$ts.dut.p[eg]+1} delay_mode 1 asymmetry #{asymmetry}")

    t_i("Measure the lowest correction value with added asymmetry delay")
    lowest_corr_add = nano_corr_lowest_measure

    t_i("Check that the correction value has the added asymmetry delay")
    diff = (lowest_corr_add - (lowest_corr_none - asymmetry))
    if ((lowest_corr_none < lowest_corr_add) || (diff < -diff_max) || (diff > diff_max))
        t_e("Unexpected correction field including egress delay. lowest_corr_none = #{lowest_corr_none}  lowest_corr_add = #{lowest_corr_add}  diff #{diff}")
    end
end

test "test_clean_up" do
    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")
end
