/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "vtss_api.h"

#if defined(VTSS_FEATURE_LAYER2)
#include "vtss_appl.h"
#include "vtss_appl_cli.h"

static const char *cli_bool_txt(BOOL enabled)
{
    return (enabled ? "Enabled " : "Disabled");
}

static const char *port_mode_txt(vtss_port_speed_t speed, BOOL fdx)
{
    switch (speed) {
    case VTSS_SPEED_10M:
        return (fdx ? "10fdx" : "10hdx");
    case VTSS_SPEED_100M:
        return (fdx ? "100fdx" : "100hdx");
    case VTSS_SPEED_1G:
        return (fdx ? "1Gfdx" : "1Ghdx");
    case VTSS_SPEED_2500M:
        return (fdx ? "2.5Gfdx" : "2.5Ghdx");
    case VTSS_SPEED_5G:
        return (fdx ? "5Gfdx" : "5Ghdx");
    case VTSS_SPEED_10G:
        return (fdx ? "10Gfdx" : "10Ghdx");
    default:
        return "?";
    }
}

static const char *port_if_txt(vtss_port_interface_t if_type)
{
    switch (if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION: return "N/C";
    case VTSS_PORT_INTERFACE_LOOPBACK:      return "LOOPBACK";
    case VTSS_PORT_INTERFACE_INTERNAL:      return "INTERNAL";
    case VTSS_PORT_INTERFACE_MII:           return "MII";
    case VTSS_PORT_INTERFACE_GMII:          return "GMII";
    case VTSS_PORT_INTERFACE_RGMII:         return "RGMII";
    case VTSS_PORT_INTERFACE_TBI:           return "TBI";
    case VTSS_PORT_INTERFACE_RTBI:          return "RTBI";
    case VTSS_PORT_INTERFACE_SGMII:         return "SGMII";
    case VTSS_PORT_INTERFACE_SGMII_2G5:     return "SGMII_2G5";
    case VTSS_PORT_INTERFACE_SERDES:        return "SERDES";
    case VTSS_PORT_INTERFACE_VAUI:          return "VAUI";
    case VTSS_PORT_INTERFACE_100FX:         return "100FX";
    case VTSS_PORT_INTERFACE_XAUI:          return "XAUI";
    case VTSS_PORT_INTERFACE_RXAUI:         return "RXAUI";
    case VTSS_PORT_INTERFACE_XGMII:         return "XGMII";
    case VTSS_PORT_INTERFACE_SPI4:          return "SPI4";
    case VTSS_PORT_INTERFACE_SGMII_CISCO:   return "SGMII_CISCO";
    case VTSS_PORT_INTERFACE_QSGMII:        return "QSGMII";
    case VTSS_PORT_INTERFACE_SFI:           return "SFI";
    }
    return "?   ";
}

/* Port configuration */
static void cli_cmd_port_conf(cli_req_t *req, BOOL state, BOOL mode, 
                              BOOL flow_control, BOOL max_length) 
{
    vtss_port_no_t          port, port_no;
    vtss_appl_port_conf_t   conf;
    vtss_appl_port_status_t status;
    vtss_port_interface_t   if_type;
    BOOL                    first = 1;
    char                    buf[80], *p;
    BOOL                    flow_control_enabled = 0;
    BOOL                    rx=0,tx=0;
    
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        port = iport2uport(port_no);
        if (req->port_list[port] == 0 || 
            vtss_appl_port_conf_get(req->appl_inst, port_no, &conf) != VTSS_RC_OK ||
            vtss_appl_port_status_get(req->appl_inst, port_no, &status) != VTSS_RC_OK ||
            vtss_appl_port_if_get(req->appl_inst, port_no, &if_type) != VTSS_RC_OK)
            continue;

        if (req->set) {
            if (mode) {
                conf.autoneg = req->auto_keyword;
                if (!conf.autoneg) {
                  conf.speed = req->speed;
                  conf.fdx = req->fdx;
                }
              } 
              if (state)
                conf.enable = req->enable;
              if (flow_control)
                conf.flow_control = req->enable;
              if (max_length)
                conf.max_length = req->value;
              if (vtss_appl_port_conf_set(req->appl_inst, port_no, &conf) != VTSS_RC_OK) 
                printf("Could not configure port %u\n", iport2uport(port_no));                                                                                            
        } else {
            if (first) {
                p = &buf[0];
                p += sprintf(p, "Port  ");
                if (state)
                    p += sprintf(p, "State     ");
                if (mode)
                    p += sprintf(p, "Mode    ");
                if (flow_control) {
                    p += sprintf(p, "Flow Control  ");
                    if (!state)
                        p += sprintf(p, "Rx Pause  Tx Pause  ");
                }
                if (max_length)
                    p += sprintf(p, "MaxFrame  ");
                if (mode) {
                    p += sprintf(p, "Link      ");
                    p += sprintf(p, "Interface ");
                }
                
                cli_table_header(buf);
                first = 0;
            }
            printf("%-6u", port);
            
            if (state)
                printf("%-10s", cli_bool_txt(conf.enable));
            if (mode)
                printf("%-8s", 
                       conf.autoneg ? "Auto" : port_mode_txt(conf.speed, conf.fdx));
            if (flow_control) {
                // Determine if 1G line ports have flow control enabled 
                rx = (conf.autoneg ? (status.link ? status.aneg.obey_pause : 0) :
                      conf.flow_control);
                tx = (conf.autoneg ? (status.link ? status.aneg.generate_pause : 0) :
                      conf.flow_control);
                
                flow_control_enabled = conf.flow_control;
                
                printf("%-14s", cli_bool_txt(flow_control_enabled));                    
                
                if (!state)
                    printf("%s  %s  ", cli_bool_txt(rx), cli_bool_txt(tx));
            }
            if (max_length)
                printf("%-10u", conf.max_length);
            if (mode) {
                printf("%-10s", status.link ? port_mode_txt(status.speed, status.fdx) : "Down");
                printf("%s", port_if_txt(if_type));
            }
            printf("\n");
        }
    }
}

