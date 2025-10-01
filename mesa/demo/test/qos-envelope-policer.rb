#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'libeasy/utils'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_xdlb = ($ts.dut.call("mesa_capability", "MESA_CAP_L2_XDLB") != 0)
    $cap_xflow = ($ts.dut.call("mesa_capability", "MESA_CAP_L2_XFLOW") != 0)
    $cap_cosid_class = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_COSID_CLASSIFICATION")
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert($cap_cosid_class == 1, "COSID classification not supported")
    assert(($cap_xdlb == true) && ($cap_xflow == true), "Dual leaky Bucket it not supported")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")), "Must be a Fireant or Laguna")
end

# Use random ingress/egress port
idx_list = port_idx_shuffle($ts)
igCos0 = idx_list[0]
igCos1 = idx_list[1]
igCos2 = idx_list[3]
eg = idx_list[2]
t_i("igCos0: #{igCos0}  igCos1: #{igCos1}  eg: #{eg}")

class_cnt = 3

t_i ("Only forward on relevant ports #{$ts.dut.p}")
port_list = port_idx_list_str(idx_list)
$ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

t_i("Configure default COSID on ingress ports")
conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[igCos0])
conf["cosid"] = 0
conf["default_prio"] = 0
conf["default_dpl"] = 0
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[igCos0], conf)
conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[igCos1])
conf["cosid"] = 1
conf["default_prio"] = 1
conf["default_dpl"] = 0
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[igCos1], conf)
conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[igCos2])
conf["cosid"] = 2
conf["default_prio"] = 2
conf["default_dpl"] = 0
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[igCos2], conf)

t_i("Allocate resources")
iflow = $ts.dut.call("mesa_iflow_alloc")
pol = $ts.dut.call("mesa_dlb_policer_alloc", class_cnt)
eflow = $ts.dut.call("mesa_eflow_alloc")
estat = $ts.dut.call("mesa_egress_cnt_alloc", class_cnt)
istat = $ts.dut.call("mesa_ingress_cnt_alloc",class_cnt)

t_i("Configure IFLOW to point to policer")
conf = $ts.dut.call("mesa_iflow_conf_get", iflow)
conf["dlb_enable"] = true
conf["dlb_id"] = pol
conf["cnt_enable"] = true
conf["cnt_id"] = istat
$ts.dut.call("mesa_iflow_conf_set", iflow, conf)

t_i("Configure EFLOW to point to counter set")
conf = $ts.dut.call("mesa_eflow_conf_get", eflow)
conf["cnt_enable"] = true
conf["cnt_id"] = estat
$ts.dut.call("mesa_eflow_conf_set", eflow, conf)

t_i("Ingress configuration VCE pointing untagged frames to policer")
vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
vce["id"] = 1
key = vce["key"]
key["port_list"] = "#{$ts.dut.port_list[igCos0]},#{$ts.dut.port_list[igCos1]},#{$ts.dut.port_list[igCos2]}"
tag = key["tag"]
tag["tagged"] = "MESA_VCAP_BIT_ANY"
tag["s_tag"] = "MESA_VCAP_BIT_ANY"
tag["vid"]["value"] = 0
tag["vid"]["mask"] = 0
tag["dei"] = "MESA_VCAP_BIT_ANY"
tag["pcp"]["mask"] = 0
action = vce["action"]
action["flow_id"] = iflow
$ts.dut.call("mesa_vce_add", 0, vce)

t_i ("Egress configuration TCE pointing to counter set")
tce = $ts.dut.call("mesa_tce_init")
tce["id"] = 1;
tce["key"]["port_list"] = "#{$ts.dut.port_list[eg]}"
tce["action"]["flow_id"] = eflow
tce["action"]["tag"]["tpid"] = "MESA_TPID_SEL_NONE"
$ts.dut.call("mesa_tce_add", 0, tce)

#$cos2_cir = 70000
#$cos2_eir = 10000
#$cos1_cir = 50000
#$cos1_eir = 10000
#$cos0_cir = 30000
#$cos0_eir = 10000

$cos2_cir = 30000
$cos2_eir = 10000
$cos1_cir = 50000
$cos1_eir = 10000
$cos0_cir = 70000
$cos0_eir = 10000

# All in same group
#$cos2_cir = 60000
#$cos2_eir = 10000
#$cos1_cir = 20000
#$cos1_eir = 10000
#$cos0_cir = 10000
#$cos0_eir = 10000

