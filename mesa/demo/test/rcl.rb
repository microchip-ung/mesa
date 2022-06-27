#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if RCL supported
cap_check_exit("L2_RCL")

$idx_tx  = 0 # PC Tx port
$idx_rx  = 1 # PC Rx port, normal forwarding
$idx_ifh = 2 # PC Rx port, with IFH
$idx_rtp = 3 # PC Rx port, RTP forwarding
$port_map = nil

# Each entry in the test table has these items:
# 1: Text string used to name the test step
# 2: VID (default 0 - untagged) and/or PCP (default all) enabled for RTC
# 3: RCL, 1 or 2 RCEs to be added, by default forwarding to $idx_rtp
# 4: Frame[0] matching RCEs, forwarded based on RCE actions
# 5: Frame[1] not matching RCEs, forwarded normally.

test_table =
[
    {
        txt: "key/port_no",
        rcl: [{}],
        f_0: {},
        f_1: {idx_tx: $idx_rx, idx_rx: $idx_tx}
    },
    {
        txt: "key/dmac",
        rcl: [{mac: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}}],
        f_0: {dmac: "01:02:03:04:05:06"},
        f_1: {dmac: "01:02:03:04:05:07"}
    },
    {
        txt: "key/smac",
        rcl: [{idx_rx: $idx_ifh}, # Match any DMAC, redirect to IFH port
              {mac: {v: [0,1,2,3,4,5], m: [0xff,0xff,0xff,0xff,0xff,0xff]}, smac: true, rtp_id: 31}],
        f_0: {dmac: "01:02:03:04:05:06", smac: "00:01:02:03:04:05", ifh: "rtp-id 31"},
        f_1: {dmac: "01:02:03:04:05:06", smac: "00:01:02:03:04:06", ifh: "rtp-id 0", idx_rx: $idx_ifh}
    },
    {
        txt: "key/untagged",
        rcl: [{tagged: 0}],
        f_0: {},
        f_1: {vid: 4096} # Priority-tagged
    },
    {
        txt: "key/tagged",
        rcl: [{tagged: 1}],
        f_0: {vid: 4096}, # Priority-tagged
        f_1: {}
    },
    {
        txt: "key/vid",
        vid: 1000,
        rcl: [{}],
        f_0: {},
        f_1: {vid: 1001}
    },
    {
        txt: "key/pcp",
        vid: 15,
        pcp: 7,
        rcl: [{}],
        f_0: {},
        f_1: {pcp: 4}
    },
    {
        txt: "key/etype",
        rcl: [{etype: "PROFINET"}],
        f_0: {etype: 0x8892},
        f_1: {etype: 0x8891}
    },
    {
        txt: "key/profinet-frame-id",
        rcl: [{etype: "PROFINET", frame_id: {v: [5,6], m: [0xff,0xff]}}],
        f_0: {etype: 0x8892, cmd: "data hex 0506"},
        f_1: {etype: 0x8892, cmd: "data hex 0507"}
    },
    {
        txt: "key/opc_ua-pub-id", # Little-endian PublisherId in frame
        rcl: [{etype: "OPC_UA", publisher_id: {v: [0x07,0x08], m: [0xff,0xff]}}],
        f_0: {cmd: "opc-ua pub-id 0x0708"},
        f_1: {cmd: "opc-ua pub-id 0x0709"}
    },
    {
        txt: "key/opc_ua-wg-id", # Little-endian WriterGroupId in frame
        rcl: [{etype: "OPC_UA", writer_group_id: {v: [0x0a,0x0b], m: [0xff,0xff]}}],
        f_0: {cmd: "opc-ua wg-id 0x0a0b"},
        f_1: {cmd: "opc-ua wg-id 0x0a0c"}
    },
    {
        txt: "act/rtp_id",
        rcl: [{idx_rx: $idx_ifh, rtp_id: 17}],
        f_0: {ifh: "rtp-id 17"},
        f_1: {vid: 1}
    },
    {
        txt: "act/rtp_sub_id",
        rcl: [{idx_rx: $idx_ifh, rtp_sub_id: true}],
        f_0: {ifh: "rtp-subid 1"},
        f_1: {vid: 1}
    },
    {
        txt: "act/rtp_inbound",
        rcl: [{idx_rx: $idx_ifh, rtp_inbound: true}],
        f_0: {ifh: "rte-inb-upd 1"},
        f_1: {vid: 1}
    },
    {
        txt: "act/llct",
        rcl: [{llct: $idx_rtp}],
        f_0: {},
        f_1: {vid: 1}
    },
]

