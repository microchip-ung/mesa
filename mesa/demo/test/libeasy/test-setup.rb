#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'uri'
require 'json'
require 'open3'
require 'socket'
require "base64"
require 'net/http'
require "packetfu"
require 'yaml'

class CliIO
    attr_accessor :timeout

    def initialize scheme, istream, ostream
        @scheme = scheme
        @input_buf = ""
        @timeout = 5
        @istream = istream
        @ostream = ostream
        @delim = "#"
    end

    def sanitize_line l
        stack = []
        l.each_byte do |b|
            case b
            when 8
                stack.pop
            else
                stack << b
            end
        end

        return stack.pack("c*")
    end

    def poll_stdin_ timeout_ = nil
        to = @timeout
        if timeout_
            to = timeout_
        end

        rs, ws = IO.select([@istream], [], [], to)
        if rs != nil and r = rs[0]
            x = r.read_nonblock(128)
            @input_buf << x
            return true
        else
            return false
        end
    end

    def poll_stdin timeout_ = nil
        to = @timeout
        if timeout_
            to = timeout_
        end

        if poll_stdin_ to
            @input_buf = sanitize_line @input_buf
            return true
        end
        return false
    end

    def pop_line
        case @scheme
        when "easytest"
            o = @input_buf.partition("\n")
        when "telnet", "termhub"
            o = @input_buf.partition("\r\n")
        else
            raise "scheme not supported"
        end
        if o[1].size >= 1
            @input_buf = o[2]
            return o[0]
        else
            return nil
        end
    end

    def read_one_line
        while true do
            l = pop_line
            if l.nil?
                if !poll_stdin
                    return nil
                end
            else
                return l
            end
        end
    end

    def read_line_expect_end pattern
        while true
            while l = pop_line
                yield l
            end

            if @input_buf.match pattern
                @input_buf = ""
                return true
            end

            if !poll_stdin
                raise "pattern not found"
            end
        end
    end

    def flush_input
        poll_stdin 0.1
        x = @input_buf
        @input_buf = ""
        return x
    end

    def send s
        @ostream.print s + "\r"
        @ostream.flush
    end

    def write s
        @ostream.write s
        @ostream.flush
    end

    def send_return
        @ostream.print "\r"
        @ostream.flush
    end

    def cmd_delim s
        @delim = s
    end

    def send_break
        if @scheme == "telnet"
            @ostream.write [0xff, 0xf3].pack("C*")
            @ostream.flush
        else
            @ostream.write "\x1b[24~"
            @ostream.flush
        end
        sleep 0.1
    end

    def sysrq cmd
        send_break
        @ostream.write(cmd)
        @ostream.flush
    end

    def cmd s
        send s
        r = []
        first = true
        read_line_expect_end @delim do |l|
            r << l
            if not first
                yield l if block_given?
            end
            first = false
        end

        return r.drop(1)
    end
end


def method_apply_result method, status
    if status != 0
        case method
        when "run"
            raise TestAbortException, ""   # Mark failed test as failed and stop test execution
        when "try"
            $test_stack[-1][:cnt_err] += 1 # Mark failed test as failed and continue
        end
    else
        case method
        when "try_err"
            $test_stack[-1][:cnt_err] += 1 # Mark passed test as failed and continue
        when "run_err"
            raise TestAbortException, ""   # Mark failed test as failed and stop test execution
        end

    end
end


