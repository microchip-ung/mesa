// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_phy_api.h>

/**
 * \file
 * \brief PHY API
 * \details This header file describes PHY control functions
 */

#ifndef _VTSS_PHY_1G_API_H_
#define _VTSS_PHY_1G_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/** \brief PHY part ids supported */
typedef enum {
    VTSS_PHY_TYPE_NONE    = 0,    /* Unknown */
    VTSS_PHY_TYPE_8201    = 8201, /* VSC8201 (Mustang) */
    VTSS_PHY_TYPE_8204    = 8204, /* VSC8204 (Blazer) */
    VTSS_PHY_TYPE_8211    = 8211, /* VSC8211 (Cobra) */
    VTSS_PHY_TYPE_8221    = 8221, /* VSC8221 (Cobra) */
    VTSS_PHY_TYPE_8224    = 8224, /* VSC8224 (Quattro) */
    VTSS_PHY_TYPE_8234    = 8234, /* VSC8234 (Quattro) */
    VTSS_PHY_TYPE_8244    = 8244, /* VSC8244 (Quattro) */
    VTSS_PHY_TYPE_8538    = 8538, /* VSC8538 (Spyder) */
    VTSS_PHY_TYPE_8558    = 8558, /* VSC8558 (Spyder) */
    VTSS_PHY_TYPE_8574    = 8574, /* VSC8574 (Tesla) */
    VTSS_PHY_TYPE_8504    = 8504, /* VSC8504 (Tesla) */
    VTSS_PHY_TYPE_8572    = 8572, /* VSC8572 (Tesla) */
    VTSS_PHY_TYPE_8552    = 8552, /* VSC8552 (Tesla) */
    VTSS_PHY_TYPE_8501    = 8501, /* VSC8502 (Nano) */
    VTSS_PHY_TYPE_8502    = 8502, /* VSC8501 (Nano) */
    VTSS_PHY_TYPE_7435    = 7435, /* VSC7435 (Integrated PHY in ServalT) */
    VTSS_PHY_TYPE_8658    = 8658, /* VSC8658 (GTO) */
    VTSS_PHY_TYPE_8601    = 8601, /* VSC8601 (Cooper) */
    VTSS_PHY_TYPE_8641    = 8641, /* VSC8641 (Cooper) */
    VTSS_PHY_TYPE_7385    = 7385, /* VSC7385 (Northolt) */
    VTSS_PHY_TYPE_7388    = 7388, /* VSC7388 (Luton) */
    VTSS_PHY_TYPE_7389    = 7389, /* VSC7389, VSC7391 (Luton16/16r) */
    VTSS_PHY_TYPE_7390    = 7390, /* VSC7390 (Luton24) */
    VTSS_PHY_TYPE_7395    = 7395, /* VSC7395, VSC7396 (Luton5e/5m) */
    VTSS_PHY_TYPE_7398    = 7398, /* VSC7398, (Luton8) */
    VTSS_PHY_TYPE_7500    = 7500, /* VSC7500 (Intrigue) */
    VTSS_PHY_TYPE_7501    = 7501, /* VSC7501 (Intrigue) */
    VTSS_PHY_TYPE_7502    = 7502, /* VSC7502 (Intrigue) */
    VTSS_PHY_TYPE_7503    = 7503, /* VSC7503 (Intrigue) */
    VTSS_PHY_TYPE_7504    = 7504, /* VSC7504 (Intrigue) */
    VTSS_PHY_TYPE_7505    = 7505, /* VSC7505 (Intrigue) */
    VTSS_PHY_TYPE_7506    = 7506, /* VSC7506 (Intrigue) */
    VTSS_PHY_TYPE_7507    = 7507, /* VSC7507 (Intrigue) */
    VTSS_PHY_TYPE_8634    = 8634, /* VSC8634 (Enzo) */
    VTSS_PHY_TYPE_8664    = 8664, /* VSC8664 (Enzo) */
    VTSS_PHY_TYPE_8512    = 8512, /* VSC8512 (Atom12) */
    VTSS_PHY_TYPE_8522    = 8522, /* VSC8522 (Atom12) */
    VTSS_PHY_TYPE_7420    = 7420, /* VSC7420 (Luton26) */
    VTSS_PHY_TYPE_8582    = 8582, /* VSC8582 (Viper) */
    VTSS_PHY_TYPE_8584    = 8584, /* VSC8584 (Viper) */
    VTSS_PHY_TYPE_8575    = 8575, /* VSC8575 (Viper) */
    VTSS_PHY_TYPE_8564    = 8564, /* VSC8564 (Viper) */
    VTSS_PHY_TYPE_8562    = 8562, /* VSC8562 (Viper) */
    VTSS_PHY_TYPE_8586    = 8586, /* VSC8586 (Viper) */
    VTSS_PHY_TYPE_8514    = 8514, /* VSC8514 (Elise) */
    VTSS_PHY_TYPE_8541    = 8541, /* 8541 (Mini) */
    VTSS_PHY_TYPE_AQR_407 =  407, /* AQR407 (Aquantia) */
    VTSS_PHY_TYPE_AQR_409 =  409, /* AQR409 (Aquantia) */
    VTSS_PHY_TYPE_AQR_411 =  411, /* AQR411/411C (Aquantia) */
    VTSS_PHY_TYPE_AQR_412 =  412, /* AQR412/412C (Aquantia) */
} vtss_phy_part_number_t;

/** \brief PHY LED modes */
typedef enum {
  VTSS_PHY_LED_MODE_LINK_ACTIVITY, /** No link in any speed on any media interface./Valid link at any speed on any media interface. Blink or pulse-stretch = Valid link at any speed on any media interface with activity present.*/
  VTSS_PHY_LED_MODE_LINK1000_ACTIVITY, /** No link in 1000BASE-T/Valid 1000BASE-T link. Blink or pulse-stretch = Valid 1000BASE-T link with activity present*/
  VTSS_PHY_LED_MODE_LINK100_ACTIVITY, /** No link in 100BASE-T/Valid 100BASE-T link. Blink or pulse-stretch = Valid 100BASE-T link with activity present*/
  VTSS_PHY_LED_MODE_LINK10_ACTIVITY, /** No link in 10BASE-T/Valid 10BASE-T link. Blink or pulse-stretch = Valid 10BASE-T link with activity present*/
  VTSS_PHY_LED_MODE_LINK100_1000_ACTIVITY, /** No link in 100BASE-T, 1000BASE-FX, or 1000BASE-TX/Valid 100BASE-T, 1000BASE-FX, or 1000BASE-TX link.Blink or pulse-stretch = Valid 100BASE-T, 1000BASE-FX, or 1000BASE-TX link with activity present.*/
  VTSS_PHY_LED_MODE_LINK10_1000_ACTIVITY, /** No link in 10BASE-T, 1000BASE-FX, or 1000BASE-TX/Valid 10BASE-T, 1000BASE-FX, or 1000BASE-TX link.Blink or pulse-stretch = Valid 10BASE-T, 1000BASE-FX, or 1000BASE-TX link with activity present.*/
  VTSS_PHY_LED_MODE_LINK10_100_ACTIVITY, /** No link in 10BASE-T, 100BASE-FX, or 100BASE-TX/Valid 10BASE-T, 100BASE-FX, or 100BASE-TX link.Blink or pulse-stretch = Valid 10BASE-T, 100BASE-FX, or 100BASE-TX link with activity present.*/
  VTSS_PHY_LED_MODE_LINK100BASE_FX_1000BASE_X_ACTIVITY, /** No link in 100BASE-FX or 1000BASE-X/ Valid 100BASE-FX or 1000BASE-X link. Blink or pulse-stretch = Valid 100BASE-FX or 1000BASE-X link with activity present.*/
  VTSS_PHY_LED_MODE_DUPLEX_COLLISION, /** Link established in half-duplex mode, or no link established. Link established in full-duplex mode.Blink or pulse-stretch = Link established in half-duplex mode but collisions are present*/
  VTSS_PHY_LED_MODE_COLLISION, /**No collision detected.Blink or pulse-stretch = Collision detected.*/
  VTSS_PHY_LED_MODE_ACTIVITY,  /** No activity present.Blink or pulse-stretch = Activity present*/
  VTSS_PHY_LED_MODE_BASE100_FX_1000BASE_X_FIBER_ACTIVITY, /**No 100BASE-FX or 1000BASE-X activity present. Blink or pulse-stretch = 100BASE-FX or 1000BASE-X activity present */
  VTSS_PHY_LED_MODE_AUTONEGOTIATION_FAULT,  /**No autonegotiation fault present., Autonegotiation fault occurred.*/
  VTSS_PHY_LED_MODE_LINK1000BASE_X_ACTIVITY, /**No link in 1000BASE-X. Valid 1000BASE-X link.*/
  VTSS_PHY_LED_MODE_LINK100BASE_FX_ACTIVITY, /**No link in 100BASE-FX.*/
  VTSS_PHY_LED_MODE_BASE1000_ACTIVITY,   /**No 1000BASE-X activity present.Blink or pulse-stretch = 1000BASE-X activity present.*/
  VTSS_PHY_LED_MODE_BASE100_FX_ACTIVITY, /**No 100BASE-FX activity present, Blink or pulse-stretch = 100BASE-FX activity present.*/
  VTSS_PHY_LED_MODE_FORCE_LED_OFF,  /** De-asserts the LED*/
  VTSS_PHY_LED_MODE_FORCE_LED_ON,   /** Asserts the LED*/
  VTSS_PHY_LED_MODE_FAST_LINK_FAIL, /** Enable fast link fail on the LED*/
  VTSS_PHY_LED_MODE_LINK_TX, /** Link Transmit Indication */
  VTSS_PHY_LED_MODE_LINK_RX, /** Link Recieve Indication */
  VTSS_PHY_LED_MODE_LINK_FAULT, /** Link Fault Indication */
} vtss_phy_led_mode_t;

#if !defined(VTSS_OPT_PHY_LED_MODE_BACKWARD_COMPATIBLE)
#define VTSS_OPT_PHY_LED_MODE_BACKWARD_COMPATIBLE 1 /**< Backward compatible with old names by default */
#endif

#if VTSS_OPT_PHY_LED_MODE_BACKWARD_COMPATIBLE
#define LINK_ACTIVITY                         VTSS_PHY_LED_MODE_LINK_ACTIVITY                        /**< Backward compatibility */
#define LINK1000_ACTIVITY                     VTSS_PHY_LED_MODE_LINK1000_ACTIVITY                    /**< Backward compatibility */
#define LINK100_ACTIVITY                      VTSS_PHY_LED_MODE_LINK100_ACTIVITY                     /**< Backward compatibility */
#define LINK10_ACTIVITY                       VTSS_PHY_LED_MODE_LINK10_ACTIVITY                      /**< Backward compatibility */
#define LINK100_1000_ACTIVITY                 VTSS_PHY_LED_MODE_LINK100_1000_ACTIVITY                /**< Backward compatibility */
#define LINK10_1000_ACTIVITY                  VTSS_PHY_LED_MODE_LINK10_1000_ACTIVITY                 /**< Backward compatibility */
#define LINK10_100_ACTIVITY                   VTSS_PHY_LED_MODE_LINK10_100_ACTIVITY                  /**< Backward compatibility */
#define LINK100BASE_FX_1000BASE_X_ACTIVITY    VTSS_PHY_LED_MODE_LINK100BASE_FX_1000BASE_X_ACTIVITY   /**< Backward compatibility */
#define DUPLEX_COLLISION                      VTSS_PHY_LED_MODE_DUPLEX_COLLISION                     /**< Backward compatibility */
#define COLLISION                             VTSS_PHY_LED_MODE_COLLISION                            /**< Backward compatibility */
#define ACTIVITY                              VTSS_PHY_LED_MODE_ACTIVITY                             /**< Backward compatibility */
#define BASE100_FX_1000BASE_X_FIBER_ACTIVITY  VTSS_PHY_LED_MODE_BASE100_FX_1000BASE_X_FIBER_ACTIVITY /**< Backward compatibility */
#define AUTONEGOTIATION_FAULT                 VTSS_PHY_LED_MODE_AUTONEGOTIATION_FAULT                /**< Backward compatibility */
#define LINK1000BASE_X_ACTIVITY               VTSS_PHY_LED_MODE_LINK1000BASE_X_ACTIVITY              /**< Backward compatibility */
#define LINK100BASE_FX_ACTIVITY               VTSS_PHY_LED_MODE_LINK100BASE_FX_ACTIVITY              /**< Backward compatibility */
#define BASE1000_ACTIVITY                     VTSS_PHY_LED_MODE_BASE1000_ACTIVITY                    /**< Backward compatibility */
#define BASE100_FX_ACTIVITY                   VTSS_PHY_LED_MODE_BASE100_FX_ACTIVITY                  /**< Backward compatibility */
#define FORCE_LED_OFF                         VTSS_PHY_LED_MODE_FORCE_LED_OFF                        /**< Backward compatibility */
#define FORCE_LED_ON                          VTSS_PHY_LED_MODE_FORCE_LED_ON                         /**< Backward compatibility */
#define FAST_LINK_FAIL                        VTSS_PHY_LED_MODE_FAST_LINK_FAIL                       /**< Backward compatibility */
#endif

