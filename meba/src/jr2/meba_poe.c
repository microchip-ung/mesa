// Copyright (c) 2004-2024 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "microchip/ethernet/board/api.h"
#include "meba_poe_generic.h"
#include "jr2_poe_hw_cfg.h"

static meba_poe_parameters_t poe_default_parameters;

void set_jr2_parameters(meba_poe_firmware_type_t poe_type)
{
    // poe firmware type - TYPE_PREBT, GEN6_BT
    // poe_default_parameters.eMeba_poe_firmware_type = JR2_POE_FIRMWARE_TYPE_DEFAULT;

    // 1 or 2 active poe controllers
    poe_default_parameters.poe_controllers_count = JR2_POE_CONTROLLERS_COUNT_DEFAULT;

    // PD692x0 family detection method
    // poe_default_parameters.ePoE_gen6_controller_detection_type_default =
    // JR2_POE_GEN6_PD692x0_CONTROLLER_TYPE_DEFAULT;

    // BT complient port operation Mode
    poe_default_parameters.bt_operation_mode_compliant_15w_default = JR2_BT_COMPLIANT_15W_DEFAULT;
    poe_default_parameters.bt_operation_mode_compliant_30w_default = JR2_BT_COMPLIANT_30W_DEFAULT;
    poe_default_parameters.bt_operation_mode_compliant_60w_default = JR2_BT_COMPLIANT_60W_DEFAULT;
    poe_default_parameters.bt_operation_mode_compliant_90w_default = JR2_BT_COMPLIANT_90W_DEFAULT;

    // BT none complient port operation Mode
    poe_default_parameters.bt_operation_mode_none_compliant_15w_default =
        JR2_BT_NON_COMPLIANT_15W_DEFAULT;
    poe_default_parameters.bt_operation_mode_none_compliant_30w_default =
        JR2_BT_NON_COMPLIANT_30W_DEFAULT;
    poe_default_parameters.bt_operation_mode_none_compliant_60w_default =
        JR2_BT_NON_COMPLIANT_60W_DEFAULT;
    poe_default_parameters.bt_operation_mode_none_compliant_90w_default =
        JR2_BT_NON_COMPLIANT_90W_DEFAULT;

    // special Port operation modes for legacy
    poe_default_parameters.bt_operation_mode_legacy_90W_poh_default =
        JR2_BT_OPERATION_MODE_LEGACY_90W_POH_DEFAULT;
    poe_default_parameters.bt_operation_mode_legacy_60W_ignore_pd_class_default =
        JR2_BT_OPERATION_MODE_LEGACY_60W_IGNORE_PD_CLASS_DEFAULT;
    poe_default_parameters.bt_operation_mode_legacy_90W_ignore_pd_class_default =
        JR2_BT_OPERATION_MODE_LEGACY_90W_IGNORE_PD_CLASS_DEFAULT;

    poe_default_parameters.reset_poe_gpio_number = JR2_RESET_POE_GPIO_NUMBER;

    // prebt led stream type
    poe_default_parameters.indv_mask_prebt_led_stream_type_default =
        JR2_INDV_MASK_PREBT_LED_STREAM_TYPE_DEFAULT;
    // power higher priority port
    poe_default_parameters.indv_mask_prebt_ignore_higher_priority_default =
        JR2_INDV_MASK_PREBT_IGNORE_HIGHER_PRIORITY_DEFAULT;
    // En/Dis support of legacy detection
    poe_default_parameters.indv_mask_prebt_supports_legact_detection_default =
        JR2_INDV_MASK_PREBT_SUPPORTS_LEGACY_DETECTION_DEFAULT;
    // En/Dis supports backoff
    poe_default_parameters.indv_mask_prebt_supports_backoff_default =
        JR2_INDV_MASK_PREBT_SUPPORTS_BACKOFF_DEFAULT;
    // en/Dis MESSAGE_READY pin notification
    poe_default_parameters.indv_mask_prebt_message_ready_notify_default =
        JR2_INDV_MASK_PREBT_MESSAGE_READY_NOTIFY_DEFAULT;
    // En/Dis Layer 2 PD commands
    poe_default_parameters.indv_mask_prebt_layer2_lldp_enable_default =
        JR2_INDV_MASK_PREBT_LAYER2_LLDP_ENABLE_DEFAULT;
    // accept/ignored Port Priority recived from the PD
    poe_default_parameters.indv_mask_prebt_layer2_priority_by_PD_default =
        JR2_INDV_MASK_PREBT_LAYER2_PRIORITY_BY_PD_DEFAULT;
    // use 4-pair matrix commands
    poe_default_parameters.indv_mask_prebt_matrix_support_4P_default =
        JR2_INDV_MASK_PREBT_MATRIX_SUPPORT_4P_DEFAULT;
    // power higher priority port
    poe_default_parameters.indv_mask_BT_ignore_higher_priority_default =
        JR2_INDV_MASK_BT_IGNORE_HIGHER_PRIORITY_DEFAULT;
    // expand Resistor detection range up to range to 55 K
    poe_default_parameters.indv_mask_BT_support_high_res_detection_default =
        JR2_INDV_MASK_BT_SUPPORT_HIGH_RES_DETECTION_DEFAULT;
    // Initialization of the I2C module system after 10 seconds of inactivity
    poe_default_parameters.indv_mask_BT_i2c_restart_enable_default =
        JR2_INDV_MASK_BT_I2C_RESTART_ENABLE_DEFAULT;
    // led stream type
    poe_default_parameters.indv_mask_BT_led_stream_type_default =
        JR2_INDV_MASK_BT_LED_STREAM_TYPE_DEFAULT;
    // HOCPP - high_over Current Pulse Protection
    poe_default_parameters.indv_mask_BT_HOCPP_default = JR2_INDV_MASK_BT_HOCPP_DEFAULT;
    // PSE powering PSE checking
    poe_default_parameters.indv_mask_BT_PSE_powering_PSE_checking_default =
        JR2_INDV_MASK_BT_PSE_POWERING_PSE_CHECKING_DEFAULT;
    // Layer2 Power Allocation Limit
    poe_default_parameters.indv_mask_BT_layer2_power_allocation_limit_default =
        JR2_INDV_MASK_BT_LAYER2_POWER_ALLOCATION_LIMIT_DEFAULT;
    // Port LED Blinks at invalid signature or connection-check error
    poe_default_parameters
        .indv_mask_BT_Port_LED_blinks_at_invalid_signature_or_connection_check_error_default =
        JR2_INDV_MASK_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR_DEFAULT;
    // Support adding lldp half priority
    poe_default_parameters.indv_mask_BT_support_adding_lldp_half_priority_default =
        JR2_INDV_MASK_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY_DEFAULT;

    // ----- PREBT Power Management mode of operation -----//
    // Selects the method of calculating total power consumption
    poe_default_parameters.prebt_pm1_default = JR2_PM1_PREBT_DEFAULT;
    // Selects the power limit at the port (maximum or according to class or predefined)
    poe_default_parameters.prebt_pm2_default = JR2_PM2_PREBT_DEFAULT;
    // Selects the start condition. (Not recommended for new designs, keep 0x00)
    poe_default_parameters.prebt_pm3_default = JR2_PM3_PREBT_DEFAULT;
}

