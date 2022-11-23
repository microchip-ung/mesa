// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PORT_STATE_H_
#define _VTSS_PORT_STATE_H_

#if defined(VTSS_FEATURE_PORT_CONTROL)
typedef struct {
    u64 value; /**< Accumulated value (64 bit) */
    u64 prev;  /**< Previous value read (32 or 40 bit) */
} vtss_chip_counter_t;

typedef struct {
    vtss_chip_counter_t emac;
    vtss_chip_counter_t pmac;
} vtss_dual_counter_t;

typedef struct {
    /* Rx counters */
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_dual_counter_t rx_octets;
    vtss_dual_counter_t rx_unicast;
    vtss_dual_counter_t rx_multicast;
    vtss_dual_counter_t rx_broadcast;
    vtss_dual_counter_t rx_shorts;
    vtss_dual_counter_t rx_fragments;
    vtss_dual_counter_t rx_jabbers;
    vtss_dual_counter_t rx_crc_align_errors;
    vtss_dual_counter_t rx_symbol_errors;
    vtss_dual_counter_t rx_64;
    vtss_dual_counter_t rx_65_127;
    vtss_dual_counter_t rx_128_255;
    vtss_dual_counter_t rx_256_511;
    vtss_dual_counter_t rx_512_1023;
    vtss_dual_counter_t rx_1024_1526;
    vtss_dual_counter_t rx_1527_max;
    vtss_dual_counter_t rx_pause;
    vtss_dual_counter_t rx_control;
    vtss_dual_counter_t rx_longs;
#else
    vtss_chip_counter_t rx_octets;
    vtss_chip_counter_t rx_unicast;
    vtss_chip_counter_t rx_multicast;
    vtss_chip_counter_t rx_broadcast;
    vtss_chip_counter_t rx_shorts;
    vtss_chip_counter_t rx_fragments;
    vtss_chip_counter_t rx_jabbers;
    vtss_chip_counter_t rx_crc_align_errors;
    vtss_chip_counter_t rx_symbol_errors;
    vtss_chip_counter_t rx_64;
    vtss_chip_counter_t rx_65_127;
    vtss_chip_counter_t rx_128_255;
    vtss_chip_counter_t rx_256_511;
    vtss_chip_counter_t rx_512_1023;
    vtss_chip_counter_t rx_1024_1526;
    vtss_chip_counter_t rx_1527_max;
    vtss_chip_counter_t rx_pause;
    vtss_chip_counter_t rx_control;
    vtss_chip_counter_t rx_longs;
#endif
    vtss_chip_counter_t rx_classified_drops;
    vtss_chip_counter_t rx_red_class[VTSS_PRIOS];
    vtss_chip_counter_t rx_yellow_class[VTSS_PRIOS];
    vtss_chip_counter_t rx_green_class[VTSS_PRIOS];
    /* Drop counters */
    vtss_chip_counter_t dr_local;
    vtss_chip_counter_t dr_tail;
    vtss_chip_counter_t dr_yellow_class[VTSS_PRIOS];
    vtss_chip_counter_t dr_green_class[VTSS_PRIOS];

    /* Tx counters */
    vtss_chip_counter_t tx_collision;
    vtss_chip_counter_t tx_drops;
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_dual_counter_t tx_octets;
    vtss_dual_counter_t tx_unicast;
    vtss_dual_counter_t tx_multicast;
    vtss_dual_counter_t tx_broadcast;
    vtss_dual_counter_t tx_pause;
    vtss_dual_counter_t tx_64;
    vtss_dual_counter_t tx_65_127;
    vtss_dual_counter_t tx_128_255;
    vtss_dual_counter_t tx_256_511;
    vtss_dual_counter_t tx_512_1023;
    vtss_dual_counter_t tx_1024_1526;
    vtss_dual_counter_t tx_1527_max;
#else
    vtss_chip_counter_t tx_octets;
    vtss_chip_counter_t tx_unicast;
    vtss_chip_counter_t tx_multicast;
    vtss_chip_counter_t tx_broadcast;
    vtss_chip_counter_t tx_pause;
    vtss_chip_counter_t tx_64;
    vtss_chip_counter_t tx_65_127;
    vtss_chip_counter_t tx_128_255;
    vtss_chip_counter_t tx_256_511;
    vtss_chip_counter_t tx_512_1023;
    vtss_chip_counter_t tx_1024_1526;
    vtss_chip_counter_t tx_1527_max;
#endif
    vtss_chip_counter_t tx_yellow_class[VTSS_PRIOS];
    vtss_chip_counter_t tx_green_class[VTSS_PRIOS];
    vtss_chip_counter_t tx_aging;
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_chip_counter_t tx_llct;
    vtss_chip_counter_t tx_ct;

    /* Rx counters */
    vtss_chip_counter_t rx_mm_assembly_errors; /* 802.3br aMACMergeFrameAssErrorCount */
    vtss_chip_counter_t rx_mm_smd_errors;      /* 802.3br aMACMergeFrameSmdErrorCount */
    vtss_chip_counter_t rx_mm_assembly_ok;     /* 802.3br aMACMergeFrameAssOkCount    */
    vtss_chip_counter_t rx_mm_fragments;       /* 802.3br aMACMergeFragCountRx        */
    vtss_chip_counter_t tx_mm_fragments;       /* 802.3br aMACMergeFragCountTx */
    vtss_chip_counter_t tx_mm_hold;            /* 802.3br aMACMergeHoldCountTx */
#endif
} vtss_port_luton26_counters_t;

