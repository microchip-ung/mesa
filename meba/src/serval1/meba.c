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

#include <stdint.h>
#include <stdio.h>
#include <mscc/ethernet/board/api.h>

#include "meba_aux.h"
#include "meba_generic.h"

typedef enum {
    BOARD_TYPE_SERVAL_REF,
    BOARD_TYPE_SERVAL_NID,
} board_type_t;

/* LED colors */
typedef enum {
    LED_GREEN,
    LED_YELLOW
} led_color_t;

/* LED tower mode */
typedef enum {
    LED_TOWER_MODE_LINK_SPEED,      /**< Green: 1G link/activity; Orange: 10/100 link/activity */
    LED_TOWER_MODE_DUPLEX,          /**< Green: FDX; Orange: HDX + Collisions */
    LED_TOWER_MODE_LINK_STATUS,     /**< Green: Link/activity; Orange: port disabled/errors */
    LED_TOWER_MODE_POWER_SAVE,      /**< Disabled to save power */
    LED_TOWER_MODE_CNT
} led_tower_mode_t;

typedef struct {
    meba_port_entry_t       map;
    led_tower_mode_t        led_mode_old;
    mesa_port_status_t      status_old;
    mesa_port_counter_t     collisions;
    mesa_bool_t             fiber_link_old;
    meba_port_admin_state_t state_old;
    mesa_bool_t             ts_phy;
} meba_ports_t;

typedef struct meba_board_state {
    board_type_t type;
    int  port_cnt;     // Number of exposed (external) ports
    int  port_map_cnt; // Number of ports in the port map (may be > port_cnt if having mirror or mep loop ports)
    led_tower_mode_t led_tower_mode;
    const mesa_fan_conf_t *fan_spec;
    meba_ports_t *port;
} meba_board_state_t;

static const mesa_fan_conf_t fan_conf = {
    .fan_pwm_freq = MESA_FAN_PWM_FREQ_20HZ,    // 20MHz
    .fan_low_pol = 0,                          // active low
    .fan_open_col = true,                      // Open collector
    .type = MESA_FAN_3_WIRE_TYPE,              // 3-wire
    .ppr = 2,                                  // 2 PPR
};

static const meba_aux_rawio_t rawio = {
    .gcb = 0x07,
    .miim = {
        .status = 0x17+0,
        .cmd    = 0x17+2,
        .data   = 0x17+3,
        .cfg    = 0x17+4,
    },
    .gpio = {
        .alt_0  = 0x15,
    }
};

static const struct {
    uint8_t port, bit;
} tower_led_mapping[4][2] = {
    {{12, 0} /* tower 0 green */, {12, 1} /* tower 0 yellow */},
    {{13, 0} /* tower 1 green */, {13, 1} /* tower 1 yellow */},
    {{14, 0} /* tower 2 green */, {14, 1} /* tower 2 yellow */},
    {{15, 0} /* tower 3 green */, {15, 1} /* tower 3 yellow */}
};

static const meba_ptp_rs422_conf_t rs422_conf = {
    .gpio_rs422_1588_mstoen = 23,
    .gpio_rs422_1588_slvoen = -1,
    .ptp_pin_ldst           = -1,
    .ptp_pin_ppso           = -1,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_SYNC,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_EXT_SYNC
};

static uint32_t serval_capability(meba_inst_t inst,
                                  int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_POE:
            return false;
        case MEBA_CAP_1588_CLK_ADJ_DAC:
            return false;
        case MEBA_CAP_1588_REF_CLK_SEL:
            return false;
        case MEBA_CAP_TEMP_SENSORS:
            // No temperature sensor in "lite" variant
            return inst->props.target == MESA_TARGET_SERVAL_LITE ? 0 : 1;
        case MEBA_CAP_BOARD_PORT_COUNT:
            return board->port_cnt;
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            return board->port_map_cnt;
        case MEBA_CAP_LED_MODES:
            return LED_TOWER_MODE_CNT;
        case MEBA_CAP_DYING_GASP:
            return true;
        case MEBA_CAP_FAN_SUPPORT:
            return board->type == BOARD_TYPE_SERVAL_NID;
        case MEBA_CAP_LED_DIM_SUPPORT:
            return inst->props.target != MESA_TARGET_SERVAL_LITE;  // No internal PHY
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
            return false;
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
            return false;
        case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:      // NOTE: Capability currently not used on Serval1. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:  // NOTE: Capability currently not used on Serval1. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_DPLL:            // NOTE: Capability currently not used on Serval1. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:      // NOTE: Capability currently not used on Serval1. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:  // NOTE: Capability currently not used on Serval1. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_ONE_PPS_INT_ID:
            return MEBA_EVENT_SYNC;
        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:      // Serval1 supports single DPLL mode if a DPLL is present
            {
                meba_synce_clock_hw_id_t dpll_type;

                if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK) && (dpll_type != MEBA_SYNCE_CLOCK_HW_NONE)) {
                    return true;
                } else {
                    return false;
                }
            }
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:        // Serval1 does not support dual DPLL mode
            return false;
        case MEBA_CAP_POE_BT:
            return false;
        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc serval_port_entry_get(meba_inst_t inst,
                                     mesa_port_no_t port_no,
                                     meba_port_entry_t *entry)
{
    mesa_rc rc;
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called");
    if (port_no < board->port_map_cnt) {
        *entry = board->port[port_no].map;
        rc = MESA_RC_OK;
    } else {
        rc = MESA_RC_ERROR;
    }
    T_N(inst, "Called(%d): rc %d - chip %d, miim bus %d, addr: %d", port_no, rc,
        entry->map.chip_port, entry->map.miim_controller, entry->map.miim_addr);
    return rc;
}

