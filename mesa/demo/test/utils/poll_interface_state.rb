#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'rubygems'
require 'bundler/setup'
require 'optparse'

$timeout = 3.0
$down = false

global = OptionParser.new do |opts|
    opts.banner = "Usage: poll_interface_state.rb [options] interfaces..."

  opts.on("-t", "--timeout <timeout>", "Timeout") do |t|
      $timeout = t.to_f
  end

  opts.on("-d", "--down", "Wait for interfaces to be down") do
      $down = true
  end

  opts.on("-u", "--up", "Wait for interfaces to be up") do
      $down = false
  end
end.order!


b = Time.now.to_f
ok = []

first = true

while (Time.now.to_f - b) < $timeout
    if first
        first = false
    else
        sleep 0.1
    end

    ARGV.each do |i|
        next if ok.include? i

        link = %x{ip link show dev #{i}}
        if /<([^>]+)>/ =~ link.lines.first
            flags = $1.split ","

            if $down
                if not flags.include? "LOWER_UP"
                    ok << i
                    puts "DOWN: #{i}"
                end
            else
                if flags.include? "LOWER_UP"
                    ok << i
                    puts "UP: #{i}"
                end
            end
        end
    end

    break if ok.size == ARGV.size
end

if ok.size != ARGV.size
    puts "Time is out, the following interfaces is still pending:"

    ARGV.each do |i|
        next if ok.include? i
        puts "  #{i}"
    end

    exit -1
end

exit 0
