// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_BOARD_TYPES_H_
#define _MICROCHIP_ETHERNET_BOARD_TYPES_H_

#include <stdint.h>
#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// Forward declaration
struct meba_inst;

// This typedef is needed to keep backwards compatibility. Lets avoid using this
// in the API, as it hides the fact that this is a pointer.
typedef struct meba_inst *meba_inst_t;

typedef mesa_port_admin_state_t meba_port_admin_state_t;

#define MEBA_API_MK_VERSION(h,l) ((h << 16) | l)
#define MEBA_API_VERSION_MAJOR   0
#define MEBA_API_VERSION_MINOR   4
#define MEBA_API_VERSION         MEBA_API_MK_VERSION(MEBA_API_VERSION_MAJOR, \
                                                     MEBA_API_VERSION_MINOR)

#define MEBA_BIT(x)              (1<<(x))
#define MEBA_BITMASK(x)          (MEBA_BIT(x)-1)

#define MEBA_PORT_CAP_NONE              0x000000000
#define MEBA_PORT_CAP_AUTONEG           0x000000001
#define MEBA_PORT_CAP_10M_HDX           0x000000002
#define MEBA_PORT_CAP_10M_FDX           0x000000004
#define MEBA_PORT_CAP_100M_HDX          0x000000008
#define MEBA_PORT_CAP_100M_FDX          0x000000010
#define MEBA_PORT_CAP_1G_FDX            0x000000020
#define MEBA_PORT_CAP_2_5G_FDX          0x000000040
#define MEBA_PORT_CAP_5G_FDX            0x000000080
#define MEBA_PORT_CAP_10G_FDX           0x000000100
#define MEBA_PORT_CAP_25G_FDX           0x000000200
#define MEBA_PORT_CAP_FLOW_CTRL         0x000001000
#define MEBA_PORT_CAP_COPPER            0x000002000
#define MEBA_PORT_CAP_FIBER             0x000004000

// Dual media, copper preferred
#define MEBA_PORT_CAP_DUAL_COPPER       0x000008000

// Dual media, fiber preferred
#define MEBA_PORT_CAP_DUAL_FIBER        0x000010000

#define MEBA_PORT_CAP_SD_ENABLE         0x000020000
#define MEBA_PORT_CAP_SD_HIGH           0x000040000
#define MEBA_PORT_CAP_SD_INTERNAL       0x000080000
#define MEBA_PORT_CAP_XAUI_LANE_FLIP    0x000200000
#define MEBA_PORT_CAP_VTSS_10G_PHY      0x000400000
#define MEBA_PORT_CAP_SFP_DETECT        0x000800000
#define MEBA_PORT_CAP_STACKING          0x001000000

// Auto detect the SFP module for dual media
#define MEBA_PORT_CAP_DUAL_SFP_DETECT   0x002000000

// SFP only port (not dual media)
#define MEBA_PORT_CAP_SFP_ONLY          0x004000000

// SFP copper not supported in dual media
#define MEBA_PORT_CAP_DUAL_NO_COPPER    0x008000000
#define MEBA_PORT_CAP_SERDES_RX_INVERT  0x010000000
#define MEBA_PORT_CAP_SERDES_TX_INVERT  0x020000000

// Connected to internal PHY
#define MEBA_PORT_CAP_INT_PHY           0x040000000

// Force mode is unsupported
#define MEBA_PORT_CAP_NO_FORCE          0x080000000

// CPU port
#define MEBA_PORT_CAP_CPU               0x100000000

// If (DUAL_)SFP_DETECT is set, it is indeed possible to detect whether an SFP
// is inserted. If - at the same time - SFP_INACCESSIBLE is set, the SFP's I2C
// interface is not accessible, so the application should use a MAC-to-MAC
// driver when an SFP is inserted, rather than attempting to read the SFP's ROM.
// If (DUAL_)SFP_DETECT is not set on an SFP port, SFP_INACCESSIBLE is a don't
// care, and a MAC-to-MAC driver should be used right away (copper backplane).
#define MEBA_PORT_CAP_SFP_INACCESSIBLE  0x200000000

