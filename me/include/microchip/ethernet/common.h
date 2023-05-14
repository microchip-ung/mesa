// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_COMMON_
#define _MICROCHIP_ETHERNET_COMMON_

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

/****************************************************************************
 * Basic types (used in includes)
 ****************************************************************************/
typedef struct mesa_state_s *mesa_inst_t;
typedef uint8_t mesa_bool_t;

#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

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
    MESA_PHY_MEDIA_IF_AMS_FI_100FX,
    MESA_PHY_MEDIA_IF_T1S_10FX,                /**< 10Base-T1S */
    MESA_PHY_MEDIA_IF_T1_100FX,                /**< 100Base-T1 */
    MESA_PHY_MEDIA_IF_T1_1000FX                /**< 1000Base-T1 */
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
    MESA_PORT_INTERFACE_RGMII,         // RGMII with no internal delay
    MESA_PORT_INTERFACE_RGMII_ID,      // RGMII with 2ns internal RX+TX delay
    MESA_PORT_INTERFACE_RGMII_RXID,    // RGMII with 2ns internal RX delay
    MESA_PORT_INTERFACE_RGMII_TXID,    // RGMII with 2ns internal TX delay
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

/** \brief PHY led intensity */
typedef uint8_t mesa_phy_led_intensity;   /**< LED intensity from 0-200, LED intensity led_intensity * 0.5 */

/* - Events ------------------------------------------------------- */
/*  PHY interrupt events */
#define MESA_PHY_LINK_LOS_EV                    (1 << 0) /**< PHY link interrupt */
#define MESA_PHY_LINK_FFAIL_EV                  (1 << 1) /**< PHY fast failure interrupt */
#define MESA_PHY_LINK_AMS_EV                    (1 << 2) /**< PHY Automatic Media Sense */
#define MESA_PHY_LINK_SPEED_STATE_CHANGE_EV     (1 << 3) /**< PHY link state change event*/
#define MESA_PHY_LINK_FDX_STATE_CHANGE_EV       (1 << 4) /**< PHY FDX state change event*/
#define MESA_PHY_LINK_AUTO_NEG_ERROR_EV         (1 << 5) /**< PHY Autonegotiation error event*/
#define MESA_PHY_LINK_AUTO_NEG_COMPLETE_EV      (1 << 6) /**< PHY Autonegotiation complete event*/
#define MESA_PHY_LINK_INLINE_POW_DEV_DETECT_EV  (1 << 7) /**< PHY Inline powered device detect event */
#define MESA_PHY_LINK_SYMBOL_ERR_INT_EV         (1 << 8) /**< PHY Symbol error event */
#define MESA_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV   (1 << 9) /**< PHY TX fifo over/underflow detect event*/
#define MESA_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV   (1 << 10) /**< PHY RX fifo over/underflow detect event*/
#define MESA_PHY_LINK_FALSE_CARRIER_INT_EV      (1 << 11) /**< PHY false-carrier interrupt event*/
#define MESA_PHY_LINK_LINK_SPEED_DS_DETECT_EV   (1 << 12) /**< PHY Link speed downshift detect event*/
#define MESA_PHY_LINK_MASTER_SLAVE_RES_ERR_EV   (1 << 13) /**< PHY master/salve resolution error event*/
#define MESA_PHY_LINK_RX_ER_INT_EV              (1 << 14) /**< PHY RX_ER interrupt event*/
#define MESA_PHY_LINK_EXTENDED_REG_INT_EV       (1 << 15) /**< PHY Use Extended Reg to Access interrupt event*/
#define MESA_PHY_LINK_WAKE_ON_LAN_INT_EV        (1 << 16) /**< PHY Wake-On-LAN interrupt event*/
/* - Extended Events Defn ------------------------------------------------------- */
#define MESA_PHY_LINK_EXT_EEE_WAKE_ERR_EV       (1 << 17) /**< PHY EEE Wake Error interrupt event*/
#define MESA_PHY_LINK_EXT_EEE_WAIT_TS_EV        (1 << 18) /**< PHY EEE Wait Quit/Rx TS Timer interrupt event*/
#define MESA_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV     (1 << 19) /**< PHY EEE Rx TQ Timer interrupt event*/
#define MESA_PHY_LINK_EXT_EEE_LINKFAIL_EV       (1 << 20) /**< PHY EEE Link Fail interrupt event*/
#define MESA_PHY_LINK_EXT_RR_SW_COMPL_EV        (1 << 21) /**< PHY Ring Resiliancy Switchover complete interrupt event*/
#define MESA_PHY_LINK_EXT_MACSEC_HOST_MAC_EV    (1 << 22) /**< PHY MACSEC Host MAC interrupt event*/
#define MESA_PHY_LINK_EXT_MACSEC_LINE_MAC_EV    (1 << 23) /**< PHY MACSEC Line MAC interrupt event*/
#define MESA_PHY_LINK_EXT_MACSEC_FC_BUFF_EV     (1 << 24) /**< PHY MACSEC Flow Control Buff interrupt event*/
#define MESA_PHY_LINK_EXT_MACSEC_INGRESS_EV     (1 << 25) /**< PHY MACSEC Ingress interrupt event*/
#define MESA_PHY_LINK_EXT_MACSEC_EGRESS_EV      (1 << 26) /**< PHY MACSEC Egress interrupt event*/
#define MESA_PHY_LINK_EXT_MEM_INT_RING_EV       (1 << 27) /**< PHY MEM Integrity Ring Control interrupt event*/

