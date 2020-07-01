#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'oam_lib'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_oam_v1 = ($ts.dut.call("mesa_capability", "MESA_CAP_VOP_V1") != 0) ? true : false
    $cap_oam_v2 = ($ts.dut.call("mesa_capability", "MESA_CAP_VOP_V2") != 0) ? true : false
    assert(($cap_oam_v1 == true) || ($cap_oam_v2 == true), "VOP must be V1 or V2,  (cap_oam_v1=#{$cap_oam_v1} $cap_oam_v2=#{$cap_oam_v1})")
    $cap_ccm_defects = $ts.dut.call("mesa_capability", "MESA_CAP_VOP_CCM_DEFECT")
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
end

MESA_VID_NULL = 0

fp = rand(3)    # Get a random ingress port between 0 and 3
begin   # Get a random egress port between 0 and 3 different from egress port
    bp = rand(3)
end while fp == bp

t_i("---------fp: #{fp}  bp: #{bp}---------")

$port0 = fp
$port1 = bp
$megid = ['M'.ord,'i'.ord,'c'.ord,'r'.ord,'o'.ord,'c'.ord,'h'.ord,'i'.ord,'p'.ord,' '.ord,'M'.ord,'E'.ord,'G'.ord]
$level = 4
$period = "MESA_VOE_CCM_PERIOD_1_SEC"
$vid = 10


def frame_rx(frame, port)
    pid_ef = []
    pid_ef << $ts.pc.bg("ef rx", "sudo ef -t 2000 rx #{$ts.pc.p[port]} #{frame}")
    sleep 1
end

