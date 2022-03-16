// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_TSN_API_H_
#define _VTSS_TSN_API_H_

#if defined(VTSS_FEATURE_FRER)

/* - FRER compound streams ----------------------------------------- */

// Number of member streams and compound streams */
#if defined(VTSS_ARCH_LAN966X)
#define VTSS_MSTREAM_CNT 512
#define VTSS_CSTREAM_CNT 256
#else
#define VTSS_MSTREAM_CNT 1024
#define VTSS_CSTREAM_CNT 512
#endif

// FRER compound stream ID.
// Sequence recovery can be enabled to eliminate duplicate frames.
typedef u16 vtss_frer_cstream_id_t;

// FRER recovery algorithm
typedef enum {
    VTSS_FRER_RECOVERY_ALG_VECTOR, // Vector recovery
    VTSS_FRER_RECOVERY_ALG_MATCH,  // Match recovery
} vtss_frer_recovery_alg_t;

// FRER member/compound stream configuration
typedef struct {
    BOOL                     recovery;    // Enable/disable recovery
    vtss_frer_recovery_alg_t alg;         // frerSeqRcvyAlgorithm: Algorithm
    u8                       hlen;        // frerSeqRcvyHistoryLength: History length, 2-32 (vector algorithm)
    u16                      reset_time;  // frerSeqRcvyResetMSec: Reset timeout (milliseconds)
    BOOL                     take_no_seq; // frerSeqRcvyTakeNoSequence: Accept frames without R-tag
    vtss_frer_cstream_id_t   cstream_id;  // Compound stream ID (valid for member stream only)
} vtss_frer_stream_conf_t;

// Get compound stream configuration.
// id [IN]     Compound stream ID.
// conf [OUT]  Compound stream configuration.
vtss_rc vtss_frer_cstream_conf_get(const vtss_inst_t            inst,
                                   const vtss_frer_cstream_id_t id,
                                   vtss_frer_stream_conf_t      *const conf);

// Set compound stream configuration.
// id [IN]    Compound stream ID.
// conf [IN]  Compound stream configuration.
vtss_rc vtss_frer_cstream_conf_set(const vtss_inst_t             inst,
                                   const vtss_frer_cstream_id_t  id,
                                   const vtss_frer_stream_conf_t *const conf);

// FRER recovery counters
typedef struct {
    vtss_counter_t out_of_order_packets; // frerCpsSeqRcvyOutOfOrderPackets
    vtss_counter_t rogue_packets;        // frerCpsSeqRcvyRoguePackets
    vtss_counter_t passed_packets;       // frerCpsSeqRcvyPassedPackets
    vtss_counter_t discarded_packets;    // frerCpsSeqRcvyDiscardedPackets
    vtss_counter_t lost_packets;         // frerCpsSeqRcvyLostPackets
    vtss_counter_t tagless_packets;      // frerCpsSeqRcvyTaglessPackets
    vtss_counter_t resets;               // frerCpsSeqRcvyResets
} vtss_frer_counters_t;

// Get compound stream Counters.
// id [IN]         Compound stream ID.
// counters [OUT]  Compund stream counters.
vtss_rc vtss_frer_cstream_cnt_get(const vtss_inst_t            inst,
                                  const vtss_frer_cstream_id_t id,
                                  vtss_frer_counters_t         *const counters);

// Clear compound stream Counters.
// id [IN]  Compound stream ID.
vtss_rc vtss_frer_cstream_cnt_clear(const vtss_inst_t            inst,
                                    const vtss_frer_cstream_id_t id);

/* - FRER member streams ------------------------------------------- */

// FRER member stream ID.
// A block of member stream IDs must be allocated for an egress port list.
// For each stream ID and egress port, configuration and counters are available.
// Individual recovery can be enabled to eliminate duplicate frames.
// Frames can also be mapped to a compound stream.
typedef u16 vtss_frer_mstream_id_t;

// Allocate FRER member stream ID block.
// port_list [IN]  Egress port list, maximum 8 ports enabled
// id [OUT]        Member stream ID base.
vtss_rc vtss_frer_mstream_alloc(const vtss_inst_t      inst,
                                const BOOL             port_list[VTSS_PORTS],
                                vtss_frer_mstream_id_t *const id);

// Free FRER member stream ID block.
// id [IN]  Member stream ID base.
vtss_rc vtss_frer_mstream_free(const vtss_inst_t            inst,
                               const vtss_frer_mstream_id_t id);