/** \brief PHY interrupt event type */
typedef  uint32_t mesa_phy_event_t;

// Chip number used for targets with multiple chips
typedef uint32_t mesa_chip_no_t;

// Error code type
typedef int32_t mesa_rc;

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

// Error codes
enum
{
    MESA_RC_OK                                  =  0,  // Success
    MESA_RC_ERROR                               = -1,  // Unspecified error
    MESA_RC_INV_STATE                           = -2,  // Invalid state for operation
    MESA_RC_INCOMPLETE                          = -3,  // Incomplete result
    MESA_RC_NOT_IMPLEMENTED                     = -4,  // Not implemented
    MESA_RC_ERR_PARM                            = -5,  // Invalid parameter
    MESA_RC_ERR_NO_RES                          = -6,  // Out of resources

    MESA_RC_ERR_KR_CONF_NOT_SUPPORTED           = -7,  // The PHY doesn't support 10GBASE_KR equalization
    MESA_RC_ERR_KR_CONF_INVALID_PARAMETER       = -8,  // One of the parameters are out of range

    // 1G ERRORS ****/
    MESA_RC_ERR_PHY_BASE_NO_NOT_FOUND           = -50,  // Port base number (first port within a chip) is not found
    MESA_RC_ERR_PHY_6G_MACRO_SETUP              = -51,  // Setup of 6G macro failed
    MESA_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED      = -52,  // PHY does not support the selected media mode
    MESA_RC_ERR_PHY_CLK_CONF_NOT_SUPPORTED      = -53,  // The PHY doesn't support clock configuration (for SynceE)
    MESA_RC_ERR_PHY_GPIO_ALT_MODE_NOT_SUPPORTED = -54,  // The PHY doesn't support the alternative mode for the selected GPIO pin
    MESA_RC_ERR_PHY_GPIO_PIN_NOT_SUPPORTED      = -55,  // The PHY doesn't support the selected GPIO pin
    MESA_RC_ERR_PHY_PORT_OUT_RANGE              = -56,  // PHY API called with port number larger than MESA_PORTS
    MESA_RC_ERR_PHY_PATCH_SETTING_NOT_SUPPORTED = -57,  // PHY API micro patch setting not supported for the port in question
    MESA_RC_ERR_PHY_LCPLL_NOT_SUPPORTED         = -58,  // PHY API LC-PLL status not supported for the port
    MESA_RC_ERR_PHY_RCPLL_NOT_SUPPORTED         = -59,  // PHY API RC-PLL status not supported for the port

