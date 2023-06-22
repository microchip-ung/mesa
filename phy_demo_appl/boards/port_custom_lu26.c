// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// Avoid "vtss_api.h not used in module port_custom_lu26.c"
/*lint --e{766} */
#include "vtss_api.h"

#if defined(VTSS_SW_OPTION_PHY)
#include "phy_api.h" // For PHY_INST
#else
#define PHY_INST NULL
#endif

#if defined(VTSS_ARCH_LUTON26)

#include "port_custom_api.h"
#include "board_probe.h"

static int board_type;
static vtss_i2c_read_t    i2c_read;     /**< I2C read function */
/*lint -esym(459, i2c_write) Ok - Not to protect i2c_write with semaphore in this file*/
static vtss_i2c_write_t   i2c_write;    /**< I2C write function */

/*lint -esym(459, lu26_port_table) */
static port_custom_entry_t lu26_port_table[VTSS_PORT_ARRAY_SIZE];

/* SGPIO LED mapping */
typedef struct {
    u8  port;
    u8  bit;
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

/*lint -esym(459, s_led_tower_mode) */
static led_tower_mode_t s_led_tower_mode = LED_TOWER_MODE_LINK_SPEED;

#if defined(BOARD_LUTON26_REF)
static const sgpio_mapping_t tower_led_mapping[4][2] = {
    {{2, 2} /* tower 0 green */, {3, 2} /* tower 0 yellow */},
    {{4, 2} /* tower 1 green */, {5, 2} /* tower 1 yellow */},
    {{6, 2} /* tower 2 green */, {6, 2} /* tower 2 yellow */},
    {{8, 2} /* tower 3 green */, {7, 2} /* tower 3 yellow */}
};

static const sgpio_mapping_t port_led_mapping[VTSS_PORT_ARRAY_SIZE][2] = {
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
    [VTSS_PORTS - 2] = {{24, 0} /* port 24 green */, {24, 1} /* port 24 yellow */},
    [VTSS_PORTS - 1] = {{25, 0} /* port 25 green */, {25, 1} /* port 25 yellow */}
};
#endif /* BOARD_LUTON26_REF */

#if defined(BOARD_LUTON10_REF)
static const sgpio_mapping_t tower_led_mapping[4][2] = {
    {{20, 0} /* tower 0 green */, {20, 1} /* tower 0 yellow */},
    {{21, 0} /* tower 1 green */, {21, 1} /* tower 1 yellow */},
    {{22, 0} /* tower 2 green */, {22, 1} /* tower 2 yellow */},
    {{23, 0} /* tower 3 green */, {23, 1} /* tower 3 yellow */}
};

static const sgpio_mapping_t port_led_mapping[VTSS_PORT_ARRAY_SIZE][2] = {
    [0] = {{ 0, 0} /* port  0 green */, { 0, 1} /* port  0 yellow */},
    [1] = {{ 1, 0} /* port  1 green */, { 1, 1} /* port  1 yellow */},
    [2] = {{ 2, 0} /* port  2 green */, { 2, 1} /* port  2 yellow */},
    [3] = {{ 3, 0} /* port  3 green */, { 3, 1} /* port  3 yellow */},
    [4] = {{ 4, 0} /* port  4 green */, { 4, 1} /* port  4 yellow */},
#if (VTSS_PORTS > 7)
    [5] = {{ 5, 0} /* port  5 green */, { 5, 1} /* port  5 yellow */},
    [6] = {{ 6, 0} /* port  6 green */, { 6, 1} /* port  6 yellow */},
    [7] = {{ 7, 0} /* port  7 green */, { 7, 1} /* port  7 yellow */},
#endif /* VTSS_PORTS > 7 */
    [VTSS_PORTS - 2] = {{24, 0} /* port 24 green */, {24, 1} /* port 24 yellow */},
    [VTSS_PORTS - 1] = {{25, 0} /* port 25 green */, {25, 1} /* port 25 yellow */}
};
#endif /* BOARD_LUTON10_REF */

#if defined(BOARD_LUTON10_REF) || defined(BOARD_LUTON26_REF)
static void lu26_led_tower_update(led_tower_mode_t led_tower_mode)
{
    vtss_sgpio_conf_t conf;
    int               i;

    /*
     * LED tower:
     *  (top)       o  mode A (link/speed)
     *              o  mode B (link/duplex)
     *              o  mode C (link/status)
     *  (button)    o  PWR save
     */
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) != VTSS_RC_OK) {
        return;
    }
    for (i = 0; i < 4; i++) {
        conf.port_conf[tower_led_mapping[i][0].port].mode[tower_led_mapping[i][0].bit] =
        conf.port_conf[tower_led_mapping[i][1].port].mode[tower_led_mapping[i][1].bit] =
        VTSS_SGPIO_MODE_OFF;
    }
    switch (led_tower_mode) {
        case LED_TOWER_MODE_LINK_SPEED:
            conf.port_conf[tower_led_mapping[0][0].port].mode[tower_led_mapping[0][0].bit] = VTSS_SGPIO_MODE_ON;
            break;
        case LED_TOWER_MODE_DUPLEX:
            conf.port_conf[tower_led_mapping[1][0].port].mode[tower_led_mapping[1][0].bit] = VTSS_SGPIO_MODE_ON;
            break;
        case LED_TOWER_MODE_LINK_STATUS:
            conf.port_conf[tower_led_mapping[2][0].port].mode[tower_led_mapping[2][0].bit] = VTSS_SGPIO_MODE_ON;
            break;
        case LED_TOWER_MODE_POWER_SAVE:
            conf.port_conf[tower_led_mapping[3][0].port].mode[tower_led_mapping[3][0].bit] = VTSS_SGPIO_MODE_ON;
            break;
        default:
            return;
    }
    (void) vtss_sgpio_conf_set(NULL, 0, 0, &conf);
}
#endif