static void cli_cmd_port_conf_all(cli_req_t *req)
{
    cli_cmd_port_conf(req, 1, 1, 1, 1);
}

static void cli_cmd_port_state(cli_req_t *req)
{
    cli_cmd_port_conf(req, 1, 0, 0, 0);
}

static void cli_cmd_port_mode(cli_req_t *req)
{
    cli_cmd_port_conf(req, 0, 1, 0, 0);
}

static void cli_cmd_port_flow_control(cli_req_t *req)
{
    cli_cmd_port_conf(req, 0, 0, 1, 0);
}

static void cli_cmd_port_max_frame(cli_req_t *req)
{
    cli_cmd_port_conf(req, 0, 0, 0, 1);
}

static void cli_cmd_port_forward(cli_req_t *req)
{
    vtss_port_no_t      uport, iport;
    vtss_port_forward_t forward;
    BOOL                first = 1;

    for (iport = 0; iport < VTSS_PORTS; iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            /* Skip port */
        } else if (req->set) {
            forward = (req->enable ? VTSS_PORT_FORWARD_ENABLED :
                       req->ingress ? VTSS_PORT_FORWARD_INGRESS :
                       req->egress ? VTSS_PORT_FORWARD_EGRESS : VTSS_PORT_FORWARD_DISABLED);
            if (vtss_port_forward_state_set(NULL, iport, forward) != VTSS_RC_OK) {
                printf("Could not set forwarding mode for port %u\n", uport);
            }
        } else if (vtss_port_forward_state_get(NULL, iport, &forward) != VTSS_RC_OK) {
            printf("Could not get forwarding mode for port %u\n", uport);
        } else {
            if (first) {
                cli_table_header("Port  Forwarding");
                first = 0;
            }
            printf("%-6u%s\n",
                   uport,
                   forward == VTSS_PORT_FORWARD_INGRESS ? "Rx" :
                   forward == VTSS_PORT_FORWARD_EGRESS ? "Tx" : cli_bool_txt(forward == VTSS_PORT_FORWARD_ENABLED));
        }
    }
}

static void cli_cmd_port_loopback(cli_req_t *req)
{
    vtss_port_no_t        uport, iport;
    vtss_port_test_conf_t conf;
    BOOL                  first = 1;

    for (iport = 0; iport < VTSS_PORTS; iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 ||
            vtss_port_test_conf_get(NULL, iport, &conf) != VTSS_RC_OK) {
            continue;
        }

        if (req->set) {
            conf.loopback = (req->near_end ? VTSS_PORT_LB_NEAR_END :
                             req->far_end ? VTSS_PORT_LB_FAR_END :
                             req->facility ? VTSS_PORT_LB_FACILITY :
                             req->equipment ? VTSS_PORT_LB_EQUIPMENT : VTSS_PORT_LB_DISABLED);
            if (vtss_port_test_conf_set(NULL, iport, &conf) != VTSS_RC_OK) {
                printf("Loopback set failed for port %u\n", uport);
            }
        } else {
            if (first) {
                cli_table_header("Port  Loopback");
                first = 0;
            }
            printf("%-6u%s\n",
                   uport,
                   conf.loopback == VTSS_PORT_LB_NEAR_END ? "Near-End" :
                   conf.loopback == VTSS_PORT_LB_FAR_END ? "Far-End" :
                   conf.loopback == VTSS_PORT_LB_FACILITY ? "Facility" :
                   conf.loopback == VTSS_PORT_LB_EQUIPMENT ? "Equipment" : "Disabled");
        }
    }
}

/* Print counters in two columns with header */
static void cli_cmd_stat_port(vtss_port_no_t port, BOOL *first, const char *name, 
                              u64 c1, u64 c2)
{
    char buf[80], *p;

    if (*first) {
        *first = 0;
        p = &buf[0];
        p += sprintf(p, "Port  Rx %-17sTx %-17s", name, name);
        cli_table_header(buf);
    }
    printf("%-2u    %-20" PRIu64 "%-20" PRIu64 "\n", port, c1, c2);
}

/* Print two counters in columns */
static void cli_cmd_stats(const char *col1, const char *col2, u64 c1, u64 c2)
{
    char buf[80];
    
    sprintf(buf, "Rx %s:", col1);
    printf("%-19s%19" PRIu64 "   ", buf, c1);
    if (col2 != NULL) {
        sprintf(buf, "Tx %s:", strlen(col2) ? col2 : col1);
        printf("%-19s%19" PRIu64, buf, c2);
    }
    printf("\n");
}

#if defined(VTSS_ARCH_SPARX)
#define RMON_FRAME_MAX 1526
#else
#define RMON_FRAME_MAX 1518
#endif /* VTSS_ARCH_SPARX */

