// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <microchip/ethernet/board/api.h>
#include <microchip/ethernet/phy/api.h>

#include "meba_aux.h"
#include "cli.h"

/** \brief Number of LAN966X PTP pins, that can be used as 1PPS or clock output/input. */
#define VTSS_TS_IO_ARRAY_SIZE       7

typedef enum {
    BOARD_TYPE_ADARO = VTSS_BOARD_LAN9668_ADARO_REF,
    BOARD_TYPE_SUNRISE = VTSS_BOARD_LAN9668_SUNRISE_REF,
    BOARD_TYPE_SVB = VTSS_BOARD_LAN9668_SVB_REF,
    BOARD_TYPE_8PORT = VTSS_BOARD_LAN9668_8PORT_REF,
    BOARD_TYPE_ENDNODE = VTSS_BOARD_LAN9668_ENDNODE_REF,
    BOARD_TYPE_ENDNODE_CARRIER = VTSS_BOARD_LAN9668_ENDNODE_CARRIER_REF,
    BOARD_TYPE_EDS2 = VTSS_BOARD_LAN9668_EDS2_REF
} board_type_t;

typedef enum {
    SLOT1_EMPTY_SLOT2_EMPTY = 0,
    SLOT1_LAN8814_SLOT2_LAN8814,
    SLOT1_LAN89x1_SLOT2_LAN8814,
    SLOT1_LAN884x_SLOT2_LAN884x,
    SLOT1_LAN89x1_SLOT2_LAN89x1,
    SLOT1_VSC8574_SLOT2_VSC8574,
    SLOT1_LAN89X1_SLOT2_VSC8574,
    SLOT1_LAN8814_SLOT2_VSC8574,
    SLOT1_LAN8842_SLOT2_EMPTY,
} eds2_phy_options_t;

/* Local mapping table */
typedef struct {
    int32_t                chip_port;
    mesa_miim_controller_t miim_controller;
    uint8_t                miim_addr;
    mesa_port_interface_t  mac_if;
    meba_port_cap_t        cap;
    mesa_bool_t            poe_support;
    int32_t                poe_port;
} port_map_t;

typedef meba_port_entry_t lan966x_port_info_t;

#define PORTS_MAX 8
typedef struct meba_board_state {
    board_type_t          type;
    uint32_t              port_cnt;
    meba_port_entry_t     *entry;
    mepa_device_t         *phy_devices[PORTS_MAX];
    mesa_port_status_t    status[PORTS_MAX];
} meba_board_state_t;

// GPIO for interrupts from external PHYs
#define GPIO_IRQ         24

// GPIO for push button
#define GPIO_PUSH_BUTTON 55

static const meba_ptp_rs422_conf_t lan966x_rs422_conf = {
    .gpio_rs422_1588_mstoen = (15 << 8) + 1,
    .gpio_rs422_1588_slvoen = (15 << 8) + 0,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 0,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_0,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3
};

/* --------------------------- Board specific ------------------------------- */
// PTP IO Events used for virtual port.
static const meba_event_t init_int_source_id[VTSS_TS_IO_ARRAY_SIZE] = {MEBA_EVENT_PTP_PIN_0, MEBA_EVENT_PTP_PIN_1, MEBA_EVENT_PTP_PIN_2, MEBA_EVENT_PTP_PIN_3, MEBA_EVENT_LAST, MEBA_EVENT_LAST, MEBA_EVENT_LAST};

static const uint32_t pin_conf_lan9668[VTSS_TS_IO_ARRAY_SIZE] = {
    (MEBA_PTP_IO_CAP_PIN_IN),
    (MEBA_PTP_IO_CAP_UNUSED),
    (MEBA_PTP_IO_CAP_UNUSED),
    (MEBA_PTP_IO_CAP_PIN_OUT),
    (MEBA_PTP_IO_CAP_UNUSED),
    (MEBA_PTP_IO_CAP_UNUSED),
    (MEBA_PTP_IO_CAP_UNUSED),
};

// NB: No SFP support!

