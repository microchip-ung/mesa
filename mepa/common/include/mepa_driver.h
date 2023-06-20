// Copyright (c) 2004-2021 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_PHY_API_PHY_DRV_H_
#define _MICROCHIP_ETHERNET_PHY_API_PHY_DRV_H_

#include <mepa_os.h>
#include <mepa_ts_driver.h>
#include <mepa_macsec_driver.h>
#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

/** PHY DRIVER
 *
 * This API defines the interface used by the switch application to interact
 * with the PHY. Using this interface the switch application should not know
 * which PHY it is using.
 *
 * Each PHY driver needs to implement the following methods for a minimum
 * configuration:
 *  mepa_driver_delete_t
 *  mepa_driver_probe_t
 *  mepa_driver_poll_t
 *  mepa_driver_conf_set_t
 */

void MEPA_trace(mepa_trace_group_t  group,
                mepa_trace_level_t  level,
                const char         *location,
                uint32_t            line,
                const char         *format,
                ...);

/**
 * \brief Clears up the data allocated in the probe function.
 *
 * \param dev [IN] Driver Instance.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_delete_t)(struct mepa_device *dev);

/**
 * \brief Resets PHY.
 *
 * \param dev      [IN]    Driver instance.
 * \param rst_conf [IN]    Reset configurations.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_reset_t)(
        struct mepa_device *dev,
        const mepa_reset_param_t *rst_conf);

/**
 * \brief Get the current status of the PHY.
 *
 * \param dev    [IN]       Driver instance.
 * \param status [OUT]      Represents the status of the PHY.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_driver_poll_t)(
        struct mepa_device *dev,
        mepa_status_t *status);

/**
 * \brief Set the configuration of the PHY.
 * \brief conf   [IN] PHY configuration.
 *
 * \param dev  [IN]   Driver Instance.
 * \param conf [IN]   PHY configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_driver_conf_set_t)(
    struct mepa_device *dev, const mepa_conf_t *conf);

/**
 * \brief Get the current interface configuraton of the PHY.
 *
 * \param dev  [IN]    Driver instance.
 * \param conf [OUT]   PHY configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_conf_get_t)(struct mepa_device *dev, mepa_conf_t *const conf);

/**
 * \brief   Set the PHY interface.
 *
 * \param   dev  [IN]     Driver instance.
 * \param   intf [IN]     The current interface configuration of PHY.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_driver_if_set_t)(
        struct mepa_device *dev,
        mepa_port_interface_t intf);

/**
 * \brief Get the PHY interface based on speed.
 *
 * \param dev    [IN]  Driver instance.
 * \param speed  [IN]  The PHY interface based on speed.
 * \param intf   [OUT] The current interface configuration of PHY.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_if_get_t)(
        struct mepa_device *dev,
        mepa_port_speed_t speed,
        mepa_port_interface_t *intf);

/**
 * \brief Sets the power mode.
 *
 * \param dev    [IN]  Driver instance.
 * \param power  [IN]  Power mode.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.
 **/
typedef mepa_rc (*mepa_driver_power_set_t)(
        struct mepa_device *dev,
        mepa_power_mode_t power);

/**
 * \brief Starts cable diag.
 *
 * \param dev  [IN]  Driver instance.
 * \param mode [IN]  Mode in which to start.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_driver_cable_diag_start_t)(
    struct mepa_device *dev, int32_t mode);

/**
 * \brief Gets result from cable diagnostics.
 *
 * \param dev      [IN]  Driver instance.
 * \param  result  [OUT] Result from cable diagnostics.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_driver_cable_diag_get_t)(
    struct mepa_device *dev, mepa_cable_diag_result_t *result);

/**
 * \brief Sets the media type in case the port is a dual media port with external phy.
 *
 *  \param dev           [IN]  Driver instance.
 *  \param phy_media_if  [IN]  Media type.
 *
 *  \return
 *     MEPA_RC_NOT_IMPLEMENTED when not supported.
 **/
