#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

test "config-vlan", false do
    $ts.dut.call("mesa_vlan_port_members_set", 1, port_idx_list_str([0, 1]))
end

test_table =
[
    {
        txt: "no-tce",
        tab: [[{idx_tx: 0},
               {idx_rx: 1}]]
    },
    {
        txt: "tce-cpu",
        cap: "ACT_FWD",
        grp: [0, 1],
        tcl: [{idx: 1, fwd: "CPU", cpu_queue: 6}], 
        npi: {idx: 2, cpu_queue: 6}, 
        tab: [[{idx_tx: 0},
               {idx_rx: 2, ifh: {port_idx: 1}}]]
    },
    {
        txt: "tce-loopback",
        cap: "ACT_FWD",
        grp: [0, 1],
        tcl: [{idx: 1, fwd: "LB"}], 
        tab: [[{idx_tx: 0, frm: "dmac 2 smac 1"},
               {idx_rx: 0, frm: "dmac 1 smac 2"}]]
    },
    {
        txt: "tce-oam",
        cap: "KEY_OAM",
        grp: [0, 1],
        vce: {idx: 0, type: "ETYPE", oam: "UNTAGGED"},
        # Match MEL XX11111, meaning value 0-5
        tcl: [{idx: 1, oam: "1", fwd: "LB", mel_val: 0x1f, mel_msk: 0x1f}], 
        tab: [[{idx_tx: 0, frm: "dmac 2 smac 1 oam-ccm mel 5"},
               {idx_rx: 0, frm: "dmac 1 smac 2 oam-ccm mel 5"}],
              [{idx_tx: 0, frm: "dmac 2 smac 1 oam-ccm mel 4"},
               {idx_rx: 1, frm: "dmac 2 smac 1 oam-ccm mel 4"}]]
    },
    {
        txt: "tce-iflow",
        cap: "ACT_FWD",
        grp: [0, 1],
        vce: {idx: 0, type: "IPV4"},
        tcl: [{idx: 1, fwd: "LB"}], 
        tab: [[{idx_tx: 0, frm: "dmac 2 smac 1 ipv4"},
               {idx_rx: 0, frm: "dmac 1 smac 2 ipv4"}],
              [{idx_tx: 0, frm: "dmac 2 smac 1"},
               {idx_rx: 1, frm: "dmac 2 smac 1"}]]
    },
]

def tcl_test(t)
    # Capability check
    cap = t[:cap]
    if (cap != nil && cap_get("L2_TCL_" + cap) == 0)
        return
    end

    # Add VCEs
    vce = t[:vce]
    iflow = nil
    if (vce != nil)
        iflow = $ts.dut.call("mesa_iflow_alloc")
        idx = fld_get(vce, :idx)
        type = fld_get(vce, :type, "ANY")
        oam = fld_get(vce, :oam, "NONE")
        vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_" + type)
        vce["id"] = 1
        vce["key"]["port_list"] = "#{$ts.dut.p[idx]}"
        action = vce["action"]
        action["oam_detect"] = ("MESA_OAM_DETECT_" + oam)
        action["flow_id"] = iflow 
        $ts.dut.call("mesa_vce_add", 0, vce)
    end

    # Add TCEs
    tcl = fld_get(t, :tcl, [])
    tcl.each do |e|
        id = fld_get(e, :id, 1)
        e[:id] = id
        tce = $ts.dut.call("mesa_tce_init")
        tce["id"] = id
        key = tce["key"]
        idx = fld_get(e, :idx)
        key["port_list"] = "#{$ts.dut.p[idx]}"
        key["vid"] = fld_get(e, :vid, 1)
        if (iflow != nil)
            key["flow_enable"] = true
            key["flow_id"] = iflow
        end
        key["oam"] = ("MESA_VCAP_BIT_" + fld_get(e, :oam, "ANY"))
        key["mel"]["value"] = fld_get(e, :mel_val)
        key["mel"]["mask"] = fld_get(e, :mel_msk)
        action = tce["action"]
        action["fwd"] = ("MESA_TCE_FWD_" + fld_get(e, :fwd, "DEFAULT"))
        action["cpu_queue"] = fld_get(e, :cpu_queue)
        $ts.dut.call("mesa_tce_add", 0, tce)
    end

    # NPI port
    npi = t[:npi]
    if (npi != nil)
        idx = fld_get(npi, :idx)
        conf = $ts.dut.call("mesa_npi_conf_get")
        conf["enable"] = true
        conf["port_no"] = $ts.dut.p[idx]
        $ts.dut.call("mesa_npi_conf_set", conf)

        cpu_queue = fld_get(npi, :cpu_queue)
        conf = $ts.dut.call("mesa_packet_rx_conf_get")
        conf["queue"][cpu_queue]["npi"]["enable"] = true
        $ts.dut.call("mesa_packet_rx_conf_set", conf)
    end

    # Frame test
    tab = fld_get(t, :tab, [])
    tab.each do |entry|
        cmd = "ef"
        cmd_add = ""
        idx_list = []
        entry.each do |e|
            idx = e[:idx_tx]
            dir = "tx"
            if (idx == nil)
                idx = e[:idx_rx]
                idx_list.push(idx)
                dir = "rx"
            end
            name = "f_#{dir}_#{idx}"
            cmd += " name #{name} "
            ifh = e[:ifh]
            if (ifh != nil)
                cmd += cmd_rx_ifh_push(ifh)
            end
            cmd += "eth"
            frm = e[:frm]
            if (frm != nil)
                cmd += " #{frm}"
            end
            cmd += " data pattern cnt 46"
            cmd_add += " #{dir} #{$ts.pc.p[idx]} name #{name}" 
        end
        [0, 1].each do |idx|
            if (!idx_list.include?idx)
                cmd += " rx #{$ts.pc.p[idx]}"
            end
        end
        $ts.pc.try(cmd + cmd_add)
    end

    # Return here when debugging a test
    #return

    # Free ingress flow
    if (iflow != nil)
        $ts.dut.call("mesa_iflow_free", iflow)
    end

    # Delete VCE
    if (vce != nil)
        $ts.dut.call("mesa_vce_del", vce["id"])
    end

    # Delete TCEs
    tcl.each do |e|
        $ts.dut.call("mesa_tce_del", e[:id])
    end

    # Disable NPI port
    if (npi != nil)
        conf = $ts.dut.call("mesa_npi_conf_get")
        conf["enable"] = false
        $ts.dut.call("mesa_npi_conf_set", conf)

        # Redirect CPU queue to NPI port
        cpu_queue = fld_get(npi, :cpu_queue)
        conf = $ts.dut.call("mesa_packet_rx_conf_get")
        conf["queue"][cpu_queue]["npi"]["enable"] = false
        $ts.dut.call("mesa_packet_rx_conf_set", conf)
    end
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    test t[:txt] do
        next if (t[:sel] != sel)
        tcl_test(t)
    end
end

test_summary

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api cil vx action 4")
end