static mesa_rc eds2_board_init(meba_inst_t inst)
{
    meba_board_state_t     *board = INST2BOARD(inst);
    mesa_sgpio_conf_t      conf;
    mesa_sgpio_port_conf_t *pc;
    uint32_t               gpio_no, port;

    T_D(inst, "board type=%d", board->type);
    if (board->type == BOARD_TYPE_EDS2) {
        for (gpio_no = 32; gpio_no < 36; gpio_no++) {
            // SGPIO signals
            (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_2);
        }
        // GPIO 28/29 are MDC/MDIO
        for (gpio_no = 28; gpio_no < 30; gpio_no++) {
            (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
        }

        // GPIO 63 is used for PHY coma mode for REV B
        gpio_no = 63;
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_OUT);
        (void)mesa_gpio_write(NULL, 0, gpio_no, 0);

        // GPIO 42 is used for delivering 1pps to PHY.
        gpio_no = 42;
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_2);

        // set default LED modes for NPI ports
        if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
            // Mode 0 is 5 Hz, two bits per port are used
            conf.bmode[0] = MESA_SGPIO_BMODE_5;
            conf.bit_count = 2;

            for (port = 0; port < 12; port++) {
                pc = &conf.port_conf[port];
                pc->enabled = (port >= 2 && port < 4); // Port 4-7 unused

                // Input port 1: SFP0_TXFAULT, SFP1_TXFAULT (Tx fault)
                // Input port 2: SFP0_LOS, SFP0_MODDET (Module detect)
                // Input port 3: SFP1_LOS, SFP1_MODDET (Module detect)
                if (port >= 2 && port < 4) {
                    pc->int_pol_high[0] = 1;
                    pc->int_pol_high[1] = 1;
                    pc->mode[0] = MESA_SGPIO_MODE_OFF;
                    pc->mode[1] = MESA_SGPIO_MODE_ON;
                }
            }
            (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
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
    entry->poe_support = map->poe_support;
    entry->poe_port = map->poe_port;
}

static void eds2_init_port_table(meba_inst_t inst, int port_cnt, port_map_t *map)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t     port_no;

    /* Fill out port mapping table */
    board->port_cnt = port_cnt;
    for (port_no = 0; port_no < port_cnt; port_no++) {
        port_entry_map(&board->entry[port_no], &map[port_no]);
        // Link phy base port for EDS2
        if (board->type == BOARD_TYPE_EDS2) {
            if (inst->props.mux_mode == MESA_PORT_MUX_MODE_0) {
                board->entry[port_no].phy_base_port = (port_no < 4) ? 0 : 4;
            } else if (inst->props.mux_mode == MESA_PORT_MUX_MODE_1) {
                if (port_no >= 4) {
                    board->entry[port_no].phy_base_port = 4;
                } else {
                    board->entry[port_no].phy_base_port = port_no;
                }
            } else {
                board->entry[port_no].phy_base_port = port_no;
            }
        } else {
            T_E(inst, "Could not assign Base port");
        }

        T_I(inst, "port_no= %d, poe_support=%d", port_no, board->entry->poe_support);
    }
}

static mesa_rc eds2_phy_addr_map(meba_inst_t inst, const int mux)
{
    eds2_phy_options_t options = (eds2_phy_options_t) mux;
    mesa_rc valid = MESA_RC_OK;

    switch (options) {
    case SLOT1_EMPTY_SLOT2_EMPTY:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_1;
        break;
    case SLOT1_LAN8814_SLOT2_LAN8814:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_0;
        break;
    case SLOT1_LAN884x_SLOT2_LAN884x:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_2;
        break;
    case SLOT1_VSC8574_SLOT2_VSC8574:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_0;
        break;
    case SLOT1_LAN8814_SLOT2_VSC8574:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_0;
        break;
    case SLOT1_LAN8842_SLOT2_EMPTY:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_1;
        break;
    default:
        valid = MESA_RC_ERROR;
        break;
    }
    return valid;
}