typedef struct {
    /* Rx counters */
    vtss_chip_counter_t rx_in_bytes;
    vtss_chip_counter_t rx_symbol_err;
    vtss_chip_counter_t rx_pause;
    vtss_chip_counter_t rx_unsup_opcode;
    vtss_chip_counter_t rx_ok_bytes;
    vtss_chip_counter_t rx_bad_bytes;
    vtss_chip_counter_t rx_unicast;
    vtss_chip_counter_t rx_multicast;
    vtss_chip_counter_t rx_broadcast;
    vtss_chip_counter_t rx_crc_err;
    vtss_chip_counter_t rx_undersize;
    vtss_chip_counter_t rx_fragments;
    vtss_chip_counter_t rx_in_range_len_err;
    vtss_chip_counter_t rx_out_of_range_len_err;
    vtss_chip_counter_t rx_oversize;
    vtss_chip_counter_t rx_jabbers;
    vtss_chip_counter_t rx_size64;
    vtss_chip_counter_t rx_size65_127;
    vtss_chip_counter_t rx_size128_255;
    vtss_chip_counter_t rx_size256_511;
    vtss_chip_counter_t rx_size512_1023;
    vtss_chip_counter_t rx_size1024_1518;
    vtss_chip_counter_t rx_size1519_max;
    vtss_chip_counter_t rx_local_drops;
#if defined(VTSS_FEATURE_QOS)
    vtss_chip_counter_t rx_classified_drops;
    vtss_chip_counter_t rx_red_class[VTSS_PRIOS];
    vtss_chip_counter_t rx_yellow_class[VTSS_PRIOS];
    vtss_chip_counter_t rx_green_class[VTSS_PRIOS];
    vtss_chip_counter_t rx_policer_drops[VTSS_PRIOS];
    vtss_chip_counter_t rx_queue_drops[VTSS_PRIOS];
    vtss_chip_counter_t rx_txqueue_drops[VTSS_PRIOS];
#endif

    /* Tx counters */
    vtss_chip_counter_t tx_out_bytes;
    vtss_chip_counter_t tx_pause;
    vtss_chip_counter_t tx_ok_bytes;
    vtss_chip_counter_t tx_unicast;
    vtss_chip_counter_t tx_multicast;
    vtss_chip_counter_t tx_broadcast;
    vtss_chip_counter_t tx_size64;
    vtss_chip_counter_t tx_size65_127;
    vtss_chip_counter_t tx_size128_255;
    vtss_chip_counter_t tx_size256_511;
    vtss_chip_counter_t tx_size512_1023;
    vtss_chip_counter_t tx_size1024_1518;
    vtss_chip_counter_t tx_size1519_max;
#if defined(VTSS_FEATURE_QOS)
    vtss_chip_counter_t tx_yellow_class[VTSS_PRIOS];
    vtss_chip_counter_t tx_green_class[VTSS_PRIOS];
    vtss_chip_counter_t tx_queue_drops[VTSS_PRIOS];
#endif
    vtss_chip_counter_t tx_multi_coll;
    vtss_chip_counter_t tx_late_coll;
    vtss_chip_counter_t tx_xcoll;
    vtss_chip_counter_t tx_defer;
    vtss_chip_counter_t tx_xdefer;
    vtss_chip_counter_t tx_csense;
    vtss_chip_counter_t tx_backoff1;
} vtss_port_jr1_counters_t;

