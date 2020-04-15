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

#define MESA_GPIO__NOT_USED MESA_GPIO_IN

typedef enum {
    BOARD_TYPE_OCELOT_PCB120,
    BOARD_TYPE_OCELOT_PCB123,
} board_type_t;

typedef enum {
    SFP_DETECT,
    SFP_FAULT,
    SFP_LOS
} sfp_signal_t;

typedef struct {
    mesa_rc (*board_init)(meba_inst_t inst);
    void (*init_porttable)(meba_inst_t inst);
} board_func_t;

typedef struct {
    meba_port_entry_t    map;
    int32_t              board_port;
    int32_t              board_port_dual;
    mesa_port_counters_t cnt;
    mesa_port_status_t   status;
    uint32_t             activity;
    mesa_bool_t          ts_phy;
} ocelot_port_info_t;

typedef struct meba_board_state {
    board_type_t          type;
    int                   port_cnt;
    ocelot_port_info_t    *port;
    uint32_t              *sgpio_port;
    const board_func_t    *func;
} meba_board_state_t;

static const meba_aux_rawio_t rawio = {
    .gcb = 0x07,
    .miim = {
        .status = 0x27+0,
        .cmd    = 0x27+2,
        .data   = 0x27+3,
        .cfg    = 0x27+4,
    },
    .gpio = {
        .alt_0  = 0x15,
    }
};

static const meba_ptp_rs422_conf_t pcb123_rs422_conf = {
    .gpio_rs422_1588_mstoen = (15<<8)+1,
    .gpio_rs422_1588_slvoen = (15<<8)+0,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 0,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_0,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3
};

static const meba_ptp_rs422_conf_t other_rs422_conf = {
    .gpio_rs422_1588_mstoen = -1,
    .gpio_rs422_1588_slvoen = -1,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 0,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_0,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3
};

#define PORT_2_BOARD_PORT(board, p) (board->port[p].board_port)
#define DUAL_PORT_2_BOARD_PORT(board, p) (board->port[p].board_port_dual)

/* --------------------------- Board specific ------------------------------- */


