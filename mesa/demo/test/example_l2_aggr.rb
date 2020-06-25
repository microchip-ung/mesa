#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
end

MESA_VID_NULL = 0

ig = rand(3)    # Get a random ingress port between 0 and 3
eg = []
begin   # Get a random egress port between 0 and 3 different from egress port
    eg[0] = rand(3)
end while ig == eg[0]
begin   # Get a random egress port between 0 and 3 different from egress port
    eg[1] = rand(3)
end while (ig == eg[1]) || (eg[0] == eg[1])
t_i("---------ig: #{ig}  eg: #{eg}---------")

test "test_conf" do
    t_i("Configure the test by calling the example code command")
    $ts.dut.run("mesa-cmd example init aggr port1 #{$ts.dut.p[eg[0]]+1} port2 #{$ts.dut.p[eg[1]]+1}")
end

smac = ["00:00:00:00:00:06","00:00:00:00:00:07"]
counters = []

test "test_run" do
    t_i("Clear port statistics")
    $ts.dut.run("mesa-cmd port statis clear")

    t_i("Transmit two frames with different SMAC")
    cmd = "sudo ef tx #{$ts.pc.p[ig]} eth smac #{smac[0]}"
    $ts.pc.run(cmd)
    cmd = "sudo ef tx #{$ts.pc.p[ig]} eth smac #{smac[1]}"
    $ts.pc.run(cmd)

    counters[0] = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg[0]])
    counters[1] = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg[1]])

    t_i("Check that port counters are as expected. One frame on each aggregated port")
    if ((counters[0]["rmon"]["tx_etherStatsPkts"] != 1) || (counters[1]["rmon"]["tx_etherStatsPkts"] != 1))
        t_e("Port counters are not as expected. port1 tx #{counters[0]["rmon"]["tx_etherStatsPkts"]}  port2 tx #{counters[1]["rmon"]["tx_etherStatsPkts"]}")
    end
end

test "test_clean_up" do
    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")

    t_i("Transmit two frames with different SMAC")
    cmd = "sudo ef tx #{$ts.pc.p[ig]} eth smac #{smac[0]}"
    $ts.pc.run(cmd)
    cmd = "sudo ef tx #{$ts.pc.p[ig]} eth smac #{smac[1]}"
    $ts.pc.run(cmd)

    counters[0] = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg[0]])
    counters[1] = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg[1]])

    t_i("Check that port counters are as expected. Three frame on each not aggregated port due to flooding")
    if ((counters[0]["rmon"]["tx_etherStatsPkts"] != 3) || (counters[1]["rmon"]["tx_etherStatsPkts"] != 3))
        t_e("Port counters are not as expected. port1 tx #{counters[0]["rmon"]["tx_etherStatsPkts"]}  port2 tx #{counters[1]["rmon"]["tx_etherStatsPkts"]}")
    end
end