typedef mepa_rc (*mepa_driver_media_set_t)(
    struct mepa_device *dev, mepa_media_interface_t phy_media_if);

/**
 * \brief Gets the media type in case the port is a dual media port with external phy.
 *
 *  \param dev           [IN]  Driver instance.
 *  \param phy_media_if  [OUT] Media type.
 *
 *  \return
 *     MEPA_RC_NOT_IMPLEMENTED when not supported.
 **/
typedef mepa_rc (*mepa_driver_media_get_t)(
    struct mepa_device *dev, mepa_media_interface_t *phy_media_if);

/**
 *  \brief Create an instance of the driver and initialize the PHY.
 **/
typedef struct mepa_device *(*mepa_driver_probe_t)(
    struct mepa_driver                  *dev,
    const mepa_callout_t    MEPA_SHARED_PTR *callout,
    struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
    struct mepa_board_conf              *conf);

/**
 * \brief  Gets copper PHY auto-negotiation status.
 *
 * \param dev   [IN]   Driver instance.
 * \param  mode [OUT]  PHY 1G status.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_driver_aneg_status_get_t)(
    struct mepa_device *dev, mepa_aneg_status_t *status);

/**
 * \brief  PHY register read access using clause22 format for debugging
 *         address : bits 0 - 4 : address within page
 *                        5 - 31: page number
 *
 * \param dev     [IN]   Driver instance.
 * \param address [IN]   Address.
 * \param value   [OUT]  Value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 **/
typedef mepa_rc (*mepa_driver_clause22_read_t)(struct mepa_device *dev,
                 uint32_t address, uint16_t *const value);

/**
 * \brief  PHY register write access using clause22 format for debugging
 *         address : bits 0 - 4 : address within page
 *                 5 - 31: page number
 *
 * \param dev     [IN]  Driver instance.
 * \param address [IN]  Address.
 * \param value   [IN]  Value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_clause22_write_t)(struct mepa_device *dev,
                 uint32_t address, uint16_t value);

/**
 * \brief  PHY register read access using clause45 format for debugging
 *         address : bits 0  - 15 : address within page
 *                 16 - 31 : page number
 *
 *  \param dev     [IN]  Driver instance.
 *  \param address [IN]  Address.
 *  \param value   [OUT] Value.
 *
 *  \return
 *    MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *    MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_clause45_read_t)(struct mepa_device *dev,
                 uint32_t address, uint16_t *const value);

/**
 * \brief  PHY register write access using clause45 format for debugging
 *         address : bits 0  - 15 : address within page
 *                 16 - 31 : page number
 *
 *  \param dev     [IN]  Driver instance.
 *  \param address [OUT] Address.
 *  \param value   [IN]  Value.
 *
 *  \return
 *    MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *    MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_clause45_write_t)(struct mepa_device *dev,
                 uint32_t address, uint16_t value);

/**
 * \brief  Enable PHY events.
 *
 * \param dev    [IN] Driver instance.
 * \param event  [IN] PHY event mask to be enabled.
 * \param enable [IN] Enable or disable the event.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_event_enable_set_t)(struct mepa_device *dev,
                 mepa_event_t event, mesa_bool_t enable);

/**
 * \brief  Get the PHY events currently enabled.
 *
 * \param dev    [IN]  Driver instance.
 * \param event  [OUT] Event mask which is currently enabled in PHY.
 *
 * \return
 *    MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *    MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_event_enable_get_t)(struct mepa_device *dev,
                 mepa_event_t *const event);

/**
 * \brief Poll the status of PHY events.
 *
 * \param dev      [IN]  Driver instance.
 * \param  ev_mask [OUT] Event mask containing current status of PHY events.
 *
 * \return
 *    MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *    MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_event_poll_t)(struct mepa_device *dev, mepa_event_t *const ev_mask);

/**
 * \brief Set loopback. Used for debugging purpose
 *
 * \param dev       [IN] Driver Instance.
 * \param loopback  [IN] Loopback Types.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.
 **/