    // MACSEC ERRORS
    MESA_RC_ERR_MACSEC_INVALID_SCI_MACADDR      = -60,  // From IEEE 802.1AE-2006, section 9.9 - The 64-bit value FF-FF-FF-FF-FF-FF is never used as an SCI and is reserved for use by implementations to indicate the absence of an SC or an SCI in contexts where an SC can be present
    MESA_RC_ERR_MACSEC_NOT_ENABLED              = -61,  // Trying to access port where MACSEC is not enabled
    MESA_RC_ERR_MACSEC_SECY_ALREADY_IN_USE      = -63,  // Trying to use a secy which is already in use
    MESA_RC_ERR_MACSEC_NO_SECY_FOUND            = -64,  // No SecY found for the specific port
    MESA_RC_ERR_MACSEC_NO_SECY_VACANCY          = -65,  // No secy vacancy
    MESA_RC_ERR_MACSEC_INVALID_VALIDATE_FRM     = -66,  // Validate_frames value invalid
    MESA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH   = -67,  // Could not program the SA match
    MESA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW    = -68,  // Could not program the SA flow
    MESA_RC_ERR_MACSEC_COULD_NOT_ENA_SA         = -69,  // Could not enable the SA
    MESA_RC_ERR_MACSEC_COULD_NOT_SET_SA         = -70,  // Could not set SA to in use
    MESA_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN   = -71,  // Invalid header bypass length
    MESA_RC_ERR_MACSEC_SC_NOT_FOUND             = -72,  // Could not find SC (from sci)
    MESA_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH        = -73,  // No control frame match
    MESA_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN    = -74,  // Could no set bypass pattern for CP rule
    MESA_RC_ERR_MACSEC_TIMEOUT_ISSUE            = -75,  // Internal timeout issue, bailing out
    MESA_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS   = -76,  // Could not empty the egress pipeline
    MESA_RC_ERR_MACSEC_AN_NOT_CREATED           = -77,  // AN not created.
    MESA_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS  = -78,  // Could not empty the ingress pipeline
    MESA_RC_ERR_MACSEC_TX_SC_NOT_EXIST          = -80,  // No tx SC found
    MESA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA     = -81,  // Could not disable sa
    MESA_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA      = -82,  // Could not delete rx sa
    MESA_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA      = -83,  // Could not delete tx sa
    MESA_RC_ERR_MACSEC_PATTERN_NOT_SET          = -84,  // Pattern not set
    MESA_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED     = -85,  // HW resources exhausted
    MESA_RC_ERR_MACSEC_SCI_ALREADY_EXISTS       = -86,  // SCI already exists
    MESA_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND    = -87,  // Could not find SC resources
    MESA_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE     = -88,  // Rx AN is in use
    MESA_RC_ERR_MACSEC_EMPTY_RECORD             = -89,  // Could not get an empty record
    MESA_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM      = -90,  // Could not program the xform record
    MESA_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA      = -91,  // Could not toggle SA
    MESA_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE     = -92,  // Tx AN is in use
    MESA_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE  = -93,  // All available SA's are in use
    MESA_RC_ERR_MACSEC_MATCH_DISABLE            = -94,  // MACSEC match disabled
    MESA_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE      = -95,  // All CP rules of the specific type are in use
    MESA_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID   = -96,  // The pattern priority is not valid
    MESA_RC_ERR_MACSEC_BUFFER_TOO_SMALL         = -97,  // Buffer to small, must be greater than MESA_MACSEC_FRAME_CAPTURE_SIZE_MAX
    MESA_RC_ERR_MACSEC_FRAME_TOO_LONG           = -98,  // Frame length is supposed to be less than the amount of data in the fifo
    MESA_RC_ERR_MACSEC_FRAME_TRUNCATED          = -99,  // Frame is Truncated
    MESA_RC_ERR_MACSEC_PHY_POWERED_DOWN         = -100, // Phy is powered down, i.e. the MacSec block is not accessible
    MESA_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE   = -101, // Port/Phy is not MacSec capable
    MESA_RC_ERR_MACSEC_AN_NOT_EXIST             = -102, // AN does not exist
    MESA_RC_ERR_MACSEC_NO_PATTERN_CFG           = -103, // No pattern is configured
    MESA_RC_ERR_MACSEC_MAX_MTU                  = -105, // Maximum MTU allowed is 32761 (+ 4 bytes for VLAN)
    MESA_RC_ERR_MACSEC_UNEXPECT_CP_MODE         = -106, // Unexpected CP mode
    MESA_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN     = -107, // Could not disable AN
    MESA_RC_ERR_MACSEC_RULE_OUT_OF_RANGE        = -108, // Rule id is out of range. Must not be larger than MESA_MACSEC_CP_RULES
    MESA_RC_ERR_MACSEC_RULE_NOT_EXIST           = -109, // Rule does not exist
    MESA_RC_ERR_MACSEC_CSR_READ                 = -110, // Could not do CSR read
    MESA_RC_ERR_MACSEC_CSR_WRITE                = -111, // Could not do CSR write
    MESA_RC_ERR_PHY_6G_RCPLL_ON_BASE_PORT_ONLY  = -112, // PHY API 6G RC-PLL status support only on Base port