// Get member stream configuration.
// id [IN]       Member stream ID.
// port_no [IN]  Egress port number.
// conf [OUT]    Member stream configuration.
vtss_rc vtss_frer_mstream_conf_get(const vtss_inst_t            inst,
                                   const vtss_frer_mstream_id_t id,
                                   const vtss_port_no_t         port_no,
                                   vtss_frer_stream_conf_t      *const conf);

// Set member stream configuration.
// id [IN]       Member stream ID.
// port_no [IN]  Egress port number.
// conf [IN]     Member stream configuration.
vtss_rc vtss_frer_mstream_conf_set(const vtss_inst_t             inst,
                                   const vtss_frer_mstream_id_t  id,
                                   const vtss_port_no_t          port_no,
                                   const vtss_frer_stream_conf_t *const conf);

// Get member stream Counters.
// id [IN]         Member stream ID.
// port_no [IN]    Egress port number.
// counters [OUT]  Member stream counters.
vtss_rc vtss_frer_mstream_cnt_get(const vtss_inst_t            inst,
                                  const vtss_frer_mstream_id_t id,
                                  const vtss_port_no_t         port_no,
                                  vtss_frer_counters_t         *const counters);

// Clear member stream Counters.
// id [IN]       Member stream ID.
// port_no [IN]  Egress port number.
vtss_rc vtss_frer_mstream_cnt_clear(const vtss_inst_t            inst,
                                    const vtss_frer_mstream_id_t id,
                                    const vtss_port_no_t         port_no);

// FRER ingress flow configuration
typedef struct {
    BOOL                   mstream_enable;  // Enable/disable member stream
    vtss_frer_mstream_id_t mstream_id;      // Member stream base ID
    BOOL                   generation;      // Enable/disable sequence generation
#if defined(VTSS_FEATURE_FRER_IFLOW_POP)
    BOOL                   pop;             // R-tag popping
#endif
} vtss_frer_iflow_conf_t;
#endif /* VTSS_FEATURE_FRER */

/* - PSFP ---------------------------------------------------------- */

#if defined(VTSS_FEATURE_PSFP)
// PSFP gate ID
typedef u16 vtss_psfp_gate_id_t;

// Number of PSFP gates */
#if defined(VTSS_ARCH_LAN966X)
#define VTSS_PSFP_GATE_CNT 256
#else
#define VTSS_PSFP_GATE_CNT 1023
#endif

// PSFP Gate Control Entry configuration
typedef struct {
    BOOL            gate_open;     // StreamGateState
    vtss_opt_prio_t prio;          // IPV: Priority
    u32             time_interval; // TimeInterval: Time interval (nsec)
    u32             octet_max;     // IntervalOctetMax: Maximum number of octets permitted (zero disables check)
} vtss_psfp_gce_t;

// Get PSFP Gate Control List.
// id [IN]        Gate ID.
// max_cnt [IN]   Size of the 'gcl' array.
// gcl [OUT]      Gate Control List
// gce_cnt [OUT]  Length of Gate Control List.
vtss_rc vtss_psfp_gcl_conf_get(const vtss_inst_t         inst,
                               const vtss_psfp_gate_id_t id,
                               const u32                 max_cnt,
                               vtss_psfp_gce_t           *const gcl,
                               u32                       *const gce_cnt);

// Set PSFP Gate Control List.
// id [IN]       Gate ID.
// gce_cnt [IN]  Length of Gate Control List.
// gcl [IN]      Gate Control List.
vtss_rc vtss_psfp_gcl_conf_set(const vtss_inst_t         inst,
                               const vtss_psfp_gate_id_t id,
                               const u32                 gce_cnt,
                               const vtss_psfp_gce_t     *const gcl);

// PSFP Gate Control List configuration
typedef struct {
    vtss_timestamp_t base_time;      // PSFPAdminBaseTime/PSFPOperBaseTime
    u32              cycle_time;     // PSFPAdminCycleTime/PSFPOperCycleTime
    u32              cycle_time_ext; // PSFPAdminCycleTimeExtension/PSFPOperCycleTimeExtension
} vtss_psfp_gcl_conf_t;

