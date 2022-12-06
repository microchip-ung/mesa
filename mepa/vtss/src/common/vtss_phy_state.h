// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_PHY_STATE_H_
#define _VTSS_PHY_STATE_H_

#include <stdio.h>
#include <string.h>

// TBD: OPSYS
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <mepa_driver.h>

#if __INTPTR_MAX__ == __INT32_MAX__
#if !defined(PRIu64)
#define PRIu64 "llu"           /**< Fallback un-signed 64-bit formatting string */
#endif
#if !defined(PRIi64)
#define PRIi64 "lli"           /**< Fallback signed 64-bit formatting string */
#endif
#if !defined(PRIx64)
#define PRIx64 "llx"           /**< Fallback hex 64-bit formatting string */
#endif
#elif __INTPTR_MAX__ == __INT64_MAX__
#if !defined(PRIu64)
#define PRIu64 "lu"           /**< Fallback un-signed 64-bit formatting string */
#endif
#if !defined(PRIi64)
#define PRIi64 "li"           /**< Fallback signed 64-bit formatting string */
#endif
#if !defined(PRIx64)
#define PRIx64 "lx"           /**< Fallback hex 64-bit formatting string */
#endif
#else
#error "Environment not 32 or 64-bit."
#endif

#if defined(VTSS_CHIP_CU_PHY)
#include "../phy_1g/vtss_phy.h"
#endif

#ifdef VTSS_CHIP_10G_PHY
#include "../phy_10g/vtss_phy_10g.h"
#endif

#ifdef VTSS_FEATURE_MACSEC
#include "../macsec/vtss_macsec.h"
#endif

typedef struct {
    u16 mmd;
    BOOL is32;
    u32 addr;
} ioreg_blk;

typedef struct {
#if defined(VTSS_CHIP_10G_PHY)
    vtss_rc (* phy_10g_mode_conf_set)(struct vtss_state_s *vtss_state,
                                      vtss_port_no_t port_no);

    vtss_rc (* phy_10g_csr_read)(struct vtss_state_s         *vtss_state,
                                 const vtss_port_no_t        port_no,
                                 const u32                   dev,
                                 const u32                   addr,
                                 u32                         *const value);

    vtss_rc (* phy_10g_csr_write)(struct vtss_state_s        *vtss_state,
                                  const vtss_port_no_t       port_no,
                                  const u32                  dev,
                                  const u32                  addr,
                                  const u32                  value);
    vtss_rc (* phy_10g_rxckout_set)   (struct vtss_state_s *vtss_state,
                                       vtss_port_no_t port_no);
    vtss_rc (* phy_10g_txckout_set)   (struct vtss_state_s *vtss_state,
                                       vtss_port_no_t port_no);
    vtss_rc (* phy_10g_srefclk_set)   (struct vtss_state_s *vtss_state,
                                          vtss_port_no_t port_no);
    vtss_rc (* phy_10g_loopback_set) (struct vtss_state_s *vtss_state,
                                      vtss_port_no_t port_no);
    vtss_rc (* phy_10g_power_set) (struct vtss_state_s *vtss_state,
                                      vtss_port_no_t port_no);
    vtss_rc (* phy_10g_base_kr_conf_set) (struct vtss_state_s *vtss_state,
                                   vtss_port_no_t port_no);
    vtss_rc (* phy_10g_pkt_gen_conf)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t        port_no,
                                            vtss_phy_10g_pkt_gen_conf_t *const conf);
    vtss_rc (* phy_10g_pkt_mon_conf)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t        port_no,
                                            vtss_phy_10g_pkt_mon_conf_t *const conf);
    vtss_rc (* phy_10g_timestamp_rd) ( struct vtss_state_s *vtss_state,
            vtss_port_no_t port_no,
            vtss_phy_10g_timestamp_val_t *conf_ts);

    vtss_rc (* venice_cross_connect) (struct vtss_state_s *vtss_state,
                                      const vtss_port_no_t port_no,
                                      const u16 value);
