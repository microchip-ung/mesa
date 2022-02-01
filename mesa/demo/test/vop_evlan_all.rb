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
    $cap_oam_v0 = ($ts.dut.call("mesa_capability", "MESA_CAP_VOP_V0") != 0) ? true : false
    $cap_oam_v1 = ($ts.dut.call("mesa_capability", "MESA_CAP_VOP_V1") != 0) ? true : false
    $cap_oam_v2 = ($ts.dut.call("mesa_capability", "MESA_CAP_VOP_V2") != 0) ? true : false
    assert(($cap_oam_v0 == true) || ($cap_oam_v1 == true) || ($cap_oam_v2 == true), "VOP must be V0 or V1 or V2,  (cap_oam_v1=#{$cap_oam_v1} $cap_oam_v2=#{$cap_oam_v1})")

    $cap_event_supported = $ts.dut.call("mesa_capability", "MESA_CAP_VOP_EVENT_SUPPORTED")
    $cap_ccm_defects = $ts.dut.call("mesa_capability", "MESA_CAP_VOP_CCM_DEFECT")
    $cap_cosid = ($ts.dut.call("mesa_capability", "MESA_CAP_QOS_COSID_CLASSIFICATION") != 0) ? true : false
    $cap_vstax = ($ts.dut.call("mesa_capability", "MESA_CAP_PACKET_VSTAX") != 0) ? true : false
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    $cap_tx_ifh_size = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_TX_IFH_SIZE")
    $cap_port_cnt = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    $cap_vop_cfm = ($ts.dut.call("mesa_capability", "MESA_CAP_VOP_CFM") != 0) ? true : false
    t_i("cap_event_supported #{$cap_event_supported}  cap_ccm_defects #{$cap_ccm_defects}  cap_oam_v0 #{$cap_oam_v0}  cap_oam_v1 #{$cap_oam_v1}  cap_oam_v2 #{$cap_oam_v2}  $cap_vop_cfm #{$cap_vop_cfm}  cap_cosid #{$cap_cosid}  cap_vstax #{$cap_vstax}  $cap_epid #{$cap_epid}  $cap_family #{$cap_family}  cap_tx_ifh_size #{$cap_tx_ifh_size}  cap_port_cnt #{$cap_port_cnt}")
end

$p_vce         = 1
$p1_vce        = 2
$d_vo_vce      = 3
$d_voe_vce     = 4
$d_voi_vce     = 5
$u_voi_vce     = 6
$d_voe_mel_vce = 7
$p2_vce =        8
$p2_v_vce =      9

$du_vo_tce  = 1
$p1_voe_tce = 2
$d_voe_tce  = 3
$inj_tce    = 4
$p_inj_tce  = 5
$p1_inj_tce = 6
$p_blk_tce  = 7
$p1_blk_tce = 8

$port0    = 0
$port1    = 1
$port2    = 2
$npi_port = 3

$mepid = 11
$peer_mepid = 22
$vid = 100
if ($cap_oam_v2)
    $p_voe_meg_level = 6    # ON V2 Independent MEL in supported so the Port domain level can be higher that the VLAN domain level
end
if ($cap_oam_v0 || $cap_oam_v1)            # ON V1 Independent MEL in not supported in all use cases so the Port domain level must be lower that the VLAN domain level
    $p_voe_meg_level = 2
end
$v_voe_meg_level = 3
$voi_meg_level = 6
$prio = 0
$sequence_no = 0
$period = "MESA_VOE_CCM_PERIOD_1_SEC"
$megid = ['A'.ord,'B'.ord,'C'.ord,'D'.ord,'E'.ord,'F'.ord,'G'.ord,'H'.ord]
$cpu_queue = 7
$pvid = 1

$port_map = $ts.dut.call("mesa_port_map_get", $cap_port_cnt)

#---------- Frame testing -----------------------------------------------------

