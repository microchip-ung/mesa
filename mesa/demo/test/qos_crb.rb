#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Frame test --------------------------------------------------------

check_capabilities do
    $cap_dlb_shaper = ($ts.dut.call("mesa_capability", "MESA_CAP_QOS_EGRESS_QUEUE_SHAPERS_CRB") != 0)
    assert(($cap_dlb_shaper == true), "Credit based shaping it not supported")
end

def shaper_test(idx_tx, idx_rx, prio, rate, level, credit_enable)
    # Setup shaper
    port = $ts.dut.p[idx_rx]
    conf = $ts.dut.call("mesa_qos_port_conf_get", port)
    shaper = conf["queue"][prio]["shaper"]
    shaper["rate"] = (rate / 1000)
    shaper["level"] = level
    shaper["credit_enable"] = credit_enable
    $ts.dut.call("mesa_qos_port_conf_set", port, conf)
    t_i("shaping at #{rate/1000} Mbps, credit_enable: #{credit_enable}")

    # Frame test using relative timestamps
    len = (10000/8) # 10000 bits per frame
    tx_cnt = 10
    cmd = "sudo ef -c #{$ts.pc.p[idx_rx]},1,adapter_unsynced,,#{tx_cnt} "
    cmd += "name f1 eth data pattern cnt #{len - 18} "
    cmd += "tx #{$ts.pc.p[idx_tx]} rep 10 name f1 "
    $ts.pc.run(cmd)
    pkts = $ts.pc.get_pcap("#{$ts.pc.p[idx_rx]}.pcap")
    if (pkts.size == 0)
        t_e("No packets logged");
    else
        t0 = 0
        t0_valid = false
        size = 0
        pkts.each do |p|
            t = p[:us_rel]
            if (t0_valid)
                diff = (t - t0)
                # Expect line rate or shaper rate
                exp_rate = (((size > level) or credit_enable) ? rate : 1000000000)
                exp = (len*8*1000000/exp_rate) # Expected diff in usec
                txt = "t: #{t}, diff: #{diff}, exp: #{exp}"
                if (diff < exp/2)
                    t_e(txt)
                else
                    t_i(txt)
                end
            else
                t_i("t: #{t}")
            end
            t0_valid = true
            t0 = t
            size = (size + len)
        end
    end
end

test "frame-io" do
    idx_tx = 0
    idx_rx = 1
    prio = 3
    rate = 1000000
    level = 4096

    # Setup default priority for ingress port
    port = $ts.dut.p[idx_tx]
    conf = $ts.dut.call("mesa_qos_port_conf_get", port)
    conf["default_prio"] = prio
    $ts.dut.call("mesa_qos_port_conf_set", port, conf)

    # Shaping at 1Mbps, CRB disabled
    shaper_test(idx_tx, idx_rx, prio, rate, level, false)

    # Shaping at 1Mbps, CRB enabled
    shaper_test(idx_tx, idx_rx, prio, rate, level, true)
end
