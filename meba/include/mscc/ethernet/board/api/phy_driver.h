// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MSCC_ETHERNET_BOARD_PHY_DRIVER_H_
#define _MSCC_ETHERNET_BOARD_PHY_DRIVER_H_

#include <mscc/ethernet/board/api/base.h>
#include <mscc/ethernet/switch/api.h>
#include <mscc/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// PHY DRIVER
//
// This API defines the interface used by the switch application to interact
// with the PHY. Using this interface the switch application should not know
// which PHY it is using.
//
// Each PHY driver needs to implement the following methods for a minimum
// configuration:
//  meba_phy_driver_delete_t
//  meba_phy_driver_probe_t
//  meba_phy_driver_poll_t
//  meba_phy_driver_conf_set_t

// Contains methods that are specific to each phy.
struct meba_phy_driver;

// Represents an instance of the meba_phy_driver.
struct meba_phy_device;

typedef mesa_rc (*mmd_read_t)(const mesa_inst_t  inst,
                              const mesa_port_no_t  port_no,
                              const uint8_t         mmd,
                              const uint16_t        addr,
                              uint16_t              *const value);

typedef mesa_rc (*mmd_write_t)(const mesa_inst_t  inst,
                               const mesa_port_no_t  port_no,
                               const uint8_t         mmd,
                               const uint16_t        addr,
                               const uint16_t        value);

typedef mesa_rc (*miim_read_t)(const mesa_inst_t    inst,
                               const mesa_chip_no_t         chip_no,
                               const mesa_miim_controller_t miim_controller,
                               const uint8_t                miim_addr,
                               const uint8_t                addr,
                               uint16_t                     *const value);

typedef mesa_rc (*miim_write_t)(const mesa_inst_t    inst,
                                const mesa_chip_no_t         chip_no,
                                const mesa_miim_controller_t miim_controller,
                                const uint8_t                miim_addr,
                                const uint8_t                addr,
                                const uint16_t               value);

typedef void (*debug_func_t)(meba_trace_level_t level,
                             const char              *location,
                             uint32_t                line_no,
                             const char              *fmt,
                             ...);

// Address mode that is specific for mscc phy.
typedef struct {
    mmd_read_t              mmd_read;
    mmd_write_t             mmd_write;
    miim_read_t             miim_read;
    miim_write_t            miim_write;
    mesa_inst_t             inst;
    mesa_port_no_t          port_no;
    struct meba_inst       *meba_inst;
    debug_func_t            debug_func;
    mesa_port_interface_t   mac_if;
} mscc_phy_driver_address_t;

// Union that contains all the values for address mode. Enumeration
// meba_phy_driver_address_mode_t decides which address type to be used.
typedef union {
    mscc_phy_driver_address_t mscc_address;
} meba_phy_driver_address_val_t;

// Enumeration of all possible address modes.
typedef enum {
    mscc_phy_driver_address_mode,
} meba_phy_driver_address_mode_t;

// Main structure that contains the address mode and the address value, these
// values has to be filled up by the switch application.
typedef struct meba_phy_driver_address {
    meba_phy_driver_address_mode_t mode;
    meba_phy_driver_address_val_t val;
} meba_phy_driver_address_t;

// Represents the status of the PHY.
typedef struct {
    mesa_bool_t link;        // Link is up
    mesa_port_speed_t speed; // Speed
    mesa_bool_t fdx;         // Full duplex
    mesa_aneg_t aneg;        // Auto-negotiation
    mesa_bool_t copper;      // For dual-media ports
    mesa_bool_t fiber;       // For dual-media ports
} meba_phy_driver_status_t;

// Represents the configuration that is applied to PHY.
typedef struct {
    mesa_port_speed_t speed;       // Forced port speed
    mesa_bool_t fdx;               // Forced duplex mode
    mesa_bool_t flow_control;      // Flow control (Standard 802.3x)
    uint32_t adv_dis;              // Auto neg advertisement disable
    meba_port_admin_state_t admin; // Admin state
} meba_phy_driver_conf_t;

