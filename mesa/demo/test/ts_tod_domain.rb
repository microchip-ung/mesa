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
    $cap_phy_ts = $ts.dut.call("mesa_capability", "MESA_CAP_PHY_TS")
    $cap_port_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    loop_pair_check
end

loop_pair_check

$pcb = $ts.dut.pcb

$port0 = 0
$npi_port = 1
$cpu_queue = 7
$loop_port0 = 0
$loop_port1 = 0

$port_map = $ts.dut.call("mesa_port_map_get", $cap_port_cnt)


def check_correction_field(domain)
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")

    frametx = tx_ifh_create($ts.dut.port_list[$port0], "MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP", 0xFEFEFEFE0000, domain) + frameHdrTx.dup + sync_pdu_create()
    test "Inject SYNC frame into NPI port and receive SYNC frame from front port and check the correction field" do
    frame_tx(frametx, $npi_port, " ", " ", " ", " ", 60)
    pkts = $ts.pc.get_pcap "#{$ts.links[$port0][:pc]}.pcap"
    $data = pkts[0][:data].each_byte.map{|c| c.to_i}
    t_i"$data #{$data}"
    correction_ns = $data[22..27]
    t_i"correction_ns #{correction_ns}   #{(correction_ns[0]<<40) + (correction_ns[1]<<32) + (correction_ns[2]<<24) + (correction_ns[3]<<16) + (correction_ns[4]<<8) + correction_ns[5]}"
    end

    frametx = tx_ifh_create($loop_port0, "MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP", 0xFEFEFEFE0000, domain) + frameHdrTx.dup + sync_pdu_create()
    test "Inject SYNC into NPI port to be transmitted on loop0 port and receive SYNC frame from NPI port and check the correction field" do
    frame_tx(frametx, $npi_port, " ", " ", " ", " ", 100)
    pkts = $ts.pc.get_pcap "#{$ts.links[$npi_port][:pc]}.pcap"
    $data = pkts[1][:data].each_byte.map{|c| c.to_i}
    t_i"$data #{$data}"
    correction_ns = $data[44+22..44+27]
    t_i"correction_ns #{correction_ns}   #{(correction_ns[0]<<40) + (correction_ns[1]<<32) + (correction_ns[2]<<24) + (correction_ns[3]<<16) + (correction_ns[4]<<8) + correction_ns[5]}"
    end

    frametx = frameHdrTx.dup + sync_pdu_create()
    test "Inject SYNC into front port and receive SYNC frame from NPI port and check the correction field" do
    frame_tx(frametx, $port0, " ", " ", " ", " ", 100)
    pkts = $ts.pc.get_pcap "#{$ts.links[$npi_port][:pc]}.pcap"
    $data = pkts[0][:data].each_byte.map{|c| c.to_i}
    t_i"$data #{$data}"
    correction_ns = $data[44+22..44+27]
    t_i"correction_ns #{correction_ns}   #{(correction_ns[0]<<40) + (correction_ns[1]<<32) + (correction_ns[2]<<24) + (correction_ns[3]<<16) + (correction_ns[4]<<8) + correction_ns[5]}"
    end

    t_i("Configure mirroring")
    conf = $ts.dut.call("mesa_mirror_conf_get")
    conf["port_no"] = $ts.dut.port_list[$port0]
    conf["tag"] = "MESA_MIRROR_TAG_NONE"
    $ts.dut.call("mesa_mirror_conf_set", conf)
