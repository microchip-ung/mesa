#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "protection"

run %w{./check_wireing.rb}, {:name => "check_wireing@protection", :abort_on_err => true}
run %w{./l2_eps.rb}
run %w{./l2_erps.rb}
run %w{./l2_frer.rb}
run %w{./mrp_all.rb}
