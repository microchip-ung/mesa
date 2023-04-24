#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0
$idx_rx = 1
$idx_no = 2

test "conf" do
    t_i("IGMP registration")
    queue = 7
    conf = $ts.dut.call("mesa_packet_rx_conf_get")
    conf["queue"][queue]["rate"] = 10
    conf["reg"]["bpdu_cpu_only"] = true
    conf["map"]["bpdu_queue"] = queue
    $ts.dut.call("mesa_packet_rx_conf_set", conf)

    port = $ts.dut.p[$idx_rx]
    $ts.dut.run("mesa-cmd packet forward #{queue} #{port + 1}")
end

#---------- Frame testing -----------------------------------------------------

test "frame-xtr-inj" do
    [64, 1518].each do |len|
        cmd = "sudo ef -t 1000 "
        cmd += "name f1 eth dmac 01:80:c2:00:00:00 data pattern cnt #{len - 18} "
        cmd += "tx #{$ts.pc.p[$idx_tx]} name f1 "
        cmd += "rx #{$ts.pc.p[$idx_rx]} name f1 "
        cmd += "rx #{$ts.pc.p[$idx_tx]} "
        cmd += "rx #{$ts.pc.p[$idx_no]}"
        $ts.pc.run(cmd)
    end
end

test "frame-cpu-queue-shaper" do
    if (cap_get("QOS_CPU_QUEUE_SHAPER") == 0)
        break;
    end
    tx_cnt = 10
    cmd = "sudo ef -c #{$ts.pc.p[$idx_rx]},1,adapter_unsynced,,#{tx_cnt} "
    cmd += "name f1 eth dmac 01:80:c2:00:00:00 data pattern cnt 46 "
    cmd += "tx #{$ts.pc.p[$idx_tx]} rep #{tx_cnt} name f1"
    $ts.pc.run(cmd)
    pkts = $ts.pc.get_pcap("#{$ts.pc.p[$idx_rx]}.pcap")
    cnt = pkts.size
    assert(cnt == tx_cnt, "Logged #{cnt} packets, expected #{tx_cnt}")
    pkts.each do |p|
        t = p[:us_rel]
        t_i("t: #{t}")
        if (p == pkts.last)
            min = 600000
            max = 1400000
            msg = "last frame at #{t}, expected range: #{min} - #{max}"
            if (t > min and t < max)
                t_i(msg)
                else
                    t_e(msg)
            end
        end
    end
end

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api ci cou act 1")
    $ts.dut.run("mesa-cmd deb api ci pac")
end
