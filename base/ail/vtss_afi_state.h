// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_AFI_STATE_H_
#define _VTSS_AFI_STATE_H_

#if defined(VTSS_FEATURE_AFI_SWC)

#if defined(VTSS_AFI_V1)

#define VTSS_AFI_TIMER_CNT 8

typedef enum {
    VTSS_AFI_SLOT_STATE_FREE,     /**< Slot is not in use                                                 */
    VTSS_AFI_SLOT_STATE_RESERVED, /**< Slot has been allocated, but no frames have been injected using it */
    VTSS_AFI_SLOT_STATE_ENABLED,  /**< Slot is allocated and a frame is using it                          */
    VTSS_AFI_SLOT_STATE_PAUSED,   /**< Slot is allocated, but currently paused (disabled in switch core)  */
} vtss_afi_slot_state_t;

typedef struct {
    /**
     * The current state of this slot.
     * The remaining members are only valid if #state != VTSS_AFI_SLOT_STATE_FREE.
     */
    vtss_afi_slot_state_t state;

    /**
     * Which timer is this slot using?
     * This points to an entry of type vtss_afi_timer_conf_t.
     */
    u32 timer_idx;

    /**
     * Which port number is this slot serving?
     */
    vtss_port_no_t port_no;
} vtss_afi_slot_conf_t;

typedef struct {
    u32 ref_cnt;
    u32 fps;
} vtss_afi_timer_conf_t;

typedef struct {
    vtss_afi_slot_conf_t  slots[VTSS_AFI_SLOT_CNT];
    vtss_afi_timer_conf_t timers[VTSS_AFI_TIMER_CNT];
    u32                   fps_per_section[2];
    BOOL                  link[VTSS_PORTS]; // To keep track of the AFI's knowledge about link state

    // Internal intra-API call to pass link state of a given port to the AFI module.
    // On entry, link_up contains the new value. On exit, it holds the old value (so it's an INOUT).
    vtss_rc (*link_state_change)(struct vtss_state_s *const vtss_state, vtss_port_no_t port_no, BOOL *link_up);

    // Internal intra-API call to get the AFI to update queue numbers, which may
    // have changed as a result of changing HQoS mode. It is guaranteed that
    // flows on that port are stopped prior to invoking it.
    // This may be NULL on platforms not requiring it.
    vtss_rc (*qu_ref_update)(struct vtss_state_s *const vtss_state, vtss_port_no_t port_no);

    vtss_rc (*alloc) (struct vtss_state_s *vtss_state, vtss_afi_frm_dscr_t *const dscr, vtss_afi_id_t *const id);
    vtss_rc (*free)  (struct vtss_state_s *vtss_state, vtss_afi_id_t id);
    vtss_rc (*hijack)(struct vtss_state_s *vtss_state, vtss_afi_id_t id);

} vtss_afi_state_t;

#endif /* defined(VTSS_AFI_V1) */

#if defined(VTSS_AFI_V2)

// Chip specific properties
// Note: API relevant chip properties are specified in vtss_afi_api.h.

// ========================================
// Jaguar2
// ----------------------------------------
#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C)
#define VTSS_AFI_FRM_CNT 4096

// Layout of AFI:MISC:NEW_FRM_INFO.FRM_INFO
#define VTSS_AFI_FRM_INFO_FP_POS    0
#define VTSS_AFI_FRM_INFO_FP_WID    15
#define VTSS_AFI_FRM_INFO_SHORT_POS 15
#define VTSS_AFI_FRM_INFO_SHORT_WID 1
#define VTSS_AFI_FRM_INFO_EPRIO_POS 16
#define VTSS_AFI_FRM_INFO_EPRIO_WID 3

// Layout of AFI:FRM_TBL:FRM_ENTRY_PART0.PART0
#define VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS   0
#define VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID   8
#define VTSS_AFI_FRM_TBL_PART0_FRM_RM_POS    9
#define VTSS_AFI_FRM_TBL_PART0_FRM_RM_WID    1
#define VTSS_AFI_FRM_TBL_PART0_FRM_GONE_POS 10
#define VTSS_AFI_FRM_TBL_PART0_FRM_GONE_WID  1
#define VTSS_AFI_FRM_TBL_PART0_FRM_INFO_POS 11
#define VTSS_AFI_FRM_TBL_PART0_FRM_INFO_WID 19