typedef mepa_rc (*mepa_driver_loopback_set_t)(struct mepa_device *dev, const mepa_loopback_t *loopback);

/**
 * \brief  Get current loopback configuration.
 *
 * \param dev       [IN]  Driver instance.
 * \param loopback  [OUT] Loopback Types.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_loopback_get_t)(struct mepa_device *dev, mepa_loopback_t *const loopback);

/**
 * \brief Set the GPIO pin mode to input, output or alternate function.
 *
 * \param dev  [IN]  Driver instance.
 * \param data [OUT] GPIO configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_gpio_mode_set_t)(struct mepa_device *dev, const mepa_gpio_conf_t *data);

/**
 * \brief  Set the GPIO pin value.
 *
 * \param dev     [IN]  Driver instance.
 * \param gpio_no [IN]  GPIO Number.
 * \param value   [IN]  Value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_gpio_out_set_t)(struct mepa_device *dev, uint8_t gpio_no, mepa_bool_t value);

/**
 * \brief  Get the GPIO pin value.
 *
 * \param dev      [IN]   Driver Instance.
 * \param gpio_no  [IN]   GPIO Number.
 * \param value    [OUT]  Value.
 *
 * \return
 *    MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *    MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_gpio_in_get_t)(struct mepa_device *dev, uint8_t gpio_no, mepa_bool_t * const value);

/**
 * \brief Configure recovered clock
 *
 * \param dev  [IN] Driver instance.
 * \param conf [IN] Synce recovered clock configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_synce_clock_conf_set_t)(struct mepa_device *dev, const mepa_synce_clock_conf_t *conf);

/**
 * \brief  Link Base Port. Used for accessing the chip leavel common resources.
 *
 * \param dev         [IN] Driver instance.
 * \param base_dev    [IN] Base port driver instance.
 * \param packet_idx  [IN] Link status.
 *
 * \return
 *  MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *  MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_link_base_port_t)(struct mepa_device *dev, struct mepa_device *base_dev, uint8_t packet_idx);

/**
 * \brief Get phy information like phy-id, revision etc.
 *
 * \param dev       [IN]   Driver instance.
 * \param phy_info  [OUT]  Phy information.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_phy_info_get_t)(struct mepa_device *dev, mepa_phy_info_t *const phy_info);

/**
 * \brief  Isolation mode as defined by IEEE 802.3-2012 section 22.2.4.1.6
 *
 * \param dev     [IN]    Driver instance.
 * \param iso_en  [OUT]   Enable /disable isolation mode.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_isolate_mode_conf_t)(struct mepa_device *dev, const mepa_bool_t iso_en);

/**
 * \brief  Debug dump API for PHY.
 *
 * \param dev  [IN]   Driver instance.
 * \param pr   [IN]   Debug printf function.
 * \param info [OUT]  Debug information.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_debug_info_dump_t)(struct mepa_device *dev,
                             const mepa_debug_print_t pr,
                             const mepa_debug_info_t   *const info);

/**
 * \brief I2C Read - perform i2C I/O thru PHY for Reading SFP using i2C i/f
 *
 * \param dev  [IN]            Driver instance.
 * \param i2c_mux [IN]         The i2c clock mux
 * \param i2c_reg_addr [IN]    The i2c register address to access.
 * \param i2c_device_addr [IN] The i2c address of the device to access.
 * \param word_access [IN]     Set to TRUE if the register data width is 16bit. FALSE = 8 bits data width
 * \param cnt [IN]             The number of registers to read.
 *                             Note: The reg_addr is incremented by 1 for each of the read counts. If you want to read 16 bites registers
 *                             (2 times 8 bits from the same register address), you need to do that by calling the vtss_phy_i2c_read twice,
 *                             and not use the cnt (set cnt to 1).
 * \param value [OUT]          Pointer to where array which in going to contain the values read.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_ERROR on Error \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_phy_i2c_read_t)(struct mepa_device *dev,
                             const uint8_t i2c_mux,
                             const uint8_t i2c_reg_addr,
                             const uint8_t i2c_dev_addr,
                             const mepa_bool_t word_access,
                             uint8_t cnt,
                             uint8_t *const value);

/**
 *
 * \brief I2C Write - perform i2C I/O thru PHY for Writing to the SFP using i2C i/f
 *
 * \param dev  [IN]            Driver instance.
 * \param i2c_mux [IN]         The i2c clock mux
 * \param i2c_reg_addr [IN]    The i2c register address to access.
 * \param i2c_device_addr [IN] The i2c address of the device to access.
 * \param word_access [IN]     Set to TRUE if the register data width is 16bit. FALSE = 8 bits data width
 * \param cnt [IN]             The number of registers to write.
 *                             Note: The reg_addr is incremented by 1 for each of the write counts. If you want to write 16 bites registers
 *                             (2 times 8 bits to the same register address), you need to do that by calling the vtss_phy_i2c_write twice,
 *                             and not use the cnt (set cnt to 1).
 * \param value [IN]           Pointer to where array containing the values to write.
 *
 * \return Return code.
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_ERROR on Error \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_phy_i2c_write_t)(struct mepa_device *dev,
                             const uint8_t i2c_mux,
                             const uint8_t i2c_reg_addr,
                             const uint8_t i2c_dev_addr,
                             const mepa_bool_t word_access,
                             uint8_t cnt,
                             const uint8_t *value);

/**
 * \brief I2C clock frequency select
 *
 * \param dev  [IN]            Driver instance.
 * \param clk_value [IN]       Pointer to where clock frequency values to write.
 *
 * \return Return code.
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
*   MEPA_RC_ERROR on Error \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_phy_i2c_clock_select_t)(struct mepa_device *dev,
                             mepa_i2c_clk_select_t const *clk_value);

/**
 * \brief PHY get SQI value
 *
 * \param dev   [IN]   Driver instance.
 * \param value [OUT]   SQI value to return
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_sqi_read_t)(struct mepa_device *dev, uint32_t *const value);

/**
 * \irief PHY write SOF value
 *
 * \param dev   [IN]   Driver instance.
 * \param conf [IN]   SOF value to be Configured
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_start_of_frame_write_t)(struct mepa_device *dev, mepa_start_of_frame_conf_t *const conf);

/**
 * \brief PHY get SOF value
 *
 * \param dev   [IN]   Driver instance.
 * \param value [OUT]   SOF value to return
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_start_of_frame_read_t)(struct mepa_device *dev, mepa_start_of_frame_conf_t *const value);

/**
 * \brief PHY get Frame Preemption
 *
 * \param dev   [IN]   Driver instance.
 * \param value [OUT]  Frame Preemption value to return
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_framepreempt_get_t)(struct mepa_device *dev, mepa_bool_t *const value);

/**
 * \brief Start PHY Self-Test Frame Generation
 *
 * \param dev     [IN]  Driver instance.
 * \param inf     [IN]  selftest information
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_selftest_start_t)(struct mepa_device *dev, const mepa_selftest_info_t *inf);

/**
 * \brief Read PHY Self-Test Checking counters
 *
 * \param dev     [IN]  Driver instance.
 * \param inf     [OUT] selftest information
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_selftest_read_t)(struct mepa_device *dev, mepa_selftest_info_t *const inf);

/**
 * \brief To Set PRBS
 *
 * \param dev    [IN]  Driver instance.
 * \param conf   [IN] Pseudo Random Binary Sequence 7 information.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_prbs_set_t)(struct mepa_device *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const prbs_conf);

/**
 * \brief To Get PRBS
 *
 * \param dev    [IN]  Driver instance.
 * \param conf   [OUT] Pseudo Random Binary Sequence 7 information.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_prbs_get_t)(struct mepa_device *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const prbs_conf);

/**
 * \brief To inject an error
 *
 * \param dev        [IN] Driver instance.
 * \param value      [IN] Pseudo Random Binary Sequence 7 error count.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_prbs_monitor_set_t)(struct mepa_device *dev, mepa_phy_prbs_monitor_conf_t *const value);

/**
 * \brief To Get  an error status
 *
 * \param dev        [IN]  Driver instance.
 * \param value      [OUT] Pseudo Random Binary Sequence 7 error count.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_prbs_monitor_get_t)(struct mepa_device *dev, mepa_phy_prbs_monitor_conf_t *const value);

/**
 * \brief To Get restart configuration (next restart mode)
 *
 * \param dev        [IN]  Driver instance.
 * \param value      [OUT] Warmrestart Info.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_warmrestart_conf_get_t)(struct mepa_device *dev, mepa_restart_t *const restart);

/**
 * \brief Set restart configuration (next restart mode)
 *
 * \param dev        [IN]  Driver instance.
 * \param value      [OUT] Warmrestart Info.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_warmrestart_conf_set_t)(struct mepa_device *dev, const mepa_restart_t restart);

/**
 * \brief To End  Warm restart configuration
 *
 * \param dev        [IN]  Driver instance.
 * \param value      [OUT] Warmrestart Info.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_warmrestart_conf_end_t)(struct mepa_device *dev);

/**
 * \brief To End  Warm restart configuration
 *
 * \param dev        [IN]  Driver instance.
 * \param value      [OUT] Warmrestart Info.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_driver_warmrestart_sync_t)(struct mepa_device *dev);

typedef struct mepa_driver {
    mepa_driver_delete_t               mepa_driver_delete;
    mepa_driver_reset_t                mepa_driver_reset;
    mepa_driver_poll_t                 mepa_driver_poll;
    mepa_driver_conf_set_t             mepa_driver_conf_set;
    mepa_driver_conf_get_t             mepa_driver_conf_get;
    mepa_driver_if_set_t               mepa_driver_if_set;
    mepa_driver_if_get_t               mepa_driver_if_get;
    mepa_driver_power_set_t            mepa_driver_power_set;
    mepa_driver_cable_diag_start_t     mepa_driver_cable_diag_start;
    mepa_driver_cable_diag_get_t       mepa_driver_cable_diag_get;
    mepa_driver_media_set_t            mepa_driver_media_set;
    mepa_driver_media_get_t            mepa_driver_media_get;
    mepa_driver_probe_t                mepa_driver_probe;
    mepa_driver_aneg_status_get_t      mepa_driver_aneg_status_get;
    mepa_driver_clause22_read_t        mepa_driver_clause22_read;
    mepa_driver_clause22_write_t       mepa_driver_clause22_write;
    mepa_driver_clause45_read_t        mepa_driver_clause45_read;
    mepa_driver_clause45_write_t       mepa_driver_clause45_write;
    mepa_driver_event_enable_set_t     mepa_driver_event_enable_set;
    mepa_driver_event_enable_get_t     mepa_driver_event_enable_get;
    mepa_driver_event_poll_t           mepa_driver_event_poll;
    mepa_driver_loopback_set_t         mepa_driver_loopback_set;
    mepa_driver_loopback_get_t         mepa_driver_loopback_get;
    mepa_driver_gpio_mode_set_t        mepa_driver_gpio_mode_set;
    mepa_driver_gpio_out_set_t         mepa_driver_gpio_out_set;
    mepa_driver_gpio_in_get_t          mepa_driver_gpio_in_get;
    mepa_driver_synce_clock_conf_set_t mepa_driver_synce_clock_conf_set;
    mepa_driver_link_base_port_t       mepa_driver_link_base_port;
    mepa_driver_phy_info_get_t         mepa_driver_phy_info_get;
    mepa_driver_isolate_mode_conf_t    mepa_driver_isolate_mode_conf;
    mepa_debug_info_dump_t             mepa_debug_info_dump;
    mepa_driver_phy_i2c_read_t         mepa_driver_phy_i2c_read;
    mepa_driver_phy_i2c_write_t        mepa_driver_phy_i2c_write;
    mepa_driver_phy_i2c_clock_select_t mepa_driver_phy_i2c_clock_select;
    mepa_driver_sqi_read_t             mepa_driver_sqi_read;
    mepa_driver_start_of_frame_write_t mepa_driver_start_of_frame_conf_set;
    mepa_driver_start_of_frame_read_t  mepa_driver_start_of_frame_conf_get;
    mepa_driver_framepreempt_get_t     mepa_driver_framepreempt_get;
    mepa_driver_selftest_start_t       mepa_driver_selftest_start;
    mepa_driver_selftest_read_t        mepa_driver_selftest_read;
    mepa_driver_prbs_set_t             mepa_driver_prbs_set;
    mepa_driver_prbs_get_t             mepa_driver_prbs_get;
    mepa_driver_prbs_monitor_set_t     mepa_driver_prbs_monitor_set;
    mepa_driver_prbs_monitor_get_t     mepa_driver_prbs_monitor_get;
    mepa_ts_driver_t                   *mepa_ts;
    mepa_macsec_driver_t               *mepa_macsec;
    uint32_t id;                  /**< Id of the driver */
    uint32_t mask;                /**< Mask of the driver */
    struct mepa_driver *next; /**< Pointer to the next driver */
} mepa_driver_t;

