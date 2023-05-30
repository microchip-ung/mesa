// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <microchip/ethernet/board/api.h>

#include "meba_aux.h"

#define RED   0    // NB: Red/Green reversed in board docs
#define GREEN 1    // NB: Red/Green reversed in board docs
#define LED_ON  MESA_SGPIO_MODE_OFF    // Inverse polarity
#define LED_OFF MESA_SGPIO_MODE_ON     // Inverse polarity
#define MAX_PORTS 8
/* Local mapping table */
typedef struct {
    int32_t                chip_port;
    mesa_miim_controller_t miim_controller;
    uint8_t                miim_addr;
    mesa_port_interface_t  mac_if;
    meba_port_cap_t        cap;
} port_map_t;

typedef meba_port_entry_t ocelot_port_info_t;

typedef struct meba_board_state {
    int                   port_cnt;
    meba_port_entry_t     *entry;
    mepa_device_t        *phy_devices[MAX_PORTS];
} meba_board_state_t;

/* --------------------------- Board specific ------------------------------- */

// NB: No SFP support!
static port_map_t port_table[] = {
    /*0*/{4, MESA_MIIM_CONTROLLER_1, 4, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    /*1*/{5, MESA_MIIM_CONTROLLER_1, 5, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    /*2*/{6, MESA_MIIM_CONTROLLER_1, 6, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    /*3*/{7, MESA_MIIM_CONTROLLER_1, 7, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    /*4*/{0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY)},
    /*5*/{1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY)},
    /*6*/{2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY)},
    /*7*/{3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY)},
    /*8*/{9, MESA_MIIM_CONTROLLER_1, 28, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
};

static mesa_rc ocelot_pcb121_init_board(meba_inst_t inst)
{
    mesa_rc rc;
    uint32_t gpio_no, port;
    mesa_sgpio_conf_t conf;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 14; gpio_no < 16; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    // Configure GPIOs for SGPIO
    for (gpio_no = 0; gpio_no < 2; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {

        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2; // Two bit per port

        // Port 11:0 with 2 bit per port
        for (port = 0; port < 12; port++) {
            conf.port_conf[port].enabled = true;
            conf.port_conf[port].mode[RED] = LED_OFF;
            conf.port_conf[port].mode[GREEN] = LED_OFF;
        }
        // Disable PCIe port
        conf.port_conf[9].enabled = false;

        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }

    return rc;
}

static void ocelot_pcb121_init_porttable(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t      port_no;
    /* Fill out port mapping table */
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        meba_port_entry_t *entry = &board->entry[port_no];
        entry->map.chip_port = port_table[port_no].chip_port;
        entry->map.miim_controller = port_table[port_no].miim_controller;
        entry->map.miim_addr = port_table[port_no].miim_addr;
        entry->mac_if = port_table[port_no].mac_if;
        entry->cap = port_table[port_no].cap;
    }
}

/* ---------------------------   Exposed API  ------------------------------- */

static uint32_t ocelot_capability(meba_inst_t inst,
                                  int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_1588_CLK_ADJ_DAC:
        case MEBA_CAP_1588_REF_CLK_SEL:
            return false;
        case MEBA_CAP_POE:
            return false;
        case MEBA_CAP_TEMP_SENSORS:
            return 2;
        case MEBA_CAP_BOARD_PORT_COUNT:
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            // On this platform port count and port map count are identical (no loop ports)
            return board->port_cnt;
        case MEBA_CAP_LED_MODES:
            return 1;    /* No alternate led mode support */
        case MEBA_CAP_DYING_GASP:
            return false;
        case MEBA_CAP_FAN_SUPPORT:
            return false;
        case MEBA_CAP_LED_DIM_SUPPORT:
            return false;
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
            return false;
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
            return false;
        case MEBA_CAP_BOARD_HAS_PCB135_CPLD:
            return false;
        case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:      // NOTE: Capability currently not used on Ocelot. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:  // NOTE: Capability currently not used on Ocelot. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_DPLL:            // NOTE: Capability currently not used on Ocelot. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:      // NOTE: Capability currently not used on Ocelot. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:  // NOTE: Capability currently not used on Ocelot. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_ONE_PPS_INT_ID:
            return MEBA_EVENT_PTP_PIN_2;
        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:
            return false;
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:        // Ocelot does not support dual DPLL mode
            return false;
        case MEBA_CAP_POE_BT:
            return false;
        case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET:
            return false;
        case MEBA_CAP_CPU_PORTS_COUNT:
            return 0;
        case MEBA_CAP_BOARD_PORT_POE_COUNT:
            return 0;
        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc ocelot_port_entry_get(meba_inst_t inst,
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

static mesa_rc ocelot_status_led_set(meba_inst_t inst,
                                     meba_led_type_t type,
                                     meba_led_color_t color)
{
    mesa_rc rc = MESA_RC_ERROR;
    if (type == MEBA_LED_TYPE_FRONT) {
        T_D(inst, "LED:%d, color=%d", type, color);
        mesa_sgpio_conf_t conf;
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            mesa_sgpio_mode_t mode_green, mode_red;
            switch (color) {
                case MEBA_LED_COLOR_OFF:
                    mode_green = LED_OFF;
                    mode_red = LED_OFF;
                    break;
                case MEBA_LED_COLOR_GREEN:
                    mode_green = LED_ON;
                    mode_red = LED_OFF;
                    break;
                case MEBA_LED_COLOR_RED:
                    mode_green = LED_OFF;
                    mode_red = LED_ON;
                    break;
                case MEBA_LED_COLOR_YELLOW:
                    mode_green = LED_ON;
                    mode_red = LED_ON;
                    break;
                default:
                    rc = MESA_RC_ERROR;
            }
            if (rc == MESA_RC_OK) {
                mesa_sgpio_port_conf_t *port_conf = &conf.port_conf[11];
                port_conf->mode[GREEN] = mode_green;
                port_conf->mode[RED] = mode_red;
                T_I(inst, "LED %d (chip %d) G/R=[%d,%d]", type, 11, mode_green, mode_red);
                rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
            }
        }
    }
    return rc;
}

static mesa_rc ocelot_port_led_update(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      const mesa_port_status_t *status,
                                      const mesa_port_counters_t *counters,
                                      const meba_port_admin_state_t *state)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc            rc = MESA_RC_OK;

    if (port_no < board->port_cnt && port_no < 8) {
        mesa_sgpio_conf_t conf;
        uint32_t sgpio_port = port_table[port_no].chip_port;
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            mesa_sgpio_mode_t mode_green, mode_red;
            if (status->link) {
                mode_green = LED_ON;
                if (status->speed >= MESA_SPEED_1G) {
                    /* Green only */
                    mode_red = LED_OFF;    // Red OFF
                } else {
                    /* Yellow  */
                    mode_red = mode_green;            // Red + Green => Yellow
                }
            } else {
                /* Both LEDs off */
                mode_red = LED_OFF;
                mode_green = LED_OFF;
            }

            T_I(inst, "Port %d (chip %d) G/R=[%d,%d]", port_no, sgpio_port, mode_green, mode_red);
            conf.port_conf[sgpio_port].mode[RED] = mode_red;
            conf.port_conf[sgpio_port].mode[GREEN] = mode_green;
            rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        }
    }
    return rc;
}

