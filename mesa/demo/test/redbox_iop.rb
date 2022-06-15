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
# |      |           |  RedBox  | HSR-SAN/PRP-SAN/HSR-PRP
# |      |           +----------+
# |      |              |    |
# |      |              2    3
# |  PC  |              |    |
# |      |       Port A |    | Port B (down for HSR-PRP)
# |      |              |    |
# |      |              1    2
# |      |              |    |
# |      |           +----------+
# |    2 |- B --- 3 -|          |
# |      |           |  IE4000  | HSR-SAN/PRP-SAN/HSR-PRP
# |    3 |- Y --- 4 -|          |
# +------+           +----------+
#    |                     |
#  Local                   10     Management (disabled)
#    |                     |
#    +---------------------+

# Serial connection to the IE4000 system is currently done like this on the PC:
#
# termhub -b 9600 -d /dev/ttyS0
#
# On the IE4000, select configuration and reboot, one of these:
#
# HSR-SAN : 'copy hsr-san-config startup-config' and 'reload'
# HSR-VLAN: 'copy hsr-vlan-config startup-config' and 'reload'
# PRP-SAN : 'copy prp-san-config startup-config' and 'reload'
# PRP-VLAN: 'copy prp-vlan-config startup-config' and 'reload'
# HSR-PRP : 'copy hsr-prp-config startup-config' and 'reload'

# Laguna RedBox mode must match IE4000 RedBox mode
$mode = "PRP_SAN"
#$mode = "HSR_SAN"
#$mode = "HSR_PRP"

# Select if VLAN tagging is used on LRE ports
$vlan = false
#$vlan = true

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
    if ($mode == "HSR_PRP")
        conf["port_a"] = 0
        conf["port_b"] = 1
        conf["net_id"] = 6
    else
        conf["port_a"] = 2
        conf["port_b"] = 3
    end
    conf["dd_age_time"] = 10000
    conf["sv"] = "MESA_RB_SV_CPU_ONLY"
    $ts.dut.call("mesa_rb_conf_set", rb_id, conf)
end

test "frame-io" do
    hsr_prp = ($mode == "HSR_PRP")
    idx_list = [0,1,2,3]
    tx_list = idx_list
    #tx_list = [2]
    tx_list.each do |idx_tx|
        len = 46
        f_base = " eth smac #{idx_tx + 1}"
        f_end = " et 0xaaaa data pattern cnt #{len}"

        # Frame f1 (Tx and Rx)
        cmd = ("sudo ef name f1" + f_base)
        seqn = 7
        len += 6
        if (hsr_prp)
            cmd += " htag pathid 0 size #{len} seqn #{seqn}"
        end
        cmd += f_end

        if (hsr_prp)
            # Frame f2 (Rx)
            cmd += (" name f2" + f_base)
            if (idx_tx > 1)
                # IE4000 -> Laguna: NetId 6 and PRP trailer not popped by Laguna.
                netid = 6
                prp = " prp seqn #{seqn} lanid 0xa size #{len}"
                seqn = 1
                len += 6
            else
                # Laguna -> IE4000: NetId 1 and PRP trailer popped by IE4000.
                netid = 1
                prp = ""
            end
            pathid = (netid << 1)
            cmd += " htag pathid #{pathid} size #{len} seqn #{seqn}"
            cmd += (f_end + prp)

            # Frame f3 (Rx from IE4000 HSR port B)
            pathid += 1
            cmd += (" name f3" + f_base)
            cmd += " htag pathid #{pathid} size #{len} seqn #{seqn}"
            cmd += (f_end + prp)
        end

        idx_list.each do |idx|
            name = $ts.pc.p[idx]
            if (idx == idx_tx)
                cmd += " tx #{name} name f1"
            else
                cmd += " rx #{name} name "
                cmd += ((hsr_prp and (idx_tx/2) != (idx/2)) ? (idx == 3 ? "f3" : "f2") : "f1")
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
