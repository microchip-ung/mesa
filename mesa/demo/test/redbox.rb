#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# RedBox ID and port indices are global variables
#
#   C    D
#   |    |
# +--------+
# | Switch |
# +--------+
#     | Interlink (RedBox port C)
# +--------+
# | RedBox |
# +--------+
#   |    |
#   A    B

$rb_id = nil
$idx_a = nil # Port A on RedBox
$idx_b = nil # Port B on RedBox
$idx_c = nil # Port C is just a switch port (not RedBox Interlink)
$idx_d = nil # Port D is just a another switch port

# Check that two ports can be part of a RedBox
check_capabilities do
    cnt = cap_get("L2_REDBOX_CNT")
    port_rb = []
    for rb_id in 0..(cnt - 1) do
        cap = $ts.dut.call("mesa_rb_cap_get", rb_id)
        cap["port_list"].split(",").each do |p|
            port = p.to_i
            t_i("port #{port} -> rb_id #{rb_id}")
            port_rb[port] = rb_id
        end
    end
    $ts.dut.p.each_with_index do |port_a, idx_a|
        rb_id = port_rb[port_a]
        $ts.dut.p.each_with_index do |port_b, idx_b|
            if (port_a != port_b and rb_id != nil and rb_id == port_rb[port_b])
                $rb_id = rb_id
                $idx_a = idx_a
                $idx_b = idx_b
                break
            end
        end
        if ($rb_id != nil)
            break
        end
    end
    assert($rb_id != nil, "RedBox must be present with two available ports")
    $ts.dut.p.each_with_index do |port, idx|
        if (idx != $idx_a and idx != $idx_b)
            if ($idx_c == nil)
                $idx_c = idx
            else
                $idx_d = idx
            end
        end
    end
end

#---------- Configuration -----------------------------------------------------