/** \brief List of LED pins per port */
typedef enum {
  VTSS_PHY_LED0,
  VTSS_PHY_LED1,
  VTSS_PHY_LED2,
  VTSS_PHY_LED3
} vtss_phy_led_number_t;

#define LED0 VTSS_PHY_LED0 /**< Backward compatibility */
#define LED1 VTSS_PHY_LED1 /**< Backward compatibility */
#define LED2 VTSS_PHY_LED2 /**< Backward compatibility */
#define LED3 VTSS_PHY_LED3 /**< Backward compatibility */

/** \brief LED model selection */
typedef struct
{
  vtss_phy_led_mode_t mode; /**< LED blink mode*/
  vtss_phy_led_number_t number; /**< Which LED to configure with the above mode*/
} vtss_phy_led_mode_select_t;

/** \brief Phy type information */
typedef struct
{
    u16             part_number;    /**< Part number */
    u16             revision;       /**< Chip revision */
    u8              port_cnt;       /**< The number of PHY ports in the chip */
    u16             channel_id;     /**< Channel id */
    u16             base_port_no;   /**< The port number for the first PHY port within the chip.   */
    vtss_port_no_t  phy_api_base_no;/**< First API no within this phy (in' case of multiple channels) */
} vtss_phy_type_t;

// Defines for micro patch configuration settings
#define MAX_CFG_BUF_SIZE 38 /**< Defines the maximum size of the micro patch CFG buffer can be for all chip families. */
#define MAX_STAT_BUF_SIZE 8 /**< Defines the number bytes in the PHY patch status array */


/* - Reset --------------------------------------------------------- */

/** \brief PHY media interface type */
typedef enum {
    VTSS_PHY_MEDIA_IF_CU,                      /**< Copper Interface */
    VTSS_PHY_MEDIA_IF_SFP_PASSTHRU,            /**< Fiber/Cu SFP Pass-thru */
    VTSS_PHY_MEDIA_IF_FI_1000BX,               /**< 1000Base-X */
    VTSS_PHY_MEDIA_IF_FI_100FX,                /**< 100Base-FX */
    VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU,         /**< AMS - Cat5/SerDes/CuSFP passthru - Note the phy mode must be set to VTSS_PHY_MODE_ANEG */
    VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU,         /**< AMS - Fiber passthru - Note the phy mode must be set to VTSS_PHY_MODE_ANEG */
    VTSS_PHY_MEDIA_IF_AMS_CU_1000BX,           /**< AMS - Cat5/1000BX/CuSFP */
    VTSS_PHY_MEDIA_IF_AMS_FI_1000BX,
    VTSS_PHY_MEDIA_IF_AMS_CU_100FX,            /**< AMS - Cat5/100FX/CuSFP */
    VTSS_PHY_MEDIA_IF_AMS_FI_100FX
} vtss_phy_media_interface_t;

/** \brief PHY media interface type */
typedef enum {
    VTSS_PHY_MDIX_AUTO,                /**< Copper media MDI auto detected */
    VTSS_PHY_MDI,                      /**< Copper media forced to MDI */
    VTSS_PHY_MDIX,                     /**< Copper media forced to MDI-X (Crossed cable) */
} vtss_phy_mdi_t;

/** \brief RGMII skews */
typedef enum {
    VTSS_RGMII_SKEW_DELAY_200_PSEC = 200,      /**< RGMII 200 Pico-Second Skew  */
    VTSS_RGMII_SKEW_DELAY_800_PSEC = 800,      /**< RGMII 800 Pico-Second Skew  */
    VTSS_RGMII_SKEW_DELAY_1100_PSEC = 1100,    /**< RGMII 1100 Pico-Second Skew */
    VTSS_RGMII_SKEW_DELAY_1700_PSEC = 1700,    /**< RGMII 1700 Pico-Second Skew */
    VTSS_RGMII_SKEW_DELAY_2000_PSEC = 2000,    /**< RGMII 2000 Pico-Second Skew */
    VTSS_RGMII_SKEW_DELAY_2300_PSEC = 2300,    /**< RGMII 2300 Pico-Second Skew */
    VTSS_RGMII_SKEW_DELAY_2600_PSEC = 2600,    /**< RGMII 2600 Pico-Second Skew */
    VTSS_RGMII_SKEW_DELAY_3400_PSEC = 3400     /**< RGMII 3400 Pico-Second Skew */
} vtss_rgmii_skew_delay_psec_t;

#define rgmii_skew_delay_200_psec   VTSS_RGMII_SKEW_DELAY_200_PSEC  /**< Backward compatibility */
#define rgmii_skew_delay_800_psec   VTSS_RGMII_SKEW_DELAY_800_PSEC  /**< Backward compatibility */
#define rgmii_skew_delay_1100_psec  VTSS_RGMII_SKEW_DELAY_1100_PSEC /**< Backward compatibility */
#define rgmii_skew_delay_1700_psec  VTSS_RGMII_SKEW_DELAY_1700_PSEC /**< Backward compatibility */
#define rgmii_skew_delay_2000_psec  VTSS_RGMII_SKEW_DELAY_2000_PSEC /**< Backward compatibility */
#define rgmii_skew_delay_2300_psec  VTSS_RGMII_SKEW_DELAY_2300_PSEC /**< Backward compatibility */
#define rgmii_skew_delay_2600_psec  VTSS_RGMII_SKEW_DELAY_2600_PSEC /**< Backward compatibility */
#define rgmii_skew_delay_3400_psec  VTSS_RGMII_SKEW_DELAY_3400_PSEC /**< Backward compatibility */

/** \brief Backward compatibility */
typedef vtss_rgmii_skew_delay_psec_t rgmii_skew_delay_psec_t;

/** \brief PHY RGMII configuration */
typedef struct {
    u16 rx_clk_skew_ps; /**< Rx clock skew in pico seconds, see rgmii_skew_delay_psec_t for options  */
    u16 tx_clk_skew_ps; /**< Tx clock skew in pico seconds, see rgmii_skew_delay_psec_t for options  */
} vtss_phy_rgmii_conf_t;

/** \brief PHY TBI configuration */
typedef struct {
    BOOL aneg_enable;  /**< Enable auto negotiation */
} vtss_phy_tbi_conf_t;

/** \brief PHY forced reset interface type */
typedef enum {
    VTSS_PHY_FORCE_RESET = 0,          /**< Default: Force reset of PHY, regardless of Config and HW MAC/MEDIA settings */
    VTSS_PHY_NOFORCE_RESET = 1,        /**< Only reset PHY if SW Config and HW config of MAC/MEDIA settings differ */
} vtss_phy_forced_reset_t;

/** \brief PHY packet mode configuration */
typedef enum {
    VTSS_PHY_PKT_MODE_IEEE_1_5_KB,  /**< IEEE NORMAL 1.5KB Pkt Length */
    VTSS_PHY_PKT_MODE_JUMBO_9_KB,   /**< JUMBO 9KB Pkt Length */
    VTSS_PHY_PKT_MODE_JUMBO_12_KB,  /**< JUMBO 12KB Pkt Length */
} vtss_phy_pkt_mode_t;

/** \brief PHY reset structure */
typedef struct {
    vtss_port_interface_t      mac_if;   /**< MAC interface */
    vtss_phy_media_interface_t media_if; /**< Media interface */
    vtss_phy_rgmii_conf_t      rgmii;    /**< RGMII MAC interface setup */
    vtss_phy_tbi_conf_t        tbi;      /**< TBI setup */
    vtss_phy_forced_reset_t    force;    /**< Force or NoForce PHY port Reset during vtss_phy_reset_private, Only used for Selected PHY Families */
    vtss_phy_pkt_mode_t        pkt_mode; /**< packet mode*/
    BOOL		       i_cpu_en; /**< Set to TRUE to enable internal 8051 CPU (Enzo and Spyder family only)*/
} vtss_phy_reset_conf_t;


/**
 * \brief Must be call previous to port PHY Reset (vtss_phy_reset).
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number (MUST be the first port for the chip).
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_pre_reset(const vtss_inst_t           inst,
                           const vtss_port_no_t        port_no);


/**
 * \brief Must be call after port PHY Reset (vtss_phy_reset).
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number (Any port with the chip can be used).
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_post_reset(const vtss_inst_t           inst,
                            const vtss_port_no_t        port_no);


/**
 * \brief Must be call before a system reset.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number (Any port with the chip can be used).
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_pre_system_reset(const vtss_inst_t           inst,
                                  const vtss_port_no_t        port_no);



/**
 * \brief Reset PHY.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Reset configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_reset(const vtss_inst_t           inst,
                       const vtss_port_no_t        port_no,
                       const vtss_phy_reset_conf_t *const conf);

/**
 * \brief Get reset configuration
 *
 * \param inst [IN]  Target instance reference
 * \param port_no [IN]  Port number (Any port within the chip can be used)
 * \param conf [OUT] Reset configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_reset_get(const vtss_inst_t           inst,
                           const vtss_port_no_t        port_no,
                           vtss_phy_reset_conf_t       *conf);


/* - Main configuration and status --------------------------------- */

/** \brief PHY mode */
typedef enum {
    VTSS_PHY_MODE_ANEG,       /**< Auto negoatiation */
    VTSS_PHY_MODE_FORCED,     /**< Forced mode */
    VTSS_PHY_MODE_POWER_DOWN  /**< Power down (disabled) */
} vtss_phy_mode_t;

/** \brief PHY forced mode configuration */
typedef struct {
    vtss_port_speed_t speed; /**< Speed */
    BOOL              fdx;   /**< Full duplex */
} vtss_phy_forced_t;

/** \brief PHY auto negotiation advertisement */
typedef struct {
    BOOL speed_10m_hdx;    /**< 10Mbps, half duplex */
    BOOL speed_10m_fdx;    /**< 10Mbps, full duplex */
    BOOL speed_100m_hdx;   /**< 100Mbps, half duplex */
    BOOL speed_100m_fdx;   /**< 100Mbps, full duplex */
    BOOL speed_1g_fdx;     /**< 1000Mpbs, full duplex */
    BOOL speed_1g_hdx;     /**< 1000Mpbs, full duplex */
    BOOL symmetric_pause;  /**< Symmetric pause */
    BOOL asymmetric_pause; /**< Asymmetric pause */
    BOOL tx_remote_fault;  /**< Local Application fault indication for Link Partner */
    BOOL speed_2g5_fdx;    /**< 2500Mpbs, full duplex */
    BOOL speed_5g_fdx;     /**< 5GE, full duplex  */
    BOOL speed_10g_fdx;    /**< 10GE, full duplex  */
    BOOL no_restart_aneg;  /**< Do not restart aneg */
} vtss_phy_aneg_t;

/** \brief PHY fast link failure pin enable/disable */
typedef enum {
    VTSS_PHY_FAST_LINK_FAIL_ENABLE = 1,    /**< Enable fast link failure pin */
    VTSS_PHY_FAST_LINK_FAIL_DISABLE,       /**< Disble fast link failure pin */
} vtss_phy_fast_link_fail_t;

