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
    meba_port_entry_t  map;
    uint32_t           board_port;
    uint32_t           sgpio_port;
    mesa_port_status_t status;
    mesa_bool_t        activity;
} fa_port_info_t;

// The PCB type
typedef enum {
    BOARD_TYPE_SPARX5_PCB125 = 125,  /* FA Modular board */
    BOARD_TYPE_SPARX5_PCB134 = 134,  /* 20xSFP + NPI */
    BOARD_TYPE_SPARX5_PCB135 = 135,  /* 48x1G + 4x10G + 4x25G + NPI */
    BOARD_TYPE_SPARX5_EMULATION = 999,
} board_type_t;

/* SparX-5 Ref board port configurations  */
typedef enum {
    VTSS_BOARD_CONF_20x10G_NPI,
    VTSS_BOARD_CONF_8x25G_NPI,
    VTSS_BOARD_CONF_4x10G,
    VTSS_BOARD_CONF_6x10G_NPI,
    VTSS_BOARD_CONF_9x10G_NPI,
    VTSS_BOARD_CONF_12x10G_NPI,
    VTSS_BOARD_CONF_16x10G_NPI,
    VTSS_BOARD_CONF_24x1G_4x10G_NPI,
    VTSS_BOARD_CONF_48x1G_4x10G_NPI,
    VTSS_BOARD_CONF_48x1G_8x10G_NPI,
    VTSS_BOARD_CONF_48x1G_4x10G_4x25G_NPI,
    VTSS_BOARD_CONF_LAST
} board_port_cfg_t;

typedef struct {
    void (*board_init)(meba_inst_t inst);
    void (*init_port)(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry);
} board_func_t;

typedef struct meba_board_state {
    board_type_t          type;
    board_port_cfg_t      port_cfg;
    mesa_bool_t           beaglebone;
    mesa_bool_t           ls1046;
    uint32_t              port_cnt;
    int                   cpu_port_cnt;
    fa_port_info_t       *port;
    const board_func_t    *func;
} meba_board_state_t;

#define VTSS_MSLEEP(m) usleep((m) * 1000)
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

#define PORT_2_BOARD_PORT(board, p) (board->port[p].board_port)
#define PORT_2_SGPIO_PORT(board, p) (board->port[p].sgpio_port)

/* --------------------------- Board specific ------------------------------- */

static void fa_emul_init_port(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    entry->map.chip_port       = port_no;
    entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
    entry->map.miim_addr       = port_no;
    entry->map.max_bw          = MESA_BW_1G;
    entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
    entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
}

static void fa_emul_board_init(meba_inst_t inst)
{
    T_I(inst, "TBD");
}


