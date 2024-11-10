#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'open3'
require 'yaml'
require 'optparse'

def run cmd
  if $verbose
    STDOUT.print "RUN: #{cmd}"
    STDOUT.flush
  end

  a = Time.now
  o, e, s = Open3.capture3(cmd)
  b = Time.now

  if $verbose
    STDOUT.print " -> #{s} in %1.3fs\n" % [b - a]
    STDOUT.flush
  end

  if s.to_i != 0 or e.size > 0
    raise "CMD: #{cmd} status: #{s.to_i}, std-err: #{e}"
  end

  return o, e, s
end

$top = File.dirname(File.dirname(File.expand_path(__FILE__)))
Dir.chdir($top)

$opt = { }
global = OptionParser.new do |opts|
  opts.banner = "Usage: #{$0} [options] output-folder"

  opts.on("-v", "--verbose", "Enable verbose printing") do
    $verbose = true
  end
end.order!

if ARGV.size != 1
  raise "No output folder"
end
$ws = ARGV[0]

git_sha = %x(git rev-parse --short HEAD).chop
git_sha_long = %x(git rev-parse HEAD).chop
begin
    git_id = %x(git describe --tags --long).chop
rescue
    git_id = git_sha
end
if ENV['BRANCH_NAME']
    git_branch = ENV['BRANCH_NAME']
else
    git_branch = %x(git symbolic-ref --short -q HEAD).chop
end
out_name = "mesa-#{git_id}@#{git_branch}"

## TODO, check to see if clean

if File.exist?($ws) or File.exist?("#{$ws}.tar")
  raise "Workspace exists already"
end

run "mkdir -p #{$ws}"
run "git archive --format=tar HEAD | tar -C #{$ws} -x"
File.open("#{$ws}/.mscc-version", 'w') do |version|
    version.puts(%Q(mesa_sha="#{git_sha}"))
    version.puts(%Q(mesa_id="#{git_id}"))
    version.puts(%Q(mesa_branch="#{git_branch}"))
end

run "rm -rf #{$ws}/.cmake/release*"
run "rm -rf #{$ws}/.cmake/licenses.rb"
run "rm -rf #{$ws}/.cmake/backwards*"
run "rm -rf #{$ws}/.cmake/copyright*"
run "rm -rf #{$ws}/mesa/demo/test"
run "rm -rf #{$ws}/Jenkinsfile"
run "rm -rf #{$ws}/Jenkinsfile_UNGE"
run "tar --format=posix --numeric-owner --owner=0 --group=0 --mtime=@0 -c -f #{$ws}.tar -C #{$ws} ."
