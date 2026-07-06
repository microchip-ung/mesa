// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <ctype.h>
#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"
#include "port.h"
#include "phy_demo_apps.h"
#include "mepa_driver.h"
#include "lan80xx.h"

#define LAN80XX_MAX_VREF_EYE 127

meba_inst_t meba_phy_diag_instance;

static mscc_appl_trace_module_t trace_module = {.name = "m25g_diag"};
static mscc_appl_trace_group_t  trace_groups[10] = {
    // TRACE_GROUP_DEFAULT
    {.name = "default", .level = MESA_TRACE_LEVEL_ERROR},
};

char *speed_neg[] = {"None", "1G", "10G", "25G"};

/* Keywords in Command Parsed or Not */
typedef struct {
    mepa_bool_t vga_parsed;
    mepa_bool_t ctle_c_parsed;
    mepa_bool_t ctle_r_parsed;
    mepa_bool_t amp_parsed;
    mepa_bool_t tap_dly_parsed;
    mepa_bool_t tap_adv_parsed;
    mepa_bool_t prbs_gen_parsed;
    mepa_bool_t prbs_mon_parsed;
} phy_diag_keyword_t;

phy_diag_keyword_t keyword_parsed;

typedef struct {
    phy25g_rx_eye_scan_t scan;
    mepa_bool_t          is_line;
    mepa_bool_t          dfe_manual;
    mepa_bool_t          dfe_adpative;
    u8                   rx_vga;
    u8                   rx_ctle_c;
    u8                   rx_ctle_r;
    u8                   amp_code;
    u8                   tx_tap_dly;
    u8                   tx_tap_adv;
    u32                  mmd;
    u32                  addr;
    u32                  value;
    mepa_prbs_pattern_t  prbs_pattern;
    u8                   prbs_user_pattern[8];
    mepa_bool_t          prbs_pcs_mon_ena;
    mepa_bool_t          prbs_gen_ena;
    u16                  ethtype;
    u32                  src_mac[6];
    u32                  dst_mac[6];
    mepa_bool_t          pkt_ptp;
    mepa_bool_t          pkt_ingr;
    mepa_bool_t          pkt_frame_single;
    mepa_bool_t          user_pattern_parsed;
    mepa_bool_t          mon_reset_enable;
} phy25g_appl_diag_t;

static void cli_cmd_pkt_mon(cli_req_t *req)
{
    mepa_rc rc;

    mepa_bool_t               pkt_mon_enable;
    phy25g_pkt_mon_rst_t      pkt_mon_reset;
    phy25g_pkt_mon_counters_t mon_counters;
    phy25g_timestamp_val_t    ts_read;
    phy25g_appl_diag_t       *mreq = req->module_req;

    if (!req->set) {
        cli_printf("\n Syntax : mepa-cmd pkt_mon <port_no> reset [enable|disable]\n");
        T_E("\n Invalid Argument \n");
        return;
    }
    if ((rc = lan80xx_pkt_mon_get(meba_phy_diag_instance->phy_devices[req->port_no], req->port_no,
                                  &pkt_mon_enable, &pkt_mon_reset)) != MEPA_RC_OK) {
        T_E("\n Error in Configuring Packet BIST Monitor on port : %d \n", (req->port_no + 1));
        return;
    }

    if ((rc = lan80xx_pkt_mon_counters_get(meba_phy_diag_instance->phy_devices[req->port_no],
                                           req->port_no, FALSE, &mon_counters, &ts_read)) !=
        MEPA_RC_OK) {
        T_E("\n Error in Getting PKT BIST Counters on port : %d \n", (req->port_no + 1));
        return;
    }
    cli_printf("\n");
    cli_printf("\n Port %d\n", (req->port_no + 1));
    cli_printf("=================\n");
    cli_printf("\n Good CRC      : %ld", mon_counters.good_crc);
    cli_printf("\n Bad  CRC      : %ld", mon_counters.bad_crc);
    cli_printf("\n Fragmented    : %ld", mon_counters.fragmented);
    cli_printf("\n Local Fault   : %ld", mon_counters.lfault);
    cli_printf("\n BER           : %ld", mon_counters.ber);
    cli_printf("\n");

    if (!mreq->mon_reset_enable) {
        return;
    }

    if ((rc = lan80xx_pkt_mon_conf(meba_phy_diag_instance->phy_devices[req->port_no], req->port_no,
                                   pkt_mon_enable, LAN80XX_PKT_MON_RST_ALL)) != MEPA_RC_OK) {
        T_E("\n Error in Configuring PKT BIST Monitor Reset on port  : %d \n", (req->port_no + 1));
        return;
    }
    return;
}