def voe_test(tag_vid = 0)
    test "voe_test #{tag_vid}" do
    t_i("Assure that LOC is detected")
    sleep(4)
    $ts.dut.run("mesa-cmd example run vop command 0 exp_loc 1")

    t_i("Create frame")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)

    test "Check Continuity Check" do
    t_i("Transmit valid CCM frame in front of VOE to clear LOC")
    frametx = frame.dup
    frametx += ccm_pdu_create($level, $period, 0, 1, $megid)
    frame_tx(frametx, $port0, "", "", " ", " ")

    t_i("After transmitting CCM. Check LOC event and status")
    $ts.dut.run("mesa-cmd example run vop command 0 exp-seen-ccm 1 exp-state-loc 0")
    $ts.dut.run("mesa-cmd example run vop command 1 exp-event-loc 1")

    sleep(4)

    t_i("After sleep. Check LOC event and status")
    $ts.dut.run("mesa-cmd example run vop command 0 exp-state-loc 1")
    $ts.dut.run("mesa-cmd example run vop command 1 exp-event-loc 1")
    end

    test "Check Level filtering" do
    t_i("Transmit valid CCM frame in front of VOE with lower level. Check that frame is level filtered.")
    frametx = frame.dup
    frametx += ccm_pdu_create($level-1, "MESA_VOE_CCM_PERIOD_1_SEC", 0, 1, $megid)
    frame_tx(frametx, $port0, "", "", " ", " ")

    if ($cap_oam_v2)    # V1 does not support CCM level check status
        t_i("After transmitting CCM. Check Level status.")
        $ts.dut.run("mesa-cmd example run vop command 0 exp-state-level 1")
    
        if ($cap_ccm_defects == 1)  # Check if defects are supported
            sleep(4)
            t_i("After sleep. Check Level status")
            $ts.dut.run("mesa-cmd example run vop command 0 exp-state-level 0")
        else
            frametx = frame.dup + ccm_pdu_create($level, "MESA_VOE_CCM_PERIOD_1_SEC", 0, 1, $megid)
            frame_tx(frametx, $port0, "", "", " ", " ")
            t_i("After transmitting CCM. Check Level status.")
            $ts.dut.run("mesa-cmd example run vop command 0 exp-state-level 0")
        end
    end

    t_i("Transmit valid CCM frame behind VOE with lower level. Check that frame is level filtered.")
    frame_tx(frametx, $port1, "", "", " ", " ")

    t_i("Transmit valid CCM frame behind VOE with higher level. Check that frame is NOT level filtered.")
    frametx = frame.dup
    frametx += ccm_pdu_create($level+1, "MESA_VOE_CCM_PERIOD_1_SEC", 0, 1, $megid)
    frame_tx(frametx, $port1, frametx, "", " ", " ")

    t_i("Transmit valid CCM frame in front of VOE with higher level. Check that frame is NOT level filtered.")
    frame_tx(frametx, $port0, "", frametx, " ", " ")
    end

    test "Check Loop Back" do
    frameuctx = frame_create(UC_STRING, SC_STRING, tag_vid)
    frameucrx = frame_create(SC_STRING, UC_STRING, tag_vid)

    t_i("Transmit valid LBM frame in front of VOE")
    frametx = frameuctx.dup + lb_pdu_create($level, 3, 5)
    framerx = frameucrx.dup + lb_pdu_create($level, 2, 5)
    frame_tx(frametx, $port0, framerx, "", " ", " ")
    end

    test "Check Link Trace" do
    t_i("Transmit valid LTM frame in front of VOE")
    frametx = frame.dup + lt_pdu_create($level, 5, 0)
    frame_tx(frametx, $port0, " ", " ", " ", " ")

    t_i("Check the LTM status.")
    $ts.dut.run("mesa-cmd example run command 2 exp-seen-ltm 1")

    t_i("Check the CPU received frame.")
    $ts.dut.run("mesa-cmd example run command 4 exp-oam-opcode 5")
    end

    test "Check Linear APS" do
    t_i("Transmit valid LAPS frame in front of VOE")
    frametx = frame.dup + laps_pdu_create($level, REQUEST_MANUEL_SWITCH)
    frame_tx(frametx, $port0, " ", " ", " ", " ")

    t_i("Check the APS status.")
    $ts.dut.run("mesa-cmd example run command 3 exp-seen-laps 1")

    t_i("Check the CPU received frame.")
    $ts.dut.run("mesa-cmd example run command 4 exp-oam-opcode 39")
    end

    test "Check CCM PDU injection" do
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    ccm_pdu = ccm_pdu_create($level, $period, $cap_oam_v2 ? 0 : 1, 2, $megid)
    
    t_i("Inject and expect valid CCM frame from the VOE")
    framerx = frame.dup + ccm_pdu
    frame_rx(framerx, $port0)
    $ts.dut.run("mesa-cmd example run command 5")
    sleep 1
    $ts.pc.run("ef rx #{$ts.pc.p[$port0]}") # This is required in order to make the previously started back ground print result. Dont know why !!

    t_i("Increment sequence number")
    ccm_pdu = ccm_pdu_create($level, $period, $cap_oam_v2 ? 1 : 2, 2, $megid)

    t_i("Inject and expect valid CCM frame from the VOE")
    framerx = frame.dup + ccm_pdu
    frame_rx(framerx, $port0)
    $ts.dut.run("mesa-cmd example run command 5")
    sleep 1
    $ts.pc.run("ef rx #{$ts.pc.p[$port0]}") # This is required in order to make the previously started back ground print result. Dont know why !!
    end

    test "Check LBM PDU injection" do
    $ts.dut.run("mesa-cmd example run command 0")

    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    lbm_pdu = lb_pdu_create($level, 3, 1)

    t_i("Inject and expect valid CCM frame from the VOE")
    framerx = frame.dup + lbm_pdu
    frame_rx(framerx, $port0)
    $ts.dut.run("mesa-cmd example run command 6")
    sleep 1
    $ts.pc.run("ef rx #{$ts.pc.p[$port0]}") # This is required in order to make the previously started back ground print result. Dont know why !!

    t_i("Increment sequence number")
    lbm_pdu = lb_pdu_create($level, 3, 2)

    t_i("Inject and expect valid LBM frame from the VOE")
    framerx = frame.dup + lbm_pdu
    frame_rx(framerx, $port0)
    $ts.dut.run("mesa-cmd example run command 6")
    sleep 1
    $ts.pc.run("ef rx #{$ts.pc.p[$port0]}") # This is required in order to make the previously started back ground print result. Dont know why !!

    $ts.dut.run("mesa-cmd example run command 0")
    end
    end
end

test "test_conf" do
    t_i("Configure the test to Port MEP by calling the example code command")
    $ts.dut.run("mesa-cmd example init vop front-port #{$ts.dut.p[fp]+1} back-port #{$ts.dut.p[bp]+1} level #{$level} vid 0")
end

test "test_run" do
    t_i("Port VOE test")
    voe_test(0)
exit 0
    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")

    t_i("VLAN VOE test")
    $ts.dut.run("mesa-cmd example init vop front-port #{$ts.dut.p[fp]+1} back-port #{$ts.dut.p[bp]+1} level #{$level} vid #{$vid}")
    voe_test($vid)
end

test "test_clean_up" do
    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")
end
