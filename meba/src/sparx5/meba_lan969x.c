// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <microchip/ethernet/board/api.h>

#include "meba_aux.h"
#include "meba_generic.h"
#include "meba_common.h"

#define STATUSLED_G_GPIO 61
#define STATUSLED_R_GPIO 61
#define VTSS_GPIOS_MAX 67
#define VTSS_MSLEEP(m) usleep((m) * 1000)

/* Local mapping table */
typedef struct {
    int32_t                chip_port;
    mesa_miim_controller_t miim_controller;
    uint8_t                miim_addr;
    mesa_port_interface_t  mac_if;
    meba_port_cap_t        cap;
    mesa_internal_bw_t     max_bw;
    uint8_t                sgpio_port;
    uint8_t                i2c_port;
    mesa_bool_t            ts_phy;
} port_map_t;

static const meba_ptp_rs422_conf_t other_rs422_conf = {
    .gpio_rs422_1588_mstoen = -1,
    .gpio_rs422_1588_slvoen = -1,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 3,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_2,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3,
    .serial_port            = "/dev/ttyAT1"
};

#define LAGUNA_CAP_10G_FDX (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_5G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH)

typedef enum {
    SFP_DETECT,
    SFP_FAULT,
    SFP_LOS
} sfp_signal_t;

static port_map_t *meba_port_map = NULL;

//---------------------------------------------------------------------------------------------------------------------------
// Chip | MII-Controller     | MII |   Default MAC IF      |   Port capabilities         |   Max core | SGPIO | I2C   | ts
// Port |                    | Addr|                       |                             |      BW    | port  | index | phy
//---------------------------------------------------------------------------------------------------------------------------

static port_map_t port_table_sunrise[] = {
    {0, MESA_MIIM_CONTROLLER_1, 0, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 0},
    {1, MESA_MIIM_CONTROLLER_1, 1, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 0},
    {2, MESA_MIIM_CONTROLLER_1, 2, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 0},
    {3, MESA_MIIM_CONTROLLER_1, 3, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 0},
    {8, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SGMII_CISCO, MEBA_PORT_CAP_SFP_1G,   MESA_BW_1G, 0, 0, 0},
};

