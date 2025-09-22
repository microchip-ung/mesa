// Copyright (c) 2004-2024 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "microchip/ethernet/board/api.h"
#include "meba_poe_generic.h"
#include "lan966x_poe_hw_cfg.h"

static meba_poe_parameters_t poe_default_parameters = {
    // poe firmware type - TYPE_PREBT , GEN6_BT
    .eMeba_poe_firmware_type = LAN9668_POE_FIRMWARE_TYPE_DEFAULT,

    // only 1 poe controller is applicable
    .poe_controllers_count = MEBA_POE_ONE_CONTROLLER,

    // PD692x0 family detection method
    .ePoE_gen6_controller_detection_type = LAN9668_POE_GEN6_PD692x0_CONTROLLER_TYPE_DEFAULT,

    // BT complient port operation Mode
    .bt_operation_mode_compliant_15w_default = LAN9668_BT_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_compliant_30w_default = LAN9668_BT_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_compliant_60w_default = LAN9668_BT_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_compliant_90w_default = LAN9668_BT_COMPLIANT_90W_DEFAULT,

    // BT none complient port operation Mode
    .bt_operation_mode_none_compliant_15w_default = LAN9668_BT_NON_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_none_compliant_30w_default = LAN9668_BT_NON_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_none_compliant_60w_default = LAN9668_BT_NON_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_none_compliant_90w_default = LAN9668_BT_NON_COMPLIANT_90W_DEFAULT,

    // special Port operation modes for legacy
    .bt_operation_mode_legacy_90W_poh_default = LAN9668_BT_OPERATION_MODE_LEGACY_90W_POH_DEFAULT,
    .bt_operation_mode_legacy_60W_ignore_pd_class_default =
        LAN9668_BT_OPERATION_MODE_LEGACY_60W_IGNORE_PD_CLASS_DEFAULT,
    .bt_operation_mode_legacy_90W_ignore_pd_class_default =
        LAN9668_BT_OPERATION_MODE_LEGACY_90W_IGNORE_PD_CLASS_DEFAULT,

    .reset_poe_gpio_number = LAN9668_RESET_POE_GPIO_NUMBER,

    // prebt led stream type
    .indv_mask_prebt_led_stream_type_default = LAN9668_INDV_MASK_PREBT_LED_STREAM_TYPE_DEFAULT,
    // power higher priority port
    .indv_mask_prebt_ignore_higher_priority_default =
        LAN9668_INDV_MASK_PREBT_IGNORE_HIGHER_PRIORITY_DEFAULT,
    // En/Dis support of legacy detection
    .indv_mask_prebt_supports_legact_detection_default =
        LAN9668_INDV_MASK_PREBT_SUPPORTS_LEGACY_DETECTION_DEFAULT,
    // En/Dis supports backoff
    .indv_mask_prebt_supports_backoff_default = LAN9668_INDV_MASK_PREBT_SUPPORTS_BACKOFF_DEFAULT,
    // en/Dis MESSAGE_READY pin notification
    .indv_mask_prebt_message_ready_notify_default =
        LAN9668_INDV_MASK_PREBT_MESSAGE_READY_NOTIFY_DEFAULT,
    // En/Dis Layer 2 PD commands
    .indv_mask_prebt_layer2_lldp_enable_default =
        LAN9668_INDV_MASK_PREBT_LAYER2_LLDP_ENABLE_DEFAULT,
    // accept/ignored Port Priority recived from the PD
    .indv_mask_prebt_layer2_priority_by_PD_default =
        LAN9668_INDV_MASK_PREBT_LAYER2_PRIORITY_BY_PD_DEFAULT,
    // use 4-pair matrix commands
    .indv_mask_prebt_matrix_support_4P_default = LAN9668_INDV_MASK_PREBT_MATRIX_SUPPORT_4P_DEFAULT,
    // power higher priority port
    .indv_mask_BT_ignore_higher_priority_default =
        LAN9668_INDV_MASK_BT_IGNORE_HIGHER_PRIORITY_DEFAULT,
    // expand Resistor detection range up to range to 55 K
    .indv_mask_BT_support_high_res_detection_default =
        LAN9668_INDV_MASK_BT_SUPPORT_HIGH_RES_DETECTION_DEFAULT,
    // Initialization of the I2C module system after 10 seconds of inactivity
    .indv_mask_BT_i2c_restart_enable_default = LAN9668_INDV_MASK_BT_I2C_RESTART_ENABLE_DEFAULT,
    // led stream type
    .indv_mask_BT_led_stream_type_default = LAN9668_INDV_MASK_BT_LED_STREAM_TYPE_DEFAULT,
    // HOCPP - high_over Current Pulse Protection
    .indv_mask_BT_HOCPP_default = LAN9668_INDV_MASK_BT_HOCPP_DEFAULT,
    .indv_mask_BT_PSE_powering_PSE_checking_default =
        LAN9668_INDV_MASK_BT_PSE_POWERING_PSE_CHECKING_DEFAULT, // PSE powering PSE checking
    // Layer2 Power Allocation Limit
    .indv_mask_BT_layer2_power_allocation_limit_default =
        LAN9668_INDV_MASK_BT_LAYER2_POWER_ALLOCATION_LIMIT_DEFAULT,
    // Port LED Blinks at invalid signature or connection-check error
    .indv_mask_BT_Port_LED_blinks_at_invalid_signature_or_connection_check_error_default =
        LAN9668_INDV_MASK_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR_DEFAULT,
    // Support adding lldp half priority
    .indv_mask_BT_support_adding_lldp_half_priority_default =
        LAN9668_INDV_MASK_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY_DEFAULT,

    // -----  PREBT Power Management mode of operation -----//
    // Selects the method of calculating total power consumption.
    .prebt_pm1_default = LAN9668_PM1_PREBT_DEFAULT,
    // Selects the power limit at the port (maximum or according to class or predefined).
    .prebt_pm2_default = LAN9668_PM2_PREBT_DEFAULT,
    // Selects the start condition. (Not recommended for new designs, keep 0x00).
    .prebt_pm3_default = LAN9668_PM3_PREBT_DEFAULT};