static void cli_cmd_pkt_bist(cli_req_t *req)
{

    mepa_rc               rc;
    phy25g_appl_diag_t   *mreq = req->module_req;
    phy25g_pkt_gen_conf_t pkt_conf;
    mepa_bool_t           pkt_mon_enable;
    phy25g_pkt_mon_rst_t  pkt_mon_reset;

    if (!keyword_parsed.prbs_mon_parsed) {
        cli_printf(
            "\n Syntax : mepa-cmd pkt_bist <port_no> [eth|ptp] [egr|ingr] [conti|single] <ethtype> <src_mac> <dst_mac> [gen_enable|gen_disable] [mon_enable|mon_disable]\n");
        T_E("\n Invalid Argument \n");
        return;
    }
    keyword_parsed.prbs_mon_parsed = 0;
    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    memset(&pkt_conf, 0, sizeof(phy25g_pkt_gen_conf_t));

    pkt_conf.enable = mreq->prbs_gen_ena;
    pkt_conf.ptp = mreq->pkt_ptp;
    pkt_conf.ingress = mreq->pkt_ingr;
    pkt_conf.frames = 1;
    pkt_conf.pkt_len = 2;
    pkt_conf.frame_single = mreq->pkt_frame_single;
    pkt_conf.etype = mreq->ethtype;

    for (u8 i = 0; i < 6; i++) {
        pkt_conf.smac.addr[i] = mreq->src_mac[i];
        pkt_conf.dmac.addr[i] = mreq->dst_mac[i];
    }

    if ((rc = lan80xx_pkt_mon_get(meba_phy_diag_instance->phy_devices[req->port_no], req->port_no,
                                  &pkt_mon_enable, &pkt_mon_reset)) != MEPA_RC_OK) {
        T_E("\n Error in Getting Pkt Bist Monitor on port : %d \n", (req->port_no + 1));
        return;
    }
    if (pkt_mon_enable != mreq->prbs_pcs_mon_ena) {
        if ((rc = lan80xx_pkt_mon_conf(meba_phy_diag_instance->phy_devices[req->port_no],
                                       req->port_no, mreq->prbs_pcs_mon_ena,
                                       LAN80XX_PKT_MON_RST_NONE)) != MEPA_RC_OK) {
            T_E("\n Error in Configuring Packet Monitor on port : %d \n", (req->port_no + 1));
            return;
        }
    }

    if ((rc = lan80xx_pkt_gen_conf(meba_phy_diag_instance->phy_devices[req->port_no], req->port_no,
                                   &pkt_conf)) != MEPA_RC_OK) {
        T_E("\n Error in Configuring Packet Generator on port : %d \n", (req->port_no + 1));
        return;
    }

    return;
}

static void phy_prbs_conf_get(cli_req_t *req, mepa_phy_prbs_generator_conf_t prbs_get)
{
    char *prbs_pattern_txt[] = {"PRBS 7",  "PRBS 9",  "PRBS 11",       "PRBS 15",
                                "PRBS 23", "PRBS 31", "Clock Pattern", "User defined"};
    cli_printf("PRBS Pattern         : %s \n", prbs_pattern_txt[prbs_get.prbsn_sel]);
    if (prbs_get.prbsn_sel == MEPA_USER_DEFINED_PATTERN) {
        cli_printf("User Define Pattern  : ");
        for (u8 i = 0; i < 7; i++) {
            cli_printf("%d, ", prbs_get.user_pattern[i]);
        }
        cli_printf("%d ", prbs_get.user_pattern[7]);
    }
    return;
}

static void cli_cmd_prbs_status(cli_req_t *req)
{
    mepa_rc                        rc;
    mepa_phy_prbs_direction_t      direction;
    mepa_phy_prbs_generator_conf_t prbs_get;
    mepa_phy_prbs_monitor_conf_t   mon_get;
    phy25g_appl_diag_t            *mreq = req->module_req;
    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    direction = mreq->is_line ? MEPA_PHY_DIRECTION_LINE : MEPA_PHY_DIRECTION_HOST;

    if ((rc = mepa_prbs_get(meba_phy_diag_instance->phy_devices[req->port_no],
                            MEPA_PHY_PRBS_TYPE_SERDES, direction, &prbs_get)) != MEPA_RC_OK) {
        T_E("\n Error in Configuring PRBS Genrator on port : %d \n", (req->port_no + 1));
        return;
    }
    mon_get.prbs_type = MEPA_PHY_PRBS_TYPE_SERDES;
    mon_get.prbs_direction = direction;
    if ((rc = mepa_prbs_monitor_get(meba_phy_diag_instance->phy_devices[req->port_no], &mon_get)) !=
        MEPA_RC_OK) {
        T_E("\n Error in Configuring PRBS Genrator on port : %d \n", (req->port_no + 1));
        return;
    }
    cli_printf("\n");
    cli_printf("\n\n Port %d, %s\n", (req->port_no + 1), direction ? "LINE" : "HOST");
    cli_printf("=================\n");
    cli_printf("\n");
    cli_printf("PRBS Generator       : %s \n", prbs_get.enable ? "Enabled" : "Disabled");
    cli_printf("PRBS Monitor         : %s \n", mon_get.enable ? "Enabled" : "Disabled");
    cli_printf("PRBS Type            : %s \n", "Serdes");

    if (prbs_get.enable) {
        phy_prbs_conf_get(req, prbs_get);
    }
    cli_printf("\n\n");
    if (mon_get.enable) {
        cli_printf("BIST Active          : %s\n", mon_get.active ? "Yes" : "No");
        cli_printf("BIST Status          : %s\n", mon_get.bist_status ? "BIST Ok" : "BIST Fail");
        cli_printf("BIST Error           : %s\n", mon_get.error_status ? "Yes" : "No");
        cli_printf("BIST Incomplete      : %s\n", mon_get.error_status ? "Yes" : "No");
        cli_printf("BIST Error Count     : %ld\n", mon_get.bist_error_count);
    }
    return;
}

