// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_BOARD_POE_H_
#define _MICROCHIP_ETHERNET_BOARD_POE_H_

#include <microchip/ethernet/board/api/poe_ctrl.h>
#include <stdint.h>
#include <microchip/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// MEBA PoE API.
//
// This is the PoE API, which defines how to interact with the PoE
// controllers located on a board controlled by MEBA.
//
// Most of the functionality is provided by the 'poe_ctrl.h' API (an API
// matching a single controller) - go read that.
//
// This API offers a function to get a list of controller instances.  It will
// make sure to instantiate drivers matching the PoE controller HW. The number
// of controller created, and the set of ports associated to each controller
// depends on how the board is build (and how it is reflected in the
// implementation of this API).
//
// Beside from creating the controller instances, the API also offers wrapper
// functions to find which controller owns a port, and forward the request to
// that controller.
//
//
// For developers only
// ===================
//
// When implementing the 'microchip/ethernet/board/api/poe.h' and the
// 'microchip/ethernet/board/api/poe_ctrl.h' API, please follow these guide lines:
// - poe_ctrl.h implementation must work on all boards.
// - poe.h is board specific (or specific to a family of boards).
// - Customer designing new boards, should only implement poe.h, and can use
//   the poe_ctrl.h implementation as is.

// All PoE controllers within the system.
typedef struct {
    // Number of controllers.
    uint32_t controller_count;

    // Controllers.
    meba_poe_ctrl_inst_t *controllers;
} meba_poe_system_t;

// Get a reference to a PoE controller and a port handle
// based on a Board and port number.
//
// port_no    [IN]    Port number
// controller [OUT]   PoE controller
// handle     [OUT]   PoE port handle
typedef mesa_rc (*meba_poe_get_controller_handle_t)(
        struct meba_inst               *inst,
        mesa_port_no_t                  port_no,
        meba_poe_ctrl_inst_t          **controller,
        meba_poe_port_handle_t         *handle);


// Setup PoE for a given port.
// port_no   [IN]  Port to configure.
// cfg       [IN]  Port configuration.
typedef mesa_rc (*meba_poe_port_cfg_set_t)(
        struct meba_inst               *inst,
        mesa_port_no_t                  port_no,
        meba_poe_port_cfg_t            *cfg);


// Get PoE status for a given port
// port_no   [IN]  Port number.
// status    [IN]  Port PoE status.
typedef mesa_rc (*meba_poe_port_status_get_t)(
        struct meba_inst               *inst,
        mesa_port_no_t                  port_no,
        meba_poe_port_status_t         *const status);

// Get a data structure with all the PoE controllers in the system. This
// may only be called once for every meba instance.
//
// system    [OUT] System.
typedef mesa_rc (*meba_poe_system_get_t)(
        struct meba_inst               *inst,
        meba_poe_system_t             **const system);


// Initialize the MEBA PoE subsystem.
// may only be called once.
// inst              [IN] Reference to the meba instance
// meba_poe_init_params_t *tPoe_init_params [IN]
typedef mesa_rc (*meba_poe_system_initialize_t)(
        struct meba_inst       *inst,
        meba_poe_init_params_t *tPoe_init_params);


// Perform chip detection.
//
typedef mesa_rc (*meba_poe_do_detection_t)(
        struct meba_inst               *inst);

// Perform chip initialization.
typedef mesa_rc (*meba_poe_chip_initialization_t)(
    struct meba_inst   *inst,
    mesa_bool_t interruptible_power,
    int16_t     restart_cause);

// Perform chip synchronization
typedef mesa_rc (*meba_poe_sync_t)(
        struct meba_inst               *inst);

// Set a PoE controller configuration.
// cfg    [IN]  Port configuration.
typedef mesa_rc (*meba_poe_cfg_set_t)(
        struct meba_inst               *inst,
        meba_poe_global_cfg_t          *cfg);

// Get PoE controller status.
// status [OUT] Controller status.
typedef mesa_rc (*meba_poe_status_get_t)(
        struct meba_inst               *inst,
        meba_poe_status_t              *status);


// Get PoE controller status.
// status [OUT] Controller capabilities.
typedef mesa_rc (*meba_poe_capabilities_get_t)(
        struct meba_inst               *inst,
        meba_poe_ctrl_cap_t            *capabilities);

// Reset PoE controller.
typedef mesa_rc (*meba_poe_reset_command_t)(
        struct meba_inst               *inst);

// Save PoE controller parameters
typedef mesa_rc (*meba_poe_save_command_t)(
        struct meba_inst               *inst);

// Enable debug traces.
// port_no   [IN]  Port number.
// trace_buf [OUT] Buffer to receive debug traces
// buf_size  [IN]  Size of buffer.
typedef mesa_rc (*meba_poe_debug_t)(
        struct meba_inst               *inst,
        mesa_port_no_t                  port_no,
        char                           *var,
        uint32_t                        str_len,
        char                           *title ,
        char                           *tx_str ,
        char                           *rx_str ,
        char                           *msg,
        int                             max_msg_len);

