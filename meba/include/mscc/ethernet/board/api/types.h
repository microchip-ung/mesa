/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <stdint.h>
#include <mscc/ethernet/switch/api.h>

#ifndef _MSCC_ETHERNET_BOARD_TYPES_H_
#define _MSCC_ETHERNET_BOARD_TYPES_H_

typedef struct meba_state_s *meba_inst_t; /**< Board API instance data */

#define MEBA_API_MK_VERSION(h,l) ((h << 16) | l) /**< Construct API version */
#define MEBA_API_VERSION_MAJOR   0               /**< Current major API version */
#define MEBA_API_VERSION_MINOR   4               /**< Current minor API version */
#define MEBA_API_VERSION         MEBA_API_MK_VERSION(MEBA_API_VERSION_MAJOR,MEBA_API_VERSION_MINOR) /**< Current API version */

#define MEBA_BIT(x)              (1<<(x))        /**< Make a bitmask for bit 'x' */
#define MEBA_BITMASK(x)          (MEBA_BIT(x)-1) /**< Make a bitmask 'x' bits wide */

/** \brief Reset point type */
typedef enum {
    MEBA_BOARD_INITIALIZE,         /**< Initialize Board */
    MEBA_PORT_RESET,               /**< Global Port Reset */
    MEBA_PORT_RESET_POST,          /**< Global Port Post Reset */
    MEBA_STATUS_LED_INITIALIZE,    /**< Status LED Initialize */
    MEBA_PORT_LED_INITIALIZE,      /**< Port LED Initialize */
    MEBA_FAN_INITIALIZE,           /**< Fan Initialize */
    MEBA_SENSOR_INITIALIZE,        /**< Sensors Initialize */
    MEBA_INTERRUPT_INITIALIZE,     /**< Interrupts Initialize */
    MEBA_SYNCE_DPLL_INITIALIZE,    /**< Initialize the SyncE DPLL i.e. setup dividers, references, monitors etc. */
} meba_reset_point_t;

/** \brief Board type */
typedef enum {
    MEBA_SENSOR_PORT_TEMP,         /**< Port temperature sensor */
    MEBA_SENSOR_BOARD_TEMP,        /**< Board/chassis temperature sensor */
} meba_sensor_t;

/** \brief Board capabilities */
typedef enum {
    MEBA_CAP_FIRST = 50000,               /**< First MEBA capability (generic) */
    MEBA_CAP_POE = MEBA_CAP_FIRST,        /**< Power Over Ethernet */
    MEBA_CAP_1588_CLK_ADJ_DAC,            /**< AD5667 DAC used to Adjust the 1588 ref clock */
    MEBA_CAP_1588_REF_CLK_SEL,            /**< Set 1588 ref clock to different frequencies */

    MEBA_CAP_TEMP_SENSORS,                /**< Number of board temperature sensors */
    MEBA_CAP_BOARD_PORT_COUNT,            /**< Number of exposed (external) ports on board */
    MEBA_CAP_BOARD_PORT_MAP_COUNT,        /**< Number of ports in the port map (may be > MEBA_CAP_BOARD_PORT_COUNT if having MEP or Mirror loop ports) */
    MEBA_CAP_LED_MODES,                   /**< Number of alternate (port) LED modes */
    MEBA_CAP_DYING_GASP,                  /**< Dying gasp power loss hardware support */
    MEBA_CAP_FAN_SUPPORT,                 /**< Is a fan supported */
    MEBA_CAP_LED_DIM_SUPPORT,             /**< Is LED dimming supported */

    MEBA_CAP_BOARD_HAS_PCB107_CPLD,       /**< The PCB107 CPLD design was originally made specifically for PCB107 but is now being used as a general component on other boards as well */
    MEBA_CAP_PCB107_CPLD_CS_VIA_MUX,      /**< Some boards drive CS to PCB107 CPLD via a mux */

    MEBA_CAP_SYNCE_CLOCK_DPLL,            /**< DPLL number for the DPLL used for SYNCE */
    MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT,      /**< Number of clock output references, including 10G ports, which must be connected to the controller outputs */
    MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT,      /**< Clock output used for PTP independent Phase/Frequency adjustment */
    MEBA_CAP_SYNCE_HO_POST_FILTERING_BW,  /**< Default holdover post filtering */
    MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT,  /**< Number of EEC options that can be selected */
    MEBA_CAP_ONE_PPS_INT_ID,              /**< ID of the interrupt handling PPS events */

    MEBA_CAP_SYNCE_DPLL_MODE_SINGLE,      /**< Board supports running SyncE/PTP in single DPLL mode */
    MEBA_CAP_SYNCE_DPLL_MODE_DUAL,        /**< Board supports running SyncE/PTP in dual DPLL mode (i.e. Independent or Common mode) */
    MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET, /**< To identify if CPLD mux has to be configured for station clock */
    MEBA_CAP_POE_BT,                      /**< Board supports PoE 802.3bt with up to 90W per port */
    MEBA_CAP_LAST                         /**< Last MEBA capability (must be last in list) */     
} meba_cap_t;

