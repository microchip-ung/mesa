// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/*---------------------------------------------------------------------------
 * $HeadURL: svn://svn-de.vitesse.com/svn-de/vtslibs/vts_ute_tcllib/tags/UTE_release_vts_ute_tcllib_20180312_trunk_bjo/api_c/vtss_sd10g65_procs.c $
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

static u8 to_u8_(const BOOL in) {
    if (in == TRUE) {
        return 1;
    } else {
        return 0;
    }
}

vtss_rc vtss_sd10g65_get_f_pll_from_f_mode(vtss_f_mode_t        f_mode,
                                           vtss_sd10g65_f_pll_t *const ret_val) {

    switch(f_mode) {
        case VTSS_SD10G65_MODE_10G_ETH :
        case VTSS_SD10G65_MODE_10G_LAN : {
            // 10.3125Gbps
            ret_val->f_pll_khz = 10e6;
            ret_val->ratio_num = 66;
            ret_val->ratio_den = 64;
            break;
        }
        case VTSS_SD10G65_MODE_WAN :
        case VTSS_SD10G65_MODE_10G_WAN : {
            // 9.95328Gbps
            ret_val->f_pll_khz = 10e6;
            ret_val->ratio_num = 248832;
            ret_val->ratio_den = 250000;
            break;
        }
        case VTSS_SD10G65_MODE_OTU2 : {
            // ~10.70923Gbps
            ret_val->f_pll_khz = 10e6;
            ret_val->ratio_num = 248832 * 255;
            ret_val->ratio_den = 250000 * 237;
            break;
        }
        case VTSS_SD10G65_MODE_OTU1e : {
            // ~11.0491Gbps
            ret_val->f_pll_khz = 10e6;
            ret_val->ratio_num = 66 * 255;
            ret_val->ratio_den = 64 * 238;
            break;
        }
        case VTSS_SD10G65_MODE_OTU2e : {
            // ~11.0957Gbps
            ret_val->f_pll_khz = 10e6;
            ret_val->ratio_num = 66 * 255;
            ret_val->ratio_den = 64 * 237;
            break;
        }
        case VTSS_SD10G65_MODE_FX100 :
        case VTSS_SD10G65_MODE_SGMII :
        case VTSS_SD10G65_MODE_1G_LAN : {
            // ~1.25Gbps
            ret_val->f_pll_khz = 1e6;
            ret_val->ratio_num = 10;
            ret_val->ratio_den = 8;
            break;
        }
         default        : {
            VTSS_E("invalid parameter value for f_mode\n");
            // 10.3125Gbps
            ret_val->f_pll_khz = 10e6;
            ret_val->ratio_num = 66;
            ret_val->ratio_den = 64;
            break;
            return VTSS_RC_ERROR;
         }
    }
    return VTSS_RC_OK;
}

/* function to calculate the greatest common divisor using the euclidean algorithm */
static u64  sd10g65_calc_gcd(const u64 num_in,
                             const u64 div_in) {
    u64 rem;
    u64 num;
    u64 div;

    rem = MEPA_MOD64(num_in, div_in);
    div = div_in;
    while (rem != 0) {
        num = div;
        div = rem;
        rem = MEPA_MOD64(num, div);
    }
    return div;
}

static vtss_rc sd10g65_synth_settings_calc (u64 num_in,
                                            u64 div_in,
                                            vtss_sd10g65_synth_settings_calc_rslt_t *const ret_val) {

    u64 numerator;
    u64 freqm;
    u64 freqn;
    u64 gcd;

    ret_val->freq_mult = (u16)MEPA_DIV64((u64)8192 * num_in, div_in);
    /* check what was cut by the above formula */
    numerator = ((u64)8192 * num_in) - (ret_val->freq_mult * div_in);

    if (numerator == 0) {
        freqm = 0;
        freqn = (u64)1 << 35;
    } else {
        /* calculate common divisor */
        gcd = sd10g65_calc_gcd(numerator, div_in);

        /* and cancel out numerator and divisor with the gcd */
        freqm = MEPA_DIV64(numerator, gcd);
        freqn = MEPA_DIV64(div_in, gcd);

        /* choose largest possible values to keep adaption time low;              */
        /* a 4G mode, that reqiured a 0.6 it showed, that the adaption time took  */
        /* several seconds when choosing 3 / 5 to get 0.6                         */
        /* SD error integ running at 312MHz takes ~32 seconds to reach zero.      */
        /* starting @~-2^35 when numerator is 3                                   */
        while (freqn < ((u64)1 << 35)) {
            freqm = ( freqm << 1 );
            freqn = ( freqn << 1 );
        }
    }
    ret_val->synth_freqm = freqm;
    ret_val->synth_freqn = freqn;
    return VTSS_RC_OK;;
}

static inline u16 sd10g65_tri_dec(u16 val_in)
{
    switch (val_in) {
    case 0: {return 6; break;}
    case 1: {return 7; break;}
    case 2: {return 4; break;}
    case 3: {return 0; break;}
    default: VTSS_E("sd10g65_tri_dec discovered invalid input value %d\n", val_in);
    }
    return 0;
}

static inline u16 sd10g65_bi_dec(u16 val_in)
{
    switch (val_in) {
    case 0: {return 3; break;}
    case 1: {return 1; break;}
    default: VTSS_E("sd10g65_bi_dec discovered invalid input value %d\n", val_in);
    }
    return 0;
}

static inline u16 sd10g65_lt_dec(u16 val_in)
{
    switch (val_in) {
    case 0: {return 0; break;}
    case 1: {return 6; break;}
    case 2: {return 5; break;}
    case 3: {return 4; break;}
    default: VTSS_E("sd10g65_lt_dec discovered invalid input value %d\n", val_in);
    }
    return 0;
}

static inline u16 sd10g65_ls_dec(u16 val_in)
{
    switch (val_in) {
    case 0: {return  8; break;}
    case 1: {return 10; break;}
    case 2: {return 12; break;}
    case 3: {return 14; break;}
    case 4: {return  7; break;}
    case 5: {return  5; break;}
    case 6: {return  3; break;}
    case 7: {return  1; break;}
    default: VTSS_E("sd10g65_ls_dec discovered invalid input value %d\n", val_in);
    }
    return 0;
}

static vtss_rc sd10g65_calc_frec_dec_bypass(const u16  freq_mult_in,
                                            vtss_sd10g65_freq_dec_bypass_rslt_t *const ret_val)
{

    u16 freq_sign;
    u16 freq_abs;
    u16 tri_2g5;
    u16 tri_625m;
    u16 tri_156m;
    u16 bi_39m;
    u16 tri_20m;
    u16 ls_5m;

    u16 ena_2g5_dec;
    u16 dir_2g5_dec;
    u16 spd_2g5_dec;

    u16 ena_625m_dec;
    u16 dir_625m_dec;
    u16 spd_625m_dec;

    u16 ena_156m_dec;
    u16 dir_156m_dec;
    u16 spd_156m_dec;

    u16 ena_39m_dec;
    u16 dir_39m_dec;

    u16 ena_20m_dec;
    u16 dir_20m_pre;
    u16 spd_20m_dec;

    u16 dir_5m_pre;
    u16 ena_2m5_dec;
    u16 ena_1m25_dec;
    u16 inv_sd_dec;

    u16 dir_ls_dec;
    u16 dir_20m_dec;

    freq_sign    = freq_mult_in >> 13;
    freq_abs     = (freq_sign == 1) ? (freq_mult_in & 0xfff) : (~freq_mult_in & 0xfff);

    tri_2g5      = sd10g65_tri_dec(((freq_abs - 684) >> 10) & 0x3);
    tri_625m     = sd10g65_tri_dec(((freq_abs - 172) >>  8) & 0x3);
    tri_156m     = sd10g65_tri_dec(((freq_abs -  44) >>  6) & 0x3);
    bi_39m       =  sd10g65_bi_dec(((freq_abs -  12) >>  5) & 0x1);
    tri_20m      =  sd10g65_lt_dec(((freq_abs +   4) >>  3) & 0x3);
    ls_5m        =  sd10g65_ls_dec(((freq_abs -   0) >>  0) & 0x7);

    ena_2g5_dec  =   ((tri_2g5  >> 2)                & 1);
    dir_2g5_dec  =  (((tri_2g5  >> 1) ^  ~freq_sign) & 1);
    spd_2g5_dec  =   ((tri_2g5  >> 0)                & 1);

    ena_625m_dec =   ((tri_625m >> 2)                & 1);
    dir_625m_dec =  (((tri_625m >> 1) ^  ~freq_sign) & 1);
    spd_625m_dec =   ((tri_625m >> 0)                & 1);

    ena_156m_dec =   ((tri_156m >> 2)                & 1);
    dir_156m_dec =  (((tri_156m >> 1) ^  ~freq_sign) & 1);
    spd_156m_dec =   ((tri_156m >> 0)                & 1);

    ena_39m_dec  =   ((bi_39m   >> 1)                & 1);
    dir_39m_dec  =  (((bi_39m   >> 0) ^  ~freq_sign) & 1);

    ena_20m_dec  =   ((tri_20m  >> 2)                & 1);
    dir_20m_pre  =  (((tri_20m  >> 1) ^  ~freq_sign) & 1);
    spd_20m_dec  =   ((tri_20m  >> 0)                & 1);

    dir_5m_pre   =  (((ls_5m    >> 3) ^  ~freq_sign) & 1);
    ena_2m5_dec  =   ((ls_5m    >> 2)                & 1);
    ena_1m25_dec =   ((ls_5m    >> 1)                & 1);
    inv_sd_dec   =  (((ls_5m    >> 0) ^  ~freq_sign) & 1);

    dir_ls_dec   =   dir_5m_pre;
    dir_20m_dec  =  (dir_20m_pre      ^ ~dir_5m_pre) & 1;

    ret_val->freq_mult_hi = ((ena_2g5_dec  <<  3) |
                             (dir_2g5_dec  <<  2) |
                             (spd_2g5_dec  <<  1) |
                             (ena_625m_dec <<  0)) ^ 0x4;

    ret_val->freq_mult = ((dir_625m_dec << 13) |
                          (spd_625m_dec << 12) |
                          (ena_156m_dec << 11) |
                          (dir_156m_dec << 10) |
                          (spd_156m_dec <<  9) |
                          (ena_39m_dec  <<  8) |
                          (dir_39m_dec  <<  7) |
                          (dir_ls_dec   <<  6) |
                          (ena_20m_dec  <<  5) |
                          (dir_20m_dec  <<  4) |
                          (spd_20m_dec  <<  3) |
                          (ena_2m5_dec  <<  2) |
                          (ena_1m25_dec <<  1) |
                          (inv_sd_dec   <<  0)) ^ 0x24D0;

    return VTSS_RC_OK;
}


