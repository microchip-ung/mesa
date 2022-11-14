// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief Generic types API
 * \details This header file describes generic types used in the API
 */

#ifndef _VTSS_API_TYPES_H_
#define _VTSS_API_TYPES_H_

#include <vtss/api/options.h>
#include <vtss_os.h>            /* This defines the *runtime* OS environment */

// TODO, all the _VTSS_MAIN_TYPES_H_ needs to be deleted then the API split is
// complete
#ifndef _VTSS_MAIN_TYPES_H_

/** \brief Max/min values for 64 signed integer */
#define VTSS_I64_MAX  0x7FFFFFFFFFFFFFFFLL  /**<  Max value for 64 bit signed integer */
#define VTSS_I64_MIN -0x8000000000000000LL  /**<  Min value for 64 bit signed integer */
#endif // _VTSS_MAIN_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _VTSS_MAIN_TYPES_H_
/* Formatting defaults if no inttypes available */
#if __INTPTR_MAX__ == __INT32_MAX__
#    if !defined(PRIu64)
#        define PRIu64 "llu"           /**< Fallback un-signed 64-bit formatting string */
#    endif

#    if !defined(PRIi64)
#        define PRIi64 "lli"           /**< Fallback signed 64-bit formatting string */
#    endif

#    if !defined(PRIx64)
#        define PRIx64 "llx"           /**< Fallback hex 64-bit formatting string */
#    endif

#elif __INTPTR_MAX__ == __INT64_MAX__
#    if !defined(PRIu64)
#        define PRIu64 "lu"           /**< Fallback un-signed 64-bit formatting string */
#    endif

#    if !defined(PRIi64)
#        define PRIi64 "li"           /**< Fallback signed 64-bit formatting string */
#    endif

#    if !defined(PRIx64)
#        define PRIx64 "lx"           /**< Fallback hex 64-bit formatting string */
#    endif
#else
#    error "Environment not 32 or 64-bit."
#endif

#define VTSS_BIT64(x)                  (1ULL << (x))                           /**< Set one bit in a 64-bit mask               */
#define VTSS_BITMASK64(x)              ((1ULL << (x)) - 1)                     /**< Get a bitmask consisting of x ones         */
#define VTSS_EXTRACT_BITFIELD64(x,o,w) (((x) >> (o)) & VTSS_BITMASK64(w))      /**< Extract w bits from bit position o in x    */
#define VTSS_ENCODE_BITFIELD64(x,o,w)  (((u64)(x) & VTSS_BITMASK64(w)) << (o)) /**< Place w bits of x at bit position o        */
#define VTSS_ENCODE_BITMASK64(o,w)     (VTSS_BITMASK64(w) << (o))              /**< Create a bitmask of w bits positioned at o */

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
#endif // _VTSS_MAIN_TYPES_H_

/****************************************************************************
 * Common types
 ****************************************************************************/
/** \brief Chip number used for targets with multiple chips */
typedef u32 vtss_chip_no_t;

/** \brief Instance identifier */
typedef struct vtss_state_s *vtss_inst_t;

/**
 * \brief Description: Event type.
 * When a variable of this type is used as an input parameter, the API will set the variable if the event has occured.
 * The API will never clear the variable. If is up to the application to clear the variable, when the event has been handled.
 **/
#ifndef _VTSS_MAIN_TYPES_H_
typedef BOOL vtss_event_t;
#endif // _VTSS_MAIN_TYPES_H_

/** \brief Policer packet rate in PPS */
typedef u32 vtss_packet_rate_t;

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_PACKET_RATE_DISABLED 0xffffffff /**< Special value for disabling packet policer */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief Port Number */
typedef u32 vtss_port_no_t;

/** \brief Physical port number */
typedef u32 vtss_phys_port_no_t;

/**
 * \brief Memory allocation flags.
 *
 * The VTSS API asks the application to
 * allocate dynamic memory for its internal structures
 * through calls to VTSS_OS_MALLOC().
 *
 * The application should normally just associate
 * this with a call to malloc() or kmalloc()
 * depending on the OS and the runtime model (API running
 * in Kernel or User space).
 *
 * However, on some OSs, it's required to allocate
 * specially if the memory is going to be associated
 * with DMA, hence the VTSS_MEM_FLAGS_DMA enumeration.
 *
 * Also, to be able to support warm restart, another
 * enumeration, VTSS_MEM_FLAGS_PERSIST, tells
 * the application to allocate the memory in a part
 * of RAM that won't be affected by a subsequent boot.
 *
 * VTSS_OS_MALLOC() must not block or make waiting points
 * if called with flags != VTSS_MEM_FLAGS_NONE.
 *
 * Each of the enumerations are ORed together to form
 * the final flags that are used in a call to VTSS_OS_MALLOC().
 *
 * The same set of flags are used in calls to VTSS_OS_FREE().
 */
typedef enum {
    VTSS_MEM_FLAGS_NONE    = 0x0, /**< Allocate normally according to runtime model (User or Kernel space). */
    VTSS_MEM_FLAGS_DMA     = 0x1, /**< Allocate memory that can be used with a DMA.                         */
    VTSS_MEM_FLAGS_PERSIST = 0x2, /**< Allocate memory that will survive a warm restart.                    */
} vtss_mem_flags_t;

#define VTSS_PORT_COUNT 1 /**< Default number of ports */

#if defined(VTSS_CHIP_SERVAL_LITE) || defined(VTSS_CHIP_CARACAL_LITE)
#if (VTSS_PORT_COUNT < 7)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 7 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 7 */
#endif /* SERVAL_LITE/CARACAL_LITE */

#if defined(VTSS_CHIP_7513)
#if (VTSS_PORT_COUNT < 9)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 9 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 9 */
#endif /* 7513 */

#if defined(VTSS_CHIP_SPARX_III_10) || defined(VTSS_CHIP_SPARX_III_10_UM) || \
    defined(VTSS_CHIP_SPARX_III_10_01)
#if (VTSS_PORT_COUNT < 10)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 10 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 10 */
#endif /* SPARX_III_10 */

#if defined(VTSS_CHIP_7511)
#if (VTSS_PORT_COUNT < 4)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 4 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 4 */
#endif /* 7511 */

