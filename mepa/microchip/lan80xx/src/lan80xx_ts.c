// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>
#include "lan80xx_private.h"
#include "lan80xx_ts_private.h"
#include "lan80xx_types.h"
#include "regs_lan80xx.h"
#include <lan80xx_ts.h>


uint8_t lan80xx_get_vs_addr_type(mepa_ts_mac_match_mode_t mac_match)
{
    uint8_t ret = 0;
    switch (mac_match) {
    case MEPA_TS_ETH_ADDR_MATCH_48BIT:
        ret = LAN80XX_PHY_TS_ETH_ADDR_MATCH_48BIT;
        break;
    case MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST:
        ret = LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST;
        break;
    case MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST:
        ret = LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST;
        break;
    case MEPA_TS_ETH_ADDR_MATCH_ANY:
    default:
        ret = LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST | MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST;
        break;
    }
    return ret;
}

uint8_t lan80xx_get_vs_mac_type(mepa_ts_mac_match_select_t mac_type)
{
    uint8_t ret;
    switch (mac_type) {
    case MEPA_TS_ETH_MATCH_DEST_ADDR:
        ret = LAN80XX_PHY_TS_ETH_MATCH_DEST_ADDR;
        break;
    case MEPA_TS_ETH_MATCH_SRC_ADDR:
        ret = LAN80XX_PHY_TS_ETH_MATCH_SRC_ADDR;
        break;
    case MEPA_TS_ETH_MATCH_SRC_OR_DEST:
        ret = LAN80XX_PHY_TS_ETH_MATCH_SRC_OR_DEST;
        break;
    default:
        ret = LAN80XX_PHY_TS_ETH_MATCH_NONE;
        break;
    }
    return ret;
}


uint8_t lan80xx_get_vs_ntw_type(mepa_ts_ip_match_select_t ntw_type)
{
    uint8_t ret;
    switch (ntw_type) {
    case MEPA_TS_IP_MATCH_DEST:
        ret = LAN80XX_PHY_TS_IP_MATCH_DEST;
        break;
    case MEPA_TS_IP_MATCH_SRC:
        ret = LAN80XX_PHY_TS_IP_MATCH_SRC;
        break;
    case MEPA_TS_IP_MATCH_SRC_OR_DEST:
        ret = LAN80XX_PHY_TS_IP_MATCH_SRC_OR_DEST;
        break;
    default:
        ret = LAN80XX_PHY_TS_IP_MATCH_NONE;
        break;
    }
    return ret;
}

mepa_rc mepa_to_lan80xx_encap(mepa_ts_pkt_encap_t encap, phy25g_ts_encap_t *phy25g_encap)
{
    mepa_rc rc = MEPA_RC_OK;
    switch (encap) {
    case MEPA_TS_ENCAP_ETH_PTP:
        *phy25g_encap = LAN80XX_PHY_TS_ENCAP_ETH_PTP;
        break;

    case MEPA_TS_ENCAP_ETH_IP_PTP:
        *phy25g_encap = LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP;
        break;

    case MEPA_TS_ENCAP_ETH_ETH_PTP:
        *phy25g_encap = LAN80XX_PHY_TS_ENCAP_ETH_ETH_PTP;
        break;

    case MEPA_TS_ENCAP_ETH_ETH_IP_PTP:
        *phy25g_encap = LAN80XX_PHY_TS_ENCAP_ETH_ETH_IP_PTP;
        break;

    case  MEPA_TS_ENCAP_ETH_MPLS_IP_PTP:
        *phy25g_encap = LAN80XX_PHY_TS_ENCAP_ETH_MPLS_IP_PTP;
        break;

    case MEPA_TS_ENCAP_ETH_MPLS_ETH_PTP:
        *phy25g_encap = LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP;
        break;

    case MEPA_TS_ENCAP_ETH_MPLS_ETH_IP_PTP:
        *phy25g_encap = LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP;
        break;

    case MEPA_TS_ENCAP_NONE:
        *phy25g_encap = LAN80XX_PHY_TS_ENCAP_NONE;
        break;

    default:
        rc = MEPA_RC_ERROR;
        break;
    }
    return rc;
}

