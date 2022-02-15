// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <microchip/ethernet/board/api.h>

#include "meba_aux.h"
#include "meba_generic.h"
#include "meba_common.h"

#define STATUSLED_G_GPIO 12
#define STATUSLED_R_GPIO 13
#define AQR_RESET 19
#define PHY_ID_GPY241 0xDC00

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

#define VTSS_MSLEEP(m) usleep((m) * 1000)

static const mesa_fan_conf_t fan_spec = {
    .fan_pwm_freq = MESA_FAN_PWM_FREQ_20HZ,    // 20MHz
    .fan_low_pol = 0,                          // active low
    .fan_open_col = true,                      // Open collector
    .type = MESA_FAN_3_WIRE_TYPE,              // 3-wire
    .ppr = 2,                                  // 2 PPR
};

static const meba_ptp_rs422_conf_t pcb134_rs422_conf = {
    .gpio_rs422_1588_mstoen = 49,
    .gpio_rs422_1588_slvoen = 48,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 3,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_2,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3
};

static const meba_ptp_rs422_conf_t other_rs422_conf = {
    .gpio_rs422_1588_mstoen = -1,
    .gpio_rs422_1588_slvoen = -1,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 3,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_2,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3
};

static const meba_event_t init_int_source_id[MESA_CAP_TS_IO_CNT] = {MEBA_EVENT_PTP_PIN_0, MEBA_EVENT_PTP_PIN_1, MEBA_EVENT_PTP_PIN_2, MEBA_EVENT_PTP_PIN_3};

static const uint32_t pin_conf_pcb134[MESA_CAP_TS_IO_CNT] = {
(MEBA_PTP_IO_CAP_PIN_OUT), // enabling as PIN_IN is causing continuous interrupt generation.
(MEBA_PTP_IO_CAP_PIN_OUT), // used by MEBA_CAP_ONE_PPS_INT_ID
(MEBA_PTP_IO_CAP_TIME_IF_IN | MEBA_PTP_IO_CAP_PIN_IN),
(MEBA_PTP_IO_CAP_TIME_IF_OUT)
};

static const uint32_t pin_conf_pcb135[MESA_CAP_TS_IO_CNT] = {
(MEBA_PTP_IO_CAP_PIN_OUT), // Need to validate PIN_IN
(MEBA_PTP_IO_CAP_PIN_OUT), // used by MEBA_CAP_ONE_PPS_INT_ID
(MEBA_PTP_IO_CAP_TIME_IF_IN | MEBA_PTP_IO_CAP_PIN_IN),
(MEBA_PTP_IO_CAP_TIME_IF_OUT)
};

#define PCB134_GPIO_FUNC_INFO_SIZE 4
static const mesa_gpio_func_info_t pcb134_gpio_func_info[PCB134_GPIO_FUNC_INFO_SIZE] = {
    {.gpio_no = 8, //MESA_GPIO_FUNC_PTP_0
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = 9, //MESA_GPIO_FUNC_PTP_1
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = 24, //MESA_GPIO_FUNC_PTP_2
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = 25, //MESA_GPIO_FUNC_PTP_3
     .alt = MESA_GPIO_FUNC_ALT_0},
};

#define PCB135_GPIO_FUNC_INFO_SIZE 4
static const mesa_gpio_func_info_t pcb135_gpio_func_info[PCB135_GPIO_FUNC_INFO_SIZE] = {
    {.gpio_no = 8, //MESA_GPIO_FUNC_PTP_0
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = 9, //MESA_GPIO_FUNC_PTP_1
     .alt = MESA_GPIO_FUNC_ALT_0},
    {.gpio_no = 54, //MESA_GPIO_FUNC_PTP_2
     .alt = MESA_GPIO_FUNC_ALT_1},
    {.gpio_no = 25, //MESA_GPIO_FUNC_PTP_3
     .alt = MESA_GPIO_FUNC_ALT_0},
};

#define PORT_2_BOARD_PORT(board, p) (board->port[p].board_port)
#define PORT_2_SGPIO_PORT(board, p) (board->port[p].sgpio_port)
#define PORT_2_SGPIO_BIT(board, p) (board->port[p].sgpio_bit)

static const meba_aux_rawio_t rawio = {
    .base = 0x4000000,
    .gcb = 0x1,
    .miim = {
        .status = 0xAC+0,
        .cmd    = 0xAC+2,
        .data   = 0xAC+3,
        .cfg    = 0xAC+4,
    },
    .gpio = {
        .alt_0  = 0x10,
        .alt1_0 = 0x12,
    }
};