#ifdef VTSS_FEATURE_10GBASE_KR
    vtss_rc (* venice_phy_10g_base_kr_train_aneg_set) (struct vtss_state_s *vtss_state,
            vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_base_kr_train_aneg_set) (struct vtss_state_s *vtss_state,
            vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_base_host_kr_train_aneg_set) (struct vtss_state_s *vtss_state,
            vtss_port_no_t port_no);
    vtss_rc (*venice_phy_10g_kr_status_get)(struct vtss_state_s *vtss_state,const vtss_port_no_t port_no,
                                     vtss_phy_10g_base_kr_status_t *const line_kr);
    vtss_rc (*malibu_phy_10g_kr_status_get)(struct vtss_state_s *vtss_state,const vtss_port_no_t port_no,
                                    BOOL host_kr, vtss_phy_10g_base_kr_status_t *const line_kr);
#endif // end VTSS_FEATURE_10GBASE_KR
    vtss_rc (* phy_10g_clause_37_status_get) (struct vtss_state_s *vtss_state,
                                              vtss_port_no_t port_no,
                                              vtss_phy_10g_clause_37_cmn_status_t *const status);

    vtss_rc (* phy_10g_clause_37_control_set) (struct vtss_state_s *vtss_state,
                                               const vtss_port_no_t port_no);

    vtss_rc (* phy_10g_link_loss_workaround) (struct vtss_state_s *vtss_state,
            const vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_mode_conf_set)(struct vtss_state_s *vtss_state,
                                          vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_gpio_mode_set)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t        port_no,
                                            const vtss_gpio_10g_no_t    gpio_no);
    vtss_rc (* malibu_phy_10g_vscope_conf_set)(struct vtss_state_s *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const vtss_phy_10g_vscope_conf_t *const conf);
    vtss_rc (* phy_10g_vscope_conf_set)(struct vtss_state_s *vtss_state,
                                                const vtss_port_no_t port_no,

                                                const vtss_phy_10g_vscope_conf_t *const conf);
    vtss_rc (* malibu_phy_10g_vscope_scan_status_get)(struct vtss_state_s *vtss_state,
                                                    const vtss_port_no_t port_no,
                                                    vtss_phy_10g_vscope_scan_status_t  *const conf);

    vtss_rc (* phy_10g_vscope_scan_status_get)(struct vtss_state_s *vtss_state,
                                                    const vtss_port_no_t port_no,
                                                    vtss_phy_10g_vscope_scan_status_t  *const conf);

    vtss_rc (* venice_phy_10g_apc_restart)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const BOOL is_host);

    vtss_rc (* malibu_phy_10g_ib_conf_set)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const vtss_phy_10g_ib_conf_t *const ib_conf,
                                           const BOOL is_host);
    vtss_rc (* malibu_phy_10g_ib_status_get)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           vtss_phy_10g_ib_status_t *const ib_status);
    vtss_rc (* malibu_phy_10g_ob_status_get)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           vtss_phy_10g_ob_status_t *const ob_status);
    vtss_rc (* malibu_phy_10g_apc_conf_set)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const vtss_phy_10g_apc_conf_t *const apc_conf,
                                           const BOOL is_host);
    vtss_rc (* malibu_phy_10g_apc_status_get)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const BOOL is_host,
                                           vtss_phy_10g_apc_status_t *const apc_status);
    vtss_rc (* malibu_phy_10g_apc_restart)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const BOOL is_host);
    vtss_rc (* malibu_phy_10g_jitter_conf_set)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const BOOL is_host,
                                           const vtss_phy_10g_jitter_conf_t *const jitter_conf);
    vtss_rc (* malibu_phy_10g_jitter_status_get)(struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const BOOL is_host,
                                           vtss_phy_10g_jitter_conf_t *const jitter_status);
    vtss_rc (* malibu_phy_10g_prbs_gen_conf)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t port_no,
                                            const vtss_phy_10g_direction_t direction,
                                            const vtss_phy_10g_prbs_generator_conf_t *const conf);
    vtss_rc (* malibu_phy_10g_prbs_mon_conf)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t port_no,
                                            const vtss_phy_10g_direction_t direction,
                                            const vtss_phy_10g_prbs_monitor_conf_t *const conf);
    vtss_rc (* malibu_phy_10g_prbs_mon_status_get)(struct vtss_state_s *vtss_state,
                                         const vtss_port_no_t port_no,
                                         const vtss_phy_10g_direction_t direction,
                                         const BOOL  reset,
                                         vtss_phy_10g_prbs_monitor_status_t *const mon_status);
    vtss_rc (* phy_10g_prbs_gen_conf)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t port_no,
                                            const vtss_phy_10g_prbs_generator_conf_t *const conf);
    vtss_rc (* phy_10g_prbs_mon_conf)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t port_no,
                                            const vtss_phy_10g_prbs_monitor_conf_t *const conf);
    vtss_rc (*phy_10g_prbs_mon_status_get) (struct vtss_state_s *vtss_state,
                                         const vtss_port_no_t port_no,
                                         const BOOL  reset,
                                         vtss_phy_10g_prbs_monitor_status_t *const mon_status);

    vtss_rc (* malibu_phy_10g_pkt_gen_conf)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t        port_no,
                                            vtss_phy_10g_pkt_gen_conf_t *const conf);
    vtss_rc (* malibu_phy_10g_pkt_mon_conf)(struct vtss_state_s *vtss_state,
                                            const vtss_port_no_t        port_no,
                                            vtss_phy_10g_pkt_mon_conf_t *const conf);
    vtss_rc (*malibu_phy_10g_clause_37_status_get)(struct vtss_state_s   *vtss_state,
                                                   const vtss_port_no_t    port_no,
                                                   vtss_phy_10g_clause_37_cmn_status_t *const status);
    vtss_rc (*malibu_phy_10g_serdes_status_get)(struct vtss_state_s   *vtss_state,
                                                   const vtss_port_no_t    port_no,
                                                   vtss_phy_10g_serdes_status_t *const status);
    vtss_rc (*malibu_phy_10g_clause_37_control_set) (struct vtss_state_s     *vtss_state,
                                                     const vtss_port_no_t     port_no);
    vtss_rc (* malibu_phy_10g_auto_failover_set)(struct vtss_state_s *vtss_state,
                                            const vtss_phy_10g_auto_failover_conf_t    *mode);
    vtss_rc (* malibu_phy_10g_gpio_read) (struct vtss_state_s *vtss_state,
                                          const vtss_port_no_t             port_no,
                                          const vtss_gpio_10g_no_t    gpio_no,
                                          BOOL                  *const value);
    vtss_rc (* malibu_phy_10g_gpio_write) (struct vtss_state_s *vtss_state,
                                           const vtss_port_no_t             port_no,
                                           const vtss_gpio_10g_no_t    gpio_no,
                                           BOOL                  const value);
   vtss_rc (* malibu_phy_10g_loopback_set) (struct vtss_state_s   *vtss_state,
                                            const vtss_port_no_t   port_no);
   vtss_rc (* malibu_phy_10g_csr_read) (struct vtss_state_s       *vtss_state,
                                            const vtss_port_no_t        port_no,
                                            const u32                   dev,
                                            const u32                   addr,
                                            u32                         *const value);
   vtss_rc (* malibu_phy_10g_csr_write) (struct vtss_state_s       *vtss_state,
                                            const vtss_port_no_t        port_no,
                                            const u32                   dev,
                                            const u32                   addr,
                                            u32                         value);
   vtss_rc (* malibu_phy_10g_event_enable) (struct vtss_state_s  *vtss_state,
                                             const vtss_port_no_t port_no);
   vtss_rc (* malibu_phy_10g_power_set) (struct vtss_state_s *vtss_state,
                                       vtss_port_no_t port_no);
   vtss_rc (* malibu_phy_10g_base_kr_conf_set) (struct vtss_state_s *vtss_state,
                                    vtss_port_no_t port_no);
   vtss_rc (* malibu_phy_10g_base_kr_host_conf_set) (struct vtss_state_s *vtss_state,
                                    vtss_port_no_t port_no);
   vtss_rc (* malibu_phy_10g_event_poll) (struct vtss_state_s           *vtss_state,
                                           const vtss_port_no_t         port_no,
                                           vtss_phy_10g_event_t         *const events);
   vtss_rc (* malibu_phy_10g_extended_event_poll) (struct vtss_state_s      *vtss_state,
                                           const vtss_port_no_t             port_no,
                                           vtss_phy_10g_extnd_event_t       *const ex_events);
   vtss_rc (* malibu_phy_10g_host_recvrd_clk_set) (struct vtss_state_s *vtss_state,
                                       vtss_port_no_t port_no);
   vtss_rc (* malibu_phy_10g_pcs_status_get) (struct vtss_state_s *vtss_state,
                                       vtss_port_no_t port_no,
                                       vtss_phy_10g_extnd_event_t       *const ex_events);
   vtss_rc (* malibu_phy_10g_line_recvrd_clk_set) (struct vtss_state_s *vtss_state,
                                       vtss_port_no_t port_no);
   vtss_rc (* malibu_phy_10g_host_clk_set) (struct vtss_state_s *vtss_state,
                                       vtss_port_no_t port_no);
   vtss_rc (* malibu_phy_10g_line_clk_set) (struct vtss_state_s *vtss_state,
                                       vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_srefclk_set)   (struct vtss_state_s *vtss_state,
                                          vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_ckout_set)   (struct vtss_state_s *vtss_state,
                                          vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_sckout_set)   (struct vtss_state_s *vtss_state,
                                          vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_timestamp_rd) ( struct vtss_state_s *vtss_state,
                                          vtss_port_no_t port_no,
                                          vtss_phy_10g_timestamp_val_t *conf_ts);
    vtss_rc (* malibu_phy_10g_lane_sync_set)   (struct vtss_state_s *vtss_state,
                                          vtss_port_no_t port_no);
    vtss_rc (* vtss_phy_10g_debug_reg_dump) (struct vtss_state_s *vtss_state,
                                             const vtss_debug_printf_t pr,
                                             BOOL clear, vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_debug_reg_dump) (struct vtss_state_s *vtss_state,
                                             const vtss_debug_printf_t pr,
                                             BOOL clear, vtss_port_no_t port_no);

    vtss_rc (* phy_10g_lane_sync_set)   (struct vtss_state_s *vtss_state,
                                          vtss_port_no_t port_no);
    vtss_rc (* phy_10g_sgmii_mode_set) ( struct vtss_state_s *vtss_state,
                                    vtss_port_no_t port_no);
    vtss_rc (* malibu_phy_10g_sgmii_mode_set) ( struct vtss_state_s *vtss_state,
                                                vtss_port_no_t port_no);
