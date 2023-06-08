#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'open3'
require 'fileutils'
require 'net/http'
require_relative './libeasy/utils'

$systems = [
    # dk-t33, Maserati systems
    { name: "dk-t33-0", image: "armv7_lan966x.itb",          branch:"master", parallel: "no", server: "33", started: "no" },
    { name: "dk-t33-2", image: "armv7_lan966x.itb",          branch:"master", parallel: "no", server: "33", started: "no" },
    { name: "dk-t33-4", image: "armv7_lan966x.itb",          branch:"master", parallel: "no", server: "33", started: "no" },
    { name: "dk-t33-5", image: "armv7_lan966x.itb",          branch:"master", parallel: "no", server: "33", started: "no" },

    # dk-t34, starting with Fireant systems
    { name: "dk-t34-3", image: "arm64_vsc7558TSN.itb",       branch:"master", parallel: "no", server: "34", started: "no" },
    { name: "dk-t34-4", image: "arm64_vsc7558TSN.itb",       branch:"master", parallel: "no", server: "34", started: "no" },
    { name: "dk-t34-5", image: "arm64_vsc7558TSN.itb",       branch:"master.laguna-19", parallel: "no", server: "34", started: "no" },
    { name: "dk-t34-0", image: "mipsel_vsc7468_pcb110.mfi",  branch:"master", parallel: "no", server: "34", started: "no" },
    { name: "dk-t34-2", image: "ls1046_vsc7512.itb",         branch:"master", parallel: "no", server: "34", started: "no" },

    # dk-t35, MIPS systems
    { name: "dk-t35-2", image: "mipsel_vsc7437.mfi",         branch:"master", parallel: "no", server: "35", started: "no" },
    { name: "dk-t35-1", image: "mipsel_vsc7514_pcb123.mfi",  branch:"master", parallel: "no", server: "35", started: "no" },
    { name: "dk-t35-4", image: "mipsel_vsc7428.mfi",         branch:"master", parallel: "no", server: "35", started: "no" },
    { name: "dk-t35-6", image: "armv7_lan969x_sr_bbb.itb",   branch:"master.laguna-19", parallel: "no", server: "35", started: "no" },

#   { name: "dk-t31",   image: "arm64_vsc7546TSN.itb",       branch:"master", parallel: "no", server: "35", started: "no" },
#   { name: "dk-t35-6", image: "mipsel_vsc7468_48.mfi",      branch:"master", parallel: "no", server: "35", started: "no" }, MESA-428 / Atom issue
           ]

if File.file?("../../../../easytest/test-setup-server/et")
    $et = "../../../../easytest/test-setup-server/et"
else
    $et = "/easytest/easytest/test-setup-server/et"
end

$suites_log = []

def suite_log_merge name
    suites_log = Dir.glob("*.log")

    l = File.open(name,"w")
    found_start = false
    test_end = ""

    suites_log.each { |log|
        puts "Merge '#{log}'..."
        File.open(log).each do |line|
            if found_start
                if line.include?("xml version") || line.include?("<tests ")
                    next
                end
            end
            
            if line.include?("<tests ") && !found_start
                found_start = true
            end
            
            if line.include?("tests_end")
                test_end = line # append at the end
                break
            end
            l.write line
        end
    }
    l.write test_end
    l.write "</tests>"
    puts "Merged to file '#{name}'"
end

puts "-----delete all .log files-----"
system("rm *.log")

puts "-----Download and unpack all test folders from Jenkins-----"
$systems.each { |system|
    # Compose path to the image and test folder of the requested branch
    jenkins_images = "http://soft00.microsemi.net:8080/job/API-mesa/job/" + system[:branch] + "/lastSuccessfulBuild/artifact/images"

    puts("Download latest test folder from jenkins")
    dl_file "#{jenkins_images}/et.tar.gz", "et.tar.gz"

    puts("Unpack Easy Test folder tar file")
    dir = "#{system[:name]}-#{system[:branch]}-test"
    run_("rm -rf #{dir}")
    run_("mkdir #{dir}")
    run_("tar xzf et.tar.gz -C #{dir}")
}

$parallel_threads = []
$sequential_threads = []
def start_test(system)
    # Compose path to the image and test folder of the requested branch
    jenkins_images = "http://soft00.microsemi.net:8080/job/API-mesa/job/" + system[:branch] + "/lastSuccessfulBuild/artifact/images"

    puts("Start test suites on system #{system[:name]} in a thread")
    t = Thread.new do
        system "GIT_BRANCH_NAME=#{system[:branch]} ./utils/run-suites-on.rb --system #{system[:name]} --dir #{system[:name]}-#{system[:branch]}-test/test --image #{jenkins_images}/#{system[:image]}"
    end
    t
end

puts "-----Start test on all 'parallel' systems in a thread.-----"
$systems.each { |system|
    if (system[:parallel] == "yes")
        $parallel_threads << start_test(system)
    end
}

def start_server_sequential(server)
    t = nil
    $systems.each { |system|
        if ((system[:parallel] == "no") && (system[:server] == server) && (system[:started] == "no"))
            t = start_test(system)
            system[:started] = "yes"
            break
        end
    }
    t
end

puts "-----Start test on all 'sequential' systems.-----"
seq_done = false
while (!seq_done)
    seq_done = true
    ["33", "34", "35"].each_with_index do |s, i|
        t = $sequential_threads[i]
        if (t == nil)
            t = start_server_sequential(s)
        end
        if (t != nil)
            # Thread is not done
            seq_done = false
            if (t.join(60) != nil)
                # Thread is done
                t = nil
            end
        end
        $sequential_threads[i] = t
    end
end
puts "-----All 'sequential' tests are completed-----"

puts "-----Wait for all 'parallel' tests to complete-----"
$parallel_threads.each do |t|
  t.join
end
puts "-----All 'parallel' tests are completed-----"

puts "-----Move all test-suite log files from created test folders to test folder-----"
$systems.each { |system|
    system("mv ./#{system[:name]}-#{system[:branch]}-test/test/*.log .")
}

puts("-----Merge the test-suite log files to one-----")
suite_log_merge("suite_log_merged.log")
