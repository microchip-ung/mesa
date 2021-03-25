#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "port"

run %w{./check_wireing.rb}, {:name => "check_wireing@port", :abort_on_err => true}

run %w{./port_buf_measurement.rb}
run %w{./port_flow_control_test1.rb}
run %w{./port_flow_control_test2.rb}
run %w{./port_forward.rb}
run %w{./port_loop.rb}
run %w{./port_pfc.rb}
run %w{./port_counters.rb}
run %w{./port_frame_length_chk.rb}
run %w{./port_mtu.rb}
run %w{./port_speeds.rb}
run %w{./port_bulk_frames.rb}
run %w{./port_kr.rb}
run %w{./port_kr_stress.rb}

