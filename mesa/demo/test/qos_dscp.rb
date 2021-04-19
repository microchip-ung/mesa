#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_2x")

$dpl_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_DPL_CNT")
t_i("$dpl_cnt: #{$dpl_cnt}  ")

idx_list = port_idx_shuffle($ts)
$igr_port = idx_list[0]
$egr_port = idx_list[1]
t_i("$igr_port: #{$igr_port}  $egr_port: #{$egr_port}")

MESA_VID_NULL = 0

$cos_conf_restore = $ts.dut.call("mesa_qos_conf_get")
$igr_qconf_restore = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$igr_port])
$igr_qdconf_restore = $ts.dut.call("mesa_qos_dpl_conf_get", $dpl_cnt)
$egr_qconf_restore = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$egr_port])
$egr_pdconf_restore = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[$egr_port], $dpl_cnt)
$egr_vconf_restore = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[$egr_port])
$egr_ddconf_restore = $ts.dut.call("mesa_qos_dscp_dpl_conf_get", $dpl_cnt)


t_i ("Configure egress port to C tag all")
vconf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.p[$egr_port])
vconf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
vconf["untagged_vid"] = MESA_VID_NULL
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[$egr_port], vconf)

t_i("Configure egress prio and dpl mapping to 1:1")
dconf = $ts.dut.call("mesa_qos_port_dpl_conf_get", $ts.dut.p[$egr_port], $dpl_cnt)
dconf[0]["pcp"] = [0,1,2,3,4,5,6,7]
dconf[0]["dei"] = [0,0,0,0,0,0,0,0]
dconf[1]["pcp"] = [0,1,2,3,4,5,6,7]
dconf[1]["dei"] = [1,1,1,1,1,1,1,1]
$ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[$egr_port], $dpl_cnt, dconf)

t_i("Configure egress prio and dpl tagging to mapped.")
qconf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$egr_port])
qconf["tag"]["remark_mode"] = "MESA_TAG_REMARK_MODE_MAPPED"
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], qconf)

def send_dhcp(translate, pcp, dei)
    test "send_dhcp" do

    txframe = "eth dmac ff:ff:ff:ff:ff:ff smac 00:00:00:00:00:0a ipv4 dscp "

    t_i("Send DSCP 0")
    rxframe = "eth dmac ff:ff:ff:ff:ff:ff smac 00:00:00:00:00:0a ctag vid 1 pcp #{pcp[0]} dei #{dei[0]} ipv4 dscp #{translate[0]}"
    $ts.pc.run("sudo ef tx #{$ts.pc.p[$igr_port]} #{txframe} 0 data pattern cnt 40 rx #{$ts.pc.p[$egr_port]} #{rxframe} data pattern cnt 40")

    t_i("Send DSCP 32")
    rxframe = "eth dmac ff:ff:ff:ff:ff:ff smac 00:00:00:00:00:0a ctag vid 1 pcp #{pcp[1]} dei #{dei[1]} ipv4 dscp #{translate[1]}"
    $ts.pc.run("sudo ef tx #{$ts.pc.p[$igr_port]} #{txframe} 32  data pattern cnt 40 rx #{$ts.pc.p[$egr_port]} #{rxframe} data pattern cnt 40")

    t_i("Send DSCP 63")
    rxframe = "eth dmac ff:ff:ff:ff:ff:ff smac 00:00:00:00:00:0a ctag vid 1 pcp #{pcp[2]} dei #{dei[2]} ipv4 dscp #{translate[2]}"
    $ts.pc.run("sudo ef tx #{$ts.pc.p[$igr_port]} #{txframe} 63 data pattern cnt 40 rx #{$ts.pc.p[$egr_port]} #{rxframe} data pattern cnt 40")

    end
end

def check_queue_counters(queues, counters)
    test "Check QoS counters" do

    icounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[$igr_port])
    ecounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.p[$egr_port])

    queues.each_with_index do |q_value, q_idx|
        if ((icounters["prio"][q_value]["rx"] != counters[q_idx]) || (ecounters["prio"][q_value]["tx"] != counters[q_idx]))
            t_e("ingress/egress counters not as expected. queue #{q_value} rx green #{icounters["prio"][q_value]["rx"]}   tx green #{ecounters["prio"][q_value]["tx"]}  expected #{counters[q_idx]}")
        end
        if ($cap_cnt_evc)
            t_i("Check colour counter")
            if ($cap_cnt_evc && (icounters["prio"][q_value]["rx_green"] != counters[q_idx]) || (ecounters["prio"][q_value]["rx_green"] != counters[q_idx]))
                t_e("ingress/egress counters not as expected. queue #{q_value}  rx green #{icounters["prio"][q_value]["rx_green"]}   tx green #{ecounters["prio"][q_value]["rx_green"]}  expected #{counters[q_idx]}")
            end
        end
    end

    end
end

