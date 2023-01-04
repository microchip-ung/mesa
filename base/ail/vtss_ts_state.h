// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_TS_STATE_H_
#define _VTSS_TS_STATE_H_

#if defined(VTSS_FEATURE_TIMESTAMP)

#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
#define VTSS_TS_ID_SIZE  63
#define TS_IDS_RESERVED_FOR_SW 4
#endif /* VTSS_ARCH_LUTON26 || VTSS_ARCH_OCELOT */

#if defined (VTSS_ARCH_OCELOT)
#define VTSS_VOE_ID_SIZE  VTSS_VOE_CNT
#endif /* VTSS_ARCH_OCELOT */

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)  /* TBD_HENRIKB */
#define VTSS_TS_ID_SIZE  3 // tbd
#define TS_IDS_RESERVED_FOR_SW 3
#define TS_PORT_ID_PORT_NUMBER_DEFAULT 0x9ABC
#endif /* VTSS_ARCH_JAGUAR_2 */

typedef struct {
    vtss_ts_ext_clock_mode_t ext_clock_mode;
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
    vtss_ts_ext_clock_mode_t ext_clock_mode_alt;
    vtss_ts_alt_clock_mode_t alt_clock_mode;
#endif
    i32 adj[VTSS_TS_DOMAIN_ARRAY_SIZE];
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)    /* TBD_HENRIKB */
    vtss_timestamp_t sample_ts[VTSS_TS_DOMAIN_ARRAY_SIZE]; /* Sampled timestamp pr domain */
    u64              sample_tc[VTSS_TS_DOMAIN_ARRAY_SIZE]; /* Timecounter corresponding to sampled timestamp pr domain */
#else
    i32 adj_divisor;
    u32 delta_sec;              /* outstanding delta time */
    u16 delta_sec_msb;          /* outstanding delta time */
    u16 delta_sign;             /* 0 if no outstanding delta, 1 if neg, 2 if pos */
    BOOL sw_ts_id_res [TS_IDS_RESERVED_FOR_SW]; /* reservation flags for Luton 26 timestamps */
#endif
    u32 sec_offset; /* current offset from HW timer */
    u32 outstanding_adjustment; /* set in timeofday_set, cleared in timeofday_onesec */
    i32 outstanding_corr;       /* value to be subtracted from hw time to get PTP time during the adjustment period */
    BOOL awaiting_adjustment; /* set when a clock onetime adjustment has been set, cleared after one sec */
    u32  clk_set_trunc;         /* In order to make the clock counter wrap at a 1 sec, the time is truncated to a multiplum of this value, which is set in tie initialization function, depending on the internal PTP clock rate */
} vtss_ts_conf_t;

typedef struct {
    vtss_timeinterval_t ingress_latency;
    vtss_timeinterval_t p2p_delay;
    vtss_timeinterval_t egress_latency;
    vtss_timeinterval_t delay_asymmetry;
    vtss_ts_operation_mode_t mode;
    i32 default_igr_latency;    /* default ingress latency in ns, for automatic compensation */
    i32 default_egr_latency;    /* default egress latency in ns, for automatic compensation */
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
    vtss_mac_t smac; /* PTP source mac address in */
#endif //defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)

} vtss_ts_port_conf_t;

/* Serval Luton 26 and Jaguar timestamp table structure */
typedef struct {
    u64 reserved_mask;                      /* port mask indicating which ports this tx idx is reserved for */
    u64 valid_mask;                         /* indication pr. port if there is a valid timestamp in the table  */
    u32 age;                                /* ageing counter */
    u64 tx_tc [VTSS_PORT_ARRAY_SIZE];       /* actual transmit time counter for the [idx][port] */
    u32 tx_id [VTSS_PORT_ARRAY_SIZE];       /* actual transmit time stamp id read from HW [idx][port] */
    u32 tx_sq [VTSS_PORT_ARRAY_SIZE];       /* actual transmit sequence number read from HW [idx][port] (Serval)*/
    u32 rx_tc;                              /* actual receive time counter for the [id] (Luton26) */
    BOOL rx_tc_valid;                       /* actual receive time counter is valid for the [id] (Luton26) */
    void * context [VTSS_PORT_ARRAY_SIZE];  /* context aligned to the  [idx,port] */
    void (*cb  [VTSS_PORT_ARRAY_SIZE]) (void *context, u32 port_no, vtss_ts_timestamp_t *ts); /* timestamp callback functions */
} vtss_ts_timestamp_status_t;

#if defined (VTSS_ARCH_OCELOT)
/* Serval OAM timestamp table structure
 * When an OAM timestamp is registered in HW, it is saved in this table
 * For each VOE instance there is place for up to VTSS_SERVAL_MAX_OAM_ENTRIES timestamps, the sequence number is used
 * to distinguish the timestamps,
 * A ringbuffer mechanism is used to fill entries into the buffer.
 * If the buffer runs over, the oldest timestamps are thrown away.
 *
 */
