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
#if defined(VTSS_ARCH_OCELOT)
#define VTSS_RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }
#if 0
#include <cyg/infra/diag.h>
#define PRINTD(args) { diag_printf("%s: ", __FUNCTION__); diag_printf args; diag_printf("\n"); }
#else
#define PRINTD(args)
#endif

/*lint -esym(459, ocelot_i2c_read) OK not to protect ocelot_i2c_read with semaphore in this file */
static vtss_i2c_read_t    ocelot_i2c_read;     /**< I2C read function */

/*lint -esym(459, ocelot_i2c_write) OK not to protect ocelot_i2c_write with semaphore in this file */
static vtss_i2c_write_t   ocelot_i2c_write;    /**< I2C write function */

static vtss_board_type_t this_board_type; // Keeping the PCB type.

typedef struct {
    vtss_port_counters_t cnt;
    vtss_port_status_t   status;
    u32                  activity;
} ocelot_port_info_t;

/*lint -esym(459, srvlt_port_table) */
static port_custom_entry_t ocelot_port_table[VTSS_PORT_ARRAY_SIZE];
static ocelot_port_info_t ocelot_old_port_info[VTSS_PORT_ARRAY_SIZE];

const int CHIP_NO = 0;
/************************************************************************
 * I2C                                                                  *
 ************************************************************************/

static vtss_rc ocelot_sfp_i2c_read(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, u8 cnt, BOOL word_access)
{
    if (ocelot_i2c_read != NULL) {
        PRINTD(("i2c_addr:0x%X, i2c_clk_sel:%d, cnd:%d, addr:%0xX\n", i2c_addr, i2c_clk_sel, cnt, addr));
        return ocelot_i2c_read(port_no, i2c_addr, addr, data, cnt);
    }
    return VTSS_RC_ERROR;
}

static vtss_rc ocelot_sfp_i2c_write(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, BOOL word_access)
{
    u8  i2c_data[3];
    if (ocelot_i2c_write != NULL) {
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        return ocelot_i2c_write(port_no, i2c_addr, i2c_data, 3);
    }
    return VTSS_RC_ERROR;
}

/************************************************************************
 * Temperature sensors                                                  *
 ************************************************************************/

static vtss_rc ocelot_temp_sensors_init(void) {
    return vtss_phy_chip_temp_init(PHY_INST, 0);
}

static vtss_rc ocelot_temp_sensors_get(vtss_port_no_t iport, i16 *temp) {
    return vtss_phy_chip_temp_get(PHY_INST, 0, temp);
}

static u8 ocelot_temp_sensors_cnt(void) {
    return 1;
}

