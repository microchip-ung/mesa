#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'oam_lib'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_mrp = ($ts.dut.call("mesa_capability", "MESA_CAP_MRP") != 0) ? true : false
    assert(($cap_mrp == true), "MRP capability must be defined,  (cap_mrp=#{$cap_mrp})")

    $cap_mrp_cnt = ($ts.dut.call("mesa_capability", "MESA_CAP_MRP_CNT") != 0) ? true : false
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
end

# Uncomment this if you want trace in the output
# $ts.dut.run("mesa-cmd deb trace api_cil mrp debug")

$p_port = 0
$s_port = 1
$i_port = 2
$port0 = $p_port
$port1 = $s_port
$port2 = $i_port
$npi_port = 3

UC_NUMBER_O = 0x000000000507

def frame_rx(frame, port)
    pid_ef = []
    pid_ef << $ts.pc.bg("ef rx", "sudo ef -t 2000 rx #{$ts.pc.p[port]} #{frame}")
    sleep 1
end

def mrp_test(tag_vid = 0)
    lan966x = ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) ? true : false

    test "mrp_test #{tag_vid}" do

    test("Assure that Test LOC is detected and no events") do
    sleep(4)
    $ts.dut.run("mesa-cmd example run mrp command 0 exp-state-p-loc 1 exp-state-s-loc 1 exp-state-i-iloc 0")
    $ts.dut.run("mesa-cmd example run mrp command 1 exp_event_loc_p 0 exp_event_loc_s 0")
    end

    t_i("Create MC_Test frame")
    frame = frame_create(MC_TEST, SC_STRING, 0, 0, "mrp")
    frametx = frame.dup + "mrp_tst t_sa #{UC_NUMBER_O} c_seq_num 1 "

    test "Transmit TST frame on ring ports to see no forwarding and clear of LOC" do
    frame_tx(frametx, $p_port, "", "", "", "")
    frame_tx(frametx, $s_port, "", "", "", "")
    $ts.dut.run("mesa-cmd example run mrp command 0 exp-state-p-loc 0 exp-seen-p-mrp 1 exp-count-p-tst 1\
                                                    exp-state-s-loc 0 exp-seen-s-mrp 1 exp-count-s-tst 1")
    $ts.dut.run("mesa-cmd example run mrp command 1 exp_event_loc_p 1 exp_event_loc_s 1")
    end

    test("Assure that Test LOC is detected") do
    sleep(4)
    $ts.dut.run("mesa-cmd example run mrp command 0 exp-state-p-loc 1 exp-state-s-loc 1")
    $ts.dut.run("mesa-cmd example run mrp command 1 exp_event_loc_p 1 exp_event_loc_s 1")
    end

    test "Inject a Test frame from the MRP and check incrementing sequence number" do
    framerx = frame.dup + "ign c_seq_num 0"
    frame_rx(framerx, $p_port)
    $ts.dut.run("mesa-cmd example run mrp command 3")
    sleep 1
    $ts.pc.run("ef rx #{$ts.pc.p[$p_port]}") # This is required in order to make the previously started back ground print result. Dont know why !!

    framerx = frame.dup + "ign c_seq_num 1"
    frame_rx(framerx, $p_port)
    $ts.dut.run("mesa-cmd example run mrp command 3")
    sleep 1
    $ts.pc.run("ef rx #{$ts.pc.p[$p_port]}") # This is required in order to make the previously started back ground print result. Dont know why !!
    end

    test "Inject a Test frame from the MRP and check ring state and transaction counter" do
    framerx = frame.dup + "ign t_state 1 t_trans 1"
    frame_rx(framerx, $p_port)
    $ts.dut.run("mesa-cmd example run mrp command 3")
    sleep 1
    $ts.pc.run("ef rx #{$ts.pc.p[$p_port]}") # This is required in order to make the previously started back ground print result. Dont know why !!
    end

    t_i("Create MC_Control frame")
    frame = frame_create(MC_CONTROL, SC_STRING, 0, 0, "mrp")

    test "Transmit LinkChange LinkDown frame on ring port to see copy to CPU and no forwarding" do
    frametx = frame.dup + "mrp_lnk "
    frame_tx(frametx, $p_port, "", "", "", "")
    $ts.dut.run("mesa-cmd example run mrp command 2 exp-mrp-type 4")
    frame_tx(frametx, $s_port, "", "", "", "")
    $ts.dut.run("mesa-cmd example run mrp command 2 exp-mrp-type 4")
    end

    t_i("Create MC_IControl frame")
    frame = frame_create(MC_ICONTROL, SC_STRING, 0, 0, "mrp")

    test "Transmit InTopologyChange frame on Interconnect port to see no forwarding, but copy to CPU" do
    frametx = frame.dup + "mrp_topo t_type 7 "
    frame_tx(frametx, $i_port, "", "", "", "")
    $ts.dut.run("mesa-cmd example run mrp command 2 exp-mrp-type 7")
    end

    end
end

test "test_conf" do
    $ts.dut.run("mesa-cmd example help mrp")
    t_i("Configure the test to Port MEP by calling the example code command")
    $ts.dut.run("mesa-cmd example init mrp p-port #{$ts.dut.p[$p_port]+1} s-port #{$ts.dut.p[$s_port]+1} i-port #{$ts.dut.p[$i_port]+1}")
end

test "test_run" do
    mrp_test(0)
end

test "test_clean_up" do
    # In case the test fails, it's nice to have the output of
    # 'deb api [cil] mrp'
    $ts.dut.run("mesa-cmd deb api mrp")

    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")
end
