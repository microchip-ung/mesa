// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_PHY_API_H_
#define _MICROCHIP_ETHERNET_PHY_API_H_

#include <stdarg.h>
#include <microchip/ethernet/common.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api/phy.h>
#ifdef MEPA_OPT_TS
#include <microchip/ethernet/phy/api/phy_ts.h>
#endif
#ifdef MEPA_OPT_MACSEC
#include <microchip/ethernet/phy/api/phy_macsec.h>
#endif
#ifdef MEPA_OPT_TC10
#include <microchip/ethernet/phy/api/phy_tc10.h>
#endif
#include <microchip/ethernet/phy/api/phy_t1s.h>

#endif // _MICROCHIP_ETHERNET_PHY_API_H_
