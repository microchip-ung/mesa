#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

def qos_tas_equal_interval_3_prio_1_port_test(eg, ig, it_vid = 0, ot_vid = 0, ot = false)
    test "Time aware scheduling with equal time slots test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}  OT #{ot}" do

    frame_size = 500
    frame_tx_time_nano = (frame_size+20)*8    # One bit takes one nano sec to transmit at 1G
    frame_tx_interval_count = 1000            # Number of frame transmitted in a GCL entry time interval
    time_interval = frame_tx_interval_count * frame_tx_time_nano
    cycle_time = 3*time_interval
    max_sdu = frame_size + (frame_size/2)

    t_i ("Create GCL")

    gcl = [{"gate_operation":"MESA_QOS_TAS_GCO_SET_GATE_STATES",
            "gate_open":[true,false,false,false,false,false,false,false],
            "time_interval":time_interval},
           {"gate_operation":"MESA_QOS_TAS_GCO_SET_GATE_STATES",
            "gate_open":[false,false,false,true,false,false,false,false],
            "time_interval":time_interval},
           {"gate_operation":"MESA_QOS_TAS_GCO_SET_GATE_STATES",
            "gate_open":[false,false,false,false,false,false,false,true],
            "time_interval":time_interval}]

    $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[ig[0]], 3, gcl)       # Create dummy GCL in order to test that multiple lists are possible
    $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[eg], 3, gcl)

    t_i ("Get TOD of domain 0")
    tod = $ts.dut.call("mesa_ts_timeofday_get")
    tod[0]["seconds"] = 0
    tod[0]["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_timeofday_set", tod[0])

    t_i ("Start GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[eg])
    conf["max_sdu"][0] = max_sdu
    conf["max_sdu"][3] = max_sdu
    conf["max_sdu"][7] = max_sdu
    conf["gate_enabled"] = true
    conf["ot"] = ot
    conf["gate_open"].each_index {|i| conf["gate_open"][i] = true}
    conf["cycle_time"] = cycle_time
    conf["cycle_time_ext"] = 256
    conf["base_time"]["nanoseconds"] = 0
    conf["base_time"]["seconds"] = 4
    conf["base_time"]["sec_msb"] = 0
    conf["gate_enabled"] = true
    conf["config_change"] = true
    $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[ig[0]], conf)       # Start dummy TAS in order to test that multiple lists are possible
    $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Check GCL is pending")
    conf = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (conf["config_pending"] != true)
        t_e("GCL unexpected config_pending = #{conf["config_pending"]}")
    end

    t_i ("Wait for GCL to start")
    sleep 5

    t_i ("Check GCL is started")
    conf = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (conf["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{conf["config_pending"]}")
    end
    time = conf["config_change_time"]
    if ((time["nanoseconds"] != 0) || (time["seconds"] != 4) || (time["sec_msb"] != 0))
        t_e("GCL unexpected config_change_time = nanoseconds #{time["nanoseconds"]} seconds #{time["seconds"]} sec_msb #{time["sec_msb"]}")
    end
    open = 0
    conf["gate_open"].each do |value|
        if (value == true)
            open += 1
        end
    end
    if (open != 1)
        t_e("GCL unexpected number of open gates #{open}")
    end

    $ts.dut.run("mesa-cmd mac flush")
    $ts.pc.run("sudo ef tx #{$ts.pc.p[eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ctag vid #{it_vid} ipv4 dscp 0")
    $ts.pc.run("sudo ef tx #{$ts.pc.p[eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ctag vid #{ot_vid} ipv4 dscp 0")

    t_i"Check that too large frames are discarded"
   #measure(ig, eg, size,        sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, max_sdu + 1, 2,     false,            false,           [0,0,0],             [1,1,1],        true,              [0,3,7], [cycle_time,cycle_time,cycle_time])

    erate = 990000000/3
   #measure(ig, eg, size,       sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, frame_size, 2,     false,            false,           [erate,erate,erate], [1,1,1],        true,              [0,3,7], [cycle_time,cycle_time,cycle_time])

    t_i ("Stop GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[eg])
    conf["gate_enabled"] = false
    conf["config_change"] = false
    conf = $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Wait for GCL to stop")
    sleep 2

    t_i ("Check GCL is stopped")
    conf = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (conf["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{conf["config_pending"]}")
    end
    time = conf["config_change_time"]
    if ((time["nanoseconds"] != 0) || (time["seconds"] != 0) || (time["sec_msb"] != 0))
        t_e("GCL unexpected config_change_time = nanoseconds #{time["nanoseconds"]} seconds #{time["seconds"]} sec_msb #{time["sec_msb"]}")
    end
    open = 0
    conf["gate_open"].each do |value|
        if (value == true)
            open += 1
        end
    end
    if (open != 8)
        t_e("GCL unexpected number of open gates #{open}")
    end

    pcp0 = 770
    pcp3 = 850
    pcp7 = 2
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X"))
        pcp0 = 1100
        pcp3 = 1300
    end
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        pcp0 = 900
        pcp3 = 1400
    end
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN969X"))
        pcp0 = 10
        pcp3 = 940
        pcp7 = 0.5
    end

    t_i ("Strict scheduling test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}")
    # Only expect frames in the highest priority queue when running strict scheduling
    $ts.dut.run("mesa-cmd mac flush")
    $ts.pc.run("sudo ef tx #{$ts.pc.p[eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ctag vid #{it_vid} ipv4 dscp 0")
    $ts.pc.run("sudo ef tx #{$ts.pc.p[eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ctag vid #{ot_vid} ipv4 dscp 0")
   #measure(ig, eg, size,       sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1,      with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure(ig, eg, 600, 1,     false,            false,           [0,0,990000000],  [pcp0,pcp3,pcp7], true,              [0,3,7]) # On SparX-5 some lower priority frames are slipping through

    t_i ("Stop dummy GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[ig[0]])
    conf["gate_enabled"] = false
    conf["config_change"] = false
    conf = $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[ig[0]], conf)
    end
end
