// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <sys/stat.h>

#include "microchip/ethernet/board/api.h"
#include "meba_poe_generic.h"
#include "poe_driver.h"

#define PD69200_CAP MEBA_POE_PORT_CAP_POE | \
    MEBA_POE_PORT_CAP_TYPE_1 | \
    MEBA_POE_PORT_CAP_TYPE_2 | \
    MEBA_POE_PORT_CAP_FORCE_ON

meba_poe_port_properties_t sparx5_pd69200_port_map_1[] =
{ { PD69200_CAP, 24000, 0, 0, 0, 24 },
  { PD69200_CAP, 24000, 1, 1, 1, 25 },
  { PD69200_CAP, 24000, 2, 2, 2, 26 },
  { PD69200_CAP, 24000, 3, 3, 3, 27 },
  { PD69200_CAP, 24000, 4, 4, 4, 28 },
  { PD69200_CAP, 24000, 5, 5, 5, 29 },
  { PD69200_CAP, 24000, 6, 6, 6, 30 },
  { PD69200_CAP, 24000, 7, 7, 7, 31 },
  { PD69200_CAP, 24000, 8, 8, 8, 32 },
  { PD69200_CAP, 24000, 9, 9, 9, 33 },
  { PD69200_CAP, 24000, 10, 10, 10, 34 },
  { PD69200_CAP, 24000, 11, 11, 11, 35 },
  { PD69200_CAP, 24000, 12, 12, 12, 36 },
  { PD69200_CAP, 24000, 13, 13, 13, 37 },
  { PD69200_CAP, 24000, 14, 14, 14, 38 },
  { PD69200_CAP, 24000, 15, 15, 15, 39 },
  { PD69200_CAP, 24000, 16, 16, 16, 40 },
  { PD69200_CAP, 24000, 17, 17, 17, 41 },
  { PD69200_CAP, 24000, 18, 18, 18, 42 },
  { PD69200_CAP, 24000, 19, 19, 19, 43 },
  { PD69200_CAP, 24000, 20, 20, 20, 44 },
  { PD69200_CAP, 24000, 21, 21, 21, 45 },
  { PD69200_CAP, 24000, 22, 22, 22, 46 },
  { PD69200_CAP, 24000, 23, 23, 23, 47 },
};

meba_poe_port_properties_t sparx5_pd69200_port_map_2[] =
{ { PD69200_CAP, 24000, 24, 0, 0, 24 },
  { PD69200_CAP, 24000, 25, 1, 1, 25 },
  { PD69200_CAP, 24000, 26, 2, 2, 26 },
  { PD69200_CAP, 24000, 27, 3, 3, 27 },
  { PD69200_CAP, 24000, 28, 4, 4, 28 },
  { PD69200_CAP, 24000, 29, 5, 5, 29 },
  { PD69200_CAP, 24000, 30, 6, 6, 30 },
  { PD69200_CAP, 24000, 31, 7, 7, 31 },
  { PD69200_CAP, 24000, 32, 8, 8, 32 },
  { PD69200_CAP, 24000, 33, 9, 9, 33 },
  { PD69200_CAP, 24000, 34, 10, 10, 34 },
  { PD69200_CAP, 24000, 35, 11, 11, 35 },
  { PD69200_CAP, 24000, 36, 12, 12, 36 },
  { PD69200_CAP, 24000, 37, 13, 13, 37 },
  { PD69200_CAP, 24000, 38, 14, 14, 38 },
  { PD69200_CAP, 24000, 39, 15, 15, 39 },
  { PD69200_CAP, 24000, 40, 16, 16, 40 },
  { PD69200_CAP, 24000, 41, 17, 17, 41 },
  { PD69200_CAP, 24000, 42, 18, 18, 42 },
  { PD69200_CAP, 24000, 43, 19, 19, 43 },
  { PD69200_CAP, 24000, 44, 20, 20, 44 },
  { PD69200_CAP, 24000, 45, 21, 21, 45 },
  { PD69200_CAP, 24000, 46, 22, 22, 46 },
  { PD69200_CAP, 24000, 47, 23, 23, 47 },
};

meba_poe_psu_input_prob_t sparx5_power_supplies[] =
{ {MEBA_POE_CTRL_PSU_ALL, 0, 5000000, 10000, 0, 1},
};

meba_poe_system_t sparx5_pd69200_system;

static
i2c_config_t sparx5_i2c_config[] =
{ { "/dev/i2c-0", 0x14 },
  { "/dev/i2c-0", 0x28 }
};

mesa_rc meba_poe_sparx5_system_get(
        meba_inst_t                     inst,
        meba_poe_system_t             **const system)
{
    *system = &sparx5_pd69200_system;
    return MESA_RC_OK;
}

mesa_rc meba_poe_sparx5_system_initialize(
        meba_inst_t                     inst)
{
    // Do poe chip detection and fill
    /* sparx5_ctrl.api = ....; */
    /* sparx5_ctrl.private_data = ....; */
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    sparx5_pd69200_system.controller_count = 2;
    sparx5_pd69200_system.controllers = malloc(sizeof(meba_poe_ctrl_inst_t) * sparx5_pd69200_system.controller_count);
    meba_pd69200bt_driver_init(&sparx5_pd69200_system.controllers[0],
                               "pd69x00",
                               meba_pd69200_i2c_adapter_open(sparx5_i2c_config[0].i2c_device,
                                                             sparx5_i2c_config[0].i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT | MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION,
                               sparx5_pd69200_port_map_1,
                               sizeof(sparx5_pd69200_port_map_1)/sizeof(meba_poe_port_properties_t),
                               sparx5_power_supplies,
                               sizeof(sparx5_power_supplies)/sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug);
    meba_pd69200bt_driver_init(&sparx5_pd69200_system.controllers[1],
                               "pd69x00-2",
                               meba_pd69200_i2c_adapter_open(sparx5_i2c_config[1].i2c_device,
                                                             sparx5_i2c_config[1].i2c_address),
                               MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                               MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                               MEBA_POE_CTRL_UNINTERRUPTABLE_POWER,
                               sparx5_pd69200_port_map_2,
                               sizeof(sparx5_pd69200_port_map_2)/sizeof(meba_poe_port_properties_t),
                               sparx5_power_supplies,
                               sizeof(sparx5_power_supplies)/sizeof(meba_poe_psu_input_prob_t),
                               inst->iface.debug);
    return MESA_RC_OK;
};

mesa_rc meba_poe_sparx5_get_controller_handle(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       meba_poe_ctrl_inst_t **controller,
                                       meba_poe_port_handle_t *handle)
{
    for (int i = 0; i < sparx5_pd69200_system.controller_count; ++i) {
        for (int j = 0; j<sparx5_pd69200_system.controllers[i].port_map_length; ++j) {
            if (sparx5_pd69200_system.controllers[i].port_map[j].port_no == port_no) {
                *controller = &sparx5_pd69200_system.controllers[i];
                *handle = sparx5_pd69200_system.controllers[i].port_map[j].handle;
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_sparx5_do_detection(meba_inst_t inst)
{
    int i;
    mesa_rc rc = MESA_RC_ERROR;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    for (i = 0; i < sparx5_pd69200_system.controller_count; ++i) {
        if (sparx5_pd69200_system.controllers[i].api->meba_poe_ctrl_do_detection(&sparx5_pd69200_system.controllers[i]) != MESA_RC_OK) {
            inst->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, "Detection Failed for controller: %d", i);
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