typedef struct {
    /* Rx counters */
    vtss_chip_counter_t rx_in_bytes;
    vtss_chip_counter_t rx_symbol_err;
    vtss_chip_counter_t rx_pause;
    vtss_chip_counter_t rx_unsup_opcode;
    vtss_chip_counter_t rx_ok_bytes;
    vtss_chip_counter_t rx_bad_bytes;
    vtss_chip_counter_t rx_unicast;
    vtss_chip_counter_t rx_multicast;
    vtss_chip_counter_t rx_broadcast;
    vtss_chip_counter_t rx_crc_err;
    vtss_chip_counter_t rx_undersize;
    vtss_chip_counter_t rx_fragments;
    vtss_chip_counter_t rx_in_range_len_err;
    vtss_chip_counter_t rx_out_of_range_len_err;
    vtss_chip_counter_t rx_oversize;
    vtss_chip_counter_t rx_jabbers;
    vtss_chip_counter_t rx_size64;
    vtss_chip_counter_t rx_size65_127;
    vtss_chip_counter_t rx_size128_255;
    vtss_chip_counter_t rx_size256_511;
    vtss_chip_counter_t rx_size512_1023;
    vtss_chip_counter_t rx_size1024_1518;
    vtss_chip_counter_t rx_size1519_max;
    vtss_chip_counter_t rx_local_drops;
#if defined(VTSS_FEATURE_QOS)
    vtss_chip_counter_t rx_class[VTSS_PRIOS];
#endif
    vtss_chip_counter_t rx_policer_drops;

    /* Tx counters */
    vtss_chip_counter_t tx_out_bytes;
    vtss_chip_counter_t tx_pause;
    vtss_chip_counter_t tx_ok_bytes;
    vtss_chip_counter_t tx_unicast;
    vtss_chip_counter_t tx_multicast;
    vtss_chip_counter_t tx_broadcast;
    vtss_chip_counter_t tx_size64;
    vtss_chip_counter_t tx_size65_127;
    vtss_chip_counter_t tx_size128_255;
    vtss_chip_counter_t tx_size256_511;
    vtss_chip_counter_t tx_size512_1023;
    vtss_chip_counter_t tx_size1024_1518;
    vtss_chip_counter_t tx_size1519_max;
#if defined(VTSS_FEATURE_QOS)
    vtss_chip_counter_t tx_yellow_class[VTSS_PRIOS];
    vtss_chip_counter_t tx_green_class[VTSS_PRIOS];
    vtss_chip_counter_t tx_green_drops[VTSS_PRIOS];
    vtss_chip_counter_t tx_yellow_drops[VTSS_PRIOS];
#endif
    vtss_chip_counter_t tx_queue_drops;
    vtss_chip_counter_t tx_multi_coll;
    vtss_chip_counter_t tx_late_coll;
    vtss_chip_counter_t tx_xcoll;
    vtss_chip_counter_t tx_defer;
    vtss_chip_counter_t tx_xdefer;
    vtss_chip_counter_t tx_csense;
    vtss_chip_counter_t tx_backoff1;
} vtss_port_jr2_counters_t;

