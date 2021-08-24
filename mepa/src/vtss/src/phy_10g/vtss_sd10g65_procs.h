// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/*---------------------------------------------------------------------------
 * $HeadURL: svn://svn-de.vitesse.com/svn-de/vtslibs/vts_ute_tcllib/tags/UTE_release_vts_ute_tcllib_20180312_trunk_bjo/api_c/vtss_sd10g65_procs.h $
 *---------------------------------------------------------------------------*/

/* ================================================================= *
 *               Note: This code is provided as part of the
 *                     Universal Tcl Environment (UTE) to provide
 *                     consistent setup functions for
 *       ^             - Verification
 *      / \            - Validation
 *     /   \           - Test Pattern Generation and
 *    /  |  \          - Software
 *   /   !   \         It should not be modified without further inquiry
 *  /_________\        by the respective team.
 *                     Please contact
 *                       Patrick Urban <patrick.urban@microsemi.com> or
 *                       Alexander Koch <alexander.koch@microsemi.com> or
 *                       Mark Venneboerger <mark.venneboerger@microsemi.com>
 *                     Please use Bugzilla for reporting issues or requesting enhancements:
 *                     Bugzilla: Tools->Victoria
 *                     http://projissuetracker/bugzilla/enter_bug.cgi?product=Victoria
 * ================================================================= */

#ifndef _VTSS_SD10G65_PROCS_H_
#define _VTSS_SD10G65_PROCS_H_


#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#endif

/* ================================================================= *
 *  Data structures / types
 * ================================================================= */


/** \brief Vitesse chip development name */
typedef enum {
    VTSS_SD10G65_CHIP_ES65XX,
    VTSS_SD10G65_CHIP_ES6512,
    VTSS_SD10G65_CHIP_ES6514,
    VTSS_SD10G65_CHIP_JAGUAR2,
    VTSS_SD10G65_CHIP_JAGUAR2C,
    VTSS_SD10G65_CHIP_VENICE,
    VTSS_SD10G65_CHIP_VENICE_C,
    VTSS_SD10G65_CHIP_MALIBU,
    VTSS_SD10G65_CHIP_MALIBU_B,
    VTSS_SD10G65_CHIP_SERVALT,
    VTSS_SD10G65_CHIP_ROLEX,
    VTSS_SD10G65_CHIP_LAST
} vtss_chip_name_t;

/** \brief SerDes mode type */
typedef enum {
        VTSS_SD10G65_MODE_10G_LAN,
        VTSS_SD10G65_MODE_10G_ETH,
        VTSS_SD10G65_MODE_10G_WAN,
        VTSS_SD10G65_MODE_WAN,
        VTSS_SD10G65_MODE_OTU2,
        VTSS_SD10G65_MODE_OTU1e,
        VTSS_SD10G65_MODE_OTU2e,
        VTSS_SD10G65_MODE_FX100,
        VTSS_SD10G65_MODE_SGMII,
        VTSS_SD10G65_MODE_1G_LAN,
        VTSS_SD10G65_MODE_NONE
} vtss_f_mode_t;

/** \brief return values of pwr_down function */
typedef struct {
    u8  sbus_tx_cfg__sbus_bias_en[2];
    u8  sbus_rx_cfg__sbus_bias_en[2];
    u8  tx_synth_cfg0__synth_ena[2];
    u8  tx_rcpll_cfg2__pll_ena[2];
    u8  ob_cfg0__en_ob[1];
    u8  rx_synth_cfg0__synth_ena[2];
    u8  rx_rcpll_cfg2__pll_ena[2];
    u8  ib_cfg8__ib_bias_mode[1];
    u8  ib_cfg0__ib_dfe_ena[1];
    u8  ib_cfg0__ib_ia_ena[1];
    u8  ib_cfg0__ib_ld_ena[1];
    u8  ib_cfg0__ib_clkdiv_ena[1];
    u8  ib_cfg0__ib_eqz_ena[1];
    u8  ib_cfg0__ib_sam_ena[1];
 } vtss_sd10g65_pwr_down_t;

/** \brief Synthesizer frequency setup type */
typedef struct {
    u32             f_pll_khz;        /**< targeted sample frequency without ratio in kHz >                                        */
    u32             ratio_num;        /**< numerator of a rational factor >                                                        */
    u32             ratio_den;        /**< denominator of a rational factor >                                                      */
} vtss_sd10g65_f_pll_t;

/** \brief Synthesizer settings calculation result */
typedef struct {
    u16 freq_mult;       /**< Frequency multiplier cfg > */
    u64 synth_freqm;     /**< SYNTH_FREQ_M >             */
    u64 synth_freqn;     /**< SYNTH_FREQ_N >             */
} vtss_sd10g65_synth_settings_calc_rslt_t;

/** \brief Frequency decoder bypass result type */
typedef struct {
    u16 freq_mult;
    u8  freq_mult_hi;
} vtss_sd10g65_freq_dec_bypass_rslt_t;

/** \brief Syntesizer multiplier configuration calculation result */
typedef struct {
    u8  synth_speed_sel;      /**< configuration value for SYNTH_CFG0.SYNTH_SPEED_SEL >    */
    u8  synth_fbdiv_sel;      /**< configuration value for SYNTH_CFG0.SYNTH_FBDIV_SEL >    */
    u32 synth_freqm_0;        /**< LSBs of SYNTH_FREQ_M >    */
    u32 synth_freqn_0;        /**< LSBs of SYNTH_FREQ_N >    */
    u8  synth_freqm_1;        /**< MSBs of SYNTH_FREQ_M >    */
    u8  synth_freqn_1;        /**< MSBs of SYNTH_FREQ_N >    */
    u8  synth_freq_mult_byp;  /**< Frequency multiplier decoder bypass > */
    u8  synth_freq_mult_hi;   /**< Frequency multiplier MSBits in bypass mode > */
    u16 synth_freq_mult;      /**< Frequency multiplier cfg > */
    u8  tx_synth_ls_speed;    /**< Lane sync speed. Only used when setting up the synthesizer for a TX macro > */
    u8  tx_synth_cs_speed;    /**< Common sync speed. Only used when setting up the synthesizer for a TX macro > */
    u8  rx_synth_fb_step;     /**< selects step width for sync output. Only used when setting up the synthesizer for a RX macro > */
    u8  rx_synth_i2_step;     /**< selects step width for integrator2. Only used when setting up the synthesizer for a RX macro > */
} vtss_sd10g65_synth_mult_calc_rslt_t;