mepa_ts_pkt_encap_t lan80xx_to_mepa_encap(phy25g_ts_encap_t phy25g_encap)
{
    switch (phy25g_encap) {
    case LAN80XX_PHY_TS_ENCAP_ETH_PTP:
        return MEPA_TS_ENCAP_ETH_PTP;
    case LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP:
        return MEPA_TS_ENCAP_ETH_IP_PTP;
    case LAN80XX_PHY_TS_ENCAP_ETH_IP_IP_PTP:
        return MEPA_TS_ENCAP_ETH_IP_IP_PTP;
    case LAN80XX_PHY_TS_ENCAP_ETH_ETH_PTP:
        return MEPA_TS_ENCAP_ETH_ETH_PTP;
    case LAN80XX_PHY_TS_ENCAP_ETH_ETH_IP_PTP:
        return MEPA_TS_ENCAP_ETH_ETH_IP_PTP;
    case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_IP_PTP:
        return MEPA_TS_ENCAP_ETH_MPLS_IP_PTP;
    case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP:
        return MEPA_TS_ENCAP_ETH_MPLS_ETH_PTP;
    case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP:
        return MEPA_TS_ENCAP_ETH_MPLS_ETH_IP_PTP;
    case LAN80XX_PHY_TS_ENCAP_NONE:
        return MEPA_TS_ENCAP_NONE;
    default:
        return MEPA_TS_ENCAP_NONE; // or MEPA_TS_ENCAP_INVALID if defined
    }
}


phy25g_ptp_action_type_t mepa_to_lan80xx_ls_action(mepa_ts_ls_type_t ls_type)
{
    phy25g_ptp_action_type_t ls_action = LAN80XX_TS_CMD_IDLE;

    if (ls_type == MEPA_TS_CMD_LOAD) {
        return LAN80XX_TS_CMD_LOAD;
    } else if (ls_type == MEPA_TS_CMD_SAVE) {
        return LAN80XX_TS_CMD_STORE;
    } else if (ls_type == MEPA_TS_CMD_DELTA) {
        return  LAN80XX_TS_CMD_DELTA;
    } else if (ls_type == MEPA_TS_CMD_TOD) {
        return LAN80XX_TS_CMD_TOD;
    }

    return ls_action;
}