#define VTSS_AFI_FRM_TBL_PART0_DELAY_POS     0
#define VTSS_AFI_FRM_TBL_PART0_DELAY_WID    30

// Threshold for when BW shall be set to 1
#define VTSS_AFI_DTI_BW1_THRES_BPS 5000000000ULL

// Width of AFI:TTI_TBL:TTI_TIMER.TIMER_LEN
#define VTSS_AFI_TTI_TBL_TIMER_LEN_WID 9

// Maximum value of TRAILING_DELAY_SEQ_CNT
#define VTSS_AFI_TRAILING_DELAY_SEQ_CNT_MAX 63

// Default values
#define VTSS_AFI_FRM_OUT_MAX_DEF         16

#endif /* VTSS_ARCH_JAGUAR_2_B || VTSS_ARCH_JAGUAR_2_C */

// ========================================
// FireAnt/Laguna
// ----------------------------------------
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
#if defined(VTSS_ARCH_SPARX5)
#define VTSS_AFI_FRM_CNT  4096
#else
#define VTSS_AFI_FRM_CNT  512
#endif
#define VTSS_AFI_FP_WID   (FA_TGT ? 15 : 14)
#define VTSS_AFI_DSTP_WID (FA_TGT ? 7 : 6)

// Layout of AFI:MISC:NEW_FRM_INFO.FRM_INFO
#define VTSS_AFI_FRM_INFO_FP_POS    0
#define VTSS_AFI_FRM_INFO_FP_WID    VTSS_AFI_FP_WID
#define VTSS_AFI_FRM_INFO_DSTP_POS  (VTSS_AFI_FRM_INFO_FP_POS + VTSS_AFI_FRM_INFO_FP_WID)
#define VTSS_AFI_FRM_INFO_DSTP_WID  VTSS_AFI_DSTP_WID
#define VTSS_AFI_FRM_INFO_EPRIO_POS (VTSS_AFI_FRM_INFO_DSTP_POS + VTSS_AFI_FRM_INFO_DSTP_WID)
#define VTSS_AFI_FRM_INFO_EPRIO_WID 3
#define VTSS_AFI_FRM_INFO_SHORT_POS (VTSS_AFI_FRM_INFO_EPRIO_POS + VTSS_AFI_FRM_INFO_EPRIO_WID)
#define VTSS_AFI_FRM_INFO_SHORT_WID 1

// Layout of AFI:FRM_TBL:FRM_ENTRY_PART0.PART0
#define VTSS_AFI_FRM_TBL_PART0_FP_POS      0
#define VTSS_AFI_FRM_TBL_PART0_FP_WID      VTSS_AFI_FP_WID
#define VTSS_AFI_FRM_TBL_PART0_DSTP_POS    (VTSS_AFI_FRM_TBL_PART0_FP_POS + VTSS_AFI_FRM_TBL_PART0_FP_WID)
#define VTSS_AFI_FRM_TBL_PART0_DSTP_WID    VTSS_AFI_DSTP_WID
#define VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS (VTSS_AFI_FRM_TBL_PART0_DSTP_POS + VTSS_AFI_FRM_TBL_PART0_DSTP_WID)
#define VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID 8

// Layout of AFI:FRM_TBL:FRM_ENTRY_PART1.PART1
#define VTSS_AFI_FRM_TBL_PART1_SHORT_POS 0
#define VTSS_AFI_FRM_TBL_PART1_SHORT_WID 1
#define VTSS_AFI_FRM_TBL_PART1_EPRIO_POS 1
#define VTSS_AFI_FRM_TBL_PART1_EPRIO_WID 3
#define VTSS_AFI_FRM_TBL_PART1_RM_POS    4
#define VTSS_AFI_FRM_TBL_PART1_RM_WID    1
#define VTSS_AFI_FRM_TBL_PART1_GONE_POS  5
#define VTSS_AFI_FRM_TBL_PART1_GONE_WID  1

#define VTSS_AFI_FRM_TBL_PART0_DELAY_POS 0
#define VTSS_AFI_FRM_TBL_PART0_DELAY_WID 30

