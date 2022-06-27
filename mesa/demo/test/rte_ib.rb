#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

dut_cap_check_exit("rte")

#---------- Configuration -----------------------------------------------------

$idx_tx  = 0 # PC Tx port
$idx_rx  = 1 # PC Rx port
$port_tx = nil # Chip Tx port
$rtp_id = 3

test "conf" do
    # Find chip Tx port
    port_cnt = cap_get("PORT_CNT")
    map = $ts.dut.call("mesa_port_map_get", port_cnt)
    $port_tx = map[$ts.dut.p[$idx_rx]]["chip_port"]

    # Initialize QSPI
    qspi_init

    # Clear IO-FPGA memory
    io_fpga_rw("fill 0x100 0x100 0")
end

def rte_next_test
    # Either flush the configuration or increment RTP ID
    if (true)
        $rtp_id = ($rtp_id + 1)
    else
        $ts.dut.call("mera_ib_flush")
    end
end

def cmd_payload_push(payload)
    len = payload.length
    i = 0
    cmd = ""
    data = ""
    while (i < len)
        j = (i + 7)
        if (j == (len - 1) or payload[i..(i + 3)] == "xxxx")
            # PN CC or wildcard
            if (data.length > 0)
                cmd += " data hex #{data}"
                data = ""
            end
            # Ignore 2 bytes using ctag
            cmd += " ctag pcp ign dei ign vid ign et 0x#{payload[(i+4)..j]}"
        else
            j = (i + 1)
            data = (data + payload[i..j])
        end
        i = (j + 1)
    end
    if (data.length > 0)
        cmd += " data hex #{data}"
    end
    cmd
end

def tx_len_test(len)
    rte_next_test
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    time = conf["time"]
    time["interval"] = 128000000 # 128 msec
    conf["port"] = $port_tx
    conf["length"] = len
    payload = ""
    for i in 0..(len - 1) do
        # Ethernet frame:
        # DMAC : ff-ff-ff-ff-ff-ff
        # SMAC : 00-00-00-00-00-01
        # EType: 0xaaaa
        # Data : Incrementing from 0
        d = (i < 6 ? 0xff : i < 11 ? 0 : i < 12 ? 1 : i < 14 ? 0xaa : ((i - 14) & 0xff))
        if (i > (len - 5))
            # PN trailer added as payload
            payload += ("%02x" % d)
        end
        conf["data"][i] = d
    end
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)
    cmd = "sudo ef -t 60 name f1 eth et 0xaaaa data pattern cnt #{len - 18}"
    cmd += cmd_payload_push(payload)
    $ts.pc.p.each_index do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == $idx_rx)
            cmd += " name f1"
        end
    end
    $ts.pc.run(cmd)

    # Disable timer to stop transmissions
    time["interval"] = 0
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)
end

def tx_time_test(time, margin)
    rte_next_test
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    conf["time"]["interval"] = time
    conf["port"] = $port_tx
    len = 60
    conf["length"] = len
    for i in 0..(len - 1) do
        conf["data"][i] = 0
    end
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)

    tx_cnt = 10
    cmd = "sudo ef -c #{$ts.pc.p[$idx_rx]},1,adapter_unsynced,,#{tx_cnt} "
    $ts.pc.run(cmd)
    pkts = $ts.pc.get_pcap("#{$ts.links[$idx_rx][:pc]}.pcap")
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

def otf_test
    # Enable untagged RTP processing
    conf = { "pcp": [true, true, true, true, true, true, true, true]}
    $ts.dut.call("mesa_rcl_vid_add", 0, conf)

    # Add RCE enabling inbound processing
    rte_next_test
    rce = $ts.dut.call("mesa_rce_init")
    rce["id"] = 1
    k = rce["key"]
    k["port_no"] = $ts.dut.p[$idx_tx]
    k["etype"] = "MESA_RCL_ETYPE_OPC_UA"
    a = rce["action"]
    a["rtp_id"] = $rtp_id
    a["rtp_inbound"] = true
    a["port_enable"] = true
    a["port_list"] = "#{$ts.dut.p[$idx_rx]}"
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
    cmd += " tx #{$ts.pc.p[$idx_tx]} name f1"
    $ts.pc.p.each_index do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == $idx_rx)
            cmd += " name f2"
        end
    end
    $ts.pc.run(cmd)

    cnt = $ts.dut.call("mera_ib_rtp_counters_get", $rtp_id)
    check_counter("tx_otf", cnt["tx_otf"], 1)
