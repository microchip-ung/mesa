#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $ot_it = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_OT")
    assert(($ot_it == 1), "OT/IT must be supported")
end


idx = 0
ig = [0,0,0]
eg = 0
# Ingress ports are 0-2. Egress is port 3
for i in 0..3
    if (($ts.dut.p[i] >= 0) && ($ts.dut.p[i] <= 2))
        ig[idx] = i
        idx = idx + 1
    end
    if ($ts.dut.p[i] == 3)
        eg = i
    end
end

test "test_conf" do
    t_i("Configure the test to OT by calling the example code command")
    $ts.dut.run("mesa-cmd example init ot")
    sleep 5
end

test "test_run" do
    frame_size = 500
    cycle_frames = 1000*3
    frame_tx_time_nano = (frame_size+20)*8    # One bit takes one nano sec to transmit at 1G
    cycle_time = cycle_frames * frame_tx_time_nano
    ot_vid = 100

    t_i("OT test")

    t_i("Learn the destination MAC on the egress port")
    $ts.pc.run("sudo ef tx #{$ts.pc.p[eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ctag vid #{ot_vid} ipv4 dscp 0")

    test "OT scheduling strict test" do
        measure(ig, eg, 600, 1,     false,            false,           [0,0,990000000],  [150,535,2],  true,              [0,3,7])
    end

    $ts.dut.run("mesa-cmd example run command 0")

    test "OT DWRR scheduling test" do
        erate0 = 990000000*1/10
        erate1 = 990000000*3/10
        erate2 = 990000000*6/10

        measure(ig, eg, 600, 1,     false,            false,           [erate0,erate1,erate2], [4,6.5,5.1],   true,              [0,1,2])
    end
#$ts.dut.run("mesa-cmd deb api cil qos act 6")
#$ts.dut.run("mesa-cmd deb api cil qos act 18")
#$ts.dut.run("mesa-cmd port statis")
#$ts.dut.run("mesa-cmd vlan pvid")
#$ts.dut.run("mesa-cmd mac dump")

    $ts.dut.run("mesa-cmd example run command 3")

    test "OT shaper test" do
        measure([ig[0]], eg, 1000, 1,     false,            false,           [500000000],      [0.7],         true)
    end

    $ts.dut.run("mesa-cmd example run command 2")

    test "OT queue shaper tests" do
        [0,3,7].each do |cos|
            measure([ig[0]], eg, 1000, 1,     false,            false,           [100000000],      [0.7],         false,             [cos])
        end
    end

    $ts.dut.run("mesa-cmd example run command 1")

    erate0 = (1000000000 * 10) / 100  #Priority 0 is 10%
    erate4 = (1000000000 * 30) / 100  #Priority 4 is 30%
    erate7 = (1000000000 * 60) / 100  #Priority 7 is 60%
    measure(ig, eg, frame_size, 2,     false,            false,           [erate0,erate4,erate7], [1.2,1.2,1.2],        true,              [0,4,7], [cycle_time,cycle_time,cycle_time])

#    test "OT TAS Priority 0 test" do
#        erate = (1000000000 * 10) / 100  #Priority 0 is 10%
#        measure([ig[0]], eg, frame_size,   2,     false,            false,           [erate],             [2],            true,              [0],     [cycle_time])
#    end
#
#    test "OT TAS Priority 4 test" do
#        erate = (1000000000 * 30) / 100  #Priority 4 is 30%
#        measure([ig[0]], eg, frame_size,   2,     false,            false,           [erate],             [1],            true,              [4],     [cycle_time])
#    end
#
#    test "OT TAS Priority 7 test" do
#        erate = (1000000000 * 60) / 100  #Priority 7 is 60%
#        measure([ig[0]], eg, frame_size,   2,     false,            false,           [erate],             [1],            true,              [7],     [cycle_time])
#    end
#
#    test "OT TAS Priority 1 test" do
#        measure([ig[0]], eg, frame_size,   2,     false,            false,           [0],                 [0],            true,              [1],     [0])
#    end
end

test "test_clean_up" do
    t_i("Clean up the test by calling the example code command")
    $ts.dut.run("mesa-cmd example uninit")
end
