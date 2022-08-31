#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'ox'
require 'pp'
require 'json'
require 'fileutils'
require 'optparse'

$cur_test = nil
$testruns = []
$env_prop_db = {}

def check_status s
    if not ["unknown", "broken", "failed", "skipped", "passed"].include? s
        raise "Invalid status #{s}"
    end
end

def combine_status cur, aggr
    check_status cur
    check_status aggr

    case cur
    when "unknown"
        return "unknown"

    when "broken"
        case aggr
        when "unknown"
            return "unknown"
        else
            return cur
        end

    when "failed"
        case aggr
        when "unknown"
            return "unknown"
        when "broken"
            return "broken"
        else
            return cur
        end

    when "skipped"
        case aggr
        when "unknown"
            return "unknown"
        when "broken"
            return "broken"
        when "failed"
            return "failed"
        else
            return cur
        end

    when "passed"
        return aggr
    end
end

class TestNode
    attr_accessor :kids
    attr_accessor :status
    attr_accessor :params
    attr_accessor :stop
    attr_accessor :name

    def initialize name, start
        @name = name
        @start = start
        @stop = nil
        @status = "passed"
        @kids = []
        @params = []
    end

    def status_update
        @kids.each do |e|
            @status = combine_status @status, e.status_update
        end

        return @status
    end

    def to_allure
        o = {
            "name": @name,
            "stage": "finished",
            "start": @start,
            "stop": @stop,
            "status": @status,
        }

        if @kids.size > 0
            o["steps"] = @kids.map{|x| x.to_allure}
        end

        if @params.size > 0
            o["parameters"] = params.map{|e| {"name": e[0], "value": e[1]}}
        end

        return o
    end
end

class TestRun
    attr_accessor :test_run_end
    attr_accessor :init_mode

    def initialize ts_start
        @steps_init = []
        @steps = []

        @cap_checks = []
        @labels = {}
        @test_run_end = nil
        @stack = []

        @init_mode = false

        @ts_start = ts_start
        @ts_end = nil

        @status = "passed"
        @param_buf = []
    end

    def label k, v
        @labels[k] = v
    end

    def uuid
        @labels["uuid"]
    end

    def param_ key, val
        if @stack.size == 0
            @param_buf << [key.to_s, val.to_s]
        else
            @stack[-1].params << [key.to_s, val.to_s]
        end
    end

    def param key, val
        val.to_s.each_line do |l|
            param_ key, l
        end
    end

    def stack_push e
        @stack << e

        @param_buf.each do |x|
            @stack[-1].params << x
        end

        @param_buf = []
    end

    def cap_start ts_start
        e = TestNode.new "capability", ts_start
        @cap_checks << e
        stack_push e
        return e
    end

    def cap_stop status, ts_stop
        sec_end status, ts_stop
    end

    def sec_start name, ts_start
        e = TestNode.new name, ts_start

        if @stack.size == 0 # Add to one of the root nodes
            if @init_mode
                @steps_init << e
            else
                @steps << e
            end
        else
            @stack[-1].kids << e
        end

        stack_push e
        return e
    end

    def sec_end status, ts_stop
        #puts "#{@stack[-1].name} -> #{status}"
        check_status status
        @stack[-1].status = status
        @stack[-1].stop = ts_stop
        @stack.pop
    end

    def testrun_end status, ts_end
        check_status status
        @status = status
        @ts_end = ts_end
    end

    def status_update
        cap_status = "passed"
        @cap_checks.each do |s|
            cap_status = combine_status cap_status, s.status_update
        end
        cap_status = "skipped" if cap_status == "failed"

        @status = combine_status @status, cap_status

        @steps_init.each do |s|
            @status = combine_status @status, s.status_update
        end

        @steps.each do |s|
            @status = combine_status @status, s.status_update
        end

        return @status
    end

    def json_container
        o = { }
        o["befores"] = []
        @steps_init.each do |x|
            o["befores"] << x.to_allure
        end

        @cap_checks.each do |x|
            o["befores"] << x.to_allure
        end

        o["children"] = [ @labels["uuid"] ]

        JSON.pretty_generate(o)
    end

    def json_results
        status_update()
        o = { }
        o["description"] = "no description"
        o["fullName"] = "no name"

        p = @labels["platform"]
        b = @labels["git_branch"]
        if (b != nil and b != "master")
            p += "@#{b}"
        end
        @labels["parentSuite"] = p
        @labels["suite"] = @labels["test_suite"]

        o["labels"] = (@labels.to_a.map{|e| {"name": e[0], "value": e[1]}})
        o["links"] = []
        o["name"] = @labels["filename"]

        o["parameters"] = [
            {"name": "platform", "value": p}
        ]
        o["stage"] = "finished"
        o["start"] = @ts_start
        o["stop"] = @ts_end
        o["status"] = @status
        #o["statusDetails"]
        o["uuid"] = @labels["uuid"]
        o["steps"] = @steps.map{|x| x.to_allure}

        JSON.pretty_generate(o)
    end
