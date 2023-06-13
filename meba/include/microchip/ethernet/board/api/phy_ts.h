// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_BOARD_PHY_TS_DRIVER_H_
#define _MICROCHIP_ETHERNET_BOARD_PHY_TS_DRIVER_H_

#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api/phy_ts.h>
#include <microchip/ethernet/hdr_start.h>

// Initialize the timestamp block
mepa_rc meba_phy_ts_init_conf_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_init_conf_t *const ts_init_conf);
mepa_rc meba_phy_ts_init_conf_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_init_conf_t *ts_init_conf);


mepa_rc meba_phy_ts_mode_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_bool_t *const enable);
mepa_rc meba_phy_ts_mode_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t enable);

// get/set Local Time counter time get
mepa_rc meba_phy_ts_ltc_ls_en(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_ls_type_t ls_cmd);
mepa_rc meba_phy_ts_ltc_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timestamp_t *const ts);
mepa_rc meba_phy_ts_ltc_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timestamp_t *const ts);
// Get/Set LTC Rate Adjust
mepa_rc meba_phy_ts_clock_rateadj_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_scaled_ppb_t *const rateadj);
mepa_rc meba_phy_ts_clock_rateadj_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_scaled_ppb_t *const rateadj);
// Adjust LTC with one NS
mepa_rc meba_phy_ts_clock_adj1ns(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t incr);


// Get/Set Delay asymmetry
mepa_rc meba_phy_ts_delay_asymmetry_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const delay_asym);
mepa_rc meba_phy_ts_delay_asymmetry_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const delay_asym);

// Get/Set Path Delay
mepa_rc meba_phy_ts_path_delay_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const path_delay);
mepa_rc meba_phy_ts_path_delay_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const path_delay);

// Get/Set Egress Latency
mepa_rc meba_phy_ts_egress_latency_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const latency);
mepa_rc meba_phy_ts_egress_latency_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const latency);

// Get/Set Ingress Latency
mepa_rc meba_phy_ts_ingress_latency_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_timeinterval_t *const latency);
mepa_rc meba_phy_ts_ingress_latency_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_timeinterval_t *const latency);


// Get/Set Rx/Tx Clock configuration
mepa_rc meba_phy_ts_rx_classifier_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, mepa_ts_classifier_t *const pkt_conf);
mepa_rc meba_phy_ts_rx_classifier_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, const mepa_ts_classifier_t *pkt_conf);
mepa_rc meba_phy_ts_tx_classifier_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, mepa_ts_classifier_t *const pkt_conf);
mepa_rc meba_phy_ts_tx_classifier_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t flow_index, const mepa_ts_classifier_t *pkt_conf);

// Get/Set Rx/Tx Clock configuration
mepa_rc meba_phy_ts_rx_clock_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf);
mepa_rc meba_phy_ts_tx_clock_conf_get(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf);
mepa_rc meba_phy_ts_rx_clock_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf);
mepa_rc meba_phy_ts_tx_clock_conf_set(meba_inst_t inst, mepa_port_no_t port_no, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf);

// Get/Set configured offset for the PPS generation.
mepa_rc meba_phy_ts_pps_conf_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_pps_conf_t *const phy_pps_conf);
mepa_rc meba_phy_ts_pps_conf_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_ts_pps_conf_t *const phy_pps_conf);

// Get ts statistics
mepa_rc meba_phy_ts_stats_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_stats_t *const statistics);

// Get/Set event mask
mepa_rc meba_phy_ts_event_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_event_t *const ev_mask);
mepa_rc meba_phy_ts_event_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_bool_t enable, const mepa_ts_event_t ev_mask);

// Poll for timestampevents
mepa_rc meba_phy_ts_event_poll(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_event_t *const status);

// Timestamp fifo read callback installation.
mepa_rc meba_phy_ts_fifo_read_install(meba_inst_t inst, mepa_port_no_t port_no, mepa_ts_fifo_read_t rd_cb);
// Read all FIFO entries.
mepa_rc meba_phy_ts_fifo_empty(meba_inst_t inst, mepa_port_no_t port_no);

mepa_rc meba_phy_ts_fifo_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_fifo_ts_entry_t ts_list[], const size_t size, uint32_t *const num);

// Sample Test configuration
mepa_rc meba_ts_test_config(meba_inst_t inst, mepa_port_no_t port_no, uint16_t test_id, mepa_bool_t reg_dump);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_BOARD_PHY_TS_DRIVER_H_
