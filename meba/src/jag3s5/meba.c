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
#include <unistd.h>

#include <mscc/ethernet/board/api.h>

#include "meba_aux.h"
#include "meba_generic.h"

#define STATUSLED_G_GPIO 12
#define STATUSLED_R_GPIO 13
#define JR3_NPI_CHIP_PORT 64

/* LED colors */
typedef enum {
    LED_GREEN,
    LED_YELLOW,
    LED_MAX
} led_color_t;

typedef enum {
    SFP_DETECT,
    SFP_FAULT,
    SFP_LOS
} sfp_signal_t;

typedef struct {
    meba_port_entry_t map;
    mesa_port_status_t status;
    mesa_bool_t activity;
} jr3_port_info_t;

// The PCB type
typedef enum {
    BOARD_TYPE_JAGUAR3_PCB134,  /* 20xSFP + NPI */
    BOARD_TYPE_JAGUAR3_PCB135,  /* 48x1G + 4x10G + 4x25G + NPI */
    BOARD_TYPE_JAGUAR3_EMULATION,
} board_type_t;

/* JR3 Ref board port configurations  */
typedef enum {
    VTSS_BOARD_CONF_20x10G_NPI,
    VTSS_BOARD_CONF_8x25G_NPI,
    VTSS_BOARD_CONF_6x10G_NPI,
    VTSS_BOARD_CONF_9x10G_NPI,
    VTSS_BOARD_CONF_12x10G_NPI,
    VTSS_BOARD_CONF_LAST
} board_port_cfg_t;

typedef struct {
    void (*board_init)(meba_inst_t inst);
    void (*init_port)(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry);
    meba_port_led_update_t led_update;
} board_func_t;

typedef struct meba_board_state {
    board_type_t          type;
    board_port_cfg_t      port_cfg;
    int                   port_cnt;
    jr3_port_info_t       *port;
    const board_func_t    *func;
} meba_board_state_t;


/* static const meba_aux_rawio_t rawio = { */
/*     .gcb = 0x01, */
/*     .miim = { */
/*         .status = 0x32+0, */
/*         .cmd    = 0x32+2, */
/*         .data   = 0x32+3, */
/*         .cfg    = 0x32+4, */
/*     }, */
/*     .gpio = { */
/*         .alt_0  = 0x1e, */
/*         .alt1_0 = 0x20, */
/*     } */
/* }; */

static mesa_rc jr3_sgpio_event_enable(const meba_inst_t        inst,
                                      const mesa_sgpio_group_t group,
                                      const mesa_port_no_t     port,
                                      const uint32_t           bit,
                                      mesa_bool_t              enable)
{
    T_N(inst, "grp %d p%d.b%d %sable", group, port, bit, enable ? "en" : "dis");
    return mesa_sgpio_event_enable(NULL, 0, group, port, bit, enable);
}

/* --------------------------- Board specific ------------------------------- */

static void jr3_emul_init_port(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    entry->map.chip_port       = port_no;
    entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
    entry->map.miim_addr       = port_no;
    entry->map.max_bw          = MESA_BW_1G;
    entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
    entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
}

static void jr3_emul_board_init(meba_inst_t inst)
{
    T_I(inst, "TBD");
}

