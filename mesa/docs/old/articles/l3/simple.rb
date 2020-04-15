#!/usr/bin/env ruby

# DUT Configuration
# =================
#
# PORT1
# -----
# vlan-tagged
# vlan-member 10, 20
# connected-to: eth_green
#
# PORT2
# -----
# vlan-access 10
# connected-to: eth_blue
#
# PORT3
# -----
# vlan-access 20
# connected-to: eth_red
#
# VLAN10
# ------
# IP: 10.0.0.1/24
#
# VLAN20
# ------
# IP: 20.0.0.1/24
#

load_example "wire-rgby", "L3-simple-example" do
    goto_step("l3_vlan_config")

    test "test vlan connections" do
        frame_io_test(:timeout => 0.1) do
            bg  "ef RX eth_red   ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 10 NULLPAD 100"
            run "ef TX eth_green ETH smac ::1 dmac ff:ff:ff:ff:ff:ff         NULLPAD 100"
        end

        frame_io_test(:timeout => 0.1) do
            bg  "ef RX eth_green ETH smac ::2 dmac ff:ff:ff:ff:ff:ff VLAN 10 NULLPAD 100"
            run "ef TX eth_red   ETH smac ::2 dmac ff:ff:ff:ff:ff:ff         NULLPAD 100"
        end
    end

    goto_step("l3_basic_config")
end
