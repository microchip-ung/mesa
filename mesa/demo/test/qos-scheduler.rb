#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

$dpl_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_DPL_CNT")
$chip_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")

MESA_CHIP_FAMILY_CARACAL = 2

# Use random ingress/egress port
idx_list = port_idx_shuffle($ts)
eg = idx_list[0]
ig = (idx_list - [eg])
ig_list = port_idx_list_str(ig)

# Save configuration
$vconf = []
$qconf = []
$dconf = []
idx_list.each do |idx|
    port = $ts.dut.p[idx]
    $vconf[port] = $ts.dut.call("mesa_vlan_port_conf_get", port)
    $qconf[port] = $ts.dut.call("mesa_qos_port_conf_get", port)
    $dconf[port] = $ts.dut.call("mesa_qos_port_dpl_conf_get", port, $dpl_cnt)
end

MESA_VID_NULL = 0

t_i("-------------------------")
t_i("ig: #{ig}  eg: #{eg}")
t_i("-------------------------")

t_i ("Only forward on relevant ports #{$ts.dut.p}")
port_list = port_idx_list_str(idx_list)
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
sleep(5)
dut_port_state_up(ig)

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

test "Strict scheduling test from #{ig_list} to #{$ts.dut.p[eg]}" do
    # Only expect frames in the highest priority queue when running strict scheduling
       #measure(ig, eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1,  with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_CARACAL"))
        measure(ig, eg, 1000, 1,     false,            false,           [0,0,990000000],  [220,305,2],   true,              [0,3,7]) # On Caracal some lower priority frames are slipping through
    else
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        measure(ig, eg, 1000, 1,     false,            false,           [0,0,990000000],  [295,535,2],  true,              [0,3,7]) # On SparX-5 some lower priority frames are slipping through
    else
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X"))
        measure(ig, eg, 1000, 1,     false,            false,           [0,0,990000000],  [260,500,0.3], true,             [0,3,7]) # On LAN966X some lower priority frames are slipping through
    else
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_OCELOT"))
        measure(ig, eg, 1000, 1,     false,            false,           [0,0,990000000],  [340,380,2],  true,              [0,3,7]) # On Ocelot some lower priority frames are slipping through
    else
        measure(ig, eg, 1000, 1,     false,            false,           [0,0,990000000],  [0,380,2],    true,              [0,3,7]) # On ServalT some lower priority frames are slipping through
    end
    end
    end
    end
end

if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_OCELOT"))
# For some reason on Ocelot if this frame is not transmitted the following two tests will - by far - not pass
    $ts.pc.run("sudo ef tx #{$ts.pc.p[eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ipv4 dscp 0")
end

test "Weighted scheduling with equal weights test from #{ig_list} to #{$ts.dut.p[eg]}" do
    # Expect equal distribution of frames in queue 0..2
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["dwrr_enable"] = true
    conf["dwrr_cnt"] = 3
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

    erate = 990000000/3
       #measure(ig, eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000,    tolerance=1,   with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X"))
        measure(ig, eg, 1000, 1,     false,            false,           [erate,erate,erate], [0.8,0.8,0.8], true,              [0,1,2])
    else
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_CARACAL"))
        measure(ig, eg, 1000, 1,     false,            false,           [erate,erate,erate], [2,2,2.4],     true,              [0,1,2])
    else
        measure(ig, eg, 1000, 1,     false,            false,           [erate,erate,erate], [2,2,2.1],     true,              [0,1,2])
    end
    end
end

test "Weighted scheduling with 10, 30 and 60 percent test from #{ig_list} to #{$ts.dut.p[eg]}" do
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

       #measure(ig, eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000,       tolerance=1,   with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X"))
        measure(ig, eg, 1000, 1,     false,            false,           [erate0,erate1,erate2], [3.5,6.4,3.6], true,              [0,1,2])
    else
    if ($chip_family == chip_family_to_id("MESA_CHIP_FAMILY_CARACAL"))
        measure(ig, eg, 1000, 1,     false,            false,           [erate0,erate1,erate2], [4,6.8,5.3],   true,              [0,1,2])
    else
        measure(ig, eg, 1000, 1,     false,            false,           [erate0,erate1,erate2], [4,6.5,5.1],   true,              [0,1,2])
    end
    end
end

# Restore configuration
t_i("Clean up")
idx_list.each do |idx|
    port = $ts.dut.p[idx]
    $ts.dut.call("mesa_vlan_port_conf_set", port, $vconf[port])
    $ts.dut.call("mesa_qos_port_conf_set", port, $qconf[port])
    $ts.dut.call("mesa_qos_port_dpl_conf_set", port, $dpl_cnt, $dconf[port])
end
