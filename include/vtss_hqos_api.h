// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/**
 * \file
 * \brief HQoS API
 * \details This header file describes Hierarchical Quality of Service (HQoS) functions
 */

#ifndef _VTSS_HQOS_API_H_
#define _VTSS_HQOS_API_H_

#include <vtss/api/types.h>

#include <vtss_qos_api.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(VTSS_FEATURE_HQOS)

/* - Hierarchical Quality of Service ---------------------------------- */

/** hqos Hierachical Quality of Service (HQoS)

    Hierarchical Quality of Service (HQoS) is about providing differentiated shaping
    and scheduling per Service (hqos_id)

    A port can be configured to be in Normal mode or HQoS mode.
    Default the port is in Normal mode.

    In Normal mode the configuration of scheduling and shaping is done by the
    mesa_qos_port_conf_set() API
    In HQoS mode mode the configuration of scheduling and shaping is done by the
    vtss_hqos_add() API

    To provide HQoS Features on an egress port, one must:

    1) Set the egress port to Hierarchical Scheduling mode using vtss_hqos_port_conf_set().
    2) Create an HQoS element related to a HQOS-ID (hqos_id) on the egress port using
       vtss_hqos_add(hqos_id).
    3) Map services to that HQOS-ID per VLAN or per IFLOW by calling
       mesa_vlan_vid_conf_set(hqos_id) and mesa_iflow_conf_set(hqos_id).
*/

/** \brief HQoS port configuration */
typedef struct {
    vtss_hqos_sch_mode_t sch_mode; /**< Egress port HQoS Scheduling mode */
} vtss_hqos_port_conf_t;

/**
 * \brief Get HQoS port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Egress Port number.
 * \param conf [OUT]    HQoS port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_hqos_port_conf_get(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                vtss_hqos_port_conf_t *const conf);

/**
 * \brief Set HQoS port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Egress Port number.
 * \param conf [IN]     HQoS port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_hqos_port_conf_set(const vtss_inst_t                  inst,
                                const vtss_port_no_t               port_no,
                                const vtss_hqos_port_conf_t *const conf);

/** \brief Egress QoS setup per HQoS ID **/
typedef struct {
    /**< This HQOS-ID is a priority service.
         Frames classified to this HQOS-ID take transmission precedence
         over non-priority HQOS-ID frames */
    BOOL priority_service;

    /**< Egress shaper */
    vtss_shaper_t shaper;

    /**< Number of queues running Weighted Round Robin scheduling */
    u8 dwrr_cnt;

    /**< Input percentages */
    vtss_pct_t input_pct[VTSS_PRIO_ARRAY_SIZE];

    /**< Configured minimum bandwidth. Unit: kbps. */
    vtss_bitrate_t min_rate;
} vtss_hqos_conf_t;

/**< The maximum number of HQoS entries on a port (non-priority + priority)*/
#define VTSS_HQOS_PORT_ENTRY_MAX 256
/**< The maximum number of priority HQoS entries on a port */
#define VTSS_HQOS_PORT_PRIORITY_ENTRY_MAX 64
/**< The maximum number of HQoS profile ID */
#define VTSS_HQOS_ID_MAX 1023

/**
 * \brief Add or set HQoS entry.
 * Note this function is only valid when the port is in VTSS_HQOS_SCH_MODE_HIERARCHICAL mode
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Egress Port number.
 * \param hqos_id [IN]  HQoS profile ID.
 * \param conf [IN]     HQoS profile configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_hqos_add(const vtss_inst_t             inst,
                      const vtss_port_no_t          port_no,
                      const vtss_hqos_id_t          hqos_id,
                      const vtss_hqos_conf_t *const conf);

/**
 * \brief Delete HQoS entry.
 * Note this function is only valid when the port is in VTSS_HQOS_SCH_MODE_HIERARCHICAL mode
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Egress Port number.
 * \param hqos_id [IN]  HQoS profile ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_hqos_del(const vtss_inst_t    inst,
                      const vtss_port_no_t port_no,
                      const vtss_hqos_id_t hqos_id);

/**
 * \brief Get HQoS ID configuration.
 * Note this function is only valid when the port is in VTSS_HQOS_SCH_MODE_HIERARCHICAL mode
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Egress Port number.
 * \param hqos_id [IN]  HQoS profile ID.
 * \param conf [OUT]    HQoS profile configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_hqos_get(const vtss_inst_t       inst,
                      const vtss_port_no_t    port_no,
                      const vtss_hqos_id_t    hqos_id,
                      vtss_hqos_conf_t *const conf);

typedef struct {
    // Actual minimum bandwidth. Unit: kbps.
    vtss_bitrate_t min_rate;
} vtss_hqos_status_t;

/**
 * \brief Get HQoS status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  egress port number
 * \param hqos_id [IN]  HQoS profile ID.
 * \param status [OUT]  HQoS profile status.
 *
 * \return Return code.
 **/
vtss_rc vtss_hqos_status_get(const vtss_inst_t         inst,
                             const vtss_port_no_t      port_no,
                             const vtss_hqos_id_t      hqos_id,
                             vtss_hqos_status_t *const status);

#endif /* VTSS_FEATURE_HQOS */

#ifdef __cplusplus
}
#endif
#endif /* _VTSS_HQOS_API_H_ */