static vtss_rc sd10g65_synth_mult_calc(vtss_sd10g65_f_pll_t f_pll_in,
                                       vtss_chip_name_t     chip_name,
                                       vtss_sd10g65_synth_mult_calc_rslt_t *const ret_val) {

    vtss_sd10g65_synth_settings_calc_rslt_t synth_settings;
    vtss_sd10g65_freq_dec_bypass_rslt_t     bypass_settings;
    u64 num_in_tmp;
    u64 div_in_tmp;
    u64 dr_khz;
    u16 mult_sy;

    vtss_rc rc;

    /* initialize */
    rc = VTSS_RC_OK;
    ret_val->synth_speed_sel       = 0;
    ret_val->synth_fbdiv_sel       = 0;
    ret_val->synth_freqm_0         = 0;
    ret_val->synth_freqn_0         = 0;
    ret_val->synth_freqm_1         = 0;
    ret_val->synth_freqn_1         = 0;
    ret_val->synth_freq_mult_byp   = 0;
    ret_val->synth_freq_mult_hi    = 0;
    ret_val->synth_freq_mult       = 0;
    ret_val->tx_synth_ls_speed     = 0;
    ret_val->tx_synth_cs_speed     = 0;
    ret_val->rx_synth_fb_step      = 0;
    ret_val->rx_synth_i2_step      = 0;

    num_in_tmp = (u64)f_pll_in.f_pll_khz * (u64)f_pll_in.ratio_num;
    div_in_tmp = (u64)f_pll_in.ratio_den * 2500000;

    dr_khz = MEPA_DIV64((u64)f_pll_in.f_pll_khz * (u64)f_pll_in.ratio_num, (u64)f_pll_in.ratio_den);

    if (dr_khz < ((u64) 2.5e6 * 2/3)) {
        VTSS_E("Target frequency to small. Target frequency for the synthesizer must be 2/3 * 2.5 GHz <= f <= 4/3 * 10Ghz\n");
        return VTSS_RC_ERROR;
    } else if (dr_khz > ((u64) 2.5e6 * 16/3)) {
        VTSS_E("Target frequency to high. Target frequency for the synthesizer must be 2/3 * 2.5 GHz <= f <= 4/3 * 10Ghz\n");
        return VTSS_RC_ERROR;
    } else {
        if (dr_khz < ((u64) 2.5e6 * 4/3)) {
            /* sample frequncy below 3.33GHz -> use 2/3 * 2G5 .. 4/3 * 2G5 */
            rc |= sd10g65_synth_settings_calc(num_in_tmp, (u64)div_in_tmp, &synth_settings);
            ret_val->synth_fbdiv_sel = 0;

            ret_val->tx_synth_ls_speed = 0;
            ret_val->tx_synth_cs_speed = 0;
            ret_val->rx_synth_fb_step  = 3;
            ret_val->rx_synth_i2_step  = 0;
        } else if(dr_khz < ((u64) 2.5e6 * 8/3)) {
            /* sample frequncy between 3.33GHz and 6.66Ghz -> use 2/3 * 5G .. 4/3 * 5G */
            rc |= sd10g65_synth_settings_calc(num_in_tmp, (u64)2*div_in_tmp, &synth_settings);
            ret_val->synth_fbdiv_sel = 1;

            ret_val->tx_synth_ls_speed = 0;
            ret_val->tx_synth_cs_speed = 1;
            ret_val->rx_synth_fb_step  = 2;
            ret_val->rx_synth_i2_step  = 0;
        } else  {
            /* sample frequncy between 6.66GHz and 13.33Ghz -> use 2/3 *10G .. 4/3 * 5G */
            rc |= sd10g65_synth_settings_calc(num_in_tmp, (u64)4*div_in_tmp, &synth_settings);
            ret_val->synth_fbdiv_sel = 2;

            ret_val->tx_synth_ls_speed = 1;
            ret_val->tx_synth_cs_speed = 1;
            ret_val->rx_synth_fb_step  = 0;
            ret_val->rx_synth_i2_step  = 0;
        }
        if (dr_khz < ((u64) 5e6)) {
            /* sample frequncy < 5 GHz */
            ret_val->synth_speed_sel = 1;
        } else {
            ret_val->synth_speed_sel = 0;
        }
        mult_sy = synth_settings.freq_mult;
        ret_val->synth_freqm_0 = (u32)(synth_settings.synth_freqm & 0xffffffff);
        ret_val->synth_freqn_0 = (u32)(synth_settings.synth_freqn & 0xffffffff);
        ret_val->synth_freqm_1 = (u8)(synth_settings.synth_freqm >> 32);
        ret_val->synth_freqn_1 = (u8)(synth_settings.synth_freqn >> 32);

        if ((chip_name == VTSS_SD10G65_CHIP_ES6514) ||
            (chip_name == VTSS_SD10G65_CHIP_JAGUAR2) ||
            (chip_name == VTSS_SD10G65_CHIP_JAGUAR2C) ||
            (chip_name == VTSS_SD10G65_CHIP_VENICE) ||
            (chip_name == VTSS_SD10G65_CHIP_VENICE_C) ||
            (chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
            (chip_name == VTSS_SD10G65_CHIP_MALIBU_B) ||
            (chip_name == VTSS_SD10G65_CHIP_SERVALT) ||
            (chip_name == VTSS_SD10G65_CHIP_ROLEX)) {
            // freq_dec has a flaw; using SW decoding and bypass mode;
            // decoding is translated from reworked verilog code
            //
            // calculating with the absolute value of the difference to multiplication with one
            // the complement is one's complement; the "+1" for the two's complement is the " ^ ~freq_sign" for the inv_sd_dec calculation
            // the "sign" is 1 for "positive" and 0 for "negative" directions
            ret_val->synth_freq_mult_byp = 1;
            rc |= sd10g65_calc_frec_dec_bypass(mult_sy, &bypass_settings);
            ret_val->synth_freq_mult_hi  = bypass_settings.freq_mult_hi;
            ret_val->synth_freq_mult     = bypass_settings.freq_mult;
        } else {
            ret_val->synth_freq_mult_byp = 0;
            ret_val->synth_freq_mult_hi  = 4;
            ret_val->synth_freq_mult     = mult_sy;
        }
    }
    return rc;
}


/* function to map from SD10G65 interface width to configuration value */
static u8   sd10g65_get_iw_setting(const u8     interface_width) {
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

vtss_rc vtss_sd10g65_setup_tx_args_init (vtss_sd10g65_setup_tx_args_t     *const init_val) {

    init_val->chip_name        = VTSS_SD10G65_CHIP_ES65XX;
    init_val->f_pll.f_pll_khz  = 10e6;
    init_val->f_pll.ratio_num  = 66;
    init_val->f_pll.ratio_den  = 64;
    init_val->f_mode           = VTSS_SD10G65_MODE_NONE;
    init_val->if_width         = 32;
    init_val->no_pwrcycle      = FALSE;
    init_val->ls_ena           = FALSE;
    init_val->i2_fsel          = 35;
    init_val->inp_loop         = FALSE;
    init_val->pad_loop         = FALSE;
    init_val->incr_levn        = 1;
    init_val->ob_levn          = 7;
    init_val->mute             = FALSE;
    init_val->invert           = FALSE;

    return VTSS_RC_OK;
}

static vtss_rc vtss_sd10g65_set_default_preset_values (vtss_sd10g65_preset_struct_t *const preset) {


    // Set default preset values
    preset->synth_phase_data   =  54;
    preset->ib_main_thres_offs =  0;
    preset->ib_vscope_hl_offs  =  8;
    preset->ib_bias_adj        =  31;
    preset->ib_sam_offs_adj    =  16;
    preset->ib_eq_ld1_offset   =  0;
    preset->ib_eqz_l_mode      =  0;
    preset->ib_eqz_c_mode      =  0;
    preset->ib_dfe_gain_adj    =  63;
    preset->ib_rib_adj         =  0;
    preset->ib_tc_eq           =  12;
    preset->ib_tc_dfe          =  12;
    preset->ib_ena_400_inp     =  0;
    preset->pll_vreg18         =  10;
    preset->pll_vco_cur        =  7;
    preset->ib_sig_sel         =  0;
    preset->ib_eqz_c_adj       =  0;
    preset->synth_dv_ctrl_i1e  =  0;

    return VTSS_RC_OK;
}

static vtss_rc setup_loop_cfg (const vtss_chip_name_t chip_name,
                                               const BOOL  inp_loop,
                                               const BOOL  pad_loop,
                                               const BOOL  cmos_loop,
                                               const u8    ib_sig_sel,
                                               vtss_sd10g65_loop_cfg_t *const loop_cfg ) {
    vtss_rc rslt;

    rslt = VTSS_RC_OK;

    if(inp_loop == TRUE) {
        if((pad_loop == TRUE) || (cmos_loop== TRUE)) {
            VTSS_E("sd10g65_setup_rx: -inp_loop, -pad_loop and -cmos_loop are exclusive, use only one at a time!");
            rslt = VTSS_RC_ERROR;
            return rslt;
        }
        // # loop data RX-PAD to int. bidi-loop "input loop"
        loop_cfg->en_inp_loop       = 1;
        loop_cfg->en_pad_loop       = 0;
        loop_cfg->sig_sel           = ib_sig_sel;
        loop_cfg->sbus_spare_pool   = 0;
        loop_cfg->sbus_loopdrv_ena  = 0;
    } else if(pad_loop == TRUE) {
        if(cmos_loop == TRUE) {
            VTSS_E("sd10g65_setup_rx: -inp_loop, -pad_loop and -cmos_loop are exclusive, use only one at a time!");
            rslt = VTSS_RC_ERROR;
            return rslt;
        }
        // # loop data from int. bidi-loop to core "pad loop"
        loop_cfg->en_inp_loop      = 0;
        loop_cfg->en_pad_loop      = 1;
        loop_cfg->sig_sel          = 2; // # loop driver
        loop_cfg->sbus_spare_pool  = 0;
        loop_cfg->sbus_loopdrv_ena = 0;
    } else if(cmos_loop == TRUE) {
        // # loop data from cmos input from core into IB "pad loop"
        // # same as pad loop, but also set sbus_spare_pool(1), all other bits '0'
        loop_cfg->en_inp_loop     = 0;
        loop_cfg->en_pad_loop     = 1;
        loop_cfg->sig_sel         = 2; // # loop driver
        loop_cfg->sbus_spare_pool = 2;
        if(chip_name == VTSS_SD10G65_CHIP_ROLEX    ||
           chip_name == VTSS_SD10G65_CHIP_VENICE   ||
           chip_name == VTSS_SD10G65_CHIP_VENICE_C) {
             loop_cfg->sbus_loopdrv_ena = 1;
         } else {
             loop_cfg->sbus_loopdrv_ena = 0;
         }
    } else {
        // # disable loop
        loop_cfg->en_inp_loop      = 0;
        loop_cfg->en_pad_loop      = 0;
        loop_cfg->sig_sel          = ib_sig_sel;
        loop_cfg->sbus_spare_pool  = 0;
        loop_cfg->sbus_loopdrv_ena = 0;
    }

    return rslt;
}

/********************************************************************************
 ********************************************************************************
 ***     M A I N   F U N C T I O N S                                          ***
 ********************************************************************************
 ********************************************************************************/



/********************************************************************************
 ***                   vtss_calc_sd10g65_setup_tx                                  ***
 ********************************************************************************/
vtss_rc vtss_calc_sd10g65_setup_tx(const vtss_sd10g65_setup_tx_args_t config,
                                   vtss_sd10g65_setup_tx_struct_t     *const ret_val) {

    vtss_rc               rslt;
    vtss_sd10g65_f_pll_t           cfg_f_pll = config.f_pll;

    vtss_sd10g65_synth_mult_calc_rslt_t  synth_mult_calc_rslt;
    u32     f_pll_khz_plain;
    u8      half_rate_mode;

    u8      ifw_tmp;
    u8      tog_cnt;
    const u8 hrate_toggle_cnt = 2;

    rslt = VTSS_RC_OK;
    if (config.f_mode != VTSS_SD10G65_MODE_NONE) {
        rslt = vtss_sd10g65_get_f_pll_from_f_mode(config.f_mode, &cfg_f_pll);
    }

    f_pll_khz_plain = (u32) (MEPA_DIV64( ((u64) cfg_f_pll.f_pll_khz * (u64) cfg_f_pll.ratio_num), (u64) cfg_f_pll.ratio_den));
    if (f_pll_khz_plain < 2500000) {
        half_rate_mode = 1;
        f_pll_khz_plain = f_pll_khz_plain * 2;
        cfg_f_pll.f_pll_khz = cfg_f_pll.f_pll_khz * 2;
    } else {
        half_rate_mode = 0;
    }

    if ((config.no_pwrcycle == 0) &&
        ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
         (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
         (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B))) {
        ret_val->pwrcycle[0] = 1;
    } else {
        ret_val->pwrcycle[0] = 0;
    }

    ret_val->f_pll_khz_plain[0] = f_pll_khz_plain;
    ret_val->f_pll_f_pll_khz[0] = cfg_f_pll.f_pll_khz;
    ret_val->f_pll_ratio_num[0] = cfg_f_pll.ratio_num;
    ret_val->f_pll_ratio_den[0] = cfg_f_pll.ratio_den;

    ret_val->tx_synth_cfg0__synth_ena[0]          = 0;
    ret_val->tx_rcpll_cfg2__pll_ena[0]            = 0;
    ret_val->ob_cfg0__en_ob[0]                    = 0;
    ret_val->sbus_tx_cfg__sbus_bias_en[0]         = 1;
    ret_val->sbus_tx_cfg__sbus_bias_speed_sel[0]  = 3;
    ret_val->sbus_rx_cfg__sbus_bias_en[0]         = 1;
    ret_val->sbus_rx_cfg__sbus_bias_speed_sel[0]  = 3;
    ret_val->ob_cfg0__en_ob[1]                    = 1;
    ret_val->tx_rcpll_cfg2__pll_ena[1]            = 1;
    ret_val->tx_synth_cfg0__synth_ena[1]          = 1;
    ret_val->tx_synth_cfg0__synth_spare_pool[0]   = 7;

    if (f_pll_khz_plain > 10312500) {
      ret_val->tx_synth_cfg0__synth_off_comp_ena[0] = 31;
    } else {
      ret_val->tx_synth_cfg0__synth_off_comp_ena[0] = 23;
    }

    ret_val->hr_mode[0]                           = half_rate_mode;

    rslt |= sd10g65_synth_mult_calc(cfg_f_pll, config.chip_name, &synth_mult_calc_rslt);

    ret_val->tx_synth_cfg0__synth_speed_sel[0]      = synth_mult_calc_rslt.synth_speed_sel;
    ret_val->tx_synth_cfg0__synth_fbdiv_sel[0]      = synth_mult_calc_rslt.synth_fbdiv_sel;
    ret_val->tx_synth_cfg3__synth_freqm_0[0]        = synth_mult_calc_rslt.synth_freqm_0;
    ret_val->tx_synth_cfg4__synth_freqn_0[0]        = synth_mult_calc_rslt.synth_freqn_0;
    ret_val->tx_synth_cfg1__synth_freqm_1[0]        = synth_mult_calc_rslt.synth_freqm_1;
    ret_val->tx_synth_cfg1__synth_freqn_1[0]        = synth_mult_calc_rslt.synth_freqn_1;
    ret_val->tx_synth_cfg1__synth_freq_mult_byp[0]  = synth_mult_calc_rslt.synth_freq_mult_byp;
    ret_val->tx_synth_cfg1__synth_freq_mult_hi[0]   = synth_mult_calc_rslt.synth_freq_mult_hi;
    ret_val->tx_synth_cfg1__synth_freq_mult[0]      = synth_mult_calc_rslt.synth_freq_mult;
    ret_val->tx_synth_cfg0__synth_ls_speed[0]       = synth_mult_calc_rslt.tx_synth_ls_speed;
    ret_val->tx_synth_cfg0__synth_cs_speed[0]       = synth_mult_calc_rslt.tx_synth_cs_speed;

    if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B)) {
        ret_val->chip_needs_hrate_toggle[0] = 1;
    } else {
        ret_val->chip_needs_hrate_toggle[0] = 0;
    }

    ret_val->tx_synth_cfg0__synth_hrate_ena[0]  = (half_rate_mode + 1) % 2;
    ret_val->tx_synth_cfg0__synth_hrate_ena[1]  = half_rate_mode;

    ret_val->tx_synth_cfg0__synth_ena_sync_unit[0] = 1;
    ret_val->tx_synth_cfg0__synth_conv_ena[0]      = 1;
    ret_val->tx_synth_cfg0__synth_ds_ena[0]        = 0;
    ret_val->tx_synth_cfg0__synth_ds_dir[0]        = 0;
    ret_val->tx_synth_cfg0__synth_ds_speed[0]      = 0;
    ret_val->tx_synth_cfg0__synth_ls_dir[0]        = 0;
    ret_val->tx_synth_cfg0__synth_ls_ena[0]        = config.ls_ena;

    ret_val->ssc_cfg1__sync_ctrl_fsel[0] = config.i2_fsel;
    if (config.inp_loop == TRUE) {
        ret_val->ob_cfg0__en_inp_loop[0]     = 1;
        ret_val->ob_cfg0__en_pad_loop[0]     = 0;
    } else if (config.pad_loop == TRUE) {
        ret_val->ob_cfg0__en_inp_loop[0]     = 0;
        ret_val->ob_cfg0__en_pad_loop[0]     = 1;
    } else {
        ret_val->ob_cfg0__en_inp_loop[0]     = 0;
        ret_val->ob_cfg0__en_pad_loop[0]     = 0;
    }
    ret_val->ob_cfg0__sel_ifw[0]         = sd10g65_get_iw_setting(config.if_width);
    ret_val->ob_cfg0__incr_levn[0]       = config.incr_levn;
    ret_val->ob_cfg0__levn[0]            = config.ob_levn;
    if (config.invert == TRUE) {
      ret_val->ob_cfg0__ser_inv[0]          = 1;
    } else {
      ret_val->ob_cfg0__ser_inv[0]          = 0;
    }
    ret_val->ob_cfg1__lev_shft[0]        = 1;
    ret_val->ob_cfg1__predrv_r_ctrl[0]   = 3;
    ret_val->ob_cfg1__predrv_c_ctrl[0]   = 3;
    ret_val->ob_cfg2__d_filter[0]        = 0;
    if (config.mute == FALSE) {
        if (config.if_width > 10) {
            ret_val->ob_cfg2__d_filter[0]        = 0x7DF820;
        } else {
            ret_val->ob_cfg2__d_filter[0]        = 0x820820;
        }
    } else {
        ret_val->ob_cfg0__incr_levn[0]       = 1;
        ret_val->ob_cfg0__levn[0]            = 31;
        ret_val->ob_cfg2__d_filter[0]        = 0x0;
    }

    if ((config.chip_name != VTSS_SD10G65_CHIP_ES6514) &&
        (config.chip_name != VTSS_SD10G65_CHIP_VENICE) &&
        (config.chip_name != VTSS_SD10G65_CHIP_JAGUAR2)) {
        ret_val->is_new_rcpll[0] = 1;
    } else {
        ret_val->is_new_rcpll[0] = 0;

    }

    ret_val->tx_rcpll_cfg2__pll_vco_cur[0] = 7;
    ret_val->tx_rcpll_cfg2__pll_vreg18[0]  = 10;
    if (f_pll_khz_plain > 7000000) {
      ret_val->tx_rcpll_cfg2__pll_lpf_cur[0] = 3;
      ret_val->tx_rcpll_cfg2__pll_lpf_res[0] = 10;
    } else if (f_pll_khz_plain > 3000000) {
      ret_val->tx_rcpll_cfg2__pll_lpf_cur[0] = 2;
      ret_val->tx_rcpll_cfg2__pll_lpf_res[0] = 15;
    } else {
      ret_val->tx_rcpll_cfg2__pll_lpf_cur[0] = 0;
      ret_val->tx_rcpll_cfg2__pll_lpf_res[0] = 10;
    }

    ret_val->tx_rcpll_cfg0__pllf_start_cnt[0]     = 2;
    ret_val->tx_rcpll_cfg0__pllf_syn_clk_ena[0]   = 0;
    ret_val->tx_rcpll_cfg0__pllf_loop_ctrl_ena[0] = 0;
    ret_val->tx_rcpll_cfg0__pllf_loop_ena[0]      = 0;
    ret_val->tx_rcpll_cfg0__pllf_ena[0]           = 0;

    if (half_rate_mode == 1) {
        ret_val->tx_rcpll_cfg1__pllf_ref_cnt_end[0] = (u16) ((u32)config.if_width * 64 * 1000000/(f_pll_khz_plain >> 1));
    } else {
        ret_val->tx_rcpll_cfg1__pllf_ref_cnt_end[0] = (u16) ((u32)config.if_width * 64 * 1000000/f_pll_khz_plain);
    }

    ret_val->tx_rcpll_cfg0__pllf_oor_recal_ena[0] = 1;

    for (ifw_tmp = 4; ifw_tmp < 6; ifw_tmp++) {
        ret_val->ob_cfg0__sel_ifw[ifw_tmp-3]         = ifw_tmp;
        for (tog_cnt = 0; tog_cnt < 2*hrate_toggle_cnt; tog_cnt++) {
            ret_val->tx_synth_cfg0__synth_hrate_ena[2+(ifw_tmp-4)*2*hrate_toggle_cnt+tog_cnt] = (half_rate_mode + tog_cnt + 1) %2;
        }
    }

    ret_val->tx_rcpll_cfg0__pllf_ena[1]           = 1;
    ret_val->tx_rcpll_cfg0__pllf_oor_recal_ena[1] = 0;


    return rslt;
}

