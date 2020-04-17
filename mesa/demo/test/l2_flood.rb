#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_uc_flood      = [1, 2]
$idx_mc_flood      = [1, 3]
$idx_ipv4_mc_flood = [2, 3]
$idx_ipv6_mc_flood = [3]

test "conf" do
    # Configure for uc flood test
    $ts.dut.call "mesa_uc_flood_members_set", "#{$ts.dut.p[1]},#{$ts.dut.p[2]}"

    #Configure for mc flood test
    $ts.dut.call "mesa_mc_flood_members_set",  "#{$ts.dut.p[1]},#{$ts.dut.p[3]}"

    #Configure for IPv4 mc flood test
    $ts.dut.call "mesa_ipv4_mc_flood_members_set",  "#{$ts.dut.p[2]},#{$ts.dut.p[3]}"

    #Configure for IPv6 mc flood test
    $ts.dut.call "mesa_ipv6_mc_flood_members_set",  "#{$ts.dut.p[3]}"
end


#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    idx_tx = 0

    test("UC flood") do
        run_ef_tx_rx_cmd($ts, idx_tx, $idx_uc_flood, "eth dmac 00:11:22:33:44:55 smac 0xa ctag et 0xaaaa data pattern cnt 64")
    end

    test("MC flood") do
        run_ef_tx_rx_cmd($ts, idx_tx, $idx_mc_flood, "eth dmac 11:22:33:44:55:66 smac 0xa ctag et 0xaaaa data pattern cnt 64")
    end

    test("IPv4 MC data flood") do
        run_ef_tx_rx_cmd($ts, idx_tx, $idx_ipv4_mc_flood, "eth dmac 01:00:5e:01:02:03 ipv4 dip 225.1.2.3")
    end

    test("IPv4 MC control flood") do
        run_ef_tx_rx_cmd($ts, idx_tx, $idx_mc_flood, "eth dmac 01:00:5e:00:00:07 ipv4 dip 224.0.0.7")
    end

    test("IPv6 MC data flood") do
        run_ef_tx_rx_cmd($ts, idx_tx, $idx_ipv6_mc_flood, "eth dmac 33:33:01:02:03:04 ipv6 dip ff00::0102:0304")
    end

    test("IPv6 MC control flood") do
        f = "eth dmac 33:33:01:02:03:04 ipv6 dip ff02::0102:0304"

        $ts.dut.call "mesa_ipv6_mc_ctrl_flood_set", false
        run_ef_tx_rx_cmd($ts, idx_tx, $idx_mc_flood, f)

        $ts.dut.call "mesa_ipv6_mc_ctrl_flood_set", true
        run_ef_tx_rx_cmd($ts, idx_tx, $idx_ipv6_mc_flood, f)
    end
end