/** \brief Parameters needed for setup_tx function */
typedef struct {
    vtss_chip_name_t     chip_name;   /**< Name of the vitesse chip >                                                              */
    vtss_sd10g65_f_pll_t f_pll;       /**< targeted sample frequency / data rate >                                                 */
    vtss_f_mode_t        f_mode;      /**< Optional mode for setting up the frequency.                                             */
                                      /**<   Overwrites f_pll if !=  VTSS_SD10G65_MODE_NONE,                                       */
                                      /**<   Mandatory for FX100 mode                                                              */
    u8                   if_width;    /**< interface width 8, 10, 16, 20, 32 or 40 bit >                                           */
    BOOL                 no_pwrcycle; /**< Omit initial power-cycle >                                                              */
    BOOL                 ls_ena;      /**< Set synth_ls_ena for lane synchronization >                                             */
    u8                   i2_fsel;     /**< Set synth_i2_fsel, should be identical to i2_fsel of SD10G65_RX setting (default: 35) > */
    BOOL                 inp_loop;    /**< Enable input loop (bidi-loop to TXD output pad) >                                       */
    BOOL                 pad_loop;    /**< Enable pad loop (core via OB to bidi-loop) >                                            */
    BOOL                 invert;      /**< Enable inversion of output data >                                                       */
    u8                   incr_levn;   /**< Set incr_levn to increase(0)/decrease(1) output level (default: 1) >                    */
    u8                   ob_levn;     /**< Set output level to <val> (default: 7)                                                  */
    BOOL                 mute;        /**< Mute Output Buffer. I e. send out common mode voltage >                                 */
} vtss_sd10g65_setup_tx_args_t;

/** \brief return values of setup_tx function */
typedef struct {
    u32 f_pll_khz_plain[1];
    u32 f_pll_f_pll_khz[1];
    u32 f_pll_ratio_num[1];
    u32 f_pll_ratio_den[1];
    u8  pwrcycle[1];
    u8  tx_synth_cfg0__synth_ena[2];
    u8  tx_rcpll_cfg2__pll_ena[2];
    u8  ob_cfg0__en_ob[2];
    u8  sbus_tx_cfg__sbus_bias_en[1];
    u8  sbus_tx_cfg__sbus_bias_speed_sel[1];
    u8  sbus_rx_cfg__sbus_bias_en[1];
    u8  sbus_rx_cfg__sbus_bias_speed_sel[1];
  //u8  ob_cfg0__en_ob[1];
  //u8  tx_rcpll_cfg2__pll_ena[1];
  //u8  tx_synth_cfg0__synth_ena[1];
    u8  tx_synth_cfg0__synth_spare_pool[1];
    u8  tx_synth_cfg0__synth_off_comp_ena[1];
    u8  hr_mode[1];
    u8  tx_synth_cfg0__synth_speed_sel[1];   /**< configuration value for SYNTH_CFG0.SYNTH_SPEED_SEL >    */
    u8  tx_synth_cfg0__synth_fbdiv_sel[1];   /**< configuration value for SYNTH_CFG0.SYNTH_FBDIV_SEL >    */
    u32 tx_synth_cfg3__synth_freqm_0[1];     /**< LSBs of SYNTH_FREQ_M >    */
    u32 tx_synth_cfg4__synth_freqn_0[1];     /**< LSBs of SYNTH_FREQ_N >    */
    u8  tx_synth_cfg1__synth_freqm_1[1];     /**< MSBs of SYNTH_FREQ_M >    */
    u8  tx_synth_cfg1__synth_freqn_1[1];     /**< MSBs of SYNTH_FREQ_N >    */
    u8  tx_synth_cfg1__synth_freq_mult_byp[1];     /**< Frequency multiplier decoder bypass > */
    u8  tx_synth_cfg1__synth_freq_mult_hi[1];      /**< Frequency multiplier MSBits in bypass mode > */
    u16 tx_synth_cfg1__synth_freq_mult[1];         /**< Frequency multiplier cfg > */
    u8  tx_synth_cfg0__synth_ls_speed[1];    /**< Lane sync speed. Only used when setting up the synthesizer for a TX macro > */
    u8  tx_synth_cfg0__synth_cs_speed[1];    /**< Common sync speed. Only used when setting up the synthesizer for a TX macro > */
    u8  chip_needs_hrate_toggle[1];
    u8  tx_synth_cfg0__synth_hrate_ena[10];
    u8  tx_synth_cfg0__synth_ena_sync_unit[1];
    u8  tx_synth_cfg0__synth_conv_ena[1];
    u8  tx_synth_cfg0__synth_ds_ena[1];
    u8  tx_synth_cfg0__synth_ds_dir[1];
    u8  tx_synth_cfg0__synth_ds_speed[1];
    u8  tx_synth_cfg0__synth_ls_dir[1];
    u8  tx_synth_cfg0__synth_ls_ena[1];
    u8  ssc_cfg1__sync_ctrl_fsel[1];
    u8  ob_cfg0__en_inp_loop[1];
    u8  ob_cfg0__en_pad_loop[1];
    u8  ob_cfg0__sel_ifw[3];
    u8  ob_cfg0__incr_levn[1];
    u8  ob_cfg0__levn[1];
    u8  ob_cfg0__ser_inv[1];
    u8  ob_cfg1__lev_shft[1];
    u8  ob_cfg1__predrv_r_ctrl[1];
    u8  ob_cfg1__predrv_c_ctrl[1];
    u32 ob_cfg2__d_filter[1];

    u8  is_new_rcpll[1];
    u8  tx_rcpll_cfg2__pll_vco_cur[1];
    u8  tx_rcpll_cfg2__pll_vreg18[1];
    u8  tx_rcpll_cfg2__pll_lpf_cur[1];
    u8  tx_rcpll_cfg2__pll_lpf_res[1];

    u16 tx_rcpll_cfg0__pllf_start_cnt[1];
    u8  tx_rcpll_cfg0__pllf_syn_clk_ena[1];
    u8  tx_rcpll_cfg0__pllf_loop_ctrl_ena[1];
    u8  tx_rcpll_cfg0__pllf_loop_ena[1];
    u8  tx_rcpll_cfg0__pllf_ena[2];

    u16 tx_rcpll_cfg1__pllf_ref_cnt_end[1];
    u8  tx_rcpll_cfg0__pllf_oor_recal_ena[2];
} vtss_sd10g65_setup_tx_struct_t;



