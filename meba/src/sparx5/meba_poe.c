// Copyright (c) 2004-2024 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "microchip/ethernet/board/api.h"
#include "meba_poe_generic.h"
#include "sparx5_poe_hw_cfg.h"
#include "meba_common.h"

meba_poe_parameters_t tSparx_poe_parameters = {
    // poe firmware type - TYPE_PREBT , GEN6_BT
    .tMeba_poe_firmware_type = SPARX5_POE_FIRMWARE_TYPE_DEFAULT,
    // PD692x0/PD77010 family detection method
    .ePoE_Controller_Type_default = SPARX5_POE_GEN6_PD692x0_CONTROLLER_TYPE_DEFAULT,

#if SPARX5_POE_FIRMWARE_TYPE_DEFAULT == MEBA_POE_FIRMWARE_TYPE_GEN6_BT
    // System has 4 modes = 15/30/60/90 (applicable for all poe ports)
    .ePoE_port_max_power_default = SPARX5_GEN6_BT_PORT_MAX_POWER_DEFAULT,

    // BT complient port operation Mode
    .bt_operation_mode_compliant_15w_default = SPARX5_GEN6_BT_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_compliant_30w_default = SPARX5_GEN6_BT_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_compliant_60w_default = SPARX5_GEN6_BT_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_compliant_90w_default = SPARX5_GEN6_BT_COMPLIANT_90W_DEFAULT,

    // BT none complient port operation Mode
    .bt_operation_mode_none_compliant_15w_default = SPARX5_GEN6_BT_NON_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_none_compliant_30w_default = SPARX5_GEN6_BT_NON_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_none_compliant_60w_default = SPARX5_GEN6_BT_NON_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_none_compliant_90w_default = SPARX5_GEN6_BT_NON_COMPLIANT_90W_DEFAULT,

    // special Port operation modes for legacy
    .bt_operation_mode_legacy_90W_poh_default =
        SPARX5_GEN6_BT_OPERATION_MODE_LEGACY_90W_POH_DEFAULT,
    .bt_operation_mode_legacy_60W_ignore_pd_class_default =
        SPARX5_GEN6_BT_OPERATION_MODE_LEGACY_60W_IGNORE_PD_CLASS_DEFAULT,
    .bt_operation_mode_legacy_90W_ignore_pd_class_default =
        SPARX5_GEN6_BT_OPERATION_MODE_LEGACY_90W_IGNORE_PD_CLASS_DEFAULT,

    // power higher priority port
    .indv_mask_BT_ignore_higher_priority_default =
        SPARX5_INDV_MASK_GEN6_BT_IGNORE_HIGHER_PRIORITY_DEFAULT,
    // expand Resistor detection range up to range to 55K
    .indv_mask_BT_support_high_res_detection_default =
        SPARX5_INDV_MASK_GEN6_BT_SUPPORT_HIGH_RES_DETECTION_DEFAULT,
    // Initialization of the I2C module system after 10 seconds of inactivity
    .indv_mask_BT_i2c_restart_enable_default = SPARX5_INDV_MASK_GEN6_BT_I2C_RESTART_ENABLE_DEFAULT,
    // led stream type
    .indv_mask_BT_led_stream_type_default = SPARX5_INDV_MASK_GEN6_BT_LED_STREAM_TYPE_DEFAULT,
    .indv_mask_BT_HOCPP_default =
        SPARX5_INDV_MASK_GEN6_BT_HOCPP_DEFAULT, // HOCPP - high_over Current Pulse Protection
    // PSE powering PSE checking
    .indv_mask_BT_PSE_powering_PSE_checking_default =
        SPARX5_INDV_MASK_GEN6_BT_PSE_POWERING_PSE_CHECKING_DEFAULT,
    // Layer2 Power Allocation Limit
    .indv_mask_BT_layer2_power_allocation_limit_default =
        SPARX5_INDV_MASK_GEN6_BT_LAYER2_POWER_ALLOCATION_LIMIT_DEFAULT,
    // Port LED Blinks at invalid signature or connection-check error
    .indv_mask_BT_Port_LED_blinks_at_invalid_signature_or_connection_check_error_default =
        SPARX5_INDV_MASK_GEN6_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR_DEFAULT,
    // Support adding lldp half priority
    .indv_mask_BT_support_adding_lldp_half_priority_default =
        SPARX5_INDV_MASK_GEN6_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY_DEFAULT,

#elif SPARX5_POE_FIRMWARE_TYPE_DEFAULT == MEBA_POE_FIRMWARE_TYPE_GEN7_BT

    // System has 4 modes = 15/30/60/90 (applicable for all poe ports)
    .ePoE_port_max_power_default = SPARX5_GEN7_BT_PORT_MAX_POWER_DEFAULT,

    // BT complient port operation Mode
    .bt_operation_mode_compliant_15w_default = SPARX5_GEN7_BT_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_compliant_30w_default = SPARX5_GEN7_BT_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_compliant_60w_default = SPARX5_GEN7_BT_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_compliant_90w_default = SPARX5_GEN7_BT_COMPLIANT_90W_DEFAULT,

    // BT none complient port operation Mode
    .bt_operation_mode_none_compliant_15w_default = SPARX5_GEN7_BT_NON_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_none_compliant_30w_default = SPARX5_GEN7_BT_NON_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_none_compliant_60w_default = SPARX5_GEN7_BT_NON_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_none_compliant_90w_default = SPARX5_GEN7_BT_NON_COMPLIANT_90W_DEFAULT,

    // led stream type
    .indv_mask_BT_led_stream_type_default = SPARX5_INDV_MASK_GEN7_BT_LED_STREAM_TYPE_DEFAULT,
    // Support adding lldp half priority
    .indv_mask_BT_support_adding_lldp_half_priority_default =
        SPARX5_INDV_MASK_GEN7_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY_DEFAULT,

#endif // MEBA_POE_FIRMWARE_TYPE_GEN7_BT

    .reset_poe_gpio_number = SPARX5_RESET_POE_GPIO_NUMBER,

    // prebt led stream type
    .indv_mask_prebt_led_stream_type_default = SPARX5_INDV_MASK_PREBT_LED_STREAM_TYPE_DEFAULT,
    // power higher priority port
    .indv_mask_prebt_ignore_higher_priority_default =
        SPARX5_INDV_MASK_PREBT_IGNORE_HIGHER_PRIORITY_DEFAULT,
    // En/Dis support of legacy detection
    .indv_mask_prebt_supports_legact_detection_default =
        SPARX5_INDV_MASK_PREBT_SUPPORTS_LEGACY_DETECTION_DEFAULT,
    // En/Dis supports backoff
    .indv_mask_prebt_supports_backoff_default = SPARX5_INDV_MASK_PREBT_SUPPORTS_BACKOFF_DEFAULT,
    // en/Dis MESSAGE_READY pin notification
    .indv_mask_prebt_message_ready_notify_default =
        SPARX5_INDV_MASK_PREBT_MESSAGE_READY_NOTIFY_DEFAULT,
    // En/Dis Layer 2 PD commands
    .indv_mask_prebt_layer2_lldp_enable_default = SPARX5_INDV_MASK_PREBT_LAYER2_LLDP_ENABLE_DEFAULT,
    // accept/ignored Port Priority recived from the PD
    .indv_mask_prebt_layer2_priority_by_PD_default =
        SPARX5_INDV_MASK_PREBT_LAYER2_PRIORITY_BY_PD_DEFAULT,
    // use 4-pair matrix commands
    .indv_mask_prebt_matrix_support_4P_default = SPARX5_INDV_MASK_PREBT_MATRIX_SUPPORT_4P_DEFAULT,

    // --  PREBT Power Management mode of operation --//
    // Selects the method of calculating total power consumption
    .prebt_pm1_default = SPARX5_PM1_PREBT_DEFAULT,
    // Selects the power limit at the port (maximum or according to class or predefined).
    .prebt_pm2_default = SPARX5_PM2_PREBT_DEFAULT,
    // Selects the start condition. (Not recommended for new designs, keep 0x00)
    .prebt_pm3_default = SPARX5_PM3_PREBT_DEFAULT};

