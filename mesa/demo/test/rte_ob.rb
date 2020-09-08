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
    conf = $ts.dut.call("mera_gen_conf_get")
    conf["enable"] = true
    $ts.dut.call("mera_gen_conf_set", conf)

    # Initialize QSPI
    qspi_init

    # Clear IO-FPGA memory
    io_fpga_rw("fill 0x100 0x100 0")
end

# Each entry in the test table has these items (only text is mandatory):
# 1: Text string used to name the test step
# 2: OPC flag (default Profinet), affecting the following three parts
# 3: RCE key/action fields
# 4: RTP entry fields
# 5: Data group fields
# 6: Frame fields
# 7: Counter values expected

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
        frame: {len: 50},
        cnt: {rx_0: 1}
    },
    {
        txt: "length_check_fail",
        rtp: {length: 50},
        frame: {len: 46},
    },

    # Profinet
    {
        txt: "pn_cc_check",
        frame: {tx_cnt: 3, cc: ["1234", "1233", "1235"]},
        cnt: {rx_0: 2}
    },
    {
        txt: "pn_ds_check_ok",
        rtp: {pn_ds: 0x07},
        frame: {ds: "07"},
        cnt: {rx_0: 1}
    },
    {
        txt: "pn_ds_check_fail",
        rtp: {pn_ds: 0x36},
    },
    {
        txt: "pn_ts_check_fail",
        frame: {ts: "01"},
    },

    # OPC-UA
    {
        txt: "opc_ok",
        opc: true,
        cnt: {rx_0: 1}
    },
    {
        txt: "opc_version_check_fail",
        opc: true,
        frame: {ver: "0"}
    },
    {
        txt: "opc_flags_check_fail",
        opc: true,
        frame: {flags: "3"}
    },
    {
        txt: "opc_flags1_check_fail",
        opc: true,
        frame: {flags1: "03"}
    },
    {
        txt: "opc_group_flags_check_fail",
        opc: true,
        frame: {gflags: "0e"}
    },
    {
        txt: "opc_group_version_fail",
        opc: true,
        rtp: {opc_grp_ver: 0x12345678},
        frame: {gver: "78563413"}
    },
    {
        txt: "opc_group_version_ok",
        opc: true,
        rtp: {opc_grp_ver: 0x12345678},
        frame: {gver: "78563412"},
        cnt: {rx_0: 1}
    },
    {
        txt: "opc_nmsg_num_fail",
        opc: true,
        frame: {nmsg_num: "0200"}
    },

    # Data group transfer
    {
        txt: "dg_write - QSPI",
        rtp: {wal_id: 7},
        dg: [{length: 4},{offs: 8, length: 34},{offs: 4, length: 4}],
        frame: {tx_cnt: 2},
        cnt: {rx_0: 2}
    },
    {
        txt: "dg_write - SRAM",
        intf: "SRAM",
        rtp: {wal_id: 8},
        dg: [{length: 4},{offs: 8, length: 34},{offs: 4, length: 4}],
        frame: {tx_cnt: 2},
        cnt: {rx_0: 2}
    },
]

def fld_get(v, fld, val = 0)
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
    dg = t[:dg]
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
    conf = $ts.dut.call("mera_ob_rtp_conf_get", $rtp_id)
    conf["type"] = ("MERA_RTP_TYPE_" + (opc ? "OPC_UA" : "PN"))
    conf["length"] = fld_get(e, :length, 46)
    conf["opc_grp_ver"] = fld_get(e, :opc_grp_ver);
    conf["pn_ds"] = fld_get(e, :pn_ds, 0x35);
    wal_id = fld_get(e, :wal_id);
    conf["wal_enable"] = (wal_id == 0 ? false : true)
    conf["wal_id"] = wal_id
    $ts.dut.call("mera_ob_rtp_conf_set", $rtp_id, conf)

    # I/O interface is a global setting, but setup here for test purposes only.
    intf = fld_get(t, :intf, "QSPI")
    if (intf != "QSPI")
        conf = $ts.dut.call("mera_gen_conf_get")
        conf["intf"] = ("MERA_IO_INTF_" + intf)
        $ts.dut.call("mera_gen_conf_set", conf)
    end

    # Add data group
    wr_addr = 0x100
    if (dg != nil)
        dg.each_with_index do |d, i|
            conf = $ts.dut.call("mera_ob_dg_init")
            conf["dg_id"] = i
            offs = fld_get(d, :offs)
            conf["pdu_offset"] = offs
            len = fld_get(d, :length, 1)
            conf["length"] = len
            $ts.dut.call("mera_ob_dg_add", $rtp_id, conf)
            conf = $ts.dut.call("mera_ob_wa_init")
            conf["rtp_id"] = $rtp_id
            conf["dg_id"] = i
            conf["wr_addr"] = wr_addr
            d[:addr] = wr_addr
            wr_addr = (wr_addr + len)
            str = ""
            len.times do |j|
                # Incrementing hex data expected, e.g. '04050607' at offset 4
                str = (str + ("%02x" % (offs + j)))
            end
            d[:str] = str
            $ts.dut.call("mera_ob_wa_add", wal_id, conf)
        end
    end

    # Send frames
    et = (opc ? 0xb62c : 0x8892)
    len = fld_get(f, :len, 46)
    tx_cnt = fld_get(f, :tx_cnt, 1)
    for i in 0..(tx_cnt - 1)
        cmd = "eth dmac 2 et #{et}"
        if (opc)
            # OPC-UA: Header and data
            ver = fld_get(f, :ver, "1")
            flags = fld_get(f, :flags, "b")
            flags1 = fld_get(f, :flags1, "01")
            gflags = fld_get(f, :gflags, "0f")
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
            ds = fld_get(f, :ds, "35")
            ts = fld_get(f, :ts, "00")
            cmd += " data pattern cnt #{len - 4}"
            cmd += " data hex #{cc}#{ds}#{ts}"
        end
        run_ef_tx_rx_cmd($ts, $idx_tx, [], cmd)
    end

    # Check counters
    rx_0 = fld_get(c, :rx_0)
    rx_1 = fld_get(c, :rx_1)
    cnt = $ts.dut.call("mera_ob_rtp_counters_get", $rtp_id)
    check_counter("rx_0", cnt["rx_0"], rx_0)
    check_counter("rx_1", cnt["rx_1"], rx_1)

    # Check data groups
    if (dg != nil)
        use_buf = (intf == "SRAM")
        base = 0
        if (use_buf)
            buf = $ts.dut.call("mera_ob_wal_req", wal_id)
            base = buf["addr"]
        end
        dg.each do |d|
            if (d.key?:str)
                addr = (d[:addr] + base)
                str = d[:str]
                res = io_str_rd(addr, str, intf)
                t_i("Exp (#{intf}): #{str}")
                act = ("0x%08x: #{res}" % addr)
                if (res == str)
                    t_i(act)
                else
                    t_e(act)
                end
            end
        end
        if (use_buf)
            $ts.dut.call("mera_ob_wal_rel", wal_id)
        end
    end

    # Next RTP ID
    $rtp_id = ($rtp_id + 1)
end

$test_table.each do |t|
    test t[:txt] do
        rte_ob_test(t)
    end
end

test "dump" do
    #$ts.dut.run("mera-cmd debug api ob")
    #$ts.dut.call("mera_ob_flush")
    #$ts.dut.run("mera-cmd debug api ob")
    #io_fpga_rw("dump 0x100 64")
end