def pscp_translate_test_func
    test "pscp_translate_test_func" do

    t_i("Configure DSCP translation table")
    cos_conf = $ts.dut.call("mesa_qos_conf_get")
    dscp = cos_conf["dscp"]
    dscp[0]["dscp"] = 1
    dscp[32]["dscp"] = 33
    dscp[63]["dscp"] = 0
    $ts.dut.call("mesa_qos_conf_set", cos_conf)

    igr_conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$igr_port])
    egr_conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$egr_port])

    test "Test no translation - no analyser update - no rewriter update" do
        igr_conf["dscp"]["translate"] = false
        igr_conf["dscp"]["mode"] = "MESA_DSCP_MODE_NONE"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)

        egr_conf["dscp"]["emode"] = "MESA_DSCP_EMODE_DISABLE"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], egr_conf)

        send_dhcp([0,32,63], [0,0,0], [0,0,0])
    end

    test "Test translation - no analyser update - no rewriter update" do
        igr_conf["dscp"]["translate"] = true
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)

        send_dhcp([0,32,63], [0,0,0], [0,0,0])
    end

    test "Test translation - no analyser update - rewriter update" do
        egr_conf["dscp"]["emode"] = "MESA_DSCP_EMODE_REMARK"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], egr_conf)

        send_dhcp([1,33,0], [0,0,0], [0,0,0])
    end

    end
end

def pscp_qos_dpl_test_func
    test "pscp_qos_dpl_test_func" do

    igr_conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$igr_port])
    egr_conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$egr_port])

    test "Test no translation - no queue mapping - no rewriter update" do
        $ts.dut.run("mesa-cmd port statis clear")

        igr_conf["dscp"]["translate"] = false
        igr_conf["dscp"]["mode"] = "MESA_DSCP_MODE_NONE"
        igr_conf["dscp"]["class_enable"] = false
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)

        egr_conf["dscp"]["emode"] = "MESA_DSCP_EMODE_DISABLE"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], egr_conf)

        send_dhcp([0,32,63], [0,0,0], [0,0,0])
        check_queue_counters([0], [3])
    end

    test "Test DSCP to queue and DPL mapping" do
        $ts.dut.run("mesa-cmd port statis clear")

        igr_conf["dscp"]["class_enable"] = true
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)

        t_i("Configure DSCP queue mapping table")
        cos_conf = $ts.dut.call("mesa_qos_conf_get")
        dscp = cos_conf["dscp"]
        dscp[0]["trust"] = true
        dscp[0]["prio"] = 1
        dscp[0]["dpl"] = 0
        dscp[32]["trust"] = false
        dscp[32]["prio"] = 2
        dscp[32]["dpl"] = 1
        dscp[63]["trust"] = true
        dscp[63]["prio"] = 3
        dscp[63]["dpl"] = 1
        $ts.dut.call("mesa_qos_conf_set", cos_conf)

        send_dhcp([0,32,63], [1,0,3], [0,0,1])
        check_queue_counters([0,1,3], [1,1,1])
    end

    end
end

