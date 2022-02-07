#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

#require 'pry'
#require_relative 'lib/api_test'
require          'pp'
require_relative 'libeasy/et'
require_relative 'oam_lib'

# Set one of the following RUN_TEST_xxx to 0 if you run this script by hand and
# don't want all tests to execute (because some of them are quite lengthy).
# The entire test (including overhead) takes ~23 minutes (without compilation).
RUN_TEST_FORWARDING = 0 # Takes ~15 minutes
RUN_TEST_TX_MODIF   = 1 # Takes ~ 3 minutes
RUN_TEST_LOC        = 1 # Takes ~ 2 minutes
RUN_TEST_CPU_COPY   = 1 # Takes ~ 3 minutes
RUN_TEST_HITME_ONCE = 1 # Takes ~30 seconds
RUN_TEST_ERROR      = 1 # Takes ~ 2 seconds

$ts = get_test_setup("mesa_pc_b2b_4x")

# Uncomment this if you want trace in the output
# $ts.dut.run("mesa-cmd deb trace api_cil mrp debug")

check_capabilities do
    cap_mrp = $ts.dut.call("mesa_capability", "MESA_CAP_MRP") != 0
    assert(cap_mrp, "MRP capability must be defined, cap_mrp = #{cap_mrp})")

    $cap_mrp_cnt     = $ts.dut.call("mesa_capability", "MESA_CAP_MRP_CNT")
    $cap_cosid       = $ts.dut.call("mesa_capability", "MESA_CAP_QOS_COSID_CLASSIFICATION") != 0
    $cap_vstax       = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_VSTAX")             != 0
    $cap_epid        = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
    $cap_family      = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    $cap_tx_ifh_size = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_TX_IFH_SIZE")
    $cap_port_cnt    = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_CNT")
    t_i("cap_mrp = #{cap_mrp}, cap_mrp_cnt = #{$cap_mrp_cnt}, cap_cosid = #{$cap_cosid}, cap_vstax = #{$cap_vstax}, cap_epid = #{$cap_epid}, cap_family = #{$cap_family}, cap_tx_ifh_size = #{$cap_tx_ifh_size}, cap_port_cnt = #{$cap_port_cnt}")
end

$ring_port1   = 0
$ring_port2   = 1
$ring_port_in = 2
$data_port    = 2
$data_vid     = 200
$cpu_queue    = 7
$pvid         = 1
$mrp_prio     = 4

$port0    = $ring_port1
$port1    = $ring_port2
$port2    = $data_port
$npi_port = 3

$port_map = $ts.dut.call("mesa_port_map_get", $cap_port_cnt)

MESA_MRP_EVENT_MASK_TST_LOC  = 0x01
MESA_MRP_EVENT_MASK_ITST_LOC = 0x02

MRP_SA_REM_LO          = 0x000000000509 # Lower MAC than ourselves
MRP_SA_OWN             = 0x00000000050A # Ourselves
MRP_SA_REM_HI          = 0x00000000050B # Higher MAC than ourselves
MRP_SA_OWN_AS_ARRAY    = [0,0,0,0,5,0xA]
MRP_SA_REM_HI_AS_ARRAY = [0,0,0,0,5,0xB]

# On dk-t33-5, the PC port's names and connections to DUT are:
#   eth5_red    connected to :port1
#   eth5_green  connected to :port2
#   eth5_blue   connected to :ic_port
#   eth5_yellow connected to $npi_port/CPU

# This is the current state of the MRP instance.
$state = {:mra           => false,
          :ring_role     => :mrm,
          :ic_role       => :none,
          :ic_mode       => :lc,
          :forwarding    => {:port1 => true, :port2 => true, :ic_port => true},
          :cpu_copy_conf => {"tst_to_cpu" => false, "itst_to_cpu" => false},

          # Expected counters
          :counters      => {:port1   => {"tst_rx_count" => 0, "itst_rx_count" => 0},
                             :port2   => {"tst_rx_count" => 0, "itst_rx_count" => 0},
                             :ic_port => {"tst_rx_count" => 0, "itst_rx_count" => 0}},
         }

# This is properties about the frame we are about to Tx.
$frm_info = {:frame       => "",
             :rx_ifh      => "",
             :type        => :mrp_test,
             :own_pdu     => true,
             :higher_prio => false,
            }

$port_types = [:port1, :port2, :ic_port]
$ring_roles = [:mrm, :mrc]
$ic_roles   = [:none, :mim, :mic]
$ic_modes   = [:rc, :lc]

def state_print()
    return "mra = #{$state[:mra]}, ring_role = #{$state[:ring_role]}, ic_role = #{$state[:ic_role]}, ic_mode = #{$state[:ic_mode]}, p1_fwd = #{$state[:forwarding][:port1]}, p2_fwd = #{$state[:forwarding][:port2]}, ic_fwd = #{$state[:forwarding][:ic_port]}"
end

def port_type_to_pc_port(port_type)
    return port_type == :port1 ? $ring_port1 : port_type == :port2 ? $ring_port2 : $ring_port_in
end

# This one returns a mesa_port_no_t
def port_type_to_dut_port(port_type)
    pc_port = port_type_to_pc_port(port_type)
    return $ts.dut.port_list[pc_port]
end

def port_type_to_status_field(port_type)
    return port_type == :port1 ? "p_status" : port_type == :port2 ? "s_status" : "i_status"
end

def port_type_to_event_field(port_type)
    return port_type == :port1 ? "p_mask" : port_type == :port2 ? "s_mask" : "i_mask"
end

def port_type_to_counter_field(port_type)
    return port_type == :port1 ? "p_counters" : port_type == :port2 ? "s_counters" : "i_counters"
end

def pdu_type_to_counter_field(pdu_type)
    return pdu_type == :mrp_test ? "tst_rx_count" : "itst_rx_count"
end

def mrp_conf_default()
    $mrp_conf = $ts.dut.call("mesa_mrp_get", 0)
    $mrp_conf["p_port"]      = port_type_to_dut_port(:port1)
    $mrp_conf["s_port"]      = port_type_to_dut_port(:port2)
    $mrp_conf["i_port"]      = port_type_to_dut_port(:ic_port)
    $mrp_conf["mac"]["addr"] = MRP_SA_OWN_AS_ARRAY
end

def mrp_add()
    $mrp_conf["ring_role"]    = $state[:ring_role] == :mrm ? "MESA_MRP_RING_ROLE_MANAGER" : "MESA_MRP_RING_ROLE_CLIENT"
    $mrp_conf["in_ring_role"] = $state[:ic_role]   == :mim ? "MESA_MRP_RING_ROLE_MANAGER" : $state[:ic_role] == :mic ? "MESA_MRP_RING_ROLE_CLIENT" : "MESA_MRP_RING_ROLE_DISABLED"
    $mrp_conf["mra"]          = $state[:mra]
    $mrp_conf["mra_priority"] = $mrp_prio
    $mrp_conf["in_rc_mode"]   = $state[:ic_mode] == :rc ? true : false
    $ts.dut.call("mesa_mrp_add", 0, $mrp_conf)

    # By default, all ports are blocking and all counters are cleared, so
    # reflect that in our $state.
    $port_types.each {|port_type|
        $state[:forwarding][port_type] = false
        [:mrp_test, :mrp_intest].each {|pdu_type|
            $state[:counters][port_type][pdu_type_to_counter_field(pdu_type)] = 0
        }
    }

    # By default, CPU copy conf is false
    $state[:cpu_copy_conf]["tst_to_cpu"]  = false
    $state[:cpu_copy_conf]["itst_to_cpu"] = false
end

def mrp_del()
    $ts.dut.call("mesa_mrp_del", 0)
end

def loc_conf_default()
    $loc_conf = $ts.dut.call("mesa_mrp_tst_loc_conf_get", 0)
    $loc_timeout_sec = 2
end

def loc_conf_set()
    # Set the LoC timeouts so low that this test can keep up the pace.
    # 666666 corresponds to 666.666 milliseconds, and multiplied by 3 gives
    # two seconds.
    interval = 666666
    cnt      = 3
    $loc_timeout_sec = ((interval.to_f() * cnt) / 1000000).round() + 1

    $loc_conf["tst_interval"]   = interval
    $loc_conf["tst_mon_count"]  = cnt
    $loc_conf["itst_interval"]  = interval
    $loc_conf["itst_mon_count"] = cnt
    $ts.dut.call("mesa_mrp_tst_loc_conf_set", 0, $loc_conf)