meba_poe_psu_input_prob_t sparx5_power_supplies[] = {
    {.id = MEBA_POE_CTRL_PSU_ALL, // PowerSupply-ID
                                  // PwrSuply Min-Pwr
     .min_w = 0,
     // PwrSuply Max-Pwr
     .max_w = SPARX5_POE_POWER_SUPPLY_MAX_POWER_W_DEFAULT,
     // PwrSuply Default-Capability
     .def_w = SPARX5_POE_POWER_SUPPLY_DEF_POWER_W_DEFAULT,
     // System PwrUsage
     .system_pwr_usage_w = SPARX5_POE_POWER_SUPPLY_SYSTEM_POWER_USAGE_DEFAULT,
     // User Conig 1=Yes,0=No
     .user_configurable = SPARX5_POE_POWER_SUPPLY_MAX_POWER_USER_CONFIG_DEFAULT}
};

meba_poe_parameters_t tLaguna_poe_parameters = {
    // poe firmware type - TYPE_PREBT , GEN6_BT
    .tMeba_poe_firmware_type = LAGUNA_POE_FIRMWARE_TYPE_DEFAULT,
    // PD692x0/PD77010 family detection method
    .ePoE_Controller_Type_default = LAGUNA_POE_GEN6_PD692x0_CONTROLLER_TYPE_DEFAULT,

#if LAGUNA_POE_FIRMWARE_TYPE_DEFAULT == MEBA_POE_FIRMWARE_TYPE_GEN6_BT
    // System has 4 modes = 15/30/60/90 (applicable for all poe ports)
    .ePoE_port_max_power_default = LAGUNA_GEN6_BT_PORT_MAX_POWER_DEFAULT,

    // BT complient port operation Mode
    .bt_operation_mode_compliant_15w_default = LAGUNA_GEN6_BT_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_compliant_30w_default = LAGUNA_GEN6_BT_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_compliant_60w_default = LAGUNA_GEN6_BT_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_compliant_90w_default = LAGUNA_GEN6_BT_COMPLIANT_90W_DEFAULT,

    // BT none complient port operation Mode
    .bt_operation_mode_none_compliant_15w_default = LAGUNA_GEN6_BT_NON_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_none_compliant_30w_default = LAGUNA_GEN6_BT_NON_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_none_compliant_60w_default = LAGUNA_GEN6_BT_NON_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_none_compliant_90w_default = LAGUNA_GEN6_BT_NON_COMPLIANT_90W_DEFAULT,

    // special Port operation modes for legacy
    .bt_operation_mode_legacy_90W_poh_default =
        LAGUNA_GEN6_BT_OPERATION_MODE_LEGACY_90W_POH_DEFAULT,
    .bt_operation_mode_legacy_60W_ignore_pd_class_default =
        LAGUNA_GEN6_BT_OPERATION_MODE_LEGACY_60W_IGNORE_PD_CLASS_DEFAULT,
    .bt_operation_mode_legacy_90W_ignore_pd_class_default =
        LAGUNA_GEN6_BT_OPERATION_MODE_LEGACY_90W_IGNORE_PD_CLASS_DEFAULT,

    // power higher priority port
    .indv_mask_BT_ignore_higher_priority_default =
        LAGUNA_INDV_MASK_GEN6_BT_IGNORE_HIGHER_PRIORITY_DEFAULT,
    // expand Resistor detection range up to range to 55K
    .indv_mask_BT_support_high_res_detection_default =
        LAGUNA_INDV_MASK_GEN6_BT_SUPPORT_HIGH_RES_DETECTION_DEFAULT,
    // Initialization of the I2C module system after 10 seconds of inactivity
    .indv_mask_BT_i2c_restart_enable_default = LAGUNA_INDV_MASK_GEN6_BT_I2C_RESTART_ENABLE_DEFAULT,
    // led stream type
    .indv_mask_BT_led_stream_type_default = LAGUNA_INDV_MASK_GEN6_BT_LED_STREAM_TYPE_DEFAULT,
    .indv_mask_BT_HOCPP_default =
        LAGUNA_INDV_MASK_GEN6_BT_HOCPP_DEFAULT, // HOCPP - high_over Current Pulse Protection
    // PSE powering PSE checking
    .indv_mask_BT_PSE_powering_PSE_checking_default =
        LAGUNA_INDV_MASK_GEN6_BT_PSE_POWERING_PSE_CHECKING_DEFAULT,
    // Layer2 Power Allocation Limit
    .indv_mask_BT_layer2_power_allocation_limit_default =
        LAGUNA_INDV_MASK_GEN6_BT_LAYER2_POWER_ALLOCATION_LIMIT_DEFAULT,
    // Port LED Blinks at invalid signature or connection-check error
    .indv_mask_BT_Port_LED_blinks_at_invalid_signature_or_connection_check_error_default =
        LAGUNA_INDV_MASK_GEN6_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR_DEFAULT,
    // Support adding lldp half priority
    .indv_mask_BT_support_adding_lldp_half_priority_default =
        LAGUNA_INDV_MASK_GEN6_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY_DEFAULT,

#elif LAGUNA_POE_FIRMWARE_TYPE_DEFAULT == MEBA_POE_FIRMWARE_TYPE_GEN7_BT

    // System has 4 modes = 15/30/60/90 (applicable for all poe ports)
    .ePoE_port_max_power_default = LAGUNA_GEN7_BT_PORT_MAX_POWER_DEFAULT,

    // BT complient port operation Mode
    .bt_operation_mode_compliant_15w_default = LAGUNA_GEN7_BT_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_compliant_30w_default = LAGUNA_GEN7_BT_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_compliant_60w_default = LAGUNA_GEN7_BT_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_compliant_90w_default = LAGUNA_GEN7_BT_COMPLIANT_90W_DEFAULT,

    // BT none complient port operation Mode
    .bt_operation_mode_none_compliant_15w_default = LAGUNA_GEN7_BT_NON_COMPLIANT_15W_DEFAULT,
    .bt_operation_mode_none_compliant_30w_default = LAGUNA_GEN7_BT_NON_COMPLIANT_30W_DEFAULT,
    .bt_operation_mode_none_compliant_60w_default = LAGUNA_GEN7_BT_NON_COMPLIANT_60W_DEFAULT,
    .bt_operation_mode_none_compliant_90w_default = LAGUNA_GEN7_BT_NON_COMPLIANT_90W_DEFAULT,

    // led stream type
    .indv_mask_BT_led_stream_type_default = LAGUNA_INDV_MASK_GEN7_BT_LED_STREAM_TYPE_DEFAULT,
    // Support adding lldp half priority
    .indv_mask_BT_support_adding_lldp_half_priority_default =
        LAGUNA_INDV_MASK_GEN7_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY_DEFAULT,

#endif // MEBA_POE_FIRMWARE_TYPE_GEN7_BT

    .reset_poe_gpio_number = LAGUNA_RESET_POE_GPIO_NUMBER,

    // prebt led stream type
    .indv_mask_prebt_led_stream_type_default = LAGUNA_INDV_MASK_PREBT_LED_STREAM_TYPE_DEFAULT,
    // power higher priority port
    .indv_mask_prebt_ignore_higher_priority_default =
        LAGUNA_INDV_MASK_PREBT_IGNORE_HIGHER_PRIORITY_DEFAULT,
    // En/Dis support of legacy detection
    .indv_mask_prebt_supports_legact_detection_default =
        LAGUNA_INDV_MASK_PREBT_SUPPORTS_LEGACY_DETECTION_DEFAULT,
    // En/Dis supports backoff
    .indv_mask_prebt_supports_backoff_default = LAGUNA_INDV_MASK_PREBT_SUPPORTS_BACKOFF_DEFAULT,
    // en/Dis MESSAGE_READY pin notification
    .indv_mask_prebt_message_ready_notify_default =
        LAGUNA_INDV_MASK_PREBT_MESSAGE_READY_NOTIFY_DEFAULT,
    // En/Dis Layer 2 PD commands
    .indv_mask_prebt_layer2_lldp_enable_default = LAGUNA_INDV_MASK_PREBT_LAYER2_LLDP_ENABLE_DEFAULT,
    // accept/ignored Port Priority recived from the PD
    .indv_mask_prebt_layer2_priority_by_PD_default =
        LAGUNA_INDV_MASK_PREBT_LAYER2_PRIORITY_BY_PD_DEFAULT,
    // use 4-pair matrix commands
    .indv_mask_prebt_matrix_support_4P_default = LAGUNA_INDV_MASK_PREBT_MATRIX_SUPPORT_4P_DEFAULT,

    // --  PREBT Power Management mode of operation --//
    // Selects the method of calculating total power consumption
    .prebt_pm1_default = LAGUNA_PM1_PREBT_DEFAULT,
    // Selects the power limit at the port (maximum or according to class or predefined).
    .prebt_pm2_default = LAGUNA_PM2_PREBT_DEFAULT,
    // Selects the start condition. (Not recommended for new designs, keep 0x00)
    .prebt_pm3_default = LAGUNA_PM3_PREBT_DEFAULT};

