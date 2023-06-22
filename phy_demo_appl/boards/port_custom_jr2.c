// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// Avoid "*.h not used in module port_custom_jr2.c"
/*lint --e{766} */
/*lint -sem(jr2_reset,          thread_protected) */
#include "port_custom_api.h"
#include "board_probe.h"
//#if defined(VTSS_SW_OPTION_PHY)
//#include "phy_api.h" // For PHY_INST
//#else
#define PHY_INST NULL
//#endif
//#include "../base/phy/phy_1g/vtss_phy.h" // For PHY registers defines
#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C)
#define VTSS_RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }
#if 0 // defined(VTSS_TRACE_ENABLE)
#define VTSS_TRACE_MODULE_ID VTSS_MODULE_ID_API_AI
#define CUSTOM_D(...)  T_D(__VA_ARGS__)
#define CUSTOM_I(...)  T_I(__VA_ARGS__)
#define CUSTOM_N(...)  T_N(__VA_ARGS__)
#define CUSTOM_E(...)  T_E(__VA_ARGS__)
#else
#define CUSTOM_D(...)
#define CUSTOM_I(...)
#define CUSTOM_N(...)
#define CUSTOM_E(...)
#endif
/*lint -esym(459, jr2_i2c_read) OK not to protect jr2_i2c_read with semaphore in this file */
static vtss_i2c_read_t    jr2_i2c_read;     /**< I2C read function */

/*lint -esym(459, jr2_i2c_write) OK not to protect jr2_i2c_write with semaphore in this file */
static vtss_i2c_write_t   jr2_i2c_write;    /**< I2C write function */

/*lint -esym(459, jr2_port_table) */
static port_custom_entry_t jr2_port_table[VTSS_PORT_ARRAY_SIZE];

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
    vtss_port_counters_t cnt;
    vtss_port_status_t   status;
    BOOL                 activity;
} jr2_port_info_t;

/* 10G PHY detection data */
typedef struct  {
    vtss_port_no_t port_no;       /* Port number (debugging) */
    u8             miim_addr[2];  /* MIIM address */
    BOOL           miim_found[2]; /* MIIM address */
    port_cap_t     cap;           /* Port capability */
} jr2_10g_detect_t;

/*lint -esym(459, jr2_old_port_info) */
static jr2_port_info_t jr2_old_port_info[VTSS_PORT_ARRAY_SIZE];

/*lint -esym(459, jr2_board_type) */
static int jr2_board_type;
static vtss_board_port_cfg_t port_cfg;

/* Jaguar NPI chip port */
#define JR2_NPI_CHIP_PORT 48

