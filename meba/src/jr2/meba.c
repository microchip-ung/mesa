// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <microchip/ethernet/board/api.h>
#include <microchip/ethernet/phy/api.h>

#include "meba_aux.h"
#include "meba_generic.h"

/* Status LEDs are the same on all boards (!) */
#define STATUSLED_G_GPIO 12
#define STATUSLED_R_GPIO 13

/* Device Identification defined in RN-N2103_AQR407_408_409_Silicon_FW_RevNotes_v0.8 */
#define PHY_ID_AQR407_B0      0xB552

/* Device Identification defined in RN-N3103_AQR411_412_411C_412C_Silicon_FW_RevNotes_v0.1 */
#define PHY_ID_AQR411_A0_ES1  0xB6E0
#define PHY_ID_AQR411_B0      0xB6E2
#define PHY_ID_AQR412_A0_ES1  0xB6F0
#define PHY_ID_AQR412_B0      0xB6F2
#define PHY_ID_AQR411C_A0_ES1 0xB700
#define PHY_ID_AQR412C_A0_ES1 0xB710

#define PORTS_MAX 53

#define PHY_ID_GPY241 0xDC00

/** \brief Number of Jaguar2 PTP pins, that can be used as 1PPS or clock output/input. */
#define VTSS_TS_IO_ARRAY_SIZE       4

#define VTSS_MSLEEP(m) usleep((m) * 1000)

/* JR2 Ref board port configurations  */
typedef enum {
    VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI,
    VTSS_BOARD_CONF_24x2G5_2xSFI_NPI,
    VTSS_BOARD_CONF_16x2G5_4xSFI_NPI,
    VTSS_BOARD_CONF_20x1G_4x2G5_2xSFI_NPI,
    VTSS_BOARD_CONF_DEFAULT_VENICE_1G_MODE,
    VTSS_BOARD_CONF_LAST
} vtss_board_port_cfg_t;

typedef struct {
    meba_port_entry_t    map;
    mesa_port_counters_t cnt;
    mesa_port_status_t   status;
    mesa_bool_t          activity;
    mesa_bool_t          ts_phy;
} jr2_port_info_t;

/* 10G PHY detection data */
typedef struct  {
    mesa_port_no_t  port_no;       /* Port number (debugging) */
    uint8_t         miim_addr[2];  /* MIIM address */
    mesa_bool_t     miim_found[2]; /* MIIM address */
    meba_port_cap_t cap;           /* Port capability */
} jr2_10g_detect_t;

/* Malibu GPIO Channel Tx Disable and Aggregated Interrupts mapping */
typedef struct
{
    vtss_gpio_10g_no_t gpio_tx_dis;   /* Tx Disable GPIO number */
    vtss_gpio_10g_no_t gpio_aggr_int; /* Aggregated Interrupt-0 GPIO number */
    vtss_gpio_10g_no_t gpio_i2c_clk;  /* GPIO Pin selection as I2C_CLK for I2C communication with SFP  */
    vtss_gpio_10g_no_t gpio_i2c_dat;  /* GPIO Pin selection as I2C_DATA for I2C communication with SFP */
    vtss_gpio_10g_no_t gpio_virtual;  /* Per port Virtual GPIO number,for internal GPIO usage          */
    vtss_gpio_10g_no_t gpio_sfp_mod_det;  /* GPIO Pin selection as SFP module detect              */
    uint32_t           aggr_intrpt;   /* Channel interrupt bitmask */
} jr2_malibu_gpio_port_map_t;

/* Jaguar NPI chip port */
#define JR2_NPI_CHIP_PORT 48

/* 10g sgpio irq */
#define PHY10G_SGPIO_GROUP  2
#define PHY10G_SGPIO_PORT   24
#define PHY10G_SGPIO_BIT    2

/* SGPIO LED mapping */
typedef struct {
    uint8_t port;
    uint8_t bit;
} sgpio_mapping_t;

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

typedef enum {
    BOARD_TYPE_SERVAL2_NID,
    BOARD_TYPE_JAGUAR2_CU48,
    BOARD_TYPE_JAGUAR2,
    BOARD_TYPE_JAGUAR2_AQR,
} board_type_t;

typedef struct {
    void (*board_init)(meba_inst_t inst);
    void (*init_port)(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry);
    meba_port_led_update_t led_update;
} board_func_t;

typedef struct meba_board_state {
    board_type_t          type;
    int                   port_cnt;
    vtss_board_port_cfg_t port_cfg;
    const mesa_fan_conf_t *fan_spec;
    jr2_port_info_t       *port;
    const board_func_t    *func;
    jr2_10g_detect_t      detect;
    mesa_bool_t           malibu_present;
    uint16_t              aqr_sb_present; //PCB126
    uint16_t              gpy241_sb_present; // UNG 8277
    uint16_t              venice_present; //Stores the model value otherwise 0
    int                   phy10g_ts_cnt;

    mepa_device_t        *phy_devices[PORTS_MAX];
} meba_board_state_t;

static const mesa_fan_conf_t fan_conf = {
    .fan_pwm_freq = MESA_FAN_PWM_FREQ_25KHZ,   // 25kHz
    .fan_low_pol = 0,                          // active low
    .fan_open_col = true,                      // Open collector
    .type = MESA_FAN_3_WIRE_TYPE,              // 3-wire
    .ppr = 2,                                  // 2 PPR
};

static const meba_aux_rawio_t rawio = {
    .gcb = 0x01,
    .miim = {
        .status = 0x32+0,
        .cmd    = 0x32+2,
        .data   = 0x32+3,
        .cfg    = 0x32+4,
    },
    .gpio = {
        .alt_0  = 0x1e,
        .alt1_0 = 0x20,
    }
};

static const meba_ptp_rs422_conf_t serval2_nid_rs422_conf = {
    .gpio_rs422_1588_mstoen = 29,
    .gpio_rs422_1588_slvoen = 28,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 3,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_2,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3
};

static const meba_ptp_rs422_conf_t jaguar2_rs422_conf = {
    .gpio_rs422_1588_mstoen = 55,
    .gpio_rs422_1588_slvoen = 54,
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

static const meba_event_t init_int_source_id[VTSS_TS_IO_ARRAY_SIZE] = {MEBA_EVENT_PTP_PIN_0, MEBA_EVENT_PTP_PIN_1, MEBA_EVENT_PTP_PIN_2, MEBA_EVENT_PTP_PIN_3};

static const uint32_t pin_conf[VTSS_TS_IO_ARRAY_SIZE] = {
(MEBA_PTP_IO_CAP_PIN_OUT | MEBA_PTP_IO_CAP_PIN_IN),
(MEBA_PTP_IO_CAP_PHY_SYNC),
(MEBA_PTP_IO_CAP_TIME_IF_IN | MEBA_PTP_IO_CAP_PIN_IN),
(MEBA_PTP_IO_CAP_TIME_IF_OUT)
};

static const uint32_t pin_conf_pcb111[VTSS_TS_IO_ARRAY_SIZE] = {
(MEBA_PTP_IO_CAP_PIN_OUT | MEBA_PTP_IO_CAP_PIN_IN),
(MEBA_PTP_IO_CAP_UNUSED),
(MEBA_PTP_IO_CAP_PIN_OUT | MEBA_PTP_IO_CAP_PIN_IN),
(MEBA_PTP_IO_CAP_UNUSED)
};

#define MALIBU_PORT_START 49    // Iport start
#define MALIBU_PORT_END   52    // Iport end (incl)
static const jr2_malibu_gpio_port_map_t malibu_gpio_map[] = {
    /* P49: CH3 */
    {
        28, 34, 26, 27, 0, 25,
        ((1<<VTSS_10G_GPIO_AGGR_INTRPT_CH3_INTR0_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR3_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR3_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_GPIO_INTR_EN)),
    },
    /* P50: CH2 */
    {
        20, 34, 18, 19, 0, 17,
        ((1<<VTSS_10G_GPIO_AGGR_INTRPT_CH2_INTR0_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR2_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR2_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_GPIO_INTR_EN)),
    },
    /* P51: CH1 */
    {
        12, 34, 10, 11, 0, 9,
        ((1<<VTSS_10G_GPIO_AGGR_INTRPT_CH1_INTR0_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR1_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR1_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_GPIO_INTR_EN)),
    },
    /* P52: CH0 */
    {
        4, 34, 2, 3, 0, 1,
        ((1<<VTSS_10G_GPIO_AGGR_INTRPT_CH0_INTR0_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR0_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR0_EN) |
         (1<<VTSS_10G_GPIO_AGGR_INTRPT_GPIO_INTR_EN)),
    },
};

static mesa_rc jr2_sgpio_event_enable(const meba_inst_t        inst,
                                      const mesa_sgpio_group_t group,
                                      const mesa_port_no_t     port,
                                      const uint32_t           bit,
                                      mesa_bool_t              enable)
{
    T_N(inst, "grp %d p%d.b%d %sable", group, port, bit, enable ? "en" : "dis");
    return mesa_sgpio_event_enable(NULL, 0, group, port, bit, enable);
}

static mesa_rc malibu_mode_conf(const meba_inst_t inst);
static mesa_rc malibu_gpio_conf(const meba_inst_t inst);
static mesa_rc venice_ts_gpio_conf();
/* --------------------------- Board specific ------------------------------- */

static mesa_bool_t jr2_10g_malibu_detect(const meba_inst_t inst)
{
    uint16_t model = 0;

    /* Trying to read PHY ID at MIIM controller = 0 */
    if (mebaux_mmd_rd(inst, &rawio, 0, 0, 30, 0, &model) == MESA_RC_OK) {
        T_I(inst, "10g phy model %x\n", model);
        if (model == 0x8254 || model == 0x8256 || model == 0x8257 || model == 0x8258) {
            return true;
        }
    }

    return false;
}

static mesa_bool_t jr2_10g_venice_detect(const meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint16_t model = 0;
    /* Trying to read PHY ID at MIIM controller = 0 */
    if (mebaux_mmd_rd(inst, &rawio, 0, 0, 30, 0, &model) == MESA_RC_OK) {
        if (model == 0x8484 || model == 0x8487 || model == 0x8488) {
            board->venice_present = model;
            return true;
        }
    }
    if (mebaux_mmd_rd(inst, &rawio, 0, 24, 30, 0, &model) == MESA_RC_OK) {
        if (model == 0x8489 || model == 0x8490 || model == 0x8491) {
            board->venice_present = model;
            return true;
        }
    }

    board->venice_present = 0;
    return false;
}

static void jr2_aqr_side_board_detect(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint16_t value = 0;
    uint8_t ctrl = 0;

    mebaux_mmd_rd(inst, &rawio, ctrl, board->detect.miim_addr[0], 0x1e, 0x3, &value);
    board->aqr_sb_present = value == PHY_ID_AQR407_B0
                            || value == PHY_ID_AQR411_A0_ES1
                            || value == PHY_ID_AQR411_B0
                            || value == PHY_ID_AQR412_A0_ES1
                            || value == PHY_ID_AQR412_B0
                            || value == PHY_ID_AQR411C_A0_ES1
                            || value == PHY_ID_AQR412C_A0_ES1 ? value : 0;
}

static void jr2_gpy241_side_board_detect(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint16_t value = 0;
    uint8_t ctrl = 0;

    mebaux_mmd_rd(inst, &rawio, ctrl, 24, 0x1, 0x3, &value);
    board->gpy241_sb_present = value == PHY_ID_GPY241 ? value : 0;
    T_D(inst, "GPY241 side board %s\n", board->gpy241_sb_present ? "found" : "not found");
}

static mesa_bool_t jr2_10g_detect(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint16_t model = 0, miim;
    uint8_t ctrl = 0;

    if (board->detect.miim_found[1]) {
        // Already found a VTSS PHY in previous round, just return the miim address
        board->detect.miim_addr[0] = board->detect.miim_addr[1];
        board->detect.cap = (MEBA_PORT_CAP_VTSS_10G_PHY | MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_XAUI_LANE_FLIP);
        T_I(inst, "10G PHY already found at addr %x, capabilities %08x",  board->detect.miim_addr[0], (uint32_t) board->detect.cap);
        return true;
    }

    // Scan the miim bus for PHY targets, they come in pairs..
    for (miim = 0; miim < 32; miim++) {
        if (mebaux_mmd_rd(inst, &rawio, ctrl, miim, 30, 0, &model) == MESA_RC_OK) {
            if (model == 0x8484 || model == 0x8487 || model == 0x8488 ||
                model == 0x8489 || model == 0x8490 || model == 0x8491) {
                T_D(inst, "Found VTSS PHY model 0x%x at port_no %u", model, board->detect.port_no);
                if (!board->detect.miim_found[0]) {
                    board->detect.miim_addr[1] = miim; // need to swap the channels to get them inline with JR2 ports
                    board->detect.miim_found[0] = 1;
                    board->detect.cap = (MEBA_PORT_CAP_VTSS_10G_PHY | MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_XAUI_LANE_FLIP);
                } else {
                    board->detect.miim_addr[0] = miim;
                    board->detect.miim_found[1] = 1;
                    return true;
                }
            }
        }
    }
    // VTSS Phy not found, look for X2 or Xenpak module at the given miim_addr
    if (mebaux_mmd_rd(inst, &rawio, ctrl, board->detect.miim_addr[0], 1, 0, &model) == MESA_RC_OK) {
        T_D(inst, "Found XAUI device at at miim address:%d port_no %u", board->detect.miim_addr[0], board->detect.port_no);
        board->detect.cap = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_XAUI_LANE_FLIP);
        return true;
    }
    return false; // Nothing found
}

static void init_port_serval2(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    if (port_no < 4) {
        /* Port 0-3: Copper ports */
        entry->map.chip_port       = port_no + 8;
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
        entry->map.miim_addr       = port_no + 16;
        entry->map.max_bw          = MESA_BW_1G;
        entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
        entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
    } else if (port_no < 12) {
        /* Port 4-11: 2.5G SFP */
        entry->map.chip_port       = port_no + ((port_no & 1) ? 7 : 9);
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
        entry->map.max_bw          = MESA_BW_2G5;
        entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
        entry->cap                 = MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH;
    } else if (port_no < 14) {
        /* Port 12-13: SFP+ */
        entry->map.chip_port       = port_no == 13 ? 49 : 50;
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
        entry->map.max_bw          = MESA_BW_10G; // 10G
        /* TBD */
        entry->mac_if              = MESA_PORT_INTERFACE_SFI;
        entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
    } else {
        /* Port 14: NPI port */
        entry->map.chip_port       = 48;
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
        entry->map.miim_addr       = 28;
        entry->map.max_bw          = MESA_BW_1G;
        entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
        entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
    }
}

static void init_port_cu48(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    meba_board_state_t *board = INST2BOARD(inst);
    if (port_no < 48) {
        /* Port 0-47: Copper ports */
        entry->map.chip_port       = port_no;
        entry->map.miim_controller = port_no < 24 ? MESA_MIIM_CONTROLLER_1 : MESA_MIIM_CONTROLLER_2;
        entry->map.miim_addr       = port_no < 24 ? port_no : port_no - 24;
        entry->map.max_bw          = MESA_BW_1G;
        entry->mac_if              = MESA_PORT_INTERFACE_QSGMII;
        entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        entry->poe_chip_port       = entry->map.chip_port % 24; // Each PD69200 controller controls 24 ports.
        entry->poe_support         = true;
    } else if (port_no < 50 &&
               (inst->props.target == MESA_TARGET_SPARX_IV_90 ||
                inst->props.target == MESA_TARGET_JAGUAR_2)) {
        /* Port 48-49: 10G ports SFI or XAUI */
        /* Detect 10G PHY, can be a VTSS PHY or X2/Xenpak module */
        /* If a device is found then this XAUI port is activated and a SFP+ port disabled */
        board->detect.port_no = port_no;
        board->detect.miim_addr[0] = (port_no - 24);
        board->detect.cap = 0;
        entry->map.max_bw = MESA_BW_10G; // 10G

        if (jr2_10g_detect(inst)) {
            /* API Port 48,49 = XAUI chip ports 49,50 - possibly VTSS PHYs */
            entry->map.chip_port       = port_no + 1;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
            entry->map.miim_addr       = board->detect.miim_addr[0];
            entry->mac_if              = MESA_PORT_INTERFACE_XAUI;
            entry->cap                 = board->detect.cap;
        } else {
            /* API Port 48,49 = SFP+ chip ports 50,49 */
            entry->map.chip_port       = port_no == 48 ? 50 : 49;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->mac_if              = MESA_PORT_INTERFACE_SFI;
            entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
        }
    } else if (port_no < 52 &&
               (inst->props.target == MESA_TARGET_SPARX_IV_90) &&
               (port_no != board->port_cnt - 1)) {
        /* API Port 50,51: 10G SFI ports 52,51 */
        entry->map.chip_port       = port_no == 50 ? 52 : 51;
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
        entry->map.max_bw          = MESA_BW_10G; // 10G
        entry->mac_if              = MESA_PORT_INTERFACE_SFI;
        entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
    } else if (port_no < 50 && inst->props.target == MESA_TARGET_SPARX_IV_80) {
        /* Port 48-49: 10G ports SFI or XAUI */
        /* Detect 10G PHY, can be a VTSS PHY or X2/Xenpak module */
        /* If a device is found then this XAUI port is activated and a  SFP+ port disabled */
        board->detect.port_no = port_no;
        board->detect.miim_addr[0] = (port_no - 24);
        board->detect.cap = 0;
        entry->map.max_bw = MESA_BW_10G; // 10G

        if (jr2_10g_detect(inst)) {
            /* API Port 48,49: XAUI chip ports 49,50 - possibly VTSS PHYs */
            entry->map.chip_port       = port_no + 1;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
            entry->map.miim_addr       = board->detect.miim_addr[0];
            entry->mac_if              = MESA_PORT_INTERFACE_XAUI;
            entry->cap                 = board->detect.cap;
        } else {
            /* API Port 48-49: SFP+ chip ports:51,52 */
            entry->map.chip_port       = port_no == 48 ? 52 : 51;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->mac_if              = MESA_PORT_INTERFACE_SFI;
            entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
        }
    } else if (port_no < 52 && inst->props.target == MESA_TARGET_SPARX_IV_52) {
        /* Port 48-51: SFP */
        entry->map.chip_port       = port_no + ((port_no & 1) ? 0 : 2);
        entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
        entry->map.max_bw          = MESA_BW_1G;
        entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
        entry->cap                 = MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH;
    } else {
        /* Last port (NPI) */
        entry->map.chip_port       = 48;
        entry->map.miim_controller = mebaux_phy_detect(inst, &rawio, 28); // Autodetect controller 0 or 1
        entry->map.miim_addr       = 28;
        entry->map.max_bw          = MESA_BW_1G;
        entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
        entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
    }
}

