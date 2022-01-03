// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_VOP_
#define _MICROCHIP_ETHERNET_SWITCH_API_VOP_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/******************************************************************************/
/******************  Introduction to VOP API  *********************************/
/******************************************************************************/
/* This OAM API in combination with the Enhanced VLAN API enables
 * configuration of MEPs and Half-MIPs.
 *
 * First, VOP must be configured by calling mesa_vop_conf_set().
 *
 * Configuring and operating a MEP:
 * 1 Allocate an OAM-supporting VOE resource.
 * 2 Do basic VOE configuration.
 * 3 Do OAM feature related VOE configuration.
 * 4 Inject OAM frames hitting VOE on egress.
 *   Injection of OAM frames can be done using AFI or CPU single frame injection.
 *   Hitting a Service VOE requires a TCE entry that maps Tx OAM frames to VOE.
 *   Hitting a Port VOE requires that the frame did not hit a Service VOE.
 * 5 Extract OAM frames hitting VOE on ingress.
 *   Extraction of frames can be controlled through VOE configuration.
 *   Hitting a Service VOE requires a VCE entry mapping Rx OAM frames to VOE.
 *   Hitting a Port VOE requires frame did not hit a Service VOE.
 * 6 Event handling.
 *   Events from VOE can be enabled or disabled.
 *   On interrupt from VOE (or any time) any active event source can be determined.
 * 7 Status information.
 *   Basic status information can be retrieved .
 *   OAM feature status information can be retrieved .
 *
 * Configuring and operating a Half-MIP (MHF):
 * 1 Allocate an OAM-supporting VOI resource.
 * 2 Do VOI configuration.
 * 3 Inject OAM frames.
 *   Injection of OAM frames can be done using AFI or CPU single frame injection.
 *   Hitting a VOI is not required.
 * 4 Extract OAM frames hitting VOI on ingress.
 *   Extraction of frames can be controlled through VOI configuration.
 *   Hitting a Down VOI requires a VCE entry mapping Rx OAM frames to VOI.
 *   Hitting an Up VOI requires a VCE entry mapping Rx OAM frames to an ingress
 *   flow ID and a TCE that matches the ingress flow ID and maps forwarded OAM
 *   frames to the VOI.
 * 5 Event handling.
 *   There are no events from VOI.
 * 6 Status information.
 *   There is no status information from VOI.
 */
/*****************************************************************************/

// -------------------------------------------------------------------------
// --- VOP - Versatile OAM Processor ---------------------------------------
// -------------------------------------------------------------------------

// VOP configuration. Once the VOP is configured, VOEs and MRPs (see mrp.h) can be configured.
typedef struct {
    mesa_mac_t  multicast_dmac;     // Common MC DMAC for all VOEs

    // Two timer periods used for OAM frame auto copy to CPU.
    // Values in microseconds. A value of 0 disables the timer.
    uint32_t    auto_copy_period[2]  CAP(VOP_V2);

    // auto_copy_xxx members are auto copy to CPU timer period selector for PDU types.
    // Value 0 or 1 select one of the two periods in 'auto_copy_period'

    uint8_t     auto_copy_ccm_valid CAP(VOP_V2); // PDU CCM is valid
    // PDU CCM has TLVs other than port and interface status TLV.
    uint8_t     auto_copy_ccm_tlv   CAP(VOP_V2);
    uint8_t     auto_copy_ccm_err   CAP(VOP_V2); // PDU CCM validation failed.
    uint8_t     auto_copy_lbr       CAP(VOP_V2); // PDU Loop Back Reply

    // CPU extraction queues to use for the various packet types
    mesa_packet_rx_queue_t  voe_queue_ccm;
    mesa_packet_rx_queue_t  voe_queue_lt  CAP(VOP_CFM); // LTM, LTR common settings
    mesa_packet_rx_queue_t  voe_queue_lbm CAP(VOP_CFM);
    mesa_packet_rx_queue_t  voe_queue_lbr CAP(VOP_CFM);
    mesa_packet_rx_queue_t  voe_queue_aps CAP(VOP_CFM); // LAPS and RAPS
    mesa_packet_rx_queue_t  voe_queue_err;
    mesa_packet_rx_queue_t  voi_queue     CAP(VOP_V2);
    mesa_packet_rx_queue_t  mrp_queue     CAP(VOP_MRP);
} mesa_vop_conf_t CAP(VOP);

