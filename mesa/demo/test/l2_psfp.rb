#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

# Enable PSFP counters using "-vp" option
$ts = get_test_setup("mesa_pc_b2b_2x", {}, "-vp")

# Check if PSFP supported
cap_check_exit("L2_PSFP")

#---------- Configuration -----------------------------------------------------

$idx_tx = 0
$idx_rx = 1
$istat = 0
$pol = 0
$filter_id = 10
$gate_id = 12
$is_fireant_arch = false
$is_correct_order = true
$fa_rev0 = false

test "conf" do
    epid = cap_get("PACKET_IFH_EPID")
    if (epid == 11)
        $is_fireant_arch = true
        $is_correct_order = false
        chip_id = $ts.dut.call("mesa_chip_id_get")
        if (chip_id["revision"] == 0)
            # FireAnt revision 0 does not support priority change and discard of small frames
            $fa_rev0 = true
        end
    elsif (epid == 14)
        # Laguna
        $is_fireant_arch = true
    end

    # Ingress counters
    $istat = $ts.dut.call("mesa_ingress_cnt_alloc", 1)
    
    # DLB policer
    $pol = $ts.dut.call("mesa_dlb_policer_alloc", 1)

    # Ingress flow
    iflow = $ts.dut.call("mesa_iflow_alloc")
    conf = $ts.dut.call("mesa_iflow_conf_get", iflow)
    conf["cnt_enable"] = true
    conf["cnt_id"] = $istat
    conf["dlb_enable"] = true
    conf["dlb_id"] = $pol
    conf["psfp"]["filter_enable"] = true
    conf["psfp"]["filter_id"] = $filter_id
    $ts.dut.call("mesa_iflow_conf_set", iflow, conf)
    
    # VCE
    port = $ts.dut.port_list[$idx_tx]
    vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
    vce["id"] = 1
    vce["key"]["port_list"] = "#{port}"
    action = vce["action"]
    action["flow_id"] = iflow
    $ts.dut.call("mesa_vce_add", 0, vce)

    # Filter
    conf = $ts.dut.call("mesa_psfp_filter_conf_get", $filter_id)
    conf["gate_enable"] = true
    conf["gate_id"] = $gate_id
    $ts.dut.call("mesa_psfp_filter_conf_set", $filter_id, conf)
end

def filter_test(txt, conf, fwd, len = 192)
    txt = ("filter." + txt)
    test txt do
        if (conf != nil)
            $ts.dut.call("mesa_psfp_filter_conf_set", $filter_id, conf)
        end
        run_ef_tx_rx_cmd($ts, $idx_tx, fwd ? [1,2,3] : [], "eth data pattern cnt #{len - 18}")
    end
end

def frame_test(txt, prio, len, tx_cnt, rx_min, rx_max)
    # Run frame test
    port = $ts.dut.port_list[$idx_rx]
    $ts.dut.call("mesa_port_counters_clear", port)
    $ts.pc.run("sudo ef name f1 eth data pattern cnt #{len - 18} tx #{$ts.pc.p[$idx_tx]} rep #{tx_cnt} name f1")
    rx_cnt = $ts.dut.call("mesa_port_counters_get", port)["prio"][prio]["tx"]
    t_i("#{txt}, tx_cnt: #{tx_cnt}, rx_cnt_#{prio}: #{rx_cnt} (rx_min: #{rx_min}, rx_max: #{rx_max})")
    if (rx_cnt < rx_min)
        t_e("Rx #{rx_cnt}, expected minimum #{rx_min}")
    end
    if (rx_cnt > rx_max)
        t_e("Rx #{rx_cnt}, expected maximum #{rx_max}")
    end
end

def policer_test(txt, conf, prio, len, tx_cnt, rx_min = tx_cnt, rx_max = rx_min)
    txt = ("policer." + txt)
    test txt do
        if (conf != nil)
            $ts.dut.call("mesa_dlb_policer_conf_set", $pol, 0, conf)
        end
        sleep(1) # Allow bucket tokens to accumulate
        frame_test(txt, prio, len, tx_cnt, rx_min, rx_max)
    end
end

def gate_test(txt, conf, prio, len, tx_cnt, rx_min = tx_cnt, rx_max = rx_min)
    txt = ("gate." + txt)
    test txt do
        if (conf != nil)
            # Apply GCL in one second
            base_time = $ts.dut.call("mesa_ts_timeofday_get")[0]
            base_time["seconds"] = (base_time["seconds"] + 1)
            conf["config"]["base_time"] = base_time
            $ts.dut.call("mesa_psfp_gate_conf_set", $gate_id, conf)
            sleep(1)
        end
        frame_test(txt, prio, len, tx_cnt, rx_min, rx_max)
    end
