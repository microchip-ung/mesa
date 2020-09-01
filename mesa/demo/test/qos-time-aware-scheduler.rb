#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $dpl_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_DPL_CNT")
    $tas_support = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_TAS")
    assert(($tas_support == 1),
           "TAS not supported on this platform")
end

MESA_VID_NULL = 0

def equal_interval_gcl_reconfig_test
    eg = rand(3)    # Get a random egress port between 0 and 3
    ig = [0,1,2,3] - [eg]  # Calculate ingress list as all other ports

    test "Time aware scheduling GCL re-configuration test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}" do

    frame_size = 500
    frame_tx_time_nano = (frame_size+20)*8                       # One bit takes one nano sec to transmit at 1G
    frame_tx_interval_count = 1000                               # Number of frame transmitted in a GCL entry time interval
    time_interval = frame_tx_interval_count * frame_tx_time_nano # number of nano for each interval
    cycle_time = 3*time_interval                                 # GCL cycle time
    cycle_time_ext = time_interval / 2                           # GCL cycle time extension

    t_i ("Create GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_gcl_conf_get", $ts.dut.p[eg], 256)
    gcl = conf[0]
    gce_cnt = conf[1]
    gcl[0]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[0]["gate_open"].each_index {|i| gcl[0]["gate_open"][i] = false}
    gcl[0]["gate_open"][0] = true
    gcl[0]["time_interval"] = time_interval
    gcl[1]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[1]["gate_open"].each_index {|i| gcl[1]["gate_open"][i] = false}
    gcl[1]["gate_open"][3] = true
    gcl[1]["time_interval"] = time_interval
    gcl[2]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[2]["gate_open"].each_index {|i| gcl[2]["gate_open"][i] = false}
    gcl[2]["gate_open"][7] = true
    gcl[2]["time_interval"] = time_interval
    $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[eg], 3, gcl)

    t_i ("Get TOD of domain 0")
    tod = $ts.dut.call("mesa_ts_timeofday_get")
    tod[0]["seconds"] = 0
    tod[0]["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_timeofday_set", tod[0])

    t_i ("Start GCL")
    base_time = tod[0].dup
    base_time["seconds"] = 3
    conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[eg])
    conf["max_sdu"][0] = frame_size + (frame_size/2)
    conf["max_sdu"][3] = frame_size + (frame_size/2)
    conf["max_sdu"][7] = frame_size + (frame_size/2)
    conf["gate_enabled"] = true
    conf["gate_open"].each_index {|i| conf["gate_open"][i] = true}
    conf["cycle_time"] = cycle_time
    conf["cycle_time_ext"] = cycle_time_ext
    conf["base_time"] = base_time
    conf["gate_enabled"] = true
    conf["config_change"] = true
    $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Wait for GCL to start")
    sleep 3

    t_i ("Check GCL is started")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end

    t_i ("Measure the frame rate and cycle time")
    erate = 990000000/3
   #measure(ig, eg, size,       sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, frame_size, 2,     false,            false,           [erate,erate,erate], [1,1,1],        true,              [0,3,7], [cycle_time,cycle_time,cycle_time])

    t_i ("-----------Create new GCL with new interval time for cycle extension----------------")
    frame_tx_interval_count = 700                                # Number of frame transmitted in a GCL entry time interval
    time_interval = frame_tx_interval_count * frame_tx_time_nano # number of nano for each interval
    cycle_time_1 = 3*time_interval                                 # GCL cycle time
    cycle_time_ext_1 = time_interval / 2                       # GCL cycle time extension
    gcl[0]["time_interval"] = time_interval
    gcl[1]["time_interval"] = time_interval
    gcl[2]["time_interval"] = time_interval
    $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[eg], 3, gcl)

    t_i ("Re-configurate GCL with cycle extension")
    # Calculate a new base time two seconds away at cycle end time
    tod = $ts.dut.call("mesa_ts_timeofday_get")
    seconds = tod[0]["seconds"] + 2
    base_time_1 = base_time.dup
    while true
        base_time_1["nanoseconds"] += cycle_time
        if (base_time_1["nanoseconds"] >= 1000000000)
            base_time_1["seconds"] += 1
            base_time_1["nanoseconds"] -= 1000000000
        end

        if (base_time_1["seconds"] > seconds)
            break;
        end
    end
    # Add half a extension time to assure extension
    base_time_1["nanoseconds"] += (cycle_time_ext/2)
    if (base_time_1["nanoseconds"] >= 1000000000)
        base_time_1["seconds"] += 1
        base_time_1["nanoseconds"] -= 1000000000
    end
    # Start new GCL
    conf["cycle_time"] = cycle_time_1
    conf["cycle_time_ext"] = cycle_time_ext
    conf["base_time"] = base_time_1
    $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Wait for GCL to start")
    sleep 3

    t_i ("Check GCL is started")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end

    t_i ("Measure the frame rate and cycle time")
    erate = 990000000/3
   #measure(ig, eg, size,       sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, frame_size, 2,     false,            false,           [erate,erate,erate], [1,1,1],        true,              [0,3,7], [cycle_time_1,cycle_time_1,cycle_time_1])

    t_i ("------------Create new GCL with new interval time for cycle truncation----------")
    frame_tx_interval_count = 400                                # Number of frame transmitted in a GCL entry time interval
    time_interval = frame_tx_interval_count * frame_tx_time_nano # number of nano for each interval
    cycle_time_2 = 3*time_interval                                 # GCL cycle time
    cycle_time_ext_2 = time_interval / 2                           # GCL cycle time extension
    gcl[0]["time_interval"] = time_interval
    gcl[1]["time_interval"] = time_interval
    gcl[2]["time_interval"] = time_interval
    $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[eg], 3, gcl)

    t_i ("Re-configurate GCL with cycle trunkation")
    # Calculate a new base time two seconds away at cycle end time
    tod = $ts.dut.call("mesa_ts_timeofday_get")
    seconds = tod[0]["seconds"] + 2
    base_time_2 = base_time_1.dup
    while true
        base_time_2["nanoseconds"] += cycle_time_1
        if (base_time_2["nanoseconds"] >= 1000000000)
            base_time_2["seconds"] += 1
            base_time_2["nanoseconds"] -= 1000000000
        end

        if (base_time_2["seconds"] > seconds)
            break;
        end
    end
    # Add two extension time to assure trunkation
    base_time_2["nanoseconds"] += (2*cycle_time_ext_1)
    if (base_time_2["nanoseconds"] >= 1000000000)
        base_time_2["seconds"] += 1
        base_time_2["nanoseconds"] -= 1000000000
    end
    # Start new GCL
    conf["cycle_time"] = cycle_time_2
    conf["cycle_time_ext"] = cycle_time_ext_1
    conf["base_time"] = base_time_2
    $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Wait for GCL to start")
    sleep 3

    t_i ("Check GCL is started")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end

    t_i ("Measure the frame rate and cycle time")
    erate = 990000000/3
   #measure(ig, eg, size,       sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],  cycle_time=[])
    measure(ig, eg, frame_size, 2,     false,            false,           [erate,erate,erate], [1,1,1],        true,              [0,3,7], [cycle_time_2,cycle_time_2,cycle_time_2])

    t_i ("Stop GCL")
    conf["gate_enabled"] = false
    conf["config_change"] = false
    conf = $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Wait for GCL to stop")
    sleep 2

    t_i ("Check GCL is stopped")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end

    t_i ("Strict scheduling test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}")
    # Only expect frames in the highest priority queue when running strict scheduling
   #measure(ig, eg, size,       sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure(ig, eg, frame_size, 1,     false,            false,           [0,0,990000000],  [150,500,2], true,              [0,3,7]) # On SparX-5 some lower priority frames are slipping through
    end