typedef struct {
    u32 tc;       /* actual time counter read from HW */
    u32 id;       /* actual time stamp id (VOE index) read from HW*/
    u32 sq;       /* actual sequence number corresponding to the timestamp */
    u32 port;     /* actual port number corresponding to the timestamp */
    BOOL valid;   /* true indicates that the timestamp is valid */
} vtss_oam_timestamp_entry_t;

#define VTSS_SERVAL_MAX_OAM_ENTRIES 10

typedef struct {
    vtss_oam_timestamp_entry_t entry [VTSS_SERVAL_MAX_OAM_ENTRIES];
    i32 last;
} vtss_oam_timestamp_status_t;
#endif /* VTSS_ARCH_OCELOT */

typedef struct {
    /* CIL function pointers */
    vtss_rc (* timeofday_get)(struct vtss_state_s *vtss_state,
                              vtss_timestamp_t    *ts,
                              u64                 *tc);
    vtss_rc (* timeofday_raw)(struct vtss_state_s *vtss_state,
                              vtss_timestamp_t    *ts,
                              u64                 *tc);
    vtss_rc (* timeofday_next_pps_get)(struct vtss_state_s *vtss_state,
                                       vtss_timestamp_t      *ts);
    vtss_rc (* timeofday_prev_pps_get)(struct vtss_state_s *vtss_state,
                                       vtss_timestamp_t      *ts);
    vtss_rc (* timeofday_set)(struct vtss_state_s *vtss_state,
                              const vtss_timestamp_t         *ts);
    vtss_rc (* timeofday_set_delta)(struct vtss_state_s *vtss_state,
                                    const vtss_timestamp_t   *ts,
                                    BOOL                 negative);
    vtss_rc (* timeofday_offset_set)(struct vtss_state_s *vtss_state,
                                     i32                     offset);
    vtss_rc (* domain_timeofday_get)(struct vtss_state_s *vtss_state,
                                     u32                 domain,
                                     vtss_timestamp_t    *ts,
                                     u64                 *tc);
    vtss_rc (* domain_timeofday_next_pps_get)(struct vtss_state_s *vtss_state,
                                       u32                   domain,
                                       vtss_timestamp_t      *ts);
    vtss_rc (* domain_timeofday_set)(struct vtss_state_s *vtss_state,
                              u32                            domain,
                              const vtss_timestamp_t         *ts);
    vtss_rc (* domain_timeofday_set_delta)(struct vtss_state_s *vtss_state,
                                    u32                            domain,
                                    const vtss_timestamp_t   *ts,
                                    BOOL                 negative);
    vtss_rc (* domain_timeofday_offset_set)(struct vtss_state_s *vtss_state,
                                     u32                            domain,
                                     i32                     offset);
    u32     (* ns_cnt_get) (vtss_inst_t inst);
    vtss_rc (* timeofday_one_sec)(struct vtss_state_s *vtss_state);
    vtss_rc (* adjtimer_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* domain_adjtimer_set)(struct vtss_state_s *vtss_state, u32 domain);
    vtss_rc (* freq_offset_get)(struct vtss_state_s *vtss_state, i32 *adj);
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) /* TBD_HENRIKB */
    vtss_rc (* alt_clock_saved_get)(struct vtss_state_s *vtss_state, u64 *saved);
    vtss_rc (* alt_clock_mode_set)(struct vtss_state_s *vtss_state);
    vtss_rc (* timeofday_next_pps_set)(struct vtss_state_s *vtss_state,
                                       const vtss_timestamp_t *ts);
#endif
#if defined(VTSS_ARCH_OCELOT)
    vtss_rc (* external_clock_mode_set)(struct vtss_state_s *vtss_state, int idx);
#else
    vtss_rc (* external_clock_mode_set)(struct vtss_state_s *vtss_state);
