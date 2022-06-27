#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'

$ts = get_test_setup("mesa_pc_b2b_4x")

# Check if HACL supported
cap_check_exit("ACL_HACL")

#---------- Configuration -----------------------------------------------------

$router_mac = [0,1,2,3,4,5]
$dip_ipv4_mc = "225.1.2.3"
$dmac_ipv4_mc = "01:00:5e:01:02:03"
$dip_ipv6_mc = "ff00::0102:0304"
$dmac_ipv6_mc = "33:33:01:02:03:04"

$conf_table =
    [
     {
         idx: 0,
         rleg: 10,
         vid: 10,
         ip: "1.1.1.1",
         ipv6: "2000::0101:0101",
         mac: [0,0,1,1,1,1]
     },
     {
         idx: 1,
         rleg: 20,
         vid: 20,
         ip: "2.2.2.2",
         ipv6: "2000::0202:0202",
         mac: [0,0,2,2,2,2]
     },
     {
         idx: 2, 
         rleg: 30,
         vid: 30,
         ip: "3.3.3.3",
         ipv6: "2000::0303:0303",
         mac: [0,0,3,3,3,3]
     },
     {
         idx: 3,
         rleg: 40,
         vid: 40,
         ip: "4.4.4.4",
         ipv6: "2000::0404:0404",
         mac: [0,0,4,4,4,4]
     },
    ]

test "conf" do
    test "enable routing" do
        conf = $ts.dut.call("mesa_l3_common_get")
        conf["rleg_mode"] = "MESA_ROUTING_RLEG_MAC_MODE_SINGLE"
        conf["base_address"] = {addr: $router_mac}
        conf["routing_enable"] = true
        conf["mc_routing_enable"] = true
        $ts.dut.call("mesa_l3_common_set", conf)
    end

    $conf_table.each do |e|
        port = $ts.dut.p[e[:idx]]
        test "port #{port}, vid #{e[:vid]}, dip #{e[:ip]}/#{e[:ipv6]}" do
            conf = $ts.dut.call("mesa_vlan_port_conf_get", port)
            conf["port_type"] = "MESA_VLAN_PORT_TYPE_C"
            conf["pvid"] = e[:vid]
            conf["untagged_vid"] = e[:vid]
            $ts.dut.call("mesa_vlan_port_conf_set", port, conf)
            $ts.dut.call("mesa_vlan_port_members_set", e[:vid], "#{port}")
            
            rl = {
                rleg_enable: true,
                rleg_id: e[:rleg],
                ipv4_unicast_enable: true,
                ipv6_unicast_enable: true,
                ipv4_multicast_enable: true,
                ipv6_multicast_enable: true,
                ipv4_icmp_redirect_enable: false,
                ipv6_icmp_redirect_enable: false,
                vlan: e[:vid],
                vrid0_enable: false,
                vrid0: 0,
                vrid1_enable: true,
                vrid1: 0,
                mc_ttl_limit_enable: false,
                mc_ttl_limit: 0
            }
            $ts.dut.call("mesa_l3_rleg_add", rl)
            
            e[:cnt] = $ts.dut.call("mesa_l3_counters_rleg_get", e[:rleg])

            ipv4 = ipv4_str2int(e[:ip])
            rt = {
                type: "MESA_ROUTING_ENTRY_TYPE_IPV4_UC",
                route: {
                    ipv4_uc: {
                        network: {
                            address: (ipv4 & 0xffff0000),
                            prefix_size: 16
                        },
                        destination: ipv4
                    },
                },
                vlan: e[:vid]
            }
            $ts.dut.call("mesa_l3_route_add", rt)

            nb = {
                dmac: {
                    addr: e[:mac]
                },
                vlan: e[:vid],
                dip: {
                    type: "MESA_IP_TYPE_IPV4",
                    addr: {
                        ipv4: ipv4
                    }
                }
            }
            $ts.dut.call("mesa_l3_neighbour_add", nb)

            ipv6 = ipv6_str2arr(e[:ipv6])
            net = ipv6.dup
            net[14] = 0
            net[15] = 0
            rt = {
                type: "MESA_ROUTING_ENTRY_TYPE_IPV6_UC",
                route: {
                    ipv6_uc: {
                        network: {
                            address: {
                                addr: net
                            },
                            prefix_size: 112
                        },
                        destination: {
                            addr: ipv6
                        }
                    },
                },
                vlan: e[:vid]
            }
            $ts.dut.call("mesa_l3_route_add", rt)

            nb = {
                dmac: {
                    addr: e[:mac]
                },
                vlan: e[:vid],
                dip: {
                    type: "MESA_IP_TYPE_IPV6",
                    addr: {
                        ipv6: {
                            addr: ipv6
                        }
                    }
                }
            }
            $ts.dut.call("mesa_l3_neighbour_add", nb)
        end
    end

    $conf_table.each do |e|
        port = $ts.dut.p[e[:idx]]
        test "port #{port}, vid #{e[:vid]}, dip #{$dip_ipv4_mc}/#{$dip_ipv6_mc}" do
            mc = {
                type: false,
                route: {
                    ipv4_mc: {
                        group: ipv4_str2int($dip_ipv4_mc),
                        source: ipv4_str2int(e[:ip])
                    }
                },
                source_rleg: e[:vid]
            }
            $ts.dut.call("mesa_l3_mc_route_add", mc)
            $conf_table.each do |u|
                if (u[:idx] != e[:idx])
                    $ts.dut.call("mesa_l3_mc_route_rleg_add", mc, u[:vid])                    
                end
            end
            
            mc = {
                type: true,
                route: {
                    ipv6_mc: {
                        group: {
                            addr: ipv6_str2arr($dip_ipv6_mc)
                        },
                        source: {
                            addr: ipv6_str2arr(e[:ipv6])
                        }
                    }
                },
                source_rleg: e[:vid]
            }
            $ts.dut.call("mesa_l3_mc_route_add", mc)
            $conf_table.each do |u|
                if (u[:idx] != e[:idx])
                    $ts.dut.call("mesa_l3_mc_route_rleg_add", mc, u[:vid])                    
                end
            end
        end
    end
