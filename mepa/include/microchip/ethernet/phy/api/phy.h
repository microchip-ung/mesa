// Copyright (c) 2004-2021 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_PHY_API_PHY_H_
#define _MICROCHIP_ETHERNET_PHY_API_PHY_H_

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

/** \brief Forigen pointer. MEPA only passes this pointer around, application instanting
 *   MEPA must define this type. If no bus-addressing data is needed, a null
 *   pointer can be used. */

struct mepa_callout_ctx;

/**
 * \brief MMD management read function (IEEE 802.3 clause 45).
 *
 * \param ctx  [IN]   Pointer to a callout structure.
 * \param mmd  [IN]   MMD register.
 * \param addr [IN]   Register address.
 * \param value[OUT]  Pointer to a value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_mmd_read_t)(struct mepa_callout_ctx           *ctx,
                                   const uint8_t                      mmd,
                                   const uint16_t                     addr,
                                   uint16_t                          *const value);



/**
 * \brief MMD management read increment function (IEEE 802.3 clause 45)
 *
 * \param ctx   [IN]  Pointer to a callout structure.
 * \param mmd   [IN]  MMD register.
 * \param addr  [IN]  Start register address (0-65535).
 * \param buf   [OUT] The register values (pointer provided by user).
 * \param count [IN]  Number of register reads (increment register reads).
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_mmd_read_inc_t)(struct mepa_callout_ctx       *ctx,
                                       const uint8_t                  mmd,
                                       const uint16_t                 addr,
                                       uint16_t                       *const buf,
                                       uint8_t                        count);

/**
 * \brief MMD management write function (IEEE 802.3 clause 45).
 *
 * \param ctx   [IN]  Pointer to a callout structure
 * \param mmd   [IN]  MMD register.
 * \param addr  [IN]  Start register address (0-65535).
 * \param value [OUT] Pointer to a value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_mmd_write_t)(struct mepa_callout_ctx          *ctx,
                                    const uint8_t                     mmd,
                                    const uint16_t                    addr,
                                    const uint16_t                    value);

/**
 * \brief MII management read function (IEEE 802.3 clause 22)
 *
 * \param ctx   [IN] Pointer to a callout structure
 * \param addr  [IN] Start register address (0-65535).
 * \param value [OUT]Pointer to a value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_miim_read_t)(struct mepa_callout_ctx          *ctx,
                                    const uint8_t                     addr,
                                    uint16_t                         *const value);

/**
 * \brief MII management write function (IEEE 802.3 clause 22)
 *
 * \param ctx   [IN]   Pointer to a callout structure.
 * \param addr  [IN]   Start register address (0-65535).
 * \param value [OUT]  Pointer to a value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_miim_write_t)(struct mepa_callout_ctx         *ctx,
                                     const uint8_t                    addr,
                                     const uint16_t                   value);


/**
 * \brief SPI  read function
 *
 * \param ctx   [IN]  Pointer to a callout structure
 * \param mmd   [IN]  MMD register.
 * \param addr  [IN]  Start register address (0-65535).
 * \param value [OUT] Pointer to a value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_spi_read_t)(struct mepa_callout_ctx          *ctx,
                                   const uint8_t                     mmd,
                                   const uint16_t                    addr,
                                   uint32_t                         *const value);

/**
 * \brief SPI  64bit read function
 *
 * \param ctx   [IN]  Pointer to a callout structure
 * \param mmd   [IN]  MMD register.
 * \param addr  [IN]  Start register address (0-65535).
 * \param value [OUT] Pointer to a value (64bit).
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_spi_read_64bit_t)(struct mepa_callout_ctx          *ctx,
                                         const uint8_t                     mmd,
                                         const uint16_t                    addr,
                                         uint64_t                         *const value);


/**
 * \brief SPI  write function
 *
 * \param ctx   [IN]  Pointer to a callout structure
 * \param mmd   [IN]  MMD register.
 * \param addr  [IN]  Start register address (0-65535).
 * \param value [OUT] Pointer to a value.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_spi_write_t)(struct mepa_callout_ctx          *ctx,
                                    const uint8_t                     mmd,
                                    const uint16_t                    addr,
                                    const uint32_t                    value);


/**
 * \brief SPI  64bit write function
 *
 * \param ctx   [IN]  Pointer to a callout structure
 * \param mmd   [IN]  MMD register.
 * \param addr  [IN]  Start register address (0-65535).
 * \param value [OUT] Pointer to a value.(64bit).
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
typedef mepa_rc (*mepa_spi_write_64bit_t)(struct mepa_callout_ctx          *ctx,
                                          const uint8_t                     mmd,
                                          const uint16_t                    addr,
                                          const uint64_t                    value);


typedef void (*mepa_trace_func_t)(const mepa_trace_data_t *data, va_list args);
typedef void *(*mepa_mem_alloc_t)(struct mepa_callout_ctx *ctx, size_t size);
typedef void (*mepa_mem_free_t)(struct mepa_callout_ctx *ctx, void *ptr);

/** \brief MEPA trace function
 *   The MEPA trace function is a single global variable. Traces will only work
 *   when a function is assigned to 'MEPA_TRACE_FUNCTION'.
 *   It is not per-instance, as it can be essential to provide tracing capability
 *   while creating instances. */