/* SGPIO LED mapping */
typedef struct {
    u8  port;
    u8  bit;
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

/* Jaguar-2 register targets and addresses */
#define JR2_TGT_GCB            0x01
#define JR2_ADDR_CHIP_ID       0x02
#define JR2_ADDR_GPIO_OUT      0x12
#define JR2_ADDR_GPIO_IN       0x14
#define JR2_ADDR_GPIO_OE       0x16
#define JR2_ADDR_GPIO_ALT_0    0x1E
#define JR2_ADDR_GPIO_ALT_1    0x1F
#define JR2_ADDR_GPIO_ALT1_0   0x20
#define JR2_ADDR_GPIO_ALT1_1   0x21

#define JR2_ADDR_MIIM_STATUS   0x32
#define JR2_ADDR_MIIM_CMD      0x34
#define JR2_ADDR_MIIM_DATA     0x35
#define JR2_ADDR_MIIM_CFG      0x36

/* Read from primary device */
static vtss_rc jr2_rd(u32 tgt, u32 addr, u32 *value, vtss_board_info_t *board_info)
{
    vtss_rc rc = VTSS_RC_ERROR;

    *value = 0xdeadbeef;
    if (board_info->reg_read != NULL) {
        rc = board_info->reg_read(0, (tgt << 22) + (tgt << 14) + addr, value);
        CUSTOM_D("tgt: 0x%x, addr: 0x%x, value: 0x%08x", tgt, (tgt << 22) + (tgt << 14) + addr, *value);
    }
    return rc;
}

/* Write to primary device */
static vtss_rc jr2_wr(u32 tgt, u32 addr, u32 value, vtss_board_info_t *board_info)
{
    vtss_rc rc = VTSS_RC_ERROR;

    if (board_info->reg_write != NULL) {
        CUSTOM_D("tgt: 0x%x, addr: 0x%x, combined: 0x%x value: 0x%08x", tgt, addr,((tgt << 14) + (tgt << 14) + addr), value);
        rc = board_info->reg_write(0, (tgt << 22) + (tgt << 14) + addr, value);
    }
    return rc;
}

#define PHY_CMD_ADDRESS  0 /* 10G: Address */
#define PHY_CMD_WRITE    1 /* 1G/10G: Write */
#define PHY_CMD_READ_INC 2 /* 1G: Read, 10G: Read and increment */
#define PHY_CMD_READ     3 /* 10G: Read */

/* MIIM bus command function for primary device */
static vtss_rc jr2_miim_cmd(u8 cmd, u8 sof, u8 ctrl, u8 miim_addr, u8 reg_addr, u16 *data,
                            vtss_board_info_t *board_info)
{
    vtss_rc rc;
    u32     value, offs = (ctrl * 9);
    int     i;

    CUSTOM_D("cmd: %u, sof: %u, ctrl: %u, miim_addr: %u, reg_addr: %u",  cmd, sof, ctrl, miim_addr, reg_addr);

    rc = jr2_wr(JR2_TGT_GCB, JR2_ADDR_MIIM_CFG + offs, (sof<<9) | (0x32<<0), board_info);


    if (rc != VTSS_RC_OK)
        return rc;

    rc = jr2_wr(JR2_TGT_GCB, JR2_ADDR_MIIM_CMD + offs,
                (1UL<<31) | (u32)(miim_addr<<25) | (reg_addr<<20) | ((*data)<<4) | (cmd<<1),
               board_info);


    if (rc != VTSS_RC_OK)
        return rc;

    for (i = 0; i < 100; i++) {
        rc = jr2_rd(JR2_TGT_GCB, JR2_ADDR_MIIM_STATUS + offs, &value, board_info);
        if (rc != VTSS_RC_OK)
            return rc;
        if (value != 0)
            continue;

        if (cmd == PHY_CMD_READ_INC || cmd == PHY_CMD_READ) {
            rc = jr2_rd(JR2_TGT_GCB, JR2_ADDR_MIIM_DATA + offs, &value, board_info);
            if (rc != VTSS_RC_OK)
                return rc;
            if (value & 0x30000)
                break;
            *data = (value & 0xffff);
        }
        return VTSS_RC_OK;
    }
    return VTSS_RC_ERROR;
}

/* Read PHY register on primary device */
static vtss_rc jr2_miim_rd(u8 ctrl, u8 miim_addr, u8 reg_addr, u16 *data,
                           vtss_board_info_t *board_info)
{
    return jr2_miim_cmd(PHY_CMD_READ_INC, 1, ctrl, miim_addr, reg_addr, data, board_info);
}

/* Detect Vitesse 10G PHY module on MIIM controller 0 */
static vtss_miim_controller_t jr2_phy_detect(u8 miim_addr, vtss_board_info_t *board_info)
{
    u16 tmp = 0;
    u8 ctrl;
    for (ctrl = 0; ctrl < 2; ctrl++) {
        if (jr2_miim_rd(ctrl, miim_addr, 0, &tmp, board_info) == VTSS_RC_OK) {
            return (ctrl == 0 ? VTSS_MIIM_CONTROLLER_0 : VTSS_MIIM_CONTROLLER_1);
        }
    }
    CUSTOM_D("Did not find an NPI Phy\n");
    return VTSS_MIIM_CONTROLLER_NONE; // Nothing found
}

/* Read MMD register on primary device */
static vtss_rc jr2_mmd_rd(u8 ctrl, u8 miim_addr, u8 mmd, u16 addr, u16 *value,
                          vtss_board_info_t *board_info)
{
    vtss_rc rc;

    rc = jr2_miim_cmd(PHY_CMD_ADDRESS, 0, ctrl, miim_addr, mmd, &addr, board_info);
    if (rc == VTSS_RC_OK)
        rc = jr2_miim_cmd(PHY_CMD_READ, 0, ctrl, miim_addr, mmd, value, board_info);
    return rc;
}


/* Detect Vitesse 10G PHY module on MIIM controller 0 */
static BOOL jr2_10g_detect(jr2_10g_detect_t *detect, vtss_board_info_t *board_info)
{
    u16 model, miim;
    u8 ctrl = 0;

    if (detect->miim_found[1]) {
        // Already found a VTSS PHY in previous round, just return the miim address
        detect->miim_addr[0] = detect->miim_addr[1];
        detect->cap = (PORT_CAP_VTSS_10G_PHY | PORT_CAP_10G_FDX | PORT_CAP_FLOW_CTRL | PORT_CAP_XAUI_LANE_FLIP | PORT_CAP_1G_FDX);
        return 1;
    }

    // Scan the miim bus for PHY targets, they come in pairs..
    for (miim = 0; miim < 32; miim++) {
        if (jr2_mmd_rd(ctrl, miim, 30, 0, &model, board_info) == VTSS_RC_OK) {
            if (model == 0x8484 || model == 0x8487 || model == 0x8488 ||
                model == 0x8489 || model == 0x8490 || model == 0x8491) {
                CUSTOM_D("Found VTSS PHY model 0x%x at port_no %u", model, detect->port_no);
                if (!detect->miim_found[0]) {
                    detect->miim_addr[1] = miim; // need to swap the channels to get them inline with JR2 ports
                    detect->miim_found[0] = 1;
                    detect->cap |= (PORT_CAP_VTSS_10G_PHY | PORT_CAP_1G_FDX | PORT_CAP_10G_FDX | PORT_CAP_FLOW_CTRL | PORT_CAP_XAUI_LANE_FLIP);
//                    detect->cap = (PORT_CAP_VTSS_10G_PHY | PORT_CAP_10G_FDX | PORT_CAP_FLOW_CTRL | PORT_CAP_XAUI_LANE_FLIP);
                } else {
                    detect->miim_addr[0] = miim;
                    detect->miim_found[1] = 1;
                    return 1;
                }
            }
        }
    }
    // VTSS Phy not found, look for X2 or Xenpak module at the given miim_addr
    if (jr2_mmd_rd(ctrl, detect->miim_addr[0], 1, 0, &model, board_info) == VTSS_RC_OK) {
        CUSTOM_D("Found XAUI device at at miim address:%d port_no %u", detect->miim_addr[0], detect->port_no);
        detect->cap = (PORT_CAP_10G_FDX | PORT_CAP_FLOW_CTRL | PORT_CAP_XAUI_LANE_FLIP);
        return 1;
    }
    return 0; // Nothing found
}



static void jr2_init_cu48(void)
{
    vtss_sgpio_conf_t conf;
    u32 port, gpio_no, bit;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 56; gpio_no < 60; gpio_no++) {
        (void)vtss_gpio_mode_set(NULL, 0, gpio_no, VTSS_GPIO_ALT_0);
    }

    /* GPIO pins 0-3,4-5,30-33 are used for SGPIOs. */
    (void)vtss_gpio_mode_set(NULL, 0,  0, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)vtss_gpio_mode_set(NULL, 0,  1, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)vtss_gpio_mode_set(NULL, 0,  2, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)vtss_gpio_mode_set(NULL, 0,  3, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / LD
    (void)vtss_gpio_mode_set(NULL, 0,  4, VTSS_GPIO_ALT_0);  // SGPIO Grp 1 / CLK
    (void)vtss_gpio_mode_set(NULL, 0,  5, VTSS_GPIO_ALT_0);  // SGPIO Grp 1 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 30, VTSS_GPIO_ALT_0);  // SGPIO Grp 2 / Clk
    (void)vtss_gpio_mode_set(NULL, 0, 31, VTSS_GPIO_ALT_0);  // SGPIO Grp 2 / LD
    (void)vtss_gpio_mode_set(NULL, 0, 32, VTSS_GPIO_ALT_0);  // SGPIO Grp 2 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 33, VTSS_GPIO_ALT_0);  // SGPIO Grp 2 / DI
    (void)vtss_gpio_mode_set(NULL, 0, 52, VTSS_GPIO_IN_INT); // Enable 10G SFP Los Intr
    (void)vtss_gpio_mode_set(NULL, 0, 53, VTSS_GPIO_IN_INT); // Enable 10G SFP Los Intr
    (void)vtss_gpio_mode_set(NULL, 0, 54, VTSS_GPIO_IN_INT); // Enable 10G SFP Los Intr
    (void)vtss_gpio_mode_set(NULL, 0, 55, VTSS_GPIO_IN_INT); // Enable 10G SFP Los Intr

    /* Setup SGPIO group 0 */
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 2;
        for (port = 0; port < VTSS_SGPIO_PORTS; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  VTSS_SGPIO_MODE_ON;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    /* Setup SGPIO group 1 */
    if (vtss_sgpio_conf_get(NULL, 0, 1, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 2;
        // QSGMII ports
        for (port = 0; port < 16; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  VTSS_SGPIO_MODE_ON;
        }
        // SFP+ ports
        for (port = 17; port < 21; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  VTSS_SGPIO_MODE_ON;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 1, &conf);
    }
    /* Setup SGPIO group 2 */
    if (vtss_sgpio_conf_get(NULL, 0, 2, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 3;

        // 24:NPI, 25:X2 slot A, 26:X2 slot B, [31:27] TxEnable, Fan, SFP+ TxEnable, Rate select
        for (port = 24; port < 32 ; port++) {
            conf.port_conf[port].enabled = 1;
        }

        // SFPplus[A|B|C|D]_TXFAULT are active high
        for (port = 25; port <= 28; port++) {
            conf.port_conf[port].int_pol_high[2] = TRUE;
        }

        // X2[A|B]_LOS[0-3] are active high
        for (port = 29; port <= 31 ; port++) {
            for (bit = 0; bit <= 2; bit++) {
                if (port == 29 && bit == 0) {
                    continue; // p29b0 is SYNCEPRESENTn (which is active low)
                }

                conf.port_conf[port].int_pol_high[bit] = TRUE; // LOS is active high
            }
        }

        /* X2 TXONOFF = ON */
        conf.port_conf[26].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[27].mode[0] = VTSS_SGPIO_MODE_ON;
        /* SFP Tx_disable = enabled */
        conf.port_conf[28].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[28].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[28].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[29].mode[0] = VTSS_SGPIO_MODE_ON;
        /* SFP RateSel = enabled    */
        conf.port_conf[29].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[29].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[30].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[30].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[30].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[31].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[31].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[31].mode[2] = VTSS_SGPIO_MODE_ON;

        (void)vtss_sgpio_conf_set(NULL, 0, 2, &conf);
    }
    /* must enable the the following interrupts (even though they are not used) to force them to be edge triggered */
    (void)vtss_sgpio_event_enable(NULL, 0, 2, 25, 0, TRUE); // SFPplusA_MODDET
    (void)vtss_sgpio_event_enable(NULL, 0, 2, 25, 1, TRUE); // SFPplusA_TXFAULT
    (void)vtss_sgpio_event_enable(NULL, 0, 2, 25, 1, TRUE); // SFPplusB_MODDET
    (void)vtss_sgpio_event_enable(NULL, 0, 2, 25, 2, TRUE); // SFPplusB_TXFAULT
}

static void jr2_init_sfp24(void)
{
    vtss_sgpio_conf_t conf;
    u32 port, gpio_no;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 56; gpio_no < 58; gpio_no++) {
        (void)vtss_gpio_mode_set(NULL, 0, gpio_no, VTSS_GPIO_ALT_0);
    }

    /* GPIO pins 0-3,4-5,30-33 are used for SGPIOs. */
    (void)vtss_gpio_mode_set(NULL, 0, 0, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)vtss_gpio_mode_set(NULL, 0, 1, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 2, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)vtss_gpio_mode_set(NULL, 0, 3, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / LD
    (void)vtss_gpio_mode_set(NULL, 0, 4, VTSS_GPIO_ALT_0);  // SGPIO Grp 1 / CLK
    (void)vtss_gpio_mode_set(NULL, 0, 5, VTSS_GPIO_ALT_0);  // SGPIO Grp 1 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 30, VTSS_GPIO_ALT_0); // SGPIO Grp 2 / Clk
    (void)vtss_gpio_mode_set(NULL, 0, 31, VTSS_GPIO_ALT_0); // SGPIO Grp 2 / LD
    (void)vtss_gpio_mode_set(NULL, 0, 32, VTSS_GPIO_ALT_0); // SGPIO Grp 2 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 33, VTSS_GPIO_ALT_0); // SGPIO Grp 2 / DI

    (void)vtss_gpio_mode_set(NULL, 0, 28, VTSS_GPIO_OUT);
    (void)vtss_gpio_write(NULL, 0, 28, TRUE);
    (void)vtss_gpio_mode_set(NULL, 0, 29, VTSS_GPIO_OUT);
    (void)vtss_gpio_write(NULL, 0, 29, TRUE);
    (void)vtss_gpio_mode_set(NULL, 0, 49, VTSS_GPIO_OUT);
    (void)vtss_gpio_write(NULL, 0, 49, TRUE);
    (void)vtss_gpio_mode_set(NULL, 0, 51, VTSS_GPIO_OUT);
    (void)vtss_gpio_mode_set(NULL, 0, 52, VTSS_GPIO_OUT);
    (void)vtss_gpio_mode_set(NULL, 0, 53, VTSS_GPIO_OUT);


    /* Setup SGPIO group 0    */
    /* Controls Port LEDs 1-24*/
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 2;
        for (port = 0; port < 24; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  VTSS_SGPIO_MODE_ON;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    /* Setup SGPIO group 1 */
    /* Controls LEDs for SFP+ and the LED tower */
    if (vtss_sgpio_conf_get(NULL, 0, 1, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 2;
        // LEDs for SFP+ and the LED tower
        for (port = 16; port < 24; port++) {
            conf.port_conf[port].enabled = 1;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 1, &conf);
    }
    /* Setup SGPIO group 2 */
    /* Controls LED for NPI, X2 LEDs and SFP signals */
    if (vtss_sgpio_conf_get(NULL, 0, 2, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 3;

        for (port = 0; port < 16 ; port++) {
            conf.port_conf[port].enabled = 1; // SFPs
            conf.port_conf[port].int_pol_high[0] = TRUE; // LOS is active high
            conf.port_conf[port].int_pol_high[2] = TRUE; // TX_FAULT is active high
        }

        for (port = 24; port < 30 ; port++) {
            conf.port_conf[port].enabled = 1; // CuPhys + SFPs+ + synce
        }

        for (port = 25; port < 29 ; port++) {
            conf.port_conf[port].int_pol_high[0] = TRUE; // LOS is active high
            conf.port_conf[port].int_pol_high[2] = TRUE; // TX_FAULT is active high
        }

        /* X2 TXONOFF = ON */
        conf.port_conf[10].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[11].mode[0] = VTSS_SGPIO_MODE_ON;
        /* SFP+ Tx_disable = enabled */
        conf.port_conf[12].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[12].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[12].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[13].mode[0] = VTSS_SGPIO_MODE_ON;
        /* SFP RateSel = enabled    */
        conf.port_conf[13].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[13].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[14].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[14].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[14].mode[2] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[15].mode[0] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[15].mode[1] = VTSS_SGPIO_MODE_ON;
        conf.port_conf[15].mode[2] = VTSS_SGPIO_MODE_ON;

        conf.port_conf[24].mode[0] = VTSS_SGPIO_MODE_ON; // NPI
        conf.port_conf[25].mode[1] = VTSS_SGPIO_MODE_ON; // X2 A
        conf.port_conf[26].mode[0] = VTSS_SGPIO_MODE_ON; // X2 B

        (void)vtss_sgpio_conf_set(NULL, 0, 2, &conf);
    }
}

static void jr2_init_srv2_nid(void)
{
    vtss_sgpio_conf_t conf;
    u32               port, gpio, bit;

    /* GPIO pins 0-3 are used for SGPIOs. */
    (void)vtss_gpio_mode_set(NULL, 0, 0, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
    (void)vtss_gpio_mode_set(NULL, 0, 1, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 2, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / DI
    (void)vtss_gpio_mode_set(NULL, 0, 3, VTSS_GPIO_ALT_0);  // SGPIO Grp 0 / LD

    (void)vtss_gpio_mode_set(NULL, 0, 30, VTSS_GPIO_ALT_0); // SGPIO Grp 2 / Clk
    (void)vtss_gpio_mode_set(NULL, 0, 31, VTSS_GPIO_ALT_0); // SGPIO Grp 2 / LD
    (void)vtss_gpio_mode_set(NULL, 0, 32, VTSS_GPIO_ALT_0); // SGPIO Grp 2 / DO
    (void)vtss_gpio_mode_set(NULL, 0, 33, VTSS_GPIO_ALT_0); // SGPIO Grp 2 / DI

    for (gpio = 44; gpio <= 59; gpio++) {
        if (gpio > 49 && gpio < 56) {
            continue;
        }
        (void)vtss_gpio_mode_set(NULL, 0, gpio, VTSS_GPIO_IN_INT); // Enable SFP Los interrupt
    }

    /* Setup SGPIO group 0 used for SFP signals */
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) == VTSS_RC_OK) {
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 2;

        for (port = 0; port < 16; port++) {
            conf.port_conf[port].enabled = 1;
            conf.port_conf[port].mode[0] =  VTSS_SGPIO_MODE_ON;
            conf.port_conf[port].mode[1] =  VTSS_SGPIO_MODE_ON;
        }

        // SFP[1-8]_TX_FAULT are active high
        for (port = 4; port <= 7; port++) {
            for (bit = 0; bit <= 1; bit++) {
                conf.port_conf[port].int_pol_high[bit] = TRUE;
            }
        }

        // SFP+[1-2]_TX_FAULT are active high
        for (bit = 0; bit <= 1; bit++) {
            conf.port_conf[10].int_pol_high[bit] = TRUE;
        }

        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }

    /* Setup SGPIO group 1 is not used */
    if (vtss_sgpio_conf_get(NULL, 0, 1, &conf) == VTSS_RC_OK) {
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        (void)vtss_sgpio_conf_set(NULL, 0, 1, &conf);
    }

    /* Setup SGPIO group 2 used for LEDs */
    if (vtss_sgpio_conf_get(NULL, 0, 2, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_5;
        conf.bit_count = 2;
        // LEDs
        for (port = 0; port < 16 ; port++) {
            conf.port_conf[port].enabled = 1;
        }
        for (port = 21; port < 29 ; port++) {
            conf.port_conf[port].enabled = 1;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 2, &conf);
    }

}

static void jr2_init_aqr(void)
{
    vtss_sgpio_conf_t conf;
    u32 port, gpio_no;

    // Configure GPIOs for MIIM/MDIO
    for (gpio_no = 56; gpio_no < 60; gpio_no++) {
        (void)vtss_gpio_mode_set(NULL, 0, gpio_no, VTSS_GPIO_ALT_0);
    }

    (void)vtss_gpio_mode_set(NULL, 0, 0, VTSS_GPIO_ALT_0);      // Serial LED Clock
    (void)vtss_gpio_mode_set(NULL, 0, 1, VTSS_GPIO_ALT_0);      // Serial LED Data
    (void)vtss_gpio_mode_set(NULL, 0, 21, VTSS_GPIO_OUT);       // SFP+ 26 Port TX disable: High : SFP+ TX power disable
    (void)vtss_gpio_mode_set(NULL, 0, 23, VTSS_GPIO_OUT);       // SFP+ 25 Port TX disable: High : SFP+ TX power disable
    (void)vtss_gpio_mode_set(NULL, 0, 24, VTSS_GPIO_IN);        // SFP+ 26 Port Present: Low : SFP+ Module Inserted
    (void)vtss_gpio_mode_set(NULL, 0, 25, VTSS_GPIO_IN);        // SFP+ 25 Port Present: Low : SFP+ Module Inserted
    (void)vtss_gpio_mode_set(NULL, 0, 26, VTSS_GPIO_OUT);       // n_PHY_RESET pin, active low at least 100ms
    (void)vtss_gpio_mode_set(NULL, 0, 48, VTSS_GPIO_IN_INT);    // Default setting or System reset (Low active)
    (void)vtss_gpio_mode_set(NULL, 0, 54, VTSS_GPIO_IN_INT);    // Port 26 nSD signal: Low : SFP+ Module Iinking
    (void)vtss_gpio_mode_set(NULL, 0, 55, VTSS_GPIO_IN_INT);    // Port 25 nSD signal: Low : SFP+ Module Iinking


    (void)vtss_gpio_write(NULL, 0, 21, 0);
    (void)vtss_gpio_write(NULL, 0, 23, 0);

    /* Setup SGPIO group 0     */
    /* Controls Port LEDs 1-26 */
    if (vtss_sgpio_conf_get(NULL, 0, 0, &conf) == VTSS_RC_OK) {
        /* The blink mode 0 is 5 HZ for link activity and collision in half duplex. */
        conf.bmode[0] = VTSS_SGPIO_BMODE_1_25;
        conf.bit_count = 2;
        for (port = 0; port < VTSS_PORTS && port < VTSS_SGPIO_PORTS; port++) {
            conf.port_conf[port].enabled = 1;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    }
}

static vtss_rc jr2_post_reset(void)
{
    if (jr2_port_table[0].map.miim_controller != VTSS_MIIM_CONTROLLER_NONE) {
        if (jr2_board_type == VTSS_BOARD_JAGUAR2_CU48_REF ||
            jr2_board_type == VTSS_BOARD_JAGUAR2_REF) {
            VTSS_RC(vtss_phy_post_reset(PHY_INST, 0));
        }
        VTSS_RC(vtss_phy_post_reset(PHY_INST, 0));
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_post_reset_aqr(void)
{
    return VTSS_RC_OK;
}

static void jr2_pre_reset(void)
{
}

//**************************************************************************************
//* I2C
//**************************************************************************************

static vtss_rc srv2_nid_i2c_read(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, u8 cnt, BOOL word_access)
{
    port_custom_entry_t *entry = &jr2_port_table[port_no];

    CUSTOM_D("port:%d\n", port_no);

    if (entry->cap & PORT_CAP_DUAL_COPPER) {
        return vtss_phy_i2c_read(NULL, port_no, port_no, addr, i2c_addr, word_access, cnt, data);
    }

    if (jr2_i2c_read != NULL) {
        CUSTOM_D("i2c_addr:0x%X, cnt:%d, addr:%0xX\n", i2c_addr, cnt, addr);
        return jr2_i2c_read(port_no, i2c_addr, addr, data, cnt);
    }

    return VTSS_RC_ERROR;
}

static vtss_rc srv2_nid_i2c_write(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, BOOL word_access)
{
    port_custom_entry_t *entry = &jr2_port_table[port_no];
    u8                  i2c_data[3];

    if (entry->cap & PORT_CAP_DUAL_COPPER) {
        return vtss_phy_i2c_write(NULL, port_no, port_no, addr, i2c_addr, word_access, 2, data);
    }

    if (jr2_i2c_write != NULL) {
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        return jr2_i2c_write(port_no, i2c_addr, i2c_data, 3);
    }
    return VTSS_RC_OK;
}

static BOOL get_sfp_status(vtss_port_no_t port_no, vtss_sgpio_port_data_t *data, sfp_signal_t sfp)
{
    u32 chip_port = jr2_port_table[port_no].map.chip_port;

    if (jr2_board_type == VTSS_BOARD_SERVAL2_NID_REF) {

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
            BOOL val = 0;
            // SFP_LOS
            switch (chip_port) {
            case 13: (void)vtss_gpio_read(NULL, 0, 44, &val); break;
            case 12: (void)vtss_gpio_read(NULL, 0, 45, &val); break;
            case 15: (void)vtss_gpio_read(NULL, 0, 46, &val); break;
            case 14: (void)vtss_gpio_read(NULL, 0, 47, &val); break;
            case 17: (void)vtss_gpio_read(NULL, 0, 48, &val); break;
            case 16: (void)vtss_gpio_read(NULL, 0, 49, &val); break;
            case 19: (void)vtss_gpio_read(NULL, 0, 56, &val); break;
            case 18: (void)vtss_gpio_read(NULL, 0, 57, &val); break;
            case 50: (void)vtss_gpio_read(NULL, 0, 58, &val); break;
            case 49: (void)vtss_gpio_read(NULL, 0, 59, &val); break;
            }
            return val;
        }

    } else if (jr2_board_type == VTSS_BOARD_JAGUAR2_REF) {
        u32 indx = (sfp == SFP_DETECT) ? 1 : (sfp == SFP_FAULT) ? 2 : 0;
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
        // VTSS_BOARD_JAGUAR2_CU48_REF || VTSS_BOARD_JAGUAR2_AQR_REF
        if (sfp == SFP_LOS) {
            BOOL val = 0;
            // SFP_LOS
            if (VTSS_BOARD_JAGUAR2_AQR_REF) {
                switch (chip_port) {
                case 51: (void)vtss_gpio_read(NULL, 0, 55, &val); break;
                case 52: (void)vtss_gpio_read(NULL, 0, 54, &val); break;
                }
            } else {
                switch (chip_port) {
                case 49: (void)vtss_gpio_read(NULL, 0, 52, &val); break;
                case 50: (void)vtss_gpio_read(NULL, 0, 53, &val); break;
                case 51: (void)vtss_gpio_read(NULL, 0, 54, &val); break;
                case 52: (void)vtss_gpio_read(NULL, 0, 55, &val); break;
                }
            }
            return val;
        } else {
            if (jr2_board_type == VTSS_BOARD_JAGUAR2_AQR_REF) {
                BOOL val;
                switch (chip_port) {
                    case 51:
                        if (sfp == SFP_DETECT) {
                            (void)vtss_gpio_read(NULL, 0, 25, &val);
                        } else if (sfp == SFP_FAULT){
                            (void)vtss_gpio_read(NULL, 0, 22, &val);
                        }
                        break;
                    case 52:
                        if (sfp == SFP_DETECT) {
                            (void)vtss_gpio_read(NULL, 0, 24, &val);
                        } else if (sfp == SFP_FAULT){
                            (void)vtss_gpio_read(NULL, 0, 20, &val);
                        }
                        break;
                }
                return sfp == SFP_DETECT ? !val : val;
            } else {
                u32 indx = (sfp == SFP_DETECT) ? 1 : (sfp == SFP_FAULT) ? 2 : 0;
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

// Get module: Present / LOS / TxFault signals
static vtss_rc jr2_sfp_status(port_custom_sfp_status_t *sfp_status)
{
    vtss_sgpio_port_data_t data[VTSS_SGPIO_PORTS];
    vtss_port_no_t         port_no;
    port_custom_entry_t    *entry;

    if (jr2_board_type != VTSS_BOARD_JAGUAR2_AQR_REF) {
        u32 sgpio_group = (jr2_board_type == VTSS_BOARD_SERVAL2_NID_REF) ? 0 : 2;
        if (vtss_sgpio_read(NULL, 0, sgpio_group, data) != VTSS_RC_OK) {
            return VTSS_RC_ERROR;
        }
    }
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        entry = &jr2_port_table[port_no];
        if (entry->cap & PORT_CAP_SFP_DETECT) {
            sfp_status[port_no].present  = get_sfp_status(port_no, data, SFP_DETECT);
            sfp_status[port_no].tx_fault = get_sfp_status(port_no, data, SFP_FAULT);
            sfp_status[port_no].los      = get_sfp_status(port_no, data, SFP_LOS);
        } else {
            sfp_status[port_no].present  = 0;
            sfp_status[port_no].los      = 0;
            sfp_status[port_no].tx_fault = 0;
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc srv2_nid_sfp_mod_detect(BOOL *detect_status)
{
    vtss_port_no_t port_no;
    vtss_sgpio_port_data_t data[VTSS_SGPIO_PORTS];

    if (vtss_sgpio_read(NULL, 0, 0, data) != VTSS_RC_OK) {
        return VTSS_RC_ERROR;
    }

    /* The status in 'data' is inverted i.e. '0' means detected */
    /* We return '1' when a module is detected */
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        // iPort 4 = SFP 0
        switch (port_no) {
        case 4:  detect_status[port_no] = !data[0].value[0]; break; // Schematic U36
        case 5:  detect_status[port_no] = !data[0].value[1]; break; // Schematic U36
        case 6:  detect_status[port_no] = !data[1].value[0]; break; // Schematic U36
        case 7:  detect_status[port_no] = !data[1].value[1]; break; // Schematic U36
        case 8:  detect_status[port_no] = !data[2].value[0]; break; // Schematic U36
        case 9:  detect_status[port_no] = !data[2].value[1]; break; // Schematic U36
        case 10: detect_status[port_no] = !data[3].value[0]; break; // Schematic U36
        case 11: detect_status[port_no] = !data[3].value[1]; break; // Schematic U36
        case 12: detect_status[port_no] = !data[8].value[0]; break; // Schematic U28
        case 13: detect_status[port_no] = !data[8].value[1]; break; // Schematic U28
        }
        CUSTOM_D("port:%d, status:%d\n", port_no, detect_status[port_no]);
    }

    return VTSS_RC_OK;
}

//
// SFP board

// Function for doing SFP i2c reads.
// In : port_no - The physical port number
//      i2c_addr - The address for the i2c device
//      addr     - The address with the i2c device to access.
//      cnt      - The number of data to read
//      word     - Not Used here
// In/Out  data     - The data read
static vtss_rc jr2_sfp_i2c_read(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, u8 cnt, BOOL word_access)
{
    vtss_rc rc = VTSS_RC_ERROR;
    u32 chip_port = jr2_port_table[port_no].map.chip_port;
    if (jr2_i2c_read != NULL) {
        rc = jr2_i2c_read(chip_port, i2c_addr, addr, data, cnt);
    }
    return rc;
}

// Function for doing SFP i2c writes
// In : port_no - The physical port number
//      i2c_addr - The address for the i2c device
//      addr     - The address with the i2c device to access.
//      cnt      - The number of data to read
//      word     - Not Used here
//      data     - The data to write
static vtss_rc jr2_sfp_i2c_write(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, BOOL word_access)
{
    u32 chip_port = jr2_port_table[port_no].map.chip_port;
    u8 i2c_data[3];
    if (jr2_i2c_write != NULL) {
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        return jr2_i2c_write(chip_port, i2c_addr, i2c_data, 3);
    }
    return VTSS_RC_ERROR;
}

static vtss_rc jr2_sfp_mod_detect(BOOL *detect_status)
{
    vtss_port_no_t port_no;
    vtss_sgpio_port_data_t data[VTSS_SGPIO_PORTS];
    u32 chip_port;

    if (jr2_board_type == VTSS_BOARD_JAGUAR2_AQR_REF) {
        // Not use on Atlanta reference board.
        memset(detect_status, 0, sizeof(*detect_status));
        return VTSS_RC_OK;
    }

    if (vtss_sgpio_read(NULL, 0, 2, data) != VTSS_RC_OK) {
        return VTSS_RC_ERROR;
    }

    /* The status in 'data' is inverted i.e. '0' means detected */
    /* We return '1' when a module is detected */
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        chip_port = jr2_port_table[port_no].map.chip_port;

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
            detect_status[port_no] = !data[chip_port - 8].value[1]; // Schematic U142
        } else if (chip_port >= 49 && chip_port <= 52) {
            detect_status[port_no] = !data[chip_port - 24].value[1];
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_sfp_mod_detect_aqr(BOOL *detect_status)
{
    vtss_port_no_t port_no;
    BOOL val = FALSE;

    CUSTOM_D("enter");
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        if (!(jr2_port_table[port_no].cap & PORT_CAP_SFP_DETECT)) {
            detect_status[port_no] = 0;
            continue;
        }

        switch(port_no) {
            case 24:
                vtss_gpio_read(NULL, 0, 25, &val);
                break;
            case 25:
                vtss_gpio_read(NULL, 0, 24, &val);
                break;
        }
        detect_status[port_no] = !val;
        CUSTOM_D("SFP-%d: %sPRESENT", port_no - 24, detect_status[port_no - 24] ? "" : "NOT-" );
    }
    return VTSS_RC_OK;
}

//**************************************************************************************
//* Add-on modules
//**************************************************************************************

//
// Malibu
//
// Function for detecting and configuring Malibu board
// Return VTSS_RC_OK if Malibu board was detected and configured correct, else error code
vtss_rc malibu_detect_and_conf(void) {
    u8 data;
    if (jr2_sfp_i2c_read(VTSS_PORTS-2, 0x40, 0, &data, 1, FALSE) == VTSS_RC_OK) { // Try to read the i2c EEPROM (address 0x40 )at the Malibu board, SFP+ port 1 (port = 27)
        CUSTOM_D("Malibu detected");

        // Setup LREF to 156.25MHz
        // Setting LREF_SELx pins to 0x00 for 156.25 MHz, See U1B at PCB VSC8258-SFP-04 schematic
        // LREF_SEL0, and LREF_SEL1 goes to SFPplusD_RATESEL0 and SFPplusD_RATESEL1, See the two schematics.
        // SFPplusD_RATESEL0 goes to Serial GPIO p15b1,(group 2)
        // SFPplusD_RATESEL1 goes to Serial GPIO p15b2 (group 2)
        vtss_sgpio_conf_t conf;
        VTSS_RC(vtss_sgpio_conf_get(NULL, 0, 2, &conf));
        conf.port_conf[15].enabled = 1;
        conf.port_conf[15].mode[1] = VTSS_SGPIO_MODE_OFF;
        conf.port_conf[15].mode[2] = VTSS_SGPIO_MODE_OFF;
        VTSS_RC(vtss_sgpio_conf_set(NULL, 0, 2, &conf));

        // Setup "CML out -> DC coupling -> CML in" to channel o
        // Setting SELx pins to 0x00 for channel 0, See U4 at PCB VSC8258-SFP-04 schematic
        // SEL0, and SEL1 goes to SFPplusB_RATESEL0 and SFPplusB_RATESEL1, See the two schematics.
        // SFPplusB_RATESEL0 goes to Serial GPIO p14b0,(group 2)
        // SFPplusB_RATESEL1 goes to Serial GPIO p14b1 (group 2)
        VTSS_RC(vtss_sgpio_conf_get(NULL, 0, 2, &conf));
        conf.port_conf[14].enabled = 1;
        conf.port_conf[14].mode[0] = VTSS_SGPIO_MODE_OFF;
        conf.port_conf[14].mode[1] = VTSS_SGPIO_MODE_OFF;
        VTSS_RC(vtss_sgpio_conf_set(NULL, 0, 2, &conf));
        return VTSS_RC_OK;
    }
    CUSTOM_D("Malibu NOT detected");
    return VTSS_RC_ERROR;
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
static void jr2_hard_reset_wait_aqr(void)
{
    u16  reg_value;
    BOOL reset_done[VTSS_PORTS] = {FALSE};
    vtss_port_no_t port_no;
    port_custom_entry_t *entry = &jr2_port_table[0];
    int i = 0;
    BOOL at_least_one_phy_not_reset;

    (void)vtss_gpio_write(NULL, 0, 26, 0);  // n_PHY_RESET pin, active low at least 100ms
    VTSS_MSLEEP(120);
    (void)vtss_gpio_write(NULL, 0, 26, 1);  // n_PHY_RESET pin, release reset state, pull high at least 20ms
    VTSS_MSLEEP(30);

    CUSTOM_D("Release Reset state");
    do {
        at_least_one_phy_not_reset = FALSE;
        for (port_no  = 0; port_no < VTSS_PORTS; port_no++) {
            entry = &jr2_port_table[port_no];
            if (reset_done[port_no] || entry->map.miim_controller == VTSS_MIIM_CONTROLLER_NONE) {
                continue;
            }

            if (vtss_mmd_read(NULL, 0, entry->map.miim_controller, entry->map.miim_addr, 0x1e, 0xcc00, &reg_value) == VTSS_RC_OK && (reg_value & 0x40)) {
                reset_done[port_no] = TRUE;
                CUSTOM_I("hard reset ready on MDIO-%d", entry->map.miim_addr);
            } else {
                at_least_one_phy_not_reset = TRUE;
            }
        }

        if (at_least_one_phy_not_reset) {
            VTSS_MSLEEP(10);
        }
    } while (i++ < 200 && at_least_one_phy_not_reset);

    if (at_least_one_phy_not_reset) {
        CUSTOM_E("Unable to reset at least one AQR PHY");
    }

}

static vtss_rc jr2_reset(void)
{
    vtss_port_no_t iport;
#if defined(VTSS_CHIP_10G_PHY) && (defined(VTSS_CHIP_JAGUAR_2) || defined(VTSS_CHIP_SPARX_IV_80) || defined(VTSS_CHIP_SPARX_IV_90))
    vtss_port_map_t    port_map[VTSS_PORT_ARRAY_SIZE];
    vtss_sgpio_conf_t conf;
    u32 port_cnt = vtss_port_cnt(NULL);

    if (jr2_board_type != VTSS_BOARD_JAGUAR2_CU48_REF && jr2_board_type != VTSS_BOARD_JAGUAR2_AQR_REF && malibu_detect_and_conf() == VTSS_RC_OK) {

        if (VTSS_PORT_ARRAY_SIZE < 24) {
            return VTSS_RC_ERROR; // Shall never happen if Malibu is detected.
        }

        (void)vtss_port_map_get(NULL, port_cnt, port_map);
        for (iport = 24; iport < VTSS_PORTS-1 && iport < VTSS_PORT_ARRAY_SIZE; iport++) {
            port_map[iport].miim_controller = VTSS_MIIM_CONTROLLER_0;
            jr2_port_table[iport].cap = (PORT_CAP_VTSS_10G_PHY | PORT_CAP_10G_FDX | PORT_CAP_FLOW_CTRL | PORT_CAP_XAUI_LANE_FLIP |PORT_CAP_1G_FDX);
#ifdef MALIBU_2_CHANNEL
            switch(iport) {
                case 24:
                port_map[24].miim_addr = 1;
                    break;
                case 25:
                port_map[25].miim_addr = 0;
                    break;
            }
#else
            switch(iport) {
                case 24:
                port_map[24].miim_addr = 3;
                    break;
                case 25:
                port_map[25].miim_addr = 2;
                    break;
                case 26:
                port_map[26].miim_addr = 1;
                    break;
                case 27:
                port_map[27].miim_addr = 0;
                    break;
            }
#endif
        }
        (void)vtss_port_map_set(NULL, port_cnt, port_map);
        // The PHY_RST goes to  SFPplusC_RATESEL0 (P14b2), See schematics
        VTSS_RC(vtss_sgpio_conf_get(NULL, 0, 2, &conf));
        conf.port_conf[14].enabled = 1;
        conf.port_conf[14].mode[2] = VTSS_SGPIO_MODE_ON;
        (void) (vtss_sgpio_conf_set(NULL, 0, 2, &conf));
    }
#endif
    if (jr2_port_table[0].map.miim_controller != VTSS_MIIM_CONTROLLER_NONE) {
        if (jr2_board_type == VTSS_BOARD_JAGUAR2_CU48_REF && (VTSS_PORTS > 37)) {
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 0));
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 12));
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 24));
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 36));
        } else if (jr2_board_type == VTSS_BOARD_JAGUAR2_REF) {
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 0));
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 4));

        } else if (jr2_board_type == VTSS_BOARD_JAGUAR2_CU48_REF) { // This board has 4 Atom12s - See schematics
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 12));
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 24));
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 36));

        } else if (jr2_board_type == VTSS_BOARD_SERVAL2_NID_REF) { // This board has a Viper or a Tesla See schematics
            VTSS_RC(vtss_phy_pre_reset(PHY_INST, 0));

        } else if( jr2_board_type == VTSS_BOARD_JAGUAR2_AQR_REF) {
            jr2_hard_reset_wait_aqr();
            for (iport = 0; iport < (VTSS_PORTS-2); iport++) { // reset only for 2.5G ports, 2 ports are 10G
                VTSS_RC(vtss_phy_pre_reset(PHY_INST, iport));
            }

        }
    }
    return VTSS_RC_OK;
}


