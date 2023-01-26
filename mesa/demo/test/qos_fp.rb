#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x", {}, "", "loop")

# Check if Frame Preemption supported
cap_check_exit("QOS_FRAME_PREEMPTION")

# Check that two loop ports exist
loop_pair_check

#---------- Configuration -----------------------------------------------------

$idx_tx = 0
$idx_rx = 1
$lp0 = $ts.dut.looped_port_list[0]
$lp1 = $ts.dut.looped_port_list[1]

test "conf" do
    p0 = $ts.dut.p[$idx_tx]
    p1 = $ts.dut.p[$idx_rx]

    # Allow jumbo frames
    $ts.dut.run("mesa-cmd port max 10240")

    # Setup loop ports in 1Gbps, as frame preemption is not supported for high speeds
    port_list = [$lp0, $lp1]
    port_list.each do |port|
        $ts.dut.run("mesa-cmd port mode #{port + 1} 1000fdx")
    end

    # Wait for loop ports to go down and come up again
    sleep(1)
    if (!dut_port_state_up(port_list))
        t_e("loop ports are not up")
    end

    # QCE: Broadcasts are high priority
    qce = $ts.dut.call("mesa_qce_init", "MESA_QCE_TYPE_ANY")
    qce["id"] = 1
    key = qce["key"]
    key["port_list"] = "#{p0}"
    key["mac"]["dmac_bc"] = "MESA_VCAP_BIT_1"
    act = qce["action"]
    act["prio_enable"] = true
    act["prio"] = 7
    $ts.dut.call("mesa_qce_add", 0, qce)

    # Port-to-port forwarding via loop ports
    $ts.dut.call("mesa_vlan_port_members_set", 1, "#{p1},#{$lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 0, "#{p0},#{$lp0}")
    $ts.dut.call("mesa_pvlan_port_members_set", 1, "#{p1},#{$lp1}")
    
    # Enable Tx frame preemption on first loop port
    port = $lp0
    conf = $ts.dut.call("mesa_qos_fp_port_conf_get", port)
    conf["admin_status"][0] = true
    conf["enable_tx"] = true
    conf["verify_disable_tx"] = false
    $ts.dut.call("mesa_qos_fp_port_conf_set", port, conf)

    # Wait for Tx Verify
    ts = Time.now.to_i
    loop do
        s = $ts.dut.call("mesa_qos_fp_port_status_get", port)
        status = s["status_verify"]
        active = s["preemption_active"]
        txt = "port #{port} status: #{status}, active: #{active}"
        if (status == "MESA_MM_STATUS_VERIFY_SUCCEEDED" and active)
            t_i(txt)
            break
        elsif ((Time.now.to_i - ts) > 3)
            t_e(txt)
            break
        end
        sleep(1)
    end
end

def cnt_check(port, cnt, name, exp)
    val = cnt[name]
    msg = "port #{port}, #{name} = #{val}, expected #{exp}"
    if (val == exp)
        t_i(msg)
    else
        t_e(msg)
    end
end

test "frame-io" do
    cnt = 10
    len_uc = 5000
    len_bc = 64
    for i in 0..(cnt - 1) do
        cmd = "sudo ef "
        cmd += "name f1 eth dmac 00:00:00:00:00:10 et 0xaaaa data pattern cnt #{len_uc - 18} "
        cmd += "name f2 eth et 0xaaaa data pattern cnt #{len_bc - 18} "
        cmd += "tx #{$ts.pc.p[$idx_tx]} name f1 "
        cmd += "tx #{$ts.pc.p[$idx_tx]} name f2 "
        cmd += "rx #{$ts.pc.p[$idx_rx]} name f1 "
        cmd += "rx #{$ts.pc.p[$idx_rx]} name f2 "
        $ts.pc.run(cmd)
        sleep(1)
    end

    # Check counters for loop ports
    cnt_tx = 0
    [$lp0, $lp1].each do |port|
        counters = $ts.dut.call("mesa_port_counters_get", port)
        c = counters["dot3br"]
        if (port == $lp0)
            dir = "ifOut"
            cnt_tx = c["aMACMergeFragCountTx"]
            t_i("Tx fragments: #{cnt_tx}")
        else
            dir = "ifIn"
            cnt_check(port, c, "aMACMergeFrameAssErrorCount", 0)
            cnt_check(port, c, "aMACMergeFrameSmdErrorCount", 0)
            cnt_check(port, c, "aMACMergeFrameAssOkCount", cnt_tx)
            cnt_check(port, c, "aMACMergeFragCountRx", cnt_tx)
            cnt_check(port, c, "aMACMergeFragCountTx", 0)
            cnt_check(port, c, "aMACMergeHoldCount", 0)
        end
        c = counters["if_group"]
        cnt_check(port, c, dir + "Octets", cnt * (len_uc + len_bc))
        cnt_check(port, c, dir + "UcastPkts", cnt)
        cnt_check(port, c, dir + "BroadcastPkts", cnt)
    end
end
