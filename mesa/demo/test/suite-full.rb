#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "full"

run %w{./suite_acl.rb}
run %w{./suite_examples.rb}
run %w{./suite_l2_basic.rb}
run %w{./suite_l3_rt.rb}
run %w{./suite_packet.rb}
run %w{./suite_port.rb}
run %w{./suite_protection.rb}
run %w{./suite_qos.rb}
run %w{./suite_ts.rb}
run %w{./suite_vop.rb}
