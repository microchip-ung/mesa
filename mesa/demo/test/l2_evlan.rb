#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

# Disable VLAN counters using "-v" option
$ts = get_test_setup("mesa_pc_b2b_4x", {}, "-v")

#---------- Configuration -----------------------------------------------------

$idx_rx = 3
$vid_a  = 10
$emap = 20

$cap_l26 = (cap_get("MEP_LUTON26") != 0)
$cap_emap = (cap_get("QOS_EGRESS_MAP_CNT") != 0)

test "conf" do
    t_i "VLAN unaware ports, PVID ensures discard of unmatched frames"
    $ts.dut.port_list.each do |port|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_UNAWARE"
        conf["pvid"] = 4095
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
        end

    t_i "Egress tag remarking based on classified PCP/DEI"
    $ts.dut.port_list.each do |port|
        conf = $ts.dut.call("mesa_qos_port_conf_get", port)
        conf["tag"]["remark_mode"] = "MESA_TAG_REMARK_MODE_CLASSIFIED"
        conf["cosid"] = 0
        conf["egress_map"] = 4095 # NONE
        $ts.dut.call("mesa_qos_port_conf_set", port, conf)
    end

    t_i "Include both ports in VLAN"
    port_list = port_idx_list_str([$idx_rx])
    $ts.dut.call("mesa_vlan_port_members_set", $vid_a, port_list)

    t_i "S-custom Ethernet Type"
    conf = $ts.dut.call("mesa_vlan_conf_get")
    conf["s_etype"] = 0x9100
    $ts.dut.call("mesa_vlan_conf_set", conf)
end

#---------- Frame testing -----------------------------------------------------