extern mepa_trace_func_t MEPA_TRACE_FUNCTION;

/** \brief PHY synchronisation callbacks passed by application */
typedef void (*mepa_lock_func_t)(const mepa_lock_t *const lock);





/** \brief Address mode that is specific for mchp phy. */
typedef struct mepa_callout {
    mepa_mmd_read_t        mmd_read;
    mepa_mmd_read_inc_t    mmd_read_inc;
    mepa_mmd_write_t       mmd_write;
    mepa_miim_read_t       miim_read;
    mepa_miim_write_t      miim_write;
    mepa_spi_read_t        spi_read;
    mepa_spi_write_t       spi_write;
    mepa_spi_read_64bit_t  spi_read_64bit;
    mepa_spi_write_64bit_t spi_write_64bit;
    mepa_lock_func_t       lock_enter;
    mepa_lock_func_t       lock_exit;

    mepa_mem_alloc_t       mem_alloc;
    mepa_mem_free_t        mem_free;
} mepa_callout_t;

struct vtss_state_s;
typedef struct vtss_state_s *vtss_inst_t;

typedef struct mepa_board_conf {
    uint32_t                 numeric_handle;

    // By default all PHYs in the VTSS library will use default instance located
    // in mepa/vtss/src/vtss.c (as a static variable).
    // This makes it easy for simple usage, but sometime it is desirable to
    // control what PHYs belong to what instance. This can be controlled using
    // the below attributes:
    // - If vtss_instance_create is set to 1, then a new instance is created and
    //   pointer to the instance is avialable in the vtss_instance_ptr field.
    // - If vtss_instance_use is set to 1, then the pointer from
    //   'vtss_instance_ptr' is used for the given MEPA device.
    uint32_t                 vtss_instance_create;
    uint32_t                 vtss_instance_use;
    vtss_inst_t              vtss_instance_ptr;
} mepa_board_conf_t;

/** \brief Create a new MEPA instance.
 *
 *   NOTE: 'callout' and 'callout_ctx' pointers must be considered as SHARED,
 *   meaning that they must remain valid until all MEPA instances are deleted.
 *   MEPA will use these poiner values in sub-sequence MEPA calls.
 *   The same instance of the callout should be used for all MEPA instances.
 *   Each PHY should have a unique callout_ctx which contains mdio address
 *   controllers etc. */

struct mepa_device *mepa_create(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                struct mepa_board_conf  *conf);

/**
 * \brief Clears up the data allocated in the probe function.
 *
 * \param dev [IN] Driver Instance.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_delete(struct mepa_device *dev);

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
mepa_rc mepa_reset(struct mepa_device *dev,
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
mepa_rc mepa_poll(struct mepa_device *dev,
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
mepa_rc mepa_conf_set(struct mepa_device *dev,
                      const mepa_conf_t *conf);

/**
 * \brief Get the current interface configuraton of the PHY.
 *
 * \param dev  [IN]   Driver instance.
 * \param conf [OUT]   PHY configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n                                                    **/
