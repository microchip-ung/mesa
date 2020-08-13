#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")
#---------- Configuration -----------------------------------------------------

# Two VLAN are used, only the second is isolated
$vid_list = [100, 200]

test "conf" do
    test "All ports are C-ports" do
        $ts.dut.port_list.each do |port|
            conf = $ts.dut.call "mesa_vlan_port_conf_get", port
            conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
            $ts.dut.call "mesa_vlan_port_conf_set", port, conf
        end
    end

    test "Make egress port member of VLANs" do
        $vid_list.each do |vid|
            $ts.dut.call "mesa_vlan_port_members_set", vid, $ts.dut.p.join(",")
        end
    end

    test "The second VLAN is isolated" do
        $ts.dut.call "mesa_isolated_vlan_set", $vid_list[1], true
    end

    test "The first two ports are isolated" do
        $ts.dut.call "mesa_isolated_port_members_set", "#{$ts.dut.p[0]},#{$ts.dut.p[1]}"
    end
end

test "frame-io" do
    $vid_list.each_with_index do |vid, idx|
        $ts.dut.p.each_index do |idx_tx|
            idx_list = []
            $ts.pc.p.each_index do |idx_rx|
                # Forward if VLAN or ingress port or egress port is not isolated
                if (idx_rx != idx_tx and (idx == 0 or idx_tx > 1 or idx_rx > 1))
                    idx_list << idx_rx
                end
            end

            cmd = "sudo ef name f1 eth ctag vid #{vid} et 0xaaaa data pattern cnt 64"
            cmd += " tx #{$ts.pc.p[idx_tx]} name f1"
            cmd += idx_list.map{|x| " rx #{$ts.pc.p[x]} name f1"}.join(" ")
            $ts.pc.run cmd
        end
    end
end

