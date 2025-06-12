// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// This file declares the lan8042 chip specic APIs and corresponding
// data structures



#ifndef _LAN80XX_H_
#define _LAN80XX_H_

// The following .h file needed
#include <microchip/ethernet/phy/api.h>
#define LAN80XX_EVENT_BIT(x)    (1ULL << x)


/**< per port Phy operational speed */
typedef enum {
    SPEED_NONE = 0,
    SPEED_1G,
    SPEED_10G,
    SPEED_25G,
} phy25g_oper_speed_mode_t;

/**< Phy operational mode */
/* Enum for PCS_RETIMER should be zero */
typedef enum {
    PCS_RETIMER = 0, /*This is a traditional PHY (PCS + SerDes) on both Host and Line, with the 1588 TSU
                        also available. MACSEC and MAC feature is not available (speed 1G / 10G/25G)*/
    MAC_RETIMER,     /* Support both MACSEC (optional) and 1588 and MAC(speed 1G / 10G/25G)*/
} phy25g_oper_mode_t;

/** \brief malibu25g Phy link and fault status */
typedef struct {
    mepa_bool_t         rx_link;    /**< The rx link status  */
    mepa_bool_t         link_down;  /**< Link down event status. Clear on read  */
    mepa_bool_t         rx_fault;   /**< Rx fault event status.  Clear on read */
    mepa_bool_t         tx_fault;   /**< Tx fault event status.  Clear on read */
    mepa_bool_t         hi_ber;     /**< HI BER Status of PCS */
} phy25g_sublayer_status_t;

/** \brief PCS1G status */
typedef struct {
    mepa_bool_t        link_status; /** Link status of PCS1G */
    mepa_bool_t        sync_status; /** Syncronous status of PCS1G */
} phy25g_pcs1g_status_t;

/** \brief Malibu25G PCS PMA status */
typedef struct {
    phy25g_sublayer_status_t    pma;                 /**< Status for PMA */
    phy25g_sublayer_status_t    line_pcs25g;         /**< Status for Line PCS 25G */
    phy25g_sublayer_status_t    host_pcs25g;         /**< Status for HOST PCS 25G */
    phy25g_pcs1g_status_t       line_pcs1g;          /**< Status for LINE PCS 1G */
    phy25g_pcs1g_status_t       host_pcs1g;          /**< Status for HOST PCS 1G */
    mepa_bool_t                 hpcs25g_block_lock;  /**< Status for HOST PCS 25G Block Lock */
    mepa_bool_t                 lpcs25g_block_lock;  /**< Status for LINE PCS 25G Block Lock */
    phy25g_oper_speed_mode_t    host_neg_speed;      /**< HOST Negotiatied Speed (applicable only when speed == MESA_SPEED_AUTO) */
    phy25g_oper_speed_mode_t    line_neg_speed;      /**< LINE Negotiatied Speed (applicable only when speed == MESA_SPEED_AUTO) */
    mepa_bool_t                 phy_status;          /**< Status of PHY */
    phy25g_oper_mode_t          oper_mode;           /**< Port mode(PCS/MAC RETIMER Mode) */
} phy25g_status_t;

/** \brief Types of Eye scan methods*/
typedef enum {
    LAN80XX_RX_EYE_NORMAL_SCAN,      /* Normal Eye Scan */
    LAN80XX_RX_EYE_FAST_SCAN,        /* Fast Eye Scan */
} phy25g_rx_eye_scan_t;

/** /brief Eye scan results */
/* Normal Scan will give the 65-bit Eye scan results, the lower 64-bits are
 * stored in "eye_res" and MSB 1 bit is stored in "eye_res_msb".
 * Eye Height of Fast Scan is stored in "eye_height"
 */
typedef struct {
    u64         eye_res[128];                /* Eye diagram plot resgister applicable only in NORMAL SCAN*/
    mepa_bool_t eye_res_msb[128];            /* NORMAL SCAN MSB bit */
    u32         eye_height;                  /* Eye Height applicable only in FAST SCAN */
} phy25g_rx_eye_scan_status_t;

/** \brief TX and RX Equalization Status */
typedef struct {
    mepa_bool_t   dfe_enable;            /* DFE enabled or not */
    mepa_bool_t   dfe_adaptive_mode;     /* Adaptive mode DFE enabled or not applicatible only if dfe_enable is TRUE */
    u32           dfe_coefficients[6];   /* 5-tap DFE coefficients */
    u32           vga_value;             /* VGA coefficient */
    u32           ctle_r_value;          /* CTLE R coefficient */
    u32           ctle_c_value;          /* CTLE C Coefficient */
    u16           tx_tap_dly;            /* TX C(-1) Coefficient */
    u16           tx_tap_adv;            /* TX C(1) Coefficient */
    u16           amp_code;
} phy25g_tx_rx_equ_status_t;


typedef enum {
    LAN80XX_CONF_TX_EQUALIZER,
    LAN80XX_CONF_RX_EQUALIZER,
    LAN80XX_CONF_TX_RX_EQUALIZER,
} phy25g_equa_t;


/** \brief Tx and Rx Equalization Configuration */
typedef struct {
    phy25g_equa_t  equalizer_conf;       /* Tx/Rx/Both Config */
    mepa_bool_t    dfe_adp_ena;          /* DFE Adaptive Mode enable */
    mepa_bool_t    dfe_man_ena;          /* DFE Manual Mode enable */
    u16            amp_code;             /* Tx Amplitude Control */
    u16            rx_vga;               /* Rx VGA configuration */
    u16            rx_ctle_c;            /* Rx CTLE C configuration */
    u16            rx_ctle_r;            /* Rx CTLE R Configuration */
    u16            tx_tap_dly;           /* Tx C(-1) Coefficient */
    u16            tx_tap_adv;           /* Tx C(1) Coefficient */
} phy25g_tx_rx_equa_conf_t;