end

def event_mask_set()
    new_event_mask = MESA_MRP_EVENT_MASK_ITST_LOC | MESA_MRP_EVENT_MASK_TST_LOC
    $ts.dut.call("mesa_mrp_event_mask_set", 0, new_event_mask, true)
    event_mask = $ts.dut.call("mesa_mrp_event_mask_get", 0)
    assert(event_mask == new_event_mask, "Expect #{event_mask} == #{new_event_mask}")
end

def port_state_set(port_type, new_fwd)
    dut_port = port_type_to_dut_port(port_type)

    new_fwd_str = new_fwd ? "MESA_MRP_PORT_STATE_FORWARDING" : "MESA_MRP_PORT_STATE_BLOCKED"
    $ts.dut.call("mesa_mrp_port_state_set", 0, dut_port, new_fwd_str)
    $state[:forwarding][port_type] = new_fwd

    # Check that it actually got set
    fwd_str = $ts.dut.call("mesa_mrp_port_state_get", 0, dut_port)
    assert(fwd_str == new_fwd_str, "Expect #{fwd_str} == #{new_fwd_str}")
end

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
    $vlan_port_conf_restore = Hash.new()
    $port_types.each {|port_type|
        port_no = port_type_to_dut_port(port_type)
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port_no)
        $vlan_port_conf_restore[port_type] = conf.dup()
        conf["port_type"]  = "MESA_VLAN_PORT_TYPE_C"
        conf["frame_type"] = "MESA_VLAN_FRAME_ALL"
        $ts.dut.call("mesa_vlan_port_conf_set", port_no, conf)
    }

    port_list = "#{$ts.dut.port_list[$ring_port1]},#{$ts.dut.port_list[$ring_port2]},#{$ts.dut.port_list[$data_port]}"
    $ts.dut.call("mesa_vlan_port_members_set", $data_vid, port_list) # Enable forwarding of data frames on data VID
    port_list = "#{$ts.dut.port_list[$ring_port1]},#{$ts.dut.port_list[$ring_port2]}"
    $ts.dut.call("mesa_vlan_port_members_set", 1, port_list)         # Enable forwarding of MRP frames on PVID

    vop_config($cpu_queue)
end

# If ingressing an MRP PDU on port_type, where do we expect it to go?
def forwarding_expect(port_type)
    # port_type: :port1, :port2, :ic_port
    p1  = false
    p2  = false
    ic  = false
    cpu = false

    # Counter expectations
    counter_incr = false

    both_ring_ports_forwarding = $state[:forwarding][:port1] && $state[:forwarding][:port2]

    case $frm_info[:type]
    when :mrp_test
        case $state[:ring_role]
        when :mrm
            # Never expect MRP_Test PDUs on ring ports or I/C port.
            # We do, however, expect lower-priority remote MRP_Test PDUs at the
            # CPU whenever we are an MRM configured as an MRA, because we need
            # to send it MRP_TestMgrNAck PDUs back.
            cpu = port_type != :ic_port && $state[:mra] && !$frm_info[:own_pdu] && !$frm_info[:higher_prio]

            # We do also expect remote MRP_Test PDUs to the CPU if asked to with
            # 'tst_to_cpu'.
            cpu = cpu || (port_type != :ic_port && !$frm_info[:own_pdu] && $state[:cpu_copy_conf]["tst_to_cpu"])

            # We expect the Rx counter to increment by one if it's not received
            # on the I/C port.
            counter_incr = port_type != :ic_port

        when :mrc
            # Forwarding through ring ports if both ring ports are forwarding,
            # only. Own MRP_Test PDUs are discarded if we are MRA, only.
            # If received on I/C port, it is discarded.
            p1 = (!$state[:mra] || !$frm_info[:own_pdu]) && both_ring_ports_forwarding && port_type == :port2
            p2 = (!$state[:mra] || !$frm_info[:own_pdu]) && both_ring_ports_forwarding && port_type == :port1

            # We expect the Rx counter to increment by one if it's not received
            # on the I/C port and we are an MRA, where MRP processing is enabled
            counter_incr = port_type != :ic_port && $state[:mra]
        end

    when :mrp_testmgrnack, :mrp_testpropagate
        case $state[:ring_role]
        when :mrm
             # We get these to the CPU if we are an MRM, but not from the I/C
             # port
            cpu = port_type != :ic_port

        when :mrc
            # Forward between ring ports if both are forwarding
            p1 = both_ring_ports_forwarding && port_type == :port2
            p2 = both_ring_ports_forwarding && port_type == :port1

            # We get these to the CPU if we are an MRA, but not from the I/C
            # port
            cpu = port_type != :ic_port && $state[:mra]
        end

    when :mrp_linkchange, :mrp_topologychange
        # Forwarding between ring ports and between ring port and I/C port
        # is identical to MC_TEST PDUs
        p1 = $state[:ring_role] == :mrc && both_ring_ports_forwarding && port_type == :port2
        p2 = $state[:ring_role] == :mrc && both_ring_ports_forwarding && port_type == :port1

        # We always get these frames to the CPU if received on a ring port, but
        # not on the I/C port.
        cpu = port_type != :ic_port

    when :mrp_intest
        case $state[:ic_role]
        when :none
            # MRM/MRC without MIM/MIC
            # Pass these PDUs through the ring ports if both are forwarding.
            # This is whether or not it's our own MRP_InTest PDUs.
            p1 = both_ring_ports_forwarding && port_type == :port2
            p2 = both_ring_ports_forwarding && port_type == :port1

        when :mim
            # MRP_InTest PDUs - whether our own or remote - are not forwarded to
            # any port.
            # We may, however, get remote MRP_InTest PDUs to the CPU if asked to
            # with 'itst_to_cpu'. This only works in MIM-RC mode, because in
            # MIM-LC mode, MRP_InTest processing is not enabled in the chip.
            cpu = !$frm_info[:own_pdu] && $state[:cpu_copy_conf]["itst_to_cpu"] && $state[:ic_mode] == :rc

            # Expect counter to increment when we are a MIM-RC.
            counter_incr = $state[:ic_mode] == :rc

        when :mic
            # When a MIC, we can forward from a ring port to I/C port, but never
            # from ring port to ring port. It doesn't matter whether it's our
            # own (which doesn't make much sense, since we're a MIC) or remote
            # MRP_InTest PDUs, and it doesn't matter whether we are in RC or LC
            # mode.
            # We forward both own and remote MRP_InTest PDUs arriving on the I/C
            # port to forwarding ring ports, only.
            p1 = $state[:forwarding][:port1]   &&  port_type == :ic_port
            p2 = $state[:forwarding][:port2]   &&  port_type == :ic_port
            ic = $state[:forwarding][:ic_port] && (port_type == :port1 || port_type == :port2)
        end

    when :mrp_inlinkchange, :mrp_inlinkstatuspoll, :mrp_intopologychange
        case $state[:ic_role]
        when :none
            # When we are neither a MIM nor a MIC, we pass these PDUs through
            # the ring ports if both are forwarding.
            p1 = both_ring_ports_forwarding && port_type == :port2
            p2 = both_ring_ports_forwarding && port_type == :port1

            # We do want MRP_InTopologyChange PDUs to the CPU if we are an MRM,
            # because the MRM needs to transmit MRP_TopologyChange PDUs on its
            # own ring.
            cpu = $state[:ring_role] == :mrm && $frm_info[:type] == :mrp_intopologychange

        when :mim, :mic
            # When we are a MIM or MIC, we let S/W handle forwarding because H/W
            # cannot handle the embedded interconnection ID (IID).
            # We never let H/W forward them
            cpu = true
        end
    end

    # Update $state[:counters] if we expect it to increment
    if counter_incr
        counter = pdu_type_to_counter_field($frm_info[:type])
        $state[:counters][port_type][counter] += 1
        t_i("Counter increment of $state[:counters][#{port_type}][#{counter}] to #{$state[:counters][port_type][counter]}")
    end

    return p1, p2, ic, cpu
end

