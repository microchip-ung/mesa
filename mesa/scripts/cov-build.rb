#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'logger'
require 'pp'
require 'csv'

project = "Mesa"
$covopts = "--config /opt/coverity/credentials.xml --auth-key-file /opt/coverity/reporter.key"
$version = %x(git rev-parse HEAD).chop

$l = Logger.new(STDERR)
$l.level = Logger::DEBUG
$arch = "mipsel"

def run_cmd(cmd, exit_on_err = false)
  $l.info "Running '#{cmd}' ..."
  system(cmd)
  if $? != 0
    $l.fatal "Running '#{cmd}' failed"
    exit 1 if exit_on_err == true
  end
end

def get_cfgs
  cfgs = []
  IO.popen("make help").each do |line|
    if line.match(/^\.\.\. (vsc\w+)/)
      cfg = $1
      if not cfg.match(/_static$/)
        cfgs <<= cfg
      end
    end
  end
  return cfgs
end

def get_streams(project)
  streams = []
  IO.popen("cov-manage-im --mode streams --show #{$covopts} --project #{project}").each do |line|
    data = line.chop.parse_csv
    if data[0] != "Stream"
      stream = data[0]
      $l.info "Have stream #{stream}"
      streams <<= stream
    end
  end
  return streams
end

def add_streams(project, streams)
  streams.each do |stream|
    $l.warn("Add %s to %s" % [stream, project])
    run_cmd("cov-manage-im #{$covopts} --mode streams --add --set name:#{stream} --set lang:cpp --set component-map:Mesa --set ownerAssignmentOption:scm --set expiration:enabled --set triage:Mesa --set \"desc:#{stream}\"")
    run_cmd("cov-manage-im #{$covopts} --mode projects --update --name #{project} --insert stream:#{stream}")
  end
end

def compile(cfg)
  $l.info "Compile #{cfg}"
  cov = "obj-#{cfg}"
  scanopts = "-V 3 -j auto"
  strip = File.expand_path("..")
  cwd = File.basename(Dir.getwd)
  run_cmd("rm -fr #{cov} CMakeFiles")
  run_cmd("./cmake .. -D#{cfg}=ON")
  run_cmd("make clean")
  run_cmd("cov-build --return-emit-failures --parse-error-threshold 50 --dir #{cov} make -j -l 10")
  run_cmd("cov-analyze #{scanopts} --dir #{cov} --strip-path #{strip}/")
  run_cmd("cov-commit-defects #{$covopts} --dir #{cov} --description 'Build of #{cfg} arch #{$arch}' --version #{$version} --stream #{$arch}-#{cfg}")
  run_cmd("./cmake .. -D#{cfg}=OFF")
end

cfgs = get_cfgs()
cfgs <<= "BUILD_MESA_DEMO"
streams = get_streams(project)
need_streams = cfgs.map { |cfg| "#{$arch}-#{cfg}" }

diff = need_streams - streams
add_streams(project, diff)

run_cmd("./cmake .. " + cfgs.map { |cfg| "-D#{cfg}=OFF"}.join(" "))
run_cmd("rm -fr *.so include_* mesa-ag")

#cfgs = [ "BUILD_MESA_DEMO", "vsc7514", "vsc7464" ]
cfgs.each do |cfg|
  compile(cfg)
end