static mesa_rc serval_reset(meba_inst_t inst,
                            meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;
    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            {
                mesa_gpio_no_t    gpio_no;
                mesa_sgpio_conf_t conf;
                uint32_t          port;

                /* Enable GPIO_0 to GPIO_3 as SGPIO signals */
                for (gpio_no = 0; gpio_no < 4; gpio_no++) {
                    (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
                }

                /* Enable GPIO_9 and GPIO_10 as MIIM controllers */
                (void)mesa_gpio_mode_set(NULL, 0, 9, MESA_GPIO_ALT_1);
                (void)mesa_gpio_mode_set(NULL, 0, 10, MESA_GPIO_ALT_1);

                /* Enable SGPIO ports 0-15,24-31 with two bits */
                if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
                    /* The blink mode 0 is 5 HZ for link activity and collion in half duplex. */
                    conf.bmode[0] = MESA_SGPIO_BMODE_5;
                    conf.bit_count = 2;
                    for (port = 0; port < MESA_SGPIO_PORTS; port++) {
                        if (board->type == BOARD_TYPE_SERVAL_NID) {
                            // For the PCB106 all serial GPIO are used. See Schematic
                            // Even though p18, p19, p30 and p31 are not connected, they are still in the chain.
                            conf.port_conf[port].enabled = 1;
                        } else {
                            // For the PCB105 p16 to p23 is not used. See Schematic
                            // Even though p30 and p31 are not connected, they are still in the chain.
                            if (port < 16 || port > 23) {
                                conf.port_conf[port].enabled = 1;
                            }
                        }
                    }
                    (void) mesa_sgpio_conf_set(NULL, 0, 0, &conf);
                }
            }
            break;
        case MEBA_PORT_RESET:
            if (inst->props.target != MESA_TARGET_SERVAL_LITE) {
                uint32_t port_no;
                rc = mesa_phy_pre_reset(PHY_INST, 0); /* Tesla PHY */
                for (port_no = 0; port_no < 4; port_no++) {
                    // SFP Signal detect shall be active high (register 19E1 bit 1 = 0)
                    (void) mesa_phy_write_masked(PHY_INST, port_no, 19 |MESA_PHY_REG_EXTENDED , 0x0, 0x1);
                }
            }
            break;
        case MEBA_PORT_RESET_POST:
            if (inst->props.target != MESA_TARGET_SERVAL_LITE) {
                rc = mesa_phy_post_reset(PHY_INST, 0); /* Tesla PHY */
            }
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            // Setup LED dimming, not avail on Serval Lite
            if (inst->props.target != MESA_TARGET_SERVAL_LITE) {
                mesa_phy_enhanced_led_control_t conf = { 0 };
                if (board->type == BOARD_TYPE_SERVAL_NID) {
                    uint32_t port_no, port_no_start = 0, port_no_end = 4;
                    mesa_phy_led_mode_select_t led_blink_mode = { 0 };
                    for (port_no = port_no_start; port_no < port_no_end; port_no++) {
                        led_blink_mode.mode = MESA_PHY_LED_MODE_LINK100BASE_FX_ACTIVITY;
                        led_blink_mode.number = MESA_PHY_LED0;
                        mesa_phy_led_mode_set(NULL, port_no, led_blink_mode);

                        led_blink_mode.mode = MESA_PHY_LED_MODE_LINK1000BASE_X_ACTIVITY;
                        led_blink_mode.number = MESA_PHY_LED1;
                        mesa_phy_led_mode_set(NULL, port_no, led_blink_mode);
                    }
                }
                conf.ser_led_output_2 = false; // Not used. 
                conf.ser_led_output_1 = true; // Enhanced serial LED output enable
                conf.ser_led_frame_rate = 0x1; // Frame rate = 1000Hz
                // For PCB105 this can be set to anything, since the
                // serial pins are not used, but for PCB106 the serial
                // pins are connected to shift registers that expect 2
                // LEDs per PHY.
                conf.ser_led_select = 2;
                mesa_phy_enhanced_led_control_init(PHY_INST, 1, conf); // Initialize the API
            }
            break;
        case MEBA_PORT_LED_INITIALIZE:
            // noop
            break;
        case MEBA_FAN_INITIALIZE:
            if (serval_capability(inst, MEBA_CAP_FAN_SUPPORT)) {
                rc = mesa_fan_controller_init(PHY_INST, board->fan_spec);
            }
            break;
        case MEBA_SENSOR_INITIALIZE:
            rc = mesa_phy_chip_temp_init(PHY_INST, 0);
            break;
        case MEBA_INTERRUPT_INITIALIZE:
            {
                mesa_phy_type_t phy_id;
                mesa_port_no_t port_no;
                for (port_no = 0; port_no < board->port_cnt; port_no++) {
                    if (mesa_phy_id_get(PHY_INST, port_no, &phy_id) != MESA_RC_OK) {
                        continue;
                    }
                    if ((phy_id.part_number == MESA_PHY_TYPE_8574) || (phy_id.part_number == MESA_PHY_TYPE_8572) ||
                        (phy_id.part_number == MESA_PHY_TYPE_8582) || (phy_id.part_number == MESA_PHY_TYPE_8584) ||
                        (phy_id.part_number == MESA_PHY_TYPE_8575)) {
                        board->port[port_no].ts_phy = true;
                    }
                }
            }
            break;
        case MEBA_SYNCE_DPLL_INITIALIZE:
            break;
    }

    return rc;
}

