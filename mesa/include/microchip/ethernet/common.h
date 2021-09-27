// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_COMMON_
#define _MICROCHIP_ETHERNET_COMMON_

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/****************************************************************************
 * Basic types (used in includes)
 ****************************************************************************/
typedef struct mesa_state_s *mesa_inst_t;
typedef uint8_t mesa_bool_t;

#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// TODO - should not be needed by MEPA!!!
// MII management controller
typedef enum
{
    MESA_MIIM_CONTROLLER_0    = 0,  // MIIM controller 0
    MESA_MIIM_CONTROLLER_1    = 1,  // MIIM controller 1
    MESA_MIIM_CONTROLLER_2    = 2,  // MIIM controller 2
    MESA_MIIM_CONTROLLER_3    = 3,  // MIIM controller 3
    MESA_MIIM_CONTROLLERS,          // Number of MIIM controllers
    MESA_MIIM_CONTROLLER_NONE = -1  // Unassigned MIIM controller
} mesa_miim_controller_t;

// Port speed
typedef enum
{
    MESA_SPEED_UNDEFINED, // Undefined
    MESA_SPEED_10M,       // 10 M
    MESA_SPEED_100M,      // 100 M
    MESA_SPEED_1G,        // 1 G
    MESA_SPEED_2500M,     // 2.5G
    MESA_SPEED_5G,        // 5G or 2x2.5G
    MESA_SPEED_10G,       // 10 G
    MESA_SPEED_12G,       // 12G
    MESA_SPEED_25G,       // 25G
    MESA_SPEED_AUTO       // Auto negotiation
} mesa_port_speed_t;

// Fiber Port speed
typedef enum
{
    MESA_SPEED_FIBER_NOT_SUPPORTED_OR_DISABLED = 0, // Fiber not supported/ Fiber port disabled
    MESA_SPEED_FIBER_100FX = 2,                     // 100BASE-FX
    MESA_SPEED_FIBER_1000X = 3,                     // 1000BASE-X
    MESA_SPEED_FIBER_AUTO = 4,                      // Auto detection - AMS mode
    MESA_SPEED_FIBER_DISABLED = 5,                  // Obsolete - use MESA_SPEED_FIBER_NOT_SUPPORTED_OR_DISABLED instead
    MESA_SPEED_FIBER_ONLY_AUTO = 6,                 // Auto detection - Fiber only (no RJ45)
} mesa_fiber_port_speed_t;

/** \brief PHY media interface type */
typedef enum {
    MESA_PHY_MEDIA_IF_CU,                      /**< Copper Interface */
    MESA_PHY_MEDIA_IF_SFP_PASSTHRU,            /**< Fiber/Cu SFP Pass-thru */
    MESA_PHY_MEDIA_IF_FI_1000BX,               /**< 1000Base-X */
    MESA_PHY_MEDIA_IF_FI_100FX,                /**< 100Base-FX */
    MESA_PHY_MEDIA_IF_AMS_CU_PASSTHRU,         /**< AMS - Cat5/SerDes/CuSFP passthru - Note the phy mode must be set to MESA_PHY_MODE_ANEG */
    MESA_PHY_MEDIA_IF_AMS_FI_PASSTHRU,         /**< AMS - Fiber passthru - Note the phy mode must be set to MESA_PHY_MODE_ANEG */
    MESA_PHY_MEDIA_IF_AMS_CU_1000BX,           /**< AMS - Cat5/1000BX/CuSFP */
    MESA_PHY_MEDIA_IF_AMS_FI_1000BX,
    MESA_PHY_MEDIA_IF_AMS_CU_100FX,            /**< AMS - Cat5/100FX/CuSFP */
    MESA_PHY_MEDIA_IF_AMS_FI_100FX
} mesa_phy_media_interface_t;

/** \brief PHY media interface type */
typedef enum {
    MESA_PHY_MDIX_AUTO,                /**< Copper media MDI auto detected */
    MESA_PHY_MDI,                      /**< Copper media forced to MDI */
    MESA_PHY_MDIX,                     /**< Copper media forced to MDI-X (Crossed cable) */
} mesa_phy_mdi_t;


