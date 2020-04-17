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
    conf["reg"]["igmp_cpu_only"] = true
    conf["map"]["igmp_queue"] = queue
    $ts.dut.call("mesa_packet_rx_conf_set", conf)

    port = $ts.dut.p[$idx_rx]
    $ts.dut.run("mesa-cmd packet forward #{queue} #{port + 1}")
end

#---------- Frame testing -----------------------------------------------------

test "frame-xtr-inj" do
    [64, 1518].each do |len|
        cmd = "sudo ef -t 1000 "
        cmd += "name f1 eth dmac 01:00:5e:01:02:03 ipv4 proto 2 data pattern cnt #{len - 38} "
        cmd += "tx #{$ts.pc.p[$idx_tx]} name f1 "
        cmd += "rx #{$ts.pc.p[$idx_rx]} name f1 "
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
    cmd += "name f1 eth dmac 01:00:5e:01:02:03 ipv4 proto 2 data pattern cnt 32 "
    cmd += "tx #{$ts.pc.p[$idx_tx]} rep #{tx_cnt} name f1"
    $ts.pc.run(cmd)
    pkts = $ts.pc.get_pcap("#{$ts.pc.p[$idx_rx]}.pcap")
    if (pkts.size == 0)
        t_e("No packets logged");
    else
        pkts.each do |p|
            t = p[:us_rel]
            t_i("t: #{t}")
            if (p == pkts.last)
                min = 700000
                max = 1300000
                msg = "last frame at #{t}, expected range: #{min} - #{max}"
                if (t > min and t < max)
                    t_i(msg)
                else
                    t_e(msg)
                end
            end
        end
    end
end
