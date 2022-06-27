#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

dut_cap_check_exit("rte")

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

    # Initialize QSPI
    qspi_init

    # Clear IO memory
    io_fpga_rw("fill 0x0100 0x100 0")
    io_sram_rw("fill 0x0100 0x100 0")
    io_sram_rw("fill 0xa900 0x100 0")
end

# Each entry in the test table has these items (only text is mandatory):
# 1: Text string used to name the test step
# 2: OPC flag (default Profinet), affecting the following three parts
# 3: RCE key/action fields
# 4: RTP entry fields
# 5: Data group fields
# 6: Frame fields
# 7: Counter values expected

test_table =
[
    # General
    {
        txt: "rx_cnt_0",
        frame: [{},{}],
    },
    {
        txt: "rx_cnt_1",
        rce: {sub_id: true},
        frame: [{},{},{}],
        cnt: {rx_0: 0, rx_1: 3}
    },
    {
        txt: "length_check_disabled",
    },
    {
        txt: "length_check_ok",
        opc: true,
        rtp: {length: 50},
        frame: [{len: 50}],
    },
    {
        txt: "length_check_fail",
        rtp: {length: 50},
        frame: [{len: 46}],
        cnt: {rx_0: 0}
    },

    # Profinet
    {
        txt: "pn_cc_check",
        frame: [{cc: "1234"},{cc: "1233"},{cc: "1235"}],
        cnt: {rx_0: 2}
    },
    {
        txt: "pn_ds_check_ok",
        rtp: {pn_ds: 0x07},
        frame: [{ds: "07"}],
    },
    {
        txt: "pn_ds_check_fail",
        rtp: {pn_ds: 0x36, pn_discard: true, pn_mm: 0x35},
        cnt: {rx_0: 0},
        ev: "PN_DS_MISMATCH"
    },
    {
        txt: "pn_ts_check_fail",
        frame: [{ts: "01"}],
        cnt: {rx_0: 0}
    },

    # OPC-UA
    {
        txt: "opc_ok",
        opc: true,
    },
    {
        txt: "opc_version_check_fail",
        opc: true,
        frame: [{ver: "0"}],
        cnt: {rx_0: 0}
    },
    {
        txt: "opc_flags_check_fail",
        opc: true,
        frame: [{flags: "3"}],
        cnt: {rx_0: 0}
    },
    {
        txt: "opc_flags1_check_fail",
        opc: true,
        frame: [{flags1: "03"}],
        cnt: {rx_0: 0}
    },
    {
        txt: "opc_group_flags_check_fail",
        opc: true,
        frame: [{gflags: "0e"}],
        cnt: {rx_0: 0}
    },
    {
        txt: "opc_group_version_fail",
        opc: true,
        rtp: {opc_grp_ver: 0x12345678},
        frame: [{gver: "78563413"}],
        cnt: {rx_0: 0}
    },
    {
        txt: "opc_group_version_ok",
        opc: true,
        rtp: {opc_grp_ver: 0x12345678},
        frame: [{gver: "78563412"}],
    },
    {
        txt: "opc_nmsg_num_fail",
        opc: true,
        frame: [{nmsg_num: "0200"}],
        cnt: {rx_0: 0}
    },

    # Data group transfer
    {
        txt: "dg_write - QSPI",
        intf: "QSPI",
        rtp: {wal_id: 7},
        dg: [{length: 4},{offs: 8, length: 34},{offs: 4, length: 4}],
    },
    {
        txt: "dg_write - SRAM",
        rtp: {wal_id: 8},
        dg: [{length: 4},{offs: 8, length: 34},{offs: 4, length: 4}],
    },
    {
        txt: "pn_dg_write - default",
        rtp: {wal_id: 9},
        # IOPS at offset 4, bit 7 is valid flag
        dg: [{length: 5, vld_offs: 4, vld_chk: true, inv_def: true, str: "0102030405", data: [1,2,3,4,5]}],
        frame: [{data: "0001020300"}],
        ev: "DG_INVALID"
    },
    {
        txt: "pn_dg_write - last valid",
        rtp: {wal_id: 10},
        # IOPS at offset 4, bit 7 is valid flag
        dg: [{length: 5, vld_offs: 4, vld_chk: true, valid: 0x78, str: "0001020380"}],
        frame: [{data: "0001020380"},{data: "0102030478"}],
    },
    {
        txt: "opc_dg_write - last valid",
        opc: true,
        rtp: {wal_id: 11},
        # DataSetFlags1 at offset 15, bit 0 is valid flag
        dg: [{offs: 15, length: 5, vld_offs: 15, vld_chk: true, valid: 0xfe, str: "0102030405"}],
        frame: [{data: "0102030405"},{data: "fe01020304"}],
        ev: "DG_INVALID"
    },
    {
        txt: "opc_dg_code",
        opc: true,
        rtp: {wal_id: 12},
        # DataSetFlags1 at offset 15, StatusCode is little-endian at offset 18
        dg: [{offs: 15, length: 5, vld_offs: 15, code_chk: true, code: 0x8704, str: "0102030405"}],
        frame: [{data: "0102030405"},{data: "0102030487"}],
    },
    {
        txt: "opc_dg_seq",
        opc: true,
        rtp: {wal_id: 13},
        # DataSetFlags1 at offset 15, SequenceNumber is little-endian at offset 16
        dg: [{offs: 15, length: 5, vld_offs: 15, seq_chk: true, str: "0102030405"}],
        frame: [{data: "0102030405"},{data: "0102030406"}],
    },
    {
        txt: "dg_write - SRAM",
        rtp: {wal_id: 14},
        dg: [{length: 8, val: [8,7,6,5,4,3,2,1], str: "0807060504030201"}],
    },
    {
        txt: "rtp_timer - default",
        rtp: {wal_id: 15, wal_int: 2000000, rtp_int: 1000000, grp_id: 10},
        dg: [{length: 4, str: "01020304", data: [1,2,3,4]}],
        frame: [],
        ev: "RTP_STATE_STOPPED"
    },
    {
        # The previous test entry stops the group used in this test
        txt: "rtp_grp - default",
        skip_flush: 1,
        rtp: {wal_id: 16, grp_id: 10, wr_addr: 0x104},
        dg: [{length: 4, str: "05060708", data: [5,6,7,8]}],
    },
]

