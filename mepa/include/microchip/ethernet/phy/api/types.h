// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_PHY_API_TYPES_H_
#define _MICROCHIP_ETHERNET_PHY_API_TYPES_H_

#include <microchip/ethernet/common.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

struct mepa_callout_ctx;

struct mepa_ts_driver;

/** \brief Contains methods that are specific to each phy. */
struct mepa_driver;

/** \brief Represents an instance of the mepa_driver. */
struct mepa_device;
typedef struct mepa_device mepa_device_t;

/**  This is pure annotation to warn the user that a given pointer will be used
     stored internally and used at a later point in time. Application is
     responsible for ensuring that such pointers remains valid through out the
     lifetime of the givne MEPA instance. */
#define MEPA_SHARED_PTR

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
typedef mesa_debug_printf_t mepa_debug_print_t;
typedef uint16_t mepa_vid_t;
typedef uint16_t mepa_etype_t;

/** \brief Advertise disable flags. */
typedef enum {
    MEPA_ADV_DIS_HDX = 0x00000001,     /**< Disable Half duplex */
    MEPA_ADV_DIS_FDX = 0x00000002,     /**< Disable Full duplex */
    MEPA_ADV_UP_MEP_LOOP = 0x00000004, /**< Use port for UP MEP loop port */
    MEPA_ADV_DIS_2500M = 0x00000008,   /**< Disable 2.5G mode */
    MEPA_ADV_DIS_1G = 0x00000010,      /**< Disable 1G mode */
    MEPA_ADV_DIS_100M = 0x00000040,    /**< Disable 100Mbit mode */
    MEPA_ADV_DIS_10M = 0x00000080,     /**< Disable 10Mbit mode */
    MEPA_ADV_DIS_5G = 0x00000100,      /**< Disable 5G mode */
    MEPA_ADV_DIS_10G = 0x00000200,     /**< Disable 10G mode */
    MEPA_ADV_DIS_RESTART_ANEG = 0x00000400, /**< Do not restart aneg */
    MEPA_ADV_DIS_SPEED =
        (MEPA_ADV_DIS_10M | MEPA_ADV_DIS_100M | MEPA_ADV_DIS_1G |
         MEPA_ADV_DIS_2500M | MEPA_ADV_DIS_5G |
         MEPA_ADV_DIS_10G), /**< All speed bits */
    MEPA_ADV_DIS_DUPLEX =
        (MEPA_ADV_DIS_HDX | MEPA_ADV_DIS_FDX), /**< All duplex bits */
    MEPA_ADV_DIS_ALL = (MEPA_ADV_DIS_SPEED | MEPA_ADV_DIS_DUPLEX |
                            MEPA_ADV_UP_MEP_LOOP) /**< All valid bits */
} mepa_adv_dis_t;


/** \brief Port speeds */
#define MEPA_SPEED_UNDEFINED MESA_SPEED_UNDEFINED
#define MEPA_SPEED_10M       MESA_SPEED_10M
#define MEPA_SPEED_100M      MESA_SPEED_100M
#define MEPA_SPEED_1G        MESA_SPEED_1G
#define MEPA_SPEED_AUTO      MESA_SPEED_AUTO

typedef mesa_port_admin_state_t mepa_port_admin_state_t;

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

/** \brief MAC Address */
typedef struct
{
    uint8_t addr[6];   /**< Network byte order */
} mepa_mac_t;

/** \brief Cable diagnostics result */
typedef struct {
    mesa_bool_t               link;      /**< Link status */
    mepa_cable_diag_status_t  status[4]; /**< Status, pair A-D (0-3) */
    uint8_t                   length[4]; /**< Length (meters), pair A-D (0-3) */
} mepa_cable_diag_result_t;

/** \brief phy reset points */
typedef enum {
    MEPA_RESET_POINT_DEFAULT = 0,
    MEPA_RESET_POINT_PRE,
    MEPA_RESET_POINT_POST,
    MEPA_RESET_POINT_POST_MAC
} mepa_reset_point_t;

typedef struct {
    mepa_media_interface_t media_intf;
    mepa_reset_point_t     reset_point;
    mepa_bool_t            framepreempt_en;      // default is disable(0)
} mepa_reset_param_t;