/** \brief Trace Levels */
typedef enum {
    MEBA_TRACE_LVL_RACKET  = 1,  /**< Highest level */
    MEBA_TRACE_LVL_NOISE   = 2,  /**< Lot's of debug information */
    MEBA_TRACE_LVL_DEBUG   = 4,  /**< Some debug information */
    MEBA_TRACE_LVL_INFO    = 6,  /**< Useful information */
    MEBA_TRACE_LVL_WARNING = 8,  /**< Potential code error, manual inspection required */
    MEBA_TRACE_LVL_ERROR   = 9,  /**< Code error encountered */
    MEBA_TRACE_LVL_NONE    = 10, /**< No trace */
} meba_trace_level_t;

/** \brief LED types */
typedef enum {
    MEBA_LED_TYPE_FRONT,         /**< Front LED main state */
    MEBA_LED_TYPE_POE,           /**< Front LED PoE state */
    MEBA_LED_TYPE_DC_A,          /**< Front LED DC in A state */
    MEBA_LED_TYPE_DC_B,          /**< Front LED DC in B state */
    MEBA_LED_TYPE_ALARM,         /**< Front LED Alarm state */
    MEBA_LED_TYPE_COUNT,         /**< Number of Front LED types */
} meba_led_type_t;

/** \brief LED colors */
typedef enum {
    MEBA_LED_COLOR_OFF,          /**< No LED */
    MEBA_LED_COLOR_GREEN,        /**< Green LED */
    MEBA_LED_COLOR_RED,          /**< Red LED */
    MEBA_LED_COLOR_YELLOW,       /**< Yellow LED */
    MEBA_LED_COLOR_COUNT,        /**< Number of LED colors */
} meba_led_color_t;

/** \brief Interrupt sources */
typedef enum {
    MEBA_EVENT_FIRST,                  /**< First interrupt source (generic) */
    MEBA_EVENT_LOS = MEBA_EVENT_FIRST, /**< Loss of signal - link down on PHY - loss of SFP optical signal */
    MEBA_EVENT_FLNK,                   /**< Fast link failure detect on PHY (Enzo - Atom) */
    MEBA_EVENT_AMS,                    /**< Automatic Media-Sence on PHY */

    MEBA_EVENT_VOE,                    /**< VOE interrupt */

    MEBA_EVENT_SYNC,                   /**< PTP Synchronization pulse update */
    MEBA_EVENT_EXT_SYNC,               /**< PTP External Synchronization input */
    MEBA_EVENT_EXT_1_SYNC,             /**< PTP External Synchronization 1 input (Serval only) */
    MEBA_EVENT_CLK_ADJ,                /**< PTP Clock adjustment updated */
    MEBA_EVENT_CLK_TSTAMP,             /**< PTP Clock timestamp is updated */

    /* The 4 PTP pins have individual enums as the corresponding interrupt must be enabled separately */
    MEBA_EVENT_PTP_PIN_0,              /**< PTP PIN 0 interrupt */
    MEBA_EVENT_PTP_PIN_1,              /**< PTP PIN 1 interrupt */
    MEBA_EVENT_PTP_PIN_2,              /**< PTP PIN 2 interrupt */
    MEBA_EVENT_PTP_PIN_3,              /**< PTP PIN 3 interrupt */

    MEBA_EVENT_INGR_ENGINE_ERR,        /**< TS More than one engine find match */
    MEBA_EVENT_INGR_RW_PREAM_ERR,      /**< TS Preamble too short to append timestamp */
    MEBA_EVENT_INGR_RW_FCS_ERR,        /**< TS FCS error in ingress */
    MEBA_EVENT_EGR_ENGINE_ERR,         /**< TS More than one engine find match */
    MEBA_EVENT_EGR_RW_FCS_ERR,         /**< TS FCS error in egress */
    MEBA_EVENT_EGR_TIMESTAMP_CAPTURED, /**< TS Timestamp captured in Tx TSFIFO */
    MEBA_EVENT_EGR_FIFO_OVERFLOW,      /**< TS Tx TSFIFO overflow */

    MEBA_EVENT_PUSH_BUTTON,            /**< General Purpose Push Button */
    MEBA_EVENT_MOD_DET,                /**< SFP Module Detect */

    MEBA_EVENT_LAST                    /**< No source after this */
} meba_event_t;

