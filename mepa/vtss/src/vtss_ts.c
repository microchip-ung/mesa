// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>
#include <vtss_phy_api.h>
#include "vtss_private.h"

#include <string.h>

//#define PRINT 1
#ifdef PRINT
#include <stdio.h>
#define pr(...) printf(__VA_ARGS__)
#define spr(...) sprintf(__VA_ARGS__)
#else
#define pr(fmt,...)
#define spr(...)
#endif


// valid clocks for the 4 configurable engines
static uint8_t valid_clocks[4][2] = {{0, 1}, {2, 3}, {4, 5}, {4, 5}};
static uint8_t def_mac[] = {0x01, 0x1B, 0x19, 0x00, 0x00, 0x00};

void get_eng_clock_info(uint16_t clk_id, vtss_phy_ts_engine_t *eng_id, uint16_t *act_id);
static uint8_t get_vs_channel_mask(mepa_device_t *dev);

// Only one callback for all the ports.
static mepa_ts_fifo_read_t fifo_cb;
///////////////////////////////////////////////////////////////////////////////////
//   Private Functions
///////////////////////////////////////////////////////////////////////////////////
static void get_default_ts_eth_class(mepa_ts_classifier_eth_t *const conf)
{
    conf->mac_match_mode = MEPA_TS_ETH_ADDR_MATCH_ANY;
    conf->mac_match_select = MEPA_TS_ETH_MATCH_DEST_ADDR;
    memcpy(conf->mac_addr, def_mac, sizeof(conf->mac_addr));
    conf->vlan_check = false;
    conf->vlan_conf.pbb_en = false;
    conf->vlan_conf.tpid = 0x88A8;
    conf->vlan_conf.etype = 0x88f7;
    conf->vlan_conf.num_tag = 0;
}
static void get_default_ts_ip_class(mepa_ts_classifier_ip_t *const conf)
{
    conf->ip_ver = MEPA_TS_IP_VER_4;
    conf->ip_match_mode = MEPA_TS_IP_MATCH_DEST;
    conf->ip_addr.ipv4.addr = conf->ip_addr.ipv4.mask = 0;
    memset(conf->ip_addr.ipv6.addr, 0, sizeof(conf->ip_addr.ipv6.addr));
    memset(conf->ip_addr.ipv6.mask, 0, sizeof(conf->ip_addr.ipv6.mask));
    conf->udp_sport_en = false;
    conf->udp_dport_en = true;
    conf->udp_sport = 0;
    conf->udp_dport = 319;
}
static void get_default_ts_ptp_class(mepa_ts_classifier_ptp_t *const conf)
{
    conf->version.upper = 2;
    conf->version.lower = 2;
    conf->minor_version.upper = conf->minor_version.lower = 0;
    //domain
    conf->domain.mode = MEPA_TS_MATCH_MODE_VALUE;
    conf->domain.match.value.val = 0;
    conf->domain.match.value.mask = 0xF;
    //sdoid
    conf->sdoid.mode = MEPA_TS_MATCH_MODE_VALUE;
    conf->sdoid.match.value.val = 0;
    conf->sdoid.match.value.mask = 0; //not used for 1588-2008 standard
}
static void get_default_ts_classifier(mepa_ts_classifier_t *const conf)
{
    conf->pkt_encap_type = MEPA_TS_ENCAP_NONE;
    conf->clock_id = 0;
    get_default_ts_eth_class(&conf->eth_class_conf);
    get_default_ts_ip_class(&conf->ip_class_conf);
}
static mepa_ts_ptp_clock_mode_t get_mepa_clk_mode(vtss_phy_ts_ptp_clock_mode_t input)
{
    mepa_ts_ptp_clock_mode_t ret = (input == VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP) ? MEPA_TS_PTP_CLOCK_MODE_BC1STEP :
                                   (input == VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP) ? MEPA_TS_PTP_CLOCK_MODE_BC2STEP :
                                   (input == VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP) ? MEPA_TS_PTP_CLOCK_MODE_TC1STEP :
                                   (input == VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP) ? MEPA_TS_PTP_CLOCK_MODE_TC2STEP : MEPA_TS_PTP_CLOCK_MODE_NONE;
    return ret;
}

static vtss_phy_ts_ptp_clock_mode_t get_mesa_clk_mode(mepa_ts_ptp_clock_mode_t in)
{
    vtss_phy_ts_ptp_clock_mode_t ret = (in == MEPA_TS_PTP_CLOCK_MODE_BC1STEP) ? VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP :
                                       (in == MEPA_TS_PTP_CLOCK_MODE_BC2STEP) ? VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP :
                                       (in == MEPA_TS_PTP_CLOCK_MODE_TC1STEP) ? VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP :
                                       (in == MEPA_TS_PTP_CLOCK_MODE_TC2STEP) ? VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP : VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP;
    return ret;
}

static vtss_phy_ts_ptp_delaym_type_t get_mesa_delay_type(mepa_ts_ptp_delaym_type_t in)
{
    return (in == MEPA_TS_PTP_DELAYM_P2P) ? VTSS_PHY_TS_PTP_DELAYM_P2P : VTSS_PHY_TS_PTP_DELAYM_E2E;
}

static void get_clk_from_action(mepa_device_t *dev, const vtss_phy_ts_ptp_engine_action_t *action, mepa_ts_ptp_clock_conf_t *const clk_conf)
{
    mepa_ts_match_uint8_t sdoid = {};
    clk_conf->enable = action->channel_map & get_vs_channel_mask(dev) ? true : false;
    T_I(data, MEPA_TRACE_GRP_TS, "clk_mode %d", action->clk_mode);
    clk_conf->clk_mode = get_mepa_clk_mode(action->clk_mode);
    clk_conf->delaym_type = (action->delaym_type == VTSS_PHY_TS_PTP_DELAYM_E2E) ? MEPA_TS_PTP_DELAYM_E2E : MEPA_TS_PTP_DELAYM_P2P;
    clk_conf->ptp_class_conf.version.lower = 2; // unused
    clk_conf->ptp_class_conf.version.upper = 2; // unused
    clk_conf->ptp_class_conf.minor_version.lower = 0; // unused
    clk_conf->ptp_class_conf.minor_version.upper = 0; // unused
    clk_conf->ptp_class_conf.domain.mode = action->ptp_conf.range_en ? MEPA_TS_MATCH_MODE_RANGE : MEPA_TS_MATCH_MODE_VALUE;
    if (clk_conf->ptp_class_conf.domain.mode == MEPA_TS_MATCH_MODE_RANGE) {
        clk_conf->ptp_class_conf.domain.match.range.upper = action->ptp_conf.domain.range.upper;
        clk_conf->ptp_class_conf.domain.match.range.lower = action->ptp_conf.domain.range.lower;
    } else {
        clk_conf->ptp_class_conf.domain.match.value.val = action->ptp_conf.domain.value.val;
        clk_conf->ptp_class_conf.domain.match.value.mask = action->ptp_conf.domain.value.mask;
    }
    clk_conf->ptp_class_conf.sdoid = sdoid; // unused
}

static mesa_rc mepa_to_vtss_encap(mepa_ts_pkt_encap_t encap, vtss_phy_ts_encap_t *vsc_encap)
{
    mesa_rc rc = MESA_RC_OK;
    switch (encap) {
    case MEPA_TS_ENCAP_ETH_PTP:
        *vsc_encap = VTSS_PHY_TS_ENCAP_ETH_PTP;
        break;
    case MEPA_TS_ENCAP_ETH_IP_PTP:
        *vsc_encap = VTSS_PHY_TS_ENCAP_ETH_IP_PTP;
        break;
    case MEPA_TS_ENCAP_NONE:
        *vsc_encap = VTSS_PHY_TS_ENCAP_NONE;
        break;
    default:
        rc = MESA_RC_ERROR;
        break;
    }
    return rc;
}
//dumps engines 0,1
static void dump_chip_matching_flow(mepa_device_t *dev, mepa_bool_t ingress)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t eth_comm[] = {0, 3};
    uint16_t eth_fl[] = {0x10, 0x16}, incr = 0x10;
    uint16_t ip_comm[] = {0x1B0, 0x1B8};
    uint16_t ip_fl[] = {0x1C0, 0x1C8};
    uint16_t i, j, st_fl;
    uint32_t blk_id = ingress ? 0 : 1;
    uint32_t value, cnt = 0;

    pr(" Dump class flows\n");
    while (cnt++ < 2) {
        pr("\n*** %s class BLK-ID : %d ***\n", ingress ? "ingress" : "egress", blk_id);
        // print common conf
        for (i = eth_comm[0]; i <= eth_comm[1]; i++) {
            vtss_phy_1588_csr_reg_read(data->vtss_instance, data->port_no, blk_id, i, &value);
            pr("0x%x : 0x%x\n", i, value);
        }
        pr("\n\n");
        // print header
        st_fl = eth_fl[0];
        pr("%8s", " ");
        for (i = 0; i < 8; i++) {
            pr("0x%-8x ", st_fl);
            st_fl += incr;
        }
        pr("\n");
        pr("%8s", " ");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 10; j++) {
                pr("-");
            }
            pr(" ");
        }
        pr("\n");

        // print eth flows
        for (j = eth_fl[0]; j <= eth_fl[1]; j++) {
            pr("0x%-4x: ", j);
            st_fl = j;
            for (i = 0; i < 8; i++) {
                vtss_phy_1588_csr_reg_read(data->vtss_instance, data->port_no, blk_id, st_fl, &value);
                pr("0x%-8x ", value);
                st_fl += incr;
            }
            pr("\n");
        }
        pr("\n\n");
        // print ip common conf
        for (i = ip_comm[0]; i <= ip_comm[1]; i++) {
            vtss_phy_1588_csr_reg_read(data->vtss_instance, data->port_no, blk_id, i, &value);
            pr("0x%x : 0x%x\n", i, value);
        }
        pr("\n\n");
        // print header
        st_fl = ip_fl[0];
        pr("%8s", " ");
        for (i = 0; i < 8; i++) {
            pr("0x%-8x ", st_fl);
            st_fl += incr;
        }
        pr("\n");
        pr("%8s", " ");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 10; j++) {
                pr("-");
            }
            pr(" ");
        }
        pr("\n");

        // print ip flows
        for (j = ip_fl[0]; j <= ip_fl[1]; j++) {
            pr("0x%-4x: ", j);
            st_fl = j;
            for (i = 0; i < 8; i++) {
                vtss_phy_1588_csr_reg_read(data->vtss_instance, data->port_no, blk_id, st_fl, &value);
                pr("0x%-8x ", value);
                st_fl += incr;
            }
            pr("\n");
        }
        blk_id += 2;
    }
}
static void dump_chip_ptp_flow(mepa_device_t *dev, mepa_bool_t ingress)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t ptp_fl[] = {0x2D0, 0x2D8};
    uint16_t i, j, st_fl, incr = 0x10;
    uint32_t blk_id, value, cnt = 0;

    blk_id = ingress ? 0 : 1;
    while (cnt++ < 2) {
        pr("\n*** %s ptp BLK-ID : %d ***\n", ingress ? "ingress" : "egress", blk_id);
        // print header
        st_fl = ptp_fl[0];
        pr("%8s", " ");
        for (i = 0; i < 6; i++) {
            pr("0x%-8x ", st_fl);
            st_fl += incr;
        }
        pr("\n");
        pr("%8s", " ");
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 10; j++) {
                pr("-");
            }
            pr(" ");
        }
        pr("\n");

        // print ptp flows
        for (j = ptp_fl[0]; j <= ptp_fl[1]; j++) {
            pr("0x%-4x: ", j);
            st_fl = j;
            for (i = 0; i < 6; i++) {
                vtss_phy_1588_csr_reg_read(data->vtss_instance, data->port_no, blk_id, st_fl, &value);
                pr("0x%-8x ", value);
                st_fl += incr;
            }
            pr("\n");
        }
        blk_id += 2;
    }
}
static void dump_flow_conf(vtss_phy_ts_engine_flow_conf_t *flow_conf)
{
    int i;

    pr("\nflow conf: eng_mode %d ", flow_conf->eng_mode);
    pr("ptp comm: ppb_en %d, etype %x, tpid %x\n", flow_conf->flow_conf.ptp.eth1_opt.comm_opt.pbb_en,
       flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype,
       flow_conf->flow_conf.ptp.eth1_opt.comm_opt.tpid);
    for (i = 0; i < 8; i++) {
        pr(" channel_map[%d] %d ", i, flow_conf->channel_map[i]);
        pr(" ptp flow: flow_en %d, match_mode %d, match_select %d\n", flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].flow_en,
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].addr_match_mode,
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].addr_match_select);
        pr(" mac address : %02x-%02x-%02x-%02x-%02x-%02x\n", flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].mac_addr[0],
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].mac_addr[1],
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].mac_addr[2],
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].mac_addr[3],
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].mac_addr[4],
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].mac_addr[5]);
        pr(" vlan_check %d, num_tag %d, outer_tag_type %d, inner_tag_type %d, tag_range_mode %d\n",
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].vlan_check,
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].num_tag,
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].outer_tag_type,
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].inner_tag_type,
           flow_conf->flow_conf.ptp.eth1_opt.flow_opt[i].tag_range_mode);
    }
}
static void dump_ptp_action(vtss_phy_ts_engine_action_t *ptp_action)
{
    int i;
    pr("\naction_ptp %d\n", ptp_action->action_ptp);
    for (i = 0; i < 2; i++) {
        pr(" action[%d]: enable %d, channel_map %d\n", i, ptp_action->action.ptp_conf[i].enable, ptp_action->action.ptp_conf[i].channel_map);
        pr("  ptpconf: range_en %d, val/upper %d, mask/lower %d\n", ptp_action->action.ptp_conf[i].ptp_conf.range_en,
           ptp_action->action.ptp_conf[i].ptp_conf.domain.value.val,
           ptp_action->action.ptp_conf[i].ptp_conf.domain.value.mask);
        pr("   clk__mode %d, delaym_type %d\n", ptp_action->action.ptp_conf[i].clk_mode,
           ptp_action->action.ptp_conf[i].delaym_type);
    }
}

