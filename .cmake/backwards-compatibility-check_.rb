#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'json'
require 'open3'
require 'logger'
require 'optparse'
require 'fileutils'

global = OptionParser.new do |opts|
  opts.banner = "Usage: #{$0}"
  opts.on("-w", "--workspace path", "(Mandotory) Where to do the build (must not exists)") do |x|
      $ws = x
  end

  opts.on("-a", "--api-build file", "(Mandotory) API build to use") do |x|
      $api = x
  end

  opts.on("-b", "--appl appl", "(Mandotory) Application to check backwards compatibility against") do |x|
      $appl = x
  end

  opts.on("-c", "--configs configs", "(Mandotory) Comma seperated list of configurations to build") do |x|
      $configs = x
  end

  opts.on("-o", "--out-folder path", "Copy artifacts to this folder") do |x|
      $out_folder = x
  end

end.order!

if $ws.nil? or $api.nil? or $appl.nil?
    puts "Mandotory options missing!"
    exit 1
end

if File.exist? $ws
    puts "Work-space exists already, please provide a non-existing works space path"
    exit 1
end

$top = File.dirname(File.dirname(File.expand_path(__FILE__)))
$ws = File.expand_path($ws)
$api = File.expand_path($api)
if $out_folder
    $out_folder = File.expand_path($out_folder)
end

%x{mkdir -p #{$ws}}
Dir.chdir($ws)

$l = Logger.new(IO.popen(["tee", "#{$ws}/build.log"], "wb"))
$l.level = Logger::INFO
log_fmt = proc do |severity, datetime, progname, msg|
    "#{severity} [#{Time.now.strftime('%H:%M:%S')}]: #{msg}\n"
end
$l.formatter = log_fmt

def run(cmd, msg = "")
    msg = "Running: " if msg.size == 0
    msg = "#{msg}: " if msg.size > 0
    $l.info "#{msg} '#{cmd}' ..."
    o, e, s = Open3.capture3(cmd)
    if $? != 0 or e.size > 0
        raise "Command '#{cmd}' failed with return code: '#{s.to_i}' err: '#{e.chomp}', out: '#{o.chomp}'"
    end
    return o.chomp
end

def run3(cmd, msg = "")
    msg = "Running: " if msg.size == 0
    msg = "#{msg}: " if msg.size > 0
    $l.info "#{msg} '#{cmd}' ..."
    o, e, s = Open3.capture3(cmd)
    res = {:out => o, :err => e, :status => s.to_i}
    return res
end

$l.info run "hostname"
$l.info run "whoami"
run "sudo #{$top}/.cmake/mscc-download-pkg -t webstax2 #{$appl}"
run "tar -xzf /opt/mscc/webstax2/#{$appl}  --strip-components=2"
run "rm -rf vtss_api"
run "mkdir vtss_api"
run "tar -xzf #{$api} --strip-components=2 -C vtss_api"

c = "cd build/tools/chk_scripts/; "
c += "./code_static_chks.rb "
c += "--src-dir #{$ws} "
c += "--json-status #{$ws}/status.json "
c += "--verbose info "
c += "--cfg #{$configs} "
c += "--compile-only "

res = run3(c)
$l.info "STDOUT:"
$l.info res[:out]
$l.info "STDERR:"
$l.info res[:err]

if res[:status] != 0
    $l.info "Compatibility check of #{$api} against #{$appl} failed!"
    err = Dir.glob "**/compile_stderr.txt"
    err.each do |e|
        if File.stat(e).size > 0
            $l.info "Compile errors in #{e}:"
            $l.info "\n#{IO.binread(e)}\n"
        end
    end
end

if $out_folder
    run "mkdir -p #{$out_folder}"
    run "cp -r build/obj/results/* #{$out_folder}/."
    run "cp status.json #{$out_folder}/."
end

exit res[:status]

