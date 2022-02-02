// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_TSN_
#define _MICROCHIP_ETHERNET_SWITCH_API_TSN_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/* - FRER compound streams ----------------------------------------- */

// FRER compound stream ID.
// Sequence recovery can be enabled to eliminate duplicate frames.
typedef uint16_t mesa_frer_cstream_id_t;

// FRER recovery algorithm
typedef enum {
    MESA_FRER_RECOVERY_ALG_VECTOR, // Vector recovery
    MESA_FRER_RECOVERY_ALG_MATCH,  // Match recovery
} mesa_frer_recovery_alg_t;

// FRER member/compound stream configuration
typedef struct {
    mesa_bool_t              recovery;    // Enable/disable recovery
    mesa_frer_recovery_alg_t alg;         // frerSeqRcvyAlgorithm: Algorithm
    uint8_t                  hlen;        // frerSeqRcvyHistoryLength: History length, 2-32 (vector algorithm)
    uint16_t                 reset_time;  // frerSeqRcvyResetMSec: Reset timeout (milliseconds)
    mesa_bool_t              take_no_seq; // frerSeqRcvyTakeNoSequence: Accept frames without R-tag
    mesa_frer_cstream_id_t   cstream_id;  // Compound stream ID (valid for member stream only)
} mesa_frer_stream_conf_t;

// Get compound stream configuration.
// id [IN]     Compound stream ID.
// conf [OUT]  Compound stream configuration.
mesa_rc mesa_frer_cstream_conf_get(const mesa_inst_t            inst,
                                   const mesa_frer_cstream_id_t id,
                                   mesa_frer_stream_conf_t      *const conf);

// Set compound stream configuration.
// id [IN]    Compound stream ID.
// conf [IN]  Compound stream configuration.
mesa_rc mesa_frer_cstream_conf_set(const mesa_inst_t             inst,
                                   const mesa_frer_cstream_id_t  id,
                                   const mesa_frer_stream_conf_t *const conf);

// FRER recovery counters
typedef struct {
    mesa_counter_t out_of_order_packets; // frerCpsSeqRcvyOutOfOrderPackets
    mesa_counter_t rogue_packets;        // frerCpsSeqRcvyRoguePackets
    mesa_counter_t passed_packets;       // frerCpsSeqRcvyPassedPackets
    mesa_counter_t discarded_packets;    // frerCpsSeqRcvyDiscardedPackets
    mesa_counter_t lost_packets;         // frerCpsSeqRcvyLostPackets
    mesa_counter_t tagless_packets;      // frerCpsSeqRcvyTaglessPackets
    mesa_counter_t resets;               // frerCpsSeqRcvyResets
} mesa_frer_counters_t;

// Get compound stream Counters.
// id [IN]         Compound stream ID.
// counters [OUT]  Compund stream counters.
mesa_rc mesa_frer_cstream_cnt_get(const mesa_inst_t            inst,
                                  const mesa_frer_cstream_id_t id,
                                  mesa_frer_counters_t         *const counters);

// Clear compound stream Counters.
// id [IN]  Compound stream ID.
mesa_rc mesa_frer_cstream_cnt_clear(const mesa_inst_t            inst,
                                    const mesa_frer_cstream_id_t id);

/* - FRER member streams ------------------------------------------- */

// FRER member stream ID.
// A block of member stream IDs must be allocated for an egress port list.
// For each stream ID and egress port, configuration and counters are available.
// Individual recovery can be enabled to eliminate duplicate frames.
// Frames can also be mapped to a compound stream.
typedef uint16_t mesa_frer_mstream_id_t;

// Allocate FRER member stream ID block.
// port_list [IN]  Egress port list, maximum 8 ports enabled
// id [OUT]        Member stream ID base.
mesa_rc mesa_frer_mstream_alloc(const mesa_inst_t      inst,
                                const mesa_port_list_t *port_list,
                                mesa_frer_mstream_id_t *const id);

// Free FRER member stream ID block.
// id [IN]    Member stream ID base.
mesa_rc mesa_frer_mstream_free(const mesa_inst_t            inst,
                               const mesa_frer_mstream_id_t id);