static void cli_cmd_prbs_set(cli_req_t *req)
{
    mepa_rc                        rc;
    phy25g_appl_diag_t            *mreq = req->module_req;
    mepa_phy_prbs_direction_t      direction;
    mepa_phy_prbs_generator_conf_t prbs_conf;
    mepa_phy_prbs_monitor_conf_t   prbs_mon;

    memset(&prbs_conf, 0, sizeof(mepa_phy_prbs_generator_conf_t));
    memset(&prbs_mon, 0, sizeof(mepa_phy_prbs_monitor_conf_t));

    if (mreq->prbs_pattern == MEPA_USER_DEFINED_PATTERN) {
        if (mreq->user_pattern_parsed == 0) {
            cli_printf("\n User Pattern is not provide \n");
            return;
        }
    }

    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    direction = mreq->is_line ? MEPA_PHY_DIRECTION_LINE : MEPA_PHY_DIRECTION_HOST;
    prbs_conf.enable = mreq->prbs_gen_ena;
    prbs_mon.enable = mreq->prbs_pcs_mon_ena;
    prbs_conf.prbsn_sel = mreq->prbs_pattern;
    prbs_mon.prbsn_sel = mreq->prbs_pattern;
    memcpy(&prbs_conf.user_pattern, &mreq->prbs_user_pattern, sizeof(prbs_conf.user_pattern));
    if ((rc = mepa_prbs_set(meba_phy_diag_instance->phy_devices[req->port_no],
                            MEPA_PHY_PRBS_TYPE_SERDES, direction, &prbs_conf)) != MEPA_RC_OK) {
        T_E("\n Error in Configuring PRBS Genrator on port : %d \n", (req->port_no + 1));
        return;
    }
    prbs_mon.prbs_type = MEPA_PHY_PRBS_TYPE_SERDES;
    prbs_mon.prbs_direction = direction;
    if ((rc = mepa_prbs_monitor_set(meba_phy_diag_instance->phy_devices[req->port_no],
                                    &prbs_mon)) != MEPA_RC_OK) {
        T_E("\n Error in Configuring PRBS Monitor on port : %d \n", (req->port_no + 1));
        return;
    }
    return;
}