#endif /* VTSS_CHIP_10G_PHY */
#if defined(VTSS_FEATURE_WIS)
    vtss_rc (* ewis_events_conf_set)(struct vtss_state_s *vtss_state,
                                     vtss_port_no_t port_no, const BOOL enable, const vtss_ewis_event_t ev_mask);
    vtss_rc (* ewis_events_poll)(struct vtss_state_s *vtss_state,
                                 vtss_port_no_t port_no,vtss_ewis_event_t *const status );
    vtss_rc (* ewis_events_poll_without_mask)(struct vtss_state_s *vtss_state,
                                              vtss_port_no_t port_no,
                                              vtss_ewis_event_t *const status );
    vtss_rc (* ewis_events_force)(struct vtss_state_s *vtss_state,
                                  vtss_port_no_t port_no, const BOOL enable, const vtss_ewis_event_t events);
    vtss_rc (* ewis_static_conf_set)(struct vtss_state_s *vtss_state,
                                     vtss_port_no_t port_no);
    vtss_rc (* ewis_force_conf_set)(struct vtss_state_s *vtss_state,
                                    vtss_port_no_t port_no);
    vtss_rc (* ewis_tx_oh_set)(struct vtss_state_s *vtss_state,
                               vtss_port_no_t port_no);
    vtss_rc (* ewis_tx_oh_passthru_set)(struct vtss_state_s *vtss_state,
                                        vtss_port_no_t port_no);
    vtss_rc (* ewis_exp_sl_set)(struct vtss_state_s *vtss_state,
                                vtss_port_no_t port_no);
    vtss_rc (* ewis_mode_conf_set)(struct vtss_state_s *vtss_state,
                                   vtss_port_no_t port_no);
    vtss_rc (* ewis_reset)(struct vtss_state_s *vtss_state,
                           vtss_port_no_t port_no);
    vtss_rc (* ewis_cons_action_set)(struct vtss_state_s *vtss_state,
                                     vtss_port_no_t port_no);
    vtss_rc (* ewis_section_txti_set)(struct vtss_state_s *vtss_state,
                                      vtss_port_no_t port_no);
    vtss_rc (* ewis_path_txti_set)(struct vtss_state_s *vtss_state,
                                   vtss_port_no_t port_no);
    vtss_rc (* ewis_test_mode_set)(struct vtss_state_s *vtss_state,
                                   vtss_port_no_t port_no);
    vtss_rc (* ewis_prbs31_err_inj_set)(struct vtss_state_s *vtss_state,
                                        vtss_port_no_t port_no, const vtss_ewis_prbs31_err_inj_t *const inj);
    vtss_rc (* ewis_test_status_get)(struct vtss_state_s *vtss_state,
                                     vtss_port_no_t port_no, vtss_ewis_test_status_t *const test_status);
    vtss_rc (* ewis_defects_get)(struct vtss_state_s *vtss_state,
                                 vtss_port_no_t port_no, vtss_ewis_defects_t *const def);
    vtss_rc (* ewis_status_get)(struct vtss_state_s *vtss_state,
                                vtss_port_no_t port_no, vtss_ewis_status_t *const status);
    vtss_rc (* ewis_section_acti_get)(struct vtss_state_s *vtss_state,
                                      vtss_port_no_t port_no, vtss_ewis_tti_t *const acti);
    vtss_rc (* ewis_path_acti_get)(struct vtss_state_s *vtss_state,
                                   vtss_port_no_t port_no, vtss_ewis_tti_t *const actii);
    vtss_rc (* ewis_perf_get)(struct vtss_state_s *vtss_state,
                              vtss_port_no_t port_no, vtss_ewis_perf_t *const perf);
    vtss_rc (* ewis_counter_get)(struct vtss_state_s *vtss_state,
                                 vtss_port_no_t port_no, vtss_ewis_counter_t *const perf);
    vtss_rc (* ewis_counter_threshold_set)(struct vtss_state_s *vtss_state,
                                           vtss_port_no_t port_no);
    vtss_rc (* ewis_perf_mode_set)(struct vtss_state_s *vtss_state,
                                   vtss_port_no_t port_no);