static mesa_rc pcb120_init_board(meba_inst_t inst)
{
    mesa_rc rc;
    const mesa_gpio_mode_t gpio_mode[22] = {
        /* GPIO_0  */ MESA_GPIO_ALT_0,     // SGPIO
        /* GPIO_1  */ MESA_GPIO_ALT_0,     // -
        /* GPIO_2  */ MESA_GPIO_ALT_0,     // -
        /* GPIO_3  */ MESA_GPIO_ALT_0,     // -
        /* GPIO_4  */ MESA_GPIO_ALT_0,     // IRQ0_IN (VIPER interrupt)
        /* GPIO_5  */ MESA_GPIO_ALT_0,     // IRQ1_IN (Dying gasp)
        /* GPIO_6  */ MESA_GPIO_ALT_0,
        /* GPIO_7  */ MESA_GPIO_ALT_0,
        /* GPIO_8  */ MESA_GPIO_ALT_0,
        /* GPIO_9  */ MESA_GPIO_ALT_0,
        /* GPIO_10 */ MESA_GPIO_ALT_0,
        /* GPIO_11 */ MESA_GPIO_ALT_0,
        /* GPIO_12 */ MESA_GPIO__NOT_USED,
        /* GPIO_13 */ MESA_GPIO__NOT_USED,
        /* GPIO_14 */ MESA_GPIO_ALT_0,     // MIIM_1_MDC  (VIPER MIIM)
        /* GPIO_15 */ MESA_GPIO_ALT_0,     // MIIM_1_MDIO
        /* GPIO_16 */ MESA_GPIO_ALT_0,     // TWI_SDA (I2C for SFP and PoE)
        /* GPIO_17 */ MESA_GPIO_ALT_0,     // TWI_SCL
        /* GPIO_18 */ MESA_GPIO_ALT_0,     // PTP
        /* GPIO_19 */ MESA_GPIO__NOT_USED, // DDR3 reset
        /* GPIO_20 */ MESA_GPIO_ALT_2,     // TWI_SCL
        /* GPIO_21 */ MESA_GPIO_ALT_2      // TWI_SCL
    };

    mesa_sgpio_conf_t conf;
    uint32_t port, i;

    // (1) --- Configure GPIO mode. See 7514 datasheet table 161, page 205.
    //
    for (i=0; i<sizeof(gpio_mode)/sizeof(gpio_mode[0]); ++i) {
      if (i==19) continue;

      (void)mesa_gpio_mode_set(NULL, 0, i, gpio_mode[i]);
    }

    // (2) --- Configure SGPIO
    //
    if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {

        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2; // Two bit per port


        // Port 19:0 with 2 bit per port

        for (port = 0; port < 10+1; ++port) {
            /* if (port==7) continue; */
            conf.port_conf[port].enabled = true;
            conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_ON;
            conf.port_conf[port].int_pol_high[0] = true; /* LOS of signal is active high */
        }

        // --- SFP TX-enable
        port=11;
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_OFF;
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;

        // --- PD69200 PoE. Set High for PoE controller to work
        port=12; // PoE LED
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;

        port=13; // Alarm status LED
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;

        port=14; // DC in A status LED
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;

        port=15; // DC in B status LED
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;

        port=16;  // System status LED
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;

        port=17; // Not used
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_0;//MESA_SGPIO_MODE_ON;
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;

        port=29; // PD69200_RSTn, xDisablePorts
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;  // Not in reset
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_ON; // PoE enable by default

        port=30; // Notused, ALARM
        conf.port_conf[port].enabled = true;
        conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_0;//MESA_SGPIO_MODE_ON;
        conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;


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
        conf.port_conf[port].int_pol_high[0] = true; // SFP2_MODDETn
        conf.port_conf[port].int_pol_high[1] = true; // SFP2_TXFAULT

        // SFP2 LOS
        port=10;

        // SFP2 MODDETn, TXFAULT
        port=11;
        conf.port_conf[port].int_pol_high[0] = true; // SFP2_MODDETn
        conf.port_conf[port].int_pol_high[1] = true; // SFP2_TXFAULT

        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc;
}

static mesa_rc pcb123_init_board(meba_inst_t inst)
{
    mesa_rc rc;
    mesa_sgpio_conf_t conf;
    uint32_t port, gpio_no;

    /* Configure GPIOs for MIIM/MDIO and I2C */
    for (gpio_no = 14; gpio_no <= 17; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    /* GPIO pins 0-3 are used for SGPIOs. */
    (void)mesa_gpio_mode_set(NULL, 0, 0, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)mesa_gpio_mode_set(NULL, 0, 1, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 2, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)mesa_gpio_mode_set(NULL, 0, 3, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / LD

    /* Setup SGPIO group 0 */
    if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collisions in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;

        /* Enable two bits per port */
        conf.bit_count = 2;

        /* Enable SLED ports 10:0 as port status LEDs */
        for (port = 0; port <= 10; port++) {
            conf.port_conf[port].enabled = true;
            conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_ON;
            conf.port_conf[port].int_pol_high[0] = true; /* LOS of signal is active high */
        }

        /* Enable SLED port 11 as system status LED */
        conf.port_conf[11].enabled = true;
        conf.port_conf[11].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[11].mode[1] = MESA_SGPIO_MODE_OFF;

        /* Enable SGPIO output ports 23:12 as LED_SEL_x (dual-media), MUX_SELx (I2C),
           RS422_xOE (IEEE1588 RS422), SFP control signals and CardDetect from uSD slot */
        for (port = 12; port <= 23; port++) {
            conf.port_conf[port].enabled = true;
            conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_OFF;
            conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_OFF;
        }

        /* MUX_SELx (I2C) is controlled by the BSP driver */
        conf.port_conf[13].mode[0] = MESA_SGPIO_MODE_NO_CHANGE;
        conf.port_conf[13].mode[1] = MESA_SGPIO_MODE_NO_CHANGE;
        conf.port_conf[14].mode[0] = MESA_SGPIO_MODE_NO_CHANGE;

        /* SFP RateSel = enabled */
        for (port = 16; port <= 19; port++) {
            conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_ON;
        }

        /* SFP TxDisable = enabled */
        for (port = 20; port <= 23; port++) {
            conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_ON;
        }

        (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc;
}
// When the dual media ports are in Serdes mode the sd_enable, sd_high and sd_internal should be set.
// MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER does not include those capabilities, therefore they are added specifically.
#define CAP_SFP_SD_HIGH (MEBA_PORT_CAP_SD_ENABLE | MEBA_PORT_CAP_SD_HIGH | MEBA_PORT_CAP_SD_INTERNAL | MEBA_PORT_CAP_SFP_DETECT)
static void pcb120_init_porttable(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t      port_no;
    /* Local mapping table */
    typedef struct {
        int32_t                board_port;
        int32_t                chip_port;
        mesa_miim_controller_t miim_controller;
        uint8_t                miim_addr;
        mesa_port_interface_t  mac_if;
        meba_port_cap_t        cap;
        mesa_bool_t            poe_support;
        int32_t                poe_port;
    } port_map_t;
    typedef struct {
        port_map_t map[10];
    } map_wrap_t;
    map_wrap_t map_wrap;

    if (inst->props.target == MESA_TARGET_7513) {
        return;
    } else if (inst->props.target == MESA_TARGET_7514) {
        if (inst->props.mux_mode == MESA_PORT_MUX_MODE_4) {
            map_wrap = (map_wrap_t) {
                {
                    {0, 5, MESA_MIIM_CONTROLLER_1, 3, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, true, 6},
                    {1, 9, MESA_MIIM_CONTROLLER_1, 2, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, true, 1},
                    {2, 6, MESA_MIIM_CONTROLLER_1, 1, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, true, 7},
                    {3, 4, MESA_MIIM_CONTROLLER_1, 0, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER, true, 0},
                    {4, 3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY), true, 4},
                    {5, 2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY), true, 3},
                    {6, 1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY), true, 5},
                    {7, 0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY), true, 2},
                    {8, 8, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH), false, 0},
                    {9, 10, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH), false, 0}
                }
            };
        } else {
            T_E(inst, "This board does not support mux_mode %d", inst->props.mux_mode);
            return;
        }
    }

    /* Fill out port mapping table */
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        board->port[port_no].board_port = map_wrap.map[port_no].board_port;
        board->port[port_no].board_port_dual = -1;
        meba_port_entry_t  *entry = &board->port[port_no].map;
        entry->map.chip_port = map_wrap.map[port_no].chip_port;
        entry->map.miim_controller = map_wrap.map[port_no].miim_controller;
        entry->map.miim_addr = map_wrap.map[port_no].miim_addr;
        entry->mac_if = map_wrap.map[port_no].mac_if;
        entry->cap = map_wrap.map[port_no].cap;
        entry->poe_support = map_wrap.map[port_no].poe_support;
        entry->poe_chip_port = map_wrap.map[port_no].poe_port;
    }

    /* Fill out board to sgpio port mapping table */
    uint32_t sgpio_port_map[10] = {5, 9, 6, 4, 3, 2, 1, 0, 8, 10};
    memcpy(board->sgpio_port, sgpio_port_map, sizeof(sgpio_port_map));
}