def voe_cc_rx_test_func(voe_idx, level, tag_vid)
    test "voe_cc_rx_test_func  voe_idx #{voe_idx}  level #{level}  tag_vid #{tag_vid}" do

    exp_valid_ccm_cnt = 0
    exp_invalid_ccm_cnt = 0
    exp_invalid_seq_cnt = 0
    exp_discard_cnt = 0
    exp_sequence = $sequence_no

    check_pdu_seen(voe_idx, PDU_CLEAR)
    check_voe_event(voe_idx, [EVENT_CLEAR])
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    # Enable CCM in VOE
    #voe_cc_config(voe_idx, enable, peer_mepid, megid, prio, period, cpu_copy="MESA_OAM_CPU_COPY_ALL", seq_no=false, selected=false)
    voe_cc_config(voe_idx, true, $peer_mepid, $megid, $prio, $period, "MESA_OAM_CPU_COPY_NONE")

    sleep(4)

    t_i("Before transmitting CCM. Check for LOC status")
    check_cc_status(voe_idx, [EVENT_LOC])

    t_i("Create frame")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)

    test "Check LOC clear and set" do
    t_i("Transmit valid CCM frame against VOE to clear LOC")
    exp_sequence += 1
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    exp_valid_ccm_cnt += 1

    t_i("After transmitting CCM. Check LOC event and status")
    check_pdu_seen(voe_idx, PDU_CCM)
    check_voe_event(voe_idx, [EVENT_LOC])
    check_cc_status(voe_idx, [EVENT_NONE])

    sleep(4)

    t_i("After sleep. Check LOC event and status")
    check_voe_event(voe_idx, [EVENT_LOC])
    check_cc_status(voe_idx, [EVENT_LOC])
    end

    test "Check Zero Period" do
    t_i("Transmit invalid CCM frame against VOE with Period zero")
    frametx = frame.dup
    frametx += ccm_pdu_create(level, 0, exp_sequence, $peer_mepid, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    exp_invalid_ccm_cnt += 1
    exp_discard_cnt += 1

    t_i("After transmitting CCM. Check Period zero event and status")
    check_pdu_seen(voe_idx, PDU_NONE)
    check_voe_event(voe_idx, [EVENT_ZERO_PERIO])
    check_cc_status(voe_idx, [EVENT_ZERO_PERIO,EVENT_LOC])
    end

    test "check invalid level" do
    t_i("Transmit invalid CCM frame against VOE with invalid level")
    frametx = frame.dup
    frametx += ccm_pdu_create(level-1, $period, exp_sequence, $peer_mepid, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    if ($cap_oam_v2)    # Low level CCM is not accepted as a CCM PDU on Serval1 - meaning it is not counting as invalid CCM
        exp_invalid_ccm_cnt += 1
    end
    exp_discard_cnt += 1

    t_i("After transmitting CCM. Check Level event and status")
    check_pdu_seen(voe_idx, PDU_LOW_LEVEL)
    if ($cap_oam_v2)    # Low level CCM is not accepted as a CCM PDU on Serval1 - meaning it cannot clear the zero period state
        check_voe_event(voe_idx, [EVENT_LEVEL,EVENT_ZERO_PERIO])
    else
        check_voe_event(voe_idx, [EVENT_LEVEL])
    end
    check_cc_status(voe_idx, [EVENT_LEVEL,EVENT_LOC])

    if ($cap_ccm_defects != 0)
        t_i("Check clear of level defect after 3.5 CCM period")
        sleep (4)
        check_voe_event(voe_idx, [EVENT_LEVEL])
        check_cc_status(voe_idx, [EVENT_LOC_ALONE])
    end
    end

    test "Check invalid MEP id" do
    t_i("Transmit invalid CCM frame against VOE with invalid peer MEP ID")
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid+1, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    exp_invalid_ccm_cnt += 1
    exp_discard_cnt += 1

    t_i("After transmitting CCM. Check Peer MEP ID event and status")
    if ($cap_ccm_defects == 0)
        t_i("Check clear of level defect after receiving CCM with expected level")
        check_voe_event(voe_idx, [EVENT_MEP,EVENT_LEVEL])
    else
        check_voe_event(voe_idx, [EVENT_MEP])
    end
    check_cc_status(voe_idx, [EVENT_MEP,EVENT_LOC])

    if ($cap_ccm_defects != 0)
        t_i("Check clear of MEP id defect after 3.5 CCM period")
        sleep (4)
        check_voe_event(voe_idx, [EVENT_MEP])
        check_cc_status(voe_idx, [EVENT_LOC_ALONE])
    end
    end

    test "check invalid MEG id" do
    t_i("Transmit invalid CCM frame against VOE with invalid MEG ID")
    save = $megid[0]
    $megid[0] = 1
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
    $megid[0] = save
    frame_tx(frametx, $port0, "", "", "", "")
    exp_invalid_ccm_cnt += 1
    exp_discard_cnt += 1

    t_i("After transmitting CCM. Check MEG ID event and status")
    if ($cap_ccm_defects == 0)
        t_i("Check clear of MEP id defect after receiving CCM with expected MEP id")
        check_voe_event(voe_idx, [EVENT_MEP,EVENT_MEG])
    else
        check_voe_event(voe_idx, [EVENT_MEG])
    end
    check_cc_status(voe_idx, [EVENT_MEG,EVENT_LOC])

    if ($cap_ccm_defects != 0)
        t_i("Check clear of MEG id defect after 3.5 CCM period")
        sleep (4)
        check_voe_event(voe_idx, [EVENT_MEG])
        check_cc_status(voe_idx, [EVENT_LOC_ALONE])
    end
    end

    test "Check invalid period" do
    t_i("Transmit invalid CCM frame against VOE with invalid period")
    exp_sequence = ($cap_ccm_defects == 0) ? exp_sequence+1 : exp_sequence    # According to G.8021 invalid period should still give LOC but this is not implemented whenno CCM defecta.
    frametx = frame.dup
    if ($cap_ccm_defects != 0)  # When defects are supported we want the clear time to be based on one sec period. Therefore the expected period must be different than one sec */
        voe_cc_change(voe_idx, "MESA_VOE_CCM_PERIOD_10_SEC")
        frametx += ccm_pdu_create(level, "MESA_VOE_CCM_PERIOD_1_SEC", exp_sequence, $peer_mepid, $megid)
    else
        frametx += ccm_pdu_create(level, "MESA_VOE_CCM_PERIOD_3_3_MS", exp_sequence, $peer_mepid, $megid)
    end
    frame_tx(frametx, $port0, "", "", "", "")

    t_i("After transmitting CCM. Check Period event and status")
    if ($cap_ccm_defects == 0)
        t_i("Check clear of MEG id defect after receiving CCM with expected MEG id")
        check_voe_event(voe_idx, [EVENT_MEG,EVENT_PERIOD,EVENT_LOC])   # According to G.8021 invalid period should still give LOC but this is not implemented whenno CCM defecta.
        check_cc_status(voe_idx, [EVENT_PERIOD,EVENT_NONE_LOC])
        exp_valid_ccm_cnt += 1
    else
        check_voe_event(voe_idx, [EVENT_PERIOD])
        check_cc_status(voe_idx, [EVENT_PERIOD,EVENT_LOC])
        exp_invalid_ccm_cnt += 1
        exp_discard_cnt += 1
    end

    if ($cap_ccm_defects != 0)
        t_i("Check clear of Period defect after 3.5 CCM period")
        sleep (4)
        check_voe_event(voe_idx, [EVENT_PERIOD])
        check_cc_status(voe_idx, [EVENT_LOC_ALONE])
        voe_cc_change(voe_idx, $period)
    end
    end

    test "Check invalid Priority" do
    t_i("Change default COS ID on port")
    #qos_port_config(port, def_qosid)
    qos_port_config($ts.dut.port_list[$port0], $prio+1)    # This is for V2 and untagged frames on Serval
    
    t_i("Transmit valid CCM frame against VOE with unexpected Priority")
    exp_sequence += 1
    frame = frame_create(MC_STRING, SC_STRING, tag_vid, $prio+1)  # On Serval the PC value in the tag is the priority
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    exp_valid_ccm_cnt += 1

    t_i("After transmitting CCM. Check Priority event and status")
    check_pdu_seen(voe_idx, PDU_CCM)
    if ($cap_ccm_defects == 0)
        t_i("Check clear of Period defect after receiving CCM with expected Period")
        check_voe_event(voe_idx, [EVENT_PERIOD,EVENT_PRIORITY])
    else
        check_voe_event(voe_idx, [EVENT_PRIORITY,EVENT_LOC])
    end
    check_cc_status(voe_idx, [EVENT_PRIORITY,EVENT_NONE_LOC])

    if ($cap_ccm_defects != 0)
        t_i("Check clear of Priority defect after 3.5 CCM period")
        sleep (4)
        check_voe_event(voe_idx, [EVENT_PRIORITY])
        check_cc_status(voe_idx, [EVENT_LOC_ALONE])
    end

    t_i("Restore default COS ID on port")
    #qos_port_config(port, def_qosid)
    qos_port_config($ts.dut.port_list[$port0], $prio)
    
    t_i("Transmit valid CCM frame against VOE.")
    exp_sequence += 1
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    exp_valid_ccm_cnt += 1
    
    t_i("After transmitting CCM. Check Priority event and status")
    check_pdu_seen(voe_idx, PDU_CCM)
    if ($cap_ccm_defects == 0)
        t_i("Check clear of Priority defect after receiving CCM with expected Priority")
        check_voe_event(voe_idx, [EVENT_PRIORITY])
    else
        check_voe_event(voe_idx, [EVENT_LOC])
    end
    check_cc_status(voe_idx, [EVENT_NONE])
    end

    test "Check RDI" do
    t_i("Transmit valid CCM frame against VOE with RDI set")
    exp_sequence += 1
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid, 1)
    frame_tx(frametx, $port0, "", "", "", "")
    exp_valid_ccm_cnt += 1

    t_i("After transmitting CCM. Check RDI event and status")
    check_pdu_seen(voe_idx, PDU_CCM)
    check_voe_event(voe_idx, [EVENT_RDI])
    check_cc_status(voe_idx, [EVENT_RDI])

    t_i("Transmit valid CCM frame against VOE.")
    exp_sequence += 1
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    exp_valid_ccm_cnt += 1

    t_i("After transmitting CCM. Check RDI event and status")
    check_pdu_seen(voe_idx, PDU_CCM)
    check_voe_event(voe_idx, [EVENT_RDI])
    check_cc_status(voe_idx, [EVENT_NONE])
    end

    test "Check invalid sequence number" do
    t_i("Transmit valid CCM frame against VOE with unexpected sequence number")
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    exp_valid_ccm_cnt += 1
    exp_invalid_seq_cnt += 1

    t_i("After transmitting CCM. Check received CCM sequence error")
    check_pdu_seen(voe_idx, PDU_CCM_SEQ)
    end

    test "Check counters" do
    #check_ccm_counters(voe_idx, ccm_rx_valid, ccm_rx_invalid, ccm_rx_seq, ccm_tx)
    check_ccm_counters(voe_idx, exp_valid_ccm_cnt, exp_invalid_ccm_cnt, exp_invalid_seq_cnt, 0)
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, exp_valid_ccm_cnt, 0, 0, 0, exp_discard_cnt, 0)
    end

    if ($cap_vop_cfm)
        test "Check count as selected" do
        t_i("Enable count as selected")
        #voe_cc_config(voe_idx, enable, peer_mepid, megid, prio, period, cpu_copy="MESA_OAM_CPU_COPY_ALL", seq_no=false, selected=false)
        voe_cc_config(voe_idx, true, $peer_mepid, $megid, $prio, $period, "MESA_OAM_CPU_COPY_NONE", false, true)

        t_i("Transmit valid CCM frame against VOE")
        exp_sequence += 1
        frametx = frame.dup
        frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
        frame_tx(frametx, $port0, "", "", "", "")

        t_i("Check counters")
        #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
        check_voe_counters(voe_idx, exp_valid_ccm_cnt, 0, 1, 0, exp_discard_cnt, 0)
        end
    end

    t_i("Clear and check counters")
    clear_all_counters(voe_idx, OAM_CNT_ALL)
    check_ccm_counters(voe_idx, 0, 0, 0, 0)
    check_voe_counters(voe_idx, 0, 0, 0, 0, 0, 0)

    test "Check TLV" do
    t_i("Transmit valid CCM frame with Port TLV against VOE")
    #ccm_pdu_create(level, period, sequence, mepid, megid, rdi=0, version=0, tlv=TLV_NONE)
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid, 0, 0, TLV_PORT)
    frame_tx(frametx, $port0, "", "", "", "")

    t_i("Check PDU seen, events and received TLV")
    check_pdu_seen(voe_idx, PDU_CCM_TLV)
    check_voe_event(voe_idx, [EVENT_TLV_PORT])
    #check_cc_status_values(voe_idx, rx_port, port_tlv, if_tlv)
    check_cc_status_values(voe_idx, $ts.dut.port_list[$port0], 2, 0)

    t_i("Transmit valid CCM frame with Interface TLV against VOE")
    #ccm_pdu_create(level, period, sequence, mepid, megid, rdi=0, version=0, tlv=TLV_NONE)
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid, 0, 0, TLV_IF)
    frame_tx(frametx, $port0, "", "", "", "")

    t_i("Check PDU seen, events and received TLV")
    check_pdu_seen(voe_idx, PDU_CCM_TLV)
    check_voe_event(voe_idx, [EVENT_TLV_IF])
    #check_cc_status_values(voe_idx, rx_port, port_tlv, if_tlv)
    check_cc_status_values(voe_idx, $ts.dut.port_list[$port0], 2, 2)
    end

    if $cap_oam_v2 && (tag_vid != 0)    # CCM Rx Port and Port move event is not supported on Serval1
        test "Check RX port move" do
        t_i("Configure Down VOE/VOI to have two ports")
        # Note that this rule must be in front of the Up-MIP and default port rules. Last parameter assure this
        vce_config($d_vo_vce, "#{$ts.dut.port_list[$port0]},#{$ts.dut.port_list[$port2]}", $vid, 0, vce_level_mask(0, $voi_meg_level), $d_vo_iflow, "MESA_OAM_DETECT_SINGLE_TAGGED", $u_voi_vce)

        t_i("Transmit four valid CCM frame against VOE on the extra port")
        frametx = frame.dup
        frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
        for i in 0..3
            frame_tx(frametx, $port2, "", "", "", "")
        end
    
        t_i("Check PDU seen, events and RX port")
        check_pdu_seen(voe_idx, PDU_CCM)
        check_voe_event(voe_idx, [EVENT_PORT_MOVE])
        #check_cc_status_values(voe_idx, rx_port, port_tlv, if_tlv)
        check_cc_status_values(voe_idx, $ts.dut.port_list[$port2], 2, 2)

        t_i("Configure Down VOE/VOI to have one port ")
        vce_config($d_vo_vce, "#{$ts.dut.port_list[$port0]}", $vid, 0, vce_level_mask(0, $voi_meg_level), $d_vo_iflow, "MESA_OAM_DETECT_SINGLE_TAGGED", $u_voi_vce)
        end
    end

    test "Check CCM copy to CPU" do
    t_i("Configure CCM copy to ALL")
    #voe_cc_config(voe_idx, enable, peer_mepid, megid, prio, period, cpu_copy="MESA_OAM_CPU_COPY_ALL", seq_no=false, selected=false)
    voe_cc_config(voe_idx, true, $peer_mepid, $megid, $prio, $period)

    t_i("transmit three CCM frames and check that all are copied to CPU")
    ccm_count = 0
    rx_ifh = rx_ifh_create()
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
    for i in 0..2
         frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
    end

    if ($cap_oam_v2)    # Auto copy CCM is only supported on V2
        t_i("Configure CCM copy to AUTO")
        #voe_cc_config(voe_idx, enable, peer_mepid, megid, prio, period, cpu_copy="MESA_OAM_CPU_COPY_ALL", seq_no=false, selected=false)
        voe_cc_config(voe_idx, true, $peer_mepid, $megid, $prio, $period, "MESA_OAM_CPU_COPY_AUTO")

        t_i("transmit four valid CCM frames fast and check that only a sample is copied to CPU")
        ccm_count = 0
        $ts.dut.call("mesa_port_counters_clear", $ts.dut.port_list[$npi_port])
        for i in 0..3
            frame_tx(frametx, $port0, " ", " ", " ", " ")
        end
        pcounters = $ts.dut.call("mesa_port_counters_get", $ts.dut.port_list[$npi_port])
        if (pcounters["rmon"]["tx_etherStatsPkts"] > 2)
            t_e("Received CCM frame count unexpected. Expected <= 2 counted #{pcounters["rmon"]["tx_etherStatsPkts"]}")
        end

        t_i("transmit three valid CCM frames slow and check that all frames are copied to CPU")
        ccm_count = 0
        for i in 0..2
            sleep(4)
            frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
        end

        t_i("transmit three invalid CCM frames slow and check that all frames are copied to CPU")
        frametx = frame.dup
        frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid+1, $megid)
        ccm_count = 0
        for i in 0..2
            sleep(4)
            frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
        end
    end # Auto copy CCM is not supported on Serval1
    end

    sleep(4)

    test "Disable CCM in VOE. Transmit valid CCM and check that LOC status is not updated" do
    voe_cc_config(voe_idx, false, 0, [], 0, 0)
    check_cc_status(voe_idx, [EVENT_LOC])
    exp_sequence += 1
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, exp_sequence, $peer_mepid, $megid)
    frame_tx(frametx, $port0, "", "", "", "")
    check_cc_status(voe_idx, [EVENT_LOC])
    end

    end
