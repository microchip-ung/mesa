#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if index table supported
cap_check_exit("L2_MAC_INDEX_TABLE")

#---------- Configuration -----------------------------------------------------

test "setup vlan-aware" do
    $ts.dut.p.each do |port|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["ingress_filter"] = true
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end
end

# Test table
$test_table =
[
    {
        txt: "error-unlocked",
        mac: [{locked: false, err: 1}]
    },
    {
        txt: "error-oui",
        mac: [{oui: 1},{oui: 2, err: 1}]
    },
    {
        txt: "error-idx",
        mac: [{idx: 8192, err: 1}]
    },
    {
        txt: "error-full",
        mac: [{vid: 10},{vid: 30},{vid: 20},{vid: 40},{vid: 50, err: 1}]
    },
    {
        txt: "entry-overwrite",
        mac: [{index_table: false},{dst: [1,3], del: 0}]
    },
    {
        txt: "get-next",
        get_next: 1,
        mac: [{vid: 10},{vid: 20, idx: 10},{vid: 20, idx: 15, index_table: false},{vid: 20, idx: 20},{vid: 30}]
    },
    {
        txt: "forward",
        mac: [{vid: 10, oui: 0x020406, idx: 0x102, dst: [1,2] }],
        frm: [{dmac: "02:04:06:00:01:02", vid: 10, idx_tx: 0, idx_rx: [1,2]}]
    },
]

def fld_get(m, fld, val = 0)
    if (m != nil and m.key?(fld))
        val = m[fld]
    end
    val
end

def fld_vid_mac_get(m)
    val = { mac: { addr: [] } }
    val[:vid] = fld_get(m, :vid, 1)
    oui = fld_get(m, :oui)
    idx = fld_get(m, :idx)
    addr = val[:mac][:addr]
    3.times do |i|
        n = (16 - 8 * i)
        addr[i] = ((oui >> n) & 0xff)
        addr[i + 3] = ((idx >> n) & 0xff)
    end
    val
end

def mac_test(t)
    mac_list = t[:mac]
    cmd = ""

    # Add entries
    mac_list.each do |m|
        e = {}
        e[:vid_mac] = fld_vid_mac_get(m)
        str = ""
        dst = fld_get(m, :dst, [])
        dst.each do |i|
            if (str != "")
                str += ","
            end
            str += "#{$ts.dut.p[i]}"
        end
        e[:destination] = str
        e[:copy_to_cpu] = fld_get(m, :cpu_copy, false)
        e[:copy_to_cpu_smac] = false
        e[:locked] = fld_get(m, :locked, true)
        e[:index_table] = fld_get(m, :index_table, true)
        e[:aged] = false
        e[:cpu_queue] = 0

        err = fld_get(m, :err)
        if (err > 0)
            $ts.dut.call_err("mesa_mac_table_add", e)
        else
            $ts.dut.call("mesa_mac_table_add", e)
        end
    end

    # Frame forwarding test
    frm = fld_get(t, :frm, [])
    frm.each do |f|
        # Add all ports to VLAN
        vid = f[:vid]
        port_list = $ts.dut.p.join(",")
        $ts.dut.call("mesa_vlan_port_members_set", vid, port_list)

        cmd = "eth dmac #{f[:dmac]}"
        cmd += cmd_tag_push({tpid: 0x8100, vid: vid})
        cmd += " data pattern cnt 64"
        run_ef_tx_rx_cmd($ts, f[:idx_tx], f[:idx_rx], cmd)
        f[:cmd] = cmd
    end

    # Get-next test
    if (t[:get_next])
        vid_mac = fld_vid_mac_get({vid: 0})
        mac_list.each do |m|
            e = $ts.dut.call("mesa_mac_table_get_next", vid_mac)
            vid_mac = e["vid_mac"]
            check_counter("next-vid", vid_mac["vid"], m[:vid])
            idx = 0
            3.times do |i|
                idx = ((idx << 8) + vid_mac["mac"]["addr"][i + 3])
            end
            check_counter("next-idx", idx, fld_get(m, :idx))
        end
    end

    # Delete entries
    mac_list.each do |m|
        vid_mac = fld_vid_mac_get(m)
        err = fld_get(m, :err)
        del = fld_get(m, :del, 1 - err)
        if (del > 0)
            $ts.dut.call("mesa_mac_table_del", vid_mac)
        end
    end

    # Frame flooding test
    frm.each do |f|
        idx_tx = f[:idx_tx]
        run_ef_tx_rx_cmd($ts, idx_tx, [0,1,2,3] - [idx_tx], f[:cmd])
    end
end

$test_table.each do |t|
    test t[:txt] do
        mac_test(t)
    end
end

test "dump" do
    break
    $ts.dut.run("mesa-cmd debug api mac_table")
    $ts.dut.run("mesa-cmd mac dump")
end
