#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

$dpl_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_DPL_CNT")
$chip_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")

MESA_CHIP_FAMILY_CARACAL = 2

$qconf0 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[0])
$qconf1 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[1])
$qconf2 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[2])
$qconf3 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[3])
$vconf0 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[0])
$vconf1 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[1])
$vconf2 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[2])
$vconf3 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[3])
$dconf0 = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[0], $dpl_cnt)
$dconf1 = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[1], $dpl_cnt)
$dconf2 = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[2], $dpl_cnt)
$dconf3 = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[3], $dpl_cnt)

MESA_VID_NULL = 0

eg = rand(3)    # Get a random egress port between 0 and 3
ig = [0,1,2,3] - [eg]  # Calculate ingress list as all other ports

t_i("-------------------------")
t_i("ig: #{ig}  eg: #{eg}")
t_i("-------------------------")

t_i ("Only forward on relevant ports #{$ts.dut.port_list}")
port_list = "#{$ts.dut.port_list[0]},#{$ts.dut.port_list[1]},#{$ts.dut.port_list[2]},#{$ts.dut.port_list[3]}"
$ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

t_i ("Configure ingress ports to C tag aware")
ig.each do |i|
    $ts.dut.run("mesa-cmd port flow control #{$ts.dut.p[i]+1} disable")

    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[i])
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[i], conf)

    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[i])
    conf["tag"]["class_enable"] = true
    conf["tag"]["pcp_dei_map"][0][0]["prio"] = 0
    conf["tag"]["pcp_dei_map"][0][0]["dpl"] = 0
    conf["tag"]["pcp_dei_map"][0][1]["prio"] = 0
    conf["tag"]["pcp_dei_map"][0][1]["dpl"] = 1
    conf["tag"]["pcp_dei_map"][1][0]["prio"] = 1
    conf["tag"]["pcp_dei_map"][1][0]["dpl"] = 0
    conf["tag"]["pcp_dei_map"][1][1]["prio"] = 1
    conf["tag"]["pcp_dei_map"][1][1]["dpl"] = 1
    conf["default_prio"] = i
    conf["default_dpl"] = 0
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[i], conf)
end

t_i ("Configure egress port to C tag all")
vconf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[eg])
vconf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
vconf["untagged_vid"] = MESA_VID_NULL
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[eg], vconf)

t_i("Configure egress prio and dpl mapping to 1:1")
dconf = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[eg], $dpl_cnt)
dconf[0]["pcp"] = [0,1,2,3,4,5,6,7]
dconf[0]["dei"] = [0,0,0,0,0,0,0,0]
dconf[1]["pcp"] = [0,1,2,3,4,5,6,7]
dconf[1]["dei"] = [1,1,1,1,1,1,1,1]
$ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[eg], $dpl_cnt, dconf)

t_i("Configure egress prio and dpl tagging to mapped. Also enable port shaper to assure queues are never emptied")
qconf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
qconf["tag"]["remark_mode"] = "MESA_TAG_REMARK_MODE_MAPPED"
qconf["shaper"]["level"] = 25000    # Shaper must have "large" burst size level in order to shape correctly at "high" rates
qconf["shaper"]["rate"] = 990000
qconf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], qconf)

test "Strict scheduling test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}" do
    # Only expect frames in the highest priority queue when running strict scheduling
       #measure(ig, eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_CARACAL"))
        measure(ig, eg, 1000, 1,     false,            false,           [0,0,990000000],  [20,200,2],  true,              [0,3,7]) # On Caracal some lower priority frames are slipping through
    else
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        measure(ig, eg, 1000, 1,     false,            false,           [0,0,990000000],  [150,500,2],  true,              [0,3,7]) # On SparX-5 some lower priority frames are slipping through
    else
        measure(ig, eg, 1000, 1,     false,            false,           [0,0,990000000],  [0,50,2],    true,              [0,3,7]) # On ServalT some lower priority frames are slipping through
    end
    end
end

test "Weighted scheduling with equal weights test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}" do
    # Expect equal distribution of frames in queue 0..2
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["dwrr_enable"] = true
    conf["dwrr_cnt"] = 3
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

    erate = 990000000/3
   #measure(ig, eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000,    tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure(ig, eg, 1000, 1,     false,            false,           [erate,erate,erate], [2,2,2],     true,              [0,1,2])
end

test "Weighted scheduling with 10, 30 and 60 percent test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}" do
    # Expect distribution of frames in queue 0..2 based on weights (10%, 30%, 60%)
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["dwrr_enable"] = true
    conf["dwrr_cnt"] = 3
    conf["queue"][0]["pct"] = 10
    conf["queue"][1]["pct"] = 30
    conf["queue"][2]["pct"] = 60
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

    erate0 = 990000000*1/10
    erate1 = 990000000*3/10
    erate2 = 990000000*6/10
   #measure(ig, eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000,       tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure(ig, eg, 1000, 1,     false,            false,           [erate0,erate1,erate2], [4,6,5],     true,              [0,1,2])
end

t_i("Clean up")
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[0], $qconf0)
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[1], $qconf1)
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[2], $qconf2)
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[3], $qconf3)
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[0], $vconf0)
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[1], $vconf1)
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[2], $vconf2)
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[3], $vconf3)
$ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[0], $dpl_cnt, $dconf0)
$ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[1], $dpl_cnt, $dconf1)
$ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[2], $dpl_cnt, $dconf2)
$ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[3], $dpl_cnt, $dconf3)

