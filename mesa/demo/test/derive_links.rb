#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require "pp"
require "json"
require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $c = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    assert($c >= 4, "Port count must be greater than 4")
end

test "Derive port wireing" do
    $ts.pc.p.each do |eth|
        $ts.pc.run "ip link set #{eth} down"
    end
    $ts.pc.run_util "poll_interface_state.rb -d -t 30 #{$ts.pc.p.join " "}"
    sleep 3

    link_db = []
    $c.times do |i|
        begin
            r = $ts.dut.call("mesa_port_status_get", i)
            link_db << i if r["link"]
        rescue
        end
    end

    msg = []
    err = false
    db = {}

    $ts.pc.p.each do |eth|
        link_db_old = link_db
        link_db = []
        $ts.pc.run "ip link set #{eth} up"
        $ts.pc.run_util "poll_interface_state.rb -t 30 #{eth}"
        sleep 3

        $c.times do |i|
            begin
                r = $ts.dut.call("mesa_port_status_get", i)
                link_db << i if r["link"]
            rescue
            end
        end

        links_up   = link_db - link_db_old
        links_down = link_db_old - link_db

        t_i "Links up:   #{links_up.join " "}"
        t_i "Links down: #{links_down.join " "}"
        if links_up.size == 1 and links_down.size == 0
            msg << "LINK-DB: #{eth} <-> #{links_up[0]}"
            db[eth] = links_up[0]
        else
            t_e "Unexpected link change!!!"
            err = true
        end
    end

    if not err
        t_i "Link DB:\n#{msg.join("\n")}"
    else
        t_e "Could not determinate link DB"
    end
end


