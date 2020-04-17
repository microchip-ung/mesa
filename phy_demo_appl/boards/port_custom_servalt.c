// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// Avoid "*.h not used in module port_custom_srvlt.c"
/*lint --e{766} */
#include "port_custom_api.h"
#include "board_probe.h"

#if defined(VTSS_SW_OPTION_PHY)
#include "phy_api.h" // For PHY_INST
#else
#define PHY_INST NULL
#endif
#if defined(VTSS_ARCH_SERVAL_T)
#define VTSS_RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }
#if defined(VTSS_TRACE_ENABLE)
#define VTSS_TRACE_MODULE_ID VTSS_MODULE_ID_API_AI
#define CUSTOM_D(...)  T_D(__VA_ARGS__)
#define CUSTOM_I(...)  T_I(__VA_ARGS__)
#define CUSTOM_N(...)  T_N(__VA_ARGS__)
#else
#define CUSTOM_D(...)
#define CUSTOM_I(...)
#define CUSTOM_N(...)
#endif

/*lint -esym(459, jr2_i2c_read) OK not to protect jr2_i2c_read with semaphore in this file */
static vtss_i2c_read_t    srvlt_i2c_read;     /**< I2C read function */

/*lint -esym(459, jr2_i2c_write) OK not to protect jr2_i2c_write with semaphore in this file */
static vtss_i2c_write_t   srvlt_i2c_write;    /**< I2C write function */


typedef struct {
    vtss_port_counters_t cnt;
    vtss_port_status_t   status;
    BOOL                 activity;
} srvlt_port_info_t;

/* ServalT NPI chip port */
#define SRVLT_NPI_CHIP_PORT 4

/*lint -esym(459, srvlt_port_table) */
static port_custom_entry_t srvlt_port_table[VTSS_PORT_ARRAY_SIZE];
static srvlt_port_info_t srvlt_old_port_info[VTSS_PORT_ARRAY_SIZE];

/* LED tower mode */
typedef enum {
    LED_TOWER_MODE_LINK_SPEED,      /**< Green: 1G link/activity; Orange: 10/100 link/activity */
    LED_TOWER_MODE_DUPLEX_SPEED,    /**< Green: FDX; Orange: HDX + Collisions */
    LED_TOWER_MODE_LINK_STATUS,     /**< Green: Link/activity; Orange: port disabled/errors */
    LED_TOWER_MODE_POWER_SAVE,      /**< Disabled to save power */
    LED_TOWER_MODE_CNT
} led_tower_mode_t;

#if !defined(BOARD_HW_NO_LED_TOWER)
/*lint -esym(459, s_led_tower_mode) */
static led_tower_mode_t s_led_tower_mode = LED_TOWER_MODE_POWER_SAVE; // Power save mode is in fact not going to be the init state,
#else
static led_tower_mode_t s_led_tower_mode = LED_TOWER_MODE_LINK_SPEED;
#endif
                                                                      // because the led_tower_update function starts by incrementing the state,
#if !defined(BOARD_HW_NO_LED_TOWER)
/* SGPIO LED mapping */
typedef struct {
    u8  port;
    u8  bit;
} sgpio_mapping_t;


static const sgpio_mapping_t tower_led_mapping[4][2] = {
    {{2, 2} /* tower 0 green */, {2, 3} /* tower 0 yellow */},
    {{3, 2} /* tower 1 green */, {3, 3} /* tower 1 yellow */},
    {{4, 2} /* tower 2 green */, {4, 3} /* tower 2 yellow */},
    {{5, 2} /* tower 3 green */, {5, 3} /* tower 3 yellow */}
};