// Get member stream configuration.
// id [IN]       Member stream ID.
// port_no [IN]  Egress port number.
// conf [OUT]    Member stream configuration.
mesa_rc mesa_frer_mstream_conf_get(const mesa_inst_t            inst,
                                   const mesa_frer_mstream_id_t id,
                                   const mesa_port_no_t         port_no,
                                   mesa_frer_stream_conf_t      *const conf);

// Set member stream configuration.
// id [IN]       Member stream ID.
// port_no [IN]  Egress port number.
// conf [IN]     Member stream configuration.
mesa_rc mesa_frer_mstream_conf_set(const mesa_inst_t             inst,
                                   const mesa_frer_mstream_id_t  id,
                                   const mesa_port_no_t          port_no,
                                   const mesa_frer_stream_conf_t *const conf);

// Get member stream Counters.
// id [IN]         Member stream ID.
// port_no [IN]    Egress port number.
// counters [OUT]  Member stream counters.
mesa_rc mesa_frer_mstream_cnt_get(const mesa_inst_t            inst,
                                  const mesa_frer_mstream_id_t id,
                                  const mesa_port_no_t         port_no,
                                  mesa_frer_counters_t         *const counters);

// Clear member stream Counters.
// id [IN]       Member stream ID.
// port_no [IN]  Egress port number.
mesa_rc mesa_frer_mstream_cnt_clear(const mesa_inst_t            inst,
                                    const mesa_frer_mstream_id_t id,
                                    const mesa_port_no_t         port_no);

// FRER ingress flow configuration
typedef struct {
    mesa_bool_t            mstream_enable;             // Enable member stream
    mesa_frer_mstream_id_t mstream_id;                 // Member stream base ID
    mesa_bool_t            generation;                 // Enable/disable sequence generation
    mesa_bool_t            pop CAP(L2_FRER_IFLOW_POP); // R-tag popping
} mesa_frer_iflow_conf_t;

/* - PSFP ---------------------------------------------------------- */

// PSFP gate ID
typedef uint16_t mesa_psfp_gate_id_t;

// PSFP Gate Control Entry configuration
typedef struct {
    mesa_bool_t     gate_open;     // StreamGateState
    mesa_opt_prio_t prio;          // IPV: Priority
    uint32_t        time_interval; // TimeInterval: Time interval (nsec)
    uint32_t        octet_max;     // IntervalOctetMax: Maximum number of octets permitted (zero disables check)
} mesa_psfp_gce_t;

// Get PSFP Gate Control List.
// id [IN]        Gate ID.
// max_cnt [IN]   Size of the 'gcl' array.
// gcl [OUT]      Gate Control List
// gce_cnt [OUT]  Length of Gate Control List.
mesa_rc mesa_psfp_gcl_conf_get(const mesa_inst_t         inst,
                               const mesa_psfp_gate_id_t id,
                               const uint32_t            max_cnt,
                               mesa_psfp_gce_t           *const gcl,
                               uint32_t                  *const gce_cnt);

// Set PSFP Gate Control List.
// id [IN]       Gate ID.
// gce_cnt [IN]  Length of Gate Control List.
// gcl [IN]      Gate Control List.
mesa_rc mesa_psfp_gcl_conf_set(const mesa_inst_t         inst,
                               const mesa_psfp_gate_id_t id,
                               const uint32_t            gce_cnt,
                               const mesa_psfp_gce_t     *const gcl);

// PSFP Gate Control List configuration
typedef struct {
    mesa_timestamp_t  base_time;      // PSFPAdminBaseTime/PSFPOperBaseTime
    uint32_t          cycle_time;     // PSFPAdminCycleTime/PSFPOperCycleTime
    uint32_t          cycle_time_ext; // PSFPAdminCycleTimeExtension/PSFPOperCycleTimeExtension
} mesa_psfp_gcl_conf_t;