end

def voe_cc_block_test_func(voe_idx, level, tag_vid)
    test "voe_cc_block_test_func  voe_idx #{voe_idx}  level #{level}  tag_vid #{tag_vid}" do

    t_i("Before transmitting CCM. Clear events and counters")
    check_voe_event(voe_idx, [EVENT_CLEAR])
    check_pdu_seen(voe_idx, PDU_CLEAR)
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    t_i("Create frame")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)

    test "Transmit CCM frame behind VOE to be filtered/blocked." do
    frametx = frame.dup
    frametx += ccm_pdu_create(level, $period, 0, $peer_mepid, $megid)
    if (tag_vid != 0)
        frame_tx(frametx, $port2, "", frametx, "", "")
    else
        frame_tx(frametx, $port2, "", "", "", "")
    end

    t_i("Check TX Low level PDU seen")
    check_pdu_seen(voe_idx, PDU_TX_LOW_LEVEL)

    t_i("Check Discard counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, 0, 0, 0, 0, 0, 1)
    end

    test "Transmit CCM frame to be forwarded." do
    t_i ("Transmit CCM frame behind VOE to be forwarded.")
    frametx = frame.dup
    frametx += ccm_pdu_create(level+1, $period, 0, $peer_mepid, $megid)
    frame_tx(frametx, $port2, frametx, frametx, "", "")

    t_i("Transmit CCM frame in front of VOE to be forwarded.")
    frame_tx(frametx, $port0, "", frametx, frametx, "")

    t_i("Check Tx and Discard counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, 0, 0, 0, 0, 0, 1)
    check_ccm_counters(voe_idx, 0, 0, 0, 0)
    end

    end
end

def voe_cc_inject_test_func(voe_idx, level, tag_vid)
    lan966x = ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X")) ? true : false

    test "voe_cc_inject_test_func  voe_idx #{voe_idx}  level #{level}  tag_vid #{tag_vid}" do

    port_domain = (tag_vid == 0) ? true : false

    t_i("Before injecting CCM. Clear events and and counters")
    check_voe_event(voe_idx, [EVENT_CLEAR])
    check_pdu_seen(voe_idx, PDU_CLEAR)
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    t_i("Create frame.")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    ccm_pdu = ccm_pdu_create(level, $period, 0, $peer_mepid, $megid)

    iflow = $cap_oam_v2 ? (port_domain ? $p_inj_iflow : 0) : (port_domain ? 0 : $inj_iflow)
    vid = port_domain ? $pvid : tag_vid
    frametx = tx_ifh_create(vid, $ts.dut.port_list[$port0], "MESA_PACKET_OAM_TYPE_CCM", false, false, iflow) + frame_create(MC_STRING, SC_STRING) + ccm_pdu.dup

    test "Check no RDI insertion." do
    t_i("Enable CCM in VOE.")
    voe_cc_config(voe_idx, true, $peer_mepid, $megid, $prio, $period)

    t_i("Create tx and rx frames")
    framerx = frame.dup + ccm_pdu.dup

    t_i("Inject CCM frame and check received CCM with no RDI.")
    frame_tx(frametx, $npi_port, framerx , "", "", "")
    end

    test "Check RDI insertion." do
    t_i("Set RDI active in VOE")
    $ts.dut.call("mesa_voe_cc_rdi_set", voe_idx, true)

    t_i("Inject CCM frame and check received CCM with RDI.")
    framerx = frame.dup + ccm_pdu_create(level, $period, $cap_oam_v2 ? 1 : 0, $peer_mepid, $megid, 1)     # On Jaguar2 the sequence number is inserted when RDI insertion is enabled
    frame_tx(frametx, $npi_port, framerx , "", "", "")

    t_i("Check counters")
    #check_ccm_counters(voe_idx, ccm_rx_valid, ccm_rx_invalid, ccm_rx_seq, ccm_tx)
    check_ccm_counters(voe_idx, 0, 0, 0, ($cap_oam_v2 || lan966x) ? 2 : 0)   # On Serval the CCM TX counter only count when the sequence number update is enabled
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, 0, (lan966x ? 0 : 2), 0, 0, 0, 0)   # Currently the OAM TX counter is not working on LAN966X
    end

    test "Check sequence number insertion." do
    t_i("Clear RDI active in VOE")
    $ts.dut.call("mesa_voe_cc_rdi_set", voe_idx, false)

    t_i("Enable sequence number update")
    #voe_cc_config(voe_idx, enable, peer_mepid, megid, prio, period, cpu_copy="MESA_OAM_CPU_COPY_ALL", seq_no=false, selected=false)
    voe_cc_config(voe_idx, true, $peer_mepid, $megid, $prio, $period, "MESA_OAM_CPU_COPY_ALL", true)

    t_i("Inject CCM frame and check received CCM with no RDI and sequence number.")
    exp_seq = ($cap_oam_v2 || lan966x) ? 2 : 1     #V2 and LAN966X start with 2 and Serval start with 1 sequence number
    framerx = frame.dup + ccm_pdu_create(level, $period, exp_seq, $peer_mepid, $megid)
    frame_tx(frametx, $npi_port, framerx , "", "", "")

    t_i("Inject CCM frame and check received CCM with no RDI and sequence number.")
    exp_seq += 1
    framerx = frame.dup + ccm_pdu_create(level, $period, exp_seq, $peer_mepid, $megid)
    frame_tx(frametx, $npi_port, framerx , "", "", "")

   #check_ccm_counters(voe_idx, ccm_rx_valid, ccm_rx_invalid, ccm_rx_seq, ccm_tx)
    check_ccm_counters(voe_idx, 0, 0, 0, ($cap_oam_v2 || lan966x) ? 4 : 2)   # On Serval the CCM TX counter only count when the sequence number update is enabled
    end

    if ($cap_vop_cfm)
        test "Check count as selected." do
        t_i("Enable count as selected")
        #voe_cc_config(voe_idx, enable, peer_mepid, megid, prio, period, cpu_copy="MESA_OAM_CPU_COPY_ALL", seq_no=false, selected=false)
        voe_cc_config(voe_idx, true, $peer_mepid, $megid, $prio, $period, "MESA_OAM_CPU_COPY_ALL", false, true)

        t_i("Inject CCM frame.")
        framerx = frame.dup + ccm_pdu_create(level, $period, 0, $peer_mepid, $megid)
        frame_tx(frametx, $npi_port, framerx , "", "", "")

        t_i("Check counters")
        #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
        check_voe_counters(voe_idx, 0, 4, 0, 1, 0, 0)

        t_i("Clear and check counters")
        clear_all_counters(voe_idx, OAM_CNT_ALL)
        check_ccm_counters(voe_idx, 0, 0, 0, 0)
        check_voe_counters(voe_idx, 0, 0, 0, 0, 0, 0)
        end
    end
    end
end

def voe_laps_rx_test_func(voe_idx, level, tag_vid, isdx, res_port)
    test "voe_laps_rx_test_func  voe_idx #{voe_idx}  level #{level}  tag_vid #{tag_vid}  isdx #{isdx}, res_port #{res_port}" do

    t_i("Before transmitting LAPS. Clear events and status")
    check_voe_event(voe_idx, [EVENT_CLEAR])
    check_pdu_seen(voe_idx, PDU_CLEAR)
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    t_i("Create frame")
    frametx = frame_create(MC_STRING, SC_STRING, tag_vid) + laps_pdu_create(level, REQUEST_MANUEL_SWITCH)   # Manuel request
    rx_ifh = rx_ifh_create(isdx, $ts.dut.port_list[res_port])

    test "Check no LAPS handling." do
    t_i("Disable LAPS")
    #voe_laps_config(voe_idx, enable, count_as_selected)
    voe_laps_config(voe_idx, false, false)

    t_i("Transmit valid LAPS frame against VOE - copy to CPU is not expected")
    frame_tx(frametx, $port0, "", "", "", "")
    end

    test "Check LAPS handling." do
    t_i("Enable LAPS - no count as selected")
    #voe_laps_config(voe_idx, enable, count_as_selected)
    voe_laps_config(voe_idx, true, false)

    t_i("Transmit valid LAPS frame against VOE - copy to CPU is expected")
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)

    t_i("After transmitting LAPS. Check PDU seen")
    check_pdu_seen(voe_idx, PDU_LAPS)

    t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, 2, 0, 0, 0, 0, 0)
    end

    test "Check count as selected." do
    t_i("Enable count as selected")
    #voe_laps_config(voe_idx, enable, count_as_selected)
    voe_laps_config(voe_idx, true, true)

    t_i("Transmit valid LAPS frame against VOE")
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)

    t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, 2, 0, 1, 0, 0, 0)
    end
    end