/** \brief Loopback types */
typedef struct {
    mepa_bool_t  h3p_lp_ena;   /* Enable H3P loopback */
    mepa_bool_t  l3p_lp_ena;   /* Enable L3P Loopback */
    mepa_bool_t  h3m_lp_ena;   /* Enable H3M Loopback */
    mepa_bool_t  l3m_lp_ena;   /* Enable L3M Loopback */
    mepa_bool_t  h7_lp_ena;    /* Enable H7 Loopback */
} phy25g_lp_types_t;

/** \brief loopback status get */
typedef struct {
    mepa_bool_t     h1_lp;     /* Status of H1 Loopback */
    mepa_bool_t     l1_lp;     /* Status of L1 Loopback */
    mepa_bool_t     h2_lp;     /* Status of H2 Loopback */
    mepa_bool_t     l2_lp;     /* Status of L2 Loopback */
    mepa_bool_t     h3p_lp;    /* Status of H3P Loopback */
    mepa_bool_t     l3p_lp;    /* Status of L3P Loopback */
    mepa_bool_t     h3m_lp;    /* Status of H3M Loopback */
    mepa_bool_t     l3m_lp;    /* Status of L3M Loopback */
    mepa_bool_t     h5_lp;     /* Status of H5 Loopback */
    mepa_bool_t     l5_lp;     /* Status of L5 Loopback */
    mepa_bool_t     h6_lp;     /* Status of H6 Loopback */
    mepa_bool_t     l6_lp;     /* Status of L6 Loopback */
    mepa_bool_t     h7_lp;     /* Status of H7 Loopback */
} phy25g_lp_get_t;

#define MAX_PORTS 4

typedef enum {
    LAN80XX_AUTO_FAILOVER_1_ISTO_1_PROTECTION,
    LAN80XX_AUTO_FAILOVER_1_PLUS_1_PROTECTION,
} phy25g_host_protect_mode_t;

typedef enum {
    LAN80XX_WPS_0_1_DEFAULT_ACTIVE_H0_H3 = 0,
    LAN80XX_WPS_0_1_DEFAULT_ACTIVE_H1_H2 = 1,
} phy25g_wps_def_active_host_t;

typedef enum {
    LAN80XX_WPS_PHY_ROLE,
    LAN80XX_WPS_SYSTEM_ROLE,
} phy25g_wps_test_role_t;

typedef struct {
    mepa_bool_t                    enable;
    u8                             src_event;
    phy25g_host_protect_mode_t     mode;
    phy25g_wps_test_role_t         role;
    mepa_bool_t                    is_mac_change;
    mepa_bool_t                    reversion;
    mepa_bool_t                    filter_ena;
    u32                            assert_filter_val;
    u32                            deassert_filter_val;
    phy25g_wps_def_active_host_t   active_host;
    mepa_bool_t                    fc_signal_enable;
    u8                             ack_timer; /* 0 - 16 */
} phy25g_autofailover_t;

typedef struct {
    phy25g_autofailover_t failover_conf;
    u8 *Lineport_chn;
} phy25g_xconnect_get_conf_t;

/**<SYNCE>**/

#define LAN80XX_PHY_DIVIDER_1 0
#define LAN80XX_PHY_DIVIDER_2 1
#define LAN80XX_PHY_DIVIDER_4 2
#define LAN80XX_PHY_DIVIDER_8 3

/** \brief 25G Phy rckout clock frequency */
typedef enum {
    LAN80XX_RCKOUT_75_00,  /**< 75 MHz */
    LAN80XX_RCKOUT_37_50,  /**< 37.50 MHz */
    LAN80XX_RCKOUT_79_58,  /**< 79.58 MHz */
    LAN80XX_RCKOUT_39_79,  /**< 39.79 MHz */
    LAN80XX_RCKOUT_125_00,  /**< 125 MHz */
    LAN80XX_RCKOUT_62_50,  /**< 62.50 MHz */
    LAN80XX_RCKOUT_31_25,  /**< 31.25 MHz */
    LAN80XX_RCKOUT_15_625,  /**< 15.625 MHz */
    LAN80XX_RCKOUT_128_90625,  /**< 128.90625 MHz */
    LAN80XX_RCKOUT_64_453125,  /**< 64.453125 MHz */
    LAN80XX_RCKOUT_32_2265625,  /**< 32.2265625 MHz */
    LAN80XX_RCKOUT_80_56640625,  /**< 80.56640625 MHz */
    LAN80XX_RCKOUT_INVALID  /**< Other values are not allowed*/
} phy_25g_rckout_freq_t;

/** Applicable to Malibu only
 * *   brief clock sources */
typedef enum {
    LAN80XX_LINE0_RECVRD_CLOCK,         /**< Line0 Recovered clock */
    LAN80XX_LINE1_RECVRD_CLOCK,         /**< Line1 Recovered clock */
    LAN80XX_LINE2_RECVRD_CLOCK,         /**< Line2 Recovered clock */
    LAN80XX_LINE3_RECVRD_CLOCK,         /**< Line3 Recovered clock */
    LAN80XX_HOST0_RECVRD_CLOCK,         /**< Host0 Recovered clock */
    LAN80XX_HOST1_RECVRD_CLOCK,         /**< Host1 Recovered clock */
    LAN80XX_HOST2_RECVRD_CLOCK,         /**< Host2 Recovered clock */
    LAN80XX_HOST3_RECVRD_CLOCK,         /**< Host3 Recovered clock */
    LAN80XX_PTP_LTC,            /**< PTP LTC */
    LAN80XX_SREFCLK,                    /**< SREFCLK */
    LAN80XX_RESERVED = 14,          /**<Reserved>*/
    LAN80XX_NONE                /**<None>*/
} phy_25g_clk_sel_t;

/**
 * * Malibu Only
 * * \brief 25G Phy RCKOUTs Enum    **/

typedef enum rckout_sel_ {
    LAN80XX_RCKOUTA,
    LAN80XX_RCKOUTB
} phy_25g_rckout_sel_t;