#if defined(BOARD_LUTON10_REF) || defined(BOARD_LUTON26_REF)
static void lu26_sgpio_led_set(vtss_port_no_t port_no,
                               led_color_t color,
                               vtss_sgpio_mode_t mode,
                               vtss_sgpio_conf_t *conf)
{
    conf->port_conf[port_led_mapping[port_no][color].port].mode[port_led_mapping[port_no][color].bit] = mode;
}
#endif

/* Release ports from reset */
static vtss_rc lu26_reset(void)
{
    vtss_rc rc = VTSS_RC_OK;
    vtss_port_no_t port_idx;

    if (board_type == VTSS_BOARD_LUTON10_REF) {
        // Call pre-reset (Must be first port)
        rc = vtss_phy_pre_reset(PHY_INST, 0);
    } else {
        // Call pre-reset (Must be first port)

        // Internal PHY
        if ((rc = vtss_phy_pre_reset(PHY_INST, 0)) != VTSS_RC_OK) {
            return rc;
        }
        // External PHY (Atom12)
        rc = vtss_phy_pre_reset(PHY_INST, 12);

        // Setup dual media port (fiber/cu), PHY 13 is external Atom12 PHY w/dual-media
        (void) vtss_phy_write_masked(NULL, 13, 19 | VTSS_PHY_REG_GPIO, 0x8000, 0xC000); // Enable fiber-media SerDes in HSIO
        (void) vtss_phy_write(NULL, 13, 18 | VTSS_PHY_REG_GPIO, 0x8f81);

        // SFP Signal detect shall be active low (register 19E1 bit 1 = TRUE)
        // Dual media ports (user port 21-24)
        for (port_idx = 20; port_idx < 24; port_idx++) {
            (void) vtss_phy_write_masked(NULL, port_idx, 19 |VTSS_PHY_REG_EXTENDED , 0x1, 0x1);
        }
    }
    return rc;
}


/* Post ports reset */
static vtss_rc lu26_post_reset(void)
{
    return vtss_phy_post_reset(PHY_INST, 0);
}


