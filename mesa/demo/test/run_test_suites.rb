#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'open3'
require 'fileutils'
require 'net/http'

$systems = [
            { name: "dk-t11",   image: "mipsel/mfi_vsc7514_pcb123.mfi",  branch:"master" },
            { name: "dk-t13",   image: "mipsel/mfi_vsc7468_pcb110.mfi",  branch:"master" },
            { name: "dk-t31",   image: "arm64/fit_vsc7546TSN.itb",       branch:"master" },
            { name: "dk-t34-4", image: "arm64/fit_vsc7558TSN.itb",       branch:"master" },
            { name: "dk-t34-3", image: "arm64/fit_vsc7558TSN.itb",       branch:"master" },
            { name: "dk-t12",   image: "mipsel/mfi_vsc7418.mfi",         branch:"master" },
            { name: "dk-t14",  image: "mipsel/mfi_vsc7468_48.mfi", branch:"master" }, MESA-428 / Atom issue
            { name: "dk-t15",   image: "mipsel/mfi_vsc7437.mfi",         branch:"master" },
            { name: "dk-t16",   image: "mipsel/mfi_vsc7429.mfi",   branch:"master" } Removed due to Ref-board instability (hangs)
            { name: "dk-t34-1",  image: "lan966x/fit_ls1046_lan9668.itb", branch:"master.mas" }
           ]

$test_suites  = "suite_port.rb suite_l2_basic.rb suite_qos.rb suite_vop.rb suite_ts.rb suite_l3_rt.rb suite_examples.rb"

if File.file?("../../../../easytest/test-setup-server/et")
    $et = "../../../../easytest/test-setup-server/et"
else
    $et = "/easytest/easytest/test-setup-server/et"
end

$suites_log = []

def suite_log_merge name
    l = File.open(name,"w")
    found_start = false
    test_end = ""

    suites_log = Dir.glob("*.log")
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

puts "-----Start test on all systems in background-----"
Thread.new {`echo hi`}

threads = []
$systems.each { |system|
     threads << Thread.new {system "./utils/run-on.rb --system #{system[:name]} --image #{system[:image]} --branch #{system[:branch]} #{$test_suites}"}
}

puts "-----Wait for all tests to complete-----"
#threads.each(&:join)
threads.each do |t|
  t.join
end
puts "-----All tests are completed-----"

puts("-----Merge the test-suite logs to one-----")
suite_log_merge("suite_log_merged.log")

