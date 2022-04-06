#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if Ingress ACL MAC update supported
cap_check_exit("ACL_MAC_IGR")

# Global port indices
idx_ctl = 0 # Controller port
idx_req = 1 # Device egress request port
idx_rep = 2 # Device ingress reply port
idx_swc = 3 # Other switch core port

# MAC addresses
mac_v = [0x70,0x16,0x9F,0x00,0xAC,0x0A] # v = 0xA (even unicast)
mac_w = [0x70,0x16,0x9F,0x00,0xAC,0x0B] # w = 0xB (odd unicast)
mac_x = [0x71,0x16,0x9F,0x00,0xAC,0x0C] # x = 0xC (even multicast)
mac_y = [0x71,0x16,0x9F,0x00,0xAC,0x0D] # y = 0xD (odd multicast)
mac_z = [0x70,0x16,0x9F,0x00,0xAC,0x01] # Other EtherCAT unicast
mac_o = [0x00,0x11,0x22,0x33,0x44,0x55] # Other unicast MAC address

# Ethernet type for EtherCAT
et_ecat = [0x88,0xa4]

def show_port(idx, name)
    port = $ts.dut.p[idx]
    chip_port = $ts.port_map[port]["chip_port"]
    t_i("Port #{name}: #{port}(#{chip_port}) - #{$ts.pc.p[idx]}")
end

# Show setup
show_port(idx_ctl, "ctl")
show_port(idx_req, "req")
show_port(idx_rep, "rep")
show_port(idx_ctl, "swc")

# Private VLAN table
test "conf-pvlan" do
    pvlan_table = [
        {
            # PVLAN 0 includes controller and switch ports
            id: 0,
            idx: [idx_ctl, idx_swc]
        },
        {
            # PVLAN 1 includes controller and device request ports
            id: 1,
            idx: [idx_ctl, idx_req]
        },
        {
            # PVLAN 2 includes controller and device reply port
            id: 2,
            idx: [idx_ctl, idx_rep]
        }
    ]
    pvlan_table.each do |e|
        $ts.dut.call("mesa_pvlan_port_members_set", e[:id], port_idx_list_str(e[:idx]))
    end
end

