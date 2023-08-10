#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$ts = get_test_setup("mesa_pc_b2b_2x", {}, "", "loop")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5) or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")} (Lan966x) or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")} (Lan969x)")
    $cap_fpga = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_FPGA")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    $cap_port_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    loop_pair_check
    $loop_port0 = $ts.dut.looped_port_list[0]
    $loop_port1 = $ts.dut.looped_port_list[1]
end

loop_pair_check

$port0 = 0
$npi_port = 1
$cpu_queue = 7

$port_map = $ts.dut.call("mesa_port_map_get", $cap_port_cnt)

def tod_tx_fifo_test
    test "tod_tx_fifo_test" do

    # Update default ingress and egress latency in the API. This is based on register values potentially different after link up
    # Delay after call to mesa_ts_status_change should be smaller as the default delay (that is added) is calculated internally in the API
    # This is only the case the first run of the test after boot as this default delay is remembered in the API
    $ts.dut.call("mesa_ts_status_change", $loop_port0)
    $ts.dut.call("mesa_ts_status_change", $loop_port1)

    # age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    t_i ("Allocate a timestamp id")
    conf = {port_mask: 1<<$loop_port0, context: 0, cb: 0}
    idx0 = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)    # Just to make sure that the test is working with idx ather than 0
    idx = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    t_i ("Transmit a Two-Step SYNC frame into NPI port with the allocated timestamp id on NPI against loop port and receive again on NPI port")
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")
    frametx = tx_ifh_create($loop_port0, "MESA_PACKET_PTP_ACTION_TWO_STEP", idx["ts_id"]<<16) + frameHdrTx.dup + sync_pdu_create()
    framerx = rx_ifh_create($loop_port1) + frameHdrTx.dup + sync_pdu_rx_create()
    frame_tx(frametx, $npi_port, " ", " ", " ", framerx, 60)

    t_i "Calculate the IFH and decode it"
    pkts = $ts.pc.get_pcap "#{$ts.links[$npi_port][:pc]}.pcap"
    ifh = rx_ifh_extract(pkts[1])   # both transmitted and received frame is in 'pkts'
    meta = { no_wait: false, chip_no: 0, xtr_qu: 0, etype: 0, fcs: 0, sw_tstamp: { hw_cnt: 0 }, length: 0}
    $frame_info = $ts.dut.call("mesa_packet_rx_hdr_decode", meta, ifh)

    t_i ("Update the TX FIFO in AIL. This will cause callback to Jason with the TX timestamp")
    $ts.dut.call("mesa_tx_timestamp_update")

    # Get the TX timestamp. This is not a MESA API function, only a Jason implementation to get the TX timestamp delivered through callback
    ts_tx = $ts.dut.call("mesa_tx_timestamp_get")

    if ((ts_tx["id"] != idx["ts_id"]) || (ts_tx["ts_valid"] != true))
        t_e("Not the expected TX timestamp. ts_tx[id] = #{ts_tx["id"]}  idx[ts_id] = #{idx["ts_id"]}  ts_tx[ts_valid] = #{ts_tx["ts_valid"]}")
    end

    diff = 1000
    t_i ("difference between RX and TX timestamp  #{($frame_info["hw_tstamp"] - ts_tx["ts"])>>16}")
    if (($frame_info["hw_tstamp"] - ts_tx["ts"]) > (diff<<16))    #Experimental value of max diff ns difference between transmitting TC and received TC
        t_e("Not the expected difference between RX and TX timestamp. ts_tx[ts] = #{ts_tx["ts"]}  $frame_info[hw_tstamp] = #{$frame_info["hw_tstamp"]}  diff = #{($frame_info["hw_tstamp"] - ts_tx["ts"])>>16}")
    end

    # age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    # Allocate first timestamp id
    conf = {port_mask: 1<<$loop_port0, context: 0, cb: 0}
    idx1 = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    # Allocate second timestamp id
    idx2 = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    # Allocate third timestamp id
    idx3 = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    if ((idx2["ts_id"] != (idx1["ts_id"] + 1)) || (idx3["ts_id"] != (idx2["ts_id"] + 1)))
        t_e("Not the expected timestamp id's. idx1 = #{idx1["ts_id"]}  idx2 = #{idx2["ts_id"]}  idx3 = #{idx3["ts_id"]}")
    end

    # age out the allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    # Allocate timestamp id
    conf = {port_mask: 1<<$loop_port0, context: 0, cb: 0}
    idx = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    if (idx["ts_id"] != 0)
        t_e("After age Not the expected timestamp id. idx = #{idx["ts_id"]}")
    end

    end
end

test "test_conf" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # Flush MAC table
    $ts.dut.call("mesa_mac_table_flush")

    # CPU queue configuration
    $packet_rx_conf_restore = $ts.dut.call("mesa_packet_rx_conf_get")
    conf = $packet_rx_conf_restore.dup
    conf["queue"][$cpu_queue]["npi"]["enable"] = true
    $ts.dut.call("mesa_packet_rx_conf_set", conf)

    # NPI port configuration save
    $npi_conf_restore = $ts.dut.call("mesa_npi_conf_get")
    conf = $npi_conf_restore.dup
    conf["enable"] = true
    conf["port_no"] = $ts.dut.port_list[$npi_port]
    $ts.dut.call("mesa_npi_conf_set", conf)

    $npi_learn_restore = $ts.dut.call("mesa_learn_port_mode_get", $ts.dut.port_list[$npi_port])
    conf = $npi_learn_restore.dup
    conf["automatic"] = false
    $ts.dut.call("mesa_learn_port_mode_set", $ts.dut.port_list[$npi_port], conf)

    # Create MAC address entry on loop1 interface to copy frame to CPU
    entry = {
        vid_mac: { vid: 1, mac: { addr: [0x00,0x02,0x03,0x04,0x05,0x06] } },
        destination: "#{$loop_port1}",
        copy_to_cpu: true,
        copy_to_cpu_smac: false,
        locked: true,
        index_table: false,
        aged: false,
        cpu_queue: $cpu_queue,
    }
    $ts.dut.call("mesa_mac_table_add", entry)

    $ts.dut.run "mesa-cmd Debug Port Polling disable"
end

test "test_run" do
    # Test TX FIFO
    tod_tx_fifo_test
end

test "test_clean_up" do
    # CPU queue configuration restore
    $ts.dut.call("mesa_packet_rx_conf_set", $packet_rx_conf_restore)

    # NPI port configuration restore
    $ts.dut.call("mesa_npi_conf_set", $npi_conf_restore)

    # Remove static mac entries
    entry = { vid: 1, mac: { addr: [0x00,0x02,0x03,0x04,0x05,0x06] } }
    $ts.dut.call("mesa_mac_table_del", entry)

    # age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}
end
