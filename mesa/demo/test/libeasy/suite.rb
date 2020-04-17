#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'ox'
require 'open3'
require 'optparse'

$stdout.sync = true
$stderr.sync = true

$err_cnt = 0

def xml_attr name, val
    return "#{name}=#{val.to_s.encode(:xml => :attr)}"
end

def xml_attrs a
    return "" if a.nil?
    return "" if a.size == 0
    return " #{a.to_a.map{|x| xml_attr(x[0], x[1])}.join(" ")}"
end

def xml_tag_start tag, attr = nil
    return "<#{tag}#{xml_attrs(attr)}>"
end

def xml_tag_end tag
    return "</#{tag}>"
end

def xml_tag tag, body = nil, attr = nil
    if body
        body = body.scrub
        body.delete!("\x00")
        body.delete!("\x0d")
        return "<#{tag}#{xml_attrs(attr)}>#{body.encode(:xml => :text)}</#{tag}>"
    else
        return "<#{tag}#{xml_attrs(attr)} />"
    end
end

def xml_ts ts
    return "#{ts.tv_sec}.#{"%09d" % ts.tv_nsec}"
end

def xml_ts_diff a, b
    return "#{"%.6f" % (b - a).to_f}"
end


puts "<?xml version=\"1.0\"?>"

$ts_tests_begin = Time.now
puts xml_tag_start "tests", {"ts" => xml_ts($ts_tests_begin)}

class TestSnooper < ::Ox::Sax
    def initialize
        @stack = []
        @indent_level = 1
    end

    def pr l, msg
        indent = ""
        l.times do |i|
            indent += "    "
        end

        puts "#{indent}#{msg}"
    end

    def start_element(name)
        if @stack.size > 0 and @stack[-1][:printed].nil?
            e = @stack[-1]
            pr e[:indent], xml_tag_start(e[:name], e[:attr])
            e[:open] = true
            e[:printed] = true
        end

        @stack.push({ :name => name, :attr => {}, :indent => @indent_level })
        @indent_level += 1
    end

    def end_element(name)
        e = @stack.pop

        @indent_level -= 1
        if e[:open].nil?
            pr e[:indent], xml_tag(e[:name], e[:data], e[:attr])
        else
            pr e[:indent], xml_tag_end(e[:name])
        end
    end

    def attr(name, value)
        @stack[-1][:attr][name] = value
    end

    def attrs_done()
        e = @stack[-1]
    end

    def instruct(target)
        @stack.push({ :name => "instruct", :attr => {}, :printed => true})
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



def run cmd, flags = {}
    handler = TestSnooper.new()

    sn = nil
    if $suite_name.nil?
        sn = File.basename($0, ".rb")
    else
        sn = $suite_name
    end

    cmd << "--test-suite-name"
    cmd << sn

    if flags[:name]
        cmd << "--test-uuid"
        cmd << flags[:name]
    end

    res = nil
    out_reader, out_writer = IO.pipe

    pid = spawn(*cmd, {:out => out_writer.fileno})
    t = Thread.new {
        p, r = Process.wait2 pid
        out_writer.close
        res = r.to_i
    }

    Ox.sax_parse(handler, out_reader, :skip => :skip_none)
    t.join

    $err_cnt += 1 if res != 0
    if flags.include? :abort_on_err and res != 0
        exit -1
    end
end

END {
    ts_tests_end = Time.now
    s = "ok"
    s = "not-ok" if $err_cnt > 0
    a = {
        "ts"     => xml_ts(ts_tests_end),
        "ts_rel" => xml_ts_diff($ts_tests_begin, ts_tests_end),
        "status" => s,
    }

    puts xml_tag "tests_end", nil, a
    puts xml_tag_end "tests"

    if $err_cnt > 0
        exit (-1)
    else
        exit (0)
    end
}


