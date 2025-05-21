// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <microchip/ethernet/board/api.h>

#include "meba_aux.h"
#include "meba_generic.h"

#define MAX_PORTS 32

typedef struct meba_board_state {
    int                port_cnt;
    meba_port_entry_t *port;
    mepa_device_t     *phy_devices[MAX_PORTS];
} meba_board_state_t;

static uint32_t lk_capability(meba_inst_t inst, int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
    case MEBA_CAP_POE:                         return 0;
    case MEBA_CAP_1588_CLK_ADJ_DAC:            return 0;
    case MEBA_CAP_1588_REF_CLK_SEL:            return 0;
    case MEBA_CAP_TEMP_SENSORS:                return 0;
    case MEBA_CAP_BOARD_PORT_COUNT:
    case MEBA_CAP_BOARD_PORT_MAP_COUNT:        return board->port_cnt;
    case MEBA_CAP_LED_MODES:                   return 0;
    case MEBA_CAP_DYING_GASP:                  return 0;
    case MEBA_CAP_FAN_SUPPORT:                 return 0;
    case MEBA_CAP_LED_DIM_SUPPORT:             return 0;
    case MEBA_CAP_BOARD_HAS_PCB107_CPLD:       return 0;
    case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:      return 0;
    case MEBA_CAP_BOARD_HAS_PCB135_CPLD:       return 0;
    case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:      return -1;
    case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:  return 0;
    case MEBA_CAP_SYNCE_CLOCK_DPLL:            return -1;
    case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:      return 0;
    case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:  return 0;
    case MEBA_CAP_ONE_PPS_INT_ID:              return 0;
    case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:      return 0;
    case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:        return 0;
    case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET: return 0;
    case MEBA_CAP_POE_BT:                      return 0;
    case MEBA_CAP_CPU_PORTS_COUNT:             return 0;
    default:                                   T_E(inst, "Unknown capability %d", cap); MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc lk_port_entry_get(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    mesa_rc             rc;
    meba_board_state_t *board = INST2BOARD(inst);

    if (port_no < board->port_cnt) {
        *entry = board->port[port_no];
        rc = MESA_RC_OK;
    } else {
        rc = MESA_RC_ERROR;
    }

    return rc;
}

static mesa_rc lk_reset(meba_inst_t inst, meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc             rc = MESA_RC_OK;

    switch (reset) {
    case MEBA_BOARD_INITIALIZE:      break;
    case MEBA_PORT_RESET:            break;
    case MEBA_PORT_RESET_POST:       break;
    case MEBA_STATUS_LED_INITIALIZE: break;
    case MEBA_PORT_LED_INITIALIZE:   break;
    case MEBA_FAN_INITIALIZE:        break;
    case MEBA_SENSOR_INITIALIZE:     break;
    case MEBA_INTERRUPT_INITIALIZE:  break;
    case MEBA_SYNCE_DPLL_INITIALIZE: break;
    case MEBA_POE_INITIALIZE:        break;
    case MEBA_PHY_INITIALIZE:
        inst->phy_devices = (mepa_device_t **)&board->phy_devices;
        inst->phy_device_cnt = board->port_cnt;
        meba_phy_driver_init(inst);
        break;
    }

    return rc;
}

meba_inst_t meba_initialize(size_t callouts_size, const meba_board_interface_t *callouts)
{
    meba_inst_t         inst;
    meba_board_state_t *board;
    int                 i;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n", sizeof(*callouts),
                callouts_size);
        return NULL;
    }

    if ((inst = meba_state_alloc(callouts,
                                 "Laika",          // Default name
                                 MESA_TARGET_P64H, // Default target
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    inst->props.target = MESA_TARGET_P64H;

    // The only board supported for now is the emulation platform named "periph1".
    // It provides 2x1G interfaces on chip port 0 and 2.
    //
    strncpy(inst->props.name, "periph1", sizeof(inst->props.name));
    board->port_cnt = 2;

    board->port = (meba_port_entry_t *)calloc(board->port_cnt, sizeof(meba_port_entry_t));
    if (board->port == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    for (i = 0; i < board->port_cnt; i++) {
        board->port[i].map.chip_port = i * 2;
        board->port[i].map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
        board->port[i].mac_if = MESA_PORT_INTERFACE_SGMII;
        board->port[i].cap = MEBA_PORT_CAP_DUMMY_PHY | MEBA_PORT_CAP_TRI_SPEED_COPPER;
    }

    inst->api.meba_capability = lk_capability;
    inst->api.meba_port_entry_get = lk_port_entry_get;
    inst->api.meba_reset = lk_reset;
    inst->api.meba_deinitialize = meba_deinitialize;

    return inst;

error_out:
    free(inst);
    return NULL;
}