test "Three DLB policers on cosid 0,1,2 WITHOUT any sharing" do
    # Configure policers
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 0)
    conf["enable"] = true
    conf["line_rate"] = true
    conf["type"] = "MESA_POLICER_TYPE_MEF"
    conf["cir"] = $cos0_cir
    conf["cbs"] = 2048
    conf["eir"] = $cos0_eir
    conf["ebs"] = 2048
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 0, conf)

    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 1)
    conf["enable"] = true
    conf["line_rate"] = true
    conf["type"] = "MESA_POLICER_TYPE_MEF"
    conf["cir"] = $cos1_cir
    conf["cbs"] = 2048
    conf["eir"] = $cos1_eir
    conf["ebs"] = 2048
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 1, conf)

    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 2)
    conf["enable"] = true
    conf["line_rate"] = true
    conf["type"] = "MESA_POLICER_TYPE_MEF"
    conf["cir"] = $cos2_cir
    conf["cbs"] = 2048
    conf["eir"] = $cos2_eir
    conf["ebs"] = 2048
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 2, conf)

    erate0 = ($cos0_cir + $cos0_eir)*1000
    measure([igCos0], eg, 1000, 1,     false,            false,           [erate0],       [1],         true,              [])
    erate1 = ($cos1_cir + $cos1_eir)*1000
    measure([igCos1], eg, 1000, 1,     false,            false,           [erate1],       [1],         true,              [])
    erate2 = ($cos2_cir + $cos2_eir)*1000
    measure([igCos2], eg, 1000, 1,     false,            false,           [erate2],       [1],         true,              [])
end

test "Three DLB policers on cosid 0,1,2 - CIR sharing - 50% inherit. COS 0 CIR does NOT share to COS 2 EIR" do
    # Configure policers
    inherit0 = (($cos1_cir + $cos2_cir) / 100) * 50
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 0)
    conf["share_cir"] = false
    conf["inherit_cir"] = inherit0
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 0, conf)

    inherit1 = ($cos2_cir / 100) * 50
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 1)
    conf["share_cir"] = true
    conf["inherit_cir"] = inherit1
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 1, conf)

    inherit2 = 0
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 2)
    conf["share_cir"] = true
    conf["inherit_cir"] = inherit2
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 2, conf)

    t_i("Traffic in COS 0")
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0], eg, 1000, 1,     false,            false,           [erate0],          [1],         true,              [])

    t_i("Traffic in COS 1")
    erate1 = ($cos1_cir + $cos1_eir + inherit1)*1000
    measure([igCos1], eg, 1000, 1,     false,            false,           [erate1],          [1],         true,              [])

    t_i("Traffic in COS 2")
    erate2 = ($cos2_cir + $cos2_eir + inherit2)*1000
    measure([igCos2], eg, 1000, 1,     false,            false,           [erate2],          [1],         true,              [])

    t_i("Traffic in COS 0 and 2")
    inherit0 = ($cos1_cir > inherit0) ? inherit0 : $cos1_cir
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0,igCos2], eg, 1000, 1, false,          false,           [erate0,erate2],   [1,1],         true,              [0,2])

    t_i("Traffic in COS 0 and 1")
    inherit0 = $cos2_cir - inherit1
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0,igCos1], eg, 1000, 1, false,          false,           [erate0,erate1],   [1,1],         true,              [0,1])

    t_i("Traffic in COS 0, 1 and 2")
    inherit1 = 0
    inherit0 = 0
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    erate1 = ($cos1_cir + $cos1_eir + inherit1)*1000
    measure([igCos0,igCos1,igCos2], eg, 1000, 1, false,          false,           [erate0,erate1,erate2],   [1,1,1],         true,              [0,1,2])
end

test "Three DLB policers on cosid 0,1,2 - CIR sharing - 50% inherit. COS 0 CIR does share to COS 2 EIR" do
    # Configure COS 0 to share CIR to COS 2 EIR
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 0)
    conf["share_cir"] = true
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 0, conf)

    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 2)
    enherit_eir_2 = (($cos0_cir + $cos1_cir + $cos2_cir) * 50) / 100
    conf["inherit_eir"] = enherit_eir_2
    conf["cm"] = true
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 2, conf)

    # Configure COS 2 traffic to be all yellow
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[igCos2])
    conf["default_dpl"] = 1
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[igCos2], conf)

    t_i("Traffic in COS 2")
    erate2 = ($cos2_eir + enherit_eir_2)*1000
    measure([igCos2], eg, 1000, 1,     false,            false,           [erate2],          [1],         true,              [])

#    cnt = $ts.dut.call("mesa_egress_cnt_get", estat, 0)
#    cnt = $ts.dut.call("mesa_egress_cnt_get", estat, 1)
#    cnt = $ts.dut.call("mesa_egress_cnt_get", estat, 2)
#    cnt = $ts.dut.call("mesa_ingress_cnt_get", istat, 0)
#    cnt = $ts.dut.call("mesa_ingress_cnt_get", istat, 1)
#    cnt = $ts.dut.call("mesa_ingress_cnt_get", istat, 2)

    # Configure COS 2 traffic to be all green
    conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[igCos2])
    conf["default_dpl"] = 0
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[igCos2], conf)

    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 0)
    conf["share_cir"] = false
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 0, conf)
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 2)
    conf["inherit_eir"] = 0
    conf["cm"] = false
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 2, conf)
end