static uint8_t get_vs_channel_mask(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint8_t ch_mask = 0;
    vtss_phy_type_t phy_id_1g;
    vtss_phy_10g_id_t phy_id_10g;

    if (data->cap == PHY_CAP_1G) {
        if (vtss_phy_id_get(data->vtss_instance, data->port_no, &phy_id_1g) == MESA_RC_OK) {
            ch_mask = phy_id_1g.phy_api_base_no == data->port_no ? VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 : VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
        } else {
            T_W(data, MEPA_TRACE_GRP_TS, "error getting 1G phy id info");
        }
    } else {
        if (vtss_phy_10g_id_get(data->vtss_instance, data->port_no, &phy_id_10g) == MESA_RC_OK) {
            ch_mask = phy_id_10g.channel_id % 2 == 0 ? VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 : VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
        } else {
            T_W(data, MEPA_TRACE_GRP_TS, "error getting 10G phy id info");
        }
    }

    return ch_mask;
}
static uint8_t get_vs_addr_type(mepa_ts_mac_match_mode_t mac_match)
{
    uint8_t ret = 0;
    switch (mac_match) {
    case MEPA_TS_ETH_ADDR_MATCH_48BIT:
        ret = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
        break;
    case MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST:
        ret = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST;
        break;
    case MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST:
        ret = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST;
        break;
    case MEPA_TS_ETH_ADDR_MATCH_ANY:
    default:
        ret = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST | MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST;
        break;
    }
    return ret;
}
static mepa_ts_mac_match_mode_t get_mepa_eth_match_mode(uint8_t match_mode)
{
    mepa_ts_mac_match_mode_t ret = MEPA_TS_ETH_ADDR_MATCH_ANY;
    if ((match_mode & VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST) &&
        (match_mode & VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST)) {
        ret = MEPA_TS_ETH_ADDR_MATCH_ANY;
    } else if (match_mode & VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST) {
        ret = MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST;
    } else if (match_mode & VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST) {
        ret = MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST;
    } else if (match_mode & VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT) {
        ret = MEPA_TS_ETH_ADDR_MATCH_48BIT;
    }
    return ret;
}
static mepa_ts_mac_match_select_t get_mepa_eth_match_select(uint8_t match_sel)
{
    mepa_ts_mac_match_select_t ret = MEPA_TS_ETH_MATCH_NONE;
    if (match_sel == VTSS_PHY_TS_ETH_MATCH_DEST_ADDR) {
        ret = MEPA_TS_ETH_MATCH_DEST_ADDR;
    } else if (match_sel == VTSS_PHY_TS_ETH_MATCH_SRC_ADDR) {
        ret = MEPA_TS_ETH_MATCH_SRC_ADDR;
    } else if (match_sel == VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST) {
        ret = MEPA_TS_ETH_MATCH_SRC_OR_DEST;
    }
    return ret;
}
static mepa_ts_ip_match_select_t get_mepa_ip_match_mode(uint8_t match)
{
    mepa_ts_ip_match_select_t ret = MEPA_TS_IP_MATCH_NONE;
    if (match == VTSS_PHY_TS_IP_MATCH_SRC) {
        ret = MEPA_TS_IP_MATCH_SRC;
    } else if (match == VTSS_PHY_TS_IP_MATCH_DEST) {
        ret = MEPA_TS_IP_MATCH_DEST;
    } else if (match == VTSS_PHY_TS_IP_MATCH_SRC_OR_DEST) {
        ret = MEPA_TS_IP_MATCH_SRC_OR_DEST;
    }
    return ret;
}
static uint8_t get_vs_mac_type(mepa_ts_mac_match_select_t mac_type)
{
    uint8_t ret;
    switch (mac_type) {
    case MEPA_TS_ETH_MATCH_DEST_ADDR:
        ret = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
        break;
    case MEPA_TS_ETH_MATCH_SRC_ADDR:
        ret = VTSS_PHY_TS_ETH_MATCH_SRC_ADDR;
        break;
    case MEPA_TS_ETH_MATCH_SRC_OR_DEST:
    default:
        ret = VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST;
        break;
    }
    return ret;
}
void get_eng_flow_info(uint16_t in_flow, vtss_phy_ts_engine_t *eng_id, uint16_t *eng_flow, uint8_t *flow_st, uint8_t *flow_end)
{
    if (in_flow >= 0 && in_flow < TS_FLOWS_PER_ENG * (VTSS_PHY_TS_PTP_ENGINE_ID_0 + 1)) {
        *eng_id = VTSS_PHY_TS_PTP_ENGINE_ID_0;
    } else if (in_flow >= (TS_FLOWS_PER_ENG * VTSS_PHY_TS_PTP_ENGINE_ID_1) &&
               in_flow <  (TS_FLOWS_PER_ENG * VTSS_PHY_TS_OAM_ENGINE_ID_2A)) {
        *eng_id = VTSS_PHY_TS_PTP_ENGINE_ID_1;
    } else if (in_flow >= (TS_FLOWS_PER_ENG * VTSS_PHY_TS_OAM_ENGINE_ID_2A) &&
               in_flow <  (TS_FLOWS_PER_ENG * (VTSS_PHY_TS_OAM_ENGINE_ID_2A + 1))) {
        *eng_id = VTSS_PHY_TS_OAM_ENGINE_ID_2A;
    } else {
        *eng_id = VTSS_PHY_TS_ENGINE_ID_INVALID;
    }
    *eng_flow = in_flow % TS_FLOWS_PER_ENG;
    *flow_st = 0;
    *flow_end = 7;
    return;
}
void get_eng_clock_info(uint16_t clk_id, vtss_phy_ts_engine_t *eng_id, uint16_t *act_id)
{
    *eng_id = clk_id / TS_ACTIONS_PER_ENGINE;
    *act_id = clk_id % TS_ACTIONS_PER_ENGINE;
}

#if 0
static mepa_rc get_ts_alt_base_dev(mepa_device_t *dev, mepa_device_t **ts_base_dev, mepa_device_t **ts_alt_dev)
{
    vtss_phy_type_t id;
    phy_data_t *data = (phy_data_t *)(dev->data), *alt_data;
    phy_data_t *base_data = (phy_data_t *)(data->base_dev->data);
    mepa_port_no_t base_port;

    vtss_phy_id_get(data->vtss_instance, data->port_no, &id);
    T_I(data, MEPA_TRACE_GRP_TS, "base port %d port %d base_no %d\n", base_data->port_no, data->port_no, id.phy_api_base_no);
    if (id.phy_api_base_no == data->port_no) {
        *ts_base_dev = dev;
        for (int i = 0; i < MAX_PORTS_PER_PHY; i++) {
            if (dev == base_data->other_dev[i]) {
                continue;
            }
            alt_data = (phy_data_t *)(base_data->other_dev[i]->data);
            vtss_phy_id_get(data->vtss_instance, alt_data->port_no, &id);
            T_D(data, MEPA_TRACE_GRP_TS, "alt port %d base_no %d\n", alt_data->port_no, id.phy_api_base_no);
            if (id.phy_api_base_no == data->port_no) {
                *ts_alt_dev = base_data->other_dev[i];
                phy_data_t *alt_data = (phy_data_t *)((*ts_alt_dev)->data);
                T_D(data, MEPA_TRACE_GRP_TS, "alt_dev port %d\n", alt_data->port_no );
                return MEPA_RC_OK;
            }
        }
    } else {
        base_port = id.phy_api_base_no;
        for (int i = 0; i < MAX_PORTS_PER_PHY; i++) {
            if (dev == base_data->other_dev[i]) {
                continue;
            }
            alt_data = (phy_data_t *)(base_data->other_dev[i]->data);
            vtss_phy_id_get(data->vtss_instance, alt_data->port_no, &id);
            T_D(data, MEPA_TRACE_GRP_TS, "alt port %d base_no %d\n", alt_data->port_no, id.phy_api_base_no);
            if (id.phy_api_base_no == base_port) {
                *ts_base_dev = base_data->other_dev[i];
                *ts_alt_dev = base_data->other_dev[i];
                phy_data_t *alt_data = (phy_data_t *)((*ts_alt_dev)->data);
                T_D(data, MEPA_TRACE_GRP_TS, "alt_dev port %d\n", alt_data->port_no );
                return MEPA_RC_OK;
                break;
            }
        }
    }
    T_I(data, MEPA_TRACE_GRP_TS, "reached end of alt dev base search");
    return MEPA_RC_ERROR;
}
#endif