#    port_list = "0,1,2,3,4,5,6,7"
    port_list = "#{$loop_port1}"
    $ts.dut.call("mesa_mirror_ingress_ports_set", port_list)

    frametx = tx_ifh_create($loop_port0, "MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP", 0xFEFEFEFE0000, domain) + frameHdrTx.dup + sync_pdu_create()
    test "Inject SYNC into NPI port to be transmitted on loop0 port and receive SYNC frame from NPI port and check the correction field" do
    frame_tx(frametx, $npi_port, " ", " ", " ", " ", 100)
    pkts = $ts.pc.get_pcap "#{$ts.links[$npi_port][:pc]}.pcap"
    $data = pkts[1][:data].each_byte.map{|c| c.to_i}
    t_i"$data #{$data}"
    npi_corr_ns = $data[44+22..44+27]

    pkts = $ts.pc.get_pcap "#{$ts.links[$port0][:pc]}.pcap"
    $data = pkts[0][:data].each_byte.map{|c| c.to_i}
    t_i"$data #{$data}"
    mirror_corr_ns = $data[22..27]

    t_i"NPI port correction_ns #{npi_corr_ns}   #{(npi_corr_ns[0]<<40) + (npi_corr_ns[1]<<32) + (npi_corr_ns[2]<<24) + (npi_corr_ns[3]<<16) + (npi_corr_ns[4]<<8) + npi_corr_ns[5]}"
    t_i"Mirror port correction_ns #{mirror_corr_ns}   #{(mirror_corr_ns[0]<<40) + (mirror_corr_ns[1]<<32) + (mirror_corr_ns[2]<<24) + (mirror_corr_ns[3]<<16) + (mirror_corr_ns[4]<<8) + mirror_corr_ns[5]}"
    end
end

def tod_domain_test(domain, seconds)
    $data = ""
    $tod_ts = 0
    $tx_tc = 0
    $frame_info = ""

    test "tod_domain_test  doamin = #{domain}  seconds = #{seconds}" do

    #domain == 3 indicates use of default domain API
    domain_def = (domain == 3) ? true : false
    if (domain_def)
        domain = 0    # The default domain is 0
    end

    # Port PTP domain configuration
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $ts.dut.port_list[$port0])
    conf["domain"] = domain
    $ts.dut.call("mesa_ts_operation_mode_set", $ts.dut.port_list[$port0], conf)
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port0)
    conf["domain"] = domain
    $ts.dut.call("mesa_ts_operation_mode_set", $loop_port0, conf)
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port1)
    conf["domain"] = domain
    $ts.dut.call("mesa_ts_operation_mode_set", $loop_port1, conf)

    #Check that TOD in a domain can be configured and is incremented
    # Set TOD to 'second'
    $tod_ts  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    $tod_ts[0]["seconds"] = seconds
    $tod_ts[0]["nanoseconds"] = 0
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", $tod_ts[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts[0])

    # Get TOD to check configuration
    $tod_ts  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    if ($tod_ts[0]["seconds"] != seconds)
        t_e("TOD in domain #{domain} was not configured as expected.  seconds = #{seconds}  tod_ts[seconds] = #{$tod_ts[0]["seconds"]}")
    end

    # Get previous PPS TOD. Only default domain call possible - there is no domain interface for this !!!
    if (domain_def)
        $ts.dut.call("mesa_ts_timeofday_set", $tod_ts[0])
        prev_ts = $ts.dut.call("mesa_ts_timeofday_prev_pps_get")
        if (prev_ts["seconds"] != seconds)
            t_e("Previous TOD in domain #{domain} was not configured as expected.  seconds = #{seconds}  prev_ts[seconds] = #{prev_ts["seconds"]}")
        end
    end

    # Get next PPS TOD.
    $tod_ts[0]["seconds"] = seconds
    $tod_ts[0]["nanoseconds"] = 0
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", $tod_ts[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts[0])
    next_ts = domain_def ? $ts.dut.call("mesa_ts_timeofday_next_pps_get") : $ts.dut.call("mesa_ts_domain_timeofday_next_pps_get", domain)
    if (next_ts["seconds"] > (seconds + 2))   # It has been seen that two seconds has passed since mesa_ts_timeofday_set()
        t_e("next TOD in domain #{domain} was not configured as expected.  seconds = #{seconds}  next_ts[seconds] = #{next_ts["seconds"]}")
    end

    t_i ("Sleep one second and check that TOD seconds is incremented - do a new TOD set first")
    $tod_ts[0]["seconds"] = seconds
    $tod_ts[0]["nanoseconds"] = 0
    domain_def ? $ts.dut.call("mesa_ts_timeofday_set", $tod_ts[0]) : $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts[0])
    sleep(1)

    $tod_ts  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    if ($tod_ts[0]["seconds"] != (seconds + 1))
        t_e("TOD in domain #{domain} is not incrementing as expected.  expected seconds = #{seconds+1}  tod_ts[seconds] = #{$tod_ts[0]["seconds"]}")
    end

    $tod_ts[0]["seconds"] = seconds
    $tod_ts[0]["nanoseconds"] = 0

    test "Inject SYNC frame with PTP action NONE AFI into NPI port and receive SYNC frame from front port and check the origin timestamp" do
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")
    #tx_ifh_create(port=0, ptp_act="MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", ptp_ts=0xFEFEFEFE0000, domain=0)
    frametx = tx_ifh_create($ts.dut.port_list[$port0], "MESA_PACKET_PTP_ACTION_AFI_NONE", 0xFEFEFEFE0000, domain) + frameHdrTx.dup + sync_pdu_create()
    framerx = frameHdrTx.dup + sync_pdu_rx_create(IGNORE, 0)  # Frame should not be updated

    $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts[0])
    frame_tx(frametx, $npi_port, framerx , " ", " ", " ")
    end