static void eds2_port_reorder(const int mux, port_map_t *const eds2_port_table)
{
    port_map_t tmp;

    switch (mux) {
    case SLOT1_LAN8814_SLOT2_LAN8814:
        // The ports on the EVB LAN8814 daughter card are swapped. The left down
        // port is connected to chip port 2, the left up port is connected to
        // chip port 3, right down is connected to chip port 0 and right up is
        // connected to chip port 1. So instead of having the wrong order of the
        // front ports we swap them here such to follow the logical order.
        // Here to do the change on both slots because in each slot we have a
        // lan8814
        // It would be better to remove this function and set correctly the
        // ports in eds2_port_table_fill but then I think the logic is to hard
        // to follow.
        tmp = eds2_port_table[0];
        eds2_port_table[0] = eds2_port_table[2];
        eds2_port_table[2] = tmp;
        tmp = eds2_port_table[1];
        eds2_port_table[1] = eds2_port_table[3];
        eds2_port_table[3] = tmp;
        tmp = eds2_port_table[4];
        eds2_port_table[4] = eds2_port_table[6];
        eds2_port_table[6] = tmp;
        tmp = eds2_port_table[5];
        eds2_port_table[5] = eds2_port_table[7];
        eds2_port_table[7] = tmp;
        break;
    case SLOT1_LAN8814_SLOT2_VSC8574:
        // See the comment from the previous case statement.
        tmp = eds2_port_table[0];
        eds2_port_table[0] = eds2_port_table[2];
        eds2_port_table[2] = tmp;
        tmp = eds2_port_table[1];
        eds2_port_table[1] = eds2_port_table[3];
        eds2_port_table[3] = tmp;
        break;
    default:
        break;
    }
}

static mesa_rc eds2_port_table_fill(meba_inst_t inst, uint32_t *const port_cnt, const int mux, port_map_t *const eds2_port_table)
{
    memset(eds2_port_table, 0, 8 * sizeof(port_map_t));
    if (eds2_phy_addr_map(inst, mux) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }

    switch (mux) {
    case SLOT1_EMPTY_SLOT2_EMPTY:
        // Even that both slots are empty the ports that are on the EDS2 board
        // are in used, therefore the port_cnt has a value of 2.
        *port_cnt = 2;
        for (int i = 0; i < *port_cnt; ++i) {
            eds2_port_table[i].chip_port = i;
            eds2_port_table[i].poe_port = i;
            eds2_port_table[i].miim_controller = MESA_MIIM_CONTROLLER_1;
            eds2_port_table[i].mac_if = MESA_PORT_INTERFACE_SGMII;
            eds2_port_table[i].miim_addr = i == 0 ? 1 : 2;
            eds2_port_table[i].poe_support = 1;
            eds2_port_table[i].cap = MEBA_PORT_CAP_COPPER |
                                     MEBA_PORT_CAP_TRI_SPEED;
        }
        break;
    case SLOT1_LAN8814_SLOT2_LAN8814:
        *port_cnt = 8;
        for (int i = 0; i < *port_cnt; ++i) {
            eds2_port_table[i].chip_port = i;
            eds2_port_table[i].poe_port = i;
            eds2_port_table[i].miim_controller = MESA_MIIM_CONTROLLER_0;
            eds2_port_table[i].mac_if = MESA_PORT_INTERFACE_QSGMII;
            eds2_port_table[i].miim_addr = ((i < 4) ? 7 : 15) + (i % 4);
            eds2_port_table[i].poe_support = 1;
            eds2_port_table[i].cap = MEBA_PORT_CAP_COPPER |
                                     MEBA_PORT_CAP_TRI_SPEED |
                                     MEBA_PORT_CAP_SERDES_TX_INVERT;
        }
        break;
    case SLOT1_LAN884x_SLOT2_LAN884x:
        // Also the ports found on EDS2 board are used in this case. And each
        // LAN884X is a single PHY therefore the port_cnt is 4.
        *port_cnt = 4;
        for (int i = 0; i < *port_cnt; ++i) {
            eds2_port_table[i].chip_port = i;
            eds2_port_table[i].poe_port = i;
            eds2_port_table[i].miim_controller = (i < 2) ? MESA_MIIM_CONTROLLER_1 : MESA_MIIM_CONTROLLER_0;
            eds2_port_table[i].mac_if = (i < 2) ? MESA_PORT_INTERFACE_SGMII : MESA_PORT_INTERFACE_RGMII;
            eds2_port_table[i].miim_addr = (i < 2) ? (i + 1) : (i == 2) ? 1 : 3;
            eds2_port_table[i].poe_support = 1;
            eds2_port_table[i].cap = MEBA_PORT_CAP_COPPER |
                                     MEBA_PORT_CAP_TRI_SPEED;
        }
        break;
    case SLOT1_VSC8574_SLOT2_VSC8574:
        *port_cnt = 8;
        for (int i = 0; i < *port_cnt; ++i) {
            eds2_port_table[i].chip_port = i;
            eds2_port_table[i].poe_port = i;
            eds2_port_table[i].miim_controller = MESA_MIIM_CONTROLLER_0;
            eds2_port_table[i].mac_if = MESA_PORT_INTERFACE_QSGMII;
            eds2_port_table[i].miim_addr = ((i < 4) ? 16 : 20) + (i % 4);
            eds2_port_table[i].poe_support = 1;
            eds2_port_table[i].cap = MEBA_PORT_CAP_COPPER |
                                     MEBA_PORT_CAP_TRI_SPEED;
        }
        break;
    case SLOT1_LAN8814_SLOT2_VSC8574:
        *port_cnt = 8;
        for (int i = 0; i < *port_cnt; ++i) {
            eds2_port_table[i].chip_port = i;
            eds2_port_table[i].poe_port = i;
            eds2_port_table[i].miim_controller = MESA_MIIM_CONTROLLER_0;
            eds2_port_table[i].mac_if = MESA_PORT_INTERFACE_QSGMII;
            eds2_port_table[i].miim_addr = ((i < 4) ? 7 : 20) + (i % 4);
            eds2_port_table[i].poe_support = 1;
            eds2_port_table[i].cap = MEBA_PORT_CAP_COPPER |
                                     MEBA_PORT_CAP_TRI_SPEED |
                                     (i < 4) ? MEBA_PORT_CAP_SERDES_TX_INVERT : 0;
        }
        break;
    case SLOT1_LAN8842_SLOT2_EMPTY:
        *port_cnt = 3;
        for (int i = 0; i < *port_cnt; ++i) {
            eds2_port_table[i].chip_port = (i < 2) ? i : 3;
            eds2_port_table[i].poe_port = i;
            eds2_port_table[i].miim_controller = (i < 2) ? MESA_MIIM_CONTROLLER_1 : MESA_MIIM_CONTROLLER_0;
            eds2_port_table[i].mac_if = MESA_PORT_INTERFACE_SGMII;
            eds2_port_table[i].miim_addr = (i < 2) ? (i + 1) : 0;
            eds2_port_table[i].poe_support = 1;
            eds2_port_table[i].cap = MEBA_PORT_CAP_COPPER |
                                     MEBA_PORT_CAP_TRI_SPEED;
        }
        break;
    }

    eds2_port_reorder(mux, eds2_port_table);

    for (int i = 0; i < *port_cnt; ++i) {
        T_D(inst, " eds2_port_table[%d]:%d, MAC_IF:%d, miim_addr:%d", i, eds2_port_table[i].chip_port, eds2_port_table[i].mac_if, eds2_port_table[i].miim_addr);
    }

    return MESA_RC_OK;
}

