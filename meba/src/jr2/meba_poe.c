// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "microchip/ethernet/board/api.h"
#include "meba_poe_generic.h"
#include "jr2_poe_hw_cfg.h"


meba_poe_parameters_t tPoE_parameters =
{
    .ePoE_Controller_Type_default = JR2_POE_PD692x0_CONTROLLER_TYPE_DEFAULT, // PD692x0 family detection method
    .ePoE_port_max_power_default  = JR2_BT_PORT_MAX_POWER_DEFAULT,           // System has 4 modes = 15/30/60/90 (applicable for all poe ports)

    // Port Operation Mode for legacy
    .bt_operation_mode_legacy_90W_poh_default             = JR2_BT_OPERATION_MODE_LEGACY_90W_POH_DEFAULT,
    .bt_operation_mode_legacy_60W_ignore_pd_class_default = JR2_BT_OPERATION_MODE_LEGACY_60W_IGNORE_PD_CLASS_DEFAULT,
    .bt_operation_mode_legacy_90W_ignore_pd_class_default = JR2_BT_OPERATION_MODE_LEGACY_90W_IGNORE_PD_CLASS_DEFAULT,

    .reset_poe_gpio_number                           = JR2_RESET_POE_GPIO_NUMBER,

    .indv_mask_AT_ignore_higher_priority_default     = JR2_INDV_MASK_AT_IGNORE_HIGHER_PRIORITY_DEFAULT,     // power higher priority port.
    .indv_mask_AT_supports_legact_detection_default  = JR2_INDV_MASK_AT_SUPPORTS_LEGACY_DETECTION_DEFAULT,  // En/Dis support of legacy detection.
    .indv_mask_AT_message_ready_notify_default       = JR2_INDV_MASK_AT_MESSAGE_READY_NOTIFY_DEFAULT,       // en/Dis MESSAGE_READY pin notification.
    .indv_mask_AT_layer2_lldp_enable_default         = JR2_INDV_MASK_AT_LAYER2_LLDP_ENABLE_DEFAULT,         // En/Dis Layer 2 PD commands.
    .indv_mask_AT_layer2_priority_by_PD_default      = JR2_INDV_MASK_AT_LAYER2_PRIORITY_BY_PD_DEFAULT,      // accept/ignored Port Priority recived from the PD
    .indv_mask_AT_matrix_support_4P_default          = JR2_INDV_MASK_AT_MATRIX_SUPPORT_4P_DEFAULT,          // use 4-pair matrix commands.
    .indv_mask_BT_ignore_higher_priority_default     = JR2_INDV_MASK_BT_IGNORE_HIGHER_PRIORITY_DEFAULT,     // power higher priority port.
    .indv_mask_BT_support_high_res_detection_default = JR2_INDV_MASK_BT_SUPPORT_HIGH_RES_DETECTION_DEFAULT, // expand Resistor detection range up to range to 55 K.
    .indv_mask_BT_i2c_restart_enable_default         = JR2_INDV_MASK_BT_I2C_RESTART_ENABLE_DEFAULT,         // Initialization of the I2C module system after 10 seconds of inactivity.
    .indv_mask_BT_led_stream_type_default            = JR2_INDV_MASK_BT_LED_STREAM_TYPE_DEFAULT,            // led stream type
    .indv_mask_HOCPP_default                         = JR2_INDV_MASK_BT_HOCPP_DEFAULT,                      // HOCPP - high_over Current Pulse Protection
    .indv_mask_PSE_powering_PSE_checking_default     = JR2_INDV_MASK_BT_PSE_POWERING_PSE_CHECKING_DEFAULT,               // PSE powering PSE checking
    .indv_mask_layer2_power_allocation_limit_default = JR2_INDV_MASK_BT_LAYER2_POWER_ALLOCATION_LIMIT_DEFAULT,           // Layer2 Power Allocation Limit
    .indv_mask_Port_LED_blinks_at_invalid_signature_or_connection_check_error_default = JR2_INDV_MASK_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR_DEFAULT,  // Port LED Blinks at invalid signature or connection-check error
    .indv_mask_support_adding_lldp_half_priority_default = JR2_INDV_MASK_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY_DEFAULT,   // Support adding lldp half priority

    // -----------  AT Power Management mode of operation  ----------------------//
    .AT_pm1_default = JR2_PM1_AT_DEFAULT,     // Selects the method of calculating total power consumption.
    .AT_PM2_default = JR2_PM2_AT_DEFAULT,     // Selects the power limit at the port (maximum or according to class or predefined).
    .AT_PM3_default = JR2_PM3_AT_DEFAULT      // Selects the start condition. (Not recommended for new designs, keep 0x00).
};


meba_poe_psu_input_prob_t jr2_power_supplies[] =
{
    {
        .id = MEBA_POE_CTRL_PSU_ALL,                // PowerSupply-ID
        .min_w = 0,                                 // PwrSuply Min-Pwr
        .max_w = JR2_POE_UNIT_MAX_POWER_W_DEFAULT,      // PwrSuply Max-Pwr
        .def_w = JR2_POE_UNIT_DEF_POWER_W_DEFAULT,      // PwrSuply Def-Capab
        .system_consumed_w = 0,                     // System PwrUsage
        .user_configurable = JR2_POE_UNIT_MAX_POWER_USER_CONFIG_DEFAULT     // User Conig 1=Yes,0=No
    }
};


meba_poe_system_t jr2_pd69200_system;

static
i2c_config_t jr2_i2c_config[] =
{ { "/dev/i2c-203", JR2_POE_CONTROLLER_1_I2C_ADDRESS },
  { "/dev/i2c-203", JR2_POE_CONTROLLER_2_I2C_ADDRESS }
};

