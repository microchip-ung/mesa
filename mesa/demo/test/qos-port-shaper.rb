#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

$frame_support = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_EGRESS_SHAPER_FRAME")

# Use random ingress/egress port
idx_list = port_idx_shuffle($ts)
ig = idx_list[0]
eg = idx_list[1]
t_i("ig: #{ig}  eg: #{eg}")

# Save configuration
$qconf = []
[ig, eg].each do |idx|
    port = $ts.dut.p[idx]
    $qconf[port] = $ts.dut.call("mesa_qos_port_conf_get", port)
end

t_i ("Only forward on relevant ports #{$ts.dut.p}")
port_list = port_idx_list_str(idx_list)
$ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

port = $ts.dut.p[ig]
$ts.dut.run("mesa-cmd port flow control #{port + 1} disable")
sleep(5)
dut_port_state_up([port])

# Check line rate without using a shaper
test "Port shaper disabled from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         false)
end

if ($frame_support == 1)
    # Check frame based shaping using three different rates.
    test "Port shaper frame rate 100 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["shaper"]["level"] = 5
        conf["shaper"]["rate"] = 100
        conf["shaper"]["mode"] = "MESA_SHAPER_MODE_FRAME"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 600,  1,     true,             false,           [100],           [3],         true)
    end

    test "Port shaper frame rate 1000 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["shaper"]["level"] = 10
        conf["shaper"]["rate"] = 1000
        conf["shaper"]["mode"] = "MESA_SHAPER_MODE_FRAME"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 600,  1,     true,             false,           [1000],           [3],         true)
    end
    test "Port shaper frame rate 300000 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
        conf["shaper"]["level"] = 50
        conf["shaper"]["rate"] = 300000
        conf["shaper"]["mode"] = "MESA_SHAPER_MODE_FRAME"
        conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 300,  1,     true,             false,           [300000],         [3],         true)
    end
end

# Check line rate using five different rates. The rates are selected to be multiple of 400 as Serval chip on support this without calling a calibrate function 50 times a sec.
test "Port shaper line rate 400 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 400
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 2,     false,            false,           [400000],         [4],         true)
end

test "Port shaper line rate 1200 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 1200
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [1200000],        [3],         true)
end

test "Port shaper line rate 10000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 10000
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [10000000],       [3],         true)
end

test "Port shaper line rate 100000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 100000
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [100000000],      [3],         true)
end

test "Port shaper line rate 1000000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 25000     # Shaper must have "large" burst size level in order to shape correctly at "high" rates
    conf["shaper"]["rate"] = 1000000
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         true)
end

# Check data rate using four different rates. The rates are selected to be multiple of 400 as Serval chip on support this without calling a calibrate function 50 times a sec.
test "Port shaper data rate 400 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 400
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_DATA"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            true,            [400000],         [1],         true)
end

test "Port shaper data rate 1200 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 1200
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_DATA"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            true,            [1200000],        [1],         true)
end

test "Port shaper data rate 10000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 10000
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_DATA"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            true,            [10000000],       [2.2],       true)
end

test "Port shaper data rate 100000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 1
    conf["shaper"]["rate"] = 100000
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_DATA"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            true,            [100000000],      [1],         true)
end

test "Port shaper data rate 1000000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
    conf["shaper"]["level"] = 25000     # Shaper must have "large" burst size level in order to shape correctly at "high" rates
    conf["shaper"]["rate"] = 1000000
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_DATA"
    conf = $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], conf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            true,            [1000000000],     [3],         true)
end

# Restore configuration
[ig, eg].each do |idx|
    port = $ts.dut.p[idx]
    $ts.dut.call("mesa_qos_port_conf_set", port, $qconf[port])
end