// Threshold for when BW shall be set to 1
#define VTSS_AFI_DTI_BW1_THRES_BPS 5000000000ULL

// Width of AFI:TTI_TBL:TTI_TIMER.TIMER_LEN
#define VTSS_AFI_TTI_TBL_TIMER_LEN_WID 9

// Maximum value of TRAILING_DELAY_SEQ_CNT
#define VTSS_AFI_TRAILING_DELAY_SEQ_CNT_MAX 63

// Default values
#define VTSS_AFI_FRM_OUT_MAX_DEF         16
#endif

// ========================================
// ServalT
// TOETBD: Some SKUs will have slower clock
// ----------------------------------------
#if defined(VTSS_ARCH_SERVAL_T)
#define VTSS_AFI_FRM_CNT 2048

// Layout of AFI:MISC:NEW_FRM_INFO.FRM_INFO
#define VTSS_AFI_FRM_INFO_FP_POS    0
#define VTSS_AFI_FRM_INFO_FP_WID    13
#define VTSS_AFI_FRM_INFO_SHORT_POS 13
#define VTSS_AFI_FRM_INFO_SHORT_WID 1
#define VTSS_AFI_FRM_INFO_EPRIO_POS 14
#define VTSS_AFI_FRM_INFO_EPRIO_WID 3

// Layout of AFI:FRM_TBL:FRM_ENTRY_PART0.PART0
#define VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS   0
#define VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID   8
#define VTSS_AFI_FRM_TBL_PART0_FRM_RM_POS   11
#define VTSS_AFI_FRM_TBL_PART0_FRM_RM_WID    1
#define VTSS_AFI_FRM_TBL_PART0_FRM_GONE_POS 12
#define VTSS_AFI_FRM_TBL_PART0_FRM_GONE_WID  1
#define VTSS_AFI_FRM_TBL_PART0_FRM_INFO_POS 13
#define VTSS_AFI_FRM_TBL_PART0_FRM_INFO_WID 17

#define VTSS_AFI_FRM_TBL_PART0_DELAY_POS     0
#define VTSS_AFI_FRM_TBL_PART0_DELAY_WID    30

// Threshold for when BW shall be set to 1
#define VTSS_AFI_DTI_BW1_THRES_BPS 4000000000ULL

// Width of AFI:TTI_TBL:TTI_TIMER.TIMER_LEN
#define VTSS_AFI_TTI_TBL_TIMER_LEN_WID 9

// Maximum value of TRAILING_DELAY_SEQ_CNT
#define VTSS_AFI_TRAILING_DELAY_SEQ_CNT_MAX 63

// Default values
#define VTSS_AFI_FRM_OUT_MAX_DEF         16

#endif /* VTSS_ARCH_SERVAL_T */

// These constants define what we would like each tick
// to be set to. What is actually achievable with the
// actual chip's clock period is then figured out
// dynamically.
#define VTSS_AFI_TTI_TICK_LEN0_US        52 /* 52us   */
#define VTSS_AFI_TTI_TICK_LEN1_US       416 /* 416us  */
#define VTSS_AFI_TTI_TICK_LEN2_US      3333 /* 3.333ms. Don't change to 3300, since that'll give a wrong divisor */
#define VTSS_AFI_TTI_TICK_LEN3_US     10000 /* 10     */
#define VTSS_AFI_TTI_TICK_LEN4_US    100000 /* 100ms  */
#define VTSS_AFI_TTI_TICK_LEN5_US   1000000 /* 1s     */
#define VTSS_AFI_TTI_TICK_LEN6_US  10000000 /* 10s    */
#define VTSS_AFI_TTI_TICK_LEN7_US  60000000 /* 1min   */

// ========================================
// LAN966X
// ----------------------------------------
#if defined(VTSS_ARCH_LAN966X)
#define VTSS_AFI_FRM_CNT 2048

