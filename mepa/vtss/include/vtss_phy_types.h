// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <vtss_phy_api.h>
#include <microchip/ethernet/phy/api/phy.h>

#ifndef _VTSS_PHY_TYPES_H_
#define _VTSS_PHY_TYPES_H_

#include <vtss_phy_api.h>
#include <stdint.h>
#include <string.h>

/** \brief C99 Integer types */
typedef int8_t             i8;   /**<  8-bit signed */
typedef int16_t            i16;  /**< 16-bit signed */
typedef int32_t            i32;  /**< 32-bit signed */
typedef int64_t            i64;  /**< 64-bit signed */

typedef uint8_t            u8;   /**<  8-bit unsigned */
typedef uint16_t           u16;  /**< 16-bit unsigned */
typedef uint32_t           u32;  /**< 32-bit unsigned */
typedef uint64_t           u64;  /**< 64-bit unsigned */

typedef uint8_t            BOOL; /**< Boolean implemented as 8-bit unsigned */

#if !defined(TRUE)
#define TRUE  1 /**< True boolean value */
#endif
#if !defined(FALSE)
#define FALSE 0 /**< False boolean value */
#endif

/** \brief Error code type */
typedef int vtss_rc;

/** \brief Error codes */
enum
{
    VTSS_RC_OK                                  =  0,  /**< Success */
    VTSS_RC_ERROR                               = -1,  /**< Unspecified error */
    VTSS_RC_INV_STATE                           = -2,  /**< Invalid state for operation */
    VTSS_RC_INCOMPLETE                          = -3,  /**< Incomplete result */
    VTSS_RC_NOT_IMPLEMENTED                     = -4,  /**< Not implemented */
    VTSS_RC_ERR_PARM                            = -5,  /**< Invalid parameter */
    VTSS_RC_ERR_NO_RES                          = -6,  /**< Out of resources */

    VTSS_RC_ERR_KR_CONF_NOT_SUPPORTED           = -7,  /**< The PHY doesn't support 10GBASE_KR equalization */
    VTSS_RC_ERR_KR_CONF_INVALID_PARAMETER       = -8,  /**< One of the parameters are out of range */

    /**** 1G ERRORS ****/
    VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND           = -50,  /**< Port base number (first port within a chip) is not found */
    VTSS_RC_ERR_PHY_6G_MACRO_SETUP              = -51,  /**< Setup of 6G macro failed */
    VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED      = -52,  /**< PHY does not support the selected media mode */
    VTSS_RC_ERR_PHY_CLK_CONF_NOT_SUPPORTED      = -53,  /**< The PHY doesn't support clock configuration (for SynceE) */
    VTSS_RC_ERR_PHY_GPIO_ALT_MODE_NOT_SUPPORTED = -54,  /**< The PHY doesn't support the alternative mode for the selected GPIO pin*/
    VTSS_RC_ERR_PHY_GPIO_PIN_NOT_SUPPORTED      = -55,  /**< The PHY doesn't support the selected GPIO pin */
    VTSS_RC_ERR_PHY_PORT_OUT_RANGE              = -56,  /**< PHY API called with port number larger than VTSS_PORTS*/
    VTSS_RC_ERR_PHY_PATCH_SETTING_NOT_SUPPORTED = -57,  /**< PHY API micro patch setting not supported for the port in question*/
    VTSS_RC_ERR_PHY_LCPLL_NOT_SUPPORTED         = -58,  /**< PHY API LC-PLL status not supported for the port */
    VTSS_RC_ERR_PHY_RCPLL_NOT_SUPPORTED         = -59,  /**< PHY API RC-PLL status not supported for the port */