#define MEBA_PORT_CAP_HDX        \
        (MEBA_PORT_CAP_10M_HDX | \
         MEBA_PORT_CAP_100M_HDX)

// Tri-speed port full duplex only
#define MEBA_PORT_CAP_TRI_SPEED_FDX \
        (MEBA_PORT_CAP_AUTONEG    | \
         MEBA_PORT_CAP_1G_FDX     | \
         MEBA_PORT_CAP_100M_FDX   | \
         MEBA_PORT_CAP_10M_FDX    | \
         MEBA_PORT_CAP_FLOW_CTRL)

// Tri-speed port, both full and half duplex */
#define MEBA_PORT_CAP_TRI_SPEED        \
        (MEBA_PORT_CAP_TRI_SPEED_FDX | \
         MEBA_PORT_CAP_HDX)

// 1G PHY present */
#define MEBA_PORT_CAP_1G_PHY         \
        (MEBA_PORT_CAP_COPPER      | \
         MEBA_PORT_CAP_FIBER       | \
         MEBA_PORT_CAP_DUAL_COPPER | \
         MEBA_PORT_CAP_DUAL_FIBER)

// Tri-speed port copper only
#define MEBA_PORT_CAP_TRI_SPEED_COPPER \
        (MEBA_PORT_CAP_TRI_SPEED     | \
         MEBA_PORT_CAP_COPPER)

// Tri-speed port fiber only
#define MEBA_PORT_CAP_TRI_SPEED_FIBER \
        (MEBA_PORT_CAP_TRI_SPEED    | \
         MEBA_PORT_CAP_FIBER)

// Tri-speed port both fiber and copper. Copper prefered
#define MEBA_PORT_CAP_TRI_SPEED_DUAL_COPPER \
        (MEBA_PORT_CAP_TRI_SPEED          | \
         MEBA_PORT_CAP_DUAL_COPPER)

// Tri-speed port both fiber and copper. Fiber prefered
#define MEBA_PORT_CAP_TRI_SPEED_DUAL_FIBER \
        (MEBA_PORT_CAP_TRI_SPEED         | \
         MEBA_PORT_CAP_DUAL_FIBER)

// Any fiber mode
#define MEBA_PORT_CAP_ANY_FIBER      \
        (MEBA_PORT_CAP_FIBER       | \
         MEBA_PORT_CAP_DUAL_FIBER  | \
         MEBA_PORT_CAP_DUAL_COPPER | \
         MEBA_PORT_CAP_SFP_DETECT)

// Any fiber mode, but auto detection not supported
#define MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER_FIXED_SPEED \
        (MEBA_PORT_CAP_DUAL_FIBER                    | \
         MEBA_PORT_CAP_DUAL_COPPER)

// Any fiber mode, auto detection supported
#define MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER \
        (MEBA_PORT_CAP_DUAL_COPPER       | \
         MEBA_PORT_CAP_DUAL_FIBER        | \
         MEBA_PORT_CAP_DUAL_SFP_DETECT)

// Copper 5 Fiber mode, auto detection supported
#define MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER   \
        (MEBA_PORT_CAP_TRI_SPEED               | \
         MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER)

// Copper & Fiber mode, but SFP auto detection not supported
#define MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER_FIXED_SFP_SPEED \
        (MEBA_PORT_CAP_TRI_SPEED | \
         MEBA_PORT_CAP_SPEED_DUAL_ANY_FIBER_FIXED_SPEED)

// 1000Base-X fiber mode
#define MEBA_PORT_CAP_DUAL_FIBER_1000X \
        (MEBA_PORT_CAP_DUAL_FIBER | \
         MEBA_PORT_CAP_DUAL_COPPER)

// SFP fiber port 100FX/1G with auto negotiation and flow control
#define MEBA_PORT_CAP_SFP_1G       \
        (MEBA_PORT_CAP_AUTONEG   | \
         MEBA_PORT_CAP_100M_FDX  | \
         MEBA_PORT_CAP_1G_FDX    | \
         MEBA_PORT_CAP_FLOW_CTRL | \
         MEBA_PORT_CAP_SFP_ONLY)