#if defined(VTSS_CHIP_CARACAL_1) || defined(VTSS_CHIP_SERVAL) || \
    defined(VTSS_CHIP_SPARX_III_11) || defined(VTSS_CHIP_7512) || defined(VTSS_CHIP_7514)
#if (VTSS_PORT_COUNT < 11)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 11 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 11 */
#endif /* CARACAL_1/SERVAL/7514 */

#if defined(VTSS_CHIP_SPARX_III_17_UM)
#if (VTSS_PORT_COUNT < 17)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 17 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 17 */
#endif /* SPARX_III_17_UM */

#if defined(VTSS_CHIP_SPARX_III_18)
#if (VTSS_PORT_COUNT < 18)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 18 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 18 */
#endif /* SPARX_III_18 */

#if defined(VTSS_CHIP_SPARX_III_24)
#if (VTSS_PORT_COUNT < 24)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 24 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 24 */
#endif /* SPARX_III_24 */

#if defined(VTSS_CHIP_SPARX_III_25_UM)
#if (VTSS_PORT_COUNT < 25)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 25 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 25 */
#endif /* SPARX_III_25_UM */

#if defined(VTSS_CHIP_SPARX_III_26) || defined(VTSS_CHIP_CARACAL_2)
#if (VTSS_PORT_COUNT < 26)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 26 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 26 */
#endif /* SPARX_III_26 */

#if defined(VTSS_CHIP_SERVAL_2)
/* 12x1G + 2x10G + NPI */
#if (VTSS_PORT_COUNT < 15)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 15 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 15 */
#endif /* VTSS_CHIP_SERVAL_2 */

#if defined(VTSS_CHIP_LYNX_2) || defined(VTSS_CHIP_SPARX_IV_44)
/* 24x1G + 2x10G + NPI */
#if (VTSS_PORT_COUNT < 27)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 27 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 27 */
#endif /* VTSS_CHIP_LYNX_2/SPARX_IV_44 */

#if defined(VTSS_CHIP_JAGUAR_2) || defined(VTSS_CHIP_SPARX_IV_52) || defined(VTSS_CHIP_SPARX_IV_80) || defined(VTSS_CHIP_SPARX_IV_90)
/* 48x1G + 4x1G + NPI */
#if (VTSS_PORT_COUNT < 53)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 53 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 53 */
#endif /* VTSS_CHIP_JAGUAR_2/SPARX_IV_52/SPARX_IV_80/SPARX_IV_90 */

#if defined(VTSS_CHIP_SERVAL_T) || defined(VTSS_CHIP_SERVAL_TP) || defined(VTSS_CHIP_SERVAL_TE) || defined(VTSS_CHIP_SERVAL_TEP)
/* 4x1G + 2x2.5G + NPI */
#if (VTSS_PORT_COUNT < 7)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 7 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 7 */
#endif /* VTSS_CHIP_SERVAL_T/SERVAL_TE */

#if defined(VTSS_CHIP_SERVAL_2_LITE) || defined(VTSS_CHIP_SPARX_IV_34)
/* 4x1G + 4x2.5G + 2x10G + NPI */
#if (VTSS_PORT_COUNT < 11)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 11 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 11 */
#endif /* VTSS_CHIP_SERVAL_2_LITE/SPARX_IV_34 */

#if defined(VTSS_CHIP_SERVAL_TE10)
/* 4x1G + 2x2.5G + 2x10G + NPI */
#if (VTSS_PORT_COUNT < 9)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 9 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 9 */
#endif /* VTSS_CHIP_SERVAL_TE10 */

#if defined(VTSS_ARCH_SPARX5)
#if (VTSS_PORT_COUNT < 65)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 65 /**< Number of ports */
#endif /* VTSS_PORT_COUNT < 65 */
#endif

#if defined(VTSS_CHIP_966X)
#if (VTSS_PORT_COUNT < 8)
#undef VTSS_PORT_COUNT
#define VTSS_PORT_COUNT 8 /**< Number of ports */
#endif
#endif

/* Number of ports may optionally be less than number of chip ports */
#if VTSS_OPT_PORT_COUNT && ((VTSS_PORT_COUNT == 1) || (VTSS_OPT_PORT_COUNT < VTSS_PORT_COUNT))
#define VTSS_PORTS VTSS_OPT_PORT_COUNT /**< Number of ports */
#else
#define VTSS_PORTS VTSS_PORT_COUNT     /**< Number of ports */
#endif /* VTSS_OPT_PORT_COUNT */

/* The first logical port number is 0. */
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_PORT_NO_NONE    (0xffffffff) /**< Port number none */
#define VTSS_PORT_NO_CPU     (0xfffffffe) /**< Port number for CPU for special purposes */
#define VTSS_PORT_NO_START   (0)          /**< Port start number */
#endif // _VTSS_MAIN_TYPES_H_
#define VTSS_PORT_NO_END     (VTSS_PORT_NO_START+VTSS_PORTS) /**< Port end number */
#define VTSS_PORT_ARRAY_SIZE VTSS_PORT_NO_END /**< Port number array size */

#define VTSS_PORT_IS_PORT(x) ((x)<VTSS_PORT_NO_END) /**< Valid port number */

