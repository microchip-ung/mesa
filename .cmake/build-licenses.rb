#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'yaml'
require 'optparse'
require_relative './licenses_lib.rb'

$top = File.dirname(File.dirname(File.expand_path(__FILE__)))
Dir.chdir($top)

$yaml = YAML.load_file("#{$top}/.cmake/release.yaml")


def licenses(top, output_file = nil, prv_release = nil, cur_release = nil)
    api_licenses = CLicenseModuleInfo.new(top, "MESA")

    license_options = Hash.new()
    license_options[:release_version_prv] = prv_release
    license_options[:release_version_cur] = cur_release

    license_options[:hdr_pre]  = "This file provides a summary of the licenses included in or used by the MESA\n"
    license_options[:hdr_pre] += "sources, along with the raw licenses for each package.\n"
    license_options[:hdr_pre] += "\n"
    license_options[:hdr_pre] += "Notice: The MESA package includes pre-built binary firmware images. These\n"
    license_options[:hdr_pre] += "        images consist of the binary MESA artifacts appended to a BSP.\n"
    license_options[:hdr_pre] += "        The combined set of licenses for these images can be found in\n"
    license_options[:hdr_pre] += "        ./bin/<preset>/licenses.txt\n"
    license_options[:hdr_pre] += "\n"

    license_options[:hdr_post]  = "\n"
    license_options[:hdr_post] += "To obtain the source, please contact sales/marketing\n\n"
    license_options[:hdr_post] += "\n"

    licenses = CLicenseCollection.new("MESA", license_options)
    licenses.concat(api_licenses)
    if output_file
        File.open(output_file, "w") do |lic|
            licenses.write(lic)
        end
    else
        licenses.write()
    end
end

def licenses_bin(top, arch, output_file = nil, bsp = nil, tc = nil, cur_release = nil)
    license_options = Hash.new()
    license_options[:release_version_cur] = cur_release
    license_options[:bsp_version] = bsp[:ver] if bsp
    license_options[:toolchain_version] = tc[:ver] if tc

    i = 0;
    i += 1 if bsp
    i_bsp = i
    i += 1 if tc
    i_tc = i

    licenses = CLicenseCollection.new("MESA", license_options)
    licenses.concat(CLicenseModuleInfo.new(top, "MESA"))

    licenses.concat(CLicenseCsv.new([bsp[:path]], "BSP")) if bsp
    licenses.concat(CLicenseCsv.new([tc[:path]], "Toolchain")) if tc

    license_options[:hdr_pre]  = "This file provides a summary of the licenses included in the binary MESA\n"
    license_options[:hdr_pre] += "firmware images for #{arch}.\n"
    license_options[:hdr_pre] += "\n"

    license_options[:hdr_post]  = "All sources are embedded in the \"component\" package. Getting access to\n"
    license_options[:hdr_post] += "these sources depends on the component; see details below.\n"
    license_options[:hdr_post] += ""
    license_options[:hdr_post] += "How to obtain the sources:\n"
    license_options[:hdr_post] += "- MESA:      Contact sales/marketing and request the source code.\n"
    license_options[:hdr_post] += "- BSP:       Download the component from [#{i_bsp}], extract it, and find\n" if bsp
    license_options[:hdr_post] += "             the individual source packages in the \"dl\" folder.\n" if bsp
    license_options[:hdr_post] += "- Toolchain: Download the toolchain from [#{i_tc}].\n" if tc
    license_options[:hdr_post] += "\n"
    license_options[:hdr_post] += "The information presented in this file represents MSCC's understanding of the\n"
    license_options[:hdr_post] += "licenses. A license audit should extract the license information from the\n"
    license_options[:hdr_post] += "sources instead of solely relying on this information.\n\n"
    license_options[:hdr_post] += "[#{i_bsp}] http://mscc-ent-open-source.s3-website-eu-west-1.amazonaws.com/?prefix=public_root/bsp/\n" if bsp
    license_options[:hdr_post] += "[#{i_tc}] http://mscc-ent-open-source.s3-website-eu-west-1.amazonaws.com/?prefix=public_root/toolchain/\n" if tc
    license_options[:hdr_post] += "\n"

    if output_file
        File.open(output_file, "w") {|lic|
            licenses.write(lic)
        }
    else
        licenses.write()
    end
end

licenses("ws", "ws/LICENSE", $yaml['conf']['friendly_name_prv'], $yaml['conf']['friendly_name_cur'])
