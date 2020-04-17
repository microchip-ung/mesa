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
    opts.banner = "Usage: run-on.rb [options]"

    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit
    end

    opts.on("-d", "--dir dir", "Change directory to dir before doing anything.") do |d|
        $options[:dir] = d
    end

    opts.on("-c", "--cmd cmd", "Command to run after reserving a test system") do |c|
        $options[:cmd] = f
    end

    opts.on("-t", "--timeout seconds", "Keep trying to reserve the needed test system, until success or timeout") do |t|
        $options[:timeout] = t
    end

    opts.on("-t", "--timeout seconds", "Keep trying to reserve the needed test system, until success or timeout") do |t|
        $options[:timeout] = t
    end

    opts.on("-s", "--system system", "System to reserve") do |s|
        $options[:system] = s
    end

    opts.on("-i", "--image image", "Image to upload") do |i|
        $options[:img] = i
    end

    opts.on("-o", "--out output", "Where to write the output of the command") do |o|
        $options[:out] = i
    end

end.parse!