static mesa_rc jr3_emul_led_update(meba_inst_t inst,
                                   mesa_port_no_t port_no,
                                   const mesa_port_status_t *status,
                                   const mesa_port_counters_t *counters,
                                   const meba_port_admin_state_t *state)
{
    T_N(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static void jr3_pcb134_init_port(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    meba_board_state_t *board = INST2BOARD(inst);

    switch (board->port_cfg) {
    case VTSS_BOARD_CONF_6x10G_NPI:
    case VTSS_BOARD_CONF_9x10G_NPI:
    case VTSS_BOARD_CONF_12x10G_NPI:
    case VTSS_BOARD_CONF_20x10G_NPI:
        if (port_no < board->port_cnt - 1) {
            // 10G ports
            entry->map.chip_port       = port_no < 4 ? port_no + 12 : port_no + 44; // 12-15(10G), 48-55(10G), 56-63(25G)
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_10G;
            entry->mac_if              = port_no < 4 ? MESA_PORT_INTERFACE_SGMII_CISCO : MESA_PORT_INTERFACE_SFI;
            entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
        } else if (port_no == board->port_cnt - 1) {
            // NPI port
            entry->map.chip_port       = 64;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_3;
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    break;
    case VTSS_BOARD_CONF_8x25G_NPI:
        if (port_no < board->port_cnt - 1) {
            // 25G ports
            entry->map.chip_port       = port_no + 44; // 56-63(25G)
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_25G;
            entry->mac_if              = MESA_PORT_INTERFACE_SFI;
            entry->cap                 = (MEBA_PORT_CAP_25G_FDX | MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G |
                                          MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
        } else if (port_no == board->port_cnt - 1) {
            // NPI port
            entry->map.chip_port       = 64;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_3;
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    break;

    default:
        T_E(inst, "Board type (%d) not supported!", board->type);
    }
}

static void jr3_pcb134_board_init(meba_inst_t inst)
{
    mesa_sgpio_conf_t conf;
    uint32_t port;

    // Configure GPIOs for MIIM/MDIO bus 1
    (void)mesa_gpio_mode_set(NULL, 0, 56, MESA_GPIO_ALT_0);
    (void)mesa_gpio_mode_set(NULL, 0, 57, MESA_GPIO_ALT_0);
    /* GPIOs for SGPIO Group 0. */
    (void)mesa_gpio_mode_set(NULL, 0, 0, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)mesa_gpio_mode_set(NULL, 0, 1, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 2, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)mesa_gpio_mode_set(NULL, 0, 3, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / LD
    /* GPIOs for SGPIO Group 1. */
    (void)mesa_gpio_mode_set(NULL, 0, 4, MESA_GPIO_ALT_0);  // SGPIO Grp 1 / CLK
    (void)mesa_gpio_mode_set(NULL, 0, 5, MESA_GPIO_ALT_0);  // SGPIO Grp 1 / DO
    /* GPIOs for SGPIO Group 2. */
    (void)mesa_gpio_mode_set(NULL, 0, 30, MESA_GPIO_ALT_0); // SGPIO Grp 2 / Clk
    (void)mesa_gpio_mode_set(NULL, 0, 31, MESA_GPIO_ALT_0); // SGPIO Grp 2 / LD
    (void)mesa_gpio_mode_set(NULL, 0, 32, MESA_GPIO_ALT_0); // SGPIO Grp 2 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 33, MESA_GPIO_ALT_0); // SGPIO Grp 2 / DI

    /* SGPIO group 0 controls Port LEDs for DEV64, D12-D15  */
    /* p0 -> D64, p12-15 -> D12-D15 */
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        for (port = 12; port < 16; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_ON;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }

    /* SGPIO group 1 controls Port LEDs for DEV48-DEV63  */
    /* p16-31 -> D48-D63 */
    if (mesa_sgpio_conf_get(NULL, 0, 1, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        for (port = 16; port < 32; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON; // Turn on while booting
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_ON; // Turn on while booting
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 1, &conf);
    }


    /* Setup SGPIO group 2 controls SFP signals */
    if (mesa_sgpio_conf_get(NULL, 0, 2, &conf) == MESA_RC_OK) {
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 3;
        for (port = 12; port < 32; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].int_pol_high[0] = true;        // LOS interrupt is active high (input)
            conf.port_conf[port].int_pol_high[2] = true;        // TX_FAULT interrupt is active high (input)
            conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_OFF; // TXDisable is enabled through jr3_port_admin_state_set() (output)
            conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_ON;  // Ratesel0 always eanbled (output)
            conf.port_conf[port].mode[2] = MESA_SGPIO_MODE_ON;  // Ratesel1 always eanbled (output)
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 2, &conf);
    }

    //    dac_init(inst); TBD-BJO
}

static void jr3_pcb135_init_port(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    T_N(inst, "TBD");
}

static void jr3_pcb135_board_init(meba_inst_t inst)
{
   T_N(inst, "TBD");
}

static mesa_bool_t port_activity_auto(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      const mesa_port_status_t *status)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_status_t *old_status = &board->port[port_no].status;
    mesa_bool_t link_activity = false;

    if (old_status->link  != status->link  ||
        old_status->speed != status->speed ||
        old_status->fdx   != status->fdx   ||
        old_status->fiber != status->fiber) {
        link_activity = true;
        *old_status = *status;
    }
    if (!link_activity && !board->port[port_no].activity) {
        return false; // No Activity
    }
    board->port[port_no].activity = link_activity;
    return true; // Activity
}

static mesa_rc jr3_led_update(meba_inst_t inst,
                              mesa_port_no_t port_no,
                              const mesa_port_status_t *status,
                              const mesa_port_counters_t *counters,
                              const meba_port_admin_state_t *state)
{
    mesa_rc             rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t            sgpio_group = 0, sgpio_port = 0;
    meba_port_entry_t  *entry = &board->port[port_no].map;
    mesa_sgpio_conf_t   conf;
    mesa_sgpio_mode_t   mode_green = MESA_SGPIO_MODE_OFF, mode_yellow = MESA_SGPIO_MODE_OFF;

    if (!port_activity_auto(inst, port_no, status)) {
        return rc;
    }

    if (entry->map.chip_port >= 12 && entry->map.chip_port <= 15) {
        sgpio_group = 0;
        sgpio_port = entry->map.chip_port;      // sgpio 12-15

    } else if (entry->map.chip_port >= 48 && entry->map.chip_port <= 63) {
        sgpio_group = 1;
        sgpio_port = entry->map.chip_port - 32; // sgpio 16-31
    } else {
        // TBD-BJO NPI port
        return rc;
    }

    /* If link then auto update LED */
    if (status->link && state->enable) {
        if (status->speed >= MESA_SPEED_1G) {
            mode_green = MESA_SGPIO_MODE_0_ACTIVITY;
        } else {
            mode_yellow = MESA_SGPIO_MODE_0_ACTIVITY;
        }
    }

    if ((rc = mesa_sgpio_conf_get(NULL, 0, sgpio_group, &conf)) == MESA_RC_OK) {
        conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_green;
        conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_yellow;
        rc = mesa_sgpio_conf_set(NULL, 0, sgpio_group, &conf);
    }
    return rc;
}

static const board_func_t board_funcs[] = {
    [BOARD_TYPE_JAGUAR3_EMULATION] = {
        .board_init = jr3_emul_board_init,
        .init_port  = jr3_emul_init_port,
        .led_update = jr3_emul_led_update,
    },
    [BOARD_TYPE_JAGUAR3_PCB134] = {
        .board_init = jr3_pcb134_board_init,
        .init_port  = jr3_pcb134_init_port,
        .led_update = jr3_led_update,
    },
    [BOARD_TYPE_JAGUAR3_PCB135] = {
        .board_init = jr3_pcb135_board_init,
        .init_port  = jr3_pcb135_init_port,
        .led_update = jr3_led_update,
    },
};

static mesa_bool_t get_sfp_status(meba_inst_t inst,
                                  mesa_port_no_t port_no,
                                  mesa_sgpio_port_data_t *data,
                                  sfp_signal_t sfp)
{
    uint32_t sgport = port_no + 12;

    if (sfp == SFP_DETECT) {
        return !data[sgport].value[1]; // The SFP detect signal is inverted
    } else if (sfp == SFP_FAULT) {
        return data[sgport].value[2];
    } else if (sfp == SFP_LOS) {
        return data[sgport].value[0];
    } else {
        T_E(inst, "Unknown signal");
    }
    return false;
}

static mesa_rc jr3_phy_event_enable(meba_inst_t inst,
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
            if ((rc = mesa_phy_event_enable_set(NULL, port_no, phy_event, enable)) != MESA_RC_OK) {
                T_E(inst, "mesa_phy_event_enable_set = %d", rc);
                break;
            }
        }
    }
    return rc;
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
        case BOARD_TYPE_JAGUAR3_PCB134:
            if (gpio_events[7]) {
                if ((rc = mesa_gpio_event_enable(NULL, 0, 7, false)) != MESA_RC_OK) {
                    T_E(inst, "mesa_gpio_event_enable = %d", rc);
                }
                signal_notifier(MEBA_EVENT_PUSH_BUTTON, 0);
                handled++;
            }
            break;

        default:
            T_E(inst, "Board type (%d) not supported!", board->type);
            return MESA_RC_ERROR;
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}


/* ---------------------------   Exposed API  ------------------------------- */

static uint32_t jr3_capability(meba_inst_t inst, int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_POE:
            return 0;
        case MEBA_CAP_1588_CLK_ADJ_DAC:
            return 0;
        case MEBA_CAP_1588_REF_CLK_SEL:
            return 0;
        case MEBA_CAP_TEMP_SENSORS:
            return 1;
        case MEBA_CAP_BOARD_PORT_COUNT:
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            return board->port_cnt;
        case MEBA_CAP_LED_MODES:
            return 0;
        case MEBA_CAP_DYING_GASP:
            return 0;
        case MEBA_CAP_FAN_SUPPORT:
            return board->type != BOARD_TYPE_JAGUAR3_EMULATION;
        case MEBA_CAP_LED_DIM_SUPPORT:
            return 0;
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
            return 0;
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
            return 0;
        case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:
            return -1;
        case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_DPLL:
            return -1;
        case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:
            return 0;
        case MEBA_CAP_ONE_PPS_INT_ID:
            return MEBA_EVENT_PTP_PIN_1;
        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:
            return 0;
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:
            return 0;
        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc jr3_port_entry_get(meba_inst_t inst,
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

static mesa_rc jr3_sensor_get(meba_inst_t inst,
                              meba_sensor_t type,
                              int six,
                              int *value)
{
    mesa_rc rc = MESA_RC_ERROR;
    int16_t temp = 0;
    T_N(inst, "Called %d:%d", type, six);

    rc = mesa_temp_sensor_get(NULL, &temp);

    if (rc == MESA_RC_OK) {
        T_N(inst, "Temp %d:%d = %d", type, six, temp);
        *value = temp;
    } else {
        T_N(inst, "Temp %d:%d = [not read:%d]", type, six, rc);
    }
    return rc;
}

static mesa_rc jr3_sfp_i2c_xfer(meba_inst_t inst,
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
    uint32_t chip_port = board->port[port_no].map.map.chip_port;
    if (write) {    // cnt ignored
        uint8_t i2c_data[3];
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        rc = inst->iface.i2c_write(chip_port, i2c_addr, i2c_data, 3);
    } else {
        rc = inst->iface.i2c_read(chip_port, i2c_addr, addr, data, cnt);
    }

    T_D(inst, "i2c %s port %d - address 0x%02x:0x%02x, %d bytes return %d", write ? "write" : "read", port_no, i2c_addr, addr, cnt, rc);
    return rc;
}

static mesa_rc jr3_sfp_insertion_status_get(meba_inst_t inst, mesa_port_list_t *present)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];

    T_N(inst, "Called");
    mesa_port_list_clear(present);

    if ((rc = mesa_sgpio_read(NULL, 0, 2, data)) == MESA_RC_OK) {
        mesa_port_no_t port_no;
        /* The 'Module Detect' is inverted i.e. '0' means detected */
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            uint32_t chip_port = board->port[port_no].map.map.chip_port;
            if (chip_port == JR3_NPI_CHIP_PORT) {
                continue;
            }
            mesa_port_list_set(present, port_no, !data[port_no].value[1]);
        }
    }
    return rc;
}

static mesa_rc jr3_sfp_status_get(meba_inst_t inst,
                                  mesa_port_no_t port_no,
                                  meba_sfp_status_t *status)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);

    if (port_no < board->port_cnt) {
        meba_port_entry_t *entry = &board->port[port_no].map;
        status->present  = false;
        status->los      = false;
        status->tx_fault = false;
        if (entry->cap & MEBA_PORT_CAP_SFP_DETECT) {
            mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];
            rc = mesa_sgpio_read(NULL, 0, 2, data); // SGPIO group 2
            if (rc == MESA_RC_OK) {
                status->present  = get_sfp_status(inst, port_no, data, SFP_DETECT);
                status->tx_fault = get_sfp_status(inst, port_no, data, SFP_FAULT);
                status->los      = get_sfp_status(inst, port_no, data, SFP_LOS);
            }
            T_N(inst, "port(%d): rc %d, present:%d los:%d tx_fault:%d", port_no, rc,
                status->present, status->los, status->tx_fault);
        }
    }
    return rc;
}

