// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include "microchip/ethernet/board/api.h"
#include "meba_poe_generic.h"

#define MESA_RC(EXPR) { mesa_rc rc = EXPR; if (rc != MESA_RC_OK) { return rc; } }

mesa_rc meba_poe_generic_chip_initialization(
    const meba_inst_t   inst,
    mesa_bool_t interruptible_power,
    int16_t     restart_cause)
{
    meba_poe_system_t   *system;
    int i;

    if ( !inst || !inst->api_poe || !inst->api_poe->meba_poe_system_get ) {
        return MESA_RC_ERROR;
    }

    if (inst->api_poe->meba_poe_system_get(inst, &system) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }

    for (i=0; i<system->controller_count; ++i) {
        (void)system->controllers[i].api->meba_poe_ctrl_chip_initialization(&system->controllers[i], interruptible_power, restart_cause);
    }

    return MESA_RC_OK;
}

mesa_rc meba_poe_generic_sync(
    const meba_inst_t               inst)
{
    meba_poe_system_t   *system;
    int i;

    if ( !inst || !inst->api_poe || !inst->api_poe->meba_poe_system_get) {
        return MESA_RC_ERROR;
    }

    if (inst->api_poe->meba_poe_system_get(inst, &system) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }

    for (i=0; i<system->controller_count; ++i) {
        system->controllers[i].api->meba_poe_ctrl_sync(&system->controllers[i]);
    }

    return MESA_RC_OK;
}

