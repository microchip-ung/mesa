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

end

test "rte-ob-restart" do
    # Add RCE mapping to RTP ID
    rce = $ts.dut.call("mesa_rce_init")
    rce["id"] = 1
    k = rce["key"]
    k["port_no"] = $ts.dut.p[$idx_tx]
    k["etype"] = "MESA_RCL_ETYPE_PROFINET"
    a = rce["action"]
    a["rtp_id"] = $rtp_id
    a["port_enable"] = true
    a["port_list"] = "#{$port_rte}"
    $ts.dut.call("mesa_rce_add", 0, rce)

    # Prepare RTP config
    len = 46
    conf = $ts.dut.call("mera_ob_rtp_conf_get", $rtp_id)
    conf["type"] = "MERA_RTP_TYPE_PN"
    conf["length"] = len
    conf["pn_ds"] = 0x35;
    conf["pn_discard"] = false;
    wal_id = 0
    conf["wal_enable"] = (wal_id == 0 ? false : true)
    conf["wal_id"] = wal_id
    time = conf["time"]

    cmd = "ef name f1 eth dmac 2 et 0x8892 data pattern cnt #{len - 4} data hex ccc03500"
    cmd += " tx #{$ts.pc.p[$idx_tx]} "

    2.times do |i|
        # Setup RTP without timer
        time["offset"] = 0
        time["interval"] = 0
        conf["time_cnt"] = 0
        $ts.dut.call("mera_ob_rtp_conf_set", $rtp_id, conf)

        # Send frame
        $ts.pc.run(cmd + "name f1")

        # Get counter
        $ts.dut.call("mera_ob_rtp_counters_get", $rtp_id)

        # Send frames in background, to test timeout counter clear
        #$ts.pc.bg("ef tx", cmd + "rep 1000000 name f1")

        # Setup RTP with timer
        time["offset"] = 1000
        time["interval"] = 1000000
        conf["time_cnt"] = 5
        $ts.dut.call("mera_ob_rtp_conf_set", $rtp_id, conf)

        $ts.pc.run(cmd + "name f1")
        $ts.dut.call("mera_ob_rtp_counters_get", $rtp_id)
        # Wait a while
        sleep(1)
    end
end

test "dump" do
    #$ts.dut.run("mera-cmd debug api ob")
    #$ts.dut.run("mesa-cmd port stati pac")
    #$ts.dut.run("mesa-cmd port stati 3,4")
end
