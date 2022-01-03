#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'libeasy/utils'

$ts = get_test_setup("mesa_pc_b2b_2x")
$cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")

MESA_VID_NULL = 0
MESA_BITRATE_DISABLED = 0xffffffff

# Use random ingress/egress port
idx_list = port_idx_shuffle($ts)
ig = idx_list[0]
eg = idx_list[1]
t_i("ig: #{ig}  eg: #{eg}")

# Save configuration
$vconf = []
$qconf = []
[ig, eg].each do |idx|
    port = $ts.dut.p[idx]
    $vconf[port] = $ts.dut.call("mesa_vlan_port_conf_get", port)
    $qconf[port] = $ts.dut.call("mesa_qos_port_conf_get", port)
end

t_i ("Only forward on relevant ports #{$ts.dut.p}")
port_list = port_idx_list_str(idx_list)
$ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

t_i ("Configure ingress port to C tag aware")
conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[ig])
conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[ig], conf)

t_i("Enable ingress tag pcp mapping")
conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
conf["tag"]["class_enable"] = true
conf["default_prio"] = 0
conf["default_dpl"] = 0
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

t_i ("Configure egress port to C tag all")
vconf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[eg])
vconf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
vconf["untagged_vid"] = MESA_VID_NULL
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[eg], vconf)

[0,3,7].each do |cos|
    # Check rate without using a policer
    test "Queue #{cos} policer disabled from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         false,             [default_cos2pcp(cos)])
    end

    test "Queue #{cos} policer line rate 100 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
        conf["queue"][cos]["policer"]["level"] = 1024
        conf["queue"][cos]["policer"]["rate"] = 100
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

           #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        if $cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")
            measure([ig], eg, 1000, 10,    false,            false,           [100000],         [10],        true,              [default_cos2pcp(cos)])
        else
        if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SERVALT"))
            measure([ig], eg, 1000, 10,    false,            false,           [100000],         [15],        true,              [default_cos2pcp(cos)])
        else if
            measure([ig], eg, 1000, 10,    false,            false,           [100000],         [3],         true,              [default_cos2pcp(cos)])
        end
        end
        end
    end

    test "Queue #{cos} policer line rate 5000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
        conf["queue"][cos]["policer"]["level"] = 1024
        conf["queue"][cos]["policer"]["rate"] = 5000
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [5000000],       [1],         true,              [default_cos2pcp(cos)])
    end

    test "Queue #{cos} policer line rate 30000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
        conf["queue"][cos]["policer"]["level"] = 2048
        conf["queue"][cos]["policer"]["rate"] = 30000
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [30000000],       [1],         true,              [default_cos2pcp(cos)])
    end

    test "Queue #{cos} policer line rate 60000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
        conf["queue"][cos]["policer"]["level"] = 2048
        conf["queue"][cos]["policer"]["rate"] = 60000
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [60000000],       [1],         true,              [default_cos2pcp(cos)])
    end

    test "Queue #{cos} policer line rate 300000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
        conf["queue"][cos]["policer"]["level"] = 4096
        conf["queue"][cos]["policer"]["rate"] = 300000
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [300000000],       [1],         true,              [default_cos2pcp(cos)])
    end

    test "Queue #{cos} policer line rate 600000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
        conf["queue"][cos]["policer"]["level"] = 4096
        conf["queue"][cos]["policer"]["rate"] = 600000
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [600000000],       [1],         true,              [default_cos2pcp(cos)])
    end

    test "Queue #{cos} policer line rate 999000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
        conf["queue"][cos]["policer"]["level"] = 4096
        conf["queue"][cos]["policer"]["rate"] = 999000
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        if $cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")
            measure([ig], eg, 1000, 1,     false,            false,           [999000000],       [1.6],       true,              [default_cos2pcp(cos)])
        else
            measure([ig], eg, 1000, 1,     false,            false,           [999000000],       [1],         true,              [default_cos2pcp(cos)])
        end
    end

    # Check rate without using a policer
    test "Queue #{cos} policer disabled from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
        conf["queue"][cos]["policer"]["level"] = 0
        conf["queue"][cos]["policer"]["rate"] = MESA_BITRATE_DISABLED
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         false,             [default_cos2pcp(cos)])
    end
end

# Restore configuration
[ig, eg].each do |idx|
    port = $ts.dut.p[idx]
    $ts.dut.call("mesa_vlan_port_conf_set", port, $vconf[port])
    $ts.dut.call("mesa_qos_port_conf_set", port, $qconf[port])
end