static mesa_rc serval_sensor_get(meba_inst_t inst,
                                 meba_sensor_t type,
                                 int six,
                                 int *value)
{
    mesa_rc rc = MESA_RC_ERROR;
    int16_t temp = 0;
    T_N(inst, "Called %d:%d", type, six);
    if (type == MEBA_SENSOR_BOARD_TEMP) {
        if (six < serval_capability(inst, MEBA_CAP_TEMP_SENSORS)) {
            rc = mesa_phy_chip_temp_get(PHY_INST, six, &temp);
        }
    } else if (type == MEBA_SENSOR_PORT_TEMP) {
        rc = mesa_phy_chip_temp_get(PHY_INST, 0, &temp);
    }
    if (rc == MESA_RC_OK) {
        *value = temp;    // Conversion
    }
    return rc;
}

static mesa_rc serval_sfp_i2c_xfer(meba_inst_t inst,
                                   mesa_port_no_t port_no,
                                   mesa_bool_t write,
                                   uint8_t i2c_addr,
                                   uint8_t addr,
                                   uint8_t *data,
                                   uint8_t cnt,
                                   mesa_bool_t word_access)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called");
    if (port_no < board->port_cnt) {
        meba_port_entry_t *entry = &board->port[port_no].map;
        if (write) {
            if (entry->cap & MEBA_PORT_CAP_DUAL_COPPER) {
                rc = mesa_phy_i2c_write(NULL, port_no, port_no, addr, i2c_addr, data, cnt, word_access);
            } else {
                // Uplink ports - Connected to switch i2c
                uint8_t i2c_data[3];
                i2c_data[0] = addr;
                memcpy(&i2c_data[1], data, 2);
                /* In serval_lite, iport 0~5 use I2C adapter (MUX_PORT_START + 4) ~ (MUX_PORT_START + 9)
                   according to bsp-driver.c */
                rc = inst->iface.i2c_write((inst->props.target != MESA_TARGET_SERVAL_LITE) ? port_no : port_no + 4,
                        i2c_addr, i2c_data, 3);
            }
        } else {
            if (entry->cap & MEBA_PORT_CAP_DUAL_COPPER) {
                rc = mesa_phy_i2c_read(NULL, port_no, port_no, addr, i2c_addr, data, cnt, word_access);
            } else {
                /* In serval_lite, iport 0~5 use I2C adapter (MUX_PORT_START + 4) ~ (MUX_PORT_START + 9)
                   according to bsp-driver.c */
                rc = inst->iface.i2c_read((inst->props.target != MESA_TARGET_SERVAL_LITE) ? port_no : port_no + 4,
                        i2c_addr, addr, data, cnt);
            }
        }
    }
    T_D(inst, "i2c %s port %d - address 0x%02x:0x%02x, %d bytes return %d", write ? "write" : "read", port_no, i2c_addr, addr, cnt, rc);
    return rc;
}

static mesa_rc serval_sfp_insertion_status_get(meba_inst_t inst,
                                               mesa_port_list_t *present)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];
    mesa_port_no_t port_no;
    mesa_rc rc;

    //T_D(inst, "Called");

    mesa_port_list_clear(present);

    if ((rc = mesa_sgpio_read(NULL, 0, 0, data)) != MESA_RC_OK)
        return rc;

    for(port_no = 0; port_no < board->port_cnt; port_no++) {
        meba_port_entry_t *entry = &board->port[port_no].map;
        if (entry->cap & MEBA_PORT_CAP_DUAL_COPPER) {
            /* Dual media port for PCB106, see U46 in schematic. */
            mesa_port_list_set(present, port_no, (data[16 + (port_no / 2)].value[port_no % 2] ? 0 : 1));
        } else if (entry->cap & MEBA_PORT_CAP_SFP_DETECT) {
            mesa_port_list_set(present, port_no, (data[entry->map.chip_port].value[1] ? 0 : 1));
        }
    }
    return rc;
}

static mesa_rc serval_sfp_status_get(meba_inst_t inst,
                                     mesa_port_no_t port_no,
                                     meba_sfp_status_t *status)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);

    if (port_no < board->port_cnt) {
        mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];
        mesa_bool_t los;
        meba_port_entry_t *entry = &board->port[port_no].map;

        if ((rc = mesa_sgpio_read(NULL, 0, 0, data)) != MESA_RC_OK) {
            return rc;
        }

        if (entry->cap & MEBA_PORT_CAP_DUAL_COPPER) {
            /* Dual media port for PCB106, see U46 in schematic. */
            (void)mesa_phy_gpio_mode(NULL, port_no, port_no, MESA_PHY_GPIO_IN);
            (void)mesa_phy_gpio_get(NULL, port_no, port_no, &los); // To get Loss Of Signal
            status->present = (data[16 + (port_no / 2)].value[port_no % 2] ? 0 : 1); // Is inverted
            status->tx_fault = (data[18 + (port_no / 2)].value[port_no % 2]);
            status->los = los;
        } else if (entry->cap & MEBA_PORT_CAP_SFP_DETECT) {
            status->present = (data[entry->map.chip_port].value[1] ? 0 : 1); // Is inverted
            status->los = data[entry->map.chip_port].value[0];
            if (entry->map.chip_port == 0) {
                status->tx_fault = data[4].value[0];
            } else if (entry->map.chip_port == 1) {
                status->tx_fault = data[4].value[1];
            } else if (entry->map.chip_port == 2) {
                status->tx_fault = data[5].value[0];
            } else if (entry->map.chip_port == 3) {
                status->tx_fault = data[5].value[1];
            } else if (entry->map.chip_port == 8) {
                status->tx_fault = data[6].value[0];
            } else if (entry->map.chip_port == 9) {
                status->tx_fault = data[6].value[1];
            }
        } else {
            status->present   = false;
            status->los       = true;
            status->tx_fault  = true;
        }
    }
    T_N(inst, "port(%d): rc %d, present:%d los:%d tx_fault:%d", port_no, rc,
        status->present, status->los, status->tx_fault);
    return rc;
}

