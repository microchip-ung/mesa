#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/suite'

$suite_name = "packet"

run %w{./check_wireing.rb}, {:name => "check_wireing@packet", :abort_on_err => true}
run %w{./packet_afi.rb}
run %w{./packet_npi_tx.rb}
run %w{./packet_rx_tx.rb}
