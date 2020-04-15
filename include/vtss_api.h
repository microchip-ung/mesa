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

/**
 * \file
 * \brief Vitesse API main header file
 * \details This is the only header file which must be included by the application
 */

#ifndef _VTSS_API_H_
#define _VTSS_API_H_

#include <vtss/api/options.h>

#include <vtss_os.h>

#include <vtss/api/types.h>
#include <vtss/api/l2_types.h>
#include <vtss_init_api.h>

#ifdef VTSS_FEATURE_MISC
#include <vtss_misc_api.h>
#endif

#ifdef VTSS_FEATURE_PORT_CONTROL
#include <vtss_port_api.h>
#endif

#ifdef VTSS_CHIP_CU_PHY
#include <vtss_phy_api.h>
#endif

#ifdef VTSS_CHIP_10G_PHY
#include <vtss_phy_10g_api.h>
#endif

#ifdef VTSS_FEATURE_LAYER2
#include <vtss_tsn_api.h>
#endif

#ifdef VTSS_FEATURE_QOS
#include <vtss_qos_api.h>
#endif

#ifdef VTSS_FEATURE_AFI_SWC
#include <vtss_afi_api.h>
#endif

#ifdef VTSS_FEATURE_PACKET
#include <vtss_packet_api.h>
#endif

#ifdef VTSS_FEATURE_VOP
#include <vtss_vop_api.h>
#endif

#ifdef VTSS_FEATURE_LAYER2
#include <vtss_l2_api.h>
#endif

#if defined(VTSS_FEATURE_LAYER3)
#include <vtss_l3_api.h>
#endif

#ifdef VTSS_FEATURE_LAYER2
#include <vtss_security_api.h>
#endif

#ifdef VTSS_FEATURE_SYNCE
#include <vtss_sync_api.h>
#endif

#if defined(VTSS_OPT_PHY_TIMESTAMP) || defined(VTSS_FEATURE_TIMESTAMP)
#include <vtss_phy_ts_api.h>
#include <vtss_ts_api.h>
#endif

#ifdef VTSS_FEATURE_WIS
#include <vtss_wis_api.h>
#endif

#ifdef VTSS_FEATURE_MACSEC
#include <vtss_macsec_api.h>
#endif

#ifdef VTSS_FEATURE_CLOCK
#include <vtss_clock_api.h>
#endif

#endif /* _VTSS_API_H_ */