/* Port statistics */
static void cli_cmd_port_stats(cli_req_t *req)
{
    vtss_port_no_t                     port, port_no, i;
    vtss_port_counters_t               counters;
    vtss_port_rmon_counters_t          *rmon = &counters.rmon;
    vtss_port_if_group_counters_t      *if_group = &counters.if_group;
    vtss_port_ethernet_like_counters_t *elike = &counters.ethernet_like;
    vtss_port_proprietary_counters_t   *prop = &counters.prop;
    BOOL                               first = 1;
    char                               buf[32];

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        port = iport2uport(port_no);
        // Do only change setting for ports in the port list
        if (req->port_list[port] == 0) {
          continue;
        }
        /* Handle 'clear' command */
        if (req->clear) {
            vtss_port_counters_clear(req->api_inst, port_no);
            continue;
        }
            
        /* Get counters */
        if (vtss_port_counters_get(req->api_inst, port_no, &counters) != VTSS_RC_OK)
            continue;
        
        /* Handle 'packet' command */
        if (req->packets) {
            cli_cmd_stat_port(port, &first, "Packets", 
                              rmon->rx_etherStatsPkts, rmon->tx_etherStatsPkts);
            continue;
        } 
        
        /* Handle 'bytes' command */
        if (req->bytes) {
            cli_cmd_stat_port(port, &first, "Octets", 
                              rmon->rx_etherStatsOctets, rmon->tx_etherStatsOctets);
            continue;
        } 
        
        /* Handle 'errors' command */
        if (req->errors) {
            cli_cmd_stat_port(port, &first, "Errors", 
                              if_group->ifInErrors, if_group->ifOutErrors);
            continue;
        } 
        
        /* Handle 'discards' command */
        if (req->discards) {
            cli_cmd_stat_port(port, &first, "Discards", 
                              if_group->ifInDiscards, if_group->ifOutDiscards);
            continue;
        }
        
        /* Handle default command */
        printf("%sPort %u Statistics:\n\n", first ? "" : "\n", port);
        first = 0;
        cli_cmd_stats("Packets", "", rmon->rx_etherStatsPkts, rmon->tx_etherStatsPkts);
        cli_cmd_stats("Octets", "", rmon->rx_etherStatsOctets, rmon->tx_etherStatsOctets);
        cli_cmd_stats("Unicast", "", if_group->ifInUcastPkts, if_group->ifOutUcastPkts);
        cli_cmd_stats("Multicast", "", rmon->rx_etherStatsMulticastPkts, 
                      rmon->tx_etherStatsMulticastPkts);
        cli_cmd_stats("Broadcast", "", rmon->rx_etherStatsBroadcastPkts, 
                      rmon->tx_etherStatsBroadcastPkts);
        cli_cmd_stats("Pause", "", elike->dot3InPauseFrames, elike->dot3OutPauseFrames);
        printf("\n");
        cli_cmd_stats("64", "", rmon->rx_etherStatsPkts64Octets, 
                      rmon->tx_etherStatsPkts64Octets);
        cli_cmd_stats("65-127", "", rmon->rx_etherStatsPkts65to127Octets, 
                      rmon->tx_etherStatsPkts65to127Octets);
        cli_cmd_stats("128-255", "", rmon->rx_etherStatsPkts128to255Octets,
                      rmon->tx_etherStatsPkts128to255Octets);
        cli_cmd_stats("256-511", "", rmon->rx_etherStatsPkts256to511Octets,
                      rmon->tx_etherStatsPkts256to511Octets);
        cli_cmd_stats("512-1023", "", rmon->rx_etherStatsPkts512to1023Octets,
                      rmon->tx_etherStatsPkts512to1023Octets);
        sprintf(buf, "1024-%u", RMON_FRAME_MAX);
        cli_cmd_stats(buf, "", rmon->rx_etherStatsPkts1024to1518Octets,
                      rmon->tx_etherStatsPkts1024to1518Octets);
        sprintf(buf, "%u-    ", RMON_FRAME_MAX + 1);
        cli_cmd_stats(buf, "", rmon->rx_etherStatsPkts1519toMaxOctets,
                      rmon->tx_etherStatsPkts1519toMaxOctets);
        printf("\n");

        // The priority queues does not apply to the host interface
        for (i = 0; i < VTSS_PRIOS; i++) {              
            sprintf(buf, "Packets_%u", i);
            cli_cmd_stats(buf, "", prop->rx_prio[i], prop->tx_prio[i]);
        }
        printf("\n");
        
        cli_cmd_stats("Drops", "", rmon->rx_etherStatsDropEvents,
                      rmon->tx_etherStatsDropEvents);
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
        cli_cmd_stats("CRC/Alignment", "Late Collisions", rmon->rx_etherStatsCRCAlignErrors,
                      elike->dot3StatsLateCollisions);
        cli_cmd_stats("Symbol", "Excessive Coll.", elike->dot3StatsSymbolErrors,
                      elike->dot3StatsExcessiveCollisions);
        cli_cmd_stats("Undersize", "Carrier Sense", rmon->rx_etherStatsUndersizePkts,
                      elike->dot3StatsCarrierSenseErrors);
#else
        cli_cmd_stats("CRC/Alignment", "Late/Exc. Coll.", rmon->rx_etherStatsCRCAlignErrors,
                      if_group->ifOutErrors);
        cli_cmd_stats("Undersize", NULL, rmon->rx_etherStatsUndersizePkts, 0);
        
#endif /* VTSS_FEATURE_PORT_CNT_ETHER_LIKE */
        cli_cmd_stats("Oversize", NULL, rmon->rx_etherStatsOversizePkts, 0);
        cli_cmd_stats("Fragments", NULL, rmon->rx_etherStatsFragments, 0);
        cli_cmd_stats("Jabbers", NULL, rmon->rx_etherStatsJabbers, 0);
        cli_cmd_stats("Filtered", NULL, counters.bridge.dot1dTpPortInDiscards, 0);
    } /* Port loop */
}