# Each entry in the test table has these items:
# 1: Text string printed during test
# 2: Switch Rx port configuration values
# 3: Switch Tx port configuration values
# 3: Host Tx frame values
# 4: Host Rx frame values
test_table =
    [
     {
         txt: "rx any, tx c-tag",
         rx_cfg: {port_idx: 0, key_type: "NORMAL"},
         tx_cfg: {ot: {tpid: "C", vid: 20, pcp: 5, dei: 1}},
         tx_frm: [{},
                  {ot: {tpid: 0x8100, vid: $vid_a}}],
         # Frames are forwarded with pushed C-tag
         rx_frm: [{ot: {tpid: 0x8100, vid: 20, pcp: 5, dei: 1}},
                  {ot: {tpid: 0x8100, vid: 20, pcp: 5, dei: 1}}]
     },
     {
         txt: "rx s-tag, tx prio c-tag",
         rx_cfg: {port_idx: 0, key_type: "NORMAL", ot: {tagged: 1, s_tag: 1, vid: {v: 10, m: 0xff}}, pop: 1},
         tx_cfg: {ot: { tpid: "C", vid: 4096, pcp: 6, dei: 0}},
         tx_frm: [{},
                  {ot: {tpid: 0x88a8, vid: 10}}],
         # S-tagged frame matching VID is forwarded priority-C-tagged, popping the S-tag
         rx_frm: [{discard: 1},
                  {ot: {tpid: 0x8100, vid: 0, pcp: 6, dei: 0}, pop: 1}]
     },
     {
         txt: "rx c-tag, tx s-tag",
         rx_cfg: {port_idx: 1, key_type: "DOUBLE_TAG", ot: {tagged: 1, s_tag: 0, vid: {v: 10, m: 0xfff}, pcp: {v: 3, m: 0x7}, dei: 0}},
         tx_cfg: {ot: {tpid: "S", vid: 20, pcp: 5, dei: 1}},
         tx_frm: [{ot: {tpid: 0x8100, vid: 10, pcp: 3}},
                  {ot: {tpid: 0x88a8, vid: 10, pcp: 3}},
                  {ot: {tpid: 0x8100, vid: 11, pcp: 3}},
                  {ot: {tpid: 0x8100, vid: 10, pcp: 4}},
                  {ot: {tpid: 0x8100, vid: 10, pcp: 3, dei: 1}},
                  {}],
         # C-tagged frame with matching (VID, PCP, DEI) is forwarded with pushed S-tag
         rx_frm: [{ot: {tpid: 0x88a8, vid: 20, pcp: 5, dei: 1}},
                  {discard: 1},
                  {discard: 1},
                  {discard: 1},
                  {discard: 1},
                  {discard: 1}]
     },
     {
         txt: "rx c-tag + s-tag, tx s-custom",
         # Luton26 skipped, does not support matching inner tag
         skip: $cap_l26,
         rx_cfg: {port_idx: 1, key_type: "IP_ADDR", ot: {tagged: 1, s_tag: 0}, it: {tagged: 1, s_tag: 1}, pop: 2},
         tx_cfg: {ot: {tpid: "S_CUSTOM", vid: 20, pcp: 5, dei: 1}},
         tx_frm: [{ot: {tpid: 0x8100, vid: 10, pcp: 3}, it: {tpid: 0x88a8, vid: 11, pcp: 4}},
                  {ot: {tpid: 0x8100, vid: 10, pcp: 3}},
                  {}],
         # Frame with C-tag and S-tag is forwarded with pushed S-custom tag
         rx_frm: [{ot: {tpid: 0x9100, vid: 20, pcp: 5, dei: 1}, pop: 2},
                  {discard: 1},
                  {discard: 1}]
     },
     {
         txt: "rx s-tag, tx untag",
         rx_cfg: {port_idx: 0, key_type: "MAC_IP_ADDR", ot: {tagged: 1, s_tag: 1, vid: {v: 10, m: 0xff}, pcp: {v: 3, m: 0x7}, dei: 0}, pop: 1},
         tx_cfg: {ot: { tpid: "NONE"}},
         tx_frm: [{ot: {tpid: 0x88a8, vid: 10, pcp: 3}},
                  {ot: {tpid: 0x8100, vid: 10, pcp: 3}},
                  {ot: {tpid: 0x88a8, vid: 11, pcp: 3}},
                  {ot: {tpid: 0x88a8, vid: 10, pcp: 4}},
                  {ot: {tpid: 0x88a8, vid: 10, pcp: 3, dei: 1}},
                  {}],
         # S-tagged frame matching (VID, PCP, DEI) is forwarded untagged, popping the S-tag
         rx_frm: [{pop: 1},
                  {discard: 1},
                  {discard: 1},
                  {discard: 1},
                  {discard: 1},
                  {discard: 1}]
     },
     {
         txt: "rx s-tag + c-tag, tx c-tag + s-tag",
         # Luton26 skipped, does not support pushing two tags
         skip: $cap_l26,
         rx_cfg: {port_idx: 1, key_type: "NORMAL", ot: {tagged: 1, s_tag: 1}, it: {tagged: 1, s_tag: 0}},
         tx_cfg: {ot: {tpid: "C", vid: 20, pcp: 5, dei: 1}, it: {tpid: "S", vid: 21, pcp: 6, dei: 0}},
         tx_frm: [{ot: {tpid: 0x88a8, vid: 10, pcp: 3}, it: {tpid: 0x8100, vid: 11, pcp: 4}},
                  {}],
         # Frame with S-tag and C-tag forwarded with pushed C-tag and S-tag
         rx_frm: [{ot: {tpid: 0x8100, vid: 20, pcp: 5, dei: 1}, it: {tpid: 0x88a8, vid: 21, pcp: 6}},
                  {discard: 1}]
     },
     {
         txt: "rx s-tag (mapped), tx c-tag (mapped)",
         rx_cfg: {port_idx: 1, key_type: "DOUBLE_TAG", ot: {tagged: 1, s_tag: 1}, map: "OUTER"},
         tx_cfg: {ot: {tpid: "C", vid: 20, pcp_sel: "MAPPED"}},
         tx_frm: [{ot: {tpid: 0x88a8, vid: 10, pcp: 3}},
                  {ot: {tpid: 0x88a8, vid: 10, pcp: 5}}],
         # Frames with S-tag mapped to COSID (fixed mapping) and forwarded with pushed C-tag.
         rx_frm: [{cosid: 1, ot: {tpid: 0x8100, vid: 20, pcp: 2}},
                  {cosid: 2, ot: {tpid: 0x8100, vid: 20, pcp: 4}}]
     },
     {
         txt: "rx any, tx port (default)",
         rx_cfg: {port_idx: 0, key_type: "NORMAL"},
         tx_cfg: {ot: {tpid: "PORT", vid: 0, pcp_sel: "PORT", dei_sel: "PORT"}},
         tx_frm: [{},
                  {ot: {tpid: 0x8100, vid: 20}}],
         # Frames are forwarded with C-tag based on port configuration and classified VID
         rx_frm: [{ot: {tpid: 0x8100, vid: $vid_a, pcp: 0, dei: 0}},
                  {ot: {tpid: 0x8100, vid: $vid_a, pcp: 0, dei: 0}}]
     },
     {
         txt: "rx any, tx port (changed)",
         rx_cfg: {port_idx: 0, key_type: "NORMAL"},
         tx_cfg: {ot: {tpid: "PORT", vid: 20, pcp_sel: "PORT", dei_sel: "PORT"}, vlan: {type: "S"}, qos: {mode: "DEFAULT", pcp: 5, dei: 1}},
         tx_frm: [{},
                  {ot: {tpid: 0x8100, vid: 10}}],
         # Frames are forwarded with S-tag based on port configuration (Luton26 puts DP in DEI field when port DEI is set)
         rx_frm: [{ot: {tpid: 0x88a8, vid: 20, pcp: 5, dei: $cap_l26 ? 0 : 1}},
                  {ot: {tpid: 0x88a8, vid: 20, pcp: 5, dei: $cap_l26 ? 0 : 1}}]
     },
     {
         txt: "rx any, tx port (changed emap)",
         skip: !$cap_emap,
         rx_cfg: {port_idx: 0, key_type: "NORMAL", qos: {cosid: 2}},
         tx_cfg: {ot: {tpid: "PORT", vid: 20, pcp_sel: "PORT", dei_sel: "PORT"}, vlan: {type: "S_CUSTOM"}, qos: {emap: $emap}},
         tx_frm: [{},
                  {ot: {tpid: 0x8100, vid: 10}}],
         # Frames are forwarded with S-custom-tag based on egress map and COSID
         rx_frm: [{cosid: 2, ot: {tpid: 0x9100, vid: 20, pcp: 4}},
                  {cosid: 2, ot: {tpid: 0x9100, vid: 20, pcp: 4}}]
     },
    ]