/** \brief The different interfaces for connecting MAC and PHY */
typedef enum
{
    VTSS_PORT_INTERFACE_NO_CONNECTION, /**< No connection */
    VTSS_PORT_INTERFACE_LOOPBACK,      /**< Internal loopback in MAC */
    VTSS_PORT_INTERFACE_INTERNAL,      /**< Internal interface */
    VTSS_PORT_INTERFACE_MII,           /**< MII (RMII does not exist) */
    VTSS_PORT_INTERFACE_GMII,          /**< GMII */
    VTSS_PORT_INTERFACE_RGMII,         /**< RGMII with no internal delay */
    VTSS_PORT_INTERFACE_RGMII_ID,      /**< RGMII with 2ns internal RX+TX delay */
    VTSS_PORT_INTERFACE_RGMII_RXID,    /**< RGMII with 2ns internal RX delay */
    VTSS_PORT_INTERFACE_RGMII_TXID,    /**< RGMII with 2ns internal TX delay */
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


/** \brief Auto negotiation struct */
typedef struct
{
    BOOL obey_pause;               /**< This port should obey PAUSE frames */
    BOOL generate_pause;           /**< Link partner obeys PAUSE frames */
} vtss_aneg_t;                     /**< Auto negotiation result */

/** \brief Serdes macro mode */
typedef enum
{
    VTSS_SERDES_MODE_DISABLE,   /**< Disable serdes */
    VTSS_SERDES_MODE_NONE,      /**< No serdes connected */
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

/** \brief VOE index */
typedef u32 vtss_voe_idx_t;

#define VTSS_VOE_IDX_NONE 0xFFFFFFFF /**< Special value meaning no VOE */

/** \brief MIP (MIP) index */
typedef u32 vtss_voi_idx_t;

#define VTSS_VOI_IDX_NONE 0xFFFFFFFF /**< Special value meaning no VOI (MIP) */

// MRP index
typedef u32 vtss_mrp_idx_t;

#define VTSS_MRP_IDX_NONE 0xFFFFFFFF /**< Special value meaning no MRP */

/****************************************************************************
 * QoS types
 ****************************************************************************/
/** \brief Priority number */
typedef u32 vtss_prio_t;
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_PRIOS           8                              /**< Number of priorities */
#define VTSS_PRIO_NO_NONE    0xffffffff                     /**< Priority number none (= undefined) */
#define VTSS_PRIO_START      0                              /**< Priority start number (lowest) */
#define VTSS_PRIO_END        (VTSS_PRIO_START + VTSS_PRIOS) /**< Priority end number */
#define VTSS_PRIO_ARRAY_SIZE VTSS_PRIO_END                  /**< Priority number array size */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief Queue number */
typedef u32 vtss_queue_t;
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_QUEUES           VTSS_PRIOS                       /**< Number of queues */
#define VTSS_QUEUE_START      0                                /**< Queue start number */
#define VTSS_QUEUE_END        (VTSS_QUEUE_START + VTSS_QUEUES) /**< Queue end number */
#define VTSS_QUEUE_ARRAY_SIZE VTSS_QUEUE_END                   /**< Queue number array size */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief Tag Priority or Priority Code Point (PCP) */
typedef u32 vtss_tagprio_t;
/** \brief Priority Code Point (PCP) */
typedef u8  vtss_pcp_t;
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_PCPS           8                            /**< Number of PCP values */
#define VTSS_PCP_START      0                            /**< PCP start number */
#define VTSS_PCP_END        (VTSS_PCP_START + VTSS_PCPS) /**< PCP end number */
#define VTSS_PCP_ARRAY_SIZE VTSS_PCP_END                 /**< PCP array size */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief Drop Eligible Indicator (DEI) */
typedef BOOL vtss_dei_t;
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_DEIS           2                            /**< Number of DEI values */
#define VTSS_DEI_START      0                            /**< DEI start number */
#define VTSS_DEI_END        (VTSS_DEI_START + VTSS_DEIS) /**< DEI end number */
#define VTSS_DEI_ARRAY_SIZE VTSS_DEI_END                 /**< DEI array size */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief Drop Precedence Level (DPL) */
typedef u8 vtss_dp_level_t;
/** \brief Drop Precedence Level (DPL) */
typedef vtss_dp_level_t vtss_dpl_t;
#define VTSS_DPLS 2 /**< Default number of drop precedence levels */

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#undef VTSS_DPLS
#define VTSS_DPLS 4 /**< Number of drop precedence levels */
#endif /* defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) */

#define VTSS_DPL_START      0                            /**< DPL start number */
#define VTSS_DPL_END        (VTSS_DPL_START + VTSS_DPLS) /**< DPL end number */
#define VTSS_DPL_ARRAY_SIZE VTSS_DPL_END                 /**< DPL array size */

/** \brief Class of Service. Same as QoS class */
typedef u8 vtss_cos_t;

/** \brief Percentage, 0-100 */
typedef u8 vtss_pct_t;

/**
 * \brief Policer/Shaper bit rate in kbps (1000 bits per second).
 * The rate will be rounded to the nearest value supported by the chip
 **/
typedef u32 vtss_bitrate_t;
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_BITRATE_DISABLED 0xffffffff /**< Bitrate disabled */
#endif // _VTSS_MAIN_TYPES_H_

/**
 * \brief Policer/shaper burst level in bytes.
 * The level will be rounded to the nearest value supported by the chip
 **/
typedef u32 vtss_burst_level_t;

/** \brief Storm policer mode configuration */
typedef enum
{
    VTSS_STORM_POLICER_MODE_PORTS_AND_CPU, /**< Police both CPU and front port destinations */
    VTSS_STORM_POLICER_MODE_PORTS_ONLY,    /**< Police front port destinations only */
    VTSS_STORM_POLICER_MODE_CPU_ONLY       /**< Police CPU destination only */
} vtss_storm_policer_mode_t;

/** \brief DSCP value (0-63) */
typedef u8 vtss_dscp_t;

/** \brief QoS Control Entry ID */
typedef u32 vtss_qce_id_t;

/** \brief Dual leaky buckets policer configuration */
typedef enum
{
    VTSS_POLICER_TYPE_MEF,    /**< MEF bandwidth profile */
    VTSS_POLICER_TYPE_SINGLE  /**< Single bucket policer (CIR/CBS) */
} vtss_policer_type_t;

/** \brief EVC policer index */
typedef u16 vtss_evc_policer_id_t;

/** \brief WRED group number */
typedef u32 vtss_wred_group_t;

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_QOS_MAP_ID_NONE  0xfff                                                              /**< ID for unallocated/unused ingress or egress map */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief Ingress map ID */
typedef u16 vtss_qos_ingress_map_id_t;

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5)
#define VTSS_QOS_INGRESS_MAP_IDS      256                                                        /**< Number of IDs */
#else
#define VTSS_QOS_INGRESS_MAP_IDS      128                                                        /**< Number of IDs */
#endif /* defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) */

#define VTSS_QOS_INGRESS_MAP_ID_START 0                                                          /**< ID start number */
#define VTSS_QOS_INGRESS_MAP_ID_END   (VTSS_QOS_INGRESS_MAP_ID_START + VTSS_QOS_INGRESS_MAP_IDS) /**< ID end number */
#define VTSS_QOS_INGRESS_MAP_ID_NONE  VTSS_QOS_MAP_ID_NONE                                       /**< ID for unallocated/unused */

/** \brief Egress map ID */
typedef u16 vtss_qos_egress_map_id_t;

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5)
#define VTSS_QOS_EGRESS_MAP_IDS       512                                                        /**< Number of IDs */
#else
#define VTSS_QOS_EGRESS_MAP_IDS       256                                                        /**< Number of IDs */
#endif /* defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) */