end

class Sample < ::Ox::Sax
    def initialize
        @indent_level = 0
        @init_flag = 0
        @test_flag = 1
        @run_flag = 0
        @check_capability = 0
        @stack = []
        @stack.push({ :name => :document, :attr => {} })
        @labels = {}
        @run_atrr = []
        @trace_atrr = []
        @ts_stamp = []
        @test_res_skp = 0

    end

    def start_element(name)
        @stack.push({ :name => name, :attr => {} })
    end

    def end_element(name)
        e = @stack.pop
        a = e[:attr]
        ts = 0;
        ts = (a[:ts].to_f*1000).to_i if a[:ts]

        case e[:name]
        when :console, :bg
            $cur_test.param "CON", e[:data]

        when :trace
            $cur_test.sec_start "T-#{a[:level]} #{e[:data]}", ts
            if a[:level] == "error"
                $cur_test.sec_end "failed", ts
            else
                $cur_test.sec_end "passed", ts
            end

        when :label
            $cur_test.label a[:name], e[:data]

            if ["git_sha", "git_sha_full", "git_id", "git_branch", "build_id"].include? a[:name]
                if $env_prop_db[a[:name]].nil?
                    $env_prop_db[a[:name]] = e[:data]
                else
                    raise "env not stable!" if $env_prop_db[a[:name]] != e[:data] and a[:name] != "git_branch"
                end
            end

        when :backtrace
            $cur_test.sec_start "Test script exception", ts
            $cur_test.param "backtrace", e[:data]
            $cur_test.sec_end "unknown", ts

        when :run_stdin, :try_stdin
            $cur_test.param "IN", e[:data]

        when :run_stdout, :try_stdout
            $cur_test.param "OUT", e[:data]

        when :run_stderr, :try_stderr
            $cur_test.param "ERR", e[:data]

        when :init
            $cur_test.init_mode = false

        when :check_capability

        end
    end

    def attr(name, value)
        @stack[-1][:attr][name] = value
    end

    def attrs_done()
        e = @stack[-1]
        a = e[:attr]
        ts = 0;
        ts = (a[:ts].to_f*1000).to_i if a[:ts]

        case e[:name]
        when :test_run
            $cur_test = TestRun.new ts
            $testruns << $cur_test

        when :test_run_end
            if a[:status] == "ok"
                $cur_test.testrun_end "passed", ts
            else
                $cur_test.testrun_end "failed", ts
            end

        when :assert
            $cur_test.sec_start "ASSERT: #{a[:msg]}", ts
            if a[:val] == "ok"
                $cur_test.sec_end "passed", ts
            else
                $cur_test.sec_end "failed", ts
            end

        when :test
            $cur_test.sec_start a[:name], ts

        when :test_end
            if a[:status] == "ok"
                $cur_test.sec_end "passed", ts
            else
                $cur_test.sec_end "failed", ts
            end

        when :tests

        when :init
            $cur_test.init_mode = true
            $cur_test.sec_start a[:name], ts

        when :"init-end"
            $cur_test.sec_end "passed", ts
            $cur_test.init_mode = false

        when :check_capability
            $cur_test.cap_start ts

        when :check_capability_end
            if a[:status] == "ok"
                $cur_test.cap_stop "passed", ts
            else
                $cur_test.cap_stop "skipped", ts
            end

        when :run, :try
            # TODO, make head-line easier to read

            where = ""
            case a[:on]
            when "pc-remote"
                where = "PC"
            else
                where = a[:on].upcase
            end

            if a[:cmd] =~ /mesa-cmd -i call (\w+)/
                n = "CALL #{$1}"
            else
                n = "#{where} #{a[:cmd]}"
            end

            $cur_test.sec_start n, ts
            $cur_test.param "CMD", a[:cmd]
            $cur_test.param "PID", a[:pid]

        when :run_end, :try_end
            $cur_test.param "RES", a[:exitstatus]
            if a[:exitstatus] == "0"
                $cur_test.sec_end "passed", ts
            else
                $cur_test.sec_end "failed", ts
            end

        end
    end

    def instruct(target)
    end

    def end_instruct(target)
    end

    def doctype(str)
    end

    def comment(str)
    end

    def cdata(str)
    end

    def value(str)
        @stack[-1][:data] = str.as_s
    end

    def error(message, line, column)
    end

    def abort(name)
    end