// Set VOP configuration.
// inst [IN] Target instance reference.
// conf [IN] New configuration for the VOP.
mesa_rc mesa_vop_conf_set(const mesa_inst_t       inst,
                          const mesa_vop_conf_t  *const conf) CAP(VOP);

mesa_rc mesa_vop_conf_get(const mesa_inst_t  inst,
                          mesa_vop_conf_t    *const conf) CAP(VOP);


// -------------------------------------------------------------------------
// --- VOE - Versatile OAM End point ---------------------------------------
// -------------------------------------------------------------------------

typedef enum {
    MESA_VOE_TYPE_SERVICE,
    MESA_VOE_TYPE_PORT,
} mesa_voe_type_t CAP(VOP_CFM);

typedef enum {
    MESA_OAM_DIRECTION_DOWN,
    MESA_OAM_DIRECTION_UP,
} mesa_oam_direction_t CAP(VOP_CFM);

// VOE Allocation structure.
typedef struct {
    mesa_voe_type_t       type CAP(VOP_CFM);
    mesa_port_no_t        port;
    mesa_oam_direction_t  direction CAP(VOP_CFM);
} mesa_voe_allocation_t CAP(VOP);

// Allocate a VOE.
// inst      [IN]  Target instance reference.
// param     [IN]  Allocation parameters
// voe_idx   [OUT] Index of allocated VOE instance.
//                 This index can be used when creating VCE or TCE entries
mesa_rc mesa_voe_alloc(const mesa_inst_t            inst,
                       const mesa_voe_allocation_t  *const param,
                       mesa_voe_idx_t               *const voe_idx)  CAP(VOP);

// Free a VOE.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of previously allocated VOE instance.
mesa_rc mesa_voe_free(const mesa_inst_t    inst,
                      const mesa_voe_idx_t voe_idx) CAP(VOP);

// Kind of DMAC check to perform on incoming OAM PDUs.
// When DMAC check is failing the frame is discarded
typedef enum {
    MESA_VOE_DMAC_CHECK_UNICAST,    // Check unicast DMAC against VOE configured 'unicast_mac'. Multicast is discarded.
    MESA_VOE_DMAC_CHECK_MULTICAST,  // Check multicast DMAC against VOP configured 'multicast_dmac'. Unicast is discarded.
    MESA_VOE_DMAC_CHECK_BOTH,       // Check both unicast and multicast DMAC.
    MESA_VOE_DMAC_CHECK_NONE        // No Check of DMAC.
} mesa_voe_dmac_check_t CAP(VOP);

// VOE Basic configuration structure.
typedef struct {
    mesa_bool_t            enable;          // Enable the VOE
    mesa_mac_t             unicast_mac;     // The VOE unicast MAC
    uint8_t                meg_level;       // MEG Level (MEL)
    mesa_voe_dmac_check_t  dmac_check_type; // Kind of DMAC check to perform
    mesa_iflow_id_t        loop_iflow_id  CAP(VOP_CFM);  // Loop ingress flow ID or MESA_IFLOW_ID_NONE

    // Block OAM PDUs with MEG level higher than the VOE MEG level
    mesa_bool_t            block_mel_high  CAP(VOP_V2);

    mesa_port_max_tags_t   tagging  CAP(VOP_TAGGING);  // OAM PDU is behind this many tags
} mesa_voe_conf_t CAP(VOP);

// Set VOE Basic configuration.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of VOE configuration to set.
// conf     [IN] New configuration for the VOE.
mesa_rc mesa_voe_conf_set(const mesa_inst_t      inst,
                          const mesa_voe_idx_t   voe_idx,
                          const mesa_voe_conf_t  *const conf)  CAP(VOP);