def frame_tx_expect(port_type)
    expect = forwarding_expect(port_type)

    t_i("port_type = #{port_type}, pdu = #{$frm_info[:type]}, p1 = #{expect[0]}, p2 = #{expect[1]}, ic = #{expect[2]}, cpu = #{expect[3]}")

    p1  = expect[0] ?                      $frm_info[:frame] : ""
    p2  = expect[1] ?                      $frm_info[:frame] : ""
    ic  = expect[2] ?                      $frm_info[:frame] : ""
    cpu = expect[3] ? $frm_info[:rx_ifh] + $frm_info[:frame] : ""

    # Note about frame_tx():
    #  This is defined in oam_lib.rb and takes the following arguments:
    #  1: The frame to Tx
    #  2: The PC port to transmit on
    #  3, 4, 5, 6: Corresponds to $port0, $port1, $port2, $npi_port (i.e. CPU), respectively.
    #   If " ": Skip check of frame arrival on port
    #   If "":  Check that no frame arrives on port
    #   Else:   Check that the specified frame arrives on port
    frame_tx($frm_info[:frame], port_type_to_pc_port(port_type), p1, p2, ic, cpu)
end

# Test forwarding of MC_TEST PDUs
def forwarding_mc_test(port_type)
    test "forwarding_mc_test(port_type = #{port_type})" do
        # MC_TEST PDUs
        mc_test_frm        = frame_create(MC_TEST, SC_STRING, 0, 0, "mrp")
        $frm_info[:rx_ifh] = rx_ifh_create(IGNORE, port_type_to_dut_port(port_type))
        $frm_info[:type]   = :mrp_test

        test "MRP_Test(own)" do
            $frm_info[:frame]   = mc_test_frm.dup + "mrp_tst t_sa #{MRP_SA_OWN} "
            $frm_info[:own_pdu] = true
            frame_tx_expect(port_type)
        end

        $frm_info[:higher_prio] = false

        test "MRP_Test(rem, lower prio, based on MRP_SA)" do
            # Higher priority is
            # (frm.MRP_Prio < cfg.MRP_Prio) || (frm.MRP_Prio == cfg.MRP_Prio && frm.MRP_SA < cfg.MRP_SA)
            # So lower priority is
            # (cfg.MRP_Prio < frm.MRP_Prio) || (cfg.MRP_Prio == frm.MRP_Prio && cfg.MRP_SA < frm.MRP_SA)
            # So if we want to use the MRP_SA as trigger, we must set the frame's
            # MRP_Prio to our own.
            $frm_info[:frame]   = mc_test_frm.dup + "mrp_tst t_sa #{MRP_SA_REM_HI} t_prio #{$mrp_prio} "
            $frm_info[:own_pdu] = false
            frame_tx_expect(port_type)
        end

        test "MRP_Test(rem, lower prio, based on MRP_Prio)" do
            # Higher priority is
            # (frm.MRP_Prio < cfg.MRP_Prio) || (frm.MRP_Prio == cfg.MRP_Prio && frm.MRP_SA < cfg.MRP_SA)
            # So lower priority is
            # (cfg.MRP_Prio < frm.MRP_Prio) || (cfg.MRP_Prio == frm.MRP_Prio && cfg.MRP_SA < frm.MRP_SA)
            # So if we want to use the MRP_Prio as trigger, we must set the frame's
            # MRP_SA to something lower and MRP_Prio to something higher.
            $frm_info[:frame]   = mc_test_frm.dup + "mrp_tst t_sa #{MRP_SA_REM_LO} t_prio #{$mrp_prio + 1} "
            $frm_info[:own_pdu] = false
            frame_tx_expect(port_type)
        end

        $frm_info[:higher_prio] = true

        test "MRP_Test(rem, higher prio, based on MRP_SA)" do
            $frm_info[:frame]   = mc_test_frm.dup + "mrp_tst t_sa #{MRP_SA_REM_LO} t_prio #{$mrp_prio} "
            $frm_info[:own_pdu] = false
            frame_tx_expect(port_type)
        end

        test "MRP_Test(rem, higher prio, based on MRP_Prio)" do
            $frm_info[:frame]   = mc_test_frm.dup + "mrp_tst t_sa #{MRP_SA_REM_HI} t_prio #{$mrp_prio - 1} "
            $frm_info[:own_pdu] = false
            frame_tx_expect(port_type)
        end

        $frm_info[:type] = :mrp_testmgrnack
        test "MRP_TestMgrNAck" do
            $frm_info[:frame] = mc_test_frm.dup + "mrp_prop_nack t_s_type 1 "
            frame_tx_expect(port_type)
        end

        $frm_info[:type] = :mrp_testpropagate
        test "MRP_TestPropagate" do
            $frm_info[:frame] = mc_test_frm.dup + "mrp_prop_nack t_s_type 2 "
            frame_tx_expect(port_type)
        end
    end
end

# Test forwarding of MC_CONTROL PDUs
def forwarding_mc_control(port_type)
    test "forwarding_mc_control(port_type = #{port_type})" do
        # MC_CONTROL PDUs
        mc_control_frm = frame_create(MC_CONTROL, SC_STRING, 0, 0, "mrp")
        $frm_info[:rx_ifh] = rx_ifh_create(IGNORE, port_type_to_dut_port(port_type))

        test "MRP_LinkChange(Down)" do
            $frm_info[:type]  = :mrp_linkchange
            $frm_info[:frame] = mc_control_frm.dup + "mrp_lnk "
            frame_tx_expect(port_type)
        end

        test "MRP_LinkChange(Up)" do
            $frm_info[:type]  = :mrp_linkchange
            $frm_info[:frame] = mc_control_frm.dup + "mrp_lnk t_type 5 "
            frame_tx_expect(port_type)
        end

        test "MRP_TopologyChange" do
            $frm_info[:type]  = :mrp_topologychange
            $frm_info[:frame] = mc_control_frm.dup + "mrp_topo "
            frame_tx_expect(port_type)
        end
    end
end

# Test forwarding of MC_INTEST PDUs
def forwarding_mc_intest(port_type)
    test "forwarding_mc_intest(port_type = #{port_type})" do
        # MC_intest PDUs
        mc_intest_frm      = frame_create(MC_ITEST, SC_STRING, 0, 0, "mrp")
        $frm_info[:rx_ifh] = rx_ifh_create(IGNORE, port_type_to_dut_port(port_type))
        $frm_info[:type]   = :mrp_intest

        test "MRP_InTest(own)" do
            $frm_info[:frame]   = mc_intest_frm.dup + "mrp_tst t_sa #{MRP_SA_OWN} t_type 6 "
            $frm_info[:own_pdu] = true
            frame_tx_expect(port_type)
        end

        test "MRP_InTest(rem)" do
            $frm_info[:frame]   = mc_intest_frm.dup + "mrp_tst t_sa #{MRP_SA_REM_LO} t_type 6 "
            $frm_info[:own_pdu] = false
            frame_tx_expect(port_type)
        end
    end
end

# Test forwarding of MC_INCONTROL PDUs
def forwarding_mc_incontrol(port_type)
    test "forwarding_mc_incontrol(port_type = #{port_type})" do
        # MC_INCONTROL PDUs
        mc_incontrol_frm   = frame_create(MC_ICONTROL, SC_STRING, 0, 0, "mrp")
        $frm_info[:rx_ifh] = rx_ifh_create(IGNORE, port_type_to_dut_port(port_type))

        test "MRP_InLinkChange(Down)" do
            $frm_info[:type]  = :mrp_inlinkchange
            $frm_info[:frame] = mc_incontrol_frm.dup + "mrp_lnk t_type 8 "
            frame_tx_expect(port_type)
        end

        test "MRP_InLinkChange(Up)" do
            $frm_info[:type]  = :mrp_inlinkchange
            $frm_info[:frame] = mc_incontrol_frm.dup + "mrp_lnk t_type 9 "
            frame_tx_expect(port_type)
        end

        test "MRP_InLinkStatusPoll" do
            $frm_info[:type]  = :mrp_inlinkstatuspoll
            $frm_info[:frame] = mc_incontrol_frm.dup + "mrp_lnk t_type 10 "
            frame_tx_expect(port_type)
        end

        test "MRP_InTopologyChange" do
            $frm_info[:type]  = :mrp_intopologychange
            $frm_info[:frame] = mc_incontrol_frm.dup + "mrp_lnk t_type 7 "
            frame_tx_expect(port_type)
        end
    end
end