// PSFP gate configuration
typedef struct {
    BOOL                 enable;                // PSFPGateEnabled: Enable/disable Gate
    BOOL                 gate_open;             // PSFPAdminGateStates: Initial gate state
    vtss_opt_prio_t      prio;                  // PSFPAdminIPV: Priority
    vtss_opt_bool_t      close_invalid_rx;      // PSFPGateClosedDueToInvalidRxEnable/PSFPGateClosedDueToInvalidRx
    vtss_opt_bool_t      close_octets_exceeded; // PSFPGateClosedDueToOctetsExceededEnable/PSFPGateClosedDueOctetsExceeded
    BOOL                 config_change;         // PSFPConfigChange: Apply the following configuration fields
    vtss_psfp_gcl_conf_t config;                // PSFPAdmin*: Gate Control List applied if 'config_change' is set
} vtss_psfp_gate_conf_t;

// Get PSFP gate configuration.
// id [IN]     Gate ID.
// conf [OUT]  Gate configuration.
vtss_rc vtss_psfp_gate_conf_get(const vtss_inst_t         inst,
                                const vtss_psfp_gate_id_t id,
                                vtss_psfp_gate_conf_t     *const conf);

// Set PSFP gate configuration.
// id [IN]    Gate ID.
// conf [IN]  Gate configuration.
vtss_rc vtss_psfp_gate_conf_set(const vtss_inst_t           inst,
                                const vtss_psfp_gate_id_t   id,
                                const vtss_psfp_gate_conf_t *const conf);

// PSFP gate status
typedef struct {
    BOOL                 gate_open;             // PSFPOperGateStates: Current gate state
    vtss_opt_prio_t      prio;                  // PSFPOperIPV: Priority
    vtss_timestamp_t     config_change_time;    // PSFPConfigChangeTime
    vtss_timestamp_t     current_time;          // PSFPCurrentTime
    BOOL                 config_pending;        // PSFPConfigPending: Configuration active indication
    BOOL                 close_invalid_rx;      // PSFPGateClosedDueToInvalidRx
    BOOL                 close_octets_exceeded; // PSFPGateClosedDueOctetsExceeded
} vtss_psfp_gate_status_t;

// Get PSFP gate status.
// id [IN]       Gate ID.
// status [OUT]  Gate configuration.
vtss_rc vtss_psfp_gate_status_get(const vtss_inst_t         inst,
                                  const vtss_psfp_gate_id_t id,
                                  vtss_psfp_gate_status_t   *const status);

// PSFP filter ID
typedef u16 vtss_psfp_filter_id_t;

// Number of PSFP filters */
#if defined(VTSS_ARCH_LAN966X)
#define VTSS_PSFP_FILTER_CNT 256
#else
#define VTSS_PSFP_FILTER_CNT 1023
#endif

// PSFP filter configuration
typedef struct {
    BOOL                gate_enable;    // Enable gate mapping
    vtss_psfp_gate_id_t gate_id;        // StreamGateInstanceID: Gate ID mapping
    u16                 max_sdu;        // Maximum SDU size (zero disables SDU check)
    vtss_opt_bool_t     block_oversize; // StreamBlockedDueToOversizeFrameEnable/StreamBlockedDueToOversizeFrame
} vtss_psfp_filter_conf_t;

// Get PSFP filter configuration.
// id [IN]     Filter ID.
// conf [OUT]  Filter configuration.
vtss_rc vtss_psfp_filter_conf_get(const vtss_inst_t           inst,
                                  const vtss_psfp_filter_id_t id,
                                  vtss_psfp_filter_conf_t     *const conf);

// Set PSFP filter configuration.
// id [IN]    Filter ID.
// conf [IN]  Filter configuration.
vtss_rc vtss_psfp_filter_conf_set(const vtss_inst_t             inst,
                                  const vtss_psfp_filter_id_t   id,
                                  const vtss_psfp_filter_conf_t *const conf);

// PSFP filter status
typedef struct {
    BOOL block_oversize; // StreamBlockedDueToOversizeFrame
} vtss_psfp_filter_status_t;

// Get PSFP filter configuration.
// id [IN]       Filter ID.
// status [OUT]  Filter status.
vtss_rc vtss_psfp_filter_status_get(const vtss_inst_t           inst,
                                    const vtss_psfp_filter_id_t id,
                                    vtss_psfp_filter_status_t   *const status);

// PSFP ingress flow configuration
typedef struct {
    BOOL                  filter_enable; // Enable filter mapping
    vtss_psfp_filter_id_t filter_id;     // Filter ID mapping
} vtss_psfp_iflow_conf_t;
#endif