/**
 * \brief Interrupt signalling callback type
 *
 * \param source_id   [IN] The interrupt source which fired.
 * \param instance_no [IN] The interrupt instance which fired
 *
 **/
typedef void (*meba_event_signal_t)(meba_event_t event, uint32_t instance_no);

/**
 * \brief Board configuration retrieval function
 *
 * \param tag     [IN] Configuration item name tag
 * \param buf    [OUT] Configuration item value (text)
 * \param bufsize [IN] Size of output buffer buf
 * \param buflen [OUT] Number of valid bytes in buf
 *
 * \return Return code. Output values only defined if SUCCESS returned.
 **/
typedef mesa_rc (*meba_conf_get_t)(const char *tag,
                                   char *buf,
                                   size_t bufsize,
                                   size_t *buflen);

/**
 * \brief Debug (trace) output function
 *
 * \param level    [IN] Debug level
 * \param location [IN] File or function name
 * \param line_no  [IN] Line number
 * \param fmt      [IN] String format (printf)
 * \param ...      [IN] Formatting args
 *
 * \return Return code. Output values only defined if SUCCESS returned.
 **/
typedef void (*meba_debug_t)(meba_trace_level_t level,
                             const char *location,
                             uint32_t line_no,
                             const char *fmt,
                             ...) __attribute__ ((format (printf, 4, 5)));

/**
 * \brief [TEMPORARY] Clock event enable
 */
typedef mesa_rc (*meba_clock_event_enable_t)(meba_inst_t inst,
                                             meba_event_t event,
                                             mesa_bool_t enable);

/**
 * \brief [TEMPORARY] Clock irq handler
 *
 * \brief Handle low-level chip interrupt, generating
 * generic, application-level events.
 *
 * \param inst            [IN] The board instance.
 * \param chip_irq        [IN] Chip interrupt which triggered
 * \param signal_notifier [IN] Function to deliver decoded interrupts to
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_clock_irq_handler_t)(meba_inst_t inst,
                                            mesa_irq_t chip_irq,
                                            meba_event_signal_t signal_notifier);

/** \brief Board interface structure */
typedef struct {
    mesa_reg_read_t  reg_read;     /**< Register read function */
    mesa_reg_write_t reg_write;    /**< Register write function */
    mesa_i2c_read_t  i2c_read;     /**< I2C read function */
    mesa_i2c_write_t i2c_write;    /**< I2C write function */
    meba_conf_get_t  conf_get;     /**< Read board config */
    meba_debug_t     debug;        /**< Board debug output */
    meba_clock_event_enable_t clock_event_enable; /**< TEMPORARY */
    meba_clock_irq_handler_t clock_irq_handler;   /**< TEMPORARY */
} meba_board_interface_t;