static vtss_phy_ts_tc_op_mode_t mepa_to_mesa_tc_opmode(mepa_ts_tc_op_mode_t tc_opmode)
{
    vtss_phy_ts_tc_op_mode_t ret;
    switch (tc_opmode) {
    case MEPA_TS_TC_OP_MODE_A:
        ret = VTSS_PHY_TS_TC_OP_MODE_B;
        break;
    case MEPA_TS_TC_OP_MODE_B:
        ret = VTSS_PHY_TS_TC_OP_MODE_A;
        break;
    case MEPA_TS_TC_OP_MODE_C:
        ret = VTSS_PHY_TS_TC_OP_MODE_C;
        break;
    default:
        ret = VTSS_PHY_TS_TC_OP_MODE_B;
        break;
    }
    return ret;
}
static void get_eth_class_from_flow(const vtss_phy_ts_eth_conf_t *flow, uint8_t flow_id, mepa_ts_classifier_eth_t *const cls_eth)
{
    cls_eth->mac_match_mode = get_mepa_eth_match_mode(flow->flow_opt[flow_id].addr_match_mode);
    cls_eth->mac_match_select = get_mepa_eth_match_select(flow->flow_opt[flow_id].addr_match_select);
    memcpy(cls_eth->mac_addr, flow->flow_opt[flow_id].mac_addr, sizeof(cls_eth->mac_addr));
    cls_eth->vlan_check = flow->flow_opt[flow_id].vlan_check;
    cls_eth->vlan_conf.pbb_en = flow->comm_opt.pbb_en; //common option
    cls_eth->vlan_conf.tpid = flow->comm_opt.tpid;  //common option
    cls_eth->vlan_conf.etype = flow->comm_opt.etype; //common option
    cls_eth->vlan_conf.num_tag = flow->flow_opt[flow_id].num_tag;
    cls_eth->vlan_conf.outer_tag.mode = MEPA_TS_MATCH_MODE_VALUE;
    cls_eth->vlan_conf.inner_tag.mode = MEPA_TS_MATCH_MODE_VALUE;
    if (flow->flow_opt[flow_id].tag_range_mode == VTSS_PHY_TS_TAG_RANGE_OUTER) {
        cls_eth->vlan_conf.outer_tag.mode = MEPA_TS_MATCH_MODE_RANGE;
    } else if (flow->flow_opt[flow_id].tag_range_mode == VTSS_PHY_TS_TAG_RANGE_INNER) {
        cls_eth->vlan_conf.inner_tag.mode = MEPA_TS_MATCH_MODE_RANGE;
    }
    if (cls_eth->vlan_conf.outer_tag.mode == MEPA_TS_MATCH_MODE_RANGE) {
        cls_eth->vlan_conf.outer_tag.match.range.lower = flow->flow_opt[flow_id].outer_tag.range.lower;
        cls_eth->vlan_conf.outer_tag.match.range.upper = flow->flow_opt[flow_id].outer_tag.range.upper;
    } else {
        cls_eth->vlan_conf.outer_tag.match.value.val  = flow->flow_opt[flow_id].outer_tag.value.val;
        cls_eth->vlan_conf.outer_tag.match.value.mask = flow->flow_opt[flow_id].outer_tag.value.mask;
    }
    if (cls_eth->vlan_conf.inner_tag.mode == MEPA_TS_MATCH_MODE_RANGE) {
        cls_eth->vlan_conf.inner_tag.match.range.lower = flow->flow_opt[flow_id].inner_tag.range.lower;
        cls_eth->vlan_conf.inner_tag.match.range.upper = flow->flow_opt[flow_id].inner_tag.range.upper;
    } else {
        cls_eth->vlan_conf.inner_tag.match.value.val  = flow->flow_opt[flow_id].inner_tag.value.val;
        cls_eth->vlan_conf.inner_tag.match.value.mask = flow->flow_opt[flow_id].inner_tag.value.mask;
    }
}

static void get_ip_class_from_flow(const vtss_phy_ts_ip_conf_t *ip, uint8_t flow_id, mepa_ts_classifier_ip_t *const cls_ip)
{
    cls_ip->ip_ver = ip->comm_opt.ip_mode == VTSS_PHY_TS_IP_VER_6 ? MEPA_TS_IP_VER_6 : MEPA_TS_IP_VER_4;
    cls_ip->ip_match_mode = get_mepa_ip_match_mode(ip->flow_opt[flow_id].match_mode);
    if (cls_ip->ip_ver == MEPA_TS_IP_VER_6) {
        memcpy(cls_ip->ip_addr.ipv6.addr, ip->flow_opt[flow_id].ip_addr.ipv6.addr, sizeof(cls_ip->ip_addr.ipv6.addr));
        memcpy(cls_ip->ip_addr.ipv6.mask, ip->flow_opt[flow_id].ip_addr.ipv6.mask, sizeof(cls_ip->ip_addr.ipv6.mask));
    } else {
        cls_ip->ip_addr.ipv4.addr = ip->flow_opt[flow_id].ip_addr.ipv4.addr;
        cls_ip->ip_addr.ipv4.mask = ip->flow_opt[flow_id].ip_addr.ipv4.mask;
    }

    cls_ip->udp_sport_en = ip->comm_opt.sport_mask ? true : false;
    cls_ip->udp_dport_en = ip->comm_opt.dport_mask ? true : false;
    cls_ip->udp_sport = ip->comm_opt.sport_val;
    cls_ip->udp_dport = ip->comm_opt.dport_val;
}
static void get_class_from_flow(const vtss_phy_ts_engine_flow_conf_t *flow, uint8_t flow_id, mepa_ts_classifier_t *const cls_conf)
{
    get_eth_class_from_flow(&flow->flow_conf.ptp.eth1_opt, flow_id, &cls_conf->eth_class_conf);
    get_ip_class_from_flow(&flow->flow_conf.ptp.ip1_opt, flow_id, &cls_conf->ip_class_conf);
}
static mepa_bool_t get_compare_common_opt(const vtss_phy_ts_ptp_engine_flow_conf_t *flow, const mepa_ts_classifier_t *cls)
{
    // Compare ethernet common options.
    if ((cls->eth_class_conf.vlan_conf.pbb_en != flow->eth1_opt.comm_opt.pbb_en) ||
        (cls->eth_class_conf.vlan_conf.etype  != flow->eth1_opt.comm_opt.etype)  ||
        (cls->eth_class_conf.vlan_conf.tpid   != flow->eth1_opt.comm_opt.tpid)) {
        return false;
    }

    // compare ip common options.
    if (cls->pkt_encap_type == MEPA_TS_ENCAP_ETH_IP_PTP) {
        if (((cls->ip_class_conf.ip_ver == MEPA_TS_IP_VER_6) &&
             (flow->ip1_opt.comm_opt.ip_mode == VTSS_PHY_TS_IP_VER_4)) ||
            ((cls->ip_class_conf.ip_ver == MEPA_TS_IP_VER_4) &&
             (flow->ip1_opt.comm_opt.ip_mode == VTSS_PHY_TS_IP_VER_6))) {
            return false;
        }
        if ((cls->ip_class_conf.udp_dport_en && !flow->ip1_opt.comm_opt.dport_mask) ||
            (!cls->ip_class_conf.udp_dport_en && flow->ip1_opt.comm_opt.dport_mask) ||
            (cls->ip_class_conf.udp_sport_en && !flow->ip1_opt.comm_opt.sport_mask) ||
            (!cls->ip_class_conf.udp_sport_en && flow->ip1_opt.comm_opt.sport_mask)) {
            return false;
        }
    }
    return true;
}
///////////////////////////////////////////////////////////////////////////////////
//   Public Api Functions
///////////////////////////////////////////////////////////////////////////////////
static mepa_rc vtss_ts_init_conf_get(mepa_device_t *dev, mepa_ts_init_conf_t *const ts_init_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    mepa_bool_t                     ts_init_done;
    vtss_phy_ts_init_conf_t         init_conf;
    phy_data_t *data = (phy_data_t *)dev->data;

    rc =  vtss_phy_ts_init_conf_get(data->vtss_instance, data->port_no, &ts_init_done, &init_conf);
    if (rc != MEPA_RC_OK) {
        return rc;
    }
    ts_init_conf->clk_src           = init_conf.clk_src;
    ts_init_conf->clk_freq          = init_conf.clk_freq;
    ts_init_conf->rx_ts_len         = init_conf.rx_ts_len == VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT ? MEPA_TS_RX_TIMESTAMP_LEN_30BIT : MEPA_TS_RX_TIMESTAMP_LEN_32BIT;
    ts_init_conf->rx_ts_pos         = init_conf.rx_ts_pos == VTSS_PHY_TS_RX_TIMESTAMP_POS_AT_END ? MEPA_TS_RX_TIMESTAMP_POS_AT_END : MEPA_TS_RX_TIMESTAMP_POS_IN_PTP;
    ts_init_conf->tx_fifo_mode      = init_conf.tx_fifo_mode;
    ts_init_conf->tx_fifo_spi_conf  = data->ts.tx_fifo_spi_conf;
    ts_init_conf->tx_ts_len         = init_conf.tx_ts_len == VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE ? MEPA_TS_FIFO_TIMESTAMP_LEN_10BYTE : MEPA_TS_FIFO_TIMESTAMP_LEN_4BYTE;
    ts_init_conf->auto_clear_ls     = init_conf.auto_clear_ls;
    ts_init_conf->dly_req_recv_10byte_ts = data->ts.dly_req_recv_10byte_ts;
    ts_init_conf->tc_op_mode  = init_conf.tc_op_mode;

    return MEPA_RC_OK;
}

