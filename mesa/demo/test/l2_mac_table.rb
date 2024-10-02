#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$conf_table = [ { automatic: true,  discard: false },
                { automatic: true,  discard: false },
                { automatic: true,  discard: true  },
                { automatic: false, discard: false } ]

$mac_table = [ "00:00:00:00:00:01",
               "00:00:00:00:00:02",
               "00:00:00:00:00:03",
               "00:00:00:00:00:04" ]

test "learn limit" do
if $ts.dut.call("mesa_capability", "MESA_CAP_L2_LEARN_LIMIT") == 1
    idx_tx = 0
    idx_list = [1,2,3]
    port = $ts.dut.port_list[idx_tx]

    t_i("Set learn limit on port #{port}")
    conf = $ts.dut.call "mesa_learn_port_mode_get", port
    conf["automatic"] = true
    conf["discard"] = false
    conf["one_shot"] = false
    conf["learn_limit"] = 10
    $ts.dut.call "mesa_learn_port_mode_set", port, conf

    for smac in 1..15
        cmd = "eth dmac 00:00:00:00:00:FF smac 00:00:00:00:00:%02x " % [smac]
        run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
    end

    cnt = 0
    vid_mac = { vid: 1, mac: { addr: [0,0,0,0,0,0] } }
    15.times {
        entry = $ts.dut.try_ignore "mesa_mac_table_get_next", vid_mac
        if (entry.nil?)
            break
        end
        vid_mac = entry["vid_mac"]
        cnt = cnt + 1
    }

    if (cnt != 10)
        t_e("Unexpected MAC count")
    end

    conf["learn_limit"] = 0
    $ts.dut.call "mesa_learn_port_mode_set", port, conf
end
end

test "conf" do
    t_i("Setting learn mode per port")
    $ts.dut.port_list.each_with_index do |port, idx|
        entry = $conf_table[idx]
        conf = $ts.dut.call "mesa_learn_port_mode_get", port
        conf["automatic"] = entry[:automatic]
        conf["discard"] = entry[:discard]
        $ts.dut.call "mesa_learn_port_mode_set", port, conf
    end

    t_i("Adding static entry on the last port")
    port = $ts.dut.port_list[3]
    entry = {
        vid_mac: { vid: 1, mac: { addr: [0,0,0,0,0,4] } },
        destination: "#{port}",
        copy_to_cpu: false,
        copy_to_cpu_smac: false,
        locked: true,
        index_table: false,
        aged: false,
        cpu_queue: 0,
    }
    $ts.dut.call "mesa_mac_table_add", entry

    t_i("Add another entry, check that it is there, delete it and check that it is gone")
    entry = $ts.dut.call "mesa_mac_table_get", entry[:vid_mac]
    entry["vid_mac"]["mac"]["addr"][5] = 5
    $ts.dut.call "mesa_mac_table_add", entry
    entry = $ts.dut.call "mesa_mac_table_get", entry["vid_mac"]
    $ts.dut.call "mesa_mac_table_del", entry["vid_mac"]
    entry = $ts.dut.call_err "mesa_mac_table_get", entry["vid_mac"]
end

#---------- Frame testing -----------------------------------------------------

test "frame_io" do
    t_i("Sending learn frames on each port")
    $ts.dut.p.each_index do |idx_tx|
        idx_list = []
        $ts.dut.p.each_index do |idx_rx|
            if (idx_rx != idx_tx and $conf_table[idx_tx][:discard] == false)
                idx_list << idx_rx
            end
        end
        cmd = "eth smac #{$mac_table[idx_tx]}"
        run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
    end

    t_i("Checking get_next")
    vid_mac = { vid: 1, mac: { addr: [0,0,0,0,0,0] } }
    $ts.dut.port_list.each_with_index do |port, idx|
        entry = $ts.dut.call "mesa_mac_table_get_next", vid_mac
        if (entry.nil?)
            t_e("MAC entry on port #{port} not found")
            break
        end
        vid_mac = entry["vid_mac"]
        port_list = entry["destination"]
        error = (vid_mac["mac"]["addr"][5] != (idx + 1) or port_list != "#{port}")
        txt = "MAC entry #{vid_mac}, port_list: #{port_list}, port: #{port}"
        if (error)
            t_e(txt)
        else
            t_i(txt)
        end
    end

    t_i("Sending unicast frames to neigbour port")
    $ts.dut.p.each_index do |idx_tx|
        idx_other = (idx_tx.odd? ? (idx_tx - 1) : (idx_tx + 1))
        idx_list = []
        $ts.dut.p.each_index do |idx_rx|
            if (idx_rx == idx_other)
                idx_list << idx_rx
            end
        end
        cmd = "eth dmac #{$mac_table[idx_other]} smac #{$mac_table[idx_tx]}"
        run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
    end

    t_i("Flushing first port and sending some unicast frames again")
    $ts.dut.call "mesa_mac_table_port_flush", $ts.dut.port_list[0]         # Flush first port
    $ts.dut.call "mesa_mac_table_vlan_flush", 2                            # No effect, VLAN 2 unused
    $ts.dut.call "mesa_mac_table_vlan_port_flush", $ts.dut.port_list[2], 3 # No effect, VLAN 3 unused
    $ts.dut.call "mesa_mac_table_port_flush", $ts.dut.port_list[3]         # No effect, only static entry
    $ts.dut.p.each_index do |idx_tx|
        if (idx_tx == 0)
            # Skip first port to avoid relearning the flushed address
            next
        end
        idx_other = (idx_tx.odd? ? (idx_tx - 1) : (idx_tx + 1))
        idx_list = []
        $ts.dut.p.each_index do |idx_rx|
            if (idx_rx != idx_tx and (idx_rx == idx_other or idx_other == 0))
                idx_list << idx_rx
            end
        end
        cmd = "eth dmac #{$mac_table[idx_other]} smac #{$mac_table[idx_tx]}"
        run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
    end

    t_i("Flushing all and sending unicast frames from last port")
    $ts.dut.call "mesa_mac_table_flush"
    # Only send from last port to avoid relearning the flushed addresses
    idx_tx = 3
    for i in 0..2
        idx_list = []
        $ts.dut.p.each_index do |idx_rx|
            if (idx_rx != idx_tx)
                idx_list << idx_rx
            end
        end
        cmd = "eth dmac #{$mac_table[i]} smac #{$mac_table[idx_tx]}"
        run_ef_tx_rx_cmd($ts, idx_tx, idx_list, cmd)
    end
end
