// Copyright (c) 2004-2021 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_PHY_API_PHY_DRV_H_
#define _MICROCHIP_ETHERNET_PHY_API_PHY_DRV_H_

#include <mepa_ts_driver.h>
#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// PHY DRIVER
//
// This API defines the interface used by the switch application to interact
// with the PHY. Using this interface the switch application should not know
// which PHY it is using.
//
// Each PHY driver needs to implement the following methods for a minimum
// configuration:
//  mepa_driver_delete_t
//  mepa_driver_probe_t
//  mepa_driver_poll_t
//  mepa_driver_conf_set_t

void MEPA_trace(mepa_trace_group_t  group,
                mepa_trace_level_t  level,
                const char         *location,
                uint32_t            line,
                const char         *format,
                ...);

// Clears up the data allocated in the probe function.
typedef mepa_rc (*mepa_driver_delete_t)(struct mepa_device *dev);

// Resets PHY.
// intf   [IN] Interface to which to reset the phy.
typedef mepa_rc (*mepa_driver_reset_t)(
        struct mepa_device *dev,
        const mepa_reset_param_t *rst_conf);

// Get the current status of the PHY.
// status        [OUT] PHY status.
typedef mepa_rc (*mepa_driver_poll_t)(
        struct mepa_device *dev,
        mepa_status_t *status);

// Set the configuration to the PHY.
// conf          [IN] PHY configuration.
typedef mepa_rc (*mepa_driver_conf_set_t)(
    struct mepa_device *dev, const mepa_conf_t *conf);

// Get the current interface configuration of PHY
typedef mepa_rc (*mepa_driver_conf_get_t)(struct mepa_device *dev, mepa_conf_t *const conf);

typedef mepa_rc (*mepa_driver_if_set_t)(
        struct mepa_device *dev,
        mepa_port_interface_t intf);

// Get the PHY interface based on speed.
// speed         [IN] Speed.
// intf          [OUT] Interface that is needed to be used by the port.
typedef mepa_rc (*mepa_driver_if_get_t)(
        struct mepa_device *dev,
        mepa_port_speed_t speed,
        mepa_port_interface_t *intf);

//  Sets the power mode.
//  power         [IN] Power.
typedef mepa_rc (*mepa_driver_power_set_t)(
        struct mepa_device *dev,
        mepa_power_mode_t power);

//  Starts cable_diag.
//  mode          [IN] Mode in which to start.
typedef mepa_rc (*mepa_driver_cable_diag_start_t)(
    struct mepa_device *dev, int mode);

//  Gets result from cable diagnostics.
//  result        [OUT] Result from cable diagnostics.
typedef mepa_rc (*mepa_driver_cable_diag_get_t)(
    struct mepa_device *dev, mepa_cable_diag_result_t *result);

//  Sets the media type in case the port is a dual media port with external phy.
//  phy_media_if  [IN] Media type.
typedef mepa_rc (*mepa_driver_media_set_t)(
    struct mepa_device *dev, mepa_media_interface_t phy_media_if);

//  Create an instance of the driver and initialize the PHY.
//  mode           [IN] Address mode.
typedef struct mepa_device *(*mepa_driver_probe_t)(
    struct mepa_driver                  *dev,
    const mepa_callout_t    MEPA_SHARED_PTR *callout,
    struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
    struct mepa_board_conf              *conf);

//  Gets copper PHY auto-negotiation status.
//  mode           [IN] PHY 1G status.
typedef mepa_rc (*mepa_driver_aneg_status_get_t)(
    struct mepa_device *dev, mepa_aneg_status_t *status);

// PHY register read access using clause22 format for debugging
// address : bits 0 - 4 : address within page
//                5 - 31: page number
typedef mepa_rc (*mepa_driver_clause22_read_t)(struct mepa_device *dev,
                 uint32_t address, uint16_t *const value);

// PHY register write access using clause22 format for debugging
// address : bits 0 - 4 : address within page
//                5 - 31: page number
typedef mepa_rc (*mepa_driver_clause22_write_t)(struct mepa_device *dev,
                 uint32_t address, uint16_t value);

// PHY register read access using clause45 format for debugging
// address : bits 0  - 15 : address within page
//                16 - 31 : page number
typedef mepa_rc (*mepa_driver_clause45_read_t)(struct mepa_device *dev,
                 uint32_t address, uint16_t *const value);

// PHY register write access using clause45 format for debugging
// address : bits 0  - 15 : address within page
//                16 - 31 : page number
typedef mepa_rc (*mepa_driver_clause45_write_t)(struct mepa_device *dev,
                 uint32_t address, uint16_t value);

