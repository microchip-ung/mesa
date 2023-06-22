// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <microchip/ethernet/board/api.h>

#include "meba_aux.h"

#define PDS_408G_NUM_COPPER_PORTS   (10) // 8x1G+PoE, 2x1G
#define PDS_408G_NUM_PORTS          (PDS_408G_NUM_COPPER_PORTS+1) // 8x1G+PoE, 2x1G, 1xSFP
#define PDS_408G_SFP_LOG_PORT_INDEX (10) // starting from zero
#define PDS_408G_NUM_POE_PORT       (8)  // logical port 0-7
#define PDS_408G_BUTTON_PRESSED         (false)
#define PDS_408G_BUTTON_RELEASED        (true)
#define PDS_408G_POE_RESET_IO           (4)
#define PDS_408G_SYSTEM_LED_IO          (7)
#define PDS_408G_POE_DISABLE_PORTS_IO   (10)  // GPI10 , output, 0=POE_Disable. 1=PoE_Enable
#define PDS_408G_RESET_BUTTON_IP        (12)

/** \brief Number of L26 or Serval PTP pins, that can be used as 1PPS or clock output/input. */
#define VTSS_TS_IO_ARRAY_SIZE       1

/* SGPIO LED mapping */
typedef struct {
    uint8_t port;
    uint8_t bit;
} sgpio_mapping_t;

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

static const uint32_t pin_conf[VTSS_TS_IO_ARRAY_SIZE] = {
(MEBA_PTP_IO_CAP_PIN_IN | MEBA_PTP_IO_CAP_PIN_OUT)
};

static const meba_event_t init_int_source_id[VTSS_TS_IO_ARRAY_SIZE] = {MEBA_EVENT_SYNC};

static const sgpio_mapping_t tower_led_mapping_lu26[LED_TOWER_MODE_CNT][2] = {
    {{2, 2} /* tower 0 green */, {3, 2} /* tower 0 yellow */},
    {{4, 2} /* tower 1 green */, {5, 2} /* tower 1 yellow */},
    {{6, 2} /* tower 2 green */, {6, 2} /* tower 2 yellow */},
    {{8, 2} /* tower 3 green */, {7, 2} /* tower 3 yellow */}
};

#define LU26_PORTS 26
#define LU10_PORTS 10
#define MAX_PORTS  (LU26_PORTS)    // Max port count

static const sgpio_mapping_t port_led_mapping_lu26[LU26_PORTS][2] = {
    [ 0] = {{ 0, 0} /* port  0 green */, { 0, 1} /* port  0 yellow */},
    [ 1] = {{ 1, 0} /* port  1 green */, { 1, 1} /* port  1 yellow */},
    [ 2] = {{ 2, 0} /* port  2 green */, { 2, 1} /* port  2 yellow */},
    [ 3] = {{ 3, 0} /* port  3 green */, { 3, 1} /* port  3 yellow */},
    [ 4] = {{ 4, 0} /* port  4 green */, { 4, 1} /* port  4 yellow */},
    [ 5] = {{ 5, 0} /* port  5 green */, { 5, 1} /* port  5 yellow */},
    [ 6] = {{ 6, 0} /* port  6 green */, { 6, 1} /* port  6 yellow */},
    [ 7] = {{ 7, 0} /* port  7 green */, { 7, 1} /* port  7 yellow */},
    [ 8] = {{ 8, 0} /* port  8 green */, { 8, 1} /* port  8 yellow */},
    [ 9] = {{ 9, 0} /* port  9 green */, { 9, 1} /* port  9 yellow */},
    [10] = {{10, 0} /* port 10 green */, {10, 1} /* port 10 yellow */},
    [11] = {{11, 0} /* port 11 green */, {11, 1} /* port 11 yellow */},
    [12] = {{12, 0} /* port 12 green */, {12, 1} /* port 12 yellow */},
    [13] = {{13, 0} /* port 13 green */, {13, 1} /* port 13 yellow */},
    [14] = {{14, 0} /* port 14 green */, {14, 1} /* port 14 yellow */},
    [15] = {{15, 0} /* port 15 green */, {15, 1} /* port 15 yellow */},
    [16] = {{16, 0} /* port 16 green */, {16, 1} /* port 16 yellow */},
    [17] = {{17, 0} /* port 17 green */, {17, 1} /* port 17 yellow */},
    [18] = {{18, 0} /* port 18 green */, {18, 1} /* port 18 yellow */},
    [19] = {{19, 0} /* port 19 green */, {19, 1} /* port 19 yellow */},
    [20] = {{20, 0} /* port 20 green */, {20, 1} /* port 20 yellow */},
    [21] = {{21, 0} /* port 21 green */, {21, 1} /* port 21 yellow */},
    [22] = {{22, 0} /* port 22 green */, {22, 1} /* port 22 yellow */},
    [23] = {{23, 0} /* port 23 green */, {23, 1} /* port 23 yellow */},
    [LU26_PORTS - 2] = {{24, 0} /* port 24 green */, {24, 1} /* port 24 yellow */},
    [LU26_PORTS - 1] = {{25, 0} /* port 25 green */, {25, 1} /* port 25 yellow */}
};

static const sgpio_mapping_t tower_led_mapping_lu10[LED_TOWER_MODE_CNT][2] = {
    {{20, 0} /* tower 0 green */, {20, 1} /* tower 0 yellow */},
    {{21, 0} /* tower 1 green */, {21, 1} /* tower 1 yellow */},
    {{22, 0} /* tower 2 green */, {22, 1} /* tower 2 yellow */},
    {{23, 0} /* tower 3 green */, {23, 1} /* tower 3 yellow */}
};

static const sgpio_mapping_t port_led_mapping_lu10[LU10_PORTS][2] = {
    [0] = {{ 0, 0} /* port  0 green */, { 0, 1} /* port  0 yellow */},
    [1] = {{ 1, 0} /* port  1 green */, { 1, 1} /* port  1 yellow */},
    [2] = {{ 2, 0} /* port  2 green */, { 2, 1} /* port  2 yellow */},
    [3] = {{ 3, 0} /* port  3 green */, { 3, 1} /* port  3 yellow */},
    [4] = {{ 4, 0} /* port  4 green */, { 4, 1} /* port  4 yellow */},
    [5] = {{ 5, 0} /* port  5 green */, { 5, 1} /* port  5 yellow */},
    [6] = {{ 6, 0} /* port  6 green */, { 6, 1} /* port  6 yellow */},
    [7] = {{ 7, 0} /* port  7 green */, { 7, 1} /* port  7 yellow */},
    [LU10_PORTS - 2] = {{24, 0} /* port 24 green */, {24, 1} /* port 24 yellow */},
    [LU10_PORTS - 1] = {{25, 0} /* port 25 green */, {25, 1} /* port 25 yellow */}
};

static const sgpio_mapping_t port_led_mapping_pds408g[PDS_408G_NUM_COPPER_PORTS][2] = {
    [0] = { { 0, 0 }/* port  0 green */, { 0, 1 }/* port  0 yellow */ },
    [1] = { { 1, 0 }/* port  1 green */, { 1, 1 }/* port  1 yellow */ },
    [2] = { { 2, 0 }/* port  2 green */, { 2, 1 }/* port  2 yellow */ },
    [3] = { { 3, 0 }/* port  3 green */, { 3, 1 }/* port  3 yellow */ },
    [4] = { { 4, 0 }/* port  4 green */, { 4, 1 }/* port  4 yellow */ },
    [5] = { { 5, 0 }/* port  5 green */, { 5, 1 }/* port  5 yellow */ },
    [6] = { { 6, 0 }/* port  6 green */, { 6, 1 }/* port  6 yellow */ },
    [7] = { { 7, 0 }/* port  7 green */, { 7, 1 }/* port  7 yellow */ },
    [8] = { { 8, 0 }/* port  8 green */, { 8, 1 }/* port  8 yellow */ },
    [9] = { { 9, 0 }/* port  9 green */, { 9, 1 }/* port  9 yellow */ },
};