typedef struct {
    /* Rx counters */
    vtss_chip_counter_t rx_in_bytes;
    vtss_dual_counter_t rx_symbol_err;
    vtss_dual_counter_t rx_pause;
    vtss_dual_counter_t rx_unsup_opcode;
    vtss_dual_counter_t rx_ok_bytes;
    vtss_dual_counter_t rx_bad_bytes;
    vtss_dual_counter_t rx_unicast;
    vtss_dual_counter_t rx_multicast;
    vtss_dual_counter_t rx_broadcast;
    vtss_dual_counter_t rx_crc_err;
    vtss_dual_counter_t rx_undersize;
    vtss_dual_counter_t rx_fragments;
    vtss_dual_counter_t rx_in_range_len_err;
    vtss_dual_counter_t rx_out_of_range_len_err;
    vtss_dual_counter_t rx_oversize;
    vtss_dual_counter_t rx_jabbers;
    vtss_dual_counter_t rx_size64;
    vtss_dual_counter_t rx_size65_127;
    vtss_dual_counter_t rx_size128_255;
    vtss_dual_counter_t rx_size256_511;
    vtss_dual_counter_t rx_size512_1023;
    vtss_dual_counter_t rx_size1024_1518;
    vtss_dual_counter_t rx_size1519_max;
    vtss_chip_counter_t rx_local_drops;
#if defined(VTSS_FEATURE_QOS)
    vtss_chip_counter_t rx_class[VTSS_PRIOS];
#endif
    vtss_chip_counter_t rx_policer_drops;

    /* Tx counters */
    vtss_chip_counter_t tx_out_bytes;
    vtss_dual_counter_t tx_pause;
    vtss_dual_counter_t tx_ok_bytes;
    vtss_dual_counter_t tx_unicast;
    vtss_dual_counter_t tx_multicast;
    vtss_dual_counter_t tx_broadcast;
    vtss_dual_counter_t tx_size64;
    vtss_dual_counter_t tx_size65_127;
    vtss_dual_counter_t tx_size128_255;
    vtss_dual_counter_t tx_size256_511;
    vtss_dual_counter_t tx_size512_1023;
    vtss_dual_counter_t tx_size1024_1518;
    vtss_dual_counter_t tx_size1519_max;
#if defined(VTSS_FEATURE_QOS)
    vtss_chip_counter_t tx_yellow_class[VTSS_PRIOS];
    vtss_chip_counter_t tx_green_class[VTSS_PRIOS];
    vtss_chip_counter_t tx_green_drops[VTSS_PRIOS];
    vtss_chip_counter_t tx_yellow_drops[VTSS_PRIOS];
#endif
    vtss_chip_counter_t tx_queue_drops;
    vtss_chip_counter_t tx_multi_coll;
    vtss_chip_counter_t tx_late_coll;
    vtss_chip_counter_t tx_xcoll;
    vtss_chip_counter_t tx_defer;
    vtss_chip_counter_t tx_xdefer;
    vtss_chip_counter_t tx_csense;
    vtss_chip_counter_t tx_backoff1;
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    /* Rx counters */
    vtss_chip_counter_t rx_mm_assembly_errors; /* 802.3br aMACMergeFrameAssErrorCount */
    vtss_chip_counter_t rx_mm_smd_errors;      /* 802.3br aMACMergeFrameSmdErrorCount */
    vtss_chip_counter_t rx_mm_assembly_ok;     /* 802.3br aMACMergeFrameAssOkCount    */
    vtss_chip_counter_t rx_mm_fragments;       /* 802.3br aMACMergeFragCountRx        */
    vtss_chip_counter_t tx_mm_fragments;       /* 802.3br aMACMergeFragCountTx */
#endif
} vtss_port_fa_counters_t;

