#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

dut_cap_check_exit("rte")

#---------- Configuration -----------------------------------------------------

port_rte = nil

test "config" do
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
end

test "rte-ob-timer" do
    idx_tx  = 0 # PC Tx port
    rtp_id = 3

    # Enable untagged RTP processing
    conf = { "pcp": [true, true, true, true, true, true, true, true]}
    $ts.dut.call("mesa_rcl_vid_add", 0, conf)

    # Enable loopback on port
    port = $ts.dut.p[idx_tx]
    $ts.dut.run("mesa-cmd port loopback #{port + 1} near-end")

    # Add RCE mapping to RTP ID
    rce = $ts.dut.call("mesa_rce_init")
    rce["id"] = 1
    k = rce["key"]
    k["port_no"] = port
    k["etype"] = "MESA_RCL_ETYPE_PROFINET"
    a = rce["action"]
    a["rtp_id"] = rtp_id
    a["port_enable"] = true
    a["port_list"] = "#{$port_rte}"
    $ts.dut.call("mesa_rce_add", 0, rce)

    # Allocate AFI
    t_i("allocate afi injection")
    cfg = {}
    cfg["port_no"] = port
    cfg["prio"] = 0
    cfg["frm_cnt"] = 1
    cfg["masquerade_port_no"] = 0
    id = $ts.dut.call("mesa_afi_fast_inj_alloc", cfg)

    # Send and hijack frame
    t_i("send frame before hijacking")
    len = 60
    tx_info = $ts.dut.call("mesa_packet_tx_info_init")
    tx_info["dst_port_mask"] = (1 << port)
    tx_info["cos"] = 0
    tx_info["afi_id"] = id
    frame = []
    for i in 0..(len - 1)
        frame[i] = (i == 5 ? 2 : i == 11 ? 1 : i == 12 ? 0x88 : i == 13 ? 0x92 : 0)
    end
    $ts.dut.call("mesa_packet_tx_frame", tx_info, frame, len);
    cfg = {}
    cfg["frm_size"] = len
    $ts.dut.call("mesa_afi_fast_inj_frm_hijack", id, cfg)

    t_i("start afi")
    rate = 1000
    cfg = {}
    cfg["bps"] = ((len + 4) * 8 * rate)
    cfg["seq_cnt"] = 0
    $ts.dut.call("mesa_afi_fast_inj_start", id, cfg)
    test_sleep(1)

    # Setup RTP entry
    conf = $ts.dut.call("mera_ob_rtp_conf_get", rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    conf["length"] = (len - 14)
    time = conf["time"]
    time["offset"] = 10000
    time["interval"] = 1000000
    conf["time_cnt"] = 3
    $ts.dut.call("mera_ob_rtp_conf_set", rtp_id, conf)

    # Stop AFI
    test_sleep(5)
    $ts.dut.call("mesa_afi_fast_inj_stop", id)
    $ts.dut.call("mesa_afi_fast_inj_free", id)
end

test_summary

test "dump" do
    test_sleep(2)
    $ts.dut.run("mera-cmd debug api ob")
    break
    $ts.dut.run("mesa-cmd port stati 1")
end