// PSFP gate configuration
typedef struct {
    mesa_bool_t          enable;                // PSFPGateEnabled: Enable/disable Gate
    mesa_bool_t          gate_open;             // PSFPAdminGateStates: Initial gate state
    mesa_opt_prio_t      prio;                  // PSFPAdminIPV: Priority
    mesa_opt_bool_t      close_invalid_rx;      // PSFPGateClosedDueToInvalidRxEnable/PSFPGateClosedDueToInvalidRx
    mesa_opt_bool_t      close_octets_exceeded; // PSFPGateClosedDueToOctetsExceededEnable/PSFPGateClosedDueOctetsExceeded
    mesa_bool_t          config_change;         // PSFPConfigChange: Apply the following configuration fields
    mesa_psfp_gcl_conf_t config;                // PSFPAdmin*: Gate Control List applied if 'config_change' is set
} mesa_psfp_gate_conf_t;

// Get PSFP gate configuration.
// id [IN]     Gate ID.
// conf [OUT]  Gate configuration.
mesa_rc mesa_psfp_gate_conf_get(const mesa_inst_t         inst,
                                const mesa_psfp_gate_id_t id,
                                mesa_psfp_gate_conf_t     *const conf);

// Set PSFP gate configuration.
// id [IN]    Gate ID.
// conf [IN]  Gate configuration.
mesa_rc mesa_psfp_gate_conf_set(const mesa_inst_t           inst,
                                const mesa_psfp_gate_id_t   id,
                                const mesa_psfp_gate_conf_t *const conf);

// PSFP gate status
typedef struct {
    mesa_bool_t          gate_open;             // PSFPOperGateStates: Current gate state
    mesa_opt_prio_t      prio;                  // PSFPOperIPV: Priority
    mesa_timestamp_t     config_change_time;    // PSFPConfigChangeTime
    mesa_timestamp_t     current_time;          // PSFPCurrentTime
    mesa_bool_t          config_pending;        // PSFPConfigPending: Configuration active indication
    mesa_bool_t          close_invalid_rx;      // PSFPGateClosedDueToInvalidRx
    mesa_bool_t          close_octets_exceeded; // PSFPGateClosedDueOctetsExceeded
} mesa_psfp_gate_status_t;

// Get PSFP gate status.
// id [IN]       Gate ID.
// status [OUT]  Gate configuration.
mesa_rc mesa_psfp_gate_status_get(const mesa_inst_t         inst,
                                  const mesa_psfp_gate_id_t id,
                                  mesa_psfp_gate_status_t   *const status);

// PSFP filter ID
typedef uint16_t mesa_psfp_filter_id_t;

// PSFP filter configuration
typedef struct {
    mesa_bool_t         gate_enable;    // Enable gate mapping
    mesa_psfp_gate_id_t gate_id;        // StreamGateInstanceID: Gate ID mapping
    uint16_t            max_sdu;        // Maximum SDU size (zero disables SDU check)
    mesa_opt_bool_t     block_oversize; // StreamBlockedDueToOversizeFrameEnable/StreamBlockedDueToOversizeFrame
} mesa_psfp_filter_conf_t;

// Get PSFP filter configuration.
// id [IN]     Filter ID.
// conf [OUT]  Filter configuration.
mesa_rc mesa_psfp_filter_conf_get(const mesa_inst_t           inst,
                                  const mesa_psfp_filter_id_t id,
                                  mesa_psfp_filter_conf_t     *const conf);

// Set PSFP filter configuration.
// id [IN]    Filter ID.
// conf [IN]  Filter configuration.
mesa_rc mesa_psfp_filter_conf_set(const mesa_inst_t             inst,
                                  const mesa_psfp_filter_id_t   id,
                                  const mesa_psfp_filter_conf_t *const conf);

// PSFP filter status
typedef struct {
    mesa_bool_t block_oversize; // StreamBlockedDueToOversizeFrame
} mesa_psfp_filter_status_t;

// Get PSFP filter status.
// id [IN]       Filter ID.
// status [OUT]  Filter status.
mesa_rc mesa_psfp_filter_status_get(const mesa_inst_t           inst,
                                    const mesa_psfp_filter_id_t id,
                                    mesa_psfp_filter_status_t   *const status);

// PSFP ingress flow configuration
typedef struct {
    mesa_bool_t           filter_enable; // Enable filter mapping
    mesa_psfp_filter_id_t filter_id;     // Filter ID mapping
} mesa_psfp_iflow_conf_t;