//**************************************************************************************
//* LEDs
//**************************************************************************************

static vtss_rc jr2_led_init(void)
{
    // Enable enahanced LED control to disable the Phy PWM (LED intensity) signal (otherwise the LEDs are off).
    if (jr2_port_table[0].map.miim_controller == VTSS_MIIM_CONTROLLER_NONE) {
        return VTSS_RC_OK;
    }
    if (jr2_board_type != VTSS_BOARD_JAGUAR2_AQR_REF) {
        (void)vtss_phy_write(NULL, 0, 31, 0x0010);
        (void)vtss_phy_write(NULL, 0, 25, 0xc6b5);
        (void)vtss_phy_write(NULL, 0, 31, 0);
    }
    /* Update status LED using GPIO_12 and GPIO_13 */
    (void)vtss_gpio_mode_set(NULL, 0, 12, VTSS_GPIO_OUT);
    (void)vtss_gpio_mode_set(NULL, 0, 13, VTSS_GPIO_OUT);
    (void)vtss_gpio_write(NULL, 0, 12, 1); // Green LED ON
    (void)vtss_gpio_write(NULL, 0, 13, 0); // Red LED OFF

    /* Set up LED enhanced led */
    if (port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI ||
        port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
        vtss_phy_enhanced_led_control_t conf;
        conf.ser_led_frame_rate = 0x1; /* Frame rate = 1000Hz */
        conf.ser_led_select = 2;       /* Does't matter */
        if (jr2_board_type == VTSS_BOARD_JAGUAR2_CU48_REF) {
            conf.ser_led_output_2 = TRUE; /* PCB111 uses phy3_led1 as PWM. See schematic- LED_PWM */
            conf.ser_led_output_1 = FALSE;  /* Not used. */
            vtss_phy_enhanced_led_control_init(PHY_INST, 1, conf); /* Setup port 1, PWM is used for port1, see schematic PCB111 near R1380 */
        } else if (jr2_board_type == VTSS_BOARD_JAGUAR2_REF) {
            conf.ser_led_output_2 = FALSE; /* Not used. */
            conf.ser_led_output_1 = TRUE;  /* PCB110 uses phy3_led0 as PWM. See schematic- LED_PWM */
            vtss_phy_enhanced_led_control_init(PHY_INST, 1, conf); /* Setup port 1, PWM is used for port1, see schematic PCB110 near R1380 */
        }
    }

    return VTSS_RC_OK;
}