    /**** MACSEC ERRORS ****/
    VTSS_RC_ERR_MACSEC_INVALID_SCI_MACADDR      = -60,  /**< From IEEE 802.1AE-2006, section 9.9 - The 64-bit value FF-FF-FF-FF-FF-FF is never used as an SCI and is reserved for use by implementations to indicate the absence of an SC or an SCI in contexts where an SC can be present */
    VTSS_RC_ERR_MACSEC_NOT_ENABLED              = -61,  /**< Trying to access port where MACSEC is not enabled*/
    VTSS_RC_ERR_MACSEC_SECY_ALREADY_IN_USE      = -63,  /**< Trying to use a secy which is already in use*/
    VTSS_RC_ERR_MACSEC_NO_SECY_FOUND            = -64,  /**< No SecY found for the specific port*/
    VTSS_RC_ERR_MACSEC_NO_SECY_VACANCY          = -65,  /**< No secy vacancy*/
    VTSS_RC_ERR_MACSEC_INVALID_VALIDATE_FRM     = -66,  /**< Validate_frames value invalid*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH   = -67,  /**< Could not program the SA match*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW    = -68,  /**< Could not program the SA flow*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA         = -69,  /**< Could not enable the SA*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA         = -70,  /**< Could not set SA to in use*/
    VTSS_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN   = -71,  /**< Invalid header bypass length*/
    VTSS_RC_ERR_MACSEC_SC_NOT_FOUND             = -72,  /**< Could not find SC (from sci)*/
    VTSS_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH        = -73,  /**< No control frame match*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN    = -74,  /**< Could no set bypass pattern for CP rule*/
    VTSS_RC_ERR_MACSEC_TIMEOUT_ISSUE            = -75,  /**< Internal timeout issue, bailing out*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS   = -76,  /**< Could not empty the egress pipeline*/
    VTSS_RC_ERR_MACSEC_AN_NOT_CREATED           = -77,  /**< AN not created.*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS  = -78,  /**< Could not empty the ingress pipeline*/
    VTSS_RC_ERR_MACSEC_TX_SC_NOT_EXIST          = -80,  /**< No tx SC found*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA     = -81,  /**< Could not disable sa*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA      = -82,  /**< Could not delete rx sa*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA      = -83,  /**< Could not delete tx sa*/
    VTSS_RC_ERR_MACSEC_PATTERN_NOT_SET          = -84,  /**< Pattern not set*/
    VTSS_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED     = -85,  /**< HW resources exhausted*/
    VTSS_RC_ERR_MACSEC_SCI_ALREADY_EXISTS       = -86,  /**< SCI already exists*/
    VTSS_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND    = -87,  /**< Could not find SC resources*/
    VTSS_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE     = -88,  /**< Rx AN is in use*/
    VTSS_RC_ERR_MACSEC_EMPTY_RECORD             = -89,  /**< Could not get an empty record*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM      = -90,  /**< Could not program the xform record*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA      = -91,  /**< Could not toggle SA*/
    VTSS_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE     = -92,  /**< Tx AN is in use*/
    VTSS_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE  = -93,  /**< All available SA's are in use*/
    VTSS_RC_ERR_MACSEC_MATCH_DISABLE            = -94,  /**< MACSEC match disabled*/
    VTSS_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE      = -95,  /**< All CP rules of the specific type are in use*/
    VTSS_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID   = -96,  /**< The pattern priority is not valid*/
    VTSS_RC_ERR_MACSEC_BUFFER_TOO_SMALL         = -97,  /**< Buffer to small, must be greater than VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX*/
    VTSS_RC_ERR_MACSEC_FRAME_TOO_LONG           = -98,  /**< Frame length is supposed to be less than the amount of data in the fifo*/
    VTSS_RC_ERR_MACSEC_FRAME_TRUNCATED          = -99,  /**< Frame is Truncated*/
    VTSS_RC_ERR_MACSEC_PHY_POWERED_DOWN         = -100, /**< Phy is powered down, i.e. the MacSec block is not accessible*/
    VTSS_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE   = -101, /**< Port/Phy is not MacSec capable*/
    VTSS_RC_ERR_MACSEC_AN_NOT_EXIST             = -102, /**< AN does not exist*/
    VTSS_RC_ERR_MACSEC_NO_PATTERN_CFG           = -103, /**< No pattern is configured*/
    VTSS_RC_ERR_MACSEC_MAX_MTU                  = -105, /**< Maximum MTU allowed is 32761 (+ 4 bytes for VLAN)*/
    VTSS_RC_ERR_MACSEC_UNEXPECT_CP_MODE         = -106, /**< Unexpected CP mode*/
    VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN     = -107, /**< Could not disable AN*/
    VTSS_RC_ERR_MACSEC_RULE_OUT_OF_RANGE        = -108, /**< Rule id is out of range. Must not be larger than VTSS_MACSEC_CP_RULES*/
    VTSS_RC_ERR_MACSEC_RULE_NOT_EXIST           = -109, /**< Rule does not exist*/
    VTSS_RC_ERR_MACSEC_CSR_READ                 = -110, /**< Could not do CSR read*/
    VTSS_RC_ERR_MACSEC_CSR_WRITE                = -111, /**< Could not do CSR write*/
    VTSS_RC_ERR_PHY_6G_RCPLL_ON_BASE_PORT_ONLY  = -112, /**< PHY API 6G RC-PLL status support only on Base port */


