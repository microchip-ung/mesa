// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <mscc/ethernet/board/api.h>

#include "meba_aux.h"

/* Local mapping table */
typedef struct {
    int32_t                chip_port;
    mesa_miim_controller_t miim_controller;
    uint8_t                miim_addr;
    mesa_port_interface_t  mac_if;
    meba_port_cap_t        cap;
} port_map_t;

typedef meba_port_entry_t lan9668_port_info_t;

typedef struct meba_board_state {
    int                   port_cnt;
    meba_port_entry_t     *entry;
} meba_board_state_t;

/* --------------------------- Board specific ------------------------------- */

// NB: No SFP support!
static port_map_t port_table_adaro[] = {
    {0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_GMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_GMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_GMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_GMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
};

static port_map_t port_table_sunrise[] = {
    {0, MESA_MIIM_CONTROLLER_0, 4, MESA_PORT_INTERFACE_GMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_0, 5, MESA_PORT_INTERFACE_GMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {2, MESA_MIIM_CONTROLLER_0, 6, MESA_PORT_INTERFACE_GMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {3, MESA_MIIM_CONTROLLER_0, 7, MESA_PORT_INTERFACE_GMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
};

static mesa_rc lan9668_adaro_init_board(meba_inst_t inst)
{
    uint32_t gpio_no;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 14; gpio_no < 16; gpio_no++) {
        // TODO, must be updated
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    return MESA_RC_OK;
}

static void port_entry_map(meba_port_entry_t *entry, port_map_t *map)
{
    entry->map.chip_port = map->chip_port;
    entry->map.miim_controller = map->miim_controller;
    entry->map.miim_addr = map->miim_addr;
    entry->mac_if = map->mac_if;
    entry->cap = map->cap;
}

static void lan9668_adaro_init_porttable(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t      port_no;

    /* Fill out port mapping table */
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        port_entry_map(&board->entry[port_no], &port_table_adaro[port_no]);
    }
}

static void lan9668_sunrise_init_porttable(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t      port_no;

    /* Fill out port mapping table */
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        port_entry_map(&board->entry[port_no], &port_table_sunrise[port_no]);
    }
}

/* ---------------------------   Exposed API  ------------------------------- */

static uint32_t lan9668_capability(meba_inst_t inst,
                                  int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_1588_CLK_ADJ_DAC:
        case MEBA_CAP_1588_REF_CLK_SEL:
        case MEBA_CAP_POE:
            return false;

        case MEBA_CAP_TEMP_SENSORS:
            return 0;

        case MEBA_CAP_BOARD_PORT_COUNT:
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            // On this platform port count and port map count are identical (no loop ports)
            return board->port_cnt;

        case MEBA_CAP_LED_MODES:
            return 1;    /* No alternate led mode support */

        case MEBA_CAP_DYING_GASP:
        case MEBA_CAP_FAN_SUPPORT:
        case MEBA_CAP_LED_DIM_SUPPORT:
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
            return false;

        case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:      // NOTE: Capability currently not used on lan9668. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:  // NOTE: Capability currently not used on lan9668. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_DPLL:            // NOTE: Capability currently not used on lan9668. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:      // NOTE: Capability currently not used on lan9668. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:  // NOTE: Capability currently not used on lan9668. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_ONE_PPS_INT_ID:
            return 0;

        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:        // lan9668 does not support dual DPLL mode
        case MEBA_CAP_POE_BT:
        case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET:
            return false;

        case MEBA_CAP_CPU_PORTS_COUNT:
            return 0;

        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc lan9668_port_entry_get(meba_inst_t inst,
                                     mesa_port_no_t port_no,
                                     meba_port_entry_t *entry)
{
    mesa_rc rc;
    meba_board_state_t *board = INST2BOARD(inst);
    if (port_no < board->port_cnt) {
        *entry = board->entry[port_no];
        rc = MESA_RC_OK;
    } else {
        rc = MESA_RC_ERROR;
    }
    T_N(inst, "Called(%d): rc %d - chip %d, miim bus %d, addr: %d", port_no, rc,
        entry->map.chip_port, entry->map.miim_controller, entry->map.miim_addr);
    return rc;
}

static mesa_rc lan9668_reset(meba_inst_t inst,
                            meba_reset_point_t reset)
{
    mesa_rc rc = MESA_RC_OK;

    T_I(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            rc = lan9668_adaro_init_board(inst);
            sleep(1); // Make sure PHYs are accessible
            break;

        case MEBA_PORT_RESET:
        case MEBA_PORT_RESET_POST:
        case MEBA_STATUS_LED_INITIALIZE:
        case MEBA_PORT_LED_INITIALIZE:
        case MEBA_FAN_INITIALIZE:
        case MEBA_SENSOR_INITIALIZE:
        case MEBA_INTERRUPT_INITIALIZE:
        case MEBA_SYNCE_DPLL_INITIALIZE:
            break;
    }

    return rc;
}

meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t        inst;
    meba_board_state_t *board;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate pulic state
    if ((inst = meba_state_alloc(callouts,
                                 "lan9668_adaro",
                                 MESA_TARGET_LAN9668,
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    board->port_cnt = 4;

    board->entry = (lan9668_port_info_t*) calloc(board->port_cnt, sizeof(lan9668_port_info_t));
    if (board->entry == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    /* Fill out port mapping table */
    if (inst->props.target == 0x9662) {
        lan9668_sunrise_init_porttable(inst);
    } else {
        lan9668_adaro_init_porttable(inst);
    }

    T_I(inst, "Board: %s, target %4x, %d ports, mux_mode %d",
        inst->props.name, inst->props.target, board->port_cnt, inst->props.mux_mode);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = lan9668_capability;
    inst->api.meba_port_entry_get             = lan9668_port_entry_get;
    inst->api.meba_reset                      = lan9668_reset;
    inst->api.meba_deinitialize               = meba_deinitialize;

    return inst;

error_out:
    free(inst);
    return NULL;
}