/* Initialize port LEDs */
static vtss_rc lu26_led_init(void)
{
    vtss_port_no_t port;
    if (board_type == VTSS_BOARD_LUTON26_REF) {
        /* Setup LED_PWM */
        /* GPIO_8 is primarily used as LED1 for port 3 (external PHY) - it is at internal port 15 */
        (void) vtss_phy_write_masked(NULL, 15, 29, 0x00F0, 0x00F0);

        // Make sure that SFP led are turned off
        for (port = 20; port < 24; port ++) {
            (void) vtss_phy_write_masked(NULL, port, 29, 0xE, 0xF);
        }

        // Phy ports 12-15 gpios are connected  to the SFP yellow LEDs (See Schematic), but we don't use them, so we need
        // to make sure that they are turned off.
        for (port = 12; port < 16; port ++) {
            (void) vtss_phy_write_masked(NULL, port, 29, 0xE, 0xF);
        }
    }
#if defined(BOARD_LUTON10_REF) || defined(BOARD_LUTON26_REF)
    /* Initial LED tower */
    lu26_led_tower_update(LED_TOWER_MODE_LINK_SPEED);
#endif

#if defined(BOARD_LUTON10_REF)
    // For Luton 10 reference board the LED pwm is in fact the FAN
    // controller PWM, so we need to initialize fan controller.
    {
        vtss_fan_conf_t fan_spec;
        fan_spec.fan_pwm_freq = VTSS_FAN_PWM_FREQ_25KHZ;
        fan_spec.fan_low_pol  = TRUE;
        fan_spec.fan_open_col = FALSE;
        (void) vtss_fan_controller_init(PHY_INST, &fan_spec );
    }
#endif

    return VTSS_RC_OK;
}


vtss_rc lu26_led_intensity(vtss_phy_led_intensity intensity)
{
#if defined(BOARD_LUTON26_REF)
    // For Luton 26 reference board the LED pwm pin is connected at
    // the ATOM12 chip (phy ports 13-24), GPIO 8. Therefore port 13 is
    // used
    return vtss_phy_led_intensity_set(PHY_INST, 13, intensity);
#elif defined(BOARD_LUTON10_REF)
    // For Luton 10 reference board the LED pwm is in fact the FAN
    // controller PWM, so we need to used vtss_fan_cool_lvl_set which
    // can be set from 0 to 255. We need to convert from percent to
    // 0-255
    return vtss_fan_cool_lvl_set(PHY_INST, intensity * 255 / 100);
#else
    return VTSS_RC_ERROR;
#endif
}

/* Update fiber port LED */
static void lu26_fiber_port_led_update(led_tower_mode_t led_tower_mode,
                                       vtss_port_no_t port_no,
                                       BOOL              link)
{
    u16 val = 0xE; // 0xE = Turn off LED
    u16 mask = 0x000F;

    if (led_tower_mode != LED_TOWER_MODE_POWER_SAVE && link) {
        val = 0x000F;
    }

    (void) vtss_phy_write_masked(NULL, port_no, 29, val, mask);
}

// Function for doing SFP i2c reads. The luton26 board supports 2 types of I2C controllers. One in the switch,
// and one in the ATOM12 PHY. The one in the switch is used for uplink SFPs, while the one in the PHY is used for the dual media SFPs.
// In : port_no - The physical port number
//      i2c_addr - The address for the i2c device
//      addr     - The address with the i2c device to access.
//      cnt      - The number of data to read
// In/Out  data     - The data read
static vtss_rc lu26_sfp_i2c_read(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, u8 cnt, BOOL word_acess)
{
    // Dual media SFP ports - Connected to PHY i2c
    if (port_no >= 20 && port_no <= 23) {
        // Due to a hardware board issue only SFP i2c mux 0 works, so that is always used.
        return vtss_phy_i2c_read(NULL, port_no, 0, addr, i2c_addr, word_acess, cnt, data);
    } else {
        // Uplink ports - Connected to switch i2c
        if (i2c_read != NULL) {
            return i2c_read(port_no, i2c_addr, addr, data, cnt);
        }
    } 
    return VTSS_RC_ERROR;
}