mesa_rc mesa_voe_conf_get(const mesa_inst_t      inst,
                          const mesa_voe_idx_t   voe_idx,
                          mesa_voe_conf_t        *const conf)  CAP(VOP);

// VOE CCM periods supported.
typedef enum {
    MESA_VOE_CCM_PERIOD_3_3_MS,
    MESA_VOE_CCM_PERIOD_10_MS,
    MESA_VOE_CCM_PERIOD_100_MS,
    MESA_VOE_CCM_PERIOD_1_SEC,
    MESA_VOE_CCM_PERIOD_10_SEC  CAP(VOP_V2)
} mesa_voe_ccm_period_t CAP(VOP);

// VOE/VOI CPU copy selection.
typedef enum {
    MESA_OAM_CPU_COPY_NONE,
    MESA_OAM_CPU_COPY_ALL,

    // The PDUs are auto-copied to CPU based on 'mesa_vop_conf_t.auto_copy_xxx'
    // period selector.
    MESA_OAM_CPU_COPY_AUTO  CAP(VOP_V2)
} mesa_oam_cpu_copy_t CAP(VOP);

// VOE Continuity Check configuration.
#define MESA_OAM_MEG_ID_LENGTH  48     // The MEG ID length
typedef struct {
    mesa_bool_t            enable;        // Enable CCM PDU handling in HW
    mesa_oam_cpu_copy_t    cpu_copy;      // Control copy of CCM PDUs to CPU
    mesa_bool_t            seq_no_update; // Update Tx CCM sequence number

    // Count PDU as selected.
    // When false, counts in mesa_voe_counters_t::rx/tx_counter
    // When true,  counts in mesa_voe_counters_t::rx/tx_selected_counter
    mesa_bool_t            count_as_selected;

    // Expected received CCM PDU period.
    mesa_voe_ccm_period_t  expected_period;

    // Expected received CCM PDU Priority
    uint8_t                expected_priority;

    // Expected received CCM PDU MEG ID.
    uint8_t                expected_megid[MESA_OAM_MEG_ID_LENGTH];

    // Expected received CCM_PDU peer MEP ID.
    uint16_t               expected_peer_mepid;
} mesa_voe_cc_conf_t CAP(VOP);

// VOE Continuity Check configuration set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// conf     [IN] Configuration parameters for CC.
mesa_rc mesa_voe_cc_conf_set(const mesa_inst_t         inst,
                             const mesa_voe_idx_t      voe_idx,
                             const mesa_voe_cc_conf_t  *const conf)  CAP(VOP);

mesa_rc mesa_voe_cc_conf_get(const mesa_inst_t      inst,
                             const mesa_voe_idx_t   voe_idx,
                             mesa_voe_cc_conf_t     *const conf)  CAP(VOP);

// VOE Continuity Check Remote Defect Indication status set.
// This RDI is inserted in transmitted CCM PDUs if CC is enabled.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
// rdi      [IN] The CCM RDI status.
mesa_rc mesa_voe_cc_rdi_set(const mesa_inst_t     inst,
                            const mesa_voe_idx_t  voe_idx,
                            const mesa_bool_t     rdi) CAP(VOP);

mesa_rc mesa_voe_cc_rdi_get(const mesa_inst_t      inst,
                            const mesa_voe_idx_t   voe_idx,
                            mesa_bool_t            *const rdi) CAP(VOP);

// VOE Continuity Check copy next received CC PDU to CPU set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
mesa_rc mesa_voe_cc_cpu_copy_next_set(const mesa_inst_t     inst,
                                      const mesa_voe_idx_t  voe_idx) CAP(VOP);

