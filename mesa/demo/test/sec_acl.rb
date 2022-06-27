#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0
$idx_rx = 1
$vid_a  = 10
$vid_b  = 11

test "conf" do
    test "By default forward to one port only" do
        port = $ts.dut.port_list[$idx_tx]
        conf = $ts.dut.call("mesa_acl_port_conf_get", port)
        action = conf["action"]
        action["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
        action["port_list"] = "#{$ts.dut.port_list[$idx_rx]}"
        $ts.dut.call("mesa_acl_port_conf_set", port, conf)
    end

    test "All ports are C-ports" do
        $ts.dut.port_list.each do |port|
            conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
            conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
            $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
        end
    end
    
    test "Include all ports in VLANs" do
        port_list = $ts.dut.p.join(",")
        $ts.dut.call("mesa_vlan_port_members_set", $vid_a, port_list)
        $ts.dut.call("mesa_vlan_port_members_set", $vid_b, port_list)
    end
end

#---------- Frame testing -----------------------------------------------------

# Each entry in the test table has these items:
# 1: Text string printed during test
# 2: ACE to be configured with discard action
# 3: Frame[0] matching the ACE, must be discarded
# 4: Frame[1] not matching the ACE, must be forwarded
test_table =
    [
     {
         txt: "any/dmac",
         ace: {type: "ANY", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "et 46"},
         f_1: {dmac: "01:02:03:04:06:07", cmd: "et 46"}
     },
     {
         txt: "any/smac",
         ace: {type: "ANY", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {smac: "00:01:02:03:04:05", cmd: "et 46"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "et 46"}
     },
     {
         txt: "dmac_mc",
         ace: {type: "ANY", dmac_mc: 1},
         f_0: {dmac: "11:22:33:44:55:66", cmd: "et 0xaaaa"},
         f_1: {dmac: "00:11:22:33:44:55", cmd: "et 0xaaaa"}
     },
     {
         txt: "dmac_mc",
         ace: {type: "ANY", dmac_mc: 0},
         f_0: {dmac: "00:11:22:33:44:55", cmd: "et 0xaaaa"},
         f_1: {dmac: "11:22:33:44:55:66", cmd: "et 0xaaaa"}
     },
     {
         txt: "dmac_bc",
         ace: {type: "ANY", dmac_bc: 1},
         f_0: {dmac: "ff:ff:ff:ff:ff:ff", cmd: "et 0xaaaa"},
         f_1: {dmac: "00:11:22:33:44:55", cmd: "et 0xaaaa"}
     },
     {
         txt: "dmac_bc",
         ace: {type: "ANY", dmac_bc: 0},
         f_0: {dmac: "00:11:22:33:44:55", cmd: "et 0xaaaa"},
         f_1: {dmac: "ff:ff:ff:ff:ff:ff", cmd: "et 0xaaaa"}
     },
     {
         txt: "untagged",
         ace: {type: "ANY", tagged: 0},
         f_0: {},
         f_1: {ot_vid: $vid_a}
     },
    {
         txt: "tagged",
         ace: {type: "ANY", tagged: 1},
         f_0: {ot_vid: $vid_a},
         f_1: {}
     },
     {
         txt: "vid",
         ace: {type: "ANY", tagged: 1, vid: {v: $vid_a, m: 0xfff}},
         f_0: {ot_vid: $vid_a},
         f_1: {ot_vid: $vid_b}
     },
     {
         txt: "pcp",
         ace: {type: "ANY", tagged: 1, pcp: {v: 7, m: 0x7}},
         f_0: {ot_vid: $vid_a, ot_pcp: 7},
         f_1: {ot_vid: $vid_b}
     },
     {
         txt: "dei",
         ace: {type: "ANY", tagged: 1, dei: 1},
         f_0: {ot_vid: $vid_a, ot_dei: 1},
         f_1: {ot_vid: $vid_b}
     },
     {
         txt: "etype/dmac",
         ace: {type: "ETYPE", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "et 0xaaaa"},
         f_1: {dmac: "01:02:03:04:06:07", cmd: "et 0xaaaa"}
     },
     {
         txt: "etype/smac",
         ace: {type: "ETYPE", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {smac: "00:01:02:03:04:05", cmd: "et 0xaaaa"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "et 0xaaaa"}
     },
     {
         txt: "etype/etype",
         ace: {type: "ETYPE", etype: {v: [0xaa,0xaa], m: [0xff,0xff]}}, 
         f_0: {cmd: "et 0xaaaa"},
         f_1: {cmd: "et 0xaabb"}
     },
     {
         txt: "etype/data",
         ace: {type: "ETYPE", data: {v: [1,2], m: [0xff, 0xff]}}, 
         f_0: {cmd: "et 0xaaaa data hex 0102"},
         f_1: {cmd: "et 0xaaaa data hex 0103"}
     },
     {
         txt: "llc/dmac",
         ace: {type: "LLC", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "et 46"},
         f_1: {dmac: "01:02:03:04:05:07", cmd: "et 46"}
     },
     {
         txt: "llc/smac",
         ace: {type: "LLC", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {smac: "00:01:02:03:04:05", cmd: "et 46"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "et 46"}
     },
     {
         txt: "llc/llc",
         ace: {type: "LLC", llc: {v: [1,2,3,0], m: [0xff,0xff,0xff,0x00]}},
         f_0: {cmd: "et 46 data hex 010203"},
         f_1: {cmd: "et 46 data hex 010204"}
     },
     {
         txt: "snap/dmac",
         ace: {type: "SNAP", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "et 46 data hex aaaa03"},
         f_1: {dmac: "01:02:03:04:05:07", cmd: "et 46 data hex aaaa03"}
     },
     {
         txt: "snap/smac",
         ace: {type: "SNAP", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {smac: "00:01:02:03:04:05", cmd: "et 46 data hex aaaa03"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "et 46 data hex aaaa03"}
     },
     {
         txt: "snap/snap",
         ace: {type: "SNAP", snap: {v: [1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff]}},
         f_0: {cmd: "et 46 data hex aaaa030102030405"},
         f_1: {cmd: "et 46 data hex aaaa030102030406"}
     },
     {
         txt: "arp/dmac",
         ace: {type: "ETYPE", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {arp: ["ETYPE"]},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "arp"},
         f_1: {dmac: "01:02:03:04:06:07", cmd: "arp"}
     },
     {
         txt: "arp/smac",
         ace: {type: "ARP", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {smac: "00:01:02:03:04:05", cmd: "arp"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "arp"}
     },
     {
         txt: "arp/opcode",
         ace: {type: "ARP", arp: 1, req: 1},
         f_0: {cmd: "arp oper 1"},
         f_1: {cmd: "arp oper 2"}
     },
     {
         txt: "arp/smac_match",
         ace: {type: "ARP", smac_match: 1},
         f_0: {smac: "00:01:02:03:04:05", cmd: "arp sha 00:01:02:03:04:05"},
         f_1: {smac: "00:01:02:03:04:05", cmd: "arp sha 00:01:02:03:04:06"}
     },
     {
         txt: "arp/dmac_match",
         ace: {type: "ARP", dmac_match: 1},
         f_0: {smac: "00:01:02:03:04:05", cmd: "arp tha 00:01:02:03:04:05"},
         f_1: {smac: "00:01:02:03:04:05", cmd: "arp tha 00:01:02:03:04:06"}
     },
     {
         txt: "arp/hlen",
         ace: {type: "ARP", length: 1},
         f_0: {cmd: "arp"},
         f_1: {cmd: "arp hlen 5"}
     },
     {
         txt: "arp/plen",
         ace: {type: "ARP", length: 1},
         f_0: {cmd: "arp"},
         f_1: {cmd: "arp plen 3"}
     },
     {
         txt: "arp/ptype",
         ace: {type: "ARP", ip: 1},
         f_0: {cmd: "arp"},
         f_1: {cmd: "arp ptype 0x86dd"}
     },
     {
         txt: "arp/htype",
         ace: {type: "ARP", ethernet: 1},
         f_0: {cmd: "arp"},
         f_1: {cmd: "arp htype 2"}
     },
     {
         txt: "arp/sip",
         ace: {type: "ARP", sip: {v: 0x01020304, m: 0xffffffff}},
         f_0: {cmd: "arp spa 1.2.3.4"},
         f_1: {cmd: "arp spa 1.2.3.5"}
     },
     {
         txt: "arp/dip",
         ace: {type: "ARP", dip: {v: 0x05060708, m: 0xffffffff}},
         f_0: {cmd: "arp tpa 5.6.7.8"},
         f_1: {cmd: "arp tpa 5.6.7.9"}
     },
     {
         txt: "ipv4/dmac",
         ace: {type: "ETYPE", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv4: ["ETYPE"]},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "ipv4"},
         f_1: {dmac: "01:02:03:04:06:07", cmd: "ipv4"}
     },
     {
         txt: "ipv4/dmac",
         ace: {type: "IPV4", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv4: ["EXT"]},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "ipv4"},
         f_1: {dmac: "01:02:03:04:06:07", cmd: "ipv4"}
     },
     {
         txt: "ipv4/smac",
         ace: {type: "ETYPE", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv4: ["ETYPE"]},
         f_0: {smac: "00:01:02:03:04:05", cmd: "ipv4"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "ipv4"}
     },
     {
         txt: "ipv4/smac",
         ace: {type: "IPV4", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv4: ["EXT"]},
         f_0: {smac: "00:01:02:03:04:05", cmd: "ipv4"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "ipv4"}
     },
     {
         txt: "ipv4/ttl",
         ace: {type: "IPV4", ttl: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 ttl 1"},
         f_1: {cmd: "ipv4 ttl 0"}
     },
     {
         txt: "ipv4/fragment/MF",
         ace: {type: "IPV4", fragment: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 flags 1"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/fragment/FO",
         ace: {type: "IPV4", fragment: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 offset 1"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/options",
         ace: {type: "IPV4", options: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 ihl 6"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/ds",
         ace: {type: "IPV4", ds: {v: 15, m: 0xff}},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 dscp 3 ecn 3"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/proto",
         ace: {type: "IPV4", proto: {v: 43, m: 0xff}},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 proto 43"},
         f_1: {cmd: "ipv4 proto 42"}
     },
     {
         txt: "ipv4/sip",
         ace: {type: "IPV4", sip: {v: 0x01020304, m: 0xffffffff}},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 sip 1.2.3.4"},
         f_1: {cmd: "ipv4 sip 1.2.3.5"}
     },
     {
         txt: "ipv4/dip",
         ace: {type: "IPV4", dip: {v: 0x05060708, m: 0xffffffff}},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 dip 5.6.7.8"},
         f_1: {cmd: "ipv4 dip 5.6.7.9"}
     },
     {
         txt: "ipv4/sport",
         ace: {type: "IPV4", proto: {v: 17, m: 0xff}, sport: {l: 10, h: 11}},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 udp sport 11"},
         f_1: {cmd: "ipv4 udp sport 12"}
     },
     {
         txt: "ipv4/dport",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, dport: {l: 12, h: 13}},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 tcp dport 12"},
         f_1: {cmd: "ipv4 tcp dport 14"}
     },
     {
         txt: "ipv4/fin",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_fin: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 tcp fin 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/syn",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_syn: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 tcp syn 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/rst",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_rst: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 tcp rst 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/psh",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_psh: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 tcp psh 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/ack",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_ack: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 tcp ack 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/urg",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_urg: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 tcp urg 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/sip_eq_dip",
         ace: {type: "IPV4", sip_eq_dip: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 sip 1.2.3.4 dip 1.2.3.4"},
         f_1: {cmd: "ipv4 sip 1.2.3.4 dip 1.2.3.5"}
     },
     {
         txt: "ipv4/sport_eq_dport",
         ace: {type: "IPV4", proto: {v: 17, m: 0xff}, sport_eq_dport: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 udp sport 11 dport 11"},
         f_1: {cmd: "ipv4 udp sport 11 dport 12"}
     },
     {
         txt: "ipv4/seq",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, seq_zero: 1},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 tcp"},
         f_1: {cmd: "ipv4 tcp seqn 1"}
     },
     {
         txt: "ipv4/data",
         ace: {type: "IPV4", proto: {v: 10, m: 0xff}, data: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv4 proto 10 data hex 010203040506"},
         f_1: {cmd: "ipv4 proto 10 data hex 010203040507"}
     },
     {
         txt: "ipv4/sip_smac",
         ace: {type: "IPV4", sip_smac: {sip: 0x01020304, smac: [0,1,2,3,4,5]}},
         key: {ipv4: ["DEFAULT","EXT"]},
         f_0: {smac: "00:01:02:03:04:05", cmd: "ipv4 sip 1.2.3.4"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "ipv4 sip 1.2.3.4"}
     },
     {
         txt: "ipv6/dmac",
         ace: {type: "ETYPE", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv6: ["ETYPE"]},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "ipv6"},
         f_1: {dmac: "01:02:03:04:06:07", cmd: "ipv6"}
     },
     {
         txt: "ipv6/dmac",
         ace: {type: "IPV6", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv6: ["EXT"]},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "ipv6"},
         f_1: {dmac: "01:02:03:04:06:07", cmd: "ipv6"}
     },
     {
         txt: "ipv6/smac",
         ace: {type: "ETYPE", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv6: ["ETYPE"]},
         f_0: {smac: "00:01:02:03:04:05", cmd: "ipv6"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "ipv6"}
     },
     {
         txt: "ipv6/smac",
         ace: {type: "IPV6", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv6: ["EXT"]},
         f_0: {smac: "00:01:02:03:04:05", cmd: "ipv6"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "ipv6"}
     },
     {
         txt: "ipv6/proto",
         ace: {type: "IPV6", proto: {v: 43, m: 0xff}},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 next 43"},
         f_1: {cmd: "ipv6"}
     },
     {
         txt: "ipv6/sip",
         ace: {type: "IPV6", sip: {v: [0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8], m: [0,0,0,0,0,0,0,0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv6: ["DEFAULT"]},
         f_0: {cmd: "ipv6 sip ::0102:0304:0506:0708"},
         f_1: {cmd: "ipv6 sip ::0102:0304:0506:0709"}
     },
     {
         txt: "ipv6/sip",
         ace: {type: "IPV6", sip: {v: [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15], m: [0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv6: ["EXT"]},
         f_0: {cmd: "ipv6 sip 0001:0203:0405:0607:0809:0a0b:0c0d:0e0f"},
         f_1: {cmd: "ipv6 sip 0002:0203:0405:0607:0809:0a0b:0c0d:0e0f"}
     },
     {
         txt: "ipv6/dip",
         ace: {type: "IPV6", dip: {v: [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15], m: [0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv6: ["EXT"]},
         f_0: {cmd: "ipv6 dip 0001:0203:0405:0607:0809:0a0b:0c0d:0e0f"},
         f_1: {cmd: "ipv6 dip 0002:0203:0405:0607:0809:0a0b:0c0d:0e0f"}
     },
     {
         txt: "ipv6/ttl",
         ace: {type: "IPV6", ttl: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 hlim 1"},
         f_1: {cmd: "ipv6 hlim 0"}
     },
     {
         txt: "ipv6/ds",
         ace: {type: "IPV6", ds: {v: 15, m: 0xff}},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 dscp 3 ecn 3"},
         f_1: {cmd: "ipv6"}
     },
     {
         txt: "ipv6/sport",
         ace: {type: "IPV6", proto: {v: 17, m: 0xff}, sport: {l: 10, h: 11}},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 udp sport 11"},
         f_1: {cmd: "ipv6 udp sport 12"}
     },
     {
         txt: "ipv6/dport",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, dport: {l: 12, h: 13}},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 tcp dport 12"},
         f_1: {cmd: "ipv6 tcp dport 14"}
     },
     {
         txt: "ipv6/fin",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_fin: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 tcp fin 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/syn",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_syn: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 tcp syn 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/rst",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_rst: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 tcp rst 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/psh",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_psh: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 tcp psh 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/ack",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_ack: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 tcp ack 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/urg",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_urg: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 tcp urg 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/sip_eq_dip",
         ace: {type: "IPV6", sip_eq_dip: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 sip ::0102:0304 dip ::0102:0304"},
         f_1: {cmd: "ipv6 sip ::0102:0304 dip ::0102:0305"}
     },
     {
         txt: "ipv6/sport_eq_dport",
         ace: {type: "IPV6", proto: {v: 17, m: 0xff}, sport_eq_dport: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 udp sport 11 dport 11"},
         f_1: {cmd: "ipv6 udp sport 11 dport 12"}
     },
     {
         txt: "ipv6/seq",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, seq_zero: 1},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 tcp"},
         f_1: {cmd: "ipv6 tcp seqn 1"}
     },
     {
         txt: "ipv6/data",
         ace: {type: "IPV6", proto: {v: 10, m: 0xff}, data: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         key: {ipv6: ["DEFAULT","EXT"]},
         f_0: {cmd: "ipv6 next 10 data hex 010203040506"},
         f_1: {cmd: "ipv6 next 10 data hex 010203040507"}
     },
    ]

def ace_test(t, type_ext)
    port = $ts.dut.port_list[$idx_tx]
    v = t[:ace]
    type = v[:type]
    ace = $ts.dut.call("mesa_ace_init", ("MESA_ACE_TYPE_" + type))
    ace["type_ext"] = type_ext
    ace["id"] = 1
    ace["port_list"] = "#{port}"

    ace_bit_set(ace, "dmac_mc", v, :dmac_mc)
    ace_bit_set(ace, "dmac_bc", v, :dmac_bc)

    k = ace["vlan"]
    ace_bit_set(k, "tagged", v, :tagged)
    vcap_vm_set(k, "vid", v, :vid)
    vcap_vm_set(k, "usr_prio", v, :pcp)
    ace_bit_set(k, "cfi", v, :dei)

    f = ace["frame"]
    case (type)
    when "ANY"
        k = f["any"]
    when "ETYPE"
        k = f["etype"]
        vcap_vm_set(k, "etype", v, :etype)
        vcap_vm_set(k, "data", v, :data)
    when "LLC"
        k = f["llc"]
        vcap_vm_set(k, "llc", v, :llc)
    when "SNAP"
        k = f["snap"]
        vcap_vm_set(k, "snap", v, :snap)
    when "ARP"
        k = f["arp"]
        ace_bit_set(k, "arp", v, :arp)
        ace_bit_set(k, "req", v, :req)
        ace_bit_set(k, "smac_match", v, :smac_match)
        ace_bit_set(k, "dmac_match", v, :dmac_match)
        ace_bit_set(k, "length", v, :length)
        ace_bit_set(k, "ip", v, :ip)
        ace_bit_set(k, "ethernet", v, :ethernet)
        vcap_vm_set(k, "sip", v, :sip)
        vcap_vm_set(k, "dip", v, :dip)
    when "IPV4", "IPV6"
        k = f[v[:type].downcase]
        ace_bit_set(k, "ttl", v, :ttl)
        ace_bit_set(k, "fragment", v, :fragment)
        ace_bit_set(k, "options", v, :options)
        vcap_vm_set(k, "ds", v, :ds)
        vcap_vm_set(k, "proto", v, :proto)
        vcap_vm_set(k, "sip", v, :sip)
        vcap_vm_set(k, "dip", v, :dip)
        vcap_vm_set(k, "data", v, :data)
        ace_range_set(k, "sport", v, :sport)
        ace_range_set(k, "dport", v, :dport)
        ace_bit_set(k, "tcp_fin", v, :tcp_fin)
        ace_bit_set(k, "tcp_syn", v, :tcp_syn)
        ace_bit_set(k, "tcp_rst", v, :tcp_rst)
        ace_bit_set(k, "tcp_psh", v, :tcp_psh)
        ace_bit_set(k, "tcp_ack", v, :tcp_ack)
        ace_bit_set(k, "tcp_urg", v, :tcp_urg)
        ace_bit_set(k, "sip_eq_dip", v, :sip_eq_dip)
        ace_bit_set(k, "sport_eq_dport", v, :sport_eq_dport)
        ace_bit_set(k, "seq_zero", v, :seq_zero)
        if (v.key?:sip_smac)
            k["sip_smac"]["enable"] = true
            k["sip_smac"]["sip"] = v[:sip_smac][:sip]
            k["sip_smac"]["smac"]["addr"] = v[:sip_smac][:smac]
        end
    else
    end
    vcap_vm_set(k, "dmac", v, :dmac)
    vcap_vm_set(k, "smac", v, :smac)

    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
    $ts.dut.call("mesa_ace_add", 0, ace)

    for i in 0..1 do
        t_i("Test '#{t[:txt]}',#{i == 0 ? "" : " no"} match => #{i == 0 ? "disc" : "forw"}ard")
        f = (i == 0 ? t[:f_0] : t[:f_1])
        cmd = "eth"
        if (f.key?:dmac)
            cmd += " dmac #{f[:dmac]}"
        end
        if (f.key?:smac)
            cmd += " smac #{f[:smac]}"
        end

        if (f.key?:ot_vid)
            cmd += " ctag vid #{f[:ot_vid]}"
            if (f.key?:ot_pcp)
                cmd += " pcp #{f[:ot_pcp]}"
            end
            if (f.key?:ot_dei)
                cmd += " dei #{f[:ot_dei]}"
            end
            cmd += " data pattern cnt 64"
        end

        if (f.key?:cmd)
            cmd += " #{f[:cmd]}"
        end
        run_ef_tx_rx_cmd($ts, $idx_tx, i == 0 ? [] : [$idx_rx], cmd)
    end
end

luton26 = cap_get("MEP_LUTON26")
epid = cap_get("PACKET_IFH_EPID")
acl_ext_dip = cap_get("ACL_EXT_DIP")
acl_ext_mac = cap_get("ACL_EXT_MAC")
port = $ts.dut.port_list[$idx_tx]
conf = $ts.dut.call("mesa_acl_port_conf_get", port)

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    v = t[:ace]
    ipv4 = (v[:type] == "IPV4" ? true : false)
    ipv6 = (v[:type] == "IPV6" ? true : false)
    if (luton26 == 1)
        # Luton26 limitations
        if (v.key?:sip_eq_dip and ipv6)
            # Matching SIP equal to DIP for IPv6 not supported
            next
        end
    end
    if (epid == 11)
        # FireAnt limitations
        if (v.key?:sip_eq_dip or v.key?:sport_eq_dport or v.key?:seq_zero)
            next
        end
        end
    if (ipv4 or ipv6)
        if (acl_ext_mac == 0 and (v.key?:dmac or v.key?:smac))
            # IP/MAC filtering not supported
            next
        end
    end
    skip_ext = false
    if (ipv4 and acl_ext_mac == 0)
        # Extended IPv4 rules not supported
        skip_ext = true
    end
    if (ipv6 and acl_ext_dip == 0)
        if (v.key?:sip or (v.key?:proto and v[:proto][:v] == 43))
        # Only IPv6 protocol and SIP filtering is supported
        else
            skip_ext = true
        end
    end

    key_list = ["DEFAULT"]
    frm = "arp"
    if (t.key?:key)
        k = t[:key]
        if (k.key?:arp)
            key_list = k[:arp]
        end
        if (k.key?:ipv4)
            key_list = k[:ipv4]
            frm = "ipv4"
        end
        if (k.key?:ipv6)
            key_list = k[:ipv6]
            frm = "ipv6"
        end
    end
    txt = t[:txt]
    key_list.each do |k|
        type_ext = (k == "EXT" ? true : false)
        if (skip_ext and type_ext)
            next
        end
        t[:txt] = (txt + " (#{k})")
        test t[:txt] do
            conf["key"][frm] = ("MESA_ACL_KEY_" + k)
            $ts.dut.call("mesa_acl_port_conf_set", port, conf)
            ace_test(t, type_ext)
        end
    end
end

test_summary