# ACL
test "conf-acl" do
    ace_table = [
        {
            # Controller port: Forward mac_w unicast request to device request port
            idx_rx: idx_ctl,
            dmac: mac_w,
            et: et_ecat,
            idx_tx: idx_req,
        },
        {
            # Controller port: Forward mac_x multicast request to device request port
            idx_rx: idx_ctl,
            dmac: mac_x,
            et: et_ecat,
            idx_tx: idx_req,
        },
        {
            # Controller port: Forward other frames to switch port only
            idx_rx: idx_ctl,
            idx_tx: idx_swc,
        },
        {
            # Reply port: Swap MAC addresses for mac_w unicast reply to controller port
            idx_rx: idx_rep,
            dmac: mac_w,
            et: et_ecat,
            idx_tx: idx_ctl,
            mac_igr: "MAC_SWAP"
        },
        {
            # Reply port: Increment DMAC and SMAC for mac_x multicast reply to controller port
            idx_rx: idx_rep,
            dmac: mac_x,
            smac: mac_v,
            et: et_ecat,
            idx_tx: idx_ctl,
            mac_igr: "DMAC_SMAC_INCR"
        },
        {
            # Reply port: Increment DMAC, replace SMAC for mac_x multicast reply to controller port
            idx_rx: idx_rep,
            dmac: mac_x,
            et: et_ecat,
            idx_tx: idx_ctl,
            mac_igr: "DMAC_INCR_SMAC_REPLACE",
            mac: mac_z
        },
    ]
    ace_table.each_with_index do |e, i|
        et = fld_get(e, :et, nil)
        type = ("MESA_ACE_TYPE_" + (et == nil ? "ANY" : "ETYPE"))
        ace = $ts.dut.call("mesa_ace_init", type)
        ace["id"] = (i + 1)
        ace["port_list"] = port_idx_list_str([e[:idx_rx]])
        if (et != nil)
            k = ace["frame"]["etype"]
            dmac = fld_get(e, :dmac, nil)
            if (dmac != nil)
                k["dmac"]["value"] = dmac
                k["dmac"]["mask"] = [0xff,0xff,0xff,0xff,0xff,0xff]
            end
            smac = fld_get(e, :smac, nil)
            if (smac != nil)
                k["smac"]["value"] = smac
                k["smac"]["mask"] = [0xff,0xff,0xff,0xff,0xff,0xff]
            end
            k["etype"]["value"] = et
            k["etype"]["mask"] = [0xff,0xff]
        end
        action = ace["action"]
        action["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
        action["port_list"] = port_idx_list_str([e[:idx_tx]])
        mac_igr = fld_get(e, :mac_igr, nil)
        if (mac_igr != nil)
            addr = action["addr"]
            addr["update"] = ("MESA_ACL_ADDR_UPDATE_IGR_" + mac_igr)
            mac = fld_get(e, :mac, nil)
            if (mac != nil)
                addr["mac"]["addr"] = mac
            end
        end
        $ts.dut.call("mesa_ace_add", 0, ace)
    end
end

# Frame test table
test_table = [
    {
        txt: "Traffic from switch port to controller port",
        idx_tx: idx_swc,
        idx_rx: idx_ctl,
        f_tx: {et: 0xabcd}
    },
    {
        txt: "Traffic from controller port to switch port",
        idx_tx: idx_ctl,
        idx_rx: idx_swc,
    },
    {
        txt: "Unicast Request mac_w/mac_v from controller to device",
        idx_tx: idx_ctl,
        idx_rx: idx_req,
        f_tx: {dmac: mac_w, smac: mac_v},
    },
    {
        txt: "Unicast Request mac_w/mac_o from controller to device",
        idx_tx: idx_ctl,
        idx_rx: idx_req,
        f_tx: {dmac: mac_w, smac: mac_o},
    },
    {
        txt: "Multicast Request mac_x/mac_v from controller to device",
        idx_tx: idx_ctl,
        idx_rx: idx_req,
        f_tx: {dmac: mac_x, smac: mac_v},
    },
    {
        txt: "Multicast Request mac_x/mac_o from controller to device",
        idx_tx: idx_ctl,
        idx_rx: idx_req,
        f_tx: {dmac: mac_x, smac: mac_o},
    },
    {
        txt: "Unicast Reply mac_w/mac_v from device to controller",
        idx_tx: idx_rep,
        idx_rx: idx_ctl,
        f_tx: {dmac: mac_w, smac: mac_v},
        f_rx: {dmac: mac_v, smac: mac_w},
    },
    {
        txt: "Unicast Reply mac_w/mac_o from device to controller",
        idx_tx: idx_rep,
        idx_rx: idx_ctl,
        f_tx: {dmac: mac_w, smac: mac_o},
        f_rx: {dmac: mac_o, smac: mac_w},
    },
    {
        txt: "Multicast Reply mac_x/mac_v from device to controller",
        idx_tx: idx_rep,
        idx_rx: idx_ctl,
        f_tx: {dmac: mac_x, smac: mac_v},
        f_rx: {dmac: mac_y, smac: mac_w},
    },
    {
        txt: "Multicast Reply mac_x/mac_o from device to controller",
        idx_tx: idx_rep,
        idx_rx: idx_ctl,
        f_tx: {dmac: mac_x, smac: mac_o},
        f_rx: {dmac: mac_y, smac: mac_z},
    },
]

def cmd_frame_push(f)
    cmd = " eth"
    dmac = fld_get(f, :dmac, [0xff,0xff,0xff,0xff,0xff,0xff])
    cmd += (" dmac " + mac_to_txt(dmac))
    smac = fld_get(f, :smac, [0x00,0x00,0x00,0x00,0x00,0x01])
    cmd += (" smac " + mac_to_txt(smac))
    et = fld_get(f, :et, 0x88a4)
    cmd += " et 0x#{et.to_s(16)} data repeat 46 0xff"
end

def ethercat_test(t)
    idx_tx = fld_get(t, :idx_tx)
    idx_rx = fld_get(t, :idx_rx)
    f_tx = fld_get(t, :f_tx, nil)
    f_rx = fld_get(t, :f_rx, f_tx)

    cmd = ("sudo ef name f_tx" + cmd_frame_push(f_tx))
    cmd += (" name f_rx" + cmd_frame_push(f_rx))
    cmd += " tx #{$ts.pc.p[idx_tx]} name f_tx"
    [0,1,2,3].each do |idx|
        cmd += " rx #{$ts.pc.p[idx]}"
        if (idx == idx_rx)
            cmd += " name f_rx"
        end
    end
    $ts.pc.run(cmd)

    # Check that SMAC has been learned correctly
    smac = fld_get(f_rx, :smac, [0x00,0x00,0x00,0x00,0x00,0x01])
    entry = $ts.dut.try("mesa_mac_table_get", {vid: 1, mac: {addr: smac}})
    msg = "SMAC #{mac_to_txt(smac)}"
    if (entry == nil)
        t_e(msg + " not learned")
    else
        exp = "#{$ts.dut.p[idx_tx]}"
        port = entry["destination"]
        msg += ", port: #{port}, exp: #{exp}"
        if (port == exp)
            t_i(msg)
        else
            t_e(msg)
        end
    end
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    test t[:txt] do
        ethercat_test(t)
    end
end

test "dump" do
    break
    #$ts.dut.run("mesa-cmd deb api ci acl")
    $ts.dut.run("mesa-cmd mac dump")
end
