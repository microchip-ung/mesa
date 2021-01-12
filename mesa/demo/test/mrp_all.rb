#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

#require 'pry'
#require_relative 'lib/api_test'
require_relative 'libeasy/et'
require_relative 'oam_lib'

#---------- Configuration -----------------------------------------------------

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_mrp = ($ts.dut.call("mesa_capability", "MESA_CAP_MRP") != 0) ? true : false
    $cap_mrp_cnt = ($ts.dut.call("mesa_capability", "MESA_CAP_MRP_CNT") != 0) ? true : false
    $cap_cosid = ($ts.dut.call("mesa_capability", "MESA_CAP_QOS_COSID_CLASSIFICATION") != 0) ? true : false
    $cap_vstax = ($ts.dut.call("mesa_capability", "MESA_CAP_PACKET_VSTAX") != 0) ? true : false
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    $cap_tx_ifh_size = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_TX_IFH_SIZE")
    $cap_port_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    t_i("cap_mrp #{$cap_mrp}  cap_mrp_cnt #{$cap_mrp_cnt}  cap_cosid #{$cap_cosid}  cap_vstax #{$cap_vstax}  $cap_epid #{$cap_epid}  $cap_family #{$cap_family}  cap_tx_ifh_size #{$cap_tx_ifh_size}  cap_port_cnt #{$cap_port_cnt}")
end

$ring_port0 = 0
$ring_port1 = 1
$data_port = 2
$data_vid  = 200
$cpu_queue = 7
$pvid = 1

$port0    = $ring_port0
$port1    = $ring_port1
$port2    = $data_port
$npi_port  = 3

$port_map = $ts.dut.call("mesa_port_map_get", $cap_port_cnt)

MESA_MRP_EVENT_MASK_TST_LOC = 0x02


#---------- Frame testing -----------------------------------------------------

#---------- Test execution ----------------------------------------------------

#binding.pry

