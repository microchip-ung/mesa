#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'yaml'
require 'open3'

$verbose = true
$top = File.dirname(File.dirname(File.expand_path(__FILE__)))
Dir.chdir($top)

$yaml = YAML.load_file("#{$top}/.cmake/release.yaml")

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

run "./mesa/docs/scripts/capdump.rb -o mesa/docs/capdb.yaml -c mesa/include/microchip/ethernet/switch/api/capability.h -C #{$ws}/bin/x86/capability_dumper #{$ws}/bin/x86/libvsc*.so"
# TODO, check if equal to the one checked into git
run "cp mesa/docs/capdb.yaml ws/mesa/docs/capdb.yaml" if File.exist? "./ws"
run "cp mesa/docs/capdb.yaml images/." if File.exist? "./images"

git_sha = %x(git rev-parse --short HEAD).chop
rev = $yaml['conf']['friendly_name_cur']
if /MESA-(.*)/ =~ rev
  rev = $1
end

#MESA-Doc
run "cd mesa/docs/scripts; ./dg.rb -r #{rev} -s #{git_sha}"
run "cp ./mesa-doc.html images/." if File.exist? "./images"
run "cp ./mesa-doc.html ws/." if File.exist? "./ws"