#if defined(VTSS_FEATURE_QOS_TAS)
// Time Aware Shaper (802.1Qbv) global configuration
typedef struct {
    // When set a quard band is implemented even for scheduled queues
    // to scheduled queue transition.
    // 0: Guard band is implemented for non-scheduled queues to scheduled
    // queues transition.
    // 1: Guard band is implemented for any queue to scheduled
    // queues transition.
    BOOL always_guard_band;
} vtss_qos_tas_conf_t;

// Get Time Aware Shaper (802.1Qbv) global configuration.
// conf    [OUT] Scheduled Traffic configuration structure.
vtss_rc vtss_qos_tas_conf_get(const vtss_inst_t    inst,
                              vtss_qos_tas_conf_t  *const conf);

// Set Time Aware Shaper (802.1Qbv) global configuration.
// conf    [IN] Scheduled Traffic configuration structure.
vtss_rc vtss_qos_tas_conf_set(const vtss_inst_t         inst,
                              const vtss_qos_tas_conf_t *const conf);

// Time Aware Shaper (802.1Qbv) Gate Control Operations
typedef enum {
    VTSS_QOS_TAS_GCO_SET_GATE_STATES,     // Set GateState
    VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC,    // Set GateState and stop preemption
    VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC  // Set GateState and resume preemption
} vtss_qos_tas_gco_t;

// Time Aware Shaper (802.1Qbv) gate control list entry
typedef struct {
    vtss_qos_tas_gco_t gate_operation; // Gate Control Operation.

    // The gate open states for the corresponding traffic classes in this interval;
    BOOL               gate_open[VTSS_QUEUE_ARRAY_SIZE];

    // A time interval that this gate_states is active before going to next GCL entry.
    // This is in nano seconds.
    u32                time_interval;
} vtss_qos_tas_gce_t;

// Time Aware Shaper (802.1Qbv) port configuration
typedef struct {
    // Maximum SDU size supported by each queue in bytes. Minimum 64 bytes.
    // This parameter contribute to calculating the guard band time max_sdu[]*8 / LINK_SPEED
    u16              max_sdu[VTSS_QUEUE_ARRAY_SIZE];

    // The GateEnabled parameter determines whether traffic scheduling
    // is active (true) or inactive (false).
    BOOL             gate_enabled;

    // The initial value of the port open states that is used when no GCL is active on the port.
    BOOL             gate_open[VTSS_QUEUE_ARRAY_SIZE];

    // The administrative cycle time in nanoseconds.
    // The cycle time must be at least as long as the sum of all time_interval
    // in the GCL configured by vtss_qos_tas_port_gcl_conf_set() and must also be less than vtss_CAP_TBD.
    u32              cycle_time;

    // In case a new GCL start time (cycle_time) is not lining up exactly with an currently active (old) GCL.
    // This is the maximum time that current GCL will be extended. Otherwise it will be truncated.
    u32              cycle_time_ext;

    // The administrative base time. This is GCL start active time after config_change true.
    // This time should be base_time + (N * cycle_time) of any currently active (old) GCL on this port.
    // in order to assure time alignment of old and new GCL.
    // Must be at least two times cycle_time in the future to assure GCL start on expected time.
    // If base_time is in the past the actual GCL start time will be calculated. This is done in ADVANCING state.
    vtss_timestamp_t base_time;

    // The ConfigChange parameter set to TRUE, signals the start of a new GCL configured by vtss_qos_tas_port_gcl_conf_set().
    // The actual start of the new GCL will happen at base_time time. As long as the new GCL is not active config_pending is TRUE.
    // This should only be done when the above parameters are all set to appropriate values.
    BOOL             config_change;

    // The length of the Gate Control List
    u32                  gcl_length;
    // The Gate Control List
    vtss_qos_tas_gce_t   gcl[VTSS_QOS_TAS_GCL_LEN_MAX];
} vtss_qos_tas_port_conf_t;

// Get Time Aware Shaper (802.1Qbv) port configuration.
// port_no [IN]  Port number.
// conf    [OUT] Scheduled Traffic configuration structure.
vtss_rc vtss_qos_tas_port_conf_get(const vtss_inst_t         inst,
                                   const vtss_port_no_t      port_no,
                                   vtss_qos_tas_port_conf_t  *const conf);

// Set Time Aware Shaper (802.1Qbv) port configuration.
// port_no [IN] Port number.
// conf    [IN] Scheduled Traffic configuration structure.
vtss_rc vtss_qos_tas_port_conf_set(const vtss_inst_t               inst,
                                   const vtss_port_no_t            port_no,
                                   const vtss_qos_tas_port_conf_t  *const conf);