static mepa_rc vtss_ts_init_conf_set(struct mepa_device *dev, const mepa_ts_init_conf_t *const ts_init_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_init_conf_t init_conf = {};

    data->ts.dly_req_recv_10byte_ts = ts_init_conf->dly_req_recv_10byte_ts;
    data->ts.tx_fifo_spi_conf = ts_init_conf->tx_fifo_spi_conf;
    init_conf.clk_freq = ts_init_conf->clk_freq;
    T_I(data, MEPA_TRACE_GRP_GEN, "clock frequency %d\n", ts_init_conf->clk_freq);
    if (ts_init_conf->clk_src == MEPA_TS_CLOCK_SRC_INTERNAL) {
        init_conf.clk_src = VTSS_PHY_TS_CLOCK_SRC_INTERNAL;
    } else if (ts_init_conf->clk_src > MEPA_TS_CLOCK_SRC_INTERNAL) {
        init_conf.clk_src = VTSS_PHY_TS_CLOCK_SRC_EXTERNAL;
    } else {
        init_conf.clk_src = ts_init_conf->clk_src;
    }
    init_conf.rx_ts_len         = ts_init_conf->rx_ts_len == MEPA_TS_RX_TIMESTAMP_LEN_30BIT ? VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT : VTSS_PHY_TS_RX_TIMESTAMP_LEN_32BIT;
    init_conf.rx_ts_pos         = ts_init_conf->rx_ts_pos == MEPA_TS_RX_TIMESTAMP_POS_AT_END ? VTSS_PHY_TS_RX_TIMESTAMP_POS_AT_END : VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP;
    init_conf.tx_fifo_mode = ts_init_conf->tx_fifo_mode;
    init_conf.tx_ts_len = ts_init_conf->tx_ts_len == MEPA_TS_FIFO_TIMESTAMP_LEN_10BYTE ? VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE : VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE;
    init_conf.tx_fifo_spi_conf = ts_init_conf->tx_fifo_spi_conf;

    if (data->cap == PHY_CAP_10G) {
        init_conf.xaui_sel_8487 = VTSS_PHY_TS_8487_XAUI_SEL_0; /**< 8487 XAUI lane selection*/
    }
    if (data->cap == PHY_CAP_10G) {
        vtss_phy_10g_id_t phy_id;
        vtss_phy_10g_id_get(data->vtss_instance, data->port_no, &phy_id);
        if (phy_id.part_number == 0x8489 || phy_id.part_number == 0x8490 || phy_id.part_number == 0x8491 ||
            phy_id.family == VTSS_PHY_FAMILY_MALIBU) {
            init_conf.auto_clear_ls = true;
        } else {
            init_conf.auto_clear_ls = false;
        }
    } else {
        vtss_phy_type_t phy_id;
        vtss_phy_id_get(data->vtss_instance, data->port_no, &phy_id);
        if (phy_id.part_number == VTSS_PHY_TYPE_8582 || phy_id.part_number == VTSS_PHY_TYPE_8584 ||
            phy_id.part_number == VTSS_PHY_TYPE_8575) {
            init_conf.auto_clear_ls = true;
        } else {
            init_conf.auto_clear_ls = false;
        }
    }
    init_conf.tc_op_mode = mepa_to_mesa_tc_opmode(ts_init_conf->tc_op_mode);

    init_conf.macsec_ena = false;
    init_conf.chk_ing_modified = false;
    init_conf.one_step_txfifo = false;

    return vtss_phy_ts_init(data->vtss_instance, data->port_no, &init_conf);
}

static mepa_rc vtss_ts_mode_get(mepa_device_t *dev, mepa_bool_t *const enable)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    return vtss_phy_ts_mode_get(data->vtss_instance, data->port_no,  enable);
}

static mepa_rc vtss_ts_mode_set(mepa_device_t *dev, const mepa_bool_t enable)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    return vtss_phy_ts_mode_set(data->vtss_instance, data->port_no,  enable);
}

static mepa_rc vtss_ts_ltc_ls_en_set(mepa_device_t *dev, const mepa_ts_ls_type_t  ls_type)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    switch (ls_type) {
    case MEPA_TS_CMD_LOAD:
        return vtss_phy_ts_ptptime_set_done(data->vtss_instance, data->port_no);
        break;
    case MEPA_TS_CMD_SAVE:
        return vtss_phy_ts_ptptime_arm(data->vtss_instance, data->port_no);
        break;
    default:
        break;
    }
    return MEPA_RC_OK;
}

static mepa_rc vtss_ts_ltc_get(mepa_device_t *dev, mepa_timestamp_t *const ts)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_timestamp_t vts;
    mesa_rc rc;

    if ((rc = vtss_phy_ts_ptptime_get(data->vtss_instance, data->port_no, &vts)) == MESA_RC_OK) {
        ts->seconds.high = vts.seconds.high;
        ts->seconds.low  = vts.seconds.low;
        ts->nanoseconds  = vts.nanoseconds;
        return MEPA_RC_OK;
    } else {
        return MEPA_RC_ERROR;
    }
}

static mepa_rc vtss_ts_ltc_set(mepa_device_t *dev, const mepa_timestamp_t *const ts)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_timestamp_t vts;

    vts.seconds.high = ts->seconds.high;
    vts.seconds.low = ts->seconds.low;
    vts.nanoseconds = ts->nanoseconds;
    return vtss_phy_ts_ptptime_set(data->vtss_instance, data->port_no, &vts);
}

static mepa_rc vtss_ts_clock_rateadj_get(mepa_device_t *dev, mepa_ts_scaled_ppb_t *const adj)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_clock_rateadj_get(data->vtss_instance, data->port_no, adj);
}

static mepa_rc vtss_ts_clock_rateadj_set(mepa_device_t *dev, const mepa_ts_scaled_ppb_t *const adj)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_clock_rateadj_set(data->vtss_instance, data->port_no, adj);
}

static mepa_rc vtss_ts_clock_adj1ns(mepa_device_t *dev, const mepa_bool_t incr)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_ptptime_adj1ns(data->vtss_instance, data->port_no, incr);
}

static mepa_rc vtss_ts_clock_delay_asymmetry_get(mepa_device_t *dev, mepa_timeinterval_t *const delay_asym)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_delay_asymmetry_get(data->vtss_instance, data->port_no, delay_asym);
}

static mepa_rc vtss_ts_clock_delay_asymmetry_set(mepa_device_t *dev, const mepa_timeinterval_t *const delay_asym)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_delay_asymmetry_set(data->vtss_instance, data->port_no, delay_asym);
}

static mepa_rc vtss_ts_clock_path_delay_get(mepa_device_t *dev, mepa_timeinterval_t *const path_delay)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_path_delay_get(data->vtss_instance, data->port_no, path_delay);
}

static mepa_rc vtss_ts_clock_path_delay_set(mepa_device_t *dev, const mepa_timeinterval_t *const path_delay)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_path_delay_set(data->vtss_instance, data->port_no, path_delay);
}

static mepa_rc vtss_ts_clock_egress_latency_get(mepa_device_t *dev, mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_egress_latency_get(data->vtss_instance, data->port_no, latency);

}

static mepa_rc vtss_ts_clock_egress_latency_set(mepa_device_t *dev, const mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_egress_latency_set(data->vtss_instance, data->port_no, latency);
}

static mepa_rc vtss_ts_clock_ingress_latency_get(mepa_device_t *dev, mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_ingress_latency_get(data->vtss_instance, data->port_no, latency);
}

static mepa_rc vtss_ts_clock_ingress_latency_set(mepa_device_t *dev, const mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_ingress_latency_set(data->vtss_instance, data->port_no, latency);
}

static mepa_rc phy_rx_clock_conf_get(mepa_device_t *dev, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const clk_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_engine_action_t action_conf;
    vtss_phy_ts_eng_init_conf_t eng_init_conf;
    vtss_phy_ts_engine_t eng_id = 0;
    uint16_t act_id;
    mesa_rc rc;
    mepa_rc ret = MEPA_RC_OK;

    T_I(data, MEPA_TRACE_GRP_TS, "start");
    get_eng_clock_info(clock_id, &eng_id, &act_id);
    // Check whether engine is used.
    rc = vtss_phy_ts_ingress_engine_init_conf_get(data->vtss_instance, data->port_no, eng_id, &eng_init_conf);
    if (rc != MESA_RC_OK) {
        // engine not used. Set default configurations
        get_default_ts_ptp_class(&clk_conf->ptp_class_conf);
        clk_conf->clk_mode = MEPA_TS_PTP_CLOCK_MODE_NONE;
        clk_conf->delaym_type = MEPA_TS_PTP_DELAYM_E2E;
        clk_conf->enable = false;
    } else {
        rc = vtss_phy_ts_ingress_engine_action_get(data->vtss_instance, data->port_no, eng_id, &action_conf);
        if (rc == MESA_RC_OK) {
            get_clk_from_action(dev, &action_conf.action.ptp_conf[act_id], clk_conf);
        } else {
            ret = MEPA_RC_ERR_TS_ACTION_GET_FAIL;
        }
    }
    T_I(data, MEPA_TRACE_GRP_TS, "end ");
    //dump_ptp_action(&action_conf);
    //dump_chip_ptp_flow(dev, true);
    return ret;
}
static mepa_rc phy_tx_clock_conf_get(mepa_device_t *dev, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const clk_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_engine_action_t action_conf;
    vtss_phy_ts_eng_init_conf_t eng_init_conf;
    vtss_phy_ts_engine_t eng_id = 0;
    uint16_t act_id;
    mesa_rc rc;
    mepa_rc ret = MEPA_RC_OK;

    get_eng_clock_info(clock_id, &eng_id, &act_id);
    T_I(data, MEPA_TRACE_GRP_TS, "eng_id %d act_id %d", eng_id, act_id);
    // Check whether engine is used.
    rc = vtss_phy_ts_egress_engine_init_conf_get(data->vtss_instance, data->port_no, eng_id, &eng_init_conf);
    if (rc != MESA_RC_OK) {
        T_I(data, MEPA_TRACE_GRP_TS, "No action configured");
        // engine not used. Set default configurations
        get_default_ts_ptp_class(&clk_conf->ptp_class_conf);
        clk_conf->clk_mode = MEPA_TS_PTP_CLOCK_MODE_NONE;
        clk_conf->delaym_type = MEPA_TS_PTP_DELAYM_E2E;
        clk_conf->enable = false;
    } else {
        rc = vtss_phy_ts_egress_engine_action_get(data->vtss_instance, data->port_no, eng_id, &action_conf);
        if (rc == MESA_RC_OK) {
            get_clk_from_action(dev, &action_conf.action.ptp_conf[act_id], clk_conf);
        } else {
            ret = MEPA_RC_ERR_TS_ACTION_GET_FAIL;
        }
    }
    T_I(data, MEPA_TRACE_GRP_TS, "here ");
    //dump_ptp_action(&action_conf);
    //dump_chip_ptp_flow(dev, false);
    return ret;
}
static mepa_rc phy_tx_classifier_conf_get(mepa_device_t *dev, uint16_t in_flow, mepa_ts_classifier_t *const out_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_engine_t eng_id;
    vtss_phy_ts_eng_init_conf_t eng_init_conf;
    vtss_phy_ts_engine_flow_conf_t flow_conf;
    uint16_t flow_id;
    uint8_t flow_start, flow_end;
    mesa_rc rc;

    T_I(data, MEPA_TRACE_GRP_TS, "tx class start");
    get_eng_flow_info(in_flow, &eng_id, &flow_id, &flow_start, &flow_end);
    // Check whether engine is used.
    rc = vtss_phy_ts_egress_engine_init_conf_get(data->vtss_instance, data->port_no, eng_id, &eng_init_conf);
    if (rc != MESA_RC_OK) {
        // return default config
        get_default_ts_classifier(out_conf);
    } else {
        // Get conf from engine
        rc = vtss_phy_ts_egress_engine_conf_get(data->vtss_instance, data->port_no, eng_id, &flow_conf);
        if (rc != MESA_RC_OK) {
            return MEPA_RC_ERR_TS_FLOW_GET_FAIL;
        }
        out_conf->pkt_encap_type = (eng_init_conf.encap_type == VTSS_PHY_TS_ENCAP_ETH_PTP) ? MEPA_TS_ENCAP_ETH_PTP :
                                   (eng_init_conf.encap_type == VTSS_PHY_TS_ENCAP_ETH_IP_PTP) ? MEPA_TS_ENCAP_ETH_IP_PTP :
                                   MEPA_TS_ENCAP_NONE;
        out_conf->enable = (flow_conf.channel_map[flow_id] & get_vs_channel_mask(dev)) ? true : false;
        get_class_from_flow(&flow_conf, flow_id, out_conf);
        out_conf->clock_id = data->ts.tx_flow_clk[in_flow];
    }
    T_I(data, MEPA_TRACE_GRP_TS, "tx class end");
    return MEPA_RC_OK;
}