#define VTSS_QOS_EGRESS_MAP_ID_START  0                                                          /**< ID start number */
#define VTSS_QOS_EGRESS_MAP_ID_END    (VTSS_QOS_EGRESS_MAP_ID_START + VTSS_QOS_EGRESS_MAP_IDS)   /**< ID end number */
#define VTSS_QOS_EGRESS_MAP_ID_NONE   VTSS_QOS_MAP_ID_NONE                                       /**< ID for unallocated/unused */

// TBD_VK: Check the defined values when the FA datasheet is available
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
#define VTSS_QOS_TAS_GCL_LEN_MAX     256 /**< Maximum supported length of TAS gate control list */
#define VTSS_QOS_TAS_CT_MIN          256 /**< Minimum supported Gate CycleTime in nS. This is due to STARTUP_TIME register resolution */
#define VTSS_QOS_TAS_CT_MAX   (1000000000-1) /**< Maximum supported Gate CycleTime in nS. Must be less than one second */
#define VTSS_QOS_TAS_MAX_SDU_MAX  (255*64) /**< Maximum supported MAX SDU size */
#define VTSS_QOS_TAS_MAX_SDU_MIN  64       /**< Minimum supported MAX SDU size */
#endif /* defined(VTSS_ARCH_SPARX5) */

// Enable and boolean value
typedef struct {
    BOOL enable; // Enable/disable value
    BOOL value;  // Value
} vtss_opt_bool_t;

// Enable and priority value
typedef struct {
    BOOL        enable; // Enable/disable value
    vtss_prio_t value;  // Value
} vtss_opt_prio_t;

// Cycle time
typedef struct {
    u32 nsec;     // Nanoseconds
    u32 nsec_ext; // Nanoseconds extension
} vtss_cycle_time_t;

/****************************************************************************
 * VLAN types
 ****************************************************************************/

/** \brief VLAN Identifier */
typedef u16 vtss_vid_t; /* 0-4095 */

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_VID_NULL     ((const vtss_vid_t)0)     /**< NULL VLAN ID */
#define VTSS_VID_DEFAULT  ((const vtss_vid_t)1)     /**< Default VLAN ID */
#define VTSS_VID_RESERVED ((const vtss_vid_t)0xFFF) /**< Reserved VLAN ID */
#define VTSS_VIDS         ((const vtss_vid_t)4096)  /**< Number of VLAN IDs */
#define VTSS_VID_ALL      ((const vtss_vid_t)0x1000)/**< Untagged VID: All VLAN IDs */
#endif // _VTSS_MAIN_TYPES_H_

/**
 * \brief VLAN acceptable frame type
 */
typedef enum
{
    VTSS_VLAN_FRAME_ALL,      /**< Accept all frames */
    VTSS_VLAN_FRAME_TAGGED,   /**< Accept tagged frames only */
    VTSS_VLAN_FRAME_UNTAGGED  /**< Accept untagged frames only */
} vtss_vlan_frame_t;

/** \brief Ethernet Type **/
typedef u16 vtss_etype_t;

/**
 * VLAN tag with "arbitrary" TPID.
 */
typedef struct {
    vtss_etype_t   tpid; /**< Tag Protocol Identifier */
    vtss_tagprio_t pcp;  /**< Priority Code Point     */
    BOOL           dei;  /**< Drop Eligible Indicator */
    vtss_vid_t     vid;  /**< VLAN Identifier         */
} vtss_vlan_tag_t;

#define VTSS_ETYPE_VTSS 0x8880 /**< Vitesse Ethernet Type */

/** \brief MAC Address */
typedef struct
{
    u8 addr[6];   /**< Network byte order */
} vtss_mac_t;

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_MAC_ADDR_SZ_BYTES    6                 /**< Number of bytes for representing MAC address (SMAC/DMAC) type */
#endif // _VTSS_MAIN_TYPES_H_

typedef u8 vtss_mac_addr_t[VTSS_MAC_ADDR_SZ_BYTES]; /**< MAC address (SMAC/DMAC) */

/** \brief MAC Address in specific VLAN */
typedef struct
{
    vtss_vid_t  vid;   /**< VLAN ID */
    vtss_mac_t  mac;   /**< MAC address */
} vtss_vid_mac_t;

#define MAC_ADDR_BROADCAST {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}  /**< Broadcast address used for addr in the vtss_mac_t struct */

#ifndef _VTSS_MAIN_TYPES_H_
typedef u32 vtss_isdx_t;   /**< Ingress Service Index type */
#define VTSS_ISDX_NONE (0) /**< Ingress Service Index number none */
#define VTSS_VSI_NONE  (0) /**< Virtual Switching Instance number none */
#endif // _VTSS_MAIN_TYPES_H_

/* Ingress flow ID */
typedef u16 vtss_iflow_id_t;

#define VTSS_IFLOW_ID_NONE 0 /**< No flow ID allocated */

/** \brief Aggregation Number. */
typedef u32 vtss_aggr_no_t;
#define VTSS_AGGRS           (VTSS_PORTS/2) /**< Number of LLAGs */
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_AGGR_NO_NONE    0xffffffff     /**< Aggregation number none */
#define VTSS_AGGR_NO_START   0              /**< Aggregation start number */
#endif // _VTSS_MAIN_TYPES_H_
#define VTSS_AGGR_NO_END     (VTSS_AGGR_NO_START+VTSS_AGGRS) /**< Aggregation number end */

/** \brief Description: GLAG number */
typedef u32 vtss_glag_no_t;

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_GLAGS         32         /**< Number of GLAGs */
#define VTSS_GLAG_NO_NONE  0xffffffff /**< GLAG number none */
#define VTSS_GLAG_NO_START 0          /**< GLAG start number */
#define VTSS_GLAG_NO_END   (VTSS_GLAG_NO_START+VTSS_GLAGS) /**< GLAG end number */
#endif // _VTSS_MAIN_TYPES_H_

