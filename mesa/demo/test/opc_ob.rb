#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0 # PC Tx port
$rtp_id = 1

test "qspi-init" do
    # Initialize QSPI
    qspi_init

    # Clear IO memory
    io_fpga_rw("fill 0x0100 0x100 0")
end

test "mesa-conf" do
    # When OPC-UA MESA demo code is done, replace setup by this:
    # $ts.dut.run("mesa-cmd example init opc_ua port #{$ts.dut.p[$idx_tx]} ...")
    $ts.dut.run("mesa-cmd example init opc_ua iport 0")

    break;

    # Find MESA port mapping to RTE port (4)
    port_rte = nil
    port_cnt = cap_get("PORT_CNT")
    map = $ts.dut.call("mesa_port_map_get", port_cnt)
    for port in 0..(port_cnt - 1)
        if (map[port]["chip_port"] == 4)
            port_rte = port
        end
    end
    if (port_rte == nil)
        t_e("RTE port not found")
    else
        t_i("RTE port: #{port_rte}")
    end

    # Enable untagged RTP processing
    conf = { "pcp": [true, true, true, true, true, true, true, true]}
    $ts.dut.call("mesa_rcl_vid_add", 0, conf)

    # Add RCE mapping to RTP ID
    rce = $ts.dut.call("mesa_rce_init")
    rce["id"] = 1
    k = rce["key"]
    k["port_no"] = $ts.dut.p[$idx_tx]
    k["etype"] = "MESA_RCL_ETYPE_OPC_UA"
    a = rce["action"]
    a["rtp_id"] = $rtp_id
    a["port_enable"] = true
    a["port_list"] = "#{port_rte}"
    $ts.dut.call("mesa_rce_add", 0, rce)
end

test "mera-conf" do
    # When OPC-UA MERA demo code is done, the setup below may be replaced by:
    $ts.dut.run("mera-cmd opc 1")

    break

    # Setup RTP entry
    wal_id = 2
    conf = $ts.dut.call("mera_ob_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_OPC_UA"
    conf["length"] = 46
    conf["opc_grp_ver"] = 0
    conf["wal_enable"] = true
    conf["wal_id"] = wal_id
    time = conf["time"]
    time["offset"] = 10000
    time["interval"] = 0
    conf["time_cnt"] = 1
    $ts.dut.call("mera_ob_rtp_conf_set", $rtp_id, conf)

    # Add data group
    conf = $ts.dut.call("mera_ob_dg_init")
    conf["dg_id"] = 0
    conf["pdu_offset"] = 15
    conf["length"] = 5
    conf["invalid_default"] = false
    conf["valid_offset"] = 0
    conf["valid_chk"] = false
    conf["opc_seq_chk"] = false
    conf["opc_code_chk"] = false
    $ts.dut.call("mera_ob_dg_add", $rtp_id, conf)

    # Add Write action
    conf = $ts.dut.call("mera_ob_wa_init")
    conf["rtp_id"] = $rtp_id
    conf["dg_id"] = 0
    addr = conf["wr_addr"]
    addr["intf"] = "MERA_IO_INTF_QSPI"
    addr["addr"] = 0x100
    $ts.dut.call("mera_ob_wa_add", wal_id, conf)
end

test "frame-io" do
    # Build frame command
    data = "0102030405"
    len = (46 - (data.length / 2))
    cmd = "eth dmac 2 et 0xb62c"

    # OPC-UA: Header and data
    ver = "1"
    flags = "b"
    flags1 = "01"
    gflags = "0f"
    gver = "00000000" # Little-endian
    nmsg_num = "0100" # Little-endian
    cmd += " data hex #{flags}#{ver}#{flags1}aaaa#{gflags}bbbb#{gver}#{nmsg_num}cccc"
    cmd += " data hex #{data}"
    cmd += " data pattern cnt #{len - 15}"
    run_ef_tx_rx_cmd($ts, $idx_tx, [], cmd)

    # Check data group
    intf = "QSPI"
    addr = 0x100
    res = io_str_rd(addr, data, intf)
    t_i("Exp (#{intf}): #{data}")
    act = ("0x%08x: #{res}" % addr)
    if (res == data)
        t_i(act)
    else
        t_e(act)
    end
end

test "dump" do
    #$ts.dut.run("mera-cmd debug api ob")
    io_fpga_rw("dump 0x0100 64")
end
