// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_PHY_OPTIONS_H_
#define _VTSS_PHY_OPTIONS_H_

// TBD
#define VTSS_CHIP_CU_PHY /**< Cobber PHY chip */
#define VTSS_FEATURE_SERDES_MACRO_SETTINGS     /**< Hooks for Serdes Macro configuration */
#define VTSS_FEATURE_MACSEC
#define VTSS_CHIP_10G_PHY
#define VTSS_OPT_PHY_TIMESTAMP 1
#define VTSS_PHY_OPT_TRACE 1

#define VTSS_FEATURE_EEE                          /**< Energy Efficient Ethernet */

#if defined(VTSS_CHIP_CU_PHY)
#define VTSS_FEATURE_WARM_START                /**< Warm start */
#endif /* VTSS_CHIP_CU_PHY */

#if !defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_FEATURE_PHY_TIMESTAMP)
#define VTSS_OPT_PHY_TIMESTAMP 1 /**< Enable PHY timestamp feature */
#endif
#endif

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#define VTSS_VIPER_B_FIFO_RESET          /**< Viper B 1588 OOS fix */
#define VTSS_VIPER_B_FIFO_RESET_API_CALL /**< Viper B OOS fix taken care of within the PHY API */
#endif

#if defined(VTSS_CHIP_10G_PHY)
#define VTSS_FEATURE_SYNCE_10G                 /**< SYNCE - L1 syncronization feature for 10G PHYs*/
#define VTSS_FEATURE_EDC_FW_LOAD               /**< 848x EDC firmware will get loaded at initilization */
#define VTSS_FEATURE_WIS                       /**< WAN interface sublayer functionality */
#define VTSS_FEATURE_WARM_START                /**< Warm start */
#define VTSS_ARCH_MALIBU                     /**< Used for Malibu-A PHY */
#define VTSS_ARCH_MALIBU_B                     /**< Used for Malibu-B PHY */
#define VTSS_ARCH_VENICE_C                     /**< Used for Venice-C PHY */
#endif /* VTSS_CHIP_10G_PHY */

// Some building script uses the feature define as an option. This is not the
// idea, but we want to have some level of backwards compatibility. If
// VTSS_OPT_PHY_MACSEC is defined, then it will control the availability for the
// MACsec feature regardless of the VTSS_FEATURE_MACSEC define.
#if defined(VTSS_OPT_PHY_MACSEC)
#undef VTSS_FEATURE_MACSEC
#if VTSS_OPT_PHY_MACSEC
#define VTSS_FEATURE_MACSEC /**< Enable macsec feature */
#endif
#elif defined(VTSS_FEATURE_MACSEC)
#define VTSS_OPT_PHY_MACSEC 1 /**< Enable macsec feature */
#else
#define VTSS_OPT_PHY_MACSEC 0 /**< Disable macsec feature */
#endif

#endif /* _VTSS_PHY_OPTIONS_H_ */
