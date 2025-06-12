#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

check_capabilities do
    $dpl_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_DPL_CNT")
    $hqos = $ts.dut.call("mesa_capability", "MESA_CAP_HQOS")
    assert(($hqos == 1), "HQOS must be supported")
end

# VLANs used in this test
$port_list = $ts.dut.port_list
$vid_members = [0, 1, 2, 3]
$vid = 100
$unknown_vid = 200
$priority_vid = 300

# One port is ingress
# One port in normal mode that is part of the VLAN
# One port is in hierarchical mode but without any HQOS entry - hqos_id is unknown
# One port is in hierarchical mode with HQOS entry
$ingress_idx = 0
$normal_idx = 1
$priority_idx = 1
$hier_unknown_idx = 2
$hier_idx = 3

$ingress_port = $ts.dut.p[$ingress_idx]
$normal_port = $ts.dut.p[$normal_idx]
$priority_port = $ts.dut.p[$priority_idx]
$hier_unknown_port = $ts.dut.p[$hier_unknown_idx]
$hier_port = $ts.dut.p[$hier_idx]

$norma1_vport = {}
$norma1_se = {}

MESA_HQOS_ID_NONE = 0xffff
VCE_ID_LAST = 0

test "conf" do
    t_i("Set VLAN port configuration")
    t_i("Enable ingress tag pcp mapping")
    $port_list.each_with_index do |port, idx|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["pvid"] = $vid
        conf["untagged_vid"] = 0
        conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)

        $ts.dut.run("mesa-cmd port flow control #{port + 1} disable")

        conf = $ts.dut.call("mesa_qos_port_conf_get", port)
        conf["tag"]["class_enable"] = true
        conf["tag"]["remark_mode"] = "MESA_TAG_REMARK_MODE_MAPPED"
        conf["tag"]["pcp_dei_map"][0][0]["prio"] = 0
        conf["tag"]["pcp_dei_map"][0][0]["dpl"] = 0
        conf["tag"]["pcp_dei_map"][0][1]["prio"] = 0
        conf["tag"]["pcp_dei_map"][0][1]["dpl"] = 1
        conf["tag"]["pcp_dei_map"][1][0]["prio"] = 1
        conf["tag"]["pcp_dei_map"][1][0]["dpl"] = 0
        conf["tag"]["pcp_dei_map"][1][1]["prio"] = 1
        conf["tag"]["pcp_dei_map"][1][1]["dpl"] = 1
        conf["default_prio"] = 0
        conf["default_dpl"] = 0
        $ts.dut.call("mesa_qos_port_conf_set", port, conf)

        t_i("Configure egress prio and dpl mapping to 1:1")
        dconf = $ts.dut.call("mesa_qos_port_dpl_conf_get", port, $dpl_cnt)
        dconf[0]["pcp"] = [0,1,2,3,4,5,6,7]
        dconf[0]["dei"] = [0,0,0,0,0,0,0,0]
        dconf[1]["pcp"] = [0,1,2,3,4,5,6,7]
        dconf[1]["dei"] = [1,1,1,1,1,1,1,1]
        $ts.dut.call("mesa_qos_port_dpl_conf_set", port, $dpl_cnt, dconf)
    end

    sleep(5)
    dut_port_state_up($port_list)

    $ts.dut.call("mesa_vlan_port_members_set", 1, "")
    $ts.dut.call("mesa_vlan_port_members_set", $vid, port_idx_list_str($vid_members))
    $ts.dut.call("mesa_vlan_port_members_set", $unknown_vid, port_idx_list_str($vid_members))
    $ts.dut.call("mesa_vlan_port_members_set", $priority_vid, port_idx_list_str($vid_members))

    t_i("Save Normal Mode configuration")
    t_i("-------------------------")
    $norma1_vport = $ts.dut.run("mesa-cmd deb api cil hqos act 20#{$hier_port}")
    $norma1_se = $ts.dut.run("mesa-cmd deb api cil hqos act 40#{$hier_port}")
    sleep 1
end