static void fa_pcb125_init_port(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    meba_board_state_t *board = INST2BOARD(inst);

    switch (board->port_cfg) {
    case VTSS_BOARD_CONF_4x10G:
        if (port_no < board->port_cnt) {
            if (port_no < 4) {
                // 10G ports
                entry->map.chip_port       = port_no + 48; // 12-15(10G), 48-55(10G), 56-63(25G)
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = MESA_BW_10G;
//                entry->mac_if              = MESA_PORT_INTERFACE_SFI;
                entry->mac_if              = MESA_PORT_INTERFACE_SGMII_CISCO;
//                entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
                entry->cap                 = (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
                entry->cap                 &= ~MEBA_PORT_CAP_SFP_DETECT; // No SFP detection
            } else {
                // 25G ports
                entry->map.chip_port       = port_no - 4 + 56; // 56-63(25G)
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = MESA_BW_10G;
//                entry->mac_if              = MESA_PORT_INTERFACE_SFI;
                if ((port_no == 4) || (port_no == 5)) {
                    entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
                } else {
                    entry->mac_if              = MESA_PORT_INTERFACE_SGMII_CISCO;
                }
//                entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
                entry->cap                 = (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
                entry->cap                 &= ~MEBA_PORT_CAP_SFP_DETECT; // No SFP detection
            }
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }

        break;
    default:
        T_E(inst, "Board type (%d) not supported!", board->type);
    }
}

static void update_entry(meba_inst_t inst, meba_port_entry_t *entry, mesa_port_interface_t if_type, mesa_internal_bw_t bw, uint32_t port_no)
{
    if (if_type == MESA_PORT_INTERFACE_QSGMII) {
        entry->map.chip_port       = port_no;
        entry->map.miim_addr       = port_no % 24;
        entry->map.miim_controller = port_no < 24 ? MESA_MIIM_CONTROLLER_0 : MESA_MIIM_CONTROLLER_1;
        entry->map.max_bw          = MESA_BW_1G;
        entry->mac_if              = MESA_PORT_INTERFACE_QSGMII;
        entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
    } else if  (if_type == MESA_PORT_INTERFACE_SFI || if_type == MESA_PORT_INTERFACE_SGMII_CISCO) {
        entry->map.chip_port       = port_no;
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
        entry->map.max_bw          = bw;
        entry->mac_if              = if_type;
        entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
        if (bw == MESA_BW_25G) {
            entry->cap             |= MEBA_PORT_CAP_25G_FDX;
        }
    } else if (if_type == MESA_PORT_INTERFACE_SGMII) {
        // NPI port
        entry->map.chip_port       = 64;
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_3;
        entry->map.miim_addr       = 28;
        entry->map.max_bw          = MESA_BW_1G;
        entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
        entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
    }
    entry->cap &= ~MEBA_PORT_CAP_SD_INTERNAL; // Signal detect (LOS) comes from SFP module (and not from Serdes)
}

static void fa_pcb134_init_port(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    meba_board_state_t *board = INST2BOARD(inst);

    switch (board->port_cfg) {
    case VTSS_BOARD_CONF_6x10G_NPI:
    case VTSS_BOARD_CONF_9x10G_NPI:
    case VTSS_BOARD_CONF_12x10G_NPI:
    case VTSS_BOARD_CONF_16x10G_NPI:
    case VTSS_BOARD_CONF_20x10G_NPI:
        if (port_no < board->port_cnt - 1) {
            mesa_port_interface_t mac_if = MESA_PORT_INTERFACE_SFI;
            if (board->beaglebone) {
                // Hardcode some ports to support CuSFP as we are missing I2C support
                mac_if = port_no < 8 ? MESA_PORT_INTERFACE_SGMII_CISCO : MESA_PORT_INTERFACE_SFI;
            }
            update_entry(inst, entry, mac_if, MESA_BW_10G, port_no < 4 ? port_no + 12 : port_no + 44); // 56-63(25G)
        } else if (port_no == board->port_cnt - 1) {
            if (board->ls1046) {
                entry->map.chip_port = CHIP_PORT_UNUSED;
                entry->cap           = MEBA_PORT_CAP_CPU | MEBA_PORT_CAP_AUTONEG;
            } else {
                // NPI port
                update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
            }
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    break;
    case VTSS_BOARD_CONF_8x25G_NPI:
        if (port_no < board->port_cnt - 1) {
            // 25G ports
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_25G, 56 + port_no); // 56-63(25G)
        } else if (port_no == board->port_cnt - 1) {
            if (board->ls1046) {
                entry->map.chip_port = CHIP_PORT_UNUSED;
                entry->cap                 = MEBA_PORT_CAP_CPU | MEBA_PORT_CAP_AUTONEG;
            } else {
                // NPI port
                update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
            }
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    break;

    default:
        T_E(inst, "Board type (%d) not supported!", board->type);
    }
}

static void fa_pcb135_init_port(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    meba_board_state_t *board = INST2BOARD(inst);

    switch (board->port_cfg) {
    case VTSS_BOARD_CONF_24x1G_4x10G_NPI:
        if (port_no < 24) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_QSGMII, MESA_BW_1G, port_no);
        } else if (port_no < 28) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_10G, 56 + port_no - 24); // 10G: 56-59
        } else if (port_no == 28) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
        break;
    case VTSS_BOARD_CONF_48x1G_4x10G_NPI:
        if (port_no < 48) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_QSGMII, MESA_BW_1G, port_no);
        } else if (port_no < 52) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_10G, 56 + port_no - 48); // 10G: 56-59
        } else if (port_no == 52) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
        break;
    case VTSS_BOARD_CONF_48x1G_8x10G_NPI:
        if (port_no < 48) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_QSGMII, MESA_BW_1G, port_no);
        } else if (port_no < 56) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_10G, 56 + port_no - 48); // 10G: 56-63
        } else if (port_no == 56) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
        break;
    case VTSS_BOARD_CONF_48x1G_4x10G_4x25G_NPI:
        if (port_no < 48) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_QSGMII, MESA_BW_1G, port_no);
        } else if (port_no < 52) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_10G, 56 + port_no - 48); // 10G: 56-59
        } else if (port_no < 56) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_25G, 56 + port_no - 48); // 25G: 60-63
        } else if (port_no == 56) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    break;

    default:
        T_E(inst, "Board type (%d) not supported!", board->type);
    }
}

static void fa_pcb125_board_init(meba_inst_t inst)
{

}