def forwarding_test_do(port_type)
    test "forwarding_test_do(itr_cnt = #{$itr_cnt}, port_type = #{port_type}, #{state_print()})" do
        forwarding_mc_test(port_type)
        forwarding_mc_control(port_type)
        forwarding_mc_intest(port_type)
        forwarding_mc_incontrol(port_type)
    end
end

def forwarding_test_counters_expect()
    t_i("Expecting counters = #{$state[:counters]}")
    counters = $ts.dut.call("mesa_mrp_counters_get", 0)
    $port_types.each {|port_type|
        field = port_type_to_counter_field(port_type)
        [:mrp_test, :mrp_intest].each {|pdu_type|
            counter = pdu_type_to_counter_field(pdu_type)
            assert(counters[field][counter] == $state[:counters][port_type][counter], "Expect #{port_type}:#{counter}: #{counters[field][counter]} == #{$state[:counters][port_type][counter]}")
        }
    }
end

def forwarding_test_counters(clear)
    test "forwarding_test_counters(itr_cnt = #{$itr_cnt}, #{state_print()})" do
        forwarding_test_counters_expect()

        return if !clear

        # Clear counters
        $ts.dut.call("mesa_mrp_counters_clear", 0)

        # Also clear $state counters
        $port_types.each {|port_type|
            field = port_type_to_counter_field(port_type)
            [:mrp_test, :mrp_intest].each {|pdu_type|
                counter = pdu_type_to_counter_field(pdu_type)
                $state[:counters][port_type][counter] = 0
            }
        }

        # And test that they indeed are cleared
        forwarding_test_counters_expect()
    end
end

def forwarding_test()
    t_i("Begin forwarding_test()")

    test "Forwarding test in all modes" do
        # Test forwarding of all MRP_Xxx and MRP_InXxx PDUs in all modes.
        $itr_cnt = 1
        [false, true].each {|mra|
            $ring_roles.each {|ring_role|
                $ic_roles.each {|ic_role|
                    $ic_modes.each {|ic_mode|
                        # Only test both I/C modes if we are a MIM.
                        next if ic_role != :mim && ic_mode == :lc

                        # Pass them into the current $state variable, so that we
                        # don't have to carry all these arguments around.
                        $state[:mra]       = mra
                        $state[:ring_role] = ring_role
                        $state[:ic_role]   = ic_role
                        $state[:ic_mode]   = ic_mode

                        mrp_add()

                        # Test that the counters indeed are 0. No need to clear
                        # them now (argument == false)
                        forwarding_test_counters(false)

                        # We need to test with
                        # 1) one of the ring ports blocked (don't need to test
                        #    with both ring ports blocked, I think.
                        # 2) the I/C port blocked
                        # 3) all ports forwarding
                        [:port2_blocked, :ic_blocked, :none_blocked].each {|blocked|
                            # Cannot block the I/C port if we're neither a MIM
                            # or MIC.
                            next if blocked == :ic_blocked && ic_role == :none

                            # Default the state
                            new_forward = Hash.new()
                            new_forward[:port1]   = true
                            new_forward[:port2]   = blocked != :port2_blocked
                            new_forward[:ic_port] = blocked != :ic_blocked

                            # Change the port state if needed
                            $port_types.each {|port_type|
                                # Don't change the I/C port if we're neither a
                                # MIM or MIC.
                                next if port_type == :ic_port && ic_role == :none

                                # Go on if the state doesn't change.
                                next if $state[:forwarding][port_type] == new_forward[port_type]

                                port_state_set(port_type, new_forward[port_type])
                            }

                            # Test by sending frames into each of the three
                            # ports from the test PC.
                            $port_types.each {|port_type|
                                # Don't transmit into I/C port unless we are a
                                # MIM/MIC.
                                next if port_type == :ic_port && ic_role == :none

                                forwarding_test_do(port_type)
                            }
                        }

                        # Test that the counters indeed are as expected. Clear
                        # and test afterwards.
                        forwarding_test_counters(true)

                        mrp_del()

                        $itr_cnt += 1
                    }
                }
            }
        }
    end

    test "Forwarding test while changing ring role dynamically" do
        $state[:mra]       = true
        $state[:ring_role] = :mrm
        $state[:ic_role]   = :none
        mrp_add()

        # Starting as MRM configured as MRA, change ring role dynamically to MRC
        # and back to MRA, and see that forwarding occurs as expected.
        prv_ring_role = "MESA_MRP_RING_ROLE_MANAGER" # Default
        [:mrm, :mrc, :mrm].each {|ring_role|
            new_ring_role = ring_role == :mrm ? "MESA_MRP_RING_ROLE_MANAGER" : "MESA_MRP_RING_ROLE_CLIENT"
            test "Check and set ring role (new_ring_role = #{new_ring_role}, prv_ring_role = #{prv_ring_role})" do
                # Get and check current ring role
                cur_ring_role = $ts.dut.call("mesa_mrp_ring_role_get", 0)
                assert(cur_ring_role == prv_ring_role, "Expect #{cur_ring_role} == #{prv_ring_role}")

                # Set new ring role
                $ts.dut.call("mesa_mrp_ring_role_set", 0, new_ring_role)

                # Check that it got set
                cur_ring_role = $ts.dut.call("mesa_mrp_ring_role_get", 0)
                assert(cur_ring_role == new_ring_role, "Expect #{cur_ring_role} == #{new_ring_role}")

                # Save it for next iteration
                prv_ring_role = new_ring_role
            end

            # Just overwrite the state, so that the following test knows what
            # ring role we currently have, to expect correctly.
            $state[:ring_role] = ring_role

            test "Forwarding test" do
                [:port1_blocked, :none_blocked].each {|blocked|
                    # Default the state
                    new_forward = Hash.new()
                    new_forward[:port1] = blocked != :port1_blocked
                    new_forward[:port2] = true

                    # Change the port state if needed
                    $port_types.each {|port_type|
                        # We don't play with the I/C port in this test.
                        next if port_type == :ic_port

                        # Go on if the state doesn't change.
                        next if $state[:forwarding][port_type] == new_forward[port_type]

                        port_state_set(port_type, new_forward[port_type])
                    }

                    # Test by sending frames into each of the ring ports from
                    # the test PC.
                    $port_types.each {|port_type|
                        next if port_type == :ic_port

                        forwarding_test_do(port_type)
                    }
                }
            end
        }

        mrp_del()
   end

    t_i("End forwarding_test()")
end

# RBNTBD: This is the expected Rx sequence number, not the Tx sequence number
# inserted in the frame. According to the register list under
# REW:PORT[0-9]:MRP_TX_CFG[0-1].MRP_SEQ_UPD_ENA, the register that holds the
# next sequence number is selected by the IFH's SEQ_NUM field, which points to
# one of the 256 entries in REW:PTP_SEQ_NO:PTP_SEQ_NO[0-255].
# How can such an entry be allocated without interfering with PTP, CCM, and DLR?
# Also, how can this be conveyed to the application, so that it can insert the
# correct number in IFH.SEQ_NUM? Sounds impractical.
# Finally, it somehow seems to count per port, which I can't find that it should
# anywhere in the register list.
$seq_cnt               = {:port1 => 0, :port2 => 0, :ic_port => 0}
$prv_primary_port_type = $port_types[0]
$prv_ring_state        = "MESA_MRP_RING_STATE_OPEN"
$prv_in_ring_state     = "MESA_MRP_RING_STATE_OPEN"
$transition_cnt        = {:mrp_test => 0, :mrp_intest => 0}