static void init_port_jr2(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    meba_board_state_t *board = INST2BOARD(inst);

    if (board->port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI || board->port_cfg == VTSS_BOARD_CONF_DEFAULT_VENICE_1G_MODE) {
        if (port_no < 8) {
            entry->map.chip_port       = port_no;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_1;
            entry->map.miim_addr       = port_no;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
            if (port_no >= 4) {
                entry->phy_base_port = 4;
            }
        } else if (port_no < 24) {
            entry->map.chip_port       = port_no;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
            if (port_no > 11) {
                entry->map.max_bw = MESA_BW_1G;
                entry->cap        = MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH;
            } else {
                entry->map.max_bw = MESA_BW_2G5;
                entry->cap        = MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH;
            }
        } else if(port_no < board->port_cnt - 1) {
            board->detect.port_no = port_no;
            board->detect.miim_addr[0] = (port_no - 24);
            board->detect.cap = 0;
            entry->map.max_bw = MESA_BW_10G; // 10G
            if ((port_no > 23 && port_no < 28) && board->aqr_sb_present) {
                /* AQR PCB126 side board */
                entry->map.chip_port       = port_no + 25;
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
                entry->map.miim_addr       = board->detect.miim_addr[0];
                entry->mac_if              = MESA_PORT_INTERFACE_SFI;
                entry->cap                 = (MEBA_PORT_CAP_COPPER_10G | MEBA_PORT_CAP_5G_FDX | MEBA_PORT_CAP_2_5G_TRI_SPEED_FDX | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_NO_FORCE);
                if ((board->aqr_sb_present == PHY_ID_AQR411_A0_ES1) || (board->aqr_sb_present == PHY_ID_AQR411_B0) || (board->aqr_sb_present == PHY_ID_AQR411C_A0_ES1)) {
                    entry->cap                 &= ~MEBA_PORT_CAP_10G_FDX;
                } else if ((board->aqr_sb_present == PHY_ID_AQR412_A0_ES1) || (board->aqr_sb_present == PHY_ID_AQR412_B0) || (board->aqr_sb_present == PHY_ID_AQR412C_A0_ES1)) {
                    entry->cap                 &= ~(MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_5G_FDX);
                }
            } else if ((port_no > 23 && port_no < 28) && board->gpy241_sb_present) {
                /* GPY241 side board */
                entry->map.max_bw = MESA_BW_2G5;
                entry->map.chip_port       = port_no + 25;
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
                entry->map.miim_addr       = port_no;
                entry->mac_if              = MESA_PORT_INTERFACE_SGMII_2G5;
                entry->cap                 = MEBA_PORT_CAP_2_5G_TRI_SPEED_COPPER | MEBA_PORT_CAP_SERDES_RX_INVERT | MEBA_PORT_CAP_SERDES_TX_INVERT;
            } else if ((port_no == 24 || port_no == 25) && jr2_10g_detect(inst)) {
                /* API Port 26,27 = XAUI chip ports 49,50 - possibly VTSS PHYs */
                if (board->port_cfg == VTSS_BOARD_CONF_DEFAULT_VENICE_1G_MODE) {
                    /* chip ports 49-50 do not map to single XAUI lanes instead
                       we use chip ports 24 and 28 */
                    entry->map.chip_port = (port_no == 24) ? 24 : 28;
                    entry->cap |= MEBA_PORT_CAP_1G_FDX | MEBA_PORT_CAP_AUTONEG;
                } else {
                    entry->map.chip_port = (port_no == 24) ? 49 : 50;
                }
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
                entry->map.miim_addr       = board->detect.miim_addr[0];
                entry->mac_if              = MESA_PORT_INTERFACE_XAUI;
                entry->cap                 |= board->detect.cap;
            } else {
                entry->map.chip_port       = port_no + 25;
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
                entry->mac_if              = MESA_PORT_INTERFACE_SFI;
                entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
            }
        } else if (port_no == board->port_cnt - 1) {
            // NPI port
            entry->map.chip_port       = 48;
            entry->map.miim_controller = mebaux_phy_detect(inst, &rawio, 28); // Autodetect controller 0 or 1
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    } else if (board->port_cfg == VTSS_BOARD_CONF_24x2G5_2xSFI_NPI) {
        if (port_no < 16) {
            entry->map.chip_port        = port_no + 8;
            entry->map.miim_controller  = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw           = MESA_BW_2G5;
            entry->mac_if               = MESA_PORT_INTERFACE_SERDES;
            entry->cap                  = MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH;
        } else if (port_no < 24) {
            entry->map.chip_port       = port_no + 8;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_2G5;
            entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
            entry->cap                 = MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT;
        } else if (port_no < 26) {
            entry->map.chip_port       = port_no + 25;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_10G; // 10G
            entry->mac_if              = MESA_PORT_INTERFACE_SFI;
            entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
        } else if (port_no == 26) {
            // NPI port
            entry->map.chip_port       = 48;
            entry->map.miim_controller = mebaux_phy_detect(inst, &rawio, 28); // Autodetect controller 0 or 1
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    } else if (board->port_cfg == VTSS_BOARD_CONF_16x2G5_4xSFI_NPI) {
        if (port_no < 16) {
            entry->map.chip_port       = port_no + 8;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_2G5;
            entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
            entry->cap                 = MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH;
        } else if (port_no < board->port_cnt - 1) {
            entry->map.chip_port       = port_no + 33;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_10G; // 10G
            entry->mac_if              = MESA_PORT_INTERFACE_SFI;
            entry->cap                 = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
        } else if (port_no == board->port_cnt - 1) {
            // NPI port
            entry->map.chip_port       = 48;
            entry->map.miim_controller = mebaux_phy_detect(inst, &rawio, 28); // Autodetect controller 0 or 1
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    } else if (board->port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_2xSFI_NPI) {
        if (port_no < 8) {
            entry->map.chip_port       = port_no;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_1;
            entry->map.miim_addr       = port_no;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
            if (port_no >= 4) {
                entry->phy_base_port = 4;
            }
        } else if (port_no < 24) {
            entry->map.chip_port       = port_no;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
            if (port_no > 11) {
                entry->map.max_bw = MESA_BW_1G;
                entry->cap        = MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH;
            } else {
                entry->map.max_bw = MESA_BW_2G5;
                entry->cap        = MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH;
            }
        } else if (port_no < 26) {
            entry->map.chip_port       = port_no + 27;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_10G; // 10G
            entry->mac_if              = MESA_PORT_INTERFACE_SFI;
            entry->cap = (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH);
        } else if (port_no == 26) {
            // NPI port
            entry->map.chip_port       = 48;
            entry->map.miim_controller = mebaux_phy_detect(inst, &rawio, 28); // Autodetect controller 0 or 1
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        } else {
            entry->map.chip_port = CHIP_PORT_UNUSED;
        }
    }
}

static void jr2_map_update(meba_port_entry_t      *entry,
                           int                    chip_port,
                           uint8_t                miim_addr,
                           mesa_miim_controller_t miim_controller,
                           mesa_port_interface_t  mac_if,
                           meba_port_cap_t        cap)
{
    entry->map.chip_port = chip_port;
    entry->map.miim_controller = miim_controller;
    entry->map.miim_addr = miim_addr;
    entry->map.max_bw = (cap & MEBA_PORT_CAP_10G_FDX) ? MESA_BW_10G : (cap & MEBA_PORT_CAP_2_5G_TRI_SPEED_COPPER) ? MESA_BW_2G5 : MESA_BW_1G;
    entry->mac_if = mac_if;
    entry->cap = cap;
}

static void init_port_aqr(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    /* new MDIO mapping for new AQ board
     * Internal Port   Chip Port   MIIM Address    MIIM Controller
     * -------------   ---------   ------------    ---------------
     * 0               11          8               0
     * 1               10          9               0
     * 2               9           10              0
     * 3               8           11              0
     * 4               15          12              0
     * 5               14          13              0
     * 6               13          14              0
     * 7               12          15              0

     * 8               19          16              1
     * 9               18          17              1
     * 10              17          18              1
     * 11              16          19              1
     * 12              23          20              1
     * 13              22          21              1
     * 14              21          22              1
     * 15              20          23              1

     * 16              27          24              2
     * 17              26          25              2
     * 18              25          26              2
     * 19              24          27              2
     * 20              31          28              2
     * 21              30          29              2
     * 22              29          30              2
     * 23              28          31              2

     * 24              51          -               -
     * 25              52          -               -
     */

#define E(p, a, c) jr2_map_update(entry, p, a, c, MESA_PORT_INTERFACE_SGMII_2G5, MEBA_PORT_CAP_COPPER |  MEBA_PORT_CAP_2_5G_TRI_SPEED_FDX | MEBA_PORT_CAP_NO_FORCE)
    switch (port_no) {
        case 0: E(11, 8, MESA_MIIM_CONTROLLER_0); break;
        case 1: E(10, 9, MESA_MIIM_CONTROLLER_0); break;
        case 2: E(9,  10, MESA_MIIM_CONTROLLER_0); break;
        case 3: E(8,  11, MESA_MIIM_CONTROLLER_0); break;
        case 4: E(15, 12, MESA_MIIM_CONTROLLER_0); break;
        case 5: E(14, 13, MESA_MIIM_CONTROLLER_0); break;
        case 6: E(13, 14, MESA_MIIM_CONTROLLER_0); break;
        case 7: E(12, 15, MESA_MIIM_CONTROLLER_0); break;

        case 8: E(19, 16, MESA_MIIM_CONTROLLER_1); break;
        case 9: E(18, 17, MESA_MIIM_CONTROLLER_1); break;
        case 10: E(17, 18, MESA_MIIM_CONTROLLER_1); break;
        case 11: E(16, 19, MESA_MIIM_CONTROLLER_1); break;
        case 12: E(23, 20, MESA_MIIM_CONTROLLER_1); break;
        case 13: E(22, 21, MESA_MIIM_CONTROLLER_1); break;
        case 14: E(21, 22, MESA_MIIM_CONTROLLER_1); break;
        case 15: E(20, 23, MESA_MIIM_CONTROLLER_1); break;

        case 16: E(27, 24, MESA_MIIM_CONTROLLER_2); break;
        case 17: E(26, 25, MESA_MIIM_CONTROLLER_2); break;
        case 18: E(25, 26, MESA_MIIM_CONTROLLER_2); break;
        case 19: E(24, 27, MESA_MIIM_CONTROLLER_2); break;
        case 20: E(31, 28, MESA_MIIM_CONTROLLER_2); break;
        case 21: E(30, 29, MESA_MIIM_CONTROLLER_2); break;
        case 22: E(29, 30, MESA_MIIM_CONTROLLER_2); break;
        case 23: E(28, 31, MESA_MIIM_CONTROLLER_2); break;
#undef E

#define E10G(p) jr2_map_update(entry, p, 0, MESA_MIIM_CONTROLLER_NONE, MESA_PORT_INTERFACE_SFI, MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH)
        case 24: E10G(51); break;
        case 25: E10G(52); break;
#undef E10G
    }
}

static void jr2_init_srv2_nid(meba_inst_t inst)
{
    mesa_sgpio_conf_t conf;
    uint32_t               port, gpio, bit;

    /* GPIO pins 0-3 are used for SGPIOs. */
    (void)mesa_gpio_mode_set(NULL, 0, 0, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)mesa_gpio_mode_set(NULL, 0, 1, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 2, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)mesa_gpio_mode_set(NULL, 0, 3, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / LD

    (void)mesa_gpio_mode_set(NULL, 0, 30, MESA_GPIO_ALT_0); // SGPIO Grp 2 / Clk
    (void)mesa_gpio_mode_set(NULL, 0, 31, MESA_GPIO_ALT_0); // SGPIO Grp 2 / LD
    (void)mesa_gpio_mode_set(NULL, 0, 32, MESA_GPIO_ALT_0); // SGPIO Grp 2 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 33, MESA_GPIO_ALT_0); // SGPIO Grp 2 / DI

    for (gpio = 44; gpio <= 59; gpio++) {
        if (gpio > 49 && gpio < 56) {
            continue;
        }
        (void)mesa_gpio_mode_set(NULL, 0, gpio, MESA_GPIO_IN_INT); // Enable SFP Los interrupt
    }

    /* Setup SGPIO group 0 used for SFP signals */
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;

        for (port = 0; port < 16; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_ON;
        }

        // SFP[1-8]_TX_FAULT are active high
        for (port = 4; port <= 7; port++) {
            for (bit = 0; bit <= 1; bit++) {
                conf.port_conf[port].int_pol_high[bit] = true;
            }
        }

        // SFP+[1-2]_TX_FAULT are active high
        for (bit = 0; bit <= 1; bit++) {
            conf.port_conf[10].int_pol_high[bit] = true;
        }

        (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }

    /* Setup SGPIO group 1 is not used */
    if (mesa_sgpio_conf_get(NULL, 0, 1, &conf) == MESA_RC_OK) {
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        (void)mesa_sgpio_conf_set(NULL, 0, 1, &conf);
    }

    /* Setup SGPIO group 2 used for LEDs */
    if (mesa_sgpio_conf_get(NULL, 0, 2, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        // LEDs
        for (port = 0; port < 16 ; port++) {
            conf.port_conf[port].enabled = 1;
        }
        for (port = 21; port < 29 ; port++) {
            conf.port_conf[port].enabled = 1;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 2, &conf);
    }

}

static void jr2_init_cu48(meba_inst_t inst)
{
    mesa_sgpio_conf_t conf;
    uint32_t port, gpio_no, bit;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 56; gpio_no < 60; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    /* GPIO pins 0-3,4-5,30-33 are used for SGPIOs. */
    (void)mesa_gpio_mode_set(NULL, 0,  0, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)mesa_gpio_mode_set(NULL, 0,  1, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)mesa_gpio_mode_set(NULL, 0,  2, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)mesa_gpio_mode_set(NULL, 0,  3, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / LD
    (void)mesa_gpio_mode_set(NULL, 0,  4, MESA_GPIO_ALT_0);  // SGPIO Grp 1 / CLK
    (void)mesa_gpio_mode_set(NULL, 0,  5, MESA_GPIO_ALT_0);  // SGPIO Grp 1 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 30, MESA_GPIO_ALT_0);  // SGPIO Grp 2 / Clk
    (void)mesa_gpio_mode_set(NULL, 0, 31, MESA_GPIO_ALT_0);  // SGPIO Grp 2 / LD
    (void)mesa_gpio_mode_set(NULL, 0, 32, MESA_GPIO_ALT_0);  // SGPIO Grp 2 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 33, MESA_GPIO_ALT_0);  // SGPIO Grp 2 / DI
    (void)mesa_gpio_mode_set(NULL, 0, 52, MESA_GPIO_IN_INT); // Enable 10G SFP Los Intr
    (void)mesa_gpio_mode_set(NULL, 0, 53, MESA_GPIO_IN_INT); // Enable 10G SFP Los Intr
    (void)mesa_gpio_mode_set(NULL, 0, 54, MESA_GPIO_IN_INT); // Enable 10G SFP Los Intr
    (void)mesa_gpio_mode_set(NULL, 0, 55, MESA_GPIO_IN_INT); // Enable 10G SFP Los Intr

    /* Setup SGPIO group 0 */
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        for (port = 0; port < MESA_SGPIO_PORTS; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_ON;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    /* Setup SGPIO group 1 */
    if (mesa_sgpio_conf_get(NULL, 0, 1, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        // QSGMII ports
        for (port = 0; port < 16; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_ON;
        }
        // SFP+ ports
        for (port = 17; port < 21; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_ON;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 1, &conf);
    }
    /* Setup SGPIO group 2 */
    if (mesa_sgpio_conf_get(NULL, 0, 2, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 3;

        // 24:NPI, 25:X2 slot A, 26:X2 slot B, [31:27] TxEnable, Fan, SFP+ TxEnable, Rate select
        for (port = 24; port < 32 ; port++) {
            conf.port_conf[port].enabled = 1;
        }

        // SFPplus[A|B|C|D]_TXFAULT are active high
        for (port = 25; port <= 28; port++) {
            conf.port_conf[port].int_pol_high[2] = true;
        }

        // X2[A|B]_LOS[0-3] are active high
        for (port = 29; port <= 31 ; port++) {
            for (bit = 0; bit <= 2; bit++) {
                if (port == 29 && bit == 0) {
                    continue; // p29b0 is SYNCEPRESENTn (which is active low)
                }

                conf.port_conf[port].int_pol_high[bit] = true; // LOS is active high
            }
        }

        /* X2 TXONOFF = ON */
        conf.port_conf[26].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[27].mode[0] = MESA_SGPIO_MODE_ON;
        /* SFP Tx_disable = enabled */
        conf.port_conf[28].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[28].mode[1] = MESA_SGPIO_MODE_ON;
        conf.port_conf[28].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[29].mode[0] = MESA_SGPIO_MODE_ON;
        /* SFP RateSel = enabled    */
        conf.port_conf[29].mode[1] = MESA_SGPIO_MODE_ON;
        conf.port_conf[29].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[30].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[30].mode[1] = MESA_SGPIO_MODE_ON;
        conf.port_conf[30].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[31].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[31].mode[1] = MESA_SGPIO_MODE_ON;
        conf.port_conf[31].mode[2] = MESA_SGPIO_MODE_ON;

        (void)mesa_sgpio_conf_set(NULL, 0, 2, &conf);
    }
    /* must enable the the following interrupts (even though they are not used) to force them to be edge triggered */
    (void)jr2_sgpio_event_enable(inst, 2, 25, 0, true); // SFPplusA_MODDET
    (void)jr2_sgpio_event_enable(inst, 2, 25, 1, true); // SFPplusA_TXFAULT
    (void)jr2_sgpio_event_enable(inst, 2, 25, 1, true); // SFPplusB_MODDET
    (void)jr2_sgpio_event_enable(inst, 2, 25, 2, true); // SFPplusB_TXFAULT
}

static void jr2_init_sfp24(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t  conf;
    uint32_t           port, gpio_no;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 56; gpio_no < 58; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    /* GPIO pins 0-3,4-5,30-33 are used for SGPIOs. */
    (void)mesa_gpio_mode_set(NULL, 0, 0, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)mesa_gpio_mode_set(NULL, 0, 1, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 2, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)mesa_gpio_mode_set(NULL, 0, 3, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / LD
    (void)mesa_gpio_mode_set(NULL, 0, 4, MESA_GPIO_ALT_0);  // SGPIO Grp 1 / CLK
    (void)mesa_gpio_mode_set(NULL, 0, 5, MESA_GPIO_ALT_0);  // SGPIO Grp 1 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 30, MESA_GPIO_ALT_0); // SGPIO Grp 2 / Clk
    (void)mesa_gpio_mode_set(NULL, 0, 31, MESA_GPIO_ALT_0); // SGPIO Grp 2 / LD
    (void)mesa_gpio_mode_set(NULL, 0, 32, MESA_GPIO_ALT_0); // SGPIO Grp 2 / DO
    (void)mesa_gpio_mode_set(NULL, 0, 33, MESA_GPIO_ALT_0); // SGPIO Grp 2 / DI

    (void)mesa_gpio_mode_set(NULL, 0, 28, MESA_GPIO_OUT);
    (void)mesa_gpio_write(NULL, 0, 28, true);
    (void)mesa_gpio_mode_set(NULL, 0, 29, MESA_GPIO_OUT);
    (void)mesa_gpio_write(NULL, 0, 29, true);
    (void)mesa_gpio_mode_set(NULL, 0, 49, MESA_GPIO_OUT);
    (void)mesa_gpio_write(NULL, 0, 49, true);

    /* GPIOs 51,52,53,58,59 are used for I2C external muxing */
    (void)mesa_gpio_mode_set(NULL, 0, 51, MESA_GPIO_OUT);
    (void)mesa_gpio_mode_set(NULL, 0, 52, MESA_GPIO_OUT);
    (void)mesa_gpio_mode_set(NULL, 0, 53, MESA_GPIO_OUT);
    (void)mesa_gpio_mode_set(NULL, 0, 58, MESA_GPIO_OUT);
    (void)mesa_gpio_mode_set(NULL, 0, 59, MESA_GPIO_OUT);

    /* GPIOs 17,18,20,21 are used for I2C internal muxing */
    (void)mesa_gpio_mode_set(NULL, 0, 17, MESA_GPIO_ALT_1);
    (void)mesa_gpio_mode_set(NULL, 0, 18, MESA_GPIO_ALT_1);
    (void)mesa_gpio_mode_set(NULL, 0, 20, MESA_GPIO_ALT_1);
    (void)mesa_gpio_mode_set(NULL, 0, 21, MESA_GPIO_ALT_1);

    /* Setup SGPIO group 0    */
    /* Controls Port LEDs 1-24*/
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        for (port = 0; port < 24; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_ON;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    /* Setup SGPIO group 1 */
    /* Controls LEDs for SFP+ and the LED tower */
    if (mesa_sgpio_conf_get(NULL, 0, 1, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 2;
        // LEDs for SFP+ and the LED tower
        for (port = 16; port < 24; port++) {
            conf.port_conf[port].enabled = 1;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 1, &conf);
    }
    /* Setup SGPIO group 2 */
    /* Controls LED for NPI, X2 LEDs and SFP signals */
    if (mesa_sgpio_conf_get(NULL, 0, 2, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_5;
        conf.bit_count = 3;

        for (port = 0; port < 16 ; port++) {
            conf.port_conf[port].enabled = 1; // SFPs
            conf.port_conf[port].int_pol_high[0] = true; // LOS is active high
            conf.port_conf[port].int_pol_high[2] = true; // TX_FAULT is active high
        }

        for (port = 24; port < 30 ; port++) {
            conf.port_conf[port].enabled = 1; // CuPhys + SFPs+ + synce
        }

        for (port = 25; port < 29 ; port++) {
            conf.port_conf[port].int_pol_high[0] = true; // LOS is active high
            conf.port_conf[port].int_pol_high[2] = true; // TX_FAULT is active high
        }

        /* X2 TXONOFF = ON */
        conf.port_conf[10].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[11].mode[0] = MESA_SGPIO_MODE_ON;
        /* SFP+ Tx_disable = enabled */
        conf.port_conf[12].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[12].mode[1] = MESA_SGPIO_MODE_ON;
        conf.port_conf[12].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[13].mode[0] = MESA_SGPIO_MODE_ON;
        /* SFP RateSel = enabled    */
        conf.port_conf[13].mode[1] = MESA_SGPIO_MODE_ON;
        conf.port_conf[13].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[14].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[14].mode[1] = MESA_SGPIO_MODE_ON;
        conf.port_conf[14].mode[2] = MESA_SGPIO_MODE_ON;
        conf.port_conf[15].mode[0] = MESA_SGPIO_MODE_ON;
        conf.port_conf[15].mode[1] = MESA_SGPIO_MODE_ON;
        conf.port_conf[15].mode[2] = MESA_SGPIO_MODE_ON;

        conf.port_conf[24].mode[0] = MESA_SGPIO_MODE_ON; // NPI
        conf.port_conf[25].mode[1] = MESA_SGPIO_MODE_ON; // X2 A
        conf.port_conf[26].mode[0] = MESA_SGPIO_MODE_ON; // X2 B

        (void)mesa_sgpio_conf_set(NULL, 0, 2, &conf);
    }

    if (board->gpy241_sb_present) {
        // It takes a while for the Intel/MaxLinear PHYs to get out of reset.
        VTSS_MSLEEP(1000);
    }
}

static void jr2_init_aqr(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t conf;
    uint32_t port, gpio_no;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 56; gpio_no < 60; gpio_no++) {
        (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
    }

    (void)mesa_gpio_mode_set(NULL, 0, 0, MESA_GPIO_ALT_0);      // Serial LED Clock
    (void)mesa_gpio_mode_set(NULL, 0, 1, MESA_GPIO_ALT_0);      // Serial LED Data
    (void)mesa_gpio_mode_set(NULL, 0, 21, MESA_GPIO_OUT);       // SFP+ 26 Port TX disable: High : SFP+ TX power disable
    (void)mesa_gpio_mode_set(NULL, 0, 23, MESA_GPIO_OUT);       // SFP+ 25 Port TX disable: High : SFP+ TX power disable
    (void)mesa_gpio_mode_set(NULL, 0, 24, MESA_GPIO_IN);        // SFP+ 26 Port Present: Low : SFP+ Module Inserted
    (void)mesa_gpio_mode_set(NULL, 0, 25, MESA_GPIO_IN);        // SFP+ 25 Port Present: Low : SFP+ Module Inserted
    (void)mesa_gpio_mode_set(NULL, 0, 26, MESA_GPIO_OUT);       // n_PHY_RESET pin, active low at least 100ms
    (void)mesa_gpio_mode_set(NULL, 0, 48, MESA_GPIO_IN_INT);    // Default setting or System reset (Low active)
    (void)mesa_gpio_mode_set(NULL, 0, 54, MESA_GPIO_IN_INT);    // Port 26 nSD signal: Low : SFP+ Module Iinking
    (void)mesa_gpio_mode_set(NULL, 0, 55, MESA_GPIO_IN_INT);    // Port 25 nSD signal: Low : SFP+ Module Iinking


    (void)mesa_gpio_write(NULL, 0, 21, 0);
    (void)mesa_gpio_write(NULL, 0, 23, 0);

    /* Setup SGPIO group 0     */
    /* Controls Port LEDs 1-26 */
    if (mesa_sgpio_conf_get(NULL, 0, 0, &conf) == MESA_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = MESA_SGPIO_BMODE_1_25;
        conf.bit_count = 2;
        for (port = 0; port < board->port_cnt && port < MESA_SGPIO_PORTS; port++) {
            conf.port_conf[port].enabled = true;
        }
        (void)mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
}


/* Port traffic activity is manually updated */
static mesa_bool_t port_activity(meba_inst_t inst,
                                 mesa_port_no_t port_no,
                                 const mesa_port_status_t *status,
                                 const mesa_port_counters_t *counters,
                                 mesa_bool_t *counters_activity)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_status_t *old_status = &board->port[port_no].status;
    mesa_port_counters_t *old_cnt = &board->port[port_no].cnt;
    mesa_bool_t link_activity = false;

    if ((counters->rmon.rx_etherStatsPkts != old_cnt->rmon.rx_etherStatsPkts) ||
        (counters->rmon.tx_etherStatsPkts != old_cnt->rmon.tx_etherStatsPkts)) {
        *counters_activity = true;
        *old_cnt = *counters;
    }
    if (old_status->link  != status->link  ||
        old_status->speed != status->speed ||
        old_status->fdx   != status->fdx) {
        link_activity = true;
        *old_status = *status;
    }
    if (!*counters_activity && !link_activity && !board->port[port_no].activity) {
        return false; // No Activity
    }
    board->port[port_no].activity = link_activity || *counters_activity;
    return true; // Activity
}

/* Port traffic activity is auto updated */
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

static mesa_rc led_update_s2(meba_inst_t inst,
                             mesa_port_no_t port_no,
                             const mesa_port_status_t *status,
                             const mesa_port_counters_t *counters,
                             const meba_port_admin_state_t *state)
{
    mesa_rc              rc = MESA_RC_OK;
    static uint8_t       port_to_led_map[] = {0,1,2,3,5,4,7,6,9,8,11,10,26,25,24}; // See UG1057, table 16 (The table doesn't say that bit 25 and 26 shall be swapped, but that has turned out to be the case)
    uint32_t             sgpio_port;
    mesa_sgpio_conf_t    conf;
    mesa_sgpio_mode_t    mode_green, mode_yellow;
    mesa_bool_t          counters_activity = false;

    if (!port_activity(inst, port_no, status, counters, &counters_activity)) {
        return rc;
    }

    if ((rc = mesa_sgpio_conf_get(NULL, 0, 2, &conf)) == MESA_RC_OK) {

        mode_green = MESA_SGPIO_MODE_OFF;
        mode_yellow = MESA_SGPIO_MODE_OFF;

        if (status->link) {
            if (status->speed >= MESA_SPEED_1G) {
                if (counters_activity) {
                    mode_green = MESA_SGPIO_MODE_0;
                } else {
                    mode_green = MESA_SGPIO_MODE_ON;
                }
            } else {
                if (counters_activity) {
                    mode_yellow = MESA_SGPIO_MODE_0;
                } else {
                    mode_yellow = MESA_SGPIO_MODE_ON;
                }
            }
        }
        if (port_no < sizeof(port_to_led_map)) {
            sgpio_port = port_to_led_map[port_no];
            conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_green;
            conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_yellow;
            rc = mesa_sgpio_conf_set(NULL, 0, 2, &conf);
        }
    }
    return rc;
}

static mesa_rc led_update_j2_cu48(meba_inst_t inst,
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
    mesa_sgpio_mode_t   mode_green, mode_yellow;

    if (!port_activity_auto(inst, port_no, status)) {
        return rc;
    }

    mode_green = entry->map.chip_port == JR2_NPI_CHIP_PORT ? MESA_SGPIO_MODE_OFF : MESA_SGPIO_MODE_ON;
    mode_yellow = entry->map.chip_port == JR2_NPI_CHIP_PORT ? MESA_SGPIO_MODE_OFF : MESA_SGPIO_MODE_ON;

    /* If link then auto update LED */
    if (status->link) {
        if (status->speed >= MESA_SPEED_1G) {
            mode_green = (entry->map.chip_port == JR2_NPI_CHIP_PORT) ? MESA_SGPIO_MODE_0_ACTIVITY_INV : MESA_SGPIO_MODE_0_ACTIVITY;
        } else {
            mode_yellow = (entry->map.chip_port == JR2_NPI_CHIP_PORT) ? MESA_SGPIO_MODE_0_ACTIVITY_INV : MESA_SGPIO_MODE_0_ACTIVITY;
        }
    }

    if (entry->map.chip_port < 32) {
        sgpio_port = entry->map.chip_port;
        sgpio_group = 0;
    } else if (entry->map.chip_port < 48) {
        sgpio_port = entry->map.chip_port - 32;
        sgpio_group = 1;
    } else if (entry->map.chip_port == 48) {
        sgpio_port = 24; //NPI
        sgpio_group = 2;
    } else {
        if ((entry->mac_if == MESA_PORT_INTERFACE_XAUI) && (entry->map.chip_port == 49 || entry->map.chip_port == 50)) {
            sgpio_group = 2;
            sgpio_port = (entry->map.chip_port == 49) ? 25 : 26;
            mode_green = status->link ? MESA_SGPIO_MODE_0_ACTIVITY_INV : MESA_SGPIO_MODE_0_ACTIVITY;
            mode_yellow = MESA_SGPIO_MODE_OFF;
        } else {
            // SFP+ ports
            switch (entry->map.chip_port) {
            case 49:  sgpio_port = 17; break;
            case 50:  sgpio_port = 18; break;
            case 51:  sgpio_port = 19; break;
            case 52:  sgpio_port = 20; break;
            }
            sgpio_group = 1;
        }
    }
    if ((rc = mesa_sgpio_conf_get(NULL, 0, sgpio_group, &conf)) == MESA_RC_OK) {
        conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_green;
        conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_yellow;
        rc = mesa_sgpio_conf_set(NULL, 0, sgpio_group, &conf);
    }
    return rc;
}

static mesa_rc led_update_j2_cu8sfp16(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      const mesa_port_status_t *status,
                                      const mesa_port_counters_t *counters,
                                      const meba_port_admin_state_t *state)
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

    mesa_rc             rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t            sgpio_group = 0, sgpio_port = 0;
    meba_port_entry_t  *entry = &board->port[port_no].map;
    mesa_sgpio_conf_t   conf;
    mesa_sgpio_mode_t   mode_green = MESA_SGPIO_MODE_ON, mode_yellow = MESA_SGPIO_MODE_ON;
    uint16_t            led0_value = AQR_LED_OFF, led1_value = AQR_LED_OFF, led2_value = AQR_LED_OFF;

    if (!port_activity_auto(inst, port_no, status)) {
        return rc;
    }

    if (entry->map.chip_port < 32) {
        sgpio_group = 0;
        sgpio_port = entry->map.chip_port;
    } else if (entry->map.chip_port == 48) {
        sgpio_group = 2;
        sgpio_port = 24; // NPI
        mode_green =  MESA_SGPIO_MODE_OFF;
        mode_yellow = MESA_SGPIO_MODE_OFF;
    } else if (entry->map.chip_port > 48) {
        if (board->aqr_sb_present || board->gpy241_sb_present) {
            led0_value = AQR_LED_OFF;
            led1_value = AQR_LED_OFF;
        }
        mode_green =  MESA_SGPIO_MODE_OFF;
        mode_yellow = MESA_SGPIO_MODE_OFF;
        if (entry->mac_if == MESA_PORT_INTERFACE_SFI) {
            sgpio_group = 1;
            sgpio_port = 16 + (entry->map.chip_port - 49);  // SFP+
        } else { // XAUI port
            sgpio_group = 2;
            sgpio_port = entry->map.chip_port == 49 ? 25 : 26;
        }
    }

    /* If AQR PCB126 SB link then update LED */
    if (entry->map.chip_port > 48 && (board->aqr_sb_present || board->gpy241_sb_present)) {
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
            /* BZ#23143, according to BZ#23013, now LED0 and LED2 are still not work, so now change to the behavior:
               No matter what speed are link up, the L_LED will always lit green.
            */
            switch (status->speed) {
                case MESA_SPEED_100M:
                case MESA_SPEED_1G:
                case MESA_SPEED_2500M:
                case MESA_SPEED_5G:
                case MESA_SPEED_10G:
                    led1_value = AQR_LED_ON | AQR_LED_RX_ACT | AQR_LED_TX_ACT | AQR_LED_ACT_STRETCH_60;
                    led0_value = AQR_LED_OFF;
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

    /* If link then auto update LED */
    if (status->link) {
        if (status->speed >= MESA_SPEED_1G) {
            mode_green = (entry->map.chip_port == JR2_NPI_CHIP_PORT || (entry->map.chip_port > 48)) ?
                    MESA_SGPIO_MODE_0_ACTIVITY_INV : MESA_SGPIO_MODE_0_ACTIVITY;
        } else {
            mode_yellow = (entry->map.chip_port == JR2_NPI_CHIP_PORT || (entry->map.chip_port > 48)) ?
                    MESA_SGPIO_MODE_0_ACTIVITY_INV : MESA_SGPIO_MODE_0_ACTIVITY;
        }
    }

    if ((rc = mesa_sgpio_conf_get(NULL, 0, sgpio_group, &conf)) == MESA_RC_OK) {
        // The Green/yellow LEDs are inverted for 1G ports, except for NPI port
        // (chip_port 48).
        conf.port_conf[sgpio_port].mode[LED_GREEN] = (entry->map.chip_port >= 48) ? mode_green : mode_yellow;
        conf.port_conf[sgpio_port].mode[LED_YELLOW] = (entry->map.chip_port >= 48) ? mode_yellow : mode_green;
        rc = mesa_sgpio_conf_set(NULL, 0, sgpio_group, &conf);
    }
    return rc;
}

static mesa_rc led_update_aqr(meba_inst_t inst,
                              mesa_port_no_t port_no,
                              const mesa_port_status_t *status,
                              const mesa_port_counters_t *counters,
                              const meba_port_admin_state_t *state)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc             rc = MESA_RC_OK;
    uint32_t            sgpio_port = 0;
    mesa_sgpio_conf_t   conf;
    mesa_bool_t         cnt_activity = false;

    if (!port_activity(inst, port_no, status, counters, &cnt_activity)) {
        return rc;
    }

    if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
        mesa_sgpio_mode_t mode_green = MESA_SGPIO_MODE_ON, mode_yellow = MESA_SGPIO_MODE_ON; // set green/yellow led off
        uint32_t chip_port = board->port[port_no].map.map.chip_port;
        /* chip port to sgpio port translation */
        if (chip_port == 51) {
            sgpio_port = 24;
        } else if (chip_port == 52) {
            sgpio_port = 25;
        } else {
            sgpio_port = chip_port - 8;
        }

        if (status->link) {
            // 1G lit yellow, 100M/2.5G/10G lit green
            if (status->speed != MESA_SPEED_1G) {
                if (cnt_activity) {
                    mode_green = MESA_SGPIO_MODE_0;
                } else {
                    mode_green = MESA_SGPIO_MODE_OFF;
                }
            } else {
                if (cnt_activity) {
                    mode_yellow = MESA_SGPIO_MODE_0;
                } else {
                    mode_yellow = MESA_SGPIO_MODE_OFF;
                }
            }
        }
        /* Note: For AQ PHY, colors green & yellow are swapped */
        conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_yellow;
        conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_green;

        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc;
}

static const board_func_t board_funcs[] = {
    [BOARD_TYPE_SERVAL2_NID] = {
        .board_init = jr2_init_srv2_nid,
        .init_port  = init_port_serval2,
        .led_update = led_update_s2,
    },
    [BOARD_TYPE_JAGUAR2_CU48] = {
        .board_init = jr2_init_cu48,
        .init_port  = init_port_cu48,
        .led_update = led_update_j2_cu48 ,
    },
    [BOARD_TYPE_JAGUAR2] = {
        .board_init = jr2_init_sfp24,
        .init_port  = init_port_jr2,
        .led_update = led_update_j2_cu8sfp16,
    },
    [BOARD_TYPE_JAGUAR2_AQR] = {
        .board_init = jr2_init_aqr,
        .init_port  = init_port_aqr,
        .led_update = led_update_aqr,
    },
};

static mesa_bool_t get_sfp_status(meba_inst_t inst,
                                  mesa_port_no_t port_no,
                                  mesa_sgpio_port_data_t *data,
                                  sfp_signal_t sfp)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t chip_port = board->port[port_no].map.map.chip_port;
    if (board->type == BOARD_TYPE_SERVAL2_NID) {
        if (sfp == SFP_DETECT) {
            switch (chip_port) { // The Present signal is inverted
                case 13: return !data[0].value[0];
                case 12: return !data[0].value[1];
                case 15: return !data[1].value[0];
                case 14: return !data[1].value[1];
                case 17: return !data[2].value[0];
                case 16: return !data[2].value[1];
                case 19: return !data[3].value[0];
                case 18: return !data[3].value[1];
                case 50: return !data[8].value[0];
                case 49: return !data[8].value[1];
            }
            return 0;
        } else if (sfp == SFP_FAULT) {
            switch (chip_port) {
                case 13: return data[4].value[0];
                case 12: return data[4].value[1];
                case 15: return data[5].value[0];
                case 14: return data[5].value[1];
                case 17: return data[6].value[0];
                case 16: return data[6].value[1];
                case 19: return data[7].value[0];
                case 18: return data[7].value[1];
                case 50: return data[10].value[0];
                case 49: return data[10].value[1];
            }
            return 0;
        } else {
            mesa_bool_t val = 0;
            // SFP_LOS
            switch (chip_port) {
                case 13: (void)mesa_gpio_read(NULL, 0, 44, &val); break;
                case 12: (void)mesa_gpio_read(NULL, 0, 45, &val); break;
                case 15: (void)mesa_gpio_read(NULL, 0, 46, &val); break;
                case 14: (void)mesa_gpio_read(NULL, 0, 47, &val); break;
                case 17: (void)mesa_gpio_read(NULL, 0, 48, &val); break;
                case 16: (void)mesa_gpio_read(NULL, 0, 49, &val); break;
                case 19: (void)mesa_gpio_read(NULL, 0, 56, &val); break;
                case 18: (void)mesa_gpio_read(NULL, 0, 57, &val); break;
                case 50: (void)mesa_gpio_read(NULL, 0, 58, &val); break;
                case 49: (void)mesa_gpio_read(NULL, 0, 59, &val); break;
            }
            return val;
        }

    } else if (board->type == BOARD_TYPE_JAGUAR2) {
        uint32_t indx = (sfp == SFP_DETECT) ? 1 : (sfp == SFP_FAULT) ? 2 : 0;
        if (chip_port >= 8 && chip_port <= 23) {
            if (sfp == SFP_DETECT) {
                return !data[chip_port - 8].value[1];
            } else {
                return data[chip_port - 8].value[indx];
            }
        } else if (chip_port >= 49 && chip_port <= 52) {
            if (sfp == SFP_DETECT) {
                return !data[chip_port - 24].value[indx];
            } else {
                return data[chip_port - 24].value[indx];
            }
        }
    } else {
        // BOARD_TYPE_JAGUAR2_CU48 || BOARD_TYPE_JAGUAR2_AQR
        if (sfp == SFP_LOS) {
            mesa_bool_t val = 0;
            // SFP_LOS
            switch (chip_port) {
                case 49: (void)mesa_gpio_read(NULL, 0, 52, &val); break;
                case 50: (void)mesa_gpio_read(NULL, 0, 53, &val); break;
                case 51: (void)mesa_gpio_read(NULL, 0, 54, &val); break;
                case 52: (void)mesa_gpio_read(NULL, 0, 55, &val); break;
            }
            return val;
        } else {
            if (board->type == BOARD_TYPE_JAGUAR2_AQR) {
                if (chip_port == 51 || chip_port == 52) {
                    mesa_bool_t val;
                    switch (chip_port) {
                        case 51:
                            if (sfp == SFP_DETECT) {
                                (void)mesa_gpio_read(NULL, 0, 25, &val);
                            } else if (sfp == SFP_FAULT){
                                (void)mesa_gpio_read(NULL, 0, 22, &val);
                            }
                            break;
                        case 52:
                            if (sfp == SFP_DETECT) {
                                (void)mesa_gpio_read(NULL, 0, 24, &val);
                            } else if (sfp == SFP_FAULT){
                                (void)mesa_gpio_read(NULL, 0, 20, &val);
                            }
                            break;
                    }
                    return sfp == SFP_DETECT ? !val : val;
                }
            } else {
                uint32_t indx = (sfp == SFP_DETECT) ? 1 : (sfp == SFP_FAULT) ? 2 : 0;
                if (chip_port >= 8 && chip_port <= 23) {
                    if (sfp == SFP_DETECT) {
                        return !data[chip_port - 8].value[1];
                    } else {
                        return data[chip_port - 8].value[indx];
                    }
                } else if (chip_port >= 49 && chip_port <= 52) {
                    if (sfp == SFP_DETECT) {
                        return !data[chip_port - 24].value[indx];
                    } else {
                        return data[chip_port - 24].value[indx];
                    }
                }
            }
        }
    }
    return 0;
}

/* ---------------------------   Exposed API  ------------------------------- */

static uint32_t jr2_capability(meba_inst_t inst,
                               int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_POE:
            return board->type == BOARD_TYPE_JAGUAR2_CU48;   // Only JR2-48
        case MEBA_CAP_1588_CLK_ADJ_DAC:
            return board->type != BOARD_TYPE_SERVAL2_NID;    // Not Serval2
        case MEBA_CAP_1588_REF_CLK_SEL:
            return board->type == BOARD_TYPE_JAGUAR2;        // Only JR2-24
        case MEBA_CAP_TEMP_SENSORS:
            if (board->type == BOARD_TYPE_JAGUAR2_CU48) {
                return 5;    // Atom x 4, base chip
            } else if (board->type == BOARD_TYPE_SERVAL2_NID) {
                return 2;    // 8514 x 1, base chip
            } else if (board->type == BOARD_TYPE_JAGUAR2 &&
                       board->port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
                return 3;    // Viper x 2, base chip
            }
            return 1;    // Base chip
        case MEBA_CAP_BOARD_PORT_COUNT:
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            // On this platform port count and port map count are identical (no loop ports)
            return board->port_cnt;
        case MEBA_CAP_LED_MODES:
            return 1;    /* No alternate led mode support */
        case MEBA_CAP_DYING_GASP:
            return (board->type == BOARD_TYPE_SERVAL2_NID);
        case MEBA_CAP_FAN_SUPPORT:
            return board->type != BOARD_TYPE_JAGUAR2_AQR;
        case MEBA_CAP_LED_DIM_SUPPORT:
            return board->type != BOARD_TYPE_JAGUAR2_AQR;
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
            if (board->type == BOARD_TYPE_JAGUAR2 || board->type == BOARD_TYPE_JAGUAR2_CU48) {
                return true;
            } else {
                return false;
            }
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
            if (board->type == BOARD_TYPE_JAGUAR2) {
                return true;
            } else {
                return false;
            }
        case MEBA_CAP_BOARD_HAS_PCB135_CPLD:
            return false;
        case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:      // NOTE: Capability currently not used on Jr2. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:  // NOTE: Capability currently not used on Jr2. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_DPLL:            // NOTE: Capability currently not used on Jr2. Therefore, it has been set to -1
            return -1;
        case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:      // NOTE: Capability currently not used on Jr2. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:  // NOTE: Capability currently not used on Jr2. Therefore, it has been set to 0
            return 0;
        case MEBA_CAP_ONE_PPS_INT_ID:
            return MEBA_EVENT_PTP_PIN_1;
        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:      // Jr2 supports single DPLL mode if a DPLL is present, but Jr48 does only support LTC mode
            {
                meba_synce_clock_hw_id_t dpll_type;

                if (board->type == BOARD_TYPE_JAGUAR2 || board->type == BOARD_TYPE_SERVAL2_NID) {
                    if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK) && (dpll_type != MEBA_SYNCE_CLOCK_HW_NONE)) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:        // Jr2 (24 ports only) and Serval2 NID support dual DPLL mode if the DPLL type is zls30363
            if (board->type == BOARD_TYPE_JAGUAR2 || board->type == BOARD_TYPE_SERVAL2_NID) {
                meba_synce_clock_hw_id_t dpll_type;

                if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK) &&
                    ((dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30363) || (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772))) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET:
             // On jr2 clock_input_sma is not directly connected to Zl30772, so CPLD has to be configured to route the connection
             if (board->type == BOARD_TYPE_JAGUAR2) {
                meba_synce_clock_hw_id_t dpll_type;
                if ((meba_synce_spi_if_get_dpll_type(inst, &dpll_type) == MESA_RC_OK) && (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772)) {
                    return true;
                } else {
                    return false;
                }

             } else {
                 return false;
             }
        case MEBA_CAP_POE_BT:
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

static mesa_rc jr2_port_entry_get(meba_inst_t inst,
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

// Reset PHY and wait for Reset completed every 10 ms but at most 2000 ms,
// this function is required because after releasing reset state, there are following procedure
// before PHY ready:
// 3) After the 20ms timer has completed, hardware state machines designed
//    to guarantee PLL and band-gap stability engage.
// 4) After the PLLs and band-gap are locked and functioning properly, the
//    processor and digital circuitry are released from reset.
// 5) The PHY image is then loaded (either via the daisy-chain, or through
//    MDIO boot-load) and the processor boots.
// 6) After the processor boots, any provisioned register values are set, and
//    the PHY enters the provisioned operating state.
// 7) Once this is complete, the processor raises the MMD reset bits and sets
//    the Reset Completed alarm, indicating it has completed reset and is
//    ready for operation.
//
// Refer to DS-N2104_AQR407H_Data_Sheet_v0.6
static void jr2_hard_reset_wait_aqr(meba_inst_t inst)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint16_t reg_value;
    mesa_bool_t reset_done[board->port_cnt], at_least_one_phy_not_reset;
    mesa_port_no_t port_no;
    int i = 0;

    (void)mesa_gpio_write(NULL, 0, 26, 0);  // n_PHY_RESET pin, active low at least 100ms
    VTSS_MSLEEP(120);
    (void)mesa_gpio_write(NULL, 0, 26, 1);  // n_PHY_RESET pin, release reset state, pull high at least 20ms
    VTSS_MSLEEP(30);

    T_D(inst, "Release Reset state");
    memset(reset_done, false, board->port_cnt);
    do {
        at_least_one_phy_not_reset = false;
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            meba_port_entry_t *entry = &board->port[port_no].map;
            if (reset_done[port_no] || entry->map.miim_controller == MESA_MIIM_CONTROLLER_NONE) {
                continue;
            }
            if (mesa_mmd_read(NULL, 0, entry->map.miim_controller, entry->map.miim_addr, 0x1e, 0xcc00, &reg_value) == MESA_RC_OK && (reg_value & 0x40)) {
                reset_done[port_no] = true;
                T_I(inst, "hard reset ready on MDIO-%d", entry->map.miim_addr);
            } else {
                at_least_one_phy_not_reset = true;
            }
        }

        if (at_least_one_phy_not_reset) {
            VTSS_MSLEEP(10);
        }
    } while (i++ < 200 && at_least_one_phy_not_reset);

    if (at_least_one_phy_not_reset) {
        T_E(inst, "Unable to reset at least one AQR PHY");
    }
}

static void malibu_init(meba_inst_t inst) {
    /* The following Malibu initialization is board specific and therefore is located in MEBA */
    vtss_phy_10g_mode_t oper_mode = {};
    oper_mode.oper_mode = VTSS_PHY_LAN_MODE;
    oper_mode.xfi_pol_invert = 1;
    oper_mode.polarity.host_rx = true;
    oper_mode.polarity.line_rx = true;
    oper_mode.polarity.host_tx = false;
    oper_mode.polarity.line_tx = false;
    oper_mode.is_host_wan = false;
    oper_mode.lref_for_host = false;
    oper_mode.h_clk_src.is_high_amp = true;
    oper_mode.l_clk_src.is_high_amp = true;
    oper_mode.h_media = VTSS_MEDIA_TYPE_SR;
    oper_mode.l_media = VTSS_MEDIA_TYPE_SR;
    oper_mode.serdes_conf.l_offset_guard = true;
    oper_mode.serdes_conf.h_offset_guard = true;

    /* port_no    miim    channel */
    /* 24         3       3 */
    /* 25         2       2 */
    /* 26         1       1 */
    /* 27         0       0 : must be initilized first */

    for (mesa_port_no_t iport = 27; iport > 23; iport--) {
        if (iport == 25 ) {
            oper_mode.polarity.host_rx = false;
            oper_mode.polarity.line_rx = false;
            oper_mode.polarity.host_tx = true;
            oper_mode.polarity.line_tx = true;
        }
        if (vtss_phy_10g_mode_set(PHY_INST, iport, &oper_mode) != MESA_RC_OK) {
            T_E(inst, "vtss_phy_10g_mode_set failed, port_no %u", iport);
        }
    }
}

static void venice_init(meba_inst_t inst) {
    /* The following Venice initialization is board specific and therefore is located in MEBA */
    meba_board_state_t *board = INST2BOARD(inst);
    uint16_t model = board->venice_present;

    if (board->venice_present == 0)
        return;

    vtss_phy_10g_mode_t oper_mode = {};
    oper_mode.oper_mode = VTSS_PHY_LAN_MODE;

    if (model == 0x8484 || model == 0x8487 || model == 0x8488) {
        oper_mode.xfi_pol_invert = 0;
    } else {
        oper_mode.xfi_pol_invert = 1;
    }

    if (model == 0x8489 || model == 0x8490 || model == 0x8491) {
        oper_mode.venice_rev_a_los_detection_workaround = true;
        oper_mode.apc_ib_regulator = VTSS_APC_IB_BACKPLANE;
        oper_mode.l_clk_src.is_high_amp = true;
    }

    if (model == 0x8484 || model == 0x8487 || model == 0x8488 || model == 0x8489 || model == 0x8490) {
        if (model == 0x8489) {
            if (vtss_phy_10g_mode_set(PHY_INST, 24, &oper_mode) != MESA_RC_OK)
                T_E(inst, "vtss_phy_10g_mode_set_failed, port_no %u", 24);
            if (vtss_phy_10g_mode_set(PHY_INST, 25, &oper_mode) != MESA_RC_OK)
                T_E(inst, "vtss_phy_10g_mode_set_failed, port_no %u", 25);
        }
        else {
            if (vtss_phy_10g_mode_set(PHY_INST, 25, &oper_mode) != MESA_RC_OK)
                T_E(inst, "vtss_phy_10g_mode_set_failed, port_no %u", 25);
            if (vtss_phy_10g_mode_set(PHY_INST, 24, &oper_mode) != MESA_RC_OK)
                T_E(inst, "vtss_phy_10g_mode_set_failed, port_no %u", 24);
        }
    }
}

static mesa_rc jr2_reset(meba_inst_t inst,
                         meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;
    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            board->func->board_init(inst);
            if (board->type == BOARD_TYPE_JAGUAR2) {
                rc = malibu_mode_conf(inst);

                // detect the venice board
                jr2_10g_venice_detect(inst);
            }
            break;
        case MEBA_PORT_RESET:
            if (board->port[0].map.map.miim_controller != MESA_MIIM_CONTROLLER_NONE) {
                if (board->type == BOARD_TYPE_JAGUAR2_CU48) {
                    if ((rc = vtss_phy_pre_reset(PHY_INST, 0)) == MESA_RC_OK &&
                        (rc = vtss_phy_pre_reset(PHY_INST, 12)) == MESA_RC_OK &&
                        (rc = vtss_phy_pre_reset(PHY_INST, 24)) == MESA_RC_OK)
                        rc = vtss_phy_pre_reset(PHY_INST, 36);
                } else if (board->type == BOARD_TYPE_JAGUAR2) {
                    if ((rc = vtss_phy_pre_reset(PHY_INST, 0)) == MESA_RC_OK)
                        rc = vtss_phy_pre_reset(PHY_INST, 4);
                } else if (board->type == BOARD_TYPE_SERVAL2_NID) { // This board has a Viper or a Tesla See schematics
                    rc = vtss_phy_pre_reset(PHY_INST, 0);
                } else if( board->type == BOARD_TYPE_JAGUAR2_AQR) {
                    jr2_hard_reset_wait_aqr(inst);
                }
            }
            if (board->malibu_present) {
                /* Initlize the 10G Malibu Phy */
                malibu_init(inst);
            }
            if (board->venice_present) {
                /* Initialize the 10G Venice Phy */
                venice_init(inst);
            }
            break;
        case MEBA_PORT_RESET_POST:
            if (board->type != BOARD_TYPE_JAGUAR2_AQR) {
                if (board->port[0].map.map.miim_controller != MESA_MIIM_CONTROLLER_NONE) {
                    if (board->type == BOARD_TYPE_JAGUAR2 || board->type == BOARD_TYPE_JAGUAR2_CU48) {
                        rc = vtss_phy_post_reset(PHY_INST, 0);
                    }
                }
                if (rc == MESA_RC_OK) {
                    rc = malibu_gpio_conf(inst);
                }
                if (board->venice_present) {
                    rc = venice_ts_gpio_conf();
                }
            }
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            mesa_gpio_direction_set(NULL, 0, STATUSLED_G_GPIO, true);
            mesa_gpio_direction_set(NULL, 0, STATUSLED_R_GPIO, true);
            break;
        case MEBA_PORT_LED_INITIALIZE:
            // Enable enahanced LED control to disable the Phy PWM (LED intensity) signal (otherwise the LEDs are off).
            if (board->port[0].map.map.miim_controller != MESA_MIIM_CONTROLLER_NONE) {
                if (board->type != BOARD_TYPE_JAGUAR2_AQR) {
                    (void)vtss_phy_write(NULL, 0, 31, 0x0010);
                    (void)vtss_phy_write(NULL, 0, 25, 0xc6b5);
                    (void)vtss_phy_write(NULL, 0, 31, 0);
                }

                /* Set up LED enhanced led */
                if (board->port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
                    vtss_phy_enhanced_led_control_t conf;
                    conf.ser_led_frame_rate = 0x1; /* Frame rate = 1000Hz */
                    conf.ser_led_select = 2;       /* Does't matter */
                    if (board->type == BOARD_TYPE_JAGUAR2_CU48) {
                        conf.ser_led_output_2 = true; /* PCB111 uses phy3_led1 as PWM. See schematic- LED_PWM */
                        conf.ser_led_output_1 = false;  /* Not used. */
                        vtss_phy_enhanced_led_control_init(PHY_INST, 1, conf); /* Setup port 1, PWM is used for port1, see schematic PCB111 near R1380 */
                    } else if (board->type == BOARD_TYPE_JAGUAR2) {
                        conf.ser_led_output_2 = false; /* Not used. */
                        conf.ser_led_output_1 = true;  /* PCB110 uses phy3_led0 as PWM. See schematic- LED_PWM */
                        vtss_phy_enhanced_led_control_init(PHY_INST, 1, conf); /* Setup port 1, PWM is used for port1, see schematic PCB110 near R1380 */
                    } else if (board->type == BOARD_TYPE_SERVAL2_NID) {
                        conf.ser_led_output_2 = false; /* Not used. */
                        conf.ser_led_output_1 = true;  /* PCB112 uses LED3_0 as PWM. See schematic- LED_PWM */
                        vtss_phy_enhanced_led_control_init(PHY_INST, 0, conf); /* Setup port 0, PWM is used for port0, see schematic PCB112 near R1380 */
                    }
                }
            }
            break;
        case MEBA_FAN_INITIALIZE:
            rc = mesa_fan_controller_init(NULL, board->fan_spec);
            if (rc == MESA_RC_OK &&
                board->type == BOARD_TYPE_SERVAL2_NID) {
                // FAN_ENA - See UG1057 Table 15
                mesa_sgpio_conf_t  conf;
                int port = 1;

                if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
                    conf.port_conf[port].enabled = true;
                    conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_OFF; // Note - FAN1_ENA is active low - See schematic.
                    conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF; // Note - FAN2_ENA is active low - See schematic.
                    rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
                }
            }
            break;
        case MEBA_SENSOR_INITIALIZE:
            // All boards have the internal JR2 sensor
            if ((rc = mesa_temp_sensor_init(NULL, true)) == MESA_RC_OK) {
                if (board->type == BOARD_TYPE_JAGUAR2_CU48) {
                    // The Jaguar2 48 ports board has a temperature sensor in 4 Atom12s
                    if ((rc = vtss_phy_chip_temp_init(PHY_INST, 0)) == MESA_RC_OK &&
                        (rc = vtss_phy_chip_temp_init(PHY_INST, 12)) == MESA_RC_OK &&
                        (rc = vtss_phy_chip_temp_init(PHY_INST, 24)) == MESA_RC_OK)
                        rc = vtss_phy_chip_temp_init(PHY_INST, 36);
                } else if (board->type == BOARD_TYPE_SERVAL2_NID) {
                    // One sensor in the 8584 PHY and one in Serval2 (iport set to 0)
                    rc = vtss_phy_chip_temp_init(PHY_INST, 0);
                } else if (board->type == BOARD_TYPE_JAGUAR2) {
                    if (board->port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
                        // If JR2 is running in
                        // VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI mode, the
                        // JR2 board has two temperature sensors in 2
                        // Viper (port1-8) + one in JR2
                        if ((rc = vtss_phy_chip_temp_init(PHY_INST, 0)) == MESA_RC_OK)
                            rc = vtss_phy_chip_temp_init(PHY_INST, 4);
                    }
                }
            }
            break;
        case MEBA_INTERRUPT_INITIALIZE:
            {
                mesa_port_no_t port_no;
                for (port_no = 0; port_no < board->port_cnt; port_no++) {
                    vtss_phy_type_t phy_id;
                    if (is_10g_port(board->port[port_no].map.cap)) {
                        board->phy10g_ts_cnt++;
                    }
                    if (vtss_phy_id_get(PHY_INST, port_no, &phy_id) != MESA_RC_OK) {
                        continue;
                    }
                    if ((phy_id.part_number == VTSS_PHY_TYPE_8574) || (phy_id.part_number == VTSS_PHY_TYPE_8572) ||
                        (phy_id.part_number == VTSS_PHY_TYPE_8582) || (phy_id.part_number == VTSS_PHY_TYPE_8584) ||
                        (phy_id.part_number == VTSS_PHY_TYPE_8575)) {
                        board->port[port_no].ts_phy = true;
                    }
                }
            }
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

static mesa_rc jr2_sensor_get(meba_inst_t inst,
                              meba_sensor_t type,
                              int six,
                              int *value)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_ERROR;
    int16_t temp = 0;
    T_N(inst, "Called %d:%d", type, six);
    if (type == MEBA_SENSOR_BOARD_TEMP) {
        if (six == 0) {
            rc = mesa_temp_sensor_get(NULL, &temp);
        } else if (board->type == BOARD_TYPE_JAGUAR2_CU48 && six < 5) {
            rc = vtss_phy_chip_temp_get(PHY_INST, (six-1)*12, &temp); // One per Atom PHY 12 x 4
        } else if (board->type == BOARD_TYPE_SERVAL2_NID && six < 2) {
            rc = vtss_phy_chip_temp_get(PHY_INST, 0, &temp); // One extra in the PHY
        }  else if (board->type == BOARD_TYPE_JAGUAR2 && six < 3 &&
                    board->port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) { // One per Viper PHY 4 x 2
            rc = vtss_phy_chip_temp_get(PHY_INST, (six-1)*4, &temp);
        }
    } else if (type == MEBA_SENSOR_PORT_TEMP) {
        if (six < board->port_cnt) {
            if (board->type == BOARD_TYPE_JAGUAR2_CU48) {
                if (six < 48) {
                    rc = vtss_phy_chip_temp_get(PHY_INST, six, &temp);
                } else {
                    rc = mesa_temp_sensor_get(NULL, &temp);
                }
            } else if (board->type == BOARD_TYPE_SERVAL2_NID) {
                // This board has 2 sensors - One in the 8584 PHY and one in Serval2
                // iport 0-3 uses their temperature sensor in the PHY
                if (six < 4) {
                    rc = vtss_phy_chip_temp_get(PHY_INST, six, &temp);
                } else {
                    // All other ports uses the temperature sensor in Serval2
                    rc = mesa_temp_sensor_get(NULL, &temp);
                }
            } else {
                if (board->type == BOARD_TYPE_JAGUAR2 &&
                    board->port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
                    // If JR2 is running in
                    // VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI mode, the
                    // JR2 board has two temperature sensors in 2
                    // Viper (port1-8).  All other ports uses the
                    // temperature sensor in JR2.
                    if (six < 8) {
                        rc = vtss_phy_chip_temp_get(PHY_INST, six, &temp);
                    } else {
                        rc = mesa_temp_sensor_get(NULL, &temp);
                    }
                } else {
                    // For all other modes the PHYs are disabled and we then uses the JR2 sensor
                    rc = mesa_temp_sensor_get(NULL, &temp);
                }
            }
        }
    }
    if (rc == MESA_RC_OK) {
        T_N(inst, "Temp %d:%d = %d", type, six, temp);
        *value = temp;    // Conversion
    } else {
        T_N(inst, "Temp %d:%d = [not read:%d]", type, six, rc);
    }
    return rc;
}

static mesa_rc jr2_sfp_i2c_xfer(meba_inst_t inst,
                                mesa_port_no_t port_no,
                                mesa_bool_t write,
                                uint8_t i2c_addr,
                                uint8_t addr,
                                uint8_t *data,
                                uint8_t cnt,
                                mesa_bool_t word_access)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    uint16_t value;
    uint8_t idx;
    T_N(inst, "Called");
    if (board->malibu_present && (port_no >= 24 && port_no < 28)) {
        if (write) {
            for (idx = 0; idx < cnt; idx++) {
                value = (uint16_t)*(data+idx);
                rc = vtss_phy_10g_i2c_write(NULL, port_no, (uint16_t)(addr + idx), &value);
                if (rc != MESA_RC_OK)
                    return rc;
            }
        } else {
            for (idx = 0; idx < cnt; idx++) {
                rc = vtss_phy_10g_i2c_read(NULL, port_no, (uint16_t)(addr + idx), &value);
                if (rc == MESA_RC_OK)
                    *(data+idx) = (uint8_t)value;
                else
                    return rc;
            }
            return rc;
        }
    } else if (board->port[port_no].map.cap & MEBA_PORT_CAP_DUAL_COPPER) {
        if (write) {
	    rc = vtss_phy_i2c_write(NULL, port_no, port_no, addr, i2c_addr, word_access, 2, data);
        } else {
            rc = vtss_phy_i2c_read(NULL, port_no, port_no, addr, i2c_addr, word_access, cnt, data);
        }
    } else {
        uint32_t chip_port = board->port[port_no].map.map.chip_port;
        if (write) {    // cnt ignored
            uint8_t i2c_data[3];
            i2c_data[0] = addr;
            memcpy(&i2c_data[1], data, 2);
            rc = inst->iface.i2c_write(chip_port, i2c_addr, i2c_data, 3);
        } else {
            rc = inst->iface.i2c_read(chip_port, i2c_addr, addr, data, cnt);
        }
    }
    T_D(inst, "i2c %s port %d - address 0x%02x:0x%02x, %d bytes return %d", write ? "write" : "read", port_no, i2c_addr, addr, cnt, rc);
    return rc;
}

static mesa_rc malibu_mode_conf(const meba_inst_t inst)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_sgpio_conf_t conf;
    uint32_t loop = 0;

    // Is Malibu there ?
    while (!(board->malibu_present = jr2_10g_malibu_detect(inst)) && loop < 50) {
        // After power up malibu is slow to respond.
        loop++;
    }

    if (!board->malibu_present) {
        return MESA_RC_OK;
    }

    if (mesa_port_cnt(NULL) < 28) {
        return MESA_RC_ERROR; // Shall never happen if Malibu is detected.
    }

    /* Update the port map with Malibu phy
       Malibu card base port is 27 and port mapping should be:
       port_no    miim    controller
       24         3       0
       25         2       0
       26         1       0
       27         0       0
     */
    for (mesa_port_no_t iport = 24; iport <= 27; iport++) {
        board->port[iport].map.mac_if              = MESA_PORT_INTERFACE_SFI;
        board->port[iport].map.map.miim_controller = MESA_MIIM_CONTROLLER_0;
        board->port[iport].map.map.miim_addr       = 27 - iport;
        board->port[iport].map.cap = (MEBA_PORT_CAP_VTSS_10G_PHY | MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_1G_FDX);
    }

    if ((rc = mesa_sgpio_conf_get(NULL, 0, 2, &conf)) == MESA_RC_OK) {
        /* Setting LREF_SELx pins to 0x00 for 156.25 MHz, See U1B at PCB VSC8258-SFP-04 schematic
           LREF_SEL0, and LREF_SEL1 goes to SFPplusD_RATESEL0 and SFPplusD_RATESEL1,
           See the two schematics.
           SFPplusD_RATESEL0 goes to Serial GPIO p15b1,(group 2)
           SFPplusD_RATESEL1 goes to Serial GPIO p15b2 (group 2) */
        conf.port_conf[15].enabled = 1;
        conf.port_conf[15].mode[1] =  MESA_SGPIO_MODE_OFF;
        conf.port_conf[15].mode[2] =  MESA_SGPIO_MODE_OFF;
        /* Setup "CML out -> DC coupling -> CML in" to channel o
           Setting SELx pins to 0x00 for channel 0, See U4 at PCB VSC8258-SFP-04 schematic
           SEL0, and SEL1 goes to SFPplusB_RATESEL0 and SFPplusB_RATESEL1,
           See the two schematics.
           SFPplusB_RATESEL0 goes to Serial GPIO p14b0,(group 2)
           SFPplusB_RATESEL1 goes to Serial GPIO p14b1 (group 2) */
        conf.port_conf[14].enabled = 1;
        conf.port_conf[14].mode[0] =  MESA_SGPIO_MODE_OFF;
        conf.port_conf[14].mode[1] =  MESA_SGPIO_MODE_OFF;

        /* To Match interrupt polarity of Malibu */
        conf.port_conf[PHY10G_SGPIO_PORT].int_pol_high[PHY10G_SGPIO_BIT] = true;
        (void)mesa_sgpio_conf_set(NULL, 0, 2, &conf);
    }

    return rc;
}

static mesa_rc venice_ts_gpio_conf()
{
    vtss_gpio_10g_gpio_mode_t  gpio_mode = {};
    vtss_phy_10g_id_t phy_id = {};

    if (vtss_phy_10g_id_get(PHY_INST, 24, &phy_id) == MESA_RC_OK) {
        /* Get base port_no for 10G */
        gpio_mode.port = phy_id.phy_api_base_no;
        gpio_mode.mode = VTSS_10G_PHY_GPIO_1588_1PPS_0;
        vtss_phy_10g_gpio_mode_set(PHY_INST, phy_id.phy_api_base_no, 0, &gpio_mode);
        gpio_mode.mode = VTSS_10G_PHY_GPIO_1588_1PPS_1;
        vtss_phy_10g_gpio_mode_set(PHY_INST, phy_id.phy_api_base_no, 11, &gpio_mode);
    }
    return MESA_RC_OK;
}
static mesa_rc malibu_gpio_conf(const meba_inst_t inst)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_no_t port_no;

    if (board->malibu_present == false)
        return MESA_RC_OK;    // Return all well if no Malibu

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        uint32_t chip_port  = board->port[port_no].map.map.chip_port;
        if (chip_port >= MALIBU_PORT_START && chip_port <= MALIBU_PORT_END) {
            const jr2_malibu_gpio_port_map_t *gmap = &malibu_gpio_map[chip_port-MALIBU_PORT_START];
            vtss_gpio_10g_gpio_mode_t gpio_conf;
            if ((rc = vtss_phy_10g_gpio_mode_get(PHY_INST, port_no, gmap->gpio_tx_dis, &gpio_conf)) == MESA_RC_OK) {
                gpio_conf.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
                rc = vtss_phy_10g_gpio_mode_set(PHY_INST, port_no, gmap->gpio_tx_dis, &gpio_conf);
            }
            if (rc != MESA_RC_OK) {
                return rc;
            }

            /* Configure Aggregated Interrupt-0  */
            if ((rc = vtss_phy_10g_gpio_mode_get(PHY_INST,port_no, gmap->gpio_aggr_int, &gpio_conf)) == MESA_RC_OK) {
                gpio_conf.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;
                gpio_conf.c_intrpt = VTSS_10G_GPIO_INTRPT_HPMA;
                gpio_conf.aggr_intrpt = gmap->aggr_intrpt;
                rc = vtss_phy_10g_gpio_mode_set(PHY_INST, port_no, gmap->gpio_aggr_int, &gpio_conf);
            }
            if (rc != MESA_RC_OK) {
                return rc;
            }

            /* Configure I2c Slave pins clk,data(for SFP access on line)  */
            if ((rc = vtss_phy_10g_gpio_mode_get(PHY_INST,port_no, gmap->gpio_i2c_clk, &gpio_conf)) == MESA_RC_OK) {
                gpio_conf.mode = VTSS_10G_PHY_GPIO_OUT;
                gpio_conf.p_gpio = gmap->gpio_virtual;
                gpio_conf.in_sig = VTSS_10G_GPIO_INTR_SGNL_I2C_MSTR_CLK_OUT;
                rc = vtss_phy_10g_gpio_mode_set(PHY_INST, port_no, gmap->gpio_i2c_clk, &gpio_conf);
            }
            if (rc != MESA_RC_OK) {
                return rc;
            }

            if ((rc = vtss_phy_10g_gpio_mode_get(PHY_INST,port_no, gmap->gpio_i2c_dat, &gpio_conf)) == MESA_RC_OK) {
                gpio_conf.mode = VTSS_10G_PHY_GPIO_OUT;
                gpio_conf.p_gpio = gmap->gpio_virtual + 1;
                gpio_conf.in_sig = VTSS_10G_GPIO_INTR_SGNL_I2C_MSTR_DATA_OUT;
                rc = vtss_phy_10g_gpio_mode_set(PHY_INST, port_no, gmap->gpio_i2c_dat, &gpio_conf);
            }
            if (rc != MESA_RC_OK) {
                return rc;
            }

            /* Configure SFP module detect  */
            if ((rc = vtss_phy_10g_gpio_mode_get(PHY_INST,port_no, gmap->gpio_sfp_mod_det, &gpio_conf)) == MESA_RC_OK) {
                gpio_conf.mode = VTSS_10G_PHY_GPIO_IN;
                gpio_conf.input = VTSS_10G_GPIO_INPUT_SFP_MOD_DET;
                gpio_conf.p_gpio_intrpt = 1;
                rc = vtss_phy_10g_gpio_mode_set(PHY_INST, port_no, gmap->gpio_sfp_mod_det, &gpio_conf);
            }
            if (rc != MESA_RC_OK) {
                return rc;
            }

            if (chip_port == MALIBU_PORT_END) {
                uint32_t global_dev = 0x1e, lopc_reg = 0xf234, lopc_value = 0x13f;
                /* By default GPIO 34 is used as INPUT for LOPC on channel 0, Now as
                   we are changing its default behaviour Configuring registers accordingly */
                rc = vtss_phy_10g_csr_write(PHY_INST,port_no, global_dev, lopc_reg, lopc_value);
            }
        }
    }

    return rc;
}

static mesa_rc jr2_sfp_insertion_status_get(meba_inst_t inst,
                                            mesa_port_list_t *present)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;

    T_N(inst, "Called");

    mesa_port_list_clear(present);

    if (board->type == BOARD_TYPE_JAGUAR2_AQR) {
        mesa_port_no_t port_no;
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            meba_port_entry_t *entry = &board->port[port_no].map;
            if (entry->cap & MEBA_PORT_CAP_SFP_DETECT) {
                mesa_bool_t val = false;
                switch(port_no) {
                    case 24:
                        mesa_gpio_read(NULL, 0, 25, &val);
                        break;
                    case 25:
                        mesa_gpio_read(NULL, 0, 24, &val);
                        break;
                }
                mesa_port_list_set(present, port_no, !val);
                T_D(inst, "SFP-%d: %sPRESENT", port_no - 24, !val ? "" : "NOT-" );
            }
        }
    } else {
        mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];
        if ((rc = mesa_sgpio_read(NULL, 0, (board->type == BOARD_TYPE_SERVAL2_NID) ? 0 : 2, data)) == MESA_RC_OK) {
            mesa_port_no_t port_no;
            if (board->type == BOARD_TYPE_SERVAL2_NID) {
                meba_port_entry_t *entry = &board->port[0].map;
                /* The status in 'data' is inverted i.e. '0' means detected */
                for (port_no = 0; port_no < board->port_cnt; port_no++, entry = &board->port[port_no].map) {
                    if (entry->cap & MEBA_PORT_CAP_SFP_DETECT) {
                        mesa_port_list_set(present, port_no, get_sfp_status(inst, port_no, data, SFP_DETECT));
                    }
                }
            } else {    // cu8sfp16, cu48
                /* The status in 'data' is inverted i.e. '0' means detected */
                for (port_no = 0; port_no < board->port_cnt; port_no++) {
                    uint32_t chip_port = board->port[port_no].map.map.chip_port;

                    // SGPIO2 port/bit       Input                     Output
                    // 0b0    Port  9 (SFP)  LOS (1=LOS from SFP)      Port 9 (SFP) TXEN (1=enable)
                    // 0b1    Port  9 (SFP)  MODDETn (0=SFP present)   Port 9 (SFP) RATESEL
                    // 0b2    Port  9 (SFP)  TXFAULT (1=TX fault)      Port 10 (SFP) TXEN (1=enable)
                    // 1b0    Port 10 (SFP)  LOS (1=LOS from SFP)      Port 10 (SFP) RATESEL
                    // 1b1    Port 10 (SFP)  MODDETn (0=SFP present)   Port 11 (SFP) TXEN (1=enable)
                    // 1b2    Port 10 (SFP)  TXFAULT (1=TX fault)      Port 11 (SFP) RATESEL
                    // 2b0    Port 11 (SFP)  LOS (1=LOS from SFP)      Port 12 (SFP) TXEN (1=enable)
                    // 2b1    Port 11 (SFP)  MODDETn (0=SFP present)   Port 12 (SFP) RATESEL
                    // 2b2    Port 11 (SFP)  TXFAULT (1=TX fault)      Port 13 (SFP) TXEN (1=enable)
                    // 3b0    Port 12 (SFP)  LOS (1=LOS from SFP)      Port 13 (SFP) RATESEL
                    // 3b1    Port 12 (SFP)  MODDETn (0=SFP present)   Port 14 (SFP) TXEN (1=enable)
                    // 3b2    Port 12 (SFP)  TXFAULT (1=TX fault)      Port 14 (SFP) RATESEL
                    // 4b0    Port 13 (SFP)  LOS (1=LOS from SFP)      Port 15 (SFP) TXEN (1=enable)
                    // 4b1    Port 13 (SFP)  MODDETn (0=SFP present)   Port 15 (SFP) RATESEL
                    // 4b2    Port 13 (SFP)  TXFAULT (1=TX fault)      Port 16 (SFP) TXEN (1=enable)
                    // 5b0    Port 14 (SFP)  LOS (1=LOS from SFP)      Port 16 (SFP) RATESEL
                    // 5b1    Port 14 (SFP)  MODDETn (0=SFP present)   Port 17 (SFP) TXEN (1=enable)
                    // 5b2    Port 14 (SFP)  TXFAULT (1=TX fault)      Port 17 (SFP) RATESEL
                    // 6b0    Port 15 (SFP)  LOS (1=LOS from SFP)      Port 18 (SFP) TXEN (1=enable)
                    // 6b1    Port 15 (SFP)  MODDETn (0=SFP present)   Port 18 (SFP) RATESEL
                    // 6b2    Port 15 (SFP)  TXFAULT (1=TX fault)      Port 19 (SFP) TXEN (1=enable)
                    // 7b0    Port 16 (SFP)  LOS (1=LOS from SFP)      Port 19 (SFP) RATESEL
                    // 7b1    Port 16 (SFP)  MODDETn (0=SFP present)   Port 20 (SFP) TXEN (1=enable)
                    // 7b2    Port 16 (SFP)  TXFAULT (1=TX fault)      Port 20 (SFP) RATESEL
                    // 8b0    Port 17 (SFP)  LOS (1=LOS from SFP)      Port 21 (SFP) TXEN (1=enable)
                    // 8b1    Port 17 (SFP)  MODDETn (0=SFP present)   Port 21 (SFP) RATESEL
                    // 8b2    Port 17 (SFP)  TXFAULT (1=TX fault)      Port 22 (SFP) TXEN (1=enable)
                    // 9b0    Port 18 (SFP)  LOS (1=LOS from SFP)      Port 22 (SFP) RATESEL
                    // 9b1    Port 18 (SFP)  MODDETn (0=SFP present)   Port 23 (SFP) TXEN (1=enable)
                    // 9b2    Port 18 (SFP)  TXFAULT (1=TX fault)      Port 23 (SFP) RATESEL
                    // 10b0   Port 19 (SFP)  LOS (1=LOS from SFP)      Port 24 (SFP) TXEN (1=enable)
                    // 10b1   Port 19 (SFP)  MODDETn (0=SFP present)   Port 24 (SFP) RATESEL
                    // 10b2   Port 19 (SFP)  TXFAULT (1=TX fault)      X2_TXONOFF_A
                    // 11b0   Port 20 (SFP)  LOS (1=LOS from SFP)      X2_TXONOFF_B
                    // 11b1   Port 20 (SFP)  MODDETn (0=SFP present)   FAN1_ENn (0=enable)
                    // 11b2   Port 20 (SFP)  TXFAULT (1=TX fault)      FAN2_ENn (0=enable)
                    // 12b0   Port 21 (SFP)  LOS (1=LOS from SFP)      SFP+ 1 TXEN (1=enable)
                    // 12b1   Port 21 (SFP)  MODDETn (0=SFP present)   SFP+ 2 TXEN (1=enable)
                    // 12b2   Port 21 (SFP)  TXFAULT (1=TX fault)      SFP+ 3 TXEN (1=enable)
                    // 13b0   Port 22 (SFP)  LOS (1=LOS from SFP)      SFP+ 4 TXEN (1=enable)
                    // 13b1   Port 22 (SFP)  MODDETn (0=SFP present)   SFP+ 1 RateSel0
                    // 13b2   Port 22 (SFP)  TXFAULT (1=TX fault)      SFP+ 1 RateSel1
                    // 14b0   Port 23 (SFP)  LOS (1=LOS from SFP)      SFP+ 2 RateSel0
                    // 14b1   Port 23 (SFP)  MODDETn (0=SFP present)   SFP+ 2 RateSel1
                    // 14b2   Port 23 (SFP)  TXFAULT (1=TX fault)      SFP+ 3 RateSel0
                    // 15b0   Port 24 (SFP)  LOS (1=LOS from SFP)      SFP+ 3 RateSel1
                    // 15b1   Port 24 (SFP)  MODDETn (0=SFP present)   SFP+ 4 RateSel0
                    // 15b2   Port 24 (SFP)  TXFAULT (1=TX fault)      SFP+ 4 RateSel1
                    // 24b0   nINT_PHY1 (PHY for ports 1-4)            NPI LED, green (1=on)
                    // 24b1   nINT_PHY2 (PHY for ports 5-8)            NPI LED, yellow (1=on)
                    // 24b2   nMODULE_INT (interrupt for X2, Malibu,   NPI, SyncE)    not used
                    // 25b0   SFP+ 1         LOS (1=LOS from SFP+)     X2_A LED, green (1=on)
                    // 25b1   SFP+ 1         MODDETn (0=SFP+ present)  X2_A LED, yellow (1=on)
                    // 25b2   SFP+ 1         TXFAULT (1=TX fault)       not used
                    // 26b0   SFP+ 2         LOS (1=LOS from SFP+)     X2_B LED, green (1=on)
                    // 26b1   SFP+ 2         MODDETn (0=SFP+ present)  X2_B LED, yellow (1=on)
                    // 26b2   SFP+ 2         TXFAULT (1=TX fault)      not used
                    // 27b0   SFP+ 3         LOS (1=LOS from SFP+)     not used
                    // 27b1   SFP+ 3         MODDETn (0=SFP+ present)  not used
                    // 27b2   SFP+ 3         TXFAULT (1=TX fault)      not used
                    // 28b0   SFP+ 4         LOS (1=LOS from SFP+)     not used
                    // 28b1   SFP+ 4         MODDETn (0=SFP+ present)  not used
                    // 28b2   SFP+ 4         TXFAULT (1=TX fault)      not used
                    // 29b0   SyncE module   PRESENT_n                 not used
                    // 29b1   Ext CPU module PRESENTn                  not used
                    // 29b2   not used       not used

                    if (chip_port >= 8 && chip_port <= 23) {
                        mesa_port_list_set(present, port_no, !data[chip_port - 8].value[1]); // Schematic U142
                    } else if (chip_port >= 49 && chip_port <= 52) {
                        mesa_port_list_set(present, port_no, !data[chip_port - 24].value[1]);
                    }
                }
            }
        }
    }
    return rc;
}

static mesa_rc jr2_sfp_status_get(meba_inst_t inst,
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
            if (board->type == BOARD_TYPE_JAGUAR2_AQR) {
                rc = MESA_RC_OK;    // No SGPIO needed, data don't care
            } else {
                uint32_t sgpio_group = (board->type == BOARD_TYPE_SERVAL2_NID) ? 0 : 2;
                rc = mesa_sgpio_read(NULL, 0, sgpio_group, data);
            }
            if (rc == MESA_RC_OK) {
                status->present  = get_sfp_status(inst, port_no, data, SFP_DETECT);
                status->tx_fault = get_sfp_status(inst, port_no, data, SFP_FAULT);
                status->los      = get_sfp_status(inst, port_no, data, SFP_LOS);
            }
        }
    }
    T_N(inst, "port(%d): rc %d, present:%d los:%d tx_fault:%d", port_no, rc,
        status->present, status->los, status->tx_fault);
    return rc;
}

static mesa_rc jr2_port_admin_state_set(meba_inst_t inst,
                                        mesa_port_no_t port_no,
                                        const meba_port_admin_state_t *state)
{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);
    if (board->port[port_no].map.map.miim_controller == MESA_MIIM_CONTROLLER_NONE) {
        mesa_sgpio_conf_t  conf;
        mesa_sgpio_mode_t  sgpio_mode = (state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
        if (board->type == BOARD_TYPE_SERVAL2_NID) {
            // TxDisable maps to SGPIO port bit 0
            static uint8_t port_to_tx_disable_map_nid[] = {0,0,0,0,8,9,10,11,4,5,6,7,12,13};
            if (port_no < sizeof(port_to_tx_disable_map_nid) &&
                (rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
                conf.port_conf[port_to_tx_disable_map_nid[port_no]].mode[0] = sgpio_mode;
                rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
            }
        } else if (board->type == BOARD_TYPE_JAGUAR2) {
            vtss_gpio_10g_gpio_mode_t gpio_conf;
            vtss_gpio_10g_no_t gpio_no;
            uint32_t global_dev = 0x1e,lopc_reg = 0xf234,value = 0x13f;

            if ((rc = mesa_sgpio_conf_get(NULL, 0, 2, &conf)) == MESA_RC_OK) {
                switch (board->port[port_no].map.map.chip_port) {
                    case 8:  conf.port_conf[0].mode[0] = sgpio_mode; break;
                    case 9:  conf.port_conf[0].mode[2] = sgpio_mode; break;
                    case 10: conf.port_conf[1].mode[1] = sgpio_mode; break;
                    case 11: conf.port_conf[2].mode[0] = sgpio_mode; break;
                    case 12: conf.port_conf[2].mode[2] = sgpio_mode; break;
                    case 13: conf.port_conf[3].mode[1] = sgpio_mode; break;
                    case 14: conf.port_conf[4].mode[0] = sgpio_mode; break;
                    case 15: conf.port_conf[4].mode[2] = sgpio_mode; break;
                    case 16: conf.port_conf[5].mode[1] = sgpio_mode; break;
                    case 17: conf.port_conf[6].mode[0] = sgpio_mode; break;
                    case 18: conf.port_conf[6].mode[2] = sgpio_mode; break;
                    case 19: conf.port_conf[7].mode[1] = sgpio_mode; break;
                    case 20: conf.port_conf[8].mode[0] = sgpio_mode; break;
                    case 21: conf.port_conf[8].mode[2] = sgpio_mode; break;
                    case 22: conf.port_conf[9].mode[1] = sgpio_mode; break;
                    case 23: conf.port_conf[10].mode[0] = sgpio_mode; break;
                    case 49:
                        gpio_conf.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
                        gpio_no = 28;
                        (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                        gpio_conf.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;
                        gpio_conf.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_CH3_INTR0_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR3_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR3_EN);
                        gpio_conf.c_intrpt = VTSS_10G_GPIO_INTRPT_HPMA;
                        gpio_no = 34;
                        rc = vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                        /* SFP+ TX disable */
                        conf.port_conf[12].mode[0] = sgpio_mode;
                        break;
                    case 50: gpio_conf.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
                        gpio_no = 20;
                        (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                        gpio_conf.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;
                        gpio_conf.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_CH2_INTR0_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR2_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR2_EN);
                        gpio_conf.c_intrpt = VTSS_10G_GPIO_INTRPT_HPMA;
                        gpio_no = 34;
                        rc = vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                        /* SFP+ TX disable */
                        conf.port_conf[12].mode[1] = sgpio_mode;
                        break;
                    case 51: gpio_conf.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
                        gpio_no = 12;
                        (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                        gpio_conf.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;
                        gpio_conf.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_CH1_INTR0_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR1_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR1_EN);
                        gpio_conf.c_intrpt = VTSS_10G_GPIO_INTRPT_HPMA;
                        gpio_no = 34;
                        rc = vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                        /* SFP+ TX disable */
                        conf.port_conf[12].mode[2] = sgpio_mode;
                        break;
                    case 52: gpio_conf.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
                        gpio_no = 4;
                        (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                        gpio_conf.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;
                        gpio_conf.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_CH0_INTR0_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR0_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR0_EN);
                        gpio_conf.c_intrpt = VTSS_10G_GPIO_INTRPT_HPMA;
                        gpio_no = 34;
                        (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                        /* By default GPIO 34 is used as INPUT for LOPC on channel 0,Now as we are changing its default behaviour
                           Configuring registers accordingly */
                        if (vtss_phy_10g_csr_write(PHY_INST,port_no,global_dev,lopc_reg,value) != MESA_RC_OK) {
                            return rc;
                        }
                        /* SFP+ TX disable */
                        conf.port_conf[13].mode[0] = sgpio_mode;
                        break;
                    default:
                        return rc;    // Nothing to do, return
                }
                rc = mesa_sgpio_conf_set(NULL, 0, 2, &conf);
            }
        } else if (board->type == BOARD_TYPE_JAGUAR2_CU48) {
            if ((rc = mesa_sgpio_conf_get(NULL, 0, 2, &conf)) == MESA_RC_OK) {
                /* SFP+ TX disable */
                switch (board->port[port_no].map.map.chip_port) {
                    case 49:
                        conf.port_conf[28].mode[0] = sgpio_mode;
                        break;
                    case 50:
                        conf.port_conf[28].mode[1] = sgpio_mode;
                        break;
                    case 51:
                        conf.port_conf[28].mode[2] = sgpio_mode;
                        break;
                    case 52:
                        conf.port_conf[29].mode[0] = sgpio_mode;
                        break;
                    default:
                        return rc;    // Nothing to do, return
                }
                rc = mesa_sgpio_conf_set(NULL, 0, 2, &conf);

            }

        } else if (board->type == BOARD_TYPE_JAGUAR2_AQR) {
            mesa_bool_t gpio_value = state->enable ? false: true;
            switch (board->port[port_no].map.map.chip_port) {
                /* SFP+ TX disable */
                case 51:
                    rc = mesa_gpio_write(NULL, 0, 23, gpio_value);
                    break;
                case 52:
                    rc = mesa_gpio_write(NULL, 0, 21, gpio_value);
            }
        }
    }
    return rc;
}

static mesa_rc jr2_status_led_set(meba_inst_t inst,
                                  meba_led_type_t type,
                                  meba_led_color_t color)
{
    mesa_rc rc = MESA_RC_ERROR;
    if (type == MEBA_LED_TYPE_FRONT && color < MEBA_LED_COLOR_COUNT) {
        T_D(inst, "LED:%d, color=%d", type, color);
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

static mesa_rc jr2_port_led_update(meba_inst_t inst,
                                   mesa_port_no_t port_no,
                                   const mesa_port_status_t *status,
                                   const mesa_port_counters_t *counters,
                                   const meba_port_admin_state_t *state)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "port(%d): Link - %d", port_no, status->link);
    return board->func->led_update(inst, port_no, status, counters, state);
}

static mesa_rc jr2_led_intensity_set(meba_inst_t inst,
                                     vtss_phy_led_intensity intensity)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    if (jr2_capability(inst, MEBA_CAP_LED_DIM_SUPPORT)) {
        meba_board_state_t *board = INST2BOARD(inst);
        if (board->port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
            /* Both PCB111 and PCB110 uses the first PHY to control the PWM */
            T_N(inst, "Set intensity %d", intensity);
            if (intensity < 30 && intensity > 0) {
                rc = vtss_phy_led_intensity_set(PHY_INST, 0, 30);
            }  else {
                rc = vtss_phy_led_intensity_set(PHY_INST, 0, intensity);
            }
        }
    }
    return rc;
}

static mesa_rc jr2_fan_param_get(meba_inst_t inst,
                                 meba_fan_param_t *param)
{
    T_N(inst, "Called");
    param->start_time = 100;
    param->start_level = 60;
    param->min_pwm = 30;
    return MESA_RC_OK;
}

static mesa_rc jr2_fan_conf_get(meba_inst_t inst,
                                mesa_fan_conf_t *conf)
{
    T_N(inst, "Called");
    meba_board_state_t *board = INST2BOARD(inst);
    *conf = *board->fan_spec;
    return MESA_RC_OK;
}

static mesa_rc jr2_ptp_rs422_conf_get(meba_inst_t inst,
                                      meba_ptp_rs422_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    T_N(inst, "Called");
    meba_board_state_t *board = INST2BOARD(inst);
    if (board->type == BOARD_TYPE_SERVAL2_NID) {
        *conf = serval2_nid_rs422_conf;
    } else if (board->type == BOARD_TYPE_JAGUAR2) {
        *conf = jaguar2_rs422_conf;
    } else {
        *conf = other_rs422_conf;
    }
    return rc;
}

static mesa_rc jr2_ptp_external_io_conf_get(meba_inst_t inst, uint32_t io_pin, meba_ptp_io_cap_t *const board_assignment, meba_event_t *const source_id)

{
    mesa_rc rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);

    if (io_pin >= VTSS_TS_IO_ARRAY_SIZE) {
        return MESA_RC_ERROR;
    }

    if (board->type == BOARD_TYPE_JAGUAR2_CU48)
    {
        *board_assignment = pin_conf_pcb111[io_pin];
    } else {
        *board_assignment = pin_conf[io_pin];
    }
    *source_id = init_int_source_id[io_pin];
    return rc;
}

// IRQ Support

static mesa_bool_t jr2_24_sgpio_maps_to_sfp_port(meba_board_state_t *board,
                                                 uint32_t sgpio,
                                                 mesa_port_no_t *port_no_res)
{
    mesa_port_no_t port_no;

    // SGPIO[p00bx; p15bx] = SFP iports [ 8; 23]
    // SGPIO[p25bx; p28bx] = SFP iports [24; 27]

    if ((sgpio > 15 && sgpio < 25) || sgpio > 28) {
        return false;
    }

    port_no = sgpio < 25 ? sgpio + 8 : sgpio - 1;

    if (port_no >= board->port_cnt) {
        return false;
    }

    if (port_no_res) {
        *port_no_res = port_no;
    }

    return is_sfp_port(board->port[port_no].map.cap);
}

static mesa_rc jr2_phy_event_enable(meba_inst_t inst,
                                    meba_board_state_t *board,
                                    vtss_phy_event_t phy_event,
                                    mesa_bool_t enable)
{
    mesa_port_no_t port_no;
    mesa_rc rc = MESA_RC_OK;
    T_D(inst, "%sable phy event %d on all ports", enable ? "en" : "dis", phy_event);
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (is_phy_port(board->port[port_no].map.cap)) {
            T_N(inst, "%sable phy event %d on port %d", enable ? "en" : "dis", phy_event, port_no);
            if (!board->aqr_sb_present && !board->gpy241_sb_present) {
                if ((rc = vtss_phy_event_enable_set(PHY_INST, port_no, phy_event, enable)) != MESA_RC_OK) {
                    T_E(inst, "vtss_phy_event_enable_set = %d", rc);
                    break;
                }
            }
        }
    }
    return rc;
}