mesa_rc meba_poe_jr2_system_get(
        meba_inst_t                     inst,
        meba_poe_system_t             **const system)
{
    *system = &jr2_pd69200_system;
    return MESA_RC_OK;
}

mesa_rc meba_poe_jr2_system_initialize(
        meba_inst_t            inst,
        meba_poe_init_params_t *tPoe_init_params)
{
    // Do poe chip detection and fill
    /* jr2_ctrl.api = ....; */
    /* jr2_ctrl.private_data = ....; */
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");

    uint8_t poe_12c0 = jr2_i2c_config[0].i2c_address;
    if (inst->poe_i2c_tags.poe_12c0 != 0)
    {
        poe_12c0 = inst->poe_i2c_tags.poe_12c0;
        //T_I("%s=%d", "poe_12c0", poe_12c0);
    }

    uint8_t poe_12c1 = jr2_i2c_config[1].i2c_address;
    if (inst->poe_i2c_tags.poe_12c1 != 0)
    {
        poe_12c1 = inst->poe_i2c_tags.poe_12c1;
        //T_I("%s=%d", "poe_12c1", poe_12c1);
    }

    jr2_pd69200_system.controller_count = 2;
    jr2_pd69200_system.controllers = malloc(sizeof(meba_poe_ctrl_inst_t) * jr2_pd69200_system.controller_count);


     // overide appl init_params if using H file parameters
    if(tPoe_init_params->use_poe_static_parameters) {
        tPoe_init_params->Max_POE_Ch                    = sizeof(jr2_pd69200AT_port_map_1)/sizeof(meba_poe_port_properties_t);
        tPoe_init_params->PwrSupply_MaxPwr              = JR2_POE_UNIT_MAX_POWER_W_DEFAULT;
        tPoe_init_params->eMEBA_POE_FIRMWARE_TYPE       = JR2_POE_FIRMWARE_TYPE_DEFAULT;
        tPoe_init_params->eMEBA_POE_SOFTWARE_POWER_TYPE = (JR2_POE_FIRMWARE_TYPE_DEFAULT == MEBA_POE_FIRMWARE_TYPE_BT) ? MEBA_POE_SOFTWARE_POWER_TYPE_BT : MEBA_POE_SOFTWARE_POWER_TYPE_AT;
    } else {
        jr2_power_supplies->def_w = tPoe_init_params->PwrSupply_MaxPwr;
        jr2_power_supplies->max_w = tPoe_init_params->PwrSupply_MaxPwr;
    }

    inst->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__,"using:  Max_POE_Ch=%d ,PwrSupply_MaxPwr=%d ,POE_FIRMWARE_TYPE=%d ,POE_SOFTWARE_TYPE=%d",
           tPoe_init_params->Max_POE_Ch ,
           tPoe_init_params->PwrSupply_MaxPwr,
           tPoe_init_params->eMEBA_POE_FIRMWARE_TYPE,
           tPoe_init_params->eMEBA_POE_SOFTWARE_POWER_TYPE);

    tPoE_parameters.poe_init_params = *tPoe_init_params;

    meba_pd69200_driver_init(&jr2_pd69200_system.controllers[0],
                             "pd69x00",
                             meba_pd69200_i2c_adapter_open(jr2_i2c_config[0].i2c_device, poe_12c0),
                             MEBA_POE_CTRL_CAP_POWER_MANAGEMENT | MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION,
                             jr2_pd69200AT_port_map_1,
                             sizeof(jr2_pd69200AT_port_map_1)/sizeof(meba_poe_port_properties_t),
                             jr2_power_supplies,
                             sizeof(jr2_power_supplies)/sizeof(meba_poe_psu_input_prob_t),
                             inst->iface.debug,
                             tPoE_parameters);

    if(tPoe_init_params->use_poe_static_parameters) {
        tPoE_parameters.poe_init_params.Max_POE_Ch = sizeof(jr2_pd69200AT_port_map_2)/sizeof(meba_poe_port_properties_t);
    }

    meba_pd69200_driver_init(&jr2_pd69200_system.controllers[1],
                             "pd69x00-2",
                             meba_pd69200_i2c_adapter_open(jr2_i2c_config[1].i2c_device, poe_12c1),
                             MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                             MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                             MEBA_POE_CTRL_INTERRUPTIBLE_POWER,
                             jr2_pd69200AT_port_map_2,
                             sizeof(jr2_pd69200AT_port_map_2)/sizeof(meba_poe_port_properties_t),
                             jr2_power_supplies,
                             sizeof(jr2_power_supplies)/sizeof(meba_poe_psu_input_prob_t),
                             inst->iface.debug,
                             tPoE_parameters);
    return MESA_RC_OK;
};

mesa_rc meba_poe_jr2_get_controller_handle(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       meba_poe_ctrl_inst_t **controller,
                                       meba_poe_port_handle_t *handle)
{
    for (int i = 0; i < jr2_pd69200_system.controller_count; ++i) {
        for (int j = 0; j<jr2_pd69200_system.controllers[i].port_map_length; ++j) {
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
    for (int i = 0; i < jr2_pd69200_system.controller_count; ++i)
    {
        if (jr2_pd69200_system.controllers[i].api->meba_poe_ctrl_do_detection(&jr2_pd69200_system.controllers[i]) == MESA_RC_ERROR)
        {
            inst->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, "Detection Failed for controller: %d", i);
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

meba_api_poe_t *meba_poe_get()
{
    return &public_functions;
}


#undef _JR2_MEBA_POE_C_