static void fa_pcb135_board_init(meba_inst_t inst)
{
    mesa_sgpio_conf_t conf;
    uint32_t port, gpio_no;

    /* Configure GPIOs for MIIM/MDIO bus 0-1, QSGMII ports */
    for (gpio_no = 56; gpio_no < 60; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }
    /* Configure GPIOs for MIIM/MDIO bus 3, NPI port */
    (void)mesa_gpio_mode_set(NULL, 0, 52, MESA_GPIO_ALT_1);
    (void)mesa_gpio_mode_set(NULL, 0, 53, MESA_GPIO_ALT_1);

    /* GPIOs for SGPIO Group 1: LEDs for 10/25G ports  */
    (void)mesa_gpio_mode_set(NULL, 0, 4, MESA_GPIO_ALT_0);  // SGPIO Grp 1 / CLK
    (void)mesa_gpio_mode_set(NULL, 0, 5, MESA_GPIO_ALT_0);  // SGPIO Grp 1 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 12, MESA_GPIO_ALT_0); // SGPIO Grp 1 / DI
    (void)mesa_gpio_mode_set(NULL, 0, 13, MESA_GPIO_ALT_0); // SGPIO Grp 1 / LD

    /* GPIOs for SGPIO Group 2: SFP signals for 10/25G ports   */
    (void)mesa_gpio_mode_set(NULL, 0, 30, MESA_GPIO_ALT_0); // SGPIO Grp 2 / Clk
    (void)mesa_gpio_mode_set(NULL, 0, 31, MESA_GPIO_ALT_0); // SGPIO Grp 2 / LD
    (void)mesa_gpio_mode_set(NULL, 0, 32, MESA_GPIO_ALT_0); // SGPIO Grp 2 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 33, MESA_GPIO_ALT_0); // SGPIO Grp 2 / DI

    /* SGPIO group 1 controls Port LEDs for D60-D63  */
    if (mesa_sgpio_conf_get(NULL, 0, 1, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        for (port = 28; port < 32; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;  // Turn on LEDs while booting
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 1, &conf);
    }

    /* SGPIO group 2 controls SFP signals for the 4x25G ports */
    if (mesa_sgpio_conf_get(NULL, 0, 2, &conf) == MESA_RC_OK) {
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 3;
        for (port = 0; port < 32; port++) {
            if (port == 0 || (port >= 16 && port <= 18) || port >= 28) {
                conf.port_conf[port].enabled = 1;
                conf.port_conf[port].int_pol_high[0] = true;        // LOS interrupt is active high (input)
                conf.port_conf[port].int_pol_high[2] = true;        // TX_FAULT interrupt is active high (input)
                conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_OFF; // TXDisable is enabled through fa_port_admin_state_set() (output)
                conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_ON;  // Ratesel0 always eanbled (output)
                conf.port_conf[port].mode[2] = MESA_SGPIO_MODE_ON;  // Ratesel1 always eanbled (output)
            }
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 2, &conf);
    }
    /* Turn on the Status LED to Red */
    mesa_gpio_direction_set(NULL, 0, STATUSLED_G_GPIO, true);
    mesa_gpio_direction_set(NULL, 0, STATUSLED_R_GPIO, true);
    inst->api.meba_status_led_set(inst, MEBA_LED_TYPE_FRONT, MEBA_LED_COLOR_RED);
}

static void fa_pcb134_board_init(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t conf;
    uint32_t port;

    if (!board->ls1046) {  // ls1046 has it own MIIM bus to the phy
        // Configure GPIOs for MIIM/MDIO bus 3
        (void)mesa_gpio_mode_set(NULL, 0, 52, MESA_GPIO_ALT_1);
        (void)mesa_gpio_mode_set(NULL, 0, 53, MESA_GPIO_ALT_1);
    }
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
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;  // Turn on LEDs while booting
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF;
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
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;  // Turn on LEDs while booting
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 1, &conf);
    }

    /* Setup SGPIO group 2 controls SFP signals */
    if (mesa_sgpio_conf_get(NULL, 0, 2, &conf) == MESA_RC_OK) {
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 3;
        // Setup p0 for S0
        // p0 has to be enabled in order for the bit shifting
        // to work as expected and p12-31 end up being mapped
        // to the front ports (SFP1-20), but it is not used for
        // anything else, so no additional conf is applied.
        conf.port_conf[0].enabled = 1;
        // SW_WA_PCB134
        // Due to a hardware bug in PCB134, all SGPIOs in group 2
        // are shifted to the left by 1 bit, so p31b0 is p31b1,
        // p31b1 is p31b2 and p31b2 is p32b0.
        // Since there is no p32, we are enabling one more port
        // in the SGPIO port map, thus shifting all SGPIOs by 3 bits
        // to the right and p32b0 is now accessible at p31b0.
        conf.port_conf[11].enabled = 1;
        // Setup p12-31 for S13-32 (SFPs 1-20)
        for (port = 12; port < 32; port++) {
            // SW_WA_PCB134
            // Due to a hardware bug in PCB134, all SGPIOs in group 2
            // are shifted to the left by 1 bit, so p31b0 is p31b1,
            // p31b1 is p31b2 and p31b2 is p32b0.
            // Since there is no p32, we are enabling one more port
            // in the SGPIO port map, thus shifting all SGPIOs by 3 bits
            // to the right and p32b0 is now accessible at p31b0.
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port - 1].int_pol_high[1] = true;        // LOS interrupt is active high (input)
            conf.port_conf[port].int_pol_high[0] = true;            // TX_FAULT interrupt is active high (input)
            conf.port_conf[port - 1].mode[1] = MESA_SGPIO_MODE_OFF; // TXDisable is enabled through fa_port_admin_state_set() (output)
            conf.port_conf[port - 1].mode[2] = MESA_SGPIO_MODE_ON;  // Ratesel0 always enabled (output)
            conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_ON;      // Ratesel1 always enabled (output)
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 2, &conf);
    }

    // Due to the same hardware bug as above the Signal Detect (LOS) from the
    // SFP modules cannot be used as an input into the PCS as the bit position
    // has changed from default.
    // Therefore we need to manually map the LOS bit into the correct device.
    // There is no API for this therefore we write directly to the hw.
    uint32_t addr;
    // Register:   VTSS_DEVCPU_GCB_HW_SGPIO_SD_CFG:SD_MAP_SEL(1)
    (void)inst->iface.reg_write(0, 0x4000000 + 0x404005, 0x1);
    for (uint32_t port = 0; port < 20; port++) {
        // ctrl [1-3], port [1-32], bit [1-4]
        // Mapping: DEV12->p11b1 : sgpio(ctrl,port,bit) = sgpio(2,11,2) = (ctrl-1)*32*4 + (port-1)*4 + bit
        uint32_t val = 2 * 32 * 4 + (11 + port) * 4 + 2;
        if (port < 4) {
            addr = port + 0x404012 + 0x4000000;
        } else {
            addr = port + 0x404032 + 0x4000000;
        }
        // Register: VTSS_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG(dev):SGPIO_TO_SD_SEL(val)
        (void)inst->iface.reg_write(0, addr, val);
    }

    /* Turn on the Status LED to RED */
    mesa_gpio_direction_set(NULL, 0, STATUSLED_G_GPIO, true);
    mesa_gpio_direction_set(NULL, 0, STATUSLED_R_GPIO, true);
    inst->api.meba_status_led_set(inst, MEBA_LED_TYPE_FRONT, MEBA_LED_COLOR_RED);

}

