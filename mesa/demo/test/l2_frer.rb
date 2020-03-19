#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if FRER supported
cap_check_exit("L2_FRER")

#---------- Configuration -----------------------------------------------------

# The FRER test operates like this:
# - One VLAN is reserved for FRER
# - Port index 0 and 1 are ingress ports
# - Port index 2 is egress port with R-tag only
# - Port index 3 is egress port with C-tag and R-tag
#
#  VCL     ISDX   MSTRM       CSTRM
# +----+  +----+  +----+      +----+
# |    |  |    |->| p2 |----->|    |
# | p0 |->| p0 |  +----+ +--->| p2 |
# |    |  |    |->| p3 |-|-+  |    |
# +----+  +----+  +----+ | |  +----+
# |    |  |    |->| p2 |-+ |  |    |
# | p1 |->| p1 |  +----+   +->| p3 |
# |    |  |    |->| p3 |----->|    |
# +----+  +----+  +----+      +----+

$vid = 100
$cap_iflow_pop = cap_get("L2_FRER_IFLOW_POP")

$conf_table = 
    [
     {
         # Port index 0 is ingress port
         mid: 0,       # Allocated member stream block
     },
     {
         # Port index 1 is ingress port
         mid: 0,       # Allocated member stream block
     },
     {
         # Port index 2 is egress port
         cid: 0,       # Compound stream ID
         inner: false, # R-tag only
     },
     {
         # Port index 3 is egress port
         cid: 1,       # Compound stream ID
         inner: true,  # C-tag and R-tag
     },
    ]

test "conf" do
    # Build egress port index list
    port_idx_list = []
    for idx in 0..3
        if ($conf_table[idx].key?:cid)
            port_idx_list << idx
        end
    end
    port_list_str = port_idx_list_str(port_idx_list)
    $ts.dut.call("mesa_vlan_port_members_set", $vid, port_list_str)

    for idx in 0..3
        cfg = $conf_table[idx]
        port = $ts.dut.port_list[idx]
        if (cfg.key?:mid)
            # Ingress port

            # Member streams
            mid = $ts.dut.call("mesa_frer_mstream_alloc", port_list_str) 
            cfg[:mid] = mid
            port_idx_list.each do |i|
                p = $ts.dut.port_list[i]                
                conf = $ts.dut.call("mesa_frer_mstream_conf_get", mid, p)
                conf["cstream_id"] = $conf_table[i][:cid]
                $ts.dut.call("mesa_frer_mstream_conf_set", mid, p, conf)
            end

            # Ingress flow
            iflow = $ts.dut.call("mesa_iflow_alloc")
            cfg[:iflow] = iflow
            conf = $ts.dut.call("mesa_iflow_conf_get", iflow)
            frer = conf["frer"]
            frer["mstream_enable"] = true
            frer["mstream_id"] = mid
            conf["cut_through_disable"] = true
            $ts.dut.call("mesa_iflow_conf_set", iflow, conf)

            # VCE
            vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
            vce["id"] = (idx + 1)
            vce["key"]["port_list"] = "#{port}"
            action = vce["action"]
            action["vid"] = $vid
            action["flow_id"] = iflow
            $ts.dut.call("mesa_vce_add", 0, vce)
        else
            # Egress port
            if ($cap_iflow_pop)
                conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
                conf["untagged_vid"] = (cfg[:inner] ? 1 : $vid)
                $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
            else
                # TCE
                tce = $ts.dut.call("mesa_tce_init")
                tce["id"] = (idx + 1);
                key = tce["key"]
                key["port_list"] = "#{port}"
                key["vid"] = $vid
                action = tce["action"]
                action["tag"]["tpid"] = "MESA_TPID_SEL_PORT"
                action["rtag"]["sel"] = ("MESA_RTAG_SEL_" + (cfg[:inner] ? "INNER" : "OUTER"))
                $ts.dut.call("mesa_tce_add", 0, tce)
            end
        end
    end
end

def frer_test(table)
    table.each do |t|
        seq = t[:seq]
        idx_tx = t[:idx_tx]
        cmd = "sudo ef"
        cmd_end = ""
        for idx in 0..3
            f = nil
            dir = "rx"
            cfg = $conf_table[idx]
            if (idx == idx_tx)
                # Tx frame untagged or R-tagged
                dir = "tx"
                f = ""
                if (t.key?:rtag)
                    f += " rtag seqn #{seq}"
                end
            elsif (t[:idx_rx].include?idx)
                # Rx frame
                f = ""
                if ($conf_table[idx][:inner])
                    # C-tag
                    f += cmd_tag_push({tpid: 0x8100, vid: $vid})
                end
                if (t.key?:rtag or t.key?:gen or $cap_iflow_pop == false)
                    # R-tag (existing or generated)
                    f += " rtag seqn #{seq}"
                end
            end
            cmd_end += " #{dir} #{$ts.pc.p[idx]}"
            unless (f.nil?)
                cmd_name = " name f#{idx}"
                cmd += cmd_name
                cmd += " eth"
                cmd += f
                cmd += " et 0xabcd data pattern cnt 128"
                cmd_end += cmd_name
            end
        end
        $ts.pc.run(cmd + cmd_end)
    end