// Layout of AFI:MISC:NEW_FRM_INFO.FRM_INFO
#define VTSS_AFI_FRM_INFO_FP_POS    0
#if defined(VTSS_ARCH_LAN966X_FPGA)
#define VTSS_AFI_FRM_INFO_FP_WID    9
#else
#define VTSS_AFI_FRM_INFO_FP_WID    12
#endif
#define VTSS_AFI_FRM_INFO_DSTP_POS  (VTSS_AFI_FRM_INFO_FP_POS + VTSS_AFI_FRM_INFO_FP_WID)
#define VTSS_AFI_FRM_INFO_DSTP_WID  4
#define VTSS_AFI_FRM_INFO_EPRIO_POS (VTSS_AFI_FRM_INFO_DSTP_POS + VTSS_AFI_FRM_INFO_DSTP_WID)
#define VTSS_AFI_FRM_INFO_EPRIO_WID 3
#define VTSS_AFI_FRM_INFO_SHORT_POS (VTSS_AFI_FRM_INFO_EPRIO_POS + VTSS_AFI_FRM_INFO_EPRIO_WID)
#define VTSS_AFI_FRM_INFO_SHORT_WID 1

// Layout of AFI:FRM_TBL:FRM_ENTRY_PART0.PART0
#define VTSS_AFI_FRM_TBL_PART0_FP_POS      0
#if defined(VTSS_ARCH_LAN966X_FPGA)
#define VTSS_AFI_FRM_TBL_PART0_FP_WID      9
#else
#define VTSS_AFI_FRM_TBL_PART0_FP_WID      12
#endif
#define VTSS_AFI_FRM_TBL_PART0_DSTP_POS    (VTSS_AFI_FRM_TBL_PART0_FP_POS + VTSS_AFI_FRM_TBL_PART0_FP_WID)
#define VTSS_AFI_FRM_TBL_PART0_DSTP_WID    4
#define VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS (VTSS_AFI_FRM_TBL_PART0_DSTP_POS + VTSS_AFI_FRM_TBL_PART0_DSTP_WID)
#define VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID 8

// Layout of AFI:FRM_TBL:FRM_ENTRY_PART1.PART1
#define VTSS_AFI_FRM_TBL_PART1_SHORT_POS 0
#define VTSS_AFI_FRM_TBL_PART1_SHORT_WID 1
#define VTSS_AFI_FRM_TBL_PART1_EPRIO_POS 1
#define VTSS_AFI_FRM_TBL_PART1_EPRIO_WID 3
#define VTSS_AFI_FRM_TBL_PART1_RM_POS    4
#define VTSS_AFI_FRM_TBL_PART1_RM_WID    1
#define VTSS_AFI_FRM_TBL_PART1_GONE_POS  5
#define VTSS_AFI_FRM_TBL_PART1_GONE_WID  1

#define VTSS_AFI_FRM_TBL_PART0_DELAY_POS 0
#define VTSS_AFI_FRM_TBL_PART0_DELAY_WID 30

// Threshold for when BW shall be set to 1
#define VTSS_AFI_DTI_BW1_THRES_BPS 5000000000ULL

// Width of AFI:TTI_TBL:TTI_TIMER.TIMER_LEN
#define VTSS_AFI_TTI_TBL_TIMER_LEN_WID 9

// Maximum value of TRAILING_DELAY_SEQ_CNT
#define VTSS_AFI_TRAILING_DELAY_SEQ_CNT_MAX 63

// Default values
#define VTSS_AFI_FRM_OUT_MAX_DEF         16

#endif /* VTSS_ARCH_LAN966X */

// ========================================

// AFI::NEW_FRM_INFO
typedef struct {
    u32 fp;
    u8  fshort;
    u8  eprio;
    u8  dstp;
} frm_info_t;

// Frame entry type
typedef struct {
    u32        frm_size; // Frame size. Only used for DTI bandwidth calculation. Need not match actual frame size.
    u32        inj_cnt;  // Injection count
    frm_info_t frm_info; // Maintained by CIL
} frm_tbl_frm_t;

// Delay entry type
typedef struct {
    u32 delay; // Clock cycles
} frm_tbl_delay_t;

// FRM_TBL entry
typedef struct {
    u8  entry_type; // 0 = Frame, 1 = Delay
    u32 next_ptr;   // Index of next FRM_TBL entry in sequence

    // Content depending on entry_type
    union {
        frm_tbl_frm_t   frm;
        frm_tbl_delay_t delay;
    } frm_delay;
} vtss_afi_frm_t;