    /**** MISC ERRORS ****/
    VTSS_RC_ERR_INVALID_NULL_PTR                = -200, /**< A pointer was unexpected NULL */

    /*** Clause 37 ERRORS ***/
    VTSS_RC_ERR_PCS_BLOCK_NOT_SUPPORTED         = -300 /**< Invalid access to PCS block */
}; // Leave it anonymous.

/** \brief Chip number used for targets with multiple chips */
typedef u32 vtss_chip_no_t;

/** \brief Instance identifier */
typedef struct vtss_state_s *vtss_inst_t;

/**
 * \brief Description: Event type.
 * When a variable of this type is used as an input parameter, the API will set the variable if the event has occured.
 * The API will never clear the variable. If is up to the application to clear the variable, when the event has been handled.
 **/
typedef BOOL vtss_event_t;

/** \brief Port Number */
typedef u32 vtss_port_no_t;

#define VTSS_PORT_ARRAY_SIZE VTSS_PORTS
#define VTSS_PORT_NO_START   (0)          /**< Port start number */
#define VTSS_PORT_NO_END     (VTSS_PORT_NO_START+VTSS_PORTS) /**< Port end number */
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_PORT_NO_NONE    (0xffffffff) /**< Port number none */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief VLAN Identifier */
typedef mepa_vid_t vtss_vid_t; /* 0-4095 */

typedef mepa_mac_t vtss_mac_t;

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_MAC_ADDR_SZ_BYTES    6                 /**< Number of bytes for representing MAC address (SMAC/DMAC) type */
#endif // _VTSS_MAIN_TYPES_H_
typedef u8 vtss_mac_addr_t[VTSS_MAC_ADDR_SZ_BYTES]; /**< MAC address (SMAC/DMAC) */

#define MAC_ADDR_BROADCAST {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}  /**< Broadcast address used for addr in the vtss_mac_t struct */

/** \brief Ethernet Type **/
typedef mepa_etype_t vtss_etype_t;

/** \brief The different interfaces for connecting MAC and PHY */
typedef enum
{
    VTSS_PORT_INTERFACE_NO_CONNECTION, /**< No connection */
    VTSS_PORT_INTERFACE_LOOPBACK,      /**< Internal loopback in MAC */
    VTSS_PORT_INTERFACE_INTERNAL,      /**< Internal interface */
    VTSS_PORT_INTERFACE_MII,           /**< MII (RMII does not exist) */
    VTSS_PORT_INTERFACE_GMII,          /**< GMII */
    VTSS_PORT_INTERFACE_RGMII,         /**< RGMII */
    VTSS_PORT_INTERFACE_RGMII_ID,      /**< RGMII */
    VTSS_PORT_INTERFACE_RGMII_RXID,    /**< RGMII */
    VTSS_PORT_INTERFACE_RGMII_TXID,    /**< RGMII */
    VTSS_PORT_INTERFACE_TBI,           /**< TBI */
    VTSS_PORT_INTERFACE_RTBI,          /**< RTBI */
    VTSS_PORT_INTERFACE_SGMII,         /**< SGMII */
    VTSS_PORT_INTERFACE_SGMII_2G5,     /**< SGMII, 2G5 */
    VTSS_PORT_INTERFACE_SGMII_CISCO,   /**< SGMII using Cisco aneg  */
    VTSS_PORT_INTERFACE_SERDES,        /**< SERDES 1G,2G5. 8B/10B PCS */
    VTSS_PORT_INTERFACE_VAUI,          /**< VAUI 2G5 */
    VTSS_PORT_INTERFACE_100FX,         /**< 100FX */
    VTSS_PORT_INTERFACE_XAUI,          /**< XAUI */
    VTSS_PORT_INTERFACE_RXAUI,         /**< RXAUI */
    VTSS_PORT_INTERFACE_XGMII,         /**< XGMII */
    VTSS_PORT_INTERFACE_SPI4,          /**< SPI4 */
    VTSS_PORT_INTERFACE_QSGMII,        /**< QSGMII */
    VTSS_PORT_INTERFACE_SFI,           /**< SFI/LAN, 5G-25G, 64B/66B PCS */
    VTSS_PORT_INTERFACE_SXGMII,        /**< 1x10G or 1x5G device.    Uses primary device. 64B/66B PCS. Experimental unsupported mode!  */
    VTSS_PORT_INTERFACE_USGMII,        /**< 8x2G5 devices. Mode 'X'. Uses 2G5 device. Experimental unsupported mode!  */
    VTSS_PORT_INTERFACE_QXGMII,        /**< 4x2G5 devices. Mode 'R'. Uses 2G5 device.    */
    VTSS_PORT_INTERFACE_DXGMII_5G,     /**< 2x2G5 devices. Mode 'F'. Uses 2G5 device. Experimental unsupported mode!  */
    VTSS_PORT_INTERFACE_DXGMII_10G,    /**< 2x5G devices.  Mode 'U'. Uses primary device. Experimental unsupported mode!  */
    VTSS_PORT_INTERFACE_CPU,           /**< Exposed CPU port. Not connected to switch */
} vtss_port_interface_t;