typedef struct {
    union {
        vtss_port_luton26_counters_t luton26; /* and serval1 */
        vtss_port_jr1_counters_t     jr1;
        vtss_port_jr2_counters_t     jr2;
        vtss_port_fa_counters_t      fa;
    } counter;
} vtss_port_chip_counters_t;

typedef struct
{
    BOOL link;        /**< FALSE if link has been down since last status read */
    struct {
        BOOL complete; /**< Aneg completion status */
        union {
            vtss_port_clause_37_adv_t cl37;    /**< Clause 37 advertisement results */
            vtss_port_sgmii_aneg_t    sgmii;   /**< Cisco-SGMII advertisement results */
            vtss_port_usxgmii_aneg_t  usxgmii; /**< USXGMII advertisement results */
        } partner;
    } autoneg;       /**< Autoneg status */
} vtss_port_clause_37_status_t;

#if defined(VTSS_ARCH_JAGUAR_2) && !defined(VTSS_ARCH_JAGUAR_2_B)
// Calendar calculator only works on JR2C and later and ServalT
#define VTSS_CALENDAR_CALC
#define VTSS_CALENDAR_LEN_MAX 512

typedef struct {
    u8   cbc[VTSS_CALENDAR_LEN_MAX]; // Resulting Cell Bus Calendar
    u32  len;                        // Length of calendar
    BOOL manual;                     // TRUE when #cbc is applied. FALSE if auto-calendar is applied
    BOOL dynamic;                    // TRUE when calendar is dynamically calcuated, FALSE when static (only valid when #manual is TRUE).
} vtss_calendar_t;
#endif /* defined(VTSS_ARCH_JAGUAR_2) && !defined(VTSS_ARCH_JAGUAR_2_B) */



#if defined(VTSS_FEATURE_PORT_KR_IRQ)

// Interrupt defines
#define KR_ACTV            (1 << 29)
#define KR_LPSVALID        (1 << 28)
#define KR_LPCVALID        (1 << 27)
#define KR_WT_DONE         (1 << 26)
#define KR_MW_DONE         (1 << 25)
#define KR_BER_BUSY_0      (1 << 24)
#define KR_BER_BUSY_1      (1 << 23)
#define KR_REM_RDY_0       (1 << 22)
#define KR_REM_RDY_1       (1 << 21)
#define KR_FRLOCK_0        (1 << 20)
#define KR_FRLOCK_1        (1 << 19)
#define KR_DME_VIOL_0      (1 << 18)
#define KR_DME_VIOL_1      (1 << 17)
#define KR_AN_XMIT_DISABLE (1 << 16)
#define KR_TRAIN           (1 << 15)
#define KR_RATE_DET        (1 << 14)
#define KR_CMPL_ACK        (1 << 13)
#define KR_AN_GOOD         (1 << 12)
#define KR_LINK_FAIL       (1 << 11)
#define KR_ABD_FAIL        (1 << 10)
#define KR_ACK_FAIL        (1 << 9)
#define KR_NP_FAIL         (1 << 8)
#define KR_NP_RX           (1 << 7)
#define KR_INCP_LINK       (1 << 6)
#define KR_GEN0_DONE       (1 << 5)
#define KR_GEN1_DONE       (1 << 4)
#define KR_AN_RATE         (0xF)
#define KR_ANEG_RATE_25G    7
#define KR_ANEG_RATE_25G_S  8
#define KR_ANEG_RATE_10G    9
#define KR_ANEG_RATE_5G     11
#define KR_ANEG_RATE_2G5    12
#define KR_ANEG_RATE_1G     13

typedef enum
{
    VTSS_COEFFICIENT_UPDATE_FRM,
    VTSS_STATUS_REPORT_FRM
} vtss_port_kr_frm_type_t;

typedef struct {
    vtss_port_kr_frm_type_t type;
    u16 data;
} vtss_port_kr_frame_t;