static port_map_t port_table_pcb8398[] = {
    {0,  MESA_MIIM_CONTROLLER_0, 4,  MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {1,  MESA_MIIM_CONTROLLER_0, 5,  MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {2,  MESA_MIIM_CONTROLLER_0, 6,  MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {3,  MESA_MIIM_CONTROLLER_0, 7,  MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {4,  MESA_MIIM_CONTROLLER_0, 8,  MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {5,  MESA_MIIM_CONTROLLER_0, 9,  MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {6,  MESA_MIIM_CONTROLLER_0, 10, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {7,  MESA_MIIM_CONTROLLER_0, 11, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {8,  MESA_MIIM_CONTROLLER_0, 12, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {9,  MESA_MIIM_CONTROLLER_0, 13, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {10, MESA_MIIM_CONTROLLER_0, 14, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {11, MESA_MIIM_CONTROLLER_0, 15, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {12, MESA_MIIM_CONTROLLER_0, 16, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {13, MESA_MIIM_CONTROLLER_0, 17, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {14, MESA_MIIM_CONTROLLER_0, 18, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {15, MESA_MIIM_CONTROLLER_0, 19, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {16, MESA_MIIM_CONTROLLER_0, 20, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {17, MESA_MIIM_CONTROLLER_0, 21, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {18, MESA_MIIM_CONTROLLER_0, 22, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {19, MESA_MIIM_CONTROLLER_0, 23, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {20, MESA_MIIM_CONTROLLER_0, 24, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {21, MESA_MIIM_CONTROLLER_0, 25, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {22, MESA_MIIM_CONTROLLER_0, 26, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {23, MESA_MIIM_CONTROLLER_0, 27, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G, 0, 0, 1},
    {24, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SFI,  LAGUNA_CAP_10G_FDX,            MESA_BW_10G, 6, 0, 0},
    {25, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SFI,  LAGUNA_CAP_10G_FDX,            MESA_BW_10G, 7, 1, 0},
    {26, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SFI,  LAGUNA_CAP_10G_FDX,            MESA_BW_10G, 8, 2, 0},
    {27, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SFI,  LAGUNA_CAP_10G_FDX,            MESA_BW_10G, 9, 3, 0},
    {29, MESA_MIIM_CONTROLLER_0, 3,  MESA_PORT_INTERFACE_RGMII_TXID, MEBA_PORT_CAP_TRI_SPEED_COPPER, MESA_BW_1G,  0, 0, 0},
};

#define PCB8398_GPIO_FUNC_INFO_SIZE 8
static const mesa_gpio_func_info_t pcb8398_gpio_func_info[PCB8398_GPIO_FUNC_INFO_SIZE] = {
    {.gpio_no = VTSS_GPIOS_MAX, //MESA_GPIO_FUNC_PTP_0
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = VTSS_GPIOS_MAX, //MESA_GPIO_FUNC_PTP_1
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = VTSS_GPIOS_MAX, //MESA_GPIO_FUNC_PTP_2
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = 57,             //MESA_GPIO_FUNC_PTP_3
     .alt = MESA_GPIO_FUNC_ALT_3},
    {.gpio_no = 58,             //MESA_GPIO_FUNC_PTP_4
     .alt = MESA_GPIO_FUNC_ALT_3},
    {.gpio_no = 59,             //MESA_GPIO_FUNC_PTP_5
     .alt = MESA_GPIO_FUNC_ALT_3},
    {.gpio_no = VTSS_GPIOS_MAX, //MESA_GPIO_FUNC_PTP_6
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = VTSS_GPIOS_MAX, //MESA_GPIO_FUNC_PTP_7
     .alt = MESA_GPIO_FUNC_ALT_0},
};


static void port_entry_map(meba_port_entry_t *entry, port_map_t *map)
{
    entry->map.chip_port = map->chip_port;
    entry->map.miim_controller = map->miim_controller;
    entry->map.miim_addr = map->miim_addr;
    entry->mac_if = map->mac_if;
    entry->cap = map->cap;
    entry->map.max_bw = map->max_bw;
}

static void lan966x_init_port_table(meba_inst_t inst, int port_cnt, port_map_t *map)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t     port_no;

    /* Fill out port mapping table */
    board->port_cnt = port_cnt;
    for (port_no = 0; port_no < port_cnt; port_no++) {
        port_entry_map(&board->port[port_no].map, &map[port_no]);
        board->port[port_no].ts_phy = map[port_no].ts_phy;
        // Initialise phy base port.
        if (board->type == BOARD_TYPE_LAGUNA_PCB8398 && port_no < 24) {
            board->port[port_no].map.phy_base_port = (port_no / 4) * 4;
        }
    }
}

static mesa_rc lan969x_board_init(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t  conf;
    uint32_t gpio_no, port;

    switch (board->type) {
    case BOARD_TYPE_SUNRISE:
        return MESA_RC_OK;
    default:
        break;
    }

    /* Configure GPIOs for MIIM/MDIO/IRQ bus 0 */
    for (gpio_no = 9; gpio_no <= 10; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    /* Configure GPIO 11 as interrupt from PHYs */
    (void)mesa_gpio_mode_set(NULL, 0, 11, MESA_GPIO_IN_INT);

    /* Configure GPIO 57 as PTP.SYNC3 for the PHYs*/
    mesa_ts_ext_io_mode_t pps_mode = {MESA_TS_EXT_IO_MODE_ONE_PPS_OUTPUT, 0, 0} ;
    (void)mesa_gpio_mode_set(NULL, 0, 57, MESA_GPIO_ALT_3);
    (void)mesa_ts_external_io_mode_set(NULL, 3, &pps_mode);

    /* GPIOs for SGPIO Group 0  */
    for (gpio_no = 5; gpio_no <= 8; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    /* SGPIO group controls:
       sgpio port 0  : i2c mux
       sgpio port 1  : RS422
       sgpio port 6-9: SFP LEDs and SFP signals */
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 4;

        conf.port_conf[0].mode[0] = MESA_SGPIO_MODE_ON;
        /* MUX_SELx (I2C) is controlled by the BSP driver - do not touch */
        for (uint32_t i = 1; i < 4; i++) {
            conf.port_conf[0].mode[i] = MESA_SGPIO_MODE_NO_CHANGE;
        }
        conf.port_conf[0].mode[0] = MESA_SGPIO_MODE_ON; // POE enabled
        conf.port_conf[0].enabled = 1;

        /* Set bit 2 and 3 to high. This sets the RS422 1PPS driver output to tristate */
        conf.port_conf[1].enabled = 1;
        conf.port_conf[1].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[1].mode[3] = MESA_SGPIO_MODE_ON;

        // SGPIO Output port 6-9:
        // bit 0: LED1
        // bit 1: LED2
        // bit 2: TxDisable
        // bit 3: RateSelect

        // SGPIO Input port 6-9:
        // bit 0: LOS
        // bit 1: ModDetect
        // bit 2: TxFault

        for (port = 6; port <= 9; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_OFF; // Turn on Green SFP LED while booting
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF; // Turn on Red SFP LED while booting
        }

        (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }

    // Status LED off (application will turn on)
    gpio_no = 61;
    (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_OUT);
    (void)mesa_gpio_write(NULL, 0, gpio_no, 1);

    // GPIO 62 is used for PHY reset
    gpio_no = 62;
    (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_OUT);
    (void)mesa_gpio_write(NULL, 0, gpio_no, 0);
    (void)mesa_gpio_write(NULL, 0, gpio_no, 1);

    // MIIM frequency needs to be reduced on this board: DEVCPU_GCB:MIIM[0]:MII_CFG = 0x2ff
    (void)mesa_reg_write(NULL, 0, 0x80406e, 0x2ff);

    return MESA_RC_OK;
}

static uint32_t lan969x_capability(meba_inst_t inst, int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_POE:
            return 1;
        case MEBA_CAP_1588_CLK_ADJ_DAC:
        case MEBA_CAP_1588_REF_CLK_SEL:
        case MEBA_CAP_TEMP_SENSORS:
            return 0;
        case MEBA_CAP_BOARD_PORT_COUNT:
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            return board->port_cnt;
        case MEBA_CAP_LED_MODES:
        case MEBA_CAP_DYING_GASP:
        case MEBA_CAP_FAN_SUPPORT:
            return 0;
        case MEBA_CAP_LED_DIM_SUPPORT:
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
        case MEBA_CAP_BOARD_HAS_PCB135_CPLD:
        case MEBA_CAP_SYNCE_CLOCK_DPLL:
        case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:
        case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:
        case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:
        case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:
            return 0;
        case MEBA_CAP_ONE_PPS_INT_ID:
            return MEBA_EVENT_PTP_PIN_3;
        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:
        case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET:
        case MEBA_CAP_POE_BT:
            return 1;
        case MEBA_CAP_CPU_PORTS_COUNT:
            return 0;
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:
            if (board->type == BOARD_TYPE_LAGUNA_PCB8398) {
                meba_synce_clock_hw_id_t dpll_type;

                if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK)) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }

        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc lan969x_port_entry_get(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      meba_port_entry_t *entry)
{
    mesa_rc rc;
    meba_board_state_t *board = INST2BOARD(inst);

    T_N(inst, "Called");
    if (port_no < board->port_cnt) {
        *entry = board->port[port_no].map;
        rc = MESA_RC_OK;
    } else {
        rc = MESA_RC_ERROR;
    }
    T_N(inst, "Called(%d): rc %d - chip %d, miim bus %d, addr: %d", port_no, rc,
        entry->map.chip_port, entry->map.miim_controller, entry->map.miim_addr);
    return rc;
}


static mesa_rc lan969x_sfp_i2c_xfer(meba_inst_t inst,
                                    mesa_port_no_t port_no,
                                    mesa_bool_t write,
                                    uint8_t i2c_addr,
                                    uint8_t addr,
                                    uint8_t *data,
                                    uint8_t cnt,
                                    mesa_bool_t word_access)
{
    mesa_rc            rc = MESA_RC_ERROR;
    uint8_t            i2c_port = meba_port_map[port_no].i2c_port;

    T_N(inst, "Called");

    if (write) {    // cnt ignored
        uint8_t i2c_data[3];
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        rc = inst->iface.i2c_write(i2c_port, i2c_addr, i2c_data, 3);
    } else {
        rc = inst->iface.i2c_read(i2c_port, i2c_addr, addr, data, cnt);
    }

    T_D(inst, "i2c %s port %d - address 0x%02x:0x%02x, %d bytes return %d",
        write ? "write" : "read", i2c_port, i2c_addr, addr, cnt, rc);
    return rc;
}

static mesa_bool_t get_sfp_status(meba_inst_t inst,
                                  mesa_port_no_t port_no,
                                  mesa_sgpio_port_data_t *data,
                                  sfp_signal_t sfp)
{
    uint32_t sgpio_port = meba_port_map[port_no].sgpio_port;

    if (sgpio_port >= MESA_SGPIO_PORTS) {
        T_E(inst, "Invalid port %d, sgpio_port %d", port_no, sgpio_port);
        return false;
    }

    if (sfp == SFP_DETECT) {
        return !data[sgpio_port].value[1]; // The SFP detect signal is inverted
    } else if (sfp == SFP_FAULT) {
        return data[sgpio_port].value[2];
    } else if (sfp == SFP_LOS) {
        return data[sgpio_port].value[0];
    } else {
        T_E(inst, "Unknown signal");
    }
    return false;
}

// For backwards compatibility (use lan969x_sfp_status_get())
static mesa_rc lan969x_sfp_insertion_status_get(meba_inst_t inst, mesa_port_list_t *present)
{
    mesa_rc                rc = MESA_RC_OK;
    meba_board_state_t     *board = INST2BOARD(inst);
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];

    T_N(inst, "Called");
    mesa_port_list_clear(present);

    if ((rc = mesa_sgpio_read(NULL, 0, 0, data)) == MESA_RC_OK) {
        mesa_port_no_t port_no;
        /* The 'Module Detect' is inverted i.e. '0' means detected */
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            if (is_sfp_port(board->port[port_no].map.cap)) {
                mesa_bool_t detect = get_sfp_status(inst, port_no, data, SFP_DETECT);
                mesa_port_list_set(present, port_no, detect);
                T_N(inst, "port:%d, status:%d", port_no, detect);
            }
        }
    }
    return rc;
}

static mesa_rc lan969x_sfp_status_get(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      meba_sfp_status_t *status)
{
    mesa_rc                rc = MESA_RC_OK;
    meba_board_state_t     *board = INST2BOARD(inst);
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];
    uint8_t                sgport = meba_port_map[port_no].sgpio_port;

    if (!is_sfp_port(board->port[port_no].map.cap)) {
        return rc;
    }

    if ((rc = mesa_sgpio_read(NULL, 0, 0, data)) == MESA_RC_OK) {
        status->los      = (data[sgport].value[0] ? 1 : 0); // SFP LOS, ACTIVE_HIGH
        status->present  = (data[sgport].value[1] ? 0 : 1); // SFP MODDET, ACTIVE_LOW
        status->tx_fault = (data[sgport].value[2] ? 1 : 0); // SFP TXFAULT, ACTIVE_HIGH

    }
    return rc;
}

// Applies only to SFPs where TxDisable is enabled/disabled
static mesa_rc lan969x_port_admin_state_set(meba_inst_t inst,
                                            mesa_port_no_t port_no,
                                            const meba_port_admin_state_t *state)
{
    mesa_rc            rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t  conf;
    mesa_sgpio_mode_t  sgmode = (state->enable ? MESA_SGPIO_MODE_OFF: MESA_SGPIO_MODE_ON);
    uint8_t            sgport = meba_port_map[port_no].sgpio_port;

    if (board->type == BOARD_TYPE_SUNRISE) {
        return rc;
    }

    if (board->port[port_no].map.map.miim_controller == MESA_MIIM_CONTROLLER_NONE &&
        sgport < MESA_SGPIO_PORTS && (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK)) {
        conf.port_conf[sgport].mode[2] = sgmode; // TxDisable maps to bit 2
        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }

    return rc;
}

static mesa_rc lan969x_port_led_update(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       const mesa_port_status_t *status,
                                       const mesa_port_counters_t *counters,
                                       const meba_port_admin_state_t *state)
{
    mesa_rc            rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_status_t *old_status = &board->status[port_no];
    mesa_sgpio_conf_t  conf;
    uint8_t            sgport = meba_port_map[port_no].sgpio_port;

    if (board->type == BOARD_TYPE_SUNRISE) {
        return rc;
    }

    // Only SFP ports
    if (board->port[port_no].map.map.miim_controller != MESA_MIIM_CONTROLLER_NONE
        || sgport >= MESA_SGPIO_PORTS) {
        return rc;
    }

    if ((status->link != old_status->link || status->speed != old_status->speed) &&
        (rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
        *old_status = *status; // Save status
        conf.port_conf[sgport].mode[0] =  MESA_SGPIO_MODE_ON; // Green off */
        conf.port_conf[sgport].mode[1] =  MESA_SGPIO_MODE_ON; // Red off */

        if (status->link) {
            if (status->speed >= MESA_SPEED_1G) {
                conf.port_conf[sgport].mode[0] = MESA_SGPIO_MODE_0_ACTIVITY; // Green on/blinking */
            } else {
                conf.port_conf[sgport].mode[1] = MESA_SGPIO_MODE_0_ACTIVITY; // Red on/blinking */
            }
        }
        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc;
}


static mesa_rc lan969x_status_led_set(meba_inst_t inst,
                                      meba_led_type_t type,
                                      meba_led_color_t color)
{
    mesa_rc            rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);

    if (board->type == BOARD_TYPE_SUNRISE) {
        return MESA_RC_OK;
    }

    if (type == MEBA_LED_TYPE_FRONT && color < MEBA_LED_COLOR_COUNT) {
        T_I(inst, "LED:%d, color=%d", type, color);
        switch (color) {
            case MEBA_LED_COLOR_OFF:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, true);
                break;
            case MEBA_LED_COLOR_GREEN:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, false);
                break;
            default:
                rc = MESA_RC_ERROR;
        }
    }
    return rc;
}

static mesa_rc lan969x_reset(meba_inst_t inst, meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;

    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            lan969x_board_init(inst);
            break;
        case MEBA_PORT_RESET:
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            break;
        case MEBA_PORT_LED_INITIALIZE:
            if (board->type == BOARD_TYPE_LAGUNA_PCB8398) {
                mepa_gpio_conf_t conf = {};
                mesa_sgpio_conf_t sgconf;
                uint8_t sgport;

                if (mesa_sgpio_conf_get(NULL, 0, 0, &sgconf) == MESA_RC_OK) {
                    for (mesa_port_no_t p = 0; p < board->port_cnt; p++) {
                        if (!is_sfp_port(board->port[p].map.cap)) {
                            continue;
                        }
                        sgport = meba_port_map[p].sgpio_port;
                        // Turned LEDs off
                        sgconf.port_conf[sgport].mode[0] =  MESA_SGPIO_MODE_ON;
                        sgconf.port_conf[sgport].mode[1] =  MESA_SGPIO_MODE_ON;
                    }
                    (void)mesa_sgpio_conf_set(NULL, 0, 0, &sgconf);
                }

                for (mesa_port_no_t p = 0; p < board->port_cnt; p++) {
                    if (meba_port_map[p].mac_if != MESA_PORT_INTERFACE_QSGMII) {
                        continue;
                    }
                    conf.led_num = MEPA_LED0;
                    conf.mode = MEPA_GPIO_MODE_LED_LINK1000_ACTIVITY;
                    (void)meba_phy_gpio_mode_set(inst, p, &conf);
                    conf.led_num = MEPA_LED1;
                    conf.mode = MEPA_GPIO_MODE_LED_LINK10_100_ACTIVITY;
                    (void)meba_phy_gpio_mode_set(inst, p, &conf);
                }
            } else if (board->type == BOARD_TYPE_SUNRISE) {
                for (uint32_t port_no = 0; port_no < board->port_cnt; port_no++) {
                    if (port_no % 4 == 0 && (board->port[port_no].map.mac_if == MESA_PORT_INTERFACE_QSGMII)) {
                        if ((rc = vtss_phy_pre_reset(PHY_INST, port_no)) != MESA_RC_OK) {
                            T_E(inst, "Could not pre reset phy %d", port_no);
                        }
                    }
                }
            }
            break;
        case MEBA_PORT_RESET_POST:
            if (board->type == BOARD_TYPE_SUNRISE) {
                (void)vtss_phy_post_reset(PHY_INST, 0);
            }
            break;
        case MEBA_FAN_INITIALIZE:
            break;
        case MEBA_SENSOR_INITIALIZE:
            break;
        case MEBA_INTERRUPT_INITIALIZE:
            break;
        case MEBA_POE_INITIALIZE:
            break;
        case MEBA_PHY_INITIALIZE:
            inst->phy_devices = (mepa_device_t **)&board->phy_devices;
            inst->phy_device_cnt = board->port_cnt;
            meba_phy_driver_init(inst);
            break;
        default:
            rc = MESA_RC_ERROR;
    }
    T_D(inst, "Called - %d - Done", reset);
    return rc;
}

static mesa_rc sgpio_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    mesa_rc        rc = MESA_RC_OK;
    mesa_bool_t    sgpio_events[3][MESA_SGPIO_PORTS];
    mesa_port_no_t port_no;
    uint32_t       sgport, bit;
    int            event_detected, handled = 0;

    if (board->type == BOARD_TYPE_SUNRISE) {
        return MESA_RC_OK;
    }

    // Get event bits
    for (bit = 0; bit < 3; bit++) {
        rc = mesa_sgpio_event_poll(NULL, 0, 0, bit, sgpio_events[bit]);
        if (rc != MESA_RC_OK) {
            return rc;
        }
    }

    // Check for LOS, MODDET and TXFAULT events
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if ((sgport = meba_port_map[port_no].sgpio_port) > 0) {
            event_detected = 0;
            for (bit = 0; bit < 3; bit++) {
                if (sgpio_events[bit][sgport]) {
                    // Event detected, disable while handling it
                    (void)mesa_sgpio_event_enable(NULL, 0, 0, sgport, bit, false);
                    event_detected = 1;
                }
            }
            if (event_detected) {
                signal_notifier(MEBA_EVENT_LOS, port_no);
                handled = 1;
            }
        }
    }
    return (handled ? MESA_RC_OK : MESA_RC_ERROR);
}

// IRQ Support
static mesa_rc lan969x_event_enable(meba_inst_t inst,
                                    meba_event_t event_id,
                                    mesa_bool_t enable)
{
    mesa_rc               rc = MESA_RC_OK;
    meba_board_state_t    *board = INST2BOARD(inst);
    uint8_t               sgport;
    mesa_port_no_t        port_no;
    mesa_ptp_event_type_t ptp_event;

    if (board->type == BOARD_TYPE_SUNRISE) {
        return MESA_RC_OK;
    }

    T_I(inst, "%sable event %d", enable ? "en" : "dis", event_id);

    switch (event_id) {
    case MEBA_EVENT_SYNC:
    case MEBA_EVENT_EXT_SYNC:
    case MEBA_EVENT_EXT_1_SYNC:
    case MEBA_EVENT_CLK_ADJ:
    case MEBA_EVENT_VOE:
        return rc;    // Dummy for now

    case MEBA_EVENT_LOS:
        if (board->type == BOARD_TYPE_LAGUNA_PCB8398) {
            // bit 0: LOS
            // bit 1: ModDetect
            // bit 2: TxFault
            for (port_no = 0; port_no < board->port_cnt-1; port_no++) {
                if ((sgport = meba_port_map[port_no].sgpio_port) > 0) {
                    (void)mesa_sgpio_event_enable(NULL, 0, 0, sgport, 0, enable); // LOS
                    (void)mesa_sgpio_event_enable(NULL, 0, 0, sgport, 2, enable); // TxFault
                }
            }
            for (port_no = 0; port_no < board->port_cnt-1; port_no++) {
                if (is_phy_port(board->port[port_no].map.cap)) {
                    if ((rc = meba_phy_event_enable_set(inst, port_no, MEPA_LINK_LOS, enable)) != MESA_RC_OK) {
                        T_E(inst, "Could not enable MEPA_LINK_LOS in phy (%d)",port_no);
                    }
                }
            }
        }
        break;
    case MEBA_EVENT_FLNK:
        for (port_no = 0; port_no < board->port_cnt-1; port_no++) {
            if (is_phy_port(board->port[port_no].map.cap)) {
                if ((rc = meba_phy_event_enable_set(inst, port_no, VTSS_PHY_LINK_FFAIL_EV, enable)) != MESA_RC_OK) {
                    T_E(inst, "Could not enable VTSS_PHY_LINK_FFAIL_EV in phy (%d)",port_no);
                }
            }
        }
        break;
    case MEBA_EVENT_PTP_PIN_0:
    case MEBA_EVENT_PTP_PIN_1:
    case MEBA_EVENT_PTP_PIN_2:
    case MEBA_EVENT_PTP_PIN_3:
    case MEBA_EVENT_CLK_TSTAMP:
        ptp_event = meba_generic_ptp_source_to_event(inst, event_id);
        if ((rc = mesa_ptp_event_enable(NULL, ptp_event, enable)) != MESA_RC_OK) {
            T_E(inst, "mesa_ptp_event_enable = %d", rc);
        }
        break;

    case MEBA_EVENT_INGR_ENGINE_ERR:
    case MEBA_EVENT_INGR_RW_PREAM_ERR:
    case MEBA_EVENT_INGR_RW_FCS_ERR:
    case MEBA_EVENT_EGR_ENGINE_ERR:
    case MEBA_EVENT_EGR_RW_FCS_ERR:
    case MEBA_EVENT_EGR_TIMESTAMP_CAPTURED:
    case MEBA_EVENT_EGR_FIFO_OVERFLOW:
        {
            mepa_ts_event_t event = meba_generic_phy_ts_source_to_event(inst, event_id);
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (board->port[port_no].ts_phy &&
                    (rc = meba_phy_ts_event_set(inst, port_no, enable, event)) != MESA_RC_OK) {
                    T_E(inst, "vtss_phy_ts_event_enable_set(%d, %d, %d) = %d", port_no, enable, event, rc);
                }
            }
        }
        break;
    case MEBA_EVENT_KR:
        // Handled in kr application
        break;

    default:
        rc = MESA_RC_NOT_IMPLEMENTED; // Will occur as part of probing
        break;
    }

    return rc;
}

static mesa_rc ext0_handler(meba_inst_t inst,
                            meba_board_state_t *board,
                            meba_event_signal_t signal_notifier)
{
    int handled = 0;
    mesa_port_no_t port_no;
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (is_phy_port(board->port[port_no].map.cap)) {
            if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                T_D(inst, "port(%d) PHY IRQ handled", port_no);
                handled++;
            }
        }
    }
    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc phy_interrupt_handler(meba_inst_t inst,
                                     meba_board_state_t *board,
                                     meba_event_signal_t signal_notifier)
{
    mesa_port_no_t    port_no;
    int               handled = 0;

    for (port_no = 0; port_no < board->port_cnt-1; port_no++) {
        if (is_phy_port(board->port[port_no].map.cap)) {
            // Check for Cu Phy events
            if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                handled++;
            }
            if (meba_generic_phy_timestamp_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                handled++;
            }
        }
    }
    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}


static mesa_rc gpio_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    uint32_t gpio;
    int gpio_cnt = MESA_CAP(MESA_CAP_MISC_GPIO_CNT);
    mesa_bool_t gpio_events[gpio_cnt], gpio_state[gpio_cnt];
    mesa_rc     rc;
    int handled = 0;

    if ((rc = mesa_gpio_event_poll(NULL, 0, gpio_events)) != MESA_RC_OK) {
        T_E(inst, "mesa_gpio_event_poll: %d", rc);
        return rc;
    }

    // Disable the interrupt while handling the event
    memset(gpio_state, 0, sizeof(gpio_state));
    for (gpio = 0; gpio < gpio_cnt; gpio++) {
        if (gpio_events[gpio]) {
            T_I(inst, "Got interrupt from gpio #%u", gpio);
            (void) mesa_gpio_read(NULL, 0, gpio, &gpio_state[gpio]);
        }
    }

    switch (board->type) {
        case BOARD_TYPE_LAGUNA_PCB8398:
            if (gpio_events[2]) {
                if ((rc = mesa_gpio_event_enable(NULL, 0, 2, false)) != MESA_RC_OK) {
                    T_E(inst, "mesa_gpio_event_enable = %d", rc);
                }
                signal_notifier(MEBA_EVENT_PUSH_BUTTON, 0);
                handled++;
            }
            if (gpio_events[11]) { // Interrupt from PHYs
                if ((rc = phy_interrupt_handler(inst, board, signal_notifier)) == MESA_RC_OK) {
                    handled++;
                }
            }
            break;

        default:
            T_E(inst, "Board type (%d) not supported!", board->type);
            return MESA_RC_ERROR;
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc lan969x_irq_handler(meba_inst_t inst,
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
    case MESA_IRQ_SGPIO:
        return sgpio_handler(inst, board, signal_notifier);
    case MESA_IRQ_EXT0:
        return ext0_handler(inst, board, signal_notifier);
    case MESA_IRQ_GPIO:
        return gpio_handler(inst, board, signal_notifier);
        return MESA_RC_OK;

    default:
        break;
    }
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc lan969x_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;

    switch (chip_irq) {
    case MESA_IRQ_PTP_SYNC:
    case MESA_IRQ_PTP_RDY:
    case MESA_IRQ_SGPIO:
    case MESA_IRQ_EXT0:
    case MESA_IRQ_GPIO:
        rc = MESA_RC_OK;
        break;
    default:
        break;
    }
    return rc;
}

static mesa_rc lan969x_serdes_tap_get(meba_inst_t inst, mesa_port_no_t port_no,
                                      mesa_port_speed_t speed, mesa_port_serdes_tap_enum_t tap,
                                      uint32_t *const ret_val)
{
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc lan969x_ptp_rs422_conf_get(meba_inst_t inst, meba_ptp_rs422_conf_t *conf)
{
    T_N(inst, "Called");

    // HENRIKBTBD
    *conf = other_rs422_conf;
    return VTSS_RC_OK;
}

static mesa_rc lan969x_gpio_func_info_get(meba_inst_t inst,
                                          mesa_gpio_func_t gpio_func,  mesa_gpio_func_info_t *info)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);

    if (board->type == BOARD_TYPE_LAGUNA_PCB8398) {
        if (gpio_func < PCB8398_GPIO_FUNC_INFO_SIZE) {
            *info = pcb8398_gpio_func_info[gpio_func];
        } else {
            T_E(inst, "Invalid gpio_func %u", gpio_func);
            rc = MESA_RC_ERROR;
        }
    } else {
        memset(info, 0, sizeof(*info));
        T_E(inst, "Unknown Board Type %u", board->type);
        rc = MESA_RC_ERROR;
    }
    return rc;
}

meba_inst_t lan969x_initialize(meba_inst_t inst, const meba_board_interface_t *callouts)
{
    meba_board_state_t *board;
    int                pcb, target, pcb_var, port_cnt = 0;

    board = INST2BOARD(inst);

    // Get the board pcb type from DT
    if (meba_conf_get_hex(inst, "pcb", &pcb) != MESA_RC_OK) {
        fprintf(stderr, "Could not read pcb id\n");
        goto error_out;
    }
    // Get the target (TSN/HSN/...) from DT
    if (meba_conf_get_hex(inst, "target", &target) != MESA_RC_OK) {
        fprintf(stderr, "Could not read target\n");
        goto error_out;
    }

    // Get the port count from uboot
    if (meba_conf_get_hex(inst, "pcb_var", &pcb_var) == MESA_RC_OK) {
        port_cnt = pcb_var;
    }

    board->type = (board_type_t)pcb;
    inst->props.board_type = board->type;
    inst->props.target = target;
    board->port = (fa_port_info_t*) calloc(30, sizeof(fa_port_info_t));
    if (board->port == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }
    if (board->type == 0x8398) {
        // This board has onboard DPLL for Synce/PTP
        // Use its 25Mhz ref clock for 1588 (and Core):
        inst->props.ref_freq = MESA_CORE_REF_CLK_25MHZ;
    }

    switch (board->type) {
    case BOARD_TYPE_LAGUNA_PCB8398:
        if (port_cnt == 0) {
            port_cnt = sizeof(port_table_pcb8398)/sizeof(port_map_t); // whole table as default
        }
        lan966x_init_port_table(inst, port_cnt, port_table_pcb8398);
        meba_port_map = port_table_pcb8398;
        break;
    case BOARD_TYPE_SUNRISE:
        lan966x_init_port_table(inst, 5, port_table_sunrise);
        meba_port_map = port_table_sunrise;
        break;
    default:
        break;
    }

    T_I(inst, "Board: %s, type %d, target %4x, mux %d, %d ports", inst->props.name, board->type, inst->props.target,
        inst->props.mux_mode, board->port_cnt);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = lan969x_capability;
    inst->api.meba_port_entry_get             = lan969x_port_entry_get;
    inst->api.meba_reset                      = lan969x_reset;
    inst->api.meba_sensor_get                 = NULL;
    inst->api.meba_sfp_i2c_xfer               = lan969x_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = lan969x_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = lan969x_sfp_status_get;
    inst->api.meba_port_admin_state_set       = lan969x_port_admin_state_set;
    inst->api.meba_port_led_update            = lan969x_port_led_update;
    inst->api.meba_led_intensity_set          = NULL;
    inst->api.meba_fan_param_get              = NULL;
    inst->api.meba_fan_conf_get               = NULL;
    inst->api.meba_status_led_set             = lan969x_status_led_set;
    inst->api.meba_irq_handler                = lan969x_irq_handler;
    inst->api.meba_irq_requested              = lan969x_irq_requested;
    inst->api.meba_event_enable               = lan969x_event_enable;
    inst->api.meba_deinitialize               = NULL;
    inst->api.meba_serdes_tap_get             = lan969x_serdes_tap_get;
    inst->api.meba_ptp_rs422_conf_get         = lan969x_ptp_rs422_conf_get;
    inst->api.meba_gpio_func_info_get         = lan969x_gpio_func_info_get;
    inst->api_synce                           = meba_synce_get();
    inst->api_tod                             = meba_tod_get();
    inst->api_poe                             = meba_poe_get();
    inst->api_cpu_port                        = NULL;
    inst->api.meba_serdes_tap_get             = NULL;
    inst->api.meba_ptp_external_io_conf_get   = NULL;
    return inst;

error_out:
    free(inst);
    return NULL;
}
