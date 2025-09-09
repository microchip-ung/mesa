// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef MEPA_LAN80XX_TYPES_H_
#define MEPA_LAN80XX_TYPES_H_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_ts_private.h"
#include "lan80xx.h"
#include "lan80xx_macsec_private.h"
#include "lan80xx_ts.h"

#define LAN80XX_MAX_PORTS_PER_PHY   (4U)
#define LAN80XX_GPIO_COUNT          (40U)

#define TRUE  1
#define FALSE 0


/* Host Communication*/
#define MEPA_RC_ERR_MB_INVALID_CRC              (-301)
#define MEPA_RC_ERR_MB_RESP_TIMEOUT             (-302)
#define MEPA_RC_ERR_MB_INVALID_PKT_LEN          (-303)
#define MEPA_RC_ERR_MB_FW_UPDATE_FAIL           (-304)
#define MEPA_RC_ERR_MB_FAIL_RESPONSE            (-305)
#define MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC        (-306)
#define MEPA_RC_ERR_OTP_ALL_KEY_COMPROMISED     (-307)
#define MEPA_RC_ERR_OTP_ALL_KEY_PROGRAMMED      (-308)
#define MEPA_RC_ERR_OTP_MAX_RECORD_REACHED      (-309)


/* MDIO Register Access */
typedef struct {
    uint16_t mmd;       /* MMD ID of the register */
    mepa_bool_t is32;   /* 32-bit register or 16-bit register */
    uint32_t addr;      /* Address of the Register */
} ioreg_blk;


/* Part number of different skews */
typedef enum {
    LAN80XX_DEV_ID_UNKNOWN = 0,
    LAN80XX_DEV_ID_8044 = 0x8044,      /* Quad 1G/10G/25G PHY with 1588 and MACSEC*/
    LAN80XX_DEV_ID_8043 = 0x8043,      /* Quad 1G/10G/25G PHY with 1588 */
    LAN80XX_DEV_ID_8042 = 0x8042,      /* Quad 1G/10G/25G PHY with MACSEC*/
    LAN80XX_DEV_ID_8024 = 0x8024,      /* Dual 1G/10G/25G PHY with 1588 and MACSEC*/
    LAN80XX_DEV_ID_8023 = 0x8023,      /* Dual 1G/10G/25G PHY with 1588 */
    LAN80XX_DEV_ID_8022 = 0x8022,      /* Dual 1G/10G/25G PHY with MACSEC*/
    LAN80XX_DEV_ID_8268 = 0x8268,      /* Quad 1G/10G PHY with 1588 and MACSEC*/
    LAN80XX_DEV_ID_8267 = 0x8267,      /* Quad 1G/10G PHY with 1588 */
    LAN80XX_DEV_ID_8264 = 0x8264,      /* Dual 1G/10G PHY with 1588 and MACSEC*/
    LAN80XX_DEV_ID_8263 = 0x8263,      /* Dual 1G/10G PHY with 1588 */
    LAN80XX_DEV_ID_8262 = 0x8262,      /* Dual 1G/10G PHY with MACSEC*/
} phy25g_device_id_type_t;

/* PHY Revision */
typedef enum {
    LAN80XX_REV_UNKNOWN = 0,
    LAN80XX_REV_A0 = 0xA0,
    LAN80XX_REV_A1 = 0xA1,
} phy25g_revision_info_t;

/* PHY Family */
typedef enum {
    PHY_FAMILY_UNKNOWN = 0,
    PHY_FAMILY_M25G,                   /* M25G family */
} phy25g_phy_family_info_t;

/* PHY Info */
typedef struct {
    phy25g_device_id_type_t  devid;    /* Part Number of the PHY */
    phy25g_revision_info_t   rev;      /* Revision Id of the PHY */
    phy25g_phy_family_info_t family;   /* PHY Family */
} phy25g_dev_info_t;

/** \brief 25G Phy Polarity inversion */
typedef struct {
    mepa_bool_t line_rx;               /**< Line side Receive path*/
    mepa_bool_t line_tx;               /**< Line side Transmit path*/
    mepa_bool_t host_rx;               /**< Host side Receive path*/
    mepa_bool_t host_tx;               /**< Host side Transmit path*/
} phy25g_polarity_inv_t;

/** \brief 25G Phy power setting */
typedef enum {
    LAN80XX_PHY_POWER_DISABLE,        /**< Disable Phy power for all sublayers*/
    LAN80XX_PHY_POWER_ENABLE,         /**< Enable Phy power for all sublayers */
} phy25g_power_t;

/**< per port Phy mode type */
typedef enum {
    LAN80XX_PHY_1G_MODE,              /* 1GBase-KX, LX, SX */
    LAN80XX_PHY_10G_LAN_MODE,         /* 10G 10GBase-R */
    LAN80XX_PHY_10G_LAN_SYNC_MODE,    /* 10G 10GBase-R */
    LAN80XX_PHY_25G_LAN_MODE,         /* 25GBase-CR, CR-S, KR, KR-S, SR, LR, ER */
    LAN80XX_PHY_25G_LAN_SYNC_MODE,    /* 25GBase-CR, CR-S, KR, KR-S, SR, LR, ER */
    LAN80XX_PHY_ANEG
} phy25g_phy_mode_t;