typedef enum {
    COEF_HOLD = 0,
    COEF_INCR = 1,
    COEF_DECR = 2,
    COEF_INIT = 0x1000,
    COEF_PRESET = 0x2000
} kr_coefficient_update_t;

typedef enum {
    STATUS_NOT_UPDATED = 0,
    STATUS_UPDATED = 1,
    STATUS_MINIMUM = 2,
    STATUS_MAXIMUM = 3,
} kr_status_report_t;

typedef struct {
    BOOL ber_enable;
    BOOL gen0_tmr_start;
    BOOL gen1_tmr_start;
    BOOL wt_start;
    BOOL mw_start;
    BOOL tr_done;
    BOOL ldcoef_vld;
    BOOL ldstat_vld;
    BOOL np_loaded;
    BOOL rate_done;
    BOOL start_training;
    BOOL stop_training;
    BOOL transmit_disable;
    BOOL training_failure;
    BOOL aneg_disable;
    BOOL next_page;
} vtss_port_kr_fw_req_t;

typedef struct {
    u16  amplitude;
    u16  tap_dly;
    u16  tap_adv;
    BOOL c0_done;
    BOOL compl_ack;
    BOOL base_page;
    u32  rs_fec_cc;
    u32  rs_fec_uc;
    BOOL sm_dis;
} vtss_port_kr_temp_storage_t;


#endif // defined(VTSS_FEATURE_PORT_KR_IRQ)

#define VTSS_SD6G_40_CNT 3

#if defined(VTSS_ARCH_SPARX5)
#define VTSS_SD28_CNT 33
#endif

