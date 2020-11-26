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
    t_i("IGMP registration")
    queue = 7
    conf = $ts.dut.call("mesa_packet_rx_conf_get")
    conf["queue"][queue]["npi"]["enable"] = true
    conf["reg"]["igmp_cpu_only"] = true
    conf["map"]["igmp_queue"] = queue
    $ts.dut.call("mesa_packet_rx_conf_set", conf)

    t_i("NPI port")
    conf = $ts.dut.call("mesa_npi_conf_get")
    conf["enable"] = true
    conf["port_no"] = $ts.dut.port_list[$idx_npi]
    $ts.dut.call("mesa_npi_conf_set", conf)

    # IPv4 MC flood members
    $ts.dut.call("mesa_ipv4_mc_flood_members_set", port_idx_list_str([$idx_router]))

    # MAC address entry
    entry = {
        vid_mac: { vid: 1, mac: { addr: [0x01,0x00,0x5e,0x02,0x03,0x04] } },
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
    
    t_i("IGMP redirect")
    f1 = "eth dmac 01:00:5e:05:06:07 smac 00:00:00:00:00:0a"
    f1 += " ipv4 proto 2 dip 225.5.6.7 data pattern cnt 32"
    f2 = cmd_rx_ifh_push({port_idx: idx_tx})
    f2 += " #{f1}"
    cmd = "sudo ef name f1 #{f1} name f2 #{f2}"
    cmd += " tx #{$ts.pc.p[idx_tx]} name f1"
    cmd += " rx #{$ts.pc.p[$idx_npi]} name f2"
    $ts.pc.run(cmd)

    t_i("IPv4 MC flooding")
    cmd = "eth dmac 01:00:5e:05:06:07 smac 00:00:00:00:00:0a"
    cmd += " ipv4 dip 225.5.6.7 udp"
    run_ef_tx_rx_cmd($ts, idx_tx, [$idx_router], cmd)

    t_i("IPv4 MC forwarding")
    cmd = "eth dmac 01:00:5e:02:03:04 smac 00:00:00:00:00:0a"
    cmd += " ipv4 dip 225.2.3.4 udp"
    run_ef_tx_rx_cmd($ts, idx_tx, [$idx_host], cmd)
end