/************************************************************************/
/* Called from port thread */
#define VTSS_GPIO__NOT_USED VTSS_GPIO_IN
static void ocelot_pcb120_init(void)
{
    const vtss_gpio_mode_t gpio_mode[22] = {
        /* GPIO_0  */ VTSS_GPIO_ALT_0,     // SGPIO
        /* GPIO_1  */ VTSS_GPIO_ALT_0,     // -
        /* GPIO_2  */ VTSS_GPIO_ALT_0,     // -
        /* GPIO_3  */ VTSS_GPIO_ALT_0,     // -
        /* GPIO_4  */ VTSS_GPIO_ALT_0,     // IRQ0_IN (VIPER interrupt)
        /* GPIO_5  */ VTSS_GPIO_ALT_0,     // IRQ1_IN (Dying gasp)
        /* GPIO_6  */ VTSS_GPIO_ALT_0,
        /* GPIO_7  */ VTSS_GPIO_ALT_0,
        /* GPIO_8  */ VTSS_GPIO_ALT_0,
        /* GPIO_9  */ VTSS_GPIO_ALT_0,
        /* GPIO_10 */ VTSS_GPIO_ALT_0,
        /* GPIO_11 */ VTSS_GPIO_ALT_0,
        /* GPIO_12 */ VTSS_GPIO__NOT_USED,
        /* GPIO_13 */ VTSS_GPIO__NOT_USED,
        /* GPIO_14 */ VTSS_GPIO_ALT_0,     // MIIM_1_MDC  (VIPER MIIM)
        /* GPIO_15 */ VTSS_GPIO_ALT_0,     // MIIM_1_MDIO
        /* GPIO_16 */ VTSS_GPIO_ALT_0,     // TWI_SDA (I2C for SFP and PoE)
        /* GPIO_17 */ VTSS_GPIO_ALT_0,     // TWI_SCL
        /* GPIO_18 */ VTSS_GPIO_ALT_0,     // PTP
        /* GPIO_19 */ VTSS_GPIO__NOT_USED, // DDR3 reset
        /* GPIO_20 */ VTSS_GPIO_ALT_2,     // TWI_SCL
        /* GPIO_21 */ VTSS_GPIO_ALT_2      // TWI_SCL
    };

    vtss_rc rc;
    vtss_sgpio_conf_t conf;
    u32               port, i;

    // (1) --- Configure GPIO mode. See 7514 datasheet table 161, page 205.
    //
    for (i=0; i<sizeof(gpio_mode)/sizeof(gpio_mode[0]); ++i) {
      if (i==19) continue;

      (void)vtss_gpio_mode_set(NULL, CHIP_NO, i, gpio_mode[i]);
    }

    // (2) --- Configure SGPIO
    //
    rc = vtss_sgpio_conf_get(NULL, 0, 0, &conf);
    if (rc) return;

    conf.bmode[0] = VTSS_SGPIO_BMODE_5;
    conf.bit_count = 2; // Two bit per port


    // Port 19:0 with 2 bit per port

    for (port = 0; port < 10+1; ++port) {
      /* if (port==7) continue; */
      conf.port_conf[port].enabled = 1;
      conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
      conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_ON;
      conf.port_conf[port].int_pol_high[0] = TRUE; /* LOS of signal is active high */
    }

    // --- SFP TX-enable
    port=11;
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_OFF;
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;

    // --- PD69200 PoE. Set High for PoE controller to work
    port=12; // PoE LED
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;

    port=13; // Alarm status LED
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;

    port=14; // DC in A status LED
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;

    port=15; // DC in B status LED
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;

    port=16;  // System status LED
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;

    port=17; // Not used
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_0;//VTSS_SGPIO_MODE_ON;
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;

    port=29; // PD69200_RSTn, xDisablePorts
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;  // Not in reset
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_ON; // PoE enable by default

    port=30; // Notused, ALARM
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_0;//VTSS_SGPIO_MODE_ON;
    conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;


    // Interrupt

    // I2C_Message_Ready
    port=4;

    // A_PUSHBUTTONn, SD_CD
    port=5;

    // Not used
    port=6;

    // Not used
    port=7;

    // SFP1 LOS
    port=8;

    // SFP1 MODDETn, TXFAULT
    port=9;
    conf.port_conf[port].int_pol_high[0] = TRUE; // SFP2_MODDETn
    conf.port_conf[port].int_pol_high[1] = TRUE; // SFP2_TXFAULT

    // SFP2 LOS
    port=10;

    // SFP2 MODDETn, TXFAULT
    port=11;
    conf.port_conf[port].int_pol_high[0] = TRUE; // SFP2_MODDETn
    conf.port_conf[port].int_pol_high[1] = TRUE; // SFP2_TXFAULT

    vtss_sgpio_conf_set(NULL, 0, 0, &conf);
}