static void pcb123_init_porttable(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t      port_no;
    /* Local mapping table */
    typedef struct {
        int32_t                board_port;
        int32_t                board_port_dual;
        int32_t                chip_port;
        mesa_miim_controller_t miim_controller;
        uint8_t                miim_addr;
        mesa_port_interface_t  mac_if;
        meba_port_cap_t        cap;
    } port_map_t;
    typedef struct {
        port_map_t map[11];
    } map_wrap_t;
    map_wrap_t map_wrap;

    /* Note that the mesa_phy_pre_reset() and mesa_phy_post_reset() functions
     * rely on the base port of a PHY, so if a PHY is used in the following port
     * maps, then the map must always make use of the PHY's base port.
     * Also, the mapping from API port to chip port in 'meba_reset()' must also be
     * updated according to the selected port map.
     */

    if (inst->props.target == MESA_TARGET_7513) {
        switch (inst->props.mux_mode) {
        case MESA_PORT_MUX_MODE_0:
            map_wrap = (map_wrap_t) {
                {
                    {0, 6, 2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {1, 7, 3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {2, 4, 0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {3, 5, 1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {8, -1, 4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {9, -1, 10, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {12, -1, 5, MESA_MIIM_CONTROLLER_1, 28, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0}
                }
            };
            break;
        case MESA_PORT_MUX_MODE_1:
            map_wrap = (map_wrap_t) {
                {
                    {0, 6, 2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {1, 7, 3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {2, 4, 0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {3, 5, 1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {8, -1, 4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {9, -1, 5, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0}
                }
            };
            break;
        case MESA_PORT_MUX_MODE_2:
        case MESA_PORT_MUX_MODE_3:
        case MESA_PORT_MUX_MODE_4:
        case MESA_PORT_MUX_MODE_5:
            T_E(inst, "This board does not support mux_mode %d", inst->props.mux_mode);
            return;
        default:
            T_E(inst, "Missing port mux_mode for board port table configuration");
            return;
        }
    } else if (inst->props.target == MESA_TARGET_7514) {
        switch (inst->props.mux_mode) {
        case MESA_PORT_MUX_MODE_0:
            map_wrap = (map_wrap_t) {
                {
                    {0, 6, 2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {1, 7, 3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {2, 4, 0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {3, 5, 1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {8, -1, 4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {9, -1, 10, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {10, -1, 7, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {11, -1, 8, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {12, -1, 5, MESA_MIIM_CONTROLLER_1, 28, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0}
                }
            };
            break;
        case MESA_PORT_MUX_MODE_1:
            map_wrap = (map_wrap_t) {
                {
                    {0, 6, 2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {1, 7, 3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {2, 4, 0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {3, 5, 1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {8, -1, 4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {9, -1, 5, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {10, -1, 7, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {11, -1, 8, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0}
                }
            };
            break;
        case MESA_PORT_MUX_MODE_2:
        case MESA_PORT_MUX_MODE_3:
            T_E(inst, "This board does not support mux_mode %d", inst->props.mux_mode);
            return;
        case MESA_PORT_MUX_MODE_4:
            map_wrap = (map_wrap_t) {
                {
                    {0, -1, 2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY)},
                    {1, -1, 3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY)},
                    {2, 4, 0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {3, 5, 1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {6, -1, 4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {7, -1, 6, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {8, -1, 9, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {9, -1, 10, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {10, -1, 7, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {11, -1, 8, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {12, -1, 5, MESA_MIIM_CONTROLLER_1, 28, MESA_PORT_INTERFACE_SGMII, MEBA_PORT_CAP_TRI_SPEED_COPPER}
                }
            };
            break;
        case MESA_PORT_MUX_MODE_5:
            map_wrap = (map_wrap_t) {
                {
                    {0, -1, 2, MESA_MIIM_CONTROLLER_0, 2, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY)},
                    {1, -1, 3, MESA_MIIM_CONTROLLER_0, 3, MESA_PORT_INTERFACE_SGMII, (MEBA_PORT_CAP_TRI_SPEED_COPPER | MEBA_PORT_CAP_INT_PHY)},
                    {2, 4, 0, MESA_MIIM_CONTROLLER_0, 0, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {3, 5, 1, MESA_MIIM_CONTROLLER_0, 1, MESA_PORT_INTERFACE_SGMII, (CAP_SFP_SD_HIGH | MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY)},
                    {6, -1, 4, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {7, -1, 6, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {8, -1, 9, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {9, -1, 5, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {10, -1, 7, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {11, -1, 8, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_SERDES, (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH)},
                    {-1, -1, -1, MESA_MIIM_CONTROLLER_NONE, 0, MESA_PORT_INTERFACE_NO_CONNECTION, 0}
                }
            };
            break;
        default:
            T_E(inst, "Missing port mux_mode for board port table configuration");
            return;
        }
    }

    /* Fill out port mapping table */
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        board->port[port_no].board_port = map_wrap.map[port_no].board_port;
        board->port[port_no].board_port_dual = map_wrap.map[port_no].board_port_dual;
        meba_port_entry_t  *entry = &board->port[port_no].map;
        entry->map.chip_port = map_wrap.map[port_no].chip_port;
        entry->map.miim_addr = map_wrap.map[port_no].miim_addr;
        entry->map.miim_controller = map_wrap.map[port_no].miim_controller;
        entry->mac_if = map_wrap.map[port_no].mac_if;
        entry->cap = map_wrap.map[port_no].cap;
    }

    /* Fill out board to sgpio port mapping table */
    uint32_t sgpio_port_map[12] = {2, 3, 0, 1, 0, 1, 4, 6, 9, 10, 7, 8};
    memcpy(board->sgpio_port, sgpio_port_map, sizeof(sgpio_port_map));
}

static const board_func_t board_funcs[] = {
    [BOARD_TYPE_OCELOT_PCB120] = {
        .board_init      = pcb120_init_board,
        .init_porttable  = pcb120_init_porttable,
    },
    [BOARD_TYPE_OCELOT_PCB123] = {
        .board_init      = pcb123_init_board,
        .init_porttable  = pcb123_init_porttable,
    },
};

#define ACTIVITY_LINK 0x01
#define ACTIVITY_CNT  0x02

static uint32_t port_activity(meba_inst_t inst,
                              mesa_port_no_t port_no,
                              const mesa_port_status_t *status,
                              const mesa_port_counters_t *counters)
{
    meba_board_state_t *board = INST2BOARD(inst);
    ocelot_port_info_t *old = &board->port[port_no];
    uint32_t activity = 0;

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

static mesa_bool_t get_sfp_status(meba_inst_t inst,
                                  mesa_port_no_t port_no,
                                  mesa_sgpio_port_data_t *data,
                                  sfp_signal_t sfp)
{
    meba_board_state_t *board = INST2BOARD(inst);
    int32_t            board_port = PORT_2_BOARD_PORT(board, port_no);

    // If the port is a dual-media one, then the board port no is different
    if (has_cap(board->port[port_no].map.cap, (MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER))) {
        board_port = DUAL_PORT_2_BOARD_PORT(board, port_no);
    }

    if (board->type == BOARD_TYPE_OCELOT_PCB120) {
        switch (board_port) {
        case 8:
            return (sfp == SFP_DETECT) ? !data[ 9].value[0] : (sfp == SFP_FAULT) ? data[ 9].value[1] : data[ 8].value[0];
        case 9:
            return (sfp == SFP_DETECT) ? !data[11].value[0] : (sfp == SFP_FAULT) ? data[11].value[1] : data[10].value[0];
        }
        return false;
    } else {
        // Assuming BOARD_TYPE_OCELOT_PCB123
        switch (board_port) {
        case 4:
            return (sfp == SFP_DETECT) ? !data[ 0].value[1] : (sfp == SFP_FAULT) ? data[ 2].value[0] : data[ 0].value[0];
        case 5:
            return (sfp == SFP_DETECT) ? !data[ 1].value[1] : (sfp == SFP_FAULT) ? data[ 2].value[1] : data[ 1].value[0];
        case 6:
            return (sfp == SFP_DETECT) ? !data[ 4].value[1] : (sfp == SFP_FAULT) ? data[ 3].value[0] : data[ 4].value[0];
        case 7:
            return (sfp == SFP_DETECT) ? !data[ 6].value[1] : (sfp == SFP_FAULT) ? data[ 3].value[1] : data[ 6].value[0];
        case 8:
            return (sfp == SFP_DETECT) ? !data[ 9].value[1] : (sfp == SFP_FAULT) ? data[ 5].value[1] : data[ 9].value[0];
        case 9:
            return (sfp == SFP_DETECT) ? !data[10].value[1] : (sfp == SFP_FAULT) ? data[11].value[0] : data[10].value[0];
        case 10:
            return (sfp == SFP_DETECT) ? !data[ 7].value[1] : (sfp == SFP_FAULT) ? data[11].value[1] : data[ 7].value[0];
        case 11:
            return (sfp == SFP_DETECT) ? !data[ 8].value[1] : (sfp == SFP_FAULT) ? data[12].value[0] : data[ 8].value[0];
        }
        return false;
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
            return board->type == BOARD_TYPE_OCELOT_PCB120;
        case MEBA_CAP_TEMP_SENSORS:
            return board->type == BOARD_TYPE_OCELOT_PCB120 ? 2 : 1;
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
        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:      // Ocelot (PCB123 only) supports single DPLL mode if a DPLL is present
            if (board->type == BOARD_TYPE_OCELOT_PCB123) {
                meba_synce_clock_hw_id_t dpll_type;

                if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK) && (dpll_type != MEBA_SYNCE_CLOCK_HW_NONE)) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:        // Ocelot does not support dual DPLL mode
            return false;
        case MEBA_CAP_POE_BT:
            return false;
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
        *entry = board->port[port_no].map;
        rc = MESA_RC_OK;
    } else {
        rc = MESA_RC_ERROR;
    }
    T_N(inst, "Called(%d): rc %d - chip %d, miim bus %d, addr: %d", port_no, rc,
        entry->map.chip_port, entry->map.miim_controller, entry->map.miim_addr);
    return rc;
}

static mesa_rc ocelot_reset(meba_inst_t inst,
                            meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;
    mesa_port_no_t int_phy_base_port = 0, ext_phy_base_port = 0;

    /* API port to chip port mapping.
     * The mesa_phy_pre_reset() and mesa_phy_post_reset() functions of the PHY API
     * need to be called using the base port of the PHY device. That is according to
     * their specifications. To do that, we need to determine the equivalent API port
     * number for the base port of the PHY.
     * Ocelot has an internal Nano PHY and its base port is connected to chip port 0.
     * Additionally, 'PCB120' utilizes an extra external Viper PHY and its base port
     * is connected to Ocelot's chip port 4.
     * Based on the supported port maps for PCB120 and PCB123 (see pcb120_init_porttable()
     * and pcb123_init_porttable()) we can deduce the API port numbers for
     * 'int_phy_base_port' and 'ext_phy_base_port'.
     */
    if (board->type == BOARD_TYPE_OCELOT_PCB120) {
        // Only MESA_TARGET_7514 is supported by this board.
        int_phy_base_port = 7;
        ext_phy_base_port = 3;
    } else {
        // Assuming BOARD_TYPE_OCELOT_PCB123
        int_phy_base_port = 2;
        // No Ext PHY in this board
    }

    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            rc = board->func->board_init(inst);
            sleep(1); // Make sure PHYs are accessible
            break;
        case MEBA_PORT_RESET:
            if ((rc = mesa_phy_pre_reset(PHY_INST, int_phy_base_port)) == MESA_RC_OK) { // Internal Nano PHY
                if (board->type == BOARD_TYPE_OCELOT_PCB120) {
                    rc = mesa_phy_pre_reset(PHY_INST, ext_phy_base_port); // External Viper PHY
                }
            }
            break;
        case MEBA_PORT_RESET_POST:
            if ((rc = mesa_phy_post_reset(PHY_INST, int_phy_base_port)) == MESA_RC_OK) { // Internal Nano PHY
                if (board->type == BOARD_TYPE_OCELOT_PCB120) {
                    rc = mesa_phy_post_reset(PHY_INST, ext_phy_base_port); // External Viper PHY
                }
            }
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            for (meba_led_type_t type = MEBA_LED_TYPE_FRONT; type < MEBA_LED_TYPE_COUNT; type++) {
                inst->api.meba_status_led_set(inst, type, MEBA_LED_COLOR_OFF);
            }
            break;
        case MEBA_PORT_LED_INITIALIZE:
            break;
        case MEBA_FAN_INITIALIZE:
            break;
        case MEBA_SENSOR_INITIALIZE:
            if ((rc = mesa_phy_chip_temp_init(PHY_INST, int_phy_base_port)) == MESA_RC_OK) { // Internal Nano PHY
                if (board->type == BOARD_TYPE_OCELOT_PCB120) {
                    rc = mesa_phy_chip_temp_init(PHY_INST, ext_phy_base_port); // External Viper PHY
                }
            }
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

static mesa_rc ocelot_sensor_get(meba_inst_t inst,
                                 meba_sensor_t type,
                                 int six,
                                 int *value)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_ERROR;
    int16_t temp = 0;

    T_N(inst, "Called %d:%d", type, six);
    if (type == MEBA_SENSOR_BOARD_TEMP) {
        if (six < ocelot_capability(inst, MEBA_CAP_TEMP_SENSORS)) {
            if (board->type == BOARD_TYPE_OCELOT_PCB120) {
                // PCB120 has a temperature sensor in the internal Nano PHY
                // and one in the external Viper PHY.
                // Viper is for board ports 0-3, thus we access it on port 0.
                // Nano is for board ports 4-7, thus we access it on port 4.
                rc = mesa_phy_chip_temp_get(PHY_INST, six * 4, &temp);
            } else {
                // Assuming BOARD_TYPE_OCELOT_PCB123
                // PCB123 has only one sensor in the internal Nano PHY.
                // We access it on port 0.
                rc = mesa_phy_chip_temp_get(PHY_INST, six, &temp);
            }
        }
    } else if (type == MEBA_SENSOR_PORT_TEMP && six < board->port_cnt) {
        mesa_port_no_t max_phy_port_no;
        int32_t board_port = PORT_2_BOARD_PORT(board, six);
        if (board->type == BOARD_TYPE_OCELOT_PCB120) {
            max_phy_port_no = 7;
        } else {
            // Assuming BOARD_TYPE_OCELOT_PCB123
            max_phy_port_no = 3;
        }
        if (board_port <= max_phy_port_no) {
            // Call the PHY API and retrieve the temperature
            rc = mesa_phy_chip_temp_get(PHY_INST, six, &temp);
        } else {
            // No temperature sensor on these ports
            temp = 0;
            rc = MESA_RC_OK;
        }
    }

    if (rc == MESA_RC_OK) {
        *value = temp;    // Conversion
    }

    return rc;
}

static mesa_rc ocelot_sfp_i2c_xfer(meba_inst_t inst,
                                   mesa_port_no_t port_no,
                                   mesa_bool_t write,
                                   uint8_t i2c_addr,
                                   uint8_t addr,
                                   uint8_t *data,
                                   uint8_t cnt,
                                   mesa_bool_t word_access)
{
    mesa_rc            rc;
    meba_board_state_t *board = INST2BOARD(inst);
    int32_t            board_port = PORT_2_BOARD_PORT(board, port_no);

    T_N(inst, "Called");
    // If the port is a dual-media one, then the board port no is different
    if (has_cap(board->port[port_no].map.cap, (MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER))) {
        board_port = DUAL_PORT_2_BOARD_PORT(board, port_no);
    }
    if (write) {    // cnt ignored
        uint8_t i2c_data[3];
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        rc = inst->iface.i2c_write(board_port, i2c_addr, i2c_data, 3);
    } else {
        rc = inst->iface.i2c_read(board_port, i2c_addr, addr, data, cnt);
    }
    T_D(inst, "i2c %s port %d, board_port %d - address 0x%02x:0x%02x, %d bytes return %d", write ? "write" : "read", port_no, board_port, i2c_addr, addr, cnt, rc);
    return rc;
}

static mesa_rc ocelot_sfp_insertion_status_get(meba_inst_t inst,
                                               mesa_port_list_t *present)
{
    meba_board_state_t    *board = INST2BOARD(inst);
    mesa_rc                rc;
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];

    mesa_port_list_clear(present);

    if ((rc = mesa_sgpio_read(NULL, 0, 0, data)) == MESA_RC_OK) {
        mesa_port_no_t port_no;
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            mesa_bool_t detect = get_sfp_status(inst, port_no, data, SFP_DETECT);
            mesa_port_list_set(present, port_no, detect);
            T_N(inst, "port:%d, status:%d", port_no, detect);
        }
    }

    return rc;
}

static mesa_rc ocelot_sfp_status_get(meba_inst_t inst,
                                     mesa_port_no_t port_no,
                                     meba_sfp_status_t *status)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);

    if (port_no < board->port_cnt) {
        mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];
        meba_port_entry_t  *entry = &board->port[port_no].map;
        if ((rc = mesa_sgpio_read(NULL, 0, 0, data)) == MESA_RC_OK) {
            if ((entry->cap & MEBA_PORT_CAP_SFP_DETECT) || (entry->cap & MEBA_PORT_CAP_DUAL_SFP_DETECT)) {
                status->present  = get_sfp_status(inst, port_no, data, SFP_DETECT);
                status->tx_fault = get_sfp_status(inst, port_no, data, SFP_FAULT);
                status->los      = get_sfp_status(inst, port_no, data, SFP_LOS);
            } else {
                status->present  = false;
                status->los      = true;
                status->tx_fault = true;
            }
        }
    }
    return rc;
}

static mesa_rc ocelot_port_admin_state_set(meba_inst_t inst,
                                           mesa_port_no_t port_no,
                                           const meba_port_admin_state_t *state)
{
    mesa_rc            rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    int32_t            board_port = PORT_2_BOARD_PORT(board, port_no);
    mesa_sgpio_conf_t  conf;
    mesa_sgpio_mode_t  sgpio_mode = state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF;

    if (board->type == BOARD_TYPE_OCELOT_PCB120) {
        /* Only applies for SFP ports, so exit faster if port is not an SFP */
        if (board_port < 8) {
            return rc;
        }
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            /* Configure SFP TxDisable */
            switch (port_no) {
            case 8:
                conf.port_conf[11].mode[0] = sgpio_mode;
                break;
            case 9:
                conf.port_conf[11].mode[1] = sgpio_mode;
                break;
            }

            rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        }
    } else {
        // If the port is a dual-media one, then the board port no is different
        if (has_cap(board->port[port_no].map.cap, (MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER))) {
            board_port = DUAL_PORT_2_BOARD_PORT(board, port_no);
        }
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            /* Configure SFP TxDisable */
            switch (board_port) {
            case 4:
                conf.port_conf[20].mode[0] = sgpio_mode;
                break;
            case 5:
                conf.port_conf[20].mode[1] = sgpio_mode;
                break;
            case 6:
               conf.port_conf[21].mode[0] = sgpio_mode;
               break;
            case 7:
                conf.port_conf[21].mode[1] = sgpio_mode;
                break;
            case 8:
                conf.port_conf[22].mode[0] = sgpio_mode;
                break;
            case 9:
                conf.port_conf[22].mode[1] = sgpio_mode;
                break;
            case 10:
                conf.port_conf[23].mode[0] = sgpio_mode;
                break;
            case 11:
                conf.port_conf[23].mode[1] = sgpio_mode;
                break;
            default:
                return rc;
            }

            rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        }
    }
    return rc;
}

static mesa_rc ocelot_status_led_set(meba_inst_t inst,
                                     meba_led_type_t type,
                                     meba_led_color_t color)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);
    if (type < MEBA_LED_TYPE_COUNT && color < MEBA_LED_COLOR_COUNT) {
        mesa_sgpio_conf_t conf;
        T_N(inst, "LED:%d, color=%d", type, color);
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            uint32_t sgpio = MESA_SGPIO_PORTS;
            if (board->type == BOARD_TYPE_OCELOT_PCB123) {
                switch (type) {
                    case MEBA_LED_TYPE_FRONT:
                        sgpio = 11;
                        break;
                    default:;
                }
            } else {    // PCB120
                switch (type) {
                    case MEBA_LED_TYPE_FRONT:
                        sgpio = 16;
                        break;
                    case MEBA_LED_TYPE_POE:
                        sgpio = 12;
                        break;
                    case MEBA_LED_TYPE_DC_A:
                        sgpio = 14;
                        break;
                    case MEBA_LED_TYPE_DC_B:
                        sgpio = 15;
                        break;
                    case MEBA_LED_TYPE_ALARM:
                        sgpio = 13;
                        break;
                    default:;
                }
            }
            if (sgpio < MESA_SGPIO_PORTS) {
                mesa_sgpio_port_conf_t *port_conf = &conf.port_conf[sgpio];
#define RED 0    // NB: Red/Green reversed in board docs
#define GRN 1    // NB: Red/Green reversed in board docs
#define ON  MESA_SGPIO_MODE_OFF
#define OFF MESA_SGPIO_MODE_ON
                T_N(inst, "LED:%d, sgpio %d, color=%d", type, sgpio, color);
                switch (color) {
                    case MEBA_LED_COLOR_OFF:
                        port_conf->mode[RED] = OFF;
                        port_conf->mode[GRN] = OFF;
                        break;
                    case MEBA_LED_COLOR_GREEN:
                        port_conf->mode[RED] = OFF;
                        port_conf->mode[GRN] = ON;
                        break;
                    case MEBA_LED_COLOR_RED:
                        port_conf->mode[RED] = ON;
                        port_conf->mode[GRN] = OFF;
                        break;
                    case MEBA_LED_COLOR_YELLOW:
                        port_conf->mode[RED] = ON;
                        port_conf->mode[GRN] = ON;
                        break;
                    default:
                        rc = MESA_RC_ERROR;
                }
                if (rc == MESA_RC_OK) {
                    rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
                }
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
    int32_t            board_port = PORT_2_BOARD_PORT(board, port_no);
    mesa_rc            rc = MESA_RC_OK;

    /* Skip NPI port for PCB123 */
    if (board->type == BOARD_TYPE_OCELOT_PCB123 && board_port == 12) {
        return rc;
    }

    if (port_no < board->port_cnt) {
        uint32_t activity = port_activity(inst, port_no, status, counters);
        if (activity) {
            mesa_sgpio_conf_t conf;

            if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
                mesa_sgpio_mode_t mode_green, mode_red;
                uint32_t sgpio_port = board->sgpio_port[board_port];
                if (board->type == BOARD_TYPE_OCELOT_PCB123) {
                    /* For dual-media ports, determine which board port is active */
                    if (has_cap(board->port[port_no].map.cap, (MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER))) {
                        uint32_t sgpio_port_other = sgpio_port;
                        if (status->fiber) {
                            board_port = DUAL_PORT_2_BOARD_PORT(board, port_no);
                            sgpio_port = board->sgpio_port[board_port];
                        } else {
                            sgpio_port_other = board->sgpio_port[DUAL_PORT_2_BOARD_PORT(board, port_no)];
                        }
                        /* A hack for dual-media ports without a LED selector */
                        if (sgpio_port != sgpio_port_other) {
                            /* Both LEDs off for the inactive part of the dual-media port */
                            conf.port_conf[sgpio_port_other].mode[1] = MESA_SGPIO_MODE_ON; // NB: Red/Green reversed in board docs
                            conf.port_conf[sgpio_port_other].mode[0] = MESA_SGPIO_MODE_ON;   // NB: Red/Green reversed in board docs
                        }
                    }
                    /* Dual-media LED selector */
                    if (sgpio_port < 2) {
                        conf.port_conf[12].mode[sgpio_port] = (status->fiber ? MESA_SGPIO_MODE_OFF : MESA_SGPIO_MODE_ON);
                    }
                }
                if (status->link) {
                    mode_green = ((activity & ACTIVITY_CNT) ? MESA_SGPIO_MODE_0_ACTIVITY : MESA_SGPIO_MODE_OFF);
                    /* Hack for port mux modes where PCB123 cannot provide automatic LED activity blink.
                       For these ports, the port LED will only indicate the link status, but no activity. */
                    if (board->type == BOARD_TYPE_OCELOT_PCB123) {
                        switch (inst->props.mux_mode) {
                        case MESA_PORT_MUX_MODE_0:
                            if ((board_port >= 6) & (board_port <= 8)) {
                                mode_green = MESA_SGPIO_MODE_OFF;
                            }
                            break;
                        case MESA_PORT_MUX_MODE_1:
                            if ((board_port >= 6) & (board_port <= 9)) {
                                mode_green = MESA_SGPIO_MODE_OFF;
                            }
                            break;
                        case MESA_PORT_MUX_MODE_2:
                        case MESA_PORT_MUX_MODE_3:
                        case MESA_PORT_MUX_MODE_4:
                        case MESA_PORT_MUX_MODE_5:
                        default:
                            break;
                        }
                    }
                    if (status->speed >= MESA_SPEED_1G) {
                        /* Green activity */
                        mode_red = MESA_SGPIO_MODE_ON;    // Red OFF
                    } else {
                        /* Yellow activity */
                        mode_red = mode_green;            // Red + Green => Yellow
                    }
                } else {
                    /* Both LEDs off */
                    mode_red = MESA_SGPIO_MODE_ON;
                    mode_green = MESA_SGPIO_MODE_ON;
                }

                T_N(inst, "Port %d (chip %d) = [%d,%d]", port_no, sgpio_port, mode_green, mode_red);
                conf.port_conf[sgpio_port].mode[1] = mode_green; // NB: Red/Green reversed in board docs
                conf.port_conf[sgpio_port].mode[0] = mode_red;   // NB: Red/Green reversed in board docs
                rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
            }
        }
    }
    return rc;
}

static mesa_rc ocelot_ptp_rs422_conf_get(meba_inst_t inst,
        meba_ptp_rs422_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    T_N(inst, "Called");
    meba_board_state_t *board = INST2BOARD(inst);
    if (board->type == BOARD_TYPE_OCELOT_PCB123) {
        *conf = pcb123_rs422_conf;
    } else {
        *conf = other_rs422_conf;
    }
    return rc;
}

static mesa_rc ocelot_event_enable(meba_inst_t inst,
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
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (is_sfp_port(board->port[port_no].map.cap)) {
                    int32_t  board_port = PORT_2_BOARD_PORT(board, port_no);
                    uint32_t sgpio_port;
                    /* If the port is a dual-media one, then the board port no is different */
                    if (has_cap(board->port[port_no].map.cap, (MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER))) {
                        board_port = DUAL_PORT_2_BOARD_PORT(board, port_no);
                    }
                    sgpio_port = board->sgpio_port[board_port];
                    // Enable SGPIO for SFP ports
                    T_D(inst, "%sable LOS on port %d GPIO %d", enable ? "en" : "dis", port_no, sgpio_port);
                    if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, sgpio_port, 0, enable)) != MESA_RC_OK) {
                        T_E(inst, "mesa_sgpio_event_enable(%d) = %d", sgpio_port, rc);
                    }
                }
            }
            break;

        case MEBA_EVENT_FLNK:
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (is_phy_internal(board->port[port_no].map.cap)) {
                    T_D(inst, "port(%d) %sable DEV_ALL", port_no, enable ? "en" : "dis");
                    if ((rc = mesa_dev_all_event_enable(NULL, port_no, MESA_DEV_ALL_LINK_EV, enable)) != MESA_RC_OK) {
                        T_E(inst, "Could not enable event for dev #%d = %d", port_no, rc);
                    }
                }
                if (is_phy_port(board->port[port_no].map.cap)) {
                    T_D(inst, "%sable FLNK on port %d", enable ? "en" : "dis", port_no);
                    if ((rc = mesa_phy_event_enable_set(PHY_INST, port_no, MESA_PHY_LINK_FFAIL_EV, enable)) != MESA_RC_OK) {
                        T_E(inst, "mesa_phy_event_enable_set = %d", rc);
                        break;
                    }
                }
            }
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

    // Poll SGPIO LOS from SFP ports
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (is_sfp_port(board->port[port_no].map.cap)) {
            int32_t  board_port = PORT_2_BOARD_PORT(board, port_no);
            uint32_t sgpio_port;
            /* If the port is a dual-media one, then the board port no is different */
            if (has_cap(board->port[port_no].map.cap, (MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER))) {
                board_port = DUAL_PORT_2_BOARD_PORT(board, port_no);
            }
            sgpio_port = board->sgpio_port[board_port];
            if (sgpio_port < MESA_SGPIO_PORTS && sgpio_events[sgpio_port]) {
                // SGPIO port no
                if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, sgpio_port, 0, false)) != MESA_RC_OK) {
                    T_E(inst, "mesa_sgpio_event_enable  = %d", rc);
                }
                T_I(inst, "LOS IRQ port %d gpio %d", port_no, sgpio_port);
                signal_notifier(MEBA_EVENT_LOS, port_no);
                handled++;
            }
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

static mesa_rc dev_all_handler(meba_inst_t inst,
                               meba_board_state_t *board,
                               meba_event_signal_t signal_notifier)
{
    mesa_dev_all_event_type_t  dev_all_events[MESA_CAP(MESA_CAP_PORT_CNT)];
    mesa_port_no_t port_no;
    int handled = 0;

    if (mesa_dev_all_event_poll(NULL, MESA_DEV_ALL_POLL_ALL, dev_all_events) != MESA_RC_OK) {
        T_E(inst, "mesa_dev_all_event_poll failed");
        return MESA_RC_ERROR;
    }

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (dev_all_events[port_no] & MESA_DEV_ALL_LINK_EV) {
            T_I(inst, "DEV %d intr", port_no);
            if (mesa_dev_all_event_enable(NULL, port_no, dev_all_events[port_no], false) != MESA_RC_OK) {
                T_E(inst, "mesa_dev_all_event_enable failed");
            }
            if (is_phy_port(board->port[port_no].map.cap)) {
                if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                    T_D(inst, "port(%d) PHY IRQ handled", port_no);
                    handled++;
                }
            }
        }
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc ocelot_irq_handler(meba_inst_t inst,
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
        case MESA_IRQ_DEV_ALL:
            return dev_all_handler(inst, board, signal_notifier);
        default:;
    }

    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc ocelot_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
        case MESA_IRQ_PTP_RDY:
        case MESA_IRQ_OAM:
        case MESA_IRQ_SGPIO:
        case MESA_IRQ_EXT0:
        case MESA_IRQ_DEV_ALL:
            rc = MESA_RC_OK;
        default:;
    }
    return rc;
}

meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t        inst;
    meba_board_state_t *board;
    uint16_t           dummy = 0;
    uint32_t           i;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate pulic state
    if ((inst = meba_state_alloc(callouts,
                                 "Ocelot",
                                 MESA_TARGET_7514,
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    if (meba_conf_get_u32(inst, "mux_mode", &i) == MESA_RC_OK) {
        inst->props.mux_mode = (mesa_port_mux_mode_t) i;
    } else {
        // Defaults
        T_D(inst, "Failed to read 'mux_mode' from the configuration file, reverting to defaults.");
        if (inst->props.target == MESA_TARGET_7513) {
            inst->props.mux_mode = MESA_PORT_MUX_MODE_0;
        } else if (inst->props.target == MESA_TARGET_7514) {
            inst->props.mux_mode = MESA_PORT_MUX_MODE_4;
        }
    }

    (void)mebaux_gpio_mode_set(inst, &rawio, 14, MESA_GPIO_ALT_0);
    (void)mebaux_gpio_mode_set(inst, &rawio, 15, MESA_GPIO_ALT_0);
    if (mebaux_miim_rd(inst, &rawio, MESA_MIIM_CONTROLLER_1, 0, 0, &dummy) == MESA_RC_OK) {
        board->type = BOARD_TYPE_OCELOT_PCB120;
        strncpy(inst->props.name, "Ocelot DIN", sizeof(inst->props.name));
        if (inst->props.target == MESA_TARGET_7513) {
            T_E(inst, "The %s board does not support the chip target %4x", inst->props.name, inst->props.target);
            goto error_out;
        } else if (inst->props.target == MESA_TARGET_7514) {
            if (inst->props.mux_mode == MESA_PORT_MUX_MODE_4) {
                board->port_cnt = 10;
            } else {
                T_E(inst, "The %s board does not support the port mux_mode %d", inst->props.name, inst->props.mux_mode);
                goto error_out;
            }
        }
    } else {
        board->type = BOARD_TYPE_OCELOT_PCB123;
        strncpy(inst->props.name, "Ocelot Ref", sizeof(inst->props.name));
        if (inst->props.target == MESA_TARGET_7513) {
            switch (inst->props.mux_mode) {
            case MESA_PORT_MUX_MODE_0:
                board->port_cnt = 7;
                break;
            case MESA_PORT_MUX_MODE_1:
                board->port_cnt = 6;
                break;
            case MESA_PORT_MUX_MODE_2:
            case MESA_PORT_MUX_MODE_3:
            case MESA_PORT_MUX_MODE_4:
            case MESA_PORT_MUX_MODE_5:
            default:
                T_E(inst, "This board does not support mux_mode %d", inst->props.mux_mode);
                goto error_out;
            }
        } else if (inst->props.target == MESA_TARGET_7514) {
            switch (inst->props.mux_mode) {
            case MESA_PORT_MUX_MODE_0:
                board->port_cnt = 9;
                break;
            case MESA_PORT_MUX_MODE_1:
                board->port_cnt = 8;
                break;
            case MESA_PORT_MUX_MODE_2:
            case MESA_PORT_MUX_MODE_3:
                T_E(inst, "This board does not support mux_mode %d", inst->props.mux_mode);
                goto error_out;
            case MESA_PORT_MUX_MODE_4:
                board->port_cnt = 11;
                break;
            case MESA_PORT_MUX_MODE_5:
                board->port_cnt = 10;
                break;
            default:
                T_E(inst, "This board does not support mux_mode %d", inst->props.mux_mode);
                goto error_out;
            }
        }
    }

    board->func = &board_funcs[board->type];

    board->port = (ocelot_port_info_t*) calloc(board->port_cnt, sizeof(ocelot_port_info_t));
    if (board->port == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    // The actual number of ports the HW design has, not the one exposed by board->port_cnt
    uint32_t count = (board->type == BOARD_TYPE_OCELOT_PCB123) ? 12 : 10;
    board->sgpio_port = (uint32_t*) calloc(count, sizeof(uint32_t));
    if (board->sgpio_port == NULL) {
        fprintf(stderr, "Board to SGPIO port table malloc failure\n");
        goto error_out;
    }

    /* Fill out port mapping table */
    board->func->init_porttable(inst);

    inst->props.board_type = (vtss_board_type_t) (VTSS_BOARD_OCELOT_REF + board->type);    // Exposed temporarily
    T_I(inst, "Board: %s, type %d, target %4x, %d ports, port_cfg %d",
        inst->props.name, board->type, inst->props.target, board->port_cnt, inst->props.mux_mode);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = ocelot_capability;
    inst->api.meba_port_entry_get             = ocelot_port_entry_get;
    inst->api.meba_reset                      = ocelot_reset;
    inst->api.meba_sensor_get                 = ocelot_sensor_get;
    inst->api.meba_sfp_i2c_xfer               = ocelot_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = ocelot_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = ocelot_sfp_status_get;
    inst->api.meba_port_admin_state_set       = ocelot_port_admin_state_set;
    inst->api.meba_status_led_set             = ocelot_status_led_set;
    inst->api.meba_port_led_update            = ocelot_port_led_update;
    //inst->api.meba_led_intensity_set          = ocelot_led_intensity_set;
    inst->api.meba_irq_handler                = ocelot_irq_handler;
    inst->api.meba_irq_requested              = ocelot_irq_requested;
    inst->api.meba_event_enable               = ocelot_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get         = ocelot_ptp_rs422_conf_get;

    inst->api_synce = meba_synce_get();
    inst->api_tod = meba_tod_get();
    inst->api_poe = meba_poe_get();

    return inst;

error_out:
   free(inst);
   return NULL;
}
