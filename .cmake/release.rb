#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'optparse'

global = OptionParser.new do |opts|
  opts.banner = "Usage: #{$0} [options]"

  opts.on("-o NAME", "output name") do |n|
    $out_name = n
  end
end.order!

def run cmd
  system "#{$top}/.cmake/logcmd.rb --log #{$top}/build.log  -- \"#{cmd}\""
  raise "Running '#{cmd}' failed" if $? != 0
end

$top = File.dirname(File.dirname(File.expand_path(__FILE__)))
Dir.chdir($top)

%x{git diff-index --quiet HEAD}
if $?.to_i != 0
  puts "Uncomitted changes detected. Please commit everything before running this script"
  exit -1
end

%x{rm -rf ws ws.tar}
run ".cmake/source-prepare.rb ws"
run "./.cmake/create_cmake_project.rb -vfnp arm64 arm64"
run "./.cmake/create_cmake_project.rb -vfnp arm arm"
run "./.cmake/create_cmake_project.rb -vfnp mipsel mipsel"
run './.cmake/copyright.rb'
run './.cmake/build-licenses.rb'
run './.cmake/build-docs.rb'
if $out_name
  run ".cmake/aggr-artifacts.rb --no-upload -o #{$out_name}"
else
  run ".cmake/aggr-artifacts.rb --no-upload "
end

