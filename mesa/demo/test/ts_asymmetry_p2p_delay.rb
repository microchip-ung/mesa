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
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    $cap_core_clock = $ts.dut.call("mesa_capability", "MESA_CAP_INIT_CORE_CLOCK")
end

$port0 = 0
$port1 = 1
$vlan = 100
$acl_id = 1
$pcb = $ts.dut.pcb

def tod_asymmetry_p2p_delay_test
    test "tod_asymmetry_p2p_delay_test" do

    if ($cap_core_clock != 0)
        misc = $ts.dut.call("mesa_misc_get")
        if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_250MHZ")
            exp_corr = 2
        else if (misc["core_clock_freq"] == "MESA_CORE_CLOCK_328MHZ")
            exp_corr = 3
        else
            exp_corr = 1
        end
        end
    else
        misc = $ts.dut.call("mesa_misc_get")
        if (($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) ||
            ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")))
            exp_corr = 2
        else
            exp_corr = 1
        end
    end

    t_i("Create IS2 to ONE-STEP SYNC frame")
    conf = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ETYPE")
    conf["id"] = $acl_id
    conf["port_list"] = "#{$ts.dut.port_list[$port0]}"
    action = conf["action"]
    action["ptp_action"] = "MESA_ACL_PTP_ACTION_ONE_STEP"
    $ts.dut.call("mesa_ace_add", 0, conf)

    lowest_corr_none,range = nano_corr_lowest_measure

    test ("No asymmetry delay check of correction field") do
    if ($pcb == 135)    #Test on Copper PHY
        if ((lowest_corr_none > 3000) || (lowest_corr_none < 1830))
            t_e("Unexpected correction field including egress delay. lowest_corr_none = #{lowest_corr_none}")
        else
            t_i("CF ok")
        end
    else if (($ts.dut.pcb == "8281-SVB") || ($ts.dut.pcb == "6849-Sunrise"))
        if ((lowest_corr_none > 7010) || (lowest_corr_none < 0))
            t_e("Unexpected correction field including egress delay. lowest_corr_none = #{lowest_corr_none}")
        else
            t_i("CF ok")
        end
    else if ((lowest_corr_none < 0) || ((lowest_corr_none / 1000) > exp_corr))
            t_e("Unexpected correction field including egress delay. lowest_corr_none = #{lowest_corr_none}  exp_corr = #{exp_corr}")
        else
            t_i("CF ok")
        end
    end
    end
    end

    t_i("Configure asymmetry delay. It is selected to be as large as possible but smaller than the lowest measured correction")
    asymmetry = lowest_corr_none-200
    $ts.dut.call("mesa_ts_delay_asymmetry_set", $ts.dut.port_list[$port0], asymmetry<<16)
    $ts.dut.call("mesa_ts_delay_asymmetry_set", $ts.dut.port_list[$port1], asymmetry<<16)

    t_i("Change IS2 to ONE-STEP add egress delay SYNC frame")
    action["ptp_action"] = "MESA_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY"
    $ts.dut.call("mesa_ace_add", 0, conf)

    lowest_corr_eg,range1 = nano_corr_lowest_measure  #Measure lowest with asymmetry deducted
    diff0 = (lowest_corr_eg - (lowest_corr_none - asymmetry))

    range = (range1 > range) ? range1 : range
    range += range / 6
    diff_max = range / 2
    test ("The asymmetry delay is subtracted from correction on egress") do
    t_i("lowest_corr_none = #{lowest_corr_none}  lowest_corr_eg = #{lowest_corr_eg}  diff #{diff0}  diff_max #{diff_max}")
    if ((lowest_corr_none < lowest_corr_eg) || (diff0 < -diff_max) || (diff0 > diff_max))
        t_e("Unexpected correction field including egress delay.")
    else
        t_i("CF ok")
    end
    end

    t_i("Change IS2 to ONE-STEP add ingress delay 1 SYNC frame")
    action["ptp_action"] = "MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1"
    $ts.dut.call("mesa_ace_add", 0, conf)

    lowest_corr_in1,range1 = nano_corr_lowest_measure
    diff1 = (lowest_corr_in1 - (lowest_corr_none + asymmetry))

    range = (range1 > range) ? range1 : range
    range += range / 6
    diff_max = range / 2
    test ("The asymmetry delay is added to correction on ingress") do
    t_i("lowest_corr_none = #{lowest_corr_none}  lowest_corr_in1 = #{lowest_corr_in1}  diff #{diff1}  diff_max #{diff_max}")
    if ((lowest_corr_in1 < lowest_corr_none) || (diff1 < -diff_max) || (diff1 > diff_max))
        t_e("Unexpected correction field including egress delay.")
    else
        t_i("CF ok")
    end
    end

    # Change IS2 to ONE-STEP add ingress delay 2 SYNC frame
    action["ptp_action"] = "MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2"
    $ts.dut.call("mesa_ace_add", 0, conf)

    lowest_corr_in2,range1 = nano_corr_lowest_measure
    diff2 = (lowest_corr_in2 - (lowest_corr_none + asymmetry))

    range = (range1 > range) ? range1 : range
    range += range / 6
    diff_max = range / 2
    test ("The asymmetry + p2p delay is added to correction on ingress. The p2p delay is zero at this point.") do
    t_i("lowest_corr_none = #{lowest_corr_none}  lowest_corr_in2 = #{lowest_corr_in2}  diff #{diff2}  diff_max #{diff_max}")
    if ((lowest_corr_in2 < lowest_corr_none) || (diff2 < -diff_max) || (diff2 > diff_max))
        t_e("Unexpected correction field including egress delay.")
    else
        t_i("CF ok")
    end
    end

    # Configure p2p delay. It is selected to be as large as possible but smaller than the lowest measured correction
    $ts.dut.call("mesa_ts_p2p_delay_set", $ts.dut.port_list[$port0], asymmetry<<16)

    lowest_corr_in2,range1 = nano_corr_lowest_measure
    diff3 = (lowest_corr_in2 - (lowest_corr_none + 2*asymmetry))

    range = (range1 > range) ? range1 : range
    range += range / 6
    diff_max = range / 2
    test ("The asymmetry + p2p delay is added to correction on ingress") do
    t_i("lowest_corr_in1 = #{lowest_corr_in1}  lowest_corr_in2 = #{lowest_corr_in2}  diff #{diff3}  diff_max #{diff_max}")
    if ((lowest_corr_in2 < lowest_corr_in1) || (diff3 < -diff_max) || (diff3 > diff_max))
        t_e("Unexpected correction field including egress delay.")
    else
        t_i("CF ok")
    end
    end

    t_i("lowest_corr_none #{lowest_corr_none} lowest_corr_eg #{lowest_corr_eg} lowest_corr_in1 #{lowest_corr_in1} lowest_corr_in2 #{lowest_corr_in2}")
    t_i("diff_max #{diff_max} diff0 #{diff0} diff1 #{diff1} diff2 #{diff2} diff3 #{diff3}")
    end
end

test "test_config" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # Flush MAC table
    $ts.dut.call("mesa_mac_table_flush")

    # Set VLAN port configuration
    $vlan_port_conf_restore0 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$port0])
    conf = $vlan_port_conf_restore0.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_UNAWARE"
    conf["pvid"] = $vlan
    conf["untagged_vid"] = $vlan
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port0], conf)

    $vlan_port_conf_restore1 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$port1])
    conf = $vlan_port_conf_restore1.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_UNAWARE"
    conf["pvid"] = $vlan
    conf["untagged_vid"] = $vlan
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port1], conf)

    # Set VLAN memberships
    port_list = "#{$ts.dut.port_list[$port0]},#{$ts.dut.port_list[$port1]}"
    $ts.dut.call("mesa_vlan_port_members_set", $vlan, port_list)

    $asymmetry_conf_restore0 = $ts.dut.call("mesa_ts_delay_asymmetry_get", $ts.dut.port_list[$port0])
    $asymmetry_conf_restore1 = $ts.dut.call("mesa_ts_delay_asymmetry_get", $ts.dut.port_list[$port1])

    $p2p_conf_restore = $ts.dut.call("mesa_ts_p2p_delay_get", $ts.dut.port_list[$port0])
end

test "test_run" do
    # Test egress and ingress asymmetry and p2p delay
    tod_asymmetry_p2p_delay_test
end

test "test_clean_up" do
    # Delete ACE rule
    $ts.dut.call("mesa_ace_del", $acl_id)

    # VLAN port configuration restore
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port0], $vlan_port_conf_restore0)
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port1], $vlan_port_conf_restore1)

    # Clear VLAN memberships
    $ts.dut.call("mesa_vlan_port_members_set", $vlan, "")

    # Asymmetry delay restore
    $ts.dut.call("mesa_ts_delay_asymmetry_set", $ts.dut.port_list[$port0], $asymmetry_conf_restore0)
    $ts.dut.call("mesa_ts_delay_asymmetry_set", $ts.dut.port_list[$port1], $asymmetry_conf_restore1)

    # p2p delay restore
    $ts.dut.call("mesa_ts_p2p_delay_set", $ts.dut.port_list[$port0], $p2p_conf_restore)
end

