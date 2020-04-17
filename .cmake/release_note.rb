#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative './release_utils.rb' # For installing release_note.rb locally

# This is a thin wrapper around release_note.rb from the mscc-release-utils GIT
# repo.
# The require_relative above performs a lazy install of a given version of the
# release utilities, and sets a variable that we can refer to below.

# Find the top of API no matter where we invoke this script from
# We know that this script is located one folder from the top.
top_dir   = File.dirname(File.dirname(File.expand_path(__FILE__))) 
yaml_file = "#{top_dir}/.cmake/release.yaml"
cmd       = "#{MSCC_RELEASE_UTILS_DIR}/release_note.rb"
system("#{cmd} --api --top #{top_dir} --no-bz --yaml #{yaml_file} --verbosity info " + ARGV.join(" "))