// VOE Link Trace configuration.
typedef struct {
    mesa_bool_t   enable;   // Enable LT PDU handling in HW

    // Count PDU as selected.
    // When false, counts in mesa_voe_counters_t::rx/tx_counter
    // When true,  counts in mesa_voe_counters_t::rx/tx_selected_counter
    mesa_bool_t   count_as_selected;

    mesa_bool_t   ltm_cpu_copy;   // Copy all LTM PDUs to CPU
    mesa_bool_t   ltr_cpu_copy;   // Copy all LTR PDUs to CPU
} mesa_voe_lt_conf_t CAP(VOP_CFM);

// VOE Link Trace configuration set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// conf     [IN] Configuration parameters for LT.
mesa_rc mesa_voe_lt_conf_set(const mesa_inst_t          inst,
                             const mesa_voe_idx_t       voe_idx,
                             const mesa_voe_lt_conf_t   *const conf)  CAP(VOP_CFM);

mesa_rc mesa_voe_lt_conf_get(const mesa_inst_t      inst,
                             const mesa_voe_idx_t   voe_idx,
                             mesa_voe_lt_conf_t     *const conf)  CAP(VOP_CFM);

// VOE Loop Back configuration.
#define MESA_VOE_LBM_TRANSACTION_ID_NONE    0xFFFFFFFF
typedef struct {
    mesa_bool_t   enable;   // Enable LBM/LBR PDU handling in HW

    // Count PDU as selected.
    // When false, counts in mesa_voe_counters_t::rx/tx_counter
    // When true,  counts in mesa_voe_counters_t::rx/tx_selected_counter
    mesa_bool_t   count_as_selected;

    mesa_bool_t          lbm_cpu_copy;  // Copy all LBM PDUs to CPU
    mesa_oam_cpu_copy_t  lbr_cpu_copy;  // Control copy of LBR PDUs to CPU

    // LBM Transaction ID to use on Tx. Must be greater than zero.
    // Auto increment of transaction ID is always enabled.
    // MESA_VOE_LBM_TRANSACTION_ID_NONE means do not change.
    uint32_t             trans_id;
} mesa_voe_lb_conf_t CAP(VOP_CFM);

// VOE Loop Back configuration set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// conf     [IN] Configuration parameters for LB.
mesa_rc mesa_voe_lb_conf_set(const mesa_inst_t          inst,
                             const mesa_voe_idx_t       voe_idx,
                             const mesa_voe_lb_conf_t   *const conf)  CAP(VOP_CFM);

mesa_rc mesa_voe_lb_conf_get(const mesa_inst_t      inst,
                             const mesa_voe_idx_t   voe_idx,
                             mesa_voe_lb_conf_t     *const conf)  CAP(VOP_CFM);

// VOE Linear Automatic Protection Switching configuration.
typedef struct {
    mesa_bool_t   enable;   // Enable LAPS PDU handling in HW

    // Count PDU as selected.
    // When false, counts in mesa_voe_counters_t::rx/tx_counter
    // When true,  counts in mesa_voe_counters_t::rx/tx_selected_counter
    mesa_bool_t   count_as_selected;

    mesa_bool_t   cpu_copy;   // Copy all LAPS PDUs to CPU
} mesa_voe_laps_conf_t CAP(VOP_CFM);

// VOE Linear Automatic Protection Switch configuration set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// conf     [IN] Configuration parameters for LAPS.
mesa_rc mesa_voe_laps_conf_set(const mesa_inst_t            inst,
                               const mesa_voe_idx_t         voe_idx,
                               const mesa_voe_laps_conf_t   *const conf)  CAP(VOP_CFM);

mesa_rc mesa_voe_laps_conf_get(const mesa_inst_t      inst,
                               const mesa_voe_idx_t   voe_idx,
                               mesa_voe_laps_conf_t   *const conf)  CAP(VOP_CFM);

// VOE status.
typedef struct {
    // Indications that an OAM PDU has been seen.
    // Are cleared during call to mesa_voe_status_get().
    mesa_bool_t  opcode_unexp_seen;
    mesa_bool_t  dmac_unexp_seen;
    mesa_bool_t  tx_level_low_seen  CAP(VOP_CFM); // Tx with level low
    mesa_bool_t  version_unexp_seen CAP(VOP_V2);
    mesa_bool_t  rx_level_low_seen  CAP(VOP_V2);  // Rx with level low
    mesa_bool_t  rx_level_high_seen CAP(VOP_V2);  // Only if 'block_mel_high' is configured
} mesa_voe_status_t CAP(VOP);

