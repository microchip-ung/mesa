// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/board/api.h>
#include "meba_generic.h"

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

static mepa_rc meba_dev_chk(meba_inst_t inst, mepa_port_no_t port_no)
{
    mepa_device_t *phy_dev;
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return MESA_RC_OK;
}

mepa_rc meba_phy_ts_init_conf_get(meba_inst_t inst, mepa_port_no_t port_no,  mepa_ts_init_conf_t *const ts_init_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_init_conf_get(inst->phy_devices[port_no], ts_init_conf);
}

mepa_rc meba_phy_ts_init_conf_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_init_conf_t *ts_init_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_init_conf_set(inst->phy_devices[port_no], ts_init_conf);
}

mepa_rc meba_phy_ts_mode_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_bool_t *const enable)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_mode_get(inst->phy_devices[port_no], enable);
}

mepa_rc meba_phy_ts_mode_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t enable)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_mode_set(inst->phy_devices[port_no], enable);
}

mepa_rc meba_phy_ts_ltc_ls_en(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_ls_type_t ls_cmd)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_ltc_ls_en(inst->phy_devices[port_no], ls_cmd);
}

mepa_rc meba_phy_ts_ltc_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timestamp_t *const ts)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_ltc_set(inst->phy_devices[port_no], ts);
}

mepa_rc meba_phy_ts_ltc_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timestamp_t *const ts)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_ltc_get(inst->phy_devices[port_no], ts);
}

mepa_rc meba_phy_ts_delay_asymmetry_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const delay_asym)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_delay_asymmetry_get(inst->phy_devices[port_no], delay_asym);
}

mepa_rc meba_phy_ts_delay_asymmetry_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const delay_asym)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_delay_asymmetry_set(inst->phy_devices[port_no], delay_asym);
}

mepa_rc meba_phy_ts_path_delay_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const path_delay)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_path_delay_get(inst->phy_devices[port_no], path_delay);
}

mepa_rc meba_phy_ts_path_delay_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const path_delay)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_path_delay_set(inst->phy_devices[port_no], path_delay);
}

mepa_rc meba_phy_ts_egress_latency_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const latency)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_egress_latency_get(inst->phy_devices[port_no], latency);
}

mepa_rc meba_phy_ts_egress_latency_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const latency)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_egress_latency_set(inst->phy_devices[port_no], latency);
}

mepa_rc meba_phy_ts_ingress_latency_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const latency)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_ingress_latency_get(inst->phy_devices[port_no], latency);
}

mepa_rc meba_phy_ts_ingress_latency_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const latency)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_ingress_latency_set(inst->phy_devices[port_no], latency);
}

mepa_rc meba_phy_ts_clock_rateadj_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_scaled_ppb_t *const rateadj)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_clock_rateadj_get(inst->phy_devices[port_no], rateadj);
}

mepa_rc meba_phy_ts_clock_rateadj_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_scaled_ppb_t *const rateadj)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_clock_rateadj_set(inst->phy_devices[port_no], rateadj);
}

mepa_rc meba_phy_ts_clock_adj1ns(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t incr)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_clock_adj1ns(inst->phy_devices[port_no], incr);
}

mepa_rc meba_phy_ts_rx_classifier_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, mepa_ts_classifier_t *const pkt_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_rx_classifier_conf_get(inst->phy_devices[port_no], flow_index, pkt_conf);
}

mepa_rc meba_phy_ts_rx_classifier_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, const mepa_ts_classifier_t *pkt_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_rx_classifier_conf_set(inst->phy_devices[port_no], flow_index, pkt_conf);
}

mepa_rc meba_phy_ts_tx_classifier_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, mepa_ts_classifier_t *const pkt_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_I(inst, "Called port %d", port_no);
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_tx_classifier_conf_get(inst->phy_devices[port_no], flow_index, pkt_conf);
}


mepa_rc meba_phy_ts_tx_classifier_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, const mepa_ts_classifier_t *pkt_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_tx_classifier_conf_set(inst->phy_devices[port_no], flow_index, pkt_conf);
}
mepa_rc meba_phy_ts_rx_clock_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_rx_clock_conf_get(inst->phy_devices[port_no], clock_id, ptpclock_conf);
}

mepa_rc meba_phy_ts_tx_clock_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_tx_clock_conf_get(inst->phy_devices[port_no], clock_id, ptpclock_conf);
}

mepa_rc meba_phy_ts_rx_clock_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_rx_clock_conf_set(inst->phy_devices[port_no], clock_id, ptpclock_conf);
}

mepa_rc meba_phy_ts_tx_clock_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_tx_clock_conf_set(inst->phy_devices[port_no], clock_id, ptpclock_conf);
}


mepa_rc meba_phy_ts_pps_conf_get(meba_inst_t inst, mepa_port_no_t port_no,
                                 mepa_ts_pps_conf_t *const phy_pps_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_pps_conf_get(inst->phy_devices[port_no], phy_pps_conf);
}


mepa_rc meba_phy_ts_pps_conf_set(meba_inst_t inst, mepa_port_no_t port_no,
                                 const mepa_ts_pps_conf_t *const phy_pps_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_pps_conf_set(inst->phy_devices[port_no], phy_pps_conf);
}

mepa_rc meba_phy_ts_stats_get(meba_inst_t inst, mepa_port_no_t port_no,
                              mepa_ts_stats_t *const statistics)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_stats_get(inst->phy_devices[port_no], statistics);
}

mepa_rc meba_phy_ts_event_get(meba_inst_t inst, mepa_port_no_t port_no,
                              mepa_ts_event_t *const ev_mask)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_event_get(inst->phy_devices[port_no], ev_mask);
}

mepa_rc meba_phy_ts_event_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t enable, const mepa_ts_event_t ev_mask)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_event_set(inst->phy_devices[port_no], enable, ev_mask);
}


mepa_rc meba_phy_ts_event_poll(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_event_t *const status)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_event_poll(inst->phy_devices[port_no], status);
}

mepa_rc meba_phy_ts_test_config(meba_inst_t inst, mepa_port_no_t port_no, uint16_t test_id, mepa_bool_t reg_dump)
{
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_test_config(inst->phy_devices[port_no], test_id, reg_dump);
}

mepa_rc meba_phy_ts_fifo_read_install(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_fifo_read_t rd_cb)
{
    mepa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_fifo_read_install(inst->phy_devices[port_no], rd_cb);
}

mepa_rc meba_phy_ts_fifo_empty(meba_inst_t inst, mepa_port_no_t port_no)
{
    mepa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_fifo_empty(inst->phy_devices[port_no]);
}

mepa_rc meba_phy_ts_fifo_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_fifo_ts_entry_t ts_list[], const size_t size, uint32_t *const num)
{
    mepa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_ts_fifo_get(inst->phy_devices[port_no], ts_list, size, num);
}