static vtss_rc lu26_sfp_i2c_write(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, BOOL word_acess)
{
    u8 i2c_data[3];
    // Dual media SFP ports - Connected to PHY i2c
    if (port_no >= 20 && port_no <= 23) {
        // Due to a hardware board issue only SFP i2c mux 0 works, so that is always used.
        return vtss_phy_i2c_write(NULL, port_no, 0, addr, i2c_addr, word_acess, 2, data);
    } else {
        // Uplink ports - Connected to switch i2c
        if (i2c_write != NULL) {
            i2c_data[0] = addr;
            memcpy(&i2c_data[1], data, 2);
            return i2c_write(port_no, i2c_addr, i2c_data, 3);
        }
    }
    return VTSS_RC_ERROR;
}

static vtss_rc lu26_sfp_mod_detect(BOOL *detect_status)
{
    vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS];
    vtss_port_no_t port_no;
    u16  i;

    if (vtss_sgpio_read(NULL, 0, 0, data) != VTSS_RC_OK)
        return VTSS_RC_ERROR;

  if (board_type == VTSS_BOARD_LUTON26_REF) {

      // Note : SFP ports 22-24 do't work due to a hardware board bug with the I2C clocks for these ports, so them we ignore.
      // Work around for that dual-media port swapped at the board where port20 = SFP2. See UG1037, Table 11.
      detect_status[20] = data[21].value[2] ? 0 : 1;  /* Bit 2 is mod_detect, 0=detected */


      // SFP uplink ports
      for(port_no = VTSS_PORTS-2; port_no < VTSS_PORTS; port_no++) {
          detect_status[port_no] = data[port_no - VTSS_PORT_NO_START].value[2] ? 0 : 1;  /* Bit 2 is mod_detect, 0=detected */
      }
  } else if(board_type == VTSS_BOARD_LUTON10_REF) {
      for(port_no = VTSS_PORTS-2, i = 26; port_no < VTSS_PORTS; port_no++, i++) {
          detect_status[port_no] = data[i].value[1] ? 0 : 1;  /* Bit one is mod_detect, 0=detected */
      }
  }
    return VTSS_RC_OK;
}