static void cli_cmd_phy_state(cli_req_t *req)
{
    mepa_rc         rc;
    mepa_conf_t     conf_get;
    phy25g_status_t status;
    u8              fec_state = 0;
    char           *mode_txt[] = {"PCS Retimer", "MAC Retimer"};
    char           *fec[] = {"None", "R-FEC", "RS-FEC", "R-FEC, RS-FEC"};
    char           *fec_enabled_port[] = {"None", "HOST", "LINE", "HOST-LINE"};
    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    if ((rc = mepa_conf_get(meba_phy_diag_instance->phy_devices[req->port_no], &conf_get)) !=
        MEPA_RC_OK) {
        T_E("\n Error Getting Conf_get on port : %d \n", (req->port_no + 1));
        return;
    }
    if (conf_get.conf_25g.base_r_10gfec || conf_get.conf_25g.base_r_25gfec) {
        fec_state += 1;
    }
    if (conf_get.conf_25g.rs_fec_25g) {
        fec_state += 2;
    }
    if ((rc = lan80xx_status_get(meba_phy_diag_instance->phy_devices[req->port_no], req->port_no,
                                 &status)) != MEPA_RC_OK) {
        T_E("\n Error in getting PHY Statusr on port : %d \n", (req->port_no + 1));
        return;
    }
    cli_printf("\n");
    cli_printf("\nPort : %d", (req->port_no + 1));
    cli_printf("\n==============\n");
    cli_printf("\n");
    switch (conf_get.speed) {
    case MESA_SPEED_1G:
        cli_printf("Port Speed              : 1G\n\n");
        cli_printf("Line PCS 1G Link        : %s\n", status.line_pcs1g.link_status ? "Up" : "Down");
        cli_printf("Host PCS 1G Link        : %s\n\n",
                   status.host_pcs1g.link_status ? "Up" : "Down");
        cli_printf("Line PCS 1G Sync        : %s\n", status.line_pcs1g.sync_status ? "Yes" : "No");
        cli_printf("Host PCS 1G Sync        : %s\n\n",
                   status.host_pcs1g.sync_status ? "Yes" : "No");
        break;
    case MESA_SPEED_10G:
    case MESA_SPEED_25G:
        cli_printf("Port Speed              : %s\n\n",
                   (conf_get.speed == MESA_SPEED_10G) ? "10G" : "25G");
        cli_printf("Line PCS25G Rx Link     : %s\n", status.line_pcs25g.rx_link ? "Up" : "Down");
        cli_printf("Line PCS25G Hi-BER      : %s\n", status.line_pcs25g.hi_ber ? "Yes" : "No");
        cli_printf("Line PCS25G Rx Fault    : %s\n", status.line_pcs25g.rx_fault ? "Yes" : "No");
        cli_printf("Line PCS25G Tx Fault    : %s\n\n", status.line_pcs25g.tx_fault ? "Yes" : "No");
        cli_printf("Host PCS25G Rx Link     : %s\n", status.host_pcs25g.rx_link ? "Up" : "Down");
        cli_printf("Host PCS25G Hi-BER      : %s\n", status.host_pcs25g.hi_ber ? "Yes" : "No");
        cli_printf("Host PCS25G Rx Fault    : %s\n", status.host_pcs25g.rx_fault ? "Yes" : "No");
        cli_printf("Host PCS25G Tx Fault    : %s\n\n", status.host_pcs25g.tx_fault ? "Yes" : "No");
        break;
    case MESA_SPEED_AUTO:
        cli_printf("Advertised Speeds       : %s %s %s\n\n",
                   (conf_get.aneg.speed_1g_fdx ? "1G " : ""),
                   (conf_get.aneg.speed_10g_fdx ? "10G " : ""),
                   ((conf_get.aneg.speed_25g_fdx || conf_get.aneg.speed_25g_kr_s_fdx) ? "25G "
                                                                                      : ""));

        cli_printf("HOST Negotiated Speed   : %s \n", speed_neg[status.host_neg_speed]);
        cli_printf("LINE Negotiated Speed   : %s \n\n", speed_neg[status.line_neg_speed]);

        cli_printf("Line PCS 1G Link        : %s\n", status.line_pcs1g.link_status ? "Up" : "Down");
        cli_printf("Host PCS 1G Link        : %s\n\n",
                   status.host_pcs1g.link_status ? "Up" : "Down");
        cli_printf("Line PCS 1G Sync        : %s\n", status.line_pcs1g.sync_status ? "Yes" : "No");
        cli_printf("Host PCS 1G Sync        : %s\n\n",
                   status.host_pcs1g.sync_status ? "Yes" : "No");
        cli_printf("Line PCS25G Rx Link     : %s\n", status.line_pcs25g.rx_link ? "Up" : "Down");
        cli_printf("Line PCS25G Hi-BER      : %s\n", status.line_pcs25g.hi_ber ? "Yes" : "No");
        cli_printf("Line PCS25G Rx Fault    : %s\n", status.line_pcs25g.rx_fault ? "Yes" : "No");
        cli_printf("Line PCS25G Tx Fault    : %s\n\n", status.line_pcs25g.tx_fault ? "Yes" : "No");
        cli_printf("Host PCS25G Rx Link     : %s\n", status.host_pcs25g.rx_link ? "Up" : "Down");
        cli_printf("Host PCS25G Hi-BER      : %s\n", status.host_pcs25g.hi_ber ? "Yes" : "No");
        cli_printf("Host PCS25G Rx Fault    : %s\n", status.host_pcs25g.rx_fault ? "Yes" : "No");
        cli_printf("Host PCS25G Tx Fault    : %s\n\n", status.host_pcs25g.tx_fault ? "Yes" : "No");
        break;
    default: cli_printf("\n Port not Configured \n"); return;
    }
    cli_printf("PMA Rx Link             : %s\n", status.pma.rx_link ? "Up" : "Down");
    cli_printf("PMA Rx Fault            : %s\n", status.pma.rx_fault ? "Yes" : "No");
    cli_printf("PMA Tx Fault            : %s\n\n", status.pma.tx_fault ? "Yes" : "No");
    cli_printf("Port Mode               : %s\n", mode_txt[status.oper_mode]);
    cli_printf("Flow Control            : %s\n", conf_get.flow_control ? "Enabled" : "Disabled");
    cli_printf("FEC Enabled             : %s\n", fec[fec_state]);
    if (fec_state != 0) {
        cli_printf("FEC Enabled Side        : %s\n", fec_enabled_port[conf_get.aneg.advertise_dir]);
    }

    return;
}

static void cli_cmd_csr_wr(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    mepa_rc             rc;
    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    if ((rc = lan80xx_phy_csr_write(meba_phy_diag_instance->phy_devices[req->port_no], req->port_no,
                                    mreq->mmd, mreq->addr, mreq->value)) != MEPA_RC_OK) {
        T_E("\n Error Writing a Register on port : %d \n", (req->port_no + 1));
        return;
    }
    return;
}

static void cli_cmd_csr_rd(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    mepa_rc             rc;
    uint32_t            value = 0;

    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    if ((rc = lan80xx_phy_csr_read(meba_phy_diag_instance->phy_devices[req->port_no], req->port_no,
                                   mreq->mmd, mreq->addr, &value)) != MEPA_RC_OK) {
        T_E("\n Error Reading a Register on port : %d \n", (req->port_no + 1));
        return;
    }
    cli_printf("\n");
    cli_table_header("Port  MMD   Address  31******24*23*******16*15*******8***7*******0    Value");
    cli_printf("%-6u%-6u0x%04x   ", (req->port_no + 1), mreq->mmd, mreq->addr);
    for (int i = 31; i >= 0; i--) {
        cli_printf("%d%s", value & (1 << i) ? 1 : 0, (i % 4) || i == 0 ? "" : ". ");
    }
    cli_printf("   0x%x\n", value);
    return;
}

static void cli_cmd_tx_eqa(cli_req_t *req)
{
    phy25g_appl_diag_t      *mreq = req->module_req;
    phy25g_tx_rx_equa_conf_t tx_conf = {};
    mepa_rc                  rc;
    if (!req->set) {
        cli_printf(
            "\n Syntax : mepa-cmd tx_eqa <port_no> [host|line] amp <equ_val> tap_dly <equ_val> tap_adv <equ_val>\n");
        T_E("\n Invalid Argument \n");
        return;
    }
    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    tx_conf.equalizer_conf = LAN80XX_CONF_TX_EQUALIZER;
    tx_conf.amp_code = mreq->amp_code;
    tx_conf.tx_tap_dly = mreq->tx_tap_dly;
    tx_conf.tx_tap_adv = mreq->tx_tap_adv;

    if ((rc = lan80xx_phy_tx_rx_equalization_set(meba_phy_diag_instance->phy_devices[req->port_no],
                                                 req->port_no, mreq->is_line, &tx_conf)) !=
        MEPA_RC_OK) {
        T_E("\n Error in Configuring Rx Eualizer on port : %d \n", (req->port_no + 1));
        return;
    }
    return;
}