// Time Aware Shaper (802.1Qbv) port status.
typedef struct {
    // The value of the ConfigPending state machine variable.
    // The value is TRUE if a configuration change is in progress but has not yet completed.
    BOOL                config_pending;

    // A counter of the number of times that a re-configuration
    // of the traffic schedule has been requested with the old
    // schedule still running and the requested base time was in the past.
    u64                 config_change_error;

    // The calculated actual GCL start time in case the configured base_time is in the past
    vtss_timestamp_t    config_change_time;

    // The current port open states for the corresponding traffic classes.
    BOOL                gate_open[VTSS_QUEUE_ARRAY_SIZE];
} vtss_qos_tas_port_status_t;

// Get Time Aware Shaper (802.1Qbv) status for port.
// port_no [IN]  Port number.
// status  [OUT] Scheduled Traffic status structure.
vtss_rc vtss_qos_tas_port_status_get(const vtss_inst_t          inst,
                                     const vtss_port_no_t       port_no,
                                     vtss_qos_tas_port_status_t *const status);

#endif /* defined(VTSS_FEATURE_QOS_TAS) */


#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
/**
 * \brief 802.1Qbu and 802.3br (Frame Preemption) port configuration
 **/
typedef struct {
    BOOL admin_status[VTSS_QUEUE_ARRAY_SIZE]; // IEEE802.1Qbu: framePreemptionStatusTable
    BOOL enable_tx;                           // IEEE802.3br: aMACMergeEnableTx
    BOOL verify_disable_tx;                   // IEEE802.3br: aMACMergeVerifyDisableTx
    u8   verify_time;                         // IEEE802.3br: aMACMergeVerifyTime [msec]
    u8   add_frag_size;                       // IEEE802.3br: aMACMergeAddFragSize
} vtss_qos_fp_port_conf_t;

/**
 * \brief Get 802.1Qbu and 802.3br (Frame Preemption) port configuration.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf    [OUT] Frame Preemption configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_fp_port_conf_get(const vtss_inst_t       inst,
                                  const vtss_port_no_t    port_no,
                                  vtss_qos_fp_port_conf_t *const conf);

/**
 * \brief Set 802.1Qbu and 802.3br (Frame Preemption) port configuration.
 *
 * \param inst    [IN] Target instance reference.
 * \param port_no [IN] Port number.
 * \param conf    [IN] Frame Preemption configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_fp_port_conf_set(const vtss_inst_t             inst,
                                  const vtss_port_no_t          port_no,
                                  const vtss_qos_fp_port_conf_t *const conf);

/**
 * \brief MAC Merge Status Verify (aMACMergeStatusVerify in 802.3br)
 **/
typedef enum {
    VTSS_MM_STATUS_VERIFY_INITIAL,   /**< INIT_VERIFICATION */
    VTSS_MM_STATUS_VERIFY_IDLE,      /**< VERIFICATION_IDLE */
    VTSS_MM_STATUS_VERIFY_SEND,      /**< SEND_VERIFY */
    VTSS_MM_STATUS_VERIFY_WAIT,      /**< WAIT_FOR_RESPONSE */
    VTSS_MM_STATUS_VERIFY_SUCCEEDED, /**< VERIFIED */
    VTSS_MM_STATUS_VERIFY_FAILED,    /**< VERIFY_FAIL */
    VTSS_MM_STATUS_VERIFY_DISABLED   /**< Verification process is disabled */
} vtss_mm_status_verify_t;

/**
 * \brief 802.1Qbu and 802.3br (Frame Preemption) port status
 **/
typedef struct {
    u32                     hold_advance;      // TBD: IEEE802.1Qbu: holdAdvance [nsec]
    u32                     release_advance;   // TBD: IEEE802.1Qbu: releaseAdvance [nsec]
    BOOL                    preemption_active; // IEEE802.1Qbu: preemptionActive, IEEE802.3br: aMACMergeStatusTx
    u8                      hold_request;      // TBD: IEEE802.1Qbu: holdRequest
    vtss_mm_status_verify_t status_verify;     // IEEE802.3br: aMACMergeStatusVerify
} vtss_qos_fp_port_status_t;

/**
 * \brief Get 802.1Qbu and 802.3br (Frame Preemption) port status.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status  [OUT] Frame Preemption status structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_qos_fp_port_status_get(const vtss_inst_t         inst,
                                    const vtss_port_no_t      port_no,
                                    vtss_qos_fp_port_status_t *const status);
#endif /* defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) */

#endif /* _VTSS_TSN_API_H_ */
