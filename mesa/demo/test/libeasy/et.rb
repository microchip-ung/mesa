#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'open3'
require 'optparse'
require_relative './test-setup'
require_relative './utils'

$options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: example.rb [options]"

    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit
    end

    opts.on("--no-init", "Skip the DUT initialization step") do |v|
        $options[:no_init] = true
    end

    opts.on("--dut-trace <trace-setting>", "Enable trace when starting the mesa demo application") do |t|
        $options[:dut_trace] = "" if $options[:dut_trace].nil?
        $options[:dut_trace] += " -t #{t}"
    end

    opts.on("--test-suite-name name", "Name of test suite") do |v|
        $options[:test_suite] = v
    end

    opts.on("--test-uuid uuid", "Name of test case") do |v|
        $options[:test_uuid] = v
    end

end.parse!



$test_stack = []
$global_errors = 0
$stdout.sync = true
$stderr.sync = true

class TestAbortException < StandardError
    attr_accessor :msg

    def initialize msg
        @msg = msg
    end
end

def xml_ts ts
    return "#{ts.tv_sec}.#{"%09d" % ts.tv_nsec}"
end

def xml_ts_diff a, b
    return "#{"%.6f" % (b - a).to_f}"
end

def xml_attr name, val
    return "#{name}=#{val.to_s.encode(:xml => :attr)}"
end

def xml_attrs a
    return "" if a.nil?
    return " #{a.to_a.map{|x| xml_attr(x[0], x[1])}.join(" ")}"
end

def xml_tag_start tag, attr = nil
    puts "<#{tag}#{xml_attrs(attr)}>"
end

def xml_tag_end tag
    puts "</#{tag}>"
end

def xml_tag tag, body = nil, attr = nil
    if body
        body = body.delete("\000")
        puts "<#{tag}#{xml_attrs(attr)}>#{body.encode(:xml => :text)}</#{tag}>"
    else
        puts "<#{tag}#{xml_attrs(attr)} />"
    end
end

puts "<?xml version=\"1.0\"?>"
$ts_root_begin = Time.now
xml_tag_start "test_run", {"ts" => xml_ts($ts_root_begin), "file" => $0}

class StreamLineProcesser
    def initialize
        @buf = ''
        @eof = false
    end

    def append data
        @buf += data
    end

    def finish
        @eof = true
    end

    def peak_line
        res = @buf.partition("\n")
        if res[1].size == 0
            return nil
        else
            return res[0]
        end
    end

    def pop_line
        line = ''

        res = @buf.partition("\n")
        if res[1].size == 0
            return nil
        else
            @buf = res[2]
            return res[0]
        end
    end

    def process_lines
        while line = pop_line
            yield line
        end

        if @buf.length > 0 and @eof
            yield @buf
        end

        @eof = false
        @buf = ""
    end
end

def run cmd, flags = []
    ts_begin = Time.now
    exitstatus = nil
    ts_end = nil
    pid = nil
    raw = nil
    raw_not_raw_detected = false

    begin
        Open3::popen3(cmd) do |_i, _o, _e, _t|
            pid = _t.pid

            first_line = true
            _i.close
            _o.sync = true;
            _e.sync = true;

            obuf = StreamLineProcesser.new
            ebuf = StreamLineProcesser.new
            chunk_size = 4096
            fds_ = [_o, _e]

            while not fds_.empty?
                fds = select(fds_, nil, nil, nil)
                ts = Time.now

                attr = {"pid" => _t.pid, "ts-rel" => xml_ts_diff(ts_begin, ts), "ts" => xml_ts(ts)}

                # detect raw formating
                if first_line and fds[0].include? _o
                    begin
                        obuf.append _o.readpartial(chunk_size)
                    rescue EOFError
                        fds_.delete_if {|s| s == _o}
                        obuf.finish
                    else
                    ensure
                        l = obuf.peak_line
                        if l
                            if l.chomp == "<?xml version=\"1.0\"?>"
                                obuf.pop_line
                                raw = true
                            else
                                raw = false
                            end
                            raw_not_raw_detected = true
                        end
                    end
                end

                # if it starts to chat on stderr, then it is not raw!
                if fds[0].include? _e and not raw_not_raw_detected
                    raw = false
                    raw_not_raw_detected = true
                end

                # We now know, and we can print the header...
                if raw_not_raw_detected and first_line
                    if not raw
                        xml_tag_start "run", {"cmd" => cmd, "ts" => xml_ts(ts_begin), "pid" => _t.pid}
                    end
                    first_line = false
                end

                # Normal processing of stdout
                if fds[0].include? _o
                    begin
                        obuf.append _o.readpartial(chunk_size)

                    rescue EOFError
                        fds_.delete_if {|s| s == _o}
                        obuf.finish
                    else

                    ensure
                        if raw_not_raw_detected
                            obuf.process_lines do |l|
                                if raw
                                    puts l
                                else
                                    #@log.debug "HOST-OUT$ #{l}" if not flags.include? :silence
                                    #yield l if block_given?
                                    xml_tag "run-stdout", l, attr
                                end
                            end
                        end
                    end
                end

                # Normal processing of stderr
                if fds[0].include? _e
                    begin
                        ebuf.append _e.readpartial(chunk_size)
                    rescue EOFError
                        fds_.delete_if {|s| s == _e}
                        ebuf.finish
                    else

                    ensure
                        if raw_not_raw_detected
                            ebuf.process_lines do |l|
                                if raw
                                    puts l
                                else
                                    #@log.debug "HOST-ERR$ #{l}" if not flags.include? :silence
                                    #yield l if block_given?
                                    xml_tag "run-stderr", l, attr
                                end
                            end
                        end
                    end
                end
            end

            #@log.debug "HOST-DONE #{_t.value}" if not flags.include? :silence
            exitstatus = _t.value.exitstatus.to_i
        end

    rescue
    else
    ensure
        if not raw
            ts_end = Time.now

            attrs = {}
            attrs["pid"] = pid if pid
            attrs["ts"] = xml_ts(ts_end)
            attrs["time_elapsed"] = xml_ts_diff(ts_begin, ts_end)
            attrs["exitstatus"] = exitstatus if exitstatus

            xml_tag "run-end", nil, attrs
            xml_tag_end "run"
        end
    end

    if exitstatus.nil? or exitstatus != 0
        raise "Cmd: #{cmd} -> #{exitstatus}"
    end
