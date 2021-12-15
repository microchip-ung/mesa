#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'open3'
require 'optparse'

$options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: pcap_analyze.rb [options] pcap-file"

    opts.on("-h", "--help", "This message") do |v|
        puts opts
        exit 0
    end

    opts.on("--frame-count [TYPE]", [:all, :pcp], "Counting (all or per PCP) frames in 'count-sec' seconds after 'pre-tx-sec' seconds") do |f|
        $options[:frame_count] = f
    end

    opts.on("-p", "--pre-tx-sec seconds", "Pre TX in seconds before counting frames") do |p|
        $options[:pre_tx_sec] = p.to_i
    end

    opts.on("-c", "--count-sec seconds", "Counting frames in seconds after Pre TX") do |c|
        $options[:count_sec] = c.to_i
    end

    opts.on("--pcp-values x,y,z", Array, "List of PCP values to count") do |p|
        $options[:pcp_values] = p
    end

    opts.on("--exp-count x,y,z", Array, "List of expected frame count per PCP") do |e|
        $options[:exp_count] = e
    end

    opts.on("--exp-tolerance x,y,z", Array, "List of expected tolerance in frame count per PCP") do |t|
        $options[:exp_tolerance] = t
    end

    opts.on("--exp-cycle microsec", "Expected TAS cycle time") do |cyc|
        $options[:exp_cycle] = cyc.to_i
    end
end.parse!

if $options[:frame_count].nil?
    $stderr.puts "--frame-count is missing"
    exit 1
end

if $options[:frame_count] == :pcp
    if $options[:pcp_values].nil?
        $stderr.puts "--pcp-values is missing"
        exit 2
    end
end

if $options[:count_sec].nil?
    $stderr.puts "--count-sec is missing"
    exit 3
end

if $options[:exp_count].nil?
    $stderr.puts "--exp-count is missing"
    exit 3
end

if ARGV.size == 0
    $stderr.puts "pcap-file parameter is missing"
    exit 4
end

if !File.exists? ARGV[0]
    $stderr.puts "pcap file: #{ARGV[0]} does not exist"
    exit 5
end

$pcap_file = ARGV[0]
size = File.size?($pcap_file)

puts "Analyze #{$pcap_file} size #{size}"

pre_tx_sec = 0
if ($options[:pre_tx_sec] != nil)
    pre_tx_sec = $options[:pre_tx_sec]
end

exp_tolerance = Array.new(8,"0")
if ($options[:exp_tolerance] != nil)
    exp_tolerance = $options[:exp_tolerance]
end

exp_cycle_f = 0.0
max_diff_percent = 0.2
if ($options[:exp_cycle] != nil)
    exp_cycle_f = $options[:exp_cycle].to_f / 1000000  # Convert expected cycle from micro seconds to floating point seconds
    max_diff = (exp_cycle_f / 100) * max_diff_percent
end

count_sec = $options[:count_sec]

pre_tx_time = 0
last_time = 0
old_last_time = 0
count = 0
pcp_count = Array.new(8,0)
rx_time = Array.new(8,1000.000000)
min_cycle = Array.new(8,100.000000)
max_cycle = Array.new(8,0.000000)
frame_size = 500
frame_time = ((frame_size + 20) * 8).to_f / 1000000000
$short_cycle = Array.new(8,0)
$long_cycle = Array.new(8,0)
curr_pcp = 8    # 8 is not a valid PCP
distance_count = 0

Open3.popen2e("tcpdump -ttttt -en -r #{$pcap_file}") do |stdin, stdout, wait_thr|
    pid = wait_thr.pid # pid of the started process.
    stdin.close
    stdout.each_line do |line|
        if ($options[:frame_count] == :all)
            if /\d\d:\d\d:(\d\d\.\d+)\s/ =~ line
                last_time = $1.to_f # relative time from first line in seconds (floating)
                if (pre_tx_sec != 0)    # count the 'pre-tx' seconds - if any
                    count += 1
                    if (last_time > pre_tx_sec)
                        puts "Pre TX time has elapsed counted #{count} frames. Duration  #{last_time}"
                        count = 0
                        pre_tx_sec = 0
                        pre_tx_time = last_time
                    end
                else                # count the 'counting' seconds
                    count += 1
                    if (last_time > (pre_tx_time + count_sec))
                        puts "count_sec time has elapsed counted #{count} frames. Duration #{last_time - pre_tx_time} count_sec #{count_sec}"
                        break
                    end
                end
            end
        end
        if ($options[:frame_count] == :pcp)
            if /\d\d:\d\d:(\d\d\.\d+) .+ vlan \d+, p (\d+)/ =~ line
                pcp_value = $2 # The PCP value
                if ((pcp_idx = $options[:pcp_values].index(pcp_value.to_s)) != nil)   # Check if this PCP is an expected value
                    last_time = $1.to_f # Relative time from first line in seconds (floating)
                    if (pre_tx_sec != 0)    # Count the 'pre-tx' seconds - if any
                        count += 1
                        if (last_time > pre_tx_sec)
                            puts "Pre TX time has elapsed counted #{count} frames. Duration  #{last_time}"
                            pre_tx_sec = 0
                            pre_tx_time = last_time
                        end
                    else                # Count the 'count_sec' seconds
                        pcp_count[pcp_idx] += 1
                        if ($options[:exp_cycle] != nil)  # Check if TAS cycle time must be checked
                            if (old_last_time != 0) # Check for "large" frame distance
                                distance = last_time - old_last_time
                                if ((distance > (frame_time * 2)) && (distance < (frame_time * 50)))
                                    distance_count += 1
                                end
                            end
                            old_last_time = last_time

                            if ((curr_pcp != pcp_value) || (distance > (frame_time * 50)))  # This is a new PCP or "long" time since last received - new SAT interval. Cycle time for this PCP can possibly be calculated
                                if (rx_time[pcp_idx] != 1000.000000)    # A previous time for this PCP is valid - calculate the TAS cycle time
                                    cycle_time = last_time - rx_time[pcp_idx]  # Calculate cycle time
                                    if (cycle_time < (exp_cycle_f - max_diff)) # Count cycles too short
                                        $short_cycle[pcp_idx] += 1
                                        puts("short  pcp_idx #{pcp_idx}  last_time #{last_time}  cycle_time #{cycle_time}  diff #{exp_cycle_f - cycle_time}  max_diff #{max_diff}  percent #{((exp_cycle_f - cycle_time) / exp_cycle_f) * 100}")
                                    end
                                    if (cycle_time > (exp_cycle_f + max_diff)) # Count cycles too long
                                        $long_cycle[pcp_idx] += 1
                                        puts("long  pcp_idx #{pcp_idx}  last_time #{last_time}  cycle_time #{cycle_time}  diff #{cycle_time - exp_cycle_f}  max_diff #{max_diff}  percent #{((cycle_time - exp_cycle_f) / exp_cycle_f) * 100}")
                                    end
                                    max_cycle[pcp_idx] = (cycle_time > max_cycle[pcp_idx]) ? cycle_time : max_cycle[pcp_idx]
                                    min_cycle[pcp_idx] = (cycle_time < min_cycle[pcp_idx]) ? cycle_time : min_cycle[pcp_idx]
                                end
                                rx_time[pcp_idx] = last_time
                            end
                        end
                        if (last_time > (pre_tx_time + count_sec))
                            puts "count_sec time has elapsed counted #{pcp_count} frames. Duration #{last_time - pre_tx_time} count_sec #{count_sec}"
                            break
                        end
                        curr_pcp = pcp_value
                    end
                end
            end
        end
    end
