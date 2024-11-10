#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'yaml'
require 'pathname'

$top = File.dirname(File.dirname(File.expand_path(__FILE__)))
Dir.chdir($top)

$yaml = YAML.load_file("#{$top}/.cmake/cmake-presets.yaml")

def run(cmd)
    puts cmd
    system cmd
    raise "Running '#{cmd}' failed" if $? != 0
end

if ARGV.size < 1
    puts "Usage: create_cmake_project <preset name> [output-folder]"
    puts ""
    puts "Valid presets:"
    $yaml["presets"].each do |k, v|
        puts "    #{k}"
    end

    exit -1
end

name = ARGV[0]
out = "build-#{name}"
out = ARGV[1] if ARGV.size > 1

if File.exist? out
    puts "Folder: #{out} exists already!"
    exit 1
end

c = $yaml["presets"][name]
if c.nil?
    puts "Not found: \"#{name}\""
    puts "Valid options:"
    $yaml["presets"].each do |k, v|
        puts "    #{k}"
    end
end

base = nil
tc = nil
tc_conf = {}
tc_folder = nil
tc_folder = nil
tc_base = nil

# Not all presets uses a brsdk, some only uses the toolchain
if c[:brsdk]
    brsdk_name = "mscc-brsdk-#{c[:arch]}-#{c[:brsdk]}"
    brsdk_name += "-#{c[:brsdk_branch]}" if c[:brsdk_branch] and c[:brsdk_branch] != "brsdk"
    brsdk_base = "/opt/mscc/#{brsdk_name}"
    base = brsdk_base

    if not File.exist? brsdk_base
        if File.exist? "/usr/local/bin/mscc-install-pkg"
            if c[:brsdk_branch]
                run "sudo /usr/local/bin/mscc-install-pkg -t brsdk/#{c[:brsdk]}-#{c[:brsdk_branch]} #{brsdk_name};"
            else
                run "sudo /usr/local/bin/mscc-install-pkg -t brsdk/#{c[:brsdk]} #{brsdk_name};"
            end
        else
            puts "Please install the BSP: #{brsdk_base}"
            puts ""
            puts "This may be done by using the following command:"
            puts "sudo sh -c \"mkdir -p /opt/mscc && wget -O- http://mscc-ent-open-source.s3-eu-west-1.amazonaws.com/public_root/bsp/#{brsdk_name}.tar.gz | tar -xz -C /opt/mscc/\""
            exit 1
        end
    end

    tc_conf = YAML.load_file("#{brsdk_base}/.mscc-version")
    tc_folder = tc_conf["toolchain"]
    tc_folder = "#{tc_conf["toolchain"]}-toolchain" if not tc_conf["toolchain"].include? "toolchain"

else
    tc_conf["toolchain"] = c[:toolchain]
    tc_folder = "#{tc_conf["toolchain"]}-toolchain"
    base = "/opt/mscc/mscc-toolchain-bin-#{tc_conf["toolchain"]}"

end

tc_name = "mscc-toolchain-bin-#{tc_conf["toolchain"]}"
tc_base = "/opt/mscc/mscc-toolchain-bin-#{tc_conf["toolchain"]}"

if not File.exist? tc_base
    if File.exist? "/usr/local/bin/mscc-install-pkg"
        run "sudo /usr/local/bin/mscc-install-pkg -t toolchains/#{tc_folder} #{tc_name};"
    else
        puts "Please install the toolchain: #{tc_name} into /opt/mscc/"
        puts ""
        puts "This may be done by using the following command:"
        puts "sudo sh -c \"mkdir -p /opt/mscc && wget -O- http://mscc-ent-open-source.s3-eu-west-1.amazonaws.com/public_root/toolchain/#{tc_name}.tar.gz | tar -xz -C /opt/mscc/\""
        exit 1
    end
end

run "mkdir -p #{out}"
Dir.chdir(out)

cmake = "cmake"
if c[:cmake]
    run "ln -s #{base}/#{c[:cmake]} cmake"
    cmake = "./cmake"
end
a = Pathname.new($top)
b = Pathname.new(Dir.pwd)
src = a.relative_path_from b

run "#{cmake} -DCMAKE_TOOLCHAIN_FILE=#{base}/#{c[:toolchainfile]} #{c[:cmake_flags]} #{src}"
