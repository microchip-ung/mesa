#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$port_idx_tx = 3

$cap_dmac = cap_get("L2_VCL_KEY_DMAC")
$cap_dip = cap_get("L2_VCL_KEY_DIP")
$vce_added = false

test "conf" do
    t_i("set S-custom tag Ethernet Type")
    conf = $ts.dut.call("mesa_vlan_conf_get")
    conf["s_etype"] = 0x9100
    $ts.dut.call("mesa_vlan_conf_set", conf)

    t_i("enable DMAC/DIP matching on port index 1")
    port = $ts.dut.port_list[1]
    conf = $ts.dut.call("mesa_vcl_port_conf_get", port)
    conf["dmac_dip"] = true
    $ts.dut.call("mesa_vcl_port_conf_set", port, conf)

    t_i("set egress port to tag all frames")
    port = $ts.dut.port_list[$port_idx_tx]
    conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
    conf["untagged_vid"] = 0
    $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
end

#---------- Frame testing -----------------------------------------------------

# Each entry in the test table has these items:
# 1: Text string printed during test
# 2: VCE to be configured with VLAN classification
# 3: Frame[0] matching the VCE
# 4: Frame[1] not matching the VCE
test_table =
    [
     {
         txt: "any",
         vce: {vid: 100, port_idx: 0, type: "ANY"},
         f_0: {port_idx: 0, cmd: ""},
         f_1: {port_idx: 1, cmd: ""}
     },
     {
         txt: "etype/uc",
         vce: {vid: 101, port_idx: 0, type: "ETYPE", etype: {v: [0xbb, 0xbb], m: [0xff, 0xff]}, dmac_mc: 0, dmac_bc: 0},
         f_0: {port_idx: 0, cmd: "et 0xbbbb", dmac: "00:11:22:33:44:55"},
         f_1: {port_idx: 0, cmd: "et 0xbbbb", dmac: "01:11:22:33:44:55"}
     },
     {
         txt: "etype/mc",
         vce: {vid: 102, port_idx: 0, type: "ETYPE", etype: {v: [0xbb, 0xbb], m: [0xff, 0xff]}, dmac_mc: 1, dmac_bc: 0},
         f_0: {port_idx: 0, cmd: "et 0xbbbb", dmac: "01:11:22:33:44:55"},
         f_1: {port_idx: 0, cmd: "et 0xbbbb", dmac: "00:11:22:33:44:55"}
     },
     {
         txt: "etype/bc",
         vce: {vid: 103, port_idx: 0, type: "ETYPE", etype: {v: [0xbb, 0xbb], m: [0xff, 0xff]}, dmac_mc: 1, dmac_bc: 1},
         f_0: {port_idx: 0, cmd: "et 0xbbbb", dmac: "ff:ff:ff:ff:ff:ff"},
         f_1: {port_idx: 0, cmd: "et 0xbbbb", dmac: "fe:ff:ff:ff:ff:ff"}
     },
     {
         txt: "etype/smac",
         vce: {vid: 104, port_idx: 0, type: "ETYPE", etype: {v: [0xcc, 0xcc], m: [0xff, 0xff]}, smac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {port_idx: 0, cmd: "et 0xcccc", smac: "00:01:02:03:04:05"},
         f_1: {port_idx: 0, cmd: "et 0xcccc", smac: "00:01:02:03:04:06"}
     },
     {
         txt: "etype/dmac",
         vce: {vid: 105, port_idx: 1, type: "ETYPE", etype: {v: [0xcc, 0xcc], m: [0xff, 0xff]}, dmac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {port_idx: 1, cmd: "et 0xcccc", dmac: "01:02:03:04:05:06"},
         f_1: {port_idx: 1, cmd: "et 0xcccc", dmac: "01:02:03:04:05:07"}
     },
     {
         txt: "etype/etype",
         vce: {vid: 106, port_idx: 0, type: "ETYPE", etype: {v: [0xab, 0xcd], m: [0xff, 0xff]}},
         f_0: {port_idx: 0, cmd: "et 0xabcd"},
         f_1: {port_idx: 0, cmd: "et 0xabce"}
     },
     {
         txt: "etype/untagged",
         vce: {vid: 110, port_idx: 0, type: "ETYPE", ot: {tagged: 0}},
         f_0: {port_idx: 0, cmd: "et 0xaaaa"},
         f_1: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x8100}}
     },
     {
         txt: "etype/c-tagged",
         vce: {vid: 111, port_idx: 0, type: "ETYPE", ot: {tagged: 1, s_tag: 0}},
         f_0: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x8100}},
         f_1: {port_idx: 0, cmd: "et 0xaaaa"}
     },
     {
         txt: "etype/s-tagged",
         vce: {vid: 112, port_idx: 0, type: "ETYPE", ot: {tagged: 1, s_tag: 1}},
         f_0: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x88a8}},
         f_1: {port_idx: 0, cmd: "et 0xaaaa"}
     },
     {
         txt: "etype/s-custom-tagged",
         vce: {vid: 113, port_idx: 0, type: "ETYPE", ot: {tagged: 1, s_tag: 1}},
         f_0: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x9100}},
         f_1: {port_idx: 0, cmd: "et 0xaaaa"}
     },
     {
         txt: "etype/c-vid",
         vce: {vid: 114, port_idx: 0, type: "ETYPE", ot: {tagged: 1, s_tag: 0, vid: {v: 7, m: 0xfff}}},
         f_0: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x8100, vid: 7}},
         f_1: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x8100, vid: 6}}
     },
     {
         txt: "etype/c-pcp",
         vce: {vid: 115, port_idx: 0, type: "ETYPE", ot: {tagged: 1, s_tag: 0, pcp: {v: 5, m: 0x7}}},
         f_0: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x8100, pcp: 5}},
         f_1: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x8100, pcp: 4}}
     },
     {
         txt: "etype/c-dei",
         vce: {vid: 116, port_idx: 0, type: "ETYPE", ot: {tagged: 1, s_tag: 0, dei: 1}},
         f_0: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x8100, dei: 1}},
         f_1: {port_idx: 0, cmd: "et 0xaaaa", ot: {tpid: 0x8100}}
     },
     {
         txt: "any/c-tagged + s-tagged",
         vce: {vid: 120, port_idx: 0, type: "ANY", ot: {tagged: 1, s_tag: 0}, it: {tagged: 1, s_tag: 1}},
         f_0: {port_idx: 0, cmd: "", ot: {tpid: 0x8100}, it: {tpid: 0x88a8}},
         f_1: {port_idx: 0, cmd: "", ot: {tpid: 0x8100}}
     },
     {
         txt: "any/c-tagged + s-vid",
         vce: {vid: 121, port_idx: 0, type: "ANY", ot: {tagged: 1, s_tag: 0}, it: {tagged: 1, s_tag: 1, vid: {v: 8, m: 0xfff}}},
         f_0: {port_idx: 0, cmd: "", ot: {tpid: 0x8100}, it: {tpid: 0x88a8, vid: 8}},
         f_1: {port_idx: 0, cmd: "", ot: {tpid: 0x8100}, it: {tpid: 0x88a8, vid: 9}}
     },
     {
         txt: "any/c-tagged + s-pcp",
         vce: {vid: 122, port_idx: 0, type: "ANY", ot: {tagged: 1, s_tag: 0}, it: {tagged: 1, s_tag: 1, pcp: {v: 6, m: 0x7}}},
         f_0: {port_idx: 0, cmd: "", ot: {tpid: 0x8100}, it: {tpid: 0x88a8, pcp: 6}},
         f_1: {port_idx: 0, cmd: "", ot: {tpid: 0x8100}, it: {tpid: 0x88a8, pcp: 7}}
     },
     {
         txt: "any/c-tagged + s-dei",
         vce: {vid: 123, port_idx: 0, type: "ANY", ot: {tagged: 1, s_tag: 0}, it: {tagged: 1, s_tag: 1, dei: 1}},
         f_0: {port_idx: 0, cmd: "", ot: {tpid: 0x8100}, it: {tpid: 0x88a8, dei: 1}},
         f_1: {port_idx: 0, cmd: "", ot: {tpid: 0x8100}, it: {tpid: 0x88a8, dei: 0}}
     },
     {
         txt: "llc/llc",
         vce: {vid: 200, port_idx: 0, type: "LLC", llc: {v:[6,5,4,3,2,1], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {port_idx: 0, cmd: "et 46 data hex 060504030201"},
         f_1: {port_idx: 0, cmd: "et 46 data hex 070504030201"}
     },
     {
         txt: "snap/snap",
         vce: {vid: 300, port_idx: 0, type: "SNAP", snap: {v:[1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
         f_0: {port_idx: 0, cmd: "et 46 data hex aaaa03010203040506"},
         f_1: {port_idx: 0, cmd: "et 46 data hex aaaa03010203040507"}
     },
     {
         txt: "ipv4/fragment",
         vce: {vid: 400, port_idx: 0, type: "IPV4", proto: {v: 100, m: 0xff}, fragment: 1},
         f_0: {port_idx: 0, cmd: "ipv4 proto 100 flags 1"},
         f_1: {port_idx: 0, cmd: "ipv4 proto 100"}
     },
     {
         txt: "ipv4/fragofs",
         vce: {vid: 401, port_idx: 0, type: "IPV4", proto: {v: 100, m: 0xff}, fragment: 0},
         f_0: {port_idx: 0, cmd: "ipv4 proto 100"},
         f_1: {port_idx: 0, cmd: "ipv4 proto 100 offset 1"}
     },
     {
         txt: "ipv4/options",
         vce: {vid: 402, port_idx: 0, type: "IPV4", proto: {v: 100, m: 0xff}, options: 1},
         f_0: {port_idx: 0, cmd: "ipv4 proto 100 ihl 6 data hex 01020304"},
         f_1: {port_idx: 0, cmd: "ipv4 proto 100"}
     },
     {
         txt: "ipv4/proto",
         vce: {vid: 403, port_idx: 0, type: "IPV4", proto: {v: 100, m: 0xff}},
         f_0: {port_idx: 0, cmd: "ipv4 proto 100"},
         f_1: {port_idx: 0, cmd: "ipv4 proto 101"}
     },
     {
         txt: "ipv4/dscp",
         vce: {vid: 404, port_idx: 0, type: "IPV4", proto: {v: 102, m: 0xff}, dscp: {v: 42, m: 0xff}},
         f_0: {port_idx: 0, cmd: "ipv4 proto 102 dscp 42"},
         f_1: {port_idx: 0, cmd: "ipv4 proto 102 dscp 43"}
     },
     {
         txt: "ipv4/dscp-range",
         vce: {vid: 405, port_idx: 0, type: "IPV4", proto: {v: 102, m: 0xff}, dscp: {l: 43, h: 44}},
         f_0: {port_idx: 0, cmd: "ipv4 proto 102 dscp 44"},
         f_1: {port_idx: 0, cmd: "ipv4 proto 102 dscp 45"}
     },
     {
         txt: "ipv4/sip",
         vce: {vid: 406, port_idx: 0, type: "IPV4", proto: {v: 102, m: 0xff}, sip: {v: 0x01020304, m: 0xffffffff}},
         f_0: {port_idx: 0, cmd: "ipv4 proto 102 sip 1.2.3.4"},
         f_1: {port_idx: 0, cmd: "ipv4 proto 102 sip 1.2.3.5"}
     },
     {
         txt: "ipv4/dip",
         vce: {vid: 407, port_idx: 1, type: "IPV4", proto: {v: 102, m: 0xff}, dip: {v: 0x05060708, m: 0xffffffff}},
         f_0: {port_idx: 1, cmd: "ipv4 proto 102 dip 5.6.7.8"},
         f_1: {port_idx: 1, cmd: "ipv4 proto 102 dip 5.6.7.9"}
     },
     {
         txt: "ipv4/sport",
         vce: {vid: 408, port_idx: 0, type: "IPV4", proto: {v: 17, m: 0xff}, sport: {v: 0x0304, m: 0xffff}},
         f_0: {port_idx: 0, cmd: "ipv4 udp sport 0x0304"},
         f_1: {port_idx: 0, cmd: "ipv4 udp sport 0x0305"}
     },
     {
         txt: "ipv4/sport-range",
         vce: {vid: 409, port_idx: 0, type: "IPV4", proto: {v: 6, m: 0xff}, sport: {l: 13, h: 14}},
         f_0: {port_idx: 0, cmd: "ipv4 tcp sport 13"},
         f_1: {port_idx: 0, cmd: "ipv4 tcp sport 15"}
     },
     {
         txt: "ipv4/dport",
         vce: {vid: 410, port_idx: 0, type: "IPV4", proto: {v: 17, m: 0xff}, dport: {v: 0x0102, m: 0xffff}},
         f_0: {port_idx: 0, cmd: "ipv4 udp dport 0x0102"},
         f_1: {port_idx: 0, cmd: "ipv4 udp dport 0x0103"}
     },
     {
         txt: "ipv4/dport-range",
         vce: {vid: 411, port_idx: 0, type: "IPV4", proto: {v: 6, m: 0xff}, dport: {l: 11, h: 12}},
         f_0: {port_idx: 0, cmd: "ipv4 tcp dport 12"},
         f_1: {port_idx: 0, cmd: "ipv4 tcp dport 13"}
     },
     {
         txt: "ipv6/proto",
         vce: {vid: 500, port_idx: 0, type: "IPV6", proto: {v: 200, m: 0xff}},
         f_0: {port_idx: 0, cmd: "ipv6 next 200"},
         f_1: {port_idx: 0, cmd: "ipv6 next 201"}
     },
     {
         txt: "ipv6/sip",
         vce: {vid: 501, port_idx: 0, type: "IPV6", sip: {v: [0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4], m: [0,0,0,0,0,0,0,0,0,0,0,0,0xff,0xff,0xff,0xff]}},
         f_0: {port_idx: 0, cmd: "ipv6 sip ::0102:0304"},
         f_1: {port_idx: 0, cmd: "ipv6 sip ::0102:0305"}
     },
     {
         txt: "ipv6/dip",
         vce: {vid: 502, port_idx: 1, type: "IPV6", dip: {v: [0,0,0,0,0,0,0,0,0,0,0,0,5,6,7,8], m: [0,0,0,0,0,0,0,0,0,0,0,0,0xff,0xff,0xff,0xff]}},
         f_0: {port_idx: 1, cmd: "ipv6 dip ::0506:0708"},
         f_1: {port_idx: 1, cmd: "ipv6 dip ::0506:0709"}
     },
     {
         txt: "ipv6/sport",
         vce: {vid: 503, port_idx: 0, type: "IPV6", proto: {v: 17, m: 0xff}, sport: {v: 0x0102, m: 0xffff}},
         f_0: {port_idx: 0, cmd: "ipv6 udp sport 0x0102"},
         f_1: {port_idx: 0, cmd: "ipv6 udp sport 0x0103"}
     },
     {
         txt: "ipv6/sport-range",
         vce: {vid: 504, port_idx: 0, type: "IPV6", proto: {v: 6, m: 0xff}, sport: {l: 15, h: 16}},
         f_0: {port_idx: 0, cmd: "ipv6 tcp sport 15"},
         f_1: {port_idx: 0, cmd: "ipv6 tcp sport 17"}
     },
     {
         txt: "ipv6/dport",
         vce: {vid: 505, port_idx: 0, type: "IPV6", proto: {v: 17, m: 0xff}, dport: {v: 0x0304, m: 0xffff}},
         f_0: {port_idx: 0, cmd: "ipv6 udp dport 0x0304"},
         f_1: {port_idx: 0, cmd: "ipv6 udp dport 0x0305"}
     },
     {
         txt: "ipv6/dport-range",
         vce: {vid: 506, port_idx: 0, type: "IPV6", proto: {v: 6, m: 0xff}, dport: {l: 17, h: 18}},
         f_0: {port_idx: 0, cmd: "ipv6 tcp dport 17"},
         f_1: {port_idx: 0, cmd: "ipv6 tcp dport 16"}
     },
   ]

def vce_tag_set(k, tag)
    vcap_vm_set(k, "vid", tag, :vid)
    vcap_vm_set(k, "pcp", tag, :pcp)
    vcap_bit_set(k, "dei", tag, :dei)
    vcap_bit_set(k, "tagged", tag, :tagged)
    vcap_bit_set(k, "s_tag", tag, :s_tag)
end

def vce_test(t)
    v = t[:vce]
    vid = v[:vid]

    # Make egress port member of VLAN
    port = $ts.dut.port_list[$port_idx_tx]
    $ts.dut.call("mesa_vlan_port_members_set", vid, "#{port}")
        
    # Add VCL rule
    conf = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_" + v[:type])
    conf["id"] = 1
    key = conf["key"]

    k = key["mac"]
    vcap_bit_set(k, "dmac_mc", v, :dmac_mc)
    vcap_bit_set(k, "dmac_bc", v, :dmac_bc)
    vcap_vm_set(k, "smac", v, :smac)
    # Encode DMAC in SMAC field for some platforms
    str = (v[:port_idx] == 1 and $cap_dmac == 0 ? "smac" : "dmac")
    vcap_vm_set(k, str, v, :dmac)

    vce_tag_set(key["tag"], v[:ot])
    vce_tag_set(key["inner_tag"], v[:it])

    # Encode DIP in SIP field for some platforms
    str = (v[:port_idx] == 1 and $cap_dip == 0 ? "sip" : "dip");
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
    when "IPV4"
        k = f["ipv4"]
        vcap_bit_set(k, "fragment", v, :fragment)
        vcap_bit_set(k, "options", v, :options)
        vcap_range_set(k, "dscp", v, :dscp)
        vcap_vm_set(k, "proto", v, :proto)
        vcap_vm_set(k, "sip", v, :sip)
        vcap_vm_set(k, str, v, :dip)
        vcap_range_set(k, "sport", v, :sport)
        vcap_range_set(k, "dport", v, :dport)
    when "IPV6"
        k = f["ipv6"]
        vcap_range_set(k, "dscp", v, :dscp)
        vcap_vm_set(k, "proto", v, :proto)
        vcap_vm_set(k, "sip", v, :sip)
        vcap_vm_set(k, str, v, :dip)
        vcap_range_set(k, "sport", v, :sport)
        vcap_range_set(k, "dport", v, :dport)
    else
    end
    key["port_list"] = "#{$ts.dut.port_list[v[:port_idx]]}"
    conf["action"]["vid"] = vid
    $ts.dut.call("mesa_vce_add", 0, conf)
    $vce_added = true

    for i in 0..1 do
        f = (i == 0 ? t[:f_0] : t[:f_1])
        idx_tx = f[:port_idx]

        # Calculate classified VLAN ID
        vid = (i == 0 ? v[:vid] : 1)

        f_base = "eth"
        if (f.key?:dmac)
            f_base += " dmac #{f[:dmac]}"
        end
        if (f.key?:smac)
            f_base += " smac #{f[:smac]}"
        end
        f_ot = ((f.key?:ot) ? cmd_tag_push(f[:ot]) : "")
        f_it = ((f.key?:it) ? cmd_tag_push(f[:it]) : "")
        f_end = " data pattern cnt 64" # Avoid switch padding after popping tag

        # Name f1 is Tx frame, and also Rx frame if no tag is pushed
        f1 = f_base
        f1 += f_ot
        f1 += f_it
        f1 += " #{f[:cmd]}"
        f1 += f_end

        # Name f2 is Rx frame if a tag is pushed
        f2 = f_base
        f2 += cmd_tag_push({tpid: 0x8100, vid: vid})
        f2 += f_ot
        f2 += f_it
        f2 += " #{f[:cmd]}"
        f2 += f_end

        cmd = "sudo ef name f1 #{f1} name f2 #{f2} tx #{$ts.pc.p[idx_tx]} name f1"
        $ts.dut.p.each_index do |idx_rx|
            cmd += " rx #{$ts.pc.p[idx_rx]}"
            tagged = (idx_rx == $port_idx_tx)
            if (idx_rx != idx_tx and (tagged or vid == 1))
                cmd += " name #{tagged ? "f2" : "f1"}"
            end
        end
        t_i("Frame[#{i}], classified VID: #{vid}")
        $ts.pc.run(cmd)
    end
end

epid = cap_get("PACKET_IFH_EPID")
# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    # Calculate list of keys to test
    skip_double_tag = false
    skip_normal = false
    skip_ip_addr = false
    skip_mac_ip_addr = false
    vce = t[:vce]

    if (vce.key?:smac or vce.key?:dmac)
        # SMAC/DMAC matching not possible for double_tag
        skip_double_tag = true
    end

    if (vce.key?:etype or vce.key?:llc or vce.key?:snap)
        # ETYPE/LLC/SNAP matching not possible for double_tag
        skip_double_tag = true
    end

    if (vce.key?:type and (vce[:type] == "IPV4" or vce[:type] == "IPV6"))
        # IP matching not possible for double_tag
        skip_double_tag = true
    end

    if (vce.key?:sport or vce.key?:dport)
        # SPORT/DPORT matching not possible for double_tag/ip_addr
        skip_double_tag = true
        skip_ip_addr = true
    end

    if (epid == 7 or epid == 9 or epid == 11)
        # Jaguar-2/Serval-T/FireAnt
    elsif (epid == 10 or epid == 13)
        # Ocelot/Maserati
        if (vce.key?:it)
            # Inner tag not possible for normal/ip_addr
            skip_normal = true
            skip_ip_addr = true
        end
    else
        # Luton26, key not supported
        skip_double_tag = true
        skip_ip_addr = true
        skip_mac_ip_addr = true
        if (vce.key?:it)
            # Inner tag matching not possible
            skip_normal = true
        end
    end

    key_list = []
    if (!skip_double_tag)
        key_list << "DOUBLE_TAG"
    end
    if (!skip_normal)
        key_list << "NORMAL"
    end
    if (!skip_ip_addr)
        key_list << "IP_ADDR"
    end
    if (!skip_mac_ip_addr)
        key_list << "MAC_IP_ADDR"
    end

    port = $ts.dut.p[vce[:port_idx]]
    conf = nil
    key_list.each do |k|
        txt = (t[:txt] + " (#{k})")
        test txt do
            if ($vce_added)
                # Delete VCE before setting up port key
                $vce_added = false
                $ts.dut.call("mesa_vce_del", 1)
            end
            if (conf == nil)
                conf = $ts.dut.call("mesa_vcl_port_conf_get", port)
            end
            conf["key_type"] = ("MESA_VCAP_KEY_TYPE_" + k)
            $ts.dut.call("mesa_vcl_port_conf_set", port, conf)
            vce_test(t)
        end
    end
end

test_summary