/* Maximum 8 ports per GLAG */
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_GLAG_PORTS           8 /**< Number of GLAG ports */
#define VTSS_GLAG_PORT_START      0 /**< GLAG port start number */
#define VTSS_GLAG_PORT_END        (VTSS_GLAG_PORT_START+VTSS_GLAG_PORTS) /**< GLAG port end number */
#define VTSS_GLAG_PORT_ARRAY_SIZE VTSS_GLAG_PORT_END /**< GLAG port array size */
#endif // _VTSS_MAIN_TYPES_H_

/****************************************************************************
 * CPU queue types
 ****************************************************************************/
/** \brief Description: CPU Rx queue number */
typedef u32 vtss_packet_rx_queue_t;

/** \brief Description: CPU Rx group number
 *  \details This is a value in range [0; VTSS_PACKET_RX_GRP_CNT[.
 */
typedef u32 vtss_packet_rx_grp_t;

/** \brief Description: CPU Tx group number
 *  \details This is a value in range [0; VTSS_PACKET_TX_GRP_CNT[.
 */
typedef u32 vtss_packet_tx_grp_t;

#ifndef _VTSS_MAIN_TYPES_H_
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
#undef  VTSS_PACKET_RX_QUEUE_CNT
#define VTSS_PACKET_RX_QUEUE_CNT    8  /**< Number of Rx packet queues */
#undef  VTSS_PACKET_RX_GRP_CNT
#define VTSS_PACKET_RX_GRP_CNT      2  /**< Number of Rx packet groups to which any queue can map */
#undef  VTSS_PACKET_TX_GRP_CNT
#define VTSS_PACKET_TX_GRP_CNT      2  /**< Number of Tx packet groups */
#endif /* VTSS_ARCH_LUTON26/SERVAL */

#if defined(VTSS_ARCH_JAGUAR_2)
#undef  VTSS_PACKET_RX_QUEUE_CNT
#define VTSS_PACKET_RX_QUEUE_CNT    8  /**< Number of Rx packet queues */
#undef  VTSS_PACKET_RX_GRP_CNT
#define VTSS_PACKET_RX_GRP_CNT      2  /**< Number of Rx packet groups to which any queue can map */
#undef  VTSS_PACKET_TX_GRP_CNT
#define VTSS_PACKET_TX_GRP_CNT      2  /**< Number of Tx packet groups */
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_ARCH_SPARX5)
#undef  VTSS_PACKET_RX_QUEUE_CNT
#define VTSS_PACKET_RX_QUEUE_CNT    8  /**< Number of Rx packet queues */
#undef  VTSS_PACKET_RX_GRP_CNT
#define VTSS_PACKET_RX_GRP_CNT      2  /**< Number of Rx packet groups to which any queue can map */
#undef  VTSS_PACKET_TX_GRP_CNT
#define VTSS_PACKET_TX_GRP_CNT      2  /**< Number of Tx packet groups */
#endif /* VTSS_ARCH_SPARX5 */

#if defined(VTSS_ARCH_LAN966X)
#undef  VTSS_PACKET_RX_QUEUE_CNT
#define VTSS_PACKET_RX_QUEUE_CNT    8  /**< Number of Rx packet queues */
#undef  VTSS_PACKET_RX_GRP_CNT
#define VTSS_PACKET_RX_GRP_CNT      2  /**< Number of Rx packet groups to which any queue can map */
#undef  VTSS_PACKET_TX_GRP_CNT
#define VTSS_PACKET_TX_GRP_CNT      2  /**< Number of Tx packet groups */
#endif /* VTSS_ARCH_LAN966X */

#define VTSS_PACKET_RX_QUEUE_NONE  (0xffffffff) /**< Rx queue not selected for a particular type of frames */
#define VTSS_PACKET_RX_QUEUE_START (0)          /**< Rx queue start number */
#define VTSS_PACKET_RX_QUEUE_END   (VTSS_PACKET_RX_QUEUE_START + VTSS_PACKET_RX_QUEUE_CNT) /**< Rx queue end number */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief COSID number */
typedef u8 vtss_cosid_t;
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_COSIDS 8 /**< Number of COSIDs */
#endif // _VTSS_MAIN_TYPES_H_

/** \brief Packet registration type */
typedef enum {
    VTSS_PACKET_REG_NORMAL,   /**< Global registration configuration is used */
    VTSS_PACKET_REG_FORWARD,  /**< Forward normally */
#if defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
    VTSS_PACKET_REG_DISCARD,  /**< Discard */
    VTSS_PACKET_REG_CPU_COPY, /**< Copy to CPU */
#endif /* VTSS_FEATURE_PACKET_PORT_REG_DISCARD */
    VTSS_PACKET_REG_CPU_ONLY  /**< Redirect to CPU */
} vtss_packet_reg_type_t;

#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
/** \brief Registration per port and L2CP */
typedef struct {
    BOOL         cosid_enable; /**< Enable COSID */
    vtss_cosid_t cosid;        /**< COSID */
} vtss_packet_rx_port_l2cp_conf_t;
#endif /* VTSS_FEATURE_PACKET_PORT_L2CP_REG */

/** \brief Packet registration per port */
typedef struct {
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    vtss_packet_reg_type_t          ipmc_ctrl_reg; /**< IP MC Control, NORMAL/FORWARD/CPU_COPY supported */
    vtss_packet_reg_type_t          igmp_reg;      /**< IGMP, NORMAL/FORWARD/CPU_ONLY supported */
    vtss_packet_reg_type_t          mld_reg;       /**< MLD, NORMAL/FORWARD/CPU_ONLY supported */
#endif
    vtss_packet_reg_type_t          bpdu_reg[16];  /**< BPDU range: 01-80-C2-00-00-0X */
    vtss_packet_reg_type_t          garp_reg[16];  /**< GARP range: 01-80-C2-00-00-2X */
#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
    vtss_packet_rx_port_l2cp_conf_t bpdu[16];      /**< BPDU range: 01-80-C2-00-00-0X */
    vtss_packet_rx_port_l2cp_conf_t garp[16];      /**< GARP range: 01-80-C2-00-00-2X */
#endif /* VTSS_FEATURE_PACKET_PORT_L2CP_REG */
} vtss_packet_rx_port_conf_t;