/** \brief Represents the instance of the driver */
typedef struct mepa_device {
    /** \brief Pointer to the driver that creates the device */
    mepa_driver_t *drv;

    uint32_t numeric_handle;

    const mepa_callout_t    *callout;
    struct mepa_callout_ctx *callout_ctx;

    void *data; /**< Private data */
} mepa_device_t;

/** \brief Wrapper over an array and counter. It is used by init functions to
 *         return the array of drivers
 **/
typedef struct mepa_drivers {
    mepa_driver_t *phy_drv; /**< Pointer to an array of drivers */
    unsigned int count;         /**< Number of entries in phy_drv */
} mepa_drivers_t;

void *mepa_mem_alloc_int(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                         struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                         size_t                                   size);

void mepa_mem_free_int(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                       struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                       void                                    *ptr);

/** \brief Internal function for drivers to use to build mepa_inst structure */
struct mepa_device *mepa_create_int(
        mepa_driver_t                           *drv,
        const mepa_callout_t    MEPA_SHARED_PTR *callout,
        struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
        struct mepa_board_conf                  *conf,
        int                                      size_of_private_data);

mepa_rc mepa_delete_int(mepa_device_t *dev);

/** \brief Default driver that match any PHY */
mepa_drivers_t mepa_default_phy_driver_init();

/** \brief Returns drivers for mscc PHY */
mepa_drivers_t mepa_mscc_driver_init();

/** \brief Returns drivers for malibu PHY */
mepa_drivers_t mepa_malibu_driver_init();

/** \brief Returns drivers for venice PHY */
mepa_drivers_t mepa_venice_driver_init();

/** \brief Returns drivers for AQR PHY */
mepa_drivers_t mepa_aqr_driver_init();

/** \brief Returns drivers for intel PHY */
mepa_drivers_t mepa_intel_driver_init();

/** \brief Returns drivers for ksz PHY */
mepa_drivers_t mepa_ksz9031_driver_init();

/** \brief Returns drivers for lan8814 PHY */
mepa_drivers_t mepa_lan8814_driver_init();

/** \brief Returns drivers for lan8770 PHY */
mepa_drivers_t mepa_lan8770_driver_init();

/** \brief Returns drivers for lan884x PHY */
mepa_drivers_t mepa_lan884x_driver_init();

#include <microchip/ethernet/hdr_end.h>
#endif /**< _MICROCHIP_ETHERNET_PHY_API_PHY_DRV_H_ */