/** \brief INTERIM board enum while cleaning up */
typedef enum {
    VTSS_BOARD_UNKNOWN = 0,
    VTSS_BOARD_LUTON10_REF = 4 /* Don't change. 1-3 are obsolete */,
    VTSS_BOARD_LUTON26_REF,
    VTSS_BOARD_JAG_CU24_REF,
    VTSS_BOARD_JAG_SFP24_REF,
    VTSS_BOARD_JAG_PCB107_REF,
    VTSS_BOARD_JAG_CU48_REF = 10 /* Don't change. 9 is obsolete */,
    VTSS_BOARD_SERVAL_REF,
    VTSS_BOARD_SERVAL_PCB106_REF,
    VTSS_BOARD_SERVAL2_NID_REF = 14 /* Don't change. 13 is obsolete */,
    VTSS_BOARD_JAGUAR2_CU48_REF,
    VTSS_BOARD_JAGUAR2_REF,
    VTSS_BOARD_JAGUAR2_AQR_REF,
    VTSS_BOARD_SERVALT_NID_REF,
    VTSS_BOARD_RIO_GRANDE_4T1T_A,  /* Proto-A, HW_ID=0 */
    VTSS_BOARD_RIO_GRANDE_4T1T,
    VTSS_BOARD_RIO_GRANDE_6T2T_A,  /* Proto-A, HW_ID=0 */
    VTSS_BOARD_RIO_GRANDE_6T2T,
    VTSS_BOARD_RIO_GRANDE_4P2S_A,  /* Proto-A, HW_ID=0 */
    VTSS_BOARD_RIO_GRANDE_4P2S,
    VTSS_BOARD_RIO_GRANDE_8P2S_A,  /* Proto-A, HW_ID=0 */
    VTSS_BOARD_RIO_GRANDE_8P2S,
    VTSS_BOARD_OCELOT_REF = 28 /* Don't change. 27 is obsolete */, // PCB120
    VTSS_BOARD_OCELOT_PCB123_REF,                                  // PCB123
    VTSS_BOARD_LUTON10_PDS408G,    /* PoE design from PoE business unit */
} vtss_board_type_t;

/** \brief Board properties struct */
typedef struct {
    // General
    char name[32];                 /**< Board name */
    mesa_target_type_t target;     /**< Target chip id */
    mesa_port_mux_mode_t mux_mode; /**< Target mux mode (optional) */
    vtss_board_type_t board_type;  /**< Board type (INTERIM) */
} meba_board_props_t;

/** \brief Port SFP status struct */
typedef struct {
    mesa_bool_t  tx_fault;         /**< TxFault */
    mesa_bool_t  los;              /**< Loss Of Signal  */
    mesa_bool_t  present;          /**< SFP module present  */
} meba_sfp_status_t;

/* ================================================================= *
 *  Port capabilities
 * ================================================================= */

#define MEBA_PORT_CAP_NONE              0x00000000 /**< No capabilities */
#define MEBA_PORT_CAP_AUTONEG           0x00000001 /**< Auto negotiation */
#define MEBA_PORT_CAP_10M_HDX           0x00000002 /**< 10 Mbps, half duplex */
#define MEBA_PORT_CAP_10M_FDX           0x00000004 /**< 10 Mbps, full duplex */
#define MEBA_PORT_CAP_100M_HDX          0x00000008 /**< 100 Mbps, half duplex */
#define MEBA_PORT_CAP_100M_FDX          0x00000010 /**< 100 Mbps, full duplex */
#define MEBA_PORT_CAP_1G_FDX            0x00000020 /**< 1 Gbps, full duplex */
#define MEBA_PORT_CAP_2_5G_FDX          0x00000040 /**< 2.5 Gbps, full duplex */
#define MEBA_PORT_CAP_5G_FDX            0x00000080 /**< 5Gbps, full duplex */
#define MEBA_PORT_CAP_10G_FDX           0x00000100 /**< 10Gbps, full duplex */
#define MEBA_PORT_CAP_25G_FDX           0x00000200 /**< 25Gbps, full duplex */
#define MEBA_PORT_CAP_FLOW_CTRL         0x00001000 /**< Flow control */
#define MEBA_PORT_CAP_COPPER            0x00002000 /**< Copper media */
#define MEBA_PORT_CAP_FIBER             0x00004000 /**< Fiber media */
#define MEBA_PORT_CAP_DUAL_COPPER       0x00008000 /**< Dual media, copper preferred */
#define MEBA_PORT_CAP_DUAL_FIBER        0x00010000 /**< Dual media, fiber preferred */
#define MEBA_PORT_CAP_SD_ENABLE         0x00020000 /**< Signal Detect enabled */
#define MEBA_PORT_CAP_SD_HIGH           0x00040000 /**< Signal Detect active high */
#define MEBA_PORT_CAP_SD_INTERNAL       0x00080000 /**< Signal Detect select internal */
#define MEBA_PORT_CAP_XAUI_LANE_FLIP    0x00200000 /**< Flip the XAUI lanes */
#define MEBA_PORT_CAP_VTSS_10G_PHY      0x00400000 /**< Connected to VTSS 10G PHY */
#define MEBA_PORT_CAP_SFP_DETECT        0x00800000 /**< Auto detect the SFP module */
#define MEBA_PORT_CAP_STACKING          0x01000000 /**< Stack port candidate */
#define MEBA_PORT_CAP_DUAL_SFP_DETECT   0x02000000 /**< Auto detect the SFP module for dual media*/
#define MEBA_PORT_CAP_SFP_ONLY          0x04000000 /**< SFP only port (not dual media)*/
#define MEBA_PORT_CAP_DUAL_NO_COPPER    0x08000000 /**< SFP copper not supported in dual media*/
#define MEBA_PORT_CAP_SERDES_RX_INVERT  0x10000000 /**< Serdes RX signal is inverted */
#define MEBA_PORT_CAP_SERDES_TX_INVERT  0x20000000 /**< Serdes TX signal is inverted */
#define MEBA_PORT_CAP_INT_PHY           0x40000000 /**< Connected to internal PHY */
#define MEBA_PORT_CAP_NO_FORCE          0x80000000 /**< Force mode is unsupported */

