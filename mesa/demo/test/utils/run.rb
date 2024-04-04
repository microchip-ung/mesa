#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'rubygems'
require 'bundler/setup'
require 'pp'
require 'open3'
require 'optparse'

$options = {}
$options[:times] = 1
OptionParser.new do |opts|
    opts.banner = "Usage: run.rb [options] -- list of tests"
    opts.banner += "\nExample: utils/run.rb `find -name \"l3_ip_mc*.rb\"` -t 10 -o log"
    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit
    end

    opts.on("-t", "--times cnt", "How many times to repeat the test") do |t|
        $options[:times] = t.to_i
    end

    $options[:stop] = false
    opts.on("-s", "--stop", "Stop if test fails") do |s|
        $options[:stop] = s
    end

    opts.on("-o", "--output folder", "Folder to store the output in") do |f|
        $options[:out_folder] = f
    end
end.parse!

if $options[:out_folder].nil?
    $stderr.puts "Output folder missing"
    exit -1
end

if File.exist? $options[:out_folder]
    system("rm -fr #{$options[:out_folder]}")
end

if not system("mkdir -p #{$options[:out_folder]}")
    $stderr.puts "Could not create output folder"
    exit -1
end

$ok = 0
$err = 0


puts "Tests to be executed:"
ARGV.each { |test|
    puts "#{test}"
}

$options[:times].times do |i|
    begin
        o = File.open("#{$options[:out_folder]}/run-%04d.stdout" % [i+1], 'w')
        e = File.open("#{$options[:out_folder]}/run-%04d.stderr" % [i+1], 'w')

        ARGV.each { |test|
            t1 = Time.now
            print "%s %04d/%04d-%04d %-30s" % [Time.now.strftime("%y-%m-%d %T"), i+1, $options[:times], $err, test]
            pid = spawn("#{test}", {:out => o, :err => e})
            Process.wait pid
            res = $?
            t2 = Time.now
            s = ""
            took = "took #{t2 - t1} seconds"
            if res.exitstatus == 0
                File.write("#{$options[:out_folder]}/run-%04d.ok" % [i+1], "#{res.exitstatus}")
                $ok += 1
                s = "ok"
            else
                File.write("#{$options[:out_folder]}/run-%04d.not-ok" % [i+1], "#{res.exitstatus}")
                $err += 1
                s = "not-ok - #{res.exitstatus}"
                if $err > 0 && $options[:stop]
                    break
                end
            end
            puts "#{s} #{took}"
        }
        if $err > 0 && $options[:stop]
            break
        end

    ensure
        o.close if not o.nil?
        e.close if not e.nil?
    end
end

puts "#{Time.now.strftime("%y-%m-%d %T")}  END - Error cnt: #{$err}"
