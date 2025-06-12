// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include <arpa/inet.h>
#include "microchip/ethernet/switch/api.h"
extern meba_inst_t meba_global_inst;

static uint8_t                src_mac[6] = {0,0,0,0,5,7};
static uint8_t                dst_mac[6] = {7,8,9,10,0,1};

static const char *phy_help_txt = "\
This is Timestamping PHY test.\n\
\n\
The SYNC frame is transmitted on a loop port and copied to CPU at reception.\n\
The log information is calculated based on received frame content.\n\
";

static struct {
    uint32_t                 family;
    mesa_port_no_t           tx_port;
    mesa_port_no_t           rx_port;
} state;

#define NO_EXP 0xFFFFFFFF
#define PTP_SYNC_MESSAGE_LENGTH = 44
#define TX_RX_FRAME_CNT 10
#define ETH_PTP_ETYPE 0x88f7


/* TS initialization ingress/egress configuration */
static int phy_ts_init(const mepa_port_no_t port_no, const mepa_ts_pkt_encap_t encap) {
    meba_phy_ts_init_conf_set(meba_global_inst, port_no, NULL);
    mepa_ts_classifier_t cs_conf;
    cs_conf.enable = 1,
    cs_conf.pkt_encap_type = encap;
    cs_conf.clock_id = 0;
    cs_conf.eth_class_conf.mac_match_mode = MEPA_TS_ETH_ADDR_MATCH_48BIT;
    cs_conf.eth_class_conf.mac_match_select = MEPA_TS_ETH_MATCH_DEST_ADDR;
    memcpy(&cs_conf.eth_class_conf.mac_addr, dst_mac, sizeof(dst_mac));
    cs_conf.eth_class_conf.vlan_check = 0;

    if (encap == MEPA_TS_ENCAP_ETH_IP_PTP) {
        cs_conf.ip_class_conf.ip_ver = MEPA_TS_IP_VER_4;
        cs_conf.ip_class_conf.ip_match_mode = MEPA_TS_IP_MATCH_SRC;  /**<  match src, dest or either IP address */
        cs_conf.ip_class_conf.udp_sport_en = FALSE;   /**<  UDP Source port check enable */
        cs_conf.ip_class_conf.udp_dport_en = FALSE;   /**<  UDP Dest port check enable */
        cs_conf.ip_class_conf.udp_dport = 319;
    }
    cs_conf.eth_class_conf.vlan_conf.etype = (encap == MEPA_TS_ENCAP_ETH_IP_PTP) ? 0x0800: 0x88f7;
    meba_phy_ts_tx_classifier_conf_set(meba_global_inst, port_no, 0, &cs_conf);
    mepa_ts_ptp_clock_conf_t ptp_conf;
    memset(&ptp_conf, 0, sizeof(ptp_conf));
    ptp_conf.enable = 1;
    ptp_conf.clk_mode = MEPA_TS_PTP_CLOCK_MODE_BC1STEP;
    ptp_conf.delaym_type = MEPA_TS_PTP_DELAYM_E2E;
    meba_phy_ts_tx_clock_conf_set(meba_global_inst, port_no, 0, &ptp_conf);
    return 0;
}

static int phy_init(int argc, const char *argv[])
{
    uint32_t tx_port = ARGV_INT("tx-port", "The SYNC TX port");
    uint32_t rx_port = ARGV_INT("rx-port", "The SYNC RX port");
    mesa_mac_table_entry_t entry;
    uint8_t                frame[1600];
    mesa_packet_rx_info_t  rx_info;

    EXAMPLE_BARRIER(argc);

    memset(&state, 0, sizeof(state));
    state.tx_port = tx_port - 1;
    state.rx_port = rx_port - 1;
    state.family = mesa_capability(NULL, MESA_CAP_MISC_CHIP_FAMILY);

    // Must be called to enable rx packet polling
    (void)mesa_packet_rx_frame(NULL, frame, sizeof(frame), &rx_info);

    // Create MAC address entry to copy frame to CPU
    entry.vid_mac.vid = 1;
    memcpy(entry.vid_mac.mac.addr, dst_mac, sizeof(entry.vid_mac.mac.addr));
    mesa_port_list_clear(&entry.destination);
    entry.copy_to_cpu = TRUE;
    entry.copy_to_cpu_smac = FALSE;
    entry.locked = TRUE;
    entry.index_table = FALSE;
    entry.aged = FALSE;
    entry.cpu_queue = 7;
    RC(mesa_mac_table_add(NULL, &entry));
    phy_ts_init(state.tx_port, MEPA_TS_ENCAP_ETH_PTP);
    return 0;
}

static int phy_clean()
{
    mesa_vid_mac_t vid_mac;

    vid_mac.vid = 1;
    memcpy(vid_mac.mac.addr, dst_mac, sizeof(vid_mac.mac.addr));
    RC(mesa_mac_table_del(NULL, &vid_mac));

    return 0;
}

