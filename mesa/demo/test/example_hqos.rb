#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $hqos = $ts.dut.call("mesa_capability", "MESA_CAP_HQOS")
    assert(($hqos == 1), "HQOS must be supported")
end


$port_list = $ts.dut.port_list
$ig = [0,1,2]
$eg = 3

test "test_conf" do
    $ts.dut.run("mesa-cmd port flow control #{$port_list[0] + 1} disable")
    $ts.dut.run("mesa-cmd port flow control #{$port_list[1] + 1} disable")
    $ts.dut.run("mesa-cmd port flow control #{$port_list[2] + 1} disable")
    sleep(5)
    dut_port_state_up($port_list)

    t_i("Configure the test to HQOS by calling the example code command")
    $ts.dut.run("mesa-cmd example init hqos port_eg #{$port_list[3]+1} port_ig1 #{$port_list[0]+1} port_ig2 #{$port_list[1]+1} port_ig3 #{$port_list[2]+1}")

    conf = $ts.dut.call("mesa_vlan_port_conf_get", $port_list[0])
    conf["pvid"] = 200
    $ts.dut.call("mesa_vlan_port_conf_set", $port_list[0], conf)
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $port_list[1])
    conf["pvid"] = 300
    $ts.dut.call("mesa_vlan_port_conf_set", $port_list[1], conf)
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $port_list[2])
    conf["pvid"] = 400
    $ts.dut.call("mesa_vlan_port_conf_set", $port_list[2], conf)
    sleep 2

    res = $ts.dut.run("mesa-cmd example run hqos hqos-id #{1} command 3");
    $act0 = res[:out].split(" ")[2].to_i * 1000
    res = $ts.dut.run("mesa-cmd example run hqos hqos-id #{2} command 3");
    $act1 = res[:out].split(" ")[2].to_i * 1000
    res = $ts.dut.run("mesa-cmd example run hqos hqos-id #{3} command 3");
    $act2 = res[:out].split(" ")[2].to_i * 1000
    t_i("act_rate #{res}  act0 #{$act0}  act1 #{$act1}  act2 #{$act2}")
end

t_i("Learn the destination MAC on the egress port")
$ts.pc.run("sudo ef tx #{$ts.pc.p[$eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ctag vid 200 ipv4 dscp 0")
$ts.pc.run("sudo ef tx #{$ts.pc.p[$eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ctag vid 300 ipv4 dscp 0")
$ts.pc.run("sudo ef tx #{$ts.pc.p[$eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ctag vid 400 ipv4 dscp 0")

test "test_normal_run" do
    measure($ig, $eg, 800, 1,     false,            false,           [$act0,$act1,$act2],  [3.5,3.5,3.5],  true,              [0,3,7])
end

test "test_priority_run" do
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $port_list[0])
    conf["pvid"] = 100
    $ts.dut.call("mesa_vlan_port_conf_set", $port_list[0], conf)

    measure($ig, $eg, 800, 1,     false,            false,           [1000000000,0,0],  [1,200,200],  true,              [0,3,7])
end

test "test_shaper_run" do
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $port_list[0])
    conf["pvid"] = 200
    $ts.dut.call("mesa_vlan_port_conf_set", $port_list[0], conf)

    t_i("Configure the HQOS shaper by calling the example code command")
    $ts.dut.run("mesa-cmd example run hqos hqos-id #{1} command 1");
    $ts.dut.run("mesa-cmd example run hqos hqos-id #{2} command 1");
    $ts.dut.run("mesa-cmd example run hqos hqos-id #{3} command 1");
    sleep 2

    measure($ig, $eg, 1000, 1,     false,            false,           [10000000,190000000,700000000],  [1,1,1],  true,              [0,3,7])
end

test "test_dwrr_run" do
    t_i("All input ports map to same VID 200 that hits HQOS-ID 1")
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $port_list[0])
    conf["pvid"] = 200
    $ts.dut.call("mesa_vlan_port_conf_set", $port_list[0], conf)
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $port_list[1])
    conf["pvid"] = 200
    $ts.dut.call("mesa_vlan_port_conf_set", $port_list[1], conf)
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $port_list[2])
    conf["pvid"] = 200
    $ts.dut.call("mesa_vlan_port_conf_set", $port_list[2], conf)

    t_i("Configure the HQOS Priority DWRR by calling the example code command")
    $ts.dut.run("mesa-cmd example run hqos hqos-id #{1} command 2");
    sleep 2

    erate0 = 100000000
    erate1 = 300000000
    erate2 = 700000000
    measure($ig, $eg, 1000, 1,     false,            false,           [erate0,erate1,erate2],  [4,7,13],  true,              [0,1,2])
end

test "test_clean_up" do
    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")
end