// Add the code for the setup_rx

/**
 * \brief Receiver preset for different cable types
 * \note _SC presets are only available for deviced that have the respective APC HW support
 *       Curently this is only Jagar2-RevC and Venice-RevC
 **/
typedef enum {
    VTSS_SD10G65_ATE,          /**< Setup be used for ATE testing > */
    VTSS_SD10G65_ATE_SC,       /**< Setup be used for ATE testing, with SmartControl > */
    VTSS_SD10G65_ZR_HW,        /**< ZR with APC hardware algorithm > */
    VTSS_SD10G65_ZR_SW,        /**< ZR with APC software algorithm > */
    VTSS_SD10G65_ZR_SC,        /**< ZR with Smart Control; L/C control based on DFE1/2 > */
    VTSS_SD10G65_DAC_HW,       /**< DAC (Direct attached copper) with APC hardware algorithm > */
    VTSS_SD10G65_DAC_SW,       /**< DAC (Direct attached copper) with APC software algorithm > */
    VTSS_SD10G65_DAC_SC,       /**< DAC (Direct attached copper) with Smart Control; L/C control based on DFE1/2 > */
    VTSS_SD10G65_SR_HW,        /**< Short Range. Use SR presets also for limiting active DAC links and DAC presets also for linear optical SR links> */
    VTSS_SD10G65_SR_SC,        /**< Short Range. with Smart Control; L/C control based on DFE1/2> */
    VTSS_SD10G65_SR2_HW,       /**< Short Range. Use SR presets also for limiting active DAC links and DAC presets also for linear optical SR links> */
    VTSS_SD10G65_SR2_SC,       /**< Short Range. with Smart Control; L/C control based on DFE1/2> */
    VTSS_SD10G65_BACKPLANE,    /**< Backplane > */
    VTSS_SD10G65_BACKPLANE_SC, /**< Backplane with Smart Control; L/C control based on DFE1/2> */
    VTSS_SD10G65_B2B,          /**< Bord to Board> */
    VTSS_SD10G65_KR_HW,        /**< KR Backplane> */
    VTSS_SD10G65_KR_SC,        /**< KR Backplane with Smart Control; L/C control based on DFE1/2> */
    VTSS_SD10G65_PRESET_NONE   /**< No preset > */
} vtss_sd10g65_preset_t;

/** \brief Receiver preset values based on selected preset mode */
typedef struct {
    i8 synth_phase_data;
    i8 ib_main_thres_offs;
    i8 ib_vscope_hl_offs;
    i8 ib_bias_adj;
    u8 ib_sam_offs_adj;
    i8 ib_tc_dfe;
    i8 ib_tc_eq;
    u8 ib_ena_400_inp;
    u8 ib_eqz_l_mode;
    u8 ib_eqz_c_mode;
    u8 ib_dfe_gain_adj;
    u8 ib_rib_adj;
    u8 ib_eq_ld1_offset;
    u8 pll_vreg18;
    u8 pll_vco_cur;
    u8 ib_sig_sel;
    u8 ib_eqz_c_adj;
    u8 synth_dv_ctrl_i1e;
} vtss_sd10g65_preset_struct_t;

/** \brief Input Buffer loop settings based on loop config */
typedef struct {
    u8 en_inp_loop;
    u8 en_pad_loop;
    u8 sig_sel;
    u8 sbus_spare_pool;
    u8 sbus_loopdrv_ena;
} vtss_sd10g65_loop_cfg_t;



/** \brief Parameters needed for setup_rx function */
typedef struct {
    vtss_chip_name_t      chip_name;   /**< Name of the vitesse chip >                                 */
    vtss_sd10g65_f_pll_t  f_pll;       /**< targeted sample frequency / data rate >                    */
    vtss_f_mode_t         f_mode;      /**< Optional mode for setting up the frequency.                */
                                       /**<   Overwrites f_pll if !=  VTSS_SD10G65_MODE_NONE,          */
                                       /**<   Mandatory for FX100 mode                                 */
    u8                    if_width;    /**< interface width 8, 10, 16, 20, 32 or 40 bit >              */
    vtss_sd10g65_preset_t preset;      /**< Setup macro with link specific presets >                   */
    BOOL                  no_pwrcycle; /**< Omit initial power-cycle >                                 */
    BOOL                  fpwr_mode;   /**< Set the fpwr_mode (default: 1) > */
    BOOL                  skip_cal;    /**< Skip ib_lat_neutral sequence (use in case IB is aleady calibrated) > */
    u8                    i1_fsel;     /**< Set synth_i1_fsel, (default: 10) > */
    u8                    i1_lim;      /**< Set synth_i1_lim,  (default: 10) > */
    u8                    i2_fsel;     /**< Set synth_i2_fsel, should be identical to i2_fsel of SD10G65_RX setting (default: 35) > */
    u8                    p_step;      /**< Set synth_p_step  (default: 1) > */
    u8                    i1_step;     /**< Set synth_i1_step (default: 1) > */
    BOOL                  i2_step;     /**< Set synth_i2_step parameter is used (default: FALSE)> */
    u8                    i2_step_val; /**< Set synth_i2_step value(default: 0) > */
    BOOL                  fb_step;     /**< Set synth_fb_step parameter is used (default: FALSE) > */
    u8                    fb_step_val; /**< Set synth_fb_step value (default: 0) > */
    BOOL                  inp_loop;    /**< Enable input loop (bidi-loop to TXD output pad) >           */
    BOOL                  pad_loop;    /**< Enable pad loop (core via OB to bidi-loop) >                */
    BOOL                  cmos_loop;   /**< Enable cmos loop (bidi-loop cmos input from core into IB) > */
    BOOL                  lock2ref;    /**< Enable lock to reference clock instead of lock to data      */
    BOOL                  invert;      /**< Enable inversion of input data >                            */
} vtss_sd10g65_setup_rx_args_t;