def qos_dpl_pscp_test_func
    test "qos_dpl_pscp_test_func" do

    igr_conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$igr_port])
    egr_conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$egr_port])

    test "Test no translation - no queue mapping - no rewriter update" do
        $ts.dut.run("mesa-cmd port statis clear")

        igr_conf["dscp"]["translate"] = false
        igr_conf["dscp"]["mode"] = "MESA_DSCP_MODE_NONE"
        igr_conf["dscp"]["class_enable"] = false
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)

        egr_conf["dscp"]["emode"] = "MESA_DSCP_EMODE_DISABLE"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], egr_conf)

        send_dhcp([0,32,63], [0,0,0], [0,0,0])
        check_queue_counters([0], [3])
    end

    test "Test queue and DPL mapping to DSCP for all" do
        $ts.dut.run("mesa-cmd port statis clear")

        igr_conf["dscp"]["class_enable"] = true
        igr_conf["dscp"]["mode"] = "MESA_DSCP_MODE_ALL"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)

        t_i("Configure DSCP to queue and DPL mapping table")
        cos_conf = $ts.dut.call("mesa_qos_conf_get")
        dscp = cos_conf["dscp"]
        dscp[0]["trust"] = true
        dscp[0]["prio"] = 1
        dscp[0]["dpl"] = 0
        dscp[32]["trust"] = false
        dscp[32]["prio"] = 2
        dscp[32]["dpl"] = 1
        dscp[63]["trust"] = true
        dscp[63]["prio"] = 3
        dscp[63]["dpl"] = 1
        $ts.dut.call("mesa_qos_conf_set", cos_conf)

        t_i("Configure queue and DPL to DSCP mapping table")
        cos_conf = $ts.dut.call("mesa_qos_dpl_conf_get", $dpl_cnt)
        cos_conf[0]["dscp"][0] = 11
        cos_conf[1]["dscp"][0] = 22
        cos_conf[0]["dscp"][1] = 33
        cos_conf[1]["dscp"][1] = 44
        cos_conf[0]["dscp"][3] = 55
        cos_conf[1]["dscp"][3] = 66
        $ts.dut.call("mesa_qos_dpl_conf_set", $dpl_cnt, cos_conf)

        egr_conf["dscp"]["emode"] = "MESA_DSCP_EMODE_REMARK"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], egr_conf)

       #send_dhcp(translate,  pcp,     dei)
        send_dhcp([33,11,66], [1,0,3], [0,0,1])
        check_queue_counters([0,1,3], [1,1,1])
    end

    test "Test queue and DPL mapping to DSCP for selected" do
        $ts.dut.run("mesa-cmd port statis clear")

        igr_conf["dscp"]["class_enable"] = true
        igr_conf["dscp"]["mode"] = "MESA_DSCP_MODE_SEL"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)

        t_i("Configure DSCP to queue and DPL mapping table")
        cos_conf = $ts.dut.call("mesa_qos_conf_get")
        dscp = cos_conf["dscp"]
        dscp[0]["trust"] = true
        dscp[0]["remark"] = true
        dscp[0]["prio"] = 1
        dscp[0]["dpl"] = 0
        dscp[32]["trust"] = false
        dscp[32]["remark"] = true
        dscp[32]["prio"] = 2
        dscp[32]["dpl"] = 1
        dscp[63]["trust"] = true
        dscp[63]["remark"] = false
        dscp[63]["prio"] = 3
        dscp[63]["dpl"] = 1
        $ts.dut.call("mesa_qos_conf_set", cos_conf)

        t_i("Configure queue and DPL to DSCP mapping table")
        cos_conf = $ts.dut.call("mesa_qos_dpl_conf_get", $dpl_cnt)
        cos_conf[0]["dscp"][0] = 11
        cos_conf[1]["dscp"][0] = 22
        cos_conf[0]["dscp"][1] = 33
        cos_conf[1]["dscp"][1] = 44
        cos_conf[0]["dscp"][3] = 55
        cos_conf[1]["dscp"][3] = 66
        $ts.dut.call("mesa_qos_dpl_conf_set", $dpl_cnt, cos_conf)

        egr_conf["dscp"]["emode"] = "MESA_DSCP_EMODE_REMARK"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], egr_conf)

       #send_dhcp(translate,  pcp,     dei)
        send_dhcp([33,11,63], [1,0,3], [0,0,1])
        check_queue_counters([0,1,3], [1,1,1])
    end

    end
end


def pscp_dpl_pscp_test_func
    test "pscp_dpl_pscp_test_func" do

    igr_conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$igr_port])
    egr_conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[$egr_port])

#    test "Test no translation - no queue mapping - no rewriter update" do
#        $ts.dut.run("mesa-cmd port statis clear")
#
#        igr_conf["dscp"]["translate"] = false
#        igr_conf["dscp"]["mode"] = "MESA_DSCP_MODE_NONE"
#        igr_conf["dscp"]["class_enable"] = false
#        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)
#
#        egr_conf["dscp"]["emode"] = "MESA_DSCP_EMODE_DISABLE"
#        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], egr_conf)
#
#        send_dhcp([0,32,63], [0,0,0], [0,0,0])
#        check_queue_counters([0], [3])
#    end

    test "Test DSCP and DPL mapping to DSCP" do
        $ts.dut.run("mesa-cmd port statis clear")

        igr_conf["dscp"]["class_enable"] = false
        igr_conf["dscp"]["mode"] = "MESA_DSCP_MODE_NONE"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], igr_conf)

        conf = $ts.dut.call("mesa_qos_dscp_dpl_conf_get", $dpl_cnt)
        conf[0][0]["dscp"] = 12
        conf[32][0]["dscp"] = 34
        conf[63][0]["dscp"] = 56
        $ts.dut.call("mesa_qos_dscp_dpl_conf_set", $dpl_cnt, conf)

        egr_conf["dscp"]["emode"] = "MESA_DSCP_EMODE_REMAP"
        $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], egr_conf)

       #send_dhcp(translate,  pcp,     dei)
        send_dhcp([12,34,56], [0,0,0], [0,0,0])
        check_queue_counters([0], [3])
    end

    end
end


test "test_run" do
#    pscp_translate_test_func
#    pscp_qos_dpl_test_func
#    qos_dpl_pscp_test_func
    pscp_dpl_pscp_test_func
end

t_i("Clean up")
$ts.dut.call("mesa_qos_conf_set", $cos_conf_restore)
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$igr_port], $igr_qconf_restore)
$ts.dut.call("mesa_qos_dpl_conf_set", $dpl_cnt, $igr_qdconf_restore)
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[$egr_port], $egr_qconf_restore)
$ts.dut.call("mesa_qos_port_dpl_conf_set", $ts.dut.p[$egr_port], $dpl_cnt, $egr_pdconf_restore)
$ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.p[$egr_port], $egr_vconf_restore)
$ts.dut.call("mesa_qos_dscp_dpl_conf_set", $dpl_cnt, $egr_ddconf_restore)
