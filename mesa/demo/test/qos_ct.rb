#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if cut-through supported
cap_check_exit("QOS_EGRESS_QUEUE_CUT_THROUGH")
$is_fireant = (cap_get("PACKET_IFH_EPID") == 11)

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

# This test requires cut-through decision per egress port.
test "ct-port" do
    if ($is_fireant == false)
        break
    end
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

# This test can be used regardless if cut-through decision is common for all ports
test "ct-common" do
    if ($is_fireant)
        break
    end
    idx_tx = 0
    idx_rx = 1

    # Ensure forwarding to Rx port only
    $ts.dut.call("mesa_vlan_port_members_set", 1, "#{$ts.dut.p[idx_rx]}");

    # Enable cut-through on egress port for priority 7
    port = $ts.dut.p[idx_rx]
    conf = $ts.dut.call("mesa_qos_port_conf_get", port)
    conf["queue"][7]["cut_through_enable"] = true
    $ts.dut.call("mesa_qos_port_conf_set", port, conf)

    # Enable PCP classification on ingress port
    port = $ts.dut.p[idx_tx]
    conf = $ts.dut.call("mesa_qos_port_conf_get", port)
    conf["tag"]["class_enable"] = true
    $ts.dut.call("mesa_qos_port_conf_set", port, conf)

    # Send f1 (PCP = 7) and F2 (PCP = 0) and capture Rx/Tx timestamps
    idx_list = [idx_tx, idx_rx]
    cmd = "sudo ef "
    for i in 1..2 do
        pcp = (i == 1 ? 7 : 0)
        cmd += ("name f#{i} eth" + cmd_tag_push({tpid: 0x8100, pcp: pcp}) + " data pattern cnt 1496 ")
        cmd += "tx #{$ts.pc.p[idx_tx]} name f#{i} "
    end
    idx_list.each do |idx|
        cmd += "-c #{$ts.pc.p[idx]},2,adapter_unsynced,,2 "
    end
    $ts.pc.run(cmd)

    t = []
    idx_list.each do |idx|
        p = $ts.pc.get_pcap("#{$ts.pc.p[idx]}.pcap")
        t[idx] = (p[1][:us] - p[0][:us])
    end
    t_i("t: #{t}")

    # The latency difference is apprimately 10 usec, but the clocks of the ports
    # of the test PC may have drifted a couple of microseconds between the frames
    check_diff(t[idx_rx] - t[idx_tx], 6, 14)
end
