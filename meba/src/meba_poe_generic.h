// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_BOARD_POE_GENERIC_H_
#define _MICROCHIP_ETHERNET_BOARD_POE_GENERIC_H_

#include <stdio.h>
#include "microchip/ethernet/board/api.h"
#include "meba_generic.h"

#define MEBA_POE_ONE_CONTROLLER  1
#define MEBA_POE_TWO_CONTROLLERS 2

#define MEBA_POE_FIRMWARE_TYPE_NONE       0
#define MEBA_POE_FIRMWARE_TYPE_GEN6_PREBT 1
#define MEBA_POE_FIRMWARE_TYPE_GEN6_BT    2
#define MEBA_POE_FIRMWARE_TYPE_GEN7_BT    3

#define MEBA_POE_PORT_MAX_POWER_15W 15
#define MEBA_POE_PORT_MAX_POWER_30W 30
#define MEBA_POE_PORT_MAX_POWER_60W 60
#define MEBA_POE_PORT_MAX_POWER_90W 90

#define MEBA_POE_GEN6_PD692X0_CONTROLLER_TYPE_AUTO_DETECTION 0
#define MEBA_POE_GEN6_PD69200_CONTROLLER_TYPE                1
#define MEBA_POE_GEN6_PD69210_CONTROLLER_TYPE                2
#define MEBA_POE_GEN6_PD69220_CONTROLLER_TYPE                3
#define MEBA_POE_GEN6_PD69200M_CONTROLLER_TYPE               4

mesa_rc meba_poe_generic_chip_initialization(const meba_inst_t inst,
                                             mesa_bool_t       interruptible_power,
                                             int16_t           restart_cause);

mesa_rc meba_poe_generic_sync(const meba_inst_t inst);

mesa_rc meba_poe_generic_chipset_get(const meba_inst_t      inst,
                                     mesa_port_no_t         index,
                                     meba_poe_chip_state_t *chip_state);

mesa_rc meba_poe_generic_version_get(const meba_inst_t inst, uint32_t max_size, char *version);

mesa_rc meba_poe_generic_cfg_set(const meba_inst_t inst, meba_poe_global_cfg_t *cfg);

mesa_rc meba_poe_generic_status_get(const meba_inst_t inst, meba_poe_status_t *status);

mesa_rc meba_poe_generic_capabilities_get(const meba_inst_t    inst,
                                          meba_poe_ctrl_cap_t *capabilities);

mesa_rc meba_poe_generic_port_cfg_set(const meba_inst_t    inst,
                                      mesa_port_no_t       port_no,
                                      meba_poe_port_cfg_t *cfg);

mesa_rc meba_poe_generic_port_prio_set(const meba_inst_t            inst,
                                       mesa_port_no_t               port_no,
                                       meba_poe_pd_power_priority_t prio);

mesa_rc meba_poe_generic_port_max_power_set(const meba_inst_t    inst,
                                            mesa_port_no_t       port_no,
                                            mesa_poe_milliwatt_t power);

mesa_rc meba_poe_generic_port_status_get(const meba_inst_t             inst,
                                         mesa_port_no_t                port_no,
                                         meba_poe_port_status_t *const status);

mesa_rc meba_poe_generic_reset_command(const meba_inst_t inst);

mesa_rc meba_poe_generic_save_command(const meba_inst_t inst);

mesa_rc meba_poe_generic_debug(const meba_inst_t inst,
                               mesa_port_no_t    port_no,
                               char             *var,
                               uint32_t          str_len,
                               char             *title,
                               char             *tx_str,
                               char             *rx_str,
                               char             *msg,
                               int               max_msg_len);

mesa_rc meba_poe_generic_supply_limits_get(const meba_inst_t          inst,
                                           meba_poe_ctrl_psu_t        id,
                                           meba_poe_psu_input_prob_t *psu_prop);

int meba_poe_generic_firmware_upgrade(const meba_inst_t inst,
                                      mesa_bool_t       reset,
                                      uint32_t          size,
                                      const char       *data);

mesa_rc meba_poe_generic_prepare_firmware_upgrade(const meba_inst_t inst,
                                                  mesa_bool_t       version_check,
                                                  uint32_t          size,
                                                  const char       *data);

mesa_rc meba_poe_generic_port_capabilities_get(const meba_inst_t    inst,
                                               mesa_port_no_t       port_no,
                                               meba_poe_port_cap_t *capabilities);

mesa_rc meba_poe_generic_port_pd_data_set(const meba_inst_t   inst,
                                          mesa_port_no_t      port_no,
                                          meba_poe_pd_data_t *pd_data);

mesa_rc meba_poe_generic_port_pd_bt_data_set(const meba_inst_t      inst,
                                             mesa_port_no_t         port_no,
                                             meba_poe_pd_bt_data_t *pd_data);

mesa_rc meba_poe_generic_port_pd_data_clear(const meba_inst_t inst, mesa_port_no_t port_no);

#endif // _MICROCHIP_ETHERNET_BOARD_POE_GENERIC_H_
