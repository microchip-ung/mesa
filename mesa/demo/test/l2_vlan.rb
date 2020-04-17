#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

# VLANs used in this test
$port_list = $ts.dut.port_list
$vid_list = [ 100, 200 ]
$vid_members = [[0, 2, 3],
               [1, 2, 3]]
$s_etype = 0x9100

# VLAN port configuration table
$conf_table =
    [
     {
         # Unaware port
         port_type: "MESA_VLAN_PORT_TYPE_UNAWARE",
         tpid: 0,
         pvid: $vid_list[0],
         uvid: 4096, # Untag all VLANs
         frame_type: "MESA_VLAN_FRAME_ALL"
     },
     {
         # Access, C-port
         port_type: "MESA_VLAN_PORT_TYPE_C",
         tpid: 0x8100,
         pvid: $vid_list[1],
         uvid: $vid_list[1],
         frame_type: "MESA_VLAN_FRAME_UNTAGGED"
     },
     {
         # Trunk, S-port
         port_type: "MESA_VLAN_PORT_TYPE_S",
         tpid: 0x88a8,
         pvid: $vid_list[0],
         uvid: 0, # Tag all VLANs
         frame_type: "MESA_VLAN_FRAME_TAGGED"
     },
     {
         # Hybrid, S-custom port
         port_type: "MESA_VLAN_PORT_TYPE_S_CUSTOM",
         tpid: $s_etype,
         pvid: $vid_list[1],
         uvid: $vid_list[1],
         frame_type: "MESA_VLAN_FRAME_ALL"
     }
    ]
              
test "conf" do
    t_i("Set global Ethernet Type for S-custom ports");
    conf = $ts.dut.call("mesa_vlan_conf_get")
    conf["s_etype"] = $s_etype
    $ts.dut.call("mesa_vlan_conf_set", conf)

    t_i("Set VLAN port configuration")
    $port_list.each_with_index do |port, idx|
        entry = $conf_table[idx]
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = entry[:port_type]
        conf["pvid"] = entry[:pvid]
        conf["untagged_vid"] = entry[:uvid]
        conf["frame_type"] = entry[:frame_type]
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end

    $ts.dut.call("mesa_vlan_port_members_set", 1, "")
    $vid_list.each_with_index do |vid, idx|
        $ts.dut.call("mesa_vlan_port_members_set", vid, port_idx_list_str($vid_members[idx]))
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    # Tag table
    tag_table = [ { tpid: 0x0000, vid: 0 },
                  { tpid: 0x8100, vid: 0 },
                  { tpid: 0x8100, vid: $vid_list[0] },
                  { tpid: 0x8100, vid: $vid_list[1] },
                  { tpid: 0x88a8, vid: 0 },
                  { tpid: 0x88a8, vid: $vid_list[0] },
                  { tpid: 0x88a8, vid: $vid_list[1] },
                  { tpid: 0x9100, vid: 0 },
                  { tpid: 0x9100, vid: $vid_list[0] },
                  { tpid: 0x9100, vid: $vid_list[1] }]

    # Caracal/Serval are not TPID aware
    tpid_unaware = (cap_get("L2_TPID_AWARE") == 0)

    # Tx frames for each host port
    tag_table.each do |tag|
        tpid = tag[:tpid]
        vid = tag[:vid]

        $ts.dut.p.each_index do |idx_tx|
            # Determine if frame is classified as tagged
            # TPID unaware switches accept all TPIDs in the VLAN classification
            conf = $conf_table[idx_tx]
            tagged = (conf[:tpid] != 0 and tpid != 0 and
                      (tpid == conf[:tpid] or tpid_unaware))

            # Determine classified VID and tag popping
            if (tagged and vid != 0)
                # VLAN-tagged, use frame VID
                cl_vid = vid
            else
                # Untagged or prority-tagged, use PVID
                cl_vid = conf[:pvid]
            end
            pop = tagged

            # Frame type check
            if (tagged and tpid_unaware and tpid != conf[:tpid] and
                (conf[:tpid] == 0x8100 or tpid == 0x8100))
                # TPID unaware switches distiguish between 0x8100 and 0x88a8/custom_etype
                tagged = false
            end
            case conf[:frame_type]
            when "MESA_VLAN_FRAME_TAGGED"
                # Allow only VLAN-tagged frames
                fwd = (tagged and vid != 0)
            when "MESA_VLAN_FRAME_UNTAGGED"
                # Allow only untagged and priority-tagged frames
                fwd = (!tagged or vid == 0)
            else
                # Allow all frames
                fwd = true
            end

            # Rx frame per egress port: Determine tag pushing
            cmd = "sudo ef"
            cmd_end = ""
            member_list = $vid_members[$vid_list.find_index(cl_vid)]
            $ts.dut.p.each_index do |idx_rx|
                conf = $conf_table[idx_rx]
                f = nil
                dir = "rx"
                if (idx_rx == idx_tx)
                    # Tx frame
                    dir = "tx"
                    f = cmd_tag_push(tag)
                elsif (fwd and member_list.include?idx_rx)
                    # Rx frame
                    f = ""
                    if (conf[:uvid] != 4096 and conf[:uvid] != cl_vid)
                        # Tag pushed
                        f += cmd_tag_push({tpid: (conf[:tpid] == 0 ? 0x8100 : conf[:tpid]), vid: cl_vid})
                    end
                    if (!pop)
                        # Original tag not popped
                        f += cmd_tag_push(tag)
                    end
                end
                cmd_end += " #{dir} #{$ts.pc.p[idx_rx]}"
                unless (f.nil?)
                    cmd_name = " name f#{idx_rx}"
                    cmd += cmd_name
                    cmd += " eth"
                    cmd += f
                    cmd += " data pattern cnt 64"
                    cmd_end += cmd_name
                end
            end
            $ts.pc.run(cmd + cmd_end)
        end
    end
end
