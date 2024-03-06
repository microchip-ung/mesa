// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <vtss_phy_api.h>

#ifndef _VTSS_PHY_OPTIONS_H_
#define _VTSS_PHY_OPTIONS_H_

// 1G PHYs, included by default
#if !defined(VTSS_OPT_PHY_1G)
#define VTSS_OPT_PHY_1G 1
#endif
#if VTSS_OPT_PHY_1G
#define VTSS_CHIP_CU_PHY
#endif

// 10G PHYs, excluded by default
#if !defined(VTSS_OPT_PHY_10G)
#define VTSS_OPT_PHY_10G 0
#endif
#if VTSS_OPT_PHY_10G
#define VTSS_CHIP_10G_PHY
#endif

// Timestamping, excluded by default
#if !defined(VTSS_OPT_PHY_TIMESTAMP)
#define VTSS_OPT_PHY_TIMESTAMP 0
#endif
#if !VTSS_OPT_PHY_TIMESTAMP
#undef VTSS_OPT_PHY_TIMESTAMP
#endif

// MacSec, excluded by default
#if !defined(VTSS_OPT_PHY_MACSEC)
#define VTSS_OPT_PHY_MACSEC 0
#endif
#undef VTSS_FEATURE_MACSEC
#if VTSS_OPT_PHY_MACSEC
#define VTSS_FEATURE_MACSEC
#endif

// Number of ports
#if VTSS_OPT_PHY_PORT_COUNT
#define VTSS_PORTS VTSS_OPT_PHY_PORT_COUNT
#else
#define VTSS_PORTS 64
#endif

// Trace, included by default
#if !defined(VTSS_OPT_PHY_TRACE)
#define VTSS_OPT_PHY_TRACE 1
#endif

// VeriPHY, included by default */
#if !defined(VTSS_PHY_OPT_VERIPHY)
#define VTSS_PHY_OPT_VERIPHY 1
#endif /* VTSS_PHY_OPT_VERIPHY */

// 10BASE-Te, excluded by default
// 10BASE-Te settings select a reduced transmit amplitude that should be right
// in the middle of the spec. range.
// The 10BASE-T settings will be right at the lower spec.-limit for 10BASE-T
// amplitude (higher than Te, but marginal to spec. the 2.2v spec.)
#if !defined(VTSS_PHY_OPT_10BASE_TE)
#define VTSS_PHY_OPT_10BASE_TE 0
#endif
#undef VTSS_10BASE_TE
#if VTSS_PHY_OPT_10BASE_TE
#define VTSS_10BASE_TE
#endif

// Energy Efficient Ethernet
#define VTSS_FEATURE_EEE

// Internal define
#define VTSS_FEATURE_WARM_START

// LED power reduction
#define VTSS_FEATURE_LED_POW_REDUC

// Hooks for Serdes Macro configuration
#define VTSS_FEATURE_SERDES_MACRO_SETTINGS

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#define VTSS_VIPER_B_FIFO_RESET          /**< Viper B 1588 OOS fix */
#define VTSS_VIPER_B_FIFO_RESET_API_CALL /**< Viper B OOS fix taken care of within the PHY API */
#endif

#if defined(VTSS_CHIP_10G_PHY)
#define VTSS_FEATURE_SYNCE_10G           /**< SYNCE - L1 syncronization feature for 10G PHYs*/
#define VTSS_FEATURE_10GBASE_KR          /**< KR */
#define VTSS_FEATURE_WIS                 /**< WAN interface sublayer functionality */
#define VTSS_FEATURE_10GBASE_KR          /**< KR */
#define VTSS_ARCH_MALIBU                 /**< Used for Malibu-A PHY */
#define VTSS_ARCH_MALIBU_B               /**< Used for Malibu-B PHY */
#define VTSS_ARCH_VENICE_C               /**< Used for Venice-C PHY */
#endif /* VTSS_CHIP_10G_PHY */

#endif /* _VTSS_PHY_OPTIONS_H_ */
