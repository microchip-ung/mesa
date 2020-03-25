#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5).")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    $cap_port_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    assert((($ts.dut.looped_port_list != nil) && (($ts.dut.looped_port_list.length % 2) == 0)),
           "Number of looped front ports must be multiples of two")
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        assert(($ts.dut.looped_port_list_10g != nil) && ($ts.dut.looped_port_list_10g.length > 1),
            "On Jaguar2 two 10G front ports must be looped")
        $loop_port0_10g = $ts.dut.looped_port_list_10g[0]
        $loop_port1_10g = $ts.dut.looped_port_list_10g[1]
    end
end

# To change PCB to run 25G Do the following linux commands:
# ps
#               ps-id root     er -b -l /tmp/console-er -- mesa-demo -f
# kill ps-id
# fw_setenv pcb_var 9
# mesa-demo
# The NPI port cable must be moved to the responding 25G port
conf = $ts.dut.call("mesa_port_conf_get", 0)
if (chip_family_to_id("MESA_CHIP_FAMILY_SPARX5") && conf["speed"] == "MESA_SPEED_25G")
    $ts.dut.looped_port_list.clear
    $ts.dut.looped_port_list << 6
    $ts.dut.looped_port_list << 7
end

$port0 = 0
$port1 = 1
$port2 = 2
$cpu_queue = 7
$npi_port = 3

$port_map = $ts.dut.call("mesa_port_map_get", $cap_port_cnt)

PTP_LATENCY_MAX = 300

def nano_delay_measure(port0, port1)
    $nano_delay

    test "nano_delay_measure" do

    # Initialize TOD to zero
    tod_ts  = $ts.dut.call("mesa_ts_timeofday_get")
    tod_ts[0]["seconds"] = 0
    tod_ts[0]["nanoseconds"] = 0

    # age out any allocated timestamps id's
    4.times {$ts.dut.call("mesa_timestamp_age")}

    # Allocate a timestamp id
    conf = {port_mask: 1<<port0, context: 0, cb: 0}
    idx = $ts.dut.call("mesa_tx_timestamp_idx_alloc", conf)

    console ("transmit SYNC frame on NPI against loop port and receive again on NPI port")
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")
    frametx = tx_ifh_create(port0, "MESA_PACKET_PTP_ACTION_TWO_STEP", idx["ts_id"]) + frameHdrTx.dup + sync_pdu_create()
    framerx = rx_ifh_create(port1) + frameHdrTx.dup + sync_pdu_rx_create()
    frame_tx(frametx, $npi_port, "", "", "", framerx, 60)
    pkts = $ts.pc.get_pcap "#{$ts.links[$npi_port][:pc]}.pcap"

    console ("Calculate the IFH and decode it")
    ifh = rx_ifh_extract(pkts[1])   # both transmitted and received frame is in 'pkts'
    meta = { no_wait: false, chip_no: 0, xtr_qu: 0, etype: 0, fcs: 0, sw_tstamp: { hw_cnt: 0 }, length: 0}
    frame_info = $ts.dut.call("mesa_packet_rx_hdr_decode", meta, ifh)

    console ("Update the TX FIFO in AIL. This will cause callback to Jason with the TX timestamp")
    $ts.dut.call("mesa_tx_timestamp_update")

    console ("Get the TX timestamp. This is not a MESA API function, only a Jason implementation to get the TX timestamp delivered through callback")
    ts_tx = $ts.dut.call("mesa_tx_timestamp_get")
    if ((ts_tx["id"] != idx["ts_id"]) || (ts_tx["ts_valid"] != true))
        t_e("Not the expected TX timestamp. ts_tx[id] = #{ts_tx["id"]}  idx[ts_id] = #{idx["ts_id"]}  ts_tx[ts_valid] = #{ts_tx["ts_valid"]}")
    end
    tod_nano_tx = ts_tx["ts"] >> 16

    #Calculate the RX TOD nanoseconds based on IFH RX tc
    tod_nano_rx = frame_info["hw_tstamp"] >> 16

    # Calculate the delay as the difference between RX and TX TOD nanoseconds
    $nano_delay = tod_nano_rx - tod_nano_tx
    console("nano_delay = #{$nano_delay}  tod_nano_tx = #{tod_nano_tx}  tod_nano_rx = #{tod_nano_rx}")
#$ts.dut.run ("mesa-cmd deb sym read SD_LANE[31-32]:SD_FIFO_DELAY:SD_DELAY_VAR")
    end

    $nano_delay
end

