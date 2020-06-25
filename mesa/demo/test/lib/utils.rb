# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

def vcap_vm_set(k, name, v, fld)
    if (v != nil and v.key?(fld))
        k[name]["value"] = v[fld][:v]
        k[name]["mask"] = v[fld][:m]
    end
end

def vcap_range_set(k, name, v, fld)
    if (v != nil and v.key?(fld))
        v = v[fld]
        k = k[name]
        if (v.key?:l)
            type = "RANGE_INCLUSIVE"
            r = {}
            r["low"] = v[:l]
            r["high"] = v[:h]
            k["vr"]["r"] = r
        else
            type = "VALUE_MASK"
            k["vr"]["v"]["value"] = v[:v]
            k["vr"]["v"]["mask"] = v[:m]
        end
        k["type"] = "MESA_VCAP_VR_TYPE_#{type}"
    end
end

def vcap_bit_set(k, name, v, fld)
    if (v != nil and v.key?(fld))
        k[name] = "MESA_VCAP_BIT_#{v[fld]}"
    end
end

def ace_bit_set(k, name, v, fld)
    if (v != nil and v.key?(fld))
        k[name] = "MESA_ACE_BIT_#{v[fld]}"
    end
end

def ace_range_set(k, name, v, fld)
    if (v != nil and v.key?(fld))
        v = v[fld]
        k = k[name]
        k["in_range"] = true
        k["low"] = v[:l]
        k["high"] = v[:h]
    end
end

# def cap_check_exit(cap)
#     if (cap_get(cap) == 0)
#         Log.info("Capability '#{cap}' not present, skipping test")
#         exit
#     end
# end

def chip_family_to_id(txt)
    case txt
    when "MESA_CHIP_FAMILY_UNKNOWN"; return 0
    when "MESA_CHIP_FAMILY_CARACAL"; return 2
    when "MESA_CHIP_FAMILY_SERVAL";  return 4
    when "MESA_CHIP_FAMILY_SERVALT"; return 6
    when "MESA_CHIP_FAMILY_JAGUAR2"; return 7
    when "MESA_CHIP_FAMILY_OCELOT";  return 8
    else; Log.error("mesa_chip_family '#{txt}' not known")
    end
end

# Convert MAC address array to string
def mac_to_txt(mac)
    mac.map {|s| s.to_s(16)}.join ":"
end

# Convert IPv4 integer to string
def ipv4_to_txt(ipv4)
    IPAddr.new(ipv4, Socket::AF_INET).to_s
end

# Convert IPv6 array to string
def ipv6_to_txt(ipv6)
    txt = ""
    for i in 0..15
        txt = (txt + (i == 0 || (i & 1) == 1 ? "" : ":") + "%02x" %ipv6[i])
    end
    txt
end

MEASURE_PCP_NONE = 0xFFFF
def measure(ig, eg, size, sec=1, frame_rate=false, data_rate=false, erate=[1000000000], etolerance=[1], with_pre_tx=false, pcp=[])
    test "measure  ig: #{ig}  eg: #{eg}  size: #{size}  sec: #{sec}  frame_rate #{frame_rate}  data_rate #{data_rate}  erate #{erate}  etolerance #{etolerance}  with_pre_tx: #{with_pre_tx}  pcp #{pcp}" do

    t_i ("Check all ports are up")
    dut_ports = []
    ig.each do |ig_value|
        dut_ports << $ts.dut.p[ig_value]
    end
    dut_ports << $ts.dut.p[eg]
    if (!dut_port_state_up(dut_ports))
        t_e ("Port state is not UP")
    end

    t_i("Clear port statistics")
    $ts.dut.run("mesa-cmd port statis clear")

    t_i ("learn mac address on egress port")
    $ts.dut.run("mesa-cmd mac flush")
    $ts.pc.run("sudo ef tx #{$ts.pc.p[eg]} eth dmac 00:00:00:00:01:02 smac 00:00:00:00:01:01 ipv4 dscp 0")
#    $ts.dut.run("mesa-cmd mac dump")

    sec_count = 1000000000/8/(20+size)    # 'size' is requested frame size inclusive checksum
    t_i("Calculated frames per sec at line speed: #{sec_count}")

    pre_tx = with_pre_tx ? 1 : 0
    t_i("Start Easy Frame transmitting #{sec*sec_count} frames of size #{size} with #{pre_tx} sec of pre TX and 2 sec of post TX. Speed is 1 Gbps.")
    time = (pre_tx+sec+100)
    rep = time*sec_count
    ig_ports = ""
    pid_ef = []
    ig.each_with_index do |ig_value, ig_idx|
        if (pcp != [])
            pid_ef << $ts.pc.bg("ef tx #{pcp[ig_idx]}", "sudo ef tx #{$ts.pc.p[ig_value]} rep #{rep} eth dmac 00:00:00:00:01:01 smac 00:00:00:00:01:1#{ig_idx} ctag vid 0 pcp #{pcp[ig_idx]} data pattern cnt #{size - (6+6+4+2+4)}") # 'size' is requested frame size inclusive checksum
        else
            pid_ef << $ts.pc.bg("ef tx",                "sudo ef tx #{$ts.pc.p[ig_value]} rep #{rep} eth dmac 00:00:00:00:01:01 smac 00:00:00:00:01:1#{ig_idx} data pattern cnt #{size - (6+6+2+4)}") # 'size' is requested frame size inclusive checksum
        end
        max = 0
        begin   # Check that the transmitter is running
            icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[ig_value])
            max = max + 1
        end while (icounters["rmon"]["rx_etherStatsPkts"] == 0) && (max < 10)
        if (max == 10)
            t_e("Easy Frame transmitting never started")
        end
        ig_ports << "#{$ts.dut.p[ig_value]+1},"
    end

    t_i("Start tcpdump logging on egress port: #{$ts.pc.p[eg]}")
    pid_tcp = $ts.pc.bg("tcpdump", "tcpdump -i #{$ts.pc.p[eg]} -j adapter_unsynced -s18 -w /tmp/dump.pcap")

