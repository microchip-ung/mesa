#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Frame testing -----------------------------------------------------

$aggr_no = 1
test "aggr-mode" do
    aggr_fld_table = 
        [ { fld: "smac_enable", smac: ["00:00:00:00:00:04","00:00:00:00:00:05"] },
          { fld: "dmac_enable", dmac: ["00:00:00:00:00:06","00:00:00:00:00:07"] },
          { fld: "sip_dip_enable", sip: ["3.3.3.2", "3.3.3.3"] },
          { fld: "sip_dip_enable", dip: ["4.4.4.4", "4.4.4.5"] },
          { fld: "sport_dport_enable", sport: [16, 17] },
          { fld: "sport_dport_enable", dport: [18, 19] } ]

    # Port index 2 and 3 are aggregated
    $ts.dut.call("mesa_aggr_port_members_set", $aggr_no, port_idx_list_str([2, 3]))

    aggr_fld_table.each do |a|
        [false, true].each do |enabled|
            fld = a[:fld]
            test "aggr-mode, #{fld} = #{enabled}" do
                conf = $ts.dut.call("mesa_aggr_mode_get")
                conf[fld] = enabled
                $ts.dut.call("mesa_aggr_mode_set", conf)
                $ts.dut.p.each_index do |idx_tx|
                    # Send two frames with different aggregation keys
                    base = ethtool_stat($ts)
                    for j in 0..1
                        cmd = "sudo ef tx #{$ts.pc.p[idx_tx]} eth"
                        if (a.key?:dmac)
                            cmd += " dmac #{a[:dmac][j]}"
                        end
                        if (a.key?:smac)
                            cmd += " smac #{a[:smac][j]}"
                        end
                        cmd += " ipv4"
                        if (a.key?:sip)
                            cmd += " sip #{a[:sip][j]}"
                        end
                        if (a.key?:dip)
                            cmd += " dip #{a[:dip][j]}"
                        end
                        cmd += " udp"
                        if (a.key?:sport)
                            cmd += " sport #{a[:sport][j]}"
                        end
                        if (a.key?:dport)
                            cmd += " dport #{a[:dport][j]}"
                        end
                        $ts.pc.run(cmd)
                    end
                    base, diff = ethtool_stat($ts, base)

                    # Check switch Tx (host Rx) counters for each interface
                    prev = 0
                    exp = {}
                    $ts.dut.port_list.each_with_index do |port, idx_rx|
                        name = "#{$ts.pc.p[idx_rx]}"
                        val = diff[name]["rx"]["packets"]
                        cnt = (idx_rx == idx_tx ? 0 :             # Not forwarding back
                               idx_rx < 2 ? 2 :                   # Egress port not aggregated
                               idx_tx > 1 ? 0 :                   # Egress and ingress port aggregated
                               enabled ? 1 :                      # Aggregation field enabled, one frame for each port
                               idx_rx == 2 ? (val == 0 ? 0 : 2) : # 0 frames on one port, 2 frames on the other port
                               prev == 0 ? 2 : 0)
                        exp["#{name}-rx"] = cnt
                        exp["#{name}-tx"] = (idx_rx == idx_tx ? 2 : 0)
                        prev = val
                    end
                    eval_stats(diff, $ts.pc.p, exp)
                end
            end
        end
    end
end

test "aggr-port" do
    aggr_table =
        [ [0,3],
          [1,2,3],
          [0,1,2,3],
          [] ]
    aggr_table.each do |a|
        str = port_idx_list_str(a)
        test "aggr-ports: #{str}" do
            $ts.dut.call("mesa_aggr_port_members_set", $aggr_no, str)
            $ts.dut.port_list.each_index do |idx_tx|
                base = ethtool_stat($ts)
                $ts.pc.run("sudo ef tx #{$ts.pc.p[idx_tx]} eth")
                base, diff = ethtool_stat($ts, base)
                cnt = 0
                $ts.dut.port_list.each_with_index do |port, idx_rx|
                    name = "#{$ts.pc.p[idx_rx]}"
                    val = diff[name]["rx"]["packets"]
                    if (a.include?idx_rx)
                        # Update aggregation counter
                        cnt += val
                    else
                        # Check non-aggregated port counter
                        exp = (idx_tx == idx_rx ? 0 : 1)
                        msg = "port #{port}, Tx expected: #{exp}, value: #{val}"
                        if (exp == val)
                            t_i(msg)
                        else
                            t_e(msg)
                        end
                    end
                end
                # Check aggregation counter
                exp = ((a.include?idx_tx or a.empty?) ? 0 : 1)
                msg = "aggr #{$aggr_no}, Tx expected: #{exp}, value: #{cnt}"
                if (exp == cnt)
                    t_i(msg)
                else
                    t_e(msg)
                end
            end
        end
    end
end