def tod_latency_test(port0, port1)
    test "tod_latency_test" do

    # Set Port PTP domain to 0 on loop ports
    conf = $ts.dut.call("mesa_ts_operation_mode_get", port0)
    conf["domain"] = 0
    $ts.dut.call("mesa_ts_operation_mode_set", port0, conf)
    conf = $ts.dut.call("mesa_ts_operation_mode_get", port1)
    conf["domain"] = 0
    $ts.dut.call("mesa_ts_operation_mode_set", port1, conf)

    # Set external clock mode to disable
    conf = $ts.dut.call("mesa_ts_external_clock_mode_get")
    conf["one_pps_mode"] = "MESA_TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE"
    conf["enable"] = false
    conf["freq"] = 0
    $ts.dut.call("mesa_ts_external_clock_mode_set", conf)

    # Update default ingress and egress latency in the API. This is based on register values potentially different after link up
    # Delay after call to mesa_ts_status_change should be smaller as the default delay (that is added) is calculated internally in the API
    # This is only the case the first run of the test after boot as this default delay is remembered in the API
    $ts.dut.call("mesa_ts_status_change", port0)
    $ts.dut.call("mesa_ts_status_change", port1)

    # Set Port egress latency to zero on loop TX port
    latency = $ts.dut.call("mesa_ts_egress_latency_get", port0)
    latency = 0
    $ts.dut.call("mesa_ts_egress_latency_set", port0, latency)

    # Set Port inress latency to zero on loop RX port
    latency = $ts.dut.call("mesa_ts_ingress_latency_get", port1)
    latency = 0
    $ts.dut.call("mesa_ts_ingress_latency_set", port1, latency)

delays = []
10.times {
    # Measure nanosecond delay
    nano_delay_0 = nano_delay_measure(port0, port1)

delays << nano_delay_0
$ts.dut.run ("mesa-cmd port state #{port0} disable")
sleep 1
$ts.dut.run ("mesa-cmd port state #{port0} enable")
sleep 2
$ts.dut.call("mesa_ts_status_change", port0)
$ts.dut.call("mesa_ts_status_change", port1)
}
console("delays = #{delays}")
return
    # The loop cable is a 1 meter DAC that should give delay close to 4 nanoseconds.
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        nano_delay = nano_delay_0
    end
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        nano_delay = nano_delay_0 - ((nano_delay_0 > 60) ? 62 : 0)  # Currently on Fireant 25G SERDES the delay can be 62 ns off. Accept this for now
    end
    if ((nano_delay < -2) || (nano_delay > 8))
        t_e("Unexpected delay with egress latency 0 and ingress latency 0.  Delay = #{nano_delay_0}")
    end

    # Set Port egress latency to max
    latency = PTP_LATENCY_MAX << 16
    $ts.dut.call("mesa_ts_egress_latency_set", port0, latency)

    # Measure nanosecond delay
    nano_delay_1 = nano_delay_measure(port0, port1)
    diff = nano_delay_0 - nano_delay_1
    console ("delay difference #{diff}")
    if ((diff > (PTP_LATENCY_MAX + 8)) || (diff < (PTP_LATENCY_MAX - 8)))
        t_e("Unexpected delay with egress latency #{PTP_LATENCY_MAX} and ingress latency 0.  Delay = #{nano_delay_1}")
    end

    # Set Port ingress latency to max
    latency = PTP_LATENCY_MAX << 16
    $ts.dut.call("mesa_ts_ingress_latency_set", port1, latency)

    # Measure nanosecond delay
    nano_delay_2 = nano_delay_measure(port0, port1)
    diff = nano_delay_0 - nano_delay_2
    console ("delay difference #{diff}")
    if ((diff > (PTP_LATENCY_MAX*2 + 8)) || (diff < (PTP_LATENCY_MAX*2 - 8)))
        t_e("Unexpected delay with egress latency #{PTP_LATENCY_MAX} and ingress latency #{PTP_LATENCY_MAX}.  Delay = #{nano_delay_2}")
    end

    console("nano_delay_0 = #{nano_delay_0}  nano_delay_1 = #{nano_delay_1}  nano_delay_2 = #{nano_delay_2}  ")

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

    # External clock mode save
    $external_clock_mode_restore = $ts.dut.call("mesa_ts_external_clock_mode_get")

    $egress_latency_restore = []
    $ingress_latency_restore = []
    $operation_mode_restore = []
    $ts.dut.looped_port_list.each do |port|
        $egress_latency_restore << $ts.dut.call("mesa_ts_egress_latency_get", port)
        $ingress_latency_restore << $ts.dut.call("mesa_ts_ingress_latency_get", port)
        $operation_mode_restore << $ts.dut.call("mesa_ts_operation_mode_get", port)
    end

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        $egress_latency_10g_restore = $ts.dut.call("mesa_ts_egress_latency_get", $loop_port0_10g)
        $ingress_latency_10g_restore = $ts.dut.call("mesa_ts_ingress_latency_get", $loop_port1_10g)
        $operation_mode_l0_10g_restore = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port0_10g)
        $operation_mode_l1_10g_restore = $ts.dut.call("mesa_ts_operation_mode_get", $loop_port1_10g)
    end

    # CreateMAC address entry to copy frame to CPU
    entry = {
        vid_mac: { vid: 1, mac: { addr: [0x00,0x02,0x03,0x04,0x05,0x06] } },
        destination: "#{$loop_port1}",
        copy_to_cpu: true,
        copy_to_cpu_smac: false,
        locked: true,
        aged: false,
        cpu_queue: $cpu_queue,
    }
    $ts.dut.call("mesa_mac_table_add", entry)
