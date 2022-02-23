#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "acl"

run %w{./check_wireing.rb}, {:name => "check_wireing@acl", :abort_on_err => true}
run %w{./acl.rb}
run %w{./acl_range.rb}
run %w{./acl_redir.rb}
run %w{./sec_acl.rb}
run %w{./sec_auth.rb}
run %w{./sec_hacl.rb}
run %w{./sec_racl.rb}
run %w{./rcl.rb}