// SFP fiber port 100FX/1G/2.5G with auto negotiation and flow control
#define MEBA_PORT_CAP_SFP_2_5G  \
        (MEBA_PORT_CAP_SFP_1G | \
         MEBA_PORT_CAP_2_5G_FDX)

// SFP fiber port 100FX/1G/2.5G with auto negotiation and flow control, signal
// detect high

#define MEBA_PORT_CAP_SFP_SD_HIGH    \
        (MEBA_PORT_CAP_SD_ENABLE   | \
         MEBA_PORT_CAP_SD_HIGH     | \
         MEBA_PORT_CAP_SD_INTERNAL | \
         MEBA_PORT_CAP_SFP_DETECT  | \
         MEBA_PORT_CAP_SFP_ONLY)

// SFP fiber port 100FX/1G/2.5G with auto negotiation and flow control, signal
// detect high
#define MEBA_PORT_CAP_SFP_SD_HIGH_NO_DETECT \
        (MEBA_PORT_CAP_SD_ENABLE          | \
         MEBA_PORT_CAP_SD_HIGH            | \
         MEBA_PORT_CAP_SD_INTERNAL        | \
         MEBA_PORT_CAP_SFP_ONLY)

#define MEBA_PORT_CAP_COPPER_10G \
        (MEBA_PORT_CAP_10G_FDX | \
         MEBA_PORT_CAP_COPPER)

// 100M/1G/2.5G Tri-speed port full duplex only
#define MEBA_PORT_CAP_2_5G_TRI_SPEED_FDX \
        (MEBA_PORT_CAP_AUTONEG         | \
         MEBA_PORT_CAP_2_5G_FDX        | \
         MEBA_PORT_CAP_1G_FDX          | \
         MEBA_PORT_CAP_100M_FDX        | \
         MEBA_PORT_CAP_FLOW_CTRL)

// 100M/1G/2.5G Tri-speed port, all full duplex and 100M half duplex
#define MEBA_PORT_CAP_2_5G_TRI_SPEED        \
        (MEBA_PORT_CAP_2_5G_TRI_SPEED_FDX | \
         MEBA_PORT_CAP_100M_HDX)

// 100M/1G/2.5G Tri-speed port copper only
#define MEBA_PORT_CAP_2_5G_TRI_SPEED_COPPER \
        (MEBA_PORT_CAP_2_5G_TRI_SPEED     | \
         MEBA_PORT_CAP_COPPER)

// Bit-mask containing the port capabilities
typedef uint64_t meba_port_cap_t;

typedef enum {
    // Initialize Board
    MEBA_BOARD_INITIALIZE,
    // Global Port Reset
    MEBA_PORT_RESET,
    // Global Port Post Reset
    MEBA_PORT_RESET_POST,
    // Status LED Initialize
    MEBA_STATUS_LED_INITIALIZE,
    // Port LED Initialize
    MEBA_PORT_LED_INITIALIZE,
    // Fan Initialize
    MEBA_FAN_INITIALIZE,
    // Sensors Initialize
    MEBA_SENSOR_INITIALIZE,
    // Interrupts Initialize
    MEBA_INTERRUPT_INITIALIZE,
    // Initialize the SyncE DPLL i.e. setup dividers, references, monitors etc.
    MEBA_SYNCE_DPLL_INITIALIZE,
    // PoE Initialize
    MEBA_POE_INITIALIZE,
    // Phy Initialize
    MEBA_PHY_INITIALIZE
} meba_reset_point_t;

typedef enum {
    // Port temperature sensor in Celsius (signed)
    MEBA_SENSOR_PORT_TEMP,
    // Board/chassis temperature sensor in Celsius (signed)
    MEBA_SENSOR_BOARD_TEMP,
} meba_sensor_t;

