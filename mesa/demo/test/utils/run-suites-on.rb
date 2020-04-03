#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'rubygems'
require 'bundler/setup'
require 'pp'
require 'open3'
require 'optparse'
require 'fileutils'
require 'net/http'
require_relative '../libeasy/utils'


$options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: run-on.rb [options]"

    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit
    end

    opts.on("-s", "--system system", "System to reserve") do |s|
        $options[:system] = s
    end

    opts.on("-d", "--dir dir", "Change directory to dir before doing anything.") do |d|
        $options[:dir] = d
    end

    opts.on("-i", "--image image", "Image to upload") do |i|
        $options[:image] = i
    end

    opts.on("-t", "--timeout seconds", "Keep trying to reserve the needed test system, until success or timeout") do |t|
        $options[:timeout] = t
    end

end.parse!

# Change directory to the test folder
Dir.chdir $options[:dir]

if File.file?("../../../../../../easytest/test-setup-server/et")
    $et = "../../../../../../easytest/test-setup-server/et"
else
    $et = "/easytest/easytest/test-setup-server/et"
end

#$test_suites  = ["suite_port.rb"]
$test_suites = Dir.glob("suite_*.rb")

def run_suites(system)
    $test_suites.each { |suite|
        puts("run suite #{suite} on system #{system}")
        res = run_("./#{suite} > #{system}.#{suite}.log", false)
        if !res
            puts "Failed running suite #{suite} on system #{system}"
        end
    }
end

if ($options[:system] != nil) && ($options[:image] != nil)
    system = $options[:system]

    # Reserve system
    t1 = Time.now
    seconds = ($options[:timeout] != nil) ? $options[:timeout] : 0
    puts("Try reserve system #{system}");
    loop do
        res = run_("#{$et} -l reserve #{system}", false)
        if res
            break   # break on sucess
        end

        if ((Time.now - t1) > seconds)
            puts("Timeout on reserve system #{system}. Waited  #{seconds} seconds");
            exit 7  # timeout - return with error
        end

        sleep(30)   # sleep and try again
        next
    end
    puts("Reservation of #{system} successful");

    puts("Download latest image from jenkins");
    dl_file "#{$options[:image]}", "img"

    puts("Upload image to DUT")
    run_("#{$et} -l upload img")

    failed = false
    begin
        puts("Run test suites on system #{system}.")
        run_("date")
        run_suites system

    rescue
        puts("Test on system #{system} failed")
        failed = true

    ensure
        # Release system
        run_("#{$et} -l release")
        run_("date")

        if (failed)
            exit 1
        end
    end
end