void led_tower_update(void)
{
    vtss_sgpio_conf_t conf;
    int               i;

    s_led_tower_mode = (led_tower_mode_t)((s_led_tower_mode + 1) % LED_TOWER_MODE_CNT);

    CUSTOM_I("Update LED mode to %d", s_led_tower_mode);
    /*
     * LED tower:
     *  (top)       o  mode A (link/speed)
     *              o  mode B (link/duplex)
     *              o  mode C (synce)
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

    switch (s_led_tower_mode) {
        case LED_TOWER_MODE_LINK_SPEED:
            i = 0;
            break;
        case LED_TOWER_MODE_DUPLEX_SPEED:
            i = 1;
            break;
        case LED_TOWER_MODE_LINK_STATUS:
            i = 2;
            break;
        case LED_TOWER_MODE_POWER_SAVE:
            i = 3;
            break;
        default:
            return;
    }
    conf.port_conf[tower_led_mapping[i][0].port].mode[tower_led_mapping[i][0].bit] = VTSS_SGPIO_MODE_ON;
    CUSTOM_D("p%db%d : %d", tower_led_mapping[i][0].port, tower_led_mapping[i][0].bit, conf.port_conf[tower_led_mapping[i][0].port].mode[tower_led_mapping[i][0].bit]);
    (void) vtss_sgpio_conf_set(NULL, 0, 0, &conf);
}
#endif /* !BOARD_HW_NO_LED_TOWER */

static vtss_rc srvlt_nid_i2c_read(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, u8 cnt, BOOL word_access)
{
    if (srvlt_i2c_read != NULL) {
        CUSTOM_D("i2c_addr:0x%X, cnt:%d, addr:%0xX\n", i2c_addr, cnt, addr);
        return srvlt_i2c_read(port_no, i2c_addr, addr, data, cnt);
    }
    return VTSS_RC_ERROR;
}

static vtss_rc srvlt_nid_i2c_write(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, BOOL word_access)
{
    if (srvlt_i2c_write != NULL) {
        u8 i2c_data[3];
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        return srvlt_i2c_write(port_no, i2c_addr, i2c_data, 3);
    }

    return VTSS_RC_ERROR;
}

/***************************************************************************
 * Fan
 ***************************************************************************/
static vtss_rc srvlt_fan_init(vtss_fan_conf_t fan_spec) {
    return vtss_fan_controller_init(NULL, &fan_spec);
}

/************************************************************************/
/* Temp sensors                                                         */
/************************************************************************/

static vtss_rc srvlt_temp_sensors_init(void) {
    // PCB 106 has one PHY containing a temperature sensor, and it is the same sensor for all ports so we simply use port 0.
    return vtss_phy_chip_temp_init(PHY_INST, 0);
}

static vtss_rc srvlt_temp_sensors_get(vtss_port_no_t iport, i16 *temp) {
    // PCB 106 has one PHY containing a temperature sensor, and it is the same sensor for all ports so we simply use port 0.
    return vtss_phy_chip_temp_get(PHY_INST, 0, temp);

}

static u8 srvlt_temp_sensors_cnt(void) {
    // PCB 106 has one PHY containing a temperature sensor.
    return 1;
}

/************************************************************************/

/* Called from port thread */
static void srvlt_init(void)
{
    vtss_sgpio_conf_t conf;
    u32               port, gpio_no;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 22; gpio_no <= 23; gpio_no++) {
        (void)vtss_gpio_mode_set(NULL, 0, gpio_no, VTSS_GPIO_ALT_0);
    }

    /* GPIO pins 0-3 are used for SGPIOs. */
    (void)vtss_gpio_mode_set(NULL, 0, 0, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)vtss_gpio_mode_set(NULL, 0, 1, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 2, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)vtss_gpio_mode_set(NULL, 0, 3, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / LD

    /* Setup SGPIO group 0          */
    /* Controls Port LEDs 1-8 + NPI */
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collisions in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 4;
        // Turn the LEDs initially off
        for (port = 0; port <= 6; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  VTSS_SGPIO_MODE_OFF;
            conf.port_conf[port].mode[1] =  VTSS_SGPIO_MODE_OFF;
        }
        for (port = 9; port <= 10; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  VTSS_SGPIO_MODE_OFF;
            conf.port_conf[port].mode[1] =  VTSS_SGPIO_MODE_OFF;
        }
        // Enable RateSel/TxDisable ports
        for (port = 11; port <= 15; port++) {
            conf.port_conf[port].enabled = 1;
        }

        // Status LED ON
        conf.port_conf[6].mode[2] =  VTSS_SGPIO_MODE_ON;
        conf.port_conf[6].mode[3] =  VTSS_SGPIO_MODE_OFF;

        /* SFP RateSel = enabled    */
        conf.port_conf[12].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[12].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[12].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[12].mode[3] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[13].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[13].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[13].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[13].mode[3] = VTSS_SGPIO_MODE_ON;

        /* SFP TxDisable = enabled    */
        conf.port_conf[14].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[14].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[14].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[14].mode[3] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[15].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[15].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[15].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[15].mode[3] = VTSS_SGPIO_MODE_ON;

        for (port = 0; port < 12; port++) {
            if (port == 4 || (port > 6 && port < 9)) {
                continue;
            }

#if !defined(VTSS_FEATURE_10G)
            if (port > 8) {
                continue;
            }
#endif
            conf.port_conf[port].int_pol_high[0] = TRUE; // LOS is active high.
            conf.port_conf[port].int_pol_high[1] = TRUE; // TX_FAULT is active high.
        }

        conf.port_conf[4].int_pol_high[1] = TRUE; // SFP10 TX_FAULT

        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }

}