typedef enum {
    MEBA_CAP_FIRST = 50000, // First MEBA capability (generic)
    MEBA_CAP_POE = MEBA_CAP_FIRST,

    // AD5667 DAC used to Adjust the 1588 ref clock
    MEBA_CAP_1588_CLK_ADJ_DAC,

    // Set 1588 ref clock to different frequencies
    MEBA_CAP_1588_REF_CLK_SEL,

    // Number of board temperature sensors
    MEBA_CAP_TEMP_SENSORS,

    // Number of exposed (external) ports on board
    MEBA_CAP_BOARD_PORT_COUNT,

    // Number of ports in the port map (may be > MEBA_CAP_BOARD_PORT_COUNT if
    // having MEP or Mirror loop ports)
    MEBA_CAP_BOARD_PORT_MAP_COUNT,

    // Number of alternate (port) LED modes
    MEBA_CAP_LED_MODES,

    // Dying gasp power loss hardware support
    MEBA_CAP_DYING_GASP,

    MEBA_CAP_FAN_SUPPORT,
    MEBA_CAP_LED_DIM_SUPPORT,  // LED Dimming

    // The PCB107 CPLD design was originally made specifically for PCB107 but is
    // now being used as a general component on other boards as well
    MEBA_CAP_BOARD_HAS_PCB107_CPLD,

    // Some boards drive CS to PCB107 CPLD via a mux
    MEBA_CAP_PCB107_CPLD_CS_VIA_MUX,

    // PCB-135 cpld
    MEBA_CAP_BOARD_HAS_PCB135_CPLD,

    // DPLL number for the DPLL used for SYNCE
    MEBA_CAP_SYNCE_CLOCK_DPLL,

    // Number of clock output references, including 10G ports, which must be
    // connected to the controller outputs
    MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT,

    // Clock output used for PTP independent Phase/Frequency adjustment
    MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT,

    // Default holdover post filtering
    MEBA_CAP_SYNCE_HO_POST_FILTERING_BW,

    // Number of EEC options that can be selected
    MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT,

    // ID of the interrupt handling PPS events
    MEBA_CAP_ONE_PPS_INT_ID,

    // Board supports running SyncE/PTP in single DPLL mode
    MEBA_CAP_SYNCE_DPLL_MODE_SINGLE,

    // Board supports running SyncE/PTP in dual DPLL mode (i.e. Independent or
    // Common mode)
    MEBA_CAP_SYNCE_DPLL_MODE_DUAL,

    // To identify if CPLD mux has to be configured for station clock
    MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET,

    // Board supports PoE 802.3bt with up to 90W per port
    MEBA_CAP_POE_BT,

    // Number of exposed (external) ports directly connected to the CPU
    MEBA_CAP_CPU_PORTS_COUNT,

    // Number of exposed (external) poe ports on board
    MEBA_CAP_BOARD_PORT_POE_COUNT,

    // For backwards compatibility, add new capabilities here!

    MEBA_CAP_LAST   // Last MEBA capability (must be last in list)
} meba_cap_t;

typedef enum {
    MEBA_TRACE_LVL_RACKET  = 1,
    MEBA_TRACE_LVL_NOISE   = 2,
    MEBA_TRACE_LVL_DEBUG   = 4,
    MEBA_TRACE_LVL_INFO    = 6,
    MEBA_TRACE_LVL_WARNING = 8,
    MEBA_TRACE_LVL_ERROR   = 9,
    MEBA_TRACE_LVL_NONE    = 10,
} meba_trace_level_t;

typedef enum {
    MEBA_LED_TYPE_FRONT,
    MEBA_LED_TYPE_POE,
    MEBA_LED_TYPE_DC_A,
    MEBA_LED_TYPE_DC_B,
    MEBA_LED_TYPE_ALARM,
    MEBA_LED_TYPE_COUNT,
} meba_led_type_t;

typedef enum {
    MEBA_LED_COLOR_OFF,
    MEBA_LED_COLOR_GREEN,
    MEBA_LED_COLOR_RED,
    MEBA_LED_COLOR_YELLOW,
    MEBA_LED_COLOR_COUNT,
} meba_led_color_t;

