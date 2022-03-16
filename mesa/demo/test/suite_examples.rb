#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "examples"

run %w{./check_wireing.rb}, {:name => "check_wireing@examples", :abort_on_err => true}
run %w{./example_l2_aggr.rb}
run %w{./example_l2_eflow.rb}
run %w{./example_l2_evlan.rb}
run %w{./example_l2_stp.rb}
run %w{./example_l2_vlan.rb}
run %w{./example_l3_ip_uc.rb}
run %w{./example_packet_rx_tx.rb}
run %w{./example_qos-time-aware-scheduler.rb}
run %w{./example_ts_transparent_clock.rb}
run %w{./example_tsn_fp.rb}
run %w{./example_tsn_frer.rb}
run %w{./example_tsn_psfp.rb}
run %w{./example_vop.rb}
run %w{./example_mrp.rb}
run %w{./example_port_conf_bulk.rb}
run %w{./example_port_dynamic.rb}

