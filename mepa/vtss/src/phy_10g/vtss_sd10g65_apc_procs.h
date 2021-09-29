// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/*---------------------------------------------------------------------------
 * $HeadURL: svn://svn-de.vitesse.com/svn-de/vtslibs/vts_ute_tcllib/tags/UTE_release_vts_ute_tcllib_20180312_trunk_bjo/api_c/vtss_sd10g65_apc_procs.h $
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


#ifndef _VTSS_SD10G65_APC_PROCS_H_
#define _VTSS_SD10G65_APC_PROCS_H_


#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#endif

/* ================================================================= *
 *  Data structures / types
 * ================================================================= */
/** \brief APC preset values based on selected  preset mode */
typedef struct {
    u8  ld_lev_ini;
    u8  range_sel;
    u8  dfe1_min;
    u8  dfe1_max;
    u16 gain_ini;
    u8  gain_adj_ini;
    u8  gain_chg_mode;
    u8  c_min;
    u8  c_max;
    u8  c_ini;
    u8  c_rs_offs;
    u8  c_chg_mode;
    u8  l_min;
    u8  l_max;
    u8  l_ini;
    u8  l_rs_offs;
    u8  l_chg_mode;
    u8  agc_min;
    u8  agc_max;
    u8  agc_ini;
    u8  lc_smartctrl;
} vtss_sd10g65_apc_preset_struct_t;


/** \brief Parameters needed for setup_apc function */
typedef struct {
    vtss_chip_name_t      chip_name;       /**< Name of the vitesse chip >                                 */
    BOOL                  is_malibu_f2df_or_df2f; /** Set to True for malibu if target is a F2DF or DF2F   */
    vtss_sd10g65_f_pll_t  f_pll;           /**< targeted sample frequency / data rate >                    */
    u8                    if_width;        /**< interface width 8, 10, 16, 20, 32 or 40 bit >              */
    vtss_sd10g65_preset_t preset;          /**< Setup macro with link specific presets >                   */
    BOOL                  skip_cal;        /**< Skip ib_lat_neutral sequence (use in case IB is aleady calibrated) > */
    BOOL                  is_2pt_cal;      /**< Use two point IS-calibration approach (default: single point calibration) > */
    BOOL                  incl_ld_cal;     /**< Include legacy LD calibration                             */
    BOOL                  ib_cal_only;     /**< Perform only IB-calibration. APC is disabled afterwards > */
    BOOL                  force_eqz_l;     /**< If TRUE, force_eqz_l_val is used > */
    BOOL                  force_eqz_c;     /**< If TRUE, force_eqz_c_val is used > */
    u8                    force_eqz_l_val; /**< EQZ_L force value (range: 0..63) > */
    u8                    force_eqz_c_val; /**< EQZ_C force value (range: 0..31) > */
    BOOL                  offset_guard;    /**< Enable offset guard > */
    BOOL                  lc_softctrl;     /**< Set eqz_l and eqz_c via LC softcontrol algorithm (do not use for ATE-pattern!) > */
    BOOL                  throttle_mode;   /**< Enable throttling mode. The relative operation time is set to 10% > */
    BOOL                  ld_lev_ini;      /**< If TRUE, ld_lev_ini_val is used > */
    u8                    ld_lev_ini_val;  /**< ld_lev_ini value (default: 24) > */
    BOOL                  range_sel;       /**< If TRUE, range_sel_val is used > */
    u8                    range_sel_val;   /**< Range_sel parameter (range 10..20; default: 12) > */
    BOOL                  single_step;     /**< Prepare for single-step operation (do not use together with -throttle_mode) > */
    BOOL                  invert;          /**< Prepare APC for use with inverted data (should match invert option of sd10g65_setup_rx) > */
} vtss_sd10g65_setup_apc_args_t;

