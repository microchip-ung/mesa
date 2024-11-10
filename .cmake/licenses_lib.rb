#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'yaml'
require 'find'
require 'csv'

class CLicenseCollection
    KEY_COMPONENT      = :component

    KEY_LICENSE_TYPES_STR = :license_types_str # Comma-separated string (e.g. "GPL-2.0, libiniparser MIT")
    KEY_LICENSE_TYPES     = :license_types     # Array of license types (e.g. ["GPL-2.0",        "libiniparser MIT"]
    KEY_LICENSES          = :licenses          # Array of license texts (e.g. ["GNU GENERAL...", "Copyright (s) 2000-20007..."]
    KEY_SOURCE_FILE       = :file              # Path to source files under a particular license or array of source files under a particular license
    KEY_NAME              = :name
    KEY_VERSION           = :version
    KEY_SOURCE            = :source
    KEY_PATH              = :path              # Where did this entry come from (path to e.g. .module_info or manifest.csv).
    KEY_PRINTED           = :printed           # Helper key to indicate whether a particular license is printed

    # Various keys for producing a diff
    KEY_VISITED                = :visited
    KEY_VERSION_PRV            = :version_prv
    KEY_VERSION_CUR            = :version_cur
    KEY_LICENSE_TYPES_STR_PRV  = :license_types_prv
    KEY_LICENSE_TYPES_STR_CUR  = :license_types_cur

    attr_reader :license_info

    # flavor:
    #   Can be anything, but if it's the API, it must be called "Mesa".
    #   For the application, it's normally something like "WebStaX", "SMBStaX",
    #   etc.
    #
    # The options argument is optional, and all its values are as well.
    #   :release_version_prv
    #      Friendly name of previous release, e.g. "4.7.0"
    #   :release_version_cur
    #      Friendly name of current release, e.g. "4.8.0"
    #   :bsp_version
    #      Version of BSP, e.g. "2018-05-162"
    #   :redboot_version
    #      Version of RedBoot, e.g. "668849a"
    #   :toolchain_version
    #      Version of toolchain, e.g. "2018.05-057"
    #   :no_header
    #      Start the license file with the "License summary" part, that is, do
    #      not write a header. Useful for license.txt embedded with the
    #      application.
    def initialize(flavor, options = nil)
        if options.nil?
            @options = Hash.new()
        else
            @options = options
        end

        @options[:no_header] = false unless @options[:no_header]

        @flavor            = flavor
        @license_info      = Array.new()
        @license_info_prev = Array.new()

        # Each value of the following hash is an array of strings, because the
        # contents have evolved over time. The one we use when we generate a
        # heading is the first entry of the array (index 0).
        # The remaining entries are used only when we attempt to parse a
        # previous license.
        # New headings were introduced with 2022.03.
        @headings = {
            KEY_COMPONENT             => ["Component"],
            KEY_SOURCE_FILE           => ["Path/File"],
            KEY_LICENSE_TYPES_STR     => ["License Types", "License Type"],
            KEY_NAME                  => ["Name"],
            KEY_VERSION               => ["Version"],
            KEY_SOURCE                => ["Source"],
            KEY_LICENSES              => ["Licenses", "License"],
            KEY_PATH                  => ["Input File"], # E.g. .module_info or manifest.csv
            KEY_VERSION_PRV           => ["Previous Version"],
            KEY_VERSION_CUR           => ["Current Version"],
            KEY_LICENSE_TYPES_STR_PRV => ["Previous License Types", "Previous License Type"],
            KEY_LICENSE_TYPES_STR_CUR => ["Current License Types", "Current License Type"]
        }

        # Controls which order the components (categories) are printed.
        # If a component is not in this list, it will be printed last.
        @component_print_order = [
            "Appl",
            "IStaX38x",
            "IStaX",
            "SMBStaX",
            "WebStaX",
            "MESA",
            "MESA-API",
            "BSP",
            "FRR",
            "Toolchain",
            "RedBoot",
            "Host Tools"
        ]
    end

    def error(str)
        raise("Error: #{str}")
    end

    def max_lengths_get(info)
        max = Hash.new()

        @headings.each {|k, v|
            max[k] = v[0].length()
        }

        info.each {|m|
            m.each {|k, v|
                next if k == KEY_VISITED
                next if max[k].nil? # Not interested in this key as a heading

                l = 0
                if v.kind_of?(Array)
                    # KEY_LICENSES and KEY_LICENSE_TYPES are arrays.
                    # Make a comma-separated string out of this array, but
                    # remove duplicates first
                    a = v.dup()
                    a.uniq!()
                    s = a.join(", ")
                    l = s.length()
                else
                    l = v.length()
                end

                max[k] = l if max[k] < l
            }
        }

        return max
    end
    private :max_lengths_get

    def header_get(fields, max)
        line = ""
        sep  = ""
        cnt = 0

        fields.each {|f|
            line += " " if line != ""
            line += sprintf("%-#{max[f]}s", @headings[f][0])

            sep  += " " if sep != ""
            sep  += "-" * max[f]

            cnt += 1
        }

        return line.strip() + "\n" + sep.strip() + "\n"
    end
    private :header_get

    def line_get(m, fields, max)
        line = ""
        fields.each {|f|
            line += " " if line != ""
            s = m[f]
            line += sprintf("%-#{max[f]}s", s)
        }

        return line.strip() + "\n"
    end
    private :line_get

    def appl_header(f, fields)
        f.write("License information\n")
        f.write("===================\n\n")
        f.write("This file provides a summary of the licenses of all software packages included\n")
        f.write("in or used by the #{@flavor} package, along with the raw licenses for\n")
        f.write("each package.\n\n")
        f.write("Summary table legend:\n")
        f.write("- Component:     Identifies the MSCC component in which the given software\n")         if fields.include?(KEY_COMPONENT)
        f.write("                 package is embedded.\n")                                              if fields.include?(KEY_COMPONENT)
        f.write("- Path/File:     Identifies the software package's location inside the MSCC\n")        if fields.include?(KEY_SOURCE_FILE)
        f.write("                 component. This is only valid for the #{@flavor} component.\n")       if fields.include?(KEY_SOURCE_FILE)
        f.write("- Name:          Name of the software package.\n")                                     if fields.include?(KEY_NAME)
        f.write("- Version:       Version of the software package.\n")                                  if fields.include?(KEY_VERSION)
        f.write("                 NOTE: Patches may have been applied on top of this version. See\n")   if fields.include?(KEY_VERSION)
        f.write("                 the source package to get further information about patches.\n")      if fields.include?(KEY_VERSION)
        f.write("- License Types: Types of license. This field is provided as a \"hint\" and should\n") if fields.include?(KEY_LICENSE_TYPES_STR)
        f.write("                 not be used in a license audit.\n")                                   if fields.include?(KEY_LICENSE_TYPES_STR)
        f.write("- Source:        This is the location from which MSCC has originally downloaded\n")    if fields.include?(KEY_SOURCE)
        f.write("                 the source of this software package.\n")                              if fields.include?(KEY_SOURCE)
        f.write("                 NOTE: This link may or may not not be valid anymore.\n\n")            if fields.include?(KEY_SOURCE)
        f.write("All sources are embedded in the \"component\" package. Getting access to these\n")
        f.write("sources depends on the component; see details below.\n\n")

        # Alignment
        width = @flavor.length() + 1
        if @options[:toolchain_version].nil?
            width = "RedBoot:".length() if "RedBoot:".length() > width
        else
            width = "Toolchain:".length() if "Toolchain:".length() > width
        end

        flv = sprintf("%-#{width}s", "#{@flavor}:")
        bsp = sprintf("%-#{width}s", "BSP:")
        bsd = sprintf("%-#{width}s", "BSP-Doc:")
        tch = sprintf("%-#{width}s", "Toolchain:") unless @options[:toolchain_version].nil?
        rdb = sprintf("%-#{width}s", "RedBoot:")
        emt = sprintf("%-#{width}s", "")

        f.write("How to obtain the sources:\n")
        f.write("- #{flv} Contact sales/marketing and request the application source code.\n")
        f.write("- #{bsp} Download the component from [1], extract it, and find\n")
        f.write("  #{emt} the individual source packages in the \"dl\" folder.\n")
        f.write("- #{bsd} Visit [2] to see the BSP documentation for this release.\n")
        f.write("- #{rdb} Download the source from [3].\n")
        f.write("- #{tch} Download the toolchain from [4].\n") unless @options[:toolchain_version].nil?
        f.write("\n")
        f.write("The information presented in this file represents MSCC's understanding of the\n")
        f.write("licenses. A license audit should extract the license information from the\n")
        f.write("sources instead of solely relying on this information.\n\n")
        f.write("[1] http://mscc-ent-open-source.s3-website-eu-west-1.amazonaws.com/?prefix=public_root/bsp/\n")
        f.write("[2] https://microchip-ung.github.io/bsp-doc/\n")
        f.write("[3] http://mscc-ent-open-source.s3-website-eu-west-1.amazonaws.com/?prefix=public_root/redboot/\n")
        f.write("[4] http://mscc-ent-open-source.s3-website-eu-west-1.amazonaws.com/?prefix=public_root/toolchain/\n") unless @options[:toolchain_version].nil?
        f.write("\n")
    end
    private :appl_header

    def api_header(f, fields)
        f.write("License information\n")
        f.write("===================\n\n")
        f.write(@options[:hdr_pre]) if @options[:hdr_pre]
        f.write("- Component:     Identifies the MSCC component in which the given software\n")         if fields.include?(KEY_COMPONENT)
        f.write("                 package is embedded.\n")                                              if fields.include?(KEY_COMPONENT)
        f.write("- Path/File:     Identifies the software package's location inside the #{@flavor}\n")  if fields.include?(KEY_SOURCE_FILE)
        f.write("                 component.\n")                                                        if fields.include?(KEY_SOURCE_FILE)
        f.write("- Name:          Name of the software package.\n")                                     if fields.include?(KEY_NAME)
        f.write("- Version:       Version of the software package.\n")                                  if fields.include?(KEY_VERSION)
        f.write("- License Types: Types of license. This field is provided as a \"hint\" and should\n") if fields.include?(KEY_LICENSE_TYPES_STR)
        f.write("                 not be used in a license audit.\n")                                   if fields.include?(KEY_LICENSE_TYPES_STR)
        f.write("- Source:        This is the location from which MSCC has originally downloaded\n")    if fields.include?(KEY_SOURCE)
        f.write("                 the source of this software package.\n")                              if fields.include?(KEY_SOURCE)
        f.write("                 NOTE: This link may or may not not be valid anymore.\n\n")            if fields.include?(KEY_SOURCE)
        f.write(@options[:hdr_post]) if @options[:hdr_post]
    end
    private :api_header

    def write_diffs(f)
        cnt = 0

        diffs = Array.new()

        # Write difference from previous release table
        f.write("\nLicense differences from previous release\n")
        f.write("=========================================\n\n")

        @license_info.each {|c|
            # Component and name must match
            c_comp = c[KEY_COMPONENT]
            c_name = c[KEY_NAME]

            @license_info_prev.each {|p|
                p_comp  = p[KEY_COMPONENT]
                p_name  = p[KEY_NAME]

                next if c_comp != p_comp || c_name != p_name

                p[KEY_VISITED] = true
                c[KEY_VISITED] = true

                p_version       = p[KEY_VERSION]
                c_version       = c[KEY_VERSION]
                p_license_types = p[KEY_LICENSE_TYPES_STR]
                c_license_types = c[KEY_LICENSE_TYPES_STR]

                next if c_version == p_version && c_license_types == p_license_types

                p[KEY_VERSION_PRV]           = p_version
                p[KEY_VERSION_CUR]           = c_version != p_version ? c_version : "Same as previous"
                p[KEY_LICENSE_TYPES_STR_PRV] = p_license_types
                p[KEY_LICENSE_TYPES_STR_CUR] = c_license_types != p_license_types ? c_license_types : "Same as previous"

                diffs << p
            }
        }

        # Loop once more, getting all new entries
        @license_info.each {|c|
            next if c.has_key?(KEY_VISITED)
            c[KEY_VISITED]               = true
            c[KEY_VERSION_PRV]           = "N/A"
            c[KEY_VERSION_CUR]           = c[KEY_VERSION]
            c[KEY_LICENSE_TYPES_STR_PRV] = "N/A"
            c[KEY_LICENSE_TYPES_STR_CUR] = c[KEY_LICENSE_TYPES_STR]
            diffs << c
        }

        # And once more, getting all removed entries
        @license_info_prev.each {|p|
            next if p.has_key?(KEY_VISITED)
            p[KEY_VISITED]               = true
            p[KEY_VERSION_PRV]           = p[KEY_VERSION]
            p[KEY_VERSION_CUR]           = "N/A"
            p[KEY_LICENSE_TYPES_STR_PRV] = p[KEY_LICENSE_TYPES_STR]
            p[KEY_LICENSE_TYPES_STR_CUR] = "N/A"
            diffs << p
        }

        max_len = max_lengths_get(diffs)

        fields = [KEY_COMPONENT, KEY_NAME, KEY_VERSION_PRV, KEY_VERSION_CUR, KEY_LICENSE_TYPES_STR_PRV, KEY_LICENSE_TYPES_STR_CUR]
        f.write(header_get(fields, max_len))

        diffs.sort_by!{|h| h[KEY_COMPONENT]}

        diffs.each {|m|
            f.write(line_get(m, fields, max_len))
        }
    end
    private :write_diffs

    def write(handle = nil)
        max_len = max_lengths_get(@license_info)

        f = handle
        f = STDOUT if !handle

        f.write("This document is best viewed in a non-line-wrapping editor.\n\n") unless @options[:no_header]

        # Select which fields to write along with the order of these fields.
        fields = [KEY_COMPONENT, KEY_SOURCE_FILE, KEY_NAME, KEY_VERSION, KEY_LICENSE_TYPES_STR]

        # Don't write the source file if we are generating a licence file
        # without header, because it's the end-user that will read it then.
        fields -= [KEY_SOURCE_FILE] if @options[:no_header]

        # Don't print the "Source" column if it's empty for all lines.
        source_empty = true
        @license_info.each {|m|
            if m[KEY_SOURCE].length() > 0
                 source_empty = false
                 break
            end
        }

        fields << KEY_SOURCE unless source_empty

        if not @options[:no_header]
            f.write("Current Version:   #{@options[:release_version_cur]}\n") unless @options[:release_version_cur].nil?
            f.write("Previous Version:  #{@options[:release_version_prv]}\n") unless @options[:release_version_prv].nil?
            f.write("BSP Version:       #{@options[:bsp_version]}\n")         unless @options[:bsp_version].nil?
            f.write("RedBoot Version:   #{@options[:redboot_version]}\n")     unless @options[:redboot_version].nil?
            f.write("Toolchain Version: #{@options[:toolchain_version]}\n")   unless @options[:toolchain_version].nil?
            f.write("\n") unless @options[:no_header]
            @flavor == "MESA" ? api_header(f, fields) : appl_header(f, fields)
        end

        # Write overview table
        f.write("License summary\n")
        f.write("===============\n\n")

        f.write(header_get(fields, max_len))

        @license_info.each {|m|
            m[KEY_PRINTED] = false
        }

        # Print components/categories in pre-selected order.
        @component_print_order.each {|c|
            @license_info.each {|m|
                next if c != m[KEY_COMPONENT]
                f.write(line_get(m, fields, max_len))
                m[KEY_PRINTED] = true;
            }
        }

        # Print the remaining categories
        @license_info.each {|m|
            next if m[KEY_PRINTED]
            f.write(line_get(m, fields, max_len))
            m[KEY_PRINTED] = true;
        }

        # If @license_info_prev is non-empty, also write differences from
        # previous release.
        write_diffs(f) if @license_info_prev.length() > 0

        # Write all the actual licenses
        f.write("\nRaw licenses\n")
        f.write("============\n\n")

        @license_info.each {|m|
            m[KEY_PRINTED] = false
        }

        # Print licenses in pre-selected components/categories order.
        @component_print_order.each {|c|
            @license_info.each {|m|
                next if c != m[KEY_COMPONENT]
                m[KEY_PRINTED] = true
                pos = 0
                m[KEY_LICENSES].each {|l|
                    f.write("#{m[KEY_COMPONENT]} - #{m[KEY_NAME]} - #{m[KEY_LICENSE_TYPES][pos]}:\n")
                    f.write("#{l}\n")
                    f.write(sprintf("\n%s\n\n", "*" * 80))
                    pos += 1
                }
            }
        }

        # Print the remaining licenses
        @license_info.each {|m|
            next if m[KEY_PRINTED]
            m[KEY_PRINTED] = true
            m[KEY_LICENSES].each {|l|
                f.write("#{m[KEY_COMPONENT]} - #{m[KEY_NAME]}:\n")
                f.write("#{l}\n")
                f.write(sprintf("\n%s\n\n", "*" * 80))
            }
        }
    end

    def concat(x)
        @license_info.concat(x.license_info)
    end

    def concat_prev(x)
        @license_info_prev.concat(x.license_info)
    end
