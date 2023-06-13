// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>

#include "../../common/include/lan8814_registers.h"
#include "lan8814_ts_registers.h"
#include "lan8814_private.h"
#include <string.h>

static  uint16_t indy_ing_latencies[MEPA_TS_CLOCK_FREQ_MAX - 1][3] = {
    {  000, 0000, 00000 }, // 1000,100,10 speeds
    {  000, 0000, 00000 },
    {  417, 1441, 8380 },
    {  415, 1447, 8377 }, // 415 1447
};

static  uint16_t indy_egr_latencies[MEPA_TS_CLOCK_FREQ_MAX - 1][3] = {
    {  000, 0000, 00000 }, // 1000,100,100 speeds
    {  000, 0000, 00000 },
    {  189,  300, 11355 },
    {  186,  296, 11353 }, // 186 296
};

static uint16_t indy_twostep_egr_lat_adj[MEPA_TS_CLOCK_FREQ_MAX][4] = {
  //     10M,100M, 1G
    {0,    0,   0,  0},
    {0,    0,   0,  0},
    {0,11197,1125,120}, //200Mhz
    {0,11198,1120,115}, //250Mhz : 100mbps cannot be compensated due to defailt value less than compensated value.
    {0,    0,   0,  0},
};

static uint8_t def_mac[] = {0x01, 0x1B, 0x19, 0x00, 0x00, 0x00};

static mepa_rc indy_ltc_target_seconds(mepa_device_t *dev, uint32_t sec);

static void get_default_ts_eth_class(mepa_ts_classifier_eth_t *const conf)
{
    conf->mac_match_mode = MEPA_TS_ETH_ADDR_MATCH_ANY;
    conf->mac_match_select = MEPA_TS_ETH_MATCH_DEST_ADDR;
    memcpy(conf->mac_addr, def_mac, sizeof(conf->mac_addr));
    conf->vlan_check = FALSE;
    conf->vlan_conf.pbb_en = FALSE;
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
    conf->udp_sport_en = FALSE;
    conf->udp_dport_en = TRUE;
    conf->udp_sport = 0;
    conf->udp_dport = 319;
}
static void get_default_ts_ptp_class(mepa_ts_classifier_ptp_t *const conf)
{
    conf->version.upper = 2;
    conf->version.lower = 2;
    conf->minor_version.upper = 1;
    conf->minor_version.lower = 0;
    //domain
    conf->domain.mode = MEPA_TS_MATCH_MODE_VALUE;
    conf->domain.match.value.val = 0;
    conf->domain.match.value.mask = 0xF;
    //sdoid
    conf->sdoid.mode = MEPA_TS_MATCH_MODE_VALUE;
    conf->sdoid.match.value.val = 0;
    conf->sdoid.match.value.mask = 0; //not used for 1588-2008 standard
}
static void get_default_ts_clock_cfg(mepa_ts_ptp_clock_conf_t *clk_conf)
{
    clk_conf->clk_mode = MEPA_TS_PTP_CLOCK_MODE_NONE;
    clk_conf->delaym_type = MEPA_TS_PTP_DELAYM_E2E;
    clk_conf->enable = FALSE;
    get_default_ts_ptp_class(&clk_conf->ptp_class_conf);
}
static void get_default_ts_classifier_cfg(mepa_ts_classifier_t *const conf)
{
    conf->pkt_encap_type = MEPA_TS_ENCAP_NONE;
    conf->clock_id = 0;
    get_default_ts_eth_class(&conf->eth_class_conf);
    get_default_ts_ip_class(&conf->ip_class_conf);
}
static mepa_rc indy_tsu_block_init(mepa_device_t *dev, const mepa_ts_init_conf_t *ts_init_conf)
{
    uint16_t val = 0, clock_cfg = 0, pll_div = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (ts_init_conf->tx_fifo_mode != MEPA_TS_FIFO_MODE_NORMAL) {
        T_E(MEPA_TRACE_GRP_TS, "TX TS FIFO mode not supported::  Port : %d\n", data->port_no);
        return MEPA_RC_ERROR;
    }
    EP_RD(dev, INDY_PTP_REF_CLK_CFG, &clock_cfg);
    switch (ts_init_conf->clk_src) {
    case MEPA_TS_CLOCK_SRC_125MHZ_INTERNAL_SYS_PLL:
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(0);
        break;
    case MEPA_TS_CLOCK_SRC_125MHZ_QSGMII_REC_CLOCK:
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(1);
        break;
    case MEPA_TS_CLOCK_SRC_EXT_1588_REF_CLOCK:
        // take input from appl for exte_clk_freq; supported ext ref freq 10, 25, 125MHZ, default it is 125MHZ.
        // 1588 PLL Filter Range Register, if 10 change to 2, (25/125 -> 3 default )
        // write PLL Divider Register DIVR-> 1, DIVQ -> 8
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(2);
        break;
    case MEPA_TS_CLOCK_SRC_RESERVED:
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(3);
        break;
    case MEPA_TS_CLOCK_SRC_FROM_RX_PORT0:
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(4);
        break;
    case MEPA_TS_CLOCK_SRC_FROM_RX_PORT1:
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(5);
        break;
    case MEPA_TS_CLOCK_SRC_FROM_RX_PORT2:
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(6);
        break;
    case MEPA_TS_CLOCK_SRC_FROM_RX_PORT3:
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(7);
        break;
    default:
        T_E(MEPA_TRACE_GRP_TS, "Clock Source not supported::  Port : %d\n", data->port_no);
        return MEPA_RC_ERROR;
    }
    switch (ts_init_conf->clk_freq) {
    case MEPA_TS_CLOCK_FREQ_200M:
        // Write PLL Divider Register,  DIVF-> 32, DIVQ -> 8 for 200M
        pll_div = pll_div | INDY_1588_PLL_DIVQ_F(3);    // 3h = /8
        pll_div = pll_div | INDY_1588_PLL_DIVF_F(0x1F); //1Fh = /32
        pll_div = pll_div | INDY_1588_PLL_DIVR_F(4);
        EP_WRM(dev, INDY_1588_PLL_DIVEDER, pll_div, INDY_DEF_MASK);
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_PERIOD_F(5);
        break;
    case MEPA_TS_CLOCK_FREQ_250M:
        // / PLL Divider Register default values will be for 250M
        clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_PERIOD_F(4);
        break;
    default:
        T_E(MEPA_TRACE_GRP_TS, "Clock frequency not supported::  Port : %d\n", data->port_no);
        return MEPA_RC_ERROR;
        break;
    }
    clock_cfg = clock_cfg | INDY_PTP_REF_CLK_CFG_REF_CLK_PERIOD_OVERRIDE;
    EP_WRM(dev, INDY_PTP_REF_CLK_CFG, clock_cfg, INDY_DEF_MASK);
    val = val | INDY_PTP_OPERATING_MODE_VAL_F(1); // 1 for PTP in normal operating mode
    EP_WRM(dev, INDY_PTP_OPERATING_MODE, val, INDY_PTP_OPERATING_MODE_VAL);
    // Enable command control.
    val = INDY_PTP_CMD_CTL_ENABLE | INDY_PTP_CMD_CTL_LTC_TEMP_RATE_SEL;
    EP_WRM(dev, INDY_PTP_CMD_CTL, val, val);

    T_I(MEPA_TRACE_GRP_TS, "Port : %d  Clock Src : %d  Freq : %d Rx TS Len :%d Rx TS Pos : %d Tx FIFO Mode : %d Tx TS Len %d\n",
        data->port_no, ts_init_conf->clk_src, ts_init_conf->clk_freq, ts_init_conf->rx_ts_len,
        ts_init_conf->rx_ts_pos, ts_init_conf->tx_fifo_mode, ts_init_conf->tx_ts_len);

    return MEPA_RC_OK;

}