/** \brief Serdes macro mode */
typedef enum
{
    VTSS_SERDES_MODE_DISABLE,   /**< Disable serdes */
    VTSS_SERDES_MODE_XAUI_12G,  /**< XAUI 12G mode  */
    VTSS_SERDES_MODE_XAUI,      /**< XAUI 10G mode  */
    VTSS_SERDES_MODE_RXAUI,     /**< RXAUI 10G mode */
    VTSS_SERDES_MODE_RXAUI_12G, /**< RXAUI 12G mode */
    VTSS_SERDES_MODE_2G5,       /**< 2.5G mode      */
    VTSS_SERDES_MODE_QSGMII,    /**< QSGMII mode    */
    VTSS_SERDES_MODE_SGMII,     /**< SGMII mode     */
    VTSS_SERDES_MODE_100FX,     /**< 100FX mode     */
    VTSS_SERDES_MODE_1000BaseX, /**< 1000BaseX mode */
    VTSS_SERDES_MODE_SFI,       /**< LAN/10G mode   */
    VTSS_SERDES_MODE_SFI_DAC,   /**< LAN/10G DAC(CU)*/
    VTSS_SERDES_MODE_SFI_SR,    /**< Short Range > */
    VTSS_SERDES_MODE_SFI_ZR,    /**< ZR with APC hardware algorithm > */
    VTSS_SERDES_MODE_SFI_BP,    /**< Backplane > */
    VTSS_SERDES_MODE_SFI_B2B,   /**< Bord to Board > */
    VTSS_SERDES_MODE_SFI_KR,    /**< 10G KR        > */
    VTSS_SERDES_MODE_SFI_PR_NONE, /**< No preset > */
    VTSS_SERDES_MODE_IDLE,      /**< Send idles (port appears as down for LP) */
    VTSS_SERDES_MODE_TEST_MODE, /**< Send fixed test pattern (port appears as up for LP, but no frame rx/tx) */
    VTSS_SERDES_MODE_USXGMII,   /**< 1 x USXGMII in 5G/10G mode */
    VTSS_SERDES_MODE_USGMII,    /**< 8 x USGMII in 1G mode */
    VTSS_SERDES_MODE_QXGMII,    /**< 4 x QXGMII in 2G5 mode.     Mode 'R'  */
    VTSS_SERDES_MODE_DXGMII_10G,/**< 2 x DXGMII_10G in 5G mode.  Mode 'U'  */
    VTSS_SERDES_MODE_DXGMII_5G  /**< 2 x DXGMII_5G in 2G5 mode.  Mode 'F'  */

} vtss_serdes_mode_t;

/** \brief Auto negotiation struct */
typedef struct
{
    BOOL obey_pause;               /**< This port should obey PAUSE frames */
    BOOL generate_pause;           /**< Link partner obeys PAUSE frames */
} vtss_aneg_t;                     /**< Auto negotiation result */