end


options = {}
OptionParser.new do |opts|
  opts.banner = "Usage: xml2allure.rb [options]"
  opts.on('-a', '--allure bin', 'allure binary path') { |v| options[:allure_bin] = v }
  opts.on('-l', '--logs path', 'json generation logs path') { |v| options[:json_logs] = v }
  opts.on('-o', '--output dir', 'report gen path') { |v| options[:reports_path] = v}
  opts.on('-url', '--url', 'report url path') { |v| options[:reports_url] = v}
  opts.on('-m', '--mulit runs', 'pass 1 for repeated runs or 0 for single run') { |v| options[:reports_multi] = v}
end.parse!

if options[:allure_bin] == nil || options[:json_logs] == nil || options[:reports_path] == nil || options[:reports_url] == nil
  puts "allurebin path is not passed please check Usage: xml2allure.rb --help" if options[:allure_bin] == nil 
  puts "allurelogs path is not passed please check Usage: xml2allure.rb --help " if options[:json_logs] == nil 
  puts "allure reports path is not passed please check Usage: xml2allure.rb --help" if options[:reports_path] == nil 
  puts "allure reports url path is not passed please check Usage: xml2allure.rb --help" if options[:reports_url] == nil
exit()
end


options[:json_logs] = options[:json_logs].chomp('/').to_s
options[:json_logs] = options[:json_logs] + '/'

options[:reports_path] = options[:reports_path].chomp('/').to_s
options[:reports_path] = options[:reports_path] + '/'

options[:reports_url] = options[:reports_url].chomp('/').to_s
options[:reports_url] = options[:reports_url] + '/'

foldername = Time.new.strftime("%Y-%m-%d::%H%M%S")

root_path = options[:json_logs]
logs_path = (options[:json_logs] + foldername).to_s
reports_path = (options[:reports_path] + foldername).to_s

allurecmd = "#{options[:allure_bin]} generate #{logs_path} -o #{reports_path}"

unless File.directory?(logs_path)
    FileUtils.mkdir_p(logs_path)
end


handler = Sample.new()
Ox.sax_parse(handler, STDIN, :skip => :skip_none)

his_folder = logs_path + "/history"
history_file = logs_path + "/history/history.json"
histrnd_file = logs_path + "/history/history-trend.json"
catgr_file = logs_path + "/categories.json"
exec_file = logs_path + "/executor.json"
env_file = logs_path + "/environment.properties"

executor = {
  "type" => "Jenkins",
  "url" => "http://example.org",
  "buildOrder" => $env_prop_db["build_id"].to_i,
  "buildName" => "4-dev# #{$env_prop_db["build_id"]}",
  "buildUrl" => "http://soft00.dk.vitesse.com:8080/view/API/job/API-mesa/job/4-dev/#{$env_prop_db["build_id"]}/",
  "reportUrl" =>  "#{options[:reports_url]}#{foldername}",
  "reportName" => "API-TEST report"
}

File.write("#{logs_path}/executor.json", executor.to_json)

open(env_file, 'w') { |f|
    $env_prop_db.each do |key,value|
       f.puts "#{key}=#{value}"
    end
}

$testruns.each do |t|
    next if t.uuid.nil?
    File.write("#{logs_path}/#{t.uuid}-container.json", t.json_container)
    File.write("#{logs_path}/#{t.uuid}-result.json", t.json_results)
end

puts "Calling #{allurecmd}"
system(allurecmd) #generating the allure Final report

puts ">>Report Link => \e[42m #{options[:reports_url]}#{foldername} \e[0m"