def add_and_delete()
test "Add and Delete" do
    hqos_id = 0
    conf = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)

    t_i("Fill up L1 number 0")
    min_rate = 3906
    conf["min_rate"] = min_rate
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Fill up L1 number 1")
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Fill up L1 number 2")
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("L1 number 3")
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if (!res[:out].include? "unknown_vport 120")
        t_e "Unexpected Unknown VPORT"
    end
    if (!res[:out].include? "unknown_l0_se 960")
        t_e "Unexpected Unknown L0 SE"
    end
    if ((!res[:out].include? "IDX:   0  HQOS-ID:   0  PRIO: 0  MIN:    3906  VPORT: 121  SE:  961  L1-SE:  2  L1-INPUT:  0") ||
        (!res[:out].include? "IDX:   6  HQOS-ID:   6  PRIO: 0  MIN:    3906  VPORT: 127  SE:  967  L1-SE:  2  L1-INPUT:  6") ||
        (!res[:out].include? "IDX:   7  HQOS-ID:   7  PRIO: 0  MIN:    3906  VPORT:   0  SE:  968  L1-SE:  2  L1-INPUT:  7") ||
        (!res[:out].include? "IDX:  63  HQOS-ID:  63  PRIO: 0  MIN:    3906  VPORT:  56  SE: 4600  L1-SE:  2  L1-INPUT: 63") ||

        (!res[:out].include? "IDX:  64  HQOS-ID:  64  PRIO: 0  MIN:    3906  VPORT:  57  SE: 4601  L1-SE:  3  L1-INPUT:  0") ||
        (!res[:out].include? "IDX:  70  HQOS-ID:  70  PRIO: 0  MIN:    3906  VPORT:  63  SE: 4607  L1-SE:  3  L1-INPUT:  6") ||
        (!res[:out].include? "IDX:  71  HQOS-ID:  71  PRIO: 0  MIN:    3906  VPORT:  64  SE:    0  L1-SE:  3  L1-INPUT:  7") ||
        (!res[:out].include? "IDX: 127  HQOS-ID: 127  PRIO: 0  MIN:    3906  VPORT: 152  SE:   56  L1-SE:  3  L1-INPUT: 63") ||

        (!res[:out].include? "IDX: 128  HQOS-ID: 128  PRIO: 0  MIN:    3906  VPORT: 153  SE:   57  L1-SE:  4  L1-INPUT:  0") ||
        (!res[:out].include? "IDX: 191  HQOS-ID: 191  PRIO: 0  MIN:    3906  VPORT: 216  SE:  120  L1-SE:  4  L1-INPUT: 63") ||

        (!res[:out].include? "IDX: 192  HQOS-ID: 192  PRIO: 0  MIN:    3906  VPORT: 217  SE:  121  L1-SE:  5  L1-INPUT:  0") ||
        (!res[:out].include? "IDX: 255  HQOS-ID: 255  PRIO: 0  MIN:    3906  VPORT: 280  SE:  184  L1-SE:  5  L1-INPUT: 63"))
        t_e "Unexpected L0 SE"
    end
    if ((!res[:out].include? "IDX 0  SE 2  L2-INPUT 1") ||
        (!res[:out].include? "IDX 1  SE 3  L2-INPUT 2") ||
        (!res[:out].include? "IDX 2  SE 4  L2-INPUT 3") ||
        (!res[:out].include? "IDX 3  SE 5  L2-INPUT 4"))
        t_e "Unexpected L1 SE"
    end

    t_i("Print VPORT_TBL and SE_TBL configuration")
    t_i("----------------------------------------")
    $ts.dut.run("mesa-cmd deb api cil hqos act 20#{$hier_port}000") #Port hier_port QGRP 0
    $ts.dut.run("mesa-cmd deb api cil hqos act 20#{$hier_port}150")
    $ts.dut.run("mesa-cmd deb api cil hqos act 20#{$hier_port}195")

    t_i("Print DWRR configuration")
    t_i("------------------------")
    $ts.dut.run("mesa-cmd deb api cil hqos act 30#{$hier_port}1")   #Port hier_port Layer 1
    $ts.dut.run("mesa-cmd deb api cil hqos act 30#{$hier_port}2")   #Port hier_port Layer 2

    t_i("Delete to empty L1 SE 1")
    t_i("------------------------")
    hqos_id = 64
    64.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if ((res[:out].include? "IDX:  64  HQOS-ID:  64  PRIO: 0  MIN:    3906  VPORT:  57  SE: 4601  L1-SE:  3  L1-INPUT:  0") ||
        (res[:out].include? "IDX:  70  HQOS-ID:  70  PRIO: 0  MIN:    3906  VPORT:  63  SE: 4607  L1-SE:  3  L1-INPUT:  6") ||
        (res[:out].include? "IDX:  71  HQOS-ID:  71  PRIO: 0  MIN:    3906  VPORT:  64  SE:    0  L1-SE:  3  L1-INPUT:  7") ||
        (res[:out].include? "IDX: 127  HQOS-ID: 127  PRIO: 0  MIN:    3906  VPORT: 152  SE:   56  L1-SE:  3  L1-INPUT: 63"))
        t_e "Unexpected L0 SE after delete to empty L1 SE 1"
    end
    if ((!res[:out].include? "IDX 0  SE 2  L2-INPUT 1") ||
        (res[:out].include? "IDX 1  SE 3  L2-INPUT 2") ||
        (!res[:out].include? "IDX 2  SE 4  L2-INPUT 3") ||
        (!res[:out].include? "IDX 3  SE 5  L2-INPUT 4"))
        t_e "Unexpected L1 SE after delete to empty L1 SE 1"
    end

    t_i("Delete one HQOS-ID in L1 SE 0 + 2 + 3")
    t_i("------------------------")
    $ts.dut.call("mesa_hqos_del", $hier_port, 0   + 2)
    $ts.dut.call("mesa_hqos_del", $hier_port, 128 + 2)
    $ts.dut.call("mesa_hqos_del", $hier_port, 192 + 2)

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if ((res[:out].include? "IDX:   #{0 + 2}  HQOS-ID:   #{0 + 2}") ||
        (res[:out].include? "IDX: #{0 + 128}  HQOS-ID: #{128 + 2}") ||
        (res[:out].include? "IDX: #{0 + 192}  HQOS-ID: #{192 + 2}"))
        t_e "Unexpected L0 SE after delete in L1 SE 0 + 2 + 3"
    end

    t_i("Add all the deleted entries (64 + 3) but with a new HQOS-ID")
    hqos_id = 500
    67.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if ((!res[:out].include? "IDX:   2  HQOS-ID: 500  PRIO: 0  MIN:    3906  VPORT: 123  SE:  963  L1-SE:  2  L1-INPUT:  2") ||
        (!res[:out].include? "IDX:  64  HQOS-ID: 501  PRIO: 0  MIN:    3906  VPORT:  57  SE: 4601  L1-SE:  4  L1-INPUT:  2") ||
        (!res[:out].include? "IDX:  65  HQOS-ID: 502  PRIO: 0  MIN:    3906  VPORT:  58  SE: 4602  L1-SE:  5  L1-INPUT:  2") ||
        (!res[:out].include? "IDX:  66  HQOS-ID: 503  PRIO: 0  MIN:    3906  VPORT:  59  SE: 4603  L1-SE:  3  L1-INPUT:  0") ||
        (!res[:out].include? "IDX: 127  HQOS-ID: 564  PRIO: 0  MIN:    3906  VPORT: 152  SE:   56  L1-SE:  3  L1-INPUT: 61") ||
        (!res[:out].include? "IDX: 130  HQOS-ID: 565  PRIO: 0  MIN:    3906  VPORT: 155  SE:   59  L1-SE:  3  L1-INPUT: 62") ||
        (!res[:out].include? "IDX: 194  HQOS-ID: 566  PRIO: 0  MIN:    3906  VPORT: 219  SE:  123  L1-SE:  3  L1-INPUT: 63"))
        t_e "Unexpected L0 SE after add all the deleted entries"
    end
    if ((!res[:out].include? "IDX 0  SE 2  L2-INPUT 1") ||
        (!res[:out].include? "IDX 1  SE 3  L2-INPUT 2") ||
        (!res[:out].include? "IDX 2  SE 4  L2-INPUT 3") ||
        (!res[:out].include? "IDX 3  SE 5  L2-INPUT 4"))
        t_e "Unexpected L1 SE after add all the deleted entries"
    end
