#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'ox'
require 'pp'
require 'optparse'

$options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: [options]"

    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit
    end

    opts.on("--brief", "") do |v|
        $options[:brief] = true
    end

    opts.on("--short", "") do |v|
        $options[:short] = true
    end
end.parse!


class String
    def black;          "\e[30m#{self}\e[0m" end
    def red;            "\e[31m#{self}\e[0m" end
    def green;          "\e[32m#{self}\e[0m" end
    def brown;          "\e[33m#{self}\e[0m" end
    def blue;           "\e[34m#{self}\e[0m" end
    def magenta;        "\e[35m#{self}\e[0m" end
    def cyan;           "\e[36m#{self}\e[0m" end
    def gray;           "\e[37m#{self}\e[0m" end

    def bg_black;       "\e[40m#{self}\e[0m" end
    def bg_red;         "\e[41m#{self}\e[0m" end
    def bg_green;       "\e[42m#{self}\e[0m" end
    def bg_brown;       "\e[43m#{self}\e[0m" end
    def bg_blue;        "\e[44m#{self}\e[0m" end
    def bg_magenta;     "\e[45m#{self}\e[0m" end
    def bg_cyan;        "\e[46m#{self}\e[0m" end
    def bg_gray;        "\e[47m#{self}\e[0m" end

    def bold;           "\e[1m#{self}\e[22m" end
    def italic;         "\e[3m#{self}\e[23m" end
    def underline;      "\e[4m#{self}\e[24m" end
    def blink;          "\e[5m#{self}\e[25m" end
    def reverse_color;  "\e[7m#{self}\e[27m" end
end

