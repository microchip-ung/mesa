#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'yaml'
require 'json'
require 'open3'
require 'pathname'
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

def cd path
  puts "cd #{path}  (was: #{Dir.pwd})" if $verbose
  Dir.chdir(path)
end

def sys cmd
  if $verbose
    puts "Running: #{cmd}"
  end

  a = Time.now
  system cmd
  b = Time.now

  if $verbose
    STDOUT.print " -> #{$?} in %1.3fs\n" % [b - a]
    STDOUT.flush
  end

  if $?.to_i != 0
    raise "CMD: #{cmd} status: #{$?.to_i}"
  end
end

def is_internal?
  if not $internal.nil?
    return $internal
  end

  if $opt[:run_external] and $opt[:run_internal]
    puts "-e and -i are mutual exclusive"
    raise
  elsif $opt[:run_external]
    $internal = false
  elsif $opt[:run_internal]
    $internal = true
  else
    run "ping -q -c 1 -W 0.5 artifacts.microchip.com"
    if $?.to_i == 0
      $internal = true
    else
      $internal = false
    end
  end

  return $internal
end

def clean_files path, files_to_keep, indent = ""
  #puts "> #{path}"
  path.each_child do |new_path|
    ext = new_path.extname
    base = new_path.basename(ext).to_s

    #puts "Path: #{new_path}" if base == "libnetsnmpmibs"
    if new_path.directory? and not new_path.symlink?
      #puts "DIR: #{new_path}" if base == "libnetsnmpmibs"
      clean_files new_path, files_to_keep, indent + "  "
    else
      #puts "NOT DIR: #{new_path}" if base == "libnetsnmpmibs"

      delete_it = true
      files_to_keep.each do |pattern|
        if File.fnmatch pattern, "./#{new_path.to_s}", File::FNM_PATHNAME | File::FNM_EXTGLOB
          #puts "matching pattern: #{pattern}" if base == "libnetsnmpmibs"
          delete_it = false
          break
        end
      end

      if delete_it
        #puts "deleting: #{new_path}" if base == "libnetsnmpmibs"
        File.delete new_path.to_s
      end
    end
  end
end

def clean_folders path, indent = ""
  #puts "> #{path}"
  path.each_child do |new_path|
    ext = new_path.extname
    base = new_path.basename(ext).to_s

    if new_path.directory? and not new_path.symlink?
      if clean_folders(new_path, indent + "  ")
        Dir.rmdir(new_path.to_s)
      end
    end
  end

  return Dir.children(path.to_s).size == 0
end

def clean path, files_to_keep
  clean_files path, files_to_keep
  clean_folders path
end


$top = File.dirname(File.dirname(File.expand_path(__FILE__)))
cd $top

$opt = { }
global = OptionParser.new do |opts|
  opts.banner = "Usage: #{$0} [options] <PRESET> [<OUTPUT-FOLDER>]"

  opts.on("-a", "--all", "Set the build all flag") do
    $opt[:all] = true
  end

  opts.on("-b", "--build", "Build after configuring") do
    $opt[:build] = true
    $opt[:all] = true
  end

  opts.on("-p", "--pack NAME", "Wrap up the binaries in a TAR archive") do |name|
    $opt[:pack] = name
    $opt[:build] = true
    $opt[:all] = true
  end

  opts.on("--external", "Assumed running out-side Microchip network (default is auto-detect)") do
    $opt[:run_external] = true
  end

  opts.on("-f", "--force", "Delete the output folder if it exist already") do
    $opt[:force] = true
  end

  opts.on("-i", "--incremental", "Do not clean before building") do
    $opt[:incremental] = true
  end

  opts.on("--interanl", "Assumed running in-side Microchip network (default is auto-detect)") do
    $opt[:run_internal] = true
  end

  opts.on("-n", "--ninja", "Use ninja generator") do
    $opt[:ninja] = true
  end

  opts.on("-v", "--verbose", "Enable verbose printing") do
    $verbose = true
  end

end.order!


$cmake_presents = YAML.load_file("#{$top}/.cmake/cmake-presets.yaml")
$bsp_deps = JSON.load_file("#{$top}/.cmake/deps-bsp.json").filter{|x| x["id"] == "bsp"}
raise "Exepcted to find one and only one BSP record in .cmake/deps-bsp.json" if $bsp_deps.size != 1
$bsp_deps = $bsp_deps.first