meba_poe_psu_input_prob_t jr2_power_supplies[] = {
    {.id = MEBA_POE_CTRL_PSU_ALL, // PowerSupply-ID
                                  // PwrSuply Min-Pwr
     .min_w = 0,
     // PwrSuply Max-Pwr
     .max_w = JR2_POE_POWER_SUPPLY_MAX_POWER_W_DEFAULT,
     // PwrSuply Default-Capability
     .def_w = JR2_POE_POWER_SUPPLY_DEF_POWER_W_DEFAULT,
     // System PwrUsage
     .system_pwr_usage_w = JR2_POE_POWER_SUPPLY_SYSTEM_POWER_USAGE_DEFAULT,
     // User Conig 1=Yes,0=No
     .user_configurable = JR2_POE_POWER_SUPPLY_MAX_POWER_USER_CONFIG_DEFAULT}
};

meba_poe_system_t jr2_pd69200_system;

static i2c_config_t jr2_i2c_config[] = {
    {"/dev/i2c-203", JR2_POE_CONTROLLER_1_I2C_ADDRESS},
    {"/dev/i2c-203", JR2_POE_CONTROLLER_2_I2C_ADDRESS}
};

mesa_rc meba_poe_jr2_system_get(meba_inst_t inst, meba_poe_system_t **const system)
{
    *system = &jr2_pd69200_system;
    return MESA_RC_OK;
}

