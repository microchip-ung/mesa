#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$port_idx_rx     = 0 # Ingress mirroring
$port_idx_tx     = 1 # Egress mirroring
$port_idx_normal = 2 # Normal forwarding and VLAN/ACL mirroring
$port_idx_mirror = 3 # Mirror port

test "conf" do
    t_i("Normal port is a C-port");
    port_normal = $ts.dut.port_list[$port_idx_normal]
    conf = $ts.dut.call("mesa_vlan_port_conf_get", port_normal)
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
    $ts.dut.call("mesa_vlan_port_conf_set", port_normal, conf)

    t_i("Mirror port")
    conf = $ts.dut.call("mesa_mirror_conf_get")
    conf["port_no"] = $ts.dut.port_list[$port_idx_mirror]
    conf["tag"] = "MESA_MIRROR_TAG_NONE"
    $ts.dut.call("mesa_mirror_conf_set", conf)

    t_i("Ingress mirroring")
    $ts.dut.call("mesa_mirror_ingress_ports_set", port_idx_list_str([$port_idx_rx]))

    t_i("Egress mirroring")
    $ts.dut.call("mesa_mirror_egress_ports_set", port_idx_list_str([$port_idx_tx]))

    t_i("VLAN mirroring")
    vid = 100
    conf = $ts.dut.call("mesa_vlan_vid_conf_get", vid)
    conf["mirror"] = true
    conf = $ts.dut.call("mesa_vlan_vid_conf_set", vid, conf)

    t_i("ACL rule mirroring IPv6 frames on normal port")
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_IPV6")
    ace["id"] = 1
    ace["port_list"] = "#{port_normal}"
    ace["action"]["mirror"] = true
    $ts.dut.call("mesa_ace_add", 0, ace)
end

#---------- Frame testing -----------------------------------------------------

def cmd_base(idx_tx, idx_rx)
    mac_base = "00:00:00:00:00:0"
    smac = (mac_base + "#{idx_tx + 1}")
    dmac = (mac_base + "#{idx_rx + 1}")
    cmd = "eth dmac #{dmac} smac #{smac}"
end

def mirror_frame_test(txt, idx_tx, idx_rx, idx_list, cmd_add = "")
    t_i("#{txt} frame on port index #{idx_tx}")
    cmd = cmd_base(idx_tx, idx_rx) + cmd_add
    run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
end

test "frame-io" do
    idx_rx = $port_idx_rx
    idx_tx = $port_idx_tx
    idx_normal = $port_idx_normal
    idx_mirror = $port_idx_mirror

    mirror_frame_test("Learn", idx_rx, idx_mirror, [idx_tx, idx_normal, idx_mirror])
    mirror_frame_test("Learn", idx_tx, idx_mirror, [idx_rx, idx_normal])
    mirror_frame_test("Learn", idx_normal, idx_mirror, [idx_rx, idx_tx, idx_mirror])
    mirror_frame_test("Rx mirror", idx_rx, idx_normal, [idx_normal, idx_mirror])
    mirror_frame_test("Normal", idx_tx, idx_normal, [idx_normal])
    mirror_frame_test("Tx mirror", idx_normal, idx_tx, [idx_tx, idx_mirror])
    mirror_frame_test("Normal", idx_normal, idx_rx, [idx_rx])

    # Add tag and avoid switch padding after popping tag
    f_end = " data pattern cnt 64"
    cmd_add = cmd_tag_push({tpid: 0x8100, vid: 100}) + f_end
    mirror_frame_test("VLAN mirror", idx_normal, idx_rx, [idx_mirror], cmd_add)

    mirror_frame_test("ACL mirror", idx_normal, idx_rx, [idx_rx, idx_mirror], " ipv6")

    if (cap_get("L2_MIRROR_TAG") != 0)
        # Pushed tag on mirror port
        tag = {tpid: 0x88a8, vid: 42, pcp: 5, dei: 1}

        t_i("Enable mirror tagging")
        conf = $ts.dut.call("mesa_mirror_conf_get")
        conf["tag"] = "MESA_MIRROR_TAG_S"
        conf["vid"] = tag[:vid]
        conf["pcp"] = tag[:pcp]
        conf["dei"] = tag[:dei]
        $ts.dut.call("mesa_mirror_conf_set", conf)

        # Send the IPv6 frame (f1) again, expect S-tagged frame (f2) on mirror port
        f1 = cmd_base(idx_normal, idx_rx)
        f2 = f1
        f1 += " ipv6"
        f1 += f_end
        f2 += cmd_tag_push(tag)
        f2 += " ipv6"
        f2 += f_end
        cmd = "sudo ef name f1 #{f1} name f2 #{f2}"
        cmd += " tx #{$ts.pc.p[idx_normal]} name f1"
        cmd += " rx #{$ts.pc.p[idx_rx]} name f1"
        cmd += " rx #{$ts.pc.p[idx_mirror]} name f2"
        $ts.pc.run(cmd)
    end
end