static void cli_cmd_mac_add(cli_req_t *req)
{
    vtss_mac_table_entry_t entry;
    int                    i;
    vtss_port_no_t         port_no;

    memset(&entry, 0, sizeof(entry));
    entry.locked = 1;
    entry.vid_mac.vid = req->vid;
    for (i = 0; i < 6; i++)
        entry.vid_mac.mac.addr[i] = req->mac[i];
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)
        entry.destination[port_no] = (req->port_list[iport2uport(port_no)] ? 1 : 0);
    vtss_mac_table_add(req->api_inst, &entry);
}

static void cli_cmd_mac_del(cli_req_t *req)
{
    vtss_vid_mac_t vid_mac;
    int            i;
    
    vid_mac.vid = req->vid;
    for (i = 0; i < 6; i++)
        vid_mac.mac.addr[i] = req->mac[i];
    vtss_mac_table_del(req->api_inst, &vid_mac);
}

static char *cli_port_list_txt(BOOL port_list[VTSS_PORT_ARRAY_SIZE], char *buf)
{
    char           *p = buf;
    vtss_port_no_t port_no, port;
    int            first = 1, count = 0;
    BOOL           member;

    *p = '\0';
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        member = port_list[port_no];
        if ((member && 
             (count == 0 || port_no == (VTSS_PORT_NO_END - 1))) || (!member && count > 1)) {
            port = iport2uport(port_no);
            p += sprintf(p, "%s%u",
                         first ? "" : count > (member ? 1 : 2) ? "-" : ",",
                         member ? port : (port - 1));
            first = 0;
        }
        if (member)
            count++;
        else
            count=0;
    }
    if (p == buf)
        sprintf(p, "None");
    return buf;
}



static void cli_mac_print(vtss_mac_table_entry_t *entry, BOOL first)
{
    char buf[64];

    if (first)
        cli_table_header("Type    VID  MAC Address        Ports");
    printf("%s %-4d %s  ",
           entry->locked ? "Static " : "Dynamic",
           entry->vid_mac.vid, 
           cli_mac_txt(entry->vid_mac.mac.addr, buf));
    printf("%s%s\n",
           cli_port_list_txt(entry->destination, buf),
           entry->copy_to_cpu ? ",CPU" : "");
}

static void cli_cmd_mac_lookup(cli_req_t *req)
{
    vtss_mac_table_entry_t entry;
    int                    i;
    
    entry.vid_mac.vid = req->vid;
    for (i = 0; i < 6; i++)
        entry.vid_mac.mac.addr[i] = req->mac[i];
    if (vtss_mac_table_get(req->api_inst, &entry.vid_mac, &entry) == VTSS_RC_OK)
        cli_mac_print(&entry, 1);
}

static void cli_cmd_mac_dump(cli_req_t *req)
{
    vtss_mac_table_entry_t entry;
    BOOL                   first = 1; 

    memset(&entry, 0, sizeof(entry));
    while (vtss_mac_table_get_next(req->api_inst, &entry.vid_mac, &entry) == VTSS_RC_OK) {
        cli_mac_print(&entry, first);
        first = 0;
    }
}

static void cli_cmd_mac_flush(cli_req_t *req)
{
    vtss_mac_table_flush(req->api_inst);
}

static void cli_cmd_mac_age_time(cli_req_t *req)
{
    vtss_mac_table_age_time_t age_time;
    
    if (req->set)
        vtss_mac_table_age_time_set(req->api_inst, req->value);
    else if (vtss_mac_table_age_time_get(req->api_inst, &age_time) == VTSS_RC_OK)
        printf("Age Time: %u\n", age_time);
}

static void cli_cmd_transmit_port(cli_req_t *req)
{
    vtss_rc        rc;
    vtss_port_no_t port, port_no;
    u8             frame[64];

    /* NULL BC */
    memset(frame, 0, sizeof(frame));
    memset(frame, 0xff, 6);
    frame[6+0] = 0x11;
    frame[6+1] = 0x22;
    frame[6+2] = 0x33;
    frame[6+3] = 0x44;
    frame[6+4] = 0x55;
    frame[6+5] = 0x66;

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        port = iport2uport(port_no);
        if (req->port_list[port]) {
            printf("Transmit %d\n", port);
            if ((rc = vtss_packet_tx_frame_port(NULL, port_no, frame, sizeof(frame))) != VTSS_RC_OK) {
                T_E("tx failure: rc %d", rc);
            }
        }
    }
}

static vtss_rc board_or_api_tx(struct vtss_appl_board_t   *board, 
                               const vtss_packet_tx_ifh_t *const ifh,
                               const u8                   *const frame,
                               const u32                   length)
{
    return (board->board_transmit ? board->board_transmit(board, ifh, frame, length) :
            vtss_packet_tx_frame(NULL, ifh, frame, length));
}


static void cli_cmd_transmit_frame(cli_req_t *req, BOOL switched)
{
    static u8 sendbuf[200] = {
        0x01, 0x80, 0xc2, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 0x00, 0x71, 0xff, 0xaa, 0xbb, 0xcc, 0xdd,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    vtss_packet_tx_ifh_t ifh;
    vtss_packet_tx_info_t tx_info;

    vtss_packet_tx_info_init(NULL, &tx_info);
    if (switched) {
        tx_info.tag.vid = req->vid;
        tx_info.switch_frm = TRUE;
        printf("Tx VID %d (switched)\n", tx_info.tag.vid);
    } else {
        vtss_port_no_t port_no;
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)  {
            if(req->port_list[iport2uport(port_no)]) {
                tx_info.dst_port_mask |= (1 << port_no);
            }
        }
        printf("Tx port mask 0x%" PRIx64 "\n", tx_info.dst_port_mask);
    }
    if (vtss_packet_tx_hdr_compile(NULL, &tx_info, &ifh) != VTSS_RC_OK ||
        board_or_api_tx(req->board, &ifh, sendbuf, sizeof(sendbuf)) != VTSS_RC_OK) { 
        printf("vtss_packet_tx_hdr_compile/vtss_packet_tx_frame(): Error\n");
    }
}