end

def voe_lb_rx_test_func(voe_idx, level, tag_vid)
    test "voe_lb_rx_test_func  voe_idx #{voe_idx}  level #{level}  tag_vid #{tag_vid}" do

    oam_rx_exp = 0
    lbr_tx_exp = 0
    lbr_rx_exp = 0

    t_i("Before transmitting LBM. Clear events, status and counters")
    check_voe_event(voe_idx, [EVENT_CLEAR])
    check_pdu_seen(voe_idx, PDU_CLEAR)
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    t_i("Create frame")
    framemc = frame_create(MC_STRING, SC_STRING, tag_vid)
    frameuctx = frame_create(UC_STRING, SC_STRING, tag_vid)
    frameucrx = frame_create(SC_STRING, UC_STRING, tag_vid)
    framerx = frameucrx.dup + lb_pdu_create(level, 2, 5)
    rx_ifh = rx_ifh_create()

    test "Check no LB handling." do
    t_i("LB disable test")
    #voe_lb_config(voe_idx, enable, count_as_selected, trans_id)
    voe_lb_config(voe_idx, false, false, 0)

    t_i("Transmit valid LBM frame against VOE")
    frametx = framemc.dup + lb_pdu_create(level, 3, 5)
    frame_tx(frametx, $port0, "", "", "", "")
    oam_rx_exp += 1

    t_i("Check LBM PDU seen")
    check_pdu_seen(voe_idx, PDU_LBM)

    t_i("Transmit valid LBR frame against VOE")
    frametx = frameuctx.dup + lb_pdu_create(level, 2, 5)
    frame_tx(frametx, $port0, "", "", "", "")
    oam_rx_exp += 1

    t_i("Check LBR PDU seen and Selected counters")
    check_pdu_seen(voe_idx, PDU_LBR)
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, 0, 0, 0, 0, 0)
    #check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm)
    check_voe_lb_counters(voe_idx, lbr_rx_exp, 0, 0, 0)
    end

    test "Check LB handling." do
    t_i("LB enable test - no count as selected - no LBM to CPU")
    #voe_lb_config(voe_idx, enable, count_as_selected, trans_id, lbm_copy = false)
    voe_lb_config(voe_idx, true, false, 5)

    t_i("Transmit valid LBM frame against VOE")
    frametx = framemc.dup + lb_pdu_create(level, 3, 5)
    frame_tx(frametx, $port0, framerx, "", "", "")
    oam_rx_exp += 1
    lbr_tx_exp += 1

    t_i("Check LBM PDU seen")
    check_pdu_seen(voe_idx, PDU_LBM)

    t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, lbr_tx_exp, 0, 0, 0, 0)

    t_i("Check LB counters in VOE")
    #check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm)
    check_voe_lb_counters(voe_idx, lbr_rx_exp, 0, lbr_tx_exp, 0)
    end

    test "Check count as selected." do
    t_i("LB enable test - count as selected")
    voe_lb_config(voe_idx, true, true, LBM_TRANSACTION_ID_NONE)

    t_i("Transmit valid LBM frame against VOE")
    frametx = framemc.dup + lb_pdu_create(level, 3, 5)
    frame_tx(frametx, $port0, framerx, "", "", "")
    lbr_tx_exp += 1

    t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, lbr_tx_exp-1, 1, 1, 0, 0)     # 

    t_i("Check LB counters in VOE")
    #check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm)
    check_voe_lb_counters(voe_idx, lbr_rx_exp, 0, lbr_tx_exp, 0)

    t_i("Transmit valid LBR frame against VOE - No OOO")
    frametx = frameuctx.dup + lb_pdu_create(level, 2, 5)
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
    lbr_rx_exp += 1

    t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, lbr_tx_exp-1, 2, 1, 0, 0)

    t_i("Check LBR counters in VOE")
    #check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm)
    check_voe_lb_counters(voe_idx, lbr_rx_exp, 0, lbr_tx_exp, 0)
    end

    test "Check OOO." do
    t_i("LB enable test - no count as selected")
    voe_lb_config(voe_idx, true, false, LBM_TRANSACTION_ID_NONE)

    t_i("Transmit valid LBR frame against VOE - With OOO")
    frametx = frameuctx.dup + lb_pdu_create(level, 2, 7)
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
    lbr_rx_exp += 1
    oam_rx_exp += 1

    t_i("Check Unexpected Transaction PDU seen")
    check_pdu_seen(voe_idx, PDU_LBR_TRANS)

     t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, lbr_tx_exp-1, 2, 1, 0, 0)

    t_i("Check OOO counters in VOE")
    #check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm, tx_trans=LBM_TRANSACTION_ID_NONE, rx_trans=LBM_TRANSACTION_ID_NONE)
    check_voe_lb_counters(voe_idx, lbr_rx_exp, 1, lbr_tx_exp, 0, 5, 7)
    end

    test "Check TLV without CRC32 error." do
    t_i("Transmit valid LBR frame against VOE - With Test TLV with no CRC32 error")
    #lbr_test_tlv_pdu_create(level, trans_id, error)
    frametx = frameuctx.dup + lbr_test_tlv_pdu_create(level, 8, false)
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
    lbr_rx_exp += 1
    oam_rx_exp += 1

    t_i("Check LBR PDU seen")
    check_pdu_seen(voe_idx, PDU_LBR)

     t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, lbr_tx_exp-1, 2, 1, 0, 0)

    t_i("Check CRC counters in VOE")
    #check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm, tx_trans=LBM_TRANSACTION_ID_NONE, rx_trans=LBM_TRANSACTION_ID_NONE, rx_crc=0)
    check_voe_lb_counters(voe_idx, lbr_rx_exp, 1, lbr_tx_exp, 0, 5, 8, 0)
    end

    test "Check TLV with CRC32 error." do
    t_i("Transmit valid LBR frame against VOE - With Test TLV with CRC32 error")
    #lbr_test_tlv_pdu_create(level, trans_id, error)
    frametx = frameuctx.dup + lbr_test_tlv_pdu_create(level, 9, true)
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
    lbr_rx_exp += 1
    oam_rx_exp += 1

    t_i("Check LBR PDU seen")
    check_pdu_seen(voe_idx, PDU_LBR)

     t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, lbr_tx_exp-1, 2, 1, 0, 0)

    t_i("Check CRC counters in VOE")
    #check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm, tx_trans=LBM_TRANSACTION_ID_NONE, rx_trans=LBM_TRANSACTION_ID_NONE, rx_crc=0)
    check_voe_lb_counters(voe_idx, lbr_rx_exp, 1, lbr_tx_exp, 0, 5, 9, 1)
    end

    test "Check LBM copy to CPU." do
    t_i("LB enable test - no count as selected - LBM to CPU")
    #voe_lb_config(voe_idx, enable, count_as_selected, trans_id, lbm_copy = false)
    voe_lb_config(voe_idx, true, false, 0, true)

    t_i("Transmit valid LBM frame against VOE")
    frametx = framemc.dup + lb_pdu_create(level, 3, 5)
    frame_tx(frametx, $port0, framerx, "", "", rx_ifh + frametx)
    end

    end