static void cli_cmd_rx_eqa(cli_req_t *req)
{
    phy25g_appl_diag_t      *mreq = req->module_req;
    phy25g_tx_rx_equa_conf_t rx_conf = {};
    mepa_rc                  rc;
    if (!req->set) {
        cli_printf(
            "\n Syntax : mepa-cmd rx_eqa <port_no> [host|line] [dfe_adp|dfe_man|disable] ctle_r <equ_val> ctle_c <equ_val> vga <equ_val>\n");
        T_E("\n Invalid Argument \n");
        return;
    }
    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    rx_conf.equalizer_conf = LAN80XX_CONF_RX_EQUALIZER;
    rx_conf.rx_vga = mreq->rx_vga;
    rx_conf.rx_ctle_c = mreq->rx_ctle_c;
    rx_conf.rx_ctle_r = mreq->rx_ctle_r;
    rx_conf.dfe_adp_ena = mreq->dfe_adpative;
    rx_conf.dfe_man_ena = mreq->dfe_manual;

    if ((rc = lan80xx_phy_tx_rx_equalization_set(meba_phy_diag_instance->phy_devices[req->port_no],
                                                 req->port_no, mreq->is_line, &rx_conf)) !=
        MEPA_RC_OK) {
        T_E("\n Error in Configuring Rx Eualizer on port : %d \n", (req->port_no + 1));
        return;
    }
    return;
}

static void cli_cmd_eye_diag(cli_req_t *req)
{
    phy25g_appl_diag_t         *mreq = req->module_req;
    phy25g_rx_eye_scan_status_t status;
    phy25g_tx_rx_equ_status_t   eqaz_status;
    mepa_rc                     rc;
    if (!req->set) {
        cli_printf("\n Syntax : mepa-cmd eye_diag <port_no> [normal|fast] [host|line]\n");
        T_E("\n Invalid Argument \n");
        return;
    }
    if (meba_phy_diag_instance->phy_devices[req->port_no] == NULL) {
        cli_printf(" Dev is Not Created for the port : %d\n", req->port_no);
        return;
    }
    if ((rc = lan80xx_rx_eye_scan_conf_set(meba_phy_diag_instance->phy_devices[req->port_no],
                                           req->port_no, mreq->is_line, mreq->scan)) !=
        MEPA_RC_OK) {
        T_E("\n Error in Configuring Eye Diagram on port : %d \n", (req->port_no + 1));
        return;
    }
    if ((rc = lan80xx_rx_eye_scan_status_get(meba_phy_diag_instance->phy_devices[req->port_no],
                                             req->port_no, mreq->scan, &status)) != MEPA_RC_OK) {
        T_E("\n Error in Getting the Eye Height and Eye Diagram on port : %d \n",
            (req->port_no + 1));
        return;
    }
    if ((rc = lan80xx_phy_tx_rx_equalization_status_get(meba_phy_diag_instance
                                                            ->phy_devices[req->port_no],
                                                        req->port_no, mreq->is_line,
                                                        &eqaz_status)) != MEPA_RC_OK) {
        T_E("\n Error in Configuring Rx Eualizer on port : %d \n", (req->port_no + 1));
        return;
    }
    cli_printf("\n\n Port %d, %s\n", (req->port_no + 1), mreq->is_line ? "LINE" : "HOST");
    cli_printf("=================\n");
    cli_printf("\n\n Equalizers Coefficients");
    cli_printf("\n -------------------------------- \n");
    cli_printf("\n Tx Coefficients :");
    cli_printf("\n\t Tap Dly : %d ", eqaz_status.tx_tap_dly);
    cli_printf("\n\t Tap Adv : %d ", eqaz_status.tx_tap_adv);
    cli_printf("\n\t Amp Code: %d ", eqaz_status.amp_code);
    cli_printf("\n\n Rx Coefficients :");
    cli_printf("\n\t DFE     : %s ", eqaz_status.dfe_enable
                                         ? (eqaz_status.dfe_adaptive_mode ? "Adaptive" : "Manual")
                                         : "Disabled");
    cli_printf("\n\t VGA     : %d ", eqaz_status.vga_value);
    cli_printf("\n\t CTLE R  : %d ", eqaz_status.ctle_r_value);
    cli_printf("\n\t CTLE C  : %d \n", eqaz_status.ctle_c_value);

    if (mreq->scan == LAN80XX_RX_EYE_NORMAL_SCAN) {
        cli_printf("\n Scan Type : Normal Scan \n");
        cli_printf("\n Vref |");
        cli_printf("\n --------------------------------------------------------------------------");
        for (u16 i = 0; i <= LAN80XX_MAX_VREF_EYE; i += 8) {
            cli_printf("\n %03d  |", i);
            cli_printf(" %d", status.eye_res_msb[i]);
            cli_printf("%lb", status.eye_res[i]);
        }
        cli_printf("\n %03d  | %d%lb", LAN80XX_MAX_VREF_EYE,
                   status.eye_res_msb[LAN80XX_MAX_VREF_EYE], status.eye_res[LAN80XX_MAX_VREF_EYE]);

    } else if (mreq->scan == LAN80XX_RX_EYE_FAST_SCAN) {
        cli_printf("\n Scan Type : Fast Scan \n");
        cli_printf("\n Eye Height : %d \n", status.eye_height);
    }
    cli_printf("\n");
    return;
}

