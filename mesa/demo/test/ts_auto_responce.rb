#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

DEFAULT_PORT_ID_PORT = 0x9ABC

$port0 = 0
$port1 = 1
$npi_port = 3
$acl_id = 1
$requestClockId = 0xAABBCCDDEEFFAABB
$requestPortNumber = 0xABCD

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")) ||
           ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5) or #{chip_family_to_id("MESA_CHIP_FAMILY_LAN969X")} (Lan969x)")
    $cap_auto_resp = $ts.dut.call("mesa_capability", "MESA_CAP_TS_DELAY_REQ_AUTO_RESP")
    assert($cap_auto_resp, "The Auto Response capability must be defined")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
end

def tod_auto_responce_test(domain)
    test "tod_auto_responce_test  domain = #{domain}" do

    # Port PTP domain configuration
    conf = $ts.dut.call("mesa_ts_operation_mode_get", $ts.dut.port_list[$port0])
    conf["domain"] = domain
    $ts.dut.call("mesa_ts_operation_mode_set", $ts.dut.port_list[$port0], conf)

    test "Create IS2 to automatic Delay Response" do
    $ace_conf = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ETYPE")
    $ace_conf["id"] = $acl_id
    $ace_conf["port_list"] = "#{$ts.dut.port_list[$port0]}"
    $action = $ace_conf["action"]
    $action["port_action"] = "MESA_ACL_PORT_ACTION_REDIR"
    $action["port_list"] = "#{$ts.dut.port_list[$port0]}"
    $action["ptp_action"] = "MESA_ACL_PTP_ACTION_ONE_STEP"
    $action["ptp"]["response"] = "MESA_ACL_PTP_RSP_DLY_REQ_RSP_TS_UPD"
    $action["ptp"]["copy_smac_to_dmac"] = false
    $action["ptp"]["set_smac_to_port_mac"] = false
    $action["ptp"]["dom_sel"] = domain
    $action["ptp"]["sport"] = 320
    $action["ptp"]["dport"] = 320
    $action["addr"]["update"] = "MESA_ACL_ADDR_UPDATE_MAC_IP_SWAP_UC"
    $ts.dut.call("mesa_ace_add", 0, $ace_conf)

    # Create the REQUEST frame
    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")
    #request_pdu_create(requestClockId, requestPortNumber)
    $frametx = frameHdrTx.dup + request_pdu_create($requestClockId, $requestPortNumber)

    # Create the RESPONSE frame
    $frameHdrRx = frame_create("00:08:09:0a:0b:0c", "00:02:03:04:05:06")
    #response_pdu_rx_create(controlField=IGNORE, secondsField=IGNORE, reqClockId=IGNORE, srcClockId=IGNORE, reqPortNumber=IGNORE, srcPortNumber=IGNORE, flagField=IGNORE)
    framerx = $frameHdrRx.dup + response_pdu_rx_create(3, 5, $requestClockId, 0, $requestPortNumber, DEFAULT_PORT_ID_PORT, IGNORE)

    # Set TOD to 5 seconds
    tod  = $ts.dut.call("mesa_ts_domain_timeofday_get", domain)
    tod[0]["seconds"] = 5
    tod[0]["nanoseconds"] = 0
    $ts.dut.call("mesa_ts_domain_timeofday_set", domain, tod[0])

    # Transmit Delay Request on front port
    frame_tx($frametx, $port0, framerx, "", "", "")
    end

    test "Configure auto delay response" do
    conf = $ts.dut.call("mesa_ts_autoresp_dom_cfg_get", domain)
    conf["ptp_port_individual"] = true
    conf["ptp_port_msb"] = 0xFFFF
    conf["clock_identity"] = [1,2,3,4,5,6,7,8]
    conf["flag_field_update"]["mask"] = 0xFF
    conf["flag_field_update"]["value"] = 0xAA
    $ts.dut.call("mesa_ts_autoresp_dom_cfg_set", domain, conf)

    srcPortNumber = ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) ? (0xFFC0 + $ts.dut.port_list[$port0] + 1) : (0xFF80 + $ts.dut.port_list[$port0] + 1)

    #response_pdu_rx_create(controlField=IGNORE, secondsField=IGNORE, reqClockId=IGNORE, srcClockId=IGNORE, reqPortNumber=IGNORE, srcPortNumber=IGNORE, flagField=IGNORE)
    framerx = $frameHdrRx.dup + response_pdu_rx_create(IGNORE, IGNORE, $requestClockId, 0x0102030405060708, $requestPortNumber, srcPortNumber, 0xAA)

    # Transmit Delay Request on front port
    frame_tx($frametx, $port0, framerx, "", "", "")
    end

    test "test the port configured SMAC" do
    $action["ptp"]["set_smac_to_port_mac"] = true
    $ts.dut.call("mesa_ace_add", 0, $ace_conf)

    $frameHdrRx = frame_create("00:08:09:0a:0b:0c", "00:0d:0e:0f:10:11")
    #response_pdu_rx_create(controlField=IGNORE, secondsField=IGNORE, reqClockId=IGNORE, srcClockId=IGNORE, reqPortNumber=IGNORE, srcPortNumber=IGNORE, flagField=IGNORE)
    framerx = $frameHdrRx.dup + response_pdu_rx_create()

    # Transmit Delay Request on front port
    frame_tx($frametx, $port0, framerx, "", "", "")
    end

    # Delete ACE rule
    $ts.dut.call("mesa_ace_del", $acl_id)

    end
end

test "test_conf" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # Flush MAC table
    $ts.dut.call("mesa_mac_table_flush")

    $operation_mode_0_restore = $ts.dut.call("mesa_ts_operation_mode_get", $ts.dut.port_list[$port0])

    # Auto delay response save
    $autoresp_dom_cfg_0_restore = $ts.dut.call("mesa_ts_autoresp_dom_cfg_get", 0)
    $autoresp_dom_cfg_1_restore = $ts.dut.call("mesa_ts_autoresp_dom_cfg_get", 1)
    $autoresp_dom_cfg_2_restore = $ts.dut.call("mesa_ts_autoresp_dom_cfg_get", 2)

    # Configure the port SMAC
    conf = $ts.dut.call("mesa_ts_smac_get", $ts.dut.port_list[$port0])
    $ts_smac_0_restore = conf.dup
    conf["addr"] = [00, 0x0d, 0x0e, 0x0f, 0x10, 0x11]
    $ts.dut.call("mesa_ts_smac_set", $ts.dut.port_list[$port0], conf)

    $ts.dut.run "mesa-cmd Debug Port Polling disable"
end

test "test_run" do
    # Test Auto request response 
    tod_auto_responce_test(0)
    tod_auto_responce_test(1)
    tod_auto_responce_test(2)
end

test "test_clean_up" do
    # Operation mode restore
    $ts.dut.call("mesa_ts_operation_mode_set", $ts.dut.port_list[$port0], $operation_mode_0_restore)

    # Auto delay response restore
    $ts.dut.call("mesa_ts_autoresp_dom_cfg_set", 0, $autoresp_dom_cfg_0_restore)
    $ts.dut.call("mesa_ts_autoresp_dom_cfg_set", 1, $autoresp_dom_cfg_1_restore)
    $ts.dut.call("mesa_ts_autoresp_dom_cfg_set", 2, $autoresp_dom_cfg_2_restore)

    # Port SMAC restore
    $ts.dut.call("mesa_ts_smac_set", $ts.dut.port_list[$port0], $ts_smac_0_restore)

    $ts.dut.run "mesa-cmd Debug Port Polling enable"
end