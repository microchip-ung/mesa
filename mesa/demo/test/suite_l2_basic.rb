#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "l2_basics"

run %w{./check_wireing.rb}, {:name => "check_wireing@l2_basics", :abort_on_err => true}
run %w{./l2_aggr.rb}
run %w{./l2_evlan.rb}
run %w{./l2_flood.rb}
run %w{./l2_igmp.rb}
run %w{./l2_isolation.rb}
run %w{./l2_mac_idx.rb}
run %w{./l2_mac_table.rb}
run %w{./l2_mirror.rb}
run %w{./l2_mld.rb}
run %w{./l2_psfp.rb}
run %w{./l2_pvlan.rb}
run %w{./l2_ssm.rb}
run %w{./l2_stp.rb}
run %w{./l2_vcl.rb}
run %w{./l2_vcl_ops.rb}
run %w{./l2_vlan.rb}
run %w{./l2_vlan_counters.rb}
run %w{./l2_vlan_tag.rb}
run %w{./l2_vlan_translation.rb}