vtss_rc jr2_led_intensity(vtss_phy_led_intensity intensity)
{
    vtss_rc rc = VTSS_RC_OK;
    if (port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI ||
        port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
        /* Both PCB111 and PCB110 uses the first PHY to control the PWM */
        if (intensity < 30 && intensity > 0) {
            rc = vtss_phy_led_intensity_set(PHY_INST, 0, 30);
        }  else {
            rc = vtss_phy_led_intensity_set(PHY_INST, 0, intensity);
        }
    }
    return rc;
}

/* Port traffic activity is manually updated */
static BOOL port_activity(vtss_port_no_t port_no,
                          vtss_port_status_t *status,
                          vtss_port_counters_t *counters,
                          BOOL *cnt_activity)
{

    vtss_port_status_t *old_status = &jr2_old_port_info[port_no].status;
    vtss_port_counters_t *old_cnt = &jr2_old_port_info[port_no].cnt;
    BOOL link_activity = 0;

    if ((counters->rmon.rx_etherStatsPkts > (old_cnt->rmon.rx_etherStatsPkts + 2)) ||
        (counters->rmon.tx_etherStatsPkts > (old_cnt->rmon.tx_etherStatsPkts + 2))) {
        *cnt_activity = 1;
        *old_cnt = *counters;
    }
    if (old_status->link  != status->link  ||
        old_status->speed != status->speed ||
        old_status->fdx   != status->fdx) {
        link_activity = 1;
        *old_status = *status;
    }
    if (!*cnt_activity && !link_activity && !jr2_old_port_info[port_no].activity) {
        return 0; // No Activity
    }
    jr2_old_port_info[port_no].activity = link_activity || *cnt_activity;
    return 1; // Activity
}