static mesa_rc eds2_ptp_rs422_conf_get(meba_inst_t inst,
                                       meba_ptp_rs422_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    //meba_board_state_t *board = INST2BOARD(inst);
    T_I(inst, "IMPLEMENTATION OF rs422_conf requires check/update to actual MASERATI hardware properties.");
    *conf = lan966x_rs422_conf;
    return rc;
}

static mesa_rc eds2_ptp_external_io_conf_get(meba_inst_t inst, uint32_t io_pin, meba_ptp_io_cap_t *const board_assignment, meba_event_t *const source_id)
{
    meba_board_state_t *board = INST2BOARD(inst);

    if (io_pin >= VTSS_TS_IO_ARRAY_SIZE) {
        return MESA_RC_ERROR;
    }
    if (board->type == BOARD_TYPE_8PORT) {
        *board_assignment = pin_conf_lan9668[io_pin];
    }
    *source_id = init_int_source_id[io_pin];
    return MESA_RC_OK;
}

/* ---------------------------   Exposed API  ------------------------------- */

static uint32_t eds2_capability(meba_inst_t inst, int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
    case MEBA_CAP_1588_CLK_ADJ_DAC:
    case MEBA_CAP_1588_REF_CLK_SEL:
        return false;

    case MEBA_CAP_POE:
        return true;

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

    case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:      // NOTE: Capability currently not used on lan966x. Therefore, it has been set to -1
        return -1;
    case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:  // NOTE: Capability currently not used on lan966x. Therefore, it has been set to 0
        return 0;
    case MEBA_CAP_SYNCE_CLOCK_DPLL:            // NOTE: Capability currently not used on lan966x. Therefore, it has been set to -1
        return -1;
    case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:      // NOTE: Capability currently not used on lan966x. Therefore, it has been set to 0
        return 0;
    case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:  // NOTE: Capability currently not used on lan966x. Therefore, it has been set to 0
        return 0;
    case MEBA_CAP_ONE_PPS_INT_ID:
        return MEBA_EVENT_PTP_PIN_3;

    case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:
        return 0;
    case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:
        if (board->type == BOARD_TYPE_EDS2) {
            meba_synce_clock_hw_id_t dpll_type;

            if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK) && (dpll_type != MEBA_SYNCE_CLOCK_HW_NONE)) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }

    case MEBA_CAP_POE_BT:
        return true;

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