mesa_rc meba_poe_generic_chipset_get(
        const meba_inst_t             inst,
        mesa_port_no_t                iport,
        meba_poe_chip_state_t         *chip_state)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    *chip_state = MEBA_POE_NO_CHIPSET_FOUND;
    if (inst->api_poe->meba_poe_get_controller_handle(inst, iport, &controller, &handle) == MESA_RC_OK) {
        if (MESA_RC_OK == controller->api->meba_poe_ctrl_chipset_get(controller, handle, chip_state)) {
            return MESA_RC_OK;
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_version_get(
        const meba_inst_t             inst,
        uint32_t                      max_size,
        char                         *value)
{
    meba_poe_system_t   *system;
    int i;

    if ( !inst || !inst->api_poe || !inst->api_poe->meba_poe_system_get) {
        return MESA_RC_ERROR;
    }

    if (inst->api_poe->meba_poe_system_get(inst, &system) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }

    for (i=0; i<system->controller_count; ++i) {
        if (MESA_RC_OK == system->controllers[i].api->meba_poe_ctrl_version_get(&system->controllers[i], max_size, value)) {
            return MESA_RC_OK;
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_port_status_get(
        const meba_inst_t              inst,
        mesa_port_no_t                 port_no,
        meba_poe_port_status_t        *const status)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    if (!inst ||
        !inst->api_poe ||
        !inst->api_poe->meba_poe_get_controller_handle) {
        return MESA_RC_ERROR;
    }

    mesa_rc rc = inst->api_poe->meba_poe_get_controller_handle(inst, port_no, &controller, &handle);
    if (rc != MESA_RC_OK)
    {
        if (rc == MESA_RC_ERR_NOT_POE_PORT_ERR)
            return MESA_RC_ERR_NOT_POE_PORT_ERR;
        else
            return MESA_RC_ERROR;
    }

    return controller->api->meba_poe_ctrl_port_status_get(controller, handle, status);
}

mesa_rc meba_poe_generic_reset_command(
    const meba_inst_t         inst)
{
    meba_poe_system_t   *system;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_system_get) {
        if (inst->api_poe->meba_poe_system_get(inst, &system) == MESA_RC_OK) {
            int i;
            for (i=0; i<system->controller_count; ++i) {
                mesa_rc rc;
                rc = system->controllers[i].api->meba_poe_ctrl_reset_command(&system->controllers[i]);
                if (rc != MESA_RC_OK) {
                    return rc;
                }
            }
        }
    }
    return MESA_RC_OK;
}

mesa_rc meba_poe_generic_save_command(
    const meba_inst_t         inst)
{
    meba_poe_system_t   *system;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_system_get) {
        if (inst->api_poe->meba_poe_system_get(inst, &system) == MESA_RC_OK) {
            int i;
            for (i=0; i<system->controller_count; ++i) {
                mesa_rc rc;
                rc = system->controllers[i].api->meba_poe_ctrl_save_command(&system->controllers[i]);
                if (rc != MESA_RC_OK) {
                    return rc;
                }
            }
        }
    }
    return MESA_RC_OK;
}

int meba_poe_generic_firmware_upgrade(
    const meba_inst_t               inst,
    mesa_bool_t                     reset,
    uint32_t                        size,
    const char                     *data)
{
    meba_poe_system_t   *system;
    int i;

    if ( !inst || !inst->api_poe || !inst->api_poe->meba_poe_system_get) {
        return 0;
    }
    if (inst->api_poe->meba_poe_system_get(inst, &system) != MESA_RC_OK) {
        return 0;
    }

    int count = 0;
    for (i=0; i<system->controller_count; ++i) {
        if (MESA_RC_OK == system->controllers[i].api->meba_poe_ctrl_firmware_upgrade(&system->controllers[i], reset, size, data)) {
            count++;
        }
    }
    return count;
}

// return MESA_RC_ERR_POE_FIRMWARE_IS_UP_TO_DATE if firmware update is needed for any of the controllers. otherwise returns MESA_RC_OK
mesa_rc meba_poe_generic_prepare_firmware_upgrade(
    const meba_inst_t               inst,
    mesa_bool_t                     version_check,
    uint32_t                        size,
    const char                     *data)
{
    meba_poe_system_t   *system;
    int i;
    mesa_rc rc = MESA_RC_OK;

    if ( !inst || !inst->api_poe || !inst->api_poe->meba_poe_system_get) {
        return MESA_RC_OK;
    }
    if (inst->api_poe->meba_poe_system_get(inst, &system) != MESA_RC_OK) {
        return MESA_RC_OK;
    }
    for (i=0; i<system->controller_count; ++i) {
        mesa_rc rc_;
        rc_ = system->controllers[i].api->meba_poe_ctrl_prepare_firmware_upgrade(&system->controllers[i], version_check, size, data);
        if (rc == MESA_RC_OK && rc_ != MESA_RC_OK) {
            rc = rc_;
        }
    }
    return rc;
}

mesa_rc meba_poe_generic_cfg_set(
    const meba_inst_t             inst,
    meba_poe_global_cfg_t         *cfg)
{
    meba_poe_system_t   *system;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_system_get) {
        if (inst->api_poe->meba_poe_system_get(inst, &system) == MESA_RC_OK) {
            int i;
            for (i=0; i<system->controller_count; ++i) {
                (void)system->controllers[i].api->meba_poe_ctrl_cfg_set(&system->controllers[i], cfg);
            }
        }
    }
    return MESA_RC_OK;
}

mesa_rc meba_poe_generic_status_get(
    const meba_inst_t             inst,
    meba_poe_status_t            *status)
{
    meba_poe_system_t   *system;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_system_get) {
        if (inst->api_poe->meba_poe_system_get(inst, &system) == MESA_RC_OK) {
            uint32_t i;
            meba_poe_status_t local_status[system->controller_count];
            uint32_t controller_count = 0;
            uint32_t valid_controller;
            for (i=0; i<system->controller_count; ++i)
            {
                if (MESA_RC_OK == system->controllers[i].api->meba_poe_ctrl_status_get(&system->controllers[i], &local_status[i]))
                {
                    controller_count++;
                    valid_controller = i;
                }
            }
            if (controller_count>0)
            {
                *status = local_status[valid_controller];
                status->operational_controller_count = controller_count;
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_capabilities_get(
    const meba_inst_t             inst,
    meba_poe_ctrl_cap_t           *capabilities)
{
    meba_poe_system_t   *system;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_system_get) {
        if (inst->api_poe->meba_poe_system_get(inst, &system) == MESA_RC_OK) {
            int i;
            for (i=0; i<system->controller_count; ++i) {
                *capabilities = system->controllers[i].capabilities;
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_port_cfg_set(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_port_cfg_t            *cfg)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_get_controller_handle ) {
        if (inst->api_poe->meba_poe_get_controller_handle(inst, port_no, &controller, &handle) == MESA_RC_OK) {
            if (controller->api->meba_poe_ctrl_port_cfg_set(controller, handle, cfg) == MESA_RC_OK) {
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_supply_limits_get(
    const meba_inst_t          inst,
    meba_poe_ctrl_psu_t        id,
    meba_poe_psu_input_prob_t *psu_prop)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_get_controller_handle ) {
        if (inst->api_poe->meba_poe_get_controller_handle(inst, 0, &controller, &handle) == MESA_RC_OK) {
            int i;
            for (i=0; i<controller->psu_map_length; ++i) {
                if (id == controller->psu_map[i].id) {
                    *psu_prop = controller->psu_map[i];
                    return MESA_RC_OK;
                }
            }

        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_port_capabilities_get(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_port_cap_t             *capabilities)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_get_controller_handle ) {
        if (inst->api_poe->meba_poe_get_controller_handle(inst, port_no, &controller, &handle) == MESA_RC_OK) {
            if(controller->api->meba_poe_ctrl_port_capabilities_get(controller, handle, capabilities) == MESA_RC_OK) {
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_debug(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    char                            *var,
    uint32_t                        str_len,
    char                            *title ,
    char                            *tx_str ,
    char                            *rx_str ,
    char                            *msg,
    int                             max_msg_len)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_get_controller_handle ) {
        if (inst->api_poe->meba_poe_get_controller_handle(inst, port_no, &controller, &handle) == MESA_RC_OK) {
            if (controller->api->meba_poe_ctrl_debug(controller ,var ,str_len ,title ,tx_str ,rx_str ,msg ,max_msg_len) == MESA_RC_OK) {
                return MESA_RC_OK;
            }
        }
        else
            printf("\n\r       Debug pd69200 access failed. no such port or controller \n\r");
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_port_pd_data_set(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_pd_data_t             *pd_data)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_get_controller_handle ) {
        if (inst->api_poe->meba_poe_get_controller_handle(inst, port_no, &controller, &handle) == MESA_RC_OK) {
            if (controller->api->meba_poe_ctrl_port_pd_data_set(controller, handle, pd_data) == MESA_RC_OK) {
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_port_pd_bt_data_set(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_pd_bt_data_t          *pd_data)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_get_controller_handle ) {
        if (inst->api_poe->meba_poe_get_controller_handle(inst, port_no, &controller, &handle) == MESA_RC_OK) {
            if (controller->api->meba_poe_ctrl_port_pd_bt_data_set(controller, handle, pd_data) == MESA_RC_OK) {
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}

mesa_rc meba_poe_generic_port_pd_data_clear(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no)
{
    meba_poe_ctrl_inst_t *controller;
    meba_poe_port_handle_t handle;
    if ( inst && inst->api_poe && inst->api_poe->meba_poe_get_controller_handle ) {
        if (inst->api_poe->meba_poe_get_controller_handle(inst, port_no, &controller, &handle) == MESA_RC_OK) {
            if (controller->api->meba_poe_ctrl_port_pd_data_clear(controller, handle) == MESA_RC_OK) {
                return MESA_RC_OK;
            }
        }
    }
    return MESA_RC_ERROR;
}