// Different media/cable types attached to the 10G Serdes
typedef enum {
    MESA_SD10G_MEDIA_PR_NONE, // No preset
    MESA_SD10G_MEDIA_SR,      // Short Range
    MESA_SD10G_MEDIA_ZR,      // Long Range
    MESA_SD10G_MEDIA_DAC,     // DAC (Direct attached copper) cable, unspecified length >
    MESA_SD10G_MEDIA_DAC_1M,  // 1m DAC
    MESA_SD10G_MEDIA_DAC_2M,  // 2m DAC
    MESA_SD10G_MEDIA_DAC_3M,  // 3m DAC
    MESA_SD10G_MEDIA_DAC_5M,  // 5m DAC
    MESA_SD10G_MEDIA_BP,      // Backplane
    MESA_SD10G_MEDIA_B2B,     // Bord to Board
    MESA_SD10G_MEDIA_10G_KR   // 10G Base KR
} mesa_sd10g_media_type_t;

#define MESA_PHY_POWER_ACTIPHY_BIT 0 /**< Defines the bit used to signaling that ActiPhy is enabled */
#define MESA_PHY_POWER_DYNAMIC_BIT 1 /**< Defines the bit used to signaling that PerfectReach is enabled */

/** \brief PHY power reduction modes */
typedef enum {
    MESA_PHY_POWER_NOMINAL = 0, /**< Default power settings */
    MESA_PHY_POWER_ACTIPHY = 1 << MESA_PHY_POWER_ACTIPHY_BIT, /**< ActiPHY - Link down power savings enabled (Bit 0) */
    MESA_PHY_POWER_DYNAMIC = 1 << MESA_PHY_POWER_DYNAMIC_BIT, /**< PerfectReach - Link up power savings enabled (Bit 1) */
    MESA_PHY_POWER_ENABLED = MESA_PHY_POWER_ACTIPHY +  MESA_PHY_POWER_DYNAMIC /**< ActiPHY + PerfectReach enabled */
} mesa_phy_power_mode_t;

/** \brief VeriPHY status */
typedef enum {
    MESA_VERIPHY_STATUS_OK      = 0,  /**< Correctly terminated pair */
    MESA_VERIPHY_STATUS_OPEN    = 1,  /**< Open pair */
    MESA_VERIPHY_STATUS_SHORT   = 2,  /**< Short pair */
    MESA_VERIPHY_STATUS_ABNORM  = 4,  /**< Abnormal termination */
    MESA_VERIPHY_STATUS_SHORT_A = 8,  /**< Cross-pair short to pair A */
    MESA_VERIPHY_STATUS_SHORT_B = 9,  /**< Cross-pair short to pair B */
    MESA_VERIPHY_STATUS_SHORT_C = 10, /**< Cross-pair short to pair C */
    MESA_VERIPHY_STATUS_SHORT_D = 11, /**< Cross-pair short to pair D */
    MESA_VERIPHY_STATUS_COUPL_A = 12, /**< Abnormal cross-pair coupling, pair A */
    MESA_VERIPHY_STATUS_COUPL_B = 13, /**< Abnormal cross-pair coupling, pair B */
    MESA_VERIPHY_STATUS_COUPL_C = 14, /**< Abnormal cross-pair coupling, pair C */
    MESA_VERIPHY_STATUS_COUPL_D = 15, /**< Abnormal cross-pair coupling, pair D */
    MESA_VERIPHY_STATUS_UNKNOWN = 16, /**< Unknown - VeriPhy never started ? */
    MESA_VERIPHY_STATUS_RUNNING = 17  /**< VeriPhy is still running - No result yet */
} mesa_phy_veriphy_status_t;

/** \brief VeriPHY result */
typedef struct {
    mesa_bool_t               link;      /**< Link status */
    mesa_phy_veriphy_status_t status[4]; /**< Status, pair A-D (0-3) */
    uint8_t                   length[4]; /**< Length (meters), pair A-D (0-3) */
} mesa_phy_veriphy_result_t;

/** \brief PHY 1G status */
typedef struct {
    mesa_bool_t master_cfg_fault;  /**< Master/Slave Configuration fault */
    mesa_bool_t master;                   /**< Master = 1, Slave = 0 */
} mesa_phy_status_1g_t;

