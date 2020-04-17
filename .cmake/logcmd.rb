#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'open3'
require 'optparse'

$log = nil

def ts t
    t.strftime("%T")
end

BLOCK_SIZE = 1024
def process_lines data
    while true
        head, sep, tail = data.partition("\n")
        if sep == "\n"
            yield head
            data = tail
        else
            return data
        end
    end
end

def console line
    f = nil
    begin
        n = File.expand_path(__FILE__) + ".lock"
        f = File.open(n, File::CREAT)
        f.flock(File::LOCK_EX)
        puts line
        f.flock(File::LOCK_UN)
    rescue
    ensure
        if f
            f.close
        end
    end
end

def console_ line
    if $run_con_line
        console $run_con_line
        $run_con_line = nil
    end
    console line
end

def log line
    begin
        $log.flock(File::LOCK_EX)
        $log.puts line
    rescue
    ensure
        $log.flock(File::LOCK_UN)
    end
end

def log_ line
    if $run_log_line
        log $run_log_line
        $run_log_line = nil
    end
    log line
end

def log_or_console line
    if $log
        return log(line)
    end

    console line
end

def log_or_console_ line
    if $log
        return log_(line)
    end

    console_ line
end

def log_and_console line
    log(line) if $log
    console(line)
end

def log_and_console_ line
    log_(line) if $log
    console_(line)
end

$msg = ""
$dir = nil
OptionParser.new do |opt|
    opt.banner = """Usage: logcmd.rb [options] -- cmd
    """
    opt.on('--log=file', "Log file") do |n|
        $log = File.open(n, "a")
    end

    #opt.on('--stdout-silent', "Do not print anything on stdout") { |o| }
    opt.on('--trace', "This is not a command to be run, but a trace statement for the log") do
        $trace = true
    end

    opt.on('--line-prepend=msg', "Prepen msg to each line") do |msg|
        $msg = "#{msg} "
    end

    opt.on('--simplegrid=dir', "Folder from which to read ip of blade server") do |dir|
        system "mkdir #{dir}"
        $dir = "#{dir}"
    end
end.parse!

cmd = ARGV.join(" ")

if $trace
    log_and_console "#{ts(Time.now)}-%05d-TRACE:  #{cmd}" % [Process.ppid]
    exit 0
end

ts_start = Time.now

$has_stderr_output = false
$buf_out = ""
$buf_err = ""
$spid = ""

s = ""
Open3.popen3("sh -c \"#{cmd}\"") do |stdin, _o, _e, wait_thr|
    stdin.close
    $spid = "%05d" % [wait_thr[:pid]]
    $run_con_line = "#{ts(Time.now)}-#{$spid}-RUN:      #{$msg}#{cmd}"
    $run_log_line = "#{ts(Time.now)}-#{$spid}-RUN:      #{$msg}#{cmd}"

    fds_ = [_o, _e]

    s += " "
    begin
        while not fds_.empty?
            fds = IO.select([_o, _e])

            at_blade = ""
            begin
                if $dir
                    at_blade = IO.read("#{$dir}/sg-offer.stamp")
                    at_blade = "@#{at_blade}"
                end
            rescue
            end

            if fds[0].include? _o
                begin
                    $buf_out << _o.read_nonblock(BLOCK_SIZE)
                    $buf_out = process_lines($buf_out) do |l|
                        log_or_console_ "#{ts(Time.now)}-#{$spid}-STDOUT:  #{$msg}#{at_blade} #{l}"
                    end
                rescue EOFError
                    fds_.delete_if {|s| s == _o}
                end
            end

            if fds[0].include? _e
                begin
                    $buf_err << _e.read_nonblock(BLOCK_SIZE)
                    $buf_err = process_lines($buf_err) do |l|
                        log_and_console_ "#{ts(Time.now)}-#{$spid}-STDERR:  #{$msg}#{at_blade} #{l}"
                        $has_stderr_output = true
                    end
                rescue EOFError
                    fds_.delete_if {|s| s == _e}
                end
            end
        end
    rescue IOError => e
        puts "IOError: #{e}"
    end

    $exit_status = wait_thr.value.exitstatus
end


if $log
    if $run_log_line
        log "#{ts(Time.now)}-#{$spid}-CMD:     #{$msg}\"#{cmd}\" return val: #{$exit_status} took #{(Time.now - ts_start).to_i} seconds (#{cmd})"
    else
        log "#{ts(Time.now)}-#{$spid}-DONE:    #{$msg}return val: #{$exit_status} took #{(Time.now - ts_start).to_i} seconds (#{cmd})"
    end


    took = (Time.now - ts_start).to_i
    stook = ""
    if took > 59940 # more than 999 minutes
        stook = "%03dh" % [took / 3600]
    elsif took > 999
        stook = "%03dm" % [took / 60]
    else
        stook = "%03ds" % [took]
    end

    if $exit_status == 0 and not $has_stderr_output
        if $dir
            console "#{ts(Time.now)}-#{stook}-OK:       #{$msg}@#{s} #{cmd}"
        else
            console "#{ts(Time.now)}-#{stook}-OK:       #{$msg} #{cmd}"
        end
    else
        if $dir
            console "#{ts(Time.now)}-#{stook}-ERR(%3d): #{$msg}@#{s} #{cmd}" % [ $exit_status ]
        else
            console "#{ts(Time.now)}-#{stook}-ERR(%3d): #{$msg} #{cmd}" % [ $exit_status ]
        end
    end

    $log.close

else
    if $run_con_line
        console "#{ts(Time.now)}-#{$spid}-CMD:     #{$msg}\"#{cmd}\" return val: #{$exit_status} took #{(Time.now - ts_start).to_i} seconds (#{cmd})"
    else
        console "#{ts(Time.now)}-#{$spid}-DONE:    #{$msg}return val: #{$exit_status} took #{(Time.now - ts_start).to_i} seconds (#{cmd})"
    end

end

if $has_stderr_output
    exit -1
end

exit $exit_status