/** \brief M25G Phy Media type */
typedef enum {
    LAN80XX_MEDIA_TYPE_SR_25G,     /**< 25GBASE-SR PMA/PMD */
    LAN80XX_MEDIA_TYPE_LR_25G,     /**< 25GBASE-LR PMA/PMD */
    LAN80XX_MEDIA_TYPE_ER_25G,     /**< 25GBASE-ER PMA/PMD */
    LAN80XX_MEDIA_TYPE_KR_25G,     /**< 25GBASE-KR or 25GBASE-KR-S PMA/PMD */
    LAN80XX_MEDIA_TYPE_CR_25G,     /**< 25GBASE-CR or 25GBASE-CR-S PMA/PMD */
    LAN80XX_MEDIA_TYPE_SR,         /**< SR,10GBASE-SR PMA/PMD (10G LAN PHY)*/
    LAN80XX_MEDIA_TYPE_KR,         /**< KR,10GBASE-KR PMA/PMD (10G LAN PHY)*/
    LAN80XX_MEDIA_TYPE_LR,         /**< LR,10GBASE-LR PMA/PMD (10G LAN PHY)*/
    LAN80XX_MEDIA_TYPE_ER,         /**< ER,10GBASE-ER PMA/PMD (10G LAN PHY)*/
    LAN80XX_MEDIA_TYPE_KX,         /**< 1000BASE-KX PMA/PMD  (1G PHY) */
    LAN80XX_MEDIA_TYPE_LX,         /**< 1000BASE-KX PMA/PMD  (1G PHY) */
    LAN80XX_MEDIA_TYPE_SX,         /**< 1000BASE-KX PMA/PMD  (1G PHY) */
    LAN80XX_MEDIA_TYPE_NONE,       /**< None          */
} phy25g_media_t;

/** \brief DFE Block configuration Backup for EYE scan enable */
typedef struct {
    u16     dfe_pd;                         /**< DFE power down register bit */
    u16     dfedmx_pd;                      /**< DFE Power control Bit */
    u16     erramp_pd;                      /**< Power down error amplifier for DFE adaptation bit */
    u16     dfedig;                         /**< DFE digital adaptation enable bit */
} phy25g_eye_backup_t;

typedef struct {
    phy25g_oper_mode_t    oper_mode;           /**< Phy operational mode (PCS/MAC) */
    phy25g_phy_mode_t     speed_oper_mode;     /**< Phy operational mode (LAN/1G/25G) */
    phy25g_media_t        h_media;             /**< Gives information of media type connected on HOST direction */
    phy25g_media_t        l_media;             /**< Gives information of media type connected on LINE direction */
    phy25g_polarity_inv_t polarity;            /**< polarity inversion configuration */
} phy25g_port_mode_t;


/** \brief Serdes Configuration based on media */
typedef struct {
    mepa_bool_t  ln_cfg_en_adv;           /* Register Ctrl tap adv */
    mepa_bool_t  ln_cfg_en_main;          /* Register Ctrl tap main */
    mepa_bool_t  ln_cfg_en_dly;           /* Register Ctrl tap dly */
    u8           ln_cfg_tap_adv_3_0;      /* Register Ctrl adv*/
    u8           ln_cfg_tap_main;         /* Register Ctrl main */
    u8           ln_cfg_tap_dly_4_0;      /* Register Ctrl dly */
    mepa_bool_t  pcs_en_adv;              /* Pin Ctrl tap adv*/
    mepa_bool_t  pcs_en_main;             /* Pin Ctrl tap main*/
    mepa_bool_t  pcs_en_dly;              /* Pin Ctrl tap adv */
    u8           cfg_tap_adv_3_0;         /* TAP ADV value */
    u8           cfg_tap_main;            /* TAP MAIN value */
    u8           cfg_tap_dly_4_0;         /* TAP DLY value */
    u8           cfg_vga_ctrl_bypass_4_0; /* VGA value */
    u8           cfg_eqR_force;           /* CTLE R */
    u8           cfg_eqC_force_3_0;       /* CTLE C */
    u8           ln_cfg_alos_thr_2_0;
    mepa_bool_t  dfe_enable;    /* DFE Enable or not */
} phy25g_serdes_data_t;

/** \brief 25G Phy each Port State */
typedef struct {
    mepa_port_no_t                  alt_port_no;
    phy25g_power_t                  power;               /* Power */
    phy25g_port_mode_t              port_mode;           /* Operating mode  */
    phy25g_oper_speed_mode_t        speed;               /* Operating Speed */
    phy25g_lp_get_t                 loopback_conf;
    uint16_t                        gpio_count;          /* Number of gpios for this Phy.  Note that multiple phy channels shares GPIOs */
    phy25g_eye_backup_t             eye_reg_backup;      /* Backup of DFE configuration while enabling the EYE Scan */
} phy25g_port_state_t;