static mesa_rc serval_port_admin_state_set(meba_inst_t inst,
                                           mesa_port_no_t port_no,
                                           const meba_port_admin_state_t *state)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);

    if (port_no < board->port_cnt) {
        meba_port_entry_t *entry = &board->port[port_no].map;
        uint32_t port = entry->map.chip_port;
        mesa_sgpio_conf_t conf;

        if (port < 4) {
            /* Chip port 0-3, SFP port 4-7, port 24-27 used for tx_enable */
            port = (27 - port);
        } else if (port < 8) {
            /* Chip port 4-7, SFP port 0-3 (if dual media), SGPIO port 20-23 used for tx_enable */
            port = ((entry->cap & MEBA_PORT_CAP_DUAL_COPPER) ? (27 - port) : 0);
        } else if (port < 10) {
            /* Chip port 8-9, SFP port 8-9, port 28-29 used for tx_enable */
            port = (20 + port);
        } else {
            port = 0;
        }
        if (port != 0) {
            if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
                conf.port_conf[port].mode[0] = (state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
                rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
            }
        } else {
            rc = MESA_RC_OK;
        }
    }
    T_D(inst, "port(%d): rc %d, enable:%d", port_no, rc, state->enable);
    return rc;
}

static void board_sgpio_led_set(meba_board_state_t *board,
                                mesa_port_no_t port_no,
                                led_color_t color,
                                mesa_sgpio_mode_t mode,
                                mesa_sgpio_conf_t *conf)
{
    uint32_t port = board->port[port_no].map.map.chip_port;
    if (port == 10 && board->type == BOARD_TYPE_SERVAL_REF) {
        /* For PCB105, activity for management port are swapped */
        mode = (mode == MESA_SGPIO_MODE_ON ? MESA_SGPIO_MODE_OFF :
                mode == MESA_SGPIO_MODE_0_ACTIVITY ? MESA_SGPIO_MODE_0_ACTIVITY_INV :
                mode == MESA_SGPIO_MODE_0_ACTIVITY_INV ? MESA_SGPIO_MODE_0_ACTIVITY :
                MESA_SGPIO_MODE_ON);
    }
    conf->port_conf[port].mode[color == LED_GREEN ? 0 : 1] = mode;
}

static mesa_rc serval_status_led_set(meba_inst_t inst,
                                     meba_led_type_t type,
                                     meba_led_color_t color)
{
    mesa_rc rc = MESA_RC_ERROR;
    if (type == MEBA_LED_TYPE_FRONT && color < MEBA_LED_COLOR_COUNT) {
        mesa_sgpio_conf_t conf;
        T_I(inst, "LED:%d, color=%d", type, color);
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            /* SGPIO port 11 used */
            mesa_sgpio_port_conf_t  *port_conf = &conf.port_conf[11];
            /* Bit 0: Green, bit 1: Red, active high */
            switch (color) {
                case MEBA_LED_COLOR_OFF:
                    port_conf->mode[0] = MESA_SGPIO_MODE_OFF;
                    port_conf->mode[1] = MESA_SGPIO_MODE_OFF;
                    break;
                case MEBA_LED_COLOR_GREEN:
                    port_conf->mode[0] = MESA_SGPIO_MODE_ON;
                    port_conf->mode[1] = MESA_SGPIO_MODE_OFF;
                    break;
                case MEBA_LED_COLOR_RED:
                    port_conf->mode[0] = MESA_SGPIO_MODE_OFF;
                    port_conf->mode[1] = MESA_SGPIO_MODE_ON;
                    break;
                case MEBA_LED_COLOR_YELLOW:
                    port_conf->mode[0] = MESA_SGPIO_MODE_ON;
                    port_conf->mode[1] = MESA_SGPIO_MODE_ON;
                    break;
                default:
                    rc = MESA_RC_ERROR;
            }
            if (rc == MESA_RC_OK) {
                rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
            }
        }
    }
    return rc;
}

