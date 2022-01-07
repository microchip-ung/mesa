#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $tas_support = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_TAS")
    assert(($tas_support == 1),
           "TAS not supported on this platform")
    $pol_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_PORT_POLICER_CNT")
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
end

MESA_VID_NULL = 0

eg = rand(3)    # Get a random egress port between 0 and 3
begin   # Get a random ingress port between 0 and 3 different from egress port
    ig = rand(3)
end while eg == ig
ig = [ig]
t_i("---------ig: #{ig}  eg: #{eg}---------")

test "test_conf" do
    t_i("Configure the test by calling the example code command")
    $cycle_frames = 3000
    $frame_size = 500
    $ts.dut.run("mesa-cmd example init tas ing-port #{$ts.dut.p[ig[0]]+1} eg-port #{$ts.dut.p[eg]+1} cycle #{$cycle_frames} size #{$frame_size}")

    $pconf_save = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig[0]], $pol_cnt)
end

test "test_run" do
    frame_tx_time_nano = ($frame_size+20)*8    # One bit takes one nano sec to transmit at 1G
    $cycle_time = $cycle_frames * frame_tx_time_nano

    t_i("Priority 0 test")
    erate = (1000000000 * 10) / 100  #Priority 0 is 10%

    if ($cap_family != chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) && ($cap_family != chip_family_to_id("MESA_CHIP_FAMILY_LAN969X"))   # For some reason the current FPGA cannot parse this test with any policing.
                                                                        # Strange thing is that it does not result in aging
        t_i("Setup ingress port policer to avoid queue aging")
        pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig[0]], $pol_cnt)
        pconf[0]["frame_rate"] = false
        pconf[0]["policer"]["level"] = 1
        pconf[0]["policer"]["rate"] = erate/999
        pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig[0]], $pol_cnt, pconf)
    end

   #measure(ig, eg, size,          sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, $frame_size,   2,     false,            false,           [erate],             [2],            true,              [0],     [$cycle_time])

    t_i("Priority 4 test")
    erate = (1000000000 * 30) / 100  #Priority 4 is 30%

    if ($cap_family != chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) && ($cap_family != chip_family_to_id("MESA_CHIP_FAMILY_LAN969X"))   # For some reason the current FPGA cannot parse this test with any policing.
        t_i("Setup ingress port policer to avoid queue aging")
        pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig[0]], $pol_cnt)
        pconf[0]["frame_rate"] = false
        pconf[0]["policer"]["level"] = 1
        pconf[0]["policer"]["rate"] = erate/999
        pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig[0]], $pol_cnt, pconf)
    end

   #measure(ig, eg, size,          sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, $frame_size,   2,     false,            false,           [erate],             [1],            true,              [4],     [$cycle_time])

    t_i("Priority 7 test")
    erate = (1000000000 * 60) / 100  #Priority 7 is 60%

    if ($cap_family != chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) && ($cap_family != chip_family_to_id("MESA_CHIP_FAMILY_LAN969X"))   # For some reason the current FPGA cannot parse this test with any policing.
        t_i("Setup ingress port policer to avoid queue aging")
        pconf = $ts.dut.call("mesa_qos_port_policer_conf_get", $ts.dut.p[ig[0]], $pol_cnt)
        pconf[0]["frame_rate"] = false
        pconf[0]["policer"]["level"] = 1
        pconf[0]["policer"]["rate"] = erate/999
        pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig[0]], $pol_cnt, pconf)
    end

   #measure(ig, eg, size,          sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, $frame_size,   2,     false,            false,           [erate],             [1],            true,              [7],     [$cycle_time])

    t_i("Priority 1 test")
   #measure(ig, eg, size,          sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, $frame_size,   2,     false,            false,           [0],                 [0],            true,              [1],     [0])
end

test "test_clean_up" do
    pconf = $ts.dut.call("mesa_qos_port_policer_conf_set", $ts.dut.p[ig[0]], $pol_cnt, $pconf_save)

    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")

    t_i("Check that TAS not active")
    erate = 1000000000
   #measure(ig, eg, size,          sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, $frame_size,   2,     false,            false,           [erate],             [1],            true,              [0])
end