def mrc_rx_func(port)
    primary = (port == $ring_port0) ? true : false

    test "mrc_rx_func port #{port}" do
    t_i("Set ring role to MRC")
    $ts.dut.call("mesa_mrp_ring_role_set", 0, "MESA_MRP_RING_ROLE_MRC")

    t_i("Create MC_Test frame")
    frame = frame_create(MC_TEST, SC_STRING, 0, 0, "mrp")
    rx_ifh = rx_ifh_create(IGNORE, $ts.dut.port_list[port])

    test "Transmit TST frame on ring port to see no block. Ring role is MRC" do
    frametx = frame.dup + "mrp_tst c_seq_num 1 "
    primary ? frame_tx(frametx, port, "", frametx, "", "") :  frame_tx(frametx, port, frametx, "", "", "")
    end

    test "Check status and counters" do
    status = $ts.dut.call("mesa_mrp_status_get", 0)
    counters = $ts.dut.call("mesa_mrp_counters_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    counters = primary ? counters["p_counters"] : counters["s_counters"]
    if (status["tst_loc"] == true)
        t_e("Unexpected tst_loc #{status["tst_loc"]}")
    end
    if (status["mrp_seen"] == false)
        t_e("Unexpected mrp_seen #{status["mrp_seen"]}")
    end
    if (status["mrp_proc_seen"] == false)
        t_e("Unexpected mrp_proc_seen #{status["mrp_proc_seen"]}")
    end
    if (counters["tst_rx_count"] != 0)
        t_e("Unexpected tst_rx_count #{counters["tst_rx_count"]}")
    end
    end

    test "Transmit Propagate frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_prop_nack "
    primary ? frame_tx(frametx, port, "", frametx, "", rx_ifh + frametx) :  frame_tx(frametx, port, frametx, "", "", rx_ifh + frametx)
    end

    test "Transmit MgrNAck frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_prop_nack t_s_type 1 "
    primary ? frame_tx(frametx, port, "", frametx, "", rx_ifh + frametx) :  frame_tx(frametx, port, frametx, "", "", rx_ifh + frametx)
    end

    test "Check that so far no invalid MAC is seen" do
    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["dmac_err_seen"] == true)
        t_e("Unexpected dmac_err_seen #{status["dmac_err_seen"]}")
    end
    end

    test "Transmit invalid Version TST frame on ring port to see invalid Version seen" do
    frametx = frame.dup + "mrp_tst c_seq_num 5 version 2 "
    primary ? frame_tx(frametx, port, "", frametx, "", "") :  frame_tx(frametx, port, frametx, "", "", "")

    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["vers_err_seen"] == false)
        t_e("Unexpected vers_err_seen #{status["vers_err_seen"]}")
    end
    end

    test "Transmit invalid Sequence TST frame on ring port to see invalid Sequence seen" do
    frametx = frame.dup + "mrp_tst c_seq_num 5 "
    primary ? frame_tx(frametx, port, "", frametx, "", "") :  frame_tx(frametx, port, frametx, "", "", "")

    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["seq_err_seen"] == false)
        t_e("Unexpected seq_err_seen #{status["seq_err_seen"]}")
    end
    end

    t_i("Create MC_Control frame")
    frame = frame_create(MC_CONTROL, SC_STRING, 0, 0, "mrp")

    test "Transmit Topology frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_topo "
    primary ? frame_tx(frametx, port, "", frametx, "", rx_ifh + frametx) :  frame_tx(frametx, port, frametx, "", "", rx_ifh + frametx)
    end

    test "Transmit LinkChange LinkDown frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_lnk "
    primary ? frame_tx(frametx, port, "", frametx, "", rx_ifh + frametx) :  frame_tx(frametx, port, frametx, "", "", rx_ifh + frametx)
    end

    test "Transmit LinkChange LinkUp frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_lnk t_type 5 "
    primary ? frame_tx(frametx, port, "", frametx, "", rx_ifh + frametx) :  frame_tx(frametx, port, frametx, "", "", rx_ifh + frametx)
    end

    test "Transmit invalid MAC (MC_CONTROL) TST frame on ring port to see invalid MAC seen" do
    frametx = frame.dup + "mrp_tst c_seq_num 6 "
    primary ? frame_tx(frametx, port, "", frametx, "", "") :  frame_tx(frametx, port, frametx, "", "", "")

    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["dmac_err_seen"] == false)
        t_e("Unexpected dmac_err_seen #{status["dmac_err_seen"]}")
    end
    end

    t_i("Clear counters")
    $ts.dut.call("mesa_mrp_counters_clear", 0)

    t_i("Set ring role to DISABLED")
    $ts.dut.call("mesa_mrp_ring_role_set", 0, "MESA_MRP_RING_ROLE_DISABLED")
    end
end

