#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

$frame_support = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_EGRESS_SHAPER_FRAME")

MESA_VID_NULL = 0

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

port = $ts.dut.p[ig]
$ts.dut.run("mesa-cmd port flow control #{port + 1} disable")
sleep(5)
dut_port_state_up([port])

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
    # Check rate without using a shaper
    test "Queue #{cos} shaper disabled from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         false,             [default_cos2pcp(cos)])
    end

    if ($frame_support == 1)
        # Check frame based shaping using three different rates.
        test "Queue #{cos} shaper frame rate 100 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
            conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
            conf["queue"][cos]["shaper"]["level"] = 5
            conf["queue"][cos]["shaper"]["rate"] = 100
            conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_FRAME"
            conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

        #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
            measure([ig], eg, 600,  1,     true,             false,           [100],           [3],         true,              [default_cos2pcp(cos)])
        end

        test "Queue #{cos} shaper frame rate 1000 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
            conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
            conf["queue"][cos]["shaper"]["level"] = 10
            conf["queue"][cos]["shaper"]["rate"] = 1000
            conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_FRAME"
            conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

        #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
            measure([ig], eg, 600,  1,     true,             false,           [1000],           [3],         true,              [default_cos2pcp(cos)])
        end

        test "Queue #{cos} shaper frame rate 300000 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
            conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
            conf["queue"][cos]["shaper"]["level"] = 50
            conf["queue"][cos]["shaper"]["rate"] = 300000
            conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_FRAME"
            conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

        #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
            measure([ig], eg, 300,  1,     true,             false,           [300000],         [3],         true,              [default_cos2pcp(cos)])
        end
    end

    # Check line rate using three different rates. The rates are selected to be multiple of 400 as Serval chip on support this without calling a calibrate function 50 times a sec.
    test "Queue #{cos} shaper line rate 400 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["queue"][cos]["shaper"]["level"] = 1
        conf["queue"][cos]["shaper"]["rate"] = 400
        conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 4,     false,            false,           [400000],         [3],         true,              [default_cos2pcp(cos)])
    end

    test "Queue #{cos} shaper line rate 100000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["queue"][cos]["shaper"]["level"] = 1
        conf["queue"][cos]["shaper"]["rate"] = 100000
        conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [100000000],      [3],         false,             [default_cos2pcp(cos)])
    end

    test "Queue #{cos} shaper line rate 1000000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["queue"][cos]["shaper"]["level"] = 25000     # Shaper must have "large" burst size level in order to shape correctly at "high" rates
        conf["queue"][cos]["shaper"]["rate"] = 1000000
        conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [1000000000],      [2],        false,             [default_cos2pcp(cos)])
    end

    # Check data rate using three different rates. The rates are selected to be multiple of 400 as Serval chip on support this without calling a calibrate function 50 times a sec.
    test "Queue #{cos} shaper data rate 400 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["queue"][cos]["shaper"]["level"] = 1
        conf["queue"][cos]["shaper"]["rate"] = 400
        conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_DATA"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            true,            [400000],         [1],         true,              [default_cos2pcp(cos)])
    end

    test "Queue #{cos} shaper data rate 100000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["queue"][cos]["shaper"]["level"] = 1
        conf["queue"][cos]["shaper"]["rate"] = 100000
        conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_DATA"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            true,            [100000000],      [1],         false,             [default_cos2pcp(cos)])
    end

    test "Queue #{cos} shaper data rate 1000000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["queue"][cos]["shaper"]["level"] = 25000     # Shaper must have "large" burst size level in order to shape correctly at "high" rates
        conf["queue"][cos]["shaper"]["rate"] = 1000000
        conf["queue"][cos]["shaper"]["mode"] = "MESA_SHAPER_MODE_DATA"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            true,            [1000000000],     [1.1],       false,             [default_cos2pcp(cos)])
    end
end

# Restore configuration
[ig, eg].each do |idx|
    port = $ts.dut.p[idx]
    $ts.dut.call("mesa_vlan_port_conf_set", port, $vconf[port])
    $ts.dut.call("mesa_qos_port_conf_set", port, $qconf[port])
end