typedef enum {
    BOARD_LUTON10,
    BOARD_LUTON26,
    BOARD_LUTON10_PDS408G,
} board_type_t;

static const sgpio_mapping_t status_led_mapping_lu26[2] = {
    {0, 2}, /* green */
    {1, 2}  /* red */
};

static const sgpio_mapping_t status_led_mapping_lu10[2] = {
    {26, 0}, /* green */
    {26, 1}  /* red */
};

typedef struct meba_board_state {
    board_type_t type;
    int port_cnt;
    const mesa_fan_conf_t *fan_spec;
    led_tower_mode_t led_tower_mode;
    const sgpio_mapping_t *status_led_map;
    uint64_t tmp_timer;
    mepa_device_t        *phy_devices[MAX_PORTS];
} meba_board_state_t;

#define VTSS_OS_TICK2MSEC(x)    ((x)*100)  // assume itteration every 100msec

static const mesa_fan_conf_t fan_conf = {
    .fan_pwm_freq = MESA_FAN_PWM_FREQ_25KHZ,   // 25kHz
    .fan_low_pol = 0,                          // active low
    .fan_open_col = true,                      // Open collector
    .type = MESA_FAN_3_WIRE_TYPE,              // 3-wire
    .ppr = 2,                                  // 2 PPR
};

/*
 * For Luton 10 the fan control pin is used for
 * controlling led intensity, because the pin connects to
 * shift registers' OE (active low), so .fan_lo_pol should be
 * set to 1. On the other hand, to make LED's link act more obvious
 * the .fan_pwm_freq is set 40HZ.
*/
static const mesa_fan_conf_t fan_conf_lu10 = {
    .fan_pwm_freq = MESA_FAN_PWM_FREQ_40HZ,    // 40Hz
    .fan_low_pol = 1,                          // 1: logic 0 when "on"
    .fan_open_col = true,                      // Open collector
    .type = MESA_FAN_3_WIRE_TYPE,              // 3-wire
    .ppr = 2,                                  // 2 PPR
};

static mesa_rc caracal_ptp_external_io_conf_get(meba_inst_t inst, uint32_t io_pin, meba_ptp_io_cap_t *const board_assignment, meba_event_t *const source_id)
{
    if (io_pin >= VTSS_TS_IO_ARRAY_SIZE) {
        return MESA_RC_ERROR;
    }
    *board_assignment = pin_conf[io_pin];
    *source_id = init_int_source_id[io_pin];
    return MESA_RC_OK;
}

const sgpio_mapping_t *sgpio_map_led(meba_board_state_t *board, int i)
{
    return (board->type == BOARD_LUTON10 || board->type == BOARD_LUTON10_PDS408G) ?
            &tower_led_mapping_lu10[i][LED_GREEN] :
            &tower_led_mapping_lu26[i][LED_GREEN];
}

const sgpio_mapping_t *sgpio_map_port(meba_board_state_t *board, mesa_port_no_t p, led_color_t c)
{
    return (board->type == BOARD_LUTON10) ?
            &port_led_mapping_lu10[p][c] :
        (board->type == BOARD_LUTON10_PDS408G) ?
            &port_led_mapping_pds408g[p][c] :
            &port_led_mapping_lu26[p][c];
}

static void lu26_led_tower_update(meba_inst_t inst,
                                  led_tower_mode_t led_tower_mode)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t conf;
    int               i;

    T_D(inst, "Current %d, new %d", board->led_tower_mode, led_tower_mode);

    /*
     * LED tower:
     *  (top)       o  mode A (link/speed)
     *              o  mode B (link/duplex)
     *              o  mode C (link/status)
     *  (button)    o  PWR save
     */
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        for (i = 0; i < LED_TOWER_MODE_CNT; i++) {
            const sgpio_mapping_t *map = sgpio_map_led(board, i);
            if (i == led_tower_mode) {
                T_I(inst, "Set LED %d mode ON", led_tower_mode);
                conf.port_conf[map->port].mode[map->bit] = MESA_SGPIO_MODE_ON;
            } else {
                T_N(inst, "Set LED %d mode OFF", i);
                conf.port_conf[map->port].mode[map->bit] = MESA_SGPIO_MODE_OFF;
            }
        }
        (void) mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        board->led_tower_mode = led_tower_mode;
    }
}