end

def equal_interval_3_prio_1_port_test
    eg = rand(3)    # Get a random egress port between 0 and 3
    ig = [0,1,2,3] - [eg]  # Calculate ingress list as all other ports

    test "Time aware scheduling with equal time slots test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}" do

    frame_size = 500
    frame_tx_time_nano = (frame_size+20)*8    # One bit takes one nano sec to transmit at 1G
    frame_tx_interval_count = 1000            # Number of frame transmitted in a GCL entry time interval
    time_interval = frame_tx_interval_count * frame_tx_time_nano
    cycle_time = 3*time_interval

    t_i ("Create GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_gcl_conf_get", $ts.dut.p[eg], 256)
    gcl = conf[0]
    gce_cnt = conf[1]
    gcl[0]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[0]["gate_open"].each_index {|i| gcl[0]["gate_open"][i] = false}
    gcl[0]["gate_open"][0] = true
    gcl[0]["time_interval"] = time_interval
    gcl[1]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[1]["gate_open"].each_index {|i| gcl[1]["gate_open"][i] = false}
    gcl[1]["gate_open"][3] = true
    gcl[1]["time_interval"] = time_interval
    gcl[2]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[2]["gate_open"].each_index {|i| gcl[2]["gate_open"][i] = false}
    gcl[2]["gate_open"][7] = true
    gcl[2]["time_interval"] = time_interval
    $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[ig[0]], 3, gcl)       # Create dummy GCL in order to test that multiple lists are possible
    $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[eg], 3, gcl)

    t_i ("Get TOD of domain 0")
    tod = $ts.dut.call("mesa_ts_timeofday_get")
    tod[0]["seconds"] = 0
    tod[0]["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_timeofday_set", tod[0])

    t_i ("Start GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[eg])
    conf["max_sdu"][0] = frame_size + (frame_size/2)
    conf["max_sdu"][3] = frame_size + (frame_size/2)
    conf["max_sdu"][7] = frame_size + (frame_size/2)
    conf["gate_enabled"] = true
    conf["gate_open"].each_index {|i| conf["gate_open"][i] = true}
    conf["cycle_time"] = cycle_time
    conf["cycle_time_ext"] = 0
    conf["base_time"]["nanoseconds"] = 0
    conf["base_time"]["seconds"] = 3
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
    sleep 3

    t_i ("Check GCL is started")
    conf = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (conf["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{conf["config_pending"]}")
    end
    time = conf["config_change_time"]
    if ((time["nanoseconds"] != 0) || (time["seconds"] != 3) || (time["sec_msb"] != 0))
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

    t_i ("Strict scheduling test from #{$ts.dut.p[ig[0]]},#{$ts.dut.p[ig[1]]},#{$ts.dut.p[ig[2]]} to #{$ts.dut.p[eg]}")
    # Only expect frames in the highest priority queue when running strict scheduling
   #measure(ig, eg, size,       sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
    measure(ig, eg, frame_size, 1,     false,            false,           [0,0,990000000],  [150,500,2], true,              [0,3,7]) # On SparX-5 some lower priority frames are slipping through

    t_i ("Stop dummy GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[ig[0]])
    conf["gate_enabled"] = false
    conf["config_change"] = false
    conf = $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[ig[0]], conf)
    end
end

def jira_appl_3396_test
    eg = rand(3)    # Get a random egress port between 0 and 3

    test "Time aware scheduling JIRA APPL-3396" do

    t_i ("Create GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_gcl_conf_get", $ts.dut.p[eg], 256)
    gcl = conf[0]
    gce_cnt = conf[1]
    gcl[0]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[0]["gate_open"].each_index {|i| gcl[0]["gate_open"][i] = false}
    gcl[0]["gate_open"][0] = true
    gcl[0]["gate_open"][1] = true
    gcl[0]["gate_open"][2] = true
    gcl[0]["gate_open"][3] = true
    gcl[0]["time_interval"] = 128
    gcl[1]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[1]["gate_open"].each_index {|i| gcl[1]["gate_open"][i] = false}
    gcl[1]["gate_open"][4] = true
    gcl[1]["gate_open"][5] = true
    gcl[1]["gate_open"][6] = true
    gcl[1]["gate_open"][7] = true
    gcl[1]["time_interval"] = 128
    $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[eg], 2, gcl)

    t_i ("Get TOD of domain 0")
    tod = $ts.dut.call("mesa_ts_timeofday_get")
    tod[0]["seconds"] = 0
    tod[0]["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_timeofday_set", tod[0])

    t_i ("Start GCL")
    conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[eg])
    conf["max_sdu"][0] = 64
    conf["max_sdu"][3] = 64
    conf["max_sdu"][7] = 64
    conf["gate_enabled"] = true
    conf["gate_open"].each_index {|i| conf["gate_open"][i] = true}
    conf["cycle_time"] = 256
    conf["cycle_time_ext"] = 0
    conf["base_time"]["nanoseconds"] = 303697500
    conf["base_time"]["seconds"] = 3
    conf["base_time"]["sec_msb"] = 0
    conf["gate_enabled"] = true
    conf["config_change"] = true
    $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Check GCL is pending")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] != true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end

    t_i ("Wait for GCL to start")
    sleep 3

    t_i ("Check GCL is started")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end

    t_i ("Start GCL again")
    conf["base_time"]["seconds"] = 6
    $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Check GCL is pending")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] != true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end

    t_i ("Wait for GCL to start")
    sleep 3

    t_i ("Check GCL is started")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end

    t_i ("Stop GCL")
    conf["gate_enabled"] = false
    conf["config_change"] = false
    conf = $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg], conf)

    t_i ("Wait for GCL to stop")
    sleep 2

    t_i ("Check GCL is stopped")
    status = $ts.dut.call("mesa_qos_tas_port_status_get", $ts.dut.p[eg])
    if (status["config_pending"] == true)
        t_e("GCL unexpected config_pending = #{status["config_pending"]}")
    end
    end
