#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    $cap_synce = $ts.dut.call("mesa_capability", "MESA_CAP_SYNCE")
    $cap_in_type = $ts.dut.call("mesa_capability", "MESA_CAP_SYNCE_IN_TYPE")
    assert($cap_synce != 0, "SYNCE is not supported")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5).")
    console("cap_family #{$cap_family}  cap_synce #{$cap_synce}  cap_in_type #{$cap_in_type}")
end

def frequency_calc(speed, divider)
    undivided = 0

    if (speed == "1000fdx")
        undivided = 125.0
    end
    if (speed == "2500")
        undivided = 312.5
    end
    if (speed == "5g")
        undivided = 40.28320313
    end
    if (speed == "10g")
        undivided = 80.56640625000
    end
    if (speed == "25g")
        undivided = 322.265625
    end

    if (divider == "MESA_SYNCE_DIVIDER_1")
        return undivided/1
    end
    if (divider == "MESA_SYNCE_DIVIDER_2")
        return undivided/2
    end
    if (divider == "MESA_SYNCE_DIVIDER_4")
        return undivided/4
    end
    if (divider == "MESA_SYNCE_DIVIDER_5")
        return undivided/5
    end
    if (divider == "MESA_SYNCE_DIVIDER_8")
        return undivided/8
    end
    if (divider == "MESA_SYNCE_DIVIDER_16")
        return undivided/16
    end
    if (divider == "MESA_SYNCE_DIVIDER_25")
        return undivided/25
    end
end

def test_reco_clock(clock_out, speed, divider1, divider2)
    console("clock_out #{clock_out}  speed #{speed}")

    $ts.dut.run("mesa-cmd port mode #{$source_port+1} #{speed}")
    $ts.dut.run("mesa-cmd port mode #{$clock_port+1} #{speed}")
    sleep(1)
    $ts.dut.run("mesa-cmd port state #{$clock_port+1},#{$source_port+1}")

    conf = $ts.dut.call("mesa_synce_clock_in_get", clock_out)
    conf["port_no"] = $clock_port
    conf["squelsh"] = true
    conf["enable"] = true
    conf["clk_in"] = "MESA_SYNCE_CLOCK_INTERFACE"
    $ts.dut.call("mesa_synce_clock_in_set", clock_out, conf)

    conf = $ts.dut.call("mesa_synce_clock_out_get", clock_out)
    conf["divider"] = divider1
    conf["enable"] = true
    $ts.dut.call("mesa_synce_clock_out_set", clock_out, conf)

    console ("Recovered clock #{clock_out} is taken from Port #{$clock_port+1}. Divider is #{divider1}. Squelch is enabled. Port speed is #{speed}")
    console ("Observe Recovered clock active at #{frequency_calc(speed, divider1)} MHz")
    console ("Hit CR to shut down port")
    STDIN.gets
    $ts.dut.run("mesa-cmd port state #{$source_port+1} disable")

    console ("Observe Recovered clock NOT active")
    console ("Hit CR to disable squelch")
    STDIN.gets
    
    conf = $ts.dut.call("mesa_synce_clock_in_get", clock_out)
    conf["squelsh"] = false
    $ts.dut.call("mesa_synce_clock_in_set", clock_out, conf)

    console ("Observe Recovered clock active")
    console ("Hit CR to continue")
    STDIN.gets

    conf = $ts.dut.call("mesa_synce_clock_in_get", clock_out)
    conf["squelsh"] = true
    $ts.dut.call("mesa_synce_clock_in_set", clock_out, conf)

    $ts.dut.run("mesa-cmd port state #{$source_port+1} enable")

    conf = $ts.dut.call("mesa_synce_clock_out_get", clock_out)
    conf["divider"] = divider2
    $ts.dut.call("mesa_synce_clock_out_set", clock_out, conf)

    console ("Recovered clock #{clock_out} is taken from Port #{$clock_port+1}. Divider is #{divider2}. Squelch is enabled. Port speed is #{speed}")
    console ("Observe Recovered clock active at #{frequency_calc(speed, divider2)} MHz")
    console ("Hit CR to continue")
    STDIN.gets

    conf = $ts.dut.call("mesa_synce_clock_out_get", clock_out)
    conf["enable"] = false
    $ts.dut.call("mesa_synce_clock_out_set", clock_out, conf)

    console ("Recovered clock is disabled - Observe NOT active")
    console ("Hit CR to continue")
    STDIN.gets