typedef struct {
    /* CIL function pointers */
    vtss_rc (* miim_read)(struct vtss_state_s *vtss_state,
                          vtss_miim_controller_t miim_controller,
                          u8 miim_addr,
                          u8 addr,
                          u16 *value,
                          BOOL report_errors);
    vtss_rc (* miim_write)(struct vtss_state_s *vtss_state,
                           vtss_miim_controller_t miim_controller,
                           u8 miim_addr,
                           u8 addr,
                           u16 value,
                           BOOL report_errors);
    vtss_rc (* mmd_read)(struct vtss_state_s *vtss_state,
                         vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                         u16 addr, u16 *value, BOOL report_errors);
    vtss_rc (* mmd_read_inc)(struct vtss_state_s *vtss_state,
                             vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                             u16 addr, u16 *buf, u8 count, BOOL report_errors);
    vtss_rc (* mmd_write)(struct vtss_state_s *vtss_state,
                          vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                          u16 addr, u16 data, BOOL report_errors);
    vtss_rc (* map_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* conf_get)(struct vtss_state_s *vtss_state,
                         const vtss_port_no_t port_no,
                         vtss_port_conf_t *const conf);
    vtss_rc (* conf_set)(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);

    vtss_rc (* ifh_set)(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);
    vtss_rc (* clause_37_status_get)(struct vtss_state_s *vtss_state,
                                     const vtss_port_no_t port_no,
                                     vtss_port_clause_37_status_t *const status);
    vtss_rc (* clause_37_control_get)(struct vtss_state_s *vtss_state,
                                      const vtss_port_no_t           port_no,
                                      vtss_port_clause_37_control_t  *const control);
    vtss_rc (* clause_37_control_set)(struct vtss_state_s *vtss_state,
                                      const vtss_port_no_t port_no);

#if defined(VTSS_FEATURE_PORT_KR) || defined(VTSS_FEATURE_PORT_KR_IRQ)
    vtss_rc (* kr_conf_set)(struct vtss_state_s *vtss_state,
                            const vtss_port_no_t port_no);

    vtss_rc (* kr_status)(struct vtss_state_s *vtss_state,
                          const vtss_port_no_t port_no,
                          vtss_port_kr_status_t *const status);

    vtss_rc (* kr_fec_set)(struct vtss_state_s *vtss_state,
                           const vtss_port_no_t port_no);
#endif /* VTSS_FEATURE_PORT_KR) || VTSS_FEATURE_PORT_KR_IRQ */

#if defined(VTSS_FEATURE_PORT_KR_IRQ)
    vtss_rc (* kr_irq_get)(vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           u32 *const vector);

    vtss_rc (* kr_irq_activity)(vtss_inst_t inst,
                                u32 *const irq_mask);

    vtss_rc (* kr_event_enable)(vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                BOOL enable);

    vtss_rc (* kr_irq_mask_set)(vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                const u32 mask);

    vtss_rc (* kr_fw_msg)(struct vtss_state_s *vtss_state,
                          const vtss_port_no_t port_no);

    vtss_rc (* kr_fw_req)(struct vtss_state_s *vtss_state,
                          const vtss_port_no_t port_no,
                          vtss_port_kr_fw_req_t *const fw_req);

    vtss_rc (* kr_frame_set)(struct vtss_state_s *vtss_state,
                             const vtss_port_no_t port_no,
                             const vtss_port_kr_frame_t *const frm);

    vtss_rc (* kr_frame_get)(struct vtss_state_s *vtss_state,
                             const vtss_port_no_t port_no,
                             vtss_port_kr_frame_t *const frm);


    vtss_rc (* kr_coef_set)(struct vtss_state_s *vtss_state,
                            const vtss_port_no_t port_no,
                            const u16 coef_in,
                            vtss_kr_status_results_t *const sts);

    vtss_rc (* kr_eye_dim)(struct vtss_state_s *vtss_state,
                           const vtss_port_no_t port_no,
                           vtss_port_kr_eye_dim_t *const eye);

    vtss_rc (* kr_ber_cnt)(struct vtss_state_s *vtss_state,
                          const vtss_port_no_t port_no,
                          u16 *const ber);

#endif /* VTSS_FEATURE_PORT_KR_IRQ */
    vtss_rc (* kr_ctle_adjust)(struct vtss_state_s *vtss_state,
                               const vtss_port_no_t port_no);

    vtss_rc (* kr_ctle_get)(struct vtss_state_s *vtss_state,
                            const vtss_port_no_t port_no, vtss_port_ctle_t *const ctle);

    vtss_rc (* test_conf_set)(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);

    vtss_rc (* serdes_debug_set)(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no,
                                 const vtss_port_serdes_debug_t *const conf);

    vtss_rc (* status_get)(struct vtss_state_s *vtss_state,
                           const vtss_port_no_t  port_no,
                           vtss_port_status_t    *const status);
    vtss_rc (* counters_update)(struct vtss_state_s *vtss_state,
                                const vtss_port_no_t port_no);
    vtss_rc (* counters_clear)(struct vtss_state_s *vtss_state,
                               const vtss_port_no_t port_no);
    vtss_rc (* counters_get)(struct vtss_state_s *vtss_state,
                             const vtss_port_no_t port_no,
                             vtss_port_counters_t *const counters);
    vtss_rc (* basic_counters_get)(struct vtss_state_s *vtss_state,
                                   const vtss_port_no_t port_no,
                                   vtss_basic_counters_t *const counters);
    vtss_rc (* forward_set)(struct vtss_state_s *vtss_state,
                                 const vtss_port_no_t port_no);

    /* Configuration/state */
    vtss_port_map_t               map[VTSS_PORT_ARRAY_SIZE];
    vtss_port_conf_t              conf[VTSS_PORT_ARRAY_SIZE];
    BOOL                          conf_set_called[VTSS_PORT_ARRAY_SIZE];
    vtss_serdes_mode_t            sd6g40_mode[VTSS_SD6G_40_CNT];
#if defined(VTSS_ARCH_SPARX5)
    vtss_serdes_mode_t            sd28_mode[VTSS_SD28_CNT];
    u32                           cmu_enable_mask;
#endif
    vtss_serdes_mode_t            serdes_mode[VTSS_PORT_ARRAY_SIZE];
    vtss_port_clause_37_control_t clause_37[VTSS_PORT_ARRAY_SIZE];
    vtss_port_test_conf_t         test_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_port_speed_t             current_speed[VTSS_PORT_ARRAY_SIZE];
    vtss_port_interface_t         current_if_type[VTSS_PORT_ARRAY_SIZE];
    vtss_sd10g_media_type_t       current_mt[VTSS_PORT_ARRAY_SIZE];
    BOOL                          link[VTSS_PORT_ARRAY_SIZE];
    BOOL                          ctle_done[VTSS_PORT_ARRAY_SIZE];
#if defined(VTSS_FEATURE_PORT_KR) || defined(VTSS_FEATURE_PORT_KR_IRQ)
    vtss_port_kr_conf_t           kr_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_port_kr_fec_t            kr_fec[VTSS_PORT_ARRAY_SIZE];
#endif /* VTSS_FEATURE_PORT_KR */
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
    vtss_port_kr_state_t          train_state[VTSS_PORT_ARRAY_SIZE];
    vtss_port_kr_temp_storage_t   kr_store[VTSS_PORT_ARRAY_SIZE];
#endif /* VTSS_FEATURE_PORT_KR_IRQ */

    vtss_port_chip_counters_t     counters[VTSS_PORT_ARRAY_SIZE];
    vtss_port_chip_counters_t     cpu_counters;
#if defined(VTSS_FEATURE_PORT_IFH)
    vtss_port_ifh_t               ifh_conf[VTSS_PORT_ARRAY_SIZE];
#endif /* VTSS_FEATURE_PORT_IFH */
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_LAN966X)
    u32                           buf_prio_shr[VTSS_PRIOS]; /* Initial values of buf_prio_shr_i or buf_prio_shr_e watermarks */