vtss_rc vtss_sd10g65_pwr_down(vtss_sd10g65_pwr_down_t *const ret_val) {

    ret_val->sbus_rx_cfg__sbus_bias_en[0] = 1;
    ret_val->sbus_tx_cfg__sbus_bias_en[0] = 1;
    ret_val->tx_synth_cfg0__synth_ena[0]  = 1;
    ret_val->tx_synth_cfg0__synth_ena[1]  = 0;
    ret_val->tx_rcpll_cfg2__pll_ena[0]    = 1;
    ret_val->tx_rcpll_cfg2__pll_ena[1]    = 0;
    ret_val->sbus_tx_cfg__sbus_bias_en[1] = 0;
    ret_val->ob_cfg0__en_ob[0]            = 0;
    ret_val->rx_synth_cfg0__synth_ena[0]  = 1;
    ret_val->rx_synth_cfg0__synth_ena[1]  = 0;
    ret_val->rx_rcpll_cfg2__pll_ena[0]    = 1;
    ret_val->rx_rcpll_cfg2__pll_ena[1]    = 0;
    ret_val->ib_cfg8__ib_bias_mode[0]     = 0;
    ret_val->ib_cfg0__ib_dfe_ena[0]       = 0;
    ret_val->ib_cfg0__ib_ia_ena[0]        = 0;
    ret_val->ib_cfg0__ib_ld_ena[0]        = 0;
    ret_val->ib_cfg0__ib_clkdiv_ena[0]    = 0;
    ret_val->ib_cfg0__ib_eqz_ena[0]       = 0;
    ret_val->ib_cfg0__ib_sam_ena[0]       = 0;
    ret_val->sbus_rx_cfg__sbus_bias_en[1] = 0;

    return VTSS_RC_OK;
}

vtss_rc vtss_sd10g65_setup_rx_args_init (vtss_sd10g65_setup_rx_args_t     *const init_val) {

    init_val->chip_name       = VTSS_SD10G65_CHIP_ES65XX;
    init_val->f_pll.f_pll_khz = 10e6;
    init_val->f_pll.ratio_num = 66;
    init_val->f_pll.ratio_den = 64;
    init_val->f_mode          = VTSS_SD10G65_MODE_NONE;
    init_val->if_width        = 32;
    init_val->preset          = VTSS_SD10G65_PRESET_NONE;
    init_val->no_pwrcycle     = FALSE;
    init_val->fpwr_mode       = TRUE;
    init_val->skip_cal        = FALSE;
    init_val->i1_fsel         = 10;
    init_val->i1_lim          = 10;
    init_val->i2_fsel         = 35;
    init_val->p_step          = 1;
    init_val->i1_step         = 1;
    init_val->i2_step         = FALSE;
    init_val->i2_step_val     = 0;
    init_val->fb_step         = FALSE;
    init_val->fb_step_val     = 0;
    init_val->inp_loop        = FALSE;
    init_val->pad_loop        = FALSE;
    init_val->cmos_loop       = FALSE;
    init_val->lock2ref        = FALSE;
    init_val->invert          = FALSE;

    return VTSS_RC_OK;
}

/********************************************************************************
 ***                   calc_sd10g65_setup_rx                                ***
 ********************************************************************************/