/* - TAS ---------------------------------------------------------- */

// Time Aware Shaper (802.1Qbv) global configuration
typedef struct {
    // If a GCL contains HOLD_MAC and RELEASE_MAC operation:
    //     When TRUE a guard band is implemented on all queues, both Express and Preemptible queues.
    //     When FALSE a guard band is only implemented on Preemptible queues.
    // If a GCL do not contains HOLD_MAC and RELEASE_MAC operation:
    //     Has no effect.
    mesa_bool_t always_guard_band CAP(MESA_CAP_QOS_TAS_HOLD_REL_MAC_RESTRICT);
} mesa_qos_tas_conf_t CAP(QOS_TAS);

// Get Time Aware Shaper (802.1Qbv) global configuration.
// conf    [OUT] Scheduled Traffic configuration structure.
mesa_rc mesa_qos_tas_conf_get(const mesa_inst_t    inst,
                              mesa_qos_tas_conf_t  *const conf)
    CAP(QOS_TAS);

// Set Time Aware Shaper (802.1Qbv) global configuration.
// conf    [IN] Scheduled Traffic configuration structure.
mesa_rc mesa_qos_tas_conf_set(const mesa_inst_t         inst,
                              const mesa_qos_tas_conf_t *const conf)
    CAP(QOS_TAS);

// Time Aware Shaper (802.1Qbv) Gate Control Operations
typedef enum {
    MESA_QOS_TAS_GCO_SET_GATE_STATES,     // Set GateState
    MESA_QOS_TAS_GCO_SET_AND_HOLD_MAC,    // Set GateState and stop preemption
    MESA_QOS_TAS_GCO_SET_AND_RELEASE_MAC  // Set GateState and resume preemption
} mesa_qos_tas_gco_t CAP(QOS_TAS);

// Time Aware Shaper (802.1Qbv) gate control list entry
// CAP(MESA_CAP_QOS_TAS_HOLD_REL_MAC_RESTRICT):
//      A GCE with HOLD_MAC all queues opened must be Express queues.
//      A GCE with RELEASE_MAC all queues opened must be Preemptable queues.
//      The same queue cannot be open in both a HOLD_MAC and a RELEASE_MAC entry.
// Note that if a list ends with gate operation HOLD_MAC then this MAC state is not changed when a new list is taking over.
// To assure the MAC is released, the new list should contain a RELEASE_MAC gate operation.
typedef struct {
    mesa_qos_tas_gco_t gate_operation; // Gate Control Operation.

    // The gate open states for the corresponding traffic classes in this interval;
    mesa_bool_t        gate_open[MESA_QUEUE_ARRAY_SIZE];

    // A time interval that the gate_open is active before going to next GCL entry.
    // This is in nano seconds.
    uint32_t           time_interval;
} mesa_qos_tas_gce_t CAP(QOS_TAS);

// Get Time Aware Shaper (802.1Qbv) port Gate Control List.
// port_no    [IN]   Port number.
// cnt        [IN]   Size of the 'gcl' array delivered by caller.
// gcl        [OUT]  Scheduled Traffic Gate Control List array of size 'cnt' delivered by caller.
//                   Containing returned GCL of length 'gce_cnt'.
// gce_cnt    [OUT]  Number of GCE in returned Gate Control List.
mesa_rc mesa_qos_tas_port_gcl_conf_get(const mesa_inst_t     inst,
                                       const mesa_port_no_t  port_no,
                                       const uint32_t        cnt,
                                       mesa_qos_tas_gce_t    *const gcl,
                                       uint32_t              *const gce_cnt)
    CAP(QOS_TAS);

// Set Time Aware Shaper (802.1Qbv) port Gate Control List.
// port_no    [IN]  Port number.
// gce_cnt    [IN]  Number of GCE in the 'gcl' array delivered by caller.
// gcl        [IN]  Scheduled Traffic Gate Control List.
mesa_rc mesa_qos_tas_port_gcl_conf_set(const mesa_inst_t          inst,
                                       const mesa_port_no_t       port_no,
                                       const uint32_t             gce_cnt,
                                       const mesa_qos_tas_gce_t   *const gcl)
    CAP(QOS_TAS);