static mepa_rc indy_ts_port_init(mepa_device_t *dev, const mepa_ts_init_conf_t *ts_init_conf)
{
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (!data->ts_state.ts_init_done) {
        // Reset all timestamp fifos at initialisation.
        // Resetting tsu with 2-step config and reconfiguring it is disabling timestamping.
        EP_WR(dev, INDY_PTP_TSU_HARD_RESET, 0x1);
        MEPA_MSLEEP(2);
    }

    // common config which are configured in registers for base port.
    // But, must be stored in data structures for all ports.
    data->ts_state.clk_src             = ts_init_conf->clk_src;
    data->ts_state.clk_freq            = ts_init_conf->clk_freq;
    data->ts_state.tx_fifo_mode        = ts_init_conf->tx_fifo_mode;
    data->ts_state.tx_fifo_ts_len      = ts_init_conf->tx_ts_len;
    data->ts_state.tsu_op_mode         = INDY_TS_MODE_STANDALONE;
    // port specific config
    data->ts_state.rx_ts_len           = ts_init_conf->rx_ts_len;
    data->ts_state.rx_ts_pos           = ts_init_conf->rx_ts_pos;
    data->ts_state.tx_auto_followup_ts = ts_init_conf->tx_auto_followup_ts;
    data->ts_state.tc_op_mode          = ts_init_conf->tc_op_mode;

    if (ts_init_conf->tc_op_mode == MEPA_TS_TC_OP_MODE_B) {
        T_E(MEPA_TRACE_GRP_TS, "tc mode B not supported on Lan-8814");
    }

    if (ts_init_conf->rx_ts_pos == MEPA_TS_RX_TIMESTAMP_POS_AT_END) {
		val = val | INDY_PTP_RX_TAIL_TAG_EN; // Append the rx timestamp at the end of the packet
		val = val | INDY_PTP_RX_TAIL_TAG_INSERT_IFG_F(1);
		val = val | INDY_PTP_RX_TAIL_TAG_ER_FORWARD;
		EP_WRM(dev, INDY_PTP_RX_TAIL_TAG, val, INDY_DEF_MASK);
    }

    // initialise classifier config state with default values.
    get_default_ts_classifier_cfg(&data->ts_state.ts_port_conf.rx_pkt_conf);
    get_default_ts_classifier_cfg(&data->ts_state.ts_port_conf.tx_pkt_conf);
    // initialise clock config
    get_default_ts_clock_cfg(&data->ts_state.ts_port_conf.rx_clock_conf);
    get_default_ts_clock_cfg(&data->ts_state.ts_port_conf.tx_clock_conf);

#if 1 // Hardware default values are not aligned
    // Ingress latencies
    val = indy_ing_latencies[ts_init_conf->clk_freq][2];
    EP_WRM(dev, INDY_PTP_RX_LATENCY_10, val, INDY_DEF_MASK);
    data->ts_state.default_latencies.rx10mbps = val << 16;
    val = indy_ing_latencies[ts_init_conf->clk_freq][1];
    EP_WRM(dev, INDY_PTP_RX_LATENCY_100, val, INDY_DEF_MASK);
    data->ts_state.default_latencies.rx100mbps =  val << 16;
    val = indy_ing_latencies[ts_init_conf->clk_freq][0];
    EP_WRM(dev, INDY_PTP_RX_LATENCY_1000, val, INDY_DEF_MASK);
    data->ts_state.default_latencies.rx1000mbps =  val << 16;

    // Egress latencies
    val = indy_egr_latencies[ts_init_conf->clk_freq][2];
    EP_WRM(dev, INDY_PTP_TX_LATENCY_10, val, INDY_DEF_MASK);
    data->ts_state.default_latencies.tx10mbps =  val << 16;
    val = indy_egr_latencies[ts_init_conf->clk_freq][1];
    EP_WRM(dev, INDY_PTP_TX_LATENCY_100, val, INDY_DEF_MASK);
    data->ts_state.default_latencies.tx100mbps =  val << 16;
    val = indy_egr_latencies[ts_init_conf->clk_freq][0];
    EP_WRM(dev, INDY_PTP_TX_LATENCY_1000, val, INDY_DEF_MASK);
    data->ts_state.default_latencies.tx1000mbps =  val << 16;

#else

    // Read default latencies
    val = 0;
    EP_RD(dev, INDY_PTP_RX_LATENCY_10, &val);
    data->ts_state.default_latencies.rx10mbps = val << 16;
    val = 0;
    EP_RD(dev, INDY_PTP_RX_LATENCY_100, &val);
    data->ts_state.default_latencies.rx100mbps =  val << 16;
    val = 0;
    EP_RD(dev, INDY_PTP_RX_LATENCY_1000, &val);
    data->ts_state.default_latencies.rx1000mbps =  val << 16;
    val = 0;
    EP_RD(dev, INDY_PTP_TX_LATENCY_10, &val);
    data->ts_state.default_latencies.tx10mbps =  val << 16;
    val = 0;
    EP_RD(dev, INDY_PTP_TX_LATENCY_100, &val);
    data->ts_state.default_latencies.tx100mbps =  val << 16;
    val = 0;
    EP_RD(dev, INDY_PTP_TX_LATENCY_1000, &val);
    data->ts_state.default_latencies.tx1000mbps =  val << 16;

#endif

    data->ts_state.ts_init_done = TRUE;
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_init_conf_set(mepa_device_t *dev, const mepa_ts_init_conf_t *const ts_init_conf)
{
    uint16_t val = 0;
    mepa_device_t *base_dev;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_ASSERT(ts_init_conf == NULL);
    base_dev = data->base_dev;
    if (base_dev == dev) {
        MEPA_ASSERT(base_dev == NULL);

        MEPA_ENTER(base_dev);
        // Reset the LTC
        val = val | INDY_PTP_LTC_HARD_RESET_CMD;
        EP_WRM(base_dev, INDY_PTP_LTC_HARD_RESET, val, INDY_DEF_MASK);
        if ((rc = indy_tsu_block_init(base_dev, ts_init_conf)) != MEPA_RC_OK) {
            MEPA_EXIT(base_dev);
            return rc;
        }
        MEPA_EXIT(base_dev);
    }

    MEPA_ENTER(dev);
    rc = indy_ts_port_init(dev, ts_init_conf);
    MEPA_EXIT(dev);

    return rc;
}
static mepa_rc indy_ts_init_conf_get(mepa_device_t *dev, mepa_ts_init_conf_t *const ts_init_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(ts_init_conf == NULL);
    MEPA_ENTER(dev);
    ts_init_conf->clk_src           = data->ts_state.clk_src;
    ts_init_conf->clk_freq          = data->ts_state.clk_freq;
    ts_init_conf->rx_ts_len         = data->ts_state.rx_ts_len;
    ts_init_conf->rx_ts_pos         = data->ts_state.rx_ts_pos;
    ts_init_conf->tx_fifo_mode      = data->ts_state.tx_fifo_mode;
    ts_init_conf->tx_fifo_spi_conf  = data->ts_state.tx_spi_en;
    ts_init_conf->tx_ts_len         = data->ts_state.tx_fifo_ts_len;
    ts_init_conf->auto_clear_ls     = FALSE;
    ts_init_conf->tc_op_mode        = data->ts_state.tc_op_mode;
    ts_init_conf->dly_req_recv_10byte_ts = FALSE;
    ts_init_conf->tx_auto_followup_ts = data->ts_state.tx_auto_followup_ts;
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_mode_set(mepa_device_t *dev, const mepa_bool_t enable)
{
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    val = enable ? INDY_PTP_TSU_GEN_CONF_EN : 0;
    EP_WRM(dev, INDY_PTP_TSU_GEN_CONF, val, INDY_PTP_TSU_GEN_CONF_EN);

    data->ts_state.ptp_en = enable;
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_reset(mepa_device_t *dev, const mepa_ts_reset_conf_t *const tsreset)
{

    MEPA_ENTER(dev);
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_mode_get(mepa_device_t *dev, mepa_bool_t *const enable)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    *enable = data->ts_state.ptp_en;

    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

#if 0

static mepa_rc indy_ts_ltc_ls_en_set2(mepa_device_t *dev, const mepa_ts_ls_type_t  ls_type)
{
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    mepa_bool_t     ls_pps = TRUE;

    MEPA_ASSERT(base_dev == NULL );
    MEPA_ENTER(dev);
    EP_WRM(dev, INDY_PTP_LTC_EXT_ADJ_CFG, 0, INDY_DEF_MASK);
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

#endif

static mepa_rc indy_ts_ltc_ls_en_set(mepa_device_t *dev, const mepa_ts_ls_type_t  ls_type)
{
    uint16_t val = 0, gpio = 3; // Remove the hardcoded GPIO#3 and take it as input;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    mepa_bool_t     ls_pps = TRUE;

    MEPA_ASSERT(base_dev == NULL );
    MEPA_ENTER(dev);
    if (base_dev == dev) {
        switch (ls_type) {
        case MEPA_TS_CMD_LOAD:
            if (ls_pps == TRUE) {
                EP_WRM(base_dev, INDY_PTP_LTC_EXT_ADJ_CFG, 0, INDY_DEF_MASK);
            } else {
                EP_WRM(base_dev, INDY_PTP_CMD_CTL, INDY_PTP_CMD_CTL_LTC_LOAD, INDY_PTP_CMD_CTL_LTC_LOAD);
            }
            break;
        case MEPA_TS_CMD_SAVE:
            if (ls_pps == TRUE) {
                EP_WRM(base_dev, INDY_PTP_GPIO_CAP_MAP_LO, INDY_PTP_GPIO_CAP_0_MAP_F(gpio), INDY_PTP_GPIO_CAP_0_MAP);
                // LTC captured on Channel#0 and on Raising edge. As of now these options are fixed.
                EP_WRM(base_dev, INDY_PTP_GPIO_CAP_EN, INDY_PTP_GPIO_RE_CAPTURE_EN_F(1), INDY_PTP_GPIO_RE_CAPTURE_EN);
                EP_WRM(base_dev, INDY_PTP_GPIO_CAP_LOCK, val, INDY_DEF_MASK);
            } else {
                EP_WRM(base_dev, INDY_PTP_CMD_CTL, INDY_PTP_CMD_CTL_LTC_READ, INDY_PTP_CMD_CTL_LTC_READ);
            }
            break;
        case MEPA_TS_ADJ_CMD_CLEAR:
            EP_WRM(base_dev, INDY_PTP_LTC_EXT_ADJ_CFG, 0, INDY_DEF_MASK);
            break;
        default:
            break;
        }
    }
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}


//Since EP_RD_INCR macro is used in below API, it must be ensured that API must be executed without interruption
//till its end. No other API should access Lan8814 registers as it may interfere with register addresses.
static mepa_rc indy_ts_ltc_get(mepa_device_t *dev, mepa_timestamp_t *const ts)
{
    uint16_t val = 0, ns_h = 0, ns_l = 0;;
    mepa_bool_t     ls_pps = TRUE;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;

    MEPA_ASSERT((ts == NULL) || (base_dev == NULL) );
    MEPA_ENTER(dev);
    if (base_dev == dev) {
        if (ls_pps == FALSE) {
            EP_WRM(base_dev, INDY_PTP_CMD_CTL, INDY_PTP_CMD_CTL_LTC_READ, INDY_PTP_CMD_CTL_LTC_READ);
            ts->seconds.high = 0;
            ts->seconds.low = 0;
            ts->nanoseconds = 0;
            // Read LTC
            EP_RD_INCR(base_dev, INDY_PTP_LTC_RD_SEC_HI, &val, TRUE);
            ts->seconds.high = val;
            val = 0;
            EP_RD_INCR(base_dev, INDY_PTP_LTC_RD_SEC_MID, &val, FALSE);
            ts->seconds.low = val;
            ts->seconds.low = ts->seconds.low << 16;
            val = 0;
            EP_RD_INCR(base_dev, INDY_PTP_LTC_RD_SEC_LO, &val, FALSE);
            ts->seconds.low = ts->seconds.low | val;
            EP_RD_INCR(base_dev, INDY_PTP_LTC_RD_NS_HI, &ns_h, FALSE);
            ts->nanoseconds = ns_h;
            ts->nanoseconds = ts->nanoseconds << 16;
            EP_RD_INCR(base_dev, INDY_PTP_LTC_RD_NS_LO, &ns_l, FALSE);
            ts->nanoseconds = ts->nanoseconds | ns_l;
            EP_RD_INCR(base_dev, INDY_PTP_LTC_RD_SUBNS_HI, &val, FALSE);
            EP_RD_INCR(base_dev, INDY_PTP_LTC_RD_SUBNS_LO, &val, FALSE);
        } else {

            ts->seconds.high = 0;
            ts->seconds.low = 0;
            ts->nanoseconds = 0;
            val = 0;
            ns_l = 0;
            ns_h = 0;
            EP_RD_INCR(base_dev, INDY_PTP_GPIO_RE_CLOCK_SEC_HI, &val, TRUE);
            ts->seconds.low = val;
            ts->seconds.low = ts->seconds.low << 16;
            val = 0;
            EP_RD_INCR(base_dev, INDY_PTP_GPIO_RE_CLOCK_SEC_LO, &val, FALSE);
            ts->seconds.low = ts->seconds.low | val;
            EP_RD_INCR(base_dev, INDY_PTP_GPIO_RE_CLOCK_NS_HI, &ns_h, FALSE);
            ts->nanoseconds = ns_h & 0x3FFF;
            ts->nanoseconds = ts->nanoseconds << 16;
            EP_RD_INCR(base_dev, INDY_PTP_GPIO_RE_CLOCK_NS_LO, &ns_l, FALSE);
            ts->nanoseconds = ts->nanoseconds | ns_l;
        }
    }
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_ltc_set(mepa_device_t *dev, const mepa_timestamp_t *const ts)
{
    uint16_t val = 0, cmd = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    phy_data_t *base_data = (phy_data_t *)base_dev->data;

    MEPA_ASSERT((ts == NULL) || (base_dev == NULL) );
    MEPA_ENTER(dev);

    if (base_dev == dev) {
        EP_RD(base_dev, INDY_PTP_LTC_EXT_ADJ_CFG, &cmd);
        if (cmd & 0x10) {
            cmd = 0;
        } else {
            cmd = cmd | INDY_PTP_LTC_EXT_ADJ_MODE;
        }
        EP_WRM(base_dev, INDY_PTP_LTC_EXT_ADJ_CFG, cmd, INDY_DEF_MASK);

        val = ts->seconds.high;
        EP_WRM(base_dev, INDY_PTP_LTC_SET_SEC_HI, val, INDY_DEF_MASK);
        val = (ts->seconds.low >> 16) & 0xFFFF;
        EP_WRM(base_dev, INDY_PTP_LTC_SET_SEC_MID, val, INDY_DEF_MASK);
        val = ts->seconds.low & 0xFFFF;
        EP_WRM(base_dev, INDY_PTP_LTC_SET_SEC_LO, val, INDY_DEF_MASK);
        val = (ts->nanoseconds >> 16) & 0xFFFF;
        EP_WRM(base_dev, INDY_PTP_LTC_SET_NS_HI, val, INDY_DEF_MASK);
        val = ts->nanoseconds & 0xFFFF;
        EP_WRM(base_dev, INDY_PTP_LTC_SET_NS_LO, val, INDY_DEF_MASK);
        EP_WRM(base_dev, INDY_PTP_LTC_EXT_ADJ_CFG, INDY_PTP_LTC_EXT_ADJ_LOAD_EN, INDY_PTP_LTC_EXT_ADJ_LOAD_EN);

        if (base_data->ts_state.pps.pps_output_enable) {
            // Reload the ltc targets
            indy_ltc_target_seconds(dev, ts->seconds.low + 2);
        }
    }

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_rateadj_get(mepa_device_t *dev, mepa_ts_scaled_ppb_t *const adj)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(adj == NULL);
    MEPA_ENTER(dev);

    *adj = data->ts_state.ts_port_conf.rate_adj;

    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_rateadj_set(mepa_device_t *dev, const mepa_ts_scaled_ppb_t *const adj)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t val = 0;
    mepa_device_t *base_dev = data->base_dev;
    MEPA_ASSERT(adj == NULL);
    MEPA_ENTER(dev);
    if ((base_dev == dev) && (adj != 0)) {
        int16_t adj_dir = (*adj > 0 ? 1 : 0);
        int64_t adj_abs = MEPA_LABS(*adj), adj_val = 0, adj_abs1 = 0;
        adj_abs1 = adj_abs;
        adj_abs1 = adj_abs1 >> 16;

        if ( adj_abs > 0) {
            adj_val = MEPA_DIV64(1000000000ULL * 0x10000ULL, adj_abs);
            adj_val = MEPA_DIV64((1LL << 32) * 4,  adj_val);
        }
        if (adj_abs >= (1LL << 30)) {
            T_W(MEPA_TRACE_GRP_TS, "High Rate Adjust value  :: direction %d Adj Value : %lld   Port : %d\n", adj_dir, adj_abs, data->port_no);
        } else {
            if (adj_dir) {
                val = val | INDY_PTP_LTC_RATE_ADJ_HI_DIR;
            }
            val = val | (0x3FFF & (adj_val >> 16));
            EP_WRM(dev, INDY_PTP_LTC_RATE_ADJ_HI, val, INDY_DEF_MASK);
            val = 0;
            val = (0xFFFF & (adj_val));
            EP_WRM(dev, INDY_PTP_LTC_RATE_ADJ_LO, val, INDY_DEF_MASK);
            data->ts_state.ts_port_conf.rate_adj = *adj;
        }
        T_I(MEPA_TRACE_GRP_TS, "Rate Adjust :: direction %d Adj Value : %d   Port : %d\n", adj_dir, (0x3FFFFFFF & adj_val), data->port_no);
    }
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_adj1ns(mepa_device_t *dev, const mepa_bool_t incr)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    phy_data_t *base_data;
    uint16_t val = 0, cmd = 0, cmd_org = 0, adj = 0;
    MEPA_ENTER(dev);
    if (base_dev == dev) {
        base_data = (phy_data_t *)base_dev->data;
        EP_RD(dev, INDY_PTP_CMD_CTL, &cmd_org);
        cmd = 0xFFFB & cmd_org;
        EP_WRM(dev, INDY_PTP_CMD_CTL, cmd, INDY_DEF_MASK);
        val = val | INDY_PTP_LTC_STEP_ADJ_DIR;

        switch (base_data->ts_state.clk_freq) {
        case MEPA_TS_CLOCK_FREQ_250M:
            if (incr) {
                adj = 4 + 1;
            } else {
                adj = 4 - 1;
            }
            break;
        case MEPA_TS_CLOCK_FREQ_200M:
            if (incr) {
                adj = 5 + 1;
            } else {
                adj = 5 - 1;
            }
            break;
        default:
            break;
        }
        EP_WRM(dev, INDY_PTP_LTC_STEP_ADJ_HI, val, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_LTC_STEP_ADJ_LO, adj, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_CMD_CTL, INDY_PTP_CMD_CTL_LTC_STEP_NANOSECONDS, INDY_PTP_CMD_CTL_LTC_STEP_NANOSECONDS);
        EP_WRM(dev, INDY_PTP_CMD_CTL, cmd_org, INDY_DEF_MASK);
    }
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

#if 0
static mepa_rc indy_ts_clock_adjns(mepa_device_t *dev, const mepa_bool_t incr)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    phy_data_t *base_data;
    mepa_port_no_t port_no;
    uint16_t val = 0, cmd = 0, cmd_org = 0, adj = 0;

    MEPA_ENTER(dev);
    if (base_dev == dev) {
        base_data = (phy_data_t *)base_dev->data;
        EP_RD(dev, INDY_PTP_CMD_CTL, &cmd_org);
        cmd = 0xFFFB & cmd_org;
        cmd = cmd | INDY_PTP_CMD_CTL_LTC_STEP_NANOSECONDS;
        EP_WRM(dev, INDY_PTP_CMD_CTL, cmd, INDY_DEF_MASK);
        switch (base_data->ts_state.clk_freq) {
        case MEPA_TS_CLOCK_FREQ_250M:
            if (incr) {
                adj = 4 + 1;
            } else {
                adj = 4 - 1;
            }
            break;
        case MEPA_TS_CLOCK_FREQ_200M:
            if (incr) {
                adj = 5 + 1;
            } else {
                adj = 5 - 1;
            }
            break;
        }
        EP_WRM(dev, INDY_PTP_LTC_STEP_ADJ_HI, val, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_LTC_STEP_ADJ_LO, adj, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_CMD_CTL, cmd_org, INDY_DEF_MASK);
    }
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}
#endif

static mepa_rc indy_ts_clock_delay_asymmetry_get(mepa_device_t *dev, mepa_timeinterval_t *const delay_asym)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    *delay_asym = data->ts_state.ts_port_conf.delay_asym;
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_delay_asymmetry_set(mepa_device_t *dev, const mepa_timeinterval_t *const delay_asym)
{
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    val = (*delay_asym >> 32) & 0xFFFF;
    EP_WRM(dev, INDY_PTP_ASYM_DLY_HI, val, INDY_DEF_MASK);
    val = (*delay_asym >> 16) & 0xFFFF;
    EP_WRM(dev, INDY_PTP_ASYM_DLY_LO, val, INDY_DEF_MASK);
    data->ts_state.ts_port_conf.delay_asym = *delay_asym;
    T_I(MEPA_TRACE_GRP_TS, "Port No : %d   Delay Asymmetry :: %d \n", data->port_no, *delay_asym);
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_path_delay_get(mepa_device_t *dev, mepa_timeinterval_t *const path_delay)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    indy_ts_data_t *ts_data;

    MEPA_ASSERT(path_delay == NULL);
    MEPA_ENTER(dev);
    ts_data = &data->ts_state;
    *path_delay = ts_data->ts_port_conf.path_delay;
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_path_delay_set(mepa_device_t *dev, const mepa_timeinterval_t *const path_delay)
{
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    indy_ts_data_t *ts_data;

    MEPA_ASSERT(path_delay == NULL);
    MEPA_ENTER(dev);
    ts_data = &data->ts_state;
    val =  (*path_delay >> 32) & 0xFFFF;
    EP_WRM(dev, INDY_PTP_PEERDLY_HI, val, INDY_DEF_MASK);
    val =  (*path_delay >> 16) & 0xFFFF;
    EP_WRM(dev, INDY_PTP_PEERDLY_LO, val, INDY_DEF_MASK);
    T_I(MEPA_TRACE_GRP_TS, "Port No : %d   Path Delay  :: %d \n", data->port_no, *path_delay);
    ts_data->ts_port_conf.path_delay = *path_delay;

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_egress_latency_get(mepa_device_t *dev, mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(latency == NULL);
    MEPA_ENTER(dev);
    switch (data->conf.speed) {
    case MEPA_SPEED_10M:
        *latency = data->ts_state.ts_port_conf.port_latencies.tx10mbps ;
        break;
    case MEPA_SPEED_100M:
        *latency = data->ts_state.ts_port_conf.port_latencies.tx100mbps;
        break;
    case MEPA_SPEED_1G:
    case MEPA_SPEED_AUTO:
        *latency = data->ts_state.ts_port_conf.port_latencies.tx1000mbps;
        break;
    default:
        break;
    }
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

// Latencies are different for 1-step and 2-step clock. New adjustments must consider it using two_step flag input.
static mepa_rc indy_ts_clock_egress_latency_set_priv(mepa_device_t *dev, const mepa_timeinterval_t *const input_latency, mepa_bool_t two_step)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    phy_data_t *base_data = (phy_data_t *)base_dev->data;
    uint16_t val = 0;
    mepa_timeinterval_t latency;

    switch (data->conf.speed) {
        case MEPA_SPEED_10M:
            latency = base_data->ts_state.default_latencies.tx10mbps;
            if (two_step) {
                latency -= indy_twostep_egr_lat_adj[base_data->ts_state.clk_freq][MEPA_SPEED_10M] << 16; //two_step adjustment
            }
            latency += *input_latency;
            if (latency >= 0) {
                val = (uint16_t)(latency >> 16); //timeinterval to nano-sec conversion.
            } else {
                T_I(MEPA_TRACE_GRP_TS, "Port No : %d   Bad Egress Latency Values :: %lld \n", data->port_no, *input_latency);
                break;
            }
            EP_WR(dev, INDY_PTP_TX_LATENCY_10, val);
            data->ts_state.ts_port_conf.port_latencies.tx10mbps = *input_latency;
            break;

        case MEPA_SPEED_100M:
            latency = base_data->ts_state.default_latencies.tx100mbps;
            if (two_step) {
                latency -= indy_twostep_egr_lat_adj[base_data->ts_state.clk_freq][MEPA_SPEED_100M] << 16; //two_step adjustment
            }
            latency += *input_latency;
            if (latency >= 0) {
                val = (uint16_t)(latency >> 16); //timeinterval to nano-sec conversion.
            } else {
                T_I(MEPA_TRACE_GRP_TS, "Port No : %d   Bad Egress Latency Values :: %lld \n", data->port_no, *input_latency);
                break;
            }
            EP_WR(dev, INDY_PTP_TX_LATENCY_100, val);
            data->ts_state.ts_port_conf.port_latencies.tx100mbps = *input_latency;
            break;

        case MEPA_SPEED_1G:
        case MEPA_SPEED_AUTO:
            latency = base_data->ts_state.default_latencies.tx1000mbps;
            if (two_step) {
                latency -= indy_twostep_egr_lat_adj[base_data->ts_state.clk_freq][MEPA_SPEED_1G] << 16; //two_step adjustment
            }
            latency += *input_latency;
            if (latency >= 0) {
                val = (uint16_t)(latency >> 16); //timeinterval to nano-sec conversion.
            } else {
                T_I(MEPA_TRACE_GRP_TS, "Port No : %d   Bad Egress Latency Values :: %lld \n", data->port_no, *input_latency);
                break;
            }
            EP_WRM(dev, INDY_PTP_TX_LATENCY_1000, val, INDY_DEF_MASK);
            data->ts_state.ts_port_conf.port_latencies.tx1000mbps = *input_latency;
            break;

        default:
            T_I(MEPA_TRACE_GRP_TS, "Lan8814 phy allows latency configuration for 10/100/1000Mbps only");
            break;
    }

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_egress_latency_set(mepa_device_t *dev, const mepa_timeinterval_t *const latency)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data         = (phy_data_t *)dev->data;
    mepa_bool_t two_step_lat = FALSE;
    mepa_ts_ptp_clock_conf_t *ptpclock_conf;

    MEPA_ASSERT(latency == NULL);
    MEPA_ENTER(dev);
    ptpclock_conf = &data->ts_state.ts_port_conf.tx_clock_conf;
    if (ptpclock_conf->enable && (ptpclock_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP ||
                ptpclock_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP)) {
        two_step_lat = TRUE;
    }
    rc = indy_ts_clock_egress_latency_set_priv(dev, latency, two_step_lat);
    MEPA_EXIT(dev);
    return rc;
}

// Before enabling clock configuration every time, this function need to be called so that
// any differences in latencies based on 1-step or 2-step clock are compensated on Tx side.
// latencies are stored or configured in units of mepa_timeinterval_t which is obtained from
// nanoseconds using (nanoseconds << 16). Additional details can be found in mepa/include/microchip/ethernet/phy/api/phy_ts.h.
mepa_rc indy_ts_reload_egress_latency(mepa_device_t *dev, mepa_bool_t two_step)
{
    phy_data_t    *data      = (phy_data_t *)dev->data;
    mepa_device_t *base_dev  = data->base_dev;
    phy_data_t    *base_data = (phy_data_t *)base_dev->data;
    mepa_timeinterval_t latency;
    uint16_t val;

    // 10m speed
    latency = base_data->ts_state.default_latencies.tx10mbps;
    if (two_step) {
        latency -= indy_twostep_egr_lat_adj[base_data->ts_state.clk_freq][MEPA_SPEED_10M] << 16; //two_step adjustment
    }
    latency += data->ts_state.ts_port_conf.port_latencies.tx10mbps; // user configured latency.
    val = (uint16_t)(latency > 0 ? latency >> 16 : 0); // latencies cannot be -ve.
    EP_WR(dev, INDY_PTP_TX_LATENCY_10, val);

    // 100m speed
    latency = base_data->ts_state.default_latencies.tx100mbps;
    if (two_step) {
        latency -= indy_twostep_egr_lat_adj[base_data->ts_state.clk_freq][MEPA_SPEED_100M] << 16; //two_step adjustment
    }
    latency += data->ts_state.ts_port_conf.port_latencies.tx100mbps; // user configured latency.
    val = (uint16_t)(latency > 0 ? latency >> 16 : 0); // latencies cannot be -ve.
    EP_WR(dev, INDY_PTP_TX_LATENCY_100, val);

    // 1000m speed
    latency = base_data->ts_state.default_latencies.tx1000mbps;
    if (two_step) {
        latency -= indy_twostep_egr_lat_adj[base_data->ts_state.clk_freq][MEPA_SPEED_1G] << 16; //two_step adjustment
    }
    latency += data->ts_state.ts_port_conf.port_latencies.tx1000mbps; // user configured latency.
    val = (uint16_t)(latency > 0 ? latency >> 16 : 0); // latencies cannot be -ve.
    EP_WR(dev, INDY_PTP_TX_LATENCY_1000, val);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_ingress_latency_get(mepa_device_t *dev, mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(latency == NULL);
    MEPA_ENTER(dev);
    switch (data->conf.speed) {
    case MEPA_SPEED_10M:
        *latency = data->ts_state.ts_port_conf.port_latencies.rx10mbps;
        break;
    case MEPA_SPEED_100M:
        *latency = data->ts_state.ts_port_conf.port_latencies.rx100mbps;
        break;
    case MEPA_SPEED_1G:
    case MEPA_SPEED_AUTO:
        *latency = data->ts_state.ts_port_conf.port_latencies.rx1000mbps;
        break;
    default:
        break;
    }
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_clock_ingress_latency_set(mepa_device_t *dev, const mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    phy_data_t *base_phy;
    uint16_t val = 0;

    MEPA_ASSERT(latency == NULL);
    MEPA_ENTER(dev);
    base_phy = (phy_data_t *)base_dev->data;

    val = (MEPA_LABS(*latency) >> 16) & 0xFFFF;
    switch (data->conf.speed) {
    case MEPA_SPEED_10M:
        if (*latency >= 0) {
            val = (uint16_t)((base_phy->ts_state.default_latencies.rx10mbps >> 16) & 0xFFFF) + val;
        } else {
            if ((base_phy->ts_state.default_latencies.rx100mbps >> 16) <= val) {
                T_I(MEPA_TRACE_GRP_TS, "Port No : %d   Bad Ingress Latency Values :: %lld \n", data->port_no, *latency);
                break;
            }
            val = (uint16_t)((base_phy->ts_state.default_latencies.rx10mbps >> 16) & 0xFFFF) - val;
        }
        EP_WRM(dev, INDY_PTP_RX_LATENCY_10, val, INDY_DEF_MASK);
        data->ts_state.ts_port_conf.port_latencies.rx10mbps = *latency;
        break;
    case MEPA_SPEED_100M:
        if (*latency >= 0) {
            val = (uint16_t)((base_phy->ts_state.default_latencies.rx100mbps >> 16) & 0xFFFF) + val;
        } else {
            if ((base_phy->ts_state.default_latencies.rx100mbps >> 16) <= val) {
                T_I(MEPA_TRACE_GRP_TS, "Port No : %d   Bad Ingress Latency Values :: %lld \n", data->port_no, *latency);
                break;
            }
            val = (uint16_t)((base_phy->ts_state.default_latencies.rx100mbps >> 16) & 0xFFFF) - val;
        }
        EP_WRM(dev, INDY_PTP_RX_LATENCY_100, val, INDY_DEF_MASK);
        data->ts_state.ts_port_conf.port_latencies.rx100mbps = *latency;
        break;
    case MEPA_SPEED_1G:
    case MEPA_SPEED_AUTO:
        if (*latency >= 0) {
            val = (uint16_t)((base_phy->ts_state.default_latencies.rx1000mbps >> 16) & 0xFFFF) + val;
        } else {
            if ((base_phy->ts_state.default_latencies.rx1000mbps >> 16) <= val) {
                T_I(MEPA_TRACE_GRP_TS, "Port No : %d   Bad Ingress Latency Values :: %lld \n", data->port_no, *latency);
                break;
            }
            val = (uint16_t)((base_phy->ts_state.default_latencies.rx1000mbps >> 16) & 0xFFFF) - val;
        }
        EP_WRM(dev, INDY_PTP_RX_LATENCY_1000, val, INDY_DEF_MASK);
        data->ts_state.ts_port_conf.port_latencies.rx1000mbps = *latency;
        break;
    default:
        break;
    }
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_rx_classifier_conf_get (mepa_device_t *dev, uint16_t flow_index, mepa_ts_classifier_t *const pkt_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(pkt_conf == NULL);

    MEPA_ENTER(dev);
    memcpy(pkt_conf, &data->ts_state.ts_port_conf.rx_pkt_conf, sizeof(mepa_ts_classifier_t));
    MEPA_EXIT(dev);

    return MEPA_RC_OK;

}

static void indy_ts_deb_pr_reg (mepa_device_t *dev,
                                const mepa_debug_print_t pr,
                                const char *str, uint16_t page, uint16_t addr, uint16_t *value)
{
    if(pr != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;
        mepa_port_no_t port_no = data->port_no;
        if(MEPA_RC_OK == indy_ext_reg_rd(dev, page, addr, value)) {
            pr("%-45s:  0x%02x  0x%02x   0x%04x     0x%08x\n", str, to_u32(port_no), page, addr, *value);
        }
    }
}

static mepa_rc indy_ts_classifier_conf_reg_dump(mepa_device_t *dev,
                                                const mepa_debug_print_t pr)
{
    uint16_t val = 0;

    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_MAC_HI", INDY_PTP_RX_USER_MAC_HI, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_MAC_MID", INDY_PTP_RX_USER_MAC_MID, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_MAC_LO", INDY_PTP_RX_USER_MAC_LO, &val);

    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_ADDR_0", INDY_PTP_RX_USER_IP_ADDR_0, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_ADDR_1", INDY_PTP_RX_USER_IP_ADDR_1, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_ADDR_2", INDY_PTP_RX_USER_IP_ADDR_2, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_ADDR_3", INDY_PTP_RX_USER_IP_ADDR_3, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_ADDR_4", INDY_PTP_RX_USER_IP_ADDR_4, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_ADDR_5", INDY_PTP_RX_USER_IP_ADDR_5, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_ADDR_6", INDY_PTP_RX_USER_IP_ADDR_6, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_ADDR_7", INDY_PTP_RX_USER_IP_ADDR_7, &val);

    //PTP User IP Mask Registers
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_MASK_0", INDY_PTP_RX_USER_IP_MASK_0, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_MASK_1", INDY_PTP_RX_USER_IP_MASK_1, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_MASK_2", INDY_PTP_RX_USER_IP_MASK_2, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_MASK_3", INDY_PTP_RX_USER_IP_MASK_3, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_MASK_4", INDY_PTP_RX_USER_IP_MASK_4, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_MASK_5", INDY_PTP_RX_USER_IP_MASK_5, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_MASK_6", INDY_PTP_RX_USER_IP_MASK_6, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_USER_IP_MASK_7", INDY_PTP_RX_USER_IP_MASK_7, &val);

    // VLAN Registers for both ingress and Egress
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_VLAN_TYPE_ID", INDY_PTP_VLAN_ETH_TYPE_ID, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_VLAN1_TYPE_ID", INDY_VLAN1_TYPE_ID, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_VLAN1_ID_MASK", INDY_VLAN1_ID_MASK, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_VLAN1_VID_RANGE_UP", INDY_VLAN1_VID_RANGE_UP, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_VLAN1_VID_RANGE_LO", INDY_VLAN1_VID_RANGE_LO, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_VLAN2_TYPE_ID", INDY_VLAN2_TYPE_ID, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_VLAN2_ID_MASK", INDY_VLAN2_ID_MASK, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_VLAN2_VID_RANGE_UP", INDY_VLAN2_VID_RANGE_UP, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_VLAN2_VID_RANGE_LO", INDY_VLAN2_VID_RANGE_LO, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_LLC_TYPE_ID", INDY_LLC_TYPE_ID, &val);

    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_CAP_INFO", INDY_PTP_CAP_INFO, &val);
    //PTP TX USER MAC ADDRESS
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_MAC_HI", INDY_PTP_TX_USER_MAC_HI, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_MAC_MID", INDY_PTP_TX_USER_MAC_MID, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_MAC_LO", INDY_PTP_TX_USER_MAC_LO, &val);
    //PTP TX USER IP ADDRESS REGISTERS
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_ADDR_0", INDY_PTP_TX_USER_IP_ADDR_0, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_ADDR_1", INDY_PTP_TX_USER_IP_ADDR_1, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_ADDR_2", INDY_PTP_TX_USER_IP_ADDR_2, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_ADDR_3", INDY_PTP_TX_USER_IP_ADDR_3, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_ADDR_4", INDY_PTP_TX_USER_IP_ADDR_4, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_ADDR_5", INDY_PTP_TX_USER_IP_ADDR_5, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_ADDR_6", INDY_PTP_TX_USER_IP_ADDR_6, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_ADDR_7", INDY_PTP_TX_USER_IP_ADDR_7, &val);
    //PTP TX USER IP MASK REGISTERS
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_MASK_0", INDY_PTP_TX_USER_IP_MASK_0, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_MASK_1", INDY_PTP_TX_USER_IP_MASK_1, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_MASK_2", INDY_PTP_TX_USER_IP_MASK_2, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_MASK_3", INDY_PTP_TX_USER_IP_MASK_3, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_MASK_4", INDY_PTP_TX_USER_IP_MASK_4, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_MASK_5", INDY_PTP_TX_USER_IP_MASK_5, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_MASK_6", INDY_PTP_TX_USER_IP_MASK_6, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_USER_IP_MASK_7", INDY_PTP_TX_USER_IP_MASK_7, &val);
    //PTP RX Parsing Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_PARSE_CONFIG", INDY_PTP_RX_PARSE_CONFIG, &val);
    //PTP RX Parsing VLAN Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_PARSE_VLAN_CONFIG", INDY_PTP_RX_PARSE_VLAN_CONFIG, &val);
    //PTP RX Parsing Layer2 Format Address Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_PARSE_L2_ADDR_EN", INDY_PTP_RX_PARSE_L2_ADDR_EN, &val);
    //PTP RX Parsing IP Format Address Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_PARSE_IP_ADDR_EN", INDY_PTP_RX_PARSE_IP_ADDR_EN, &val);
    //PTP RX Parsing UDP Source Port Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_PARSE_UDP_SRC_PORT", INDY_PTP_RX_PARSE_UDP_SRC_PORT, &val);
    //PTP RX Parsing UDP Destination Port Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_PARSE_UDP_DEST_PORT", INDY_PTP_RX_PARSE_UDP_DEST_PORT, &val);
    //PTP RX Version Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_VERSION", INDY_PTP_RX_VERSION, &val);
    //PTP RX Domain / Domain Range Lower Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_DOMAIN_DOMAIN_LO", INDY_PTP_RX_DOMAIN_DOMAIN_LO, &val);
    //PTP RX Domain Mask / Domain Range Upper Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_DOMAIN_MASK_DOMAIN_UP", INDY_PTP_RX_DOMAIN_MASK_DOMAIN_UP, &val);
    //PTP RX SdoId / SdoId Range Lower Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_SDOID_SDOID_LO", INDY_PTP_RX_SDOID_SDOID_LO, &val);
    //PTP RX SdoId Mask / SdoId Range Upper Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_SDOID_MASK_SDOID_UP", INDY_PTP_RX_SDOID_MASK_SDOID_UP, &val);

    //PTP TX Parsing Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_PARSE_CONFIG", INDY_PTP_TX_PARSE_CONFIG, &val);
    //PTP TX Parsing VLAN Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_PARSE_VLAN_CONFIG", INDY_PTP_TX_PARSE_VLAN_CONFIG, &val);
    //PTP TX Parsing Layer2 Format Address Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_PARSE_L2_ADDR_EN", INDY_PTP_TX_PARSE_L2_ADDR_EN, &val);
    //PTP TX Parsing IP Format Address Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_PARSE_IP_ADDR_EN", INDY_PTP_TX_PARSE_IP_ADDR_EN, &val);
    //PTP TX Parsing UDP Source Port Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_PARSE_UDP_SRC_PORT", INDY_PTP_TX_PARSE_UDP_SRC_PORT, &val);
    //PTP TX Parsing UDP Destination Port Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_PARSE_UDP_DEST_PORT", INDY_PTP_TX_PARSE_UDP_DEST_PORT, &val);
    // PTP TX Version Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_VERSION", INDY_PTP_TX_VERSION, &val);
    // PTP TX Domain / Domain Range Lower Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_DOMAIN_DOMAIN_LO", INDY_PTP_TX_DOMAIN_DOMAIN_LO, &val);
    // PTP TX Domain Mask / Domain Range Upper Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_DOMAIN_MASK_DOMAIN_UP", INDY_PTP_TX_DOMAIN_MASK_DOMAIN_UP, &val);
    // PTP TX SdoId / SdoId Range Lower Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_SDOID_SDOID_LO", INDY_PTP_TX_SDOID_SDOID_LO, &val);
    // PTP TX SdoId Mask / SdoId Range Upper Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_SDOID_MASK_SDOID_UP", INDY_PTP_TX_SDOID_MASK_SDOID_UP, &val);

    //MEPA_EXIT(dev);
    return MEPA_RC_OK;
}
static mepa_rc indy_ts_clock_conf_reg_dump(mepa_device_t *dev,
                                           const mepa_debug_print_t pr)
{
    uint16_t val = 0;

    // PTP TSU Interrupt Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TSU_INT_EN", INDY_PTP_TSU_INT_EN, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TSU_INT_STS", INDY_PTP_TSU_INT_STS, &val);

    //PTP RX Timestamp Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_TIMESTAMP_EN", INDY_PTP_RX_TIMESTAMP_EN, &val);
    //PTP RX Timestamp Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_TIMESTAMP_CONFIG", INDY_PTP_RX_TIMESTAMP_CONFIG, &val);
    //PTP RX Modification Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_MOD", INDY_PTP_RX_MOD, &val);
    //PTP RX Reserved Bytes Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_RSVD_BYTE_CFG", INDY_PTP_RX_RSVD_BYTE_CFG, &val);
    //PTP RX Tail Tag Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_TAIL_TAG", INDY_PTP_RX_TAIL_TAG, &val);
    //PTP RX Correction Field Modification Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_CF_MOD_EN", INDY_PTP_RX_CF_MOD_EN, &val);
    //PTP RX Correction Field Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_RX_CF_CFG", INDY_PTP_RX_CF_CFG, &val);

    // PTP TX Timestamp Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_TIMESTAMP_EN", INDY_PTP_TX_TIMESTAMP_EN, &val);
    // PTP TX Timestamp Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_TIMESTAMP_CONFIG", INDY_PTP_TX_TIMESTAMP_CONFIG, &val);
    // PTP TX Modification Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_MOD", INDY_PTP_TX_MOD, &val);
    // PTP TX Reserved Bytes Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_RSVD_BYTE_CFG", INDY_PTP_TX_RSVD_BYTE_CFG, &val);
    // PTP TX Tail Tag Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_TAIL_TAG", INDY_PTP_TX_TAIL_TAG, &val);
    // PTP TX Correction Field Modification Enable Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_CF_MOD_EN", INDY_PTP_TX_CF_MOD_EN, &val);
    // PTP TX Correction Field Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_CF_CFG", INDY_PTP_TX_CF_CFG, &val);
    // PTP TX Message Header
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_MSG_HEADER1", INDY_PTP_TX_MSG_HEADER1, &val);
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TX_MSG_HEADER2", INDY_PTP_TX_MSG_HEADER2, &val);

    // TSU General Configuration Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TSU_GEN_CONF", INDY_PTP_TSU_GEN_CONF, &val);
    // TSU Hard Reset Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TSU_HARD_RESET", INDY_PTP_TSU_HARD_RESET, &val);
    // TSU Soft Reset Register
    indy_ts_deb_pr_reg(dev,  pr,  "INDY_PTP_TSU_SOFT_RESET", INDY_PTP_TSU_SOFT_RESET, &val);
    return MEPA_RC_OK;
}
static mepa_rc indy_ts_classifier_ptp_conf_priv(mepa_device_t *dev, mepa_bool_t ing, const mepa_ts_classifier_ptp_t *ptp_hdr_conf)
{
    uint16_t val = 0, version = 0;

    if (ing) {
        val = 0xF & ptp_hdr_conf->version.upper;
        val = val << 4;
        val = val | (0xF & ptp_hdr_conf->minor_version.upper);
        version = val;
        val = 0;
        val = 0xF & ptp_hdr_conf->version.lower;
        val = val << 4;
        val = val | (0xF & ptp_hdr_conf->minor_version.lower);
        version = version << 8;
        version = version | (0xFF & val);
        EP_WRM(dev, INDY_PTP_RX_VERSION, version, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_TX_VERSION, version, INDY_DEF_MASK);
        if (ptp_hdr_conf->domain.mode == MEPA_TS_MATCH_MODE_RANGE) {
            val = 0;
            val = val | INDY_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_EN;
            val = val | INDY_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_LO_F(ptp_hdr_conf->domain.match.range.lower);
            EP_WRM(dev, INDY_PTP_RX_DOMAIN_DOMAIN_LO, val, INDY_DEF_MASK);
            val = 0;
            val = val | ptp_hdr_conf->domain.match.range.upper;
            EP_WRM(dev, INDY_PTP_RX_DOMAIN_MASK_DOMAIN_UP, val, INDY_DEF_MASK);
        } else {
            val = ptp_hdr_conf->domain.match.value.val;
            EP_WRM(dev, INDY_PTP_RX_DOMAIN_DOMAIN_LO, val, INDY_DEF_MASK);
            val = 0;
            val = ptp_hdr_conf->domain.match.value.mask;
            EP_WRM(dev, INDY_PTP_RX_DOMAIN_MASK_DOMAIN_UP, val, INDY_DEF_MASK);
        }
#if 0
        if (ptp_hdr_conf->sdoid.mode == MEPA_TS_MATCH_MODE_RANGE) {
            val = 0;
            val = val | INDY_PTP_RX_SDOID_SDOID_LO_RANGE_EN;
            val = val | INDY_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_LO_F(ptp_hdr_conf->sdoid.match.range.lower);
            EP_WRM(dev, INDY_PTP_RX_SDOID_SDOID_LO, val, INDY_DEF_MASK);
            val = 0;
            val = val | ptp_hdr_conf->sdoid.match.range.upper;
            EP_WRM(dev, INDY_PTP_RX_SDOID_MASK_SDOID_UP, val, INDY_DEF_MASK);
        } else {
            val = ptp_hdr_conf->sdoid.match.value.val;
            EP_WRM(dev, INDY_PTP_RX_SDOID_SDOID_LO, val, INDY_DEF_MASK);
            val = 0;
            val = ptp_hdr_conf->sdoid.match.value.mask;
            EP_WRM(dev, INDY_PTP_RX_SDOID_MASK_SDOID_UP, val, INDY_DEF_MASK);
        }
#endif
    } else {
        val = 0xF & ptp_hdr_conf->version.upper;
        val = val << 4;
        val = val | (0xF & ptp_hdr_conf->minor_version.upper);
        version = val;
        val = 0;
        val = 0xF & ptp_hdr_conf->version.lower;
        val = val << 4;
        val = val | (0xF & ptp_hdr_conf->minor_version.lower);
        version = version << 8;
        version = version | (0xFF & val);
        EP_WRM(dev, INDY_PTP_TX_VERSION, version, INDY_DEF_MASK);
        if (ptp_hdr_conf->domain.mode == MEPA_TS_MATCH_MODE_RANGE) {
            val = 0;
            val = val | INDY_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_EN;
            val = val | INDY_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_LO_F(ptp_hdr_conf->domain.match.range.lower);
            EP_WRM(dev, INDY_PTP_TX_DOMAIN_DOMAIN_LO, val, INDY_DEF_MASK);
            val = 0;
            val = val | ptp_hdr_conf->domain.match.range.upper;
            EP_WRM(dev, INDY_PTP_TX_DOMAIN_MASK_DOMAIN_UP, val, INDY_DEF_MASK);
        } else {
            val = ptp_hdr_conf->domain.match.value.val;
            EP_WRM(dev, INDY_PTP_TX_DOMAIN_DOMAIN_LO, val, INDY_DEF_MASK);
            val = 0;
            val = ptp_hdr_conf->domain.match.value.mask;
            EP_WRM(dev, INDY_PTP_TX_DOMAIN_MASK_DOMAIN_UP, val, INDY_DEF_MASK);
        }
#if 0
        if (ptp_hdr_conf->sdoid.mode == MEPA_TS_MATCH_MODE_RANGE) {
            val = val | INDY_PTP_TX_SDOID_SDOID_LO_RANGE_EN;
            val = val | INDY_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_LO_F(ptp_hdr_conf->sdoid.match.range.lower);
            EP_WRM(dev, INDY_PTP_TX_SDOID_SDOID_LO, val, INDY_DEF_MASK);
            val = 0;
            val = val | ptp_hdr_conf->sdoid.match.range.upper;
            EP_WRM(dev, INDY_PTP_TX_SDOID_MASK_SDOID_UP, val, INDY_DEF_MASK);
        } else {
            val = ptp_hdr_conf->sdoid.match.value.val;
            EP_WRM(dev, INDY_PTP_TX_SDOID_SDOID_LO, val, INDY_DEF_MASK);
            val = 0;
            val = ptp_hdr_conf->sdoid.match.value.mask;
            EP_WRM(dev, INDY_PTP_TX_SDOID_MASK_SDOID_UP, val, INDY_DEF_MASK);
        }
#endif

    }
    return MEPA_RC_OK;
}


static mepa_rc indy_ts_classifier_ipv4_addr_conf_priv(mepa_device_t *dev, mepa_bool_t ing, const mepa_ipv4_network_t *ipv4)
{
    uint16_t val = 0;

    if (ing) {
        val = (ipv4->addr >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_7, val, INDY_DEF_MASK);
        val = ipv4->addr & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_6, val, INDY_DEF_MASK);

        val = (ipv4->mask >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_7, val, INDY_DEF_MASK);
        val = ipv4->mask & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_6, val, INDY_DEF_MASK);
    } else {
        val = (ipv4->addr >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_7, val, INDY_DEF_MASK);
        val = ipv4->addr & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_6, val, INDY_DEF_MASK);

        val = (ipv4->mask >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_7, val, INDY_DEF_MASK);
        val = ipv4->mask & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_6, val, INDY_DEF_MASK);
    }
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_classifier_ipv6_addr_conf_priv(mepa_device_t *dev, mepa_bool_t ing, const mepa_ipv6_network_t *ipv6)
{
    uint16_t val = 0;

    if (ing) {
        val = (ipv6->addr[0] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_0, val, INDY_DEF_MASK);
        val = ipv6->addr[0] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_1, val, INDY_DEF_MASK);
        val = (ipv6->addr[1] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_2, val, INDY_DEF_MASK);
        val = ipv6->addr[1] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_3, val, INDY_DEF_MASK);
        val = (ipv6->addr[2] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_4, val, INDY_DEF_MASK);
        val = ipv6->addr[2] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_5, val, INDY_DEF_MASK);
        val = (ipv6->addr[3] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_6, val, INDY_DEF_MASK);
        val = ipv6->addr[3] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_ADDR_7, val, INDY_DEF_MASK);

        val = (ipv6->mask[0] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_0, val, INDY_DEF_MASK);
        val = ipv6->mask[0] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_1, val, INDY_DEF_MASK);
        val = (ipv6->mask[1] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_2, val, INDY_DEF_MASK);
        val = ipv6->mask[1] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_3, val, INDY_DEF_MASK);
        val = (ipv6->mask[2] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_4, val, INDY_DEF_MASK);
        val = ipv6->mask[2] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_5, val, INDY_DEF_MASK);
        val = (ipv6->mask[3] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_6, val, INDY_DEF_MASK);
        val = ipv6->mask[3] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_RX_USER_IP_MASK_7, val, INDY_DEF_MASK);
    } else {
        val = (ipv6->addr[0] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_0, val, INDY_DEF_MASK);
        val = ipv6->addr[0] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_1, val, INDY_DEF_MASK);
        val = (ipv6->addr[1] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_2, val, INDY_DEF_MASK);
        val = ipv6->addr[1] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_3, val, INDY_DEF_MASK);
        val = (ipv6->addr[2] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_4, val, INDY_DEF_MASK);
        val = ipv6->addr[2] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_5, val, INDY_DEF_MASK);
        val = (ipv6->addr[3] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_6, val, INDY_DEF_MASK);
        val = ipv6->addr[3] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_ADDR_7, val, INDY_DEF_MASK);

        val = (ipv6->mask[0] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_0, val, INDY_DEF_MASK);
        val = ipv6->mask[0] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_1, val, INDY_DEF_MASK);
        val = (ipv6->mask[1] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_2, val, INDY_DEF_MASK);
        val = ipv6->mask[1] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_3, val, INDY_DEF_MASK);
        val = (ipv6->mask[2] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_4, val, INDY_DEF_MASK);
        val = ipv6->mask[2] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_5, val, INDY_DEF_MASK);
        val = (ipv6->mask[3] >> 16) & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_6, val, INDY_DEF_MASK);
        val = ipv6->mask[3] & 0xFFFF;
        EP_WRM(dev, INDY_PTP_TX_USER_IP_MASK_7, val, INDY_DEF_MASK);
    }
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_classifier_mac_conf_set_priv(mepa_device_t *dev,  mepa_bool_t ing, const uint8_t *mac_addr)
{
    uint16_t val = 0;

    if (ing) {
        val = mac_addr[0] << 8 | mac_addr[1];
        EP_WRM(dev, INDY_PTP_RX_USER_MAC_HI, val, INDY_DEF_MASK);
        val = mac_addr[2] << 8 | mac_addr[3];
        EP_WRM(dev, INDY_PTP_RX_USER_MAC_MID, val, INDY_DEF_MASK);
        val = mac_addr[4] << 8 | mac_addr[5];
        EP_WRM(dev, INDY_PTP_RX_USER_MAC_LO, val, INDY_DEF_MASK);
    } else {
        val = mac_addr[0] << 8 | mac_addr[1];
        EP_WRM(dev, INDY_PTP_TX_USER_MAC_HI, val, INDY_DEF_MASK);
        val = mac_addr[2] << 8 | mac_addr[3];
        EP_WRM(dev, INDY_PTP_TX_USER_MAC_MID, val, INDY_DEF_MASK);
        val = mac_addr[4] << 8 | mac_addr[5];
        EP_WRM(dev, INDY_PTP_TX_USER_MAC_LO, val, INDY_DEF_MASK);
    }
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_classifier_vlan_conf_set_priv(mepa_device_t *dev, mepa_bool_t ing, const mepa_ts_vlan_conf_t *const vlan_conf)
{
    uint16_t vlan_parse = 0, range_up = 0, range_lo = 0, vid = 0, mask = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    if (ing) {
        switch (vlan_conf->num_tag) {
        case 2:
            vlan_parse = vlan_parse | INDY_PTP_RX_PARSE_VLAN_VLAN2_CHECK_EN;
            /* fall-through */
        case 1:
            vlan_parse = vlan_parse | INDY_PTP_RX_PARSE_VLAN_VLAN1_CHECK_EN;
            vlan_parse = vlan_parse | INDY_PTP_RX_PARSE_VLAN_TAG_COUNT_F(vlan_conf->num_tag);
            EP_WRM(dev, INDY_PTP_RX_PARSE_VLAN_CONFIG, vlan_parse, INDY_DEF_MASK);
            break;
        default:
            T_E(MEPA_TRACE_GRP_TS, "Number of VLAN tags supported : 2 ::  Port : %d\n", data->port_no);
            return MEPA_RC_ERROR;
            break;
        }
    } else {
        switch (vlan_conf->num_tag) {
        case 2:
            vlan_parse = vlan_parse | INDY_PTP_TX_PARSE_VLAN_VLAN2_CHECK_EN;
            /* fall-through */
        case 1:
            vlan_parse = vlan_parse | INDY_PTP_TX_PARSE_VLAN_VLAN1_CHECK_EN;
            vlan_parse = vlan_parse | INDY_PTP_TX_PARSE_VLAN_TAG_COUNT_F(vlan_conf->num_tag);
            EP_WRM(dev, INDY_PTP_TX_PARSE_VLAN_CONFIG, vlan_parse, INDY_DEF_MASK);
            break;
        default:
            T_E(MEPA_TRACE_GRP_TS, "Number of VLAN tags supported : 2 ::  Port : %d\n", data->port_no);
            return MEPA_RC_ERROR;
            break;
        }
    }

    // common configuration for both ingress and egress, reconfigures
    switch (vlan_conf->num_tag) {
    case 2:
        if (vlan_conf->outer_tag.mode == MEPA_TS_MATCH_MODE_RANGE) {
            range_up = range_up | INDY_VLAN2_VID_RANGE_EN;
            range_up = range_up | INDY_VLAN2_VID_RANGE_UP_VAL_F(vlan_conf->outer_tag.match.range.upper);
            range_lo = range_lo | INDY_VLAN2_VID_RANGE_UP_VAL_F(vlan_conf->outer_tag.match.range.lower);
            EP_WRM(dev, INDY_VLAN2_VID_RANGE_UP, range_up, INDY_DEF_MASK);
            EP_WRM(dev, INDY_VLAN2_VID_RANGE_LO, range_lo, INDY_DEF_MASK);
        } else {
            vid = vid | INDY_VLAN2_TYPE_SELECT_F(0);
            vid = vid | INDY_VLAN2_TYPE_ID_VAL_F(vlan_conf->outer_tag.match.value.val);
            mask = mask | INDY_VLAN2_ID_MASK_VAL_F(vlan_conf->outer_tag.match.value.mask);
            EP_WRM(dev, INDY_VLAN2_TYPE_ID, vid, INDY_DEF_MASK);
            EP_WRM(dev, INDY_VLAN2_ID_MASK, mask, INDY_DEF_MASK);
        }
        /* fall-through */
    case 1:
        if (vlan_conf->inner_tag.mode == MEPA_TS_MATCH_MODE_RANGE) {
            range_up = 0, range_lo = 0;
            range_up = range_up | INDY_VLAN1_VID_RANGE_EN;
            range_up = range_up | INDY_VLAN1_VID_RANGE_UP_VAL_F(vlan_conf->inner_tag.match.range.upper);
            range_lo = range_lo | INDY_VLAN1_VID_RANGE_UP_VAL_F(vlan_conf->inner_tag.match.range.lower);
            EP_WRM(dev, INDY_VLAN1_VID_RANGE_UP, range_up, INDY_DEF_MASK);
            EP_WRM(dev, INDY_VLAN1_VID_RANGE_LO, range_lo, INDY_DEF_MASK);
        } else {
            mask = 0, vid = 0;
            vid = vid | INDY_VLAN1_TYPE_SELECT_F(0);
            vid = vid | INDY_VLAN1_TYPE_ID_VAL_F(vlan_conf->inner_tag.match.value.val);
            mask = mask | INDY_VLAN1_ID_MASK_VAL_F(vlan_conf->inner_tag.match.value.mask);
            EP_WRM(dev, INDY_VLAN1_TYPE_ID, vid, INDY_DEF_MASK);
            EP_WRM(dev, INDY_VLAN1_ID_MASK, mask, INDY_DEF_MASK);
        }
        break;
    default:
        T_E(MEPA_TRACE_GRP_TS, "Number of VLAN tags supported : 2 ::  Port : %d\n", data->port_no);
        return MEPA_RC_ERROR;
        break;
    }
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_rx_classifier_conf_set_priv(mepa_device_t *dev, uint16_t flow_index, const mepa_ts_classifier_t *const pkt_conf)
{
    uint16_t parse_config = 0, l2_en = 0, ip_en = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    T_I(MEPA_TRACE_GRP_TS, "RX Classifier :Port : %d  Encapsulation :%d MAC Mode : %d MAC Select : %d VLAN En : %d\n",
        data->port_no, pkt_conf->pkt_encap_type, pkt_conf->eth_class_conf.mac_match_mode,
        pkt_conf->eth_class_conf.mac_match_select, pkt_conf->eth_class_conf.vlan_check);
    // PBB not supported
    if (pkt_conf->eth_class_conf.vlan_check && pkt_conf->eth_class_conf.vlan_conf.pbb_en) {
        T_E(MEPA_TRACE_GRP_TS, "PBB not supported on Indy.  Port : %d\n", data->port_no);
        return MEPA_RC_ERROR;
    }
    if ((pkt_conf->eth_class_conf.mac_match_select == MEPA_TS_ETH_MATCH_SRC_OR_DEST) &&
        (pkt_conf->eth_class_conf.mac_match_mode   != MEPA_TS_ETH_ADDR_MATCH_48BIT)) {
        T_E(MEPA_TRACE_GRP_TS, "When both source or destination mac address need to be matched,"
                               "match mode must be set to full 48-bit address");
        return MEPA_RC_ERROR;
    }
    switch (pkt_conf->pkt_encap_type) {
    case MEPA_TS_ENCAP_ETH_PTP:
        parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_LAYER2_EN;
        parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_PEER_NONPEER_MIX;
        l2_en = l2_en | INDY_PTP_TX_PARSE_L2_MAC_EN_F(pkt_conf->eth_class_conf.mac_match_select);
        if (pkt_conf->eth_class_conf.mac_match_select == MEPA_TS_ETH_MATCH_SRC_ADDR) {
            MEPA_RC(indy_ts_classifier_mac_conf_set_priv(dev, TRUE, pkt_conf->eth_class_conf.mac_addr));
        } else {
            parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(pkt_conf->eth_class_conf.mac_match_mode);
            if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST) { // Match any Unicast MAC
                parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(2);
            } else if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST) { // Match any Multicast MAC
                parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(4);
            } else if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_48BIT) { // Match compleete 48 bit MAC
                parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(1);
                parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_EN;
                MEPA_RC(indy_ts_classifier_mac_conf_set_priv(dev, TRUE, pkt_conf->eth_class_conf.mac_addr));
            }
        }
        if (pkt_conf->eth_class_conf.vlan_check == TRUE) {
            MEPA_RC(indy_ts_classifier_vlan_conf_set_priv(dev, TRUE, &pkt_conf->eth_class_conf.vlan_conf));
        } else {
            EP_WRM(dev, INDY_PTP_RX_PARSE_VLAN_CONFIG, 0, INDY_DEF_MASK);
        }
        EP_WRM(dev, INDY_PTP_RX_PARSE_L2_ADDR_EN, l2_en, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_RX_PARSE_IP_ADDR_EN, ip_en, INDY_DEF_MASK);
        break;
    case MEPA_TS_ENCAP_ETH_IP_PTP:
        T_I(MEPA_TRACE_GRP_TS, "RX IP/PTP Encap :: Port : %d  IP Ver: %d IP Match Mode : %d: UDP SPort chk : %d UDP SPort chk : %d  S Port: %d D Port :%d\n",
            data->port_no, pkt_conf->ip_class_conf.ip_ver, pkt_conf->ip_class_conf.ip_match_mode, pkt_conf->ip_class_conf.udp_sport_en,
            pkt_conf->ip_class_conf.udp_dport_en, pkt_conf->ip_class_conf.udp_sport, pkt_conf->ip_class_conf.udp_dport);
        parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_LAYER2_EN;
        parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_PEER_NONPEER_MIX;
        l2_en = l2_en | INDY_PTP_RX_PARSE_L2_MAC_EN_F(pkt_conf->eth_class_conf.mac_match_select);
        if (pkt_conf->eth_class_conf.mac_match_select == MEPA_TS_ETH_MATCH_SRC_ADDR) {
            MEPA_RC(indy_ts_classifier_mac_conf_set_priv(dev, TRUE, pkt_conf->eth_class_conf.mac_addr));
        } else {
            parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(pkt_conf->eth_class_conf.mac_match_mode);
            if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST) { // Match any Unicast MAC
                parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(2);
            } else if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST) { // Match any Multicast MAC
                parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(4);
            } else if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_48BIT) { // Match compleete 48 bit MAC
                parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(1);
                parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_MAC_DA_EN;
                MEPA_RC(indy_ts_classifier_mac_conf_set_priv(dev, TRUE, pkt_conf->eth_class_conf.mac_addr));
            }
        }
        if (pkt_conf->eth_class_conf.vlan_check == TRUE) {
            MEPA_RC(indy_ts_classifier_vlan_conf_set_priv(dev, TRUE, &pkt_conf->eth_class_conf.vlan_conf));
        } else {
            EP_WRM(dev, INDY_PTP_RX_PARSE_VLAN_CONFIG, 0, INDY_DEF_MASK);
        }
        EP_WRM(dev, INDY_PTP_RX_PARSE_L2_ADDR_EN, l2_en, INDY_DEF_MASK);

        if (pkt_conf->ip_class_conf.ip_match_mode == MEPA_TS_IP_MATCH_DEST) {
            ip_en = ip_en | INDY_PTP_RX_PARSE_IP_DA_EN;
        }
        if (pkt_conf->ip_class_conf.ip_ver == MEPA_TS_IP_VER_4) {
            ip_en = ip_en | INDY_PTP_RX_PARSE_IPv4_UMAC_EN_F(pkt_conf->eth_class_conf.mac_match_select);
            ip_en = ip_en | INDY_PTP_RX_PARSE_IPv4_IP_EN_F(pkt_conf->ip_class_conf.ip_match_mode);
            parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_IPV4_EN;
            MEPA_RC(indy_ts_classifier_ipv4_addr_conf_priv(dev, TRUE, &pkt_conf->ip_class_conf.ip_addr.ipv4));
        } else {
            parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_IPV6_EN;
            ip_en = ip_en | INDY_PTP_RX_PARSE_IPv6_UMAC_EN_F(pkt_conf->eth_class_conf.mac_match_select);
            ip_en = ip_en | INDY_PTP_RX_PARSE_IPv6_IP_EN_F(pkt_conf->ip_class_conf.ip_match_mode);
            MEPA_RC(indy_ts_classifier_ipv6_addr_conf_priv(dev, TRUE, &pkt_conf->ip_class_conf.ip_addr.ipv6));
        }
        if (pkt_conf->ip_class_conf.udp_sport_en) {
            parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_UDP_SPORT_EN;
            EP_WRM(dev, INDY_PTP_RX_PARSE_UDP_SRC_PORT, pkt_conf->ip_class_conf.udp_sport, INDY_DEF_MASK);
        }
        if (pkt_conf->ip_class_conf.udp_dport_en) {
            parse_config = parse_config | INDY_PTP_RX_PARSE_CONFIG_UDP_DPORT_EN;
            EP_WRM(dev, INDY_PTP_RX_PARSE_UDP_DEST_PORT, pkt_conf->ip_class_conf.udp_dport, INDY_DEF_MASK);
        }
        EP_WRM(dev, INDY_PTP_RX_PARSE_IP_ADDR_EN, ip_en, INDY_DEF_MASK);
        break;
    case MEPA_TS_ENCAP_NONE:
        break;
    default:
        T_E(MEPA_TRACE_GRP_TS, "Encapsulation type not supported on Indy. Port : %d\n", data->port_no);
        return MEPA_RC_ERROR;
        break;
    }
    EP_WRM(dev, INDY_PTP_RX_PARSE_CONFIG, parse_config, INDY_DEF_MASK);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_tx_classifier_conf_set_priv(mepa_device_t *dev, uint16_t flow_index, const mepa_ts_classifier_t *const pkt_conf)
{
    uint16_t parse_config = 0, l2_en = 0, ip_en = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;

    T_I(MEPA_TRACE_GRP_TS, "Tx Classifier :Port : %d  Encapsulation :%d MAC Mode : %d MAC Select : %d VLAN En : %d\n",
        data->port_no, pkt_conf->pkt_encap_type, pkt_conf->eth_class_conf.mac_match_mode,
        pkt_conf->eth_class_conf.mac_match_select, pkt_conf->eth_class_conf.vlan_check);

    // PBB not supported
    if (pkt_conf->eth_class_conf.vlan_check && pkt_conf->eth_class_conf.vlan_conf.pbb_en) {
        return MEPA_RC_ERROR;
    }
    if ((pkt_conf->eth_class_conf.mac_match_select == MEPA_TS_ETH_MATCH_SRC_OR_DEST) &&
        (pkt_conf->eth_class_conf.mac_match_mode   != MEPA_TS_ETH_ADDR_MATCH_48BIT)) {
        T_E(MEPA_TRACE_GRP_TS, "When both source or destination mac address need to be matched,"
                               "match mode must be set to full 48-bit address");
        return MEPA_RC_ERROR;
    }

    switch (pkt_conf->pkt_encap_type) {
    case MEPA_TS_ENCAP_ETH_PTP:
        parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_LAYER2_EN;
        parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_PEER_NONPEER_MIX;
        l2_en = l2_en | INDY_PTP_TX_PARSE_L2_MAC_EN_F(pkt_conf->eth_class_conf.mac_match_select);
        if (pkt_conf->eth_class_conf.mac_match_select == MEPA_TS_ETH_MATCH_SRC_ADDR) {
            MEPA_RC(indy_ts_classifier_mac_conf_set_priv(dev, FALSE, pkt_conf->eth_class_conf.mac_addr));
        } else {
            parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(pkt_conf->eth_class_conf.mac_match_mode);
            if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST) { // Match any Unicast MAC
                parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(2);
            } else if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST) { // Match any Multicast MAC
                parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(4);
            } else if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_48BIT) { // Match compleete 48 bit MAC
                parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(1);
                parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_EN;
                MEPA_RC(indy_ts_classifier_mac_conf_set_priv(dev, FALSE, pkt_conf->eth_class_conf.mac_addr));
            }
        }
        if (pkt_conf->eth_class_conf.vlan_check == TRUE) {
            MEPA_RC(indy_ts_classifier_vlan_conf_set_priv(dev, FALSE, &pkt_conf->eth_class_conf.vlan_conf));
        } else {
            EP_WRM(dev, INDY_PTP_TX_PARSE_VLAN_CONFIG, 0, INDY_DEF_MASK);
        }
        EP_WRM(dev, INDY_PTP_TX_PARSE_L2_ADDR_EN, l2_en, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_TX_PARSE_IP_ADDR_EN, ip_en, INDY_DEF_MASK);
        break;
    case MEPA_TS_ENCAP_ETH_IP_PTP:
        T_I(MEPA_TRACE_GRP_TS, "TX IP/PTP Encap :: Port : %d  IP Ver: %d IP Match Mode : %d: UDP SPort chk : %d UDP SPort chk : %d  S Port: %d D Port :%d\n",
            data->port_no, pkt_conf->ip_class_conf.ip_ver, pkt_conf->ip_class_conf.ip_match_mode, pkt_conf->ip_class_conf.udp_sport_en,
            pkt_conf->ip_class_conf.udp_dport_en, pkt_conf->ip_class_conf.udp_sport, pkt_conf->ip_class_conf.udp_dport);
        parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_LAYER2_EN;
        parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_PEER_NONPEER_MIX;
        l2_en = l2_en | INDY_PTP_TX_PARSE_L2_MAC_EN_F(pkt_conf->eth_class_conf.mac_match_select);
        if (pkt_conf->eth_class_conf.mac_match_select == MEPA_TS_ETH_MATCH_SRC_ADDR) {
            MEPA_RC(indy_ts_classifier_mac_conf_set_priv(dev, FALSE, pkt_conf->eth_class_conf.mac_addr));
        } else {
            parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(pkt_conf->eth_class_conf.mac_match_mode);
            if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST) { // Match any Unicast MAC
                parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(2);
            } else if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST) { // Match any Multicast MAC
                parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(4);
            } else if (pkt_conf->eth_class_conf.mac_match_mode == MEPA_TS_ETH_ADDR_MATCH_48BIT) { // Match compleete 48 bit MAC
                parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(1);
                parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_MAC_DA_EN;
                MEPA_RC(indy_ts_classifier_mac_conf_set_priv(dev, FALSE, pkt_conf->eth_class_conf.mac_addr));
            }
        }
        if (pkt_conf->eth_class_conf.vlan_check == TRUE) {
            MEPA_RC(indy_ts_classifier_vlan_conf_set_priv(dev, FALSE, &pkt_conf->eth_class_conf.vlan_conf));
        } else {
            EP_WRM(dev, INDY_PTP_TX_PARSE_VLAN_CONFIG, 0, INDY_DEF_MASK);
        }

        EP_WRM(dev, INDY_PTP_TX_PARSE_L2_ADDR_EN, l2_en, INDY_DEF_MASK);
        if (pkt_conf->ip_class_conf.ip_match_mode == MEPA_TS_IP_MATCH_DEST) {
            ip_en = ip_en | INDY_PTP_TX_PARSE_IP_DA_EN;
        }
        if (pkt_conf->ip_class_conf.ip_ver == MEPA_TS_IP_VER_4) {
            ip_en = ip_en | INDY_PTP_TX_PARSE_IPv4_UMAC_EN_F(pkt_conf->eth_class_conf.mac_match_select);
            ip_en = ip_en | INDY_PTP_TX_PARSE_IPv4_IP_EN_F(pkt_conf->ip_class_conf.ip_match_mode);
            parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_IPV4_EN;
            MEPA_RC(indy_ts_classifier_ipv4_addr_conf_priv(dev, FALSE, &pkt_conf->ip_class_conf.ip_addr.ipv4));
        } else {
            parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_IPV6_EN;
            ip_en = ip_en | INDY_PTP_TX_PARSE_IPv6_UMAC_EN_F(pkt_conf->eth_class_conf.mac_match_select);
            ip_en = ip_en | INDY_PTP_TX_PARSE_IPv6_IP_EN_F(pkt_conf->ip_class_conf.ip_match_mode);
            MEPA_RC(indy_ts_classifier_ipv6_addr_conf_priv(dev, FALSE, &pkt_conf->ip_class_conf.ip_addr.ipv6));
        }
        if (pkt_conf->ip_class_conf.udp_sport_en) {
            parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_UDP_SPORT_EN;
            EP_WRM(dev, INDY_PTP_TX_PARSE_UDP_SRC_PORT, pkt_conf->ip_class_conf.udp_sport, INDY_DEF_MASK);
        }
        if (pkt_conf->ip_class_conf.udp_dport_en) {
            parse_config = parse_config | INDY_PTP_TX_PARSE_CONFIG_UDP_DPORT_EN;
            EP_WRM(dev, INDY_PTP_TX_PARSE_UDP_DEST_PORT, pkt_conf->ip_class_conf.udp_dport, INDY_DEF_MASK);
        }
        EP_WRM(dev, INDY_PTP_TX_PARSE_IP_ADDR_EN, ip_en, INDY_DEF_MASK);
        break;
    case MEPA_TS_ENCAP_NONE:
        break;
    default:
        T_E(MEPA_TRACE_GRP_TS, "EGR Classifier: Encapsulation type not supported on Indy. Port : %d\n", data->port_no);
        rc = MEPA_RC_ERROR;
        break;
    }
    EP_WRM(dev, INDY_PTP_TX_PARSE_CONFIG, parse_config, INDY_DEF_MASK);
    return rc;
}

