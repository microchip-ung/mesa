// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <microchip/ethernet/board/api.h>
#include <microchip/ethernet/phy/api.h>

#include "meba_aux.h"

typedef enum {
    BOARD_TYPE_ADARO = 0x6813,
    BOARD_TYPE_SUNRISE = 0x6849,
    BOARD_TYPE_8PORT = 0x8290,
    BOARD_TYPE_ENDNODE = 0x8291,
    BOARD_TYPE_ENDNODE_CARRIER = 0x8309
} board_type_t;

/* Local mapping table */
typedef struct {
    int32_t                chip_port;
    mesa_miim_controller_t miim_controller;
    uint8_t                miim_addr;
    mesa_port_interface_t  mac_if;
    meba_port_cap_t        cap;
} port_map_t;

typedef meba_port_entry_t lan9668_port_info_t;

#define PORTS_MAX 8
typedef struct meba_board_state {
    board_type_t          type;
    int                   port_cnt;
    meba_port_entry_t     *entry;
    mepa_device_t         *phy_devices[PORTS_MAX];
} meba_board_state_t;

static const meba_ptp_rs422_conf_t lan9668_rs422_conf = {
    .gpio_rs422_1588_mstoen = (15<<8)+1,
    .gpio_rs422_1588_slvoen = (15<<8)+0,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 0,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_0,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3
};

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
    {4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, MEBA_PORT_CAP_NONE},
};

static port_map_t port_table_8port[] = {
    {0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {4, MESA_MIIM_CONTROLLER_0, 4, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {5, MESA_MIIM_CONTROLLER_0, 5, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {6, MESA_MIIM_CONTROLLER_0, 6, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {7, MESA_MIIM_CONTROLLER_0, 7, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},

};

static port_map_t port_table_endnode[] = {
    {0, MESA_MIIM_CONTROLLER_1, 1, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_1, 2, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, MEBA_PORT_CAP_NONE},
};

static port_map_t port_table_endnode_carrier[] = {
    {0, MESA_MIIM_CONTROLLER_1, 1, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_1, 2, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {2, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SGMII_CISCO, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT)},
    {3, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SGMII_CISCO, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT)},
    {4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, MEBA_PORT_CAP_NONE},
};

static port_map_t port_table_svb[] = {
    {0, MESA_MIIM_CONTROLLER_1, 1, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_1, 2, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {3, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SGMII_CISCO, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT)},
    {4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SGMII_CISCO, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT)},
};

static mesa_rc lan9668_adaro_init_board(meba_inst_t inst)
{
    uint32_t gpio_no;

    if (inst->props.target == 0x9662) {
        for (gpio_no = 28; gpio_no < 30; gpio_no++) {
            (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
        }
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

static void lan966x_init_port_table(meba_inst_t inst, int port_cnt, port_map_t *map)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t     port_no;

    /* Fill out port mapping table */
    board->port_cnt = port_cnt;
    for (port_no = 0; port_no < port_cnt; port_no++) {
        port_entry_map(&board->entry[port_no], &map[port_no]);
    }
}


static mesa_rc lan9668_ptp_rs422_conf_get(meba_inst_t inst,
        meba_ptp_rs422_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    //meba_board_state_t *board = INST2BOARD(inst);
    T_I(inst, "IMPLEMENTATION OF rs422_conf requires check/update to actual MASERATI hardware properties.");
    *conf = lan9668_rs422_conf;
    return rc;
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
        case MEBA_CAP_BOARD_HAS_PCB135_CPLD:
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
    meba_board_state_t *board = INST2BOARD(inst);
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
        case MEBA_POE_INITIALIZE:
            break;

        case MEBA_PHY_INITIALIZE:
            inst->phy_devices = (mepa_device_t **)&board->phy_devices;
            inst->phy_device_cnt = board->port_cnt;
            meba_phy_driver_init(inst);
            break;
    }

    return rc;
}

static mesa_rc lan9668_event_enable(meba_inst_t inst,
                                   meba_event_t event_id,
                                   mesa_bool_t enable)
{
    mesa_rc rc = MESA_RC_OK;
    T_I(inst, "%sable event %d  REQUIRE IMPLEMENTATION ", enable ? "en" : "dis", event_id);

    switch (event_id) {
    case MEBA_EVENT_SYNC:
    case MEBA_EVENT_EXT_SYNC:
    case MEBA_EVENT_EXT_1_SYNC:
    case MEBA_EVENT_CLK_ADJ:
    case MEBA_EVENT_VOE:
    case MEBA_EVENT_LOS:
    case MEBA_EVENT_KR:
    case MEBA_EVENT_FLNK: // Phy link down event
        return rc;    // Dummy for now

    default:
        return MESA_RC_NOT_IMPLEMENTED;    // Will occur as part of probing
    }

    return rc;

}


static mesa_rc sgpio_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    mesa_rc        rc;
    int            handled = 0;
    mesa_bool_t    sgpio_events[MESA_SGPIO_PORTS];
    mesa_port_no_t port_no;

    // Chip_no == 0, Group == 0 and bit == 0)
    if ((rc = mesa_sgpio_event_poll(NULL, 0, 0, 0, sgpio_events)) != MESA_RC_OK) {
        T_E(inst, "mesa_sgpio_event_poll = %d", rc);
        return rc;
    }

    // Poll SGPIO LOS from SFP ports
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc ext0_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    return  MESA_RC_ERROR;
}

static mesa_rc dev_all_handler(meba_inst_t inst,
                               meba_board_state_t *board,
                               meba_event_signal_t signal_notifier)
{
    mesa_dev_all_event_type_t  dev_all_events[MESA_CAP(MESA_CAP_PORT_CNT)];
    mesa_port_no_t port_no;
    int handled = 0;

    if (mesa_dev_all_event_poll(NULL, MESA_DEV_ALL_POLL_ALL, dev_all_events) != MESA_RC_OK) {
        T_E(inst, "mesa_dev_all_event_poll failed");
        return MESA_RC_ERROR;
    }

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (dev_all_events[port_no] & MESA_DEV_ALL_LINK_EV) {
            T_I(inst, "DEV %d intr", port_no);
            if (mesa_dev_all_event_enable(NULL, port_no, dev_all_events[port_no], false) != MESA_RC_OK) {
                T_E(inst, "mesa_dev_all_event_enable failed");
            }
            if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                T_D(inst, "port(%d) PHY IRQ handled", port_no);
                handled++;
            }
        }
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc lan9668_sfp_insertion_status_get(meba_inst_t inst,
                                               mesa_port_list_t *present)
{
    mesa_port_list_clear(present);
    return MESA_RC_OK;
}

static mesa_rc lan9668_irq_handler(meba_inst_t inst,
                               mesa_irq_t chip_irq,
                               meba_event_signal_t signal_notifier)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_I(inst, "Called - irq %d", chip_irq);

    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
            return meba_generic_ptp_handler(inst, signal_notifier);
        case MESA_IRQ_PTP_RDY:
            signal_notifier(MEBA_EVENT_CLK_TSTAMP, 0);
            return MESA_RC_OK;
        case MESA_IRQ_OAM:
            signal_notifier(MEBA_EVENT_VOE, 0);
            return MESA_RC_OK;
        case MESA_IRQ_SGPIO:
            return sgpio_handler(inst, board, signal_notifier);
        case MESA_IRQ_EXT0:
            return ext0_handler(inst, board, signal_notifier);
        case MESA_IRQ_DEV_ALL:
            return dev_all_handler(inst, board, signal_notifier);
        default:;
    }

    return MESA_RC_NOT_IMPLEMENTED;
}