end

def tx_dg_test(intf, ral_id, opc = false)
    len = 60
    rte_next_test
    conf = $ts.dut.call("mera_ib_rtp_conf_get", $rtp_id)
    conf["type"] = ("MERA_RTP_TYPE_" + (opc ? "OPC_UA" : "PN"))
    time = conf["time"]
    time["offset"]   =   1000000 # 1 msec
    time["interval"] = 128000000 # 128 msec
    conf["port"] = $port_tx
    conf["length"] = len
    payload = ""
    for i in 0..(len - 1) do
        d = (i < 6 ? 0xff : i < 11 ? 0 : i < 12 ? 1 : i < 14 ? 0xaa : $rtp_id)
        conf["data"][i] = d
        if (i > 13)
            payload += ("%02x" % d)
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
          {offs: 12, data: "9876", vld_offs: 14, seq_update: true, code_update: true},
          {offs: 20, data: "0102030405060708", val: [8,7,6,5,4,3,2,1]}]
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

        if (d.key?:val and use_buf == false)
            # Disable RA and write to frame memory
            ctrl = {}
            ctrl["enable"] = false
            $ts.dut.call("mera_ib_ra_ctrl_set", ral_id, ra_id, ctrl)

            d[:val].each_with_index do |v, j|
                data = {}
                offs = (d[:offs] + j)
                data["offset"] = (14 + offs)
                data["value"] = v
                offs = (offs * 2)
                payload[offs..(offs + 1)] = ("%02x" % v)
                $ts.dut.call("mera_ib_rtp_data_set", $rtp_id, data)
            end
        end

        conf = $ts.dut.call("mera_ib_dg_init")
        conf["rtp_id"] = $rtp_id
        conf["pdu_offset"] = d[:offs]
        vld_offs = fld_get(d, :vld_offs)
        conf["valid_offset"] = vld_offs
        vld_update = fld_get(d, :vld_update, false)
        conf["valid_update"] = vld_update
        seq_update = fld_get(d, :seq_update, false)
        conf["opc_seq_update"] = seq_update
        code_update = fld_get(d, :code_update, false)
        conf["opc_code_update"] = code_update
        $ts.dut.call("mera_ib_dg_add", ral_id, ra_id, conf)
        if (vld_update)
            # PN/OPC valid update
            offs = (vld_offs * 2)
            payload[offs..(offs + 1)] = (opc ? "1d" : "80")
        end
        if (opc and seq_update)
            # OPC sequence number update at offset 1 from valid byte
            offs = ((vld_offs + 1) * 2)
            payload[offs..(offs + 3)] = "xxxx"
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
    conf["time"]["interval"] = 128000000 # 128 msec, offset zero
    $ts.dut.call("mera_ib_ral_conf_set", ral_id, conf)
    sleep(1)

    # Easyframe runs a little longer than the specified time
    cmd = "sudo ef -t 60 name f1 eth et 0xaaaa"
    cmd += cmd_payload_push(payload)
    $ts.pc.p.each_index do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == $idx_rx)
            cmd += " name f1"
        end
    end
    $ts.pc.run(cmd)

    # Disable RTP to stop transmissions
    conf = rtp_conf
    conf["type"] = "MERA_RTP_TYPE_DISABLED"
    $ts.dut.call("mera_ib_rtp_conf_set", $rtp_id, conf)
end

test "tx-data-min" do
    tx_len_test(60)
end

test "tx-data-max" do
    tx_len_test(1514)
end

test "tx-interval-min" do
    # 31.25 usec
    tx_time_test(31250, 2)
end

test "tx-interval-max" do
    # 128 msec
    tx_time_test(128000000, 20)
end

test "otf" do
    otf_test
end

test "dg-qspi" do
    tx_dg_test("QSPI", 1)
end

test "dg-sram-pn" do
    tx_dg_test("SRAM", 2)
end

test "dg-sram-opc" do
    tx_dg_test("SRAM", 3, true)
end

test_summary

test "dump" do
    break
    $ts.dut.run("mera-cmd debug api ib")
    io_fpga_rw("dump 0x0100 64")
    io_sram_rw("dump 0x0100 64")
end