test "conf" do
    # Get port map
    port_cnt = cap_get("PORT_CNT")
    $port_map = $ts.dut.call("mesa_port_map_get", port_cnt)

    # Include only two ports in default PVLAN
    port_list = port_idx_list_str([$idx_tx, $idx_rx])
    $ts.dut.call("mesa_pvlan_port_members_set", 0, port_list)

    # Enable IFH
    port = $ts.dut.p[$idx_ifh]
    conf = $ts.dut.call("mesa_port_ifh_conf_get", port)
    conf["ena_xtr_header"] = true
    $ts.dut.call("mesa_port_ifh_conf_set", port, conf)
end

$rce_cnt = 0

def rce_set(k, name, v, fld)
    if (v.key?(fld))
        k[name] = v[fld]
    end
end

def rte_test(t)
    # Add RCL VID
    vid = ((t.key?:vid) ? t[:vid] : 0)
    conf = {}
    conf["pcp"] = []
    for i in 0..7 do
        pcp = ((t.key?:pcp) ? t[:pcp] : i)
        conf["pcp"][i] = (i == pcp ? true :false)
    end
    $ts.dut.call("mesa_rcl_vid_add", vid, conf)

    # Delete previous RCE not to be used
    rcl = t[:rcl]
    if ($rce_cnt > rcl.length)
        $ts.dut.call("mesa_rce_del", 2)
    end
    $rce_cnt = rcl.length

    # Add RCEs
    idx_rx = $idx_rtp
    rcl.each_with_index do |v, idx|
        if (v.key?:idx_rx)
            idx_rx = v[:idx_rx]
        end
        rce = $ts.dut.call("mesa_rce_init")
        rce["id"] = (idx + 1)
        k = rce["key"]
        port = $ts.dut.p[$idx_tx]
        k["port_no"] = port
        rce_set(k , "smac", v, :smac)
        vcap_vm_set(k, "mac", v, :mac)
        vcap_bit_set(k, "tagged", v, :tagged)
        k["vid"] = vid
        k["etype"] = ("MESA_RCL_ETYPE_" + ((v.key?:etype) ? v[:etype] : "ANY"))
        vcap_vm_set(k, "frame_id", v, :frame_id)
        vcap_vm_set(k, "publisher_id", v, :publisher_id)
        vcap_vm_set(k, "writer_group_id", v, :writer_group_id)
        a = rce["action"]
        rce_set(a, "rtp_id", v, :rtp_id)
        rce_set(a, "rtp_sub_id", v, :rtp_sub_id)
        rce_set(a, "rtp_inbound", v, :rtp_inbound)
        a["port_enable"] = true
        if (v.key?:llct and $port_map[port]["chip_port"] < 2)
            # Only ingress port 0 and 1 support LLCT
            a["llct_enable"] = true
            a["llct_port_no"] = $ts.dut.p[v[:llct]]
        else
            a["port_list"] = "#{$ts.dut.p[(v.key?:idx_rx) ? v[:idx_rx] : $idx_rtp]}"
        end
        rce = $ts.dut.call("mesa_rce_add", 0, rce)
    end

    # Frame test
    for i in 0..1 do
        f = (i == 0 ? t[:f_0] : t[:f_1])
        f1 = "eth"
        # Unicast DMAC by default
        f1 += " dmac #{(f.key?:dmac) ? f[:dmac] : "10"}"
        if (f.key?:smac)
            f1 += " smac #{f[:smac]}"
        end
        vid = ((f.key?:vid) ? f[:vid] : ((t.key?:vid) ? t[:vid] : 0))
        if (vid > 0)
            pcp = ((f.key?:pcp) ? f[:pcp] : ((t.key?:pcp) ? t[:pcp] : 0))
            f1 += cmd_tag_push({tpid: 0x8100, vid: (vid & 4095), pcp: pcp})
        end
        if (f.key?:etype)
            f1 += " et #{f[:etype]}"
        end
        if (f.key?:cmd)
            f1 += " #{f[:cmd]}"
        end
        f1 += " data pattern cnt 48"
        f2 = ""
        if (f.key?:idx_rx)
            idx_rx = f[:idx_rx]
        elsif (i == 1)
            # Normal forwarding
            idx_rx = $idx_rx
        end
        if (idx_rx == $idx_ifh)
            f2 = cmd_rx_ifh_push
            if (f.key?:ifh)
                f2 += " #{f[:ifh]}"
            end
        end
        f2 += " #{f1}"
        idx_tx = ((f.key?:idx_tx) ? f[:idx_tx] : $idx_tx)
        cmd = "sudo ef name f1 #{f1} name f2 #{f2}"
        cmd += " tx #{$ts.pc.p[idx_tx]} name f1"
        [0, 1, 2, 3].each do |idx|
            if (idx != idx_tx)
                cmd += " rx #{$ts.pc.p[idx]}"
                if (idx == idx_rx)
                    cmd += " name f2"
                end
            end
        end
        $ts.pc.run(cmd)
    end
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        rte_test(t)
    end
end

test_summary

#$ts.dut.run("mesa-cmd deb api ci vx")
