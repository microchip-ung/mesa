#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

$suites_log = Dir["*.log"]

puts $suites_log

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

suite_log_merge "suite_log_merged.log"

system "cat suite_log_merged.log | libeasy/xml2allure.rb -a /data/jenkins/jobs/api-test/workspace/allure-2.10.0/bin/allure -l /data/jenkins/jobs/api-test/workspace/logs -o /data/www/public_html/api-test -u http://soft00.dk.vitesse.com/api-test"
