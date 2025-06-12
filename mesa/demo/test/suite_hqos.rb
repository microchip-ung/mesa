#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "hqos"

run %w{./check_wireing.rb}, {:name => "check_wireing@qos", :abort_on_err => true}
run %w{./hqos.rb}