def time_set(conf, interval)
    time = conf["time"]
    time["offset"] = 10000
    time["interval"] = interval
end

def rte_ob_test(t)
    flush = false
    if (flush and fld_get(t, :skip_flush) > 0)
        return
    end

    # Extract test items
    opc = fld_get(t, :opc, false)
    r = t[:rce]
    e = t[:rtp]
    dg = fld_get(t, :dg, [])
    fr = fld_get(t, :frame, [{}])
    c = t[:cnt]

    # Clear events
    ev = fld_get(t, :ev, "")
    if (ev != "")
        $ts.dut.call("mera_event_poll")
    end

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
    grp_id = fld_get(e, :grp_id)
    conf["grp_id"] = grp_id
    conf["length"] = fld_get(e, :length, 46)
    conf["opc_grp_ver"] = fld_get(e, :opc_grp_ver);
    conf["pn_ds"] = fld_get(e, :pn_ds, 0x35);
    conf["pn_discard"] = fld_get(e, :pn_discard, false);
    wal_id = fld_get(e, :wal_id);
    conf["wal_enable"] = (wal_id == 0 ? false : true)
    conf["wal_id"] = wal_id
    time_set(conf, fld_get(e, :rtp_int))
    conf["time_cnt"] = 1
    $ts.dut.call("mera_ob_rtp_conf_set", $rtp_id, conf)

    # Add data group
    intf = fld_get(t, :intf, "SRAM")
    wr_addr = fld_get(e, :wr_addr, 0x100)
    dg.each_with_index do |d, i|
        conf = $ts.dut.call("mera_ob_dg_init")
        conf["dg_id"] = i
        offs = fld_get(d, :offs)
        conf["pdu_offset"] = offs
        len = fld_get(d, :length, 1)
        conf["length"] = len
        conf["invalid_default"] = fld_get(d, :inv_def, false)
        conf["valid_offset"] = fld_get(d, :vld_offs)
        conf["valid_chk"] = fld_get(d, :vld_chk, false)
        conf["opc_seq_chk"] = fld_get(d, :seq_chk, false)
        conf["opc_code_chk"] = fld_get(d, :code_chk, false)
        str = ""
        data = fld_get(d, :data, "")
        len.times do |j|
            conf["data"][j] = (data == "" ? 0 : data[j])
            str = (str + ("%02x" % (offs + j)))
        end
        if (fld_get(d, :str) == 0)
            d[:str] = str
        end
        $ts.dut.call("mera_ob_dg_add", $rtp_id, conf)

        if (d.key?:val)
            # Disable DG and write to DG memory
            ctrl = {}
            ctrl["enable"] = false
            $ts.dut.call("mera_ob_dg_ctrl_set", $rtp_id, i, ctrl)

            d[:val].each_with_index do |v, j|
                data = {}
                data["offset"] = j
                data["value"] = v
                $ts.dut.call("mera_ob_dg_data_set", $rtp_id, i, data)
            end
        end

        conf = $ts.dut.call("mera_ob_wa_init")
        conf["rtp_id"] = $rtp_id
        conf["grp_id"] = grp_id
        conf["dg_id"] = i
        addr = conf["wr_addr"]
        addr["intf"] = ("MERA_IO_INTF_" + intf)
        addr["addr"] = wr_addr
        d[:addr] = wr_addr
        wr_addr = (wr_addr + len)
        $ts.dut.call("mera_ob_wa_add", wal_id, conf)
    end

    wal_int = fld_get(e, :wal_int)
    if (wal_int > 0)
        conf = $ts.dut.call("mera_ob_wal_conf_get", wal_id)
        time_set(conf, wal_int)
        $ts.dut.call("mera_ob_wal_conf_set", wal_id, conf)
        sleep(1)
    end

    # Send frames
    et = (opc ? 0xb62c : 0x8892)
    fr.each_with_index do |f, i|
        data = fld_get(f, :data, "")
        len = (fld_get(f, :len, 46) - (data.length / 2))
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
            if (data != "")
                cmd += " data hex #{data}"
            end
            cmd += " data pattern cnt #{len - 15}"
        else
            # Profinet: Data and trailer
            cc = fld_get(f, :cc, "ccc#{i}")
            if (cc.kind_of? Array)
                cc = cc[i]
            end
            ds = fld_get(f, :ds, "35")
            ts = fld_get(f, :ts, "00")
            if (data != "")
                cmd += " data hex #{data}"
            end
            cmd += " data pattern cnt #{len - 4}"
            cmd += " data hex #{cc}#{ds}#{ts}"
        end
        run_ef_tx_rx_cmd($ts, $idx_tx, [], cmd)
    end

    # Check counters
    rx_0 = fld_get(c, :rx_0, fr.length)
    rx_1 = fld_get(c, :rx_1)
    cnt = $ts.dut.call("mera_ob_rtp_counters_get", $rtp_id)
    check_counter("rx_0", cnt["rx_0"], rx_0)
    check_counter("rx_1", cnt["rx_1"], rx_1)

    # Check PN status
    pn_mm = fld_get(e, :pn_mm)
    if (pn_mm > 0)
        status = $ts.dut.call("mera_ob_rtp_status_get", $rtp_id)
        check_val_hex_u8("pn_ds", status["pn_ds"], pn_mm)
    end

    # Check event
    if (ev != "")
        val = $ts.dut.call("mera_event_poll")
        check_val_str("event", val, "MERA_EVENT_" + ev)
    end

    # Check data groups
    use_buf = false
    if (dg.size != 0 and intf == "SRAM")
        use_buf = true
    end
    base = 0
    if (use_buf)
        buf = $ts.dut.call("mera_ob_wal_req", wal_id)
        base = buf["addr"]
    end
    dg.each_with_index do |d, i|
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
        if (d.key?:valid)
            status = $ts.dut.call("mera_ob_dg_status_get", $rtp_id, i)
            check_val_hex_u8("valid", status["valid"], d[:valid])
        end
        if (d.key?:code)
            status = $ts.dut.call("mera_ob_dg_status_get", $rtp_id, i)
            check_val_hex_u16("opc_code", status["opc_code"], d[:code])
        end
    end
    if (use_buf)
        $ts.dut.call("mera_ob_wal_rel", wal_id)
    end

    # Either flush the configuration or increment RTP ID
    if (flush)
        $ts.dut.call("mera_ob_flush")
    else
        $rtp_id = ($rtp_id + 1)
    end
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        rte_ob_test(t)
    end
end

test_summary

test "dump" do
    break
    $ts.dut.run("mera-cmd debug api ob")
    io_fpga_rw("dump 0x0100 64")
    io_sram_rw("dump 0x0100 64")
    io_sram_rw("dump 0xa900 64")
end