static mepa_rc lan80xx_ts_reset(mepa_device_t *dev, const mepa_ts_reset_conf_t *const tsreset)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_ts_reset_priv(dev, tsreset);
    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan80xx_ts_init_conf_get(mepa_device_t *dev, mepa_ts_init_conf_t *const ts_init_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    mepa_bool_t                     ts_init_done = FALSE;
    phy25g_phy_ts_init_conf_t         init_conf = {0};
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    memset(ts_init_conf, 0 , sizeof(mepa_ts_init_conf_t));

    MEPA_ENTER(dev);
    rc =  lan80xx_phy_ts_init_conf_get(dev, data->port_no, &ts_init_done, &init_conf);

    if (ts_init_done == TRUE) {
        switch (init_conf.clk_src) {
        case LAN80XX_PHY_TS_CLOCK_SRC_SYSREFCLK:
            ts_init_conf->clk_src = MEPA_TS_CLOCK_SRC_INTERNAL;
            break;
        case LAN80XX_PHY_TS_CLOCK_SRC_LINE0:
            ts_init_conf->clk_src = MEPA_TS_CLOCK_SRC_FROM_RX_PORT0;
            break;
        case LAN80XX_PHY_TS_CLOCK_SRC_LINE1:
            ts_init_conf->clk_src = MEPA_TS_CLOCK_SRC_FROM_RX_PORT1;
            break;
        case LAN80XX_PHY_TS_CLOCK_SRC_LINE2:
            ts_init_conf->clk_src = MEPA_TS_CLOCK_SRC_FROM_RX_PORT2;
            break;
        case LAN80XX_PHY_TS_CLOCK_SRC_LINE3:
            ts_init_conf->clk_src = MEPA_TS_CLOCK_SRC_FROM_RX_PORT3;
            break;
        case LAN80XX_PHY_TS_CLOCK_SRC_EXTERNAL_25MHZ:
            ts_init_conf->clk_src = MEPA_TS_CLOCK_SRC_EXTERNAL;
            break;
        default:
            T_E(MEPA_TRACE_GRP_TS, "Not a valide clock src %s:  %d\n", __func__, ts_init_conf->clk_src);
            /* We don't return error here, as get function just fetch existing config */
        }
        ts_init_conf->clk_freq          = init_conf.clk_freq;
        ts_init_conf->rx_ts_len         = init_conf.rx_ts_len == LAN80XX_PHY_TS_RX_TIMESTAMP_LEN_30BIT ? MEPA_TS_RX_TIMESTAMP_LEN_30BIT : MEPA_TS_RX_TIMESTAMP_LEN_32BIT;
        ts_init_conf->rx_ts_pos         = init_conf.rx_ts_pos == LAN80XX_PHY_TS_RX_TIMESTAMP_POS_AT_END ? MEPA_TS_RX_TIMESTAMP_POS_AT_END : MEPA_TS_RX_TIMESTAMP_POS_IN_PTP;
        ts_init_conf->tx_fifo_mode      = init_conf.tx_fifo_mode;
        ts_init_conf->tx_fifo_spi_conf  = init_conf.tx_fifo_spi_conf;
        ts_init_conf->tx_ts_len         = init_conf.tx_ts_len == LAN80XX_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE ? MEPA_TS_FIFO_TIMESTAMP_LEN_10BYTE : MEPA_TS_FIFO_TIMESTAMP_LEN_4BYTE;
        ts_init_conf->auto_clear_ls     = init_conf.auto_clear_ls;
        ts_init_conf->dly_req_recv_10byte_ts = data->ts.dly_req_recv_10byte_ts;
        ts_init_conf->tc_op_mode        = init_conf.tc_op_mode;
        ts_init_conf->mch_pch_conf      = init_conf.mch_conf;
    } else {
        ts_init_conf->clk_src           = MEPA_TS_CLOCK_SRC_NONE;
        ts_init_conf->clk_freq          = MEPA_TS_CLOCK_FREQ_NONE;
    }
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_init_conf_set(mepa_device_t *dev, const mepa_ts_init_conf_t *const ts_init_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_rc rc = MEPA_RC_ERROR;

    if (base_data->features.ptp_1588_disable != 0U) {
        T_E(MEPA_TRACE_GRP_TS, "\n PHY SKU on port : %d doesn't support PTP", data->port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);

    phy25g_phy_ts_init_conf_t init_conf = {0};

    switch (ts_init_conf->clk_src) {
    case MEPA_TS_CLOCK_SRC_INTERNAL:
        init_conf.clk_src =  LAN80XX_PHY_TS_CLOCK_SRC_SYSREFCLK;
        break;
    case MEPA_TS_CLOCK_SRC_FROM_RX_PORT0:
        init_conf.clk_src =  LAN80XX_PHY_TS_CLOCK_SRC_LINE0;
        break;
    case MEPA_TS_CLOCK_SRC_FROM_RX_PORT1:
        init_conf.clk_src =  LAN80XX_PHY_TS_CLOCK_SRC_LINE1;
        break;
    case MEPA_TS_CLOCK_SRC_FROM_RX_PORT2:
        init_conf.clk_src =  LAN80XX_PHY_TS_CLOCK_SRC_LINE2;
        break;
    case MEPA_TS_CLOCK_SRC_FROM_RX_PORT3:
        init_conf.clk_src =  LAN80XX_PHY_TS_CLOCK_SRC_LINE3;
        break;
    case MEPA_TS_CLOCK_SRC_EXT_1588_REF_CLOCK:
    case MEPA_TS_CLOCK_SRC_EXTERNAL:
        init_conf.clk_src = LAN80XX_PHY_TS_CLOCK_SRC_EXTERNAL_25MHZ;
        break;

    default:
        T_E(MEPA_TRACE_GRP_TS, "Not a valide clock src %s:  %d\n", __FUNCTION__, ts_init_conf->clk_src);
        MEPA_EXIT(dev);
        return MEPA_RC_ERROR;
    }
    init_conf.clk_freq         = ts_init_conf->clk_freq;
    init_conf.rx_ts_len        = (ts_init_conf->rx_ts_len == MEPA_TS_RX_TIMESTAMP_LEN_30BIT) ? LAN80XX_PHY_TS_RX_TIMESTAMP_LEN_30BIT : LAN80XX_PHY_TS_RX_TIMESTAMP_LEN_32BIT;
    init_conf.rx_ts_pos        = (ts_init_conf->rx_ts_pos == MEPA_TS_RX_TIMESTAMP_POS_AT_END) ? LAN80XX_PHY_TS_RX_TIMESTAMP_POS_AT_END : LAN80XX_PHY_TS_RX_TIMESTAMP_POS_IN_PTP;
    init_conf.tx_fifo_mode     = ts_init_conf->tx_fifo_mode;
    init_conf.tx_ts_len        = (ts_init_conf->tx_ts_len == MEPA_TS_FIFO_TIMESTAMP_LEN_10BYTE) ? LAN80XX_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE : LAN80XX_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE;
    init_conf.tx_fifo_spi_conf = ts_init_conf->tx_fifo_spi_conf;
    init_conf.auto_clear_ls    = ts_init_conf->auto_clear_ls;
    init_conf.tc_op_mode       = mepa_to_lan80xx_tc_opmode(ts_init_conf->tc_op_mode);
    init_conf.chk_ing_modified = FALSE;
    init_conf.one_step_txfifo  = FALSE;
    init_conf.mch_conf         = ts_init_conf->mch_pch_conf;

    rc = lan80xx_phy_ts_init(dev, data->port_no, &init_conf);

    if (data->phy_ts_port_conf.port_ts_init_done == TRUE) {
        data->ts.dly_req_recv_10byte_ts = ts_init_conf->dly_req_recv_10byte_ts;
    }
    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan80xx_ts_tx_classifier_conf_set(struct mepa_device *dev,
                                                 uint16_t flow_index,
                                                 const mepa_ts_classifier_t *const pkt_class_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_tx_classifier_conf_set_priv(dev, flow_index, pkt_class_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_tx_classifier_conf_get(mepa_device_t *dev,
                                                 uint16_t in_flow,
                                                 mepa_ts_classifier_t *const out_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_tx_classifier_conf_get_priv(dev, in_flow, out_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_rx_classifier_conf_set(struct mepa_device *dev,
                                                 uint16_t flow_index,
                                                 const mepa_ts_classifier_t *const pkt_class_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_rx_classifier_conf_set_priv(dev, flow_index, pkt_class_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_rx_classifier_conf_get(mepa_device_t *dev, uint16_t in_flow,
                                                 mepa_ts_classifier_t *const out_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_rx_classifier_conf_get_priv(dev, in_flow, out_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_tx_clock_conf_set(struct mepa_device *dev,
                                            uint16_t clock_id,
                                            const mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_tx_clock_conf_set_priv(dev, clock_id, ptpclock_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_rx_clock_conf_set(struct mepa_device *dev,
                                            uint16_t clock_id,
                                            const mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_rx_clock_conf_set_priv(dev, clock_id, ptpclock_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_tx_clock_conf_get(mepa_device_t *dev, uint16_t clock_id,
                                            mepa_ts_ptp_clock_conf_t *const clk_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_tx_clock_conf_get_priv(dev, clock_id, clk_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_rx_clock_conf_get(mepa_device_t *dev, uint16_t clock_id,
                                            mepa_ts_ptp_clock_conf_t *const clk_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_rx_clock_conf_get_priv(dev, clock_id, clk_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_ltc_ls_en(mepa_device_t *dev, mepa_ts_ls_type_t const ls_type)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ptp_action_type_t ltc_ls_action;
    mesa_rc rc = MEPA_RC_OK;

    MEPA_ENTER(dev);
    ltc_ls_action = mepa_to_lan80xx_ls_action(ls_type);
    rc = lan80xx_phy_ts_ltc_ls_action_set(dev, data->port_no, ltc_ls_action);
    MEPA_EXIT(dev);

    return rc;

}

static mepa_rc lan80xx_ts_mode_get(mepa_device_t *dev, mepa_bool_t *const enable)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_ts_mode_get_priv(dev, enable);
    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan80xx_ts_mode_set(mepa_device_t *dev, const mepa_bool_t enable)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_ts_mode_set_priv(dev, enable);
    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan80xx_ts_ltc_get(mepa_device_t *dev, mepa_timestamp_t *const ts)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    MEPA_ENTER(dev);
    u32 value = 0;

    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_PTP_LTC_PTP_TOD_NSEC(base_data->lsc_select), &value);
    ts->nanoseconds = (value & 0x3fffffff);

    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_PTP_LTC_PTP_TOD_NSEC_FRAC(base_data->lsc_select), &value);
    ts->picoseconds = (value & 0xff);

    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_PTP_LTC_PTP_TOD_SEC_LSB(base_data->lsc_select), &value);
    ts->seconds.low = (value & 0xffffffff);

    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_PTP_LTC_PTP_TOD_SEC_MSB(base_data->lsc_select), &value);
    ts->seconds.high = (value & 0xffff) ;

    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_ts_ltc_set(mepa_device_t *dev, const mepa_timestamp_t *const ts)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_timestamp_t m25gts;
    mepa_rc rc = MEPA_RC_ERROR;

    m25gts.seconds.high = ts->seconds.high;
    m25gts.seconds.low = ts->seconds.low;
    m25gts.nanoseconds = ts->nanoseconds;
    m25gts.subnanoseconds  = ts->picoseconds;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_csr_ptptime_set_priv(dev, data->port_no, &m25gts);
    MEPA_EXIT(dev);

    return rc;
}

static void lan80xx_ts_fifo_read_install(mepa_device_t  *dev, mepa_ts_fifo_read_t rd_cb)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    MEPA_ENTER(dev);
    data->ts_fifo_cb = rd_cb;
    MEPA_EXIT(dev);
    return;
}

static mepa_rc lan80xx_ts_fifo_empty(mepa_device_t  *dev)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_fifo_empty(dev, data->port_no, NULL, NULL, TRUE);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_fifo_get(mepa_device_t *dev, mepa_fifo_ts_entry_t ts_list[], const size_t size, uint32_t *const num)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;
    MEPA_ENTER(dev);
    do {
        if (num == NULL) {
            T_E(MEPA_TRACE_GRP_TS, "Invalid argument\n");
            rc = MEPA_RC_ERROR;
            break;
        }

        if (size < LAN80XX_PHY_TS_FIFO_MAX_ENTRIES) {
            T_E(MEPA_TRACE_GRP_TS, "Size of Input TS list is less than 16\n");
            rc = MEPA_RC_ERROR;
            break;
        }

        if (lan80xx_phy_ts_fifo_get(dev, data->port_no, ts_list, LAN80XX_PHY_TS_FIFO_MAX_ENTRIES, num) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_TS, "Failed to get FIFO entries!!\n");
            rc = MEPA_RC_ERROR;
        }
    } while (0);
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_ts_clock_path_delay_get(mepa_device_t *dev, mepa_timeinterval_t *const path_delay)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    return lan80xx_phy_ts_path_delay_get(dev, data->port_no, path_delay);
}

static mepa_rc lan80xx_ts_clock_path_delay_set(mepa_device_t *dev, const mepa_timeinterval_t *const path_delay)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    return lan80xx_phy_ts_path_delay_set(dev, data->port_no, path_delay);
}


static mepa_rc lan80xx_ts_clock_delay_asymmetry_get(mepa_device_t *dev, mepa_timeinterval_t *const delay_asym)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_delay_asymmetry_get(dev, data->port_no, delay_asym);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_clock_delay_asymmetry_set(mepa_device_t *dev, const mepa_timeinterval_t *const delay_asym)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_delay_asymmetry_set(dev, data->port_no, delay_asym);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_clock_rateadj_get(mepa_device_t *dev, mepa_ts_scaled_ppb_t *const adj)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_clock_rateadj_get(dev, data->port_no, adj);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_clock_rateadj_set(mepa_device_t *dev, const mepa_ts_scaled_ppb_t *const adj)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_clock_rateadj_set(dev, data->port_no, adj);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_clock_egress_latency_get(mepa_device_t *dev, mepa_timeinterval_t *const latency)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_egress_latency_get(dev, data->port_no, latency);
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_ts_clock_egress_latency_set(mepa_device_t *dev, const mepa_timeinterval_t *const latency)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_egress_latency_set(dev, data->port_no, latency);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_clock_ingress_latency_get(mepa_device_t *dev, mepa_timeinterval_t *const latency)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_ingress_latency_get(dev, data->port_no, latency);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_clock_ingress_latency_set(mepa_device_t *dev, const mepa_timeinterval_t *const latency)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_ingress_latency_set(dev, data->port_no, latency);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_stats_get(mepa_device_t *dev, mepa_ts_stats_t *const statistics)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_ts_stats_t stats;
    mesa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    if ((rc = lan80xx_phy_ts_stats_get(dev, data->port_no, &stats)) == MEPA_RC_OK) {
        statistics->ingr_pream_shrink_err = stats.ingr_pream_shrink_err;
        statistics->egr_pream_shrink_err = stats.egr_pream_shrink_err;
        statistics->ingr_fcs_err         = stats.ingr_fcs_err;
        statistics->egr_fcs_err          = stats.egr_fcs_err;
        statistics->ingr_frm_mod_cnt     = stats.ingr_frm_mod_cnt;
        statistics->egr_frm_mod_cnt      = stats.egr_frm_mod_cnt;
        statistics->ts_fifo_tx_cnt       = stats.ts_fifo_tx_cnt;
        statistics->ts_fifo_drop_cnt     = stats.ts_fifo_drop_cnt;
    }
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_ts_event_get(mepa_device_t *dev, mepa_ts_event_t *const ev_mask)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_event_enable_get(dev, data->port_no, ev_mask);
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_ts_event_set(mepa_device_t *dev, const mepa_bool_t enable, const mepa_ts_event_t ev_mask)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_event_enable_set(dev, data->port_no, enable, ev_mask);
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_ts_event_poll(mepa_device_t *dev, mepa_ts_event_t  *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = lan80xx_phy_ts_event_poll(dev, data->port_no, status);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_pps_conf_set(mepa_device_t *dev, const mepa_ts_pps_conf_t *const phy_pps_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_pps_conf_set_priv(dev, phy_pps_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_ts_pps_conf_get(mepa_device_t *dev, mepa_ts_pps_conf_t *const phy_pps_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_ts_pps_conf_get_priv(dev, phy_pps_conf);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_fifo_sig_set(mepa_device_t  *dev, const mepa_port_no_t  port_no, const phy25g_ts_fifo_sig_mask_t   sig_mask)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_phy_ts_fifo_sig_set_priv(dev, port_no, sig_mask);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_fifo_sig_get(mepa_device_t  *dev, const mepa_port_no_t  port_no, phy25g_ts_fifo_sig_mask_t   *sig_mask)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_phy_ts_fifo_sig_get_priv(dev, port_no, sig_mask);
    MEPA_EXIT(dev);
    return rc;
}

mepa_ts_driver_t lan80xx_ts_drivers = {
    .mepa_ts_reset                      = lan80xx_ts_reset,
    .mepa_ts_init_conf_get              = lan80xx_ts_init_conf_get,
    .mepa_ts_init_conf_set              = lan80xx_ts_init_conf_set,
    .mepa_ts_mode_get                   = lan80xx_ts_mode_get,
    .mepa_ts_mode_set                   = lan80xx_ts_mode_set,
    .mepa_ts_tx_classifier_conf_set     = lan80xx_ts_tx_classifier_conf_set,
    .mepa_ts_tx_classifier_conf_get     = lan80xx_ts_tx_classifier_conf_get,
    .mepa_ts_rx_classifier_conf_set     = lan80xx_ts_rx_classifier_conf_set,
    .mepa_ts_rx_classifier_conf_get     = lan80xx_ts_rx_classifier_conf_get,
    .mepa_ts_tx_clock_conf_set          = lan80xx_ts_tx_clock_conf_set,
    .mepa_ts_tx_clock_conf_get          = lan80xx_ts_tx_clock_conf_get,
    .mepa_ts_rx_clock_conf_set          = lan80xx_ts_rx_clock_conf_set,
    .mepa_ts_rx_clock_conf_get          = lan80xx_ts_rx_clock_conf_get,
    .mepa_ts_fifo_read_install          = lan80xx_ts_fifo_read_install,
    .mepa_ts_fifo_empty                 = lan80xx_ts_fifo_empty,
    .mepa_ts_fifo_get                   = lan80xx_ts_fifo_get,
    .mepa_ts_ltc_get                    = lan80xx_ts_ltc_get,
    .mepa_ts_ltc_set                    = lan80xx_ts_ltc_set,
    .mepa_ts_ltc_ls_en                  = lan80xx_ts_ltc_ls_en,
    .mepa_ts_delay_asymmetry_get        = lan80xx_ts_clock_delay_asymmetry_get,
    .mepa_ts_delay_asymmetry_set        = lan80xx_ts_clock_delay_asymmetry_set,
    .mepa_ts_path_delay_get             = lan80xx_ts_clock_path_delay_get,
    .mepa_ts_path_delay_set             = lan80xx_ts_clock_path_delay_set,
    .mepa_ts_clock_rateadj_get          = lan80xx_ts_clock_rateadj_get,
    .mepa_ts_clock_rateadj_set          = lan80xx_ts_clock_rateadj_set,
    .mepa_ts_egress_latency_get         = lan80xx_ts_clock_egress_latency_get,
    .mepa_ts_egress_latency_set         = lan80xx_ts_clock_egress_latency_set,
    .mepa_ts_ingress_latency_get        = lan80xx_ts_clock_ingress_latency_get,
    .mepa_ts_ingress_latency_set        = lan80xx_ts_clock_ingress_latency_set,
    .mepa_ts_pps_conf_set               = lan80xx_ts_pps_conf_set,
    .mepa_ts_clock_adj1ns               = NULL,
    .mepa_ts_pps_conf_get               = lan80xx_ts_pps_conf_get,
    .mepa_ts_stats_get                  = lan80xx_ts_stats_get,
    .mepa_ts_event_get                  = lan80xx_ts_event_get,
    .mepa_ts_event_set                  = lan80xx_ts_event_set,
    .mepa_ts_event_poll                 = lan80xx_ts_event_poll,
};