/** \brief Port speed */
typedef enum
{
    VTSS_SPEED_UNDEFINED,   /**< Undefined */
    VTSS_SPEED_10M,         /**< 10 M */
    VTSS_SPEED_100M,        /**< 100 M */
    VTSS_SPEED_1G,          /**< 1 G */
    VTSS_SPEED_2500M,       /**< 2.5G */
    VTSS_SPEED_5G,          /**< 5G or 2x2.5G */
    VTSS_SPEED_10G,         /**< 10 G */
    VTSS_SPEED_12G,         /**< 12G */
    VTSS_SPEED_25G,         /**< 25G */
    VTSS_SPEED_AUTO
} vtss_port_speed_t;

/** \brief Port status parameter struct */
typedef struct
{
    vtss_event_t      link_down;       /**< Link down event occurred since last call */
    BOOL              link;            /**< Link is up. Remaining fields only valid if TRUE */
    vtss_port_speed_t speed;           /**< Speed */
    BOOL              fdx;             /**< Full duplex */
    BOOL              remote_fault;    /**< Remote fault signalled */
    BOOL              aneg_complete;   /**< Autoneg completed (for clause_37 and Cisco aneg) */
    BOOL              unidirectional_ability; /**<TRUE: PHY able to transmit from media independent interface regardless of whether the PHY has
                                                 determined that a valid link has been established.FALSE: PHY able to transmit from media
                                                 independent interface only when the PHY has determined that a valid link has been established.
                                                 Note This bit is only applicable to 100BASE-FX and 1000BASE-X fiber media modes.*/
    vtss_aneg_t aneg;                  /**< Auto negotiation result */
    BOOL mdi_cross;                    /**< Indication of if Auto-MDIX crossover is performed */
    BOOL fiber;                        /**< Indication of if the link is a fiber link, TRUE if link is a fiber link. FALSE if link is cu link or No Media */
    BOOL copper;                       /**< Indication of if the link is a copper link, TRUE if link is a copper link. FALSE if link is fiber link or No Media */
} vtss_port_status_t;

#define VTSS_PHY_POWER_ACTIPHY_BIT 0 /**< Defines the bit used to signaling that ActiPhy is enabled */
#define VTSS_PHY_POWER_DYNAMIC_BIT 1 /**< Defines the bit used to signaling that PerfectReach is enabled */

/** \brief PHY power reduction modes */
typedef enum {
    VTSS_PHY_POWER_NOMINAL = 0, /**< Default power settings */
    VTSS_PHY_POWER_ACTIPHY = 1 << VTSS_PHY_POWER_ACTIPHY_BIT, /**< ActiPHY - Link down power savings enabled (Bit 0) */
    VTSS_PHY_POWER_DYNAMIC = 1 << VTSS_PHY_POWER_DYNAMIC_BIT, /**< PerfectReach - Link up power savings enabled (Bit 1) */
    VTSS_PHY_POWER_ENABLED = VTSS_PHY_POWER_ACTIPHY +  VTSS_PHY_POWER_DYNAMIC /**< ActiPHY + PerfectReach enabled */
} vtss_phy_power_mode_t;

/** \brief VeriPHY status */
typedef enum {
    VTSS_VERIPHY_STATUS_OK      = 0,  /**< Correctly terminated pair */
    VTSS_VERIPHY_STATUS_OPEN    = 1,  /**< Open pair */
    VTSS_VERIPHY_STATUS_SHORT   = 2,  /**< Short pair */
    VTSS_VERIPHY_STATUS_ABNORM  = 4,  /**< Abnormal termination */
    VTSS_VERIPHY_STATUS_SHORT_A = 8,  /**< Cross-pair short to pair A */
    VTSS_VERIPHY_STATUS_SHORT_B = 9,  /**< Cross-pair short to pair B */
    VTSS_VERIPHY_STATUS_SHORT_C = 10, /**< Cross-pair short to pair C */
    VTSS_VERIPHY_STATUS_SHORT_D = 11, /**< Cross-pair short to pair D */
    VTSS_VERIPHY_STATUS_COUPL_A = 12, /**< Abnormal cross-pair coupling, pair A */
    VTSS_VERIPHY_STATUS_COUPL_B = 13, /**< Abnormal cross-pair coupling, pair B */
    VTSS_VERIPHY_STATUS_COUPL_C = 14, /**< Abnormal cross-pair coupling, pair C */
    VTSS_VERIPHY_STATUS_COUPL_D = 15, /**< Abnormal cross-pair coupling, pair D */
    VTSS_VERIPHY_STATUS_UNKNOWN = 16, /**< Unknown - VeriPhy never started ? */
    VTSS_VERIPHY_STATUS_RUNNING = 17  /**< VeriPhy is still running - No result yet */
} vtss_phy_veriphy_status_t;