# Each entry in the test table has these fields:
# - Text string printed during test
# - Configuration of RedBox and switch
# - Table of frames with forwarding properties for each port (A/B/C/D)
# - Counter exceptions (optional)
test_table =
[
    # HSR-SAN tests
    {
        txt: "HSR-SAN, port A to port B/C/D",
        cfg: {mode: "HSR_SAN"},
        tab: [{fwd: [{idx_tx: $idx_a, hsr: {net_id: 2, lan_id: 1}},
                     {idx: $idx_b, hsr: {net_id: 2, lan_id: 1}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "HSR-SAN, port B to port A/C/D",
        cfg: {mode: "HSR_SAN"},
        tab: [{fwd: [{idx_tx: $idx_b, hsr: {net_id: 2, lan_id: 1}},
                     {idx: $idx_a, hsr: {net_id: 2, lan_id: 1}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "HSR-SAN, port C to port A/B/D",
        cfg: {mode: "HSR_SAN", net_id: 7},
        tab: [{fwd: [{idx_tx: $idx_c},
                     {idx: $idx_a, hsr: {net_id: 7}},
                     {idx: $idx_b, hsr: {net_id: 7}},
                     {idx: $idx_d}]}]
    },
    {
        txt: "HSR-SAN, port D to port A/B/C",
        cfg: {mode: "HSR_SAN", net_id: 7},
        tab: [{fwd: [{idx_tx: $idx_d},
                     {idx: $idx_a, hsr: {net_id: 7}},
                     {idx: $idx_b, hsr: {net_id: 7}},
                     {idx: $idx_c}]}]
    },
    {
        txt: "HSR-SAN, discard HSR-tagged on Interlink",
        cfg: {mode: "HSR_SAN"},
        tab: [{fwd: [{idx_tx: $idx_c, hsr: {}},
                     {idx: $idx_d, hsr: {}}]}]
    },
    {
        txt: "HSR-SAN, discard non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_SAN"},
        tab: [
            {fwd: [{idx_tx: $idx_a}]},
            {fwd: [{idx_tx: $idx_b}]},
        ]
    },
    {
        txt: "HSR-SAN with VLANs, port A to port B/C",
        cfg: {mode: "HSR_SAN",
              vlan: {vid: 10, list: [{idx: $idx_a, type: "C", uvid: 0},
                                     {idx: $idx_c, pvid: 10, uvid: 10}]}},
        tab: [{fwd: [{idx_tx: $idx_a, vid: 10, hsr: {}},
                     {idx: $idx_b, vid: 10, hsr: {}},
                     {idx: $idx_c}]}]
    },
    {
        txt: "HSR-SAN with VLANs, port D to port A/B",
        cfg: {mode: "HSR_SAN", net_id: 6,
              vlan: {vid: 10, list: [{idx: $idx_a, type: "C", uvid: 0},
                                     {idx: $idx_d, pvid: 10, uvid: 10}]}},
        tab: [{fwd: [{idx_tx: $idx_d},
                     {idx: $idx_a, vid: 10, hsr: {net_id: 6}},
                     {idx: $idx_b, vid: 10, hsr: {net_id: 6}}]}]
    },
    {
        # Fails, Jira-208: Two frames forwarded differently (payload depedent)
        txt: "HSR-SAN with VLANs, forwarding two tagged frames fails",
        cfg: {mode: "HSR_SAN"},
        tab: [
            {fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}]},
            {fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {seqn: 2}},
                   {idx: $idx_b, hsr: {seqn: 2}},
                   {idx: $idx_d}]},
        ]
    },
    {
        txt: "HSR-SAN, DMAC-PNT filtering on Interlink->LRE",
        cfg: {mode: "HSR_SAN"},
        tab: [
            # Learn SMAC in PNT and flush switch port
            {frm: {smac: 0xcc},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}],
             flush: $idx_c},
            # Send to DMAC on Interlink, expect discard on LRE
            {frm: {dmac: 0xcc},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_d}]}
        ]
    },
    {
        txt: "HSR-SAN, DMAC-PNT-STATIC filtering on Interlink->LRE",
        cfg: {mode: "HSR_SAN", proxy: {mac: 0xcc}},
        # Send to DMAC on Interlink, expect discard on LRE
        tab: [{frm: {dmac: 0xcc},
               fwd: [{idx_tx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "HSR-SAN, DMAC-PNT filtering on LRE->LRE",
        cfg: {mode: "HSR_SAN"},
        tab: [
            # Learn SMAC in PNT (and on switch port C)
            {frm: {smac: 0xcc},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}]},
            # Send to DMAC on LRE, expect discard on LRE
            {frm: {dmac: 0xcc},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_c}]}
        ]
    },
    {
        txt: "HSR-SAN, DMAC-PNT-STATIC filtering on LRE->LRE",
        cfg: {mode: "HSR_SAN", proxy: {mac: 0xcc}},
        # Send to DMAC on LRE, expect discard on LRE
        tab: [{frm: {dmac: 0xcc},
               fwd: [{idx_tx: $idx_b, hsr: {}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "HSR-SAN, SMAC-PNT filtering/ageing on LRE->interlink",
        cfg: {mode: "HSR_SAN", pnt_age_time: 20},
        tab: [
            # Learn SMAC in PNT
            {frm: {smac: 0xcc},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}],
             wait: 10},
            # Send from SMAC on LRE, expect discard on Interlink
            {frm: {smac: 0xcc},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}}],
             wait: 10},
            # Send from SMAC on LRE, expect forward on Interlink
            {frm: {smac: 0xcc},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_c},
                   {idx: $idx_d}]}
        ]
    },
    {
        txt: "HSR-SAN, SMAC-PNT-STATIC filtering on LRE->interlink",
        cfg: {mode: "HSR_SAN", proxy: {mac: 0xcc}},
        # Send from SMAC on LRE, expect discard on Interlink
        tab: [{frm: {smac: 0xcc},
               fwd: [{idx_tx: $idx_b, hsr: {}},
                     {idx: $idx_a, hsr: {}}]}]
    },
    {
        txt: "HSR-SAN, DMAC-NT filtering on LRE->interlink",
        cfg: {mode: "HSR_SAN", node: {mac: 0xbb}},
        tab: [{frm: {dmac: 0xbb},
               fwd: [{idx_tx: $idx_a, hsr:{}},
                     {idx: $idx_b, hsr: {}}]}]
    },

    # PRP-SAN tests
    {
        # Fails, PRP size 6 bytes too long
        txt: "PRP-SAN, port A to port C/D",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: $idx_a, prp: {lan_id: 0}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        # Fails, PRP size 6 bytes too long
        txt: "PRP-SAN, port B to port C/D",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: $idx_b, prp: {lan_id: 1}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "PRP-SAN, port A wrong LAN",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: $idx_a, prp: {lan_id: 1}},
                     {idx: $idx_c, prp: {lan_id: 1}},
                     {idx: $idx_d, prp: {lan_id: 1}}]}],
        cnt: [{port: "port_a", name: "rx_wrong_lan", val: 1}]
    },
    {
        # Fails, Jira-210: No PRP trailer added
        txt: "PRP-SAN, port C to port A/B with sequence numbers",
        cfg: {mode: "PRP_SAN"},
        tab: [
            {fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, prp: {lan_id: 0}},
                   {idx: $idx_b, prp: {lan_id: 1}},
                   {idx: $idx_d}]},
            {fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, prp: {lan_id: 0}},
                   {idx: $idx_b, prp: {lan_id: 1}},
                   {idx: $idx_d}]},
        ]
    },
    {
        txt: "PRP-SAN, forward to SAN on port A",
        cfg: {mode: "PRP_SAN", nt_age_time: 20},
        tab: [
            # Learn SAN on port A
            {frm: {smac: 0xaa},
             fwd: [{idx_tx: $idx_a},
                   {idx: $idx_c},
                   {idx: $idx_d}],
             wait: 10},
            # Forward to SAN on port A
            {frm: {dmac: 0xaa},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a}],
             wait: 10},
            # Node timeout, forward to SAN on port A/B
            {frm: {dmac: 0xaa},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, prp: {lan_id: 0}},
                   {idx: $idx_b, prp: {lan_id: 1}}]},
        ]
    },
    {
        txt: "PRP-SAN, forward to SAN on port B",
        cfg: {mode: "PRP_SAN", nt_age_time: 20},
        tab: [
            # Learn SAN on port B
            {frm: {smac: 0xbb},
             fwd: [{idx_tx: $idx_b},
                   {idx: $idx_c},
                   {idx: $idx_d}],
             wait: 10},
            # Forward to SAN on port B
            {frm: {dmac: 0xbb},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a}],
             wait: 10},
            # Node timeout, forward to SAN on port A/B
            {frm: {dmac: 0xbb},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, prp: {lan_id: 0}},
                   {idx: $idx_b, prp: {lan_id: 1}}]},
        ]
    },

    # HSR-PRP tests
    {
        # Fails, translation to NetId 5 not working
        txt: "HSR-PRP, port A to port C/D",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}},
                     {idx: $idx_c, prp: {}},
                     {idx: $idx_d, prp: {}}]}]
    },
    {
        # Fails, PRP size 6 bytes too long
        txt: "HSR-PRP, port C to port A/B",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: $idx_c, prp: {}},
                     {idx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}},
                     {idx: $idx_d, prp: {}}]}]
    },
    {
        txt: "HSR-PRP, discard HSR-tagged on Interlink",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: $idx_c, hsr: {}},
                     {idx: $idx_d, hsr: {}}]}]
    },
    {
        txt: "HSR-PRP, discard non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_PRP"},
        tab: [
            {fwd: [{idx_tx: $idx_a}]},
            {fwd: [{idx_tx: $idx_b}]},
        ]
    },
    {
        txt: "HSR-PRP, DMAC-PNT filtering on Interlink->LRE",
        cfg: {mode: "HSR_PRP"},
        tab: [
            # Learn SMAC in PNT and flush switch port
            {frm: {smac: 0xcc},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}],
             flush: $idx_c},
            # Send to DMAC on Interlink, expect discard on LRE
            {frm: {dmac: 0xcc},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_d}]}
        ]
    },
    {
        txt: "HSR-PRP, DMAC-PNT filtering on LRE->LRE",
        cfg: {mode: "HSR_PRP"},
        tab: [
            # Learn SMAC in PNT (and on switch port C)
            {frm: {smac: 0xcc},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}]},
            # Send to DMAC on LRE, expect discard on LRE
            {frm: {dmac: 0xcc},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_c, prp: {}}]}
        ]
    },
    {
        txt: "HSR-PRP, DMAC-NT filtering on LRE->interlink",
        cfg: {mode: "HSR_PRP", node: {mac: 0xbb}},
        tab: [{frm: {dmac: 0xbb},
               fwd: [{idx_tx: $idx_a, hsr:{}},
                     {idx: $idx_b, hsr: {}}]}]
    },

    # HSR-HSR tests
    {
        txt: "HSR-HSR, port A to port B/C/D",
        cfg: {mode: "HSR_HSR"},
        tab: [{fwd: [{idx_tx: $idx_a, hsr: {net_id: 3}},
                     {idx: $idx_b, hsr: {net_id: 3}},
                     {idx: $idx_c, hsr: {net_id: 3}},
                     {idx: $idx_d, hsr: {net_id: 3}}]}]
    },
    {
        txt: "HSR-HSR, port C to port A/B/D",
        cfg: {mode: "HSR_HSR"},
        tab: [{fwd: [{idx_tx: $idx_c, hsr: {net_id: 3}},
                     {idx: $idx_a, hsr: {net_id: 3}},
                     {idx: $idx_b, hsr: {net_id: 3}},
                     {idx: $idx_d, hsr: {net_id: 3}}]}]
    },
    {
        txt: "HSR-HSR, discard non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_HSR"},
        tab: [
            {fwd: [{idx_tx: $idx_a}]},
            {fwd: [{idx_tx: $idx_b}]},
        ]
    },
    {
        txt: "HSR-HSR, DMAC-PNT filtering on LRE->LRE",
        cfg: {mode: "HSR_HSR"},
        tab: [
            # Learn SMAC in PNT (and on switch port C)
            {frm: {smac: 0xcc},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}]},
            # Send to DMAC on LRE, expect discard on LRE
            {frm: {dmac: 0xcc},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_c, hsr: {}}]}
        ]
    },
    {
        txt: "HSR-HSR, DMAC-NT filtering on LRE->interlink",
        cfg: {mode: "HSR_HSR", node: {mac: 0xbb}},
        tab: [{frm: {dmac: 0xbb},
               fwd: [{idx_tx: $idx_a, hsr:{}},
                     {idx: $idx_b, hsr: {}}]}]
    },
    {
        txt: "HSR-HSR, NetId filtering/translation",
        cfg: {mode: "HSR_HSR", net_id: 4},
        tab: [
            # NetId 4 not forwarded to Interlink
            {fwd: [{idx_tx: $idx_a, hsr: {net_id: 4}},
                   {idx: $idx_b, hsr: {net_id: 4}}]},
            # Other NetIds translated to 4 on Interlink
            {fwd: [{idx_tx: $idx_a, hsr: {net_id: 3}},
                   {idx: $idx_b, hsr: {net_id: 3}},
                   {idx: $idx_c, hsr: {net_id: 4}},
                   {idx: $idx_b, hsr: {net_id: 4}}]},
        ]
    },
]

