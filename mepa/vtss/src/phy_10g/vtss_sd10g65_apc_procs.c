// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT



/*---------------------------------------------------------------------------
 * $HeadURL: svn://svn-de.vitesse.com/svn-de/vtslibs/vts_ute_tcllib/tags/UTE_release_vts_ute_tcllib_20180312_trunk_bjo/api_c/vtss_sd10g65_apc_procs.c $
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

#include <stdio.h>

#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#else
#include <vtss_phy_api.h>
#include "../common/vtss_phy_common.h"
#endif

#include "vtss_sd10g65_procs.h"
#include "vtss_sd10g65_apc_procs.h"

static u8 to_u8_(const BOOL a) {
    return (a == TRUE) ? 1 : 0;
}

/* function to map from SD10G65 interface width to configuration value */
static u8   sd10g65_apc_get_iw_setting(const u8     interface_width) {
    switch (interface_width) {
        case 8: {
            return 0;
            break;
        }
        case 10: {
            return 1;
            break;
        }
        case 16: {
            return 2;
            break;
        }
        case 20: {
            return 3;
            break;
        }
        case 32: {
            return 4;
            break;
        }
        case 40: {
            return 5;
            break;
        }
        default : {
            VTSS_E("Illegal value %d for interface width\n", interface_width);
            return VTSS_RC_ERROR;
        }
    }
}

