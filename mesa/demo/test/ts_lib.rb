#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

MC_ADDR = [0x01,0x80,0xC2,0x00,0x00,0x30]
MC_ADDR_INV = [0x01,0x80,0xC3,0x00,0x00,0x30]
UC_ADDR = [0,0,0,0,5,6]
UC_ADDR_INV = [0,0,0,4,5,6]
MC_STRING = "01:80:C2:00:00:30"
MC_STRING_INV = "01:80:C3:00:00:30"
UC_STRING = "00:00:00:00:05:06"
UC_STRING_INV = "00:00:00:04:05:06"
SC_STRING = "00:00:00:00:05:07"

PTP_SYNC_MESSAGE = 0
PTP_SYNC_MESSAGE_LENGTH = 44
PTP_SYNC_TS_OFFSET = 34
PTP_REQUEST_MESSAGE = 1
PTP_REQUEST_MESSAGE_LENGTH = 44
PTP_RESPOND_MESSAGE = 9
PTP_RESPOND_MESSAGE_LENGTH = 54

PORT_NO_NONE = 0xFFFFFFFF
IGNORE = 0xFFFFFFFF

MESA_CHIP_FAMILY_SERVAL =  4
MESA_CHIP_FAMILY_SERVALT = 6
MESA_CHIP_FAMILY_JAGUAR2 = 7
MESA_CHIP_FAMILY_OCELOT =  8

def nano_corr_lowest_measure
    $nano_corr_loewst=0xFFFFFFFFFFFFFFFF
    $nano_corr_highest=0

    test "nano_corr_lowest_measure" do

    frame = frame_create(MC_STRING, SC_STRING)

    # Create the SYNC frame
    frametx = frame.dup + sync_pdu_create(0)
    framerx = frame.dup + sync_pdu_rx_create(0)

    for i in 0..5
        # Transmit SYNC frame into $port0
        frame_tx(frametx, $port0, "", framerx, " ", " ", 40)
        pkts = $ts.pc.get_pcap "#{$ts.links[$port1][:pc]}.pcap"
        data = pkts[0][:data].each_byte.map{|c| c.to_i}

        # Calculate the lowest correction value based on frame timestamp
        nano_correction = ((data[14+8]<<40) + (data[14+9]<<32) + (data[14+10]<<24) + (data[14+11]<<16) + (data[14+12]<<8) + (data[14+13]))
        if (nano_correction < $nano_corr_loewst)
            $nano_corr_loewst = nano_correction
        end
        if (nano_correction > $nano_corr_highest)
            $nano_corr_highest = nano_correction
        end
    end

    t_i("nano_corr_loewst = #{$nano_corr_loewst}")
    t_i("nano_corr_highest = #{$nano_corr_highest}")
    end

    $nano_corr_loewst
end

def tc_to_tod_nano(tc)
    $tod_nano_ret = 0

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        tc = tc >> 16
        test "tc_to_tod_nano  tc = #{tc}" do
    
        tod_ret  = $ts.dut.call("mesa_ts_timeofday_get")
        tod_tc = (tod_ret[1] >> 16)
        if (tod_tc < tc)
            t_i("TOD tc has wrapped. tc #{tc}  tod_tc #{tod_tc}  diff #{tc - tod_tc}")
            tod_tc += 0xFFFFFFFF    # Add 0xFFFFFFFF to TOD tc
        end
        diff_tc = tod_tc - tc
        if (diff_tc > tod_ret[0]["nanoseconds"])
            t_i("TOD nanoseconds has wrapped")
            tod_ret[0]["nanoseconds"] += (1000000000*(diff_tc/1000000000))    # Add seconds to TOD nanoseconds
        end
        $tod_nano_ret = (tod_ret[0]["nanoseconds"] - diff_tc) & 0x3FFFFFFF
    
        t_i("tc = #{tc}  tod_tc = #{tod_tc}  tod[nanoseconds] = #{tod_ret[0]["nanoseconds"]}  diff_tc = #{diff_tc}  tod_nano_ret = #{$tod_nano_ret}")
    
        end
    end
    $tod_nano_ret << 16
end