end

def test_port_speed_change
    test "test_port_speed_change" do
    $clock_port = 8
    $source_port = 10

    console ("connect port #{$clock_port+1} and port #{$source_port+1} with optical fiber using 25G SFP")

    console ("connect measurement to Recovered clock #{$clock_out0}")
    console ("Hit CR to continue")
    STDIN.gets

    $ts.dut.run("mesa-cmd port mode #{$source_port+1} 1000fdx")
    $ts.dut.run("mesa-cmd port mode #{$clock_port+1} 1000fdx")
    sleep(1)
    $ts.dut.run("mesa-cmd port state #{$clock_port+1},#{$source_port+1}")

    conf = $ts.dut.call("mesa_synce_clock_in_get", $clock_out0)
    conf["port_no"] = $clock_port
    conf["squelsh"] = true
    conf["enable"] = true
    conf["clk_in"] = "MESA_SYNCE_CLOCK_INTERFACE"
    $ts.dut.call("mesa_synce_clock_in_set", $clock_out0, conf)

    conf = $ts.dut.call("mesa_synce_clock_out_get", $clock_out0)
    conf["divider"] = "MESA_SYNCE_DIVIDER_5"
    conf["enable"] = true
    $ts.dut.call("mesa_synce_clock_out_set", $clock_out0, conf)

    console ("Recovered clock #{$clock_out0} is taken from Port #{$clock_port+1}. Divider is MESA_SYNCE_DIVIDER_5. Squelch is enabled. Port speed is 1000fdx")
    console ("Observe Recovered clock active at #{frequency_calc("1000fdx", "MESA_SYNCE_DIVIDER_5")} MHz")
    console ("Hit CR to continue to change speed")
    STDIN.gets

    $ts.dut.run("mesa-cmd port mode #{$source_port+1} 10g")
    $ts.dut.run("mesa-cmd port mode #{$clock_port+1} 10g")
    sleep(1)
    $ts.dut.run("mesa-cmd port state #{$clock_port+1},#{$source_port+1}")

    console ("Recovered clock #{$clock_out0} is taken from Port #{$clock_port+1}. Divider is MESA_SYNCE_DIVIDER_5. Squelch is enabled. Port speed is 2500")
    console ("Observe Recovered clock active at #{frequency_calc("10g", "MESA_SYNCE_DIVIDER_5")} MHz")
    console ("Hit CR to continue")
    STDIN.gets

    conf = $ts.dut.call("mesa_synce_clock_out_get", $clock_out0)
    conf["enable"] = false
    $ts.dut.call("mesa_synce_clock_out_set", $clock_out0, conf)
    end
end