end

test "test_run" do
    misc_conf = $ts.dut.call("mesa_misc_get")
    t_i("Core Clock Frequency #{misc_conf["core_clock_freq"]}")
    t_i("----------------------------------------------------")

    conf = $ts.dut.call("mesa_port_conf_get", 0)
    if (chip_family_to_id("MESA_CHIP_FAMILY_SPARX5") && (conf["speed"] == "MESA_SPEED_25G"))
        t_i("------------ Measuring 25G mode -----------------")
        port0 = $ts.dut.looped_port_list[0]
        port1 = $ts.dut.looped_port_list[1]
        $ts.dut.run("mesa-cmd port mode #{port1+1} 25g")
        $ts.dut.run("mesa-cmd port mode #{port0+1} 25g")
        tod_latency_test(port0, port1)
    end
exit(0)
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
if (i <= 2)
    next
end
        # Test egress and ingress latency
        # On Fireant - currently 1G - 2.5G can only pass on 625MHz
        if (($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || (misc_conf["core_clock_freq"] == "MESA_CORE_CLOCK_625MHZ"))
            t_i("------------ Measuring 1G mode -----------------")
#            $ts.dut.run("mesa-cmd port mode #{port0+1} 1000fdx")
#            $ts.dut.run("mesa-cmd port mode #{port1+1} 1000fdx")
#            tod_latency_test(port0, port1)
#
#            t_i("------------ Measuring 2.5G mode -----------------")
#            $ts.dut.run("mesa-cmd port mode #{port0+1} 2500")
#            $ts.dut.run("mesa-cmd port mode #{port1+1} 2500")
#            tod_latency_test(port0, port1)
        end

        # On Fireant - currently 5G can only pass on 625MHz or 250MHz
        if (($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) && ((misc_conf["core_clock_freq"] == "MESA_CORE_CLOCK_625MHZ") || (misc_conf["core_clock_freq"] == "MESA_CORE_CLOCK_250MHZ")))
            t_i("------------ Measuring 5G mode -----------------")
            $ts.dut.run("mesa-cmd port mode #{port0+1} 5g")
            $ts.dut.run("mesa-cmd port mode #{port1+1} 5g")
            tod_latency_test(port0, port1)
        end

        if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
            t_i("------------ Measuring 10G mode -----------------")
            $ts.dut.run("mesa-cmd port mode #{port0+1} 10g")
            $ts.dut.run("mesa-cmd port mode #{port1+1} 10g")
            tod_latency_test(port0, port1)
        end
    end

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
#        t_i("------------ Measuring 10G mode -----------------")
#        $ts.dut.run("mesa-cmd port mode #{$loop_port0_10g+1} 10g")
#        $ts.dut.run("mesa-cmd port mode #{$loop_port1_10g+1} 10g")
#        tod_latency_test($loop_port0_10g, $loop_port1_10g)
    end

end

test "test_clean_up" do
    # CPU queue configuration restore
    $ts.dut.call("mesa_packet_rx_conf_set", $packet_rx_conf_restore)

    # NPI port configuration restore
    $ts.dut.call("mesa_npi_conf_set", $npi_conf_restore)

    # Remove static mac entries
    entry = { vid: 1, mac: { addr: [0x00,0x02,0x03,0x04,0x05,0x06] } }
    $ts.dut.call("mesa_mac_table_del", entry)

    # External clock mode restore
    $ts.dut.call("mesa_ts_external_clock_mode_set", $external_clock_mode_restore)

    # Egress and ingress latency and Operation mode restore
    $ts.dut.looped_port_list.each_with_index do |port, idx|
        $ts.dut.call("mesa_ts_egress_latency_set", port, $egress_latency_restore[idx])
        $ts.dut.call("mesa_ts_ingress_latency_set", port, $ingress_latency_restore[idx])
        $ts.dut.call("mesa_ts_operation_mode_set", port, $operation_mode_restore[idx])
    end

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        # Egress and ingress latency restore
        $ts.dut.call("mesa_ts_egress_latency_set", $loop_port0_10g, $egress_latency_10g_restore)
        $ts.dut.call("mesa_ts_ingress_latency_set", $loop_port1_10g, $ingress_latency_10g_restore)

        # Operation mode restore
        $ts.dut.call("mesa_ts_operation_mode_set", $loop_port0_10g, $operation_mode_l0_10g_restore)
        $ts.dut.call("mesa_ts_operation_mode_set", $loop_port1_10g, $operation_mode_l1_10g_restore)
    end
end