static uint32_t caracal_capability(meba_inst_t inst, int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_POE:
            return (board->type == BOARD_LUTON10 ? false : true);
        case MEBA_CAP_1588_CLK_ADJ_DAC:
            return false;
        case MEBA_CAP_1588_REF_CLK_SEL:
            return false;
        case MEBA_CAP_TEMP_SENSORS:
            return board->type == BOARD_LUTON26 ? 2 : 1;
        case MEBA_CAP_BOARD_PORT_COUNT:
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            // On this platform port count and port map count are identical (no loop ports)
            return board->port_cnt;
        case MEBA_CAP_LED_MODES:
            // LED_TOWER_MODE_CNT; No led_update() function - handled implicitly w. caracal_port_led_update ...
            return 1;
        case MEBA_CAP_DYING_GASP:
            return false;
        case MEBA_CAP_FAN_SUPPORT:
            return board->type == BOARD_LUTON26;
        case MEBA_CAP_LED_DIM_SUPPORT:
            // According to sec 4.3.3.in UG1037-01-02-RBM_VSC56xxEV_SparX_III_and_Caracal_mng24_unmng24_mng8_Hardware_Manual
            // a PWM output of the VSC85x2 PHY is used to dim the LEDs.
            return true;
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
            return false;
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
            return false;
        case MEBA_CAP_BOARD_HAS_PCB135_CPLD:
            return false;
        case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:      // NOTE: Capability currently not used on Caracal. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:  // NOTE: Capability currently not used on Caracal. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_DPLL:            // NOTE: Capability currently not used on Caracal. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:      // NOTE: Capability currently not used on Caracal. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:  // NOTE: Capability currently not used on Caracal. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_ONE_PPS_INT_ID:
            return MEBA_EVENT_SYNC;
        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:      // Caracal supports single DPLL mode if a DPLL is present
            {
                meba_synce_clock_hw_id_t dpll_type;

                if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK) && (dpll_type != MEBA_SYNCE_CLOCK_HW_NONE)) {
                    return true;
                } else {
                    return false;
                }
            }
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:        // Caracal does not support dual DPLL mode
            return false;
        case MEBA_CAP_POE_BT:
            return board->type == BOARD_LUTON10_PDS408G;
        case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET:
            return false;
        case MEBA_CAP_CPU_PORTS_COUNT:
            return 0;
        case MEBA_CAP_BOARD_PORT_POE_COUNT:
            return board->port_cnt;
        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc caracal_port_entry_get(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    meba_board_state_t *board = INST2BOARD(inst);

    T_N(inst, "Called");

    // No sense continuing if the board does not have enough ports
    if (port_no >= board->port_cnt) {
        return MESA_RC_ERROR;
    }

    if (board->type == BOARD_LUTON10_PDS408G) {
        if (port_no == PDS_408G_SFP_LOG_PORT_INDEX) {
            entry->map.chip_port       = 24; // port_no;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
            entry->cap                 = MEBA_PORT_CAP_SFP_1G;
            entry->cap                |= MEBA_PORT_CAP_SFP_SD_HIGH;
            entry->cap                |= MEBA_PORT_CAP_DUAL_SFP_DETECT;
        } else {
            /* Copper ports (0..9) with internal PHY */
            entry->map.chip_port       = port_no;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
            entry->map.miim_addr       = port_no;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY;

            if (caracal_capability(inst, MEBA_CAP_POE)) {
                if (port_no < PDS_408G_NUM_POE_PORT) { // port 0-7 support PoE
                    entry->poe_support   = true;
                    entry->poe_chip_port = entry->map.chip_port;
                }
            }
        }

        return MESA_RC_OK;
    }

    // VSC7426 (aka SparX-III-24) does not use the uplink SFPs
    mesa_bool_t has_uplink = (inst->props.target != MESA_TARGET_SPARX_III_24);
    // Most SKUs use 1G uplinks, so setting that as default and updating
    // for the exceptions.
    meba_port_cap_t uplink_cap1, uplink_cap2;
    uplink_cap1 = MEBA_PORT_CAP_SFP_1G;
    uplink_cap2 = MEBA_PORT_CAP_SFP_1G;
    switch (inst->props.target) {
        case MESA_TARGET_CARACAL_LITE:
        case MESA_TARGET_CARACAL_1:
            uplink_cap1 = MEBA_PORT_CAP_SFP_2_5G;
            uplink_cap2 = MEBA_PORT_CAP_SFP_2_5G;
            break;
        case MESA_TARGET_CARACAL_2:
            uplink_cap2 = MEBA_PORT_CAP_SFP_2_5G;
            break;
        default:
            break;
    }

    if (has_uplink && port_no >= board->port_cnt - 2) {
        // Only if the Target uses the uplink ports.
        mesa_bool_t uplink1 = port_no == board->port_cnt - 2;
        /* SFP ports */
        entry->map.chip_port = (uplink1 ? 24 : 25);
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
        entry->mac_if = MESA_PORT_INTERFACE_SERDES;
        // Use the Uplink port speed for the specific chip.
        entry->cap = (uplink1 ? uplink_cap1 : uplink_cap2);
        entry->cap |= MEBA_PORT_CAP_SFP_SD_HIGH;
    } else {
        // Non-uplink ports
        if (port_no < 12) {
            /* Copper ports (0..11) with internal PHY */
            entry->map.chip_port = port_no;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
            entry->map.miim_addr = port_no;
            entry->mac_if = MESA_PORT_INTERFACE_SGMII;
            entry->cap = MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY;
        } else {
            /* Copper and dual media ports (12..23) through external PHY */
            mesa_port_no_t chip_port_no = port_no;
            // VSC7425 (aka SparX-III-18)  is a special case where there is a gap
            // on the chip ports that are enabled. Chip ports 12..19 remain unused.
            if (inst->props.target == MESA_TARGET_SPARX_III_18) {
                chip_port_no = port_no + 8;
            }

            entry->map.chip_port = chip_port_no;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_1;
            entry->map.miim_addr = (chip_port_no - 12);
            entry->mac_if = MESA_PORT_INTERFACE_QSGMII;

            // SFP auto-detection works for all dual media ports (chip_port_no
            // 20-23), but it's not possible to access SFPs in chip_port_no
            // 21-23 through I2C, because their I2C bus is connected to ATOM12
            // and not Lu26.
            entry->cap = chip_port_no < 20 ? MEBA_PORT_CAP_TRI_SPEED_COPPER :
                                             MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER;

            // Since chip_port_no 20-23 are connected through QSGMII on ATOM12,
            // we can't (easily?) change a single port to run SGMII_CISCO and
            // therefore we can't support CuSFPs.
            if (chip_port_no >= 20 && chip_port_no <= 23) {
                entry->cap |= MEBA_PORT_CAP_DUAL_NO_COPPER;
            }

            // chip_port_no 21-23 are not I2C accessible on PCB boards <=
            // rev 2.0. It may work on rev. 2.03, but MCHP has not produced such
            // boards. Customers that use newer schematics may want to remove
            // the following three lines of code.
            if (chip_port_no >= 21 && chip_port_no <= 23) {
                entry->cap |= MEBA_PORT_CAP_SFP_INACCESSIBLE;
            }
        }

        if (caracal_capability(inst, MEBA_CAP_POE)) {
            entry->poe_support = true;
            entry->poe_chip_port = entry->map.chip_port;
        }
    }
    return MESA_RC_OK;
}

