#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require "pp"
require "json"
require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

check_capabilities do
    c = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    assert(c >= 4, "Port count must be greater than 4")
end

test "check port wireing" do
    $ts.links.each do |link|
        test "Check link: #{link[:pc]} <-> #{link[:dut]}" do
            $ts.pc.run "ip link set #{link[:pc]} down"
            $ts.pc.run "poll_interface_state.rb -d -t 30 #{link[:pc]}"

            $ts.links.each do |link2|
                if link[:pc] == link2[:pc]
                    check_poll 0.2, 30, "Dut link must be down: #{link2[:dut]}" do
                        r = $ts.dut.call("mscc_appl_port_status_get", link2[:dut])
                        not r["link"]
                    end
                else
                    check_poll 0.2, 60, "Dut link must be up: #{link2[:dut]}" do
                        r = $ts.dut.call("mscc_appl_port_status_get", link2[:dut])
                        r["link"]
                    end
                end
            end

            $ts.pc.run "ip link set #{link[:pc]} up"
            $ts.pc.run "poll_interface_state.rb -u -t 30 #{link[:pc]}"
        end
    end
end
