#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

cap_check_exit("QOS_INGRESS_MAP_CNT")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0
$idx_rx = 1
$vid_a  = 10

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
end

#---------- Frame testing -----------------------------------------------------

# Each entry in the test table has these items:
# 1: Text string printed during test
# 2: Switch Rx port configuration values
# 3: Switch Tx port configuration values
# 3: Host Tx frame values
# 4: Host Rx frame values expected
test_table =
    [
     {
         txt: "rx pcp to pcp",
         rx_cfg: {id: 0, key: "PCP", pcp: 7, "pcp" => 5},
         tx_cfg: {},
         tx_frm: {pcp: 7}, # Mapped to PCP = 5
         rx_frm: {pcp: 5}  # Classified value
     },
     {
         txt: "rx pcp to dei",
         rx_cfg: {id: 1, key: "PCP", pcp: 6, "dei" => 1},
         tx_cfg: {},
         tx_frm: {pcp: 6}, # Mapped to DEI = 1
         rx_frm: {dei: 1}  # Classified value
     },
     {
         txt: "rx dscp to dscp",
         rx_cfg: {id: 2, key: "DSCP", dscp: 39, "dscp" => 40},
         tx_cfg: {emode: "REMARK"},
         tx_frm: {tpid: 0, dscp: 39}, # Mapped to DSCP = 40
         rx_frm: {dscp: 40}           # Classified value
     },
     {
         txt: "rx pcp to cos",
         rx_cfg: {id: 3, key: "PCP", pcp: 7, "cos" => 4},
         tx_cfg: {mode: "MAPPED"},
         tx_frm: {pcp: 7}, # Mapped to (COS, DPL) = (4, 0)
         rx_frm: {pcp: 4}  # Mapped using port egress mapping
     },
     {
         txt: "rx pcp_dei to dpl",
         rx_cfg: {id: 4, key: "PCP_DEI", pcp: 4, dei: 0, "dpl" => 1},
         tx_cfg: {mode: "MAPPED"},
         tx_frm: {pcp: 4, dei: 0}, # Mapped to (COS, DPL) = (0, 1)
         rx_frm: {pcp: 1, dei: 1}  # Mapped using port egress mapping
     },
     {
         txt: "rx pcp to cosid/tx cosid to dscp",
         rx_cfg: {id: 5, key: "PCP", pcp: 5, "cosid" => 6},
         tx_cfg: {id: 0, key: "COSID", cosid: 6, "dscp" => 21},
         tx_frm: {pcp: 5, dscp: 0}, # Mapped to COSID = 6
         rx_frm: {dscp: 21}         # Mapped from COSID
     },
     {
         txt: "rx pcp to cosid_dpl/tx cosid_dpl to dscp",
         rx_cfg: {id: 6, key: "PCP", pcp: 4, "cosid" => 5, "dpl" => 1},
         tx_cfg: {id: 1, key: "COSID_DPL", cosid: 5, dpl: 1, "dscp" => 22},
         tx_frm: {pcp: 4, dscp: 0}, # Mapped to (COSID, DPL) = (5, 1)
         rx_frm: {dscp: 22}         # Mapped from (COSID, DPL)
     },
     {
         txt: "rx dscp to dscp/tx dscp to dscp",
         rx_cfg: {id: 7, key: "DSCP", dscp: 42, "dscp" => 43, "dpl" => 1},
         tx_cfg: {id: 2, key: "DSCP", dscp: 43, "dscp" => 44},
         tx_frm: {dscp: 42}, # Mapped to DSCP = 43
         rx_frm: {dscp: 44}  # Mapped from DSCP
     },
     {
         txt: "rx pcp to dscp_dpl/tx dscp_dpl to pcp",
         rx_cfg: {id: 6, key: "PCP", pcp: 4, "dscp" => 45, "dpl" => 3},
         tx_cfg: {id: 3, key: "DSCP_DPL", dscp: 45, dpl: 3, "pcp" => 5},
         tx_frm: {pcp: 4, dscp: 0}, # Mapped to (DSCP, DPL) = (45, 3)
         rx_frm: {pcp: 5, dscp: 0}  # Mapped from (DSCP, DPL)
     },
    ]

def frame_fld_get(tx_fld, hdr, fld)
    if (hdr.key?(fld))
        tx_fld = hdr[fld]
    end
    tx_fld
end

