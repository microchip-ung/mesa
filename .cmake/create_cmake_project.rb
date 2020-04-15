#!/usr/bin/env ruby
# Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
    puts "Usage: create_cmake_project <name> [output-folder]"
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


brsdk_name = "mscc-brsdk-#{name}-#{c[:brsdk]}"
brsdk_name += "-#{c[:brsdk_branch]}" if c[:brsdk_branch] != "brsdk"
brsdk_base = "/opt/mscc/#{brsdk_name}"

if not File.exist? brsdk_base
    if File.exist? "/usr/local/bin/mscc-install-pkg"
        run "sudo /usr/local/bin/mscc-install-pkg -t brsdk/#{c[:brsdk]}-#{c[:brsdk_branch]} #{brsdk_name};"
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
tc_base = "/opt/mscc/mscc-toolchain-bin-#{tc_conf["toolchain"]}"

if not File.exist? tc_base
    if File.exist? "/usr/local/bin/mscc-install-pkg"
        run "sudo /usr/local/bin/mscc-install-pkg -t toolchains/#{tc_folder} mscc-toolchain-bin-#{tc_conf["toolchain"]};"
    else
        puts "Please install the toolchain: #{brsdk_base}"
        puts ""
        puts "This may be done by using the following command:"
        puts "sudo sh -c \"mkdir -p /opt/mscc && wget -O- http://mscc-ent-open-source.s3-eu-west-1.amazonaws.com/public_root/toolchain/mscc-toolchain-bin-#{tc_conf["toolchain"]}.tar.gz | tar -xz -C /opt/mscc/\""
        exit 1
    end
end

run "mkdir -p #{out}"
Dir.chdir(out)

run "ln -s #{brsdk_base}/#{c[:cmake]} cmake"
a = Pathname.new($top)
b = Pathname.new(Dir.pwd)
src = a.relative_path_from b

run "./cmake -DCMAKE_TOOLCHAIN_FILE=#{brsdk_base}/#{c[:brsdk_toolchain]} #{c[:cmake_flags]} #{src}"