// Applies only to SFPs where TxDisable is enabled/disabled
static mesa_rc jr3_port_admin_state_set(meba_inst_t inst,
                                        mesa_port_no_t port_no,
                                        const meba_port_admin_state_t *state)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    if (board->port[port_no].map.map.miim_controller == MESA_MIIM_CONTROLLER_NONE) {
        mesa_sgpio_conf_t  conf;
        mesa_sgpio_mode_t  sgpio_mode = (state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
        if (board->type == BOARD_TYPE_JAGUAR3_PCB134) {
            if ((rc = mesa_sgpio_conf_get(NULL, 0, 2, &conf)) == MESA_RC_OK) {
                uint32_t sgport = port_no + 12;
                conf.port_conf[sgport].mode[0] = sgpio_mode; // TxDisable maps to bit 0, SGPIO 2
                rc = mesa_sgpio_conf_set(NULL, 0, 2, &conf);
            }
        }
    }
    return rc;
}

static mesa_rc jr3_status_led_set(meba_inst_t inst,
                                  meba_led_type_t type,
                                  meba_led_color_t color)
{
    mesa_rc rc = MESA_RC_ERROR;
    if (type == MEBA_LED_TYPE_FRONT && color < MEBA_LED_COLOR_COUNT) {
        T_I(inst, "LED:%d, color=%d", type, color);
        switch (color) {
            case MEBA_LED_COLOR_OFF:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, false);
                rc = mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, false);
                break;
            case MEBA_LED_COLOR_GREEN:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, false);
                rc = mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, true);
                break;
            case MEBA_LED_COLOR_RED:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, true);
                rc = mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, false);
                break;
            case MEBA_LED_COLOR_YELLOW:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, true);
                rc = mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, true);
                break;
            default:
                rc = MESA_RC_ERROR;
        }
    }
    return rc;
}

