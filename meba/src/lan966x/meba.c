// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <microchip/ethernet/board/api.h>
#include <microchip/ethernet/phy/api.h>

#include "meba_aux.h"

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

/* Local mapping table */
typedef struct {
    int32_t                chip_port;
    mesa_miim_controller_t miim_controller;
    uint8_t                miim_addr;
    mesa_port_interface_t  mac_if;
    meba_port_cap_t        cap;
} port_map_t;

typedef meba_port_entry_t lan966x_port_info_t;

#define PORTS_MAX 8
typedef struct meba_board_state {
    board_type_t          type;
    int                   port_cnt;
    meba_port_entry_t     *entry;
    mepa_device_t         *phy_devices[PORTS_MAX];
    mesa_port_status_t    status[PORTS_MAX];
} meba_board_state_t;

// GPIO for interrupts from external PHYs
#define GPIO_IRQ         24

// GPIO for push button
#define GPIO_PUSH_BUTTON 55

static const meba_ptp_rs422_conf_t lan966x_rs422_conf = {
    .gpio_rs422_1588_mstoen = (15<<8)+1,
    .gpio_rs422_1588_slvoen = (15<<8)+0,
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
    // Front port view:
    // 3 1 7 5
    // 2 0 6 4
    {2, MESA_MIIM_CONTROLLER_0,  9, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {3, MESA_MIIM_CONTROLLER_0, 10, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {0, MESA_MIIM_CONTROLLER_0,  7, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_0,  8, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {6, MESA_MIIM_CONTROLLER_0, 17, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {7, MESA_MIIM_CONTROLLER_0, 18, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {4, MESA_MIIM_CONTROLLER_0, 15, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {5, MESA_MIIM_CONTROLLER_0, 16, MESA_PORT_INTERFACE_QSGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
};

static port_map_t port_table_endnode[] = {
    {0, MESA_MIIM_CONTROLLER_1, 1, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_1, 2, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, MEBA_PORT_CAP_NONE},
};

#define CAP_SFP (MEBA_PORT_CAP_SFP_2_5G - MEBA_PORT_CAP_100M_FDX)

static port_map_t port_table_endnode_carrier[] = {
    {0, MESA_MIIM_CONTROLLER_1, 1, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_1, 2, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {2, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, CAP_SFP | MEBA_PORT_CAP_SFP_SD_HIGH},
    {3, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, CAP_SFP | MEBA_PORT_CAP_SFP_SD_HIGH},
    {4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, MEBA_PORT_CAP_NONE},
};

static port_map_t port_table_svb[] = {
    {0, MESA_MIIM_CONTROLLER_1, 1, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {1, MESA_MIIM_CONTROLLER_1, 2, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
    {3, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SGMII_CISCO, CAP_SFP | MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT},
    {4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SGMII_CISCO, CAP_SFP | MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT},
};

static mesa_rc lan966x_board_init(meba_inst_t inst)
{
    meba_board_state_t     *board = INST2BOARD(inst);
    mesa_sgpio_conf_t      conf;
    mesa_sgpio_port_conf_t *pc;
    uint32_t               gpio_no, port;

    switch (board->type) {
    case BOARD_TYPE_SUNRISE:
        for (gpio_no = 28; gpio_no < 30; gpio_no++) {
            (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
        }
        sleep(1); // Make sure PHYs are accessible
        break;
    case BOARD_TYPE_ENDNODE:
    case BOARD_TYPE_ENDNODE_CARRIER:
        for (gpio_no = 32; gpio_no < 36; gpio_no++) {
            // SGPIO signals
            (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_2);
        }
        if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
            // Mode 0 is 5 Hz, two bits per port are used
            conf.bmode[0] = MESA_SGPIO_BMODE_5;
            conf.bit_count = 2;

            for (port = 0; port < 12; port++) {
                pc = &conf.port_conf[port];
                pc->enabled = (port < 4 || port > 7); // Port 4-7 unused

                // Input port 1: SFP0_TXFAULT, SFP1_TXFAULT (Tx fault)
                // Input port 2: SFP0_LOS, SFP0_MODDET (Module detect)
                // Input port 3: SFP1_LOS, SFP1_MODDET (Module detect)
                if (port > 0 && port < 4) {
                    pc->int_pol_high[0] = 1;
                    pc->int_pol_high[1] = 1;
                }

                // Output port  0: P0_GRN, P0_YEL (LED control)
                // Output port  1: P1_GRN, P1_YEL (LED control)
                // Output port  2: SFP0_GR, SFP0_RD (LED control), S0_BLU/S0_GRN (Endnode)
                // Output port  3: SFP1_GR, SFP1_RD (LED control), S1_BLU/S1_GRN (Endnode)
                // Output port  8: SFP0_RS0, SFP0_RS1 (Rate select)
                // Output port  9: SFP1_RS0, SFP1_RS1 (Rate select)
                // Output port 10: SFP0_TXEN, SFP1_TXEN (Tx enable)
                // Output port 11: SFP0_SCKEN, SFP1_SCKEN (I2C clock select)
                if (port < 2) {
                    // Port 0/1 LED control, turn green on and yellow off while booting
                    pc->mode[0] = MESA_SGPIO_MODE_OFF;
                    pc->mode[1] = MESA_SGPIO_MODE_ON;
                } else if (port < 4) {
                    // Port 2/3 LED control, turn green on and red off while booting
                    // Endnode: Turn blue/green off (Carrier SFP ports not present)
                    pc->mode[0] = (board->type == BOARD_TYPE_ENDNODE ?
                                   MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
                    pc->mode[1] = MESA_SGPIO_MODE_ON;
                } else if (port == 8 || port == 9) {
                    // Rate select
                    pc->mode[0] = MESA_SGPIO_MODE_ON;
                    pc->mode[1] = MESA_SGPIO_MODE_ON;
                }
            }
            (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        }
        break;
    case BOARD_TYPE_8PORT:
        // GPIO 24 is IRQ from PHYs
        (void)mesa_gpio_mode_set(NULL, 0, GPIO_IRQ, MESA_GPIO_ALT_4);
        (void)mesa_gpio_event_enable(NULL, 0, GPIO_IRQ, true);

        // GPIO 28/29 are MDC/MDIO
        for (gpio_no = 28; gpio_no < 30; gpio_no++) {
            (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
        }

        // GPIO 53 is used for PHY reset
        gpio_no = 53;
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_OUT);
        (void)mesa_gpio_write(NULL, 0, gpio_no, 0);
        (void)mesa_gpio_write(NULL, 0, gpio_no, 1);
        (void)mesa_gpio_write(NULL, 0, gpio_no, 0);
        (void)mesa_gpio_write(NULL, 0, gpio_no, 1);

        // GPIO 60 is used for PHY coma mode for REV B
        gpio_no = 60;
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_OUT);
        (void)mesa_gpio_write(NULL, 0, gpio_no, 0);

        // GPIO 39 is used for delivering 1pps to PHY.
        gpio_no = 39;
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_2);
        break;
    case BOARD_TYPE_EDS2:
        for (gpio_no = 32; gpio_no < 36; gpio_no++) {
            // SGPIO signals
            (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_2);
        }
        if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
            // Mode 0 is 5 Hz, two bits per port are used
            conf.bmode[0] = MESA_SGPIO_BMODE_5;
            conf.bit_count = 2;

            for (port = 0; port < 12; port++) {
                pc = &conf.port_conf[port];
                pc->enabled = (port < 4 || port > 7); // Port 4-7 unused

                // Input port 1: SFP0_TXFAULT, SFP1_TXFAULT (Tx fault)
                // Input port 2: SFP0_LOS, SFP0_MODDET (Module detect)
                // Input port 3: SFP1_LOS, SFP1_MODDET (Module detect)
                if (port > 0 && port < 4) {
                    pc->int_pol_high[0] = 1;
                    pc->int_pol_high[1] = 1;
                }

                // Output port  0: P0_GRN, P0_YEL (LED control)
                // Output port  1: P1_GRN, P1_YEL (LED control)
                // Output port  2: SFP0_GR, SFP0_RD (LED control), S0_BLU/S0_GRN (Endnode)
                // Output port  3: SFP1_GR, SFP1_RD (LED control), S1_BLU/S1_GRN (Endnode)
                // Output port  8: SFP0_RS0, SFP0_RS1 (Rate select)
                // Output port  9: SFP1_RS0, SFP1_RS1 (Rate select)
                // Output port 10: SFP0_TXEN, SFP1_TXEN (Tx enable)
                // Output port 11: SFP0_SCKEN, SFP1_SCKEN (I2C clock select)
                if (port < 2) {
                    // Port 0/1 LED control, turn green on and yellow off while booting
                    pc->mode[0] = MESA_SGPIO_MODE_OFF;
                    pc->mode[1] = MESA_SGPIO_MODE_ON;
                } else if (port < 4) {
                    // Port 2/3 LED control, turn green on and red off while booting
                    // Endnode: Turn blue/green off (Carrier SFP ports not present)
                    pc->mode[0] = (board->type == BOARD_TYPE_ENDNODE ?
                                   MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
                    pc->mode[1] = MESA_SGPIO_MODE_ON;
                } else if (port == 8 || port == 9) {
                    // Rate select
                    pc->mode[0] = MESA_SGPIO_MODE_ON;
                    pc->mode[1] = MESA_SGPIO_MODE_ON;
                }
            }
            (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        }
        break;

    default:
        break;
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
        // Link phy base port for 8 port board.
        if (board->type == BOARD_TYPE_8PORT) {
            board->entry[port_no].phy_base_port = map[port_no].chip_port >= 4 && map[port_no].chip_port <= 7 ? 4 : 0;
        }
    }
}

static mesa_rc lan966x_ptp_rs422_conf_get(meba_inst_t inst,
                                          meba_ptp_rs422_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    //meba_board_state_t *board = INST2BOARD(inst);
    T_I(inst, "IMPLEMENTATION OF rs422_conf requires check/update to actual MASERATI hardware properties.");
    *conf = lan966x_rs422_conf;
    return rc;
}

static mesa_rc lan966x_ptp_external_io_conf_get(meba_inst_t inst, uint32_t io_pin, meba_ptp_io_cap_t *const board_assignment, meba_event_t *const source_id)
{
    meba_board_state_t *board = INST2BOARD(inst);

    if (io_pin >= VTSS_TS_IO_ARRAY_SIZE) {
        return MESA_RC_ERROR;
    }
    if (board->type == BOARD_TYPE_8PORT)
    {
        *board_assignment = pin_conf_lan9668[io_pin];
    }
    *source_id = init_int_source_id[io_pin];
    return MESA_RC_OK;
}

/* ---------------------------   Exposed API  ------------------------------- */

static uint32_t lan966x_capability(meba_inst_t inst, int cap)
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
            if (board->type == BOARD_TYPE_8PORT || board->type == BOARD_TYPE_EDS2) {
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

static mesa_rc lan966x_port_entry_get(meba_inst_t inst,
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

static mesa_rc lan966x_reset(meba_inst_t inst,
                             meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;
    T_I(inst, "Called - %d", reset);
    switch (reset) {
    case MEBA_BOARD_INITIALIZE:
        rc = lan966x_board_init(inst);
        break;

    case MEBA_PORT_LED_INITIALIZE:
        if (board->type == BOARD_TYPE_8PORT) {
            mesa_port_no_t   port_no;
            mepa_gpio_conf_t conf;

            conf.gpio_no = 0;
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                conf.led_num = MEPA_LED0;
                conf.mode = MEPA_GPIO_MODE_LED_LINK10_100_ACTIVITY;
                (void)meba_phy_gpio_mode_set(inst, port_no, &conf);
                conf.led_num = MEPA_LED1;
                conf.mode = MEPA_GPIO_MODE_LED_LINK1000_ACTIVITY;
                (void)meba_phy_gpio_mode_set(inst, port_no, &conf);
            }
        }
        break;

    case MEBA_PORT_RESET:
    case MEBA_PORT_RESET_POST:
    case MEBA_STATUS_LED_INITIALIZE:
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

static mesa_rc lan966x_sfp_i2c_xfer(meba_inst_t inst,
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

static mesa_rc lan966x_sfp_insertion_status_get(meba_inst_t inst,
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

static mesa_rc lan966x_sfp_status_get(meba_inst_t inst,
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

static mesa_rc lan966x_port_admin_state_set(meba_inst_t inst,
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

static mesa_rc lan966x_port_led_update(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       const mesa_port_status_t *status,
                                       const mesa_port_counters_t *counters,
                                       const meba_port_admin_state_t *state)
{
    mesa_rc            rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_status_t *old_status = &board->status[port_no];
    mesa_sgpio_conf_t  conf;
    mesa_sgpio_mode_t  *mode = conf.port_conf[port_no].mode;
    uint32_t           port_max;

    // Only the first 2/4 ports on Endnode/Carrier systems need LED update
    port_max = (board->type == BOARD_TYPE_ENDNODE ? 2 :
                board->type == BOARD_TYPE_ENDNODE_CARRIER ? 4 : 0);
    if (port_no < port_max &&
        (status->link != old_status->link || status->speed != old_status->speed) &&
        (rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
        *old_status = *status; // Save status
        mode[0] = MESA_SGPIO_MODE_ON; // P0_GR/P1_GR/SFP0_GR/SFP1_GR
        mode[1] = MESA_SGPIO_MODE_ON; // P0_YEL/P1_YEL/SFP0_RD/SFP1_RD
        if (status->link) {
            if (status->speed >= MESA_SPEED_1G) {
                mode[0] = MESA_SGPIO_MODE_0_ACTIVITY;
            } else {
                mode[1] = MESA_SGPIO_MODE_0_ACTIVITY;
            }
        }
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

    if (board->type == BOARD_TYPE_ADARO || board->type == BOARD_TYPE_SUNRISE) {
        return MESA_RC_ERROR;
    }

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
        if (board->type == BOARD_TYPE_8PORT && gpio_events[GPIO_IRQ]) {
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                (void)meba_generic_phy_event_check(inst, port_no, signal_notifier);
            }
            handled = 1;
        }
        // Check the timestamp events.
        if (board->type == BOARD_TYPE_8PORT && gpio_events[GPIO_IRQ]) {
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (meba_generic_phy_timestamp_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                    handled = 1;
                }
            }
        }
    }

    // If the GPIO line is still active at this point, it is required to
    // reiterate over all the devices and see why they are polling the line.
    if (gpio_handler_active(&button, &phy) == MESA_RC_OK)
        goto repeat_handler;

    return (handled ? MESA_RC_OK : MESA_RC_ERROR);
}

static mesa_rc ext0_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    return  MESA_RC_ERROR;
}

static mesa_rc cu_phy_handler(meba_inst_t inst, meba_board_state_t *board,
                              mesa_irq_t irq, meba_event_signal_t signal_notifier)
{
    if (board->type == BOARD_TYPE_ADARO || board->type == BOARD_TYPE_SUNRISE) {
        return MESA_RC_ERROR;
    }
    return meba_generic_phy_event_check(inst, irq - MESA_IRQ_CU_PHY_0, signal_notifier);
}

static mesa_rc lan966x_irq_handler(meba_inst_t inst,
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


static mesa_rc lan966x_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
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

static mesa_rc lan966x_event_enable(meba_inst_t inst,
                                    meba_event_t event_id,
                                    mesa_bool_t enable)
{
    mesa_rc               rc = MESA_RC_OK;
    meba_board_state_t    *board = INST2BOARD(inst);
    mesa_port_no_t        port_no;
    uint32_t              i, port, bit;
    mesa_ptp_event_type_t ptp_event;

    switch (event_id) {
    case MEBA_EVENT_SYNC:
    case MEBA_EVENT_EXT_SYNC:
    case MEBA_EVENT_EXT_1_SYNC:
    case MEBA_EVENT_CLK_ADJ:
    case MEBA_EVENT_VOE:
        break;
    case MEBA_EVENT_LOS:
        if (board->type == BOARD_TYPE_ENDNODE_CARRIER) {
            for (port_no = 2; port_no < 4; port_no++) {
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
                    (void)mesa_sgpio_event_enable(NULL, 0, 0, port, bit, enable);
                }
            }
        } else if (board->type == BOARD_TYPE_8PORT) {
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (is_phy_port(board->entry[port_no].cap)) {
                    rc = meba_phy_event_enable_set(inst, port_no, MEPA_LINK_LOS, enable);
                    if (rc != MESA_RC_OK) {
                        break;
                    }
                }
            }
        }
        break;
    case MEBA_EVENT_FLNK:
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            if (is_phy_port(board->entry[port_no].cap)) {
                rc = meba_phy_event_enable_set(inst, port_no, VTSS_PHY_LINK_FFAIL_EV, enable);
                if (rc != MESA_RC_OK) {
                    break;
                }
            }
        }
        break;
    case MEBA_EVENT_PUSH_BUTTON:
        if (board->type == BOARD_TYPE_8PORT ||
            board->type == BOARD_TYPE_ENDNODE ||
            board->type == BOARD_TYPE_ENDNODE_CARRIER) {
            rc = mesa_gpio_event_enable(NULL, 0, GPIO_PUSH_BUTTON, enable);
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
        if (board->type == BOARD_TYPE_8PORT) {
            mepa_ts_event_t event = meba_generic_phy_ts_source_to_event(inst, event_id);
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if ((rc = meba_phy_ts_event_set(inst, port_no, enable, event)) != MESA_RC_OK) {
                    T_E(inst, "vtss_phy_ts_event_enable_set(%d, %d, %d) = %d", port_no, enable, event, rc);
                }
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
    board->entry = (lan966x_port_info_t*) calloc(8, sizeof(lan966x_port_info_t));
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
    case BOARD_TYPE_SVB:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_5;
        lan966x_init_port_table(inst, 4, port_table_svb);
        break;
    case BOARD_TYPE_8PORT:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_0;
        lan966x_init_port_table(inst, 8, port_table_8port);
        break;
    case BOARD_TYPE_ENDNODE:
        lan966x_init_port_table(inst, 3, port_table_endnode);
        break;
    case BOARD_TYPE_ENDNODE_CARRIER:
        lan966x_init_port_table(inst, 5, port_table_endnode_carrier);
        break;
    case BOARD_TYPE_EDS2:
        lan966x_init_port_table(inst, 2, port_table_endnode);
    default:
        break;
    }

    inst->props.board_type = board->type;

    T_I(inst, "Board: %s, target %4x, %d ports, mux_mode %d",
        inst->props.name, inst->props.target, board->port_cnt, inst->props.mux_mode);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = lan966x_capability;
    inst->api.meba_port_entry_get             = lan966x_port_entry_get;
    inst->api.meba_reset                      = lan966x_reset;
    inst->api.meba_sfp_i2c_xfer               = lan966x_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = lan966x_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = lan966x_sfp_status_get;
    inst->api.meba_port_admin_state_set       = lan966x_port_admin_state_set;
    inst->api.meba_port_led_update            = lan966x_port_led_update;
    inst->api.meba_irq_handler                = lan966x_irq_handler;
    inst->api.meba_irq_requested              = lan966x_irq_requested;
    inst->api.meba_event_enable               = lan966x_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get         = lan966x_ptp_rs422_conf_get;
    inst->api_synce                           = meba_synce_get();
    inst->api_tod                             = meba_tod_get();
    inst->api.meba_ptp_external_io_conf_get   = lan966x_ptp_external_io_conf_get;

    return inst;

error_out:
    free(inst);
    return NULL;
}
