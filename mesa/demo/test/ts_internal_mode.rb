#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'
require 'pry'

$ts = get_test_setup("mesa_pc_b2b_2x", {}, "", "loop")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5). or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")} (Lan966x).")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    loop_pair_check
    $loop_port0 = $ts.dut.looped_port_list[0]
    $loop_port1 = $ts.dut.looped_port_list[1]
end

loop_pair_check

$port0 = 0
$npi_port = 1
$port1 = 2
$cpu_queue = 7
$vlan = 100
$acl_id = 1

def tod_internal_mode_ingress_node_test
    test "tod_internal_mode_ingress_node_test" do

    # Configure input port as mode NONE
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port1)
    conf["domain"] = 0
    conf["mode"] = "MESA_TS_MODE_NONE"
    $ts.dut.call("mesa_ts_operation_mode_set", $loop_port1, conf)

    # Configure the output port internal mode. This must be called before 'ts_operation_mode'
    conf = $ts.dut.call("mesa_ts_internal_mode_get")
    conf["int_fmt"] = "MESA_TS_INTERNAL_FMT_RESERVED_LEN_30BIT"
    $ts.dut.call("mesa_ts_internal_mode_set", conf)

    # Configure output port as mode INTERNAL
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $ts.dut.port_list[$port0])
    conf["domain"] = 0
    conf["mode"] = "MESA_TS_MODE_INTERNAL"
    $ts.dut.call("mesa_ts_operation_mode_set", $ts.dut.port_list[$port0], conf)

    # age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    # Allocate a timestamp id
    conf = {port_mask: 1<<$loop_port0, context: 0, cb: 0}
    idx0 = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)    # Just to make sure that the test is working with idx ather than 0
    idx = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    # Set TOD to zero
    tod_ts  = $ts.dut.call("mesa_ts_timeofday_get")
    tod_ts[0]["seconds"] = 0
    tod_ts[0]["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_timeofday_set", tod_ts[0])

    t_i ("Transmit a Two-Step SYNC frame into NPI port with the allocated timestamp id")
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")
    frametx = tx_ifh_create($loop_port0, "MESA_PACKET_PTP_ACTION_TWO_STEP", idx["ts_id"]<<16) + frameHdrTx.dup + sync_pdu_create()
    frame_tx(frametx, $npi_port, " ", " ", " ", " ", 60)

    t_i("Update the TX FIFO in AIL. This will cause callback to Json with the TX timestamp")
    $ts.dut.call("mesa_tx_timestamp_update")

    # Get the TX time stamp. This is not a MESA API function, only a Json implementation to get the TX timestamp delivered through callback
    ts_tx = $ts.dut.call("mesa_tx_timestamp_get")

    t_i("Calculate the TX TOD nanoseconds based on TX time stamp")
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        tod_nano_tx = tc_to_tod_nano(ts_tx["ts"])
    else
        tod_nano_tx = ts_tx["ts"]
    end

    if ((ts_tx["id"] != idx["ts_id"]) || (ts_tx["ts_valid"] != true))
        t_e("Not the expected TX timestamp. ts_tx[id] = #{ts_tx["id"]}  idx[ts_id] = #{idx["ts_id"]}  ts_tx[ts_valid] = #{ts_tx["ts_valid"]}")
    end

    t_i "Calculate the 30 bit nano sec TS contained in the SYNC PDU reserved field "
    pkts = $ts.pc.get_pcap "#{$ts.links[$port0][:pc]}.pcap"
    $data = pkts[0][:data].each_byte.map{|c| c.to_i}
    reserved2 = $data[14+16..14+16+3]
    frame_ts = (reserved2[0]<<24) + (reserved2[1]<<16) + (reserved2[2]<<8) + reserved2[3]

    # check that the transmitted frame is containing expected TS in reserved fields
    diff = frame_ts - (tod_nano_tx>>16)
    t_i("Difference between frame and TX-FIFO #{diff}")
    if ((diff < 0) || (diff > 4000))
        t_e("SYNC PDU reserved field not as expected.   frame_ts #{frame_ts}   tod_nano_tx #{tod_nano_tx>>16}")
    end

    # age out the allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    end
end

