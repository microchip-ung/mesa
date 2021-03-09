#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check SSM supported
cap_check_exit("L2_IPV4_MC_SIP")

#---------- Configuration -----------------------------------------------------

$vid_list = [10, 20]
$idx_router = 3

test "conf" do
    t_i("Set VLAN port configuration")
    $ts.dut.port_list.each_with_index do |port, idx|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["pvid"] = $vid_list[idx == 0 ? 0 : 1]
        conf["untagged_vid"] = 4096
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end

    t_i("Set VLAN membership")
    $vid_list.each do |vid|
        $ts.dut.call("mesa_vlan_port_members_set", vid, $ts.dut.p.join(","))
    end

    t_i("Set flood members")
    port_list = "#{$ts.dut.p[$idx_router]}"
    $ts.dut.call("mesa_ipv4_mc_flood_members_set", port_list);
    $ts.dut.call("mesa_ipv6_mc_flood_members_set", port_list);
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    conf_table =
        [
         {vid: $vid_list[0], sip: "1.2.3.4", dip: "225.2.3.4", port_list: [1,3]},
         {vid: $vid_list[1], sip: "0.0.0.0", dip: "239.7.8.9", port_list: [2,3]},
         {vid: $vid_list[1], sip: "2.3.4.5", dip: "239.7.8.9", port_list: [0,3]},
         {vid: $vid_list[0], sip: "2000::0102:0304", dip: "ff00::0102:0304", port_list: [1,3]},
         {vid: $vid_list[1], sip: "::",              dip: "ff00::ffff:ffff", port_list: [2,3]},
         {vid: $vid_list[1], sip: "2000::0203:0405", dip: "ff00::ffff:ffff", port_list: [0,3]},
        ]

    flood = [$idx_router]
    frame_table =
        [
         {txt: "IPv4 SSM match", idx_tx: 0, idx_rx: [1,3], dmac: "01:00:5e:02:03:04", cmd: "ipv4 sip 1.2.3.4 dip 225.2.3.4"},
         {txt: "SIP mismatch", idx_tx: 0,   idx_rx: flood, dmac: "01:00:5e:02:03:04", cmd: "ipv4 sip 1.2.3.5 dip 225.2.3.4"},
         {txt: "DIP mismatch", idx_tx: 0,   idx_rx: flood, dmac: "01:00:5e:02:03:05", cmd: "ipv4 sip 1.2.3.4 dip 225.2.3.5"},
         {txt: "IPv4 ASM match", idx_tx: 1, idx_rx: [2,3], dmac: "01:00:5e:07:08:09", cmd: "ipv4 sip 2.3.4.6 dip 239.7.8.9"},
         {txt: "IPv4 SSM match", idx_tx: 1, idx_rx: [0,3], dmac: "01:00:5e:07:08:09", cmd: "ipv4 sip 2.3.4.5 dip 239.7.8.9"},
         {txt: "IPv6 SSM match", idx_tx: 0, idx_rx: [1,3], dmac: "33:33:01:02:03:04", cmd: "ipv6 sip 2000::0102:0304 dip ff00::0102:0304"},
         {txt: "SIP mismatch", idx_tx: 0,   idx_rx: flood, dmac: "33:33:01:02:03:04", cmd: "ipv6 sip 2000::0102:0305 dip ff00::0102:0304"},
         {txt: "DIP mismatch", idx_tx: 0,   idx_rx: flood, dmac: "33:33:01:02:03:05", cmd: "ipv6 sip 2000::0102:0304 dip ff00::0102:0305"},
         {txt: "IPv6 ASM match", idx_tx: 1, idx_rx: [2,3], dmac: "33:33:ff:ff:ff:ff", cmd: "ipv6 sip 2000::0203:0406 dip ff00::ffff:ffff"},
         {txt: "IPv6 SSM match", idx_tx: 1, idx_rx: [0,3], dmac: "33:33:ff:ff:ff:ff", cmd: "ipv6 sip 2000::0203:0405 dip ff00::ffff:ffff"},
        ]

    cap_ipv6 = cap_get("L2_IPV6_MC_SIP")

    # Two iterations are done
    # 0: Add entries, expect forwarding accordingly
    # 1: Delete entries again, expect flooding
    [0,1].each do |itr|
        conf_table.each do |conf|
            port_list = port_idx_list_str(conf[:port_list])
            vid = conf[:vid]
            sip = conf[:sip]
            dip = conf[:dip]
            if ((sip.include? ":") and cap_ipv6 == 0)
                next
            end
            t_i("vid: #{vid}, sip: #{sip}, dip: #{dip}")
            if (sip.include? ".")
                sip = ipv4_str2int(sip)
                dip = ipv4_str2int(dip)
                if (itr == 1)
                    $ts.dut.call("mesa_ipv4_mc_del", vid, sip, dip)
                else
                    $ts.dut.call("mesa_ipv4_mc_add", vid, sip, dip, port_list)
                end
            else
                sip = {addr: ipv6_str2arr(sip)}
                dip = {addr: ipv6_str2arr(dip)}
                if (itr == 1)
                    $ts.dut.call("mesa_ipv6_mc_del", vid, sip, dip)
                else
                    $ts.dut.call("mesa_ipv6_mc_add", vid, sip, dip, port_list)
                end
            end
        end

        frame_table.each do |frame|
            cmd = frame[:cmd]
            if ((cmd.include? "ipv6") and cap_ipv6 == 0)
                next
            end
            t_i("#{frame[:txt]}, #{itr == 0 ? "forward" : "flood"}")
            cmd = ("eth dmac #{frame[:dmac]} smac 00:00:00:00:00:0a " + cmd)
            idx_tx = frame[:idx_tx]
            idx_list = (itr == 0 ? frame[:idx_rx] : flood)
            run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
        end
    end
end