static vtss_rc srvlt_reset(void)
{
    return VTSS_RC_OK;
}

static vtss_rc srvlt_post_reset(void)
{
    return (vtss_phy_post_reset(PHY_INST, 0)); /* Internal PHY */
}

static void srvlt_pre_reset(void)
{
}

static vtss_rc srvlt_led_init(void)
{
    return VTSS_RC_OK;
}

vtss_rc srvlt_led_intensity(vtss_phy_led_intensity intensity)
{
    /* Both PCB111 and PCB110 uses the first PHY to control the PWM */
    return vtss_phy_led_intensity_set(PHY_INST, 0, intensity);
}

static BOOL port_activity(vtss_port_no_t port_no, vtss_port_status_t *status)
{

    vtss_port_status_t *old_status = &srvlt_old_port_info[port_no].status;
    BOOL link_activity = 0;

    if (old_status->link  != status->link  ||
        old_status->speed != status->speed ||
        old_status->fdx   != status->fdx   ||
        old_status->fiber != status->fiber) {
        link_activity = 1;
        *old_status = *status;
    }
    if (!link_activity && !srvlt_old_port_info[port_no].activity) {
        return 0; // No Activity
    }
    srvlt_old_port_info[port_no].activity = link_activity;
    return 1; // Activity
}

