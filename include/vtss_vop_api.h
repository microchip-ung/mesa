// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_VOP_API_H_
#define _VTSS_VOP_API_H_

#include <vtss/api/types.h>

#if defined(VTSS_FEATURE_VOP)
#ifdef __cplusplus
extern "C" {
#endif

#if defined(VTSS_FEATURE_VOP_V0)     /* VOP V0 */

#  define VTSS_DOWN_VOI_CNT           (0)                         // No VOIs (MIPs) in HW
#  define VTSS_UP_VOI_CNT             (0)                         // No VOIs (MIPs) in HW.
#  if defined(VTSS_ARCH_LAN966X)   /* Maserati */
#    define VTSS_PORT_VOE_CNT           (8)                        // Number of port VOEs in HW
#    define VTSS_PATH_SERVICE_VOE_CNT   (0)                        // Number of path/service VOEs in HW
#    define VTSS_PORT_VOE_BASE_IDX      (0)                        // Index of first port VOE
#  else
#    error "not defined expected architure for VOP V0"
#  endif

#elif defined(VTSS_FEATURE_VOP_V1)     /* VOP V1 */

#  define VTSS_DOWN_VOI_CNT           (0)                         // No VOIs (MIPs) in HW
#  define VTSS_UP_VOI_CNT             (0)                         // No VOIs (MIPs) in HW.
#  if defined(VTSS_ARCH_OCELOT)   /* Ocelot */
#    define VTSS_PORT_VOE_CNT           (11)                        // Number of port VOEs in HW
#    define VTSS_PATH_SERVICE_VOE_CNT   (32)                        // Number of path/service VOEs in HW
#    define VTSS_PORT_VOE_BASE_IDX      (32)                        // Index of first port VOE
#  elif defined(VTSS_ARCH_LAN966X)   /* Maserati */
#    define VTSS_PORT_VOE_CNT           (8)                        // Number of port VOEs in HW
#    define VTSS_PATH_SERVICE_VOE_CNT   (0)                        // Number of path/service VOEs in HW
#    define VTSS_PORT_VOE_BASE_IDX      (0)                        // Index of first port VOE
#  else
#    error "not defined expected architure for VOP V1"
#  endif

#elif defined(VTSS_FEATURE_VOP_V2)  /* End VOP V1 */
                                    /* Begin VOP V2*/
#  if defined(VTSS_ARCH_SERVAL_T)     /* ServalT */

#    define VTSS_PATH_SERVICE_VOE_CNT   (192)                       // Number of path/service VOEs in HW
#    define VTSS_PORT_VOE_BASE_IDX      (192)                       // Index of first port VOE
#    define VTSS_PORT_VOE_CNT           (11)                        // Number of port VOEs in HW

#    define VTSS_DOWN_VOI_CNT           (128)                       // Number of down VOI (MIP) in HW
#    define VTSS_UP_VOI_CNT             (127)                       // Number of up VOI (MIP) in HW. Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB

#  else                               /* End ServalT */

#    define VTSS_PATH_SERVICE_VOE_CNT   (1024)                      // Number of path/service VOEs in HW
#    define VTSS_PORT_VOE_BASE_IDX      (1024)                      // Index of first port VOE

#    if defined(VTSS_ARCH_JAGUAR_2)     /* Jaguar2 */
#      define VTSS_PORT_VOE_CNT           (53)                        // Number of port VOEs in HW
#    elif defined(VTSS_ARCH_SPARX5)     /* SparX-5 */
#      define VTSS_PORT_VOE_CNT           (65)                        // Number of port VOEs in HW
#    else
#      error "not defined expected architure for VOP V2"
#    endif

#    define VTSS_DOWN_VOI_CNT           (1024)                      // Number of down VOI (MIP) in HW
#    define VTSS_UP_VOI_CNT             (1023)                      // Number of up VOI (MIP) in HW. Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB
#  endif

#else                               /* End VOP V2 */
#  error "VOP V1 or V2 must be defined"
#endif


#define VTSS_VOE_CNT                ((VTSS_PATH_SERVICE_VOE_CNT) + (VTSS_PORT_VOE_CNT))   // Total count of port + path/service VOEs
#define VTSS_VOI_CNT                ((VTSS_DOWN_VOI_CNT) + (VTSS_UP_VOI_CNT))             // Total count of down and up VOIs
#define VTSS_EVENT_MASK_ARRAY_SIZE  ((VTSS_VOE_CNT+31)/32)                                // Size in u32's of event mask array used by vtss_voe_event_active_get()


// -------------------------------------------------------------------------
// --- VOP - Vitesse OAM Processor -----------------------------------------
// -------------------------------------------------------------------------

// VOP configuration. Once the VOP is configured, VOEs can be configured.
typedef struct {
    vtss_mac_t  multicast_dmac;      // Common MC DMAC for all VOEs

#if defined(VTSS_FEATURE_VOP_V2)
    u32         auto_copy_period[2]; // Timer period values in microseconds, used for auto copy to CPU (auto "hit me once").
                                     // A value of 0 disables the timer.
    u8          auto_copy_ccm_valid; // #auto_copy_period timer (0 or 1) to use for auto copy next valid CCM to CPU.
    u8          auto_copy_ccm_tlv;   // #auto_copy_period timer (0 or 1) to use for auto copy to CPU if CCM has more TLVs than port and
                                     // interface status.
    u8          auto_copy_ccm_err;   // #auto_copy_period timer (0 or 1) to use for auto copy to CPU if CCM validation fails
                                     // (including MEG level too low).
    u8          auto_copy_lbr;       // #auto_copy_period timer (0 or 1) to use for auto copy next or LBR (or non-OAM message) to CPU.
#endif

    // CPU extraction queues to use for the various packet types
    vtss_packet_rx_queue_t  voe_queue_ccm;
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_packet_rx_queue_t  voe_queue_lt;   // LTM, LTR common settings
    vtss_packet_rx_queue_t  voe_queue_lbm;
    vtss_packet_rx_queue_t  voe_queue_lbr;
    vtss_packet_rx_queue_t  voe_queue_aps;  // LAPS and RAPS
#endif
    vtss_packet_rx_queue_t  voe_queue_err;
#if defined(VTSS_FEATURE_VOP_V2)
    vtss_packet_rx_queue_t  voi_queue;
#endif
#if defined(VTSS_FEATURE_MRP)
    vtss_packet_rx_queue_t  mrp_queue;
#endif
} vtss_vop_conf_t;

// Set VOP configuration.
// inst  [IN]  Target instance reference.
// conf  [IN] New configuration for the VOP.
vtss_rc vtss_vop_conf_set(const vtss_inst_t       inst,
                          const vtss_vop_conf_t   *const conf);

vtss_rc vtss_vop_conf_get(const vtss_inst_t  inst,
                          vtss_vop_conf_t    *const cfg);




// -------------------------------------------------------------------------
// --- VOE - Versatile OAM End point ---------------------------------------
// -------------------------------------------------------------------------

// VOE type -- Service/Path or Port
typedef enum {
    VTSS_VOE_TYPE_SERVICE,
    VTSS_VOE_TYPE_PORT,
} vtss_voe_type_t;

// VOE/VOI direction
typedef enum {
    VTSS_OAM_DIRECTION_DOWN,
    VTSS_OAM_DIRECTION_UP,
} vtss_oam_direction_t;

// VOE Allocation structure.
typedef struct {
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_voe_type_t       type;
#endif
    vtss_port_no_t        port;
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_oam_direction_t  direction;
#endif
} vtss_voe_allocation_t;

// Allocate a VOE.
// inst      [IN]  Target instance reference.
// param     [IN]  Allocation parameters
// voe_idx   [OUT] Index of allocated VOE instance.
vtss_rc vtss_voe_alloc(const vtss_inst_t            inst,
                       const vtss_voe_allocation_t  *const param,
                       vtss_voe_idx_t               *const voe_idx);

// Free a VOE. If it's still enabled, it will also be disabled.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of previously allocated VOE instance.
vtss_rc vtss_voe_free(const vtss_inst_t     inst,
                      const vtss_voe_idx_t  voe_idx);

// Kind of DMAC check to perform on incoming OAM PDUs
typedef enum {
    VTSS_VOE_DMAC_CHECK_UNICAST,    // Check unicast DMAC
    VTSS_VOE_DMAC_CHECK_MULTICAST,  // Check multicast DMAC
    VTSS_VOE_DMAC_CHECK_BOTH,       // Check both uni and multicast DMAC
    VTSS_VOE_DMAC_CHECK_NONE        // No Check of DMAC
} vtss_voe_dmac_check_t;

// VOE Basic configuration structure.
typedef struct {
    BOOL                   enable;          // Enable the VOE
    vtss_mac_t             unicast_mac;     // This VOE's unicast MAC
    u8                     meg_level;       // MEG Level (MEL)
    vtss_voe_dmac_check_t  dmac_check_type; // Kind of DMAC check to perform
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_iflow_id_t        loop_iflow_id;   // Loop ingress flow id
#endif
#if defined(VTSS_FEATURE_VOP_V2)
    // Block OAM PDUs with MEG level higher than the VOE MEG level
    BOOL                   block_mel_high;
#endif
#if defined(VTSS_FEATURE_VOP_TAGGING)
    vtss_port_max_tags_t   tagging;         // OAM PDU is behind this many tags
#endif
} vtss_voe_conf_t;

// Set VOE configuration.
// Note that RDI and hitme configuration must be (re-)applied after
// a call to this function.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of VOE configuration to get.
// conf     [IN] New configuration for the VOE.
vtss_rc vtss_voe_conf_set(const vtss_inst_t      inst,
                          const vtss_voe_idx_t   voe_idx,
                          const vtss_voe_conf_t  *const conf);

vtss_rc vtss_voe_conf_get(const vtss_inst_t      inst,
                          const vtss_voe_idx_t   voe_idx,
                          vtss_voe_conf_t        *const conf);


// Supported OAM periods for CCM
typedef enum {
    VTSS_VOE_CCM_PERIOD_3_3_MS,
    VTSS_VOE_CCM_PERIOD_10_MS,
    VTSS_VOE_CCM_PERIOD_100_MS,
    VTSS_VOE_CCM_PERIOD_1_SEC,
#if defined(VTSS_FEATURE_VOP_V2)
    VTSS_VOE_CCM_PERIOD_10_SEC
#endif
} vtss_voe_ccm_period_t;

// VOE/VOI CPU copy selection.
typedef enum {
    VTSS_OAM_CPU_COPY_NONE,
    VTSS_OAM_CPU_COPY_ALL,

#if defined(VTSS_FEATURE_VOP_V2)
    // The PDUs are auto-copied to CPU based on 'vtss_vop_conf_t.auto_copy_xxx'
    // period selector.
    VTSS_OAM_CPU_COPY_AUTO
#endif
} vtss_oam_cpu_copy_t;

// VOE CC configuration.
#define VTSS_OAM_MEG_ID_LENGTH  48     // The MEG-ID length
typedef struct {
    BOOL                   enable;         // Enable CCM PDU handling in HW
    vtss_oam_cpu_copy_t    cpu_copy;       // Control copy of CCM PDUs to CPU
    BOOL                   seq_no_update;  // Update TX CCM sequence number

    // Count PDU as selected.
    // There is one counter in vtss_voe_counters_t that counts any
    // OAM PDU type that is configured to 'count_as_selected'.
    BOOL                   count_as_selected;

    // Expected received CCM PDU period.
    vtss_voe_ccm_period_t  expected_period;

    // Expected received CCM PDU Priority
    u8                     expected_priority;

    // Expected received CCM PDU MEG-ID.
    u8                     expected_megid[VTSS_OAM_MEG_ID_LENGTH];

    // Expected received CCM_PDU peer MEP-ID.
    u16                    expected_peer_mepid;
} vtss_voe_cc_conf_t;

// VOE Continuity Check configuration set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// conf     [IN] Configuration parameters for CC.
vtss_rc vtss_voe_cc_conf_set(const vtss_inst_t         inst,
                             const vtss_voe_idx_t      voe_idx,
                             const vtss_voe_cc_conf_t  *const conf);

vtss_rc vtss_voe_cc_conf_get(const vtss_inst_t      inst,
                             const vtss_voe_idx_t   voe_idx,
                             vtss_voe_cc_conf_t     *const conf);

// VOE Continuity Check RDI status set.
// This RDI is inserted in transmitted CCM if CC is enabled.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
// rdi      [IN] The CCM RDI status.
vtss_rc vtss_voe_cc_rdi_set(const vtss_inst_t     inst,
                            const vtss_voe_idx_t  voe_idx,
                            const BOOL            rdi);

vtss_rc vtss_voe_cc_rdi_get(const vtss_inst_t     inst,
                            const vtss_voe_idx_t  voe_idx,
                            BOOL                  *const rdi);

// VOE Continuity Check copy next received CC PDU to CPU set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
vtss_rc vtss_voe_cc_cpu_copy_next_set(const vtss_inst_t     inst,
                                      const vtss_voe_idx_t  voe_idx);
#if defined(VTSS_FEATURE_VOP_CFM)
// VOE LT configuration.
typedef struct {
    BOOL   enable;   // Enable LT PDU handling in HW

    // Count PDU as selected. */
    // There is one counter in vtss_voe_counters_t that counts any
    // OAM PDU type that is configured to 'count_as_selected'. */
    BOOL   count_as_selected;

    BOOL   ltm_cpu_copy;   // Copy all LTM PDUs to CPU
    BOOL   ltr_cpu_copy;   // Copy all LTR PDUs to CPU
} vtss_voe_lt_conf_t;

// VOE Link Trace configuration set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// conf     [IN] Configuration parameters for LT.
vtss_rc vtss_voe_lt_conf_set(const vtss_inst_t          inst,
                             const vtss_voe_idx_t       voe_idx,
                             const vtss_voe_lt_conf_t   *const conf);

vtss_rc vtss_voe_lt_conf_get(const vtss_inst_t      inst,
                             const vtss_voe_idx_t   voe_idx,
                             vtss_voe_lt_conf_t     *const conf);

// VOE LB configuration.
#define VTSS_VOE_LBM_TRANSACTION_ID_NONE    0xFFFFFFFF
typedef struct {
    BOOL   enable;   // Enable LBM/LBR PDU handling in HW

    // Count PDU as selected. */
    // There is one counter in vtss_voe_counters_t that counts any
    // OAM PDU type that is configured to 'count_as_selected'.
    BOOL   count_as_selected;

    BOOL                 lbm_cpu_copy;  // Copy all LBM PDUs to CPU
    vtss_oam_cpu_copy_t  lbr_cpu_copy;  // Control copy of LBR PDUs to CPU

    // LBM Transaction ID to use on Tx. VTSS_VOE_LBM_TRANSACTION_ID_NONE means unchanged.
    // Auto increment of Tx LBM transaction ID is always enabled
    u32                  trans_id;
} vtss_voe_lb_conf_t;

// VOE Loop Back configuration set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// conf     [IN] Configuration parameters for LB.
vtss_rc vtss_voe_lb_conf_set(const vtss_inst_t          inst,
                             const vtss_voe_idx_t       voe_idx,
                             const vtss_voe_lb_conf_t   *const conf);

vtss_rc vtss_voe_lb_conf_get(const vtss_inst_t      inst,
                             const vtss_voe_idx_t   voe_idx,
                             vtss_voe_lb_conf_t     *const conf);

// VOE LAPS configuration.
typedef struct {
    BOOL   enable;   // Enable LAPS PDU handling in HW

    // Count PDU as selected.
    // There is one counter in vtss_voe_counters_t that counts any
    // OAM PDU type that is configured to 'count_as_selected'.
    BOOL   count_as_selected;

    BOOL   cpu_copy;   // Copy all LAPS PDUs to CPU
} vtss_voe_laps_conf_t;

// VOE Linear Automatic Protection Switch configuration set.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// conf     [IN] Configuration parameters for LAPS.
vtss_rc vtss_voe_laps_conf_set(const vtss_inst_t            inst,
                               const vtss_voe_idx_t         voe_idx,
                               const vtss_voe_laps_conf_t   *const conf);

vtss_rc vtss_voe_laps_conf_get(const vtss_inst_t      inst,
                               const vtss_voe_idx_t   voe_idx,
                               vtss_voe_laps_conf_t   *const conf);
#endif

// VOE status.
typedef struct {
    // Indications that a OAM PDU has been seen.
    // Are cleared during call to vtss_voe_status_get().
    BOOL  opcode_unexp_seen;
    BOOL  dmac_unexp_seen;
#if defined(VTSS_FEATURE_VOP_CFM)
    BOOL  tx_level_low_seen;   // TX with level low
#endif
#if defined(VTSS_FEATURE_VOP_V2)
    BOOL  version_unexp_seen;
    BOOL  rx_level_low_seen;   // RX with level low
    BOOL  rx_level_high_seen;  // Only if 'block_mel_high' is configured
#endif
} vtss_voe_status_t;

// VOE status information get.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// status   [IN] Status information for VOE instance.
vtss_rc vtss_voe_status_get(const vtss_inst_t     inst,
                            const vtss_voe_idx_t  voe_idx,
                            vtss_voe_status_t     *const status);

// VOE counters
typedef struct {
    // All the following counters are cleared
    // during call to vtss_voe_counters_clear().

    // OAM PDU RX and TX counters.
    u64   rx_counter;
#if defined(VTSS_FEATURE_VOP_CFM)
    u64   tx_counter;
#endif
    // Counters named '_selected_' is counting any OAM PDU type
    // that is configured to 'count_as_selected'.
    u64   rx_selected_counter;
#if defined(VTSS_FEATURE_VOP_CFM)
    u64   tx_selected_counter;
#endif
#if defined(VTSS_FEATURE_VOP_V2)
    // Rx/Tx PDUs that are discarded due to filtering
    u64   rx_discard_counter;  // Check of MEL or DMAC or Version or CCM
    u64   tx_discard_counter;  // Check of MEL
#endif
} vtss_voe_counters_t;

// Get VOE counters.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the configured VOE instance.
// counters [OUT] VOE counters.
vtss_rc vtss_voe_counters_get(const vtss_inst_t    inst,
                              const vtss_voe_idx_t voe_idx,
                              vtss_voe_counters_t  *counters);

// VOE counters clear.
// Clear counters in vtss_voe_counters_t
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
vtss_rc vtss_voe_counters_clear(const vtss_inst_t     inst,
                                const vtss_voe_idx_t  voe_idx);

// VOE CC status
typedef struct {
    // (period == 0) for last received CCM PDU
    BOOL  zero_period;

    // (RDI == 1) for last received CCM PDU
    BOOL  rdi;

    // dLOC as described in G.8021 6.1.2
    BOOL  loc;

    // If VTSS_ARCH_SPARX5 is TRUE then the following status
    // is a defect as described in G.8021 6.1.2.

    // (period != expected) for last received CCM PDU or
    // dUNP as described in G.8021 6.1.2
    BOOL  period_unexp;

    // (priority != expected) for last received CCM PDU or
    // dUNPr as described in G.8021 6.1.2
    BOOL  priority_unexp;

    // (MEP-ID != expected) for last received CCM PDU or
    // dUNM as described in G.8021 6.1.2
    BOOL  mep_id_unexp;

    // (MEG-ID != expected) for last received CCM PDU or
    // dMMG as described in G.8021 6.1.2
    BOOL  meg_id_unexp;
#if defined(VTSS_FEATURE_VOP_V2)
    // (MEL != expected) for last received CCM PDU or
    // dUNL as described in G.8021 6.1.2
    BOOL  mel_unexp;

    // This CCM related status is based on the latest received CCM PDU.
    vtss_port_no_t  rx_port;          // The ingress port
    u8              port_status_tlv;  // Port Status TLV value
    u8              if_status_tlv;    // Interface Status TLV value
#endif
    // Indications that a CCM PDU has been seen.
    // Are cleared during call to vtss_voe_cc_status_get()
    BOOL  seen;
#if defined(VTSS_FEATURE_VOP_V2)
    BOOL  tlv_seen;        // With TLV
    BOOL  seq_unexp_seen;  // With unexpected sequence number
#endif
} vtss_voe_cc_status_t;

// VOE Continuity Check status get.
//
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the VOE instance.
// status   [OUT] CCM status information.
vtss_rc vtss_voe_cc_status_get(const vtss_inst_t     inst,
                               const vtss_voe_idx_t  voe_idx,
                               vtss_voe_cc_status_t  *status);

// VOE CC Counters
typedef struct {
    // CCM PDU RX and TX counters
    // Are cleared during call to vtss_voe_cc_counters_clear()
    u64  rx_valid_counter;
    u64  rx_invalid_counter;
    u64  rx_oo_counter;  // Out of Order sequence numbers counter
    u64  tx_counter;
} vtss_voe_cc_counters_t;

// Get VOE Continuity Check counters.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
// counters [OUT] CC counters.
vtss_rc vtss_voe_cc_counters_get(const vtss_inst_t      inst,
                                 const vtss_voe_idx_t   voe_idx,
                                 vtss_voe_cc_counters_t *counters);

// VOE Continuity Check counter clear.
// Clear CC counters in vtss_voe_cc_counters_t
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
vtss_rc vtss_voe_cc_counters_clear(const vtss_inst_t     inst,
                                   const vtss_voe_idx_t  voe_idx);

#if defined(VTSS_FEATURE_VOP_CFM)
// VOE LT status
typedef struct {
    // Indications that a LT PDU has been seen.
    // Are cleared during call to vtss_voe_lt_status_get()
    BOOL   ltm_seen;
    BOOL   ltr_seen;
} vtss_voe_lt_status_t;

// VOE Link Trace status get.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the VOE instance.
// status   [OUT] LT status.
vtss_rc vtss_voe_lt_status_get(const vtss_inst_t      inst,
                               const vtss_voe_idx_t   voe_idx,
                               vtss_voe_lt_status_t   *status);

// VOE LB status.
typedef struct {
    // Indications that a LB PDU has been seen.
    // Are cleared during call to vtss_voe_lb_status_get()
    BOOL   lbm_seen;
    BOOL   lbr_seen;
#if defined(VTSS_FEATURE_VOP_V2)
    BOOL   trans_unexp_seen;  // LBR PDU with unexpected transaction id
#endif
    u32    tx_trans_id;         // The next transmitted transaction id
    u32    rx_trans_id;         // The last received transaction id
} vtss_voe_lb_status_t;

/* VOE Loop Back status get.
 * inst     [IN]  Target instance reference.
 * voe_idx  [IN]  Index of the VOE instance.
 * status   [OUT] LB status. */
vtss_rc vtss_voe_lb_status_get(const vtss_inst_t      inst,
                               const vtss_voe_idx_t   voe_idx,
                               vtss_voe_lb_status_t   *status);

// VOE LB counters
typedef struct {
    // LB PDU RX and TX counters
    // Are cleared during call to vtss_voe_lb_counters_clear()
    u64    rx_lbr_counter;
    u64    tx_lbm_counter;
    u64    rx_lbr_oo_counter;   // Out of Order sequence numbers counter
#if defined(VTSS_FEATURE_VOP_V2)
    u64    rx_lbr_crc_counter;  // Test TLV that has CRC error counter
    u64    tx_lbr_counter;
#endif
} vtss_voe_lb_counters_t;

// Get VOE Loop Back counters.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the VOE instance.
// counters [OUT] LB counters.
vtss_rc vtss_voe_lb_counters_get(const vtss_inst_t      inst,
                                 const vtss_voe_idx_t   voe_idx,
                                 vtss_voe_lb_counters_t *counters);

// VOE Loop Back counters clear.
// Clear LB counters in vtss_voe_lb_counters_t
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the VOE instance.
vtss_rc vtss_voe_lb_counters_clear(const vtss_inst_t     inst,
                                   const vtss_voe_idx_t  voe_idx);

// VOE LAPS status
typedef struct {
    // Indications that a LAPS PDU has been seen.
    // Are cleared during call to vtss_voe_laps_status_get()
    BOOL  seen;
} vtss_voe_laps_status_t;

// VOE Linear Automatic Protection Switch status get.
// inst     [IN]  Target instance reference.
// voe_idx  [IN]  Index of the VOE instance.
// status   [OUT] LAPS status.
vtss_rc vtss_voe_laps_status_get(const vtss_inst_t        inst,
                                 const vtss_voe_idx_t     voe_idx,
                                 vtss_voe_laps_status_t   *status);
#endif

// VOE event active state get
// Get bit mask array indicating VOEs with active events.
// Function called by interrupt or periodically.
// inst        [IN]  Target instance reference.
// active_size [IN]  The size of the active event mask array.
//                   Must be VTSS_EVENT_MASK_ARRAY_SIZE.
// active      [OUT] Active event mask array. The LSB of active[0] is VOE index 0.
vtss_rc vtss_voe_event_active_get(const vtss_inst_t   inst,
                                  const u32           active_size,
                                  u32                 *const active);

// VOE Event indication flags.
// Different events can be enabled/disabled and polled.
// The events are represented by a bit in an event mask.
#define VTSS_VOE_EVENT_MASK_NONE                0x000
// Period check state changed
#define VTSS_VOE_EVENT_MASK_CCM_PERIOD          0x001
// Period zero check state changed
#define VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD     0x002
// Priority check state changed
#define VTSS_VOE_EVENT_MASK_CCM_PRIORITY        0x004
// Loss Of Continuity state changed
#define VTSS_VOE_EVENT_MASK_CCM_LOC             0x008
// MEP ID state changed
#define VTSS_VOE_EVENT_MASK_CCM_MEP_ID          0x010
// MEG ID state changed
#define VTSS_VOE_EVENT_MASK_CCM_MEG_ID          0x020
// MEG Level state changed
#define VTSS_VOE_EVENT_MASK_CCM_MEG_LEVEL       0x040
// RDI flag value changed
#define VTSS_VOE_EVENT_MASK_CCM_RX_RDI          0x080
#if defined(VTSS_FEATURE_VOP_V2)
// Rx source port move detected
#define VTSS_VOE_EVENT_MASK_CCM_SRC_PORT_MOVE   0x100
// Port status TLV value changed
#define VTSS_VOE_EVENT_MASK_CCM_TLV_PORT_STATUS 0x200
// Interface status TLV value changed
#define VTSS_VOE_EVENT_MASK_CCM_TLV_IF_STATUS   0x400
#define VTSS_VOE_EVENT_MASK_ALL                 0x7FF
#else
#define VTSS_VOE_EVENT_MASK_ALL                 0x0FF
#endif

// VOE event generation enable/disable.
// inst     [IN] Target instance reference.
// voe_idx  [IN] Index of the configured VOE instance.
// mask     [IN] Mask of events to either enable or disable.
// enable   [IN] Whether to enable or disable the events specified in the mask.
vtss_rc vtss_voe_event_mask_set(const vtss_inst_t     inst,
                                const vtss_voe_idx_t  voe_idx,
                                const u32             mask,
                                const BOOL            enable);

vtss_rc vtss_voe_event_mask_get(const vtss_inst_t     inst,
                                const vtss_voe_idx_t  voe_idx,
                                u32                   *const mask);

// VOE event polling.
// Mask is returned indicating pending events. Pending event are cleared after get.
// inst      [IN]  Target instance reference.
// voe_idx   [IN]  Index of polled VOE instance.
// mask      [OUT] Mask of detected pending events during get.
vtss_rc vtss_voe_event_get(const vtss_inst_t     inst,
                           const vtss_voe_idx_t  voe_idx,
                           u32                   *const mask);




#if defined(VTSS_FEATURE_VOP_V2)
// -------------------------------------------------------------------------
// --- VOI - Versatile OAM Intermediate point     --------------------------
// --- Note that in registers this is called MIP  --------------------------
// -------------------------------------------------------------------------

// VOI Allocation structure.
typedef struct {
    vtss_port_no_t        port;
    vtss_oam_direction_t  direction;
} vtss_voi_allocation_t;

// Allocate a VOI.
// inst      [IN]  Target instance reference.
// param     [IN]  Allocation parameters
// voi_idx   [OUT] Index of allocated VOI instance.
//                 this index can be used when creating VCE or TCE entries */
vtss_rc vtss_voi_alloc(const vtss_inst_t            inst,
                       const vtss_voi_allocation_t  *const param,
                       vtss_voi_idx_t               *const voi_idx);

// Free a VOI.
// inst      [IN] Target instance reference.
// voi_idx   [IN] Index of previously allocated VOI instance.
vtss_rc vtss_voi_free(const vtss_inst_t       inst,
                      const vtss_voi_idx_t    voi_idx);

// VOI APS PDU handling.
typedef enum {
    VTSS_OAM_RAPS_HANDLING_NONE,        // RAPS PDUs are not handled
    VTSS_OAM_RAPS_HANDLING_COPY_CPU,    // RAPS PDUs are copied to CPU
    VTSS_OAM_RAPS_HANDLING_REDIR_CPU,   // RAPS PDUs are redirected to CPU
    VTSS_OAM_RAPS_HANDLING_DISCARD,     // RAPS PDUs are discarded
} vtss_oam_raps_handling_t;

// VOI configuration.
typedef struct {
    BOOL                      enable;         // Enable the VOI
    vtss_mac_t                unicast_mac;    // The VOI unicast MAC
    u32                       meg_level;      // MEG Level (MEL)
    BOOL                      lbm_cpu_redir;  // Enable LBM redirect to CPU
    BOOL                      ltm_cpu_redir;  // Enable LTM redirect to CPU
    vtss_oam_raps_handling_t  raps_handling;  // Control handling of RAPS PDUs
} vtss_voi_conf_t;

// VOI configuration set.
// inst      [IN] Target instance reference.
// voi_idx   [IN] Index of the configured VOI instance.
// conf      [IN] Configuration parameters for VOI. */
vtss_rc vtss_voi_conf_set(const vtss_inst_t       inst,
                          const vtss_voi_idx_t    voi_idx,
                          const vtss_voi_conf_t   *const conf);

vtss_rc vtss_voi_conf_get(const vtss_inst_t      inst,
                          const vtss_voi_idx_t   voi_idx,
                          vtss_voi_conf_t        *const conf);
#endif /* VTSS_FEATURE_VOP_V2 */

#ifdef __cplusplus
}
#endif
#endif /* VTSS_FEATURE_VOP */
#endif /* _VTSS_VOP_API_H_ */
