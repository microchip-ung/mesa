#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$ts = get_test_setup("mesa_pc_b2b_2x")

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
    $cap_core_clock = $ts.dut.call("mesa_capability", "MESA_CAP_INIT_CORE_CLOCK")
end

$pcb = $ts.dut.pcb

$external_io_in = 2
$external_io_out = 1
if ($pcb == "6813-Adaro")
    $external_io_in = 0
end
if ($pcb == 111)
    $external_io_out = 0
end
if ($pcb == "8291-EndNode")
    $external_io_in = 4
end
if ($pcb == "8290")
    $external_io_in = 0
    $external_io_out = 3
end
if ($pcb == "8398")
    $external_io_out = 4
    $external_io_in = 5
end
t_i "external_io_in #{$external_io_in}  external_io_out #{$external_io_out}"


def get_saved_ts_diff
    test "get_saved_ts_diff" do
    $tod0 = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
    i = 0
    (0..20).each do |i|
        $tod1 = $ts.dut.call("mesa_ts_saved_timeofday_get", $external_io_in)
        if ($tod1[0]["seconds"] == ($tod0[0]["seconds"] + 1))
            break;
        end
        if ($tod1[0]["seconds"] > ($tod0[0]["seconds"] + 1))
            # When seconds has incremented more than once we take a new sample
            $tod0 = $tod1.dup
        end
        if (i == 10)
            t_e("TOD seconds not incrementing correctly")
        end
    end
    end
    nano_diff = $tod1[0]["nanoseconds"] - $tod0[0]["nanoseconds"]
    t_i "nano_diff #{nano_diff}"
    return nano_diff
end

def tod_adj_timer_test(domain_out, domain_in)
    test "tod_adj_timer_test  domain = #{domain_out}" do
    if ($cap_core_clock != 0)
        # Get the core clock and set the maximum frequency adjustment
        misc = $ts.dut.call("mesa_misc_get")
        if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_625MHZ")
            adj_max = 11874999
            diff_high = 1190000
            diff_low = 1185000
        end
        if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_500MHZ")
            adj_max = 9499999
            diff_high = 951500
            diff_low = 948000
        end
        if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_328MHZ")
            adj_max = 6231998
            diff_high = 624184
            diff_low = 621888
        end
        if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_250MHZ")
            adj_max = 4749999
            diff_high = 476000
            diff_low = 474000
        end
    else
        adj_max = 11874999
        diff_high = 1190000
        diff_low = 1185000
    end
    diff_no_adj = 2
    if ($pcb == "6813-Adaro")
        diff_no_adj = 8
        adj_max = 1200000
        diff_high = 120114
        diff_low = 119885
    end
    if ($pcb == "8290") || ($pcb == "8291")
        diff_no_adj = 8
        adj_max = 2400000
        diff_high = 240114
        diff_low = 239885
    end
    if ($pcb == "6849-Sunrise")
        diff_no_adj = 12
        adj_max = 1300000
        diff_high = 130100
        diff_low = 129900
    end

    t_i "diff_high #{diff_high}  diff_low #{diff_low}  adj_max #{adj_max}"
    #domain_out == 3 indicates use of default domain API
    domain_def = (domain_out == 3) ? true : false
    if (domain_def)
        domain_out = 0    # The default domain is 0
    end

    t_i("Get and save current frequency adjustment")
    adjtimer = domain_def ? $ts.dut.call("mesa_ts_adjtimer_get") : $ts.dut.call("mesa_ts_domain_adjtimer_get", domain_out)

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
    sleep 1.5

    diff = get_saved_ts_diff

    t_i("Difference #{diff}")
    if ((diff > diff_no_adj) || (diff < -diff_no_adj))
        t_e("Difference is not as expected")
    end

    t_i("Set frequency adjustment to maximum positive")
    domain_def ? $ts.dut.call("mesa_ts_adjtimer_set", adj_max) : $ts.dut.call("mesa_ts_domain_adjtimer_set", domain_out, adj_max)
    sleep 1.5

    diff = get_saved_ts_diff
    t_i("Difference #{diff}")
    if (diff.abs > diff_high) || (diff.abs < diff_low)
        t_e("Difference is not as expected")
    end

    t_i("Set frequency adjustment to maximum negative")
    domain_def ? $ts.dut.call("mesa_ts_adjtimer_set", -adj_max) : $ts.dut.call("mesa_ts_domain_adjtimer_set", domain_out, -adj_max)
    sleep 1.5

    diff = get_saved_ts_diff
    t_i("Difference #{diff}")
    if (diff.abs > diff_high) || (diff.abs < diff_low)
        t_e("Difference is not as expected")
    end

    t_i("Set frequency adjustment to saved")
    domain_def ? $ts.dut.call("mesa_ts_adjtimer_set", adjtimer) : $ts.dut.call("mesa_ts_domain_adjtimer_set", domain_out, adjtimer)
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
   #tod_adj_timer_test1(domain_out, domain_in)
    tod_adj_timer_test(0, 1)
    tod_adj_timer_test(1, 2)
    tod_adj_timer_test(2, 0)
    tod_adj_timer_test(3, 1)
end

test "test_clean_up" do
    # Frequency adjustment restore
    $ts.dut.call("mesa_ts_domain_adjtimer_set", 0, $frequence_adjustment_restore0)
    $ts.dut.call("mesa_ts_domain_adjtimer_set", 1, $frequence_adjustment_restore1)
    $ts.dut.call("mesa_ts_domain_adjtimer_set", 2, $frequence_adjustment_restore2)
end