static mesa_rc lan9668_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
        case MESA_IRQ_PTP_RDY:
        case MESA_IRQ_OAM:
        case MESA_IRQ_SGPIO:
        case MESA_IRQ_EXT0:
        case MESA_IRQ_DEV_ALL:
            rc = MESA_RC_OK;
        default:;
    }
    return rc;
}

meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t        inst;
    meba_board_state_t *board;
    int                pcb;

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

    // Always allocate for 8 ports
    board->entry = (lan9668_port_info_t*) calloc(8, sizeof(lan9668_port_info_t));
    if (board->entry == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    // Get board type
    if (meba_conf_get_hex(inst, "pcb", &pcb) == MESA_RC_OK) {
        board->type = (board_type_t)pcb;
    } else {
        board->type = BOARD_TYPE_ADARO;   // Default
    }

    /* Fill out port mapping table */
    inst->props.mux_mode = MESA_PORT_MUX_MODE_1;
    switch (board->type) {
    case BOARD_TYPE_ADARO:
        lan966x_init_port_table(inst, 4, port_table_adaro);
        break;
    case BOARD_TYPE_SUNRISE:
        lan966x_init_port_table(inst, 5, port_table_sunrise);
        break;
    case BOARD_TYPE_8PORT:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_0;
        lan966x_init_port_table(inst, 8, port_table_8port);
        break;
    case BOARD_TYPE_ENDNODE:
        lan966x_init_port_table(inst, 3, port_table_endnode);
        break;
    case BOARD_TYPE_ENDNODE_CARRIER:
        if (1) {
            // Fow now, use SVB
            inst->props.mux_mode = MESA_PORT_MUX_MODE_5;
            lan966x_init_port_table(inst, 4, port_table_svb);
        } else {
            lan966x_init_port_table(inst, 5, port_table_endnode_carrier);
        }
        break;
    default:
        break;
    }

    inst->props.board_type = board->type;

    T_I(inst, "Board: %s, target %4x, %d ports, mux_mode %d",
        inst->props.name, inst->props.target, board->port_cnt, inst->props.mux_mode);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = lan9668_capability;
    inst->api.meba_port_entry_get             = lan9668_port_entry_get;
    inst->api.meba_sfp_insertion_status_get   = lan9668_sfp_insertion_status_get;
    inst->api.meba_reset                      = lan9668_reset;
    inst->api.meba_irq_handler                = lan9668_irq_handler;
    inst->api.meba_irq_requested              = lan9668_irq_requested;
    inst->api.meba_event_enable               = lan9668_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get         = lan9668_ptp_rs422_conf_get;

    return inst;

error_out:
    free(inst);
    return NULL;
}