end
end

def priority_add_and_delete()
test "Priority Add and Delete" do
    hqos_id = 0
    conf = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)

    t_i("Fill up L1 number 2") #note that L1 number 1 is used as Priority L1 SE on port $hier_unknown_port
    min_rate = 3906
    conf["min_rate"] = min_rate
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Fill up Priority L1 number 0")
    conf["priority_service"] = true
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Print DWRR configuration")
    t_i("------------------------")
    $ts.dut.run("mesa-cmd deb api cil hqos act 30#{$hier_port}1")   #Port hier_port Layer 1
    $ts.dut.run("mesa-cmd deb api cil hqos act 30#{$hier_port}2")   #Port hier_port Layer 2

    t_i("Fill up L1 number 3") #note that L1 number 1 is used as Priority L1 SE on port $hier_unknown_port
    conf["priority_service"] = false
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if ((!res[:out].include? "IDX:   0  HQOS-ID:   0  PRIO: 0  MIN:    3906  VPORT: 121  SE:  961  L1-SE:  2  L1-INPUT:  0") ||
        (!res[:out].include? "IDX:   6  HQOS-ID:   6  PRIO: 0  MIN:    3906  VPORT: 127  SE:  967  L1-SE:  2  L1-INPUT:  6") ||
        (!res[:out].include? "IDX:   7  HQOS-ID:   7  PRIO: 0  MIN:    3906  VPORT:   0  SE:  968  L1-SE:  2  L1-INPUT:  7") ||
        (!res[:out].include? "IDX:  63  HQOS-ID:  63  PRIO: 0  MIN:    3906  VPORT:  56  SE: 4600  L1-SE:  2  L1-INPUT: 63") ||

        (!res[:out].include? "IDX:  64  HQOS-ID:  64  PRIO: 1  MIN:    3906  VPORT:  57  SE: 4601  L1-SE:  0  L1-INPUT:  0") ||
        (!res[:out].include? "IDX:  70  HQOS-ID:  70  PRIO: 1  MIN:    3906  VPORT:  63  SE: 4607  L1-SE:  0  L1-INPUT:  6") ||
        (!res[:out].include? "IDX:  71  HQOS-ID:  71  PRIO: 1  MIN:    3906  VPORT:  64  SE:    0  L1-SE:  0  L1-INPUT:  7") ||
        (!res[:out].include? "IDX: 127  HQOS-ID: 127  PRIO: 1  MIN:    3906  VPORT: 152  SE:   56  L1-SE:  0  L1-INPUT: 63") ||

        (!res[:out].include? "IDX: 128  HQOS-ID: 128  PRIO: 0  MIN:    3906  VPORT: 153  SE:   57  L1-SE:  3  L1-INPUT:  0") ||
        (!res[:out].include? "IDX: 191  HQOS-ID: 191  PRIO: 0  MIN:    3906  VPORT: 216  SE:  120  L1-SE:  3  L1-INPUT: 63"))
        t_e "Unexpected L0 SE"
    end
    if ((!res[:out].include? "IDX 0  SE 2  L2-INPUT 1") ||
        (!res[:out].include? "IDX 1  SE 3  L2-INPUT 2"))
        t_e "Unexpected L1 SE"
    end

    t_i("Delete to empty Priority L1 number 0")
    t_i("------------------------")
    hqos_id = 64
    64.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if ((res[:out].include? "IDX:  64  HQOS-ID:  64  PRIO: 1  MIN:    3906  VPORT:  57  SE: 4601  L1-SE:  0  L1-INPUT:  0") ||
        (res[:out].include? "IDX:  70  HQOS-ID:  70  PRIO: 1  MIN:    3906  VPORT:  63  SE: 4607  L1-SE:  0  L1-INPUT:  6") ||
        (res[:out].include? "IDX:  71  HQOS-ID:  71  PRIO: 1  MIN:    3906  VPORT:  64  SE:    0  L1-SE:  0  L1-INPUT:  7") ||
        (res[:out].include? "IDX: 127  HQOS-ID: 127  PRIO: 1  MIN:    3906  VPORT: 152  SE:   56  L1-SE:  0  L1-INPUT: 63"))
        t_e "Unexpected L0 SE after delete to empty L1 SE 1"
    end
    if ((!res[:out].include? "IDX 0  SE 2  L2-INPUT 1") ||
        (!res[:out].include? "IDX 1  SE 3  L2-INPUT 2"))
        t_e "Unexpected L1 SE after delete to empty Priority L1 SE"
    end

    t_i("Delete to empty L1 number 2") #note that L1 number 1 is used as Priority L1 SE on port $hier_unknown_port
    t_i("------------------------")
    hqos_id = 0
    64.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if ((res[:out].include? "IDX:   0  HQOS-ID:   0  PRIO: 0  MIN:    3906  VPORT: 121  SE:  961  L1-SE:  2  L1-INPUT:  0") ||
        (res[:out].include? "IDX:   6  HQOS-ID:   6  PRIO: 0  MIN:    3906  VPORT: 127  SE:  967  L1-SE:  2  L1-INPUT:  6") ||
        (res[:out].include? "IDX:   7  HQOS-ID:   7  PRIO: 0  MIN:    3906  VPORT:   0  SE:  968  L1-SE:  2  L1-INPUT:  7") ||
        (res[:out].include? "IDX:  63  HQOS-ID:  63  PRIO: 0  MIN:    3906  VPORT:  56  SE: 4600  L1-SE:  2  L1-INPUT: 63"))
        t_e "Unexpected L0 SE after delete to empty L1 SE 2"
    end
    if ((res[:out].include? "IDX 0  SE 2  L2-INPUT 1") ||
        (!res[:out].include? "IDX 1  SE 3  L2-INPUT 2"))
        t_e "Unexpected L1 SE after delete to empty L1 SE 2"
    end

    t_i("Delete to empty L1 number 3") #note that L1 number 1 is used as Priority L1 SE on port $hier_unknown_port
    t_i("------------------------")
    hqos_id = 128
    64.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if ((res[:out].include? "IDX: 128  HQOS-ID: 128  PRIO: 0  MIN:    3906  VPORT: 153  SE:   57  L1-SE:  3  L1-INPUT:  0") ||
        (res[:out].include? "IDX: 191  HQOS-ID: 191  PRIO: 0  MIN:    3906  VPORT: 216  SE:  120  L1-SE:  3  L1-INPUT: 63"))
        t_e "Unexpected L0 SE after delete to empty L1 SE 3"
    end
    if (res[:out].include? "IDX 1  SE 3  L2-INPUT 2")
        t_e "Unexpected L1 SE after delete to empty L1 SE 3"
    end

    t_i("Fill up L1 number 2 again")
    hqos_id = 0
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Print Internal structures")
    t_i("-------------------------")
    res = $ts.dut.run("mesa-cmd deb api cil hqos act 10#{$hier_port}")
    sleep 1

    if ((!res[:out].include? "IDX:   0  HQOS-ID:   0  PRIO: 0  MIN:    3906  VPORT: 121  SE:  961  L1-SE:  2  L1-INPUT:  0"))
        t_e "Unexpected L0 SE after adding SE 2 again 1"
    end
    if ((!res[:out].include? "IDX:   6  HQOS-ID:   6  PRIO: 0  MIN:    3906  VPORT: 127  SE:  967  L1-SE:  2  L1-INPUT:  6"))
        t_e "Unexpected L0 SE after adding SE 2 again 2"
    end
    if ((!res[:out].include? "IDX:   7  HQOS-ID:   7  PRIO: 0  MIN:    3906  VPORT:   0  SE:  968  L1-SE:  2  L1-INPUT:  7"))
        t_e "Unexpected L0 SE after adding SE 2 again 3"
    end
    if ((!res[:out].include? "IDX:  63  HQOS-ID:  63  PRIO: 0  MIN:    3906  VPORT:  56  SE: 4600  L1-SE:  2  L1-INPUT: 63"))
        t_e "Unexpected L0 SE after adding SE 2 again 4"
    end
    if (!res[:out].include? "IDX 0  SE 2  L2-INPUT 1")
        t_e "Unexpected L1 SE after adding SE 2 again"
    end

    t_i("Delete to clean up")
    t_i("------------------------")
    hqos_id = 0
    64.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end