static mesa_rc caracal_reset(meba_inst_t inst,
                             meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;
    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            {
                mesa_gpio_no_t    gpio;
                mesa_sgpio_conf_t conf;
                uint32_t          port;

                /* Enable GPIO 0-3 as SGPIO pins */
                for (gpio = 0; gpio < 4; gpio++) {
                    (void) mesa_gpio_mode_set(NULL, 0, gpio, MESA_GPIO_ALT_0);
                }

                /* Set GPIO 8 as nINT */
                (void) mesa_gpio_mode_set(NULL, 0, 8, MESA_GPIO_ALT_0);

                if (board->type == BOARD_LUTON10_PDS408G) {
                    // Set GPIO 4 as CPU POE-reset. Low=CPU PoE RESET. Leave it in "1" so that there will not be PoE CPU RESET
                    //POE_CPU_OK_BY_IO; // "1" = no PoE CPU reset (let it continue to run)
                    (void)mesa_gpio_write(NULL        , 0, PDS_408G_POE_RESET_IO, true ); // '1' = dont reset PoE CPU
                    (void)mesa_gpio_mode_set(NULL     , 0, PDS_408G_POE_RESET_IO, MESA_GPIO_OUT);
                    (void)mesa_gpio_direction_set(NULL, 0, PDS_408G_POE_RESET_IO, true);

                    // Set GPIO 7 as System LED
                    (void)mesa_gpio_write(NULL        , 0, PDS_408G_SYSTEM_LED_IO, true);
                    (void)mesa_gpio_mode_set(NULL     , 0, PDS_408G_SYSTEM_LED_IO, MESA_GPIO_OUT);
                    (void)mesa_gpio_direction_set(NULL, 0, PDS_408G_SYSTEM_LED_IO, true);

                    // Set GPIO 10 as POE En/Dis by output pin (0=disable)
                    (void)mesa_gpio_write(NULL        , 0, PDS_408G_POE_DISABLE_PORTS_IO, true ); // "1" = dont disable PoE
                    (void)mesa_gpio_mode_set(NULL     , 0, PDS_408G_POE_DISABLE_PORTS_IO, MESA_GPIO_OUT);
                    (void)mesa_gpio_direction_set(NULL, 0, PDS_408G_POE_DISABLE_PORTS_IO, true);

                    /* Set GPIO 12 as push button int */
                    (void)mesa_gpio_mode_set(NULL     , 0, PDS_408G_RESET_BUTTON_IP, MESA_GPIO_IN);
                    (void)mesa_gpio_direction_set(NULL, 0, PDS_408G_RESET_BUTTON_IP, false);
                }

                /* Setup SGPIO */
                if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
                    /* The blink mode 0 is 5 HZ for link activity and collion in half duplex. */
                    conf.bmode[0] = MESA_SGPIO_BMODE_5;
                    if (board->type == BOARD_LUTON26) {
                        conf.bit_count = 3;
                        for (port = 0; port < MESA_SGPIO_PORTS; port++)
                            conf.port_conf[port].enabled = 1;
                        conf.port_conf[26].mode[2] = MESA_SGPIO_MODE_ON; /* SFP0 Tx enable */
                        conf.port_conf[27].mode[1] = MESA_SGPIO_MODE_ON; /* SFP1 Tx enable */

                        conf.port_conf[28].mode[0] = MESA_SGPIO_MODE_ON; /* SFP2 Tx enable */
                        conf.port_conf[28].mode[1] = MESA_SGPIO_MODE_ON; /* SFP3 Tx enable */
                        conf.port_conf[28].mode[2] = MESA_SGPIO_MODE_ON; /* SFP4 Tx enable */
                        conf.port_conf[29].mode[0] = MESA_SGPIO_MODE_ON; /* SFP5 Tx enable */
                    }
                    if (board->type == BOARD_LUTON10) {
                        conf.bit_count = 2;
                        for (port = 0; port < MESA_SGPIO_PORTS; port++)
                            conf.port_conf[port].enabled = (port < 8 || port > 19 ? 1 : 0);
                        conf.port_conf[30].mode[0] = MESA_SGPIO_MODE_ON; /* SFP0 Tx enable */
                        conf.port_conf[31].mode[0] = MESA_SGPIO_MODE_ON; /* SFP1 Tx enable */
                    }
                    if (board->type == BOARD_LUTON10_PDS408G) {
                        conf.bit_count = 1;
                        for (port = 0; port < MESA_SGPIO_PORTS; port++)
                            conf.port_conf[port].enabled = (port < PDS_408G_NUM_COPPER_PORTS ? 1 : 0);
                        // Only one SFP port on PDS408G. Fixit.
                        conf.port_conf[30].mode[0] = MESA_SGPIO_MODE_ON; /* SFP0 Tx enable */
                        conf.port_conf[31].mode[0] = MESA_SGPIO_MODE_ON; /* SFP1 Tx enable */
                    }

                    (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
                }
            }
            break;
        case MEBA_PORT_RESET:
            // Internal PHY
            if ((rc = vtss_phy_pre_reset(PHY_INST, 0)) != MESA_RC_OK) {
                break;
            }

            if (board->type != BOARD_LUTON10 && board->type != BOARD_LUTON10_PDS408G) {
                mesa_port_no_t port_idx;

                // External PHY (Atom12)
                rc = vtss_phy_pre_reset(PHY_INST, 12);

                // Setup dual media port (fiber/cu), PHY 13 is external Atom12 PHY w/dual-media
                (void) vtss_phy_write_masked(NULL, 13, 19 | VTSS_PHY_REG_GPIO, 0x8000, 0xC000); // Enable fiber-media SerDes in HSIO
                (void) vtss_phy_write(NULL, 13, 18 | VTSS_PHY_REG_GPIO, 0x8f81);

                switch (inst->props.target) {
                    case MESA_TARGET_SPARX_III_24:
                    case MESA_TARGET_SPARX_III_26:
                    case MESA_TARGET_CARACAL_2:
                        // SFP Signal detect shall be active low (register 19E1 bit 1 = true)
                        // Dual media ports (user port 21-24)
                        for (port_idx = 20; port_idx < 24; port_idx++) {
                            (void) vtss_phy_write_masked(NULL, port_idx, 19 |VTSS_PHY_REG_EXTENDED , 0x1, 0x1);
                        }
                        break;
                    case MESA_TARGET_SPARX_III_18:
                        // SFP Signal detect shall be active low (register 19E1 bit 1 = true)
                        // Dual media ports (user port 12-16)
                        for (port_idx = 12; port_idx < 16; port_idx++) {
                            (void) vtss_phy_write_masked(NULL, port_idx, 19 |VTSS_PHY_REG_EXTENDED , 0x1, 0x1);
                        }
                        break;
                    default:
                        break;
                 }
            }
            break;
        case MEBA_PORT_RESET_POST:
            rc = vtss_phy_post_reset(PHY_INST, 0);
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            {
                vtss_phy_enhanced_led_control_t conf;
                conf.ser_led_output_2 = true;
                conf.ser_led_output_1 = false;
                conf.ser_led_frame_rate = 0x1;
                conf.ser_led_select = 0;
                if (board->type == BOARD_LUTON26) {
                    vtss_phy_enhanced_led_control_init(PHY_INST, 13, conf);
                } else if (board->type == BOARD_LUTON10 ||
                           board->type == BOARD_LUTON10_PDS408G) {
                    vtss_phy_enhanced_led_control_init(PHY_INST, 1, conf);
                }
            }
            break;
        case MEBA_PORT_LED_INITIALIZE:
            {
                mesa_port_no_t port;
                if (board->type == BOARD_LUTON26) {
                    /* Setup LED_PWM */
                    /* GPIO_8 is primarily used as LED1 for port 3 (external PHY) - it is at internal port 15 */
                    rc = vtss_phy_write_masked(NULL, 15, 29, 0x00F0, 0x00F0);

                    switch (inst->props.target) {
                        case MESA_TARGET_SPARX_III_24:
                        case MESA_TARGET_SPARX_III_26:
                                // Phy ports 12-15 gpios are connected to the SFP yellow LEDs (See Schematic),
                                // The default mode is Link1000/Activily. And it's an issue that
                                // the SFP LEDs will light yellow when port 12-16 come up(Bug 23210).
                                // So we turned off them here. Actully there's no clear definition for
                                // yellow LEDs. So S/W doesn't implement it yet.
                                for (port = 12; port < 16; port++) {
                                    (void) vtss_phy_write_masked(NULL, port, 29 , 0xE, 0xF);
                                }
                                // Make sure that SFP led are turned off
                                for (port = 20; port < 24; port ++) {
                                    (void) vtss_phy_write_masked(NULL, port, 29, 0xE, 0xF);
                                }
                            break;
                        case MESA_TARGET_SPARX_III_18:
                            // Phy ports 12-16 gpios are connected  to the SFP yellow LEDs (See Schematic), but we don't use them, so we need
                            // to make sure that they are turned off.
                            for (port = 12; port < 16; port ++) {
                                (void) vtss_phy_write_masked(NULL, port, 29, 0xE, 0xF);
                            }
                        default:
                            break;
                     }
                }
                /* Initial LED tower */
                lu26_led_tower_update(inst, LED_TOWER_MODE_LINK_SPEED);

                // For Luton 10 reference board the LED pwm is in fact the FAN
                // controller PWM, so we need to initialize fan controller.
                if (board->type == BOARD_LUTON10 || board->type == BOARD_LUTON10_PDS408G) {
                    rc = mesa_fan_controller_init(PHY_INST, board->fan_spec );
                }
            }
            break;
        case MEBA_FAN_INITIALIZE:
            if (caracal_capability(inst, MEBA_CAP_FAN_SUPPORT)) {
                rc = mesa_fan_controller_init(NULL, board->fan_spec);
            }
            break;
        case MEBA_SENSOR_INITIALIZE:
            if (board->type == BOARD_LUTON26) {
                // The Luton26 board has a temperature sensor in Luton26 (ports 0-11) and one in Atom12 (ports 12-24)
                if ((rc = vtss_phy_chip_temp_init(PHY_INST, 0)) != MESA_RC_OK ||
                    (rc = vtss_phy_chip_temp_init(PHY_INST, 12)) != MESA_RC_OK) {
                    rc = MESA_RC_ERROR;
                }
            } else if (board->type == BOARD_LUTON10 ||
                       board->type == BOARD_LUTON10_PDS408G) {
                // The Luton10 board has a temperature sensor in the internal PHY.
                rc = vtss_phy_chip_temp_init(PHY_INST, 0);
            }
            break;
        case MEBA_INTERRUPT_INITIALIZE:
            break;
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

static mesa_rc caracal_sensor_get(meba_inst_t inst,
                                  meba_sensor_t type,
                                  int six,
                                  int *value)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_ERROR;
    int16_t temp = 0;
    T_N(inst, "Called %d:%d", type, six);
    if (type == MEBA_SENSOR_BOARD_TEMP) {
        if (six < caracal_capability(inst, MEBA_CAP_TEMP_SENSORS)) {
            if (board->type == BOARD_LUTON26) {
                // The Luton26 board has a temperature sensor in Luton26 (ports 0-11) and one in Atom12 (ports 12-24)
                rc = vtss_phy_chip_temp_get(PHY_INST, six * 12, &temp);
            } else {
                // The Luton10 board has a temperature sensor in the internal PHY.
                rc = vtss_phy_chip_temp_get(PHY_INST, six, &temp);
            }
        }
    } else if (type == MEBA_SENSOR_PORT_TEMP) {
        if (board->type == BOARD_LUTON26) {
            // The Luton26 board has a temperature sensor in Luton26 (ports 0-11) and one in Atom12 (ports 12-24)
            rc = vtss_phy_chip_temp_get(PHY_INST, six < 12 ? 0 : 12, &temp);
        } else {
            // The Luton10 board has a temperature sensor in the internal PHY.
            rc = vtss_phy_chip_temp_get(PHY_INST, 0, &temp);
        }
    }
    if (rc == MESA_RC_OK) {
        *value = temp;    // Conversion
    }
    return rc;
}