typedef enum {
    MEBA_EVENT_FIRST,

    // Loss of signal - link down on PHY - loss of SFP optical signal
    MEBA_EVENT_LOS = MEBA_EVENT_FIRST,

    // Fast link failure detect on PHY (Enzo - Atom)
    MEBA_EVENT_FLNK,

    // Automatic Media-Sence on PHY
    MEBA_EVENT_AMS,

    // VOE interrupt
    MEBA_EVENT_VOE,

    // PTP Synchronization pulse update
    MEBA_EVENT_SYNC,

    // PTP External Synchronization input
    MEBA_EVENT_EXT_SYNC,

    // PTP External Synchronization 1 input (Serval only)
    MEBA_EVENT_EXT_1_SYNC,

    // PTP Clock adjustment updated
    MEBA_EVENT_CLK_ADJ,

    // PTP Clock timestamp is updated
    MEBA_EVENT_CLK_TSTAMP,

    // The 4 PTP pins have individual enums as the corresponding interrupt must
    // be enabled separately
    MEBA_EVENT_PTP_PIN_0,
    MEBA_EVENT_PTP_PIN_1,
    MEBA_EVENT_PTP_PIN_2,
    MEBA_EVENT_PTP_PIN_3,

    // TS More than one engine find match
    MEBA_EVENT_INGR_ENGINE_ERR,

    // TS Preamble too short to append timestamp
    MEBA_EVENT_INGR_RW_PREAM_ERR,

    // TS FCS error in ingress
    MEBA_EVENT_INGR_RW_FCS_ERR,

    // TS More than one engine find match
    MEBA_EVENT_EGR_ENGINE_ERR,

    // TS FCS error in egress
    MEBA_EVENT_EGR_RW_FCS_ERR,

    // TS Timestamp captured in Tx TSFIFO
    MEBA_EVENT_EGR_TIMESTAMP_CAPTURED,

    // TS Tx TSFIFO overflow
    MEBA_EVENT_EGR_FIFO_OVERFLOW,

    // General Purpose Push Button
    MEBA_EVENT_PUSH_BUTTON,

    // SFP Module Detect
    MEBA_EVENT_MOD_DET,

    // KR activity
    MEBA_EVENT_KR,

    MEBA_EVENT_LAST
} meba_event_t;

typedef enum {
    MEBA_PTP_IO_CAP_UNUSED       = 0x0,
    MEBA_PTP_IO_CAP_TIME_IF_IN   = 0x1,
    MEBA_PTP_IO_CAP_TIME_IF_OUT  = 0x2,
    MEBA_PTP_IO_CAP_PIN_IN       = 0x4,
    MEBA_PTP_IO_CAP_PIN_OUT      = 0x8,
    MEBA_PTP_IO_CAP_PHY_SYNC     = 0x10
} meba_ptp_io_cap_t;

// Interrupt signalling callback type
// source_id   [IN] The interrupt source which fired.
// instance_no [IN] The interrupt instance which fired
typedef void (*meba_event_signal_t)(meba_event_t event,
                                    uint32_t instance_no);

// Board configuration call out. This is used by MEBA, to ask the application
// for certain configuration.
// tag    [IN]  Configuration item name tag
// buf    [OUT] Configuration item value (text)
// bufsize[IN]  Size of output buffer buf
// buflen [OUT] Number of valid bytes in buf
typedef mesa_rc (*meba_conf_get_t)(const char *tag,
                                   char *buf,
                                   size_t bufsize,
                                   size_t *buflen);

typedef void (*meba_debug_t)(meba_trace_level_t level,
                             const char *location,
                             uint32_t line_no,
                             const char *fmt,
                             ...);

// [TEMPORARY] Clock event enable
typedef mesa_rc (*meba_clock_event_enable_t)(struct meba_inst *inst,
                                             meba_event_t event,
                                             mesa_bool_t enable);

// [TEMPORARY] Clock irq handler
//
// Handle low-level chip interrupt, generating generic, application-level
// events.
//
// chip_irq        [IN] Chip interrupt which triggered
// signal_notifier [IN] Function to deliver decoded interrupts to
typedef mesa_rc (*meba_clock_irq_handler_t)(
        struct meba_inst *inst,
        mesa_irq_t chip_irq,
        meba_event_signal_t signal_notifier);

// MEBA call-out functions
typedef struct {
    mesa_reg_read_t  reg_read;
    mesa_reg_write_t reg_write;
    mesa_i2c_read_t  i2c_read;
    mesa_i2c_write_t i2c_write;
    meba_conf_get_t  conf_get;
    meba_debug_t     debug;
    meba_clock_event_enable_t clock_event_enable; // TEMPORARY
    meba_clock_irq_handler_t  clock_irq_handler;  // TEMPORARY
    mepa_lock_func_t  lock_enter; // lock callback function called before entering MEPA Api
    mepa_lock_func_t  lock_exit;  // unlock callback function called after executing MEPA Api
    mepa_trace_func_t trace;
} meba_board_interface_t;

 // INTERIM board enum - will be deleted eventually