def map_set(map, values, cfg)
    ["cos", "dpl", "cosid", "pcp", "dei", "dscp"].each do |k|
        if (cfg.key?k)
            map["action"][k] = true
            values[k] = cfg[k]
        end
    end
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        # Ingress port
        cfg = t[:rx_cfg]
        port = $ts.dut.port_list[$idx_tx]
        conf = $ts.dut.call("mesa_qos_port_conf_get", port)
        conf["ingress_map"] = ((cfg.key?:id) ? cfg[:id] : 0xfff)
        $ts.dut.call("mesa_qos_port_conf_set", port, conf)

        # Ingress map
        imap_id = nil
        if (cfg.key?:key)
            map = $ts.dut.call("mesa_qos_ingress_map_init", "MESA_QOS_INGRESS_MAP_KEY_" + cfg[:key])
            imap_id = cfg[:id]
            map["id"] = imap_id

            maps = map["maps"]
            case (cfg[:key])
            when "PCP"
                values = maps["pcp"][cfg[:pcp]]
            when "PCP_DEI"
                values = maps["pcp_dei"][cfg[:pcp]][cfg[:dei]]
            when "DSCP"
                values = maps["dscp"][cfg[:dscp]]
            when "DSCP_PCP_DEI"
                if (cfg.key?:dscp)
                    values = maps["dpd"][cfg[:dscp]]
                else
                    values = maps["dpd"][cfg[:pcp]][cfg[:dei]]
                end
            end
            map_set(map, values, cfg)
            $ts.dut.call("mesa_qos_ingress_map_add", map)
        end

        # Egress port
        cfg = t[:tx_cfg]
        port = $ts.dut.port_list[$idx_rx]
        conf = $ts.dut.call("mesa_qos_port_conf_get", port)
        conf["egress_map"] = ((cfg.key?:id) ? cfg[:id] : 0xfff)
        conf["tag"]["remark_mode"] = ("MESA_TAG_REMARK_MODE_" + ((cfg.key?:mode) ? cfg[:mode] : "CLASSIFIED"))
        conf["dscp"]["emode"] = ("MESA_DSCP_EMODE_" + ((cfg.key?:emode) ? cfg[:emode] : "DISABLE"))
        $ts.dut.call("mesa_qos_port_conf_set", port, conf)

        # Egress map
        emap_id = nil
        if (cfg.key?:key)
            map = $ts.dut.call("mesa_qos_egress_map_init", "MESA_QOS_EGRESS_MAP_KEY_" + cfg[:key])
            emap_id = cfg[:id]
            map["id"] = emap_id

            maps = map["maps"]
            case (cfg[:key])
            when "COSID"
                values = maps["cosid"][cfg[:cosid]]
            when "COSID_DPL"
                values = maps["cosid_dpl"][cfg[:cosid]][cfg[:dpl]]
            when "DSCP"
                values = maps["dscp"][cfg[:dscp]]
            when "DSCP_DPL"
                values = maps["dscp_dpl"][cfg[:dscp]][cfg[:dpl]]
            end
            map_set(map, values, cfg)
            $ts.dut.call("mesa_qos_egress_map_add", map)
        end

        # Frame test
        f_base = " eth"
        f_end = " data pattern cnt 64"

        f = t[:tx_frm]
        tag = {}
        tag[:tpid] = ((f.key?:tpid) ? f[:tpid] : 0x8100)
        tag[:vid] = $vid_a
        tag[:pcp] = ((f.key?:pcp) ? f[:pcp] : 0)
        tag[:dei] = ((f.key?:dei) ? f[:dei] : 0)

        cmd = "sudo ef name f1"
        cmd += f_base
        cmd += cmd_tag_push(tag)
        if (f.key?:dscp)
            cmd += " ipv4 dscp #{f[:dscp]}"
        end
        cmd += f_end

        cmd += " name f2"
        cmd += f_base
        f = t[:rx_frm]
        tag[:pcp] = ((f.key?:pcp) ? f[:pcp] : tag[:pcp])
        tag[:dei] = ((f.key?:dei) ? f[:dei] : tag[:dei])
        cmd += cmd_tag_push(tag)
        if (f.key?:dscp)
            cmd += " ipv4 dscp #{f[:dscp]}"
        end
        cmd += f_end

        cmd += " tx #{$ts.pc.p[$idx_tx]} name f1"
        cmd += " rx #{$ts.pc.p[$idx_rx]} name f2"
        t_i("Test '#{t[:txt]}'")
        $ts.pc.run(cmd)

        if (imap_id != nil)
            $ts.dut.call("mesa_qos_ingress_map_del", imap_id)
        end
        if (emap_id != nil)
            $ts.dut.call("mesa_qos_egress_map_del", emap_id)
        end
    end
end