/** \brief PHY RGMII configuration */
typedef struct {
    uint16_t rx_clk_skew_ps; /**< Rx clock skew in pico seconds, see mesa_rgmii_skew_delay_psec_t for options  */
    uint16_t tx_clk_skew_ps; /**< Tx clock skew in pico seconds, see mesa_rgmii_skew_delay_psec_t for options  */
} mesa_phy_rgmii_conf_t;

/** \brief PHY TBI configuration */
typedef struct {
    mesa_bool_t aneg_enable;  /**< Enable auto negotiation */
} mesa_phy_tbi_conf_t;

/** \brief PHY forced reset interface type */
typedef enum {
    MESA_PHY_FORCE_RESET = 0,          /**< Default: Force reset of PHY, regardless of Config and HW MAC/MEDIA settings */
    MESA_PHY_NOFORCE_RESET = 1,        /**< Only reset PHY if SW Config and HW config of MAC/MEDIA settings differ */
} mesa_phy_forced_reset_t;

/** \brief PHY packet mode configuration */
typedef enum {
    MESA_PHY_PKT_MODE_IEEE_1_5_KB,  /**< IEEE NORMAL 1.5KB Pkt Length */
    MESA_PHY_PKT_MODE_JUMBO_9_KB,   /**< JUMBO 9KB Pkt Length */
    MESA_PHY_PKT_MODE_JUMBO_12_KB,  /**< JUMBO 12KB Pkt Length */
} mesa_phy_pkt_mode_t;

// The different interfaces for connecting MAC and PHY
typedef enum
{
    MESA_PORT_INTERFACE_NO_CONNECTION, // No connection
    MESA_PORT_INTERFACE_LOOPBACK,      // Internal loopback in MAC
    MESA_PORT_INTERFACE_INTERNAL,      // Internal interface
    MESA_PORT_INTERFACE_MII,           // MII (RMII does not exist)
    MESA_PORT_INTERFACE_GMII,          // GMII
    MESA_PORT_INTERFACE_RGMII,         // RGMII
    MESA_PORT_INTERFACE_TBI,           // TBI
    MESA_PORT_INTERFACE_RTBI,          // RTBI
    MESA_PORT_INTERFACE_SGMII,         // SGMII
    MESA_PORT_INTERFACE_SGMII_2G5,     // SGMII 2G5
    MESA_PORT_INTERFACE_SGMII_CISCO,   // SGMII using Cisco aneg
    MESA_PORT_INTERFACE_SERDES,        // SERDES
    MESA_PORT_INTERFACE_VAUI,          // VAUI
    MESA_PORT_INTERFACE_100FX,         // 100FX
    MESA_PORT_INTERFACE_XAUI,          // XAUI
    MESA_PORT_INTERFACE_RXAUI,         // RXAUI
    MESA_PORT_INTERFACE_XGMII,         // XGMII
    MESA_PORT_INTERFACE_SPI4,          // SPI4
    MESA_PORT_INTERFACE_QSGMII,        // QSGMII
    MESA_PORT_INTERFACE_SFI,           // SFI/LAN
    MESA_PORT_INTERFACE_SXGMII,        // 1x10G or 1x5G device.    Uses primary device. 64B/66B PCS */
    MESA_PORT_INTERFACE_USGMII,        // 8x2G5 devices. Mode 'X'. Uses 2G5 device.     */
    MESA_PORT_INTERFACE_QXGMII,        // 4x2G5 devices. Mode 'R'. Uses 2G5 device.     */
    MESA_PORT_INTERFACE_DXGMII_5G,     // 2x2G5 devices. Mode 'F'. Uses 2G5 device.     */
    MESA_PORT_INTERFACE_DXGMII_10G,    // 2x5G devices.  Mode 'U'. Uses primary device. */
} mesa_port_interface_t;

/** \brief PHY reset structure */
typedef struct {
    mesa_port_interface_t      mac_if;   /**< MAC interface */
    mesa_phy_media_interface_t media_if; /**< Media interface */
    mesa_phy_rgmii_conf_t      rgmii;    /**< RGMII MAC interface setup */
    mesa_phy_tbi_conf_t        tbi;      /**< TBI setup */
    mesa_phy_forced_reset_t    force;    /**< Force or NoForce PHY port Reset during mesa_phy_reset_private, Only used for Selected PHY Families */
    mesa_phy_pkt_mode_t        pkt_mode; /**< packet mode*/
    mesa_bool_t                i_cpu_en; /**< Set to TRUE to enable internal 8051 CPU (Enzo and Spyder family only)*/
} mesa_phy_reset_conf_t;

