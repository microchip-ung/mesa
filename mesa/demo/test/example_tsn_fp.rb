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

$idx_iport = 0
$idx_eport = 1
$tport = $ts.dut.looped_port_list[0]
$rport = $ts.dut.looped_port_list[1]

test "init" do
    # Allow jumbo frames
    $ts.dut.run("mesa-cmd port max 10240")
    port_list = [$tport, $rport]
    port_list.each do |port|
        $ts.dut.run("mesa-cmd port mode #{port + 1} 1000fdx")
    end

    # Wait for loop ports to go down and come up again
    sleep(1)
    if (!dut_port_state_up(port_list))
        t_e("loop ports are not up")
    end

    # Setup frame preemption
    $ts.dut.run("mesa-cmd example init fp iport #{$ts.dut.p[$idx_iport]} eport #{$ts.dut.p[$idx_eport]} tport #{$tport} rport #{$rport}")

    # Wait for Tx Verify
    ts = Time.now.to_i
    port = $tport
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

test "frame-test" do
    len_uc = 3000
    len_bc = 64
    for i in 0..9 do
        cmd = "sudo ef "
        cmd += "name f1 eth dmac 00:00:00:00:00:10 et 0xaaaa data pattern cnt #{len_uc - 18} "
        cmd += "name f2 eth et 0xaaaa data pattern cnt #{len_bc - 18} "
        cmd += "tx #{$ts.pc.p[$idx_iport]} name f1 "
        cmd += "tx #{$ts.pc.p[$idx_iport]} name f2 "
        cmd += "rx #{$ts.pc.p[$idx_eport]} name f1 "
        cmd += "rx #{$ts.pc.p[$idx_eport]} name f2 "
        $ts.pc.run(cmd)
        sleep(1)
    end
    $ts.dut.run("mesa-cmd example run fp");
end

test "uninit" do
    $ts.dut.run("mesa-cmd example uninit")
end