static char ret_string[500];
static const char* phy_help()
{
    (void)sprintf(ret_string, "%s", phy_help_txt);
    return ret_string;
}

static int phy_run(int argc, const char *argv[])
{
    uint32_t command = ARGV_RUN_INT("command", "The command to run.\n\
        value 0 status show.\n\
        value 1 is CPU RX SYNC frame print.\n\
        value 2 is CPU TX SYNC frame.\n");
    mesa_packet_tx_info_t   tx_info;
    mesa_packet_rx_info_t   rx_info;
    uint32_t                ether_type, idx, rcode, delay=0, reserved;
    uint8_t                 frame[1600], *et_ptr;
    mepa_timestamp_t ts;
    uint8_t ptp_pload[] = {0x0, 0x2, 0x0,0x2c, 0x0, 0x0, 0x0, 0xc8};
    EXAMPLE_BARRIER(argc);

    switch (command) {
    case 0:
        /* Print out some status info */
        cli_printf("Status:\n");
        cli_printf("    Delay:     %u\n", delay);
        break;

    case 1:
    for(int i = 0; i< TX_RX_FRAME_CNT; i++) {
        if ((rcode = mesa_packet_rx_frame(NULL, frame, sizeof(frame), &rx_info)) != MESA_RC_OK) {
            cli_printf("mesa_packet_rx_frame() failed  rc %X  Incomplete %u\n", rcode, (rcode == MESA_RC_INCOMPLETE));
            return -1;
        }

        if ((frame[12] == 0x81) && (frame[13] == 0x00)) {
            et_ptr = &frame[12 + 4];
        } else {
            et_ptr = &frame[12];
        }
        ether_type = (et_ptr[0] << 8) + et_ptr[1];
        ts.seconds.high = (frame[48] << 8) + frame[49];
        ts.seconds.low = (frame[50] << 24) | (frame[51] << 16) | (frame[52] << 8) | frame[53];
        //ts.nanoseconds =  (frame[54] << 24) | (frame[55] << 16) | (frame[56] << 8) | frame[57];
        //reserved = (frame[30] << 24) | (frame[31] << 16) | (frame[32] << 8) | frame[33];
        memcpy(&reserved , &frame[30], sizeof(uint32_t));
        memcpy(&ts.nanoseconds , &frame[54], sizeof(uint32_t));
        if(ether_type == ETH_PTP_ETYPE) {
            cli_printf("Frame received:\n");
            cli_printf("    Port:   %u:\n", rx_info.port_no + 1);
            cli_printf("    Length: %u:\n", rx_info.length);
            cli_printf("    Tag type: %s:\n", (rx_info.tag_type == MESA_TAG_TYPE_UNTAGGED) ? "Un-tagged" : (rx_info.tag_type == MESA_TAG_TYPE_C_TAGGED) ? "C-tagged" : (rx_info.tag_type == MESA_TAG_TYPE_S_TAGGED) ? "S-tagged" : "Unknown");
            cli_printf("    Ether type: %X:\n", ether_type);
            cli_printf("    Sec: %d\n", ts.seconds.high << 16 | ts.seconds.low);
            cli_printf("    Nsec: %x\n", ntohl(ts.nanoseconds));
            cli_printf("    Reserved: %x\n", ntohl(reserved));
            cli_printf("    Time Error : %d\n", (uint32_t)(ntohl(ts.nanoseconds) - ntohl(reserved)));
        }
    }
        break;

    case 2:
        RC(mesa_packet_tx_info_init(NULL, &tx_info));
        if (state.family == MESA_CHIP_FAMILY_SPARX5) {
            tx_info.dst_port = state.tx_port;
        } else {
            tx_info.dst_port_mask = 0x01 << state.tx_port;
        }
        tx_info.switch_frm = FALSE;
        tx_info.masquerade_port = MESA_PORT_NO_NONE;

        // Initialize the TX frame
        memset(frame, 0, sizeof(frame));
        idx = 0;
        memcpy(frame+idx, dst_mac, sizeof(dst_mac));
        idx += 6;
        memcpy(frame+idx, src_mac, sizeof(src_mac));
        idx += 6;
        *(frame+idx+0) = 0x88;
        *(frame+idx+1) = 0xF7;
        idx += 2;
        memcpy(frame+idx, ptp_pload, sizeof(ptp_pload));
//        *(frame+idx+0) =
//        *(frame+idx+1) =
        idx += 64;

        // Transmit the frame
        for(int i=0; i<TX_RX_FRAME_CNT; i++)
            RC(mesa_packet_tx_frame(NULL, &tx_info, frame, idx));
        break;

    default:
        cli_printf("Unknown command\n");
        break;
    }

    return 0;
}

EXAMPLE(ts_phy, phy_init, phy_run, phy_clean, phy_help);