typedef struct {
    phy_25g_clk_sel_t      src;         /**< RCVRD_CLK source */
    phy_25g_rckout_freq_t  freq;          /**< RCVRD_CLK freq*/
    mepa_bool_t            rcvd_clk_enable;          /**< Enable/Disable RCVRD_CLK */
    mepa_bool_t            los_squelch_enable;          /**< Enable/Disable LOS Squelch*/
    mepa_bool_t            link_sts_enable;          /**< Enable/Disable Link down squelch*/
    mepa_bool_t            auto_squelch_enable;          /**< Enable/Disable Squelch*/
    phy_25g_rckout_sel_t   rckout_sel;  /**< RCKOUT sel eg-'0' for RCKOUTA, '1' for RCKOUTB */
} phy_25g_rckout_conf_t;

/**
 * \brief Operating Mode of the PHY
 *
 * \param dev [IN]             mepa driver
 * \param port_no [IN]         port number
 * \param phy_mode [IN]        PCS/MAC Retimer Mode
 *
 * \return Return code.
 *  MEPA_RC_OK  on Sucess
 *  MEPA_RC_ERROR on Fail
 **/
mepa_rc lan80xx_operating_mode_set(const mepa_device_t *dev,
                                   const mepa_port_no_t port_no,
                                   phy25g_oper_mode_t phy_mode);


/**
 * \brief Get the configuration for SyncE
 *
 * \param dev [IN]             mepa driver
 * \param port_no [IN]         port number
 * \param rckout_conf          Returns the SyncE configuration
 *
 * \return Return code.
 *  MEPA_RC_OK  on Sucess
 *  MEPA_RC_ERROR on Fail
 **/
mepa_rc lan80xx_rckout_conf_get(mepa_device_t     *dev,
                                const mepa_port_no_t    port_no,
                                phy_25g_rckout_conf_t *const rckout_conf_a,
                                phy_25g_rckout_conf_t *const rckout_conf_b);

/**
 * \brief Set the configuration for SyncE
 *
 * \param dev [IN]             mepa driver
 * \param port_no [IN]         port number
 * \param rckout_conf          SyncE configuration
 *
 * \return Return code.
 *  MEPA_RC_OK  on Sucess
 *  MEPA_RC_ERROR on Fail
 **/

mepa_rc lan80xx_rckout_conf_set(mepa_device_t *dev,
                                const mepa_port_no_t port_no,
                                const phy_25g_rckout_conf_t *rckout_conf);

/**<SYNCE>**/

/** \brief Malibu25G Packet Monitor counters reset */
typedef enum {
    LAN80XX_PKT_MON_RST_ALL,    /**< Reset all counters        */
    LAN80XX_PKT_MON_RST_GOOD,   /**< Reset good crc counter    */
    LAN80XX_PKT_MON_RST_BAD,    /**< Reset bad crc counter     */
    LAN80XX_PKT_MON_RST_FRAG,   /**< Reset Fragment counter    */
    LAN80XX_PKT_MON_RST_LFAULT, /**< Reset local fault counter */
    LAN80XX_PKT_MON_RST_BER,    /**< Reset Ber counter         */
    LAN80XX_PKT_MON_RST_NONE,   /**< None                      */
} phy25g_pkt_mon_rst_t;

/** \brief Malibu25G Packet Monitor counters */
typedef struct {
    u32     good_crc;           /**< Good CRC packet count             */
    u32     bad_crc;            /**< Bad CRC packet count              */
    u32     fragmented;         /**< Fragmented packet count           */
    u32     lfault;             /**< Local fault packet count          */
    u32     ber;                /**< B-errored packet count            */
} phy25g_pkt_mon_counters_t;

/** \brief Malibu25G PHY Packet generator configuration */
typedef struct {
    mepa_bool_t     enable;              /**< Enable or disable packet generator    */
    mepa_bool_t     ptp;                 /**< PTP or standard frame                 */
    mepa_bool_t     ingress;             /**< Ingress or egress                     */
    mepa_bool_t     frames;              /**< frames or idles                       */
    mepa_bool_t     frame_single;        /**< Generate single packet                */
    mepa_bool_t     is_v2_1;             /**< 1 if it is PTPv2.1 ; 0 if it is PTPv2 */
    u16             etype;               /**< Ethertype                             */
    u8              trans_spec_majorSid;
    u8              minorSid;
    u32             message_type_spec;
    u8              pkt_len;             /**< Packet length,min=64,max=16KB         */
    u32             ipg_len;             /**< Inter Packet Gap                      */
    mepa_mac_t      smac;                /**< Source MAC address                    */
    mepa_mac_t      dmac;                /**< Destination MAC address               */
    u8              ptp_ts_sec;          /**< Seconds part of timestamp value       */
    u8              ptp_ts_ns;           /**< NanoSeconds part of ts value          */
    u8              srate;               /**< Srate for ptp frames                  */
} phy25g_pkt_gen_conf_t;

/** \brief Malibu25G PHY timestamp value array(holder) */
typedef struct {
    u16 timestamp[10][5];      /**< 5 bytes each of 10 timestamp values */
} phy25g_timestamp_val_t;




/**
 * \brief Gives the Status of PCS and PMA and PHY.
 *
 * \param dev [IN]             mepa driver
 * \param port_no [IN]         port number
 * \param status               Returns the link status and fault status of PMA and PCS and PHY status.
 *
 * \return Return code.
 *  MEPA_RC_OK  on Sucess
 *  MEPA_RC_ERROR on Fail
 **/
mepa_rc lan80xx_status_get(const mepa_device_t     *dev,
                           const mepa_port_no_t    port_no,
                           phy25g_status_t         *const status);

/**
 * \brief
 * Cofiguration for RX Eye Scan.
 *
 * \param dev     [IN]         mepa driver
 * \param port_no [IN]         port number
 * \param conf    [IN]         Eye scan configuration which includes scan type and enable.
 *
 * \return Return code.
 *  MEPA_RC_OK  on Sucess
 *  MEPA_RC_ERROR on Fail
 **/
mepa_rc lan80xx_rx_eye_scan_conf_set (const mepa_device_t          *dev,
                                      const mepa_port_no_t         port_no,
                                      mepa_bool_t                  is_line,
                                      const phy25g_rx_eye_scan_t   conf);
/**
 * \brief
 * Status of RX Eye Scan.
 *
 * \param dev     [IN]         mepa driver
 * \param port_no [IN]         port number
 * \param status               Eye Scan Status
 *
 * \return Return code.
 *  MEPA_RC_OK  on Sucess
 *  MEPA_RC_ERROR on Fail
 **/
