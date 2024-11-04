#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

# Test of IPv4/IPv6 UDP/TCP SPORT/DPORT range checkers.
# Loop iterations (for 8 range checkers):
# 0 : IPv4 UDP DPORT, range 1-2
# 1 : IPv4 TCP DPORT, range 1-2 (reuse)
# 2 : IPv4 UDP SPORT, range 1-3
# 3 : IPv4 TCP SPORT, range 1-3 (reuse)
# ...
# 14: IPv6 UDP SPORT, range 1-9
# 15: IPv6 TCP SPORT, range 1-9 (reuse)
# 16: IPv4 UDP DPORT, range 1-10 (no more range checkers)
# 17: IPv4 TCP DPORT, single value (no range checker needed)
# 18: IPv4 UDP SPORT, wildcard (no range checker needed)

range_cnt = (cap_get("SOC_FAMILY") == 10 ? 16 : 8)
ace_cnt = (2 * range_cnt + 3)
ace_cnt.times do |idx|
    id = (idx + 1)
    min = 1
    max = (2 + (idx / 2))
    if (id == (ace_cnt - 1))
        # Single value test
        min = 100
        max = 100
    end
    if (id == ace_cnt)
        # Wildcard value test
        min = 0
        max = 0xffff
    end
    ipv6 = (idx & 4 > 0)
    sport = (idx & 2 > 0)
    tcp = (idx & 1 > 0)
    txt = (ipv6 ? "IPv6 " : "IPv4 ")
    txt += (tcp ? "TCP " : "UDP ")
    txt += (sport ? "SPORT " : "DPORT ")
    txt += "#{min} - #{max}"

    test txt do
        # Add ACE
        ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_IPV" + (ipv6 ? "6" : "4"))
        ace["id"] = id
        idx_tx = 0
        ace["port_list"] = "#{$ts.dut.port_list[idx_tx]}"
        ip = (ipv6 ? "ipv6" : "ipv4")
        f = ace["frame"][ip]
        p = f["proto"]
        p["value"] = (tcp ? 6 : 17)
        p["mask"] = 0xff
        k = f[sport ? "sport" : "dport"]
        k["in_range"] = true
        k["low"] = min
        k["high"] = max
        ace["action"]["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
        if (id == (ace_cnt - 2))
            # No more range checkers, expect error
            $ts.dut.call_err("mesa_ace_add", 0, ace)
            next
        else
            $ts.dut.call("mesa_ace_add", 0, ace)
        end

        # Send matching frame
        cmd = "eth "
        cmd += ip
        cmd += (tcp ? " tcp" : " udp")
        cmd += (sport ? " sport" : " dport")
        cmd += " #{max}"
        run_ef_tx_rx_cmd($ts, idx_tx, [], cmd)

        # Check counter
        cnt = $ts.dut.call("mesa_ace_counter_get", id)
        check_counter("ace[#{id}]", cnt, 1)
    end
end

test_summary

test "dump" do
    #$ts.dut.run("mesa-cmd deb api ai acl")
end

