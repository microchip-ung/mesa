#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

test "chip_id" do
    break
    t_i("Read chip ID")
    id = $ts.dut.call("mesa_chip_id_get")
    part_no = id["part_number"]
    rev = id["revision"]
    t_i("part_no: 0x#{part_no.to_s(16)}, revision: #{rev}")
end

test "forward" do
    break
    t_i("Forward one frame from each port to all other ports")
    idx_list = []
    $ts.dut.p.each_index do |idx|
        idx_list << idx
    end
    $ts.dut.p.each_index do |idx|
        port = $ts.dut.p[idx]
        t_i("Tx idx: #{idx}, #{$ts.pc.p[idx]} -> port #{port}")
        run_ef_tx_rx_cmd($ts, idx, idx_list - [idx], "eth smac #{port + 1}")
    end
    $ts.dut.run("mesa-cmd mac dump")
    $ts.dut.run("mesa-cmd port stati pa")
end

test "forward-length" do
    break
    t_i("Forward frames of different sizes from port index 1 to 0")
    [64, 128, 256].each do |len|
        t_i("Tx #{len} bytes, port #{$ts.dut.p[1]} -> #{$ts.dut.p[0]}")
        $ts.pc.run("sudo ef name f1 eth et 0xaaaa data pattern cnt #{len - 18} tx #{$ts.pc.p[1]} name f1 rx #{$ts.pc.p[0]} name f1")
    end
    $ts.dut.run("mesa-cmd port stati pa")
end