end
end

def delete_all()
    t_i("Delete all entries")
    t_i("------------------------")
    hqos_id = 0
    64.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end
    hqos_id = 128
    128.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end

    hqos_id = 500
    67.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end
end

def set_to_normal()
test "Back to Normal Mode" do
    delete_all()

    conf = $ts.dut.call("mesa_hqos_port_conf_get", $hier_port)
    conf["sch_mode"] = "MESA_HQOS_SCH_MODE_NORMAL"
    $ts.dut.call("mesa_hqos_port_conf_set", $hier_port, conf)

    t_i("Get new Normal Mode configuration")
    t_i("-------------------------")
    new_norma1_vport = $ts.dut.run("mesa-cmd deb api cil hqos act 20#{$hier_port}")
    new_norma1_se = $ts.dut.run("mesa-cmd deb api cil hqos act 40#{$hier_port}")
    sleep 1

    if (new_norma1_vport[:out] != $norma1_vport[:out])
        t_e("Unexpected new_norma1_vport")
    end
    if (new_norma1_se[:out] != $norma1_se[:out])
        t_e("Unexpected new_norma1_se")
    end
end
end

def egress_shaper
test "Egress Shaper Test" do
    hqos_id = 0
    conf = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)
    vlan = $ts.dut.call("mesa_vlan_vid_conf_get", $vid);

    t_i("Add Normal entry with output shaper - 1 Mbit")
    conf["min_rate"] = 700000
    conf["shaper"]["rate"] = 700000
    conf["shaper"]["level"] = 10000
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)

    t_i("Add Priority entry with output shaper - 10 Mbit")
    prio_hqos_id = 10
    conf["priority_service"] = true
    conf["min_rate"] = 10000
    conf["shaper"]["rate"] = 10000
    conf["shaper"]["level"] = 10
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    $ts.dut.call("mesa_hqos_add", $hier_port, prio_hqos_id, conf)

    t_i("Inject frames into the VID generating Normal QGRP")
    vlan["hqos_id"] = hqos_id
    $ts.dut.call("mesa_vlan_vid_conf_set", $vid, vlan);
    erate = 700000000
   #measure(ig,             eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_idx, 1000, 1,     false,            false,           [erate],          [3],         false,             [3])

    t_i("Inject frames into the VID generating Priority QGRP")
    vlan["hqos_id"] = prio_hqos_id
    $ts.dut.call("mesa_vlan_vid_conf_set", $vid, vlan);
    erate = 10000000
   #measure(ig,             eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_idx, 1000, 1,     false,            false,           [erate],          [3],         false,             [4])

    t_i("Inject frames into the Unknown VID generating QGRP 0 hitting the Unknown L0 SE at egress")
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ingress_port)
    conf["pvid"] = $unknown_vid
    $ts.dut.call("mesa_vlan_port_conf_set", $ingress_port, conf)
   #measure(ig,             eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_idx, 1000, 1,     false,            false,           [0],              [5],         false,             [1])

    $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
    $ts.dut.call("mesa_hqos_del", $hier_port, prio_hqos_id)
