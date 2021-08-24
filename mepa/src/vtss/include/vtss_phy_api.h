// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_API_H_
#define _VTSS_API_H_

#include <vtss_phy_options.h>
#include <vtss_phy_types.h>

#ifdef VTSS_CHIP_CU_PHY
#include <vtss_phy_1g_api.h>
#endif

#ifdef VTSS_CHIP_10G_PHY
#include <vtss_phy_10g_api.h>
#endif

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#include <vtss_phy_ts_api.h>
#endif

#ifdef VTSS_FEATURE_WIS
#include <vtss_wis_api.h>
#endif

#ifdef VTSS_FEATURE_MACSEC
#include <vtss_macsec_api.h>
#endif

#endif /* _VTSS_API_H_ */