static int cli_param_parse_src_mac(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    memset(mreq->src_mac, 0, sizeof(mreq->src_mac));
    return cli_parse_mac_address(req, mreq->src_mac);
}

static int cli_param_parse_dst_mac(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    memset(mreq->dst_mac, 0, sizeof(mreq->dst_mac));
    return cli_parse_mac_address(req, mreq->dst_mac);
}

static int cli_cmd_parse_mmd_id(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    return cli_parm_hex_u32(req, &mreq->mmd, 0, MASK_32BIT);
}

static int cli_cmd_parse_reg_addr(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    return cli_parm_hex_u32(req, &mreq->addr, 0, MASK_32BIT);
}

static int cli_cmd_parse_reg_val(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    return cli_parm_hex_u32(req, &mreq->value, 0, MASK_32BIT);
}

static int cli_param_parse_ethtype(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    return cli_parm_u16(req, &mreq->ethtype, 0, MASK_16BIT);
}

static int cli_param_value(cli_req_t *req)
{
    uint8_t             value;
    phy25g_appl_diag_t *mreq = req->module_req;

    if (keyword_parsed.ctle_r_parsed) {
        cli_parm_u8(req, &value, 0, MASK_8BIT);
        mreq->rx_ctle_r = value;
        keyword_parsed.ctle_r_parsed = 0;
        req->set = 0;
    } else if (keyword_parsed.ctle_c_parsed) {
        cli_parm_u8(req, &value, 0, MASK_8BIT);
        mreq->rx_ctle_c = value;
        keyword_parsed.ctle_c_parsed = 0;
        req->set = 0;
    } else if (keyword_parsed.vga_parsed) {
        cli_parm_u8(req, &value, 0, MASK_8BIT);
        mreq->rx_vga = value;
        keyword_parsed.vga_parsed = 0;
    } else if (keyword_parsed.amp_parsed) {
        cli_parm_u8(req, &value, 0, MASK_8BIT);
        mreq->amp_code = value;
        keyword_parsed.amp_parsed = 0;
        req->set = 0;
    } else if (keyword_parsed.tap_dly_parsed) {
        cli_parm_u8(req, &value, 0, MASK_8BIT);
        mreq->tx_tap_dly = value;
        keyword_parsed.tap_dly_parsed = 0;
        req->set = 0;
    } else if (keyword_parsed.tap_adv_parsed) {
        cli_parm_u8(req, &value, 0, MASK_8BIT);
        mreq->tx_tap_adv = value;
        keyword_parsed.tap_adv_parsed = 0;
    } else {
        return 1;
    }
    return 0;
}

static int cli_param_keyword(cli_req_t *req)
{
    if (!strncasecmp(req->cmd, "ctle_r", strlen("ctle_r"))) {
        keyword_parsed.ctle_r_parsed = 1;
    } else if (!strncasecmp(req->cmd, "ctle_c", strlen("ctle_c"))) {
        keyword_parsed.ctle_c_parsed = 1;
    } else if (!strncasecmp(req->cmd, "vga", strlen("vga"))) {
        keyword_parsed.vga_parsed = 1;
    } else if (!strncasecmp(req->cmd, "amp", strlen("amp"))) {
        keyword_parsed.amp_parsed = 1;
    } else if (!strncasecmp(req->cmd, "tap_dly", strlen("tap_dly"))) {
        keyword_parsed.tap_dly_parsed = 1;
    } else if (!strncasecmp(req->cmd, "tap_adv", strlen("tap_adv"))) {
        keyword_parsed.tap_adv_parsed = 1;
    } else if (!strncasecmp(req->cmd, "gen", strlen("gen"))) {
        keyword_parsed.prbs_gen_parsed = 1;
    } else if (!strncasecmp(req->cmd, "mon", strlen("mon"))) {
        keyword_parsed.prbs_mon_parsed = 1;
    } else if (!strncasecmp(req->cmd, "reset", strlen("reset"))) {
        return 0;
    } else {
        return 1;
    }

    return 0;
}