/** \brief PHY Sigdet pin polarity configuration */
typedef enum {
     VTSS_PHY_SIGDET_POLARITY_ACT_LOW = 1,   /**< Set Sigdet polarity Active low */
     VTSS_PHY_SIGDET_POLARITY_ACT_HIGH,      /**< Set Sigdet polarity Active High */
} vtss_phy_sigdet_polarity_t;

/** \brief PHY Unidirectional enable/disable */
typedef enum {
    VTSS_PHY_UNIDIRECTIONAL_DISABLE = 0,   /**< Disable Unidirectional (Default) */
    VTSS_PHY_UNIDIRECTIONAL_ENABLE,        /**< Enable Unidirectional */
} vtss_phy_unidirectional_t;

/** \brief PHY MEDIA SerDes PCS Remote Fault Indication, See Clause 37, Table 37-3 */
typedef enum {
    VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_NONE    = 0,    /**< MAC SerDes PCS Control, SGMII Input Preamble for 100BaseX - No Preamble Req'd */
    VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_ONE     = 1,    /**< MAC SerDes PCS Control, SGMII Input Preamble for 100BaseX - One-Byte Preamble Req'd */
    VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_TWO     = 2,    /**< MAC SerDes PCS Control, SGMII Input Preamble for 100BaseX - Two-Byte Preamble Req'd */
    VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_RSVD    = 3     /**< MAC SerDes PCS Control, SGMII Input Preamble for 100BaseX - Reserved */
} vtss_phy_mac_serd_pcs_sgmii_pre;

/** \brief PHY MAC SerDes PCS Control, Reg16E3 */
typedef struct {
    BOOL                             disable;            /**< MAC i/f disable: 1000BaseX MAC i/f disable when media link down  */
    BOOL                             restart;            /**< MAC i/f restart: 1000BaseX MAC i/f restart on media link change  */
    BOOL                             pd_enable;          /**< MAC i/f ANEG parallel detect enable             */
    BOOL                             aneg_restart;       /**< Restart MAC i/f ANEG */
    BOOL                             force_adv_ability;  /**< Force adv. ability from Reg18E3 */
    vtss_phy_mac_serd_pcs_sgmii_pre  sgmii_in_pre;       /**< SGMII Input Preamble for 100BaseFX */
    BOOL                             sgmii_out_pre;      /**< SGMII Output Preamble */
    BOOL                             serdes_aneg_ena;    /**< MAC SerDes ANEG Enable  */
    BOOL                             serdes_pol_inv_in;  /**< Invert SerDes Polarity at input of MAC */
    BOOL                             serdes_pol_inv_out; /**< Invert SerDes Polarity at output of MAC */
    BOOL                             fast_link_stat_ena; /**< Fast Link Fail Status Enable */
    BOOL                             inhibit_odd_start;  /**< Inhibit MAC Odd-Start delay */
} vtss_phy_mac_serd_pcs_cntl_t;

/** \brief PHY MEDIA SerDes PCS Remote Fault Indication, See Clause 37, Table 37-3 */
typedef enum {
    VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_NO_ERROR   = 0,    /**< Media SerDes PCS Control, Most Recent Clause 37 ANEG Exchg - Table 37-3 */
    VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_OFFLINE    = 1,    /**< Media SerDes PCS Control, Most Recent Clause 37 ANEG Exchg */
    VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_LINK_FAIL  = 2,    /**< Media SerDes PCS Control, Most Recent Clause 37 ANEG Exchg */
    VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_ANEG_ERROR = 3     /**< Media SerDes PCS Control, Most Recent Clause 37 ANEG Exchg */
} vtss_phy_media_rem_fault_t;

/** \brief PHY MEDIA SerDes PCS Control, Reg23E3 */
typedef struct {
    vtss_phy_media_rem_fault_t  remote_fault;    /**< Remote Fault to Media indication sent in most recent Clause 37 ANEG  */
    BOOL   aneg_pd_detect;                       /**< SerDes MEDIA ANEG parallel detect enable             */
    BOOL   force_adv_ability;                    /**< Force adv. ability from Reg25E3 */
    BOOL   serdes_pol_inv_in;                    /**< Invert SerDes Polarity at input of Media SerDes */
    BOOL   serdes_pol_inv_out;                   /**< Invert SerDes Polarity at output of Media SerDes */
    BOOL   inhibit_odd_start;                    /**< Inhibit Media Odd-Start delay */
    BOOL   force_hls;                            /**< Forces 100BaseFX to Tx HSL continuously  */
    BOOL   force_fefi;                           /**< Forces 100BaseFX Far-End-Fault Indication */
    BOOL   force_fefi_value;                     /**< Forces/Suppress FEFI */
} vtss_phy_media_serd_pcs_cntl_t;

/** \brief PHY AMS Force configuration */
typedef enum {
    VTSS_PHY_MEDIA_FORCE_AMS_SEL_NORMAL   = 0,    /**< Force AMS Override to Force Selection - Normal */
    VTSS_PHY_MEDIA_FORCE_AMS_SEL_SERDES   = 1,    /**< Force AMS Override to Force Selection - SerDes Media */
    VTSS_PHY_MEDIA_FORCE_AMS_SEL_COPPER   = 2     /**< Force AMS Override to Force Selection - Copper Media */
} vtss_phy_media_force_ams_sel_t;


/** \brief PHY configuration */
typedef struct {
    vtss_phy_mode_t                 mode;         /**< PHY mode */
    vtss_phy_forced_t               forced;       /**< Forced mode configuration */
    vtss_phy_aneg_t                 aneg;         /**< Auto-negotiation mode configuration */
    vtss_phy_mdi_t                  mdi;          /**< Cu cable MDI (Crossed cable / normal cable) */
    vtss_phy_fast_link_fail_t       flf;          /**< Fast link failure configuration */
    vtss_phy_sigdet_polarity_t      sigdet;       /**< Sigdet pin polarity configuration */
    vtss_phy_unidirectional_t       unidir;       /**< Unidirectional Configuration */
    vtss_phy_mac_serd_pcs_cntl_t    mac_if_pcs;   /**< PHY MAC SerDes PCS Control (Reg16E3) */
    vtss_phy_media_serd_pcs_cntl_t  media_if_pcs; /**< PHY MAC SerDes PCS Control (Reg23E3) */
    vtss_phy_media_force_ams_sel_t  force_ams_sel;/**< PHY Media AMS Force Selection*/
    BOOL                            skip_coma;    /**< PHY COMA Mode - Automatically apply COMA Config or SKIP */
} vtss_phy_conf_t;


/**
 * \brief Get chip temperature
 *
 * \param inst [IN]  Target instance reference
 * \param port_no [IN]  Port number (Any port within the chip can be used).
 * \param temp [OUT] Chip temperature
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_chip_temp_get(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               i16        *const temp);


/**
 * \brief Init. chip temperature
 *
 * \param inst [IN]       Target instance reference
 * \param port_no [IN]  Port number (Any port within the chip can be used).
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_chip_temp_init(const vtss_inst_t inst,
                                const vtss_port_no_t port_no);


/**
 * \brief Get PHY configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    PHY configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_conf_get(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          vtss_phy_conf_t      *const conf);

/**
 * \brief Set PHY configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     PHY configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_conf_set(const vtss_inst_t     inst,
                          const vtss_port_no_t  port_no,
                          const vtss_phy_conf_t *const conf);

/**
 * \brief Get PHY status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [OUT]  PHY status.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_status_get(const vtss_inst_t    inst,
                            const vtss_port_no_t port_no,
                            vtss_port_status_t   *const status);
/**
 * \brief Get Clause37 Link pArtner's ability
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [OUT]  PHY status.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_cl37_lp_abil_get(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  vtss_port_status_t   *const status);
/* - 1G configuration and status ----------------------------------- */

/**
 * \brief Get the PHY type/id.
 * The the Phy ID - can only be used after setting the operating mode
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param phy_id [OUT]  PHY Type/id.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_id_get(const vtss_inst_t   inst,
                        const vtss_port_no_t  port_no,
                        vtss_phy_type_t *phy_id);

/** \brief ring resiliency status */
typedef enum {
     VTSS_PHY_TIMING_DEFAULT_SLAVE,        /* Node is clocking slave at initial link-up */
     VTSS_PHY_TIMING_MASTER_AS_SLAVE,      /* Timing master becoming slave */
     VTSS_PHY_TIMING_SLAVE_AS_MASTER,      /* Timing slave becoming master */
     VTSS_PHY_TIMING_DEFAULT_MASTER,       /* reflects autoneg master at initial link-up */
     VTSS_PHY_TIMING_LP_NOT_RESILIENT_CAP, /* LP is not ring resilient capable */
} vtss_phy_ring_resiliency_status_t;

#define TIMING_DEFAULT_SLAVE        VTSS_PHY_TIMING_DEFAULT_SLAVE        /**< Backward compatibility */
#define TIMING_MASTER_AS_SLAVE      VTSS_PHY_TIMING_MASTER_AS_SLAVE      /**< Backward compatibility */
#define TIMING_SLAVE_AS_MASTER      VTSS_PHY_TIMING_SLAVE_AS_MASTER      /**< Backward compatibility */
#define TIMING_DEFAULT_MASTER       VTSS_PHY_TIMING_DEFAULT_MASTER       /**< Backward compatibility */
#define TIMING_LP_NOT_RESILIENT_CAP VTSS_PHY_TIMING_LP_NOT_RESILIENT_CAP /**< Backward compatibility */

/** \brief ring resiliency configuration */
typedef struct {
    BOOL                                 enable_rrslnt;    /**<  enable or disable ring resiliency */
    vtss_phy_ring_resiliency_status_t    ring_res_status;  /**< ring resilency status for node */
} vtss_phy_ring_resiliency_conf_t;

/**
 * \brief Set PHY ring resiliency configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param ring_rslnt_conf [IN]     ring resiliency configuration.
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ring_resiliency_conf_set(const vtss_inst_t    inst,
                                      const vtss_port_no_t port_no,
                                      const vtss_phy_ring_resiliency_conf_t *const ring_rslnt_conf);
/**
 * \brief Get PHY ring resiliency configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param ring_rslnt_conf [OUT]     ring resiliency configuration.
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ring_resiliency_conf_get(const vtss_inst_t    inst,
                                      const vtss_port_no_t port_no,
                                      vtss_phy_ring_resiliency_conf_t *const ring_rslnt_conf);


/** \brief PHY 1G configuration */
typedef struct {
    struct {
        BOOL cfg;                               /**< Manual Master/Slave Config. 1=enabled */
        BOOL val;                               /**< Master/Slave Config value, 1=Master */
    } master;                             /**< Master/Slave Mode */
} vtss_phy_conf_1g_t;

/**
 * \brief Get PHY 1G configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    PHY 1G configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_conf_1g_get(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             vtss_phy_conf_1g_t    *const conf);

/**
 * \brief Set PHY 1G configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     PHY 1G configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_conf_1g_set(const vtss_inst_t         inst,
                             const vtss_port_no_t      port_no,
                             const vtss_phy_conf_1g_t  *const conf);

/** \brief PHY 1G status */
typedef struct {
    BOOL master_cfg_fault;  /**< Master/Slave Configuration fault */
    BOOL master;                   /**< Master = 1, Slave = 0 */
} vtss_phy_status_1g_t;

/**
 * \brief Get PHY 1G status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [OUT]  PHY 1G status.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_status_1g_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_phy_status_1g_t  *const status);

/* - Power configuration and status -------------------------------- */

#define VTSS_PHY_POWER_ACTIPHY_BIT 0 /**< Defines the bit used to signaling that ActiPhy is enabled */
#define VTSS_PHY_POWER_DYNAMIC_BIT 1 /**< Defines the bit used to signaling that PerfectReach is enabled */

/** \brief PHY power configuration */
typedef struct {
    vtss_phy_power_mode_t mode; /**< Power mode */
} vtss_phy_power_conf_t;

/**
 * \brief Get PHY power configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    PHY power configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_power_conf_get(const vtss_inst_t      inst,
                                const vtss_port_no_t   port_no,
                                vtss_phy_power_conf_t  *const conf);

/**
 * \brief Set PHY power configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     PHY power configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_power_conf_set(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_phy_power_conf_t  *const conf);

#define VTSS_PHY_ACTIPHY_PWR        100 /**< ActiPHY power status */
#define VTSS_PHY_LINK_DOWN_PWR      200 /**< Link down power status */
#define VTSS_PHY_LINK_UP_FULL_PWR   400 /**< Link up full power status */