#endif /* VTSS_FEATURE_WIS */
} vtss_cil_func_t;

#if defined(VTSS_OPT_PHY_TIMESTAMP)
typedef struct {
    BOOL                            eng_used; /* allocated the engine to application */
    vtss_phy_ts_encap_t             encap_type; /* engine encapsulation */
    vtss_phy_ts_engine_flow_match_t flow_match_mode; /* strict/non-strict flow match */
    u8                              flow_st_index; /* start index of flow */
    u8                              flow_end_index; /* end index of flow */
    vtss_phy_ts_engine_flow_conf_t  flow_conf; /* engine flow config */
    vtss_phy_ts_engine_action_t     action_conf; /* engine action */
    u8                              action_flow_map[6]; /* action map to flow */
} vtss_phy_ts_eng_conf_t;

#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0)
typedef struct {
    u16                      phy_type;
    u16                      channel_id;
    BOOL                     enable;
    BOOL                     alt_port_init_done;
    vtss_phy_ts_fifo_mode_t  alt_port_tx_fifo_mode;
} vtss_phy_ts_new_spi_conf_t;
#endif /* defined(VTSS_CHIP_CU_PHY) && defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0) */

typedef struct {
    BOOL                             port_ts_init_done; /* PHY TS init done */
    BOOL                             eng_init_done; /* 1588 TS engine init done */
    BOOL                             port_ena;
    vtss_port_no_t                   base_port; /* base port for multi-channel PHY */
    vtss_port_no_t                   alt_port;
    vtss_phy_ts_clockfreq_t          clk_freq;  /* reference clock frequency */
    vtss_phy_ts_clock_src_t          clk_src;   /* reference clock source */
    vtss_phy_ts_rxtimestamp_pos_t    rx_ts_pos; /* Rx timestamp position */
    vtss_phy_ts_rxtimestamp_len_t    rx_ts_len; /* Rx timestamp length */
    vtss_phy_ts_fifo_mode_t          tx_fifo_mode; /* Tx TSFIFO access mode */
    vtss_phy_ts_fifo_timestamp_len_t tx_ts_len; /* timestamp size in Tx TSFIFO */
    vtss_phy_ts_tc_op_mode_t         tc_op_mode; /* TC operating Mode: Mode A or B*/
    vtss_phy_ts_8487_xaui_sel_t      xaui_sel_8487; /* 8487 XAUI Lane selection */
    vtss_phy_ts_fifo_sig_mask_t      sig_mask;  /* FIFO signature */
    u32                              fifo_age;  /* SW TSFIFO age in milli-sec */
    vtss_timeinterval_t              ingress_latency;
    vtss_timeinterval_t              egress_latency;
    vtss_timeinterval_t              path_delay;
    vtss_timeinterval_t              delay_asym;
    vtss_phy_ts_scaled_ppb_t         rate_adj;  /* clock rate adjustment */
    vtss_phy_ts_eng_conf_t           ingress_eng_conf[4]; /*port ingress engine configuration including encapsulation, comparator configuration and action  */
    vtss_phy_ts_eng_conf_t           egress_eng_conf[4]; /*port egress engine configuration including encapsulation, comparator configuration and action  */
    vtss_phy_ts_event_t              event_mask; /* interrupt mask config */
    u32                              egr_reg_mask;  /* Egress mask register value */
    u32                              ingr_reg_mask; /* Ingress mask register value */
    u32                              ltc_reg_mask;  /* LTC reg mask value */
    BOOL                             event_enable; /* interrupt enable/disable */
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0)
    vtss_phy_ts_new_spi_conf_t       new_spi_conf; /* Config info for New SPI Mode */