class Sample < ::Ox::Sax
    def initialize
        @indent_level = 0
        @time_start = nil
        @time_now = nil
        @time_now_rel_s = nil
        @stack = []
        @stack.push({ :name => :document, :attr => {} })
        @test_stack = []
    end

    def update_ts ts
        if ts.nil?
            @time_now_rel_s = nil
            @time_now = nil
            return
        end

        if /(\d+).(\d{9})/ =~ ts
            @time_now = (($1.to_i + Rational($2.to_i, 1000000000)) * 1000000000).to_i
        else
            raise "Invalid TS: #{ts}"
        end

        if @time_start.nil?
            @time_start = @time_now
        end

        diff = @time_now - @time_start

         h, diff = diff.divmod(60 * 60 * 1000 * 1000 * 1000)
         m, diff = diff.divmod(     60 * 1000 * 1000 * 1000)
         s, diff = diff.divmod(          1000 * 1000 * 1000)
        ms, diff = diff.divmod(                 1000 * 1000)
        us,   ns = diff.divmod(                        1000)

        # TODO, rounding...

        @time_now_rel_s = "%02d:%02d:%02d.%03d.%03d" % [h, m, s, ms, us]
        @time_now_rel_s = "%02d:%02d:%02d.%03d" % [h, m, s, ms]
    end

    def pr msg, pre_indent = " "
        indent = ""
        @indent_level.times do |i|
            indent += "    "
        end

        if $options[:short]
            puts "#{msg}"
        else
            puts "#{@time_now_rel_s} #{pre_indent} #{indent}#{msg}"
        end
    end

    def start_element(name)
        @stack.push({ :name => name, :attr => {} })
    end

    def end_element(name)
        e = @stack.pop
        a = e[:attr]
        update_ts a[:ts]

        case e[:name]
        when :trace
            case a[:level]
            when "noice"
                pr "#{e[:data]}", "T_N".gray
            when "debug"
                pr "#{e[:data]}", "T_D".green
            when "info"
                pr "#{e[:data]}", "T_I".bg_green
            when "error"
                pr "#{e[:data]}", "T_E".bg_red
            when "fatal"
                pr "#{e[:data]}", "T_F".bg_red.bold.blink
            else
                pr "#{e[:data]}"
            end

        when :poll
            if a[:val] == "ok"
                #pr "#{e[:name].to_s} OK", "POL".gray
            else
                pr "#{e[:data].to_s} NOT-OK", "POL".gray.bold
            end

        when :assert, :assert_poll
            if a[:val] == "ok"
                pr "#{e[:name].to_s} OK: #{a[:msg]}", "AST".bg_green
            else
                pr "#{e[:data].to_s} NOT-OK: #{a[:msg]}", "AST".bg_red
            end

        when :check, :check_poll
            if a[:val] == "ok"
                pr "#{e[:name].to_s} OK: #{a[:msg]}", "CHK".bg_green
            else
                pr "#{e[:data].to_s} NOT-OK: #{a[:msg]}", "CHK".bg_red
            end

        when :backtrace
            pr "Test script crash in:\n#{e[:data]}", "BUG".bg_red.bold

        when :run, :try, :try_ignore, :try_err, :run_err
            @indent_level -= 1

        when :run_stdin, :try_stdin, :try_ignore_stdin, :try_err_stdin, :run_err_stdin
            pr "#{e[:data]}", "IN ".gray

        when :run_stdout, :try_stdout, :try_ignore_stdout, :try_err_stdout, :run_err_stdout
            pr "#{e[:data]}", "OUT".green

        when :run_stderr, :try_stderr, :try_ignore_stderr, :try_err_stderr, :run_err_stderr
            pr "#{e[:data]}", "ERR".red

        when :run_end, :try_end, :try_ignore_end, :try_err_end, :run_err_end
            msg = "Exit #{a[:exitstatus].to_i}, took #{a[:ts_rel]} secs"
            if a[:exitstatus].to_i == 0
                pr msg, "RES".green.bold
            else
                pr msg, "RES".bg_red
            end

        when :console
            pr "#{e[:data]}", "CON".cyan

        when :bg
            pr "#{a[:name]}: #{a[:cmd]}", "BG ".magenta

        when :bg_stdout
            pr "#{a[:name]}-OUT: #{e[:data]}", "BG ".magenta

        when :bg_stderr
            pr "#{a[:name]}-ERR: #{e[:data]}", "BG ".bg_red

        when :test_end
            pr "Test failed: #{@test_stack[-1]}", "TST".bg_red if a[:status] != "ok"

        when :test_run_end
            if a[:status] == "ok"
                pr "OK: #{a[:file]}", "TC".green.bold
            else
                pr "Not-OK: #{a[:file]}", "TC".bg_red
            end

        when :test_run
            @indent_level -= 1

        when :test
            @indent_level -= 1
            @test_stack.pop

        when :check_capability_end
            if a[:status] == "ok"
                pr "Capability OK", "CAP".bg_green
            else
                pr "capability NOT OK", "CAP".bg_red
            end

        when :check_capability
            @indent_level -= 1

        end
    end

    def attr(name, value)
        @stack[-1][:attr][name] = value
    end

    def attrs_done()
        e = @stack[-1]
        a = e[:attr]
        update_ts a[:ts]

        case e[:name]
        when :run, :try, :try_ignore, :try_err, :run_err
            pr "#{e[:name].upcase}-#{a[:on]}: #{a[:cmd]}", "#{e[:name].upcase}".bg_cyan
            @indent_level += 1

        when :test_run
            pr "#{a[:file]}", "TC".bg_blue
            @indent_level += 1

        when :test
            pr "#{a[:name]}", "TST".bg_blue
            @test_stack << a[:name]
            @indent_level += 1

        when :check_capability
            pr "Check Capabilities", "CAP".bg_magenta
            @indent_level += 1
        end
    end

    def instruct(target)
    end

    def end_instruct(target)
    end

    def doctype(str)
    end

    def comment(str)
    end

    def cdata(str)
    end

    def value(str)
        @stack[-1][:data] = str.as_s
    end

    def error(message, line, column)
    end

    def abort(name)
    end
end

class Brief < ::Ox::Sax
    def initialize
        @stack = []
        @indent_level = 1
    end

    def pr msg, pre_indent = " "
        indent = ""
        @indent_level.times do |i|
            indent += "    "
        end

        if $options[:short]
            puts "#{msg}"
        else
            puts "#{@time_now_rel_s} #{pre_indent} #{indent}#{msg}"
        end
    end

    def start_element(name)
        @stack.push({ :name => name, :attr => {}, :indent => @indent_level })
        @indent_level += 1
    end

    def end_element(name)
        e = @stack.pop
        @indent_level -= 1
    end

    def attr(name, value)
        @stack[-1][:attr][name] = value
    end

    def attrs_done()
        e = @stack[-1]

        a = e[:attr]

        case e[:name]
        when :test_run_end
            if a[:status] == "ok"
                pr "OK: #{a[:file]}", "TC".bg_green
            else
                pr "NOT-OK: #{a[:file]}", "TC".bg_red
            end
        end
    end

    def instruct(target)
        @stack.push({:name => "instruct", :attr => {}})
    end

    def end_instruct(target)
        e = @stack.pop
    end

    def doctype(str)
    end

    def comment(str)
    end

    def cdata(str)
    end

    def value(str)
        @stack[-1][:data] = str.as_s
    end

    def error(message, line, column)
    end

    def abort(name)
    end
end


handler = nil

if $options[:brief]
    handler = Brief.new()
else
    handler = Sample.new()
end

Ox.sax_parse(handler, STDIN, :skip => :skip_none)