/* Called from port thread */
static void ocelot_pcb123_init(void)
{
    vtss_sgpio_conf_t conf;
    u32               port, gpio_no;

    /* Configure GPIOs for MIIM/MDIO and I2C */
    for (gpio_no = 14; gpio_no <= 17; gpio_no++) {
        (void)vtss_gpio_mode_set(NULL, 0, gpio_no, VTSS_GPIO_ALT_0);
    }

    /* GPIO pins 0-3 are used for SGPIOs. */
    (void)vtss_gpio_mode_set(NULL, 0, 0, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)vtss_gpio_mode_set(NULL, 0, 1, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 2, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)vtss_gpio_mode_set(NULL, 0, 3, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / LD

    /* Setup SGPIO group 0 */
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collisions in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;

        /* Enable two bits per port */
        conf.bit_count = 2;

        /* Enable SLED ports 10:0 as port status LEDs */
        for (port = 0; port <= 10; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].int_pol_high[0] = TRUE; /* LOS of signal is active high */
        }

        /* Enable SLED port 11 as system status LED */
        conf.port_conf[11].enabled = 1;
        conf.port_conf[11].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[11].mode[1] = VTSS_SGPIO_MODE_OFF;

        /* Enable SGPIO output ports 23:12 as LED_SEL_x (dual-media), MUX_SELx (I2C),
           RS422_xOE (IEEE1588 RS422), SFP control signals and CardDetect from uSD slot */
        for (port = 12; port <= 23; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_OFF;
            conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_OFF;
        }

        /* MUX_SELx (I2C) is controlled by the BSP driver */
        conf.port_conf[13].mode[0] = VTSS_SGPIO_MODE_NO_CHANGE;
        conf.port_conf[13].mode[1] = VTSS_SGPIO_MODE_NO_CHANGE;
        conf.port_conf[14].mode[0] = VTSS_SGPIO_MODE_NO_CHANGE;

        /* SFP RateSel = enabled */
        for (port = 16; port <= 19; port++) {
            conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_ON;
        }

        /* SFP TxDisable = enabled */
        for (port = 20; port <= 23; port++) {
            conf.port_conf[port].mode[0] = VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] = VTSS_SGPIO_MODE_ON;
        }

        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }
}

static vtss_rc ocelot_reset(void)
{
    VTSS_RC(vtss_phy_pre_reset(PHY_INST, 3)); // Viper PHY
    if (this_board_type == VTSS_BOARD_OCELOT_REF) {
        VTSS_RC(vtss_phy_pre_reset(PHY_INST, 7)); // Nano PHY
    }

    return VTSS_RC_OK;
}

static vtss_rc ocelot_post_reset(void)
{
    VTSS_RC(vtss_phy_post_reset(PHY_INST, 3)); // Viper PHY
    if (this_board_type == VTSS_BOARD_OCELOT_REF) {
        VTSS_RC(vtss_phy_post_reset(PHY_INST, 7)); // Nano PHY
    }

    return VTSS_RC_OK;
}

static void ocelot_pre_reset(void)
{

}

static vtss_rc ocelot_led_init(void)
{
    return VTSS_RC_OK;
}

#define ACTIVITY_LINK 0x01
#define ACTIVITY_CNT  0x02

static u32 port_activity(vtss_port_no_t port_no,
                         vtss_port_status_t *status,
                         vtss_port_counters_t *counters)
{
    ocelot_port_info_t *old = &ocelot_old_port_info[port_no];
    u32 activity = 0;

    /* Counter activity detected after a few frames */
    if ((counters->rmon.rx_etherStatsPkts > (old->cnt.rmon.rx_etherStatsPkts + 2)) ||
        (counters->rmon.tx_etherStatsPkts > (old->cnt.rmon.tx_etherStatsPkts + 2))) {
        activity = ACTIVITY_CNT;
    }
    old->cnt = *counters;

    /* Link activity */
    if (old->status.link != status->link ||
        old->status.speed != status->speed ||
        old->status.fdx != status->fdx ||
        old->status.fiber != status->fiber) {
        activity |= ACTIVITY_LINK;
        old->status = *status;
    }

    if (activity == old->activity) {
        /* No activity change */
        return 0;
    }
    old->activity = activity;
    return (activity | ACTIVITY_LINK);
}