def mrm_rx_func(port)
    primary = (port == $ring_port0) ? true : false

    test "mrm_rx_func port #{port}" do
    t_i("Create MC_Test frame")
    frame = frame_create(MC_TEST, SC_STRING, 0, 0, "mrp")
    rx_ifh = rx_ifh_create(IGNORE, $ts.dut.port_list[port])

    test "Transmit TST frame on ring port to see no block. Ring role is disabled" do
    frametx = frame.dup + "mrp_tst c_seq_num 1 "
    primary ? frame_tx(frametx, port, "", frametx, "", "") :  frame_tx(frametx, port, frametx, "", "", "")
    end

    role = $ts.dut.call("mesa_mrp_ring_role_get", 0)
    if (role != "MESA_MRP_RING_ROLE_DISABLED")
        t_e("Unexpected ring role #{role}")
    end

    t_i("Set ring role to MRM")
    $ts.dut.call("mesa_mrp_ring_role_set", 0, "MESA_MRP_RING_ROLE_MRM")

    sleep 2

    test "Check LOC active" do
    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] :  status["s_status"]
    if (status["tst_loc"] != true)
        t_e("Unexpected tst_loc #{status["tst_loc"]}")
    end
    end

    test "Check LOC event without event enabled" do
    event = $ts.dut.call("mesa_mrp_event_get", 0)
    if ((event["p_mask"] != 0) || (event["s_mask"] != 0))
        t_e("Unexpected event p_mask #{event["p_mask"]} s_mask #{event["s_mask"]}")
    end
    end

    t_i("Enable LOC event")
    $ts.dut.call("mesa_mrp_event_mask_set", 0, MESA_MRP_EVENT_MASK_TST_LOC, true)
    mask = $ts.dut.call("mesa_mrp_event_mask_get", 0)
    if (mask != MESA_MRP_EVENT_MASK_TST_LOC)
        t_e("Unexpected event mask #{mask}")
    end

    test "Check LOC event LOC active" do
    event = $ts.dut.call("mesa_mrp_event_get", 0)
    if ((event["p_mask"] != MESA_MRP_EVENT_MASK_TST_LOC) || (event["s_mask"] != MESA_MRP_EVENT_MASK_TST_LOC))
        t_f("Unexpected event p_mask #{event["p_mask"]} s_mask #{event["s_mask"]}")
    end
    end

    test "Transmit TST frame on ring port to see block" do
    frametx = frame.dup + "mrp_tst c_seq_num 2 "
    frame_tx(frametx, port, "", "", "", "")
    end

    test "Check status and counters" do
    status = $ts.dut.call("mesa_mrp_status_get", 0)
    counters = $ts.dut.call("mesa_mrp_counters_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    counters = primary ? counters["p_counters"] : counters["s_counters"]
    if (status["tst_loc"] == true)
        t_e("Unexpected tst_loc #{status["tst_loc"]}")
    end
    if (status["mrp_seen"] == false)
        t_e("Unexpected mrp_seen #{status["mrp_seen"]}")
    end
    if (status["mrp_proc_seen"] == false)
        t_e("Unexpected mrp_proc_seen #{status["mrp_proc_seen"]}")
    end
    if (counters["tst_rx_count"] != 1)
        t_e("Unexpected tst_rx_count #{counters["tst_rx_count"]}")
    end
    end

    test "Check counter clear" do
    $ts.dut.call("mesa_mrp_counters_clear", 0)
    counters = $ts.dut.call("mesa_mrp_counters_get", 0)
    counters = primary ? counters["p_counters"] : counters["s_counters"]
    if (counters["tst_rx_count"] != 0)
        t_e("Unexpected tst_rx_count #{counters["tst_rx_count"]}")
    end
    end

    test "Check LOC event when LOC clear" do
    event = $ts.dut.call("mesa_mrp_event_get", 0)
    event = primary ? event["p_mask"] : event["s_mask"]
    if (event != MESA_MRP_EVENT_MASK_TST_LOC)
        t_e("Unexpected event mask #{event}")
    end
    end

    sleep 2

    test "Check LOC active" do
    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["tst_loc"] != true)
        t_e("Unexpected tst_loc #{status["tst_loc"]}")
    end
    end

    test "Check LOC event when LOC set" do
    event = $ts.dut.call("mesa_mrp_event_get", 0)
    event = primary ? event["p_mask"] : event["s_mask"]
    if (event != MESA_MRP_EVENT_MASK_TST_LOC)
        t_e("Unexpected event mask #{event}")
    end
    end

    test "Check LOC event clear after get" do
    event = $ts.dut.call("mesa_mrp_event_get", 0)
    event = primary ? event["p_mask"] : event["s_mask"]
    if (event != 0)
        t_e("Unexpected event mask #{event}")
    end
    end

    copy = $ts.dut.call("mesa_mrp_copy_tst_get", 0)
    copy["tst_clear_loc"] = true
    $ts.dut.call("mesa_mrp_copy_tst_set", 0, copy)

    test "Transmit TST frame on ring port to see clear LOC copy to CPU" do
    frametx = frame.dup + "mrp_tst c_seq_num 3 "
    frame_tx(frametx, port, "", "", "", rx_ifh + frametx)
    end

    test "Transmit TST frame on ring port to see NO copy to CPU" do
    frametx = frame.dup + "mrp_tst c_seq_num 4 "
    frame_tx(frametx, port, "", "", "", "")
    end

    test "Transmit Propagate frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_prop_nack "
    frame_tx(frametx, port, "", "", "", rx_ifh + frametx)
    end

    test "Transmit MgrNAck frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_prop_nack t_s_type 1 "
    frame_tx(frametx, port, "", "", "", rx_ifh + frametx)
    end

    test "Check that so far no invalid MAC is seen" do
    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["dmac_err_seen"] == true)
        t_e("Unexpected dmac_err_seen #{status["dmac_err_seen"]}")
    end
    end

    test "Transmit invalid Version TST frame on ring port to see invalid Version seen" do
    frametx = frame.dup + "mrp_tst c_seq_num 5 version 2 "
    frame_tx(frametx, port, "", "", "", "")

    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["vers_err_seen"] == false)
        t_e("Unexpected vers_err_seen #{status["vers_err_seen"]}")
    end
    end

    test "Transmit invalid Sequence TST frame on ring port to see invalid Sequence seen" do
    frametx = frame.dup + "mrp_tst c_seq_num 5 "
    frame_tx(frametx, port, "", "", "", "")

    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["vers_err_seen"] == true)
        t_e("Unexpected vers_err_seen #{status["vers_err_seen"]}")
    end
    if (status["seq_err_seen"] == false)
        t_e("Unexpected seq_err_seen #{status["seq_err_seen"]}")
    end
    end

    t_i("Create MC_Control frame")
    frame = frame_create(MC_CONTROL, SC_STRING, 0, 0, "mrp")

    test "Transmit Topology frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_topo "
    frame_tx(frametx, port, "", "", "", rx_ifh + frametx)
    end

    test "Transmit LinkChange LinkDown frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_lnk "
    frame_tx(frametx, port, "", "", "", rx_ifh + frametx)
    end

    test "Transmit LinkChange LinkUp frame on ring port to see copy to CPU" do
    frametx = frame.dup + "mrp_lnk t_type 5 "
    frame_tx(frametx, port, "", "", "", rx_ifh + frametx)
    end

    test "Transmit invalid MAC (MC_CONTROL) TST frame on ring port to see invalid MAC seen" do
    frametx = frame.dup + "mrp_tst c_seq_num 6 "
    frame_tx(frametx, port, "", "", "", "")

    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["seq_err_seen"] == true)
        t_e("Unexpected seq_err_seen #{status["seq_err_seen"]}")
    end
    if (status["dmac_err_seen"] == false)
        t_e("Unexpected dmac_err_seen #{status["dmac_err_seen"]}")
    end
    end

    t_i("Check dmac_err_seen clear")
    status = $ts.dut.call("mesa_mrp_status_get", 0)
    status = primary ? status["p_status"] : status["s_status"]
    if (status["dmac_err_seen"] == true)
        t_e("Unexpected dmac_err_seen #{status["dmac_err_seen"]}")
    end

    t_i("Clear counters")
    $ts.dut.call("mesa_mrp_counters_clear", 0)

    t_i("Copy to CPU disable")
    copy["tst_clear_loc"] = false
    $ts.dut.call("mesa_mrp_copy_tst_set", 0, copy)

    t_i("Clear events")
    event = $ts.dut.call("mesa_mrp_event_get", 0)

    t_i("Disable LOC event")
    $ts.dut.call("mesa_mrp_event_mask_set", 0, MESA_MRP_EVENT_MASK_TST_LOC, false)

    t_i("Set ring role to DISABLED")
    $ts.dut.call("mesa_mrp_ring_role_set", 0, "MESA_MRP_RING_ROLE_DISABLED")
    end
