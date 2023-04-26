#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'rubygems'
require 'bundler/setup'
require 'pp'
require 'open3'
require 'optparse'

$options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: repeat.rb [options] -- cmd-to-call"

    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit
    end

    opts.on("-t", "--times cnt", "How many times to repeat the test") do |t|
        $options[:times] = t.to_i
    end

    opts.on("-o", "--output folder", "Folder to store the output in") do |f|
        $options[:out_folder] = f
    end
end.parse!

if $options[:times].nil?
    $stderr.puts "Times is missing"
    exit -1
end

if $options[:out_folder].nil?
    $stderr.puts "Output folder missing"
    exit -1
end

if File.exist? $options[:out_folder]
    $stderr.puts "Output folder exists already"
    exit -1
end

if not system("mkdir -p #{$options[:out_folder]}")
    $stderr.puts "Could not create output folder"
    exit -1
end

$ok = 0
$err = 0

puts "#{Time.now.strftime("%y-%m-%d %T")}  START - Cnt: #{$options[:times]}"
$options[:times].times do |i|
    begin
        o = File.open("#{$options[:out_folder]}/run-%04d.stdout" % [i], 'w')
        e = File.open("#{$options[:out_folder]}/run-%04d.stderr" % [i], 'w')

        t1 = Time.now
        pid = spawn(*ARGV, {:out => o, :err => e})
        Process.wait pid
        res = $?
        t2 = Time.now

        s = ""
        took = "took #{t2 - t1} seconds"
        if res.exitstatus == 0
            File.write("#{$options[:out_folder]}/run-%04d.ok" % [i], "#{res.exitstatus}")
            $ok += 1
            s = "ok"
        else
            File.write("#{$options[:out_folder]}/run-%04d.not-ok" % [i], "#{res.exitstatus}")
            $err += 1
            s = "not-ok - #{res.exitstatus}"
        end

        puts "#{Time.now.strftime("%y-%m-%d %T")}  %04d/%04d-%04d #{s} #{took}" % [i, $options[:times] - 1, $err]

    ensure
        o.close if not o.nil?
        e.close if not e.nil?
    end
end

puts "#{Time.now.strftime("%y-%m-%d %T")}  END - Error cnt: #{$err}"

