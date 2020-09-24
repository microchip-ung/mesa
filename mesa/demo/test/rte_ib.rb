#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$port = [] # Chip ports
$rtp_id = 3

test "conf" do
    # Find chip Tx port
    port_cnt = cap_get("PORT_CNT")
    map = $ts.dut.call("mesa_port_map_get", port_cnt)
    [0, 1, 2, 3].each do |idx|
        $port[idx] = map[$ts.dut.p[idx]]["chip_port"]
    end

    # Enable RTE
    conf = $ts.dut.call("mera_gen_conf_get")
    conf["enable"] = true
    $ts.dut.call("mera_gen_conf_set", conf)

    # Initialize QSPI
    qspi_init

    # Clear IO-FPGA memory
    io_fpga_rw("fill 0x100 0x100 0")
end

# Push Profinet APDU status
def cmd_apdu_push(apdu = {})
    pcp = "ign"
    dei = "ign"
    vid = "ign"
    if (apdu.key?:cc)
        cc = a[:cc]
        pcp = ((cc >> 13) & 0x7)
        dei = ((cc >> 12) & 0x1)
        vid = (cc & 0xfff)
    end
    et = "ign"
    if (apdu.key?:ds)
        et = (apdu[:ds] << 8)
    end
    cmd = " ctag pcp #{pcp} dei #{dei} vid #{vid} et #{et}"
end

def tx_len_test(len)
    idx_rx = 1
    $rtp_id = ($rtp_id + 1)
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    # One-shot time by default
    conf["port"] = $port[idx_rx]
    conf["length"] = len
    for i in 0..(len - 1) do
        # Ethernet frame:
        # DMAC : ff-ff-ff-ff-ff-ff
        # SMAC : 00-00-00-00-00-01
        # EType: 0xaaaa
        # Data : Incrementing from 0
        d = (i < 6 ? 0xff : i < 11 ? 0 : i < 12 ? 1 : i < 14 ? 0xaa : ((i - 14) & 0xff))
        conf["data"][i] = d
    end
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)
    cmd = "sudo ef -t 1000 name f1 eth et 0xaaaa data pattern cnt #{len - 18}"
    cmd += cmd_apdu_push
    [0, 1, 2, 3].each do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == idx_rx)
            cmd += " name f1"
        end
    end
    $ts.pc.run(cmd)
end

test "tx-data-min" do
    tx_len_test(60)
end

test "tx-data-max" do
    tx_len_test(1514)
end

def tx_time_test(idx, time, margin)
    $rtp_id = ($rtp_id + 1)
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    conf["time"]["interval"] = time
    conf["port"] = $port[idx]
    len = 60
    conf["length"] = len
    for i in 0..(len - 1) do
        conf["data"][i] = 0
    end
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)

    tx_cnt = 10
    cmd = "sudo ef -c #{$ts.pc.p[idx]},1,adapter_unsynced,,#{tx_cnt} "
    $ts.pc.run(cmd)
    pkts = $ts.pc.get_pcap("#{$ts.links[idx][:pc]}.pcap")
    cnt = pkts.size
    if (cnt != tx_cnt)
        t_e("Only #{cnt} packets logged");
    else
        time = (time / 1000) # Convert from nsec to usec
        t_i("Logged #{cnt} packets")
        t0 = 0
        t0_valid = false
        pkts.each do |p|
            t = p[:us_rel]
            diff = (t - t0)
            txt = "(t: #{t}, t0: #{t0}, diff: #{diff})"
            if (t0_valid and ((diff + margin) < time or diff > (time + margin)))
                t_e(txt)
            else
                t_i(txt)
            end
            t0 = t
            t0_valid = true
        end
    end

    # Show counters
    cnt = $ts.dut.call("mera_ib_rtp_counters_get", $rtp_id)
    t_i("cnt: #{cnt}")

    # Disable RTP to stop transmissions
    conf["type"] = "MERA_RTP_TYPE_DISABLED"
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)
end

test "tx-interval-min" do
    # 10 usec
    tx_time_test(2, 10000, 2)
end

test "tx-interval-max" do
    # 10 msec
    tx_time_test(1, 10000000, 20)
end

test "otf" do
    idx_tx = 0
    idx_rx = 1

    # Enable untagged RTP processing
    conf = { "pcp": [true, true, true, true, true, true, true, true]}
    $ts.dut.call("mesa_rcl_vid_add", 0, conf)

    # Add RCE enabling inbound processing
    $rtp_id = ($rtp_id + 1)
    rce = $ts.dut.call("mesa_rce_init")
    rce["id"] = 1
    k = rce["key"]
    k["port_no"] = $ts.dut.p[idx_tx]
    k["etype"] = "MESA_RCL_ETYPE_OPC_UA"
    a = rce["action"]
    a["rtp_id"] = $rtp_id
    a["rtp_inbound"] = true
    a["port_enable"] = true
    a["port_list"] = "#{$ts.dut.p[idx_rx]}"
    $ts.dut.call("mesa_rce_add", 0, rce)

    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_OPC_UA"
    conf["mode"] = "MERA_RTP_IB_MODE_OTF"
    len = 60
    conf["length"] = len
    offs = 14 # Update data at offset 14
    conf["data"][offs] = 0xaa
    conf["update"][offs] = 1
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)

    f1 = "eth dmac 2 et 0xb62c"
    cmd = "sudo ef name f1 #{f1} name f2 #{f1} data hex aa"
    cmd += " tx #{$ts.pc.p[idx_tx]} name f1"
    [0, 1, 2, 3].each do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == idx_rx)
            cmd += " name f2"
        end
    end
    $ts.pc.run(cmd)

    cnt = $ts.dut.call("mera_ib_rtp_counters_get", $rtp_id)
    check_counter("tx_otf", cnt["tx_otf"], 1)