#endif /* defined(VTSS_CHIP_CU_PHY) && defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0) */
#if defined (VTSS_SW_OPTION_REMOTE_TS_PHY)
    BOOL                              remote_phy;    /**< TRUE if the phy is remote */
#endif /* VTSS_SW_OPTION_REMOTE_TS_PHY */
#ifdef VTSS_FEATURE_PTP_DELAY_COMP_ENGINE
    vtss_timeinterval_t              ingress_delay_comp;
    vtss_timeinterval_t              egress_delay_comp;
#endif
    BOOL                             is_gen2;
    vtss_phy_ts_alt_clock_mode_t     alt_clock_mode;
    vtss_phy_ts_pps_conf_t           pps_conf;
    vtss_phy_ts_sertod_conf_t        sertod_conf;
    vtss_phy_ltc_freq_synth_t        ltc_freq_synth;
#if defined(VTSS_CHIP_CU_PHY)
    vtss_phy_daisy_chain_conf_t      spi_daisy_chain;
#endif //(VTSS_CHIP_CU_PHY)
    u16                              load_pulse_delay;
    BOOL                             chk_ing_modified;
    BOOL                             auto_clear_ls;
    BOOL                             macsec_ena;
    BOOL                             one_step_txfifo;
    u8                               ip1_nxt_cmp[4]; /* IP1 comparator is available only in blocks 0,1,2,3. */
    u8                               ip2_nxt_cmp[4]; /* IP2 comparator is available only in blocks 0,1,2,3. */
} vtss_phy_ts_port_conf_t;

