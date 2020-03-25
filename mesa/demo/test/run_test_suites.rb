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
#            { name: "dk-t14",  image: "mipsel/mfi_vsc7468_48.mfi", branch:"master" }, MESA-428 / Atom issue
            { name: "dk-t15",   image: "mipsel/mfi_vsc7437.mfi",         branch:"master" },
#            { name: "dk-t16",   image: "mipsel/mfi_vsc7429.mfi",   branch:"master" } Removed due to Ref-board instability (hangs)
            { name: "dk-t34-1",  image: "lan966x/fit_ls1046_lan9668.itb", branch:"master.mas" }
           ]

$test_suites  = ["suite_port.rb",
                 "suite_l2_basic.rb",
                 "suite_qos.rb",
                 "suite_vop.rb",
                 "suite_ts.rb",
                 "suite_l3_rt.rb",
                 "suite_examples.rb"]

if File.file?("../../../../easytest/test-setup-server/et")
    $et = "../../../../easytest/test-setup-server/et"
else
    $et = "/easytest/easytest/test-setup-server/et"
end

$suites_log = []
skip_system = []
run_system = []

def run_(cmd, verify=true)
    puts "Executing #{cmd}"
    res = system cmd
    if verify
        raise "Running '#{cmd}' failed" if $? != 0
    end
    res
end


def dl_file uri, out
    FileUtils.mkdir_p File.dirname(out)
    puts "Downloading #{uri} to #{out}"
    IO.write(out, Net::HTTP.get(URI(uri)))
end

def run_suites(t)
    $test_suites.each { |name|
        $suites_log << "#{t}.#{name}.log"
        res = run_("./#{name} > #{t}.#{name}.log", false)
        if res
            puts "Failed running #{name}"
        end
    }
end

def suite_log_merge name
    l = File.open(name,"w")
    found_start = false
    test_end = ""
    $suites_log.each { |log|
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

# Release the system
if (File.file?(".mscc-libeasy-topology.yaml"))
    puts ".mscc-libeasy-topology.yaml Released"
    run_("#{$et} -l release", false)
elsif (File.file?("#{ENV['HOME']}/.mscc-libeasy-topology.yaml"))
    run_("#{$et} release", false)
end


$systems.each { |system|
    # Compose path to the image and test folder of the requested branch
    jenkins_images = "http://soft00.microsemi.net:8080/job/API-mesa/job/" + system[:branch] + "/lastSuccessfulBuild/artifact/images"

    # Reserve system
    res = run_("#{$et} -l reserve #{system[:name]}", false)
    if !res
        skip_system << system[:name]
        next
    end
    run_system << system[:name]

    # Download latest image from jenkins
    dl_file "#{jenkins_images}/#{system[:image]}", "img"
    # Download latest test folder from jenkins
    dl_file "#{jenkins_images}/et.tar.gz", "et.tar.gz"

    # Upload image to DUT
    run_("#{$et} upload img")

    # Unpack Easy Test folder tar file
    run_("rm -rf test")
    run_("tar xzf et.tar.gz")

    # Copy the reserved system topology file to the created test folder
    run_("cp .mscc-libeasy-topology.yaml test")

    begin
        # Change directory to the created test folder
        cur = Dir.pwd
        Dir.chdir "./test"
        # Run test suites on system.
        run_suites system[:name]

        # Move .log files from created test folder to test folder
        run_("mv *.log ../.")

    rescue
        run_("echo script #{system[:name]} failed")

    ensure
        Dir.chdir cur

        run_("date")

        # Release system
        run_("#{$et} release")

        run_("date")
    end

}
puts "\nTested on systems:  #{run_system.join(" ")}"
puts "Skipped systems:    #{skip_system.join(" ")}"
puts "Merge the test-suite logs to one:"
suite_log_merge "suite_log_merged.log"