static void cli_cmd_transmit_vlan(cli_req_t *req)
{
    cli_cmd_transmit_frame(req, TRUE);
}

static void cli_cmd_vlan_add(cli_req_t *req)
{
    vtss_port_no_t iport;
    BOOL           member[VTSS_PORTS];

    for (iport = 0; iport < VTSS_PORTS; iport++) {
        member[iport] = req->port_list[iport2uport(iport)];
    }
    (void)vtss_vlan_port_members_set(NULL, req->vid, member);
}

static void cli_cmd_vlan_del(cli_req_t *req)
{
    BOOL member[VTSS_PORTS];

    memset(member, 0, sizeof(member));
    (void)vtss_vlan_port_members_set(NULL, req->vid, member);
}

#define CLI_CMD_VLAN_TYPE   1
#define CLI_CMD_VLAN_PVID   2
#define CLI_CMD_VLAN_UVID   3
#define CLI_CMD_VLAN_FRAME  4
#define CLI_CMD_VLAN_FILTER 5

static void cli_cmd_vlan_port_conf(cli_req_t *req, u8 cmd)
{
    vtss_port_no_t        iport, uport;
    vtss_vlan_port_conf_t conf;
    vtss_vid_t            vid;
    BOOL                  member[VTSS_PORTS];
    char                  buf[64];
    BOOL                  skip, header = TRUE;

    /* Set/show port configuration */
    for (iport = 0; iport < VTSS_PORTS; iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 || vtss_vlan_port_conf_get(NULL, iport, &conf) != VTSS_RC_OK)
            continue;

        if (req->set) {
            if (cmd == CLI_CMD_VLAN_TYPE) {
                conf.port_type = req->port_type;
            } else if (cmd == CLI_CMD_VLAN_PVID) {
                conf.pvid = req->vid;
            } else if (cmd == CLI_CMD_VLAN_UVID) {
                conf.untagged_vid = (req->vid == VTSS_VID_DEFAULT ? conf.pvid : req->vid);
            } else if (cmd == CLI_CMD_VLAN_FRAME) {
                conf.frame_type = req->frame_type;
            } else if (cmd == CLI_CMD_VLAN_FILTER) {
                conf.ingress_filter = req->enable;
            }
            (void)vtss_vlan_port_conf_set(NULL, iport, &conf);
            continue;
        }

        if (header) {
            header = FALSE;
            cli_table_header("Port  Type      PVID  UVID  Frame     Filter");
        }
        printf("%-6u%-10s%-6u%-6u%-10s%s\n",
               uport,
               conf.port_type == VTSS_VLAN_PORT_TYPE_UNAWARE ? "Unaware" :
               conf.port_type == VTSS_VLAN_PORT_TYPE_C ? "C-port" :
               conf.port_type == VTSS_VLAN_PORT_TYPE_S ? "S-port" : "?",
               conf.pvid,
               conf.untagged_vid,
               conf.frame_type == VTSS_VLAN_FRAME_ALL ? "All" :
               conf.frame_type == VTSS_VLAN_FRAME_TAGGED ? "Tagged" :
               conf.frame_type == VTSS_VLAN_FRAME_UNTAGGED ? "Untagged" : "?",
               cli_bool_txt(conf.ingress_filter));
    }

    /* Show VLAN table */
    header = TRUE;
    for (vid = VTSS_VID_DEFAULT; !req->set && vid < VTSS_VIDS; vid++) {
        if (vtss_vlan_port_members_get(NULL, vid, member) != VTSS_RC_OK)
            continue;

        skip = TRUE;
        for (iport = 0; iport < VTSS_PORTS; iport++) {
            if (member[iport]) {
                skip = FALSE;
                break;
            }
        }
        if (skip)
            continue;

        if (header) {
            header = FALSE;
            printf("\n");
            cli_table_header("VID   Ports");
        }
        printf("%-6u%s\n", vid, cli_port_list_txt(member, buf));
    }
}

static void cli_cmd_vlan_port_type(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_TYPE);
}

static void cli_cmd_vlan_port_pvid(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_PVID);
}

static void cli_cmd_vlan_port_uvid(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_UVID);
}

static void cli_cmd_vlan_port_frame(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_FRAME);
}

static void cli_cmd_vlan_port_filter(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_FILTER);
}

/* Debug PHY read/write */
static void cli_cmd_debug_phy(cli_req_t *req, BOOL write)
{
    vtss_port_no_t port, port_no;
    int            i, addr, first = 1;
    u32            reg;
    u16            value;

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        port = iport2uport(port_no);
        if (req->port_list[port] == 0)
            continue;

        for (addr = 0; addr < CLI_PHY_MAX; addr++) {
            if (req->addr_list[addr] == 0)
                continue;

            reg = ((req->page << 5) | addr);
            if (write) {
                /* Write */
                vtss_phy_write(req->api_inst, port_no, reg, req->value);
            } else if (vtss_phy_read(req->api_inst, port_no, reg, &value) == VTSS_RC_OK) {
                /* Read success */
                if (first) {
                    first = 0;
                    cli_table_header("Port  Addr  15******8*7*******0  Value");
                }
                
                printf("%-6u0x%02x  ", port, addr);
                for (i = 15; i >= 0; i--)
                    printf("%d%s", value & (1<<i) ? 1 : 0, (i % 4) || i == 0 ? "" : ".");
                printf("  0x%04x\n", value);
            }
        }
    }
}