mepa_rc lan80xx_rx_eye_scan_status_get (const mepa_device_t                *dev,
                                        const mepa_port_no_t               port_no,
                                        const phy25g_rx_eye_scan_t         scan,
                                        phy25g_rx_eye_scan_status_t        *const status);
/**
 * \brief
 *  Tx and Rx Equalization Status.
 *
 * \param dev [IN]             mepa driver
 * \param port_no [IN]         port number
 * \param status               Returns the status of Tx and Rx Equalization Configurations
 *
 * \return Return code.
 * MEPA_RC_OK on Sucess
 * MEPA_RC_ERROR on Fail
 **/
mepa_rc lan80xx_phy_tx_rx_equalization_status_get(const mepa_device_t        *dev,
                                                  const mepa_port_no_t       port_no,
                                                  mepa_bool_t                is_line,
                                                  phy25g_tx_rx_equ_status_t  *const status);

/**
 * \brief
 *  Tx and Rx Equalization Configuration.
 *
 * \param dev [IN]             mepa driver
 * \param port_no [IN]         port number
 * \param conf                 Tx and Rx Equalization Configurations
 *
 * \return Return code.
 * MEPA_RC_OK on Sucess
 * MEPA_RC_ERROR on Fail
 **/
mepa_rc lan80xx_phy_tx_rx_equalization_set(const mepa_device_t              *dev,
                                           const mepa_port_no_t             port_no,
                                           mepa_bool_t                      is_line,
                                           const phy25g_tx_rx_equa_conf_t   *const conf);

/**
 * \brief
 * To Configure the Client ID and SCL frequency of the SFP I2C
 * SCL frequency = (300 MHz) / [5 * (PRESCALE+1)]
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port number
 * \param client_id    [IN] I2C Client ID
 * \param prescalar    [IN] Prescalar for SCL Frequency (0x003B = 1 MHz,
 *                                                       0x0095 = 400 kHz(default),
 *                                                       0x0257 = 100 kHz)
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_phy_i2c_init(mepa_device_t         *dev,
                             const mepa_port_no_t  port_no,
                             const u8              client_id,
                             const u16             prescalar);

/**
 * To Configure different loopbacks which are not supported in
 * mepa_loopback_set( )
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param loopback     [IN] loopback enable configuration
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_phy_loopback_conf_set(mepa_device_t            *dev,
                                      const mepa_port_no_t     port_no,
                                      const phy25g_lp_types_t  *loopback);

/**
 * To get the loopback configuration on the PHY
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param loopback     [OUT] loopback configuration status
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_phy_loopback_conf_get(mepa_device_t         *dev,
                                      const mepa_port_no_t  port_no,
                                      phy25g_lp_get_t       *const loopback);

/**
 * To Enable/Disable the temperature sensor.
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param enable       [IN] Temperature sensor enable
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_temp_sensor_init(mepa_device_t          *dev,
                                 const mepa_port_no_t   port_no,
                                 u8                     threshold,
                                 mepa_bool_t            enable);


#define LAN80XX_AUTO_FAILOVER_EVENT_SD25G_PLL_LOL   1
#define LAN80XX_AUTO_FAILOVER_EVENT_SD25G_LOS       2
#define LAN80XX_AUTO_FAILOVER_EVENT_SD25G_LNK_DN    4
#define LAN80XX_AUTO_FAILOVER_EVENT_PCS1G_LNK_DN    16
#define LAN80XX_AUTO_FAILOVER_EVENT_FAILOVERIN0     32
#define LAN80XX_AUTO_FAILOVER_EVENT_FAILOVERIN1     64
#define LAN80XX_AUTO_FAILOVER_EVENT_SW_FORCE        128
/**
 * Packet Bist configuration set
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param conf         [IN] packet bist block Configuration
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_pkt_gen_conf(const mepa_device_t    *dev,
                             const mepa_port_no_t   port_no,
                             const phy25g_pkt_gen_conf_t  *const conf);

/**
 * Packet Monitor configuration
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param mon_enable   [IN] Monitor block enable
 * \param reset_cnt    [IN] Reset counter values
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_pkt_mon_conf(const mepa_device_t   *dev,
                             const mepa_port_no_t  port_no,
                             mepa_bool_t           mon_enable,
                             phy25g_pkt_mon_rst_t  reset_cnt);


/**
 * Packet Monitor configuration Get
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param mon_enable   [OUT] Monitor block enable
 * \param reset_cnt    [OUT] Reset counter values
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_pkt_mon_get(const mepa_device_t   *dev,
                            const mepa_port_no_t  port_no,
                            mepa_bool_t           *const mon_enable,
                            phy25g_pkt_mon_rst_t  *const reset_cnt);

/**
 * Packet Monitor Counters get
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param ts_rd        [IN] Timstamp counter read
 * \param pkt_counters [OUT] Counters value
 * \param ts_packet    [OUT] Timestamp values
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_pkt_mon_counters_get(const mepa_device_t        *dev,
                                     const mepa_port_no_t       port_no,
                                     mepa_bool_t                ts_rd,
                                     phy25g_pkt_mon_counters_t  *const pkt_counters,
                                     phy25g_timestamp_val_t     *const ts_packet);

/**
 * To get current temperature
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param value        [OUT] Temperature value
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_temp_sensor_get(mepa_device_t          *dev,
                                const mepa_port_no_t   port_no,
                                i16                    *const value);


/**
 * \brief LAN80XX Interrupt Events
*/
/* GPIO interrupts */
#define LAN80XX_GPIO_INTR_1                          LAN80XX_EVENT_BIT(63)
#define LAN80XX_GPIO_INTR_0                          LAN80XX_EVENT_BIT(62)

/* LINE MAC Tx Montitor Interrupts */
#define LAN80XX_LINE_MAC_LOCAL_ERR_STATE_INTR        LAN80XX_EVENT_BIT(61)
#define LAN80XX_LINE_MAC_REMOTE_ERR_STATE_INTR       LAN80XX_EVENT_BIT(60)
#define LAN80XX_LINE_MAC_IDLE_STATE_INTR             LAN80XX_EVENT_BIT(59)
#define LAN80XX_LINE_MAC_DIS_STATE_INTR              LAN80XX_EVENT_BIT(58)