def vce_tag_set(k, cfg, fld)
    if (cfg.key?(fld))
        v = cfg[fld]
        vcap_vm_set(k, "vid", v, :vid)
        vcap_vm_set(k, "pcp", v, :pcp)
        vcap_bit_set(k, "dei", v, :dei)
        vcap_bit_set(k, "tagged", v, :tagged)
        vcap_bit_set(k, "s_tag", v, :s_tag)
    end
end

def tce_tag_set(k, cfg, fld, emap)
    if (cfg.key?(fld))
        v = cfg[fld]
        if (v.key?:tpid)
            k["tpid"] = ("MESA_TPID_SEL_" + v[:tpid])
        end
        if (v.key?:vid)
            k["vid"] = v[:vid]
        end
        k["pcp_sel"] = ("MESA_PCP_SEL_" + ((v.key?:pcp_sel) ? v[:pcp_sel] : "FIXED"))
        if (v.key?:pcp)
            k["pcp"] = v[:pcp]
        end
        k["dei_sel"] = ("MESA_DEI_SEL_" + ((v.key?:dei_sel) ? v[:dei_sel] : "FIXED"))
        if (v.key?:dei)
            k["dei"] = v[:dei]
        end
        k["map_id"] = emap
    end
end

def frame_tag_push(hdr, fld, push)
    cmd = ""
    if (push and hdr.key?(fld))
        cmd = cmd_tag_push(hdr[fld])
    end
    cmd
end

def cnt_check(name, val, exp)
    msg = "#{name} = #{val}, expected #{exp}"
    if (val == exp)
        t_i(msg)
    else
        t_e(msg)
    end
end