static mesa_bool_t port_activity(meba_inst_t inst,
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

static const board_func_t board_funcs[] = {
    [BOARD_TYPE_SPARX5_EMULATION] = {
        .board_init = fa_emul_board_init,
        .init_port  = fa_emul_init_port,
    },
    [BOARD_TYPE_SPARX5_PCB125] = {
        .board_init = fa_pcb125_board_init,
        .init_port  = fa_pcb125_init_port,
    },
    [BOARD_TYPE_SPARX5_PCB134] = {
        .board_init = fa_pcb134_board_init,
        .init_port  = fa_pcb134_init_port,
    },
    [BOARD_TYPE_SPARX5_PCB135] = {
        .board_init = fa_pcb135_board_init,
        .init_port  = fa_pcb135_init_port,
    },
};

static mesa_bool_t get_sfp_status(meba_inst_t inst,
                                  mesa_port_no_t port_no,
                                  mesa_sgpio_port_data_t *data,
                                  sfp_signal_t sfp)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t           sgpio_port = PORT_2_SGPIO_PORT(board, port_no);

    // SW_WA_PCB134
    // Due to a hardware bug in PCB134, all SGPIOs in group 2
    // are shifted to the left by 1 bit, so p31b0 is p31b1,
    // p31b1 is p31b2 and p31b2 is p32b0.
    // Since there is no p32, we are enabling one more port
    // in the SGPIO port map, thus shifting all SGPIOs by 3 bits
    // to the right and p32b0 is now accessible at p31b0.
    if (sfp == SFP_DETECT) {
        if (board->type == BOARD_TYPE_SPARX5_PCB134) {
            return !data[sgpio_port - 1].value[2]; // The SFP detect signal is inverted
        } else {
            return !data[sgpio_port].value[1]; // The SFP detect signal is inverted
        }
    } else if (sfp == SFP_FAULT) {
        if (board->type == BOARD_TYPE_SPARX5_PCB134) {
            return data[sgpio_port].value[0];
        } else {
            return data[sgpio_port].value[2];
        }
    } else if (sfp == SFP_LOS) {
        if (board->type == BOARD_TYPE_SPARX5_PCB134) {
            return data[sgpio_port - 1].value[1];
        } else {
            return data[sgpio_port].value[0];
        }
    } else {
        T_E(inst, "Unknown signal");
    }
    return false;
}