// VOE status information get.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// status   [IN] Status information for VOE instance.
mesa_rc mesa_voe_status_get(const mesa_inst_t     inst,
                            const mesa_voe_idx_t  voe_idx,
                            mesa_voe_status_t     *const status)  CAP(VOP);

// VOE counters
typedef struct {
    // All the following counters are cleared during call to
    // mesa_voe_counters_clear().

    // OAM PDU Rx and Tx counters.
    uint64_t     rx_counter;
    uint64_t     tx_counter CAP(VOP_CFM);

    // Counters named '_selected_' are counting any OAM PDU type that is
    // configured to 'count_as_selected'.
    uint64_t     rx_selected_counter;
    uint64_t     tx_selected_counter CAP(VOP_CFM);

    // Rx/Tx PDUs that are discarded due to filtering
    uint64_t     rx_discard_counter CAP(VOP_V2);  // Check of MEL or DMAC or Version or CCM
    uint64_t     tx_discard_counter CAP(VOP_V2);  // Check of MEL
} mesa_voe_counters_t  CAP(VOP);

// Get VOE counters.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the configured VOE instance.
// counters [OUT] VOE counters.
mesa_rc mesa_voe_counters_get(const mesa_inst_t    inst,
                              const mesa_voe_idx_t voe_idx,
                              mesa_voe_counters_t  *counters)  CAP(VOP);

// VOE counter clear.
// Clear counters in mesa_voe_counters_t
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
mesa_rc mesa_voe_counters_clear(const mesa_inst_t     inst,
                                const mesa_voe_idx_t  voe_idx)  CAP(VOP);

// VOE CC status
typedef struct {
    // (period == 0) for last received CCM PDU
    mesa_bool_t  zero_period;

    // (RDI == 1) for last received CCM PDU
    mesa_bool_t  rdi;

    // dLOC (Loss Of Continuity defect) as described in G.8021 6.1.2
    mesa_bool_t  loc;

    // If MESA_CAP_VOP_CCM_DEFECT is TRUE then the following status is a defect
    // as described in G.8021 6.1.2.

    // (period != expected) for last received CCM PDU or dUNP (Unexpected
    // Periodicity defect) as described in G.8021 6.1.2
    mesa_bool_t  period_unexp;

    // (priority != expected) for last received CCM PDU or dUNPr (Unexpected
    // Priority defect) as described in G.8021 6.1.2
    mesa_bool_t  priority_unexp;

    // (MEP-ID != expected) for last received CCM PDU or dUNM (defect Unexpected
    // MEP defect) as described in G.8022 6.1.2
    mesa_bool_t  mep_id_unexp;

    // (MEG-ID != expected) for last received CCM PDU or dMMG (MisMerGe defect)
    // as described in G.8021 6.1.2
    mesa_bool_t  meg_id_unexp;

    // (MEL != expected) for last received CCM PDU or dUNL (Unexpected MEL
    // defect) as described in G.8021 6.1.2
    mesa_bool_t  mel_unexp  CAP(VOP_V2);

    // This CCM related status is based on the latest received CCM PDU.
    mesa_port_no_t  rx_port  CAP(VOP_V2);          // The ingress port
    uint8_t         port_status_tlv  CAP(VOP_V2);  // Port Status TLV value
    uint8_t         if_status_tlv  CAP(VOP_V2);    // Interface Status TLV value

    // Indications that a CCM PDU has been seen.
    // Are cleared during call to mesa_voe_cc_status_get()
    mesa_bool_t  seen;
    mesa_bool_t  tlv_seen  CAP(VOP_V2);        // With TLV
    mesa_bool_t  seq_unexp_seen  CAP(VOP_V2);  // With unexpected sequence number
} mesa_voe_cc_status_t CAP(VOP);