    // MISC ERRORS
    MESA_RC_ERR_INVALID_NULL_PTR                = -200, // A pointer was unexpected NULL
    MESA_RC_ERR_INV_PORT_BOARD                  = -201, // The specific port not available on this board

    // Clause 37 ERRORS
    MESA_RC_ERR_PCS_BLOCK_NOT_SUPPORTED         = -300, // Invalid access to PCS block

    // PoE ERRORS
    MESA_RC_ERR_POE_FIRMWARE_IS_UP_TO_DATE      = -400, // The version of loaded firmware is identical to new
    MESA_RC_ERR_POE_RX_BUF_EMPTY                = -401, // poe rx buffer empty - data 0x00
    MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED          = -402, // poe firmware update error
    MESA_RC_ERR_POE_COMM_PROT_ERR               = -403, // poe rx communication protocol error
    MESA_RC_ERR_NOT_POE_PORT_ERR                = -404, // not a poe port
}; // Leave it anonymous.

// Event type.
// When a variable of this type is used as an input parameter, the API will set the variable if the event has occured.
// The API will never clear the variable. If is up to the application to clear the variable, when the event has been handled.
typedef uint8_t mesa_event_t;

// Ethernet Type
typedef uint16_t mesa_etype_t;

// VLAN Identifier
typedef uint16_t mesa_vid_t; // 0-4095

// MAC Address
typedef struct
{
    uint8_t addr[6];   // Network byte order
} mesa_mac_t;

// Number of bytes for representing MAC address (SMAC/DMAC) type
#define MESA_MAC_ADDR_SZ_BYTES 6

// MAC address (SMAC/DMAC)
typedef uint8_t mesa_mac_addr_t[MESA_MAC_ADDR_SZ_BYTES];

// Time interval in ns * 1<<16
// range +-2**47 ns = 140737 sec = 39 hours
// For example, 2.5 ns is expressed as 0x0000.0000.0002.8000
typedef int64_t mesa_timeinterval_t;

/******************************************************************************/
/* Port status                                                                */
/******************************************************************************/