/* HOST MAC Tx Monistor Interrupts */
#define LAN80XX_HOST_MAC_LOCAL_ERR_STATE_INTR        LAN80XX_EVENT_BIT(57)
#define LAN80XX_HOST_MAC_REMOTE_ERR_STATE_INTR       LAN80XX_EVENT_BIT(56)
#define LAN80XX_HOST_MAC_IDLE_STATE_INTR             LAN80XX_EVENT_BIT(55)
#define LAN80XX_HOST_MAC_DIS_STATE_INTR              LAN80XX_EVENT_BIT(54)

/* LINE MAC Interrupts */
#define LAN80XX_LINE_MAC_RX_IPG_SHRINK_INTR          LAN80XX_EVENT_BIT(53)
#define LAN80XX_LINE_MAC_RX_PREAMBLE_SHRINK_INTR     LAN80XX_EVENT_BIT(52)
#define LAN80XX_LINE_MAC_RX_PREAMBLE_MISMATCH_INTR   LAN80XX_EVENT_BIT(51)
#define LAN80XX_LINE_MAC_RX_PREAM_ERR_INTR           LAN80XX_EVENT_BIT(50)
#define LAN80XX_LINE_MAC_RX_NON_STD_PREAMBLE_INTR    LAN80XX_EVENT_BIT(49)
#define LAN80XX_LINE_MAC_RX_MPLS_MC_INTR             LAN80XX_EVENT_BIT(48)
#define LAN80XX_LINE_MAC_RX_MPLS_UC_INTR             LAN80XX_EVENT_BIT(47)
#define LAN80XX_LINE_MAC_RX_TAG_INTR                 LAN80XX_EVENT_BIT(46)
#define LAN80XX_LINE_MAC_TX_UNDERFLOW_INTR           LAN80XX_EVENT_BIT(45)
#define LAN80XX_LINE_MAC_TX_ABORT_INTR               LAN80XX_EVENT_BIT(44)

/* HOST MAC Interrupts */
#define LAN80XX_HOST_MAC_RX_IPG_SHRINK_INTR          LAN80XX_EVENT_BIT(43)
#define LAN80XX_HOST_MAC_RX_PREAMBLE_SHRINK_INTR     LAN80XX_EVENT_BIT(42)
#define LAN80XX_HOST_MAC_RX_PREAMBLE_MISMATCH_INTR   LAN80XX_EVENT_BIT(41)
#define LAN80XX_HOST_MAC_RX_PREAM_ERR_INTR           LAN80XX_EVENT_BIT(40)
#define LAN80XX_HOST_MAC_RX_NON_STD_PREAMBLE_INTR    LAN80XX_EVENT_BIT(39)
#define LAN80XX_HOST_MAC_RX_MPLS_MC_INTR             LAN80XX_EVENT_BIT(38)
#define LAN80XX_HOST_MAC_RX_MPLS_UC_INTR             LAN80XX_EVENT_BIT(37)
#define LAN80XX_HOST_MAC_RX_TAG_INTR                 LAN80XX_EVENT_BIT(36)
#define LAN80XX_HOST_MAC_TX_UNDERFLOW_INTR           LAN80XX_EVENT_BIT(35)
#define LAN80XX_HOST_MAC_TX_ABORT_INTR               LAN80XX_EVENT_BIT(34)

/* FC Buffer Interrupts */
#define LAN80XX_EGR_FC_BUFFER_FAULT_READ             LAN80XX_EVENT_BIT(33)
#define LAN80XX_EGR_FC_BUFFER_DED_INTR               LAN80XX_EVENT_BIT(32)
#define LAN80XX_EGR_FC_BUFFER_SEC_INTR               LAN80XX_EVENT_BIT(31)
#define LAN80XX_INGR_FC_BUFFER_FAULT_READ_INTR       LAN80XX_EVENT_BIT(30)
#define LAN80XX_INGR_FC_BUFFER_DED_INTR              LAN80XX_EVENT_BIT(29)
#define LAN80XX_INGR_FC_BUFFER_SEC_INTR              LAN80XX_EVENT_BIT(28)
#define LAN80XX_EGR_FC_BUFFER_INIT_DONE_INTR         LAN80XX_EVENT_BIT(27)
#define LAN80XX_INGR_FC_BUFFER_INIT_DONE_INTR        LAN80XX_EVENT_BIT(26)
#define LAN80XX_EGR_ECC_INTERRUPT_STATUS_INTR        LAN80XX_EVENT_BIT(25)
#define LAN80XX_INGR_ECC_INTERRUPT_STATUS_INTR       LAN80XX_EVENT_BIT(24)
#define LAN80XX_RX_UNDERFLOW_DROP_INTR               LAN80XX_EVENT_BIT(23)
#define LAN80XX_RX_OVERFLOW_DROP_INTR                LAN80XX_EVENT_BIT(22)
#define LAN80XX_TX_DATA_QUEUE_UNDERFLOW_DROP_INTR    LAN80XX_EVENT_BIT(21)
#define LAN80XX_TX_DATA_QUEUE_OVERFLOW_DROP_INTR     LAN80XX_EVENT_BIT(20)
#define LAN80XX_TX_CTRL_QUEUE_UNDERFLOW_DROP_INTR    LAN80XX_EVENT_BIT(19)
#define LAN80XX_TX_CTRL_QUEUE_OVERFLOW_DROP_INTR     LAN80XX_EVENT_BIT(18)
#define LAN80XX_RX_UNCORRECTED_FRM_DROP_INTR         LAN80XX_EVENT_BIT(17)
#define LAN80XX_TX_UNCORRECTED_FRM_DROP_INTR         LAN80XX_EVENT_BIT(16)
#define LAN80XX_XON_PAUSE_GEN_INTR                   LAN80XX_EVENT_BIT(15)
#define LAN80XX_XOFF_PAUSE_GEN_INTR                  LAN80XX_EVENT_BIT(14)

