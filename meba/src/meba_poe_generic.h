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

#ifndef _MSCC_ETHERNET_BOARD_POE_GENERIC_H_
#define _MSCC_ETHERNET_BOARD_POE_GENERIC_H_

#include <stdio.h>
#include "mscc/ethernet/board/api.h"

mesa_rc meba_poe_generic_chip_initialization(
    const meba_inst_t               inst);

mesa_rc meba_poe_generic_sync(
    const meba_inst_t               inst);

mesa_rc meba_poe_generic_chipset_get(
    const meba_inst_t               inst,
    mesa_port_no_t                  index,
    meba_poe_chip_state_t          *chip_state);

mesa_rc meba_poe_generic_version_get(
    const meba_inst_t               inst,
    uint32_t                        max_size,
    char                            *version);

mesa_rc meba_poe_generic_cfg_set(
    const meba_inst_t               inst,
    meba_poe_cfg_t                  *cfg);

mesa_rc meba_poe_generic_status_get(
    const meba_inst_t               inst,
    meba_poe_status_t               *status);

mesa_rc meba_poe_generic_capabilities_get(
    const meba_inst_t               inst,
    meba_poe_ctrl_cap_t             *capabilities);

mesa_rc meba_poe_generic_port_cfg_set(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_port_cfg_t             *cfg);

mesa_rc meba_poe_generic_port_prio_set(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_port_prio_t            prio);

mesa_rc meba_poe_generic_port_max_power_set(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    mesa_poe_milliwatt_t            power);

mesa_rc meba_poe_generic_port_status_get(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_port_status_t          *const status);

mesa_rc meba_poe_generic_reset_command(
    const meba_inst_t         inst);

mesa_rc meba_poe_generic_debug(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    uint8_t                         *buf,
    int                             buf_size);

mesa_rc meba_poe_generic_supply_limits_get(
    const meba_inst_t          inst,
    meba_poe_ctrl_psu_t        id,
    meba_poe_psu_input_prob_t *psu_prop);

mesa_rc meba_poe_generic_firmware_upgrade(
    const meba_inst_t               inst,
    mesa_bool_t                     reset,
    uint32_t                        size,
    const char                      *data);

mesa_rc meba_poe_generic_prepare_firmware_upgrade(
    const meba_inst_t               inst,
    mesa_bool_t                     version_check,
    uint32_t                        size,
    const char                      *data);

mesa_rc meba_poe_generic_port_capabilities_get(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_port_cap_t             *capabilities);

mesa_rc meba_poe_generic_port_pd_data_set(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_pd_data_t              *pd_data);

mesa_rc meba_poe_generic_port_pd_bt_data_set(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no,
    meba_poe_pd_bt_data_t           *pd_data);

mesa_rc meba_poe_generic_port_pd_data_clear(
    const meba_inst_t               inst,
    mesa_port_no_t                  port_no);

#endif  // _MSCC_ETHERNET_BOARD_POE_GENERIC_H_