static mesa_rc eds2_port_entry_get(meba_inst_t inst,
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

static mesa_rc eds2_reset(meba_inst_t inst,
                          meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;

    T_D(inst, "Called - %d", reset);
    switch (reset) {
    case MEBA_BOARD_INITIALIZE:
        rc = eds2_board_init(inst);
        break;

    case MEBA_PORT_LED_INITIALIZE:
        mesa_port_no_t   port_no;
        mepa_gpio_conf_t conf;

        conf.gpio_no = 17;
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            conf.led_num = MEPA_LED0;
            conf.mode = MEPA_GPIO_MODE_LED_LINK10_100_ACTIVITY;
            (void)meba_phy_gpio_mode_set(inst, port_no, &conf);
            conf.led_num = MEPA_LED1;
            conf.mode = MEPA_GPIO_MODE_LED_LINK1000_ACTIVITY;
            (void)meba_phy_gpio_mode_set(inst, port_no, &conf);
        }
        break;

    case MEBA_PORT_RESET:
    case MEBA_PORT_RESET_POST:
    case MEBA_STATUS_LED_INITIALIZE:
    case MEBA_FAN_INITIALIZE:
    case MEBA_SENSOR_INITIALIZE:
    case MEBA_SYNCE_DPLL_INITIALIZE:
    case MEBA_POE_INITIALIZE:
        break;
    case MEBA_INTERRUPT_INITIALIZE:
        // GPIO 24 is IRQ from PHYs
        (void)mesa_gpio_mode_set(NULL, 0, GPIO_IRQ, MESA_GPIO_ALT_4);
        (void)mesa_gpio_event_enable(NULL, 0, GPIO_IRQ, true);
        break;
    case MEBA_PHY_INITIALIZE:
        inst->phy_devices = (mepa_device_t **)&board->phy_devices;
        inst->phy_device_cnt = board->port_cnt;
        meba_phy_driver_init(inst);
        break;
    case MEBA_ENTRY_PHY_SET:
        break;
    }

    return rc;
}

static mesa_rc eds2_sfp_i2c_xfer(meba_inst_t inst,
                                 mesa_port_no_t port_no,
                                 mesa_bool_t write,
                                 uint8_t i2c_addr,
                                 uint8_t addr,
                                 uint8_t *data,
                                 uint8_t cnt,
                                 mesa_bool_t word_access)
{
    mesa_rc rc;
    uint8_t i2c_data[3];

    T_N(inst, "Called");
    if (write) { // cnt ignored
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        rc = inst->iface.i2c_write(port_no, i2c_addr, i2c_data, 3);
    } else {
        rc = inst->iface.i2c_read(port_no, i2c_addr, addr, data, cnt);
    }
    return rc;
}

static mesa_rc eds2_sfp_insertion_status_get(meba_inst_t inst,
                                             mesa_port_list_t *present)
{
    mesa_rc                rc = MESA_RC_OK;
    meba_board_state_t     *board = INST2BOARD(inst);
    mesa_port_no_t         port_no;
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];

    mesa_port_list_clear(present);
    if (board->type == BOARD_TYPE_ENDNODE_CARRIER &&
        (rc = mesa_sgpio_read(NULL, 0, 0, data)) == MESA_RC_OK) {
        for (port_no = 2; port_no < 4; port_no++) {
            // SFP MODDET at bit 1
            mesa_port_list_set(present, port_no, data[port_no].value[1] ? 0 : 1);
        }
    }
    return rc;
}