/* Rate Adaption FIFO Interrupts */
#define LAN80XX_L2H_RA_FIFO_OVERFLOW_INTR            LAN80XX_EVENT_BIT(13)
#define LAN80XX_L2H_RA_FIFO_UNDERFLOW_INTR           LAN80XX_EVENT_BIT(12)
#define LAN80XX_H2L_RA_FIFO_OVERFLOW_INTR            LAN80XX_EVENT_BIT(11)
#define LAN80XX_H2L_RA_FIFO_UNDERFLOW_INTR           LAN80XX_EVENT_BIT(10)

/* 25G PCS Interrupts */
#define LAN80XX_HOST_PCS25G_HI_BER_INTR              LAN80XX_EVENT_BIT(9)
#define LAN80XX_HOST_PCS25G_BLOCK_LOCK_INTR          LAN80XX_EVENT_BIT(8)
#define LAN80XX_HOST_PCS25G_ALIGN_DONE_INTR          LAN80XX_EVENT_BIT(7)
#define LAN80XX_LINE_PCS25G_HI_BER_INTR              LAN80XX_EVENT_BIT(6)
#define LAN80XX_LINE_PCS25G_BLOCK_LOCK_INTR          LAN80XX_EVENT_BIT(5)
#define LAN80XX_LINE_PCS25G_ALIGN_DONE_INTR          LAN80XX_EVENT_BIT(4)

/* 1G PCS Interrupts */
#define LAN80XX_HOST_PCS1G_OUT_OF_SYNC_INTR          LAN80XX_EVENT_BIT(3)
#define LAN80XX_HOST_PCS1G_LINK_DOWN_INTR            LAN80XX_EVENT_BIT(2)
#define LAN80XX_LINE_PCS1G_OUT_OF_SYNC_INTR          LAN80XX_EVENT_BIT(1)
#define LAN80XX_LINE_PCS1G_LINK_DOWN_INTR            LAN80XX_EVENT_BIT(0)

typedef u64 phy25g_events_t;

typedef enum {
    LAN80XX_EVT_INTR_A, /* Interrupt source A */
    LAN80XX_EVT_INTR_B, /* Interrupt source B */
} phy25g_evt_src_sel_t;

typedef struct {
    phy25g_events_t evt_set;   /* Event Sources to be configured */
    mepa_bool_t enable;    /* Enable or Disable selected Event sources */
    phy25g_evt_src_sel_t intr_sel; /* Interrupt to be routed to INTRA or INTRB */
} phy25g_event_conf_t;

