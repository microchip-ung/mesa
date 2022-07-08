#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if HACL supported
cap_check_exit("ACL_HACL")

$idx_tx = 0
$idx_rx = 1
$vid_a  = 10
$vid_b  = 11

#---------- Configuration -----------------------------------------------------

test "conf" do
    test "All ports are C-ports" do
        $ts.dut.p.each do |port|
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
         acl: "vacl",
         ace: {type: "ETYPE", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
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
        acl: "vacl",
        ace: {type: "ANY", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
        f_0: {dmac: "01:02:03:04:05:06", cmd: "ipv4"},
        f_1: {dmac: "01:02:03:04:06:07", cmd: "ipv4"}
     },
     {
         txt: "ipv4/smac",
         acl: "vacl",
         ace: {type: "ETYPE", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {smac: "00:01:02:03:04:05", cmd: "ipv4"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "ipv4"}
     },
     {
         txt: "ipv4/ttl",
         ace: {type: "IPV4", ttl: 1},
         f_0: {cmd: "ipv4 ttl 1"},
         f_1: {cmd: "ipv4 ttl 0"}
     },
     {
         txt: "ipv4/fragment/MF",
         ace: {type: "IPV4", fragment: 1},
         f_0: {cmd: "ipv4 flags 1"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/fragment/FO",
         ace: {type: "IPV4", fragment: 1},
         f_0: {cmd: "ipv4 offset 1"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/options",
         ace: {type: "IPV4", options: 1},
         f_0: {cmd: "ipv4 ihl 6"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/ds",
         ace: {type: "IPV4", ds: {v: 15, m: 0xff}},
         f_0: {cmd: "ipv4 dscp 3 ecn 3"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/proto",
         ace: {type: "IPV4", proto: {v: 43, m: 0xff}},
         f_0: {cmd: "ipv4 proto 43"},
         f_1: {cmd: "ipv4 proto 42"}
     },
     {
         txt: "ipv4/sip",
         ace: {type: "IPV4", sip: {v: 0x01020304, m: 0xffffffff}},
         f_0: {cmd: "ipv4 sip 1.2.3.4"},
         f_1: {cmd: "ipv4 sip 1.2.3.5"}
     },
     {
         txt: "ipv4/dip",
         ace: {type: "IPV4", dip: {v: 0x05060708, m: 0xffffffff}},
         f_0: {cmd: "ipv4 dip 5.6.7.8"},
         f_1: {cmd: "ipv4 dip 5.6.7.9"}
     },
     {
         txt: "ipv4/sport",
         ace: {type: "IPV4", proto: {v: 17, m: 0xff}, sport: {l: 10, h: 11}},
         f_0: {cmd: "ipv4 udp sport 11"},
         f_1: {cmd: "ipv4 udp sport 12"}
     },
     {
         txt: "ipv4/dport",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, dport: {l: 12, h: 13}},
         f_0: {cmd: "ipv4 tcp dport 12"},
         f_1: {cmd: "ipv4 tcp dport 14"}
     },
     {
         txt: "ipv4/fin",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_fin: 1},
         f_0: {cmd: "ipv4 tcp fin 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/syn",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_syn: 1},
         f_0: {cmd: "ipv4 tcp syn 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/rst",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_rst: 1},
         f_0: {cmd: "ipv4 tcp rst 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/psh",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_psh: 1},
         f_0: {cmd: "ipv4 tcp psh 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/ack",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_ack: 1},
         f_0: {cmd: "ipv4 tcp ack 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/urg",
         ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_urg: 1},
         f_0: {cmd: "ipv4 tcp urg 1"},
         f_1: {cmd: "ipv4 tcp"}
     },
     {
         txt: "ipv4/data",
         ace: {type: "IPV4", proto: {v: 10, m: 0xff}, data: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {cmd: "ipv4 proto 10 data hex 010203040506"},
         f_1: {cmd: "ipv4 proto 10 data hex 010203040507"}
     },
     {
         txt: "ipv6/dmac",
         acl: "vacl",
         ace: {type: "ETYPE", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {dmac: "01:02:03:04:05:06", cmd: "ipv6"},
         f_1: {dmac: "01:02:03:04:06:07", cmd: "ipv6"}
     },
     {
         txt: "ipv6/smac",
         acl: "vacl",
         ace: {type: "ETYPE", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {smac: "00:01:02:03:04:05", cmd: "ipv6"},
         f_1: {smac: "00:01:02:03:04:06", cmd: "ipv6"}
     },
     {
         txt: "ipv6/proto",
         ace: {type: "IPV6", proto: {v: 43, m: 0xff}},
         f_0: {cmd: "ipv6 next 43"},
         f_1: {cmd: "ipv6"}
     },
     {
         txt: "ipv6/sip",
         ace: {type: "IPV6", sip: {v: [0,0,0,0,0,0,0,0,0,0,0,0,5,6,7,8], m: [0,0,0,0,0,0,0,0,0,0,0,0,0xff,0xff,0xff,0xff]}},
         f_0: {cmd: "ipv6 sip ::0506:0708"},
         f_1: {cmd: "ipv6 sip ::0506:0709"}
     },
     {
         txt: "ipv6/ttl",
         ace: {type: "IPV6", ttl: 1},
         f_0: {cmd: "ipv6 hlim 1"},
         f_1: {cmd: "ipv6 hlim 0"}
     },
     {
         txt: "ipv6/ds",
         ace: {type: "IPV6", ds: {v: 15, m: 0xff}},
         f_0: {cmd: "ipv6 dscp 3 ecn 3"},
         f_1: {cmd: "ipv6"}
     },
     {
         txt: "ipv6/sport",
         ace: {type: "IPV6", proto: {v: 17, m: 0xff}, sport: {l: 10, h: 11}},
         f_0: {cmd: "ipv6 udp sport 11"},
         f_1: {cmd: "ipv6 udp sport 12"}
     },
     {
         txt: "ipv6/dport",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, dport: {l: 12, h: 13}},
         f_0: {cmd: "ipv6 tcp dport 12"},
         f_1: {cmd: "ipv6 tcp dport 14"}
     },
     {
         txt: "ipv6/fin",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_fin: 1},
         f_0: {cmd: "ipv6 tcp fin 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/syn",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_syn: 1},
         f_0: {cmd: "ipv6 tcp syn 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/rst",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_rst: 1},
         f_0: {cmd: "ipv6 tcp rst 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/psh",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_psh: 1},
         f_0: {cmd: "ipv6 tcp psh 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/ack",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_ack: 1},
         f_0: {cmd: "ipv6 tcp ack 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/urg",
         ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_urg: 1},
         f_0: {cmd: "ipv6 tcp urg 1"},
         f_1: {cmd: "ipv6 tcp"}
     },
     {
         txt: "ipv6/data",
         ace: {type: "IPV6", proto: {v: 10, m: 0xff}, data: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {cmd: "ipv6 next 10 data hex 010203040506"},
         f_1: {cmd: "ipv6 next 10 data hex 010203040507"}
     },
    ]

def ace_test(t, acl)
    eacl = (acl[0] == "E" ? true : false)
    v = t[:ace]
    type = v[:type]
    ace = $ts.dut.call("mesa_hace_init", ("MESA_ACE_TYPE_" + type))
    ace["id"] = 1
    k = ace["key"]
    k["port_list"] = "#{$ts.dut.p[eacl ? $idx_rx : $idx_tx]}"

    ace_bit_set(k, "dmac_mc", v, :dmac_mc)
    ace_bit_set(k, "dmac_bc", v, :dmac_bc)
    vcap_vm_set(k, "dmac", v, :dmac)
    vcap_vm_set(k, "smac", v, :smac)

    k = k["vlan"]
    ace_bit_set(k, "tagged", v, :tagged)
    vcap_vm_set(k, "vid", v, :vid)
    vcap_vm_set(k, "usr_prio", v, :pcp)
    ace_bit_set(k, "cfi", v, :dei)

    k = ace["key"]
    case (type)
    when "ETYPE"
        k = k["etype"]
        vcap_vm_set(k, "etype", v, :etype)
        vcap_vm_set(k, "data", v, :data)
    when "LLC"
        vcap_vm_set(k["llc"], "llc", v, :llc)
    when "SNAP"
        vcap_vm_set(k["snap"], "snap", v, :snap)
    when "ARP"
        k = k["arp"]
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
        k = k[type.downcase]
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
    else
    end

    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
    action["port_list"] = "#{$ts.dut.p[$idx_rx]}"    
    hacl_type = ("MESA_HACL_TYPE_" + acl)
    $ts.dut.call("mesa_hace_add", hacl_type, 0, ace)

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

        idx_list = ([0, 1, 2, 3] - [$idx_tx])
        if (i == 0)
            idx_list = (eacl ? (idx_list - [$idx_rx]) : [$idx_rx])
        end
        run_ef_tx_rx_cmd($ts, $idx_tx, idx_list, cmd)
    end

    $ts.dut.call("mesa_hace_del", hacl_type, ace["id"])
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    acl = t[:acl]
    case (t[:ace][:type])
    when "ARP", "IPV4", "IPV6"
        # Frame type only supported for PACL
        acl = "pacl"
    else
    end

    acl_list = ["IPACL", "IVACL", "EVACL", "EPACL"]
    case (acl)
    when "pacl"
        acl_list = ["IPACL", "EPACL"]
    when "vacl"
        acl_list = ["IVACL", "EVACL"]
    end

    acl_list.each do |acl|
        test "#{acl}: #{t[:txt]}" do
            ace_test(t, acl)
        end
    end
end

test_summary
