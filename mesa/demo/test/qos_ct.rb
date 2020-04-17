#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if cut-through supported
cap_check_exit("QOS_EGRESS_QUEUE_CUT_THROUGH")

#---------- Configuration -----------------------------------------------------

def frame_test(idx_tx, idx_list)
    cmd = "sudo ef name f1 eth data pattern cnt 1500 tx #{$ts.pc.p[idx_tx]} name f1 "
    idx_list.each do |idx|
        cmd += "-c #{$ts.pc.p[idx]},1,adapter_unsynced,,1 "
        cmd += "rx #{$ts.pc.p[idx]} name f1 "
    end
    $ts.pc.run(cmd)

    t = []
    idx_list.each do |idx|
        pkts = $ts.pc.get_pcap("#{$ts.pc.p[idx]}.pcap")
        t[idx] = pkts[0][:us]
    end
    t
end

def check_diff(delta, min, max)
    txt = "diff: #{delta} usec, min: #{min}, max: #{max}"
    if (delta >= min and delta <= max)
        t_i(txt)
    else
        t_e(txt)
    end
end

test "frame-io" do
    idx_tx = 0
    idx_ct = 1
    idx_sf = 2
    idx_list = [idx_ct, idx_sf]

    # Store-and-forward on both egress ports
    t1 = frame_test(idx_tx, idx_list) 

    # Enable cut-through on egress port for priority 0
    port = $ts.dut.p[idx_ct]
    conf = $ts.dut.call("mesa_qos_port_conf_get", port)
    conf["queue"][0]["cut_through_enable"] = true
    $ts.dut.call("mesa_qos_port_conf_set", port, conf)
    
    # Cut-through on idx_ct, store-and-forward on idx_sf
    t2 = frame_test(idx_tx, idx_list)

    # Change default priority to 7 on ingress port
    port = $ts.dut.p[idx_tx]
    conf = $ts.dut.call("mesa_qos_port_conf_get", port)
    conf["default_prio"] = 7
    $ts.dut.call("mesa_qos_port_conf_set", port, conf)

    # Store-and-forward on both egress ports
    t3 = frame_test(idx_tx, idx_list)

    # Change back to default prority and disable cut-through for ingress flow
    conf["default_prio"] = 0
    $ts.dut.call("mesa_qos_port_conf_set", port, conf)
    iflow = $ts.dut.call("mesa_iflow_alloc")
    conf = $ts.dut.call("mesa_iflow_conf_get", iflow)
    conf["cut_through_disable"] = true
    $ts.dut.call("mesa_iflow_conf_set", iflow, conf)
    vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
    vce["id"] = 1
    vce["key"]["port_list"] = "#{port}"
    action = vce["action"]["flow_id"] = iflow
    $ts.dut.call("mesa_vce_add", 0, vce)

    # Store-and-forward on both egress ports
    t4 = frame_test(idx_tx, idx_list)

    t_i("t1: #{t1}")
    t_i("t2: #{t2}")
    t_i("t3: #{t3}")
    t_i("t4: #{t4}")

    # In cut-through, only the first cell is stored (about 200 bytes) 
    # Latency difference between cut-through and store-and-forward
    # at 1Gbps is approximately (1500 - 200)*8 nsec = 10 usec
    check_diff(t2[idx_sf] + t1[idx_ct] - t1[idx_sf] - t2[idx_ct], 9, 11)

    # In store-and-forward, the latency difference should be small
    check_diff(t3[idx_sf] + t1[idx_ct] - t1[idx_sf] - t3[idx_ct], -1, 1)

    # In store-and-forward, the latency difference should be small
    check_diff(t4[idx_sf] + t1[idx_ct] - t1[idx_sf] - t4[idx_ct], -1, 1)
end
