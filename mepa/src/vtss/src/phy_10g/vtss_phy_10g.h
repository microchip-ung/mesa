// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PHY_10G_H_
#define _VTSS_PHY_10G_H_

/* MMD sublayers */
#define MMD_PMA     1
#define MMD_HPMA    9 
#define MMD_WIS     2
#define MMD_PCS     3
#define MMD_XS      4
#define MMD_NVR_DOM 30 // 8486
#define MMD_GLOBAL  30 // 8484/8487/8488

/* Sublayer Registers */
#define REG_CONTROL_1      0
#define REG_STATUS_1       1
#define REG_DEVICE_ID_1    2
#define REG_DEVICE_ID_2    3
#define REG_SPEED_ABILITY  4
#define REG_PACKAGE_1      5
#define REG_PACKAGE_2      6
#define REG_CONTROL_2      7
#define REG_STATUS_2       8

typedef struct _vtss_phy_10g_port_state_info_t {
    vtss_phy_10g_family_t        family;     /* Family          */
    vtss_phy_10g_type_t          type;       /* Type            */
    u16                          revision;   /* Revision number */
    u16                          device_feature_status;    /* Device features depending on EFUSE */
    vtss_phy_10g_status_t        status;     /* Status          */
    vtss_phy_10g_mode_t          mode;       /* Operating mode  */
    vtss_phy_10g_loopback_t      loopback;   /* Loopbacks      */
    vtss_phy_10g_power_t         power;      /* Power */
    vtss_phy_10g_failover_mode_t failover;   /* Failover mode */
    vtss_phy_10g_clause_37_control_t clause_37;  /* line 1G PCS Clause 37 (1G Serdes mode) */
    vtss_phy_10g_clause_37_control_t host_clause_37;  /* host 1G PCS Clause 37 (1G Serdes mode) */
    u16                          channel_id; /* Phy Channel id  */
    u16                          chip_no;    /* Phy chip number  */
    BOOL                         channel_id_lock; /* Make the channel id 'read only'  */
    vtss_port_no_t               phy_api_base_no; /* First API no within this phy */
    u16                          gpio_count; /* Number of gpios for this Phy.  Note that multiple phy channels shares GPIOs */
    BOOL                         edc_fw_api_load; /* Is the EDC FW loaded through the API? */
#if defined(VTSS_FEATURE_SYNCE_10G)
    BOOL synce_clkout;          /* Clock out for recovered clock is enabled/disabled */
    BOOL xfp_clkout;            /* Clock out for XFP is enabled/disabled */
    vtss_phy_10g_rxckout_conf_t  rxckout;   /* RXCKOUT configuration */
    vtss_phy_10g_txckout_conf_t  txckout;   /* TXCKOUT configuration */
    vtss_phy_10g_srefclk_mode_t  srefclk; /* SREFCLK configuration for venice/Malibu family */
    vtss_phy_10g_ckout_conf_t    ckout;  /*  CKOUT configuration for Malibu family */
    vtss_phy_10g_sckout_conf_t   sckout;  /*  SCKOUT configuration for Malibu family */
    vtss_phy_10g_line_clk_conf_t line_clk;  /*  Line clk configuration for Malibu family */
    vtss_phy_10g_host_clk_conf_t host_clk;  /*  Host clk configuration for Malibu family */
#endif /* VTSS_FEATURE_SYNCE_10G */
    vtss_phy_10g_lane_sync_conf_t lane_sync; /* Lane SYNC Configuration for Malibu PHY */
    vtss_phy_10g_base_kr_conf_t kr_conf; /* 10gBASE-KR configuration data */
    vtss_phy_10g_base_kr_conf_t host_kr_conf; /* Host 10gBASE-KR configuration data */
#ifdef VTSS_FEATURE_10GBASE_KR
    vtss_phy_10g_base_kr_train_aneg_t kr_tr_aneg;   /* line,10gBASE-KR training & autoneg config */
    vtss_phy_10g_base_kr_train_aneg_t h_kr_tr_aneg;   /* Host,10gBASE-KR training & autoneg config */
#endif /* VTSS_FEATURE_10GBASE_KR */
   
    vtss_phy_10g_event_t         ev_mask;
    BOOL                         event_86_enable;
    vtss_gpio_10g_gpio_mode_t    gpio_mode[VTSS_10G_PHY_GPIO_MAL_MAX];
    BOOL                         warm_start_reg_changed;
    BOOL                         phy_88_event_B;
    BOOL                         current_los;    /* current Loss Of Signal detected (for Venice rev A work around) */
    BOOL                         ex_ev_enable;
    vtss_phy_10g_extnd_event_t   ex_ev_mask;
    vtss_phy_10g_auto_failover_conf_t l_a_failover; /* line, Auto Failover mode */
    vtss_phy_10g_auto_failover_conf_t h_a_failover; /* host, Auto Failover mode */
    vtss_phy_10g_prbs_generator_conf_t prbs_gen_conf[VTSS_PHY_10G_PRBS_TYPE_CNT][VTSS_PHY_10G_DIRECTION_CNT];
    vtss_phy_10g_prbs_monitor_conf_t   prbs_mon_conf[VTSS_PHY_10G_PRBS_TYPE_CNT][VTSS_PHY_10G_DIRECTION_CNT];
    vtss_phy_10g_vscope_conf_t vscope_conf;
    vtss_phy_10g_sgmii_lane_select_t sgmii_lane;
    vtss_phy_10g_jitter_conf_t l_jitter_conf; /**< Line Jitter configuration */
    vtss_phy_10g_jitter_conf_t h_jitter_conf; /**< Host Jitter configuration */
    /**
     * is_port_2_channel_map_reverse is to identify front port to channel mapping order
     * TRUE  - eg : 24- 1, 25- 0
     * FALSE - eg : 24- 0, 25- 1
     * Used to assign corresponding channel id if PHY has 2 x 1588 instances and to select apt. port-
     * when PHY is in Failover state
     */
    BOOL                          is_port_2_channel_map_reverse;
    /**
     * alt_port_no is to represent alternate port (LINE) when PHY is in failover state
     * Eg : normal case port-X sources traffic from port-X  LINE direction,
     *      but in failovers state port-X sources traffic from port-Y LINE direction
     */
    vtss_port_no_t                alt_port_no;
    vtss_phy_10g_i2c_slave_conf_t i2c_slave_conf; /**< i2c slave address and other parameters */
} vtss_phy_10g_port_state_t;

vtss_rc vtss_phy_10g_init_conf_set(struct vtss_state_s *vtss_state);
vtss_rc vtss_phy_10g_restart_conf_set(struct vtss_state_s *vtss_state);

vtss_rc vtss_phy_10g_sync(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);

vtss_rc vtss_phy_10g_debug_info_print(struct vtss_state_s *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info,
                                      BOOL                      ail);
vtss_rc vtss_phy_10g_debug_venice_vml_info_print(struct vtss_state_s *vtss_state,
                                                 const vtss_debug_printf_t pr,
                                                 vtss_port_no_t port_no,
                                                 BOOL  ail);
vtss_rc vtss_phy_10g_debug_malibu_vml_info_print(struct vtss_state_s *vtss_state,
                                                 const vtss_debug_printf_t pr,
                                                 vtss_port_no_t port_no);

vtss_rc vtss_phy_10g_debug_malibu_info_print(struct vtss_state_s *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      vtss_port_no_t port_no);
vtss_rc vtss_phy_10g_inst_venice_create(struct vtss_state_s *vtss_state);
vtss_rc vtss_phy_10g_inst_malibu_create(struct vtss_state_s *vtss_state);

#endif /* _VTSS_PHY_10G_H_ */