/* Port traffic activity is auto updated */
static BOOL port_activity_auto(vtss_port_no_t port_no, vtss_port_status_t *status)
{

    vtss_port_status_t *old_status = &jr2_old_port_info[port_no].status;
    BOOL link_activity = 0;

    if (old_status->link  != status->link  ||
        old_status->speed != status->speed ||
        old_status->fdx   != status->fdx   ||
        old_status->fiber != status->fiber) {
        link_activity = 1;
        *old_status = *status;
    }
    if (!link_activity && !jr2_old_port_info[port_no].activity) {
        return 0; // No Activity
    }
    jr2_old_port_info[port_no].activity = link_activity;
    return 1; // Activity
}

static vtss_rc jr2_led_update_jr2(vtss_port_no_t port_no,
                                  vtss_port_status_t *status,
                                  vtss_port_counters_t *counters,
                                  port_custom_conf_t *port_conf)

{
    u32                 sgpio_group = 0, sgpio_port=0, chip_port = jr2_port_table[port_no].map.chip_port;
    vtss_sgpio_conf_t   conf;
    vtss_sgpio_mode_t   mode_green = VTSS_SGPIO_MODE_ON, mode_yellow = VTSS_SGPIO_MODE_ON;
    BOOL                update_led = port_activity_auto(port_no, status);

    if (!update_led) {
        return VTSS_RC_OK;
    }

    if (chip_port < 32) {
        sgpio_group = 0;
        sgpio_port = chip_port;
    } else if (chip_port == 48) {
        sgpio_group = 2;
        sgpio_port = 24; // NPI
        mode_green =  VTSS_SGPIO_MODE_OFF;
        mode_yellow = VTSS_SGPIO_MODE_OFF;
    } else if (chip_port > 48) {
        mode_green =  VTSS_SGPIO_MODE_OFF;
        mode_yellow = VTSS_SGPIO_MODE_OFF;
        if (jr2_port_table[port_no].mac_if == VTSS_PORT_INTERFACE_SFI) {
            sgpio_group = 1;
            sgpio_port = 16 + (chip_port - 49);  // SFP+
        } else { // XAUI port
            sgpio_group = 2;
            sgpio_port = chip_port == 49 ? 25 : 26;
        }
    }
    /* If link then auto update LED */
    if (status->link) {
        if (status->speed >= VTSS_SPEED_1G) {
            mode_green = (chip_port == JR2_NPI_CHIP_PORT || (chip_port > 48)) ? VTSS_SGPIO_MODE_0_ACTIVITY_INV : VTSS_SGPIO_MODE_0_ACTIVITY;
        } else {
            mode_yellow = (chip_port == JR2_NPI_CHIP_PORT || (chip_port > 48)) ? VTSS_SGPIO_MODE_0_ACTIVITY_INV : VTSS_SGPIO_MODE_0_ACTIVITY;
        }
    }

    VTSS_RC(vtss_sgpio_conf_get(NULL, 0, sgpio_group, &conf));

    // The Green/yellow LEDs are inverted for 1G ports
    conf.port_conf[sgpio_port].mode[LED_GREEN] = (chip_port > 48) ? mode_green : mode_yellow;
    conf.port_conf[sgpio_port].mode[LED_YELLOW] = (chip_port > 48) ? mode_yellow : mode_green;
    return vtss_sgpio_conf_set(NULL, 0, sgpio_group, &conf);
}


// TBD: enable LED update via the Phy
static vtss_rc jr2_led_update_cu48(vtss_port_no_t port_no,
                                   vtss_port_status_t *status,
                                   vtss_port_counters_t *counters,
                                   port_custom_conf_t *port_conf)
{
    u32                 sgpio_group=0, sgpio_port=0, chip_port = jr2_port_table[port_no].map.chip_port;
    vtss_sgpio_conf_t   conf;
    vtss_sgpio_mode_t   mode_green, mode_yellow;
    vtss_rc             rc;
    BOOL                update_led = port_activity_auto(port_no, status);

    if (!update_led) {
        return VTSS_RC_OK;
    }

    mode_green = chip_port == JR2_NPI_CHIP_PORT ? VTSS_SGPIO_MODE_OFF : VTSS_SGPIO_MODE_ON;
    mode_yellow = chip_port == JR2_NPI_CHIP_PORT ? VTSS_SGPIO_MODE_OFF : VTSS_SGPIO_MODE_ON;

    /* If link then auto update LED */
    if (status->link) {
        if (status->speed >= VTSS_SPEED_1G) {
            mode_green = (chip_port == JR2_NPI_CHIP_PORT) ? VTSS_SGPIO_MODE_0_ACTIVITY_INV : VTSS_SGPIO_MODE_0_ACTIVITY;
        } else {
            mode_yellow = (chip_port == JR2_NPI_CHIP_PORT) ? VTSS_SGPIO_MODE_0_ACTIVITY_INV : VTSS_SGPIO_MODE_0_ACTIVITY;
        }
    }

    if (chip_port < 32) {
        sgpio_port = chip_port;
        sgpio_group = 0;
    } else if (chip_port < 48) {
        sgpio_port = chip_port - 32;
        sgpio_group = 1;
    } else if (chip_port == 48) {
        sgpio_port = 24; //NPI
        sgpio_group = 2;
    } else {
        if ((jr2_port_table[port_no].mac_if == VTSS_PORT_INTERFACE_XAUI) && (chip_port == 49 || chip_port == 50)) {
            sgpio_group = 2;
            sgpio_port = (chip_port == 49) ? 25 : 26;
            mode_green = status->link ? VTSS_SGPIO_MODE_0_ACTIVITY_INV : VTSS_SGPIO_MODE_0_ACTIVITY;
            mode_yellow = VTSS_SGPIO_MODE_OFF;
        } else {
            // SFP+ ports
            switch (chip_port) {
            case 49:  sgpio_port = 17; break;
            case 50:  sgpio_port = 18; break;
            case 51:  sgpio_port = 19; break;
            case 52:  sgpio_port = 20; break;
            }
            sgpio_group = 1;
        }
    }
    if ((rc = vtss_sgpio_conf_get(NULL, 0, sgpio_group, &conf)) != VTSS_RC_OK) {
        return rc;
    }
    conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_green;
    conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_yellow;
    return vtss_sgpio_conf_set(NULL, 0, sgpio_group, &conf);
}

// TBD: enable auto update
static vtss_rc srv2_led_update_nid(vtss_port_no_t port_no,
                                   vtss_port_status_t *status,
                                   vtss_port_counters_t *counters,
                                   port_custom_conf_t *port_conf)
{
    u8                   port_to_led_map[VTSS_PORTS] = {0,1,2,3,5,4,7,6,9,8,11,10,26,25,24}; // See UG1057, table 16 (The table doesn't say that bit 25 and 26 shall be swapped, but that has turned out to be the case)
    u32                  sgpio_port;
    vtss_sgpio_conf_t    conf;
    vtss_sgpio_mode_t    mode_green, mode_yellow;
    BOOL                 cnt_activity = 0, update_led = port_activity(port_no, status, counters, &cnt_activity);

    if (!update_led) {
        return VTSS_RC_OK;
    }

    VTSS_RC(vtss_sgpio_conf_get(NULL, 0, 2, &conf));

    mode_green = VTSS_SGPIO_MODE_OFF;
    mode_yellow = VTSS_SGPIO_MODE_OFF;

    if (status->link) {
        if (status->speed >= VTSS_SPEED_1G) {
            if (cnt_activity) {
                mode_green = VTSS_SGPIO_MODE_0;
            } else {
                mode_green = VTSS_SGPIO_MODE_ON;
            }
        } else {
            if (cnt_activity) {
                mode_yellow = VTSS_SGPIO_MODE_0;
            } else {
                mode_yellow = VTSS_SGPIO_MODE_ON;
            }
        }
    }
    sgpio_port = port_to_led_map[port_no];
    conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_green;
    conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_yellow;
    return vtss_sgpio_conf_set(NULL, 0, 2, &conf);
}

