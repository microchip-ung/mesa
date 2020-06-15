#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'open3'
require 'fileutils'
require 'net/http'
require_relative './libeasy/utils'

$systems = [
#            { name: "dk-t11",   image: "mipsel_vsc7514_pcb123.mfi",  branch:"master" },
            { name: "dk-t13",   image: "mipsel_vsc7468_pcb110.mfi",  branch:"master" },
            { name: "dk-t31",   image: "arm64_vsc7546TSN.itb",       branch:"master" },
            { name: "dk-t34-4", image: "arm64_vsc7558TSN.itb",       branch:"master" },
            { name: "dk-t34-3", image: "arm64_vsc7558TSN.itb",       branch:"master" },
#            { name: "dk-t14",  image: "mipsel_vsc7468_48.mfi", branch:"master" }, MESA-428 / Atom issue
            { name: "dk-t15",   image: "mipsel_vsc7437.mfi",         branch:"master" },
#            { name: "dk-t16",   image: "mipsel_vsc7429.mfi",   branch:"master" } Removed due to Ref-board instability (hangs)
            { name: "dk-t34-1", image: "arm64_ls1046_lan9668.itb", branch:"master.mas" },
            { name: "dk-t06",   image: "arm64_ls1046_lan9668.itb", branch:"master.mas" },
            { name: "dk-t35-0", image: "arm64_ls1046_lan9662.itb", branch:"master.mas" },
            { name: "dk-t34-2", image: "ls1046_vsc7512.itb",       branch:"master" }
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

puts "-----Start test on all systems in a thread-----"
threads = []
$systems.each { |system|

    # Compose path to the image and test folder of the requested branch
    jenkins_images = "http://soft00.microsemi.net:8080/job/API-mesa/job/" + system[:branch] + "/lastSuccessfulBuild/artifact/images"

    puts("Download latest test folder from jenkins")
    dl_file "#{jenkins_images}/et.tar.gz", "et.tar.gz"

    puts("Unpack Easy Test folder tar file")
    run_("rm -rf #{system[:name]}-test")
    run_("mkdir #{system[:name]}-test")
    run_("tar xzf et.tar.gz -C #{system[:name]}-test")

    puts("Run all test suites on system #{system[:name]} in a thread")
    threads << Thread.new do
        system "./utils/run-suites-on.rb --system #{system[:name]} --dir #{system[:name]}-test/test --image #{jenkins_images}/#{system[:image]}"
    end

}

puts "-----Wait for all tests to complete-----"
threads.each do |t|
  t.join
end
puts "-----All tests are completed-----"

puts "-----Move all test-suite log files from created test folders to test folder-----"
$systems.each { |system|
    system("mv ./#{system[:name]}-test/test/*.log .")
}

puts("-----Merge the test-suite log files to one-----")
suite_log_merge("suite_log_merged.log")