meba_poe_psu_input_prob_t lan9668_power_supplies[] = {
    {.id = MEBA_POE_CTRL_PSU_ALL, // PowerSupply-ID
                                  // PwrSuply Min-Pwr
     .min_w = 0,
     // PwrSuply Max-Pwr
     .max_w = LAN9668_POE_POWER_SUPPLY_MAX_POWER_W_DEFAULT,
     // PwrSuply Def-Capab
     .def_w = LAN9668_POE_POWER_SUPPLY_DEF_POWER_W_DEFAULT,
     // System PwrUsage
     .system_pwr_usage_w = LAN9668_POE_POWER_SUPPLY_SYSTEM_POWER_USAGE_DEFAULT,
     // User Conig 1=Yes,0=No
     .user_configurable = LAN9668_POE_POWER_SUPPLY_MAX_POWER_USER_CONFIG_DEFAULT}
};

meba_poe_system_t lan9668_pd69200_system;

static i2c_config_t lan9668_i2c_config = {"/dev/i2c-1", LAN9668_POE_I2C_ADDRESS};

mesa_rc meba_poe_system_get(meba_inst_t inst, meba_poe_system_t **const system)
{
    *system = &lan9668_pd69200_system;
    return MESA_RC_OK;
}

mesa_rc meba_poe_system_initialize(meba_inst_t inst, meba_poe_init_params_t *tPoe_init_params)
{
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    poe_default_parameters.max_poe_ports = tPoe_init_params->max_poe_ports;

    if ((tPoe_init_params->poe_type_from_tag >= 1) && (tPoe_init_params->poe_type_from_tag <= 2)) {
        poe_default_parameters.eMeba_poe_firmware_type = tPoe_init_params->poe_type_from_tag;
        printf("\n\rpoe firmware type from tag=%d\n\r", tPoe_init_params->eMeba_poe_firmware_type);
    } else {
        // poe firmware type - TYPE_PREBT , GEN6_BT
        poe_default_parameters.eMeba_poe_firmware_type = LAN9668_POE_FIRMWARE_TYPE_DEFAULT;
        printf("\n\rpoe firmware type default=%d\n\r", tPoe_init_params->eMeba_poe_firmware_type);
    }

    // overide tMeba_poe_init_params params if using H file parameters
    // overide meba power supply by appl init_params
    if (!tPoe_init_params->use_poe_static_parameters) {
        lan9668_power_supplies->def_w = tPoe_init_params->power_supply_default_power_limit;
        lan9668_power_supplies->max_w = tPoe_init_params->power_supply_max_power_w;
        lan9668_power_supplies->system_pwr_usage_w =
            tPoe_init_params->power_supply_internal_pwr_usage;

        // when PS external user can change the power supply limit power
        lan9668_power_supplies->user_configurable =
            tPoe_init_params->ePower_supply_internal_external;

        poe_default_parameters.eMeba_poe_firmware_type = tPoe_init_params->eMeba_poe_firmware_type;
    }

    if (poe_default_parameters.eMeba_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_GEN6_BT) {
        // Do poe chip detection and fill
        // lan9668_ctrl.api = ....;
        // lan9668_ctrl.private_data = ....;
        lan9668_pd69200_system.controller_count = 1;
        lan9668_pd69200_system.controllers =
            malloc(sizeof(meba_poe_ctrl_inst_t) * lan9668_pd69200_system.controller_count);

        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            poe_default_parameters.max_poe_ports =
                sizeof(lan9668_pd69200_4pairs_port_map) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface
            .debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                   "using: max_poe_ports=%d, power_supply_max_power_w=%d, eMeba_poe_firmware_type=%d",
                   poe_default_parameters.max_poe_ports, lan9668_power_supplies->max_w,
                   poe_default_parameters.eMeba_poe_firmware_type);

        lan9668_pd69200_system.controllers[0].index = 0;
        meba_pd_bt_driver_init(&lan9668_pd69200_system.controllers[0], "pd69x00bt",
                               meba_pd_i2c_adapter_open(&lan9668_pd69200_system.controllers[0],
                                                        lan9668_i2c_config.i2c_device,
                                                        lan9668_i2c_config.i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                   MEBA_POE_CTRL_INTERRUPTIBLE_POWER |
                                   MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST |
                                   MEBA_POE_CTRL_LEGACY_PD_CLASS_MODE,
                               lan9668_pd69200_4pairs_port_map,
                               sizeof(lan9668_pd69200_4pairs_port_map) /
                                   sizeof(meba_poe_port_properties_t),
                               lan9668_power_supplies,
                               sizeof(lan9668_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug, poe_default_parameters);
    } else if (poe_default_parameters.eMeba_poe_firmware_type ==
               MEBA_POE_FIRMWARE_TYPE_GEN6_PREBT) {
        // Do poe chip detection and fill
        // lan9668_ctrl.api = ....;
        // lan9668_ctrl.private_data = ....;
        lan9668_pd69200_system.controller_count = 1;
        lan9668_pd69200_system.controllers =
            malloc(sizeof(meba_poe_ctrl_inst_t) * lan9668_pd69200_system.controller_count);

        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            poe_default_parameters.max_poe_ports =
                sizeof(lan9668_pd69200_4pairs_port_map) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface
            .debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                   "using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                   poe_default_parameters.max_poe_ports, lan9668_power_supplies->max_w,
                   poe_default_parameters.eMeba_poe_firmware_type);

        lan9668_pd69200_system.controllers[0].index = 0;
        meba_pd69200_driver_init(&lan9668_pd69200_system.controllers[0], "pd69x00at",
                                 meba_pd_i2c_adapter_open(&lan9668_pd69200_system.controllers[0],
                                                          lan9668_i2c_config.i2c_device,
                                                          lan9668_i2c_config.i2c_address),
                                 MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                     MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                                     MEBA_POE_CTRL_INTERRUPTIBLE_POWER,
                                 lan9668_pd69200_4pairs_port_map,
                                 sizeof(lan9668_pd69200_4pairs_port_map) /
                                     sizeof(meba_poe_port_properties_t),
                                 lan9668_power_supplies,
                                 sizeof(lan9668_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                                 inst->iface.debug, poe_default_parameters);
    } else {
        return MESA_RC_ERROR;
    }

    return MESA_RC_OK;
};

mesa_rc meba_poe_get_controller_handle(meba_inst_t             inst,
                                       mesa_port_no_t          port_no,
                                       meba_poe_ctrl_inst_t  **controller,
                                       meba_poe_port_handle_t *handle)
{
    for (int i = 0; i < lan9668_pd69200_system.controller_count; ++i) {
        for (int j = 0; j < lan9668_pd69200_system.controllers[i].port_map_length; ++j) {
            if (lan9668_pd69200_system.controllers[i].port_map[j].port_no == port_no) {
                *controller = &lan9668_pd69200_system.controllers[i];
                *handle = lan9668_pd69200_system.controllers[i].port_map[j].handle;
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

// returns values:
// - MESA_RC_OK : when all controllers are responded (not MESA_RC_ERROR)
// - MESA_RC_ERROR : when one or more controllers are responded with MESA_RC_ERROR
mesa_rc meba_poe_do_detection(meba_inst_t inst)
{
    mesa_rc rc = MESA_RC_ERROR;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    for (int i = 0; i < lan9668_pd69200_system.controller_count; ++i) {
        if (lan9668_pd69200_system.controllers[i]
                .api->meba_poe_ctrl_do_detection(&lan9668_pd69200_system.controllers[i]) ==
            MESA_RC_ERROR) {
            inst->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                              "Detection Failed for controller: %d", i);
        } else {
            rc = MESA_RC_OK;
        }
    }
    return rc;
}

static meba_api_poe_t public_functions = {
    .meba_poe_system_initialize = meba_poe_system_initialize,
    .meba_poe_system_get = meba_poe_system_get,
    .meba_poe_get_controller_handle = meba_poe_get_controller_handle,
    .meba_poe_do_detection = meba_poe_do_detection,
    .meba_poe_chip_initialization = meba_poe_generic_chip_initialization,
    .meba_poe_sync = meba_poe_generic_sync,
    .meba_poe_version_get = meba_poe_generic_version_get,
    .meba_poe_port_cfg_set = meba_poe_generic_port_cfg_set,
    .meba_poe_port_status_get = meba_poe_generic_port_status_get,
    .meba_poe_cfg_set = meba_poe_generic_cfg_set,
    .meba_poe_status_get = meba_poe_generic_status_get,
    .meba_poe_capabilities_get = meba_poe_generic_capabilities_get,
    .meba_poe_reset_command = meba_poe_generic_reset_command,
    .meba_poe_save_command = meba_poe_generic_save_command,
    .meba_poe_debug = meba_poe_generic_debug,
    .meba_poe_firmware_upgrade = meba_poe_generic_firmware_upgrade,
    .meba_poe_prepare_firmware_upgrade = meba_poe_generic_prepare_firmware_upgrade,
    .meba_poe_supply_limits_get = meba_poe_generic_supply_limits_get,
    .meba_poe_port_capabilities_get = meba_poe_generic_port_capabilities_get,
    .meba_poe_port_pd_data_set = meba_poe_generic_port_pd_data_set,
    .meba_poe_port_pd_bt_data_set = meba_poe_generic_port_pd_bt_data_set,
    .meba_poe_port_pd_data_clear = meba_poe_generic_port_pd_data_clear,
};

meba_api_poe_t *meba_poe_get() { return &public_functions; }
