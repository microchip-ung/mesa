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

    def get_cursor
      @input_buf = ""
      send ""
      sleep 0.1
      poll_stdin 0.1

      while l = pop_line
      end

      x = @input_buf
      @input_buf = ""

      return x
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

    def read_line_expect_out_end pattern
      while true
        while l = pop_line
          yield l
          if l.match pattern
            return true
          end
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

    def read_line_expect_retry pattern, total_timeout, retry_timeout, retry_cmd = nil
      timeout_before = @timeout
      @timeout = retry_timeout
      match = false

      start = Time.now
      while Time.now - start < total_timeout
        begin
          match = read_line_expect_out_end pattern do |l|
            if block_given?
              yield l
            else
              console l
            end
          end
          if match
            break
          end
        rescue
          if retry_cmd
            send retry_cmd
          end
        end
      end

      @timeout = timeout_before
      if not match
        raise "pattern not found"
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
    attr_accessor :api, :p, :port_list, :looped_port_list, :looped_port_list_10g, :io, :port_admin, :pcb, :cap

    def initialize api, url, ports, looped_ports, looped_ports_10g, port_admin, pcb, cap
        @api = api
        @p = ports
        @port_list = ports
        @looped_port_list = looped_ports
        @looped_port_list_10g = looped_ports_10g
        @port_admin = port_admin
        @pcb = pcb
        @cap = cap
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

    # ignore errors
    def run_ignore cmd, *args
        execute cmd, "try_ignore", *args
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

    def linux_login
        @io.read_line_expect_retry /login:/, 180, 2, ""
        @io.read_line_expect_retry /#/, 10, 1, "root"
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
            ts = ts_now.to_f
            msg = nil
            case l
            when /ER-M-(\d+)-(\d+\.\d+)-RUN\s+(.*)/
                msg = {:type => :run, :pid => $1.to_i, :ts => ts, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDOUT\s+(.*)/
                msg = {:type => :out, :pid => $1.to_i, :ts => ts, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDERR\s+(.*)/
                msg = {:type => :err, :pid => $1.to_i, :ts => ts, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDIN\s+(.*)/
                msg = {:type => :in, :pid => $1.to_i, :ts => ts, :data => $3}

            when /ER-M-(\d+)-(\d+\.\d+)-EXIT\s+(.*)/
                msg = {:type => :res, :pid => $1.to_i, :ts => ts, :data => $3}

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
            attrs = {"pid" => msg[:pid], "name" => bg_job[:name], "on" => bg_job[:on], "ts_rel" => xml_ts_diff(ts_begin, ts), "ts" => xml_ts(ts_now)}

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

    def bg_exitstatus pid
        poll_cmd_output(pid)
        @background_jobs[pid[:pid]][:res]
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
            ts = ts_now.to_f
            msg = nil
            case l
            when /ER-M-(\d+)-(\d+\.\d+)-RUN\s+(.*)/
                msg = {:type => :run, :pid => $1.to_i, :ts => ts, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDOUT\s+(.*)/
                msg = {:type => :out, :pid => $1.to_i, :ts => ts, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDERR\s+(.*)/
                msg = {:type => :err, :pid => $1.to_i, :ts => ts, :data => $3}

            when /ER-[LC]-(\d+)-(\d+\.\d+)-STDIN\s+(.*)/
                msg = {:type => :in, :pid => $1.to_i, :ts => ts, :data => $3}

            when /ER-M-(\d+)-(\d+\.\d+)-EXIT\s+(.*)/
                msg = {:type => :res, :pid => $1.to_i, :ts => ts, :data => $3}

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
            attrs = {"pid" => msg[:pid], "name" => bg_job[:name], "on" => bg_job[:on], "ts_rel" => xml_ts_diff(ts_begin, ts), "ts" => xml_ts(ts_now)}

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

    def bg_exitstatus pid
        poll_cmd_output(pid)
        @background_jobs[pid][:res]
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

$easyframes_sha = "ce45ec85871ad2f1412a964868f8ad11bf581bfc"

UBOOT_PROMPTS = ["m => ", "ocelot # ", "luton # ", "jr2 # ", "servalt # ", "=> "]

class Mesa_Pc_b2b
    attr_accessor :dut, :pc, :links, :ts_external_clock_looped, :port_admin, :port_map, :labels

    def initialize conf, mesa_args, port_cnt, topo_name, labels
        #Default topology
        dut_url = conf["dut"]["terminal"]
        dut_args = conf["dut"]["mesa_demo_args"]
        dut_ports = conf["dut"]["ports"]
        dut_looped_ports = conf["dut"]["looped_ports"]
        dut_looped_ports_10g = conf["dut"]["looped_ports_10g"]
        port_admin = conf["dut"]["port_admin"]
        pcb = conf["dut"]["pcb"]
        cap = conf["dut"]["cap"]
        pc_ports = conf["pc"]["ports"]

        #Check for any multi topology overwriting
        if (conf["Multi_topo"] != nil)
            conf["Multi_topo"].each do |topo|
                next if (topo["#{topo_name}"] == nil)
                name = topo["#{topo_name}"]
                if (name["dut"] != nil)
                    if (name["dut"]["ports"] != nil)
                        dut_ports = name["dut"]["ports"]
                    end
                    if (name["dut"]["looped_ports"] != nil)
                        dut_looped_ports = name["dut"]["looped_ports"]
                    end
                end
                if (name["pc"] != nil)
                    if (name["pc"]["ports"] != nil)
                        pc_ports = name["pc"]["ports"]
                    end
                end
            end
        end

        check_capabilities do
            cnt = dut_ports.length
            if (cnt < port_cnt)
                assert(false, "setup has #{cnt} ports, test requires #{port_cnt}")
            end
        end

        #Create the DUT
        @dut = MesaDut.new :mesa, dut_url, dut_ports, dut_looped_ports, dut_looped_ports_10g, port_admin, pcb, cap
        @labels = labels

        if conf.key?("easytest_cmd_server")
            @pc = TestPCRemote.new conf["easytest_cmd_server"], pc_ports, conf["easytest_server"]
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

        #Check for any multi topology commands
        if (conf["Multi_topo"] != nil)
            conf["Multi_topo"].each do |topo|
                if (topo["#{topo_name}"] != nil)
                    name = topo["#{topo_name}"]
                    name["command"].each do |command|  #Do all required server PC commands
                        @pc.run command
                        sleep 1
                    end
                end
            end
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

            @dut.run "echo 0 > /proc/sys/kernel/printk"
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
                    sleep 1
                    if ((Time.now.to_i - ts) > 60)
                        t_f "DUT port #{port} not operational"
                        break;
                    end
                end
            end
        end

        cnt = @dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
        @port_map = @dut.call("mesa_port_map_get", cnt)
    end

    def uboot_break
      begin
        t_i "try to reach uboot prompt"
        @dut.io.read_line_expect_retry /(Hit any key to stop autoboot|Press SPACE to abort autoboot)/, 30, 1
        @dut.io.send " "
        sleep 0.1
        cur  = @dut.io.get_cursor
        if not UBOOT_PROMPTS.include? cur
          t_i "Cursor: #{cur} does not look like UBoot"
          return false
        end
        t_i "Reached to UBoot console"
        return true

      rescue => e
        t_backtrace e
        return false
      end
    end

    def trigger_reboot_dut conf
      again = 10
      while again > 0
        t_i "Detect environment and trigger a reboot"
        l = @dut.io.get_cursor
        t_i "Got: #{l}"

        if UBOOT_PROMPTS.include? l
          t_i "Looks like uboot"
          @dut.io.send "reset"
          again = 0
        elsif l =~ /#/
          t_i "Looks linux shell - try reboot cmd"
          @dut.io.sysrq("b")
          @dut.io.send ""
          @dut.io.send "reboot"
          again = 0

        elsif l =~ /login:/
          t_i "Looks login shell"
          @dut.io.send "root"
          again -= 1
          sleep 1
        elsif l =~ /Password:/
          t_i "Looks linux login prompt"
          # root does not use any password - maybe some garbage was entered
          @dut.io.send ""
          sleep 5
          again -= 1
        else
          if again > 8
            t_i "Unexpected prompt: #{l} - try reset tty"
            @dut.io.send("stty echo")
            sleep(0.1)
            @dut.io.send("export PS1=\"# \"")
            sleep(0.1)
            @dut.io.send("export PS2=\"> \"")
            sleep(0.1)
            @dut.io.send("")
            again -= 1
          else
            t_i "Unexpected prompt: #{l} - do power-cycle"
            @pc.run conf["power_control"]
            again = 0
            t_i "Unexpected prompt: #{l} - do power-cycle"
          end
        end
      end
    end

    def trigger_laguna_reboot_dut conf
      again = 10
      while again > 0
        t_i "Detect environment and trigger a reboot"
        l = @dut.io.get_cursor
        t_i "Got: #{l}"

        if l =~ /#/
          t_i "Do not attempt to SW-reset Laguna"
          @dut.io.send("echo 16 >/sys/class/gpio/export")
          sleep 0.1
          @dut.io.send("echo out >/sys/class/gpio/gpio16/direction")
          sleep 0.1
          @dut.io.send("echo 0 >/sys/class/gpio/gpio16/value")
          sleep 0.1
          @dut.io.send("echo 1 >/sys/class/gpio/gpio16/value")
          t_i "Do not attempt to SW-reset Laguna - DONE"
          return

        elsif l =~ /login:/
          t_i "Looks login shell"
          @dut.io.send "root"
          again -= 1
          sleep 1
        elsif l =~ /Password:/
          t_i "Looks linux login prompt"
          # root does not use any password - maybe some garbage was entered
          @dut.io.send ""
          sleep 5
          again -= 1
        else
          t_i "Unexpected prompt: #{l} - do power-cycle"
          @dut.io.send("stty echo")
          sleep(0.1)
          @dut.io.send("export PS1=\"# \"")
          sleep(0.1)
          @dut.io.send("export PS2=\"> \"")
          sleep(0.1)
          @dut.io.send("")
          again -= 1
        end
      end
    end

    def reboot_dut conf
      if ((conf["dut"]["pcb"] == "6849-Sunrise") && (conf["dut"]["family"] == "laguna"))
        trigger_laguna_reboot_dut conf
      else
        trigger_reboot_dut conf
      end

      if not uboot_break()
        @pc.run conf["power_control"]
        if not uboot_break()
          t_i "Give up reach UBoot prompt"
          raise "Give up reach UBoot prompt"
        end

      end

      @dut.io.send "run bootcmd"
      @dut.linux_login
    end

    def uninit
        @pc.run "/easytest/local/if-setup-dhcp.rb"
        @dut.unmute
    end
end

def show_mesa_setup(ts)
    test("show-setup", false) do
        pmap = ts.port_map

        max = 0
        cnt = ts.dut.p.length
        cnt.times do |idx|
            len = ts.pc.p[idx].length
            if (len > max)
                max = len
            end
        end

        # Show diagram of PC and DUT with port links
        cnt.times do |idx|
            port = ts.dut.p[idx]
            chip_port = pmap[port]["chip_port"]
            name = ts.pc.p[idx]
            str = "|       #{idx} |- #{name} "
            (max - name.length).times do
                str += "-"
            end
            str += "---"
            str += "-" if (port < 10)
            str += " #{port} -| #{chip_port}"
            str += " " if (chip_port < 10)
            str += "      |"

            txt = ""
            len = (str.length - 22)
            len.times do
                txt += " "
            end

            if (idx == 0)
                a = ts.labels["platform"].split("_t3")
                if (a.size == 2)
                    len = (txt.length + 12)
                    l = ("   t3" + a[1])
                    while (l.length < len)
                        l += " "
                    end
                    l += a[0]
                    t_i(l)
                end
                t_i("+---------+" + txt + "+---------+")
            end
            t_i(str)
            if (idx == ((cnt / 2) - 1))
                t_i("|   PC    |" + txt + "|   DUT   |")
            elsif (idx == (cnt - 1))
                t_i("+---------+" + txt + "+---------+") if (idx == (cnt - 1))
            else
                t_i("|         |" + txt + "|         |")
            end
        end

        # Show looped ports
        [ts.dut.looped_port_list, ts.dut.looped_port_list_10g].each_with_index do |port_list, idx|
            cnt = (port_list == nil ? 0 : (port_list.length / 2))
            cnt.times do |i|
                p1 = port_list[2 * i]
                p2 = port_list[2 * i + 1]
                cp1 = pmap[p1]["chip_port"]
                cp2 = pmap[p2]["chip_port"]
                str = (idx == 0 ? "1G_#{i} " : "10G_#{i}")
                t_i("Loop_#{str}: #{p1}-#{p2} (#{cp1}-#{cp2})")
            end
        end
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

def get_test_setup_inner(setup, conf, mesa_args, topo_name, labels)
    case setup
    when "mesa_pc_b2b_4x"
        ts = Mesa_Pc_b2b.new(conf, mesa_args, 4, topo_name, labels)
        show_mesa_setup(ts)
        return ts
    when "mesa_pc_b2b_2x"
        ts = Mesa_Pc_b2b.new(conf, mesa_args, 2, topo_name, labels)
        show_mesa_setup(ts)
        return ts
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

def get_test_setup(setup, labels= {}, mesa_args = "", topo_name = "default")
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
        ts = get_test_setup_inner(setup, conf, mesa_args, topo_name, labels)
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

    # name the bridge the same as the index of the PC NIC that is used
    # in this way in case the test fails we can clean up before the new
    # test is started
    $br   = "br#{$ts.pc.p[0][3..3]}"

    $eth0_mac      = "::1:0:0"
    $eth0_mac_peer = "::1:1:0"
    $eth1_mac      = "::1:0:1"
    $eth1_mac_peer = "::1:1:1"
    $eth2_mac      = "::1:0:2"
    $eth2_mac_peer = "::1:1:2"
    $eth3_mac      = "::1:0:3"
    $eth3_mac_peer = "::1:1:3"
    $br_mac        = "::1:0:0"

    # try to delete the bridge on PC in case one exists
    $ts.pc.try_ignore "ip link del dev #{$br}"

    $ts.dut.run "ip link set dev #{$eth0} address 00:00:00:01:00:00" if $eth0
    $ts.dut.run "ip link set dev #{$eth1} address 00:00:00:01:00:01" if $eth1
    $ts.dut.run "ip link set dev #{$eth2} address 00:00:00:01:00:02" if $eth2
    $ts.dut.run "ip link set dev #{$eth3} address 00:00:00:01:00:03" if $eth3

    $ts.dut.run "ip link add name #{$br} type bridge"
    $ts.dut.run "ip link set dev #{$br} up"

    $ts.dut.run "ip link set #{$eth0} master #{$br}" if $eth0
    $ts.dut.run "ip link set #{$eth1} master #{$br}" if $eth1
    $ts.dut.run "ip link set #{$eth2} master #{$br}" if $eth2
    $ts.dut.run "ip link set #{$eth3} master #{$br}" if $eth3
end
