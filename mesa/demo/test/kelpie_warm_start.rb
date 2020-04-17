#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

#-------------------------------------------------------------------------------------
# Test-case for Kelpie/warm-start
#
# Warm start usage:
# 1. Initilize API with the 'warm_start_enable' parameter (it will be cold start if the chip is not configured)
# 2. Perform the needed API configuration.  In this testcase: 'conf_xxx' functions.
# 3. Complete the warm start with 'mesa_restart_conf_end()'.
#
# To run this test:
# sudo ./kelpie_warm_start.rb            :  Normal run with cold start followed by warm start
# sudo ./kelpie_warm_start.rb --no-init  :  Only warm start, item 1,2,3.
#
#
# Use SMB to inject traffic manually
#
# Use CLI command :'cli deb sym wr DEVCPU_GCB:CHIP_REGS:GPR 0' to force initial cold start even though warm-start is requested
#
# I.e:
# sudo ./kelpie_warm_start.rb            : Normal start
# 'cli deb sym wr DEVCPU_GCB:CHIP_REGS:GPR 0' : Reset the general purpose register used for warm-start
# sudo ./kelpie_warm_start.rb --no-init  : API is cold-started
# sudo ./kelpie_warm_start.rb --no-init  : API is warm-started
#
#-------------------------------------------------------------------------------------

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Hack, only Serval-1 has this capability and warm start
cap_check_exit("L2_VCAP_PORT_CONF")

#---------- Configuration -----------------------------------------------------

def test_port_list a
    port_list = ""
    a.each do |idx|
        port_list += "#{$ts.dut.port_list[idx]}"
        port_list += "," unless idx == a.last
    end
    port_list
end

# Ports used in this test
$port_list = $ts.dut.port_list

# VLANs used in this test
$vid_list = [ 1,2,3]
$vid_members = [$port_list[0], $port_list[1], $port_list[2], $port_list[3]]
$s_etype = 0x9100


# Create a policy which triggers on one tag and not zero tag or two tags
def conf_qce
    qce = $ts.dut.call("mesa_qce_init", "MESA_QCE_TYPE_ANY")
    qce["id"] = 1
    key = qce["key"]
    tag = key["tag"]
    tag["tagged"] = "MESA_VCAP_BIT_1"
    inner_tag = key["inner_tag"]
    inner_tag["tagged"] = "MESA_VCAP_BIT_0"
    key["port_list"] = test_port_list($port_list)
    action = qce["action"]
    action["policy_no"] = 1
    action["policy_no_enable"] = true
    $ts.dut.call("mesa_qce_add", 0, qce)
end

# Create an ace which uses the above policy and if hit then redirect frames to some port
def conf_acl
    ace = $ts.dut.call("mesa_ace_init", "MESA_ACE_TYPE_ANY")
    ace["id"] = 1
    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_REDIR"
    action["port_list"] = "#{$port_list[0]}"
    ace["port_list"] = "#{$port_list[1]}"
    policy = ace["policy"]
    policy["value"] = 1
    policy["mask"] = 0x3f
    $ts.dut.call("mesa_ace_add", 0, ace)
end

# Create an default ACL port rule and if hit (by any frame) then redirect frames to some port
def conf_acl_port
    conf = $ts.dut.call("mesa_acl_port_conf_get", 0)
    action = conf["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_REDIR"
    action["port_list"] = "#{$port_list[1]}"
    $ts.dut.call("mesa_acl_port_conf_set", 0, conf)
end


# Create VLANs and add the front ports
def conf_vlan
    # VLAN port configuration table
    $conf_table =
        [
         {
             # Hybrid, S-custom port
             port_type: "MESA_VLAN_PORT_TYPE_S_CUSTOM",
             tpid: $s_etype,
             pvid: $vid_list[1],
             uvid: $vid_list[1],
             frame_type: "MESA_VLAN_FRAME_ALL"
         },
        ]
    # Set global Ethernet Type for S-custom ports
    conf = $ts.dut.call("mesa_vlan_conf_get")
    conf["s_etype"] = $s_etype
    $ts.dut.call("mesa_vlan_conf_set", conf)

    # Set VLAN port configuration
    $port_list.each_with_index do |port, idx|
        entry = $conf_table[0]
        conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
        conf["port_type"] = entry[:port_type]
        conf["pvid"] = entry[:pvid]
        conf["untagged_vid"] = entry[:uvid]
        conf["frame_type"] = entry[:frame_type]
        $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
    end

    # Set VLAN memberships
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")
    $vid_list.each_with_index do |vid, idx|
        member_list = $vid_members
        str = ""
        member_list.each do |port|
            str += "#{port}"
            str += "," unless port == member_list.last
        end
        $ts.dut.call("mesa_vlan_port_members_set", vid, str)
    end
end

def conf_func(warm)
    conf_acl_port
    conf_qce
    conf_acl
    conf_vlan
end

#---------- Frame testing -----------------------------------------------------

def frame_func

end

#---------- Test execution ----------------------------------------------------

test "warm-start" do
    conf_func(false)
    frame_func
    warm_start($ts)
end