// VOE Continuity Check status get.
//
// When CCM G.8021 defects are not supported in VOE (MESA_CAP_VOP_CCM_DEFECT ==
// false), it can be calculated by application like this:
// mesa_voe_event_get(NULL, voe_idx, &mask);
// mesa_voe_cc_status_get(NULL, voe_idx, &status);
// if (mask | MESA_VOE_EVENT_CCM_PERIOD) {  // Period event detected
//    if (status.period_unexp) {   // Unexpected Period received
//        dUNP = true;
//        Cancel dUNP clear timer;
//    } else {                     // Expected Period received
//        Start dUNP clear timer with the longest period received
//        in CCM PDU with unexpected period;
//    }
// }
// if (dUNP clear time out) {   // Time out of the dUNP clear timer
//     dUNP = false;
// }
//
// The above will give a clear timer that is longer that specified in G.8021 6.1.3.
// The clear timer should have been started when the last CCM PDU with
// unexpected Period was received.
//
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the VOE instance.
// status   [OUT] CCM status information.
mesa_rc mesa_voe_cc_status_get(const mesa_inst_t     inst,
                               const mesa_voe_idx_t  voe_idx,
                               mesa_voe_cc_status_t  *status)  CAP(VOP);

// VOE CC Counters
typedef struct {
    // CCM PDU Rx and Tx counters
    // Are cleared during call to mesa_voe_cc_counters_clear()
    uint64_t  rx_valid_counter;
    uint64_t  rx_invalid_counter;
    uint64_t  rx_oo_counter;  // Out of Order sequence numbers counter
    uint64_t  tx_counter;
} mesa_voe_cc_counters_t  CAP(VOP);

// Get VOE Continuity Check counters.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
// counters [OUT] CC counters.
mesa_rc mesa_voe_cc_counters_get(const mesa_inst_t      inst,
                                 const mesa_voe_idx_t   voe_idx,
                                 mesa_voe_cc_counters_t *counters)  CAP(VOP);

// VOE Continuity Check counters clear.
// Clear CC counters in mesa_voe_cc_counters_t
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
mesa_rc mesa_voe_cc_counters_clear(const mesa_inst_t     inst,
                                   const mesa_voe_idx_t  voe_idx)  CAP(VOP);

// VOE Link Trace status
typedef struct {
    // Indications that an LT PDU has been seen.
    // Are cleared during call to mesa_voe_lt_status_get()
    mesa_bool_t   ltm_seen;
    mesa_bool_t   ltr_seen;
} mesa_voe_lt_status_t CAP(VOP_CFM);

// VOE Link Trace status get.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the VOE instance.
// status   [OUT] LT status.
mesa_rc mesa_voe_lt_status_get(const mesa_inst_t      inst,
                               const mesa_voe_idx_t   voe_idx,
                               mesa_voe_lt_status_t   *status)  CAP(VOP_CFM);

// VOE Loop Back status.
typedef struct {
    // Indications that an LB PDU has been seen.
    // Are cleared during call to mesa_voe_lb_status_get()
    mesa_bool_t   lbm_seen;
    mesa_bool_t   lbr_seen;
    mesa_bool_t   trans_unexp_seen CAP(VOP_V2);  // LBR PDU with unexpected transaction ID

    uint32_t   tx_trans_id;         // The next transmitted transaction ID
    uint32_t   rx_trans_id;         // The last received transaction ID
} mesa_voe_lb_status_t CAP(VOP_CFM);

/* VOE Loop Back status get.
 * inst     [IN]  Target instance reference.
 * voe_idx  [IN]  Index of the VOE instance.
 * status   [OUT] LB status. */
mesa_rc mesa_voe_lb_status_get(const mesa_inst_t      inst,
                               const mesa_voe_idx_t   voe_idx,
                               mesa_voe_lb_status_t   *status)  CAP(VOP_CFM);

