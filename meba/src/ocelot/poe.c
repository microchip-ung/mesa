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
#include <stdio.h>
#include "mscc/ethernet/board/api.h"
#include "meba_poe_generic.h"
#include "poe_driver.h"

#define PD69200_CAP MEBA_POE_PORT_CAP_POE | \
    MEBA_POE_PORT_CAP_TYPE_1 | \
    MEBA_POE_PORT_CAP_TYPE_2 | \
    MEBA_POE_PORT_CAP_FORCE_ON

meba_poe_port_properties_t ocelot_pd69200_port_map[] = 
{ { PD69200_CAP, 24000, 0, 0, 6 },
  { PD69200_CAP, 24000, 1, 1, 1 },
  { PD69200_CAP, 24000, 2, 2, 7 },
  { PD69200_CAP, 24000, 3, 3, 0 },
  { PD69200_CAP, 24000, 4, 4, 4 },
  { PD69200_CAP, 24000, 5, 5, 3 },
  { PD69200_CAP, 24000, 6, 6, 5 },
  { PD69200_CAP, 24000, 7, 7, 2 },
};

meba_poe_psu_input_prob_t ocelot_power_supplies[] =
{ {MEBA_POE_CTRL_PSU_ALL, 0, 100000, 10000, 10000, 1}
};

meba_poe_system_t ocelot_pd69200_system;

static
i2c_config_t ocelot_i2c_config = { "/dev/i2c-201", 0x20 };

mesa_rc meba_poe_system_get(
        const meba_inst_t             inst,
        meba_poe_system_t             **const system)
{
    *system = &ocelot_pd69200_system;
    return MESA_RC_OK;
}

mesa_rc meba_poe_system_initialize(
        const meba_inst_t             inst)
{
    // Do poe chip detection and fill
    /* ocelot_ctrl.api = ....; */
    /* ocelot_ctrl.private_data = ....; */
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    ocelot_pd69200_system.controller_count = 1;
    ocelot_pd69200_system.controllers = malloc(sizeof(meba_poe_ctrl_inst_t) * ocelot_pd69200_system.controller_count);
    meba_pd69200_driver_init(&ocelot_pd69200_system.controllers[0],
                             "pd69x00",
                             meba_pd69200_i2c_adapter_open(ocelot_i2c_config.i2c_device,
                                                           ocelot_i2c_config.i2c_address),
                             MEBA_POE_CTRL_CAP_POWER_MANAGEMENT |
                             MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION,
                             ocelot_pd69200_port_map,
                             sizeof(ocelot_pd69200_port_map)/sizeof(meba_poe_port_properties_t),
                             ocelot_power_supplies,
                             sizeof(ocelot_power_supplies)/sizeof(meba_poe_psu_input_prob_t),
                             inst->iface.debug);
    return MESA_RC_OK;
};

mesa_rc meba_poe_get_controller_handle(const meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       meba_poe_ctrl_inst_t **controller,
                                       meba_poe_port_handle_t *handle)
{
    for (int i = 0; i < ocelot_pd69200_system.controller_count; ++i) {
        for (int j = 0; j<ocelot_pd69200_system.controllers[i].port_map_length; ++j) {
            if (ocelot_pd69200_system.controllers[i].port_map[j].port_no == port_no) {
                *controller = &ocelot_pd69200_system.controllers[i];
                *handle = ocelot_pd69200_system.controllers[i].port_map[j].handle;
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_do_detection(const meba_inst_t inst)
{
    int i;
    inst->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "Called");
    for (i = 0; i < ocelot_pd69200_system.controller_count; ++i) {
        if (ocelot_pd69200_system.controllers[i].api->meba_poe_ctrl_do_detection(&ocelot_pd69200_system.controllers[i]) != MESA_RC_OK) {
            inst->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, "Detection Failed: %d", i);
            return MESA_RC_ERROR;
        }
    }
    return MESA_RC_OK;
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