static mesa_rc caracal_sfp_i2c_xfer(meba_inst_t inst,
                                    mesa_port_no_t port_no,
                                    mesa_bool_t write,
                                    uint8_t i2c_addr,
                                    uint8_t addr,
                                    uint8_t *data,
                                    uint8_t cnt,
                                    mesa_bool_t word_access)
{
    mesa_rc rc;
    meba_port_entry_t entry;
    mesa_port_no_t    chip_port;

    T_N(inst, "Called, port_no=%d", port_no);

    if ((rc = caracal_port_entry_get(inst, port_no, &entry)) != MESA_RC_OK) {
        return rc;
    }

    // Use chip_port for SFP i2c access
    chip_port = entry.map.chip_port;

    if (write) {    // cnt ignored
        // Dual media SFP ports - Connected to PHY i2c
        if (chip_port >= 20 && chip_port <= 23) {
            // Due to a hardware board issue only SFP i2c mux 0 works, so that is always used.
            rc = vtss_phy_i2c_write(NULL, port_no, 0, addr, i2c_addr, word_access, 2, data);
        } else {
            // Uplink ports - Connected to switch i2c
            uint8_t i2c_data[3];
            i2c_data[0] = addr;
            memcpy(&i2c_data[1], data, 2);
            /* This function pointer refers to i2c_write() in vtss_appl/main/vtss_api_if.cxx,
               the first parameter will be converted to i2c adaptor ID via I2C_PORT2DEV(),
               so we must know which adaptors are used for SFP0 and SFP1 which is defined in
               vtss_appl/board/linux/luton26/bsp-dirver.c
            */
            rc = inst->iface.i2c_write(chip_port == 24 ? 8 : 9, i2c_addr, i2c_data, 3);
        }
    } else {
        if (chip_port >= 20 && chip_port <= 23) {
            // Due to a hardware board issue on rev 2.0 and less, onlySFP i2c
            // mux 0 works. However, on schematics sent to customers (rev. 2.03)
            // this has been fixed, so that it works. The cutomer may want to
            // remove the lines where MEBA_PORT_CAP_SFP_INACCESSIBLE are set.
            rc = vtss_phy_i2c_read(NULL, port_no, port_no - 20, addr, i2c_addr, word_access, cnt, data);
        } else {
            // Uplink ports - Connected to switch i2c
            /* This function pointer refers to i2c_read() in vtss_appl/main/vtss_api_if.cxx,
               the first parameter will be converted to i2c adaptor ID via I2C_PORT2DEV(),
               so we must know which adaptors are used for SFP0 and SFP1 which is defined in
               vtss_appl/board/linux/luton26/bsp-dirver.c
            */
            rc = inst->iface.i2c_read(chip_port == 24 ? 8 : 9, i2c_addr, addr, data, cnt);
        }
    }
    T_D(inst, "i2c %s port %d - address 0x%02x:0x%02x, %d bytes return %d", write ? "write" : "read", port_no, i2c_addr, addr, cnt, rc);
    return rc;
}

static mesa_rc caracal_sfp_insertion_status_get(meba_inst_t inst,
                                                mesa_port_list_t *present)
{
    meba_board_state_t     *board = INST2BOARD(inst);
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];
    mesa_port_no_t         port_no;
    uint32_t               offset;

    //T_D(inst, "Called");

    mesa_port_list_clear(present);

    if (mesa_sgpio_read(NULL, 0, 0, data) != MESA_RC_OK)
        return MESA_RC_ERROR;

    if (board->type == BOARD_LUTON26) {
        // Chip ports 21-23 are not I2C accessible (because I2C for these ports
        // is connected to ATOM12 and not Lu26). However, SFP detect works, and
        // it's nice to know whether an SFP is plugged in or not.
        // The mapping from SGPIO port and bit to port number and function can
        // be found in UG1037, Table 11 (the non-greyed cells).
        if (inst->props.target == MESA_TARGET_SPARX_III_18) {
            // port_no 20 is called port_no 12 on SPARX_III_18.
            // port_no 21 is called port_no 13 on SPARX_III_18, etc.
            offset = 8;
        } else {
            offset = 0;
        }

        // Dual media ports
        mesa_port_list_set(present, 20 - offset, data[27].value[0] ? 0 : 1); // sfp2present (p27b0)
        mesa_port_list_set(present, 21 - offset, data[27].value[2] ? 0 : 1); // sfp3present (p27b2)
        mesa_port_list_set(present, 22 - offset, data[28].value[1] ? 0 : 1); // sfp4present (p28b1)
        mesa_port_list_set(present, 23 - offset, data[29].value[0] ? 0 : 1); // sfp5present (p29b0)

        // SFP uplink ports. Only sparxIII_24 doens't have uplink port
        if (inst->props.target != MESA_TARGET_SPARX_III_24) {
            mesa_port_list_set(present, 24 - offset, data[24].value[1] ? 0 : 1); // sfp0present (p24b1)
            mesa_port_list_set(present, 25 - offset, data[25].value[1] ? 0 : 1); // sfp1present (p25b1)
        }
    } else if(board->type == BOARD_LUTON10) {
        int i;
        for(port_no = board->port_cnt - 2, i = 26; port_no < board->port_cnt; port_no++, i++) {
            /* Bit one is mod_detect, 0=detected */
            mesa_port_list_set(present, port_no, data[i].value[1] ? 0 : 1);
        }
    } else if(board->type == BOARD_LUTON10_PDS408G) {
        int i;
        for(port_no = board->port_cnt - 2, i = 26; port_no < board->port_cnt; port_no++, i++) {
            // Only one SFP port on PDS408G. Fixit.
            /* Bit one is mod_detect, 0=detected */
            mesa_port_list_set(present, port_no, data[i].value[1] ? 0 : 1);
        }
    }

    return MESA_RC_OK;
}

static mesa_rc caracal_port_admin_state_set(meba_inst_t inst,
                                            mesa_port_no_t port_no,
                                            const meba_port_admin_state_t *state)
{
    mesa_rc rc;
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t conf;
    meba_port_entry_t entry;

    if ((rc = caracal_port_entry_get(inst, port_no, &entry)) != MESA_RC_OK ||
        (rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) != MESA_RC_OK) {
        return rc;
    }
    if (board->type == BOARD_LUTON10 ||
        board->type == BOARD_LUTON10_PDS408G) {
        // Only one SFP port on PDS408G. Fixit.
        if (entry.map.chip_port == 24) {
            conf.port_conf[30].mode[0] = state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF;
        } else if (entry.map.chip_port == 25) {
            conf.port_conf[31].mode[0] = state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF;
        }
        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    } else if (board->type == BOARD_LUTON26) {
        if (entry.map.chip_port == 24) {
            conf.port_conf[26].mode[2] = state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF;
        } else if (entry.map.chip_port == 25) {
            conf.port_conf[27].mode[1] = state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF;
        }
        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc;
}

static void lu26_sgpio_led_set(meba_inst_t inst,
                               mesa_port_no_t port_no,
                               led_color_t color,
                               mesa_sgpio_mode_t mode,
                               mesa_sgpio_conf_t *conf)
{
    meba_board_state_t *board = INST2BOARD(inst);
    const sgpio_mapping_t *map = sgpio_map_port(board, port_no, color);
    conf->port_conf[map->port].mode[map->bit] = mode;
}

/* Update fiber port LED */
static void lu26_fiber_port_led_update(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       mesa_bool_t link)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint16_t val = 0xE; // 0xE = Turn off LED
    uint16_t mask = 0x000F;

    if (board->led_tower_mode != LED_TOWER_MODE_POWER_SAVE && link) {
        val = 0x000F;
    }

    (void) vtss_phy_write_masked(NULL, port_no, 29, val, mask);
}