def frame_tx(frame, port, frame0, frame1, frame2, framenpi, capture_size=0)
    if (capture_size != 0)
        cap = $ts.links.collect{|x| "-c #{x[:pc]},#{capture_size},adapter_unsynced,,20"}.join(" ")
        cmd = "ef #{cap} name ftx #{frame}"
    else
        cmd = "ef name ftx #{frame}"
    end

    if ((frame0 != "") && (frame0 != " "))   # This means that frame0 received is expected
        cmd += "name frx0 #{frame0}"
    end
    if ((frame1 != "") && (frame1 != " "))   # This means that frame0 received is expected
        cmd += "name frx1 #{frame1}"
    end
    if ((framenpi != "") && (framenpi != " "))   # This means that framenpi received is expected
        cmd += "name frxn #{framenpi}"
    end

    cmd += "tx #{$ts.pc.p[port]} name ftx "

    if (frame0 != " ")  # Frame with a space means that no receive check should be done
        if (frame0 != "")   # This means that frame0 received is expected
            cmd += "rx #{$ts.pc.p[$port0]} name frx0 "
        else                # This means the no received frame is expected
            cmd += "rx #{$ts.pc.p[$port0]} "
        end
    end

    if (frame1 != " ")  # Frame with a space means that no receive check should be done
        if (frame1 != "")   # This means that frame0 received is expected
            cmd += "rx #{$ts.pc.p[$port1]} name frx1 "
        else                # This means the no received frame is expected
            cmd += "rx #{$ts.pc.p[$port1]} "
        end
    end

    if (framenpi != " ")  # Frame with a space means that no receive check should be done
        if (framenpi != "")   # This means that frame0 received is expected
            cmd += "rx #{$ts.pc.p[$npi_port]} name frxn "
        else                # This means the no received frame is expected
            cmd += "rx #{$ts.pc.p[$npi_port]} "
        end
    end

    $ts.pc.run cmd
end

def rx_ifh_extract(frame)
    $data = frame[:data].each_byte.map{|c| c.to_i}

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        ifh = $data[16..16+27]
        for i in 28..39
            ifh << 0
        end
    else
        ifh = $data[16..16+36]
        for i in 37..39
            ifh << 0
        end
    end
    ifh
end

def tx_ifh_create(port=0, ptp_act="MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ", ptp_ts=0xFEFEFEFE0000, domain=0, seq_idx=0)
    $tx_ifh = ""

    test "tx_ifh_create.  port = #{port}  ptp_act = #{ptp_act}  ptp_ts #{ptp_ts}  domain #{domain}  seq_idx #{seq_idx}" do

    tx_info = $ts.dut.call("mesa_packet_tx_info_init")
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        tx_info["dst_port"] = port
    else
        tx_info["dst_port_mask"] = (0x01 << port)
    end
    tx_info["switch_frm"] = false
    tx_info["masquerade_port"] = PORT_NO_NONE
    tx_info["frm_len"] = 12+2+PTP_SYNC_MESSAGE_LENGTH
    tx_info["pdu_offset"] = 14
    tx_info["sequence_idx"] = seq_idx
    tx_info["ptp_action"] = ptp_act
    tx_info["ptp_domain"] = domain
    tx_info["ptp_timestamp"] = ptp_ts

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        ifh = $ts.dut.call("mesa_packet_tx_hdr_encode", tx_info, 36)
    else
        if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X"))
            ifh = $ts.dut.call("mesa_packet_tx_hdr_encode", tx_info, 28)
        else
            ifh = $ts.dut.call("mesa_packet_tx_hdr_encode", tx_info, 32)
        end
    end

    $tx_ifh = "sp-jr2 dmac ff:ff:ff:ff:ff:ff smac fe:ff:ff:ff:ff:ff id #{$cap_epid} data hex #{ifh[0].take(ifh[1]).pack("c*").unpack("H*").first} "   #sp-jr2 is the same as lp-oc1 and SparX-5
    end

    $tx_ifh
end

def rx_ifh_create(port=IGNORE)
    $ifh = ""

    test "rx_ifh_create" do

    $ifh = "sp-jr2 ign id #{$cap_epid} "    #sp-jr2 is the same as lp-oc1
    if (($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SERVALT")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")))
        $ifh += "ifh-jr2 ign "
        if (port != IGNORE)
            $ifh += "f-src-port #{$port_map[port]["chip_port"]} "
        end
    end
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        $ifh += "ifh-fa ign "
        if (port != IGNORE)
            $ifh += "f-src-port #{$port_map[port]["chip_port"]} "
        end
    end
    if (($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SERVAL")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_OCELOT")))
        $ifh += "efh-oc1 ign "
    end
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X"))
        $ifh += "ifh-mas ign "
        if (port != IGNORE)
            $ifh += "src-port #{$port_map[port]["chip_port"]} "
        end
    end
    end

    $ifh
end