end

def voe_lb_inject_test_func(voe_idx, level, tag_vid)
    test "voe_lb_inject_test_func  voe_idx #{voe_idx}  level #{level}  tag_vid #{tag_vid}" do

    port_domain = (tag_vid == 0) ? true : false

    t_i("Before injecting LBM. Clear events and counters")
    check_voe_event(voe_idx, [EVENT_CLEAR])
    check_pdu_seen(voe_idx, PDU_CLEAR)
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    t_i("Create frame")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    lb_pdu = lb_pdu_create(level, 3, 0)

    iflow = $cap_oam_v2 ? (port_domain ? $p_inj_iflow : 0) : (port_domain ? 0 : $inj_iflow)
    vid = port_domain ? $pvid : tag_vid
    frametx = tx_ifh_create(vid, $ts.dut.port_list[$port0], "MESA_PACKET_OAM_TYPE_LBM", false, false, iflow) + frame_create(MC_STRING, SC_STRING) + lb_pdu.dup

    test "Check no LB handling." do
    t_i("LB disable test")
    #voe_lb_config(voe_idx, enable, count_as_selected, trans_id, lbm_copy = false)
    voe_lb_config(voe_idx, false, false, 0)

    t_i("Inject two LBM frame.")
    framerx = frame.dup + lb_pdu.dup
    frame_tx(frametx, $npi_port, framerx , "", "", "")
    frame_tx(frametx, $npi_port, framerx , "", "", "")
    end

    test "Check LB handling." do
    t_i("LB enable test")
    #voe_lb_config(voe_idx, enable, count_as_selected, trans_id, lbm_copy = false)
    voe_lb_config(voe_idx, true, false, 5)

    t_i("Inject two LBM frame.")
    framerx = frame.dup + lb_pdu_create(level, 3, 5)
    frame_tx(frametx, $npi_port, framerx , "", "", "")
    framerx = frame.dup + lb_pdu_create(level, 3, 6)
    frame_tx(frametx, $npi_port, framerx , "", "", "")

    t_i("Check LB counters in VOE")
    #check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm, tx_trans=LBM_TRANSACTION_ID_NONE, rx_trans=LBM_TRANSACTION_ID_NONE)
    check_voe_lb_counters(voe_idx, 0, 0, 0, 2, 7, 5-1)  #Expected Rx transaction id is configured one lower than Tx 
    end
    end
end

