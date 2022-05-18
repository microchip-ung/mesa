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

# On the IE4000, select configuration and reboot, one of these:
#
# HSR-SAN : 'copy hsr-san-config startup-config' and 'reload'
# HSR-VLAN: 'copy hsr-vlan-config startup-config' and 'reload'
# PRP-SAN : 'copy prp-san-config startup-config' and 'reload'
# PRP-VLAN: 'copy prp-vlan-config startup-config' and 'reload'

# Before test, RedBox mode is selected
$mode = "PRP_SAN"
#$mode = "HSR_SAN"

# Select if VLAN tagging is used on LRE ports
$vlan = false

test "conf" do
    if ($vlan)
        # VLAN tagging on LRE ports
        [2,3].each do |port|
            conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
            conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
            conf["untagged_vid"] = 0
            $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
        end
    end

    if ($mode == nil)
        # PVLAN setup for debugging frames
        $ts.dut.call("mesa_pvlan_port_members_set", 0, "0,2")
        $ts.dut.call("mesa_pvlan_port_members_set", 1, "1,3")
        break
    end

    # RedBox configuration
    rb_id = 0
    conf = $ts.dut.call("mesa_rb_conf_get", rb_id)
    conf["mode"] = ("MESA_RB_MODE_" + $mode)
    conf["port_a"] = 2
    conf["port_b"] = 3
    conf["dd_age_time"] = 10000
    conf["sv"] = "MESA_RB_SV_CPU_ONLY"
    $ts.dut.call("mesa_rb_conf_set", rb_id, conf)
end

test "frame-io" do
    idx_list = [0,1,2,3]
    tx_list = idx_list
    #tx_list = [2]
    tx_list.each do |idx_tx|
        cmd = "sudo ef name f1 eth smac #{idx_tx + 1} et 0xaaaa data pattern cnt 46"
        idx_list.each do |idx|
            name = $ts.pc.p[idx]
            if (idx == idx_tx)
                cmd += " tx #{name} name f1"
            else
                cmd += " rx #{name} name f1"
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