typedef struct {
    BOOL                   is_spi_paused;
    u16                    spi_prev_status;
    vtss_phy_ts_eng_conf_t eng_conf;
} vtss_phy_ts_state_t;
#endif  /* VTSS_OPT_PHY_TIMESTAMP */

typedef struct vtss_state_s {
    u32                   cookie;
    u32                   port_count;
    BOOL                  restart_updated; /* Restart has been detected */
    BOOL                  warm_start_cur;  /* Current warm start status */
    BOOL                  warm_start_prev; /* Previous warm start status */
    const mepa_callout_t    *callout[VTSS_PORT_ARRAY_SIZE];
    struct mepa_callout_ctx *callout_ctx[VTSS_PORT_ARRAY_SIZE];
#if defined(VTSS_FEATURE_WARM_START)
    vtss_restart_t        restart_cur;     /* Current restart configuration */
    vtss_restart_t        restart_prev;    /* Previous restart configuration */
    vtss_version_t        version_cur;     /* Current version */
    vtss_version_t        version_prev;    /* Previous version */
#endif /* VTSS_FEATURE_WARM_START */
#if defined(VTSS_CHIP_CU_PHY)
    vtss_phy_inst_state_t phy_inst_state;
    vtss_phy_port_state_t phy_state[VTSS_PORT_ARRAY_SIZE];
    vtss_phy_led_mode_select_t led_mode_select; // LED blink mode
#if defined(VTSS_FEATURE_LED_POW_REDUC)
    u8                            led_intensity;
    vtss_phy_enhanced_led_control_t enhanced_led_control;
    BOOL                            phy_led_control_warm_start_port_list[VTSS_PORTS]; /**<List of ports which is used for LED control (Normally only one port). This is needed in order to know which ports that shall be configured during warm start */
#endif
#endif
    BOOL                  sync_calling_private; /* Used by PHY APIs */
    BOOL                  system_reseting;      // Signaling if system is rebooting.
    vtss_phy_init_conf_t  init_conf;
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    vtss_serdes_macro_conf_t serdes; /**< Serdes macro configuration */
#endif
#if defined(VTSS_FEATURE_MACSEC)
    vtss_macsec_internal_conf_t macsec_conf[VTSS_PORT_ARRAY_SIZE];
#endif
#if defined(VTSS_OPT_PHY_TIMESTAMP)
    vtss_phy_ts_port_conf_t  phy_ts_port_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_phy_ts_state_t      phy_ts_state;
    vtss_phy_ts_fifo_read    ts_fifo_cb;
    void                     *cntxt;
#endif  /* VTSS_OPT_PHY_TIMESTAMP */

#if defined(VTSS_FEATURE_WIS)
    vtss_ewis_conf_t              ewis_conf[VTSS_PORT_ARRAY_SIZE];
#endif
    ioreg_blk              io_var;   /* temporary structures used in register read/write in phys */
#if defined(VTSS_CHIP_10G_PHY)
    vtss_port_no_t                phy_10g_api_base_no; /* Support variable for determining base API port no */
    u32                           phy_channel_id;  /* Support counter for determining channel id */
    u32                           phy_chip_no;     /* Support counter for determining chip number */
    vtss_phy_10g_port_state_t     phy_10g_state[VTSS_PORT_ARRAY_SIZE];
    void                          *phy_10g_generic;    /* Generic pointer, Refer to bug#18201 */
#endif
    vtss_cil_func_t               cil;
} vtss_phy_state_t;