static mesa_rc eds2_sfp_status_get(meba_inst_t inst,
                                   mesa_port_no_t port_no,
                                   meba_sfp_status_t *status)
{
    mesa_rc                rc = MESA_RC_OK;
    meba_board_state_t     *board = INST2BOARD(inst);
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];

    memset(status, 0, sizeof(*status));
    if (board->type == BOARD_TYPE_ENDNODE_CARRIER &&
        (port_no == 2 || port_no == 3) &&
        (rc = mesa_sgpio_read(NULL, 0, 0, data)) == MESA_RC_OK) {
        status->los      = (data[port_no].value[0] ? 0 : 1);     // SFP LOS at bit 0
        status->present  = (data[port_no].value[1] ? 0 : 1);     // SFP MODDET at bit 1
        status->tx_fault = (data[1].value[port_no - 2] ? 0 : 1); // SFP TXFAULT at port 1, bit 0/1
    }
    return rc;
}

static mesa_rc eds2_port_admin_state_set(meba_inst_t inst,
                                         mesa_port_no_t port_no,
                                         const meba_port_admin_state_t *state)
{
    mesa_rc            rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t  conf;
    mesa_sgpio_mode_t  mode;

    if (board->type == BOARD_TYPE_ENDNODE_CARRIER &&
        (port_no == 2 || port_no == 3) &&
        (rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
        mode = (state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
        conf.port_conf[10].mode[port_no - 2] = mode; // SFP TXEN at port 10, bit 0/1
        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc;
}

static mesa_rc sgpio_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    mesa_rc        rc = MESA_RC_OK;
    mesa_bool_t    sgpio_events[2][MESA_SGPIO_PORTS];
    mesa_port_no_t port_no;
    uint32_t       i, port, bit;
    int            event_detected, handled = 0;

    if (board->type != BOARD_TYPE_ENDNODE_CARRIER) {
        return rc;
    }

    // Get event bits 0-1
    for (bit = 0; bit < 2; bit++) {
        rc = mesa_sgpio_event_poll(NULL, 0, 0, bit, sgpio_events[bit]);
        if (rc != MESA_RC_OK) {
            return rc;
        }
    }

    // Check for LOS, MODDET and TXFAULT events
    for (port_no = 2; port_no < 4; port_no++) {
        event_detected = 0;
        for (i = 0; i < 3; i++) {
            if (i == 2) {
                // TXFAULT at port 1, bit 0/1
                port = 1;
                bit = (port_no - 2);
            } else {
                // LOS/MODDET at bit 0/1
                port = port_no;
                bit = i;
            }
            if (sgpio_events[bit][port]) {
                // Event detected, disable while handling it
                (void)mesa_sgpio_event_enable(NULL, 0, 0, port, bit, false);
                event_detected = 1;
            }
        }
        if (event_detected) {
            signal_notifier(MEBA_EVENT_LOS, port_no);
            handled = 1;
        }
    }
    return (handled ? MESA_RC_OK : MESA_RC_ERROR);
}

// Read the lines of the GPIO_IRQ and GPIO_PUSH_BUTTON. If the line is low, it
// means that, that GPIO is still active. In that case it is required to redo
// the handler of the gpio so the line will become inactive.
// Change the logic of the phy and button variables, so if the physical line is
// low(active) then phy will have a value of true, if the physical line is
// high(not active), then phy will have a value of false. Do this because the
// function mesa_gpio_event_poll, will set a value of true if there was an
// event. In this way it is possible the OR the result from
// here(gpio_handler_active) with the result from mesa_gpio_event_poll.
// The reason of doing all this is because GPIO controller can detect only if
// there are any changes in the GPIO line and not if line is low or high. So in
// case while we extract the timestamps from PHY3, PHY0 will get some timestamp
// in the FIFO so it would also active GPIO line. So in this case we will never
// an interrupt. But we can read that the line is still active so in that case
// call again the procedure to clear the interrupt lines.
static mesa_rc gpio_handler_active(mesa_bool_t *button, mesa_bool_t *phy)
{
    mesa_gpio_read(NULL, 0, GPIO_IRQ, phy);
    mesa_gpio_read(NULL, 0, GPIO_PUSH_BUTTON, button);

    *phy = !(*phy);
    *button = !(*button);

    return *phy == true || *button == true ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc gpio_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    int            handled = 0;
    mesa_bool_t    gpio_events[100];
    mesa_port_no_t port_no;
    mesa_bool_t    button = 0;
    mesa_bool_t    phy = 0;
repeat_handler:
    if (mesa_gpio_event_poll(NULL, 0, gpio_events) == MESA_RC_OK) {
        // Merge the value from event_poll with the value from handler_active,
        // If any of this is active, it means that the line is active
        gpio_events[GPIO_PUSH_BUTTON] |= button;
        gpio_events[GPIO_IRQ] |= phy;

        if (gpio_events[GPIO_PUSH_BUTTON]) {
            (void)mesa_gpio_event_enable(NULL, 0, GPIO_PUSH_BUTTON, false);
            signal_notifier(MEBA_EVENT_PUSH_BUTTON, 0);
            handled = 1;
        }
        if (gpio_events[GPIO_IRQ]) {
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                (void)meba_generic_phy_event_check(inst, port_no, signal_notifier);
            }
            handled = 1;
        }
        // Check the timestamp events.
        if (gpio_events[GPIO_IRQ]) {
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (meba_generic_phy_timestamp_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                    handled = 1;
                }
            }
        }
    }

    // If the GPIO line is still active at this point, it is required to
    // reiterate over all the devices and see why they are polling the line.
    if (gpio_handler_active(&button, &phy) == MESA_RC_OK) {
        goto repeat_handler;
    }

    return (handled ? MESA_RC_OK : MESA_RC_ERROR);
}