/** \brief PHY power status */
typedef struct {
    u32 level;  /**< Usage level */
} vtss_phy_power_status_t;

/**
 * \brief Get PHY power status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [OUT]  PHY power configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_power_status_get(const vtss_inst_t        inst,
                                  const vtss_port_no_t     port_no,
                                  vtss_phy_power_status_t  *const status);

/* - Clock configuration ---------- -------------------------------- */

/** \brief PHY active clock out */
#define VTSS_PHY_RECOV_CLK1     0    /**< RCVRD_CLK1 */
#define VTSS_PHY_RECOV_CLK2     1    /**< RCVRD_CLK2 */
#define VTSS_PHY_RECOV_CLK_NUM  2    /**< Number of recovered clocks */
typedef u16 vtss_phy_recov_clk_t;    /**< Container of recovered clock out identifier */

/** \brief PHY clock sources */
typedef enum {
    VTSS_PHY_CLK_DISABLED, /**< Recovered Clock Disable */
    VTSS_PHY_SERDES_MEDIA, /**< SerDes PHY */
    VTSS_PHY_COPPER_MEDIA, /**< Copper PHY */
    VTSS_PHY_TCLK_OUT,     /**< Transmitter TCLK */
    VTSS_PHY_LOCAL_XTAL    /**< Local XTAL */
} vtss_phy_clk_source_t;

/** \brief PHY clock frequencies */
typedef enum {
    VTSS_PHY_FREQ_25M,  /**< 25 MHz */
    VTSS_PHY_FREQ_125M, /**< 125 MHz */
    VTSS_PHY_FREQ_3125M /**< 31.25 MHz This is only valid on ATOM family - NOT Enzo*/
} vtss_phy_freq_t;

/** \brief PHY clock squelch levels */
typedef enum {
    VTSS_PHY_CLK_SQUELCH_MAX = 0, /**< Automatically squelch clock to low when the link is not up, is unstable, is up in a mode that does not support the generation of arecovered clock (1000BASE-T master or 10BASE-T), or is up in EEE mode (100BASE-TX or 1000BASE-T slave).*/

    VTSS_PHY_CLK_SQUELCH_MED = 1, /**< Same as VTSS_PHY_CLK_SQUELCH_MAX except that the clock is also generated in 1000BASE-T master and 10BASE-T link-up modes. This mode also generates a recovered clock output in EEE mode during reception of LP_IDLE.*/
    VTSS_PHY_CLK_SQUELCH_MIN = 2, /**< Squelch only when the link is not up*/
    VTSS_PHY_CLK_SQUELCH_NONE= 3, /**< Disable clock squelch.*/
} vtss_phy_clk_squelch;

/** \brief PHY clock configuration */
typedef struct {
    vtss_phy_clk_source_t src;     /**< Clock source */
    vtss_phy_freq_t       freq;    /**< Clock requency */
    vtss_phy_clk_squelch  squelch; /**< Clock squelsh level */
} vtss_phy_clock_conf_t;

/**
 * \brief Set PHY clock configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param port_no [IN]     Port number to become clock source.
 * \param clock_port [IN]  Set configuration for this clock port.
 * \param conf [IN]        PHY clock configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_clock_conf_set(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_phy_recov_clk_t   clock_port,
                                const vtss_phy_clock_conf_t  *const conf);


/**
 * \brief Get PHY clock configuration.
 *
 * \param inst [IN]            Target instance reference.
 * \param port_no [IN]         Port number of the first port at this PHY instance.
 * \param clock_port [IN]      Get configuration for this clock port.
 * \param conf [OUT]           PHY clock configuration.
 * \param clock_source [OUT]   Port number that is clock source for this clock_port.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_clock_conf_get(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_phy_recov_clk_t   clock_port,
                                vtss_phy_clock_conf_t        *const conf,
                                vtss_port_no_t               *const clock_source);


/* - I2C ---------------------------------------------------- */
/**
 * \brief I2C read
 *
 * \param inst [IN]            Target instance reference.
 * \param port_no [IN]         Port number.
 * \param i2c_mux [IN]         The i2c clock mux
 * \param i2c_reg_addr [IN]    The i2c register address to access.
 * \param i2c_device_addr [IN] The i2c address of the device to access
 * \param word_access [IN]    Set to TRUE if the register data width is 16bit. FALSE = 8 bits data width.
 * \param cnt [IN]             The number of registers to read. Note: The reg_addr is incremented by 1 for each of the read counts. If you want to read 16 bites registers (2 times 8 bits from the same register address), you need to do that by calling the vtss_phy_i2c_read twice, and not use the cnt (set cnt to 1).
 * \param value [OUT]          Pointer to where array which in going to contain the values read.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_i2c_read(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          const u8             i2c_mux,
                          const u8             i2c_reg_addr,
                          const u8             i2c_device_addr,
                          BOOL                 word_access,
                          u8                   cnt,
                          u8                   *const value);


/**
 *
 * \brief I2C writes
 * \param inst [IN]            Target instance reference.
 * \param port_no [IN]         Port number.
 * \param i2c_mux [IN]         The i2c clock mux
 * \param i2c_reg_addr [IN]    The i2c register address to access.
 * \param i2c_device_addr [IN] The i2c address of the device to access.
 * \param word_access [IN]    Set to TRUE if the register data width is 16bit. FALSE = 8 bits data width
 * \param cnt [IN]             The number of registers to write. Note: The reg_addr is incremented by 1 for each of the write counts. If you want to write 16 bites registers (2 times 8 bits to the same register address), you need to do that by calling the vtss_phy_i2c_write twice, and not use the cnt (set cnt to 1).
 * \param value [IN]           Pointer to where array containing the values to write.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_i2c_write(const vtss_inst_t    inst,
                           const vtss_port_no_t port_no,
                           const u8             i2c_mux,
                           const u8             i2c_reg_addr,
                           const u8             i2c_device_addr,
                           BOOL                 word_access,
                           u8                   cnt,
                           const u8            *value);


/**
 * \brief I2C clock frequency select
 *
 * \param dev  [IN]            Driver instance.
 * \param clk_value [IN]       Pointer to where clock frequency values to write.
 *
 * \return Return code.
**/
vtss_rc vtss_phy_i2c_clock_select(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  const mepa_i2c_clk_select_t *clk_value);


/* - Read/write ---------------------------------------------------- */

/* PHY register pages */
#define VTSS_PHY_PAGE_STANDARD   0x0000 /**< Standard registers */
#define VTSS_PHY_PAGE_EXTENDED   0x0001 /**< Extended registers */
#define VTSS_PHY_PAGE_EXTENDED_2 0x0002 /**< Extended registers - page 2 */
#define VTSS_PHY_PAGE_EXTENDED_3 0x0003 /**< Extended registers - page 3 */
#define VTSS_PHY_PAGE_EXTENDED_4 0x0004 /**< Extended registers - page 4 */
#define VTSS_PHY_PAGE_GPIO       0x0010 /**< GPIO registers */
#define VTSS_PHY_PAGE_1588       0x1588 /**< 1588 (PTP) registers */
#define VTSS_PHY_PAGE_MACSEC     0x0004 /**< MACSEC page */
#define VTSS_PHY_PAGE_TEST       0x2A30 /**< Test registers */
#define VTSS_PHY_PAGE_TR         0x52B5 /**< Token ring registers */
#define VTSS_PHY_PAGE_0x2DAF     0x2DAF /**< 0x2DAF registers */
/* PHY register page access for a single register can be done
   using an OR operation of the register address and the page below */
#define VTSS_PHY_REG_STANDARD (VTSS_PHY_PAGE_STANDARD<<5) /**< Standard registers */
#define VTSS_PHY_REG_EXTENDED (VTSS_PHY_PAGE_EXTENDED<<5) /**< Extended registers */
#define VTSS_PHY_REG_GPIO     (VTSS_PHY_PAGE_GPIO<<5)     /**< GPIO registers */
#define VTSS_PHY_REG_TEST     (VTSS_PHY_PAGE_TEST<<5)     /**< Test registers */
#define VTSS_PHY_REG_TR       (VTSS_PHY_PAGE_TR<<5)       /**< Token ring registers */

/**
 * \brief Read value from PHY register.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param addr [IN]     Register address. The page number is encoded in the 16 MSB.
 * \param value [OUT]   Register value.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_read(const vtss_inst_t    inst,
                      const vtss_port_no_t port_no,
                      const u32            addr,
                      u16                  *const value);


/**
 * \brief Read value from PHY register at a specific page. Page register is set to standard page when read is done.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param page [IN]     Page - Page do to the read at.
 * \param addr [IN]     Register address. The page number is encoded in the 16 MSB.
 * \param value [OUT]   Register value.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_read_page(const vtss_inst_t    inst,
                           const vtss_port_no_t port_no,
                           const u32            page,
                           const u32            addr,
                           u16                  *const value);



/**
 * \brief Read value from PHY mmd register.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param devad [IN]    Devad register address.
 * \param addr [IN]     Register address.
 * \param value [OUT]   Register value.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_mmd_read(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          const u16            devad,
                          const u32            addr,
                          u16                  *const value);

/**
 * \brief Write value to PHY mmd register.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param devad [IN]    Devad register address.
 * \param addr [IN]     Register address.
 * \param value [OUT]   Register value.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_mmd_write(const vtss_inst_t    inst,
                           const vtss_port_no_t port_no,
                           const u16            devad,
                           const u32            addr,
                           u16                  value);

/**
 * \brief Write value to PHY register.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param addr [IN]     Register address. The page number is encoded in the 16 MSB.
 * \param value [IN]    Register value.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_write(const vtss_inst_t    inst,
                       const vtss_port_no_t port_no,
                       const u32            addr,
                       const u16            value);

/**
 * \brief Write masked value to PHY register.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param addr [IN]     Register address. The page number is encoded in the 16 MSB.
 * \param value [IN]    Register value.
 * \param mask [IN]     Register mask.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_write_masked(const vtss_inst_t    inst,
                              const vtss_port_no_t port_no,
                              const u32            addr,
                              const u16            value,
                              const u16            mask);


/**
 * \brief Write masked value to PHY register and setups the page register.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param page [IN]     Page number.
 * \param addr [IN]     Register address. The page number is encoded in the 16 MSB.
 * \param value [IN]    Register value.
 * \param mask [IN]     Register mask.
 *
 * \return Return code.
 **/

/* Write PHY register, masked (including page setup) */
vtss_rc vtss_phy_write_masked_page(const vtss_inst_t    inst,
                                   const vtss_port_no_t port_no,
                                   const u16            page,
                                   const u16            addr,
                                   const u16            value,
                                   const u16            mask);
/* - GPIO control -------------------------------------------------- */
/**
 * \brief GPIO pin operating mode
 **/
typedef enum
{
    VTSS_PHY_GPIO_ALT_0 = 0,  /**< Set GPIO to as alternate function - e.g. SCL, SIGDET, 1588_SPI_CS or 1588_SPI_DO. Matches the alternate function "00" in the data-sheet  */
    VTSS_PHY_GPIO_ALT_1 = 1,  /**< Set GPIO to as alternate function 1 - Matches the alternate function "01" in the data-sheet  */
    VTSS_PHY_GPIO_ALT_2 = 2,  /**< Set GPIO to as alternate function 2 - Matches the alternate function "10" in the data-sheet  */
    VTSS_PHY_GPIO_OUT   = 3,  /**< Set GPIO pin as output */
    VTSS_PHY_GPIO_IN    = 4,  /**< Set GPIO pin as input */

} vtss_phy_gpio_mode_t;

/**
 * \brief Configure GPIO mode
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Any port number within the chip containing the GPIO -
 * \param gpio_no [IN]  The GPIO number.
 * \param mode    [IN]  The mode the GPIO pin should operate in.
 *
 * \return VTSS_RC_OK when configuration was done correctly else error code.
 **/
