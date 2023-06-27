#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "ts"

run %w{./check_wireing.rb}, {:name => "check_wireing@ts", :abort_on_err => true}
run %w{./ts_adj_timer.rb}
run %w{./ts_asymmetry_p2p_delay.rb}
run %w{./ts_auto_responce.rb}
run %w{./ts_tod_domain.rb}
run %w{./ts_tod_domain_offset.rb}
run %w{./ts_sequence_id.rb}
run %w{./ts_external_clock_1pps.rb}
run %w{./ts_external_io_1pps.rb}
run %w{./ts_external_clock_frequence.rb}
run %w{./ts_external_io_rs422_1pps.rb}
run %w{./ts_internal_mode.rb}
run %w{./ts_tod_latency.rb}
run %w{./ts_tx_fifo.rb}
run %w{./ts_ptp_ipv4_ipv6.rb}