static void cli_cmd_debug_phy_read(cli_req_t *req)
{
    cli_cmd_debug_phy(req, 0);
}

static void cli_cmd_debug_phy_write(cli_req_t *req)
{
    cli_cmd_debug_phy(req, 1);
}

/* Debug MIIMread/write */
static void cli_cmd_debug_miim(cli_req_t *req, BOOL write)
{
    vtss_miim_controller_t miim_controller = VTSS_MIIM_CONTROLLER_0;
    int                    i, addr, first = 1;
    u16                    value;

    for (addr = 0; addr < CLI_PHY_MAX; addr++) {
        if (req->addr_list[addr] == 0)
            continue;

        if (write) {
            /* Write */
            vtss_miim_write(req->api_inst, 0, miim_controller, req->miim_addr, addr, req->value);
        } else if (vtss_miim_read(req->api_inst, 0, miim_controller, req->miim_addr, addr, &value) == VTSS_RC_OK) {
            /* Read success */
            if (first) {
                first = 0;
                cli_table_header("MIIM  Addr  15******8*7*******0  Value");
            }

            printf("%-6u0x%02x  ", req->miim_addr, addr);
            for (i = 15; i >= 0; i--)
                printf("%d%s", value & (1<<i) ? 1 : 0, (i % 4) || i == 0 ? "" : ".");
            printf("  0x%04x\n", value);
        }
    }
}

static void cli_cmd_debug_miim_read(cli_req_t *req)
{
    cli_cmd_debug_miim(req, 0);
}

static void cli_cmd_debug_miim_write(cli_req_t *req)
{
    cli_cmd_debug_miim(req, 1);
}

static void cli_cmd_debug_symreg_read(cli_req_t *req)
{
    symreg_cli_regs_print(SYMREG_READ, req->pattern, 0);
}

static void cli_cmd_debug_symreg_write(cli_req_t *req)
{
    symreg_cli_regs_print(SYMREG_WRITE, req->pattern, req->value);
}

static void cli_cmd_debug_symreg_query(cli_req_t *req)
{
    symreg_cli_regs_print(SYMREG_QUERY, req->pattern, 0);
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Port Configuration [<port_list>]",
        "Show port configuration",
        cli_cmd_port_conf_all
    },
    {
        "Port State [<port_list>] [enable|disable]",
        "Set or show the port administrative state",
        cli_cmd_port_state
    },
    {
        "Port Mode [<port_list>] [10hdx|10fdx|100hdx|100fdx|1000fdx|2500fdx|10gfdx|auto]",
        "Set or show the port speed and duplex mode",
        cli_cmd_port_mode
    },
    {
        "Port Flow Control [<port_list>] [enable|disable]",
        "Set or show the port flow control mode",
        cli_cmd_port_flow_control
    },
    {
        "Port MaxFrame [<port_list>] [<max_frame>]",
        "Set or show the port maximum frame size",
        cli_cmd_port_max_frame
    },
    {
        "Port Forwarding [<port_list>] [enable|disable|rx|tx]",
        "Set or show the port forwarding mode",
        cli_cmd_port_forward
    },
    {
        "Port Loopback [<port_list>] [near-end|far-end|facility|equipment] [enable|disable]",
        "Set or show the port forwarding mode",
        cli_cmd_port_loopback
    },
    {
        "Port Statistics [<port_list>] [clear|packets|bytes|errors|discards]",
        "Show port statistics",
        cli_cmd_port_stats
    },
    {
        "MAC Add <mac_addr> <port_list> [<vid>]",
        "Add MAC address table entry",
        cli_cmd_mac_add
    },
    {
        "MAC Delete <mac_addr> [<vid>]",
        "Delete MAC address entry",
        cli_cmd_mac_del
    },
    {
        "MAC Lookup <mac_addr> [<vid>]",
        "Lookup MAC address entry",
        cli_cmd_mac_lookup
    },
    {
        "MAC Dump",
        "Show sorted list of MAC address entries",
        cli_cmd_mac_dump
    },
    {
        "MAC Flush",
        "Flush all learned entries",
        cli_cmd_mac_flush
    },
    {
        "MAC Agetime [<age_time>]",
        "Set or show the MAC address age timer",
        cli_cmd_mac_age_time
    },
    {
        "Transmit Port <port_list>]",
        "Transmit (broadcast) on port - using vtss_packet_tx_frame_port",
        cli_cmd_transmit_port
    },
    {
        "Transmit VLAN <vid>",
        "Transmit packet on vlan - using vtss_packet_tx_frame() ",
        cli_cmd_transmit_vlan
    },
    {
        "VLAN Add <vid> <port_list>",
        "Add VLAN",
        cli_cmd_vlan_add
    },
    {
        "VLAN Delete <vid>",
        "Delete VLAN",
        cli_cmd_vlan_del
    },
    {
        "VLAN Type [<port_list>] [unaware|c-port|s-port]",
        "Set or show VLAN port type",
        cli_cmd_vlan_port_type
    },
    {
        "VLAN PVID [<port_list>] [<vid>]",
        "Set or show port VLAN ID",
        cli_cmd_vlan_port_pvid
    },
    {
        "VLAN UVID [<port_list>] [all|none|pvid]",
        "Set or show Tx untagged VID",
        cli_cmd_vlan_port_uvid
    },
    {
        "VLAN Frame [<port_list>] [all|tagged|untagged]",
        "Set or show accepted frame type",
        cli_cmd_vlan_port_frame
    },
    {
        "VLAN Filter [<port_list>] [enable|disable]",
        "Set or show VLAN ingress filtering",
        cli_cmd_vlan_port_filter
    },
    {
        "Debug PHY Read <port_list> <addr_list> [<page>]",
        "Read PHY register",
        cli_cmd_debug_phy_read
    },
    {
        "Debug PHY Write <port_list> <addr_list> <value> [<page>]",
        "Write PHY register",
        cli_cmd_debug_phy_write
    },
    {
        "Debug MIIM Read <miim_addr> <addr_list>",
        "Read MIIM register",
        cli_cmd_debug_miim_read
    },
    {
        "Debug MIIM Write <miim_addr> <addr_list> <value>",
        "Write MIIM register",
        cli_cmd_debug_miim_write
    },
    {
        "Debug Sym Read <word128>",
        "Read one/many switch register(s)",
        cli_cmd_debug_symreg_read
    },
    {
        "Debug Sym Write <word128> <value32>",
        "Write one/many switch register(s)",
        cli_cmd_debug_symreg_write
    },
    {
        "Debug Sym Query <word128>",
        "Display the matched register(s)",
        cli_cmd_debug_symreg_query
    },
};