/** \brief return values of setup_rx function */
typedef struct {
    u32 f_pll_khz_plain[1];
    u32 f_pll_f_pll_khz[1];
    u32 f_pll_ratio_num[1];
    u32 f_pll_ratio_den[1];
    /* Initial power down-cycle (required for RCPLL ramp-up in some chips)  */
    u8  pwrcycle[1];
    u8  rx_synth_cfg0__synth_ena[10];
    u8  rx_rcpll_cfg2__pll_ena[2];
    u8  ib_cfg8__ib_bias_mode[2];
    u8  ib_cfg0__ib_dfe_ena[2];
    u8  ib_cfg0__ib_ia_ena[2];
    u8  ib_cfg0__ib_ld_ena[2];
    u8  ib_cfg0__ib_clkdiv_ena[2];
    u8  ib_cfg0__ib_eqz_ena[2];
    u8  ib_cfg0__ib_sam_ena[2];
    /* Configure SBUS                                                       */
    u8  sbus_special_handling[1];
    u8  sbus_rx_cfg__sbus_loopdrv_ena[1];
    u8  sbus_rx_cfg__sbus_spare_pool[1];
    u8  sbus_rx_cfg__sbus_bias_en[1];
    u8  sbus_rx_cfg__sbus_bias_speed_sel[1];

    /* Enable various bias circuits (SYNTH, PLL, IB)                        */
    // u8  rx_rcpll_cfg2__pll_ena[1];
    // u8  rx_synth_cfg0__synth_ena[1];
    u8  rx_synth_cfg2__synth_aux_ena[1];
    // u8  ib_cfg0__ib_clkdiv_ena[1];
    u8  ib_cfg0__ib_vbulk_sel[1];
    // u8  ib_cfg0__ib_sam_ena[1];
    // u8  ib_cfg8__ib_bias_mode[1];
    u8  ib_cfg8__ib_cml_curr[1];
    u8  ib_cfg8__ib_bias_adj[1];
    u8  chip_needs_hrate_toggle[1];
    /* Some register accesses to help the RCPLL come out of reset           */
    u8  des_cfg0__des_if_mode_sel[4];
    u8  des_cfg0__des_dis[2];

    /* Configure RX-SYNTHESIZER                                             */
    u8  rx_synth_cfg0__synth_spare_pool[1];
    u8  rx_synth_cfg0__synth_off_comp_ena[1];

    u8  rx_synth_cfg0__synth_speed_sel[1];   /**< configuration value for SYNTH_CFG0.SYNTH_SPEED_SEL >    */
    u8  rx_synth_cfg0__synth_fbdiv_sel[1];   /**< configuration value for SYNTH_CFG0.SYNTH_FBDIV_SEL >    */
    u32 rx_synth_cfg3__synth_freqm_0[1];     /**< LSBs of SYNTH_FREQ_M >    */
    u32 rx_synth_cfg4__synth_freqn_0[1];     /**< LSBs of SYNTH_FREQ_N >    */
    u8  rx_synth_cfg1__synth_freqm_1[1];     /**< MSBs of SYNTH_FREQ_M >    */
    u8  rx_synth_cfg1__synth_freqn_1[1];     /**< MSBs of SYNTH_FREQ_N >    */
    u8  rx_synth_cfg1__synth_freq_mult_byp[1];     /**< Frequency multiplier decoder bypass > */
    u8  rx_synth_cfg1__synth_freq_mult_hi[1];      /**< Frequency multiplier MSBits in bypass mode > */
    u16 rx_synth_cfg1__synth_freq_mult[1];         /**< Frequency multiplier cfg > */
    u8  fb_step_param_used[1];
    u8  rx_synth_cfg0__synth_fb_step[2];
    u8  i2_step_param_used[1];
    u8  rx_synth_cfg0__synth_i2_step[2];

    u8  rx_synth_cfg0__synth_hrate_ena[10];
    u8  rx_synth_cfg0__synth_i2_ena[1];
    u8  rx_synth_cfg0__synth_conv_ena[1];
    u8  rx_synth_sync_ctrl__synth_sc_sync[1];

    u8  rx_synth_cfg2__synth_phase_data[1];
    u8  rx_synth_cfg2__synth_cpmd_dig_ena[1];
    u8  rx_synth_cfg0__synth_p_step[1];
    u8  rx_synth_cfg0__synth_i1_step[1];

    u8  rx_synth_cfg2__synth_dv_ctrl_i1e[1];
    u8  rx_synth_cfg2__synth_dv_ctrl_i1m[1];

    u8  rx_synth_cdrlf__synth_integ3_ena[1];
    u32 rx_synth_cdrlf[1];
    u8  rx_synth_cdrlf__synth_integ1_max1[1];
    u8  rx_synth_cdrlf__synth_integ1_max0[1];
    u8  rx_synth_cdrlf__synth_integ1_lim[1];
    u8  rx_synth_cdrlf__synth_integ1_fsel[1];
    u8  rx_synth_cdrlf__synth_integ2_fsel[1];

    /* Configure IB                                                         */
    u8  ib_cfg0__ib_rib_adj[1];
    // u8  ib_cfg0__ib_eqz_ena[1];
    // u8  ib_cfg0__ib_dfe_ena[1];
    // u8  ib_cfg0__ib_ld_ena[1];
    // u8  ib_cfg0__ib_ia_ena[1];
    u8  ib_cfg0__ib_ia_sdet_ena[1];

    u8  ib_cfg3__ib_eq_ld1_offset[1];
    u8  ib_cfg3__ib_ldsd_divsel[1];
    u8  ib_cfg3__ib_ia_sdet_level[1];
    u8  ib_cfg3__ib_sdet_sel[1];

    u8  ib_cfg5__ib_offs_value[1];
    u8  ib_cfg5__ib_calmux_ena[1];

    u8  ib_cfg6__ib_sam_offs_adj[1];
    u8  ib_cfg6__ib_auto_agc_adj[1];

    u8  ib_cfg7__ib_dfe_gain_adj_s[1];
    u8  ib_cfg7__ib_dfe_gain_adj[1];
    u8  ib_cfg7__ib_dfe_offset_h[1];

    u8  skip_cal[1];

    u8  ib_cfg8__ib_lat_neutral[2];

    u8  ib_cfg4__ib_eqz_c_adj_ib[1];
    u8  ib_cfg4__ib_eqz_c_adj_es0[1];
    u8  ib_cfg4__ib_eqz_c_adj_es1[1];
    u8  ib_cfg4__ib_eqz_c_adj_es2[1];
    u8  ib_cfg4__ib_eqz_c_mode[1];
    u8  ib_cfg4__ib_eqz_l_mode[1];
    u8  ib_cfg4__ib_vscope_h_thres[1];
    u8  ib_cfg4__ib_vscope_l_thres[1];
    u8  ib_cfg4__ib_main_thres[1];

    u8  ib_cfg3__ib_set_sdet[1];
    u8  ib_cfg0__ib_sig_sel[1];
    u8  ib_cfg10__ib_loop_drv[1];
    u8  ib_cfg10__ib_loop_rec[1];
    u8  ib_cfg11__ib_ena_400_inp[1];
    u8  ib_cfg11__ib_tc_dfe[1];
    u8  ib_cfg11__ib_tc_eq[1];

    /* Configure DES                                                        */
    u8  moebdiv_cfg0__moebdiv_bw_cdr_sel_a[1];
    u8  moebdiv_cfg0__moebdiv_bw_cdr_sel_b[1];
    u8  moebdiv_cfg0__moebdiv_cpmd_swap[1];
    u8  moebdiv_cfg0__moebdiv_dis[1];
    // u8  des_cfg0__des_if_mode_sel[1];
    u8  des_cfg0__des_inv_m[1];
    u8  des_cfg0__des_inv_h[1];
    u8  des_cfg0__des_inv_l[1];

    /* Configure RX-RCPLL                                                   */
    u8  is_new_rcpll[1];
    u8  rx_rcpll_cfg2__pll_vco_cur[1];
    u8  rx_rcpll_cfg2__pll_vreg18[1];
    u8  rx_rcpll_cfg2__pll_lpf_cur[1];
    u8  rx_rcpll_cfg2__pll_lpf_res[1];

    u16 rx_rcpll_cfg0__pllf_start_cnt[1];
    u8  rx_rcpll_cfg0__pllf_syn_clk_ena[1];
    u8  rx_rcpll_cfg0__pllf_loop_ctrl_ena[1];
    u8  rx_rcpll_cfg0__pllf_loop_ena[1];
    u8  rx_rcpll_cfg0__pllf_ena[2];

    u16 rx_rcpll_cfg1__pllf_ref_cnt_end[1];
    u8  rx_rcpll_cfg0__pllf_oor_recal_ena[2];

} vtss_sd10g65_setup_rx_struct_t;


