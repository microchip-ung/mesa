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
$policy_discard = 20

test "conf" do
    t_i("C-ports")
    $ts.dut.port_list.each do |port|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end
    
    t_i("Include both ports in VLAN")
    port_list = port_idx_list_str([$idx_tx, $idx_rx])
    $ts.dut.call("mesa_vlan_port_members_set", 1, port_list)
    $ts.dut.call("mesa_vlan_port_members_set", $vid_a, port_list)
    $ts.dut.call("mesa_vlan_port_members_set", $vid_b, port_list)

    t_i("Make ACL rule discarding all frames with policy")
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ANY")
    ace["id"] = 1
    ace["port_list"] = port_idx_list_str([$idx_tx]) 
    pol = ace["policy"]
    pol["value"] = $policy_discard
    pol["mask"] = 0xff
    ace["action"]["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
    $ts.dut.call("mesa_ace_add", 0, ace)
end

#---------- Frame testing -----------------------------------------------------

# Each entry in the test table has these items:
# 1: Text string printed during test
# 2: Optional capability to be checked
# 3: Optional port mode list to be checked
# 4: QCE to be configured with discard action
# 5: Frame[0] matching the QCE, must be discarded
# 6: Frame[1] not matching the QCE, must be forwarded
test_table =
    [
     {
         txt: "dmac_mc",
         qce: {type: "ANY", dmac_mc: 0},
         f_0: {dmac: "00:11:22:33:44:55"},
         f_1: {dmac: "11:22:33:44:55:66"}
     },
     {
         txt: "dmac_mc",
         qce: {type: "ANY", dmac_mc: 0},
         f_0: {dmac: "00:11:22:33:44:55"},
         f_1: {dmac: "11:22:33:44:55:66"}
     },
     {
         txt: "dmac_bc",
         qce: {type: "ANY", dmac_bc: 1},
         f_0: {dmac: "ff:ff:ff:ff:ff:ff"},
         f_1: {dmac: "00:11:22:33:44:55"}
     },
     {
         txt: "dmac",
         cap: "KEY_DMAC",
         mode: ["NORMAL_DST", "MAC_IP_ADDR"],
         qce: {type: "ANY", dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {dmac: "01:02:03:04:05:06"},
         f_1: {dmac: "01:02:03:04:06:07"}
     },
     {
         txt: "smac",
         qce: {type: "ANY", smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {smac: "00:01:02:03:04:05"},
         f_1: {smac: "00:01:02:03:04:06"}
     },
     {
         txt: "untagged",
         qce: {type: "ANY", tagged: 0},
         f_0: {},
         f_1: {ot: {tpid: 0x8100, vid: $vid_a}}
     },
     {
         txt: "tagged",
         qce: {type: "ANY", tagged: 1, s_tag: 0},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a}},
         f_1: {}
     },
     {
         txt: "vid",
         qce: {type: "ANY", tagged: 1, vid: {v: $vid_a, m: 0xfff}},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a}},
         f_1: {ot: {tpid: 0x8100, vid: $vid_b}}
     },
     {
         txt: "pcp",
         qce: {type: "ANY", tagged: 1, pcp: {v: 7, m: 0x7}},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a, pcp: 7}},
         f_1: {ot: {tpid: 0x8100, vid: $vid_a}}
     },
     {
         txt: "dei",
         qce: {type: "ANY", tagged: 1, dei: 1},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a, dei: 1}},
         f_1: {ot: {tpid: 0x8100, vid: $vid_a}}
     },
     {
         txt: "inner/untagged",
         cap: "KEY_INNER_TAG",
         qce: {type: "ANY", tagged: 1, in_tagged: 0},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a}},
         f_1: {ot: {tpid: 0x8100, vid: $vid_a}, it: {tpid: 0x8100}}
     },
     {
         txt: "inner/tagged",
         cap: "KEY_INNER_TAG",
         qce: {type: "ANY", in_tagged: 1, in_s_tag: 0},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a}, it: {tpid: 0x8100}},
         f_1: {ot: {tpid: 0x8100, vid: $vid_a}}
     },
     {
         txt: "inner/vid",
         cap: "KEY_INNER_TAG",
         mode: ["DOUBLE_TAG", "IP_ADDR", "MAC_IP_ADDR"],
         qce: {type: "IPV4", in_tagged: 1, in_vid: {v: $vid_a, m: 0xfff}},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a}, it: {tpid: 0x8100, vid: $vid_a}, cmd: "ipv4"},
         f_1: {ot: {tpid: 0x8100, vid: $vid_a}, it: {tpid: 0x8100, vid: $vid_b}, cmd: "ipv4"}
     },
     {
         txt: "inner/pcp",
         cap: "KEY_INNER_TAG",
         mode: ["DOUBLE_TAG", "IP_ADDR", "MAC_IP_ADDR"],
         qce: {type: "IPV4", in_tagged: 1, in_pcp: {v: 7, m: 0x7}},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a}, it: {tpid: 0x8100, pcp: 7}, cmd: "ipv4"},
         f_1: {ot: {tpid: 0x8100, vid: $vid_a}, it: {tpid: 0x8100}, cmd: "ipv4"}
     },
     {
         txt: "inner/dei",
         cap: "KEY_INNER_TAG",
         mode: ["DOUBLE_TAG", "IP_ADDR", "MAC_IP_ADDR"],
         qce: {type: "IPV4", in_tagged: 1, in_dei: 1},
         f_0: {ot: {tpid: 0x8100, vid: $vid_a}, it: {tpid: 0x8100, dei: 1}, cmd: "ipv4"},
         f_1: {ot: {tpid: 0x8100, vid: $vid_a}, it: {tpid: 0x8100}, cmd: "ipv4"}
     },
     {
         txt: "etype/etype",
         qce: {type: "ETYPE", etype: {v: [0xaa,0xaa], m: [0xff,0xff]}}, 
         f_0: {cmd: "et 0xaaaa"},
         f_1: {cmd: "et 0xaabb"}
     },
     {
         txt: "etype/data",
         qce: {type: "ETYPE", data: {v: [1,2,3,4], m: [0xff, 0xff, 0xff, 0xff]}}, 
         f_0: {cmd: "et 0xaaaa data hex 01020304"},
         f_1: {cmd: "et 0xaaaa data hex 01010205"}
     },
     {
         txt: "llc",
         qce: {type: "LLC", llc: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {cmd: "et 46 data hex 010203040506"},
         f_1: {cmd: "et 46 data hex 010207040506"}
     },
     {
         txt: "snap",
         qce: {type: "SNAP", snap: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {cmd: "et 46 data hex aaaa03010203040506"},
         f_1: {cmd: "et 46 data hex aaaa03010203040807"}
     },
     {
         txt: "ipv4/fragment/MF",
         qce: {type: "IPV4", fragment: 1},
         f_0: {cmd: "ipv4 flags 1"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/fragment/FO",
         qce: {type: "IPV4", fragment: 1},
         f_0: {cmd: "ipv4 offset 1"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/dscp",
         qce: {type: "IPV4", dscp: {v: 42, m: 0x3f}},
         f_0: {cmd: "ipv4 dscp 42"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/proto",
         qce: {type: "IPV4", proto: {v: 43, m: 0xff}},
         f_0: {cmd: "ipv4 proto 43"},
         f_1: {cmd: "ipv4"}
     },
     {
         txt: "ipv4/sip",
         mode: ["NORMAL_SRC", "IP_ADDR", "MAC_IP_ADDR"],
         qce: {type: "IPV4", sip: {v: 0x01020304, m: 0xffffffff}},
         f_0: {cmd: "ipv4 sip 1.2.3.4"},
         f_1: {cmd: "ipv4 sip 1.2.3.5"}
     },
     {
         txt: "ipv4/dip",
         cap: "KEY_DIP",
         mode: ["NORMAL_DST", "IP_ADDR", "MAC_IP_ADDR"],
         qce: {type: "IPV4", dip: {v: 0x05060708, m: 0xffffffff}},
         f_0: {cmd: "ipv4 dip 5.6.7.8"},
         f_1: {cmd: "ipv4 dip 5.6.7.9"}
     },
     {
         txt: "ipv4/sport",
         mode: ["NORMAL_SRC", "NORMAL_DST", "MAC_IP_ADDR"],
         qce: {type: "IPV4", proto: {v: 17, m: 0xff}, sport: {l: 10, h: 11}},
         f_0: {cmd: "ipv4 udp sport 11"},
         f_1: {cmd: "ipv4 udp sport 12"}
     },
     {
         txt: "ipv4/dport",
         mode: ["NORMAL_SRC", "NORMAL_DST", "MAC_IP_ADDR"],
         qce: {type: "IPV4", proto: {v: 6, m: 0xff}, dport: {l: 12, h: 13}},
         f_0: {cmd: "ipv4 tcp dport 12"},
         f_1: {cmd: "ipv4 tcp dport 14"}
     },
     {
         txt: "ipv6/dscp",
         qce: {type: "IPV6", dscp: {v: 42, m: 0xff}},
         f_0: {cmd: "ipv6 dscp 42"},
         f_1: {cmd: "ipv6"}
     },
     {
         txt: "ipv6/proto",
         qce: {type: "IPV6", proto: {v: 43, m: 0xff}},
         f_0: {cmd: "ipv6 next 43"},
         f_1: {cmd: "ipv6"}
     },
     {
         txt: "ipv6/sip",
         mode: ["NORMAL_SRC", "IP_ADDR", "MAC_IP_ADDR"],
         qce: {type: "IPV6", sip: {v: [0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4], m: [0,0,0,0,0,0,0,0,0,0,0,0,0xff,0xff,0xff,0xff]}},
         f_0: {cmd: "ipv6 sip ::0102:0304"},
         f_1: {cmd: "ipv6 sip ::0102:0305"}
     },
     {
         txt: "ipv6/dip",
         cap: "KEY_DIP",
         mode: ["NORMAL_DST", "IP_ADDR", "MAC_IP_ADDR"],
         qce: {type: "IPV6", dip: {v: [0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4], m: [0,0,0,0,0,0,0,0,0,0,0,0,0xff,0xff,0xff,0xff]}},
         f_0: {cmd: "ipv6 dip ::0102:0304"},
         f_1: {cmd: "ipv6 dip ::0102:0305"}
     },
     {
         txt: "ipv6/sport",
         mode: ["NORMAL_SRC", "NORMAL_DST", "MAC_IP_ADDR"],
         qce: {type: "IPV6", proto: {v: 17, m: 0xff}, sport: {l: 10, h: 11}},
         f_0: {cmd: "ipv6 udp sport 11"},
         f_1: {cmd: "ipv6 udp sport 12"}
     },
     {
         txt: "ipv6/dport",
         mode: ["NORMAL_SRC", "NORMAL_DST", "MAC_IP_ADDR"],
         qce: {type: "IPV6", proto: {v: 6, m: 0xff}, dport: {l: 12, h: 13}},
         f_0: {cmd: "ipv6 tcp dport 12"},
         f_1: {cmd: "ipv6 tcp dport 14"}
     },
    ]


# Setup port mode for Serval-1
def port_mode_set(idx, mode)
    port = $ts.dut.port_list[$idx_tx]
    conf = $ts.dut.call("mesa_qos_port_conf_get", port)
    conf["key_type"] = ("MESA_VCAP_KEY_TYPE_" + (mode[0] == "N" ? "NORMAL" : mode))
    conf["dmac_dip"] = (mode == "NORMAL_DST" ? true : false)
    $ts.dut.call("mesa_qos_port_conf_set", port, conf)
end

cap_key_type = cap_get("QOS_QCL_KEY_TYPE")
# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test "key-#{t[:txt]}" do
        if (t.key?:cap and cap_get("QOS_QCL_" + t[:cap]) == 0)
            next
        end

        v = t[:qce]
        qce = $ts.dut.call("mesa_qce_init", "MESA_QCE_TYPE_" + v[:type])
        qce["id"] = 1
        key = qce["key"]
        key["port_list"] = port_idx_list_str([$idx_tx]) 

        k = key["mac"]
        vcap_bit_set(k, "dmac_mc", v, :dmac_mc)
        vcap_bit_set(k, "dmac_bc", v, :dmac_bc)
        vcap_vm_set(k, "dmac", v, :dmac)
        vcap_vm_set(k, "smac", v, :smac)

        k = key["tag"]
        vcap_bit_set(k, "tagged", v, :tagged) 
        vcap_bit_set(k, "s_tag", v, :s_tag)
        vcap_range_set(k, "vid", v, :vid)
        vcap_vm_set(k, "pcp", v, :pcp)
        vcap_bit_set(k, "dei", v, :dei)

        k = key["inner_tag"]
        vcap_bit_set(k, "tagged", v, :in_tagged) 
        vcap_bit_set(k, "s_tag", v, :in_s_tag)
        vcap_range_set(k, "vid", v, :in_vid)
        vcap_vm_set(k, "pcp", v, :in_pcp)
        vcap_bit_set(k, "dei", v, :in_dei)

        f = key["frame"]
        case (v[:type])
        when "ETYPE"
            k = f["etype"]
            vcap_vm_set(k, "etype", v, :etype)
            vcap_vm_set(k, "data", v, :data)
        when "LLC"
            k = f["llc"]
            vcap_vm_set(k, "data", v, :llc)
        when "SNAP"
            k = f["snap"]
            vcap_vm_set(k, "data", v, :snap)
        when "IPV4", "IPV6"
            k = f[v[:type].downcase]
            vcap_bit_set(k, "fragment", v, :fragment)
            vcap_range_set(k, "dscp", v, :dscp)
            vcap_vm_set(k, "proto", v, :proto)
            vcap_vm_set(k, "sip", v, :sip)
            vcap_vm_set(k, "dip", v, :dip)
            vcap_range_set(k, "sport", v, :sport)
            vcap_range_set(k, "dport", v, :dport)
        else
        end

        action = qce["action"]
        action["policy_no_enable"] = true
        action["policy_no"] = $policy_discard
        $ts.dut.call("mesa_qce_add", 0, qce)

        # Determine port mode list
        if (t.key?:mode and cap_key_type == 1)
            mode_list = t[:mode]
        else
            mode_list = [nil]
        end

        mode_list.each do |mode|
            if (mode != nil)
                # Set port mode
                port_mode_set($idx_tx, mode)
            end

            for i in 0..1 do
                str = (mode == nil ? "" : " (" + mode + ")")
                t_i("Test key '#{t[:txt]}'#{str},#{i == 0 ? "" : " no"} match => #{i == 0 ? "disc" : "forw"}ard")
                f = (i == 0 ? t[:f_0] : t[:f_1])
                cmd = "eth"
                if (f.key?:dmac)
                    cmd += " dmac #{f[:dmac]}"
                end
                if (f.key?:smac)
                    cmd += " smac #{f[:smac]}"
                end
                if (f.key?:ot)
                    cmd += cmd_tag_push(f[:ot])
                end
                if (f.key?:it)
                    cmd += cmd_tag_push(f[:it])
                end
                if (f.key?:cmd)
                    cmd += " #{f[:cmd]}"
                end
                cmd += " data pattern cnt 64"
                run_ef_tx_rx_cmd($ts, $idx_tx, i == 0 ? [] : [$idx_rx], cmd)
            end
        end
        if (mode_list[0] != nil)
            # Set mode back to default
            port_mode_set($idx_tx, "NORMAL_SRC")
        end
    end
end

action_table =
    [
     {
         txt: "prio",
         prio: 7, dp: 0, pcp_dei: 0, pcp: 7, dei: 0, dscp: 0, mode: "MAPPED", emode: "DISABLE"
     },
     {
         txt: "dp",
         prio: 0, dp: 1, pcp_dei: 0, pcp: 1, dei: 1, dscp: 0, mode: "MAPPED", emode: "DISABLE"
     },
     {
         txt: "pcp/dei",
         prio: 0, dp: 0, pcp_dei: 1, pcp: 6, dei: 1, dscp: 0, mode: "CLASSIFIED", emode: "DISABLE"
     },
     {
         txt: "dscp",
         prio: 0, dp: 0, pcp_dei: 0, pcp: 0, dei: 0, dscp: 42, mode: "CLASSIFIED", emode: "REMARK"
     }
    ]

# Run all or selected test
sel = table_lookup(action_table, :sel)
action_table.each do |t|
    next if (t[:sel] != sel)
    test "action-#{t[:txt]}" do
        qce = $ts.dut.call("mesa_qce_init", "MESA_QCE_TYPE_IPV4")
        qce["id"] = 1
        qce["key"]["port_list"] = port_idx_list_str([$idx_tx]) 
        action = qce["action"]
        action["prio_enable"] = (t[:prio] == 0 ? false : true)
        action["prio"] = t[:prio]
        action["dp_enable"] = (t[:dp] == 0 ? false : true)
        action["dp"] = t[:dp]
        action["pcp_dei_enable"] = (t[:pcp_dei] == 0 ? false : true)
        action["pcp"] = t[:pcp]
        action["dei"] = t[:dei]
        action["dscp_enable"] = (t[:dscp] == 0 ? false : true)
        action["dscp"] = t[:dscp]
        $ts.dut.call("mesa_qce_add", 0, qce)

        port = $ts.dut.port_list[$idx_rx]
        conf = $ts.dut.call("mesa_qos_port_conf_get", port)
        conf["tag"]["remark_mode"] = ("MESA_TAG_REMARK_MODE_" + t[:mode])
        conf["dscp"]["emode"] = ("MESA_DSCP_EMODE_" + t[:emode])
        $ts.dut.call("mesa_qos_port_conf_set", port, conf)
        
        cmd = "sudo ef"
        cmd_end = ""
        [$idx_tx, $idx_rx].each do |idx|
            tag = {tpid: 0x8100, vid: $vid_a}
            if (idx == $idx_tx)
                dir = "tx"
                dscp = 0
            else
                dir = "rx"
                dscp = t[:dscp]
                tag[:pcp] = t[:pcp]
                tag[:dei] = t[:dei]
            end
            cmd += " name f#{idx}"
            cmd += " eth dmac ff:ff:ff:ff:ff:ff smac 00:00:00:00:00:0a"
            cmd += cmd_tag_push(tag)
            cmd += " ipv4 dscp #{dscp}"
            cmd += " data pattern cnt 64"
            cmd_end += " #{dir} #{$ts.pc.p[idx]} name f#{idx}"
        end
        $ts.pc.run(cmd + cmd_end)
    end
end

test_summary
