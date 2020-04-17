#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

$dpl_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_DPL_CNT")

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

$cap_cnt_evc = ($ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT_EVC") != 0) ? true : false
console ("$cap_cnt_evc #{$cap_cnt_evc}")

MESA_VID_NULL = 0

eg = rand(3)    # Get a random egress port between 0 and 3
begin   # Get a random ingress port between 0 and 3 different from egress port
    ig = rand(3)
end while eg == ig
console("ig: #{ig}  eg: #{eg}")

console ("Only forward on relevant ports #{$ts.dut.port_list}")
port_list = "#{$ts.dut.port_list[0]},#{$ts.dut.port_list[1]},#{$ts.dut.port_list[2]},#{$ts.dut.port_list[3]}"
$ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

console ("learn mac address on egress port")
$ts.pc.run("sudo ef tx #{$ts.pc.p[eg]} eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ipv4 dscp 0")

console ("Configure ingress port to C tag aware")
vconf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[ig])
vconf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[ig], vconf)

console ("Configure egress port to C tag all")
vconf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[eg])
vconf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
vconf["untagged_vid"] = MESA_VID_NULL
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[eg], vconf)

console("Configure egress prio and dpl mapping to 1:1")
dconf = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[eg], $dpl_cnt)
dconf[0]["pcp"] = [0,1,2,3,4,5,6,7]
dconf[0]["dei"] = [0,0,0,0,0,0,0,0]
dconf[1]["pcp"] = [0,1,2,3,4,5,6,7]
dconf[1]["dei"] = [1,1,1,1,1,1,1,1]
$ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[eg], $dpl_cnt, dconf)

console("Configure egress prio and dpl tagging to mapped")
qconf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[eg])
qconf["tag"]["remark_mode"] = "MESA_TAG_REMARK_MODE_MAPPED"
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[eg], qconf)

qconf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])

test "Check cos 3 dpl 0 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    console("Configure ingress default prio and dpl")
    qconf["default_prio"] = 3
    qconf["default_dpl"] = 0
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], qconf)

    console("clear port counters")
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[ig])
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[eg])

    console("Send IPV4 frame and expect reception of tag with pcp and dei")
    txframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ipv4 dscp 0 data pattern cnt 40"
    rxframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ctag vid 1 pcp 3 dei 0 ipv4 dscp 0 data pattern cnt 40"
    $ts.pc.run("sudo ef tx #{$ts.pc.p[ig]} #{txframe} rx #{$ts.pc.p[eg]} #{rxframe}")

    console("Check QoS counters")
    icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[ig])
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])

    if ((icounters["prio"][3]["rx"] != 1) || (ecounters["prio"][3]["tx"] != 1))
        t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][3]["rx"]}   tx green #{ecounters["prio"][3]["tx"]}")
    end
    if ($cap_cnt_evc)
        console("Check colour counter")
        if ($cap_cnt_evc && (icounters["prio"][3]["rx_green"] != 1) || (ecounters["prio"][3]["tx_green"] != 1))
            t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][3]["rx_green"]}   tx green #{ecounters["prio"][3]["tx_green"]}")
        end
    end
end

test "Check cos 5 dpl 1 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    console("Configure ingress default prio and dpl")
    qconf["default_prio"] = 5
    qconf["default_dpl"] = 1
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], qconf)

    console("clear port counters")
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[ig])
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[eg])

    console("Send IPV4 frame and expect reception of tag with pcp and dei")
    txframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ipv4 dscp 0 data pattern cnt 40"
    rxframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ctag vid 1 pcp 5 dei 1 ipv4 dscp 0 data pattern cnt 40"
    $ts.pc.run("sudo ef tx #{$ts.pc.p[ig]} #{txframe} rx #{$ts.pc.p[eg]} #{rxframe}")

    console("Check QoS counters")
    icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[ig])
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])

    if ((icounters["prio"][5]["rx"] != 1) || (ecounters["prio"][5]["tx"] != 1))
        t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][3]["rx"]}   tx green #{ecounters["prio"][3]["tx"]}")
    end
    if ($cap_cnt_evc)
        console("Check colour counter")
        if ($cap_cnt_evc && (icounters["prio"][5]["rx_yellow"] != 1) || (ecounters["prio"][5]["tx_yellow"] != 1))
            t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][5]["rx_yellow"]}   tx yellow #{ecounters["prio"][5]["tx_yellow"]}")
        end
    end
end

