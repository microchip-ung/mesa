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


$options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: run-on.rb [options] -- list of tests"

    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit
    end

    opts.on("-s", "--system system", "System to reserve") do |s|
        $options[:system] = s
    end

    opts.on("-i", "--image image", "Image to upload") do |i|
        $options[:image] = i
    end

    opts.on("-b", "--branch branch", "branch to upload") do |b|
        $options[:branch] = b
    end

    opts.on("-t", "--timeout seconds", "Keep trying to reserve the needed test system, until success or timeout") do |t|
        $options[:timeout] = t
    end

end.parse!

if File.file?("../../../../easytest/test-setup-server/et")
    $et = "../../../../easytest/test-setup-server/et"
else
    $et = "/easytest/easytest/test-setup-server/et"
end

def dl_file uri, out
    FileUtils.mkdir_p File.dirname(out)
    puts "Downloading #{uri} to #{out}"
    IO.write(out, Net::HTTP.get(URI(uri)))
end

def run_(cmd, verify=true)
    puts "Executing #{cmd}"
    res = system cmd
    if verify
        raise "Running '#{cmd}' failed" if $? != 0
    end
    res
end

def run_suites(system)
    ARGV.each { |suite|
        puts("run suite #{suite} on system #{system}")
        res = run_("./#{suite} > #{system}.#{suite}.log", false)
        if !res
            puts "Failed running suite #{suite} on system #{system}"
        end
    }
end

if ($options[:system] != nil) && ($options[:image] != nil) && ($options[:branch] != nil)
    system = $options[:system]

    # Compose path to the image and test folder of the requested branch
    jenkins_images = "http://soft00.microsemi.net:8080/job/API-mesa/job/" + $options[:branch] + "/lastSuccessfulBuild/artifact/images"

    # Reserve system
    t1 = Time.now
    seconds = ($options[:timeout] != nil) ? $options[:timeout] : 0
    puts("Try reserve system #{system}");
    loop do
        res = run_("#{$et} -l -n #{system} reserve #{system}", false)
        if res
            break   # break on sucess
        end

        if ((Time.now - t1) > seconds)
            exit 7  # timeout - return with error
        end

        sleep(30)   # sleep and try again
        next
    end
    puts("Reservation of #{system} successful");

    puts("Download latest image from jenkins");
    dl_file "#{jenkins_images}/#{$options[:image]}", "#{system}-img"
    puts("Download latest test folder from jenkins")
    dl_file "#{jenkins_images}/et.tar.gz", "#{system}-et.tar.gz"

    puts("Upload image to DUT")
    run_("#{$et} -l -n #{system} upload #{system}-img")

    puts("Unpack Easy Test folder tar file")
    run_("rm -rf #{system}-test")
    run_("mkdir #{system}-test")
    run_("tar xzf et.tar.gz -C #{system}-test")

    puts("Move the reserved system topology file to the created test folder")
    run_("mv .mscc-libeasy-topology#{system}.yaml ./#{system}-test/test/.mscc-libeasy-topology.yaml")

    begin
        run_("date")

        # Change directory to the created test folder
        cur = Dir.pwd
        Dir.chdir "./#{system}-test/test"

        puts("Run test suites on system #{system}.")
        run_suites system

        # Move .log files from created test folder to test folder
        run_("mv *.log ../../.")

    rescue
        run_("Test on system #{system} failed")

    ensure
        # Release system
        run_("#{$et} -l release")

        run_("date")

        Dir.chdir cur

    end
end