static mesa_rc ocelot_reset(meba_inst_t inst,
                            meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;
    mesa_port_no_t int_phy_base_port = 4, ext_phy_base_port = 0;

    T_I(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            rc = ocelot_pcb121_init_board(inst);
            sleep(1); // Make sure PHYs are accessible
            break;
        case MEBA_PORT_RESET:
            if ((rc = vtss_phy_pre_reset(PHY_INST, int_phy_base_port)) == MESA_RC_OK) { // Internal Nano PHY
                rc = vtss_phy_pre_reset(PHY_INST, ext_phy_base_port); // External Viper PHY
            }
            break;
        case MEBA_PORT_RESET_POST:
            if ((rc = vtss_phy_post_reset(PHY_INST, int_phy_base_port)) == MESA_RC_OK) { // Internal Nano PHY
                rc = vtss_phy_post_reset(PHY_INST, ext_phy_base_port); // External Viper PHY
            }
            break;
        case MEBA_STATUS_LED_INITIALIZE:
        case MEBA_PORT_LED_INITIALIZE:
        case MEBA_FAN_INITIALIZE:
            break;
        case MEBA_SENSOR_INITIALIZE:
            if ((rc = vtss_phy_chip_temp_init(PHY_INST, int_phy_base_port)) == MESA_RC_OK) { // Internal Nano PHY
                rc = vtss_phy_chip_temp_init(PHY_INST, ext_phy_base_port); // External Viper PHY
            }
            break;
        case MEBA_INTERRUPT_INITIALIZE:
        case MEBA_SYNCE_DPLL_INITIALIZE:
            break;
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
                                 "ocelot_pcb121",
                                 MESA_TARGET_7512,
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    inst->props.mux_mode = MESA_PORT_MUX_MODE_3;
    board->port_cnt = 8;

    board->entry = (ocelot_port_info_t*) calloc(board->port_cnt, sizeof(ocelot_port_info_t));
    if (board->entry == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    /* Fill out port mapping table */
    ocelot_pcb121_init_porttable(inst);

    T_I(inst, "Board: %s, target %4x, %d ports, mux_mode %d",
        inst->props.name, inst->props.target, board->port_cnt, inst->props.mux_mode);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = ocelot_capability;
    inst->api.meba_port_entry_get             = ocelot_port_entry_get;
    inst->api.meba_status_led_set             = ocelot_status_led_set;
    inst->api.meba_port_led_update            = ocelot_port_led_update;
    inst->api.meba_reset                      = ocelot_reset;
    inst->api.meba_deinitialize               = meba_deinitialize;

    return inst;

error_out:
    free(inst);
    return NULL;
}