/* Update port LED */
static vtss_rc lu26_led_update(vtss_port_no_t port_no,
                               vtss_port_status_t *status,
                               vtss_port_counters_t *counters,
                               port_custom_conf_t *port_conf)
{
    /*lint -esym(459, status_old, port_collision_cnt) */
    static vtss_port_status_t   status_old[VTSS_PORTS];
    static vtss_port_counter_t  port_collision_cnt[VTSS_PORTS];
    BOOL                        need_process = FALSE, tower_mode_changed = FALSE, collision = FALSE;
    BOOL                        gpio_val;
    vtss_port_no_t              port_idx = port_no, process_cnt = port_no + 1;
    vtss_sgpio_conf_t           conf;
    u16                         reg;
    BOOL                        fiber;

    /* Check if port's link/speed/fdx has changed */
    if (status_old[port_no].link != status->link ||
        (status_old[port_no].link == status->link && (status_old[port_no].speed != status->speed || status_old[port_no].fdx != status->fdx))) {
        need_process = TRUE;
    }
    status_old[port_no] = *status;

    /* Check if port collision occured */
    if (s_led_tower_mode == LED_TOWER_MODE_DUPLEX &&
        status->link &&
        !status->fdx &&
        port_collision_cnt[port_no] != counters->rmon.tx_etherStatsCollisions) {
        need_process = TRUE;
        collision = TRUE;
    }
    port_collision_cnt[port_no] = counters->rmon.tx_etherStatsCollisions;

    /* Push button: GPIO bit 12.
       Don't need polling tower moce each time. */
    if ((port_no % 4) == 0 && vtss_gpio_read(NULL, 0, 12, &gpio_val) == VTSS_RC_OK && gpio_val == TRUE) {
        tower_mode_changed = TRUE;
        s_led_tower_mode = (led_tower_mode_t)((s_led_tower_mode + 1) % LED_TOWER_MODE_CNT);

        /* Update LED tower */
        lu26_led_tower_update(s_led_tower_mode);

        /* Update all ports LED status */
        port_idx = VTSS_PORT_NO_START;
        process_cnt = VTSS_PORTS;
    }

    /* Return here if nothing has changed or in power saving mode */
    if ((!need_process && !tower_mode_changed) ||
        (!tower_mode_changed && s_led_tower_mode == LED_TOWER_MODE_POWER_SAVE)) {
        return VTSS_RC_OK;
    }

    /* Update port LEDs */
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) == VTSS_RC_OK) {
        for (; port_idx < process_cnt; port_idx++) {
            lu26_sgpio_led_set(port_idx, LED_GREEN, VTSS_SGPIO_MODE_OFF, &conf);
            lu26_sgpio_led_set(port_idx, LED_YELLOW, VTSS_SGPIO_MODE_OFF, &conf);

            if (board_type == VTSS_BOARD_LUTON26_REF) {
                fiber = FALSE;
                if (lu26_port_table[port_idx].cap & (PORT_CAP_SPEED_DUAL_ANY_FIBER)) {

                    /* Read Media Mode  status */
                    (void) vtss_phy_read(NULL, port_idx, 20 | VTSS_PHY_REG_EXTENDED, &reg);
                    fiber = (((reg >> 6) & 0x3) == 2 ? 1 : 0);
                    if (fiber || !status_old[port_idx].link) {
                        lu26_fiber_port_led_update(s_led_tower_mode, port_idx, status_old[port_idx].link);
                    }
                }
            }

            switch (s_led_tower_mode) {
                case LED_TOWER_MODE_LINK_SPEED:
                    if (status_old[port_idx].link) {
                        if (status_old[port_idx].speed >= VTSS_SPEED_1G) {
                            /* Green: 1G link/activity */
                            lu26_sgpio_led_set(port_idx, LED_GREEN, VTSS_SGPIO_MODE_0_ACTIVITY_INV, &conf);
                        } else {
                            /* Yellow: 100/10 link/activity */
                            lu26_sgpio_led_set(port_idx, LED_YELLOW, VTSS_SGPIO_MODE_0_ACTIVITY_INV, &conf);
                        }
                    }
                break;
                case LED_TOWER_MODE_DUPLEX:
                    if (status_old[port_idx].link) {
                        if (status_old[port_idx].fdx) {
                            /* Green: FDX */
                            lu26_sgpio_led_set(port_idx, LED_GREEN, VTSS_SGPIO_MODE_0_ACTIVITY_INV, &conf);
                        } else if (port_idx == port_no && collision) {
                            /* Blink yellow: HDX with collision */
                            lu26_sgpio_led_set(port_idx, LED_YELLOW, VTSS_SGPIO_MODE_0, &conf);
                        } else {
                            /* Yellow: HDX without collision */
                            lu26_sgpio_led_set(port_idx, LED_YELLOW, VTSS_SGPIO_MODE_ON, &conf);
                        }
                    }
                break;
                case LED_TOWER_MODE_LINK_STATUS:
                    if (status_old[port_idx].link) {
                        /* Green: link on */
                        lu26_sgpio_led_set(port_idx, LED_GREEN, VTSS_SGPIO_MODE_ON, &conf);
                    }
                break;
                case LED_TOWER_MODE_POWER_SAVE:
                break;
                default:
                break;
            }
        }
        (void) vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }

    return VTSS_RC_OK;
}