/** \brief Represents the status of the PHY. */
typedef struct {
    mepa_bool_t link;        /**< Link is up */
    mepa_port_speed_t speed; /**< Speed */
    mepa_bool_t fdx;         /**< Full duplex */
    mepa_aneg_t aneg;        /**< Auto-negotiation */
    mepa_bool_t copper;      /**< For dual-media ports */
    mepa_bool_t fiber;       /**< For dual-media ports */
} mepa_status_t;

/** \brief manual negotiation preferred state */
typedef enum {
    MEPA_MANUAL_NEG_DISABLED = 0, /**< Disable manual preference of master/slave states in IEEE registers 9,10 for 1G speed */
    MEPA_MANUAL_NEG_REF,          /**< master state used in IEEE registers 9,10 for 1G speed */
    MEPA_MANUAL_NEG_CLIENT        /**< slave  state used in IEEE registers 9,10 for 1G speed */
} mepa_manual_neg_t;

/** \brief preferred Media Mode MDI/MDIX/AUTO */
typedef enum {
    MEPA_MEDIA_MODE_AUTO = 0, /**< AMDIX */
    MEPA_MEDIA_MODE_MDI,      /**< MDI */
    MEPA_MEDIA_MODE_MDIX,     /**< MDIX */
} mepa_media_mode_t;

/** \breif preferred I2C clock ftrequency select */
typedef enum {
    MEPA_I2C_CLK_SEL_0 = 0, /** 100 Khz */
    MEPA_I2C_CLK_SEL_1, /** 200 Khz */
    MEPA_I2C_CLK_SEL_2, /** 800 Khz */
    MEPA_I2C_CLK_SEL_3 /** 4Mhz */
} mepa_i2c_clk_select_t;

/** \brief preferref Force Media AMS Select */
typedef enum {
    MEPA_PHY_MEDIA_FORCE_AMS_SEL_NORMAL = 0, /**< Force AMS Override to Force Selection - Normal */
    MEPA_PHY_MEDIA_FORCE_AMS_SEL_SERDES,     /**< Force AMS Override to Force Selection - SerDes Media */
    MEPA_PHY_MEDIA_FORCE_AMS_SEL_COPPER,     /**< Force AMS Override to Force Selection - Copper Media */
} mepa_phy_media_force_ams_sel_t;

/** \brief Represents the configuration that is applied to PHY. */
typedef struct {
    mepa_port_speed_t speed;       /**< Forced port speed */
    mepa_bool_t fdx;               /**< Forced duplex mode */
    mepa_bool_t flow_control;      /**< Flow control (Standard 802.3x) */
    uint32_t adv_dis;              /**< Auto neg advertisement disable */
    mepa_port_admin_state_t admin; /**< Admin state */
    mepa_aneg_adv_t aneg;          /**< Auto-negitiation advertisement */
    mepa_bool_t mac_if_aneg_ena;   /**< Enable auto-negotiation on host mac interface */
    mepa_manual_neg_t man_neg;     /**< manual negotiation control in 1G instead of using auto-negotiation */
    mepa_media_mode_t mdi_mode;    /**< Preferred media mode */
    mepa_phy_media_force_ams_sel_t force_ams_mode_sel; /**< Force AMS Media Select */
} mepa_conf_t;

/** \brief  MEPA event mask */
typedef uint32_t mepa_event_t;


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

#define MEPA_RC_ERR_TS_ENG_MAP                  -201 /**< Input flow index could not be converted to appropriate Engine id */
#define MEPA_RC_ERR_TS_ENG_INIT                 -202 /**< Engine init configuration error */
#define MEPA_RC_ERR_TS_ENG_ENCAP_OVERWRITE      -203 /**< Engine already has encapsulation configured on it. */
#define MEPA_RC_ERR_TS_ENG_INVALID_CLOCK        -204 /**< Invalid clock id for engine which contains the flow. */
#define MEPA_RC_ERR_TS_INVALID_ENCAP            -205 /**< Invalid encapsulation id */
#define MEPA_RC_ERR_TS_ENG_COMM_OVERWRITE       -206 /**< Engine common configuration options cannot be overwritten. */
#define MEPA_RC_ERR_TS_FLOW_CONF                -207 /**< Error in setting underlying engine's flow configuration */
#define MEPA_RC_ERR_TS_ACTION_IN_USE            -208 /**< Action in use by other port sharing the engine */
#define MEPA_RC_ERR_TS_ACTION_GET_FAIL          -209 /**< Failed to get the action information */
#define MEPA_RC_ERR_TS_FLOW_GET_FAIL            -210 /**< Error in obtaining underlying engine's flow configuration */
#define MEPA_RC_ERR_TS_ENG_CLR                  -211 /**< Error in clearing the engine configuration */