end

# Global variable for test summary
$test_summary_list = []

def test_summary(all = true)
    test("summary", false) do
        list = $test_summary_list
        cnt_total = list.length
        cnt_err = 0
        list.each_with_index do |e, i|
            txt = nil
            if (e[:status] == "not-ok")
                cnt_err += 1
                txt = "Failed "
            elsif (all)
                txt = "Success"
            end
            if (txt != nil)
                txt += " [#{i}]"
                cnt = ((cnt_total - 1).to_s.length - i.to_s.length)
                cnt.times do
                    txt += " "
                end
                txt += ": "
                t_i(txt + e[:name])
            end
        end
        t_i("Total : #{cnt_total}")
        t_i("Ok    : #{cnt_total - cnt_err}")
        t_i("Errors: #{cnt_err}")
        $test_summary_list = []
    end
end

def test(name, summary = true)
    do_abort = false
    ts_begin = Time.now

    begin
        xml_tag_start "test", {"name" => name, "ts" => xml_ts(ts_begin)}
        $test_stack.push({:cnt_ok => 0, :cnt_err => 0})
        yield nil

    rescue TestAbortException => e
        $test_stack[-1][:cnt_err] += 1
        do_abort = true

    rescue => e
        $test_stack[-1][:cnt_err] += 1
        attrs = {}
        attrs["ts"] = xml_ts(Time.now)
        xml_tag "backtrace", e.backtrace.join("\n\t").sub("\n\t", ": #{e}#{e.class ? " (#{e.class})" : ''}\n\t"), attrs
        do_abort = true

    else
        if $test_stack[-1][:cnt_err] == 0
            $test_stack[-1][:cnt_ok] += 1
        else
            $test_stack[-1][:cnt_err] += 1
        end

    ensure
        if $test_stack.size > 1
            $test_stack[-2][:cnt_ok] += $test_stack[-1][:cnt_ok]
            $test_stack[-2][:cnt_err] += $test_stack[-1][:cnt_err]
        end

        attrs = {}
        #attrs["cnt_err"] = $test_stack[-1][:cnt_err]
        #attrs["cnt_ok"] = $test_stack[-1][:cnt_ok]
        #attrs["status"] = "ok"
        if $test_stack[-1][:cnt_err] > 0
            attrs["status"] = "not-ok"
            $global_errors += 1
        else
            attrs["status"] = "ok"
        end

        if (summary)
            $test_summary_list << {name: name, status: attrs["status"]}
        end

        ts_end = Time.now
        attrs["ts"] = xml_ts(ts_end)
        attrs["time_elapsed"] = xml_ts_diff(ts_begin, ts_end)

        xml_tag "test_end", nil, attrs
        $test_stack.pop

        xml_tag_end "test"
    end

    if $test_stack.size > 0 and do_abort
        raise TestAbortException, ""
    end
end

def check_capabilities
    do_abort = false
    ts_begin = Time.now

    begin
        xml_tag_start "check_capability", {"ts" => xml_ts(ts_begin)}
        $test_stack.push({:cnt_ok => 0, :cnt_err => 0})
        yield nil

    rescue TestAbortException => e
        $test_stack[-1][:cnt_err] += 1
        do_abort = true

    rescue => e
        $test_stack[-1][:cnt_err] += 1
        attrs = {}
        attrs["ts"] = xml_ts(Time.now)
        xml_tag "backtrace", e.backtrace.join("\n\t").sub("\n\t", ": #{e}#{e.class ? " (#{e.class})" : ''}\n\t"), attrs
        do_abort = true

    else

    ensure
        attrs = {}
        if $test_stack[-1][:cnt_err] > 0
            attrs["status"] = "not-ok"
        else
            attrs["status"] = "ok"
        end

        ts_end = Time.now
        attrs["ts"] = xml_ts(ts_end)
        attrs["time_elapsed"] = xml_ts_diff(ts_begin, ts_end)

        xml_tag "check_capability_end", nil, attrs
        $test_stack.pop

        xml_tag_end "check_capability"
    end

    if do_abort
        exit 0
    end
end

# Method to run the ef command, ts is the test setup object, 
# idx_tx is the interface to transmit on,
# rx_idx_list is an array or interfaces to receive on. 
# frame is the content of the frame

def run_ef_tx_rx_cmd ts, tx_idx, rx_idx_list, frame
    cmd = "ef name f1 #{frame}"
    cmd += " tx #{ts.pc.p[tx_idx]} name f1"
    ts.pc.p.each_index do |idx|
        if rx_idx_list.include? idx
            cmd += " rx #{ts.pc.p[idx]} name f1"
        else
            cmd += " rx #{ts.pc.p[idx]}"
        end
    end

    ts.pc.run "sudo #{cmd}"
end


def console msg
    xml_tag "console", msg, {"ts" => xml_ts(Time.now)}
end

def trace level, msg
    xml_tag "trace", msg.to_s, {"level" => level, "ts" => xml_ts(Time.now)}
end

def t_backtrace e
    xml_tag "backtrace", e.backtrace.join("\n\t").sub("\n\t", ": #{e}#{e.class ? " (#{e.class})" : ''}\n\t")
end

def t_n msg
    trace "noice", msg
end

def t_d msg
    trace "debug", msg
end

def t_i msg
    trace "info", msg
end

def t_e msg
    trace "error", msg
    $test_stack[-1][:cnt_err] += 1
end

def t_f msg
    trace "fatal", msg
end

def assert expr, msg = "NO-MESSAGE"
    if expr
        xml_tag "assert", nil, {"val" => "ok", "msg" => msg, "ts" => xml_ts(Time.now)}
    else
        xml_tag "assert", nil, {"val" => "not-ok", "msg" => msg, "ts" => xml_ts(Time.now)}
        raise TestAbortException, msg
    end
end

def check expr, msg = "NO-MESSAGE"
    if expr
        xml_tag "check", nil, {"val" => "ok", "msg" => msg, "ts" => xml_ts(Time.now)}
    else
        xml_tag "check", nil, {"val" => "not-ok", "msg" => msg, "ts" => xml_ts(Time.now)}
        $test_stack[-1][:cnt_err] += 1
    end
end

def poll sleep_time, cnt, block
    ok = false
    first = true
    ts_b = Time.now.to_f

    i = 0
    while i < cnt
        if first
            first = false
        else
            sleep sleep_time
        end

        i += 1
        res = block.call

        break if res
    end

    val = "not-ok"
    val = "ok" if res
    xml_tag "poll", nil, {"val" => val, "cnt" => i, "ts" => xml_ts(Time.now)}

    return res
end

def assert_poll sleep_time, cnt, msg = "NO-MESSAGE", &block
    test msg do
        res = poll sleep_time, cnt, block

        if res
            xml_tag "assert_poll", nil, {"val" => "ok", "msg" => msg, "ts" => xml_ts(Time.now)}
        else
            xml_tag "assert_poll", nil, {"val" => "not-ok", "msg" => msg, "ts" => xml_ts(Time.now)}
            raise TestAbortException, msg
        end
    end
end

def check_poll sleep_time, cnt, msg = "NO-MESSAGE", &block
    test "POLLING: #{msg}" do
        res = poll sleep_time, cnt, block

        if res
            xml_tag "check_poll", nil, {"val" => "ok", "msg" => msg, "ts" => xml_ts(Time.now)}
        else
            xml_tag "check_poll", nil, {"val" => "not-ok", "msg" => msg, "ts" => xml_ts(Time.now)}
            $test_stack[-1][:cnt_err] += 1
        end

        return res
    end
end

END {
    ts_root_end = Time.now
    s = "ok"
    s = "not-ok" if $global_errors > 0
    a = {
        "ts"     => xml_ts(ts_root_end),
        "ts_rel" => xml_ts_diff($ts_root_begin, ts_root_end),
        "status" => s,
        "file"   => $0,
    }

    $global_test_setup.uninit if $global_test_setup

    xml_tag "test_run_end", nil, a
    xml_tag_end "test_run"

    if $global_errors > 0
        exit (-1)
    else
        exit (0)
    end
}