/** \brief PHY interrupt event type */
typedef  uint32_t mesa_phy_event_t;

// Chip number used for targets with multiple chips
typedef uint32_t mesa_chip_no_t;

// Error code type
typedef int mesa_rc;

#define MESA_PORT_NO_NONE    (0xffffffff) // Port number none
#define MESA_PORT_NO_CPU     (0xfffffffe) // Port number for CPU for special purposes
// Port Number
typedef uint32_t mesa_port_no_t;

// Auto negotiation struct
typedef struct
{
    mesa_bool_t obey_pause;      // This port should obey PAUSE frames
    mesa_bool_t generate_pause;  // Link partner obeys PAUSE frames
} mesa_aneg_t;                   // Auto negotiation result

// PHY timestamp in seconds and nanoseconds (10 bytes Timestamp)
typedef struct {
    struct {
        uint16_t high; // bits 32-47 of 48-bit second
        uint32_t low;  // bits 0-31 of 48-bit second
    } seconds; // 6 bytes second part of Timestamp
    uint32_t nanoseconds; // 4 bytes nano-sec part of Timestamp
} mesa_phy_timestamp_t;

// PPS Configuration
typedef struct mesa_phy_ts_pps_config_s {
    uint32_t   pps_width_adj ;    // The value of nano second counter upto which 1PPS is held high
    uint32_t   pps_offset;        // PPS pulse offset in nano seconds
    uint32_t   pps_output_enable; // PPS pulse output is enabled for this port
} mesa_phy_ts_pps_conf_t;

// Clock frequency ratio in scaled PartsPerBillion, defined as rate in units of ppb and multiplied by 2^16
// Example, 2.5 ppb is expressed as 0000 0000 0002 8000
typedef int64_t mesa_phy_ts_scaled_ppb_t;

//brief Timestamp interrupt events
#define MESA_PHY_TS_INGR_ENGINE_ERR            0x01  // More than one engine find match
#define MESA_PHY_TS_INGR_RW_PREAM_ERR          0x02  // Preamble too short to append timestamp
#define MESA_PHY_TS_INGR_RW_FCS_ERR            0x04  // FCS error in ingress
#define MESA_PHY_TS_EGR_ENGINE_ERR             0x08  // More than one engine find match
#define MESA_PHY_TS_EGR_RW_FCS_ERR             0x10  // FCS error in egress
#define MESA_PHY_TS_EGR_TIMESTAMP_CAPTURED     0x20  // Timestamp captured in Tx TSFIFO
#define MESA_PHY_TS_EGR_FIFO_OVERFLOW          0x40  // Tx TSFIFO overflow
#define MESA_PHY_TS_DATA_IN_RSRVD_FIELD        0x80  // Data in reserved Field
#define MESA_PHY_TS_LTC_NEW_PPS_INTRPT         0x100 // New PPS pushed onto external PPS pin
#define MESA_PHY_TS_LTC_LOAD_SAVE_NEW_TOD      0x200 // New LTC value either loaded in to HW or saved into registers

typedef uint32_t mesa_phy_ts_event_t;   // Int events: Single event or 'OR' multiple events above


// Timestamping Statistics.
typedef struct {
    uint32_t    ingr_pream_shrink_err; // Frames with preambles too short to shrink
    uint32_t    egr_pream_shrink_err;  // Frames with preambles too short to shrink
    uint32_t    ingr_fcs_err;          // Timestamp block received frame with FCS error in ingress
    uint32_t    egr_fcs_err;           // Timestamp block received frame with FCS error in egress
    uint32_t    ingr_frm_mod_cnt;      // No of frames modified by timestamp block (rewritter) in ingress
    uint32_t    egr_frm_mod_cnt;       // No of frames modified by timestamp block (rewritter) in egress
    uint32_t    ts_fifo_tx_cnt;        // the number of timestamps transmitted to the interface
    uint32_t    ts_fifo_drop_cnt;      // Count of dropped Timestamps not enqueued to the Tx TSFIFO
} mesa_phy_ts_stats_t;

