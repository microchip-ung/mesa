// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include "microchip/ethernet/board/api.h"
#include "meba_poe_generic.h"
#include "poe_driver.h"


#define PD69200_CAP MEBA_POE_PORT_CAP_POE | \
    MEBA_POE_PORT_CAP_TYPE_1 | \
    MEBA_POE_PORT_CAP_TYPE_2 | \
    MEBA_POE_PORT_CAP_FORCE_ON

meba_poe_port_properties_t caracal_pd69200_port_map[] = 
{ { PD69200_CAP, 24000, 0, 0, 0, 255 },
  { PD69200_CAP, 24000, 1, 1, 1, 255 },
  { PD69200_CAP, 24000, 2, 2, 2, 255 },
  { PD69200_CAP, 24000, 3, 3, 3, 255 },
  { PD69200_CAP, 24000, 4, 4, 4, 255 },
  { PD69200_CAP, 24000, 5, 5, 5, 255 },
  { PD69200_CAP, 24000, 6, 6, 6, 255 },
  { PD69200_CAP, 24000, 7, 7, 7, 255 },
  { PD69200_CAP, 24000, 8, 8, 8, 255 },
  { PD69200_CAP, 24000, 9, 9, 9, 255 },
  { PD69200_CAP, 24000, 10, 10, 10, 255 },
  { PD69200_CAP, 24000, 11, 11, 11, 255 },
  { PD69200_CAP, 24000, 12, 12, 12, 255 },
  { PD69200_CAP, 24000, 13, 13, 13, 255 },
  { PD69200_CAP, 24000, 14, 14, 14, 255 },
  { PD69200_CAP, 24000, 15, 15, 15, 255 },
  { PD69200_CAP, 24000, 16, 16, 16, 255 },
  { PD69200_CAP, 24000, 17, 17, 17, 255 },
  { PD69200_CAP, 24000, 18, 18, 18, 255 },
  { PD69200_CAP, 24000, 19, 19, 19, 255 },
  { PD69200_CAP, 24000, 20, 20, 20, 255 },
  { PD69200_CAP, 24000, 21, 21, 21, 255 },
  { PD69200_CAP, 24000, 22, 22, 22, 255 },
  { PD69200_CAP, 24000, 23, 23, 23, 255 },
};

#define PD69200BT_CAP MEBA_POE_PORT_CAP_POE | \
    MEBA_POE_PORT_CAP_TYPE_1 | \
    MEBA_POE_PORT_CAP_TYPE_2 | \
    MEBA_POE_PORT_CAP_TYPE_3 | \
    MEBA_POE_PORT_CAP_TYPE_4 | \
    MEBA_POE_PORT_CAP_4PAIR  | \
    MEBA_POE_PORT_CAP_FORCE_ON

meba_poe_port_properties_t pds408g_pd69200_port_map[] =
{ { PD69200BT_CAP, 24000, 0, 0, 0, 8  },
  { PD69200BT_CAP, 24000, 1, 1, 1, 9  },
  { PD69200BT_CAP, 24000, 2, 2, 2, 10 },
  { PD69200BT_CAP, 24000, 3, 3, 3, 11 },
  { PD69200BT_CAP, 24000, 4, 4, 4, 12 },
  { PD69200BT_CAP, 24000, 5, 5, 5, 13 },
  { PD69200BT_CAP, 24000, 6, 6, 6, 14 },
  { PD69200BT_CAP, 24000, 7, 7, 7, 15 },
};

meba_poe_psu_input_prob_t caracal_power_supplies[] =
{ {MEBA_POE_CTRL_PSU_ALL, 0, 100000, 10000, 0, 1}
};

meba_poe_psu_input_prob_t pds408g_power_supplies[] =
{ {MEBA_POE_CTRL_PSU_ALL, 0, 480000, 480000, 0, 0}
};

meba_poe_system_t caracal_pd69200_system;

i2c_config_t caracal_i2c_config = { "/dev/i2c-203", 0x14 };

i2c_config_t pds408g_i2c_config = { "/dev/i2c-203", 0x20 };