vtss_rc vtss_phy_gpio_mode(const vtss_inst_t          inst,
                           const vtss_port_no_t       port_no,
                           const u8                   gpio_no,
                           const vtss_phy_gpio_mode_t mode);

/**
 * \brief Get the value from a GPIO pin
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Any port number within the chip containing the GPIO.
 * \param gpio_no [IN]  The GPIO number.
 * \param value   [OUT] Pointer to where to put the pin value (TRUE = pin input high, FALSE = pin input low)
 *
 * \return VTSS_RC_OK if value is valid else error code.
 **/
vtss_rc vtss_phy_gpio_get(const vtss_inst_t          inst,
                          const vtss_port_no_t       port_no,
                          const u8                   gpio_no,
                          BOOL                       *value);

/**
 * \brief Set the value of a GPIO pin
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Any port number within the chip containing the GPIO.
 * \param gpio_no [IN]  The GPIO number.
 * \param value   [IN]  The pin value. (TRUE = set pin high, FALSE = set pin low)
 *
 * \return VTSS_RC_OK when setting was done correctly else error code.
 **/
vtss_rc vtss_phy_gpio_set(const vtss_inst_t          inst,
                          const vtss_port_no_t       port_no,
                          const u8                   gpio_no,
                          BOOL                       value);

/**
 * \brief Enable/Disable Isolate Mode
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Any port number within the chip containing the GPIO.
 * \param iso_en   [IN]  Enable/Disable Isolate Mode
 *
 * \return VTSS_RC_OK when setting was done correctly else error code.
 **/

vtss_rc vtss_phy_isolate_mode_conf(const vtss_inst_t          inst,
                          const vtss_port_no_t      port_no,
                          const BOOL                iso_en);


/* - VeriPHY ------------------------------------------------------- */

/**
 * \brief Start VeriPHY.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param mode [IN]     VeriPHY mode.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_veriphy_start(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               const u8              mode);

/** \brief VeriPHY result */
typedef struct {
    BOOL                      link;      /**< Link status */
    vtss_phy_veriphy_status_t status[4]; /**< Status, pair A-D (0-3) */
    u8                        length[4]; /**< Length (meters), pair A-D (0-3) */
} vtss_phy_veriphy_result_t;

/**
 * \brief Get VeriPHY result.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param result [OUT   VeriPHY result.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_veriphy_get(const vtss_inst_t          inst,
                             const vtss_port_no_t       port_no,
                             vtss_phy_veriphy_result_t  *const result);


/** \brief EEE mode */
typedef enum {
    VTSS_EEE_DISABLE,  /* Update EEE state to disabled */
    VTSS_EEE_ENABLE,   /* Update EEE state to enabled */
    VTSS_EEE_REG_UPDATE, /* Update EEE register with current state */
} vtss_eee_mode_t;

#define EEE_DISABLE    VTSS_EEE_DISABLE    /**< Backward compatibility */
#define EEE_ENABLE     VTSS_EEE_ENABLE     /**< Backward compatibility */
#define EEE_REG_UPDATE VTSS_EEE_REG_UPDATE /**< Backward compatibility */

/** \brief EEE configuration */
typedef struct {
    vtss_eee_mode_t        eee_mode;   /**< EEE mode.  */
    BOOL                   eee_ena_phy; /**< Signaling current state in the phy api */
} vtss_phy_eee_conf_t;


/**
 * \brief Setting the LEDs blink mode
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number the port in question.
 * \param led_mode_select [IN] The LEDs mode
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_led_mode_set(const vtss_inst_t            inst,
                              const vtss_port_no_t         port_no,
                              const vtss_phy_led_mode_select_t led_mode_select);

/** \brief PHY led intensity */
typedef u8  vtss_phy_led_intensity;   /**< LED intensity from 0-200, LED intensity led_intensity * 0.5 */

/** \brief enhanced LED control */
typedef struct {
    BOOL ser_led_output_1;   /**<Set to TRUE if hardware board uses serial LEDs at PHY0, PHY1, PHY2 and PHY3 LED0 pins. */
    BOOL ser_led_output_2;   /**<Set to TRUE if hardware board uses serial LEDs at PHY0, PHY1, PHY2 and PHY3 LED1 pins. */
    u8   ser_led_frame_rate; /**<Serial LED frame rate.  0x0 = 2500Hz, 0x1 = 1000 Hz, 0x2 = 500 Hz, 0x3 = 250 Hz, 0x4 = 200 Hz, 0x5 = 125 Hz, 0x6 = 40 Hz  */
    u8   ser_led_select;     /**<The number of LEDs the hardware board supports for each PHY,  0x00 = 4 LEDs, 0x01 = 3 LEDs, 0x2 = 2 LEDs, 0x3 = 1 LED*/
} vtss_phy_enhanced_led_control_t;


/**
 * \brief Setting the LEDs  intensity
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number - Don't care for time being (Just set to a valid port), since all LEDs intensities are set to the same.
 * \param intensity [IN] The LEDs intensities in % (0-100)
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_led_intensity_set(const vtss_inst_t            inst,
                                   const vtss_port_no_t         port_no,
                                   const vtss_phy_led_intensity intensity);




/**
 * \brief Getting the LEDs intensity
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number - Don't care for time being (Just set to a valid port), since all LEDs intensities are set to the same.
 * \param intensity [IN] The LEDs intensities in % (0-100)
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_led_intensity_get(const vtss_inst_t            inst,
                                   const vtss_port_no_t         port_no,
                                   vtss_phy_led_intensity       *intensity);




/**
 * \brief Setting the enhanced LED control initial state (Should only be set once at startup)..
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Enhanced LED control configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_enhanced_led_control_init(const vtss_inst_t            inst,
                                           const vtss_port_no_t         port_no,
                                           const vtss_phy_enhanced_led_control_t conf);



/**
 * \brief Getting the enhanced LED control initial state (Should only be set once at startup)..
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Enhanced LED control configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_enhanced_led_control_init_get(const vtss_inst_t            inst,
                                               const vtss_port_no_t         port_no,
                                               vtss_phy_enhanced_led_control_t *conf);



/**
 * \brief Pulling the coma mode pin low
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number (Any port number for the PHY which shall pull the coma mode pin low).
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_coma_mode_disable(const vtss_inst_t            inst,
                                   const vtss_port_no_t         port_no);


/**
 * \brief Pulling the coma mode pin high (Set in coma mode if no external hardware is controlling the pin)
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number (Any port number for the PHY which shall pull the coma mode pin low. remember to use same port number as when calling vtss_phy_coma_mode_disable).
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_coma_mode_enable(const vtss_inst_t            inst,
                                  const vtss_port_no_t         port_no);



/** \brief debug function for Atom family Rev. A. chips */
void vga_adc_debug(const vtss_inst_t inst, u8 vga_adc_pwr, vtss_port_no_t port_no);


/**
 * \brief Get information about if a port is EEE capable
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number
 * \param eee_capable [OUT]  True if port is EEE capable else FALSE
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_port_eee_capable(const vtss_inst_t           inst,
                                  const vtss_port_no_t        port_no,
                                  BOOL                        *eee_capable);

/**
 * \brief Enabling / Disabling EEE (Energy Efficient Ethernet)
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param enable [IN]   Enable EEE
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_eee_ena(const vtss_inst_t           inst,
                         const vtss_port_no_t        port_no,
                         const BOOL                  enable);


/**
 * \brief Getting the current EEE (Energy Efficient Ethernet) configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]     EEE configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_eee_conf_get(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              vtss_phy_eee_conf_t         *conf);


/**
 * \brief Setting the EEE (Energy Efficient Ethernet) configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    EEE configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_eee_conf_set(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              const vtss_phy_eee_conf_t   conf);




/**
 * \brief Getting the if phy is currently powered save mode due to EEE
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param rx_in_power_save_state [OUT]  TRUE is phy rx part is in power save mode
 * \param tx_in_power_save_state [OUT]  TRUE is phy tx part is in power save mode
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_eee_power_save_state_get(const vtss_inst_t           inst,
                                          const vtss_port_no_t        port_no,
                                          BOOL  *rx_in_power_save_state,
                                          BOOL  *tx_in_power_save_state);

/**
 * \brief Getting the EEE advertisement
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param advertisement [OUT]  Advertisement bit mask.
 *                             Bit 0 = Link partner advertises 100BASE-T capability.
 *                             Bit 1 = Link partner advertises 1000BASE-T capability.
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_eee_link_partner_advertisements_get(const vtss_inst_t      inst,
                                                const vtss_port_no_t        port_no,
                                                u8                          *advertisement);




/* - Events ------------------------------------------------------- */
/*  PHY interrupt events */
#define VTSS_PHY_LINK_LOS_EV                    (1 << 0) /**< PHY link interrupt */
#define VTSS_PHY_LINK_FFAIL_EV                  (1 << 1) /**< PHY fast failure interrupt */
#define VTSS_PHY_LINK_AMS_EV                    (1 << 2) /**< PHY Automatic Media Sense */
#define VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV     (1 << 3) /**< PHY link state change event*/
#define VTSS_PHY_LINK_FDX_STATE_CHANGE_EV       (1 << 4) /**< PHY FDX state change event*/
#define VTSS_PHY_LINK_AUTO_NEG_ERROR_EV         (1 << 5) /**< PHY Autonegotiation error event*/
#define VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV      (1 << 6) /**< PHY Autonegotiation complete event*/
#define VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV  (1 << 7) /**< PHY Inline powered device detect event */
#define VTSS_PHY_LINK_SYMBOL_ERR_INT_EV         (1 << 8) /**< PHY Symbol error event */
#define VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV   (1 << 9) /**< PHY TX fifo over/underflow detect event*/
#define VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV   (1 << 10) /**< PHY RX fifo over/underflow detect event*/
#define VTSS_PHY_LINK_FALSE_CARRIER_INT_EV      (1 << 11) /**< PHY false-carrier interrupt event*/
#define VTSS_PHY_LINK_LINK_SPEED_DS_DETECT_EV   (1 << 12) /**< PHY Link speed downshift detect event*/
#define VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV   (1 << 13) /**< PHY master/salve resolution error event*/
#define VTSS_PHY_LINK_RX_ER_INT_EV              (1 << 14) /**< PHY RX_ER interrupt event*/
#define VTSS_PHY_LINK_EXTENDED_REG_INT_EV       (1 << 15) /**< PHY Use Extended Reg to Access interrupt event*/
#define VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV        (1 << 16) /**< PHY Wake-On-LAN interrupt event*/
/* - Extended Events Defn ------------------------------------------------------- */
#define VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV       (1 << 17) /**< PHY EEE Wake Error interrupt event*/
#define VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV        (1 << 18) /**< PHY EEE Wait Quit/Rx TS Timer interrupt event*/
#define VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV     (1 << 19) /**< PHY EEE Rx TQ Timer interrupt event*/
#define VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV       (1 << 20) /**< PHY EEE Link Fail interrupt event*/
#define VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV        (1 << 21) /**< PHY Ring Resiliancy Switchover complete interrupt event*/
#define VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV    (1 << 22) /**< PHY MACSEC Host MAC interrupt event*/
#define VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV    (1 << 23) /**< PHY MACSEC Line MAC interrupt event*/
#define VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV     (1 << 24) /**< PHY MACSEC Flow Control Buff interrupt event*/
#define VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV     (1 << 25) /**< PHY MACSEC Ingress interrupt event*/
#define VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV      (1 << 26) /**< PHY MACSEC Egress interrupt event*/
#define VTSS_PHY_LINK_EXT_MEM_INT_RING_EV       (1 << 27) /**< PHY MEM Integrity Ring Control interrupt event*/

/** \brief PHY interrupt event type */
typedef  u32 vtss_phy_event_t;

/**
 * \brief Enabling / Disabling of events
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ev_mask [IN]  Mask containing events that are enabled/disabled
 * \param enable [IN]   Enable/disable of event
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_event_enable_set(const vtss_inst_t         inst,
                                  const vtss_port_no_t      port_no,
                                  const vtss_phy_event_t    ev_mask,
                                  const BOOL                enable);



/**
 * \brief Getting current interrupt event state
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ev_mask [IN]  Mask containing events that are enabled/disabled
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_event_enable_get(const vtss_inst_t         inst,
                                  const vtss_port_no_t      port_no,
                                  vtss_phy_event_t          *ev_mask);



/**
 * \brief Polling for active events
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ev_mask [OUT] Mask containing events that are active
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_event_poll(const vtss_inst_t     inst,
                            const vtss_port_no_t  port_no,
                            vtss_phy_event_t      *const ev_mask);



/* - Misc--- */