def frame_create(dmac, smac)
    $frame = ""

    test "frame_create.  dmac = #{dmac}  smac = #{smac}" do

    $frame = "eth dmac #{dmac} smac #{smac} et 0x88F7 "

    end

    $frame
end

def sync_pdu_create(header_rsv=0, hdr_sequenceId=0)
    $sync_pdu = ""

    test "sync_pdu_create  header_rsv #{header_rsv}" do

    $sync_pdu = "ptp-sync hdr-reserved2 #{header_rsv} hdr-sequenceId #{hdr_sequenceId} "

    end

    return $sync_pdu
end

def sync_pdu_rx_create(header_rsv=IGNORE, secondsField=IGNORE, sequenceId=IGNORE, cf_org=IGNORE, all=FALSE)
    $sync_pdu = ""

    test "sync_pdu_rx_create  header_rsv #{header_rsv} secondsField #{secondsField}" do

    $sync_pdu = "ptp-sync ign "

    if (all)
        $sync_pdu = "ptp-sync ign "
        return $sync_pdu
        $sync_pdu += "hdr-transportSpecific 0 "
        $sync_pdu += "hdr-messageType 0 "
        $sync_pdu += "hdr-reserved 0 "
        $sync_pdu += "hdr-versionPTP 0 "
        $sync_pdu += "hdr-messageLength 44 "
        $sync_pdu += "hdr-domainNumber 0 "
        $sync_pdu += "hdr-reserved1 0 "
        $sync_pdu += "hdr-flagField 0 "
        $sync_pdu += "hdr-reserved2 0 "
        $sync_pdu += "hdr-clockId 0 "
        $sync_pdu += "hdr-portNumber 0 "
        $sync_pdu += "hdr-sequenceId #{sequenceId} "
        if (secondsField != IGNORE)
            $sync_pdu += "ots-secondsField #{secondsField} "
        end
        $sync_pdu += "hdr-controlField 0 "
        $sync_pdu += "hdr-logMessageInterval 0 "
        $sync_pdu += "ots-secondsField #{seconds} "
    end

    if (header_rsv != IGNORE)
        $sync_pdu += "hdr-reserved2 #{header_rsv} "
    end
    if (sequenceId != IGNORE)
        $sync_pdu += "hdr-sequenceId #{sequenceId} "
    end
    if (secondsField != IGNORE)
        $sync_pdu += "ots-secondsField #{secondsField} "
    end
    if (cf_org != IGNORE)
        $sync_pdu += "hdr-correctionField 0 ots-secondsField 0 ots-nanosecondsField 0 "
    end

    end

    return $sync_pdu
end

def request_pdu_create(requestClockId, requestPortNumber)
    $request_pdu = ""

    test "request_pdu_create requestClockId #{requestClockId} requestPortNumber #{requestPortNumber}" do

    $request_pdu = "ptp-request hdr-clockId #{requestClockId} hdr-portNumber #{requestPortNumber} "

    end

    return $request_pdu
end

def response_pdu_rx_create(controlField=IGNORE, secondsField=IGNORE, reqClockId=IGNORE, srcClockId=IGNORE, reqPortNumber=IGNORE, srcPortNumber=IGNORE, flagField=IGNORE)
    $response_pdu = ""

    test "response_pdu_rx_create requestClockId #{controlField} #{controlField} secondsField #{secondsField} reqClockId #{reqClockId} srcClockId #{srcClockId} reqPortNumber #{reqPortNumber} srcPortNumber #{srcPortNumber} flagField #{flagField}" do

    $response_pdu = "ptp-response ign hdr-messageType #{PTP_RESPOND_MESSAGE} "
    if (flagField != IGNORE)
        $response_pdu += "hdr-flagField #{flagField} "
    end
    if (srcClockId != IGNORE)
        $response_pdu += "hdr-clockId #{srcClockId} "
    end
    if (srcPortNumber != IGNORE)
        $response_pdu += "hdr-portNumber #{srcPortNumber} "
    end
    if (controlField != IGNORE)
        $response_pdu += "hdr-controlField #{controlField} "
    end
    if (secondsField != IGNORE)
        $response_pdu += "rts-secondsField #{secondsField} "
    end
    if (reqClockId != IGNORE)
        $response_pdu += "rpi-clockId #{reqClockId} "
    end
    if (reqPortNumber != IGNORE)
        $response_pdu += "rpi-portNumber #{reqPortNumber} "
    end

    end

    if (($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) ||
        ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")))
        $response_pdu += "data repeat 6 0 "
    end

    return $response_pdu
end