// Perform the Firmware upgrade.
// This function upgrades the PoE controller firmware.  The poe_firmware_upgrade
// function must be called before this function to check firmware versions, and
// set the controller to MEBA_POE_FIRMWARE_UPGRADE.
// reset         [IN]  If true, the controller is reset after upgrade.
// size          [IN]  Size of firmware data in bytes.
// firmware      [IN]  Firmware to load.
typedef int (*meba_poe_firmware_upgrade_t)(
        struct meba_inst               *inst,
        mesa_bool_t                     reset,
        uint32_t                        size,
        const char                     *firmware);

// Preparation of Firmware upgrade.
// If the version_check parameter is true, this function will check the firmware
// version against the version of the installed firmware.  If the firmware
// versions are identical the return code will be
// MESA_RC_ERR_POE_FIRMWARE_IS_UP_TO_DATE.  If the firmware versions are not
// identical the return code will be MESA_RC_OK, and the state of the controller
// will be set to MEBA_POE_FIRMWARE_UPGRADE
//
// If the parameter version_check is false, the state of the controller will be
// set to MEBA_POE_FIRMWARE_UPGRADE, and the return code will be MESA_RC_OK.
//
// version_check [IN]  If true, firmware is only upgradeed if the version is
//                     diffferent from the currently loaded.
// size          [IN]  Size of firmware data in bytes.
// firmware      [IN]  Firmware to load.
typedef mesa_rc (*meba_poe_prepare_firmware_upgrade_t)(
        struct meba_inst               *inst,
        mesa_bool_t                     version_check,
        uint32_t                        size,
        const char                     *firmware);

// Get PoE supply limits
// max             [OUT] Maximum supply power
// min             [OUT] Minimum supply power
// system_reserve  [OUT] Power reserved for switch
typedef mesa_rc (*meba_poe_supply_limits_get_t)(
    struct meba_inst          *inst,
    meba_poe_ctrl_psu_t        id,
    meba_poe_psu_input_prob_t *psu_prop);

// Get PoE port capabilities
// port_no       [IN]  Port number
// capabilities  [OUT] Port capabilities
typedef mesa_rc (*meba_poe_port_capabilities_get_t)(
        struct meba_inst               *inst,
        mesa_port_no_t                  port_no,
        meba_poe_port_cap_t            *capabilities);

// Set PD configuration
// port_no   [IN]  Port number.
// pd_data   [IN]  PD data to configure.
typedef mesa_rc (*meba_poe_port_pd_data_set_t)(
        struct meba_inst               *inst,
        mesa_port_no_t                  port_no,
        meba_poe_pd_data_t             *pd_data);

// Set PoE BT PD configuration.
// This function shall be called when the PoE application receives a type 3 or
// type 4 LLDp pdu with PoE information which shall be reflected in the PoE
// controller configuration.
//
// inst      [IN]  Controller instance.
// port_no   [IN]  Port handle
// pd_data   [IN]  PD data to configure.
typedef mesa_rc (*meba_poe_port_pd_bt_data_set_t)(
    struct meba_inst                   *inst,
    mesa_port_no_t                      port_no,
    meba_poe_pd_bt_data_t              *pd_data);

// Clear port lldp mode
// port_no   [IN]  Port number.
typedef mesa_rc (*meba_poe_port_pd_data_clear_t)(
        struct meba_inst               *inst,
        mesa_port_no_t                  port_no);

// Get PoE controller firmware version.
// inst     [IN]  Controller instance.
// max_size [IN]  The maximum size of firmware version.
// version  [OUT] The firmware version.
typedef mesa_rc (*meba_poe_version_get_t)(
        struct meba_inst               *inst,
        uint32_t                        max_size,
        char                           *version);

// List of PoE APIs
#define MEBA_LIST_OF_API_POE_CALLS                     \
    X(meba_poe_system_initialize)                      \
    X(meba_poe_system_get)                             \
    X(meba_poe_get_controller_handle)                  \
    X(meba_poe_do_detection)                           \
    X(meba_poe_chip_initialization)                    \
    X(meba_poe_sync)                                   \
    X(meba_poe_version_get)                            \
    X(meba_poe_port_cfg_set)                           \
    X(meba_poe_port_status_get)                        \
    X(meba_poe_cfg_set)                                \
    X(meba_poe_status_get)                             \
    X(meba_poe_capabilities_get)                       \
    X(meba_poe_reset_command)                          \
    X(meba_poe_save_command)                           \
    X(meba_poe_debug)                                  \
    X(meba_poe_firmware_upgrade)                       \
    X(meba_poe_prepare_firmware_upgrade)               \
    X(meba_poe_supply_limits_get)                      \
    X(meba_poe_port_capabilities_get)                  \
    X(meba_poe_port_pd_data_set)                       \
    X(meba_poe_port_pd_bt_data_set)                    \
    X(meba_poe_port_pd_data_clear)                     \

typedef struct {
#define X(name) name##_t name;
    MEBA_LIST_OF_API_POE_CALLS
#undef X
} meba_api_poe_t;

#include <microchip/ethernet/board/api/hdr_end.h>
#endif  // _MICROCHIP_ETHERNET_BOARD_POE_H_