/* --------------------------- Board specific ------------------------------- */
static void fa_gpy241_detect(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    u16 id = 0, id2 = 0;

    mebaux_miim_rd(inst, &rawio, 0, 0, 0x3, &id);
    mebaux_miim_rd(inst, &rawio, 0, 1, 0x3, &id2);

    if (id == 0x0670 || id2 == 0x0670) {
        // Found Elise Phy which means PCB135 version 1-2
        board->gpy241_present = FALSE;
    } else {
        // Did not find Elise Phy which means PCB135 version 3
        // Note Indy / Maxlinear phy's are in reset at this point
        board->gpy241_present = TRUE;
        /* Default to SGMII mode */
        board->gpy241_usxgmii_mode = FALSE;
    }
}


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
                entry->mac_if              = MESA_PORT_INTERFACE_SGMII_CISCO;
                entry->cap                 = (MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
                entry->cap                 &= ~MEBA_PORT_CAP_SFP_DETECT; // No SFP detection
            } else {
                // 25G ports
                entry->map.chip_port       = port_no - 4 + 56; // 56-63(25G)
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = MESA_BW_10G;
                if ((port_no == 4) || (port_no == 5)) {
                    entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
                } else {
                    entry->mac_if              = MESA_PORT_INTERFACE_SGMII_CISCO;
                }
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

static void update_entry(meba_inst_t inst, meba_port_entry_t *entry, mesa_port_interface_t if_type, mesa_internal_bw_t bw, uint32_t chip_port)
{
    meba_board_state_t *board = INST2BOARD(inst);

    if (if_type == MESA_PORT_INTERFACE_QSGMII) {
        entry->map.chip_port       = chip_port;
        entry->map.miim_addr       = chip_port % 24;
        entry->map.miim_controller = chip_port < 24 ? MESA_MIIM_CONTROLLER_0 : MESA_MIIM_CONTROLLER_1;
        entry->map.max_bw          = MESA_BW_1G;
        entry->mac_if              = MESA_PORT_INTERFACE_QSGMII;
        entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
    } else if  (if_type == MESA_PORT_INTERFACE_SFI || if_type == MESA_PORT_INTERFACE_SGMII_CISCO) {
        entry->map.chip_port       = chip_port;
        if ((board->type == BOARD_TYPE_SPARX5_PCB135) && (entry->map.chip_port >= 56 && entry->map.chip_port < 60)) {
            // Aquantia Phy
            entry->map.miim_addr       = chip_port - 56;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_3;
            entry->cap  = (MEBA_PORT_CAP_COPPER_10G | MEBA_PORT_CAP_5G_FDX | MEBA_PORT_CAP_2_5G_TRI_SPEED_FDX | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_NO_FORCE);
            entry->cap &= ~MEBA_PORT_CAP_SD_ENABLE; // Signal detect is disabled when connected to AQR phys
        } else {
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_5G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
            if (entry->map.chip_port >= 56 && entry->map.chip_port < 64) {
                // 100-FX mode not supported on 25G SerDes, so removing the capability.
                entry->cap &= ~MEBA_PORT_CAP_100M_FDX;
            }
            if (bw == MESA_BW_25G) {
                entry->cap             |= MEBA_PORT_CAP_25G_FDX;
            }
        }
        entry->map.max_bw          = bw;
        entry->mac_if              = if_type;
        if (board->type == BOARD_TYPE_SPARX5_PCB134) {
            // Due to a hardware bug in PCB134, the SFP SD is connected to the wrong SGPIO bit.
            // The 'SD to SGPIO' needs remapping as follows (for dev12-15, dev48-63):
            // dev12 --> [SGPIO2, port 11, bit 1],
            // ...
            // dev63 --> [SGPIO2, port 30, bit 1]
            entry->map.sd_map.action   = MESA_SD_SGPIO_MAP_ENABLE;
            entry->map.sd_map.group    = 2;
            entry->map.sd_map.port     = chip_port < 16 ? (11 + (chip_port - 12)) : 11 + (chip_port - 48 + 4);
            entry->map.sd_map.bit      = 1;
        } else if (board->type == BOARD_TYPE_SPARX5_PCB135) {
            // Per default the device SD is mapped to SGPIO1
            // On PCB135 the SFP SD is connected to SGPIO2.
            // Therefore a new mapping is needed (for dev12-15, dev48-63):
            // dev12 --> [SGPIO2, port 12, bit 0],
            // ...
            // dev63 --> [SGPIO2, port 31, bit 0]
            entry->map.sd_map.action   = MESA_SD_SGPIO_MAP_ENABLE;
            entry->map.sd_map.group    = 2;
            entry->map.sd_map.port     = chip_port < 16 ? (12 + (chip_port - 12)) : 12 + (chip_port - 48 + 4);
            entry->map.sd_map.bit      = 0;
        }
    } else if (if_type == MESA_PORT_INTERFACE_QXGMII) {
        // GPY-241 Phy strapped into QXGMII mode connected to S25 (Serdes25G_0)
        entry->map.chip_port       = chip_port;
        entry->mac_if              = if_type;
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_3; // 4xGPY-241 on PCB-135v4
        entry->map.miim_addr       = chip_port == 8 ? 3 : chip_port == 24 ? 0 : chip_port == 40 ? 2 : 1;
        entry->map.max_bw          = bw;
        entry->cap  = (MEBA_PORT_CAP_2_5G_TRI_SPEED_COPPER | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_NO_FORCE | MEBA_PORT_CAP_10M_FDX);
        entry->cap &= ~MEBA_PORT_CAP_SD_ENABLE; // Signal detect is disabled when connected to GPY phys
    } else if (if_type == MESA_PORT_INTERFACE_SGMII || if_type == MESA_PORT_INTERFACE_SGMII_2G5) {
        entry->map.chip_port       = chip_port;
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_3;
        entry->map.miim_addr       = chip_port == 64 ? 28 : (chip_port - 56); // NPI or GPY-241 x 4
        entry->map.max_bw          = bw;
        entry->mac_if              = if_type;
        entry->cap                 = chip_port == 64 ? MEBA_PORT_CAP_TRI_SPEED_COPPER : (MEBA_PORT_CAP_2_5G_TRI_SPEED_COPPER | MEBA_PORT_CAP_10M_FDX);
    }
    entry->cap &= ~MEBA_PORT_CAP_SD_INTERNAL; // Signal detect (LOS) comes from SFP module (and not from Serdes)
    entry->cap &= ~MEBA_PORT_CAP_SD_HIGH;     // The polarity is inversed
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
    case VTSS_BOARD_CONF_10x10G_4x25G_NPI:
        if (port_no < 10) {
            // 10G ports, chip ports: 12-15,48-53.
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_10G, port_no < 4 ? port_no + 12 : port_no + 44);
        } else if (port_no < 14) {
            // 25G ports, chip ports: 56-59.
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_25G, 56 + port_no - 10);
        } else if (port_no == 14) {
            // NPI port, chip port: 64.
            update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
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
    mesa_port_interface_t if_type;
    uint32_t chip_port;
    mesa_internal_bw_t bw;

    switch (board->port_cfg) {
    case VTSS_BOARD_CONF_24x1G_4x10G_NPI:
        if (port_no < 24) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_QSGMII, MESA_BW_1G, port_no);
            entry->poe_chip_port       = entry->map.chip_port % 24; // Each PD69200 controller controls 24 ports.
            entry->poe_support         = true;
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
            entry->poe_chip_port       = entry->map.chip_port % 24; // Each PD69200 controller controls 24 ports.
            entry->poe_support         = true;
        } else if (port_no < 52) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, MESA_BW_10G, 56 + port_no - 48); // 10G: 56-59
        } else if (port_no == 52) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
        break;
    case VTSS_BOARD_CONF_48x1G_4x10G_4x25G_NPI:
    case VTSS_BOARD_CONF_48x1G_8x10G_NPI:
        if (port_no < 48) {
            if (board->gpy241_present && board->gpy241_usxgmii_mode && (port_no % 16 == 8)) {
                // QXGMII Test mode, this will disable QSGMII ports
                if_type = MESA_PORT_INTERFACE_QXGMII; // chip_ports 8,24,40,56 -> SD25
                bw = MESA_BW_2G5;
            } else {
                if_type = MESA_PORT_INTERFACE_QSGMII;
                bw = MESA_BW_1G;
            }
            update_entry(inst, entry, if_type, bw, port_no);
            entry->poe_chip_port       = entry->map.chip_port % 24; // Each PD69200 controller controls 24 ports.
            entry->poe_support         = true;
        } else if (port_no < 52) {
            chip_port = 56 + port_no - 48;
            if (board->gpy241_present && board->gpy241_usxgmii_mode && (chip_port % 16 == 8)) {
                if_type = MESA_PORT_INTERFACE_QXGMII; // chip_ports 8,24,40,56 -> SD25
                bw = MESA_BW_2G5;
            } else if (board->gpy241_present && board->gpy241_usxgmii_mode) {
                if_type = MESA_PORT_INTERFACE_NO_CONNECTION;
                bw = MESA_BW_1G;
            } else if (board->gpy241_present) {
                if_type = MESA_PORT_INTERFACE_SGMII_2G5;
                bw = MESA_BW_2G5;
            } else {
                if_type = MESA_PORT_INTERFACE_SFI;
                bw = MESA_BW_10G;
            }
            update_entry(inst, entry, if_type, bw, chip_port); // 10G: 56-59
        } else if (port_no < 56) {
            mesa_internal_bw_t bw = board->port_cfg == VTSS_BOARD_CONF_48x1G_4x10G_4x25G_NPI ? MESA_BW_25G : MESA_BW_10G;
            update_entry(inst, entry, MESA_PORT_INTERFACE_SFI, bw, 56 + port_no - 48); // 25G: 60-63
        } else if (port_no == 56) {
            update_entry(inst, entry, MESA_PORT_INTERFACE_SGMII, MESA_BW_1G, 64);
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    break;

    default:
        T_E(inst, "Board type (%d) not supported!", board->type);
    }
    if (entry->map.chip_port >= 56 && entry->map.chip_port <= 59) {
        entry->cap &= ~MEBA_PORT_CAP_SFP_DETECT; // No SFP detection on Aquantia connected ports
    }
}

static void fa_pcb125_board_init(meba_inst_t inst)
{

}