meba_poe_psu_input_prob_t laguna_power_supplies[] = {
    {.id = MEBA_POE_CTRL_PSU_ALL, // PowerSupply-ID
                                  // PwrSuply Min-Pwr
     .min_w = 0,
     // PwrSuply Max-Pwr
     .max_w = LAGUNA_POE_POWER_SUPPLY_MAX_POWER_W_DEFAULT,
     // PwrSuply Default-Capability
     .def_w = LAGUNA_POE_POWER_SUPPLY_DEF_POWER_W_DEFAULT,
     // System PwrUsage
     .system_pwr_usage_w = LAGUNA_POE_POWER_SUPPLY_SYSTEM_POWER_USAGE_DEFAULT,
     // User Conig 1=Yes,0=No
     .user_configurable = LAGUNA_POE_POWER_SUPPLY_MAX_POWER_USER_CONFIG_DEFAULT}
};

meba_poe_system_t pd_system;

static i2c_config_t sparx5_gen6_i2c_config[] = {
    {"/dev/i2c-0", SPARX5_POE_GEN6_CONTROLLER_1_I2C_ADDRESS},
#if SPARX5_POE_CONTROLLERS_COUNT == MEBA_POE_TWO_CONTROLLERS
    {"/dev/i2c-0", SPARX5_POE_GEN6_CONTROLLER_2_I2C_ADDRESS}
#endif
};