/**
 * \brief Function for enabling/disabling squelch work around.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Any phy port with the chip
 * \param enable  [IN]  TRUE = enable squelch workaround, FALSE = Disable squelch workaround
 *
 * \return VTSS_RC_OK - Workaround was enabled/disable. VTSS_RC_ERROR - Squelch workaround patch not loaded
 **/
vtss_rc vtss_squelch_workaround(const vtss_inst_t         inst,
                                const vtss_port_no_t      port_no,
                                const BOOL enable);


/**
 * \brief Function for writing to CSR registers
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] The port in question
 * \param page         [IN] The page for the CSR register access e.g. VTSS_PHY_PAGE_1588 or VTSS_PHY_PAGE_MACSEC
 * \param target       [IN] The CSR target
 * \param csr_reg_addr [IN] The CSR register to write
 * \param value        [IN] The value to write
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/
vtss_rc vtss_phy_csr_wr(const vtss_inst_t    inst,
                        const u16            page,
                        const vtss_port_no_t port_no,
                        const u16            target,
                        const u32            csr_reg_addr,
                        const u32            value);

/**
 * \brief Function for writing to CSR registers
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] Any phy port with the chip
 * \param page         [IN] The page for the CSR register access e.g. VTSS_PHY_PAGE_1588 or VTSS_PHY_PAGE_MACSEC
 * \param target       [IN] The CSR target
 * \param csr_reg_addr [IN] The CSR register to read.
 * \param value        [IN] The value read
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/
vtss_rc vtss_phy_csr_rd(const vtss_inst_t    inst,
                        const u16            page,
                        const vtss_port_no_t port_no,
                        const u16            target,
                        const u32            csr_reg_addr,
                        u32                  *value);

/* - Debug--- */
/** \brief Phy statistic information */
typedef struct
{
    u8             cu_good;    /**< Cu media CRC good packet received since last time read */
    u8             cu_bad;    /**< RC error counter for packets received on the Cu media interface. The value saturates at 0xFF and subsequently clears when read and restarts count.*/
    u16            serdes_tx_good; /**< SerDes Transmit good packet count modulo 10000*/
    u8             serdes_tx_bad;  /**< SerDes Transmit CRC packet count (saturates at 255)*/
    u8             rx_err_cnt_base_tx; /**< 100/1000BASE-TX receive error counter. 8-bit counter that saturates when it reaches
                                          255. These bits are self-clearing when read. */
    u16            media_mac_serdes_good;/**<Counter containing the number of packets with valid CRCs. This counter does not saturate and will roll over to 0 when the count reaches 10,000 packets. */
    u8             media_mac_serdes_crc; /**<CRC error counter for packets received on the Fiber media or MAC interfaces. The value saturates at 0xFF and subsequently clears when read and restarts count.*/
} vtss_phy_statistic_t;

/**
 * \brief debug function for getting phy statistics.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Any phy port with the chip
 * \param statistics  [OUT]  Pointer to where to put the statistics.
 *
 * \return VTSS_RC_OK - Statistics is valid else statistics is invalid
 **/

vtss_rc vtss_phy_statistic_get(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               vtss_phy_statistic_t *statistics);



/** \brief Internal loop-back type */
typedef enum {
    VTSS_LB_1G_NONE,             /**< No looback   */
    VTSS_LB_FAR_END,             /**< Loopback at far end (Loopback at cu side)  - Only valid when Enable = TRUE */
    VTSS_LB_NEAR_END,            /**< Loopback at near end (Loopback at MAC side) - Only valid when Enable = TRUE  */
} lb_type;

/** \brief 1G Phy loopbacks */
typedef struct {
    BOOL far_end_enable;                     /**< Enable/Disable loopback far end loopback  */
    BOOL near_end_enable;                    /**< Enable/Disable loopback near end loopback  */
    BOOL connector_enable;                   /**< Enable/Disable loopback connector loopback  */
    BOOL mac_serdes_input_enable;            /**< Enable/Disable loopback SerDes MAC Input loopback  */
    BOOL mac_serdes_facility_enable;         /**< Enable/Disable loopback SerDes MAC Facility loopback  */
    BOOL mac_serdes_equipment_enable;        /**< Enable/Disable loopback SerDes MAC Equipment loopback  */
    BOOL media_serdes_input_enable;          /**< Enable/Disable loopback SerDes MEDIA Input loopback  */
    BOOL media_serdes_facility_enable;       /**< Enable/Disable loopback SerDes MEDIA Facility loopback  */
    BOOL media_serdes_equipment_enable;      /**< Enable/Disable loopback SerDes MEDIA Equipment loopback  */
} vtss_phy_loopback_t;


/**
 * \brief Debug function for enabling check of page register for all phy register accesses
 *
 * \param inst [IN]     Target instance reference.
 * \param enable [IN]   TRUE to enable phy page register check. FALSE to disable
 *
 * \return Return code. VTSS_RC_OK if phy page check were set.
 **/
vtss_rc vtss_phy_do_page_chk_set(const vtss_inst_t    inst,
                                 const BOOL enable);


/**
 * \brief Debug function for getting if check of page register is enabled
 *
 * \param inst [IN]     Target instance reference.
 * \param enable [OUT]   TRUE if phy page register check is enabled else FALSE
 *
 * \return Return code. VTSS_RC_OK when enable is valid.
 **/
vtss_rc vtss_phy_do_page_chk_get(const vtss_inst_t    inst,
                                 BOOL *enable);


/**
 * \brief Debug function for setting phy internal loopback
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Phy port that should have the internal loopback
 * \param loopback [IN] Loopback type
 *
 * \return Return code. VTSS_RC_OK if firmware is loaded correctly else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_loopback_set(const vtss_inst_t    inst,
                              const vtss_port_no_t port_no,
                              vtss_phy_loopback_t  loopback);
/**
 * \brief Debug function for getting the current phy internal loopback
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Phy port that with the internal loopback
 * \param loopback [IN] Current loopback type
 *
 * \return Return code. VTSS_RC_OK if firmware is loaded correctly else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_loopback_get(const vtss_inst_t    inst,
                              const vtss_port_no_t port_no,
                              vtss_phy_loopback_t  *loopback);


/**
 * \brief Debug function for checking if the phy firmware is loaded correctly
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Must the first PHY port within the chip.
 * \param code_length [IN]   The length of the microcode patch
 * \param expected_crc [IN]  The expected CRC.
 *
 * \return Return code. VTSS_RC_OK if firmware is loaded correctly else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_is_8051_crc_ok(const vtss_inst_t    inst,
                                const vtss_port_no_t port_no,
                                u16                  code_length,
                                u16                  expected_crc);

/**
 * \brief Debug function for setting the ob post0 patch.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  PHY port within the chip.
 * \param value [IN]    The value to call the ob post0 patch with.
 *
 * \return Return code. VTSS_RC_OK if patch were updated correct else VTSS_RC_ERROR
 **/

vtss_rc vtss_phy_cfg_ob_post0(const vtss_inst_t       inst,
                              const vtss_port_no_t    port_no,
                              const u16               value);

/**
 * \brief Debug function for setting the ib cterm patch.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  PHY port within the chip.
 * \param ib_cterm_ena [IN]    The value of ib_cterm_ena to call the ib cterm patch with.
 * \param ib_eq_mode [IN]    The value of ib_eq_mode to call the ib cterm patch with.
 *
 * \return Return code. VTSS_RC_OK if patch were updated correct else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_cfg_ib_cterm(const vtss_inst_t       inst,
                              const vtss_port_no_t    port_no,
                              const u8                ib_cterm_ena,
                              const                   u8 ib_eq_mode);



/**
 * \brief Debug function for getting PHY setting set by the micro patches.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  PHY port within the chip.
 * \param mcb_bus [INOUT]  If set to 2 the returned data is for LCPLL/RComp else the mcb_bus is returning 0 if the data is for 1G, and returning 1 if the data is for 6G .
 * \param cfg_buf [IN]    Pointer to array where to put the current settings.
 * \param stat_buf [IN]   Pointer to array where to put the current status.
 *
 * \return Return code. VTSS_RC_OK if patch were updated correct else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_patch_setttings_get(const vtss_inst_t       inst,
                                     const vtss_port_no_t    port_no,
                                     u8                      *mcb_bus,
                                     u8                      *cfg_buf,
                                     u8                      *stat_buf);

/**
 * \brief Function for updating the status via the result from PHY registers
 * \param port_no [IN]    The port in question.
 * \param lp_auto_neg_advertisment_reg [IN] The value from the register containing the Link partners auto negotiation advertisement (Standard page 5)
 * \param lp_1000base_t_status_reg [IN] The value from the register containing the Link partners 1000BASE-T Status (Standard page 10)
 * \param mii_status_reg [IN] The value from the register containing mii status (Standard page 1)
 * \param phy_setup      [IN] The phy configuration setup
 * \param status [INOUT]  Pointer to where to put the result */

void vtss_phy_reg_decode_status(vtss_port_no_t port_no,
                                u16 lp_auto_neg_advertisment_reg,
                                u16 lp_1000base_t_status_reg, u16 mii_status_reg,
                                const vtss_phy_conf_t phy_setup,
                                vtss_port_status_t *const status);



/**
 * \brief Function for finding flow control status based upon configuration and PHY registers.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param lp_auto_neg_advertisment_reg [IN]    The value from the register containing the Link partners auto negotiation advertisement (Standard page 5)
 * \param phy_setup                    [IN]    The phy configuration setup
 * \param status                       [INOUT] Pointer to where to put the result * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_flowcontrol_decode_status(const vtss_inst_t       inst,
                                           const vtss_port_no_t port_no,
                                           u16 lp_auto_neg_advertisment_reg,
                                           const vtss_phy_conf_t phy_setup,
                                           vtss_port_status_t *const status);


/**
 * \brief debug function for printing PHY statistics
 * \param inst    [IN]   Target instance reference.
 * \param pr      [IN]   Function pointer to print function e.g. CPRINTF
 * \param port_no [IN]   Port in question
 * \param print_hdr [IN] Set to TRUE to print header and counters. Set FALSE to only print counters
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_debug_stat_print(const vtss_inst_t         inst,
                                  const vtss_debug_printf_t pr,
                                  const vtss_port_no_t      port_no,
                                  const BOOL                print_hdr);

/**
 * \brief Function for checking if any issue were seen during warm-start
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  The port in question.
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_warm_start_failed_get(const vtss_inst_t inst, const vtss_port_no_t port_no);


/**
 * \brief debug function for printing some of the internal PHY state/configurations
 * \param inst      [IN] Target instance reference.
 * \param pr        [IN] Function pointer to print function e.g. CPRINTF
 * \param port_no   [IN] Port in question
 * \param print_hdr [IN] Set to TRUE to print header and phy state info. Set FALSE to only print state info. Normally this is set to TRUE for the first port called, and FALSE for the rest in order to only get one (common) header
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_debug_phyinfo_print(const vtss_inst_t         inst,
                                     const vtss_debug_printf_t pr,
                                     const vtss_port_no_t      port_no,
                                     const BOOL                print_hdr);

/**
 * \brief debug function for printing some of the internal PHY state/configurations
 * \param inst      [IN] Target instance reference.
 * \param pr        [IN] Function pointer to print function e.g. CPRINTF
 * \param clear     [IN] Set to TRUE to clear the counters & Stickt bits if any
 * \param port_no   [IN] Port in question
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_debug_register_dump(const vtss_inst_t inst,
                                       const vtss_debug_printf_t pr,
                                       BOOL clear, const vtss_port_no_t port_no);
/**
 * \brief Function for making getting the API updated with base port number for all ports. MUST not be called unless all ports are detected.
 * \param inst      [IN] Target instance reference.
 * \return Return code. VTSS_RC_OK if all base ports were updated correctly else error code.*/