static mepa_rc indy_ts_rx_classifier_conf_set(mepa_device_t *dev, uint16_t flow_index, const mepa_ts_classifier_t *const pkt_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_ASSERT(pkt_conf == NULL);
    MEPA_ENTER(dev);

    if ((rc = indy_ts_rx_classifier_conf_set_priv(dev, flow_index, pkt_conf)) != MEPA_RC_OK) {
        MEPA_EXIT(dev);
        return rc;
    }
    memcpy(&data->ts_state.ts_port_conf.rx_pkt_conf, pkt_conf, sizeof(mepa_ts_classifier_t));

    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc indy_ts_tx_classifier_conf_get(mepa_device_t *dev, uint16_t flow_index,           mepa_ts_classifier_t *const pkt_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(pkt_conf == NULL);
    MEPA_ENTER(dev);
    memcpy(pkt_conf, &data->ts_state.ts_port_conf.tx_pkt_conf, sizeof(mepa_ts_classifier_t));

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_tx_classifier_conf_set(mepa_device_t *dev, uint16_t flow_index, const mepa_ts_classifier_t *const pkt_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_ASSERT(pkt_conf == NULL);
    MEPA_ENTER(dev);

    if ((rc = indy_ts_tx_classifier_conf_set_priv(dev, flow_index, pkt_conf)) != MEPA_RC_OK) {
        MEPA_EXIT(dev);
        return rc;
    }

    memcpy(&data->ts_state.ts_port_conf.tx_pkt_conf, pkt_conf, sizeof(mepa_ts_classifier_t));
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc indy_ts_rx_ptp_clock_conf_get (mepa_device_t *dev, uint16_t clock_id,
                                              mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(ptpclock_conf == NULL);
    MEPA_ENTER(dev);
    ptpclock_conf->enable = data->ts_state.ts_port_conf.rx_clock_conf.enable;
    ptpclock_conf->clk_mode = data->ts_state.ts_port_conf.rx_clock_conf.clk_mode;
    ptpclock_conf->delaym_type = data->ts_state.ts_port_conf.rx_clock_conf.delaym_type;
    ptpclock_conf->cf_update = data->ts_state.ts_port_conf.rx_clock_conf.cf_update;
    memcpy(&ptpclock_conf->ptp_class_conf, &data->ts_state.ts_port_conf.rx_clock_conf.ptp_class_conf, sizeof(ptpclock_conf->ptp_class_conf));
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ts_tx_ptp_clock_conf_get(mepa_device_t *dev, uint16_t clock_id,
                                             mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(ptpclock_conf == NULL);
    MEPA_ENTER(dev);
    ptpclock_conf->enable = data->ts_state.ts_port_conf.tx_clock_conf.enable;
    ptpclock_conf->clk_mode = data->ts_state.ts_port_conf.tx_clock_conf.clk_mode;
    ptpclock_conf->delaym_type = data->ts_state.ts_port_conf.tx_clock_conf.delaym_type;
    ptpclock_conf->cf_update = data->ts_state.ts_port_conf.tx_clock_conf.cf_update;
    memcpy(&ptpclock_conf->ptp_class_conf, &data->ts_state.ts_port_conf.tx_clock_conf.ptp_class_conf, sizeof(ptpclock_conf->ptp_class_conf));
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

// Event Messages
#define SYNC_PACKET         0x0001
#define DELAY_REQ_PACKET    0x0002
#define PDELAY_REQ_PACKET   0x0004
#define PDELAY_RESP_PACKET  0x0008
// General Messages
#define FOLLOW_UP               0b10000000
#define DELAY_RESP              0b100000000
#define PDELAY_RESP_FOLLOW_UP   0b1000000000
#define ANNOUNCE                0b10000000000
#define SIGNALING               0b100000000000
#define MANAGEMENT              0b1000000000000

static mepa_rc indy_ts_rx_ptp_clock_conf_set(mepa_device_t *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    uint16_t ts_insert = 0, cf_update = 0, val = 0, rx_mod = 0, ts_config = 0, cf_config = 0;
    uint16_t rx_pdelay_upd = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;
    MEPA_ENTER(dev);
    rc = indy_ts_classifier_ptp_conf_priv(dev, TRUE, &ptpclock_conf->ptp_class_conf);
    if (rc != MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_TS, "PTP rx classifier conf set error");
    } else {
        memcpy(&data->ts_state.ts_port_conf.rx_clock_conf.ptp_class_conf, &ptpclock_conf->ptp_class_conf, sizeof(ptpclock_conf->ptp_class_conf));
    }
    if (!ptpclock_conf->enable) {
        EP_WRM(dev, INDY_PTP_RX_TIMESTAMP_EN, 0, INDY_DEF_MASK);
    } else {
        switch (ptpclock_conf->clk_mode) {
        case MEPA_TS_PTP_CLOCK_MODE_BC1STEP:
            if (ptpclock_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P ) {
                // Peer-to-Peer delay measurement method
                ts_insert = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
                rx_pdelay_upd |= INDY_F_PTP_RX_PDREQ_AUTO_UPDATE;
                //ts_insert = SYNC_PACKET | DELAY_REQ_PACKET;
            } else {
                // End-to-End delay measurement method
                ts_insert = SYNC_PACKET | DELAY_REQ_PACKET;
                //ts_insert = SYNC_PACKET | DELAY_REQ_PACKET;
            }
            break;
        case MEPA_TS_PTP_CLOCK_MODE_BC2STEP:
            if (ptpclock_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P ) {
                // Peer-to-Peer delay measurement method
                ts_insert = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
                //ts_insert = SYNC_PACKET | DELAY_REQ_PACKET;
            } else {
                // End-to-End delay measurement method
                ts_insert = SYNC_PACKET | DELAY_REQ_PACKET;
                //ts_insert = SYNC_PACKET | DELAY_REQ_PACKET;
            }
            break;
        case MEPA_TS_PTP_CLOCK_MODE_TC1STEP:
            if (ptpclock_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P ) {
                // Peer-to-Peer delay measurement method
                cf_update = SYNC_PACKET | DELAY_REQ_PACKET;
                ts_insert = PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
                rx_pdelay_upd |= INDY_F_PTP_RX_PDREQ_AUTO_UPDATE;
            } else {
                // End-to-End delay measurement method
                //ts_insert = SYNC_PACKET | PDELAY_RESP_PACKET;
                cf_update = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
            }
            break;
        case MEPA_TS_PTP_CLOCK_MODE_TC2STEP:
            // reserved field updation.
            ts_insert = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
            break;
        default:
            T_E(MEPA_TRACE_GRP_TS, "EGR Clock: Clock Type not supported. Port : %d\n", data->port_no);
            break;
        }
        EP_WRM(dev, INDY_PTP_RX_PDREQ_NS_HI, rx_pdelay_upd, INDY_F_PTP_RX_PDREQ_AUTO_UPDATE);
        EP_WRM(dev, INDY_PTP_RX_TIMESTAMP_EN, ts_insert, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_RX_CF_MOD_EN, cf_update, INDY_DEF_MASK);
        // 1 : Method B - CF_SUB_ADD_64 - ingress time subtracted from correction field
        // 0 : Method A - ingress timestamp in reserved bytes.
        if (data->ts_state.tc_op_mode == MEPA_TS_TC_OP_MODE_C) {
            cf_config |= INDY_PTP_RX_PTP_CF_METHOD;
        }
        cf_config = cf_config | INDY_PTP_RX_PTP_MAX_CF_DIS;
        EP_WRM(dev, INDY_PTP_RX_CF_CFG, cf_config, INDY_DEF_MASK);
        ts_config = ts_config | INDY_PTP_RX_PTP_ALT_MASTER_EN;
        ts_config = ts_config | INDY_PTP_RX_PTP_UDP_CHKSUM_DIS;
        EP_WRM(dev, INDY_PTP_RX_TIMESTAMP_CONFIG, val, INDY_DEF_MASK);
        val = 0x0405;
        EP_WRM(dev, INDY_PTP_RX_RSVD_BYTE_CFG, val, INDY_DEF_MASK);
        rx_mod = rx_mod | INDY_PTP_RX_MOD_PTP_INSERT_TS_EN;
        if(data->ts_state.rx_ts_len == MEPA_TS_RX_TIMESTAMP_LEN_32BIT) {
            rx_mod = rx_mod | INDY_PTP_RX_MOD_PTP_INSERT_TS_32BIT;
        }
        EP_WRM(dev, INDY_PTP_RX_MOD, rx_mod, rx_mod);
    }

    data->ts_state.ts_port_conf.rx_clock_conf.enable = ptpclock_conf->enable;
    data->ts_state.ts_port_conf.rx_clock_conf.clk_mode = ptpclock_conf->clk_mode;
    data->ts_state.ts_port_conf.rx_clock_conf.delaym_type = ptpclock_conf->delaym_type;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_tx_ptp_clock_conf_set(mepa_device_t *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    uint16_t ts_insert = 0, cf_update = 0, tx_mod = 0, ts_config = 0, cf_config = 0;
    mepa_rc rc;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_bool_t two_step_lat = FALSE;

    MEPA_ENTER(dev);
    if (ptpclock_conf->enable && (ptpclock_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP ||
                ptpclock_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP)) {
        two_step_lat = TRUE;
    }
    // Reload egress latencies based on clock type i.e. 1-step or 2-step
    indy_ts_reload_egress_latency(dev, two_step_lat);
    rc = indy_ts_classifier_ptp_conf_priv(dev, TRUE, &ptpclock_conf->ptp_class_conf);
    if (rc != MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_TS, "PTP tx classifier conf set error");
    } else {
        memcpy(&data->ts_state.ts_port_conf.tx_clock_conf.ptp_class_conf, &ptpclock_conf->ptp_class_conf, sizeof(ptpclock_conf->ptp_class_conf));
    }
    if (!ptpclock_conf->enable) {
        EP_WRM(dev, INDY_PTP_TX_TIMESTAMP_EN, 0, INDY_DEF_MASK);
    } else {
        // Configure the PTP actions to be taken on egress port
        switch (ptpclock_conf->clk_mode) {
        case MEPA_TS_PTP_CLOCK_MODE_BC1STEP:
            if (ptpclock_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P ) {
                // Peer-to-Peer delay measurement method
                cf_update = PDELAY_REQ_PACKET;
                tx_mod = tx_mod | INDY_PTP_TX_MOD_PDRESP_TA_INSERT; // Update correction field with turn  around time in PD_RESP
            } else {
                // End-to-End delay measurement method
                cf_update = DELAY_REQ_PACKET;
            }
            tx_mod = tx_mod | INDY_PTP_TX_MOD_SYNC_TS_INSERT;
            break;
        case MEPA_TS_PTP_CLOCK_MODE_BC2STEP:
            if (ptpclock_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P ) {
                // Peer-to-Peer delay measurement method
                ts_insert = PDELAY_REQ_PACKET;
                if (data->ts_state.tx_auto_followup_ts) {
                    tx_mod |= INDY_PTP_TX_MOD_FOLLOWUP_TS_INSERT | INDY_PTP_TX_MOD_PDRESPFOLLOWUP_TS_INSERT;
                } else {
                    ts_insert |= SYNC_PACKET | PDELAY_RESP_PACKET;
                }
            } else {
                // End-to-End delay measurement method
                ts_insert =  DELAY_REQ_PACKET;
                if (data->ts_state.tx_auto_followup_ts) {
                    tx_mod |= INDY_PTP_TX_MOD_FOLLOWUP_TS_INSERT;
                } else {
                    ts_insert |= SYNC_PACKET;
                }
            }
            break;
        case MEPA_TS_PTP_CLOCK_MODE_TC1STEP:
            if (ptpclock_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P ) {
                // Peer-to-Peer delay measurement method
                //ts_insert = SYNC_PACKET | PDELAY_REQ_PACKET| PDELAY_RESP_PACKET;
                cf_update = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET;
                tx_mod = tx_mod | INDY_PTP_TX_MOD_PDRESP_TA_INSERT; // Update correction field with turn  around time in PD_RESP
            } else {
                // End-to-End delay measurement method
                //ts_insert = SYNC_PACKET | PDELAY_RESP_PACKET;
                cf_update = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
            }
            break;
        case MEPA_TS_PTP_CLOCK_MODE_TC2STEP:
            ts_insert = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
            break;
        default:
            break;
        }
        EP_WRM(dev, INDY_PTP_TX_TIMESTAMP_EN, ts_insert, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_TX_CF_MOD_EN, cf_update, INDY_DEF_MASK);
        // 1 : Method B - CF_SUB_ADD_64 - ingress time subtracted from correction field
        // 0 : Method A - subtract ingress timestamp in reserved bytes.
        if (data->ts_state.tc_op_mode == MEPA_TS_TC_OP_MODE_C) {
            cf_config |= INDY_PTP_TX_PTP_CF_METHOD;
        }
        cf_config = cf_config | INDY_PTP_TX_PTP_MAX_CF_DIS;
        EP_WRM(dev, INDY_PTP_TX_CF_CFG, cf_config, INDY_DEF_MASK);
        ts_config = ts_config | INDY_PTP_TX_PTP_ALT_MASTER_EN;
        ts_config = ts_config | INDY_PTP_TX_PTP_UDP_CHKSUM_DIS;
        EP_WRM(dev, INDY_PTP_TX_TIMESTAMP_CONFIG, ts_config, INDY_DEF_MASK);
        //val = 0x0a27;
        //EP_WRM(dev, INDY_PTP_TX_RSVD_BYTE_CFG, val, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_TX_MOD, tx_mod, INDY_DEF_MASK);
    }
    data->ts_state.ts_port_conf.tx_clock_conf.enable = ptpclock_conf->enable;
    data->ts_state.ts_port_conf.tx_clock_conf.clk_mode = ptpclock_conf->clk_mode;
    data->ts_state.ts_port_conf.tx_clock_conf.delaym_type = ptpclock_conf->delaym_type;

    #if 0
    indy_ts_classifier_conf_reg_dump(dev, NULL);
    indy_ts_clock_conf_reg_dump(dev, NULL);
    #endif
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_pps_conf_get (mepa_device_t *dev, mepa_ts_pps_conf_t *const phy_pps_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    *phy_pps_conf = data->ts_state.pps;
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_ltc_target_seconds(mepa_device_t *dev, uint32_t sec)
{
    uint16_t val = sec & 0xFFFF;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    phy_data_t *base_data = (phy_data_t *)base_dev->data;

    EP_WR(dev, INDY_PTP_LTC_TARGET_SEC_LO_A, val);
    val = (sec >> 16);
    EP_WR(dev, INDY_PTP_LTC_TARGET_SEC_HI_A, val);
    val = base_data->ts_state.pps.pps_offset & 0xFFFF;
    EP_WR(dev, INDY_PTP_LTC_TARGET_NS_LO_A, val);
    val = base_data->ts_state.pps.pps_offset >> 16;
    EP_WR(dev, INDY_PTP_LTC_TARGET_NS_HI_A, val);

    return MEPA_RC_OK;
}
static mepa_rc indy_ts_pps_conf_set (mepa_device_t *dev, const mepa_ts_pps_conf_t *const phy_pps_conf)
{
    uint16_t val = 0;
    uint32_t pps[] = {100,500,1000,5000,10000,50000,100000,500000,1000000,5000000,10000000,50000000,100000000,200000000};
    uint16_t pps_num = sizeof(pps)/sizeof(pps[0]);
    mepa_timestamp_t ts = {};
    uint16_t i;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    phy_data_t *base_data = (phy_data_t *)base_dev->data;

    indy_ts_ltc_get(dev, &ts);
    MEPA_ENTER(dev);
    data->ts_state.pps = *phy_pps_conf;
    base_data->ts_state.pps = *phy_pps_conf;
    if (phy_pps_conf->pps_output_enable) {
        // configure target for 1pps trigger as current ltc + 2 seconds.
        indy_ltc_target_seconds(dev, ts.seconds.low + 2);

        // Reload after every sec
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_SEC_HI_A, val, INDY_DEF_MASK);
        val = 1;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_SEC_LO_A, val, INDY_DEF_MASK);
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_NS_HI_A, val, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_NS_LO_A, val, INDY_DEF_MASK);

        // find suitable pps width option among list of allowed pps width options.
        for (i = 0; i < pps_num; i++) {
            if (phy_pps_conf->pps_width_adj <= pps[i]) {
                break;
            }
        }
        if (i >= pps_num) {
            i = pps_num - 1;
        }
        val = (i << 4) | 0x2; // event A
        EP_WRM(dev, INDY_PTP_GENERAL_CONFIG, val, INDY_DEF_MASK);
    } else {
        // configure target for 1pps trigger as 0.
        indy_ltc_target_seconds(dev, 0);
        val = 0;
        EP_WR(dev, INDY_PTP_GENERAL_CONFIG, val);
    }
    data->ts_state.pps = *phy_pps_conf;
    base_data->ts_state.pps = *phy_pps_conf;
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

#if 0
static mepa_rc indy_ts_rx_ts_get (mepa_device_t *dev)
{
    uint16_t val = 0, head1 = 0, head2 = 0;
    mepa_timestamp_t ts = {};
    mepa_ts_fifo_sig_t sig = {};
    mepa_ts_fifo_status_t status = MEPA_TS_FIFO_SUCCESS;
    mepa_bool_t valid_ts = TRUE;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_ts_fifo_read_t rd_cb = data->ts_state.fifo_cb;
    memset(&sig, 0, sizeof(mepa_ts_fifo_sig_t));
    memset(&ts, 0, sizeof(mepa_timestamp_t));
    MEPA_ENTER(dev);
    do {
        EP_RD(dev, INDY_PTP_RX_TS_NS_HI, &val);
        if (val & INDY_PTP_RX_TS_NS_PTP_TX_TS_VALID) {
            ts.nanoseconds = (((val) & 0x3fff) << 16);
            val = 0;
            EP_RD(dev, INDY_PTP_RX_TS_NS_LO, &val);
            ts.nanoseconds = ts.nanoseconds | val;

            val = 0;
            EP_RD(dev, INDY_PTP_RX_TS_SEC_HI, &val);
            ts.seconds.low =  val;

            val = 0;
            EP_RD(dev, INDY_PTP_RX_TS_SEC_LO, &val);
            ts.seconds.low = (ts.seconds.low << 16) | val;

            EP_RD(dev, INDY_PTP_RX_MSG_HEADER1, &head1);
            EP_RD(dev, INDY_PTP_RX_MSG_HEADER2, &head2);

            sig.msg_type = head1 & 0xF;
            sig.sequence_id = head2;

            MEPA_EXIT(dev);
            rd_cb(data->port_no, &ts, &sig, status);
            MEPA_ENTER(dev);
        } else {
            valid_ts = FALSE;
        }

    } while (valid_ts);
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}
#endif

static mepa_rc indy_ts_tx_ts_get (mepa_device_t *dev)
{
    uint16_t val = 0, head1 = 0, head2 = 0;
    mepa_timestamp_t ts = {};
    mepa_ts_fifo_sig_t sig = {};
    mepa_ts_fifo_status_t status = MEPA_TS_FIFO_SUCCESS;
    mepa_bool_t valid_ts = TRUE;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_ts_fifo_read_t rd_cb = data->ts_state.fifo_cb;

    memset(&sig, 0, sizeof(mepa_ts_fifo_sig_t));
    memset(&ts, 0, sizeof(mepa_timestamp_t));
    MEPA_ENTER(dev);
    do {
        EP_RD(dev, INDY_PTP_TX_TS_NS_HI, &val);

        if (val & INDY_PTP_TX_TS_NS_PTP_TX_TS_VALID) {
            ts.nanoseconds = (((val) & 0x3fff) << 16);
            val = 0;
            EP_RD(dev, INDY_PTP_TX_TS_NS_LO, &val);
            ts.nanoseconds = ts.nanoseconds | val;

            val = 0;
            EP_RD(dev, INDY_PTP_TX_TS_SEC_HI, &val);
            ts.seconds.low =  val;

            val = 0;
            EP_RD(dev, INDY_PTP_TX_TS_SEC_LO, &val);
            ts.seconds.low = (ts.seconds.low << 16) | val;

            EP_RD(dev, INDY_PTP_TX_MSG_HEADER1, &head1);
            EP_RD(dev, INDY_PTP_TX_MSG_HEADER2, &head2);

            sig.msg_type = head1 & 0xF;
            sig.sequence_id = head2;
            sig.crc_src_port = head1 >> 4;
            sig.has_crc_src = TRUE;

            MEPA_EXIT(dev);
            rd_cb(data->port_no, &ts, &sig, status);
            MEPA_ENTER(dev);
        } else {
            valid_ts = FALSE;
        }
    } while (valid_ts);
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_TS, "msg_type:%d seq_id:%d crc_src_port:0x%x", sig.msg_type,
                            sig.sequence_id, sig.crc_src_port);

    return MEPA_RC_OK;
}

//Since EP_RD_INCR macro is used in below API, it must be ensured that API must be executed without interruption
//till its end. No other API should access Lan8814 registers as it may interfere with register addresses.
mepa_rc indy_ts_stats_get(mepa_device_t *dev, mepa_ts_stats_t   *const statistics)
{
    uint16_t val = 0, val2 = 0;

    MEPA_ASSERT(statistics == NULL);
    MEPA_ENTER(dev);
    memset(statistics, 0, sizeof(mepa_ts_stats_t));
    EP_RD_INCR(dev, INDY_PTP_TX_CHKSUM_DROPPED_CNT_HI, &val, TRUE);
    EP_RD_INCR(dev, INDY_PTP_TX_CHKSUM_DROPPED_CNT_LO, &val2, FALSE);
    statistics->egr_fcs_err = val;
    statistics->egr_fcs_err = statistics->egr_fcs_err << 16 | val2;

    EP_RD_INCR(dev, INDY_PTP_TX_FRMS_MOD_CNT_HI, &val, FALSE);
    EP_RD_INCR(dev, INDY_PTP_TX_FRMS_MOD_CNT_LO, &val2, FALSE);
    statistics->egr_frm_mod_cnt = val;
    statistics->egr_frm_mod_cnt = statistics->egr_frm_mod_cnt << 16 | val2;

    EP_RD_INCR(dev, INDY_PTP_RX_CHKSUM_DROPPED_CNT_HI, &val, TRUE);
    EP_RD_INCR(dev, INDY_PTP_RX_CHKSUM_DROPPED_CNT_LO, &val2, FALSE);
    statistics->ingr_fcs_err = val;
    statistics->ingr_fcs_err = statistics->ingr_fcs_err << 16 | val2;

    EP_RD_INCR(dev, INDY_PTP_RX_FRMS_MOD_CNT_HI, &val, FALSE);
    EP_RD_INCR(dev, INDY_PTP_RX_FRMS_MOD_CNT_LO, &val2, FALSE);
    statistics->ingr_frm_mod_cnt = val;
    statistics->ingr_frm_mod_cnt = statistics->ingr_frm_mod_cnt << 16 | val2;

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_event_get (mepa_device_t *dev,
                                  mepa_ts_event_t *const ev_mask)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ASSERT(ev_mask == NULL);
    MEPA_ENTER(dev);
    *ev_mask = data->ts_state.ts_port_conf.event_mask;

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_event_set (mepa_device_t *dev, const mepa_bool_t enable, const mepa_ts_event_t ev_mask)
{
    uint16_t mask = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    mepa_bool_t mask_changed = FALSE;
    MEPA_ENTER(dev);
    if (enable) {
        mask_changed = (0 == (data->ts_state.ts_port_conf.event_mask & ev_mask));
        data->ts_state.ts_port_conf.event_mask |= ev_mask;
    } else {
        mask_changed = (0 != (data->ts_state.ts_port_conf.event_mask & ev_mask));
        data->ts_state.ts_port_conf.event_mask &= ~ev_mask;
    }
    EP_RD(dev, INDY_PTP_TSU_INT_EN, &mask);
    if (mask_changed) {
        if (ev_mask & MEPA_TS_EGR_FIFO_OVERFLOW) {
            mask |= INDY_PTP_TSU_INT_TX_TS_OVRFL_EN;
            data->ts_state.ts_port_conf.event_mask = data->ts_state.ts_port_conf.event_mask | MEPA_TS_EGR_FIFO_OVERFLOW;
        }
        if (ev_mask & MEPA_TS_EGR_TIMESTAMP_CAPTURED) {
            mask |=  INDY_PTP_TSU_INT_TX_TS_EN;
            data->ts_state.ts_port_conf.event_mask = data->ts_state.ts_port_conf.event_mask | MEPA_TS_EGR_TIMESTAMP_CAPTURED;
        }
        EP_WRM(dev, INDY_PTP_TSU_INT_EN, mask, INDY_DEF_MASK);
    }
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_ts_event_poll(mepa_device_t *dev, mepa_ts_event_t  *const status)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t val = 0;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_ASSERT(status == NULL);
    MEPA_ENTER(dev);
    do {
        uint32_t chip_port = data->packet_idx % 4;
        rc = EP_RD(dev, INDY_CHIP_LVL_INTR_STATUS, &val);
        if (val & (1 << chip_port)) {
            rc = EP_RD(dev, INDY_PTP_TSU_INT_STS, &val);
            if (val & INDY_PTP_TX_TS_OVRFL_INT) {
                *status |= data->ts_state.ts_port_conf.event_mask & MEPA_TS_EGR_FIFO_OVERFLOW;
            }
            if (val & INDY_PTP_TX_TS_INT) {
                *status |= data->ts_state.ts_port_conf.event_mask & MEPA_TS_EGR_TIMESTAMP_CAPTURED;
            }
        }
    } while (0);
    MEPA_EXIT(dev);
    return rc;
}

void indy_ts_fifo_read_install(mepa_device_t *dev, mepa_ts_fifo_read_t rd_cb)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    MEPA_ENTER(dev);
    data->ts_state.fifo_cb = rd_cb;
    MEPA_EXIT(dev);
}

//Since EP_RD_INCR macro is used in below API, it must be ensured that API must be executed without interruption
//till its end. No other API should access Lan8814 registers as it may interfere with register addresses.
mepa_rc indy_ts_fifo_get(mepa_device_t *dev, mepa_fifo_ts_entry_t ts_list[], const size_t size, uint32_t *const num)
{
    uint16_t val, i;

    if (size < MEPA_TS_FIFO_MAX_ENTRIES) {
        T_E(MEPA_TRACE_GRP_TS, "Size of Input TS list is less than 8\n");
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    for (i = 0; i < MEPA_TS_FIFO_MAX_ENTRIES; i++) {
        EP_RD_INCR(dev, INDY_PTP_TX_TS_NS_HI, &val, TRUE);

        if (val & INDY_PTP_TX_TS_NS_PTP_TX_TS_VALID) {
            ts_list[i].ts.nanoseconds = (((val) & 0x3fff) << 16);
            EP_RD_INCR(dev, INDY_PTP_TX_TS_NS_LO, &val, FALSE);
            ts_list[i].ts.nanoseconds = ts_list[i].ts.nanoseconds | val;

            EP_RD_INCR(dev, INDY_PTP_TX_TS_SEC_HI, &val, FALSE);
            ts_list[i].ts.seconds.low =  val;

            EP_RD_INCR(dev, INDY_PTP_TX_TS_SEC_LO, &val, FALSE);
            ts_list[i].ts.seconds.low = (ts_list[i].ts.seconds.low << 16) | val;
            ts_list[i].ts.seconds.high = 0;

            EP_RD_INCR(dev, INDY_PTP_TX_MSG_HEADER1, &val, FALSE);
            ts_list[i].sig.msg_type = val & 0xF;
            ts_list[i].sig.crc_src_port = val >> 4;
            ts_list[i].sig.has_crc_src = TRUE;

            EP_RD_INCR(dev, INDY_PTP_TX_MSG_HEADER2, &val, FALSE);
            ts_list[i].sig.sequence_id = val;
        } else {
            break;
        }
    }
    *num = i;
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_TS, "FIFO entries read = %d", *num);

    return MEPA_RC_OK;

    MEPA_EXIT(dev);
}

mepa_rc indy_ts_test_config(mepa_device_t *dev, uint16_t test_id, mepa_bool_t reg_dump)
{
    uint16_t ts_insert = 0, cf_update = 0, val = 0, tx_mod = 0, rx_mod = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_ts_classifier_t pkt_conf;
    mepa_device_t *base_dev = data->base_dev;
    mepa_rc rc = MEPA_RC_OK;
    mepa_ts_classifier_ptp_t ptp_class_conf = {};
    MEPA_ENTER(dev);
    if (base_dev == dev) {
        //EP_WRM(dev, INDY_PTP_LTC_SOFT_RESET, 0x1, INDY_DEF_MASK);
        // Enable 1PPS Output on channel A
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_SEC_HI_A, val, INDY_DEF_MASK);
        val = 0x2;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_SEC_LO_A, val, INDY_DEF_MASK);
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_NS_HI_A, val, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_LTC_TARGET_NS_LO_A, val, INDY_DEF_MASK);

        // Reload after every 1 sec
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_SEC_HI_A, val, INDY_DEF_MASK);
        val = 1;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_SEC_LO_A, val, INDY_DEF_MASK);
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_NS_HI_A, val, INDY_DEF_MASK);
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_NS_LO_A, val, INDY_DEF_MASK);

        // Enable 1PPS Output on channel B
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_SEC_HI_B, val, INDY_DEF_MASK);
        val = 0x2;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_SEC_LO_B, val, INDY_DEF_MASK);
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_NS_HI_B, val, INDY_DEF_MASK);
        EP_WRM(dev, INDY_PTP_LTC_TARGET_NS_LO_B, val, INDY_DEF_MASK);

        // Reload after every 0.5 sec
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_SEC_HI_B, val, INDY_DEF_MASK);
        val = 0;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_SEC_LO_B, val, INDY_DEF_MASK);
        val = 0x1DCD;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_NS_HI_B, val, INDY_DEF_MASK);
        val = 0x6500;
        EP_WRM(dev, INDY_PTP_LTC_TARGET_RELOAD_NS_LO_B, val, INDY_DEF_MASK);

        val = 0xE4A;
        EP_WRM(dev, INDY_PTP_GENERAL_CONFIG, val, INDY_DEF_MASK);

        // Enable PTP
        EP_RD(dev, INDY_PTP_CMD_CTL, &val);
        val = val | INDY_PTP_CMD_CTL_ENABLE;
        EP_WRM(dev, INDY_PTP_CMD_CTL, val, INDY_DEF_MASK);
    }

    val = 0;
    EP_WRM(dev, INDY_PTP_TSU_GEN_CONF, val, INDY_DEF_MASK);
    //Rx Classifier configuration
    memset(&pkt_conf, 0, sizeof(mepa_ts_classifier_t));

    pkt_conf.pkt_encap_type = MEPA_TS_ENCAP_ETH_IP_PTP;
    pkt_conf.ip_class_conf.ip_match_mode = MEPA_TS_IP_MATCH_NONE;
    pkt_conf.eth_class_conf.mac_match_select =  MEPA_TS_ETH_MATCH_NONE;
    pkt_conf.eth_class_conf.vlan_check = 0;
    ptp_class_conf.domain.mode = MEPA_TS_MATCH_MODE_RANGE;
    ptp_class_conf.domain.match.range.upper = 0xff;
    ptp_class_conf.domain.match.range.lower = 0x00;
    ptp_class_conf.version.lower = 0x2;
    ptp_class_conf.version.upper = 0x2;
    ptp_class_conf.minor_version.lower = 0x0;
    ptp_class_conf.minor_version.upper = 0x1;

    if ((rc = indy_ts_rx_classifier_conf_set_priv(dev, 0, &pkt_conf)) != MEPA_RC_OK) {
        MEPA_EXIT(dev);
        return rc;
    }

    //Tx Classifier configuration
    if ((rc = indy_ts_tx_classifier_conf_set_priv(dev, 0, &pkt_conf)) != MEPA_RC_OK) {
        MEPA_EXIT(dev);
        return rc;
    }

    if ((rc = indy_ts_classifier_ptp_conf_priv(dev, TRUE, &ptp_class_conf)) != MEPA_RC_OK) {
        MEPA_EXIT(dev);
        return rc;
    }
    if ((rc = indy_ts_classifier_ptp_conf_priv(dev, FALSE, &ptp_class_conf)) != MEPA_RC_OK) {
        MEPA_EXIT(dev);
        return rc;
    }
    // Rx Clock Configuration
    ts_insert = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
    cf_update = SYNC_PACKET | DELAY_REQ_PACKET | PDELAY_REQ_PACKET | PDELAY_RESP_PACKET;
    EP_WRM(dev, INDY_PTP_RX_TIMESTAMP_EN, ts_insert, INDY_DEF_MASK);
    EP_WRM(dev, INDY_PTP_RX_CF_MOD_EN, cf_update, INDY_DEF_MASK);
    val = 1;
    EP_WRM(dev, INDY_PTP_RX_CF_CFG, val, INDY_DEF_MASK);
    val = 0b0110;
    EP_WRM(dev, INDY_PTP_RX_TIMESTAMP_CONFIG, val, INDY_DEF_MASK);
    val = 0x0405;
    EP_WRM(dev, INDY_PTP_RX_RSVD_BYTE_CFG, val, INDY_DEF_MASK);
    rx_mod = rx_mod | INDY_PTP_RX_MOD_PTP_INSERT_TS_EN;
    EP_WRM(dev, INDY_PTP_RX_MOD, rx_mod, rx_mod);

    // Tx Clock Configuration
    EP_WRM(dev, INDY_PTP_TX_TIMESTAMP_EN, ts_insert, INDY_DEF_MASK);
    EP_WRM(dev, INDY_PTP_TX_CF_MOD_EN, cf_update, INDY_DEF_MASK);
    val = 1;
    EP_WRM(dev, INDY_PTP_TX_CF_CFG, val, INDY_DEF_MASK);
    val = 0b0110;
    EP_WRM(dev, INDY_PTP_TX_TIMESTAMP_CONFIG, val, INDY_DEF_MASK);
    tx_mod = tx_mod | INDY_PTP_TX_MOD_SYNC_TS_INSERT;
    EP_WRM(dev, INDY_PTP_TX_MOD, tx_mod, tx_mod);

    EP_RD(dev, INDY_PTP_CMD_CTL, &val);
    if (base_dev == dev) {
        // Enable PTP
        EP_RD(dev, INDY_PTP_CMD_CTL, &val);
        val = val | INDY_PTP_CMD_CTL_ENABLE;
        //EP_WRM(dev, INDY_PTP_CMD_CTL, val, INDY_DEF_MASK);
    }

    // Enable TSU
    val = 0;
    val = val | INDY_PTP_TSU_GEN_CONF_EN;
    EP_WRM(dev, INDY_PTP_TSU_GEN_CONF, val, INDY_DEF_MASK);
    if (reg_dump) {
        indy_ts_classifier_conf_reg_dump(dev, NULL);
        indy_ts_clock_conf_reg_dump(dev, NULL);
    }
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