typedef struct {
    phy25g_oper_speed_mode_t    neg_speed;
    mepa_bool_t                 prl_detect;
    mepa_bool_t                 an_complete;
    mepa_bool_t                 an_rem_fault;
} phy25g_aneg_status;

typedef struct {
    mepa_bool_t      macsec_disable;
    mepa_bool_t      ptp_1588_disable;
    mepa_bool_t      speed_25g_disable;
    mepa_bool_t      quad_disable;
    mepa_bool_t      cleartags_disable;
    mepa_bool_t      mpls_disable;
} phy25g_features_t;

/* MEPA-1226: mepa dev must be passed to callback function */
typedef uint8_t(*phy25g_gpio_read_t)(const mepa_device_t *dev);
//
// This structure is accessed from mepa_device->data member
// which is info about malibu15g a.k.a private data
typedef struct phy25g_state_s {
    mepa_bool_t                     reset_done;
    mepa_bool_t                     channel_id_lock;     /* Lock Channel ID Config */
    mepa_bool_t                     warm_start_cur;      /* Current warm start status */
    mepa_restart_t                  restart_cur;         /* Current restart configuration */
    mepa_restart_t                  restart_prev;        /* Previous restart configuration */
    mepa_bool_t                     sync_calling_private; /* Used by PHY APIs */
    uint8_t                         packet_idx;
    uint8_t                         channel_id;
    uint8_t                         lsc_select;          /* LOAD or STORE LSC Pin */
    phy25g_aneg_status              host_aneg_status;
    phy25g_aneg_status              line_aneg_status;
    mepa_port_no_t                  port_no;
    mepa_conf_t                     conf;
    phy25g_dev_info_t               dev;                  /* PHY Info */
    ioreg_blk                       io_var;               /* temporary structures used in register read/write in phys */
    mepa_synce_clock_conf_t         synce_conf;
    mepa_device_t                   *base_dev;                          /* Pointer to the device of base port on the phy chip */
    mepa_device_t                   *other_port_dev[LAN80XX_MAX_PORTS_PER_PHY]; /* Storing All Port Instance in Base Dev */
    mepa_port_no_t                  chip_ports[LAN80XX_MAX_PORTS_PER_PHY];      /* Port Numbers of the Chip are strored in Base Dev */
    uint8_t                         max_port_cnt;                       /* Max Channel of the Chip (Quad/Dual) */
    uint8_t                         port_cnt;                           /* No of Ports associatied with this Base Dev */
    mepa_bool_t                     post1_passed;                       /* Post 1 Status, by default 1, when POST1 Fails in any of the ports it becomes 0 */
    mepa_bool_t                     ts_base_detected;
    mepa_port_interface_t           mac_if;
    mepa_device_t                   *ts_base_dev;
    mepa_phy_prbs_generator_conf_t  host_prbs_conf;
    mepa_phy_prbs_generator_conf_t  line_prbs_conf;
    mepa_phy_prbs_generator_conf_t  host_pcs_prbs_conf;
    mepa_phy_prbs_generator_conf_t  line_pcs_prbs_conf;
    mepa_phy_prbs_monitor_conf_t    host_prbs_mon_conf;
    mepa_phy_prbs_monitor_conf_t    line_prbs_mon_conf;
    mepa_bool_t                     pkt_bist_mon_ena;
    phy25g_pkt_mon_rst_t            pkt_bist_reset;
    phy25g_port_state_t             port_state;
    phy25g_events_t                 events;
    mepa_bool_t                     reversion;
    mepa_bool_t                     is_mac_change;
    phy25g_host_protect_mode_t      mode;
    phy25g_ext_events_t             ext_events;
    mepa_bool_t                     frame_preempt_ena;
    mepa_bool_t                     flow_control_ena;
    phy25g_rx_eye_scan_status_t     eye_scan;
    phy25g_ts_data_t                ts;
    phy25g_macsec_internal_conf_t   macsec_conf;
    mepa_macsec_inst_count_t        inst_counts;
    mepa_bool_t                     ptp_shared_ltc_pll_init;
    mepa_bool_t                     ptp_shared_sti_interface_init;
    mepa_bool_t                     ptp_shared_ltc_resource;
    phy25g_ptp_lsc_input            ptp_lsc_input_config;
    phy25g_ptp_lsc_output           ptp_lsc_output_config;
    phy25g_phy_ts_port_conf_t       phy_ts_port_conf;
    mepa_ts_fifo_read_t             ts_fifo_cb;
    void                            *cntxt;
    phy25g_gpio_read_t              ft_gpio_read;
    mepa_port_no_t                  krlog_en_ports;
    phy25g_features_t               features;
} phy25g_phy_state_t;


#endif //_MEPA_LAN80XX_TYPES_H_
