// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/* PTP public header with chip specific data structures and APIs */

#ifndef LAN80XX_TS_H_
#define LAN80XX_TS_H_

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>

typedef enum {
    LAN80XX_PTP_SYNC_CLOCK_SELECT_LSC0,
    LAN80XX_PTP_SYNC_CLOCK_SELECT_LSC1,
    LAN80XX_PTP_SYNC_CLOCK_SELECT_LSC2,
    LAN80XX_PTP_SYNC_CLOCK_SELECT_LSC3,
    LAN80XX_PTP_ASYNC_NO_CLOCK,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK_DIV_2,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK_DIV_4,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK_DIV_5,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK_DIV_8,
} phy25g_ptp_lsc_sync_clock_t;


typedef enum {
    LAN80XX_PTP_LSC_ACTIVE_HIGH,
    LAN80XX_PTP_LSC_ACTIVE_LOW,
} phy25g_lsc_pin_polarity_t;


typedef enum {
    LAN80XX_PTP_ACTION_IMMEDIATE,
    LAN80XX_PTP_ACTION_ONE_SHOT_ON_ACTIVE_EDGE,
    LAN80XX_PTP_ACTION_RESERVED,
    LAN80XX_PTP_ACTION_CONTINUOUS,
} phy25g_pps_action_t;

typedef enum {
    LAN80XX_PTP_LSC_PIN_0,
    LAN80XX_PTP_LSC_PIN_1,
    LAN80XX_PTP_LSC_PIN_2,
    LAN80XX_PTP_LSC_PIN_3,
} phy25g_lsc_pin_sel_t;

typedef struct {
    phy25g_ptp_lsc_sync_clock_t      clk_select;
    phy25g_lsc_pin_polarity_t        pin_inv_pol;
    phy25g_pps_action_t              pin_sync_mode;//00:Load immediate 01:excute on active edge on pin 11:action repeate at next active edge.
    phy25g_lsc_pin_sel_t             lsc_select;   //LSC Pin select.
} phy25g_pps_input_conf_t;


typedef enum {
    LAN80XX_PTP_LSC_SQUARE_WAVEFORM,
    LAN80XX_PTP_LSC_1PPS,
    LAN80XX_PTP_NSEC_BIT_OUT,
} phy25g_lsc_output_sync_t;

typedef struct {
    phy25g_ptp_lsc_sync_clock_t   clk_select;         /**< Sync or Async */
    phy25g_lsc_pin_polarity_t     pin_inv_pol;
    phy25g_lsc_output_sync_t      pin_sync_mode;      /**< Waveform or 1PPS */
    uint32_t                      pps_pulse_high ;    /**< Pulse or waveform high width in NSEC*/
    uint32_t                      pps_pulse_low;      /**< Waveform low width or 1PPS Pulse start boundary in NSEC */
    phy25g_lsc_pin_sel_t          lsc_select;         /**< LSC Pin select */
} phy25g_pps_output_conf_t;


typedef struct {
    uint32_t one_sec_wait_period_cfg;
    uint32_t one_microsec_period_cfg;
} phy25g_ts_sertod_Load_period_cfg;


typedef struct {

    uint8_t      pin_select;
    mepa_bool_t  pin_inv_pol;
    uint8_t      pin_sync_mode;//immediate, one short, continuous.
    mepa_bool_t load_enable;    /**< Serial ToD Input Enable */
    mepa_bool_t store_enable;    /**< Serial ToD Output Enable */
    mepa_bool_t msb_byte_first;
    mepa_bool_t msb_bit_first;
    uint8_t     ls_unit_sel;
    phy25g_ts_sertod_Load_period_cfg Ld_period_cfg;
} phy25g_ts_sertod_input_conf_t;

typedef struct {

    uint8_t      pin_select;
    mepa_bool_t  pin_inv_pol;
    uint8_t      pin_sync_mode;//immediate, one short, continuous.

    mepa_bool_t msb_byte_first;
    mepa_bool_t msb_bit_first;
    uint32_t  pin_wfh_period;
    uint32_t  pin_wfl_period;
} phy25g_ts_sertod_output_conf_t;


typedef struct {

    uint8_t      clk_select;
    uint8_t      pin_sync_mode;//immediate, one short, continuous.
    uint8_t      epps_event_detect_adjust;
    uint8_t      lsc_select;
} phy25g_ts_epps_conf_t;

typedef struct {

    int32_t nanoseconds; /**< 4 bytes nano-sec part of Timestamp */
    int8_t  subnanoseconds;
    uint8_t lsc_select;
} phy25g_ts_ltc_delta_adj_cfg;


/**
 * \brief Link up latency in 1588 engine.
 * \note To set the Link up latency in the 1588 engine
 * \param dev [IN]             mepa driver
*/
mepa_rc lan80xx_linkup_delay(mepa_device_t *dev);


/**
 * \brief configure LSC pin config for LS controller.
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \param phy25g_onepps_Input_cfg LSC pin config paramter.
*/
mepa_rc lan80xx_phy_ts_pps_input_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_pps_input_conf_t *const pin_conf);

/**
 * \brief configure serial tod input interface config .
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \param phy25g_ts_sertod_conf_t serial tod input parameter config.
*/
mepa_rc lan80xx_phy_ts_sertod_input_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_sertod_input_conf_t *const sertod_conf);


/**
 * \brief configure EPPS configuration inputs.
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \phy25g_ts_epps_conf_t   epps config paramter.
*/
mepa_rc lan80xx_phy_ts_epps_conf_set(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_epps_conf_t *const epps_conf);


/**
 * \brief configure PTP TOD Delta config .
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \phy25g_ts_ltc_delta_adj_cfg   TOD delta config paramter.
*/

mepa_rc lan80xx_phy_ts_ptptime_adj_delta(mepa_device_t  *dev, const mepa_port_no_t  port_no, phy25g_ts_ltc_delta_adj_cfg *const phy25g_ltc_tod_adj);

/**
 * \brief configure serial tod output interface config.
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \param phy25g_ts_sertod_conf_t serial tod output parameter config.
*/
mepa_rc lan80xx_phy_ts_sertod_output_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_sertod_output_conf_t *const sertod_conf);

/**
 * \brief configure LSC pin output config for LS controller.
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \param phy25g_onepps_Input_cfg LSC pin output config paramter.
*/
mepa_rc lan80xx_phy_ts_pps_ouput_conf_set(mepa_device_t *dev, const mepa_port_no_t  port_no, const phy25g_pps_output_conf_t *const pps_out_conf);

#endif