// VOE LB counters
typedef struct {
    // LB PDU Rx and Tx counters
    // Are cleared during call to mesa_voe_lb_counters_clear()
    uint64_t   rx_lbr_counter;
    uint64_t   tx_lbm_counter;
    uint64_t   rx_lbr_oo_counter;               // Out of Order sequence numbers counter
    uint64_t   rx_lbr_crc_counter  CAP(VOP_V2); // Test TLV that has CRC error counter
    uint64_t   tx_lbr_counter      CAP(VOP_V2);
} mesa_voe_lb_counters_t  CAP(VOP_CFM);

// Get VOE Loop Back counters.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the VOE instance.
// counters [OUT] LB counters.
mesa_rc mesa_voe_lb_counters_get(const mesa_inst_t      inst,
                                 const mesa_voe_idx_t   voe_idx,
                                 mesa_voe_lb_counters_t *counters)  CAP(VOP_CFM);

// VOE Loop Back counters clear.
// Clear LB counters in mesa_voe_lb_status_t
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
mesa_rc mesa_voe_lb_counters_clear(const mesa_inst_t     inst,
                                  const mesa_voe_idx_t  voe_idx)  CAP(VOP_CFM);

// VOE Linear Automatic Protection Switch status
typedef struct {
    // Indications that a LAPS PDU has been seen.
    // Are cleared during call to mesa_voe_laps_status_get()
    mesa_bool_t   seen;
} mesa_voe_laps_status_t CAP(VOP_CFM);

// VOE Linear Automatic Protection Switch status get.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the VOE instance.
// status   [OUT] LAPS status.
mesa_rc mesa_voe_laps_status_get(const mesa_inst_t        inst,
                                 const mesa_voe_idx_t     voe_idx,
                                 mesa_voe_laps_status_t   *status)  CAP(VOP_CFM);

// VOE event active state get
// Get bit mask array indicating VOEs with active events.
// Function called by interrupt or periodically.
// inst        [IN]  Target instance reference.
// active_size [IN]  The size of the active event mask array.
//                   Must be MESA_CAP_VOP_EVENT_ARRAY_SIZE.
// active      [OUT] Active event mask array. The LSBit of active[0] is VOE
//                   index 0.
mesa_rc mesa_voe_event_active_get(const mesa_inst_t   inst,
                                  const uint32_t      active_size,
                                  uint32_t            *const active)  CAP(VOP);

// VOE Event indication flags.
// Different events can be enabled/disabled and polled.
// The events are represented by a bit in an event mask.
// MESA_CAP(MESA_CAP_VOP_EVENT_SUPPORTED) will return an event mask with the
// events supported on a given platform
#define MESA_VOE_EVENT_MASK_NONE                0x000
// Period check state changed
#define MESA_VOE_EVENT_MASK_CCM_PERIOD          0x001
// Period zero check state changed
#define MESA_VOE_EVENT_MASK_CCM_ZERO_PERIOD     0x002
// Priority check state changed
#define MESA_VOE_EVENT_MASK_CCM_PRIORITY        0x004
// Loss Of Continuity state changed
#define MESA_VOE_EVENT_MASK_CCM_LOC             0x008
// MEP ID state changed
#define MESA_VOE_EVENT_MASK_CCM_MEP_ID          0x010
// MEG ID state changed
#define MESA_VOE_EVENT_MASK_CCM_MEG_ID          0x020
// MEG Level state changed
#define MESA_VOE_EVENT_MASK_CCM_MEG_LEVEL       0x040
// RDI flag value changed
#define MESA_VOE_EVENT_MASK_CCM_RX_RDI          0x080
// Rx source port move detected
#define MESA_VOE_EVENT_MASK_CCM_SRC_PORT_MOVE   0x100
// Port status TLV value changed
#define MESA_VOE_EVENT_MASK_CCM_TLV_PORT_STATUS 0x200
// Interface status TLV value changed
#define MESA_VOE_EVENT_MASK_CCM_TLV_IF_STATUS   0x400
#define MESA_VOE_EVENT_MASK_ALL                 0xFFF