vtss_rc vtss_calc_sd10g65_setup_rx(const vtss_sd10g65_setup_rx_args_t config,
                                   vtss_sd10g65_setup_rx_struct_t     *const ret_val) {

    vtss_rc rslt;
    vtss_sd10g65_f_pll_t           cfg_f_pll = config.f_pll;
    vtss_sd10g65_f_pll_t           cfg_f_pll_synth_mult_cfg;
    /* vtss_sd10g65_f_pll_t tmp_f_pll; */
    /* u64 base_f_pll = 0; */
    u32     f_pll_khz_plain;
    u8      half_rate_mode;

    u8      ifw_tmp;
    u8      tog_cnt;
    const u8 hrate_toggle_cnt = 2;
    vtss_sd10g65_preset_struct_t preset;
    vtss_sd10g65_loop_cfg_t loop_cfg;
    vtss_sd10g65_synth_mult_calc_rslt_t  synth_mult_calc_rslt;

    rslt = VTSS_RC_OK;

    if (config.f_mode != VTSS_SD10G65_MODE_NONE) {
        rslt |= vtss_sd10g65_get_f_pll_from_f_mode(config.f_mode, &cfg_f_pll);
    }
    f_pll_khz_plain = (u32) (MEPA_DIV64( ((u64) cfg_f_pll.f_pll_khz * (u64) cfg_f_pll.ratio_num), (u64) cfg_f_pll.ratio_den));

    // Mode dependent settings (ib_rib_adj 2-complement: 8=>-8,15=>-1,0=>0,7=>7)

    // Set default preset values
    rslt |= vtss_sd10g65_set_default_preset_values(&preset);

    if ((config.chip_name != VTSS_SD10G65_CHIP_VENICE_C) &&
        (config.chip_name != VTSS_SD10G65_CHIP_JAGUAR2C) &&
        (config.chip_name != VTSS_SD10G65_CHIP_MALIBU_B)) {
      if ((config.preset == VTSS_SD10G65_ZR_SC) ||
          (config.preset == VTSS_SD10G65_DAC_SC) ||
          (config.preset == VTSS_SD10G65_SR_SC) ||
          (config.preset == VTSS_SD10G65_SR2_SC) ||
          (config.preset == VTSS_SD10G65_KR_SC) ||
          (config.preset == VTSS_SD10G65_BACKPLANE_SC)) {
        VTSS_E("vtss_calc_sd10g65_setup_rx: Smart Control presets are not supported for the current Device");
      }
    }


    switch(config.preset) {
        case VTSS_SD10G65_ATE          : preset.synth_dv_ctrl_i1e  =  3;
                                         break;
        case VTSS_SD10G65_ATE_SC       : preset.synth_dv_ctrl_i1e  =  3;
                                         break;
        case VTSS_SD10G65_ZR_HW        : preset.synth_phase_data   =  51;
                                         preset.ib_main_thres_offs = -10;
                                         preset.ib_vscope_hl_offs  =  11;
                                         preset.ib_tc_dfe          =   0;
                                         preset.ib_tc_eq           =   0;
                                         preset.ib_ena_400_inp     =   1;
                                         break;
        case VTSS_SD10G65_ZR_SW        : preset.ib_main_thres_offs = -8;
                                         preset.ib_vscope_hl_offs  = 11;
                                         preset.ib_bias_adj        = 48;
                                         preset.ib_eqz_l_mode      =  2;
                                         preset.ib_dfe_gain_adj    = 36;
                                         preset.ib_tc_dfe          =  0;
                                         preset.ib_tc_eq           =  0;
                                         preset.ib_ena_400_inp     =  1;
                                         break;
        case VTSS_SD10G65_ZR_SC        : preset.ib_main_thres_offs = -8;
                                         preset.ib_vscope_hl_offs  = 11;
                                         preset.ib_bias_adj        = 48;
                                         preset.ib_eqz_l_mode      =  2;
                                         preset.ib_dfe_gain_adj    = 36;
                                         preset.ib_tc_dfe          =  0;
                                         preset.ib_tc_eq           =  0;
                                         preset.ib_ena_400_inp     =  1;
                                         break;
        case VTSS_SD10G65_DAC_HW       : preset.ib_vscope_hl_offs  = 10;
                                         preset.ib_rib_adj         =  8;
                                         preset.ib_eq_ld1_offset   = 20;
                                         preset.ib_tc_dfe          =  0;
                                         preset.ib_tc_eq           =  0;
                                         preset.ib_ena_400_inp     =  1;
                                         break;
        case VTSS_SD10G65_DAC_SW       : preset.ib_vscope_hl_offs  = 10;
                                         preset.ib_rib_adj         =  8;
                                         preset.ib_eq_ld1_offset   = 20;
                                         preset.ib_tc_dfe          =  0;
                                         preset.ib_tc_eq           =  0;
                                         preset.ib_ena_400_inp     =  1;
                                         preset.ib_eqz_l_mode      =  3;
                                         preset.ib_eqz_c_mode      =  1;
                                         break;
        case VTSS_SD10G65_DAC_SC       : preset.ib_vscope_hl_offs  = 10;
                                         preset.ib_rib_adj         =  8;
                                         preset.ib_eq_ld1_offset   = 20;
                                         preset.ib_tc_dfe          =  0;
                                         preset.ib_tc_eq           =  0;
                                         preset.ib_ena_400_inp     =  1;
                                         preset.ib_eqz_l_mode      =  3;
                                         preset.ib_eqz_c_mode      =  1;
                                         break;
        case VTSS_SD10G65_SR_HW        : preset.ib_eqz_c_adj       =  2;
                                         preset.synth_phase_data   = 54;
                                         break;
        case VTSS_SD10G65_SR_SC        : preset.ib_eqz_l_mode      =  3;
                                         preset.ib_eqz_c_mode      =  1;
                                         break;
        case VTSS_SD10G65_SR2_HW       : preset.synth_phase_data   = 54;
                                         break;
        case VTSS_SD10G65_SR2_SC       : preset.ib_eqz_l_mode      =  3;
                                         preset.ib_eqz_c_mode      =  1;
                                         break;
        case VTSS_SD10G65_BACKPLANE    : preset.synth_phase_data   = 54;
                                         break;
        case VTSS_SD10G65_BACKPLANE_SC : preset.ib_vscope_hl_offs  = 10;
                                         preset.ib_rib_adj         =  8;
                                         preset.ib_eq_ld1_offset   = 20;
                                         preset.ib_tc_dfe          =  0;
                                         preset.ib_tc_eq           =  0;
                                         preset.ib_ena_400_inp     =  1;
                                         preset.ib_eqz_l_mode      =  3;
                                         preset.ib_eqz_c_mode      =  1;
                                         break;
        case VTSS_SD10G65_B2B          : preset.synth_phase_data   = 54;
                                         break;
        case VTSS_SD10G65_KR_HW        : preset.ib_vscope_hl_offs  = 10;
                                         preset.ib_eqz_l_mode      =  2;
                                         preset.ib_eq_ld1_offset   = 20;
                                         preset.ib_rib_adj         = 12;
                                         preset.ib_ena_400_inp     =  1;
                                         break;
        case VTSS_SD10G65_KR_SC        : preset.ib_vscope_hl_offs  = 10;
                                         preset.ib_rib_adj         =  8;
                                         preset.ib_eq_ld1_offset   = 20;
                                         preset.ib_tc_dfe          =  0;
                                         preset.ib_tc_eq           =  0;
                                         preset.ib_ena_400_inp     =  1;
                                         preset.ib_eqz_l_mode      =  3;
                                         preset.ib_eqz_c_mode      =  1;
                                         break;
        default                        : break;
    }

    if (f_pll_khz_plain < 2500000) {
        half_rate_mode = 1;
        f_pll_khz_plain = f_pll_khz_plain * 2;
        cfg_f_pll.f_pll_khz = cfg_f_pll.f_pll_khz * 2;
    } else {
        half_rate_mode = 0;
    }

    ret_val->f_pll_khz_plain[0] = f_pll_khz_plain;
    ret_val->f_pll_f_pll_khz[0] = cfg_f_pll.f_pll_khz;
    ret_val->f_pll_ratio_num[0] = cfg_f_pll.ratio_num;
    ret_val->f_pll_ratio_den[0] = cfg_f_pll.ratio_den;

    rslt |= setup_loop_cfg(config.chip_name, config.inp_loop, config.pad_loop, config.cmos_loop, preset.ib_sig_sel, &loop_cfg);
    if (rslt != VTSS_RC_OK) {
        VTSS_E("Error during loop config");
        return rslt;
    }

    /* -------------------------------------------------------------------- */
    /* Initial power down-cycle (required for RCPLL ramp-up in some chips)  */
    /* -------------------------------------------------------------------- */
    if ((config.no_pwrcycle == 0) &&
        ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
         (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
         (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B))) {
        ret_val->pwrcycle[0] = 1;
    } else {
        ret_val->pwrcycle[0] = 0;
    }

    ret_val->rx_synth_cfg0__synth_ena[0] = 0;
    ret_val->rx_rcpll_cfg2__pll_ena[0]   = 0;
    ret_val->ib_cfg8__ib_bias_mode[0]    = 0;
    ret_val->ib_cfg0__ib_dfe_ena[0]      = 0;
    ret_val->ib_cfg0__ib_ia_ena[0]       = 0;
    ret_val->ib_cfg0__ib_ld_ena[0]       = 0;
    ret_val->ib_cfg0__ib_clkdiv_ena[0]   = 0;
    ret_val->ib_cfg0__ib_eqz_ena[0]      = 0;
    ret_val->ib_cfg0__ib_sam_ena[0]      = 0;

    /* -------------------------------------------------------------------- */
    /* Configure SBUS                                                       */
    /* -------------------------------------------------------------------- */
    if (config.chip_name == VTSS_SD10G65_CHIP_ROLEX) {
        ret_val->sbus_special_handling[0] = 1;
    } else {
        ret_val->sbus_special_handling[0] = 0;
    }

    ret_val->sbus_rx_cfg__sbus_loopdrv_ena[0]    = loop_cfg.sbus_loopdrv_ena;
    ret_val->sbus_rx_cfg__sbus_spare_pool[0]     = loop_cfg.sbus_spare_pool;
    ret_val->sbus_rx_cfg__sbus_bias_en[0]        = 1; /* select sync_ibus0 */
    ret_val->sbus_rx_cfg__sbus_bias_speed_sel[0] = 3; /* no longer data rate dependend */

    /* -------------------------------------------------------------------- */
    /* Enable various bias circuits (SYNTH, PLL, IB)                        */
    /* -------------------------------------------------------------------- */

    ret_val->rx_rcpll_cfg2__pll_ena[1]        = 1;
    ret_val->rx_synth_cfg0__synth_ena[1]      = 1;  /* global synthesizer enable */
    ret_val->rx_synth_cfg2__synth_aux_ena[0]  = 1;  /* aux channel clk gen */
    if (config.fpwr_mode == TRUE) {
        ret_val->ib_cfg0__ib_clkdiv_ena[1]    = 1;  /* enckdv  (enable internal clock divider) */
    } else {
        ret_val->ib_cfg0__ib_clkdiv_ena[1]    = 0;  /* enckdv  (disable internal clock divider) */
    }
    ret_val->ib_cfg0__ib_vbulk_sel[0]         = 1;  /* fast    (sel. bulk volt. for cml cells) */
    ret_val->ib_cfg0__ib_sam_ena[1]           = 1;  /* ensam   (enable sampling stage) */
    ret_val->ib_cfg8__ib_bias_mode[1]         = 1;  /* constant current mode */
    ret_val->ib_cfg8__ib_cml_curr[0]          = 0;  /* run with increased current */
    ret_val->ib_cfg8__ib_bias_adj[0]          = preset.ib_bias_adj;

    if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B)) {
        ret_val->chip_needs_hrate_toggle[0] = 1;
    } else {
        ret_val->chip_needs_hrate_toggle[0] = 0;
    }
    /* -------------------------------------------------------------------- */
    /* Some register accesses to help the RCPLL come out of reset           */
    /* -------------------------------------------------------------------- */
    ret_val->des_cfg0__des_if_mode_sel[0] = 0;
    ret_val->des_cfg0__des_dis[0]         = 1;
    ret_val->des_cfg0__des_dis[1]         = 0;

    /* -------------------------------------------------------------------- */
    /* Configure RX-SYNTHESIZER                                             */
    /* -------------------------------------------------------------------- */
    ret_val->rx_synth_cfg0__synth_spare_pool[0]   = 7;
    ret_val->rx_synth_cfg0__synth_off_comp_ena[0] = 15;

    if (config.fpwr_mode == TRUE) {
        cfg_f_pll_synth_mult_cfg = cfg_f_pll;
    } else {
        cfg_f_pll_synth_mult_cfg = cfg_f_pll;
        cfg_f_pll_synth_mult_cfg.f_pll_khz = cfg_f_pll.f_pll_khz / 2;
        if (cfg_f_pll_synth_mult_cfg.f_pll_khz * 2 != cfg_f_pll.f_pll_khz) {
            VTSS_D("Rounding error during calculation of synthesizer settings. Try to use ratio to avoid this");
        }
    }

    rslt |= sd10g65_synth_mult_calc(cfg_f_pll_synth_mult_cfg, config.chip_name, &synth_mult_calc_rslt);

    ret_val->rx_synth_cfg0__synth_speed_sel[0]      = synth_mult_calc_rslt.synth_speed_sel;
    ret_val->rx_synth_cfg0__synth_fbdiv_sel[0]      = synth_mult_calc_rslt.synth_fbdiv_sel;
    ret_val->rx_synth_cfg3__synth_freqm_0[0]        = synth_mult_calc_rslt.synth_freqm_0;
    ret_val->rx_synth_cfg4__synth_freqn_0[0]        = synth_mult_calc_rslt.synth_freqn_0;
    ret_val->rx_synth_cfg1__synth_freqm_1[0]        = synth_mult_calc_rslt.synth_freqm_1;
    ret_val->rx_synth_cfg1__synth_freqn_1[0]        = synth_mult_calc_rslt.synth_freqn_1;
    ret_val->rx_synth_cfg1__synth_freq_mult_byp[0]  = synth_mult_calc_rslt.synth_freq_mult_byp;
    ret_val->rx_synth_cfg1__synth_freq_mult_hi[0]   = synth_mult_calc_rslt.synth_freq_mult_hi;
    ret_val->rx_synth_cfg1__synth_freq_mult[0]      = synth_mult_calc_rslt.synth_freq_mult;
    ret_val->rx_synth_cfg0__synth_fb_step[0]        = synth_mult_calc_rslt.rx_synth_fb_step;
    ret_val->rx_synth_cfg0__synth_i2_step[0]        = synth_mult_calc_rslt.rx_synth_i2_step;

    ret_val->fb_step_param_used[0]                  = (config.fb_step == TRUE) ? 1 : 0;
    ret_val->rx_synth_cfg0__synth_fb_step[1]        = config.fb_step_val;
    ret_val->i2_step_param_used[0]                  = (config.i2_step == TRUE) ? 1 : 0;
    ret_val->rx_synth_cfg0__synth_i2_step[1]        = config.i2_step_val;


    /* half rate mode handling */
    ret_val->rx_synth_cfg0__synth_hrate_ena[0]  = (half_rate_mode + 1) % 2;
    ret_val->rx_synth_cfg0__synth_hrate_ena[1]  = half_rate_mode;

    ret_val->rx_synth_cfg0__synth_i2_ena[0]     = 1;
    ret_val->rx_synth_cfg0__synth_conv_ena[0]   = 1;

    ret_val->rx_synth_sync_ctrl__synth_sc_sync[0] = 0;

    if (config.fpwr_mode == TRUE) {
        if (f_pll_khz_plain > 5000000) {
            ret_val->rx_synth_cfg2__synth_phase_data[0] = preset.synth_phase_data;
        } else {
            ret_val->rx_synth_cfg2__synth_phase_data[0] = 64;
        }
    } else {
        ret_val->rx_synth_cfg2__synth_phase_data[0] = 32;
    }

    if (config.f_mode == VTSS_SD10G65_MODE_FX100) {
        ret_val->rx_synth_cfg2__synth_cpmd_dig_ena[0] = 1;
    } else {
        ret_val->rx_synth_cfg2__synth_cpmd_dig_ena[0] = 0;
    }

    /* phase rotator stepping changed from 64 to 128 steps (stepsize reduced to 1/128 UI) */
    ret_val->rx_synth_cfg0__synth_p_step[0]  = config.p_step;
    ret_val->rx_synth_cfg0__synth_i1_step[0] = config.i1_step;

    /* # enable integrator1 activity */
    if (config.lock2ref == TRUE) {
        ret_val->rx_synth_cfg2__synth_dv_ctrl_i1e[0] = 1;
        ret_val->rx_synth_cfg2__synth_dv_ctrl_i1m[0] = 1;
    } else {
        if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
            (config.chip_name == VTSS_SD10G65_CHIP_VENICE_C) ||
            (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
            (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B) ||
            (config.chip_name == VTSS_SD10G65_CHIP_ES6512) ||
            (config.chip_name == VTSS_SD10G65_CHIP_ES6514) ||
            (config.chip_name == VTSS_SD10G65_CHIP_ES65XX) ||
            (config.chip_name == VTSS_SD10G65_CHIP_ROLEX)) {
            ret_val->rx_synth_cfg2__synth_dv_ctrl_i1e[0] = 3;
            ret_val->rx_synth_cfg2__synth_dv_ctrl_i1m[0] = 3;
        } else if ((config.chip_name == VTSS_SD10G65_CHIP_JAGUAR2) ||
                   (config.chip_name == VTSS_SD10G65_CHIP_JAGUAR2C) ||
                   (config.chip_name == VTSS_SD10G65_CHIP_SERVALT)) {
            ret_val->rx_synth_cfg2__synth_dv_ctrl_i1e[0] = preset.synth_dv_ctrl_i1e;
            ret_val->rx_synth_cfg2__synth_dv_ctrl_i1m[0] = preset.synth_dv_ctrl_i1e;
        } else {
            VTSS_E("CHIP not fully supported yet by sd10g65_setup_rx_c. Please specify behaviour of I1 in case of a missing link status signal.");
            ret_val->rx_synth_cfg2__synth_dv_ctrl_i1e[0] = 0;
            ret_val->rx_synth_cfg2__synth_dv_ctrl_i1m[0] = 0;
        }
    }

    ret_val->rx_synth_cdrlf__synth_integ3_ena[0] = 1;

    ret_val->rx_synth_cdrlf[0] = (0x80000000 |
                                 ((u32)config.i1_lim  << 21) |
                                 ((u32)config.i1_lim  << 16) |
                                 ((u32)config.i1_lim  << 11) |
                                 ((u32)config.i1_fsel <<  6) |
                                 ((u32)config.i2_fsel <<  0));

    ret_val->rx_synth_cdrlf__synth_integ1_max1[0] = config.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_max0[0] = config.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_lim[0]  = config.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_fsel[0] = config.i1_fsel;
    ret_val->rx_synth_cdrlf__synth_integ2_fsel[0] = config.i2_fsel;

    /* -------------------------------------------------------------------- */
    /* Configure IB                                                         */
    /* -------------------------------------------------------------------- */
    ret_val->ib_cfg0__ib_rib_adj[0]     = preset.ib_rib_adj;
    ret_val->ib_cfg0__ib_eqz_ena[1]     = 1;
    ret_val->ib_cfg0__ib_dfe_ena[1]     = 1;
    ret_val->ib_cfg0__ib_ld_ena[1]      = 1;
    ret_val->ib_cfg0__ib_ia_ena[1]      = 1;
    ret_val->ib_cfg0__ib_ia_sdet_ena[0] = 1;

    ret_val->ib_cfg3__ib_eq_ld1_offset[0] = preset.ib_eq_ld1_offset;
    ret_val->ib_cfg3__ib_ldsd_divsel[0]   = 0; /* 0: divide by 128 */
    ret_val->ib_cfg3__ib_ia_sdet_level[0] = 2;
    ret_val->ib_cfg3__ib_sdet_sel[0]      = 0; /* 0:ia, 1:ie (default: 0) */

    ret_val->ib_cfg5__ib_offs_value[0] = 31;
    ret_val->ib_cfg5__ib_calmux_ena[0] = 1;


    /* Set default values in case not used */
    ret_val->ib_cfg6__ib_auto_agc_adj[0]   = 0;
    ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 0;
    ret_val->ib_cfg7__ib_dfe_gain_adj[0]   = 63;
    if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (config.chip_name == VTSS_SD10G65_CHIP_ES6514)) {
        /* macros with original IB - leave as it is for now */
        ret_val->ib_cfg6__ib_sam_offs_adj[0]   = preset.ib_sam_offs_adj;
        if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) &&
            (config.preset == VTSS_SD10G65_SR_HW)) {
          ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 0;
        } else {
          ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 1;
        }
        ret_val->ib_cfg7__ib_dfe_gain_adj[0]   = preset.ib_dfe_gain_adj;
        ret_val->ib_cfg7__ib_dfe_offset_h[0]   = 25; /*needed for IB-Cal via APC */
    } else if (config.chip_name == VTSS_SD10G65_CHIP_JAGUAR2) {
        /* macros with original IB with improved cfg */
        ret_val->ib_cfg6__ib_sam_offs_adj[0]   = preset.ib_sam_offs_adj;
        ret_val->ib_cfg6__ib_auto_agc_adj[0]   = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj[0]   = preset.ib_dfe_gain_adj;
        ret_val->ib_cfg7__ib_dfe_offset_h[0]   = 20;
    } else {
        /* macros with improved 1st IB stage, e.g. "MALIBU", "SERVALT" */
        ret_val->ib_cfg6__ib_sam_offs_adj[0]   = preset.ib_sam_offs_adj;
        ret_val->ib_cfg6__ib_auto_agc_adj[0]   = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj[0]   = preset.ib_dfe_gain_adj;
        // vscope_hl_offs / dfe_offset_h relation: 8/19, 10/24, 11/26 -> calculate automatically:
        // tcl code: expr (int(0.5 + 19.0/8.0 * $PRESET(ib_vscope_hl_offs)))
        // --> 4/8 + 19/8 * preset.ib_vscope_hl_offs = (4+19* preset.ib_vscope_hl_offs)/8
        ret_val->ib_cfg7__ib_dfe_offset_h[0]   = (u8) ((u16)(4 + 19*preset.ib_vscope_hl_offs)/8);
    }

    if (config.skip_cal == TRUE) {
         ret_val->skip_cal[0] = 1;
    } else {
         ret_val->skip_cal[0] = 0;
    }
    ret_val->ib_cfg8__ib_lat_neutral[0] = 1;
    ret_val->ib_cfg8__ib_lat_neutral[1] = 0;

    /* Enable c_adj "boost" bits */
    ret_val->ib_cfg4__ib_eqz_c_adj_ib[0]   = preset.ib_eqz_c_adj;
    ret_val->ib_cfg4__ib_eqz_c_adj_es0[0]  = preset.ib_eqz_c_adj;
    ret_val->ib_cfg4__ib_eqz_c_adj_es1[0]  = preset.ib_eqz_c_adj;
    ret_val->ib_cfg4__ib_eqz_c_adj_es2[0]  = preset.ib_eqz_c_adj;

    /* Define L/C ramping */
    ret_val->ib_cfg4__ib_eqz_c_mode[0]     = preset.ib_eqz_c_mode;
    ret_val->ib_cfg4__ib_eqz_l_mode[0]     = preset.ib_eqz_l_mode;

    /* set Vscope threshold voltage to +/- 0.08V */
    ret_val->ib_cfg4__ib_vscope_h_thres[0] = 32 + preset.ib_vscope_hl_offs;
    ret_val->ib_cfg4__ib_vscope_l_thres[0] = 31 - preset.ib_vscope_hl_offs;
    if (preset.ib_main_thres_offs >= 0) {
        ret_val->ib_cfg4__ib_main_thres[0] = 32 + preset.ib_main_thres_offs;
    } else {
        ret_val->ib_cfg4__ib_main_thres[0] = 31 + preset.ib_main_thres_offs;
    }

    ret_val->ib_cfg3__ib_set_sdet[0]     = loop_cfg.en_pad_loop;
    ret_val->ib_cfg0__ib_sig_sel[0]      = loop_cfg.sig_sel;
    ret_val->ib_cfg10__ib_loop_drv[0]    = loop_cfg.en_inp_loop;
    ret_val->ib_cfg10__ib_loop_rec[0]    = loop_cfg.en_pad_loop;

    ret_val->ib_cfg11__ib_ena_400_inp[0] = preset.ib_ena_400_inp;
    ret_val->ib_cfg11__ib_tc_dfe[0]      = preset.ib_tc_dfe;
    ret_val->ib_cfg11__ib_tc_eq[0]       = preset.ib_tc_eq;

    /* -------------------------------------------------------------------- */
    /* Configure DES                                                        */
    /* -------------------------------------------------------------------- */
    if (half_rate_mode == 1) {
        ret_val->moebdiv_cfg0__moebdiv_bw_cdr_sel_a[0] = 2;
        ret_val->moebdiv_cfg0__moebdiv_bw_cdr_sel_b[0] = 2;
    } else {
        ret_val->moebdiv_cfg0__moebdiv_bw_cdr_sel_a[0] = 3;
        ret_val->moebdiv_cfg0__moebdiv_bw_cdr_sel_b[0] = 3;
    }
    ret_val->moebdiv_cfg0__moebdiv_cpmd_swap[0] = 0;
    if (config.lock2ref == TRUE) {
        ret_val->moebdiv_cfg0__moebdiv_dis[0] = 1;
    } else {
        ret_val->moebdiv_cfg0__moebdiv_dis[0] = 0;
    }
    if (config.invert == TRUE) {
      ret_val->des_cfg0__des_inv_m[0] = 1;
      ret_val->des_cfg0__des_inv_h[0] = 1;
      ret_val->des_cfg0__des_inv_l[0] = 1;
    } else {
      ret_val->des_cfg0__des_inv_m[0] = 0;
      ret_val->des_cfg0__des_inv_h[0] = 0;
      ret_val->des_cfg0__des_inv_l[0] = 0;
    }
    ret_val->des_cfg0__des_if_mode_sel[1]     = sd10g65_get_iw_setting(config.if_width);

    /* -------------------------------------------------------------------- */
    /* Configure RX-RCPLL                                                   */
    /* -------------------------------------------------------------------- */

    if ((config.chip_name != VTSS_SD10G65_CHIP_ES6514) &&
        (config.chip_name != VTSS_SD10G65_CHIP_VENICE) &&
        (config.chip_name != VTSS_SD10G65_CHIP_JAGUAR2)) {
        ret_val->is_new_rcpll[0] = 1;
    } else {
        ret_val->is_new_rcpll[0] = 0;

    }

    ret_val->rx_rcpll_cfg2__pll_vco_cur[0] = 7;
    ret_val->rx_rcpll_cfg2__pll_vreg18[0]  = 10;
    if (f_pll_khz_plain > 7000000) {
      ret_val->rx_rcpll_cfg2__pll_lpf_cur[0] = 3;
      ret_val->rx_rcpll_cfg2__pll_lpf_res[0] = 10;
    } else if (f_pll_khz_plain > 3000000) {
      ret_val->rx_rcpll_cfg2__pll_lpf_cur[0] = 2;
      ret_val->rx_rcpll_cfg2__pll_lpf_res[0] = 15;
    } else {
      ret_val->rx_rcpll_cfg2__pll_lpf_cur[0] = 0;
      ret_val->rx_rcpll_cfg2__pll_lpf_res[0] = 10;
    }

    ret_val->rx_rcpll_cfg0__pllf_start_cnt[0]     = 2;
    ret_val->rx_rcpll_cfg0__pllf_syn_clk_ena[0]   = 0;
    ret_val->rx_rcpll_cfg0__pllf_loop_ctrl_ena[0] = 0;
    ret_val->rx_rcpll_cfg0__pllf_loop_ena[0]      = 0;
    ret_val->rx_rcpll_cfg0__pllf_ena[0]           = 0;

    if (half_rate_mode == 1) {
        ret_val->rx_rcpll_cfg1__pllf_ref_cnt_end[0] = (u16) ((u32)config.if_width * 64 * 1000000/(f_pll_khz_plain >> 1));
    } else {
        ret_val->rx_rcpll_cfg1__pllf_ref_cnt_end[0] = (u16) ((u32)config.if_width * 64 * 1000000/f_pll_khz_plain);
    }

    ret_val->rx_rcpll_cfg0__pllf_oor_recal_ena[0] = 1;

    for (ifw_tmp = 4; ifw_tmp < 6; ifw_tmp++) {
        ret_val->des_cfg0__des_if_mode_sel[ifw_tmp-2]         = ifw_tmp;
        for (tog_cnt = 0; tog_cnt < 2*hrate_toggle_cnt; tog_cnt++) {
            ret_val->rx_synth_cfg0__synth_hrate_ena[2+(ifw_tmp-4)*2*hrate_toggle_cnt+tog_cnt] = (half_rate_mode + tog_cnt + 1) %2;
        }
    }
    for (ifw_tmp = 4; ifw_tmp < 6; ifw_tmp++) {
        for (tog_cnt = 0; tog_cnt < 2*hrate_toggle_cnt; tog_cnt++) {
            ret_val->rx_synth_cfg0__synth_ena[2+(ifw_tmp-4)*2*hrate_toggle_cnt+tog_cnt] = tog_cnt % 2;
        }
    }

    ret_val->rx_rcpll_cfg0__pllf_ena[1]           = 1;
    ret_val->rx_rcpll_cfg0__pllf_oor_recal_ena[1] = 0;

    return rslt;
}; /* vtss_calc_sd10g65_setup_rx */