static i2c_config_t sparx5_gen7_i2c_config[] = {
    {"/dev/i2c-0", SPARX5_POE_GEN7_CONTROLLER_I2C_ADDRESS}
};

i2c_config_t laguna_gen6_i2c_config[] = {
    {"/dev/i2c-0", LAGUNA_POE_GEN6_CONTROLLER_I2C_ADDRESS}
};

i2c_config_t laguna_gen7_i2c_config[] = {
    {"/dev/i2c-0", LAGUNA_POE_GEN7_CONTROLLER_I2C_ADDRESS}
};

mesa_rc meba_poe_sparx5_system_get(meba_inst_t inst, meba_poe_system_t **const system)
{
    *system = &pd_system;
    return MESA_RC_OK;
}

mesa_rc meba_poe_sparx5_pcb135_system_initialize(meba_inst_t             inst,
                                                 meba_poe_init_params_t *tPoe_init_params)
{
    // Do poe chip detection and fill
    // sparx5_ctrl.api = ....;
    // sparx5_ctrl.private_data = ....;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");

#if SPARX5_POE_CONTROLLERS_COUNT == MEBA_POE_TWO_CONTROLLERS
    pd_system.controller_count = 2;
#else
    pd_system.controller_count = 1;
#endif // SPARX5_POE_CONTROLLERS_COUNT

    inst->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, "controllers count=%d",
                      pd_system.controller_count);

    pd_system.controllers = malloc(sizeof(meba_poe_ctrl_inst_t) * pd_system.controller_count);
    // overide tMeba_poe_init_params params if using H file parameters
    if (tPoe_init_params->use_poe_static_parameters) {
        tPoe_init_params->power_supply_max_power_w = SPARX5_POE_POWER_SUPPLY_MAX_POWER_W_DEFAULT;
        tPoe_init_params->eMeba_poe_firmware_type = SPARX5_POE_FIRMWARE_TYPE_DEFAULT;
    } else { // overide meba power supply by appl init_params
        sparx5_power_supplies->def_w = tPoe_init_params->power_supply_default_power_limit;
        sparx5_power_supplies->max_w = tPoe_init_params->power_supply_max_power_w;
        sparx5_power_supplies->system_pwr_usage_w =
            tPoe_init_params->power_supply_internal_pwr_usage;
    }

    if (tPoe_init_params->eMeba_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_GEN6_BT) {

        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            tPoe_init_params->max_poe_ports =
                sizeof(sparx5_pd69200_4pairs_port_map_1) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface
            .debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                   "using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                   tPoe_init_params->max_poe_ports, tPoe_init_params->power_supply_max_power_w,
                   tPoe_init_params->eMeba_poe_firmware_type);

        tSparx_poe_parameters.poe_init_params = *tPoe_init_params;

        pd_system.controllers[0].index = 0;
        meba_pd_bt_driver_init(&pd_system.controllers[0], "pd69x00bt",
                               meba_pd_i2c_adapter_open(&pd_system.controllers[0],
                                                        sparx5_gen6_i2c_config[0].i2c_device,
                                                        sparx5_gen6_i2c_config[0].i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                   MEBA_POE_CTRL_INTERRUPTIBLE_POWER |
                                   MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST |
                                   MEBA_POE_CTRL_LEGACY_PD_CLASS_MODE,
                               sparx5_pd69200_4pairs_port_map_1,
                               sizeof(sparx5_pd69200_4pairs_port_map_1) /
                                   sizeof(meba_poe_port_properties_t),
                               sparx5_power_supplies,
                               sizeof(sparx5_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug, tSparx_poe_parameters);

#if SPARX5_POE_CONTROLLERS_COUNT == MEBA_POE_TWO_CONTROLLERS
        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            tPoe_init_params->max_poe_ports =
                sizeof(sparx5_pd69200_4pairs_port_map_2) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface
            .debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                   "using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                   tPoe_init_params->max_poe_ports, tPoe_init_params->power_supply_max_power_w,
                   tPoe_init_params->eMeba_poe_firmware_type);

        tSparx_poe_parameters.poe_init_params = *tPoe_init_params;

        pd_system.controllers[1].index = 1;
        meba_pd_bt_driver_init(&pd_system.controllers[1], "pd69x00bt-2",
                               meba_pd_i2c_adapter_open(&pd_system.controllers[1],
                                                        sparx5_gen6_i2c_config[1].i2c_device,
                                                        sparx5_gen6_i2c_config[1].i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                   MEBA_POE_CTRL_INTERRUPTIBLE_POWER |
                                   MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST |
                                   MEBA_POE_CTRL_LEGACY_PD_CLASS_MODE,
                               sparx5_pd69200_4pairs_port_map_2,
                               sizeof(sparx5_pd69200_4pairs_port_map_2) /
                                   sizeof(meba_poe_port_properties_t),
                               sparx5_power_supplies,
                               sizeof(sparx5_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug, tSparx_poe_parameters);
#endif // SPARX5_POE_CONTROLLERS_COUNT
    } else if (tPoe_init_params->eMeba_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_GEN7_BT) {
        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            tPoe_init_params->max_poe_ports =
                sizeof(sparx5_pd69777_4pairs_port_map) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface
            .debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                   "using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                   tPoe_init_params->max_poe_ports, tPoe_init_params->power_supply_max_power_w,
                   tPoe_init_params->eMeba_poe_firmware_type);

        tSparx_poe_parameters.poe_init_params = *tPoe_init_params;

        pd_system.controllers[0].index = 0;
        meba_pd_bt_driver_init(&pd_system.controllers[0], "pd77010",
                               meba_pd_i2c_adapter_open(&pd_system.controllers[0],
                                                        sparx5_gen7_i2c_config[0].i2c_device,
                                                        sparx5_gen7_i2c_config[0].i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                   MEBA_POE_CTRL_INTERRUPTIBLE_POWER |
                                   MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST,
                               sparx5_pd69777_4pairs_port_map,
                               sizeof(sparx5_pd69777_4pairs_port_map) /
                                   sizeof(meba_poe_port_properties_t),
                               sparx5_power_supplies,
                               sizeof(sparx5_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug, tSparx_poe_parameters);
    } else if (tPoe_init_params->eMeba_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_GEN6_PREBT) {
        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            tPoe_init_params->max_poe_ports =
                sizeof(sparx5_pd69200_4pairs_port_map_1) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface
            .debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                   "using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                   tPoe_init_params->max_poe_ports, tPoe_init_params->power_supply_max_power_w,
                   tPoe_init_params->eMeba_poe_firmware_type);

        tSparx_poe_parameters.poe_init_params = *tPoe_init_params;

        pd_system.controllers[0].index = 0;
        meba_pd69200_driver_init(&pd_system.controllers[0], "pd69x00at",
                                 meba_pd_i2c_adapter_open(&pd_system.controllers[0],
                                                          sparx5_gen6_i2c_config[0].i2c_device,
                                                          sparx5_gen6_i2c_config[0].i2c_address),
                                 MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                     MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                                     MEBA_POE_CTRL_INTERRUPTIBLE_POWER,
                                 sparx5_pd69200_4pairs_port_map_1,
                                 sizeof(sparx5_pd69200_4pairs_port_map_1) /
                                     sizeof(meba_poe_port_properties_t),
                                 sparx5_power_supplies,
                                 sizeof(sparx5_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                                 inst->iface.debug, tSparx_poe_parameters);
#if SPARX5_POE_CONTROLLERS_COUNT == MEBA_POE_TWO_CONTROLLERS
        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            tPoe_init_params->max_poe_ports =
                sizeof(sparx5_pd69200_4pairs_port_map_2) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface
            .debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
                   "using: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
                   tPoe_init_params->max_poe_ports, tPoe_init_params->power_supply_max_power_w,
                   tPoe_init_params->eMeba_poe_firmware_type);

        tSparx_poe_parameters.poe_init_params = *tPoe_init_params;

        pd_system.controllers[1].index = 1;
        meba_pd69200_driver_init(&pd_system.controllers[1], "pd69x00at-2",
                                 meba_pd_i2c_adapter_open(&pd_system.controllers[1],
                                                          sparx5_gen6_i2c_config[1].i2c_device,
                                                          sparx5_gen6_i2c_config[1].i2c_address),
                                 MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                     MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                                     MEBA_POE_CTRL_INTERRUPTIBLE_POWER,
                                 sparx5_pd69200_4pairs_port_map_2,
                                 sizeof(sparx5_pd69200_4pairs_port_map_2) /
                                     sizeof(meba_poe_port_properties_t),
                                 sparx5_power_supplies,
                                 sizeof(sparx5_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                                 inst->iface.debug, tSparx_poe_parameters);
#endif // SPARX5_POE_CONTROLLERS_COUNT
    } else {
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
};

mesa_rc meba_poe_laguna_pcb8398_system_initialize(meba_inst_t             inst,
                                                  meba_poe_init_params_t *tPoe_init_params)
{
    // Do poe chip detection and fill
    // lan969x_ctrl.api = ....;
    // lan969x_ctrl.private_data = ....;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");

    pd_system.controller_count = 1;
    pd_system.controllers = malloc(sizeof(meba_poe_ctrl_inst_t) * pd_system.controller_count);

    // overide tMeba_poe_init_params params if using H file parameters
    if (tPoe_init_params->use_poe_static_parameters) {
        tPoe_init_params->power_supply_max_power_w = LAGUNA_POE_POWER_SUPPLY_MAX_POWER_W_DEFAULT;
        tPoe_init_params->eMeba_poe_firmware_type = LAGUNA_POE_FIRMWARE_TYPE_DEFAULT;
    } else { // overide meba power supply by appl init_params
        laguna_power_supplies->def_w = tPoe_init_params->power_supply_default_power_limit;
        laguna_power_supplies->max_w = tPoe_init_params->power_supply_max_power_w;
        laguna_power_supplies->system_pwr_usage_w =
            tPoe_init_params->power_supply_internal_pwr_usage;
    }

    if (tPoe_init_params->eMeba_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_GEN6_BT) {

        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            tPoe_init_params->max_poe_ports =
                sizeof(laguna_pd69200_4pairs_port_map) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface.debug(
            MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
            "gen6 BT: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
            tPoe_init_params->max_poe_ports, tPoe_init_params->power_supply_max_power_w,
            tPoe_init_params->eMeba_poe_firmware_type);

        tLaguna_poe_parameters.poe_init_params = *tPoe_init_params;

        pd_system.controllers[0].index = 0;
        meba_pd_bt_driver_init(&pd_system.controllers[0], "pd69x00bt",
                               meba_pd_i2c_adapter_open(&pd_system.controllers[0],
                                                        laguna_gen6_i2c_config[0].i2c_device,
                                                        laguna_gen6_i2c_config[0].i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                   MEBA_POE_CTRL_INTERRUPTIBLE_POWER |
                                   MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST |
                                   MEBA_POE_CTRL_LEGACY_PD_CLASS_MODE,
                               laguna_pd69200_4pairs_port_map,
                               sizeof(laguna_pd69200_4pairs_port_map) /
                                   sizeof(meba_poe_port_properties_t),
                               laguna_power_supplies,
                               sizeof(laguna_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug, tLaguna_poe_parameters);

    } else if (tPoe_init_params->eMeba_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_GEN7_BT) {
        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            tPoe_init_params->max_poe_ports =
                sizeof(laguna_pd69777_4pairs_port_map) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface.debug(
            MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
            "gen7 BT: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
            tPoe_init_params->max_poe_ports, tPoe_init_params->power_supply_max_power_w,
            tPoe_init_params->eMeba_poe_firmware_type);

        tLaguna_poe_parameters.poe_init_params = *tPoe_init_params;

        pd_system.controllers[0].index = 0;
        meba_pd_bt_driver_init(&pd_system.controllers[0], "pd77010",
                               meba_pd_i2c_adapter_open(&pd_system.controllers[0],
                                                        laguna_gen7_i2c_config[0].i2c_device,
                                                        laguna_gen7_i2c_config[0].i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                   MEBA_POE_CTRL_INTERRUPTIBLE_POWER |
                                   MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST,
                               laguna_pd69777_4pairs_port_map,
                               sizeof(laguna_pd69777_4pairs_port_map) /
                                   sizeof(meba_poe_port_properties_t),
                               laguna_power_supplies,
                               sizeof(laguna_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug, tLaguna_poe_parameters);
    } else if (tPoe_init_params->eMeba_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_GEN6_PREBT) {
        // overide tMeba_poe_init_params params if using H file parameters
        if (tPoe_init_params->use_poe_static_parameters) {
            tPoe_init_params->max_poe_ports =
                sizeof(laguna_pd69200_4pairs_port_map) / sizeof(meba_poe_port_properties_t);
        }

        inst->iface.debug(
            MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,
            "gen6 PREBT: max_poe_ports=%d ,power_supply_max_power_w=%d ,eMeba_poe_firmware_type=%d",
            tPoe_init_params->max_poe_ports, tPoe_init_params->power_supply_max_power_w,
            tPoe_init_params->eMeba_poe_firmware_type);

        tLaguna_poe_parameters.poe_init_params = *tPoe_init_params;

        pd_system.controllers[0].index = 0;
        meba_pd69200_driver_init(&pd_system.controllers[0], "pd69x00at",
                                 meba_pd_i2c_adapter_open(&pd_system.controllers[0],
                                                          laguna_gen6_i2c_config[0].i2c_device,
                                                          laguna_gen6_i2c_config[0].i2c_address),
                                 MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                     MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                                     MEBA_POE_CTRL_INTERRUPTIBLE_POWER,
                                 laguna_pd69200_4pairs_port_map,
                                 sizeof(laguna_pd69200_4pairs_port_map) /
                                     sizeof(meba_poe_port_properties_t),
                                 laguna_power_supplies,
                                 sizeof(laguna_power_supplies) / sizeof(meba_poe_psu_input_prob_t),
                                 inst->iface.debug, tLaguna_poe_parameters);
    } else {
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
};

mesa_rc meba_poe_sparx5_system_initialize(meba_inst_t             inst,
                                          meba_poe_init_params_t *tPoe_init_params)
{
    // Do poe chip detection and fill
    // sparx5_ctrl.api = ....;
    // sparx5_ctrl.private_data = ....;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    switch (inst->props.board_type) {
    case BOARD_TYPE_SPARX5_PCB135:
        return meba_poe_sparx5_pcb135_system_initialize(inst, tPoe_init_params);
    case BOARD_TYPE_LAGUNA_PCB8398:
        return meba_poe_laguna_pcb8398_system_initialize(inst, tPoe_init_params);
    default: return MESA_RC_OK;
    }
}

mesa_rc meba_poe_sparx5_get_controller_handle(meba_inst_t             inst,
                                              mesa_port_no_t          port_no,
                                              meba_poe_ctrl_inst_t  **controller,
                                              meba_poe_port_handle_t *handle)
{
    for (int i = 0; i < pd_system.controller_count; ++i) {
        for (int j = 0; j < pd_system.controllers[i].port_map_length; ++j) {
            if (pd_system.controllers[i].port_map[j].port_no == port_no) {
                *controller = &pd_system.controllers[i];
                *handle = pd_system.controllers[i].port_map[j].handle;
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

// returns values:
// - MESA_RC_OK : when all controllers are responded (not MESA_RC_ERROR)
// - MESA_RC_ERROR : when one or more controllers are responded with MESA_RC_ERROR
mesa_rc meba_poe_sparx5_do_detection(meba_inst_t inst)
{
    mesa_rc rc = MESA_RC_ERROR;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");

    inst->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, "controller_count: %d",
                      pd_system.controller_count);

    for (int i = 0; i < pd_system.controller_count; ++i) {
        if (pd_system.controllers[i].api->meba_poe_ctrl_do_detection(&pd_system.controllers[i]) ==
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
    .meba_poe_system_initialize = meba_poe_sparx5_system_initialize,
    .meba_poe_system_get = meba_poe_sparx5_system_get,
    .meba_poe_get_controller_handle = meba_poe_sparx5_get_controller_handle,
    .meba_poe_do_detection = meba_poe_sparx5_do_detection,
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