/**
 * \brief Time interval in ns * 1<<16
 * range +-2**47 ns = 140737 sec = 39 hours
 * For example, 2.5 ns is expressed as 0x0000.0000.0002.8000
 */
typedef i64 vtss_timeinterval_t;

struct mepa_callout;
typedef struct mepa_callout mepa_callout_t;

struct mepa_callout_ctx;
typedef struct mepa_callout_ctx mepa_callout_ctx_t;

/** \brief Create PHY instance */
vtss_rc vtss_phy_inst_create(const mepa_callout_t    *callout,
                             struct mepa_callout_ctx *callout_ctx,
                             vtss_inst_t *const inst);

/** \brief Destroy PHY instance */
vtss_rc vtss_phy_inst_destroy(const mepa_callout_t    *callout,
                              struct mepa_callout_ctx *callout_ctx,
                              const vtss_inst_t inst);

/** \brief Debug layer */
/* Debug layer */
typedef enum {
    VTSS_DEBUG_LAYER_ALL, /**< All layers */
    VTSS_DEBUG_LAYER_AIL, /**< Application Interface Layer */
    VTSS_DEBUG_LAYER_CIL  /**< Chip Interface Layer */
} vtss_debug_layer_t;

/** \brief Debug function group */
typedef enum {
    VTSS_DEBUG_GROUP_ALL,       /**< All groups */
    VTSS_DEBUG_GROUP_PHY,       /**< PHY */
    VTSS_DEBUG_GROUP_PHY_TS,    /**< PHY_TS: PHY TimeStamping */
    VTSS_DEBUG_GROUP_MACSEC,    /**< 802.1AE MacSec */

    /* New groups are added above this line */
    VTSS_DEBUG_GROUP_COUNT      /**< Number of groups */
} vtss_debug_group_t;

/** \brief Debug information structure */
typedef struct {
    vtss_debug_layer_t           layer;                           /**< Layer */
    vtss_debug_group_t           group;                           /**< Function group */
    BOOL                         port_list[VTSS_PORT_ARRAY_SIZE]; /**< Port list */
    BOOL                         full;                            /**< Full information dump */
    BOOL                         clear;                           /**< Clear counters */
    BOOL                         vml_format;                      /**< VML format register dump */
} vtss_debug_info_t;

/** \brief Attribute */
#if defined(__GNUC__) && (__GNUC__ > 2)
#define VTSS_ATTR_PRINTF(X, Y) __attribute__ ((format(printf,X,Y)))
#else
#define VTSS_ATTR_PRINTF(X, Y)
#endif

/** \brief Debug printf function
 *
 * The signature is similar to that of printf(). However, the return value is
 * not used anywhere within the API.
 */
typedef int (*vtss_debug_printf_t)(const char *fmt, ...) VTSS_ATTR_PRINTF(1, 2);