static vtss_rc jr2_led_update_aqr(vtss_port_no_t port_no,
                                  vtss_port_status_t *status,
                                  vtss_port_counters_t *counters,
                                  port_custom_conf_t *port_conf)

{
    u32                 sgpio_port = 0, chip_port = jr2_port_table[port_no].map.chip_port;
    vtss_sgpio_conf_t   conf;
    vtss_sgpio_mode_t   mode_green = VTSS_SGPIO_MODE_ON, mode_yellow = VTSS_SGPIO_MODE_ON; // set green/yellow led off
    vtss_rc             rc;
    BOOL                cnt_activity = 0, update_led = port_activity(port_no, status, counters, &cnt_activity);

    if (!update_led) {
        return VTSS_RC_OK;
    }

    if ((rc = vtss_sgpio_conf_get(NULL, 0, 0, &conf)) != VTSS_RC_OK) {
        return rc;
    }

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
        if (status->speed != VTSS_SPEED_1G) {
            if (cnt_activity) {
                mode_green = VTSS_SGPIO_MODE_0;
            } else {
                mode_green = VTSS_SGPIO_MODE_OFF;
            }
        } else {
            if (cnt_activity) {
                mode_yellow = VTSS_SGPIO_MODE_0;
            } else {
                mode_yellow = VTSS_SGPIO_MODE_OFF;
            }
        }
    }
    /* Note: For AQ PHY, colors green & yellow are swapped */
    conf.port_conf[sgpio_port].mode[LED_GREEN] = mode_yellow;
    conf.port_conf[sgpio_port].mode[LED_YELLOW] = mode_green;

    return vtss_sgpio_conf_set(NULL, 0, 0, &conf);
}

static void jr2_port_conf(vtss_port_no_t port_no,
                          port_custom_conf_t *port_conf)
{
    u8 port_to_tx_disable_map_nid[VTSS_PORTS] = {0,0,0,0,8,9,10,11,4,5,6,7,12,13}; // TxDisable maps to SGPIO port bit 0
    u32 chip_port = jr2_port_table[port_no].map.chip_port;
    vtss_sgpio_conf_t  conf;
    vtss_sgpio_mode_t  sgpio_mode = (port_conf->enable ? VTSS_SGPIO_MODE_ON : VTSS_SGPIO_MODE_OFF);
#if defined(VTSS_CHIP_10G_PHY) && (defined(VTSS_CHIP_JAGUAR_2) || defined(VTSS_CHIP_SPARX_IV_80) || defined(VTSS_CHIP_SPARX_IV_90))
    vtss_gpio_10g_gpio_mode_t gpio_conf;
    vtss_gpio_10g_no_t gpio_no;
    u32 global_dev = 0x1e,lopc_reg = 0xf234,value = 0x13f;
#endif

    if (jr2_board_type == VTSS_BOARD_SERVAL2_NID_REF && jr2_port_table[port_no].map.miim_controller == -1) {
        (void)vtss_sgpio_conf_get(NULL, 0, 0, &conf);
        conf.port_conf[port_to_tx_disable_map_nid[port_no]].mode[0] = sgpio_mode;
        (void)vtss_sgpio_conf_set(NULL, 0, 0, &conf);
    } else if (jr2_board_type == VTSS_BOARD_JAGUAR2_REF && (jr2_port_table[port_no].map.miim_controller == -1) )  {
        (void)vtss_sgpio_conf_get(NULL, 0, 2, &conf);
        switch (chip_port) {
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
#if defined(VTSS_CHIP_10G_PHY) && (defined(VTSS_CHIP_JAGUAR_2) || defined(VTSS_CHIP_SPARX_IV_80) || defined(VTSS_CHIP_SPARX_IV_90))
        case 49: gpio_conf.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
                 gpio_no = 28;
                 (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                 gpio_conf.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;
                 gpio_conf.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_CH3_INTR0_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR3_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR3_EN);
                 gpio_conf.c_intrpt = VTSS_10G_GPIO_INTRPT_HPMA;
                 gpio_no = 34;
                 (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                 break;
        case 50: gpio_conf.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
                 gpio_no = 20;
                 (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                 gpio_conf.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;
                 gpio_conf.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_CH2_INTR0_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR2_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR2_EN);
                 gpio_conf.c_intrpt = VTSS_10G_GPIO_INTRPT_HPMA;
                 gpio_no = 34;
                 (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                 break;
        case 51: gpio_conf.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
                 gpio_no = 12;
                 (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
                 gpio_conf.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;
                 gpio_conf.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_CH1_INTR0_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR1_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR1_EN);
                 gpio_conf.c_intrpt = VTSS_10G_GPIO_INTRPT_HPMA;
                 gpio_no = 34;
                 (void)vtss_phy_10g_gpio_mode_set(PHY_INST,port_no,gpio_no,&gpio_conf);
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
                 vtss_phy_10g_csr_write(PHY_INST,port_no,global_dev,lopc_reg,value);
                 break;
#endif
        default:
            return;
        }
        (void)vtss_sgpio_conf_set(NULL, 0, 2, &conf);
    }
}
/***************************************************************************
 * Fan
 ***************************************************************************/
static vtss_rc jr2_fan_init(vtss_fan_conf_t fan_spec) {
    return vtss_fan_controller_init(NULL, &fan_spec);
}

static vtss_rc jr2_fan_init_nid(vtss_fan_conf_t fan_spec) {

    // FAN_ENA - See UG1057 Table 15
    vtss_sgpio_conf_t  conf;
    int port = 1;

    VTSS_RC(vtss_sgpio_conf_get(NULL, 0, 0, &conf));
    conf.port_conf[port].enabled = 1;
    conf.port_conf[port].mode[0] =  VTSS_SGPIO_MODE_OFF; // Note - FAN1_ENA is active low - See schematic.
    conf.port_conf[port].mode[1] =  VTSS_SGPIO_MODE_OFF; // Note - FAN2_ENA is active low - See schematic.
    VTSS_RC(vtss_sgpio_conf_set(NULL, 0, 0, &conf));

    // Set up fan controller.
    return vtss_fan_controller_init(NULL, &fan_spec);
}

/***************************************************************************
 * Temperature sensors
 ***************************************************************************/

static vtss_rc jr2_temp_sensors_init(void) {

    // All boards have the internal JR2 sensor
    VTSS_RC(vtss_temp_sensor_init(NULL, TRUE));

    if (jr2_board_type == VTSS_BOARD_JAGUAR2_CU48_REF) {
        // The Jaguar2 48 ports board has a temperature sensor in 4 Atom12s
        VTSS_RC(vtss_phy_chip_temp_init(PHY_INST, 0));
        VTSS_RC(vtss_phy_chip_temp_init(PHY_INST, 12));
        VTSS_RC(vtss_phy_chip_temp_init(PHY_INST, 24));
        VTSS_RC(vtss_phy_chip_temp_init(PHY_INST, 36));
    } else if (jr2_board_type == VTSS_BOARD_SERVAL2_NID_REF) {
        // One sensor in the 8584 PHY and one in Serval2 (iport set to 0)
        VTSS_RC(vtss_phy_chip_temp_init(PHY_INST, 0));
    } else {
        if (port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
            // If JR2 is running in VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI mode, the JR2 board has two temperature sensors in 2 Viper (port1-8) + one in JR2
            VTSS_RC(vtss_phy_chip_temp_init(PHY_INST, 0));
            VTSS_RC(vtss_phy_chip_temp_init(PHY_INST, 4));
        }
    } // jr2_board_type == VTSS_BOARD_JAGUAR2_CU48_REF

    return VTSS_RC_OK;
}

static vtss_rc jr2_temp_sensors_get(vtss_port_no_t iport, i16 *temp) {
    if (jr2_board_type == VTSS_BOARD_JAGUAR2_CU48_REF) {
        if (iport < 48) {
            return vtss_phy_chip_temp_get(PHY_INST, iport, temp);
        } else {
            return vtss_temp_sensor_get(NULL, temp);
        }
    } else if (jr2_board_type == VTSS_BOARD_SERVAL2_NID_REF) {
        // This board has 2 sensors - One in the 8584 PHY and one in Serval2
        // iport 0-3 uses their temperature sensor in the PHY
         if (iport < 4) {
            return vtss_phy_chip_temp_get(PHY_INST, iport, temp);
        } else {
             // All other ports uses the temperature sensor in Serval2
            return vtss_temp_sensor_get(NULL, temp);
        }
    } else {
        if (port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
            // If JR2 is running in VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI mode, the JR2 board has two temperature sensors in 2 Viper (port1-8).
            // All other ports uses the temperature sensor in JR2.
            if (iport < 8) {
                return vtss_phy_chip_temp_get(PHY_INST, iport, temp);
            } else {
                return vtss_temp_sensor_get(NULL, temp);
            }
        } else {
            // For all other modes the PHYs are disabled and we then uses the JR2 sensor
            return vtss_temp_sensor_get(NULL, temp);
        }
    }
}

static u8 jr2_temp_sensors_cnt(void) {
    if (jr2_board_type == VTSS_BOARD_JAGUAR2_CU48_REF) {
        return 5;
    } else if (jr2_board_type == VTSS_BOARD_SERVAL2_NID_REF) {
        // This board has 2 sensors - One in the 8584 PHY and one in Serval2
        return 2;
    } else {
        if (port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI) {
            // If JR2 is running in VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI mode, the JR2 board has two temperature sensors in 2 Viper (port1-8).
            return 3;
        } else {
            // For all other modes the PHYs are disabled and we then uses the JR2 sensor
        return 1;
        }
    }
}


static BOOL vtss_board_probe_jr2_cu48(vtss_board_t *board, vtss_board_info_t *board_info)
{
    vtss_port_no_t      port_no;
    port_custom_entry_t *entry;
    u32 gpio_no, alt_mask;
#if defined(VTSS_CHIP_SPARX_IV_80) || defined(VTSS_CHIP_SPARX_IV_90) || defined(VTSS_CHIP_JAGUAR_2)
    jr2_10g_detect_t detect;

    detect.miim_found[0] = 0;
    detect.miim_found[1] = 0;
#endif

    // Configure GPIOs for MIIM/MDIO
    (void) jr2_rd(JR2_TGT_GCB, JR2_ADDR_GPIO_ALT1_0, &alt_mask, board_info);
    for (gpio_no = 56; gpio_no < 60; gpio_no++) {
        alt_mask = (1 << (gpio_no - 32)) | alt_mask;
    }
    (void) jr2_wr(JR2_TGT_GCB, JR2_ADDR_GPIO_ALT1_0, alt_mask, board_info);

    board->type = VTSS_BOARD_JAGUAR2_CU48_REF,
    jr2_board_type = board_info->board_type = board->type;

    board->name = "Jaguar-2 CU48 Reference";
    board->features = (VTSS_BOARD_FEATURE_LOS | VTSS_BOARD_FEATURE_1588_CLK_ADJ_DAC | VTSS_BOARD_FEATURE_POE);
    board->custom_port_table = jr2_port_table;
    board->init = jr2_init_cu48;
    board->reset = jr2_reset;
    board->pre_reset = jr2_pre_reset;
    board->post_reset = jr2_post_reset;
    board->led_init = jr2_led_init;
    board->board_fan_init          = jr2_fan_init;
    board->board_temp_sensors_init = jr2_temp_sensors_init;
    board->board_temp_sensors_get  = jr2_temp_sensors_get;
    board->board_temp_sensors_cnt  = jr2_temp_sensors_cnt;
    board->led_update = jr2_led_update_cu48;
    board->port_conf = jr2_port_conf;
    board->sfp_i2c_read = jr2_sfp_i2c_read;
    board->sfp_i2c_write = jr2_sfp_i2c_write;
    board->sfp_mod_detect = jr2_sfp_mod_detect;
    board->sfp_status = jr2_sfp_status;

#if defined(VTSS_CHIP_SPARX_IV_90) || defined(VTSS_CHIP_SPARX_IV_52)
    board->mux_mode = VTSS_PORTS > 51 ? VTSS_PORT_MUX_MODE_2 : VTSS_PORT_MUX_MODE_AUTO;
#else
    board->mux_mode = VTSS_PORT_MUX_MODE_AUTO;
#endif

    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        entry = &jr2_port_table[port_no];
        if (port_no < 48) {
            /* Port 0-47: Copper ports */
            entry->map.chip_port       = port_no;
            entry->map.miim_controller = port_no < 24 ? VTSS_MIIM_CONTROLLER_1 : VTSS_MIIM_CONTROLLER_2;
            entry->map.miim_addr       = port_no < 24 ? port_no : port_no - 24;
            entry->map.max_bw          = VTSS_BW_1G;
            entry->mac_if              = VTSS_PORT_INTERFACE_QSGMII;
            entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
#ifdef VTSS_SW_OPTION_POE
            entry->poe_chip_port       =  entry->map.chip_port;
            entry->poe_support         =  port_no < 24 ? TRUE : FALSE;
#endif
#if defined(VTSS_CHIP_SPARX_IV_90) || defined(VTSS_CHIP_JAGUAR_2)
        } else if (port_no < 50) {
            /* Port 48-49: 10G ports SFI or XAUI */
            /* Detect 10G PHY, can be a VTSS PHY or X2/Xenpak module */
            /* If a device is found then this XAUI port is activated and a SFP+ port disabled */
            detect.port_no = port_no;
            detect.miim_addr[0] = (port_no - 24);
            detect.cap = 0;
            entry->map.max_bw = VTSS_BW_DEFAULT; // 10G

            if (jr2_10g_detect(&detect, board_info)) {
                /* API Port 48,49 = XAUI chip ports 49,50 - possibly VTSS PHYs */
                entry->map.chip_port       = port_no + 1;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
                entry->map.miim_addr       = detect.miim_addr[0];
                entry->mac_if              = VTSS_PORT_INTERFACE_XAUI;
                entry->cap                 = detect.cap;
            } else {
                /* API Port 48,49 = SFP+ chip ports 50,49 */
                entry->map.chip_port       = port_no == 48 ? 50 : 49;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
                entry->cap                 = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
            }
        } else if (port_no < 52 && port_no != VTSS_PORTS - 1) {
            /* API Port 50,51: 10G SFI ports 52,51 */
            entry->map.chip_port       = port_no == 50 ? 52 : 51;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = VTSS_BW_DEFAULT; // 10G
            entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
            entry->cap                 = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
#elif defined(VTSS_CHIP_SPARX_IV_80)
        } else if (port_no < 50) {
            /* Port 48-49: 10G ports SFI or XAUI */
            /* Detect 10G PHY, can be a VTSS PHY or X2/Xenpak module */
            /* If a device is found then this XAUI port is activated and a  SFP+ port disabled */
            detect.port_no = port_no;
            detect.miim_addr[0] = (port_no - 24);
            detect.cap = 0;
            entry->map.max_bw = VTSS_BW_DEFAULT; // 10G

            if (jr2_10g_detect(&detect, board_info)) {
                /* API Port 48,49: XAUI chip ports 49,50 - possibly VTSS PHYs */
                entry->map.chip_port       = port_no + 1;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
                entry->map.miim_addr       = detect.miim_addr[0];
                entry->mac_if              = VTSS_PORT_INTERFACE_XAUI;
                entry->cap                 = detect.cap;
            } else {
                /* API Port 48-49: SFP+ chip ports:51,52 */
                entry->map.chip_port       = port_no == 48 ? 52 : 51;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
                entry->cap                 = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
            }
#else /* VTSS_CHIP_SPARX_IV_52 */
        } else if (port_no < 52) {
            /* Port 48-51: SFP */
            entry->map.chip_port       = port_no + ((port_no & 1) ? 0 : 2);
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = VTSS_BW_1G;
            entry->mac_if              = VTSS_PORT_INTERFACE_SERDES;
            entry->cap                 = PORT_CAP_SFP_1G | PORT_CAP_SFP_SD_HIGH;
#endif
        } else {
            /* Last port (NPI) */
            entry->map.chip_port       = 48;
            entry->map.miim_controller = jr2_phy_detect(28, board_info); // Autodetect controller 0 or 1
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = VTSS_BW_1G;
            entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
            entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
        }
    }
    return TRUE;
}

static BOOL vtss_board_probe_srv2_nid(vtss_board_t *board, vtss_board_info_t *board_info)
{
    vtss_port_no_t      port_no;
    port_custom_entry_t *entry;

    board->type = VTSS_BOARD_SERVAL2_NID_REF;
    jr2_board_type = board_info->board_type = board->type;

    board->name = "Serval-2";
    board->features = (VTSS_BOARD_FEATURE_LOS);
    board->custom_port_table = jr2_port_table;
    board->init = jr2_init_srv2_nid;
    board->reset = jr2_reset;
    board->pre_reset = jr2_pre_reset;
    board->post_reset = jr2_post_reset;
    board->led_init = jr2_led_init;
    board->board_fan_init          = jr2_fan_init_nid;
    board->board_temp_sensors_init = jr2_temp_sensors_init;
    board->board_temp_sensors_get  = jr2_temp_sensors_get;
    board->board_temp_sensors_cnt  = jr2_temp_sensors_cnt;
    board->led_update = srv2_led_update_nid;
    board->port_conf = jr2_port_conf;
    board->sfp_i2c_read = srv2_nid_i2c_read;
    board->sfp_i2c_write = srv2_nid_i2c_write;
    board->sfp_mod_detect = srv2_nid_sfp_mod_detect;
    board->sfp_status = jr2_sfp_status;
    board->mux_mode = VTSS_PORT_MUX_MODE_AUTO;

    /* Fill out port mapping table */
    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        entry = &jr2_port_table[port_no];
        if (port_no < 4) {
            /* Port 0-3: Copper ports */
            entry->map.chip_port       = port_no + 8;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
            entry->map.miim_addr       = port_no + 16;
            entry->map.max_bw          = VTSS_BW_1G;
            entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
            entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
#if (VTSS_PORTS > 12)
        } else if (port_no < 12) {
            /* Port 4-11: 2.5G SFP */
            entry->map.chip_port       = port_no + ((port_no & 1) ? 7 : 9);
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = VTSS_BW_2G5;
            entry->mac_if              = VTSS_PORT_INTERFACE_SERDES;
            entry->cap                 = PORT_CAP_SFP_2_5G | PORT_CAP_SFP_SD_HIGH;
#endif /* VTSS_PORTS > 12 */
#if (VTSS_PORTS > 14)
        } else if (port_no < 14) {
            /* Port 12-13: SFP+ */
            entry->map.chip_port       = port_no == 13 ? 49 : 50;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = VTSS_BW_DEFAULT; // 10G
            /* TBD */
            entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
            entry->cap                 = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
#endif /* VTSS_PORTS > 14 */
        } else {
            /* Port 14: NPI port */
            entry->map.chip_port       = 48;
            entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = VTSS_BW_1G;
            entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
            entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
        }
    }

    return TRUE;
}

