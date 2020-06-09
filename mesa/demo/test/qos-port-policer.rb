#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

$pol_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_PORT_POLICER_CNT")

$pconf0 = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[0], $pol_cnt)
$pconf1 = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[1], $pol_cnt)
$pconf2 = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[2], $pol_cnt)
$pconf3 = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[3], $pol_cnt)

MESA_BITRATE_DISABLED = 0xffffffff

eg = rand(3)    # Get a random egress port between 0 and 3
begin   # Get a random ingress port between 0 and 3 different from egress port
    ig = rand(3)
end while eg == ig
console("ig: #{ig}  eg: #{eg}")

console ("Only forward on relevant ports #{$ts.dut.port_list}")
port_list = "#{$ts.dut.port_list[0]},#{$ts.dut.port_list[1]},#{$ts.dut.port_list[2]},#{$ts.dut.port_list[3]}"
$ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

# Check bit rate without using a policer
test "Port policer disabled from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[ig])
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[eg])

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         false)

    icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[ig])
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])

    if ((icounters["rmon"]["rx_etherStatsPkts"] - (icounters["if_group"]["ifInDiscards"] + icounters["if_group"]["ifInErrors"])) != ecounters["rmon"]["tx_etherStatsPkts"])   # Check that all frames are transmitted - no policing
        t_e("ingress/egress counters not as expected. rx #{icounters["rmon"]["rx_etherStatsPkts"]}   tx #{ecounters["rmon"]["tx_etherStatsPkts"]}")
    end
end

# Check bit rate using five different rates
test "Port policer bit rate 100 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = false
    pconf[0]["policer"]["level"] = 0
    pconf[0]["policer"]["rate"] = 100
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 5,     false,            false,           [100000],         [6],         true)
end

test "Port policer bit rate 1000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = false
    pconf[0]["policer"]["level"] = 0
    pconf[0]["policer"]["rate"] = 1000
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 3,     false,            false,           [1000000],        [3],         false)
end

test "Port policer bit rate 10000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = false
    pconf[0]["policer"]["level"] = 0
    pconf[0]["policer"]["rate"] = 10000
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [10000000],       [2],         false)
end

test "Port policer bit rate 100000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = false
    pconf[0]["policer"]["level"] = 1
    pconf[0]["policer"]["rate"] = 100000
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [100000000],      [2],         false)
end

test "Port policer bit rate 1000000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = false
    pconf[0]["policer"]["level"] = 1
    pconf[0]["policer"]["rate"] = 1000000
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         false)
end

# Check frame rate using four different rates
test "Port policer frame rate 100 fps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = true
    pconf[0]["policer"]["rate"] = 100
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 3,     true,            false,           [100],             [2],         true)
end

test "Port policer frame rate 1000 fps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = true
    pconf[0]["policer"]["rate"] = 1000
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 2,     true,            false,           [1000],            [1],         true)
end

test "Port policer frame rate 10000 fps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = true
    pconf[0]["policer"]["level"] = 206
    pconf[0]["policer"]["rate"] = 10000
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     true,            false,           [10000],           [1],         true)
end

test "Port policer frame rate 100000 fps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig], $pol_cnt)
    pconf[0]["frame_rate"] = true
    pconf[0]["policer"]["level"] = 206
    pconf[0]["policer"]["rate"] = 100000
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig], $pol_cnt, pconf)

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     true,            false,           [100000],          [2],         false)
end

$ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[0], $pol_cnt, $pconf0)
$ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[1], $pol_cnt, $pconf1)
$ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[2], $pol_cnt, $pconf2)
$ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[3], $pol_cnt, $pconf3)