/**
 * Events Enable/Disable
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param evt          [IN] Events Enable/Disable
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_event_conf_set(mepa_device_t          *dev,
                               const mepa_port_no_t   port_no,
                               const phy25g_event_conf_t  evt_set);


/**
 * \brief LAN80XX Extended Interrupt Events
*/
#define LAN80XX_L3_FIFO_ERROR_INTR                     LAN80XX_EVENT_BIT(63)
#define LAN80XX_L2_FIFO_ERROR_INTR                     LAN80XX_EVENT_BIT(62)
#define LAN80XX_L1_FIFO_ERROR_INTR                     LAN80XX_EVENT_BIT(61)
#define LAN80XX_L0_FIFO_ERROR_INTR                     LAN80XX_EVENT_BIT(60)
#define LAN80XX_H3_FIFO_ERROR_INTR                     LAN80XX_EVENT_BIT(59)
#define LAN80XX_H2_FIFO_ERROR_INTR                     LAN80XX_EVENT_BIT(58)
#define LAN80XX_H1_FIFO_ERROR_INTR                     LAN80XX_EVENT_BIT(57)
#define LAN80XX_H0_FIFO_ERROR_INTR                     LAN80XX_EVENT_BIT(56)
#define LAN80XX_L3_COND_ALT_UNF_DET_INTR               LAN80XX_EVENT_BIT(55)
#define LAN80XX_L2_COND_ALT_UNF_DET_INTR               LAN80XX_EVENT_BIT(54)
#define LAN80XX_L1_COND_ALT_UNF_DET_INTR               LAN80XX_EVENT_BIT(53)
#define LAN80XX_L0_COND_ALT_UNF_DET_INTR               LAN80XX_EVENT_BIT(52)
#define LAN80XX_H3_COND_ALT_UNF_DET_INTR               LAN80XX_EVENT_BIT(51)
#define LAN80XX_H2_COND_ALT_UNF_DET_INTR               LAN80XX_EVENT_BIT(50)
#define LAN80XX_H1_COND_ALT_UNF_DET_INTR               LAN80XX_EVENT_BIT(49)
#define LAN80XX_H0_COND_ALT_UNF_DET_INTR               LAN80XX_EVENT_BIT(48)
#define LAN80XX_L3_COND_ALT_DET_INTR                   LAN80XX_EVENT_BIT(47)
#define LAN80XX_L2_COND_ALT_DET_INTR                   LAN80XX_EVENT_BIT(46)
#define LAN80XX_L1_COND_ALT_DET_INTR                   LAN80XX_EVENT_BIT(45)
#define LAN80XX_L0_COND_ALT_DET_INTR                   LAN80XX_EVENT_BIT(44)
#define LAN80XX_H3_COND_ALT_DET_INTR                   LAN80XX_EVENT_BIT(43)
#define LAN80XX_H2_COND_ALT_DET_INTR                   LAN80XX_EVENT_BIT(42)
#define LAN80XX_H1_COND_ALT_DET_INTR                   LAN80XX_EVENT_BIT(41)
#define LAN80XX_H0_COND_ALT_DET_INTR                   LAN80XX_EVENT_BIT(40)
#define LAN80XX_L3_SWITCH_INTR                         LAN80XX_EVENT_BIT(39)
#define LAN80XX_L2_SWITCH_INTR                         LAN80XX_EVENT_BIT(38)
#define LAN80XX_L1_SWITCH_INTR                         LAN80XX_EVENT_BIT(37)
#define LAN80XX_L0_SWITCH_INTR                         LAN80XX_EVENT_BIT(36)
#define LAN80XX_H3_SWITCH_INTR                         LAN80XX_EVENT_BIT(35)
#define LAN80XX_H2_SWITCH_INTR                         LAN80XX_EVENT_BIT(34)
#define LAN80XX_H1_SWITCH_INTR                         LAN80XX_EVENT_BIT(33)
#define LAN80XX_H0_SWITCH_INTR                         LAN80XX_EVENT_BIT(32)
#define LAN80XX_WPS0_FAILOVER_INTR                     LAN80XX_EVENT_BIT(31)
#define LAN80XX_WPS1_FAILOVER_INTR                     LAN80XX_EVENT_BIT(30)
#define LAN80XX_WPS0_CONN_FAULT_INTR                   LAN80XX_EVENT_BIT(29)
#define LAN80XX_WPS1_CONN_FAULT_INTR                   LAN80XX_EVENT_BIT(28)
#define LAN80XX_WPS0_FC_ACK_TIMER_INTR                 LAN80XX_EVENT_BIT(27)
#define LAN80XX_WPS1_FC_ACK_TIMER_INTR                 LAN80XX_EVENT_BIT(26)
#define LAN80XX_LINE_PMA_RXEI_FILTERED_INTR            LAN80XX_EVENT_BIT(25)
#define LAN80XX_LINE_PMA_RESET_DONE_INTR               LAN80XX_EVENT_BIT(24)
#define LAN80XX_HOST_PMA_RXEI_FILTERED_INTR            LAN80XX_EVENT_BIT(23)
#define LAN80XX_HOST_PMA_RESET_DONE_INTR               LAN80XX_EVENT_BIT(22)
#define LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR   LAN80XX_EVENT_BIT(21)
#define LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR   LAN80XX_EVENT_BIT(20)
#define LAN80XX_LINE_MAC_MM_PRMPT_ACTIVE_INTR          LAN80XX_EVENT_BIT(19)
#define LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR   LAN80XX_EVENT_BIT(18)
#define LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR   LAN80XX_EVENT_BIT(17)
#define LAN80XX_HOST_MAC_MM_PRMPT_ACTIVE_INTR          LAN80XX_EVENT_BIT(16)
#define LAN80XX_LINE_PMAC_RX_PREAMBLE_SHRINK           LAN80XX_EVENT_BIT(15)
#define LAN80XX_LINE_PMAC_RX_PREAMBLE_MISMATCH         LAN80XX_EVENT_BIT(14)
#define LAN80XX_LINE_PMAC_RX_PREAMBLE_ERR              LAN80XX_EVENT_BIT(13)
#define LAN80XX_LINE_PMAC_RX_NON_STD_PREAMBLE_INTR     LAN80XX_EVENT_BIT(12)
#define LAN80XX_LINE_PMAC_RX_MPLS_MC_INTR              LAN80XX_EVENT_BIT(11)
#define LAN80XX_LINE_PMAC_RX_MPLS_UC_INTR              LAN80XX_EVENT_BIT(10)
#define LAN80XX_LINE_PMAC_TX_UNDERFLOW_INTR            LAN80XX_EVENT_BIT(9)
#define LAN80XX_LINE_PMAC_TX_ABORT_INTR                LAN80XX_EVENT_BIT(8)
#define LAN80XX_HOST_PMAC_RX_PREAMBLE_SHRINK           LAN80XX_EVENT_BIT(7)
#define LAN80XX_HOST_PMAC_RX_PREAMBLE_MISMATCH         LAN80XX_EVENT_BIT(6)
#define LAN80XX_HOST_PMAC_RX_PREAMBLE_ERR              LAN80XX_EVENT_BIT(5)
#define LAN80XX_HOST_PMAC_RX_NON_STD_PREAMBLE_INTR     LAN80XX_EVENT_BIT(4)
#define LAN80XX_HOST_PMAC_RX_MPLS_MC_INTR              LAN80XX_EVENT_BIT(3)
#define LAN80XX_HOST_PMAC_RX_MPLS_UC_INTR              LAN80XX_EVENT_BIT(2)
#define LAN80XX_HOST_PMAC_TX_UNDERFLOW_INTR            LAN80XX_EVENT_BIT(1)
#define LAN80XX_HOST_PMAC_TX_ABORT_INTR                LAN80XX_EVENT_BIT(0)

typedef u64 phy25g_ext_events_t;

typedef struct {
    phy25g_ext_events_t ext_evt_set;   /* Event Sources to be configured */
    mepa_bool_t enable;    /* Enable or Disable selected Event sources */
    phy25g_evt_src_sel_t intr_sel; /* Interrupt to be routed to INTRA or INTRB */
} phy25g_ext_event_conf_t;