static BOOL vtss_board_probe_jr2_sfp24(vtss_board_t *board, vtss_board_info_t *board_info)
{
    vtss_port_no_t      port_no;
    port_custom_entry_t *entry;
    jr2_10g_detect_t detect;

    board->type = VTSS_BOARD_JAGUAR2_REF;
    jr2_board_type = board_info->board_type = board->type;

    board->name = "Jaguar-2";
    board->features = (VTSS_BOARD_FEATURE_LOS | VTSS_BOARD_FEATURE_1588_CLK_ADJ_DAC | VTSS_BOARD_FEATURE_1588_REF_CLK_SEL);
    board->custom_port_table = jr2_port_table;
    board->init = jr2_init_sfp24;
    board->reset = jr2_reset;
    board->pre_reset = jr2_pre_reset;
    board->post_reset = jr2_post_reset;
    board->led_init = jr2_led_init;
    board->board_fan_init          = jr2_fan_init;
    board->board_temp_sensors_init = jr2_temp_sensors_init;
    board->board_temp_sensors_get  = jr2_temp_sensors_get;
    board->board_temp_sensors_cnt  = jr2_temp_sensors_cnt;
    board->led_update = jr2_led_update_jr2;
    board->port_conf = jr2_port_conf;
    board->sfp_i2c_read = jr2_sfp_i2c_read;
    board->sfp_i2c_write = jr2_sfp_i2c_write;
    board->sfp_mod_detect = jr2_sfp_mod_detect;
    board->sfp_status = jr2_sfp_status;
    board->mux_mode = VTSS_PORT_MUX_MODE_AUTO;

    detect.miim_found[0] = 0;
    detect.miim_found[1] = 0;

    if (port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI || port_cfg == VTSS_BOARD_CONF_DEFAULT_VENICE_1G_MODE) {
        for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
            entry = &jr2_port_table[port_no];
            board_info->port_count = VTSS_PORTS;
            if (port_no < 8) {
                entry->map.chip_port       = port_no;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_1;
                entry->map.miim_addr       = port_no;
                entry->map.max_bw          = VTSS_BW_1G;
                entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
                entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
            } else if (port_no < 24) {
                entry->map.chip_port       = port_no;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->mac_if              = VTSS_PORT_INTERFACE_SERDES;
                if (port_no > 11) {
                    entry->map.max_bw = VTSS_BW_1G;
                    entry->cap        = PORT_CAP_SFP_1G | PORT_CAP_SFP_SD_HIGH;
                } else {
                    entry->map.max_bw = VTSS_BW_2G5;
                    entry->cap        = PORT_CAP_SFP_2_5G | PORT_CAP_SFP_SD_HIGH;
                }
            } else if (port_no < (board_info->port_count - 1)) {
                // Auto detect XAUI ports and replace the SFI ports if detected
                detect.port_no      = port_no;
                detect.miim_addr[0] = port_no == 24 ? 24 : 25;
                detect.cap          = 0;
                entry->map.max_bw   = VTSS_BW_DEFAULT; // 10G

                if ((port_no == 24 || port_no == 25) && jr2_10g_detect(&detect, board_info)) {
                    /* API Port 26,27 = XAUI chip ports 49,50 - possibly VTSS PHYs */
                    entry->cap                 = detect.cap;
                    if (port_cfg == VTSS_BOARD_CONF_DEFAULT_VENICE_1G_MODE) {
                        /* chip ports 49-50 do not map to single XAUI lanes instead we use chip ports 24 and 28 */
                        entry->map.chip_port       = port_no == 24 ? 24 : 28;
                        entry->cap |= PORT_CAP_1G_FDX | PORT_CAP_AUTONEG;
                    } else {
                        entry->map.chip_port       = port_no == 24 ? 49 : 50;
                    }
                    entry->map.miim_controller = VTSS_MIIM_CONTROLLER_0;;
                    entry->map.miim_addr       = detect.miim_addr[0];
                    entry->mac_if              = VTSS_PORT_INTERFACE_XAUI;
                } else {
                    entry->map.chip_port       = port_no + 25;
                    entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                    entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
                    entry->cap                 = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
                }
            } else if (port_no == (board_info->port_count - 1)) {
                // NPI port
                entry->map.chip_port       = 48;
                entry->map.miim_controller = jr2_phy_detect(28, board_info); // Autodetect controller 0 or 1
                entry->map.miim_addr       = 28;
                entry->map.max_bw          = VTSS_BW_1G;
                entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
                entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
            } else {
                entry->map.chip_port = CHIP_PORT_UNUSED;
            }
        }
    } else if (port_cfg == VTSS_BOARD_CONF_24x2G5_2xSFI_NPI) {
        board->mux_mode = VTSS_PORT_MUX_MODE_1;
        board_info->port_count = 27;
        for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
            entry = &jr2_port_table[port_no];
            if (port_no < 24) {
                entry->map.chip_port       = port_no + 8;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = VTSS_BW_2G5;
                entry->mac_if              = VTSS_PORT_INTERFACE_SERDES;
                entry->cap                 = PORT_CAP_SFP_2_5G | PORT_CAP_SFP_SD_HIGH;
            } else if (port_no < 26) {
                entry->map.chip_port       = port_no + 25;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = VTSS_BW_DEFAULT; // 10G
                entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
                entry->cap                 = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
            } else if (port_no == 26) {
                // NPI port
                entry->map.chip_port       = 48;
                entry->map.miim_controller = jr2_phy_detect(28, board_info); // Autodetect controller 0 or 1
                entry->map.miim_addr       = 28;
                entry->map.max_bw          = VTSS_BW_1G;
                entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
                entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
            } else {
                entry->map.chip_port = CHIP_PORT_UNUSED;
            }
        }
    } else if (port_cfg == VTSS_BOARD_CONF_16x2G5_4xSFI_NPI) {
        board->mux_mode = VTSS_PORT_MUX_MODE_0;
        board_info->port_count = (VTSS_PORTS - 8);
        for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
            entry = &jr2_port_table[port_no];
            if (port_no < 16) {
                entry->map.chip_port       = port_no + 8;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = VTSS_BW_2G5;
                entry->mac_if              = VTSS_PORT_INTERFACE_SERDES;
                entry->cap                 = PORT_CAP_SFP_2_5G | PORT_CAP_SFP_SD_HIGH;
            } else if (port_no < (board_info->port_count - 1)) {
                entry->map.chip_port       = port_no + 33;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = VTSS_BW_DEFAULT; // 10G
                entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
                entry->cap                 = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
            } else if (port_no == (board_info->port_count - 1)) {
                // NPI port
                entry->map.chip_port       = 48;
                entry->map.miim_controller = jr2_phy_detect(28, board_info); // Autodetect controller 0 or 1
                entry->map.miim_addr       = 28;
                entry->map.max_bw          = VTSS_BW_1G;
                entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
                entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
            } else {
                entry->map.chip_port = CHIP_PORT_UNUSED;
            }
        }
    } else if (port_cfg == VTSS_BOARD_CONF_20x1G_4x2G5_2xSFI_NPI) {
        for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
            entry = &jr2_port_table[port_no];
            board_info->port_count = 27;
            if (port_no < 8) {
                entry->map.chip_port       = port_no;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_1;
                entry->map.miim_addr       = port_no;
                entry->map.max_bw          = VTSS_BW_1G;
                entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
                entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
            } else if (port_no < 24) {
                entry->map.chip_port       = port_no;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->mac_if              = VTSS_PORT_INTERFACE_SERDES;
                if (port_no > 11) {
                    entry->map.max_bw = VTSS_BW_1G;
                    entry->cap        = PORT_CAP_SFP_1G | PORT_CAP_SFP_SD_HIGH;
                } else {
                    entry->map.max_bw = VTSS_BW_2G5;
                    entry->cap        = PORT_CAP_SFP_2_5G | PORT_CAP_SFP_SD_HIGH;
                }
            } else if (port_no < 26) {
                entry->map.chip_port       = port_no + 27;
                entry->map.miim_controller = VTSS_MIIM_CONTROLLER_NONE;
                entry->map.max_bw          = VTSS_BW_DEFAULT; // 10G
                entry->mac_if              = VTSS_PORT_INTERFACE_SFI;
                entry->cap = (PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
            } else if (port_no == 26) {
                // NPI port
                entry->map.chip_port       = 48;
                entry->map.miim_controller = jr2_phy_detect(28, board_info); // Autodetect controller 0 or 1
                entry->map.miim_addr       = 28;
                entry->map.max_bw          = VTSS_BW_1G;
                entry->mac_if              = VTSS_PORT_INTERFACE_SGMII;
                entry->cap                 = PORT_CAP_TRI_SPEED_COPPER;
            } else {
                entry->map.chip_port = CHIP_PORT_UNUSED;
            }
        }
    }

    return TRUE;
}