typedef enum {
    VTSS_BOARD_UNKNOWN = 0,
    // 1-3 is obsolete
    VTSS_BOARD_LUTON10_REF = 4,
    VTSS_BOARD_LUTON26_REF,
    VTSS_BOARD_JAG_CU24_REF,
    VTSS_BOARD_JAG_SFP24_REF,
    VTSS_BOARD_JAG_PCB107_REF,
    // 9 is obsolete
    VTSS_BOARD_JAG_CU48_REF = 10,
    VTSS_BOARD_SERVAL_REF,
    VTSS_BOARD_SERVAL_PCB106_REF,
    // 13 is obsolete
    VTSS_BOARD_SERVAL2_NID_REF = 14,
    VTSS_BOARD_JAGUAR2_CU48_REF,
    VTSS_BOARD_JAGUAR2_REF,
    VTSS_BOARD_JAGUAR2_AQR_REF,
    VTSS_BOARD_SERVALT_NID_REF,
    // 19-27 are obsolete
    VTSS_BOARD_OCELOT_REF = 28, // PCB120
    VTSS_BOARD_OCELOT_PCB123_REF,
    VTSS_BOARD_OCELOT_PCB123_LAN8814_REF,
    VTSS_BOARD_LUTON10_PDS408G, // PoE design from PoE business unit
    VTSS_BOARD_FIREANT_PCB134_REF = 134,
    VTSS_BOARD_FIREANT_PCB135_REF = 135,
    VTSS_BOARD_LAN9668_ADARO_REF = 0x6813,
    VTSS_BOARD_LAN9668_SUNRISE_REF = 0x6849,
    VTSS_BOARD_LAN9668_SVB_REF = 0x8281,
    VTSS_BOARD_LAN9668_8PORT_REF = 0x8290,
    VTSS_BOARD_LAN9668_ENDNODE_REF = 0x8291,
    VTSS_BOARD_LAN9668_ENDNODE_CARRIER_REF = 0x8309,
    VTSS_BOARD_LAN9668_EDS2_REF = 0x8385,
} vtss_board_type_t;

typedef struct {
    char name[32];
    mesa_target_type_t   target;
    mesa_port_mux_mode_t mux_mode;

    // Board type (INTERIM) - DO NOT DEPEND ON THIS
    vtss_board_type_t board_type;
} meba_board_props_t;


typedef struct {
    mesa_port_map_t        map;
    mesa_port_interface_t  mac_if;
    meba_port_cap_t        cap;
    // Chips including multiple PHYs (dual, quad) typically have shared
    // resources. The base-port indicate which "port" owning such
    // shared resources.
    mesa_port_no_t         phy_base_port;
    // Chip port number (may be different than poe channel number)
    mesa_chip_no_t         poe_chip_port;
    mesa_bool_t            poe_support;
} meba_port_entry_t;

// Yes, this is a MEPA type defined here. In MEPA it is "just" a pointer which
// are never de-referenced.
typedef struct mepa_callout_ctx {
    mesa_inst_t             inst;
    struct meba_inst        *meba_inst;
    mepa_port_no_t          port_no;
    mesa_miim_controller_t  miim_controller;
    uint8_t                 miim_addr;
    mesa_chip_no_t          chip_no;
} mepa_callout_ctx_t;

typedef struct {
    // The duration of time to be before going to low level (seconds)
    uint8_t start_time;

    // The level to be at before going to low level (pct)
    uint8_t start_level;

    // The min level supported by fan (pct)
    uint8_t min_pwm;
} meba_fan_param_t;

typedef struct {
    mesa_bool_t  tx_fault;
    mesa_bool_t  los;        // Loss Of Signal
    mesa_bool_t  present;    // SFP module present
} meba_sfp_status_t;

#include <microchip/ethernet/board/api/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_BOARD_TYPES_H_
