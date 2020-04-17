// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "mscc/ethernet/switch/api.h"

static struct {
    mesa_port_no_t        iport;
    mesa_port_no_t        eport;
    mesa_packet_rx_conf_t conf;
    uint32_t              rx_cnt;
    uint32_t              tx_port_cnt;
    uint32_t              tx_vlan_cnt;
} state;

static int packet_init(int argc, const char *argv[])
{
    mesa_port_no_t        iport = ARGV_INT("iport", "Ingress port");
    mesa_port_no_t        eport = ARGV_INT("eport", "Egress port");
    mesa_packet_rx_conf_t conf;

    EXAMPLE_BARRIER(argc);

    // Store state
    memset(&state, 0, sizeof(state));
    state.iport = iport;
    state.eport = eport;

    // Redirect IGMP frames to CPU queue 7
    RC(mesa_packet_rx_conf_get(NULL, &conf));
    state.conf = conf;
    conf.reg.igmp_cpu_only = 1;
    conf.map.igmp_queue = 7;
    RC(mesa_packet_rx_conf_set(NULL, &conf));
    
    return 0;
}

static void packet_stat(const char *name, uint32_t cnt)
{
    char buf[80];

    sprintf(buf, "%s:", name);
    cli_printf("%-19s%10lu\n", buf, cnt);
}

static int packet_run(int argc, const char *argv[])
{
    EXAMPLE_BARRIER(argc);

    packet_stat("Rx Packets", state.rx_cnt);
    packet_stat("Tx Port Packets", state.tx_port_cnt);
    packet_stat("Tx VLAN Packets", state.tx_vlan_cnt);

    return 0;
}

static int packet_uninit(void)
{
    RC(mesa_packet_rx_conf_set(NULL, &state.conf));
    return 0;
}

static int packet_poll(int fast)
{
    uint8_t               frame[1600], *f = &frame[4]; // Make room for inserting tag
    mesa_packet_rx_info_t rx_info;
    mesa_packet_tx_info_t tx_info;

    // Extract frame
    if (fast == 0 ||
        mesa_packet_rx_frame(NULL, f, sizeof(frame) - 4, &rx_info) != MESA_RC_OK ||
        (rx_info.xtr_qu_mask & (1 << 7)) == 0) {
        return 0;
    }
    state.rx_cnt++;

    RC(mesa_packet_tx_info_init(NULL, &tx_info));
    if (rx_info.port_no == state.iport) {
        // Received on ingress port, forward to egress port
        tx_info.dst_port_mask = 1;
        tx_info.dst_port_mask <<= state.eport;
        tx_info.dst_port = state.eport;
        state.tx_port_cnt++;
    } else {
        // Received on another port, forward on VLAN 1 by inserting C-tag
        tx_info.switch_frm = 1;
        f = &frame[0];
        memmove(f, f + 4, 12); 
        f[12] = 0x81;
        f[13] = 0x00;
        f[14] = 0x00;
        f[15] = 0x01;
        rx_info.length += 4;
        state.tx_vlan_cnt++;
    }
    RC(mesa_packet_tx_frame(NULL, &tx_info, f, rx_info.length));
    
    return 0;
}

static const char *packet_help(void)
{
    return "Packet extraction/injection example";
}

EXAMPLE_EXT(packet, packet_init, packet_run, packet_uninit, packet_poll, packet_help);
