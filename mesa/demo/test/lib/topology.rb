#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

# Check for command line args and add as a hash key.
# Currently '--no-frame' and '--no-init' supported for warm-start testing with external frame genarator.
$args = Hash[ ARGV.join(' ').scan(/--?([^=\s]+)(?:=(\S+))?/) ]

class Dut
    attr_accessor :mport
    attr_accessor :ip_addr
    attr_accessor :ip_mask
    attr_accessor :gateway
    attr_accessor :console
    attr_accessor :port_list
    attr_accessor :hp_list
    attr_accessor :if_list
    attr_accessor :cli
    attr_accessor :conf_func
    attr_accessor :frame_func
    attr_accessor :warm_start
    attr_accessor :go

    def initialize
        @mport = nil
        @ip_addr = nil
        @ip_mask = nil
        @gateway = nil
        @console = nil
        @port_list = []
        @hp_list = []
        @if_list = []
        @cli = nil
        @conf_func = nil
        @frame_func = nil
        @warm_start = false
        @go = false
    end
end

$dut = Dut.new

def conf_func
    Log.error("conf_func not implemented")
end

def frame_func
    Log.error("frame_func not implemented")
end

$go = false
def warm_start
    $go = true
    thr1 = Thread.new do
        $dut.cli.cmd("cli warm start")
        $dut.warm_start = true
        conf_func
        $dut.warm_start = false
        send_req("mesa_restart_conf_end")
        $go = false
    end
    thr2 = Thread.new do
        while ($go)
            frame_func if !$args.key?("no-frame")
        end
    end
    thr1.join
    thr2.join
end

def dut_test
    # Normal test
    conf_func  if !$args.key?("no-init")
    frame_func if !$args.key?("no-frame")

    # Warm start test
    #warm_start

    Log.info("Number of error messages: #{Log.error_cnt}")
end

$file = nil
begin
    $file = File.new("topology.txt", "r")
rescue
    Log.info("topology.txt not found")
end

begin
    if $file.nil?
        $file = File.new(ENV['HOME'] + "/.vtss_sw_test_topology")
    end
rescue
    Log.info("vtss_sw_test_topology not found")
end

if $file.nil?
    Log.error("no topology file found")
    exit
end

$file.each do |line|
    #puts "line: #{line}"
    a = line.split("=")

    # Key
    key = a[0]
    k = key.split(".")

    # Value
    val = a[1]
    v = (val ? val.split(",") : nil)
    port = (v and v[1] ? v[1].to_i : nil)
    
    case k[0]
    when "dut0"
        case k[1]
        when "mgmt"
            case k[2]
            when "port"
                if (port)
                    $dut.mport = port
                end
                
            when "ip"
                v = val.split("/")
                $dut.ip_addr = v[0]
                mask = v[1]
                if (mask.split(".").length == 1)
                    # Support for prefix length notation, e.g. 1.2.3.4/24
                    len = mask.to_i
                    m = 0
                    for i in 0..31
                        if ((i + len) >= 32)
                            m += (1 << i)
                        end
                    end
                    mask = "#{(m >> 24) & 0xff}.#{(m >> 16) & 0xff}.#{(m >> 8) & 0xff}.#{m & 0xff}"
                end
                $dut.ip_mask = mask
                
            when "gateway"
                $dut.gateway = val
            end
            
        when "console"
            $dut.console = val
        else
            if (k[1][0] == "p" && v[1])
                # E.g. "dut0.p3"
                $dut.port_list[k[1][1].to_i] = port
            end
        end
        
    when "host"
        if (k[1][0] == "p" and k.length == 2)
            # E.g. "host.p2"
            $dut.hp_list[k[1][1].to_i] = val.gsub("\n", "")
        end
    end
end

def check_parm_valid(name, parm, required = true, count = 0)
    if (parm.nil?)
        if (required)
            Log.error("topology #{name} not found")
            exit
        end
    elsif (count > 0)
        cnt = parm.count { |x| x != nil }
        if (count > cnt)
            Log.error("#{name} must have at least #{count} elements")
            exit
        end
    end
    t_i "#{name}: #{parm}"
end

def demo_start
    test "demo_start" do
        check_parm_valid("mport", $dut.mport)
        check_parm_valid("ip_addr", $dut.ip_addr)
        check_parm_valid("ip_mask", $dut.ip_mask)
        check_parm_valid("gateway", $dut.gateway)
        check_parm_valid("console", $dut.console)
        check_parm_valid("port_list", $dut.port_list, false, 4)
        check_parm_valid("hp_list", $dut.hp_list, false, 4)

        # Connect to DUT and start demo application
        cli = Cli.new($dut.console)
        uport = $dut.mport + 1
        if !$args.key?("no-init") and !$args.key?("no-startup")
            if_name = "vtss.port.#{uport}"
            cli.cmd("mesa-cmd exit")
            cli.cmd("ip link del #{if_name}")
            sleep(1)
            cli.cmd("mesa-demo -p #{uport} -t port:def:info -t api_ail:def:info")
            sleep(10)
            cli.cmd("ifconfig #{if_name} #{$dut.ip_addr} netmask #{$dut.ip_mask}")
            cli.cmd("route add default gw #{$dut.gateway}")
            cli.cmd("ping -c 1 #{$dut.gateway}")
        end
        $dut.cli = cli
    end
end

def port_list_str(port_list)
    str = ""
    port_list.each do |port|
        str += "#{port}"
        str += "," unless port == port_list.last
    end
    str
end

def port_idx_list_str(idx_list)
    str = ""
    idx_list.each do |idx|
        str += "#{$dut.port_list[idx]}"
        str += "," unless idx == idx_list.last
    end
    str
end

# Convert IPv6 address string to dotted decimal string
def ipv6_str2oct(ipv6_str)
    addr = IPAddr.new(ipv6_str)
    a = addr.to_string.split(":")
    str = ""
    a.each_with_index do |x, i|
        y = x.to_i(16)
        str += "#{i == 0 ? "" : "."}#{y >> 8}.#{y & 0xff}"
    end
    str
end

# Get length of IFH including any prefix header
def ifh_len_get(cmd = 3)
    len = 0
    if ((cmd & 1) != 0)
        len += (cap_get("MEP_LUTON26") == 0 ? 16 : 0)
    end
    if ((cmd & 2) != 0)
        len += cap_get("PACKET_RX_IFH_SIZE")
    end
    len
end

demo_start