def tx_modif_test_do(new_primary_port_type, new_ring_state, new_in_ring_state)
    test "tx_modif_test_do(itr_cnt = #{$itr_cnt}, new_primary_port_type = #{new_primary_port_type}, prv_primary_port_type = #{$prv_primary_port_type}, new_ring_state = #{new_ring_state}, prv_ring_state = #{$prv_ring_state}, new_in_ring_state = #{new_in_ring_state}, prv_in_ring_state = #{$prv_in_ring_state}, #{state_print()})" do
        test "Check and set primary ring port (new_primary_port_type = #{new_primary_port_type})" do
            # Get and check current primary port
            cur_primary_port_no = $ts.dut.call("mesa_mrp_primary_port_get", 0)
            prv_primary_port_no = port_type_to_dut_port($prv_primary_port_type)
            assert(cur_primary_port_no == prv_primary_port_no, "Expect #{cur_primary_port_no} == #{prv_primary_port_no}")

            # Set new primary port
            new_primary_port_no = port_type_to_dut_port(new_primary_port_type)
            $ts.dut.call("mesa_mrp_primary_port_set", 0, new_primary_port_no)

            # Check that it got set
            cur_primary_port_no = $ts.dut.call("mesa_mrp_primary_port_get", 0)
            assert(cur_primary_port_no == new_primary_port_no, "Expect #{cur_primary_port_no} == #{new_primary_port_no}")

            # Save it for next iteration
            $prv_primary_port_type = new_primary_port_type
        end

        test "Check and set ring state (new_ring_state = #{new_ring_state})" do
            # Get and check current ring state
            cur_ring_state = $ts.dut.call("mesa_mrp_ring_state_get", 0)
            assert(cur_ring_state == $prv_ring_state, "Expect #{cur_ring_state} == #{$prv_ring_state}")

            # If new ring state differs from current ring state, the number of
            # MRP_transitions increment by one.
            $transition_cnt[:mrp_test] += 1 if cur_ring_state != new_ring_state

            # Set new ring state
            $ts.dut.call("mesa_mrp_ring_state_set", 0, new_ring_state)

            # Check that it got set
            cur_ring_state = $ts.dut.call("mesa_mrp_ring_state_get", 0)
            assert(cur_ring_state == new_ring_state, "Expect #{cur_ring_state} == #{new_ring_state}")

            # Save it for next iteration
            $prv_ring_state = new_ring_state
        end

        test "Check and set I/C ring state (new_in_ring_state = #{new_in_ring_state})" do
            # Get and check current I/C ring state
            cur_in_ring_state = $ts.dut.call("mesa_mrp_in_ring_state_get", 0)
            assert(cur_in_ring_state == $prv_in_ring_state, "Expect #{cur_in_ring_state} == #{$prv_in_ring_state}")

            # If new I/C state differs from current ring state, the number of
            # MRP_transitions increment by one.
            $transition_cnt[:mrp_intest] += 1 if cur_in_ring_state != new_in_ring_state

            # Set new I/C state
            $ts.dut.call("mesa_mrp_in_ring_state_set", 0, new_in_ring_state)

            # Check that it got set
            cur_in_ring_state = $ts.dut.call("mesa_mrp_in_ring_state_get", 0)
            assert(cur_in_ring_state == new_in_ring_state, "Expect #{cur_in_ring_state} == #{new_in_ring_state}")

            # Save it for next iteration
            $prv_in_ring_state = new_in_ring_state
        end

        expect_ring_state    = new_ring_state    == "MESA_MRP_RING_STATE_OPEN" ? 0 : 1
        expect_in_ring_state = new_in_ring_state == "MESA_MRP_RING_STATE_OPEN" ? 0 : 1

        # MRP_PortRole is 0 from primary port, 1 for secondary port, and 2 for
        # I/C port. 3 is invalid.
        port_role = Hash.new()
        port_role[:port1]   = new_primary_port_type == :port1 ? 0 : 1
        port_role[:port2]   = new_primary_port_type == :port2 ? 0 : 1
        port_role[:ic_port] = 2 # Cannot change

        # Create MC_TEST PDU
        mc_test_frm  = frame_create(MC_TEST, SC_STRING, 0, 0, "mrp")

        # Create MC_INTEST PDU
        mc_intest_frm = frame_create(MC_ITEST, SC_STRING, 0, 0, "mrp")

        # Create Tx IFHs. There is one per port the frame ends up on, and there
        # is one per MRP_Test and MRP_InTest type.
        mrp_test_tx_ifh   = Hash.new()
        mrp_intest_tx_ifh = Hash.new()
        $port_types.each {|port_type|
            port_no = port_type_to_dut_port(port_type)
            mrp_test_tx_ifh[port_type]   = tx_ifh_create(0, port_no, "MESA_PACKET_OAM_TYPE_MRP_TST")
            mrp_intest_tx_ifh[port_type] = tx_ifh_create(0, port_no, "MESA_PACKET_OAM_TYPE_MRP_ITST")
        }

        test "From CPU Tx two MRP_Test PDUs with abnormal variable fields and check the chip overwrites with expected values" do
            $port_types.each {|port_type|
                next if port_type == :ic_port
                # Transmit invalid MRP_PortRole (3), a "random" MRP_SequenceID,
                # invalid MRP_RingState (5), and a "random" MRP_Transition to
                # check that the chip overwrites the fields correctly.
                frm_tx = mrp_test_tx_ifh[port_type] + mc_test_frm.dup() + "mrp_tst t_sa #{MRP_SA_OWN} t_role 3 c_seq_num 10000 t_state 5 t_trans 1211 "

                [0, 1].each {|cnt|
                    t_i("Tx MRP_Test on #{port_type}, expect MRP_PortRole = #{port_role[port_type]}, MRP_RingState = #{expect_ring_state}, MRP_Transition = #{$transition_cnt[:mrp_test]}, MRP_Sequence_ID = #{$seq_cnt[port_type]}")
                    # MRP_Test Rx expect mask looks like:
                    # TX:      01154e00000100000000050788e3-0001-0212-000000000000050a-0003-0005-04bb-00000000-0112-2710-0000000000000000000000000000000000000000000000000000000000000000000000000000
                    # RX:      01154e00000100000000050788e3-0001-0212-000000000000050a-0000-0000-0006-000246eb-0112-0064-0000000000000000000000000000000000000000000000000000000000000000000000000000
                    # RX-MASK: ffffffffffffffffffffffffffff-0000-0000-0000000000000000-ffff-ffff-ffff-00000000-0000-ffff-0000000000000000000000000000000000000000000000000000000000000000000000000000
                    #                     ^                                              ^    ^    ^                  ^
                    #                     |                                              |    |    |                  |
                    #              DMAC, SMAC, EtherType                         MRP_PortRole | MRP_Transition    MRP_SequenceID
                    #                                                                    MRP_RingState
                    frm_rx = mc_test_frm.dup() + "mrp_tst ignore c_seq_num #{$seq_cnt[port_type]} t_role #{port_role[port_type]} t_state #{expect_ring_state} t_trans #{$transition_cnt[:mrp_test]} "
                    $seq_cnt[port_type] += 1
                    frame_tx(frm_tx, $npi_port, port_type == :port1 ? frm_rx : "", port_type == :port2 ? frm_rx : "", "", "")
                }
            }
        end

        test "From CPU Tx two MRP_InTest PDUs with abnormal variable fields and check the chip overwrites with expected values" do
            $port_types.each {|port_type|
                # Transmit invalid MRP_PortRole (3), a "random" MRP_SequenceID,
                # invalid MRP_RingState (5), and a "random" MRP_Transition to
                # check that the chip overwrites the fields correctly.
                frm_tx = mrp_intest_tx_ifh[port_type] + mc_intest_frm.dup() + "mrp_tst t_sa #{MRP_SA_OWN} t_type 6 t_role 3 c_seq_num 10000 t_state 5 t_trans 1211 "

                [0, 1].each {|cnt|
                    t_i("Tx MRP_InTest on #{port_type}, expect MRP_PortRole = #{port_role[port_type]}, MRP_RingState = #{expect_in_ring_state}, MRP_Transition = #{$transition_cnt[:mrp_intest]}, MRP_Sequence_ID = #{$seq_cnt[port_type]}")

                    # MRP_InTest Rx expect Mask looks like:
                    # TX:      01154e00000300000000050788e3-0001-0612-000000000000050a-0003-0005-04bb-00000000-0112-2710-0000000000000000000000000000000000000000000000000000000000000000000000000000
                    # RX:      01154e00000300000000050788e3-0001-0612-000000000000050a-0000-0001-0011-00024d7b-0112-0066-0000000000000000000000000000000000000000000000000000000000000000000000000000
                    # RX-MASK: ffffffffffffffffffffffffffff-0000-0000-0000000000000000-ffff-ffff-ffff-00000000-0000-ffff-0000000000000000000000000000000000000000000000000000000000000000000000000000
                    #                     ^                                              ^    ^    ^                  ^
                    #                     |                                              |    |    |                  |
                    #              DMAC, SMAC, EtherType                         MRP_PortRole | MRP_Transition    MRP_SequenceID
                    #                                                                    MRP_RingState
                    frm_rx = mc_intest_frm.dup() + "mrp_tst ignore c_seq_num #{$seq_cnt[port_type]} t_role #{port_role[port_type]} t_state #{expect_in_ring_state} t_trans #{$transition_cnt[:mrp_intest]} "
                    $seq_cnt[port_type] += 1
                    frame_tx(frm_tx, $npi_port, port_type == :port1 ? frm_rx : "", port_type == :port2 ? frm_rx : "", port_type == :ic_port ? frm_rx : "", "")
                }
            }
        end
    end