static vtss_rc ocelot_led_update(vtss_port_no_t port_no,
                                 vtss_port_status_t *status,
                                 vtss_port_counters_t *counters,
                                 port_custom_conf_t *port_conf)
{
    u32               chip_port = ocelot_port_table[port_no].map.chip_port;
    vtss_sgpio_conf_t conf;
    vtss_rc           rc;
    vtss_sgpio_mode_t mode_green, mode_red;
    u32               activity;

    if (port_no == (VTSS_PORTS - 1)) {
        /* Skip NPI port */
        return VTSS_RC_OK;
    }

    activity = port_activity(port_no, status, counters);
    if (!activity) {
        return VTSS_RC_OK;
    }

    if ((rc = vtss_sgpio_conf_get(NULL, 0, 0, &conf)) != VTSS_RC_OK) {
        return rc;
    }

    /* Dual-media LED selector */
    if (chip_port < 2) {
        conf.port_conf[12].mode[chip_port] = (status->fiber ? VTSS_SGPIO_MODE_OFF : VTSS_SGPIO_MODE_ON);
    }

    if (status->link) {
        mode_green = ((activity & ACTIVITY_CNT) ? VTSS_SGPIO_MODE_0_ACTIVITY : VTSS_SGPIO_MODE_OFF);
        if (status->speed >= VTSS_SPEED_1G) {
            /* Green activity */
            mode_red = VTSS_SGPIO_MODE_ON;
        } else {
            /* Yellow activity */
            mode_red = mode_green;
        }
    } else {
        /* Both LEDs off */
        mode_red = VTSS_SGPIO_MODE_ON;
        mode_green = VTSS_SGPIO_MODE_ON;
    }
    conf.port_conf[chip_port].mode[0] = mode_red;
    conf.port_conf[chip_port].mode[1] = mode_green;

    return vtss_sgpio_conf_set(NULL, 0, 0, &conf);
}