if ARGV.size < 1
  puts "Usage: create_cmake_project <preset name> [output-folder]"
  puts ""
  puts "Valid presets:"
  $cmake_presents["presets"].each do |k, v|
    puts "    #{k}"
  end

  exit -1
end

name = ARGV[0]
out = "build-#{name}"
out = ARGV[1] if ARGV.size > 1

if File.exist? out and not $opt[:incremental]
  if $opt[:force]
    run "rm -rf #{out}"
  else
    puts "Folder: #{out} exist already!"
    exit 1
  end
end

c = $cmake_presents["presets"][name]
if c.nil?
  puts "Not found: \"#{name}\""
  puts "Valid options:"
  $cmake_presents["presets"].each do |k, v|
    puts "    #{k}"
  end
end

base = nil

# Not all presets uses a brsdk, some only uses the toolchain
if c[:brsdk_arch]
  brsdk_name = "mchp-brsdk-#{c[:arch]}-#{$bsp_deps["build-artifact-version-string"]}"
  brsdk_base = "/opt/mchp/#{brsdk_name}"
  base = brsdk_base
  puts brsdk_name

  if not File.exist? brsdk_base
    if is_internal?
      sys "wget --quiet -O- #{$bsp_deps["build-artifact-url"]}/#{brsdk_name}.tar.gz | tar -xz -C /opt/mchp/"
    else
      puts "Please install the BSP: #{brsdk_base}"
      puts ""
      puts "This may be done by using the following command:"
      puts "sudo sh -c \"mkdir -p /opt/mchp && wget -O- http://mscc-ent-open-source.s3-eu-west-1.amazonaws.com/public_root/bsp/#{brsdk_name}.tar.gz | tar -xz -C /opt/mchp/\""
      exit 1
    end
  end

  $tc = JSON.load_file("#{brsdk_base}/.deps.json").find{|x| x["id"] == "toolchain"}
  $tc_name = "mchp-toolchain-bin-#{$tc["build-artifact-version-string"]}"
  $tc_path = "/opt/mchp/#{$tc_name}"

else
  raise "not supported"
end

if not File.exist? $tc_path
  if is_internal?
    tc_link = "#{$tc["build-artifact-url"]}/#{$tc_name}.tar.gz"
    sys "wget --quiet -O- #{tc_link} | tar -xz -C /opt/mchp/"
  else
    raise "not implemented!"
    puts "Please install the toolchain: #{$tc_name} into /opt/mchp/"
    puts ""
    puts "This may be done by using the following command:"
    puts "sudo sh -c \"mkdir -p /opt/mchp && wget -O- http://mscc-ent-open-source.s3-eu-west-1.amazonaws.com/public_root/toolchain/#{$tc_name}.tar.gz | tar -xz -C /opt/mchp/\""
    exit 1
  end
end

if not File.exist? out
  run "mkdir -p #{out}"
end
cd out

cmake = "cmake"
if c[:cmake]
  if not File.exist? cmake
    run "ln -s #{base}/#{c[:cmake]} cmake"
  end
  cmake = "./cmake"
end
a = Pathname.new($top)
b = Pathname.new(Dir.pwd)
src = a.relative_path_from b

cmd = [cmake]
cmd << "-DCMAKE_TOOLCHAIN_FILE=#{base}/#{c[:toolchainfile]}"
cmd << "-DBUILD_ALL=on" if $opt[:all]
cmd << "-G Ninja" if $opt[:ninja]
cmd << c[:cmake_flags] if c[:cmake_flags]
cmd << src

if not File.exist? "CMakeCache.txt"
  sys cmd.join " "
end

if $opt[:build]
  if $opt[:ninja]
    sys "ninja"
  else
    cpu_cnt, e, s = run("cat /proc/cpuinfo | grep processor | wc -l")
    sys "make -j#{cpu_cnt.strip}"
  end

  if $opt[:pack] and c[:package_list]
    cd $top
    run "rm -rf tmp-ws-packing"
    run "mkdir tmp-ws-packing"
    run "cp -r #{out} tmp-ws-packing/#{$opt[:pack]}"
    cd "tmp-ws-packing/#{$opt[:pack]}"
    clean(Pathname.new("."), c[:package_list])
    cd $top

    run "tar --format=posix --numeric-owner --owner=0 --group=0 --mtime=@0 -c -f #{$opt[:pack]}.tar -C tmp-ws-packing #{$opt[:pack]}"
    run "rm -rf tmp-ws-packing"
  end
end