static int cli_param_parse(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;

    if (!strncasecmp(req->cmd, "normal", strlen("normal"))) {
        mreq->scan = LAN80XX_RX_EYE_NORMAL_SCAN;
    } else if (!strncasecmp(req->cmd, "fast", strlen("fast"))) {
        mreq->scan = LAN80XX_RX_EYE_FAST_SCAN;
    } else if (!strncasecmp(req->cmd, "host", strlen("host"))) {
        mreq->is_line = 0;
    } else if (!strncasecmp(req->cmd, "line", strlen("line"))) {
        mreq->is_line = 1;
    } else if (!strncasecmp(req->cmd, "dfe_adp", strlen("dfe_adp"))) {
        mreq->dfe_adpative = 1;
    } else if (!strncasecmp(req->cmd, "dfe_man", strlen("dfe_man"))) {
        mreq->dfe_manual = 1;
    } else if (!strncasecmp(req->cmd, "disable", strlen("disable"))) {
        mreq->dfe_adpative = 0;
        mreq->dfe_manual = 0;
    } else if (!strncasecmp(req->cmd, "prbs7", strlen("prbs7"))) {
        mreq->prbs_pattern = MEPA_PRBS7;
    } else if (!strncasecmp(req->cmd, "prbs9", strlen("prbs9"))) {
        mreq->prbs_pattern = MEPA_PRBS9;
    } else if (!strncasecmp(req->cmd, "prbs11", strlen("prbs11"))) {
        mreq->prbs_pattern = MEPA_PRBS11;
    } else if (!strncasecmp(req->cmd, "prbs15", strlen("prbs15"))) {
        mreq->prbs_pattern = MEPA_PRBS15;
    } else if (!strncasecmp(req->cmd, "prbs23", strlen("prbs23"))) {
        mreq->prbs_pattern = MEPA_PRBS23;
    } else if (!strncasecmp(req->cmd, "prbs31", strlen("prbs31"))) {
        mreq->prbs_pattern = MEPA_PRBS31;
    } else if (!strncasecmp(req->cmd, "user_ptn", strlen("user_ptn"))) {
        mreq->prbs_pattern = MEPA_USER_DEFINED_PATTERN;
    } else if (!strncasecmp(req->cmd, "mon_enable", strlen("mon_enable"))) {
        keyword_parsed.prbs_mon_parsed = TRUE;
        mreq->prbs_pcs_mon_ena = TRUE;
    } else if (!strncasecmp(req->cmd, "mon_disable", strlen("mon_disable"))) {
        keyword_parsed.prbs_mon_parsed = TRUE;
        mreq->prbs_pcs_mon_ena = FALSE;
    } else if (!strncasecmp(req->cmd, "gen_enable", strlen("gen_enable"))) {
        mreq->prbs_gen_ena = TRUE;
    } else if (!strncasecmp(req->cmd, "gen_disable", strlen("gen_disable"))) {
        mreq->prbs_gen_ena = FALSE;
    } else if (!strncasecmp(req->cmd, "eth", strlen("eth"))) {
        mreq->pkt_ptp = 0;
    } else if (!strncasecmp(req->cmd, "ptp", strlen("ptp"))) {
        mreq->pkt_ptp = 1;
    } else if (!strncasecmp(req->cmd, "egr", strlen("egr"))) {
        mreq->pkt_ingr = 0;
    } else if (!strncasecmp(req->cmd, "ingr", strlen("ingr"))) {
        mreq->pkt_ingr = 1;
    } else if (!strncasecmp(req->cmd, "conti", strlen("conti"))) {
        mreq->pkt_frame_single = 0;
    } else if (!strncasecmp(req->cmd, "single", strlen("single"))) {
        mreq->pkt_frame_single = 1;
    } else if (!strncasecmp(req->cmd, "reset_enable", strlen("reset_enable"))) {
        mreq->mon_reset_enable = 1;
    } else if (!strncasecmp(req->cmd, "reset_disable", strlen("reset_disable"))) {
        mreq->mon_reset_enable = 0;
    } else {
        return 1;
    }

    return 0;
}

static int cli_param_prbs_pattern(cli_req_t *req)
{
    phy25g_appl_diag_t *mreq = req->module_req;
    int                 len = 0;
    len = strlen(req->cmd);
    unsigned int temp[8];
    if (len > 31) {
        cli_printf("\n Invalid PRBS Pattern\n");
        return 1;
    }
    if (sscanf(req->cmd, "%u,%u,%u,%u,%u,%u,%u,%u", &temp[0], &temp[1], &temp[2], &temp[3],
               &temp[4], &temp[5], &temp[6], &temp[7]) == 8) {

        for (u8 i = 0; i < 8; i++) {
            if (temp[i] >= 255) {
                cli_printf("\n Invalid Range of Input \n");
                return 1;
            }
            mreq->prbs_user_pattern[i] = temp[i];
        }
    }
    for (int i = 0; i < 8; i++) {
        cli_printf("\n user_pattern[%d] : %d \n", i, mreq->prbs_user_pattern[i]);
    }
    mreq->user_pattern_parsed = 1;
    return 0;
}