static vtss_rc srvlt_led_update(vtss_port_no_t port_no,
                              vtss_port_status_t *status,
                              vtss_port_counters_t *counters,
                              port_custom_conf_t *port_conf)
{
    u32                 chip_port = srvlt_port_table[port_no].map.chip_port;
    u32                 bit_green = 0, bit_yellow = 1;
    vtss_sgpio_conf_t   conf;
    vtss_sgpio_mode_t   mode_green = VTSS_SGPIO_MODE_OFF, mode_yellow = VTSS_SGPIO_MODE_OFF;
    vtss_rc             rc;
    BOOL                update_led = port_activity(port_no, status), tower_mode_changed;
    static BOOL         pre_collision_state[VTSS_PORTS], enable_old[VTSS_PORTS];
    static vtss_port_counter_t port_collision_cnt[VTSS_PORTS];
    BOOL                       collision = FALSE;
#if !defined(BOARD_HW_NO_LED_TOWER)
    static led_tower_mode_t s_led_tower_mode_old[VTSS_PORTS];
#endif /* !BOARD_HW_NO_LED_TOWER */


#if !defined(BOARD_HW_NO_LED_TOWER)
    // find out if tower mode has changed since the last time the port was served.
    tower_mode_changed = s_led_tower_mode_old[port_no] != s_led_tower_mode;
    s_led_tower_mode_old[port_no] = s_led_tower_mode;
#else
    tower_mode_changed = FALSE;
#endif /* !BOARD_HW_NO_LED_TOWER */

    /* Clear port count database whatever the current link status */
    if (!counters->rmon.tx_etherStatsCollisions) {
        port_collision_cnt[port_no] = 0;
    }

    if (s_led_tower_mode == LED_TOWER_MODE_DUPLEX_SPEED &&
        status->link &&
        !status->fdx &&
        port_collision_cnt[port_no] != counters->rmon.tx_etherStatsCollisions) {
        update_led = TRUE;
        collision = TRUE;
        pre_collision_state[port_no] = TRUE;
    } else if (!status->link) {
        port_collision_cnt[port_no] = counters->rmon.tx_etherStatsCollisions;
        pre_collision_state[port_no] = FALSE;
    }

    if (pre_collision_state[port_no] != collision) {
        pre_collision_state[port_no] = collision;
        update_led = TRUE;
    }

    if (s_led_tower_mode == LED_TOWER_MODE_LINK_STATUS &&
        enable_old[port_no] != port_conf->enable) {
        update_led = TRUE;
    }

    enable_old[port_no] = port_conf->enable;

    /* Return here if nothing has changed or in power saving mode */
    if ((!update_led
        && !tower_mode_changed) ||
        (!tower_mode_changed && s_led_tower_mode == LED_TOWER_MODE_POWER_SAVE
        )) {
        CUSTOM_N("Port %d: DON'T NEED update led(update_led = %s, tower_mode_changed = %s, s_led_tower_mode = %d)",
                port_no, update_led ? "TRUE" : "FALSE", tower_mode_changed ? "TRUE" : "FALSE", s_led_tower_mode);
      return VTSS_RC_OK;
    }

    CUSTOM_I("Port %d: update led", port_no);
    if ((rc = vtss_sgpio_conf_get(NULL, 0, 0, &conf)) != VTSS_RC_OK) {
        return rc;
    }

    if (chip_port < 2 && update_led) {
        if (status->fiber) {
            // Turn off RJ45 LED
            conf.port_conf[chip_port].mode[bit_green] = mode_green;
            conf.port_conf[chip_port].mode[bit_yellow] = mode_yellow;
            CUSTOM_D("Port %d: p%db%d: %d", port_no, chip_port, bit_green, conf.port_conf[chip_port].mode[bit_green]);
            CUSTOM_D("Port %d: p%db%d: %d", port_no, chip_port, bit_yellow, conf.port_conf[chip_port].mode[bit_yellow]);

            // Dual port in Serdes mode
            bit_green = 2;
            bit_yellow = 3;
        } else {
            // Turn off SFP
            conf.port_conf[chip_port].mode[2] = mode_green;
            conf.port_conf[chip_port].mode[3] = mode_yellow;
            CUSTOM_D("port %d: p%db%d: %d", port_no, chip_port, 2, conf.port_conf[chip_port].mode[2]);
            CUSTOM_D("port %d: p%db%d: %d", port_no, chip_port, 3, conf.port_conf[chip_port].mode[3]);
        }
    }

    switch (s_led_tower_mode) {
    case LED_TOWER_MODE_LINK_SPEED:
            if (status->link) {
                if (status->speed >= VTSS_SPEED_1G) {
                    /* Green: 1G link/activity */
                    mode_green = VTSS_SGPIO_MODE_0_ACTIVITY_INV;
                } else {
                    /* Yellow: 100/10 link/activity */
                    mode_yellow = VTSS_SGPIO_MODE_0_ACTIVITY_INV;
                }
            }
        break;
    case LED_TOWER_MODE_DUPLEX_SPEED:
            if (status->link) {
                if (status->fdx) {
                    /* Green: FDX */
                    mode_green = VTSS_SGPIO_MODE_0_ACTIVITY_INV;
                } else if (collision) {
                    /* Blink yellow: HDX with collision */
                    mode_yellow = VTSS_SGPIO_MODE_0;
                } else {
                    /* Yellow: HDX without collision */
                    mode_yellow = VTSS_SGPIO_MODE_ON;
                }
            }
        break;
        case LED_TOWER_MODE_LINK_STATUS:
          if (port_conf->enable == FALSE) {
                mode_yellow = VTSS_SGPIO_MODE_ON;
          } else if (status->link) {
                /* Green: link on */
                mode_green = VTSS_SGPIO_MODE_ON;
          }
        break;
    case LED_TOWER_MODE_POWER_SAVE:
        break;
    default:
        break;
    }

    // one to one mapping between chip_port and sgpio_port
    conf.port_conf[chip_port].mode[bit_green] = mode_green;
    conf.port_conf[chip_port].mode[bit_yellow] = mode_yellow;
    CUSTOM_D("Port %d: p%db%d: %d", port_no, chip_port, bit_green, conf.port_conf[chip_port].mode[bit_green]);
    CUSTOM_D("Port %d: p%db%d: %d", port_no, chip_port, bit_yellow, conf.port_conf[chip_port].mode[bit_yellow]);
    return vtss_sgpio_conf_set(NULL, 0, 0, &conf);
}