end
end

def priority_vs_normal()
test "Priority vs Normal Test" do
    hqos_id = 0
    conf = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)
    normal_vlan = $ts.dut.call("mesa_vlan_vid_conf_get", $vid);
    priority_vlan = $ts.dut.call("mesa_vlan_vid_conf_get", $priority_vid);

    t_i("Add Normal entry")
    conf["min_rate"] = 1000000
    $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)

    t_i("Add Priority entry")
    prio_hqos_id = 10
    conf["min_rate"] = 1000000
    conf["priority_service"] = true
    $ts.dut.call("mesa_hqos_add", $hier_port, prio_hqos_id, conf)

    t_i("Make Normal VID generate Normal HQOS-ID")
    normal_vlan["hqos_id"] = hqos_id
    $ts.dut.call("mesa_vlan_vid_conf_set", $vid, normal_vlan);

    t_i("Make Priority VID generate Priority HQOS-ID")
    priority_vlan["hqos_id"] = prio_hqos_id
    $ts.dut.call("mesa_vlan_vid_conf_set", $priority_vid, priority_vlan);

    t_i("Make $ingress_port classify to Normal VID")
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ingress_port)
    conf["pvid"] = $vid
    $ts.dut.call("mesa_vlan_port_conf_set", $ingress_port, conf)

    t_i("Make $priority_port classify to Priority VID")
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $priority_port)
    conf["pvid"] = $priority_vid
    $ts.dut.call("mesa_vlan_port_conf_set", $priority_port, conf)

    t_i("Inject frames into Normal and Priority VID")
    cos = 3
    erate = 1000000
   #measure(ig,                            eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx, $priority_idx], $hier_idx, 1000, 1,     false,            false,           [0, 1000000000],  [220,3],     false,             [2,5])

    $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
    $ts.dut.call("mesa_hqos_del", $hier_port, prio_hqos_id)