static int cli_parm_age_time(cli_req_t *req)
{
    int error;
    u32 value;

    error = (cli_parm_u32(req, &value, 0, 1000000) || (value != 0 && value < 10));
    if (!error)
        req->value = value;
    return error;
}

static int cli_parm_keyword(cli_req_t *req)
{
    char *found;
    
    if ((found = cli_parse_find(req->cmd, req->stx)) == NULL)
        return 1;

    if (!strncmp(found, "auto", 4))
        req->auto_keyword = 1;
    else if (!strncmp(found, "all", 3)) {
        req->vid = VTSS_VID_ALL;
        req->frame_type = VTSS_VLAN_FRAME_ALL;
    } else if (!strncmp(found, "bytes", 5))
        req->bytes = 1;
    else if (!strncmp(found, "clear", 5))
        req->clear = 1;
    else if (!strncmp(found, "cool", 4))
        req->warm = 0;
    else if (!strncmp(found, "c-port", 6))
        req->port_type = VTSS_VLAN_PORT_TYPE_C;
    else if (!strncmp(found, "debug", 5))
        req->level = VTSS_TRACE_LEVEL_DEBUG;
    else if (!strncmp(found, "discards", 8))
        req->discards = 1;
    else if (!strncmp(found, "disable", 7))
        req->disable = 1;
    else if (!strncmp(found, "equipment", 9))
        req->equipment = 1;
    else if (!strncmp(found, "errors", 6))
        req->errors = 1;
    else if (!strncmp(found, "enable", 6))
        req->enable = 1;
    else if (!strncmp(found, "facility", 8))
        req->facility = 1;
    else if (!strncmp(found, "far-end", 7))
        req->far_end = 1;
    else if (!strncmp(found, "full", 4))
        req->full = 1;
    else if (!strncmp(found, "info", 4))
        req->level = VTSS_TRACE_LEVEL_INFO;
    else if (!strncmp(found, "near-end", 8))
        req->near_end = TRUE;
    else if (!strncmp(found, "noise", 5))
        req->level = VTSS_TRACE_LEVEL_NOISE;
    else if (!strncmp(found, "none", 4))
        req->vid = VTSS_VID_NULL;
    else if (!strncmp(found, "off", 3))
        req->level = VTSS_TRACE_LEVEL_NONE;
    else if (!strncmp(found, "packets", 7))
        req->packets = 1;
    else if (!strncmp(found, "pvid", 4))
        req->vid = VTSS_VID_DEFAULT;
    else if (!strncmp(found, "rx", 2))
        req->ingress = 1;
    else if (!strncmp(found, "s-port", 6))
        req->port_type = VTSS_VLAN_PORT_TYPE_S;
    else if (!strncmp(found, "tagged", 6))
        req->frame_type = VTSS_VLAN_FRAME_TAGGED;
    else if (!strncmp(found, "tx", 2))
        req->egress = 1;
    else if (!strncmp(found, "untagged", 8))
        req->frame_type = VTSS_VLAN_FRAME_UNTAGGED;
    else if (!strncmp(found, "unaware", 7))
        req->port_type = VTSS_VLAN_PORT_TYPE_UNAWARE;
    else if (!strncmp(found, "warm", 4))
        req->warm = 1;
    else if (!strncmp(found, "10hdx", 5))
        req->speed = VTSS_SPEED_10M;
    else if (!strncmp(found, "10fdx", 5)) {
        req->speed = VTSS_SPEED_10M;
        req->fdx = 1;
    } else if (!strncmp(found, "100hdx", 6))
        req->speed = VTSS_SPEED_100M;
    else if (!strncmp(found, "100fdx", 6)) { 
        req->speed = VTSS_SPEED_100M;
        req->fdx = 1;
    } else if (!strncmp(found, "1000fdx", 7)) {
        req->speed = VTSS_SPEED_1G;
        req->fdx = 1;    
    } else if (!strncmp(found, "2500fdx", 7)) {
        req->speed = VTSS_SPEED_2500M;
        req->fdx = 1;
    } else if (!strncmp(found, "10gfdx", 7)) {
        req->speed = VTSS_SPEED_10G;
        req->fdx = 1;
    } else
        printf("no match:%s\n", found);
    
    return 0;
}