static mesa_rc ext0_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    return  MESA_RC_ERROR;
}

static mesa_rc cu_phy_handler(meba_inst_t inst, meba_board_state_t *board,
                              mesa_irq_t irq, meba_event_signal_t signal_notifier)
{
    return meba_generic_phy_event_check(inst, irq - MESA_IRQ_CU_PHY_0, signal_notifier);
}

static mesa_rc eds2_irq_handler(meba_inst_t inst,
                                mesa_irq_t chip_irq,
                                meba_event_signal_t signal_notifier)
{
    meba_board_state_t *board = INST2BOARD(inst);

    T_D(inst, "Called - irq %d", chip_irq);
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
    case MESA_IRQ_GPIO:
        return gpio_handler(inst, board, signal_notifier);
    case MESA_IRQ_PUSH_BUTTON:
        signal_notifier(MEBA_EVENT_PUSH_BUTTON, 0);
        return MESA_RC_OK;
    case MESA_IRQ_EXT0:
        return ext0_handler(inst, board, signal_notifier);
    case MESA_IRQ_CU_PHY_0:
    case MESA_IRQ_CU_PHY_1:
        T_I(inst, "CU_PHY");
        return cu_phy_handler(inst, board, chip_irq, signal_notifier);
    default:
        break;
    }
    return MESA_RC_NOT_IMPLEMENTED;
}


static mesa_rc eds2_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;

    switch (chip_irq) {
    case MESA_IRQ_PTP_SYNC:
    case MESA_IRQ_PTP_RDY:
    case MESA_IRQ_OAM:
    case MESA_IRQ_SGPIO:
    case MESA_IRQ_GPIO:
    case MESA_IRQ_PUSH_BUTTON:
    case MESA_IRQ_EXT0:
    case MESA_IRQ_CU_PHY_0:
    case MESA_IRQ_CU_PHY_1:
        rc = MESA_RC_OK;
        break;
    default:
        break;
    }
    return rc;
}