#    t_i("Wait for necessary amount of frames to be transmitted")
#    time1 = Time.now
#    low_count = 0
#    fail = false
#    begin
#        sleep(1)
#        time2 = Time.now
#        sec_diff = time2 - time1
#        ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])
#        if (ecounters["prio"][3]["tx"] != low_count)
#            ecounters1 = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])
#            t_i ("At sec_diff #{sec_diff} Low Priority tx detected.  count0 #{ecounters["prio"][3]["tx"]}  count1 #{ecounters1["prio"][3]["tx"]}")
#            t_i ("Port tx count0 #{ecounters["rmon"]["tx_etherStatsPkts"]}  tx count1 #{ecounters1["rmon"]["tx_etherStatsPkts"]}")
#            low_count = ecounters1["prio"][3]["tx"]
#            fail = true
#        end
#    end until (sec_diff) >= (pre_tx+sec+2)
#    if fail
#        t_e("Failed as low priority tx is counted")
#    end

    t_i("Wait for necessary amount of frames to be transmitted")
    sleep(pre_tx+sec+2)

#    $ts.dut.run("mesa-cmd mac dump")
#    $ts.dut.run("mesa-cmd port statis #{ig_ports}#{$ts.dut.p[eg]+1} pac")

    t_i("Kill the tcpdump process")
    $ts.pc.run("kill -s SIGHUP #{pid_tcp}")

    t_i("Wait for tcpdump process to terminate")
    sleep(1)  #TODO        Process.wait(pid_tcp)

    t_i("Kill Easy Frame transmitters")
    pid_ef.each do |pid|
        $ts.pc.run("kill -s SIGHUP #{pid}")
    end

    t_i("Wait for Easy Frame transmitter to complete")
    old_count = 0
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])
    max = 0
    while (ecounters["rmon"]["tx_etherStatsPkts"] != old_count) && (max < 10) do  # Check that the transmitter is running
        old_count = ecounters["rmon"]["tx_etherStatsPkts"]
        ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[eg])
        max = max + 1
    end
    if (max == 10)
        t_e("Easy Frame transmitting never completed")
    end

    t_i("Analyze pcap file")
    sec_count = 1000000000/8/((data_rate ? 0 : 20)+size)  # 'size' is requested frame size inclusive checksum
    expected_count = ""
    expected_tolerance = ""
    expected_pcp = ""
    if (pcp != [])
        pcp.each_with_index do |pcp_value, pcp_idx|
            expected_pcp << "#{pcp_value},"
            count = frame_rate ? sec*erate[pcp_idx] : sec*sec_count*erate[pcp_idx]/1000000000
            expected_count << "#{count},"
            if (count != 0) # If count is expected the tolerance is a percentage of expected count
                tolerance = ((count * etolerance[pcp_idx]) / 100) + ((((count * etolerance[pcp_idx]) % 100) != 0) ? 1 : 0)
            else            # If count is not expected then the tolerance is a number of frames
                tolerance = etolerance[pcp_idx]
            end
            expected_tolerance << "#{tolerance},"
        end
        $ts.pc.run("pcap_analyze.rb --frame-count pcp --pre-tx-sec #{pre_tx} --count-sec #{sec} --pcp_values #{expected_pcp} --exp-count #{expected_count} --exp-tolerance #{expected_tolerance} /tmp/dump.pcap")
    else
        expected_count = frame_rate ? sec*erate[0] : sec*sec_count*erate[0]/1000000000
        expected_tolerance = ((expected_count * etolerance[0]) / 100) + ((((expected_count * etolerance[0]) % 100) != 0) ? 1 : 0)
        $ts.pc.run("pcap_analyze.rb --frame-count all --pre-tx-sec #{pre_tx} --count-sec #{sec} --exp-count #{expected_count} --exp-tolerance #{expected_tolerance} /tmp/dump.pcap")
    end

    end # test
end


def default_cos2pcp(cos)
  case cos
  when 0
    return 1
  when 1
    return 0
  else
    return cos
  end
end
