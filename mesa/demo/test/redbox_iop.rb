#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# RedBox interoperability test of Laguna against Cisco IE4000 switch.
# The setup below must be established:
#
# +------+           +----------+
# |    0 |- R --- 0--|          |
# |      |           |  Laguna  | Switch Core
# |    1 |- G --- 1 -|          |
# |      |           +----------+
# |      |           |  RedBox  | HSR-SAN or PRP-SAN
# |      |           +----------+
# |      |              |    |
# |      |              2    3
# |  PC  |              |    |
# |      |       Port A |    | Port B
# |      |              |    |
# |      |              1    2
# |      |              |    |
# |      |           +----------+
# |    2 |- B --- 3 -|          |
# |      |           |  IE4000  | HSR-SAN or PRP-SAN
# |    3 |- Y --- 4 -|          |
# +------+           +----------+
#    |                     |
#  Local                   10     Management (disabled)
#    |                     |
#    +---------------------+

# On the IE4000, select configuration and boot, either:
#
# 'copy hsr-san-config startup-config' and 'reload'
#
# or:
#
# 'copy prp-san-config startup-config' and 'reload'

# Before test, select HSR-SAN or PRP-SAN mode
$hsr = false

test "conf" do
    # RedBox configuration
    rb_id = 0
    conf = $ts.dut.call("mesa_rb_conf_get", rb_id)
    conf["mode"] = ("MESA_RB_MODE_" + ($hsr ? "HSR_SAN" : "PRP_SAN"))
    conf["port_a"] = 2
    conf["port_b"] = 3
    conf["dd_age_time"] = 10000
    if (true)
        # RedBox setup
        $ts.dut.call("mesa_rb_conf_set", rb_id, conf)
    else
        # PVLAN setup for debugging frames
        $ts.dut.call("mesa_pvlan_port_members_set", 0, "0,2")
        $ts.dut.call("mesa_pvlan_port_members_set", 1, "1,3")
    end
end

test "frame-io" do
    idx_list = [0,1,2,3]
    tx_list = idx_list
    #tx_list = [2]
    tx_list.each do |idx_tx|
        cmd = "sudo ef"
        cmd += " name f1 eth smac #{idx_tx + 1} et 0xaaaa data pattern cnt 46"
        # In HSR-SAN mode, Supervision frames are seen when proxy node is learned
        sv = ($hsr and idx_tx > 1)
        if (sv)
            # Ignoring 46 bytes data using IPv6(40) and HSR(6) headers
            cmd += " name sv eth ign dmac 01:15:4e:00:01:00 ipv6 ign htag ign"
        end
        idx_list.each do |idx|
            name = $ts.pc.p[idx]
            if (idx == idx_tx)
                cmd += " tx #{name} name f1"
            else
                cmd += " rx #{name} name f1"
                if (sv and idx < 2)
                    # Ignore Supervision frames
                    cmd += " rx #{name} name sv"
                end
            end
        end
        $ts.pc.try(cmd)
    end
end

test "dump" do
    break
    $ts.dut.run("mesa-cmd deb api cil redbox act 1")
    $ts.dut.run("mesa-cmd deb api ail coun")
end
