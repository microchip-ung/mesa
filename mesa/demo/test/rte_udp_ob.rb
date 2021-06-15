#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_tx   = 0 # PC Tx port
$idx_loop = 1 # Loop port
$rtp_id   = 1

test "qspi-init" do
    # Initialize QSPI
    qspi_init

    # Clear IO memory
    io_fpga_rw("fill 0x0100 0x100 0")
end

test "mesa-conf" do
    port_tx = $ts.dut.p[$idx_tx]
    port_loop = $ts.dut.p[$idx_loop]

    # Redirect UDP frames from Tx port to loop port
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_IPV4")
    ace["id"] = 1
    ace["port_list"] = "#{port_tx}"
    ipv4 = ace["frame"]["ipv4"]
    proto = ipv4["proto"]
    proto["value"] = 17
    proto["mask"] = 0xff
    dport = ipv4["dport"]
    dport["in_range"] = true
    dport["low"] = 4840
    dport["high"] = 4840
    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_REDIR"
    action["port_list"] = "#{port_loop}"
    $ts.dut.call("mesa_ace_add", 0, ace)

    # Set loop port to tag frames with EType OPC-UA
    $ts.dut.call("mesa_vlan_conf_set", { s_etype: 0xb62c })
    $ts.dut.run("symreg vlan_etype_cfg 0x88a8")
    conf = $ts.dut.call("mesa_vlan_port_conf_get", port_loop)
    conf["untagged_vid"] = 0
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_S_CUSTOM"
    $ts.dut.call("mesa_vlan_port_conf_set", port_loop, conf);

    # Enable loop on loop port
    conf = $ts.dut.call("mesa_port_conf_get", port_loop)
    conf["loop"] = "MESA_PORT_LOOP_PCS_HOST"
    $ts.dut.call("mesa_port_conf_set", port_loop, conf)

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
    k["port_no"] = port_loop
    k["etype"] = "MESA_RCL_ETYPE_OPC_UA"
    a = rce["action"]
    a["rtp_id"] = $rtp_id
    a["port_enable"] = true
    a["port_list"] = "#{port_rte}"
    $ts.dut.call("mesa_rce_add", 0, rce)
end

test "mera-conf" do
    # Disable OPC-UA header checks
    $ts.dut.run("symreg opc_pdu_flags 0")
    $ts.dut.run("symreg opc_pdu_misc 0")
    ttl = 31 # IPv4 TTL field is seen as part of NMSG_NUM
    $ts.dut.run("symreg opc_pdu_misc.opc_network_msg_num #{ttl * 256}")

    # Setup RTP entry
    wal_id = 2
    conf = $ts.dut.call("mera_ob_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_OPC_UA"
    conf["length"] = 52
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
    conf["pdu_offset"] = (4 + 28 + 15)
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
    data = "0504030201"
    cmd = "eth dmac 2 ipv4 dip 225.1.2.3 udp dport 4840"

    # OPC-UA: Header and data
    ver = "1"
    flags = "b"
    flags1 = "01"
    gflags = "0f"
    gver = "00000000" # Little-endian
    nmsg_num = "0100" # Little-endian
    cmd += " data hex #{flags}#{ver}#{flags1}aaaa#{gflags}bbbb#{gver}#{nmsg_num}cccc"
    cmd += " data hex #{data}"
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
    #$ts.dut.run("mesa-cmd port stati pac")
    #$ts.dut.run("mera-cmd debug api ob")
    io_fpga_rw("dump 0x0100 16")
end