static mesa_rc serval_port_led_update(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      const mesa_port_status_t *status,
                                      const mesa_port_counters_t *counters,
                                      const meba_port_admin_state_t *state)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc             rc;
    mesa_bool_t         need_process = false, fiber_link = false, cu_sfp = false, collision = false, tower_mode_changed;
    uint16_t            phy_reg;

    // Tesla SFP ports are ports 0-3. Because the SFP LED are
    // controlled by Tesla, we need to disable the CU LED if the link
    // up is due to SFP link (Found in Tesla register 28 bit 1:0).
    if ((board->port[port_no].map.cap & MEBA_PORT_CAP_DUAL_COPPER) &&
        mesa_phy_read(NULL, port_no,  28, &phy_reg) == MESA_RC_OK &&
        (phy_reg & 0x3) == 0x2) { // Bit 1:0   0x1 = Cu, 0x2 = FIBER
        fiber_link = true;
        if (mesa_phy_read(NULL, port_no,  23, &phy_reg) == MESA_RC_OK) {
            // If we are in the PASS through mode we are running CU
            // SFP and should be handled specially
            if ((phy_reg & 0x700) == 0x100) {
                cu_sfp = true;
            }
        }
    }

    /* Check if port's link/speed/fdx has changed */
    if (board->port[port_no].status_old.link != status->link ||
        board->port[port_no].state_old.enable != state->enable ||
        (status->link &&
         (board->port[port_no].status_old.speed != status->speed ||
          board->port[port_no].status_old.fdx != status->fdx ||
          board->port[port_no].fiber_link_old != fiber_link))) {
        T_I(inst, "Port %d: Link state change - Force update", port_no);
        need_process = true;
    }
    board->port[port_no].status_old = *status;
    board->port[port_no].fiber_link_old = fiber_link;
    board->port[port_no].state_old = *state;

    /* Check if port collision occured */
    if (board->led_tower_mode == LED_TOWER_MODE_DUPLEX &&
        status->link &&
        !status->fdx &&
        board->port[port_no].collisions != counters->rmon.tx_etherStatsCollisions) {
        T_I(inst, "Port %d: Collision - Force update", port_no);
        need_process = true;
        collision = true;
    }
    board->port[port_no].collisions = counters->rmon.tx_etherStatsCollisions;

    // find out if tower mode has changed since the last time the port was served.
    tower_mode_changed = board->port[port_no].led_mode_old != board->led_tower_mode;
    board->port[port_no].led_mode_old = board->led_tower_mode;

    /* Return here if nothing has changed or in power saving mode */
    if ((!need_process && !tower_mode_changed) ||
        (!tower_mode_changed && board->led_tower_mode == LED_TOWER_MODE_POWER_SAVE)) {
        return MESA_RC_OK;
    }

    /* Need to update? */
    if (need_process || tower_mode_changed) {
        mesa_sgpio_conf_t conf;
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            led_color_t color;
            mesa_sgpio_mode_t activity;
            board_sgpio_led_set(board, port_no, LED_GREEN, MESA_SGPIO_MODE_OFF, &conf);
            board_sgpio_led_set(board, port_no, LED_YELLOW, MESA_SGPIO_MODE_OFF, &conf);

            color = LED_GREEN;
            activity = MESA_SGPIO_MODE_OFF;

            if (!fiber_link) { // Only turn on LED if the link up is a CU port.
                switch (board->led_tower_mode) {
                    case LED_TOWER_MODE_LINK_SPEED:
                        if (board->port[port_no].status_old.link) {
                            if (board->port[port_no].status_old.speed >= MESA_SPEED_1G) {
                                /* Green: 1G link/activity */
                                color = LED_GREEN;
                                activity = MESA_SGPIO_MODE_0_ACTIVITY_INV;
                            } else {
                                /* Yellow: 100/10 link/activity */
                                color = LED_YELLOW;
                                activity = MESA_SGPIO_MODE_0_ACTIVITY_INV;
                            }
                        }
                        break;
                    case LED_TOWER_MODE_DUPLEX:
                        if (board->port[port_no].status_old.link) {
                            if (board->port[port_no].status_old.fdx) {
                                /* Green: FDX */
                                color = LED_GREEN;
                                activity = MESA_SGPIO_MODE_0_ACTIVITY_INV;
                            } else if (collision) {
                                /* Blink yellow: HDX with collision */
                                color = LED_YELLOW;
                                activity = MESA_SGPIO_MODE_0;
                            } else {
                                /* Yellow: HDX without collision */
                                color = LED_YELLOW;
                                activity = MESA_SGPIO_MODE_ON;
                            }
                        }
                        break;
                    case LED_TOWER_MODE_LINK_STATUS:
                        if (!state->enable) {
                            color = LED_YELLOW;
                            activity = MESA_SGPIO_MODE_ON;
                        } else if (board->port[port_no].status_old.link) {
                            /* Green: link on */
                            color = LED_GREEN;
                            activity = MESA_SGPIO_MODE_ON;
                        }
                        break;
                    case LED_TOWER_MODE_POWER_SAVE:
                        break;
                    default:
                        break;
                }
            }

            T_I(inst, "port(%d): color:%d activity:%d", port_no, color, activity);
            board_sgpio_led_set(board, port_no, color, activity, &conf);

            // Setup SFP LED for Dual media ports (port 1-4)
            if (board->port[port_no].map.cap & MEBA_PORT_CAP_DUAL_COPPER) {

                // LED0 = Yellow, LED1 = Green
                mesa_phy_led_mode_select_t led0_blink_mode, led1_blink_mode;
                led0_blink_mode.number = MESA_PHY_LED0; // LED0 is the yellow LED
                led1_blink_mode.number = MESA_PHY_LED1; // LED1 is the green LED

                // In Link status mode the Yellow LED shall be turn on if port is disabled, else green
                switch (board->led_tower_mode) {
                    case LED_TOWER_MODE_LINK_STATUS :
                        // Both 100FX and 1000Base-x should be green in this mode.
                        led1_blink_mode.mode = MESA_PHY_LED_MODE_LINK100BASE_FX_1000BASE_X_ACTIVITY;

                        // If port is disabled then turn yellow LED on.
                        if (!state->enable) {
                            led0_blink_mode.mode = MESA_PHY_LED_MODE_FORCE_LED_ON;
                        } else {
                            led0_blink_mode.mode = MESA_PHY_LED_MODE_FORCE_LED_OFF;
                        }
                        break;
                    case LED_TOWER_MODE_POWER_SAVE:
                        led0_blink_mode.mode = MESA_PHY_LED_MODE_FORCE_LED_OFF;
                        led1_blink_mode.mode = MESA_PHY_LED_MODE_FORCE_LED_OFF;
                        break;

                    default:
                        led0_blink_mode.mode = MESA_PHY_LED_MODE_FORCE_LED_OFF;
                        led1_blink_mode.mode = MESA_PHY_LED_MODE_FORCE_LED_OFF;

                        if (board->port[port_no].status_old.link) {
                            if (cu_sfp) { // For Cu SFP we need to select the corresponding LED
                                switch (status->speed) {
                                    case MESA_SPEED_10M:
                                    case MESA_SPEED_100M:
                                        led0_blink_mode.mode = MESA_PHY_LED_MODE_LINK100_1000_ACTIVITY; // Set yellow LED
                                        led1_blink_mode.mode = MESA_PHY_LED_MODE_FORCE_LED_OFF;         // Set green LED
                                        break;
                                    default:
                                        led0_blink_mode.mode = MESA_PHY_LED_MODE_FORCE_LED_OFF;         // Set yellow LED
                                        led1_blink_mode.mode = MESA_PHY_LED_MODE_LINK100_1000_ACTIVITY; // Set green LED
                                }
                            } else {
                                led0_blink_mode.mode = MESA_PHY_LED_MODE_LINK100BASE_FX_ACTIVITY; // Default mode for the yellow LED
                                led1_blink_mode.mode = MESA_PHY_LED_MODE_LINK1000BASE_X_ACTIVITY; // Default mode for the green LED
                            }
                        }
                        break;
                }

                T_I(inst, "port(%d): mode0:%d mode1:%d", port_no, led0_blink_mode.mode, led1_blink_mode.mode);
                if ((rc = mesa_phy_led_mode_set(NULL, port_no, led0_blink_mode)) != MESA_RC_OK ||
                    (rc = mesa_phy_led_mode_set(NULL, port_no, led1_blink_mode)) != MESA_RC_OK) {
                    return rc;
                }
            }
            rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        }
    }

    return rc;
}