#endif /* defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) */
    vtss_port_forward_t           forward[VTSS_PORT_ARRAY_SIZE];

#if defined(VTSS_ARCH_JAGUAR_2)
    vtss_port_mux_mode_t          mux_mode[VTSS_CHIP_CNT]; /* Port mux modes */
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_CALENDAR_CALC)
    vtss_calendar_t               calendar;
#endif /* defined(VTSS_CALENDAR_CALC) */
} vtss_port_state_t;

vtss_rc vtss_port_inst_create(struct vtss_state_s *vtss_state);
vtss_rc vtss_port_restart_sync(struct vtss_state_s *vtss_state);

vtss_port_no_t vtss_cmn_first_port_no_get(struct vtss_state_s *vtss_state,
                                          const BOOL port_list[VTSS_PORT_ARRAY_SIZE]);
#if VTSS_OPT_DEBUG_PRINT
vtss_port_no_t vtss_cmn_port2port_no(struct vtss_state_s *vtss_state,
                                     const vtss_debug_info_t *const info, u32 port);
#endif
vtss_port_no_t vtss_api_port(struct vtss_state_s *vtss_state, u32 chip_port);
vtss_rc vtss_port_conf_set_private(struct vtss_state_s    *vtss_state,
                                   const vtss_port_no_t   port_no,
                                   const vtss_port_conf_t *const conf);
vtss_rc vtss_cmn_port_clause_37_adv_get(u32 value, vtss_port_clause_37_adv_t *adv);
vtss_rc vtss_cmn_port_clause_37_adv_set(u32 *value, vtss_port_clause_37_adv_t *adv, BOOL aneg_enable);
vtss_rc vtss_cmn_port_sgmii_cisco_aneg_get(u32 value, vtss_port_sgmii_aneg_t *sgmii_adv);
vtss_rc vtss_cmn_port_usxgmii_aneg_get(u32 value, vtss_port_usxgmii_aneg_t *usxgmii);
#if VTSS_OPT_DEBUG_PRINT
void vtss_port_debug_print(struct vtss_state_s *vtss_state,
                           const vtss_debug_printf_t pr,
                           const vtss_debug_info_t   *const info);
#endif

#endif /* VTSS_FEATURE_PORT_CONTROL */

#endif /* _VTSS_PORT_STATE_H_ */
