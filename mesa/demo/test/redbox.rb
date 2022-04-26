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

# Global table of port A/B/C/D combinations
$rb_table = []
$rb = nil
$rb_id = nil

# Check that two ports can be part of a RedBox
check_capabilities do
    cnt = cap_get("L2_REDBOX_CNT")
    port_rb = []
    cnt.times do |rb_id|
        cap = $ts.dut.call("mesa_rb_cap_get", rb_id)
        cap["port_list"].split(",").each do |p|
            port = p.to_i
            t_i("port #{port} -> rb_id #{rb_id}")
            port_rb[port] = rb_id
        end
    end

    # For each port A, look for port B/C/D
    $ts.dut.p.each_with_index do |port_a, idx_a|
        rb_id = port_rb[port_a]
        next if (rb_id == nil)
        # Look for port B with same RedBox ID
        port_rb[port_a] = nil
        $ts.dut.p.each_with_index do |port_b, idx_b|
            next if (rb_id != port_rb[port_b])
            # Found port B, look for port C and D
            port_rb[port_b] = nil
            idx_c = nil
            $ts.dut.p.each_index do |idx|
                next if (idx == idx_a or idx == idx_b)
                if (idx_c == nil)
                    idx_c = idx
                else
                    # Found port A/B/C/D, save in global table
                    $rb_table << {rb_id: rb_id,
                                  idx_a: idx_a,
                                  idx_b: idx_b,
                                  idx_c: idx_c,
                                  idx_d: idx}
                    break
                end
            end
            break
        end
    end
    assert($rb_table.size > 0, "RedBox must be present with two available ports")
end

#---------- Configuration -----------------------------------------------------

test "disable-flow-control" do
    $ts.dut.run("mesa-cmd port maxframe 1524")
    $ts.dut.run("mesa-cmd port flow control disable")
    sleep(1)
    dut_port_state_up($ts.dut.p)