end

def tx_modif_test()
    t_i("Begin tx_modif_test()")

    # Test chip's modification of CPU-transmitted PDUs.
    # Only MRM's (whether MRA or pure MRM) and MIM-RC are of interest in this
    # test.
    $state[:mra]       = false
    $state[:ring_role] = :mrm
    $state[:ic_role]   = :mim
    $state[:ic_mode]   = :rc

    mrp_add()

    $itr_cnt = 1

    # Run this test with first port1 as primary port, then port2, and finally
    # back to port1.
    # Also change ring state and I/C ring state, first from open then to closed
    # and finally back to open.
    # Do the same for the interconnection ring.
    [:port1, :port2, :port1].each {|port_type|
        ["MESA_MRP_RING_STATE_OPEN", "MESA_MRP_RING_STATE_CLOSED", "MESA_MRP_RING_STATE_OPEN"].each {|ring_state|
            ["MESA_MRP_RING_STATE_OPEN", "MESA_MRP_RING_STATE_CLOSED", "MESA_MRP_RING_STATE_OPEN"].each {|in_ring_state|
                tx_modif_test_do(port_type, ring_state, in_ring_state)
                $itr_cnt += 1
            }
        }
    }

    mrp_del()
    t_i("End tx_modif_test()")
end

def loc_test_expect()
    status = $ts.dut.call("mesa_mrp_status_get", 0)
    events = $ts.dut.call("mesa_mrp_event_get", 0)

    # Read once more to verify that all events are now cleared, due to
    # the previous reading.
    cleared_events = $ts.dut.call("mesa_mrp_event_get", 0)

    $port_types.each {|port_type|
        # Test both MRP_Test and MRP_InTest LoC
        status_field = port_type_to_status_field(port_type)
        events_field = port_type_to_event_field(port_type)

        # Ask caller what he expects given the current state.
        expect = Hash.new()
        yield(port_type, expect)

        # Test MRP_Test LoC
        assert(status[status_field]["tst_loc"] == expect[:tst], "Expect status[#{port_type}].tst_loc #{expect[:tst]}")

        # Test MRP_InTest LoC
        assert(status[status_field]["itst_loc"] == expect[:itst], "Expect status[#{port_type}].itst_loc #{expect[:itst]}")

        # Test mrp_seen
        assert(status[status_field]["mrp_seen"] == expect[:mrp_seen], "Expect status[#{port_type}].mrp_seen #{expect[:mrp_seen]}")

        # Test mrp_proc_seen
        assert(status[status_field]["mrp_proc_seen"] == expect[:mrp_proc_seen], "Expect status[#{port_type}].mrp_proc_seen #{expect[:mrp_proc_seen]}")

        # Test Events
        assert(events[events_field] == expect[:event], "Expect events[#{port_type}] == #{expect[:event]}")

        # Test cleared events
        assert(cleared_events[events_field] == 0, "Expect cleared events[#{port_type}] == 0")
    }
end