#    check_correction_field(domain)

    test "Inject SYNC frame into NPI port and receive SYNC frame from front port and check the origin timestamp" do
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")
    #tx_ifh_create(port=0, ptp_act="MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", ptp_ts=0xFEFEFEFE0000, domain=0)
    frametx = tx_ifh_create($ts.dut.port_list[$port0], "MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", 0xFEFEFEFE0000, domain) + frameHdrTx.dup + sync_pdu_create()
    framerx = frameHdrTx.dup + sync_pdu_rx_create(IGNORE, seconds)

    $ts.dut.call("mesa_ts_domain_timeofday_set", domain, $tod_ts[0])
    frame_tx(frametx, $npi_port, framerx , " ", " ", " ")
    end

    test "Inject SYNC into NPI port to be transmitted on loop0 port and receive SYNC frame from NPI port" do
    # Update default ingress and egress latency in the API. This is based on register values potentially different after link up
    # Delay after call to mesa_ts_status_change should be smaller as the default delay (that is added) is calculated internally in the API
    # This is only the case the first run of the test after boot as this default delay is remembered in the API
    $ts.dut.call("mesa_ts_status_change", $loop_port0)
    $ts.dut.call("mesa_ts_status_change", $loop_port1)

    # age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    # Allocate a timestamp id
    conf = {port_mask: 1<<$loop_port0, context: 0, cb: 0}
    idx0 = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)    # Just to make sure that the test is working with idx ather than 0
    idx = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    t_i ("Transmit a Two-Step SYNC frame into NPI port with the allocated timestamp id on NPI against loop port and receive again on NPI port")
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")
    #tx_ifh_create(port=0, ptp_act="MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", ptp_ts=0xFEFEFEFE0000, domain=0)
    frametx = tx_ifh_create($loop_port0, "MESA_PACKET_PTP_ACTION_TWO_STEP", idx["ts_id"]<<16, domain) + frameHdrTx.dup + sync_pdu_create()
    framerx = rx_ifh_create($loop_port1) + frameHdrTx.dup + sync_pdu_rx_create()
    $tod_ts  = domain_def ? $ts.dut.call("mesa_ts_timeofday_get") : $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    frame_tx(frametx, $npi_port, " ", " ", " ", framerx, 60)

    t_i "Calculate the IFH and decode it"
    pkts = $ts.pc.get_pcap "#{$ts.links[$npi_port][:pc]}.pcap"
    ifh = rx_ifh_extract(pkts[1])   # both transmitted and received frame is in 'pkts'
    meta = { no_wait: false, chip_no: 0, xtr_qu: 0, etype: 0, fcs: 0, sw_tstamp: { hw_cnt: 0 }, length: 0}
    $frame_info = $ts.dut.call("mesa_packet_rx_hdr_decode", meta, ifh)
    $hw_tstamp = $frame_info["hw_tstamp"] >> 16

    if ((domain == 0) && ($cap_phy_ts != 0))    #Port with timestamping PHY is assumed by API to be in domain 0 always
        t_i ("Get the frame RX tc based on a 32 bit ns counter from frame content inserted by timestamping PHY")
        tx_props = { ts_feature_is_PTS: true, phy_ts_mode: "MESA_PACKET_INTERNAL_TC_MODE_32BIT", backplane_port: false, delay_comp: {delay_cnt: 100<<16, asymmetry_cnt: 100<<16} }
        phy_ts = ($tod_ts[0]["seconds"] * 1000000000) + $tod_ts[0]["nanoseconds"] # The TS inserted in frame by PHY is a 32 bit wrapping TOD nanoseconds. Current TOD TS is used as PHY TS
        timestamp = [((phy_ts & 0xFF000000) >> 24), ((phy_ts & 0xFF0000) >> 16), ((phy_ts & 0xFF00) >> 8), (phy_ts & 0xFF)]
        frame_ts = $ts.dut.call("mesa_ptp_get_timestamp", timestamp, $frame_info, "MESA_PACKET_PTP_MESSAGE_TYPE_SYNC", tx_props)
        rx_tc = frame_ts[0]

        if (rx_tc != $tod_ts[1])
            t_e("RX TC is not as expected.  rx_tc: #{rx_tc}  tod_ts[1]: #{$tod_ts[1]}")
        end
    end

    t_i ("Update the TX FIFO in AIL. This will cause callback to Jason with the TX timestamp")
    $ts.dut.call("mesa_tx_timestamp_update")

    t_i ("Get the TX timestamp. This is not a MESA API function, only a Jason implementation to get the TX timestamp delivered through callback")
    ts_tx = $ts.dut.call("mesa_tx_timestamp_get")
    if ((ts_tx["id"] != idx["ts_id"]) || (ts_tx["ts_valid"] != true))
        t_e("Not the expected TX timestamp. ts_tx[id] = #{ts_tx["id"]}  idx[ts_id] = #{idx["ts_id"]}  ts_tx[ts_valid] = #{ts_tx["ts_valid"]}")
    end
    $tx_tc = ts_tx["ts"] >> 16
    end

    test "Check the calculated received frame tc value" do
    t_i "Get the delay and asymmetry compensated frame RX tc from frame_info"
    tx_props = { ts_feature_is_PTS: false, phy_ts_mode: "MESA_PACKET_INTERNAL_TC_MODE_32BIT", backplane_port: false, delay_comp: {delay_cnt: 100<<16, asymmetry_cnt: 100<<16} }
    rx_ts = $ts.dut.call("mesa_ptp_get_timestamp", [0,1,2,3], $frame_info, "MESA_PACKET_PTP_MESSAGE_TYPE_SYNC", tx_props)
    rx_tc = rx_ts[0] >> 16
    diff = rx_tc - $tx_tc
    t_i ("tx_tc: #{$tx_tc}  hw_tstamp: #{$hw_tstamp}  rx_tc: #{rx_tc}  difference: #{diff}")

    # The loop cable is a 1 meter DAC that should give delay close to 4 nanoseconds.
    min = -200-2
    max = -200+18  #200ns is from delay_comp: {delay_cnt: 100<<16, asymmetry_cnt: 100<<16}
                   #Latency 17 is seen on Fireant Jenkins test
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X"))
        if ($ts.dut.pcb == "8281-SVB")
            min = -200+480  #Copper SFP
            max = -200+520  #Copper SFP
        end
        if ($ts.dut.pcb == "8290")
            min = -200      #External PHY
            max = -200+75   #External PHY
        end
    end

    if (diff > max)
        t_e("Difference between TX TC and RX TC is unexpected high.  max: #{max}")
    end
    if (diff < min)
        t_e("Difference between TX TC and RX TC is unexpected low.  min: #{min}")
    end

    if (($hw_tstamp - (tx_props[:delay_comp][:delay_cnt]>>16) - (tx_props[:delay_comp][:asymmetry_cnt]>>16)) != rx_tc)  # Check that the calculated frame tc is correctly compensated
        t_e("Frame TC is not as expected. rx_tc: #{rx_tc}  hw_tstamp: #{$hw_tstamp}  expected rx_tc #{$hw_tstamp - (tx_props[:delay_comp][:delay_cnt]>>16) - (tx_props[:delay_comp][:asymmetry_cnt]>>16)}")
    end
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
    $npi_conf_restore = $ts.dut.call("mesa_npi_conf_get")
    conf = $npi_conf_restore.dup
    conf["enable"] = true
    conf["port_no"] = $ts.dut.port_list[$npi_port]
    $ts.dut.call("mesa_npi_conf_set", conf)

    $npi_learn_restore = $ts.dut.call("mesa_learn_port_mode_get", $ts.dut.port_list[$npi_port])
    conf = $npi_learn_restore.dup
    conf["automatic"] = false
    $ts.dut.call("mesa_learn_port_mode_set", $ts.dut.port_list[$npi_port], conf)

    $operation_mode_0_restore = $ts.dut.call("mesa_ts_operation_mode_get", $ts.dut.port_list[$port0])
    $operation_mode_l0_restore = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port0)
    $operation_mode_l1_restore = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port1)

    # CreateMAC address entry to copy frame to CPU
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

    $loop_port0 = $ts.dut.looped_port_list[0]
    $loop_port1 = $ts.dut.looped_port_list[1]

    i = 0
    while (i < $ts.dut.looped_port_list.length) do
        if ((i % 2) != 0)
            port0 = $ts.dut.looped_port_list[i-1]
            port1 = $ts.dut.looped_port_list[i]
            i = i + 1
        else
            i = i + 1
            next
        end

        if ((port0 >= $cap_port_cnt) || (port1 >= $cap_port_cnt))
            next
        end

        cap = $ts.dut.run "mesa-cmd deb port cap #{port0+1}"
        if cap[:out].include?("SFP_ONLY")
            t_i "Prefer SFP port  port0 #{port0} port1 #{port1}"
            $loop_port0 = port0
            $loop_port1 = port1
            break;
        end
    end