static void ocelot_port_conf(vtss_port_no_t port_no,
                             port_custom_conf_t *port_conf)
{
    vtss_sgpio_conf_t conf;
    if (this_board_type == VTSS_BOARD_OCELOT_REF) {
        vtss_rc rc;
        vtss_sgpio_mode_t sgpio_mode;

        // --- Only for SFPs which is port port 8,9
        if (!(port_no==8 || port_no==9)) return;

        rc = vtss_sgpio_conf_get(NULL, 0, 0, &conf);
        if (rc) {
            // --- Should not happen
            return;
        }

        sgpio_mode = (port_conf->enable ? VTSS_SGPIO_MODE_ON : VTSS_SGPIO_MODE_OFF);

        /* Configure SFP TxDisable */
        switch (port_no) {
        case 8: conf.port_conf[11].mode[0] = sgpio_mode; break;
        case 9: conf.port_conf[11].mode[1] = sgpio_mode; break;
        }

        rc = vtss_sgpio_conf_set(NULL, 0, 0, &conf);
        if (rc) {
            // --- Should not happen
            return;
        }
    } else {
        vtss_sgpio_mode_t sgpio_mode = (port_conf->enable ? VTSS_SGPIO_MODE_ON : VTSS_SGPIO_MODE_OFF);

        (void)vtss_sgpio_conf_get(NULL, 0, 0, &conf);
        /* Configure SFP TxDisable */
        switch (port_no) {
        case 2: conf.port_conf[20].mode[0] = sgpio_mode; break;
        case 3: conf.port_conf[20].mode[1] = sgpio_mode; break;
        case 4: conf.port_conf[21].mode[0] = sgpio_mode; break;
        case 5: conf.port_conf[21].mode[1] = sgpio_mode; break;
        case 6: conf.port_conf[22].mode[0] = sgpio_mode; break;
        case 7: conf.port_conf[22].mode[1] = sgpio_mode; break;
        case 8: conf.port_conf[23].mode[0] = sgpio_mode; break;
        case 9: conf.port_conf[23].mode[1] = sgpio_mode; break;
        default:
            return;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }
}

typedef enum {
    SFP_DETECT,
    SFP_FAULT,
    SFP_LOS
} sfp_signal_t;

static BOOL get_sfp_status(vtss_port_no_t port_no, vtss_sgpio_port_data_t *data, sfp_signal_t sfp)
{
    if (this_board_type == VTSS_BOARD_OCELOT_REF) {
        switch (sfp) {
        case SFP_DETECT: return  port_no==8  ? !data[ 9].value[0] : !data[11].value[0];
        case SFP_FAULT:  return  port_no==8  ?  data[ 9].value[1] :  data[11].value[1];
        case SFP_LOS:    return  port_no==8  ?  data[ 8].value[0] :  data[10].value[0];
        }

        // --- We are not supposed to get here
        return FALSE;
    } else {
        switch (port_no) {
        case 2: return (sfp == SFP_DETECT) ? !data[ 0].value[1] : (sfp == SFP_FAULT) ? data[ 2].value[0] : data[ 0].value[0];
        case 3: return (sfp == SFP_DETECT) ? !data[ 1].value[1] : (sfp == SFP_FAULT) ? data[ 2].value[1] : data[ 1].value[0];
        case 4: return (sfp == SFP_DETECT) ? !data[ 4].value[1] : (sfp == SFP_FAULT) ? data[ 3].value[0] : data[ 4].value[0];
        case 5: return (sfp == SFP_DETECT) ? !data[ 6].value[1] : (sfp == SFP_FAULT) ? data[ 3].value[1] : data[ 6].value[0];
        case 6: return (sfp == SFP_DETECT) ? !data[ 9].value[1] : (sfp == SFP_FAULT) ? data[ 5].value[1] : data[ 9].value[0];
        case 7: return (sfp == SFP_DETECT) ? !data[10].value[1] : (sfp == SFP_FAULT) ? data[11].value[0] : data[10].value[0];
        case 8: return (sfp == SFP_DETECT) ? !data[ 7].value[1] : (sfp == SFP_FAULT) ? data[11].value[1] : data[ 7].value[0];
        case 9: return (sfp == SFP_DETECT) ? !data[ 8].value[1] : (sfp == SFP_FAULT) ? data[12].value[0] : data[ 8].value[0];
        }
        return FALSE;
    }
}

/* Get module present / LOS / TxFault signals */
static vtss_rc ocelot_sfp_status(port_custom_sfp_status_t *sfp_status)
{
    vtss_sgpio_port_data_t data[VTSS_SGPIO_PORTS];
    vtss_port_no_t         port_no;
    port_custom_entry_t    *entry;

    VTSS_RC(vtss_sgpio_read(NULL, 0, 0, data));
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        entry = &ocelot_port_table[port_no];
        if ((entry->cap & PORT_CAP_SFP_DETECT) || (entry->cap & PORT_CAP_DUAL_SFP_DETECT)) {
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

static vtss_rc ocelot_sfp_mod_detect(BOOL *detect_status)
{
    vtss_port_no_t         port_no;
    vtss_sgpio_port_data_t data[VTSS_SGPIO_PORTS];

    if (vtss_sgpio_read(NULL, 0, 0, data) != VTSS_RC_OK) {
        return VTSS_RC_ERROR;
    }

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        detect_status[port_no] = get_sfp_status(port_no, data, SFP_DETECT);
    }
    PRINTD(("port:%d, status:%d\n", port_no, detect_status[port_no]));

    return VTSS_RC_OK;
}

// The port map for PCB 120 (PoE)
static void port_map_pcb120(void) {
    vtss_port_no_t      port_no;
    port_custom_entry_t *entry;
    /* Local mapping table */
    struct {
        i32 chip_port;
        u8  miim_addr;
        i32 poe_port;
    } map[] = {
        {5, 3, 6},
        {9, 2, 1},
        {6, 1, 7},
        {4, 0, 0},
        {3, 3, 4},
        {2, 2, 3},
        {1, 1, 5},
        {0, 0, 2},
        {8, 0, 0},
        {10, 0, 0},
        {-1, 0, 0}
    };

    /* Fill out port mapping table */
    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        entry = &ocelot_port_table[port_no];
        entry->map.chip_port = map[port_no].chip_port;
        entry->map.miim_addr = map[port_no].miim_addr;
#ifdef VTSS_SW_OPTION_POE
        entry->poe_port = map[port_no].poe_port;
#endif
        if (port_no < 8) {
            entry->mac_if = VTSS_PORT_INTERFACE_SGMII;
#ifdef VTSS_SW_OPTION_POE
            entry->poe_support = TRUE;
#endif
            if (port_no < 4) {
                // External PHY
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_1;
                entry->cap = PORT_CAP_TRI_SPEED_COPPER;
            } else {
                // Internal PHY
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
                entry->cap = (PORT_CAP_TRI_SPEED_COPPER | PORT_CAP_INT_PHY);
            }
        } else {
            entry->mac_if = VTSS_PORT_INTERFACE_SERDES;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->cap = (PORT_CAP_SFP_2_5G | PORT_CAP_SFP_SD_HIGH);
        }
    }
}

// The port map for PCB 123 (Non PoE)
static void port_map_pcb123(void) {
    vtss_port_no_t      port_no;
    port_custom_entry_t *entry;

    /* Fill out port mapping table */
    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        entry = &ocelot_port_table[port_no];
        if (port_no < 2) {
            /* Copper ports without dual-media support */
            entry->map.chip_port = port_no + 2;
            entry->map.miim_addr = port_no + 2;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
            entry->mac_if = VTSS_PORT_INTERFACE_SGMII;
            entry->cap = PORT_CAP_TRI_SPEED_COPPER | PORT_CAP_INT_PHY;
        } else if (port_no < 4) {
            /* Dual-media ports */
            entry->map.chip_port = port_no - 2;
            entry->map.miim_addr = port_no - 2;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
            entry->mac_if = VTSS_PORT_INTERFACE_SGMII;
            entry->cap = PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | PORT_CAP_INT_PHY;
        } else {
            /* SFP ports */
            i32 port_map[] = {4, 6, 9, 5, 7, 8};
            entry->map.chip_port = port_map[port_no - 4];
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->mac_if = VTSS_PORT_INTERFACE_SERDES;
            if (port_no < 8) {
                entry->cap = PORT_CAP_SFP_1G | PORT_CAP_SFP_SD_HIGH;
            } else {
                entry->cap = PORT_CAP_SFP_2_5G | PORT_CAP_SFP_SD_HIGH;
            }
        }
    }
}

