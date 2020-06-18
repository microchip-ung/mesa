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
    conf = $ts.dut.call("lan9662_rte_gen_conf_get")
    conf["enable"] = true
    $ts.dut.call("lan9662_rte_gen_conf_set", conf)
end

def tx_test_len(len)
    idx_rx = 1
    conf = $ts.dut.call("lan9662_rte_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "LAN9662_RTP_TYPE_PN"
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
    $ts.dut.call("lan9662_rte_ib_rtp_conf_set", $rtp_id, conf)
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

test "tx-data" do
    tx_test_len(60)
    tx_test_len(1514)
end

def tx_test_time(idx, time, margin)
    conf = $ts.dut.call("lan9662_rte_ib_rtp_conf_get", $rtp_id)
    conf["type"] = "LAN9662_RTP_TYPE_PN"
    conf["time"] = time
    conf["port"] = $port[idx]
    len = 60
    conf["length"] = len
    for i in 0..(len - 1) do
        conf["data"][i] = 0
    end
    $ts.dut.call("lan9662_rte_ib_rtp_conf_set", $rtp_id, conf)
    $rtp_id = ($rtp_id + 1)

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
end

test "tx-interval" do
    # 10 msec
    tx_test_time(1, 10000000, 20)
    # 10 usec
    tx_test_time(2, 10000, 2)
end

test "dump" do
    #$ts.dut.run("lan9662-rte-cmd debug api ib")
end