end

def fld_get(v, fld, val = 0)
    if (v != nil and v.key?(fld))
        val = v[fld]
    end
    val
end

def tx_dg_test(intf, ral_id, opc = false)
    len = 60
    idx_rx = 1
    $rtp_id = ($rtp_id + 1)
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = ("MERA_RTP_TYPE_" + (opc ? "OPC_UA" : "PN"))
    time = conf["time"]
    time["offset"] = 1000000 # One msec
    time["interval"] = 1000000000 # One second
    conf["port"] = $port[idx_rx]
    conf["length"] = len
    payload = ""
    for i in 0..(len - 1) do
        d = (i < 6 ? 0xff : i < 11 ? 0 : i < 12 ? 1 : i < 14 ? 0xaa : $rtp_id)
        conf["data"][i] = d
        if (i > 13 and i < (len - 4))
            payload = (payload + ("%02x" % d))
        end
    end
    rtp_conf = conf
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)

    rd_addr = 0x100
    ra_id = 3
    use_buf = (intf == "SRAM")
    base = 0
    if (use_buf)
        buf = $ts.dut.call("mera_ib_ral_req", ral_id)
        base = buf["addr"]
    end
    dg = [{offs: 0, data: "0123456789ab"},
          {offs: 7, data: "ef", vld_offs: 8, vld_update: true},
          {offs: 12, data: "9876", vld_offs: 14, code_update: true}]
    dg.each do |d|
        offs = (d[:offs] * 2)
        data = d[:data]
        size = data.length
        payload[offs..(offs + size - 1)] = data
        size = (size / 2)
        conf = $ts.dut.call("mera_ib_ra_init")
        conf["ra_id"] = ra_id
        addr = conf["rd_addr"]
        addr["intf"] = ("MERA_IO_INTF_" + intf)
        addr["addr"] = rd_addr
        conf["length"] = size
        $ts.dut.call("mera_ib_ra_add", ral_id, conf)

        conf = $ts.dut.call("mera_ib_dg_init")
        conf["rtp_id"] = $rtp_id
        conf["pdu_offset"] = d[:offs]
        vld_offs = fld_get(d, :vld_offs)
        conf["valid_offset"] = vld_offs
        vld_update = fld_get(d, :vld_update, false)
        conf["valid_update"] = vld_update
        code_update = fld_get(d, :code_update, false)
        conf["opc_code_update"] = code_update
        $ts.dut.call("mera_ib_dg_add", ral_id, ra_id, conf)
        if (vld_update)
            # PN/OPC valid update
            offs = (vld_offs * 2)
            payload[offs..(offs + 1)] = (opc ? "1d" : "80")
        end
        if (opc and code_update)
            # OPC status code update at offset 3 from valid byte
            offs = ((vld_offs + 3) * 2)
            payload[offs..(offs + 1)] = "00"
        end
        io_str_wr(rd_addr + base, d[:data], intf)
        rd_addr = (rd_addr + size)
        ra_id = (ra_id + 1)
    end
    if (use_buf)
        $ts.dut.call("mera_ib_ral_rel", ral_id)
    end

    # Start RAL timer
    conf = $ts.dut.call("mera_ib_ral_conf_get", ral_id)
    time = conf["time"]
    conf["time"]["interval"] = 1000000000 # One second, offset zero
    $ts.dut.call("mera_ib_ral_conf_set", ral_id, conf)

    sleep(1)
    # Easyframe runs a little longer, so 900 msec means about a second.
    cmd = "sudo ef -t 900 name f1 eth et 0xaaaa data hex #{payload}"
    cmd += cmd_apdu_push
    [0, 1, 2, 3].each do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == idx_rx)
            cmd += " name f1"
        end
    end
    $ts.pc.run(cmd)

    # Disable RTP to stop transmissions
    conf = rtp_conf
    conf["type"] = "MERA_RTP_TYPE_DISABLED"
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)
end

test "dg-QSPI" do
    tx_dg_test("QSPI", 1)
end

test "dg-SRAM-PN" do
    tx_dg_test("SRAM", 2)
end

test "dg-SRAM-OPC" do
    tx_dg_test("SRAM", 3, true)
end

test "dump" do
    break
    $ts.dut.run("mera-cmd debug api ib")
    io_fpga_rw("dump 0x0100 64")
    io_sram_rw("dump 0x0100 64")
end
