#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_host   = 1
$idx_router = 2
$idx_npi    = 3

test "conf" do
    t_i("MLD registration")
    queue = 7
    conf = $ts.dut.call("mesa_packet_rx_conf_get")
    conf["queue"][queue]["npi"]["enable"] = true
    conf["reg"]["mld_cpu_only"] = true
    conf["map"]["igmp_queue"] = queue
    $ts.dut.call("mesa_packet_rx_conf_set", conf)

    t_i("NPI port")
    conf = $ts.dut.call("mesa_npi_conf_get")
    conf["enable"] = true
    conf["port_no"] = $ts.dut.port_list[$idx_npi]
    $ts.dut.call("mesa_npi_conf_set", conf)

    t_i("IPv6 MC flood members")
    $ts.dut.call("mesa_ipv6_mc_flood_members_set", port_idx_list_str([$idx_router]))

    t_i("MAC address entry")
    entry = {
        vid_mac: { vid: 1, mac: { addr: [0x33,0x33,0x02,0x03,0x04,0x05] } },
        destination: port_idx_list_str([$idx_host]),
        copy_to_cpu: false,
        copy_to_cpu_smac: false,
        locked: true,
        index_table: false,
        aged: false,
        cpu_queue: 0,
    }
    $ts.dut.call("mesa_mac_table_add", entry)
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    idx_tx = 0

    t_i("MLD redirect")
    f1 = "eth dmac 33:33:05:06:07:08 smac 00:00:00:00:00:0a"
    f1 += " ipv6 dip ff00::0506:0708 next 0"                  # Hop-by-Hop options header
    f1 += (" data hex 3a02050200000100" + "8f00000000000000") # ICMPv6 and MLDv2 Report message
    f2 = cmd_rx_ifh_push({port_idx: idx_tx})
    f2 += " #{f1}"
    cmd = "sudo ef name f1 #{f1} name f2 #{f2}"
    cmd += " tx #{$ts.pc.p[idx_tx]} name f1"
    cmd += " rx #{$ts.pc.p[$idx_npi]} name f2"
    $ts.pc.run(cmd)

    t_i("IPv6 MC flooding")
    cmd = "eth dmac 33:33:05:06:07:08 smac 00:00:00:00:00:0a"
    cmd += " ipv6 dip ff00::0506:0708 udp"
    run_ef_tx_rx_cmd($ts, idx_tx, [$idx_router], cmd)

    t_i("IPv6 MC forwarding")
    cmd = "eth dmac 33:33:02:03:04:05 smac 00:00:00:00:00:0a"
    cmd += " ipv6 dip ff00::0203:0405 udp"
    run_ef_tx_rx_cmd($ts, idx_tx, [$idx_host], cmd)
end