vtss_rc vtss_phy_detect_base_ports(const vtss_inst_t inst);


/**
 * \brief Function for configuring External Connector Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param lpback                       [IN]    TRUE=Loopback ON, FALSE=Loopback OFF
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_ext_connector_loopback(const vtss_inst_t    inst,
                                        const vtss_port_no_t port_no,
                                        const BOOL           lpback);

/**
 * \brief Function for configuring MAC-SerDes(SGMII) Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param mode                         [IN]    serdes mode and port
 *        mode: bits 15:12: 0x8= Fibre Media or 0x9=SGMII/QSGMII MAC
 *        mode: bits 11:8: Port Address (0-3)
 *        mode: bits 7:4: Loopback Type: 0=No,1=Pad,2=Input,4=Facility,8=Equipment
 *        mode: bits 3:0: 0x2
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_serdes_sgmii_loopback( const vtss_inst_t    inst,
                                        const vtss_port_no_t port_no,
                                        const u16            mode);

/**
 * \brief Function for configuring Fibre-Media SerDes Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param mode                         [IN]    serdes mode and port
 *        mode: bits 15:12: 0x8= Fibre Media or 0x9=SGMII/QSGMII MAC
 *        mode: bits 11:8: Port Address (0-3)
 *        mode: bits 7:4: Loopback Type: 0=No,1=Pad,2=Input,4=Facility,8=Equipment
 *        mode: bits 3:0: 0x2
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_serdes_fmedia_loopback( const vtss_inst_t    inst,
                                         const vtss_port_no_t port_no,
                                         const u16            mode);


/**
 * \brief debug function for printing some of the internal PHY Registers
 * \param inst      [IN] Target instance reference.
 * \param pr        [IN] Function pointer to print function e.g. CPRINTF
 * \param port_no   [IN] Port in question
 * \param page_no   [IN] Page No in question, 0, 1, 2, 3, 1588, MACSEC, TEST, TR
 * \param print_hdr [IN] Set to TRUE to print header and phy state info. Set FALSE to only print state info. Normally this is set to TRUE for the first port called, and FALSE for the rest in order to only get one (common) header
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_debug_regdump_print(const vtss_inst_t         inst,
                                     const vtss_debug_printf_t pr,
                                     const vtss_port_no_t      port_no,
                                     const vtss_port_no_t      page_no,
                                     const BOOL                print_hdr);



/****************************************************************************
 * WAKE-ON-LAN types
 ****************************************************************************/

#define MAX_WOL_MAC_ADDR_SIZE     6 /**< Defines the maximum size WOL MAC ADDR, ie. 6 Octets. */
#define MAX_WOL_PASSWD_SIZE       6 /**< Defines the maximum size WOL Secure_On Password, ie. 6 Octets. */
#define MIN_WOL_PASSWD_SIZE       4 /**< Defines the minimum size WOL Secure_On Password, ie. 4 Octets. */

/**
 * \brief Structure for Wake-On-LAN MAC Address
*/
typedef struct
{
    u8 addr[MAX_WOL_MAC_ADDR_SIZE];     /**< Wake-On-LAN MAC Address - 6 bytes */
} vtss_wol_mac_addr_t;

/**
 * \brief Structure for Wake-On-LAN Secure-On Password
*/
typedef struct
{
    u8 passwd[MAX_WOL_PASSWD_SIZE];     /**< Secure-On Password, Can be 4 or 6 bytes */
} vtss_secure_on_passwd_t;

/**
 * \brief Structure for Wake-On-LAN Password Length configuration
*/
typedef enum {
    VTSS_WOL_PASSWD_LEN_4 = 4,              /**< PasswdLen=4 bytes */
    VTSS_WOL_PASSWD_LEN_6 = 6,              /**< PasswdLen=6 bytes */
} vtss_wol_passwd_len_type_t;

/**
 * \brief Structure for Get/Set Wake-On-LAN configuration
*/
typedef struct {
    BOOL                        secure_on_enable;    /**< Enable/Disable for Secure-On Password          */
    vtss_wol_mac_addr_t         wol_mac;             /**< Wake-On-LAN MAC Addr Definition                */
    vtss_secure_on_passwd_t     wol_pass;            /**< Wake-On-LAN Password Definition                */
    vtss_wol_passwd_len_type_t  wol_passwd_len;      /**< Enumeration for Password Length options        */
    u16                         magic_pkt_cnt;       /**< Magic Packet Repetition Count (1-16 is valid)  */
} vtss_phy_wol_conf_t;

/**
 * \brief function to Enable or Disable WOL by enabling or disabling the interrupt
 * \param inst      [IN] Target instance reference.
 * \param port_no   [IN] Port in question
 * \param enable    [IN] Boolean, Enable=TRUE or 1, Disable=False or 0
 * \return Return code. VTSS_RC_OK if no errors.
*/
vtss_rc vtss_phy_wol_enable(const vtss_inst_t           inst,
                            const vtss_port_no_t        port_no,
                            const BOOL                  enable);

/**
 * \brief function to Get Wake-On-LAN configuration
 * \param inst      [IN] Target instance reference.
 * \param port_no   [IN] Port in question
 * \param conf      [IN] Ptr to WoL Structure vtss_phy_wol_conf_t to be filled out by API
 * \return Return code. VTSS_RC_OK if no errors.
*/
vtss_rc vtss_phy_wol_conf_get(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              vtss_phy_wol_conf_t   *const conf);

/**
 * \brief function to Set Wake-On-LAN configuration
 * \param inst      [IN] Target instance reference.
 * \param port_no   [IN] Port in question
 * \param conf      [IN] Ptr to WoL Structure vtss_phy_wol_conf_t filled out by User
 * \return Return code. VTSS_RC_OK if no errors.
*/
vtss_rc vtss_phy_wol_conf_set(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              const vtss_phy_wol_conf_t *const conf);


/**
 * \brief Debug function for getting PHY setting set by the micro patches.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  PHY port within the chip.
 * \param mcb_bus [INOUT]  If set to 2 the returned data is for LCPLL/RComp else the mcb_bus is returning 0 if the data is for 1G, and returning 1 if the data is for 6G .
 * \param cfg_buf [IN]    Pointer to array where to put the current settings.
 * \param stat_buf [IN]   Pointer to array where to put the current status.
 *
 * \return Return code. VTSS_RC_OK if patch were updated correct else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_patch_settings_get(const vtss_inst_t       inst,
                                    const vtss_port_no_t    port_no,
                                    u8                      *mcb_bus,
                                    u8                      *cfg_buf,
                                    u8                      *stat_buf);


/**
 * \brief Structure for Get PHY RC-PLL status
*/
typedef struct {
    u8 out_of_range;          /**< Out of range condition error */
    u8 cal_error;             /**< Calibration Error indication */
    u8 cal_not_done;          /**< Calibration not started or finished */
} vtss_rcpll_status_t;

/**
 * \brief Debug function for getting PHY Serdes6G RC-PLL status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  PHY port within the chip.
 * \param rcpll_status [OUT] Pointer to RC-PLL structure vtss_rcpll_status_t to get the status.
 *
 * \return Return code. VTSS_RC_OK if patch were updated correct else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_serdes6g_rcpll_status_get(const vtss_inst_t    inst,
                                           const vtss_port_no_t port_no,
                                           vtss_rcpll_status_t  *rcpll_status);
/**
 * \brief Debug function for getting PHY Serdes1G RC-PLL status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  PHY port within the chip.
 * \param rcpll_status [OUT] Pointer to RC-PLL structure vtss_rcpll_status_t to get the status.
 *
 * \return Return code. VTSS_RC_OK if patch were updated correct else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_serdes1g_rcpll_status_get(const vtss_inst_t    inst,
                                           const vtss_port_no_t port_no,
                                           vtss_rcpll_status_t  *rcpll_status);
/**
 * \brief Structure for Get PHY LC-PLL status
*/
typedef struct {
    u8 lock_status;        /**< PLL lock status */
    u8 cal_done;           /**< Calibration status */
    u8 cal_error;          /**< Calibration Error indication */
    u8 fsm_lock;           /**< FSM lock status */
    u8 fsm_stat;           /**< FSM internal status */
    u8 gain_stat;          /**< VCO frequency step stop */
} vtss_lcpll_status_t;

/**
 * \brief Debug function for getting PHY LC-PLL status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  PHY port within the chip.
 * \param lcpll_status [OUT] Pointer to LC-PLL structure vtss_lcpll_status_t to get the status.
 *
 * \return Return code. VTSS_RC_OK if patch were updated correct else VTSS_RC_ERROR
 **/
vtss_rc vtss_phy_lcpll_status_get(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  vtss_lcpll_status_t  *lcpll_status);


/**
 * \brief Debug function for Resetting the LCPLL for the PHY.
 * \note: This would occur PRIOR to calling PHY pre-reset(), reset(), and post-reset() functions, immediately after HW Reset
 *        At this point in the process, the PHY API does not know the PHY Base Port Number.
 *        If the Calling application uses the Base Port number, the LCPLL is reset and VTSS_RC_OK is returned
 *        If the Calling application uses any other port number, VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND is returned and no action is taken
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  PHY port within the chip.
 *
 * \return Return code. VTSS_RC_OK if LCPLL reset correctly
 *                      VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND if the port_no used was not the base_port_no of the PHY, ie. No action taken
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_reset_lcpll(const vtss_inst_t           inst,
                             const vtss_port_no_t        port_no);


/**
 * \brief Debug function for reading the 6G SerDes ob_post0 and ob_post1 values.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   PHY port within the chip.
 * \param ob_post0 [OUT]  ob_post0 settings in serdes6g_ob_cfg for 6G SerDes Macro (See TN1052), 6 bits, default:0, Customizeable.
 * \param ob_post1 [OUT]  ob_post1 settings in serdes6g_ob_cfg for 6G SerDes Macro (See TN1052), 5 bits, default:0, Do not change.
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_sd6g_ob_post_rd(vtss_inst_t             inst,
                                 const vtss_port_no_t    port_no,
                                 u8                     *ob_post0,
                                 u8                     *ob_post1);


/**
 * \brief Debug function for modifying the 6G SerDes ob_post0 and ob_post1 values.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   PHY port within the chip.
 * \param ob_post0 [IN]  Modify ob_post0 settings in serdes6g_ob_cfg for 6G SerDes Macro (See TN1052), 6 bits, default:0, Customizeable.
 * \param ob_post1 [IN]  Modify ob_post1 settings in serdes6g_ob_cfg for 6G SerDes Macro (See TN1052), 5 bits, default:0, Do not change.
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_sd6g_ob_post_wr(vtss_inst_t             inst,
                                 const vtss_port_no_t    port_no,
                                 const u8                ob_post0,
                                 const u8                ob_post1);

/**
 * \brief Debug function for reading the 6G SerDes ob_level value.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   PHY port within the chip.
 * \param ob_level [OUT]  ob_level settings in serdes6g_ob_cfg1 for 6G SerDes Macro (See TN1052), 6 bits, default:0x18, Customizeable Amplitude Control.
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_sd6g_ob_lev_rd(vtss_inst_t              inst,
                                const vtss_port_no_t     port_no,
                                u8                      *ob_level);


/**
 * \brief Debug function for modifying the 6G SerDes ob_lev value.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   PHY port within the chip.
 * \param ob_level [IN]  Modify ob_lev settings in serdes6g_ob_cfg1 for 6G SerDes Macro (See TN1052), 6 bits, default:0x18, Customizeable Amplitude Control.
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_sd6g_ob_lev_wr(vtss_inst_t              inst,
                                const vtss_port_no_t     port_no,
                                const u8                 ob_level);

/**
 * \brief Function to modify the values for the MAC and MEDIA I/F Inhibit ODD Start Delay.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   PHY port within the chip.
 * \param mac_inhibit [IN]  Modify Inhibit MAC Odd-start Delay settings, ie. Reg 16E3.2.
 * \param media_inhibit [IN]  Modify Inhibit MEDIA Odd-start Delay settings, ie. Reg 23E3.4.
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_mac_media_inhibit_odd_start(vtss_inst_t          inst,
                                             const vtss_port_no_t port_no,
                                             const BOOL           mac_inhibit,
                                             const BOOL           media_inhibit);


/**
 * \brief Far-End Failure Indication modes
 *  These settings map to PHY Reg23E3, bits 0 and 1
 **/
