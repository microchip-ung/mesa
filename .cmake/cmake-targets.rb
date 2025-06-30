#!/usr/bin/env ruby

# Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'json'
require 'optparse'
require 'pathname'
require 'shellwords'

ARRAY_PROPS = [ "COMPILE_DEFINITIONS", "INCLUDE_DIRECTORIES",
                "INTERFACE_LINK_LIBRARIES", "INTERFACE_LINK_OPTIONS",
                "LINK_DEPENDS", "LINK_LIBRARIES", "LINK_OPTIONS",
                "MANUALLY_ADDED_DEPENDENCIES", "SOURCES",
                "INTERFACE_COMPILE_DEFINITIONS", "COMPILE_OPTIONS",
                "INTERFACE_COMPILE_OPTIONS", "INTERFACE_INCLUDE_DIRECTORIES",
                "TARGET_OBJECTS", "RDEPS", ]

class CmakeTargets
  attr_accessor :targets, :root_targets
  def initialize path
    @path = path
    @root_targets = []
    load_cmake_target_db()
    load_compile_commands()
  end

  def visit(target_name, &cb)
    stack = []
    #puts "Visit: #{target_name}"
    visit_(target_name, stack, "", cb)
  end

 private
  def load_cmake_target_db
    puts "Reading: #{@path}/cmake_target_db.txt"
    x = File.read("#{@path}/cmake_target_db.txt")

    @targets = {}
    x.split("\n").each do |l|
      if l =~ /([^ ]+) (\w+) = (.+)/
        t = @targets[$1]
        if t.nil?
          @targets[$1] = {}
          t = @targets[$1]
        end

        if ARRAY_PROPS.include? $2
          t[$2] = $3.split(";")
        else
          t[$2] = $3
        end
      elsif l =~ /([^ ]+) (\w+) =\s*$/
      else
        puts "Garbage: #{l}"
      end
    end

    @targets.each do |k, v|
      ARRAY_PROPS.each do |p|
        if v[p].nil?
          if v[p] = []
          end
        end
      end
    end

    @targets.each do |k, v|
      deps = targets_deps(v)
      v["DEPS"] = deps
      deps.each do |d|
        dd = @targets[d]
        if dd.nil?
          puts "Missing dependency! #{k} dependes on '#{d}', but '#{d}' could not be found"
        else
          @targets[d]["RDEPS"] << k
        end
      end
    end

    @targets.each do |k, v|
      v["RDEPS"].uniq!
      if v["RDEPS"].size == 0
        @root_targets << k
      end
    end

  end

  def targets_deps(target)
    res = []
    ["LINK_LIBRARIES", "MANUALLY_ADDED_DEPENDENCIES", "INTERFACE_LINK_LIBRARIES"].each do |p|
      l = target[p]
      res += l if l
    end
    return res.uniq
  end

  def load_compile_commands
    j = JSON.parse(File.read("#{@path}/compile_commands.json"))
    @compile_cmds = {}
    @compile_cmds_by_src = {}

    j.each do |r|
      #puts "----"
      next_is_output = false
      o = nil
      #puts r["command"]
      Shellwords.split(r["command"]).each do |w|
        o = w if next_is_output
        next_is_output = (w == "-o")
      end

      #puts o
      if o
        p = Pathname.new o
        p = p.expand_path(@path)
        if @compile_cmds[o]
          raise "multiple commands generate same output!"
        end
        #puts "abs out path: #{p.to_s}"
        r["obj"] = p.to_s
        @compile_cmds_by_src[r["file"]] = r
        @compile_cmds[p.to_s] = r
      end
    end
  end

  def visit_(target_name, stack, indent, cb)
    #puts "#{indent}#{target_name}"
    t = @targets[target_name]
    return if t.nil?

    if t["mark"]
      puts "Loops! #{stack.inspect}"
      raise "loops"
    else
      t["mark"] = true
    end

    stack.push target_name

    add_compile_cmds t
    cb.call target_name, t, indent, stack

    deps = targets_deps(t)
    deps.each do |d|
      visit_(d, stack, indent + " ", cb)
    end

    t["mark"] = false
    stack.pop
  end

  def add_compile_cmds target
    compile_command_records = []
    src_bin_pairs = []

    src_a = []
    target["TARGET_OBJECTS"].each do |bin|
      p = Pathname.new bin
      if not p.absolute?
        p = p.expand_path(@path)
      else
        p = p.expand_path
      end

      cmds = @compile_cmds[p.to_s]
      if cmds.nil?
        pp @compile_cmds.to_a.collect{|x| x[0]}
        puts p.to_s
        raise "not found"
      end

      src_path_json = Pathname.new cmds["file"]
      if not src_path_json.absolute?
        src_path_json = src_path_json.expand_path(cmds["directory"])
      else
        src_path_json = src_path_json.expand_path
      end

      src_bin_pairs << [src_path_json.to_s, p.to_s]
      src_a << src_path_json.to_s
      compile_command_records << cmds
    end

    src_b = []
    target["SOURCES"].each do |src|
      src_path = Pathname.new src
      if not src_path.absolute?
        src_path = src_path.expand_path(target["SOURCE_DIR"])
      else
        src_path = src_path.expand_path
      end
      src_b << src_path.to_s
    end

    s = src_a - src_b
    if (s.size != 0)
      pp s
      raise "Some sources was not covered"
    end

    target["COMPILE_COMMANDS"] = compile_command_records
    target["SRC_BIN_PAIRS"] = src_bin_pairs
  end
end

if $0 == __FILE__
  $opt_path = nil
  $top = File.dirname(File.dirname(File.expand_path(__FILE__)))

  opt_parser = OptionParser.new do |opts|
    opts.banner = """Usage: lm-cov-runner [options]

Options:"""
    opts.on("-b", "--build NAME", "Name of build folder (must be present in project top)") do |p|
      $opt_path = "#{$top}/#{p}"
    end

    opts.on("-t", "--target TARGET", "Target to show") do |t|
      $opt_target = t
    end

    opts.on("-r", "--root-targets", "List root-targets") do |t|
      $opt_roots = true
    end

    opts.on("-h", "--help", "Show this message") do
      puts opts
      exit
    end
  end

  opt_parser.parse!(ARGV)

  if $opt_path.nil?
    puts "Missing option: -b NAME"
    exit -1
  end

  ct = CmakeTargets.new $opt_path
  if $opt_roots
    ct.root_targets.each do |t|
      puts t
    end
    exit
  end

  if $opt_target.nil?
    ct.root_targets.each do |t|
      ct.visit(t) do |target_name, target, indent, stack|
        puts "#{indent}#{target_name}"
      end
    end
    exit
  else
    ct.visit($opt_target) do |target_name, target, indent, stack|
      puts "#{indent}#{target_name}"
    end
    exit
  end
end