/** \brief VDD power supply */
typedef enum {
    VTSS_VDD_1V0,               /**< 1.0V (default) */
    VTSS_VDD_1V2,               /**< 1.2V */
} vtss_vdd_t;

/****************************************************************************
 * L3 types
 ****************************************************************************/
/** \brief Description: UDP/TCP port number */
typedef u16 vtss_udp_tcp_t;

/** \brief IPv4 address/mask */
typedef u32 vtss_ip_t;

/** \brief IPv4 address/mask */
typedef vtss_ip_t vtss_ipv4_t;

/** \brief Prefix size */
typedef u32 vtss_prefix_size_t;

/** \brief IPv6 address/mask */
typedef struct
{
    u8 addr[16]; /**< Address */
} vtss_ipv6_t;

/* NOTE: This type may be used directly in SNMP
 * InetAddressType types.  */

/** \brief Router leg ID */
typedef u32 vtss_l3_rleg_id_t;

/** \brief IP address type */
typedef enum {
    VTSS_IP_TYPE_NONE = 0, /**< Matches "InetAddressType_unknown" */
    VTSS_IP_TYPE_IPV4 = 1, /**< Matches "InetAddressType_ipv4"    */
    VTSS_IP_TYPE_IPV6 = 2, /**< Matches "InetAddressType_ipv6"    */
} vtss_ip_type_t;

/** \brief Either an IPv4 or IPv6 address  */
typedef struct {
    vtss_ip_type_t  type; /**< Union type */
    union {
        vtss_ipv4_t ipv4; /**< IPv4 address */
        vtss_ipv6_t ipv6; /**< IPv6 address */
    } addr;               /**< IP address */
} vtss_ip_addr_t;

/** \brief IPv4 network */
typedef struct
{
    vtss_ipv4_t        address;     /**< Network address */
    vtss_prefix_size_t prefix_size; /**< Prefix size */
} vtss_ipv4_network_t;

/** \brief IPv6 network */
typedef struct
{
    vtss_ipv6_t        address;     /**< Network address */
    vtss_prefix_size_t prefix_size; /**< Prefix size */
} vtss_ipv6_network_t;

/** \brief IPv6 network */
typedef struct
{
    vtss_ip_addr_t     address;     /**< Network address */
    vtss_prefix_size_t prefix_size; /**< Prefix size */
} vtss_ip_network_t;

/** \brief Routing entry type */
typedef enum
{
    VTSS_ROUTING_ENTRY_TYPE_INVALID = 0,
    VTSS_ROUTING_ENTRY_TYPE_IPV6_UC = 1,
    VTSS_ROUTING_ENTRY_TYPE_IPV4_MC = 2, /* obsolete */
    VTSS_ROUTING_ENTRY_TYPE_IPV4_UC = 3,
} vtss_routing_entry_type_t;

/** \brief IPv4 multicast routing entry */
typedef struct
{
    /**< Multicast Group address */
    vtss_ipv4_t         group;

    /**< SIP address. All zero address enables source independent MC groups [*.G] */
    vtss_ipv4_t         source;
} vtss_ipv4_mc_t;

/** \brief IPv6 multicast routing entry */
typedef struct
{
    /**< Multicast Group address */
    vtss_ipv6_t         group;

    /**< SIP address. All zero address enables source independent MC groups [*.G] */
    vtss_ipv6_t         source;
} vtss_ipv6_mc_t;

/** \brief IPv4 unicast routing entry */
typedef struct
{
    vtss_ipv4_network_t network;     /**< Network to route */
    vtss_ipv4_t         destination; /**< IP address of next-hop router.
                                          Zero if local route */
} vtss_ipv4_uc_t;

/** \brief IPv6 routing entry */
typedef struct
{
    vtss_ipv6_network_t network;     /**< Network to route */
    vtss_ipv6_t         destination; /**< IP address of next-hop router.
                                          Zero if local route */
} vtss_ipv6_uc_t;

/** \brief Unicast Routing entry */
typedef struct
{
   /** Type of unicast route */
   vtss_routing_entry_type_t type;

   union {
       /** IPv6 unicast route */
       vtss_ipv4_uc_t ipv4_uc;

       /** IPv6 unicast route */
       vtss_ipv6_uc_t ipv6_uc;
   } route; /**< Route */

   /** Link-local addresses needs to specify a egress vlan. */
   vtss_vid_t vlan;

} vtss_routing_entry_t;

#define VTSS_RT_TYPE_IPV4_MC 0
#define VTSS_RT_TYPE_IPV6_MC 1

/** \brief Multicast Routing entry */
typedef struct
{
    /** Type of multicast route: VTSS_RT_TYPE_IPV4_MC or VTSS_RT_TYPE_IPV6_MC */
    BOOL type;

    union {
        /** IPv4 multicast route */
        vtss_ipv4_mc_t ipv4_mc;

        /** IPv6 multicast route */
        vtss_ipv6_mc_t ipv6_mc;
    } route; /**< MC Route */

    /** Optional: Multicast Reverse Path Forwarding, use VTSS_VID_NULL to ignore */
    vtss_vid_t source_rleg;
} vtss_routing_mc_entry_t;

/** \brief Routing interface statics counter */
typedef struct {
    u64 ipv4uc_received_octets;    /**< IPv4UC octets received and hardware forwarded */
    u64 ipv4uc_received_frames;    /**< IPv4UC frames received and hardware forwarded */
    u64 ipv6uc_received_octets;    /**< IPv6UC octets received and hardware forwarded */
    u64 ipv6uc_received_frames;    /**< IPv6UC frames received and hardware forwarded */

    u64 ipv4uc_transmitted_octets; /**< IPv4UC octets transmitted */
    u64 ipv4uc_transmitted_frames; /**< IPv4UC frames transmitted */
    u64 ipv6uc_transmitted_octets; /**< IPv6UC octets transmitted */
    u64 ipv6uc_transmitted_frames; /**< IPv6UC frames transmitted */

    u64 ipv4mc_received_octets;    /**< IPv4MC octets received and hardware forwarded */
    u64 ipv4mc_received_frames;    /**< IPv4MC frames received and hardware forwarded */
    u64 ipv6mc_received_octets;    /**< IPv6MC octets received and hardware forwarded */
    u64 ipv6mc_received_frames;    /**< IPv6MC frames received and hardware forwarded */

    u64 ipv4mc_transmitted_octets; /**< IPv4MC octets transmitted */
    u64 ipv4mc_transmitted_frames; /**< IPv4MC frames transmitted */
    u64 ipv6mc_transmitted_octets; /**< IPv6MC octets transmitted */
    u64 ipv6mc_transmitted_frames; /**< IPv6MC frames transmitted */
} vtss_l3_counters_t;