typedef enum {
    MEPA_TRACE_LVL_RACKET  = 1,
    MEPA_TRACE_LVL_NOISE   = 2,
    MEPA_TRACE_LVL_DEBUG   = 4,
    MEPA_TRACE_LVL_INFO    = 6,
    MEPA_TRACE_LVL_WARNING = 8,
    MEPA_TRACE_LVL_ERROR   = 9,
    MEPA_TRACE_LVL_NONE    = 10,
} mepa_trace_level_t;

/** \brief GPIO modes */
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

/** \brief Led id */
typedef enum {
    MEPA_LED0 = 0,
    MEPA_LED1
} mepa_led_num_t;

/** \brief Additional GPIO data used while setting gpio mode */
typedef struct {
    uint8_t gpio_no;
    mepa_led_num_t led_num;
    mepa_gpio_mode_t mode;
} mepa_gpio_conf_t;

/** \brief SOF Preemption mode */
typedef enum {
    MEPA_PREEMPTION_NORMAL_SFD = 0,
    MEPA_PREEMPTION_SMD_E,
    MEPA_PREEMPTION_SMD_EXCEPT_CONTINUOUS,
    MEPA_PREEMPTION_SMD_ALL,
} mepa_preemption_mode_t;

/** \brief SOF data */
typedef struct {
    uint8_t sof_no;
    mepa_bool_t ingress;
    mepa_preemption_mode_t sof_preemption_mode;
} mepa_start_of_frame_conf_t;

/**< Loopback types */
typedef struct {
    mepa_bool_t far_end_ena;    /**< far end loopback where traffic is looped back towards link partner from pcs. */
    mepa_bool_t near_end_ena;   /**< Near end loopback where traffic is looped back towards Mac from pcs. */
    mepa_bool_t connector_ena;  /**< connector loopback where traffic is looped back towards Mac uing external connector. */
    mepa_bool_t mac_serdes_input_ena;   /**< Mac side serdes input loopback where traffic is looped towards link partner. */
    mepa_bool_t mac_serdes_facility_ena;/**< Mac side serdes facility loopback where traffic is looped towards link partner. */
    mepa_bool_t mac_serdes_equip_ena;   /**< Mac side serdes equipment loopback where traffic is looped towards Mac. */
    mepa_bool_t media_serdes_input_ena; /**< Media side serdes input loopback where traffic is looped towards Mac. */
    mepa_bool_t media_serdes_facility_ena; /**< Media side serdes facility loopback where traffic is looped towards link partner. */
    mepa_bool_t media_serdes_equip_ena; /**< Media side serdes equipment loopback where traffic is looped back towards link partner. */
    mepa_bool_t qsgmii_pcs_tbi_ena;  /**< QSGMII tbi loopback where traffic is looped towards link partner from QSGMII pcs. */
    mepa_bool_t qsgmii_pcs_gmii_ena; /**< QSGMII gmi loopback where traffic is looped towards Mac from QSGMII pcs. */
    mepa_bool_t qsgmii_serdes_ena;   /**< QSGMII serdes loopback where traffic is looped towards link partner from QSGMII serdes. This would affect all the 4 ports of PHY. */
} mepa_loopback_t;

/** \brief phy clock source */
typedef enum {
    MEPA_SYNCE_CLOCK_SRC_DISABLED,
    MEPA_SYNCE_CLOCK_SRC_SERDES_MEDIA,
    MEPA_SYNCE_CLOCK_SRC_COPPER_MEDIA,
    MEPA_SYNCE_CLOCK_SRC_CLOCK_IN_1,
    MEPA_SYNCE_CLOCK_SRC_CLOCK_IN_2
} mepa_synce_clock_src_t;