test "Check no tag pcp to cos mapping from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    console("Disable ingress tag pcp mapping")
    qconf["tag"]["class_enable"] = false
    qconf["default_prio"] = 0
    qconf["default_dpl"] = 0
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], qconf)

    console("clear port counters")
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[ig])
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[eg])

    console("Send IPV4 frame with tag and expect reception of tag with pcp and dei")
    txframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ctag vid 1 pcp 3 dei 1 ipv4 dscp 0 data pattern cnt 40"
    rxframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ctag vid 1 pcp 0 dei 0 ipv4 dscp 0 data pattern cnt 40"
    $ts.pc.run("sudo ef tx #{$ts.pc.p[ig]} #{txframe} rx #{$ts.pc.p[eg]} #{rxframe}")

    console("Check QoS counters")
    icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[ig])
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])

    if ((icounters["prio"][0]["rx"] != 1) || (ecounters["prio"][0]["tx"] != 1))
        t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][0]["rx"]}   tx green #{ecounters["prio"][0]["tx"]}")
    end
    if ($cap_cnt_evc)
        console("Check colour counter")
        if ($cap_cnt_evc && (icounters["prio"][0]["rx_green"] != 1) || (ecounters["prio"][0]["tx_green"] != 1))
            t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][0]["rx_green"]}   tx green #{ecounters["prio"][0]["tx_green"]}")
        end
    end
end

test "Check tag pcp 5, dei 0 to cos mapping cos 5, dpl 0 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
    console("Enable ingress tag pcp mapping")
    qconf["tag"]["class_enable"] = true
    qconf["default_prio"] = 0
    qconf["default_dpl"] = 0
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], qconf)

    console("clear port counters")
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[ig])
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[eg])

    console("Send IPV4 frame with tag and expect reception of tag with pcp and dei")
    txframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ctag vid 1 pcp 5 dei 0 ipv4 dscp 0 data pattern cnt 40"
    rxframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ctag vid 1 pcp 5 dei 0 ipv4 dscp 0 data pattern cnt 40"
    $ts.pc.run("sudo ef tx #{$ts.pc.p[ig]} #{txframe} rx #{$ts.pc.p[eg]} #{rxframe}")

    console("Check QoS counters")
    icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[ig])
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])

    if ((icounters["prio"][5]["rx"] != 1) || (ecounters["prio"][5]["tx"] != 1))
        t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][5]["rx"]}   tx green #{ecounters["prio"][5]["tx"]}")
    end
    if ($cap_cnt_evc)
        console("Check colour counter")
        if ($cap_cnt_evc && (icounters["prio"][5]["rx_green"] != 1) || (ecounters["prio"][5]["tx_green"] != 1))
            t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][5]["rx_green"]}   tx green #{ecounters["prio"][5]["tx_green"]}")
        end
    end
end

test "Check tag pcp 0, dei 1 to cos mapping cos 1, dpl 1 from #{ig} to #{eg}" do
    console("Enable ingress tag pcp mapping")
    qconf["tag"]["class_enable"] = true
    qconf["default_prio"] = 0
    qconf["default_dpl"] = 0
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], qconf)

    console("clear port counters")
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[ig])
    $ts.dut.call("mesa_port_counters_clear", $ts.dut.p[eg])

    console("Send IPV4 frame with tag and expect reception of tag with pcp and dei")
    txframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ctag vid 1 pcp 0 dei 1 ipv4 dscp 0 data pattern cnt 40"
    rxframe = "eth dmac 00:01:00:00:00:02 smac 00:01:00:00:00:01 ctag vid 1 pcp 1 dei 1 ipv4 dscp 0 data pattern cnt 40"
    $ts.pc.run("sudo ef tx #{$ts.pc.p[ig]} #{txframe} rx #{$ts.pc.p[eg]} #{rxframe}")

    console("Check QoS counters")
    icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[ig])
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])

    if ((icounters["prio"][1]["rx"] != 1) || (ecounters["prio"][1]["tx"] != 1))
        t_e("ingress/egress counters not as expected. rx green #{icounters["prio"][1]["rx"]}   tx green #{ecounters["prio"][1]["tx"]}")
    end
    if ($cap_cnt_evc)
        console("Check colour counter")
        if ($cap_cnt_evc && (icounters["prio"][1]["rx_yellow"] != 1) || (ecounters["prio"][1]["tx_yellow"] != 1))
            t_e("ingress/egress counters not as expected. rx yellow #{icounters["prio"][1]["rx_yellow"]}   tx yellow #{ecounters["prio"][1]["tx_yellow"]}")
        end
    end
end

console("Clean up")
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
