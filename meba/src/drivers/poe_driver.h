// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_BOARD_POE_DRIVER_H_
#define _MICROCHIP_ETHERNET_BOARD_POE_DRIVER_H_

#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/switch/api/types.h>

typedef struct {
    const char   *i2c_device;
    const uint8_t i2c_address;
} i2c_config_t;

typedef void (*pointer_to_meba_poe_io_reset_t)(mesa_bool_t);

typedef struct {

    mesa_bool_t is_bt;

    // PD692x0 family detection method
    meba_poe_controller_type_t ePoE_Controller_Type_default;

    // System has 4 modes = 15/30/60/90 (applicable for all poe ports)
    meba_poe_port_max_power_t ePoE_port_max_power_default;

    // BT complient port operation Mode
    uint8_t bt_operation_mode_compliant_15w_default;
    uint8_t bt_operation_mode_compliant_30w_default;
    uint8_t bt_operation_mode_compliant_60w_default;
    uint8_t bt_operation_mode_compliant_90w_default;

    // BT none complient port operation Mode
    uint8_t bt_operation_mode_none_compliant_15w_default;
    uint8_t bt_operation_mode_none_compliant_30w_default;
    uint8_t bt_operation_mode_none_compliant_60w_default;
    uint8_t bt_operation_mode_none_compliant_90w_default;

    // BT special modes Port Operations Mode for legacy
    uint8_t bt_operation_mode_legacy_90W_poh_default;
    uint8_t bt_operation_mode_legacy_60W_ignore_pd_class_default;
    uint8_t bt_operation_mode_legacy_90W_ignore_pd_class_default;

    // gpio number used to reset poe ports
    uint8_t reset_poe_gpio_number;

    // the final (from appl or from api h file) init parameters to init poe module
    meba_poe_init_params_t poe_init_params;

    // prebt - power higher priority port.
    uint8_t indv_mask_prebt_ignore_higher_priority_default;

    // prebt - En/Dis support of legacy detection.
    uint8_t indv_mask_prebt_supports_legact_detection_default;

    // prebt - En/Dis supports backoff
    uint8_t indv_mask_prebt_supports_backoff_default;

    // prebt - en/Dis MESSAGE_READY pin notification.
    uint8_t indv_mask_prebt_message_ready_notify_default;

    // prebt - led stream type
    uint8_t indv_mask_prebt_led_stream_type_default;

    // prebt - En/Dis Layer 2 PD commands.
    uint8_t indv_mask_prebt_layer2_lldp_enable_default;

    // prebt - accept/ignored Port Priority recived from the PD
    uint8_t indv_mask_prebt_layer2_priority_by_PD_default;

    // prebt - use 4-pair matrix commands.
    uint8_t indv_mask_prebt_matrix_support_4P_default;

    // bt - power higher priority port.
    uint8_t indv_mask_BT_ignore_higher_priority_default;

    // bt - expand Resistor detection range up to range to 55 K.
    uint8_t indv_mask_BT_support_high_res_detection_default;

    // bt - Initialization of the I2C module system after 10 seconds of
    // inactivity.
    uint8_t indv_mask_BT_i2c_restart_enable_default;

    // bt - led stream type
    uint8_t indv_mask_BT_led_stream_type_default;

    // bt - HOCPP - high_over Current Pulse Protection
    uint8_t indv_mask_BT_HOCPP_default;

    // bt - single_detection_fail_event
    uint8_t indv_mask_BT_bt_single_detection_fail_event_default;

    // bt - PSE powering PSE checking
    uint8_t indv_mask_BT_PSE_powering_PSE_checking_default;

    // bt - Layer2 Power Allocation Limit
    uint8_t indv_mask_BT_layer2_power_allocation_limit_default;

    // bt - Port LED Blinks at invalid signature or connection-check error
    uint8_t
        indv_mask_BT_Port_LED_blinks_at_invalid_signature_or_connection_check_error_default;

    // bt - Support adding lldp half priority
    uint8_t indv_mask_BT_support_adding_lldp_half_priority_default;

    // -----------  PREBT Power Management mode of operation
    // ----------------------//

    // Selects the method of calculating total power consumption.
    uint8_t prebt_pm1_default;

    // Selects the power limit at the port (maximum or according to class or
    // predefined).
    uint8_t prebt_pm2_default;

    // Selects the start condition. (Not recommended for new designs, keep 0x00).
    uint8_t prebt_pm3_default;
} meba_poe_parameters_t;

/**
 * \brief Open an I2C device and configure I2C address
 *
 * \param filename       [IN] Filename for the I2C device
 * \param i2c_addr       [IN] i2c address to communicate with
 *
 * \return File descriptor for I2C driver
 */
int meba_pd69200_i2c_adapter_open(const char *filename, uint8_t i2c_addr);

/**
 * \brief Initialize driver
 *
 * \param inst              [IN] MEBA instance.
 * \param driver_name       [IN] Driver name.
 * \param capabilities      [IN] Capabilities.
 * \param port_map          [IN] Port map.
 * \param port_map_length   [IN] Number of elements in port map.
 * \param psu_map           [IN] Psu map.
 * \param psu_map_length    [IN] Number of elements in psu_map.
 * \param read_function     [IN] Read function.
 * \param write_function    [IN] Write function.
 * \param debug             [OUT] Board debug output.
 *
 * \return meba_poe_ctrl_inst
 */
void meba_pd69200_driver_init(meba_poe_ctrl_inst_t       *inst,
                              char const                 *driver_name,
                              int                         adapter_fd,
                              meba_poe_ctrl_cap_t         capabilities,
                              meba_poe_port_properties_t *port_map,
                              uint32_t                    port_map_length,
                              meba_poe_psu_input_prob_t  *psu_map,
                              uint32_t                    psu_map_length,
                              meba_debug_t                debug,
                              meba_poe_parameters_t       tMeba_poe_parameters);

/**
 * \brief Initialize driver
 *
 * \param inst              [IN] MEBA instance.
 * \param driver_name       [IN] Driver name.
 * \param capabilities      [IN] Capabilities.
 * \param port_map          [IN] Port map.
 * \param port_map_length   [IN] Number of elements in port map.
 * \param psu_map           [IN] Psu map.
 * \param psu_map_length    [IN] Number of elements in psu_map.
 * \param read_function     [IN] Read function.
 * \param write_function    [IN] Write function.
 * \param debug             [OUT] Board debug output.
 *
 * \return meba_poe_ctrl_inst
 */
void meba_pd69200bt_driver_init(meba_poe_ctrl_inst_t       *inst,
                                char const                 *driver_name,
                                int                         adapter_fd,
                                meba_poe_ctrl_cap_t         capabilities,
                                meba_poe_port_properties_t *port_map,
                                uint32_t                    port_map_length,
                                meba_poe_psu_input_prob_t  *psu_map,
                                uint32_t                    psu_map_length,
                                meba_debug_t                debug,
                                meba_poe_parameters_t tMeba_poe_parameters);

#endif // _MICROCHIP_ETHERNET_BOARD_POE_DRIVER_H_