/** \brief synce recovered clock */
typedef enum {
    MEPA_SYNCE_CLOCK_DST_1 = 0,
    MEPA_SYNCE_CLOCK_DST_2,
    MEPA_SYNCE_CLOCK_DST_MAX,
} mepa_synce_clock_dst_t;

/** \brief recovered clock frequencies */
typedef enum {
    MEPA_FREQ_25M,    /**< 25Mhz recovered clock */
    MEPA_FREQ_31_25M, /**< 31.25Mhz receovered clock */
    MEPA_FREQ_125M,   /**< 125Mhz recovered clock */
} mepa_freq_t;

/** \brief Synce recovered clock configuration */
typedef struct {
    mepa_synce_clock_src_t src; /**< source type */
    mepa_synce_clock_dst_t dst; /**< recovered clock number */
    mepa_freq_t            freq;/**< recovered clock frequency */
} mepa_synce_clock_conf_t;

/** \brief mepa trace groups */
typedef enum {
    MEPA_TRACE_GRP_GEN,   /**< PHY general features */
    MEPA_TRACE_GRP_TS,    /**< Timestamp Api */
} mepa_trace_group_t;

typedef struct {
    mepa_trace_group_t  group;
    mepa_trace_level_t  level;
    const char         *location;
    uint32_t            line;
    const char         *format;
} mepa_trace_data_t;

/** \brief lock structure */
typedef struct {
    const char *function;  /**< function name */
    const char *file;      /**< file name */
    int        line;       /**< line number */
} mepa_lock_t;

/** \brief PHY type */
typedef enum {
    MEPA_CAP_SPEED_MASK_1G = 0x1,  /**< PHY supports maximum speed of 1G. */
    MEPA_CAP_SPEED_MASK_2G5 = 0x40,/**< PHY supports maximum speed of 2G5. */
    MEPA_CAP_SPEED_MASK_10G = 0x2, /**< PHY supports maximum speed of 10G. */
    MEPA_CAP_TS_MASK_GEN_1 = 0x4,  /**< PHY supports timestamping capability of GEN-1 devices such as vsc8574. */
    MEPA_CAP_TS_MASK_GEN_2 = 0x8,  /**< PHY supports timestamping capability of GEN-2 devices such as vsc8584, vsc8490. */
    MEPA_CAP_TS_MASK_GEN_3 = 0x10, /**< PHY supports timestamping capability of GEN-3 devices such as Lan8814. */
    MEPA_CAP_TS_MASK_NONE  = 0x20, /**< PHY does not support timestamping capability. */
} mepa_phy_cap_t;

/** \brief phy info
 *  vsc-phy note: In VSC-phys such as vsc8574, base port and alternate port pairs like {0,2} and {1,3} share the same 1588 engine. Suppose {0,2} is the timestamping po     rt pair.
 *  Port '0' is the base port and Port '2' is the alternate port. */
typedef struct {
    uint16_t             part_number;     /**< Part number */
    uint16_t             revision;        /**< Chip revision. */
    mepa_phy_cap_t       cap;             /**< PHY capability 1G or 10G phy. */
    mepa_port_no_t       ts_base_port;    /**< Timestamping base port number. VSC-phys like vsc8574 have 2 different timestamping base ports 0 and 1 in a phy. See note above. */
} mepa_phy_info_t;

/** \brief Debug layer */
typedef enum {
    MEPA_DEBUG_LAYER_ALL, /**< All layers */
    MEPA_DEBUG_LAYER_AIL, /**< Application Interface Layer */
    MEPA_DEBUG_LAYER_CIL  /**< Chip Interface Layer */
} mepa_debug_layer_t;

 /** \brief Debug function group */
typedef enum {
    MEPA_DEBUG_GROUP_ALL    ,    /**< All groups */
    MEPA_DEBUG_GROUP_PHY    ,    /**< PHY */
    MEPA_DEBUG_GROUP_PHY_TS ,    /**< PHY_TS: PHY TimeStamping */
    MEPA_DEBUG_GROUP_MACSEC ,    /**< 802.1AE MacSec */

    /* New groups are added above this line */
    MEPA_DEBUG_GROUP_COUNT      /**< Number of groups */
} mepa_debug_group_t;

