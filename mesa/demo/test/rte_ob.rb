#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_tx  = 0 # PC Tx port
$idx_rx  = 1 # PC Rx port
$rtp_id = 3
$port_rte = nil

test "conf" do
    port_cnt = cap_get("PORT_CNT")
    map = $ts.dut.call("mesa_port_map_get", port_cnt)
    for port in 0..(port_cnt - 1)
        if (map[port]["chip_port"] == 4)
            $port_rte = port
        end
    end
    if ($port_rte == nil)
        t_e("RTE port not found")
    else
        t_i("RTE port: #{$port_rte}")
    end

    # Enable untagged RTP processing
    conf = { "pcp": [true, true, true, true, true, true, true, true]}
    $ts.dut.call("mesa_rcl_vid_add", 0, conf)

    # Enable RTE
    conf = $ts.dut.call("lan9662_rte_gen_conf_get")
    conf["enable"] = true
    $ts.dut.call("lan9662_rte_gen_conf_set", conf)

end

# Each entry in the test table has these items (only text is mandatory):
# 1: Text string used to name the test step
# 2: OPC flag (default Profinet), affecting the following three parts
# 3: RCE key/action fields
# 4: RTP entry fields
# 5: Frame fields
# 6: Counter values expected

$test_table =
[
    # General
    {
        txt: "rx_cnt_0",
        frame: {tx_cnt: 2},
        cnt: {rx_0: 2}
    },
    {
        txt: "rx_cnt_1",
        rce: {sub_id: true},
        frame: {tx_cnt: 3},
        cnt: {rx_1: 3}
    },
    {
        txt: "length_check_disabled",
        cnt: {rx_0: 1}
    },
    {
        txt: "length_check_ok",
        opc: true,
        rtp: {length: 50},
        frame: {tx_cnt: 1, len: 50},
        cnt: {rx_0: 1}
    },
    {
        txt: "length_check_fail",
        rtp: {length: 50},
        frame: {tx_cnt: 1, len: 46},
    },

    # Profinet
    {
        txt: "pn_cc_check",
        frame: {tx_cnt: 3, cc: ["1234", "1233", "1235"]},
        cnt: {rx_0: 2}
    },
    {
        txt: "ps_ds_check_invalid_primary",
        frame: {ds: "01"},
    },
    {
        txt: "pn_ds_check_valid_primary",
        frame: {ds: "05"},
        cnt: {rx_0: 1}
    },
    {
        txt: "pn_ds_check_valid_backup",
        frame: {ds: "04"},
        cnt: {rx_0: 1}
    },
    {
        txt: "pn_ts_check",
        frame: {ts: "01"},
    },

    # OPC-UA
    {
        txt: "opc_ok",
        opc: true,
        cnt: {rx_0: 1}
    },
    {
        txt: "opc_version",
        opc: true,
        frame: {ver: "0"}
    },
    {
        txt: "opc_flags",
        opc: true,
        frame: {flags: "7"}
    },
    {
        txt: "opc_flags1",
        opc: true,
        frame: {flags1: "03"}
    },
    {
        txt: "opc_group_flags",
        opc: true,
        frame: {gflags: "30"}
    },
    {
        txt: "opc_group_version",
        opc: true,
        frame: {gver: "01000000"}
    },
    {
        txt: "opc_nmsg_num",
        opc: true,
        frame: {nmsg_num: "0200"}
    },
]

def fld_get(v, fld, defval)
    val = defval
    if (v != nil and v.key?(fld))
        val = v[fld]
    end
    val
end

def rte_ob_test(t)
    # Extract test items
    opc = fld_get(t, :opc, false)
    r = t[:rce]
    e = t[:rtp]
    f = t[:frame]
    c = t[:cnt]

    # Add RCE mapping to RTP ID
    rce = $ts.dut.call("mesa_rce_init")
    rce["id"] = 1
    k = rce["key"]
    k["port_no"] = $ts.dut.p[$idx_tx]
    k["etype"] = ("MESA_RCL_ETYPE_" + (opc ? "OPC_UA" : "PROFINET"))
    a = rce["action"]
    a["rtp_id"] = $rtp_id
    a["rtp_sub_id"] = fld_get(r, :sub_id, false)
    a["port_enable"] = true
    a["port_list"] = "#{$port_rte}"
    $ts.dut.call("mesa_rce_add", 0, rce)

    # Setup RTP entry
    conf = $ts.dut.call("lan9662_rte_ob_rtp_conf_get", $rtp_id)
    conf["type"] = ("LAN9662_RTP_TYPE_" + (opc ? "OPC_UA" : "PN"))
    conf["length"] = fld_get(e, :length, 0)
    $ts.dut.call("lan9662_rte_ob_rtp_conf_set", $rtp_id, conf)

    # Send frames
    et = (opc ? 0xb62c : 0x8892)
    len = fld_get(f, :len, 46)
    tx_cnt = fld_get(f, :tx_cnt, 1)
    for i in 0..(tx_cnt - 1)
        cmd = "eth dmac 2 et #{et}"
        if (opc)
            # OPC-UA: Header and data
            ver = fld_get(f, :ver, "1")
            flags = fld_get(f, :flags, "3") # Default TBD
            flags1 = fld_get(f, :flags1, "01")
            gflags = fld_get(f, :gflags, "10")
            gver = fld_get(f, :gver, "00000000")     # Little-endian
            nmsg_num = fld_get(f, :nmsg_num, "0100") # Little-endian
            cmd += " data hex #{flags}#{ver}#{flags1}aaaa#{gflags}bbbb#{gver}#{nmsg_num}cccc"
            cmd += " data pattern cnt #{len - 15}"
        else
            # Profinet: Data and trailer
            cc = fld_get(f, :cc, "ccc#{i}")
            if (cc.kind_of? Array)
                cc = cc[i]
            end
            ds = fld_get(f, :ds, "00")
            ts = fld_get(f, :ts, "00")
            cmd += " data pattern cnt #{len - 4}"
            cmd += " data hex #{cc}#{ds}#{ts}"
        end
        run_ef_tx_rx_cmd($ts, $idx_tx, [], cmd)
    end

    # Check counters
    rx_0 = fld_get(c, :rx_0, 0)
    rx_1 = fld_get(c, :rx_1, 0)
    cnt = $ts.dut.call("lan9662_rte_ob_rtp_counters_get", $rtp_id)
    check_counter("rx_0", cnt["rx_0"], rx_0)
    check_counter("rx_1", cnt["rx_1"], rx_1)

    # Next RTP ID
    $rtp_id = ($rtp_id + 1)
end

$test_table.each do |t|
    test t[:txt] do
        rte_ob_test(t)
    end
end

test "dump" do
    #$ts.dut.run("lan9662-rte-cmd debug api ob")
end
