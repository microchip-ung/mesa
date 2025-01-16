// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_L2_TYPES_H_
#define _VTSS_L2_TYPES_H_

#include <vtss/api/types.h>

/**
 * \file
 * \brief Layer 2 Public API Header for l2
 * \details This header file describes public Layer 2 datatypes
 */

/** \brief Aggregation traffic distribution mode */
typedef struct {
    BOOL smac_enable;        /**< Source MAC address */
    BOOL dmac_enable;        /**< Destination MAC address */
    BOOL sip_dip_enable;     /**< Source and destination IP address */
    BOOL sport_dport_enable; /**< Source and destination UDP/TCP port */
} vtss_aggr_mode_t;

/**
 * \brief sFlow sampler type.
 *
 * The API supports sampling ingress and egress separately, as well
 * as simultaneously.
 */
typedef enum {
    VTSS_SFLOW_TYPE_NONE = 0, /**< Sampler is not enabled on the port. */
    VTSS_SFLOW_TYPE_RX, /**< Sampler is enabled for ingress on the port. */
    VTSS_SFLOW_TYPE_TX, /**< Sampler is enabled for egress on the port. */
    VTSS_SFLOW_TYPE_ALL /**< Sampler is enabled for both ingress and egress on
                           the port. */
} vtss_sflow_type_t;

#endif /* #define _VTSS_L2_TYPES_H_ */