/****************************************************************************
 * VCAP types
 ****************************************************************************/
/** \brief VCAP 1 bit */
typedef enum vtss_vcap_bit
{
    VTSS_VCAP_BIT_ANY, /**< Value 0 or 1 */
    VTSS_VCAP_BIT_0,   /**< Value 0 */
    VTSS_VCAP_BIT_1    /**< Value 1 */
} vtss_vcap_bit_t;

/** \brief VCAP 8 bit value and mask */
typedef struct
{
    u8 value;   /**< Value */
    u8 mask;    /**< Mask, cleared bits are wildcards */
} vtss_vcap_u8_t;

/** \brief VCAP 16 bit value and mask */
typedef struct
{
    u8 value[2];   /**< Value */
    u8 mask[2];    /**< Mask, cleared bits are wildcards */
} vtss_vcap_u16_t;

/** \brief VCAP 24 bit value and mask */
typedef struct
{
    u8 value[3];   /**< Value */
    u8 mask[3];    /**< Mask, cleared bits are wildcards */
} vtss_vcap_u24_t;

/** \brief VCAP 32 bit value and mask */
typedef struct
{
    u8 value[4];   /**< Value */
    u8 mask[4];    /**< Mask, cleared bits are wildcards */
} vtss_vcap_u32_t;

/** \brief VCAP 40 bit value and mask */
typedef struct
{
    u8 value[5];   /**< Value */
    u8 mask[5];    /**< Mask, cleared bits are wildcards */
} vtss_vcap_u40_t;

/** \brief VCAP 48 bit value and mask */
typedef struct
{
    u8 value[6];   /**< Value */
    u8 mask[6];    /**< Mask, cleared bits are wildcards */
} vtss_vcap_u48_t;

/** \brief VCAP 128 bit value and mask */
typedef struct
{
    u8 value[16];   /**< Value */
    u8 mask[16];    /**< Mask, cleared bits are wildcards */
} vtss_vcap_u128_t;

/** \brief VCAP VLAN ID value and mask */
typedef struct
{
    u16 value;   /**< Value */
    u16 mask;    /**< Mask, cleared bits are wildcards */
} vtss_vcap_vid_t;

/** \brief VCAP IPv4 address value and mask */
typedef struct
{
    vtss_ip_t value;   /**< Value */
    vtss_ip_t mask;    /**< Mask, cleared bits are wildcards */
} vtss_vcap_ip_t;

/** \brief VCAP UDP/TCP port range */
typedef struct
{
    BOOL           in_range;   /**< Port in range match */
    vtss_udp_tcp_t low;        /**< Port low value */
    vtss_udp_tcp_t high;       /**< Port high value */
} vtss_vcap_udp_tcp_t;

/** \brief Value/Range type */
typedef enum
{
    VTSS_VCAP_VR_TYPE_VALUE_MASK,        /**< Used as value/mask */
    VTSS_VCAP_VR_TYPE_RANGE_INCLUSIVE,   /**< Used as inclusive range: low <= range <= high */
    VTSS_VCAP_VR_TYPE_RANGE_EXCLUSIVE    /**< Used as exclusive range: range < low or range > high */
} vtss_vcap_vr_type_t;

/** \brief VCAP universal value or range type */
typedef u16 vtss_vcap_vr_value_t;

/** \brief VCAP universal value or range */
typedef struct
{
    vtss_vcap_vr_type_t type; /**< Type */
    union
    {
        struct
        {
            vtss_vcap_vr_value_t value; /**< Value */
            vtss_vcap_vr_value_t mask;  /**< Mask, cleared bits are wildcards */
        } v; /**< type == VTSS_VCAP_VR_TYPE_VALUE_MASK */
        struct
        {
            vtss_vcap_vr_value_t low;   /**< Low value */
            vtss_vcap_vr_value_t high;  /**< High value */
        } r; /**< type == VTSS_VCAP_VR_TYPE_RANGE_XXXXXX */
    } vr; /**< Value or range */
} vtss_vcap_vr_t;

/** \brief VCAP key type */
typedef enum {
    VTSS_VCAP_KEY_TYPE_NORMAL,     /**< Half key, SIP only */
    VTSS_VCAP_KEY_TYPE_DOUBLE_TAG, /**< Quarter key, two tags */
    VTSS_VCAP_KEY_TYPE_IP_ADDR,    /**< Half key, SIP and DIP */
    VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR /**< Full key, MAC and IP addresses */
} vtss_vcap_key_type_t;

/****************************************************************************
 * ACL types
 ****************************************************************************/
/** \brief ACL policer number */
typedef u32 vtss_acl_policer_no_t;
#define VTSS_ACL_POLICERS         16                                              /**< Number of ACL policers */
#define VTSS_ACL_POLICER_NO_START 0                                               /**< ACL policer start number */
#define VTSS_ACL_POLICER_NO_END   (VTSS_ACL_POLICER_NO_START + VTSS_ACL_POLICERS) /**< ACL policer end number */

