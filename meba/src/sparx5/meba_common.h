// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define MAX_PORTS 57
typedef struct {
    meba_port_entry_t  map;
    uint32_t           board_port;
    uint32_t           sgpio_port;
    uint32_t           sgpio_bit;
    mesa_port_status_t status;
    mesa_bool_t        activity;
    mesa_bool_t        ts_phy;
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
    VTSS_BOARD_CONF_10x10G_4x25G_NPI,
    VTSS_BOARD_CONF_LAST
} board_port_cfg_t;

typedef struct {
    void (*board_init)(meba_inst_t inst);
    void (*init_port)(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry);
} board_func_t;

typedef struct meba_board_state {
    board_type_t          type;
    board_port_cfg_t      port_cfg;
    const mesa_fan_conf_t *fan_spec;
    mesa_bool_t           beaglebone;
    mesa_bool_t           ls1046;
    mesa_bool_t           gpy241_present;
    mesa_bool_t           viper_present;
    mesa_bool_t           malibu_present;
    mesa_bool_t           gpy241_usxgmii_mode;
    uint16_t              gpy241_leds[4];
    uint32_t              port_cnt;
    int                   cpu_port_cnt;
    fa_port_info_t        *port;
    const board_func_t    *func;
    mepa_device_t        *phy_devices[MAX_PORTS];
} meba_board_state_t;