mepa_rc mepa_conf_get(struct mepa_device *dev,
                      mepa_conf_t *const conf);

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
mepa_rc mepa_if_set(struct mepa_device *dev,
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
mepa_rc mepa_if_get(struct mepa_device *dev,
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
mepa_rc mepa_power_set(struct mepa_device *dev,
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
mepa_rc mepa_cable_diag_start(struct mepa_device *dev,
                              int mode);


/**
 * \brief Gets result from cable diagnostics.
 *
 * \param  dev     [IN]  Driver instance.
 * \param  result  [OUT] Result from cable diagnostics.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_cable_diag_get(struct mepa_device *dev,
                            mepa_cable_diag_result_t *result);

/**
 * \brief Sets the media type in case the port is a dual media port with external phy.
 *
 *  \param dev           [IN]  Driver instance.
 *  \param phy_media_if  [IN]  Media type.
 *
 *  \return
 *     MEPA_RC_NOT_IMPLEMENTED when not supported.
 **/
mepa_rc mepa_media_set(struct mepa_device *dev,
                       mepa_media_interface_t phy_media_if);

/**
 * \brief Get the media type in case the port is a dual media port with external
 * phy.
 *
 *  \param dev           [IN]  Driver instance.
 *  \param phy_media_if  [OUT] Media type.
 *
 *  \return
 *     MEPA_RC_NOT_IMPLEMENTED when not supported.
 **/
mepa_rc mepa_media_get(struct mepa_device *dev,
                       mepa_media_interface_t *phy_media_if);

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
mepa_rc mepa_aneg_status_get(struct mepa_device *dev,
                             mepa_aneg_status_t *status);


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
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_clause22_read(struct mepa_device *dev,
                           uint32_t address,
                           uint16_t *const value);

/**
 * \brief  PHY register write access using clause22 format for debugging
 *  address : bits 0 - 4 : address within page
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
mepa_rc mepa_clause22_write(struct mepa_device *dev,
                            uint32_t address,
                            uint16_t value);

/**
 * \brief  PHY register read access using clause45 format for debugging
 *  address : bits 0  - 15 : address within page
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
mepa_rc mepa_clause45_read(struct mepa_device *dev,
                           uint32_t address,
                           uint16_t *const value);

/**
 * \brief  PHY register write access using clause45 format for debugging
 *  address : bits 0  - 15 : address within page
 *                 16 - 31 : page number
 *
 *  \param dev     [IN]  Driver instance.
 *  \param address [OUT] Adress.
 *  \param value   [IN]  Value.
 *
 *  \return
 *    MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *    MEPA_RC_OK on success.
 **/
mepa_rc mepa_clause45_write(struct mepa_device *dev,
                            uint32_t address,
                            uint16_t value);

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
mepa_rc mepa_event_enable_set(struct mepa_device *dev,
                              mepa_event_t event,
                              mesa_bool_t enable);

/**
 * \brief  Get the PHY events currently enabled.
 *
 * \param dev    [IN] Driver instance.
 * \param event  [OUT] Event mask which is currently enabled in PHY.
 *
 * \return
 *    MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *    MEPA_RC_OK on success.
 **/
mepa_rc mepa_event_enable_get(struct mepa_device *dev,
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
mepa_rc mepa_event_poll(struct mepa_device *dev,
                        mepa_event_t *const ev_mask);

/**
 * \brief Set loopback. Used for debugging purpose
 *
 * \param dev       [IN] Driver Instance.
 * \param loopback  [IN] Loopback Types.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_loopback_set(struct mepa_device *dev,
                          const mepa_loopback_t *loopback);

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
mepa_rc mepa_loopback_get(struct mepa_device *dev,
                          mepa_loopback_t *const loopback);

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
mepa_rc mepa_gpio_mode_set(struct mepa_device *dev,
                           const mepa_gpio_conf_t *data);

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
mepa_rc mepa_gpio_out_set(struct mepa_device *dev,
                          uint8_t gpio_no,
                          mepa_bool_t value);

/**
 * \brief  Get the GPIO pin value.
 *
 * \param dev      [IN]  Driver Instance.
 * \param gpio_no  [IN]  GPIO Number.
 * \param value    [OUT]  Value.
 *
 * \return
 *    MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *    MEPA_RC_OK on success.
 **/
mepa_rc mepa_gpio_in_get(struct mepa_device *dev,
                         uint8_t gpio_no,
                         mepa_bool_t *const value);

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
mepa_rc mepa_synce_clock_conf_set(struct mepa_device *dev,
                                  const mepa_synce_clock_conf_t *conf);

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
mepa_rc mepa_link_base_port(struct mepa_device *dev,
                            struct mepa_device *base_dev,
                            uint8_t packet_idx);

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
mepa_rc mepa_phy_info_get(struct mepa_device *dev,
                          mepa_phy_info_t *const phy_info);

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
mepa_rc mepa_isolate_mode_conf(struct mepa_device *dev,
                               const mepa_bool_t iso_en);

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
mepa_rc mepa_debug_info_dump(struct mepa_device *dev,
                             const mepa_debug_print_t pr,
                             const mepa_debug_info_t   *const info);

/** - I2C ---------------------------------------------------- */
/**
 * \brief I2C Read - perform i2C I/O thru PHY for Reading SFP using i2C i/f
 *
 * \param dev  [IN]            Driver instance.
 * \param i2c_mux [IN]         The i2c clock mux
 * \param i2c_reg_addr [IN]    The i2c register address to access.
 * \param i2c_device_addr [IN] The i2c address of the device to access
 * \param word_access [IN]     Set to TRUE if the register data width is 16bit. FALSE = 8 bits data width.
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
mepa_rc mepa_i2c_read(mepa_device_t *dev,
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
 * \param value [OUT]          Pointer to where array which in going to contain the values read.
 *
 * \return Return code.
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_ERROR on Error \n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_i2c_write(mepa_device_t *dev,
                       const uint8_t i2c_mux,
                       const uint8_t i2c_reg_addr,
                       const uint8_t i2c_dev_addr,
                       const mepa_bool_t word_access,
                       uint8_t cnt,
                       const uint8_t *value);

/**
 *
 * \brief I2C clock frequency select
 *
 * \param dev  [IN]            Driver instance.
 * \param clk_value [IN]       Pointer to where array containing the clock frequency values to write.
 *
 * \return Return code.
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_ERROR on Error \n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_i2c_clock_select(mepa_device_t *dev,
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
mepa_rc mepa_sqi_read(struct mepa_device *dev, uint32_t *const value);

/**
 * \brief PHY write SOF value
 *
 * \param dev   [IN]   Driver instance.
 * \param conf [IN]   SOF value to be Configured
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_start_of_frame_conf_set(struct mepa_device *dev, mepa_start_of_frame_conf_t *const conf);

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
mepa_rc mepa_start_of_frame_conf_get(struct mepa_device *dev, mepa_start_of_frame_conf_t *const value);

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
mepa_rc mepa_framepreempt_get(struct mepa_device *dev, mepa_bool_t *const value);

/**
 * \brief Start PHY Self-Test Frame
 *
 * \param dev     [IN]  Driver instance.
 * \param inf     [IN]  selftest information
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_selftest_start(struct mepa_device *dev, const mepa_selftest_info_t *inf);

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
mepa_rc mepa_selftest_read(struct mepa_device *dev, mepa_selftest_info_t *const selftest_inf);

/**
 * \brief To Set the PRBS7 sequence configuration
 *
 * \param dev      [IN]  Driver instance.
 * \param conf     [IN] PRBS7 information.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_prbs_set(struct mepa_device *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const mepa_conf);

/**
 * \brief To Get the PRBS7 sequence configuration
 *
 * \param dev      [IN]  Driver instance.
 * \param conf     [OUT] PRBS7 information.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_prbs_get(struct mepa_device *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const mepa_conf);

/**
 * \brief To inject an error
 *
 * \param dev       [IN]  Driver instance.
 * \param value     [IN] Error count information
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_prbs_monitor_set(struct mepa_device *dev, mepa_phy_prbs_monitor_conf_t *const value);

/**
 * \brief To Verify the PRBS7
 *
 * \param dev       [IN]  Driver instance.
 * \param value     [OUT] Error count information
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported. \n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_prbs_monitor_get(struct mepa_device *dev, mepa_phy_prbs_monitor_conf_t *const value);

#include <microchip/ethernet/hdr_end.h>
#endif