def test_10G_serdes
    test "test_10G_serdes" do
    $clock_port = 8
    $source_port = 10

    console ("connect port #{$clock_port+1} and port #{$source_port+1} with optical fiber using 25G SFP")

    console ("connect measurement to Recovered clock #{$clock_out0}")
    console ("Hit CR to continue")
    STDIN.gets

    test_reco_clock($clock_out0, "1000fdx", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_8")
    test_reco_clock($clock_out0, "2500", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_16")
    test_reco_clock($clock_out0, "5g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_2")
    test_reco_clock($clock_out0, "10g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_4")

    console ("connect measurement to Recovered clock #{$clock_out1}")
    console ("Hit CR to continue")
    STDIN.gets

    test_reco_clock($clock_out1, "1000fdx", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_25")
    test_reco_clock($clock_out1, "2500", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_4")
    test_reco_clock($clock_out1, "5g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_16")
    test_reco_clock($clock_out1, "10g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_5")
    end
end

def test_25G_serdes_10G_mode
    test "test_25G_serdes_10G_mode" do
    $clock_port = 12
    $source_port = 13

    console ("connect port #{$clock_port+1} and port #{$source_port+1} with optical fiber using 25G SFP")

    console ("connect measurement to Recovered clock #{$clock_out0}")
    console ("Hit CR to continue")
    STDIN.gets

    test_reco_clock($clock_out0, "1000fdx", "MESA_SYNCE_DIVIDER_2", "MESA_SYNCE_DIVIDER_5")
#    test_reco_clock($clock_out0, "2500", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_16")   Currently 2.5G is not working
    test_reco_clock($clock_out0, "5g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_2")
    test_reco_clock($clock_out0, "10g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_25")

    console ("connect measurement to Recovered clock #{$clock_out1}")
    console ("Hit CR to continue")
    STDIN.gets

    test_reco_clock($clock_out1, "1000fdx", "MESA_SYNCE_DIVIDER_2", "MESA_SYNCE_DIVIDER_5")
#    test_reco_clock($clock_out1, "2500", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_4")   Currently 2.5G is not working
    test_reco_clock($clock_out1, "5g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_16")
    test_reco_clock($clock_out1, "10g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_8")
    end
end

def test_25G_serdes_25G_mode
    test "test_25G_serdes_25G_mode" do
    $clock_port = 0
    $source_port = 1

    console ("The 10G ports are not used. 25G Port 1 is port 13")
    console ("connect port #{$clock_port+1} and port #{$source_port+1} with optical fiber using 25G SFP")

    console ("connect measurement to Recovered clock #{$clock_out0}")
    console ("Hit CR to continue")
    STDIN.gets

    test_reco_clock($clock_out0, "1000fdx", "MESA_SYNCE_DIVIDER_2", "MESA_SYNCE_DIVIDER_5")
#    test_reco_clock($clock_out0, "2500", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_16")   Currently 2.5G is not working
    test_reco_clock($clock_out0, "5g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_2")
    test_reco_clock($clock_out0, "10g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_25")
    test_reco_clock($clock_out0, "25g", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_4")

    console ("connect measurement to Recovered clock #{$clock_out1}")
    console ("Hit CR to continue")
    STDIN.gets

    test_reco_clock($clock_out1, "1000fdx", "MESA_SYNCE_DIVIDER_2", "MESA_SYNCE_DIVIDER_5")
#    test_reco_clock($clock_out1, "2500", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_4")   Currently 2.5G is not working
    test_reco_clock($clock_out1, "5g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_16")
    test_reco_clock($clock_out1, "10g", "MESA_SYNCE_DIVIDER_1", "MESA_SYNCE_DIVIDER_8")
    test_reco_clock($clock_out1, "25g", "MESA_SYNCE_DIVIDER_5", "MESA_SYNCE_DIVIDER_16")
    end
end

test "test_config" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")
end

test "test_run" do
    $clock_out0 = 2   # On PCB134 the clockout 0 on the SYNCE connector is connected to Fireant clock output 2
    $clock_out1 = 3   # On PCB134 the clockout 1 on the SYNCE connector is connected to Fireant clock output 3

    conf = $ts.dut.call("mesa_port_conf_get", 0)
    if (conf["speed"] == "MESA_SPEED_25G")
        test_25G_serdes_25G_mode
        console ("Change PCB to run 10G. Do the following linux commands:")
        console ("ps")
        console ("  ps-id root     er -b -l /tmp/console-er -- mesa-demo -f")
        console ("kill ps-id")
        console ("fw_setenv pcb_var")
        console ("mesa-demo")
    else
        test_port_speed_change
        test_10G_serdes
        test_25G_serdes_10G_mode
        console ("To change PCB to run 25G Do the following linux commands:")
        console ("ps")
        console ("              ps-id root     er -b -l /tmp/console-er -- mesa-demo -f")
        console ("kill ps-id")
        console ("fw_setenv pcb_var 9")
        console ("mesa-demo")
        console ("Run the script with option --no-init or the wire check will not pass")
    end
end

test "test_clean_up" do
end

