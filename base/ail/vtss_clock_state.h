// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_CLOCK_STATE_H_
#define _VTSS_CLOCK_STATE_H_

#if defined(VTSS_FEATURE_CLOCK)

#define INPUT_CNT  4 /* Note: The es6514 has only two SerDes macros but four OMEGA channels */
#define OUTPUT_CNT 4 /* Note: The es6514 has only two SerDes macros but four OMEGA channels */
#define DPLL_CNT   2

typedef struct {
    /* CIL function pointers */
    vtss_rc (*rd)(struct vtss_state_s *vtss_state, const u32 addr, u32 *const value);
    vtss_rc (*wr)(struct vtss_state_s *vtss_state, const u32 addr, const u32 value);
    vtss_rc (*wrm)(struct vtss_state_s *vtss_state, const u32 addr, const u32 value, const u32 mask);

    vtss_rc (*global_enable_set)(struct vtss_state_s             *vtss_state,
                                 const vtss_clock_global_enable_t ena);
    vtss_rc (*global_enable_get)(struct vtss_state_s *vtss_state, vtss_clock_global_enable_t *ena);
    vtss_rc (*global_sw_reset)(struct vtss_state_s *vtss_state);
    vtss_rc (*clock_shutdown)(struct vtss_state_s *vtss_state);
    vtss_rc (*selection_mode_set)(struct vtss_state_s                     *vtss_state,
                                  const vtss_clock_dpll_inst_t             dpll,
                                  const vtss_clock_selection_conf_t *const conf);
    vtss_rc (*selection_mode_get)(struct vtss_state_s               *vtss_state,
                                  const vtss_clock_dpll_inst_t       dpll,
                                  vtss_clock_selection_conf_t *const conf);
    vtss_rc (*operation_conf_set)(struct vtss_state_s                *vtss_state,
                                  const vtss_clock_dpll_inst_t        dpll,
                                  const vtss_clock_dpll_conf_t *const conf);
    vtss_rc (*operation_conf_get)(struct vtss_state_s          *vtss_state,
                                  const vtss_clock_dpll_inst_t  dpll,
                                  vtss_clock_dpll_conf_t *const conf);
    vtss_rc (*ho_stack_conf_set)(struct vtss_state_s                    *vtss_state,
                                 const vtss_clock_dpll_inst_t            dpll,
                                 const vtss_clock_ho_stack_conf_t *const conf);
    vtss_rc (*ho_stack_conf_get)(struct vtss_state_s              *vtss_state,
                                 const vtss_clock_dpll_inst_t      dpll,
                                 vtss_clock_ho_stack_conf_t *const conf);
    vtss_rc (*ho_stack_content_get)(struct vtss_state_s                 *vtss_state,
                                    const vtss_clock_dpll_inst_t         dpll,
                                    vtss_clock_ho_stack_content_t *const conf);
    vtss_rc (*dco_frequency_offset_set)(struct vtss_state_s         *vtss_state,
                                        const vtss_clock_dpll_inst_t dpll,
                                        const i64                    offset);
    vtss_rc (*dco_frequency_offset_get)(struct vtss_state_s         *vtss_state,
                                        const vtss_clock_dpll_inst_t dpll,
                                        i64 *const                   offset);
    vtss_rc (*output_filter_bw_set)(struct vtss_state_s *vtss_state,
                                    const u8             clock_output,
                                    const u32            bw_100uhz);
    vtss_rc (*output_filter_bw_get)(struct vtss_state_s *vtss_state,
                                    const u8             clock_output,
                                    u32                 *bw_100uhz);
    vtss_rc (*output_filter_lock_fast_set)(struct vtss_state_s *vtss_state, const u8 clock_output);
    vtss_rc (*output_filter_lock_fast_get)(struct vtss_state_s *vtss_state,
                                           const u8             clock_output,
                                           BOOL                *lock_completed);
    vtss_rc (*output_psl_conf_set)(struct vtss_state_s               *vtss_state,
                                   const u8                           clock_output,
                                   const vtss_clock_psl_conf_t *const conf);
    vtss_rc (*output_psl_conf_get)(struct vtss_state_s         *vtss_state,
                                   const u8                     clock_output,
                                   vtss_clock_psl_conf_t *const conf);
    vtss_rc (*adj_frequency_set)(struct vtss_state_s *vtss_state,
                                 const u8             clock_output,
                                 const i64            adj);
    vtss_rc (*adj_frequency_get)(struct vtss_state_s *vtss_state,
                                 const u8             clock_output,
                                 i64 *const           adj);
    vtss_rc (*adj_phase_set)(struct vtss_state_s *vtss_state, const u8 clock_output, const i32 adj);
    vtss_rc (*adj_phase_get)(struct vtss_state_s *vtss_state, BOOL *const adj_ongoing);
    vtss_rc (*priority_set)(struct vtss_state_s                        *vtss_state,
                            const vtss_clock_dpll_inst_t                dpll,
                            const u8                                    clock_input,
                            const vtss_clock_priority_selector_t *const conf);
    vtss_rc (*priority_get)(struct vtss_state_s                  *vtss_state,
                            const vtss_clock_dpll_inst_t          dpll,
                            const u8                              clock_input,
                            vtss_clock_priority_selector_t *const conf);
    vtss_rc (*input_frequency_set)(struct vtss_state_s *vtss_state,
                                   const u8             clock_input,
                                   const u32            freq_khz,
                                   const BOOL           use_internal_clock_src);
    vtss_rc (*input_frequency_get)(struct vtss_state_s *vtss_state,
                                   const u8             clock_input,
                                   u32 *const           freq_khz,
                                   BOOL *const          use_internal_clock_src);
    vtss_rc (*input_frequency_ratio_set)(struct vtss_state_s            *vtss_state,
                                         const u8                        clock_input,
                                         const u32                       freq_khz,
                                         const vtss_clock_ratio_t *const ratio,
                                         const BOOL                      use_internal_clock_src);
    vtss_rc (*input_frequency_ratio_get)(struct vtss_state_s      *vtss_state,
                                         const u8                  clock_input,
                                         u32 *const                freq_khz,
                                         vtss_clock_ratio_t *const ratio,
                                         BOOL *const               use_internal_clock_src);
    vtss_rc (*output_frequency_set)(struct vtss_state_s *vtss_state,
                                    const u8             clock_output,
                                    const u32            freq_khz,
                                    const u32            par_freq_khz);
    vtss_rc (*output_frequency_get)(struct vtss_state_s *vtss_state,
                                    const u8             clock_output,
                                    u32 *const           freq_khz,
                                    u32 *const           par_freq_khz);
    vtss_rc (*output_frequency_ratio_set)(struct vtss_state_s            *vtss_state,
                                          const u8                        clock_output,
                                          const u32                       freq_khz,
                                          const u32                       par_freq_khz,
                                          const vtss_clock_ratio_t *const ratio);
    vtss_rc (*output_frequency_ratio_get)(struct vtss_state_s      *vtss_state,
                                          const u8                  clock_output,
                                          u32 *const                freq_khz,
                                          u32 *const                par_freq_khz,
                                          vtss_clock_ratio_t *const ratio);
    vtss_rc (*output_level_set)(struct vtss_state_s *vtss_state,
                                const u8             clock_output,
                                const u16            level_mv);
    vtss_rc (*output_level_get)(struct vtss_state_s *vtss_state,
                                const u8             clock_output,
                                u16 *const           level_mv);
    vtss_rc (*output_selector_set)(struct vtss_state_s                     *vtss_state,
                                   const u8                                 clock_output,
                                   const vtss_clock_input_selector_t *const input);
    vtss_rc (*output_selector_get)(struct vtss_state_s               *vtss_state,
                                   const u8                           clock_output,
                                   vtss_clock_input_selector_t *const input);
    vtss_rc (*input_alarm_conf_set)(struct vtss_state_s                 *vtss_state,
                                    const u8                             clock_input,
                                    const vtss_clock_input_conf_t *const conf);
    vtss_rc (*input_alarm_conf_get)(struct vtss_state_s           *vtss_state,
                                    const u8                       clock_input,
                                    vtss_clock_input_conf_t *const conf);
    vtss_rc (*input_cfm_conf_set)(struct vtss_state_s               *vtss_state,
                                  const u8                           clock_input,
                                  const vtss_clock_cfm_conf_t *const conf);
    vtss_rc (*input_cfm_conf_get)(struct vtss_state_s         *vtss_state,
                                  const u8                     clock_input,
                                  vtss_clock_cfm_conf_t *const conf);
    vtss_rc (*input_pfm_conf_set)(struct vtss_state_s               *vtss_state,
                                  const u8                           clock_input,
                                  const vtss_clock_pfm_conf_t *const conf);
    vtss_rc (*input_pfm_conf_get)(struct vtss_state_s         *vtss_state,
                                  const u8                     clock_input,
                                  vtss_clock_pfm_conf_t *const conf);
    vtss_rc (*input_gst_conf_set)(struct vtss_state_s               *vtss_state,
                                  const u8                           clock_input,
                                  const vtss_clock_gst_conf_t *const conf);
    vtss_rc (*input_gst_conf_get)(struct vtss_state_s         *vtss_state,
                                  const u8                     clock_input,
                                  vtss_clock_gst_conf_t *const conf);
    vtss_rc (*selector_state_get)(struct vtss_state_s               *vtss_state,
                                  const vtss_clock_dpll_inst_t       dpll,
                                  vtss_clock_selector_state_t *const selector_state,
                                  u8 *const                          clock_input);
    vtss_rc (*dpll_state_get)(struct vtss_state_s           *vtss_state,
                              const vtss_clock_dpll_inst_t   dpll,
                              vtss_clock_dpll_state_t *const pll_state);
    vtss_rc (*ho_stack_frequency_offset_get)(struct vtss_state_s         *vtss_state,
                                             const vtss_clock_dpll_inst_t dpll,
                                             i64 *const                   offset);
    vtss_rc (*input_state_get)(struct vtss_state_s            *vtss_state,
                               const u8                        clock_input,
                               vtss_clock_input_state_t *const input_state);
    vtss_rc (*input_event_poll)(struct vtss_state_s                 *vtss_state,
                                const u8                             clock_input,
                                vtss_clock_input_event_type_t *const ev_mask);
    vtss_rc (*input_event_enable)(struct vtss_state_s                *vtss_state,
                                  const u8                            clock_input,
                                  const vtss_clock_input_event_type_t ev_mask,
                                  const BOOL                          enable);
    vtss_rc (*dpll_event_poll)(struct vtss_state_s                *vtss_state,
                               const vtss_clock_dpll_inst_t        dpll,
                               vtss_clock_dpll_event_type_t *const ev_mask);
    vtss_rc (*dpll_event_enable)(struct vtss_state_s               *vtss_state,
                                 const vtss_clock_dpll_inst_t       dpll,
                                 const vtss_clock_dpll_event_type_t ev_mask,
                                 const BOOL                         enable);

    /* State variables */
    BOOL                           init_done;
    vtss_clock_global_enable_t     global_enable;
    vtss_clock_selection_conf_t    selection_conf[DPLL_CNT];
    BOOL                           emulated_ho_state[DPLL_CNT];
    i64                            dco_frequency_offset[DPLL_CNT];
    i64                            dco_ho_offset[DPLL_CNT];
    u32                            input_frequency[INPUT_CNT];
    u32                            input_sample_freq_khz[INPUT_CNT];
    vtss_clock_ratio_t             input_frequency_ratio[INPUT_CNT];
    BOOL                           use_internal_clock_src[INPUT_CNT];
    u32                            output_frequency[OUTPUT_CNT];
    u32                            par_output_frequency[OUTPUT_CNT];
    vtss_clock_ratio_t             output_frequency_ratio[OUTPUT_CNT];
    vtss_clock_psl_conf_t          psl_conf[OUTPUT_CNT];
    u16                            output_level[OUTPUT_CNT];
    i64                            adj_frequency[OUTPUT_CNT];
    vtss_clock_dpll_conf_t         dpll_conf[DPLL_CNT];
    vtss_clock_ho_stack_conf_t     ho_stack_conf[DPLL_CNT];
    vtss_clock_priority_selector_t priority_selector[DPLL_CNT][INPUT_CNT];
    vtss_clock_input_selector_t    input_selector[OUTPUT_CNT];
    vtss_clock_input_conf_t        input_conf[INPUT_CNT];
    vtss_clock_cfm_conf_t          cfm_conf[INPUT_CNT];
    vtss_clock_pfm_conf_t          pfm_conf[INPUT_CNT];
    vtss_clock_gst_conf_t          gst_conf[INPUT_CNT];
    u32                            output_filter_bw[OUTPUT_CNT];

    BOOL serdes_rx_en[INPUT_CNT];
    BOOL serdes_tx_en[OUTPUT_CNT];

    /* Fixed Chip parameters */
    /* Number of DPLLs i.e. controllers in omega*/
    u8 dpll_cnt;
    /* Number of clock inputs / sources */
    u8 clock_input_cnt;
    /* Number of clock outputs / generated clocks */
    u8 clock_output_cnt;

    /* Max frequency offset in ppb for phase sift */
    u32 phase_shift_max_freq_offset;

    /* Semiconstant paramters */
    /* Paramters where validation my find better values or they might even get
     * configuration options */
    /* Filter parameter for Integ2 in receiver */
    u8 f2df_integ2_fsel;

} vtss_clock_state_t;

#endif /* VTSS_FEATURE_CLOCK */
#endif /* _VTSS_CLOCK_STATE_H_ */