end

def fld_check(data, name, exp)
    val = data[name]
    msg = "#{name} = #{val}, expected #{exp}"
    if (val == exp)
        t_i(msg)
    else
        t_e(msg)
    end
end

def cnt_check(cnt, name, exp)
    fld_check(cnt, name, exp)
end

def filter_status_test(id, name, exp)
    status = $ts.dut.call("mesa_psfp_filter_status_get", id)
    fld_check(status, name, exp)
end

def gate_status_test(id, name, exp)
    status = $ts.dut.call("mesa_psfp_gate_status_get", id)
    fld_check(status, name, exp)
end

def dlb_status_test(id, name, exp)
    status = $ts.dut.call("mesa_dlb_policer_status_get", id, 0)
    fld_check(status, name, exp)
end

test "frame-filter" do
    # MaxSDU
    conf = $ts.dut.call("mesa_psfp_filter_conf_get", $filter_id)
    max_sdu = 256
    conf["max_sdu"] = max_sdu
    filter_test("max_sdu.discard", conf, false, max_sdu + 1)
    filter_test("max_sdu.forward", nil, true, max_sdu)

    # Block oversize
    filter_status_test($filter_id, "block_oversize", false)
    conf["block_oversize"]["enable"] = true
    conf["block_oversize"]["value"] = true
    filter_test("block_oversize.all", conf, false)
    conf["block_oversize"]["value"] = false
    filter_test("block_oversize.forward", conf, true)
    filter_test("block_oversize.blocking", nil, false, max_sdu + 1)
    filter_test("block_oversize.blocked", nil, false)
    filter_status_test($filter_id, "block_oversize", true)
    conf["block_oversize"]["enable"] = false
    conf["max_sdu"] = 0
    filter_test("block_oversize.reopen", conf, true)

    # Gate discard
    prio = 0
    len = ($fa_rev0 ? 192 : 64)
    conf = $ts.dut.call("mesa_psfp_gate_conf_get", $gate_id)
    conf["enable"] = true
    gate_test("closed", conf, prio, len, 1, 0)

    # Counter check
    cnt = $ts.dut.call("mesa_ingress_cnt_get", $istat, 0)
    cnt_check(cnt, "rx_match", 8)
    if ($is_correct_order)
        # Order: Filter->Gate->Policer
        cnt_check(cnt, "rx_sdu_discard", 4)
        cnt_check(cnt, "rx_sdu_pass", 4)
        cnt_check(cnt, "rx_gate_discard", 1)
        cnt_check(cnt, "rx_gate_pass", 3)
    else
        # Order: Gate->Filter->Policer
        cnt_check(cnt, "rx_gate_discard", 1)
        cnt_check(cnt, "rx_gate_pass", 7)
        cnt_check(cnt, "rx_sdu_discard", 2)
        cnt_check(cnt, "rx_sdu_pass", 5)
    end
end