typedef enum {
    VTSS_AFI_ENTRY_STATE_FREE,      /**< Entry is not in use                                  */
    VTSS_AFI_ENTRY_STATE_STOPPED,   /**< Entry is allocated and hijacked, but stopped by user */
    VTSS_AFI_ENTRY_STATE_STARTED,   /**< Entry is allocated and hijacked, and started by user */
} vtss_afi_entry_state_t;

// DTI_TBL entry
typedef struct {
    // Arguments to most recent call to vtss_afi_fast_inj_start()
    vtss_afi_fast_inj_start_cfg_t start_cfg;

    // State of this entry (free/user-started/user-stopped)
    vtss_afi_entry_state_t state;

    // DTI is paused by driver due to missing link on either down- or up-port.
    // For a flow to be started, state must be VTSS_AFI_ENTRY_STATE_STARTED and
    // paused must be 0.
    BOOL paused;

    // DTI_MODE fields (except for dti_ena)
    // 0 = inject sequence a given number of times.
    // 1 = inject until stopped
    u8  mode;
    u8  bw;
#if !defined(VTSS_ARCH_JAGUAR_2_B)
    u8  dti_next;
#endif
    u32 trailing_delay_seq_cnt;
    u32 frm_inj_cnt;

    // DTI_PORT_QU fields
    vtss_port_no_t port_no;
    vtss_prio_t    prio;

    // Points to the first entry in frm_tbl[] for this flow.
    // Is 0 when no such entry has been allocated.
    u32 first_frm_idx;

    u8  frm_cnt; // Number of frames in sequence.

    // When masquerading (creating up-flows), #port_no is set to
    // VTSS_PORT_NO_NONE. The following member is the port, the up-flows are
    // ingressing in that case.
    // When not masquerading (creating down-flows), #port_no is set to a real
    // port number, and the following is set to VTSS_PORT_NO_NONE.
    vtss_port_no_t masquerade_port_no;
} vtss_afi_dti_t;

// TTI_TBL entry
typedef struct {
    // Arguments to most recent call to vtss_afi_slow_inj_start()
    vtss_afi_slow_inj_start_cfg_t start_cfg;

    // State of this entry (free/user-started/user-stopped)
    vtss_afi_entry_state_t state;

    // TTI is paused by driver due to missing link on either down- or up-port.
    // For a flow to be started, state must be VTSS_AFI_ENTRY_STATE_STARTED and
    // paused must be 0.
    BOOL paused;

    // TTI frame has been hijacked
    BOOL hijacked;

    // TTI_TIMER fields (except for timer_ena)
    // For Jaguar2 timer is stopped by setting timer_len=0.
    u8  tick_idx;
    u8  jitter;
    u16 timer_len;

    i32 frm_idx;      // TTI_FRM.FRM_PTR. -1 => No FRM allocated.
    u16 tick_cnt;     // TTI_TICKS.TICK_CNT
    u8  inj_cnt_ena;  // TTI_MISC_CFG.INJ_CNT_ENA

    // TTI_PORT_QU fields
    vtss_port_no_t port_no;
    vtss_prio_t    prio;

    // When masquerading (creating up-flows), #port_no is set to
    // VTSS_PORT_NO_NONE. The following member is the port, the up-flows are
    // ingressing in that case.
    // When not masquerading (creating down-flows), #port_no is set to a real
    // port number, and the following is set to VTSS_PORT_NO_NONE.
    vtss_port_no_t masquerade_port_no;
} vtss_afi_tti_t;

// PORT_TBL entry
typedef struct {
    BOOL started; // Injections administratively allowed
    BOOL link;    // TOETBD: Link up/down handling?

    // PORT_CFG fields
    u8  fc_skip_tti_inj;
    u16 frm_out_max;
#if !defined(VTSS_ARCH_JAGUAR_2_B)
    u8  frm_rm_only;
#endif
} vtss_afi_port_t;