/**
 * \brief Print default information
 *
 * \param inst [IN]   Target instance reference.
 * \param prntf [IN]  Debug printf function.
 * \param info [IN]   Debug information
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_debug_info_print(const vtss_inst_t         inst,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
/**
 * \brief SPI read/write function
 *
 * \param inst [IN] Vitesse API instance.
 * \param port_no [IN] Port number.
 * \param bitsize [IN] Size (in bytes) of bitstream following this parameter.
 * \param data [IN|OUT] Pointer to the data to be written to SPI Slave, if doing write operation.
 *                      Pointer to the data read from SPI Slave, if doing read operation.
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_spi_read_write_t)(const vtss_inst_t inst,
                                         const vtss_port_no_t port_no,
                                         const u8 bitsize,
                                         u8 *const bitstream);

/**
 * \brief SPI 32 bit read/write function
 *
 * \param inst    [IN] Vitesse API instance.
 * \param port_no [IN] Port number.
 * \param read    [IN] Read/Write.
 * \param dev     [IN] MMD device number.
 * \param reg_num [IN] Register offset.
 * \param data [IN|OUT] Pointer to the data to be written to SPI Slave, if doing write operation.
 *                      Pointer to the data read from SPI Slave, if doing read operation.
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_spi_32bit_read_write_t)(const vtss_inst_t inst,
                                               vtss_port_no_t port_no,
                                               BOOL           read,
                                               u8             dev,
                                               u16            reg_num,
                                               u32            *const data);

/**
 * \brief SPI 64 bit read/write function
 *
 * \param inst    [IN] Vitesse API instance.
 * \param port_no [IN] Port number.
 * \param read    [IN] Read/Write.
 * \param dev     [IN] MMD device number.
 * \param reg_num [IN] Register offset.
 * \param data [IN|OUT] Pointer to the data to be written to SPI Slave, if doing write operation.
 *                      Pointer to the data read from SPI Slave, if doing read operation.
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_spi_64bit_read_write_t)(const vtss_inst_t inst,
                                               vtss_port_no_t port_no,
                                               BOOL           read,
                                               u8             dev,
                                               u16            reg_num,
                                               u64            *const data);

/**
 * \brief MII management read function (IEEE 802.3 clause 22)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param addr [IN]    Register address (0-31)
 * \param value [OUT]  Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_miim_read_t)(const vtss_inst_t    inst,
                                    const vtss_port_no_t port_no,
                                    const u8             addr,
                                    u16                  *const value);

/**
 * \brief MII management write function (IEEE 802.3 clause 22)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param addr [IN]    Register address (0-31)
 * \param value [IN]   Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_miim_write_t)(const vtss_inst_t    inst,
                                     const vtss_port_no_t port_no,
                                     const u8             addr,
                                     const u16            value);

/**
 * \brief MMD management read function (IEEE 802.3 clause 45)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param mmd [IN]     MMD address (0-31)
 * \param addr [IN]    Register address (0-65535)
 * \param value [OUT]  Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_mmd_read_t)(const vtss_inst_t    inst,
                                   const vtss_port_no_t port_no,
                                   const u8             mmd,
                                   const u16            addr,
                                   u16                  *const value);

/**
 * \brief MMD management read increment function (IEEE 802.3 clause 45)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param mmd [IN]     MMD address (0-31)
 * \param addr [IN]    Start register address (0-65535)
 * \param buf [OUT]    The register values (pointer provided by user)
 * \param count [IN]   Number of register reads (increment register reads)
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_mmd_read_inc_t)(const vtss_inst_t    inst,
                                       const vtss_port_no_t port_no,
                                       const u8             mmd,
                                       const u16            addr,
                                       u16                  *const buf,
                                       u8                   count);

/**
 * \brief MMD management write function (IEEE 802.3 clause 45)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param mmd [IN]     MMD address (0-31)
 * \param addr [IN]    Start register address (0-65535)
 * \param buf [IN]     The register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_mmd_write_t)(const vtss_inst_t    inst,
                                    const vtss_port_no_t port_no,
                                    const u8             mmd,
                                    const u16            addr,
                                    const u16            value);

#if defined(VTSS_FEATURE_WARM_START)
/** \brief Restart information source */
typedef enum {
    VTSS_RESTART_INFO_SRC_NONE,   /* Restart information not stored in PHYs */
    VTSS_RESTART_INFO_SRC_CU_PHY, /* Restart information stored in 1G PHY */
    VTSS_RESTART_INFO_SRC_10G_PHY /* Restart information stored in 10G PHY */
} vtss_restart_info_src_t;
#endif /* VTSS_FEATURE_WARM_START */

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
/** \brief VDD power supply */
typedef enum {
    VTSS_VDD_1V0,               /**< 1.0V (default) */
    VTSS_VDD_1V2,               /**< 1.2V */
} vtss_vdd_t;

/** \brief Serdes fields */
typedef struct {
    u32        ob_post0;                  /**< Trace length */
    u32        ob_sr;                     /**< Slew Rate */
} vtss_serdes_fields_t;

/** \brief Backward compatibility */
typedef vtss_serdes_fields_t serdes_fields_t;

