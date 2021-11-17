// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_TS_DRV_API_H_
#define _MEPA_TS_DRV_API_H_

#include <microchip/ethernet/phy/api.h>

// Enable/Disable the timestamp block (Mode:TSU in Bypass mode)
typedef mepa_rc (*mepa_ts_mode_set_t)(struct mepa_device *dev, const mepa_bool_t enable);
typedef mepa_rc (*mepa_ts_mode_get_t)(struct mepa_device *dev, mepa_bool_t *const enable);

// Reset the timestamp block
typedef mepa_rc (*mepa_ts_reset_t)(struct mepa_device *dev, const mepa_ts_reset_conf_t *const tsreset);

// Initialize the timestamp block
typedef mepa_rc (*mepa_ts_init_conf_set_t)(struct mepa_device *dev, const mepa_ts_init_conf_t *const ts_init_conf);
typedef mepa_rc (*mepa_ts_init_conf_get_t)(struct mepa_device *dev, mepa_ts_init_conf_t *const ts_init_conf);

// Timestamp Load/Save enable
typedef mepa_rc (*mepa_ts_ltc_ls_en_t)(struct mepa_device *dev, mepa_ts_ls_type_t const ls_type);

// Get/Set the Local Time counter
typedef mepa_rc (*mepa_ts_ltc_get_t)(struct mepa_device *dev, mepa_timestamp_t *const ts);
typedef mepa_rc (*mepa_ts_ltc_set_t)(struct mepa_device *dev, const mepa_timestamp_t *const ts);

// Get/Set the delay asymmetry
typedef mepa_rc (*mepa_ts_delay_asymmetry_get_t)(struct mepa_device *dev, mepa_timeinterval_t *const delay_asym);
typedef mepa_rc (*mepa_ts_delay_asymmetry_set_t)(struct mepa_device *dev, const mepa_timeinterval_t *const delay_asym);

// Get/Set the path delay
typedef mepa_rc (*mepa_ts_path_delay_get_t)(struct mepa_device *dev, mepa_timeinterval_t *const path_delay);
typedef mepa_rc (*mepa_ts_path_delay_set_t)(struct mepa_device *dev, const mepa_timeinterval_t *const path_delay);

// Get/Set ingress and egress latency values, 48bit nanosec +16bit sub-nanosec
typedef mepa_rc (*mepa_ts_egress_latency_get_t)(struct mepa_device *dev, mepa_timeinterval_t *const latency);
typedef mepa_rc (*mepa_ts_egress_latency_set_t)(struct mepa_device *dev, const mepa_timeinterval_t *const latency);
typedef mepa_rc (*mepa_ts_ingress_latency_get_t)(struct mepa_device *dev, mepa_timeinterval_t *const latency);
typedef mepa_rc (*mepa_ts_ingress_latency_set_t)(struct mepa_device *dev, const mepa_timeinterval_t *const latency);

// Get/Set the clock rate adjustment value, frequency offset in units of scaled ppb
typedef mepa_rc (*mepa_ts_clock_rateadj_get_t)(struct mepa_device *dev, mepa_ts_scaled_ppb_t *const rateadj);
typedef mepa_rc (*mepa_ts_clock_rateadj_set_t)(struct mepa_device *dev, const mepa_ts_scaled_ppb_t *const rateadj);

// Adjust LTC with one NS
typedef mepa_rc (*mepa_ts_clock_adj1ns_t)(struct mepa_device *dev, const mepa_bool_t incr);

// Get/Set PPS
typedef mepa_rc (*mepa_ts_pps_conf_get_t)(struct mepa_device *dev, mepa_ts_pps_conf_t *const phy_pps_conf);
typedef mepa_rc (*mepa_ts_pps_conf_set_t) (struct mepa_device *dev, const mepa_ts_pps_conf_t *const phy_pps_conf);


// Get/Set ingress and egress PTP packet classifier configuration.
typedef mepa_rc (*mepa_ts_rx_classifier_conf_get_t)(struct mepa_device *dev, uint16_t flow_index, mepa_ts_classifier_t *const pkt_class_conf);
typedef mepa_rc (*mepa_ts_tx_classifier_conf_get_t)(struct mepa_device *dev, uint16_t flow_index, mepa_ts_classifier_t *const pkt_class_conf);
typedef mepa_rc (*mepa_ts_rx_classifier_conf_set_t)(struct mepa_device *dev, uint16_t flow_index, const mepa_ts_classifier_t *const pkt_class_conf);
typedef mepa_rc (*mepa_ts_tx_classifier_conf_set_t)(struct mepa_device *dev, uint16_t flow_index, const mepa_ts_classifier_t *const pkt_class_conf);

