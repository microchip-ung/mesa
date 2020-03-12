#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$port_idx_ingress = 0 # Port index for ingress port
$port_idx_egress  = 3 # Port index for egress port, tagging all frames

$vid_list = [10, 20, 30]
$vid_max = 32

test "conf" do
    t_i("Set egress port to tag all frames")
    port = $ts.dut.port_list[$port_idx_egress]
    conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
    conf["untagged_vid"] = 0
    $ts.dut.call("mesa_vlan_port_conf_set", port, conf)

    t_i("Make egress port member of VLANs")
    $vid_list.each do |vid|
        $ts.dut.call("mesa_vlan_port_members_set", vid, "#{port}")
    end
    $ts.dut.call("mesa_vlan_port_members_set", $vid_max, "#{port}")
end

#---------- Frame testing -----------------------------------------------------

def vcl_frame_test(vid)
    # Tx untagged frame f1, Rx tagged frame f2
    f_base = " eth"
    f_end = " data pattern cnt 64"
    cmd = "sudo ef name f1" + f_base + f_end
    cmd += " name f2" + f_base + cmd_tag_push({tpid: 0x8100, vid: vid}) + f_end

    $ts.dut.p.each_index do |idx_rx|
        dir = "rx"
        f = nil
        if (idx_rx == $port_idx_ingress)
            # Tx frame f1
            dir = "tx"
            f = "f1"
        elsif (idx_rx == $port_idx_egress)
            # Rx frame f2
            dir = "rx"
            f = "f2"
        end
        cmd += " #{dir} #{$ts.pc.p[idx_rx]}"
        unless (f.nil?)
            cmd += " name #{f}"
        end
    end
    t_i("Classified VID: #{vid}")
    $ts.pc.run(cmd)
end

def vce_vid_add(vid, vid_next)
    conf = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
    conf["id"] = vid
    conf["key"]["port_list"] = "#{$ts.dut.port_list[$port_idx_ingress]}"
    conf["action"]["vid"] = vid
    $ts.dut.call("mesa_vce_add", vid_next, conf)
end

def vce_vid_del(vid)
    $ts.dut.call("mesa_vce_del", vid)
end

test "frame-io" do
    # Add VCE for each VID
    $vid_list.each do |vid|
        vce_vid_add(vid, 0)
    end

    # Check that the first VID is matched
    vcl_frame_test($vid_list[0])

    # Delete the VCE for the first VID and check that the next VID is matched
    vce_vid_del($vid_list[0])
    vcl_frame_test($vid_list[1])
    
    # Move the VCE for the last VID up and check that it is matched
    vce_vid_add($vid_list[2], $vid_list[1])
    vcl_frame_test($vid_list[2])
    
    # Delete the VCE for the last VID and check that the next VID is matched
    vce_vid_del($vid_list[2])
    vcl_frame_test($vid_list[1])
    
    # Delete the last VCE
    vce_vid_del($vid_list[1])

    # Add VCEs and delete them
    for i in 0..1
        for vid in 1..$vid_max
            if (i == 0)
                vce_vid_add(vid, 0)
            else
                if (vid == $vid_max)
                    # Check the last VID before deleting it
                    vcl_frame_test(vid)
                end
                vce_vid_del(vid)
            end
        end
    end
end
