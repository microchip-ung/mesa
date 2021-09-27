// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/phy/api/phy.h>
#include <microchip/ethernet/phy/api/phy_ts.h>
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
    if(!phy_dev->drv->mepa_ts){
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return MESA_RC_OK;
}

mepa_rc meba_phy_ts_init_conf_get(meba_inst_t inst, mepa_port_no_t port_no,  mepa_ts_init_conf_t *const ts_init_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

	T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if ( !phy_dev->drv->mepa_ts->mepa_ts_init_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_init_conf_get(phy_dev, ts_init_conf);

}

mepa_rc meba_phy_ts_init_conf_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_init_conf_t *ts_init_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

	T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if ( !phy_dev->drv->mepa_ts->mepa_ts_init_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_init_conf_set(phy_dev, ts_init_conf);

}

mepa_rc meba_phy_ts_mode_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_bool_t *const enable)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if ( !phy_dev->drv->mepa_ts->mepa_ts_mode_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_mode_get(phy_dev, enable);
}

mepa_rc meba_phy_ts_mode_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t enable)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if ( !phy_dev->drv->mepa_ts->mepa_ts_mode_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_mode_set(phy_dev, enable);
}

mepa_rc meba_phy_ts_ltc_ls_en(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_ls_type_t ls_cmd)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_ltc_ls_en) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_ltc_ls_en(phy_dev, ls_cmd);
}

mepa_rc meba_phy_ts_ltc_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timestamp_t *const ts)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_ltc_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_ltc_set(phy_dev, ts);
}

mepa_rc meba_phy_ts_ltc_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timestamp_t *const ts)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_ltc_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_ltc_get(phy_dev, ts);
}

mepa_rc meba_phy_ts_delay_asymmetry_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const delay_asym)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_delay_asymmetry_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_delay_asymmetry_get(phy_dev, delay_asym);
}

mepa_rc meba_phy_ts_delay_asymmetry_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const delay_asym)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_delay_asymmetry_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_delay_asymmetry_set(phy_dev, delay_asym);
}

mepa_rc meba_phy_ts_path_delay_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const path_delay)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_path_delay_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_path_delay_get(phy_dev, path_delay);
}

mepa_rc meba_phy_ts_path_delay_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const path_delay)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_path_delay_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_path_delay_set(phy_dev, path_delay);
}

mepa_rc meba_phy_ts_egress_latency_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const latency)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_egress_latency_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_egress_latency_get(phy_dev, latency);
}

mepa_rc meba_phy_ts_egress_latency_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const latency)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_egress_latency_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_egress_latency_set(phy_dev, latency);
}

mepa_rc meba_phy_ts_ingress_latency_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const latency)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_ingress_latency_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_ingress_latency_get(phy_dev, latency);
}

mepa_rc meba_phy_ts_ingress_latency_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const latency)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_ingress_latency_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_ingress_latency_set(phy_dev, latency);
}

mepa_rc meba_phy_ts_clock_rateadj_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_scaled_ppb_t *const rateadj)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_clock_rateadj_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_clock_rateadj_get(phy_dev, rateadj);
}

mepa_rc meba_phy_ts_clock_rateadj_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_scaled_ppb_t *const rateadj)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_clock_rateadj_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_clock_rateadj_set(phy_dev, rateadj);
}

mepa_rc meba_phy_ts_clock_adj1ns(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t incr)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_clock_adj1ns) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_clock_adj1ns(phy_dev, incr);
}

mepa_rc meba_phy_ts_rx_classifier_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, mepa_ts_classifier_t *const pkt_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_get(phy_dev, flow_index, pkt_conf);
}

mepa_rc meba_phy_ts_rx_classifier_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, const mepa_ts_classifier_t *pkt_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_set(phy_dev, flow_index, pkt_conf);
}

mepa_rc meba_phy_ts_tx_classifier_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, mepa_ts_classifier_t *const pkt_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_I(inst, "Called port %d", port_no);
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    T_I(inst, "Called port %d", port_no);
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    T_I(inst, "Called port %d", port_no);
    return phy_dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_get(phy_dev, flow_index, pkt_conf);
}


mepa_rc meba_phy_ts_tx_classifier_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, const mepa_ts_classifier_t *pkt_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_set(phy_dev, flow_index, pkt_conf);
}
mepa_rc meba_phy_ts_rx_clock_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_rx_clock_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_rx_clock_conf_get(phy_dev, clock_id, ptpclock_conf);
}

mepa_rc meba_phy_ts_tx_clock_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_tx_clock_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_tx_clock_conf_get(phy_dev, clock_id, ptpclock_conf);
}

mepa_rc meba_phy_ts_rx_clock_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_rx_clock_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_rx_clock_conf_set(phy_dev, clock_id, ptpclock_conf);
}

mepa_rc meba_phy_ts_tx_clock_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_tx_clock_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_tx_clock_conf_set(phy_dev, clock_id, ptpclock_conf);
}


mepa_rc meba_phy_ts_pps_conf_get(meba_inst_t inst, mepa_port_no_t port_no,
                                 mepa_ts_pps_conf_t *const phy_pps_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_pps_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_pps_conf_get(phy_dev, phy_pps_conf);
}


mepa_rc meba_phy_ts_pps_conf_set(meba_inst_t inst, mepa_port_no_t port_no,
                                 const mepa_ts_pps_conf_t *const phy_pps_conf)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }
    phy_dev = inst->phy_devices[port_no];

    if (!phy_dev->drv->mepa_ts->mepa_ts_pps_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_pps_conf_set(phy_dev, phy_pps_conf);
}

mepa_rc meba_phy_ts_stats_get(meba_inst_t inst, mepa_port_no_t port_no,
                              mepa_ts_stats_t *const statistics)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_stats_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_stats_get(phy_dev, statistics);
}

mepa_rc meba_phy_ts_event_get(meba_inst_t inst, mepa_port_no_t port_no,
                              mepa_ts_event_t *const ev_mask)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_event_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_event_get(phy_dev, ev_mask);
}

mepa_rc meba_phy_ts_event_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t enable, const mepa_ts_event_t ev_mask)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_event_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_event_set(phy_dev, enable, ev_mask);
}


mepa_rc meba_phy_ts_event_poll(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_event_t *const status)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_event_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_event_poll(phy_dev, status);
}

mepa_rc meba_phy_ts_test_config(meba_inst_t inst, mepa_port_no_t port_no, uint16_t test_id, mepa_bool_t reg_dump)
{
    mepa_device_t *phy_dev;
    mesa_rc rc = MESA_RC_ERROR;

    T_N(inst, "Called");
    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_test_config) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_test_config(phy_dev, test_id, reg_dump);
}

mepa_rc meba_phy_ts_fifo_read_install(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_fifo_read_t rd_cb)
{
    mepa_device_t *phy_dev;
    mepa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_fifo_read_install) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    phy_dev->drv->mepa_ts->mepa_ts_fifo_read_install(phy_dev, rd_cb);
    return MESA_RC_OK;
}

mepa_rc meba_phy_ts_fifo_empty(meba_inst_t inst, mepa_port_no_t port_no)
{
    mepa_device_t *phy_dev;
    mepa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev->drv->mepa_ts->mepa_ts_fifo_empty) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_ts->mepa_ts_fifo_empty(phy_dev);
}