mesa_rc meba_poe_caracal_system_get(
        meba_inst_t                     inst,
        meba_poe_system_t             **const system)
{
    *system = &caracal_pd69200_system;
    return MESA_RC_OK;
}

mesa_rc meba_poe_caracal_system_initialize(
        meba_inst_t                     inst)
{
    // Do poe chip detection and fill
    /* caracal_ctrl.api = ....; */
    /* caracal_ctrl.private_data = ....; */
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    caracal_pd69200_system.controller_count = 1;
    caracal_pd69200_system.controllers = malloc(sizeof(meba_poe_ctrl_inst_t) * caracal_pd69200_system.controller_count);
    switch (inst->props.board_type) {
        case VTSS_BOARD_LUTON10_PDS408G:
            caracal_pd69200_system.controller_count = 1;
            caracal_pd69200_system.controllers = malloc(sizeof(meba_poe_ctrl_inst_t) * caracal_pd69200_system.controller_count);
            meba_pd69200bt_driver_init(&caracal_pd69200_system.controllers[0],
                                       "pd69x00bt",
                                       meba_pd69200_i2c_adapter_open(pds408g_i2c_config.i2c_device,
                                                                     pds408g_i2c_config.i2c_address),
                                       MEBA_POE_CTRL_CAP_POWER_MANAGEMENT | MEBA_POE_CTRL_UNINTERRUPTABLE_POWER,
                                       pds408g_pd69200_port_map,
                                       sizeof(pds408g_pd69200_port_map)/sizeof(meba_poe_port_properties_t),
                                       pds408g_power_supplies,
                                       sizeof(pds408g_power_supplies)/sizeof(meba_poe_psu_input_prob_t),
                                       inst->iface.debug);
            break;
        default:
            caracal_pd69200_system.controller_count = 1;
            caracal_pd69200_system.controllers = malloc(sizeof(meba_poe_ctrl_inst_t) * caracal_pd69200_system.controller_count);
            meba_pd69200_driver_init(&caracal_pd69200_system.controllers[0],
                                     "pd69x00",
                                     meba_pd69200_i2c_adapter_open(caracal_i2c_config.i2c_device,
                                                                   caracal_i2c_config.i2c_address),
                                     MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                                     MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION |
                                     MEBA_POE_CTRL_UNINTERRUPTABLE_POWER,
                                     caracal_pd69200_port_map,
                                     sizeof(caracal_pd69200_port_map)/sizeof(meba_poe_port_properties_t),
                                     caracal_power_supplies,
                                     sizeof(caracal_power_supplies)/sizeof(meba_poe_psu_input_prob_t),
                                     inst->iface.debug);
    }
    return MESA_RC_OK;
};

mesa_rc meba_poe_caracal_get_controller_handle(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       meba_poe_ctrl_inst_t **controller,
                                       meba_poe_port_handle_t *handle)
{
    for (int i = 0; i < caracal_pd69200_system.controller_count; ++i) {
        for (int j = 0; j<caracal_pd69200_system.controllers[i].port_map_length; ++j) {
            if (caracal_pd69200_system.controllers[i].port_map[j].port_no == port_no) {
                *controller = &caracal_pd69200_system.controllers[i];
                *handle = caracal_pd69200_system.controllers[i].port_map[j].handle;
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_caracal_do_detection(meba_inst_t inst)
{
    int i;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    for (i = 0; i < caracal_pd69200_system.controller_count; ++i) {
        if (caracal_pd69200_system.controllers[i].api->meba_poe_ctrl_do_detection(&caracal_pd69200_system.controllers[i]) != MESA_RC_OK) {
            inst->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, "Detection Failed: %d", i);
            return MESA_RC_ERROR;
        }
    }
    return MESA_RC_OK;
}

static meba_api_poe_t public_functions = {
    .meba_poe_system_initialize = meba_poe_caracal_system_initialize,
    .meba_poe_system_get = meba_poe_caracal_system_get,
    .meba_poe_get_controller_handle = meba_poe_caracal_get_controller_handle,
    .meba_poe_do_detection = meba_poe_caracal_do_detection,
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