end

# IPv4 options are not tested, such frames are always redirected to CPU, so RACLs have no effect.
test_table =
    [
    {
        txt: "ipv4/fragment/MF",
        ace: {type: "IPV4", fragment: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "flags 1"},
        f_1: {}
    },
    {
        txt: "ipv4/ds",
        ace: {type: "IPV4", ds: {v: 15, m: 0xff}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "dscp 3 ecn 3"},
        f_1: {}
    },
    {
        txt: "ipv4/proto",
        ace: {type: "IPV4", proto: {v: 43, m: 0xff}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "proto 43"},
        f_1: {}
    },
    {
        txt: "ipv4/sip",
        ace: {type: "IPV4", sip: {v: 0x01010101, m: 0xffffffff}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {},
        f_1: {sip: "1.1.1.2"}
    },
    {
        txt: "ipv4/dip",
        ace: {type: "IPV4", dip: {v: 0x02020202, m: 0xffffffff}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {},
        f_1: {dip: "2.2.2.1"}
    },
    {
        txt: "ipv4/sport",
        ace: {type: "IPV4", proto: {v: 17, m: 0xff}, sport: {l: 10, h: 11}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "udp sport 11"},
        f_1: {cmd: "udp sport 12"}
    },
    {
        txt: "ipv4/dport",
        ace: {type: "IPV4", proto: {v: 6, m: 0xff}, dport: {l: 12, h: 13}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp dport 12"},
        f_1: {cmd: "tcp dport 14"}
    },
    {
        txt: "ipv4/fin",
        ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_fin: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp fin 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv4/syn",
        ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_syn: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp syn 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv4/rst",
        ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_rst: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp rst 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv4/psh",
        ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_psh: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp psh 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv4/ack",
        ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_ack: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp ack 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv4/urg",
        ace: {type: "IPV4", proto: {v: 6, m: 0xff}, tcp_urg: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp urg 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv4/data",
        ace: {type: "IPV4", proto: {v: 10, m: 0xff}, data: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "proto 10 data hex 010203040506"},
        f_1: {cmd: "proto 10 data hex 010203040507"}
    },
    {
        txt: "ipv4-mc/rleg",
        ace: {type: "IPV4", proto: {v: 10, m: 0xff}},
        idx_tx: 0,
        idx_rx: [1],
        dip: $dip_ipv4_mc,
        dmac: $dmac_ipv4_mc,
        f_0: {idx_rx: [2,3], cmd: "proto 10"},
        f_1: {idx_rx: [1,2,3]}
    },
    {
        txt: "ipv6/ds",
        ace: {type: "IPV6", ds: {v: 15, m: 0xff}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "dscp 3 ecn 3"},
        f_1: {}
    },
    {
        txt: "ipv6/proto",
        ace: {type: "IPV6", proto: {v: 43, m: 0xff}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "next 43"},
        f_1: {}
    },
    {
        txt: "ipv6/sip",
        ace: {type: "IPV6", sip: {v: [0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1], m: [0,0,0,0,0,0,0,0,0,0,0,0,0xff,0xff,0xff,0xff]}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {},
        f_1: {sip: "2000::0101:0102"}
    },
    {
        txt: "ipv6/dip",
        ace: {type: "IPV6", dip: {v: [0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2], m: [0,0,0,0,0,0,0,0,0,0,0,0,0xff,0xff,0xff,0xff]}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {},
        f_1: {dip: "2000::0202:0201"}
    },
    {
        txt: "ipv6/sport",
        ace: {type: "IPV6", proto: {v: 17, m: 0xff}, sport: {l: 10, h: 11}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "udp sport 11"},
        f_1: {cmd: "udp sport 12"}
    },
    {
        txt: "ipv6/dport",
        ace: {type: "IPV6", proto: {v: 6, m: 0xff}, dport: {l: 12, h: 13}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp dport 12"},
        f_1: {cmd: "tcp dport 14"}
    },
    {
        txt: "ipv6/fin",
        ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_fin: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp fin 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv6/syn",
        ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_syn: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp syn 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv6/rst",
        ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_rst: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp rst 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv6/psh",
        ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_psh: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp psh 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv6/ack",
        ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_ack: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp ack 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv6/urg",
        ace: {type: "IPV6", proto: {v: 6, m: 0xff}, tcp_urg: 1},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "tcp urg 1"},
        f_1: {cmd: "tcp"}
    },
    {
        txt: "ipv6/data",
        ace: {type: "IPV6", proto: {v: 10, m: 0xff}, data: {v: [1,2,3,4,5,6], m: [0xff,0xff,0xff,0xff,0xff,0xff]}},
        idx_tx: 0,
        idx_rx: [1],
        f_0: {cmd: "next 10 data hex 010203040506"},
        f_1: {cmd: "next 10 data hex 010203040507"}
    },
    {
        txt: "ipv6-mc/rleg",
        ace: {type: "IPV6", proto: {v: 10, m: 0xff}},
        idx_tx: 0,
        idx_rx: [1],
        dip: $dip_ipv6_mc,
        dmac: $dmac_ipv6_mc,
        f_0: {idx_rx: [2,3], cmd: "next 10"},
        f_1: {idx_rx: [1,2,3]}
    },
    ]

def cnt_update(cnt, name, len)
    n = (name + "_frames")
    cnt[n] = (cnt[n] + 1)
    n = (name + "_octets")
    cnt[n] = (cnt[n] + len)
end

def ace_test(t, acl)
    v = t[:ace]
    type = v[:type]
    ace = $ts.dut.call("mesa_hace_init", "MESA_ACE_TYPE_" + type)
    ace["id"] = 1
    k = ace["key"]

    idx_tx = t[:idx_tx]
    idx_rx = t[:idx_rx]
    iracl = (acl[0] == "I")
    [0, 1, 2, 3].each do |idx|
        add = false
        if (iracl)
            # I-RACL: Include ingress router leg
            if (idx == idx_tx)
                add = true
            end
        elsif (idx_rx.include?(idx))
            # E-RACL: Include egress router legs
            add = true
        end
        if (add)
            rleg = $conf_table[idx][:rleg]
            r = k["rleg_list"]["_private"]
            r[rleg / 8] = (r[rleg / 8] + (1 << (rleg % 8)))
        end
    end

    ipv6 = (v[:type] == "IPV6")
    if (ipv6)
        k = k["ipv6"]
    else
        k = k["ipv4"]
        ace_bit_set(k, "ttl", v, :ttl)
        ace_bit_set(k, "fragment", v, :fragment)
        ace_bit_set(k, "options", v, :options)
    end
    vcap_vm_set(k, "ds", v, :ds)
    vcap_vm_set(k, "proto", v, :proto)
    vcap_vm_set(k, "sip", v, :sip)
    vcap_vm_set(k, "dip", v, :dip)
    vcap_vm_set(k, "data", v, :data)
    ace_range_set(k, "sport", v, :sport)
    ace_range_set(k, "dport", v, :dport)
    ace_bit_set(k, "tcp_fin", v, :tcp_fin)
    ace_bit_set(k, "tcp_syn", v, :tcp_syn)
    ace_bit_set(k, "tcp_rst", v, :tcp_rst)
    ace_bit_set(k, "tcp_psh", v, :tcp_psh)
    ace_bit_set(k, "tcp_ack", v, :tcp_ack)
    ace_bit_set(k, "tcp_urg", v, :tcp_urg)
    
    action = ace["action"]
    action["port_action"] = "MESA_ACL_PORT_ACTION_FILTER"
    hacl_type = ("MESA_HACL_TYPE_" + acl)
    $ts.dut.call("mesa_hace_add", hacl_type, 0, ace)

    rmac = mac_to_txt($router_mac)
    name = ((ipv6 ? "ipv6" : "ipv4") + ((t[:txt].include? "mc") ? "mc" : "uc"))

    for i in 0..1 do
        t_i("#{t[:txt]} (#{i == 0 ? "filter" : "forward"})")
        f = (i == 0 ? t[:f_0] : t[:f_1])

        src = $conf_table[idx_tx]

        # SIP comes from ingress port or frame
        sip = (ipv6 ? src[:ipv6] : src[:ip])
        if (f.key?:sip)
            sip = f[:sip]
        end

        # DIP comes from egress port or test or frame
        dip = nil
        idx_rx = t[:idx_rx]
        if (idx_rx != nil)
            e = $conf_table[idx_rx[0]]
            dip = (ipv6 ? e[:ipv6] : e[:ip])
        end
        if (t.key?:dip)
            dip = t[:dip]
        end
        if (f.key?:dip)
            dip = f[:dip]
        end

        # Egress port comes from test or frame
        rx_name = "#{name}_received"
        if (i == 0 and !iracl)
            # E-RACL: Discard frame 0 by default
            idx_rx = []
        end
        if (f.key?:idx_rx)
            # Multicast: Forward to egress ports
            idx_rx = f[:idx_rx]
        end
        if (i == 0 and iracl)
            # I-RACL: Discard frame 0
            idx_rx = []
            rx_name = nil
        end
        
        # Frame length
        len = 64
        if (ipv6 and (f.key?:cmd))
            if (f[:cmd].include? "udp")
                # MAC + IPv6 + UDP + FCS
                len = (14 + 40 + 8 + 4)
            elsif (f[:cmd].include? "tcp")
                # MAC + IPv6 + TCP + FCS
                len = (14 + 40 + 20 + 4)
            end
        end

        cmd = "sudo ef"
        cmd_end = ""
        [0, 1, 2, 3].each do |idx|
            dmac = nil
            smac = nil
            ttl = ((t.key?:ttl) ? t[:ttl] : 64)
            dir = "rx"
            cnt = $conf_table[idx][:cnt]
            if (idx == idx_tx)
                # Ingress port and router leg
                dmac = rmac
                smac = mac_to_txt(src[:mac])
                dir = "tx"
                if (rx_name != nil)
                    cnt_update(cnt, rx_name, len)
                end
            elsif (idx_rx.include?(idx))
                # Egress port and router leg
                dst = $conf_table[idx]
                dmac = mac_to_txt(dst[:mac])
                smac = rmac
                ttl = (ttl - 1)
                cnt_update(cnt, "#{name}_transmitted", len)
            end
            cmd_end += " #{dir} #{$ts.pc.p[idx]}"
            if (dmac != nil)
                cmd_end += " name f#{idx}"
                if (t.key?:dmac)
                    dmac = t[:dmac]
                end
                cmd += " name f#{idx} eth dmac #{dmac} smac #{smac}"
                if (ipv6)
                    cmd += " ipv6 hlim"
                else
                    cmd += " ipv4 ttl"
                end
                cmd += " #{ttl} sip #{sip} dip #{dip}"
                if (f.key?:cmd)
                    cmd += " #{f[:cmd]}"
                end
            end
        end
        $ts.pc.run(cmd + cmd_end)
    end
    $ts.dut.call("mesa_hace_del", hacl_type, ace["id"])
end

# Run all or selected test
sel = table_lookup(test_table, :sel)
test_table.each do |t|
    next if (t[:sel] != sel)
    acl_list = ["IRACL", "ERACL"]
    #acl_list = ["IRACL"]
    txt = t[:txt]
    acl_list.each do |acl|
        t[:txt] = "#{acl}: #{txt}"
        test t[:txt] do
            ace_test(t, acl)
        end
    end
end

$conf_table.each do |e|
    rleg = e[:rleg]
    test "rleg #{rleg} counters" do
        cnt = $ts.dut.call("mesa_l3_counters_rleg_get", rleg)
        exp = e[:cnt]
        msg = "cnt: #{cnt}, exp: #{exp}"
        if (cnt == exp)
            t_i(msg)
        else
            t_e(msg)
        end
    end
end

test_summary