end

def equal_interval_1_prio_3_port_test
    ig = rand(3)    # Get a random ingress port between 0 and 3
    eg = [0,1,2,3] - [ig]  # Calculate engress list as all other ports

    test "Time aware scheduling with equal time slots test from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg[0]]},#{$ts.dut.p[eg[1]]},#{$ts.dut.p[eg[2]]}" do

    frame_size = 500
    frame_tx_time_nano = (frame_size+20)*8    # One bit takes one nano sec to transmit at 1G
    frame_tx_interval_count = 1000            # Number of frame transmitted in a GCL entry time interval
    time_interval = frame_tx_interval_count * frame_tx_time_nano
    cycle_time = 3*time_interval

    t_i ("Initialize GCL configuration")
    conf = $ts.dut.call("mesa_qos_tas_port_gcl_conf_get", $ts.dut.p[eg[0]], 256)
    gcl = conf[0]
    gce_cnt = conf[1]
    gcl[0]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[0]["gate_open"].each_index {|i| gcl[0]["gate_open"][i] = false}
    gcl[0]["time_interval"] = time_interval
    gcl[1]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[1]["gate_open"].each_index {|i| gcl[1]["gate_open"][i] = false}
    gcl[1]["time_interval"] = time_interval
    gcl[2]["gate_operation"] = "MESA_QOS_TAS_GCO_SET_GATE_STATES"
    gcl[2]["gate_open"].each_index {|i| gcl[2]["gate_open"][i] = false}
    gcl[2]["time_interval"] = time_interval

    t_i ("Create GCL on all egress ports")
    eg.each do |eg_idx|
        gcl[1]["gate_open"][eg_idx] = true  #Enable this prio
        $ts.dut.call("mesa_qos_tas_port_gcl_conf_set", $ts.dut.p[eg_idx], 3, gcl)
        gcl[1]["gate_open"][eg_idx] = false     #This prio must be false in next loop
    end

    t_i ("Get TOD of domain 0")
    tod = $ts.dut.call("mesa_ts_timeofday_get")
    tod[0]["seconds"] = 0
    tod[0]["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_timeofday_set", tod[0])

    t_i ("Start TAS on all egress ports")
    eg.each do |eg_idx|
        t_i ("Start GCL")
        conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[eg_idx])
        conf["max_sdu"][eg_idx] = frame_size + (frame_size/2)
        conf["gate_enabled"] = true
        conf["gate_open"].each_index {|i| conf["gate_open"][i] = true}
        conf["cycle_time"] = cycle_time
        conf["cycle_time_ext"] = 0
        conf["base_time"]["nanoseconds"] = 0
        conf["base_time"]["seconds"] = 3
        conf["base_time"]["sec_msb"] = 0
        conf["gate_enabled"] = true
        conf["config_change"] = true
        conf = $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg_idx], conf)
    end

    t_i ("Wait for GCL to start")
    sleep 3

    t_i ("Test TAS on all egress ports")
    eg.each do |eg_idx|
       #measure(ig,   eg,     size,       sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],   cycle_time=[])
        measure([ig], eg_idx, frame_size, 2,     false,            false,           [990000000/3],       [2],            true,              [eg_idx], [cycle_time])
    end

    t_i ("Stop TAS on all egress ports")
    eg.each do |eg_idx|
        t_i ("Stop GCL")
        conf = $ts.dut.call("mesa_qos_tas_port_conf_get", $ts.dut.p[eg_idx])
        conf["gate_enabled"] = false
        conf["config_change"] = false
        conf = $ts.dut.call("mesa_qos_tas_port_conf_set", $ts.dut.p[eg_idx], conf)
    end

    t_i ("Wait for GCL to stop")
    sleep 2

    t_i ("Test witout TAS on all egress ports")
    eg.each do |eg_idx|
       #measure(ig, eg,       size,       sec=1, frame_rate=false, data_rate=false, erate=[1000000000],  etolerance=[1], with_pre_tx=false, pcp=[],   cycle_time=[])
        measure([ig], eg_idx, frame_size, 1,     false,            false,           [990000000],         [1],            true,              [eg_idx])
    end
    end