// Backward compatibility naming for now
typedef vtss_phy_state_t vtss_state_t;

#define vtss_init_conf_t vtss_phy_init_conf_t


#define VTSS_STATE_COOKIE 0x53727911

#define vtss_inst_check vtss_phy_inst_check
vtss_rc vtss_phy_inst_check(const vtss_inst_t inst, vtss_state_t **vtss_state);


#define vtss_inst_port_no_check vtss_phy_inst_port_no_check
vtss_rc vtss_phy_inst_port_no_check(const vtss_inst_t    inst,
                                    vtss_state_t         **vtss_state,
                                    const vtss_port_no_t port_no);

#define vtss_cmn_restart_update vtss_phy_restart_update
vtss_rc vtss_phy_restart_update(vtss_state_t *vtss_state, u32 value);

#define vtss_cmn_restart_value_get vtss_phy_restart_value_get
u32 vtss_phy_restart_value_get(vtss_state_t *vtss_state);

#define vtss_port_if_txt vtss_phy_port_if_txt
extern const char *vtss_phy_port_if_txt(vtss_port_interface_t if_type);

#define vtss_debug_group_enabled vtss_phy_debug_group_enabled
BOOL vtss_phy_debug_group_enabled(const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t *const info,
                                  const vtss_debug_group_t group);

#if !defined(NULL)
#define NULL ((void *)0)
#endif

extern const char *vtss_phy_func;

/* Call Chip Interface Layer function if it exists */
#define VTSS_FUNC(func, ...) (vtss_state->func == NULL ? VTSS_RC_ERROR : vtss_state->func(vtss_state, ##__VA_ARGS__))

/* Call Chip Interface Layer function if it exists and we are in cold start mode */
#define VTSS_FUNC_COLD(func, ...) (vtss_state->func == NULL ? VTSS_RC_ERROR : vtss_state->warm_start_cur ? VTSS_RC_OK : vtss_state->func(vtss_state, ## __VA_ARGS__))

/* Call function in cold start mode only */
#define VTSS_RC_COLD(expr) (vtss_state->warm_start_cur ? VTSS_RC_OK : (expr))

#define VTSS_RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }

#define VTSS_ENTER(...) { vtss_state_t *_vtss_state; if (vtss_inst_check(inst, &_vtss_state) != VTSS_RC_OK) { return VTSS_RC_ERROR; } else if (_vtss_state->init_conf.lock_enter) { vtss_phy_lock_t _lock; _lock.function = __FUNCTION__; _lock.file = __FILE__; _lock.line = __LINE__; _vtss_state->init_conf.lock_enter(&_lock); } vtss_phy_func = __FUNCTION__; }
#define VTSS_EXIT(...) { vtss_state_t *_vtss_state; vtss_phy_func = NULL; if (vtss_inst_check(inst, &_vtss_state) == VTSS_RC_OK && _vtss_state->init_conf.lock_exit) { vtss_phy_lock_t _lock; _lock.function = __FUNCTION__; _lock.file = __FILE__; _lock.line = __LINE__; _vtss_state->init_conf.lock_exit(&_lock); } }

#define VTSS_BOOL(expr) ((expr) ? 1 : 0)

#define VTSS_ARRSZ(t) (sizeof(t)/sizeof(t[0]))

/* Bit field macros */
#define VTSS_BF_SIZE(n)      ((n+7)/8)
#define VTSS_BF_GET(a, n)    ((a[(n)/8] & (1<<((n)%8))) ? 1 : 0)
#define VTSS_BF_SET(a, n, v) do { if (v) { a[(n)/8] |= (1U<<((n)%8)); } else { a[(n)/8] &= ~(1U<<((n)%8)); }} while (0)
#define VTSS_BF_CLR(a, n)    (memset(a, 0, VTSS_BF_SIZE(n)))

/* ================================================================= *
 *  Trace
 * ================================================================= */

extern vtss_phy_trace_func_t vtss_phy_trace_func;

#if VTSS_OPT_PHY_TRACE

#define VTSS_TRACE_GROUP_PHY    VTSS_PHY_TRACE_GROUP_DEFAULT
#define VTSS_TRACE_GROUP_MACSEC VTSS_PHY_TRACE_GROUP_DEFAULT

#define VTSS_TRACE_LAYER_CIL    VTSS_PHY_TRACE_LAYER_CIL

/* Default trace layer */
#ifndef VTSS_TRACE_LAYER
#define VTSS_TRACE_LAYER VTSS_PHY_TRACE_LAYER_AIL
#endif /* VTSS_TRACE_LAYER */

/* Default trace group */
#ifndef VTSS_TRACE_GROUP
#define VTSS_TRACE_GROUP VTSS_PHY_TRACE_GROUP_DEFAULT
#endif /* VTSS_TRACE_GROUP */

#define VTSS_E(...) VTSS_EG(VTSS_TRACE_GROUP, ##__VA_ARGS__)
#define VTSS_I(...) VTSS_IG(VTSS_TRACE_GROUP, ##__VA_ARGS__)
#define VTSS_D(...) VTSS_DG(VTSS_TRACE_GROUP, ##__VA_ARGS__)
#define VTSS_N(...) VTSS_NG(VTSS_TRACE_GROUP, ##__VA_ARGS__)

/* For files with multiple trace groups: */
#define VTSS_T(_grp, _lvl, ...) { if (vtss_phy_trace_func) vtss_phy_trace_func(_grp, _lvl, __FUNCTION__, __LINE__, __VA_ARGS__); }
#define VTSS_EG(_grp, ...) VTSS_T(_grp, VTSS_PHY_TRACE_LEVEL_ERROR, __VA_ARGS__)
#define VTSS_IG(_grp, ...) VTSS_T(_grp, VTSS_PHY_TRACE_LEVEL_INFO,  __VA_ARGS__)
#define VTSS_DG(_grp, ...) VTSS_T(_grp, VTSS_PHY_TRACE_LEVEL_DEBUG, __VA_ARGS__)
#define VTSS_NG(_grp, ...) VTSS_T(_grp, VTSS_PHY_TRACE_LEVEL_NOISE, __VA_ARGS__)

#else /* VTSS_PHY_OPT_TRACE */

/* No trace */
#define VTSS_E(...)
#define VTSS_I(...)
#define VTSS_D(...)
#define VTSS_N(...)

#define VTSS_EG(_grp, ...)
#define VTSS_IG(_grp, ...)
#define VTSS_DG(_grp, ...)
#define VTSS_NG(_grp, ...)

#endif /* VTSS_PHY_OPT_TRACE */
#endif /* _VTSS_PHY_STATE_H_ */