static mesa_rc serval_led_mode_set(meba_inst_t inst, uint32_t mode)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t  conf;
    mesa_rc            rc;

    if (mode < LED_TOWER_MODE_CNT) {
        board->led_tower_mode = mode;
    } else {
        return MESA_RC_ERROR;
    }

    T_I(inst, "Update LED mode to %d", board->led_tower_mode);

    /*
     * LED tower:
     *  (top)       o  mode A (link/speed)
     *              o  mode B (link/duplex)
     *              o  mode C (link/status)
     *  (button)    o  PWR save
     */
    if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
        int i;
        for (i = 0; i < 4; i++) {
            conf.port_conf[tower_led_mapping[i][0].port].mode[tower_led_mapping[i][0].bit] =
                    conf.port_conf[tower_led_mapping[i][1].port].mode[tower_led_mapping[i][1].bit] =
                    MESA_SGPIO_MODE_OFF;
        }

        /* PTP ports - OFF */
        conf.port_conf[30].mode[0] =
                conf.port_conf[30].mode[1] =
                conf.port_conf[31].mode[0] =
                conf.port_conf[31].mode[1] =
                MESA_SGPIO_MODE_ON;     /* Inverted polarity! */

        i = board->led_tower_mode;    // Maps 1:1
        conf.port_conf[tower_led_mapping[i][0].port].mode[tower_led_mapping[i][0].bit] = MESA_SGPIO_MODE_ON;
        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc ;
}

static mesa_rc serval_led_intensity_set(meba_inst_t inst,
                                        mesa_phy_led_intensity intensity)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    if (serval_capability(inst, MEBA_CAP_LED_DIM_SUPPORT)) {
        T_N(inst, "Called - %d", intensity);
        rc = mesa_phy_led_intensity_set(PHY_INST, 0, intensity);
    }
    return rc;
}

static mesa_rc serval_fan_param_get(meba_inst_t inst,
                                    meba_fan_param_t *param)
{
    mesa_rc rc = MESA_RC_OK;
    T_N(inst, "Called");
    if (serval_capability(inst, MEBA_CAP_FAN_SUPPORT)) {
        param->start_time = 100;
        param->start_level = 60;
        param->min_pwm = 30;
    } else {
        rc = MESA_RC_ERROR;
    }
    return rc;
}

static mesa_rc serval_fan_conf_get(meba_inst_t inst,
                                mesa_fan_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    T_N(inst, "Called");
    if (serval_capability(inst, MEBA_CAP_FAN_SUPPORT)) {
        meba_board_state_t *board = INST2BOARD(inst);
        *conf = *board->fan_spec;
    } else {
        rc = MESA_RC_ERROR;
    }
    return rc;
}

static mesa_rc serval_ptp_rs422_conf_get(meba_inst_t inst,
                                   meba_ptp_rs422_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    T_N(inst, "Called");
    *conf = rs422_conf;
    return rc;
}

static mesa_rc serval_phy_event_enable(meba_inst_t inst,
                                       meba_board_state_t *board,
                                       mesa_phy_event_t phy_event,
                                       mesa_bool_t enable)
{
    mesa_port_no_t port_no;
    mesa_rc rc = MESA_RC_OK;
    T_D(inst, "%sable phy event %d on all ports", enable ? "en" : "dis", phy_event);
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (is_phy_port(board->port[port_no].map.cap)) {
            T_N(inst, "%sable phy event %d on port %d", enable ? "en" : "dis", phy_event, port_no);
            if ((rc = mesa_phy_event_enable_set(PHY_INST, port_no, phy_event, enable)) != MESA_RC_OK) {
                T_E(inst, "mesa_phy_event_enable_set = %d", rc);
                break;
            }
        }
    }
    return rc;
}