// Timestamp block clock frequencies
typedef enum {
    MESA_PHY_TS_CLOCK_FREQ_125M,   // 125 MHz
    MESA_PHY_TS_CLOCK_FREQ_15625M, // 156.25 MHz
    MESA_PHY_TS_CLOCK_FREQ_200M,   // 200 MHz
    MESA_PHY_TS_CLOCK_FREQ_250M,   // 250 MHz
    MESA_PHY_TS_CLOCK_FREQ_500M,   // 500 MHz
    MESA_PHY_TS_CLOCK_FREQ_MAX,    // MAX Freq
} mesa_phy_ts_clockfreq_t;

// Clock input source
typedef enum {
    MESA_PHY_TS_CLOCK_SRC_EXTERNAL,   // External source
    // 10G: XAUI lane 0 recovered clock, 1G: MAC RX clock (note: direction is opposite to 10G, i.e. PHY->MAC)
    MESA_PHY_TS_CLOCK_SRC_CLIENT_RX,
    // 10G: XAUI lane 0 recovered clock,1G: MAC TX clock (note:  direction is opposite to 10G, i.e. MAC->PHY)
    MESA_PHY_TS_CLOCK_SRC_CLIENT_TX,
    MESA_PHY_TS_CLOCK_SRC_LINE_RX,    // Received line clock
    MESA_PHY_TS_CLOCK_SRC_LINE_TX,    // transmitted line clock
    MESA_PHY_TS_CLOCK_SRC_INTERNAL,   // 10G: Invalid, 1G: Internal 250 MHz Clock
} mesa_phy_ts_clock_src_t;

//Rx Timestamp position inside PTP frame
typedef enum {
    MESA_PHY_TS_RX_TIMESTAMP_POS_IN_PTP, // Rx timestamp in Reserved 4 bytes of PTP header
    MESA_PHY_TS_RX_TIMESTAMP_POS_AT_END, // Shrink Preamble by 4 bytes and append 4 bytes at the end of frame
} mesa_phy_ts_rxtimestamp_pos_t;

// RX Timestamp length in PTP header reserved field, 30bit or 32bit
typedef enum {
    MESA_PHY_TS_RX_TIMESTAMP_LEN_30BIT, // The nanosecCounter i.e. [0..999999999]
    MESA_PHY_TS_RX_TIMESTAMP_LEN_32BIT, // nanosecCounter + secCounter*10^9
} mesa_phy_ts_rxtimestamp_len_t;

// Defines Tx TSFIFO access mode.
typedef enum {
    MESA_PHY_TS_FIFO_MODE_NORMAL, // Timestamp can be read from normal CPU interface
    MESA_PHY_TS_FIFO_MODE_SPI,    /// Timestamps are pushed out on the SPI interface
} mesa_phy_ts_fifo_mode_t;

// Length of Timestamp stored in Tx TSFIFO.
typedef enum {
    MESA_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE,  // 4 byte Tx timestamp
    MESA_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE, // 10 byte Tx timestamp
} mesa_phy_ts_fifo_timestamp_len_t;


// PTP Clock operational modes
typedef enum {
    MESA_PHY_TS_PTP_CLOCK_MODE_BC1STEP, // Ordinary/Boundary clock, 1 step
    MESA_PHY_TS_PTP_CLOCK_MODE_BC2STEP, // Ordinary/Boundary clock, 2 step
    MESA_PHY_TS_PTP_CLOCK_MODE_TC1STEP, // Transparent clock, 1 step
    MESA_PHY_TS_PTP_CLOCK_MODE_TC2STEP, // Transparent clock, 2 step
    MESA_PHY_TS_PTP_DELAY_COMP_ENGINE,  //  Delay Compenstaion
} mesa_phy_ts_ptp_clock_mode_t;

//PTP delay measurement method
typedef enum {
    MESA_PHY_TS_PTP_DELAYM_P2P, // Peer-to-Peer delay measurement method
    MESA_PHY_TS_PTP_DELAYM_E2E, // End-to-End delay measurement method
} mesa_phy_ts_ptp_delaym_type_t;

typedef struct {
    mesa_bool_t             enable;
} mesa_port_admin_state_t;

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_COMMON_