/** \brief ACL policy number */
typedef u32 vtss_acl_policy_no_t;
#define VTSS_ACL_POLICY_NO_NONE  0xffffffff                                     /**< ACLs disabled on port */
#define VTSS_ACL_POLICY_NO_MIN   0                                              /**< ACLs policy minimum number */
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
#define VTSS_ACL_POLICY_NO_MAX   255                                            /**< ACLs policy maximum number */
#elif defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_ACL_POLICY_NO_MAX   127                                            /**< ACLs policy maximum number */
#elif defined(VTSS_ARCH_OCELOT)
#define VTSS_ACL_POLICY_NO_MAX   63                                             /**< ACLs policy maximum number */
#else
#define VTSS_ACL_POLICY_NO_MAX   7                                              /**< ACLs policy maximum number */
#endif /* VTSS_ARCH_LUTON26/JAGUAR_2 */
#define VTSS_ACL_POLICIES        (VTSS_ACL_POLICY_NO_MAX + 1)                   /**< Number of ACL policies */
#define VTSS_ACL_POLICY_NO_START  VTSS_ACL_POLICY_NO_MIN                        /**< ACL policy start number */
#define VTSS_ACL_POLICY_NO_END   (VTSS_ACL_POLICY_NO_START + VTSS_ACL_POLICIES) /**< ACL policy end number */

/** \brief Counter */
typedef u64 vtss_counter_t;

/** \brief Counter pair */
typedef struct {
    vtss_counter_t frames; /**< Number of frames */
    vtss_counter_t bytes;  /**< Number of bytes */
} vtss_counter_pair_t;

#if defined(VTSS_FEATURE_EVC_COUNTERS) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_FEATURE_VOP)
/** \brief EVC/ECE counters */
typedef struct {
    vtss_counter_pair_t rx_green;   /**< Rx green frames/bytes */
    vtss_counter_pair_t rx_yellow;  /**< Rx yellow frames/bytes */
    vtss_counter_pair_t rx_red;     /**< Rx red frames/bytes */
    vtss_counter_pair_t rx_discard; /**< Rx discarded frames/bytes */
    vtss_counter_pair_t tx_discard; /**< Tx discarded frames/bytes */
    vtss_counter_pair_t tx_green;   /**< Tx green frames/bytes */
    vtss_counter_pair_t tx_yellow;  /**< Tx yellow frames/bytes */
} vtss_evc_counters_t;
#endif

/** \brief MPLS TC bits */
typedef u8 vtss_mpls_tc_t;

/****************************************************************************
 * 1588 types
 ****************************************************************************/

/**
 * \brief Clock adjustment rate in parts per billion (ppb) * 1<<16.
 * Range is +-2**47 ppb
 * For example, 8.25 ppb is expressed as 0x0000.0000.0008.4000
 */
typedef i64 vtss_clk_adj_rate_t;

/**
 * \brief Time interval in ns * 1<<16
 * range +-2**47 ns = 140737 sec = 39 hours
 * For example, 2.5 ns is expressed as 0x0000.0000.0002.8000
 */
typedef i64 vtss_timeinterval_t;

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_ONE_MIA 1000000000 /**< One billion */
#define VTSS_ONE_MILL   1000000 /**< One million */
#define VTSS_MAX_TIMEINTERVAL 0x7fffffffffffffffLL /**< Maximum time interval */
#endif // _VTSS_MAIN_TYPES_H_

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_INTERVAL_SEC(t) ((i32)VTSS_DIV64((t)>>16, VTSS_ONE_MIA)) /**< One Second time interval */
#define VTSS_INTERVAL_MS(t)  ((i32)VTSS_DIV64((t)>>16, VTSS_ONE_MILL)) /**< One millisecond time interval */
#define VTSS_INTERVAL_US(t)  ((i32)VTSS_DIV64((t)>>16, 1000)) /**< One microsecond time interval */
#define VTSS_INTERVAL_NS(t)  ((i32)VTSS_MOD64((t)>>16, VTSS_ONE_MIA)) /**< This returns the ns part of the interval, not the total number of ns */
#define VTSS_INTERVAL_PS(t)  (((((i32)(t & 0xffff))*1000)+0x8000)/0x10000) /**< This returns the ps part of the interval, not the total number of ps */
#define VTSS_SEC_NS_INTERVAL(s,n) (((vtss_timeinterval_t)(n)+(vtss_timeinterval_t)(s)*VTSS_ONE_MIA)<<16)  /**< TBD */
#endif // _VTSS_MAIN_TYPES_H_

/**
 * \brief Time stamp in seconds and nanoseconds
 */
typedef struct {
    u16 sec_msb;         /**< Seconds msb */
    u32 seconds;         /**< Seconds */
    u32 nanoseconds;     /**< nanoseconds */
    u16 nanosecondsfrac; /**< 16 bit fraction of nano seconds */
} vtss_timestamp_t;

/**
 * \brief Scaled nanosec as defined in 802.1AS clause 6.3.3.1:
 *        The ScaledNs type represents signed values of time and time interval in units of 2**-16 ns.
 */
typedef struct {
    i32 scaled_ns_high;     /**< Seconds */
    u64 scaled_ns_low;      /**< nanoseconds */
} vtss_scaled_ns_t;

/**
 * \brief Unsigned Scaled nanosec as defined in 802.1AS clause 6.3.3.2:
 *        The UScaledNs type represents unsigned values of time and time interval in units of 2**-16 ns.
 */
typedef struct {
    u32 uscaled_ns_high;    /**< Seconds */
    u64 uscaled_ns_low;     /**< nanoseconds */
} vtss_uscaled_ns_t;

#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_CLOCK_IDENTITY_LENGTH 8 /**< Length of unique PTP identifier */
#endif // _VTSS_MAIN_TYPES_H_

/**
 * \brief PTP clock unique identifier
 */
typedef u8 vtss_clock_identity[VTSS_CLOCK_IDENTITY_LENGTH];

/****************************************************************************
 * SYNCE types
 ****************************************************************************/

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#define VTSS_SYNCE_CLK_PORT_ARRAY_SIZE  4    /**< SYNCE clock out port numberarray size */
#else
#define VTSS_SYNCE_CLK_PORT_ARRAY_SIZE  2    /**< SYNCE clock out port numberarray size */
#endif

/****************************************************************************
 * VSTAX types
 ****************************************************************************/

/** \brief VStaX Unit Port Set ID (UPSID; 0-31). */
typedef int vtss_vstax_upsid_t;

/** \brief Unit Port Set Port Number */
typedef u32 vtss_vstax_upspn_t;

#ifdef __cplusplus
}
#endif

#endif /* _VTSS_API_TYPES_H_ */