/** \brief Parameters needed for setup_f2df function */
typedef struct {
    vtss_chip_name_t      chip_name;   /**< Name of the vitesse chip >                                 */
    vtss_sd10g65_f_pll_t  f_in;       /**< targeted sample frequency / data rate >                    */
    BOOL                  no_pwrcycle; /**< Omit initial power-cycle >                                 */
    u8                    i1_fsel;     /**< Set synth_i1_fsel, (default: 10) > */
    u8                    i1_lim;      /**< Set synth_i1_lim,  (default: 10) > */
    u8                    i2_fsel;     /**< Set synth_i2_fsel, should be identical to i2_fsel of SD10G65_RX setting (default: 35) > */
    BOOL                  inp_loop;    /**< Enable input loop (bidi-loop to TXD output pad) >           */
    BOOL                  pad_loop;    /**< Enable pad loop (core via OB to bidi-loop) >                */
    BOOL                  cmos_loop;   /**< Enable cmos loop (bidi-loop cmos input from core into IB) > */
    BOOL                  invert;
} vtss_sd10g65_setup_f2df_args_t;

/** \brief return values of setup_f2df function */
typedef struct {
    u32 f_in_khz_plain[1];
    u32 f_in_f_pll_khz[1];
    u32 f_in_ratio_num[1];
    u32 f_in_ratio_den[1];
    u32 f_pll_khz_plain[1];
    u32 f_pll_f_pll_khz[1];
    u32 f_pll_ratio_num[1];
    u32 f_pll_ratio_den[1];
    /* Initial power down-cycle (required for RCPLL ramp-up in some chips)  */
    u8  pwrcycle[1];
    u8  rx_synth_cfg0__synth_ena[10];
    u8  rx_rcpll_cfg2__pll_ena[2];
    u8  ib_cfg8__ib_bias_mode[2];
    u8  ib_cfg0__ib_dfe_ena[3];
    u8  ib_cfg0__ib_ia_ena[2];
    u8  ib_cfg0__ib_ld_ena[2];
    u8  ib_cfg0__ib_clkdiv_ena[2];
    u8  ib_cfg0__ib_eqz_ena[2];
    u8  ib_cfg0__ib_sam_ena[2];
    /* Configure SBUS                                                       */
    u8  sbus_special_handling[1];
    u8  sbus_rx_cfg__sbus_loopdrv_ena[1];
    u8  sbus_rx_cfg__sbus_spare_pool[1];
    u8  sbus_rx_cfg__sbus_bias_en[1];
    u8  sbus_rx_cfg__sbus_bias_speed_sel[1];

    /* Enable various bias circuits (SYNTH, PLL, IB)                        */
    // u8  rx_rcpll_cfg2__pll_ena[1];
    // u8  rx_synth_cfg0__synth_ena[1];
    u8  rx_synth_cfg2__synth_aux_ena[1];
    // u8  ib_cfg0__ib_clkdiv_ena[1];
    u8  ib_cfg0__ib_vbulk_sel[1];
    // u8  ib_cfg0__ib_sam_ena[1];
    // u8  ib_cfg8__ib_bias_mode[1];
    u8  ib_cfg8__ib_cml_curr[1];
    u8  ib_cfg8__ib_bias_adj[1];
    u8  chip_needs_hrate_toggle[1];
    /* Some register accesses to help the RCPLL come out of reset           */
    u8  des_cfg0__des_if_mode_sel[4];
    u8  des_cfg0__des_dis[2];

    /* Configure RX-SYNTHESIZER                                             */
    u8  rx_synth_cfg0__synth_spare_pool[1];
    u8  rx_synth_cfg0__synth_off_comp_ena[1];

    u8  rx_synth_cfg0__synth_speed_sel[1];   /**< configuration value for SYNTH_CFG0.SYNTH_SPEED_SEL >    */
    u8  rx_synth_cfg0__synth_fbdiv_sel[1];   /**< configuration value for SYNTH_CFG0.SYNTH_FBDIV_SEL >    */
    u32 rx_synth_cfg3__synth_freqm_0[1];     /**< LSBs of SYNTH_FREQ_M >    */
    u32 rx_synth_cfg4__synth_freqn_0[1];     /**< LSBs of SYNTH_FREQ_N >    */
    u8  rx_synth_cfg1__synth_freqm_1[1];     /**< MSBs of SYNTH_FREQ_M >    */
    u8  rx_synth_cfg1__synth_freqn_1[1];     /**< MSBs of SYNTH_FREQ_N >    */
    u8  rx_synth_cfg1__synth_freq_mult_byp[1];     /**< Frequency multiplier decoder bypass > */
    u8  rx_synth_cfg1__synth_freq_mult_hi[1];      /**< Frequency multiplier MSBits in bypass mode > */
    u16 rx_synth_cfg1__synth_freq_mult[1];         /**< Frequency multiplier cfg > */
    u8  rx_synth_cfg0__synth_fb_step[1];
    u8  rx_synth_cfg0__synth_i2_step[1];

    u8  rx_synth_cfg0__synth_hrate_ena[10];
    u8  rx_synth_cfg0__synth_i2_ena[1];
    u8  rx_synth_cfg0__synth_conv_ena[1];
    u8  rx_synth_sync_ctrl__synth_sc_sync[1];

    u8  rx_synth_cfg2__synth_phase_data[1];
    u8  rx_synth_cfg2__synth_cpmd_dig_ena[1];
    u8  rx_synth_cfg0__synth_p_step[1];
    u8  rx_synth_cfg0__synth_i1_step[1];

    u8  rx_synth_cfg2__synth_dv_ctrl_i1e[2];
    u8  rx_synth_cfg2__synth_dv_ctrl_i1m[2];

    u8  rx_synth_cdrlf__synth_integ3_ena[2];
    u32 rx_synth_cdrlf[2];
    u8  rx_synth_cdrlf__synth_integ1_max1[2];
    u8  rx_synth_cdrlf__synth_integ1_max0[2];
    u8  rx_synth_cdrlf__synth_integ1_lim[2];
    u8  rx_synth_cdrlf__synth_integ1_fsel[2];
    u8  rx_synth_cdrlf__synth_integ2_fsel[2];

    /* Configure IB                                                         */
    u8  ib_cfg0__ib_rib_adj[1];
    // u8  ib_cfg0__ib_eqz_ena[1];
    // u8  ib_cfg0__ib_dfe_ena[1];
    // u8  ib_cfg0__ib_ld_ena[1];
    // u8  ib_cfg0__ib_ia_ena[1];
    u8  ib_cfg0__ib_ia_sdet_ena[1];

    u8  ib_cfg3__ib_eq_ld1_offset[1];
    u8  ib_cfg3__ib_ldsd_divsel[1];
    u8  ib_cfg3__ib_ia_sdet_level[2];
    u8  ib_cfg3__ib_sdet_sel[2];

    u8  ib_cfg5__ib_offs_value[2];
    u8  ib_cfg5__ib_calmux_ena[1];

    u8  ib_cfg6__ib_sam_offs_adj[1];
    u8  ib_cfg6__ib_auto_agc_adj[1];

    u8  ib_cfg7__ib_dfe_gain_adj_s[1];
    u8  ib_cfg7__ib_dfe_gain_adj[1];
    u8  ib_cfg7__ib_dfe_offset_h[1];

    u8  skip_cal[1];

    u8  ib_cfg8__ib_lat_neutral[2];

    u8  ib_cfg4__ib_eqz_c_adj_ib[1];
    u8  ib_cfg4__ib_eqz_c_adj_es0[1];
    u8  ib_cfg4__ib_eqz_c_adj_es1[1];
    u8  ib_cfg4__ib_eqz_c_adj_es2[1];
    u8  ib_cfg4__ib_eqz_c_mode[1];
    u8  ib_cfg4__ib_eqz_l_mode[1];
    u8  ib_cfg4__ib_vscope_h_thres[1];
    u8  ib_cfg4__ib_vscope_l_thres[1];
    u8  ib_cfg4__ib_main_thres[1];

    u8  ib_cfg3__ib_set_sdet[1];
    u8  ib_cfg0__ib_sig_sel[1];
    u8  ib_cfg10__ib_loop_drv[1];
    u8  ib_cfg10__ib_loop_rec[1];
    u8  ib_cfg11__ib_ena_400_inp[1];
    u8  ib_cfg11__ib_tc_dfe[1];
    u8  ib_cfg11__ib_tc_eq[1];

    /* Configure DES                                                        */
    u8  moebdiv_cfg0__moebdiv_bw_cdr_sel_a[1];
    u8  moebdiv_cfg0__moebdiv_bw_cdr_sel_b[1];
    u8  moebdiv_cfg0__moebdiv_cpmd_swap[1];
    u8  des_cfg0__des_inv_m[1];
    u8  des_cfg0__des_inv_h[1];
    u8  des_cfg0__des_inv_l[1];
    u8  moebdiv_cfg0__moebdiv_dis[1];
    // u8  des_cfg0__des_if_mode_sel[1];

    /* Configure RX-RCPLL                                                   */
    u8  is_new_rcpll[1];
    u8  rx_rcpll_cfg2__pll_vco_cur[1];
    u8  rx_rcpll_cfg2__pll_vreg18[1];
    u8  rx_rcpll_cfg2__pll_lpf_cur[1];
    u8  rx_rcpll_cfg2__pll_lpf_res[1];

    u16 rx_rcpll_cfg0__pllf_start_cnt[1];
    u8  rx_rcpll_cfg0__pllf_syn_clk_ena[1];
    u8  rx_rcpll_cfg0__pllf_loop_ctrl_ena[1];
    u8  rx_rcpll_cfg0__pllf_loop_ena[1];
    u8  rx_rcpll_cfg0__pllf_ena[2];

    u16 rx_rcpll_cfg1__pllf_ref_cnt_end[1];
    u8  rx_rcpll_cfg0__pllf_oor_recal_ena[2];


    /* Perform setup_f2df config */

    /* Do some input buffer updates for SD10G running in F2DF mode */
    u16 ib_cfg2__ib_eqz_gain[1];
    u8  ib_cfg1__ib_amp_l[1];
    u8  ib_cfg1__ib_eqz_l0[1];
    u8  ib_cfg1__ib_eqz_l1[1];
    u8  ib_cfg1__ib_eqz_l2[1];
    u8  ib_cfg1__ib_agc_l[1];
    u8  ib_cfg1__ib_amp_c[1];
    u8  ib_cfg1__ib_eqz_c0[1];
    u8  ib_cfg1__ib_eqz_c1[1];
    u8  ib_cfg1__ib_eqz_c2[1];
    u8  ib_cfg9__ib_dfe_coef1[1];

    /* Setup the Signal Detect logic */
    //u8  ib_cfg3__ib_sdet_sel[1];
    /* Configure Signal detect clock divider */
    u8  ib_cfg3__ib_sdet_clk_div[1];
    //u8  ib_cfg3__ib_ia_sdet_level[1];
    /* Manually calibrate the IB */
    // u8  ib_cfg5__ib_offs_value[1];
    u8  ib_cfg5__ib_offs_blksel[4];
    u8  ib_cfg5__ib_ia_offs_cal_ena[2];
    u8  rx_synth_cfg2__synth_dv_ctrl_i2e[1];
    // u8  rx_synth_cfg2__synth_dv_ctrl_i1m[1];
    // u8  rx_synth_cfg2__synth_dv_ctrl_i1e[1];
    // u8  rx_synth_cdrlf__synth_integ3_ena[1];
    // u8  rx_synth_cdrlf__synth_integ1_max1[1];
    // u8  rx_synth_cdrlf__synth_integ1_max0[1];
    // u8  rx_synth_cdrlf__synth_integ1_lim[1];
    // u8  rx_synth_cdrlf__synth_integ1_fsel[1];
    // u32 rx_synth_cdrlf[1];
    // u8  rx_synth_cdrlf__synth_integ2_fsel[1];

    u8  chip_still_has_sample_mode[1];
    u32 f2df_cfg_stat[1];
    u8  f2df_cfg_stat__f2df_side_det_bit_sel[1];
    u8  f2df_cfg_stat__f2df_side_det_ones_weight[1];
    u8  f2df_cfg_stat__f2df_side_det_zeros_weight[1];
    u8  f2df_cfg_stat__f2df_tog_det_cnt[1];
    u8  f2df_cfg_stat__f2df_data_valid_propper_side[1];
    u8  f2df_cfg_stat__f2df_sticky_clr[1];
    u8  f2df_cfg_stat__f2df_sample_mode_div[1];
    u8  f2df_cfg_stat__f2df_enable[1];

} vtss_sd10g65_setup_f2df_struct_t;

