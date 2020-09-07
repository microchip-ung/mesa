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

def tx_len_test(len)
    idx_rx = 1
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    conf["time"] = 0 # One-shot
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
    $rtp_id = ($rtp_id + 1)
    cmd = "sudo ef -t 1000 name f1 eth et 0xaaaa data pattern cnt #{len - 14}"
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
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    conf["time"] = time
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
    $rtp_id = ($rtp_id + 1)
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
    $rtp_id = ($rtp_id + 1)
end

def tx_dg_test(intf, ral_id)
    # I/O interface is a global setting, but setup here for test purposes only.
    conf = $ts.dut.call("mera_gen_conf_get")
    conf["intf"] = ("MERA_IO_INTF_" + intf)
    $ts.dut.call("mera_gen_conf_set", conf)
    use_buf = (intf == "SRAM")

    len = 60
    idx_rx = 1
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    conf["time"] = 1000000000 # One second
    conf["port"] = $port[idx_rx]
    conf["length"] = len
    payload = ""
    for i in 0..(len - 1) do
        d = (i < 6 ? 0xff : i < 11 ? 0 : i < 12 ? 1 : i < 14 ? 0xaa : 0xff)
        conf["data"][i] = d
        if (i > 13)
            payload = (payload + ("%02x" % d))
        end
    end
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)

    conf = $ts.dut.call("mera_ib_ral_conf_get", ral_id)
    conf["time"] = 1000000000 # One second
    $ts.dut.call("mera_ib_ral_conf_set", ral_id, conf)

    rd_addr = 0x100
    ra_id = 3
    dg = [{offs: 0, data: "0123456789ab"},{offs: 7, data: "ef"}]
    dg.each do |d|
        offs = (d[:offs] * 2)
        data = d[:data]
        size = data.length
        payload[offs..(offs + size - 1)] = data
        size = (size / 2)
        conf = $ts.dut.call("mera_ib_ra_init")
        conf["ra_id"] = ra_id
        conf["rd_addr"] = rd_addr
        conf["length"] = size
        $ts.dut.call("mera_ib_ra_add", ral_id, conf)

        conf = $ts.dut.call("mera_ib_dg_init")
        conf["rtp_id"] = $rtp_id
        conf["pdu_offset"] = d[:offs]
        $ts.dut.call("mera_ib_dg_add", ral_id, ra_id, conf)

        addr = rd_addr
        if (use_buf)
            buf = $ts.dut.call("mera_ib_ra_req", ral_id, ra_id)
            addr = (addr + buf["addr"])
        end
        io_str_wr(addr, d[:data], intf)
        if (use_buf)
            $ts.dut.call("mera_ib_ra_rel", ral_id, ra_id)
        end
        rd_addr = (rd_addr + size)
        ra_id = (ra_id + 1)
    end

    sleep(1)
    cmd = "sudo ef -t 1000 name f1 eth et 0xaaaa data hex #{payload}"
    [0, 1, 2, 3].each do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == idx_rx)
            cmd += " name f1"
        end
    end
    $ts.pc.run(cmd)
    $rtp_id = ($rtp_id + 1)
end

test "dg-QSPI" do
    tx_dg_test("QSPI", 1)
end

test "dg-SRAM" do
    tx_dg_test("SRAM", 2)
end

test "dump" do
    #$ts.dut.run("mera-cmd debug api ib")
    #$ts.dut.call("mera_ib_flush")
    #$ts.dut.run("mera-cmd debug api ib")
    #io_fpga_rw("dump 0x100 64")
end