test "Three DLB policers on cosid 0,1,2 - CIR sharing - 50% inherit. Testing when the Coupling Flag is enable" do
    # Enable CF in COS 2
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 2)
    conf["cf"] = true
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 2, conf)

    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 0)

    t_i("Traffic in COS 0")
    inherit0 = ($cos1_cir > conf["inherit_cir"]) ? conf["inherit_cir"] : $cos1_cir
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0], eg, 1000, 1,     false,            false,           [erate0],          [1],         true,              [])

    # Enable CF in COS 1
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 1)
    conf["cf"] = true
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 1, conf)

    t_i("Traffic in COS 0")
    erate0 = ($cos0_cir + $cos0_eir)*1000
    measure([igCos0], eg, 1000, 1,     false,            false,           [erate0],          [1],         true,              [])
end

test "Three DLB policers on cosid 0,1,2 - EIR sharing - 50% inherit." do
    # Configure policers
    inherit0 = (($cos1_eir + $cos2_eir) / 100) * 50
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 0)
    conf["cf"] = false
    conf["share_cir"] = false
    conf["share_eir"] = false
    conf["inherit_eir"] = inherit0
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 0, conf)

    inherit1 = ($cos2_eir / 100) * 50
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 1)
    conf["cf"] = false
    conf["share_cir"] = false
    conf["share_eir"] = true
    conf["inherit_eir"] = inherit1
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 1, conf)

    inherit2 = 0
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 2)
    conf["cf"] = false
    conf["share_cir"] = false
    conf["share_eir"] = true
    conf["inherit_eir"] = inherit2
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 2, conf)

    t_i("Traffic in COS 0")
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0], eg, 1000, 1,     false,            false,           [erate0],          [1],         true,              [])

    t_i("Traffic in COS 1")
    erate1 = ($cos1_cir + $cos1_eir + inherit1)*1000
    measure([igCos1], eg, 1000, 1,     false,            false,           [erate1],          [1],         true,              [])

    t_i("Traffic in COS 2")
    erate2 = ($cos2_cir + $cos2_eir + inherit2)*1000
    measure([igCos2], eg, 1000, 1,     false,            false,           [erate2],          [1],         true,              [])

    t_i("Traffic in COS 0 and 2")
    inherit0 = ($cos1_eir > inherit0) ? inherit0 : $cos1_eir
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0,igCos2], eg, 1000, 1, false,          false,           [erate0,erate2],   [1,1],         true,              [0,2])

    t_i("Traffic in COS 0 and 1")
    inherit0 = $cos2_eir - inherit1
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0,igCos1], eg, 1000, 1, false,          false,           [erate0,erate1],   [1,1],         true,              [0,1])

    t_i("Traffic in COS 0, 1 and 2")
    inherit1 = 0
    inherit0 = 0
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    erate1 = ($cos1_cir + $cos1_eir + inherit1)*1000
    measure([igCos0,igCos1,igCos2], eg, 1000, 1, false,          false,           [erate0,erate1,erate2],   [1,1,1],         true,              [0,1,2])
end

test "Three DLB policers on cosid 0,1,2 - CIR sharing - MAX inherit. COS 0 CIR does NOT share to COS 2 EIR" do
    # Configure policers
    inherit0 = $cos1_cir + $cos2_cir
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 0)
    conf["share_cir"] = false
    conf["share_eir"] = false
    conf["inherit_cir"] = inherit0
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 0, conf)

    inherit1 = $cos2_cir
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 1)
    conf["share_cir"] = true
    conf["share_eir"] = false
    conf["inherit_cir"] = inherit1
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 1, conf)

    inherit2 = 0
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 2)
    conf["share_cir"] = true
    conf["share_eir"] = false
    conf["inherit_cir"] = inherit2
    conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, 2, conf)

    t_i("Traffic in COS 0")
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0], eg, 1000, 1,     false,            false,           [erate0],          [10],         true,              [])

    t_i("Traffic in COS 1")
    erate1 = ($cos1_cir + $cos1_eir + inherit1)*1000
    measure([igCos1], eg, 1000, 1,     false,            false,           [erate1],          [1],         true,              [])

    t_i("Traffic in COS 2")
    erate2 = ($cos2_cir + $cos2_eir + inherit2)*1000
    measure([igCos2], eg, 1000, 1,     false,            false,           [erate2],          [1],         true,              [])

    t_i("Traffic in COS 0 and 2")
    inherit0 = $cos1_cir
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0,igCos2], eg, 1000, 1, false,          false,           [erate0,erate2],   [1,1],         true,              [0,2])

    t_i("Traffic in COS 0 and 1")
    inherit0 = 0
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    measure([igCos0,igCos1], eg, 1000, 1, false,          false,           [erate0,erate1],   [1,1],         true,              [0,1])

    t_i("Traffic in COS 0, 1 and 2")
    inherit1 = 0
    erate0 = ($cos0_cir + $cos0_eir + inherit0)*1000
    erate1 = ($cos1_cir + $cos1_eir + inherit1)*1000
    measure([igCos0,igCos1,igCos2], eg, 1000, 1, false,          false,           [erate0,erate1,erate2],   [1,1,1],         true,              [0,1,2])
end
#$ts.dut.run("mesa-cmd deb api cil qos full act 17")
#$ts.dut.run("mesa-cmd deb api cil qos full act 16")