static mepa_rc phy_rx_classifier_conf_get(mepa_device_t *dev, uint16_t in_flow, mepa_ts_classifier_t *const out_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_engine_t eng_id;
    vtss_phy_ts_eng_init_conf_t eng_init_conf;
    vtss_phy_ts_engine_flow_conf_t flow_conf;
    uint16_t flow_id;
    uint8_t flow_start, flow_end;
    mesa_rc rc;

    T_I(data, MEPA_TRACE_GRP_TS, "here ");
    get_eng_flow_info(in_flow, &eng_id, &flow_id, &flow_start, &flow_end);
    // Check whether engine is used.
    rc = vtss_phy_ts_ingress_engine_init_conf_get(data->vtss_instance, data->port_no, eng_id, &eng_init_conf);
    if (rc != MESA_RC_OK) {
        // return default config
        get_default_ts_classifier(out_conf);
    } else {
        // Get conf from engine
        rc = vtss_phy_ts_ingress_engine_conf_get(data->vtss_instance, data->port_no, eng_id, &flow_conf);
        if (rc != MESA_RC_OK) {
            return MEPA_RC_ERR_TS_FLOW_GET_FAIL;
        }
        out_conf->pkt_encap_type = (eng_init_conf.encap_type == VTSS_PHY_TS_ENCAP_ETH_PTP) ? MEPA_TS_ENCAP_ETH_PTP :
                                   (eng_init_conf.encap_type == VTSS_PHY_TS_ENCAP_ETH_IP_PTP) ? MEPA_TS_ENCAP_ETH_IP_PTP :
                                   MEPA_TS_ENCAP_NONE;
        out_conf->enable = (flow_conf.channel_map[flow_id] & get_vs_channel_mask(dev)) ? true : false;
        get_class_from_flow(&flow_conf, flow_id, out_conf);
        out_conf->clock_id = data->ts.rx_flow_clk[in_flow];
    }
    T_I(data, MEPA_TRACE_GRP_TS, "here ");
    //dump_flow_conf(&flow_conf);
    //dump_chip_matching_flow(dev, true);
    return MEPA_RC_OK;
}

static mepa_rc vtss_ts_rx_clock_conf_set(mepa_device_t *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    vtss_phy_ts_engine_action_t action_conf;
    vtss_phy_ts_engine_t eng_id = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t act_id;
    mesa_rc rc = MESA_RC_OK;
    vtss_phy_ts_ptp_engine_action_t *action;
    uint8_t ch_map;
    mepa_bool_t act_chng = false;

    T_I(data, MEPA_TRACE_GRP_TS, "rx clock start");

    get_eng_clock_info(clock_id, &eng_id, &act_id);
    rc = vtss_phy_ts_ingress_engine_action_get(data->vtss_instance, data->port_no, eng_id, &action_conf);
    if (rc != MESA_RC_OK) {
        return MEPA_RC_ERR_TS_ENG_INVALID_CLOCK;
    }
    action = &action_conf.action.ptp_conf[act_id];
    if ((ptpclock_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_NONE) ||
        (!ptpclock_conf->enable)) {
        T_I(data, MEPA_TRACE_GRP_TS, "disabling action channel mask ");
        action->channel_map &= ~(get_vs_channel_mask(dev));
        if ((ptpclock_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_NONE) &&
            (!action->channel_map)) {
            action->enable = false;
        }
    } else if (action->enable) {
        T_I(data, MEPA_TRACE_GRP_TS, "action enabled already with clk_mode %d in mode %d\n", action->clk_mode, ptpclock_conf->clk_mode);
        dump_ptp_action(&action_conf);
        if ((action->clk_mode != get_mesa_clk_mode(ptpclock_conf->clk_mode)) ||
            (action->delaym_type != get_mesa_delay_type(ptpclock_conf->delaym_type))) {
            act_chng = true;
        }
        ch_map = get_vs_channel_mask(dev);
        if (action->channel_map && act_chng && (action->channel_map != ch_map)) {
            return MEPA_RC_ERR_TS_ACTION_IN_USE;
        }
        action->channel_map |= ch_map;
    } else {
        T_I(data, MEPA_TRACE_GRP_TS, "clk_mode %d delaym_type %d act-id %d\n", ptpclock_conf->clk_mode, ptpclock_conf->delaym_type, act_id);
        action->enable = true;
        action->channel_map |= get_vs_channel_mask(dev);
        action->clk_mode = get_mesa_clk_mode(ptpclock_conf->clk_mode);
        action->delaym_type = get_mesa_delay_type(ptpclock_conf->delaym_type);
        action->cf_update = false;
        action->delay_req_recieve_timestamp = data->ts.dly_req_recv_10byte_ts;
    }
    if (action->enable && ptpclock_conf->ptp_class_conf.domain.mode == MEPA_TS_MATCH_MODE_RANGE) {
        action->ptp_conf.range_en = true;
        action->ptp_conf.domain.range.lower = ptpclock_conf->ptp_class_conf.domain.match.range.lower;
        action->ptp_conf.domain.range.upper = ptpclock_conf->ptp_class_conf.domain.match.range.upper;
    } else {
        action->ptp_conf.range_en = false;
        action->ptp_conf.domain.value.val  = ptpclock_conf->ptp_class_conf.domain.match.value.val & 0xff;
        action->ptp_conf.domain.value.mask = ptpclock_conf->ptp_class_conf.domain.match.value.mask & 0xff;
    }

    rc = vtss_phy_ts_ingress_engine_action_set(data->vtss_instance, data->port_no, eng_id, &action_conf);
    dump_ptp_action(&action_conf);
    dump_chip_ptp_flow(dev, true);
    T_I(data, MEPA_TRACE_GRP_TS, "rx clock end");
    return (rc == MESA_RC_OK) ? MEPA_RC_OK : MEPA_RC_ERROR;
}

static mepa_rc vtss_ts_tx_clock_conf_set(mepa_device_t *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    vtss_phy_ts_engine_action_t action_conf;
    vtss_phy_ts_engine_t eng_id = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t act_id;
    mesa_rc rc = MESA_RC_OK;
    vtss_phy_ts_ptp_engine_action_t *action;
    uint8_t ch_map;
    mepa_bool_t act_chng = false;

    T_I(data, MEPA_TRACE_GRP_TS, "start ");
    T_I(data, MEPA_TRACE_GRP_TS, "Get engine action ");
    get_eng_clock_info(clock_id, &eng_id, &act_id);
    rc = vtss_phy_ts_egress_engine_action_get(data->vtss_instance, data->port_no, eng_id, &action_conf);
    if (rc != MESA_RC_OK) {
        return MEPA_RC_ERR_TS_ENG_INVALID_CLOCK;
    }
    action = &action_conf.action.ptp_conf[act_id];
    if ((ptpclock_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_NONE) ||
        (!ptpclock_conf->enable)) {
        T_I(data, MEPA_TRACE_GRP_TS, "disabling action channel mask ");
        action->channel_map &= ~(get_vs_channel_mask(dev));
        if ((ptpclock_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_NONE) &&
            (!action->channel_map)) {
            action->enable = false;
        }
    } else if (action->enable) {
        T_I(data, MEPA_TRACE_GRP_TS, "action enabled already\n");
        if ((action->clk_mode != get_mesa_clk_mode(ptpclock_conf->clk_mode)) ||
            (action->delaym_type != get_mesa_delay_type(ptpclock_conf->delaym_type)) ||
            (action->cf_update != ptpclock_conf->cf_update)) {
            act_chng = true;
        }
        ch_map = get_vs_channel_mask(dev);
        if (action->channel_map && act_chng && (action->channel_map != ch_map)) {
            return MEPA_RC_ERR_TS_ACTION_IN_USE;
        }
        action->channel_map |= ch_map;
    } else {
        T_I(data, MEPA_TRACE_GRP_TS, "clk_mode %d delaym_type %d cf_update %d\n", ptpclock_conf->delaym_type, ptpclock_conf->cf_update);
        action->enable = true;
        action->channel_map |= get_vs_channel_mask(dev);
        action->clk_mode = get_mesa_clk_mode(ptpclock_conf->clk_mode);
        action->delaym_type = get_mesa_delay_type(ptpclock_conf->delaym_type);
        action->cf_update = false;
        action->delay_req_recieve_timestamp = false;
    }
    if (action->enable && ptpclock_conf->ptp_class_conf.domain.mode == MEPA_TS_MATCH_MODE_RANGE) {
        action->ptp_conf.range_en = true;
        action->ptp_conf.domain.range.lower = ptpclock_conf->ptp_class_conf.domain.match.range.lower;
        action->ptp_conf.domain.range.upper = ptpclock_conf->ptp_class_conf.domain.match.range.upper;
    } else {
        action->ptp_conf.range_en = false;
        action->ptp_conf.domain.value.val  = ptpclock_conf->ptp_class_conf.domain.match.value.val & 0xff;
        action->ptp_conf.domain.value.mask = ptpclock_conf->ptp_class_conf.domain.match.value.mask & 0xff;
    }
    T_I(data, MEPA_TRACE_GRP_TS, "Set engine action");

    rc = vtss_phy_ts_egress_engine_action_set(data->vtss_instance, data->port_no, eng_id, &action_conf);
    dump_ptp_action(&action_conf);
    dump_chip_ptp_flow(dev, false);
    T_I(data, MEPA_TRACE_GRP_TS, "end ");
    return (rc == MESA_RC_OK) ? MEPA_RC_OK : MEPA_RC_ERROR;
}

static mepa_rc vtss_ts_pps_conf_get (mepa_device_t *dev, mepa_ts_pps_conf_t *const phy_pps_conf)
{

    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_pps_conf_t pps_conf;
    mesa_rc rc;

    if ((rc =  vtss_phy_ts_pps_conf_get(data->vtss_instance, data->port_no, &pps_conf)) == MESA_RC_OK) {
        phy_pps_conf->pps_width_adj = pps_conf.pps_width_adj;
        phy_pps_conf->pps_offset = pps_conf.pps_offset;
        phy_pps_conf->pps_output_enable = pps_conf.pps_output_enable;
        return MEPA_RC_OK;
    } else {
        return MEPA_RC_ERROR;
    }
}