end

# Sequence generation test
test "frame-io-generation" do
    # Enable sequence generation on port index 0
    iflow = $conf_table[0][:iflow]
    conf = $ts.dut.call("mesa_iflow_conf_get", iflow)
    conf["frer"]["generation"] = true
    $ts.dut.call("mesa_iflow_conf_set", iflow, conf)

    table = [{gen: 1, seq: 0, idx_tx: 0, idx_rx: [2,3]}, # Seq 0 generated on port index 0
             {seq: 0, idx_tx: 1, idx_rx: [2,3]}, # No seq generated on port index 1
             {gen: 1, seq: 1, idx_tx: 0, idx_rx: [2,3]}] # Seq 1 generated on port index 0
    frer_test(table)

    # Disable sequence generation again
    conf["frer"]["generation"] = false
    $ts.dut.call("mesa_iflow_conf_set", iflow, conf)
end

# Sequence recovery test
test "frame-io-recovery" do
    # Enable recovery for compound stream on egress port index 2
    cid = $conf_table[2][:cid]
    conf = $ts.dut.call("mesa_frer_cstream_conf_get", cid)
    conf["recovery"] = true
    conf["alg"] = "MESA_FRER_RECOVERY_ALG_VECTOR"
    conf["hlen"] = 8
    conf["reset_time"] = 1000
    $ts.dut.call("mesa_frer_cstream_conf_set", cid, conf)

    # Enable recovery for member stream from port index 1 to port index 3
    mid = $conf_table[1][:mid]
    port = $ts.dut.port_list[3]
    conf = $ts.dut.call("mesa_frer_mstream_conf_get", mid, port)
    conf["recovery"] = true
    conf["alg"] = "MESA_FRER_RECOVERY_ALG_MATCH"
    conf["reset_time"] = 1000
    $ts.dut.call("mesa_frer_mstream_conf_set", mid, port, conf)

    table = [{rtag: 1, seq: 100, idx_tx: 0, idx_rx: [2,3]}, # Seq 100 forwarded
             {rtag: 1, seq: 100, idx_tx: 1, idx_rx: [3]},   # Seq 100 discarded by Sequence Recovery on index 2
             {rtag: 1, seq: 100, idx_tx: 1, idx_rx: []},    # Seq 100 discarded by Recovery on index 2 and 3
             {rtag: 1, seq: 101, idx_tx: 1, idx_rx: [2,3]}] # Seq 101 forwarded
    frer_test(table)

    # Clear counters for compound stream and await reset
    $ts.dut.call("mesa_frer_cstream_cnt_clear", cid)
    sleep(1)

    # Counter test using compound stream (Vector algorithm) on egress port index 2
    table = [{seq: 0, idx_tx: 0, idx_rx: [3]},              # No R-tag discarded (Tagless++, Discarded++)
             {rtag: 1, seq: 100, idx_tx: 0, idx_rx: [2,3]}, # Seq 100 forwarded (Passed++)
             {rtag: 1, seq: 108, idx_tx: 0, idx_rx: [3]},   # Seq 108 discarded (Rogue++, Discarded++)
             {rtag: 1, seq: 93, idx_tx: 0, idx_rx: [2,3]},  # Seq 93 forwarded (Passed++, OutOfOrder++)
             {rtag: 1, seq: 100, idx_tx: 0, idx_rx: [3]},   # Seq 100 discarded (Discarded++)
             {rtag: 1, seq: 107, idx_tx: 0, idx_rx: [2,3]}] # Seq 107 forwarded (Passed++, Lost+=6, OutOfOrder++)
    frer_test(table)

    cnt = $ts.dut.call("mesa_frer_cstream_cnt_get", cid)

    table = [["out_of_order", 2],
             ["rogue", 1],
             ["passed", 3],
             ["discarded", 3],
             ["lost", 6],
             ["tagless", 1]]
    table.each do |c|
        name = c[0] + "_packets"
        val = cnt[name]
        exp = c[1]
        msg = "#{name}, expected: #{exp}, value: #{val}"
        if (exp == val)
            t_i(msg)
        else
            t_e(msg)
        end
    end
end
