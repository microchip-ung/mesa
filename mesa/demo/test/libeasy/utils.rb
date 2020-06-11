# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'ipaddr'

def hexstr s
    ss = ""
    s.each_byte{|b| ss += ("%02x" % [b])}
    return ss
end

# Convert IPv6 address string to byte array
def ipv6_str2arr(ipv6_str)
    ipaddr = IPAddr.new ipv6_str
    ipaddr = ipaddr.hton.split(//)
    adr = []
    ipaddr.each do |x|
        adr << x.unpack("H*").first.hex
    end
    adr
end

# Convert IPv4 address string to integer
def ipv4_str2int(ipv4)
    IPAddr.new(ipv4, Socket::AF_INET).to_i
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

def port_idx_list_str(idx_list)
    str = ""
    idx_list.each do |idx|
        str += "#{$ts.dut.port_list[idx]}"
        str += "," unless idx == idx_list.last
    end
    str
end

def cap_get(cap)
    return $ts.dut.call "mesa_capability", "MESA_CAP_" + cap
end

def cap_check_exit(cap)
    check_capabilities do
        if (cap_get(cap) == 0)
            assert(false, "Capability '#{cap}' not present, skipping test")
        end
    end
end

def cmd_tag_push(tag)
    cmd = ""
    if (tag.key?:tpid and tag[:tpid] != 0)
        tpid = tag[:tpid]
        vid = ((tag.key?:vid) ? tag[:vid] : 0)
        pcp = ((tag.key?:pcp) ? tag[:pcp] : 0)
        dei = ((tag.key?:dei) ? tag[:dei] : 0)
        cmd = " et 0x#{tpid.to_s(16)} ctag vid #{vid} pcp #{pcp} dei #{dei}"
    end
    cmd
end

def cmd_rx_ifh_push(ifh={})
    # Short prefix by default (Jaguar-2 format used)
    epid = cap_get("PACKET_IFH_EPID")
    cmd = "sp-jr2 ign et 0x8880 id #{epid}"

    # Default field names
    port_name = "src-port"
    isdx_name = "isdx"
    vid_name = "vid"

    case epid
    when 5, 10
        # Serval-1/Ocelot
        cmd += " efh-oc1 ign"
    when 7, 9
        # Jaguar-2/Serval-T
        cmd += " ifh-jr2 ign"
        port_name = "f-src-port"
        isdx_name = "vm1-isdx"
        vid_name = "vt-cl-vid"
    when 11
        # FireAnt
        cmd += " ifh-fa ign"
        port_name = "f-src-port"
        isdx_name = "vm1-isdx"
        vid_name = "vt-cl-vid"
    else
        # Luton26, no prefix
        cmd = "efh-crcl ign"
    end

    if (ifh.key?:port_idx)
        # Match chip port
        port_cnt = cap_get("PORT_CNT")
        pmap = $ts.dut.call("mesa_port_map_get", port_cnt)
        port = $ts.dut.port_list[ifh[:port_idx]]
        cmd += " #{port_name} #{pmap[port]["chip_port"]}"
    end

    if (ifh.key?:vid)
        cmd += " #{vid_name} #{ifh[:vid]} "
    end

    if (ifh.key?:isdx)
        cmd += " #{isdx_name} #{ifh[:isdx]} "
    end

    cmd
end

def cmd_tx_ifh_push(info={})
    # Short prefix by default (Jaguar-2 format used)
    epid = cap_get("PACKET_IFH_EPID")
    cmd = "sp-jr2 dmac ff:ff:ff:ff:ff:ff smac fe:ff:ff:ff:ff:ff id #{epid} "
    if (epid == 0)
        # Luton26, no prefix
        cmd = ""
    end

    # Build IFH based on Tx information
    tx_info = $ts.dut.call("mesa_packet_tx_info_init")
    info.each do |key, val|
        tx_info[key.to_s] = val
    end
    # Support one egress port only via 'dst_port' field
    tx_info["dst_port_mask"] = (1 << tx_info["dst_port"])
    ifh = $ts.dut.call("mesa_packet_tx_hdr_encode", tx_info, cap_get("PACKET_TX_IFH_SIZE"))
    cmd += "data hex #{ifh[0].take(ifh[1]).pack("c*").unpack("H*").first} "
end

def ethtool_stat ts, diff = nil, ns = nil
    tot = {}

    ns_ = ""
    if ns
        ns_ = "ip netns exec #{ns}"
    end

    names = []
    ts.pc.run("#{ns_} ip link")[:out].each_line do |l|
        name = ""
        if /^\d+:\s+(\w+):/ =~ l
            name = $1
        elsif /^\d+:\s+(\w+\.\d+)@/ =~ l
            name = $1
        end
        if (ts.pc.p.include?(name))
            names << name
        end
    end

    names.each do |e|
        begin
            ts.pc.run("#{ns_} ethtool -S #{e}")[:out].each_line do |l|
                tot[e] = { "rx" => {}, "tx" => {}} if tot[e].nil?
                if /(rx|tx)_(\w+):\s+(\d+)/ =~ l
                    tot[e][$1][$2] = $3.to_i
                end
            end
        rescue
        end
    end

    return tot if diff.nil?

    res = Marshal.load(Marshal.dump(tot))
    tot.each do |ifn, rxtx|
        rxtx["rx"].each do |n, val|
            begin
                res[ifn]["rx"][n] -= diff[ifn]["rx"][n]
            rescue
            end
        end

        rxtx["tx"].each do |n, val|
            begin
                res[ifn]["tx"][n] -= diff[ifn]["tx"][n]
            rescue
            end
        end
    end

    return tot, res
end

def eval_stats actual_stat, if_list, expect_stat, tolerance = 0
    act = {}
    exp = {}
    tol = {}

    t = 0
    if expect_stat["tolerance"]
        t = expect_stat["tolerance"]
    elsif tolerance.is_a? Integer
        t = tolerance
    end

    if_list.each do |n|
        act["#{n}"] = { "rx" => 0, "tx" => 0 }
        exp["#{n}"] = { "rx" => 0, "tx" => 0 }
        tol["#{n}"] = { "rx" => t, "tx" => t }
        ["rx", "tx"].each do |x|
            if actual_stat[n][x]["packets"]
                # as returned by ethtool -S on host
                act[n][x] = actual_stat[n][x]["packets"]
            else
                raise "Could not parse actual_stat"
            end
        end
    end

    err = 0

    expect_stat.each do |k, v|
        begin
            if /([^-]+)-(rx|tx)/ =~ k
                exp[$1][$2] = v
            end
        rescue
            puts "Problem processing expect_stat #{k}"
            err += 1
        end
    end

    if tolerance.is_a? Hash
        tolerance.each do |k, v|
            begin
                if /([^-]+)-(rx|tx)/ =~ k
                    tol[$1][$2] = v
                end
            rescue
                puts "Problem processing tolerance #{k}"
                err += 1
            end
        end
    end

    txt = []
    if_list.each do |n|
        rx_act = act[n]["rx"]
        rx_exp = exp[n]["rx"]
        rx_diff = rx_act - rx_exp
        tx_act = act[n]["tx"]
        tx_exp = exp[n]["tx"]
        tx_diff = tx_act - tx_exp
        txt << "%20s | %8d %8d | %8d %8d | %8d %8d" %
          [n, rx_act, tx_act, rx_exp, tx_exp, rx_diff, tx_diff]
        err += 1 if (rx_diff).abs > tol[n]["rx"]
        err += 1 if (tx_diff).abs > tol[n]["tx"]
    end

    t_i("NIC Name               Actual rx/tx        Expected rx/tx      Difference rx/tx")
    t_i("-------------------- | -------- -------- | -------- -------- | -------- --------")
    txt.each {|l| t_i(l)}

    if err > 0
        t_e("Counter mismatch")
    end
end

def conf_func(warm)
    t_e("conf_func not implemented")
end

def frame_func
    t_e("frame_func not implemented")
end

def warm_start(ts)
    go = true
    thr1 = Thread.new do
        ts.dut.run("mesa-cmd warm start")
        conf_func(true)
        ts.dut.call("mesa_restart_conf_end")
        go = false
    end
    thr2 = Thread.new do
        while (go)
            frame_func
        end
    end
    thr1.join
    thr2.join
end

def chip_family_to_id(txt)
    case txt
    when "MESA_CHIP_FAMILY_UNKNOWN"; return 0
    when "MESA_CHIP_FAMILY_CARACAL"; return 2
    when "MESA_CHIP_FAMILY_SERVAL";  return 4
    when "MESA_CHIP_FAMILY_SERVALT"; return 6
    when "MESA_CHIP_FAMILY_JAGUAR2"; return 7
    when "MESA_CHIP_FAMILY_OCELOT";  return 8
    when "MESA_CHIP_FAMILY_SPARX5"; return 9
    else; t_e("mesa_chip_family '#{txt}' not known")
    end
end

def dut_port_state_up(ports)
    ts = Time.now.to_i
    ports.each do |port|
        loop do
            oper_up = $ts.dut.call "mesa_port_state_get", port
            break if oper_up
            if ((Time.now.to_i - ts) > 20)
                return false
            end
            sleep 1
        end
    end
    return true
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

MEASURE_PCP_NONE = 0xFFFF
def measure(ig, eg, size, sec=1, frame_rate=false, data_rate=false, erate=[1000000000], etolerance=[1], with_pre_tx=false, pcp=[], cycle_time=[])
    test "measure  ig: #{ig}  eg: #{eg}  size: #{size}  sec: #{sec}  frame_rate #{frame_rate}  data_rate #{data_rate}  erate #{erate}  etolerance #{etolerance}  with_pre_tx: #{with_pre_tx}  pcp #{pcp}  cycle_time #{cycle_time}" do

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

    sec_count_in = 1000000000/8/(20+size)    # Calculate frames per second at line speed. The ef tx function can only run at line speed. The 'size' parameter is the requested frame size inclusive checksum
    t_i("Calculated frames per sec at line speed: #{sec_count_in}")

    pre_tx = with_pre_tx ? 1 : 0    # Calculate the possible pre tx time in seconds
    t_i("Start Easy Frame transmitting #{sec*sec_count_in} frames of size #{size} with #{pre_tx} sec of pre TX and 2 sec of post TX. Speed is 1 Gbps.")
    time = (pre_tx+sec+100)     # Calculate the required seconds that the transmitter must at least (+100) be transmitting
    rep = time*sec_count_in     # Convert the required transmission seconds to number of frames, as this is the parameter to ef tx function
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
    sec_count_out = 1000000000/8/((data_rate ? 0 : 20)+size)  # This is the theoretical full rate number of outgoing frames per sec. 'size' is requested frame size inclusive checksum
    expected_count = ""
    expected_tolerance = ""
    expected_pcp = ""
    expected_cycle = (cycle_time == []) ? "" : "--exp-cycle #{cycle_time[0] / 1000}"

    if (pcp != [])
        pcp.each_with_index do |pcp_value, pcp_idx|
            sec_count = (sec_count_out*erate[pcp_idx])/1000000000   # Number of outgoing frames per sec as a fraction of the full rate count
            sec_count = (sec_count < sec_count_in) ? sec_count : sec_count_in   # Number of outgoing frames cannot be larger than the number of incoming. In case of data rate and line speed shaping this could be calculated
            expected_pcp << "#{pcp_value},"
            count = frame_rate ? sec*erate[pcp_idx] : sec*sec_count
            expected_count << "#{count},"
            if (count != 0) # If count is expected the tolerance is a percentage of expected count
                tolerance = ((count * etolerance[pcp_idx]) / 100) + ((((count * etolerance[pcp_idx]) % 100) != 0) ? 1 : 0)
            else            # If count is not expected then the tolerance is a number of frames
                tolerance = etolerance[pcp_idx]
            end
            expected_tolerance << "#{tolerance},"
        end
        $ts.pc.run("pcap_analyze.rb --frame-count pcp --pre-tx-sec #{pre_tx} --count-sec #{sec} --pcp_values #{expected_pcp} --exp-count #{expected_count} --exp-tolerance #{expected_tolerance} #{expected_cycle} /tmp/dump.pcap")
    else
        sec_count = (sec_count_out*erate[0])/1000000000   # Number of outgoing frames per sec as a fraction of the full rate count
        sec_count = (sec_count < sec_count_in) ? sec_count : sec_count_in   # Number of outgoing frames cannot be larger than the number of incomming. In case of data rate and line speed shaping this could be calculated
        expected_count = frame_rate ? sec*erate[0] : sec*sec_count
        expected_tolerance = ((expected_count * etolerance[0]) / 100) + ((((expected_count * etolerance[0]) % 100) != 0) ? 1 : 0)
        $ts.pc.run("pcap_analyze.rb --frame-count all --pre-tx-sec #{pre_tx} --count-sec #{sec} --exp-count #{expected_count} --exp-tolerance #{expected_tolerance} /tmp/dump.pcap")
    end

    end # test
end

# Wait for network interfaces to come up or down
# ts: test setup
# device: :dut or :pc
# iface: An interface or an array of interfaces. "eth1" or ["eth1","eth2","eth3"]
# timeout: time (in seconds) to wait in total
# sleep_time: time (in seconds) to wait between polls
# Add :down in flags in order to wait for the interface(s) to come down.
def wait_iface_state ts, device, iface, timeout = 10, sleep_time = 1, flags = []
    case device
    when :dut
        raise "Not yet supported on the MESA API!" if ts.dut.api == :mesa
    when :pc
    else
        raise "Invalid device!"
    end

    ni = []
    if iface.is_a? Array
        ni = iface
    else
        ni << iface
    end

    b = Time.now.to_f
    ok = []

    first = true

    while (Time.now.to_f - b) < timeout
        if first
            first = false
        else
            sleep sleep_time
        end

        ni.each do |i|
            next if ok.include? i

            res = ts.dut.run "ip link show dev #{i}"
            if /<([^>]+)>/ =~ res[:out].lines.first
                f = $1.split ","

                if flags.include? :down
                    if not f.include? "LOWER_UP"
                        ok << i
                    end
                else
                    if f.include? "LOWER_UP"
                        ok << i
                    end
                end
            end
        end

        break if ok.size == ni.size
    end

    raise "Timeout! The following interfaces are still pending: #{ni - ok}" if ok.size != ni.size
end

# Input is a string containing pairs of data such as the output from ethtool -S <device>:
# # ethtool -S eth8
# NIC statistics:
#      rx_octets: 20682
#      rx_unicast: 200
#      rx_multicast: 85
#      rx_broadcast: 0
#      .
#      .
# Each pair is here separated by "\n" and the name and counter is separated by ": "
# These are the default separators.
#
# Names and counters are converted to keys and values in a hash
#
# All incomplete pairs, e.g "NIC statistics:" which has no value, are left out by default.
# Add :keep_nil in flags in order to keep keys without values.
#
# It is possible to return all keys to symbols ("rx_octets" -> :rx_octets).
# Add :to_sym in flags in order convert all keys.
#
# All values than can be translated to an integer is done so by default.
# Add :no_int in flags in order to keep all values as strings.
#
# The string above generates a hash like this:
# {"rx_octets"=>20682, "rx_unicast"=>200, "rx_multicast"=>85, "rx_broadcast"=>0, ..}
#
# hash["eth8"]["rx_unicast"] -> 200
#
def string_pairs_to_hash str, arr_sep = "\n", key_sep = ": ", flags = []
    hash = {}
    array = str.split(arr_sep)
    array.each do |a|
        kv = a.split(key_sep)
        if flags.include? :to_sym
            k = kv[0].to_sym # Convert to symbol
        else
            k = kv[0] # Keep it as string
        end
        if flags.include? :no_int
            v = kv[1] # Keep it as string
        else
            v = Integer(kv[1]) rescue kv[1] # Convert to integer if possible
        end
        if flags.include? :keep_nil
            hash[k] = v # Add everything including nil values
        else
            hash[k] = v if not v.nil? # Add everything but nil values
        end
    end
    return hash
end

# Get interface statistics and return them in a hash
# ts: test setup
# device: :dut or :pc
# iface: An interface or an array of interfaces. "eth1" or ["eth1","eth2","eth3"]
# prev: Previous statistics for making diffs (optional)
# If present, prev is expected to be generated with the same interfaces(s)
# Output is a hash like this
# {"eth1"=>{"rx_octets"=>200, "rx_unicast"=>2, "rx_multicast"=>1, "rx_broadcast"=>0, ..},
#  "eth2"=>{"rx_octets"=>4000, "rx_unicast"=>20, "rx_multicast"=>5, "rx_broadcast"=>1, ..}}
def get_iface_statistics ts, device, iface, prev = nil
    case device
    when :dut
        raise "Not yet supported on the MESA API!" if ts.dut.api == :mesa
    when :pc
    else
        raise "Invalid device!"
    end

    ni = []
    if iface.is_a? Array
        ni = iface
    else
        ni << iface
    end

    stat = {}
    diff = {}
    ni.each do |i|
        s = ts.pc.run "ethtool -S #{i}" if device == :pc
        s = ts.dut.run "ethtool -S #{i}" if device == :dut
        h = string_pairs_to_hash s[:out]
        stat[i] = h
        if not prev.nil?
            diff[i] = prev[i].merge(h) {|k, o, n| n - o}
        end
    end
    if prev.nil?
        return stat
    else
        return stat, diff
    end
end

# percent deviation between actual and expected
# returns true if deviation is within limit
def percent_deviation act, exp, dev
    pct = (act.to_f - exp.to_f) * 100 / exp.to_f
    return (pct.abs <= dev.to_f)
end

# absolute deviation between actual and expected
# returns true if deviation is within limit
def absolute_deviation act, exp, dev
    diff = act.to_f - exp.to_f
    return (diff.abs <= dev.to_f)
end

# Evaluate statistics counters
# Use the output from get_iface_statistics
# Counters not mentioned in expect is expected to be zero.
# Add :ignore in flags in order to ignore counters not mentioned.
#
# The following formats are supported in the expected values:
#  A literal integer:     2000
#  String interpolation: "#{NUMBER * 2}"
#  Absolute deviation:   "2000 +- 30"
#  Deviation in percent: "2000 +- 10 %"
#  A logical expression: "2000 <= %a and %a <= 3000 and %a != 2345"
#                        where %a is a placeholder for the actual value:
# Expect format example:
# {"eth1"=>{"rx_octets"=>200, "rx_unicast"=>"#{NUM}", "rx_multicast"=>"2000 +- 30"},
#  "eth2"=>{"rx_octets"=>"2000 <= %a and %a <= 3000 and %a != 2345", "rx_unicast"=>"2000 +- 10 %"}}
#
def eval_statistics actual, expect, flags = []
    err = 0
    remaining = {}

    actual.each do |dev, stat|
        stat.each do |k, v|
            if expect[dev].nil? || expect[dev][k].nil?
                remaining[dev] = {} if remaining[dev].nil? # Create first level hash
                remaining[dev][k] = v if not flags.include? :ignore
            else
                e = expect[dev][k]
                if e.is_a? String and e.match('\A\s*(\d+)\s*\Z')
                    # This String is a single integer - convert it to an Integer
                    e = Integer(e)
                end

                if e.is_a? String
                    s = e.gsub("%a", "#{v}") # Replace placeholder with actual for use with eval
                    if e.match('\A\s*(\d+)\s*\+-\s*(\d+)\s*\Z') # Match on e.g. '2000 +- 30'
#                        t_i "Match #{e} #{$1} #{$2} abs"
                        t_e "ERROR: #{dev} #{k}: Actual = #{v} is not #{e}!" if not absolute_deviation(v, $1, $2)
                        err += 1
                    elsif e.match('\A\s*(\d+)\s*\+-\s*(\d+)\s*%\s*\Z') # Match on e.g. '2000 +- 10 %'
#                        t_i "Match #{e} #{$1} #{$2} pct"
                        t_e "ERROR: #{dev} #{k}: Actual = #{v} is not #{e}!" if not percent_deviation(v, $1, $2)
                        err += 1
                    elsif eval("(#{s})") == false # E.g. eval (100 < %a and %a < 300) returned false
                        t_e "ERROR: #{dev} #{k}: Actual = #{v}. Expected (#{s}) is false!"
                        err += 1
                    else # E.g. eval (100 < %a and %a < 300) returned true
#                        t_i "Match #{e} (#{s})"
                    end
                else # Integer
                    if v != e
                        t_e "ERROR: #{dev} #{k}: Actual = #{v}. Expected #{e}!"
                        err += 1
                    end
                end
            end
        end
    end

    remaining.each do |dev, stat|
        stat.each do |k, v|
            if v > 0
                t_e "ERROR: #{dev} #{k}: Actual = #{v}. Expected 0!"
                err += 1
            end
        end
    end
    return err
end

def dl_file uri, out
    FileUtils.mkdir_p File.dirname(out)
    puts "Downloading #{uri} to #{out}"
    IO.write(out, Net::HTTP.get(URI(uri)))
end

def run_(cmd, verify=true)
    puts "Executing #{cmd}"
    res = system cmd
    if verify
        raise "Running '#{cmd}' failed" if $? != 0
    end
    res
end

