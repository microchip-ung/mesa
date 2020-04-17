#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$vid_list = [ 10, 20, 30]

test "conf" do
    port_list = $ts.dut.port_list

    t_i("Set VLAN port configuration")
    port_list.each_with_index do |port, idx|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["pvid"] = $vid_list[idx & 1]
        conf["untagged_vid"] = (idx < 2 ? 4096 : 0)
        conf["frame_type"] = ("MESA_VLAN_FRAME_" + (idx < 2 ? "UNTAGGED" : "TAGGED"))
        conf["ingress_filter"] = false
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end

    t_i("Set VLAN memberships")
    $vid_list.each_with_index do |vid, idx|
        str = ""
        if (idx == 0)
            str += "#{port_list[0]},"
        elsif (idx == 1)
            str += "#{port_list[1]},"
        end
        str += "#{port_list[2]},#{port_list[3]}"
        $ts.dut.call("mesa_vlan_port_members_set", vid, str)
    end

    t_i("Set VLAN translation group configuration")
    port_list.each do |port|
        conf = {
            group_id: (port + 1),
            port_list: "#{port}"
        }
        $ts.dut.call("mesa_vlan_trans_group_to_port_set", conf)
    end
    
    t_i("Add VLAN translations")
    conf_table = 
        [
         {
             group_id: (port_list[2] + 1),
             vid: $vid_list[1],
             trans_vid: $vid_list[0],
             dir: "MESA_VLAN_TRANS_DIR_BOTH"
         },
         {
             group_id: (port_list[3] + 1),
             vid: $vid_list[2],
             trans_vid: $vid_list[1],
             dir: "MESA_VLAN_TRANS_DIR_BOTH"
         }
        ]
    conf_table.each do |conf|
        $ts.dut.call("mesa_vlan_trans_group_add", conf)
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    # Frame table
    tag_table = [ { tpid: 0x0000, vid: 0 },
                  { tpid: 0x8100, vid: $vid_list[0] },
                  { tpid: 0x8100, vid: $vid_list[1] },
                  { tpid: 0x8100, vid: $vid_list[2] } ]

    # Tx frames for each host port
    tag_table.each do |tag|
        tpid = tag[:tpid]
        vid = tag[:vid]
        $ts.dut.p.each_index do |idx_tx|
            # Calculate forwarding
            if (tpid == 0)
                # Untagged frame, only accepted on access ports
                fwd = (idx_tx < 2)
                cl_vid = $vid_list[idx_tx]
            else
                # Tagged frame, only accepted on trunk ports
                fwd = (idx_tx > 1)
                if (idx_tx == 2 and vid == $vid_list[1])
                    cl_vid = $vid_list[0]
                elsif (idx_tx == 3 and vid == $vid_list[2])
                    cl_vid = $vid_list[1]
                else
                    cl_vid = vid
                end
            end
            cmd = "sudo ef"
            cmd_end = ""
            $ts.dut.p.each_index do |idx_rx|
                dir = "rx"
                if (idx_rx == idx_tx)
                    # Tx frame
                    dir = "tx"
                    f = cmd_tag_push(tag)
                elsif (idx_rx < 2 and cl_vid != $vid_list[idx_rx])
                    # Access port only member of port VLAN
                    f = nil
                elsif (fwd and idx_rx != idx_tx)
                    # Rx frame
                    f = ""
                    if (idx_rx > 1)
                        # Tag pushed
                        ptag = {tpid: 0x8100}
                        if (idx_rx == 2 and cl_vid == $vid_list[0])
                            ptag[:vid] = $vid_list[1]
                        elsif (idx_rx == 3 and cl_vid == $vid_list[1])
                            ptag[:vid] = $vid_list[2]
                        else
                            ptag[:vid] = cl_vid
                        end
                        f = cmd_tag_push(ptag)
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