static mesa_rc caracal_status_led_set(meba_inst_t inst,
                                      meba_led_type_t type,
                                      meba_led_color_t color)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);
    if (type == MEBA_LED_TYPE_FRONT && color < MEBA_LED_COLOR_COUNT) {
        mesa_sgpio_conf_t conf;
        const sgpio_mapping_t
                *green = &board->status_led_map[0],
                *red = &board->status_led_map[1];
        T_I(inst, "LED:%d, color=%d", type, color);
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            switch (color) {
                // Active high
                case MEBA_LED_COLOR_OFF:
                    conf.port_conf[green->port].mode[green->bit] = MESA_SGPIO_MODE_OFF;
                    conf.port_conf[red->port  ].mode[red->bit  ] = MESA_SGPIO_MODE_OFF;
                    break;
                case MEBA_LED_COLOR_GREEN:
                    conf.port_conf[green->port].mode[green->bit] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[red->port  ].mode[red->bit  ] = MESA_SGPIO_MODE_OFF;
                    break;
                case MEBA_LED_COLOR_RED:
                    conf.port_conf[green->port].mode[green->bit] = MESA_SGPIO_MODE_OFF;
                    conf.port_conf[red->port  ].mode[red->bit  ] = MESA_SGPIO_MODE_ON;
                    break;
                case MEBA_LED_COLOR_YELLOW:
                    conf.port_conf[green->port].mode[green->bit] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[red->port  ].mode[red->bit  ] = MESA_SGPIO_MODE_ON;
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

static mesa_rc caracal_port_led_update(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       const mesa_port_status_t *status,
                                       const mesa_port_counters_t *counters,
                                       const meba_port_admin_state_t *state)
{
    meba_board_state_t *board = INST2BOARD(inst);
    static mesa_port_status_t   status_old[MAX_PORTS];
    static mesa_port_counter_t  port_collision_cnt[MAX_PORTS];
    mesa_bool_t                 need_process = false, tower_mode_changed = false, collision = false;
    mesa_bool_t                 gpio_val;
    mesa_port_no_t              port_idx = port_no, process_cnt = port_no + 1;
    mesa_sgpio_conf_t           conf;
    uint16_t                    reg;

    T_N(inst, "Called - port %d", port_no);

    /* Check if port's link/speed/fdx has changed */
    if (status_old[port_no].link != status->link ||
        (status_old[port_no].link == status->link &&
         (status_old[port_no].speed != status->speed || status_old[port_no].fdx != status->fdx))) {
        T_I(inst, "Port %d: Link state change - Force update", port_no);
        need_process = true;
    }
    status_old[port_no] = *status;

    /* Check if port collision occured */
    if (board->led_tower_mode == LED_TOWER_MODE_DUPLEX &&
        status->link &&
        !status->fdx &&
        port_collision_cnt[port_no] != counters->rmon.tx_etherStatsCollisions) {
        T_I(inst, "Port %d: Collision - Force update", port_no);
        need_process = true;
        collision = true;
    }
    port_collision_cnt[port_no] = counters->rmon.tx_etherStatsCollisions;

    /* Push button: GPIO bit 12.
       Don't need polling tower moce each time. */

    if (board->type == BOARD_LUTON10_PDS408G) {
        board->tmp_timer++;

        port_idx = 0;
        process_cnt = board->port_cnt;

        {
            static   uint64_t     system_led_toogle_time = 0;
            static   mesa_bool_t  system_led_toogle = true;


            if (VTSS_OS_TICK2MSEC(board->tmp_timer - system_led_toogle_time) > 500)
            {
                mesa_gpio_write(NULL, 0, PDS_408G_SYSTEM_LED_IO, system_led_toogle);
                system_led_toogle = !system_led_toogle;
                system_led_toogle_time = board->tmp_timer;
            }
        }

        /* Update port LEDs */
        if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK)
        {
            for (; port_idx < process_cnt - 1; port_idx++)
            {
                lu26_sgpio_led_set(inst, port_idx, LED_GREEN, MESA_SGPIO_MODE_OFF, &conf);

                //Y no need for tower LED and different blink mode support - just blink inverse activity
                if (status_old[port_idx].link) lu26_sgpio_led_set(inst, port_idx, LED_GREEN, MESA_SGPIO_MODE_0_ACTIVITY_INV, &conf);
            }
            (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        }

        return MESA_RC_OK;

    }

    if ((port_no % 4) == 0 && mesa_gpio_read(NULL, 0, 12, &gpio_val) == MESA_RC_OK && gpio_val) {
        tower_mode_changed = true;
        led_tower_mode_t led_tower_mode = (led_tower_mode_t)((board->led_tower_mode + 1) % LED_TOWER_MODE_CNT);

        T_I(inst, "Mode button pressed");

        /* Update LED tower */
        lu26_led_tower_update(inst, led_tower_mode);

        /* Update all ports LED status */
        port_idx = 0;
        process_cnt = board->port_cnt;
    }

    /* Return here if nothing has changed or in power saving mode */
    if ((!need_process && !tower_mode_changed) ||
        (!tower_mode_changed && board->led_tower_mode == LED_TOWER_MODE_POWER_SAVE)) {
        return MESA_RC_OK;
    }

    /* Update port LEDs */
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        for (; port_idx < process_cnt; port_idx++) {
            lu26_sgpio_led_set(inst, port_idx, LED_GREEN, MESA_SGPIO_MODE_OFF, &conf);
            lu26_sgpio_led_set(inst, port_idx, LED_YELLOW, MESA_SGPIO_MODE_OFF, &conf);

            if (board->type == BOARD_LUTON26) {
                meba_port_entry_t entry;
                if (caracal_port_entry_get(inst, port_idx, &entry) == MESA_RC_OK &&
                    (entry.cap & (MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER))) {
                    /* Read Media Mode  status */
                    if (vtss_phy_read(NULL, port_idx, 20 | VTSS_PHY_REG_EXTENDED, &reg) == MESA_RC_OK) {
                        mesa_bool_t fiber = (((reg >> 6) & 0x3) == 2 ? 1 : 0);
                        if (fiber || !status_old[port_idx].link) {
                            lu26_fiber_port_led_update(inst, port_idx, status_old[port_idx].link);
                        }
                    }
                }
            }

            switch (board->led_tower_mode) {
                case LED_TOWER_MODE_LINK_SPEED:
                    if (status_old[port_idx].link) {
                        if (status_old[port_idx].speed >= MESA_SPEED_1G) {
                            /* Green: 1G link/activity */
                            lu26_sgpio_led_set(inst, port_idx, LED_GREEN, MESA_SGPIO_MODE_0_ACTIVITY_INV, &conf);
                        } else {
                            /* Yellow: 100/10 link/activity */
                            lu26_sgpio_led_set(inst, port_idx, LED_YELLOW, MESA_SGPIO_MODE_0_ACTIVITY_INV, &conf);
                        }
                    }
                    break;
                case LED_TOWER_MODE_DUPLEX:
                    if (status_old[port_idx].link) {
                        if (status_old[port_idx].fdx) {
                            /* Green: FDX */
                            lu26_sgpio_led_set(inst, port_idx, LED_GREEN, MESA_SGPIO_MODE_0_ACTIVITY_INV, &conf);
                        } else if (port_idx == port_no && collision) {
                            /* Blink yellow: HDX with collision */
                            lu26_sgpio_led_set(inst, port_idx, LED_YELLOW, MESA_SGPIO_MODE_0, &conf);
                        } else {
                            /* Yellow: HDX without collision */
                            lu26_sgpio_led_set(inst, port_idx, LED_YELLOW, MESA_SGPIO_MODE_ON, &conf);
                        }
                    }
                    break;
                case LED_TOWER_MODE_LINK_STATUS:
                    if (status_old[port_idx].link) {
                        /* Green: link on */
                        lu26_sgpio_led_set(inst, port_idx, LED_GREEN, MESA_SGPIO_MODE_ON, &conf);
                    }
                    break;
                case LED_TOWER_MODE_POWER_SAVE:
                    break;
                default:
                    break;
            }
        }
        (void) mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }

    return MESA_RC_OK;
}

static mesa_rc caracal_led_intensity_set(meba_inst_t inst,
                                         vtss_phy_led_intensity intensity)
{
    mesa_rc rc;
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", intensity);
    if (board->type == BOARD_LUTON26) {
        // For Luton 26 reference board the LED pwm pin is connected at
        // the ATOM12 chip (phy ports 13-24), GPIO 8. Therefore port 13 is
        // used
        rc = vtss_phy_led_intensity_set(PHY_INST, 13, intensity);
    } else {
        // For Luton 10 reference board the LED pwm is in fact the FAN
        // controller PWM, so we need to used mesa_fan_cool_lvl_set which
        // can be set from 0 to 255. We need to convert from percent to
        // 0-255
        rc = mesa_fan_cool_lvl_set(PHY_INST, intensity * 255 / 100);
    }
    return rc;
}

static mesa_rc caracal_fan_param_get(meba_inst_t inst,
                                     meba_fan_param_t *param)
{
    mesa_rc rc = MESA_RC_OK;
    T_N(inst, "Called");
    if (caracal_capability(inst, MEBA_CAP_FAN_SUPPORT)) {
        param->start_time = 100;
        param->start_level = 60;
        param->min_pwm = 30;
    } else {
        rc = MESA_RC_ERROR;
    }
    return rc;
}

static mesa_rc caracal_fan_conf_get(meba_inst_t inst,
                                    mesa_fan_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    T_N(inst, "Called");
    if (caracal_capability(inst, MEBA_CAP_FAN_SUPPORT)) {
        meba_board_state_t *board = INST2BOARD(inst);
        *conf = *board->fan_spec;
    } else {
        rc = MESA_RC_ERROR;
    }
    return rc;
}

static mesa_rc caracal_phy_event_enable(meba_inst_t inst,
                                    vtss_phy_event_t phy_event,
                                    mesa_bool_t enable)
{
    mesa_port_no_t port_no;
    meba_board_state_t *board = INST2BOARD(inst);
    meba_port_entry_t entry;
    mesa_rc rc = MESA_RC_OK;
    T_D(inst, "%sable phy event %d on all ports", enable ? "en" : "dis", phy_event);

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (caracal_port_entry_get(inst, port_no, &entry) != MESA_RC_OK) {
            T_E(inst, "get port entry fail");
            break;
        }

        if (is_phy_internal(entry.cap)) {
            if (mesa_dev_all_event_enable(NULL, port_no, MESA_DEV_ALL_LINK_EV, enable) != MESA_RC_OK) {
                T_E(inst, "vtss_phy_event_enable_set = %d", rc);
                break;
            }
        }
        if (is_phy_port(entry.cap)){
            if ((rc = vtss_phy_event_enable_set(PHY_INST, port_no, phy_event, enable)) != MESA_RC_OK) {
                T_E(inst, "vtss_phy_event_enable_set = %d", rc);
                break;
            }
        }

    }
    return rc;
}

