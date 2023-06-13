// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_TS_DRV_API_H_
#define _MEPA_TS_DRV_API_H_

#include <microchip/ethernet/phy/api.h>

/**
 * \brief Enable/Disable the timestamp block (Mode:TSU in Bypass mode).
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [IN]  Enable/Disable the timestamp block.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_mode_set_t)(struct mepa_device *dev, const mepa_bool_t enable);

/**
 * \brief Enable/Disable the timestamp block (Mode:TSU in Bypass mode).
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [OUT] Enable/Disable the timestamp block.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_mode_get_t)(struct mepa_device *dev, mepa_bool_t *const enable);

/**
 * \brief Reset the timestamp block
 *
 * \param dev   [IN] Driver instance.
 * \param reset [IN] Reset configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not support.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_ts_reset_t)(struct mepa_device *dev, const mepa_ts_reset_conf_t *const tsreset);

/**
 * \brief Initialize the timestamp block
 *
 * \param dev  [IN]  Driver instance.
 * \param conf [IN]  Initialization parameters
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not support.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_init_conf_set_t)(struct mepa_device *dev, const mepa_ts_init_conf_t *const ts_init_conf);

/**
 * \brief Initialize the timestamp block
 *
 * \param dev  [IN]  Driver instance.
 * \param conf [OUT] Initialization parameters.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_init_conf_get_t)(struct mepa_device *dev, mepa_ts_init_conf_t *const ts_init_conf);

/**
 * \brief  Timestamp Load/Save enable
 *
 * \param dev  [IN] Driver instance.
 * \param type [IN] LTC Load/Save Enable commands.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_ltc_ls_en_t)(struct mepa_device *dev, mepa_ts_ls_type_t const ls_type);

/**
 * \brief Get the Local Time counter.
 *
 * \param dev [IN]  Driver instance.
 * \param ts  [OUT] PHY timestamp in seconds and nanoseconds.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_ltc_get_t)(struct mepa_device *dev, mepa_timestamp_t *const ts);

/**
 * \brief Set the Local Time counter.
 *
 * \param dev [IN]  Driver instance.
 * \param ts  [IN]  Local time counter.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_ltc_set_t)(struct mepa_device *dev, const mepa_timestamp_t *const ts);


/**
 * \brief Get the delay asymmetry
 *
 * \param dev   [IN]  Driver instance.
 * \param delay [OUT] Delay asymmetry.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_delay_asymmetry_get_t)(struct mepa_device *dev, mepa_timeinterval_t *const delay_asym);

/**
 * \brief Set the delay asymmetry
 *
 * \param dev   [IN]  Driver instance.
 * \param delay [IN]  Delay asymmetry.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_delay_asymmetry_set_t)(struct mepa_device *dev, const mepa_timeinterval_t *const delay_asym);

/**
 * \brief Get the path delay
 *
 * \param dev   [IN]  Driver instance.
 * \param delay [OUT] Path delay.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_path_delay_get_t)(struct mepa_device *dev, mepa_timeinterval_t *const path_delay);

/**
 * \brief Set the path delay
 *
 * \param dev   [IN]  Driver instance.
 * \param delay [IN]  Path delay.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_path_delay_set_t)(struct mepa_device *dev, const mepa_timeinterval_t *const path_delay);

/**
 * \brief Get egress latency values, 48bit nanosec +16bit sub-nanosec
 *
 * \param dev     [IN]  Driver instance.
 * \param latency [OUT] Egress latency value.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_egress_latency_get_t)(struct mepa_device *dev, mepa_timeinterval_t *const latency);

/**
 * \brief Set egress latency values, 48bit nanosec +16bit sub-nanosec
 *
 * \param dev     [IN] Driver instance.
 * \param latency [IN] Egress latency.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_egress_latency_set_t)(struct mepa_device *dev, const mepa_timeinterval_t *const latency);

/**
 * \brief Get ingress latency values, 48bit nanosec +16bit sub-nanosec
 *
 * \param dev     [IN]  Driver instance.
 * \param latency [OUT] Ingress Latency.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_ingress_latency_get_t)(struct mepa_device *dev, mepa_timeinterval_t *const latency);

/**
 * \brief Set ingress latency values, 48bit nanosec +16bit sub-nanosec
 *
 * \param dev     [IN]  Driver instance.
 * \param latency [IN]  Ingress latency.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_ingress_latency_set_t)(struct mepa_device *dev, const mepa_timeinterval_t *const latency);

/**
 * \brief Get the clock rate adjustment value, frequency offset in units of scaled ppb.
 *
 * \param dev     [IN]  Driver instance.
 * \param rateadj [OUT] Ingress latency.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_clock_rateadj_get_t)(struct mepa_device *dev, mepa_ts_scaled_ppb_t *const rateadj);

/**
 * \brief Clock frequency ratio in scaled PartsPerBillion.
 *
 * \param dev     [IN] Driver instance.
 * \param rateadj [IN] Clock rate adjustment.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_clock_rateadj_set_t)(struct mepa_device *dev, const mepa_ts_scaled_ppb_t *const rateadj);

/**
 * \brief Get Adjust LTC with one NS.
 *
 * \param dev  [IN] Driver instance.
 * \param incr [IN] Increament/Decreament.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_clock_adj1ns_t)(struct mepa_device *dev, const mepa_bool_t incr);

/**
 * \brief Get PPS.
 *
 * \param dev          [IN]  Driver instance.
 * \param phy_pps_conf [OUT] PHY PPS Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_pps_conf_get_t)(struct mepa_device *dev, mepa_ts_pps_conf_t *const phy_pps_conf);

/**
 * \brief Set PPS.
 *
 * \param dev          [IN] Driver instance.
 * \param phy_pps_conf [IN] PHY PPS Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_pps_conf_set_t) (struct mepa_device *dev, const mepa_ts_pps_conf_t *const phy_pps_conf);

/**
 * \brief Get ingress PTP packet classifier configuration.
 *
 * \param dev        [IN]  Driver instance.
 * \param flow index [IN]  Flow index.
 * \param conf       [OUT] Rx/Tx Clock configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_rx_classifier_conf_get_t)(struct mepa_device *dev, uint16_t flow_index, mepa_ts_classifier_t *const pkt_class_conf);

/**
 * \brief Get egress PTP packet classifier configuration.
 *
 * \param dev        [IN]  Driver instance.
 * \param flow index [IN]  Flow index.
 * \param conf       [OUT] Rx/Tx Clock configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_tx_classifier_conf_get_t)(struct mepa_device *dev, uint16_t flow_index, mepa_ts_classifier_t *const pkt_class_conf);

/**
 * \brief Set ingress PTP packet classifier configuration.
 *
 * \param dev        [IN]  Driver instance.
 * \param flow index [IN]  Flow index.
 * \param conf       [OUT] Rx/Tx Clock configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_rx_classifier_conf_set_t)(struct mepa_device *dev, uint16_t flow_index, const mepa_ts_classifier_t *const pkt_class_conf);

/**
 * \brief Set egress PTP packet classifier configuration.
 *
 * \param dev        [IN]  Driver instance.
 * \param flow index [IN]  Flow index.
 * \param conf       [OUT] Clock configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_tx_classifier_conf_set_t)(struct mepa_device *dev, uint16_t flow_index, const mepa_ts_classifier_t *const pkt_class_conf);

/**
 * \brief Get ingress  PTP clock configuration.
 *
 * \param dev      [IN] Driver instance.
 * \param clock_id [IN] Clock ID.
 * \param conf     [IN] Clock Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_rx_clock_conf_get_t)(struct mepa_device *dev, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf);

/**
 * \brief Get egress PTP clock configuration.
 *
 * \param dev      [IN] Driver instance.
 * \param clock_id [IN] Clock ID.
 * \param conf     [IN] Clock Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_tx_clock_conf_get_t)(struct mepa_device *dev, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf);


/**
 * \brief Set ingress  PTP clock configuration.
 *
 * \param dev      [IN] Driver instance.
 * \param clock_id [IN] Clock ID
 * \param conf     [IN] Clock Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_rx_clock_conf_set_t)(struct mepa_device *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *const ptpclock_conf);

/**
 * \brief Set egress PTP clock configuration.
 *
 * \param dev      [IN]  Driver instance.
 * \param clock_id [OUT] Clock ID.
 * \param conf     [OUT] Clock Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_tx_clock_conf_set_t)(struct mepa_device *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *const ptpclock_conf);

/**
 * \brief Get statistics.
 *
 * \param dev  [IN] Driver instance.
 * \param stat [IN] Ts statics.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_stats_get_t)(struct mepa_device *dev, mepa_ts_stats_t *const statistics);

/**
 * \brief Set events
 *
 * \param dev     [IN]  Driver instance.
 * \param enable  [OUT] Interrupt enable.
 * \param ev_mask [OUT] Timestamp interrupt events.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_event_set_t) (struct mepa_device *dev, const mepa_bool_t enable, const mepa_ts_event_t ev_mask);

/**
 * \brief Get events.
 *
 * \param dev     [IN] Driver instance.
 * \param ev_mask [IN] Timestamp interrupt events.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_event_get_t) (struct mepa_device *dev, mepa_ts_event_t *const ev_mask);

/**
 * \brief Polling function for TS events.
 *
 * \param dev    [IN]  Driver instance.
 * \param status [OUT] Timestamp interrupt events.
 *
 * \return
 *    MEPA_RC_OK on success.\n
 *    MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_ts_event_poll_t) (struct mepa_device *dev, mepa_ts_event_t *const status);

/** \brief Install the callback function which will pass FIFO timestamp to application.
 *   cntxt refers to the arguments context needed by the callback function. */
typedef void (*mepa_ts_fifo_read_install_t)(struct mepa_device *dev, mepa_ts_fifo_read_t rd_cb);

/** \brief Get all FIFO timestamp entries. Usually called after receiving timestamp captured interrupt. */
typedef mepa_rc (*mepa_ts_fifo_empty_t)(struct mepa_device *dev);

/** \brief Get FIFO timestamp entries up to maximum of 8 entries. Returns number of FIFO entries read to application. */
typedef mepa_rc (*mepa_ts_fifo_entry_get_t)(struct mepa_device *dev, mepa_fifo_ts_entry_t ts_list[], const size_t size, uint32_t *const num);

/** \brief Sample Test configurations */
typedef mepa_rc (*mepa_ts_test_config_t) (struct mepa_device *dev, uint16_t test_id, mepa_bool_t reg_dump);

/** \brief PHY Timestamp Driver */
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
    mepa_ts_fifo_entry_get_t                mepa_ts_fifo_get;
} mepa_ts_driver_t;

#endif
