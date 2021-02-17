#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_rx = 1

# Global variable for frame, input data etc.
$g = {port: 0, len: 60, frame: [], offs: 10, data: [5,4,3,2,1], addr: 0x100}

test "qspi-init" do
    # Build frame
    for i in 0..($g[:len] - 1) do
        $g[:frame][i] = (i < 6 ? 0xff : i < 11 ? 0 : i < 12 ? 1 : i < 14 ? 0xaa : 0)
    end

    # Find chip Tx port
    port_cnt = cap_get("PORT_CNT")
    map = $ts.dut.call("mesa_port_map_get", port_cnt)
    $g[:port] = map[$ts.dut.p[$idx_rx]]["chip_port"]

    # Initialize QSPI
    qspi_init

    # Clear IO-FPGA memory
    io_fpga_rw("fill 0x100 0x100 0")

    # Write data to QSPI
    data = $g[:data]
    str = ""
    for i in 0..(data.length - 1) do
        str += ("%02x" % data[i])
    end
    io_str_wr($g[:addr], str, "QSPI")
end

test "mera-conf" do
    # When OPC-UA MERA demo code is done, the setup below may be replaced by:
    $ts.dut.run("mera-cmd opc 2")

    # Setup RTP entry
    rtp_id = 1
    conf = $ts.dut.call("mera_ib_rtp_conf_get", rtp_id)
    conf["type"] = "MERA_RTP_TYPE_OPC_UA"
    time = conf["time"]
    time["offset"] = 1000000 # One msec
    time["interval"] = 1000000000 # One second
    conf["port"] = $g[:port]
    len = $g[:len]
    conf["length"] = len
    for i in 0..(len - 1) do
        conf["data"][i] = $g[:frame][i]
    end
    $ts.dut.call("mera_ib_rtp_conf_set", rtp_id, conf)

    # Add RA
    ra_id = 3
    ral_id = 1
    conf = $ts.dut.call("mera_ib_ra_init")
    conf["ra_id"] = ra_id
    addr = conf["rd_addr"]
    addr["intf"] = "MERA_IO_INTF_QSPI"
    addr["addr"] = $g[:addr]
    conf["length"] = $g[:data].length
    $ts.dut.call("mera_ib_ra_add", ral_id, conf)

    # Add DG
    conf = $ts.dut.call("mera_ib_dg_init")
    conf["rtp_id"] = rtp_id
    conf["pdu_offset"] = $g[:offs]
    conf["valid_offset"] = 0
    conf["valid_update"] = false
    conf["opc_seq_update"] = false
    conf["opc_code_update"] = false
    $ts.dut.call("mera_ib_dg_add", ral_id, ra_id, conf)

    # Start RAL timer
    conf = $ts.dut.call("mera_ib_ral_conf_get", ral_id)
    time = conf["time"]
    conf["time"]["interval"] = 1000000000 # One second, offset zero
    $ts.dut.call("mera_ib_ral_conf_set", ral_id, conf)
    sleep(1)
end

test "frame-io" do
    # Calculate frame hex string
    str = ""
    offs = $g[:offs]
    data = $g[:data]
    for i in 0..($g[:len] - 1) do
        j = (i - 14)
        d = ((j >= offs and j < (offs + data.length)) ? data[j - offs] : $g[:frame][i])
        str += ("%02x" % d)
    end

    # Easyframe runs a little longer, so 900 msec means about a second.
    cmd = "sudo ef -t 900 name f1 data hex #{str}"
    [0, 1, 2, 3].each do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == $idx_rx)
            cmd += " name f1"
        end
    end
    $ts.pc.run(cmd)
end

test "dump" do
    #$ts.dut.run("mera-cmd debug api ib")
    io_fpga_rw("dump 0x0100 64")
end