end

def mrm_tx_func(port)
    primary = (port == $ring_port0) ? true : false

    test "mrm_tx_func port #{port}" do
    t_i("Set ring role to MRM")
    $ts.dut.call("mesa_mrp_ring_role_set", 0, "MESA_MRP_RING_ROLE_MRM")

    t_i("Create MC_Test frame")
    frame = frame_create(MC_TEST, SC_STRING, 0, 0, "mrp")
    tx_ifh = tx_ifh_create(0, $ts.dut.port_list[port], "MESA_PACKET_OAM_TYPE_MRP_TST")

    test "Inject TST frame to see sequence number incremented" do
    tst_pdutx = "mrp_tst "
    frametx = tx_ifh + frame.dup + tst_pdutx.dup

    tst_pdurx = "mrp_tst ign c_seq_num 0 "
    framerx = frame.dup + tst_pdurx.dup
    primary ? frame_tx(frametx, $npi_port, framerx, "", "", "") :  frame_tx(frametx, $npi_port, "", framerx, "", "")

    tst_pdurx = "mrp_tst ign c_seq_num 1 "
    framerx = frame.dup + tst_pdurx.dup
    primary ? frame_tx(frametx, $npi_port, framerx, "", "", "") :  frame_tx(frametx, $npi_port, "", framerx, "", "")

    tst_pdurx = "mrp_tst ign c_seq_num 2 "
    framerx = frame.dup + tst_pdurx.dup
    primary ? frame_tx(frametx, $npi_port, framerx, "", "", "") :  frame_tx(frametx, $npi_port, "", framerx, "", "")
    end

    test "Inject TST frame to see Port Role inserted" do
    tst_pdutx = "mrp_tst "
    frametx = tx_ifh + frame.dup + tst_pdutx.dup
    tst_pdurx_p = "mrp_tst ign t_role 0 " # Primary port
    tst_pdurx_s = "mrp_tst ign t_role 1 " # Secondary port

    framerx = frame.dup + (primary ? tst_pdurx_p.dup : tst_pdurx_s.dup)
    primary ? frame_tx(frametx, $npi_port, framerx, "", "", "") :  frame_tx(frametx, $npi_port, "", framerx, "", "")

    t_i("Change port roles")
    ports = $ts.dut.call("mesa_mrp_ports_get", 0)
    ports["p_port"] = $ts.dut.port_list[$ring_port1]
    ports["s_port"] = $ts.dut.port_list[$ring_port0]
    $ts.dut.call("mesa_mrp_ports_set", 0, ports)

    framerx = frame.dup + (primary ? tst_pdurx_s.dup : tst_pdurx_p.dup)
    primary ? frame_tx(frametx, $npi_port, framerx, "", "", "") :  frame_tx(frametx, $npi_port, "", framerx, "", "")

    t_i("Change port roles back")
    ports = $ts.dut.call("mesa_mrp_ports_get", 0)
    ports["p_port"] = $ts.dut.port_list[$ring_port0]
    ports["s_port"] = $ts.dut.port_list[$ring_port1]
    $ts.dut.call("mesa_mrp_ports_set", 0, ports)
    end

    test "Inject TST frame to see Ring State inserted" do
    tst_pdutx = "mrp_tst "
    frametx = tx_ifh + frame.dup + tst_pdutx.dup

    tst_pdurx = "mrp_tst ign t_state 0 " # Ring Open
    framerx = frame.dup + tst_pdurx.dup
    primary ? frame_tx(frametx, $npi_port, framerx, "", "", "") :  frame_tx(frametx, $npi_port, "", framerx, "", "")

    t_i("Change Ring State")
    $ts.dut.call("mesa_mrp_ring_state_set", 0, "MESA_MRP_RING_STATE_CLOSED")

    tst_pdurx = "mrp_tst ign t_state 1 " # Ring Closed
    framerx = frame.dup + tst_pdurx.dup
    primary ? frame_tx(frametx, $npi_port, framerx, "", "", "") :  frame_tx(frametx, $npi_port, "", framerx, "", "")

    t_i("Change Ring State back")
    $ts.dut.call("mesa_mrp_ring_state_set", 0, "MESA_MRP_RING_STATE_OPEN")
    end

    t_i("Set ring role to DISABLED")
    $ts.dut.call("mesa_mrp_ring_role_set", 0, "MESA_MRP_RING_ROLE_DISABLED")
    end
