// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_PHY_API_TYPES_H_
#define _MICROCHIP_ETHERNET_PHY_API_TYPES_H_

#include <microchip/ethernet/common.h>
#include <microchip/ethernet/switch/api/phy_1g.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

typedef mesa_aneg_t mepa_aneg_t;
typedef mesa_bool_t mepa_bool_t;
typedef mesa_chip_no_t mepa_chip_no_t;
typedef mesa_fiber_port_speed_t mepa_fiber_port_speed_t;
typedef mesa_phy_mdi_t mepa_mdi_t;
typedef mesa_phy_media_interface_t mepa_media_interface_t;
typedef mesa_port_interface_t mepa_port_interface_t;
typedef mesa_port_no_t mepa_port_no_t;
typedef mesa_port_speed_t mepa_port_speed_t;
typedef mesa_rc mepa_rc;
typedef mesa_sd10g_media_type_t mepa_sd10g_media_type_t;
typedef mesa_phy_power_mode_t mepa_power_mode_t;
typedef mesa_phy_status_1g_t mepa_aneg_status_t;
typedef mesa_phy_rgmii_conf_t mepa_rgmii_conf_t;
typedef mesa_phy_tbi_conf_t mepa_tbi_conf_t;
typedef mesa_phy_forced_reset_t mepa_forced_reset_t;
typedef mesa_phy_pkt_mode_t mepa_pkt_mode_t;
typedef mesa_phy_reset_conf_t mepa_reset_conf_t;
typedef mesa_phy_event_t mepa_event_t;
typedef mesa_phy_veriphy_status_t mepa_cable_diag_status_t;
typedef mesa_port_admin_state_t mepa_port_admin_state_t;
typedef mesa_phy_led_number_t mepa_led_number_t;

/** \brief Port speeds */
#define MEPA_SPEED_UNDEFINED MESA_SPEED_UNDEFINED
#define MEPA_SPEED_10M       MESA_SPEED_10M
#define MEPA_SPEED_100M      MESA_SPEED_100M
#define MEPA_SPEED_1G        MESA_SPEED_1G
#define MEPA_SPEED_AUTO      MESA_SPEED_AUTO

/** \brief Cable diagnostics status */
#define MEPA_CABLE_DIAG_STATUS_OK        MESA_VERIPHY_STATUS_OK
#define MEPA_CABLE_DIAG_STATUS_OPEN      MESA_VERIPHY_STATUS_OPEN
#define MEPA_CABLE_DIAG_STATUS_SHORT     MESA_VERIPHY_STATUS_SHORT
#define MEPA_CABLE_DIAG_STATUS_ABNORM    MESA_VERIPHY_STATUS_ABNORM
#define MEPA_CABLE_DIAG_STATUS_SHORT_A   MESA_VERIPHY_STATUS_SHORT_A
#define MEPA_CABLE_DIAG_STATUS_SHORT_B   MESA_VERIPHY_STATUS_SHORT_B
#define MEPA_CABLE_DIAG_STATUS_SHORT_C   MESA_VERIPHY_STATUS_SHORT_C
#define MEPA_CABLE_DIAG_STATUS_SHORT_D   MESA_VERIPHY_STATUS_SHORT_D
#define MEPA_CABLE_DIAG_STATUS_COUPL_A   MESA_VERIPHY_STATUS_COUPL_A
#define MEPA_CABLE_DIAG_STATUS_COUPL_B   MESA_VERIPHY_STATUS_COUPL_B
#define MEPA_CABLE_DIAG_STATUS_COUPL_C   MESA_VERIPHY_STATUS_COUPL_C
#define MEPA_CABLE_DIAG_STATUS_COUPL_D   MESA_VERIPHY_STATUS_COUPL_D
#define MEPA_CABLE_DIAG_STATUS_UNKNOWN   MESA_VERIPHY_STATUS_UNKNOWN
#define MEPA_CABLE_DIAG_STATUS_RUNNING   MESA_VERIPHY_STATUS_RUNNING

/** \brief PHY events */
#define MEPA_LINK_LOS MESA_PHY_LINK_LOS_EV
#define MEPA_FAST_LINK_FAIL MESA_PHY_LINK_FFAIL_EV