static mesa_rc jr3_port_led_update(meba_inst_t inst,
                                   mesa_port_no_t port_no,
                                   const mesa_port_status_t *status,
                                   const mesa_port_counters_t *counters,
                                   const meba_port_admin_state_t *state)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "port(%d): Link - %d", port_no, status->link);
    return board->func->led_update(inst, port_no, status, counters, state);
}

static mesa_rc jr3_led_intensity_set(meba_inst_t inst,
                                     mesa_phy_led_intensity intensity)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    return rc;
}

static mesa_rc jr3_fan_param_get(meba_inst_t inst,
                                 meba_fan_param_t *param)
{
    T_N(inst, "Called");
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc jr3_fan_conf_get(meba_inst_t inst,
                                mesa_fan_conf_t *conf)
{
    T_N(inst, "Called");
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc jr3_ptp_rs422_conf_get(meba_inst_t inst,
                                      meba_ptp_rs422_conf_t *conf)
{
    T_N(inst, "Called");
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc jr3_reset(meba_inst_t inst, meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;

    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            board->func->board_init(inst);
            break;
        case MEBA_PORT_RESET:
            break;
        case MEBA_PORT_RESET_POST:
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            (void)jr3_status_led_set(inst, MEBA_LED_TYPE_FRONT, MEBA_LED_COLOR_YELLOW);
            break;
        case MEBA_PORT_LED_INITIALIZE:
            break;
        case MEBA_FAN_INITIALIZE:
            // TBD-BJO
            break;
        case MEBA_SENSOR_INITIALIZE:
//            (void)vtss_temp_sensor_init(NULL, true);
            break;
        case MEBA_INTERRUPT_INITIALIZE:
            break;
        case MEBA_SYNCE_DPLL_INITIALIZE:
            break;
    }
    return rc;
}

// IRQ Support
static mesa_rc jr3_event_enable(meba_inst_t inst,
                                meba_event_t event_id,
                                mesa_bool_t enable)
{
    mesa_rc               rc = MESA_RC_OK;
    meba_board_state_t    *board = INST2BOARD(inst);
    int                   gpio, sgpio;

    T_I(inst, "%sable event %d", enable ? "en" : "dis", event_id);

    switch (event_id) {
    case MEBA_EVENT_SYNC:
    case MEBA_EVENT_EXT_SYNC:
    case MEBA_EVENT_EXT_1_SYNC:
    case MEBA_EVENT_CLK_ADJ:
    case MEBA_EVENT_VOE:
        return rc;    // Dummy for now

    case MEBA_EVENT_LOS: // Loss Of Signal (SFP)
        switch (board->type) {
        case BOARD_TYPE_JAGUAR3_PCB134:
            for (sgpio = 12; sgpio <= 31; sgpio++) {
                /*  mesa_sgpio_event_enable(inst, chip, group, port, bit, enable */
                if (mesa_sgpio_event_enable(NULL, 0, 2, sgpio, 0, enable) != MESA_RC_OK) {
                    T_E(inst, "Could not enable event for sgpio #%d", sgpio);
                }
            }
            break;
        default:
            return MESA_RC_NOT_IMPLEMENTED;
        }

    case MEBA_EVENT_FLNK: // Phy link down event
        rc = jr3_phy_event_enable(inst, board, MESA_PHY_LINK_FFAIL_EV, enable);
        break;

    case MEBA_EVENT_PUSH_BUTTON:
        switch (board->type) {
        case BOARD_TYPE_JAGUAR3_PCB134:
            gpio = 7;
            break;

        default:
            gpio = -1;
        }

        if (gpio >= 0) {
            T_I(inst, "%sable Push_button(GPIO_%d) interrupt", enable ? "en" : "dis", gpio);
            if (mesa_gpio_event_enable(NULL, 0, gpio, enable) != MESA_RC_OK) {
                T_E(inst, "Could not control event for gpio #%d", gpio);
            }
        }
        break;

    default:
        return MESA_RC_NOT_IMPLEMENTED;    // Will occur as part of probing
    }

    T_I(inst, "%sable event %d", enable ? "en" : "dis", event_id);
    return rc;
}

static mesa_rc sgpio2_handler(meba_inst_t inst,
                              meba_board_state_t *board,
                              meba_event_signal_t signal_notifier)
{
    mesa_rc           rc;
    mesa_port_no_t    port_no;
    uint32_t          bit, sgpio_port;
    mesa_bool_t       sgpio_events_bit[3][MESA_SGPIO_PORTS];
    int               handled = 0;

    // Getting SGPIO bit 0 - 2
    for (bit = 0; bit <= 2; bit++) {
        if ((rc = mesa_sgpio_event_poll(NULL, 0, 2, bit, sgpio_events_bit[bit])) != MESA_RC_OK) {
            T_E(inst, "mesa_sgpio_event_poll = %d", rc);
            return rc; // Don't even re-enable SGPIO2 interrupt
        }
    }

    // Disable the interrupt while handling the event
    for (sgpio_port = 0; sgpio_port < MESA_SGPIO_PORTS; sgpio_port++) {
        for (bit = 0; bit <= 2; bit++) {
            if (sgpio_events_bit[bit][sgpio_port]) {
                T_D(inst, "SGPIO2 event on p%db%d", sgpio_port, bit);
                if ((rc = jr3_sgpio_event_enable(inst, 2, sgpio_port, bit, false)) != MESA_RC_OK) {
                    T_E(inst, "mesa_sgpio_event_enable = %d", rc);
                    // Go on anyway
                }
            }
        }
    }

    switch (board->type) {
        case BOARD_TYPE_JAGUAR3_PCB134:
            for (sgpio_port = 12; sgpio_port <= 31; sgpio_port++) {
                port_no = sgpio_port - 12;
                // Check for SFP/SFP+ LOS - bit 0
                if (sgpio_events_bit[0][sgpio_port]) {
                    signal_notifier(MEBA_EVENT_LOS, port_no);
                    handled++;
                }
                // Check MODDET - bit 1
                if (sgpio_events_bit[1][sgpio_port]) {
                    if (!handled) {
                        // LOS, MODDET and TX_FAULT all share the same interrupt,
                        // so some signal notifier needs to be called to ensure
                        // that interrupts are reenabled. When module is either
                        // removed or inserted there is no harm in calling the LOS
                        // signal handler and let that reenable interrupts.
                        handled++;
                        signal_notifier(MEBA_EVENT_LOS, port_no);
                    }
                }
                // Check TXFAULT - bit 2
                if (sgpio_events_bit[2][sgpio_port]) {
                    if (!handled) {
                        // LOS, MODDET and TX_FAULT all share the same interrupt,
                        // so some signal notifier needs to be called to ensure
                        // that interrupts are reenabled. When TXFAULT is detected
                        // there is no harm in calling the LOS
                        // signal handler and let that reenable interrupts.
                        handled++;
                        signal_notifier(MEBA_EVENT_LOS, port_no);
                    }
                }
            }
            break;
        default:
            T_E(inst, "Board type (%d) not supported!", board->type);
            return MESA_RC_ERROR; // Don't re-enable SGPIO2 interrupt
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc ext0_handler(meba_inst_t inst,
                            meba_board_state_t *board,
                            meba_event_signal_t signal_notifier)
{
    // Check NPI phy
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

static mesa_rc jr3_irq_handler(meba_inst_t inst,
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
        case MESA_IRQ_GPIO:
            return gpio_handler(inst, board, signal_notifier);
        case MESA_IRQ_SGPIO2:
            return sgpio2_handler(inst, board, signal_notifier);
       case MESA_IRQ_EXT0:
           return ext0_handler(inst, board, signal_notifier);
    default:;
    }

    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc jr3_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
        case MESA_IRQ_PTP_RDY:
        case MESA_IRQ_OAM:
        case MESA_IRQ_GPIO:
        case MESA_IRQ_SGPIO2:
        case MESA_IRQ_EXT0:
            rc = MESA_RC_OK;
        default:;
    }
    return rc;
}

// Public Initialize
meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t         inst;
    meba_board_state_t *board;
    mesa_port_no_t      port_no;
    int                 i;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate public state and set the board name and target.
    // The name and target are fetched from the application (through MESA capabilities)
    if ((inst = meba_state_alloc(callouts,
                                 "SparX-5",          // Default name
                                 MESA_TARGET_7558_04,// Default target
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state. 'board' provides the private info from this file.
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    // Get the type of pcb-board from the application (through MESA capabilities)
    if (meba_conf_get_hex(inst, "type", &i) == MESA_RC_OK) {
        board->type = (board_type_t) i;
    }

    // Get the port configuration to be applied on this PCB
    if (meba_conf_get_hex(inst, "port_cfg", &i) == MESA_RC_OK) {
        board->port_cfg = (board_port_cfg_t) i;
    } else {
        board->port_cfg = VTSS_BOARD_CONF_20x10G_NPI;   // Default
    }

    switch (board->type) {
    case BOARD_TYPE_JAGUAR3_PCB134:
        switch (board->port_cfg) {
        case VTSS_BOARD_CONF_20x10G_NPI:
            board->port_cnt = 21;
            break;
        case VTSS_BOARD_CONF_8x25G_NPI:
            board->port_cnt = 9;
            break;
        case VTSS_BOARD_CONF_6x10G_NPI:
            board->port_cnt = 7;
            break;
        case VTSS_BOARD_CONF_9x10G_NPI:
            board->port_cnt = 10;
            break;
        case VTSS_BOARD_CONF_12x10G_NPI:
            board->port_cnt = 13;
            break;
        default:
            T_E(inst, "Unknown port config: %d", board->port_cfg);
            goto error_out;
        }
        break;
    case BOARD_TYPE_JAGUAR3_PCB135:
        board->port_cnt = 57; // 48cu + 4x10G + 4x25G + NPI
        break;

    default:
        T_E(inst, "Unknown board type: %d", board->type);
        goto error_out;
    }


    // Hook up the local functions in this file
    board->func = &board_funcs[board->type];

    board->port = (jr3_port_info_t*) calloc(board->port_cnt, sizeof(jr3_port_info_t));
    if (board->port == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    inst->props.board_type = board->type;
    // Fill out port mapping table
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        board->func->init_port(inst, port_no, &board->port[port_no].map);
    }
    T_I(inst, "Board: %s, type %d, target %4x, mux %d, %d ports", inst->props.name, board->type, inst->props.target,
        inst->props.mux_mode, board->port_cnt);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = jr3_capability;
    inst->api.meba_port_entry_get             = jr3_port_entry_get;
    inst->api.meba_reset                      = jr3_reset;
    inst->api.meba_sensor_get                 = jr3_sensor_get;
    inst->api.meba_sfp_i2c_xfer               = jr3_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = jr3_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = jr3_sfp_status_get;
    inst->api.meba_port_admin_state_set       = jr3_port_admin_state_set;
    inst->api.meba_status_led_set             = jr3_status_led_set;
    inst->api.meba_port_led_update            = jr3_port_led_update;
    inst->api.meba_led_intensity_set          = jr3_led_intensity_set;
    inst->api.meba_fan_param_get              = jr3_fan_param_get;
    inst->api.meba_fan_conf_get               = jr3_fan_conf_get;
    inst->api.meba_irq_handler                = jr3_irq_handler;
    inst->api.meba_irq_requested              = jr3_irq_requested;
    inst->api.meba_event_enable               = jr3_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get         = jr3_ptp_rs422_conf_get;
    inst->api_synce                           = meba_synce_get();
    inst->api_tod                             = meba_tod_get();
    return inst;

error_out:
    free(inst);
    return NULL;
}
