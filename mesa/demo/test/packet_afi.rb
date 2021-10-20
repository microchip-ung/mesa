#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

#---------- Configuration -----------------------------------------------------

$idx_npi = 0
$idx_rx  = 1

test "conf" do
    t_i("NPI port")
    conf = $ts.dut.call("mesa_npi_conf_get")
    conf["enable"] = true
    conf["port_no"] = $ts.dut.port_list[$idx_npi]
    $ts.dut.call("mesa_npi_conf_set", conf)
end

#---------- Frame testing -----------------------------------------------------

def frame_tx(port, prio, id, len, npi = true)
    if (npi)
        f1 = cmd_tx_ifh_push({"dst_port": port, "cos": prio, "afi_id": id}) + "eth data pattern cnt #{len - 20 - 18}"
        $ts.pc.run("sudo ef name f1 #{f1} tx #{$ts.pc.p[$idx_npi]} name f1")
    else
        tx_info = $ts.dut.call("mesa_packet_tx_info_init")
        tx_info["dst_port_mask"] = (1 << port)
        tx_info["cos"] = prio
        tx_info["afi_id"] = id
        frame = []
        for i in 0..(len - 1)
            frame[i] = (i < 6 ? 0xff : i < 11 ? 0 : i == 11 ? 1 : 0xaa)
        end
        $ts.dut.call("mesa_packet_tx_frame", tx_info, frame, len);
    end
end

def frame_tx_manual(port, prio, id, len)
end

def frame_rx(idx, usec)
    cnt = 10
    $ts.pc.run("sudo ef -c #{$ts.pc.p[idx]},1,adapter_unsynced,,#{cnt}")
    pkts = $ts.pc.get_pcap("#{$ts.pc.p[idx]}.pcap")
    if (pkts.size == cnt)
        t_i("Logged #{cnt} packets, expect #{usec} usec between each")
        t0 = 0
        cnt = 0
        pkts.each_with_index do |p, i|
            t = p[:us_rel]
            txt = "t: #{t}"
            if (i == 0)
                t_i(txt)
            else
                diff = (t - t0)
                txt += ", diff: #{diff}"
                error = false
                if (diff < 0.9*usec or diff > 1.1*usec)
                    cnt = (cnt + 1)
                    if (cnt > 1)
                        # Accept one dropped frame on test PC
                        error = true
                    end
                end
                if (error)
                    t_e(txt)
                else
                    t_i(txt)
                end
            end
            t0 = t
        end
    else
        t_e("Logged #{pkts.size} packets, expected #{cnt}");
    end
end

def check_cnt(port, prio)
    cnt = $ts.dut.call("mesa_port_counters_get", port)
    tx_cnt = cnt["rmon"]["tx_etherStatsPkts"]
    tx_prio = cnt["prio"][prio]["tx"]
    txt = "tx_cnt: #{tx_cnt}, tx_prio[#{prio}]: #{tx_prio}"
    if (tx_cnt == tx_prio)
        t_i(txt)
    else
        t_e(txt)
    end
end

test "frame-io-afi-v1" do
    if (cap_get("AFI_V1") == 0)
        break
    end

    idx = $idx_rx
    prio = 3
    len = 128
    rate = 10 # 10 fps
    usec = 100000
    port = $ts.dut.port_list[idx]
    
    # Clear counters
    $ts.dut.call("mesa_port_counters_clear", port)

    t_i("allocate afi injection")
    id = $ts.dut.call("mesa_afi_alloc", {"fps": rate})[1]

    # Send and hijack frame
    # Hijacking via NPI injection does not seem to work, so manual injection is used.
    t_i("send frame before hijacking")
    frame_tx(port, prio, id, len, false)
    $ts.dut.call("mesa_afi_hijack", id)

    # Check rate of received frames
    frame_rx(idx, usec)

    t_i("stop and free afi")
    $ts.dut.call("mesa_afi_free", id)

    # Check counters
    check_cnt(port, prio)
end

test "frame-io-afi-v2-slow" do
    if (cap_get("AFI_V2") == 0)
        break
    end

    idx = $idx_rx
    prio = 4
    len = 256
    rate = 36000 # 10 fps
    usec = 100000
    port = $ts.dut.port_list[idx]
    
    # Clear counters
    $ts.dut.call("mesa_port_counters_clear", port)

    t_i("allocate afi injection")
    conf = {}
    conf["port_no"] = port
    conf["prio"] = prio
    conf["masquerade_port_no"] = 0
    id = $ts.dut.call("mesa_afi_slow_inj_alloc", conf)

    # Send and hijack frame
    t_i("send frame before hijacking")
    frame_tx(port, prio, id, len)
    $ts.dut.call("mesa_afi_slow_inj_frm_hijack", id)

    t_i("start afi")
    conf = {}
    conf["fph"] = rate
    conf["jitter_mode"] = 0
    conf["first_frame_urgent"] = false
    $ts.dut.call("mesa_afi_slow_inj_start", id, conf)
    
    # Check rate of received frames
    frame_rx(idx, usec)

    t_i("stop and free afi")
    $ts.dut.call("mesa_afi_slow_inj_stop", id)
    $ts.dut.call("mesa_afi_slow_inj_free", id)

    # Check counters
    check_cnt(port, prio)
end

test "frame-io-afi-v2-fast" do
    if (cap_get("AFI_V2") == 0)
        break
    end

    idx = $idx_rx
    prio = 5
    len = (1000/8) # 1000 bits per frame
    rate = 1000*1000
    usec = (rate / (len * 8))
    port = $ts.dut.port_list[idx]

    # Clear counters
    $ts.dut.call("mesa_port_counters_clear", port)

    t_i("allocate afi injection")
    conf = {}
    conf["port_no"] = port
    conf["prio"] = prio
    conf["frm_cnt"] = 1
    conf["masquerade_port_no"] = 0
    id = $ts.dut.call("mesa_afi_fast_inj_alloc", conf)

    # Send and hijack frame
    t_i("send frame before hijacking")
    frame_tx(port, prio, id, len)
    conf = {}
    conf["frm_size"] = len
    $ts.dut.call("mesa_afi_fast_inj_frm_hijack", id, conf)    

    t_i("start afi")
    conf = {}
    conf["bps"] = rate
    conf["seq_cnt"] = 0 # Forever
    act = $ts.dut.call("mesa_afi_fast_inj_start", id, conf)
    
    # Check rate of received frames
    frame_rx(idx, usec)

    t_i("stop and free afi")
    $ts.dut.call("mesa_afi_fast_inj_stop", id)
    $ts.dut.call("mesa_afi_fast_inj_free", id)

    # Check counters
    check_cnt(port, prio)
end