static mesa_rc caracal_event_enable(meba_inst_t inst,
                                    meba_event_t event_id,
                                    mesa_bool_t enable)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    meba_port_entry_t entry;

    switch (event_id) {
        case MEBA_EVENT_SYNC:
        case MEBA_EVENT_EXT_SYNC:
        case MEBA_EVENT_CLK_ADJ:
            {
                mesa_ptp_event_type_t ptp_event = meba_generic_ptp_source_to_event(inst, event_id);
                if ((rc = mesa_ptp_event_enable(NULL, ptp_event, enable)) != MESA_RC_OK) {
                    T_E(inst, "mesa_ptp_event_enable = %d", rc);
                }
            }
            break;
        case MEBA_EVENT_LOS:
            {
                mesa_port_no_t port_no;
                for (port_no = 0; port_no < board->port_cnt; port_no++) {
                    if (caracal_port_entry_get(inst, port_no, &entry) != MESA_RC_OK) {
                        T_E(inst, "get port entry fail");
                        break;
                    }

                    if (is_sfp_port(entry.cap)) {
                        uint32_t sgpio_port = entry.map.chip_port;
                        if (sgpio_port == 24 || sgpio_port == 25) {
                            // Enable SGPIO for SFP ports
                            T_D(inst, "%sable LOS on port %d SGPIO %d bit 0", enable ? "en" : "dis", port_no, sgpio_port);
                            if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, sgpio_port, 0, enable)) != MESA_RC_OK) {
                                T_E(inst, "mesa_sgpio_event_enable(%d) = %d", sgpio_port, rc);
                            }
                        }

                        /* If the port is a dual-media one, then the board port no is different */
                        if (has_cap(entry.cap, (MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER))) {
                            rc = caracal_phy_event_enable(inst, VTSS_PHY_LINK_LOS_EV, enable);
                        }
                    }
                }
            }
            break;
        case MEBA_EVENT_FLNK:
            rc = caracal_phy_event_enable(inst, VTSS_PHY_LINK_FFAIL_EV, enable);
            break;
        default:
            T_I(inst, "Unsupported Interrupt source %d", event_id);
            rc = MESA_RC_NOT_IMPLEMENTED;
    }

    return rc;
}