/** \brief Parameters needed for setup_df2f function */
typedef struct {
    vtss_chip_name_t     chip_name;   /**< Name of the vitesse chip >                                                              */
    vtss_sd10g65_f_pll_t f_out;       /**< Set frequency of output clock signal >                                                  */
    BOOL                 use_par_clk; /**< Provide the geneated clock on the parallel interface towards the core rather then on the HS I/O */
    BOOL                 no_pwrcycle; /**< Omit initial power-cycle >                                                              */
    BOOL                 ls_ena;      /**< Set synth_ls_ena for lane synchronization >                                             */
    u8                   i2_fsel;     /**< Set synth_i2_fsel, should be identical to i2_fsel of SD10G65_RX setting (default: 35) > */
    BOOL                 inp_loop;    /**< Enable input loop (bidi-loop to TXD output pad) >                                       */
    BOOL                 pad_loop;    /**< Enable pad loop (core via OB to bidi-loop) >                                            */
    u8                   incr_levn;   /**< Set incr_levn to increase(0)/decrease(1) output level (default: 1) >                    */
    u8                   ob_levn;     /**< Set output level to <val> (default: 7)                                                  */
} vtss_sd10g65_setup_df2f_args_t;


/** \brief return values of setup_df2f function */
typedef struct {
    u32 f_out_khz_plain[1];
    u32 f_out_f_pll_khz[1];
    u32 f_out_ratio_num[1];
    u32 f_out_ratio_den[1];
    u32 f_sam_khz_plain[1];
    u32 f_sam_f_pll_khz[1];
    u32 f_sam_ratio_num[1];
    u32 f_sam_ratio_den[1];
    u8  pwrcycle[1];
    u8  tx_synth_cfg0__synth_ena[2];
    u8  tx_rcpll_cfg2__pll_ena[2];
    u8  ob_cfg0__en_ob[2];
    u8  sbus_special_handling[1];
    u8  sbus_tx_cfg__sbus_bias_en[1];
    u8  sbus_tx_cfg__sbus_bias_speed_sel[1];
    u8  sbus_rx_cfg__sbus_bias_en[1];
    u8  sbus_rx_cfg__sbus_bias_speed_sel[1];
  //u8  ob_cfg0__en_ob[1];
  //u8  tx_rcpll_cfg2__pll_ena[1];
  //u8  tx_synth_cfg0__synth_ena[1];
    u8  tx_synth_cfg0__synth_spare_pool[1];
    u8  tx_synth_cfg0__synth_off_comp_ena[1];
    u8  hr_mode[1];
    u8  tx_synth_cfg0__synth_speed_sel[1];   /**< configuration value for SYNTH_CFG0.SYNTH_SPEED_SEL >    */
    u8  tx_synth_cfg0__synth_fbdiv_sel[1];   /**< configuration value for SYNTH_CFG0.SYNTH_FBDIV_SEL >    */
    u32 tx_synth_cfg3__synth_freqm_0[1];     /**< LSBs of SYNTH_FREQ_M >    */
    u32 tx_synth_cfg4__synth_freqn_0[1];     /**< LSBs of SYNTH_FREQ_N >    */
    u8  tx_synth_cfg1__synth_freqm_1[1];     /**< MSBs of SYNTH_FREQ_M >    */
    u8  tx_synth_cfg1__synth_freqn_1[1];     /**< MSBs of SYNTH_FREQ_N >    */
    u8  tx_synth_cfg1__synth_freq_mult_byp[1];     /**< Frequency multiplier decoder bypass > */
    u8  tx_synth_cfg1__synth_freq_mult_hi[1];      /**< Frequency multiplier MSBits in bypass mode > */
    u16 tx_synth_cfg1__synth_freq_mult[1];         /**< Frequency multiplier cfg > */
    u8  tx_synth_cfg0__synth_ls_speed[1];    /**< Lane sync speed. Only used when setting up the synthesizer for a TX macro > */
    u8  tx_synth_cfg0__synth_cs_speed[1];    /**< Common sync speed. Only used when setting up the synthesizer for a TX macro > */
    u8  chip_needs_hrate_toggle[1];
    u8  tx_synth_cfg0__synth_hrate_ena[10];
    u8  tx_synth_cfg0__synth_ena_sync_unit[1];
    u8  tx_synth_cfg0__synth_conv_ena[1];
    u8  tx_synth_cfg0__synth_ds_ena[1];
    u8  tx_synth_cfg0__synth_ds_dir[1];
    u8  tx_synth_cfg0__synth_ds_speed[1];
    u8  tx_synth_cfg0__synth_ls_dir[1];
    u8  tx_synth_cfg0__synth_ls_ena[1];
    u8  ssc_cfg1__sync_ctrl_fsel[1];
    u8  ob_cfg0__en_inp_loop[1];
    u8  ob_cfg0__en_pad_loop[1];
    u8  ob_cfg0__ser_inv[1];
    u8  ob_cfg0__sel_ifw[3];
    u8  ob_cfg0__incr_levn[1];
    u8  ob_cfg0__levn[1];
    u8  ob_cfg0__en_direct[1];
    u8  ob_cfg1__lev_shft[1];
    u8  ob_cfg1__predrv_r_ctrl[1];
    u8  ob_cfg1__predrv_c_ctrl[1];
    u32 ob_cfg2__d_filter[1];

    u8  is_new_rcpll[1];
    u8  tx_rcpll_cfg2__pll_vco_cur[1];
    u8  tx_rcpll_cfg2__pll_vreg18[1];
    u8  tx_rcpll_cfg2__pll_lpf_cur[1];
    u8  tx_rcpll_cfg2__pll_lpf_res[1];

    u16 tx_rcpll_cfg0__pllf_start_cnt[1];
    u8  tx_rcpll_cfg0__pllf_syn_clk_ena[1];
    u8  tx_rcpll_cfg0__pllf_loop_ctrl_ena[1];
    u8  tx_rcpll_cfg0__pllf_loop_ena[1];
    u8  tx_rcpll_cfg0__pllf_ena[2];

    u16 tx_rcpll_cfg1__pllf_ref_cnt_end[1];
    u8  tx_rcpll_cfg0__pllf_oor_recal_ena[2];

    u8  use_par_clk[1];
    u8  use_clk_gen[1];
    u16 dft_clk_gen_cfg__cg_per_cfg[1];
    u16 dft_clk_gen_cfg__cg_per_jump_cfg[1];
    u16 dft_clk_gen_cfg__cg_dcd_cfg[1];
    u8  dft_clk_gen_cfg__cg_mode_cfg[1];
    u8  dft_tx_cfg__tx_wid_sel_cfg[1];
    u8  dft_tx_cfg__opath_cfg[1];
    u8  dft_tx_cfg__dft_tx_ena[1];
    u8  dft_tx_cfg__tx_word_mode_cfg[1];
    u8  dft_tx_cfg__ipath_cfg[1];
    u8  dft_tx_cfg__tx_prbs_sel_cfg[1];
    u8  dft_tx_cfg__scram_inv_cfg[1];
    u8  num_words[1];
    u8  dft_tx_pat_cfg__store_addr_cfg[16];
    u16 dft_tx_pat_cfg__pattern_cfg[16];
    u8  dft_tx_pat_cfg__pat_vld_cfg[2];
    u8  dft_tx_pat_cfg__max_addr_gen_cfg[2];
    u8  interface_width[1];


} vtss_sd10g65_setup_df2f_struct_t;


