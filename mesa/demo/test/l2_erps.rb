#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

# ERPI table with forwarding state per (ERPI, port)
$erpi_table =
    [ { erpi: 10, fwd: [ true , true , false, true  ] },
      { erpi: 20, fwd: [ true , true , true , false ] },
      { erpi: 30, fwd: [ true , false, true , true  ] } ]

# VLAN table with mappings to ERPIs
$vlan_table =
    [ { vid: 100, erpi: [10, 20] },
      { vid: 200, erpi: [20, 30] },
      { vid: 300, erpi: [] } ]

test "conf" do
    test "All ports are C-ports with ingress filtering" do
        $ts.dut.port_list.each do |port|
            conf = $ts.dut.call "mesa_vlan_port_conf_get", port
            conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
            conf["ingress_filter"] = true
            $ts.dut.call "mesa_vlan_port_conf_set", port, conf
        end
    end

    test "All ports are members of all used VLANs" do
        port_list = $ts.dut.p.join(",")
        $vlan_table.each do |v|
            vid = v[:vid]
            $ts.dut.call "mesa_vlan_port_members_set", vid, port_list
            v[:erpi].each do |erpi|
                $ts.dut.call "mesa_erps_vlan_member_set", erpi, vid, true
            end
        end
    end
    
    test "Forwarding state per (ERPI, port)" do
        $erpi_table.each do |e|
            $ts.dut.port_list.each_with_index do |port, i|
                state = "MESA_ERPS_STATE_#{e[:fwd][i] ? "FORW" : "DISC"}ARDING"
                $ts.dut.call "mesa_erps_port_state_set", e[:erpi], port, state
            end
        end
    end
end

#---------- Frame testing -----------------------------------------------------

test "frame-io" do
    $vlan_table.each do |v|
        vid = v[:vid]
        $ts.dut.p.each_index do |idx_tx|
            idx_list = []
            $ts.dut.p.each_index do |idx_rx|
                fwd = (idx_rx != idx_tx)
                $erpi_table.each do |e|
                    if (v[:erpi].include? e[:erpi] and (e[:fwd][idx_tx] == false or e[:fwd][idx_rx] == false))
                        # Discard if ingress or egress port is discarding for any ERPI
                        fwd = false
                    end
                end
                if (fwd)
                    idx_list << idx_rx
                end
            end
            t_i("Classified VID: #{vid}")
            cmd = "eth ctag vid #{vid} et 0xaaaa data pattern cnt 64"
            run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
        end
    end
end
