#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

test "conf" do
    t_i("Set VLAN port configuration")
    $ts.dut.port_list.each do |port|
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
        conf["untagged_vid"] = 0
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end

    t_i("Enable PCP classification")
    $ts.dut.port_list.each do |port|
        conf = $ts.dut.call("mesa_qos_port_conf_get", port)
        conf["tag"]["class_enable"] = true
        for pcp in 0..7
            conf["tag"]["pcp_dei_map"][pcp][0]["prio"] = pcp
        end
        $ts.dut.call("mesa_qos_port_conf_set", port, conf)
    end
end

#---------- Frame testing -----------------------------------------------------

def check_cnt(port, i, name, cnt, exp, prio = 8)
    val = cnt[name]
    if (prio < 8)
        name = name + "[#{prio}]"
    end
    if (i == 1)
        # Counter has been cleared, expect zero value
        exp = 0
    end
    msg = "port #{port}, #{name}, expected: #{exp}, value: #{val}"
    if (exp == val)
        t_i(msg)
    else
        t_e(msg)
    end
end

def check_rmon_cnt(port, i, name, cnt, exp, dir = 3)
    rx = (port == $ts.dut.port_list[0])
    rmon = cnt["rmon"]
    name = "etherStats" + name
    if ((dir & 1) != 0)
        check_cnt(port, i, "rx_#{name}", rmon, rx ? exp : 0)
    end
    if ((dir & 2) != 0)
        check_cnt(port, i, "tx_#{name}", rmon, rx ? 0 : exp)
    end
end

def check_ifgrp_cnt(port, i, name, cnt, exp)
    rx = (port == $ts.dut.port_list[0])
    ifgrp = cnt["if_group"]
    check_cnt(port, i, "ifIn#{name}", ifgrp, rx ? exp : 0)
    check_cnt(port, i, "ifOut#{name}", ifgrp, rx ? 0 : exp)
end

def check_prio_cnt(port, i, prio, cnt, exp)
    rx = (port == $ts.dut.port_list[0])
    pcnt = cnt["prio"][prio]
    check_cnt(port, i, "rx", pcnt, rx ? exp : 0, prio)
    check_cnt(port, i, "tx", pcnt, rx ? 0 : exp, prio)
end

test "frame-io" do
    # Frame table
    frame_table = [ { cnt: 1, dmac: "00:00:00:00:00:0a", pcp: 0, size: 64 },
                    { cnt: 2, dmac: "00:00:00:00:00:0a", pcp: 1, size: 65 },
                    { cnt: 3, dmac: "01:00:00:00:00:00", pcp: 2, size: 128 },
                    { cnt: 4, dmac: "01:00:00:00:00:00", pcp: 3, size: 256 },
                    { cnt: 5, dmac: "01:00:00:00:00:00", pcp: 4, size: 512 },
                    { cnt: 6, dmac: "ff:ff:ff:ff:ff:ff", pcp: 5, size: 1024 },
                    { cnt: 7, dmac: "ff:ff:ff:ff:ff:ff", pcp: 6, size: 1518 },
                    { cnt: 8, dmac: "ff:ff:ff:ff:ff:ff", pcp: 7, size: 1518 } ]

    # Initialize counters
    cnt_octets = 0
    cnt_uc = 0
    cnt_mc = 0
    cnt_bc = 0
    cnt_64 = 0
    cnt_65 = 0
    cnt_128 = 0
    cnt_256 = 0
    cnt_512 = 0
    cnt_1024 = 0
    cnt_prio = []
    for i in 0..7
        cnt_prio[i] = 0
    end
    $ts.dut.run "mesa-cmd port statis clear"
    # Tx frames on port 0, expect on all other ports
    idx_tx = 0
    frame_table.each do |frame_entry|
        dmac = frame_entry[:dmac]
        pcp = frame_entry[:pcp]
        size = frame_entry[:size]

        cmd = "sudo ef tx #{$ts.pc.p[idx_tx]} eth dmac #{dmac}"
        cmd += cmd_tag_push({tpid: 0x8100, vid: 1, pcp: pcp})
        # Adjust data length for length MAC header, tag and FCS
        cmd += " data pattern cnt #{size - 14 - 4 - 4}"

        for i in 1..frame_entry[:cnt]
            # Send frames
            $ts.pc.run(cmd)

            # Calculate counters
            cnt_octets += size
            if (dmac[1] == "f")
                cnt_bc += 1
            elsif (dmac[1] == "1")
                cnt_mc += 1
            else
                cnt_uc += 1
            end
            if (size < 65)
                cnt_64 += 1
            elsif (size < 128)
                cnt_65 += 1
            elsif (size < 256)
                cnt_128 += 1
            elsif (size < 512)
                cnt_256 += 1
            elsif (size < 1024)
                cnt_512 += 1
            else
                cnt_1024 += 1
            end
            cnt_prio[pcp] += 1
        end
    end

    $ts.dut.port_list.each do |port|
        for i in 0..1
            cnt = $ts.dut.call("mesa_port_counters_get", port)
            if (i == 0)
                $ts.dut.call("mesa_port_counters_clear", port)
            end

            test "rmon counters" do
                # Check RMON counters
                check_rmon_cnt(port, i, "DropEvents", cnt, 0)
                check_rmon_cnt(port, i, "Octets", cnt, cnt_octets)
                check_rmon_cnt(port, i, "Pkts", cnt, cnt_uc + cnt_mc + cnt_bc)
                check_rmon_cnt(port, i, "BroadcastPkts", cnt, cnt_bc)
                check_rmon_cnt(port, i, "MulticastPkts", cnt, cnt_mc)
                check_rmon_cnt(port, i, "CRCAlignErrors", cnt, 0, 1)
                check_rmon_cnt(port, i, "UndersizePkts", cnt, 0, 1)
                check_rmon_cnt(port, i, "OversizePkts", cnt, 0, 1)
                check_rmon_cnt(port, i, "Fragments", cnt, 0, 1)
                check_rmon_cnt(port, i, "Jabbers", cnt, 0, 1)
                check_rmon_cnt(port, i, "Collisions", cnt, 0, 2)
                check_rmon_cnt(port, i, "Pkts64Octets", cnt, cnt_64)
                check_rmon_cnt(port, i, "Pkts65to127Octets", cnt, cnt_65)
                check_rmon_cnt(port, i, "Pkts128to255Octets", cnt, cnt_128)
                check_rmon_cnt(port, i, "Pkts256to511Octets", cnt, cnt_256)
                check_rmon_cnt(port, i, "Pkts512to1023Octets", cnt, cnt_512)
                check_rmon_cnt(port, i, "Pkts1024to1518Octets", cnt, cnt_1024)
                check_rmon_cnt(port, i, "Pkts1519toMaxOctets", cnt, 0)
            end

            test "ifgrp counters" do
                # Check Interface Group counters
                check_ifgrp_cnt(port, i, "Octets", cnt, cnt_octets)
                check_ifgrp_cnt(port, i, "UcastPkts", cnt, cnt_uc)
                check_ifgrp_cnt(port, i, "MulticastPkts", cnt, cnt_mc)
                check_ifgrp_cnt(port, i, "BroadcastPkts", cnt, cnt_bc)
                check_ifgrp_cnt(port, i, "NUcastPkts", cnt, cnt_mc + cnt_bc)
                check_ifgrp_cnt(port, i, "Discards", cnt, 0)
                check_ifgrp_cnt(port, i, "Errors", cnt, 0)
            end
            # Check priority counters
            test "prio counters" do
                for j in 0..7
                    check_prio_cnt(port, i, j, cnt, cnt_prio[j])
                end
            end
        end
    end
end