def voe_lt_rx_test_func(voe_idx, level, tag_vid)
    test "voe_lt_rx_test_func  voe_idx #{voe_idx}  level #{level}  tag_vid #{tag_vid}" do

    oam_rx_exp = 0

    t_i("Before transmitting LTM. Clear events, status and counters")
    check_voe_event(voe_idx, [EVENT_CLEAR])
    check_pdu_seen(voe_idx, PDU_CLEAR)
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    t_i("Create frame")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    rx_ifh = rx_ifh_create()

    test "Check no LT handling." do
    t_i("LT disable test")
    #voe_lt_config(voe_idx, enable, count_as_selected)
    voe_lt_config(voe_idx, false, false)

    t_i("Transmit valid LTM frame against VOE")
    frametx = frame.dup + lt_pdu_create(level, 5, 0)
    frame_tx(frametx, $port0, "", "", "", "")
    oam_rx_exp += 1

    t_i("Check LTM PDU seen")
    check_pdu_seen(voe_idx, PDU_LTM)

    t_i("Transmit valid LTR frame against VOE")
    frametx = frame.dup + lt_pdu_create(level, 4, 0)
    frame_tx(frametx, $port0, "", "", "", "")
    oam_rx_exp += 1

    t_i("Check LTR PDU seen")
    check_pdu_seen(voe_idx, PDU_LTR)
    end

    test "Check LT handling." do
    t_i("LT enable test - no count as selected")
    voe_lt_config(voe_idx, true, false)

    t_i("Transmit valid LTM frame against VOE")
    frametx = frame.dup + lt_pdu_create(level, 5, 0)
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
    oam_rx_exp += 1

    t_i("Check LTM PDU seen")
    check_pdu_seen(voe_idx, PDU_LTM)

    t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, 0, 0, 0, 0, 0)

    t_i("Transmit valid LTR frame against VOE")
    frametx = frame.dup + lt_pdu_create(level, 4, 0)
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)
    oam_rx_exp += 1

    t_i("Check LTR PDU seen")
    check_pdu_seen(voe_idx, PDU_LTR)

    t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, oam_rx_exp, 0, 0, 0, 0, 0)
    end

    test "Check count as selected." do
    t_i("LT enable test - count as selected")
    voe_lt_config(voe_idx, true, true)

    t_i("Transmit valid LTR frame against VOE")
    frametx = frame.dup + lt_pdu_create(level, 4, 0)
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)

    t_i("Transmit valid LTM frame against VOE")
    frametx = frame.dup + lt_pdu_create(level, 5, 0)
    frame_tx(frametx, $port0, "", "", "", rx_ifh + frametx)

    t_i("Check Rx and Selected counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)

    check_voe_counters(voe_idx, oam_rx_exp, 0, 2, 0, 0, 0)
    end

    end
end

def voi_raps_rx_test_func(voi_idx, level, tag_vid, isdx, res_port, in_port, out_port)
    test "voi_raps_rx_test_func  voi_idx #{voi_idx}  level #{level}  tag_vid #{tag_vid}  isdx #{isdx}  res_port #{res_port}  in_port #{in_port}  out_port #{out_port}" do

    up = (res_port != in_port) ? true : false

    t_i("Create frame")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    frametx = frame.dup + raps_pdu_create(level, 0x07)   # Manuel request
    rx_ifh = rx_ifh_create(isdx, $ts.dut.port_list[res_port])

    test "Check RAPS discard." do
    voi_raps_config(voi_idx, "MESA_OAM_RAPS_HANDLING_DISCARD")

    t_i("Transmit valid RAPS frame against VOI")
    frame_tx(frametx, in_port, "", "", up ? frametx : "", "")
    end

    test "Check RAPS copy to CPU." do
    voi_raps_config(voi_idx, "MESA_OAM_RAPS_HANDLING_COPY_CPU")

    t_i("Transmit valid RAPS frame against VOI. Receive copied RAPS frame from NPI port")
    frame_tx(frametx, in_port, (out_port == $port0) ? frametx : "", (out_port == $port1) ? frametx : "", (out_port == $port2) ? frametx : frametx, rx_ifh + frametx)
    end

    test "RAPS redirect to CPU" do
    voi_raps_config(voi_idx, "MESA_OAM_RAPS_HANDLING_REDIR_CPU")

    t_i("Transmit valid RAPS frame against VOI")
    frame_tx(frametx, in_port, "", "", up ? frametx : "", rx_ifh + frametx)
    end

    test "RAPS no handling" do
    voi_raps_config(voi_idx, "MESA_OAM_RAPS_HANDLING_NONE")

    t_i("Transmit valid RAPS frame against VOI")
    frame_tx(frametx, in_port, (out_port == $port0) ? frametx : "", (out_port == $port1) ? frametx : "", (out_port == $port2) ? frametx : frametx, "")
    end

    end
end

def voi_raps_inject_test_func(voi_idx, level, tag_vid, up)
    test "voi_raps_inject_test_func  voi_idx #{voi_idx}  level #{level}  tag_vid #{tag_vid}  up #{up}" do

    t_i("Create tx and rx frames")
    raps_pdu = raps_pdu_create(level, 0x07)
    iflow = 0   # Never port domain
    frametx = tx_ifh_create(tag_vid, $ts.dut.port_list[$port0], "MESA_PACKET_OAM_TYPE_CCM", true, up, iflow) + frame_create(MC_STRING, SC_STRING) + raps_pdu.dup
    framerx = frame_create(MC_STRING, SC_STRING, tag_vid) + raps_pdu.dup

    t_i("Inject RAPS frame. Receive RAPS frame from front ports")
    frame_tx(frametx, $npi_port, !up ? framerx : "", up ? framerx : "", up ? framerx : "", "")

    end
end

def voi_lbm_ltm_rx_test_func(voi_idx, level, tag_vid, opcode, up)
    test "voi_lbm_ltm_rx_test_func  voe_idx #{voi_idx}  level #{level}  tag_vid #{tag_vid}  opcode #{opcode}  up #{up}" do

    lbm = (opcode == 3) ? true : false

    t_i("Create frame")
    frame = frame_create(lbm ? UC_STRING : MC_STRING, SC_STRING, tag_vid)
    frametx = frame.dup + (lbm ? lb_pdu_create(level, opcode, 0) : lt_pdu_create(level, opcode, 0))
    rx_ifh = rx_ifh_create()

    test "Check no LBM/LTM handling." do
    if (lbm)
        t_i("LBM copy CPU disable test")
        voi_lbm_config(voi_idx, false)
    else
        t_i("LTM copy CPU disable test")
        voi_ltm_config(voi_idx, false)
    end

    t_i("Transmit valid " + (lbm ? "LBM " : "LTM ") + "frame against VOI")
    frame_tx(frametx, up ? $port1 : $port0,  up ? frametx : "", !up ? frametx : "", frametx, "")
    end

    test "Check LBM/LTM handling." do
    if (lbm)
        t_i("LBM copy CPU enable test")
        voi_lbm_config(voi_idx, true)
    else
        t_i("LTM copy CPU enable test")
        voi_ltm_config(voi_idx, true)
    end

    t_i("Transmit valid " + (lbm ? "LBM " : "LTM ") + "frame against VOI")
    frame_tx(frametx, up ? $port1 : $port0,  "", "", up ? frametx : "", rx_ifh + frametx)
    end
    end
end

def voe_rx_test_func(voe_idx, level, tag_vid)
    test "voe_rx_test_func  voe_idx #{voe_idx}  level #{level}  tag_vid #{tag_vid}" do

    rx_discard_cnt = 0
    rx_oam_cnt = 0

    t_i("Before transmitting Frames. Clear events, status and counters")
    check_voe_event(voe_idx, [EVENT_CLEAR])
    check_pdu_seen(voe_idx, PDU_CLEAR)
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    #voe_config_change(voe_idx, dmac_check, mel_high)
    voe_config_change(voe_idx, "MESA_VOE_DMAC_CHECK_BOTH", false)

    t_i("Create frame")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    frameuctx = frame_create(UC_STRING, SC_STRING, tag_vid)
    frameucrx = frame_create(SC_STRING, UC_STRING, tag_vid)
    lbm_pdu = lb_pdu_create(level, 3, 5)

    if ($cap_oam_v2 && (tag_vid == 0))
        test "Check Block high MEL." do
        t_i("Transmit high level CCM frame against VOE without block of high MEL")
        frametx = frame.dup + ccm_pdu_create(level+1, $period, 0, $peer_mepid, $megid)
        frame_tx(frametx, $port0, "", frametx, frametx, "")

        t_i("Check no PDU seen")
        check_pdu_seen(voe_idx, PDU_NONE)

        #voe_config_change(voe_idx, dmac_check, mel_high)
        voe_config_change(voe_idx, "MESA_VOE_DMAC_CHECK_BOTH", true)

        t_i("Transmit high level CCM frame against VOE block of high MEL. Receive forwarded CCM frame from front port is not expected")
        frame_tx(frametx, $port0, "", "", "", "")

        t_i("Check High level PDU seen")
        check_pdu_seen(voe_idx, PDU_HIGH_LEVEL)
    
        t_i("Check Rx discard and OAM counters")
        #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
        check_voe_counters(voe_idx, 0, 0, 0, 0, 1, 0)

        #voe_config_change(voe_idx, dmac_check, mel_high)
        voe_config_change(voe_idx, "MESA_VOE_DMAC_CHECK_BOTH", false)

        clear_all_counters(voe_idx, OAM_CNT_ALL)
        end
    end

    test "Check Unexpected opcode." do
    t_i("Transmit unexpected Opcode frame against VOE")
    frametx = frame.dup + unexpected_pdu_create(level, 60)
    frame_tx(frametx, $port0, "", "", "", "")
    rx_oam_cnt += 1

    t_i("Check unexpected Opcode PDU seen")
    check_pdu_seen(voe_idx, PDU_OPCODE)

    t_i("Check Rx discard and OAM counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, rx_oam_cnt, 0, 0, 0, 0, 0)
    end

    if ($cap_oam_v2)
        test "Check Unexpected version." do
        t_i("Transmit unexpected Version LBM frame against VOE")
        frametx = frame.dup + unexpected_pdu_create(level, 3, 2)
        frame_tx(frametx, $port0, "", "", "", "")
        rx_discard_cnt += 1

        t_i("Check unexpected Version PDU seen")
        check_pdu_seen(voe_idx, PDU_VERSION)

        t_i("Transmit unexpected Version CCM frame against VOE")
        frametx = frame.dup + ccm_pdu_create(level, $period, 0, $peer_mepid, $megid, 0, 2)
        frame_tx(frametx, $port0, "", "", "", "")
        rx_discard_cnt += 1

        t_i("Check unexpected Version PDU seen")
        check_pdu_seen(voe_idx, PDU_VERSION)

        t_i("Check Rx discard and OAM counters")
        #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
        check_voe_counters(voe_idx, rx_oam_cnt, 0, 0, 0, rx_discard_cnt, 0)
        end
    end

    rx_discard_cnt = 0
    rx_oam_cnt = 0
    clear_all_counters(voe_idx, OAM_CNT_ALL)

    t_i("LB enable")
    voe_lb_config(voe_idx, true, false, 5)

    test "Check check and allow both Unicast and Multicast MAC test." do
    t_i("Create frame with invalid Multicast MAC")
    frame = frame_create(MC_STRING_INV, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with invalid MC MAC")
    frametx = frame.dup + lbm_pdu.dup
    frame_tx(frametx, $port0, "", "", "", "")
    rx_discard_cnt += 1

    t_i("Check Invalid DMAC PDU seen")
    check_pdu_seen(voe_idx, PDU_DMAC)

    t_i("Create frame with invalid Unicast MAC")
    frame = frame_create(UC_STRING_INV, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with invalid UC MAC")
    frametx = frame.dup + lbm_pdu.dup
    frame_tx(frametx, $port0, "", "", "", "")
    rx_discard_cnt += 1

    t_i("Check Invalid DMAC PDU seen")
    check_pdu_seen(voe_idx, PDU_DMAC)
    end

    test "Check check and allow only Unicast MAC." do
    #voe_config_change(voe_idx, dmac_check, mel_high)
    voe_config_change(voe_idx, "MESA_VOE_DMAC_CHECK_UNICAST", false)

    t_i("Create frame with valid Multicast MAC")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with valid MC MAC")
    frametx = frame.dup + lbm_pdu.dup
    frame_tx(frametx, $port0, "", "", "", "")
    rx_discard_cnt += 1

    t_i("Check valid LBR PDU seen")
    check_pdu_seen(voe_idx, PDU_DMAC)

    t_i("Create frame with invalid Multicast MAC")
    frame = frame_create(MC_STRING_INV, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with invalid MC MAC")
    frametx = frame.dup + lbm_pdu.dup
    frame_tx(frametx, $port0, "", "", "", "")
    rx_discard_cnt += 1

    t_i("Check valid LBR PDU seen")
    check_pdu_seen(voe_idx, PDU_DMAC)

    t_i("Check Rx discard and OAM counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, rx_oam_cnt, 0, 0, 0, rx_discard_cnt, 0)

    t_i("Create frame with invalid Unicast MAC")
    frame = frame_create(UC_STRING_INV, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with invalid UC MAC")
    frametx = frame.dup + lbm_pdu.dup
    frame_tx(frametx, $port0, "", "", "", "")
    rx_discard_cnt += 1

    t_i("Check Invalid DMAC PDU seen")
    check_pdu_seen(voe_idx, PDU_DMAC)

    t_i("Transmit valid LBM frame against VOE with valid UC MAC")
    frametx = frameuctx.dup + lbm_pdu.dup
    framerx = frameucrx.dup + lb_pdu_create(level, 2, 5)
    frame_tx(frametx, $port0, framerx, "", "", "")
    rx_oam_cnt += 1

    t_i("Check LBM PDU seen")
    check_pdu_seen(voe_idx, PDU_LBM)
    end

    test "Check check and allow only Multicast MAC." do
    #voe_config_change(voe_idx, dmac_check, mel_high)
    voe_config_change(voe_idx, "MESA_VOE_DMAC_CHECK_MULTICAST", false)

    t_i("Create frame with valid Unicast MAC")
    frame = frame_create(UC_STRING, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with valid UC MAC")
    frametx = frame.dup + lbm_pdu.dup
    frame_tx(frametx, $port0, "", "", "", "")
    rx_discard_cnt += 1

    t_i("Check valid LBR PDU seen")
    check_pdu_seen(voe_idx, PDU_DMAC)

    t_i("Create frame with invalid Unicast MAC")
    frame = frame_create(UC_STRING_INV, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with invalid UC MAC")
    frametx = frame.dup + lbm_pdu.dup
    frame_tx(frametx, $port0, "", "", "", "")
    rx_discard_cnt += 1

    t_i("Check valid LBR PDU seen")
    check_pdu_seen(voe_idx, PDU_DMAC)

    t_i("Check Rx discard counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, rx_oam_cnt, rx_oam_cnt, 0, 0, rx_discard_cnt, 0)

    t_i("Create frame with invalid Multicast MAC")
    frame = frame_create(MC_STRING_INV, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with invalid MC MAC")
    frametx = frame.dup + lbm_pdu.dup
    frame_tx(frametx, $port0, "", "", "", "")
    rx_discard_cnt += 1

    t_i("Check Invalid DMAC PDU seen")
    check_pdu_seen(voe_idx, PDU_DMAC)

    t_i("Create frame with valid Multicast MAC")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)

    t_i("Transmit valid LBM frame against VOE with valid MC MAC")
    frametx = frame.dup + lbm_pdu.dup
    framerx = frameucrx.dup + lb_pdu_create(level, 2, 5)
    frame_tx(frametx, $port0, framerx, "", "", "")
    rx_oam_cnt += 1

    t_i("Check LBM PDU seen")
    check_pdu_seen(voe_idx, PDU_LBM)

    t_i("Check Rx discard and OAM counters")
    #check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    check_voe_counters(voe_idx, rx_oam_cnt, rx_oam_cnt, 0, 0, rx_discard_cnt, 0)

    #voe_config_change(voe_idx, dmac_check, mel_high)
    voe_config_change(voe_idx, "MESA_VOE_DMAC_CHECK_BOTH", false)
    end

    end
end

def voi_handled_opcode_test_func(voi_idx, level, frame, opcode, up)
    test "voi_handled_opcode_test_func  voi_idx #{voi_idx}  level #{level}  opcode #{opcode}  up #{up}" do

    t_i("Check Opcode is not handled")
    t_i("Transmit OAM frame against VOI")
    frametx = frame.dup + lb_pdu_create(level, opcode, 0)
    frame_tx(frametx, up ? $port1 : $port0,  up ? frametx : "", !up ? frametx : "", frametx, "")

    end
end

def voi_handled_test_func(voi_idx, level, tag_vid, up)
    test "voi_handled_test_func  voe_idx #{voi_idx}  level #{level}  tag_vid #{tag_vid}  up #{up}" do

    t_i("Configure VOI to handle LBM - LTM - RAPS")
    voi_lbm_config(voi_idx, true)
    voi_ltm_config(voi_idx, true)
    voi_raps_config(voi_idx, "MESA_OAM_RAPS_HANDLING_DISCARD")

    t_i("Create Unicast frame")
    frame = frame_create(UC_STRING_INV, SC_STRING, tag_vid)

    voi_handled_opcode_test_func(voi_idx, level, frame, 3, up)  # LBM
    voi_handled_opcode_test_func(voi_idx, level, frame, 46, up) # DMR
    voi_handled_opcode_test_func(voi_idx, level, frame, 37, up) # TST

    t_i("Create Multicast frame")
    frame = frame_create(MC_STRING, SC_STRING, tag_vid)
    voi_handled_opcode_test_func(voi_idx, level, frame, 55, up) # SLM
    voi_handled_opcode_test_func(voi_idx, level, frame, 1, up)  # CCM

    end
end

#---------- Test execution ----------------------------------------------------

#binding.pry

test "test_config" do
    # Flush MAC table
    $ts.dut.call("mesa_mac_table_flush")

    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

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
    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$port0])
    $vlan_port_conf_restore0 = conf.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port0], conf)

    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$port1])
    $vlan_port_conf_restore1 = conf.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port1], conf)

    conf = $ts.dut.call("mesa_vlan_port_conf_get", $ts.dut.port_list[$port2])
    $vlan_port_conf_restore2 = conf.dup
    conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
    conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port2], conf)

    # Set VLAN memberships
    port_list = "#{$ts.dut.port_list[$port0]},#{$ts.dut.port_list[$port1]},#{$ts.dut.port_list[$port2]}"
    $ts.dut.call("mesa_vlan_port_members_set", $vid, port_list)
    port_list = "#{$ts.dut.port_list[$port0]},#{$ts.dut.port_list[$port1]},#{$ts.dut.port_list[$port2]}"
    $ts.dut.call("mesa_vlan_port_members_set", 1, port_list)   #Also enable forwarding on PVID

    # Set Port default QOS ID
    $qos_conf_restore0 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.port_list[$port0])
    conf = $qos_conf_restore0.dup
    conf["cosid"] = $prio
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.port_list[$port0], conf)
    $qos_conf_restore1 = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.port_list[$port1])
    conf = $qos_conf_restore1.dup
    conf["cosid"] = $prio
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.port_list[$port1], conf)

    # Set VOP configuration
    vop_config($cpu_queue)

    # Allocate Port VOE
    $p_voe_idx = voe_alloc("MESA_VOE_TYPE_PORT", $ts.dut.port_list[$port0]);

    # Allocate Port VOE "behind" the VLAN Down-VOE
    $p1_voe_idx = voe_alloc("MESA_VOE_TYPE_PORT", $ts.dut.port_list[$port1]);

    if ($cap_vop_cfm)
        # Allocate VLAN Down VOE
        $d_voe_idx = voe_alloc("MESA_VOE_TYPE_SERVICE", $ts.dut.port_list[$port0]);
    end

    if ($cap_oam_v2)
        # Allocate VOIs
        $d_voi_idx = voi_alloc("MESA_OAM_DIRECTION_DOWN", $port0)
        $u_voi_idx = voi_alloc("MESA_OAM_DIRECTION_UP", $port0)
    end

    $p_voe_iflow = IFLOW_ID_NONE
    $p1_voe_iflow = IFLOW_ID_NONE
    if ($cap_oam_v2)
        # Allocate iflow's
        $p_voe_iflow = $ts.dut.call("mesa_iflow_alloc")
        $p1_voe_iflow = $ts.dut.call("mesa_iflow_alloc")
        $d_vo_iflow = $ts.dut.call("mesa_iflow_alloc")
        $u_voi_iflow = $ts.dut.call("mesa_iflow_alloc")
        $p_inj_iflow = $p_voe_iflow
        $p1_inj_iflow = $p1_voe_iflow

        # Allocate eflow
        $inj_eflow = $ts.dut.call("mesa_eflow_alloc")
        $p_inj_eflow = $ts.dut.call("mesa_eflow_alloc")
        $p1_inj_eflow = $ts.dut.call("mesa_eflow_alloc")

        # Configure iflow's
        iflow_config($p_voe_iflow, $p_voe_idx, VOI_IDX_NONE)
        iflow_config($p1_voe_iflow, $p1_voe_idx, VOI_IDX_NONE)
        iflow_config($d_vo_iflow, $d_voe_idx, $d_voi_idx)
        iflow_config($u_voi_iflow, VOE_IDX_NONE, VOI_IDX_NONE)

        # Configure eflow's
        eflow_config($inj_eflow, $d_voe_idx, $u_voi_idx)
        eflow_config($p_inj_eflow, $p_voe_idx, VOI_IDX_NONE)
        eflow_config($p1_inj_eflow, $p1_voe_idx, VOI_IDX_NONE)
    end

    if ($cap_oam_v1)
        # Allocate iflow's
        $p_voe_iflow = $ts.dut.call("mesa_iflow_alloc")
        $p1_voe_iflow = $ts.dut.call("mesa_iflow_alloc")
        $d_voe_iflow = $ts.dut.call("mesa_iflow_alloc")
        $inj_iflow = $d_voe_iflow

        # Allocate eflow
        $inj_eflow = $ts.dut.call("mesa_eflow_alloc")

        # Configure iflow's
        iflow_config($p_voe_iflow, $p_voe_idx, VOI_IDX_NONE)
        iflow_config($p1_voe_iflow, $p1_voe_idx, VOI_IDX_NONE)
        iflow_config($d_voe_iflow, $d_voe_idx, VOI_IDX_NONE)

        # Configure eflow's
        eflow_config($inj_eflow, $d_voe_idx, VOI_IDX_NONE)
    end

    if ($cap_oam_v2)
        # Configure VCE
        #vce_config(id, port, vid, level_val, level_mask, flow_id, oam_detect)
        vce_config($p_vce, "#{$ts.dut.port_list[$port0]}", 0, 0, 0, $p_voe_iflow, "MESA_OAM_DETECT_UNTAGGED")
        vce_config($d_vo_vce, "#{$ts.dut.port_list[$port0]}", $vid, 0, 0, $d_vo_iflow, "MESA_OAM_DETECT_SINGLE_TAGGED")
        vce_config($p1_vce, "#{$ts.dut.port_list[$port1]}", 0, 0, 0, $p1_voe_iflow, "MESA_OAM_DETECT_UNTAGGED")
        vce_config($u_voi_vce, "#{$ts.dut.port_list[$port1]},#{$ts.dut.port_list[$port2]}", $vid, 0, 0, $u_voi_iflow, "MESA_OAM_DETECT_SINGLE_TAGGED")
        vce_config($p2_vce, "#{$ts.dut.port_list[$port2]}", 0, 0, 0, IFLOW_ID_NONE, "MESA_OAM_DETECT_UNTAGGED")
        vce_config($p2_v_vce, "#{$ts.dut.port_list[$port2]}", $vid, 0, 0, IFLOW_ID_NONE, "MESA_OAM_DETECT_SINGLE_TAGGED")

        # Configure TCE
        #tce_config(id, port, vid, iflow_id, eflow_id)
        tce_config($inj_tce, $ts.dut.port_list[$port0], $vid, IFLOW_ID_NONE, $inj_eflow)
        tce_config($p_inj_tce, $ts.dut.port_list[$port0], 0, $p_inj_iflow, $p_inj_eflow)
        tce_config($p1_inj_tce, $ts.dut.port_list[$port1], 0, $p1_inj_iflow, $p1_inj_eflow)
        tce_config($p_blk_tce, $ts.dut.port_list[$port0], $pvid, IFLOW_ID_NONE, $p_inj_eflow)
        tce_config($p1_blk_tce, $ts.dut.port_list[$port1], $pvid, IFLOW_ID_NONE, $p1_inj_eflow)
    end

    if ($cap_oam_v1)
        # Configure VCE
        #vce_config(id, port, vid, level_val, level_mask, flow_id, oam_detect)
        vce_config($p_vce, "#{$ts.dut.port_list[$port0]}", 0, 0, 0, $p_voe_iflow, "MESA_OAM_DETECT_UNTAGGED")   #Always match on all levels in port domain
        vce_config($d_voe_vce, "#{$ts.dut.port_list[$port0]}", $vid, 0, vce_level_mask(0, $v_voe_meg_level), $d_voe_iflow, "MESA_OAM_DETECT_SINGLE_TAGGED")
        vce_config($p1_vce, "#{$ts.dut.port_list[$port1]}", 0, 0, 0, $p1_voe_iflow, "MESA_OAM_DETECT_UNTAGGED")   #Always match on all levels in port domain
        vce_config($d_voe_mel_vce, "#{$ts.dut.port_list[$port1]},#{$ts.dut.port_list[$port2]}", $vid, 0, 0, IFLOW_ID_NONE, "MESA_OAM_DETECT_SINGLE_TAGGED")
        vce_config($p2_vce, "#{$ts.dut.port_list[$port2]}", 0, 0, 0, IFLOW_ID_NONE, "MESA_OAM_DETECT_UNTAGGED")

        # Configure TCE
        #tce_config(id, port, vid, iflow_id, eflow_id)
        tce_config($d_voe_tce, $ts.dut.port_list[$port0], $vid, IFLOW_ID_NONE, $inj_eflow)
        tce_config($inj_tce, $ts.dut.port_list[$port0], $vid, $inj_iflow, $inj_eflow)
    end

    # Configure VOE
    #voe_config(voe_idx, meg_level, iflow_id)
    voe_config($p_voe_idx, $p_voe_meg_level, $p_voe_iflow)
    voe_config($p1_voe_idx, $p_voe_meg_level, $p1_voe_iflow)
    if ($cap_oam_v1)
        voe_config($d_voe_idx, $v_voe_meg_level, $inj_iflow)
    end
    if ($cap_oam_v2)
        voe_config($d_voe_idx, $v_voe_meg_level, IFLOW_ID_NONE)
    end

    if ($cap_oam_v2)
        # Configure VOI
        #voi_config(voi_idx, meg_level)
        voi_config($d_voi_idx, $voi_meg_level)
        voi_config($u_voi_idx, $voi_meg_level)
    end