end
end

def normal_dwrr()
test "DWRR on Normal Test" do
    hqos_id = 0
    hqos = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)
    normal_vlan = $ts.dut.call("mesa_vlan_vid_conf_get", $vid);

    t_i("Add Normal entry")
    hqos["min_rate"] = 1000000
    $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, hqos)

    t_i("Make Normal VID generate Normal HQOS-ID")
    normal_vlan["hqos_id"] = hqos_id
    $ts.dut.call("mesa_vlan_vid_conf_set", $vid, normal_vlan);

    t_i("Make ingress ports classify to Normal VID")
    $port_list.each_with_index do |port, idx|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["pvid"] = $vid
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end

    t_i("Inject frames into all ingress ports")
    erate = 1000000000
   #measure(ig,      eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([0,1,2], $hier_idx, 1000, 1,     false,            false,           [0,0,erate],          [150,600,3],         false,             [2,4,7])

    t_i("Configure the DWRR to give equal percentage to all priorities")
    hqos["dwrr_cnt"] = 3
    hqos["input_pct"][0] = 10
    hqos["input_pct"][1] = 30
    hqos["input_pct"][2] = 70
    $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, hqos)

    t_i("Inject frames into all ingress ports")
    erate0 = 100000000
    erate1 = 300000000
    erate2 = 700000000
   #measure(ig,      eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000,        tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([0,1,2], $hier_idx, 1000, 1,     false,            false,           [erate0,erate1,erate2],  [4,7,13],     true,              [0,1,2])

    $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
end
end

def multiple_l2_input_test()
test "Multiple L2 input" do
    hqos_id = 0
    conf = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)

    t_i("Fill up L1 number 0")
    min_rate = 1000000
    conf["min_rate"] = min_rate
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Fill up L1 number 1")
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    t_i("Fill up L1 number 2")
    64.times do
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end


    t_i("Configure ports to generate HQOS-ID 0 - 64 - 128 - 192")
    $port_list.each_with_index do |port, idx|
        vid = 100 * (idx + 1)
        hqos_id = 64 * idx

        vlan = $ts.dut.call("mesa_vlan_port_conf_get", port)
        vlan["pvid"] = vid
        $ts.dut.call("mesa_vlan_port_conf_set", port, vlan)

        vlan = $ts.dut.call("mesa_vlan_vid_conf_get", vid);
        vlan["hqos_id"] = hqos_id
        $ts.dut.call("mesa_vlan_vid_conf_set", vid, vlan);
    end

    t_i("Inject frames into all ingress ports")
    erate = 333333333
   #measure(ig,      eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000,    tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([0,1,2], $hier_idx, 1000, 1,     false,            false,           [erate,erate,erate], [3,3,3],     false,             [2,4,7])

    t_i("Add output shaper to traffic carrying L0 with different rate")
    conf["min_rate"] = 1000
    conf["shaper"]["rate"] = 1000
    conf["shaper"]["level"] = 10
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    $ts.dut.call("mesa_hqos_add", $hier_port, 0, conf)
    conf["min_rate"] = 10000
    conf["shaper"]["rate"] = 10000
    conf["shaper"]["level"] = 10
    $ts.dut.call("mesa_hqos_add", $hier_port, 64, conf)
    conf["min_rate"] = 100000
    conf["shaper"]["rate"] = 100000
    conf["shaper"]["level"] = 100
    $ts.dut.call("mesa_hqos_add", $hier_port, 128, conf)

    t_i("Inject frames into all ingress ports")
    erate2 = 1000000
    erate4 = 10000000
    erate7 = 100000000
   #measure(ig,      eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000,       tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([0,1,2], $hier_idx, 1000, 1,     false,            false,           [erate2,erate4,erate7], [3,3,3],     false,             [2,4,7])

    hqos_id = 0
    192.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end
