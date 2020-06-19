#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Configuration -----------------------------------------------------

$idx_tx  = 0 # PC Tx port
$idx_rx  = 1 # PC Rx port
$rtp_id = 3
$port_rte = nil

test "conf" do
    port_cnt = cap_get("PORT_CNT")
    map = $ts.dut.call("mesa_port_map_get", port_cnt)
    for port in 0..(port_cnt - 1)
        if (map[port]["chip_port"] == 4)
            $port_rte = port
        end
    end
    if ($port_rte == nil)
        t_e("RTE port not found")
    else
        t_i("RTE port: #{$port_rte}")
    end

    # Enable untagged RTP processing
    conf = { "pcp": [true, true, true, true, true, true, true, true]}
    $ts.dut.call("mesa_rcl_vid_add", 0, conf)

    # Enable RTE
    conf = $ts.dut.call("lan9662_rte_gen_conf_get")
    conf["enable"] = true
    $ts.dut.call("lan9662_rte_gen_conf_set", conf)

end

def rx_cnt_test(sub_id)
    # Add RCE mapping to RTP ID
    rce = $ts.dut.call("mesa_rce_init")
    rce["id"] = 1
    k = rce["key"]
    k["port_no"] = $ts.dut.p[$idx_tx]
    k["etype"] = "MESA_RCL_ETYPE_PROFINET"
    a = rce["action"]
    a["rtp_id"] = $rtp_id
    a["rtp_sub_id"] = (sub_id == 1) # Boolean
    a["port_enable"] = true
    a["port_list"] = "#{$port_rte}"
    $ts.dut.call("mesa_rce_add", 0, rce)

    conf = $ts.dut.call("lan9662_rte_ob_rtp_conf_get", $rtp_id)
    conf["type"] = "LAN9662_RTP_TYPE_PN"
    $ts.dut.call("lan9662_rte_ob_rtp_conf_set", $rtp_id, conf)

    conf = $ts.dut.call("lan9662_rte_ob_rtp_pdu2dg_init")
    conf["pdu_offset"] = 1
    $ts.dut.call("lan9662_rte_ob_rtp_pdu2dg_add", $rtp_id, conf)

    cmd = "eth dmac 2 et 0x8892 data pattern cnt 46"
    tx_cnt = 3
    for i in 0..(tx_cnt - 1)
        run_ef_tx_rx_cmd($ts, $idx_tx, [], cmd)
    end
    cnt = $ts.dut.call("lan9662_rte_ob_rtp_counters_get", $rtp_id)
    name = "rx_#{sub_id}"
    check_counter(name, cnt[name], tx_cnt)
    $rtp_id = ($rtp_id + 1)
end

test "rx-counter" do
    rx_cnt_test(0)
    rx_cnt_test(1)
end

test "dump" do
    #$ts.dut.run("lan9662-rte-cmd debug api")
end