end

test "test_conf" do
    $qconf0 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[0])
    $qconf1 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[1])
    $qconf2 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[2])
    $qconf3 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[3])
    $vconf0 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[0])
    $vconf1 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[1])
    $vconf2 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[2])
    $vconf3 = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[3])
    $dconf0 = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[0], $dpl_cnt)
    $dconf1 = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[1], $dpl_cnt)
    $dconf2 = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[2], $dpl_cnt)
    $dconf3 = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[3], $dpl_cnt)

    t_i ("Only forward on relevant ports #{$ts.dut.port_list}")
    port_list = "#{$ts.dut.port_list[0]},#{$ts.dut.port_list[1]},#{$ts.dut.port_list[2]},#{$ts.dut.port_list[3]}"
    $ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

    t_i ("Configure all ports to C tag aware")
    (0..3).each do |i|
        $ts.dut.run("mesa-cmd port flow control #{$ts.dut.p[i]+1} disable")

        t_i ("Configure all ports to C tag aware")
        conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[i])
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["untagged_vid"] = MESA_VID_NULL
        $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[i], conf)

        t_i("Configure ingress prio classificationand prio and dpl mapping to 1:1")
        t_i("Configure egress prio and dpl tagging to mapped. Also enable port shaper to assure queues are never emptied")
        conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[i])
        conf["tag"]["class_enable"] = true
        conf["tag"]["remark_mode"] = "MESA_TAG_REMARK_MODE_MAPPED"
        conf["tag"]["pcp_dei_map"][0][0]["prio"] = 0
        conf["tag"]["pcp_dei_map"][0][0]["dpl"] = 0
        conf["tag"]["pcp_dei_map"][0][1]["prio"] = 0
        conf["tag"]["pcp_dei_map"][0][1]["dpl"] = 1
        conf["tag"]["pcp_dei_map"][1][0]["prio"] = 1
        conf["tag"]["pcp_dei_map"][1][0]["dpl"] = 0
        conf["tag"]["pcp_dei_map"][1][1]["prio"] = 1
        conf["tag"]["pcp_dei_map"][1][1]["dpl"] = 1
        conf["default_prio"] = i
        conf["default_dpl"] = 0
        conf["shaper"]["level"] = 25000    # Shaper must have "large" burst size level in order to shape correctly at "high" rates
        conf["shaper"]["rate"] = 990000
        conf["shaper"]["mode"] = "MESA_SHAPER_MODE_LINE"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[i], conf)

        t_i("Configure egress prio and dpl mapping to 1:1")
        dconf = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[i], $dpl_cnt)
        dconf[0]["pcp"] = [0,1,2,3,4,5,6,7]
        dconf[0]["dei"] = [0,0,0,0,0,0,0,0]
        dconf[1]["pcp"] = [0,1,2,3,4,5,6,7]
        dconf[1]["dei"] = [1,1,1,1,1,1,1,1]
        $ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[i], $dpl_cnt, dconf)
    end
end

test "test_run" do
    t_i("Test call of TAS global configuration")
    conf = $ts.dut.call("mesa_qos_tas_conf_get")
    conf["always_guard_band"] = false
    conf = $ts.dut.call("mesa_qos_tas_conf_set", conf)

    jira_appl_3396_test
    equal_interval_3_prio_1_port_test
    equal_interval_1_prio_3_port_test
    equal_interval_gcl_reconfig_test
end

test "test_clean_up" do
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[0], $qconf0)
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[1], $qconf1)
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[2], $qconf2)
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[3], $qconf3)
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[0], $vconf0)
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[1], $vconf1)
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[2], $vconf2)
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[3], $vconf3)
    $ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[0], $dpl_cnt, $dconf0)
    $ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[1], $dpl_cnt, $dconf1)
    $ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[2], $dpl_cnt, $dconf2)
    $ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[3], $dpl_cnt, $dconf3)
end