static void fa_pcb135_board_init(meba_inst_t inst)
{
    mesa_sgpio_conf_t conf;
    uint32_t port, gpio_no;
    meba_board_state_t *board = INST2BOARD(inst);

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
    /* and Port LED function indicator (p24-p27)  */
    if (mesa_sgpio_conf_get(NULL, 0, 1, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;

        for (port = 24; port < 32; port++) {
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
        for (port = 28; port < 32; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].int_pol_high[0] = true;        // LOS interrupt is active high (input)
            conf.port_conf[port].int_pol_high[2] = true;        // TX_FAULT interrupt is active high (input)
            conf.port_conf[port].mode[0] = MESA_SGPIO_MODE_OFF; // TXDisable is enabled through fa_port_admin_state_set() (output)
            conf.port_conf[port].mode[1] = MESA_SGPIO_MODE_ON;  // Ratesel0 always eanbled (output)
            conf.port_conf[port].mode[2] = MESA_SGPIO_MODE_ON;  // Ratesel1 always eanbled (output)
        }
        conf.port_conf[0].enabled  = true; // I2C
        conf.port_conf[16].enabled = true; // I2C
        conf.port_conf[17].enabled = true; // Elise Phy
        conf.port_conf[18].enabled = true; // Elise Phy
        conf.port_conf[17].int_pol_high[0] = false; // INTR for QSGMII Elise Phy 0-1 (8 instances)
        conf.port_conf[17].int_pol_high[1] = false; // INTR for QSGMII Elise Phy 2-3 (8 instances)
        conf.port_conf[17].int_pol_high[2] = false; // INTR for QSGMII Elise Phy 4-5 (8 instances)
        conf.port_conf[18].int_pol_high[0] = false; // INTR for QSGMII Elise Phy 6-7 (8 instances)
        conf.port_conf[18].int_pol_high[1] = false; // INTR for QSGMII Elise Phy 8-9 (8 instances)
        conf.port_conf[18].int_pol_high[2] = false; // INTR for QSGMII Elise Phy 10-11 (8 instances)
        (void)mesa_sgpio_conf_set(NULL, 0, 2, &conf);
    }
    /* Turn on the Status LED to Red */
    mesa_gpio_direction_set(NULL, 0, STATUSLED_G_GPIO, true);
    mesa_gpio_direction_set(NULL, 0, STATUSLED_R_GPIO, true);
    inst->api.meba_status_led_set(inst, MEBA_LED_TYPE_FRONT, MEBA_LED_COLOR_RED);

    /* Aquantia (or Board) Reset GPIO */
    mesa_gpio_direction_set(NULL, 0, AQR_RESET, true);

    (void) mesa_gpio_write(NULL, 0, AQR_RESET, false);
    VTSS_MSLEEP(1);
    // Take Aquantia (or Board) Phy out of reset
    (void) mesa_gpio_write(NULL, 0, AQR_RESET, true);

    if (board->gpy241_present) {
        // Delay for gpy241 phy coming out of reset
        VTSS_MSLEEP(1000);
    } else {
        // Delay for AQR phy coming out of reset
        VTSS_MSLEEP(50);
    }

    /* We must increase the drive strength for MIIM/MDIO bus 3  */
    /* with HSIOWRAP:GPIO_CFG:G_DS[52-53] = 2.                  */
    /* Currently unsupported in the API therefore direct write  */
    mesa_reg_write(NULL, 0, 0x4142038, 0xE);
    mesa_reg_write(NULL, 0, 0x4142039, 0xE);
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
    /* p0 -> D64, 8-11 -> Led-tower, p12-15 -> D12-D15  */
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        for (port = 8; port < 16; port++) {
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
        /* conf.port_conf[0].mode[0] = MESA_SGPIO_MODE_OFF; */
        /* conf.port_conf[31].mode[1] = MESA_SGPIO_MODE_OFF; */
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

    if (sgpio_port >= MESA_SGPIO_PORTS) {
        T_E(inst, "Invalid port %d, sgpio_port %d", port_no, sgpio_port);
        return false;
    }
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
                                    vtss_phy_event_t phy_event,
                                    mesa_bool_t enable)
{
    mesa_port_no_t     port_no;
    mesa_rc            rc = MESA_RC_OK;

    T_D(inst, "%sable phy event %d on all ports", enable ? "en" : "dis", phy_event);

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (is_phy_port(board->port[port_no].map.cap)) {
            // We do not need/expect any event configuration to be done for AQR/ML.
            // Currently the feature is not implemented in the MEPA layer, and
            // MEBA will therefore return MESA_RC_NOT_IMPLEMENTED.
            rc = meba_phy_event_enable_set(inst, port_no, phy_event, enable);
            if (rc == MESA_RC_OK) {
                T_I(inst, "%sable phy event %d on phy:%d", enable ? "en" : "dis", phy_event, port_no);
            }
            if (rc == MESA_RC_OK || rc == MESA_RC_NOT_IMPLEMENTED) {
                continue;
            } else {
                T_E(inst, "meba_phy_event_enable = %d, port %d", rc, port_no);
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
        case BOARD_TYPE_SPARX5_PCB135:
            if (gpio_events[2]) {
                if ((rc = mesa_gpio_event_enable(NULL, 0, 2, false)) != MESA_RC_OK) {
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


static mesa_rc kr_irq2port(meba_inst_t inst, mesa_irq_t chip_irq, mesa_port_no_t *port_no)
{
    meba_board_state_t    *board = INST2BOARD(inst);
    mesa_rc               rc = MESA_RC_ERROR;
    uint32_t              chip_port;

    // Convert chip IRQs to to chip ports
    // and check if the chip port exists in the port map.
    switch (chip_irq) {
    case MESA_IRQ_KR_SD10G_0: chip_port = 12;  break;
    case MESA_IRQ_KR_SD10G_1: chip_port = 13;  break;
    case MESA_IRQ_KR_SD10G_2: chip_port = 14;  break;
    case MESA_IRQ_KR_SD10G_3: chip_port = 15;  break;
    case MESA_IRQ_KR_SD10G_4: chip_port = 48;  break;
    case MESA_IRQ_KR_SD10G_5: chip_port = 49;  break;
    case MESA_IRQ_KR_SD10G_6: chip_port = 50;  break;
    case MESA_IRQ_KR_SD10G_7: chip_port = 51;  break;
    case MESA_IRQ_KR_SD10G_8: chip_port = 52;  break;
    case MESA_IRQ_KR_SD10G_9: chip_port = 53;  break;
    case MESA_IRQ_KR_SD10G_10: chip_port = 54; break;
    case MESA_IRQ_KR_SD10G_11: chip_port = 55; break;
    case MESA_IRQ_KR_SD10G_12: chip_port = 56; break;
    case MESA_IRQ_KR_SD10G_13: chip_port = 57; break;
    case MESA_IRQ_KR_SD10G_14: chip_port = 58; break;
    case MESA_IRQ_KR_SD10G_15: chip_port = 59; break;
    case MESA_IRQ_KR_SD10G_16: chip_port = 60; break;
    case MESA_IRQ_KR_SD10G_17: chip_port = 61; break;
    case MESA_IRQ_KR_SD10G_18: chip_port = 62; break;
    case MESA_IRQ_KR_SD10G_19: chip_port = 63; break;
    default: rc = MESA_RC_ERROR;
    }

    for (mesa_port_no_t p = 0; p < board->port_cnt; p++) {
        if (board->port[p].map.map.chip_port == chip_port) {
            *port_no = p;
            return MESA_RC_OK;
        }
    }

    return rc;
}

/* ---------------------------   Exposed API  ------------------------------- */

static uint32_t fa_capability(meba_inst_t inst, int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_POE:
            return board->type == BOARD_TYPE_SPARX5_PCB135;   // Only PCB135
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
            return (board->type == BOARD_TYPE_SPARX5_PCB135) && (!board->gpy241_present);
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
            return 0;
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
            return 0;
        case MEBA_CAP_BOARD_HAS_PCB135_CPLD:
            return (board->type == BOARD_TYPE_SPARX5_PCB135) && (!board->gpy241_present);
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
            if (board->type == BOARD_TYPE_SPARX5_PCB134) {
                meba_synce_clock_hw_id_t dpll_type;

                if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK) &&
                    (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772)) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET:
            return false;
        case MEBA_CAP_POE_BT:
            return board->type == BOARD_TYPE_SPARX5_PCB135;   // Only PCB135
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
    meba_board_state_t *board = INST2BOARD(inst);

    T_N(inst, "Called %d:%d", type, six);

    if (type == MEBA_SENSOR_BOARD_TEMP) {
        rc = mesa_temp_sensor_get(NULL, &temp);
        // EMC1182 needs more debug
        /* rc = inst->iface.i2c_read(0, 0x4C, 0, data, 10); */
        /* printf("data: %d, %d, %d \n",data[0],data[1],data[2]); */
    } else if (type == MEBA_SENSOR_PORT_TEMP) {
        if (board->type == BOARD_TYPE_SPARX5_PCB134) {
            rc = mesa_temp_sensor_get(NULL, &temp);
        } else if (board->type == BOARD_TYPE_SPARX5_PCB135) {
            if (board->port[six].map.mac_if == MESA_PORT_INTERFACE_QSGMII) {
                rc = vtss_phy_chip_temp_get(PHY_INST, six, &temp);
            } else {
                rc = mesa_temp_sensor_get(NULL, &temp);
            }
        }
    }

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

//    if (board->port[port_no].map.map.miim_controller == MESA_MIIM_CONTROLLER_NONE || port_no == 52) {
        mesa_sgpio_conf_t  conf;
        mesa_sgpio_mode_t  sgpio_mode = (state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
        uint32_t           sgpio_port = PORT_2_SGPIO_PORT(board, port_no);

        if (sgpio_port >= MESA_SGPIO_PORTS) {
            T_E(inst, "Invalid port %d, sgpio_port %d", port_no, sgpio_port);
            return MESA_RC_ERROR;
        }
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
//    }

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

static void gpy_led_wrm(meba_inst_t inst, uint16_t ctrl, uint16_t miim, uint16_t mmd, uint16_t addr,  uint16_t value, uint16_t mask)
{
    uint16_t val;
    meba_board_state_t *board = INST2BOARD(inst);

    if (miim > 3) {
        T_E (inst, "Illegal MIIM address %d",miim);
        return;
    }
    val = board->gpy241_leds[miim];
    val = ((val & ~mask) | (value & mask));
    mesa_mmd_write(NULL, 0, ctrl, miim, mmd, addr, val);
    board->gpy241_leds[miim] = val; // need to cache it as the phy FW will overwrite the LED reg
}

#define GPY_LED_OFF                0xfd00
#define GPY_LED_OFF_MASK           0xff00
#define GPY_LED_1G_LINK_ON         0xf001 // Left green
#define GPY_LED_100M_LINK_ON       0xf004 // right green
#define GPY_LED_2G5_LINK_ON        0xfD02 // right orange
#define GPY_LED_2G5_LINK_MASK      0xff02
#define GPY_LED_CONTROL            0,27   // LED control register mmd,addr
#define GPY_LED_DEFAULT            0xfd00
#define GPY_LED_DEFAULT_MASK       0xff00

/*
   PHYLED0: Left Green     10m/100M speed : Default phy control incl. blinking when traffic
   PHYLED1: Right Orange   2G5 speed      : Manual control, no blinking (due to board issue)
   PHYLED2: Right Green    1G speed       : Default phy control incl. blinking when traffic

   Note: Due to board layout issue PHYLED1 (orange) is controlled from the neighbour phy (miim addr +/-1).
         The LED control is manual and traffic blinking is off
         Another issue is that each time the phy link changes the phy FW will force the LEDs to auto.
         Workaround for that is to cache the LED status instead of reading it from the phy.
*/

static void fa_gpy_led_update(meba_inst_t inst, mesa_port_no_t port_no, const mesa_port_status_t *status)
{
    meba_board_state_t *board = INST2BOARD(inst);
    meba_port_entry_t  *entry = &board->port[port_no].map;
    uint16_t           phyled_0_2_value = GPY_LED_OFF, neighbor_addr;
    uint16_t           phyled_1_value = GPY_LED_OFF;
    uint16_t           phyled_0_2_mask = 0;

    if (entry->map.chip_port < 56 || entry->map.chip_port > 59) {
        return; /* Not GPY phy connected ports */
    }

    if (status->link) {
        switch (status->speed) {
        case MESA_SPEED_10M:
        case MESA_SPEED_100M:
        case MESA_SPEED_1G:
            phyled_0_2_value = GPY_LED_DEFAULT;
            phyled_0_2_mask  = GPY_LED_DEFAULT_MASK;
            phyled_1_value   = GPY_LED_OFF;
            break;
        case MESA_SPEED_2500M:
            phyled_0_2_value = GPY_LED_OFF;
            phyled_0_2_mask  = GPY_LED_OFF_MASK;
            phyled_1_value   = GPY_LED_2G5_LINK_ON;
            break;
        default:
            break;
        }
    }
    /* Update 10/100/1G LEDs */
    gpy_led_wrm(inst, entry->map.miim_controller, entry->map.miim_addr, GPY_LED_CONTROL, phyled_0_2_value, phyled_0_2_mask);

    if (entry->map.miim_addr == 0 || entry->map.miim_addr == 2) {
        neighbor_addr = entry->map.miim_addr + 1;
    } else {
        neighbor_addr = entry->map.miim_addr - 1;
    }
    /* Update 2.5G LED from the neighbour phy */
    gpy_led_wrm(inst, entry->map.miim_controller, neighbor_addr, GPY_LED_CONTROL, phyled_1_value, GPY_LED_2G5_LINK_MASK);
}

static void fa_aqr_led_update(meba_inst_t inst, mesa_port_no_t port_no, const mesa_port_status_t *status)
{
#define AQR_LED_OFF             0x0000
#define AQR_LED_5G_LINK_ON      0x8000
#define AQR_LED_2G5_LINK_ON     0x4000
#define AQR_LED_ON              0x0100
#define AQR_LED_10G_LINK_ON     0x0080
#define AQR_LED_1G_LINK_ON      0x0040
#define AQR_LED_100M_LINK_ON    0x0020
#define AQR_LED_CONNECTING      0x0010
#define AQR_LED_RX_ACT          0x0008
#define AQR_LED_TX_ACT          0x0004
#define AQR_LED_ACT_STRETCH_100 0x0003
#define AQR_LED_ACT_STRETCH_60  0x0002
#define AQR_LED_ACT_STRETCH_28  0x0001
#define AQR_LED_ACT_STRETCH_0   AQR_LED_OFF

    meba_board_state_t *board = INST2BOARD(inst);
    meba_port_entry_t  *entry = &board->port[port_no].map;
    uint16_t           led0_value = AQR_LED_OFF, led1_value = AQR_LED_OFF, led2_value = AQR_LED_OFF;

    if (entry->map.chip_port >= 56 && entry->map.chip_port < 60) {
        if (status->link) {
            /* LED0/LED2: Right
               LED1: Left

               If LED1 is HIGH, then left LED will lit GREEN.
               If LED0 is LOW & LED2 is HIGH, then right LED will lit GREEN.
               If LED0 is HIGH & LED2 is LOW, then right LED will lit YELLOW.

               L_LED   R_RED(Active)
               100M   GREEN   OFF
               1G     OFF     GREEN
               2.5G   GREEN   GREEN
               5G     OFF     YELLOW
               10G    GREEN   YELLOW
            */

            switch (status->speed) {
            case MESA_SPEED_100M:
                led0_value = AQR_LED_OFF;
                led1_value = AQR_LED_ON | AQR_LED_RX_ACT | AQR_LED_TX_ACT | AQR_LED_ACT_STRETCH_60;
                led2_value = AQR_LED_OFF;
                break;
            case MESA_SPEED_1G:
            case MESA_SPEED_2500M:
            case MESA_SPEED_5G:
            case MESA_SPEED_10G:
                led0_value = AQR_LED_ON | AQR_LED_RX_ACT | AQR_LED_TX_ACT | AQR_LED_ACT_STRETCH_60;
                led1_value = AQR_LED_OFF;
                led2_value = AQR_LED_OFF;
                break;
            default:
                led0_value = AQR_LED_OFF;
                led1_value = AQR_LED_OFF;
                led2_value = AQR_LED_OFF;
                break;
            }
        }
        mesa_mmd_write(NULL, 0, entry->map.miim_controller, entry->map.miim_addr, 0x1e, 0xc430, led0_value);
        mesa_mmd_write(NULL, 0, entry->map.miim_controller, entry->map.miim_addr, 0x1e, 0xc431, led1_value);
        mesa_mmd_write(NULL, 0, entry->map.miim_controller, entry->map.miim_addr, 0x1e, 0xc432, led2_value);
    }
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
    uint32_t           board_port = PORT_2_BOARD_PORT(board, port_no);
    uint32_t           led_tower = 0;
    mesa_sgpio_conf_t  conf;
    mesa_sgpio_mode_t  mode_green = MESA_SGPIO_MODE_OFF, mode_yellow = MESA_SGPIO_MODE_OFF, mode_green_tower = MESA_SGPIO_MODE_OFF;
    mesa_sgpio_mode_t  mode_yellow_tower = MESA_SGPIO_MODE_OFF;

    T_N(inst, "port(%d): Link - %d", port_no, status->link);

    if (!port_activity(inst, port_no, status)) {
        return rc;
    }

    switch (board->type) {
    case BOARD_TYPE_SPARX5_PCB125:
        return MESA_RC_OK;
    case BOARD_TYPE_SPARX5_PCB134:
        if (sgpio_port >= 12 && sgpio_port <= 15) {
            sgpio_group = 0;
        } else if (sgpio_port >= 16 && sgpio_port <= 31) {
            sgpio_group = 1;
        } else {
            // NPI LED is controlled through the PHY
            return MESA_RC_OK;
        }
        break;
    case BOARD_TYPE_SPARX5_PCB135:
        if (!board->gpy241_present && (board_port >= 48) && (board_port <= 51)) {
            // 4x10G Cu ports
            // If AQR then update AQR LED
            (void)fa_aqr_led_update(inst, port_no, status);
            return MESA_RC_OK;
        } else if (board->gpy241_present && (board_port >= 48) && (board_port <= 51)) {
            (void)fa_gpy_led_update(inst, port_no, status);
            return MESA_RC_OK;
        }
        if (sgpio_port >= 28 && sgpio_port <= 31) {
            // Only LED update for the 4x25G ports
            sgpio_group = 1;
            mode_green  = MESA_SGPIO_MODE_ON; // Turn off default
            mode_yellow = MESA_SGPIO_MODE_ON; // Turn off default
            led_tower = sgpio_port - 4;  // The Front end LED tower is offset by 4
        } else {
            // PHY LEDs are controlled through the PHYs
            return MESA_RC_OK;
        }
        break;
    default:
        return MESA_RC_NOT_IMPLEMENTED;
    }

    /* If link then auto update LED */
    if (status->link && state->enable) {
        if (status->speed >= MESA_SPEED_1G) {
            mode_yellow = MESA_SGPIO_MODE_OFF;
            mode_green = MESA_SGPIO_MODE_0_ACTIVITY_INV;
            mode_green_tower = MESA_SGPIO_MODE_ON; // Auto update does not apply to tower
        } else {
            mode_green = MESA_SGPIO_MODE_OFF;
            mode_yellow = MESA_SGPIO_MODE_0_ACTIVITY_INV;
        }
        mode_yellow_tower = mode_yellow;
    }
    if ((rc = mesa_sgpio_conf_get(NULL, 0, sgpio_group, &conf)) == MESA_RC_OK) {
        conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_green;
        conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_yellow;
        if (led_tower > 0) {
            // Copy the port LED to front end LED tower
            conf.port_conf[led_tower].mode[LED_GREEN] = mode_green_tower;
            conf.port_conf[led_tower].mode[LED_YELLOW] = mode_yellow_tower;
        }
        rc = mesa_sgpio_conf_set(NULL, 0, sgpio_group, &conf);
    }

    return rc;
}

static mesa_rc fa_led_intensity_set(meba_inst_t inst,
                                    vtss_phy_led_intensity intensity)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    meba_board_state_t *board = INST2BOARD(inst);

    if (fa_capability(inst, MEBA_CAP_LED_DIM_SUPPORT)) {
        for (uint32_t port_no = 0; port_no < board->port_cnt; port_no++) {
            if (board->port[port_no].map.mac_if == MESA_PORT_INTERFACE_QSGMII) {
                rc = vtss_phy_led_intensity_set(PHY_INST, port_no, intensity);
            }
        }
    }
    return rc;
}

static mesa_rc fa_fan_param_get(meba_inst_t inst,
                                 meba_fan_param_t *param)
{
    T_N(inst, "Called");
    param->start_time = 100;
    param->start_level = 60;
    param->min_pwm = 30;
    return MESA_RC_OK;
}

static mesa_rc fa_fan_conf_get(meba_inst_t inst,
                                mesa_fan_conf_t *conf)
{
    T_N(inst, "Called");
    meba_board_state_t *board = INST2BOARD(inst);
    *conf = *board->fan_spec;
    return MESA_RC_OK;
}

static mesa_rc fa_ptp_rs422_conf_get(meba_inst_t inst,
                                      meba_ptp_rs422_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called");
    if (board->type == BOARD_TYPE_SPARX5_PCB134 || board->type == BOARD_TYPE_SPARX5_PCB135) {
        *conf = pcb134_rs422_conf;
    } else {
        *conf = other_rs422_conf;
    }
    return rc;
}

static mesa_rc fa_ptp_external_io_conf_get(meba_inst_t inst, uint32_t io_pin, meba_ptp_io_cap_t *const board_assignment, meba_event_t *const source_id)
{
    meba_board_state_t *board = INST2BOARD(inst);

    if (io_pin >= MESA_CAP_TS_IO_CNT) {
        return MESA_RC_ERROR;
    }
    if (board->type == BOARD_TYPE_SPARX5_PCB135)
    {
        *board_assignment = pin_conf_pcb135[io_pin];
    } else {
        *board_assignment = pin_conf_pcb134[io_pin]; //default
    }
    *source_id = init_int_source_id[io_pin];
    return MESA_RC_OK;
}

// The Serdes Tx equalizer settings depends on the board layout and can vary from port to port.
// The API calls this function after applying general Serdes settings and updates the Tx equalizer.
static mesa_rc fa_serdes_tap_get(meba_inst_t inst, mesa_port_no_t port_no,
                                 mesa_port_speed_t speed, mesa_port_serdes_tap_enum_t tap, uint32_t *const ret_val)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t chip_port = board->port[port_no].map.map.chip_port;
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;

    if (board->type == BOARD_TYPE_SPARX5_PCB134) {
        if (speed == MESA_SPEED_10G && tap == MESA_SERDES_POST_CURSOR) {
            if (port_no < 4) {
                *ret_val = 0x14; // 10G Serdes, chip ports 12-15.
                rc = MESA_RC_OK;
            } else if (port_no < 8) {
                *ret_val = 0xD;  // 10G Serdes, chip ports 49-51.
                rc = MESA_RC_OK;
            } else if (port_no < 12) {
                *ret_val = 0xA;  // 10G Serdes, chip ports 52-55.
                rc = MESA_RC_OK;
            } else if ((chip_port >= 56) && (63 >= chip_port)) {
                *ret_val = 0x66; // 25G Serdes, chip ports 56-63.
                rc = MESA_RC_OK;
            }
        } else if (speed == MESA_SPEED_5G && tap == MESA_SERDES_POST_CURSOR) {
            if (port_no < 4) {
                *ret_val = 0x14; // 10G Serdes, chip ports 12-15.
                rc = MESA_RC_OK;
            } else if (port_no < 8) {
                *ret_val = 0xD;  // 10G Serdes, chip ports 49-51.
                rc = MESA_RC_OK;
            } else if (port_no < 12) {
                *ret_val = 0xA;  // 10G Serdes, chip ports 52-55.
                rc = MESA_RC_OK;
            } else if ((chip_port >= 56) && (63 >= chip_port)) {
                *ret_val = 0x6; // 25G Serdes, chip ports 56-63.
                rc = MESA_RC_OK;
            }
        } else if (speed == MESA_SPEED_2500M && tap == MESA_SERDES_POST_CURSOR) {
            if (port_no < 4) {
                *ret_val = 0x8; // 10G Serdes, chip ports 12-15.
                rc = MESA_RC_OK;
            } else if (port_no < 12) {
                *ret_val = 0x4;  // 10G Serdes, chip ports 49-55.
                rc = MESA_RC_OK;
            } else if ((chip_port >= 56) && (63 >= chip_port)) {
                *ret_val = 0; // 25G Serdes, chip ports 56-63.
                rc = MESA_RC_OK;
            }
        }
    } else if (board->type == BOARD_TYPE_SPARX5_PCB135) {
        // TX EQ settings not needed
    }

    return rc;
}


static mesa_rc fa_gpio_func_info_get(meba_inst_t inst,
                                     mesa_gpio_func_t gpio_func,  mesa_gpio_func_info_t *info)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called");
    if (board->type == BOARD_TYPE_SPARX5_PCB134) {
        if (gpio_func < PCB134_GPIO_FUNC_INFO_SIZE) {
            *info = pcb134_gpio_func_info[gpio_func];
        } else {
            T_E(inst, "Invalid gpio_func %u", gpio_func);
            rc = MESA_RC_ERROR;
        }
    } else if (board->type == BOARD_TYPE_SPARX5_PCB135) {
        if (gpio_func < PCB135_GPIO_FUNC_INFO_SIZE) {
            *info = pcb135_gpio_func_info[gpio_func];
        } else {
            T_E(inst, "Invalid gpio_func %u", gpio_func);
            rc = MESA_RC_ERROR;
        }
    } else {
        memset(info, 0, sizeof(*info));
        T_E(inst, "Unknown Board Type %u", board->type);
        rc = MESA_RC_ERROR;
    }
    return rc;
}

static mesa_rc fa_reset(meba_inst_t inst, meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;
    mesa_sgpio_conf_t  conf;

    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            board->func->board_init(inst);
            break;
        case MEBA_PORT_RESET:
            if (board->type == BOARD_TYPE_SPARX5_PCB135 && !board->gpy241_present) {
                for (uint32_t port_no = 0; port_no < board->port_cnt; port_no++) {
                    if (port_no % 4 == 0 && (board->port[port_no].map.mac_if == MESA_PORT_INTERFACE_QSGMII)) {
                        if ((rc = vtss_phy_pre_reset(PHY_INST, port_no)) != MESA_RC_OK) {
                            T_E(inst, "Could not pre reset phy %d", port_no);
                        }
                    }
                }
            }
            break;
        case MEBA_PORT_RESET_POST:
            if (board->type == BOARD_TYPE_SPARX5_PCB135 && !board->gpy241_present) {
                // Release COMA mode (activate Elise phys)
                (void)vtss_phy_post_reset(PHY_INST, 0);

                // PCB135 does not use reversed MDI pair for AQR as the driver defaults to.
                for (uint32_t port_no = 0; port_no < board->port_cnt; port_no++) {
                    if (board->port[port_no].map.map.chip_port >= 56 && board->port[port_no].map.map.chip_port < 60) {
                        mesa_mmd_write(NULL, 0, board->port[port_no].map.map.miim_controller, board->port[port_no].map.map.miim_addr, 0x1, 0xe400, 6);
                    }
                }
            }
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            (void)fa_status_led_set(inst, MEBA_LED_TYPE_FRONT, MEBA_LED_COLOR_YELLOW);
            break;
        case MEBA_PORT_LED_INITIALIZE:
            if (board->type == BOARD_TYPE_SPARX5_PCB134) {
                // Turn off the Port LEDs
                if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
                    for (uint32_t port = 8; port < 16; port++) {
                        conf.port_conf[port].enabled = 1;
                        conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_OFF;
                        conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF;
                    }
                    (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
                }
                if (mesa_sgpio_conf_get(NULL, 0, 1, &conf) == MESA_RC_OK) {
                    for (uint32_t port = 16; port < 32; port++) {
                        conf.port_conf[port].enabled = 1;
                        conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_OFF;
                        conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF;
                    }
                    (void)mesa_sgpio_conf_set(NULL, 0, 1, &conf);
                }
            }

            if (board->type == BOARD_TYPE_SPARX5_PCB135 && board->gpy241_present) {
                // Indy LED setup to fix a board layout issue
                mepa_gpio_conf_t gpio_conf;
                gpio_conf.mode = MEPA_GPIO_MODE_LED_LINK1000_ACTIVITY;
                gpio_conf.led_num = MEPA_LED0;
                for (uint32_t port_no = 0; port_no < 48; port_no++) {
                    gpio_conf.gpio_no = 12;
                    meba_phy_gpio_mode_set(inst, port_no, &gpio_conf);
                    gpio_conf.gpio_no = 14;
                    meba_phy_gpio_mode_set(inst, ++port_no, &gpio_conf);
                    gpio_conf.gpio_no = 18;
                    meba_phy_gpio_mode_set(inst, ++port_no, &gpio_conf);
                    gpio_conf.gpio_no = 20;
                    meba_phy_gpio_mode_set(inst, ++port_no, &gpio_conf);
                }

                gpio_conf.mode = MEPA_GPIO_MODE_LED_LINK10_100_ACTIVITY;
                gpio_conf.led_num = MEPA_LED1;
                for (uint32_t port_no = 0; port_no < 48; port_no++) {
                    gpio_conf.gpio_no = 11;
                    meba_phy_gpio_mode_set(inst, port_no, &gpio_conf);
                    gpio_conf.gpio_no = 13;
                    meba_phy_gpio_mode_set(inst, ++port_no, &gpio_conf);
                    gpio_conf.gpio_no = 17;
                    meba_phy_gpio_mode_set(inst, ++port_no, &gpio_conf);
                    gpio_conf.gpio_no = 19;
                    meba_phy_gpio_mode_set(inst, ++port_no, &gpio_conf);
                }
            }
            break;
        case MEBA_FAN_INITIALIZE:
            rc = mesa_fan_controller_init(NULL, board->fan_spec);
            if (rc == MESA_RC_OK) {
                mesa_sgpio_conf_t  conf;
                if ((rc = mesa_sgpio_conf_get(NULL, 0, 2, &conf)) == MESA_RC_OK) {
                    if (board->type == BOARD_TYPE_SPARX5_PCB134) {
                        conf.port_conf[0].enabled = true;
                        conf.port_conf[0].mode[1] =  MESA_SGPIO_MODE_OFF; // Note - FAN1_ENA is active low - See schematic.
                        conf.port_conf[0].mode[2] =  MESA_SGPIO_MODE_OFF; // Note - FAN2_ENA is active low - See schematic.
                    } else {
                        conf.port_conf[18].enabled = true;
                        conf.port_conf[18].mode[0] =  MESA_SGPIO_MODE_OFF; // Note - FAN1_ENA is active low - See schematic.
                        conf.port_conf[18].mode[1] =  MESA_SGPIO_MODE_OFF; // Note - FAN2_ENA is active low - See schematic.
                    }
                    rc = mesa_sgpio_conf_set(NULL, 0, 2, &conf);
                }
            }
            mesa_fan_cool_lvl_set(NULL, 0xFF); // Set default level to maximum
            break;
        case MEBA_SENSOR_INITIALIZE:
            (void)mesa_temp_sensor_init(NULL, true);
            break;
        case MEBA_INTERRUPT_INITIALIZE:
            break;
        case MEBA_SYNCE_DPLL_INITIALIZE:
            break;
        case MEBA_POE_INITIALIZE:
            if (board->type == BOARD_TYPE_SPARX5_PCB135) {
                mesa_sgpio_conf_t  conf;
                if ((rc = mesa_sgpio_conf_get(NULL, 0, 2, &conf)) == MESA_RC_OK) {
                    conf.port_conf[16].enabled = true;
                    conf.port_conf[16].mode[0] =  MESA_SGPIO_MODE_ON;
                    conf.port_conf[16].mode[1] =  MESA_SGPIO_MODE_ON;
                    rc = mesa_sgpio_conf_set(NULL, 0, 2, &conf);
                }
            }
            break;
        case MEBA_PHY_INITIALIZE:
            inst->phy_devices = (mepa_device_t **)&board->phy_devices;
            inst->phy_device_cnt = board->port_cnt;
            meba_phy_driver_init(inst);
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
    mesa_ptp_event_type_t ptp_event;

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
                if ((rc = mesa_sgpio_event_enable(NULL, 0, 2, sgpio_port, hack_bit, enable)) != MESA_RC_OK) {
                    T_E(inst, "Could not enable event for sgpio #%d", sgpio_port);
                }
            }
        }
        break;

    case MEBA_EVENT_FLNK: // Phy link down event
        rc = fa_phy_event_enable(inst, board, VTSS_PHY_LINK_FFAIL_EV, enable);
        if (board->type == BOARD_TYPE_SPARX5_PCB135) {
            uint32_t sgpio_port_old = 0xff;
            uint32_t sgpio_bit_old  = 0xff;
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (is_phy_port(board->port[port_no].map.cap)) {
                    uint32_t sgpio_port = PORT_2_SGPIO_PORT(board, port_no);
                    uint32_t sgpio_bit  = PORT_2_SGPIO_BIT(board, port_no);
                    if (sgpio_port >= MESA_SGPIO_PORTS) {
                        continue;
                    }
                    if (sgpio_port == sgpio_port_old &&
                        sgpio_bit  == sgpio_bit_old) {
                        continue;
                    }
                    if ((rc += mesa_sgpio_event_enable(NULL, 0, 2, sgpio_port, sgpio_bit, enable)) != MESA_RC_OK) {
                        T_E(inst, "Could not enable event for sgpio #%d", sgpio_port);
                    }
                    sgpio_port_old = sgpio_port;
                    sgpio_bit_old = sgpio_bit;
                }
            }
        }
        break;

    case MEBA_EVENT_PUSH_BUTTON:
        switch (board->type) {
        case BOARD_TYPE_SPARX5_PCB134:
        case BOARD_TYPE_SPARX5_PCB135:
            gpio = 2;
            break;

        default:
            gpio = -1;
        }

        if (gpio >= 0) {
            T_I(inst, "%sable Push_button(GPIO_%d) interrupt", enable ? "en" : "dis", gpio);
            // TBD_FA_IRQ
            if (mesa_gpio_event_enable(NULL, 0, gpio, enable) != MESA_RC_OK) {
                T_E(inst, "Could not control event for gpio #%d", gpio);
            }
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

    case MEBA_EVENT_KR:
        // Handled in kr application
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
        } else if (is_phy_port(board->port[port_no].map.cap)) {
            uint32_t sgpio_port = PORT_2_SGPIO_PORT(board, port_no);
            uint32_t sgpio_bit  = PORT_2_SGPIO_BIT(board, port_no);
            if (sgpio_port >= MESA_SGPIO_PORTS) {
                continue;
            }
            if (sgpio_events_bit[sgpio_bit][sgpio_port]) {
                // Check for Cu Phy events
                if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                    handled++;
                }
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

static mesa_rc kr_handler(meba_inst_t inst,
                          meba_board_state_t *board,
                          mesa_irq_t chip_irq,
                          meba_event_signal_t signal_notifier)
{
    mesa_port_no_t port_no = 0;
    if (kr_irq2port(inst, chip_irq, &port_no) != MESA_RC_OK) {
        return MESA_RC_OK; // Not used in the current board config
    }

    signal_notifier(MEBA_EVENT_KR, port_no);
    return MESA_RC_OK;
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
        case MESA_IRQ_PUSH_BUTTON:
            signal_notifier(MEBA_EVENT_PUSH_BUTTON, 0);
            return MESA_RC_OK;
        case MESA_IRQ_SGPIO2:
            return sgpio2_handler(inst, board, signal_notifier);
       case MESA_IRQ_EXT0:
           return ext0_handler(inst, board, signal_notifier);
       case MESA_IRQ_KR_SD10G_0:
       case MESA_IRQ_KR_SD10G_1:
       case MESA_IRQ_KR_SD10G_2:
       case MESA_IRQ_KR_SD10G_3:
       case MESA_IRQ_KR_SD10G_4:
       case MESA_IRQ_KR_SD10G_5:
       case MESA_IRQ_KR_SD10G_6:
       case MESA_IRQ_KR_SD10G_7:
       case MESA_IRQ_KR_SD10G_8:
       case MESA_IRQ_KR_SD10G_9:
       case MESA_IRQ_KR_SD10G_10:
       case MESA_IRQ_KR_SD10G_11:
       case MESA_IRQ_KR_SD10G_12:
       case MESA_IRQ_KR_SD10G_13:
       case MESA_IRQ_KR_SD10G_14:
       case MESA_IRQ_KR_SD10G_15:
       case MESA_IRQ_KR_SD10G_16:
       case MESA_IRQ_KR_SD10G_17:
       case MESA_IRQ_KR_SD10G_18:
       case MESA_IRQ_KR_SD10G_19:
           return kr_handler(inst, board, chip_irq, signal_notifier);
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
        case MESA_IRQ_PUSH_BUTTON:
        case MESA_IRQ_SGPIO2:
        case MESA_IRQ_EXT0:
        case MESA_IRQ_KR_SD10G_0:
        case MESA_IRQ_KR_SD10G_1:
        case MESA_IRQ_KR_SD10G_2:
        case MESA_IRQ_KR_SD10G_3:
        case MESA_IRQ_KR_SD10G_4:
        case MESA_IRQ_KR_SD10G_5:
        case MESA_IRQ_KR_SD10G_6:
        case MESA_IRQ_KR_SD10G_7:
        case MESA_IRQ_KR_SD10G_8:
        case MESA_IRQ_KR_SD10G_9:
        case MESA_IRQ_KR_SD10G_10:
        case MESA_IRQ_KR_SD10G_11:
        case MESA_IRQ_KR_SD10G_12:
        case MESA_IRQ_KR_SD10G_13:
        case MESA_IRQ_KR_SD10G_14:
        case MESA_IRQ_KR_SD10G_15:
        case MESA_IRQ_KR_SD10G_16:
        case MESA_IRQ_KR_SD10G_17:
        case MESA_IRQ_KR_SD10G_18:
        case MESA_IRQ_KR_SD10G_19:
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
    meba_inst_t        inst;
    meba_board_state_t *board;
    mesa_port_no_t     port_no;
    char               buf[32];
    uint32_t           u;
    int                i;
    FILE               *fp;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate public state and set the board name and target.
    // The name and target are fetched from the application (through MESA capabilities)
    if ((inst = meba_state_alloc(callouts,
                                 "SparX-5",          // Default name
                                 MESA_TARGET_7558TSN,// Default target
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state. 'board' provides the private info from this file.
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    // Get the chip ID
    if (meba_conf_get_hex(inst, "chip_id", &i) == MESA_RC_OK) {
        inst->props.target = (mesa_target_type_t) i;
    }

    // Get the board type from the application
    if (inst->iface.conf_get("pcb", buf, sizeof(buf), NULL) == MESA_RC_OK) {
        mesa_switch_bw_t bw = mesa_capability(NULL, MESA_CAP_MISC_SWITCH_BW);
        T_D(inst, "Board Type is %s", buf);

        // Assign the board type to the board name
        // as we do not have a separate variable to store the board name.
        strncpy(inst->props.name, buf, sizeof(inst->props.name));
        if (strstr(buf, "pcb134")) {
            board->type = BOARD_TYPE_SPARX5_PCB134;
            // Default port count, in case it cannot be read out
            // in the next step
            switch (bw) {
                case MESA_SWITCH_BW_64:
                    board->port_cnt = 7;
                    break;
                case MESA_SWITCH_BW_90:
                    board->port_cnt = 10;
                    break;
                case MESA_SWITCH_BW_128:
                    board->port_cnt = 13;
                    break;
                case MESA_SWITCH_BW_160:
                    board->port_cnt = 17;
                    break;
                default:
                    board->port_cnt = 21;
            }

        } else if (strstr(buf, "pcb135")) {
            board->type = BOARD_TYPE_SPARX5_PCB135;
            // Default port count, in case it cannot be read out
            // in the next step
            switch (bw) {
                case MESA_SWITCH_BW_64:
                    board->port_cnt = 29;
                    break;
                case MESA_SWITCH_BW_90:
                    board->port_cnt = 53;
                    break;
                default:
                    board->port_cnt = 57;
                    break;
            }
        }
    }

    // Get the board port count
    if (meba_conf_get_u32(inst, "pcb_var", &u) == MESA_RC_OK) {
        T_D(inst, "Board port count is %d", u);
        board->port_cnt = u;
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
        } else if (board->port_cnt == 15) {
            board->port_cfg = VTSS_BOARD_CONF_10x10G_4x25G_NPI;
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
            if (inst->props.target == MESA_TARGET_7552TSN ||
                inst->props.target == MESA_TARGET_7552) {
                board->port_cfg = VTSS_BOARD_CONF_48x1G_8x10G_NPI;
            } else {
                board->port_cfg = VTSS_BOARD_CONF_48x1G_4x10G_4x25G_NPI;
            }
        } else {
            T_E(inst, "Unknown board (%d) / port count (%d)",board->type,board->port_cnt);
        }
        // Configure GPIOs for MIIM/MDI
        for (i = 56; i < 60; i++) {
            mebaux_gpio_mode_set(inst, &rawio, i, MESA_GPIO_ALT_0);
        }
        for (i = 52; i < 54; i++) {
            mebaux_gpio_mode_set(inst, &rawio, i, MESA_GPIO_ALT_1);
        }
        // Detect gpy241 / PCB135v4 board
        fa_gpy241_detect(inst);
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
                if (port_no < board->port_cnt - 1) {
                    board->port[port_no].board_port = port_no;
                    board->port[port_no].sgpio_port = port_no + 12;
                } else {
                    // NPI port is always board port 20,
                    // the last port in the physical board map.
                    board->port[port_no].board_port = 20;
                    // NPI port has no SPGIO, so assigning an out-of-range value.
                    board->port[port_no].sgpio_port = MESA_SGPIO_PORTS;
                }
            } else if (board->port_cfg == VTSS_BOARD_CONF_8x25G_NPI) {
                if (port_no < board->port_cnt - 1) {
                    board->port[port_no].board_port = port_no + 12;
                    board->port[port_no].sgpio_port = port_no + 24;
                } else {
                    // NPI port is always board port 20,
                    // the last port in the physical board map.
                    board->port[port_no].board_port = 20;
                    // NPI port has no SPGIO, so assigning an out-of-range value.
                    board->port[port_no].sgpio_port = MESA_SGPIO_PORTS;
                }
            } else if (board->port_cfg == VTSS_BOARD_CONF_10x10G_4x25G_NPI) {
                if (port_no < 10) {
                    board->port[port_no].board_port = port_no;
                    board->port[port_no].sgpio_port = port_no + 12;
                } else if (port_no < 14) {
                    board->port[port_no].board_port = port_no + 2;
                    board->port[port_no].sgpio_port = port_no + 14;
                } else {
                    // NPI port is always board port 20,
                    // the last port in the physical board map.
                    board->port[port_no].board_port = 20;
                    // NPI port has no SPGIO, so assigning an out-of-range value.
                    board->port[port_no].sgpio_port = MESA_SGPIO_PORTS;
                }

            } else {
                T_E(inst, "Board type (%d) and port_cfg (%d) not supported!", board->type, board->port_cfg);
                goto error_out;
            }
            break;
        case BOARD_TYPE_SPARX5_PCB135:
            if ((board->port_cfg == VTSS_BOARD_CONF_24x1G_4x10G_NPI) ||
                (board->port_cfg == VTSS_BOARD_CONF_48x1G_4x10G_NPI)) {
                if (port_no < board->port_cnt - 5) {
                    // 1G Cu ports, either 24x or 48x
                    board->port[port_no].board_port = port_no;
                    // 1 SGPIO interrupt is assigned to 2 phys (8 ports)
                    if (port_no < 8) {
                        board->port[port_no].sgpio_port = 17;
                        board->port[port_no].sgpio_bit = 0;
                    } else if (port_no < 16) {
                        board->port[port_no].sgpio_port = 17;
                        board->port[port_no].sgpio_bit = 1;
                    } else if (port_no < 24) {
                        board->port[port_no].sgpio_port = 17;
                        board->port[port_no].sgpio_bit = 2;
                    } else if (port_no < 32) {
                        board->port[port_no].sgpio_port = 18;
                        board->port[port_no].sgpio_bit = 0;
                    } else if (port_no < 40) {
                        board->port[port_no].sgpio_port = 18;
                        board->port[port_no].sgpio_bit = 1;
                    } else if (port_no < 48) {
                        board->port[port_no].sgpio_port = 18;
                        board->port[port_no].sgpio_bit = 2;
                    } else {
                        board->port[port_no].sgpio_port = MESA_SGPIO_PORTS;
                    }
                } else if (port_no < board->port_cnt - 1) {
                    // 4x10G Cu ports
                    // These are physical ports 48-51
                    board->port[port_no].board_port = 48 + port_no - (board->port_cnt - 5);
                    // No SGPIO port available, so assigning an out-of-range value.
                    board->port[port_no].sgpio_port = MESA_SGPIO_PORTS;
                } else {
                    // NPI port is always board port 56,
                    // the last port in the physical board map.
                    board->port[port_no].board_port = 56;
                    // NPI port has no SPGIO, so assigning an out-of-range value.
                    board->port[port_no].sgpio_port = MESA_SGPIO_PORTS;
                }
            } else if ((board->port_cfg == VTSS_BOARD_CONF_48x1G_8x10G_NPI) ||
                       (board->port_cfg == VTSS_BOARD_CONF_48x1G_4x10G_4x25G_NPI)) {
                board->port[port_no].board_port = port_no;
                if ((port_no >= board->port_cnt - 5) && (port_no < board->port_cnt - 1)) {
                    // 4x25G SFP ports
                    // These are physical ports 52-55
                    board->port[port_no].sgpio_port = board->port[port_no].map.map.chip_port - 32;
                } else {
                    // 1 SGPIO interrupt is assigned to 2 vtss/microchip phys (8 port)
                    if (port_no < 8) {
                        board->port[port_no].sgpio_port = 17;
                        board->port[port_no].sgpio_bit = 0;
                    } else if (port_no < 16) {
                        board->port[port_no].sgpio_port = 17;
                        board->port[port_no].sgpio_bit = 1;
                    } else if (port_no < 24) {
                        board->port[port_no].sgpio_port = 17;
                        board->port[port_no].sgpio_bit = 2;
                    } else if (port_no < 32) {
                        board->port[port_no].sgpio_port = 18;
                        board->port[port_no].sgpio_bit = 0;
                    } else if (port_no < 40) {
                        board->port[port_no].sgpio_port = 18;
                        board->port[port_no].sgpio_bit = 1;
                    } else if (port_no < 48) {
                        board->port[port_no].sgpio_port = 18;
                        board->port[port_no].sgpio_bit = 2;
                    } else if (port_no < 52 && is_phy_port(board->port[port_no].map.cap) && board->gpy241_present) {
                         // SGPIO interrupt is assigned to the GPY241 Phy (note that the PCB135 needs to be ECO'ed for this)
                        board->port[port_no].sgpio_port = 16;
                        board->port[port_no].sgpio_bit = 2;
                    } else {
                        board->port[port_no].sgpio_port = MESA_SGPIO_PORTS;
                    }
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
    board->fan_spec = &fan_spec;
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
    inst->api.meba_gpio_func_info_get         = fa_gpio_func_info_get;
    inst->api_synce                           = meba_synce_get();
    inst->api_tod                             = meba_tod_get();
    inst->api_poe                             = meba_poe_get();
    inst->api_cpu_port                        = board->ls1046 ? fa_ls1046_cpu_ports : NULL;
    inst->api.meba_serdes_tap_get             = fa_serdes_tap_get;
    inst->api.meba_ptp_external_io_conf_get   = fa_ptp_external_io_conf_get;
    return inst;

error_out:
    free(inst);
    return NULL;
}