// Time Aware Shaper (802.1Qbv) port configuration
typedef struct {
    // Maximum SDU size supported by each queue in bytes. Minimum 64 bytes.
    // This parameter is also used to calculate the guard band time: gbt = max_sdu[]*8 / LINK_SPEED
    // In case of HOLD_MAC gate operaton, the guard band time in preemptable queues is automatically selected as the min fragment size plus 64 bytes.
    // CAP(MESA_CAP_QOS_TAS_HOLD_REL_MAC_RESTRICT):
    //      A queue is determined preemptible if it is not opened in a MAC_HOD gate operation.
    uint16_t         max_sdu[MESA_QUEUE_ARRAY_SIZE];

    // The GateEnabled parameter determines whether traffic scheduling
    // is active (true) or inactive (false).
    mesa_bool_t      gate_enabled;

    // The initial value of the port open states that is used when no GCL is active on the port.
    mesa_bool_t      gate_open[MESA_QUEUE_ARRAY_SIZE];

    // The administrative cycle time in nanoseconds.
    // The cycle time must be at least as long as the sum of all time_interval
    // in the GCL configured by mesa_qos_tas_port_gcl_conf_set() and must also be larger than
    // MESA_CAP_QOS_TAS_CT_MIN-1 and smaller MESA_CAP_QOS_TAS_CT_MAX+1.
    uint32_t         cycle_time;

    // In case a new GCL start time (cycle_time) is not lining up exactly with an currently active (old) GCL.
    // This is the maximum time that current GCL will be extended. Otherwise it will be truncated.
    // Must also be larger than MESA_CAP_QOS_TAS_CT_MIN-1 and smaller MESA_CAP_QOS_TAS_CT_MAX+1.
    uint32_t         cycle_time_ext;

    // The administrative base time. This is GCL start active time after config_change true.
    // This time should be base_time + (N * cycle_time) of any currently active (old) GCL on this port.
    // in order to assure time alignment of old and new GCL.
    // Must be at least two times cycle_time in the future to assure GCL start on expected time.
    // If base_time is in the past the actual GCL start time will be calculated. This is done in ADVANCING state.
    mesa_timestamp_t base_time;

    // The ConfigChange parameter set to TRUE, signals the start of a new GCL configured by mesa_qos_tas_port_gcl_conf_set().
    // The actual start of the new GCL will happen at base_time time. As long as the new GCL is not active config_pending is TRUE.
    // This should only be done when the above parameters are all set to appropriate values.
    mesa_bool_t      config_change;
} mesa_qos_tas_port_conf_t CAP(QOS_TAS);

// Get Time Aware Shaper (802.1Qbv) port configuration.
// port_no [IN]  Port number.
// conf    [OUT] Scheduled Traffic configuration structure.
mesa_rc mesa_qos_tas_port_conf_get(const mesa_inst_t       inst,
                                   const mesa_port_no_t    port_no,
                                   mesa_qos_tas_port_conf_t *const conf)
    CAP(QOS_TAS);

// Set Time Aware Shaper (802.1Qbv) port configuration.
// port_no [IN] Port number.
// conf    [IN] Scheduled Traffic configuration structure.
mesa_rc mesa_qos_tas_port_conf_set(const mesa_inst_t             inst,
                                   const mesa_port_no_t          port_no,
                                   const mesa_qos_tas_port_conf_t *const conf)
    CAP(QOS_TAS);

// Time Aware Shaper (802.1Qbv) port status.
typedef struct {
    // The value of the ConfigPending state machine variable.
    // The value is TRUE if a configuration change is in progress but has not yet completed.
    mesa_bool_t         config_pending;

    // A counter of the number of times that a re-configuration
    // of the traffic schedule has been requested with the old
    // schedule still running and the requested base time was in the past.
    uint64_t            config_change_error;

    // The calculated actual GCL start time in case the configured base_time is in the past
    mesa_timestamp_t    config_change_time;

    // The current port open states for the corresponding traffic classes.
    mesa_bool_t         gate_open[MESA_QUEUE_ARRAY_SIZE];
} mesa_qos_tas_port_status_t CAP(QOS_TAS);