static vtss_rc vtss_sd10g65_apc_set_default_preset_values (const vtss_chip_name_t chip_name,
                                                           vtss_sd10g65_apc_preset_struct_t *const preset) {

    if ((chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (chip_name == VTSS_SD10G65_CHIP_ES6514) ||
        (chip_name == VTSS_SD10G65_CHIP_JAGUAR2)) {
        preset->ld_lev_ini    =  24;
        preset->range_sel     =  20;
        preset->dfe1_min      =   0;
        preset->dfe1_max      =  80;
        preset->gain_ini      =   0;
        preset->gain_adj_ini  =   0;
        preset->gain_chg_mode =   0;
        preset->c_min         =   0;
        preset->c_max         =  31;
        preset->c_ini         =  13;
        preset->c_rs_offs     =   3;
        preset->c_chg_mode    =   0;
        preset->l_min         =   0;
        preset->l_max         =  62;
        preset->l_ini         =  26;
        preset->l_rs_offs     =   2;
        preset->l_chg_mode    =   0;
        preset->agc_min       =   0;
        preset->agc_max       = 248;
        preset->agc_ini       = 104;
        preset->lc_smartctrl  =   0;
    } else {
        preset->ld_lev_ini    =  24;
        preset->range_sel     =  20;
        preset->dfe1_min      =   0;
        preset->dfe1_max      =  80;
        preset->gain_ini      =   0;
        preset->gain_adj_ini  =   0;
        preset->gain_chg_mode =   0;
        preset->c_min         =   0;
        preset->c_max         =  31;
        preset->c_ini         =  11;
        preset->c_rs_offs     =   3;
        preset->c_chg_mode    =   0;
        preset->l_min         =   0;
        preset->l_max         =  62;
        preset->l_ini         =  22;
        preset->l_rs_offs     =   2;
        preset->l_chg_mode    =   0;
        preset->agc_min       =   0;
        preset->agc_max       = 248;
        preset->agc_ini       =  88;
        preset->lc_smartctrl  =   0;
    }

    return VTSS_RC_OK;
}

/********************************************************************************
 ***                   calc_sd10g65_setup_apc                                ***
 ********************************************************************************/
vtss_rc vtss_sd10g65_setup_apc_args_init(vtss_sd10g65_setup_apc_args_t     *const init_val){

    init_val->chip_name       = VTSS_SD10G65_CHIP_ES65XX;
    init_val->is_malibu_f2df_or_df2f = FALSE;
    init_val->f_pll.f_pll_khz = 10e6;
    init_val->f_pll.ratio_num = 66;;
    init_val->f_pll.ratio_den = 64;;
    init_val->if_width        = 32;
    init_val->preset          = VTSS_SD10G65_PRESET_NONE;
    init_val->skip_cal        = FALSE;
    init_val->is_2pt_cal      = FALSE;
    init_val->incl_ld_cal     = FALSE;
    init_val->ib_cal_only     = FALSE;
    init_val->force_eqz_l     = FALSE;
    init_val->force_eqz_l_val = 32;
    init_val->force_eqz_c     = FALSE;
    init_val->force_eqz_c_val = 16;
    init_val->offset_guard    = TRUE;
    init_val->lc_softctrl     = FALSE;
    init_val->throttle_mode   = FALSE;
    init_val->ld_lev_ini      = FALSE;
    init_val->ld_lev_ini_val  = 24;
    init_val->range_sel       = FALSE;
    init_val->range_sel_val   = 20;
    init_val->single_step     = FALSE;
    init_val->invert          = FALSE;

    return VTSS_RC_OK;
} /* vtss_sd10g65_setup_apc_args_init */

vtss_rc vtss_calc_sd10g65_setup_apc(const vtss_sd10g65_setup_apc_args_t config,
                                    vtss_sd10g65_setup_apc_struct_t     *const ret_val ) {

    typedef struct {
        u8  max;
        u8  ini;
        u8  min;
        u8  range_sel;
        u8  chg_mode;
    } vtss_apc_param_set_t;

    typedef enum {
        VTSS_SD10G65_APC_PARAM_OFFS,
        VTSS_SD10G65_APC_PARAM_C,
        VTSS_SD10G65_APC_PARAM_L,
        VTSS_SD10G65_APC_PARAM_AGC,
        VTSS_SD10G65_APC_PARAM_DFE1,
        VTSS_SD10G65_APC_PARAM_DFE2,
        VTSS_SD10G65_APC_PARAM_DFE3,
        VTSS_SD10G65_APC_PARAM_DFE4,
        VTSS_SD10G65_APC_PARAM_LAST,
    } vtss_apc_param_t;

    vtss_rc rc;
    vtss_apc_param_t apc_param = VTSS_SD10G65_APC_PARAM_LAST;
    vtss_sd10g65_apc_preset_struct_t preset;
    vtss_apc_param_set_t apc_set[apc_param];
    vtss_sd10g65_f_pll_t           cfg_f_pll = config.f_pll;
    u32     f_pll_khz_plain, optimize_for_1g = FALSE;
    u8      thresh_init;

    f_pll_khz_plain = (u32) (MEPA_DIV64( ((u64) cfg_f_pll.f_pll_khz * (u64) cfg_f_pll.ratio_num), (u64) cfg_f_pll.ratio_den));
    rc = vtss_sd10g65_apc_set_default_preset_values(config.chip_name, &preset);

    if (cfg_f_pll.f_pll_khz <= 2.5e6 && config.chip_name != VTSS_SD10G65_CHIP_VENICE) {
        optimize_for_1g = TRUE;
        preset.dfe1_max =  68;  // 1G optimization
    }

    if ((config.chip_name != VTSS_SD10G65_CHIP_VENICE_C) &&
        (config.chip_name != VTSS_SD10G65_CHIP_JAGUAR2C) &&
        (config.chip_name != VTSS_SD10G65_CHIP_MALIBU_B)) {
      if ((config.preset == VTSS_SD10G65_ZR_SC) ||
          (config.preset == VTSS_SD10G65_DAC_SC) ||
          (config.preset == VTSS_SD10G65_SR_SC) ||
          (config.preset == VTSS_SD10G65_SR2_SC) ||
          (config.preset == VTSS_SD10G65_KR_SC) ||
          (config.preset == VTSS_SD10G65_BACKPLANE_SC)) {
        VTSS_E("vtss_calc_sd10g65_setup_apc: Smart Control presets are not supported for the current Device");
      }
    }

    switch(config.preset) {
        case VTSS_SD10G65_ATE          : preset.ld_lev_ini =  34;
                                         break;
        case VTSS_SD10G65_ATE_SC       : preset.ld_lev_ini =  34;
                                         preset.lc_smartctrl = 1;
                                         break;
        case VTSS_SD10G65_ZR_HW        : preset.ld_lev_ini =  48;
                                         preset.c_ini      =  11;
                                         preset.l_ini      =  22;
                                         preset.agc_ini    =  88;
                                         preset.dfe1_max   = 127;
                                         break;
        case VTSS_SD10G65_ZR_SW        : preset.c_ini      =  11;
                                         preset.l_ini      =  22;
                                         preset.agc_ini    =  88;
                                         preset.l_max      =  79;
                                         break;
        case VTSS_SD10G65_ZR_SC        : preset.c_ini      =  11;
                                         preset.l_ini      =  22;
                                         preset.agc_ini    =  88;
                                         preset.l_max      =  79;
                                         preset.lc_smartctrl = 1;
                                         break;
        case VTSS_SD10G65_DAC_HW       : preset.ld_lev_ini =   4;
                                         preset.c_min      =   4;
                                         preset.c_ini      =  25;
                                         preset.l_min      =   8;
                                         preset.l_ini      =  50;
                                         preset.agc_max    = 216;
                                         preset.agc_ini    = 168;
                                         preset.dfe1_max   = 127;
                                         break;
        case VTSS_SD10G65_DAC_SW       : preset.ld_lev_ini =   4;
                                         preset.l_max      =  79;
                                         preset.c_ini      =  25;
                                         preset.l_ini      =  50;
                                         preset.agc_ini    = 166;
                                         break;
        case VTSS_SD10G65_DAC_SC       : preset.ld_lev_ini =   4;
                                         preset.c_min      =   4;
                                         preset.c_ini      =  25;
                                         preset.l_max      =  79;
                                         preset.l_min      =   8;
                                         preset.l_ini      =  50;
                                         preset.agc_max    = 216;
                                         preset.agc_ini    = 168;
                                         preset.lc_smartctrl = 1;
                                         break;
        case VTSS_SD10G65_SR_HW        : if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE_C) ||
                                             (config.chip_name == VTSS_SD10G65_CHIP_MALIBU)) {
                                           preset.ld_lev_ini =  44;
                                         } else {
                                           preset.dfe1_max   = 127;
                                         }
                                         break;
        case VTSS_SD10G65_SR_SC        : preset.l_max      =  79;
                                         preset.lc_smartctrl = 1;
                                         break;
        case VTSS_SD10G65_SR2_HW       : preset.dfe1_max   = 127;
                                         break;
        case VTSS_SD10G65_SR2_SC       : preset.l_max      =  79;
                                         preset.lc_smartctrl = 1;
                                         break;
        case VTSS_SD10G65_BACKPLANE    : preset.c_ini      =  25;
                                         preset.c_chg_mode =   1;
                                         preset.l_ini      =  62;
                                         preset.l_chg_mode =   1;
                                         break;
        case VTSS_SD10G65_BACKPLANE_SC : preset.ld_lev_ini =   4;
                                         preset.c_min      =   4;
                                         preset.c_ini      =  25;
                                         preset.l_max      =  79;
                                         preset.l_min      =   8;
                                         preset.l_ini      =  50;
                                         preset.agc_max    = 216;
                                         preset.agc_ini    = 168;
                                         preset.lc_smartctrl = 1;
                                         break;
        case VTSS_SD10G65_B2B          : preset.c_ini      =  10;
                                         preset.c_chg_mode =   1;
                                         preset.l_ini      =  62;
                                         preset.l_chg_mode =   1;
                                         break;
        case VTSS_SD10G65_KR_HW        : preset.ld_lev_ini =   8;
                                         preset.c_ini      =  11;
                                         preset.l_ini      =  44;
                                         preset.agc_ini    =  88;
                                         preset.l_rs_offs  =   1;
                                         preset.l_max      = 124;
                                         preset.dfe1_max   = 127;
                                         break;
        case VTSS_SD10G65_KR_SC        : preset.ld_lev_ini =   4;
                                         preset.c_min      =   4;
                                         preset.c_ini      =  25;
                                         preset.l_min      =   8;
                                         preset.l_ini      =  50;
                                         preset.l_max      =  79;
                                         preset.agc_ini    = 168;
                                         preset.agc_max    = 216;
                                         preset.lc_smartctrl = 1;
                                         break;
        default                        : break;
    }

    // overrider ld_lev_ini / range_sel if requested
    if (config.ld_lev_ini == TRUE) {
        preset.ld_lev_ini = config.ld_lev_ini_val;
    }
    if (config.range_sel == TRUE) {
        preset.range_sel = config.range_sel_val;
    }

    if (config.offset_guard == TRUE &&
        (config.preset != VTSS_SD10G65_KR_HW &&
         config.preset != VTSS_SD10G65_KR_SC )) {
      apc_set[VTSS_SD10G65_APC_PARAM_OFFS].max = 0xA0; // --> 640 (512+128)
      apc_set[VTSS_SD10G65_APC_PARAM_OFFS].ini = 0x80; // --> 512
      apc_set[VTSS_SD10G65_APC_PARAM_OFFS].min = 0x60; // --> 384 (512-128)
    } else {
      apc_set[VTSS_SD10G65_APC_PARAM_OFFS].max =  255; // --> 1020
      apc_set[VTSS_SD10G65_APC_PARAM_OFFS].ini =  128; // -->  512
      apc_set[VTSS_SD10G65_APC_PARAM_OFFS].min =    0; // -->    0
    }

    apc_set[VTSS_SD10G65_APC_PARAM_C].max    =  preset.c_max;
    apc_set[VTSS_SD10G65_APC_PARAM_C].ini    =  preset.c_ini;
    apc_set[VTSS_SD10G65_APC_PARAM_C].min    =  preset.c_min;

    apc_set[VTSS_SD10G65_APC_PARAM_L].max    =  preset.l_max;
    apc_set[VTSS_SD10G65_APC_PARAM_L].ini    =  preset.l_ini;
    apc_set[VTSS_SD10G65_APC_PARAM_L].min    =  preset.l_min;

    apc_set[VTSS_SD10G65_APC_PARAM_AGC].max  =  preset.agc_max;
    apc_set[VTSS_SD10G65_APC_PARAM_AGC].ini  =  preset.agc_ini;
    apc_set[VTSS_SD10G65_APC_PARAM_AGC].min  =  preset.agc_min;

    apc_set[VTSS_SD10G65_APC_PARAM_DFE1].max =  preset.dfe1_max;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE1].ini =  64;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE1].min =  preset.dfe1_min;

    apc_set[VTSS_SD10G65_APC_PARAM_DFE2].max =  optimize_for_1g ? 36 : 48; // 1G optimization
    apc_set[VTSS_SD10G65_APC_PARAM_DFE2].ini =  32;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE2].min =  0;

    apc_set[VTSS_SD10G65_APC_PARAM_DFE3].max =  optimize_for_1g ? 20 : 31; // 1G optimization;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE3].ini =  16;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE3].min =  0;

    apc_set[VTSS_SD10G65_APC_PARAM_DFE4].max =  optimize_for_1g ? 20 : 31; // 1G optimization;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE4].ini =  16;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE4].min =  0;

    if (config.offset_guard == TRUE &&
        (config.preset == VTSS_SD10G65_KR_HW ||
         config.preset == VTSS_SD10G65_KR_SC )) {
      apc_set[VTSS_SD10G65_APC_PARAM_OFFS].range_sel = 12; // as suggested by Stefan Janiszewski for all KR presets
    } else {
      apc_set[VTSS_SD10G65_APC_PARAM_OFFS].range_sel = preset.range_sel;
    }
    apc_set[VTSS_SD10G65_APC_PARAM_C].range_sel    = preset.range_sel + preset.c_rs_offs;
    apc_set[VTSS_SD10G65_APC_PARAM_C].chg_mode     = preset.c_chg_mode;
    apc_set[VTSS_SD10G65_APC_PARAM_L].range_sel    = preset.range_sel + preset.l_rs_offs;
    apc_set[VTSS_SD10G65_APC_PARAM_L].chg_mode     = preset.l_chg_mode;
    apc_set[VTSS_SD10G65_APC_PARAM_AGC].range_sel  = preset.range_sel;

    apc_set[VTSS_SD10G65_APC_PARAM_DFE1].range_sel = preset.range_sel;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE2].range_sel = preset.range_sel;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE3].range_sel = preset.range_sel;
    apc_set[VTSS_SD10G65_APC_PARAM_DFE4].range_sel = preset.range_sel;


    ret_val->apc_common_cfg0__apc_fsm_recover_mode[0]  = 1;
    ret_val->apc_common_cfg0__hml_errcorr_ena[0]       = 0;
    ret_val->apc_common_cfg0__skip_cal[0]              = to_u8_(config.skip_cal);
    ret_val->apc_common_cfg0__if_width[0]              = sd10g65_apc_get_iw_setting(config.if_width);
    ret_val->apc_common_cfg0__reset_apc[0]             = 1;
    ret_val->apc_common_cfg0__apc_direct_ena[0]        = 1;
    ret_val->apc_common_cfg1__offscal_dis_swap[0]      = 1;
    ret_val->apc_ld_cal_cfg__cal_clk_div[0]            = 3;
    /*  clear all skip bits which might be set from previous runs */
    ret_val->apc_is_cal_cfg0__skip_observe_init[0]       = 0;
    ret_val->apc_is_cal_cfg0__skip_offset_init[0]        = 0;
    ret_val->apc_is_cal_cfg0__skip_threshold_init[0]     = 0;
    ret_val->apc_is_cal_cfg0__skip_dfe_buffer_init[0]    = 0;
    ret_val->apc_is_cal_cfg0__skip_observe_cal[0]        = 0;
    ret_val->apc_is_cal_cfg0__skip_offset_cal[0]         = 0;
    ret_val->apc_is_cal_cfg0__skip_threshold_cal[0]      = 0;
    ret_val->apc_is_cal_cfg0__skip_dfe_buffer_cal[0]     = 0;
    ret_val->apc_is_cal_cfg1__par_data_num_ones_thres[0] = config.if_width / 4;
    ret_val->apc_is_cal_cfg1__cal_num_iterations[0]      = 1;


    if (f_pll_khz_plain == 0) {
        VTSS_E("vtss_calc_sd10g65_setup_apc: f_pll not correctly set!\n");
        rc = VTSS_RC_ERROR;
        return rc;
    } else {
        if (config.chip_name != VTSS_SD10G65_CHIP_VENICE) {
            ret_val->calibration_time_ms[0] =   0; // not used at all
            ret_val->calibration_time_ms[1] = (u16) (MEPA_DIV64((((u64)1<<(2*ret_val->apc_ld_cal_cfg__cal_clk_div[0]))*(ret_val->apc_is_cal_cfg1__cal_num_iterations[0]+1)*156500*config.if_width)+(f_pll_khz_plain-1), f_pll_khz_plain));
        } else {
            ret_val->calibration_time_ms[0] =  50;
            ret_val->calibration_time_ms[1] = 200;
        }
    }

    ret_val->apc_eqz_common_cfg__eqz_gain_auto_restart[0] = 0;
    ret_val->ib_cal_only[0]                               = config.ib_cal_only;
    ret_val->apc_eqz_agc_par_cfg__eqz_agc_ini[0]          = apc_set[VTSS_SD10G65_APC_PARAM_AGC].ini;
    ret_val->apc_dfe1_par_cfg__dfe1_ini[0]                = apc_set[VTSS_SD10G65_APC_PARAM_DFE1].ini;
    ret_val->apc_dfe2_par_cfg__dfe2_ini[0]                = apc_set[VTSS_SD10G65_APC_PARAM_DFE2].ini;
    ret_val->apc_dfe3_par_cfg__dfe3_ini[0]                = apc_set[VTSS_SD10G65_APC_PARAM_DFE3].ini;
    ret_val->apc_dfe4_par_cfg__dfe4_ini[0]                = apc_set[VTSS_SD10G65_APC_PARAM_DFE4].ini;
    ret_val->throttle_mode[0]                             = to_u8_(config.throttle_mode);
    ret_val->sd10g65_ib_cfg0__ib_vscope_ena[0]            = 1;    /* CML sampler always active */
    ret_val->apc_parctrl_sync_cfg__fsm1_op_mode[0]        = 1;    /* one-time operation */
    if (config.throttle_mode == TRUE) {
        ret_val->apc_parctrl_fsm1_timer_cfg__fsm1_op_time[0]  = 500;  /* number of active cycles */
    } else {
        ret_val->apc_parctrl_fsm1_timer_cfg__fsm1_op_time[0]  = 50000;  /* number of active cycles */
    }
    ret_val->apc_top_ctrl_cfg__sleep_time[0]              = 4500; /* number of inactive cycles */
    ret_val->apc_common_cfg0__throttle_mode[0]            = 1;    /* enable throttle mode */
    ret_val->single_step[0]                               = to_u8_(config.single_step);
    ret_val->apc_eqz_ld_ctrl__ld_lev_ini[0]               = preset.ld_lev_ini;
    ret_val->apc_eqz_ld_ctrl_cfg0__ld_t_deadtime_wrk[0]   = 65535;
    ret_val->apc_eqz_ld_ctrl_cfg0__ld_t_timeout_wrk[0]    = 1000;
    ret_val->apc_eqz_ld_ctrl_cfg1__ld_t_deadtime_cal[0]   = 65535;
    ret_val->apc_eqz_ld_ctrl_cfg1__ld_t_timeout_cal[0]    = 1000;
    ret_val->apc_eqz_pat_match_cfg0__eqz_c_pat_mask[0]    = 15;
    ret_val->apc_eqz_pat_match_cfg0__eqz_c_pat_match[0]   = 5;
    ret_val->apc_eqz_pat_match_cfg0__eqz_l_pat_mask[0]    = 15;
    ret_val->apc_eqz_pat_match_cfg0__eqz_l_pat_match[0]   = 5;
    ret_val->apc_eqz_pat_match_cfg1__eqz_offs_pat_mask[0] = 7;
    ret_val->apc_eqz_pat_match_cfg1__eqz_offs_pat_match[0]= 2;
    ret_val->apc_eqz_pat_match_cfg1__eqz_agc_pat_mask[0]  = 15;
    ret_val->apc_eqz_pat_match_cfg1__eqz_agc_pat_match[0] = 5;

    /* # OFFS, AGC control be enabled in all modes */
    ret_val->apc_eqz_offs_par_cfg__eqz_offs_chg_mode[0]  = 0;
    ret_val->apc_eqz_offs_par_cfg__eqz_offs_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_OFFS].range_sel;
    ret_val->apc_eqz_offs_par_cfg__eqz_offs_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_OFFS].max;
    ret_val->apc_eqz_offs_par_cfg__eqz_offs_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_OFFS].min;
    ret_val->apc_eqz_offs_par_cfg__eqz_offs_ini[0]       = apc_set[VTSS_SD10G65_APC_PARAM_OFFS].ini;
    ret_val->apc_eqz_offs_ctrl__eqz_offs_sync_mode[0]    = 1;

    ret_val->apc_eqz_agc_par_cfg__eqz_agc_chg_mode[0]  = 0;
    ret_val->apc_eqz_agc_par_cfg__eqz_agc_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_AGC].range_sel;
    ret_val->apc_eqz_agc_par_cfg__eqz_agc_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_AGC].max;
    ret_val->apc_eqz_agc_par_cfg__eqz_agc_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_AGC].min;
    // Note: same assignment as above
    ret_val->apc_eqz_agc_par_cfg__eqz_agc_ini[0]       = apc_set[VTSS_SD10G65_APC_PARAM_AGC].ini;
    ret_val->apc_eqz_agc_ctrl__eqz_agc_sync_mode[0]    = 1;

    /* # In case input data are inverted, the offset control direction has to be inverted as well */
    if (config.invert == TRUE) {
      ret_val->apc_eqz_offs_par_cfg__eqz_offs_dir_sel[0]   = 1;
    } else {
      ret_val->apc_eqz_offs_par_cfg__eqz_offs_dir_sel[0]   = 0;
    }

    if (f_pll_khz_plain > 2500000) {
        ret_val->high_data_rate[0] = 1;
    } else {
        ret_val->high_data_rate[0] = 0;
    }

    /* L anc C control either forced or enabled for higher data rates only */
    ret_val->force_eqz_l[0] = to_u8_(config.force_eqz_l);
    if (config.force_eqz_l == TRUE) {
        /* # force L or C */
        ret_val->apc_eqz_l_par_cfg__eqz_l_chg_mode[0]  = 1; /* use forced values */
        ret_val->apc_eqz_l_par_cfg__eqz_l_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_L].range_sel; /* Not used in this mode */
        ret_val->apc_eqz_l_par_cfg__eqz_l_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_L].max; /* Not used in this mode */
        ret_val->apc_eqz_l_par_cfg__eqz_l_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_L].min; /* Not used in this mode */
        ret_val->apc_eqz_l_par_cfg__eqz_l_ini[0]       = config.force_eqz_l_val;
        ret_val->apc_eqz_l_ctrl__eqz_l_sync_mode[0]    = 0; /* disabled */
    } else if (ret_val->high_data_rate[0] == 1) {
        /* high data rates -> use and ctrl L and C */
        ret_val->apc_eqz_l_par_cfg__eqz_l_chg_mode[0]  = apc_set[VTSS_SD10G65_APC_PARAM_L].chg_mode; /* control parameter */
        ret_val->apc_eqz_l_par_cfg__eqz_l_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_L].range_sel;
        ret_val->apc_eqz_l_par_cfg__eqz_l_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_L].max;
        ret_val->apc_eqz_l_par_cfg__eqz_l_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_L].min;
        ret_val->apc_eqz_l_par_cfg__eqz_l_ini[0]       = apc_set[VTSS_SD10G65_APC_PARAM_L].ini;
        if ((config.lc_softctrl == TRUE) || (preset.lc_smartctrl == 1)) {
            /* start LC softctrl with known initial values */
            ret_val->apc_eqz_l_ctrl__eqz_l_sync_mode[0]    = 0; /* disabled */
        } else {
            ret_val->apc_eqz_l_ctrl__eqz_l_sync_mode[0]    = 1;
        }
    } else {
        /* low data rates -> force L and C to 0 */
        ret_val->apc_eqz_l_par_cfg__eqz_l_chg_mode[0]  = 1; /* use forced values */
        ret_val->apc_eqz_l_par_cfg__eqz_l_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_L].range_sel; /* Not used in this mode */
        ret_val->apc_eqz_l_par_cfg__eqz_l_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_L].max; /* Not used in this mode */
        ret_val->apc_eqz_l_par_cfg__eqz_l_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_L].min; /* Not used in this mode */
        ret_val->apc_eqz_l_par_cfg__eqz_l_ini[0]       = 0; /* lowest value */
        ret_val->apc_eqz_l_ctrl__eqz_l_sync_mode[0]    = 0; /* disabled */
    }

    ret_val->force_eqz_c[0] = to_u8_(config.force_eqz_c);
    if (config.force_eqz_c == TRUE) {
        /* # force L or C */
        ret_val->apc_eqz_c_par_cfg__eqz_c_chg_mode[0]  = 1; /* use forced values */
        ret_val->apc_eqz_c_par_cfg__eqz_c_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_C].range_sel; /* Not used in this mode */
        ret_val->apc_eqz_c_par_cfg__eqz_c_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_C].max; /* Not used in this mode */
        ret_val->apc_eqz_c_par_cfg__eqz_c_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_C].min; /* Not used in this mode */
        ret_val->apc_eqz_c_par_cfg__eqz_c_ini[0]       = config.force_eqz_c_val;
        ret_val->apc_eqz_c_ctrl__eqz_c_sync_mode[0]    = 0; /* disabled */
    } else if (ret_val->high_data_rate[0] == 1) {
        /* high data rates -> use and ctrl L and C */
        ret_val->apc_eqz_c_par_cfg__eqz_c_chg_mode[0]  = apc_set[VTSS_SD10G65_APC_PARAM_C].chg_mode; /* control parameter */
        ret_val->apc_eqz_c_par_cfg__eqz_c_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_C].range_sel;
        ret_val->apc_eqz_c_par_cfg__eqz_c_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_C].max;
        ret_val->apc_eqz_c_par_cfg__eqz_c_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_C].min;
        ret_val->apc_eqz_c_par_cfg__eqz_c_ini[0]       = apc_set[VTSS_SD10G65_APC_PARAM_C].ini;
        if ((config.lc_softctrl == TRUE) || (preset.lc_smartctrl == 1)) {
            /* start LC softctrl with known initial values */
            ret_val->apc_eqz_c_ctrl__eqz_c_sync_mode[0]    = 0; /* disabled */
        } else {
            ret_val->apc_eqz_c_ctrl__eqz_c_sync_mode[0]    = 1;
        }
    } else {
        /* low data rates -> force L and C to 0 */
        ret_val->apc_eqz_c_par_cfg__eqz_c_chg_mode[0]  = 1; /* use forced values */
        ret_val->apc_eqz_c_par_cfg__eqz_c_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_C].range_sel; /* Not used in this mode */
        ret_val->apc_eqz_c_par_cfg__eqz_c_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_C].max; /* Not used in this mode */
        ret_val->apc_eqz_c_par_cfg__eqz_c_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_C].min; /* Not used in this mode */
        ret_val->apc_eqz_c_par_cfg__eqz_c_ini[0]       = 0; /* lowest value */
        ret_val->apc_eqz_c_ctrl__eqz_c_sync_mode[0]    = 0; /* disabled */
    }

    ret_val->apc_dfe1_par_cfg__dfe1_chg_mode[0]  = 0;
    ret_val->apc_dfe1_par_cfg__dfe1_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_DFE1].range_sel;
    ret_val->apc_dfe1_par_cfg__dfe1_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE1].max;
    ret_val->apc_dfe1_par_cfg__dfe1_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE1].min;
    // Note: same assignment as above
    ret_val->apc_dfe1_par_cfg__dfe1_ini[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE1].ini;
    ret_val->apc_dfe1_ctrl__dfe1_sync_mode[0]    = 1;

    ret_val->apc_dfe2_par_cfg__dfe2_chg_mode[0]  = 0;
    ret_val->apc_dfe2_par_cfg__dfe2_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_DFE2].range_sel;
    ret_val->apc_dfe2_par_cfg__dfe2_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE2].max;
    ret_val->apc_dfe2_par_cfg__dfe2_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE2].min;
    // Note: same assignment as above
    ret_val->apc_dfe2_par_cfg__dfe2_ini[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE2].ini;
    ret_val->apc_dfe2_ctrl__dfe2_sync_mode[0]    = 1;

    ret_val->apc_dfe3_par_cfg__dfe3_chg_mode[0]  = 0;
    ret_val->apc_dfe3_par_cfg__dfe3_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_DFE3].range_sel;
    ret_val->apc_dfe3_par_cfg__dfe3_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE3].max;
    ret_val->apc_dfe3_par_cfg__dfe3_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE3].min;
    // Note: same assignment as above
    ret_val->apc_dfe3_par_cfg__dfe3_ini[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE3].ini;
    ret_val->apc_dfe3_ctrl__dfe3_sync_mode[0]    = 1;

    ret_val->apc_dfe4_par_cfg__dfe4_chg_mode[0]  = 0;
    ret_val->apc_dfe4_par_cfg__dfe4_range_sel[0] = apc_set[VTSS_SD10G65_APC_PARAM_DFE4].range_sel;
    ret_val->apc_dfe4_par_cfg__dfe4_max[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE4].max;
    ret_val->apc_dfe4_par_cfg__dfe4_min[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE4].min;
    // Note: same assignment as above
    ret_val->apc_dfe4_par_cfg__dfe4_ini[0]       = apc_set[VTSS_SD10G65_APC_PARAM_DFE4].ini;
    ret_val->apc_dfe4_ctrl__dfe4_sync_mode[0]    = 1;

    /* gain setting */
    ret_val->apc_eqz_gain_ctrl_cfg__eqz_gain_ini[0]         = preset.gain_ini;
    ret_val->apc_eqz_gain_adj_ctrl_cfg__eqz_gain_adj_ini[0] = preset.gain_adj_ini;
    ret_val->apc_eqz_common_cfg__eqz_gain_chg_mode[0]       = preset.gain_chg_mode;

    /* do calibration if desired */
    ret_val->skip_cal[0]    = to_u8_(config.skip_cal);
    ret_val->is_2pt_cal[0]  = to_u8_(config.is_2pt_cal);
    ret_val->incl_ld_cal[0] = to_u8_(config.incl_ld_cal);

    thresh_init = 31;
    ret_val->sd10g65_ib_cfg8__ib_inv_thr_cal_val[0] = 0;
    ret_val->apc_is_cal_cfg0__cpmd_thres_init[0]    = thresh_init; /* to be optimized (default 0) */
    ret_val->apc_is_cal_cfg0__vsc_thres_init[0]     = thresh_init; /* to be optimized (default 0) */
    ret_val->apc_is_cal_cfg0__skip_threshold_cal[1] = 1;
    ret_val->apc_is_cal_cfg1__cal_vsc_offset_tgt[0] = 1;

    ret_val->sd10g65_ib_cfg0__ib_dfe_ena[0]         = 0; /* disable dfe stage */
    ret_val->sd10g65_des_cfg0__des_inv_x[0]         = 0; /* disable inversion for IB cal */
    if (config.incl_ld_cal == TRUE) {
      ret_val->apc_common_cfg0__apc_mode[0]           = 5; /* automatic mode for full ib_cal */
    } else {
      ret_val->apc_common_cfg0__apc_mode[0]           = 1; /* manual mode for manual ib_cal */
    }
    ret_val->apc_common_cfg0__reset_apc[1]          = 0; /* reset release */

    ret_val->sd10g65_ib_cfg0__ib_dfe_ena[1]         = 1; /* restore dfe stage */
    if (config.invert == TRUE) {
      ret_val->sd10g65_des_cfg0__des_inv_x[1]         = 1; /* enable inversion when intended */
    } else {
      ret_val->sd10g65_des_cfg0__des_inv_x[1]         = 0; /* no inversion intended */
    }
    ret_val->apc_common_cfg0__apc_mode[1]           = 0; /* disable apc */
    ret_val->apc_common_cfg0__apc_direct_ena[1]     = 0;
    /*  calibration done */

    ret_val->apc_is_cal_cfg0__skip_observe_init[1]       = 1;
    ret_val->apc_is_cal_cfg0__skip_offset_init[1]        = 1;
    ret_val->apc_is_cal_cfg0__skip_threshold_init[1]     = 1;
    ret_val->apc_is_cal_cfg0__skip_dfe_buffer_init[1]    = 1;
    ret_val->apc_is_cal_cfg0__skip_observe_cal[1]        = 1;
    ret_val->apc_is_cal_cfg0__skip_offset_cal[1]         = 1;
    ret_val->apc_is_cal_cfg0__skip_threshold_cal[2]      = 1;
    ret_val->apc_is_cal_cfg0__skip_dfe_buffer_cal[1]     = 1;
    ret_val->apc_common_cfg0__skip_cal[1]                = 1;

    if (config.single_step == TRUE) {
      ret_val->apc_common_cfg0__apc_mode[2]           = 1; /* manual_mode */
    } else {
      ret_val->apc_common_cfg0__apc_mode[2]           = 2; /* apc full operation (fsm1) */
    }
    ret_val->apc_common_cfg0__reset_apc[2]            = 0;

    /* in case LC softctrl shall be launched, do this now... (SW version only for f_pll>2.5G) */
    /* Not really in the API as it is not supported by UTE becaus it requires read_modify write and othe complex methods */
    /* Latest devices however have this algorithm brought to HW (a.k.a. lc_smartctrl, the "_SC" in the presets and this will be configured now */
    ret_val->lc_smartctrl[0] = preset.lc_smartctrl;
    ret_val->apc_lc_softctrl_cfg1__lc_sc_dfe2_target[0]   =  32;
    ret_val->apc_lc_softctrl_cfg1__lc_sc_dfe1_target[0]   =  63;
    ret_val->apc_lc_softctrl_cfg__lc_sc_timer[0]          =  10;
    ret_val->apc_lc_softctrl_cfg__lc_sc_avgshft[0]        =   6;
    ret_val->apc_lc_softctrl_cfg__lc_sc_dfe1_threshold[0] =   8;   /* 8=default   */
    ret_val->apc_lc_softctrl_cfg__lc_sc_dfe2_threshold[0] =   4;   /* 4=default   */
    ret_val->apc_lc_softctrl_cfg__lc_sc_agc_threshold[0]  = 125;   /* 125=default */
    ret_val->apc_lc_softctrl_cfg__lc_sc_div_c_sel[0]      =   1;
    ret_val->apc_lc_softctrl_cfg__lc_sc_div_l[0]          =   4;   /* 4=default   */
    ret_val->apc_lc_softctrl_cfg__lc_sc_div_c[0]          =   4;   /* 4=default   */
    ret_val->apc_lc_softctrl_cfg__lc_sc_mode[0]           = preset.lc_smartctrl;


    return rc;

} /* vtss_calc_sd10g65_setup_apc */

/* ******************************************************************************** */
/* ***                        E N D   O F    F I L E                            *** */
/* ******************************************************************************** */