#endif
    vtss_rc (* external_clock_saved_get)(struct vtss_state_s *vtss_state, u32 *saved);
    vtss_rc (* ingress_latency_set)(struct vtss_state_s *vtss_state,
                                    vtss_port_no_t    port_no);
    vtss_rc (* p2p_delay_set)(struct vtss_state_s *vtss_state,
                              vtss_port_no_t          port_no);
    vtss_rc (* egress_latency_set)(struct vtss_state_s *vtss_state,
                                   vtss_port_no_t     port_no);
    vtss_rc (* delay_asymmetry_set)(struct vtss_state_s *vtss_state,
                                    vtss_port_no_t     port_no);
    vtss_rc (* operation_mode_set)(struct vtss_state_s *vtss_state,
                                   vtss_port_no_t     port_no);
    vtss_rc (* internal_mode_set) (struct vtss_state_s *vtss_state);
    vtss_rc (* timestamp_get)(struct vtss_state_s *vtss_state);
    vtss_rc (* timestamp_convert)(struct vtss_state_s *vtss_state,
                                  vtss_port_no_t      port_no,
                                  u64                 *ts);
    vtss_rc (* timestamp_id_release)(struct vtss_state_s *vtss_state,
                                     u32              ts_id);
    vtss_rc (* status_change)(struct vtss_state_s *vtss_state,
                              vtss_port_no_t      port_no);
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
    vtss_rc (* autoresp_cfg_set)(struct vtss_state_s *vtss_state,
                                 u8                  instance);
    vtss_rc (* smac_set)(struct vtss_state_s *vtss_state,
                              vtss_port_no_t      port_no);
#endif //defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
    vtss_rc (* external_io_mode_set)(struct vtss_state_s *vtss_state, u32 io);
    vtss_rc (* saved_timeofday_get) (struct vtss_state_s *vtss_state, u32 io,
                                     vtss_timestamp_t    *ts,
                                     u64                 *tc);
    vtss_rc (* output_clock_edge_offset_get) (struct vtss_state_s *vtss_state, u32 io,
                                              u32                 *offset);
#endif
    vtss_rc (* seq_cnt_get) (struct vtss_state_s *vtss_state,
                             u32                 sec_cntr,
                             u16 *const          cnt_val);
#if defined(VTSS_ARCH_OCELOT)
    vtss_rc (* alt_clock_saved_timeofday_get) (struct vtss_state_s *vtss_state,
                                     vtss_timestamp_t               *ts);
#endif
    vtss_rc (* link_up)(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);

    /* Configuration/state */
    vtss_ts_conf_t              conf;
    vtss_ts_internal_mode_t     int_mode;
    vtss_ts_port_conf_t         port_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_ts_timestamp_status_t  status[VTSS_TS_ID_SIZE];
#if defined (VTSS_ARCH_OCELOT) && defined (VTSS_FEATURE_VOP)
    vtss_oam_timestamp_status_t oam_ts_status[VTSS_VOE_ID_SIZE];
#endif /* VTSS_ARCH_OCELOT && VTSS_FEATURE_VOP */
#if defined (VTSS_ARCH_OCELOT)
    BOOL                        add_sub_option;
#endif /* VTSS_ARCH_OCELOT */
#if defined (VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
    vtss_ts_ext_io_mode_t       io_cfg[VTSS_TS_IO_ARRAY_SIZE];
#endif /* VTSS_ARCH_JAGUAR2 */
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
#if defined (VTSS_ARCH_JAGUAR_2)
    vtss_ts_autoresp_dom_cfg_t       auto_resp_cfg[VTSS_TS_DOMAIN_ARRAY_SIZE];
#endif /* VTSS_ARCH_JAGUAR2 */
#if defined(VTSS_ARCH_SPARX5)
    vtss_ts_autoresp_dom_cfg_t       auto_resp_cfg[VTSS_TS_RESP_CTRL_ARRAY_SIZE];
#endif /* VTSS_ARCH_SPARX5 */
#endif /* VTSS_FEATURE_DELAY_REQ_AUTO_RESP */
} vtss_ts_state_t;

// internal function used in other part of the API
vtss_rc vtss_timestampAdd(vtss_timestamp_t *ts, const vtss_timestamp_t *ts_add);
vtss_rc vtss_timestampSub(vtss_timestamp_t *ts, const vtss_timestamp_t *ts_sub);
vtss_rc vtss_timestampAddNano(vtss_timestamp_t *ts, u64 nano);
vtss_rc vtss_timestampSubNano(vtss_timestamp_t *ts, u64 nano);
vtss_rc vtss_timestampAddSec(vtss_timestamp_t *ts);
vtss_rc vtss_timestampSubSec(vtss_timestamp_t *ts);
BOOL    vtss_timestampLarger(const vtss_timestamp_t *ts1, const vtss_timestamp_t *ts2);

vtss_rc _vtss_rx_timestamp_id_release(const vtss_inst_t              inst,
                                     const vtss_ts_id_t             *const ts_id);

vtss_rc vtss_ts_inst_create(struct vtss_state_s *vtss_state);

#if VTSS_OPT_DEBUG_PRINT
void vtss_ts_debug_print(struct vtss_state_s *vtss_state,
                         const vtss_debug_printf_t pr,
                         const vtss_debug_info_t   *const info);
#endif

#endif  /* VTSS_FEATURE_TIMESTAMP */

#endif /* _VTSS_TS_STATE_H_ */
