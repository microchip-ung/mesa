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

def dl uri, out
    FileUtils.mkdir_p File.dirname(out)
    puts "Downloading #{uri} to #{out}"
    IO.write(out, Net::HTTP.get(URI(uri)))
end

$system = ""
def run(cmd, verify = true)
    puts "#{$system}: run #{cmd}"

    res = system cmd

    if verify
        raise "#{$system}: '#{cmd}' failed" if $? != 0
    end

    res
end

def print_err e
    msg = ""
    msg += "#{$system}: Traceback (most recent call last):\n"
    e.backtrace.to_enum.with_index.reverse_each do |t, i|
        if i != 0
            msg += "#{$system}:\t #{i}: #{t}\n"
        else
            msg += "#{$system}: #{t}: #{e}#{e.class ? " (#{e.class})" : ''}"
        end
    end
    puts msg
end

$options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: run-on.rb [options]"

    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit
    end

    opts.on("-s", "--system system", "System to reserve") do |s|
        $options[:system] = s
        $system = s
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

    opts.on("-e", "--et path", "Use this et script") do |e|
        $options[:et] = e
    end

end.parse!

# Change directory to the test folder
Dir.chdir $options[:dir]

if $options[:et] != nil
    $et = $options[:et]
elsif File.file?("../../../../../../easytest/test-setup-server/et")
    $et = "../../../../../../easytest/test-setup-server/et"
else
    $et = "/easytest/easytest/test-setup-server/et"
end

#$test_suites  = ["suite_port.rb"]
$test_suites = Dir.glob("suite_*.rb")

def run_suites(system)
    $test_suites.each { |suite|
        puts("run suite #{suite} on system #{system}")
        res = run("./#{suite} > #{system}.#{suite}.log", false)
#res = 1
        if !res
            puts "Failed running suite #{suite} on system #{system}"
        end
    }
end

if ($options[:system] != nil) && ($options[:image] != nil)
    # Reserve system
    t1 = Time.now
    seconds = ($options[:timeout] != nil) ? $options[:timeout] : 0
    puts("#{$system}: Try reserve");
    reserved = false
    failed = false
    begin
        loop do
            res = run("#{$et} -l reserve #{$system}", false)
            if res
                reserved = true
                break   # break on sucess
            end

            if ((Time.now - t1) > seconds)
                puts("#{$system}: Reserve time-out after #{seconds} seconds");
                exit 7  # timeout - return with error
            end

            puts("#{$system}: Reserve failed, will try again (#{Time.now - t1} < #{seconds})");
            sleep(30)   # sleep and try again
            next
        end
        puts("#{$system}: Reservation successful");

        10.times do
            begin
                puts("#{$system}: Download latest image from jenkins");
                dl "#{$options[:image]}", "img"

                puts("#{$system}: Upload image to DUT")
                run("#{$et} -l upload img")
                break
            rescue => e
                print_err e
            end
        end

        puts("#{$system}: Run test suites")
        run("date")
        run_suites $system

    rescue => e
        puts("#{$system}: Test failed")
        failed = true
        print_err e

    ensure
        # Release $system
        begin
            if (reserved)
                puts("#{$system}: Release");
                run("#{$et} -l release", false)
            end
        rescue
        end
        run("date")

        if (failed)
            exit 1
        end
    end
end