/** \brief PHY auto negotiation advertisement */
typedef struct {
    mepa_bool_t speed_10m_hdx;    /**< 10Mbps, half duplex */
    mepa_bool_t speed_10m_fdx;    /**< 10Mbps, full duplex */
    mepa_bool_t speed_100m_hdx;   /**< 100Mbps, half duplex */
    mepa_bool_t speed_100m_fdx;   /**< 100Mbps, full duplex */
    mepa_bool_t speed_1g_fdx;     /**< 1000Mpbs, full duplex */
    mepa_bool_t speed_1g_hdx;     /**< 1000Mpbs, full duplex */
    mepa_bool_t tx_remote_fault;  /**< Local Application fault indication for Link Partner */
    mepa_bool_t speed_2g5_fdx;    /**< 2500Mpbs, full duplex */
    mepa_bool_t speed_5g_fdx;     /**< 5GE, full duplex */
    mepa_bool_t speed_10g_fdx;    /**< 10GE, full duplex */
    mepa_bool_t no_restart_aneg;  /**< Do not restart aneg */
} mepa_aneg_adv_t;

/** \brief Cable diagnostics result */
typedef struct {
    mesa_bool_t               link;      /**< Link status */
    mepa_cable_diag_status_t  status[4]; /**< Status, pair A-D (0-3) */
    uint8_t                   length[4]; /**< Length (meters), pair A-D (0-3) */
} mepa_cable_diag_result_t;

// phy reset points
typedef enum {
    MEPA_RESET_POINT_DEFAULT = 0,
    MEPA_RESET_POINT_PRE,
    MEPA_RESET_POINT_POST,
    MEPA_RESET_POINT_POST_MAC
} mepa_reset_point_t;

typedef struct {
    mepa_media_interface_t media_intf;
    mepa_reset_point_t     reset_point;
} mepa_reset_param_t;

/* mepa_rc error codes */
#define MEPA_RC_OK                              MESA_RC_OK
#define MEPA_RC_ERROR                           MESA_RC_ERROR
#define MEPA_RC_INV_STATE                       MESA_RC_INV_STATE
#define MEPA_RC_INCOMPLETE                      MESA_RC_INCOMPLETE
#define MEPA_RC_NOT_IMPLEMENTED                 MESA_RC_NOT_IMPLEMENTED
#define MEPA_RC_ERR_PARM                        MESA_RC_ERR_PARM
#define MEPA_RC_ERR_NO_RES                      MESA_RC_ERR_NO_RES
#define MEPA_RC_ERR_KR_CONF_NOT_SUPPORTED       MESA_RC_ERR_KR_CONF_NOT_SUPPORTED
#define MEPA_RC_ERR_KR_CONF_INVALID_PARAMETER   MESA_RC_ERR_KR_CONF_INVALID_PARAMETER

typedef enum {
    MEPA_TRACE_LVL_RACKET  = 1,
    MEPA_TRACE_LVL_NOISE   = 2,
    MEPA_TRACE_LVL_DEBUG   = 4,
    MEPA_TRACE_LVL_INFO    = 6,
    MEPA_TRACE_LVL_WARNING = 8,
    MEPA_TRACE_LVL_ERROR   = 9,
    MEPA_TRACE_LVL_NONE    = 10,
} mepa_trace_level_t;

// GPIO modes
typedef enum {
    MEPA_GPIO_MODE_NONE = 0,
    MEPA_GPIO_MODE_IN,
    MEPA_GPIO_MODE_OUT,
    MEPA_GPIO_MODE_ALT,
    MEPA_GPIO_MODE_LED_LINK_ACTIVITY,
    MEPA_GPIO_MODE_LED_LINK1000_ACTIVITY,
    MEPA_GPIO_MODE_LED_LINK100_ACTIVITY,
    MEPA_GPIO_MODE_LED_LINK10_ACTIVITY,
    MEPA_GPIO_MODE_LED_LINK100_1000_ACTIVITY,
    MEPA_GPIO_MODE_LED_LINK10_1000_ACTIVITY,
    MEPA_GPIO_MODE_LED_LINK10_100_ACTIVITY,
    MEPA_GPIO_MODE_LED_LINK100BASE_FX_1000BASE_X_ACTIVITY,
    MEPA_GPIO_MODE_LED_DUPLEX_COLLISION,
    MEPA_GPIO_MODE_LED_COLLISION,
    MEPA_GPIO_MODE_LED_ACTIVITY,
    MEPA_GPIO_MODE_LED_BASE100_FX_1000BASE_X_FIBER_ACTIVITY,
    MEPA_GPIO_MODE_LED_AUTONEGOTIATION_FAULT,
    MEPA_GPIO_MODE_LED_LINK1000BASE_X_ACTIVITY,
    MEPA_GPIO_MODE_LED_LINK100BASE_FX_ACTIVITY,
    MEPA_GPIO_MODE_LED_BASE1000_ACTIVITY,
    MEPA_GPIO_MODE_LED_BASE100_FX_ACTIVITY,
    MEPA_GPIO_MODE_LED_FORCE_LED_OFF,
    MEPA_GPIO_MODE_LED_FORCE_LED_ON,
    MEPA_GPIO_MODE_LED_FAST_LINK_FAIL,
    MEPA_GPIO_MODE_LED_LINK_TX,
    MEPA_GPIO_MODE_LED_LINK_RX,
    MEPA_GPIO_MODE_LED_LINK_FAULT,
    MEPA_GPIO_MODE_LED_DISABLE_EXTENDED,
    MEPA_GPIO_MODE_RCVRD_CLK_OUT1,
    MEPA_GPIO_MODE_RCVRD_CLK_OUT2,
} mepa_gpio_mode_t;

