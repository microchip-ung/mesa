#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$ts = get_test_setup("mesa_pc_b2b_4x", {}, "")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5). or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")} (Lan966x).")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    $cap_phy_ts = $ts.dut.call("mesa_capability", "MESA_CAP_PHY_TS")
    $cap_port_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    $packet_inj_encap = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_INJ_ENCAP")
    assert($packet_inj_encap == 1, "injection with specific encapsulation not supported")
    loop_pair_check
end

loop_pair_check

$pcb = $ts.dut.pcb

$vlan = 100
$port0 = 0
$port1 = 1
$npi_port = 2
$cpu_queue = 7
$acl_id = 1

$port_map = $ts.dut.call("mesa_port_map_get", $cap_port_cnt)

def ip_test(ip)
    $data = ""
    $tod_ts = 0
    $tx_tc = 0
    $frame_info = ""
    $requestClockId = 0xAABBCCDDEEFFAABB
    $requestPortNumber = 0xABCD

    seconds = 10
    domain = 0

    # Port PTP domain configuration
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $ts.dut.port_list[$port0])
    conf["domain"] = domain
    $ts.dut.call("mesa_ts_operation_mode_set", $ts.dut.port_list[$port0], conf)

    # Set TOD to 10 second
    $tod_ts  = $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    $tod_ts[0]["seconds"] = seconds
    $tod_ts[0]["nanoseconds"] = 0

    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c", "#{ip} udp")

    test "Inject a ORIGIN-TIMESTAMP SYNC frame into NPI port and receive frame from front port and check the origin timestamp" do
    #tx_ifh_create(port=0, ptp_act="MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", ptp_ts=0xFEFEFEFE0000, domain=0, seq_idx=0, proto=0)
    frametx = tx_ifh_create($ts.dut.port_list[$port0], "MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", 0xFEFEFEFE0000, 0, 0, ip) + frameHdrTx.dup + sync_pdu_create()
    frameHdrRx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c", "#{ip} ign udp ign")
    framerx = frameHdrRx + sync_pdu_rx_create(IGNORE, seconds)

    $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts[0])
    frame_tx(frametx, $npi_port, framerx , " ", " ", " ")
    end

    test "Inject a ORIGIN-TIMESTAMP REQUEST frame into NPI port and receive frame from front port and check the correction field" do
    #tx_ifh_create(port=0, ptp_act="MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", ptp_ts=0xFEFEFEFE0000, domain=0, seq_idx=0, proto=0)
    frametx = tx_ifh_create($ts.dut.port_list[$port0], "MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP", 0xFEFEFEFE0000, 0, 0, ip) + frameHdrTx.dup + request_pdu_create($requestClockId, $requestPortNumber)

    size = 44+28+17
    off = 14+28
    $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts[0])
    frame_tx(frametx, $npi_port, " " , " ", " ", " ", size)
    pkts = $ts.pc.get_pcap "#{$ts.links[$port0][:pc]}.pcap"
    data = pkts[0][:data].each_byte.map{|c| c.to_i}
    t_i "data #{data}"

    nano_correction = ((data[off+8]<<40) + (data[off+9]<<32) + (data[off+10]<<24) + (data[off+11]<<16) + (data[off+12]<<8) + (data[off+13]))
    origin_sec = ((data[off+34]<<40) + (data[off+35]<<32) + (data[off+36]<<24) + (data[off+37]<<16) + (data[off+38]<<8) + (data[off+39]))
    origin_nsec = ((data[off+40]<<24) + (data[off+41]<<16) + (data[off+42]<<8) + (data[off+43]))
    origin_f = origin_sec.to_f + origin_nsec/1000000000.0
    t_i "nano_correction #{nano_correction}"
    t_i "origin_f #{origin_f}"
    if (nano_correction > 1000)
        t_e "Origin not as expected"
    end
    if ((origin_f > 13.2) || (origin_f < seconds))
        t_e "Origin not as expected"
    end
    end

    test "Inject a ONE-STEP REQUEST frame into NPI port and receive frame from front port and check the correction field" do
    #tx_ifh_create(port=0, ptp_act="MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", ptp_ts=0xFEFEFEFE0000, domain=0, seq_idx=0, proto=0)
    frametx = tx_ifh_create($ts.dut.port_list[$port0], "MESA_PACKET_PTP_ACTION_ONE_STEP", (seconds * 1000000000) << 16, 0, 0, ip) + frameHdrTx.dup + request_pdu_create($requestClockId, $requestPortNumber)

    size = 44+28+17
    off = 14+28
    $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts[0])
    frame_tx(frametx, $npi_port, " " , " ", " ", " ", size)
    pkts = $ts.pc.get_pcap "#{$ts.links[$port0][:pc]}.pcap"
    data = pkts[0][:data].each_byte.map{|c| c.to_i}
    t_i "data #{data}"

    nano_correction = ((data[off+8]<<40) + (data[off+9]<<32) + (data[off+10]<<24) + (data[off+11]<<16) + (data[off+12]<<8) + (data[off+13]))
    origin_sec = ((data[off+34]<<40) + (data[off+35]<<32) + (data[off+36]<<24) + (data[off+37]<<16) + (data[off+38]<<8) + (data[off+39]))
    origin_nsec = ((data[off+40]<<24) + (data[off+41]<<16) + (data[off+42]<<8) + (data[off+43]))
    origin_f = origin_sec.to_f + origin_nsec/1000000000.0
    t_i "nano_correction #{nano_correction}"
    t_i "origin_f #{origin_f}"
    if (nano_correction > 800000000)
        t_e "Origin not as expected"
    end
    if (origin_f != 0)
        t_e "Origin not as expected"
    end
    end

    test "Transmit a ONE-STEP SYNC through the switch and check correction field is updated" do
    conf = $ts.dut.call("mesa_ace_init", (ip == "ipv4") ? "MESA_ACE_TYPE_IPV4" : "MESA_ACE_TYPE_IPV6")
    conf["id"] = $acl_id
    conf["port_list"] = "#{$ts.dut.port_list[$port0]}"
    action = conf["action"]
    action["ptp_action"] = "MESA_ACL_PTP_ACTION_ONE_STEP"
    $ts.dut.call("mesa_ace_add", 0, conf)

    lowest_corr_none,range = nano_corr_lowest_measure(ip)

    if ((lowest_corr_none < 0) || (lowest_corr_none > 3100))
        t_e("Unexpected correction field including egress delay. lowest_corr_none = #{lowest_corr_none}")
    end
    end
end

test "test_conf" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # CPU queue configuration
    $packet_rx_conf_restore = $ts.dut.call("mesa_packet_rx_conf_get")
    conf = $packet_rx_conf_restore.dup
    conf["queue"][$cpu_queue]["npi"]["enable"] = true
    $ts.dut.call("mesa_packet_rx_conf_set", conf)

    # NPI port configuration save
    conf = $ts.dut.call("mesa_npi_conf_get")
    conf["enable"] = true
    conf["port_no"] = $ts.dut.port_list[$npi_port]
    $ts.dut.call("mesa_npi_conf_set", conf)

    # Set VLAN port configuration
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$port0])
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_UNAWARE"
    conf["pvid"] = $vlan
    conf["untagged_vid"] = $vlan
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port0], conf)

    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$port1])
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_UNAWARE"
    conf["pvid"] = $vlan
    conf["untagged_vid"] = $vlan
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port1], conf)

    # Set VLAN memberships
    port_list = "#{$ts.dut.port_list[$port0]},#{$ts.dut.port_list[$port1]}"
    $ts.dut.call("mesa_vlan_port_members_set", $vlan, port_list)
end

test "test_run" do
    ip_test("ipv4")
#    ip_test("ipv6")
end