end
end

def iflow_classification()
test "HQOS classification using IFLOW (ISDX)" do
    t_i("Add Normal entry shaping to 1 Mbit")
    hqos_id = 10
    hqos = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)
    hqos["min_rate"] = 1000
    hqos["shaper"]["rate"] = 1000
    hqos["shaper"]["level"] = 10
    hqos["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, hqos)

    t_i("Make ingress ports classify to Normal VID")
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ingress_port)
    conf["pvid"] = $vid
    $ts.dut.call("mesa_vlan_port_conf_set", $ingress_port, conf)

    t_i("Disable HQOS-ID on Normal VID")
    vlan = $ts.dut.call("mesa_vlan_vid_conf_get", $vid);
    vlan["hqos_id"] = MESA_HQOS_ID_NONE
    $ts.dut.call("mesa_vlan_vid_conf_set", $vid, vlan);

    t_i("Allocate IFLOW and make it generate HQOS-ID")
    iflow_id = $ts.dut.call("mesa_iflow_alloc")
    iflow = $ts.dut.call("mesa_iflow_conf_get", iflow_id)
    iflow["hqos_id"] = hqos_id
    $ts.dut.call("mesa_iflow_conf_set", iflow_id, iflow)

    t_i("Create VCE matching on VID and have IFLOW as action")
    vce_id = 10
    vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
    vce["id"] = vce_id
    key = vce["key"]
    key["port_list"] = "#{$ingress_port}"
    tag = key["tag"]
    tag["tagged"] = "MESA_VCAP_BIT_1"
    tag["s_tag"] = "MESA_VCAP_BIT_ANY"
    tag["vid"]["value"] = 0
    tag["vid"]["mask"] = 0xFFFF
    tag["dei"] = "MESA_VCAP_BIT_ANY"
    tag["pcp"]["mask"] = 0
    action = vce["action"]
    action["flow_id"] = iflow_id
    $ts.dut.call("mesa_vce_add", VCE_ID_LAST, vce)

    t_i("Inject frames into ingress ports")
    erate = 1000000
   #measure(ig,             eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_idx, 1000, 1,     false,            false,           [erate],          [3],         false,             [6])

    $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
    $ts.dut.call("mesa_vce_del", vce_id)
end
end

def multiple_ports_same_id()
test "Create HQOS entry on two ports with same ID" do
    hqos_id = 10

    t_i("Make ingress ports classify to Normal VID")
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ingress_port)
    conf["pvid"] = $vid
    $ts.dut.call("mesa_vlan_port_conf_set", $ingress_port, conf)

    t_i("HQOS-ID on Normal VID")
    vlan = $ts.dut.call("mesa_vlan_vid_conf_get", $vid);
    vlan["hqos_id"] = hqos_id
    $ts.dut.call("mesa_vlan_vid_conf_set", $vid, vlan);

    conf = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)

    t_i("Add entry with output shaper - 1 Mbit")
    conf["min_rate"] = 1000
    conf["shaper"]["rate"] = 1000
    conf["shaper"]["level"] = 10
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)

    t_i("Add entry with output shaper - 10 Mbit")
    conf["min_rate"] = 10000
    conf["shaper"]["rate"] = 10000
    conf["shaper"]["level"] = 10
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    $ts.dut.call("mesa_hqos_add", $hier_unknown_port, hqos_id, conf)

    t_i("Inject frames and measure on 1Mbit port")
    erate = 1000000
   #measure(ig,             eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_idx, 1000, 1,     false,            false,           [erate],          [3],         false,             [3])

    t_i("Inject frames and measure on 10Mbit port")
    erate = 10000000
   #measure(ig,             eg,                size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_unknown_idx, 1000, 1,     false,            false,           [erate],          [3],         false,             [7])

    $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
    $ts.dut.call("mesa_hqos_del", $hier_unknown_port, hqos_id)
