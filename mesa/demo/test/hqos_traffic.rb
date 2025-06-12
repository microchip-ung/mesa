#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

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
    $ts.dut.run("mesa-cmd port flow control #{$ingress_port + 1} disable")
    sleep(5)
    dut_port_state_up([$ingress_port])

    t_i("Set VLAN port configuration")
    t_i("Enable ingress tag pcp mapping")
    $port_list.each_with_index do |port, idx|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["pvid"] = 1000
        conf["untagged_vid"] = 0
        conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)

        conf = $ts.dut.call("mesa_qos_port_conf_get", port)
        conf["tag"]["class_enable"] = true
        conf["default_prio"] = 0
        conf["default_dpl"] = 0
        $ts.dut.call("mesa_qos_port_conf_set", port, conf)
    end

    $vid = 1
    hqos_id = 0
    vlan = $ts.dut.call("mesa_vlan_vid_conf_get", $vid);
    256.times do
        $ts.dut.call("mesa_vlan_port_members_set", $vid, port_idx_list_str($vid_members))
        vlan["fid"] = $vid
        vlan["hqos_id"] = hqos_id
        $ts.dut.call("mesa_vlan_vid_conf_set", $vid, vlan);
        $vid += 1
        hqos_id += 1
    end

    t_i("Set to Hierarchical mode")
    conf = $ts.dut.call("mesa_hqos_port_conf_get", $hier_port)
    conf["sch_mode"] = "MESA_HQOS_SCH_MODE_HIERARCHICAL"
    $ts.dut.call("mesa_hqos_port_conf_set", $hier_port, conf)

    # the following is creating HQOS entries in 6 groups with 26 and 4 groups with 25
    # in total 256 entries. The rate in each group is calculated to add up to 1G
    hqos_id = 0
    conf = $ts.dut.call("mesa_hqos_get", $hier_port, hqos_id)
    total = 0;
    256.times do
        if (hqos_id < 26)
            conf["min_rate"] = 50
            total += 50
        else if (hqos_id < (26 * 2))
            conf["min_rate"] = 100
            total += 100
        else if (hqos_id < (26 * 3))
            conf["min_rate"] = 200
            total += 200
        else if (hqos_id < (26 * 4))
            conf["min_rate"] = 500
            total += 500
        else if (hqos_id < (26 * 5))
            conf["min_rate"] = 800
            total += 800
        else if (hqos_id < (26 * 6))
            conf["min_rate"] = 1230
            total += 1400
        else if (hqos_id < ((26 * 6) + (25 * 1)))
            conf["min_rate"] = 5000
            total += 5000
        else if (hqos_id < ((26 * 6) + (25 * 2)))
            conf["min_rate"] = 7000
            total += 7000
        else if (hqos_id < ((26 * 6) + (25 * 3)))
            conf["min_rate"] = 10000
            total += 10000
        else if (hqos_id < ((26 * 6) + (25 * 4)))
            conf["min_rate"] = 15000
            total += 15000
        end
        end
        end
        end
        end
        end
        end
        end
        end
        end
        $ts.dut.call("mesa_hqos_add", $hier_port, hqos_id, conf)
        hqos_id += 1
    end

    status = []
    hqos_id = 0
    256.times do
        status[hqos_id] = $ts.dut.call("mesa_hqos_status_get", $hier_port, hqos_id)
        hqos_id += 1
    end

    hqos_id = 0
    256.times do
        t_i("HQOS-ID #{hqos_id}  ACT-RATE #{status[hqos_id]["min_rate"]}")
        hqos_id += 1
    end

    sleep (2)
    t_i("----- Rate Total #{total}")
end