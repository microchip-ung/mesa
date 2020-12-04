#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
$ts = get_test_setup("mesa_pc_b2b_4x")

#---------- Description -------------------------------------------------------
# Purpose:
# Test KR functionality
#
# Test procedure:
# 1. Aneg (no training) to 1g, 2g5, 5g, 10g, 25g and verify successful aneg complete
# 2. Aneg and train at 10G/25g and verify successful training
# 3. Parallel detect to to 1g, 2g5, 5g, 10g, 25g and verify successful aneg complete
# 4. Disable KR and verify successful link up

#---------- Configuration -----------------------------------------------------
check_capabilities do
    $cap_kr = $ts.dut.call("mesa_capability", "MESA_CAP_PORT_KR_IRQ")
    assert(($cap_kr != true), "KR IRQ must be supported")
end

$kr_ports = []
test "Config" do
    $ts.dut.looped_port_list.each do |idx|
        conf = $ts.dut.call "mesa_port_conf_get", idx
        if conf["serdes"]["media_type"].include? "DAC"
            $kr_ports << idx
        end
    end
end

cap25 = ""
speed = []
speed_cap = []
check_capabilities do
    assert(($kr_ports.count > 0), "DAC based loop ports must be supported (#{$kr_ports.count})")

    conf = $ts.dut.call("mesa_port_conf_get", $kr_ports[0])
    if (conf["speed"] == "MESA_SPEED_25G")
        cap25 = "adv-25g"
        speed = ['25g', '10g', '5g', '2500', '1000fdx', '25g']
        speed_cap = ['adv-1g', 'adv-2g5', 'adv-5g', 'adv-10g', 'adv-25g']
    elsif (conf["speed"] == "MESA_SPEED_10G")
        speed = ['10g', '5g', '2500', '1000fdx', '10g']
        speed_cap = ['adv-1g', 'adv-2g5', 'adv-5g', 'adv-10g']
    end
    assert((speed_cap.count > 0), "Loop ports must be 10G or 25G")
end

############ ANEG only ################
test "Aneg" do
    cli_port = $kr_ports[0]+1
    $ts.dut.run "mesa-cmd port kr aneg #{cli_port} adv-1g adv-2g5 adv-5g adv-10g #{cap25}"
    speed_cap.each do |cap|
        cli_port = $kr_ports[1]+1
        $ts.dut.run "mesa-cmd port kr aneg #{cli_port} #{cap}"
        sleep 3
        $kr_ports.each do |idx|
            conf = $ts.dut.call "mesa_port_kr_status_get", idx
            if conf["aneg"]["complete"] != true
                t_e("Could not complete aneg for #{cap} got #{conf["aneg"]["complete"]}");
                break
            else
                t_i("Aneg to '#{cap}' completed");
                t_i("==========================");
            end
        end
    end
    $ts.dut.run "mesa-cmd port kr aneg dis"
end

############ TRAINING ################
spds = []
spds << "adv-10g"
if cap25 != ""
    spds << "adv-25g"
end
test "Training" do
    spds.each do |spd|
      $kr_ports.each do |idx|
        cli_port = idx+1
        $ts.dut.run "mesa-cmd port kr aneg #{cli_port} #{spd} rfec rsfec train"
      end
      $kr_ports.each do |idx|
          conf = $ts.dut.call "mesa_port_kr_status_get", idx
          eye = $ts.dut.call "mesa_port_kr_eye_get", idx
          if conf["train"]["complete"] != true
              t_e("Could not complete aneg for #{spd} got #{conf["aneg"]["complete"]}");
          else
              t_i("Training (#{spd}) completed with eye height:#{eye["height"]}");
              t_i("=================================================");
          end

          if eye["height"] < 10
              t_e("Eye height is small");
          end
          if spd == "adv-10g"
              if conf["fec"]["r_fec_enable"] != true
                  t_e("Base R-FEC not enabled");
              end
          else
              if conf["fec"]["rs_fec_enable"] != true
                  t_e("Base RS-FEC not enabled");
              end
          end
      end
    end
    $ts.dut.run "mesa-cmd port kr aneg dis"
end

############ PARALLEL DETECT ################
test "Parallel detect" do
    cli_port = $kr_ports[0]+1
    $ts.dut.run "mesa-cmd port kr deb #{cli_port} pd"
    $ts.dut.run "mesa-cmd port kr aneg #{cli_port} adv-1g adv-2g5 adv-5g adv-10g #{cap25}"
    speed.each do |cap|
        cli_port = $kr_ports[1]+1
        $ts.dut.run "mesa-cmd port mode #{cli_port} #{cap}"
        sleep 3
        conf = $ts.dut.call "mesa_port_kr_status_get", $kr_ports[0]
        if conf["aneg"]["complete"] != true
            t_e("Could not complete aneg for #{cap} got #{conf["aneg"]["complete"]}");
        else
            t_i("Parallel detect to '#{cap}' completed");
            t_i("=================================");
        end
    end
end

test "Disable KR" do
    $ts.dut.run "mesa-cmd port kr aneg dis"
    $kr_ports.each do |idx|
        status = $ts.dut.call "mesa_port_status_get", idx
        if status["link"] != true
            t_e("No link after KR disable");
        else
            t_i("Link is up after KR disable");
            t_i("===========================");
        end
    end
end