// Advertise disable flags.
typedef enum {
    MEBA_PHY_ADV_DIS_HDX = 0x00000001,     // Disable Half duplex
    MEBA_PHY_ADV_DIS_FDX = 0x00000002,     // Disable Full duplex
    MEBA_PHY_ADV_UP_MEP_LOOP = 0x00000004, // Use port for UP MEP loop port
    MEBA_PHY_ADV_DIS_2500M = 0x00000008,   // Disable 2.5G mode
    MEBA_PHY_ADV_DIS_1G = 0x00000010,      // Disable 1G mode
    MEBA_PHY_ADV_DIS_100M = 0x00000040,    // Disable 100Mbit mode
    MEBA_PHY_ADV_DIS_10M = 0x00000080,     // Disable 10Mbit mode
    MEBA_PHY_ADV_DIS_5G = 0x00000100,      // Disable 5G mode
    MEBA_PHY_ADV_DIS_10G = 0x00000200,     // Disable 10G mode
    MEBA_PHY_ADV_DIS_RESTART_ANEG = 0x00000400, // Do not restart aneg
    MEBA_PHY_ADV_DIS_SPEED =
        (MEBA_PHY_ADV_DIS_10M | MEBA_PHY_ADV_DIS_100M | MEBA_PHY_ADV_DIS_1G |
         MEBA_PHY_ADV_DIS_2500M | MEBA_PHY_ADV_DIS_5G |
         MEBA_PHY_ADV_DIS_10G), // All speed bits
    MEBA_PHY_ADV_DIS_DUPLEX =
        (MEBA_PHY_ADV_DIS_HDX | MEBA_PHY_ADV_DIS_FDX), // All duplex bits
    MEBA_PHY_ADV_DIS_ALL = (MEBA_PHY_ADV_DIS_SPEED | MEBA_PHY_ADV_DIS_DUPLEX |
                            MEBA_PHY_ADV_UP_MEP_LOOP) // All valid bits
} meba_phy_adv_dis_t;

// Clears up the data allocated in the probe function.
typedef mesa_rc (*meba_phy_driver_delete_t)(struct meba_phy_device *dev);

// Resets PHY.
// intf   [IN] Interface to which to reset the phy.
typedef mesa_rc (*meba_phy_driver_reset_t)(struct meba_phy_device *dev,
                                           mesa_phy_media_interface_t intf);

// Get the current status of the PHY.
// status        [OUT] PHY status.
typedef mesa_rc (*meba_phy_driver_poll_t)(struct meba_phy_device *dev,
                                          meba_phy_driver_status_t *status);

// Set the configuration to the PHY.
// cap           [IN] Port capabilities.
// conf          [IN] PHY configuration.
typedef mesa_rc (*meba_phy_driver_conf_set_t)(
    struct meba_phy_device *dev, meba_port_cap_t cap,
    const meba_phy_driver_conf_t *conf);

// Get the PHY interface based on speed.
// speed         [IN] Speed.
// intf          [OUT] Interface that is needed to be used by the port.
typedef mesa_rc (*meba_phy_driver_if_get_t)(struct meba_phy_device *dev,
                                            mesa_port_speed_t speed,
                                            mesa_port_interface_t *intf);

// Get the media type used by PHY that supports 10G speed.
// mt            [OUT] Media type.
typedef mesa_rc (*meba_phy_driver_mt_get_t)(struct meba_phy_device *dev,
                                            mesa_sd10g_media_type_t *mt);

//  Sets the power mode.
//  power         [IN] Power.
typedef mesa_rc (*meba_phy_driver_power_set_t)(struct meba_phy_device *dev,
                                               mesa_phy_power_mode_t power);

//  Starts veriphy.
//  mode          [IN] Mode in which to start.
typedef mesa_rc (*meba_phy_driver_veriphy_start_t)(struct meba_phy_device *,
                                                   int mode);
