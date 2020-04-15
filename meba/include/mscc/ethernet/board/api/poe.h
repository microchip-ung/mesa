/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef _MSCC_ETHERNET_BOARD_POE_H_
#define _MSCC_ETHERNET_BOARD_POE_H_

#include <mscc/ethernet/board/api/poe_ctrl.h>
#include <stdint.h>

/**
 * \file
 * \brief MEBA PoE API.
 *
 * \details This is the PoE API, which defines how to interact with the PoE
 * controllers located on a board controlled by MEBA.
 *
 * Most of the functionality is provided by the 'poe_ctrl.h' API (an API
 * matching a single controller) - go read that.
 *
 * This API offers a function to get a list of controller instances.  It will
 * make sure to instantiate drivers matching the PoE controller HW. The number
 * of controller created, and the set of ports associated to each controller
 * depends on how the board is build (and how it is reflected in the
 * implementation of this API).
 *
 * Beside from creating the controller instances, the API also offers wrapper
 * functions to find which controller owns a port, and forward the request to
 * that controller.
 *
 *
 * For developers only
 * ===================
 *
 * When implementing the 'mscc/ethernet/board/api/poe.h' and the
 * 'mscc/ethernet/board/api/poe_ctrl.h' API, please follow these guide lines:
 * - poe_ctrl.h implementation must work on all boards.
 * - poe.h is board specific (or specific to a family of boards).
 * - Customer designing new boards, should only implement poe.h, and can use
 *   the poe_ctrl.h implementation as is.
 */

/** All PoE controllers within the system. */
typedef struct {
    /** Number of controllers. */
    uint32_t controller_count;

    /** Controllers. */
    meba_poe_ctrl_inst_t *controllers;
} meba_poe_system_t;