BOOL vtss_board_probe_ocelot(vtss_board_t *board, vtss_board_info_t *board_info)
{
    memset(board, 0, sizeof(*board));

    /* Enable GPIO_14 and GPIO_15 as MIIM controllers for being able to access the PHY */
    (void)vtss_gpio_mode_set(NULL, 0, 14, VTSS_GPIO_ALT_0);
    (void)vtss_gpio_mode_set(NULL, 0, 15, VTSS_GPIO_ALT_0);

    // At this point the PHY access function is not ready, so we have to do direct MIIM access
    u16 dummy;
    if (vtss_miim_read(NULL, 0, VTSS_MIIM_CONTROLLER_1, 0, 0, &dummy) == VTSS_RC_OK) {
        board->type = VTSS_BOARD_OCELOT_REF;
        board->name = "Ocelot PoE";
        port_map_pcb120();
        board_info->port_count--;
        board->init = ocelot_pcb120_init;
        board->features = (VTSS_BOARD_FEATURE_LOS | VTSS_BOARD_FEATURE_POE);
    } else {
        board->type = VTSS_BOARD_OCELOT_PCB123_REF;
        board->name = "Ocelot";
        port_map_pcb123();
        board->init = ocelot_pcb123_init;
        board->features = (VTSS_BOARD_FEATURE_LOS);
    }
    this_board_type = board->type;
    ocelot_i2c_read   = board_info->i2c_read;
    ocelot_i2c_write  = board_info->i2c_write;
    board->custom_port_table = ocelot_port_table;
    board->reset = ocelot_reset;
    board->pre_reset = ocelot_pre_reset;
    board->post_reset = ocelot_post_reset;
    board->led_init = ocelot_led_init;
    board->led_update = ocelot_led_update;
    board->port_conf = ocelot_port_conf;
    board->sfp_i2c_read = ocelot_sfp_i2c_read;
    board->sfp_i2c_write = ocelot_sfp_i2c_write;
    board->sfp_mod_detect = ocelot_sfp_mod_detect;
    board->sfp_status = ocelot_sfp_status;
    board->board_temp_sensors_init = ocelot_temp_sensors_init;
    board->board_temp_sensors_get = ocelot_temp_sensors_get;
    board->board_temp_sensors_cnt = ocelot_temp_sensors_cnt;

    return TRUE;
}
#endif /* VTSS_ARCH_OCELOT */

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