typedef enum {
    VTSS_100FX_FEFI_NORMAL = 0,            /**< Normal FEFI Operation, as specified by Reg23E3.1 */
    VTSS_100FX_FEFI_FORCE_SUPPRESS = 2,    /**< Force FEFI, as specifed by Reg23E3.0  */
    VTSS_100FX_FEFI_FORCE_ENABLE = 3,      /**< Force FEFI, as specifed by Reg23E3.0  */
} vtss_fefi_mode_t;

/**
 * \brief Function to modify the values for the Far-End Fail Indication.
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       PHY port within the chip.
 * \param fefi [OUT]         PHY port Far End Failure Indicator Config.
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_fefi_get(vtss_inst_t               inst,
                          const vtss_port_no_t      port_no,
                          vtss_fefi_mode_t         *fefi);

/**
 * \brief Function to modify the values for the Far-End Fail Indication.
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       PHY port within the chip.
 * \param fefi [IN]          PHY port Far End Failure Indicator Config.
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_fefi_set(vtss_inst_t               inst,
                          const vtss_port_no_t      port_no,
                          const vtss_fefi_mode_t    fefi);

/**
 * \brief Function to get the status for the Far-End Fail Indication.
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       PHY port within the chip.
 * \param fefi_detect [OUT]  PHY port Far End Failure Indicator
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_fefi_detect(vtss_inst_t               inst,
                             const vtss_port_no_t      port_no,
                             BOOL                     *fefi_detect);


/**
 * \brief Function to get the Mean Squared Error (MSE), ie. Noise floor for 100m.
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       PHY port within the chip.
 * \param mse [OUT]          PHY port MSE Value
 *      In order to convert the returned mse value to dB, do the following
 *      This computation would be required for each channel pair
 *      mse_dbl = mse / (1024 * 2048);     Note: Convert to Double and Scale by 2^21 = 1024 * 2048
 *      mse_dbl = 20 * log10(mse_dbl);     Note: Convert to dB
 *          Nominal Computed Values for mse_dbl are: -22dB to -31dB
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_mse_100m_get(vtss_inst_t              inst,
                              const vtss_port_no_t     port_no,
                              u32                     *mse);


/**
 * \brief Function to get the Mean Squared Error (MSE), ie. Noise floor for 1000m.
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       PHY port within the chip.
 * \param mseA [OUT]         PHY port MSE Chan A Value
 * \param mseB [OUT]         PHY port MSE Chan B Value
 * \param mseC [OUT]         PHY port MSE Chan C Value
 * \param mseD [OUT]         PHY port MSE Chan D Value
 *      In order to convert the returned mse value to dB, do the following
 *      This computation would be required for each channel pair
 *      mse_dbl = mse / (1024 * 2048);     Note: Convert to Double and Scale by 2^21 = 1024 * 2048
 *      mse_dbl = 20 * log10(mse_dbl);     Note: Convert to dB
 *          Nominal Computed Values for mse_dbl are: -22dB to -31dB
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_mse_1000m_get(vtss_inst_t              inst,
                               const vtss_port_no_t     port_no,
                               u32                     *mseA,
                               u32                     *mseB,
                               u32                     *mseC,
                               u32                     *mseD);

/**
 * \brief Function for Configuring MAC i/f 6G serdes (applicable only on VIPER,ELISE)
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] Any phy port with the chip
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/

vtss_rc vtss_phy_sd6g_mac_serdes_conf(const vtss_inst_t    inst,
                                      const vtss_port_no_t port_no);


#ifdef _ENABLE_PHY_SERDES_DEBUG_
/**
 * \brief Debug Function for reading MAC i/f 6G serdes (applicable only on VIPER,ELISE)
 * VIPER & ELISE FAMILY ONLY -- VSC8584/82 & VSC8514
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] Any phy port with the chip
 * \param csr_reg      [IN] The CSR register to read,
 * \param csr_reg_val  [IN] The value read
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/
vtss_rc vtss_phy_sd6g_csr_reg_rd_dbg(const vtss_inst_t         inst,
                                     const vtss_port_no_t      port_no,
                                     const u32                 csr_reg,
                                     u32                      *csr_reg_val);
#endif



/**
 * \brief Debug Function to retrieve the values from Token Ring
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       PHY port within the chip.
 * \param tr_addr [IN]       Token Ring ADDR (TR16) to Read
 * \param tr_lower [OUT]     Token Ring Lower 16bits of Value (TR17)
 * \param tr_upper [OUT]     Token Ring Upper 16bits of Value (TR18)
 *
 * \return Return code. VTSS_RC_OK if all Ok
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_read_tr_addr(vtss_inst_t              inst,
                              const vtss_port_no_t     port_no,
                              u16                      tr_addr,
                              u16                     *tr_lower,
                              u16                     *tr_upper);

/**
 * \brief Function for Configuring MAC i/f 6G serdes (applicable only on VIPER,ELISE)
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] Any phy port with the chip
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/

vtss_rc vtss_phy_sd6g_mac_serdes_conf(const vtss_inst_t    inst,
                                      const vtss_port_no_t port_no);


#ifdef _ENABLE_PHY_SERDES_DEBUG_
/**
 * \brief Debug Function for reading MAC i/f 6G serdes (applicable only on VIPER,ELISE)
 * VIPER & ELISE FAMILY ONLY -- VSC8584/82 & VSC8514
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] Any phy port with the chip
 * \param csr_reg      [IN] The CSR register to read,
 * \param csr_reg_val  [IN] The value read
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/
vtss_rc vtss_phy_sd6g_csr_reg_rd_dbg(const vtss_inst_t         inst,
                                     const vtss_port_no_t      port_no,
                                     const u32                 csr_reg,
                                     u32                      *csr_reg_val);
#endif



/**
 * \brief Polling for to determine if the Chip Type and revision is Viper Rev_B
 *
 * \param inst [IN]           Target instance reference.
 * \param port_no [IN]        Port number
 * \param is_viper_revB [OUT] Boolean to indicate that the Chip/Rev is Viper RevB
 *
 * \return Return code.
 *
 **/
vtss_rc vtss_phy_is_viper_revB(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               BOOL                  *is_viper_revB);

/**
 * \brief Polling for active EXT Interrupt events
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ev_mask [OUT] Mask containing events that are active
 *
 * \return Return code.
 *
 * NOTE: Viper Rev. B Self-Clearing Interrupt Stuck ON Work-Around
 *       Normally, the API function: vtss_phy_event_poll() handles ALL Interrupts.
 *       This API is a work-around for Viper family (VSC8584/VSC8582/VSC8575/VSC8564/VSC8562/VSC8586)
 *       Viper Rev_B has a Bug which prevents EXT INT (Reg26.5) and AMS INT (Reg26.4) from Clearing properly (MDINT stays asserted),
 *       This results in MDINT Stuck ON if one of these INT's are ever triggered, putting the system into a Stuck Interrupt situation
 *       This API can be used to directly Poll for the events in Extended Interrupt Status Reg. 29E2.
 **/
vtss_rc vtss_phy_ext_event_poll(const vtss_inst_t     inst,
                                const vtss_port_no_t  port_no,
                                vtss_phy_event_t      *const ev_mask);

#if defined(VTSS_FEATURE_MACSEC) && defined(KAT_TEST_ENABLE_1G)

/**
 * \brief EPG generated frame for Known Answer Test (KAT)
 * VIPER FAMILY, Rev. B and later ONLY -- VSC8584/82
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] Any phy port with the chip
 * \param bool         [IN] Generate Matching frame or non-matching frame for KAT
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/

vtss_rc vtss_phy_epg_gen_kat_frame( const vtss_inst_t        inst,
                                    const vtss_port_no_t     port_no,
                                    BOOL                     match);

#endif  /* VTSS_FEATURE_MACSEC && KAT_TEST_ENABLE_1G */



/**
 * \brief Get PHY status from the PHY Instance (Does not read PHY Registers).
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [OUT]  PHY status.
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_status_inst_poll(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  vtss_port_status_t   *const status);
/**
 * \brief Function for Reading from 6G serdes registers (applicable only on VIPER,ELISE)
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] Any phy port with the chip
 * \param target       [IN] The CSR target
 * \param csr_reg_addr [IN] The CSR register to read,
 * \param value        [OUT] The value read
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/
vtss_rc vtss_phy_macsec_csr_sd6g_rd(vtss_inst_t          inst,
                                    const vtss_port_no_t port_no,
                                    const u16            target,
                                    const u32            csr_reg_addr,
                                    u32                  *value);


/**
 * \brief Function for Writing to 6G serdes registers (applicable only on VIPER,ELISE)
 *
 * \param inst         [IN] Target instance reference.
 * \param port_no      [IN] Any phy port with the chip
 * \param target       [IN] The CSR target
 * \param csr_reg_addr [IN] The CSR register to read,
 * \param value        [IN] The value read
 *
 * \return VTSS_RC_OK when new access can be done - VTSS_RC_ERROR if something when wrong and access was never granted.
 **/
vtss_rc vtss_phy_macsec_csr_sd6g_wr(vtss_inst_t          inst,
                                    const vtss_port_no_t port_no,
                                    const u16            target,
                                    const u32            csr_reg_addr,
                                    u32                  value);



/**
 * \brief Execute PHY firmware update for certain PHYs, currently only for AQR PHYs
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param fw [IN]       Firmware.
 * \param len [IN]      Firmware length.
 *
 * \return Return code. VTSS_RC_OK if firmware update OK or skip firmware update.
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_firmware_update(const vtss_inst_t    inst,
                                 const vtss_port_no_t port_no,
                                 u8 *const fw,
                                 u32 *const len);

/**
 * \brief PHY SerDes to Retrieve PRBS Settings
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port number.
 * \param test_sel [OUT]  Test Mode (0=OFF, 1=BIST)
 * \param prbs [OUT]      PRBS Type (0=PRBS7)
 *
 * \return Return code. VTSS_RC_OK if PRBS Config OK.
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_serdes_prbs_conf_get(const vtss_inst_t     inst,
                                      const vtss_port_no_t  port_no,
                                      u8                   *test_sel,
                                      u8                   *prbs);

/**
 * \brief PHY SerDes Config to Enable/Disable PRBS7
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param prbs_ena [IN] PRBS7 Enable flag (TRUE=Enable, FALSE=Disable)
 *
 * \return Return code. VTSS_RC_OK if PRBS Config OK.
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_serdes_prbs_conf_set(const vtss_inst_t    inst,
                                      const vtss_port_no_t port_no,
                                      const BOOL           prbs_ena);


/**
 * \brief Configure/update PHY MAC i/f SerDes OB_CNTRL Config
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param ob_post0 [IN] SerDes Config Range 0-63
 * \param ob_post1 [IN] SerDes Config Range 0-31
 * \param ob_prec  [IN] SerDes Config Range 0-31
 *
 * \return Return code. VTSS_RC_OK if SerDes OB_CNTRL Config OK.
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_mac_serdes_ob_cntrl_set(const vtss_inst_t     inst,
                                         const vtss_port_no_t  port_no,
                                         const u8              ob_post0,
                                         const u8              ob_post1,
                                         const u8              ob_prec);


/**
 * \brief Retrieve PHY MEDIA i/f SerDes OB_CNTRL Config
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param ob_post0 [OUT] SerDes Config Range 0-63
 * \param ob_post1 [OUT] SerDes Config Range 0-31
 * \param ob_prec  [OUT] SerDes Config Range 0-31
 *
 * \return Return code. VTSS_RC_OK if SerDes OB_CNTRL Config OK.
 *                      VTSS_RC_ERROR if and error occurred.
 **/
vtss_rc vtss_phy_mac_serdes_ob_cntrl_get(const vtss_inst_t     inst,
                                         const vtss_port_no_t  port_no,
                                         u8                   *ob_post0,
                                         u8                   *ob_post1,
                                         u8                   *ob_prec);



#ifdef __cplusplus
}
#endif
#endif /* _VTSS_PHY_1G_API_H_ */