static mesa_rc serval_event_enable(meba_inst_t inst,
                                   meba_event_t event_id,
                                   mesa_bool_t enable)
{
    meba_board_state_t    *board = INST2BOARD(inst);
    mesa_rc               rc = MESA_RC_OK;
    mesa_port_no_t        port_no;

    T_I(inst, "%sable event %d", enable ? "en" : "dis", event_id);

    switch (event_id) {
        case MEBA_EVENT_SYNC:
        case MEBA_EVENT_EXT_SYNC:
        case MEBA_EVENT_EXT_1_SYNC:
        case MEBA_EVENT_CLK_ADJ:
        case MEBA_EVENT_CLK_TSTAMP:
        case MEBA_EVENT_PTP_PIN_0:
        case MEBA_EVENT_PTP_PIN_1:
        case MEBA_EVENT_PTP_PIN_2:
        case MEBA_EVENT_PTP_PIN_3:
            {
                mesa_ptp_event_type_t ptp_event = meba_generic_ptp_source_to_event(inst, event_id);
                if ((rc = mesa_ptp_event_enable(NULL, ptp_event, enable)) != MESA_RC_OK) {
                    T_E(inst, "mesa_ptp_event_enable = %d", rc);
                }
                return rc;
            }

        case MEBA_EVENT_LOS:
            if (enable) {
                for (port_no = 0; port_no < 10; port_no++) {
                    if (port_no < 4 || port_no > 7) {
                        // Enable SGPIO for SFP ports
                        if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, port_no, 0, enable)) != MESA_RC_OK) {
                            T_E(inst, "mesa_sgpio_event_enable = %d", rc);
                        }
                    }
                }
            }
            rc = serval_phy_event_enable(inst, board, MESA_PHY_LINK_LOS_EV, enable);
            break;

        case MEBA_EVENT_FLNK:
            rc = serval_phy_event_enable(inst, board, MESA_PHY_LINK_FFAIL_EV, enable);
            break;

        case MEBA_EVENT_AMS:
            rc = serval_phy_event_enable(inst, board, MESA_PHY_LINK_AMS_EV, enable);
            break;

        case MEBA_EVENT_INGR_ENGINE_ERR:
        case MEBA_EVENT_INGR_RW_PREAM_ERR:
        case MEBA_EVENT_INGR_RW_FCS_ERR:
        case MEBA_EVENT_EGR_ENGINE_ERR:
        case MEBA_EVENT_EGR_RW_FCS_ERR:
        case MEBA_EVENT_EGR_TIMESTAMP_CAPTURED:
        case MEBA_EVENT_EGR_FIFO_OVERFLOW: {
            mesa_phy_ts_event_t event = meba_generic_phy_ts_source_to_event(inst, event_id);
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (board->port[port_no].ts_phy) {
                    if ((rc = mesa_phy_ts_event_enable_set(PHY_INST, port_no, enable, event)) != MESA_RC_OK) {
                        T_E(inst, "mesa_phy_ts_event_enable_set(%d, %d, %d) = %d", port_no, enable, event, rc);
                    }
                }
            }
            return rc;
        }

        case MEBA_EVENT_PUSH_BUTTON:
            // Push button is Port 7 bit 0, See schematic.
            if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, 7, 0, enable)) != MESA_RC_OK) {
                T_E(inst, "mesa_sgpio_event_enable = %d", rc);
            }
            return rc;

        default:
            T_I(inst, "Unsupported Interrupt event %d", event_id);
            return MESA_RC_NOT_IMPLEMENTED;
    }

    return MESA_RC_OK;
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

    // Push button is Port 7 bit 0 (see schematic).
    if (sgpio_events[7]) {
        T_I(inst, "Pushbutton IRQ");
        // Disable interrupt.
        if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, 7, 0, false)) != MESA_RC_OK) {
            T_E(inst, "mesa_sgpio_event_enable = %d", rc);
        }
        signal_notifier(MEBA_EVENT_PUSH_BUTTON, 0);
        handled++;
    }

    // Poll SGPIO LOS from SFP ports
    for (port_no = 0; port_no < 10; port_no++) {
        if (port_no != 7 && sgpio_events[port_no]) {
            uint32_t instance_no;
            // SGPIO port no
            if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, port_no, 0, false)) != MESA_RC_OK) {
                T_E(inst, "mesa_sgpio_event_enable  = %d", rc);
                // continue
            }
            if (port_no < 4) {
                instance_no = 7 - port_no;
            } else {
                instance_no = port_no;
            }
            if (board->port_map_cnt < 11 && instance_no >= 4) {
                instance_no -= 4;    // Reduced port map skips Cupper PHY ports
            }
            T_I(inst, "LOS IRQ port %d", instance_no);
            signal_notifier(MEBA_EVENT_LOS, instance_no);
            handled++;
        }
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc ext0_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    int handled = 0;
    mesa_port_no_t port_no;

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (board->port[port_no].ts_phy) {
            if (meba_generic_phy_timestamp_check(inst, port_no, signal_notifier) == MESA_RC_OK)
                handled++;
        }
        if (is_phy_port(board->port[port_no].map.cap)) {
            if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK)
                handled++;
        }
    }
    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc serval_irq_handler(meba_inst_t inst,
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
        default:;
    }

    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc serval_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
        case MESA_IRQ_PTP_RDY:
        case MESA_IRQ_OAM:
        case MESA_IRQ_SGPIO:
        case MESA_IRQ_EXT0:
            rc = MESA_RC_OK;
        default:;
    }
    return rc;
}