static cli_cmd_t cli_cmd_table[] = {
    {
     "PHY EYE_DIAG <port_no> <normal|fast> <host|line>", "Serdes EYE Diagram",
     cli_cmd_eye_diag, },

    {
     "PHY RX_EQA <port_no> <host|line> <dfe_adp|dfe_man|disable> ctle_r <equ_val> ctle_c <equ_val> vga <equ_val>",
     "Rx Equalizer Config",                                                                                                                           cli_cmd_rx_eqa,
     },

    {
     "PHY TX_EQA <port_no> <host|line> amp <equ_val> tap_dly <equ_val> tap_adv <equ_val>",                              "Tx Equalizer Config",
     cli_cmd_tx_eqa, },

    {
     "PHY CL45_READ <port_no> <mmd> <address>",                                                        "Clause 45 CSR Read of PHY",
     cli_cmd_csr_rd, },

    {
     "PHY CL45_WRITE <port_no> <mmd> <address> <reg_val>",                                    "Clause 45 CSR Write of PHY",
     cli_cmd_csr_wr, },

    {
     "PHY STATE <port_no>",          "PCS and PMA Status of PHY",
     cli_cmd_phy_state, },

    {
     "PHY PRBS_TEST <port_no> <host|line> <prbs7|prbs9|prbs11|prbs15|prbs23|prbs31|user_ptn> <gen_enable|gen_disable> <mon_enable|mon_disable> [<user_val>]",
     "PRBS Generator and Monitor Conf",                                                                                                                           cli_cmd_prbs_set,
     },

    {
     "PHY PRBS_STATUS <port_no> <host|line>","PRBS Staus",
     cli_cmd_prbs_status, },

    {
     "PHY PKT_BIST <port_no> <eth|ptp> <egr|ingr> <conti|single> <ethtype> <src_mac> <dst_mac> <gen_enable|gen_disable> <mon_enable|mon_disable>",
     "Packet generator",                                                                                                         cli_cmd_pkt_bist,
     },

    {
     "PHY PKT_MON <port_no> reset <reset_enable|reset_disable>",                                 "Packet Monitor Status",
     cli_cmd_pkt_mon, },
};

static cli_parm_t cli_parm_table[] = {
    {"<normal|fast>", "Normal Eye Scan or Fast Eye Scan", CLI_PARM_FLAG_NONE, cli_param_parse},

    {"<host|line>", "Host Side or Line Side", CLI_PARM_FLAG_SET, cli_param_parse},

    {"<mon_enable|mon_disable>", "Enable or Disable Pattern Checker", CLI_PARM_FLAG_SET,
     cli_param_parse},

    {"<gen_enable|gen_disable>", "Enable or Disable Pattern Generator", CLI_PARM_FLAG_SET,
     cli_param_parse},

    {"<src_mac>", "Source MAC Address", CLI_PARM_FLAG_NONE, cli_param_parse_src_mac},

    {"<dst_mac>", "Distination MAC Address", CLI_PARM_FLAG_NONE, cli_param_parse_dst_mac},

    {"<eth|ptp>", "Ehernet packet or PTP packet", CLI_PARM_FLAG_NONE, cli_param_parse},

    {"<egr|ingr>", "Egress Direction or Ingress Direction", CLI_PARM_FLAG_NONE, cli_param_parse},

    {"<conti|single>", "Continuous Packet or Single packet", CLI_PARM_FLAG_NONE, cli_param_parse},

    {"<ethtype>", "Ethertype", CLI_PARM_FLAG_NONE, cli_param_parse_ethtype},

    {"<prbs7|prbs9|prbs11|prbs15|prbs23|prbs31|user_ptn>", "PRBS Patterns", CLI_PARM_FLAG_NONE,
     cli_param_parse},

    {"<user_val>", "User Defined Pattern in XXX,XXX,XXX,XXX,XXX,XXX,XXX,XXX format",
     CLI_PARM_FLAG_NONE, cli_param_prbs_pattern},

    {"<mmd>", "MMD ID of Register", CLI_PARM_FLAG_NONE, cli_cmd_parse_mmd_id},

    {"<address>", "Register Address", CLI_PARM_FLAG_SET, cli_cmd_parse_reg_addr},

    {"<reg_val>", "Register value", CLI_PARM_FLAG_SET, cli_cmd_parse_reg_val},

    {"<dfe_adp|dfe_man|disable>", "Adpative DFE or Manual DFE or Disable DFE", CLI_PARM_FLAG_NONE,
     cli_param_parse},

    {"<reset_enable|reset_disable>", "Enable/Disable Pkt Monitor Reset", CLI_PARM_FLAG_SET,
     cli_param_parse},

    {"<equ_val>", "Equalizer Coefficients", CLI_PARM_FLAG_SET, cli_param_value},

    {
     "ctle_r", "Keyword",
     CLI_PARM_FLAG_NONE, cli_param_keyword,
     },

    {
     "ctle_c", "Keyword",
     CLI_PARM_FLAG_NONE, cli_param_keyword,
     },

    {
     "vga", "Keyword",
     CLI_PARM_FLAG_NONE, cli_param_keyword,
     },

    {
     "amp", "Keyword",
     CLI_PARM_FLAG_NONE, cli_param_keyword,
     },

    {
     "tap_dly", "Keyword",
     CLI_PARM_FLAG_NONE, cli_param_keyword,
     },

    {
     "tap_adv", "Keyword",
     CLI_PARM_FLAG_NONE, cli_param_keyword,
     },

    {
     "reset", "Keyword",
     CLI_PARM_FLAG_NONE, cli_param_keyword,
     },
};

static void phy_cli_init(void)
{
    int i;

    /* Register CLI Commands */
    for (i = 0; i < sizeof(cli_cmd_table) / sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }

    /* Register CLI Params */
    for (i = 0; i < sizeof(cli_parm_table) / sizeof(cli_parm_t); i++) {
        mscc_appl_cli_parm_reg(&cli_parm_table[i]);
    }
}

void mscc_appl_m25gdiag_demo(mscc_appl_init_t *init)
{
    meba_phy_diag_instance = init->board_inst;
    switch (init->cmd) {
    case MSCC_INIT_CMD_INIT: phy_cli_init(); break;
    default:                 break;
    }
}