static mesa_rc jr2_event_enable(meba_inst_t inst,
                                meba_event_t event_id,
                                mesa_bool_t enable)
{
    mesa_rc               rc = MESA_RC_OK;
    meba_board_state_t    *board = INST2BOARD(inst);
    mesa_ptp_event_type_t ptp_event;
    int                   gpio, sgpio;
    mesa_port_no_t        port_no;
    uint32_t              bit;

    T_I(inst, "%sable event %d", enable ? "en" : "dis", event_id);

    switch (event_id) {
        case MEBA_EVENT_SYNC:
        case MEBA_EVENT_EXT_SYNC:
        case MEBA_EVENT_EXT_1_SYNC:
        case MEBA_EVENT_CLK_ADJ:
        case MEBA_EVENT_VOE:
            return rc;    // Dummy for now

        case MEBA_EVENT_MOD_DET:
            if (enable) {    // Only ENABLE sgpio path if enabling
                switch (board->type) {
                    case BOARD_TYPE_JAGUAR2:
                        if (jr2_sgpio_event_enable(inst, 2, 24, 2, enable) != MESA_RC_OK) {
                            T_E(inst, "Could not enable event for sgpio #24");
                        }
                        break;
                    default:
                        break;
                }
            }
            break;

        case MEBA_EVENT_LOS:
            if (enable) {    // Only ENABLE sgpio path if enabling
                switch (board->type) {
                    case BOARD_TYPE_JAGUAR2:
                        for (sgpio = 0; sgpio <= 28; sgpio++) {
                            // UG1053, VSC5628EV, Table 17, where x can be 0 (Loss of Signal; LOS), 1 (MODDETn; 0 = SFP present), 2 (TX_FAULT).
                            // SGPIO[p00bx; p15bx] = SFP iports [ 8; 23]
                            // SGPIO[p25bx; p28bx] = SFP iports [24; 27]
                            if (jr2_24_sgpio_maps_to_sfp_port(board, sgpio, NULL)) {
                                if (jr2_sgpio_event_enable(inst, 2, sgpio, 0, enable) != MESA_RC_OK) {
                                    T_E(inst, "Could not enable event for sgpio #%d", sgpio);
                                }
                            }
                        }
                        break;

                    case BOARD_TYPE_SERVAL2_NID:
                        for (gpio = 44; gpio <= 59; gpio++) {
                            if (gpio > 49 && gpio < 56) {
                                continue;
                            }

                            if (mesa_gpio_event_enable(NULL, 0, gpio, enable) != MESA_RC_OK) {
                                // Enable GPIOs for SFP LOS
                                T_E(inst, "Could not enable event for gpio #%d", gpio);
                            }
                        }
                        break;

                    case BOARD_TYPE_JAGUAR2_CU48:
                        for (gpio = 52; gpio <= 55; gpio++) {
                            if (mesa_gpio_event_enable(NULL, 0, gpio, enable) != MESA_RC_OK) {
                                // Enable GPIOs for 10G SFP LOS
                                T_D(inst, "Could not enable event for gpio #%d", gpio);
                            }
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case MEBA_EVENT_FLNK:
            if (enable) {    // Only ENABLE sgpio path if enabling
                if (board->type == BOARD_TYPE_JAGUAR2) {
                    // UG1053, VSC5628EV, Table 17, where
                    //   p24b0 = nINT from iport 0-3
                    //   p24b1 = nINT from iport 4-7
                    for (bit = 0; bit <= 1; bit++) {
                        if (jr2_sgpio_event_enable(inst, 2, 24, bit, enable) != MESA_RC_OK) {
                            T_E(inst, "Could not enable event for bit #%d", bit);
                        }
                    }
                } else if (board->type == BOARD_TYPE_JAGUAR2_CU48) {
                    // TABLE 11 in UG10153 - // p24b0 = nINT_PHY0 (ports 1-12), p24b1 = nINT_PHY1 (ports 13-24), P25b0 = nINT_PHY2 (ports 25-36), p26b0 = nINT_PHY3 (ports 37-48)
                    rc += jr2_sgpio_event_enable(inst, 2, 24, 0, enable); // nINT_PHY0 (ports 1-12)
                    rc += jr2_sgpio_event_enable(inst, 2, 24, 1, enable); // nINT_PHY1 (ports 13-24)
                    rc += jr2_sgpio_event_enable(inst, 2, 25, 0, enable); // nINT_PHY2 (ports 25-36)
                    rc += jr2_sgpio_event_enable(inst, 2, 26, 0, enable); // nINT_PHY3 (ports 37-48)

                    if (rc != MESA_RC_OK) {
                        T_E(inst, "Could not enable event");
                    }
                }
            }
            rc = jr2_phy_event_enable(inst, board, VTSS_PHY_LINK_FFAIL_EV, enable);
            break;

        case MEBA_EVENT_AMS:
            rc = MESA_RC_ERROR;    // No dual-media ports
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
        case MEBA_EVENT_EGR_FIFO_OVERFLOW: {
            mepa_ts_event_t event = meba_generic_phy_ts_source_to_event(inst, event_id);

            if (board->type == BOARD_TYPE_JAGUAR2) {
                if (enable) {
                    if ((rc = jr2_sgpio_event_enable(inst, 2, 24, 0, enable)) != MESA_RC_OK) {  /* Enable SGPIOs for 1G PHY port 1-4 events */
                        T_E(inst, "jr2_sgpio_event_enable = %d", rc);
                    }
                    if ((rc = jr2_sgpio_event_enable(inst, 2, 24, 1, enable)) != MESA_RC_OK) {  /* Enable SGPIOs for 1G PHY port 5-8 events */
                        T_E(inst, "jr2_sgpio_event_enable = %d", rc);
                    }
                }
                if (board->phy10g_ts_cnt != 0) {
                    if (enable) {
                        if ((rc = jr2_sgpio_event_enable(inst, PHY10G_SGPIO_GROUP, PHY10G_SGPIO_PORT, PHY10G_SGPIO_BIT, enable)) != MESA_RC_OK) {
                            // Enable SGPIOs for MALIBU events
                            T_E(inst, "mesa_sgpio_event_enable = %d", rc);
                        }
                    }
                    for (port_no = 0; port_no < board->port_cnt; port_no++) {
                        if (is_10g_port(board->port[port_no].map.cap)) {
                            meba_phy_ts_event_set(inst, port_no, enable, event);
                        }
                    }
                }
            }
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (board->port[port_no].ts_phy) {
                    meba_phy_ts_event_set(inst, port_no, enable, event);
                }
            }
            break;
        }

        case MEBA_EVENT_PUSH_BUTTON:
            switch (board->type) {
                case BOARD_TYPE_JAGUAR2:
                case BOARD_TYPE_JAGUAR2_CU48:
                    gpio = 48;
                    break;

                case BOARD_TYPE_SERVAL2_NID:
                    gpio = 5;
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

    return rc;
}

static void push_button(meba_inst_t inst, uint32_t gpio, meba_event_signal_t signal_notifier)
{
    mesa_rc     rc;
    T_I(inst, "Got interrupt from GPIO_%d(push button)", gpio);
    if ((rc = mesa_gpio_event_enable(NULL, 0, gpio, false)) != MESA_RC_OK) {
        T_E(inst, "mesa_gpio_event_enable = %d", rc);
    }
    signal_notifier(MEBA_EVENT_PUSH_BUTTON, 0);
}

static mesa_rc gpio_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    uint32_t    gpio, instance_no = 0;
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
        case BOARD_TYPE_SERVAL2_NID:
            for (gpio = 44; gpio <= 59; gpio++) {
                if (gpio > 49 && gpio < 56) {
                    continue;
                }
                if (gpio_events[gpio]) {
                    instance_no = (gpio <= 49) ? (gpio - 40) : (gpio - 46);
                    // Only react on a LOS event
                    if (gpio_state[gpio]) {
                        // Disable the interrupt while handling the event
                        (void) mesa_gpio_event_enable(NULL, 0, gpio, false);
                        T_I(inst, "Got interrupt from gpio #%u, sfp #%u", gpio, instance_no);
                        signal_notifier(MEBA_EVENT_LOS, instance_no);
                    } else {
                        T_I(inst, "Ignore inactive LOS, gpio #%u, sfp #%u", gpio, instance_no);
                    }
                    handled++;
                }
            }

            // Check Front panel button on GPIO5
            if (gpio_events[5]) {
                push_button(inst, 5, signal_notifier);
                handled++;
            }
            break;

        case BOARD_TYPE_JAGUAR2_CU48:
        case BOARD_TYPE_JAGUAR2_AQR:
            for (gpio = 52; gpio <= 55; gpio++) {
                if (gpio_events[gpio]) {
                    switch (gpio) {
                        case 52:
                            instance_no = 49;
                            break;

                        case 53:
                            instance_no = 48;
                            break;

                        case 54:
                            instance_no = 51;
                            break;

                        case 55:
                            instance_no = 50;
                            break;
                    }

                    handled++;    // Allways handled
                    if (instance_no < board->port_cnt && is_sfp_port(board->port[instance_no].map.cap)) {
                        // Only react on a LOS event
                        if (gpio_state[gpio]) {
                            // Disable the interrupt while handling the event
                            (void) mesa_gpio_event_enable(NULL, 0, gpio, false);
                            T_I(inst, "Got interrupt from gpio #%u, sfp #%u", gpio, instance_no);
                            signal_notifier(MEBA_EVENT_LOS, instance_no);
                        } else {
                            T_I(inst, "Ignore inactive LOS, gpio #%u, sfp #%u", gpio, instance_no);
                        }
                    } else {
                        T_D(inst, "Ignore IRQ on inactive port %d", instance_no);
                    }
                }
            }
            // Fallthrough!

        case BOARD_TYPE_JAGUAR2:
            // Check Front panel button on GPIO48
            if (gpio_events[48]) {
                push_button(inst, 48, signal_notifier);
                handled++;
            }
            break;

        default:
            T_E(inst, "Board type (%d) not supported!", board->type);
            return MESA_RC_ERROR;
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc sgpio2_handler(meba_inst_t inst,
                              meba_board_state_t *board,
                              meba_event_signal_t signal_notifier)
{
    mesa_rc           rc;
    mesa_port_no_t    port_no, start_port, end_port;
    uint32_t          bit, sgpio_port;
    mesa_bool_t       sgpio_events_bit[3][MESA_SGPIO_PORTS];
    int               i, handled = 0;
    mesa_bool_t       chk_phys[48];
    vtss_phy_10g_event_t events;

    // Getting SGPIO bit 0 - 2 (see UG1053 Table 17, p24 b0 + b1)
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
                if ((rc = jr2_sgpio_event_enable(inst, 2, sgpio_port, bit, false)) != MESA_RC_OK) {
                    T_E(inst, "mesa_sgpio_event_enable = %d", rc);
                    // Go on anyway
                }
            }
        }
    }

    switch (board->type) {
        case BOARD_TYPE_JAGUAR2:
            start_port = MESA_PORT_NO_NONE;
            end_port   = MESA_PORT_NO_NONE;

            // Determine which of the event bits were set (see UG1053 Table 17, p24b0 + p24b1)
            if (sgpio_events_bit[0][24]) {
                start_port = 0;
                end_port   = 3; // nINT_PHY1 (PHY for ports 1-4)
            }

            if (sgpio_events_bit[1][24]) {
                if (start_port == MESA_PORT_NO_NONE) {
                    start_port = 4;
                }

                end_port = 7; // nINT_PHY2 (PHY for ports 5-8)
            }

            T_D(inst, "start_port = %u, sgpio_event_bit[0][24] = %d sgpio_event_bit[1][24] = %d", start_port, sgpio_events_bit[0][24], sgpio_events_bit[1][24]);

            // Read PHYs if the interrupt was from one of the PHYs
            if (start_port != MESA_PORT_NO_NONE) {
                for (port_no = start_port; port_no <= end_port; port_no++) {
                    if (board->port[port_no].ts_phy) {
                        if (meba_generic_phy_timestamp_check(inst, port_no, signal_notifier) == MESA_RC_OK)
                            handled++;
                    }
                }

                // Check for Cu Phy events (ports 0-7)
                for (port_no = start_port; port_no <= end_port; port_no++) {
                    meba_port_entry_t *entry = &board->port[port_no].map;
                    if (is_phy_port(entry->cap)) {
                        if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK)
                            handled++;
                    }
                }
            }

            // Check for SFP/SFP+ LOS (SGMII ports: 1G:8-23 (p0b0-p15b0) + 10G:25-28 (p25b0-p28b0))
            for (sgpio_port = 0; sgpio_port <= 28; sgpio_port++) {
                mesa_bool_t port_handled = false;
                if (sgpio_events_bit[0][sgpio_port]) {
                    if (jr2_24_sgpio_maps_to_sfp_port(board, sgpio_port, &port_no)) {
                        signal_notifier(MEBA_EVENT_LOS, port_no);
                        port_handled = true;
                        handled++;
                    }
                }
                // Check MODDET
                if (sgpio_events_bit[2][sgpio_port]) {
                    if (!port_handled &&
                        jr2_24_sgpio_maps_to_sfp_port(board, sgpio_port, &port_no)) {
                        // LOS, MODDET and TX_FAULT all share the same interrupt,
                        // so some signal notifier needs to be called to ensure
                        // that interrupts are reenabled. When module is either
                        // removed or inserted there is no harm in calling the LOS
                        // signal handler and let that reenable interrupts.
                        handled++;
                        signal_notifier(MEBA_EVENT_LOS, port_no);
                        port_handled = true;
                    }
                    for (port_no = 0; port_no < board->port_cnt; port_no++) {
                        if (is_10g_port(board->port[port_no].map.cap)) {
                            if (vtss_phy_10g_event_poll(NULL, port_no, &events) == MESA_RC_OK) {
                                if(events == VTSS_PHY_10G_MODULE_STAT_EV) {
                                    signal_notifier(MEBA_EVENT_MOD_DET, port_no);
                                    handled++;
                                }
                            }
                        }
                    }
                }

                // Check TXFAULT
                if (sgpio_events_bit[1][sgpio_port]) {
                    if (jr2_24_sgpio_maps_to_sfp_port(board, sgpio_port, &port_no)) {
                        T_D(inst, "TXFAULT seen on port %d, ignored", port_no);
                    }
                    if (!port_handled &&
                        jr2_24_sgpio_maps_to_sfp_port(board, sgpio_port, &port_no)) {
                        // LOS, MODDET and TX_FAULT all share the same interrupt,
                        // so some signal notifier needs to be called to ensure
                        // that interrupts are reenabled. When TXFAULT is detected
                        // there is no harm in calling the LOS
                        // signal handler and let that reenable interrupts.
                        handled++;
                        signal_notifier(MEBA_EVENT_LOS, port_no);
                        port_handled = true;
                    }
                }
            }

            // Check for timestamp event
            if (board->phy10g_ts_cnt && sgpio_events_bit[PHY10G_SGPIO_GROUP][PHY10G_SGPIO_PORT]) {
                for (port_no = 0; port_no < board->port_cnt; port_no++) {
                    if (is_10g_port(board->port[port_no].map.cap)) {
                        if (meba_generic_phy_timestamp_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                            T_D(inst, "port(%d) PHY TS IRQ handled", port_no);
                            handled++;
                        }
                    }
                }
            }

            break;

        case BOARD_TYPE_JAGUAR2_CU48:
            memset(chk_phys, 0, sizeof(chk_phys));

            // Determine which of the event bits were set (See UG1053 Table 17, p24 b0 + b1)
            if (sgpio_events_bit[0][24]) {
                for (i = 0; i < 12; i++) {
                    chk_phys[i] = true;
                }
            }

            if (sgpio_events_bit[1][24]) {
                for (i = 12; i < 24; i++) {
                    chk_phys[i] = true;
                }
            }

            if (sgpio_events_bit[0][25]) {
                for (i = 24; i < 36; i++) {
                    chk_phys[i] = true;
                }
            }

            if (sgpio_events_bit[0][26]) {
                for (i = 36; i < 48; i++) {
                    chk_phys[i] = true;
                }
            }

            // Check for Cu Phy events (ports 0-47)
            for (port_no = 0; port_no <= 47; port_no++) {
                if (chk_phys[port_no] && is_phy_port(board->port[port_no].map.cap)) {
                    if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                        T_D(inst, "port(%d) IRQ handled", port_no);
                        handled++;
                    }
                }
            }

            // Handle SGPIO "false" shared IRQs
            if (!handled) {
                int bit, i;
                for (bit = 24; bit <= 26; bit++) {
                    for (i = 0; i <= 2; i++) {
                        if (sgpio_events_bit[i][bit]) {
                            T_D(inst, "False IRQ ignored, bit p%d.b%d", bit, i);
                            handled++;
                            break;
                        }
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

static mesa_rc ext1_handler(meba_inst_t inst,
                            meba_board_state_t *board,
                            meba_event_signal_t signal_notifier)
{
    int handled = 0;
    mesa_port_no_t port_no;
    // NB: Shared output from the VSC8584 and VSC8221
    // PHYs,DS26503 T1/E1/J1 framer and ZL30343 Sync-E
    // controller. When an interrupt occurs, software must
    // poll the possible sources for their current
    // interrupt status e.g. through MII or SPI, as it is
    // otherwise not possible to distinguish which source
    // has activated the shared interrupt signal
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (is_phy_port(board->port[port_no].map.cap)) {
            if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                T_D(inst, "port(%d) PHY IRQ handled", port_no);
                handled++;
            }
        }
        if (board->port[port_no].ts_phy) {
            if (meba_generic_phy_timestamp_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                T_D(inst, "port(%d) PHY TS IRQ handled", port_no);
                handled++;
            }
        }
    }
    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc jr2_irq_handler(meba_inst_t inst,
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
        case MESA_IRQ_EXT1:
            return ext1_handler(inst, board, signal_notifier);
        default:;
    }

    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc jr2_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
        case MESA_IRQ_PTP_RDY:
        case MESA_IRQ_OAM:
        case MESA_IRQ_GPIO:
        case MESA_IRQ_SGPIO2:
        case MESA_IRQ_EXT1:
            rc = MESA_RC_OK;
        default:;
    }
    return rc;
}

static void i2c_add_sym_link(meba_inst_t inst, uint32_t port, uint32_t cap,
                             uint32_t vport)
{
    /* Create a i2c symlink to ensure that the first i2c id starts at 100 */
    if (cap & MEBA_PORT_CAP_SFP_DETECT) {
        char str1[20], str2[20];
        sprintf(str2, "%s%d", "/dev/i2c-", port + 100);
        // First 3 i2c adapter are created by default by linux kernel
        // First 8 ports are not SFP ports, therefore
        // the next generated i2c adapter is at port + 3 - 8.
        sprintf(str1, "%s%d", "/dev/i2c-", vport + 3 - 8); // First SFP i2c adapter assigned by device tree
        if (symlink(str1, str2) != 0) {
            T_E(inst, "Could not create symlink %s to %s\n", str1, str2);
        }
    }
}

// Public Initialize

meba_inst_t meba_initialize(size_t callouts_size,
                            const meba_board_interface_t *callouts)
{
    meba_inst_t         inst;
    meba_board_state_t *board;
    mesa_port_no_t      port_no;
    int                 i=0;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate public state
    if ((inst = meba_state_alloc(callouts,
                                 "Jaguar-2",
                                 MESA_TARGET_JAGUAR_2,
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);

    if (meba_conf_get_hex(inst, "type", &i) == MESA_RC_OK) {
        board->type = (board_type_t) i;
    } else {
        board->type = BOARD_TYPE_JAGUAR2;   // Default
    }
    if (meba_conf_get_hex(inst, "port_cfg", &i) == MESA_RC_OK) {
        board->port_cfg = (vtss_board_port_cfg_t) i;
    } else {
        board->port_cfg = VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI;   // Default
    }
    // Initialize Malibu/AQR side board presence to false
    board->malibu_present = false;
    board->aqr_sb_present = 0;
    board->gpy241_sb_present = 0;

    inst->props.mux_mode = MESA_PORT_MUX_MODE_AUTO;    // Default
    switch (board->type) {
        case BOARD_TYPE_SERVAL2_NID:
            board->port_cnt = 15;
            break;
        case BOARD_TYPE_JAGUAR2_CU48:
            if (inst->props.target == MESA_TARGET_SPARX_IV_90 || inst->props.target == MESA_TARGET_SPARX_IV_52) {
                board->port_cnt = 53;
                inst->props.mux_mode = MESA_PORT_MUX_MODE_2;
            } else {
                board->port_cnt = 51;
            }
            // Configure GPIOs for MIIM/MDI
            for (i = 56; i < 60; i++) {
                mebaux_gpio_mode_set(inst, &rawio, i, MESA_GPIO_ALT_0);
            }
            break;
        case BOARD_TYPE_JAGUAR2:
            switch (board->port_cfg) {
                case VTSS_BOARD_CONF_24x2G5_2xSFI_NPI:
                    board->port_cnt = 27;
                    inst->props.mux_mode = MESA_PORT_MUX_MODE_1;
                    break;
                case VTSS_BOARD_CONF_20x1G_4x2G5_2xSFI_NPI:
                    board->port_cnt = 27;
                    break;
                case VTSS_BOARD_CONF_16x2G5_4xSFI_NPI:
                    if (inst->props.target == MESA_TARGET_SPARX_IV_44) {
                        board->port_cnt = 19;
                    } else {
                        board->port_cnt = 21;
                    }
                    inst->props.mux_mode = MESA_PORT_MUX_MODE_0;
                    break;
                case VTSS_BOARD_CONF_DEFAULT_VENICE_1G_MODE:
                case VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI:
                default:
                    board->port_cnt = 29;
                    // Detect AQR side board exist
                    jr2_aqr_side_board_detect(inst);
                    jr2_gpy241_side_board_detect(inst);
            }
            break;
        case BOARD_TYPE_JAGUAR2_AQR:
            board->port_cnt = 26;
            inst->props.mux_mode = MESA_PORT_MUX_MODE_1;
            break;
        default:
            T_E(inst, "Unknown board type: %d", board->type);
            goto error_out;
    }

    board->func = &board_funcs[board->type];

    board->port = (jr2_port_info_t*) calloc(board->port_cnt, sizeof(jr2_port_info_t));
    if (board->port == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }

    inst->props.board_type = (vtss_board_type_t) (VTSS_BOARD_SERVAL2_NID_REF + board->type);    // Exposed temporarily
    board->fan_spec = &fan_conf;

    mesa_bool_t ls1046_board = (access("/proc/vc3fdma", F_OK) == 0) ? false : true;

    /* Fill out port mapping table */
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        board->func->init_port(inst, port_no, &board->port[port_no].map);

        if (ls1046_board) {
            i2c_add_sym_link(inst, board->port[port_no].map.map.chip_port, board->port[port_no].map.cap, port_no);
        }
    }

    T_I(inst, "Board: %s, type %d, target %4x, mux %d, %d ports", inst->props.name, board->type, inst->props.target,
        inst->props.mux_mode, board->port_cnt);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                     = jr2_capability;
    inst->api.meba_port_entry_get                 = jr2_port_entry_get;
    inst->api.meba_reset                          = jr2_reset;
    inst->api.meba_sensor_get                     = jr2_sensor_get;
    inst->api.meba_sfp_i2c_xfer                   = jr2_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get       = jr2_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get                 = jr2_sfp_status_get;
    inst->api.meba_port_admin_state_set           = jr2_port_admin_state_set;
    inst->api.meba_status_led_set                 = jr2_status_led_set;
    inst->api.meba_port_led_update                = jr2_port_led_update;
    inst->api.meba_led_intensity_set              = jr2_led_intensity_set;
    inst->api.meba_fan_param_get                  = jr2_fan_param_get;
    inst->api.meba_fan_conf_get                   = jr2_fan_conf_get;
    inst->api.meba_irq_handler                    = jr2_irq_handler;
    inst->api.meba_irq_requested                  = jr2_irq_requested;
    inst->api.meba_event_enable                   = jr2_event_enable;
    inst->api.meba_deinitialize                   = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get             = jr2_ptp_rs422_conf_get;
    inst->api.meba_ptp_external_io_conf_get       = jr2_ptp_external_io_conf_get;

    inst->api_synce = meba_synce_get();
    inst->api_tod = meba_tod_get();
    inst->api_poe = meba_poe_get();

    return inst;

error_out:
    free(inst);
    return NULL;
}