end

test "test_run" do
    # Test TOD domains using domain specific API
    tod_domain_test(0, 10)
    tod_domain_test(1, 100)
    tod_domain_test(2, 1000)

    # Test TOD using default domain (0) API. Domain value 3 is a illegal domain indicating default
    tod_domain_test(3, 0)
end

test "test_clean_up" do
    # CPU queue configuration restore
    $ts.dut.call("mesa_packet_rx_conf_set", $packet_rx_conf_restore)

    # NPI port configuration restore
    $ts.dut.call("mesa_npi_conf_set", $npi_conf_restore)

    $ts.dut.call("mesa_learn_port_mode_set", $ts.dut.port_list[$npi_port], $npi_learn_restore)

    # Remove static mac entries
    entry = { vid: 1, mac: { addr: [0x00,0x02,0x03,0x04,0x05,0x06] } }
    $ts.dut.call("mesa_mac_table_del", entry)

    # Operation mode restore
    $ts.dut.call("mesa_ts_operation_mode_set", $ts.dut.port_list[$port0], $operation_mode_0_restore)
    $ts.dut.call("mesa_ts_operation_mode_get", $loop_port0, $operation_mode_l0_restore)
    $ts.dut.call("mesa_ts_operation_mode_get", $loop_port0, $operation_mode_l1_restore)

    # age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    $ts.dut.run "mesa-cmd Debug Port Polling enable"
end
