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
$options[:out_folder] = nil  # Default: no output folder, suppress logs

OptionParser.new do |opts|
  opts.banner = "Usage: run.rb [options] -- list of tests"
  opts.banner += "\nExample: utils/run.rb `find -name \"l3_ip_mc*.rb\"` -t 10 -o log"

  opts.on("-h", "--help", "This message") do
    puts opts
    exit
  end

  opts.on("-t", "--times cnt", "How many times to repeat the test") do |t|
    $options[:times] = t.to_i
  end

  $options[:stop] = false
  opts.on("-s", "--stop", "Stop if test fails") do
    $options[:stop] = true
  end

  opts.on("-o", "--output folder", "Folder to store the output in") do |f|
    $options[:out_folder] = f
  end
end.parse!

# Convert relative filenames (without path) to ./filename format
ARGV.map! do |test|
  if !test.start_with?("/", "./") && File.exist?(test)  # If file exists locally and is not an absolute/relative path
    "./#{test}"
  else
    test  # Keep as-is
  end
end

# Create output folder if specified
if $options[:out_folder]
  if File.exist? $options[:out_folder]
    system("rm -fr #{$options[:out_folder]}")
  end

  unless system("mkdir -p #{$options[:out_folder]}")
    $stderr.puts "Could not create output folder"
    exit -1
  end
end

$ok = 0
$err = 0

puts "Tests to be executed:"
ARGV.each { |test| puts test }

$options[:times].times do |i|
  begin
    o = e = nil
    if $options[:out_folder]
      o = File.open("#{$options[:out_folder]}/run-%04d.stdout" % [i + 1], 'w')
      e = File.open("#{$options[:out_folder]}/run-%04d.stderr" % [i + 1], 'w')
    else
      o = e = File.open("/dev/null", "w")  # Suppress all output
    end

    ARGV.each do |test|
      t1 = Time.now
      print "%s %04d/%04d-%04d %-30s" % [Time.now.strftime("%y-%m-%d %T"), i + 1, $options[:times], $err, test]

      pid = spawn("#{test}", out: o, err: e)  # Redirect both stdout and stderr

      Process.wait pid
      res = $?
      t2 = Time.now
      took = "took #{t2 - t1} seconds"

      if res.exitstatus == 0
        File.write("#{$options[:out_folder]}/run-%04d.ok" % [i + 1], "#{res.exitstatus}") if $options[:out_folder]
        $ok += 1
        s = "ok"
      else
        File.write("#{$options[:out_folder]}/run-%04d.not-ok" % [i + 1], "#{res.exitstatus}") if $options[:out_folder]
        $err += 1
        s = "not-ok - #{res.exitstatus}"
        break if $err > 0 && $options[:stop]
      end
      puts "#{s} #{took}"
    end

    break if $err > 0 && $options[:stop]

  ensure
    o&.close
    e&.close
  end
end

puts "#{Time.now.strftime("%y-%m-%d %T")}  END - Error cnt: #{$err}"
