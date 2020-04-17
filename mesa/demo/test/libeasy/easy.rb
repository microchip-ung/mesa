#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'socket'
require 'open3'

def sys cmd
    system cmd
    raise "\nCMD Failed: >#{cmd}< with exit code: #{$?}\n" if $?.to_i != 0
end

class StreamLineProcesser
    def initialize
        @buf = ''
    end

    def append data
        @buf += data
        line = ''

        while true
            res = @buf.partition("\n")
            if res[1].size == 0
                break;
            else
                line = res[0]
                @buf = res[2]
            end

            yield line
        end
    end

    def finish
        if @buf.length > 0
            yield @buf
        end
    end
end

class CliIO
    attr_accessor :timeout

    def initialize istream, ostream
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

    def poll_stdin_
        rs, ws = IO.select([@istream], [], [], @timeout)
        if rs != nil and r = rs[0]
            x = r.read_nonblock(128)
            @input_buf << x
            return true
        else
            return false
        end
    end

    def poll_stdin
        if poll_stdin_
            @input_buf = sanitize_line @input_buf
            return true
        end
        return false
    end

    def pop_line
        o = @input_buf.partition("\r\n")
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
        poll_stdin
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
        @ostream.write "\x1b[24~"
        @ostream.flush
        sleep 0.1
    end

    def sysrq cmd
        send_break
        @ostream.write(cmd)
        @ostream.flush
    end

    def cmd s, flags = []
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