static mesa_rc loop_port_update(meba_inst_t inst, meba_board_state_t *board, const char *tag)
{
    meba_ports_t      *entry;
    mesa_port_no_t    port_no, loop_port;
    mesa_rc           rc;

    if ((rc = meba_conf_get_u32(inst, tag, &loop_port)) != MESA_RC_OK || loop_port == MESA_PORT_NO_NONE) {
        // Not implemented by application or doesn't want a loop port.
        return rc;
    }

    // Loop ports must be the last ports and not copper ports
    for (port_no = board->port_map_cnt - 1; port_no > 0; port_no--) {
        mesa_bool_t swap = false;

        entry = &board->port[port_no];

        if (entry->map.mac_if == MESA_PORT_INTERFACE_SGMII) {
            if (port_no == loop_port) {
                swap = true;
            }
        }

        if (swap) {
            meba_ports_t tmp = *entry;
            *entry = board->port[port_no - 1];
            board->port[port_no - 1] = tmp;
        }
    }

    // One less exposed port
    board->port_cnt--;
    return MESA_RC_OK;
}

meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t inst;
    meba_board_state_t *board;
    mesa_port_no_t port_no;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate pulic state
    if ((inst = meba_state_alloc(callouts,
                                 "Serval1",
                                 MESA_TARGET_SERVAL,
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    // Board detection - NO API
    /* Enable GPIO_9 and GPIO_10 as MIIM controllers for being able to access the PHY */
    (void)mebaux_gpio_mode_set(inst, &rawio, 9, MESA_GPIO_ALT_1);
    (void)mebaux_gpio_mode_set(inst, &rawio, 10, MESA_GPIO_ALT_1);
    uint16_t gpio_in_reg = 0;
    (void) mebaux_miim_wr(inst, &rawio, MESA_MIIM_CONTROLLER_1, 16, 31, 0x10); // Setup GPIO page
    if (mebaux_miim_rd(inst, &rawio, MESA_MIIM_CONTROLLER_1, 16, 15, &gpio_in_reg) == MESA_RC_OK) {
        if (gpio_in_reg & 0x0200) {
            board->type = BOARD_TYPE_SERVAL_NID;
        }
        (void) mebaux_miim_wr(inst, &rawio, MESA_MIIM_CONTROLLER_1, 16, 31, 0); // Setup STANDARD page
    } else {
        board->type = BOARD_TYPE_SERVAL_REF;
    }

    board->port_map_cnt = (inst->props.target == MESA_TARGET_SERVAL_LITE ? 7 : 11);
    board->port_cnt = board->port_map_cnt;
    if (board->type == BOARD_TYPE_SERVAL_REF) {
        inst->props.board_type = VTSS_BOARD_SERVAL_REF; // Exposed temporarily
    } else {
        inst->props.board_type = VTSS_BOARD_SERVAL_PCB106_REF; // Exposed temporarily
    }
    board->fan_spec = &fan_conf;
    board->port = (meba_ports_t*) calloc(board->port_map_cnt, sizeof(meba_ports_t));
    if (board->port == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        free(inst);
        return NULL;
    }
    T_I(inst, "Board: %s, type %d, target %4x, %d ports", inst->props.name, board->type, inst->props.target, board->port_map_cnt);

    T_D(inst, "Initialize portmap");
    for (port_no = 0; port_no < board->port_map_cnt; port_no++) {
        meba_port_entry_t *entry = &board->port[port_no].map;
        if (port_no == board->port_map_cnt - 1) {
            /* Last port maps to chip port 10: NPI port */
            entry->map.chip_port = 10;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_1;
            entry->map.miim_addr = 28;
            entry->mac_if = MESA_PORT_INTERFACE_SGMII;
            entry->cap = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        } else if (port_no < 4 && inst->props.target != MESA_TARGET_SERVAL_LITE) {
            /* Chip port 7-4: Copper */
            if (board->type == BOARD_TYPE_SERVAL_NID) {
                entry->cap = MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER;
            } else {
                entry->cap = MEBA_PORT_CAP_TRI_SPEED_COPPER;
            }
            entry->map.chip_port = (7 - port_no);
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_1;
            entry->map.miim_addr = (16 + port_no);
            entry->mac_if = MESA_PORT_INTERFACE_SGMII;
        } else if (port_no < board->port_map_cnt - 3) {
            /* Chip port 3-0: 1G SFP */
            entry->map.chip_port = (board->port_map_cnt - 4 - port_no);
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->mac_if = MESA_PORT_INTERFACE_SERDES;
            entry->cap = MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH;
        } else {
            /* Chip port 8-9: 2.5G SFP */
            entry->map.chip_port = (port_no + 11 - board->port_map_cnt);
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->mac_if = MESA_PORT_INTERFACE_SERDES;
            entry->cap = MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH;
        }
    }

    loop_port_update(inst, board, "mep_loop_port");
    loop_port_update(inst, board, "mirror_loop_port");

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = serval_capability;
    inst->api.meba_port_entry_get             = serval_port_entry_get;
    inst->api.meba_reset                      = serval_reset;
    inst->api.meba_sensor_get                 = serval_sensor_get;
    inst->api.meba_sfp_i2c_xfer               = serval_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = serval_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = serval_sfp_status_get;
    inst->api.meba_port_admin_state_set       = serval_port_admin_state_set;
    inst->api.meba_status_led_set             = serval_status_led_set;
    inst->api.meba_port_led_update            = serval_port_led_update;
    inst->api.meba_led_mode_set               = serval_led_mode_set;
    inst->api.meba_led_intensity_set          = serval_led_intensity_set;
    inst->api.meba_fan_param_get              = serval_fan_param_get;
    inst->api.meba_fan_conf_get               = serval_fan_conf_get;
    inst->api.meba_irq_handler                = serval_irq_handler;
    inst->api.meba_irq_requested              = serval_irq_requested;
    inst->api.meba_event_enable               = serval_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get         = serval_ptp_rs422_conf_get;

    inst->api_synce = meba_synce_get();
    inst->api_tod = meba_tod_get();

    return inst;
}