/**
 * \brief Get a reference to a PoE controller and a port handle
 * based on a Board and port number.
 *
 * \param inst       [IN]    MEBA instance.
 * \param port_no    [IN]    Port number
 * \param controller [OUT]   PoE controller
 * \param handle     [OUT]   PoE port handle
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_get_controller_handle_t)(
        const meba_inst_t               inst,
        mesa_port_no_t                  port_no,
        meba_poe_ctrl_inst_t          **controller,
        meba_poe_port_handle_t         *handle);


/**
 * \brief Setup PoE for a given port.
 *
 * \param inst      [IN]  MEBA instance.
 * \param port_no   [IN]  Port to configure.
 * \param cfg       [IN]  Port configuration.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_port_cfg_set_t)(
        const meba_inst_t               inst,
        mesa_port_no_t                  port_no,
        meba_poe_port_cfg_t            *cfg);


/**
 * \brief Get PoE status for a given port
 *
 * \param inst      [IN]  MEBA instance.
 * \param port_no   [IN]  Port number.
 * \param status    [IN]  Port PoE status.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_port_status_get_t)(
        const meba_inst_t               inst,
        mesa_port_no_t                  port_no,
        meba_poe_port_status_t         *const status);

/**
 * \brief Get a data structure with all the PoE controllers in the system. This
 * may only be called once for every meba instance.
 *
 * \param meba      [IN]  MEBA instance.
 * \param system    [OUT] System.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_system_get_t)(
        const meba_inst_t               inst,
        meba_poe_system_t             **const system);


/**
 * \brief Initialize the MEBA PoE subsystem.
 * may only be called once.
 *
 * \param inst      [IN]  MEBA instance.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_system_initialize_t)(
        const meba_inst_t               inst);


/**
 * \brief Perform chip detection.
 *
 * \param inst   [IN]  MEBA instance.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_do_detection_t)(
        const meba_inst_t               inst);

/**
 * \brief Perform chip initialization.
 *
 * \param inst   [IN]  MEBA instance.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_chip_initialization_t)(
        const meba_inst_t               inst);

/**
 * \brief Perform chip synchronization
 *
 * \param inst   [IN]  MEBA instance.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_sync_t)(
        const meba_inst_t               inst);

/**
 * \brief Set a PoE controller configuration.
 *
 * \param inst   [IN]  MEBA instance.
 * \param cfg    [IN]  Port configuration.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_cfg_set_t)(
        const meba_inst_t               inst,
        meba_poe_cfg_t                 *cfg);

/**
 * \brief Get PoE controller status.
 *
 * \param inst   [IN]  MEBA instance.
 * \param status [OUT] Controller status.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_status_get_t)(
        const meba_inst_t               inst,
        meba_poe_status_t              *status);


/**
 * \brief Get PoE controller status.
 *
 * \param inst   [IN]  MEBA instance.
 * \param status [OUT] Controller capabilities.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_capabilities_get_t)(
        const meba_inst_t               inst,
        meba_poe_ctrl_cap_t            *capabilities);

/**
 * \brief Resset PoE controller.
 *
 * \param inst   [IN]  MEBA instance.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_reset_command_t)(
        const meba_inst_t               inst);

/**
 * \brief Enable debug traces.
 *
 * \param inst      [IN]  MEBA instance.
 * \param port_no   [IN]  Port number.
 * \param trace_buf [OUT] Buffer to receive debug traces
 * \param buf_size  [IN]  Size of buffer.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_debug_t)(
        const meba_inst_t               inst,
        mesa_port_no_t                  port_no,
        uint8_t                        *buf,
        int                             buf_size);

/**
 * \brief Perform the Firmware upgrade.
 *
 * \details  This function upgrades the PoE controller firmware.
 * The poe_firmware_upgrade function must be called before this function to check firmware versions,
 * and set the controller to MEBA_POE_FIRMWARE_UPGRADE.
 *
 * \param inst          [IN]  MEBA instance
 * \param reset         [IN]  If true, the controller is reset after upgrade.
 * \param size          [IN]  Size of firmware data in bytes.
 * \param firmware      [IN]  Firmware to load.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_firmware_upgrade_t)(
        const meba_inst_t               inst,
        mesa_bool_t                     reset,
        uint32_t                        size,
        const char                     *firmware);

/**
 * \brief Preparation of Firmware upgrade.
 *
 * \details If the version_check parameter is true, this function will check the
 * firmware version against the version of the installed firmware.
 * If the firmware versions are identical the return code will be
 * MESA_RC_ERR_POE_FIRMWARE_VER_NOT_NEW.
 * If the firmware versions are not identical the return code will be MESA_RC_OK,
 * and the state of the controller will be set to MEBA_POE_FIRMWARE_UPGRADE
 *
 * If the parameter version_check is false, the state of the controller will be
 * set to MEBA_POE_FIRMWARE_UPGRADE, and the return code will be MESA_RC_OK.
 *
 * \param inst          [IN]  MEBA instance
 * \param version_check [IN]  If true, firmware is only upgradeed if the version
 *                            is diffferent from the currently loaded.
 * \param size          [IN]  Size of firmware data in bytes.
 * \param firmware      [IN]  Firmware to load.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_prepare_firmware_upgrade_t)(
        const meba_inst_t               inst,
        mesa_bool_t                     version_check,
        uint32_t                        size,
        const char                     *firmware);

/**
 * \brief Get PoE supply limits
 *
 * \param inst            [IN]  MEBA instance.
 * \param max             [OUT] Maximum supply power
 * \param min             [OUT] Minimum supply power
 * \param system_reserve  [OUT] Power reserved for switch
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_supply_limits_get_t)(
    const meba_inst_t          inst,
    meba_poe_ctrl_psu_t        id,
    meba_poe_psu_input_prob_t *psu_prop);

/**
 * \brief Get PoE port capabilities
 *
 * \param inst          [IN]  MEBA instance.
 * \param port_no       [IN]  Port number
 * \param capabilities  [OUT] Port capabilities
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_port_capabilities_get_t)(
        const meba_inst_t               inst,
        mesa_port_no_t                  port_no,
        meba_poe_port_cap_t            *capabilities);

/**
 * \brief Set PD configuration
 *
 * \param inst      [IN]  MEBA instance.
 * \param port_no   [IN]  Port number.
 * \param pd_data   [IN]  PD data to configure.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_port_pd_data_set_t)(
        const meba_inst_t               inst,
        mesa_port_no_t                  port_no,
        meba_poe_pd_data_t             *pd_data);

/**
 * \brief Set PoE BT PD configuration.
 * This function shall be called when the PoE application receives a type 3 or type 4
 * LLDp pdu with PoE information which shall be reflected in the PoE controller configuration.
 *
 * \param inst      [IN]  Controller instance.
 * \param port_no   [IN]  Port handle
 * \param pd_data   [IN]  PD data to configure.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_port_pd_bt_data_set_t)(
    const meba_inst_t          inst,
    mesa_port_no_t             port_no,
    meba_poe_pd_bt_data_t     *pd_data);

/**
 * \brief Clear port lldp mode
 *
 * \param inst      [IN]  MEBA instance.
 * \param port_no   [IN]  Port number.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_port_pd_data_clear_t)(
        const meba_inst_t               inst,
        mesa_port_no_t                  port_no);

/**
 * \brief Get PoE controller firmware version.
 *
 * \param inst     [IN]  Controller instance.
 * \param max_size [IN]  The maximum size of firmware version.
 * \param version  [OUT] The firmware version.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_version_get_t)(
        const meba_inst_t               inst,
        uint32_t                        max_size,
        char                           *version);

/** List of PoE APIs  */
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
    X(meba_poe_debug)                                  \
    X(meba_poe_firmware_upgrade)                       \
    X(meba_poe_prepare_firmware_upgrade)               \
    X(meba_poe_supply_limits_get)                      \
    X(meba_poe_port_capabilities_get)                  \
    X(meba_poe_port_pd_data_set)                       \
    X(meba_poe_port_pd_bt_data_set)                    \
    X(meba_poe_port_pd_data_clear)                     \

/** \brief Board functions struct */
typedef struct {
/** \brief Fill up the struct with function pointers */
#define X(name) name##_t name;
    MEBA_LIST_OF_API_POE_CALLS
#undef X
} meba_api_poe_t;

#endif  // _MSCC_ETHERNET_BOARD_POE_H_
