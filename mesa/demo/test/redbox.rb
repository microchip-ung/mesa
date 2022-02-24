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

#---------- Configuration -----------------------------------------------------

# Each entry in the test table has these fields:
# 1: Text string printed during test
# 2: Configuration of RedBox and switch
# 3: Basic frame properties (optional)
# 4: Forwarding properties for each port (A/B/C/D)
test_table =
[
    {
        txt: "HSR-SAN, port A to port B/C/D",
        cfg: {mode: "HSR_SAN"},
        fwd: [{idx_tx: $idx_a, hsr: {net_id: 2, lan_id: 1}},
              {idx: $idx_b, hsr: {net_id: 2, lan_id: 1}},
              {idx: $idx_c},
              {idx: $idx_d}]
    },
    {
        txt: "HSR-SAN, port B to port A/C/D",
        cfg: {mode: "HSR_SAN"},
        fwd: [{idx_tx: $idx_b, hsr: {net_id: 2, lan_id: 1}},
              {idx: $idx_a, hsr: {net_id: 2, lan_id: 1}},
              {idx: $idx_c},
              {idx: $idx_d}]
    },
    {
        txt: "HSR-SAN, port C to port A/B/D",
        cfg: {mode: "HSR_SAN", net_id: 7},
        fwd: [{idx_tx: $idx_c},
              {idx: $idx_a, hsr: {net_id: 7}},
              {idx: $idx_b, hsr: {net_id: 7}},
              {idx: $idx_d}]
    },
    {
        txt: "HSR-SAN, port D to port A/B/C",
        cfg: {mode: "HSR_SAN", net_id: 7},
        fwd: [{idx_tx: $idx_d},
              {idx: $idx_a, hsr: {net_id: 7}},
              {idx: $idx_b, hsr: {net_id: 7}},
              {idx: $idx_c}]
    },
    {
        txt: "HSR-SAN with VLANs, port A to port B/C",
        cfg: {mode: "HSR_SAN",
              vlan: {vid: 10, list: [{idx: $idx_a, type: "C", uvid: 0},
                                     {idx: $idx_c, pvid: 10, uvid: 10}]}},
        fwd: [{idx_tx: $idx_a, vid: 10, hsr: {}},
              {idx: $idx_b, vid: 10, hsr: {}},
              {idx: $idx_c}]
    },
    {
        txt: "HSR-SAN with VLANs, port D to port A/B",
        cfg: {mode: "HSR_SAN", net_id: 6,
              vlan: {vid: 10, list: [{idx: $idx_a, type: "C", uvid: 0},
                                     {idx: $idx_d, pvid: 10, uvid: 10}]}},
        fwd: [{idx_tx: $idx_d},
              {idx: $idx_a, vid: 10, hsr: {net_id: 6}},
              {idx: $idx_b, vid: 10, hsr: {net_id: 6}}]
    },
    {
        txt: "PRP-SAN, port A to port C/D",
        cfg: {mode: "PRP_SAN"},
        fwd: [{idx_tx: $idx_a, prp: {lan_id: 0}},
              {idx: $idx_c},
              {idx: $idx_d}]
    },
    {
        txt: "PRP-SAN, port B to port C/D",
        cfg: {mode: "PRP_SAN"},
        fwd: [{idx_tx: $idx_b, prp: {lan_id: 1}},
              {idx: $idx_c},
              {idx: $idx_d}],
    },
    {
        txt: "PRP-SAN, port A wrong LAN",
        cfg: {mode: "PRP_SAN"},
        fwd: [{idx_tx: $idx_a, prp: {lan_id: 1}},
              {idx: $idx_c, prp: {lan_id: 1}},
              {idx: $idx_d, prp: {lan_id: 1}}],
        cnt: [{port: "port_a", name: "rx_wrong_lan", val: 1}],
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
    conf = $ts.dut.call("mesa_rb_conf_set", $rb_id, conf)

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

    # Clear counters
    $ts.dut.call("mesa_rb_counters_clear", $rb_id)
    exp = $ts.dut.call("mesa_rb_counters_get", $rb_id)

    # Frame test
    idx_name = []
    $ts.dut.p.each_index do |idx|
        s = (idx == $idx_a ? "a" : idx == $idx_b ? "b" : idx == $idx_c ? "c" : "d")
        idx_name[idx] = s
    end
    f = fld_get(t, :frm, {})
    len = fld_get(f, :len, 46)
    cmd = " sudo ef"
    cmd_add = ""
    idx_list = []
    idx_tx = nil
    smac = 1
    fwd = fld_get(t, :fwd, [])
    fwd.each_with_index do |e, i|
        idx = e[:idx_tx]
        dir = "rx"
        if (idx == nil)
            idx = e[:idx]
        else
            idx_tx = idx
            smac = "0x#{idx_name[idx]}"
            dir = "tx"
        end
        name = " name f_#{idx_name[idx]}"
        cmd_add += " #{dir} #{$ts.pc.p[idx]} #{name}"
        cmd += name
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
            seqn = fld_get(hsr, :seqn, 0)
            cmd += " htag pathid #{path_id} size #{size} seqn #{seqn}"
        end
        cmd += " et 0xeeee data pattern cnt #{len}"
        prp = fld_get(e, :prp, nil)
        if (prp != nil)
            seqn = fld_get(prp, :seqn, 0)
            net_id = fld_get(prp, :net_id, 5)
            lan_id = fld_get(prp, :lan_id, 0)
            path_id = ((net_id << 1) + lan_id)
            size = fld_get(prp, :size, len + 12) # Should be '+ 6' but FPGA needs update
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

    # Restore VLAN port configuration
    vlan_idx_list.each do |idx|
        vlan_port_conf_set(idx, {})
    end

    # Check RedBox counters
    if (idx_tx == $idx_a)
        exp["port_a"]["rx"] = 1
    elsif (idx_list.include?($idx_a))
        exp["port_a"]["tx"] = 1
    end
    if (idx_tx == $idx_b)
        exp["port_b"]["rx"] = 1
    elsif (idx_list.include?($idx_b))
        exp["port_b"]["tx"] = 1
    end
    if (idx_tx == $idx_c || idx_tx == $idx_d)
        exp["port_c"]["rx"] = 1
    elsif (idx_list.include?($idx_c) or idx_list.include?($idx_d))
        exp["port_c"]["tx"] = 1
    end
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
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        redbox_test(t)
    end
end

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api redbox")
    $ts.dut.run("mesa-cmd port stati pac")
end