#define MEBA_PORT_CAP_HDX (MEBA_PORT_CAP_10M_HDX | MEBA_PORT_CAP_100M_HDX) /**< Half duplex */
#define MEBA_PORT_CAP_TRI_SPEED_FDX (MEBA_PORT_CAP_AUTONEG | MEBA_PORT_CAP_1G_FDX | MEBA_PORT_CAP_100M_FDX | MEBA_PORT_CAP_10M_FDX | MEBA_PORT_CAP_FLOW_CTRL) /**< Tri-speed port full duplex only */
#define MEBA_PORT_CAP_TRI_SPEED (MEBA_PORT_CAP_TRI_SPEED_FDX | MEBA_PORT_CAP_HDX) /**< Tri-speed port, both full and half duplex */
#define MEBA_PORT_CAP_1G_PHY (MEBA_PORT_CAP_COPPER | MEBA_PORT_CAP_FIBER | MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER) /**< 1G PHY present */

#define MEBA_PORT_CAP_TRI_SPEED_COPPER            (MEBA_PORT_CAP_TRI_SPEED | MEBA_PORT_CAP_COPPER)                                                                          /**< Tri-speed port copper only*/
#define MEBA_PORT_CAP_TRI_SPEED_FIBER             (MEBA_PORT_CAP_TRI_SPEED | MEBA_PORT_CAP_FIBER)                                                                           /**< Tri-speed port fiber only*/
#define MEBA_PORT_CAP_TRI_SPEED_DUAL_COPPER       (MEBA_PORT_CAP_TRI_SPEED | MEBA_PORT_CAP_DUAL_COPPER)                                                                     /**< Tri-speed port both fiber and copper. Copper prefered*/
#define MEBA_PORT_CAP_TRI_SPEED_DUAL_FIBER        (MEBA_PORT_CAP_TRI_SPEED | MEBA_PORT_CAP_DUAL_FIBER)                                                                      /**< Tri-speed port both fiber and copper. Fiber prefered*/
#define MEBA_PORT_CAP_ANY_FIBER                   (MEBA_PORT_CAP_FIBER | MEBA_PORT_CAP_DUAL_FIBER | MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_SFP_DETECT) /**< Any fiber mode */
#define MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER_FIXED_SPEED       (MEBA_PORT_CAP_DUAL_FIBER | MEBA_PORT_CAP_DUAL_COPPER)                             /**< Any fiber mode, but auto detection not supported */
#define MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER        (MEBA_PORT_CAP_DUAL_COPPER | MEBA_PORT_CAP_DUAL_FIBER| MEBA_PORT_CAP_DUAL_SFP_DETECT)              /**< Any fiber mode, auto detection supported */
#define MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER    (MEBA_PORT_CAP_TRI_SPEED | MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER)                                                            /**< Copper 5 Fiber mode, auto detection supported */
#define MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER_FIXED_SFP_SPEED    (MEBA_PORT_CAP_TRI_SPEED | MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER_FIXED_SPEED)                                /**< Copper & Fiber mode, but SFP auto detection not supported */
#define MEBA_PORT_CAP_DUAL_FIBER_1000X                 (MEBA_PORT_CAP_DUAL_FIBER | MEBA_PORT_CAP_DUAL_COPPER)                                                                    /**< 1000Base-X fiber mode */