def tod_internal_mode_egress_node_test
    test "tod_internal_mode_egress_node_test" do

    # This is the RX TOD nanosecond on the ingress node that is inserted in the PTP header reserved field against the egress node
    ingress_node_tod_nanoseconds = 35000000

    # Configure output port as mode NONE
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $ts.dut.port_list[$port0])
    conf["domain"] = 0
    conf["mode"] = "MESA_TS_MODE_NONE"
    $ts.dut.call("mesa_ts_operation_mode_set", $ts.dut.port_list[$port0], conf)

    # Configure the input port internal mode. This must be called before 'ts_operation_mode'
    conf = $ts.dut.call("mesa_ts_internal_mode_get")
    conf["int_fmt"] = "MESA_TS_INTERNAL_FMT_RESERVED_LEN_30BIT"
    $ts.dut.call("mesa_ts_internal_mode_set", conf)

    # Configure input port as mode INTERNAL
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port1)
    conf["domain"] = 0
    conf["mode"] = "MESA_TS_MODE_INTERNAL"
    $ts.dut.call("mesa_ts_operation_mode_set", $loop_port1, conf)

    # Age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    # Allocate a timestamp id
    conf = {port_mask: 1<<$loop_port0, context: 0, cb: 0}
    idx0 = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)    # Just to make sure that the test is working with idx ather than 0
    idx = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    # Create Two-Step SYNC frame with the allocated time stamp id and Header RSV to ingress_node_tod_nanoseconds.
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")
    frametx = tx_ifh_create($loop_port0, "MESA_PACKET_PTP_ACTION_TWO_STEP", idx["ts_id"]<<16) + frameHdrTx.dup + sync_pdu_create(ingress_node_tod_nanoseconds)

    # Set TOD to zero
    tod_ts  = $ts.dut.call("mesa_ts_timeofday_get")
    tod_ts[0]["seconds"] = 0
    tod_ts[0]["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_timeofday_set", tod_ts[0])

    t_i("Transmit the Two-Step SYNC frame into NPI port")
    frame_tx(frametx, $npi_port, " " , " ", " ", " ", 60)

    t_i ("Update the TX FIFO in AIL. This will cause callback to Json with the TX timestamp")
    $ts.dut.call("mesa_tx_timestamp_update")

    # Get the TX time stamp. This is not a MESA API function, only a Json implementation to get the TX timestamp delivered through callback
    ts_tx = $ts.dut.call("mesa_tx_timestamp_get")

    t_i ("Calculate the TX TOD nanoseconds based on TX time stamp")
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        tod_nano_tx = tc_to_tod_nano(ts_tx["ts"])
    else
        tod_nano_tx = ts_tx["ts"]
    end

    if ((ts_tx["id"] != idx["ts_id"]) || (ts_tx["ts_valid"] != true))
        t_e("Not the expected TX timestamp. ts_tx[id] = #{ts_tx["id"]}  idx[ts_id] = #{idx["ts_id"]}  ts_tx[ts_valid] = #{ts_tx["ts_valid"]}")
    end

    t_i "Calculate the Correction field contained in the SYNC PDU "
    pkts = $ts.pc.get_pcap "#{$ts.links[$port0][:pc]}.pcap"
    $data = pkts[0][:data].each_byte.map{|c| c.to_i}
    corr = $data[14+8..14+8+7]
    nano_correction = (corr[0]<<56) + (corr[1]<<48) + (corr[2]<<40) + (corr[3]<<32) + (corr[4]<<24) + (corr[5]<<16) + (corr[6]<<8) + corr[7]

    t_i("calculate the smallest expected correction value. The tod_nano_tx is not egress time in this node but close")
    smallest_corr_value = (tod_nano_tx >> 16) - ingress_node_tod_nanoseconds
    diff = (nano_correction >> 16) - smallest_corr_value    # The difference the actual correction value and the calculated smallest value is due to the difference between the frame TX timestamp and the actual node TX timestamap approx 4000 nanoseconds
    t_i("Difference between frame and TX-FIFO #{diff}  nano_correction #{nano_correction >> 16}   tod_nano_tx #{tod_nano_tx >> 16}   smallest_corr_value #{smallest_corr_value}")

    # check that the transmitted frame is containing expected correction field
    if ((diff < 0) || (diff > 4000))
        t_e("SYNC PDU correction field not as expected.")
    end

    # age out the allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    end
end

test "test_conf" do
    $ts.dut.run("mesa-cmd port mode #{$loop_port0+1} 1000fdx")
    $ts.dut.run("mesa-cmd port mode #{$loop_port1+1} 1000fdx")

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

    # Set VLAN port configuration
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$port0])
    $vlan_port_conf_restore0 = conf.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_UNAWARE"
    conf["pvid"] = $vlan
    conf["untagged_vid"] = $vlan
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port0], conf)

    conf = $ts.dut.call("mesa_vlan_port_conf_get", $loop_port1)
    $vlan_port_conf_restore1 = conf.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_UNAWARE"
    conf["pvid"] = $vlan
    conf["untagged_vid"] = $vlan
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $loop_port1, conf)

    # Set VLAN memberships
    port_list = "#{$ts.dut.port_list[$port0]},#{$loop_port1}"
    $ts.dut.call("mesa_vlan_port_members_set", $vlan, port_list)

    # Create IS2 to ONE-STEP SYNC frame
    conf = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ETYPE")
    conf["id"] = $acl_id
    conf["port_list"] = "#{$loop_port1}"
    action = conf["action"]
    action["ptp_action"] = "MESA_ACL_PTP_ACTION_ONE_STEP"
    $ts.dut.call("mesa_ace_add", 0, conf)

    # Port PTP domain configuration save
    $operation_mode_0_restore =  $ts.dut.call("mesa_ts_operation_mode_get", $ts.dut.port_list[$port0])
    $operation_mode_l1_restore = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port1)

    # Internal mode configuration save
    $internal_mode = $ts.dut.call("mesa_ts_internal_mode_get")
end

test "test_run" do
    # Test ingress internal mode
    tod_internal_mode_ingress_node_test

    # Test egress internal mode
    tod_internal_mode_egress_node_test
end

test "test_clean_up" do
    # CPU queue configuration restore
    $ts.dut.call("mesa_packet_rx_conf_set", $packet_rx_conf_restore)

    # NPI port configuration restore
    $ts.dut.call("mesa_npi_conf_set", $npi_conf_restore)

    # Delete ACE rule
    $ts.dut.call("mesa_ace_del", $acl_id)

    # VLAN port configuration restore
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port0], $vlan_port_conf_restore0)
    $ts.dut.call("mesa_vlan_port_conf_set", $loop_port1, $vlan_port_conf_restore1)

    # Clear VLAN memberships
    $ts.dut.call("mesa_vlan_port_members_set", $vlan, "")

    # Operation mode restore
    $ts.dut.call("mesa_ts_operation_mode_set", $ts.dut.port_list[$port0], $operation_mode_0_restore)
    $ts.dut.call("mesa_ts_operation_mode_set", $loop_port1, $operation_mode_l1_restore)

    # Internal mode restore
    $ts.dut.call("mesa_ts_internal_mode_set", $internal_mode)

    # age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}
end