static mepa_rc vtss_ts_pps_conf_set (mepa_device_t *dev, const mepa_ts_pps_conf_t *const phy_pps_conf)
{

    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_pps_conf_t pps_conf;

    pps_conf.pps_width_adj = phy_pps_conf->pps_width_adj;
    pps_conf.pps_offset = phy_pps_conf->pps_offset;
    pps_conf.pps_output_enable = phy_pps_conf->pps_output_enable;
    return vtss_phy_ts_pps_conf_set(data->vtss_instance, data->port_no, &pps_conf);
}

mepa_rc vtss_ts_stats_get(mepa_device_t *dev, mepa_ts_stats_t *const statistics)
{

    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_stats_t stats;
    mesa_rc rc;

    if ((rc = vtss_phy_ts_stats_get(data->vtss_instance, data->port_no, &stats)) == MESA_RC_OK) {
        statistics->ingr_pream_shrink_err = stats.ingr_pream_shrink_err;
        statistics->egr_pream_shrink_err = stats.egr_pream_shrink_err;
        statistics->ingr_fcs_err         = stats.ingr_fcs_err;
        statistics->egr_fcs_err          = stats.egr_fcs_err;
        statistics->ingr_frm_mod_cnt     = stats.ingr_frm_mod_cnt;
        statistics->egr_frm_mod_cnt      = stats.egr_frm_mod_cnt;
        statistics->ts_fifo_tx_cnt       = stats.ts_fifo_tx_cnt;
        statistics->ts_fifo_drop_cnt     = stats.ts_fifo_drop_cnt;
        return MEPA_RC_OK;
    } else {
        return MEPA_RC_ERROR;
    }
}

static mepa_rc vtss_ts_event_get (mepa_device_t *dev,
                                  mepa_ts_event_t *const ev_mask)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    return vtss_phy_ts_event_enable_get(data->vtss_instance, data->port_no, ev_mask);
}

static mepa_rc vtss_ts_event_set (mepa_device_t *dev, const mepa_bool_t enable, const mepa_ts_event_t ev_mask)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    return vtss_phy_ts_event_enable_set(data->vtss_instance, data->port_no, enable, ev_mask);
}

static mepa_rc vtss_ts_event_poll(mepa_device_t *dev, mepa_ts_event_t  *const status)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_event_poll(data->vtss_instance, data->port_no, status);

}

static mepa_rc phy_ts_rx_classifier_conf_set(struct mepa_device *dev, uint16_t in_flow, const mepa_ts_classifier_t *const in_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_eng_init_conf_t eng_init_conf;
    vtss_phy_ts_engine_flow_conf_t flow_conf;
    vtss_phy_ts_engine_t eng_id;
    uint16_t flow_id, i;
    uint8_t flow_start, flow_end;
    vtss_phy_ts_eth_conf_t *eth;
    vtss_phy_ts_eth_flow_conf_t *eth_flow;
    vtss_phy_ts_ip_conf_t *ip;
    vtss_phy_ts_ip_flow_conf_t *ip_flow;
    const mepa_ts_classifier_eth_t *eth_in = &in_conf->eth_class_conf;
    const mepa_ts_classifier_ip_t *ip_in = &in_conf->ip_class_conf;
    const mepa_range_unit16_t *range_in;
    const mepa_value_unit16_t *val_in;
    vtss_phy_ts_encap_t encap;
    vtss_phy_ts_engine_action_t action_conf;
    mesa_rc v_rc;

    T_I(data, MEPA_TRACE_GRP_TS, "Rx class conf set Start");
    get_eng_flow_info(in_flow, &eng_id, &flow_id, &flow_start, &flow_end);
    if (mepa_to_vtss_encap(in_conf->pkt_encap_type, &encap) != MESA_RC_OK) {
        T_I(data, MEPA_TRACE_GRP_TS, "Could not convert encap pkt encap %d", in_conf->pkt_encap_type);
        return MEPA_RC_ERR_TS_INVALID_ENCAP;
    }

    // step - 1
    // Verify if the engine is initialised
    v_rc = vtss_phy_ts_ingress_engine_init_conf_get(data->vtss_instance, data->port_no, eng_id, &eng_init_conf);
    T_I(data, MEPA_TRACE_GRP_TS, "Get engine init conf \n");
    if (v_rc != MESA_RC_OK) {
        // Engine not initialised.
        v_rc = vtss_phy_ts_ingress_engine_init(data->vtss_instance, data->port_no, eng_id, encap, flow_start, flow_end, VTSS_PHY_TS_ENG_FLOW_MATCH_STRICT);
        if (v_rc != MESA_RC_OK) {
            return MEPA_RC_ERR_TS_ENG_INIT;
        }
        // clear channel maps
        v_rc = vtss_phy_ts_ingress_engine_conf_get(data->vtss_instance, data->port_no, eng_id, &flow_conf);
        for (i = 0; i < 8; i++) {
            flow_conf.channel_map[i] = 0;
        }
        v_rc = vtss_phy_ts_ingress_engine_action_get(data->vtss_instance, data->port_no, eng_id, &action_conf);
        action_conf.action.ptp_conf[0].enable = action_conf.action.ptp_conf[1].enable = false;
        action_conf.action.ptp_conf[0].channel_map = action_conf.action.ptp_conf[1].channel_map = 0;
        v_rc = vtss_phy_ts_ingress_engine_action_set(data->vtss_instance, data->port_no, eng_id, &action_conf);
        T_I(data, MEPA_TRACE_GRP_TS, "engine init configured \n");
    } else {
        // Check the encap already configured on engine is same as input encapsulation.
        if (in_conf->pkt_encap_type != MEPA_TS_ENCAP_NONE && encap != eng_init_conf.encap_type) {
            T_I(data, MEPA_TRACE_GRP_TS, "engine encap error");
            return MEPA_RC_ERR_TS_ENG_ENCAP_OVERWRITE;
        }
        v_rc = vtss_phy_ts_ingress_engine_conf_get(data->vtss_instance, data->port_no, eng_id, &flow_conf);
        if (v_rc != MESA_RC_OK) {
            T_I(data, MEPA_TRACE_GRP_TS, "could not get egress engine conf");
            return MEPA_RC_ERR_TS_FLOW_CONF;
        }
        if (!get_compare_common_opt(&flow_conf.flow_conf.ptp, in_conf)) {
            T_W(data, MEPA_TRACE_GRP_TS, "overwriting common configuration not valid");
            // Allow over-writing common conf. The last config applied is the one that applies for all flows finally. Otherwise,
            // it is not possible to modify common configuration after initialisation.
            //return MEPA_RC_ERR_TS_ENG_COMM_OVERWRITE;
        }
        T_I(data, MEPA_TRACE_GRP_TS, "engine conf obtained");
    }
    if (in_conf->pkt_encap_type == MEPA_TS_ENCAP_NONE) {
        // clear the channel map and check whether engine needs to be disabled.
        flow_conf.channel_map[flow_id] &= ~(get_vs_channel_mask(dev));
        mepa_bool_t eng_used = false;
        for (i = 0; i < 8; i++) {
            if (flow_conf.channel_map[i]) {
                eng_used = true;
            }
        }
        if (!eng_used) {
            // clear the engine.
            if (vtss_phy_ts_ingress_engine_clear(data->vtss_instance, data->port_no, eng_id) != MESA_RC_OK) {
                T_I(data, MEPA_TRACE_GRP_TS, "Not able to clear the ingress engine %d port %d", eng_id, data->port_no);
                return MEPA_RC_ERR_TS_ENG_CLR;
            }
            T_I(data, MEPA_TRACE_GRP_TS, "engine conf cleared");
        } else {
            dump_flow_conf(&flow_conf);
            if (vtss_phy_ts_ingress_engine_conf_set(data->vtss_instance, data->port_no, eng_id, &flow_conf) != MESA_RC_OK) {
                T_I(data, MEPA_TRACE_GRP_TS, " Not able to set ingress flow configuration for flow %d", flow_id);
                return MEPA_RC_ERR_TS_FLOW_CONF;
            }
        }
    } else {
        // engine 0 -> 0, 1 clock-ids
        // engine 1 -> 2, 3 clock-ids
        // engine 2 -> 4, 5 clock-ids
        if (in_conf->clock_id != valid_clocks[eng_id][0] && in_conf->clock_id != valid_clocks[eng_id][1]) {
            return MEPA_RC_ERR_TS_ENG_INVALID_CLOCK;
        } else {
            data->ts.rx_flow_clk[in_flow] = in_conf->clock_id;
        }
        eth = &flow_conf.flow_conf.ptp.eth1_opt;
        eth_flow = &eth->flow_opt[flow_id];
        ip = &flow_conf.flow_conf.ptp.ip1_opt;
        ip_flow = &ip->flow_opt[flow_id];
        if (encap == VTSS_PHY_TS_ENCAP_ETH_IP_PTP) {
            // ip common options
            if (ip_in->ip_ver == MEPA_TS_IP_VER_6) {
                ip->comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
            } else {
                ip->comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
            }
            ip->comm_opt.dport_mask = in_conf->ip_class_conf.udp_dport_en ? 0xFFFF : 0;
            ip->comm_opt.dport_val = in_conf->ip_class_conf.udp_dport;
            ip->comm_opt.sport_mask = in_conf->ip_class_conf.udp_sport_en ? 0xFFFF : 0;
            ip->comm_opt.sport_val = in_conf->ip_class_conf.udp_sport;
        }
        // ethernet common options
        eth->comm_opt.pbb_en = eth_in->vlan_conf.pbb_en;
        eth->comm_opt.etype = eth_in->vlan_conf.etype;
        eth->comm_opt.tpid = eth_in->vlan_conf.tpid;

        // flow common options
        flow_conf.channel_map[flow_id] |= get_vs_channel_mask(dev);
        flow_conf.eng_mode = true;

        // ip flow conf
        if (encap == VTSS_PHY_TS_ENCAP_ETH_IP_PTP) {
            ip_flow->flow_en = true;
            ip_flow->match_mode = ip_in->ip_match_mode; // mepa_ts_ip_match_select_t uses same order as vsc constants.
            if (ip_in->ip_ver == MEPA_TS_IP_VER_6) {
                memcpy(&ip_flow->ip_addr.ipv6.addr, &ip_in->ip_addr.ipv6.addr, sizeof(ip_flow->ip_addr.ipv6.addr));
                memcpy(&ip_flow->ip_addr.ipv6.mask, &ip_in->ip_addr.ipv6.mask, sizeof(ip_flow->ip_addr.ipv6.mask));
            } else {
                ip_flow->ip_addr.ipv4.addr = ip_in->ip_addr.ipv4.addr;
                ip_flow->ip_addr.ipv4.mask = ip_in->ip_addr.ipv4.mask;
            }
        }

        // ethernet flow conf
        eth_flow->flow_en = true;
        eth_flow->addr_match_mode = get_vs_addr_type(in_conf->eth_class_conf.mac_match_mode);
        eth_flow->addr_match_select = get_vs_mac_type(in_conf->eth_class_conf.mac_match_select);
        memcpy(eth_flow->mac_addr, eth_in->mac_addr, sizeof(eth_in->mac_addr));
        eth_flow->vlan_check = eth_in->vlan_check;
        eth_flow->num_tag = eth_in->vlan_conf.num_tag;
        eth_flow->tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
        if (eth->comm_opt.pbb_en && (eth_in->vlan_conf.outer_tag.mode == MEPA_TS_MATCH_MODE_RANGE ||
                                     eth_in->vlan_conf.inner_tag.mode == MEPA_TS_MATCH_MODE_RANGE)) {
            T_I(data, MEPA_TRACE_GRP_TS, " For pbb enabled case, tag range cannot be configured");
            return MEPA_RC_ERROR;
        }
        if (eth->comm_opt.pbb_en) {
            eth_flow->outer_tag_type = VTSS_PHY_TS_TAG_TYPE_B;
            eth_flow->inner_tag_type = VTSS_PHY_TS_TAG_TYPE_I;
        } else if (eth_flow->num_tag > 0) {
            eth_flow->outer_tag_type = eth->comm_opt.tpid ? VTSS_PHY_TS_TAG_TYPE_S : VTSS_PHY_TS_TAG_TYPE_C;
            eth_flow->inner_tag_type = eth->comm_opt.tpid ? VTSS_PHY_TS_TAG_TYPE_S : VTSS_PHY_TS_TAG_TYPE_C;
        }
        if (eth_in->vlan_conf.outer_tag.mode == MEPA_TS_MATCH_MODE_RANGE) {
            eth_flow->tag_range_mode = VTSS_PHY_TS_TAG_RANGE_OUTER;
            range_in = &eth_in->vlan_conf.outer_tag.match.range;
            eth_flow->outer_tag.range.upper = range_in->upper;
            eth_flow->outer_tag.range.lower = range_in->lower;
        } else {//MEPA_TS_MATCH_MODE_VALUE
            val_in = &eth_in->vlan_conf.outer_tag.match.value;
            eth_flow->outer_tag.value.val = val_in->val;
            eth_flow->outer_tag.value.mask = val_in->mask;
        }
        if (eth_in->vlan_conf.inner_tag.mode == MEPA_TS_MATCH_MODE_RANGE) {
            eth_flow->tag_range_mode = VTSS_PHY_TS_TAG_RANGE_INNER;
            range_in = &eth_in->vlan_conf.inner_tag.match.range;
            eth_flow->inner_tag.range.upper = range_in->upper;
            eth_flow->inner_tag.range.lower = range_in->lower;
        } else {//MEPA_TS_MATCH_MODE_VALUE
            val_in = &eth_in->vlan_conf.inner_tag.match.value;
            eth_flow->inner_tag.value.val = val_in->val;
            eth_flow->inner_tag.value.mask = val_in->mask;
        }
        dump_flow_conf(&flow_conf);
        if (vtss_phy_ts_ingress_engine_conf_set(data->vtss_instance, data->port_no, eng_id, &flow_conf) != MESA_RC_OK) {
            T_I(data, MEPA_TRACE_GRP_TS, " Not able to set ingress flow configuration for flow %d", flow_id);
            return MEPA_RC_ERR_TS_FLOW_CONF;
        }
        T_I(data, MEPA_TRACE_GRP_TS, " ingress flow configuration done for flow %d", flow_id);
    }
    dump_chip_matching_flow(dev, true);
    //data->ts.rx_eng[eng_id].clock_id = in_conf->clock_id;
    T_I(data, MEPA_TRACE_GRP_TS, "exit");
    return MEPA_RC_OK;
}

