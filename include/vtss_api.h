// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


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

#ifdef VTSS_FEATURE_MRP
#include <vtss_mrp_api.h>
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

#if defined(VTSS_FEATURE_TIMESTAMP)
#include <vtss_ts_api.h>
#endif

#ifdef VTSS_FEATURE_CLOCK
#include <vtss_clock_api.h>
#endif

#endif /* _VTSS_API_H_ */