#    exit_status = wait_thr.value # Process::Status object returned.
end

$pcap_saved = false
def save_pcap_file
    if (!$pcap_saved)
        copy_file_name = "#{$pcap_file}.#{Time.now.nsec}"
        puts"Saved #{$pcap_file} to #{copy_file_name}"
        system("date")
        system("cp #{$pcap_file} #{copy_file_name}")
    end
    $pcap_saved = true
end

if (last_time < (pre_tx_time + count_sec))
    if ($options[:frame_count] == :all)
        puts "count_sec time has NOT elapsed. counted #{count}. pre_tx_time #{pre_tx_time} last_time #{last_time} count_sec #{count_sec}"
    end
    if ($options[:frame_count] == :pcp)
        puts "count_sec time has NOT elapsed. counted #{pcp_count}. pre_tx_time #{pre_tx_time} last_time #{last_time} count_sec #{count_sec}"
    end
    save_pcap_file
end

if ($options[:frame_count] == :all)
    exp = $options[:exp_count][0].to_i
    tolerance = exp_tolerance[0].to_i
    off = 0.to_f
    off = (exp) ? (((count.to_f - exp) / exp) * 100).to_f : 99999
    if ((count > (exp + tolerance)) || (count < (exp - tolerance)))
        $stderr.puts "Analyze failed. Not expected number of frames counted.  off #{off}  Counted: #{count}  Expected: #{exp}  Tolerance: #{tolerance}"
        if ((exp != 0) && (count == 0))
            save_pcap_file
        end
        exit 7
    end

    puts "------Analyze succeeded.  off #{off}------"
    exit 0
end

if ($options[:frame_count] == :pcp)
    $options[:pcp_values].each_with_index do |pcp_value, pcp_idx|
        count = pcp_count[pcp_idx]
        exp = $options[:exp_count][pcp_idx].to_i
        tolerance = exp_tolerance[pcp_idx].to_i
        off = 0.to_f
        off = (exp != 0) ? (((count.to_f - exp) / exp) * 100) : 99999
        if ((count > (exp + tolerance)) || (count < (exp - tolerance)))
            $stderr.puts "Analyze failed. Not expected number of frames counted. pcp #{pcp_value}  off #{off}  Counted: #{count}  Expected: #{exp}  Tolerance: #{tolerance}"
            if ((exp != 0) && (count == 0))
                save_pcap_file
            end
            exit 7
        end
        puts "------Expected number of frames counted. pcp #{pcp_value}  off #{off}------"
    end

    if ($options[:exp_cycle] != nil)
        $options[:pcp_values].each_with_index do |pcp_value, pcp_idx|
            min = min_cycle[pcp_idx]
            max = max_cycle[pcp_idx]
            short = $short_cycle[pcp_idx]
            long = $long_cycle[pcp_idx]
            if ((short > 6) || (long > 8))
                $stderr.puts "Analyze failed.  Cycle time is not as expected. pcp #{pcp_value}  exp_cycle_f #{exp_cycle_f}"
                puts "min #{min}  max #{max}  min_lim #{exp_cycle_f - max_diff}  max_lim #{exp_cycle_f + max_diff}\n\
                      min_percent #{((exp_cycle_f - min) / exp_cycle_f) * 100}  max_percent #{((max - exp_cycle_f) / exp_cycle_f) * 100}"
                puts "short #{short}  long #{long}  distance_count #{distance_count}  frame_time #{frame_time}"
                puts "short_cycle #{$short_cycle}  long_cycle #{$long_cycle}"
                exit 7
            end
        end
        puts "------Expected cycle length measured. short_cycle #{$short_cycle}  long_cycle #{$long_cycle}------"
    end

    puts "------Analyze succeeded.------"
    exit 0
end
