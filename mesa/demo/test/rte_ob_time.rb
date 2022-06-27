#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

dut_cap_check_exit("rte")

# The test requires an external loop of port 2 and 3.
# Trace in the MERA demo application is needed to check timing.
loop_pair_check

#---------- Configuration -----------------------------------------------------

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
end

test "rte-ob-time" do
    rtp_ob = 3
    rtp_ib = 4

    # Add RCE mapping to RTP ID
    rce = $ts.dut.call("mesa_rce_init")
    rce["id"] = 1
    k = rce["key"]
    k["port_no"] = 2
    k["etype"] = "MESA_RCL_ETYPE_PROFINET"
    a = rce["action"]
    a["rtp_id"] = rtp_ob
    a["rtp_sub_id"] = false
    a["port_enable"] = true
    a["port_list"] = "#{$port_rte}"
    $ts.dut.call("mesa_rce_add", 0, rce)

    # Setup RTP-IB entry
    conf = $ts.dut.call("mera_ib_rtp_conf_get", rtp_ib)
    conf["type"] = "MERA_RTP_TYPE_PN"
    time = conf["time"]
    time["interval"] = 1000000 # 1 msec
    time["offset"]   = 500000
    conf["port"] = 3
    conf["length"] = 60
    data = conf["data"]
    data[12] = 0x88
    data[13] = 0x92
    data[56] = 0xcc;
    data[57] = 0xc0;
    data[58] = 0x35;
    data[59] = 0x00;
    $ts.dut.call("mera_ib_rtp_conf_set", rtp_ib, conf)

    # Setup RTP-OB entry
    sleep(1)
    conf = $ts.dut.call("mera_ob_rtp_conf_get", rtp_ob)
    conf["type"] = "MERA_RTP_TYPE_PN"
    conf["grp_id"] = 0
    conf["length"] = 46
    conf["opc_grp_ver"] = 0
    conf["pn_ds"] = 0x35
    conf["pn_discard"] = false
    wal_id = 0
    conf["wal_enable"] = (wal_id == 0 ? false : true)
    conf["wal_id"] = wal_id
    time = conf["time"]
    time["interval"] = 1000000 # 1 msec
    time["offset"] = 500000
    conf["time_cnt"] = 10
    $ts.dut.call("mera_ob_rtp_conf_set", rtp_ob, conf)

    # Disable RTE-IB to stop frames
    sleep(10)
    conf = $ts.dut.call("mera_ib_rtp_conf_get", rtp_ib + 1)
    $ts.dut.call("mera_ib_rtp_conf_set", rtp_ib, conf)
end

test "dump" do
    break
    $ts.dut.run("mera-cmd debug api ob")
    #io_fpga_rw("dump 0x0100 64")
    #io_sram_rw("dump 0x0100 64")
    #io_sram_rw("dump 0xa900 64")
end