//  Gets result from veriphy.
//  result        [OUT] Result from veriphy.
typedef mesa_rc (*meba_phy_driver_veriphy_get_t)(
    struct meba_phy_device *dev, mesa_phy_veriphy_result_t *result);

//  Sets the media type in case the port is a dual media port with external phy.
//  phy_media_if  [IN] Media type.
typedef mesa_rc (*meba_phy_driver_media_set_t)(
    struct meba_phy_device *dev, mesa_phy_media_interface_t phy_media_if);

//  Create an instance of the driver and initialize the PHY.
//  mode           [IN] Address mode.
typedef struct meba_phy_device *(*meba_phy_driver_probe_t)(
    struct meba_phy_driver *dev, const meba_phy_driver_address_t *mode);

//  Gets PHY 1G status.
//  mode           [IN] PHY 1G status.
typedef mesa_rc (*meba_phy_driver_status_1g_get_t)(
    struct meba_phy_device *dev, mesa_phy_status_1g_t *status);

// Full list of PHY driver interface
#define MEBA_LIST_OF_API_PHY_DRIVER_CALLS \
    X(meba_phy_driver_delete)             \
    X(meba_phy_driver_reset)              \
    X(meba_phy_driver_poll)               \
    X(meba_phy_driver_conf_set)           \
    X(meba_phy_driver_if_get)             \
    X(meba_phy_driver_mt_get)             \
    X(meba_phy_driver_power_set)          \
    X(meba_phy_driver_veriphy_start)      \
    X(meba_phy_driver_veriphy_get)        \
    X(meba_phy_driver_media_set)          \
    X(meba_phy_driver_probe)              \
    X(meba_phy_driver_status_1g_get)

typedef struct meba_phy_driver {
    meba_phy_driver_delete_t         meba_phy_driver_delete;
    meba_phy_driver_reset_t          meba_phy_driver_reset;
    meba_phy_driver_poll_t           meba_phy_driver_poll;
    meba_phy_driver_conf_set_t       meba_phy_driver_conf_set;
    meba_phy_driver_if_get_t         meba_phy_driver_if_get;
    meba_phy_driver_mt_get_t         meba_phy_driver_mt_get;
    meba_phy_driver_power_set_t      meba_phy_driver_power_set;
    meba_phy_driver_veriphy_start_t  meba_phy_driver_veriphy_start;
    meba_phy_driver_veriphy_get_t    meba_phy_driver_veriphy_get;
    meba_phy_driver_media_set_t      meba_phy_driver_media_set;
    meba_phy_driver_probe_t          meba_phy_driver_probe;
    meba_phy_driver_status_1g_get_t  meba_phy_driver_status_1g_get;

    uint32_t id;                  // Id of the driver
    uint32_t mask;                // Mask of the driver
    struct meba_phy_driver *next; // Pointer to the next driver
} meba_phy_driver_t;

// Represents the instance of the driver
typedef struct meba_phy_device {
    // Pointer to the driver that creates the device
    meba_phy_driver_t *drv;

    void *data; // Private data
} meba_phy_device_t;

// Wrapper over an array and counter. It is used by init functions to return the
// array of drivers
typedef struct meba_phy_drivers {
    meba_phy_driver_t *phy_drv; // Pointer to an array of drivers
    unsigned int count;         // Number of entries in phy_drv
} meba_phy_drivers_t;

// Default driver that match any PHY
meba_phy_drivers_t meba_default_phy_driver_init();

// Returns drivers for mscc PHY
meba_phy_drivers_t meba_mscc_driver_init();

// Returns drivers for malibu PHY
meba_phy_drivers_t meba_malibu_driver_init();

// Returns drivers for venice PHY
meba_phy_drivers_t meba_venice_driver_init();

#include <mscc/ethernet/board/api/hdr_end.h>
#endif