/** \brief Serdes macro configuration */
typedef struct {
    vtss_vdd_t           serdes1g_vdd; /**< Serdes1g supply */
    vtss_vdd_t           serdes6g_vdd; /**< Serdes6g supply */
    BOOL                 ib_cterm_ena; /**< AC(0)/DC(1) coupled */
    vtss_serdes_fields_t qsgmii;       /**< Appl/Board specific fields for QSGMII */
} vtss_serdes_macro_conf_t;
#endif /* VTSS_FEATURE_SERDES_MACRO_SETTINGS */

// API lock/unlock callback passed by application
typedef mepa_lock_t vtss_phy_lock_t;
typedef mepa_lock_func_t vtss_phy_lock_func_t;

/** \brief Trace groups */
typedef enum
{
    VTSS_PHY_TRACE_GROUP_DEFAULT,       /**< Default trace group */
    VTSS_PHY_TRACE_GROUP_TS,            /**< Timestamping */

    VTSS_PHY_TRACE_GROUP_COUNT          /**< Number of trace groups */
} vtss_phy_trace_group_t;

/** \brief Trace levels */
typedef enum
{
    VTSS_PHY_TRACE_LEVEL_NONE,  /**< No trace */
    VTSS_PHY_TRACE_LEVEL_ERROR, /**< Error trace */
    VTSS_PHY_TRACE_LEVEL_INFO,  /**< Information trace */
    VTSS_PHY_TRACE_LEVEL_DEBUG, /**< Debug trace */
    VTSS_PHY_TRACE_LEVEL_NOISE, /**< More debug information */

    VTSS_PHY_TRACE_LEVEL_COUNT  /**< Number of trace levels */
} vtss_phy_trace_level_t;

// API trace function
typedef void (*vtss_phy_trace_func_t)(const vtss_phy_trace_group_t group,
                                      const vtss_phy_trace_level_t level,
                                      const char                   *location,
                                      const int                    line,
                                      const char                   *format,
                                      ...);

/** \brief Initialization configuration. */
typedef struct {
    vtss_miim_read_t         miim_read;         /**< MII management read function */
    vtss_miim_write_t        miim_write;        /**< MII management write function */
    vtss_mmd_read_t          mmd_read;          /**< MMD management read function */
    vtss_mmd_read_inc_t      mmd_read_inc;      /**< MMD management read increment function */
    vtss_mmd_write_t         mmd_write;         /**< MMD management write function */
    vtss_spi_read_write_t    spi_read_write;    /**< Board specific SPI read/write callout function */
    vtss_spi_32bit_read_write_t spi_32bit_read_write; /**< Board specific SPI read/write callout function for 32 bit data */
    vtss_spi_64bit_read_write_t spi_64bit_read_write; /**< Board specific SPI read/write callout function for 64 bit data*/
#if defined(VTSS_FEATURE_WARM_START)
    BOOL                     warm_start_enable; /**< Allow warm start */
    vtss_restart_info_src_t  restart_info_src;  /**< Source of restart information */
    vtss_port_no_t           restart_info_port; /**< Port used to store PHY restart information */
#endif /* VTSS_FEATURE_WARM_START */
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    vtss_serdes_macro_conf_t serdes;            /**< Serdes macro configuration */
#endif /* VTSS_FEATURE_SERDES_MACRO_SETTINGS */
    vtss_phy_lock_func_t     lock_enter;
    vtss_phy_lock_func_t     lock_exit;
    vtss_phy_trace_func_t    trace_func;
} vtss_phy_init_conf_t;

/** \brief Get default init configuration */
vtss_rc vtss_phy_init_conf_get(const vtss_inst_t inst,
                               vtss_phy_init_conf_t  *const conf);

/** \brief Set default init configuration */
vtss_rc vtss_phy_init_conf_set(const vtss_inst_t      inst,
                               const vtss_phy_init_conf_t *const conf);

/** \brief API version */
typedef u16 vtss_version_t;

/** \brief Restart type */
typedef enum {
    VTSS_RESTART_COLD, /**< Cold: Chip and CPU restart, e.g. power cycling */
    VTSS_RESTART_COOL, /**< Cool: Chip and CPU restart done by CPU */
    VTSS_RESTART_WARM  /**< Warm: CPU restart only */
} vtss_restart_t;

#endif /* _VTSS_PHY_TYPES_H_ */
