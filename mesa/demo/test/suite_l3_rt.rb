#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "l3_rt"

run %w{./check_wireing.rb}, {:name => "check_wireing@l3_rt", :abort_on_err => true}
run %w{./l3_ip_uc.rb}
run %w{./l3_ecmp.rb}
run %w{./l3_ip_mc.rb}
run %w{./l3_ip_mc_bulk.rb}
run %w{./l3_ip_mc_rlegs_bulk.rb}
run %w{./l3_ip_mc_rpf.rb}
run %w{./l3_ipv6_mc.rb}
run %w{./l3_ipv6_mc_bulk.rb}