class MesaDut
    attr_accessor :api, :p, :port_list, :looped_port_list, :looped_port_list_10g, :io, :port_admin, :pcb

    def initialize api, url, ports, looped_ports, looped_ports_10g, port_admin, pcb
        @api = api
        @p = ports
        @port_list = ports
        @looped_port_list = looped_ports
        @looped_port_list_10g = looped_ports_10g
        @port_admin = port_admin
        @pcb = pcb
        @dut_term = URI(url)
        @stream = TCPSocket.open(@dut_term.host, @dut_term.port)

        if @dut_term.scheme == "telnet"
            @stream.write [0xff, 0xfb, 0x03, 0xff, 0xfd, 0x03, 0xff, 0xfd, 0x01].pack("C*")
            IO.select([@stream], nil, nil, 1)
            @stream.recv_nonblock 1024
        end

        @io = CliIO.new @dut_term.scheme, @stream, @stream
        @buf = []
        @background_jobs = {}
    end

    def mute
        @io.send "stty -echo"
        @io.flush_input
        @io.send "export PS1=\"\""
        @io.send "export PS2=\"\""
        @io.send "export PS3=\"\""
        @io.send "export PS4=\"\""
        @io.flush_input
    end

    def unmute
        @io.send "stty echo"
        @io.send "export PS1=\"# \""
        @io.send "export PS2=\"> \""
        @io.send "echo done"
        @io.flush_input
    end

    # Run cli command. Stop test if error.
    def run cmd, *args
        execute cmd, "run", *args
    end

    def run_err cmd
        execute cmd, "run_err"
    end

    # Run cli command wrapped with json. Stop test if error.
    def call cmd, *args
        call_execute cmd, "run", *args
    end

    # Same as 'call' but expect an error.
    def call_err cmd, *args
        call_execute cmd, "run_err", *args
    end

    # Same as 'call' but don't stop if error.
    def try cmd, *args
        call_execute cmd, "try", *args
    end

    # Same as 'try' but expect an error.
    def try_err cmd, *args
        call_execute cmd, "try_err", *args
    end

    # Same as 'try' but ignore errors and always report the test as passed.
    def try_ignore cmd, *args
        call_execute cmd, "try_ignore", *args
    end

    def sw_reboot(cnt = 10)
        @io.sysrq("b")
        @io.send "\nres\n" # in case we are in uboot

        redboot = false
        while l = @io.read_one_line
            console l

            case l
            when /U-Boot/
                break
            when /RedBoot/
                redboot = true
                break
            when /b: not found/ #in case sysrq("b") fails
                if (cnt > 0)
                    sw_reboot(cnt - 1)
                else
                    @io.send "\nreboot\n" # if in Linux and sysrq not working
                end
                return
            when /b: command not found/ #in case sysrq("b") fails
                @io.send "\necho 'b' > /proc/sysrq-trigger\n" # in case we are in qemu
                return
            end
        end

        if redboot
            t_d "Doing a RedBoot ramload - BE AWARE NEW IMAGE MAY NOT BE LOADED"
            while l = @io.read_one_line
                console l

                case l
                when /Executing boot script in/
                    break
                else
                end
            end

            @io.write [3].pack("c")
            sleep 0.1
            @io.send "ramload"
        end

    end

    def linux_login
        @io.timeout = 300
        @io.read_line_expect_end /login:/ do |l|
            console l
        end

        @io.timeout = 1
        @io.send "root"
        @io.read_line_expect_end /#/ do |l|
            console l
        end
        @io.cmd "echo 4 > /proc/sys/kernel/printk"
    end

    def terminal_alive timeout
        @io.timeout = timeout
        @io.read_one_line
    end

    def poll_input
        # TODO, this should run in a background thread
        @io.poll_stdin_

        while l = @io.pop_line
            ts_now = Time.now
            msg = nil
            case l
            when /ER-M-(\d+)-(\d+\.\d+)-RUN\s+(.*)/
                msg = {:type => :run, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDOUT\s+(.*)/
                msg = {:type => :out, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDERR\s+(.*)/
                msg = {:type => :err, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDIN\s+(.*)/
                msg = {:type => :in, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            when /ER-M-(\d+)-(\d+\.\d+)-EXIT\s+(.*)/
                msg = {:type => :res, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            else
                # none-matched lines are matched as console messages in the xml
                # stream
                console l
            end

            next if msg.nil?

            bg_job = @background_jobs[msg[:pid]]
            if bg_job.nil?
                @buf << msg
                next
            end

            # Sink output from background processes to the XML stream such that
            # we can easily see where the messages was emitted
            ts_begin = bg_job[:ts_begin]
            ts = ts_begin + msg[:ts]
            attrs = {"pid" => msg[:pid], "name" => bg_job[:name], "on" => bg_job[:on], "ts_rel" => xml_ts_diff(ts_begin, ts), "ts" => xml_ts(ts)}

            case msg[:type]
            when :out
                xml_tag "bg_stdout", msg[:data], attrs
                bg_job[:out] += msg[:data]

            when :err
                xml_tag "bg_stderr", msg[:data], attrs
                bg_job[:err] += msg[:data]

            when :in
                # Does this make any sense??
                xml_tag "bg_stdin", msg[:data], attrs

            when :res
                attrs["exitstatus"] = msg[:data].to_i
                xml_tag "bg_end", nil, attrs
                bg_job[:res] = msg[:data].to_i
            end
        end
    end

    def pid_for_cmd cmd
        # Search for PID
        while true
            poll_input
            i = @buf.index {|l| l[:type] == :run}

            if i
                res = @buf[i]
                @buf.delete_at i
                return res
            end
        end
    end

    def poll_cmd_output pid
        res = []

        poll_input

        i = @buf.reject! do |l|
            if l[:pid] == pid or l[:type] == :other
                res << l
                true
            else
                false
            end
        end

        return res
    end

    def bg name, cmd, flags = []
        # Issue the command
        @io.send "er -b -l /tmp/console-er -- #{cmd}"

        pid = pid_for_cmd cmd
        ts_begin = Time.now
        xml_tag "bg", nil, {"on" => "dut", "name" => name, "cmd" => cmd, "ts" => xml_ts(ts_begin), "pid" => pid[:pid]}
        @background_jobs[pid[:pid]] = {:ts_begin => ts_begin, :out => "", :err => "", :in => "", :name => name, :on => "dut"}

        return pid
    end

    def bg_sink pid
        raise "not implemented"
    end

    def execute cmd, method, stdin = nil
        # Issue the command
        if stdin
            lines64 = Base64.encode64(stdin + "\n").split "\n"
            @io.send "base64decode /tmp/input-buf"
            lines64.each do |l|
                @io.send l
            end
            @io.send ""
            @io.send ""
            @io.send "er -l /tmp/console-er -- sh -c \"#{cmd}\" < /tmp/input-buf"
        else
            @io.send "er -l /tmp/console-er -- sh -c \"#{cmd}\""
        end

        pid = pid_for_cmd cmd

        ts_begin = Time.now
        xml_tag_start "#{method}", {"on" => "dut", "cmd" => cmd, "ts" => xml_ts(ts_begin),
                                    "pid" => pid[:pid]}
        res_out = ""
        res_err = ""

        while true
            t = poll_cmd_output(pid[:pid])

            t.each do |l|
                yield l if block_given?

                ts = ts_begin + (l[:ts] - pid[:ts])
                attrs = {"pid" => pid[:pid], "ts_rel" => xml_ts_diff(ts_begin, ts),
                         "ts" => xml_ts(ts), "on" => "dut"}

                case l[:type]
                when :out
                    data = (l[:data] + "\n")
                    xml_tag "#{method}_stdout", data, attrs
                    res_out += data
                when :err
                    xml_tag "#{method}_stderr", l[:data], attrs
                    res_err += l[:data]
                when :in
                    xml_tag "#{method}_stdin", l[:data], attrs
                when :res
                    attrs["exitstatus"] = l[:data].to_i
                    xml_tag "#{method}_end", nil, attrs
                    xml_tag_end "#{method}"
                    method_apply_result method, attrs["exitstatus"]
                    return { :out => res_out, :err => res_err, :res => l[:data].to_i }
                end
            end
        end
    end

    def call_execute cmd, method, *args
        t_d "#{__LINE__}: #{cmd} #{args.to_json.to_s.size}"
        cli = (cmd.start_with?("mera") ? "mera" : "mesa")
        res = execute "#{cli}-cmd -i call #{cmd}", method, args.to_json

        if res[:res] > 0
            o = {}
        else
            j = JSON.parse(res[:out])
            o = j["result"].reject{|x| x.nil? }
        end

        if o.size == 0
            return nil
        elsif o.size == 1
            return o[0]
        else
            return o
        end
    end
end

class TestPCRemote
    attr_accessor :p

    def initialize url, ports, easytest_server
        @p = ports
        @dut_term = URI(url)
        @stream = TCPSocket.open(@dut_term.host, @dut_term.port)
        @io = CliIO.new "easytest", @stream, @stream
        @buf = []
        @background_jobs = {}
        @easytest_server = easytest_server
    end

    def poll_input
        @io.poll_stdin_

        while l = @io.pop_line
            puts l
            ts_now = Time.now
            msg = nil
            case l
            when /ER-M-(\d+)-(\d+\.\d+)-RUN\s+(.*)/
                msg = {:type => :run, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDOUT\s+(.*)/
                msg = {:type => :out, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDERR\s+(.*)/
                msg = {:type => :err, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDIN\s+(.*)/
                msg = {:type => :in, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            when /ER-M-(\d+)-(\d+\.\d+)-EXIT\s+(.*)/
                msg = {:type => :res, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

            else
                # none-matched lines are matched as console messages in the xml
                # stream
                console l
            end

            next if msg.nil?

            bg_job = @background_jobs[msg[:pid]]
            if bg_job.nil?
                @buf << msg
                next
            end

            # Sink output from background processes to the XML stream such that
            # we can easily see where the messages was emitted
            ts_begin = bg_job[:ts_begin]
            ts = ts_begin + msg[:ts]
            attrs = {"pid" => msg[:pid], "name" => bg_job[:name], "on" => bg_job[:on], "ts_rel" => xml_ts_diff(ts_begin, ts), "ts" => xml_ts(ts)}

            case msg[:type]
            when :out
                xml_tag "bg_stdout", msg[:data], attrs
                bg_job[:out] += msg[:data]

            when :err
                xml_tag "bg_stderr", msg[:data], attrs
                bg_job[:err] += msg[:data]

            when :in
                # Does this make any sense??
                xml_tag "bg_stdin", msg[:data], attrs

            when :res
                attrs["exitstatus"] = msg[:data].to_i
                xml_tag "bg_end", nil, attrs
                bg_job[:res] = msg[:data].to_i
            end
        end
    end

    def pid_for_cmd cmd
        # Search for PID
        while true
            poll_input
            i = @buf.index {|l| l[:type] == :run}

            if i
                res = @buf[i]
                @buf.delete_at i
                return res
            end
        end
    end

    def poll_cmd_output pid
        res = []

        poll_input

        i = @buf.reject! do |l|
            if l[:pid] == pid or l[:type] == :other
                res << l
                true
            else
                false
            end
        end

        return res
    end


    # Run cli command. Stop test if error.
    def run cmd
        execute cmd, "run"
    end

    # Same as 'run' but expect an error.
    def run_err cmd
        execute cmd, "run_err"
    end

    # Same as 'run' but don't stop if error.
    def try cmd
        execute cmd, "try"
    end

    # Same as 'try' but expect an error.
    def try_err cmd
        execute cmd, "try_err"
    end

    # Same as 'try' but ignore errors and always report the test as passed.
    def try_ignore cmd
        execute cmd, "try_ignore"
    end

    def bash_function cmd
        @io.write "#{cmd}\n"
    end

    def execute cmd, method
        #t_i "IO-Write: er -l ./.er.lock -- #{cmd}"
        @io.write "er -l ./.er.lock -- #{cmd}\n"
        #t_i "IO-Write: done"

        pid = pid_for_cmd cmd

        ts_begin = Time.now
        xml_tag_start "#{method}", {"on" => "pc-remote", "cmd" => cmd, "ts" => xml_ts(ts_begin),
                                    "pid" => pid[:pid]}
        res_out = ""
        res_err = ""

        while true
            t = poll_cmd_output(pid[:pid])

            t.each do |l|
                yield l if block_given?

                ts = ts_begin + (l[:ts] - pid[:ts])
                attrs = {"pid" => pid[:pid], "ts_rel" => xml_ts_diff(ts_begin, ts),
                         "ts" => xml_ts(ts), "on" => "dut"}

                case l[:type]
                when :out
                    data = (l[:data] + "\n")
                    xml_tag "#{method}_stdout", data, attrs
                    res_out += data
                when :err
                    xml_tag "#{method}_stderr", l[:data], attrs
                    res_err += l[:data]
                when :in
                    xml_tag "#{method}_stdin", l[:data], attrs
                when :res
                    attrs["exitstatus"] = l[:data].to_i
                    xml_tag "#{method}_end", nil, attrs
                    xml_tag_end "#{method}"
                    method_apply_result method, attrs["exitstatus"]
                    return { :out => res_out, :err => res_err, :res => l[:data].to_i }
                end
            end
        end
    end

    def bg name, cmd, flags = []
        @io.write "er -l ./.er.lock -b -- #{cmd}\n"

        pid = pid_for_cmd cmd
        ts_begin = Time.now
        xml_tag "bg", nil, {"on" => "pc-remote", "name" => "#{name}-#{pid[:pid]}", "cmd" => cmd, "ts" => xml_ts(ts_begin), "pid" => pid[:pid]}
        @background_jobs[pid[:pid]] = {:ts_begin => ts_begin, :out => "", :err => "", :in => "", :on => "dut"}

        return pid[:pid]
    end

    def get name
        src_url = URI("http://#{@easytest_server}/ws/#{name}")
        res = Net::HTTP.get_response(src_url)

        if res.code.to_i == 200
            t_i "Download #{res.body.size} bytes from #{src_url}"
            return res.body
        else
            raise "Failed to download: #{src_url} -> #{res.code}"
        end
    end

    def get_pcap name
        d = get(name)
        pcap = PacketFu::PcapFile.new.read d
        ts_start = 0
        ts_prev = 0
        a = pcap[:body].map do |p|
            us = 0
            us += p[:timestamp][:sec][:value] * 1000000
            us += p[:timestamp][:usec][:value]
            ts_start = us if ts_start == 0
            ts_prev = us if ts_prev == 0
            ts_delta = us - ts_prev
            ts_prev = us
            {:us => us, :us_rel => us - ts_start, :us_delta => ts_delta, :len_on_wire => p[:orig_len][:value], :data => p[:data]}
        end

        return a
    end
end

class TestPC
    attr_accessor :p

    def initialize ports
        @p = ports
    end

    # Run cli command. Stop test if error.
    def run cmd
        execute cmd, "run"
    end

    # Same as 'run' but expect an error.
    def run_err cmd
        execute cmd, "run_err"
    end

    # Same as 'run' but don't stop if error.
    def try cmd
        execute cmd, "try"
    end

    # Same as 'try' but expect an error.
    def try_err cmd
        execute cmd, "try_err"
    end

    # Same as 'try' but ignore errors and always report the test as passed.
    def try_ignore cmd
        execute cmd, "try_ignore"
    end


    def execute cmd, method

        c = "er -- #{cmd}"
        ts_begin = Time.now
        pid = nil
        res_out = ""
        res_err = ""

        Open3::popen2(c) do |i, o, t|
            i.close
            o.each do |l|
                ll = nil

                case l
                when /ER-M-(\d+)-(\d+\.\d+)-RUN\s+(.*)/
                    ll = {:type => :run, :pid => $1.to_i, :ts => $2.to_f, :data => $3}
                    pid = ll[:pid]

                when /ER-[LC]-(\d+)-(\d+\.\d+)-STDOUT\s+(.*)/
                    ll = {:type => :out, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

                when /ER-[LC]-(\d+)-(\d+\.\d+)-STDERR\s+(.*)/
                    ll = {:type => :err, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

                when /ER-[LC]-(\d+)-(\d+\.\d+)-STDIN\s+(.*)/
                    ll = {:type => :in, :pid => $1.to_i, :ts => $2.to_f, :data => $3}

                when /ER-M-(\d+)-(\d+\.\d+)-EXIT\s+(.*)/
                    ll = {:type => :res, :pid => $1.to_i, :ts => $2.to_f, :data => $3}
                else
                    t_d l
                end

                next if pid.nil? or ll[:pid] != pid

                ts = ts_begin + ll[:ts]
                attrs = {"pid" => pid, "ts_rel" => xml_ts_diff(ts_begin, ts), "ts" => xml_ts(ts)}

                case ll[:type]
                when :run
                    attrs["on"] = "pc"
                    attrs["cmd"] = cmd
                    xml_tag_start "#{method}", attrs
                when :out
                    xml_tag "#{method}_stdout", ll[:data], attrs
                    res_out += ll[:data]
                when :err
                    xml_tag "#{method}_stderr", ll[:data], attrs
                    res_err += ll[:data]
                when :in
                    xml_tag "#{method}_stdin", ll[:data], attrs
                when :res
                    attrs["exitstatus"] = ll[:data].to_i
                    xml_tag "#{method}_end", nil, attrs
                    xml_tag_end "#{method}"
                    method_apply_result method, attrs["exitstatus"]
                    return { :out => res_out, :err => res_err, :res => ll[:data].to_i }
                end
            end
        end
    end

end

def upload_utils conf
    path = File.expand_path(File.dirname(__FILE__))
    path = File.expand_path("#{path}/../utils")
    out_r, out_w  = IO.pipe
    opts = { :in => :close,
             :out => out_w,
             :err => $stderr,
             :chdir => path,
    }

    pid = Process.spawn("tar -C #{path} -czf - .", opts)
    out_w.close
    t = Process.detach pid
    out_r.binmode
    data = out_r.read
    t.join
    out_r.close
    raise "tar exit code: #{t.value}" if t.value != 0

    uri = URI.parse("http://#{conf["easytest_server"]}/utils");
    request = Net::HTTP::Post.new(uri)
    request.body = data
    response = Net::HTTP.start(uri.hostname, uri.port) do |http|
        res = http.request(request)
    end

    if response.code.to_i != 200
        puts "Error uploading utils: #{response.code}"
        if response.body
            puts "Message: #{response.body}"
        end
    end

end

$easyframes_sha = "e922a34e1778e60be322ef7c3f54d3fac68e03c7"

class Switchdev_Pc_b2b_4x
    attr_accessor :dut, :pc, :links, :vinst, :vconn, :ts_external_clock_looped, :port_admin

    def initialize conf, mesa_args
        dut_url = conf["dut"]["terminal"]
        dut_args = conf["dut"]["mesa_demo_args"]
        dut_ports = conf["dut"]["ports"]
        dut_looped_ports = conf["dut"]["looped_ports"]
        pc_ports = conf["pc"]["ports"]
        port_admin = conf["dut"]["port_admin"]
        pcb = conf["dut"]["pcb"]
        dut_looped_ports_10g = conf["dut"]["looped_ports_10g"]
        dut_ports_sd = []
        dut_looped_ports_sd = []
        map = conf["dut"]["port-name-map"]
        map.each do |item|
            if dut_ports.include? item["idx"]
                dut_ports_sd << item["linux"]
            elsif dut_looped_ports.include? item["idx"]
                dut_looped_ports_sd << item["linux"]
            elsif dut_looped_ports_10g.include? item["idx"]
                dut_looped_ports_sd << item["linux"]
            else
                puts "Error in portmap"
                exit
            end
            dut_looped_ports_sd << "eth#{port+offset}"
        end
        @dut = MesaDut.new :switchdev, dut_url, dut_ports_sd, dut_looped_ports_sd, dut_looped_ports_10g, port_admin, pcb

        if conf.key?("easytest_cmd_server")
            @pc = TestPCRemote.new conf["easytest_cmd_server"], pc_ports, conf["easytest_server"]
            @pc.bash_function "rvm use 2.6.2"
            #@pc.run "rvm info"
            upload_utils conf
            @pc.run "bundle-install.sh"
            @pc.run "lazy-ef-install.rb #{$easyframes_sha}" # TODO, find a better place to store this data
        else
            @pc = TestPC.new pc_ports
        end

        @links = dut_ports_sd.zip(pc_ports).map{|e| {:dut => e[0], :pc => e[1]}}
        @ts_external_clock_looped = (conf["ts_external_clock_looped"] == true) ? true : false
        if conf["pc"].key?("et_idx")
           @pc.bash_function "export IDX=#{conf["pc"]["et_idx"]}"
        end

        if $options[:no_init]
            @pc.run "/easytest/local/if-setup-l2-test.rb"
            @dut.mute
        else
            t_i "Preparing PC for network load"
            @pc.run "/easytest/local/if-setup-dhcp.rb"

            reboot_dut conf

            t_i "Prepare for test run"
            @pc.run "/easytest/local/if-setup-l2-test.rb"
            @dut.mute

            t = ""
            t = $options[:dut_trace]

            @dut.bg "rte", "mera-demo -f"
        end

        @vinst = []
        @vconn = []

        dut_ports_sd.each do |port|
            if port.is_a? Integer
                @dut.run "ip link set eth#{port} up"
            else
                @dut.run "ip link set #{port} up"
            end
        end

        if !$options[:no_init]
            @pc.run "poll_interface_state.rb -t 60 #{pc_ports.join " "}"
        end

        # TODO, wait for the DUT to see the link
    end

    def reboot_dut conf
        t_i "SW Rebooting DUT"
        @dut.sw_reboot
        loop = 0
        while loop < 3 do
            if !@dut.terminal_alive 5
                t_i "Terminal not responsive - power-cycle "
                @pc.run conf["power_control"]
            else
                break
            end
            loop = loop + 1
        end
        @dut.linux_login
    end

    def uninit
        @pc.run "/easytest/local/if-setup-dhcp.rb"
        @dut.unmute

        @vinst.each do |q|
            q.stop
        end
        @vinst = []

        @vconn.each do |c|
            c.stop
        end
        @vconn = []
    end
end

class Switchdev_Pc_bsp
    attr_accessor :dut, :pc

    def initialize conf
        dut_url = conf["dut"]["terminal"]
        port_admin = conf["dut"]["port_admin"]
        pcb = conf["dut"]["pcb"]
        @dut = MesaDut.new :bsp, dut_url, nil, nil, nil, port_admin, pcb

        if conf.key?("easytest_cmd_server")
            @pc = TestPCRemote.new conf["easytest_cmd_server"], nil, conf["easytest_server"]
            @pc.bash_function "rvm use 2.6.2"
            #@pc.run "rvm info"
            upload_utils conf
            @pc.run "bundle-install.sh"
            @pc.run "lazy-ef-install.rb #{$easyframes_sha}" # TODO, find a better place to store this data
        else
            @pc = TestPC.new nil
        end

        t_i "Rebooting DUT"
        @dut.sw_reboot
        @dut.linux_login
    end

    def uninit
        @pc.run "/easytest/local/if-setup-dhcp.rb"
        @dut.unmute
    end
end

class Qemu_Pc
    attr_accessor :pc, :vinst, :vconn

    def initialize conf
        dut_url = conf["dut"]["terminal"]
        port_admin = conf["dut"]["port_admin"]
        pcb = conf["dut"]["pcb"]

        if conf.key?("easytest_cmd_server")
            @pc = TestPCRemote.new conf["easytest_cmd_server"], nil, conf["easytest_server"]
            @pc.bash_function "rvm use 2.6.2"
            #@pc.run "rvm info"
            upload_utils conf
            @pc.run "bundle-install.sh"
            @pc.run "lazy-ef-install.rb #{$easyframes_sha}" # TODO, find a better place to store this data
        else
            @pc = TestPC.new nil
        end

        @vinst = []
        @vconn = []
    end

    def uninit
        @vinst.each do |q|
            q.stop
        end
        @vinst = []

        @vconn.each do |c|
            c.stop
        end
        @vconn = []
    end
end

class Mesa_Pc_b2b
    attr_accessor :dut, :pc, :links, :ts_external_clock_looped, :port_admin

    def initialize conf, mesa_args, port_cnt
        dut_url = conf["dut"]["terminal"]
        dut_args = conf["dut"]["mesa_demo_args"]
        dut_ports = conf["dut"]["ports"]
        dut_looped_ports = conf["dut"]["looped_ports"]
        dut_looped_ports_10g = conf["dut"]["looped_ports_10g"]
        pc_ports = conf["pc"]["ports"]
        port_admin = conf["dut"]["port_admin"]
        pcb = conf["dut"]["pcb"]
        check_capabilities do
            cnt = dut_ports.length
            if (cnt < port_cnt)
                assert(false, "setup has #{cnt} ports, test requires #{port_cnt}")
            end
        end
        @dut = MesaDut.new :mesa, dut_url, dut_ports, dut_looped_ports, dut_looped_ports_10g, port_admin, pcb

        if conf.key?("easytest_cmd_server")
            @pc = TestPCRemote.new conf["easytest_cmd_server"], pc_ports, conf["easytest_server"]
            @pc.bash_function "rvm use 2.6.2"
            #@pc.run "rvm info"
            upload_utils conf
            @pc.run "bundle-install.sh"
            @pc.run "lazy-ef-install.rb #{$easyframes_sha}" # TODO, find a better place to store this data
        else
            @pc = TestPC.new pc_ports
        end

        @links = dut_ports.zip(pc_ports).map{|e| {:dut => e[0], :pc => e[1]}}
        @ts_external_clock_looped = (conf["ts_external_clock_looped"] == true) ? true : false
       if conf["pc"].key?("et_idx")
           @pc.bash_function "export IDX=#{conf["pc"]["et_idx"]}"
       end

        if $options[:no_init]
            @pc.run "/easytest/local/if-setup-l2-test.rb"
            @dut.mute
        else
            t_i "Preparing PC for network load"
            @pc.run "/easytest/local/if-setup-dhcp.rb"

            reboot_dut conf

            t_i "Prepare for test run"
            @pc.run "/easytest/local/if-setup-l2-test.rb"
            @dut.mute

            t = ""
            t = $options[:dut_trace]

            @dut.bg "api", "mesa-demo -f #{dut_args} #{t} #{mesa_args}"
            @dut.bg "rte", "mera-demo -f #{dut_args}"
        end

        if !$options[:no_init]
            @pc.run "poll_interface_state.rb -t 60 #{pc_ports.join " "}"

            t_i "Wait until DUT ports are operational"
            ts = Time.now.to_i
            dut_ports.each do |port|
                loop do
                    oper_up = @dut.call "mesa_port_state_get", port
                    break if oper_up
                    if ((Time.now.to_i - ts) > 60)
                        t_f "DUT port #{port} not operational"
                        break;
                    end
                    sleep 1
                end
            end
        end
    end

    def reboot_dut conf
        t_i "SW Rebooting DUT"
        @dut.sw_reboot
        loop = 0
        while loop < 3 do
            if !@dut.terminal_alive 5
                t_i "Terminal not responsive - power-cycle "
                @pc.run conf["power_control"]
            else
                break
            end
            loop = loop + 1
        end
        @dut.linux_login
    end

    def uninit
        @pc.run "/easytest/local/if-setup-dhcp.rb"
        @dut.unmute
    end
end

def dut_init_block name
    ts_begin = Time.now
    has_err = false

    begin
        xml_tag_start "init", {"name" => name, "ts" => xml_ts(ts_begin)}
        yield

    rescue => e
        attrs = {}
        attrs["ts"] = xml_ts(Time.now)
        xml_tag "backtrace", e.backtrace.join("\n\t").sub("\n\t", ": #{e}#{e.class ? " (#{e.class})" : ''}\n\t"), attrs
        has_err = true
        $global_errors += 1
    else

    ensure
        ts_end = Time.now
        attrs = {}
        attrs["ts"] = xml_ts(ts_end)
        attrs["time_elapsed"] = xml_ts_diff(ts_begin, ts_end)
        xml_tag "init-end", nil, attrs
        xml_tag_end "init"
    end

    exit -1 if has_err
end

def get_test_setup_inner(setup, conf, mesa_args)
    case setup
    when "mesa_pc_b2b_4x"
        return Mesa_Pc_b2b.new(conf, mesa_args, 4)
    when "mesa_pc_b2b_2x"
        return Mesa_Pc_b2b.new(conf, mesa_args, 2)
    when "switchdev_pc_b2b_4x"
        return Switchdev_Pc_b2b_4x.new(conf, mesa_args)
    when "switchdev_pc_bsp"
        return Switchdev_Pc_bsp.new(conf)
    when "qemu_pc"
        return Qemu_Pc.new(conf)
    else
        raise "No such setup in inventory"
    end
end

def git_info cmd, env = nil, default = "UNKNOWN"
    if env and ENV[env]
        return ENV[env]
    end

    begin
        v = %x(#{cmd}).chop
        raise if $0.to_i != 0
        return v
    rescue
        return default
    end
end

def get_test_setup(setup, labels= {}, mesa_args = "")
    # URI:
    #    telnet://  -> if using a terminal server
    #    termhub:// -> if using termhub
    #
    # Keep the topology file .mscc-libeasy-topology.yaml in the home directory of the test PC

    if (File.exist?('.mscc-libeasy-topology.yaml'))
        conf = YAML.load_file ".mscc-libeasy-topology.yaml"
    else
        conf = YAML.load_file "#{ENV["HOME"]}/.mscc-libeasy-topology.yaml"
    end
    xml_tag_start "labels"
    file_base_name = File.basename($0, ".rb")

    if conf["platform_name"]
        labels["platform"]  = conf["platform_name"]
    else
        labels["platform"]  = "Name_missing_in_topology_file"
    end

    hist_name = "#{file_base_name}@#{labels["platform"]}_history"

    # default values - if not explictly defined
    labels["name"]      = "#{file_base_name}@#{Time.now.to_i}"   if labels["name"].nil?
    labels["historyid"] = hist_name        if labels["historyid"].nil?
    labels["full_name"] = labels["name"]   if labels["full_name"].nil?
    labels["severity"]  = "normal"         if labels["severity"].nil?
    labels["owner"]     = "none"           if labels["owner"].nil?
    labels["desc"]      = "no description" if labels["desc"].nil?

    # Git/Jenkins version info
    labels["git_sha"]      = git_info "git rev-parse --short HEAD",       "GIT_SHA_SHORT"
    labels["git_sha_full"] = git_info "git rev-parse HEAD",               "GIT_SHA_FULL"
    labels["git_id"]       = git_info "git describe --tags --long",       "GIT_ID",          labels["git_sha"]
    labels["git_branch"]   = git_info "git symbolic-ref --short -q HEAD", "GIT_BRANCH_NAME"
    if ENV["BUILD_ID"]
        labels["build_id"] = ENV["BUILD_ID"]
    else
        labels["build_id"] = "0"
    end

    # Can not be overwritten
    labels["filename"]  = file_base_name

    if not $options[:test_suite].nil?
        labels["test_suite"]  = $options[:test_suite]
    else
        labels["test_suite"]  = "No_test_suite"
    end

    if $options[:test_uuid]
        labels["uuid"] = $options[:test_uuid]
        labels["historyid"] = "#{$options[:test_uuid]}@#{labels["platform"]}_history"
    end

    labels["uuid"] = "#{labels["filename"]}@#{labels["test_suite"]}@#{labels["platform"]}@#{Time.now.to_i}"

    labels.each do |k, v|
        xml_tag "label", v.to_s, {"name" => k}
    end

    xml_tag_end "labels"

    dut_init_block setup do
        ts = get_test_setup_inner(setup, conf, mesa_args)
        $global_test_setup = ts

        if (defined? ts.dut) and ts.dut.api == :mesa
            ports = ts.dut.call("mesa_vlan_port_members_get", 1)
            ports_a = ports.split(",").map(&:to_i)
            if (ts.dut.looped_port_list != nil)    # Check for looped front ports and remove them from VLAN 1 to avoid looping
                ts.dut.looped_port_list.each { |port|
                    ports_a.delete(port)
                }
            end
            if (ts.dut.looped_port_list_10g != nil)    # Check for looped front ports and remove them from VLAN 1 to avoid looping
                ts.dut.looped_port_list_10g.each { |port|
                    ports_a.delete(port)
                }
            end
            ports = ports_a.join(',')
            ts.dut.call("mesa_vlan_port_members_set", 1, ports)
            if (ts.dut.port_admin != nil)
                ts.dut.run("mesa-cmd port state #{ts.dut.port_admin} disable") # Disable the admin port
            end

            cl = ts.dut.call("mesa_capability", "MESA_CAP_INIT_CORE_CLOCK")
            if (cl != 0)
                misc_conf = ts.dut.call("mesa_misc_get")
                t_i("Core Clock Frequency #{misc_conf["core_clock_freq"]}")
            end
        end

        return ts
    end
end

def basic_br_init()
    if $ts.dut.p[0].is_a? Integer
        $eth0 = $ts.dut.p[0] ? "eth#{$ts.dut.p[0]}" : nil
        $eth1 = $ts.dut.p[1] ? "eth#{$ts.dut.p[1]}" : nil
        $eth2 = $ts.dut.p[2] ? "eth#{$ts.dut.p[2]}" : nil
        $eth3 = $ts.dut.p[3] ? "eth#{$ts.dut.p[3]}" : nil
    else
        $eth0 = $ts.dut.p[0] ? "#{$ts.dut.p[0]}" : nil
        $eth1 = $ts.dut.p[1] ? "#{$ts.dut.p[1]}" : nil
        $eth2 = $ts.dut.p[2] ? "#{$ts.dut.p[2]}" : nil
        $eth3 = $ts.dut.p[3] ? "#{$ts.dut.p[3]}" : nil
    end
    $br   = "br0"

    $eth0_mac      = "::1:0:0"
    $eth0_mac_peer = "::1:1:0"
    $eth1_mac      = "::1:0:1"
    $eth1_mac_peer = "::1:1:1"
    $eth2_mac      = "::1:0:2"
    $eth2_mac_peer = "::1:1:2"
    $br_mac        = "::1:0:0"

    $ts.dut.run "ip link set dev #{$eth0} address 00:00:00:01:00:00" if $eth0
    $ts.dut.run "ip link set dev #{$eth1} address 00:00:00:01:00:01" if $eth1
    $ts.dut.run "ip link set dev #{$eth2} address 00:00:00:01:00:02" if $eth2
    $ts.dut.run "ip link set dev #{$eth3} address 00:00:00:01:00:03" if $eth3

    $ts.dut.run "ip link add name br0 type bridge"
    $ts.dut.run "ip link set dev br0 up"

    $ts.dut.run "ip link set #{$eth0} master br0" if $eth0
    $ts.dut.run "ip link set #{$eth1} master br0" if $eth1
    $ts.dut.run "ip link set #{$eth2} master br0" if $eth2
    $ts.dut.run "ip link set #{$eth3} master br0" if $eth3
end
