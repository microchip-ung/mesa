#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

test_table = [
    {
        txt: "mirror-ingress-port",
        mir: {idx: 3},
        igr: {idx: 0},
        frm: [
            # Learn frame
            {tx: {idx: 1, eth: "smac 11"}, rx: {idx: [0,2]}},
            # Ingress mirror
            {tx: {idx: 0, eth: "dmac 11 smac 10"}, rx: {idx: [1,3]}}
        ]
    },
    {
        txt: "mirror-egress-port",
        mir: {idx: 0},
        egr: {idx: 3},
        frm: [
            # Learn frame
            {tx: {idx: 3, eth: "smac 13"}, rx: {idx: [1,2]}},
            # Egress mirror
            {tx: {idx: 2, eth: "dmac 13 smac 12"}, rx: {idx: [0,3]}}
        ]
    },
    {
        txt: "mirror-ingress-vlan",
        mir: {idx: 1},
        vln: {vid: 1, mirror: true, idx: []},
        frm: [
            # VLAN mirror
            {tx: {idx: 3}, rx: {idx: [1]}}
        ]
    },
    {
        txt: "mirror-acl",
        mir: {idx: 3},
        ace: {id: 1, idx: 0, type: "MESA_ACE_TYPE_IPV6"},
        frm: [
            # Learn frame
            {tx: {idx: 1, eth: "smac 11"}, rx: {idx: [0,2]}},
            # ACL
            {tx: {idx: 0, eth: "dmac 11 ipv6"}, rx: {idx: [1,3]}}
        ]
    },
    {
        txt: "mirror-tag",
        cap: "L2_MIRROR_TAG",
        mir: {idx: 3, tag: "MESA_MIRROR_TAG_S", vid: 10, pcp: 7},
        igr: {idx: 0},
        vln: {vid: 1, mirror: false, idx: []},
        frm: [
            # Ingress mirror
            {tx: {idx: 0, eth: "data pattern cnt 64"},
             rx: {idx: [3], eth: nil, tag: {tpid: 0x88a8, vid: 10, pcp: 7}}}
        ]
    },
    {
        txt: "mirror-cpu-ingress",
        mir: {idx: 3},
        cpu: {igr: true},
        npi: {idx: 0},
        frm: [
            # CPU ingress mirror
            {tx: {idx: 0, ifh: {idx: 2}}, rx: {idx: [2,3]}}
        ]
    },
    {
        txt: "mirror-cpu-egress",
        mir: {idx: 3},
        cpu: {egr: true},
        frm: [
            # CPU egress mirror
            {tx: {idx: 0, eth: "dmac 01:80:c2:00:00:00"}, rx: {idx: [3]}}
        ]
    },
    {
        txt: "mirror-egress-cpu-tx",
        mir: {idx: 0},
        egr: {idx: 1},
        npi: {idx: 2},
        frm: [
            # Egress mirror of frame transmitted by CPU
            {tx: {idx: 2, ifh: {idx: 1}}, rx: {idx: [0,1]}}
        ]
    },
]

def cmd_frame(eth, tag)
    cmd = "eth"
    if (eth != nil)
        cmd += " #{eth}"
    end
    if (tag != nil)
        tpid = fld_get(tag, :tpid, 0x8100)
        cmd += cmd_tag_push({tpid: tpid, vid: tag[:vid], pcp: tag[:pcp]})
        cmd += " data pattern cnt 64"
    end
    return cmd
end

