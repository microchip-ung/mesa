// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef MSCC_ETHERNET_SWITCH_API_HQOS
#define MSCC_ETHERNET_SWITCH_API_HQOS

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h> // ALL INCLUDE ABOVE THIS LINE

// #include <mscc/ethernet/switch/api/hqos.h>

// Hierarchical Quality of Service
// ===============================
//
// MESA_HQOS_SCH_MODE_NORMAL:
// --------------------------
//
// Hierarchical Quality of Service (HQoS) is about providing differentiated shaping
// and scheduling per Service (hqos_id)
//
// A port can be configured to be in Normal mode or HQoS mode.
// Default the port is in Normal mode.
//
// In Normal mode (MESA_HQOS_SCH_MODE_NORMAL) the scheduler hierarchy is like this:
//
//                               Priority-layer
//
//                             +--------+ Port0 P0
//                             |        |<---------
//                  +----------| SE P0  | PortN P0
//                  |          |        |<---------
//      Port-layer  |          +--------+
//                  V
//         +--------+          +--------+ Port0 P1
//         |        |          |        |<---------
//  <------| SE     |<---------| SE P1  | PortN P1
//         |        |          |        |<---------
//         +--------+          +--------+
//                  ^
//                  |          (SE P2..6)
//                  |
//                  |          +--------+ Port0 P7
//                  |          |        |<---------
//                  +----------| SE P7  | PortN P7
//                             |        |<---------
//                             +--------+
//
// At priority-layer there are one Scheduler Element (SE0-7) for each priority.
// Input to this SEs is from each ingress port.
// This is fully created when calling mesa_hqos_port_conf_set(MESA_HQOS_SCH_MODE_NORMAL)
// Configuration of scheduling and shaping is done by the mesa_qos_port_conf_set() API
//
//
// MESA_HQOS_SCH_MODE_HIERARCHICAL:
// --------------------------------
//
// In HQoS mode (MESA_HQOS_SCH_MODE_HIERARCHICAL) the scheduler hierarchy is
// like this:
//
//             Port-layer                        Service-layer
//
//                                             +-----------+ Priority0
//             +--------+                      |           |<---------
//             |        |<---------------------| HQOS-ID0  | Priority7
//             |        |                      |           |<---------
//             |        |                      +-----------+
//             |        |
//             |        |                      +-----------+ Priority0
//             |        |                      |           |<---------
//             |        |<---------------------| HQOS-ID1  | Priority7
//             |        |                      |           |<---------
//             |        |                      +-----------+
//             |        |
//             |        |                      +-----------+ Priority0
//             |        |                      |           |<---------
//             |        |<---------------------| HQOS-ID2  | Priority7
//             |        |                      |           |<---------
//             |        |                      +-----------+
//      <------| SE     |
//             |        |                      +-----------+ Priority0
//             |        |                      |           |<---------
//             |        |<---------------------| HQOS-ID3  | Priority7
//             |        |                      |           |<---------
//             |        |                      +-----------+
//             |        |
//             |        |                      +-----------+ Priority0
//             |        |                      |           |<---------
//             |        |<---------------------| HQOS-ID4  | Priority7
//             |        |                      |           |<---------
//             |        |                      +-----------+
//             |        |
//             |        |                      many more...
//             |        |
//             |        |                      +-----------+ Priority0
//             |        |                      |           |<---------
//             |        |<---------------------| HQOS-ID127| Priority7
//             +--------+                      |           |<---------
//                                             +-----------+
//
//
// - Traffic are classifed to a (mesa_hqos_id_t) using mesa_iflow_conf_set/mesa_vlan_vid_conf_set.
// - Per port, Per mesa_hqos_id_t, service-level SE (mesa_hqos_id_t) is created/deleted dynamic
//   using the mesa_hqos_add/del APIs.
//   - The same mesa_hqos_id_t value can be used on different ports (essential to support multicast
//     traffic)
// - Port-layer SE can be configured using mesa_qos_port_conf_set().