/** \brief Debug information structure */
typedef struct {
    mepa_debug_layer_t layer;       /**< Layer */
    mepa_debug_group_t group;       /**< Function group */
    mepa_bool_t        full;        /**< Full information dump */
    mepa_bool_t        clear;       /**< Clear counters */
    mepa_bool_t        vml_format;  /**< VML format register dump */
} mepa_debug_info_t;

/** \brief self-test information structure */
typedef struct {
    mepa_port_speed_t	speed;
    mepa_media_mode_t	mdi;
    uint32_t		frames;
    uint32_t		good_cnt;
    uint32_t		err_cnt;
} mepa_selftest_info_t;

/** \brief PRBS information */
typedef enum {
    MEPA_PHY_DIRECTION_HOST, /**< To configure HOST PRBS */
    MEPA_PHY_DIRECTION_LINE, /**< To configure LINE PRBS */
    MEPA_PHY_DIRECTION_CNT,  /**< ENUM Count             */
} mepa_phy_prbs_direction_t;

/** \brief PRBS information */
typedef enum {
    MEPA_PHY_PRBS_TYPE_SERDES, /**< Configure SERDES prbs */
    MEPA_PHY_PRBS_TYPE_PCS,    /**< Configure PCS prbs    */
    MEPA_PHY_PRBS_TYPE_CNT,    /**< ENUM Count            */
} mepa_phy_prbs_type_t;

/** \brief PRBS mode */
typedef enum {
    MEPA_PRBS7, /**< PRBS mode 7 */
    MEPA_PRBS15,/**< PRBS mode 15 */
    MEPA_PRBS31,/**< PRBS mode 31 */
}mepa_prbs_pattern_t;

/** \brief PRBS clock */
typedef enum {
    MEPA_PRBS_CLK25_MHZ, /**< Clock 25MHz */
    MEPA_PRBS_CLK125_MHZ,/**< Clock 125MHz */
} mepa_prbs_clock_t;

/** \brief PRBS Loopback */
typedef enum {
    MEPA_PRBS_INTERNAL_LOOPBACK, /**< Internal loopback for PRBS */
    MEPA_PRBS_EXTERNAL_LOOPBACK, /**< External loopback for PRBS */
} mepa_prbs_loopback_t;

/** \brief PRBS Information */
typedef struct {
    mepa_bool_t enable;            /**< Enabling PRBS */
    mepa_prbs_pattern_t prbsn_sel; /**< PRBS mode selection */
    mepa_prbs_clock_t clk;         /**< Clock selection */
    mepa_prbs_loopback_t loopback; /**< Loopback selection */
} mepa_phy_prbs_generator_conf_t;

/** \brief PRBS Error Information */
typedef struct {
    mepa_prbs_pattern_t  prbsn_sel; /**< PRBS mode selection */
    uint32_t no_of_errors;          /**< Error Generation */
} mepa_phy_prbs_monitor_conf_t;

/** \brief API version */
typedef uint16_t mepa_restart_version_t;

/** \brief Restart type */
typedef enum {
    /**< Cold: Chip and CPU restart, e.g. power cycling */
    MEPA_RESTART_COLD,
    /**< Cool: Chip and CPU restart done by CPU */
    MEPA_RESTART_COOL,
    /**< Warm: CPU restart only */
    MEPA_RESTART_WARM
} mepa_restart_t;

/** \brief Restart status */
typedef struct {
    mepa_restart_t restart;      /**< Previous restart mode */
    mepa_restart_t prev_version; /**< Previous API version */
    mepa_restart_t cur_version;  /**< Current API version */
} mepa_restart_status_t;

/** \brief Restart info */
typedef struct {
    mepa_restart_t         restart_cur;      /* Current restart configuration */
    mepa_restart_t         restart_prev;    /* Previous restart configuration */
    mepa_restart_version_t version_cur;     /* Current version */
    mepa_restart_version_t  version_prev;    /* Previous version */
} mepa_restart_info_t;



#include <microchip/ethernet/hdr_end.h>  /**< ALL INCLUDE ABOVE THIS LINE */
#endif /**< _MICROCHIP_ETHERNET_PHY_API_TYPES_H_ */