end

test "test_run" do
    voe_cc_rx_test_func($p_voe_idx, $p_voe_meg_level, 0)
    voe_cc_inject_test_func($p_voe_idx, $p_voe_meg_level, 0)
    voe_cc_block_test_func($p_voe_idx, $p_voe_meg_level, 0)
    if ($cap_vop_cfm)
        voe_cc_rx_test_func($d_voe_idx, $v_voe_meg_level, $vid)
        voe_cc_inject_test_func($d_voe_idx, $v_voe_meg_level, $vid)
        voe_cc_block_test_func($d_voe_idx, $v_voe_meg_level, $vid)
        voe_laps_rx_test_func($p_voe_idx, $p_voe_meg_level, 0, $p_voe_iflow, $port0)
        if ($cap_oam_v2)
            voe_laps_rx_test_func($d_voe_idx, $v_voe_meg_level, $vid, $d_vo_iflow, $port0)
        end
        if ($cap_oam_v1)
            voe_laps_rx_test_func($d_voe_idx, $v_voe_meg_level, $vid, $d_voe_iflow, $port0)
        end
        voe_lb_rx_test_func($p_voe_idx, $p_voe_meg_level, 0)
        voe_lb_rx_test_func($d_voe_idx, $v_voe_meg_level, $vid)
        voe_lb_inject_test_func($p_voe_idx, $p_voe_meg_level, 0)
        voe_lb_inject_test_func($d_voe_idx, $v_voe_meg_level, $vid)
        voe_lt_rx_test_func($p_voe_idx, $p_voe_meg_level, 0)
        voe_lt_rx_test_func($d_voe_idx, $v_voe_meg_level, $vid)
        voe_rx_test_func($p_voe_idx, $p_voe_meg_level, 0)
        voe_rx_test_func($d_voe_idx, $v_voe_meg_level, $vid)

        if ($cap_oam_v2)
            voi_raps_rx_test_func($d_voi_idx, $voi_meg_level, $vid, $d_vo_iflow, $port0, $port0, $port1)
            voi_raps_rx_test_func($u_voi_idx, $voi_meg_level, $vid, $u_voi_iflow, $port0, $port1, $port0)
            voi_raps_inject_test_func($d_voi_idx, $voi_meg_level, $vid, false)
            voi_raps_inject_test_func($u_voi_idx, $voi_meg_level, $vid, true)
            voi_lbm_ltm_rx_test_func($d_voi_idx, $voi_meg_level, $vid, 3, false)
            voi_lbm_ltm_rx_test_func($u_voi_idx, $voi_meg_level, $vid, 3, true)
            voi_lbm_ltm_rx_test_func($d_voi_idx, $voi_meg_level, $vid, 5, false)
            voi_lbm_ltm_rx_test_func($u_voi_idx, $voi_meg_level, $vid, 5, true)
            voi_handled_test_func($d_voi_idx, $voi_meg_level, $vid, false)
            voi_handled_test_func($u_voi_idx, $voi_meg_level, $vid, true)
        end
    end
