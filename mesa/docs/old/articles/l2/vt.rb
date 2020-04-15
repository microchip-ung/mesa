#!/usr/bin/env ruby

# DUT Configuration
# =================
#
# PORT1
# -----
# vlan-tagged
# vlan-member 10, 20, 30
# connected-to: eth_green
#
# PORT2
# -----
# vlan-member 10
# connected-to: eth_blue
#
# PORT3
# -----
# vlan-member 20, 30
# connected-to: eth_red
#

load_example "VT-code-example" do
    # Verify frame forwarding without any translation
    test "test frame forwarding" do
        frame_io_test(:timeout => 0.1) do
            bg  "ef RX eth_blue  ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 10 NULLPAD 100"
            run "ef TX eth_green ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 10 NULLPAD 100"
        end

        frame_io_test(:timeout => 0.1) do
            bg  "ef RX eth_red   NO FRAME"
            run "ef TX eth_green ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 10 NULLPAD 100"
        end
    end

    # enable bi-directional translation at port 1, from VLAN 10 to VLAN 20
    goto_step("vt_translation_config")

    # verify forwarding based on the added translation
    test "test vlan translation" do
        frame_io_test(:timeout => 0.1) do
            bg  "ef RX eth_blue  NO FRAME"
            run "ef TX eth_green ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 10 NULLPAD 100"
        end

        frame_io_test(:timeout => 0.1) do
            bg  "ef RX eth_red   ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 20 NULLPAD 100"
            run "ef TX eth_green ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 10 NULLPAD 100"
        end
    end

    # Verify translation is not yet operational on port 3, since port is not a member
    # of group 1 yet
    test "test frame forwarding2" do
        frame_io_test(:timeout => 0.1) do
            bg  "ef RX eth_red   ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 30 NULLPAD 100"
            run "ef TX eth_green ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 30 NULLPAD 100"
        end
    end

    # Make port 3 a member of the translation group 1
    goto_step("vt_port_config")
    # Verify that egress translation is now enabled on port 3
    test "test vlan translation2" do
        frame_io_test(:timeout => 0.1) do
            bg  "ef RX eth_red   ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 40 NULLPAD 100"
            run "ef TX eth_green ETH smac ::1 dmac ff:ff:ff:ff:ff:ff VLAN 30 NULLPAD 100"
        end
    end

    # clean up before leaving the test case
    goto_step(vt_clean_up)
end