vtss_rc vtss_sd10g65_setup_f2df_args_init(vtss_sd10g65_setup_f2df_args_t *const init_val) {

    init_val->chip_name      = VTSS_SD10G65_CHIP_ES65XX;
    init_val->f_in.f_pll_khz = 156250;
    init_val->f_in.ratio_num = 1;
    init_val->f_in.ratio_den = 1;
    init_val->no_pwrcycle    = FALSE;
    init_val->i1_fsel        = 15;
    init_val->i1_lim         = 11;
    init_val->i2_fsel        = 35;
    init_val->inp_loop       = FALSE;
    init_val->pad_loop       = FALSE;
    init_val->cmos_loop      = FALSE;

    return VTSS_RC_OK;
}

/********************************************************************************
 ***                   calc_sd10g65_setup_f2df                                ***
 ********************************************************************************/
vtss_rc vtss_calc_sd10g65_setup_f2df(const vtss_sd10g65_setup_f2df_args_t config,
                                     vtss_sd10g65_setup_f2df_struct_t     *const ret_val ) {

    vtss_rc rslt;
    vtss_sd10g65_f_pll_t           cfg_f_in = config.f_in;
    vtss_sd10g65_f_pll_t           cfg_f_pll_synth_mult_cfg;
    vtss_sd10g65_f_pll_t           cfg_f_sam; /* sample frequency */
    vtss_sd10g65_setup_rx_args_t   config_rx;

    u32     f_in_khz_plain;
    u32     f_sam_khz_plain;

    u8   side_detect;
    u8   side_detect_bit_sel;
    u8   interface_width = 16;
    BOOL found;

    u8      ifw_tmp;
    u8      tog_cnt;
    u8      i;
    const u8 hrate_toggle_cnt = 2;
    vtss_sd10g65_preset_struct_t preset;
    vtss_sd10g65_loop_cfg_t loop_cfg;
    vtss_sd10g65_synth_mult_calc_rslt_t  synth_mult_calc_rslt;

    // Set default preset values
    rslt = vtss_sd10g65_set_default_preset_values(&preset);
    // Default values;
    rslt = VTSS_RC_OK;
    rslt = vtss_sd10g65_setup_rx_args_init (&config_rx);
    if(config.inp_loop == TRUE) {
        if((config.pad_loop == TRUE) || (config.cmos_loop== TRUE)) {
            VTSS_E("sd10g65_setup_f2df: -inp_loop, -pad_loop and -cmos_loop are exclusive, use only one at a time!");
            rslt =  VTSS_RC_ERROR;
            return rslt;
        }
        // # loop data RX-PAD to int. bidi-loop "input loop"
        config_rx.inp_loop = TRUE;
    } else if(config.pad_loop == TRUE) {
        if(config.cmos_loop == TRUE) {
            VTSS_E("sd10g65_setup_f2df: -inp_loop, -pad_loop and -cmos_loop are exclusive, use only one at a time!");
            rslt =  VTSS_RC_ERROR;
            return rslt;
        }
        // # loop data from int. bidi-loop to core "pad loop"
        config_rx.pad_loop = TRUE;
    } else if(config.cmos_loop == TRUE) {
        // # loop data from cmos input from core into IB "pad loop"
        // # same as pad loop, but also set sbus_spare_pool(1), all other bits '0'
        config_rx.cmos_loop = TRUE;
    }

    rslt = setup_loop_cfg(config.chip_name, config_rx.inp_loop, config_rx.pad_loop, config_rx.cmos_loop, preset.ib_sig_sel, &loop_cfg);
    if (rslt != VTSS_RC_OK) {
        VTSS_E("Error during loop config");
        return rslt;
    }

    f_in_khz_plain = (u32) (MEPA_DIV64( ((u64) cfg_f_in.f_pll_khz * (u64) cfg_f_in.ratio_num), (u64) cfg_f_in.ratio_den));
    if (f_in_khz_plain < 1000) {
        VTSS_E("Input frequency = %d kHz to low, has to be >= 1e6Hz", f_in_khz_plain);
        rslt =  VTSS_RC_ERROR;
        return rslt;
    } else if (f_in_khz_plain > 250000) {
        VTSS_E("Input frequency = %d kHz to high, has to be <= 250e6Hz", f_in_khz_plain);
        rslt =  VTSS_RC_ERROR;
        return rslt;
    }

    /*  select interface width and sample divider to give sample frequency between 2.5 and 4 GBps */
    found = FALSE;
    side_detect = 0;
    while ((side_detect < 8) && (found == FALSE)) {
        interface_width = 16;
        if ((f_in_khz_plain * interface_width * (1 << side_detect)) >= 2500000) {
            found = TRUE;
        } else {
            interface_width = 20;
            if ((f_in_khz_plain * interface_width * (1 << side_detect)) >= 2500000) {
                found = TRUE;
            }
        }
        if (found == FALSE) {
            side_detect++;
        }
    }

    /* select side_det_bit dependent on the sampling divider and the interface width */
    if (side_detect == 0) {
        side_detect_bit_sel = interface_width >> 2;
    } else if (side_detect == 1) {
        side_detect_bit_sel = interface_width >> 1;
    } else {
        side_detect_bit_sel = 0;
        if ((config.chip_name == VTSS_SD10G65_CHIP_ES6512) ||
            (config.chip_name == VTSS_SD10G65_CHIP_VENICE)) {
            VTSS_E("Input frequency = %d kHz to low, has to be >= 62.5e6Hz", f_in_khz_plain);
            rslt =  VTSS_RC_ERROR;
            return rslt;
        }
    }

    /* -------------------------------------------------------------------- */
    /* Initial power down-cycle (required for RCPLL ramp-up in some chips)  */
    /* -------------------------------------------------------------------- */
    if ((config.no_pwrcycle == 0) &&
        ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
         (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
         (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B))) {
        ret_val->pwrcycle[0] = 1;
    } else {
        ret_val->pwrcycle[0] = 0;
    }

    cfg_f_sam.f_pll_khz = cfg_f_in.f_pll_khz * interface_width * (1 << side_detect);
    cfg_f_sam.ratio_num = cfg_f_in.ratio_num;
    cfg_f_sam.ratio_den = cfg_f_in.ratio_den;

    f_sam_khz_plain = (u32) (MEPA_DIV64( ((u64) cfg_f_sam.f_pll_khz * (u64) cfg_f_sam.ratio_num), (u64) cfg_f_sam.ratio_den));

    ret_val->f_pll_khz_plain[0] = f_sam_khz_plain;
    ret_val->f_pll_f_pll_khz[0] = cfg_f_sam.f_pll_khz;
    ret_val->f_pll_ratio_num[0] = cfg_f_sam.ratio_num;
    ret_val->f_pll_ratio_den[0] = cfg_f_sam.ratio_den;

    ret_val->f_in_khz_plain[0] = f_in_khz_plain;
    ret_val->f_in_f_pll_khz[0] = cfg_f_in.f_pll_khz;
    ret_val->f_in_ratio_num[0] = cfg_f_in.ratio_num;
    ret_val->f_in_ratio_den[0] = cfg_f_in.ratio_den;


    /* -------------------------------------------------------------------- */
    /* Initial power down-cycle (required for RCPLL ramp-up in some chips)  */
    /* -------------------------------------------------------------------- */
    ret_val->rx_synth_cfg0__synth_ena[0] = 0;
    ret_val->rx_rcpll_cfg2__pll_ena[0]   = 0;
    ret_val->ib_cfg8__ib_bias_mode[0]    = 0;
    ret_val->ib_cfg0__ib_dfe_ena[0]      = 0;
    ret_val->ib_cfg0__ib_ia_ena[0]       = 0;
    ret_val->ib_cfg0__ib_ld_ena[0]       = 0;
    ret_val->ib_cfg0__ib_clkdiv_ena[0]   = 0;
    ret_val->ib_cfg0__ib_eqz_ena[0]      = 0;
    ret_val->ib_cfg0__ib_sam_ena[0]      = 0;

    /* -------------------------------------------------------------------- */
    /* Configure SBUS                                                       */
    /* -------------------------------------------------------------------- */
    if (config.chip_name == VTSS_SD10G65_CHIP_ROLEX) {
        ret_val->sbus_special_handling[0] = 1;
    } else {
        ret_val->sbus_special_handling[0] = 0;
    }

    ret_val->sbus_rx_cfg__sbus_loopdrv_ena[0]    = loop_cfg.sbus_loopdrv_ena;
    ret_val->sbus_rx_cfg__sbus_spare_pool[0]     = loop_cfg.sbus_spare_pool;
    ret_val->sbus_rx_cfg__sbus_bias_en[0]        = 1; /* select sync_ibus0 */
    ret_val->sbus_rx_cfg__sbus_bias_speed_sel[0] = 3; /* no longer data rate dependend */

    /* -------------------------------------------------------------------- */
    /* Enable various bias circuits (SYNTH, PLL, IB)                        */
    /* -------------------------------------------------------------------- */

    ret_val->rx_rcpll_cfg2__pll_ena[1]        = 1;
    ret_val->rx_synth_cfg0__synth_ena[1]      = 1;  /* global synthesizer enable */
    ret_val->rx_synth_cfg2__synth_aux_ena[0]  = 1;  /* aux channel clk gen */

    /* For F2DF fpwr_mode is always true */
    ret_val->ib_cfg0__ib_clkdiv_ena[1]        = 1;  /* enckdv  (enable internal clock divider) */

    ret_val->ib_cfg0__ib_vbulk_sel[0]         = 1;  /* fast    (sel. bulk volt. for cml cells) */
    ret_val->ib_cfg0__ib_sam_ena[1]           = 1;  /* ensam   (enable sampling stage) */
    ret_val->ib_cfg8__ib_bias_mode[1]         = 1;  /* constant current mode */
    ret_val->ib_cfg8__ib_cml_curr[0]          = 0;  /* run with increased current */
    ret_val->ib_cfg8__ib_bias_adj[0]          = preset.ib_bias_adj;

    if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B)) {
        ret_val->chip_needs_hrate_toggle[0] = 1;
    } else {
        ret_val->chip_needs_hrate_toggle[0] = 0;
    }
    /* -------------------------------------------------------------------- */
    /* Some register accesses to help the RCPLL come out of reset           */
    /* -------------------------------------------------------------------- */
    ret_val->des_cfg0__des_if_mode_sel[0] = 0;
    ret_val->des_cfg0__des_dis[0]         = 1;
    ret_val->des_cfg0__des_dis[1]         = 0;

    /* -------------------------------------------------------------------- */
    /* Configure RX-SYNTHESIZER                                             */
    /* -------------------------------------------------------------------- */
    ret_val->rx_synth_cfg0__synth_spare_pool[0]   = 7;
    ret_val->rx_synth_cfg0__synth_off_comp_ena[0] = 15;

    cfg_f_pll_synth_mult_cfg = cfg_f_sam;

    rslt |= sd10g65_synth_mult_calc(cfg_f_pll_synth_mult_cfg, config.chip_name, &synth_mult_calc_rslt);

    ret_val->rx_synth_cfg0__synth_speed_sel[0]      = synth_mult_calc_rslt.synth_speed_sel;
    ret_val->rx_synth_cfg0__synth_fbdiv_sel[0]      = synth_mult_calc_rslt.synth_fbdiv_sel;
    ret_val->rx_synth_cfg3__synth_freqm_0[0]        = synth_mult_calc_rslt.synth_freqm_0;
    ret_val->rx_synth_cfg4__synth_freqn_0[0]        = synth_mult_calc_rslt.synth_freqn_0;
    ret_val->rx_synth_cfg1__synth_freqm_1[0]        = synth_mult_calc_rslt.synth_freqm_1;
    ret_val->rx_synth_cfg1__synth_freqn_1[0]        = synth_mult_calc_rslt.synth_freqn_1;
    ret_val->rx_synth_cfg1__synth_freq_mult_byp[0]  = synth_mult_calc_rslt.synth_freq_mult_byp;
    ret_val->rx_synth_cfg1__synth_freq_mult_hi[0]   = synth_mult_calc_rslt.synth_freq_mult_hi;
    ret_val->rx_synth_cfg1__synth_freq_mult[0]      = synth_mult_calc_rslt.synth_freq_mult;
    ret_val->rx_synth_cfg0__synth_fb_step[0]        = synth_mult_calc_rslt.rx_synth_fb_step;
    ret_val->rx_synth_cfg0__synth_i2_step[0]        = synth_mult_calc_rslt.rx_synth_i2_step;

    /* half rate mode handling */
    ret_val->rx_synth_cfg0__synth_hrate_ena[0]  = 1;
    ret_val->rx_synth_cfg0__synth_hrate_ena[1]  = 0;

    ret_val->rx_synth_cfg0__synth_i2_ena[0]     = 1;
    ret_val->rx_synth_cfg0__synth_conv_ena[0]   = 1;

    ret_val->rx_synth_sync_ctrl__synth_sc_sync[0] = 0;

    if (f_sam_khz_plain > 5000000) {
        ret_val->rx_synth_cfg2__synth_phase_data[0] = preset.synth_phase_data;
    } else {
        ret_val->rx_synth_cfg2__synth_phase_data[0] = 64;
    }

    ret_val->rx_synth_cfg2__synth_cpmd_dig_ena[0] = 0;

    /* phase rotator stepping changed from 64 to 128 steps (stepsize reduced to 1/128 UI) */
    ret_val->rx_synth_cfg0__synth_p_step[0]  = 1;
    ret_val->rx_synth_cfg0__synth_i1_step[0] = 1;

    /* # enable integrator1 activity */
    if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (config.chip_name == VTSS_SD10G65_CHIP_VENICE_C) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B) ||
        (config.chip_name == VTSS_SD10G65_CHIP_ES6512) ||
        (config.chip_name == VTSS_SD10G65_CHIP_ES6514) ||
        (config.chip_name == VTSS_SD10G65_CHIP_ES65XX) ||
        (config.chip_name == VTSS_SD10G65_CHIP_ROLEX)) {
        ret_val->rx_synth_cfg2__synth_dv_ctrl_i1e[0] = 3;
        ret_val->rx_synth_cfg2__synth_dv_ctrl_i1m[0] = 3;
    } else if ((config.chip_name == VTSS_SD10G65_CHIP_JAGUAR2) ||
               (config.chip_name == VTSS_SD10G65_CHIP_JAGUAR2C) ||
               (config.chip_name == VTSS_SD10G65_CHIP_SERVALT)) {
        ret_val->rx_synth_cfg2__synth_dv_ctrl_i1e[0] = 0;
        ret_val->rx_synth_cfg2__synth_dv_ctrl_i1m[0] = 0;
    } else {
        VTSS_E("CHIP not fully supported yet by sd10g65_setup_f2df_c. Please specify behaviour of I1 in case of a missing link status signal.");
        ret_val->rx_synth_cfg2__synth_dv_ctrl_i1e[0] = 0;
        ret_val->rx_synth_cfg2__synth_dv_ctrl_i1m[0] = 0;
    }


    ret_val->rx_synth_cdrlf__synth_integ3_ena[0] = 1;

    ret_val->rx_synth_cdrlf[0] = (0x80000000 |
                                 ((u32)config_rx.i1_lim  << 21) |
                                 ((u32)config_rx.i1_lim  << 16) |
                                 ((u32)config_rx.i1_lim  << 11) |
                                 ((u32)config_rx.i1_fsel <<  6) |
                                 ((u32)config_rx.i2_fsel <<  0));

    ret_val->rx_synth_cdrlf__synth_integ1_max1[0] = config_rx.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_max0[0] = config_rx.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_lim[0]  = config_rx.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_fsel[0] = config_rx.i1_fsel;
    ret_val->rx_synth_cdrlf__synth_integ2_fsel[0] = config_rx.i2_fsel;

    /* -------------------------------------------------------------------- */
    /* Configure IB                                                         */
    /* -------------------------------------------------------------------- */
    ret_val->ib_cfg0__ib_rib_adj[0]     = preset.ib_rib_adj;
    ret_val->ib_cfg0__ib_eqz_ena[1]     = 1;
    ret_val->ib_cfg0__ib_dfe_ena[1]     = 1;
    ret_val->ib_cfg0__ib_ld_ena[1]      = 1;
    ret_val->ib_cfg0__ib_ia_ena[1]      = 1;
    ret_val->ib_cfg0__ib_ia_sdet_ena[0] = 1;

    ret_val->ib_cfg3__ib_eq_ld1_offset[0] = preset.ib_eq_ld1_offset;
    ret_val->ib_cfg3__ib_ldsd_divsel[0]   = 0; /* 0: divide by 128 */
    ret_val->ib_cfg3__ib_ia_sdet_level[0] = 2;
    ret_val->ib_cfg3__ib_sdet_sel[0]      = 0; /* 0:ia, 1:ie (default: 0) */

    ret_val->ib_cfg5__ib_offs_value[0] = 31;
    ret_val->ib_cfg5__ib_calmux_ena[0] = 1;


    /* Set default values in case not used */
    ret_val->ib_cfg6__ib_auto_agc_adj[0]   = 0;
    ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 0;
    ret_val->ib_cfg7__ib_dfe_gain_adj[0]   = 63;
    if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (config.chip_name == VTSS_SD10G65_CHIP_ES6514)) {
        /* macros with original IB - leave as it is for now */
        ret_val->ib_cfg6__ib_sam_offs_adj[0]   = preset.ib_sam_offs_adj;
        // no ib_auto_agc_adj available
        ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj[0]   = preset.ib_dfe_gain_adj;
        ret_val->ib_cfg7__ib_dfe_offset_h[0]   = 25; /*needed for IB-Cal via APC */
    } else if (config.chip_name == VTSS_SD10G65_CHIP_JAGUAR2) {
        /* macros with original IB with improved cfg */
        ret_val->ib_cfg6__ib_sam_offs_adj[0]   = preset.ib_sam_offs_adj;
        ret_val->ib_cfg6__ib_auto_agc_adj[0]   = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj[0]   = preset.ib_dfe_gain_adj;
        ret_val->ib_cfg7__ib_dfe_offset_h[0]   = 20;
    } else {
        /* macros with improved 1st IB stage, e.g. "MALIBU", "SERVALT" */
        ret_val->ib_cfg6__ib_sam_offs_adj[0]   = preset.ib_sam_offs_adj;
        ret_val->ib_cfg6__ib_auto_agc_adj[0]   = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj_s[0] = 1;
        ret_val->ib_cfg7__ib_dfe_gain_adj[0]   = preset.ib_dfe_gain_adj;
        // vscope_hl_offs / dfe_offset_h relation: 8/19, 10/24, 11/26 -> calculate automatically:
        // tcl code: expr (int(0.5 + 19.0/8.0 * $PRESET(ib_vscope_hl_offs)))
        // --> 4/8 + 19/8 * preset.ib_vscope_hl_offs = (4+19* preset.ib_vscope_hl_offs)/8
        ret_val->ib_cfg7__ib_dfe_offset_h[0]   = (u8) ((u16)(4 + 19*preset.ib_vscope_hl_offs)/8);
    }

    ret_val->skip_cal[0] = 0;

    ret_val->ib_cfg8__ib_lat_neutral[0] = 1;
    ret_val->ib_cfg8__ib_lat_neutral[1] = 0;

    /* Enable c_adj "boost" bits */
    ret_val->ib_cfg4__ib_eqz_c_adj_ib[0]   = preset.ib_eqz_c_adj;
    ret_val->ib_cfg4__ib_eqz_c_adj_es0[0]  = preset.ib_eqz_c_adj;
    ret_val->ib_cfg4__ib_eqz_c_adj_es1[0]  = preset.ib_eqz_c_adj;
    ret_val->ib_cfg4__ib_eqz_c_adj_es2[0]  = preset.ib_eqz_c_adj;

    /* Define L/C ramping */
    ret_val->ib_cfg4__ib_eqz_c_mode[0]     = preset.ib_eqz_c_mode;
    ret_val->ib_cfg4__ib_eqz_l_mode[0]     = preset.ib_eqz_l_mode;

    /* set Vscope threshold voltage to +/- 0.08V */
    ret_val->ib_cfg4__ib_vscope_h_thres[0] = 32 + preset.ib_vscope_hl_offs;
    ret_val->ib_cfg4__ib_vscope_l_thres[0] = 31 - preset.ib_vscope_hl_offs;
    if (preset.ib_main_thres_offs >= 0) {
        ret_val->ib_cfg4__ib_main_thres[0] = 32 + preset.ib_main_thres_offs;
    } else {
        ret_val->ib_cfg4__ib_main_thres[0] = 31 + preset.ib_main_thres_offs;
    }

    ret_val->ib_cfg3__ib_set_sdet[0]     = loop_cfg.en_pad_loop;
    ret_val->ib_cfg0__ib_sig_sel[0]      = loop_cfg.sig_sel;
    ret_val->ib_cfg10__ib_loop_drv[0]    = loop_cfg.en_inp_loop;
    ret_val->ib_cfg10__ib_loop_rec[0]    = loop_cfg.en_pad_loop;

    ret_val->ib_cfg11__ib_ena_400_inp[0] = preset.ib_ena_400_inp;
    ret_val->ib_cfg11__ib_tc_dfe[0]      = preset.ib_tc_dfe;
    ret_val->ib_cfg11__ib_tc_eq[0]       = preset.ib_tc_eq;

    /* -------------------------------------------------------------------- */
    /* Configure DES                                                        */
    /* -------------------------------------------------------------------- */
    ret_val->moebdiv_cfg0__moebdiv_bw_cdr_sel_a[0] = 3;
    ret_val->moebdiv_cfg0__moebdiv_bw_cdr_sel_b[0] = 3;
    ret_val->moebdiv_cfg0__moebdiv_cpmd_swap[0] = 0;

    /* For F2DF lock2ref is always false */
    ret_val->moebdiv_cfg0__moebdiv_dis[0] = 0;


    if (config.invert == TRUE) {
      ret_val->des_cfg0__des_inv_m[0] = 1;
      ret_val->des_cfg0__des_inv_h[0] = 1;
      ret_val->des_cfg0__des_inv_l[0] = 1;
    } else {
      ret_val->des_cfg0__des_inv_m[0] = 0;
      ret_val->des_cfg0__des_inv_h[0] = 0;
      ret_val->des_cfg0__des_inv_l[0] = 0;
    }
    ret_val->des_cfg0__des_if_mode_sel[1]  = sd10g65_get_iw_setting(interface_width);

    /* -------------------------------------------------------------------- */
    /* Configure RX-RCPLL                                                   */
    /* -------------------------------------------------------------------- */

    if ((config.chip_name != VTSS_SD10G65_CHIP_ES6514) &&
        (config.chip_name != VTSS_SD10G65_CHIP_VENICE) &&
        (config.chip_name != VTSS_SD10G65_CHIP_JAGUAR2)) {
        ret_val->is_new_rcpll[0] = 1;
    } else {
        ret_val->is_new_rcpll[0] = 0;

    }

    ret_val->rx_rcpll_cfg2__pll_vco_cur[0] = 7;
    ret_val->rx_rcpll_cfg2__pll_vreg18[0]  = 10;
    if (f_sam_khz_plain > 7000000) {
      ret_val->rx_rcpll_cfg2__pll_lpf_cur[0] = 3;
      ret_val->rx_rcpll_cfg2__pll_lpf_res[0] = 10;
    } else if (f_sam_khz_plain > 3000000) {
      ret_val->rx_rcpll_cfg2__pll_lpf_cur[0] = 2;
      ret_val->rx_rcpll_cfg2__pll_lpf_res[0] = 15;
    } else {
      ret_val->rx_rcpll_cfg2__pll_lpf_cur[0] = 0;
      ret_val->rx_rcpll_cfg2__pll_lpf_res[0] = 10;
    }

    ret_val->rx_rcpll_cfg0__pllf_start_cnt[0]     = 2;
    ret_val->rx_rcpll_cfg0__pllf_syn_clk_ena[0]   = 0;
    ret_val->rx_rcpll_cfg0__pllf_loop_ctrl_ena[0] = 0;
    ret_val->rx_rcpll_cfg0__pllf_loop_ena[0]      = 0;
    ret_val->rx_rcpll_cfg0__pllf_ena[0]           = 0;

    ret_val->rx_rcpll_cfg1__pllf_ref_cnt_end[0] = (u16) ((u32)interface_width * 64 * 1000000/f_sam_khz_plain);

    ret_val->rx_rcpll_cfg0__pllf_oor_recal_ena[0] = 1;

    for (ifw_tmp = 4; ifw_tmp < 6; ifw_tmp++) {
        ret_val->des_cfg0__des_if_mode_sel[ifw_tmp-2]         = ifw_tmp;
        for (tog_cnt = 0; tog_cnt < 2*hrate_toggle_cnt; tog_cnt++) {
            ret_val->rx_synth_cfg0__synth_hrate_ena[2+(ifw_tmp-4)*2*hrate_toggle_cnt+tog_cnt] = (tog_cnt + 1) %2;
        }
    }
    for (ifw_tmp = 4; ifw_tmp < 6; ifw_tmp++) {
        for (tog_cnt = 0; tog_cnt < 2*hrate_toggle_cnt; tog_cnt++) {
            ret_val->rx_synth_cfg0__synth_ena[2+(ifw_tmp-4)*2*hrate_toggle_cnt+tog_cnt] = tog_cnt % 2;
        }
    }

    ret_val->rx_rcpll_cfg0__pllf_ena[1]           = 1;
    ret_val->rx_rcpll_cfg0__pllf_oor_recal_ena[1] = 0;

    /* ##################################################################### */
    /* ##################################################################### */
    /* # Perform setup_f2df config                                           */
    /* ##################################################################### */
    /* ##################################################################### */
    /*  In the F2DF of Venice RevA among others the latches that store the DFE coefficients are not reachable => disable DFE */
    ret_val->ib_cfg0__ib_dfe_ena[2]     = 0;
    /* Do some input buffer updates for SD10G running in F2DF mode */
    ret_val->ib_cfg2__ib_eqz_gain[0]     = 400;
    ret_val->ib_cfg1__ib_amp_l[0]          = 0;
    ret_val->ib_cfg1__ib_eqz_l0[0]         = 0;
    ret_val->ib_cfg1__ib_eqz_l1[0]         = 0;
    ret_val->ib_cfg1__ib_eqz_l2[0]         = 0;
    ret_val->ib_cfg1__ib_agc_l[0]          = 0;
    ret_val->ib_cfg1__ib_amp_c[0]          = 0;
    ret_val->ib_cfg1__ib_eqz_c0[0]         = 0;
    ret_val->ib_cfg1__ib_eqz_c1[0]         = 0;
    ret_val->ib_cfg1__ib_eqz_c2[0]         = 0;
    ret_val->ib_cfg9__ib_dfe_coef1[0]     = 96;

    /* Setup the Signal Detect logic */
    ret_val->ib_cfg3__ib_sdet_sel[1]       = 0;
    /* Configure Signal detect clock divider */
    /* Signal Detect checks for edges in a defined window */
    /* Window size is par_clock_period * 2^(2*IB_SDET_CLK_DIV+1) */
    /* With targeted sample frequency and interface width, the par_clock_period is between 125Mhz and 250MHz */
    /* We add a factor of 4 as security */
    if (f_in_khz_plain < 4000) {
        ret_val->ib_cfg3__ib_sdet_clk_div[0] = 5;
    } else if (f_in_khz_plain < 16000) {
        ret_val->ib_cfg3__ib_sdet_clk_div[0] = 4;
    } else if (f_in_khz_plain < 64000) {
        ret_val->ib_cfg3__ib_sdet_clk_div[0] = 3;
    } else {
        ret_val->ib_cfg3__ib_sdet_clk_div[0] = 2;
    }
    ret_val->ib_cfg3__ib_ia_sdet_level[1] = 2;
    /* Manually calibrate the IB */
    ret_val->ib_cfg5__ib_offs_value[1] = 32;
    for (i=0; i<4;i++) {
        ret_val->ib_cfg5__ib_offs_blksel[i] = i;
    }
    ret_val->ib_cfg5__ib_ia_offs_cal_ena[0] = 1;
    ret_val->ib_cfg5__ib_ia_offs_cal_ena[1] = 0;

    ret_val->rx_synth_cfg2__synth_dv_ctrl_i2e[0] = 0;
    ret_val->rx_synth_cfg2__synth_dv_ctrl_i1m[1] = 0;
    ret_val->rx_synth_cfg2__synth_dv_ctrl_i1e[1] = 0;

    ret_val->rx_synth_cdrlf[1] = (0x80000000 |
                                 ((u32)config.i1_lim  << 21) |
                                 ((u32)config.i1_lim  << 16) |
                                 ((u32)config.i1_lim  << 11) |
                                 ((u32)config.i1_fsel <<  6) |
                                 ((u32)config.i2_fsel <<  0));

    ret_val->rx_synth_cdrlf__synth_integ3_ena[1] = 1;
    ret_val->rx_synth_cdrlf__synth_integ1_lim[1]  = config.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_max0[1] = config.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_max1[1] = config.i1_lim;
    ret_val->rx_synth_cdrlf__synth_integ1_fsel[1] = config.i1_fsel;
    ret_val->rx_synth_cdrlf__synth_integ2_fsel[1] = config.i2_fsel;

    if ((config.chip_name == VTSS_SD10G65_CHIP_ES6512) ||
        (config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (config.chip_name == VTSS_SD10G65_CHIP_JAGUAR2)) {
        ret_val->chip_still_has_sample_mode[0] = 1;
        if (side_detect > 1) {
            VTSS_E("Input frequency to f2df cannot be handeled by this device");
            rslt = VTSS_RC_ERROR;
            return rslt;
        }
    } else {
        ret_val->chip_still_has_sample_mode[0] = 0;
    }

    ret_val->f2df_cfg_stat[0]        = ((side_detect         << 25) | /* F2DF_SAMPLE_DIV */
                                        (side_detect_bit_sel << 17) | /* F2DF_SIDE_DET_BIT_SEL */
                                        (0                   << 14) | /* F2DF_SIDE_DET_ONES_WEIGHT */
                                        (2                   << 11) | /* F2DF_SIDE_DET_ZEROS_WEIGHT */
                                        (40                  <<  4) | /* F2DF_TOG_DET_CNT */
                                        (0                   <<  3) | /* F2DF_DATA_VALID_PROPPER_SIDE */
                                        (0                   <<  2) | /* F2DF_STICKY_CLR */
                                        (1                   <<  0)); /* F2DF_ENABLE */
    ret_val->f2df_cfg_stat__f2df_side_det_bit_sel[0]        = side_detect_bit_sel;
    ret_val->f2df_cfg_stat__f2df_side_det_ones_weight[0]    = 0;
    ret_val->f2df_cfg_stat__f2df_side_det_zeros_weight[0]   = 2;
    ret_val->f2df_cfg_stat__f2df_tog_det_cnt[0]             = 40;
    ret_val->f2df_cfg_stat__f2df_data_valid_propper_side[0] = 0;
    ret_val->f2df_cfg_stat__f2df_sticky_clr[0]              = 0;
    ret_val->f2df_cfg_stat__f2df_sample_mode_div[0]         = side_detect;
    ret_val->f2df_cfg_stat__f2df_enable[0]                  = 1;

    return rslt;
}; /* vtss_calc_sd10g65_setup_f2df */