mepa_rc indy_ts_debug_info_dump(struct mepa_device *dev,
                                    const mepa_debug_print_t pr,
                                    const mepa_debug_info_t   *const info)
{
    mepa_rc rc = MEPA_RC_OK;

    switch(info->group)
    {
        case MEPA_DEBUG_GROUP_ALL:
        case MEPA_DEBUG_GROUP_PHY_TS:
        {
            MEPA_ENTER(dev);
            indy_ts_classifier_conf_reg_dump(dev, pr);
            indy_ts_clock_conf_reg_dump(dev, pr);
            MEPA_EXIT(dev);
        }
        break;
        default:
            rc = MEPA_RC_OK;
    }
    return rc;
}

mepa_ts_driver_t indy_ts_drivers = {
    .mepa_ts_init_conf_get              = indy_ts_init_conf_get,
    .mepa_ts_init_conf_set              = indy_ts_init_conf_set,
    .mepa_ts_mode_get                   = indy_ts_mode_get,
    .mepa_ts_mode_set                   = indy_ts_mode_set,
    .mepa_ts_reset                      = indy_ts_reset,
    .mepa_ts_ltc_ls_en                  = indy_ts_ltc_ls_en_set,
    .mepa_ts_ltc_get                    = indy_ts_ltc_get,
    .mepa_ts_ltc_set                    = indy_ts_ltc_set,
    .mepa_ts_clock_rateadj_get          = indy_ts_clock_rateadj_get,
    .mepa_ts_clock_rateadj_set          = indy_ts_clock_rateadj_set,
    .mepa_ts_clock_adj1ns               = indy_ts_clock_adj1ns,
    .mepa_ts_delay_asymmetry_get        = indy_ts_clock_delay_asymmetry_get,
    .mepa_ts_delay_asymmetry_set        = indy_ts_clock_delay_asymmetry_set,
    .mepa_ts_path_delay_get             = indy_ts_clock_path_delay_get,
    .mepa_ts_path_delay_set             = indy_ts_clock_path_delay_set,
    .mepa_ts_egress_latency_get         = indy_ts_clock_egress_latency_get,
    .mepa_ts_egress_latency_set         = indy_ts_clock_egress_latency_set,
    .mepa_ts_ingress_latency_get        = indy_ts_clock_ingress_latency_get,
    .mepa_ts_ingress_latency_set        = indy_ts_clock_ingress_latency_set,
    .mepa_ts_rx_classifier_conf_get     = indy_ts_rx_classifier_conf_get,
    .mepa_ts_rx_classifier_conf_set     = indy_ts_rx_classifier_conf_set,
    .mepa_ts_tx_classifier_conf_get     = indy_ts_tx_classifier_conf_get,
    .mepa_ts_tx_classifier_conf_set     = indy_ts_tx_classifier_conf_set,
    .mepa_ts_rx_clock_conf_get          = indy_ts_rx_ptp_clock_conf_get,
    .mepa_ts_tx_clock_conf_get          = indy_ts_tx_ptp_clock_conf_get,
    .mepa_ts_rx_clock_conf_set          = indy_ts_rx_ptp_clock_conf_set,
    .mepa_ts_tx_clock_conf_set          = indy_ts_tx_ptp_clock_conf_set,
    .mepa_ts_pps_conf_get               = indy_ts_pps_conf_get,
    .mepa_ts_pps_conf_set               = indy_ts_pps_conf_set,
    .mepa_ts_stats_get                  = indy_ts_stats_get,
    .mepa_ts_event_get                  = indy_ts_event_get,
    .mepa_ts_event_set                  = indy_ts_event_set,
    .mepa_ts_event_poll                 = indy_ts_event_poll,
    .mepa_ts_fifo_read_install          = indy_ts_fifo_read_install,
    .mepa_ts_fifo_empty                 = indy_ts_tx_ts_get,
    .mepa_ts_test_config                = indy_ts_test_config,
    .mepa_ts_fifo_get                   = indy_ts_fifo_get,
};