// Led id
typedef enum {
    MEPA_LED0 = 0,
    MEPA_LED1
} mepa_led_num_t;

// Additional GPIO data used while setting gpio mode
typedef struct {
    uint8_t gpio_no;
    mepa_led_num_t led_num;
    mepa_gpio_mode_t mode;
} mepa_gpio_conf_t;

// Loopback types
typedef struct {
    mepa_bool_t far_end_ena;    // far end loopback where traffic is looped back towards link partner from pcs.
    mepa_bool_t near_end_ena;   // Near end loopback where traffic is looped back towards Mac from pcs.
    mepa_bool_t connector_ena;  // connector loopback where traffic is looped back towards Mac uing external connector.
    mepa_bool_t mac_serdes_input_ena;   // Mac side serdes input loopback where traffic is looped towards link partner.
    mepa_bool_t mac_serdes_facility_ena;// Mac side serdes facility loopback where traffic is looped towards link partner.
    mepa_bool_t mac_serdes_equip_ena;   // Mac side serdes equipment loopback where traffic is looped towards Mac.
    mepa_bool_t media_serdes_input_ena; // Media side serdes input loopback where traffic is looped towards Mac.
    mepa_bool_t media_serdes_facility_ena; // Media side serdes facility loopback where traffic is looped towards link partner.
    mepa_bool_t media_serdes_equip_ena; // Media side serdes equipment loopback where traffic is looped back towards link partner.
    mepa_bool_t qsgmii_pcs_tbi_ena;  // QSGMII tbi loopback where traffic is looped towards link partner from QSGMII pcs.
    mepa_bool_t qsgmii_pcs_gmii_ena; // QSGMII gmi loopback where traffic is looped towards Mac from QSGMII pcs.
    mepa_bool_t qsgmii_serdes_ena;   // QSGMII serdes loopback where traffic is looped towards link partner from QSGMII serdes. This would affect all the 4 ports of PHY.
} mepa_loopback_t;

// phy clock source
typedef enum {
    MEPA_SYNCE_CLOCK_SRC_DISABLED,
    MEPA_SYNCE_CLOCK_SRC_SERDES_MEDIA,
    MEPA_SYNCE_CLOCK_SRC_COPPER_MEDIA
} mepa_synce_clock_src_t;

// synce recovered clock
typedef enum {
    MEPA_SYNCE_CLOCK_DST_1 = 0,
    MEPA_SYNCE_CLOCK_DST_2,
    MEPA_SYNCE_CLOCK_DST_MAX,
} mepa_synce_clock_dst_t;

// recovered clock frequencies
typedef enum {
    MEPA_FREQ_25M,    // 25Mhz recovered clock
    MEPA_FREQ_31_25M, // 31.25Mhz receovered clock
    MEPA_FREQ_125M,   // 125Mhz recovered clock
} mepa_freq_t;

// Synce recovered clock configuration
typedef struct {
    mepa_synce_clock_src_t src; // source type
    mepa_synce_clock_dst_t dst; // recovered clock number
    mepa_freq_t            freq;// recovered clock frequency
} mepa_synce_clock_conf_t;

// mepa trace groups
typedef enum {
    MEPA_TRACE_GRP_GEN,   // PHY general features
    MEPA_TRACE_GRP_TS,    // Timestamp Api
} mepa_trace_group_t;


// lock structure
typedef struct {
    const char *function;  // function name
    const char *file;      // file name
    int        line;       // line number
} mepa_lock_t;

#include <microchip/ethernet/hdr_end.h>  // ALL INCLUDE ABOVE THIS LINE
#endif // _MICROCHIP_ETHERNET_PHY_API_TYPES_H_