test "frame-gate" do
    # Gate priority
    prio = ($fa_rev0 ? 0 : 7)
    conf = $ts.dut.call("mesa_psfp_gate_conf_get", $gate_id)
    conf["enable"] = true
    conf["gate_open"] = true
    conf["prio"]["enable"] = true
    conf["prio"]["value"] = prio
    gate_test("prio", conf, prio, 192, 1)
    conf["prio"]["enable"] = false
    # The following tests should work at 1G and 10G speeds:
    # - 100 usec gate intervals are used.
    # - Frame size of 10000 bits per frame.
    # - 1G: 10 frames per 100 usec.
    # - 10G: 100 frames per 100 usec.
    len = ((10000/8) - 20)
    tx_cnt = 1000
    prio = 0
    conf["prio"]["value"] = prio
    
    # Gate states
    time_interval = 100000 # 100 usec
    conf["config_change"] = true
    gcl_conf = conf["config"]
    gcl_conf["cycle_time"] = (2 * time_interval)
    gcl = $ts.dut.call("mesa_psfp_gcl_conf_get", $gate_id, 4)[0]
    gce_cnt = 2
    gce = gcl[0]
    gce["gate_open"] = true
    gce["time_interval"] = time_interval
    gce = gcl[1]
    gce["gate_open"] = false
    gce["time_interval"] = time_interval
    $ts.dut.call("mesa_psfp_gcl_conf_set", $gate_id, gce_cnt, gcl)
    rx_min = (tx_cnt*45/100) # Minimum 45 % pass
    rx_max = (tx_cnt*55/100) # Maximum 55 % pass
    gate_test("state", conf, prio, len, tx_cnt, rx_min, rx_max)

    t_i("gate.interval")
    $ts.dut.call("mesa_ingress_cnt_clear", $istat, 0)
    cmd = "sudo ef -c #{$ts.pc.p[$idx_rx]},1,adapter_unsynced,,#{tx_cnt} "
    cmd += "name f1 eth data pattern cnt #{len - 18} tx #{$ts.pc.p[$idx_tx]} rep #{tx_cnt} name f1"
    $ts.pc.run(cmd)
    pkts = $ts.pc.get_pcap "#{$ts.links[1][:pc]}.pcap"
    if (pkts.size == 0)
        t_e("No packets logged");
    else
        t_i("Logged #{pkts.size} packets")
        t_int = (time_interval / 1000) # Microseconds
        t0 = 0
        t0_valid = false
        margin = 20
        pkts.each do |p|
            t = p[:us_rel]
            diff = (t - t0)
            txt = "(t: #{t}, t0: #{t0}, diff: #{diff})"
            if (diff < 0)
                t_e("Prev interval #{txt}")
            elsif (diff < (t_int + margin))
                t_i("Same interval #{txt}")
            elsif (!t0_valid or (diff > (2*t_int - margin) and diff < (2*t_int + margin)))
                t_i("Next interval #{txt}")
                t0 = t
                t0_valid = true
            else
                t_i("Closed interval #{txt}")
            end
        end
    end
    $ts.dut.call("mesa_ingress_cnt_get", $istat, 0)

    # Invalid Rx
    gate_status_test($gate_id, "close_invalid_rx", false)
    conf["close_invalid_rx"]["enable"] = true
    conf["close_invalid_rx"]["value"] = true
    gate_test("close_invalid_rx.all", conf, prio, len, tx_cnt, 0)
    conf["close_invalid_rx"]["value"] = false
    gate_test("close_invalid_rx.closing", conf, prio, len, tx_cnt, 0, rx_max)
    gate_status_test($gate_id, "close_invalid_rx", true)
    gate_test("close_invalid_rx.closed", nil, prio, len, tx_cnt, 0)
    conf["close_invalid_rx"]["enable"] = false

    # Octets exceeded
    gce_cnt = 1
    gce = gcl[0]
    gce["octet_max"] = len
    gate_status_test($gate_id, "close_octets_exceeded", false)
    $ts.dut.call("mesa_psfp_gcl_conf_set", $gate_id, gce_cnt, gcl)
    conf["close_octets_exceeded"]["enable"] = true
    conf["close_octets_exceeded"]["value"] = true
    gate_test("close_octets_exceeded.all", conf, prio, len, tx_cnt, 0)
    conf["close_octets_exceeded"]["value"] = false
    gate_test("close_octets_exceeded.closing", conf, prio, len, tx_cnt, 1, 2)
    gate_status_test($gate_id, "close_octets_exceeded", true)
    gate_test("close_octets_exceeded.closed", nil, prio, len, tx_cnt, 0)
    conf["close_octets_exceeded"]["enable"] = false
    conf["enable"] = false
    gate_test("disabled", conf, prio, len, 1)
end

test "frame-policer" do
    prio = 0
    len = 1024
    conf = $ts.dut.call("mesa_dlb_policer_conf_get", $pol, 0)
    if ($is_fireant_arch)
        # FireAnt: Send 10 frames, expect 1-2 frames
        tx_cnt = 10
        rx_min = 1
        rx_max = 2
    else
        # Maserati: Send 20 frames, expect 5-15 frames
        tx_cnt = 20
        rx_min = 5
        rx_max = 15
    end

    # CIR policing
    conf["enable"] = true
    conf["cir"] = 100 # Current minimum rate in DLB API
    conf["cbs"] = len # Room for one frame
    policer_test("cir.red", conf, prio, len, tx_cnt, rx_min, rx_max)
    policer_test("cir.red", nil, prio, len, tx_cnt, rx_min, rx_max)

    # Forced close: All frames red
    dlb_status_test($pol, "mark_all_red", false)
    conf["mark_all_red"]["enable"] = true
    conf["mark_all_red"]["value"] = true
    policer_test("mark_red.enable", conf, prio, len, tx_cnt, 0)

    # Mark all red
    conf["mark_all_red"]["value"] = false
    policer_test("mark_red.closing", conf, prio, len, tx_cnt, rx_min, rx_max)
    policer_test("mark_red.closed", nil, prio, len, tx_cnt, 0)
    dlb_status_test($pol, "mark_all_red", true)

    # EIR policing
    conf["mark_all_red"]["enable"] = false
    conf["eir"] = 100
    conf["ebs"] = (tx_cnt*len)
    policer_test("eir.yellow.fwd", conf, prio, len, tx_cnt)

    # Drop yellow
    conf["drop_yellow"] = true
    policer_test("eir.yellow.drop", conf, prio, len, tx_cnt, rx_min, rx_max)
end