// VOE event generation enable/disable.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// mask     [IN] Mask of events to either enable or disable.
// enable   [IN] Whether to enable or disable the events specified in the mask.
mesa_rc mesa_voe_event_mask_set(const mesa_inst_t     inst,
                                const mesa_voe_idx_t  voe_idx,
                                const uint32_t        mask,
                                const mesa_bool_t     enable)  CAP(VOP);

mesa_rc mesa_voe_event_mask_get(const mesa_inst_t     inst,
                                const mesa_voe_idx_t  voe_idx,
                                uint32_t              *const mask)  CAP(VOP);

// VOE event polling.
// Mask is returned indicating pending events. Pending event are cleared after get.
// inst      [IN]  Target instance reference.
// voe_idx   [IN]  Index of polled VOE instance.
// mask      [OUT] Mask of detected pending events during get.
mesa_rc mesa_voe_event_get(const mesa_inst_t     inst,
                           const mesa_voe_idx_t  voe_idx,
                           uint32_t              *const mask)  CAP(VOP);




// -------------------------------------------------------------------------
// --- VOI - Versatile OAM Intermediate point     --------------------------
// --- Note that in registers this is called MIP  --------------------------
// -------------------------------------------------------------------------

// VOI Allocation structure.
typedef struct {
    mesa_port_no_t        port;
    mesa_oam_direction_t  direction;
} mesa_voi_allocation_t CAP(VOP_V2);

// Allocate a VOI.
// inst      [IN]  Target instance reference.
// param     [IN]  Allocation parameters
// voi_idx   [OUT] Index of allocated VOI instance.
//                 this index can be used when creating VCE or TCE entries
mesa_rc mesa_voi_alloc(const mesa_inst_t            inst,
                       const mesa_voi_allocation_t  *const param,
                       mesa_voi_idx_t               *const voi_idx)  CAP(VOP_V2);

// Free a VOI.
// inst      [IN] Target instance reference.
// voi_idx   [IN] Index of previously allocated VOI instance.
mesa_rc mesa_voi_free(const mesa_inst_t       inst,
                      const mesa_voi_idx_t    voi_idx)  CAP(VOP_V2);

// VOI APS PDU handling.
typedef enum {
    MESA_OAM_RAPS_HANDLING_NONE,        // RAPS PDUs are not handled
    MESA_OAM_RAPS_HANDLING_COPY_CPU,    // RAPS PDUs are copied to CPU
    MESA_OAM_RAPS_HANDLING_REDIR_CPU,   // RAPS PDUs are redirected to CPU
    MESA_OAM_RAPS_HANDLING_DISCARD,     // RAPS PDUs are discarded
} mesa_oam_raps_handling_t CAP(VOP_V2);

// VOI configuration.
typedef struct {
    mesa_bool_t               enable;         // Enable the VOI
    mesa_mac_t                unicast_mac;    // The VOI unicast MAC
    uint32_t                  meg_level;      // MEG Level (MEL)
    mesa_bool_t               lbm_cpu_redir;  // Enable LBM redirect to CPU
    mesa_bool_t               ltm_cpu_redir;  // Enable LTM redirect to CPU
    mesa_oam_raps_handling_t  raps_handling;  // Control handling of RAPS PDUs
} mesa_voi_conf_t CAP(VOP_V2);

// VOI configuration set.
// inst      [IN] Target instance reference.
// voi_idx   [IN] Index of the configured VOI instance.
// conf      [IN] Configuration parameters for VOI.
mesa_rc mesa_voi_conf_set(const mesa_inst_t       inst,
                          const mesa_voi_idx_t    voi_idx,
                          const mesa_voi_conf_t   *const conf)  CAP(VOP_V2);

mesa_rc mesa_voi_conf_get(const mesa_inst_t      inst,
                          const mesa_voi_idx_t   voi_idx,
                          mesa_voi_conf_t        *const conf)  CAP(VOP_V2);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_VOP_