end

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
        tab: [{fwd: [{idx_tx: "a", hsr: {net_id: 2, lan_id: 1}},
                     {idx_rx: "b", hsr: {net_id: 2, lan_id: 1}},
                     {idx_rx: "c"},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port A to port B/C/D - max-length",
        cfg: {mode: "HSR_SAN"},
        tab: [{frm: {len: 1500},
               fwd: [{idx_tx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "c"},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port B to port A/C/D - burst",
        cfg: {mode: "HSR_SAN"},
        tab: [{node: {mac: 0x0b}},
              {cnt: 10,
               fwd: [{idx_tx: "b", hsr: {net_id: 2, lan_id: 1}},
                     {idx_rx: "a", hsr: {net_id: 2, lan_id: 1}},
                     {idx_rx: "c"},
                     {idx_rx: "d"}]},
              {node: {mac: 0x0b, cmd: "get", cnt: [{port: "b", name: "rx", val: 10}]}}]
    },
    {
        txt: "port C to port A/B/D",
        cfg: {mode: "HSR_SAN", net_id: 7},
        tab: [{proxy: {mac: 0x0c}},
              {fwd: [{idx_tx: "c"},
                     {idx_rx: "a", hsr: {net_id: 7}},
                     {idx_rx: "b", hsr: {net_id: 7}},
                     {idx_rx: "d"}]},
              {proxy: {mac: 0x0c, cmd: "get", cnt: 1}}]
    },
    {
        txt: "port C to port A/B/D - max-length",
        cfg: {mode: "HSR_SAN"},
        tab: [{frm: {len: 1500},
               fwd: [{idx_tx: "c"},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port D to port A/B/C - burst",
        cfg: {mode: "HSR_SAN", net_id: 7},
        tab: [{cnt: 10,
               fwd: [{idx_tx: "d"},
                     {idx_rx: "a", hsr: {net_id: 7}},
                     {idx_rx: "b", hsr: {net_id: 7}},
                     {idx_rx: "c"}]},
              {proxy: {mac: 0x0d, cmd: "get", cnt: 10}}]
    },
    {
        txt: "port D to port A/B/C - repeated burst",
        cfg: {mode: "HSR_SAN"},
        tab: [{rep: 1000,
               fwd: [{idx_tx: "d"},
                     {idx_rx: "a"},
                     {idx_rx: "b"},
                     {idx_rx: "c"}]}]
    },
    {
        txt: "port C to port B/D - port A disabled",
        cfg: {mode: "HSR_SAN", idx_dis: "a"},
        tab: [{fwd: [{idx_tx: "c"},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port D to port A/C - port B disabled",
        cfg: {mode: "HSR_SAN", idx_dis: "b"},
        tab: [{fwd: [{idx_tx: "d"},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "c"}]}]
    },
    {
        txt: "discard HSR-tagged on Interlink",
        cfg: {mode: "HSR_SAN"},
        tab: [{fwd: [{idx_tx: "c", hsr: {}},
                     {idx_rx: "d", hsr: {}}]}]
    },
    {
        txt: "redirect non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_SAN", npi: "d", non_hsr_queue: 1},
        tab: [{fwd: [{idx_tx: "a"},
                     {idx_rx: "d", ifh_rx: "a"}]}],
        # Expect zero counters
        cnt: [
            {port: "port_c", name: "tx", val: 0},
            {port: "port_c", name: "tx_dupl_zero", val: 0}
        ]
    },
    {
        txt: "VLANs, port A to port B/C",
        cfg: {mode: "HSR_SAN",
              vlan: {vid: 10, list: [{idx: "a", type: "C", uvid: 0},
                                     {idx: "c", pvid: 10, uvid: 10}]}},
        tab: [{fwd: [{idx_tx: "a", vid: 10, hsr: {}},
                     {idx_rx: "b", vid: 10, hsr: {}},
                     {idx_rx: "c"}]}]
    },
    {
        txt: "VLANs, port D to port A/B",
        cfg: {mode: "HSR_SAN", net_id: 6,
              vlan: {vid: 10, list: [{idx: "a", type: "C", uvid: 0},
                                     {idx: "d", pvid: 10, uvid: 10}]}},
        tab: [{fwd: [{idx_tx: "d"},
                     {idx_rx: "a", vid: 10, hsr: {net_id: 6}},
                     {idx_rx: "b", vid: 10, hsr: {net_id: 6}}]}]
    },
    {
        txt: "DMAC-PNT filtering on Interlink->LRE",
        cfg: {mode: "HSR_SAN"},
        tab: [
            # Learn SMAC in PNT and flush switch port
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d"}],
             flush: "c"},
            # Send to DMAC on Interlink, expect discard on LRE
            {frm: {dmac: ":cc"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "d"}]}
        ]
    },
    {
        txt: "DMAC-PNT-STATIC filtering on Interlink->LRE",
        cfg: {mode: "HSR_SAN"},
        # Send to DMAC on Interlink, expect discard on LRE
        tab: [{proxy: {mac: 0xcc},
               frm: {dmac: ":cc"},
               fwd: [{idx_tx: "c"},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "DMAC-PNT filtering on LRE->LRE",
        cfg: {mode: "HSR_SAN"},
        tab: [
            # Learn SMAC in PNT (and on switch port C)
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d"}]},
            # Send to DMAC on LRE, expect discard on LRE
            {frm: {dmac: ":cc"},
             fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "c"}]}
        ]
    },
    {
        txt: "DMAC-PNT-STATIC filtering on LRE->LRE",
        cfg: {mode: "HSR_SAN"},
        # Send to DMAC on LRE, expect discard on LRE
        tab: [{proxy: {mac: 0xcc},
               frm: {dmac: ":cc"},
               fwd: [{idx_tx: "b", hsr: {}},
                     {idx_rx: "c"},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "SMAC-PNT filtering/ageing on LRE->interlink",
        cfg: {mode: "HSR_SAN", pnt_age_time: 20},
        tab: [
            # Learn SMAC in PNT
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d"}],
             wait: 10},
            # Send from SMAC on LRE, expect discard on Interlink
            {proxy: {mac: 0xcc, cmd: "get", cnt: 1},
             frm: {smac: ":cc"},
             fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}}],
             wait: 10},
            # Send from SMAC on LRE, expect forward on Interlink
            {proxy: {mac: 0xcc, cmd: "get", err: true},
             frm: {smac: ":cc"},
             fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "c"},
                   {idx_rx: "d"}]}
        ],
        # Expect own counter on port A
        cnt: [{port: "port_a", name: "rx_own", val: 1}]
    },
    {
        txt: "SMAC-PNT-STATIC filtering on LRE->interlink",
        cfg: {mode: "HSR_SAN"},
        # Send from SMAC on LRE, expect discard on Interlink
        tab: [{proxy: {mac: 0xcc},
               frm: {smac: ":cc"},
               fwd: [{idx_tx: "b", hsr: {}},
                     {idx_rx: "a", hsr: {}}]}],
        # Expect own counter on port B
        cnt: [{port: "port_b", name: "rx_own", val: 1}]
    },
    {
        txt: "DMAC-NT-STATIC filtering on LRE->interlink",
        cfg: {mode: "HSR_SAN"},
        tab: [{node: {mac: 0xbb},
               frm: {dmac: ":bb"},
               fwd: [{idx_tx: "a", hsr:{}},
                     {idx_rx: "b", hsr: {}}]}]
    },
    {
        txt: "NT operations",
        cfg: {mode: "HSR_SAN"},
        tab: [{node: {mac: 0xbb}},
              {node: {mac: 0xbb, cmd: "get"}},
              {node: {mac: 0xba, cmd: "get", err: true}},
              {node: {mac: 0xba, cmd: "get_next", mac_next: 0xbb}},
              {node: {mac: 0xbb, cmd: "get_next", err: true}},
              {node: {mac: 0xbb, cmd: "del"}},
              {node: {mac: 0xbb, cmd: "get", err: true}},
              {node: {mac: 0x00, cmd: "get_next", err: true}}]
    },
    {
        txt: "PNT operations",
        cfg: {mode: "HSR_SAN"},
        tab: [{proxy: {mac: 0xcc}},
              {proxy: {mac: 0xcc, cmd: "get"}},
              {proxy: {mac: 0xcb, cmd: "get", err: true}},
              {proxy: {mac: 0xcb, cmd: "get_next", mac_next: 0xcc}},
              {proxy: {mac: 0xcc, cmd: "get_next", err: true}},
              {proxy: {mac: 0xcc, cmd: "del"}},
              {proxy: {mac: 0xcc, cmd: "get", err: true}},
              {proxy: {mac: 0x00, cmd: "get_next", err: true}}]
    },
    {
        txt: "BPDU Rx on LRE",
        cfg: {mode: "HSR_SAN", npi: "d", bpdu_queue: 2},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: "a"},
                     {idx_rx: "d", ifh_rx: "a"}]}],
        # Expect zero counters
        cnt: [
            {port: "port_c", name: "tx", val: 0},
            {port: "port_c", name: "tx_dupl_zero", val: 0}
        ]
    },
    {
        txt: "BPDU Tx to LREs",
        cfg: {mode: "HSR_SAN", npi: "d"},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: "d", ifh_tx: "a", rb_tag_dis: true},
                     {idx_rx: "a"},
                     {idx_rx: "b"}]}],
        # Expect zero counter
        cnt: [{port: "port_c", name: "rx", val: 0}]
    },
    {
        txt: "Supervision Rx on LRE",
        cfg: {mode: "HSR_SAN", sv: "CPU_ONLY", npi: "d", sv_queue: 3},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "d", hsr: {}, ifh_rx: "a"}]}]
    },
    {
        txt: "Supervision Discard on LRE",
        cfg: {mode: "HSR_SAN", sv: "DISCARD"},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}}]}]
    },
    {
        txt: "Supervision Tx to LREs",
        cfg: {mode: "HSR_SAN", npi: "d"},
        tab: [{frm: {dmac: "01:15:4e:00:01:00"},
               fwd: [{idx_tx: "d", ifh_tx: "a"},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}}]}]
    },
    {
        txt: "port A/B duplicate discard towards port A/B/C/D",
        cfg: {mode: "HSR_SAN", dd_age_time: 20000},
        tab: [
            # Forward and learn default sequence number
            {frm: {smac: ":ab"},
             fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "c"},
                   {idx_rx: "d"}],
             wait: 10},
            # Discard default sequence number from port A to port B/C
            {frm: {smac: ":ab"},
             fwd: [{idx_tx: "a", hsr: {}}]},
            # Discard default sequence number from port B to port C
            {frm: {smac: ":ab"},
             fwd: [{idx_tx: "b", hsr: {}},
                   {idx_rx: "a", hsr: {}}]},
            # Discard default sequence number from port B to port A/C
            {frm: {smac: ":ab"},
             fwd: [{idx_tx: "b", hsr: {}}]},
            # Forward another sequence number
            {frm: {smac: ":ab"},
             fwd: [{idx_tx: "a", hsr: {seqn: 2}},
                   {idx_rx: "b", hsr: {seqn: 2}},
                   {idx_rx: "c"},
                   {idx_rx: "d"}],
             wait: 10},
            # Forward default sequence number again after timeout
            {frm: {smac: ":ab"},
             fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "c"},
                   {idx_rx: "d"}]},
        ],
        # Expect duplicate counters on port A/B/C
        cnt: [
            {port: "port_a", name: "tx_dupl_zero", val: 0},
            {port: "port_a", name: "tx_dupl_one", val: 1},
            {port: "port_b", name: "tx_dupl_zero", val: 0},
            {port: "port_b", name: "tx_dupl_one", val: 1},
            {port: "port_c", name: "tx_dupl_zero", val: 0},
            {port: "port_c", name: "tx_dupl_multi", val: 1},
        ]
    },

    # PRP-SAN tests
    {
        txt: "port A to port C/D",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: "a", prp: {lan_id: 0}},
                     {idx_rx: "c"},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port A to port C/D - max-length",
        cfg: {mode: "PRP_SAN"},
        tab: [{frm: {len: 1500},
               fwd: [{idx_tx: "a", prp: {lan_id: 0}},
                     {idx_rx: "c"},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port B to port C/D - burst",
        cfg: {mode: "PRP_SAN"},
        tab: [{cnt: 10,
               fwd: [{idx_tx: "b", prp: {lan_id: 1}},
                     {idx_rx: "c"},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port C to port A/B/D",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: "c"},
                     {idx_rx: "a", prp: {lan_id: 0}},
                     {idx_rx: "b", prp: {lan_id: 1}},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port C to port A/B/D - max-length",
        cfg: {mode: "PRP_SAN"},
        tab: [{frm: {len: 1500},
               fwd: [{idx_tx: "c"},
                     {idx_rx: "a", prp: {lan_id: 0}},
                     {idx_rx: "b", prp: {lan_id: 1}},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port D to port A/B/C - burst",
        cfg: {mode: "PRP_SAN"},
        tab: [{cnt: 10,
               fwd: [{idx_tx: "d"},
                     {idx_rx: "a", prp: {lan_id: 0}},
                     {idx_rx: "b", prp: {lan_id: 1}},
                     {idx_rx: "c"}]}]
    },
    {
        txt: "port D to port A/B/C - repeated burst",
        cfg: {mode: "PRP_SAN"},
        tab: [{rep: 1000,
               fwd: [{idx_tx: "d"},
                     {idx_rx: "a"},
                     {idx_rx: "b"},
                     {idx_rx: "c"}]}]
    },
    {
        txt: "port A wrong LAN",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: "a", prp: {lan_id: 1}},
                     {idx_rx: "c", prp: {lan_id: 1}},
                     {idx_rx: "d", prp: {lan_id: 1}}]},
              {node: {mac: 0x0a, cmd: "get",
                      cnt: [{port: "a", name: "rx", val: 1},
                            {port: "a", name: "rx_wrong_lan", val: 1}]}}],
        cnt: [{port: "port_a", name: "rx_wrong_lan", val: 1}]
    },
    {
        txt: "port B wrong LAN",
        cfg: {mode: "PRP_SAN"},
        tab: [{fwd: [{idx_tx: "b", prp: {}},
                     {idx_rx: "c", prp: {}},
                     {idx_rx: "d", prp: {}}]},
              {node: {mac: 0x0b, cmd: "get",
                      cnt: [{port: "b", name: "rx", val: 1},
                            {port: "b", name: "rx_wrong_lan", val: 1}]}}],
        cnt: [{port: "port_b", name: "rx_wrong_lan", val: 1}]
    },
    {
        txt: "forward to SAN on port A",
        cfg: {mode: "PRP_SAN", nt_age_time: 20},
        tab: [
            # Learn SAN on port A
            {frm: {smac: ":aa"},
             fwd: [{idx_tx: "a"},
                   {idx_rx: "c"},
                   {idx_rx: "d"}],
             wait: 10},
            # Forward to SAN on port A
            {frm: {dmac: ":aa"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a"}],
             wait: 10},
            # Node timeout, forward to SAN on port A/B
            {frm: {dmac: ":aa"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a", prp: {lan_id: 0}},
                   {idx_rx: "b", prp: {lan_id: 1}}]},
        ]
    },
    {
        txt: "forward to SAN on port B",
        cfg: {mode: "PRP_SAN", nt_age_time: 20},
        tab: [
            # Learn SAN on port B
            {frm: {smac: ":bb"},
             fwd: [{idx_tx: "b"},
                   {idx_rx: "c"},
                   {idx_rx: "d"}],
             wait: 10},
            # Forward to SAN on port B
            {node: {mac: 0xbb, cmd: "get", cnt: [{port: "b", name: "rx", val: 1}]},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a"}],
             wait: 10},
            # Node timeout, forward to SAN on port A/B
            {node: {mac: 0xbb, cmd: "get", err: true},
             frm: {dmac: ":bb"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a", prp: {lan_id: 0}},
                   {idx_rx: "b", prp: {lan_id: 1}}]},
        ]
    },
    {
        txt: "BPDU Rx on LRE",
        cfg: {mode: "PRP_SAN", npi: "d", bpdu_queue: 2},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: "a"},
                     {idx_rx: "d", ifh_rx: "a"}]}],
        # Expect zero counters
        cnt: [
            {port: "port_c", name: "tx", val: 0},
            {port: "port_c", name: "tx_dupl_zero", val: 0}
        ]

    },
    {
        txt: "BPDU Tx to LREs",
        cfg: {mode: "PRP_SAN", npi: "d"},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: "d", ifh_tx: "a", rb_tag_dis: true},
                     {idx_rx: "a"},
                     {idx_rx: "b"}]}],
        # Expect zero counter
        cnt: [{port: "port_c", name: "rx", val: 0}]
    },
    {
        txt: "Supervision Rx on LRE",
        cfg: {mode: "PRP_SAN", sv: "CPU_ONLY", npi: "d", sv_queue: 3},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: "a", prp: {}},
                     {idx_rx: "d", prp: {}, ifh_rx: "a"}]}]
    },
    {
        txt: "Supervision Tx to LREs",
        cfg: {mode: "PRP_SAN", npi: "d"},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: "d", ifh_tx: "a"},
                     {idx_rx: "a", prp: {}},
                     {idx_rx: "b", prp: {lan_id: 1}}]}]
    },
    {
        txt: "port A duplicate discard towards port C/D",
        cfg: {mode: "PRP_SAN", dd_age_time: 20000},
        tab: [
            # Forward and learn default sequence number
            {fwd: [{idx_tx: "a", prp: {}},
                   {idx_rx: "c"},
                   {idx_rx: "d"}],
             wait: 10},
            # Discard default sequence number
            {fwd: [{idx_tx: "a", prp: {}}]},
            # Discard default sequence number again
            {fwd: [{idx_tx: "a", prp: {}}]},
            # Forward another sequence number
            {fwd: [{idx_tx: "a", prp: {seqn: 2}},
                   {idx_rx: "c"},
                   {idx_rx: "d"}],
             wait: 10},
            # Forward default sequence number again after timeout
            {fwd: [{idx_tx: "a", prp: {}},
                   {idx_rx: "c"},
                   {idx_rx: "d"}]},
        ],
        # Expect multiple duplicate counters on port C
        cnt: [
            {port: "port_c", name: "tx_dupl_zero", val: 0},
            {port: "port_c", name: "tx_dupl_multi", val: 1},
        ]
    },

    # HSR-PRP tests
    {
        txt: "port A to port B/C/D",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "c", prp: {}},
                     {idx_rx: "d", prp: {}}]}]
    },
    {
        txt: "port A to port B/C/D - max-length",
        cfg: {mode: "HSR_PRP"},
        tab: [{frm: {len: 1500},
               fwd: [{idx_tx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "c", prp: {}},
                     {idx_rx: "d", prp: {}}]}]
    },
    {
        txt: "port B to port A/C/D - burst",
        cfg: {mode: "HSR_PRP"},
        tab: [{cnt: 20,
               fwd: [{idx_tx: "b", hsr: {}},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "c", prp: {}},
                     {idx_rx: "d", prp: {}}]}]
    },
    {
        txt: "port C to port A/B/D",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: "c", prp: {}},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "d", prp: {}}]}]
    },
    {
        txt: "port C to port A/B/D - max-length",
        cfg: {mode: "HSR_PRP"},
        tab: [{frm: {len: 1500},
               fwd: [{idx_tx: "c", prp: {}},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "d", prp: {}}]}]
    },
    {
        txt: "port D to port A/B/C - burst",
        cfg: {mode: "HSR_PRP"},
        tab: [{cnt: 10,
               fwd: [{idx_tx: "d", prp: {}},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "c", prp: {}}]}]
    },
    {
        txt: "port C to port A/B/D - untagged",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: "c"},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "d"}]}]
    },
    {
        txt: "port D to port A/B/C - untagged burst",
        cfg: {mode: "HSR_PRP"},
        tab: [{cnt: 10,
               fwd: [{idx_tx: "d"},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "c"}]}]
    },
    {
        txt: "port D to port A/B/C - untagged repeated burst",
        cfg: {mode: "HSR_PRP"},
        tab: [{rep: 1000,
               fwd: [{idx_tx: "d"},
                     {idx_rx: "a"},
                     {idx_rx: "b"},
                     {idx_rx: "c"}]}]
    },
    {
        txt: "discard HSR-tagged on Interlink",
        cfg: {mode: "HSR_PRP"},
        tab: [{fwd: [{idx_tx: "c", hsr: {}},
                     {idx_rx: "d", hsr: {}}]}]
    },
    {
        txt: "redirect non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_PRP", npi: "d", non_hsr_queue: 1},
        tab: [{fwd: [{idx_tx: "a"},
                     {idx_rx: "d", ifh_rx: "a"}]}],
        # Expect zero counters
        cnt: [
            {port: "port_c", name: "tx", val: 0},
            {port: "port_c", name: "tx_dupl_zero", val: 0}
        ]
    },
    {
        txt: "DMAC-PNT filtering on Interlink->LRE",
        cfg: {mode: "HSR_PRP"},
        tab: [
            # Learn SMAC in PNT and flush switch port
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d"}],
             flush: "c"},
            # Send to DMAC on Interlink, expect discard on LRE
            {frm: {dmac: ":cc"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "d"}]}
        ]
    },
    {
        txt: "DMAC-PNT filtering on LRE->LRE",
        cfg: {mode: "HSR_PRP"},
        tab: [
            # Learn SMAC in PNT (and on switch port C)
            {frm: {smac: ":cc"},
             fwd: [{idx_tx: "c"},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d"}]},
            # Send to DMAC on LRE, expect discard on LRE
            {frm: {dmac: :":cc"},
             fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "c", prp: {}}]}
        ]
    },
    {
        txt: "DMAC-NT-STATIC filtering on LRE->interlink",
        cfg: {mode: "HSR_PRP"},
        tab: [{node: {mac: 0xbb},
               frm: {dmac: ":bb"},
               fwd: [{idx_tx: "a", hsr:{}},
                     {idx_rx: "b", hsr: {}}]}]
    },
    {
        txt: "BPDU Rx on LRE",
        cfg: {mode: "HSR_PRP", npi: "d", bpdu_queue: 2},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: "a"},
                     {idx_rx: "d", ifh_rx: "a"}]}],
        # Expect zero counters
        cnt: [
            {port: "port_c", name: "tx", val: 0},
            {port: "port_c", name: "tx_dupl_zero", val: 0}
        ]

    },
    {
        txt: "BPDU Tx to LREs",
        cfg: {mode: "HSR_PRP", npi: "d"},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: "d", ifh_tx: "a", rb_tag_dis: true},
                     {idx_rx: "a"},
                     {idx_rx: "b"}]}],
        # Expect zero counter
        cnt: [{port: "port_c", name: "rx", val: 0}]
    },
    {
        txt: "Supervision Rx on LRE",
        cfg: {mode: "HSR_PRP", sv: "CPU_COPY", npi: "d", sv_queue: 3},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "c", prp: {}},
                     {idx_rx: "d", prp: {}, ifh_rx: "a"}]}]
    },
    {
        txt: "Supervision Tx to LREs",
        cfg: {mode: "HSR_PRP", npi: "d"},
        tab: [{frm: {dmac: "01:15:4e:00:01:00"},
               fwd: [{idx_tx: "d", ifh_tx: "a"},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}}]}]
    },
    {
        txt: "port A duplicate discard towards port B/C/D",
        cfg: {mode: "HSR_PRP", dd_age_time: 20000},
        tab: [
            # Forward and learn default sequence number
            {fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "c", prp: {}},
                   {idx_rx: "d", prp: {}}],
             wait: 10},
            # Discard default sequence number from port A to port B/C
            {fwd: [{idx_tx: "a", hsr: {}}]},
            # Forward another sequence number
            {fwd: [{idx_tx: "a", hsr: {seqn: 2}},
                   {idx_rx: "b", hsr: {seqn: 2}},
                   {idx_rx: "c", prp: {seqn: 2}},
                   {idx_rx: "d", prp: {seqn: 2}}],
             wait: 10},
            # Forward default sequence number again after timeout
            {fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "c", prp: {}},
                   {idx_rx: "d", prp: {}}]},
        ],
        # Expect duplicate counters on port B/C
        cnt: [
            {port: "port_b", name: "tx_dupl_zero", val: 0},
            {port: "port_b", name: "tx_dupl_one", val: 1},
            {port: "port_c", name: "tx_dupl_zero", val: 0},
            {port: "port_c", name: "tx_dupl_one", val: 1},
        ]
    },
    {
        txt: "port C duplicate discard towards port A/B",
        cfg: {mode: "HSR_PRP", dd_age_time: 20000},
        tab: [
            # Forward and learn default sequence number
            {fwd: [{idx_tx: "c", prp: {}},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d", prp: {}}],
             wait: 10},
            # Discard default sequence number from port C to port A/B
            {fwd: [{idx_tx: "c", prp: {}},
                   {idx_rx: "d", prp: {}}]},
            # Forward another sequence number
            {fwd: [{idx_tx: "c", prp: {seqn: 2}},
                   {idx_rx: "a", hsr: {seqn: 2}},
                   {idx_rx: "b", hsr: {seqn: 2}},
                   {idx_rx: "d", prp: {seqn: 2}}],
             wait: 10},
            # Forward default sequence number again after timeout
            {fwd: [{idx_tx: "c", prp: {}},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d", prp: {}}]},
        ],
        # Expect duplicate counters on port A/B
        cnt: [
            {port: "port_a", name: "tx_dupl_zero", val: 0},
            {port: "port_a", name: "tx_dupl_one", val: 1},
            {port: "port_b", name: "tx_dupl_zero", val: 0},
            {port: "port_b", name: "tx_dupl_one", val: 1},
        ]
    },

    # HSR-HSR tests
    {
        txt: "port A to port B/C/D",
        cfg: {mode: "HSR_HSR"},
        tab: [{fwd: [{idx_tx: "a", hsr: {net_id: 3}},
                     {idx_rx: "b", hsr: {net_id: 3}},
                     {idx_rx: "c", hsr: {net_id: 3}},
                     {idx_rx: "d", hsr: {net_id: 3}}]}]
    },
    {
        txt: "port A to port B/C/D - max-length",
        cfg: {mode: "HSR_HSR"},
        tab: [{frm: {len: 1500},
               fwd: [{idx_tx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "c", hsr: {}},
                     {idx_rx: "d", hsr: {}}]}]
    },
    {
        txt: "port C to port A/B/D",
        cfg: {mode: "HSR_HSR"},
        tab: [{fwd: [{idx_tx: "c", hsr: {net_id: 3}},
                     {idx_rx: "a", hsr: {net_id: 3}},
                     {idx_rx: "b", hsr: {net_id: 3}},
                     {idx_rx: "d", hsr: {net_id: 3}}]}]
    },
    {
        txt: "port C to port A/B/D - max-length",
        cfg: {mode: "HSR_HSR"},
        tab: [{frm: {len: 1500},
               fwd: [{idx_tx: "c", hsr: {}},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "d", hsr: {}}]}]
    },
    {
        txt: "redirect non-HSR-tagged on LRE ports",
        cfg: {mode: "HSR_HSR", npi: "d", non_hsr_queue: 1},
        tab: [{fwd: [{idx_tx: "a"},
                     {idx_rx: "d", ifh_rx: "a"}]}],
        # Expect zero counters
        cnt: [
            {port: "port_c", name: "tx", val: 0},
            {port: "port_c", name: "tx_dupl_zero", val: 0}
        ]
    },
    {
        txt: "DMAC-NT-STATIC filtering on LRE->interlink",
        cfg: {mode: "HSR_HSR"},
        tab: [{node: {mac: 0xbb},
               frm: {dmac: ":bb"},
               fwd: [{idx_tx: "a", hsr:{}},
                     {idx_rx: "b", hsr: {}}]}]
    },
    {
        txt: "NetId filtering/translation",
        cfg: {mode: "HSR_HSR", net_id: 4},
        tab: [
            # NetId 3 forwarded to Interlink
            {fwd: [{idx_tx: "a", hsr: {net_id: 3}},
                   {idx_rx: "b", hsr: {net_id: 3}},
                   {idx_rx: "c", hsr: {net_id: 3}},
                   {idx_rx: "d", hsr: {net_id: 3}}]},
            # NetId 4 not forwarded to Interlink
            {fwd: [{idx_tx: "a", hsr: {net_id: 4}},
                   {idx_rx: "b", hsr: {net_id: 4}}]},
            # NetId 3 translated to 4 from Interlink
            {fwd: [{idx_tx: "c", hsr: {net_id: 3}},
                   {idx_rx: "a", hsr: {net_id: 4}},
                   {idx_rx: "b", hsr: {net_id: 4}},
                   {idx_rx: "d", hsr: {net_id: 3}}]},
            # NetId 4 translated to 4 from Interlink
            {fwd: [{idx_tx: "c", hsr: {net_id: 4}},
                   {idx_rx: "a", hsr: {net_id: 4}},
                   {idx_rx: "b", hsr: {net_id: 4}},
                   {idx_rx: "d", hsr: {net_id: 4}}]},
            # NetId 0 translated to 4 from Interlink
            {fwd: [{idx_tx: "c", hsr: {}},
                   {idx_rx: "a", hsr: {net_id: 4}},
                   {idx_rx: "b", hsr: {net_id: 4}},
                   {idx_rx: "d", hsr: {}}]},
        ]
    },
    {
        txt: "BPDU Rx on LRE",
        cfg: {mode: "HSR_HSR", npi: "d", bpdu_queue: 2},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: "a"},
                     {idx_rx: "d", ifh_rx: "a"}]}],
        # Expect zero counters
        cnt: [
            {port: "port_c", name: "tx", val: 0},
            {port: "port_c", name: "tx_dupl_zero", val: 0}
        ]
    },
    {
        txt: "BPDU Tx to LREs",
        cfg: {mode: "HSR_HSR", npi: "d"},
        tab: [{frm: {dmac: "01:80:c2:00:00:00"},
               fwd: [{idx_tx: "d", ifh_tx: "a", rb_tag_dis: true},
                     {idx_rx: "a"},
                     {idx_rx: "b"}]}],
        # Expect zero counter
        cnt: [{port: "port_c", name: "rx", val: 0}]
    },
    {
        txt: "Supervision Rx on LRE",
        cfg: {mode: "HSR_HSR", sv: "CPU_ONLY", npi: "d", sv_queue: 3},
        tab: [{frm: {dmac: "01:15:4e:00:01:00", et: 0x88fb},
               fwd: [{idx_tx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}},
                     {idx_rx: "d", hsr: {}, ifh_rx: "a"}]}]
    },
    {
        txt: "Supervision Tx to LREs",
        cfg: {mode: "HSR_HSR", npi: "d"},
        tab: [{frm: {dmac: "01:15:4e:00:01:00"},
               fwd: [{idx_tx: "d", hsr: {}, ifh_tx: "a"},
                     {idx_rx: "a", hsr: {}},
                     {idx_rx: "b", hsr: {}}]}]
    },
    {
        txt: "port A duplicate discard towards port B/C/D",
        cfg: {mode: "HSR_HSR", dd_age_time: 20000},
        tab: [
            # Forward and learn default sequence number
            {fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "c", hsr: {}},
                   {idx_rx: "d", hsr: {}}],
             wait: 10},
            # Discard default sequence number from port A to port B/C
            {fwd: [{idx_tx: "a", hsr: {}}]},
            # Forward another sequence number
            {fwd: [{idx_tx: "a", hsr: {seqn: 2}},
                   {idx_rx: "b", hsr: {seqn: 2}},
                   {idx_rx: "c", hsr: {seqn: 2}},
                   {idx_rx: "d", hsr: {seqn: 2}}],
             wait: 10},
            # Forward default sequence number again after timeout
            {fwd: [{idx_tx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "c", hsr: {}},
                   {idx_rx: "d", hsr: {}}]},
        ],
        # Expect duplicate counters on port B/C
        cnt: [
            {port: "port_b", name: "tx_dupl_zero", val: 0},
            {port: "port_b", name: "tx_dupl_one", val: 1},
            {port: "port_c", name: "tx_dupl_zero", val: 0},
            {port: "port_c", name: "tx_dupl_one", val: 1},
        ]
    },
    {
        txt: "port C duplicate discard towards port A/B",
        cfg: {mode: "HSR_HSR", dd_age_time: 20000},
        tab: [
            # Forward and learn default sequence number
            {fwd: [{idx_tx: "c", hsr: {}},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d", hsr: {}}],
             wait: 10},
            # Discard default sequence number from port C to port A/B
            {fwd: [{idx_tx: "c", hsr: {}},
                   {idx_rx: "d", hsr: {}}]},
            # Forward another sequence number
            {fwd: [{idx_tx: "c", hsr: {seqn: 2}},
                   {idx_rx: "a", hsr: {seqn: 2}},
                   {idx_rx: "b", hsr: {seqn: 2}},
                   {idx_rx: "d", hsr: {seqn: 2}}],
             wait: 10},
            # Forward default sequence number again after timeout
            {fwd: [{idx_tx: "c", hsr: {}},
                   {idx_rx: "a", hsr: {}},
                   {idx_rx: "b", hsr: {}},
                   {idx_rx: "d", hsr: {}}]},
        ],
        # Expect duplicate counters on port A/B
        cnt: [
            {port: "port_a", name: "tx_dupl_zero", val: 0},
            {port: "port_a", name: "tx_dupl_one", val: 1},
            {port: "port_b", name: "tx_dupl_zero", val: 0},
            {port: "port_b", name: "tx_dupl_one", val: 1},
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

def queue_set(cfg, conf, name, fld)
    q = fld_get(cfg, fld, nil)
    if (q != nil)
        conf["queue"][q]["npi"]["enable"] = true
    end
    conf["map"][name] = (q == nil ? 0 : q)
end

def rb_idx(name)
    idx = (name == "a" ? $rb[:idx_a] :
               name == "b" ? $rb[:idx_b] :
                   name == "c" ? $rb[:idx_c] : $rb[:idx_d])
end

# Frame test
def rb_frame_test(entry, exp, dupl_incr, index)
    cmd = "sudo ef"
    cmd_add = ""
    idx_list = []
    idx_tx = nil
    idx_tx_name = nil
    smac = "01"
    f = fld_get(entry, :frm, {})
    et = fld_get(f, :et, 0xeeee)
    len = fld_get(f, :len, 46)
    fwd = fld_get(entry, :fwd, [])
    rep = fld_get(entry, :rep, 1)
    port_c_done = false
    fwd.each_with_index do |e, i|
        idx_name = e[:idx_tx]
        dir = "rx"
        if (idx_name == nil)
            idx_name = e[:idx_rx]
        else
            smac = fld_get(f, :smac, ":0#{idx_name}")
            dir = "tx"
            idx_tx_name = idx_name
            idx_tx = rb_idx(idx_name)
        end
        name = " name f_#{idx_name}"
        idx = rb_idx(idx_name)
        idx_list.push(idx)
        if (index > 0)
            name += "_#{index + 1}"
        end
        if (rep == 1 or dir == "tx")
            cmd_add += " #{dir} #{$ts.pc.p[idx]}"
            if (rep > 1)
                cmd_add += " rep #{rep}"
            end
            cmd_add += name
            cmd += name
            ifh_rx = fld_get(e, :ifh_rx, nil)
            if (ifh_rx != nil)
                ifh_rx = rb_idx(ifh_rx)
                cmd += (" " + cmd_rx_ifh_push({port_idx: ifh_rx}))
            end
            ifh_tx = fld_get(e, :ifh_tx, nil)
            if (ifh_tx != nil)
                info = {}
                ifh_tx = rb_idx(ifh_tx)
                info[:dst_port] = $ts.dut.p[ifh_tx]
                rb_tag_dis = fld_get(e, :rb_tag_dis, false)
                info[:rb_tag_disable] = rb_tag_dis
                info[:rb_dd_disable] = rb_tag_dis
                cmd += (" " + cmd_tx_ifh_push(info))
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
                cmd += " htag pathid #{path_id} size #{size} seqn #{seqn + index}"
            end
            cmd += " et 0x#{et.to_s(16)} data repeat #{len} 0xff"
            prp = fld_get(e, :prp, nil)
            if (prp != nil)
                seqn = fld_get(prp, :seqn, 1)
                net_id = fld_get(prp, :net_id, 5)
                lan_id = fld_get(prp, :lan_id, 0)
                path_id = ((net_id << 1) + lan_id)
                size = fld_get(prp, :size, len + 6)
                cmd += " prp seqn #{seqn + index} lanid #{path_id} size #{size}"
            end
        end

        # Update expected counters
        cnt = rep
        case idx_name
        when "a", "b"
            # Do not count untagged frames on port A/B
            if (cnt == 1 and prp == nil and hsr == nil)
                cnt = 0
            end
        else
            # Count RedBox port C for switch port C/D
            idx_name = "c"
            if (port_c_done)
                cnt = 0
            else
                port_c_done = true
            end
        end
        port_name = ("port_" + idx_name)
        if (dir == "tx")
            cnt_incr(exp, port_name, "rx", cnt)
        else
            cnt_incr(exp, port_name, "tx", cnt)
            cnt_incr(exp, port_name, "tx_dupl_zero", cnt * dupl_incr)
        end
    end
    cmd += cmd_add
    $ts.dut.p.each_index do |idx|
        if (!idx_list.include?idx)
            cmd += " rx #{$ts.pc.p[idx]}"
        end
    end
    if (idx_tx != nil)
        $ts.pc.try(cmd)
    end

    flush_idx = fld_get(entry, :flush, nil)
    if (flush_idx != nil)
        # Flush switch core port
        flush_idx = rb_idx(flush_idx)
        $ts.dut.call("mesa_mac_table_port_flush", $ts.dut.p[flush_idx])
    end

    wait = fld_get(entry, :wait)
    if (wait > 0)
        # Wait a number of seconds
        sleep(wait)
    end
end

def check_mac(name, val, exp)
    v = mac_to_txt(val["addr"])
    e = mac_to_txt(exp[:addr])
    msg = "#{name}: #{v}, expected: #{e}"
    if (v == e)
        t_i(msg)
    else
        t_e(msg)
    end
end

def redbox_test(t)
    cfg = t[:cfg]

    # Disable the previous RedBox configuration, if needed
    rb_id = $rb[:rb_id]
    if (rb_id != $rb_id and $rb_id != nil)
        conf = $ts.dut.call("mesa_rb_conf_get", $rb_id)
        conf["mode"] = "MESA_RB_MODE_DISABLED"
        $ts.dut.call("mesa_rb_conf_set", $rb_id, conf)
    end
    $rb_id = rb_id

    # RedBox configuration
    mode = fld_get(cfg, :mode, "DISABLED")
    conf = $ts.dut.call("mesa_rb_conf_get", rb_id)
    conf["mode"] = ("MESA_RB_MODE_" + mode)
    conf["port_a"] = $ts.dut.p[$rb[:idx_a]]
    conf["port_b"] = $ts.dut.p[$rb[:idx_b]]
    conf["net_id"] = fld_get(cfg, :net_id)
    conf["lan_id"] = fld_get(cfg, :lan_id)
    conf["nt_age_time"] = fld_get(cfg, :nt_age_time)
    conf["pnt_age_time"] = fld_get(cfg, :pnt_age_time)
    conf["sv"] = ("MESA_RB_SV_" + fld_get(cfg, :sv, "FORWARD"))
    dd_age_time = fld_get(cfg, :dd_age_time)
    if (conf["dd_age_time"] > 1000 and dd_age_time > 1000)
        # Briefly use minimum age to flush DD table from previous test
        conf["dd_age_time"] = 1
        $ts.dut.call("mesa_rb_conf_set", rb_id, conf)
    end
    conf["dd_age_time"] = dd_age_time
    $ts.dut.call("mesa_rb_conf_set", rb_id, conf)

    # Remove nodes and proxy nodes from previous tests
    $ts.dut.call("mesa_rb_node_table_clear", rb_id, "MESA_RB_CLEAR_ALL")
    $ts.dut.call("mesa_rb_proxy_node_table_clear", rb_id, "MESA_RB_CLEAR_ALL")

    # Flush MAC addresses learned previously
    $ts.dut.call("mesa_mac_table_flush")

    # VLAN configuration
    vlan = fld_get(cfg, :vlan, nil)
    vlan_idx_list = []
    if (vlan != nil)
        vid = fld_get(vlan, :vid)
        list = fld_get(vlan, :list, [])
        list.each do |e|
            idx = rb_idx(fld_get(e, :idx))
            vlan_idx_list.push(idx)
            vlan_port_conf_set(idx, e)
        end
        $ts.dut.call("mesa_vlan_port_members_set", vid, port_idx_list_str(vlan_idx_list))
    end

    # NPI port
    idx_npi = fld_get(cfg, :npi, nil)
    if (idx_npi != nil)
        # Map one CPU queue to NPI port
        idx_npi = rb_idx(idx_npi)
        conf = $ts.dut.call("mesa_packet_rx_conf_get")
        8.times do |q|
            conf["queue"][q]["npi"]["enable"] = false
        end
        queue_set(cfg, conf, "bpdu_queue", :bpdu_queue)
        queue_set(cfg, conf, "sv_queue", :sv_queue)
        queue_set(cfg, conf, "non_hsr_queue", :non_hsr_queue)
        $ts.dut.call("mesa_packet_rx_conf_set", conf)

        # Enable NPI port
        conf = $ts.dut.call("mesa_npi_conf_get")
        conf["enable"] = true
        conf["port_no"] = $ts.dut.p[idx_npi]
        $ts.dut.call("mesa_npi_conf_set", conf)
    end

    # Disable port
    idx_dis = fld_get(cfg, :idx_dis, nil)
    if (idx_dis != nil)
        idx_dis = rb_idx(idx_dis)
        $ts.dut.run("mesa-cmd port state #{$ts.dut.p[idx_dis] + 1} disable")
        sleep(5)
    end

    # Clear counters
    $ts.dut.call("mesa_rb_counters_clear", rb_id)
    exp = $ts.dut.call("mesa_rb_counters_get", rb_id)

    # Frame test
    tab = fld_get(t, :tab, [])
    tab.each do |entry|
        # Node entry
        node = fld_get(entry, :node, nil)
        if (node != nil)
            mac = fld_get(node, :mac, 0xee)
            mac = {addr: [0,0,0,0,0,mac]}
            type = ("MESA_RB_NODE_TYPE_" + fld_get(node, :type, "DAN"))
            san_a = fld_get(node, :san_a, false)
            conf = {type: type, san_a: san_a}
            cmd = fld_get(node, :cmd, "add")
            cnt = fld_get(node, :cnt, [])
            err = fld_get(node, :err, false)
            if (cmd == "add")
                $ts.dut.call("mesa_rb_node_add", rb_id, mac, conf)
            elsif (cmd == "del")
                $ts.dut.call("mesa_rb_node_del", rb_id, mac)
            elsif (cmd == "get")
                if (err)
                    $ts.dut.try_err("mesa_rb_node_get", rb_id, mac)
                else
                    e = $ts.dut.try("mesa_rb_node_get", rb_id, mac)
                    if (e != nil)
                        check_mac("node_get", e["mac"], mac)
                    end
                    ["a", "b"].each do |port_name|
                        ["rx", "rx_wrong_lan"].each do |cnt_name|
                            x = 0
                            cnt.each do |c|
                                if (c[:port] == port_name and c[:name] == cnt_name)
                                    x = c[:val]
                                end
                            end
                            pname = ("port_" + port_name)
                            name = "#{pname}[#{cnt_name}]"
                            check_counter(name, e[pname]["cnt"][cnt_name], x)
                        end
                    end
                end
            elsif (cmd == "get_next")
                if (err)
                    $ts.dut.try_err("mesa_rb_node_get_next", rb_id, mac)
                else
                    e = $ts.dut.try("mesa_rb_node_get_next", rb_id, mac)
                    if (e != nil)
                        mac_next = fld_get(node, :mac_next, 0xee)
                        mac_next = {addr: [0,0,0,0,0,mac_next]}
                        check_mac("node_get_next", e["mac"], mac_next)
                    end
                end
            end
        end

        # Proxy Node entry
        proxy = fld_get(entry, :proxy, nil)
        if (proxy != nil)
            mac = fld_get(proxy, :mac, 0xee)
            mac = {addr: [0,0,0,0,0,mac]}
            cmd = fld_get(proxy, :cmd, "add")
            err = fld_get(proxy, :err, false)
            if (cmd == "add")
                $ts.dut.call("mesa_rb_proxy_node_add", rb_id, mac)
            elsif (cmd == "del")
                $ts.dut.call("mesa_rb_proxy_node_del", rb_id, mac)
            elsif (cmd == "get")
                if (err)
                    $ts.dut.try_err("mesa_rb_proxy_node_get", rb_id, mac)
                else
                    e = $ts.dut.try("mesa_rb_proxy_node_get", rb_id, mac)
                    if (e != nil)
                        check_mac("proxy_node_get", e["mac"], mac)
                    end
                    x = fld_get(proxy, :cnt)
                    check_counter("rx", e["cnt"]["rx"], x)
                end
            elsif (cmd == "get_next")
                if (err)
                    $ts.dut.try_err("mesa_rb_proxy_node_get_next", rb_id, mac)
                else
                    e = $ts.dut.try("mesa_rb_proxy_node_get_next", rb_id, mac)
                    if (e != nil)
                        mac_next = fld_get(proxy, :mac_next, 0xee)
                        mac_next = {addr: [0,0,0,0,0,mac_next]}
                        check_mac("proxy_node_get_next", e["mac"], mac_next)
                    end
                end
            end
        end

        cnt = fld_get(entry, :cnt, 1)
        cnt.times do |index|
            rb_frame_test(entry, exp, dd_age_time > 1000 ? 0 : 1, index)
        end
    end

    # Check RedBox counters
    cnt = fld_get(t, :cnt, [])
    cnt.each do |c|
        # Override default expected counters
        exp[c[:port]][c[:name]] = c[:val]
    end
    cnt = $ts.dut.call("mesa_rb_counters_get", rb_id)
    ["port_a", "port_b", "port_c"].each do |port_name|
        ["tx", "rx", "rx_wrong_lan", "rx_own",
         "tx_dupl_zero", "tx_dupl_one", "tx_dupl_multi"].each do |cnt_name|
            name = "#{port_name}[#{cnt_name}]"
            check_counter(name, cnt[port_name][cnt_name], exp[port_name][cnt_name])
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

    # Enable port again
    if (idx_dis != nil)
        $ts.dut.run("mesa-cmd port state #{$ts.dut.p[idx_dis] + 1} enable")
        sleep(5)
    end
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
cnt_ok = 0
cnt_err = 0
fail_list = []
$rb_table.each_with_index do |rb, rb_idx|
    #next if rb_idx != 0
    $rb = rb
    test_table.each do |t|
        next if (t[:sel] != sel)
        txt = ("RedBox #{$rb[:rb_id]}-#{rb_idx}: " + t[:cfg][:mode] + ", " + t[:txt])
        test txt do
            ["a", "b", "c", "d"].each do |name|
                idx = rb_idx(name)
                port = $ts.dut.p[idx]
                chip_port = $ts.port_map[port]["chip_port"]
                t_i("Port #{name}: #{port}(#{chip_port}) - #{$ts.pc.p[idx]}")
            end
            err = $test_stack[-1][:cnt_err]
            redbox_test(t)
            if ($test_stack[-1][:cnt_err] == err)
                cnt_ok += 1
            else
                cnt_err += 1
                fail_list << txt
            end
        end
    end
end
t_i("Total : #{cnt_ok + cnt_err}")
t_i("Ok    : #{cnt_ok}")
t_i("Errors: #{cnt_err}")
fail_list.each do |txt|
    #t_i("Failed: " + txt)
end

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api cil redbox")
    #$ts.dut.run("mesa-cmd deb api ai vlan")
    #$ts.dut.run("mesa-cmd port stati pac")
    #$ts.dut.run("mesa-cmd mac dump")
end