//  Enable PHY events.
//  event          [IN] PHY event mask to be enabled.
//  enable         [IN] enable or disable the event
typedef mepa_rc (*mepa_driver_event_enable_set_t)(struct mepa_device *dev,
                 mepa_event_t event, mesa_bool_t enable);

//  Get the PHY events currently enabled.
//  event          [OUT] Event mask which is currently enabled in PHY
typedef mepa_rc (*mepa_driver_event_enable_get_t)(struct mepa_device *dev,
                 mepa_event_t *const event);

//  Poll the status of PHY events
//  ev_mask        [OUT] Event mask containing current status of PHY events.
typedef mepa_rc (*mepa_driver_event_poll_t)(struct mepa_device *dev, mepa_event_t *const ev_mask);

// Set loopback. Used for debugging purpose
typedef mepa_rc (*mepa_driver_loopback_set_t)(struct mepa_device *dev, const mepa_loopback_t *loopback);

// Get current loopback configuration
typedef mepa_rc (*mepa_driver_loopback_get_t)(struct mepa_device *dev, mepa_loopback_t *const loopback);

// Set the GPIO pin mode to input, output or alternate function
typedef mepa_rc (*mepa_driver_gpio_mode_set_t)(struct mepa_device *dev, const mepa_gpio_conf_t *data);

// Set the GPIO pin value
typedef mepa_rc (*mepa_driver_gpio_out_set_t)(struct mepa_device *dev, uint8_t gpio_no, mepa_bool_t value);

// Get the GPIO pin value
typedef mepa_rc (*mepa_driver_gpio_in_get_t)(struct mepa_device *dev, uint8_t gpio_no, mepa_bool_t * const value);

// Configure recovered clock
typedef mepa_rc (*mepa_driver_synce_clock_conf_set_t)(struct mepa_device *dev, const mepa_synce_clock_conf_t *conf);

// Link Base Port. Used for accessing the chip leavel common resources
typedef mepa_rc (*mepa_driver_link_base_port_t)(struct mepa_device *dev, struct mepa_device *base_dev, uint8_t packet_idx);

// Get phy information like phy-id, revision etc.
typedef mepa_rc (*mepa_driver_phy_info_get_t)(struct mepa_device *dev, mepa_phy_info_t *const phy_info);

// Enable/Disable Isolate mode
typedef mepa_rc (*mepa_driver_isolate_mode_conf_t)(struct mepa_device *dev, const mepa_bool_t iso_en);

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
    mepa_ts_driver_t                   *mepa_ts;

    uint32_t id;                  // Id of the driver
    uint32_t mask;                // Mask of the driver
    struct mepa_driver *next; // Pointer to the next driver
} mepa_driver_t;

// Represents the instance of the driver
typedef struct mepa_device {
    // Pointer to the driver that creates the device
    mepa_driver_t *drv;

    uint32_t numeric_handle;

    const mepa_callout_t    *callout;
    struct mepa_callout_ctx *callout_ctx;

    void *data; // Private data
} mepa_device_t;

// Wrapper over an array and counter. It is used by init functions to return the
// array of drivers
typedef struct mepa_drivers {
    mepa_driver_t *phy_drv; // Pointer to an array of drivers
    unsigned int count;         // Number of entries in phy_drv
} mepa_drivers_t;

void *mepa_mem_alloc_int(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                         struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                         size_t                                   size);

void mepa_mem_free_int(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                       struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                       void                                    *ptr);

// Internal function for drivers to use to build mepa_inst structure
struct mepa_device *mepa_create_int(
        mepa_driver_t                           *drv,
        const mepa_callout_t    MEPA_SHARED_PTR *callout,
        struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
        struct mepa_board_conf                  *conf,
        int                                      size_of_private_data);

mepa_rc mepa_delete_int(mepa_device_t *dev);

// Default driver that match any PHY
mepa_drivers_t mepa_default_phy_driver_init();

// Returns drivers for mscc PHY
mepa_drivers_t mepa_mscc_driver_init();

// Returns drivers for malibu PHY
mepa_drivers_t mepa_malibu_driver_init();

// Returns drivers for venice PHY
mepa_drivers_t mepa_venice_driver_init();

// Returns drivers for AQR PHY
mepa_drivers_t mepa_aqr_driver_init();

// Returns drivers for intel PHY
mepa_drivers_t mepa_intel_driver_init();

// Returns drivers for ksz PHY
mepa_drivers_t mepa_ksz9031_driver_init();

// Returns drivers for lan8814 PHY
mepa_drivers_t mepa_lan8814_driver_init();

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_PHY_API_PHY_DRV_H_