static int cli_parm_max_frame(cli_req_t *req)
{
    return cli_parm_u32(req, &req->value, VTSS_MAX_FRAME_LENGTH_STANDARD, VTSS_MAX_FRAME_LENGTH_MAX);
} 

static int cli_parm_addr_list(cli_req_t *req)
{
    return cli_parse_list(req->cmd, req->addr_list, 0, 31, 0);
}

static int cli_parm_page(cli_req_t *req)
{
    return cli_parm_u32(req, &req->page, 0, 0xffff);
}

static int cli_parm_miim_addr(cli_req_t *req)
{
    return cli_parm_u8(req, &req->miim_addr, 0, 31);
}

static int cli_parm_reg_pattern(cli_req_t *req)
{
    size_t cnt = strlen(req->cmd);

    if (cnt + 1 > sizeof(req->pattern)) {
        printf("Pattern length must be maximum %zu characters!\n", sizeof(req->pattern) - 1);
        return 1;
    }

    if (cnt > 0) {
        strncpy(req->pattern, req->cmd, cnt + 1);
        req->pattern[cnt] = '\0';
    }

    return 0;
}

static int cli_parm_reg_value(cli_req_t *req)
{
    return cli_parm_u32(req, &req->value, 0, 0xffffffff);
}

static cli_parm_t cli_parm_table[] = {
    {
        "10hdx|10fdx|100hdx|100fdx|1000fdx|2500fdx|10gfdx|auto",
        "10hdx      : 10 Mbps, half duplex\n"
        "10fdx      : 10 Mbps, full duplex\n"
        "100hdx     : 100 Mbps, half duplex\n"
        "100fdx     : 100 Mbps, full duplex\n"
        "1000fdx    : 1 Gbps, full duplex\n"
        "2500fdx    : 2.5 Gbps, full duplex\n"
        "10gfdx     : 10 Gbps, full duplex\n"
        "auto       : Auto negotiation of speed and duplex\n"
        "(default: Show configured and current mode)",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "clear|packets|bytes|errors|discards",
        "clear      : Clear port statistics\n"
        "packets    : Show packet statistics\n"
        "bytes      : Show byte statistics\n"
        "errors     : Show error statistics\n"
        "discards   : Show discard statistics\n"
        "(default: Show all port statistics)",
        CLI_PARM_FLAG_NO_TXT,
        cli_parm_keyword
    },
    {
        "enable|disable|rx|tx",
        "enable     : Enable forwarding in both directions\n"
        "disable    : Disable forwarding\n"
        "rx         : Enable Rx forwarding\n"
        "tx         : Enable Tx forwarding\n"
        "(default: Show forwarding mode)",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "near-end|far-end|facility|equipment",
        "near-end   : Loopback from Tx to Rx in PHY\n"
        "far-end    : Loopback from Rx to Tx in PHY\n"
        "equipment  : Loopback from Tx to Rx in SerDes\n"
        "facility   : Loopback from Rx to Tx in SerDes\n"
        "(default: Show loopback mode)",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "<max_frame>",
        "Port maximum frame size, default: Show maximum frame size",
        CLI_PARM_FLAG_NONE | CLI_PARM_FLAG_SET,
        cli_parm_max_frame
    },
    {
        "<age_time>",
        "MAC address age time (10-1000000), default: Show age time",
        CLI_PARM_FLAG_SET,
        cli_parm_age_time
    },
    {
        "unaware|c-port|s-port",
        "VLAN port type, default: Show type",
        CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "all|none|pvid",
        "VLAN egress tagging, default: Show mode",
        CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "all|tagged|untagged",
        "VLAN accepted frames, default: Show mode",
        CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "<addr_list>",
        "Register address list (0-31)",
        CLI_PARM_FLAG_NONE,
        cli_parm_addr_list
    },
    {
        "<page>",
        "Register page (0-0xffff), default: page 0",
        CLI_PARM_FLAG_NONE,
        cli_parm_page
    },
    {
        "<miim_addr>",
        "MII management address (0-31)",
        CLI_PARM_FLAG_NONE,
        cli_parm_miim_addr
    },
    {
        "<word128>",
        "Register pattern on the form 'target[t]:reggrp[g]:reg[r]', where\n\
        'target' is the name of the target (e.g. dev).\n\
        'reggrp' is the name of the register group.\n\
        'reg'    is the name of the register.\n\
        t        is a list of target replications if applicable.\n\
        g        is a list of register group replications if applicable.\n\
        r        is a list of register replications if applicable.\n\
        If a given replication (t, g, r) is omitted, all applicable replications will be accessed.\n\
        Both 'target', 'reggrp' and 'reg' may be omitted, which corresponds to wildcarding that part\n\
        of the name. Matches are exact, but wildcards ('*', '?') are allowed.",
        CLI_PARM_FLAG_NONE,
        cli_parm_reg_pattern
    },
    {
        "<value32>",
        "Value to be written to register (0-0xffffffff)",
        CLI_PARM_FLAG_SET,
        cli_parm_reg_value
    },
};

void vtss_appl_cli_l2_init(void)
{
    int i;
    
    /* Initialize symbolic register access */
    symreg_init();

    /* Register commands */
    for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
        vtss_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }

    /* Register parameters */
    for (i = 0; i < sizeof(cli_parm_table)/sizeof(cli_parm_t); i++) {
        vtss_appl_cli_parm_reg(&cli_parm_table[i]);
    }
}
#endif /* VTSS_FEATURE_LAYER2 */
