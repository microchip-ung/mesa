#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "qos"

run %w{./check_wireing.rb}, {:name => "check_wireing@qos", :abort_on_err => true}
run %w{./qos_map.rb}
run %w{./qos_dscp.rb}
run %w{./qos_crb.rb}
run %w{./qos_fp.rb}
run %w{./qos_pcp.rb}
run %w{./qos_qcl.rb}
run %w{./qos-port-param.rb}
run %w{./qos-port-policer.rb}
run %w{./qos-port-shaper.rb}
run %w{./qos-queue-policer.rb}
run %w{./qos-queue-shaper.rb}
run %w{./qos-scheduler.rb}
run %w{./qos-dlb-policer.rb}
run %w{./qos-time-aware-scheduler.rb}
run %w{./qos-otit-scheduler-shaper.rb}