mesa_rc meba_poe_jr2_system_initialize(meba_inst_t inst, meba_poe_init_params_t *tPoe_init_params)
{
    // Do poe chip detection and fill
    // jr2_ctrl.api = ....;
    // jr2_ctrl.private_data = ....;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");

    jr2_pd69200_system.controller_count = JR2_POE_CONTROLLERS_COUNT_DEFAULT;
    poe_default_parameters.max_poe_ports = tPoe_init_params->max_poe_ports;

    if ((tPoe_init_params->poe_type_from_tag >= 1) && (tPoe_init_params->poe_type_from_tag <= 2)) {
        poe_default_parameters.eMeba_poe_firmware_type = tPoe_init_params->poe_type_from_tag;
        printf("\n\rpoe firmware type from tag=%d\n\r", tPoe_init_params->eMeba_poe_firmware_type);
    } else {
        // poe firmware type - TYPE_PREBT , GEN6_BT
        poe_default_parameters.eMeba_poe_firmware_type = JR2_POE_FIRMWARE_TYPE_DEFAULT;
        printf("\n\rpoe firmware type default=%d\n\r", tPoe_init_params->eMeba_poe_firmware_type);
    }

    if ((tPoe_init_params->poe_controllers_count_from_tag == 1) ||
        (tPoe_init_params->poe_controllers_count_from_tag == 2)) {
        jr2_pd69200_system.controller_count = tPoe_init_params->poe_controllers_count_from_tag;
        printf("controllers count from tag=%d\n\r", jr2_pd69200_system.controller_count);
    } else {
        jr2_pd69200_system.controller_count = JR2_POE_CONTROLLERS_COUNT_DEFAULT;
        printf("controllers count default=%d\n\r", jr2_pd69200_system.controller_count);
    }

    jr2_pd69200_system.controllers =
        malloc(sizeof(meba_poe_ctrl_inst_t) * jr2_pd69200_system.controller_count);

    // overide tMeba_poe_init_params params if using H file parameters
    // overide meba power supply by appl init_params
    if (!tPoe_init_params->use_poe_static_parameters) {
        jr2_power_supplies->def_w = tPoe_init_params->power_supply_default_power_limit;
        jr2_power_supplies->max_w = tPoe_init_params->power_supply_max_power_w;
        jr2_power_supplies->system_pwr_usage_w = tPoe_init_params->power_supply_internal_pwr_usage;
    }

    set_jr2_parameters(poe_default_parameters.eMeba_poe_firmware_type);

    if (poe_default_parameters.eMeba_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_GEN6_BT) {
        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            poe_default_parameters.max_poe_ports =
                sizeof(jr2_pd69200_4pairs_port_map_1) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface.debug(
            MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
            "dev1 using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
            poe_default_parameters.max_poe_ports, jr2_power_supplies->max_w,
            poe_default_parameters.eMeba_poe_firmware_type);

        jr2_pd69200_system.controllers[0].index = 0;
        meba_pd_bt_driver_init(&jr2_pd69200_system.controllers[0], "pd69x00bt",
                               meba_pd_i2c_adapter_open(&jr2_pd69200_system.controllers[0],
                                                        jr2_i2c_config[0].i2c_device,
                                                        jr2_i2c_config[0].i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                   MEBA_POE_CTRL_INTERRUPTIBLE_POWER |
                                   MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST |
                                   MEBA_POE_CTRL_LEGACY_PD_CLASS_MODE,
                               jr2_pd69200_4pairs_port_map_1,
                               sizeof(jr2_pd69200_4pairs_port_map_1) /
                                   sizeof(meba_poe_port_properties_t),
                               jr2_power_supplies,
                               sizeof(jr2_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug, poe_default_parameters);

        if (jr2_pd69200_system.controller_count == MEBA_POE_TWO_CONTROLLERS) {
            // overide tMeba_poe_init_params params if using H file parameters
            if (tPoe_init_params->use_poe_static_parameters) {
                poe_default_parameters.max_poe_ports =
                    sizeof(jr2_pd69200_4pairs_port_map_2) / sizeof(meba_poe_port_properties_t);
            }

            inst->iface.debug(
                MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                "dev2 using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                poe_default_parameters.max_poe_ports, jr2_power_supplies->max_w,
                poe_default_parameters.eMeba_poe_firmware_type);

            jr2_pd69200_system.controllers[1].index = 1;
            meba_pd_bt_driver_init(&jr2_pd69200_system.controllers[1], "pd69x00bt-2",
                                   meba_pd_i2c_adapter_open(&jr2_pd69200_system.controllers[1],
                                                            jr2_i2c_config[1].i2c_device,
                                                            jr2_i2c_config[1].i2c_address),
                                   MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                       MEBA_POE_CTRL_INTERRUPTIBLE_POWER |
                                       MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST |
                                       MEBA_POE_CTRL_LEGACY_PD_CLASS_MODE,
                                   jr2_pd69200_4pairs_port_map_2,
                                   sizeof(jr2_pd69200_4pairs_port_map_2) /
                                       sizeof(meba_poe_port_properties_t),
                                   jr2_power_supplies,
                                   sizeof(jr2_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                                   inst->iface.debug, poe_default_parameters);
        }
    } else if (poe_default_parameters.eMeba_poe_firmware_type ==
               MEBA_POE_FIRMWARE_TYPE_GEN6_PREBT) {
        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            poe_default_parameters.max_poe_ports =
                sizeof(jr2_pd69200_2pairs_port_map_1) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface
            .debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                   "using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                   poe_default_parameters.max_poe_ports, jr2_power_supplies->max_w,
                   poe_default_parameters.eMeba_poe_firmware_type);

        jr2_pd69200_system.controllers[0].index = 0;
        meba_pd69200_driver_init(&jr2_pd69200_system.controllers[0], "pd69x00at",
                                 meba_pd_i2c_adapter_open(&jr2_pd69200_system.controllers[0],
                                                          jr2_i2c_config[0].i2c_device,
                                                          jr2_i2c_config[0].i2c_address),
                                 MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                     MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                                     MEBA_POE_CTRL_INTERRUPTIBLE_POWER,
                                 jr2_pd69200_2pairs_port_map_1,
                                 sizeof(jr2_pd69200_2pairs_port_map_1) /
                                     sizeof(meba_poe_port_properties_t),
                                 jr2_power_supplies,
                                 sizeof(jr2_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                                 inst->iface.debug, poe_default_parameters);
        if (jr2_pd69200_system.controller_count == MEBA_POE_TWO_CONTROLLERS) {
            // overide tMeba_poe_init_params params if using H file parameters
            if (tPoe_init_params->use_poe_static_parameters) {
                poe_default_parameters.max_poe_ports =
                    sizeof(jr2_pd69200_2pairs_port_map_2) / sizeof(meba_poe_port_properties_t);
            }

            inst->iface.debug(
                MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                "dev2 using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                poe_default_parameters.max_poe_ports, jr2_power_supplies->max_w,
                poe_default_parameters.eMeba_poe_firmware_type);

            jr2_pd69200_system.controllers[1].index = 1;
            meba_pd69200_driver_init(&jr2_pd69200_system.controllers[1], "pd69x00at-2",
                                     meba_pd_i2c_adapter_open(&jr2_pd69200_system.controllers[1],
                                                              jr2_i2c_config[1].i2c_device,
                                                              jr2_i2c_config[1].i2c_address),
                                     MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                         MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                                         MEBA_POE_CTRL_INTERRUPTIBLE_POWER,
                                     jr2_pd69200_2pairs_port_map_2,
                                     sizeof(jr2_pd69200_2pairs_port_map_2) /
                                         sizeof(meba_poe_port_properties_t),
                                     jr2_power_supplies,
                                     sizeof(jr2_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                                     inst->iface.debug, poe_default_parameters);
        }
    } else {
        return MESA_RC_ERROR;
    }

    return MESA_RC_OK;
};

mesa_rc meba_poe_jr2_get_controller_handle(meba_inst_t             inst,
                                           mesa_port_no_t          port_no,
                                           meba_poe_ctrl_inst_t  **controller,
                                           meba_poe_port_handle_t *handle)
{
    for (int i = 0; i < jr2_pd69200_system.controller_count; ++i) {
        for (int j = 0; j < jr2_pd69200_system.controllers[i].port_map_length; ++j) {
            if (jr2_pd69200_system.controllers[i].port_map[j].port_no == port_no) {
                *controller = &jr2_pd69200_system.controllers[i];
                *handle = jr2_pd69200_system.controllers[i].port_map[j].handle;
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

// returns values:
// - MESA_RC_OK : when all controllers are responded (not MESA_RC_ERROR)
// - MESA_RC_ERROR : when one or more controllers are responded with MESA_RC_ERROR
mesa_rc meba_poe_jr2_do_detection(meba_inst_t inst)
{
    mesa_rc rc = MESA_RC_ERROR;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    for (int i = 0; i < jr2_pd69200_system.controller_count; ++i) {
        if (jr2_pd69200_system.controllers[i]
                .api->meba_poe_ctrl_do_detection(&jr2_pd69200_system.controllers[i]) ==
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
    .meba_poe_system_initialize = meba_poe_jr2_system_initialize,
    .meba_poe_system_get = meba_poe_jr2_system_get,
    .meba_poe_get_controller_handle = meba_poe_jr2_get_controller_handle,
    .meba_poe_do_detection = meba_poe_jr2_do_detection,
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