end

#$ts.dut.run("mesa-cmd deb api ail mrp act 2")
#$ts.dut.run("mesa-cmd deb api cil mrp act 2")
#$ts.dut.run("mesa-cmd mac dump")
#    $ts.dut.run("mesa-cmd deb api ail mrp")
#    $ts.dut.run("mesa-cmd deb api cil mrp")

test "test_config" do
    # Flush MAC table
    $ts.dut.call("mesa_mac_table_flush")

    # CPU queue configuration
    $packet_rx_conf_restore = $ts.dut.call("mesa_packet_rx_conf_get")
    conf = $packet_rx_conf_restore.dup
    conf["queue"][$cpu_queue]["npi"]["enable"] = true
    $ts.dut.call("mesa_packet_rx_conf_set", conf)

    # NPI port configuration
    $npi_conf_restore = $ts.dut.call("mesa_npi_conf_get")
    conf = $npi_conf_restore.dup
    conf["enable"] = true
    conf["port_no"] = $ts.dut.port_list[$npi_port]
    $ts.dut.call("mesa_npi_conf_set", conf)

    # Set VLAN port configuration
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$ring_port0])
    $vlan_port_conf_restore0 = conf.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$ring_port0], conf)

    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$ring_port1])
    $vlan_port_conf_restore1 = conf.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$ring_port1], conf)

    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$data_port])
    $vlan_port_conf_restore2 = conf.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$data_port], conf)

    port_list = "#{$ts.dut.port_list[$ring_port0]},#{$ts.dut.port_list[$ring_port1]},#{$ts.dut.port_list[$data_port]}"
    $ts.dut.call("mesa_vlan_port_members_set", $data_vid, port_list) #Enable forwarding of data frames on data VID
    port_list = "#{$ts.dut.port_list[$ring_port0]},#{$ts.dut.port_list[$ring_port1]}"
    $ts.dut.call("mesa_vlan_port_members_set", 1, port_list)   #Enable forwarding of MRP frames on PVID

    vop_config($cpu_queue)

    conf = $ts.dut.call("mesa_mrp_get", 0)
    conf["p_port"] = $ts.dut.port_list[$ring_port0]
    conf["s_port"] = $ts.dut.port_list[$ring_port1]
    $ts.dut.call("mesa_mrp_add", 0, conf)

    loc = $ts.dut.call("mesa_mrp_tst_loc_get", 0)
    loc["tst_interval"] = 333333
    loc["tst_mon_count"] = 3
    $ts.dut.call("mesa_mrp_tst_loc_set", 0, loc)
end

test "test_run" do
    mrm_rx_func($ring_port0)
    mrm_rx_func($ring_port1)

    mrc_rx_func($ring_port0)
    mrc_rx_func($ring_port1)

    mrm_tx_func($ring_port0)
    mrm_tx_func($ring_port1)
end

test "test_clean_up" do
    # VLAN port configuration restore
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$ring_port0], $vlan_port_conf_restore0)
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$ring_port1], $vlan_port_conf_restore1)

    # Clear VLAN memberships
    $ts.dut.call("mesa_vlan_port_members_set", $data_vid, "")

    # CPU queue configuration restore
    $ts.dut.call("mesa_packet_rx_conf_set", $packet_rx_conf_restore)

    # NPI port configuration restore
    $ts.dut.call("mesa_npi_conf_set", $npi_conf_restore)

    $ts.dut.call("mesa_mrp_del", 0)
end