typedef struct {
    // CIL function pointers
    vtss_rc (*afi_enable)(      struct vtss_state_s *const vtss_state);
    vtss_rc (*ttis_enable)(     struct vtss_state_s *const vtss_state);

    vtss_rc (*tti_start)(       struct vtss_state_s *const vtss_state, u32 tti_idx, BOOL do_config);
    vtss_rc (*tti_stop)(        struct vtss_state_s *const vtss_state, u32 tti_idx);
    vtss_rc (*tti_frm_hijack)(  struct vtss_state_s *const vtss_state, u32 tti_idx);
    vtss_rc (*tti_frm_rm_inj)(  struct vtss_state_s *const vtss_state, u32 tti_idx);

    vtss_rc (*dti_start)(       struct vtss_state_s *const vtss_state, u32 dti_idx, BOOL do_frm_delay_config, BOOL do_dti_config, BOOL start_flow);
    vtss_rc (*dti_stop)(        struct vtss_state_s *const vtss_state, u32 dti_idx);
    vtss_rc (*dti_frm_hijack)(  struct vtss_state_s *const vtss_state, u32 dti_idx, u32 frm_size);
    vtss_rc (*dti_frm_rm_inj)(  struct vtss_state_s *const vtss_state, u32 dti_idx);
    vtss_rc (*dti_cnt_get)(     struct vtss_state_s *const vtss_state, u32 dti_idx, u32 *const cnt);

    // Administrative port start/stop
    vtss_rc (*port_admin_start)(struct vtss_state_s *const vtss_state, vtss_port_no_t port_no);
    vtss_rc (*port_admin_stop)( struct vtss_state_s *const vtss_state, vtss_port_no_t port_no);

    // Internal intra-API call to pass link state of a given port to the AFI module.
    // On entry, link_up contains the new value. On exit, it holds the old value (so it's an INOUT).
    vtss_rc (*link_state_change)(struct vtss_state_s *const vtss_state, vtss_port_no_t port_no, BOOL *link_up);

    // Internal intra-API call to get the AFI to update queue numbers, which may
    // have changed as a result of changing HQoS mode. It is guaranteed that
    // flows on that port are stopped prior to invoking it.
    // This may be NULL on platforms not requiring it.
    vtss_rc (*qu_ref_update)(struct vtss_state_s *const vtss_state, vtss_port_no_t port_no);

    // FRM_TBL/DTI_TBL/TTI_TBL allocation. One bit per entry.
    u32 frms_alloced[(VTSS_AFI_FRM_CNT      + 31) / 32];
    u32 dtis_alloced[(VTSS_AFI_FAST_INJ_CNT + 31) / 32];
    u32 ttis_alloced[(VTSS_AFI_SLOW_INJ_CNT + 31) / 32];

    // ==================
    // Chip configuration
    // ------------------
    // The following fields are maintained by CIL
    //   frm_tbl.frm_delay.frm.frm_info
    //   dti_tbl.started
    //   tti_tbl.started
    //   port_tbl.started
    // All other fields are maintained by AIL.

    u8  afi_ena; // MISC_CTRL.AFI_ENA. Set when TTI/DTI is alloced.
    u8  tti_ena; // TTI_CTRL.TTI_ENA. Set when first TTI is alloced.

    // FRM_TBL
    vtss_afi_frm_t frm_tbl[VTSS_AFI_FRM_CNT];

    // DTI_TBL
    vtss_afi_dti_t dti_tbl[VTSS_AFI_FAST_INJ_CNT];

    // TTI_TBL
    vtss_afi_tti_t tti_tbl[VTSS_AFI_SLOW_INJ_CNT];

    // PORT_TBL
    // Indexed by logical port number (vtss_port_no_t) + 1 for VD1 (last in range).
    vtss_afi_port_t port_tbl[VTSS_PORTS + 1];

    // TICK length
    u32 tick_len_us[8];

    // Switch core's clock period in picoseconds
    u64 clk_period_ps;
} vtss_afi_state_t;

vtss_rc vtss_afi_inst_create(struct vtss_state_s *vtss_state);
void vtss_afi_debug_print(struct vtss_state_s *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info);

// ========================================
// Functions shared with CIL
// ----------------------------------------

vtss_rc afi_frm_idx_chk(struct vtss_state_s *vtss_state, i32 frm_idx);

// ----------------------------------------
// Functions shared with CIL
// ========================================

#endif // VTSS_AFI_V2
#endif // VTSS_FEATURE_AFI_SWC
#endif // _VTSS_AFI_STATE_H_