typedef struct {
    u8  apc_common_cfg0__apc_fsm_recover_mode[1];
    u8  apc_common_cfg0__hml_errcorr_ena[1];
    u8  apc_common_cfg0__skip_cal[2];
    u8  apc_common_cfg0__if_width[1];
    u8  apc_common_cfg0__reset_apc[3];
    u8  apc_common_cfg0__apc_direct_ena[2];

    u8  apc_common_cfg1__offscal_dis_swap[1];

    u8  apc_ld_cal_cfg__cal_clk_div[1];
    /*  clear all skip bits which might be set from previous runs */
    u8  apc_is_cal_cfg0__skip_observe_init[2];
    u8  apc_is_cal_cfg0__skip_offset_init[2];
    u8  apc_is_cal_cfg0__skip_threshold_init[2];
    u8  apc_is_cal_cfg0__skip_dfe_buffer_init[2];
    u8  apc_is_cal_cfg0__skip_observe_cal[2];
    u8  apc_is_cal_cfg0__skip_offset_cal[2];
    u8  apc_is_cal_cfg0__skip_threshold_cal[3];
    u8  apc_is_cal_cfg0__skip_dfe_buffer_cal[2];
    u8  apc_is_cal_cfg1__par_data_num_ones_thres[1];
    u8  apc_is_cal_cfg1__cal_num_iterations[1];

    u16 calibration_time_ms[2];

    u8  apc_eqz_common_cfg__eqz_gain_auto_restart[1];

    u8  ib_cal_only[1];

    u8  apc_eqz_agc_par_cfg__eqz_agc_ini[1];
    u8  apc_dfe1_par_cfg__dfe1_ini[1];
    u8  apc_dfe2_par_cfg__dfe2_ini[1];
    u8  apc_dfe3_par_cfg__dfe3_ini[1];
    u8  apc_dfe4_par_cfg__dfe4_ini[1];

    u8  throttle_mode[1];

    u8  sd10g65_ib_cfg0__ib_vscope_ena[1];
    u8  apc_parctrl_sync_cfg__fsm1_op_mode[2];
    u16 apc_parctrl_fsm1_timer_cfg__fsm1_op_time[1];
    u16 apc_top_ctrl_cfg__sleep_time[1];
    u8  apc_common_cfg0__throttle_mode[1];

    u8  single_step[1];

    u8  invert[1];

    u8  apc_eqz_ld_ctrl__ld_lev_ini[1];

    u16 apc_eqz_ld_ctrl_cfg0__ld_t_deadtime_wrk[1];
    u16 apc_eqz_ld_ctrl_cfg0__ld_t_timeout_wrk[1];
    u16 apc_eqz_ld_ctrl_cfg1__ld_t_deadtime_cal[1];
    u16 apc_eqz_ld_ctrl_cfg1__ld_t_timeout_cal[1];

    u8  apc_eqz_pat_match_cfg0__eqz_c_pat_mask[1];
    u8  apc_eqz_pat_match_cfg0__eqz_c_pat_match[1];
    u8  apc_eqz_pat_match_cfg0__eqz_l_pat_mask[1];
    u8  apc_eqz_pat_match_cfg0__eqz_l_pat_match[1];

    u8  apc_eqz_pat_match_cfg1__eqz_offs_pat_mask[1];
    u8  apc_eqz_pat_match_cfg1__eqz_offs_pat_match[1];
    u8  apc_eqz_pat_match_cfg1__eqz_agc_pat_mask[1];
    u8  apc_eqz_pat_match_cfg1__eqz_agc_pat_match[1];

    u8  apc_eqz_offs_par_cfg__eqz_offs_chg_mode[1];
    u8  apc_eqz_offs_par_cfg__eqz_offs_range_sel[1];
    u8  apc_eqz_offs_par_cfg__eqz_offs_max[1];
    u8  apc_eqz_offs_par_cfg__eqz_offs_min[1];
    u8  apc_eqz_offs_par_cfg__eqz_offs_ini[1];
    u8  apc_eqz_offs_par_cfg__eqz_offs_dir_sel[1];
    u8  apc_eqz_offs_ctrl__eqz_offs_sync_mode[1];

    u8  apc_eqz_agc_par_cfg__eqz_agc_chg_mode[1];
    u8  apc_eqz_agc_par_cfg__eqz_agc_range_sel[1];
    u8  apc_eqz_agc_par_cfg__eqz_agc_max[1];
    u8  apc_eqz_agc_par_cfg__eqz_agc_min[1];
    // u8  apc_eqz_agc_par_cfg__eqz_agc_ini[1];
    u8  apc_eqz_agc_ctrl__eqz_agc_sync_mode[1];

    /* L anc C control either forced or enabled for higher data rates only */
    u8  high_data_rate[1];
    u8  force_eqz_l[1];
    u8  apc_eqz_l_par_cfg__eqz_l_chg_mode[1];
    u8  apc_eqz_l_par_cfg__eqz_l_range_sel[1];
    u8  apc_eqz_l_par_cfg__eqz_l_max[1];
    u8  apc_eqz_l_par_cfg__eqz_l_min[1];
    u8  apc_eqz_l_par_cfg__eqz_l_ini[1];
    u8  apc_eqz_l_ctrl__eqz_l_sync_mode[1];
    u8  force_eqz_c[1];
    u8  apc_eqz_c_par_cfg__eqz_c_chg_mode[1];
    u8  apc_eqz_c_par_cfg__eqz_c_range_sel[1];
    u8  apc_eqz_c_par_cfg__eqz_c_max[1];
    u8  apc_eqz_c_par_cfg__eqz_c_min[1];
    u8  apc_eqz_c_par_cfg__eqz_c_ini[1];
    u8  apc_eqz_c_ctrl__eqz_c_sync_mode[1];

    /* DFE settings */
    u8  apc_dfe1_par_cfg__dfe1_chg_mode[1];
    u8  apc_dfe1_par_cfg__dfe1_range_sel[1];
    u8  apc_dfe1_par_cfg__dfe1_max[1];
    u8  apc_dfe1_par_cfg__dfe1_min[1];
    //u8  apc_dfe1_par_cfg__dfe1_ini[1];
    u8  apc_dfe1_ctrl__dfe1_sync_mode[1];

    u8  apc_dfe2_par_cfg__dfe2_chg_mode[1];
    u8  apc_dfe2_par_cfg__dfe2_range_sel[1];
    u8  apc_dfe2_par_cfg__dfe2_max[1];
    u8  apc_dfe2_par_cfg__dfe2_min[1];
    //u8  apc_dfe2_par_cfg__dfe2_ini[1];
    u8  apc_dfe2_ctrl__dfe2_sync_mode[1];

    u8  apc_dfe3_par_cfg__dfe3_chg_mode[1];
    u8  apc_dfe3_par_cfg__dfe3_range_sel[1];
    u8  apc_dfe3_par_cfg__dfe3_max[1];
    u8  apc_dfe3_par_cfg__dfe3_min[1];
    //u8  apc_dfe3_par_cfg__dfe3_ini[1];
    u8  apc_dfe3_ctrl__dfe3_sync_mode[1];

    u8  apc_dfe4_par_cfg__dfe4_chg_mode[1];
    u8  apc_dfe4_par_cfg__dfe4_range_sel[1];
    u8  apc_dfe4_par_cfg__dfe4_max[1];
    u8  apc_dfe4_par_cfg__dfe4_min[1];
    //u8  apc_dfe4_par_cfg__dfe4_ini[1];
    u8  apc_dfe4_ctrl__dfe4_sync_mode[1];

    /* gain setting */
    u16 apc_eqz_gain_ctrl_cfg__eqz_gain_ini[1];
    u8  apc_eqz_gain_adj_ctrl_cfg__eqz_gain_adj_ini[1];
    u8  apc_eqz_common_cfg__eqz_gain_chg_mode[1];

    /* do calibration if desired */
    u8  skip_cal[1];
    u8  is_2pt_cal[1];
    u8  incl_ld_cal[1];
    u8  sd10g65_ib_cfg8__ib_inv_thr_cal_val[1];
    u8  apc_is_cal_cfg0__cpmd_thres_init[1];
    u8  apc_is_cal_cfg0__vsc_thres_init[1];
    // u8  apc_is_cal_cfg0__skip_threshold_cal[1];
    u8  apc_is_cal_cfg1__cal_vsc_offset_tgt[1];
    u8  sd10g65_ib_cfg0__ib_dfe_ena[2];
    u8  sd10g65_des_cfg0__des_inv_x[2];

    u8  apc_common_cfg0__apc_mode[3];
    // u8  apc_common_cfg0__reset_apc[1];

    // u8  sd10g65_ib_cfg0__ib_dfe_ena[1];
    // u8  apc_common_cfg0__apc_mode[1];
    // u8  apc_common_cfg0__apc_direct_ena[1];
    /*  calibration done */


    // u8  apc_is_cal_cfg0__skip_observe_init[1];
    // u8  apc_is_cal_cfg0__skip_offset_init[1];
    // u8  apc_is_cal_cfg0__skip_threshold_init[1];
    // u8  apc_is_cal_cfg0__skip_dfe_buffer_init[1];
    // u8  apc_is_cal_cfg0__skip_observe_cal[1];
    // u8  apc_is_cal_cfg0__skip_offset_cal[1];
    // u8  apc_is_cal_cfg0__skip_threshold_cal[1];
    // u8  apc_is_cal_cfg0__skip_dfe_buffer_cal[1];
    // u8  apc_common_cfg0__skip_cal[1];
    // u8  apc_common_cfg0__apc_mode[1];
    // u8  apc_common_cfg0__reset_apc[1];

    u8  lc_smartctrl[1];
    u8  apc_lc_softctrl_cfg1__lc_sc_dfe2_target[1];
    u8  apc_lc_softctrl_cfg1__lc_sc_dfe1_target[1];

    u8  apc_lc_softctrl_cfg__lc_sc_timer[1];
    u8  apc_lc_softctrl_cfg__lc_sc_avgshft[1];
    u8  apc_lc_softctrl_cfg__lc_sc_dfe1_threshold[1];
    u8  apc_lc_softctrl_cfg__lc_sc_dfe2_threshold[1];
    u8  apc_lc_softctrl_cfg__lc_sc_agc_threshold[1];
    u8  apc_lc_softctrl_cfg__lc_sc_div_c_sel[1];
    u8  apc_lc_softctrl_cfg__lc_sc_div_l[1];
    u8  apc_lc_softctrl_cfg__lc_sc_div_c[1];
    u8  apc_lc_softctrl_cfg__lc_sc_mode[1];
} vtss_sd10g65_setup_apc_struct_t;

/* ================================================================= *
 *  Function prototypes
 * ================================================================= */
vtss_rc vtss_sd10g65_setup_apc_args_init(vtss_sd10g65_setup_apc_args_t     *const init_val);
vtss_rc vtss_calc_sd10g65_setup_apc(const vtss_sd10g65_setup_apc_args_t config,
                                    vtss_sd10g65_setup_apc_struct_t     *const ret_val );

#endif

/* ******************************************************************************** */
/* ***                        E N D   O F    F I L E                            *** */
/* ******************************************************************************** */