static mesa_rc eds2_event_enable(meba_inst_t inst,
                                 meba_event_t event_id,
                                 mesa_bool_t enable)
{
    mesa_rc               rc = MESA_RC_OK;
    meba_board_state_t    *board = INST2BOARD(inst);
    mesa_port_no_t        port_no;
    mesa_ptp_event_type_t ptp_event;

    switch (event_id) {
    case MEBA_EVENT_SYNC:
    case MEBA_EVENT_EXT_SYNC:
    case MEBA_EVENT_EXT_1_SYNC:
    case MEBA_EVENT_CLK_ADJ:
    case MEBA_EVENT_VOE:
        break;
    case MEBA_EVENT_LOS:
        T_D(inst, "Enable events for MEBA_EVENT_LOS");
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            if (is_phy_port(board->entry[port_no].cap)) {
                T_D(inst, "Enable event MEPA_LINK_LOS for port %d", port_no);
                if ((rc = meba_phy_event_enable_set(inst, port_no, MEPA_LINK_LOS, TRUE)) != MESA_RC_OK) {
                    T_E(inst, "Event MEPA_LINK_LOS Set is failed for port:%d", port_no);
                }
            }
        }
        break;
    case MEBA_EVENT_FLNK:
        T_D(inst, "Enable events for MEBA_EVENT_FLNK (%d ports)", board->port_cnt);
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            if (is_phy_port(board->entry[port_no].cap)) {
                T_D(inst, "Enable event MEBA_EVENT_FLNK for port %d", port_no);
                if ((rc = meba_phy_event_enable_set(inst, port_no, VTSS_PHY_LINK_FFAIL_EV, enable)) != MESA_RC_OK) {
                    T_E(inst, "Event MEBA_EVENT_FLINK Set is failed for port:%d", port_no);
                }
            }
        }
        break;
    case MEBA_EVENT_PUSH_BUTTON:
        T_D(inst, "Enable Reset GPIO PUSH button interrupt");
        rc = mesa_gpio_event_enable(NULL, 0, GPIO_PUSH_BUTTON, enable);
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
        mepa_ts_event_t event = meba_generic_phy_ts_source_to_event(inst, event_id);
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            // Get the PHY capabilities and if it doesn't support timestamping
            // then don't enable events
            if (meba_capability(inst, port_no, MEPA_CAP_TS_GEN_1) == 0 &&
                meba_capability(inst, port_no, MEPA_CAP_TS_GEN_2) == 0 &&
                meba_capability(inst, port_no, MEPA_CAP_TS_GEN_3) == 0) {
                continue;
            }

            if ((rc = meba_phy_ts_event_set(inst, port_no, enable, event)) != MESA_RC_OK) {
                T_E(inst, "vtss_phy_ts_event_enable_set(%d, %d, %d) = %d", port_no, enable, event, rc);
            }
        }
        break;
    default:
        rc = MESA_RC_NOT_IMPLEMENTED; // Will occur as part of probing
        break;
    }
    return rc;
}

meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t        inst;
    meba_board_state_t *board;
    int                pcb;
    int                mux_mode = 0;
    port_map_t         eds2_port_table[8];

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate pulic state
    if ((inst = meba_state_alloc(callouts,
                                 "EDS2_lan9668",
                                 MESA_TARGET_LAN9668,
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    // Always allocate for 8 ports
    board->entry = (lan966x_port_info_t *) calloc(8, sizeof(lan966x_port_info_t));
    if (board->entry == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    // Get board type
    if (meba_conf_get_hex(inst, "pcb", &pcb) == MESA_RC_OK) {
        board->type = (board_type_t)pcb;
    }
    // Get mux_mode
    if (meba_conf_get_hex(inst, "mux_mode", &mux_mode) != MESA_RC_OK) {
        T_D(inst, "Using default mux_mode %d", mux_mode);
    }
    T_D(inst, "board type=%d, mux_mode %d", board->type, mux_mode);

    if (eds2_port_table_fill(inst, &board->port_cnt, mux_mode, eds2_port_table) != MESA_RC_OK) {
        fprintf(stderr, "Port table fill failure\n");
        goto error_out;
    }
    eds2_init_port_table(inst, board->port_cnt, eds2_port_table);
    inst->props.board_type = board->type;

    T_I(inst, "Board: %s, target %4x, %d ports, mux_mode %d",
        inst->props.name, inst->props.target, board->port_cnt, inst->props.mux_mode);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = eds2_capability;
    inst->api.meba_port_entry_get             = eds2_port_entry_get;
    inst->api.meba_reset                      = eds2_reset;
    inst->api.meba_sfp_i2c_xfer               = eds2_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = eds2_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = eds2_sfp_status_get;
    inst->api.meba_port_admin_state_set       = eds2_port_admin_state_set;
    inst->api.meba_irq_handler                = eds2_irq_handler;
    inst->api.meba_irq_requested              = eds2_irq_requested;
    inst->api.meba_event_enable               = eds2_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get         = eds2_ptp_rs422_conf_get;
    inst->api_synce                           = meba_synce_get();
    inst->api_tod                             = meba_tod_get();
    inst->api.meba_ptp_external_io_conf_get   = eds2_ptp_external_io_conf_get;
    inst->api_poe = meba_poe_get();

    return inst;

error_out:
    free(inst);
    return NULL;
}

