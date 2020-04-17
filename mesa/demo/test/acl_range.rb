#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Hack, only Serval-1 has this capability and warm start
cap_check_exit("L2_VCAP_PORT_CONF")

#---------- Configuration -----------------------------------------------------

def ace_add(id, id_next = 0)
    if (id == 1)
        # ACE 1: Discard UDP port 1-3
        port_action = "MESA_ACL_PORT_ACTION_FILTER"
        dport_min = 1
    else
        # Add 2: Forward UDP port 4-6
        port_action = "MESA_ACL_PORT_ACTION_NONE"
        dport_min = 4
    end

    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_IPV4")
    ace["id"] = id
    ace["port_list"] = "#{$ts.dut.port_list[0]}"
    ipv4 = ace["frame"]["ipv4"]
    ipv4["proto"]["value"] = 17
    ipv4["proto"]["mask"] = 0xff
    ipv4["dport"]["low"] = dport_min
    ipv4["dport"]["high"] = (dport_min + 2)
    action = ace["action"]
    action["port_action"] = port_action
    action["port_list"] = ""
    $ts.dut.call("mesa_ace_add", id_next, ace)
end

def conf_func(warm)
    if (warm)
        ace_add(2)
        ace_add(1, 2)
    else
        ace_add(1)
        ace_add(2)
    end
end

#---------- Frame testing -----------------------------------------------------

def frame_func
    t_i("Send frame on host port 0, expect no frame on port 1 (ACL discard)")
    cmd = "sudo ef name f1 eth ipv4 udp dport 3"
    cmd += " tx #{$ts.pc.p[0]} name f1"
    cmd += " rx #{$ts.pc.p[1]}"
    $ts.pc.run(cmd)
end

#---------- Test execution ----------------------------------------------------

test "warm-start" do
    conf_func(false)
    frame_func
    warm_start($ts)
end
