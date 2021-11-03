// Copyright (c) 2004-2021 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>

mepa_rc mepa_delete(struct mepa_device *dev) {
    if (!dev || !dev->drv->mepa_driver_delete) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_delete(dev);
}

mepa_rc mepa_reset(struct mepa_device *dev,
                   const mepa_reset_param_t *rst_conf) {
    if (!dev || !dev->drv->mepa_driver_reset) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_reset(dev, rst_conf);
}

mepa_rc mepa_poll(struct mepa_device *dev,
                  mepa_driver_status_t *status) {
    if(!dev || !dev->drv->mepa_driver_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_poll(dev, status);
}

mepa_rc mepa_conf_set(struct mepa_device *dev,
                      const mepa_driver_conf_t *conf) {
    if(!dev || !dev->drv->mepa_driver_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_conf_set(dev, conf);
}

mepa_rc mepa_conf_get(struct mepa_device *dev,
                      mepa_driver_conf_t *const conf) {
    if(!dev || !dev->drv->mepa_driver_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_conf_get(dev, conf);
}

mepa_rc mepa_if_get(struct mepa_device *dev,
                    mepa_port_speed_t speed,
                    mepa_port_interface_t *intf) {
    if(!dev || !dev->drv->mepa_driver_if_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_if_get(dev, speed, intf);
}

mepa_rc mepa_power_set(struct mepa_device *dev,
                       mepa_power_mode_t power) {
    if(!dev || !dev->drv->mepa_driver_power_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_power_set(dev, power);
}

mepa_rc mepa_cable_diag_start(struct mepa_device *dev,
                              int mode) {
    if (!dev || !dev->drv->mepa_driver_cable_diag_start) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_cable_diag_start(dev, mode);
}

mepa_rc mepa_cable_diag_get(struct mepa_device *dev,
                            mepa_cable_diag_result_t *result) {
    if (!dev || !dev->drv->mepa_driver_cable_diag_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_cable_diag_get(dev, result);
}

mepa_rc mepa_media_set(struct mepa_device *dev,
                       mepa_media_interface_t phy_media_if) {
    if (!dev || !dev->drv->mepa_driver_media_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_media_set(dev, phy_media_if);
}

mepa_rc mepa_aneg_status_get(struct mepa_device *dev,
                             mepa_aneg_status_t *status) {
    if (!dev || !dev->drv->mepa_driver_aneg_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_aneg_status_get(dev, status);
}

mepa_rc mepa_clause22_read(struct mepa_device *dev,
                           uint32_t address,
                           uint16_t *const value) {
    if (!dev || !dev->drv->mepa_driver_clause22_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_clause22_read(dev, address, value);
}

mepa_rc mepa_clause22_write(struct mepa_device *dev,
                            uint32_t address,
                            uint16_t value) {
    if (!dev || !dev->drv->mepa_driver_clause22_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_clause22_write(dev, address, value);
}

mepa_rc mepa_clause45_read(struct mepa_device *dev,
                           uint32_t address,
                           uint16_t *const value) {
    if (!dev || !dev->drv->mepa_driver_clause45_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_clause45_read(dev, address, value);
}

mepa_rc mepa_clause45_write(struct mepa_device *dev,
                            uint32_t address,
                            uint16_t value) {
    if (!dev || !dev->drv->mepa_driver_clause45_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_clause45_write(dev, address, value);
}

mepa_rc mepa_event_enable_set(struct mepa_device *dev,
                              mepa_event_t event,
                              mesa_bool_t enable) {
    if (!dev || !dev->drv->mepa_driver_event_enable_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_event_enable_set(dev, event, enable);
}

mepa_rc mepa_event_enable_get(struct mepa_device *dev,
                              mepa_event_t *const event) {
    if (!dev || !dev->drv->mepa_driver_event_enable_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_event_enable_get(dev, event);
}

mepa_rc mepa_event_poll(struct mepa_device *dev,
                        mepa_event_t *const ev_mask) {
    if (!dev || !dev->drv->mepa_driver_event_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_event_poll(dev, ev_mask);
}

mepa_rc mepa_loopback_set(struct mepa_device *dev,
                          const mepa_loopback_t *loopback) {
    if (!dev || !dev->drv->mepa_driver_loopback_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_loopback_set(dev, loopback);
}

mepa_rc mepa_loopback_get(struct mepa_device *dev,
                          mepa_loopback_t *const loopback) {
    if (!dev || !dev->drv->mepa_driver_loopback_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_loopback_get(dev, loopback);
}

mepa_rc mepa_gpio_mode_set(struct mepa_device *dev,
                           const mepa_gpio_conf_t *data) {
    if (!dev || !dev->drv->mepa_driver_gpio_mode_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_gpio_mode_set(dev, data);
}

mepa_rc mepa_gpio_out_set(struct mepa_device *dev,
                          uint8_t gpio_no,
                          mepa_bool_t value) {
    if (!dev || !dev->drv->mepa_driver_gpio_out_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_gpio_out_set(dev, gpio_no, value);
}

mepa_rc mepa_gpio_in_get(struct mepa_device *dev,
                         uint8_t gpio_no,
                         mepa_bool_t *const value) {
    if (!dev || !dev->drv->mepa_driver_gpio_in_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_gpio_in_get(dev, gpio_no, value);
}

mepa_rc mepa_synce_clock_conf_set(struct mepa_device *dev,
                                  const mepa_synce_clock_conf_t *conf) {
    if (!dev || !dev->drv->mepa_driver_synce_clock_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_synce_clock_conf_set(dev, conf);
}

mepa_rc mepa_link_base_port(struct mepa_device *dev,
                            struct mepa_device *base_dev) {
    if (!dev || !dev->drv->mepa_driver_link_base_port) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_link_base_port(dev, base_dev);
}

mepa_rc mepa_phy_info_get(struct mepa_device *dev,
                          mepa_phy_info_t *const phy_info) {
    if (!dev || !dev->drv->mepa_driver_phy_info_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_phy_info_get(dev, phy_info);
}

mepa_rc mepa_ts_mode_set(struct mepa_device *dev,
                         const mepa_bool_t enable) {
    if (!dev->drv->mepa_ts->mepa_ts_mode_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_mode_set(dev, enable);
}

mepa_rc mepa_ts_mode_get(struct mepa_device *dev,
                         mepa_bool_t *const enable) {
    if (!dev->drv->mepa_ts->mepa_ts_mode_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_mode_get(dev, enable);
}

mepa_rc mepa_ts_reset(struct mepa_device *dev,
                      const mepa_ts_reset_conf_t *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_reset) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_reset(dev, conf);
}

mepa_rc mepa_ts_init_conf_set(struct mepa_device              *dev,
                              const mepa_ts_init_conf_t       *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_init_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_init_conf_set(dev, conf);
}

mepa_rc mepa_ts_init_conf_get(struct mepa_device              *dev,
                              mepa_ts_init_conf_t             *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_init_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_init_conf_get(dev, conf);
}

mepa_rc mepa_ts_ltc_ls_en(struct mepa_device                  *dev,
                          mepa_ts_ls_type_t                    const type) {
    if (!dev->drv->mepa_ts->mepa_ts_ltc_ls_en) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ltc_ls_en(dev, type);
}

mepa_rc mepa_ts_ltc_get(struct mepa_device                    *dev,
                        mepa_timestamp_t                      *const ts) {
    if (!dev->drv->mepa_ts->mepa_ts_ltc_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ltc_get(dev, ts);
}

mepa_rc mepa_ts_ltc_set(struct mepa_device                    *dev,
                        const mepa_timestamp_t                *const ts) {
    if (!dev->drv->mepa_ts->mepa_ts_ltc_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ltc_set(dev, ts);
}

mepa_rc mepa_ts_delay_asymmetry_get(struct mepa_device        *dev,
                                    mepa_timeinterval_t       *const delay) {
    if (!dev->drv->mepa_ts->mepa_ts_delay_asymmetry_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_delay_asymmetry_get(dev, delay);
}

mepa_rc mepa_ts_delay_asymmetry_set(struct mepa_device        *dev,
                                    const mepa_timeinterval_t *const delay) {
    if (!dev->drv->mepa_ts->mepa_ts_delay_asymmetry_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_delay_asymmetry_set(dev, delay);
}

mepa_rc mepa_ts_path_delay_get(struct mepa_device             *dev,
                               mepa_timeinterval_t            *const delay) {
    if (!dev->drv->mepa_ts->mepa_ts_path_delay_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_path_delay_get(dev, delay);
}

mepa_rc mepa_ts_path_delay_set(struct mepa_device *dev,
                               const mepa_timeinterval_t      *const delay) {
    if (!dev->drv->mepa_ts->mepa_ts_path_delay_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_path_delay_set(dev, delay);
}

mepa_rc mepa_ts_egress_latency_get(struct mepa_device         *dev,
                                   mepa_timeinterval_t        *const latency) {
    if (!dev->drv->mepa_ts->mepa_ts_egress_latency_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_egress_latency_get(dev, latency);
}

mepa_rc mepa_ts_egress_latency_set(struct mepa_device         *dev,
                                   const mepa_timeinterval_t  *const latency) {
    if (!dev->drv->mepa_ts->mepa_ts_egress_latency_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_egress_latency_set(dev, latency);
}

mepa_rc mepa_ts_ingress_latency_get(struct mepa_device        *dev,
                                    mepa_timeinterval_t       *const latency) {
    if (!dev->drv->mepa_ts->mepa_ts_ingress_latency_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ingress_latency_get(dev, latency);
}

mepa_rc mepa_ts_ingress_latency_set(struct mepa_device        *dev,
                                    const mepa_timeinterval_t *const latency) {
    if (!dev->drv->mepa_ts->mepa_ts_ingress_latency_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ingress_latency_set(dev, latency);
}

mepa_rc mepa_ts_clock_rateadj_get(struct mepa_device          *dev,
                                  mepa_ts_scaled_ppb_t        *const rateadj) {
    if (!dev->drv->mepa_ts->mepa_ts_clock_rateadj_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_clock_rateadj_get(dev, rateadj);
}

mepa_rc mepa_ts_clock_rateadj_set(struct mepa_device          *dev,
                                  const mepa_ts_scaled_ppb_t  *const rateadj) {
    if (!dev->drv->mepa_ts->mepa_ts_clock_rateadj_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_clock_rateadj_set(dev, rateadj);
}

mepa_rc mepa_ts_clock_adj1ns(struct mepa_device               *dev,
                             const mepa_bool_t                 incr) {
    if (!dev->drv->mepa_ts->mepa_ts_clock_adj1ns) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_clock_adj1ns(dev, incr);
}

mepa_rc mepa_ts_pps_conf_get(struct mepa_device               *dev,
                             mepa_ts_pps_conf_t               *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_pps_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_pps_conf_get(dev, conf);
}

mepa_rc mepa_ts_pps_conf_set(struct mepa_device              *dev,
                              const mepa_ts_pps_conf_t        *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_pps_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_pps_conf_set(dev, conf);
}

mepa_rc mepa_ts_rx_classifier_conf_get(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       mepa_ts_classifier_t       *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_get(dev, flow_index, conf);
}

mepa_rc mepa_ts_tx_classifier_conf_get(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       mepa_ts_classifier_t       *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_get(dev, flow_index, conf);
}

mepa_rc mepa_ts_rx_classifier_conf_set(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       const mepa_ts_classifier_t *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_set(dev, flow_index, conf);
}

mepa_rc mepa_ts_tx_classifier_conf_set(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       const mepa_ts_classifier_t *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_set(dev, flow_index, conf);
}

mepa_rc mepa_ts_rx_clock_conf_get(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  mepa_ts_ptp_clock_conf_t        *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_rx_clock_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_rx_clock_conf_get(dev, clock_id, conf);
}

mepa_rc mepa_ts_tx_clock_conf_get(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  mepa_ts_ptp_clock_conf_t        *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_tx_clock_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_tx_clock_conf_get(dev, clock_id, conf);
}

mepa_rc mepa_ts_rx_clock_conf_set(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  const mepa_ts_ptp_clock_conf_t  *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_rx_clock_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_rx_clock_conf_set(dev, clock_id, conf);
}

mepa_rc mepa_ts_tx_clock_conf_set(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  const mepa_ts_ptp_clock_conf_t  *const conf) {
    if (!dev->drv->mepa_ts->mepa_ts_tx_clock_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_tx_clock_conf_set(dev, clock_id, conf);
}

mepa_rc mepa_ts_stats_get(struct mepa_device                    *dev,
                          mepa_ts_stats_t                       *const stat) {
    if (!dev->drv->mepa_ts->mepa_ts_stats_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_stats_get(dev, stat);
}

mepa_rc mepa_ts_event_set(struct mepa_device                      *dev,
                          const mepa_bool_t                        enable,
                          const mepa_ts_event_t                    ev_mask) {
    if (!dev->drv->mepa_ts->mepa_ts_event_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_event_set(dev, enable, ev_mask);
}

mepa_rc mepa_ts_event_get(struct mepa_device                      *dev,
                          mepa_ts_event_t                         *const ev_mask) {
    if (!dev->drv->mepa_ts->mepa_ts_event_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_event_get(dev, ev_mask);
}

mepa_rc mepa_ts_event_poll(struct mepa_device                     *dev,
                           mepa_ts_event_t                        *const status) {
    if (!dev->drv->mepa_ts->mepa_ts_event_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_event_poll(dev, status);
}

mepa_rc mepa_ts_fifo_empty(struct mepa_device                     *dev) {
    if (!dev->drv->mepa_ts->mepa_ts_fifo_empty) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_fifo_empty(dev);
}

mepa_rc mepa_ts_test_config(struct mepa_device                    *dev,
                            uint16_t                               test_id,
                            mepa_bool_t                            reg_dump) {
    if (!dev->drv->mepa_ts->mepa_ts_test_config) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_test_config(dev, test_id, reg_dump);
}