#define MEBA_PORT_CAP_SFP_1G   (MEBA_PORT_CAP_AUTONEG | MEBA_PORT_CAP_100M_FDX | MEBA_PORT_CAP_1G_FDX | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_ONLY)                 /**< SFP fiber port 100FX/1G with auto negotiation and flow control */
#define MEBA_PORT_CAP_SFP_2_5G (MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_2_5G_FDX)                                                                                              /**< SFP fiber port 100FX/1G/2.5G with auto negotiation and flow control */
#define MEBA_PORT_CAP_SFP_SD_HIGH (MEBA_PORT_CAP_SD_ENABLE | MEBA_PORT_CAP_SD_HIGH | MEBA_PORT_CAP_SD_INTERNAL | MEBA_PORT_CAP_SFP_DETECT | MEBA_PORT_CAP_SFP_ONLY)                        /**< SFP fiber port 100FX/1G/2.5G with auto negotiation and flow control, signal detect high */
#define MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT (MEBA_PORT_CAP_SD_ENABLE | MEBA_PORT_CAP_SD_HIGH | MEBA_PORT_CAP_SD_INTERNAL | MEBA_PORT_CAP_SFP_ONLY)                        /**< SFP fiber port 100FX/1G/2.5G with auto negotiation and flow control, signal detect high */
#define MEBA_PORT_CAP_COPPER_10G (MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_COPPER)

#define MEBA_PORT_CAP_2_5G_TRI_SPEED_FDX     (MEBA_PORT_CAP_AUTONEG | MEBA_PORT_CAP_2_5G_FDX | MEBA_PORT_CAP_1G_FDX | MEBA_PORT_CAP_100M_FDX | MEBA_PORT_CAP_FLOW_CTRL) /**< 100M/1G/2.5G Tri-speed port full duplex only */
#define MEBA_PORT_CAP_2_5G_TRI_SPEED         (MEBA_PORT_CAP_2_5G_TRI_SPEED_FDX | MEBA_PORT_CAP_100M_HDX)                                                 /**< 100M/1G/2.5G Tri-speed port, all full duplex and 100M half duplex */
#define MEBA_PORT_CAP_2_5G_TRI_SPEED_COPPER  (MEBA_PORT_CAP_2_5G_TRI_SPEED | MEBA_PORT_CAP_COPPER)                                                        /**< 100M/1G/2.5G Tri-speed port copper only */

typedef uint64_t meba_port_cap_t; /**< Bit-mask containing the port capabilities */

/** \brief Port capabilities structure */
typedef struct {
    mesa_port_map_t        map;           /**< Port map */
    mesa_port_interface_t  mac_if;        /**< MAC interface */
    meba_port_cap_t        cap;           /**< Port capabilities */
    mesa_chip_no_t         poe_chip_port; /**< Chip port number (may be different than poe channel number) */
    mesa_bool_t            poe_support;   /**< PoE support for this port */
} meba_port_entry_t;

/** \brief Port admin state structure */
typedef struct {
    mesa_bool_t             enable; /**< Admin enable/disable */
} meba_port_admin_state_t;

/** \brief Board FAN parameters */
typedef struct {
    uint8_t start_time;    /**< The duration of time to be before going to low level (seconds) */
    uint8_t start_level;   /**< The level to be at before going to low level (pct) */
    uint8_t min_pwm;       /**< The min level supported by fan (pct) */
} meba_fan_param_t;

#endif // _MSCC_ETHERNET_BOARD_TYPES_H_