static void jr2_map_update(vtss_port_no_t         port_no,
                           i32                    chip_port,
                           u8                     miim_addr,
                           vtss_miim_controller_t miim_controller,
                           vtss_port_interface_t  mac_if,
                           port_cap_t             cap)
{
    port_custom_entry_t *entry;
    if (port_no < VTSS_PORTS) {
        entry = &jr2_port_table[port_no];
        entry->map.chip_port = chip_port;
        entry->map.miim_controller = miim_controller;
        entry->map.miim_addr = miim_addr;
        entry->map.max_bw = (cap & PORT_CAP_10G_FDX) ? VTSS_BW_10G : (cap & PORT_CAP_2_5G_TRI_SPEED_COPPER) ? VTSS_BW_2G5 : VTSS_BW_1G;
        entry->mac_if = mac_if;
        entry->cap = cap;
    }
}
static BOOL vtss_board_probe_jr2_aqr(vtss_board_t *board, vtss_board_info_t *board_info)
{
    board->type = VTSS_BOARD_JAGUAR2_AQR_REF;
    jr2_board_type = board_info->board_type = board->type;

    board->name = "Jaguar-2 Atlanta Reference";
    board->features = (VTSS_BOARD_FEATURE_LOS |  VTSS_BOARD_FEATURE_1588_CLK_ADJ_DAC);
    board->custom_port_table = jr2_port_table;
    board->init = jr2_init_aqr;
    board->reset = jr2_reset;
    board->pre_reset = jr2_pre_reset;
    board->post_reset = jr2_post_reset_aqr;
    board->led_init = jr2_led_init;
    board->board_fan_init          = jr2_fan_init;
    board->board_temp_sensors_init = jr2_temp_sensors_init;
    board->board_temp_sensors_get  = jr2_temp_sensors_get;
    board->board_temp_sensors_cnt  = jr2_temp_sensors_cnt;
    board->led_update = jr2_led_update_aqr;
    board->port_conf = jr2_port_conf;
    board->sfp_i2c_read = jr2_sfp_i2c_read;
    board->sfp_i2c_write = jr2_sfp_i2c_write;
    board->sfp_mod_detect = jr2_sfp_mod_detect_aqr;
    board->sfp_status = jr2_sfp_status;
    board->mux_mode = VTSS_PORT_MUX_MODE_1; // Ports muxed to Serdes blocks: 24x2G5, chip ports 8-23,51-52

    /* new MDIO mapping for new AQ board
     * Internal Port   Chip Port   MIIM Address    MIIM Controller
     * -------------   ---------   ------------    ---------------
     * 0               11          8               0
     * 1               10          9               0
     * 2               9           10               0
     * 3               8           11               0
     * 4               15          12               0
     * 5               14          13               0
     * 6               13          14               0
     * 7               12          15               0

     * 8               19          16               1
     * 9               18          17               1
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
    jr2_map_update(0, 11, 8, VTSS_MIIM_CONTROLLER_0, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(1, 10, 9, VTSS_MIIM_CONTROLLER_0, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(2, 9,  10, VTSS_MIIM_CONTROLLER_0, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(3, 8,  11, VTSS_MIIM_CONTROLLER_0, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(4, 15, 12, VTSS_MIIM_CONTROLLER_0, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(5, 14, 13, VTSS_MIIM_CONTROLLER_0, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(6, 13, 14, VTSS_MIIM_CONTROLLER_0, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(7, 12, 15, VTSS_MIIM_CONTROLLER_0, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);

    jr2_map_update(8, 19, 16, VTSS_MIIM_CONTROLLER_1, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(9, 18, 17, VTSS_MIIM_CONTROLLER_1, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(10, 17, 18, VTSS_MIIM_CONTROLLER_1, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(11, 16, 19, VTSS_MIIM_CONTROLLER_1, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(12, 23, 20, VTSS_MIIM_CONTROLLER_1, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(13, 22, 21, VTSS_MIIM_CONTROLLER_1, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(14, 21, 22, VTSS_MIIM_CONTROLLER_1, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(15, 20, 23, VTSS_MIIM_CONTROLLER_1, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);

    jr2_map_update(16, 27, 24, VTSS_MIIM_CONTROLLER_2, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(17, 26, 25, VTSS_MIIM_CONTROLLER_2, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(18, 25, 26, VTSS_MIIM_CONTROLLER_2, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(19, 24, 27, VTSS_MIIM_CONTROLLER_2, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(20, 31, 28, VTSS_MIIM_CONTROLLER_2, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(21, 30, 29, VTSS_MIIM_CONTROLLER_2, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(22, 29, 30, VTSS_MIIM_CONTROLLER_2, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);
    jr2_map_update(23, 28, 31, VTSS_MIIM_CONTROLLER_2, VTSS_PORT_INTERFACE_SGMII_2G5, PORT_CAP_2_5G_TRI_SPEED_COPPER);

    jr2_map_update(24, 51, 0, VTSS_MIIM_CONTROLLER_NONE, VTSS_PORT_INTERFACE_SFI, PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
    jr2_map_update(25, 52, 0, VTSS_MIIM_CONTROLLER_NONE, VTSS_PORT_INTERFACE_SFI, PORT_CAP_10G_FDX | PORT_CAP_SFP_2_5G | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_SD_HIGH);
    return TRUE;
}

BOOL vtss_board_probe_jr2(vtss_board_t *board, vtss_board_info_t *board_info)
{
    memset(board, 0, sizeof(*board));
    memset(jr2_old_port_info, 0, sizeof(jr2_old_port_info));

    jr2_i2c_read   = board_info->i2c_read;
    jr2_i2c_write  = board_info->i2c_write;

    // Default board configuration
    port_cfg = VTSS_BOARD_CONF_20x1G_4x2G5_4xSFI_NPI;

    board->led_intensity = jr2_led_intensity;

    if (VTSS_PORTS > 37) {
        return vtss_board_probe_jr2_cu48(board, board_info);
    } else if (VTSS_PORTS == 26) {
        return vtss_board_probe_jr2_aqr(board, board_info);
    } else if ((VTSS_PORTS < 38) && (VTSS_PORTS > 15)) {
        return vtss_board_probe_jr2_sfp24(board, board_info);
    } else {
        return vtss_board_probe_srv2_nid(board, board_info);
    }
}

#endif /* VTSS_ARCH_JAGUAR_2_B/C */

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