$iflow = 0
$cap_xstat = false
$eflow = 0
$cap_imap = false
$istat = 0
$estat = 0
$imap = 0
test "conf-common" do
    cap_xflow = (cap_get("L2_XFLOW") != 0)
    $cap_xstat = (cap_get("L2_XSTAT") != 0)
    cap_xdlb = (cap_get("L2_XDLB") != 0)
    $cap_imap = (cap_get("QOS_INGRESS_MAP_CNT") != 0)
    class_cnt = ($cap_imap ? 4 : 1)
    $iflow = (cap_xflow ? $ts.dut.call("mesa_iflow_alloc") : 0)
    $istat = ($cap_xstat ? $ts.dut.call("mesa_ingress_cnt_alloc", class_cnt) : 0)
    pol = (cap_xdlb ? $ts.dut.call("mesa_dlb_policer_alloc", class_cnt) : 0)
    $eflow = (cap_xflow ? $ts.dut.call("mesa_eflow_alloc") : 0)
    $estat = ($cap_xstat ? $ts.dut.call("mesa_egress_cnt_alloc", class_cnt) : 0)
    if (cap_xflow)
        conf = $ts.dut.call("mesa_iflow_conf_get", $iflow)
        conf["cnt_enable"] = true
        conf["cnt_id"] = $istat
        conf["dlb_enable"] = true
        conf["dlb_id"] = pol
        $ts.dut.call("mesa_iflow_conf_set", $iflow, conf)

        conf = $ts.dut.call("mesa_eflow_conf_get", $eflow)
        conf["cnt_enable"] = true
        conf["cnt_id"] = $estat
        $ts.dut.call("mesa_eflow_conf_set", $eflow, conf)
    end

    # Policer with COSID 1 discards all frames
    if (cap_xdlb && class_cnt > 1)
        cosid = 1
        conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
        conf["enable"] = true
        conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, cosid, conf)
    end
    # Ingress map, PCP -> COSID (0-3)
    $imap = 10
    if ($cap_imap)
        map = $ts.dut.call("mesa_qos_ingress_map_init", "MESA_QOS_INGRESS_MAP_KEY_PCP")
        map["id"] = $imap
        map["action"]["cosid"] = true
        for pcp in 0..7 do
            map["maps"]["pcp"][pcp]["cosid"] = (pcp / 2)
        end
        $ts.dut.call("mesa_qos_ingress_map_add", map)
    else
        $ts.dut.port_list.each do |port|
            conf = $ts.dut.call("mesa_qos_port_conf_get", port)
            tag = conf["tag"]
            tag["class_enable"] = true
            for pcp in 0..7 do
                for dei in 0..1 do
                    tag["pcp_dei_map"][pcp][dei]["prio"] = (pcp / 2)
                end
            end
            $ts.dut.call("mesa_qos_port_conf_set", port, conf)
        end
    end

    # Egress map, COSID (0-3) -> PCP
    if ($cap_emap)
        map = $ts.dut.call("mesa_qos_egress_map_init", "MESA_QOS_EGRESS_MAP_KEY_COSID")
        map["id"] = $emap
        map["action"]["pcp"] = true
        map["action"]["dei"] = true
        for cosid in 0..3 do
            map["maps"]["cosid"][cosid]["pcp"] = (cosid * 2)
        end
        $ts.dut.call("mesa_qos_egress_map_add", map)
    else
        dpl_cnt = cap_get("QOS_DPL_CNT")
        $ts.dut.port_list.each do |port|
            conf = $ts.dut.call("mesa_qos_port_dpl_conf_get", port, dpl_cnt)
            for prio in 0..3 do
                conf[0]["pcp"][prio] = (prio * 2)
            end
            $ts.dut.call("mesa_qos_port_dpl_conf_set", port, dpl_cnt, conf)
        end
    end
end

sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        if (t.key?:skip and t[:skip])
            t_i("Skipping for this platform")
            next
        end

        # Ingress configuration
        cfg = t[:rx_cfg]
        idx_tx = cfg[:port_idx]
        port = $ts.dut.port_list[idx_tx]
        vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
        vce["id"] = 1;
        if (cfg.key?:key_type)
            # Add VCE with empty port list so that we can change key type
            $ts.dut.call("mesa_vce_add", 0, vce)
            conf = $ts.dut.call("mesa_vcl_port_conf_get", port)
            conf["key_type"] = ("MESA_VCAP_KEY_TYPE_" + cfg[:key_type])
            conf = $ts.dut.call("mesa_vcl_port_conf_set", port, conf)
        end
    
        key = vce["key"]
        vce_tag_set(key["tag"], cfg, :ot)
        vce_tag_set(key["inner_tag"], cfg, :it)
        key["port_list"] = "#{port}"
        action = vce["action"]
        action["vid"] = $vid_a
        action["flow_id"] = $iflow
        if (cfg.key?:pop)
            action["pop_enable"] = true
            action["pop_cnt"] = cfg[:pop]
        end
        if (cfg.key?:map)
            action["map_sel"] = ("MESA_IMAP_SEL_" + cfg[:map])
            action["map_id"] = $imap
        end
        $ts.dut.call("mesa_vce_add", 0, vce)

        if (cfg.key?:qos)
            c = cfg[:qos]
            conf = $ts.dut.call("mesa_qos_port_conf_get", port)
            if (c.key?:cosid)
                conf["cosid"] = c[:cosid]
            end
            $ts.dut.call("mesa_qos_port_conf_set", port, conf)
        end

        # Egress configuration
        cfg = t[:tx_cfg]
        idx_rx = $idx_rx
        port = $ts.dut.port_list[idx_rx]
        tce = $ts.dut.call("mesa_tce_init")
        tce["id"] = 1;
        key = tce["key"]
        key["port_list"] = "#{port}"
        key["vid"] = $vid_a
        action = tce["action"]
        action["flow_id"] = $eflow
        tce_tag_set(action["tag"], cfg, :ot, $emap);
        tce_tag_set(action["inner_tag"], cfg, :it, $emap);
        $ts.dut.call("mesa_tce_add", 0, tce)

        if (cfg.key?:vlan)
            c = cfg[:vlan]
            conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
            if (c.key?:type)
                conf["port_type"] = ("MESA_VLAN_PORT_TYPE_" + c[:type])
            end
            $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
        end
        if (cfg.key?:qos)
            c = cfg[:qos]
            conf = $ts.dut.call("mesa_qos_port_conf_get", port)
            tag = conf["tag"]
            if (c.key?:mode)
                tag["remark_mode"] = ("MESA_TAG_REMARK_MODE_" + c[:mode])
            end
            if (c.key?:pcp)
                tag["egress_pcp"] = c[:pcp]
            end
            if (c.key?:dei)
                tag["egress_dei"] = c[:dei]
            end
            if (c.key?:emap)
                conf["egress_map"] = c[:emap]
            end
            $ts.dut.call("mesa_qos_port_conf_set", port, conf)
        end

        # Frame test
        t[:tx_frm].each_with_index do |tx_f, i|
            t_i("Frame[#{i}]: '#{t[:txt]}'")
            f_base = "eth"
            f_end = " data pattern cnt 64" # Avoid switch padding after popping tag

            # Tx frame (name f1)
            cmd = "sudo ef name f1 #{f_base}"
            cmd += frame_tag_push(tx_f, :ot, true)
            cmd += frame_tag_push(tx_f, :it, true)
            cmd += f_end

            rx_f = t[:rx_frm][i]
            cosid = (($cap_imap and (rx_f.key?:cosid)) ? rx_f[:cosid] : 0)
            discard = rx_f.key?:discard
            forward = (!discard and cosid != 1)
            pop = ((rx_f.key?:pop) ? rx_f[:pop] : 0)
            if (forward)
                # Rx frame (name f2)
                cmd += " name f2 #{f_base}"
                cmd += frame_tag_push(rx_f, :ot, true)
                cmd += frame_tag_push(rx_f, :it, true)
                cmd += frame_tag_push(tx_f, :ot, pop < 1)
                cmd += frame_tag_push(tx_f, :it, pop < 2)
                cmd += f_end
            end
            cmd += " tx #{$ts.pc.p[idx_tx]} name f1 rx #{$ts.pc.p[idx_rx]}"
            if (forward)
                cmd += " name f2"
            end

            if ($cap_xstat)
                # Clear counters
                $ts.dut.call("mesa_ingress_cnt_clear", $istat, cosid)
                $ts.dut.call("mesa_egress_cnt_clear", $estat, cosid)
            end
            $ts.pc.run(cmd)
            if ($cap_xstat)
                # Check counters
                cnt = $ts.dut.call("mesa_ingress_cnt_get", $istat, cosid)
                name = (cosid == 1 ? "rx_red" : "rx_green")
                cnt_check(name, cnt[name]["frames"], discard ? 0 : 1)
                cnt = $ts.dut.call("mesa_egress_cnt_get", $estat, cosid)
                name = "tx_green"
                cnt_check(name, cnt[name]["frames"], forward ? 1 : 0)
            end
        end
    end
end

test_summary