vtss_rc vtss_sd10g65_setup_df2f_args_init (vtss_sd10g65_setup_df2f_args_t     *const init_val) {

    init_val->chip_name        = VTSS_SD10G65_CHIP_ES65XX;
    init_val->f_out.f_pll_khz  = 125000; // changed because the default would cause an error!!
    init_val->f_out.ratio_num  = 66;
    init_val->f_out.ratio_den  = 64;
    init_val->no_pwrcycle      = FALSE;
    init_val->ls_ena           = FALSE;
    init_val->i2_fsel          = 35;
    init_val->inp_loop         = FALSE;
    init_val->pad_loop         = FALSE;
    init_val->incr_levn        = 1;
    init_val->ob_levn          = 7;

    return VTSS_RC_OK;
}


vtss_rc vtss_calc_sd10g65_setup_df2f(const vtss_sd10g65_setup_df2f_args_t config,
                                     vtss_sd10g65_setup_df2f_struct_t     *const ret_val) {

    vtss_rc                        rslt;
    vtss_sd10g65_f_pll_t           cfg_f_out = config.f_out;
    vtss_sd10g65_f_pll_t           cfg_f_sam;

    vtss_sd10g65_synth_mult_calc_rslt_t  synth_mult_calc_rslt;
    u32     f_out_khz_plain;
    u32     f_sam_khz_plain;

    u8      ifw_tmp;
    u8      tog_cnt;
    const u8 hrate_toggle_cnt = 2;

    BOOL    use_clk_gen;
    u8      interface_width;
    u8      num_periods;
    u8      dft_word_mode = 8; /* need to have a default value to avoid compiler warning */
    u8      num_words = 5;     /* need to have a default value to avoid compiler warning */
    u8      num_bits;
    BOOL    chip_supports_dft_clk_gen;
    u16     pattern[16] = { 0 };
    u8      toggle;
    u8      incr;
    u8      clock_gen_period_half = 16; /* need to have a default value to avoid compiler warning */
    u8      divider;
    u8      synth_half_rate_mode = 0;
    u8      i;



    rslt = VTSS_RC_OK;
    if ((config.chip_name == VTSS_SD10G65_CHIP_ES6512)  ||
        (config.chip_name == VTSS_SD10G65_CHIP_VENICE)  ||
        (config.chip_name == VTSS_SD10G65_CHIP_JAGUAR2)) {
        chip_supports_dft_clk_gen = FALSE;
    } else {
        chip_supports_dft_clk_gen = TRUE;
    }


    f_out_khz_plain = (u32) (MEPA_DIV64( ((u64) cfg_f_out.f_pll_khz * (u64) cfg_f_out.ratio_num), (u64) cfg_f_out.ratio_den));

    if (config.use_par_clk == FALSE) {
        if (f_out_khz_plain > 500000) {
            VTSS_E("Targeted output frequency to high. Must not be above 500 MHz");
            return VTSS_RC_ERROR;
        } else if (f_out_khz_plain < 1000) {
            VTSS_E("Targeted output frequency to low. Must not be below  1 MHz");
            return VTSS_RC_ERROR;
        } else {
            /*  to get low jitter use SER baudrate of 9..10.8GBps */
            if (f_out_khz_plain >= 140625) {
                use_clk_gen = FALSE;
                interface_width = 40;
                num_periods = 2; /* perids per pattern */
                dft_word_mode = 8;
                for (num_words = 5; num_words <= 16; num_words++) {
                    num_bits = num_words * dft_word_mode / num_periods;
                    if (f_out_khz_plain * num_bits >= 9000000) {
                        break;
                    }
                }

                cfg_f_sam.f_pll_khz = cfg_f_out.f_pll_khz * num_bits;
                cfg_f_sam.ratio_num = cfg_f_out.ratio_num;
                cfg_f_sam.ratio_den = cfg_f_out.ratio_den;
                f_sam_khz_plain = f_out_khz_plain * num_bits;

                /* With dft_word_mode == 8 and num_periods [1..2], num_bits is always a multiple of 4 */
                /* calculate the pattern to be stored in the const pattern generator */
                /* We have either 1 or 2 periods stored */
                /*                                                   */
                /* exampel 4 one period:     exampel 4 two periods:  */
                /*                                                   */
                /*        0x00                     0x00              */
                /*        0x00                     0xc0              */
                /*        0x00                     0xff              */
                /*        0xf0                     0x0f              */
                /*        0xff                     0x00              */
                /*        0xff                     0xfc              */
                /*        0xff                     0xff              */
                toggle = 0;
                incr   = 0;
                for (i=0 ; i < num_words ; i++) {
                    switch ((8*(i+1)) % (num_bits / 2)) {
                    case 0: {
                        pattern[i] = 0x00 ^ toggle;
                        break;
                    }
                    case 2: {
                        pattern[i] = 0x03 ^ toggle;
                        break;
                    }
                    case 4: {
                        pattern[i] = 0x0f ^ toggle;
                        break;
                    }
                    case 6: {
                        pattern[i] = 0x3f ^ toggle;
                        break;
                    }
                    default : {
                        pattern[i] = 0x00 ^ toggle;
                    }
                    }
                    incr += 8;
                    if (incr >= (num_bits/2)) {
                        toggle ^= 0xff;
                        incr -= num_bits / 2;
                    }
                }
            } else {
                if (chip_supports_dft_clk_gen == TRUE) {
                    if (f_out_khz_plain >= 56250) {
                        /* 9Ghz / 160 bit = 56.25MHz */
                        use_clk_gen = FALSE;
                        interface_width = 40;
                        num_periods = 1; /* perids per pattern */
                        dft_word_mode = 10;
                        for (num_words = 5; num_words <= 16; num_words++) {
                            num_bits = num_words * dft_word_mode / num_periods;
                            if (f_out_khz_plain * num_bits >= 9000000) {
                                break;
                            }
                        }

                        cfg_f_sam.f_pll_khz = cfg_f_out.f_pll_khz * num_bits;
                        cfg_f_sam.ratio_num = cfg_f_out.ratio_num;
                        cfg_f_sam.ratio_den = cfg_f_out.ratio_den;
                        f_sam_khz_plain = f_out_khz_plain * num_bits;
                        for (i=0 ; i < num_words/2 ; i++) {
                            pattern[i] = 0x00;
                            pattern[i+(num_words+1)/2] = 0x3ff;
                        }
                        if ((num_words % 2) == 1) {
                            pattern[num_words/2] = 0x01f;
                        }
                    } else {
                        /* use clock pattern generator */
                        use_clk_gen = TRUE;
                        interface_width = 32;
                        clock_gen_period_half = 10800000 / (f_out_khz_plain * interface_width * 2);
                        f_sam_khz_plain = f_out_khz_plain * interface_width * 2 * clock_gen_period_half;
                        cfg_f_sam.f_pll_khz = cfg_f_out.f_pll_khz * interface_width * 2 * clock_gen_period_half;
                        cfg_f_sam.ratio_num = cfg_f_out.ratio_num;
                        cfg_f_sam.ratio_den = cfg_f_out.ratio_den;
                    }
                } else { /* chip does not have the DFT clock gen */
                    if (f_out_khz_plain >= 56250) {
                        /* select sample frequency >= 9Ghz */
                        divider = 1;
                    } else if (f_out_khz_plain >= 28125) {
                        /* select sample frequency >= 4.5Ghz */
                        divider = 2;
                    } else if (f_out_khz_plain >= 15625) {
                        /* select sample frequency >= 2.5Ghz = lowest specified frequency for RC_PLL */
                        divider = 4;
                    } else if ((u64) cfg_f_out.f_pll_khz * cfg_f_out.ratio_num * 2 >= (u64) cfg_f_out.ratio_den * 15625) {
                        /* select sample frequency >= 1.25Ghz */
                        divider = 8;
                        synth_half_rate_mode = 1;
                    } else {
                        VTSS_E ("Sorry Tx frequencies below 7.8125 MHz are not supported for this chip\n");
                        return VTSS_RC_ERROR;
                    }
                    use_clk_gen = FALSE;
                    interface_width = 40;
                    num_periods = 1; /* periods per pattern */
                    dft_word_mode = 10;

                    for (num_words = 5; num_words <= 16; num_words++) {
                        num_bits = num_words * dft_word_mode / num_periods;
                        if (divider < 4) {
                            if (f_out_khz_plain * num_bits * divider >= 9000000) {
                                break;
                            }
                        } else if (divider < 8) {
                            if (f_out_khz_plain * num_bits * divider >= 10000000) {
                                break;
                            }
                        } else {
                            if ((u64) cfg_f_out.f_pll_khz * cfg_f_out.ratio_num * num_bits >= (u64) cfg_f_out.ratio_den * 1250000) {
                                break;
                            }
                        }
                    }
                    f_sam_khz_plain = f_out_khz_plain * num_bits * (1 + synth_half_rate_mode);
                    cfg_f_sam.f_pll_khz = cfg_f_out.f_pll_khz * num_bits * (1 + synth_half_rate_mode);
                    cfg_f_sam.ratio_num = cfg_f_out.ratio_num;
                    cfg_f_sam.ratio_den = cfg_f_out.ratio_den;
                    for (i=0 ; i < num_words/2 ; i++) {
                        pattern[i] = 0x00;
                        pattern[i+(num_words+1)/2] = 0x3ff;
                    }
                    if ((num_words % 2) == 1) {
                        pattern[num_words/2] = 0x01f;
                    }
                }
            }
        }
    } else {  /* config.use_par_clk == TRUE  -- We want to have the parrallel clock towards the core configured*/
        use_clk_gen = FALSE;
        if (f_out_khz_plain > 400000) {
            VTSS_E("Targeted parallel clock frequency to high. Must not be above 400 MHz");
            return VTSS_RC_ERROR;
        } else if (f_out_khz_plain < 31250) {
            VTSS_E("Targeted parallel clock frequency to low. Must not be below  31.25 MHz");
            return VTSS_RC_ERROR;
        } else {
            if (f_out_khz_plain < 41667) {
                /*  31.25 MHz .. 41.66 MHz: 1G25 mode @ 40bit IW */
                interface_width = 40;
                synth_half_rate_mode = 1;
            } else if (f_out_khz_plain < 83334) {
                /*  41.66 MHz .. 83.33 MHz:  2G5 mode @ 40bit IW */
                interface_width = 40;
            } else if (f_out_khz_plain < 166667) {
                /*  83.33 MHz .. 166.6 MHZ:   5G mode @ 40bit IW */
                interface_width = 40;
            } else if (f_out_khz_plain < 250000) {
                /*  166.6 MHz .. 250.0 MHz:  10G mode @ 40bit IW */
                interface_width = 40;
            } else if (f_out_khz_plain < 333334) {
                /*  250.0 MHz .. 333.3 MHz:  10G mode @ 32bit IW */
                interface_width = 32;
            } else {
                /*  333.3 MHz .. 400.0 MHz:  10G mode @ 20bit IW */
                interface_width = 20;
            }
            f_sam_khz_plain = f_out_khz_plain * interface_width * (1 + synth_half_rate_mode);
            cfg_f_sam.f_pll_khz = cfg_f_out.f_pll_khz * interface_width * (1 + synth_half_rate_mode);
            cfg_f_sam.ratio_num = cfg_f_out.ratio_num;
            cfg_f_sam.ratio_den = cfg_f_out.ratio_den;

        }

    }

    /* ##################################################################### */
    /* ##################################################################### */
    /* # Perform setup_tx config                                             */
    /* ##################################################################### */
    /* ##################################################################### */

    if ((config.no_pwrcycle == 0) &&
        ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
         (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
         (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B))) {
        ret_val->pwrcycle[0] = 1;
    } else {
        ret_val->pwrcycle[0] = 0;
    }

    ret_val->f_out_khz_plain[0] = f_out_khz_plain;
    ret_val->f_out_f_pll_khz[0] = cfg_f_out.f_pll_khz;
    ret_val->f_out_ratio_num[0] = cfg_f_out.ratio_num;
    ret_val->f_out_ratio_den[0] = cfg_f_out.ratio_den;
    ret_val->f_sam_khz_plain[0] = f_sam_khz_plain;
    ret_val->f_sam_f_pll_khz[0] = cfg_f_sam.f_pll_khz;
    ret_val->f_sam_ratio_num[0] = cfg_f_sam.ratio_num;
    ret_val->f_sam_ratio_den[0] = cfg_f_sam.ratio_den;

    ret_val->tx_synth_cfg0__synth_ena[0]          = 0;
    ret_val->tx_rcpll_cfg2__pll_ena[0]            = 0;
    ret_val->ob_cfg0__en_ob[0]                    = 0;


    /* Rolex does not have a GDC Tx macro, but it is used as an example for devices that do have a Tx/Tx pair */
    if (config.chip_name == VTSS_SD10G65_CHIP_ROLEX) {
        ret_val->sbus_special_handling[0] = 1;
    } else {
        ret_val->sbus_special_handling[0] = 0;
    }
    ret_val->sbus_tx_cfg__sbus_bias_en[0]         = 1;
    ret_val->sbus_tx_cfg__sbus_bias_speed_sel[0]  = 3;
    ret_val->sbus_rx_cfg__sbus_bias_en[0]         = 1;
    ret_val->sbus_rx_cfg__sbus_bias_speed_sel[0]  = 3;
    ret_val->ob_cfg0__en_ob[1]                    = 1;
    ret_val->tx_rcpll_cfg2__pll_ena[1]            = 1;
    ret_val->tx_synth_cfg0__synth_ena[1]          = 1;
    ret_val->tx_synth_cfg0__synth_spare_pool[0]   = 7;

    if (f_sam_khz_plain > 10312500) {
      ret_val->tx_synth_cfg0__synth_off_comp_ena[0] = 31;
    } else {
      ret_val->tx_synth_cfg0__synth_off_comp_ena[0] = 23;
    }

    ret_val->hr_mode[0]                           = synth_half_rate_mode;

    rslt |= sd10g65_synth_mult_calc(cfg_f_sam, config.chip_name, &synth_mult_calc_rslt);

    ret_val->tx_synth_cfg0__synth_speed_sel[0]      = synth_mult_calc_rslt.synth_speed_sel;
    ret_val->tx_synth_cfg0__synth_fbdiv_sel[0]      = synth_mult_calc_rslt.synth_fbdiv_sel;
    ret_val->tx_synth_cfg3__synth_freqm_0[0]        = synth_mult_calc_rslt.synth_freqm_0;
    ret_val->tx_synth_cfg4__synth_freqn_0[0]        = synth_mult_calc_rslt.synth_freqn_0;
    ret_val->tx_synth_cfg1__synth_freqm_1[0]        = synth_mult_calc_rslt.synth_freqm_1;
    ret_val->tx_synth_cfg1__synth_freqn_1[0]        = synth_mult_calc_rslt.synth_freqn_1;
    ret_val->tx_synth_cfg1__synth_freq_mult_byp[0]  = synth_mult_calc_rslt.synth_freq_mult_byp;
    ret_val->tx_synth_cfg1__synth_freq_mult_hi[0]   = synth_mult_calc_rslt.synth_freq_mult_hi;
    ret_val->tx_synth_cfg1__synth_freq_mult[0]      = synth_mult_calc_rslt.synth_freq_mult;
    ret_val->tx_synth_cfg0__synth_ls_speed[0]       = synth_mult_calc_rslt.tx_synth_ls_speed;
    ret_val->tx_synth_cfg0__synth_cs_speed[0]       = synth_mult_calc_rslt.tx_synth_cs_speed;

    if ((config.chip_name == VTSS_SD10G65_CHIP_VENICE) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU) ||
        (config.chip_name == VTSS_SD10G65_CHIP_MALIBU_B)) {
        ret_val->chip_needs_hrate_toggle[0] = 1;
    } else {
        ret_val->chip_needs_hrate_toggle[0] = 0;
    }

    ret_val->tx_synth_cfg0__synth_hrate_ena[0]  = (synth_half_rate_mode + 1) % 2;
    ret_val->tx_synth_cfg0__synth_hrate_ena[1]  = synth_half_rate_mode;

    ret_val->tx_synth_cfg0__synth_ena_sync_unit[0] = 1;
    ret_val->tx_synth_cfg0__synth_conv_ena[0]      = 1;
    ret_val->tx_synth_cfg0__synth_ds_ena[0]        = 0;
    ret_val->tx_synth_cfg0__synth_ds_dir[0]        = 0;
    ret_val->tx_synth_cfg0__synth_ds_speed[0]      = 0;
    ret_val->tx_synth_cfg0__synth_ls_dir[0]        = 0;
    ret_val->tx_synth_cfg0__synth_ls_ena[0]        = config.ls_ena;

    ret_val->ssc_cfg1__sync_ctrl_fsel[0] = config.i2_fsel;
    if (config.inp_loop == TRUE) {
        ret_val->ob_cfg0__en_inp_loop[0]     = 1;
        ret_val->ob_cfg0__en_pad_loop[0]     = 0;
    } else if (config.pad_loop == TRUE) {
        ret_val->ob_cfg0__en_inp_loop[0]     = 0;
        ret_val->ob_cfg0__en_pad_loop[0]     = 1;
    } else {
        ret_val->ob_cfg0__en_inp_loop[0]     = 0;
        ret_val->ob_cfg0__en_pad_loop[0]     = 0;
    }
    ret_val->ob_cfg0__sel_ifw[0]         = sd10g65_get_iw_setting(interface_width);
    ret_val->ob_cfg0__ser_inv[0]         = 0;

    if (config.use_par_clk == FALSE) {
        /* power up output buffer */
        ret_val->ob_cfg0__incr_levn[0]       = config.incr_levn;
        ret_val->ob_cfg0__levn[0]            = config.ob_levn;
        ret_val->ob_cfg0__en_direct[0]       = 0;
        // interface_width is alway > 10 :
        ret_val->ob_cfg2__d_filter[0]        = 0x7DF820;
    } else {
        /* disable output buffer */
        ret_val->ob_cfg0__incr_levn[0]       = 1;
        ret_val->ob_cfg0__levn[0]            = 31;
        ret_val->ob_cfg0__en_direct[0]       = 1;
        ret_val->ob_cfg2__d_filter[0]        = 0;
    }
    ret_val->ob_cfg1__lev_shft[0]        = 1;
    ret_val->ob_cfg1__predrv_r_ctrl[0]   = 3;
    ret_val->ob_cfg1__predrv_c_ctrl[0]   = 3;


    if ((config.chip_name != VTSS_SD10G65_CHIP_ES6514) &&
        (config.chip_name != VTSS_SD10G65_CHIP_VENICE) &&
        (config.chip_name != VTSS_SD10G65_CHIP_JAGUAR2)) {
        ret_val->is_new_rcpll[0] = 1;
    } else {
        ret_val->is_new_rcpll[0] = 0;

    }

    ret_val->tx_rcpll_cfg2__pll_vco_cur[0] = 7;
    ret_val->tx_rcpll_cfg2__pll_vreg18[0]  = 10;
    if (f_sam_khz_plain > 7000000) {
        ret_val->tx_rcpll_cfg2__pll_lpf_cur[0] = 3;
        ret_val->tx_rcpll_cfg2__pll_lpf_res[0] = 10;
    } else if (f_sam_khz_plain > 3000000) {
        ret_val->tx_rcpll_cfg2__pll_lpf_cur[0] = 2;
        ret_val->tx_rcpll_cfg2__pll_lpf_res[0] = 15;
    } else {
        ret_val->tx_rcpll_cfg2__pll_lpf_cur[0] = 0;
        ret_val->tx_rcpll_cfg2__pll_lpf_res[0] = 10;
    }

    ret_val->tx_rcpll_cfg0__pllf_start_cnt[0]     = 2;
    ret_val->tx_rcpll_cfg0__pllf_syn_clk_ena[0]   = 0;
    ret_val->tx_rcpll_cfg0__pllf_loop_ctrl_ena[0] = 0;
    ret_val->tx_rcpll_cfg0__pllf_loop_ena[0]      = 0;
    ret_val->tx_rcpll_cfg0__pllf_ena[0]           = 0;

    if (synth_half_rate_mode == 1) {
        ret_val->tx_rcpll_cfg1__pllf_ref_cnt_end[0] = (u16) ((u32)interface_width * 64 * 1000000/(f_sam_khz_plain >> 1));
    } else {
        ret_val->tx_rcpll_cfg1__pllf_ref_cnt_end[0] = (u16) ((u32)interface_width * 64 * 1000000/f_sam_khz_plain);
    }

    ret_val->tx_rcpll_cfg0__pllf_oor_recal_ena[0] = 1;

    for (ifw_tmp = 4; ifw_tmp < 6; ifw_tmp++) {
        ret_val->ob_cfg0__sel_ifw[ifw_tmp-3]         = ifw_tmp;
        for (tog_cnt = 0; tog_cnt < 2*hrate_toggle_cnt; tog_cnt++) {
            ret_val->tx_synth_cfg0__synth_hrate_ena[2+(ifw_tmp-4)*2*hrate_toggle_cnt+tog_cnt] = (synth_half_rate_mode + tog_cnt + 1) %2;
        }
    }

    ret_val->tx_rcpll_cfg0__pllf_ena[1]           = 1;
    ret_val->tx_rcpll_cfg0__pllf_oor_recal_ena[1] = 0;

    /* ##################################################################### */
    /* ##################################################################### */
    /* # Perform setup_df2f config                                           */
    /* ##################################################################### */
    /* ##################################################################### */
    ret_val->use_par_clk[0]                      = to_u8_(config.use_par_clk);
    ret_val->use_clk_gen[0]                      = to_u8_(use_clk_gen);
    /* default values */
    ret_val->dft_clk_gen_cfg__cg_per_cfg[0]      = 0;
    ret_val->dft_clk_gen_cfg__cg_per_jump_cfg[0] = 0;
    ret_val->dft_clk_gen_cfg__cg_dcd_cfg[0]      = 0;
    ret_val->dft_clk_gen_cfg__cg_mode_cfg[0]     = 0;
    ret_val->dft_tx_cfg__tx_wid_sel_cfg[0]       = 5;
    ret_val->dft_tx_cfg__opath_cfg[0]            = 0;
    ret_val->dft_tx_cfg__dft_tx_ena[0]           = 0;
    ret_val->dft_tx_cfg__tx_word_mode_cfg[0]     = 0;
    ret_val->dft_tx_cfg__ipath_cfg[0]            = 1;
    ret_val->dft_tx_cfg__tx_prbs_sel_cfg[0]      = 4;
    ret_val->dft_tx_cfg__scram_inv_cfg[0]        = 1;
    if (config.use_par_clk == FALSE) {
        if (use_clk_gen == TRUE) {
            ret_val->dft_clk_gen_cfg__cg_per_cfg[0]      = clock_gen_period_half;
            ret_val->dft_clk_gen_cfg__cg_per_jump_cfg[0] = clock_gen_period_half;
            ret_val->dft_clk_gen_cfg__cg_dcd_cfg[0]      = 0;
            ret_val->dft_clk_gen_cfg__cg_mode_cfg[0]     = 0;
            ret_val->dft_tx_cfg__tx_wid_sel_cfg[0]       = sd10g65_get_iw_setting(interface_width);
            ret_val->dft_tx_cfg__opath_cfg[0]            = 2;
            ret_val->dft_tx_cfg__dft_tx_ena[0]           = 1;
        } else {
            ret_val->dft_tx_cfg__dft_tx_ena[0]           = 1;
            ret_val->dft_tx_cfg__tx_wid_sel_cfg[0]       = sd10g65_get_iw_setting(interface_width);
            ret_val->dft_tx_cfg__tx_word_mode_cfg[0]     = (dft_word_mode == 8) ? 0 : 1;
            ret_val->dft_tx_cfg__ipath_cfg[0]            = 0;
            ret_val->dft_tx_cfg__scram_inv_cfg[0]        = 1;
            ret_val->num_words[0]                        = num_words;
            for (i=0 ; i < 16 ; i++) {
                if (i < num_words) {
                    /* pattern must be written highest address downto 0 */
                    ret_val->dft_tx_pat_cfg__store_addr_cfg[i] = i;
                    ret_val->dft_tx_pat_cfg__pattern_cfg[i]    = pattern[i];
                    ret_val->dft_tx_pat_cfg__pat_vld_cfg[0]    = 1;
                    ret_val->dft_tx_pat_cfg__pat_vld_cfg[1]    = 0;
                } else {
                    ret_val->dft_tx_pat_cfg__store_addr_cfg[i] = 0;
                    ret_val->dft_tx_pat_cfg__pattern_cfg[i]    = 0;
                }
            }
            ret_val->dft_tx_pat_cfg__max_addr_gen_cfg[0]      = (num_words-1) ^ 0x1; /* see Bugzilla #17784 */
            ret_val->dft_tx_pat_cfg__max_addr_gen_cfg[1]      = num_words-1;
            ret_val->dft_tx_cfg__opath_cfg[0]                 = 1;
        }
    }
    ret_val->interface_width[0] = interface_width;

    return rslt;
}



/* ******************************************************************************** */
/* ***                        E N D   O F    F I L E                            *** */
/* ******************************************************************************** */