// Get/Set ingress and egress PTP clock configuration.
typedef mepa_rc (*mepa_ts_rx_clock_conf_get_t)(struct mepa_device *dev, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf);
typedef mepa_rc (*mepa_ts_tx_clock_conf_get_t)(struct mepa_device *dev, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf);
typedef mepa_rc (*mepa_ts_rx_clock_conf_set_t)(struct mepa_device *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *const ptpclock_conf);
typedef mepa_rc (*mepa_ts_tx_clock_conf_set_t)(struct mepa_device *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *const ptpclock_conf);

// Get statistics
typedef mepa_rc (*mepa_ts_stats_get_t)(struct mepa_device *dev, mepa_ts_stats_t *const statistics);

// Get/Set events
typedef mepa_rc (*mepa_ts_event_set_t) (struct mepa_device *dev, const mepa_bool_t enable, const mepa_ts_event_t ev_mask);
typedef mepa_rc (*mepa_ts_event_get_t) (struct mepa_device *dev, mepa_ts_event_t *const ev_mask);

// Polling function for TS events
typedef mepa_rc (*mepa_ts_event_poll_t) (struct mepa_device *dev, mepa_ts_event_t *const status);

// Install the callback function which will pass FIFO timestamp to application.
// cntxt refers to the arguments context needed by the callback function.
typedef void (*mepa_ts_fifo_read_install_t)(struct mepa_device *dev, mepa_ts_fifo_read_t rd_cb);

// Get all FIFO timestamp entries. Usually called after receiving timestamp captured interrupt.
typedef mepa_rc (*mepa_ts_fifo_empty_t)(struct mepa_device *dev);

// Sample Test configurations
typedef mepa_rc (*mepa_ts_test_config_t) (struct mepa_device *dev, uint16_t test_id, mepa_bool_t reg_dump);

// PHY Timestamp Driver
typedef struct mepa_ts_driver {
    mepa_ts_init_conf_get_t                 mepa_ts_init_conf_get;
    mepa_ts_init_conf_set_t                 mepa_ts_init_conf_set;
    mepa_ts_mode_get_t                      mepa_ts_mode_get;
    mepa_ts_mode_set_t                      mepa_ts_mode_set;
    mepa_ts_reset_t                         mepa_ts_reset;
    mepa_ts_ltc_ls_en_t                     mepa_ts_ltc_ls_en;
    mepa_ts_ltc_get_t                       mepa_ts_ltc_get;
    mepa_ts_ltc_set_t                       mepa_ts_ltc_set;
    mepa_ts_clock_rateadj_get_t             mepa_ts_clock_rateadj_get;
    mepa_ts_clock_rateadj_set_t             mepa_ts_clock_rateadj_set;
    mepa_ts_clock_adj1ns_t                  mepa_ts_clock_adj1ns;
    mepa_ts_delay_asymmetry_get_t           mepa_ts_delay_asymmetry_get;
    mepa_ts_delay_asymmetry_set_t           mepa_ts_delay_asymmetry_set;
    mepa_ts_path_delay_get_t                mepa_ts_path_delay_get;
    mepa_ts_path_delay_set_t                mepa_ts_path_delay_set;
    mepa_ts_egress_latency_get_t            mepa_ts_egress_latency_get;
    mepa_ts_egress_latency_set_t            mepa_ts_egress_latency_set;
    mepa_ts_ingress_latency_get_t           mepa_ts_ingress_latency_get;
    mepa_ts_ingress_latency_set_t           mepa_ts_ingress_latency_set;
    mepa_ts_pps_conf_set_t                  mepa_ts_pps_conf_set;
    mepa_ts_pps_conf_get_t                  mepa_ts_pps_conf_get;
    mepa_ts_rx_classifier_conf_get_t        mepa_ts_rx_classifier_conf_get;
    mepa_ts_rx_classifier_conf_set_t        mepa_ts_rx_classifier_conf_set;
    mepa_ts_tx_classifier_conf_get_t        mepa_ts_tx_classifier_conf_get;
    mepa_ts_tx_classifier_conf_set_t        mepa_ts_tx_classifier_conf_set;
    mepa_ts_rx_clock_conf_get_t             mepa_ts_rx_clock_conf_get;
    mepa_ts_tx_clock_conf_get_t             mepa_ts_tx_clock_conf_get;
    mepa_ts_rx_clock_conf_set_t             mepa_ts_rx_clock_conf_set;
    mepa_ts_tx_clock_conf_set_t             mepa_ts_tx_clock_conf_set;
    mepa_ts_stats_get_t                     mepa_ts_stats_get;
    mepa_ts_event_get_t                     mepa_ts_event_get;
    mepa_ts_event_set_t                     mepa_ts_event_set;
    mepa_ts_event_poll_t                    mepa_ts_event_poll;
    mepa_ts_test_config_t                   mepa_ts_test_config;
    mepa_ts_fifo_read_install_t             mepa_ts_fifo_read_install;
    mepa_ts_fifo_empty_t                    mepa_ts_fifo_empty;
} mepa_ts_driver_t;

#endif