static mepa_rc phy_ts_tx_classifier_conf_set(struct mepa_device *dev, uint16_t in_flow, const mepa_ts_classifier_t *const in_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_eng_init_conf_t eng_init_conf;
    vtss_phy_ts_engine_flow_conf_t flow_conf;
    vtss_phy_ts_engine_t eng_id;
    uint16_t flow_id, i;
    uint8_t flow_start, flow_end;
    vtss_phy_ts_eth_conf_t *eth;
    vtss_phy_ts_eth_flow_conf_t *eth_flow;
    vtss_phy_ts_ip_conf_t *ip;
    vtss_phy_ts_ip_flow_conf_t *ip_flow;
    const mepa_ts_classifier_eth_t *eth_in = &in_conf->eth_class_conf;
    const mepa_ts_classifier_ip_t *ip_in = &in_conf->ip_class_conf;
    const mepa_range_unit16_t *range_in;
    const mepa_value_unit16_t *val_in;
    vtss_phy_ts_encap_t encap;
    vtss_phy_ts_engine_action_t action_conf;
    mesa_rc v_rc;

    T_I(data, MEPA_TRACE_GRP_TS, "Tx class conf set start");
    get_eng_flow_info(in_flow, &eng_id, &flow_id, &flow_start, &flow_end);
    if (mepa_to_vtss_encap(in_conf->pkt_encap_type, &encap) != MESA_RC_OK) {
        T_I(data, MEPA_TRACE_GRP_TS, "Could not convert encap pkt encap %d", in_conf->pkt_encap_type);
        return MEPA_RC_ERR_TS_INVALID_ENCAP;
    }
    // engine 0 -> 0, 1 clock-ids
    // engine 1 -> 2, 3 clock-ids
    // engine 2 -> 4, 5 clock-ids
    if ((in_conf->pkt_encap_type != MEPA_TS_ENCAP_NONE) && (in_conf->clock_id != valid_clocks[eng_id][0] && in_conf->clock_id != valid_clocks[eng_id][1])) {
        return MEPA_RC_ERR_TS_ENG_INVALID_CLOCK;
    } else { // store clock id
        data->ts.tx_flow_clk[in_flow] = in_conf->clock_id;
    }

    T_I(data, MEPA_TRACE_GRP_TS, "Get engine init conf \n");
    // step - 1
    // Verify if the engine is initialised
    v_rc = vtss_phy_ts_egress_engine_init_conf_get(data->vtss_instance, data->port_no, eng_id, &eng_init_conf);
    if (v_rc != MESA_RC_OK) {
        T_I(data, MEPA_TRACE_GRP_TS, "flow_start %d flow_end %d eng_id %d\n", flow_start, flow_end, eng_id);
        // Engine not initialised.
        v_rc = vtss_phy_ts_egress_engine_init(data->vtss_instance, data->port_no, eng_id, encap, flow_start, flow_end, VTSS_PHY_TS_ENG_FLOW_MATCH_STRICT);
        if (v_rc != MESA_RC_OK) {
            return MEPA_RC_ERR_TS_ENG_INIT;
        }
        // clear channel maps
        v_rc = vtss_phy_ts_egress_engine_conf_get(data->vtss_instance, data->port_no, eng_id, &flow_conf);
        for (i = 0; i < 8; i++) {
            flow_conf.channel_map[i] = 0;
        }
        v_rc = vtss_phy_ts_egress_engine_action_get(data->vtss_instance, data->port_no, eng_id, &action_conf);
        action_conf.action.ptp_conf[0].enable = action_conf.action.ptp_conf[1].enable = false;
        action_conf.action.ptp_conf[0].channel_map = action_conf.action.ptp_conf[1].channel_map = 0;
        vtss_phy_ts_egress_engine_action_set(data->vtss_instance, data->port_no, eng_id, &action_conf);
        T_I(data, MEPA_TRACE_GRP_TS, "engine init configured \n");
    } else {
        // Check the encap already configured on engine is same as input encapsulation.
        if (in_conf->pkt_encap_type != MEPA_TS_ENCAP_NONE && encap != eng_init_conf.encap_type) {
            T_I(data, MEPA_TRACE_GRP_TS, "engine encap error");
            return MEPA_RC_ERR_TS_ENG_ENCAP_OVERWRITE;
        }
        v_rc = vtss_phy_ts_egress_engine_conf_get(data->vtss_instance, data->port_no, eng_id, &flow_conf);
        if (v_rc != MESA_RC_OK) {
            T_I(data, MEPA_TRACE_GRP_TS, "could not get egress engine conf");
            return MEPA_RC_ERR_TS_FLOW_CONF;
        }
        if (!get_compare_common_opt(&flow_conf.flow_conf.ptp, in_conf)) {
            T_W(data, MEPA_TRACE_GRP_TS, "overwriting common configuration not valid");
            // Allow over-writing common conf. The last config applied is the one that applies for all flows finally. Otherwise,
            // it is not possible to modify common configuration after initialisation.
            //return MEPA_RC_ERR_TS_ENG_COMM_OVERWRITE;
        }
        T_I(data, MEPA_TRACE_GRP_TS, "engine conf obtained");
    }
    if (in_conf->pkt_encap_type == MEPA_TS_ENCAP_NONE) {
        // clear the channel map and check whether engine needs to be disabled.
        flow_conf.channel_map[flow_id] &= ~(get_vs_channel_mask(dev));
        mepa_bool_t eng_used = false;
        for (i = 0; i < 8; i++) {
            if (flow_conf.channel_map[i]) {
                eng_used = true;
            }
        }
        if (!eng_used) {
            // clear the engine.
            if (vtss_phy_ts_egress_engine_clear(data->vtss_instance, data->port_no, eng_id) != MESA_RC_OK) {
                T_I(data, MEPA_TRACE_GRP_TS, "Not able to clear the egress engine %d port %d", eng_id, data->port_no);
                return MEPA_RC_ERR_TS_ENG_CLR;
            }
            T_I(data, MEPA_TRACE_GRP_TS, "engine conf cleared");
        } else {
            dump_flow_conf(&flow_conf);
            if (vtss_phy_ts_egress_engine_conf_set(data->vtss_instance, data->port_no, eng_id, &flow_conf) != MESA_RC_OK) {
                T_I(data, MEPA_TRACE_GRP_TS, " Not able to set egress flow configuration for flow %d", flow_id);
                return MEPA_RC_ERR_TS_FLOW_CONF;
            }
        }
    } else {
        eth = &flow_conf.flow_conf.ptp.eth1_opt;
        eth_flow = &eth->flow_opt[flow_id];
        ip = &flow_conf.flow_conf.ptp.ip1_opt;
        ip_flow = &ip->flow_opt[flow_id];
        if (encap == VTSS_PHY_TS_ENCAP_ETH_IP_PTP) {
            // ip common options
            if (ip_in->ip_ver == MEPA_TS_IP_VER_6) {
                ip->comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
            } else {
                ip->comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
            }
            ip->comm_opt.dport_mask = in_conf->ip_class_conf.udp_dport_en ? 0xFFFF : 0;
            ip->comm_opt.dport_val = in_conf->ip_class_conf.udp_dport;
            ip->comm_opt.sport_mask = in_conf->ip_class_conf.udp_sport_en ? 0xFFFF : 0;
            ip->comm_opt.sport_val = in_conf->ip_class_conf.udp_sport;
        }
        // ethernet common options
        eth->comm_opt.pbb_en = eth_in->vlan_conf.pbb_en;
        eth->comm_opt.etype = eth_in->vlan_conf.etype;
        eth->comm_opt.tpid = eth_in->vlan_conf.tpid;

        // flow common options
        flow_conf.channel_map[flow_id] |= get_vs_channel_mask(dev);
        flow_conf.eng_mode = true;

        // ip flow conf
        if (encap == VTSS_PHY_TS_ENCAP_ETH_IP_PTP) {
            ip_flow->flow_en = true;
            ip_flow->match_mode = ip_in->ip_match_mode; // mepa_ts_ip_match_select_t uses same order as vsc constants.
            if (ip_in->ip_ver == MEPA_TS_IP_VER_6) {
                memcpy(&ip_flow->ip_addr.ipv6.addr, &ip_in->ip_addr.ipv6.addr, sizeof(ip_flow->ip_addr.ipv6.addr));
                memcpy(&ip_flow->ip_addr.ipv6.mask, &ip_in->ip_addr.ipv6.mask, sizeof(ip_flow->ip_addr.ipv6.mask));
            } else {
                ip_flow->ip_addr.ipv4.addr = ip_in->ip_addr.ipv4.addr;
                ip_flow->ip_addr.ipv4.mask = ip_in->ip_addr.ipv4.mask;
            }
        }

        // ethernet flow conf
        eth_flow->flow_en = true;
        eth_flow->addr_match_mode = get_vs_addr_type(in_conf->eth_class_conf.mac_match_mode);
        eth_flow->addr_match_select = get_vs_mac_type(in_conf->eth_class_conf.mac_match_select);
        memcpy(eth_flow->mac_addr, eth_in->mac_addr, sizeof(eth_in->mac_addr));
        eth_flow->vlan_check = eth_in->vlan_check;
        eth_flow->num_tag = eth_in->vlan_conf.num_tag;
        eth_flow->tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
        if (eth->comm_opt.pbb_en && (eth_in->vlan_conf.outer_tag.mode == MEPA_TS_MATCH_MODE_RANGE ||
                                     eth_in->vlan_conf.inner_tag.mode == MEPA_TS_MATCH_MODE_RANGE)) {
            T_I(data, MEPA_TRACE_GRP_TS, " For pbb enabled case, tag range cannot be configured");
            return MEPA_RC_ERROR;
        }
        if (eth->comm_opt.pbb_en) {
            eth_flow->outer_tag_type = VTSS_PHY_TS_TAG_TYPE_B;
            eth_flow->inner_tag_type = VTSS_PHY_TS_TAG_TYPE_I;
        } else if (eth_flow->num_tag > 0) {
            eth_flow->outer_tag_type = eth->comm_opt.tpid ? VTSS_PHY_TS_TAG_TYPE_S : VTSS_PHY_TS_TAG_TYPE_C;
            eth_flow->inner_tag_type = eth->comm_opt.tpid ? VTSS_PHY_TS_TAG_TYPE_S : VTSS_PHY_TS_TAG_TYPE_C;
        }
        if (eth_in->vlan_conf.outer_tag.mode == MEPA_TS_MATCH_MODE_RANGE) {
            eth_flow->tag_range_mode = VTSS_PHY_TS_TAG_RANGE_OUTER;
            range_in = &eth_in->vlan_conf.outer_tag.match.range;
            eth_flow->outer_tag.range.upper = range_in->upper;
            eth_flow->outer_tag.range.lower = range_in->lower;
        } else {//MEPA_TS_MATCH_MODE_VALUE
            val_in = &eth_in->vlan_conf.outer_tag.match.value;
            eth_flow->outer_tag.value.val = val_in->val;
            eth_flow->outer_tag.value.mask = val_in->mask;
        }
        if (eth_in->vlan_conf.inner_tag.mode == MEPA_TS_MATCH_MODE_RANGE) {
            eth_flow->tag_range_mode = VTSS_PHY_TS_TAG_RANGE_INNER;
            range_in = &eth_in->vlan_conf.inner_tag.match.range;
            eth_flow->inner_tag.range.upper = range_in->upper;
            eth_flow->inner_tag.range.lower = range_in->lower;
        } else {//MEPA_TS_MATCH_MODE_VALUE
            val_in = &eth_in->vlan_conf.inner_tag.match.value;
            eth_flow->inner_tag.value.val = val_in->val;
            eth_flow->inner_tag.value.mask = val_in->mask;
        }
        dump_flow_conf(&flow_conf);
        if (vtss_phy_ts_egress_engine_conf_set(data->vtss_instance, data->port_no, eng_id, &flow_conf) != MESA_RC_OK) {
            T_I(data, MEPA_TRACE_GRP_TS, " Not able to set egress flow configuration for flow %d", flow_id);
            return MEPA_RC_ERR_TS_FLOW_CONF;
        }
        T_I(data, MEPA_TRACE_GRP_TS, " egress flow configuration done for flow %d", flow_id);
    }
    vtss_phy_ts_fifo_sig_set(data->vtss_instance, data->port_no, VTSS_PHY_TS_FIFO_SIG_MSG_TYPE | VTSS_PHY_TS_FIFO_SIG_DOMAIN_NUM |
                             VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID | VTSS_PHY_TS_FIFO_SIG_SEQ_ID);
    dump_chip_matching_flow(dev, false);
    T_I(data, MEPA_TRACE_GRP_TS, "exit");
    return MEPA_RC_OK;
}

