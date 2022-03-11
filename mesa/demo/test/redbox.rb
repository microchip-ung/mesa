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

test "show-redbox" do
    port_cnt = cap_get("PORT_CNT")
    pmap = $ts.dut.call("mesa_port_map_get", port_cnt)
    t_i("RedBox #{$rb_id}:")
    name = ["A", "B", "C", "D"]
    [$idx_a, $idx_b, $idx_c, $idx_d].each do |idx|
        port = $ts.dut.p[idx]
        chip_port = pmap[port]["chip_port"]
        t_i("Port #{name[idx]}: #{port}(#{chip_port}) - #{$ts.pc.p[idx]}")
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
        txt: "port A to port B/C/D",
        cfg: {mode: "HSR_SAN"},
        tab: [{fwd: [{idx_tx: $idx_a, hsr: {net_id: 2, lan_id: 1}},
                     {idx: $idx_b, hsr: {net_id: 2, lan_id: 1}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "port B to port A/C/D",
        cfg: {mode: "HSR_SAN"},
        tab: [{fwd: [{idx_tx: $idx_b, hsr: {net_id: 2, lan_id: 1}},
                     {idx: $idx_a, hsr: {net_id: 2, lan_id: 1}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "port C to port A/B/D",
        cfg: {mode: "HSR_SAN", net_id: 7},
        tab: [{fwd: [{idx_tx: $idx_c},
                     {idx: $idx_a, hsr: {net_id: 7}},
                     {idx: $idx_b, hsr: {net_id: 7}},
                     {idx: $idx_d}]}]
    },
    {
        txt: "port D to port A/B/C",
        cfg: {mode: "HSR_SAN", net_id: 7},
        tab: [{fwd: [{idx_tx: $idx_d},
                     {idx: $idx_a, hsr: {net_id: 7}},
                     {idx: $idx_b, hsr: {net_id: 7}},
                     {idx: $idx_c}]}]
    },
    {
        txt: "discard HSR-tagged on Interlink",
        cfg: {mode: "HSR_SAN"},
        tab: [{fwd: [{idx_tx: $idx_c, hsr: {}},
                     {idx: $idx_d, hsr: {}}]}]
    },
    {
        txt: "discard non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_SAN"},
        tab: [
            {fwd: [{idx_tx: $idx_a}]},
            {fwd: [{idx_tx: $idx_b}]},
        ]
    },
    {
        txt: "VLANs, port A to port B/C",
        cfg: {mode: "HSR_SAN",
              vlan: {vid: 10, list: [{idx: $idx_a, type: "C", uvid: 0},
                                     {idx: $idx_c, pvid: 10, uvid: 10}]}},
        tab: [{fwd: [{idx_tx: $idx_a, vid: 10, hsr: {}},
                     {idx: $idx_b, vid: 10, hsr: {}},
                     {idx: $idx_c}]}]
    },
    {
        txt: "VLANs, port D to port A/B",
        cfg: {mode: "HSR_SAN", net_id: 6,
              vlan: {vid: 10, list: [{idx: $idx_a, type: "C", uvid: 0},
                                     {idx: $idx_d, pvid: 10, uvid: 10}]}},
        tab: [{fwd: [{idx_tx: $idx_d},
                     {idx: $idx_a, vid: 10, hsr: {net_id: 6}},
                     {idx: $idx_b, vid: 10, hsr: {net_id: 6}}]}]
    },
    {
        # Fails, Jira-208: Two frames forwarded differently (payload depedent)
        txt: "forwarding two frames fails",
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
        txt: "DMAC-PNT filtering on Interlink->LRE",
        cfg: {mode: "HSR_SAN"},
        tab: [
            # Learn SMAC in PNT and flush switch port
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}],
             flush: $idx_c},
            # Send to DMAC on Interlink, expect discard on LRE
            {frm: {dmac: ":cc"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_d}]}
        ]
    },
    {
        txt: "DMAC-PNT-STATIC filtering on Interlink->LRE",
        cfg: {mode: "HSR_SAN", proxy: {mac: 0xcc}},
        # Send to DMAC on Interlink, expect discard on LRE
        tab: [{frm: {dmac: ":cc"},
               fwd: [{idx_tx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "DMAC-PNT filtering on LRE->LRE",
        cfg: {mode: "HSR_SAN"},
        tab: [
            # Learn SMAC in PNT (and on switch port C)
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}]},
            # Send to DMAC on LRE, expect discard on LRE
            {frm: {dmac: ":cc"},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_c}]}
        ]
    },
    {
        txt: "DMAC-PNT-STATIC filtering on LRE->LRE",
        cfg: {mode: "HSR_SAN", proxy: {mac: 0xcc}},
        # Send to DMAC on LRE, expect discard on LRE
        tab: [{frm: {dmac: ":cc"},
               fwd: [{idx_tx: $idx_b, hsr: {}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "SMAC-PNT filtering/ageing on LRE->interlink",
        cfg: {mode: "HSR_SAN", pnt_age_time: 20},
        tab: [
            # Learn SMAC in PNT
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}],
             wait: 10},
            # Send from SMAC on LRE, expect discard on Interlink
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}}],
             wait: 10},
            # Send from SMAC on LRE, expect forward on Interlink
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_c},
                   {idx: $idx_d}]}
        ]
    },
    {
        txt: "SMAC-PNT-STATIC filtering on LRE->interlink",
        cfg: {mode: "HSR_SAN", proxy: {mac: 0xcc}},
        # Send from SMAC on LRE, expect discard on Interlink
        tab: [{frm: {smac: ":cc"},
               fwd: [{idx_tx: $idx_b, hsr: {}},
                     {idx: $idx_a, hsr: {}}]}]
    },
    {
        txt: "DMAC-NT filtering on LRE->interlink",
        cfg: {mode: "HSR_SAN", node: {mac: 0xbb}},
        tab: [{frm: {dmac: ":bb"},
               fwd: [{idx_tx: $idx_a, hsr:{}},
                     {idx: $idx_b, hsr: {}}]}]
    },
    {
        txt: "BPDU Rx on LRE",
        cfg: {mode: "HSR_SAN", npi: $idx_d},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: $idx_a},
                     {idx: $idx_d, ifh_rx: $idx_a}]}]
    },
    {
        txt: "BPDU Tx to LREs",
        cfg: {mode: "HSR_SAN", npi: $idx_d},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: $idx_d, ifh_tx: $idx_a, rb_tag_dis: true},
                     {idx: $idx_a},
                     {idx: $idx_b}]}]
    },
    {
        txt: "Supervision Rx on LRE",
        cfg: {mode: "HSR_SAN", sv: "CPU_ONLY", npi: $idx_d},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}},
                     {idx: $idx_d, ifh_rx: $idx_a}]}]
    },
    {
        txt: "Supervision Tx to LREs",
        cfg: {mode: "HSR_SAN", npi: $idx_d},
        tab: [{frm: {dmac: "01:15:4e:00:01:00"},
               fwd: [{idx_tx: $idx_d, ifh_tx: $idx_a},
                     {idx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}}]}]
    },

    # PRP-SAN tests
    {
        # Fails, PRP size 6 bytes too long
        txt: "port A to port C/D",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: $idx_a, prp: {lan_id: 0}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        # Fails, PRP size 6 bytes too long
        txt: "port B to port C/D",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: $idx_b, prp: {lan_id: 1}},
                     {idx: $idx_c},
                     {idx: $idx_d}]}]
    },
    {
        txt: "port A wrong LAN",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: $idx_a, prp: {lan_id: 1}},
                     {idx: $idx_c, prp: {lan_id: 1}},
                     {idx: $idx_d, prp: {lan_id: 1}}]}],
        cnt: [{port: "port_a", name: "rx_wrong_lan", val: 1}]
    },
    {
        # Fails, Jira-210: No PRP trailer added
        txt: "port C to port A/B with sequence numbers",
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
        txt: "forward to SAN on port A",
        cfg: {mode: "PRP_SAN", nt_age_time: 20},
        tab: [
            # Learn SAN on port A
            {frm: {smac: ":aa"},
             fwd: [{idx_tx: $idx_a},
                   {idx: $idx_c},
                   {idx: $idx_d}],
             wait: 10},
            # Forward to SAN on port A
            {frm: {dmac: ":aa"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a}],
             wait: 10},
            # Node timeout, forward to SAN on port A/B
            {frm: {dmac: ":aa"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, prp: {lan_id: 0}},
                   {idx: $idx_b, prp: {lan_id: 1}}]},
        ]
    },
    {
        txt: "forward to SAN on port B",
        cfg: {mode: "PRP_SAN", nt_age_time: 20},
        tab: [
            # Learn SAN on port B
            {frm: {smac: ":bb"},
             fwd: [{idx_tx: $idx_b},
                   {idx: $idx_c},
                   {idx: $idx_d}],
             wait: 10},
            # Forward to SAN on port B
            {frm: {dmac: ":bb"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a}],
             wait: 10},
            # Node timeout, forward to SAN on port A/B
            {frm: {dmac: ":bb"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, prp: {lan_id: 0}},
                   {idx: $idx_b, prp: {lan_id: 1}}]},
        ]
    },
    {
        txt: "BPDU Rx on LRE",
        cfg: {mode: "PRP_SAN", npi: $idx_d},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: $idx_a},
                     {idx: $idx_d, ifh_rx: $idx_a}]}]
    },
    {
        txt: "BPDU Tx to LREs",
        cfg: {mode: "PRP_SAN", npi: $idx_d},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: $idx_d, ifh_tx: $idx_a, rb_tag_dis: true},
                     {idx: $idx_a},
                     {idx: $idx_b}]}]
    },
    {
        txt: "Supervision Rx on LRE",
        cfg: {mode: "PRP_SAN", sv: "CPU_ONLY", npi: $idx_d},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: $idx_a, prp: {}},
                     {idx: $idx_d, ifh_rx: $idx_a}]}]
    },
    {
        txt: "Supervision Tx to LREs",
        cfg: {mode: "PRP_SAN", npi: $idx_d},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: $idx_d, ifh_tx: $idx_a},
                     {idx: $idx_a, prp: {}},
                     {idx: $idx_b, prp: {lan_id: 1}}]}]
    },

    # HSR-PRP tests
    {
        # Fails, translation to NetId 5 not working
        txt: "port A to port C/D",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}},
                     {idx: $idx_c, prp: {}},
                     {idx: $idx_d, prp: {}}]}]
    },
    {
        # Fails, PRP size 6 bytes too long
        txt: "port C to port A/B",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: $idx_c, prp: {}},
                     {idx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}},
                     {idx: $idx_d, prp: {}}]}]
    },
    {
        txt: "discard HSR-tagged on Interlink",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: $idx_c, hsr: {}},
                     {idx: $idx_d, hsr: {}}]}]
    },
    {
        txt: "discard non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_PRP"},
        tab: [
            {fwd: [{idx_tx: $idx_a}]},
            {fwd: [{idx_tx: $idx_b}]},
        ]
    },
    {
        txt: "DMAC-PNT filtering on Interlink->LRE",
        cfg: {mode: "HSR_PRP"},
        tab: [
            # Learn SMAC in PNT and flush switch port
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}],
             flush: $idx_c},
            # Send to DMAC on Interlink, expect discard on LRE
            {frm: {dmac: ":cc"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_d}]}
        ]
    },
    {
        txt: "DMAC-PNT filtering on LRE->LRE",
        cfg: {mode: "HSR_PRP"},
        tab: [
            # Learn SMAC in PNT (and on switch port C)
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}]},
            # Send to DMAC on LRE, expect discard on LRE
            {frm: {dmac: :":cc"},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_c, prp: {}}]}
        ]
    },
    {
        txt: "DMAC-NT filtering on LRE->interlink",
        cfg: {mode: "HSR_PRP", node: {mac: 0xbb}},
        tab: [{frm: {dmac: ":bb"},
               fwd: [{idx_tx: $idx_a, hsr:{}},
                     {idx: $idx_b, hsr: {}}]}]
    },
    {
        txt: "Supervision Rx on LRE",
        cfg: {mode: "HSR_PRP", sv: "CPU_COPY", npi: $idx_d},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}},
                     {idx: $idx_c, prp: {}},
                     {idx: $idx_d, prp: {}, ifh_rx: $idx_a}]}]
    },

    # HSR-HSR tests
    {
        txt: "port A to port B/C/D",
        cfg: {mode: "HSR_HSR"},
        tab: [{fwd: [{idx_tx: $idx_a, hsr: {net_id: 3}},
                     {idx: $idx_b, hsr: {net_id: 3}},
                     {idx: $idx_c, hsr: {net_id: 3}},
                     {idx: $idx_d, hsr: {net_id: 3}}]}]
    },
    {
        txt: "port C to port A/B/D",
        cfg: {mode: "HSR_HSR"},
        tab: [{fwd: [{idx_tx: $idx_c, hsr: {net_id: 3}},
                     {idx: $idx_a, hsr: {net_id: 3}},
                     {idx: $idx_b, hsr: {net_id: 3}},
                     {idx: $idx_d, hsr: {net_id: 3}}]}]
    },
    {
        txt: "discard non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_HSR"},
        tab: [
            {fwd: [{idx_tx: $idx_a}]},
            {fwd: [{idx_tx: $idx_b}]},
        ]
    },
    {
        txt: "DMAC-PNT filtering on LRE->LRE",
        cfg: {mode: "HSR_HSR"},
        tab: [
            # Learn SMAC in PNT (and on switch port C)
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: $idx_c},
                   {idx: $idx_a, hsr: {}},
                   {idx: $idx_b, hsr: {}},
                   {idx: $idx_d}]},
            # Send to DMAC on LRE, expect discard on LRE
            {frm: {dmac: ":cc"},
             fwd: [{idx_tx: $idx_a, hsr: {}},
                   {idx: $idx_c, hsr: {}}]}
        ]
    },
    {
        txt: "DMAC-NT filtering on LRE->interlink",
        cfg: {mode: "HSR_HSR", node: {mac: 0xbb}},
        tab: [{frm: {dmac: ":bb"},
               fwd: [{idx_tx: $idx_a, hsr:{}},
                     {idx: $idx_b, hsr: {}}]}]
    },
    {
        txt: "NetId filtering/translation",
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
    {
        txt: "BPDU Rx on LRE",
        cfg: {mode: "HSR_HSR", npi: $idx_d},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: $idx_a},
                     {idx: $idx_d, ifh_rx: $idx_a}]}]
    },
    {
        txt: "BPDU Tx to LREs",
        cfg: {mode: "HSR_HSR", npi: $idx_d},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: $idx_d, ifh_tx: $idx_a, rb_tag_dis: true},
                     {idx: $idx_a},
                     {idx: $idx_b}]}]
    },
    {
        txt: "Supervision Rx on LRE",
        cfg: {mode: "HSR_HSR", npi: $idx_d},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}},
                     {idx: $idx_d, hsr: {}, ifh_rx: $idx_a}]}]
    },
    {
        txt: "Supervision Tx to LREs",
        cfg: {mode: "HSR_HSR", npi: $idx_d},
        tab: [{frm: {dmac: "01:15:4e:00:01:00"},
               fwd: [{idx_tx: $idx_d, hsr: {}, ifh_tx: $idx_a},
                     {idx: $idx_a, hsr: {}},
                     {idx: $idx_b, hsr: {}}]}]
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
    conf["sv"] = ("MESA_RB_SV_" + fld_get(cfg, :sv, "FORWARD"))
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

    # NPI port
    idx_npi = fld_get(cfg, :npi, nil)
    if (idx_npi != nil)
        # Map CPU queue 0 to NPI port
        conf = $ts.dut.call("mesa_packet_rx_conf_get")
        conf["queue"][0]["npi"]["enable"] = true
        $ts.dut.call("mesa_packet_rx_conf_set", conf)

        # Enable NPI port
        conf = $ts.dut.call("mesa_npi_conf_get")
        conf["enable"] = true
        conf["port_no"] = $ts.dut.p[idx_npi]
        $ts.dut.call("mesa_npi_conf_set", conf)
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
        smac = "01"
        f = fld_get(entry, :frm, {})
        et = fld_get(f, :et, 0xeeee)
        len = fld_get(f, :len, 46)
        fwd = fld_get(entry, :fwd, [])
        fwd.each_with_index do |e, i|
            idx = e[:idx_tx]
            dir = "rx"
            if (idx == nil)
                idx = e[:idx]
            else
                idx_tx = idx
                smac = fld_get(f, :smac, ":0#{idx_name[idx]}")
                dir = "tx"
            end
            name = " name f_#{idx_name[idx]}"
            cmd_add += " #{dir} #{$ts.pc.p[idx]}#{name}"
            cmd += name
            ifh_rx = fld_get(e, :ifh_rx, nil)
            if (ifh_rx != nil)
                cmd += (" " + cmd_rx_ifh_push({port_idx: ifh_rx}))
            end
            ifh_tx = fld_get(e, :ifh_tx, nil)
            if (ifh_tx != nil)
                rb_tag_dis = fld_get(e, :rb_tag_dis, false)
                port = $ts.dut.p[ifh_tx]
                cmd += (" " + cmd_tx_ifh_push({dst_port: port, rb_tag_disable: rb_tag_dis}))
            end
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
            cmd += " et 0x#{et.to_s(16)} data repeat #{len} 0x00" # TBD: Using zeros is work-around
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

    # Restore NPI configuration
    if (idx_npi != nil)
        conf = $ts.dut.call("mesa_npi_conf_get")
        conf["enable"] = false
        $ts.dut.call("mesa_npi_conf_set", conf)
    end
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
cnt_ok = 0
cnt_err = 0
test_table.each do |t|
    next if (t[:sel] != sel)
    cfg = fld_get(t, :cfg, nil)
    mode = fld_get(cfg, :mode, "?")
    txt = (mode + ", " + t[:txt])
    test txt do
        err = $test_stack[-1][:cnt_err]
        redbox_test(t)
        if ($test_stack[-1][:cnt_err] == err)
            cnt_ok += 1
        else
            cnt_err += 1
        end
    end
end
t_i("Total : #{cnt_ok + cnt_err}")
t_i("Ok    : #{cnt_ok}")
t_i("Errors: #{cnt_err}")

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api cil redbox")
    #$ts.dut.run("mesa-cmd deb api ai vlan")
    $ts.dut.run("mesa-cmd port stati pac")
    #$ts.dut.run("mesa-cmd mac dump")
end