def loc_test_do()
    test "loc_test_do(#{state_print()})" do
        # Create own MRP_Test PDU
        mc_test_frm      = frame_create(MC_TEST, SC_STRING, 0, 0, "mrp")
        mrp_test_frm_own = mc_test_frm.dup() + "mrp_tst t_sa #{MRP_SA_OWN} "

        # Create remote, but not best MRP_Test PDU
        mrp_test_frm_rem_not_best = mc_test_frm.dup() + "mrp_tst t_sa #{MRP_SA_REM_HI} t_prio #{$mrp_prio + 1} "

        # Create remote, best MRM MRP_Test PDU (based on prio)
        best_mrm_sa          = MRP_SA_REM_HI
        best_mrm_sa_as_array = MRP_SA_REM_HI_AS_ARRAY
        best_mrm_prio        = $mrp_prio - 1
        mrp_test_frm_rem_best = mc_test_frm.dup() + "mrp_tst t_sa #{best_mrm_sa} t_prio #{best_mrm_prio} "

        # Create MRP_InTest PDU
        mc_intest_frm  = frame_create(MC_ITEST, SC_STRING, 0, 0, "mrp")
        mrp_intest_frm = mc_intest_frm.dup() + "mrp_tst t_sa #{MRP_SA_OWN} t_type 6 "

        test "Test LoC initially inactive" do
            loc_test_expect() {|port_type, expect|
                # We expect it inactive for all port and test types
                expect[:tst]           = false
                expect[:itst]          = false
                expect[:event]         = 0
                expect[:mrp_seen]      = false
                expect[:mrp_proc_seen] = false
            }
        end

        test "Test LoC active after #{$loc_timeout_sec} seconds" do
            # Wait until timeout
            sleep $loc_timeout_sec

            loc_test_expect() {|port_type, expect|
                # Test MRP_Test LoC
                # We expect it active if we are an MRA or MRM and testing ring
                # ports (MRCs also have LoC enabled if they are MRAs).
                # The I/C port does not have MRP_Test processing enabled.
                expect[:tst] = ($state[:mra] || $state[:ring_role] == :mrm) && port_type != :ic_port

                # Test MRP_InTest LoC
                # We expect it active if we are a MIM-RC on all ports
                expect[:itst] = $state[:ic_role] == :mim && $state[:ic_mode] == :rc

                # We expect the event based on whether we expect TST and ITST.
                expect[:event] = (expect[:tst] ? MESA_MRP_EVENT_MASK_TST_LOC : 0) | (expect[:itst] ? MESA_MRP_EVENT_MASK_ITST_LOC : 0)

                # We still haven't transmitted any MRP PDUs into the DUT.
                expect[:mrp_seen]      = false
                expect[:mrp_proc_seen] = false
            }
        end

        test "Tx MRP_Test(Own) PDU and test LoC inactive" do
            $port_types.each{|port_type|
                # Send MRP_Test PDU, without expecting reception on any ports,
                # because that's already tested by the forwarding test.
                # The " " means: skip arrival check.
                # It takes roughly 120 ms to Tx one frame on one port.
                frame_tx(mrp_test_frm_own, port_type_to_pc_port(port_type), " ", " ", " ", " ")
            }

            loc_test_expect() {|port_type, expect|
                # Test MRP_Test LoC
                # We don't expect any 'tst_loc' to be active.
                expect[:tst] = false

                # Test MRP_InTest LoC
                # We expect it active if we are a MIM-RC on all ports, since we
                # haven't yet Tx'ed any MRP_InTest PDUs.
                expect[:itst] = $state[:ic_role] == :mim && $state[:ic_mode] == :rc

                # Test Events
                # Since clear of a saturated miss counter also causes an event
                # (SIC!), we must expect that, even though "tst_loc" is now
                # false.
                # We expect MRP_Test events like when the miss counter saturated
                # after $loc_timeout_sec above.
                expect[:event] = ($state[:mra] || $state[:ring_role] == :mrm) && port_type != :ic_port ? MESA_MRP_EVENT_MASK_TST_LOC : 0

                # We expect an MRP PDU to be seen and processed on the enabled
                # ports.
                expect[:mrp_seen]      = port_type != :ic_port || $state[:ic_role] != :none
                expect[:mrp_proc_seen] = port_type != :ic_port || $state[:ic_role] != :none
            }
        end

        test "Tx MRP_InTest PDU and test LoC inactive" do
            $port_types.each{|port_type|
                # Send MRP_InTest PDU, without expecting reception on any ports,
                # because that's already tested by the forwarding test.
                # The " " means: skip arrival check.
                frame_tx(mrp_intest_frm, port_type_to_pc_port(port_type), " ", " ", " ", " ")
            }

            # Test that both 'tst_loc' and 'itst_loc' are inactive on all ports
            loc_test_expect() {|port_type, expect|
                # Test MRP_Test LoC
                # We don't expect any 'tst_loc' to be active.
                expect[:tst] = false

                # Test MRP_InTest LoC
                # We don't expect any 'itst_loc' to be active.
                expect[:itst] = false

                # Test Events
                # Since clear of a saturated miss counter also causes an event
                # (SIC!), we must expect that, even though "itst_loc" is now
                # false.
                # We expect MRP_InTest events whenever we're an MIM-RC.
                expect[:event] = $state[:ic_role] == :mim && $state[:ic_mode] == :rc ? MESA_MRP_EVENT_MASK_ITST_LOC : 0

                # We expect an MRP PDU to be seen and processed on the enabled
                # ports.
                expect[:mrp_seen]      = port_type != :ic_port || $state[:ic_role] != :none
                expect[:mrp_proc_seen] = port_type != :ic_port || $state[:ic_role] != :none
            }
        end

        # Nothing more to do unless we are an MRA configured as MRC.
        return if $state[:ring_role] != :mrc || !$state[:mra]

        test "Set Best MRM and test LoC active again after #{$loc_timeout_sec} seconds" do
            # Set Best MRM.
            conf = $ts.dut.call("mesa_mrp_best_mrm_get", 0)
            conf["mac"]["addr"] = best_mrm_sa_as_array
            conf["prio"]        = best_mrm_prio
            $ts.dut.call("mesa_mrp_best_mrm_set", 0, conf)

            # Wait until timeout
            sleep $loc_timeout_sec

            loc_test_expect() {|port_type, expect|
                # Test MRP_Test LoC
                # Since we are an MRA configured as MRC, we expect LoC to be
                # active now (MRCs also have LoC enabled if they are MRAs).
                # The I/C port does not have MRP_Test processing enabled.
                expect[:tst] = port_type != :ic_port

                # Test MRP_InTest LoC
                # We expect it active if we are a MIM-RC on all ports
                expect[:itst] = $state[:ic_role] == :mim && $state[:ic_mode] == :rc

                expect[:event] = (expect[:tst] ? MESA_MRP_EVENT_MASK_TST_LOC : 0) | (expect[:itst] ? MESA_MRP_EVENT_MASK_ITST_LOC : 0)

                # No MRP PDUs seen since last call, and thereby no processing
                # done
                expect[:mrp_seen]      = false
                expect[:mrp_proc_seen] = false
            }
        end

        test "Tx MRP_Test(Not Best) and test that this doesn't clear LoC" do
            $port_types.each{|port_type|
                # Send MRP_Test PDU, without expecting reception on any
                # ports, because that's already tested by the forwarding
                # test.
                # The " " means: skip arrival check.
                # It takes roughly 120 ms to Tx one frame on one port.
                frame_tx(mrp_test_frm_rem_not_best, port_type_to_pc_port(port_type), " ", " ", " ", " ")
            }

            loc_test_expect() {|port_type, expect|
                # Test MRP_Test LoC
                # We still expect it active if we are an MRA or MRM and
                # testing ring ports (MRCs also have LoC enabled if they are
                # MRAs).
                # The I/C port does not have MRP_Test processing enabled.
                expect[:tst] = ($state[:mra] || $state[:ring_role] == :mrm) && port_type != :ic_port

                # Test MRP_InTest LoC
                # We expect it active if we are a MIM-RC on all ports
                expect[:itst] = $state[:ic_role] == :mim && $state[:ic_mode] == :rc

                # Since events get cleared for every iteration, no new
                # events have occurred.
                expect[:event] = 0

                # We expect an MRP PDU to be seen and processed on the enabled
                # ports.
                expect[:mrp_seen]      = port_type != :ic_port || $state[:ic_role] != :none
                expect[:mrp_proc_seen] = port_type != :ic_port || $state[:ic_role] != :none
            }
        end

        test "Tx MRP_Test(Best) and test that this clears LoC" do
            $port_types.each{|port_type|
                # Send MRP_Test PDU, without expecting reception on any ports,
                # because that's already tested by the forwarding test.
                # The " " means: skip arrival check.
                # It takes roughly 120 ms to Tx one frame on one port.
                frame_tx(mrp_test_frm_rem_best, port_type_to_pc_port(port_type), " ", " ", " ", " ")
            }

            loc_test_expect() {|port_type, expect|
                # Test MRP_Test LoC
                # We don't expect any 'tst_loc' to be active.
                expect[:tst] = false

                # Test MRP_InTest LoC
                # We expect it active if we are a MIM-RC on all ports
                expect[:itst] = $state[:ic_role] == :mim && $state[:ic_mode] == :rc

                expect[:event] = (expect[:tst] ? MESA_MRP_EVENT_MASK_TST_LOC : 0) | (expect[:itst] ? MESA_MRP_EVENT_MASK_ITST_LOC : 0)

                # Test Events
                # Since clear of a saturated miss counter also causes an event
                # (SIC!), we must expect that, even though "tst_loc" is now
                # false.
                # We expect MRP_Test events like when the miss counter saturated
                # after $loc_timeout_sec above.
                expect[:event] = port_type != :ic_port ? MESA_MRP_EVENT_MASK_TST_LOC : 0

                # We expect an MRP PDU to be seen and processed on the enabled
                # ports.
                expect[:mrp_seen]      = port_type != :ic_port || $state[:ic_role] != :none
                expect[:mrp_proc_seen] = port_type != :ic_port || $state[:ic_role] != :none
            }
        end
    end
end

def loc_test()
    t_i("Begin loc_test()")

    # Test MRM/MRC/MIM/MIC LoC
    [false, true].each {|mra|
        $ring_roles.each {|ring_role|
            $ic_roles.each {|ic_role|
                $ic_modes.each {|ic_mode|
                    # Only test both I/C modes if we are a MIM.
                    next if ic_role != :mim && ic_mode == :lc

                    $state[:ring_role] = ring_role
                    $state[:ic_role]   = ic_role
                    $state[:mra]       = mra
                    $state[:ic_mode]   = ic_mode
                    mrp_add()
                    loc_conf_set() # Also clears current sticky events.
                    event_mask_set()
                    loc_test_do()
                    mrp_del()
                }
            }
        }
    }

    t_i("End loc_test()")
end

def cpu_copy_test_do(new_tst_copy, new_itst_copy)
    test "cpu_copy_test_do(new_tst_copy = #{new_tst_copy}, new_itst_copy = #{new_itst_copy}, previous cpu_copy_conf = #{$state[:cpu_copy_conf]}, #{state_print()})" do
        test "Check and set tst/itst copy" do
            # Get and check current CPU copy
            cur_cpu_copy_conf = $ts.dut.call("mesa_mrp_tst_copy_conf_get", 0)
            assert(cur_cpu_copy_conf["tst_to_cpu"]  == $state[:cpu_copy_conf]["tst_to_cpu"],  "Expect tst_to_cpu:  #{cur_cpu_copy_conf['tst_to_cpu']}  == #{$state[:cpu_copy_conf]['tst_to_cpu']}")
            assert(cur_cpu_copy_conf["itst_to_cpu"] == $state[:cpu_copy_conf]["itst_to_cpu"], "Expect itst_to_cpu: #{cur_cpu_copy_conf['itst_to_cpu']} == #{$state[:cpu_copy_conf]['itst_to_cpu']}")

            new_cpu_copy_conf = Hash.new()
            new_cpu_copy_conf["tst_to_cpu"]  = new_tst_copy
            new_cpu_copy_conf["itst_to_cpu"] = new_itst_copy

            # Set new copy conf
            $ts.dut.call("mesa_mrp_tst_copy_conf_set", 0, new_cpu_copy_conf)

            # Check that it got set
            cur_cpu_copy_conf = $ts.dut.call("mesa_mrp_tst_copy_conf_get", 0)
            assert(cur_cpu_copy_conf["tst_to_cpu"]  == new_cpu_copy_conf["tst_to_cpu"],  "Expect tst_to_cpu:  #{cur_cpu_copy_conf['tst_to_cpu']}  == #{new_cpu_copy_conf['tst_to_cpu']}")
            assert(cur_cpu_copy_conf["itst_to_cpu"] == new_cpu_copy_conf["itst_to_cpu"], "Expect itst_to_cpu: #{cur_cpu_copy_conf['itst_to_cpu']} == #{new_cpu_copy_conf['itst_to_cpu']}")

            # Save it for the expectations in next sub-test below.
            $state[:cpu_copy_conf] = new_cpu_copy_conf
        end

        test "Send MRP_Test and MRP_InTest PDUs into the switch" do
            $port_types.each {|port_type|
                forwarding_mc_test(port_type)
                forwarding_mc_intest(port_type)
            }
        end
    end