// Get Time Aware Shaper (802.1Qbv) status for port.
// port_no [IN]  Port number.
// status  [OUT] Scheduled Traffic status structure.
mesa_rc mesa_qos_tas_port_status_get(const mesa_inst_t          inst,
                                     const mesa_port_no_t       port_no,
                                     mesa_qos_tas_port_status_t *const status)
    CAP(QOS_TAS);

/* - Frame Preemption ---------------------------------------------- */

// 802.1Qbu and 802.3br (Frame Preemption) port configuration
typedef struct {
    mesa_bool_t admin_status[MESA_QUEUE_ARRAY_SIZE]; // IEEE802.1Qbu: framePreemptionStatusTable
    mesa_bool_t enable_tx;                           // IEEE802.3br: aMACMergeEnableTx
    mesa_bool_t verify_disable_tx;                   // IEEE802.3br: aMACMergeVerifyDisableTx
    uint8_t     verify_time;                         // IEEE802.3br: aMACMergeVerifyTime [msec]
    uint8_t     add_frag_size;                       // IEEE802.3br: aMACMergeAddFragSize
} mesa_qos_fp_port_conf_t CAP(QOS_FRAME_PREEMPTION);

// Get 802.1Qbu and 802.3br (Frame Preemption) port configuration.
// port_no [IN]  Port number.
// conf    [OUT] Frame Preemption configuration structure.
mesa_rc mesa_qos_fp_port_conf_get(const mesa_inst_t       inst,
                                  const mesa_port_no_t    port_no,
                                  mesa_qos_fp_port_conf_t *const conf)
    CAP(QOS_FRAME_PREEMPTION);

// Set 802.1Qbu and 802.3br (Frame Preemption) port configuration.
// port_no [IN] Port number.
// conf    [IN] Frame Preemption configuration structure.
mesa_rc mesa_qos_fp_port_conf_set(const mesa_inst_t             inst,
                                  const mesa_port_no_t          port_no,
                                  const mesa_qos_fp_port_conf_t *const conf)
    CAP(QOS_FRAME_PREEMPTION);

// MAC Merge Status Verify (aMACMergeStatusVerify in 802.3br)
typedef enum {
    MESA_MM_STATUS_VERIFY_INITIAL,   // INIT_VERIFICATION
    MESA_MM_STATUS_VERIFY_IDLE,      // VERIFICATION_IDLE
    MESA_MM_STATUS_VERIFY_SEND,      // SEND_VERIFY
    MESA_MM_STATUS_VERIFY_WAIT,      // WAIT_FOR_RESPONSE.
    MESA_MM_STATUS_VERIFY_SUCCEEDED, // VERIFIED
    MESA_MM_STATUS_VERIFY_FAILED,    // VERIFY_FAIL
    MESA_MM_STATUS_VERIFY_DISABLED   // Verification process is disabled
} mesa_mm_status_verify_t CAP(QOS_FRAME_PREEMPTION);

// 802.1Qbu and 802.3br (Frame Preemption) port status
typedef struct {
    uint32_t                hold_advance;      // TBD: IEEE802.1Qbu: holdAdvance [nsec]
    uint32_t                release_advance;   // TBD: IEEE802.1Qbu: releaseAdvance [nsec]
    mesa_bool_t             preemption_active; // IEEE802.1Qbu: preemptionActive, IEEE802.3br: aMACMergeStatusTx
    uint8_t                 hold_request;      // TBD: IEEE802.1Qbu: holdRequest
    mesa_mm_status_verify_t status_verify;     // IEEE802.3br: aMACMergeStatusVerify
} mesa_qos_fp_port_status_t CAP(QOS_FRAME_PREEMPTION);

// Get 802.1Qbu and 802.3br (Frame Preemption) port status.
// port_no [IN]  Port number.
// status  [OUT] Frame Preemption status structure.
mesa_rc mesa_qos_fp_port_status_get(const mesa_inst_t         inst,
                                    const mesa_port_no_t      port_no,
                                    mesa_qos_fp_port_status_t *const status)
    CAP(QOS_FRAME_PREEMPTION);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_L2_