def vlan_port_conf_set(idx, e)
    port = $ts.dut.p[idx]
    conf = {}
    conf["port_type"] = ("MESA_VLAN_PORT_TYPE_" + fld_get(e, :type, "UNAWARE"))
    conf["pvid"] = fld_get(e, :pvid, 1)
    conf["untagged_vid"] = fld_get(e, :uvid, 1)
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    conf["ingress_filter"] = false
    $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
end

def cnt_incr(c, port_name, cnt_name, incr = 1)
    c[port_name][cnt_name] = (c[port_name][cnt_name] + incr)
end

def redbox_test(t)
    cfg = t[:cfg]

    # RedBox configuration
    mode = fld_get(cfg, :mode, "DISABLED")
    port_a = $ts.dut.p[$idx_a]
    port_b = $ts.dut.p[$idx_b]
    port_c = $ts.dut.p[$idx_c]
    conf = $ts.dut.call("mesa_rb_conf_get", $rb_id)
    conf["mode"] = ("MESA_RB_MODE_" + mode)
    conf["port_a"] = port_a
    conf["port_b"] = port_b
    conf["net_id"] = fld_get(cfg, :net_id)
    conf["lan_id"] = fld_get(cfg, :lan_id)
    conf["nt_age_time"] = fld_get(cfg, :nt_age_time)
    conf["pnt_age_time"] = fld_get(cfg, :pnt_age_time)
    conf = $ts.dut.call("mesa_rb_conf_set", $rb_id, conf)

    # Remove nodes and proxy nodes from previous tests
    $ts.dut.call("mesa_rb_node_table_clear", $rb_id, "MESA_RB_CLEAR_ALL")
    $ts.dut.call("mesa_rb_proxy_node_table_clear", $rb_id, "MESA_RB_CLEAR_ALL")

    # Flush MAC addresses learned previously
    $ts.dut.call("mesa_mac_table_flush")

    # Node entry
    node = fld_get(cfg, :node, nil)
    if (node != nil)
        mac = fld_get(node, :mac, 0xee)
        mac = {addr: [0,0,0,0,0,mac]}
        type = ("MESA_RB_NODE_TYPE_" + fld_get(node, :type, "DAN"))
        san_a = fld_get(node, :san_a, false)
        conf = {type: type, san_a: san_a}
        $ts.dut.call("mesa_rb_node_add", $rb_id, mac, conf)
    end

    # Proxy Node entry
    proxy = fld_get(cfg, :proxy, nil)
    if (proxy != nil)
        mac = fld_get(proxy, :mac, 0xee)
        mac = {addr: [0,0,0,0,0,mac]}
        $ts.dut.call("mesa_rb_proxy_node_add", $rb_id, mac)
    end

    # VLAN configuration
    vlan = fld_get(cfg, :vlan, nil)
    vlan_idx_list = []
    if (vlan != nil)
        vid = fld_get(vlan, :vid)
        list = fld_get(vlan, :list, [])
        list.each do |e|
            idx = fld_get(e, :idx)
            vlan_idx_list.push(idx)
            vlan_port_conf_set(idx, e)
        end
        $ts.dut.call("mesa_vlan_port_members_set", vid, port_idx_list_str(vlan_idx_list))
    end

    idx_name = []
    $ts.dut.p.each_index do |idx|
        s = (idx == $idx_a ? "a" : idx == $idx_b ? "b" : idx == $idx_c ? "c" : "d")
        idx_name[idx] = s
    end

    # Clear counters
    $ts.dut.call("mesa_rb_counters_clear", $rb_id)
    exp = $ts.dut.call("mesa_rb_counters_get", $rb_id)

    tab = fld_get(t, :tab, [])
    tab.each do |entry|
        # Frame test
        cmd = "sudo ef"
        cmd_add = ""
        idx_list = []
        idx_tx = nil
        smac = 1
        f = fld_get(entry, :frm, {})
        len = fld_get(f, :len, 46)
        fwd = fld_get(entry, :fwd, [])
        fwd.each_with_index do |e, i|
            idx = e[:idx_tx]
            dir = "rx"
            if (idx == nil)
                idx = e[:idx]
            else
                idx_tx = idx
                smac = fld_get(f, :smac, "0x#{idx_name[idx]}")
                dir = "tx"
            end
            name = " name f_#{idx_name[idx]}"
            cmd_add += " #{dir} #{$ts.pc.p[idx]}#{name}"
            cmd += name
            cmd += " eth"
            if (f.key?:dmac)
                cmd += " dmac #{f[:dmac]}"
            end
            cmd += " smac #{smac}"
            if (e.key?:vid)
                cmd += " ctag vid #{e[:vid]}"
            end
            hsr = fld_get(e, :hsr, nil)
            if (hsr != nil)
                net_id = fld_get(hsr, :net_id, 0)
                lan_id = fld_get(hsr, :lan_id, 0)
                path_id = ((net_id << 1) + lan_id)
                size = fld_get(hsr, :size, len + 6)
                seqn = fld_get(hsr, :seqn, 1)
                cmd += " htag pathid #{path_id} size #{size} seqn #{seqn}"
            end
            cmd += " et 0xeeee data repeat #{len} 0x00" # TBD: Using zeros is work-around
            prp = fld_get(e, :prp, nil)
            if (prp != nil)
                seqn = fld_get(prp, :seqn, 1)
                net_id = fld_get(prp, :net_id, 5)
                lan_id = fld_get(prp, :lan_id, 0)
                path_id = ((net_id << 1) + lan_id)
                size = fld_get(prp, :size, len + 6)
                cmd += " prp seqn #{seqn} lanid #{path_id} size #{size}"
            end
            idx_list.push(idx)
        end
        cmd += cmd_add
        $ts.dut.p.each_index do |idx|
            if (!idx_list.include?idx)
                cmd += " rx #{$ts.pc.p[idx]}"
            end
        end
        $ts.pc.try(cmd)

        flush_idx = fld_get(entry, :flush, nil)
        if (flush_idx != nil)
            # Flush switch core port
            $ts.dut.call("mesa_mac_table_port_flush", $ts.dut.p[flush_idx])
        end

        wait = fld_get(entry, :wait)
        if (wait > 0)
            # Wait a number of seconds
            sleep(wait)
        end

        # Update expected counters
        if (idx_tx == $idx_a)
            cnt_incr(exp, "port_a", "rx")
        elsif (idx_list.include?($idx_a))
            cnt_incr(exp, "port_a", "tx")
        end
        if (idx_tx == $idx_b)
            cnt_incr(exp, "port_b", "rx")
        elsif (idx_list.include?($idx_b))
            cnt_incr(exp, "port_b", "tx")
        end
        if (idx_tx == $idx_c || idx_tx == $idx_d)
            cnt_incr(exp, "port_c", "rx")
        elsif (idx_list.include?($idx_c) or idx_list.include?($idx_d))
            cnt_incr(exp, "port_c", "tx")
        end
    end

    # Check RedBox counters
    cnt = fld_get(t, :cnt, [])
    cnt.each do |c|
        # Override default expected counters
        exp[c[:port]][c[:name]] = c[:val]
    end
    cnt = $ts.dut.call("mesa_rb_counters_get", $rb_id)
    ["port_a", "port_b", "port_c"].each do |port_name|
        ["tx", "rx", "rx_wrong_lan", "rx_own",
         "tx_dupl_zero", "tx_dupl_one", "tx_dupl_multi"].each do |cnt_name|
            name = "#{port_name}[#{cnt_name}]"
            #check_counter(name, cnt[port_name][cnt_name], exp[port_name][cnt_name])
        end
    end

    # Restore VLAN port configuration
    vlan_idx_list.each do |idx|
        vlan_port_conf_set(idx, {})
    end
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        redbox_test(t)
    end
end

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api cil redbox")
    #$ts.dut.run("mesa-cmd deb api ai vlan")
    $ts.dut.run("mesa-cmd port stati pac")
    #$ts.dut.run("mesa-cmd mac dump")
end