end
end

def hier_unknown_normal()
test "Measure on HIER - HIER Unknown - Normal port" do
    hqos_id = 10

    t_i("Make ingress ports classify to Normal VID")
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ingress_port)
    conf["pvid"] = $vid
    $ts.dut.call("mesa_vlan_port_conf_set", $ingress_port, conf)

    t_i("HQOS-ID on Normal VID")
    vlan = $ts.dut.call("mesa_vlan_vid_conf_get", $vid);
    vlan["hqos_id"] = hqos_id
    $ts.dut.call("mesa_vlan_vid_conf_set", $vid, vlan);

    conf = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)

    t_i("On HIER port add entry with output shaper - 1 Mbit")
    conf["min_rate"] = 1000
    conf["shaper"]["rate"] = 1000
    conf["shaper"]["level"] = 10
    conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
    $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)

    t_i("Inject frames and measure on 1Mbit port")
    erate = 1000000
   #measure(ig,             eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_idx, 1000, 1,     false,            false,           [erate],          [3],         false,             [2])

    t_i("Inject frames and measure on Unknown port")
    erate = 0
   #measure(ig,             eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_unknown_idx, 1000, 1,     false,            false,           [erate],          [10],         false,             [5])

    t_i("Inject frames and measure on Normal port")
    erate = 1000000000
   #measure(ig,             eg,          size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $normal_idx, 1000, 1,     false,            false,           [erate],          [3],         false,             [7])

    $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
end
end

def actual_min_rate()
test "Actual minimum rate" do
    conf = $ts.dut.call("mesa_hqos_get", $hier_port, 0)

    conf["min_rate"] =  10000
    $ts.dut.call("mesa_hqos_add", $hier_port, 0, conf)
    conf["min_rate"] = 290000
    $ts.dut.call("mesa_hqos_add", $hier_port, 1, conf)
    conf["min_rate"] = 700000
    $ts.dut.call("mesa_hqos_add", $hier_port, 2, conf)

    t_i("Configure ports to generate HQOS-ID 0 - 64 - 128 - 192")
    $port_list.each_with_index do |port, idx|
        vid = 100 * (idx + 1)

        vlan = $ts.dut.call("mesa_vlan_port_conf_get", port)
        vlan["pvid"] = vid
        $ts.dut.call("mesa_vlan_port_conf_set", port, vlan)

        vlan = $ts.dut.call("mesa_vlan_vid_conf_get", vid);
        vlan["hqos_id"] = idx
        $ts.dut.call("mesa_vlan_vid_conf_set", vid, vlan);
    end

    t_i("Get the actual minimum rate")
    status = $ts.dut.call("mesa_hqos_status_get", $hier_port, 0)
    $act0 = status["min_rate"] * 1000
    status = $ts.dut.call("mesa_hqos_status_get", $hier_port, 1)
    $act1 = status["min_rate"] * 1000
    status = $ts.dut.call("mesa_hqos_status_get", $hier_port, 2)
    $act2 = status["min_rate"] * 1000

    t_i("Inject frames into all ingress ports")
   #measure(ig,      eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000,    tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([0,1,2], $hier_idx, 1000, 1,     false,            false,           [$act0,$act1,$act2], [4,4,4],     true,              [2,4,7])

    hqos_id = 0
    3.times do
        $ts.dut.call("mesa_hqos_del", $hier_port, hqos_id)
        hqos_id += 1
    end
end
end

test "The Test" do
    # Check rate without using a shaper
    erate = 1000000000
   #measure(ig,             eg,        size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure([$ingress_idx], $hier_idx, 1000, 1,     false,            false,           [erate],          [2],         false,             [3])

    t_i("Set to Hierarchical mode")
    conf = $ts.dut.call("mesa_hqos_port_conf_get", $hier_port)
    conf["sch_mode"] = "MESA_HQOS_SCH_MODE_HIERARCHICAL"
    $ts.dut.call("mesa_hqos_port_conf_set", $hier_port, conf)
    $ts.dut.call("mesa_hqos_port_conf_set", $hier_unknown_port, conf)

    add_and_delete()

    t_i("Set to Normal mode. This also check the new normal configuration against the initial one")
    set_to_normal()

    t_i("Set to Hierarchical mode and run the Add-Delete test again")
    $ts.dut.call("mesa_hqos_port_conf_set", $hier_port, conf)
    add_and_delete()

    delete_all()

    priority_add_and_delete()

    priority_vs_normal()
    egress_shaper()
    normal_dwrr()
    multiple_l2_input_test()
    iflow_classification()
    multiple_ports_same_id()
    hier_unknown_normal()
    actual_min_rate()
end