static void vtss_phy_ts_fifo_read_cb(const vtss_inst_t              inst,
                                     const mesa_port_no_t           port_no,
                                     const vtss_phy_timestamp_t     *const fifo_ts,
                                     const vtss_phy_ts_fifo_sig_t   *const sig,
                                     void                           *cntxt,
                                     const vtss_phy_ts_fifo_status_t status)
{
    mepa_ts_fifo_sig_t mep_sig;
    mepa_timestamp_t ts;
    ts.seconds.high = fifo_ts->seconds.high;
    ts.seconds.low  = fifo_ts->seconds.low;
    ts.nanoseconds  = fifo_ts->nanoseconds;
    mep_sig.msg_type = sig->msg_type;
    mep_sig.domain_num = sig->domain_num;
    mep_sig.sequence_id = sig->sequence_id;
    memcpy(mep_sig.src_port_identity, sig->src_port_identity, sizeof(mep_sig.src_port_identity));
    mep_sig.has_crc_src = false;
    mep_sig.crc_src_port = 0;
    fifo_cb(port_no, &ts, &mep_sig, (mepa_ts_fifo_status_t)status);
}

void vtss_ts_fifo_read_install(struct mepa_device *dev,  mepa_ts_fifo_read_t rd_cb)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    fifo_cb = rd_cb ? rd_cb : fifo_cb; // Only one copy exists for all the vsc phy types
    vtss_phy_ts_fifo_read_install(data->vtss_instance, vtss_phy_ts_fifo_read_cb, NULL);
}

mepa_rc vtss_ts_fifo_empty(struct mepa_device *dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_phy_ts_fifo_empty(data->vtss_instance, data->port_no);
}

mepa_rc vtss_ts_fifo_get(struct mepa_device *dev, mepa_fifo_ts_entry_t ts_list[],
                         const size_t size, uint32_t *const num)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_ts_fifo_entry_t vtss_entry[MEPA_TS_FIFO_MAX_ENTRIES];
    int i;

    if (size < MEPA_TS_FIFO_MAX_ENTRIES) {
        T_E(data, MEPA_TRACE_GRP_TS, "Size of Input TS list is less than 8\n");
        return MEPA_RC_ERROR;
    }

    if (vtss_phy_ts_fifo_get(data->vtss_instance, data->port_no, vtss_entry, MEPA_TS_FIFO_MAX_ENTRIES, num) == VTSS_RC_OK) {
        for (i = 0; i < *num; i++) {
            ts_list[i].ts.seconds.high = vtss_entry[i].ts.seconds.high;
            ts_list[i].ts.seconds.low = vtss_entry[i].ts.seconds.low;
            ts_list[i].ts.nanoseconds = vtss_entry[i].ts.nanoseconds;
            ts_list[i].sig.msg_type = vtss_entry[i].sig.msg_type;
            ts_list[i].sig.domain_num = vtss_entry[i].sig.domain_num;
            memcpy(ts_list[i].sig.src_port_identity, vtss_entry[i].sig.src_port_identity, sizeof(ts_list[i].sig.src_port_identity));
            ts_list[i].sig.sequence_id = vtss_entry[i].sig.sequence_id;
            ts_list[i].sig.has_crc_src = false;
        }
    }
    return MEPA_RC_OK;
}

mepa_ts_driver_t vtss_ts_drivers = {
    .mepa_ts_init_conf_get          = vtss_ts_init_conf_get,
    .mepa_ts_init_conf_set          = vtss_ts_init_conf_set,
    .mepa_ts_mode_get               = vtss_ts_mode_get,
    .mepa_ts_mode_set               = vtss_ts_mode_set,
    .mepa_ts_ltc_ls_en              = vtss_ts_ltc_ls_en_set,
    .mepa_ts_ltc_get                = vtss_ts_ltc_get,
    .mepa_ts_ltc_set                = vtss_ts_ltc_set,
    .mepa_ts_clock_rateadj_get      = vtss_ts_clock_rateadj_get,
    .mepa_ts_clock_rateadj_set      = vtss_ts_clock_rateadj_set,
    .mepa_ts_clock_adj1ns           = vtss_ts_clock_adj1ns,
    .mepa_ts_delay_asymmetry_get    = vtss_ts_clock_delay_asymmetry_get,
    .mepa_ts_delay_asymmetry_set    = vtss_ts_clock_delay_asymmetry_set,
    .mepa_ts_path_delay_get         = vtss_ts_clock_path_delay_get,
    .mepa_ts_path_delay_set         = vtss_ts_clock_path_delay_set,
    .mepa_ts_egress_latency_get     = vtss_ts_clock_egress_latency_get,
    .mepa_ts_egress_latency_set     = vtss_ts_clock_egress_latency_set,
    .mepa_ts_ingress_latency_get    = vtss_ts_clock_ingress_latency_get,
    .mepa_ts_ingress_latency_set    = vtss_ts_clock_ingress_latency_set,
    .mepa_ts_rx_clock_conf_get      = phy_rx_clock_conf_get,
    .mepa_ts_tx_clock_conf_get      = phy_tx_clock_conf_get,
    .mepa_ts_rx_clock_conf_set      = vtss_ts_rx_clock_conf_set,
    .mepa_ts_tx_clock_conf_set      = vtss_ts_tx_clock_conf_set,
    .mepa_ts_pps_conf_get           = vtss_ts_pps_conf_get,
    .mepa_ts_pps_conf_set           = vtss_ts_pps_conf_set,
    .mepa_ts_stats_get              = vtss_ts_stats_get,
    .mepa_ts_event_get              = vtss_ts_event_get,
    .mepa_ts_event_set              = vtss_ts_event_set,
    .mepa_ts_event_poll             = vtss_ts_event_poll,
    .mepa_ts_rx_classifier_conf_set = phy_ts_rx_classifier_conf_set,
    .mepa_ts_tx_classifier_conf_set = phy_ts_tx_classifier_conf_set,
    .mepa_ts_rx_classifier_conf_get = phy_rx_classifier_conf_get,
    .mepa_ts_tx_classifier_conf_get = phy_tx_classifier_conf_get,
    .mepa_ts_fifo_read_install      = vtss_ts_fifo_read_install,
    .mepa_ts_fifo_empty             = vtss_ts_fifo_empty,
    .mepa_ts_fifo_get               = vtss_ts_fifo_get,
};