/**
 * Extended Events Enable/Disable
 *
 * \param dev          [IN] mepa driver
 * \param port_no      [IN] Port Number
 * \param ext_evt      [IN] Events Enable/Disable
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_ext_event_conf_set(mepa_device_t                 *dev,
                                   const mepa_port_no_t          port_no,
                                   const phy25g_ext_event_conf_t     ext_evt_conf);



/**
 * Event Get
 *
 * \param dev          [IN]  mepa driver
 * \param port_no      [IN]  Port Number
 * \param evt          [OUT] Get the Events Enabled
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_event_conf_get(mepa_device_t          *dev,
                               const mepa_port_no_t   port_no,
                               phy25g_events_t    *const evt);

/**
 * Extended Event Get
 *
 * \param dev          [IN]  mepa driver
 * \param port_no      [IN]  Port Number
 * \param ext_evt      [OUT] Get the Events Enabled
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_ext_event_conf_get(mepa_device_t          *dev,
                                   const mepa_port_no_t   port_no,
                                   phy25g_ext_events_t    *const ext_evt);

/**
 * Event Poll
 *
 * \param dev          [IN]  mepa driver
 * \param port_no      [IN]  Port Number
 * \param evt          [OUT] Returns the Event Triggered
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_event_poll(mepa_device_t          *dev,
                           const mepa_port_no_t   port_no,
                           phy25g_events_t        *const evt);

/**
 * Extended Event Poll
 *
 * \param dev          [IN]  mepa driver
 * \param port_no      [IN]  Port Number
 * \param ext_evt      [OUT] Returns the Event Triggered
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_ext_event_poll(mepa_device_t          *dev,
                               const mepa_port_no_t   port_no,
                               phy25g_ext_events_t    *const ext_evt);

/**
 * Clause 45 CSR Write
 *
 * \param dev          [IN]  mepa driver
 * \param port_no      [IN]  Port Number
 * \param mmd          [IN]  MMD Device ID of Register
 * \param addr         [IN]  Register Address
 * \param value        [IN]  Value of Register
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_phy_csr_write(mepa_device_t               *dev,
                              const mepa_port_no_t        port_no,
                              const u32                   mmd,
                              const u32                   addr,
                              const u32                   value);

/**
 * Clause 45 CSR Read
 *
 * \param dev          [IN]  mepa driver
 * \param port_no      [IN]  Port Number
 * \param mmd          [IN]  MMD Device ID of Register
 * \param addr         [IN]  Register Address
 * \param value        [OUT] Value of Register
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_phy_csr_read(mepa_device_t               *dev,
                             const mepa_port_no_t        port_no,
                             const u16                   mmd,
                             const u32                   addr,
                             u32                         *const value);


/**
 * Flow Control Configuration
 *
 * \param dev          [IN]  mepa driver
 * \param port_no      [IN]  Port Number
 * \param enable       [IN]  Enable/Disable Flow Control
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_flow_control_set(const mepa_device_t     *dev,
                                 mepa_port_no_t          port_no,
                                 mepa_bool_t             enable);

/** \brief Host/Line PMAC Counters */
typedef struct {
    /* Rx RMON counters */
    u64   if_rx_good_octets;              /**< In Good octets     */
    u64   if_rx_bad_octets;               /**< In Bad octets     */
    u32   if_rx_pause_pkts;               /**< In pause        */
    u32   if_rx_ucast_pkts;               /**< In unicasts     */
    u32   if_rx_multicast_pkts;           /**< In multicasts   */
    u32   if_rx_broadcast_pkts;           /**< In broadcasts   */
    u32   if_rx_errors;                   /**< In errors       */

    u32   if_rx_CRCAlignErrors;           /**< In CRC errors      */
    u32   if_rx_UndersizePkts;            /**< In Undersize pkts  */
    u32   if_rx_OversizePkts;             /**< In Oversize pkts   */
    u32   if_rx_Fragments;                /**< In Fragments       */
    u32   if_rx_Jabbers;                  /**< In Jabbers         */
    u32   if_rx_Pkts64Octets;             /**< In Pkts64Octets         */
    u32   if_rx_Pkts65to127Octets;        /**< In Pkts65to127Octets    */
    u32   if_rx_Pkts128to255Octets;       /**< In Pkts128to255Octets   */
    u32   if_rx_Pkts256to511Octets;       /**< In Pkts256to511Octets   */
    u32   if_rx_Pkts512to1023Octets;      /**< In Pkts512to1023Octets  */
    u32   if_rx_Pkts1024to1518Octets;     /**< In Pkts1024to1518Octets */
    u32   if_rx_Pkts1519toMaxOctets;      /**< In Pkts1519toMaxOctets  */

    u32   if_rx_align_lost;               /**< Align Lost Frame */
    u32   if_rx_assmbly_err;              /**< Assembly Error in P frame */
    u32   if_rx_smd_err;                  /**< SMD Error */
    u32   if_rx_assmblt_ok;               /**< Frames Reassembled Sucessfully */
    u32   if_rx_merge_frag;               /**< P Fragements Received */
    u32   if_tx_pfrag_cnt;                /**< P Fragments Transmitted */

    /* Tx RMON counters */
    u64   if_tx_octets;                   /**< Out octets      */
    u32   if_tx_pause_pkts;               /**< Out pause       */
    u32   if_tx_ucast_pkts;               /**< Out unicasts    */
    u32   if_tx_multicast_pkts;           /**< Out multicasts  */
    u32   if_tx_broadcast_pkts;           /**< Out broadcasts  */

    u32   if_tx_Pkts64Octets;             /**< Out Pkts64Octets         */
    u32   if_tx_Pkts65to127Octets;        /**< Out Pkts65to127Octets    */
    u32   if_tx_Pkts128to255Octets;       /**< Out Pkts128to255Octets   */
    u32   if_tx_Pkts256to511Octets;       /**< Out Pkts256to511Octets   */
    u32   if_tx_Pkts512to1023Octets;      /**< Out Pkts512to1023Octets  */
    u32   if_tx_Pkts1024to1518Octets;     /**< Out Pkts1024to1518Octets */
    u32   if_tx_Pkts1519toMaxOctets;      /**< Out Pkts1519toMaxOctets  */
} phy25g_pmac_counters_t;


mepa_rc lan80xx_pmac_counters_get(mepa_device_t                  *dev,
                                  const mepa_port_no_t           port_no,
                                  mepa_bool_t                    is_host,
                                  phy25g_pmac_counters_t         *const counters);


mepa_rc lan80xx_pmac_counters_clear(mepa_device_t                  *dev,
                                    const mepa_port_no_t           port_no,
                                    mepa_bool_t                    is_host);



mepa_rc lan80xx_xconnect_anylinetoanyhost(mepa_device_t *dev, mepa_port_no_t port_no, mepa_bool_t xconnect_enable, u8 LineDefaultCh[MAX_PORTS]);
mepa_rc lan80xx_xconnect_hostfailover_Protection(mepa_device_t  *dev, mepa_port_no_t port_no, const phy25g_autofailover_t *conf);
mepa_rc lan80xx_xconnect_failover(mepa_device_t *dev, const mepa_port_no_t port_no);
mepa_rc lan80xx_xconnect_conf_get(mepa_device_t  *dev, const mepa_port_no_t   port_no, phy25g_xconnect_get_conf_t   *const get_conf);
mepa_rc lan80xx_xconnect_force_failover(mepa_device_t *dev, const mepa_port_no_t port_no);
#endif //  end of _LAN80XX_H_