// Port status parameter struct
typedef struct
{
    mesa_event_t      link_down;     // Link down event occurred since last call
    mesa_bool_t       link;          // Link is up. Remaining fields only valid if TRUE
    mesa_port_speed_t speed;         // Speed
    mesa_bool_t       fdx;           // Full duplex
    mesa_bool_t       remote_fault;  // Remote fault signalled
    mesa_bool_t       aneg_complete; // Autoneg completed (for clause_37 and Cisco aneg)

    // TRUE: PHY able to transmit from media independent interface regardless of whether the PHY has
    // determined that a valid link has been established.FALSE: PHY able to transmit from media
    // independent interface only when the PHY has determined that a valid link has been established.
    // Note This bit is only applicable to 100BASE-FX and 1000BASE-X fiber media modes.*/
    mesa_bool_t       unidirectional_ability;

    mesa_aneg_t       aneg;          // Auto negotiation result
    mesa_bool_t       mdi_cross;     // Indication of if Auto-MDIX crossover is performed
    mesa_bool_t       fiber;         // Indication of if the link is a fiber link
    mesa_bool_t       copper;        // Indication of if the link is a copper link
} mesa_port_status_t;

// Serdes macro mode
typedef enum
{
    MESA_SERDES_MODE_DISABLE,   // Disable serdes
    MESA_SERDES_MODE_NONE,      // No serdes connected
    MESA_SERDES_MODE_XAUI_12G,  // XAUI 12G mode
    MESA_SERDES_MODE_XAUI,      // XAUI 10G mode
    MESA_SERDES_MODE_RXAUI,     // RXAUI 10G mode
    MESA_SERDES_MODE_RXAUI_12G, // RXAUI 12G mode
    MESA_SERDES_MODE_2G5,       // 2.5G mode
    MESA_SERDES_MODE_QSGMII,    // QSGMII mode
    MESA_SERDES_MODE_SGMII,     // SGMII mode
    MESA_SERDES_MODE_100FX,     // 100FX mode
    MESA_SERDES_MODE_1000BaseX, // 1000BaseX mode
    MESA_SERDES_MODE_SFI,       // LAN/10G mode
    MESA_SERDES_MODE_SFI_DAC,   // LAN/10G DAC(CU)
    MESA_SERDES_MODE_SFI_SR,    // Short Range
    MESA_SERDES_MODE_SFI_ZR,    // ZR with APC hardware algorithm
    MESA_SERDES_MODE_SFI_BP,    // Backplane
    MESA_SERDES_MODE_SFI_B2B,   // Bord to Board
    MESA_SERDES_MODE_SFI_PR_NONE, // No preset
    MESA_SERDES_MODE_IDLE,      // Send idles (port appears as down for LP)
    MESA_SERDES_MODE_TEST_MODE, // Send fixed test pattern (port appears as up for LP, but no frame rx/tx)
    MESA_SERDES_MODE_SXGMII,    // 1 x USXGMII in 5G/10G mode.           Experimental unsupported mode!
    MESA_SERDES_MODE_USGMII,    // 8 x USGMII in 1G mode.                Experimental unsupported mode!
    MESA_SERDES_MODE_QXGMII,    // 4 x QXGMII in 2G5 mode.     Mode 'R'.
    MESA_SERDES_MODE_DXGMII_10G,// 2 x DXGMII_10G in 5G mode.  Mode 'U'. Experimental unsupported mode!
    MESA_SERDES_MODE_DXGMII_5G  // 2 x DXGMII_5G in 2G5 mode.  Mode 'F'. Experimental unsupported mode!
} mesa_serdes_mode_t;

// VDD power supply
typedef enum {
    MESA_VDD_1V0, // 1.0V (default)
    MESA_VDD_1V2, // 1.2V
} mesa_vdd_t;

#if defined(__GNUC__) && (__GNUC__ > 2)
#define MESA_ATTR_PRINTF(X, Y) __attribute__ ((format(printf,X,Y)))
#else
#define MESA_ATTR_PRINTF(X, Y)
#endif

// Debug printf function
// The signature is similar to that of printf(). However, the return value is
// not used anywhere within MESA.
typedef int (*mesa_debug_printf_t)(const char *fmt, ...) MESA_ATTR_PRINTF(1, 2);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_COMMON_