static void srvlt_port_conf(vtss_port_no_t port_no,
                            port_custom_conf_t *port_conf)
{
    vtss_sgpio_conf_t  conf;
    vtss_sgpio_mode_t  sgpio_mode = (port_conf->enable ? VTSS_SGPIO_MODE_ON : VTSS_SGPIO_MODE_OFF);
    u32 chip_port = srvlt_port_table[port_no].map.chip_port;


    (void)vtss_sgpio_conf_get(NULL, 0, 0, &conf);

    // Configure SFP TxDisable
    switch (chip_port) {
    case 0: conf.port_conf[14].mode[0] = sgpio_mode; break;
    case 1: conf.port_conf[14].mode[1] = sgpio_mode; break;
    case 2: conf.port_conf[14].mode[2] = sgpio_mode; break;
    case 3: conf.port_conf[14].mode[3] = sgpio_mode; break;
    case 5: conf.port_conf[15].mode[0] = sgpio_mode; break;
    case 6: conf.port_conf[15].mode[1] = sgpio_mode; break;
    case 9: conf.port_conf[15].mode[2] = sgpio_mode; break;
    case 10: conf.port_conf[15].mode[3] = sgpio_mode; break;
    default:
        return;
    }

    CUSTOM_D("Port %d: bmode_0: %d, bmode_1: %d, bit_count: %d", port_no, conf.bmode[0], conf.bmode[1], conf.bit_count);
    CUSTOM_D("Port %d: p6b2: %d", port_no, conf.port_conf[6].mode[2]);
    CUSTOM_D("Port %d: p6b3: %d", port_no, conf.port_conf[6].mode[3]);
    (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
}

typedef enum {
    SFP_DETECT,
    SFP_FAULT,
    SFP_LOS
} sfp_signal_t;

static BOOL get_sfp_status(vtss_port_no_t port_no, vtss_sgpio_port_data_t *data, sfp_signal_t sfp)
{
    u32 chip_port = srvlt_port_table[port_no].map.chip_port;
    u32 indx = (sfp == SFP_DETECT) ? 2 : (sfp == SFP_FAULT) ? 1 : 0;

    switch (chip_port) {
    case 0:  return (sfp == SFP_DETECT) ? !data[0].value[indx] : data[0].value[indx];
    case 1:  return (sfp == SFP_DETECT) ? !data[1].value[indx] : data[1].value[indx];
    case 2:  return (sfp == SFP_DETECT) ? !data[2].value[indx] : data[2].value[indx];
    case 3:  return (sfp == SFP_DETECT) ? !data[3].value[indx] : data[3].value[indx];
    case 5:  return (sfp == SFP_DETECT) ? !data[5].value[indx] : data[5].value[indx];
    case 6:  return (sfp == SFP_DETECT) ? !data[6].value[indx] : data[6].value[indx];
    case 9:  return (sfp == SFP_DETECT) ? !data[9].value[indx] : data[9].value[indx];
    case 10: return (sfp == SFP_DETECT) ? !data[4].value[indx] : (sfp == SFP_FAULT) ? data[4].value[indx] : data[10].value[indx];
    }
    return 0;
}

// Get module present / LOS / TxFault signals
static vtss_rc serval_sfp_status(port_custom_sfp_status_t *sfp_status)
{
    vtss_sgpio_port_data_t data[VTSS_SGPIO_PORTS];
    vtss_port_no_t         port_no;
    port_custom_entry_t    *entry;

    if (vtss_sgpio_read(NULL, 0, 0, data) != VTSS_RC_OK) {
        return VTSS_RC_ERROR;
    }
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        entry = &srvlt_port_table[port_no];
        if (entry->cap & PORT_CAP_SFP_DETECT || entry->cap & PORT_CAP_DUAL_SFP_DETECT) {
            sfp_status[port_no].present  = get_sfp_status(port_no, data, SFP_DETECT);
            sfp_status[port_no].tx_fault = get_sfp_status(port_no, data, SFP_FAULT);
            sfp_status[port_no].los      = get_sfp_status(port_no, data, SFP_LOS);
        } else {
            sfp_status[port_no].present  = 0;
            sfp_status[port_no].los      = 1;
            sfp_status[port_no].tx_fault = 1;
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc srvlt_sfp_mod_detect(BOOL *detect_status)
{
    vtss_port_no_t         port_no;
    vtss_sgpio_port_data_t data[VTSS_SGPIO_PORTS];

    if (vtss_sgpio_read(NULL, 0, 0, data) != VTSS_RC_OK) {
        return VTSS_RC_ERROR;
    }

    /* The status in 'data' is inverted i.e. '0' means detected */
    /* We return '1' when a module is detected */
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        detect_status[port_no] = get_sfp_status(port_no, data, SFP_DETECT);
    }
    CUSTOM_D("port:%d, status:%d\n", port_no, detect_status[port_no]);

    return VTSS_RC_OK;
}

/* Number of 1G/2.5G/10G ports */
#define PORT_CNT_1G  4
#if (VTSS_PORTS == 5)
/* Bringup, 4xCu + NPI */
#define PORT_CNT_2G5 0
#define PORT_CNT_10G 0
#elif (VTSS_PORTS == 7)
/* VSC7415/7435 */
#define PORT_CNT_2G5 2
#define PORT_CNT_10G 0
#elif (VTSS_PORTS == 9)
/* VSC7437 */
#define PORT_CNT_2G5 2
#define PORT_CNT_10G 2
#elif (VTSS_PORTS == 11)
/* VSC7436 */
#define PORT_CNT_2G5 4
#define PORT_CNT_10G 2
#else
#error Serval-T port count is not supported
#endif

BOOL vtss_board_probe_jr2(vtss_board_t *board, vtss_board_info_t *board_info)
{
    vtss_port_no_t      port_no;
    port_custom_entry_t *entry;

    memset(board, 0, sizeof(*board));

    srvlt_i2c_read   = board_info->i2c_read;
    srvlt_i2c_write  = board_info->i2c_write;

    board->type = VTSS_BOARD_SERVALT_NID_REF;
    board->name = "Serval-T";
    board->features = (VTSS_BOARD_FEATURE_LOS);
    board->custom_port_table = srvlt_port_table;
    board->init = srvlt_init;
    board->reset = srvlt_reset;
    board->pre_reset = srvlt_pre_reset;
    board->post_reset = srvlt_post_reset;
    board->led_init = srvlt_led_init;
    board->led_intensity = srvlt_led_intensity;
    board->led_update = srvlt_led_update;
    board->port_conf = srvlt_port_conf;
    board->sfp_i2c_read = srvlt_nid_i2c_read;
    board->sfp_i2c_write = srvlt_nid_i2c_write;
    board->sfp_mod_detect = srvlt_sfp_mod_detect;
    board->sfp_status = serval_sfp_status;
    board->board_fan_init          = srvlt_fan_init;
    board->board_temp_sensors_init = srvlt_temp_sensors_init;
    board->board_temp_sensors_get  = srvlt_temp_sensors_get;
    board->board_temp_sensors_cnt  = srvlt_temp_sensors_cnt;

    /* Fill out port mapping table */
    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        entry = &srvlt_port_table[port_no];
        if (port_no < PORT_CNT_1G) {
            if (port_no < 2) {
                /* Port 0-3: Copper ports, chip port 0-3 */
                entry->map.chip_port       = port_no;
                entry->map.miim_addr       = port_no;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
                entry->map.max_bw          = VTSS_BW_1G;
                entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
                entry->cap                 = PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | PORT_CAP_INT_PHY;
                entry->cap                &= ~(PORT_CAP_10M_HDX | PORT_CAP_100M_HDX); // BZ20946: half-duplex not supported
            } else {
                entry->map.chip_port       = port_no;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = VTSS_BW_1G;
                entry->mac_if              = VTSS_PORT_INTERFACE_SERDES;
                entry->cap                 = PORT_CAP_SFP_1G | PORT_CAP_SFP_SD_HIGH;
            }
#if PORT_CNT_2G5 > 0
        } else if (port_no < (PORT_CNT_1G + PORT_CNT_2G5)) {
            /* Port 4-5 or 4-7: 2.5G SFP, chip port 5-6 or 5-8 */
            entry->map.chip_port       = port_no + 1;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = VTSS_BW_2G5;
            entry->mac_if              = VTSS_PORT_INTERFACE_SERDES;
            entry->cap                 = PORT_CAP_SFP_2_5G | PORT_CAP_SFP_SD_HIGH;
#endif /* PORT_CNT_2G5 > 0 */
#if (PORT_CNT_10G > 0)
        } else if (port_no < PORT_CNT_1G + PORT_CNT_2G5 + PORT_CNT_10G) {
            /* Port 6-7 or 8-9: SFP+, chip port 9-10 */
            entry->map.chip_port       = port_no + 5 - PORT_CNT_2G5;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = VTSS_BW_DEFAULT; // 10G
            entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
            entry->cap                 = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH | PORT_CAP_SERDES_TX_INVERT);
#endif /* PORT_CNT_10G > 0 */
        } else {
            /* Port 6/8/10: NPI port, chip port 4 */
            entry->map.chip_port       = 4;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_1;
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = VTSS_BW_1G;
            entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
            entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
        }
    }

    return TRUE;
}
#endif /* VTSS_ARCH_SERVAL_T */

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