/* Switch the SFP modules on/off using the SGPIOs */
static vtss_rc lu26_sfp_power_set(vtss_port_no_t port_no, BOOL enable)
{
    vtss_sgpio_conf_t conf;
    u32 chipport = lu26_port_table[port_no].map.chip_port;

    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) != VTSS_RC_OK) {
        return VTSS_RC_ERROR;
    }
    if (board_type == VTSS_BOARD_LUTON10_REF) {
        if (chipport == 24) {
            conf.port_conf[30].mode[0] = enable ? VTSS_SGPIO_MODE_ON : VTSS_SGPIO_MODE_OFF;
        } else if (chipport == 25) {
            conf.port_conf[31].mode[0] = enable ? VTSS_SGPIO_MODE_ON : VTSS_SGPIO_MODE_OFF;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    } else if (board_type == VTSS_BOARD_LUTON26_REF) {
        if (chipport == 24) {
            conf.port_conf[26].mode[2] = enable ? VTSS_SGPIO_MODE_ON : VTSS_SGPIO_MODE_OFF;
        } else if (chipport == 25) {
            conf.port_conf[27].mode[1] = enable ? VTSS_SGPIO_MODE_ON : VTSS_SGPIO_MODE_OFF;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return VTSS_RC_OK;
}

static void lu26_port_conf(vtss_port_no_t port_no, port_custom_conf_t *port_conf)
{
    /*  Enable/disable SFP module 'Tx_disable' */
    (void)lu26_sfp_power_set(port_no, port_conf->enable);
}

// lu26_pre_reset(), called before system reset.
// Disables the SGPIO controller and waits the required amount of time for it to settle.
// The potential problem is that: When resetting the SIO controller (and GPIOs)
// when the chain is only partially shifted out is that; if the shift registers on
// the PCB latches the data during reset (i.e. GPIO latch / clk is tristating and
// then being pulled to an active value) then all sorts of bad things can happen
//(for example a customers could use serial GPIO controlling board reset).
static void lu26_pre_reset(void)
{
    vtss_gpio_no_t gpio;

    /* Disable SGPIO controller (GPIO 0-3 for SGPIO) */
    for (gpio = 0; gpio < 4; gpio++) {
        (void) vtss_gpio_mode_set(NULL, 0, gpio, VTSS_GPIO_IN);
    }
    VTSS_MSLEEP(10); /* Waits a period time */

    if (board_type == VTSS_BOARD_LUTON10_REF) {
        (void) vtss_phy_pre_system_reset(NULL, 0);
    } else {
        // Internal PHY
        (void) vtss_phy_pre_system_reset(NULL, 0);

        // External PHY (Atom12)
        (void) vtss_phy_pre_system_reset(NULL, 12);
    }

    // Put in coma mode during reboot. If not in coma mode during reboot, the link can come up before tat system is initialized, and that can generate CRC errors if frames are transmitted as soon as there is linkup.
    (void) vtss_phy_coma_mode_enable(NULL, 0); // Shall use the same port as used in the vtss_phy_post_reset function
}

// Function for doing special port initialization that depends upon the platform
static void lu26_init(void)
{
    vtss_gpio_no_t    gpio;
    vtss_sgpio_conf_t conf;
    u32               port;


    /* Enable GPIO 0-3 as SGPIO pins */
    for (gpio = 0; gpio < 4; gpio++) {
        (void) vtss_gpio_mode_set(NULL, 0, gpio, VTSS_GPIO_ALT_0);
    }

    /* Setup SGPIO */
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collion in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        if (board_type == VTSS_BOARD_LUTON26_REF) {
            conf.bit_count = 3;
            for (port = 0; port < VTSS_SGPIO_PORTS; port++)
                conf.port_conf[port].enabled = 1;
            conf.port_conf[26].mode[2] = VTSS_SGPIO_MODE_ON; /* SFP0 Tx enable */
            conf.port_conf[27].mode[1] = VTSS_SGPIO_MODE_ON; /* SFP1 Tx enable */

            conf.port_conf[28].mode[0] = VTSS_SGPIO_MODE_ON; /* SFP2 Tx enable */
            conf.port_conf[28].mode[1] = VTSS_SGPIO_MODE_ON; /* SFP3 Tx enable */
            conf.port_conf[28].mode[2] = VTSS_SGPIO_MODE_ON; /* SFP4 Tx enable */
            conf.port_conf[29].mode[0] = VTSS_SGPIO_MODE_ON; /* SFP5 Tx enable */
        }
        if (board_type == VTSS_BOARD_LUTON10_REF) {
            conf.bit_count = 2;
            for (port = 0; port < VTSS_SGPIO_PORTS; port++)
                conf.port_conf[port].enabled = (port < 8 || port > 19 ? 1 : 0);
            conf.port_conf[30].mode[0] = VTSS_SGPIO_MODE_ON; /* SFP0 Tx enable */
            conf.port_conf[31].mode[0] = VTSS_SGPIO_MODE_ON; /* SFP1 Tx enable */
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }
}
/***************************************************************************
 * Fan
 ***************************************************************************/
static vtss_rc lu26_fan_init(vtss_fan_conf_t fan_spec) {
    return vtss_fan_controller_init(NULL, &fan_spec);
}

/*
 * Lu26/Lu10 temperature sensor.
 */
static vtss_rc lu26_temp_sensors_init(void) {
#ifdef BOARD_LUTON26_REF
    // The Luton26 board has a temperature sensor in Luton26 (ports 0-11) and one in Atom12 (ports 12-24)
    if ((vtss_phy_chip_temp_init(PHY_INST, 0) == VTSS_RC_OK &&
         vtss_phy_chip_temp_init(PHY_INST, 12) == VTSS_RC_OK)) {
        return VTSS_RC_OK;
    }
#elif defined(BOARD_LUTON10_REF)
    // The Luton10 board has a temperature sensor in the internal PHY.
    if (vtss_phy_chip_temp_init(PHY_INST, 0) == VTSS_RC_OK) {
        return VTSS_RC_OK;
    }
#endif
    return VTSS_RC_ERROR;
}


static vtss_rc lu26_temp_sensors_get(vtss_port_no_t iport, i16 *temp) {
#ifdef BOARD_LUTON26_REF
    // The Luton26 board has a temperature sensor in Luton26 (ports 0-11) and one in Atom12 (ports 12-24)
    return vtss_phy_chip_temp_get(PHY_INST, (iport < 12) ? 0: 12, temp);
#elif defined(BOARD_LUTON10_REF)
    // The Luton10 board has a temperature sensor in the internal PHY.
    return vtss_phy_chip_temp_get(PHY_INST, 0, temp);
#endif
}

static u8 lu26_temp_sensors_cnt(void) {
#ifdef BOARD_LUTON26_REF
    // The Luton26 board has a temperature sensor in Luton26 (ports 0-11) and one in Atom12 (ports 12-24)
    return 2;
#elif defined(BOARD_LUTON10_REF)
    // The Luton10 board has a temperature sensor in the internal PHY.
    return 1;
#endif
}


/*
 * Lu26/Lu10 board probe function.
 */
BOOL vtss_board_probe_lu26(vtss_board_t *board, vtss_board_info_t *board_info)
{
    /*lint -esym(459, i2c_read, board_type) */
    BOOL                uplink1 = TRUE;
    vtss_port_no_t      port_no;
    port_custom_entry_t *entry;

    memset(board, 0, sizeof(*board));
    i2c_read   = board_info->i2c_read;
    i2c_write  = board_info->i2c_write;

    board_type = board_info->board_type;
    if (board_type != VTSS_BOARD_LUTON26_REF && board_type != VTSS_BOARD_LUTON10_REF) {
#if (VTSS_PORTS > 11)
        board_type = VTSS_BOARD_LUTON26_REF;
#else
        board_type = VTSS_BOARD_LUTON10_REF;
#endif /* VTSS_PORTS > 11 */
    }

    board->type = (vtss_board_type_t)board_type;
    board_info->board_type = board_type;
    board->features =
        VTSS_BOARD_FEATURE_AMS |
        VTSS_BOARD_FEATURE_LOS |
        VTSS_BOARD_FEATURE_VCXO;
    switch(board_type) {
    case VTSS_BOARD_LUTON10_REF:
        board->name = "Luton10";
        break;
    case VTSS_BOARD_LUTON26_REF:
        board->name = "Luton26";
        board->features |= VTSS_BOARD_FEATURE_POE;
        break;
    }
    board->custom_port_table = lu26_port_table;

    board->init = lu26_init;
    board->reset = lu26_reset;
    board->pre_reset = lu26_pre_reset;
    board->post_reset = lu26_post_reset;
    board->led_init = lu26_led_init;
    board->led_update = lu26_led_update;
    board->led_intensity = lu26_led_intensity;
    board->port_conf = lu26_port_conf;
    board->sfp_i2c_read = lu26_sfp_i2c_read;
    board->sfp_i2c_write = lu26_sfp_i2c_write;
    board->sfp_mod_detect = lu26_sfp_mod_detect;
    board->board_fan_init          = lu26_fan_init;
    board->board_temp_sensors_init = lu26_temp_sensors_init;
    board->board_temp_sensors_get  = lu26_temp_sensors_get;
    board->board_temp_sensors_cnt  = lu26_temp_sensors_cnt;

#if defined(VTSS_CHIP_CARACAL_1) || defined(VTSS_CHIP_CARACAL_LITE)
#define CAP_UPLINK_1 PORT_CAP_SFP_2_5G
#define CAP_UPLINK_2 PORT_CAP_SFP_2_5G
#elif defined(VTSS_CHIP_CARACAL_2)
#define CAP_UPLINK_1 PORT_CAP_SFP_1G
#define CAP_UPLINK_2 PORT_CAP_SFP_2_5G
#else
#define CAP_UPLINK_1 PORT_CAP_SFP_1G
#define CAP_UPLINK_2 PORT_CAP_SFP_1G
#endif

    for (port_no = 0; port_no < board_info->port_count; port_no++) {
        entry = &lu26_port_table[port_no];
        if (port_no >= (board_info->port_count - 2)) {
            /* SFP ports */
            entry->map.chip_port = (uplink1 ? 24 : 25);
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->mac_if = VTSS_PORT_INTERFACE_SERDES;
            entry->cap = ((uplink1 ? CAP_UPLINK_1 : CAP_UPLINK_2) | PORT_CAP_SFP_SD_HIGH);
            uplink1 = FALSE;
#if (VTSS_PORTS > 12) /* Avoid compiler warning */
        } else if (port_no >= 12) {
            /* Copper ports with external PHY */
            entry->map.chip_port = port_no;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_1;
            entry->map.miim_addr = (port_no - 12);
            entry->mac_if = VTSS_PORT_INTERFACE_QSGMII;
            /* For dual media ports (iport 20-23), SFP auto detection only works for iport 20 */
            entry->cap = (port_no < 20 ? PORT_CAP_TRI_SPEED_COPPER :
                          port_no == 20 ? PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER :
                          PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER_FIXED_SFP_SPEED);

#ifdef VTSS_SW_OPTION_POE
            entry->poe_support   =  (port_no < 24);
            entry->poe_chip_port =  entry->map.chip_port;
#endif
#endif
        } else {
            /* Copper ports with internal PHY */
            entry->map.chip_port = port_no;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
            entry->map.miim_addr = port_no;
            entry->mac_if = VTSS_PORT_INTERFACE_SGMII;
            entry->cap = PORT_CAP_TRI_SPEED_COPPER | PORT_CAP_INT_PHY;
#ifdef VTSS_SW_OPTION_POE
            entry->poe_support   =  TRUE;
            entry->poe_chip_port =  entry->map.chip_port;
#endif

        }
    }
    return TRUE;
}

#endif /* defined(VTSS_ARCH_LUTON26) */

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