/* ================================================================= *
 *  Function prototypes
 * ================================================================= */

vtss_rc vtss_sd10g65_get_f_pll_from_f_mode(vtss_f_mode_t  f_mode,
                                           vtss_sd10g65_f_pll_t *const ret_val);

vtss_rc vtss_sd10g65_pwr_down(vtss_sd10g65_pwr_down_t *const ret_val);

vtss_rc vtss_sd10g65_setup_tx_args_init(vtss_sd10g65_setup_tx_args_t     *const init_val);
vtss_rc vtss_sd10g65_setup_rx_args_init(vtss_sd10g65_setup_rx_args_t     *const init_val);
vtss_rc vtss_sd10g65_setup_f2df_args_init(vtss_sd10g65_setup_f2df_args_t *const init_val);
vtss_rc vtss_sd10g65_setup_df2f_args_init(vtss_sd10g65_setup_df2f_args_t *const init_val);

vtss_rc vtss_calc_sd10g65_setup_tx(const vtss_sd10g65_setup_tx_args_t config,
                                    vtss_sd10g65_setup_tx_struct_t    *const ret_val);

vtss_rc vtss_calc_sd10g65_setup_rx(const vtss_sd10g65_setup_rx_args_t config,
                                   vtss_sd10g65_setup_rx_struct_t     *const ret_val );

vtss_rc vtss_calc_sd10g65_setup_f2df(const vtss_sd10g65_setup_f2df_args_t config,
                                     vtss_sd10g65_setup_f2df_struct_t     *const ret_val);

vtss_rc vtss_calc_sd10g65_setup_df2f(const vtss_sd10g65_setup_df2f_args_t config,
                                     vtss_sd10g65_setup_df2f_struct_t    *const ret_val);

#endif
