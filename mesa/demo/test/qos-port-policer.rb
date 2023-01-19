#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

$pol_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_PORT_POLICER_CNT")

MESA_BITRATE_DISABLED = 0xffffffff

# Use random ingress/egress port
idx_list = port_idx_shuffle($ts)
ig = idx_list[0]
eg = idx_list[1]
t_i("ig: #{ig}  eg: #{eg}")

# Save configuration
$pconf = []
[ig, eg].each do |idx|
    port = $ts.dut.p[idx]
    $pconf[port] = $ts.dut.call("mesa_qos_port_policer_conf_get", port, $pol_cnt)
end

t_i ("Only forward on relevant ports #{$ts.dut.p}")
port_list = port_idx_list_str(idx_list)
$ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

# Check bit rate without using a policer
test "Port policer disabled from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[ig])
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[eg])

   #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         false)

    icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[ig])
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])

    rxcnt = icounters["rmon"]["rx_etherStatsPkts"] - (icounters["if_group"]["ifInDiscards"] + icounters["if_group"]["ifInErrors"])
    txcnt = ecounters["rmon"]["tx_etherStatsPkts"] - (icounters["if_group"]["ifOutDiscards"] + icounters["if_group"]["ifOutErrors"])
    if ((rxcnt > (txcnt + 5)) ||  # Check that all frames are transmitted - no policing
        (rxcnt < txcnt))          # It is seen that more frame are received than transmitted. Seems that server sometimes transmit protocol PDUs
        t_e("ingress/egress counters not as expected. rx #{rxcnt}   tx #{txcnt}")
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

# Restore configuration
[ig, eg].each do |idx|
    port = $ts.dut.p[idx]
    $ts.dut.call("mesa_qos_port_policer_conf_set", port, $pol_cnt, $pconf[port])
end