static mesa_rc fa_phy_event_enable(meba_inst_t inst,
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
                T_E(inst, "mesa_phy_event_enable_set = %d, port_no %d", rc, port_no);
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
        case BOARD_TYPE_SPARX5_PCB134:
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

static uint32_t fa_capability(meba_inst_t inst, int cap)
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
            return board->type != BOARD_TYPE_SPARX5_EMULATION;
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
        case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET:
            return false;
        case MEBA_CAP_CPU_PORTS_COUNT:
            return board->ls1046 ? 1 : 0;
        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc fa_port_entry_get(meba_inst_t inst,
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

static mesa_rc fa_sensor_get(meba_inst_t inst,
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

static mesa_rc fa_sfp_i2c_xfer(meba_inst_t inst,
                                mesa_port_no_t port_no,
                                mesa_bool_t write,
                                uint8_t i2c_addr,
                                uint8_t addr,
                                uint8_t *data,
                                uint8_t cnt,
                                mesa_bool_t word_access)
{
    mesa_rc            rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t           board_port = PORT_2_BOARD_PORT(board, port_no);

    T_N(inst, "Called");

    if (write) {    // cnt ignored
        uint8_t i2c_data[3];
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        rc = inst->iface.i2c_write(board_port, i2c_addr, i2c_data, 3);
    } else {
        rc = inst->iface.i2c_read(board_port, i2c_addr, addr, data, cnt);
    }

    T_D(inst, "i2c %s port %d - address 0x%02x:0x%02x, %d bytes return %d", write ? "write" : "read", board_port, i2c_addr, addr, cnt, rc);
    return rc;
}

static mesa_rc fa_sfp_insertion_status_get(meba_inst_t inst, mesa_port_list_t *present)
{
    mesa_rc                rc = MESA_RC_OK;
    meba_board_state_t     *board = INST2BOARD(inst);
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];

    T_N(inst, "Called");
    mesa_port_list_clear(present);

    if ((rc = mesa_sgpio_read(NULL, 0, 2, data)) == MESA_RC_OK) {
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

static mesa_rc fa_sfp_status_get(meba_inst_t inst,
                                  mesa_port_no_t port_no,
                                  meba_sfp_status_t *status)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);

    if (board->type == BOARD_TYPE_SPARX5_PCB134 ||
        board->type == BOARD_TYPE_SPARX5_PCB135) {
        if (port_no < board->port_cnt) {
            status->present  = false;
            status->los      = false;
            status->tx_fault = false;
            if (is_sfp_port(board->port[port_no].map.cap)) {
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
    }
    return rc;
}

// Applies only to SFPs where TxDisable is enabled/disabled
static mesa_rc fa_port_admin_state_set(meba_inst_t inst,
                                        mesa_port_no_t port_no,
                                        const meba_port_admin_state_t *state)
{
    mesa_rc            rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);

    if (board->type == BOARD_TYPE_SPARX5_PCB125) {
        return rc;
    }

    if (board->port[port_no].map.map.miim_controller == MESA_MIIM_CONTROLLER_NONE) {
        mesa_sgpio_conf_t  conf;
        mesa_sgpio_mode_t  sgpio_mode = (state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
        uint32_t           sgpio_port = PORT_2_SGPIO_PORT(board, port_no);

        if ((rc = mesa_sgpio_conf_get(NULL, 0, 2, &conf)) == MESA_RC_OK) {
            // SW_WA_PCB134
            // Due to a hardware bug in PCB134, all SGPIOs in group 2
            // are shifted to the left by 1 bit, so p31b0 is p31b1,
            // p31b1 is p31b2 and p31b2 is p32b0.
            // Since there is no p32, we are enabling one more port
            // in the SGPIO port map, thus shifting all SGPIOs by 3 bits
            // to the right and p32b0 is now accessible at p31b0.
            if (board->type == BOARD_TYPE_SPARX5_PCB134) {
                conf.port_conf[sgpio_port - 1].mode[1] = sgpio_mode; // TxDisable maps to bit 0, SGPIO group 2
            } else {
                conf.port_conf[sgpio_port].mode[0] = sgpio_mode; // TxDisable maps to bit 0, SGPIO group 2
            }
            rc = mesa_sgpio_conf_set(NULL, 0, 2, &conf);
        }
    }

    return rc;
}

static mesa_rc fa_status_led_set(meba_inst_t inst,
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

static mesa_rc fa_port_led_update(meba_inst_t inst,
                                   mesa_port_no_t port_no,
                                   const mesa_port_status_t *status,
                                   const mesa_port_counters_t *counters,
                                   const meba_port_admin_state_t *state)
{
    mesa_rc            rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t           sgpio_group = 0;
    uint32_t           sgpio_port = PORT_2_SGPIO_PORT(board, port_no);
    mesa_sgpio_conf_t  conf;
    mesa_sgpio_mode_t  mode_green = MESA_SGPIO_MODE_OFF, mode_yellow = MESA_SGPIO_MODE_OFF;

    switch (board->type) {
    case BOARD_TYPE_SPARX5_PCB125:
        return MESA_RC_OK;
    case BOARD_TYPE_SPARX5_PCB134:
        if (sgpio_port >= 12 && sgpio_port <= 15) {
            sgpio_group = 0;
        } else if (sgpio_port >= 16 && sgpio_port <= 31) {
            sgpio_group = 1;
        } else {
            return rc;  // NPI LED is controlled through the PHY
        }
        break;
    case BOARD_TYPE_SPARX5_PCB135:
        mode_green = MESA_SGPIO_MODE_ON;
        mode_yellow = MESA_SGPIO_MODE_ON; // mode_green=ON and mode_yellow=ON = Turn OFF
        if (sgpio_port >= 28 && sgpio_port <= 31) {
            // Only LED update for the 4x25G ports
            sgpio_group = 1;
            /* Align actual chip_ports to sgpios */
            if (board->port[port_no].map.map.chip_port == 60) {
                sgpio_port = 30;
            } else if (board->port[port_no].map.map.chip_port == 61) {
                sgpio_port = 31;
            } else if (board->port[port_no].map.map.chip_port == 62) {
                sgpio_port = 29;
            } else {
                sgpio_port = 28; // chip_port == 63
            }
        } else {
            return rc;
        }
        break;
    default:
        return MESA_RC_NOT_IMPLEMENTED;
    }

    T_N(inst, "port(%d): Link - %d", port_no, status->link);

    if (!port_activity(inst, port_no, status)) {
        return rc;
    }
    /* If link then auto update LED */
    if (status->link && state->enable) {
        if (status->speed >= MESA_SPEED_1G) {
            mode_yellow = MESA_SGPIO_MODE_OFF;
            mode_green = MESA_SGPIO_MODE_0_ACTIVITY_INV;
        } else {
            mode_green = MESA_SGPIO_MODE_OFF;
            mode_yellow = MESA_SGPIO_MODE_0_ACTIVITY_INV;
        }
    }
    if ((rc = mesa_sgpio_conf_get(NULL, 0, sgpio_group, &conf)) == MESA_RC_OK) {
        conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_green;
        conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_yellow;
        rc = mesa_sgpio_conf_set(NULL, 0, sgpio_group, &conf);
    }

    return rc;
}

static mesa_rc fa_led_intensity_set(meba_inst_t inst,
                                     mesa_phy_led_intensity intensity)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    return rc;
}

static mesa_rc fa_fan_param_get(meba_inst_t inst,
                                 meba_fan_param_t *param)
{
    T_N(inst, "Called");
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc fa_fan_conf_get(meba_inst_t inst,
                                mesa_fan_conf_t *conf)
{
    T_N(inst, "Called");
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc fa_ptp_rs422_conf_get(meba_inst_t inst,
                                      meba_ptp_rs422_conf_t *conf)
{
    T_N(inst, "Called");
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc fa_reset(meba_inst_t inst, meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;

    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            board->func->board_init(inst);
            break;
        case MEBA_PORT_RESET:
            if (board->type == BOARD_TYPE_SPARX5_PCB135) {
                for (uint32_t port_no = 0; port_no < board->port_cnt; port_no++) {
                    if (port_no % 4 == 0 && (board->port[port_no].map.mac_if == MESA_PORT_INTERFACE_QSGMII)) {
                        if ((rc = mesa_phy_pre_reset(PHY_INST, port_no)) != MESA_RC_OK) {
                            T_E(inst, "Could not pre reset phy %d", port_no);
                        }
                    }
                }
            }
            break;
        case MEBA_PORT_RESET_POST:
            if (board->type == BOARD_TYPE_SPARX5_PCB135) {
                // Release COMA mode (activate Elise phys)
                (void)mesa_phy_post_reset(PHY_INST, 0);
            }
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            (void)fa_status_led_set(inst, MEBA_LED_TYPE_FRONT, MEBA_LED_COLOR_YELLOW);
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
    T_D(inst, "Called - %d - Done", reset);
    return rc;
}

// IRQ Support
static mesa_rc fa_event_enable(meba_inst_t inst,
                                meba_event_t event_id,
                                mesa_bool_t enable)
{
    mesa_rc               rc = MESA_RC_OK;
    meba_board_state_t    *board = INST2BOARD(inst);
    int                   gpio;
    mesa_port_no_t        port_no;

    T_I(inst, "%sable event %d", enable ? "en" : "dis", event_id);

    switch (event_id) {
    case MEBA_EVENT_SYNC:
    case MEBA_EVENT_EXT_SYNC:
    case MEBA_EVENT_EXT_1_SYNC:
    case MEBA_EVENT_CLK_ADJ:
    case MEBA_EVENT_VOE:
        return rc;    // Dummy for now

    case MEBA_EVENT_LOS:
        // Loss Of Signal (SFP)
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            if (is_sfp_port(board->port[port_no].map.cap)) {
                uint32_t sgpio_port = PORT_2_SGPIO_PORT(board, port_no);
                uint32_t hack_bit = 0;
                if (sgpio_port >= MESA_SGPIO_PORTS) {
                    continue;
                }
                T_D(inst, "%sable LOS on port %d GPIO %d", enable ? "en" : "dis", port_no, sgpio_port);
                // Enable LOS events, bit 0
                // SW_WA_PCB134
                // Due to a hardware bug in PCB134, all SGPIOs in group 2
                // are shifted to the left by 1 bit, so p31b0 is p31b1,
                // p31b1 is p31b2 and p31b2 is p32b0.
                // Since there is no p32, we are enabling one more port
                // in the SGPIO port map, thus shifting all SGPIOs by 3 bits
                // to the right and p32b0 is now accessible at p31b0.
                if (board->type == BOARD_TYPE_SPARX5_PCB134) {
                    sgpio_port--;
                    hack_bit = 1;
                }
                if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, sgpio_port, hack_bit, enable)) != MESA_RC_OK) {
                    T_E(inst, "Could not enable event for sgpio #%d", sgpio_port);
                }
            }
        }
        break;

    case MEBA_EVENT_FLNK: // Phy link down event
        rc = fa_phy_event_enable(inst, board, MESA_PHY_LINK_FFAIL_EV, enable);
        break;

    case MEBA_EVENT_PUSH_BUTTON:
        switch (board->type) {
        case BOARD_TYPE_SPARX5_PCB134:
            gpio = 7;
            break;

        default:
            gpio = -1;
        }

        if (gpio >= 0) {
            T_I(inst, "%sable Push_button(GPIO_%d) interrupt", enable ? "en" : "dis", gpio);
            // TBD_FA_IRQ
            //if (mesa_gpio_event_enable(NULL, 0, gpio, enable) != MESA_RC_OK) {
                //T_E(inst, "Could not control event for gpio #%d", gpio);
            //}
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
    uint32_t          bit;
    mesa_bool_t       sgpio_events_bit[3][MESA_SGPIO_PORTS];
    int               handled = 0;

    // Getting SGPIO bit 0 - 2
    for (bit = 0; bit <= 2; bit++) {
        if ((rc = mesa_sgpio_event_poll(NULL, 0, 2, bit, sgpio_events_bit[bit])) != MESA_RC_OK) {
            T_E(inst, "mesa_sgpio_event_poll = %d", rc);
            return rc; // Don't even re-enable SGPIO2 interrupt
        }
    }

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (is_sfp_port(board->port[port_no].map.cap)) {
            mesa_bool_t event_detected = false;
            uint32_t    sgpio_port = PORT_2_SGPIO_PORT(board, port_no);

            if (sgpio_port >= MESA_SGPIO_PORTS) {
                continue;
            }

            for (bit = 0; bit <= 2; bit++) {
                // Check for SFP/SFP+ LOS - bit 0
                // Check MODDET           - bit 1
                // Check TXFAULT          - bit 2
                // SW_WA_PCB134
                // Due to a hardware bug in PCB134, all SGPIOs in group 2
                // are shifted to the left by 1 bit, so p31b0 is p31b1,
                // p31b1 is p31b2 and p31b2 is p32b0.
                // Since there is no p32, we are enabling one more port
                // in the SGPIO port map, thus shifting all SGPIOs by 3 bits
                // to the right and p32b0 is now accessible at p31b0.
                uint32_t hack_bit = bit;
                if (board->type == BOARD_TYPE_SPARX5_PCB134) {
                    if (bit == 2) {
                        hack_bit = 0;
                    } else {
                        sgpio_port--;
                        hack_bit = bit + 1;
                    }
                }
                if (sgpio_events_bit[hack_bit][sgpio_port]) {
                    T_I(inst, "%s IRQ port %d gpio %d", (bit == 0) ? "LOS" : ((bit == 1) ? "MODDET" : "TXFAULT"), port_no, sgpio_port);
                    // Disable the interrupt while handling the event
                    if ((rc = mesa_sgpio_event_enable(NULL, 0, 2, sgpio_port, hack_bit, false)) != MESA_RC_OK) {
                        T_E(inst, "mesa_sgpio_event_enable = %d", rc);
                        // Go on anyway
                    }
                    event_detected = true;
                }
            }

            if (event_detected) {
                // LOS, MODDET and TX_FAULT all share the same interrupt,
                // so some signal notifier needs to be called to ensure
                // that interrupts are re-enabled.
                signal_notifier(MEBA_EVENT_LOS, port_no);
                handled++;
            }
        }
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

static mesa_rc fa_irq_handler(meba_inst_t inst,
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

static mesa_rc fa_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
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

static meba_api_cpu_port_t fa_ls1046_cpu_ports[] =
{
    { 21, "eth0" },
};

// Public Initialize
meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t         inst;
    meba_board_state_t *board;
    mesa_port_no_t      port_no;
    uint32_t            u;
    FILE                *fp;

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

    // Get the type of pcb-board from the application
    if (meba_conf_get_u32(inst, "type", &u) == MESA_RC_OK) {
        board->type = (board_type_t)u;
    }

    // Get the board port count
    if (meba_conf_get_u32(inst, "board_port_cnt", &u) == MESA_RC_OK) {
        board->port_cnt = u;
    } else {
        board->port_cnt = 21;
    }

    // Check for Beaglbone platform
    if ((fp = fopen("/sys/firmware/devicetree/base/model", "r"))) {
        char model[128];
        const char *m = fgets(model, sizeof(model), fp);
        fclose(fp);
        if (m && strstr(model, "BeagleBone")) {
            board->beaglebone = true;
        }
        if (m && strstr(model, "LS1046")) {
            board->ls1046 = true;
        }
    }

    switch (board->type) {
    case BOARD_TYPE_SPARX5_PCB125:
        board->port_cfg = VTSS_BOARD_CONF_4x10G;
        break;
    case BOARD_TYPE_SPARX5_PCB134:
        if (board->port_cnt == 7) {
            board->port_cfg = VTSS_BOARD_CONF_6x10G_NPI;
        } else if (board->port_cnt == 9) {
            board->port_cfg = VTSS_BOARD_CONF_8x25G_NPI;
        } else if (board->port_cnt == 10) {
            board->port_cfg = VTSS_BOARD_CONF_9x10G_NPI;
        } else if (board->port_cnt == 17) {
            board->port_cfg = VTSS_BOARD_CONF_16x10G_NPI;
        } else if (board->port_cnt == 13) {
            board->port_cfg = VTSS_BOARD_CONF_12x10G_NPI;
        } else if (board->port_cnt == 21) {
            board->port_cfg = VTSS_BOARD_CONF_20x10G_NPI;
        } else {
            T_E(inst, "Unknown board (%d) / port count (%d)",board->type,board->port_cnt);
        }
        break;
    case BOARD_TYPE_SPARX5_PCB135:
        if (board->port_cnt == 29) {
            board->port_cfg = VTSS_BOARD_CONF_24x1G_4x10G_NPI;
        } else if (board->port_cnt == 53) {
            board->port_cfg = VTSS_BOARD_CONF_48x1G_4x10G_NPI;
        } else if (board->port_cnt == 57) {
            if (inst->props.target == MESA_TARGET_7552_04 ||
                inst->props.target == MESA_TARGET_7552) {
                board->port_cfg = VTSS_BOARD_CONF_48x1G_8x10G_NPI;
            } else {
                board->port_cfg = VTSS_BOARD_CONF_48x1G_4x10G_4x25G_NPI;
            }
        } else {
            T_E(inst, "Unknown board (%d) / port count (%d)",board->type,board->port_cnt);
        }
        break;
    default:
        T_E(inst, "Unknown PCB type");
        goto error_out;
    }

    // Hook up the local functions in this file
    board->func = &board_funcs[board->type];

    board->port = (fa_port_info_t*) calloc(board->port_cnt, sizeof(fa_port_info_t));
    if (board->port == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    inst->props.board_type = board->type;
    // Fill out port mapping table
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        board->func->init_port(inst, port_no, &board->port[port_no].map);
        switch (board->type) {
        case BOARD_TYPE_SPARX5_PCB125:
            if (board->port_cfg == VTSS_BOARD_CONF_4x10G) {
                    board->port[port_no].board_port = port_no;
                    board->port[port_no].sgpio_port = port_no;
            } else {
                T_E(inst, "Board type (%d) and port_cfg (%d) not supported!", board->type, board->port_cfg);
                goto error_out;
            }
            break;
        case BOARD_TYPE_SPARX5_PCB134:
            if ((board->port_cfg == VTSS_BOARD_CONF_6x10G_NPI) ||
                (board->port_cfg == VTSS_BOARD_CONF_9x10G_NPI) ||
                (board->port_cfg == VTSS_BOARD_CONF_12x10G_NPI) ||
                (board->port_cfg == VTSS_BOARD_CONF_16x10G_NPI) ||
                (board->port_cfg == VTSS_BOARD_CONF_20x10G_NPI)) {
                board->port[port_no].board_port = port_no;
                board->port[port_no].sgpio_port = port_no + 12;
            } else if (board->port_cfg == VTSS_BOARD_CONF_8x25G_NPI) {
                board->port[port_no].board_port = port_no + 12;
                board->port[port_no].sgpio_port = port_no + 24;
            } else {
                T_E(inst, "Board type (%d) and port_cfg (%d) not supported!", board->type, board->port_cfg);
                goto error_out;
            }
            break;
        case BOARD_TYPE_SPARX5_PCB135:
            if (board->port_cfg == VTSS_BOARD_CONF_48x1G_4x10G_4x25G_NPI) {
                board->port[port_no].board_port = port_no;
                if (board->port[port_no].map.map.chip_port >= 60) {
                    board->port[port_no].sgpio_port = board->port[port_no].map.map.chip_port - 32;
                }
            } else {
                T_E(inst, "Board type (%d) and port_cfg (%d) not supported!", board->type, board->port_cfg);
                goto error_out;
            }
            break;
        default:
            T_E(inst, "Board type (%d) not supported!", board->type);
            goto error_out;
        }
        board->port[port_no].activity = true; // Force an LED update
    }
    T_I(inst, "Board: %s, type %d, target %4x, mux %d, %d ports", inst->props.name, board->type, inst->props.target,
        inst->props.mux_mode, board->port_cnt);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = fa_capability;
    inst->api.meba_port_entry_get             = fa_port_entry_get;
    inst->api.meba_reset                      = fa_reset;
    inst->api.meba_sensor_get                 = fa_sensor_get;
    inst->api.meba_sfp_i2c_xfer               = fa_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = fa_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = fa_sfp_status_get;
    inst->api.meba_port_admin_state_set       = fa_port_admin_state_set;
    inst->api.meba_status_led_set             = fa_status_led_set;
    inst->api.meba_port_led_update            = fa_port_led_update;
    inst->api.meba_led_intensity_set          = fa_led_intensity_set;
    inst->api.meba_fan_param_get              = fa_fan_param_get;
    inst->api.meba_fan_conf_get               = fa_fan_conf_get;
    inst->api.meba_irq_handler                = fa_irq_handler;
    inst->api.meba_irq_requested              = fa_irq_requested;
    inst->api.meba_event_enable               = fa_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get         = fa_ptp_rs422_conf_get;
    inst->api_synce                           = meba_synce_get();
    inst->api_tod                             = meba_tod_get();
    inst->api_cpu_port                        = board->ls1046 ? fa_ls1046_cpu_ports : NULL;
    return inst;

error_out:
    free(inst);
    return NULL;
}