// HQoS port configuration
// When a port is in mode MESA_HQOS_SCH_MODE_NORMAL then the "_hqos_" API is not applicable.
// In normal mode the API functions mesa_qos_port_conf_set() and mesa_qos_port_conf_get() are used.
typedef struct {
    mesa_hqos_sch_mode_t sch_mode; /**< Egress port HQoS Scheduling mode */
} mesa_hqos_port_conf_t CAP(HQOS);

// Get HQoS port configuration.
//
// inst [IN]     Target instance reference.
// port_no [IN]  Egress Port number.
// conf [OUT]    HQoS port configuration structure.
mesa_rc mesa_hqos_port_conf_get(const mesa_inst_t            inst,
                                const mesa_port_no_t         port_no,
                                mesa_hqos_port_conf_t *const conf) CAP(HQOS);

// Set HQoS port configuration.
//
// inst [IN]     Target instance reference.
// port_no [IN]  Egress Port number.
// conf [IN]     HQoS port configuration structure.
mesa_rc mesa_hqos_port_conf_set(const mesa_inst_t                  inst,
                                const mesa_port_no_t               port_no,
                                const mesa_hqos_port_conf_t *const conf) CAP(HQOS);

// Egress HQoS setup per HQOS-ID
typedef struct {
    // This HQOS-ID is a priority service.
    // Frames classified to this HQOS-ID take transmission precedence
    // over non-priority HQOS-ID frames
    mesa_bool_t priority_service; // This cannot be changed after the initial add

    // Output shaper
    mesa_shaper_t shaper;

    // Number of inputs running Deficit Weighted Round Robin scheduling
    uint8_t dwrr_cnt;

    // Input percentages
    mesa_pct_t input_pct[MESA_PRIO_ARRAY_SIZE];

    // Configured minimum bandwidth. Unit: kbps.
    mesa_bitrate_t min_rate;
} mesa_hqos_conf_t CAP(HQOS);

// Add or set HQoS entry.
//
// inst [IN]     Target instance reference.
// port_no [IN]  egress port number
// hqos_id [IN]  HQoS profile ID.
// conf [IN]     HQoS profile configuration.
mesa_rc mesa_hqos_add(const mesa_inst_t             inst,
                      const mesa_port_no_t          port_no,
                      const mesa_hqos_id_t          hqos_id,
                      const mesa_hqos_conf_t *const conf) CAP(HQOS);

// Delete HQoS entry.
//
// inst [IN]     Target instance reference.
// port_no [IN]  egress port number
// hqos_id [IN]  HQoS profile ID.
mesa_rc mesa_hqos_del(const mesa_inst_t    inst,
                      const mesa_port_no_t port_no,
                      const mesa_hqos_id_t hqos_id) CAP(HQOS);

// Get HQoS ID configuration.
//
// inst [IN]     Target instance reference.
// port_no [IN]  egress port number
// hqos_id [IN]  HQoS profile ID.
// conf [OUT]    HQoS profile configuration.
mesa_rc mesa_hqos_get(const mesa_inst_t       inst,
                      const mesa_port_no_t    port_no,
                      const mesa_hqos_id_t    hqos_id,
                      mesa_hqos_conf_t *const conf) CAP(HQOS);

typedef struct {
    // Actual minimum bandwidth. Unit: kbps.
    mesa_bitrate_t min_rate;
} mesa_hqos_status_t CAP(HQOS);

// Get HQoS status.
//
// inst [IN]     Target instance reference.
// port_no [IN]  egress port number
// hqos_id [IN]  HQoS profile ID.
// status [OUT]  HQoS profile status.
mesa_rc mesa_hqos_status_get(const mesa_inst_t         inst,
                             const mesa_port_no_t      port_no,
                             const mesa_hqos_id_t      hqos_id,
                             mesa_hqos_status_t *const status) CAP(HQOS);

#include <microchip/ethernet/hdr_end.h>
#endif // MSCC_ETHERNET_SWITCH_API_HQOS