def mirror_test(t)
    # Capability check
    cap = t[:cap]
    if (cap != nil and cap_get(cap) == 0)
        return
    end

    # Mirror configuration
    mir = t[:mir]
    c = $ts.dut.call("mesa_mirror_conf_get")
    port_none = c["port_no"]
    c["port_no"] = $ts.dut.p[mir[:idx]]
    tag = mir[:tag]
    if (tag != nil)
        c["tag"] = tag
        c["vid"] = mir[:vid]
        c["pcp"] = mir[:pcp]
    end
    $ts.dut.call("mesa_mirror_conf_set", c)

    # NPI port
    npi = t[:npi]
    if (npi != nil)
        c = $ts.dut.call("mesa_npi_conf_get")
        c["enable"] = true
        c["port_no"] = $ts.dut.p[npi[:idx]]
        $ts.dut.call("mesa_npi_conf_set", c)
    end

    # Ingress mirroring
    igr = t[:igr]
    if (igr != nil)
        $ts.dut.call("mesa_mirror_ingress_ports_set", "#{$ts.dut.p[igr[:idx]]}")
    end

    # Egress mirroring
    egr = t[:egr]
    if (egr != nil)
        $ts.dut.call("mesa_mirror_egress_ports_set", "#{$ts.dut.p[egr[:idx]]}")
    end

    # CPU mirroring
    cpu = t[:cpu]
    if (cpu != nil)
        if (cpu[:igr] != nil)
            $ts.dut.call("mesa_mirror_cpu_ingress_set", true)
        end
        if (cpu[:egr] != nil)
            $ts.dut.call("mesa_mirror_cpu_egress_set", true)
        end
    end

    # VLAN mirroring
    vlan = t[:vln]
    old = nil
    if (vlan != nil)
        vid = vlan[:vid]
        c = $ts.dut.call("mesa_vlan_vid_conf_get", vid)
        c["mirror"] = vlan[:mirror]
        $ts.dut.call("mesa_vlan_vid_conf_set", vid, c)
        old = $ts.dut.call("mesa_vlan_port_members_get", vid)
        $ts.dut.call("mesa_vlan_port_members_set", vid, port_idx_list_str(vlan[:idx]))
    end

    # ACL mirroring
    ace = t[:ace]
    if (ace != nil)
        c = $ts.dut.call("mesa_ace_init", ace[:type])
        c["id"] = ace[:id]
        c["port_list"] = "#{$ts.dut.p[ace[:idx]]}"
        c["action"]["mirror"] = true
        $ts.dut.call("mesa_ace_add", 0, c)
    end

    # Frame test
    frm = fld_get(t, :frm, [])
    frm.each do |f|
        cmd = "ef name f_tx "
        tx = f[:tx]
        eth = tx[:eth]
        tag = tx[:tag]
        ifh = tx[:ifh]
        if (ifh != nil)
            cmd += cmd_tx_ifh_push({"dst_port": $ts.dut.p[ifh[:idx]]})
            eth = "data pattern cnt 64"
        end
        cmd += cmd_frame(eth, tag)
        cmd += " name f_rx "
        rx = f[:rx]
        eth = fld_get(rx, :eth, eth)
        tag = fld_get(rx, :tag, tag)
        cmd += cmd_frame(eth, tag)
        [0,1,2,3].each do |idx|
            if (idx == tx[:idx])
                cmd += " tx #{$ts.pc.p[idx]} name f_tx"
            else
                cmd += " rx #{$ts.pc.p[idx]}"
                if (rx[:idx].include?idx)
                    cmd += " name f_rx"
                end
            end
        end
        $ts.pc.try(cmd)
    end

    # Return here when debugging a test
    #return

    # Restore mirror configuration
    c = $ts.dut.call("mesa_mirror_conf_get")
    c["port_no"] = port_none
    c["tag"] = "MESA_MIRROR_TAG_NONE"
    $ts.dut.call("mesa_mirror_conf_set", c)

    # Restore NPI configuration
    npi = t[:npi]
    if (npi != nil)
        c = $ts.dut.call("mesa_npi_conf_get")
        c["enable"] = false
        $ts.dut.call("mesa_npi_conf_set", c)
    end

    # Restore ingress mirroring
    if (igr != nil)
        $ts.dut.call("mesa_mirror_ingress_ports_set", "")
    end

    # Restore egress mirroring
    if (egr != nil)
        $ts.dut.call("mesa_mirror_egress_ports_set", "")
    end

    # Restore CPU mirroring
    if (cpu != nil)
        if (cpu[:igr] != nil)
            $ts.dut.call("mesa_mirror_cpu_ingress_set", false)
        end
        if (cpu[:egr] != nil)
            $ts.dut.call("mesa_mirror_cpu_egress_set", false)
        end
    end

    # Restore VLAN mirroring
    if (vlan != nil)
        vid = vlan[:vid]
        c = $ts.dut.call("mesa_vlan_vid_conf_get", vid)
        c["mirror"] = false
        $ts.dut.call("mesa_vlan_vid_conf_set", vid, c)
        $ts.dut.call("mesa_vlan_port_members_set", vid, old)
    end

    # Remove ACL rule
    if (ace != nil)
        ace = $ts.dut.call("mesa_ace_del", ace[:id])
    end
end

sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        mirror_test(t)
    end
end
test_summary

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api mirror")
end