end

# Class that parses .module_info files and organizes the contents nicely in
# order to be able to print licenses.
class CLicenseModuleInfo < CLicenseCollection
    def initialize(top_path, component, suppress_errors_regexp = nil, options = nil)
        super('') # Initialize CLicenseCollection

        if options.nil?
            @local_options = Hash.new()
        else
            @local_options = options
        end

        # The options argument is optional, and all its values are as well.
        #   :use_git
        #      If true, a "git ls-files" will be used to find .module_info files
        #      If false or unspecified, "find" will be used to find them.
        #      The difference is that if you e.g. have embedded the API in the
        #      application, and :use_git is false, it will also include the
        #      .module_info files, it finds in the API.
        #   :exclude_if_location_contains_regexp
        #      If non-nil, .module_info files that contains references to
        #      'directory' or 'files' or 'file' that matches this regexp will
        #      be excluded.
        #      A typical :exclude_if_location_contains_regexp is "/test/".
        #   :merge_identical_licenses
        #      If true, we will go over all licenses at the end and see if
        #      name, version, license type, and source are identical, that is,
        #      Path/File will not have to match, and if so, they will be merged
        #      into one.
        @local_options[:use_git]                  = false unless @local_options.key?(:use_git)
        @local_options[:merge_identical_licenses] = false unless @local_options.key?(:merge_identical_licenses)

        @top_path = File.expand_path(top_path)

        # At most one of these keys must exist in each YAML document.
        # They indicate which folder, file or files are under a given license.
        # If none of them are given, the whole directory where this YAML file
        # is placed is considered under this license.
        at_most_one_hot_file_fields = ['directory', 'file', 'files']

        # Exactly one of these keys must exist in each YAML document.
        # They indicate the license itself or a file where it can be found.
        one_hot_license_fields = ['attribution', 'attribution_file']

        module_info = Array.new()
        module_info_files = Array.new()

        if @local_options[:use_git]
            # First get the top .module_info file - if any
            module_info_files = `git -C #{@top_path} ls-files .module_info`.split()

            # Then get the .module_info files for sub-folders
            module_info_files += `git -C #{@top_path} ls-files '*/.module_info'`.split()
            module_info_files.map! {|file| "#{@top_path}/#{file}"}
        else
           Find.find(@top_path) {|path|
               next unless path =~ /\/\.module_info$/
               module_info_files.push(path)
           }
        end

        module_info_files.each {|path|
            # Use load_stream() over load_file() to be able to load multiple
            # documents within the same YAML file.
            YAML.load_stream(File.open(path)) do |yaml|
                if yaml['license'].nil?
                    error("No license info ('license' key) found in #{path}")
                elsif how_many_hot(yaml, at_most_one_hot_file_fields) > 1
                    error("At most one of #{at_most_one_hot_file_fields} must be present in #{path}")
                elsif yaml['license'] != "VTSS"
                    if not one_hot(yaml, one_hot_license_fields)
                        error("Exactly one of #{one_hot_license_fields} must be present in #{path}")
                    end

                    if yaml['category'].nil?
                        yaml[KEY_COMPONENT] = component
                    else
                        yaml[KEY_COMPONENT] = yaml['category']
                    end

                    yaml[KEY_PATH] = path
                    module_info.push(yaml)
                end
            end
        }

        # Post-process so that we get the info on the same form as when
        # processing the BSP
        module_info.each {|m|
            files = Array.new
            at_most_one_hot_file_fields.each {|f|
                next if m[f].nil?

                if m[f].class == Array
                    files.concat(m[f])
                else
                    files << m[f]
                end
            }

            # Default to folder in which this .module_info file resides.
            files << './' if files.length() == 0

            # Get the folder name of the .module_info file. This serves as the
            # base path to the files or folders given by at_most_one_hot_file_fields
            module_info_dir = File.dirname(m[KEY_PATH])

            # Create a line for each file that uses this license
            files.each {|file_relative_to_module_info_file|
                source_file_or_folder = File.expand_path(File.join(module_info_dir, file_relative_to_module_info_file))

                next if not @local_options[:exclude_if_location_contains_regexp].nil? and source_file_or_folder =~ /#{@local_options[:exclude_if_location_contains_regexp]}/

                dir_or_file_exists = File.exist?(source_file_or_folder)
                if not m['placeholder'] and not dir_or_file_exists
                    # If sub-dirs (like 'test') isn't included in the source we
                    # are analyzing, it's OK that the file or folder that the
                    # license covers doesn't exist. We should skip it in that
                    # case. But if we are invoked on a full repository, all
                    # referenced files and folders must exists. So this script
                    # must also be invoked (by hand) on a full repo to check
                    # that all module_info files are correct.
                    # Notice, that this behavior may be overridden by the
                    # special 'placeholder' key in the .module_info file (used
                    # by vtss_api), because the vtss_api not necessarily exists
                    # in the source we are analyzing, but must be included in
                    # the license overview anyway. In this case, the license
                    # must be embedded in the .module_info file or we will get
                    # an error further down this function.
                    error("File or folder (\"#{file_relative_to_module_info_file}\") referenced from \"#{m[KEY_PATH]}\" doesn't exist") unless suppress_errors_regexp && source_file_or_folder =~ /#{suppress_errors_regexp}/
                    next
                end

                h                    = Hash.new()
                h[KEY_LICENSE_TYPES] = Array.new()
                h[KEY_LICENSES]      = Array.new()

                h[KEY_LICENSE_TYPES_STR] = m['license'].to_s().chomp()
                one_hot_license_fields.each {|f|
                    next if m[f].nil?

                    case f
                    when 'attribution'
                        h[KEY_LICENSE_TYPES].push(h[KEY_LICENSE_TYPES_STR])
                        h[KEY_LICENSES].push(m[f].to_s().chomp())

                    when 'attribution_file'
                        attr_file = "#{@top_path}/#{m[f]}"
                        exists = File.file?(attr_file)

                        if not exists
                            # Hack: When bundling the API with the application,
                            # the attribution_file is relative to the top of the
                            # API and not to the top of the application, so try
                            # to look for it one further directory down
                            attr_file = "#{@top_path}/vtss_api/#{m[f]}"
                            exists = File.file?(attr_file)
                        end

                        if exists
                            h[KEY_LICENSE_TYPES].push(h[KEY_LICENSE_TYPES_STR])
                            h[KEY_LICENSES].push(File.open(attr_file).read().to_s().chomp())
                        else
                            # Don't guard this by suppress_errors_regexp,
                            # because if the source is modified and the folder
                            # or file the licence covers exists, so must the
                            # license file.
                            error("License file (\"#{attr_file}\") referenced from #{m[KEY_PATH]} doesn't exist (it must be specified as relative to the top of the repo)")
                            next
                        end
                    else
                        error("Internal error: Update script to support .module_info key = #{f}")
                        h[KEY_LICENSE_TYPES].push(h[KEY_LICENSE_TYPES_STR])
                        h[KEY_LICENSES].push(m[f].to_s().chomp())
                    end
                }

                # Convert source_file_or_folder to a path relative to the top of
                # the project. Both source_file_or_folder and @top_path are
                # absolute paths, and source_file_or_folder is guaranteed to be
                # a subdir of @top_path.
                file_relative_to_top_path = source_file_or_folder.sub(/^#{@top_path}/, '')
                file_relative_to_top_path.sub!(/^\//, '') # Strip leading slash
                file_relative_to_top_path = '.' if file_relative_to_top_path.length() == 0

                # The component (e.g. "Appl") will only be used if the
                # .module_info file section doesn't include it's own category
                # (e.g. "Host Tool").
                h[KEY_PATH]          = m[KEY_PATH]
                h[KEY_COMPONENT]     = m[KEY_COMPONENT]
                h[KEY_SOURCE_FILE]   = file_relative_to_top_path.chomp()
                h[KEY_NAME]          = m['name'].to_s().chomp()
                h[KEY_VERSION]       = m['version'].to_s().chomp()
                h[KEY_SOURCE]        = m['source'].to_s().chomp()

                @license_info << h
            }
        }

        # Sort entries by filenames or path that uses a particular license
        uniquify_and_sort()
    end

    def how_many_hot(yaml, fields)
        cnt = 0

        fields.each {|f|
            cnt += 1 unless yaml[f].nil?
        }

        return cnt
    end

    def one_hot(yaml, fields)
        return how_many_hot(yaml, fields) == 1 ? true : false
    end

    def uniquify_and_sort()
        # If two KEY_SOURCE_FILE entries are identical, remove one of them.
        @license_info.uniq! {|x| x[KEY_SOURCE_FILE]}

        if @local_options[:merge_identical_licenses]
            # With this option, we merge licenses with same Name (e.g. libcxx),
            # same version (e.g. 1.29.3), same license type (e.g. MIT), same
            # source location (e.g. https://github.com/llvm-mirror/libcxx.git),
            # and same license description.
            # This is useful if the x[KEY_SOURCE_FILE] differs, but the
            # resulting licenses.txt does not print the x[KEY_SOURCE_FILE]
            # column.
            @license_info.uniq! {|x| [x[KEY_NAME], x[KEY_VERSION], x[KEY_LICENSE_TYPES_STR], x[KEY_SOURCE], x[KEY_LICENSES]]}
        end

        # Sort by File/Path name
        @license_info.sort! {|x, y| x[KEY_SOURCE_FILE] <=> y[KEY_SOURCE_FILE]}
    end
    private :uniquify_and_sort
end

# Class that parses a CSV (manifest.csv) file and organizes the contents nicely
# in order to be able to print licenses.
class CLicenseCsv < CLicenseCollection
    def initialize(csv_files, component)
        super('') # Initialize CLicenseCollection

        csv_files.each {|csv_file|
            csv = CSV.read(csv_file)
            first = true
            csv.each {|row|
                if first
                    first = false
                    if row[0] != "PACKAGE"        or
                       row[1] != "VERSION"        or
                       row[2] != "LICENSE"        or
                       row[3] != "LICENSE FILES"  or
                       row[4] != "SOURCE ARCHIVE" or
                       row[5] != "SOURCE SITE"
                        error("Unable to parse CSV file \"#{csv_file}\" as it doesn't contain the correct columns")
                        break
                    end
                else
                    h                    = Hash.new()
                    h[KEY_LICENSE_TYPES] = Array.new()
                    h[KEY_LICENSES]      = Array.new()

                    h[KEY_COMPONENT]         = component.chomp()
                    h[KEY_PATH]              = csv_file
                    h[KEY_NAME]              = row[0].chomp()
                    h[KEY_VERSION]           = row[1].chomp()
                    h[KEY_LICENSE_TYPES_STR] = row[2].chomp()

                    # Get license types (there might be more than one)
                    license_types = h[KEY_LICENSE_TYPES_STR].split(",")
                    license_types.each {|t| t.strip!()}

                    if row[5] == "no upstream" or row[5] =~ /bitbucket.microchip.com/
                        # The package is not available for the great masses out
                        # there, so don't publish its location.
                        h[KEY_SOURCE] = ""
                    else
                        h[KEY_SOURCE] = row[5].chomp() + "/" + row[4].chomp()
                    end

                    # Get LICENSE FILES (there might be more than one).
                    files = row[3].split(' ')
                    files.each {|f|
                        license_file = "#{File.dirname(csv_file)}/licenses/#{h[KEY_NAME]}-#{h[KEY_VERSION]}/#{f.chomp()}"
                        h[KEY_LICENSES].push(File.open(license_file).read().to_s().chomp())

                        if (license_types[h[KEY_LICENSES].length() - 1].nil?)
                            # We have more licenses than license types. Re-use
                            # the last.
                            h[KEY_LICENSE_TYPES].push(license_types[license_types.length() - 1])
                        else
                            # Assume there is a one-to-one correspondance
                            # between the position of the license type and the
                            # license file in the CSV file.
                            h[KEY_LICENSE_TYPES].push(license_types[h[KEY_LICENSES].length() - 1])
                        end
                    }

                    @license_info << h
                end
            }
        }

        uniquify_and_sort()
    end

    def uniquify_and_sort()
        # If two licenses are identical (identified by name, version, and
        # license), remove one of them.
        @license_info.uniq! {|x| x.values_at(KEY_NAME, KEY_VERSION)}

        # Sort by name of package
        @license_info.sort! {|x, y| x[KEY_NAME] <=> y[KEY_NAME]}
    end
    private :uniquify_and_sort
end

# Class that installs an explicit license (all fields are specified in the
# call).
class CLicenseExplicit < CLicenseCollection
    def initialize(component, path, name, version, license_type, source, license)
        super('') # Initialize CLicenseCollection

        h                        = Hash.new()
        h[KEY_LICENSE_TYPES]     = Array.new()
        h[KEY_LICENSES]          = Array.new()

        h[KEY_COMPONENT]         = component.chomp()
        h[KEY_PATH]              = path.chomp()
        h[KEY_NAME]              = name.chomp()
        h[KEY_VERSION]           = version.to_s().chomp()
        h[KEY_SOURCE]            = source.chomp()
        h[KEY_LICENSE_TYPES_STR] = license_type.chomp()

        h[KEY_LICENSE_TYPES].push(h[KEY_LICENSE_TYPES_STR])
        h[KEY_LICENSES].push(license.chomp())

        @license_info << h
    end
end

# Class that parses an existing licenses.txt file - with the intent of comparing
# it to the latest licenses and produce a diff.
# The argument release_version_prv tells what we expect the previous version to
# be. If lic_file contains a line matching "Current Version:(.*)", then the
# match must equal release_version_prv, or an error is generated - indicating
# that the branch master has forgotten to commit the previous licenses.
class CLicenseParse < CLicenseCollection
    def initialize(lic_file, release_version_prv = nil)
        super('') # Initialize CLicenseCollection

        h = Hash.new()

        @lic_file = lic_file
        @options[:release_version_prv] = release_version_prv unless release_version_prv.nil?

        # Find and parse the heading of the license summary.
        fields_get()

        # Read the file again, while obtaining the licenses.
        licenses_get()
    end

    # Attempts to find a line that matches the headings we can output.
    # All words in the line must match headings.
    # Sets @fields to the longest matching line. If no such line is found, it
    # raises an error
    def fields_get()
        @fields                    = Hash.new()
        @license_start_line_number = 0
        line_number                = 0
        previous_version_found     = false
        previous_version           = ""

        File.readlines(@lic_file).each {|line|
            # Avoid "invalid byte-sequence in US-ASCII" exception, which may
            # occur if some of the licenses has unicode.
            line.encode!('UTF-8', :invalid => :replace)

            if line =~ /^Current Version:(.*)/
                error("More than one line matching '^Current Version:' found") if previous_version_found
                previous_version_found = true
                previous_version = $1.strip()
            end

            new_fields = nil
            pos        = 0
            prev_len   = line.length()
            line_number += 1

            while prev_len > 0
                match = false
                @headings.each {|key, heading_arr|
                    heading_arr.each {|heading|
                        if line =~ /^\b#{heading}\b/
                            line.sub!(/^#{heading}\s*[^\w]/, '')
                            new_fields = Hash.new unless new_fields
                            new_len  = line.length()
                            width = prev_len - new_len

                            # Is the following producing errors? Then comment out
                            # the line
                            error("key = #{key} already found on line #{line_number}") if new_fields.has_key?(key)

                            new_fields[key] = [pos, width]

                            pos     += prev_len - new_len
                            prev_len = new_len
                            match = true
                            break
                        end
                    }

                    break if match;
                }

                break unless match
            end

            if prev_len == 0 && new_fields
                # Whole line matched. See if new_fields is longer than @fields.
                if new_fields.length() > @fields.length()
                    @fields = new_fields
                    @license_start_line_number = line_number
                end
            end
        }

        error("Couldn't find a license summary header in #{@lic_file} ") if @fields.length() == 0

        # A number of keys must exist
        [KEY_COMPONENT, KEY_NAME, KEY_VERSION, KEY_LICENSE_TYPES_STR].each {|key|
            error("Couldn't find a column with key = #{key} in #{@lic_file} ") unless @fields.has_key?(key)
        }

        if previous_version_found && !@options[:release_version_prv].nil? && previous_version != @options[:release_version_prv]
            error("Previous version found in #{@lic_file} is \"#{previous_version}\", but it was expected to be \"#{@options[:release_version_prv]}\". Did you forget to commit license files from the \"#{@options[:release_version_prv]}\" release?")
        end
    end
    private :fields_get

    def licenses_get()
        line_number = 0

        # Create a pattern that a given line must match, given the fields, we
        # parsed in field_get()
        regexp       = ""
        field_number = 0
        # "Luckily", a hash in Ruby preserves its insertion order when iterating
        @fields.each {|key, value|
            field_number += 1

            if field_number == @fields.length() - 1
                # The next-to-last field doesn't have to have the full width
                min_width = 1
                max_width = value[1]
            elsif field_number == @fields.length()
                # The last field doesn't have to be present
                min_width = 0
                max_width = 1000
            else
                # All other fields must have their full width
                min_width = value[1]
                max_width = value[1]
            end

            regexp += "(.{#{min_width},#{max_width}})"
        }

        File.readlines(@lic_file).each {|line|
            # Avoid "invalid byte-sequence in US-ASCII" exception, which may
            # occur if some of the licenses has unicode.
            line.encode!('UTF-8', :invalid => :replace)
            line.chomp!()

            # Skip past the @license_start_line_number
            line_number += 1
            next if line_number <= @license_start_line_number

            m = line.match(regexp)

            # Stop after the first line that doesn't match
            break if m == nil

            # Skip past lines that start with a "-", which should only be the
            # line after the heading
            next if m[0][0] == '-'

            # Time to build up the hash of license info
            field_number = 0
            h = Hash.new()
            @fields.each {|key, value|
                field_number += 1
                h[key] = m[field_number].strip()
            }

            @license_info << h
        }
    end
    private :licenses_get
end

# Want to try it out offline?
# Modify bsp_path and toolchain_path to a folder with an unpacked version of the
# BSP and Toolchain on your system.
=begin
top            = %x{git rev-parse --show-toplevel}.chomp()
bsp_ver        = "2018.05-166"
bsp_path       = "/opt/mscc/mscc-brsdk-mips-#{bsp_ver}"
toolchain_ver  = "2018.05-057"
toolchain_path = "/opt/mscc/mscc-toolchain-bin-#{toolchain_ver}"
redboot_sha    = "abcdef1"

options = Hash.new()
options[:release_version_prv] = "4.6.0"
options[:release_version_cur] = "4.7.0"
options[:bsp_version]         = bsp_ver
options[:toolchain_version]   = toolchain_ver
options[:redboot_version]     = redboot_sha

result = CLicenseCollection.new("WebStaX", options)

# WebStaX licenses
result.concat(CLicenseModuleInfo.new(top, "WebStaX"))

# BSP licenses
# Starting with SDK 2018.05-100, the manifest.csv files are located in subdirs
# of #{bsp_path}/stage1/legal-info/
manifest_csv_files  = Dir["#{bsp_path}/stage1/legal-info/**/manifest.csv"]
manifest_csv_files += Dir["#{bsp_path}/stage2/smb/legal-info/**/manifest.csv"]
result.concat(CLicenseCsv.new(manifest_csv_files, "BSP"))

# Toolchain licenses
result.concat(CLicenseCsv.new(["#{toolchain_path}/mipsel-mips32r2-linux-gnu/legal-info/manifest.csv", "#{toolchain_path}/mipsel-mips32r2-linux-uclibc/legal-info/manifest.csv"], "Toolchain"))

# Redboot license
result.concat(CLicenseExplicit.new(
        "RedBoot",   # Component
        "",          # Path
        "RedBoot",   # Name
        redboot_sha, # Version
        "GPLv2",     # License type
        "",          # Where did we get the source from?
        "Redboot license as text"))

result.write()
=end