end

def cpu_copy_test()
    t_i("Begin cpu_copy_test()")

    # Test as MRM and MIM.
    $state[:ring_role] = :mrm
    $state[:ic_role]   = :mim

    [false, true].each {|mra|
        $ic_modes.each {|ic_mode|
            $state[:mra]     = mra
            $state[:ic_mode] = ic_mode
            mrp_add()

            [false, true].each {|tst_copy|
                [false, true].each {|itst_copy|
                    cpu_copy_test_do(tst_copy, itst_copy)
                }
            }

            mrp_del()
        }
    }

    t_i("End cpu_copy_test()")
end

def hitme_once_test_do(tst_hitme_once, itst_hitme_once)
    test "hitme_once_test_do(MRP_Test = #{tst_hitme_once}, MRP_InTest = #{itst_hitme_once}, #{state_print()})" do
        $ts.dut.call("mesa_mrp_tst_hitme_once", 0)  if tst_hitme_once
        $ts.dut.call("mesa_mrp_itst_hitme_once", 0) if itst_hitme_once

        # Create MRP_Test PDU
        mc_test_frm  = frame_create(MC_TEST,  SC_STRING, 0, 0, "mrp")
        mrp_test_frm = mc_test_frm.dup + "mrp_tst t_sa #{MRP_SA_OWN} "

        # Create MRP_InTest PDU
        mc_intest_frm  = frame_create(MC_ITEST, SC_STRING, 0, 0, "mrp")
        mrp_intest_frm = mc_intest_frm.dup() + "mrp_tst t_sa #{MRP_SA_OWN} t_type 6 "

        $port_types.each {|port_type|
            rx_ifh = rx_ifh_create(IGNORE, port_type_to_dut_port(port_type))
            cpu_test_frm   = rx_ifh + mrp_test_frm
            cpu_intest_frm = rx_ifh + mrp_intest_frm

            # Send MRP_Test and MRP_InTest PDUs twice. Never expect them to arrive
            # at the CPU the second time. But expect them to arrive the first time
            # if hitme once for that PDU type is enabled.
            port = port_type_to_pc_port(port_type);
            [1, 2].each {|cnt|
                # We don't care whether the frames arrive on other ports than
                # the CPU, since that's handled by the forwarding test.

                # MRP_Test
                copy_to_cpu = cnt == 1 && tst_hitme_once && port_type != :ic_port
                frame_tx(mrp_test_frm, port, " ", " ", " ", copy_to_cpu ? cpu_test_frm : "")

                # MRP_InTest
                copy_to_cpu = cnt == 1 && itst_hitme_once
                frame_tx(mrp_intest_frm, port, " ", " ", " ", copy_to_cpu ? cpu_intest_frm : "")
            }
        }
    end
end

def hitme_once_test()
    t_i("Begin hitme_once_test()")

    # Test as MRM and MIM-RC.
    $state[:ring_role] = :mrm
    $state[:ic_role]   = :mim
    $state[:ic_mode]   = :rc

    mrp_add()

    [true, false].each {|tst_hitme_once|
        [true, false].each {|itst_hitme_once|
            hitme_once_test_do(tst_hitme_once, itst_hitme_once)
        }
    }

    mrp_del()

    t_i("End hitme_once_test()")
end

def error_test_expect()
    status = $ts.dut.call("mesa_mrp_status_get", 0)

    # Ask caller what he expects given the current state.
    expect = {:dmac_err_seen => false, :vers_err_seen => false}
    yield(expect) if block_given?

    $port_types.each {|port_type|
        # The I/C port is not in play in this test.
        next if port_type == :ic_port

        status_field = port_type_to_status_field(port_type)

        # Test dmac_err_seen
        assert(status[status_field]["dmac_err_seen"] == expect[:dmac_err_seen], "Expect status[#{port_type}].dmac_err_seen #{expect[:dmac_err_seen]}")

        # Test vers_err_seen
        assert(status[status_field]["vers_err_seen"] == expect[:vers_err_seen], "Expect status[#{port_type}].vers_err_seen #{expect[:vers_err_seen]}")
    }
end

def error_test_do()
    test "error_test_do(#{state_print()})" do
        # Create MC_TEST PDU
        mc_test_frm = frame_create(MC_TEST, SC_STRING, 0, 0, "mrp")

        # Create MC_CONTROL PDU
        mc_control_frm = frame_create(MC_CONTROL, SC_STRING, 0, 0, "mrp")

        test "Test error status initially inactive" do
            # Start by testing that all error indicators are false.
            error_test_expect()
        end

        test "Tx MRP_Test PDU with invalid DMAC" do
            # Using the MC_CONTROL DMAC, create an MRP_Test PDU (which should
            # have used the MC_TEST DMAC).
            inv_dmac_frm = mc_control_frm.dup() + "mrp_tst t_sa #{MRP_SA_OWN} "
            $port_types.each {|port_type|
                 # The I/C port is not in play in this test.
                 next if port_type == :ic_port

                 # Expect erroneous frames to be discarded
                 frame_tx(inv_dmac_frm, port_type_to_pc_port(port_type), "", "", "", "")
            }

            error_test_expect() {|expect|
                expect[:dmac_err_seen] = true
            }
        end

        test "Tx MRP_Test PDU with invalid version number" do
            inv_vers_frm = mc_test_frm.dup() + "mrp_tst t_sa #{MRP_SA_OWN} version 2 "

            $port_types.each {|port_type|
                 # The I/C port is not in play in this test.
                 next if port_type == :ic_port

                 # Expect erroneous frames to be discarded
                 frame_tx(inv_vers_frm, port_type_to_pc_port(port_type), "", "", "", "")
            }

            error_test_expect() {|expect|
                expect[:vers_err_seen] = true
            }
        end

        # Sequence error detection is disabled in the chip, because not all MRP
        # link partners are able to generate the correct sequence number, so the
        # field no longer exists.
    end
end

def error_test()
    t_i("Begin error_test()")
    # Just perform the test as MRM, as other modes will work the same.
    $state[:ring_role] = :mrm
    $state[:ic_role]   = :none
    $state[:mra]       = false
    mrp_add()
    error_test_do()
    mrp_del()
    t_i("End error_test()")
end

test "test_run" do
    # Default $mrp_conf and $loc_conf
    mrp_conf_default()
    loc_conf_default()

    # Test forwarding of MRP_Xxx PDUs in all mode combinations and with and
    # without ports forwarding.
    forwarding_test() if RUN_TEST_FORWARDING != 0

    # Test Tx of chip-modified MRP_Xxx PDUs
    tx_modif_test()   if RUN_TEST_TX_MODIF   != 0

    # Test Loss of Continuity for both MRMs and MIMs.
    loc_test()        if RUN_TEST_LOC        != 0

    # Test CPU copying with hitme_once and tst_copy_conf_set functions
    cpu_copy_test()   if RUN_TEST_CPU_COPY   != 0

    # Test hitme once of MRP_Test and MRP_InTest PDUs
    hitme_once_test() if RUN_TEST_HITME_ONCE != 0

    # Test various status errors.
    error_test()      if RUN_TEST_ERROR      != 0
end

test "test_clean_up" do
    # In case the test fails, it's nice to have the state and the output of
    # 'deb api [cil] mrp'
    t_i("state = #{$state}")
    $ts.dut.run("mesa-cmd deb api mrp")

    # Restore VLAN port configuration
    $port_types.each {|port_type|
        $ts.dut.call("mesa_vlan_port_conf_set", port_type_to_dut_port(port_type), $vlan_port_conf_restore[port_type])
    }

    # Clear VLAN memberships
    $ts.dut.call("mesa_vlan_port_members_set", $data_vid, "")

    # CPU queue configuration restore
    $ts.dut.call("mesa_packet_rx_conf_set", $packet_rx_conf_restore)

    # NPI port configuration restore
    $ts.dut.call("mesa_npi_conf_set", $npi_conf_restore)
end