static mesa_rc sgpio_handler(meba_inst_t inst, meba_event_signal_t signal_notifier)
{
    mesa_rc             rc;
    int                 handled = 0;
    mesa_bool_t         sgpio_events[MESA_SGPIO_PORTS];
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t      port_no;
    meba_port_entry_t   entry;

    // Chip_no == 0, Group == 0 and bit == 0)
    if ((rc = mesa_sgpio_event_poll(NULL, 0, 0, 0, sgpio_events)) != MESA_RC_OK) {
        T_E(inst, "mesa_sgpio_event_poll = %d", rc);
        return rc;
    }

    // Poll SGPIO LOS from uplink ports
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        uint32_t sgpio_port;
        if (caracal_port_entry_get(inst, port_no, &entry) != MESA_RC_OK) {
            T_E(inst, "get port entry fail");
            break;
        }

        if (entry.map.chip_port != 24 && entry.map.chip_port != 25) {
            continue;
        }

        sgpio_port = entry.map.chip_port;
        if (sgpio_events[sgpio_port]) {
            // SGPIO port no
            if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, sgpio_port, 0, false)) != MESA_RC_OK) {
                T_E(inst, "mesa_sgpio_event_enable  = %d", rc);
            }
            T_I(inst, "LOS IRQ port %d gpio %d", port_no, sgpio_port);
            signal_notifier(MEBA_EVENT_LOS, port_no);
            handled++;
        }
    }
    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc ext0_handler(meba_inst_t inst,
                            meba_event_signal_t signal_notifier)
{
    int handled = 0;
    mesa_port_no_t port_no;
    meba_board_state_t *board = INST2BOARD(inst);
    meba_port_entry_t entry;

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (caracal_port_entry_get(inst, port_no, &entry) != MESA_RC_OK) {
            T_E(inst, "get port entry fail");
            break;
        }
        if (!is_phy_internal(entry.cap) && is_phy_port(entry.cap)) {
            if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                T_D(inst, "port(%d) PHY IRQ handled", port_no);
                handled++;
            }
        }
    }
    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc dev_all_handler(meba_inst_t inst,
                               meba_event_signal_t signal_notifier)
{
    mesa_dev_all_event_type_t  dev_all_events[MESA_CAP(MESA_CAP_PORT_CNT)];
    mesa_port_no_t port_no;
    meba_board_state_t *board = INST2BOARD(inst);
    meba_port_entry_t entry;

    if (mesa_dev_all_event_poll(NULL, MESA_DEV_ALL_POLL_ALL, dev_all_events) != MESA_RC_OK) {
        T_E(inst, "mesa_dev_all_event_poll failed");
        return MESA_RC_ERROR;
    }

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (caracal_port_entry_get(inst, port_no, &entry) != MESA_RC_OK) {
            T_E(inst, "get port entry fail");
            break;
        }
        if (dev_all_events[port_no] & MESA_DEV_ALL_LINK_EV) {

            T_I(inst, "DEV %d intr", port_no);
            if (entry.cap & MEBA_PORT_CAP_COPPER) {
                if (mesa_dev_all_event_enable(NULL, port_no, MESA_DEV_ALL_LINK_EV, false) != MESA_RC_OK) {
                    T_E(inst, "mesa_dev_all_event_enable failed");
                }

                if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                    T_D(inst, "port(%d) PHY IRQ handled", port_no);
                }

                // In some cases meba_generic_phy_event_check() doesn't re-enable the interrupt (due to chip issue).
                // Therefore it's done specifically here
                if (mesa_dev_all_event_enable(NULL, port_no, MESA_DEV_ALL_LINK_EV, true) != MESA_RC_OK) {
                    T_E(inst, "mesa_dev_all_event_enable failed");
                }
            }
        }
    }
    return MESA_RC_OK;
}

static mesa_rc caracal_irq_handler(meba_inst_t inst,
                                   mesa_irq_t chip_irq,
                                   meba_event_signal_t signal_notifier)
{
    T_I(inst, "Called - irq %d", chip_irq);

    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
            return meba_generic_ptp_handler(inst, signal_notifier);
        case MESA_IRQ_SGPIO:
            return sgpio_handler(inst, signal_notifier);
        case MESA_IRQ_EXT0:
            return ext0_handler(inst, signal_notifier);
        case MESA_IRQ_DEV_ALL:
            return dev_all_handler(inst, signal_notifier);
        default:;
    }

    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc caracal_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
        case MESA_IRQ_SGPIO:
        case MESA_IRQ_EXT0:
        case MESA_IRQ_DEV_ALL:
            rc = MESA_RC_OK;
            break;
        default:;
    }
    return rc;
}

meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t inst;
    meba_board_state_t *board;
    int                 i;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate pulic state
    if ((inst = meba_state_alloc(callouts,
                                 "Luton10",
                                 MESA_TARGET_CARACAL_1,
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Figure out the mux_mode (see also vtss_port_inst_create() in
    // .../base/ail/vtss_port_api.c).
    switch (inst->props.target) {
    case MESA_TARGET_SPARX_III_10:
    // case MESA_TARGET_SPARX_III_10_01: /* Only exists as VTSS_TARGET_xxx, not MESA_TARGET_xxx */
        inst->props.mux_mode = MESA_PORT_MUX_MODE_2;
        break;


    case MESA_TARGET_CARACAL_LITE:
    case MESA_TARGET_CARACAL_1:
    // case MESA_TARGET_SPARX_III_10_UM: /* Only exists as VTSS_TARGET_xxx, not MESA_TARGET_xxx */
        inst->props.mux_mode = MESA_PORT_MUX_MODE_1;
        break;

    default:
        inst->props.mux_mode = MESA_PORT_MUX_MODE_0;
    }

    // Initialize our state
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);
    if (meba_conf_get_hex(inst, "type", &i) == MESA_RC_OK) {
        board->type = (board_type_t) i;
        board->port_cnt = PDS_408G_NUM_PORTS;
        board->status_led_map = status_led_mapping_lu26;
        inst->props.board_type = VTSS_BOARD_LUTON10_PDS408G;  // Exposed temporarily
        board->status_led_map = status_led_mapping_lu10;
        board->fan_spec = &fan_conf_lu10;
    } else if (inst->props.target == MESA_TARGET_CARACAL_LITE ||
        inst->props.target == MESA_TARGET_SPARX_III_10 ||
        inst->props.target == MESA_TARGET_CARACAL_1) {
        board->type = BOARD_LUTON10;
        switch (inst->props.target) {
            case MESA_TARGET_CARACAL_LITE:
                board->port_cnt = 7;
                break;
            default:
                board->port_cnt = 10;
                break;
        }
        board->status_led_map = status_led_mapping_lu10;
        inst->props.board_type = (vtss_board_type_t) (VTSS_BOARD_LUTON10_REF + board->type);    // Exposed temporarily
        board->fan_spec = &fan_conf_lu10;
    } else {
        board->type = BOARD_LUTON26;
        switch (inst->props.target) {
            case MESA_TARGET_SPARX_III_18:
                board->port_cnt = 18;
                break;
            case MESA_TARGET_SPARX_III_24:
                board->port_cnt = 24;
                break;
            default:
                board->port_cnt = 26;
                break;
        }
        board->status_led_map = status_led_mapping_lu26;
        inst->props.board_type = (vtss_board_type_t) (VTSS_BOARD_LUTON10_REF + board->type);    // Exposed temporarily
        board->fan_spec = &fan_conf;
    }
    board->led_tower_mode = LED_TOWER_MODE_LINK_SPEED;
    board->tmp_timer = 0;
    T_I(inst, "Board: %s, type %d, target %4x, %d ports, mux_mode = %d", inst->props.name, board->type, inst->props.target, board->port_cnt, inst->props.mux_mode);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = caracal_capability;
    inst->api.meba_port_entry_get             = caracal_port_entry_get;
    inst->api.meba_reset                      = caracal_reset;
    inst->api.meba_sensor_get                 = caracal_sensor_get;
    inst->api.meba_sfp_i2c_xfer               = caracal_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = caracal_sfp_insertion_status_get;
    //inst->api.meba_sfp_status_get             = caracal_sfp_status_get;
    inst->api.meba_port_admin_state_set       = caracal_port_admin_state_set;
    inst->api.meba_status_led_set             = caracal_status_led_set;
    inst->api.meba_port_led_update            = caracal_port_led_update;
    inst->api.meba_led_intensity_set          = caracal_led_intensity_set;
    inst->api.meba_fan_param_get              = caracal_fan_param_get;
    inst->api.meba_fan_conf_get               = caracal_fan_conf_get;
    inst->api.meba_irq_handler                = caracal_irq_handler;
    inst->api.meba_irq_requested              = caracal_irq_requested;
    inst->api.meba_event_enable               = caracal_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_external_io_conf_get   = caracal_ptp_external_io_conf_get;
    inst->api_synce = meba_synce_get();
    inst->api_tod = meba_tod_get();
    inst->api_poe = meba_poe_get();

    return inst;
}