test "forward-loop" do
    break
    loop_pair_check
    t_i("Forward frames via loop ports and change mode")
    p0 = $ts.dut.p[0]
    p1 = $ts.dut.p[1]
    lp0 = $ts.dut.looped_port_list[0]
    lp1 = $ts.dut.looped_port_list[1]

    vid = 2
    $ts.dut.call("mesa_vlan_port_members_set", vid, "#{p0},#{p1},#{lp0},#{lp1}")
    [p0,p1,lp0,lp1].each do |port|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["pvid"] = vid
        conf["untagged_vid"] = vid
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end
    $ts.dut.call("mesa_pvlan_port_members_set", 0, "#{p0},#{lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 1, "#{p1},#{lp1}")

    cnt = 10000000
    cmd = "ef name f1 eth smac 1 name f2 eth smac 2"
    cmd += " tx #{$ts.pc.p[0]} rep #{cnt} name f1"
    cmd += " tx #{$ts.pc.p[1]} rep #{cnt} name f2"
    $ts.pc.bg("ef", cmd)

    10.times do |i|
        t_i("--- Iteration #{i} ---")
        sleep(1)
        mode = (i.odd? ? "auto" : "100fdx")
        $ts.dut.run("mesa-cmd port mode #{lp0 + 1} #{mode}")
        sleep(5)
        $ts.dut.run("mesa-cmd port stati packets")
    end
end

test "forward-loop-2.5G" do
    break
    loop_pair_check
    idx_tx = 0
    idx_rx = 1
    p0 = $ts.dut.p[idx_tx]
    p1 = $ts.dut.p[idx_rx]
    lp0 = $ts.dut.looped_port_list[0]
    lp1 = $ts.dut.looped_port_list[1]

    # Loop ports are 2.5G
    [lp0, lp1].each do |port|
        $ts.dut.run("mesa-cmd port mode #{port + 1} 2500")
    end

    # Port-to-port forwarding via loop ports
    $ts.dut.call("mesa_vlan_port_members_set", 1, "#{p1},#{lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 0, "#{p0},#{lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 1, "#{p1},#{lp1}")

    # Forwarding via loop ports
    cmd = "sudo ef name f1 eth "
    cmd += "tx #{$ts.pc.p[idx_tx]} name f1 "
    cmd += "rx #{$ts.pc.p[idx_rx]} name f1 "
    $ts.pc.run(cmd)
    $ts.dut.run("mesa-cmd port mode")
    $ts.dut.run("mesa-cmd port stati pa")
end

test "forward-loop-aqr" do
    break
    idx_tx = 0
    idx_rx = 1
    p0 = $ts.dut.p[idx_tx]
    p1 = $ts.dut.p[idx_rx]

    # Hard-coded loop ports
    lp0 = 48
    lp1 = 49
    #$ts.dut.run("mesa-cmd port adv #{lp0 + 1} 10g dis")
    sleep(3)
    dut_port_state_up([lp0, lp1])

    # Port-to-port forwarding via loop ports
    $ts.dut.call("mesa_vlan_port_members_set", 1, "#{p1},#{lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 0, "#{p0},#{lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 1, "#{p1},#{lp1}")

    # Forwarding via loop ports
    cmd = "sudo ef name f1 eth "
    cmd += "tx #{$ts.pc.p[idx_tx]} name f1 "
    cmd += "rx #{$ts.pc.p[idx_rx]} name f1 "
    $ts.pc.run(cmd)
    $ts.dut.run("mesa-cmd port mode")
    $ts.dut.run("mesa-cmd port stati pa")
end

test "led-control" do
    break
    $ts.dut.p.each_with_index do |port, i|
        mode = (i == 0 ? "100fdx" : i == 1 ? "100hdx" : i == 2 ? "10fdx" : "10hdx")
        $ts.dut.run("mesa-cmd port mode #{port + 1} #{mode}")
    end
    sleep(5)
    $ts.dut.run("mesa-cmd debug phy cls read 1,8 5 0")
    $ts.dut.run("mesa-cmd debug phy cls read 1,8 5 1")
    $ts.dut.run("mesa-cmd debug phy cls read 1,8 4 32")
    $ts.dut.run("mesa-cmd debug phy cls read 1,8 4 33")
    $ts.dut.run("mesa-cmd port mode")
end

test "timestamp" do
    break
    idx_tx = 0
    idx_rx = 1

    # Send learn frame to ensure forwarding to a single port
    mac = 10
    $ts.pc.run("sudo ef tx #{$ts.pc.p[idx_rx]} eth smac #{mac}")

    a = []
    10.times do
        # Send two frames and capture Rx/Tx timestamps
        cmd = "sudo ef name f0 eth dmac #{mac} "
        2.times do
            cmd += "tx #{$ts.pc.p[idx_tx]} name f0 "
        end
        idx_list = [idx_tx, idx_rx]
        idx_list.each do |idx|
            cmd += "-c #{$ts.pc.p[idx]},1,adapter_unsynced,,2 "
        end
        $ts.pc.run(cmd)

        # Calculate timestamp difference between the two frames on Tx and Rx port
        t = []
        ok = true
        idx_list.each do |idx|
            p = $ts.pc.get_pcap("#{$ts.pc.p[idx]}.pcap")
            if (p.size == 2)
                t[idx] = (p[1][:us] - p[0][:us])
            else
                ok = false
            end
        end
        if (ok)
            a << t
        end
        sleep(1)
    end

    a.each_with_index do |t, i|
        tx = t[idx_tx]
        rx = t[idx_rx]
        t_i("Index #{i}: tx: #{tx}, rx: #{rx}, tx - rx: #{tx - rx}")
    end
end

test "acl-port-counter" do
    break
    idx = 0
    port = $ts.dut.p[idx]
    conf = $ts.dut.call("mesa_acl_port_conf_get", port)
    conf["action"]["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
    $ts.dut.call("mesa_acl_port_conf_set", port, conf)
    m = {
        vid_mac: { vid: 1, mac: { addr: [255,255,255,255,255,255] } },
        destination: "#{$ts.dut.p[1]}",
        copy_to_cpu: true,
        copy_to_cpu_smac: false,
        locked: true,
        index_table: false,
        aged: false,
        cpu_queue: 0,
    }
    $ts.dut.call("mesa_mac_table_add", m)
    run_ef_tx_rx_cmd($ts, idx, [], "eth")
    $ts.dut.run("mesa-cmd port stati pa")
    cnt = $ts.dut.call("mesa_port_counters_get", port)["bridge"]["dot1dTpPortInDiscards"]
    check_counter("Filtered", cnt, 1)
end

test "fwd-drop-count" do
    break
    # If a frame is dropped for one egress port, the ingress port drop counter increments
    idx = 0
    $ts.dut.run("mesa-cmd port flow control disable")
    $ts.dut.run("mesa-cmd port adv #{$ts.dut.p[1] + 1} 1000 dis")
    sleep(5)
    $ts.pc.run("ef name f1 eth tx #{$ts.pc.p[idx]} rep 1000000 name f1")
    $ts.dut.run("mesa-cmd port stati pac")
    $ts.dut.run("mesa-cmd port stati #{$ts.dut.p[idx] + 1}")
end

test "acl-cpu-queue" do
    break
    idx_tx = 0
    idx_rx = 1
    queue = 6
    port = $ts.dut.p[idx_tx]
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ETYPE")
    ace["id"] = 1
    ace["port_list"] = "#{port}"
    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
    action["cpu"] = true
    action["cpu_queue"] = queue
    action["ptp_action"] = "MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2"
    $ts.dut.call("mesa_ace_add", 0, ace)
    $ts.dut.run("mesa-cmd packet forward #{queue} #{$ts.dut.p[idx_rx] + 1}")
    run_ef_tx_rx_cmd($ts, idx_tx, [idx_rx], "eth")
end

test "dlb-policer" do
    break
    idx = 0

    # Ingress counters
    istat = $ts.dut.call("mesa_ingress_cnt_alloc", 1)

    # DLB policer
    pol = $ts.dut.call("mesa_dlb_policer_alloc", 1)
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, 0)
    conf["enable"] = true
    conf["cir"] = 100  # Current minimum rate in DLB API
    conf["cbs"] = 1024 # Room for one frame
    $ts.dut.call("mesa_dlb_policer_conf_set", pol, 0, conf)

    # Ingress flow
    iflow = $ts.dut.call("mesa_iflow_alloc")
    conf = $ts.dut.call("mesa_iflow_conf_get", iflow)
    conf["cnt_enable"] = true
    conf["cnt_id"] = istat
    conf["dlb_enable"] = true
    conf["dlb_id"] = pol
    $ts.dut.call("mesa_iflow_conf_set", iflow, conf)

    # VCE
    port = $ts.dut.p[idx]
    vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
    vce["id"] = 1
    vce["key"]["port_list"] = "#{port}"
    action = vce["action"]
    action["flow_id"] = iflow
    $ts.dut.call("mesa_vce_add", 0, vce)

    # Frame Tx
    len = 1024
    $ts.pc.run("sudo ef name f1 eth et 0xaaaa data pattern cnt #{len - 18} tx #{$ts.pc.p[idx]} rep 10 name f1")
    $ts.dut.run("mesa-cmd port stati pac")
end

test "acl-etype-counter" do
    break
    idx = 0
    port = $ts.dut.p[idx]
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ETYPE")
    ace["id"] = 1
    ace["port_list"] = "#{port}"
    etype = ace["frame"]["etype"]["etype"]
    etype["value"] = [0x89,0x02]
    etype["mask"] = [0xff,0xff]
    $ts.dut.call("mesa_ace_add", 0, ace)
    run_ef_tx_rx_cmd($ts, idx, [1,2,3], "eth et 0x8902")
    cnt = $ts.dut.call("mesa_ace_counter_get", ace["id"])
    check_counter("ace", cnt, 1)
end

test "acl-frame-policer" do
    break
    idx = 0
    pol = 0
    port = $ts.dut.p[idx]
    conf = $ts.dut.call("mesa_acl_port_conf_get", port)
    action = conf["action"]
    action["police"] = true
    action["policer_no"] = pol
    $ts.dut.call("mesa_acl_port_conf_set", port, conf)
    conf = $ts.dut.call("mesa_acl_policer_conf_get", pol)
    conf["rate"] = 30
    $ts.dut.call("mesa_acl_policer_conf_set", pol, conf)
    $ts.pc.run("ef name f1 eth tx #{$ts.pc.p[idx]} rep 100 name f1")
    $ts.dut.run("mesa-cmd port stati pac")
end