end

test "test_clean_up" do
    if ($cap_oam_v2)
        $ts.dut.call("mesa_iflow_free", $p_voe_iflow)
        $ts.dut.call("mesa_iflow_free", $p1_voe_iflow)
        $ts.dut.call("mesa_iflow_free", $d_vo_iflow)
        $ts.dut.call("mesa_iflow_free", $u_voi_iflow)

        $ts.dut.call("mesa_eflow_free", $inj_eflow)
        $ts.dut.call("mesa_eflow_free", $p_inj_eflow)
        $ts.dut.call("mesa_eflow_free", $p1_inj_eflow)

        $ts.dut.call("mesa_vce_del", $p_vce)
        $ts.dut.call("mesa_vce_del", $p1_vce)
        $ts.dut.call("mesa_vce_del", $p2_vce)
        $ts.dut.call("mesa_vce_del", $p2_v_vce)
        $ts.dut.call("mesa_vce_del", $d_vo_vce)
        $ts.dut.call("mesa_vce_del", $u_voi_vce)

        $ts.dut.call("mesa_tce_del", $inj_tce)
        $ts.dut.call("mesa_tce_del", $p_inj_tce)
        $ts.dut.call("mesa_tce_del", $p1_inj_tce)
        $ts.dut.call("mesa_tce_del", $p_blk_tce)
        $ts.dut.call("mesa_tce_del", $p1_blk_tce)
    end

    if ($cap_oam_v1)
        $ts.dut.call("mesa_iflow_free", $p_voe_iflow)
        $ts.dut.call("mesa_iflow_free", $p1_voe_iflow)
        $ts.dut.call("mesa_iflow_free", $d_voe_iflow)

        $ts.dut.call("mesa_eflow_free", $inj_eflow)

        $ts.dut.call("mesa_vce_del", $p_vce)
        $ts.dut.call("mesa_vce_del", $d_voe_vce)
        $ts.dut.call("mesa_vce_del", $d_voe_mel_vce)
        $ts.dut.call("mesa_vce_del", $p2_vce)

        $ts.dut.call("mesa_tce_del", $d_voe_tce)
        $ts.dut.call("mesa_tce_del", $inj_tce)
    end

    $ts.dut.call("mesa_voe_free", $p_voe_idx)
    $ts.dut.call("mesa_voe_free", $p1_voe_idx)
    if ($cap_vop_cfm)
        $ts.dut.call("mesa_voe_free", $d_voe_idx)
    end

    if ($cap_oam_v2)
        $ts.dut.call("mesa_voi_free", $d_voi_idx)
        $ts.dut.call("mesa_voi_free", $u_voi_idx)
    end

    # VLAN port configuration restore
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port0], $vlan_port_conf_restore0)
    $ts.dut.call("mesa_vlan_port_conf_set", $ts.dut.port_list[$port1], $vlan_port_conf_restore1)

    # Clear VLAN memberships
    $ts.dut.call("mesa_vlan_port_members_set", $vid, "")

    # CPU queue configuration restore
    $ts.dut.call("mesa_packet_rx_conf_set", $packet_rx_conf_restore)

    # NPI port configuration restore
    $ts.dut.call("mesa_npi_conf_set", $npi_conf_restore)

    # Port default QOS ID restore
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.port_list[$port0], $qos_conf_restore0)
    $ts.dut.call("mesa_qos_port_conf_set", $ts.dut.port_list[$port1], $qos_conf_restore1)
end

